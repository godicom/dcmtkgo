package main

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap -lc++ -ldcmtkgo
// #include <export.h>
import "C"
import (
	"fmt"
)

func main() {
	fmt.Printf("Invoking c library...\n")
	C.doSomeJob()
	fmt.Printf("Done\n")
	fmt.Println("Hello")
}
