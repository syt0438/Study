package classfile

type ConstantPool []ConstantInfo

// 用于读取常量池信息
func readConstantPool(reader *ClassReader) ConstantPool {
	// 读取常量池的表头，以获取常量项的数量
	cpCount := int(reader.readUint16())
	cp := make([]ConstantInfo, cpCount)

	// 注意项 1：常量池索引从 1 开始
	for i := 1; i < cpCount; i++ {
		cp[i] = readConstantInfo(reader, cp)

		switch cp[i].(type) {
		// 注意项 3：Long 和 Double 类型的常量占两个位置
		case *ConstantLongInfo, *ConstantDoubleInfo:
			i++
		}
	}

	return cp
}

// 根据索引从常量池中查找常量
func (self ConstantPool) getConstantInfo(index uint16) ConstantInfo {
	if cpInfo := self[index]; cpInfo != nil {
		return cpInfo
	}

	panic("Invalid constant poll index!")
}

// 根据索引从常量池中查找字段或方法的名字和描述符
func (self ConstantPool) getNameAndType(index uint16) (string, string) {
	ntInfo := self.getConstantInfo(index).(*ConstantNameAndTypeInfo)
	name := self.getUtf8(ntInfo.nameIndex)
	_type := self.getUtf8(ntInfo.descriptorIndex)

	return name, _type
}

// 根据索引从常量池中查找类名
func (self ConstantPool) getClassName(index uint16) string {
	classInfo := self.getConstantInfo(index).(*ConstantClassInfo)

	return self.getUtf8(classInfo.nameIndex)
}

// 根据索引从常量池中查找 UTF-8 字符串
func (self ConstantPool) getUtf8(index uint16) string {
	utf8Info := self.getConstantInfo(index).(*ConstantUtf8Info)

	return utf8Info.str
}
