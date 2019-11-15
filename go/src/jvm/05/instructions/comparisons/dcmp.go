package comparisons

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

// double compare: greater than
type DCMPG struct {
	base.NoOperandsInstruction
}

// double compare: less than
type DCMPL struct {
	base.NoOperandsInstruction
}

func (self *DCMPG) Execute(frame *rtda.Frame) {
	_dcmp(frame, true)
}

func (self *DCMPL) Execute(frame *rtda.Frame) {
	_dcmp(frame, false)
}

func _dcmp(frame *rtda.Frame, flag bool) {
	stack := frame.OperandStack()

	v2 := stack.PopDouble()
	v1 := stack.PopDouble()

	if v1 > v2 {
		stack.PushInt(1)
	} else if v1 == v2 {
		stack.PushInt(0)
	} else if v1 < v2 {
		stack.PushInt(-1)
	} else if flag {
		stack.PushInt(1)
	} else {
		stack.PushInt(-1)
	}
}
