package classfile

import "fmt"

type ClassFile struct {
	magic        uint32
	minorVersion uint16
	majorVersion uint16
	constantPool ConstantPool
	accessFlags  uint16 // 由标志所构成的掩码，用于表示某个类或者接口的访问权限及属性
	thisClass    uint16
	superClass   uint16
	interfaces   []uint16
	fields       []*MemberInfo
	methods      []*MemberInfo
	attributes   []AttributeInfo
}

func Parse(classData []byte) (cf *ClassFile, err error) {
	defer func() {
		if r := recover(); r != nil {
			var ok bool

			err, ok = r.(error)

			if !ok {
				err = fmt.Errorf("%v", r)
			}
		}
	}()

	cr := &ClassReader{classData}
	cf = &ClassFile{}

	cf.read(cr)

	return
}

// read 方法依次调用其他方法解析 class 文件
func (self *ClassFile) read(reader *ClassReader) {
	// 3.2.3
	self.readAndCheckMagic(reader)
	// 3.2.4
	self.readAndCheckVersion(reader)
	// 3.2.4
	self.constantPool = readConstantPool(reader)
	// 3.3
	self.accessFlags = reader.readUint16()
	self.thisClass = reader.readUint16()
	self.superClass = reader.readUint16()
	self.interfaces = reader.readUint16s()
	self.fields = readMembers(reader, self.constantPool)
	// 3.2.8
	self.methods = readMembers(reader, self.constantPool)
	// 3.4
	self.attributes = readAttributes(reader, self.constantPool)
}

/*
	很多文件格式都会规定满足该格式的文件必须以某几个固定字节开头，这几个字节主要起标识作用，叫做魔法值
	Class 文件以 4 字节的 CAFEBABE 开头，Java 虚拟机规定，如果加载的 class 文件不符合要求的格式，Java 虚拟机的实现就需要抛出 java.lang.ClassFormatError 异常

	TODO: 由于还未编写异常机制，占有 panic 代替中止程序的运行
*/
func (self *ClassFile) readAndCheckMagic(reader *ClassReader) {
	magic := reader.readUint32()

	if magic != 0xCAFEBABE {
		panic("java.lang.ClassFormatError: magic!")
	}
}

/*
	仅支持 Java SE 8 的版本范围 45.0 ~ 52.0 的 class 文件
	魔法数之后，就是 class 文件的次版本号和主版本号，都是 u2 类型
	例如：某 class 文件的主版本号是 M，次版本号是 m，那么完整的版本号就可以表示成 "M.m"形式
	注意：次版本号只在 J2SE 1.2 之前用过，从 1.2 开始就没有用了（值都是 0），主版本号在 J2SE 1.2 之前都是 45，从 1.2 开始每次有大的 Java 版本发布，都会加 1
*/
func (self *ClassFile) readAndCheckVersion(reader *ClassReader) {
	self.minorVersion = reader.readUint16()
	self.majorVersion = reader.readUint16()

	switch self.majorVersion {
	// JDK 1.02 ~ JDK 1.1
	case 45:
		return
	// J2SE 1.2 ~ JavaSE 13
	case 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57:
		if self.minorVersion == 0 {
			return
		}
	}

	panic("java.lang.UnsupportedClassVersionError")
}

// 从常量池中查找类名
func (self *ClassFile) ClassName() string {
	return self.constantPool.getClassName(self.thisClass)
}

// 从常量池中查找超类名
func (self *ClassFile) SuperClassName() string {
	if self.superClass > 0 {
		return self.constantPool.getClassName(self.superClass)
	}

	return ""
}

// 从常量池中查找接口名
func (self ClassFile) InterfaceNames() []string {
	interfaceNames := make([]string, len(self.interfaces))

	for i, cpIndex := range self.interfaces {
		interfaceNames[i] = self.constantPool.getClassName(cpIndex)
	}

	return interfaceNames
}

// getter
func (self *ClassFile) MajorVersion() uint16 {
	return self.majorVersion
}

// getter
func (self *ClassFile) MinorVersion() uint16 {
	return self.minorVersion
}

// getter
func (self *ClassFile) ConstantPool() ConstantPool {
	return self.constantPool
}

// getter
func (self *ClassFile) AccessFlags() uint16 {
	return self.accessFlags
}

// getter
func (self *ClassFile) Fields() []*MemberInfo {
	return self.fields
}

// getter
func (self *ClassFile) Methods() []*MemberInfo {
	return self.methods
}
