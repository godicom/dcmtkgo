package dcmtkgo

import (
	"fmt"
	"testing"
)

func BenchmarkDummySumm(b *testing.B) {
	sum := dummySummInLib(2, 3)
	sum = sum + 1
}

func BenchmarkCallGetData(b *testing.B) {
	ds := NewDataset()
	var err error
	err = ds.openDataSet("/Users/vladislavtroinich/data/test.dcm")
	if err != nil {
		b.Fatal(err)
		return
	}
	var val string
	fmt.Println("N = ", b.N)
	for n := 0; n < b.N; n++ {
		val, err = ds.getString(16, 16)
		if err != nil {
			b.Fatal(err)
		}
	}
	fmt.Println(val)
	fmt.Println("Done")

}
