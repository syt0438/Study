package classfile

import "encoding/binary"

/*
	字节码文件二进制序列的包装类型
	注意: ClassReader 并没有使用索引记录数据位置，而是使用 Go 语言的 reslice 语法跳过已经读取的数据
*/
type ClassReader struct {
	data []byte
}

// u1
func (self *ClassReader) readUint8() uint8 {
	val := self.data[0]

	self.data = self.data[1:]

	return val
}

// u2
func (self *ClassReader) readUint16() uint16 {
	val := binary.BigEndian.Uint16(self.data)

	self.data = self.data[2:]

	return val
}

// u4
func (self *ClassReader) readUint32() uint32 {
	val := binary.BigEndian.Uint32(self.data)

	self.data = self.data[4:]

	return val
}

// u8
func (self *ClassReader) readUint64() uint64 {
	val := binary.BigEndian.Uint64(self.data)

	self.data = self.data[8:]

	return val
}

/*
	读取 uint16 数据表，表的大小由表头的 uint16 数据指出
	注意: 相同类型的多条数据一般按表 table 的形式存储在 class 文件中，表由表头和表项 item 构成，表头是 u2 或 u4 的整数。假设表头是n，后面就紧跟着 n 个表项数据
*/
func (self *ClassReader) readUint16s() []uint16 {
	n := self.readUint16()
	s := make([]uint16, n)

	for i := range s {
		s[i] = self.readUint16()
	}

	return s
}

// 读取指定数量的字节序列
func (self *ClassReader) readBytes(n uint32) []byte {
	bytes := self.data[:n]

	self.data = self.data[n:]

	return bytes
}
