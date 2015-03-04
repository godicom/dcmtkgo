/*
** VR Enumerations.
** NB: The order of entries has to conform to the order in DcmVRDict (see dcmvr.cc)!
**     If not an error message is reported and the program aborts (only in DEBUG mode).
*/
enum DcmtgoEVR
{
    /// application entity title
    DMGO_AE,
    /// age string
    DMGO_AS,
    /// attribute tag
    DMGO_AT,
    /// code string
    DMGO_CS,
    /// date string
    DMGO_DA,
    /// decimal string
    DMGO_DS,
    /// date time string
    DMGO_DT,
    /// float single-precision
    DMGO_FL,
    /// float double-precision
    DMGO_FD,
    /// integer string
    DMGO_IS,
    /// long string
    DMGO_LO,
    /// long text
    DMGO_LT,
    /// other byte
    DMGO_OB,
    /// other float
    DMGO_OF,
    /// other word
    DMGO_OW,
    /// person name
    DMGO_PN,
    /// short string
    DMGO_SH,
    /// signed long
    DMGO_SL,
    /// sequence of items
    DMGO_SQ,
    /// signed short
    DMGO_SS,
    /// short text
    DMGO_ST,
    /// time string
    DMGO_TM,
    /// unique identifier
    DMGO_UI,
    /// unsigned long
    DMGO_UL,
    /// unsigned short
    DMGO_US,
    /// unlimited text
    DMGO_UT,
    /// OB or OW depending on context
    DMGO_ox,
    /// SS or US depending on context
    DMGO_xs,
    /// US, SS or OW depending on context, used for LUT Data (thus the name)
    DMGO_lt,
    /// na="not applicable", for data which has no VR
    DMGO_na,
    /// up="unsigned pointer", used internally for DICOMDIR suppor
    DMGO_up,
    /// used internally for items
    DMGO_item,
    /// used internally for meta info datasets
    DMGO_metainfo,
    /// used internally for datasets
    DMGO_dataset,
    /// used internally for DICOM files
    DMGO_fileFormat,
    /// used internally for DICOMDIR objects
    DMGO_dicomDir,
    /// used internally for DICOMDIR records
    DMGO_dirRecord,
    /// used internally for pixel sequences in a compressed image
    DMGO_pixelSQ,
    /// used internally for pixel items in a compressed image
    DMGO_pixelItem,
    /// used internally for elements with unknown VR (encoded with 4-byte length field in explicit VR)
    DMGO_UNKNOWN,
    /// unknown value representation
    DMGO_UN,
    /// used internally for uncompressed pixeld data
    DMGO_PixelData,
    /// used internally for overlay data
    DMGO_OverlayData,
    /// used internally for elements with unknown VR with 2-byte length field in explicit VR
    DMGO_UNKNOWN2B
};



void printDCMTags(const char * fileName);



int makeGetErrorCtx(unsigned long * errorCtx);
void closeErrorCtx(unsigned long errorCtx);
int getError(unsigned long errorCtx, int errorId, char * buf, unsigned long bufSize);

int openDcmtkDataSet(unsigned long errorCtx, const char * fileName, unsigned long *rvDataSetCtx);
int testPrintTag(unsigned long errorCtx, unsigned long dataSetCtx, unsigned short g, unsigned short e);
int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx);

