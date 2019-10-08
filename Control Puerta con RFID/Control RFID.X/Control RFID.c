/*
 * Programa: Control_RFID. 
 * Microcontrolador: PIC16F1936.
 * Autor: Borxo Garc�a.
 * Versi�n:1.0v.
 */

//Palabras de configuraci�n
// CONFIG1
#pragma config FOSC = INTOSC    
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = OFF      
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = OFF      
#pragma config CLKOUTEN = OFF   
#pragma config IESO = OFF      
#pragma config FCMEN = OFF      

// CONFIG2
#pragma config WRT = OFF        
#pragma config PLLEN = OFF       
#pragma config STVREN = OFF     
#pragma config BORV = LO        
#pragma config LVP = OFF        

//Velocidad del oscilador interno//
#define _XTAL_FREQ 4000000

//Librerias//
#include <xc.h>
#include <stdio.h>
#include <string.h>

void main (void)
{   
    //Variables Locales//
    /*char ContraAsiic [3][12]={
                                {'0','A','0','0','6','D','F','8','C','4','5','B'},
                                {'0','A','0','0','6','D','7','A','B','D','A','0'},
                                {'0','C','0','0','4','1','D','C','8','9','1','8'}
                            };*/
    char ContraHex[3][14]=   {
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                            };
    /*char ContraHex[3][14]=   {
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                                {0x02,0x30,0x43,0x30,0x30,0x34,0x31,0x44,0x43,0x38,0x39,0x31,0x38,0x03}
                            };*/
    
    char Dato [14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int comp=0;
    //Configuraci�n Puertos//
    TRISA1=0;
    TRISA2=0;
    
    //Timer1//
    T1CON=0b00110001;
   //Configuraci�n EUSART//
    CREN=1;
    SYNC=0;
    SPEN=1; 
    
    //Configuraci�n Baudios//
    BRGH=1;
    BRG16=0;
    SPBRG=25;
    
    //Configuraci�n del Oscilador//
    OSCCON=0b01101000; //4Mhz
    
    while(1)
    {
        TMR1IF=0;
        
       /* for (int p=0;p<14;p++)
        {
            Dato[p]=0;
        } */
        
        for(int i=0;i<14;i++)
        {
            while (RCIF==0 );
            Dato[i]=RCREG;
            __delay_ms(500);
        }
        
      /* for(int z=0;z<2;z++)
        {
           comp=strcmp( ContraHex[z], Dato);
        }*/
        comp=strcmp( ContraHex[2], Dato);
          if(comp<0) 
            {
            RA1=0;       
            RA2=1;
            __delay_ms(5000);
             RA2=0;
            }
        else if (comp>0) {RA1=1;}  
    }
}
