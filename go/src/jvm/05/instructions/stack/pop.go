package stack

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

// 弹出占用一个操作数栈位置的变量
type POP struct {
	base.NoOperandsInstruction
}

// 弹出占用两个操作数栈位置的变量
type POP2 struct {
	base.NoOperandsInstruction
}

func (self *POP) Execute(frame *rtda.Frame) {
	frame.OperandStack().PopSlot()
}

func (self *POP2) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	stack.PopSlot()
	stack.PopSlot()
}
