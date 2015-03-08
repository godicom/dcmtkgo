void printDCMTags(const char * fileName);

int makeGetErrorCtx(unsigned long * errorCtx);
void closeErrorCtx(unsigned long errorCtx);
int getError(unsigned long errorCtx, int errorId, char * buf, unsigned long bufSize);

int dummySum(int a, int b);

int openDcmtkDataSet(unsigned long errorCtx, const char * fileName, unsigned long *rvDataSetCtx);

int getString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize);


int getFloat32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, float * rvValue);
int getFloat64(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, double * rvValue);

int getUint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned int * rvValue);
int getSint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, int * rvValue);

int getUint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned short* rvValue);
int getUint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned short** rvValueArray, unsigned long * rvCount);

int getSint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, short* rvValue);

int getUint8(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned char* rvValue);

int testPrintTag(unsigned long errorCtx, unsigned long dataSetCtx, unsigned short g, unsigned short e);
int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx);

