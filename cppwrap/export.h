int makeGetErrorCtx(unsigned long * errorCtx);
void closeErrorCtx(unsigned long errorCtx);
int getError(unsigned long errorCtx, int errorId, char * buf, unsigned long bufSize);

int openDcmtkDataSet(unsigned long errorCtx, const char * fileName, unsigned long *rvDataSetCtx);
int closeDcmtkDataSet(unsigned long errorCtx, unsigned long dataSetCtx);

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
int setUint8(unsigned long errorCtx, unsigned long dataSetCtx, unsigned int g_e, unsigned char value);
