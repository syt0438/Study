package main

import "fmt"

func main() {
	cmd := parseCmd()

	if cmd.versionFlag {
		fmt.Println("version 0.0.1")

		return
	}

	if cmd.helpFlag || cmd.class == "" {
		printUsage()

		return
	}

	startJVM(cmd)
}

func startJVM(cmd *Cmd) {
	fmt.Printf("classpath: %s class: %s args: %v\n", cmd.cpOption, cmd.class, cmd.args)
}
