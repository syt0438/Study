package classfile

const (
	CONSTANT_Class             = 7
	CONSTANT_Fieldref          = 9
	CONSTANT_Methodref         = 10
	CONSTANT_InterfaceMetodref = 11
	CONSTANT_String            = 8
	CONSTANT_Integer           = 3
	CONSTANT_Float             = 4
	CONSTANT_Long              = 5
	CONSTANT_Double            = 6
	CONSTANT_NameAndType       = 12
	CONSTANT_Utf8              = 1
	CONSTANT_MethodHandle      = 15
	CONSTANT_MethodType        = 16
	CONSTANT_InvokeDynamic     = 18
)

type ConstantInfo interface {
	// 用于读取常量信息，由具体的常量结构体实现
	readInfo(reader *ClassReader)
}

/*
	1. 读取 tag 值，获取常量类型
	2. 调用 newConstantInfo 创建具体的常量
	3. 调用常量的 readInfo 方法读取常量信息
*/
func readConstantInfo(reader *ClassReader, cp ConstantPool) ConstantInfo {
	tag := reader.readUint8()
	c := newConstantInfo(tag, cp)
	c.readInfo(reader)

	return c
}

// 根据 tag 值，创建具体的常量
func newConstantInfo(tag uint8, cp ConstantPool) ConstantInfo {
	switch tag {
	case CONSTANT_Integer:
		return &ConstantIntegerInfo{}
	case CONSTANT_Float:
		return &ConstantFloatInfo{}
	case CONSTANT_Long:
		return &ConstantLongInfo{}
	case CONSTANT_Double:
		return &ConstantDoubleInfo{}
	case CONSTANT_Utf8:
		return &ConstantUtf8Info{}
	case CONSTANT_String:
		return &ConstantStringInfo{cp: cp}
	case CONSTANT_Class:
		return &ConstantClassInfo{cp: cp}
	case CONSTANT_NameAndType:
		return &ConstantNameAndTypeInfo{}
	case CONSTANT_Fieldref:
		return &ConstantFieldrefInfo{ConstantMemberrefInfo{cp: cp}}
	case CONSTANT_Methodref:
		return &ConstantMethodrefInfo{ConstantMemberrefInfo{cp: cp}}
	case CONSTANT_InterfaceMetodref:
		return &ConstantInterfaceMethodrefInfo{ConstantMemberrefInfo{cp: cp}}
	case CONSTANT_MethodType:
		return &ConstantMethodTypeInfo{}
	case CONSTANT_MethodHandle:
		return &ConstantMethodHandleInfo{}
	case CONSTANT_InvokeDynamic:
		return &ConstantInvokeDynamicInfo{}
	default:
		panic("java.lang.ClassFormatError: constant pool tag")
	}
}
