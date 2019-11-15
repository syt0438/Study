package base

import "jvm/05/rtda"

type Instruction interface {
	/*
		用于从字节码中提取操作数
	*/
	FetchOperands(reader *BytecodeReader)

	/*
		执行具体的指令逻辑
	*/
	Execute(frame *rtda.Frame)
}

// 表示无操作数的指令
type NoOperandsInstruction struct{}

// 表示跳转指令
type BranchInstruction struct {
	Offset int // 存放跳转偏移量
}

// 根据单字节操作数获取索引，来操作局部变量表
type Index8Instruction struct {
	Index uint
}

// 根据两字节操作数获取索引，来访问运行时常量池
type Index16Instruction struct {
	Index uint
}

func (self *NoOperandsInstruction) FetchOperands(reader *BytecodeReader) {
	// nothing to do
}

// 获取指令跳转偏移量：从字节码中读取一个 int16 整数，转成 int 后赋给 Offset 字段
func (self *BranchInstruction) FetchOperands(reader *BytecodeReader) {
	self.Offset = int(reader.ReadInt16())
}

// 获取局部变量表索引：从字节码中读取一个 int8 整数，转成 uint 后赋给 Index 字段
func (self *Index8Instruction) FetchOperands(reader *BytecodeReader) {
	self.Index = uint(reader.ReadUint8())
}

// 获取运行时常量池索引：从字节码中读取一个 uint16 整数，转成 uint 后赋给 Index 字段
func (self *Index16Instruction) FetchOperands(reader *BytecodeReader) {
	self.Index = uint(reader.ReadUint16())
}
