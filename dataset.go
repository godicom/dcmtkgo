package dcmtkgo

type Dataset interface {
	DatasetReader
	DatasetWriter
}

type DatasetReader interface {
	GetInt32(tag uint32) (int32, error)
	GetInt32Array(tag uint32) ([]int32, error)
	GetUint32(tag uint32) (uint32, error)
	GetUint32Array(tag uint32) ([]uint32, error)

	GetInt16(tag uint32) (int16, error)
	GetInt16Array(tag uint32) ([]int16, error)
	GetUint16(tag uint32) (uint16, error)
	GetUint16Array(tag uint32) ([]uint16, error)

	GetUint8(tag uint32) (uint8, error)
	GetUint8Array(tag uint32) ([]uint8, error)

	GetFloat32(tag uint32) (float32, error)
	GetFloat32Array(tag uint32) ([]float32, error)
	GetFloat64(tag uint32) (float64, error)
	GetFloat64Array(tag uint32) ([]float64, error)

	GetString(tag uint32) (string, error)
}

type DatasetWriter interface {
	SetString(tag uint32, value string) error

	SetUint8Array(tag uint32, values []uint8) error

	SetUint16(tag uint32, value uint16) error
	SetUint16Array(tag uint32, values []uint16) error
	SetInt16(tag uint32, value int16) error
	SetInt16Array(tag uint32, value []int16) error

	SetUint32(tag uint32, value uint32) error
	SetUint32Array(tag uint32, values []uint32) error
	SetInt32(tag uint32, value int32) error
	SetInt32Array(tag uint32, values []int32) error

	SetFloat32(tag uint32, value float32) error
	SetFloat32Array(tag uint32, value []float32) error
	SetFloat64(tag uint32, value float64) error
	SetFloat64Array(tag uint32, value []float64) error
}

// Creates Empty data set
func NewDataset() Dataset {
	return newDataset()
}

// Reads dataset from file
func OpenDataset(filename string) (Dataset, error) {
	ds := newDataset()
	err := ds.openDataSet(filename)
	return ds, err
}
