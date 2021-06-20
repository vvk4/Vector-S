#include <p33Exxxx.h>

#define Version     0x406////30.10.2020




#define VECTOR
#define VECTORMS
#define VECTORS
//#define SERVICE
//#define BUZZER_WITH_GENERATOR


//#define _5V_TST

#define VECTOR_MPU_6000
#define BLE
////////////////////////////////////////#define CHAGER_VIA_MOTOR_VECTOR_M2

//#define SENSORLESS_TEST

//#define NO_UBT
//#define  SIN_MIDDLE 
//#define MPU6050
#define MPU6500////////////////////////////////////////
////////////////////////////////////////#define LSM6DS33
#if !definedPhasePERMASS_DEF VECTOR
#define ISOLATED
#endif
//#define INT_FRC
//#define PROTECT
//#define TEST_PWM_KEYS
#define SEL_SENSOR_ORDER   //MUST BE ALWAYS
#define REV2
#define DIRMOTOR

//#define INDICATOR
//#define IND_8
//#define IND_10
//#define BMS

//#define U_2_2k



//#define TST_PIN        LATFbits.LATF13
//#define TRIS_TST_PIN   TRISFbits.TRISF13     



/*
#define V_MIN_OFF   2100
#define V_MIN_Pre_OFF   2300
#define V_MIN_Sound 2900
#define V_min_OverV 3900
 */

#define CURRMASS_SIZE   64
#define CURRMASS_SHIFT  6



#define FLASHMASS_SIZE 243 //(MAX 240)
#define MassTMPSIZE 1000



#define FCY  60000000	 // xtal = 8Mhz; with PLL -> 60 MIPS
#define FPWM 20000		 // 20 kHz, so that no audible noise is present.

#define TRIS_ALARM_LED  TRISGbits.TRISG13
#define ALARM_LED       LATGbits.LATG13

#define TRIS_MODE_LED   TRISGbits.TRISG15
#define MODE_LED        LATGbits.LATG15

//-----------------------------------------------------------------------------------------------------
//BLDC 1
#if !defined VECTOR
#define TRIS_DS         TRISAbits.TRISA6
#define DS              LATAbits.LATA6
#define ANSEL_DS        ANSELAbits.ANSA6
#endif

//A:

#define TRIS_PWM1_A_H   TRISEbits.TRISE1    //AN25
#define PWM1_A_H        LATEbits.LATE1
#define ANSEL_PWM1_A_H  ANSELEbits.ANSE1
#define PEN1_A_H        IOCON1bits.PENH


#define TRIS_PWM1_A_L   TRISEbits.TRISE0    //AN24
#define PWM1_A_L        LATEbits.LATE0
#define ANSEL_PWM1_A_L  ANSELEbits.ANSE0
#define PEN1_A_L        IOCON1bits.PENL

//B:

#define TRIS_PWM1_B_H   TRISEbits.TRISE3    //AN27
#define PWM1_B_H        LATEbits.LATE3
#define ANSEL_PWM1_B_H  ANSELEbits.ANSE3
#define PEN1_B_H        IOCON2bits.PENH


#define TRIS_PWM1_B_L   TRISEbits.TRISE2    //AN26
#define PWM1_B_L        LATEbits.LATE2
#define ANSEL_PWM1_B_L  ANSELEbits.ANSE2
#define PEN1_B_L        IOCON2bits.PENL


//C:

#define TRIS_PWM1_C_H   TRISEbits.TRISE5    //AN29
#define PWM1_C_H        LATEbits.LATE5
#define ANSEL_PWM1_C_H  ANSELEbits.ANSE5
#define PEN1_C_H        IOCON3bits.PENH



#define TRIS_PWM1_C_L   TRISEbits.TRISE4    //AN28
#define PWM1_C_L        LATEbits.LATE4
#define ANSEL_PWM1_C_L  ANSELEbits.ANSE4
#define PEN1_C_L        IOCON3bits.PENL


//HALL:
#define TRIS_Hall1_A    TRISFbits.TRISF3
#define Hall1_A         PORTFbits.RF3
#define CNEN_Hall1_A    CNENFbits.CNIEF3

#define TRIS_Hall1_B    TRISFbits.TRISF2
#define Hall1_B         PORTFbits.RF2
#define CNEN_Hall1_B    CNENFbits.CNIEF2

#define TRIS_Hall1_C    TRISFbits.TRISF5
#define Hall1_C         PORTFbits.RF5
#define CNEN_Hall1_C    CNENFbits.CNIEF5

#if defined VECTORMS

#define TRIS_ChagerOut    TRISGbits.TRISG0
#define ChagerOut         LATGbits.LATG0
#define TRIS_ChagerIn     TRISGbits.TRISG1
#define ChagerIn          PORTGbits.RG1
#define CNPU_ChagerIn     CNPUGbits.CNPUG1
#endif



//BLDC 1 END

#if !defined REV2

#define TRIS_But1       TRISBbits.TRISB10
#define But1            PORTBbits.RB10
#define ANSEL_But1      ANSELBbits.ANSB10
#define CNPU_But1       CNPUBbits.CNPUB10


#define TRIS_But2       TRISBbits.TRISB11
#define But2            PORTBbits.RB11
#define ANSEL_But2      ANSELBbits.ANSB11
#define CNPU_But2       CNPUBbits.CNPUB11

#define TRIS_But3       TRISBbits.TRISB14
#define But3            PORTBbits.RB14
#define ANSEL_But3      ANSELBbits.ANSB14
#define CNPU_But3       CNPUBbits.CNPUB14


#define TRIS_But4       TRISBbits.TRISB15
#define But4            PORTBbits.RB15
#define ANSEL_But4      ANSELBbits.ANSB15
#define CNPU_But4       CNPUBbits.CNPUB15


#define TRIS_But5       TRISBbits.TRISB0
#define But5            PORTBbits.RB0
#define ANSEL_But5      ANSELBbits.ANSB0
#define CNPU_But5       CNPUBbits.CNPUB0
#else


#define TRIS_But2       TRISBbits.TRISB10
#define But2            PORTBbits.RB10
#define ANSEL_But2      ANSELBbits.ANSB10
#define CNPU_But2       CNPUBbits.CNPUB10


#define TRIS_But3       TRISBbits.TRISB11
#define But3            PORTBbits.RB11
#define ANSEL_But3      ANSELBbits.ANSB11
#define CNPU_But3       CNPUBbits.CNPUB11



#if defined VECTOR
#define TRIS_But1       TRISBbits.TRISB4
#define But1            PORTBbits.RB4
#define ANSEL_But1      ANSELBbits.ANSB4
#define CNPU_But1       CNPUBbits.CNPUB4
#else
#define TRIS_But1       TRISBbits.TRISB0
#define But1            PORTBbits.RB0
#define ANSEL_But1      ANSELBbits.ANSB0
#define CNPU_But1       CNPUBbits.CNPUB0
#endif




#define TRIS_But4       TRISDbits.TRISD15
#define But4            PORTDbits.RD15
#define CNPU_But4       CNPUDbits.CNPUD15

#endif

#define TRISBuzzer      TRISFbits.TRISF4
#if defined BUZZER_WITH_GENERATOR
#define Buzzer          LATFbits.LATF4
#else
#define BuzzerNoGenerator  LATFbits.LATF4
#endif

#if !defined REV2
#define TRISLight       TRISFbits.TRISF8
#define Light           LATFbits.LATF8
#endif

#if !defined VECTORS
#if defined REV2
#if defined VECTOR
#define TRISHorn       TRISDbits.TRISD10
#define Horn           LATDbits.LATD10
#define ANSELHorn      ANSELDbits.ANSD10
#else
#define TRISHorn       TRISFbits.TRISF8
#define Horn           LATFbits.LATF8
#endif
#else
#define TRISHorn        TRISAbits.TRISA2
#define Horn            LATAbits.LATA2
#endif
#else
#define TRISHorn       TRISFbits.TRISF1
#define Horn           LATFbits.LATF1
#endif

#define TRISSpd1Sensor  TRISAbits.TRISA3
#define Spd1Sensor      PORTAbits.RA3

#define TRISSpd2Sensor  TRISAbits.TRISA4
#define Spd2Sensor      PORTAbits.RA4

#define TRIS_Break1     TRISDbits.TRISD12
#define Break1          PORTDbits.RD12
#define CNPU_Break1     CNPUDbits.CNPUD12

#define TRIS_Break2     TRISDbits.TRISD3
#define Break2          PORTDbits.RD3
#define CNPU_Break2     CNPUDbits.CNPUD3

#define TRISRight       TRISDbits.TRISD4
#define RightPort       LATDbits.LATD4

#define TRISLeft       TRISDbits.TRISD5
#define LeftPort       LATDbits.LATD5

#define TRIS_PAS        TRISAbits.TRISA7
#define PAS             PORTAbits.RA7
#define ANSEL_PAS       ANSELAbits.ANSA7

#if !defined VECTOR
//Flash I/O pins
#if !defined ISOLATED
#define CE_FLASH            LATDbits.LATD10
#define TRIS_CE_FLASH       TRISDbits.TRISD10

#define SO_FLASH            PORTDbits.RD9
#define TRIS_SO_FLASH       TRISDbits.TRISD9

#define WP_FLASH            LATDbits.LATD8
#define TRIS_WP_FLASH       TRISDbits.TRISD8


#define SI_FLASH            LATAbits.LATA15
#define TRIS_SI_FLASH       TRISAbits.TRISA15

#define SCK_FLASH           LATAbits.LATA14
#define TRIS_SCK_FLASH      TRISAbits.TRISA14

#define HOLD_FLASH            LATAbits.LATA5
#define TRIS_HOLD_FLASH       TRISAbits.TRISA5
#else
#define CE_FLASH            LATAbits.LATA3
#define TRIS_CE_FLASH       TRISAbits.TRISA3

#define SO_FLASH            PORTAbits.RA2
#define TRIS_SO_FLASH       TRISAbits.TRISA2

#define WP_FLASH            LATDbits.LATD8
#define TRIS_WP_FLASH       TRISDbits.TRISD8


#define SI_FLASH            LATAbits.LATA15
#define TRIS_SI_FLASH       TRISAbits.TRISA15

#define SCK_FLASH           LATAbits.LATA14
#define TRIS_SCK_FLASH      TRISAbits.TRISA14

#define HOLD_FLASH            LATAbits.LATA5
#define TRIS_HOLD_FLASH       TRISAbits.TRISA5

#endif
//Flash I/O pins END
#else
#define CE_FLASH            LATAbits.LATA3
#define TRIS_CE_FLASH       TRISAbits.TRISA3

#define SO_FLASH            PORTAbits.RA2
#define TRIS_SO_FLASH       TRISAbits.TRISA2

#define WP_FLASH            LATDbits.LATD8
#define TRIS_WP_FLASH       TRISDbits.TRISD8


#define SI_FLASH            LATAbits.LATA15
#define TRIS_SI_FLASH       TRISAbits.TRISA15

#define SCK_FLASH           LATAbits.LATA14
#define TRIS_SCK_FLASH      TRISAbits.TRISA14

#define HOLD_FLASH            LATAbits.LATA5
#define TRIS_HOLD_FLASH       TRISAbits.TRISA5

#endif



// Gyro I/O pins

#define GYRO_SCK_TRIS			(TRISDbits.TRISD2)  //RP66
#define GYRO_SCK_RPOR                   RPOR1bits.RP66R

#define GYRO_dsPICSDO_TRIS      	(TRISDbits.TRISD1)  //RP65
#define GYRO_dsPICSDO_RPOR              RPOR0bits.RP65R

#define GYRO_dsPICSDI_TRIS		(TRISCbits.TRISC14)  //RPI62
#define GYRO_dsPICSDI_RPINR             62
#define GYRO_dsPICSDI_ANSEL             ANSELCbits.ANSC14

#if !defined LSM6DS33
#if defined MPU6500
#define GYRO_CS_TRIS			(TRISDbits.TRISD7)
#define GYRO_CS_IO			(LATDbits.LATD7)
#define GYRO_CS_ANSEL                   ANSELDbits.ANSD7


#define GYRO_CS2_TRIS			(TRISDbits.TRISD6)
#define GYRO_CS2_IO              (LATDbits.LATD6)
#define GYRO_CS2_ANSEL           (ANSELDbits.ANSD6)



#else
#define GYRO_CS_TRIS			(TRISCbits.TRISC13)
#define GYRO_CS_IO			(LATCbits.LATC13)
#define GYRO_CS_ANSEL                   ANSELCbits.ANSC13



