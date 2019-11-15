package rtda

/*
JVM
  Thread
    pc
    Stack
      Frame
        LocalVars
        OperandStack

-Xss 选项设置 Java 虚拟机栈大小
*/
type Thread struct {
	pc    int    // PC 程序计数器用于存储当前正在执行的指令地址
	stack *Stack // Java 虚拟机栈指针
}

func NewThread() *Thread {
	return &Thread{
		stack: newStack(1024), // 栈最多可以容纳 1024 帧
	}
}

func (self *Thread) PC() int {
	return self.pc
}

func (self *Thread) SetPC(pc int) {
	self.pc = pc
}

func (self *Thread) PushFrame(frame *Frame) {
	self.stack.push(frame)
}

func (self *Thread) PopFrame() *Frame {
	return self.stack.pop()
}

func (self *Thread) CurrentFrame() *Frame {
	return self.stack.top()
}

func (self *Thread) NewFrame(maxLocals, maxStack uint) *Frame {
	return newFrame(self, maxLocals, maxStack)
}