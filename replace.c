#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include <fcntl.h>
#include <unistd.h>

char* degistir(const char* satir, const char* aranan, const char* yenikelime) 
{ 
 int i;
 int say=0;
 int arananuzunluk = strlen(aranan); 
 int yeniuzunluk = strlen(yenikelime); 

  for (i = 0; satir[i] != '\0'; i++) {  //satirin sonuna kadar
	if (strstr(&satir[i], aranan) == &satir[i]) { 
		i = i + arananuzunluk - 1; //index'i bi sonraki kelimeye getir.
		say++; } 
  } 
	
 char* degismis; 
 degismis = (char*)malloc(i + say * (yeniuzunluk - arananuzunluk) + 1); //yeni satir icin yer ayır
  
 i = 0; 
  while (*satir!='\0') { //  \0 'a kadar 
	if (strstr(satir, aranan) == satir) { //aranan varsa yenikelimeyi ekle, 
		strcpy(&degismis[i], yenikelime); 
		i += yeniuzunluk;
		satir += arananuzunluk; } //indexi yenikelime kadar ileri al 
	 else
		degismis[i++] = *satir++; } //whilesonu
  
 degismis[i] = '\0'; //sona bitis karakteri
 return degismis; 
}
 

int main(int argc, char **argv)
{
  IS is;
  int i;
  char *txt=".txt";
  char *aranan,*yenikelime;
  int degisen=0;
  int varmi=0;
  int satirsayi=0;

  if (argc != 4) { fprintf(stderr, "Parametre olarak: 'dosya-adı degisecek-kelime yeni-kelime' seklinde giris yapin\n"); exit(1); }


  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    printf("Böyle bir dosya yok.\n");
    exit(1);
  }
  if(strstr(argv[1],txt)==NULL) {printf("sadece .txt uzantılı dosya giriniz.\n"); exit(1);}


  aranan=argv[2];
  yenikelime=argv[3];
 char* sonuc = (char*) malloc(sizeof(char)*(1000)); 

  while(get_line(is) >= 0) {
	
	strcat(sonuc,degistir(is->text1, aranan, yenikelime));

	for (i = 0; i < is->NF; i++) {
		if(strstr(is->fields[i],aranan)!=NULL){ varmi=1; }
		if (strcmp(is->fields[i], aranan) == 0){ degisen++; }   
	}//for sonu

  } //while sonu
if(varmi==0) { printf("Dosya iceriginde degistirelecek kelime bulunmuyor.\n"); exit(1); } 

 int fd, sz;

  fd = open("soru2-replace.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) { perror("w1"); exit(1); }

  sz = write(fd, sonuc, strlen(sonuc));

  close(fd); //dosya kapa

printf("\nDeğiştirilen kelime sayısı..:%d\n",degisen);

  jettison_inputstruct(is); //is kapa
  free(sonuc);
 
exit(0);
}
