package dcmtkgo

type Dataset interface {
	GetInt32(tag uint32) (int32, error)
	GetUint32(tag uint32) (uint32, error)

	GetInt16(tag uint32) (int16, error)
	GetUint16(tag uint32) (uint16, error)

	GetUint8(tag uint32) (uint8, error)

	GetFloat32(tag uint32) (float32, error)
	GetFloat64(tag uint32) (float64, error)

	GetString(tag uint32) (string, error)
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
