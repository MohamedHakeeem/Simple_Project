
#include <xc.h>
#include "LCD.h"
#include "config.h"
#include"stdint.h"

/*DC motor control*/
#define REV RD2
#define LV1 RD3
#define Stepper_mode RD4
#define LV3 RD5
#define LV4 RD6


void PWM_DEGREE(uint16_t  DC);

/*Stepper motor control*/   
unsigned char i=0;  
#define step TRISA
#define out PORTA

  

void Step_Right_Angle(uint8_t angle);
void Step_Left_Angle(uint8_t angle);

void main(void) {
 
 /******In lcd , we use PORTB as output and opreatin pins are i range[0:5]***********/
  LCD_Init();
  LCD_Clear();
  LCD_Set_Cursor(1,5); 
  LCD_Write_String("Simple_Control");
 
    
  /*********initialization and configuration of pwm*************/
   TRISD=0xFC;
   TRISD0=0;
   TRISD1=0;

   RD0=1;
   RD1=0; 

   CCP1M3=1;
   CCP1M2=1;
   TRISC2=0;
   TMR2ON=1;
   T2CKPS0=1;
   T2CKPS1=0;
   PR2=124;
   
   PWM_DEGREE(0);
   
   /*stepper control*/
   step=0x00;
   out=0x00;
  
  while(1)
  {
     
      if(REV ==1)
       {
          
          RD0= ~RD0;
          RD1= ~RD1;
         
          LCD_Clear(); 
          LCD_Set_Cursor(1,5);
          LCD_Write_String("Motor_Reversed");
          __delay_ms(200);  
       }
     
      if(LV1 == 1)
       {
           PWM_DEGREE(0);
          
            LCD_Clear(); 
            LCD_Set_Cursor(1,5);
            LCD_Write_String("DC_Stopped");
          __delay_ms(5);
          
       }
      
       
       if(Stepper_mode == 1)
       {
            Step_Right_Angle(30);
       
            LCD_Clear(); 
            LCD_Set_Cursor(1,5);
            LCD_Write_String("Stepper_mode");
            __delay_ms(5);
       }
 
       if(LV3 == 1)
       {
           PWM_DEGREE(250);
           
            LCD_Clear(); 
            LCD_Set_Cursor(1,5);
            LCD_Write_String("low_Speed");
         __delay_ms(5);
       }
 
       
   
      if(LV4 == 1)
       {
           
          PWM_DEGREE(500);
         
           LCD_Clear(); 
           LCD_Set_Cursor(1,5);
           LCD_Write_String("High_Speed");
          
          __delay_ms(5);
       }
     
 
              
      
         
       __delay_ms(50);
      
  }
        return;
        
}


void PWM_DEGREE(uint16_t  DC)
{
    if(DC<1024)
    {
    CCP1Y=DC & 1;
    CCP1X=DC & 2;
    CCPR1L=DC >> 2;
    }
}

void Step_Right_Angle(uint8_t angle)
{
    uint8_t no_step=0;
    no_step=((angle*48)/360) ;
     for(int j=0;j<no_step;j++)
        {
            out=(1<<i);
            i++;
        __delay_ms(50);
        if(i==4)i=0;
        
        } 
    
    
    
    
}

void Step_Left_Angle(uint8_t angle)
{
    uint8_t no_step=0;
    no_step=((angle*48)/360) ;
    
    
    for(int j=0 ,i =0;j< no_step;j++)
      {
            out=(8>>i);
            i++;
            __delay_ms(50);
            if(i==4)i=0;
            
            
  
     }
    
    
    
}
