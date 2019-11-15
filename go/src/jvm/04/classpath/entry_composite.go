package classpath

import (
	"errors"
	"strings"
)

/*
	在 Go 中，数组属于比较底层的数据结构，很少直接使用。
	大部分情况下，使用更便利的 slice 类型
*/
type CompositeEntry []Entry

/*
	1. 将路径列表按分隔符分成多个小路径
	2. 将小路径转换为具体的 Entry 实例
*/
func newCompositeEntry(pathList string) CompositeEntry {
	compositeEntry := []Entry{}

	for _, path := range strings.Split(pathList, pathListSeparator) {
		entry := newEntry(path)

		compositeEntry = append(compositeEntry, entry)
	}

	return compositeEntry
}

/*
	依次调用每个子 Entry 的 readClass 方法，如果成功读取到 class 数据，
	则返回数据，否则如果收到错误信息，则继续遍历，如果遍历结束仍未找到 class 文件，则返回错误信息
*/
func (self CompositeEntry) readClass(className string) ([]byte, Entry, error) {
	for _, entry := range self {
		data, from, err := entry.readClass(className)

		if err == nil {
			return data, from, err
		}
	}

	return nil, nil, errors.New("class not found: " + className)
}

func (self CompositeEntry) String() string {
	strs := make([]string, len(self))

	for i, entry := range self {
		strs[i] = entry.String()
	}

	return strings.Join(strs, pathListSeparator)
}
