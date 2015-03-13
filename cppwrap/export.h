int makeGetErrorCtx(unsigned long * errorCtx);
void closeErrorCtx(unsigned long errorCtx);
int getError(unsigned long errorCtx, int errorId, char * buf, unsigned long bufSize);

int getDatasetSize(unsigned long errorCtx, unsigned long dataSetCtx, unsigned long * rvSize);
int dumpDatasetToStdOut(unsigned long errorCtx, unsigned long dataSetCtx);

int createEmptyDcmtkDataset(unsigned long errorCtx, unsigned long *rvDatasetCtx);
int createDatasetFromMemory(unsigned long errorCtx, unsigned long *rvDatasetCtx, const unsigned char * buf, unsigned int bufSize, int transfer);
int openDcmtkDataset(unsigned long errorCtx, const char * fileName, unsigned long *rvDatasetCtx);
int saveDcmtkDataset(unsigned long errorCtx, unsigned long dataSetCtx, const char * fileName, int transfer);
int saveDcmtkDatasetToMemory(unsigned long errorCtx, unsigned long dataSetCtx, unsigned char * buf, unsigned int bufSize, unsigned long *rvWrittenLength, int transfer);
int closeDcmtkDataset(unsigned long errorCtx, unsigned long dataSetCtx);

int getString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize);
int getFloat32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, float * rvValue);
int getFloat64(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, double * rvValue);
int getUint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned int * rvValue);
int getSint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, int * rvValue);
int getUint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned short* rvValue);
int getSint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, short* rvValue);
int getUint8(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned char* rvValue);

int getStringArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize);
int getFloat32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const float** rvValueArray, unsigned long * rvCount);
int getFloat64Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const double** rvValueArray, unsigned long * rvCount);
int getUint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned int** rvValueArray, unsigned long * rvCount);
int getSint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const int** rvValueArray, unsigned long * rvCount);
int getUint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned short** rvValueArray, unsigned long * rvCount);
int getSint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const short** rvValueArray, unsigned long * rvCount);
int getUint8Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned char** rvValueArray, unsigned long * rvCount);

int setString(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize);
int setFloat32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, float value);
int setFloat64(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, double value);
int setUint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned int value);
int setSint32(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, int value);
int setUint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned short value);
int setSint16(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, short value);

int setStringArray(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, char * buf, int bufSize);
int setUint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned short* array, unsigned long length);
int setSint16Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const short* array, unsigned long length);
int setUint8Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned char* array, unsigned long length);
int setFloat32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const float* array, unsigned long length);
int setFloat64Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const double* array, unsigned long length);
int setUint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const unsigned int* array, unsigned long length);
int setSint32Array(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, const int* array, unsigned long length);
