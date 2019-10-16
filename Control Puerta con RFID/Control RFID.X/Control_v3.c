/*
 * Programa: Control_RFID. 
 * Microcontrolador: PIC16F1936.
 * Autor: Borxo García.
 * Versión:1.0v.
 */

//Palabras de configuración
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
volatile char Buffer[13];
volatile int U=0;

//Funciones//
void interrupt Recept (void);
void comprarar (char Contra[]);

void interrupt Recept (void)
{
    static char i=0; 
    static char Flag=0;
    
    if (Flag==0)
    {
    while(RCREG==0x02);
    Flag=1;
    }    
    if (Flag==1)
    {
        Buffer[i]=RCREG;
        TXREG=Buffer[i];
        if(++i==13)
        {
        i=0;
        Flag=0;
        U=1;
        }
        else;
    }
}

void main (void)
{
     //Variables Locales//
    /*char ContraAsiic [3][12]={
                                {'0','A','0','0','6','D','F','8','C','4','5','B'},
                                {'0','A','0','0','6','D','7','A','B','D','A','0'},
                                {'0','C','0','0','4','1','D','C','8','9','1','8'}
                            };*/
    /*char ContraHex[2][14]=   {
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                            };*/
    char ContraHex[2][13]=   {
                                {0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                            };
    /*char ContraHex[3][14]=   {
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                                {0x02,0x30,0x43,0x30,0x30,0x34,0x31,0x44,0x43,0x38,0x39,0x31,0x38,0x03}
                            };*/
    int comp=0;
    //char com1[14]={0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03};
    char com2[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    //Configuración Puertos//
    TRISA=0x00;
    
    //Configuración EUSART//
    CREN=1;
    SYNC=0;
    SPEN=1; 
    
    //Configuración Baudios//
    BRGH=1;
    BRG16=1;
    SPBRG=103;
    TXEN = 1;
    
    //Cnfiguración Interrupción EUSART//
    GIE=1;
    PEIE=1;
    RCIE=1;
    
    //Configuración del Oscilador//
    OSCCON=0b01101000; //4Mhz

    while (1)
    {
        if (Busqueda()==0)
        {
            PORTA=0b00000001;
            __delay_ms(1000);
        }
        
        else if(Busqueda()==1)
        {
            PORTA=0b00000010;
            __delay_ms(3000);
        }
    }
}

int Busqueda ()
{   
    int comp=0;
    int y=0;
    char ContraHex[2][13]=   {
                                {0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                            };
    PORTA=0x00; 
    
    //memset(Buffer,'\0',13);
    U=0;
    while(U==0);
    
    while(comp!=0 && y==2)
    {
       comp=strncmp ( ContraHex[y], Buffer,13); 
       y++;
    }
    
    if(comp==0)
    {
        return (1);
    }
    else return (0);
    
}