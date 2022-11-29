#include "ImRGB.h"
#define BUF_SIZE 1024
#include <math.h>
#define PI 3.14159265358979323846

int main(int argc, char *argv[])
{  
  if (argc < 2) {
    fprintf(stderr, "USAGE: test <InputImage1> \n");
    return -1;
  }
  
  IM_RGB* pimSource;
  IM_RGB* pimTmp;

  imInit();
  
  char strInputFileName[BUF_SIZE];
  char strOutputFileName[BUF_SIZE];

  int i,j;

  //READ
  strncpy(strInputFileName, (char *)argv[1], BUF_SIZE);
  pimSource=imRead(strInputFileName);
  
  int iSizeX=pimSource->iSizeX;
  int iSizeY=pimSource->iSizeY;


  pimTmp=imMalloc(iSizeX,iSizeY);

  for(j=0;j<iSizeY;j++){
    for(i=0;i<iSizeX;i++){
      pimTmp->R[iSizeX*j+i]=512;
      pimTmp->G[iSizeX*j+i]=512;
      pimTmp->B[iSizeX*j+i]=512;
    }
  }
   
  //WRITE

  sprintf(strOutputFileName,"Tmp.bmp");
  imWrite(pimTmp,strOutputFileName);

  imFree(pimSource);
  imFree(pimTmp);

  return 0;
}
