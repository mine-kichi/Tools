#include "ImRGB.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#define MN_MODE (1)

////////////////////////////////////////////////////////////////////////
void (*imErrMessageHandle)(char *str)=imDispErrMessage2stderr;

#if 0 //Limited Range 16-235
double im_cfRGB2YCC[3][4]=
//  R'      G'      B'     Offset
{{  0.257,  0.504,  0.098,  16.0 },  //R
{ -0.148, -0.291,  0.439, 128.0 },  //G
{  0.439, -0.368, -0.071, 128.0 }}; //B

double im_cfYCC2RGB[3][4]=
//  Y       Cb      Cr       Offset
{{  1.164,  0.000,  1.596, (1.164*-16.0)                +( 1.596*-128.0)},
{  1.164, -0.392, -0.813, (1.164*-16.0)+(-0.392*-128.0)+(-0.813*-128.0)},
{  1.164,  2.017,  0.000, (1.164*-16.0)+( 2.017*-128.0)                }};
//double im_cfRGB2YCC[3][4]=
//    //  R'      G'      B'     Offset
//{{  0.299,  0.587,  0.114,   0.0 },  //R
// { -0.169, -0.331,  0.500, 128.0 },  //G
// {  0.500, -0.419, -0.081, 128.0 }}; //B

//double im_cfYCC2RGB[3][4]=
//    //  Y       Cb      Cr       Offset
//{{  1.000,  0.000,  1.402, (1.000*- 0.0)                +( 1.402*-128.0)},
// {  1.000, -0.344, -0.714, (1.000*- 0.0)+(-0.344*-128.0)+(-0.714*-128.0)},
// {  1.000,  1.772,  0.000, (1.000*- 0.0)+( 1.772*-128.0)                }};
#else //FullRange 0-255
int im_cfYCC2RGB[3][4]=
{{  2048,     0,  2870,  0},//Y
{  2048,  -703, -1463,  0},//U
{  2048,  3630,     0,  0}};//V
int im_cfRGB2YCC[3][4]=
{{   613,  1202,   233,         0 },//R
{  -346,  -678,  1024,			0 },//G
{  1024,  -858,  -166,			0 }};//B
#endif

/**
* Initialize for using Basic Image Read/Write libray.
*/
void imInit(){	

	imErrMessageHandle=imDispErrMessage2stderr;
	/*
	BITMAPFILEHEADER bf;
	BITMAPCOREHEADER bc;
	BITMAPINFOHEADER bi;	

	_IM_DISP_SIZE_OF(BITMAPFILEHEADER,bf,bfType);         //2
	_IM_DISP_SIZE_OF(BITMAPFILEHEADER,bf,bfSize);         //4
	_IM_DISP_SIZE_OF(BITMAPFILEHEADER,bf,bfReserved1);    //2
	_IM_DISP_SIZE_OF(BITMAPFILEHEADER,bf,bfReserved2);    //2 
	_IM_DISP_SIZE_OF(BITMAPFILEHEADER,bf,bfOffBits);      //4

	_IM_DISP_SIZE_OF(BITMAPCOREHEADER,bc,bcSize);       //4
	_IM_DISP_SIZE_OF(BITMAPCOREHEADER,bc,bcWidth);      //2
	_IM_DISP_SIZE_OF(BITMAPCOREHEADER,bc,bcHeight);     //2
	_IM_DISP_SIZE_OF(BITMAPCOREHEADER,bc,bcPlanes);     //2
	_IM_DISP_SIZE_OF(BITMAPCOREHEADER,bc,bcBitCount);   //2


	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biSize);         // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biWidth);        // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biHeight);       // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biPlanes);       // 2
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biBitCount);     // 2 
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biCompression);  // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biSizeImage);    // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biXPixPerMeter); // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biYPixPerMeter); // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biClrUsed);      // 4
	_IM_DISP_SIZE_OF(BITMAPINFOHEADER,bi,biClrImporant);  // 4
	*/
}

/**
* Memory Allocation for IM_RGB structure
* \param  iSizeX is Image Width  ( X )
* \param  iSizeX is Image Height ( Y )
* \return Allocated pointer of IM_RGB
*/
IM_RGB* imMalloc( int iSizeX, int iSizeY ){

	IM_RGB* pimRGB;
	int iSize ;	

	pimRGB =(IM_RGB*)malloc(sizeof(IM_RGB));

	pimRGB->iSizeX=iSizeX;
	pimRGB->iSizeY=iSizeY;

	iSize = pimRGB->iSizeX*pimRGB->iSizeY;

	pimRGB->R = (ImImage *)malloc(sizeof(ImImage)*iSize);
	pimRGB->G = (ImImage *)malloc(sizeof(ImImage)*iSize);
	pimRGB->B = (ImImage *)malloc(sizeof(ImImage)*iSize);

	return pimRGB;
}

/**
* Memory Release for IM_RGB structure
* \param  pimRGB is pointer of IM_RGB structure which allocated by imMalloc
* \return pointer of IM_RGB ( NULL pointer )
*/
IM_RGB* imFree( IM_RGB* pimRGB ){
	if( pimRGB != NULL ){
		free(pimRGB->R);
		free(pimRGB->G);
		free(pimRGB->B);
		free(pimRGB);
	}
	return pimRGB;
}



/*****************************************************************************/
/**
* Display the error message to stderr
* \param  strErrMsg is a pointer of error message strings 
*/
void imDispErrMessage2stderr( char *strErrMsg ){
	fprintf( stderr, strErrMsg );
}
#ifndef IM_BMP_BUF_SIZE
#define IM_BMP_BUF_SIZE (1024)
#endif

