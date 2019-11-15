package classpath

import (
	"os"
	"path/filepath"
	"strings"
)

/*
	通配符类路径仅匹配指定目录下的 JAR 文件
*/
func newWildcardEntry(path string) CompositeEntry {
	baseDir := path[:len(path)-1]

	compositeEntry := []Entry{}

	walkFn := func(path string, fileInfo os.FileInfo, err error) error {
		if err != nil {
			return nil
		}

		if fileInfo.IsDir() && path != baseDir {
			return filepath.SkipDir
		}

		if strings.HasSuffix(path, ".jar") || strings.HasSuffix(path, ".JAR") {
			jarEntry := newZipEntry(path)

			compositeEntry = append(compositeEntry, jarEntry)
		}

		return nil
	}

	filepath.Walk(baseDir, walkFn)

	return compositeEntry
}
