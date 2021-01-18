#include "Mn.h"

unsigned char ReadSensor1_F(void);
unsigned char ReadSensor1_B(void);
unsigned char ReadSensor1_B_V(void);
unsigned char ReadSensor1_F_V(void);
void SetPWM1_SV(void);

long int TabRes0, TabRes1, TabRes2;
unsigned int ThetaIndex,ThetaIndexPrev;
unsigned char SensorDl_1,ThetaSector,ThetaSectorPrev,ThetaIDX;
unsigned char ThetaMass[6];

const unsigned char tab_sin[] = {
    2, 6, 10, 15, 19, 23, 27, 31,
    35, 39, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 99, 103, 107, 111, 115, 118, 121, 124,
    127, 131, 135, 138, 142, 145, 149, 152, 155, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 192, 194, 197, 200,
    202, 205, 207, 210, 212, 214, 217, 219, 221, 223, 225, 227, 229, 231, 232, 234, 236, 237, 239, 240, 242, 243, 244, 245,
    247, 248, 249, 250, 250, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254,
    253, 253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 244, 242, 241, 240, 238, 237, 235, 233, 232, 230, 228, 226, 224,
    222, 222, 225, 226, 228, 230, 232, 234, 235, 237, 238, 240, 241, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 252,
    253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 252, 252, 251, 250, 249, 248,
    247, 246, 245, 244, 243, 241, 240, 238, 237, 235, 234, 232, 230, 228, 227, 225, 223, 220, 218, 216, 214, 212, 209, 207,
    204, 202, 199, 197, 194, 191, 188, 185, 183, 180, 177, 174, 171, 167, 164, 161, 158, 154, 151, 148, 144, 141, 137, 134,
    130, 127, 123, 119, 116, 112, 108, 104, 101, 97, 93, 89, 85, 81, 77, 73, 69, 65, 61, 57, 53, 49, 45, 41,
    36, 32, 28, 24, 20, 16, 12, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
unsigned char tab_sinSQ[] = {0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


const char tab_sin_M[] = {


    -96, -93, -91, -89, -87, -85, -82, -80, -77, -75, -72, -70, -67, -64, -61, -58, -56,
    -53, -50, -47, -44, -40, -37, -34, -31, -27, -24, -21, -17, -14, -10, -7, -1, 3, 7,
    10, 14, 17, 21, 24, 27, 31, 34, 37, 40, 43, 46, 49, 52, 55, 58, 61, 64, 66, 69, 72, 
    74, 77, 79, 82, 84, 86, 89, 91, 93, 95, 97, 99, 101, 103, 104, 106, 108, 109, 111,
    112, 114, 115, 116, 117, 119, 120, 121, 122, 122, 123, 124, 125, 125, 126, 126, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 126, 126, 125, 125, 124, 124, 123,
    122, 121, 120, 119, 118, 117, 116, 114, 113, 112, 110, 109, 107, 105, 104, 102, 100,
    98, 96, 94, 94, 97, 98, 100, 102, 104, 106, 107, 109, 110, 112, 113, 115, 116, 117,
    118, 119, 120, 121, 122, 123, 124, 124, 125, 126, 126, 126, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 126, 126, 126, 125, 124, 124, 123, 122, 121, 120, 119, 118,
    117, 116, 115, 113, 112, 110, 109, 107, 106, 104, 102, 100, 99, 97, 95, 92, 90, 88,
    86, 84, 81, 79, 76, 74, 71, 69, 66, 63, 60, 57, 55, 52, 49, 46, 43, 39, 36, 33,
    30, 26, 23, 20, 16, 13, 9, 6, -1, -4, -8, -11, -15, -18, -22, -25, -28, -32, -35,
    -38, -41, -44, -47, -50, -53, -56, -59, -62, -65, -67, -70, -73, -75, -78, -80, -83,
    -85, -87, -90, -92, -94, -96, -98, -100, -102, -104, -105, -107, -109, -110, -112,
    -113, -115, -116, -117, -118, -120, -121, -122, -123, -123, -124, -125, -126, -126,
    -127, -127, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127,
    -127, -126, -126, -125, -125, -124, -123, -122, -121, -120, -119, -118, -117, -115,
    -114, -113, -111, -110, -108, -106, -105, -103, -101, -99, -97, -95, -95, -98, -99, 
    -101, -103, -105, -107, -108, -110, -111, -113, -114, -116, -117, -118, -119, -120, 
    -121, -122, -123, -124, -125, -125, -126, -127, -127, -127, -128, -128, -128, -128,
    -128, -128, -128, -128, -128, -128, -127, -127, -127, -126, -125, -125, -124, -123,
    -122, -121, -120, -119, -118, -117, -116, -114, -113, -111, -110, -108, -107, -105,
    -103, -101, -100, -98
};
//Hall interrupt

void __attribute__((interrupt, auto_psv)) _CNInterrupt() {
    unsigned long int TmL;
    unsigned int k;
    IFS1bits.CNIF = 0;
    //TST_PIN2=!TST_PIN2;

    if (Sensorless2)
        return;



    if ((!Sensorless) || ((SensorlessNotBEMF)&&(!SensorlessStartNoHalls))) {


        if ((!Vector) || (BreakPressed)) {
            if (Forward1)
                Sensor1 = ReadSensor1_F();
            else
                Sensor1 = ReadSensor1_B();


        } else {
            //            IEC3bits.T8IE = 0;
            if (!DirPWM1) {
                if (Forward1)
                    Sensor1 = ReadSensor1_F_V();
                else
                    Sensor1 = ReadSensor1_B_V();
            } else {
                if (Forward1)
                    Sensor1 = ReadSensor1_B_V();
                else
                    Sensor1 = ReadSensor1_F_V();
            }


            if (IFS3bits.T8IF)
                Phase1Period1Up = TMR8;
            IEC3bits.T8IE = 1;


        }

        if ((Sensor1_Prev != Sensor1))//&&(CanSensor1))
        {
            if ((NearSensors[Sensor1][0] == Sensor1_Prev) || (NearSensors[Sensor1][1] == Sensor1_Prev)) {
                Odometr++;
                Distance++;
                Odometr10m++;
                if (Odometr10m >= ImpNa10Metr) {
                    Odometr10m = 0;
                    //RecOdometrFl=1;
                }

            }


            Sensor1_Prev = Sensor1;


            if (HallDelay1_F_UP) {
                if (HallDelay1_F < HallDelay1_FMustBe)
                    HallDelay1_F++;
                else
                    HallDelay1_F = HallDelay1_FMustBe;
            } else {
                if (HallDelay1_F > HallDelay1_FMustBe)
                    HallDelay1_F--;
                else
                    HallDelay1_F = HallDelay1_FMustBe;
            }


            if (HallDelay1_B_UP) {
                if (HallDelay1_B < HallDelay1_BMustBe)
                    HallDelay1_B++;
                else
                    HallDelay1_B = HallDelay1_BMustBe;
            } else {
                if (HallDelay1_B > HallDelay1_BMustBe)
                    HallDelay1_B--;
                else
                    HallDelay1_B = HallDelay1_BMustBe;
            }



            if ((Vector)&&(!BreakPressed)) {
#ifdef HALFTABLE
                //    if (Theta1Cnt>10)
#else
                //    if ((Theta1Cnt>3)||(T45Over))
#endif
                {

                    TmL = TMR4;
                    Phase1Period1 = TMR5HLD;
                    Phase1Period1 = (Phase1Period1 << 16) + TmL;

                    TMR5HLD = 0;
                    TMR4 = 0;
                    TMR5 = 0;


                    if (!DirPWM1) {
                        if (Forward1) {
                            if (HallDelay1_F < 0) {
                                HallDelayCnt_1 = -HallDelay1_F;
                                CanGetHalls1 = 0;
                            } else {
                                CanGetHalls1 = 1;
                                //Theta1CntPWMSND = Theta1Cnt;
                                Theta1Cnt = 0;
                                Sensor1_Prev_OP = Sensor1_Prev;
                            }
                        } else {
                            if (HallDelay1_B < 0) {
                                HallDelayCnt_1 = -HallDelay1_B;
                                CanGetHalls1 = 0;
                            } else {
                                CanGetHalls1 = 1;
                                //Theta1CntPWMSND = Theta1Cnt;
                                Theta1Cnt = 0;
                                Sensor1_Prev_OP = Sensor1_Prev;
                            }
                        }
                    } else {
                        if (!Forward1) {
                            if (HallDelay1_F < 0) {
                                HallDelayCnt_1 = -HallDelay1_F;
                                CanGetHalls1 = 0;
                            } else {
                                CanGetHalls1 = 1;
                                //Theta1CntPWMSND = Theta1Cnt;
                                Theta1Cnt = 0;
                                Sensor1_Prev_OP = Sensor1_Prev;
                            }
                        } else {
                            if (HallDelay1_B < 0) {
                                HallDelayCnt_1 = -HallDelay1_B;
                                CanGetHalls1 = 0;
                            } else {
                                CanGetHalls1 = 1;
                                //Theta1CntPWMSND = Theta1Cnt;
                                Theta1Cnt = 0;
                                Sensor1_Prev_OP = Sensor1_Prev;
                            }
                        }
                    }


                    if (PhasePERMASS) {
                        for (k = 0; k < (PhasePERMASS - 1); k++)
                            Phase1PeriodMass[k] = Phase1PeriodMass[k + 1];


                        Phase1PeriodMass[PhasePERMASS - 1] = Phase1Period1;

                        Phase1PeriodSumm = 0;
                        for (k = 0; k < PhasePERMASS; k++)
                            Phase1PeriodSumm = Phase1PeriodSumm + Phase1PeriodMass[k];
                        Phase1PeriodSumm = Phase1PeriodSumm>>PhasePERMASS_SHFT;
                    } else {
                        long int TmpL;
                        unsigned char SnPrev;
                        Phase1PeriodSumm = Phase1Period1;
                        if (!DirPWM1) {
                            SnPrev = NearSensors[Sensor1_Prev][0];
                            TmpL = Phase1Period1 * (long int) NearSensors[SnPrev][3];
                            TmpL = TmpL >> 7;
                            Phase1PeriodSumm = Phase1PeriodSumm + TmpL;
                        } else {
                            SnPrev = NearSensors[Sensor1_Prev][1];
                            TmpL = Phase1Period1 * (long int) NearSensors[SnPrev][2];
                            TmpL = TmpL >> 7;
                            Phase1PeriodSumm = Phase1PeriodSumm + TmpL;
                        }

                    }




                    if (PWM32Bits)
                        Phase1Period1 = Phase1PeriodSumm >> 3;
                    else
                        Phase1Period1 = Phase1PeriodSumm >> 4;

                    //                    Phase1Period1Show = Phase1Period1;

                    if (Phase1Period1 > 65530) {
                        PR8Temp = (unsigned int) (Phase1Period1 >> 3);
                        T8CONbits.TCKPS = 1;
                        //T45Over=1;
                    } else {
                        PR8Temp = (unsigned int) Phase1Period1;
                        T8CONbits.TCKPS = 0;
                        T45Over = 0;

                        if (PR8Temp < 1000) {
                            if (Vector&&!TrapezoidaRAM1) {
                                TrapezoidaRAM1 = 1;
                                TrapezoidaRAM1Mem = 1;
                            }
                        }
                        if (PR8Temp > 1200) {
                            if (Vector) {
                                if (TrapezoidaRAM1Mem) {
                                    TrapezoidaRAM1Mem = 0;
                                    TrapezoidaRAM1 = 0;
                                }
                            }
                        }
                    }
                }
            }

            Phases1();

            if (Forward1) {
                BackwardCnt++;
            } else {
                if (BackwardCnt)
                    BackwardCnt--;
            }

            if (!Sensorless) {
                if (!MeasuringSpd1) {
                    _1sCnt1 = 0;
                    MeasuringSpd1 = 1;
                } else {
                    //if (!Sensorless2)
                    //TST_PIN = !TST_PIN;
                    if (Forward1)
                        Spd1Cnt++;
                    else
                        Spd1Cnt--;
                }
            }
        }
    }
}

unsigned char ReadSensor1_F(void) {
    unsigned char Sens = 0;
#if !defined DIRMOTOR
    if (!Hall1_A) {
        Sens = Sens | 1;
    }

    if (!Hall1_B) {
        Sens = Sens | 2;
    }

    if (!Hall1_C) {
        Sens = Sens | 4;
    }
#endif
#if defined DIRMOTOR
    if (!DirPWM1) {
        if (!Hall1_A) {
            Sens = Sens | 1;
        }

        if (!Hall1_B) {
            Sens = Sens | 2;
        }

        if (!Hall1_C) {
            Sens = Sens | 4;
        }

    } else {
        if (Hall1_A) {
            Sens = Sens | 1;
        }

        if (Hall1_B) {
            Sens = Sens | 2;
        }

        if (Hall1_C) {
            Sens = Sens | 4;
        }

    }
#endif
    Sens = InvHalls(Sens);

    if ((Sens == 0) || (Sens == 7))
        HallErrCnt++;

    Halls = Sens;

    Sens = ChangeSensorOrder(Sens, SensOrder1);

    return Sens;
}

unsigned char ReadSensor1_B(void) {
    unsigned char Sens = 0;
#if !defined DIRMOTOR
    if (Hall1_A) {
        Sens = Sens | 1;
    }

    if (Hall1_B) {
        Sens = Sens | 2;
    }

    if (Hall1_C) {
        Sens = Sens | 4;
    }
#endif
#if defined DIRMOTOR
    if (!DirPWM1) {
        if (Hall1_A) {
            Sens = Sens | 1;
        }

        if (Hall1_B) {
            Sens = Sens | 2;
        }

        if (Hall1_C) {
            Sens = Sens | 4;
        }
    } else {
        if (!Hall1_A) {
            Sens = Sens | 1;
        }

        if (!Hall1_B) {
            Sens = Sens | 2;
        }

        if (!Hall1_C) {
            Sens = Sens | 4;
        }

    }
#endif
    Sens = InvHalls(Sens);

    if ((Sens == 0) || (Sens == 7))
        HallErrCnt++;

    Halls = Sens;
    Sens = ChangeSensorOrder(Sens, SensOrder1);

    return Sens;
}

unsigned char ReadSensor1_B_V(void) {
    unsigned char Sens = 0;
    if (Hall1_A) {
        Sens = Sens | 1;
    }

    if (Hall1_B) {
        Sens = Sens | 2;
    }

    if (Hall1_C) {
        Sens = Sens | 4;
    }

    Sens = InvHalls(Sens);


    if ((Sens == 0) || (Sens == 7))
        HallErrCnt++;

    Halls = Sens;


#if defined SEL_SENSOR_ORDER
    Sens = ChangeSensorOrder(Sens, SensOrder1);
#endif

    return Sens;
}

unsigned char ReadSensor1_F_V(void) {
    unsigned char Sens = 0;
    if (!Hall1_A) {
        Sens = Sens | 1;
    }

    if (!Hall1_B) {
        Sens = Sens | 2;
    }

    if (!Hall1_C) {
        Sens = Sens | 4;
    }

    Sens = InvHalls(Sens);

    if ((Sens == 0) || (Sens == 7))
        HallErrCnt++;

    Halls = Sens;


#if defined SEL_SENSOR_ORDER
    Sens = ChangeSensorOrder(Sens, SensOrder1);
#endif

    return Sens;
}

unsigned char InvHalls(unsigned char Sensors) {
    if (InvHallA)
        Sensors = Sensors^1;
    if (InvHallB)
        Sensors = Sensors^2;
    if (InvHallC)
        Sensors = Sensors^4;

    return Sensors;
}

unsigned char ChangeSensorOrder(unsigned char Sns, unsigned char SendOrder) {
    unsigned char SensTmp = Sns;
    switch (SendOrder) {
        case 0:
            return Sns;
            break;
        case 1:
            SensTmp = SensTmp & 0x4;

            if (Sns & 1) //A -> B
                SensTmp = SensTmp | 2;

            if (Sns & 2) //B -> A
                SensTmp = SensTmp | 1;

            return SensTmp;
            break;
        case 2:
            SensTmp = 0;

            if (Sns & 1) //A -> C
                SensTmp = SensTmp | 4;

            if (Sns & 2) //B -> A
                SensTmp = SensTmp | 1;

            if (Sns & 4) //C -> B
                SensTmp = SensTmp | 2;

            return SensTmp;
            break;
        case 3:
            SensTmp = 0;

            if (Sns & 1) //A -> A
                SensTmp = SensTmp | 1;

            if (Sns & 2) //B -> C
                SensTmp = SensTmp | 4;

            if (Sns & 4) //C -> B
                SensTmp = SensTmp | 2;

            return SensTmp;
            break;
        case 4:
            SensTmp = 0;

            if (Sns & 1) //A -> B
                SensTmp = SensTmp | 2;

            if (Sns & 2) //B -> C
                SensTmp = SensTmp | 4;

            if (Sns & 4) //C -> A
                SensTmp = SensTmp | 1;

            return SensTmp;
            break;
        case 5:
            SensTmp = 0;

            if (Sns & 1) //A -> C
                SensTmp = SensTmp | 4;

            if (Sns & 2) //B -> B
                SensTmp = SensTmp | 2;

            if (Sns & 4) //C -> A
                SensTmp = SensTmp | 1;

            return SensTmp;
            break;
        default:
            return 0;
            break;

    }
}

//Phase switching
void Phases1(void) {
    unsigned char LowDrv, HiDrv;

    
    
    if (Sensorless2)
        return;
    
    if ((Vector)&&(!BreakPressed))
        return;
    if (ChagerViaMotor)
        return;


    PWM1_A_H = 0;
    PWM1_A_L = 0;
    PWM1_B_H = 0;
    PWM1_B_L = 0;
    PWM1_C_H = 0;
    PWM1_C_L = 0;


    if ((Sensor1 < 7)&&(Sensor1 > 0)) {
        LowDrv = LowDrive[Sensor1];
        HiDrv = HiDrive[Sensor1];
    } else {
        LowDrv = 0;
        HiDrv = 0;

        PEN1_A_H = 0;
        PEN1_A_L = 0;
        PEN1_B_H = 0;
        PEN1_B_L = 0;
        PEN1_C_H = 0;
        PEN1_C_L = 0;


    }

    if (HiDrv & 1) {//A
        if (BreakPressed) {
            PEN1_A_H = 0;
            if (_1stBreak)
                PEN1_A_L = 0; //1;
            else
                PEN1_A_L = 1;

        } else {
            PEN1_A_H = 1;
            if (StrongMode)
                PEN1_A_L = 1;
            else
                PEN1_A_L = 0;
        }
        PEN1_B_H = 0;
        PEN1_B_L = 0;
        PEN1_C_H = 0;
        PEN1_C_L = 0;
    }
    if (HiDrv & 2) {//B
        PEN1_A_H = 0;
        PEN1_A_L = 0;
        if (BreakPressed) {
            PEN1_B_H = 0;
            if (_1stBreak)
                PEN1_B_L = 0; //1;
            else
                PEN1_B_L = 1;


        } else {
            PEN1_B_H = 1;
            if (StrongMode)
                PEN1_B_L = 1;
            else
                PEN1_B_L = 0;

        }
        PEN1_C_H = 0;
        PEN1_C_L = 0;
    }
    if (HiDrv & 4) {//C
        PEN1_A_H = 0;
        PEN1_A_L = 0;
        PEN1_B_H = 0;
        PEN1_B_L = 0;
        if (BreakPressed) {
            PEN1_C_H = 0;
            if (_1stBreak)
                PEN1_C_L = 0; //1;
            else
                PEN1_C_L = 1;

        } else {
            PEN1_C_H = 1;
            if (StrongMode)
                PEN1_C_L = 1;
            else
                PEN1_C_L = 0;
        }
    }
    if (!BreakPressed) {
        if (LowDrv & 1)
            PWM1_A_L = 1; //PEN1_A_L=1;//
        if (LowDrv & 2)
            PWM1_B_L = 1; //PEN1_B_L=1;//
        if (LowDrv & 4)
            PWM1_C_L = 1; //PEN1_C_L=1;//
    } else {
        if (_1stBreak) {
            if (LowDrv & 1)
                PEN1_A_L = 1; //PWM1_A_L=1;//
            if (LowDrv & 2)
                PEN1_B_L = 1; //PWM1_B_L=1;//
            if (LowDrv & 4)
                PEN1_C_L = 1; //PWM1_C_L=1;//
        } else {
            if (LowDrv & 1)
                PWM1_A_L = 1; //PEN1_A_L=1;//
            if (LowDrv & 2)
                PWM1_B_L = 1; //PEN1_B_L=1;//
            if (LowDrv & 4)
                PWM1_C_L = 1; //PEN1_C_L=1;//
        }
    }


}

void InitBLDCPorts(void) {

    PWM1_A_H = 0;
    PWM1_A_L = 0;
    PWM1_B_H = 0;
    PWM1_B_L = 0;
    PWM1_C_H = 0;
    PWM1_C_L = 0;


    //A:
#if !defined VECTOR
    TRIS_DS = 0;
#endif


    TRIS_PWM1_A_H = 0;
    ANSEL_PWM1_A_H = 0;

    TRIS_PWM1_A_L = 0;
    ANSEL_PWM1_A_L = 0;

    //B:

    TRIS_PWM1_B_H = 0;
    ANSEL_PWM1_B_H = 0;

    TRIS_PWM1_B_L = 0;
    ANSEL_PWM1_B_L = 0;

    //C:

    TRIS_PWM1_C_H = 0;
    ANSEL_PWM1_C_H = 0;

    TRIS_PWM1_C_L = 0;
    ANSEL_PWM1_C_L = 0;


    //HALL:

    CNEN_Hall1_A = 1;


    CNEN_Hall1_B = 1;


    CNEN_Hall1_C = 1;



    //BLDC 1 END



    PWM1_A_H = 0;
    PWM1_A_L = 0;
    PWM1_B_H = 0;
    PWM1_B_L = 0;
    PWM1_C_H = 0;
    PWM1_C_L = 0;




    TRIS_Hall1_A = 1;
    TRIS_Hall1_B = 1;
    TRIS_Hall1_C = 1;


    IPC4bits.CNIP = 5;
    IEC1bits.CNIE = 1;


    DS = 0;
}




void SVPWM1_SetPWM(void) {
    //    if (!Monocycle)
    //      return;
    if (ChagerViaMotor) {
        SetPWM_ChagerViaMotor();
        return;
    }

    if (DS) {

        PWM1_A_H = 0;
        PWM1_A_L = 0;
        PWM1_B_H = 0;
        PWM1_B_L = 0;
        PWM1_C_H = 0;
        PWM1_C_L = 0;


        PEN1_A_H = 0;
        PEN1_A_L = 0;
        PEN1_B_H = 0;
        PEN1_B_L = 0;
        PEN1_C_H = 0;
        PEN1_C_L = 0;
        PhasePWM = PWM1Show = 0;
        return;
    }




    if (BreakPressed)
        return;




    if (CURRENT_PROTECTION) {
        if (Amplitude1 > PI_Curr1Res)
            Amplitude1Tmp = Amplitude1 - PI_Curr1Res;
        else
            Amplitude1Tmp = 0;
    } else
        Amplitude1Tmp = Amplitude1;
    PhasePWM = Amplitude1Tmp;

    PWM1Show = Amplitude1Tmp;


    if (TrapezoidaRAM1) {
        switch (Sensor1_Prev_OP) {
            case 1:
                PWM1_A_H = 0;
                PWM1_A_L = 1;
                PWM1_B_H = 0;
                PWM1_B_L = 0;
                PWM1_C_H = 0;
                PWM1_C_L = 0;

                PEN1_A_H = 0;
                PEN1_A_L = 0;
                PEN1_B_H = 1;
                if (StrongMode)
                    PEN1_B_L = 1;
                else
                    PEN1_B_L = 0;
                PEN1_C_H = 0; //1;
                PEN1_C_L = 0;



                SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 1]) >> 8);
                SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 257]) >> 8);
                SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 129]) >> 8);
                break;
            case 3:
                PWM1_A_H = 0;
                PWM1_A_L = 1;
                PWM1_B_H = 0;
                PWM1_B_L = 0;
                PWM1_C_H = 0;
                PWM1_C_L = 0;


                PEN1_A_H = 0;
                PEN1_A_L = 0;
                PEN1_B_H = 0; //1;
                PEN1_B_L = 0;
                PEN1_C_H = 1;
                if (StrongMode)
                    PEN1_C_L = 1;
                else
                    PEN1_C_L = 0;


                SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 65]) >> 8);
                SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 321]) >> 8);
                SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 193]) >> 8);
                break;
            case 2:
                PWM1_A_H = 0;
                PWM1_A_L = 0;
                PWM1_B_H = 0;
                PWM1_B_L = 1;
                PWM1_C_H = 0;
                PWM1_C_L = 0;


                PEN1_A_H = 0; //1;
                PEN1_A_L = 0;
                PEN1_B_H = 0;
                PEN1_B_L = 0;
                PEN1_C_H = 1;
                if (StrongMode)
                    PEN1_C_L = 1;
                else
                    PEN1_C_L = 0;


                SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 129]) >> 8);
                SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 1]) >> 8);
                SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 257]) >> 8);
                break;
            case 6:
                PWM1_A_H = 0;
                PWM1_A_L = 0;
                PWM1_B_H = 0;
                PWM1_B_L = 1;
                PWM1_C_H = 0;
                PWM1_C_L = 0;


                PEN1_A_H = 1;
                if (StrongMode)
                    PEN1_A_L = 1;
                else
                    PEN1_A_L = 0;
                PEN1_B_H = 0;
                PEN1_B_L = 0;
                PEN1_C_H = 0; //1;
                PEN1_C_L = 0;


                SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 193]) >> 8);
                SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 65]) >> 8);
                SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 321]) >> 8);
                break;
            case 4:
                PWM1_A_H = 0;
                PWM1_A_L = 0;
                PWM1_B_H = 0;
                PWM1_B_L = 0;
                PWM1_C_H = 0;
                PWM1_C_L = 1;


                if (StrongMode)
                    PEN1_A_L = 1;
                else
                    PEN1_A_L = 0;
                PEN1_A_H = 1;
                PEN1_B_H = 0; //1;
                PEN1_B_L = 0;
                PEN1_C_H = 0;
                PEN1_C_L = 0;

                SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 257]) >> 8);
                SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 129]) >> 8);
                SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 1]) >> 8);
                break;
            case 5:
                PWM1_A_H = 0;
                PWM1_A_L = 0;
                PWM1_B_H = 0;
                PWM1_B_L = 0;
                PWM1_C_H = 0;
                PWM1_C_L = 1;


                PEN1_A_H = 0; //1;
                PEN1_A_L = 0;
                PEN1_B_H = 1;
                if (StrongMode)
                    PEN1_B_L = 1;
                else
                    PEN1_B_L = 0;
                PEN1_C_H = 0;
                PEN1_C_L = 0;

                SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 321]) >> 8);
                SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 193]) >> 8);
                SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 65]) >> 8);
                break;

        }
    } else {

        switch (Sensor1_Prev_OP) {
            case 1:
                if (!SIN_MIDDLE) {
                    TabRes0 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 1];
                    TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 257];
                    TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 129];
                } else {
                    TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 1]);
                    TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 257]);
                    TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 129]);
                }

                if (!StrongMode) {
                    if (TabRes0 == 0) {
                        PWM1_A_H = 0;
                        PWM1_A_L = 1;
                        PEN1_A_H = 0;
                        PEN1_A_L = 0;
                    } else {
                        PWM1_A_H = 0;
                        PWM1_A_L = 0;
                        PEN1_A_H = 1;
                        PEN1_A_L = 0;
                    }

                    if (TabRes1 == 0) {
                        PWM1_B_H = 0;
                        PWM1_B_L = 1;
                        PEN1_B_H = 0;
                        PEN1_B_L = 0;
                    } else {
                        PWM1_B_H = 0;
                        PWM1_B_L = 0;
                        PEN1_B_H = 1;
                        PEN1_B_L = 0;
                    }


                    if (TabRes2 == 0) {
                        PWM1_C_H = 0;
                        PWM1_C_L = 1;
                        PEN1_C_H = 0;
                        PEN1_C_L = 0;
                    } else {
                        PWM1_C_H = 0;
                        PWM1_C_L = 0;
                        PEN1_C_H = 1;
                        PEN1_C_L = 0;
                    }


                }

                if (!SIN_MIDDLE) {
                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                } else {
                    SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                }


                break;
            case 3:
                if (!SIN_MIDDLE) {
                    TabRes0 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 65];
                    TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 321];
                    TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 193];
                } else {
                    TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 65]);
                    TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 321]);
                    TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 193]);
                }

                if (!StrongMode) {

                    if (TabRes0 == 0) {
                        PWM1_A_H = 0;
                        PWM1_A_L = 1;
                        PEN1_A_H = 0;
                        PEN1_A_L = 0;
                    } else {
                        PWM1_A_H = 0;
                        PWM1_A_L = 0;
                        PEN1_A_H = 1;
                        PEN1_A_L = 0;
                    }

                    if (TabRes1 == 0) {
                        PWM1_B_H = 0;
                        PWM1_B_L = 1;
                        PEN1_B_H = 0;
                        PEN1_B_L = 0;
                    } else {
                        PWM1_B_H = 0;
                        PWM1_B_L = 0;
                        PEN1_B_H = 1;
                        PEN1_B_L = 0;
                    }


                    if (TabRes2 == 0) {
                        PWM1_C_H = 0;
                        PWM1_C_L = 1;
                        PEN1_C_H = 0;
                        PEN1_C_L = 0;
                    } else {
                        PWM1_C_H = 0;
                        PWM1_C_L = 0;
                        PEN1_C_H = 1;
                        PEN1_C_L = 0;
                    }

                }

                if (!SIN_MIDDLE) {
                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                } else {
                    SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                }

                break;
            case 2:
                if (!SIN_MIDDLE) {
                    TabRes0 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 129];
                    TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 1];
                    TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 257];
                } else {
                    TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 129]);
                    TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 1]);
                    TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 257]);
                }


                if (!StrongMode) {

                    if (TabRes0 == 0) {
                        PWM1_A_H = 0;
                        PWM1_A_L = 1;
                        PEN1_A_H = 0;
                        PEN1_A_L = 0;
                    } else {
                        PWM1_A_H = 0;
                        PWM1_A_L = 0;
                        PEN1_A_H = 1;
                        PEN1_A_L = 0;
                    }

                    if (TabRes1 == 0) {
                        PWM1_B_H = 0;
                        PWM1_B_L = 1;
                        PEN1_B_H = 0;
                        PEN1_B_L = 0;
                    } else {
                        PWM1_B_H = 0;
                        PWM1_B_L = 0;
                        PEN1_B_H = 1;
                        PEN1_B_L = 0;
                    }


                    if (TabRes2 == 0) {
                        PWM1_C_H = 0;
                        PWM1_C_L = 1;
                        PEN1_C_H = 0;
                        PEN1_C_L = 0;
                    } else {
                        PWM1_C_H = 0;
                        PWM1_C_L = 0;
                        PEN1_C_H = 1;
                        PEN1_C_L = 0;
                    }

                }
                if (!SIN_MIDDLE) {
                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                } else {
                    SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                }

                break;
            case 6:
                if (!SIN_MIDDLE) {
                    TabRes0 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 193];
                    TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 65];
                    TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 321];
                } else {
                    TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 193]);
                    TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 65]);
                    TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 321]);
                }



                if (!StrongMode) {


                    if (TabRes0 == 0) {
                        PWM1_A_H = 0;
                        PWM1_A_L = 1;
                        PEN1_A_H = 0;
                        PEN1_A_L = 0;
                    } else {
                        PWM1_A_H = 0;
                        PWM1_A_L = 0;
                        PEN1_A_H = 1;
                        PEN1_A_L = 0;
                    }

                    if (TabRes1 == 0) {
                        PWM1_B_H = 0;
                        PWM1_B_L = 1;
                        PEN1_B_H = 0;
                        PEN1_B_L = 0;
                    } else {
                        PWM1_B_H = 0;
                        PWM1_B_L = 0;
                        PEN1_B_H = 1;
                        PEN1_B_L = 0;
                    }


                    if (TabRes2 == 0) {
                        PWM1_C_H = 0;
                        PWM1_C_L = 1;
                        PEN1_C_H = 0;
                        PEN1_C_L = 0;
                    } else {
                        PWM1_C_H = 0;
                        PWM1_C_L = 0;
                        PEN1_C_H = 1;
                        PEN1_C_L = 0;
                    }



                }


                if (!SIN_MIDDLE) {
                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                } else {
                    SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                }

                break;
            case 4:
                if (!SIN_MIDDLE) {
                    TabRes0 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 257];
                    TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 129];
                    TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 1];
                } else {
                    TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 257]);
                    TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 129]);
                    TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 1]);
                }

                if (!StrongMode) {

                    if (TabRes0 == 0) {
                        PWM1_A_H = 0;
                        PWM1_A_L = 1;
                        PEN1_A_H = 0;
                        PEN1_A_L = 0;
                    } else {
                        PWM1_A_H = 0;
                        PWM1_A_L = 0;
                        PEN1_A_H = 1;
                        PEN1_A_L = 0;
                    }

                    if (TabRes1 == 0) {
                        PWM1_B_H = 0;
                        PWM1_B_L = 1;
                        PEN1_B_H = 0;
                        PEN1_B_L = 0;
                    } else {
                        PWM1_B_H = 0;
                        PWM1_B_L = 0;
                        PEN1_B_H = 1;
                        PEN1_B_L = 0;
                    }


                    if (TabRes2 == 0) {
                        PWM1_C_H = 0;
                        PWM1_C_L = 1;
                        PEN1_C_H = 0;
                        PEN1_C_L = 0;
                    } else {
                        PWM1_C_H = 0;
                        PWM1_C_L = 0;
                        PEN1_C_H = 1;
                        PEN1_C_L = 0;
                    }

                }


                if (!SIN_MIDDLE) {
                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                } else {
                    SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                }

                break;
            case 5:
                if (!SIN_MIDDLE) {
                    TabRes0 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 321];
                    TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 193];
                    TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 65];
                } else {
                    TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 321]);
                    TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 193]);
                    TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 65]);
                }


                if (!StrongMode) {

                    if (TabRes0 == 0) {
                        PWM1_A_H = 0;
                        PWM1_A_L = 1;
                        PEN1_A_H = 0;
                        PEN1_A_L = 0;
                    } else {
                        PWM1_A_H = 0;
                        PWM1_A_L = 0;
                        PEN1_A_H = 1;
                        PEN1_A_L = 0;
                    }

                    if (TabRes1 == 0) {
                        PWM1_B_H = 0;
                        PWM1_B_L = 1;
                        PEN1_B_H = 0;
                        PEN1_B_L = 0;
                    } else {
                        PWM1_B_H = 0;
                        PWM1_B_L = 0;
                        PEN1_B_H = 1;
                        PEN1_B_L = 0;
                    }


                    if (TabRes2 == 0) {
                        PWM1_C_H = 0;
                        PWM1_C_L = 1;
                        PEN1_C_H = 0;
                        PEN1_C_L = 0;
                    } else {
                        PWM1_C_H = 0;
                        PWM1_C_L = 0;
                        PEN1_C_H = 1;
                        PEN1_C_L = 0;
                    }

                }


                if (!SIN_MIDDLE) {
                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                } else {
                    SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                    SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                }

                break;


        }


    }



    SetPWM1_SV();


    



}

