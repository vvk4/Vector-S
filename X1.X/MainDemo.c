
#include <math.h>
#include "Mn.h"
#include <xc.h>


/*
    void __attribute__((interrupt, auto_psv)) _DefaultInterrupt(void)
    {
  
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }

    void __attribute__((interrupt, auto_psv)) _OscillatorFail(void)
    {
  
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }
    void __attribute__((interrupt, auto_psv)) _AddressError(void)
    {
  
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }
    void __attribute__((interrupt, auto_psv)) _StackError(void)
    {
  
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }
    void __attribute__((interrupt, auto_psv)) _MathError(void)
    {
      
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }

*/

#define GreenLed  LATJbits.LATJ10
#define TRISGreenLed  TRISJbits.TRISJ10




int main(void)
{

}
        InitSegAll();
//        while (1);

    MyTimeOut=500;
while (MyTimeOut);


    Nop();
    Nop();
    Nop();
//    while (1)

   KEY_BT=1;
    Nop();
    Nop();
    Nop();
    HvReplyHC05=0;
    MyTimeOut=550;
    AT_Rec=1;
TrmHC05_AT("AT",sizeof("AT"));//AT+NAME=RoboWell
while ((!HvReplyHC05)&&(MyTimeOut));
    AT_Rec=0;

   KEY_BT=0;

       Hv_HC05=0;


   if (MyTimeOut)
{
        Hv_HC05=1;
        
        ANSELBbits.ANSB4=0;//MY MY MY MY MY
        ANSELBbits.ANSB0=0;//MY MY MY MY MY
        ANSELEbits.ANSE9=0;//MY MY MY MY MY

while (1)
    {
    Nop();
        StateIndicator();
        WrOdmtr();
        writeFlash();
        WriteErrors();
        ReceiveUDP();
        //TrmErrorsHC05();
        Rbw();
        GetRbw();
        DataFrmBMS();
        ErrorSound();
        CountSpd();
        if (MustTrmHC05)
        {
        MustTrmHC05=0;
        TrmHC05(HC05TrmMass);
        }
        PrepareBMSPacket();
        Dbg();
        TrmSteer();

    }
}
else
    CloseU4();


        while (1)
                    DataFrmBMS();

}
