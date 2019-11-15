package math

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
	"math"
)

type IREM struct {
	base.NoOperandsInstruction
}

type LREM struct {
	base.NoOperandsInstruction
}

type FREM struct {
	base.NoOperandsInstruction
}

type DREM struct {
	base.NoOperandsInstruction
}

func (self *IREM) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopInt()
	v1 := stack.PopInt()

	if v2 == 0 {
		panic("java.lang.ArithmeticException: / by zero")
	}

	result := v1 % v2

	stack.PushInt(result)
}

func (self *LREM) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopLong()
	v1 := stack.PopLong()

	if v2 == 0 {
		panic("java.lang.ArithmeticException: / by zero")
	}

	result := v1 % v2

	stack.PushLong(result)
}

func (self *FREM) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := float64(stack.PopFloat())
	v1 := float64(stack.PopFloat())

	result := float32(math.Mod(v1, v2))

	stack.PushFloat(result)
}

func (self *DREM) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()
	v2 := stack.PopDouble()
	v1 := stack.PopDouble()

	result := math.Mod(v1, v2)

	stack.PushDouble(result)
}
