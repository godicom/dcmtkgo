package dcmtkgo

import (
	"fmt"
	"testing"
)

func TestTimeConsuming(t *testing.T) {
	ds := NewDataset()
	err := ds.openDataSet("/home/antlad/tmp/test.dcm")
	if (err != nil) {
		t.Fatal(err)
	}
	fmt.Println(ds.getString(16, 16))

}

