package main

//Don't know how to do it yet(may be later with cmake)
//Add for linux(gcc): -lstdc++
//Add for mac(clang): -lc++

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap  -ldcmtkgo -ldcmdata -lz -lofstd -loflog -lc++
// #include <export.h>
import "C"
import (
	"fmt"
)

func main() {
	fmt.Printf("Invoking c library...\n")
	//var errCtx C.ulong = 0
	var errCtx C.ulong = 0
	var dsCtx C.ulong = 0
	C.makeGetErrorCtx(&errCtx)
	var errId C.int = C.openDcmtkDataSet(errCtx, "empty", &dsCtx)
	if errId != 0 {
		var errStr [256]C.char
		C.getError(errCtx, errId, &errStr[0], 256)
	}

	//path := "/Users/vladislavtroinich/data/test.dcm"
	//C.printDCMTags(C.CString(path))
	fmt.Printf("Done\n")
}
