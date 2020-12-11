#include "Mn.h"

#define BEMF_FILTER    3
#define BEMF_FILTER_HI 10
#define SUMM_CNT       2
void FillSndArray(unsigned char * Array, unsigned int Index, unsigned char Cmd);

int CntDebugArray;
unsigned int Idx, BemfFilterHi = BEMF_FILTER_HI, BemfFilterHiCnt, PeriodCnt, PeriodSumm, SummCnt, BEMFHallCnt, BEMFHallCntMax;
unsigned char SndDebugArraysStateMachine, BEMFAStateMachine, BEMFBStateMachine, BEMFCStateMachine;
unsigned char BEMFACnt, PhaseACnt, BEMFBCnt, PhaseBCnt, BEMFCCnt, PhaseCCnt;
unsigned char PEN1_A_H_Prev, PEN1_B_H_Prev, PEN1_C_H_Prev, Snsr;

void SensorlessInit(void) {
    ADC2Init();
}

void ADC2Init(void) {

    /* Set port configuration */
    //ANSELA = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    //ANSELB = 0x012C; // Ensure AN2, AN3, AN5 and AN8 are analog
    /* Initialize ADC module */
    AD2CON1 = 0x04E4; // Enable 12-bit mode, auto-sample and auto-conversion
    AD2CON2 = 0x0408; // Sample 4 channels alternately using channel scanning
    AD2CON2bits.SMPI = 2;
    AD2CON3 = 0xff; //0x0F0F; // Sample for 15*TAD before converting
    AD2CON4 = 0x0000;


    AD2CSSL = 0; //b111;
    AD2CHS0bits.CH0SA = 0; // CH0SA bits ignored for CH0 +ve input selection
    AD2CHS0bits.CH0NA = 0; // Select VREF- for CH0 -ve input


    AD2CON1bits.SSRC = 0; //
    AD2CON1bits.SSRCG = 1;
    //---------------------
    AD2CON2bits.CHPS = 2;
    AD2CON2bits.SMPI = 0;
    AD2CON1bits.SIMSAM = 1;
    AD2CON3bits.ADCS = 0xf;
    AD2CON3bits.SAMC = 0x2;

    AD2CHS123bits.CH123SA = 0;
    /* Enable ADC module and provide ADC stabilization delay */

    AD2CON1bits.ADON = 1;
    IFS1bits.AD2IF = 0;
    IPC5bits.AD2IP = 7;
    IEC1bits.AD2IE = 1;



    int k;
    for (k = 0; k < 20000; k++);



}

void ADC2Init1(void) {

    /* Set port configuration */
    //ANSELA = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    //ANSELB = 0x012C; // Ensure AN2, AN3, AN5 and AN8 are analog
    /* Initialize ADC module */
    AD2CON1 = 0x04E4; // Enable 12-bit mode, auto-sample and auto-conversion
    AD2CON2 = 0x0408; // Sample 4 channels alternately using channel scanning
#if defined REV2
    //AD2CON2bits.CHPS=0x10;
    //AD2CON1bits.SIMSAM=1;
#endif
    AD2CON3 = 5; //0x0F0F; // Sample for 15*TAD before converting
    AD2CON4 = 0x0000;
    //AD2CSSH=0b000000000100000;
    // AD2CSSL=0b00000000001110;
    AD2CSSL = 0b00000000000111;
    //   AD1CSSL=0b110000000000000;
    //AD1CSSH = 0x0000;
    //AD1CSSL = 0x012C; // Select AN2, AN3, AN5 and AN8 for scanning
    /* Assign MUXA inputs */
    AD2CHS0bits.CH0SA = 0; // CH0SA bits ignored for CH0 +ve input selection
    AD2CHS0bits.CH0NA = 0; // Select VREF- for CH0 -ve input


    AD2CON1bits.SSRC = 3;
    AD2CON1bits.SSRCG = 0;

    /* Enable ADC module and provide ADC stabilization delay */
    AD2CON1bits.ADON = 1;
    IFS1bits.AD2IF = 0;
    IPC5bits.AD2IP = 7;
    IEC1bits.AD2IE = 1;

    int k;
    for (k = 0; k < 20000; k++);


}

