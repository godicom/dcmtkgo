package main

// #cgo CFLAGS: -I/Users/vladislavtroinich/projects/dcmtkgo/src/cppwrap/
// #cgo LDFLAGS: -l/Users/vladislavtroinich/projects/cppwrap-build/libdcmtkgo.a
// #include "export.h"

import (
	"C"
	"fmt"
)

func main() {
	fmt.Printf("Invoking c library...\n")
	C.doSomeJob()
	fmt.Printf("Done\n")
	fmt.Println("Hello")
}
