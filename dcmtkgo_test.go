package dcmtkgo

// Rral tests
import (
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

func TestSaveLoadMemory(t *testing.T) {
	ds, err := NewEmptyDataset()
	if err != nil {
		t.Fatal(err)
	}
	cases := []struct {
		tag uint32
		val string
	}{
		{PatientName, "Test^S R"},
		{SOPInstanceUID, "1.2.276.0.7230010.3.1.4.2139363186.7819.982086466.4"},
	}

	for _, c := range cases {
		err := ds.SetString(c.tag, c.val)
		if err != nil {
			t.Error(err)
		}
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
		got, err := ds2.GetString(c.tag)
		if err != nil {
			t.Error(err)
		}
		if got != c.val {
			t.Errorf("Different values expect %s got %s", c.val, got)
		}
	}
}