void __attribute__((interrupt, auto_psv)) _AD2Interrupt(void) {
    unsigned char LowDrv, HiDrv;


    IFS1bits.AD2IF = 0;


    TST_PIN = !TST_PIN;

    //  if (Sensor1_Prev==1)

    MotorPhaseC = ADC2BUF1;
    MotorPhaseB = ADC2BUF2;
    MotorPhaseA = ADC2BUF3;



    MotorNeutralVoltage = (MotorPhaseA + MotorPhaseB + MotorPhaseC) / 3;

    if ((PEN1_A_H != PEN1_A_H_Prev) || (PEN1_B_H != PEN1_B_H_Prev) || (PEN1_C_H != PEN1_C_H_Prev)) {
        BemfFilterHi = BemfFilterHiCnt >> 2;
        if (BemfFilterHi<BEMF_FILTER_HI)
            BemfFilterHi=BEMF_FILTER_HI;
        BemfFilterHiCnt = 0;
        PEN1_A_H_Prev = PEN1_A_H;
        PEN1_B_H_Prev = PEN1_B_H;
        PEN1_C_H_Prev = PEN1_C_H;
    }

    BemfFilterHiCnt++;





    switch (BEMFAStateMachine) {
        case 0:
            if (MotorPhaseA > MotorNeutralVoltage) {
                PhaseACnt++;
                if (PhaseACnt > BemfFilterHi) {
                    BEMFAStateMachine = 1;
                }
            } else
                PhaseACnt = 0;
            break;
        case 1:
            if (MotorPhaseA < MotorNeutralVoltage) {
                BEMFAStateMachine = 2;
                BEMFACnt = 0;
            }
            break;
        case 2:
            if (MotorPhaseA < MotorNeutralVoltage) {
                BEMFACnt++;
                if (BEMFACnt > BEMF_FILTER) {
                    BEMFAStateMachine = 0;
                    BEMFA_OK = 1;
                    BEMF_OK = 1;
                    A2_OK = 0;
                    PhaseACnt = 0;
                }
            } else {
                BEMFAStateMachine = 1;
            }
            break;
        default:
            BEMFAStateMachine = 0;
            break;
    }

    switch (BEMFBStateMachine) {
        case 0:
            if (MotorPhaseB > MotorNeutralVoltage) {
                PhaseBCnt++;
                if (PhaseBCnt > BemfFilterHi) {
                    BEMFBStateMachine = 1;
                }
            } else
                PhaseBCnt = 0;
            break;
        case 1:
            if (MotorPhaseB < MotorNeutralVoltage) {
                BEMFBStateMachine = 2;
                BEMFBCnt = 0;
            }
            break;
        case 2:
            if (MotorPhaseB < MotorNeutralVoltage) {
                BEMFBCnt++;
                if (BEMFBCnt > BEMF_FILTER) {
                    BEMFBStateMachine = 0;
                    BEMFB_OK = 1;
                    BEMF_OK = 1;
                    B2_OK = 0;
                    PhaseBCnt = 0;
                }
            } else {
                BEMFBStateMachine = 1;
            }
            break;
        default:
            BEMFBStateMachine = 0;
            break;
    }

    switch (BEMFCStateMachine) {
        case 0:
            if (MotorPhaseC > MotorNeutralVoltage) {
                PhaseCCnt++;
                if (PhaseCCnt > BemfFilterHi) {
                    BEMFCStateMachine = 1;
                }
            } else
                PhaseCCnt = 0;
            break;
        case 1:
            if (MotorPhaseC < MotorNeutralVoltage) {
                BEMFCStateMachine = 2;
                BEMFCCnt = 0;
            }
            break;
        case 2:
            if (MotorPhaseC < MotorNeutralVoltage) {
                BEMFCCnt++;
                if (BEMFCCnt > BEMF_FILTER) {
                    BEMFCStateMachine = 0;
                    BEMFC_OK = 1;
                    BEMF_OK = 1;
                    C2_OK = 0;
                    PhaseCCnt = 0;
                }
            } else {
                BEMFCStateMachine = 1;
            }
            break;
        default:
            BEMFCStateMachine = 0;
            break;
    }

    PeriodCnt++;

    if (BEMF_OK)//||BEMFB_OK||BEMFC_OK) 
    {
        PeriodSumm = PeriodSumm + PeriodCnt;
        BEMF_OK = 0;
        MotorNeutralVoltage = 1000;
        SummCnt++;
        if (SummCnt >= SUMM_CNT) {
            SummCnt = 0;
            BEMFHallCnt = PeriodSumm >> 3;
            BEMFHallCntMax = PeriodSumm >> 2;
            PeriodSumm = 0;
            /*if (CntPhase < MassTMPSIZE) {//Fill debug array
                MassTMPPhaseB[CntPhase++] = BEMFHallCnt;
              }*/
        }
        PeriodCnt = 0;

    }

    BEMFHallCnt++;
    if (BEMFHallCnt >= BEMFHallCntMax) {
        BEMFHallCnt = 0;

        if (Sensorless2) {
            if (BEMFA_OK) {
                if (!A2_OK) {
                    A2_OK = 1;
                    Snsr = 1;
                    MotorNeutralVoltage = 2000;
                } else {
                    BEMFA_OK = 0;
                    Snsr = 3;
                    MotorNeutralVoltage = 2000;
                }
            } else
                if (BEMFB_OK) {
                if (!B2_OK) {
                    Snsr = 2;
                    MotorNeutralVoltage = 2000;
                    B2_OK = 1;
                } else {
                    Snsr = 6;
                    MotorNeutralVoltage = 2000;
                    BEMFB_OK = 0;
                }
            } else
                if (BEMFC_OK) {
                if (!C2_OK) {
                    Snsr = 4;
                    MotorNeutralVoltage = 2000;
                    C2_OK = 1;
                } else {
                    Snsr = 5;
                    MotorNeutralVoltage = 2000;
                    BEMFC_OK = 0;
                }
            }
                else
                    Snsr = 0;

            PWM1_A_H = 0;
            PWM1_A_L = 0;
            PWM1_B_H = 0;
            PWM1_B_L = 0;
            PWM1_C_H = 0;
            PWM1_C_L = 0;
            if (Snsr)
            {
            LowDrv = LowDrive[Snsr];
            HiDrv = HiDrive[Snsr];



            if (HiDrv & 1) {//A
                PEN1_A_H = 1;
                if (StrongMode)
                    PEN1_A_L = 1;
                else
                    PEN1_A_L = 0;
                PEN1_B_H = 0;
                PEN1_B_L = 0;
                PEN1_C_H = 0;
                PEN1_C_L = 0;
            }
            else
            if (HiDrv & 2) {
                PEN1_A_H = 0;
                PEN1_A_L = 0;

                PEN1_B_H = 1;
                if (StrongMode)
                    PEN1_B_L = 1;
                else
                    PEN1_B_L = 0;
                PEN1_C_H = 0;
                PEN1_C_L = 0;
            }
            else
            if (HiDrv & 4) {//C
                PEN1_A_H = 0;
                PEN1_A_L = 0;
                PEN1_B_H = 0;
                PEN1_B_L = 0;
                PEN1_C_H = 1;
                if (StrongMode)
                    PEN1_C_L = 1;
                else
                    PEN1_C_L = 0;
            }
            if (LowDrv & 1)
                PWM1_A_L = 1;
            else
            if (LowDrv & 2)
                PWM1_B_L = 1;
            else
            if (LowDrv & 4)
                PWM1_C_L = 1;
        }
            else
            {
                PEN1_A_H = 0;
                PEN1_A_L = 0;
                PEN1_B_H = 0;
                PEN1_B_L = 0;
                PEN1_C_H = 0;
                PEN1_C_L = 0;
            }
        }



    }

/*
    MotorPhaseA = Sensor1_Prev;
    MotorPhaseB = Snsr;

    MotorPhaseA = MotorPhaseA * 100;
    MotorPhaseB = MotorPhaseB * 110;
    */
    

    if (CntPhase < MassTMPSIZE) {//Fill debug array
        MassTMPPhaseA[CntPhase] = MotorPhaseA;
        MassTMPPhaseB[CntPhase] = MotorPhaseB;
        MassTMPPhaseC[CntPhase] = MotorPhaseC;
        MassTMPNeutral[CntPhase++] = MotorNeutralVoltage;
    }

}

