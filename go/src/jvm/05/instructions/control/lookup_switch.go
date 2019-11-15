package control

import (
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

type LOOKUP_SWITCH struct {
	defaultOffset int32
	npairs        int32
	matchOffsets  []int32
}

func (self *LOOKUP_SWITCH) FetchOperands(reader *base.BytecodeReader) {
	reader.SkipPadding()

	self.defaultOffset = reader.ReadInt32()
	self.npairs = reader.ReadInt32()
	self.matchOffsets = reader.ReadInt32s(self.npairs * 2)
}

func (self *LOOKUP_SWITCH) Execute(frame *rtda.Frame) {
	caseVal := frame.OperandStack().PopInt()

	for i := int32(0); i < self.npairs*2; i += 2 {
		key := self.matchOffsets[i]

		if caseVal == key {
			offset := self.matchOffsets[i+1]
			base.Branch(frame, int(offset))

			return
		}
	}

	base.Branch(frame, int(self.defaultOffset))
}
