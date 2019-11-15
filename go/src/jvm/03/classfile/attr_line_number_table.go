package classfile

type LineNumberTableEntry struct {
	startPc    uint16
	lineNumber uint16
}

type LineNumberTableAttribute struct {
	lineNumberTable []*LineNumberTableEntry
}

func (self *LineNumberTableAttribute) readInfo(reader *ClassReader) {
	lineNumberTableLength := reader.readUint16()
	lineNumberTable := make([]*LineNumberTableEntry, lineNumberTableLength)

	for i := range lineNumberTable {
		lineNumberTable[i] = &LineNumberTableEntry{
			startPc:    reader.readUint16(),
			lineNumber: reader.readUint16(),
		}
	}

	self.lineNumberTable = lineNumberTable
}