#endif
#else
#define GYRO_CS_TRIS			(TRISDbits.TRISD6)
#define GYRO_CS_IO              (LATDbits.LATD6)
#define GYRO_CS_ANSEL           (ANSELDbits.ANSD6)


#define GYRO_CS1_TRIS			(TRISDbits.TRISD7)
#define GYRO_CS1_IO			(LATDbits.LATD7)
#define GYRO_CS1_ANSEL                   ANSELDbits.ANSD7


#endif




#define Gyro_DRDY_TRIS                   (TRISDbits.TRISD0)
#define Gyro_DRDY_IO			(LATDbits.LATD0)

#define GYRO_INT1_TRIS			(TRISDbits.TRISD11)
#define GYRO_INT1_IO			(PORTDbits.RD11)

#define GYRO_INT_EDGE			(INTCON2bits.INT3EP)
#define GYRO_INT_IE			(IEC3bits.INT3IE)
#define GYRO_INT_IF			(IFS3bits.INT3IF)
#define GYRO_SSPBUF			(SPI3BUF)
#define GYRO_SPISTAT			(SPI3STAT)
#define GYRO_SPISTATbits		(SPI3STATbits)
#define GYRO_SPICON1			(SPI3CON1)
#define GYRO_SPICON1bits		(SPI3CON1bits)
#define GYRO_SPICON2			(SPI3CON2)
#define GYRO_SPI_IE			(IEC5bits.SPI3IE)
//#define GYRO_SPI_IP			(IPC22bits.SPI3IP)
#define GYRO_SPI_IF			(IFS5bits.SPI3IF)


// Gyro I/O pins  END



// Accel I/O pins

#if !defined VECTORMS
#define ACC_SCK_TRIS			(TRISGbits.TRISG0)  //RP66
#define ACC_SCK_RPOR                    RPOR12bits.RP112R
#define ACC_dsPICSDO_TRIS               (TRISGbits.TRISG1)  //RP65
#define ACC_dsPICSDO_RPOR               RPOR13bits.RP113R
#endif
#define ACC_dsPICSDI_TRIS		(TRISFbits.TRISF1)  //RPI72
#define ACC_dsPICSDI_RPINR              97

#define ACC_CS_TRIS			(TRISFbits.TRISF0)
#define ACC_CS_IO			(LATFbits.LATF0)

#define ACC_INT1_TRIS			(TRISDbits.TRISD7)
#define ACC_INT1_IO			(PORTDbits.RD7)

//#define ACC_INT2_TRIS			(TRISDbits.TRISD13)
//#define ACC_INT2_IO			(PORTDbits.RD13)


//#define ACC_INT_EDGE			(INTCON2bits.INT4EP)
//#define ACC_INT_IE			(IEC3bits.INT4IE)
//#define ACC_INT_IF			(IFS3bits.INT4IF)
#define ACC_SSPBUF			(SPI4BUF)
#define ACC_SPISTAT			(SPI4STAT)
#define ACC_SPISTATbits		(SPI4STATbits)
#define ACC_SPICON1			(SPI4CON1)
#define ACC_SPICON1bits		(SPI4CON1bits)
#define ACC_SPICON2			(SPI4CON2)
#define ACC_SPI_IE			(IEC7bits.SPI4IE)
//#define ACC_SPI_IP			(IPC22bits.SPI3IP)
#define ACC_SPI_IF			(IFS7bits.SPI4IF)

//-------------------------------------------------------------------------------------------
#define MAX_TiltYAV 32//64
#define MAX_TiltYAV_SHIFT 5//6



#if defined REV2
#define BuzzerMacroOn			BzFuncOn();
//#define BuzzerMacroOn			{Buzzer=1; if (BuzzAndHorn) Horn=1;}
#if !defined VECTOR
#if !defined ISOLATED
#define BuzzerMacroOff			{Buzzer=0; Horn=0;}
#else
#define BuzzerMacroOff			{Buzzer=0; Horn=1;}
#endif
#else
#if !defined VECTORS
#define BuzzerMacroOff			{Buzzer=0; {if (!LightOn) Horn=1;}}
#else
//#define BuzzerMacroOff			{Buzzer=0; {if (!LightOn) Horn=0;}}
#define BuzzerMacroOff			{Buzzer=0; {if (!LightOn&&!KeyLightStop) OC3R=0;}}
#endif
#endif

#else
#define BuzzerMacroOn			{Buzzer=1; if (BuzzAndHorn) Horn=1;}
#define BuzzerMacroOff			{Buzzer=0; Horn=0;}
#endif

typedef union {
    unsigned long int Flags;

    struct {
        unsigned int Fl0 : 1;
        unsigned int Fl1 : 1;
        unsigned int Fl2 : 1;
        unsigned int Fl3 : 1;
        unsigned int Fl4 : 1;
        unsigned int Fl5 : 1;
        unsigned int Fl6 : 1;
        unsigned int Fl7 : 1;
        unsigned int Fl8 : 1;
        unsigned int Fl9 : 1;
        unsigned int Fl10 : 1;
        unsigned int Fl11 : 1;
        unsigned int Fl12 : 1;
        unsigned int Fl13 : 1;
        unsigned int Fl14 : 1;
        unsigned int Fl15 : 1;
        unsigned int Fl16 : 1;
        unsigned int Fl17 : 1;
        unsigned int Fl18 : 1;
        unsigned int Fl19 : 1;
        unsigned int Fl20 : 1;
        unsigned int Fl21 : 1;
        unsigned int Fl22 : 1;
        unsigned int Fl23 : 1;
        unsigned int Fl24 : 1;
        unsigned int Fl25 : 1;
        unsigned int Fl26 : 1;
        unsigned int Fl27 : 1;
        unsigned int Fl28 : 1;
        unsigned int Fl29 : 1;
        unsigned int Fl30 : 1;
        unsigned int Fl31 : 1;
    };
} FLAGS;



#define Transmitting_U3         Flgs.Fl0
#define GettingPacketU3_FL      Flgs.Fl1
#define CHK_Err_U3              Flgs.Fl2
#define HvDataPacketU3_FL       Flgs.Fl3
#define FindGyroVertical        Flgs.Fl4
#define MustTrm                 Flgs.Fl5
#define Forward1                Flgs.Fl6
#define SendingMass             Flgs.Fl7
#define StartingTiltX           Flgs.Fl8
#define PrevForward1            Flgs.Fl9
#define PrevForward2            Flgs.Fl10
#define NoBalance               Flgs.Fl11
#define PWM1Plus                Flgs.Fl12
#define HvAccData               Flgs.Fl13
#define HvGyroData              Flgs.Fl14
#define Starting                Flgs.Fl15
#define CalibrateGyro           Flgs.Fl16
#define CalibrateAcc            Flgs.Fl17
#define MustTrmFlashMass        Flgs.Fl18
#define TiltXPlus               Flgs.Fl19
#define SendPhase               Flgs.Fl20
//#define SendingMassB            Flgs.Fl21
#define TakingPacketUbat        Flgs.Fl22
#define HvPacketUBat            Flgs.Fl23
//#define SendingMass400          Flgs.Fl24
#define CanSensor1              Flgs.Fl25
#define CanSensor2              Flgs.Fl26
#define HvSpd1                  Flgs.Fl27
#define SpeedControlPID         Flgs.Fl28
#define MeasuringSpd1           Flgs.Fl29
#define StrongMode              Flgs.Fl30
//#define SendingMassC            Flgs.Fl31


//#define SendingNeutral          Flgs1.Fl0
#define ChagerViaMotor          Flgs1.Fl1
#define OffingBreak             Flgs1.Fl2
#define OdometrErased           Flgs1.Fl3
#define TemperatureFl           Flgs1.Fl4
#define StartingMove            Flgs1.Fl5
#define RecOdometrFl            Flgs1.Fl6
#define But4Pressed             Flgs1.Fl7
#define ButBPressed             Flgs1.Fl8
#define HvBt4                   Flgs1.Fl9
#define HvSpd1_PID              Flgs1.Fl10
#define Drebezg4                Flgs1.Fl11
#define StrtPID_On              Flgs1.Fl12
#define HvToChangeNumSpdLimFl   Flgs1.Fl13
#define Bt4Up                   Flgs1.Fl14
#define PWM_Minus               Flgs1.Fl15
#define BreakPressed            Flgs1.Fl16
#define DirPWM1Mem              Flgs1.Fl17
#define HvToPrg                 Flgs1.Fl18
#define HvToWriteFlash          Flgs1.Fl19
#define WriteErr_Fl             Flgs1.Fl20
#define NoValidTilt             Flgs1.Fl21
#define FlgPID                  Flgs1.Fl22
#define ErrorTiltFl             Flgs1.Fl23
#define Starting2               Flgs1.Fl24
#define OnTransmittHC05         Flgs1.Fl25
#define HvReplyHC05             Flgs1.Fl26
#define PreStopping             Flgs1.Fl27
#define AT_Trm                  Flgs1.Fl28
#define HallDelay1_Direction    Flgs1.Fl29
#define AT_Rec                  Flgs1.Fl30
#define GettingPacketU4_FL      Flgs1.Fl31


#define  CHK_Err_U4              Flgs2.Fl0
#define  HvPacketU4_FL           Flgs2.Fl1
#define  MustTrmPacketHC05_FL    Flgs2.Fl2
#define  AddTestTilt             Flgs2.Fl3
#define  ChangingTiltSensor      Flgs2.Fl4
#define NullPtr                  Flgs2.Fl5
#define TiltSteerError           Flgs2.Fl6
#define NullPtrRot               Flgs2.Fl7
#define MustTrmErrors            Flgs2.Fl8
#define But3Pressed               Flgs2.Fl9
#define Preas1                   Flgs2.Fl10
#define Preas2                   Flgs2.Fl11
#define HorningL                 Flgs2.Fl12
#define HvZeroCrossing               Flgs2.Fl13
#define OneLeg                   Flgs2.Fl14
#define TiltZadAdd_UP            Flgs2.Fl15
#define KpMustBe_UP              Flgs2.Fl16
#define StartRot_UP              Flgs2.Fl17
#define Ki_UP                    Flgs2.Fl18
#define KRot_UP                  Flgs2.Fl19
#define KpRot_UP                 Flgs2.Fl20
#define KiRot_UP                 Flgs2.Fl21
#define Preasure1                Flgs2.Fl22
#define Preasure2                Flgs2.Fl23
#define BuzzerOnAlways           Flgs2.Fl24
#define MustTrmHC05              Flgs2.Fl25
#define HC05_BUSY                Flgs2.Fl26
#define KpSPD_UP                 Flgs2.Fl27
#define AngleLimit_UP            Flgs2.Fl28
#define NoSound                  Flgs2.Fl29
#define AlarmOn                  Flgs2.Fl30
#define HorningH                 Flgs2.Fl31

#define  Robowell                Flgs3.Fl0
#define  NameRBW                 Flgs3.Fl1
#define  SpeedRBW                Flgs3.Fl2
#define  GetRobowell             Flgs3.Fl3
#define  Calibrating             Flgs3.Fl4
#define  ClearCurrentAH          Flgs3.Fl5
#define  HornAlmOn               Flgs3.Fl6
#define  MustSendDataPacket      Flgs3.Fl7
#define  Isltd                   Flgs3.Fl8
#define  CntSingleBeepFl         Flgs3.Fl9
#define  TmrActive               Flgs3.Fl10
#define  Stt3                    Flgs3.Fl11
#define  BMS_V_Low               Flgs3.Fl12
#define  Falling                 Flgs3.Fl13
#define SendStorageDataToBMS     Flgs3.Fl14
//#define CanZeroCrossing          Flgs3.Fl15
#define SoundOUT                 Flgs3.Fl16
#define GettingStorage           Flgs3.Fl17
#define TestSIN_Ok               Flgs3.Fl18
#define OverSpeed                Flgs3.Fl19
#define SensorlessNotBEMF                  Flgs3.Fl20
#define TestVibro                Flgs3.Fl21
#define HvSpdFloat_Fl            Flgs3.Fl22
#define TestVibroLR              Flgs3.Fl23
#define RegenOver3900            Flgs3.Fl24
#define PID_On                   Flgs3.Fl25
#define TEST_PWM_KEYS            Flgs3.Fl26//0x4000000
#define ErrorSnd                 Flgs3.Fl27
#define OnIndFl                  Flgs3.Fl28
#define SoundIN                  Flgs3.Fl29
#define SoundTmr                  Flgs3.Fl30
#define Drebezg3                  Flgs3.Fl31


