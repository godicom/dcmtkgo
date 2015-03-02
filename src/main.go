package main

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap -lc++ -ldcmtkgo -ldcmdata -lz -lofstd -loflog
// #include <export.h>
import "C"
import (
	"fmt"
)

func main() {
	fmt.Printf("Invoking c library...\n")
	path := "/Users/vladislavtroinich/data/test.dcm"
	C.printDCMTags(C.CString(path))
	fmt.Printf("Done\n")
}