void SetPWM1_SV(void) {

    if (ChagerViaMotor) {
        SetPWM_ChagerViaMotor();
        return;
    }







    int PWM = SV_PWM1_0;


    if (PWM < DEADTIME_GLUK) {
        DTR1 = DEADTIME * 2; //DTRx Registers are ignored in this mode
        ALTDTR1 = DEADTIME * 2;
        PWM = PWM + DEADTIME + Khard;
    } else {
        DTR1 = DEADTIME; //DTRx Registers are ignored in this mode
        ALTDTR1 = DEADTIME;
        PWM = PWM + DEADTIME_2 + Khard;

    }


    PDC1 = PWM; //SV_PWM1_0+DEADTIME_2+Khard;



    PWM = SV_PWM1_1;


    if (PWM < DEADTIME_GLUK) {
        DTR2 = DEADTIME * 2; //DTRx Registers are ignored in this mode
        ALTDTR2 = DEADTIME * 2;
        PWM = PWM + DEADTIME + Khard;
    } else {
        DTR2 = DEADTIME; //DTRx Registers are ignored in this mode
        ALTDTR2 = DEADTIME;
        PWM = PWM + DEADTIME_2 + Khard;

    }


    PDC2 = PWM; //SV_PWM1_1+DEADTIME_2+Khard;





    PWM = SV_PWM1_2;


    if (PWM < DEADTIME_GLUK) {
        DTR3 = DEADTIME * 2; //DTRx Registers are ignored in this mode
        ALTDTR3 = DEADTIME * 2;
        PWM = PWM + DEADTIME + Khard;
    } else {
        DTR3 = DEADTIME; //DTRx Registers are ignored in this mode
        ALTDTR3 = DEADTIME;
        PWM = PWM + DEADTIME_2 + Khard;

    }


    PDC3 = PWM; //SV_PWM1_2+DEADTIME_2+Khard;








}





