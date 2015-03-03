package main

//Don't know how to do it yet(may be later with cmake)
//Add for linux(gcc): -lstdc++
//Add for mac(clang): -lc++

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap  -ldcmtkgo -ldcmdata -lz -lofstd -loflog
// #include <export.h>
import "C"
import (
	"fmt"
)

func main() {
	fmt.Printf("Invoking c library...\n")
	path := "/home/antlad/tmp/test.dcm"
	C.printDCMTags(C.CString(path))
	fmt.Printf("Done\n")
}
