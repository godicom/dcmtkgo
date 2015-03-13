package dcmtkgo

// Real tests
import (
	"reflect"
	"testing"
)

func TestGetString(t *testing.T) {
	cases := []struct {
		tag  uint32
		want string
	}{
		{PatientName, "Test^S R"},
		{SOPInstanceUID, "1.2.276.0.7230010.3.1.4.2139363186.7819.982086466.4"},
	}

	ds, err := OpenDataset("test_files/test_sr.dcm")
	if err != nil {
		t.Fatal(err)
	}

	for _, c := range cases {
		got, err := ds.GetString(c.tag)
		if err != nil {
			t.Error(err)
		}

		if got != c.want {
			t.Errorf("Expected %q, got %q", c.want, got)
		}
	}
}

func compareValues(err error, expect interface{}, got interface{}, t *testing.T) {
	if err != nil {
		t.Error(err)
	}
	
	if !reflect.DeepEqual(got, expect) {
		t.Errorf("Expected %q, got %q", expect, got)
	}
}

func loadValueFromDataset(ds Dataset, tag uint32, val interface{}, t *testing.T) {
	var err error
	var got interface{}
	switch v := val.(type) {
	case uint8:
		//err = ds.setUint8????
	case uint16:
		got, err = ds.GetUint16(tag)
		compareValues(err, v, got, t)
	case int16:
		got, err = ds.GetInt16(tag)
		compareValues(err, v, got, t)
	case float32:
		got, err = ds.GetFloat32(tag)
		compareValues(err, v, got, t)
	case float64:
		got, err = ds.GetFloat64(tag)
		compareValues(err, v, got, t)
	case string:
		got, err = ds.GetString(tag)
		compareValues(err, v, got, t)
	case uint32:
		got, err = ds.GetUint32(tag)
		compareValues(err, v, got, t)
	case int32:
		got, err = ds.GetInt32(tag)
		compareValues(err, v, got, t)
	case []uint8:
		got, err = ds.GetUint8Array(tag)
		compareValues(err, v, got, t)
	case []uint16:
		got, err = ds.GetUint16Array(tag)
		compareValues(err, v, got, t)
	case []int16:
		got, err = ds.GetInt16Array(tag)
		compareValues(err, v, got, t)
	case []uint32:
		got, err = ds.GetUint32Array(tag)
		compareValues(err, v, got, t)
	case []int32:
		got, err = ds.GetInt32Array(tag)
		compareValues(err, v, got, t)
	case []float32:
		got, err = ds.GetFloat32Array(tag)
		compareValues(err, v, got, t)
	case []float64:
		got, err = ds.GetFloat64Array(tag)
		compareValues(err, v, got, t)
	default:
		t.Fatal("unknown")
	}
	if err != nil {
		t.Fatal(err)
	}

}

func saveValueToDataset(ds Dataset, tag uint32, val interface{}, t *testing.T) {
	var err error
	switch v := val.(type) {
	case string:
		err = ds.SetString(tag, v)
	case uint8:
		//err = ds.setUint8(tag, v)
	case uint16:
		err = ds.SetUint16(tag, v)
	case int16:
		err = ds.SetInt16(tag, v)
	case uint32:
		err = ds.SetUint32(tag, v)
	case int32:
		err = ds.SetInt32(tag, v)
	case float32:
		err = ds.SetFloat32(tag, v)
	case float64:
		err = ds.SetFloat64(tag, v)
	case []uint8:
		err = ds.SetUint8Array(tag, v)
	case []uint16:
		err = ds.SetUint16Array(tag, v)
	case []int16:
		err = ds.SetInt16Array(tag, v)
	case []uint32:
		err = ds.SetUint32Array(tag, v)
	case []int32:
		err = ds.SetInt32Array(tag, v)
	case []float32:
		err = ds.SetFloat32Array(tag, v)
	case []float64:
		err = ds.SetFloat64Array(tag, v)
	default:
		t.Error("unknown")
	}
	if err != nil {
		t.Error(err)
	}
}

func TestSomeTypes(t *testing.T) {
	ds, err := NewEmptyDataset()
	if err != nil {
		t.Fatal(err)
	}

	cases := []struct {
		tag  uint32
		want interface{}
	}{
		{PatientName, "Test^S R"},
		{SOPInstanceUID, "1.2.276.0.7230010.3.1.4.2139363186.7819.982086466.4"},
		{AcquisitionMatrix,  []uint16{4, 3, 2, 1}},
		//{SOPInstanceUID, uint32(1234)},
	}

	for _, c := range cases {
		saveValueToDataset(ds, c.tag, c.want, t)
	}

	s := make([]uint8, 4000, 4000)
	writtenLen, err := ds.SaveDatasetToMemory(s, ExsLittleEndianImplicit)
	if err != nil {
		t.Fatal(err)
	}

	ds2, err := LoadFromMemory(s[0:writtenLen], ExsLittleEndianImplicit)
	if err != nil {
		t.Fatal(err)
	}

	for _, c := range cases {
		loadValueFromDataset(ds2, c.tag, c.want, t)
	}

}