void SVPWM1(void) {
    unsigned char DirPWM1TMP;


    if (ChagerViaMotor) {
        SetPWM_ChagerViaMotor();
        return;
    }

    if (DS) {

        PWM1_A_H = 0;
        PWM1_A_L = 0;
        PWM1_B_H = 0;
        PWM1_B_L = 0;
        PWM1_C_H = 0;
        PWM1_C_L = 0;


        PEN1_A_H = 0;
        PEN1_A_L = 0;
        PEN1_B_H = 0;
        PEN1_B_L = 0;
        PEN1_C_H = 0;
        PEN1_C_L = 0;
        PhasePWM = PWM1Show = 0;
        return;
    }


    if (BreakPressed)
        return;
    DirPWM1TMP = !DirPWM1;
    if (InvSin)
        DirPWM1TMP = !DirPWM1TMP;


    if (!TrapezoidaRAM1) {
        if (StrongMode) {
            PEN1_A_H = 1;
            PEN1_A_L = 1;
            PEN1_B_H = 1;
            PEN1_B_L = 1;
            PEN1_C_H = 1;
            PEN1_C_L = 1;
        }

    }

    if (T45Over)
        Theta1Cnt = Theta1Zero;

    //Sensor1_Prev_OP=1;





    if (DirPWM1TMP) {
        if (Forward1) {
            HallDelay1_Direction = 0;
            if (HallDelay1_F > 0) {
                if (Theta1Cnt > (63 - HallDelay1_F)) {
                    if (!SensorDl_1) {
                        SensorDl_1 = NearSensors[Sensor1_Prev_OP][0];
                        Sensor1_Prev_OP = SensorDl_1;
                    }
                } else {
                    SensorDl_1 = 0;
                    // Sensor1_Prev_OP=ReadSensor1_F_V();//++++++++++++++++++++++++++++

                }
            } else {
                SensorDl_1 = 0;
                //   if (CanGetHalls1)
                //Sensor1_Prev_OP=ReadSensor1_F_V();//+++++++++++++++++++++++++++++++++
            }

        } else {
            HallDelay1_Direction = 1;
            if (HallDelay1_B > 0) {
                if (Theta1Cnt > (63 - HallDelay1_B)) {
                    if (!SensorDl_1) {
                        SensorDl_1 = NearSensors[Sensor1_Prev_OP][1];
                        Sensor1_Prev_OP = SensorDl_1;
                    }
                } else {
                    //   Sensor1_Prev_OP=ReadSensor1_B_V();//-----------------------
                    SensorDl_1 = 0;
                }
            } else {
                SensorDl_1 = 0;
                //     if (CanGetHalls1)
                //Sensor1_Prev_OP=ReadSensor1_B_V();//---------------------------------
            }
        }
    } else {
        if (!Forward1) {
            HallDelay1_Direction = 0;
            if (HallDelay1_F > 0) {
                if (Theta1Cnt > (63 - HallDelay1_F)) {
                    if (!SensorDl_1) {
                        SensorDl_1 = NearSensors[Sensor1_Prev_OP][0];
                        Sensor1_Prev_OP = SensorDl_1;
                    }
                } else {
                    SensorDl_1 = 0;
                    //     Sensor1_Prev_OP=ReadSensor1_F_V();//--------------------------------------

                }
            } else {
                SensorDl_1 = 0;
                //       if (CanGetHalls1)
                //      Sensor1_Prev_OP=ReadSensor1_F_V();//----------------------------

            }

        } else {
            HallDelay1_Direction = 1;
            if (HallDelay1_B > 0) {
                if (Theta1Cnt > (63 - HallDelay1_B)) {
                    if (!SensorDl_1) {
                        SensorDl_1 = NearSensors[Sensor1_Prev_OP][1];
                        Sensor1_Prev_OP = SensorDl_1;
                    }
                } else {
                    //         Sensor1_Prev_OP=ReadSensor1_B_V();//+++++++++++++++++++++
                    SensorDl_1 = 0;
                }
            } else {
                SensorDl_1 = 0;
                //    if (CanGetHalls1)
                //                Sensor1_Prev_OP=ReadSensor1_B_V();//+++++++++++++++++++


            }
        }
    }

#ifdef HALFTABLE
    if (Theta1Cnt < 32)//64)//THETA_NUM)
    {
        if (Forward1)
            Theta1CntPWM = 63 - (Theta1Cnt << 1);
        else
            Theta1CntPWM = Theta1Cnt << 1;
#else
    if (Theta1Cnt < 64)//THETA_NUM)
    {
        if (DirPWM1TMP) {
            if (Forward1)
                if (SensorDl_1) {
                    Theta1CntPWM = 127 - HallDelay1_F - Theta1Cnt;
                    //  Theta1CntPWM=HallDelay1_F-Theta1Cnt;
                } else {
                    Theta1CntPWM = 63 - Theta1Cnt - HallDelay1_F;
                } else
                if (SensorDl_1) {
                Theta1CntPWM = HallDelay1_B - (64 - Theta1Cnt);
            } else {
                Theta1CntPWM = Theta1Cnt + HallDelay1_B;
            }
        } else {
            if (!Forward1)
                if (SensorDl_1) {
                    Theta1CntPWM = 127 - HallDelay1_F - Theta1Cnt;
                    //  Theta1CntPWM=HallDelay1_F-Theta1Cnt;
                } else {
                    Theta1CntPWM = 63 - Theta1Cnt - HallDelay1_F;
                } else
                if (SensorDl_1) {
                Theta1CntPWM = HallDelay1_B - (64 - Theta1Cnt);
            } else {
                Theta1CntPWM = Theta1Cnt + HallDelay1_B;
            }
        }
#endif
        if (CURRENT_PROTECTION) {
            if (Amplitude1 > PI_Curr1Res)
                Amplitude1Tmp = Amplitude1 - PI_Curr1Res;
            else
                Amplitude1Tmp = 0;
        } else
            Amplitude1Tmp = Amplitude1;
        PhasePWM = Amplitude1Tmp;



        PWM1Show = Amplitude1Tmp;

        
                
        //Theta1CntPWM=63-Theta1CntPWM;

        if (TrapezoidaRAM1) {
            switch (Sensor1_Prev_OP) {
                case 1:
                    PWM1_A_H = 0;
                    PWM1_A_L = 1;
                    PWM1_B_H = 0;
                    PWM1_B_L = 0;
                    PWM1_C_H = 0;
                    PWM1_C_L = 0;

                    PEN1_A_H = 0;
                    PEN1_A_L = 0;
                    PEN1_B_H = 1;
                    if (StrongMode)
                        PEN1_B_L = 1;
                    else
                        PEN1_B_L = 0;
                    PEN1_C_H = 0; //1;
                    PEN1_C_L = 0;



                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 1]) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 257]) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 129]) >> 8);
                    break;
                case 3:
                    PWM1_A_H = 0;
                    PWM1_A_L = 1;
                    PWM1_B_H = 0;
                    PWM1_B_L = 0;
                    PWM1_C_H = 0;
                    PWM1_C_L = 0;


                    PEN1_A_H = 0;
                    PEN1_A_L = 0;
                    PEN1_B_H = 0; //1;
                    PEN1_B_L = 0;
                    PEN1_C_H = 1;
                    if (StrongMode)
                        PEN1_C_L = 1;
                    else
                        PEN1_C_L = 0;


                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 65]) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 321]) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 193]) >> 8);
                    break;
                case 2:
                    PWM1_A_H = 0;
                    PWM1_A_L = 0;
                    PWM1_B_H = 0;
                    PWM1_B_L = 1;
                    PWM1_C_H = 0;
                    PWM1_C_L = 0;


                    PEN1_A_H = 0; //1;
                    PEN1_A_L = 0;
                    PEN1_B_H = 0;
                    PEN1_B_L = 0;
                    PEN1_C_H = 1;
                    if (StrongMode)
                        PEN1_C_L = 1;
                    else
                        PEN1_C_L = 0;


                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 129]) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 1]) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 257]) >> 8);
                    break;
                case 6:
                    PWM1_A_H = 0;
                    PWM1_A_L = 0;
                    PWM1_B_H = 0;
                    PWM1_B_L = 1;
                    PWM1_C_H = 0;
                    PWM1_C_L = 0;


                    PEN1_A_H = 1;
                    if (StrongMode)
                        PEN1_A_L = 1;
                    else
                        PEN1_A_L = 0;
                    PEN1_B_H = 0;
                    PEN1_B_L = 0;
                    PEN1_C_H = 0; //1;
                    PEN1_C_L = 0;


                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 193]) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 65]) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 321]) >> 8);
                    break;
                case 4:
                    PWM1_A_H = 0;
                    PWM1_A_L = 0;
                    PWM1_B_H = 0;
                    PWM1_B_L = 0;
                    PWM1_C_H = 0;
                    PWM1_C_L = 1;


                    if (StrongMode)
                        PEN1_A_L = 1;
                    else
                        PEN1_A_L = 0;
                    PEN1_A_H = 1;
                    PEN1_B_H = 0; //1;
                    PEN1_B_L = 0;
                    PEN1_C_H = 0;
                    PEN1_C_L = 0;

                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 257]) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 129]) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 1]) >> 8);
                    break;
                case 5:
                    PWM1_A_H = 0;
                    PWM1_A_L = 0;
                    PWM1_B_H = 0;
                    PWM1_B_L = 0;
                    PWM1_C_H = 0;
                    PWM1_C_L = 1;


                    PEN1_A_H = 0; //1;
                    PEN1_A_L = 0;
                    PEN1_B_H = 1;
                    if (StrongMode)
                        PEN1_B_L = 1;
                    else
                        PEN1_B_L = 0;
                    PEN1_C_H = 0;
                    PEN1_C_L = 0;

                    SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 321]) >> 8);
                    SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 193]) >> 8);
                    SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * (unsigned long int) tab_sinSQ[THETA_NUM - Theta1CntPWM - 65]) >> 8);
                    break;

            }
        } else {
            switch (Sensor1_Prev_OP) {

                case 1:

                    if (!SIN_MIDDLE) {
                        ThetaIndex = THETA_NUM - Theta1CntPWM - 1;
                        TabRes0 = (unsigned long int) tab_sin[ThetaIndex];
                        TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 257];
                        TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 129];
                    } else {
                        TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 1]);
                        TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 257]);
                        TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 129]);
                    }

                    if (!StrongMode) {
                        if (TabRes0 == 0) {
                            PWM1_A_H = 0;
                            PWM1_A_L = 1;
                            PEN1_A_H = 0;
                            PEN1_A_L = 0;
                        } else {
                            PWM1_A_H = 0;
                            PWM1_A_L = 0;
                            PEN1_A_H = 1;
                            PEN1_A_L = 0;
                        }

                        if (TabRes1 == 0) {
                            PWM1_B_H = 0;
                            PWM1_B_L = 1;
                            PEN1_B_H = 0;
                            PEN1_B_L = 0;
                        } else {
                            PWM1_B_H = 0;
                            PWM1_B_L = 0;
                            PEN1_B_H = 1;
                            PEN1_B_L = 0;
                        }


                        if (TabRes2 == 0) {
                            PWM1_C_H = 0;
                            PWM1_C_L = 1;
                            PEN1_C_H = 0;
                            PEN1_C_L = 0;
                        } else {
                            PWM1_C_H = 0;
                            PWM1_C_L = 0;
                            PEN1_C_H = 1;
                            PEN1_C_L = 0;
                        }


                    }


                    if (!SIN_MIDDLE) {
                        SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                        SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                        SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                    } else {
                        SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                    }


                    break;
                case 3:
                    if (!SIN_MIDDLE) {
                        ThetaIndex = THETA_NUM - Theta1CntPWM - 65;
                        TabRes0 = (unsigned long int) tab_sin[ThetaIndex];
                        TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 321];
                        TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 193];
                    } else {
                        TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 65]);
                        TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 321]);
                        TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 193]);
                    }

                    if (!StrongMode) {

                        if (TabRes0 == 0) {
                            PWM1_A_H = 0;
                            PWM1_A_L = 1;
                            PEN1_A_H = 0;
                            PEN1_A_L = 0;
                        } else {
                            PWM1_A_H = 0;
                            PWM1_A_L = 0;
                            PEN1_A_H = 1;
                            PEN1_A_L = 0;
                        }

                        if (TabRes1 == 0) {
                            PWM1_B_H = 0;
                            PWM1_B_L = 1;
                            PEN1_B_H = 0;
                            PEN1_B_L = 0;
                        } else {
                            PWM1_B_H = 0;
                            PWM1_B_L = 0;
                            PEN1_B_H = 1;
                            PEN1_B_L = 0;
                        }


                        if (TabRes2 == 0) {
                            PWM1_C_H = 0;
                            PWM1_C_L = 1;
                            PEN1_C_H = 0;
                            PEN1_C_L = 0;
                        } else {
                            PWM1_C_H = 0;
                            PWM1_C_L = 0;
                            PEN1_C_H = 1;
                            PEN1_C_L = 0;
                        }

                    }

                    if (!SIN_MIDDLE) {
                        SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                        SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                        SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                    } else {
                        SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                    }

                    break;
                case 2:
                    if (!SIN_MIDDLE) {
                        ThetaIndex = THETA_NUM - Theta1CntPWM - 129;
                        TabRes0 = (unsigned long int) tab_sin[ThetaIndex];
                        TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 1];
                        TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 257];
                    } else {
                        TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 129]);
                        TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 1]);
                        TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 257]);
                    }


                    if (!StrongMode) {

                        if (TabRes0 == 0) {
                            PWM1_A_H = 0;
                            PWM1_A_L = 1;
                            PEN1_A_H = 0;
                            PEN1_A_L = 0;
                        } else {
                            PWM1_A_H = 0;
                            PWM1_A_L = 0;
                            PEN1_A_H = 1;
                            PEN1_A_L = 0;
                        }

                        if (TabRes1 == 0) {
                            PWM1_B_H = 0;
                            PWM1_B_L = 1;
                            PEN1_B_H = 0;
                            PEN1_B_L = 0;
                        } else {
                            PWM1_B_H = 0;
                            PWM1_B_L = 0;
                            PEN1_B_H = 1;
                            PEN1_B_L = 0;
                        }


                        if (TabRes2 == 0) {
                            PWM1_C_H = 0;
                            PWM1_C_L = 1;
                            PEN1_C_H = 0;
                            PEN1_C_L = 0;
                        } else {
                            PWM1_C_H = 0;
                            PWM1_C_L = 0;
                            PEN1_C_H = 1;
                            PEN1_C_L = 0;
                        }

                    }
                    if (!SIN_MIDDLE) {
                        SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                        SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                        SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                    } else {
                        SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                    }

                    break;
                case 6:
                    if (!SIN_MIDDLE) {
                        ThetaIndex = THETA_NUM - Theta1CntPWM - 193;
                        TabRes0 = (unsigned long int) tab_sin[ThetaIndex];
                        TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 65];
                        TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 321];
                    } else {
                        TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 193]);
                        TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 65]);
                        TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 321]);
                    }



                    if (!StrongMode) {


                        if (TabRes0 == 0) {
                            PWM1_A_H = 0;
                            PWM1_A_L = 1;
                            PEN1_A_H = 0;
                            PEN1_A_L = 0;
                        } else {
                            PWM1_A_H = 0;
                            PWM1_A_L = 0;
                            PEN1_A_H = 1;
                            PEN1_A_L = 0;
                        }

                        if (TabRes1 == 0) {
                            PWM1_B_H = 0;
                            PWM1_B_L = 1;
                            PEN1_B_H = 0;
                            PEN1_B_L = 0;
                        } else {
                            PWM1_B_H = 0;
                            PWM1_B_L = 0;
                            PEN1_B_H = 1;
                            PEN1_B_L = 0;
                        }


                        if (TabRes2 == 0) {
                            PWM1_C_H = 0;
                            PWM1_C_L = 1;
                            PEN1_C_H = 0;
                            PEN1_C_L = 0;
                        } else {
                            PWM1_C_H = 0;
                            PWM1_C_L = 0;
                            PEN1_C_H = 1;
                            PEN1_C_L = 0;
                        }



                    }


                    if (!SIN_MIDDLE) {
                        SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                        SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                        SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                    } else {
                        SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                    }
                    break;
                case 4:
                    if (!SIN_MIDDLE) {
                        ThetaIndex = THETA_NUM - Theta1CntPWM - 257;
                        TabRes0 = (unsigned long int) tab_sin[ThetaIndex];
                        TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 129];
                        TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 1];
                    } else {
                        TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 257]);
                        TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 129]);
                        TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 1]);
                    }

                    if (!StrongMode) {

                        if (TabRes0 == 0) {
                            PWM1_A_H = 0;
                            PWM1_A_L = 1;
                            PEN1_A_H = 0;
                            PEN1_A_L = 0;
                        } else {
                            PWM1_A_H = 0;
                            PWM1_A_L = 0;
                            PEN1_A_H = 1;
                            PEN1_A_L = 0;
                        }

                        if (TabRes1 == 0) {
                            PWM1_B_H = 0;
                            PWM1_B_L = 1;
                            PEN1_B_H = 0;
                            PEN1_B_L = 0;
                        } else {
                            PWM1_B_H = 0;
                            PWM1_B_L = 0;
                            PEN1_B_H = 1;
                            PEN1_B_L = 0;
                        }


                        if (TabRes2 == 0) {
                            PWM1_C_H = 0;
                            PWM1_C_L = 1;
                            PEN1_C_H = 0;
                            PEN1_C_L = 0;
                        } else {
                            PWM1_C_H = 0;
                            PWM1_C_L = 0;
                            PEN1_C_H = 1;
                            PEN1_C_L = 0;
                        }

                    }


                    if (!SIN_MIDDLE) {
                        SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                        SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                        SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                    } else {
                        SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                    }

                    break;
                case 5:
                    if (!SIN_MIDDLE) {
                        ThetaIndex = THETA_NUM - Theta1CntPWM - 321;
                        TabRes0 = (unsigned long int) tab_sin[ThetaIndex];
                        TabRes1 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 193];
                        TabRes2 = (unsigned long int) tab_sin[THETA_NUM - Theta1CntPWM - 65];
                    } else {
                        TabRes0 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 321]);
                        TabRes1 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 193]);
                        TabRes2 = (long int) (tab_sin_M[THETA_NUM - Theta1CntPWM - 65]);
                    }


                    if (!StrongMode) {

                        if (TabRes0 == 0) {
                            PWM1_A_H = 0;
                            PWM1_A_L = 1;
                            PEN1_A_H = 0;
                            PEN1_A_L = 0;
                        } else {
                            PWM1_A_H = 0;
                            PWM1_A_L = 0;
                            PEN1_A_H = 1;
                            PEN1_A_L = 0;
                        }

                        if (TabRes1 == 0) {
                            PWM1_B_H = 0;
                            PWM1_B_L = 1;
                            PEN1_B_H = 0;
                            PEN1_B_L = 0;
                        } else {
                            PWM1_B_H = 0;
                            PWM1_B_L = 0;
                            PEN1_B_H = 1;
                            PEN1_B_L = 0;
                        }


                        if (TabRes2 == 0) {
                            PWM1_C_H = 0;
                            PWM1_C_L = 1;
                            PEN1_C_H = 0;
                            PEN1_C_L = 0;
                        } else {
                            PWM1_C_H = 0;
                            PWM1_C_L = 0;
                            PEN1_C_H = 1;
                            PEN1_C_L = 0;
                        }

                    }


                    if (!SIN_MIDDLE) {
                        SV_PWM1_0 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes0) >> 8);
                        SV_PWM1_1 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes1) >> 8);
                        SV_PWM1_2 = (unsigned int) (((unsigned long int) Amplitude1Tmp * TabRes2) >> 8);
                    } else {
                        SV_PWM1_0 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes0) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_1 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes1) >> 8) + MAX_PWM_CONST / 2);
                        SV_PWM1_2 = (unsigned int) ((((long int) Amplitude1Tmp * TabRes2) >> 8) + MAX_PWM_CONST / 2);
                    }

                    break;


            }

        }
    }

    if (TestingSin) {
        if ((ThetaIndex != ThetaIndexPrev)&&(ThetaIndex > 2)&&(ThetaIndex < 380)) {

            if (ThetaIndex > ThetaIndexPrev)
                ThetaIndexINC = 1;
            if (ThetaIndex < ThetaIndexPrev)
                ThetaIndexINC = 0;
        }
        ThetaIndexPrev = ThetaIndex;


        if ((ThetaIndex >= 20)&&(ThetaIndex < 44))
            ThetaSector = 1;
        if ((ThetaIndex >= 84)&&(ThetaIndex < 108))
            ThetaSector = 2;
        if ((ThetaIndex >= 148)&&(ThetaIndex < 172))
            ThetaSector = 3;
        if ((ThetaIndex >= 212)&&(ThetaIndex < 236))
            ThetaSector = 4;
        if ((ThetaIndex >= 276)&&(ThetaIndex < 300))
            ThetaSector = 5;
        if ((ThetaIndex >= 340)&&(ThetaIndex < 364))
            ThetaSector = 6;

        if (ThetaSectorPrev != ThetaSector) {
            if ((ThetaSector == 1)&&(StrtTestingSin)) {
                ThetaIDX = 0;
                ThetaMass[ThetaIDX] = 1;
                StrtTestingSin = 0;
            }
            if (!StrtTestingSin) {
                if (ThetaSector == 2)
                    ThetaMass[ThetaIDX] = 2;
                if (ThetaSector == 3)
                    ThetaMass[ThetaIDX] = 3;
                if (ThetaSector == 4)
                    ThetaMass[ThetaIDX] = 4;
                if (ThetaSector == 5)
                    ThetaMass[ThetaIDX] = 5;
                if (ThetaSector == 6)
                    ThetaMass[ThetaIDX] = 6;

                if (ThetaIDX == 5) {
                    if ((((ThetaMass[0] == 1)&&(ThetaMass[1] == 2)&&(ThetaMass[2] == 3)&&(ThetaMass[3] == 4)&&(ThetaMass[4] == 5)&&(ThetaMass[5] == 6)) && ThetaIndexINC) ||
                            (((ThetaMass[0] == 1)&&(ThetaMass[1] == 6)&&(ThetaMass[2] == 5)&&(ThetaMass[3] == 4)&&(ThetaMass[4] == 3)&&(ThetaMass[5] == 2))&&!ThetaIndexINC)) {
                        TestSIN_Ok = 1;
                    }
                    /*      else
                          {
                              TestSIN_Ok=0;
                          }
                     */
                    if (TestSIN_OkCnt) {
                        TestSIN_OkCnt--;
                        if (TestSIN_OkCnt) {
                            ThetaIDX = 0;
                        } else
                            TestingSin = 0;
                    } else
                        TestingSin = 0;

                }
                ThetaIDX++;
            }
        }
        ThetaSectorPrev = ThetaSector;

    }

    SetPWM1_SV();



}


    
    
