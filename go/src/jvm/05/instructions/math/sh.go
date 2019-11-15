package math

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

// int <<
type ISHL struct {
	base.NoOperandsInstruction
}

// long <<
type LSHL struct {
	base.NoOperandsInstruction
}

// int >>
type ISHR struct {
	base.NoOperandsInstruction
}

// long >>
type LSHR struct {
	base.NoOperandsInstruction
}

// int >>>
type IUSHR struct {
	base.NoOperandsInstruction
}

// long >>>
type LUSHR struct {
	base.NoOperandsInstruction
}

func (self *ISHL) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopInt()
	v1 := stack.PopInt()

	operand := uint32(v2) & 0x1F

	result := v1 << operand

	stack.PushInt(result)
}

func (self *LSHL) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopInt()
	v1 := stack.PopLong()

	operand := uint32(v2) & 0x3F

	result := v1 << operand

	stack.PushLong(result)
}

func (self *ISHR) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopInt()
	v1 := stack.PopInt()

	operand := uint32(v2) & 0x1F
	result := v1 >> operand

	stack.PushInt(result)
}

func (self *LSHR) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopInt()
	v1 := stack.PopLong()

	operand := uint32(v2) & 0x3F

	result := v1 >> operand

	stack.PushLong(result)
}

func (self *IUSHR) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopInt()
	v1 := stack.PopInt()

	operand := uint32(v2) & 0x1F

	result := int32(uint32(v1) >> operand)

	stack.PushInt(result)
}

func (self *LUSHR) Execute(frame *rtda.Frame) {
	stack := frame.OperandStack()

	v2 := stack.PopInt()
	v1 := stack.PopLong()

	operand := uint32(v2) & 0x3F

	result := int64(uint64(v1) >> operand)

	stack.PushLong(result)
}
