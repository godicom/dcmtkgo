package dcmtkgo

//Don't know how to do it yet(may be later with cmake)
//Add for linux(gcc): -lstdc++
//Add for mac(clang): -lc++

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap  -ldcmtkgo -ldcmdata -lz -lofstd -loflog -lstdc++
// #include <export.h>
// #include <stdlib.h>
import "C"
import (
	"fmt"
	//"unsafe"
//	"runtime"
	"errors"
)

// TODO: optimize
func getErrorString(errCtx C.ulong, errId C.int) string {
	var errStr [256]C.char
	C.getError(errCtx, errId, &errStr[0], 256)
	return C.GoString(&errStr[0])
}

type Dataset struct {
	errCtx C.ulong
	dsCtx C.ulong
}

func (ds * Dataset) openDataSet(filename string) error {
	errId := C.makeGetErrorCtx(&ds.errCtx)
	if  errId!= 0 {
		return errors.New("Can't create Error ctx")
	}
	errId = C.openDcmtkDataSet(ds.errCtx, C.CString(filename), &ds.dsCtx)
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds * Dataset) getString(g uint16, e uint16) (string, error) {

	errId := C.testPrintTag(ds.errCtx, ds.dsCtx, C.ushort(g), C.ushort(e))
	if errId != 0 {
		fmt.Println(getErrorString(ds.errCtx, errId))
	}

	return "", nil
}

func closeDataSet(ds * Dataset) error {
	if ds.errCtx == 0 {
		defer C.closeErrorCtx(ds.errCtx)
	}
	
	if ds.dsCtx != 0 {
		var errId C.int = C.closeDcmtkDataSet(ds.errCtx, ds.dsCtx)

		if errId != 0 {
			errorStr := getErrorString(ds.errCtx, errId)
			return errors.New(errorStr)
		}
	}

	return nil
}


func NewDataset() * Dataset {
	ds := Dataset {
		errCtx :0,
		dsCtx: 0}
	// runtime.SetFinalizer(&ds, closeDataSet)
	return &ds
}

func main() {
	// fmt.Printf("Invoking c library...\n")
	// //var errCtx C.ulong = 0
	// var errCtx C.ulong = 0
	// var dsCtx C.ulong = 0
	// path := C.CString("empty")
	// C.makeGetErrorCtx(&errCtx)
	// errId := C.openDcmtkDataSet(errCtx, path, &dsCtx)
	// if errId != 0 {
	// 	printError(errCtx, errId)
	// 	return
	// }

	// //errId = closeDcmtkDataSet(dsCtx, )

	// C.free(unsafe.Pointer(path))

	// //path := "/Users/vladislavtroinich/data/test.dcm"
	// //C.printDCMTags(C.CString(path))
	// fmt.Printf("Done\n")
}