#define Hv2WDMaster              Flgs4.Fl0
#define DbgOdmtr                 Flgs4.Fl1
#define BreakPressed2            Flgs4.Fl2
#define MustTrm_U3               Flgs4.Fl3
#define OnTransmitt_U3           Flgs4.Fl4
#define HvPachetSteer            Flgs4.Fl5
#define BEMFA_OK                 Flgs4.Fl6
#define Stopping                 Flgs4.Fl7
#define HvOptions                Flgs4.Fl8
#define BreakPressedPrev         Flgs4.Fl9
#define _1stBreak                Flgs4.Fl10
#define Wheeling                 Flgs4.Fl11
#define StrtWheeling             Flgs4.Fl12
#define InitReady                Flgs4.Fl13
#define NoSecret                 Flgs4.Fl14
#define AlmOffing                Flgs4.Fl15
#define T45Over                  Flgs4.Fl16
#define T45OverFl                Flgs4.Fl17
#define T67Over                  Flgs4.Fl18
#define T67OverFl                Flgs4.Fl19
#define CanGetHalls1             Flgs4.Fl20
#define CanGetHalls2             Flgs4.Fl21
#define HallDelay1_F_UP          Flgs4.Fl22
#define HallDelay1_B_UP          Flgs4.Fl23
#define HallDelay2_F_UP          Flgs4.Fl24
#define HallDelay2_B_UP          Flgs4.Fl25
#define T45OverFl1               Flgs4.Fl26
#define T67OverFl1               Flgs4.Fl27
#define ReversON                 Flgs4.Fl28
#define ReversChanged            Flgs4.Fl29
#define NoChager                 Flgs4.Fl30
#define HvCalibrationHalls       Flgs4.Fl31


#define  Bt3Up                   Flgs5.Fl0
#define  HvBt3                   Flgs5.Fl1
#define  But1Pressed             Flgs5.Fl2
#define  ChargingComplete        Flgs5.Fl3
#define  Vector                  Flgs5.Fl4
#define  Drebezg1                Flgs5.Fl5
#define  Bt1Up                   Flgs5.Fl6
#define  HvBt1                   Flgs5.Fl7
#define  CV                      Flgs5.Fl8
#define  Bt2Up                   Flgs5.Fl9
#define  HvBt2                   Flgs5.Fl10
#define  But2Pressed             Flgs5.Fl11
#define  BtPID_Activated         Flgs5.Fl12
#define  SpeedControlMem         Flgs5.Fl13
#define  StartingBTN             Flgs5.Fl14
#define  DisconnectMotor         Flgs5.Fl15
#define  BreakPressedUp          Flgs5.Fl16
#define  MustTrmFlashMassForSaveOptPC Flgs5.Fl17
#define  MustTrmProfileMass      Flgs5.Fl18
#define  MustTrmCmdOk            Flgs5.Fl19
#define  MustTrmCmdOk2           Flgs5.Fl20
#define  SensorlessInitialized   Flgs5.Fl21
#define  Locked                  Flgs5.Fl22
#define  SendUnlockMSG           Flgs5.Fl23
#define  StrongModeMixedMustOn   Flgs5.Fl24
#define  HvZ_Cr                  Flgs5.Fl25
#define  PrevStrongMode          Flgs5.Fl26
#define  BreakPressedMonocycle   Flgs5.Fl27
#define  LeftTurn                Flgs5.Fl28
#define  RightTurn               Flgs5.Fl29
#define  StopLights              Flgs5.Fl30
#define  SlStrt                  Flgs5.Fl31


#define  SpeedControlTmp         Flgs6.Fl0
#define  SpeedControlPrev        Flgs6.Fl1
#define  HvBreak                 Flgs6.Fl2
#define  HvMPU6050               Flgs6.Fl3
#define  CurrDecrease            Flgs6.Fl4
#define  FillCurrentMass         Flgs6.Fl5
#define  FillSinMass             Flgs6.Fl6
#define  BuzzerOff               Flgs6.Fl7
#define  TestingSin              Flgs6.Fl8
#define  StrtTestingSin          Flgs6.Fl9
#define  Alignment               Flgs6.Fl10
#define  ThetaIndexINC           Flgs6.Fl11
#define  MustTrmStateOfSinTest   Flgs6.Fl12
#define  Shift_F                 Flgs6.Fl13
#define  HvConfirm               Flgs6.Fl14
#define AutoNastroyka_ConfirmMSG Flgs6.Fl15
#define ShiftUpping              Flgs6.Fl16
#define HvUBT                    Flgs6.Fl17
#define PIN_CODE_HC05            Flgs6.Fl18
#define ResetedPIN               Flgs6.Fl19
#define MustResetPIN             Flgs6.Fl20
#define GAZ_IMMITATOR            Flgs6.Fl21
#define TrapezoidaRAM1_Temp      Flgs6.Fl22
#define SetOverCurrTrapezoida    Flgs6.Fl23
#define HvToTest                 Flgs6.Fl24
#define MPU6000_Initialized      Flgs6.Fl25
#define MPU60000_Initializing    Flgs6.Fl26

#if defined VECTOR
#define DS                       Flgs6.Fl27
#endif
#define CalibrateHalls           Flgs6.Fl28
#define Drebezg2                 Flgs6.Fl29
#define SensorlessStartNoHalls   Flgs6.Fl30


#define SlaveBut1                Flgs7.Fl0
#define SlaveBut2                Flgs7.Fl1
#define SlaveBut3                Flgs7.Fl2
#define SlaveBut4                Flgs7.Fl3
#define SlaveBreak               Flgs7.Fl4
#define CalibrateJOYSTICK        Flgs7.Fl5
#define HvADC1                   Flgs7.Fl6
#define ResetedPIN1              Flgs7.Fl7
#define HvButtonsFromMaster      Flgs7.Fl8
#define StopLightFl              Flgs7.Fl9
#define MustTrmFlashMass2        Flgs7.Fl10
#define MustTrmFlashMass2ForSaveOptPC Flgs7.Fl11
#define MustTrmCmdOk3            Flgs7.Fl12
#define LSM6DS33_Initialized     Flgs7.Fl13
#define Right                    Flgs7.Fl14
#define Left                     Flgs7.Fl15
#define TestU3ChangeSpd          Flgs7.Fl16
#define U4_9600                  Flgs7.Fl17
#define BMSErr                   Flgs7.Fl18
#define WheelingNew              Flgs7.Fl19
#define PrevNoChager             Flgs7.Fl20
#define EPrevFl                  Flgs7.Fl21
#define Hv_HC05                  Flgs7.Fl22
#define StpLightsNew             Flgs7.Fl23
#define ButtonBreakOnlyPrev      Flgs7.Fl24
#define PWM10kHzTmp              Flgs7.Fl25
#define Bt1DnMustCount           Flgs7.Fl26
#define Bt2DnMustCount           Flgs7.Fl27
#define Bt3DnMustCount           Flgs7.Fl28
#define Bt4DnMustCount           Flgs7.Fl29
#define TrapezoidaRAM1Mem        Flgs7.Fl30
#define MonocycleSlave           Flgs7.Fl31

#define OkToBalance              Flgs8.Fl0
#define CountingHumanSensor      Flgs8.Fl1
#define NoBalanceFmMaster        Flgs8.Fl2
#define StopMotorMonocycle       Flgs8.Fl3
#if !defined BUZZER_WITH_GENERATOR
#define Buzzer                   Flgs8.Fl4
#endif
#define TmpFl                    Flgs8.Fl5
#define BEMFB_OK                 Flgs8.Fl6
#define BEMFC_OK                 Flgs8.Fl7
#define BEMF_OK                  Flgs8.Fl8
#define A2_OK                    Flgs8.Fl9
#define B2_OK                    Flgs8.Fl10
#define C2_OK                    Flgs8.Fl11







#define TICK_PERIOD 0.004




#define  KpMustBeErr 1
#define  KdErr 2
#define  KiErr 3
#define  TiltYCorrErr 4
#define  KGYROErr 5
#define  TiltXSteerCorrErr 6
#define  TiltYSteerCorrErr 7
#define  CalibrationGyroXErr 8
#define  CalibrationGyroYErr 9
#define  CalibrationGyroZErr 10
#define  CalibrationAccXErr 11
#define  CalibrationAccYErr 12
#define  CalibrationAccZErr 13
#define  KRotErr 14
#define  StartRotErr 15
#define  KpRotErr 16
#define   CurrLimitErr 17
#define  KiRotErr 18
#define  KpSPDErr 19
#define  AngleLimitErr 20
#define  SpeedLimitErr 21
#define  XLimitErr 22
#define  YLimitErr 23
#define  UBatLowErr 24
#define  KpBackErr  25
#define  TiltBackLimitErr  26
#define  NumSpeedLimitErr  27
#define  KpMustBeMaxErr 28
#define  KpSpeedErr  29
#define  DiffTiltLimitErr    30
#define  TiltZadCHNGErr     31

typedef union {
    unsigned int StatusFlags;

    struct {
        unsigned int Fl0 : 1;
        unsigned int Fl1 : 1;
        unsigned int Fl2 : 1;
        unsigned int Fl3 : 1;
        unsigned int Fl4 : 1;
        unsigned int Fl5 : 1;
        unsigned int Fl6 : 1;
        unsigned int Fl7 : 1;
        unsigned int Fl8 : 1;
        unsigned int Fl9 : 1;
        unsigned int Fl10 : 1;
        unsigned int Fl11 : 1;
        unsigned int Fl12 : 1;
        unsigned int Fl13 : 1;
        unsigned int Fl14 : 1;
        unsigned int Fl15 : 1;
    };
} STAT_FLAGS;

#define DirectControlMotor     StatFlgs.Fl0
#define EEPROM_CHK_ERR         StatFlgs.Fl1
//#define BEMFA_OK       StatFlgs.Fl2
#define PWM10kHz              StatFlgs.Fl2

#define Beep_10m               StatFlgs.Fl3
#define ThreePositionSwitch    StatFlgs.Fl4
#define SmoothBreak            StatFlgs.Fl5
#define AutoPID                StatFlgs.Fl6
#define Unicycle               StatFlgs.Fl7
#define ZeroThroottle          StatFlgs.Fl8
#define ManualStart            StatFlgs.Fl9
#define NoAutoTrm              StatFlgs.Fl10
#define MixedMode              StatFlgs.Fl11
#define AnalogBreak            StatFlgs.Fl12
#define StrongModePID          StatFlgs.Fl13
#define RobotFl                StatFlgs.Fl14
#define Monocycle              StatFlgs.Fl15



#define DirPWM1                StatFlgs1.Fl0
#define SpeedControl           StatFlgs1.Fl1
#define DirBalance             StatFlgs1.Fl2
#define BuzzAndHorn            StatFlgs1.Fl3
#define DoNotTestBMS           StatFlgs1.Fl4
#define Sensorless             StatFlgs1.Fl5
#define BreakInvBtn            StatFlgs1.Fl6
#define Tmprt1                 StatFlgs1.Fl7
#define Lock                   StatFlgs1.Fl8
#define Tmprt2                 StatFlgs1.Fl9
#define VectorMem              StatFlgs1.Fl10
#define CurrLimitSound         StatFlgs1.Fl11
#define TrapezoidaRAM1         StatFlgs1.Fl12
#define CURRENT_PROTECTION     StatFlgs1.Fl13
#define BreakButtonMonocycle   StatFlgs1.Fl14
#define PWM32Bits              StatFlgs1.Fl15


#define Tmprt3                 StatFlgs2.Fl0
#define Tmprt4                 StatFlgs2.Fl1
#define StrongModeMem          StatFlgs2.Fl2
#define MonoStopDirection      StatFlgs2.Fl3
#define RotAlfaXRes            StatFlgs2.Fl4
#define TurnSignal             StatFlgs2.Fl5
#define LightsTudaSuda         StatFlgs2.Fl6
#define LightsStopMonoDir      StatFlgs2.Fl7
#define SlowStart              StatFlgs2.Fl8
#define Sensorless2            StatFlgs2.Fl9
#define MixedModeSlowSpeedOff  StatFlgs2.Fl10
#define MixedMode2             StatFlgs2.Fl11
#define PWM_Mode               StatFlgs2.Fl12
#define PWM_Mode_ZeroThrottle  StatFlgs2.Fl13
#define SIN_MIDDLE             StatFlgs2.Fl14
#define InvSin                 StatFlgs2.Fl15



