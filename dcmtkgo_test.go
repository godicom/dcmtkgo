package dcmtkgo

import (
	"runtime"
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
