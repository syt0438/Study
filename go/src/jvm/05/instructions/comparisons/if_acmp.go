package comparisons

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type IF_ACMPEQ struct {
	base.BranchInstruction
}

type IF_ACMPNE struct {
	base.BranchInstruction
}

func (self *IF_ACMPEQ) Execute(frame *rtda.Frame) {
	if _acmp(frame) {
		base.Branch(frame, self.Offset)
	}
}

func (self *IF_ACMPNE) Execute(frame *rtda.Frame) {
	if !_acmp(frame) {
		base.Branch(frame, self.Offset)
	}
}

func _acmp(frame *rtda.Frame) bool {
	stack := frame.OperandStack()

	v2 := stack.PopRef()
	v1 := stack.PopRef()

	return v1 == v2
}
