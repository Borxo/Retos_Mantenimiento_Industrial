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

void main (void)
{   
    //Variables Locales//
    char ContraAsiic [3][12]{
                                {'0','A','0','0','6','D','F','8','C','4','5','B'},
                                {'0','A','0','0','6','D','7','A','B','D','A','0'},
                                {'0','C','0','0','4','1','D','C','8','9','1','8'}
                            };
    char ContraHex[3][14]   {
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x02,0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03},
                                {0x02,0x30,0x43,0x30,0x30,0x34,0x31,0x44,0x43,0x38,0x39,0x31,0x38,0x03}
                            };
    
    while(1)
    {
        
    }
}
