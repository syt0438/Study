package conversions

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type L2I struct {
	base.NoOperandsInstruction
}

type L2F struct {
	base.NoOperandsInstruction
}

type L2D struct {
	base.NoOperandsInstruction
}

func (self *L2I) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopLong()

	stack.PushInt(int32(val))
}
func (self *L2F) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopLong()

	stack.PushFloat(float32(val))
}
func (self *L2D) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val := stack.PopLong()

	stack.PushDouble(float64(val))
}
