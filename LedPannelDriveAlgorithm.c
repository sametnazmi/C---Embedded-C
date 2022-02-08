  struct ledpanel_strings{
unsigned char bm[100];
int y_size;
int bm_end;
  } ;
  

  struct ledpanel_strings a;
  
/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
  void coonvert(struct ledpanel_strings *s)
{
  
  s->y_size=17;
  int width=42;
    s->bm_end=width*s->y_size;


    
    
  int bytecount = (s->y_size%8) == 0 ? (s->y_size/8) : (s->y_size/8+1); // dizinin byte sütun genisligi
  unsigned char d[32],x[32] = {0};
  int i,j;
  for(j = 0; j<s->bm_end; j++)
  {
    memcpy(d,&s->bm[bytecount*j],bytecount);
    for(i = 0;i<s->y_size;i++)
    {
      x[i/8]  |=  (((d[bytecount - (((s->y_size%8)<(i%8)) ? 1:0) -i/8]>>(i))&0x01)<<((s->y_size- 1 -i)%8));
//      x[i/8]  |=  d[bytecount - (((s->y_size%8)<(i%8)) ? 1:0) -i/8]; 
//      x[((s->y_size- 1 -i)/8)] |= ((d[i/8]>>(i))&0x01)<<((s->y_size- 1 -i)%8);
    }
    memcpy(&s->bm[bytecount*j],x,bytecount);
    memset(x,'\0',32);
  }
}

  unsigned char l[]={0x4,0x5,
  0x66,0x75,
  0x78,0x75,
  0x14,0x25,
  0x1,0x2,
  0x3,0x4,
  0x5,0x6,
  0x7,0x80,
  0x5,0xFA,
  0x45,0x23,
  0x35,0x36,
  0x45,0x12,
  0x12,0x00,
  0xAC,0xFA,
  0xBB,0xCC,
  0x12,0x1,
  0xAA,0xDD};  
  unsigned char constant_l[]={0x4,0x5,
  0x66,0x75,
  0x78,0x75,
  0x14,0x25,
  0x1,0x2,
  0x3,0x4,
  0x5,0x6,
  0x7,0x80,
  0x5,0xFA,
  0x45,0x23,
  0x35,0x36,
  0x45,0x12,
  0x12,0x00,
  0xAC,0xFA,
  0xBB,0xCC,
  0x12,0x1,
  0xAA,0xDD};  

  unsigned char sembol[17][17]; //ilk rakam satir - heightcount , ikinci rakam sütun - widthcount
  unsigned char trans_sembol[17][17]; //ilk rakam satir - widthcount , ikinci rakam sütun - heightcount
  unsigned char new_trans_sembol[17][17]; //Satirlari terslenmis yeni matris
  

  unsigned char temp[1]={0};
  unsigned char temp2[1]={0};
  void coonvert2(struct ledpanel_strings *s)
{
  s->y_size=17; //sütun
  int width=2*8; //satir
  s->bm_end=width;
  int heightcount = (s->y_size%8) == 0 ? (s->y_size/8) : (s->y_size/8+1); // dizinin byte satir sayisi
  int widthcount = (width%8) == 0 ? (width/8) : (width/8+1); // dizinin byte sütun sayisi
  //Byte içinde bitlerin yer degistirmesi, byte in ters çevrilmesi
  for(int i=0;i<heightcount*widthcount;i++)
  {
    memcpy(temp,&l[i],1);  
    for(int j=0;j<8;j++)
    {
      temp2[0] |=((temp[0]>>j)&0x01)<<(7-j);
    }
        memcpy(&l[i],temp2,1);
        memset(temp2,0,1);  

  }
  ///////////////////////////////////////////////////////77
  //Diziyi matris yapma
    // heightcount satir sayisi widthcount sütun sayisi
  int i=0;
  for( int c = 0 ; c < heightcount ; c++ ) //sütun elemanlarini içeri alma
   {
      for( int d = 0 ; d < widthcount ; d++ ) //satir elemanlarini içeri alma
      {
    memcpy(&sembol[c][d],&l[i],1);
      i++;
      }
   } i=0;
  ////////////////////////////////////////////////
  //Matrisin transpozunu alma
     for(int c = 0 ; c < heightcount ; c++ ) // loop to transpose the matrix
   {
      for(int d = 0 ; d < widthcount ; d++ )
      {
         trans_sembol[d][c] = sembol[c][d];
      }
   }
   ////////////////////////////////////////////////
   //Matriste satir degisimi yapma
        for(int d = 0 ; d < widthcount ; d++ ) // loop to transpose the matrix
   {
      for(int c = 0 ; c < heightcount ; c++ )
      {
         new_trans_sembol[d][c] = trans_sembol[(widthcount-1)-d][c];
      }
   }
  //Matrisi tekrar dizi yapma
     int j=0;
     for(int c = 0 ; c < widthcount ; c++ ) // loop for printing transposed matrix
   {
      for(int d = 0 ; d < heightcount ; d++ )
      {
    memcpy(&l[j],&new_trans_sembol[c][d],1);
    j++;
      }
   }j=0;
}