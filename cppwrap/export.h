void printDCMTags(const char * fileName);

int makeGetErrorCtx(unsigned long * errorCtx);
void closeErrorCtx(unsigned long errorCtx);
int getError(unsigned long errorCtx, int errorId, char * buf, unsigned long bufSize);

int dummySum(int a, int b);

int openDcmtkDataSet(unsigned long errorCtx, const char * fileName, unsigned long *rvDataSetCtx);
int getString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize);
// int getGetUint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned int * rvValue);
// int getGetSint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, int * rvValue);

// int getGetUint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned short* rvValue);
// int getGetSint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, short* rvValue);

// int getGetUint8(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned char* rvValue);
// int getGetSint8(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char* rvValue);

int testPrintTag(unsigned long errorCtx, unsigned long dataSetCtx, unsigned short g, unsigned short e);
int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx);

