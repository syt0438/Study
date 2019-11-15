package constants

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type BIPUSH struct {
	val int8
}

type SIPUSH struct {
	val int16
}

func (self *BIPUSH) FetchOperands(reader *base.BytecodeReader) {
	self.val = reader.ReadInt8()
}

func (self *BIPUSH) Execute(frame *rtda.Frame) {
	val := int32(self.val)

	frame.OperandStack().PushInt(val)
}

func (self *SIPUSH) FetchOperands(reader *base.BytecodeReader) {
	self.val = reader.ReadInt16()
}

func (self *SIPUSH) Execute(frame *rtda.Frame) {
	val := int32(self.val)

	frame.OperandStack().PushInt(val)
}