void InitPWM_Vector(void) {
    //Mgnovenniy = 0;

    /* Set PWM Period on Primary Time Base */
    PTPER = 6000;
    /* Set Phase Shift */

    if (0) {
        PHASE1 = 1500;
        PHASE2 = 1500;
        PHASE3 = 1500;
    } else {
        PHASE1 = MAX_PWM + DEADTIME + Khard;
        PHASE2 = MAX_PWM + DEADTIME + Khard;
        PHASE3 = MAX_PWM + DEADTIME + Khard;
    }
    /* Set Duty Cycles */

    //MDC=200;

    PDC1 = 100;
    PDC2 = 100;
    PDC3 = 100;
    /* Set Dead Time Values */
    DTR1 = DTR2 = DTR3 = DEADTIME; //DTRx Registers are ignored in this mode
    ALTDTR1 = ALTDTR2 = ALTDTR3 = DEADTIME;
    /* Set PWM Mode to Complementary */
    IOCON1 = IOCON2 = IOCON3 = 0xc000;
    /* Set Primary Time Base, Edge-Aligned Mode and Independent Duty Cycles */
    if (ShortCircuit)
        PWMCON1 = PWMCON2 = PWMCON3 = 0x1204;
    else
        PWMCON1 = PWMCON2 = PWMCON3 = 0x0204;

    /* Configure Faults */
    FCLCON1 = FCLCON2 = FCLCON3 = 0x0003;


    PEN1_A_H = 1;
    PEN1_A_L = 1;
    PEN1_B_H = 1;
    PEN1_B_L = 1;
    PEN1_C_H = 1;
    PEN1_C_L = 1;

    //#if !defined TEST_PWM_KEYS
    if (!TEST_PWM_KEYS) {


        if (!SIN_MIDDLE) {
            if (ShortCircuit) {
                FCLCON1bits.FLTSRC = 0b01001;
                FCLCON2bits.FLTSRC = 0b01001;
                FCLCON3bits.FLTSRC = 0b01001;
                FCLCON1bits.FLTMOD = 0; //1;
                FCLCON2bits.FLTMOD = 0; //1;
                FCLCON3bits.FLTMOD = 0; //1;
#if defined REV2
                FCLCON1bits.FLTPOL = 0; //1;
                FCLCON2bits.FLTPOL = 0; //1;
                FCLCON3bits.FLTPOL = 0; //1;
#else
                FCLCON1bits.FLTPOL = 0;
                FCLCON2bits.FLTPOL = 0;
                FCLCON3bits.FLTPOL = 0;
#endif

                IOCON1bits.FLTDAT = 0b00;
                IOCON2bits.FLTDAT = 0b00;
                IOCON3bits.FLTDAT = 0b00;
            } else {
                if (0) {
                    FCLCON1bits.FLTSRC = 0b01001;
                    FCLCON2bits.FLTSRC = 0b01001;
                    FCLCON3bits.FLTSRC = 0b01001;
                    FCLCON1bits.FLTMOD = 1;
                    FCLCON2bits.FLTMOD = 1;
                    FCLCON3bits.FLTMOD = 1;
#if defined REV2
                    FCLCON1bits.FLTPOL = 1;
                    FCLCON2bits.FLTPOL = 1;
                    FCLCON3bits.FLTPOL = 1;
#else
                    FCLCON1bits.FLTPOL = 0;
                    FCLCON2bits.FLTPOL = 0;
                    FCLCON3bits.FLTPOL = 0;
#endif

                    IOCON1bits.FLTDAT = 0b00;
                    IOCON2bits.FLTDAT = 0b00;
                    IOCON3bits.FLTDAT = 0b00;
                } else {
                    FCLCON1bits.FLTMOD = 3;
                    FCLCON2bits.FLTMOD = 3;
                    FCLCON3bits.FLTMOD = 3;
                }
            }
        } else {
            FCLCON1 = FCLCON2 = FCLCON3 = 0x0003;
        }
    }
    //#endif
    //SEVTCMP=100;


    /* 1:1 Prescaler */
    PTCON2 = 0x0000;
    /* Enable PWM Module */
    PTCON = 0x8000;


    /*	//----------------------------------
        //	Unlock the Reprogrammable Pin Mechanism
        __builtin_write_OSCCONL(OSCCON & (~(1<<6))); // clear bit 6
        // Select RP88 as input for fault 1
        RPINR12 = 0x0058;
        //	Lock the Reprogrammable Pin Mechanism
        __builtin_write_OSCCONL(OSCCON | (1<<6)); 	 // Set bit 6

        PTCON = 0x8000;		// start PWM


     */
    //while (1);
}
