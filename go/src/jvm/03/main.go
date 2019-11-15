package main

import (
	"fmt"
	"jvm/03/classfile"
	"jvm/03/classpath"
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
	classFile := loadClass(className, cp)

	fmt.Println(cmd.class)
	printClassInfo(classFile)

}

func printClassInfo(classFile *classfile.ClassFile) {
	fmt.Printf("Version: %v.%v\n", classFile.MajorVersion(), classFile.MinorVersion())
	fmt.Printf("Constants Count: %v\n", len(classFile.ConstantPool()))
	fmt.Printf("Access Flags: 0x%x\n", classFile.AccessFlags())
	fmt.Printf("This Class: %v\n", classFile.ClassName())
	fmt.Printf("Super Class: %v\n", classFile.SuperClassName())
	fmt.Printf("Interfaces: %v\n", classFile.InterfaceNames())

	fmt.Printf("Fields Count: %v\n", len(classFile.Fields()))

	for _, field := range classFile.Fields() {
		fmt.Printf("    %s -> %s\n", field.Name(), field.Descriptor())
	}

	fmt.Printf("Methods Count: %v\n", len(classFile.Methods()))

	for _, method := range classFile.Methods() {
		fmt.Printf("    %s -> %s\n", method.Name(), method.Descriptor())
	}
}

func loadClass(className string, cp *classpath.Classpath) *classfile.ClassFile {
	classData, _, err := cp.ReadClass(className)

	if err != nil {
		panic(err)
	}

	classFile, err := classfile.Parse(classData)

	if err != nil {
		panic(err)
	}

	return classFile
}
