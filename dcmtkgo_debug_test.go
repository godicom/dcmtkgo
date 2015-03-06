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

func TestDebugArray(t *testing.T) {
	ds, err := OpenDataset("test_files/I_000020.dcm")
	if err != nil {
		t.Fatal(err)
	}
	fmt.Println(ds.GetString(FrameTimeVector))
}
