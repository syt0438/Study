package base

type BytecodeReader struct {
	code []byte // 存放字节码
	pc   int    // 记录读取到了哪个字节
}

func (self *BytecodeReader) Reset(code []byte, pc int) {
	self.code = code
	self.pc = pc
}

func (self *BytecodeReader) PC() int {
	return self.pc
}

func (self *BytecodeReader) ReadUint8() uint8 {
	val := self.code[self.pc]

	self.pc++

	return val
}

func (self *BytecodeReader) ReadInt8() int8 {
	val := self.ReadUint8()

	return int8(val)
}

func (self *BytecodeReader) ReadUint16() uint16 {
	high := uint16(self.ReadUint8())
	low := uint16(self.ReadUint8())

	return (high << 8) | low
}

func (self *BytecodeReader) ReadInt16() int16 {
	val := self.ReadUint16()

	return int16(val)
}

func (self *BytecodeReader) ReadUint32() uint32 {
	high := uint32(self.ReadUint8()) << 24
	middleHigh := uint32(self.ReadUint8()) << 16
	middleLow := uint32(self.ReadUint8()) << 8
	low := uint32(self.ReadUint8())

	return high | middleHigh | middleLow | low
}

func (self *BytecodeReader) ReadInt32() int32 {
	return int32(self.ReadUint32())
}

func (self *BytecodeReader) ReadInt32s(n int32) []int32 {
	s := make([]int32, n)

	for i := range s {
		s[i] = self.ReadInt32()
	}

	return s
}

func (self *BytecodeReader) SkipPadding() {
	for self.pc%4 != 0 {
		self.ReadUint8()
	}
}
