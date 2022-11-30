#ifndef IM_RGB_H
#define IM_RGB_H

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN64_
#define IM_CPU64
#endif

#ifdef __x86_64__
#ifndef IM_CPU64
#define IM_CPU64
#endif
#endif


#define PPM_LEN_OUTPUT (0)
#define IM_BIT_DEPTH (10)

#if IM_BIT_DEPTH == 10
typedef unsigned int ImImage;
#else
typedef unsigned char ImImage;
#endif

#define IM_TYPE_FLAG (1) // 1=bmp, 0=ppm

#define IM_BIT_SHIFT (11)


typedef struct _IM_RGB{
		int iSizeX;
		int iSizeY;
		ImImage *R;
		ImImage *B;
		ImImage *G;
} IM_RGB;




void imInit();

IM_RGB* imMalloc( int iSizeX, int iSizeY );
IM_RGB* imFree( IM_RGB* pimRGB );



/*****************************************************************************/

typedef struct tagBITMAPFILEHEADER {
  unsigned short bfType;         //2
  unsigned int   bfSize;         //4
  unsigned short bfReserved1;    //2
  unsigned short bfReserved2;    //2 
  unsigned int   bfOffBits;      //4
} BITMAPFILEHEADER;
typedef struct tagBITMAPCOREHEADER{
    unsigned int   bcSize;       //4
    short          bcWidth;      //2
    short          bcHeight;     //2
    unsigned short bcPlanes;     //2
    unsigned short bcBitCount;   //2
} BITMAPCOREHEADER;
typedef struct tagBITMAPINFOHEADER{
    unsigned int   biSize;         // 4
    int            biWidth;        // 4
    int            biHeight;       // 4
    unsigned short biPlanes;       // 2
    unsigned short biBitCount;     // 2 
    unsigned int   biCompression;  // 4
    unsigned int   biSizeImage;    // 4
    int            biXPixPerMeter; // 4
    int            biYPixPerMeter; // 4
    unsigned int   biClrUsed;      // 4
    unsigned int   biClrImporant;  // 4
} BITMAPINFOHEADER;
#define IM_BMP_SIZEOF_BxSIZE       sizeof(unsigned int  )

#define IM_BMP_SIZEOF_BF (2+4+2+2+4)
#define IM_BMP_SIZEOF_BF (2+4+2+2+4)

#define IM_BMP_SIZEOF_BC           (4+2+2+2+2)
#define IM_BMP_SIZEOF_BC_WO_BCSIZE (IM_BMP_SIZEOF_BC-IM_BMP_SIZEOF_BxSIZE)
#define IM_BMP_SIZEOF_BI (4+4+4+2+2+4+4+4+4+4+4)
#define IM_BMP_SIZEOF_BI_WO_BISIZE (IM_BMP_SIZEOF_BI-IM_BMP_SIZEOF_BxSIZE)

/*****************************************************************************/
#if 0 //Debug mode 
#define _IM_DISP_SIZE_OF(TYP,STR,MEMB) \
 printf(#TYP"."#MEMB" = %d\n",sizeof(STR.MEMB))

#define _IM_BUF2MEM(TYP,MEM,BUF,IDX) \
(MEM)=(TYP)(*((TYP*)(&((BUF)[(IDX)]))));(IDX)+=sizeof(MEM) ;\
printf(#MEM"\t:%d\n",MEM)


#define _IM_MEM2BUF(TYP,MEM,BUF,IDX) \
memcpy( &((BUF)[(IDX)]), &(MEM), sizeof(TYP) );(IDX)+=sizeof(MEM) ;\
printf(#MEM"\t:%d\n",MEM)

#else //Debug mode
#define _IM_DISP_SIZE_OF(TYP,STR,MEMB) 

#define _IM_BUF2MEM(TYP,MEM,BUF,IDX) \
(MEM)=(TYP)(*((TYP*)(&((BUF)[(IDX)]))));(IDX)+=sizeof(MEM) 

#define _IM_MEM2BUF(TYP,MEM,BUF,IDX) \
memcpy( &((BUF)[(IDX)]), &(MEM), sizeof(TYP) );(IDX)+=sizeof(MEM) 

#endif //Debug mode

void imDispErrMessage2stderr( char *strErrMsg );

extern void (*imErrMessageHandle)(char *str);

#define IM_BMP_BUF_SIZE (1024)

int imReadBmpHeader( char *strFileName, FILE **fpp,
    BITMAPFILEHEADER* pbfh,
    BITMAPCOREHEADER* pbch,
    BITMAPINFOHEADER* pbih);
int imBmpReadBody( IM_RGB* pimRGB, FILE *fp, char* strFileName, 
    BITMAPFILEHEADER* pbfh,
    BITMAPCOREHEADER* pbch,
    BITMAPINFOHEADER* pbih);
int imBmpReadAgain( IM_RGB* pimDST, char *strFileName );
IM_RGB* imBmpRead( char *strFileName );
int imReadAgain( IM_RGB* pimDST, char *strFileName );

int imBmpWrite( IM_RGB* pimRGB, char* strFileName );

void imClear(IM_RGB *pimRGB);
IM_RGB* imRead( char *strFileName );
int imWrite( IM_RGB* pimRGB, char *strFileName );
void imCopy(IM_RGB* pimDST, IM_RGB* pimSRC);
void imSwap(IM_RGB** ppimA, IM_RGB** ppimB);
int  imHalfSynth(IM_RGB* pimDst, IM_RGB* pimLeft,IM_RGB* pimRight);

int imIsSameSize(IM_RGB* pimA, IM_RGB* pimB);

/****************************************************/
// BasicGraphicProcedure
/****************************************************/
extern int im_cfRGB2YCC[3][4];
extern int im_cfYCC2RGB[3][4];

void imXXX2YYY( IM_RGB *pimYYY, IM_RGB *pimXXX, int fMatrix[3][4], int X2Y_flag );
void imRGB2YCC( IM_RGB *pimYCC, IM_RGB *pimRGB );
void imYCC2RGB( IM_RGB *pimRGB, IM_RGB *pimYCC );



void CSVwrite(IM_RGB *pimRGB,char *strFileName);

IM_RGB* imPPMread( char *strFileName );
int imPPMwrite( IM_RGB* pimRGB, char* strFileNameorg, char* strFileNamedst);

IM_RGB* imPread( char *strFileName );
int imPwrite( IM_RGB* pimRGB, char* strFileNameorg, char* strFileNamedst );

int imPPMconvert( IM_RGB* pimRGB, char* strOutputFileName );
int PPMconvert( IM_RGB* pimRGB, char* strOutputFileName );

#endif // IM_RGB_H
