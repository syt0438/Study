package control

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type TABLE_SWITCH struct {
	defaultOffset int32
	low           int32
	high          int32
	jumpOffsets   []int32
}

func (self *TABLE_SWITCH) FetchOperands(reader *base.BytecodeReader) {
	reader.SkipPadding()

	self.defaultOffset = reader.ReadInt32()
	self.low = reader.ReadInt32()
	self.high = reader.ReadInt32()

	jumpOffsetCount := self.high - self.low + 1

	self.jumpOffsets = reader.ReadInt32s(jumpOffsetCount)
}

func (self *TABLE_SWITCH) Execute(frame *rtda.Frame) {
	caseVal := frame.OperandStack().PopInt()

	var offset int

	if self.low <= caseVal && caseVal <= self.high {
		index := caseVal - self.low

		offset = int(self.jumpOffsets[index])
	} else {
		offset = int(self.defaultOffset)
	}

	base.Branch(frame, offset)
}