#define CW_CCW_AnyProfile      StatFlgs3.Fl0
#define ShortCircuit           StatFlgs3.Fl1
#define HighDataSpdUART        StatFlgs3.Fl2
#define BothBreaks             StatFlgs3.Fl3
#define TrapezoidaWhenBigCurrent StatFlgs3.Fl4
#define Joystick               StatFlgs3.Fl5
#define JoystickCalibrOnReset  StatFlgs3.Fl6
#define ChangeAxis             StatFlgs3.Fl7
#define IRFP4110               StatFlgs3.Fl8
#define LightOn                StatFlgs3.Fl9
#define CurrentControlOnly     StatFlgs3.Fl10
#define Vertical               StatFlgs3.Fl11
#define ButtonBreakOnly        StatFlgs3.Fl12
#define StpLights              StatFlgs3.Fl13
#define StrongModeBreakOff     StatFlgs3.Fl14
#define StrongModeMotorOff     StatFlgs3.Fl15

#define KeyLightStop           StatFlgs4.Fl0
#define KeyLightStopGabarit    StatFlgs4.Fl1
#define MigStop                StatFlgs4.Fl2
#define LightsFromButton       StatFlgs4.Fl3
#define KpKpMinus              StatFlgs4.Fl4
#define Segway                 StatFlgs4.Fl5
#define GyroAccSameOff         StatFlgs4.Fl6
#define HumanSensor            StatFlgs4.Fl7
#define PWMChanged             StatFlgs4.Fl8
#define InvHallA               StatFlgs4.Fl9
#define InvHallB               StatFlgs4.Fl10
#define InvHallC               StatFlgs4.Fl11
#define BreakFilter            StatFlgs4.Fl12
#define TrapezoidaWhenBigSpeed StatFlgs4.Fl13
#define I_PWMmaxSignal         StatFlgs4.Fl14
#define DifferentKd            StatFlgs4.Fl15
//BLDC 2






//#define Break       ((!Break1)||(!Break2))
#define Break       (BreakFunc())
//(!Break1)

#if !defined DGTU

#if !defined STARUS
#define WheelDiametr 40//48.5//30.5//
#define WheelImp 138//90//
#endif
#if defined STARUS
#define WheelDiametr 30.5//
#define WheelImp 90//
#endif

#define _CmImp (WheelDiametr*3.14159/WheelImp)//1.10411//0.9106
//#define ImpToKmH 0.3974793//0.327818//0.31464 //_CmImp*3.6*0.1
#define ImpToKmH  (_CmImp*3.6*0.1)
#define ImpNa10Metr (1000/(WheelDiametr*3.14159))*WheelImp       //906//1098
#endif


#if defined DGTU
#define WheelDiametr 44
#define WheelImp 138
#define _CmImp WheelDiametr*3.14159/WheelImp//1.0016663
#define ImpToKmH 0.3606 //_CmImp*3.6*0.1
#define ImpNa10Metr 998
#endif





#define KEY_BT  LATGbits.LATG7
#define TRIS_KEY_BT  TRISGbits.TRISG7




void TrmDataPacketHC05(void);


#if defined IND_10
#define TrisLed9  TRISHbits.TRISH7
#define Led9  LATHbits.LATH7
#define TrisLed8  TRISDbits.TRISD14
#define Led8  LATDbits.LATD14
#endif




//CMD To WAVE
#define SET_ACTIVE_CHANNELS     1
#define CALIBRATE_ACC		2
#define CALIBRATE_GYRO		3
#define CALIBRATE_ACCX          4
#define CALIBRATE_ACCY          5
#define SET_ACCX_BIAS		6
#define SET_ACCY_BIAS		7
#define SET_ACCZ_BIAS		8
#define SET_GYROX_BIAS		9
#define SET_GYROY_BIAS		10
#define SET_GYRO4X_BIAS		11
#define SET_GYRO4Y_BIAS		12
#define WRITE_TO_EEPROM   	13
#define SET_FREQUENCY		14
#define GET_OPTIONS		15
#define BROADCAST_ON		16
#define BROADCAST_OFF		17
#define GET_DATA_PACKET		18
#define SET_EUSART_BAUD_RATE	19
#define ST_ON                   20
#define ST_OFF                  21
#define SET_I2C_ADDR		22
#define GET_STATUS_I2C          23
#define RESET                   24
#define SET_GYRO_ACCX_RATIO     25
#define SET_TILT_ANGLE		26
#define GET_VERSION             27


#define GET_STATUS2             77


//CMD From WAVE
#define DATA_PACKET		0x81
#define CRC_ERROR		0x82
#define GOOD_RESULT		0x83
#define BAD_RESULT		0x84
#define EEPROM_ERROR		0x85
#define UNRECOGNIZED_COMMAND	0x86
#define OPTIONS    		0x87
#define VERSION 		0x88


#define ACC_AV_TTL  256
#define ACC_AV_SHFT  8


typedef unsigned char BYTE; /* 8-bit unsigned  */
typedef unsigned short int WORD; /* 16-bit unsigned */
typedef unsigned long DWORD; /* 32-bit unsigned */

typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned short int UINT16;


//#define   SQUARE
//#define   HALFTABLE
#define PhasePERMASS_DEF    64
#define THETA_NUM       384
#define ADCThrottleBreak_SIZE 128    
#define ADCThrottleBreak_SIZE_SHFT 7



#if defined VECTOR
#define DEADTIME_Si8233 0//6
#else
#define DEADTIME_Si8233 6
#endif
#define DEADTIME        100//50//
#define DEADTIME_GLUK   0//80//20//
#define DEADTIME_2        (DEADTIME/2)

#define MAX_PWM_SENSORLESS_CONST    (3000-DEADTIME-DEADTIME_Si8233)
#define MAX_PWM_CONST_EBIKE     (1500-DEADTIME-DEADTIME_Si8233)
#define MAX_PWM_CONST_MONOCYCLE10kHz (6000-DEADTIME-DEADTIME_Si8233)
#define MAX_PWM_CONST_MONOCYCLE5kHz (5000-DEADTIME-DEADTIME_Si8233)//(12000-DEADTIME-DEADTIME_Si8233)
#define MAX_PWM_CONST_MONOCYCLE (3000-DEADTIME-DEADTIME_Si8233)
#define CntCalibrHallsMAX   64

#define CLBR_JOISTICK_MASS_SIZE 64
#define CLBR_JOISTICK_SHFT 6

#define SIZE_OF_PROFILE     70

#define PROFILEMASS_SIZE    240

#if defined ISOLATED
#define TRIS_UBt_SCK    TRISBbits.TRISB5
#define UBt_SCK         LATBbits.LATB5
#define ANSEL_UBt_SCK    ANSELBbits.ANSB5

#define TRIS_UBt_DATA   TRISBbits.TRISB4
#define UBt_DATA        PORTBbits.RB4
#define ANSEL_UBt_DATA  ANSELBbits.ANSB4
#endif

//TENZO
#define ADC_TENZO_BITS 4096
#if defined REV2
#define ADC_TENZO_BITS_REV2 3745
#else
#define ADC_TENZO_BITS_REV2 4096
#endif
#define R 2200

//TENZO 1
#define T1_R1 980
#define T1_R2 1030
#define T1_R3 1135
#define T1_R4 1247
#define T1_R5 1367
#define T1_R6 1495
#define T1_R7 1630
#define T1_R8 1772
#define T1_R9 1922
#define T1_R10 2000
#define T1_R11 2080
#define T1_R12 2245
#define T1_R13 2417
#define T1_R14 2597
#define T1_R15 2785
#define T1_R16 2980
#define T1_R17 3182
#define T1_R18 3392
#define T1_R19 3607
#define T1_R20 3817
#define T1_R21 3915
#define T1_R22 4008
#define T1_R23 4166
#define T1_R24 4280









#define T1_V1    (unsigned int)(((float)T1_R1/((float)T1_R1+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V2    (unsigned int)(((float)T1_R2/((float)T1_R2+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V3    (unsigned int)(((float)T1_R3/((float)T1_R3+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V4    (unsigned int)(((float)T1_R4/((float)T1_R4+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V5    (unsigned int)(((float)T1_R5/((float)T1_R5+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V6    (unsigned int)(((float)T1_R6/((float)T1_R6+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V7    (unsigned int)(((float)T1_R7/((float)T1_R7+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V8    (unsigned int)(((float)T1_R8/((float)T1_R8+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V9    (unsigned int)(((float)T1_R9/((float)T1_R9+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V10    (unsigned int)(((float)T1_R10/((float)T1_R10+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V11    (unsigned int)(((float)T1_R11/((float)T1_R11+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V12    (unsigned int)(((float)T1_R12/((float)T1_R12+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V13    (unsigned int)(((float)T1_R13/((float)T1_R13+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V14    (unsigned int)(((float)T1_R14/((float)T1_R14+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V15    (unsigned int)(((float)T1_R15/((float)T1_R15+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V16    (unsigned int)(((float)T1_R16/((float)T1_R16+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V17    (unsigned int)(((float)T1_R17/((float)T1_R17+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V18    (unsigned int)(((float)T1_R18/((float)T1_R18+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V19    (unsigned int)(((float)T1_R19/((float)T1_R19+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V20    (unsigned int)(((float)T1_R20/((float)T1_R20+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V21    (unsigned int)(((float)T1_R21/((float)T1_R21+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V22    (unsigned int)(((float)T1_R22/((float)T1_R22+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V23    (unsigned int)(((float)T1_R23/((float)T1_R23+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T1_V24    (unsigned int)(((float)T1_R24/((float)T1_R24+(float)R))*(float)ADC_TENZO_BITS_REV2)

//TENZO 1  END



//TENZO 2  NTCALUG03A103H
#define T2_R1 334274
#define T2_R2 241323
#define T2_R3 176133
#define T2_R4 129900
#define T2_R5 96761
#define T2_R6 72765
#define T2_R7 55218
#define T2_R8 42268
#define T2_R9 32624
#define T2_R10 25381
#define T2_R11 19897
#define T2_R12 15711
#define T2_R13 12493
#define T2_R14 10000
#define T2_R15 8056
#define T2_R16 6530
#define T2_R17 5324
#define T2_R18 4365
#define T2_R19 3599
#define T2_R20 2982
#define T2_R21 2484
#define T2_R22 2078
#define T2_R23 1747
#define T2_R24 1476
#define T2_R25 1252
#define T2_R26 1066
#define T2_R27 912
#define T2_R28 782
#define T2_R29 674
#define T2_R30 583
#define T2_R31 506
#define T2_R32 440
#define T2_R33 384
#define T2_R34 337









#define T2_V1    (unsigned int)(((float)T2_R1/((float)T2_R1+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V2    (unsigned int)(((float)T2_R2/((float)T2_R2+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V3    (unsigned int)(((float)T2_R3/((float)T2_R3+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V4    (unsigned int)(((float)T2_R4/((float)T2_R4+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V5    (unsigned int)(((float)T2_R5/((float)T2_R5+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V6    (unsigned int)(((float)T2_R6/((float)T2_R6+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V7    (unsigned int)(((float)T2_R7/((float)T2_R7+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V8    (unsigned int)(((float)T2_R8/((float)T2_R8+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V9    (unsigned int)(((float)T2_R9/((float)T2_R9+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V10    (unsigned int)(((float)T2_R10/((float)T2_R10+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V11    (unsigned int)(((float)T2_R11/((float)T2_R11+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V12    (unsigned int)(((float)T2_R12/((float)T2_R12+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V13    (unsigned int)(((float)T2_R13/((float)T2_R13+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V14    (unsigned int)(((float)T2_R14/((float)T2_R14+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V15    (unsigned int)(((float)T2_R15/((float)T2_R15+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V16    (unsigned int)(((float)T2_R16/((float)T2_R16+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V17    (unsigned int)(((float)T2_R17/((float)T2_R17+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V18    (unsigned int)(((float)T2_R18/((float)T2_R18+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V19    (unsigned int)(((float)T2_R19/((float)T2_R19+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V20    (unsigned int)(((float)T2_R20/((float)T2_R20+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V21    (unsigned int)(((float)T2_R21/((float)T2_R21+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V22    (unsigned int)(((float)T2_R22/((float)T2_R22+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V23    (unsigned int)(((float)T2_R23/((float)T2_R23+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V24    (unsigned int)(((float)T2_R24/((float)T2_R24+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V25    (unsigned int)(((float)T2_R25/((float)T2_R25+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V26    (unsigned int)(((float)T2_R26/((float)T2_R26+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V27    (unsigned int)(((float)T2_R27/((float)T2_R27+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V28    (unsigned int)(((float)T2_R28/((float)T2_R28+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V29    (unsigned int)(((float)T2_R29/((float)T2_R29+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V30    (unsigned int)(((float)T2_R30/((float)T2_R30+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V31    (unsigned int)(((float)T2_R31/((float)T2_R31+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V32    (unsigned int)(((float)T2_R32/((float)T2_R32+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V33    (unsigned int)(((float)T2_R33/((float)T2_R33+(float)R))*(float)ADC_TENZO_BITS)
#define T2_V34    (unsigned int)(((float)T2_R34/((float)T2_R34+(float)R))*(float)ADC_TENZO_BITS)

