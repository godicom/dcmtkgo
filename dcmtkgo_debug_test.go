package dcmtkgo

// Tests for debuging, when they become normal they must be moved to other file
import (
	"fmt"
	//"runtime"
	"testing"
)

//Some dirty test of finalizer
// func TestFinalazier(t *testing.T) {
// 	for i := 0; i < 10; i++ {
// 		ds, err := OpenDataset("test_files/test_sr.dcm")
// 		ds.GetString(SOPInstanceUID)
// 		if err != nil {
// 			t.Fatal(err)
// 		}
// 		runtime.GC()
// 	}
// }

func TestCreateNewDataSet(t *testing.T) {
	ds, err := NewEmptyDataset()
	if err != nil {
		t.Fatal(err)
	}
	err = ds.SetString(PatientID, "New Patient name")
	if err != nil {
		t.Fatal(err)
	}
	err = ds.SaveToFile("/tmp/test.dcm", ExsLittleEndianExplicit)
	if err != nil {
		t.Fatal(err)
	}
	err = ds.CloseDataset()
	if err != nil {
		t.Fatal(err)
	}
}

func TestDebugArray(t *testing.T) {
	ds, err := OpenDataset("test_files/IM-0001-0013.dcm")
	if err != nil {
		t.Fatal(err)
	}

	arr, err := ds.GetUint16Array(0x00181310)
	if err != nil {
		t.Fatal(err)
	}
	for i := range arr {
		fmt.Println(arr[i])
	}

	//fmt.Println(ds.GetString(FrameTimeVector))
}
