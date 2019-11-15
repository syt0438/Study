package base

import "jvm/05/rtda"

func Branch(frame *rtda.Frame, offset int) {
	pc := frame.Thread().PC()

	nextPC := pc + offset

	frame.SetNextPC(nextPC)
}