//TENZO 2  END


//TENZO 3  KTY83/110
#define T3_R1 500
#define T3_R2 525
#define T3_R3 577
#define T3_R4 632
#define T3_R5 691
#define T3_R6 754
#define T3_R7 820
#define T3_R8 889
#define T3_R9 962
#define T3_R10 1000
#define T3_R11 1039
#define T3_R12 1118
#define T3_R13 1202
#define T3_R14 1288
#define T3_R15 1379
#define T3_R16 1472
#define T3_R17 1569
#define T3_R18 1670
#define T3_R19 1774
#define T3_R20 1882
#define T3_R21 1937
#define T3_R22 1993
#define T3_R23 2107
#define T3_R24 2225
#define T3_R25 2346
#define T3_R26 2471
#define T3_R27 2535










#define T3_V1    (unsigned int)(((float)T3_R1/((float)T3_R1+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V2    (unsigned int)(((float)T3_R2/((float)T3_R2+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V3    (unsigned int)(((float)T3_R3/((float)T3_R3+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V4    (unsigned int)(((float)T3_R4/((float)T3_R4+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V5    (unsigned int)(((float)T3_R5/((float)T3_R5+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V6    (unsigned int)(((float)T3_R6/((float)T3_R6+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V7    (unsigned int)(((float)T3_R7/((float)T3_R7+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V8    (unsigned int)(((float)T3_R8/((float)T3_R8+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V9    (unsigned int)(((float)T3_R9/((float)T3_R9+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V10    (unsigned int)(((float)T3_R10/((float)T3_R10+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V11    (unsigned int)(((float)T3_R11/((float)T3_R11+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V12    (unsigned int)(((float)T3_R12/((float)T3_R12+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V13    (unsigned int)(((float)T3_R13/((float)T3_R13+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V14    (unsigned int)(((float)T3_R14/((float)T3_R14+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V15    (unsigned int)(((float)T3_R15/((float)T3_R15+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V16    (unsigned int)(((float)T3_R16/((float)T3_R16+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V17    (unsigned int)(((float)T3_R17/((float)T3_R17+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V18    (unsigned int)(((float)T3_R18/((float)T3_R18+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V19    (unsigned int)(((float)T3_R19/((float)T3_R19+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V20    (unsigned int)(((float)T3_R20/((float)T3_R20+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V21    (unsigned int)(((float)T3_R21/((float)T3_R21+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V22    (unsigned int)(((float)T3_R22/((float)T3_R22+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V23    (unsigned int)(((float)T3_R23/((float)T3_R23+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V24    (unsigned int)(((float)T3_R24/((float)T3_R24+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V25    (unsigned int)(((float)T3_R25/((float)T3_R25+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V26    (unsigned int)(((float)T3_R26/((float)T3_R26+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T3_V27    (unsigned int)(((float)T3_R27/((float)T3_R27+(float)R))*(float)ADC_TENZO_BITS_REV2)

//TENZO 3  END


//TERMO 4  KTY84/130
#define T4_R1 359
#define T4_R2 391
#define T4_R3 424
#define T4_R4 460
#define T4_R5 498
#define T4_R6 538
#define T4_R7 581
#define T4_R8 603
#define T4_R9 626
#define T4_R10 672
#define T4_R11 722
#define T4_R12 773
#define T4_R13 826
#define T4_R14 882
#define T4_R15 940
#define T4_R16 1000
#define T4_R17 1062
#define T4_R18 1127
#define T4_R19 1194
#define T4_R20 1262
#define T4_R21 1334
#define T4_R22 1407
#define T4_R23 1482
#define T4_R24 1560
#define T4_R25 1640
#define T4_R26 1722
#define T4_R27 1807
#define T4_R28 1893
#define T4_R29 1982
#define T4_R30 2073
#define T4_R31 2166
#define T4_R32 2261
#define T4_R33 2357
#define T4_R34 2452
#define T4_R35 2542
#define T4_R36 2624










#define T4_V1    (unsigned int)(((float)T4_R1/((float)T4_R1+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V2    (unsigned int)(((float)T4_R2/((float)T4_R2+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V3    (unsigned int)(((float)T4_R3/((float)T4_R3+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V4    (unsigned int)(((float)T4_R4/((float)T4_R4+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V5    (unsigned int)(((float)T4_R5/((float)T4_R5+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V6    (unsigned int)(((float)T4_R6/((float)T4_R6+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V7    (unsigned int)(((float)T4_R7/((float)T4_R7+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V8    (unsigned int)(((float)T4_R8/((float)T4_R8+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V9    (unsigned int)(((float)T4_R9/((float)T4_R9+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V10    (unsigned int)(((float)T4_R10/((float)T4_R10+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V11    (unsigned int)(((float)T4_R11/((float)T4_R11+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V12    (unsigned int)(((float)T4_R12/((float)T4_R12+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V13    (unsigned int)(((float)T4_R13/((float)T4_R13+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V14    (unsigned int)(((float)T4_R14/((float)T4_R14+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V15    (unsigned int)(((float)T4_R15/((float)T4_R15+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V16    (unsigned int)(((float)T4_R16/((float)T4_R16+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V17    (unsigned int)(((float)T4_R17/((float)T4_R17+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V18    (unsigned int)(((float)T4_R18/((float)T4_R18+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V19    (unsigned int)(((float)T4_R19/((float)T4_R19+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V20    (unsigned int)(((float)T4_R20/((float)T4_R20+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V21    (unsigned int)(((float)T4_R21/((float)T4_R21+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V22    (unsigned int)(((float)T4_R22/((float)T4_R22+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V23    (unsigned int)(((float)T4_R23/((float)T4_R23+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V24    (unsigned int)(((float)T4_R24/((float)T4_R24+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V25    (unsigned int)(((float)T4_R25/((float)T4_R25+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V26    (unsigned int)(((float)T4_R26/((float)T4_R26+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V27    (unsigned int)(((float)T4_R27/((float)T4_R27+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V28    (unsigned int)(((float)T4_R28/((float)T4_R28+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V29    (unsigned int)(((float)T4_R29/((float)T4_R29+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V30   (unsigned int)(((float)T4_R30/((float)T4_R30+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V31    (unsigned int)(((float)T4_R31/((float)T4_R31+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V32    (unsigned int)(((float)T4_R32/((float)T4_R32+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V33    (unsigned int)(((float)T4_R33/((float)T4_R33+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V34    (unsigned int)(((float)T4_R34/((float)T4_R34+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V35    (unsigned int)(((float)T4_R35/((float)T4_R35+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T4_V36    (unsigned int)(((float)T4_R36/((float)T4_R36+(float)R))*(float)ADC_TENZO_BITS_REV2)

//TERMO 4  END



//TENZO 5  KTY83/122
#define T5_R1 505
#define T5_R2 530
#define T5_R3 583
#define T5_R4 639
#define T5_R5 698
#define T5_R6 762
#define T5_R7 828
#define T5_R8 898
#define T5_R9 972
#define T5_R10 1010
#define T5_R11 1049
#define T5_R12 1130
#define T5_R13 1214
#define T5_R14 1301
#define T5_R15 1392
#define T5_R16 1487
#define T5_R17 1585
#define T5_R18 1687
#define T5_R19 1792
#define T5_R20 1900
#define T5_R21 1959
#define T5_R22 2012
#define T5_R23 2128
#define T5_R24 2247
#define T5_R25 2370
#define T5_R26 2496
#define T5_R27 2560










#define T5_V1    (unsigned int)(((float)T5_R1/((float)T5_R1+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V2    (unsigned int)(((float)T5_R2/((float)T5_R2+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V3    (unsigned int)(((float)T5_R3/((float)T5_R3+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V4    (unsigned int)(((float)T5_R4/((float)T5_R4+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V5    (unsigned int)(((float)T5_R5/((float)T5_R5+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V6    (unsigned int)(((float)T5_R6/((float)T5_R6+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V7    (unsigned int)(((float)T5_R7/((float)T5_R7+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V8    (unsigned int)(((float)T5_R8/((float)T5_R8+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V9    (unsigned int)(((float)T5_R9/((float)T5_R9+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V10    (unsigned int)(((float)T5_R10/((float)T5_R10+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V11    (unsigned int)(((float)T5_R11/((float)T5_R11+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V12    (unsigned int)(((float)T5_R12/((float)T5_R12+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V13    (unsigned int)(((float)T5_R13/((float)T5_R13+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V14    (unsigned int)(((float)T5_R14/((float)T5_R14+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V15    (unsigned int)(((float)T5_R15/((float)T5_R15+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V16    (unsigned int)(((float)T5_R16/((float)T5_R16+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V17    (unsigned int)(((float)T5_R17/((float)T5_R17+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V18    (unsigned int)(((float)T5_R18/((float)T5_R18+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V19    (unsigned int)(((float)T5_R19/((float)T5_R19+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V20    (unsigned int)(((float)T5_R20/((float)T5_R20+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V21    (unsigned int)(((float)T5_R21/((float)T5_R21+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V22    (unsigned int)(((float)T5_R22/((float)T5_R22+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V23    (unsigned int)(((float)T5_R23/((float)T5_R23+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V24    (unsigned int)(((float)T5_R24/((float)T5_R24+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V25    (unsigned int)(((float)T5_R25/((float)T5_R25+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V26    (unsigned int)(((float)T5_R26/((float)T5_R26+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T5_V27    (unsigned int)(((float)T5_R27/((float)T5_R27+(float)R))*(float)ADC_TENZO_BITS_REV2)

//TENZO 5  END



//TENZO 6  KTY81/210 FETs
#define T6_R1 980
#define T6_R2 1030
#define T6_R3 1135
#define T6_R4 1247
#define T6_R5 1367
#define T6_R6 1495
#define T6_R7 1630
#define T6_R8 1772
#define T6_R9 1922
#define T6_R10 2000
#define T6_R11 2080
#define T6_R12 2245
#define T6_R13 2417
#define T6_R14 2597
#define T6_R15 2785
#define T6_R16 2980
#define T6_R17 3182
#define T6_R18 3392
#define T6_R19 3607
#define T6_R20 3817
#define T6_R21 3915
#define T6_R22 4008
#define T6_R23 4166
#define T6_R24 4280











#define T6_V1    (unsigned int)(((float)T6_R1/((float)T6_R1+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V2    (unsigned int)(((float)T6_R2/((float)T6_R2+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V3    (unsigned int)(((float)T6_R3/((float)T6_R3+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V4    (unsigned int)(((float)T6_R4/((float)T6_R4+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V5    (unsigned int)(((float)T6_R5/((float)T6_R5+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V6    (unsigned int)(((float)T6_R6/((float)T6_R6+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V7    (unsigned int)(((float)T6_R7/((float)T6_R7+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V8    (unsigned int)(((float)T6_R8/((float)T6_R8+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V9    (unsigned int)(((float)T6_R9/((float)T6_R9+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V10    (unsigned int)(((float)T6_R10/((float)T6_R10+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V11    (unsigned int)(((float)T6_R11/((float)T6_R11+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V12    (unsigned int)(((float)T6_R12/((float)T6_R12+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V13    (unsigned int)(((float)T6_R13/((float)T6_R13+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V14    (unsigned int)(((float)T6_R14/((float)T6_R14+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V15    (unsigned int)(((float)T6_R15/((float)T6_R15+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V16    (unsigned int)(((float)T6_R16/((float)T6_R16+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V17    (unsigned int)(((float)T6_R17/((float)T6_R17+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V18    (unsigned int)(((float)T6_R18/((float)T6_R18+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V19    (unsigned int)(((float)T6_R19/((float)T6_R19+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V20    (unsigned int)(((float)T6_R20/((float)T6_R20+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V21    (unsigned int)(((float)T6_R21/((float)T6_R21+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V22    (unsigned int)(((float)T6_R22/((float)T6_R22+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V23    (unsigned int)(((float)T6_R23/((float)T6_R23+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V24    (unsigned int)(((float)T6_R24/((float)T6_R24+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V25    (unsigned int)(((float)T6_R25/((float)T6_R25+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V26    (unsigned int)(((float)T6_R26/((float)T6_R26+(float)R))*(float)ADC_TENZO_BITS)
#define T6_V27    (unsigned int)(((float)T6_R27/((float)T6_R27+(float)R))*(float)ADC_TENZO_BITS)

