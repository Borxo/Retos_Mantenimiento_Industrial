/*
 * Programa: Control_RFID. 
 * Microcontrolador: PIC16F1936.
 * Autor: Borxo García.
 * Versión:1.3v.
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

//Función de Interrupción//
void interrupt Recept (void)
{   
    //Variables de la Interrupción//
    static char i=0;  
    static char Flag=0;
    
    if (Flag==0)         //Espera a que llegue el bit de inicio.
    {
    while(RCREG==0x02);
    Flag=1;              //Cuando llega pone a uno Flag.
    }    
    if (Flag==1)        
    {
        Buffer[i]=RCREG;  //Guarda los datos del registro RCREG en un Buffer. 
        if(++i==13)       //Cuando todos los datos se han guardado.
        {                  
        i=0;              //Se reinicia la variable i y el flag.
        Flag=0;          
        U=1;              //Se pone la variable U.
        }
        else;
    }
}

void main (void)
{
    //Configuración Puertos//
    TRISC7=1; //Pin Recepción EUSART.
    TRISC4=0; //Led Rojo.
    TRISC5=0; //Led verde y cerradura.
    //Configuración EUSART para recepción//
    CREN=1;
    SYNC=0;
    SPEN=1; 
    
    //Configuración Baudios 9600(16bits)//
    BRGH=1;
    BRG16=1;
    SPBRG=103;
    
    //Cnfiguración Interrupción EUSART//
    GIE=1;
    PEIE=1;
    RCIE=1;
    
    //Configuración del Oscilador//
    OSCCON=0b01101000; //4Mhz

    while (1)
    {
        if (Busqueda()==0)      //Si el valor devuelto de la función es 0.
        {
            PORTC=0b00010000;   //Activa el pin RC4.
            __delay_ms(3000);   //Espera 3 Segundos. 
            PORTC=0x00;         //Pone a 0 el puerto C.
        }
        
        else if(Busqueda()==1)  //Si el valor devuelto de la función es 1.
        {
            PORTC=0b00100000;  //Activa el pin RC5.
            __delay_ms(3000);  //Espera 3 Segundos.
            PORTC=0x00;        //Pone a 0 el puerto C.  
        }
    }
}

int Busqueda ()
{   
    //Variables locales//
    int comp=0;
    int x=0;
    char ContraHex[2][13]=   {          //Almacen de claves que activan la cerradura.
                                {0x30,0x41,0x30,0x30,0x36,0x44,0x46,0x38,0x43,0x34,0x35,0x42,0x03},
                                {0x30,0x41,0x30,0x30,0x36,0x44,0x37,0x41,0x42,0x44,0x41,0x30,0x03}
                            };
    U=0;         //Reinicia la variable U.
    while(U==0); //Espera a que se recogan todos los datos de la EUSART.
    do {         //Compara las cadenas almacenadas con la cadena del buffer.
           comp=strncmp ( ContraHex[x], Buffer,13);
           if(++x==2)x=0;
        } while(comp!=0 && x>0); // Si existe la clave pone comp=0 y sino un
                                 // numero mayor que 0.
    if(comp==0)                  //Si comp==0 devuelve un 1. 
    {                            
        return (1);
    }
    else return (0);             //Si es distinto a 0 devuelve un 0.
    
}