/*****************************************************************************/
/**
Read Header of Bitmap 
*/
int imReadBmpHeader( char *strFileName, FILE **fpp,
					BITMAPFILEHEADER* pbfh,
					BITMAPCOREHEADER* pbch,
					BITMAPINFOHEADER* pbih){

						int idx=0;

						int iVerticalStep;
						unsigned long bxSize;

						char strErrMsg [IM_BMP_BUF_SIZE];
						char strReadBuf[IM_BMP_BUF_SIZE];

						if( (*fpp=fopen(strFileName,"rb"))==NULL ){
							sprintf( strErrMsg, "imBmpReadHeader:File Open Error: %s\n", strFileName );
							imErrMessageHandle(strErrMsg);
							return -1;
						}
						/* Read Bitmap HEADER -------------------------------------------*/
						fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BF,(size_t)1,*fpp);
						idx = 0;
						_IM_BUF2MEM( unsigned short ,pbfh->bfType     ,strReadBuf,idx);    //2
						_IM_BUF2MEM( unsigned int   ,pbfh->bfSize     ,strReadBuf,idx);    //4
						_IM_BUF2MEM( unsigned short ,pbfh->bfReserved1,strReadBuf,idx);    //2
						_IM_BUF2MEM( unsigned short ,pbfh->bfReserved2,strReadBuf,idx);    //2 
						_IM_BUF2MEM( unsigned int   ,pbfh->bfOffBits  ,strReadBuf,idx);    //4

						fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BxSIZE,(size_t)1,*fpp);
						idx=0;
						_IM_BUF2MEM( unsigned int   ,bxSize          ,strReadBuf,idx);  //4

						if       ( bxSize == 40 ){ // Windows bitmap
							fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BI_WO_BISIZE,(size_t)1,*fpp);
							idx = 0;
							pbih->biSize = bxSize;
							_IM_BUF2MEM( int            ,pbih->biWidth        ,strReadBuf,idx);  // 4
							_IM_BUF2MEM( int            ,pbih->biHeight       ,strReadBuf,idx);  // 4
							_IM_BUF2MEM( unsigned short ,pbih->biPlanes       ,strReadBuf,idx);  // 2
							_IM_BUF2MEM( unsigned short ,pbih->biBitCount     ,strReadBuf,idx);  // 2 
							_IM_BUF2MEM( unsigned int   ,pbih->biCompression  ,strReadBuf,idx);  // 4
							_IM_BUF2MEM( unsigned int   ,pbih->biSizeImage    ,strReadBuf,idx);  // 4
							_IM_BUF2MEM( int            ,pbih->biXPixPerMeter ,strReadBuf,idx);  // 4
							_IM_BUF2MEM( int            ,pbih->biYPixPerMeter ,strReadBuf,idx);  // 4
							_IM_BUF2MEM( unsigned int   ,pbih->biClrUsed      ,strReadBuf,idx);  // 4
							_IM_BUF2MEM( unsigned int   ,pbih->biClrImporant  ,strReadBuf,idx);  // 4
						}else if ( bxSize == 12 ){ // OS/2 bitmap
							fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BC_WO_BCSIZE,(size_t)1,*fpp);
							idx = 0;
							pbch->bcSize = bxSize;
							_IM_BUF2MEM( short          ,pbch->bcWidth    ,strReadBuf,idx);   //2
							_IM_BUF2MEM( short          ,pbch->bcHeight   ,strReadBuf,idx);   //2
							_IM_BUF2MEM( unsigned short ,pbch->bcPlanes   ,strReadBuf,idx);   //2
							_IM_BUF2MEM( unsigned short ,pbch->bcBitCount ,strReadBuf,idx);   //2
							sprintf( strErrMsg, "imBmpReadHeader:File Open Error (Imcompatible BMP): %s\n", strFileName );
							imErrMessageHandle(strErrMsg);
							fclose(*fpp);
							return -1;
						}else{
							sprintf( strErrMsg, "imBmpReadHeader:File Open Error (Bloaken File?): %s(bxSize=%ld)\n", strFileName,bxSize );
							imErrMessageHandle(strErrMsg);
							fclose(*fpp);
							return -1;
						}
						/* Jadge Readable -------------------------------------------------*/
						if( pbih->biPlanes      !=1  ||
							(pbih->biBitCount    !=24 && pbih->biBitCount    !=32 ) ||
							pbih->biCompression !=0     ){
								sprintf( strErrMsg, "imBmpReadHeader:File Open Error (Imcompatible BMP): %s\n", strFileName );
								imErrMessageHandle(strErrMsg);
								fclose(*fpp);
								return -1;
						}

						iVerticalStep=(int)(4*ceil(pbih->biWidth * (pbih->biBitCount/8) /4.0));
						if( pbih->biHeight * iVerticalStep != pbih->biSizeImage ){
							sprintf( strErrMsg, "imBmpReadHeader:File Open Error (Illigal file size): %s\n", strFileName );
							imErrMessageHandle(strErrMsg);
							fclose(*fpp);
							return -1;
						}
						return 0;

}

/*****************************************************************************/
/**
* Read Body of Bitmap 
*/

int imBmpReadBody( IM_RGB* pimRGB, FILE *fp, char* strFileName, 
				  BITMAPFILEHEADER* pbfh,
				  BITMAPCOREHEADER* pbch,
				  BITMAPINFOHEADER* pbih){

					  unsigned char* pBmpData;
					  char strErrMsg [IM_BMP_BUF_SIZE];

					  int bmp_idx;
					  int im_idx;
					  int iVerticalStep;
					  int y, x;
					  int ret;

					  if( (pBmpData=(unsigned char*)malloc( pbih->biSizeImage ))==NULL ){
						  sprintf( strErrMsg, "imBmpReadBody:Memory Allocation Error: %s\n", strFileName );
						  imErrMessageHandle(strErrMsg);
						  fclose(fp);
						  return -1;
					  }

					  /* Read Data -------------------------------------------*/
					  ret=fread(pBmpData,(size_t)sizeof(char),(size_t)pbih->biSizeImage,fp );
					  if( ret != pbih->biSizeImage ){
						  sprintf( strErrMsg, "imBmpReadBody:Readable data is not enough: %s\n", strFileName );
						  imErrMessageHandle(strErrMsg);
						  fclose(fp);
						  return -1;
					  }

					  /* Copy Data -------------------------------------------*/
					  bmp_idx=0;
					  im_idx =0;
					  iVerticalStep=(int)(4*ceil(pbih->biWidth * (pbih->biBitCount/8) /4.0));

					  for( y=0; y<pbih->biHeight; y++ ){
						  bmp_idx = (pbih->biHeight-y-1)*iVerticalStep ;
						  for( x=0; x<pbih->biWidth; x++ ){
							  pimRGB->B[im_idx] = pBmpData[bmp_idx+0];
							  pimRGB->G[im_idx] = pBmpData[bmp_idx+1];
							  pimRGB->R[im_idx] = pBmpData[bmp_idx+2];
							  bmp_idx +=3 ;
							  im_idx  ++  ;
							  if( pbih->biBitCount==32 ){
								  bmp_idx ++ ;
							  }
						  }
					  }  

					  fclose(fp);
					  free(pBmpData);
					  return 0;
}

