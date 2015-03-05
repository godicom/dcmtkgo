void printDCMTags(const char * fileName);

int makeGetErrorCtx(unsigned long * errorCtx);
void closeErrorCtx(unsigned long errorCtx);
int getError(unsigned long errorCtx, int errorId, char * buf, unsigned long bufSize);

int dummySum(int a, int b);

int openDcmtkDataSet(unsigned long errorCtx, const char * fileName, unsigned long *rvDataSetCtx);
int getString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned short g, unsigned short e, char * buf, int bufSize);
int testPrintTag(unsigned long errorCtx, unsigned long dataSetCtx, unsigned short g, unsigned short e);
int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx);

