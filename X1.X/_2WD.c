#include "Mn.h"


unsigned char BtRcPrev_U3,CntRec_U3;


void UARTInit_U3(void) {

    IPC20bits.U3TXIP = 2;
    IPC20bits.U3RXIP = 7;



    U3BRG = 129; //34;// 115200




    U3MODEbits.UARTEN = 1; 
    U3MODEbits.USIDL = 0; 
    U3MODEbits.IREN = 0; 
    U3MODEbits.RTSMD = 1;
    U3MODEbits.UEN = 0b00;
    U3MODEbits.WAKE = 0; 
    U3MODEbits.LPBACK = 0;
    U3MODEbits.ABAUD = 0; 
    U3MODEbits.RXINV = 0; 
    U3MODEbits.BRGH = 1; 
    U3MODEbits.PDSEL = 0b00;
    U3MODEbits.STSEL = 0; 


    U3STAbits.UTXISEL0 = 0;
    U3STAbits.UTXISEL1 = 0;
    U3STA &= 0xDFFF; 
    U3STAbits.UTXBRK = 0;
    U3STAbits.UTXEN = 1; 
    U3STAbits.URXISEL = 0b00; 
    U3STAbits.ADDEN = 0;

    IFS5bits.U3RXIF = 0;
    IEC5bits.U3RXIE = 1;

    IFS5bits.U3TXIF = 1;
    IEC5bits.U3TXIE = 0;

}

void __attribute__((interrupt, auto_psv)) _U3TXInterrupt(void) {
    IFS5bits.U3TXIF = 0; 

    if (CntTrmSteer < CntTrmSteer_N) {
        U3TXREG = TrmMass_U3[CntTrmSteer];
        CntTrmSteer++;
    } else {
        OnTransmitt_U3 = 0;
        IEC5bits.U3TXIE = 0; 
    }




}

void InitPort_U3(void) {
    TRISFbits.TRISF13 = 0;
    TRISAbits.TRISA1 = 1;
    RPINR27bits.U3RXR = 17;
    RPOR12bits.RP109R = 0b011011;
}

