package main

import (
	"fmt"
	"jvm/05/classfile"
	"jvm/05/classpath"
	"strings"
)

/*
	Go 中没有专门的构造函数，本项目统一使用 new 开头的函数来创建结构体实例，并将此类函数称为构造函数
*/
func main() {
	cmd := parseCmd()

	if cmd.versionFlag {
		fmt.Println("version 0.0.1")

		return
	}

	if cmd.helpFlag || cmd.class == "" {
		printUsage()

		return
	}

	startJVM(cmd)
}

func startJVM(cmd *Cmd) {
	cp := classpath.Parse(cmd.XjreOption, cmd.cpOption)
	className := strings.Replace(cmd.class, ".", "/", -1)
	cf := loadClass(className, cp)
	mainMethod := getMainMethod(cf)

	if mainMethod == nil {
		fmt.Printf("Main method not found in class %s \n", cmd.class)

		return
	}

	interpret(mainMethod)
}

func loadClass(className string, cp *classpath.Classpath) *classfile.ClassFile {
		classData, _, err := cp.ReadClass(className)

		if err != nil {
		panic(err)
	}

		cf, err := classfile.Parse(classData)

		if err != nil {
		panic(err)
	}

	return cf
}

func getMainMethod(cf *classfile.ClassFile) *classfile.MemberInfo {
	for _, method := range cf.Methods() {
		if method.Name() == "main" && method.Descriptor() == "([Ljava/lang/String;)V" {
			return method
		}
	}

	return nil
}
