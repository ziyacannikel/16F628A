     unsigned char dizi1[36];      //bayrak ilk 8 led verileri
     unsigned char dizi2[36];      //bayrak son 3 led verileri
     int i;
     float sayac=0;
     float time;
     bit d1;
     bit d2;
     bit k1;
void interrupt(){
     if (INTCON.T0IF)//Timer0 Kesme bayraðý kontrol ediliyor.
     {
         sayac=sayac+1;
         TMR0=131;//Timer0 registerýna 0,1 ms'de bir kesme oluþturacak deðer
         INTCON.T0IF=0;// Kesme bayraðý sýfýrlar
      }
}

void kesme_ayar(){
       OPTION_REG.T0CS=0;// Clock dahili osilatör seçildi.
       OPTION_REG.T0SE=0;
       OPTION_REG.PSA=0;//Prescaler deðeri Timer0 için kullanýlacak.
       OPTION_REG.PS2=0;//Prescaler deðeri 1:2
       OPTION_REG.PS1=0;//Prescaler deðeri 1:2
       OPTION_REG.PS0=0;//Prescaler deðeri 1:2
       INTCON.GIE=1;// tüm kesmeleri açýk
       INTCON.T0IF=0;//Kesme bayraðýný her ihtimale karþý sýfýrla
       TMR0=131 ;//Timer0 registerýna 0,1 ms'de bir kesme oluþturacak deðer yükle
       INTCON.T0IE=1;//Timer0 kesmesini aktif
}


void kurulum(){
     TRISA=0B00001000;    //Ra3 input
     TRISB=0B00000000;    //b portu komple out
     PORTA=0;
     PORTB=0;
    for(i=0;i<13;i++){
      dizi1[i]      = 0B11111000;
    }
     dizi1[13]      = 0B01111000;
     dizi1[14]      = 0B01111000;
     for(i=15;i<19;i++){
     dizi1[i]       = 0B00111000;
     dizi1[i+4]     = 0B00011000;
     dizi1[i+8]     = 0B00001000;
     }
     dizi1[27]      = 0B00000000;
     dizi1[28]      = 0B00000000;
     dizi1[29]      = 0B00000000;
     dizi1[30]      = 0B00000001;
     dizi1[31]      = 0B10000001;
     dizi1[32]      = 0B11100111;
     dizi1[33]      = 0B11111110;
     dizi1[34]      = 0B01111110;
     dizi1[35]      = 0B11111100;

      for(i=0;i<6;i++){
        dizi2[i]    = 0B00000011;
      }
      for(i=6;i<10;i++){
        dizi2[i]    = 0B00000001;
      }
      for(i=10;i<30;i++){
        dizi2[i]     =0B00000000;
      }
     dizi2[30]       = 0B00000001;
     dizi2[31]       = 0B00000001;
     dizi2[32]       = 0B00000000;
     dizi2[33]       = 0B00000000;
     dizi2[34]       = 0B00000000;
     dizi2[35]       = 0B00000111;

}

 void sure_hesap(){
      d1=0;
      d2=0;
      k1=0;
      sayac =0;
   while(1){

     while( PORTA.RA3==1){
       if (k1==0){
       kesme_ayar();
       k1=1;
       }
     }
     if(d1==1 && d2==1){
       break;
     }
     if(sayac>0 && d1==0){
       d1=1;
       sayac=0;
     }
     while( PORTA.RA3==0 && d1==1)
     {
       d2=1;
     }


   }
    INTCON.GIE=0; // sayma iþi tamamlandý ve sayac a yazýldý
}



void main() {
     CMCON=0x07;         //comparatorleri kapat
    // delay_ms(2000);//motor devrinin sabitlenmesi ve çalýþtýrma için hazýrlýk
     kurulum();    //baþlangýç koþullarýný oluþturur
     sure_hesap();
      /*
      !!!! mekanizma bu þekilde !!!!
        time=(sayac*20)/11;
              PORTA=0XFF;
              while(0<time){
              time=time-1;
              }
              time=(sayac*20)/11;
              PORTA=0x00;
               while(0<time){
              time=time-1;
              }
      */


     while(1){
     for(i=0;i<36;i++){
     PORTB=dizi1[i];
     PORTA=dizi2[i];
     time=(sayac*20)/(11*72);
       while(0<time){
              time=time-1;
       }
     }

     for(i=35;i>=0;i--){
     PORTB=dizi1[i];
     PORTA=dizi2[i];
     time=(sayac*20)/(11*72);
       while(0<time){
              time=time-1;
       }
     }


     }

}