void __attribute__((interrupt, auto_psv)) _U3RXInterrupt() { 

    unsigned char BtRc;
    BtRc = U3RXREG;
    IFS5bits.U3RXIF = 0;

    if (U3STAbits.OERR) {
        U3STAbits.OERR = 0;
    }

    if (!GettingPacketU3_FL)
    {
        if ((BtRc == BtRcPrev_U3)&&(BtRc == 0xff)) {
            BtRcPrev_U3 = 0;
            GettingPacketU3_FL = 1;
            CntRec_U3 = 0;
        } else {
            BtRcPrev_U3 = BtRc;
        }
    } else {
        if (CntRec_U3 > 30)
            GettingPacketU3_FL = 0; 
        else {
            PacketRec_U3[CntRec_U3] = BtRc; 
            CntRec_U3++; 
            if (CntRec_U3 > (PacketRec_U3[0] + 1))
            {
                GettingPacketU3_FL = 0;

                TiltTimoutCnt = TiltTimoutConst;

                if (CalcCheckSumm(PacketRec_U3[0] + 1, PacketRec_U3) != PacketRec_U3[PacketRec_U3[0] + 1])
                {
                    CHK_Err_U3 = 1; 
                } else {
                    if (PacketRec_U3[1] != 57)
                        HvDataPacketU3_FL = 1;
                    else {
                        if ((PacketRec_U3[2] == 0)&&(PacketRec_U3[3] == 0x73)&&(PacketRec_U3[4] == 0xb2)) {
                            int Tm = PacketRec_U3[6];
                            Tm = Tm << 8;
                            Tm = Tm + PacketRec_U3[5];
                            if (Tm == SerNumber) {
                                U4MODE = 0;
                                U4_9600 = 1;
                                MODE_LED = 1;
                                UARTInit_U4();
                                SoundNum = 2;
                                Locked = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}



void RecSlave2WDControls(void) {
    unsigned int CntBt = 3;
    if (!HvDataPacketU3_FL)
        return;
    HvDataPacketU3_FL = 0;

    Hv2WDMasterCnt = 1250;
    Hv2WDMaster = 1;

    switch (PacketRec_U3[1]) {
        case 1:
            if (PacketRec_U3[2]&0x01)
                SlaveBut1 = 1;
            else
                SlaveBut1 = 0;
            if (PacketRec_U3[2]&0x02)
                SlaveBut2 = 1;
            else
                SlaveBut2 = 0;
            if (PacketRec_U3[2]&0x04)
                SlaveBut3 = 1;
            else
                SlaveBut3 = 0;
            if (PacketRec_U3[2]&0x08)
                SlaveBut4 = 1;
            else
                SlaveBut4 = 0;
            if (PacketRec_U3[2]&0x10)
                SlaveBreak = 1;
            else
                SlaveBreak = 0;

            if (PacketRec_U3[2]&0x20)
                MonocycleSlave = 1;
            else
                MonocycleSlave = 0;

            if (PacketRec_U3[2]&0x40)
                NoBalanceFmMaster = 1;
            else
                NoBalanceFmMaster = 0;


            SlaveADCThrottle = PacketRec_U3[CntBt++];
            SlaveADCThrottle = SlaveADCThrottle + (((int) PacketRec_U3[CntBt++]) << 8);
            SlaveADCThrottleBreak = PacketRec_U3[CntBt++];
            SlaveADCThrottleBreak = SlaveADCThrottleBreak + (((int) PacketRec_U3[CntBt++]) << 8);

            PWMMonocycleSlaveFmMaster = PacketRec_U3[CntBt++];
            PWMMonocycleSlaveFmMaster = PWMMonocycleSlaveFmMaster + (((int) PacketRec_U3[CntBt++]) << 8);


            HvButtonsFromMaster = 1;

            break;
    }
}



void ButtonsSlave(void) {

#if !defined REV2
    unsigned char HvBt1Tmp, HvBt2Tmp, HvBt3Tmp, HvBt4Tmp, HvBt5Tmp;
    unsigned char Bt1UpTmp, Bt2UpTmp, Bt3UpTmp, Bt4UpTmp, Bt5UpTmp;
#endif
    if (StartingBTN) {
        if (!SlaveBut1) {
            But1Pressed = 1;
            HvBt1 = 1;
        } else {
            But1Pressed = 0;
            Bt1Up = 1;
        }

        if (!SlaveBut2) {
            But2Pressed = 1;
            HvBt2 = 1;
        } else {
            But2Pressed = 0;
            Bt2Up = 1;
        }

        if (!SlaveBut3) {
            But3Pressed = 1;
            HvBt3 = 1;
        } else {
            But3Pressed = 0;
            Bt3Up = 1;
        }
        if (!SlaveBut4) {
            But4Pressed = 1;
            HvBt4 = 1;
        } else {
            But4Pressed = 0;
            Bt4Up = 1;
        }

    }
    //   return;
    if (!But1Pressed) {
        if (Bt1Cnt) {
            if (!SlaveBut1) {
                Bt1Cnt = Bt1CntConst;
                But1Pressed = 1;
            } else {
                Bt1Cnt--;
                if (!Bt1Cnt) {
                    Drebezg1 = 0;
                    Bt1Up = 1;
                }
            }
        } else {
            Bt1LongCnt = 0;
            if (!SlaveBut1) {
                Bt1Cnt = Bt1CntConst;
                But1Pressed = 1;
            }
        }
    } else {
        if (Bt1Cnt) {
            if (SlaveBut1) {
                Bt1Cnt = Bt1CntConst;
                But1Pressed = 0;
            } else {
                Bt1Cnt--;
                if (!Bt1Cnt) {
                    if (!Drebezg1) {
                        HvBt1 = 1;
                        Drebezg1 = 1;
                        Bt1LongCnt = 0;
                    }
                }
            }
        } else {
            if (SlaveBut1) {
                Bt1Cnt = Bt1CntConst;
                But1Pressed = 0;
            }
            Bt1LongCnt++;
        }
    }



    if (!But2Pressed) {
        if (Bt2Cnt) {
            if (!SlaveBut2) {
                Bt2Cnt = Bt2CntConst;
                But2Pressed = 1;
            } else {
                Bt2Cnt--;
                if (!Bt2Cnt) {
                    Drebezg2 = 0;
                    Bt2Up = 1;
                }
            }
        } else {
            Bt2LongCnt = 0;
            if (!SlaveBut2) {
                Bt2Cnt = Bt2CntConst;
                But2Pressed = 1;
            }
        }
    } else {
        if (Bt2Cnt) {
            if (SlaveBut2) {
                Bt2Cnt = Bt2CntConst;
                But2Pressed = 0;
            } else {
                Bt2Cnt--;
                if (!Bt2Cnt) {
                    if (!Drebezg2) {
                        HvBt2 = 1;
                        Drebezg2 = 1;
                        Bt2LongCnt = 0;
                    }
                }
            }
        } else {
            if (SlaveBut2) {
                Bt2Cnt = Bt2CntConst;
                But2Pressed = 0;
            }
            Bt2LongCnt++;
        }
    }



    if (!But3Pressed) {
        if (Bt3Cnt) {
            if (!SlaveBut3) {
                Bt3Cnt = Bt3CntConst;
                But3Pressed = 1;
            } else {
                Bt3Cnt--;
                if (!Bt3Cnt) {
                    Drebezg3 = 0;
                    Bt3Up = 1;
                }
            }
        } else {
            Bt3LongCnt = 0;
            if (!SlaveBut3) {
                Bt3Cnt = Bt3CntConst;
                But3Pressed = 1;
            }
        }
    } else {
        if (Bt3Cnt) {
            if (SlaveBut3) {
                Bt3Cnt = Bt3CntConst;
                But3Pressed = 0;
            } else {
                Bt3Cnt--;
                if (!Bt3Cnt) {
                    if (!Drebezg3) {
                        HvBt3 = 1;
                        Drebezg3 = 1;
                        Bt3LongCnt = 0;
                    }
                }
            }
        } else {
            if (SlaveBut3) {
                Bt3Cnt = Bt3CntConst;
                But3Pressed = 0;
            }
            Bt3LongCnt++;
        }
    }




    if (!But4Pressed) {
        if (Bt4Cnt) {
            if (!SlaveBut4) {
                Bt4Cnt = Bt4CntConst;
                But4Pressed = 1;
            } else {
                Bt4Cnt--;
                if (!Bt4Cnt) {
                    Drebezg4 = 0;
                    Bt4Up = 1;
                }
            }
        } else {
            Bt4LongCnt = 0;
            if (!SlaveBut4) {
                Bt4Cnt = Bt4CntConst;
                But4Pressed = 1;
            }
        }
    } else {
        if (Bt4Cnt) {
            if (SlaveBut4) {
                Bt4Cnt = Bt4CntConst;
                But4Pressed = 0;
            } else {
                Bt4Cnt--;
                if (!Bt4Cnt) {
                    if (!Drebezg4) {
                        HvBt4 = 1;
                        Drebezg4 = 1;
                        Bt4LongCnt = 0;
                    }
                }
            }
        } else {
            if (SlaveBut4) {
                Bt4Cnt = Bt4CntConst;
                But4Pressed = 0;
            }
            Bt4LongCnt++;
        }
    }

#if !defined REV2
    HvBt1Tmp = But1Pressed;
    HvBt2Tmp = But2Pressed;
    HvBt3Tmp = But3Pressed;
    HvBt4Tmp = But4Pressed;


    Bt1UpTmp = Bt1Up;
    Bt2UpTmp = Bt2Up;
    Bt3UpTmp = Bt3Up;
    Bt4UpTmp = Bt4Up;

    But1Pressed = 0;
    Bt1Up = 0;


    But2Pressed = HvBt1Tmp;
    But3Pressed = HvBt2Tmp;
    But4Pressed = HvBt3Tmp;

    Bt2Up = Bt1UpTmp;
    Bt3Up = Bt2UpTmp;
    Bt4Up = Bt3UpTmp;

#endif

}



