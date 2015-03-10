package dcmtkgo

//Don't know how to do it yet(may be later with cmake)
//Add for linux(gcc): -lstdc++
//Add for mac(clang): -lc++

// #cgo CFLAGS: -I./cppwrap
// #cgo LDFLAGS: -L./cppwrap  -ldcmtkgo -ldcmdata -lz -lofstd -loflog -lstdc++
// #include <export.h>
import "C"
import (
	"errors"
	"reflect"
	"runtime"
	"unsafe"
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

func (ds *dataset) GetInt32Array(tag uint32) ([]int32, error) {
	var array *C.int
	var length C.ulong
	errId := C.getSint32Array(ds.errCtx, ds.dsCtx, C.uint(tag), &array, &length)
	if errId != 0 {
		return nil, errors.New(getErrorString(ds.errCtx, errId))
	}
	return *(*[]int32)(makeSliceForArray(unsafe.Pointer(array), int(length))), nil
}

func (ds *dataset) GetUint32(tag uint32) (uint32, error) {
	var value C.uint
	errId := C.getUint32(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return uint32(value), nil
}

func makeSliceForArray(ptr unsafe.Pointer, length int) unsafe.Pointer {
	hdr := reflect.SliceHeader{
		Data: uintptr(ptr),
		Len:  length,
		Cap:  length,
	}
	return unsafe.Pointer(&hdr)
}

func (ds *dataset) GetUint32Array(tag uint32) ([]uint32, error) {
	var array *C.uint
	var length C.ulong
	errId := C.getUint32Array(ds.errCtx, ds.dsCtx, C.uint(tag), &array, &length)
	if errId != 0 {
		return nil, errors.New(getErrorString(ds.errCtx, errId))
	}
	return *(*[]uint32)(makeSliceForArray(unsafe.Pointer(array), int(length))), nil
}

func (ds *dataset) GetInt16(tag uint32) (int16, error) {
	var value C.short
	errId := C.getSint16(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return int16(value), nil
}

func (ds *dataset) GetInt16Array(tag uint32) ([]int16, error) {
	var array *C.short
	var length C.ulong
	errId := C.getSint16Array(ds.errCtx, ds.dsCtx, C.uint(tag), &array, &length)
	if errId != 0 {
		return nil, errors.New(getErrorString(ds.errCtx, errId))
	}
	return *(*[]int16)(makeSliceForArray(unsafe.Pointer(array), int(length))), nil
}

func (ds *dataset) GetUint16(tag uint32) (uint16, error) {
	var value C.ushort
	errId := C.getUint16(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return uint16(value), nil
}

func (ds *dataset) GetUint16Array(tag uint32) ([]uint16, error) {
	var array *C.ushort
	var length C.ulong
	errId := C.getUint16Array(ds.errCtx, ds.dsCtx, C.uint(tag), &array, &length)
	if errId != 0 {
		return nil, errors.New(getErrorString(ds.errCtx, errId))
	}
	return *(*[]uint16)(makeSliceForArray(unsafe.Pointer(array), int(length))), nil
}

func (ds *dataset) GetUint8(tag uint32) (uint8, error) {
	var value C.uchar
	errId := C.getUint8(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return uint8(value), nil
}

func (ds *dataset) GetUint8Array(tag uint32) ([]uint8, error) {
	var array *C.uchar
	var length C.ulong
	errId := C.getUint8Array(ds.errCtx, ds.dsCtx, C.uint(tag), &array, &length)
	if errId != 0 {
		return nil, errors.New(getErrorString(ds.errCtx, errId))
	}
	return *(*[]uint8)(makeSliceForArray(unsafe.Pointer(array), int(length))), nil
}

func (ds *dataset) GetFloat32(tag uint32) (float32, error) {
	var value C.float
	errId := C.getFloat32(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return float32(value), nil
}

func (ds *dataset) GetFloat32Array(tag uint32) ([]float32, error) {
	var array *C.float
	var length C.ulong
	errId := C.getFloat32Array(ds.errCtx, ds.dsCtx, C.uint(tag), &array, &length)
	if errId != 0 {
		return nil, errors.New(getErrorString(ds.errCtx, errId))
	}
	return *(*[]float32)(makeSliceForArray(unsafe.Pointer(array), int(length))), nil
}

func (ds *dataset) GetFloat64(tag uint32) (float64, error) {
	var value C.double
	errId := C.getFloat64(ds.errCtx, ds.dsCtx, C.uint(tag), &value)
	if errId != 0 {
		return 0, errors.New(getErrorString(ds.errCtx, errId))
	}
	return float64(value), nil
}

func (ds *dataset) GetFloat64Array(tag uint32) ([]float64, error) {
	var array *C.double
	var length C.ulong
	errId := C.getFloat64Array(ds.errCtx, ds.dsCtx, C.uint(tag), &array, &length)
	if errId != 0 {
		return nil, errors.New(getErrorString(ds.errCtx, errId))
	}
	return *(*[]float64)(makeSliceForArray(unsafe.Pointer(array), int(length))), nil
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

func (ds *dataset) SetString(tag uint32, value string) error {
	errId := C.setString(ds.errCtx, ds.dsCtx, C.uint(tag), C.CString(value), C.int(len(value)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetUint8Array(tag uint32, values []uint8) error {
	errId := C.setUint8Array(ds.errCtx, ds.dsCtx, C.uint(tag), (*C.uchar)(unsafe.Pointer(&values)), C.ulong(len(values)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetUint16(tag uint32, value uint16) error {
	errId := C.setUint16(ds.errCtx, ds.dsCtx, C.uint(tag), C.ushort(value))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetUint16Array(tag uint32, values []uint16) error {
	errId := C.setUint16Array(ds.errCtx, ds.dsCtx, C.uint(tag), (*C.ushort)(unsafe.Pointer(&values)), C.ulong(len(values)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetInt16(tag uint32, value int16) error {
	errId := C.setSint16(ds.errCtx, ds.dsCtx, C.uint(tag), C.short(value))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetInt16Array(tag uint32, values []int16) error {
	errId := C.setSint16Array(ds.errCtx, ds.dsCtx, C.uint(tag), (*C.short)(unsafe.Pointer(&values)), C.ulong(len(values)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetUint32(tag uint32, value uint32) error {
	errId := C.setUint32(ds.errCtx, ds.dsCtx, C.uint(tag), C.uint(value))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetUint32Array(tag uint32, values []uint32) error {
	errId := C.setUint32Array(ds.errCtx, ds.dsCtx, C.uint(tag), (*C.uint)(unsafe.Pointer(&values)), C.ulong(len(values)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetInt32(tag uint32, value int32) error {
	errId := C.setSint32(ds.errCtx, ds.dsCtx, C.uint(tag), C.int(value))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetInt32Array(tag uint32, values []int32) error {
	errId := C.setSint32Array(ds.errCtx, ds.dsCtx, C.uint(tag), (*C.int)(unsafe.Pointer(&values)), C.ulong(len(values)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetFloat32(tag uint32, value float32) error {
	errId := C.setFloat32(ds.errCtx, ds.dsCtx, C.uint(tag), C.float(value))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetFloat32Array(tag uint32, values []float32) error {
	errId := C.setFloat32Array(ds.errCtx, ds.dsCtx, C.uint(tag), (*C.float)(unsafe.Pointer(&values)), C.ulong(len(values)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetFloat64(tag uint32, value float64) error {
	errId := C.setFloat64(ds.errCtx, ds.dsCtx, C.uint(tag), C.double(value))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) SetFloat64Array(tag uint32, values []float64) error {
	errId := C.setFloat64Array(ds.errCtx, ds.dsCtx, C.uint(tag), (*C.double)(unsafe.Pointer(&values)), C.ulong(len(values)))
	if errId != 0 {
		return errors.New(getErrorString(ds.errCtx, errId))
	}
	return nil
}

func (ds *dataset) CloseDataset() error {
	if ds.errCtx == 0 {
		defer C.closeErrorCtx(ds.errCtx) // TODO: what to do if it fail?
	}
	if ds.dsCtx != 0 {
		var errId C.int = C.closeDcmtkDataSet(ds.errCtx, ds.dsCtx)

		if errId != 0 {
			return errors.New(getErrorString(ds.errCtx, errId))
		}
	}
	return nil
}

func newDataset() *dataset {
	ds := &dataset{
		errCtx: 0,
		dsCtx:  0}
	runtime.SetFinalizer(ds, (*dataset).CloseDataset)
	return ds
}