//TENZO 6  END









//TENZO 7  MF58 B 5k
#define T7_R1 52840
#define T7_R2 41190
#define T7_R3 32430
#define T7_R4 25650
#define T7_R5 20480
#define T7_R6 16430
#define T7_R7 13290
#define T7_R8 10800
#define T7_R9 8839
#define T7_R10 7266
#define T7_R11 6013
#define T7_R12 5000
#define T7_R13 4179
#define T7_R14 3508
#define T7_R15 2962
#define T7_R16 2510
#define T7_R17 2138
#define T7_R18 1826
#define T7_R19 1568
#define T7_R20 1351
#define T7_R21 1169
#define T7_R22 1014
#define T7_R23 884
#define T7_R24 773
#define T7_R25 677
#define T7_R26 596
#define T7_R27 527
#define T7_R28 466
#define T7_R29 413









#define T7_V1    (unsigned int)(((float)T7_R1/((float)T7_R1+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V2    (unsigned int)(((float)T7_R2/((float)T7_R2+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V3    (unsigned int)(((float)T7_R3/((float)T7_R3+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V4    (unsigned int)(((float)T7_R4/((float)T7_R4+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V5    (unsigned int)(((float)T7_R5/((float)T7_R5+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V6    (unsigned int)(((float)T7_R6/((float)T7_R6+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V7    (unsigned int)(((float)T7_R7/((float)T7_R7+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V8    (unsigned int)(((float)T7_R8/((float)T7_R8+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V9    (unsigned int)(((float)T7_R9/((float)T7_R9+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V10    (unsigned int)(((float)T7_R10/((float)T7_R10+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V11    (unsigned int)(((float)T7_R11/((float)T7_R11+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V12    (unsigned int)(((float)T7_R12/((float)T7_R12+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V13    (unsigned int)(((float)T7_R13/((float)T7_R13+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V14    (unsigned int)(((float)T7_R14/((float)T7_R14+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V15    (unsigned int)(((float)T7_R15/((float)T7_R15+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V16    (unsigned int)(((float)T7_R16/((float)T7_R16+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V17    (unsigned int)(((float)T7_R17/((float)T7_R17+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V18    (unsigned int)(((float)T7_R18/((float)T7_R18+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V19    (unsigned int)(((float)T7_R19/((float)T7_R19+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V20    (unsigned int)(((float)T7_R20/((float)T7_R20+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V21    (unsigned int)(((float)T7_R21/((float)T7_R21+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V22    (unsigned int)(((float)T7_R22/((float)T7_R22+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V23    (unsigned int)(((float)T7_R23/((float)T7_R23+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V24    (unsigned int)(((float)T7_R24/((float)T7_R24+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V25    (unsigned int)(((float)T7_R25/((float)T7_R25+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V26    (unsigned int)(((float)T7_R26/((float)T7_R26+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V27    (unsigned int)(((float)T7_R27/((float)T7_R27+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V28    (unsigned int)(((float)T7_R28/((float)T7_R28+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V29    (unsigned int)(((float)T7_R29/((float)T7_R29+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V30    (unsigned int)(((float)T7_R30/((float)T7_R30+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V31    (unsigned int)(((float)T7_R31/((float)T7_R31+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V32    (unsigned int)(((float)T7_R32/((float)T7_R32+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V33    (unsigned int)(((float)T7_R33/((float)T7_R33+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T7_V34    (unsigned int)(((float)T7_R34/((float)T7_R34+(float)R))*(float)ADC_TENZO_BITS_REV2)

//TENZO 7  END





//TENZO 8  MF58 G 10k
#define T8_R1 181700
#define T8_R2 133300
#define T8_R3 98880
#define T8_R4 74100
#define T8_R5 56060
#define T8_R6 42800
#define T8_R7 32960
#define T8_R8 25580
#define T8_R9 20000
#define T8_R10 15760
#define T8_R11 12510
#define T8_R12 10000
#define T8_R13 8048
#define T8_R14 6518
#define T8_R15 5312
#define T8_R16 4354
#define T8_R17 3588
#define T8_R18 2974
#define T8_R19 2476
#define T8_R20 2072
#define T8_R21 1743
#define T8_R22 1437
#define T8_R23 1250
#define T8_R24 1065
#define T8_R25 911
#define T8_R26 782
#define T8_R27 674
#define T8_R28 584
#define T8_R29 507









#define T8_V1    (unsigned int)(((float)T8_R1/((float)T8_R1+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V2    (unsigned int)(((float)T8_R2/((float)T8_R2+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V3    (unsigned int)(((float)T8_R3/((float)T8_R3+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V4    (unsigned int)(((float)T8_R4/((float)T8_R4+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V5    (unsigned int)(((float)T8_R5/((float)T8_R5+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V6    (unsigned int)(((float)T8_R6/((float)T8_R6+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V7    (unsigned int)(((float)T8_R7/((float)T8_R7+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V8    (unsigned int)(((float)T8_R8/((float)T8_R8+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V9    (unsigned int)(((float)T8_R9/((float)T8_R9+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V10    (unsigned int)(((float)T8_R10/((float)T8_R10+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V11    (unsigned int)(((float)T8_R11/((float)T8_R11+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V12    (unsigned int)(((float)T8_R12/((float)T8_R12+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V13    (unsigned int)(((float)T8_R13/((float)T8_R13+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V14    (unsigned int)(((float)T8_R14/((float)T8_R14+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V15    (unsigned int)(((float)T8_R15/((float)T8_R15+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V16    (unsigned int)(((float)T8_R16/((float)T8_R16+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V17    (unsigned int)(((float)T8_R17/((float)T8_R17+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V18    (unsigned int)(((float)T8_R18/((float)T8_R18+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V19    (unsigned int)(((float)T8_R19/((float)T8_R19+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V20    (unsigned int)(((float)T8_R20/((float)T8_R20+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V21    (unsigned int)(((float)T8_R21/((float)T8_R21+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V22    (unsigned int)(((float)T8_R22/((float)T8_R22+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V23    (unsigned int)(((float)T8_R23/((float)T8_R23+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V24    (unsigned int)(((float)T8_R24/((float)T8_R24+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V25    (unsigned int)(((float)T8_R25/((float)T8_R25+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V26    (unsigned int)(((float)T8_R26/((float)T8_R26+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V27    (unsigned int)(((float)T8_R27/((float)T8_R27+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V28    (unsigned int)(((float)T8_R28/((float)T8_R28+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V29    (unsigned int)(((float)T8_R29/((float)T8_R29+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V30    (unsigned int)(((float)T8_R30/((float)T8_R30+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V31    (unsigned int)(((float)T8_R31/((float)T8_R31+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V32    (unsigned int)(((float)T8_R32/((float)T8_R32+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V33    (unsigned int)(((float)T8_R33/((float)T8_R33+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T8_V34    (unsigned int)(((float)T8_R34/((float)T8_R34+(float)R))*(float)ADC_TENZO_BITS_REV2)

//TENZO 8  END




//TENZO 9  NCP18XH103F03RB
#define T9_R1 195652
#define T9_R2 184917
#define T9_R3 174845
#define T9_R4 165391
#define T9_R5 156513
#define T9_R6 148171
#define T9_R7 140330
#define T9_R8 132958
#define T9_R9 126022
#define T9_R10 119494
#define T9_R11 113347
#define T9_R12 107565
#define T9_R13 102116
#define T9_R14 96978
#define T9_R15 92132
#define T9_R16 87559
#define T9_R17 83242
#define T9_R18 79166
#define T9_R19 75316
#define T9_R20 71677
#define T9_R21 68237
#define T9_R22 64991
#define T9_R23 61919
#define T9_R24 59011
#define T9_R25 56258
#define T9_R26 53650
#define T9_R27 51178
#define T9_R28 48835
#define T9_R29 46613
#define T9_R30 44506
#define T9_R31 42506
#define T9_R32 40600
#define T9_R33 38791
#define T9_R34 37073
#define T9_R35 35442
#define T9_R36 33892
#define T9_R37 32420
#define T9_R38 31020
#define T9_R39 29689
#define T9_R40 28423
#define T9_R41 27219
#define T9_R42 26076
#define T9_R43 24988
#define T9_R44 23951
#define T9_R45 22963
#define T9_R46 22021
#define T9_R47 21123
#define T9_R48 20267
#define T9_R49 19450
#define T9_R50 18670
#define T9_R51 17926
#define T9_R52 17214
#define T9_R53 16534
#define T9_R54 15886
#define T9_R55 15266
#define T9_R56 14674
#define T9_R57 14108
#define T9_R58 13566
#define T9_R59 13049
#define T9_R60 12554
#define T9_R61 12081
#define T9_R62 11628
#define T9_R63 11195
#define T9_R64 10780
#define T9_R65 10382
#define T9_R66 10000
#define T9_R67 9634
#define T9_R68 9284
#define T9_R69 8947
#define T9_R70 8624
#define T9_R71 8315
#define T9_R72 8018
#define T9_R73 7734
#define T9_R74 7461
#define T9_R75 7199
#define T9_R76 6948
#define T9_R77 6707
#define T9_R78 6475
#define T9_R79 6253
#define T9_R80 6039
#define T9_R81 5834
#define T9_R82 5636
#define T9_R83 5445
#define T9_R84 5262
#define T9_R85 5086
#define T9_R86 4917
#define T9_R87 4754
#define T9_R88 4597
#define T9_R89 4446
#define T9_R90 4301
#define T9_R91 4161
#define T9_R92 4026
#define T9_R93 3896
#define T9_R94 3771
#define T9_R95 3651
#define T9_R96 3535
#define T9_R97 3423
#define T9_R98 3315
#define T9_R99 3211
#define T9_R100 3111
#define T9_R101 3014
#define T9_R102 2922
#define T9_R103 2834
#define T9_R104 2748
#define T9_R105 2666
#define T9_R106 2586
#define T9_R107 2509
#define T9_R108 2435
#define T9_R109 2364
#define T9_R110 2294
#define T9_R111 2228
#define T9_R112 2163
#define T9_R113 2100
#define T9_R114 2040
#define T9_R115 1981
#define T9_R116 1925
#define T9_R117 1870
#define T9_R118 1817
#define T9_R119 1766
#define T9_R120 1716
#define T9_R121 1669
#define T9_R122 1622
#define T9_R123 1578
#define T9_R124 1535
#define T9_R125 1493
#define T9_R126 1452
#define T9_R127 1413
#define T9_R128 1375
#define T9_R129 1338
#define T9_R130 1303
#define T9_R131 1268
#define T9_R132 1234
#define T9_R133 1202
#define T9_R134 1170
#define T9_R135 1139
#define T9_R136 1110
#define T9_R137 1081
#define T9_R138 1053
#define T9_R139 1026
#define T9_R140 999
#define T9_R141 974
#define T9_R142 949
#define T9_R143 925
#define T9_R144 902
#define T9_R145 880
#define T9_R146 858
#define T9_R147 837
#define T9_R148 816
#define T9_R149 796
#define T9_R150 777
#define T9_R151 758
#define T9_R152 740
#define T9_R153 722
#define T9_R154 705
#define T9_R155 688
#define T9_R156 672
#define T9_R157 656
#define T9_R158 640
#define T9_R159 625
#define T9_R160 611
#define T9_R161 596
#define T9_R162 583
#define T9_R163 569
#define T9_R164 556
#define T9_R165 544
#define T9_R166 531