void SndDebugArrays(void) {

    if (HC05_BUSY)
        return;

    if (!Hv_HC05)
        return;
    if (!SendingMass)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    switch (SndDebugArraysStateMachine) {
        case 1:
            //            for (i = 0; i<sizeof (MassTMPPhaseA); i++)
            //                MassTMPPhaseA[i] = i;

            if ((Idx + 246)>sizeof (MassTMPPhaseA)) {
                SndDebugArraysStateMachine = 2;
                Idx = 0;
            } else
                FillSndArray((unsigned char *) MassTMPPhaseA, Idx, 8);
            break;
        case 2:
            //            for (i = 0; i<sizeof (MassTMPPhaseB); i++)
            //                MassTMPPhaseB[i] = i+100;

            if ((Idx + 246)>sizeof (MassTMPPhaseB)) {
                SndDebugArraysStateMachine = 3;
                Idx = 0;
            } else
                FillSndArray((unsigned char *) MassTMPPhaseB, Idx, 9);
            break;
        case 3:
            //            for (i = 0; i<sizeof (MassTMPPhaseC); i++)
            //                MassTMPPhaseC[i] = i+200;

            if ((Idx + 246)>sizeof (MassTMPPhaseC)) {
                SndDebugArraysStateMachine = 4;
                Idx = 0;
            } else
                FillSndArray((unsigned char *) MassTMPPhaseC, Idx, 19);
            break;
        case 4:
            //            for (i = 0; i<sizeof (MassTMPNeutral); i++)
            //                MassTMPNeutral[i] = i+300;

            if ((Idx + 246)>sizeof (MassTMPNeutral)) {
                SndDebugArraysStateMachine = 5;
                Idx = 0;
            } else
                FillSndArray((unsigned char *) MassTMPNeutral, Idx, 20);
            break;
        default:
            SendingMass = 0;
            break;
    }


    MustTrmHC05 = 1;

}

void FillSndArray(unsigned char * Array, unsigned int Index, unsigned char Cmd) {
    unsigned int i;


    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;
    HC05TrmMass[2] = 247;

    HC05TrmMass[3] = Cmd; //COMMAND
    for (i = 4; i < 250; i++) {
        HC05TrmMass[i] = Array[Index + i - 4];
    }
    Idx = Index + i - 4;
    HC05TrmMass[i] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);
}