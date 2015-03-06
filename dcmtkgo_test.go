package dcmtkgo

import (
	"fmt"
	"testing"
)

func TestGetString(t *testing.T) {
	ds := NewDataset()
	err := ds.openDataSet("test_files/test_sr.dcm")
	if err != nil {
		t.Fatal(err)
	}

	val, err := ds.getString(0x00100010)
	if err != nil {
		t.Fatal(err)
	}
	
	if val != "Test^S R" {
		t.Fatal("0010,0010 fail")
	}

	val, err = ds.getString(0x00080018)
	if err != nil {
		t.Fatal(err)
	}

	if val != "1.2.276.0.7230010.3.1.4.2139363186.7819.982086466.4" {
		t.Fatal("0008,0018 fail")
	}
	
}

func BenchmarkDummySumm(b *testing.B) {
	sum := dummySummInLib(2, 3)
	sum = sum + 1
}

func BenchmarkCallGetData(b *testing.B) {
	ds := NewDataset()
	var err error
	err = ds.openDataSet("test_files/test_sr.dcm")
	if err != nil {
		b.Fatal(err)
		return
	}
	var val string
	fmt.Println("N = ", b.N)
	for n := 0; n < b.N; n++ {
		val, err = ds.getString(0x00100010)
		if err != nil {
			b.Fatal(err)
		}
	}
	fmt.Println(val)
	fmt.Println("Done")

}
