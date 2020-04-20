#include "RIMS.h"
volatile int TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}

enum SM1_STATES { SM1_SMStart, SM1_Move, SM1_Stop, SM1_init} SM1_STATE;
void Tick_AMAZONBELT() { 
   switch(SM1_STATE) { 
      case SM1_SMStart:
         if (1) {
            SM1_STATE = SM1_init;
         }
         break;
      case SM1_Move:
         if (!A0) {
            SM1_STATE = SM1_Move;
         }
         else if (A0 ) {
            SM1_STATE = SM1_Stop;
         }
         else {
            SM1_STATE = SM1_Move;
         }
         break;
      case SM1_Stop:
         if (!A0) {
            SM1_STATE = SM1_Move;
         }
         else if (A0 ) {
            SM1_STATE = SM1_Stop;
         }
         else {
            SM1_STATE = SM1_Stop;
         }
         break;
      case SM1_init:
         if (A1) {
            SM1_STATE = SM1_Move;
         }
         else {
            SM1_STATE = SM1_init;
         }
         break;
      default:
         SM1_STATE = SM1_init;
         break;
   }
   switch(SM1_STATE) { 
      case SM1_SMStart:
         
         break;
      case SM1_Move:
         B0 = 0;
         break;
      case SM1_Stop:
         B0 = 1;
         break;
      case SM1_init:
         
         break;
   }
}

int main(){
   int AMAZONBELTElapsedTime = 1000;
   int periodGCD = 1000;
   TimerSet(periodGCD);
   TimerOn();
   while(1){
      if (AMAZONBELTElapsedTime >= 1000){
         Tick_AMAZONBELT();
         AMAZONBELTElapsedTime = 0;
      }
      AMAZONBELTElapsedTime += 1000;
      while(!TimerFlag);
      TimerFlag=0;
   }
}

