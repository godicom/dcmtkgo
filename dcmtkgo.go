package dcmtkgo

//Don't know how to do it yet(may be later with cmake)
//Add for linux(gcc): -lstdc++
//Add for mac(clang): -lc++

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap  -ldcmtkgo -ldcmdata -lz -lofstd -loflog -lstdc++
// #include <export.h>
import "C"
import (
	//"fmt"
	//"unsafe"
	//	"runtime"
	"errors"
)

var i int

func dummySummInLib(a int, b int) int {
	i = int(C.dummySum(C.int(a+i), C.int(b)))
	return i
}

// TODO: optimize
func getErrorString(errCtx C.ulong, errId C.int) string {
	var errStr [256]C.char
	C.getError(errCtx, errId, &errStr[0], 256)
	return C.GoString(&errStr[0])
}

type Dataset struct {
	errCtx C.ulong
	dsCtx  C.ulong
}

func (ds *Dataset) openDataSet(filename string) error {
	errId := C.makeGetErrorCtx(&ds.errCtx)
	if errId != 0 {
		return errors.New("Can't create Error ctx")
	}
	errId = C.openDcmtkDataSet(ds.errCtx, C.CString(filename), &ds.dsCtx)
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}
func (ds *Dataset) getSint32(g_e uint32) (int32, error) {
	var value C.int
	errId := C.getGetSint32(ds.errCtx, ds.dsCtx, C.uint(g_e), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}

	return int32(value), nil
}

func (ds *Dataset) getUint32(g_e uint32) (uint32, error) {
	var value C.uint
	errId := C.getGetUint32(ds.errCtx, ds.dsCtx, C.uint(g_e), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}

	return uint32(value), nil
}

func (ds *Dataset) getString(g_e uint32) (string, error) {

// TODO: do something with this buffer 
	var errStr [256]C.char
	errId := C.getString(ds.errCtx, ds.dsCtx, C.uint(g_e), &errStr[0], 256)
	if errId != 0 {
		return "", errors.New(getErrorString(ds.errCtx, errId))
	}

	return C.GoString(&errStr[0]), nil
}

func closeDataSet(ds *Dataset) error {
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

func NewDataset() *Dataset {
	ds := Dataset{
		errCtx: 0,
		dsCtx:  0}
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
