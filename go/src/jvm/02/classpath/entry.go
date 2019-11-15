package classpath

import (
	"os"
	"strings"
)

const pathListSeparator = string(os.PathListSeparator)

/*
	定义 Entry 接口，用于表示类路径项
	注意: Go 中的结构体不需要显式实现接口，只要方法匹配即可
*/
type Entry interface {
	// Go 惯例: Go 中的函数或方法允许返回多个值，最后一个返回值作为错误信息
	readClass(className string) ([]byte, Entry, error)

	String() string
}

func newEntry(path string) Entry {
	if strings.Contains(path, pathListSeparator) {
		return newCompositeEntry(path)
	}

	if strings.HasSuffix(path, "*") {
		return newWildcardEntry(path)
	}

	if strings.HasSuffix(path, ".jar") || strings.HasSuffix(path, ".JAR") ||
		strings.HasSuffix(path, ".zip") || strings.HasSuffix(path, ".ZIP") {
		return newZipEntry(path)
	}

	return newDirEntry(path)
}
