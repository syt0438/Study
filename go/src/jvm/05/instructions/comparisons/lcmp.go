package comparisons

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type LCMP struct {
	base.NoOperandsInstruction
}

func (self *LCMP) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	val2 := stack.PopLong()
	val1 := stack.PopLong()

	if val1 > val2 {
		stack.PushInt(1)
	} else if val1 == val2 {
		stack.PushInt(0)
	} else {
		stack.PushInt(-1)
	}

}