#define T9_V1    (unsigned int)(((float)T9_R1/((float)T9_R1+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V2    (unsigned int)(((float)T9_R2/((float)T9_R2+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V3    (unsigned int)(((float)T9_R3/((float)T9_R3+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V4    (unsigned int)(((float)T9_R4/((float)T9_R4+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V5    (unsigned int)(((float)T9_R5/((float)T9_R5+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V6    (unsigned int)(((float)T9_R6/((float)T9_R6+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V7    (unsigned int)(((float)T9_R7/((float)T9_R7+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V8    (unsigned int)(((float)T9_R8/((float)T9_R8+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V9    (unsigned int)(((float)T9_R9/((float)T9_R9+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V10    (unsigned int)(((float)T9_R10/((float)T9_R10+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V11    (unsigned int)(((float)T9_R11/((float)T9_R11+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V12    (unsigned int)(((float)T9_R12/((float)T9_R12+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V13    (unsigned int)(((float)T9_R13/((float)T9_R13+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V14    (unsigned int)(((float)T9_R14/((float)T9_R14+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V15    (unsigned int)(((float)T9_R15/((float)T9_R15+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V16    (unsigned int)(((float)T9_R16/((float)T9_R16+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V17    (unsigned int)(((float)T9_R17/((float)T9_R17+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V18    (unsigned int)(((float)T9_R18/((float)T9_R18+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V19    (unsigned int)(((float)T9_R19/((float)T9_R19+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V20    (unsigned int)(((float)T9_R20/((float)T9_R20+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V21    (unsigned int)(((float)T9_R21/((float)T9_R21+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V22    (unsigned int)(((float)T9_R22/((float)T9_R22+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V23    (unsigned int)(((float)T9_R23/((float)T9_R23+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V24    (unsigned int)(((float)T9_R24/((float)T9_R24+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V25    (unsigned int)(((float)T9_R25/((float)T9_R25+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V26    (unsigned int)(((float)T9_R26/((float)T9_R26+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V27    (unsigned int)(((float)T9_R27/((float)T9_R27+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V28    (unsigned int)(((float)T9_R28/((float)T9_R28+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V29    (unsigned int)(((float)T9_R29/((float)T9_R29+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V30    (unsigned int)(((float)T9_R30/((float)T9_R30+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V31    (unsigned int)(((float)T9_R31/((float)T9_R31+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V32    (unsigned int)(((float)T9_R32/((float)T9_R32+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V33    (unsigned int)(((float)T9_R33/((float)T9_R33+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V34    (unsigned int)(((float)T9_R34/((float)T9_R34+(float)R))*(float)ADC_TENZO_BITS_REV2)


#define T9_V35    (unsigned int)(((float)T9_R35/((float)T9_R35+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V36    (unsigned int)(((float)T9_R36/((float)T9_R36+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V37    (unsigned int)(((float)T9_R37/((float)T9_R37+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V38    (unsigned int)(((float)T9_R38/((float)T9_R38+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V39    (unsigned int)(((float)T9_R39/((float)T9_R39+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V40    (unsigned int)(((float)T9_R40/((float)T9_R40+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V41    (unsigned int)(((float)T9_R41/((float)T9_R41+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V42    (unsigned int)(((float)T9_R42/((float)T9_R42+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V43    (unsigned int)(((float)T9_R43/((float)T9_R43+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V44    (unsigned int)(((float)T9_R44/((float)T9_R44+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V45    (unsigned int)(((float)T9_R45/((float)T9_R45+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V46    (unsigned int)(((float)T9_R46/((float)T9_R46+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V47    (unsigned int)(((float)T9_R47/((float)T9_R47+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V48    (unsigned int)(((float)T9_R48/((float)T9_R48+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V49    (unsigned int)(((float)T9_R49/((float)T9_R49+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V50    (unsigned int)(((float)T9_R50/((float)T9_R50+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V51    (unsigned int)(((float)T9_R51/((float)T9_R51+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V52    (unsigned int)(((float)T9_R52/((float)T9_R52+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V53    (unsigned int)(((float)T9_R53/((float)T9_R53+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V54    (unsigned int)(((float)T9_R54/((float)T9_R54+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V55    (unsigned int)(((float)T9_R55/((float)T9_R55+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V56    (unsigned int)(((float)T9_R56/((float)T9_R56+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V57    (unsigned int)(((float)T9_R57/((float)T9_R57+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V58    (unsigned int)(((float)T9_R58/((float)T9_R58+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V59    (unsigned int)(((float)T9_R59/((float)T9_R59+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V60    (unsigned int)(((float)T9_R60/((float)T9_R60+(float)R))*(float)ADC_TENZO_BITS_REV2)

#define T9_V61    (unsigned int)(((float)T9_R61/((float)T9_R61+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V62    (unsigned int)(((float)T9_R62/((float)T9_R62+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V63    (unsigned int)(((float)T9_R63/((float)T9_R63+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V64    (unsigned int)(((float)T9_R64/((float)T9_R64+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V65    (unsigned int)(((float)T9_R65/((float)T9_R65+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V66    (unsigned int)(((float)T9_R66/((float)T9_R66+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V67    (unsigned int)(((float)T9_R67/((float)T9_R67+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V68    (unsigned int)(((float)T9_R68/((float)T9_R68+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V69    (unsigned int)(((float)T9_R69/((float)T9_R69+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V70    (unsigned int)(((float)T9_R70/((float)T9_R70+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V71    (unsigned int)(((float)T9_R71/((float)T9_R71+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V72    (unsigned int)(((float)T9_R72/((float)T9_R72+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V73    (unsigned int)(((float)T9_R73/((float)T9_R73+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V74    (unsigned int)(((float)T9_R74/((float)T9_R74+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V75    (unsigned int)(((float)T9_R75/((float)T9_R75+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V76    (unsigned int)(((float)T9_R76/((float)T9_R76+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V77    (unsigned int)(((float)T9_R77/((float)T9_R77+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V78    (unsigned int)(((float)T9_R78/((float)T9_R78+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V79    (unsigned int)(((float)T9_R79/((float)T9_R79+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V80    (unsigned int)(((float)T9_R80/((float)T9_R80+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V81    (unsigned int)(((float)T9_R81/((float)T9_R81+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V82    (unsigned int)(((float)T9_R82/((float)T9_R82+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V83    (unsigned int)(((float)T9_R83/((float)T9_R83+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V84    (unsigned int)(((float)T9_R84/((float)T9_R84+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V85    (unsigned int)(((float)T9_R85/((float)T9_R85+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V86    (unsigned int)(((float)T9_R86/((float)T9_R86+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V87    (unsigned int)(((float)T9_R87/((float)T9_R87+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V88    (unsigned int)(((float)T9_R88/((float)T9_R88+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V89    (unsigned int)(((float)T9_R89/((float)T9_R89+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V90    (unsigned int)(((float)T9_R90/((float)T9_R90+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V91    (unsigned int)(((float)T9_R91/((float)T9_R91+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V92    (unsigned int)(((float)T9_R92/((float)T9_R92+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V93    (unsigned int)(((float)T9_R93/((float)T9_R93+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V94    (unsigned int)(((float)T9_R94/((float)T9_R94+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V95    (unsigned int)(((float)T9_R95/((float)T9_R95+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V96    (unsigned int)(((float)T9_R96/((float)T9_R96+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V97    (unsigned int)(((float)T9_R97/((float)T9_R97+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V98    (unsigned int)(((float)T9_R98/((float)T9_R98+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V99    (unsigned int)(((float)T9_R99/((float)T9_R99+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V100    (unsigned int)(((float)T9_R100/((float)T9_R100+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V101    (unsigned int)(((float)T9_R101/((float)T9_R101+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V102    (unsigned int)(((float)T9_R102/((float)T9_R102+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V103    (unsigned int)(((float)T9_R103/((float)T9_R103+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V104    (unsigned int)(((float)T9_R104/((float)T9_R104+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V105    (unsigned int)(((float)T9_R105/((float)T9_R105+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V106    (unsigned int)(((float)T9_R106/((float)T9_R106+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V107    (unsigned int)(((float)T9_R107/((float)T9_R107+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V108    (unsigned int)(((float)T9_R108/((float)T9_R108+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V109    (unsigned int)(((float)T9_R109/((float)T9_R109+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V110    (unsigned int)(((float)T9_R110/((float)T9_R110+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V111    (unsigned int)(((float)T9_R111/((float)T9_R111+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V112    (unsigned int)(((float)T9_R112/((float)T9_R112+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V113    (unsigned int)(((float)T9_R113/((float)T9_R113+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V114    (unsigned int)(((float)T9_R114/((float)T9_R114+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V115    (unsigned int)(((float)T9_R115/((float)T9_R115+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V116    (unsigned int)(((float)T9_R116/((float)T9_R116+(float)R))*(float)ADC_TENZO_BITS_REV2)



#define T9_V117    (unsigned int)(((float)T9_R117/((float)T9_R117+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V118    (unsigned int)(((float)T9_R118/((float)T9_R118+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V119    (unsigned int)(((float)T9_R119/((float)T9_R119+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V120    (unsigned int)(((float)T9_R120/((float)T9_R120+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V121    (unsigned int)(((float)T9_R121/((float)T9_R121+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V122    (unsigned int)(((float)T9_R122/((float)T9_R122+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V123    (unsigned int)(((float)T9_R123/((float)T9_R123+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V124    (unsigned int)(((float)T9_R124/((float)T9_R124+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V125    (unsigned int)(((float)T9_R125/((float)T9_R125+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V126    (unsigned int)(((float)T9_R126/((float)T9_R126+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V127    (unsigned int)(((float)T9_R127/((float)T9_R127+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V128    (unsigned int)(((float)T9_R128/((float)T9_R128+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V129    (unsigned int)(((float)T9_R129/((float)T9_R129+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V130    (unsigned int)(((float)T9_R130/((float)T9_R130+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V131    (unsigned int)(((float)T9_R131/((float)T9_R131+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V132    (unsigned int)(((float)T9_R132/((float)T9_R132+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V133    (unsigned int)(((float)T9_R133/((float)T9_R133+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V134    (unsigned int)(((float)T9_R134/((float)T9_R134+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V135    (unsigned int)(((float)T9_R135/((float)T9_R135+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V136    (unsigned int)(((float)T9_R136/((float)T9_R136+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V137    (unsigned int)(((float)T9_R137/((float)T9_R137+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V138    (unsigned int)(((float)T9_R138/((float)T9_R138+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V139    (unsigned int)(((float)T9_R139/((float)T9_R139+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V140    (unsigned int)(((float)T9_R140/((float)T9_R140+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V141    (unsigned int)(((float)T9_R141/((float)T9_R141+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V142    (unsigned int)(((float)T9_R142/((float)T9_R142+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V143    (unsigned int)(((float)T9_R143/((float)T9_R143+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V144    (unsigned int)(((float)T9_R144/((float)T9_R144+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V145    (unsigned int)(((float)T9_R145/((float)T9_R145+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V146    (unsigned int)(((float)T9_R146/((float)T9_R146+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V147    (unsigned int)(((float)T9_R147/((float)T9_R147+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V148    (unsigned int)(((float)T9_R148/((float)T9_R148+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V149    (unsigned int)(((float)T9_R149/((float)T9_R149+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V150    (unsigned int)(((float)T9_R150/((float)T9_R150+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V151    (unsigned int)(((float)T9_R151/((float)T9_R151+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V152    (unsigned int)(((float)T9_R152/((float)T9_R152+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V153    (unsigned int)(((float)T9_R153/((float)T9_R153+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V154    (unsigned int)(((float)T9_R154/((float)T9_R154+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V155    (unsigned int)(((float)T9_R155/((float)T9_R155+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V156    (unsigned int)(((float)T9_R156/((float)T9_R156+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V157    (unsigned int)(((float)T9_R157/((float)T9_R157+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V158    (unsigned int)(((float)T9_R158/((float)T9_R158+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V159    (unsigned int)(((float)T9_R159/((float)T9_R159+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V160    (unsigned int)(((float)T9_R160/((float)T9_R160+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V161    (unsigned int)(((float)T9_R161/((float)T9_R161+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V162    (unsigned int)(((float)T9_R162/((float)T9_R162+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V163    (unsigned int)(((float)T9_R163/((float)T9_R163+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V164    (unsigned int)(((float)T9_R164/((float)T9_R164+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V165    (unsigned int)(((float)T9_R165/((float)T9_R165+(float)R))*(float)ADC_TENZO_BITS_REV2)
#define T9_V166    (unsigned int)(((float)T9_R166/((float)T9_R166+(float)R))*(float)ADC_TENZO_BITS_REV2)
















