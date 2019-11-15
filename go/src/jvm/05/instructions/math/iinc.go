package math

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type IINC struct {
	Index uint  // 1 个字节的局部变量表索引
	Const int32 // 1 个字节的常量值
}

func (self *IINC) FetchOperands(reader *base.BytecodeReader) {
	self.Index = uint(reader.ReadUint8())
	self.Const = int32(reader.ReadInt8())
}

func (self *IINC) Execute(frame *rtda.Frame) {
	localVars := frame.LocalVars()

	val := localVars.GetInt(self.Index)
	val += self.Const

	localVars.SetInt(self.Index, val)
}
