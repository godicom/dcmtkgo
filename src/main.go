package main

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap -lstdc++ -ldcmtkgo -ldcmdata -lz -lofstd -loflog
// #include <export.h>
import "C"
import (
	"fmt"
)
//-lc++

func main() {
	fmt.Printf("Invoking c library...\n")
	path := "/home/antlad/tmp/test.dcm"
	C.printDCMTags(C.CString(path))
	fmt.Printf("Done\n")
}
