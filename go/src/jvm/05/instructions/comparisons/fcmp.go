package comparisons

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

// float compare: greater than
type FCMPG struct {
	base.NoOperandsInstruction
}

// float compare: less than
type FCMPL struct {
	base.NoOperandsInstruction
}

func (self *FCMPG) Execute(frame *rtda.Frame) {
	_fcmp(frame, true)
}

func (self *FCMPL) Execute(frame *rtda.Frame) {
	_fcmp(frame, false)
}

func _fcmp(frame *rtda.Frame, flag bool) {
	stack := frame.OperandStack()

	v2 := stack.PopFloat()
	v1 := stack.PopFloat()

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
