package rtda

// 栈帧
type Frame struct {
	lower        *Frame        // 虚拟机栈使用链表结构实现
	localVars    LocalVars     // 保存局部变量表指针
	operandStack *OperandStack // 保存操作数栈指针
	thread       *Thread
	nextPC       int		   //  NextPC 程序计数器用于存储下一步需要执行的指令地址
}

/*
	maxLocals: 最大局部变量表大小
	maxStack: 最大操作数栈深度
*/
func newFrame(thread *Thread, maxLocals, maxStack uint) *Frame {
	return &Frame{
		thread:       thread,
		localVars:    newLocalVars(maxLocals),
		operandStack: newOperandStack(maxStack),
	}
}

func (self *Frame) LocalVars() LocalVars {
	return self.localVars
}

func (self *Frame) OperandStack() *OperandStack {
	return self.operandStack
}

func (self *Frame) Thread() *Thread {
	return self.thread
}

func (self *Frame) NextPC() int {
	return self.nextPC
}

func (self *Frame) SetNextPC(nextPC int) {
	self.nextPC = nextPC
}
