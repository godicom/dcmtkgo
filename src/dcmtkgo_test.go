package dcmkgo_test

//Don't know how to do it yet(may be later with cmake)
//Add for linux(gcc): -lstdc++
//Add for mac(clang): -lc++

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap  -ldcmtkgo -ldcmdata -lz -lofstd -loflog -lc++
// #include <export.h>
// #include <stdlib.h>
import "C"
import (
	"fmt"
	"testing"
	"unsafe"
)

func printError(errCtx C.ulong, errId C.int) {
	fmt.Println("checking error")
	var errStr [256]C.char
	C.getError(errCtx, errId, &errStr[0], 256)
	fmt.Println(C.GoString(&errStr[0]))
}

func TestHandlesNonExistingItemsTest(t *testing.T) {
	fmt.Printf("Invoking c library...\n")
	//var errCtx C.ulong = 0
	var errCtx C.ulong = 0
	var dsCtx C.ulong = 0
	path := C.CString("empty")
	C.makeGetErrorCtx(&errCtx)
	errId := C.openDcmtkDataSet(errCtx, path, &dsCtx)
	if errId != 0 {
		printError(errCtx, errId)
		return
	}

	//errId = closeDcmtkDataSet(dsCtx, )

	C.free(unsafe.Pointer(path))

	//path := "/Users/vladislavtroinich/data/test.dcm"
	//C.printDCMTags(C.CString(path))
	fmt.Printf("Done\n")
}
