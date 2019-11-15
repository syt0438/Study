package main

import (
	"fmt"
	"jvm/05/classfile"
	"jvm/05/instructions"
	"jvm/05/instructions/base"
	"jvm/05/rtda"
)

func interpret(methodInfo *classfile.MemberInfo) {
	codeAttr := methodInfo.CodeAttribute()
	maxLocals := codeAttr.MaxLocals()
	maxStack := codeAttr.MaxStack()
	bytecode := codeAttr.Code()

	thread := rtda.NewThread()
	frame := thread.NewFrame(maxLocals, maxStack)

	thread.PushFrame(frame)

	defer catchErr(frame)

	loop(thread, bytecode)
}

func loop(thread *rtda.Thread, bytecode []byte) {
	frame := thread.PopFrame()
	reader := &base.BytecodeReader{}

	for {
		pc := frame.NextPC()
		thread.SetPC(pc)

		//region decode
		reader.Reset(bytecode, pc)
		opcode := reader.ReadUint8()

		instruction := instructions.NewInstruction(opcode)
		instruction.FetchOperands(reader)

		frame.SetNextPC(reader.PC())
		//endregion

		//region execute
		fmt.Printf("PC: %2d, Instruction: %T %v\n", pc, instruction, instruction)

		instruction.Execute(frame)
		//endregion
	}
}

func catchErr(frame *rtda.Frame) {
	if r := recover(); r != nil {
		fmt.Printf("LocalVars: %v\n", frame.LocalVars())
		fmt.Printf("OperandStack: %v\n", frame.OperandStack())

		panic(r)
	}
}
