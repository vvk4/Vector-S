#include "Mn.h"



int CntTrmHC05_N;
unsigned char CntTrmHC05,CntRecHC05,BtRcPrev_U4,CntRec_U4;


void UARTInit_U4(void) {

    IPC22bits.U4TXIP = 1;
    IPC22bits.U4RXIP = 7;


#if defined REV2
#if defined SERVICE
    if (U4_9600)
#else
    if (0)
#endif
        U4BRG = 390; //
    else
        U4BRG = 97; //390;//32;//
#else
    U4BRG = 97; //390;//
#endif    




    U4MODEbits.UARTEN = 1; // UART2 is Enabled
    U4MODEbits.USIDL = 0; // Continue operation at Idlestate
    U4MODEbits.IREN = 0; // IrDA En/Decoder is disabled
    U4MODEbits.RTSMD = 1; // Simplex mode
    U4MODEbits.UEN = 0b00; // UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by port latches.
    U4MODEbits.WAKE = 0; // Wake-up on start bit is enabled
    U4MODEbits.LPBACK = 0; // Loop-back is disabled
    U4MODEbits.ABAUD = 0; // auto baud is disabled
    U4MODEbits.RXINV = 0; // No RX inversion
    U4MODEbits.BRGH = 0; //1;		// low boud rate
    U4MODEbits.PDSEL = 0b00; // 8bit no parity
    U4MODEbits.STSEL = 0; // one stop bit


    U4STAbits.UTXISEL0 = 0;
    U4STAbits.UTXISEL1 = 0;
    U4STA &= 0xDFFF; // clear TXINV by bit masking
    U4STAbits.UTXBRK = 0; // sync break tx is disabled
    U4STAbits.UTXEN = 1; //transmit  is enabled
    U4STAbits.URXISEL = 0b00; // interrupt flag bit is set when RXBUF is filled whith 1 character
    U4STAbits.ADDEN = 0; // address detect mode is disabled

    IFS5bits.U4RXIF = 0; // clear interrupt flag of rx
    IEC5bits.U4RXIE = 1; // enable rx recieved data interrupt

    IFS5bits.U4TXIF = 0; // clear interrupt flag of rx
    IEC5bits.U4TXIE = 0; // enable rx recieved data interrupt


    //     U4TXREG = 0xaa;



}

void __attribute__((interrupt, auto_psv)) _U4TXInterrupt(void) {
    IFS5bits.U4TXIF = 0; // Clear TX Interrupt flag
    //U4TXREG = 0xab;
    //return;
    TimeOutHC05 = 125;

    if (CntTrmHC05 < CntTrmHC05_N) {
        if (AT_Trm)
            U4TXREG = TrmMassHC05[CntTrmHC05];
        else
            U4TXREG = HC05TrmMass[CntTrmHC05];

        CntTrmHC05++;
    } else {
        OnTransmittHC05 = 0;
        HC05_BUSY = 0;
        IEC5bits.U4TXIE = 0; // enable rx recieved data interrupt
    }


}

void InitPort_U4(void) {
    TRISGbits.TRISG14 = 0;
    TRISGbits.TRISG12 = 1;

    RPINR28bits.U4RXR = 124;
    RPOR15bits.RP126R = 0b011101;
#ifdef REV2
    TRIS_KEY_BT = 0;
#endif
}

void __attribute__((interrupt, auto_psv)) _U4RXInterrupt() { //?????????????????????????????? ?????? ?????????????????? ??????????????? UART2
    // ??????????????? ?????? ?????????????????????????????????
    unsigned char BtRc;
    BtRc = U4RXREG;
    IFS5bits.U4RXIF = 0; // ??????????????? ???????????????

    CntU4TimeOut = 500;

    if (U4STAbits.OERR) {
        U4STAbits.OERR = 0;
    }


    if (AT_Rec) {


        RecMassHC05[CntRecHC05] = BtRc;
        CntRecHC05++;

        if ((CntRecHC05 > 2)&&(RecMassHC05[CntRecHC05 - 2] == 13)&&(RecMassHC05[CntRecHC05 - 1] == 10)) {
            CntRecHC05 = 0;
            HvReplyHC05 = 1;
        }
    } else {


        if (!GettingPacketU4_FL) {
            if ((BtRc == BtRcPrev_U4)&&(BtRc == 0xff)) {
                BtRcPrev_U4 = 0;
                GettingPacketU4_FL = 1;
                CntRec_U4 = 0;
            } else {
                BtRcPrev_U4 = BtRc;
            }
        } else {
            if (CntRec_U4 > (sizeof (RecBytes) - 1))
                GettingPacketU4_FL = 0;
            else {
                RecBytes[CntRec_U4] = BtRc;
                CntRec_U4++;
                if (CntRec_U4 > (RecBytes[0] + 1)) {
                    GettingPacketU4_FL = 0;
                    //     TiltTimoutCnt=TiltTimoutConst;



                    if (CalcCheckSumm(RecBytes[0] + 1, RecBytes) != RecBytes[RecBytes[0] + 1]) {
                        CHK_Err_U4 = 1;
                    } else {
                        /*                           int nn=RecBytes[0];
                                                   int j;
                                                   for (j=0;j<nn;j++)
                                                   {
                                                       RecBytes[j]=RecBytes[j+1];
                                                   }*/
                        HvPacketU4_FL = 1;

                    }
                }
            }




        }
    }


}

void TrmHC05_AT(char *Mass, int N) {
    int i;
    while (OnTransmittHC05);

    AT_Trm = 1;

    for (i = 0; i < 30000; i++);

    for (i = 0; i < N; i++) {
        TrmMassHC05[i] = Mass[i];
    }


    TrmMassHC05[i - 1] = 0xd;
    TrmMassHC05[i] = 0xa;
    if (MustResetPIN) {
        TrmMassHC05[i + 1] = 0xd;
        TrmMassHC05[i + 2] = 0xa;
        //N++;
        //N++;
    }


    OnTransmittHC05 = 1;
    CntTrmHC05 = 1;
    CntTrmHC05_N = N + 1;

    U4TXREG = TrmMassHC05[0];
    IEC5bits.U4TXIE = 1;


}

void TrmHC05(unsigned char *Mass) {
    unsigned char N = Mass[2];



    while (OnTransmittHC05);



    AT_Trm = 0;




    OnTransmittHC05 = 1;
    CntTrmHC05 = 1;
    CntTrmHC05_N = N + 4;

    U4TXREG = Mass[0];
    IEC5bits.U4TXIE = 1;


}

void CloseU4(void) {
    RPINR28bits.U4RXR = 0;
    RPOR4bits.RP79R = 0;
    U4MODEbits.UARTEN = 0;
}



