#include <io.h>
#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 
char key= '0';
float total = 0;
int state = 0;
char Buf[16];


int row ;
int col;
char scan [4] = {0XFE,0XFD,0XFB,0XF7};

char list [10][16] = { "0- crisp" , "1- water" , "2- pepsi" , "3- coca" , "4- chips" , "5- crisp" , "6- soda" , "7- cold tea" , "8- Ice cream" , "9- pop corn"};
float price[10] = {3 , 1.5 , 2 , 2.5 , 2 , 4 , 1 , 5 , 4.5 , 2};
char keypad [4][4] = { {'7','8','9',' '},{'4','5','6',' '},{'1','2','3','-'},{'c','0','=','+'}};      
char Data=0;
char Data2=0;
char Seven_Segment(char Input_Data){
 char K;
 switch (Input_Data){
 case 0: K=0x7E; return K; break;
 case 1: K=0x0C; return K; break;
 case 2: K=0xB6; return K; break;
 case 3: K=0x9E; return K; break;
 case 4: K=0xCC; return K; break;
 case 5: K=0xDA; return K; break;
 case 6: K=0xFA; return K; break;
 case 7: K=0x0E; return K; break;
 case 8: K=0xFE; return K; break;
 case 9: K=0xDE; return K; break;
 default: K=0x00; return K; break;} }
char key_pad(){

        while(1){
            for(row=0; row <=3; row++){
            
                PORTB = scan[row];
                
                col = 5;
                
                if(PINB.4 ==0){
                    col = 0;
                }
                if(PINB.5 ==0){
                    col = 1;
                }
                if(PINB.6 ==0){
                    col = 2;
                }
                if(PINB.7 ==0){
                    col = 3;
                }
              
                
                if(col != 5){ 

                 delay_ms(250);    
                  return keypad[row][col];
                }   
            }      
   }
    
}
int result(){
                    lcd_clear();
                     lcd_gotoxy(0,0);
                     lcd_puts("Total cost :");
                     lcd_gotoxy(0,1);
                     sprintf(Buf,"%.1f $", total); 
                     lcd_puts(Buf);
                     return 1;
}
void newState(){
    lcd_clear();
    lcd_gotoxy(0,0);
    
    lcd_puts(list[state]);
    lcd_gotoxy(0,1); 
    sprintf(Buf,"%.1f $", price[state]);
    lcd_puts(Buf);

}
int checking(){

     if(key == '='){
            return result();                    
     }
     else if(key == 'c'){
            
             total += price[state];
             Data++;
             if(Data == 10){
                Data = 0;
                Data2++;
             }
                 PORTC=Seven_Segment(Data);
                 PORTD=Seven_Segment(Data2);
     }
     else if(key == '+'){
        state++;
        if (state == 10){
            state = 0;
        }
        newState();
     }
     else if(key == '-'){
        state--;
        if (state == -1){
            state = 9;
        }      
        newState();
     }
     else if(key >= '0' && key <= '9'){
        state = key - '0' ;    
        newState();
     }
    else{
    lcd_clear();
    lcd_gotoxy(0,0);
    
    lcd_puts(list[state]);
    lcd_gotoxy(0,1); 
    sprintf(Buf,"%.1f $", price[state]);
    lcd_puts(Buf);
 
    }  
    
    

}    
void main(){


DDRB = 0x0F;
DDRC=0xFF;
PORTC=0x00;
DDRD=0xFF;
PORTD=0x00;

 
 lcd_init(16);
 lcd_clear();
PORTC=Seven_Segment(Data); 
 PORTD=Seven_Segment(Data2);
 while(1){
 checking();               
 key = key_pad();
 
 }
 }