//TENZO 9  END







#define CRERR_THROTTLE_ON_HIGH      1
#define CRERR_THROTTLE_ZERO_ERR     2
#define CRERR_UBAT_LOW              3
#define CRERR_MPU6050               4
#define CRERR_OVERHEATED_IN         5
#define CRERR_OVERHEATED_OUT        6
#define CRERR_SPD0                  7
#define CRERR_UBAT_HI               8
#define CRERR_THROTTLE_AFTER_TUNING 9
#define CRERR_GYROACC_DISCONNECTED  10
#define CRERR_MASTER_DISCONNECTED   11
#define CRERR_PWM_CHANGED_HIGH      12




#define CRERR_SEC_ERROR_1           249
#define CRERR_SEC_ERROR_2           250
#define CRERR_SEC_ERROR_3           251
#define CRERR_SECRET_UBT            252





#define SELF_TEST_X 13
#define SELF_TEST_Y 14
#define SELF_TEST_Z 15
#define SELF_TEST_A 16
#define SMPLRT_DIV  25
#define CONFIG      26
#define GYRO_CONFIG 27
#define ACCEL_CONFIG    28
#define FIFO_EN     35
#define I2C_MST_CTRL    36
#define I2C_SLV0_ADDR   37
#define I2C_SLV0_REG    38
#define I2C_SLV0_CTRL   39
#define I2C_SLV1_ADDR   40
#define I2C_SLV1_REG    41
#define I2C_SLV1_CTRL   42
#define I2C_SLV2_ADDR   43
#define I2C_SLV2_REG    44
#define I2C_SLV2_CTRL   45
#define I2C_SLV3_ADDR   46
#define I2C_SLV3_REG    47
#define I2C_SLV3_CTRL   48
#define I2C_SLV4_ADDR   49
#define I2C_SLV4_REG    50
#define I2C_SLV4_DO     51
#define I2C_SLV4_CTRL   52
#define I2C_SLV4_DI     53
#define I2C_MST_STATUS  54
#define INT_PIN_CFG     55
#define INT_ENABLE      56
#define INT_STATUS      58
#define ACCEL_XOUT_H    59
#define ACCEL_XOUT_L    60
#define ACCEL_YOUT_H    61
#define ACCEL_YOUT_L    62
#define ACCEL_ZOUT_H    63
#define ACCEL_ZOUT_L    64
#define TEMP_OUT_H      65
#define TEMP_OUT_L      66
#define GYRO_XOUT_H     67
#define GYRO_XOUT_L     68
#define GYRO_YOUT_H     69
#define GYRO_YOUT_L     70
#define GYRO_ZOUT_H     71
#define GYRO_ZOUT_L     72
#define EXT_SENS_DATA_00    73
#define EXT_SENS_DATA_01    74
#define EXT_SENS_DATA_02    75
#define EXT_SENS_DATA_03    76
#define EXT_SENS_DATA_04    77
#define EXT_SENS_DATA_05    78
#define EXT_SENS_DATA_06    79
#define EXT_SENS_DATA_07    80
#define EXT_SENS_DATA_08    81
#define EXT_SENS_DATA_09    82
#define EXT_SENS_DATA_10    83
#define EXT_SENS_DATA_11    84
#define EXT_SENS_DATA_12    85
#define EXT_SENS_DATA_13    86
#define EXT_SENS_DATA_14    87
#define EXT_SENS_DATA_15    88
#define EXT_SENS_DATA_16    89
#define EXT_SENS_DATA_17    90
#define EXT_SENS_DATA_18    91
#define EXT_SENS_DATA_19    92
#define EXT_SENS_DATA_20    93
#define EXT_SENS_DATA_21    94
#define EXT_SENS_DATA_22    95
#define EXT_SENS_DATA_23    96
#define I2C_SLV0_DO 99
#define I2C_SLV1_DO 100
#define I2C_SLV2_DO 101
#define I2C_SLV3_DO 102
#define I2C_MST_DELAY_CTRL  103
#define SIGNAL_PATH_RESET   104
#define USER_CTRL   106
#define PWR_MGMT_1  107
#define PWR_MGMT_2  108
#define FIFO_COUNTH 114
#define FIFO_COUNTL 115
#define FIFO_R_W    116
#define WHO_AM_I    117



extern void InitSegAll(void);
extern void UDPSocketsInit(void);
extern void SegMain(void);
extern void TransmittUDP(void);
extern void ReceiveUDP(void);
extern void WrOdmtr(void);
extern void CountSpd(void);
extern void TrmSteer(void);
extern void RdSensors(void);
extern void VectorInit(void);
extern void TrapeziumInit(void);
extern void ChangeCVR(void);
extern void GyroAcel(void);
extern void ADC2Init(void);
extern void SensorlessInit(void);
extern void SndDebugArrays(void);
extern unsigned char CalcCheckSumm(unsigned int N, unsigned char *Mass);
void Phases1(void);
extern unsigned char ReadSensor1_F(void);
extern unsigned char ReadSensor1_B(void);
extern unsigned char ReadSensor1_B_V(void);
extern unsigned char ReadSensor1_F_V(void);
extern unsigned char InvHalls(unsigned char Sensors);
extern unsigned char ChangeSensorOrder(unsigned char Sns, unsigned char SendOrder);
extern void InitBLDCPorts(void);
extern void SetPWM_ChagerViaMotor();
extern void InitPWM_Vector(void);
extern float GetTemperaturePTC_KTY84_130(unsigned int ResTemp);
extern float GetTemperaturePTC_KTY81_210_FETs(unsigned int ResTemp);
extern float GetTemperaturePTC_KTY83_122(unsigned int ResTemp);
extern float GetTemperaturePTC_KTY83_110(unsigned int ResTemp);
extern float GetTemperature_NCP18XH103F03RB(unsigned int ResTemp);
extern float GetTemperature_MF58_G_10K(unsigned int ResTemp);
extern float GetTemperature_MF58_B_5K(unsigned int ResTemp);
extern float GetTemperature_NTCALUG03A103H(unsigned int ResTemp);
extern float GetTemperaturePTC_KTY81_210(unsigned int ResTemp);
extern void InitPort_U4(void);
extern void UARTInit_U4(void);
extern unsigned char CalcCheckSumm(unsigned int N, unsigned char *Mass);
extern void ReceiveUDP(void);
extern void ButtonsSlave(void);
extern void RecSlave2WDControls(void);
extern void SegAll(void);



#if defined VECTORMS
extern const float CurrPerDigitDEF;
#else
const float CurrPerDigitDEF = 96.68; //29.296;//14.648;
#endif
extern unsigned int StartingMoveCnt, CurrLimitWork, CurrLimit, Hv2WDMasterCnt, SlaveADCThrottle, SlaveADCThrottleBreak;
extern unsigned int Bt1LongCnt, Bt2LongCnt, Bt3LongCnt, Bt4LongCnt;
extern STAT_FLAGS StatFlgs, StatFlgs1, StatFlgs2, StatFlgs3, StatFlgs4;
extern FLAGS Flgs, Flgs1, Flgs2, Flgs3, Flgs4, Flgs5, Flgs6, Flgs7, Flgs8, FlgsErr, Flgs1Err, Flgs2Err;
extern float TiltZad, KpAddSpd, TiltZadAdd, TiltZadTmp, TiltChng, TiltZadAddMustBe, TiltZadState5, TiltZadWheeling, SpdStartLevelFl;
extern float KpKpSpd, KdAddSpd, KdKpSpd, SlowSpeedForKpFl;
extern float E, EPlus, EPrevPlus, KdNoMan, KdNoManR, KdOneTwoLeg, EPrev, KpMustBe, KpNoMan, KdMustBe;
extern float KpWheelingMem, KpSlowSpeed, KiKp, KiKpMustBe;
extern float KdMax, KdMin, KiKd, Eid, KdDiff, KdMustBePrev, KiMustBe1, KiAdd, ELimited, ELimitedMem;
extern float KpRot, KpRotMustBe, KdRot, KiRot, KiRotMustBe, KpMax, KiMax, KpMin;
extern float KpWheelingMem, KpSlowSpeed, KiKp, KiKpMustBe, EiPWMmax;
extern float AlfaXRes, AlfaYRes, AlfaZRes, AlfaXResPrev, AlfaYResPrev, AlfaZResPrev, KiKpDeadZone;
extern float Spd1Fl, Spd1FlPlus, KpKpDeadZone, KpKpZoneEnd, KpKp2ZoneEnd, KpDeadZone, EpPWMmax;
extern float Ep, Ed, Ei, Kp, Kd, Ki, KiMustBe, KiNoMan, KiWheelingMem, ESumm, EdPWMmax, KpKp2DeadZone;
extern float AddTilt, AddTiltLimit, KpKpMustBe, KpKp2MustBe, KpKp, KpKp2, Kp_p, Kp2, KpK, KiK, Ki_p, Ki_pp, Ki_pPrev, Ki_ppDelta;
extern float GyroXFl, GyroYFl, GyroZFl;
extern float XNew, YNew, ZNew, YNewShow;
extern float AccXFlPrev, AccYFlPrev, AccZFlPrev;
extern float AlfaXRes, AlfaYRes, AlfaZRes, AlfaXResPrev, AlfaYResPrev, AlfaZResPrev;
extern float KGYRO, KACC;
extern float AccXFl, AccYFl, AccZFl;
extern unsigned char MaxAngleStopBreak, Sounds, SoundNum, CriticalError, KdStateMachine, PhasePERMASS_SHFT, TestSIN_OkCnt;
extern unsigned char CntKdSwitch, CntKdSwitchCONST, Sensor1_Prev, Sensor1, HallDelayCnt_1, Halls, SensOrder1, Theta1Zero;
extern unsigned char HC05TrmMass[FLASHMASS_SIZE + 10], SndDebugArraysStateMachine, Sensor1_Prev_OP, PhasePERMASS;
extern unsigned char CntTrmSteer, CntTrmSteer_N, TrmMass_U3[255], TiltTimoutCnt, TiltTimoutConst;
extern unsigned char PacketTrm_U3[40], Bt1Cnt, Bt2Cnt, Bt3Cnt, Bt4Cnt, Bt1CntConst, Bt2CntConst, Bt3CntConst, Bt4CntConst;
extern unsigned char PacketRec_U3[30];
extern char TrmMassHC05[100];
extern char RecMassHC05[100];
extern BYTE RecBytes[254];
extern char NearSensors[8][4], HallDelay1_F, HallDelay1_FMustBe, HallDelay1_B, HallDelay1_BMustBe;
extern const unsigned char LowDrive[7], HiDrive[7];
extern int Spd1Res, Spd1KpLevel, Spd1KdLevel, Spd1ResPrev, SpdPID, Spd1ResPlus, Spd1Cnt, SpdTmp, Spd1ResPlusTST;
extern int XLimit, YLimit, GyroZFlTurn, CurrUst, PWMMonocycleSlaveFmMaster;
extern int BreakMonocycleSpd, TimeDecreaseKi, MAX_PWM_CONST;
extern int OnDelayConst, OnDelayCnt, CurrUstWork, Spd1Cnt;
extern int TiltXThis, TiltYThis, MAX_PWM, PWM1Show;
extern unsigned int SV_PWM1_0, SV_PWM1_1, SV_PWM1_2, BuzzerOffTime, Odometr10m, Theta1Cnt, PR8Temp, BackwardCnt, HallErrCnt;
extern unsigned int Theta1CntPWM, Khard, CntU4TimeOut, SerNumber;
extern long int GyroZFilter, PWM1Temp, RotAddSumm, KFilterPrev, KFilter, Phase1Period1, PI_Curr1Res;
extern unsigned long int Odometr, Distance, Phase1PeriodSumm, Phase1PeriodMass[PhasePERMASS_DEF], PhasePWM;
extern unsigned long int Amplitude1, Amplitude1Tmp;
extern float EpLog, EiLog, EdLog;
extern unsigned int MotorPhaseA, MotorPhaseB, MotorPhaseC, MotorNeutralVoltage, _1sCnt1, PWM_Sensorless;
extern unsigned int MassTMPPhaseA[MassTMPSIZE], MassTMPPhaseB[MassTMPSIZE], MassTMPPhaseC[MassTMPSIZE], MassTMPNeutral[MassTMPSIZE], CntPhase;
extern unsigned int Idx, BemfFilterHiCnt, BemfFilterHi, BEMFHallCntMax, Phase1Period1Up, TimeOutHC05;