/*****************************************************************************/
/**
* Read Bitmap w/o memory allocation
*/
int imBmpReadAgain( IM_RGB* pimDST, char *strFileName ){

	BITMAPFILEHEADER bfh;
	BITMAPCOREHEADER bch;
	BITMAPINFOHEADER bih;
	FILE *fp;
	char strErrMsg[IM_BMP_BUF_SIZE];

	//Pointer Check
	if( pimDST==NULL ){
		sprintf( strErrMsg, "imBmpReadAgain:pimDST is NULL pointer\n" );
		imErrMessageHandle(strErrMsg);
		return -1;
	}

	//Read Header 
	if( imReadBmpHeader( strFileName, &fp, &bfh, &bch, &bih ) ){
		return -1;
	}

	//Size Check
	if( (pimDST->iSizeX!=bih.biWidth) || (pimDST->iSizeY!=bih.biHeight) ){
		sprintf( strErrMsg, "imBmpReadAgain:Incompatible size: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		fclose(fp);
		return -1;
	}


	//Read Body
	if( imBmpReadBody( pimDST, fp, strFileName, &bfh, &bch, &bih ) ){
		return -1;
	}
	return 0;
}


/*****************************************************************************/
/**
* Read Bitmap w/o memory allocation
*/
IM_RGB* imBmpRead2( char *strFileName ){

	IM_RGB* pimRGB;

	BITMAPFILEHEADER bfh;
	BITMAPCOREHEADER bch;
	BITMAPINFOHEADER bih;
	FILE *fp;
	char strErrMsg[IM_BMP_BUF_SIZE];
	//Read Header 
	if( imReadBmpHeader( strFileName, &fp, &bfh, &bch, &bih ) ){
		return NULL;
	}

	//Memory Allocation for pimRGB
	if( (pimRGB=imMalloc(bih.biWidth,bih.biHeight)) ==NULL){
		sprintf( strErrMsg, "imBmpRead:Memory Allocation Error: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		fclose(fp);
		return NULL;
	}

	//Read Body
	if( imBmpReadBody( pimRGB, fp, strFileName, &bfh, &bch, &bih ) ){
		return NULL;
	}
	return pimRGB;
}

int imReadAgain( IM_RGB* pimDST, char *strFileName ){
	return imBmpReadAgain( pimDST, strFileName );
}

/*****************************************************************************/
/**
* RGB 24 bit BMPFILE reader 
* \param  strFileName is a pointer of file name strings 
*/
IM_RGB* imBmpRead( char *strFileName ){

	IM_RGB* pimRGB=NULL;

	BITMAPFILEHEADER bfh;
	BITMAPCOREHEADER bch;
	BITMAPINFOHEADER bih;

	int idx=0;
	int x,y;
	int bmp_idx;
	int im_idx;
	int iVerticalStep;

	unsigned long bxSize;

	char strErrMsg [IM_BMP_BUF_SIZE];
	char strReadBuf[IM_BMP_BUF_SIZE];
	unsigned char *pBmpData;
	FILE *fp;


	if( (fp=fopen(strFileName,"rb"))==NULL ){
		sprintf( strErrMsg, "imBmpRead:File Open Error: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}
	/* Read Bitmap HEADER -------------------------------------------*/
	fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BF,(size_t)1,fp);
	idx = 0;
	_IM_BUF2MEM( unsigned short ,bfh.bfType     ,strReadBuf,idx);    //2
	_IM_BUF2MEM( unsigned int   ,bfh.bfSize     ,strReadBuf,idx);    //4
	_IM_BUF2MEM( unsigned short ,bfh.bfReserved1,strReadBuf,idx);    //2
	_IM_BUF2MEM( unsigned short ,bfh.bfReserved2,strReadBuf,idx);    //2 
	_IM_BUF2MEM( unsigned int   ,bfh.bfOffBits  ,strReadBuf,idx);    //4

	fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BxSIZE,(size_t)1,fp);
	idx=0;
	_IM_BUF2MEM( unsigned int   ,bxSize          ,strReadBuf,idx);  //4

	if       ( bxSize == 40 ){ // Windows bitmap
		fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BI_WO_BISIZE,(size_t)1,fp);
		idx = 0;
		bih.biSize = bxSize;
		_IM_BUF2MEM( int            ,bih.biWidth        ,strReadBuf,idx);  // 4
		_IM_BUF2MEM( int            ,bih.biHeight       ,strReadBuf,idx);  // 4
		_IM_BUF2MEM( unsigned short ,bih.biPlanes       ,strReadBuf,idx);  // 2
		_IM_BUF2MEM( unsigned short ,bih.biBitCount     ,strReadBuf,idx);  // 2 
		_IM_BUF2MEM( unsigned int   ,bih.biCompression  ,strReadBuf,idx);  // 4
		_IM_BUF2MEM( unsigned int   ,bih.biSizeImage    ,strReadBuf,idx);  // 4
		_IM_BUF2MEM( int            ,bih.biXPixPerMeter ,strReadBuf,idx);  // 4
		_IM_BUF2MEM( int            ,bih.biYPixPerMeter ,strReadBuf,idx);  // 4
		_IM_BUF2MEM( unsigned int   ,bih.biClrUsed      ,strReadBuf,idx);  // 4
		_IM_BUF2MEM( unsigned int   ,bih.biClrImporant  ,strReadBuf,idx);  // 4
	}else if ( bxSize == 12 ){ // OS/2 bitmap
		fread(strReadBuf,(size_t)IM_BMP_SIZEOF_BC_WO_BCSIZE,(size_t)1,fp);
		idx = 0;
		bch.bcSize = bxSize;
		_IM_BUF2MEM( short          ,bch.bcWidth    ,strReadBuf,idx);   //2
		_IM_BUF2MEM( short          ,bch.bcHeight   ,strReadBuf,idx);   //2
		_IM_BUF2MEM( unsigned short ,bch.bcPlanes   ,strReadBuf,idx);   //2
		_IM_BUF2MEM( unsigned short ,bch.bcBitCount ,strReadBuf,idx);   //2
		sprintf( strErrMsg, "imBmpRead:File Open Error (Imcompatible BMP): %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}else{
		sprintf( strErrMsg, "imBmpRead:File Open Error (Bloaken File?): %s(bxSize=%ld)\n", strFileName,bxSize );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}
	/* Jadge Readable -------------------------------------------------*/
	if( bih.biPlanes      !=1  ||
		( bih.biBitCount  !=24 && bih.biBitCount  !=32 ) ||
		bih.biCompression !=0     ){
			sprintf( strErrMsg, "imBmpRead:File Open Error (Imcompatible BMP): %s\n", strFileName );
			imErrMessageHandle(strErrMsg);
			return pimRGB;    
	}

	iVerticalStep=(int)(4*ceil(bih.biWidth * (bih.biBitCount/8) /4.0));
	if( bih.biHeight * iVerticalStep != bih.biSizeImage ){
		sprintf( strErrMsg, "imBmpRead:File Open Error (Illigal file size): %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}
	/* Memory Allocation   -------------------------------------------*/
	if( (pimRGB=imMalloc(bih.biWidth,bih.biHeight)) ==NULL ||
		(pBmpData=(unsigned char*)malloc( bih.biSizeImage ))==NULL ){
			sprintf( strErrMsg, "imBmpRead:Memory Allocation Error: %s\n", strFileName );
			imErrMessageHandle(strErrMsg);
			return pimRGB;
	}

	/* Read Data -------------------------------------------*/
	fread(pBmpData,(size_t)sizeof(unsigned char),(size_t)(bih.biSizeImage),fp );

	/* Copy Data -------------------------------------------*/
	bmp_idx=0;
	im_idx =0;
	//	int dx,bitshift[3];
	for( y=0; y<bih.biHeight; y++ ){
		bmp_idx = (bih.biHeight-y-1)*iVerticalStep ;
		for( x=0; x<bih.biWidth; x++ ){
			if(IM_BIT_DEPTH == 10){
				pimRGB->B[im_idx] = (ImImage)((pBmpData[bmp_idx+0]<<2)+(ImImage)(pBmpData[bmp_idx+0]>>6));//+bitshift[0]
				pimRGB->G[im_idx] = (ImImage)((pBmpData[bmp_idx+1]<<2)+(ImImage)(pBmpData[bmp_idx+1]>>6));//+bitshift[1]
				pimRGB->R[im_idx] = (ImImage)((pBmpData[bmp_idx+2]<<2)+(ImImage)(pBmpData[bmp_idx+2]>>6));//+bitshift[2]
			}
			else{
				pimRGB->B[im_idx] = (ImImage)pBmpData[bmp_idx+0];
				pimRGB->G[im_idx] = (ImImage)pBmpData[bmp_idx+1];
				pimRGB->R[im_idx] = (ImImage)pBmpData[bmp_idx+2];
			}
			bmp_idx +=3 ;
			im_idx  ++  ;
			if( bih.biBitCount==32 ){
				bmp_idx ++ ;
			}
			//printf("%d %d %d %d\n", pBmpData[bmp_idx+0], pBmpData[bmp_idx+1], pBmpData[bmp_idx+2], pBmpData[bmp_idx+3]); 
			//getchar();

		}
	}

	fclose(fp);
	free(pBmpData);
	return pimRGB;

}

/*****************************************************************************/
/**
* RGB 24 bit BMPFILE writer 
* \param  pimRGB      is a pointer of IM_RGB output
* \param  strFileName is a pointer of file name strings 
*/
int imBmpWrite( IM_RGB* pimRGB, char* strFileName ){
	int ret=1;

	BITMAPFILEHEADER bfh;
	//BITMAPCOREHEADER bch;
	BITMAPINFOHEADER bih;

	int idx=0;
	int x,y;
	int bmp_idx;
	int im_idx;
	int iVerticalStep;

	char strErrMsg [IM_BMP_BUF_SIZE];
	char strWriteBuf[IM_BMP_BUF_SIZE];
	unsigned char *pBmpData;
	FILE *fp;

	iVerticalStep=(int)(4*ceil( pimRGB->iSizeX * 3 /4.0));

	memset(&bfh,0,sizeof(bfh));
	memset(&bih,0,sizeof(bih));
	memset(strWriteBuf,0,IM_BMP_BUF_SIZE);

	bih.biSize         = IM_BMP_SIZEOF_BI;
	bih.biWidth        = pimRGB->iSizeX;
	bih.biHeight       = pimRGB->iSizeY;
	bih.biPlanes       = 1;
	bih.biBitCount     =24;
	bih.biCompression  = 0;
	bih.biSizeImage    =iVerticalStep * pimRGB->iSizeY;
	bih.biXPixPerMeter = 0;
	bih.biYPixPerMeter = 0;
	bih.biClrUsed      = 0;
	bih.biClrImporant  = 0;

	bfh.bfType      = 19778;
	bfh.bfSize      = IM_BMP_SIZEOF_BF + IM_BMP_SIZEOF_BI + bih.biSizeImage;
	bfh.bfReserved1 =0;
	bfh.bfReserved2 =0;
	bfh.bfOffBits   = IM_BMP_SIZEOF_BF + IM_BMP_SIZEOF_BI;

	/* Copy Structure Member to Buffer ------------------------------*/
	idx=0;
	_IM_MEM2BUF( unsigned short ,bfh.bfType     ,strWriteBuf,idx);    //2
	_IM_MEM2BUF( unsigned int   ,bfh.bfSize     ,strWriteBuf,idx);    //4
	_IM_MEM2BUF( unsigned short ,bfh.bfReserved1,strWriteBuf,idx);    //2
	_IM_MEM2BUF( unsigned short ,bfh.bfReserved2,strWriteBuf,idx);    //2 
	_IM_MEM2BUF( unsigned int   ,bfh.bfOffBits  ,strWriteBuf,idx);    //4

	_IM_MEM2BUF( unsigned int   ,bih.biSize         ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( int            ,bih.biWidth        ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( int            ,bih.biHeight       ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( unsigned short ,bih.biPlanes       ,strWriteBuf,idx);  // 2
	_IM_MEM2BUF( unsigned short ,bih.biBitCount     ,strWriteBuf,idx);  // 2 
	_IM_MEM2BUF( unsigned int   ,bih.biCompression  ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( unsigned int   ,bih.biSizeImage    ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( int            ,bih.biXPixPerMeter ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( int            ,bih.biYPixPerMeter ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( unsigned int   ,bih.biClrUsed      ,strWriteBuf,idx);  // 4
	_IM_MEM2BUF( unsigned int   ,bih.biClrImporant  ,strWriteBuf,idx);  // 4  

	/* Memory Allocation   -------------------------------------------*/
	if( (pBmpData=(unsigned char*)malloc( bih.biSizeImage ))==NULL ){
		sprintf( strErrMsg, "imBmpWrite:Memory Allocation Error: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return ret;
	}


	/* Copy Data -------------------------------------------*/
	bmp_idx=0;
	im_idx =0;
	for( y=0; y<bih.biHeight; y++ ){
		bmp_idx = (bih.biHeight-y-1)*iVerticalStep ;
		for( x=0; x<bih.biWidth; x++ ){
			if(sizeof(ImImage)==sizeof(unsigned int)){
				pBmpData[bmp_idx+0] = (unsigned char)(pimRGB->B[im_idx]>>2);
				pBmpData[bmp_idx+1] = (unsigned char)(pimRGB->G[im_idx]>>2);
				pBmpData[bmp_idx+2] = (unsigned char)(pimRGB->R[im_idx]>>2);
			}
			else{
				pBmpData[bmp_idx+0] = (unsigned char)(pimRGB->B[im_idx]);
				pBmpData[bmp_idx+1] = (unsigned char)(pimRGB->G[im_idx]);
				pBmpData[bmp_idx+2] = (unsigned char)(pimRGB->R[im_idx]);
			}
			bmp_idx += 3;
			im_idx  ++;
		}
	}

	/* File Open/Write/Close      -------------------------------------------*/
	if( (fp=fopen(strFileName,"wb"))==NULL ){
		sprintf( strErrMsg, "imBmpWrite:File Open Error: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return ret;
	}
	fwrite(strWriteBuf,(size_t)IM_BMP_SIZEOF_BI+IM_BMP_SIZEOF_BF,(size_t)1,fp);
	fwrite(pBmpData,(size_t)sizeof(unsigned char),(size_t) (bih.biSizeImage) ,fp);
	fclose(fp);

	/* Memory Free ---------------------------------------------------------*/
	free(pBmpData);

	ret = 0;
	return ret;

}

/*****************************************************************************/
/**
* Clear IM_RGB structure 
* \param  pimRGB is a pointer of IM_RGB 
*/

void imClear(IM_RGB *pimRGB){
	pimRGB->iSizeX=0;
	pimRGB->iSizeY=0;
	pimRGB->R=NULL;
	pimRGB->G=NULL;
	pimRGB->B=NULL;
}

/**
* RGB 24 bit BMPFILE reader 
* \param  strFileName is a pointer of file name strings 
*/
IM_RGB* imRead( char *strFileName ){
	return imBmpRead(strFileName);
}

/**
* RGB 24 bit BMPFILE writer 
* \param  strFileName is a pointer of IM_RGB output
* \param  strFileName is a pointer of file name strings 
*/
int imWrite( IM_RGB* pimRGB, char *strFileName ){
	return imBmpWrite(pimRGB,strFileName);
}

/**
* Bitmap Copy 
* \param  pimDST is Destination Image 
* \param  pimDST is Source Image 
*/
void imCopy(IM_RGB* pimDST, IM_RGB* pimSRC){
	//int idx = 0;
	memcpy(pimDST->R,pimSRC->R,sizeof(ImImage)*pimDST->iSizeX*pimDST->iSizeY);
	memcpy(pimDST->G,pimSRC->G,sizeof(ImImage)*pimDST->iSizeX*pimDST->iSizeY);
	memcpy(pimDST->B,pimSRC->B,sizeof(ImImage)*pimDST->iSizeX*pimDST->iSizeY);
	//for (int y=0;y<pimSRC->iSizeY;y++){
	//	for (int x=0;x<pimSRC->iSizeX;x++){
	//		pimDST->R[idx]	 = pimSRC->R[idx];
	//		pimDST->G[idx]	 = pimSRC->G[idx];
	//		pimDST->B[idx]	 = pimSRC->B[idx];
	//		idx++;
	//	}
	//}
}

/**
* Pointer Swap
* \param  ppimA becomes ppimB's pointer
* \param  ppimB becomes ppimA's pointer
*/
void imSwap(IM_RGB** ppimA, IM_RGB** ppimB){
	IM_RGB *pimT;
	pimT=*ppimA;
	*ppimA=*ppimB;
	*ppimB=pimT;
}

int  imHalfSynth(IM_RGB* pimDst, IM_RGB* pimLeft,IM_RGB* pimRight){

	int x,y;
	int iSizeX;
	int iSizeY;
	int src_idx;
	int dst_idx;
	char strErrMsg[IM_BMP_BUF_SIZE];

	if( (!imIsSameSize(pimLeft, pimRight))||
		(!imIsSameSize(pimLeft, pimDst  )) ){
			sprintf( strErrMsg, "imHalfSynth:Imcompatible size:\n\
								Left :%d x %d\n\
								Right:%d x %d\n\
								Dst  :%d x %d\n",
								pimLeft ->iSizeX,pimLeft ->iSizeY,
								pimRight->iSizeX,pimRight->iSizeY,
								pimDst  ->iSizeX,pimDst  ->iSizeY);
			imErrMessageHandle(strErrMsg);
			return -1;
	} 

	iSizeX = pimLeft->iSizeX;
	iSizeY = pimLeft->iSizeY;
	for( y=0; y<iSizeY; y++ ){
		dst_idx=y*iSizeX;
		src_idx=y*iSizeX+iSizeX/4;
		for( x=0; x<iSizeX/2; x++ ){
			pimDst->R[dst_idx] = pimLeft->R[src_idx];
			pimDst->G[dst_idx] = pimLeft->G[src_idx];
			pimDst->B[dst_idx] = pimLeft->B[src_idx];
			dst_idx++;
			src_idx++;
		}
		src_idx=y*iSizeX+iSizeX/4;
		for(    ; x<iSizeX  ; x++ ){
			pimDst->R[dst_idx] = pimRight->R[src_idx];
			pimDst->G[dst_idx] = pimRight->G[src_idx];
			pimDst->B[dst_idx] = pimRight->B[src_idx];
			dst_idx++;
			src_idx++;
		}
	}

	return 0;
}
int imIsSameSize(IM_RGB* pimA, IM_RGB* pimB){
	if( (pimA->iSizeX == pimB->iSizeX) &&
		(pimA->iSizeY == pimB->iSizeY) ){
			return 1;
	}else{
		return 0;
	}
}



/****************************************************/
/* BasicGraphicProcedure */
/****************************************************/
/**
* Affine transformation
* \param  pimYYY        is Destination Image 
* \param  pimXXX        is Source Image 
* \param  fMatrix[3][4] is Coefficient Matrix 
*/
void imXXX2YYY( IM_RGB *pimYYY, IM_RGB *pimXXX, int fMatrix[3][4], int X2Y_flag ){


	ImImage *pXXX[3];
	ImImage *pYYY[3];

	int sum,tmp;
	int idx,x,y,i,j;
	int bit_shift;
	
	idx=0;

	if (X2Y_flag==0){
		fMatrix[0][3]=0;
		fMatrix[1][3]=(128<<((IM_BIT_SHIFT)+(IM_BIT_DEPTH-8)));
		fMatrix[2][3]=(128<<((IM_BIT_SHIFT)+(IM_BIT_DEPTH-8)));//11+2�r�b�g�V�t�g�A����+2�r�b�g����11�r�b�g�V�t�g����������8�r�b�g�̌v�Z�Ɏg���W���̂���
	}

	if (X2Y_flag==1){
		fMatrix[0][3]=(1*0)									    + ( 2870*(-128<<(IM_BIT_DEPTH-8)));
		fMatrix[1][3]=(1*0) + (-703*(-128<<(IM_BIT_DEPTH-8)))	+ (-1463*(-128<<((IM_BIT_DEPTH-8))));//RGB�֘A�ō��V�t�g�����鎞�͉��ʃr�b�g���߂�ׂ�
		fMatrix[2][3]=(1*0) + (3630*(-128<<(IM_BIT_DEPTH-8)));
	}

	for( y=0; y<pimXXX->iSizeY; y ++ ){
		for( x=0; x<pimXXX->iSizeX; x++ ){
			pXXX[0]=&(pimXXX->R[idx]);pXXX[1]=&(pimXXX->G[idx]);pXXX[2]=&(pimXXX->B[idx]);
			pYYY[0]=&(pimYYY->R[idx]);pYYY[1]=&(pimYYY->G[idx]);pYYY[2]=&(pimYYY->B[idx]);
			for( i=0; i<3; i++ ){
				sum=fMatrix[i][3];//�萔�l����sum�ɑ��
				for( j=0; j<3; j++ ){
					sum+=fMatrix[i][j]*(*pXXX[j]);//RGB��YCbCr�ϊ��̎��ɓ��Ă͂߂�B�W����11�r�b�g�����V�t�g���Ă���B
				}//j
				/*
				if (X2Y_flag==0 && sizeof(ImImage)==sizeof(unsigned int)){//RGB��YCbCr�̏ꍇ��9�r�b�g�E�V�t�g(YCbCr��12�r�b�g)
				bit_shift = IM_BIT_SHIFT-2;}
				else if (X2Y_flag ==1 && sizeof(ImImage)==sizeof(unsigned int)) {//YCbCr��RGB�̏ꍇ��13�r�b�g�E�V�t�g(RGB��10�r�b�g)
				bit_shift = IM_BIT_SHIFT+2;}
				else{
				bit_shift = IM_BIT_SHIFT;}
				*/
				bit_shift = IM_BIT_SHIFT;
				tmp = (sum >> (bit_shift-1)) & 1;
				sum = (sum>>bit_shift)+tmp;

				if(IM_BIT_DEPTH==10){
					if( sum>1023 ){//�I�[�o�[�t���[�΍�
						sum=1023;}
					//if( sum>4095 ){
					//	sum=4095;}
					if(sum<    0){
						sum=0;}
				}
				else{
					if( sum>255 ){
						sum=255;}
					if(sum < 0){
						sum=0;}
				}

				*pYYY[i]=(ImImage)sum;//[R][G][B]�̂��ꂼ��̃A�h���X�̈ʒu��sum�̒l����
			}//i
			idx++;
		}//y
	}//x
}

/**
* Color space transformation RGB to YCbCr
* \param  pimYCC is Destination Image ( YCbCr )
* \param  pimRGB is Source Image      ( RGB   )
*/
void imRGB2YCC( IM_RGB *pimYCC, IM_RGB *pimRGB ){
	int RGB_flag=0;
	imXXX2YYY( pimYCC, pimRGB, im_cfRGB2YCC, RGB_flag);
}

/**
* Color space transformation YCbCr to RGB
* \param  pimRGB is Destination Image ( RGB   )
* \param  pimYCC is Source Image      ( YCbCr )
*/
void imYCC2RGB( IM_RGB *pimRGB, IM_RGB *pimYCC ){
	int YCC_flag=1;
	imXXX2YYY( pimRGB, pimYCC, im_cfYCC2RGB, YCC_flag );
}


void CSVwrite(IM_RGB *pimRGB, char *strFileName){
	FILE *csvfp1;
	FILE *csvfp2;
	FILE *csvfp3;
	int i,j,idx=0;
	//	int tmpR,tmpG,tmpB;
	char fname1[255]="Y";
	char fname2[255]="Cb";
	char fname3[255]="Cr";
	if(sizeof(ImImage)==sizeof(unsigned int)){

		strcat(fname1,strFileName);
		strcat(fname2,strFileName);
		strcat(fname3,strFileName);
		char strErrMsg[IM_BMP_BUF_SIZE];
		
		csvfp1=fopen(fname1,"w");
		csvfp2=fopen(fname2,"w");
		csvfp3=fopen(fname3,"w");



		for(j=0;j<pimRGB->iSizeY;j++){
			for(i=0;i<pimRGB->iSizeX;i++){
				if(sizeof(ImImage)==sizeof(unsigned int)){
					//tmpR = (pimRGB->R[i+(pimRGB->iSizeX*idx)] >> 3) & 1;
					//tmpG = (pimRGB->G[i+(pimRGB->iSizeX*idx)] >> 3) & 1;
					//tmpB = (pimRGB->B[i+(pimRGB->iSizeX*idx)] >> 3) & 1;
					fprintf(csvfp1,"%d,",((pimRGB->R[i+(pimRGB->iSizeX*idx)])));
					fprintf(csvfp2,"%d,",((pimRGB->G[i+(pimRGB->iSizeX*idx)])));
					fprintf(csvfp3,"%d,",((pimRGB->B[i+(pimRGB->iSizeX*idx)])));
				}
				else{
					fprintf(csvfp1,"%d,",pimRGB->R[i+(pimRGB->iSizeX*idx)]);
					fprintf(csvfp2,"%d,",pimRGB->G[i+(pimRGB->iSizeX*idx)]);
					fprintf(csvfp3,"%d,",pimRGB->B[i+(pimRGB->iSizeX*idx)]);
				}
			}
			fprintf(csvfp1,"\n");
			fprintf(csvfp2,"\n");
			fprintf(csvfp3,"\n");
			idx++;
		}

		if( csvfp1 == NULL || csvfp2 == NULL || csvfp3 == NULL){
			sprintf( strErrMsg, "CSVwrite:Memory Allocation Error: %s or %s or %s\n", fname1,fname2,fname3 );
			imErrMessageHandle(strErrMsg);
			return;
		}

		fclose(csvfp1);
		fclose(csvfp2);
		fclose(csvfp3);
	}
}


IM_RGB* imPPMread( char *strFileName ){

	IM_RGB* pimRGB=NULL;

	int idx=0;
	//  int x,y;
	int X_Size,Y_Size,lm;

	//    unsigned long bxSize;

	char strErrMsg [IM_BMP_BUF_SIZE];
	FILE *fp;
	char temp[75];
	char format[5];
	int type;
	char comment[255];



	if( (fp=fopen(strFileName,"r"))==NULL ){
		sprintf( strErrMsg, "imPPMread:File Open Error: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}
	/* Read PPM HEADER -------------------------------------------*/
	//fgets(format,5,fp);
	fgets(temp, 75, fp) ;
	sscanf(temp,"%s",format);//�t�@�C���`���̏��̓ǂݍ���

	if (format[0]!='P'){
		sprintf( strErrMsg, "imPPMread:File type isn't PPM: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}
	sscanf(format,"P%d",&type);
	if(type != 3 && type != 6){
		sprintf( strErrMsg, "imPPMread:File type isn't PPM: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}


	do {
		fgets(comment,255,fp);
	}while (comment[0] == '#');//�擪������#(�R�����g)�̏ꍇ�ǂݔ�΂�
	sscanf(comment,"%d%d",&X_Size,&Y_Size);//�摜�T�C�Y�̓ǂݍ���

	fgets(temp, 75, fp);
	sscanf(temp,"%d",&lm);

	if (X_Size<=0||Y_Size<=0||lm<=0){
		sprintf( strErrMsg, "imPPMread:PPM range is fault: %s\n", strFileName );
		imErrMessageHandle(strErrMsg);
		return pimRGB;
	}

	/* Memory Allocation   -------------------------------------------*/
	pimRGB=imMalloc(X_Size,Y_Size);

	/* Read Data -------------------------------------------*/
#if 0 //Conventional Reader : Line number = Pixel count
	unsigned int valR, valG, valB;
	for (idx=0;idx<(X_Size*Y_Size);idx++){
		fgets(temp, 75, fp); 
		sscanf(temp,"%d %d %d", &valR, &valG, &valB);
		pimRGB->R[idx]=valR;
		pimRGB->G[idx]=valG;
		pimRGB->B[idx]=valB;
	}
#else
	char pcBuf[IM_BMP_BUF_SIZE];
	int sub_idx;
	int val;
	char *pcCur;
	char *pcBegin;
	int iState;

	const int ciStateNotNum=0;
	const int ciStateNum=1;

	sub_idx = 0;
	idx = 0;
	while( (fgets( pcBuf, IM_BMP_BUF_SIZE, fp) !=NULL) &&
		(idx<(X_Size*Y_Size))                          ){
			//printf("%s\n",pcBuf);
			//getchar();
			iState=ciStateNotNum;
			for( pcCur=pcBuf; (pcCur<(pcBuf+IM_BMP_BUF_SIZE)) && ((*pcCur) != '\0')/* && ((*pcCur)!='\n') && ((*pcCur)!= '\r')*/  ;pcCur++ ){
				//printf("%c(%d)",*pcCur,*pcCur);
				if( ('0'<=(*pcCur)) && ((*pcCur)<='9') ){
					//printf(":Number:%d\n",iState);
					if( iState!=ciStateNum ){
						pcBegin = pcCur ;
					}
					iState = ciStateNum;
				}else{
					//printf(":NotNumber:%d\n",iState);
					if( iState!=ciStateNotNum ){
						*pcCur = '\0';
						val=atoi(pcBegin);
						//printf("idx:%d sub_idx:%d  = %d(%s) \n ",idx,sub_idx,val,pcBegin);
						//if( val!=0 ){
						//  getchar();
						//}
						switch( sub_idx ){
		case 0:
			pimRGB->R[idx]=val;
			sub_idx++;
			break;
		case 1:
			pimRGB->G[idx]=val;
			sub_idx++;
			break;
		case 2:
		default:
			pimRGB->B[idx]=val;
			sub_idx=0;
			idx ++ ;
			break;
						}
					}
					iState = ciStateNotNum;
				}
			}


	}	  
#endif

	fclose(fp);
	return pimRGB;


}


int imPPMwrite( IM_RGB* pimRGB, char* strFileNameorg, char* strFileNamedst){
	FILE *ppm;
	int i;
	int ret_cnt=0;

	char strErrMsg[IM_BMP_BUF_SIZE];

	int X_Size,Y_Size,lm;
	int length;
	FILE *ffp;
	char format[5];
	int type;
	char comment[255];
	char temp[75];//add mine


	if( (ffp=fopen(strFileNameorg,"r"))==NULL ){
		sprintf( strErrMsg, "imPPMread:File Open Error: %s\n", strFileNameorg );
		imErrMessageHandle(strErrMsg);
		return -1;
	}
	/* Read PPM HEADER -------------------------------------------*/
#if MN_MODE
	fgets(temp, 75, ffp) ;
	sscanf(temp,"%s",format);//�t�@�C���`���̏��̓ǂݍ���
#else
	fscanf(ffp,"%s%*c",format);//�t�@�C���`���̏��̓ǂݍ���
#endif

	if (format[0]!='P'){
		sprintf( strErrMsg, "imPPMread:File type isn't PPM: %s\n", strFileNameorg );
		imErrMessageHandle(strErrMsg);
		return -1;
	}
	sscanf(format,"P%d",&type);
	if(type != 3 && type != 6){
		sprintf( strErrMsg, "imPPMread:File type isn't PPM: %s\n", strFileNameorg );
		imErrMessageHandle(strErrMsg);
		return -1;
	}
	do {
		fgets(comment,255,ffp);
	}while (comment[0] == '#');//�擪������#(�R�����g)�̏ꍇ�ǂݔ�΂�
	sscanf(comment,"%d%d",&X_Size,&Y_Size);//�摜�T�C�Y�̓ǂݍ���

#if MN_MODE
	fgets(temp, 75, ffp);
	sscanf(temp,"%d",&lm);
#else
	fscanf(ffp,"%d",&lm);
#endif

	if (X_Size<=0||Y_Size<=0||lm<=0){
		sprintf( strErrMsg, "imPPMread:PPM range is fault: %s\n", strFileNameorg );
		imErrMessageHandle(strErrMsg);
		return -1;
	}

	ppm=fopen(strFileNamedst,"w");
	if ( PPM_LEN_OUTPUT > 0 && PPM_LEN_OUTPUT <= 5 ){
		length=PPM_LEN_OUTPUT;
	}
	else{
		length=5;
	}
	//	    fprintf(ppm,"%s\n%d %d\n%d\n",format,X_Size,Y_Size,lm);
#if MN_MODE
	fprintf(ppm,"%s\r\n%d %d\r\n%d\r\n",format,pimRGB->iSizeX,pimRGB->iSizeY,lm);
#else
	fprintf(ppm,"%s\n%d %d\n%d\n",format,pimRGB->iSizeX,pimRGB->iSizeY,lm);
#endif
	for(i=0;i<(pimRGB->iSizeX * pimRGB->iSizeY);i++){
		if (IM_BIT_DEPTH == 10){
			//				printf("%04d %04d %04d ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
			//				fprintf(ppm,"%04d %04d %04d ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));

#if MN_MODE
		  fprintf(ppm," %04d %04d %04d\r\n",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#else
			fprintf(ppm," %04d %04d %04d ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#endif
		}
		else{
#if MN_MODE
			fprintf(ppm," %03d %03d %03d\r\n",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#else
			fprintf(ppm," %03d %03d %03d ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#endif
		}
		ret_cnt++;
		if (ret_cnt==length){
#if MN_MODE

#else
			fprintf(ppm,"\n");
#endif
			ret_cnt=0;
		}

	}

	if( ppm == NULL ){
		//        sprintf( strErrMsg, "CSVwrite:Memory Allocation Error: %s\n", ppm );
		sprintf( strErrMsg, "CSVwrite:Memory Allocation Error: %s\n", strFileNamedst );
		imErrMessageHandle(strErrMsg);
		return -1;
	}
	fclose(ffp);
	fclose(ppm);
	return 1;
}

IM_RGB* imPread( char *strFileName ){
	return imPPMread(strFileName);
}


int imPwrite( IM_RGB* pimRGB, char* strFileNameorg, char* strFileNamedst ){
	return imPPMwrite(pimRGB,strFileNameorg,strFileNamedst);
}



int imPPMconvert( IM_RGB* pimRGB, char* strOutputFileName ){
	FILE *ppm;
	int i;
	int ret_cnt=0;

	char strErrMsg[IM_BMP_BUF_SIZE];

	int X_Size,Y_Size,length,lm;

	char format[5]="P3";
	//	int type;
	//	char comment[255];

	X_Size=pimRGB->iSizeX;//pimSource->iSizeX��X�̃T�C�Y��m�邱�Ƃ��ł��܂�
	Y_Size=pimRGB->iSizeY;

	if(IM_BIT_DEPTH==10){
		lm=1023;
	}
	else{
		lm=255;
	}

	ppm=fopen(strOutputFileName,"w");

	if ( PPM_LEN_OUTPUT > 0 && PPM_LEN_OUTPUT <= 5 ){
		length=PPM_LEN_OUTPUT;
	}
	else{
		length=5;
	}
#if MN_MODE
	fprintf(ppm,"%s\r\n%d %d\r\n%d\r\n",format,X_Size,Y_Size,lm);
#else
	fprintf(ppm,"%s\n%d %d\n%d\n",format,X_Size,Y_Size,lm);
#endif
	for(i=0;i<(pimRGB->iSizeX * pimRGB->iSizeY);i++){
		if (IM_BIT_DEPTH == 10){
#if MN_MODE
			fprintf(ppm," %04d %04d %04d\r\n",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#else
			fprintf(ppm," %04d %04d %04d ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#endif
		}
		else{
#if MN_MODE
			fprintf(ppm," %03d %03d %03d\r\n ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#else
			fprintf(ppm," %03d %03d %03d ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
#endif
		}
		//fprintf(ppm,"%04d %04d %04d ",(pimRGB->R[i]),(pimRGB->G[i]),(pimRGB->B[i]));
		ret_cnt++;
		if (ret_cnt==(length)){
#if MN_MODE

#else
			fprintf(ppm,"\n");
#endif
			ret_cnt=0;
		}

	}

	if( ppm == NULL ){
		//      sprintf( strErrMsg, "CSVwrite:Memory Allocation Error: %s\n", ppm );
		sprintf( strErrMsg, "CSVwrite:Memory Allocation Error: %s\n", strOutputFileName );
		imErrMessageHandle(strErrMsg);
		return -1;
	}
	fclose(ppm);
	return 1;
}


int PPMconvert( IM_RGB* pimRGB, char* strOutputFileName ){
	return imPPMconvert(pimRGB,strOutputFileName);
}
