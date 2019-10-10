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

//Variables//
volatile char Buffer[14];

//Funciones//
void interrupt Recept (void);

void interrupt Recept (void)
{
    static char i=0; 
    
    Buffer[i]=RCREG;
    if(++i==14)
        i=0;
    else;
}

void main (void)
{
     //Variables Locales//
    /*char ContraAsiic [3][12]={
                                {'0','A','0','0','6','D','F','8','C','4','5','B'},
                                {'0','A','0','0','6','D','7','A','B','D','A','0'},
                                {'0','C','0','0','4','1','D','C','8','9','1','8'}
                            };*/
    char ContraHex[2][14]=   {
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                            };
    /*char ContraHex[3][14]=   {
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                                {0x02,0x30,0x43,0x30,0x30,0x34,0x31,0x44,0x43,0x38,0x39,0x31,0x38,0x03}
                            };*/
    int comp=0;
    //Configuraci�n Puertos//
    TRISA=0x00;

    
    //Configuraci�n EUSART//
    CREN=1;
    SYNC=0;
    SPEN=1; 
    
    //Configuraci�n Baudios//
    BRGH=1;
    BRG16=0;
    SPBRG=25;
    
    //Cnfiguraci�n Interrupci�n EUSART//
    GIE=1;
    PEIE=1;
    RCIE=1;
    
    //Configuraci�n del Oscilador//
    OSCCON=0b01101000; //4Mhz
    
    while (1)
    {
          comp=strcmp( ContraHex[2], Buffer);
          if(comp<=0) 
            {
              RA2=1;
              RA1=0;
            }
        else if (comp>=0) {RA1=1;RA2=0;}  
    }
 }
  