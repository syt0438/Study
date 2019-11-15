package conversions

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type I2B struct {
	base.NoOperandsInstruction
}

type I2C struct {
	base.NoOperandsInstruction
}

type I2S struct {
	base.NoOperandsInstruction
}

type I2L struct {
	base.NoOperandsInstruction
}

type I2F struct {
	base.NoOperandsInstruction
}

type I2D struct {
	base.NoOperandsInstruction
}

func (self *I2B) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopInt()

	result := int32(int8(val))

	stack.PushInt(result)
}

func (self *I2C) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopInt()

	result := int32(uint16(val))

	stack.PushInt(result)
}

func (self *I2S) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopInt()

	result := int32(int16(val))

	stack.PushInt(result)
}

func (self *I2L) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopInt()

	stack.PushLong(int64(val))
}
func (self *I2F) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopInt()

	stack.PushFloat(float32(val))
}
func (self *I2D) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopInt()

	stack.PushDouble(float64(val))
}
