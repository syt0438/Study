package main

import (
	"fmt"
	"jvm/02/classpath"
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

	fmt.Printf("Classpath: %v class: %v args: %v\n", cp, cmd.class, cmd.args)

	className := strings.Replace(cmd.class, ".", "/", -1)

	data, _, err := cp.ReadClass(className)

	if err != nil {
		fmt.Printf("Could not found or load main class: %s ", cmd.class)

		return
	}

	fmt.Printf("Main class data: %v\n", data)
}
