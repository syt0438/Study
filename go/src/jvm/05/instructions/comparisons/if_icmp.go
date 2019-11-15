package comparisons

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type IF_ICMPEQ struct {
	base.BranchInstruction
}

type IF_ICMPNE struct {
	base.BranchInstruction
}

type IF_ICMPGT struct {
	base.BranchInstruction
}

type IF_ICMPGE struct {
	base.BranchInstruction
}

type IF_ICMPLE struct {
	base.BranchInstruction
}

type IF_ICMPLT struct {
	base.BranchInstruction
}

func (self *IF_ICMPEQ) Execute(frame *rtda.Frame) {
	if v1, v2 := _icmp(frame); v1 == v2 {
		base.Branch(frame, self.Offset)
	}
}

func (self *IF_ICMPNE) Execute(frame *rtda.Frame) {
	if v1, v2 := _icmp(frame); v1 != v2 {
		base.Branch(frame, self.Offset)
	}
}

func (self *IF_ICMPGT) Execute(frame *rtda.Frame) {
	if v1, v2 := _icmp(frame); v1 > v2 {
		base.Branch(frame, self.Offset)
	}
}

func (self *IF_ICMPGE) Execute(frame *rtda.Frame) {
	if v1, v2 := _icmp(frame); v1 >= v2 {
		base.Branch(frame, self.Offset)
	}
}

func (self *IF_ICMPLE) Execute(frame *rtda.Frame) {
	if v1, v2 := _icmp(frame); v1 <= v2 {
		base.Branch(frame, self.Offset)
	}
}

func (self *IF_ICMPLT) Execute(frame *rtda.Frame) {
	if v1, v2 := _icmp(frame); v1 < v2 {
		base.Branch(frame, self.Offset)
	}
}

func _icmp(frame *rtda.Frame) (v1, v2 int32) {
	stack := frame.OperandStack()

	v2 = stack.PopInt()
	v1 = stack.PopInt()

	return v1, v2
}
