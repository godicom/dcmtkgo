package dcmtkgo

//Don't know how to do it yet(may be later with cmake)
//Add for linux(gcc): -lstdc++
//Add for mac(clang): -lc++

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap  -ldcmtkgo -ldcmdata -lz -lofstd -loflog -lstdc++
// #include <export.h>
import "C"
import (
	//"unsafe"
	"errors"
	"runtime"
)

// TODO: optimize
func getErrorString(errCtx C.ulong, errId C.int) string {
	var errStr [256]C.char
	C.getError(errCtx, errId, &errStr[0], 256)
	return C.GoString(&errStr[0])
}

type dataset struct {
	errCtx C.ulong
	dsCtx  C.ulong
}

func (ds *dataset) openDataSet(filename string) error {
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

func (ds *dataset) GetInt32(tag uint32) (int32, error) {
	var value C.int
	errId := C.getSint32(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return int32(value), nil
}

func (ds *dataset) GetUint32(tag uint32) (uint32, error) {
	var value C.uint
	errId := C.getUint32(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return uint32(value), nil
}

func (ds *dataset) GetInt16(tag uint32) (int16, error) {
	var value C.short
	errId := C.getSint16(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return int16(value), nil
}

func (ds *dataset) GetUint16(tag uint32) (uint16, error) {
	var value C.ushort
	errId := C.getUint16(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return uint16(value), nil
}

func (ds *dataset) GetUint8(tag uint32) (uint8, error) {
	var value C.uchar
	errId := C.getUint8(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return uint8(value), nil
}

func (ds *dataset) GetFloat32(tag uint32) (float32, error) {
	var value C.float
	errId := C.getFloat32(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return float32(value), nil
}

func (ds *dataset) GetFloat64(tag uint32) (float64, error) {
	var value C.double
	errId := C.getFloat64(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return float64(value), nil
}

func (ds *dataset) GetString(tag uint32) (string, error) {
	// TODO: do something with this buffer
	var errStr [256]C.char
	errId := C.getString(ds.errCtx, ds.dsCtx, C.uint(tag), &errStr[0], 256)
	if errId != 0 {
		return "", errors.New(getErrorString(ds.errCtx, errId))
	}

	return C.GoString(&errStr[0]), nil
}

func (ds *dataset) CloseDataSet() error {
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

func newDataset() *dataset {
	ds := dataset{
		errCtx: 0,
		dsCtx:  0}
	runtime.SetFinalizer(&ds, (*dataset).CloseDataSet)
	return &ds
}
