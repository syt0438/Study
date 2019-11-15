package constants

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type NOP struct {
	base.NoOperandsInstruction
}

func (self *NOP) Execute(frame *rtda.Frame) {
	// don't do anything
}
