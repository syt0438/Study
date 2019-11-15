package extended

import (
	"jvm/05/instructions/base"
	"jvm/05/instructions/loads"
	"jvm/05/instructions/math"
	"jvm/05/instructions/stores"
	"jvm/05/rtda"
)

type WIDE struct {
	modifiedInstruction base.Instruction
}

func (self *WIDE) FetchOperands(reader *base.BytecodeReader) {
	opcode := reader.ReadUint8()

	switch opcode {
	case 0x15:
		ins := &loads.ILOAD{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x16:
		ins := &loads.LLOAD{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x17:
		ins := &loads.FLOAD{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x18:
		ins := &loads.DLOAD{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x19:
		ins := &loads.ALOAD{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x36:
		ins := &stores.ISTORE{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x37:
		ins := &stores.LSTORE{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x38:
		ins := &stores.FSTORE{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x39:
		ins := &stores.DSTORE{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x3A:
		ins := &stores.ASTORE{}
		ins.Index = uint(reader.ReadUint16())
		self.modifiedInstruction = ins
	case 0x84:
		ins := &math.IINC{}
		ins.Index = uint(reader.ReadUint16())
		ins.Const = int32(reader.ReadInt16())
		self.modifiedInstruction = ins
	case 0xA9:
		panic("Unsupported opcode: 0xA9 (ret)")
	}
}

func (self *WIDE) Execute(frame *rtda.Frame) {
	self.modifiedInstruction.Execute(frame)
}
