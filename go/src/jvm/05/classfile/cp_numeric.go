package classfile

import "math"

type ConstantIntegerInfo struct {
	val int32
}

type ConstantFloatInfo struct {
	val float32
}

type ConstantLongInfo struct {
	val int64
}

type ConstantDoubleInfo struct {
	val float64
}

// 先读取一个 uint32 数据，然后把它转型成 int32 类型
func (self *ConstantIntegerInfo) readInfo(reader *ClassReader) {
	bytes := reader.readUint32()

	self.val = int32(bytes)
}

// 先读取一个 uint32 数据，然后调用 math 包的 Float32frombits（）函数，把它转换成 float32 类型
func (self *ConstantFloatInfo) readInfo(reader *ClassReader) {
	bytes := reader.readUint32()

	self.val = math.Float32frombits(bytes)
}

// 先读取一个 uint64 数据，然后把它转型成 int64 类型
func (self *ConstantLongInfo) readInfo(reader *ClassReader) {
	bytes := reader.readUint64()

	self.val = int64(bytes)
}

// 先读取一个 uint64 数据，然后把它转型成 float64 类型
func (self *ConstantDoubleInfo) readInfo(reader *ClassReader) {
	bytes := reader.readUint64()

	self.val = math.Float64frombits(bytes)
}
