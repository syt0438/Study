package rtda

type Stack struct {
	maxSize uint   // 定义最大可用容纳多少帧
	size    uint   // 保存栈的当前大小
	_top    *Frame // 保存栈顶帧（活动栈帧）
}

func newStack(maxSize uint) *Stack {
	return &Stack{
		maxSize: maxSize,
	}
}

// 将帧压栈到栈顶
func (self *Stack) push(frame *Frame) {
	if self.size > self.maxSize {
		panic("java.lang.StackOverflowError")
	}

	if self._top != nil {
		frame.lower = self._top
	}

	self._top = frame
	self.size++
}

// 将栈顶帧弹出
func (self *Stack) pop() *Frame {
	if self._top == nil {
		panic("Stack top is empty")
	}

	top := self._top
	self._top = top.lower
	top.lower = nil

	self.size--

	return top
}

func (self *Stack) top() *Frame {
	if self._top == nil {
		panic("Stack top is empty")
	}

	return self._top
}
