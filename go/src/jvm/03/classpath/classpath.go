package classpath

import (
	"os"
	"path/filepath"
)

type Classpath struct {
	bootClasspath Entry
	extClasspath  Entry
	userClasspath Entry
}

/*
	1. 使用-Xjre选项解析启动类路径和扩展类路径
	2. 使用 -classpath 或 -cp 选项解析用户类路径
*/
func Parse(jreOption string, cpOption string) *Classpath {
	cp := &Classpath{}

	cp.parseBootAndExtClasspath(jreOption)
	cp.parseUserClasspath(cpOption)

	return cp
}

func (self *Classpath) parseBootAndExtClasspath(jreOption string) {
	jreDir := getJreDir(jreOption)

	// jre/lib/*
	jreLibPath := filepath.Join(jreDir, "lib", "*")
	self.bootClasspath = newWildcardEntry(jreLibPath)

	// jre/lib/ext/*
	jreExtPath := filepath.Join(jreDir, "lib", "ext", "*")
	self.extClasspath = newWildcardEntry(jreExtPath)
}

/*
	如果用户没有提供-classpath/-cp选项，则使用当前目录作为用户类路径
*/
func (self *Classpath) parseUserClasspath(cpOption string) {
	if cpOption == "" {
		cpOption = "."
	}

	self.userClasspath = newEntry(cpOption)
}

/*
	依次从启动类路径、扩展类路径和用户类路径中搜索 class 文件
*/
func (self *Classpath) ReadClass(className string) ([]byte, Entry, error) {
	className = className + ".class"

	if data, entry, err := self.bootClasspath.readClass(className); err == nil {
		return data, entry, err
	}

	if data, entry, err := self.extClasspath.readClass(className); err == nil {
		return data, entry, err
	}

	return self.userClasspath.readClass(className)
}

func (self *Classpath) String() string {
	return self.userClasspath.String()
}

func exists(path string) bool {
	_, err := os.Stat(path)

	if err != nil {
		return false
	}

	return true
}

/*
	获取 Jre 运行时的库目录路径(包括启动类路径、扩展类路径)
*/
func getJreDir(jreOption string) string {
	if jreOption != "" && exists(jreOption) {
		return jreOption
	}

	localJreDir := "./jre"

	if exists(localJreDir) {
		return localJreDir
	}

	jh := os.Getenv("JAVA_HOME")

	if jh != "" {
		return filepath.Join(jh, "jre")
	}

	panic("Could not found jre folder!")
}
