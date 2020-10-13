#include "Mn.h"
#include <xc.h>
#include <math.h>


unsigned char MaxAngleStopBreak;

void GyroAcel(void) {
    float RotX = GyroYFl*TICK_PERIOD;
    float RotY = -GyroXFl*TICK_PERIOD;
    float RotZ = -GyroZFl*TICK_PERIOD;

    float Alf = RotX * 8.75 / 57296, Bt = RotY * 8.75 / 57296, Gm = RotZ * 8.75 / 57296;
    float SinBt = sin(Bt); 
    float CosBt = cos(Bt); 
    float SinAlf = sin(Alf);
    float CosAlf = cos(Alf);
    float SinGm = sin(Gm);
    float CosGm = cos(Gm);

    if (!Starting) {

        XNew = (AccXFlPrev * CosBt * CosGm - AccYFlPrev * CosBt * SinGm + AccZFlPrev * SinBt) * KGYRO + KACC*AccXFl;
        YNew = (AccXFlPrev * SinAlf * SinBt * CosGm + AccXFlPrev * CosAlf * SinGm + AccYFlPrev * SinAlf * SinBt * SinGm + AccYFlPrev * CosAlf * CosGm - AccZFlPrev * SinAlf * CosBt)
                * KGYRO + KACC*AccYFl;
        ZNew = (-AccXFlPrev * CosAlf * SinBt * CosGm + AccXFlPrev * SinAlf * SinGm + AccYFlPrev * CosAlf * SinBt * SinGm + AccYFlPrev * SinAlf * CosGm + AccZFlPrev * CosAlf * CosBt)
                * KGYRO + KACC*AccZFl;

        if (!Vertical) {
            if (!RotAlfaXRes) {
                if ((YNew == 0)&&(ZNew == 0))
                    AlfaXRes = AlfaXResPrev;
                else {
                    AlfaXRes = atan(XNew / (sqrt(YNew * YNew + ZNew * ZNew)))*57.296;
                    Starting2 = 0;
                }
                AlfaXResPrev = AlfaXRes;
            } else {
                if ((XNew == 0)&&(ZNew == 0))
                    AlfaZRes = AlfaZResPrev;
                else {
                    AlfaZRes = atan(ZNew / (sqrt(XNew * XNew + YNew * YNew)))*57.296;
                    Starting2 = 0;
                }
                AlfaZResPrev = AlfaZRes;
                AlfaXRes = AlfaZRes;
            }

            if ((XNew == 0)&&(ZNew == 0))
                AlfaYRes = AlfaYResPrev;
            else {
                AlfaYRes = atan(YNew / (sqrt(XNew * XNew + ZNew * ZNew)))*57.296;
                Starting2 = 0;
            }
            AlfaYResPrev = AlfaYRes;



        } else {
            //      if (!RotAlfaXRes)
            {
                if ((YNew == 0)&&(ZNew == 0))
                    AlfaXRes = AlfaXResPrev;
                else {
                    AlfaXRes = atan(XNew / (sqrt(YNew * YNew + ZNew * ZNew)))*57.296;
                    Starting2 = 0;
                }
                AlfaXResPrev = AlfaXRes;
            }
            //    else
            {
                if ((XNew == 0)&&(ZNew == 0))
                    AlfaZRes = AlfaZResPrev;
                else {
                    AlfaZRes = atan(ZNew / (sqrt(XNew * XNew + YNew * YNew)))*57.296;
                    Starting2 = 0;
                }
                AlfaZResPrev = AlfaZRes;
                AlfaYRes = AlfaZRes;
            }
        }



        if (Starting2) {
            Starting2 = 0;
            return;
        }

        TiltXThis = (int) (AlfaXRes * 100);
        TiltYThis = (int) (AlfaYRes * 100);

        AccXFlPrev = XNew;
        AccYFlPrev = YNew;
        AccZFlPrev = ZNew;

    } else {
        Starting = 0;
        AccXFlPrev = AccXFl;
        AccYFlPrev = AccYFl;
        AccZFlPrev = AccZFl;
        Starting2 = 1;
    }

    if (!RotAlfaXRes) {
        GyroZFilter = GyroZFilter * KFilterPrev + ((long int) GyroZFl) * KFilter;
    } else {
        GyroZFilter = GyroZFilter * KFilterPrev + ((long int) GyroYFl) * KFilter;
    }
    GyroZFilter = GyroZFilter >> 7;
}

void MonoWheel(void) {
    if (!StartingMoveCnt) {
        if (Monocycle) {
            if (TiltZadAdd < TiltZadAddMustBe)
                TiltZadAdd = TiltZadAdd + 0.02;
            if (TiltZadAdd > TiltZadAddMustBe)
                TiltZadAdd = TiltZadAdd - 0.02;

            if (TiltZadAdd > 0) {
                if (TiltZadAdd > MaxAngleStopBreak)
                    TiltZadAdd = MaxAngleStopBreak;
            } else {
                if (TiltZadAdd<-MaxAngleStopBreak)
                    TiltZadAdd = -MaxAngleStopBreak;
            }


            if (Spd1ResPlus > Spd1KpLevel) {
                KpAddSpd = Spd1ResPlus - Spd1KpLevel;
                KpAddSpd = KpAddSpd*KpKpSpd;
            } else
                KpAddSpd = 0;


            if (Spd1ResPlus > Spd1KdLevel) {
                KdAddSpd = Spd1ResPlus - Spd1KdLevel;
                KdAddSpd = KdAddSpd*KdKpSpd;
            } else
                KdAddSpd = 0;

            if (Spd1ResPlus < SlowSpeedForKpFl)
                KpMustBe = KpSlowSpeed;
            else
                KpMustBe = KpWheelingMem + KpAddSpd;

            if (KpMustBe > KpMax)
                KpMustBe = KpMax;

            float TiltLight = AlfaYRes - (TiltZad);
            if (LightsTudaSuda) {


                if (LightsStopMonoDir) {
                    if (TiltLight > 0.5) {
#if !defined VECTOR
                        Right = 1;
                        Left = 0;
#else
                        Right = 0;
                        Left = 1;
#endif

                    }
                    if (TiltLight<-0.5) {
#if !defined VECTOR
                        Right = 0;
                        Left = 1;
#else
                        Right = 1;
                        Left = 0;
#endif
                    }
                } else {
                    if (TiltLight < 0.5) {
#if !defined VECTOR
                        Right = 1;
                        Left = 0;
#else
                        Right = 0;
                        Left = 1;
#endif
                    }
                    if (TiltLight>-0.5) {
#if !defined VECTOR
                        Right = 0;
                        Left = 1;
#else
                        Right = 1;
                        Left = 0;
#endif
                    }
                }
                if ((TiltLight>-0.5)&&(TiltLight < 0.5)) {
#if !defined VECTOR
                    Right = 0;
                    Left = 0;
#else
                    Right = 1;
                    Left = 1;
#endif
                }

            } else {
                if (LightsStopMonoDir) {
                    if (TiltLight > 0.5)
                        StopLights = 1;
                    else
                        StopLights = 0;
                } else {
                    if (TiltLight<-0.5)
                        StopLights = 1;
                    else
                        StopLights = 0;
                }
                if (GyroZFilter<-GyroZFlTurn)
                    LeftTurn = 1;
                else
                    LeftTurn = 0;
                if (GyroZFilter > GyroZFlTurn)
                    RightTurn = 1;
                else
                    RightTurn = 0;
            }

            if ((BreakPressedMonocycle) || (Spd1FlPlus > BreakMonocycleSpd)) {
                if (!MonoStopDirection)
                    TiltZadAddMustBe = 30;
                else
                    TiltZadAddMustBe = -30;
                if (BreakButtonMonocycle) {
                    if (!Sounds)
                        SoundNum = 10;
                }
            } else
                TiltZadAddMustBe = 0;


            if (StopMotorMonocycle) {
                StrongMode = 0;
                DS = 1;
                NoBalance = 1;

            }

            if (OnDelayCnt) {
                OnDelayCnt--;
                if ((!Sounds)&&(BuzzerOffTime == 0))
                    SoundNum = 23;

            }

            if (NoBalance) {
                TiltZadAddMustBe = 0;
                KpMustBe = 0;
                PWM1Temp = 0;
                EPrev = 0;
                if ((Spd1ResPlus < 4)&&(!OnDelayCnt)&&(!StopMotorMonocycle)&&(AlfaXRes>-YLimit)&&(AlfaXRes < YLimit)&&(AlfaYRes > (TiltZad - 1))&&(AlfaYRes < (TiltZad + 1))&&(!CriticalError)&&!ChagerViaMotor) {
                    if (!Segway) {
                        NoBalance = 0;
                        RotAddSumm = 0;
                        SoundNum = 1;
                        if (StrongModeMem)
                            StrongMode = 1;
                        EPrevFl = 1;
                        if (!WheelingNew)
                            ESumm = 0;

                        if (DS) {
                            DS = 0;
                            RdSensors();
                        }


                        if (Sensorless) {
                            Sensorless = 0;
                            SensorlessNotBEMF = 0;
                            SensorlessStartNoHalls = 0;
                            CurrUst = CurrUstWork;
                            CurrLimit = CurrLimitWork;
                            if (VectorMem)
                                VectorInit();
                            else
                                TrapeziumInit();
                            ChangeCVR();
                            RdSensors();
                        }
                    } else {
                        if (HumanSensor) {
                            if (OkToBalance) {
                                NoBalance = 0;
                                RotAddSumm = 0;
                                SoundNum = 1;
                                if (StrongModeMem)
                                    StrongMode = 1;
                                EPrevFl = 1;
                                if (!WheelingNew)
                                    ESumm = 0;

                                if (DS) {
                                    DS = 0;
                                    RdSensors();
                                }

                            }
                        } else {
                            NoBalance = 0;
                            RotAddSumm = 0;
                            SoundNum = 1;
                            if (StrongModeMem)
                                StrongMode = 1;
                            EPrevFl = 1;
                            if (!WheelingNew)
                                ESumm = 0;

                            if (DS) {
                                DS = 0;
                                RdSensors();
                            }

                        }
                    }
                }
            }
            if (!NoBalance) {
                if ((AlfaXRes<-XLimit) || (AlfaXRes > XLimit) || (AlfaYRes < (TiltZad - YLimit)) || (AlfaYRes > (TiltZad + YLimit))) {
                    SoundNum = 10;
                    StrongMode = 0;
                    DS = 1;
                    NoBalance = 1;

                    OnDelayCnt = OnDelayConst;

                }

                if (Sensorless) {
                    Sensorless = 0;
                    SensorlessNotBEMF = 0;
                    SensorlessStartNoHalls = 0;
                    CurrUst = CurrUstWork;
                    CurrLimit = CurrLimitWork;
                    if (VectorMem)
                        VectorInit();
                    else
                        TrapeziumInit();
                    ChangeCVR();
                    RdSensors();
                }

                if (DirBalance)
                    E = TiltZad + TiltZadAdd - AlfaYRes;
                else
                    E = -TiltZad - TiltZadAdd + AlfaYRes;

                if (EPrevFl) {
                    EPrevFl = 0;
                    EPrev = E;
                }

                if (E < 0)
                    EPlus = -E;
                else
                    EPlus = E;

                if (EPrev < 0)
                    EPrevPlus = -EPrev;
                else
                    EPrevPlus = EPrev;


                float Kdd;

                if (DifferentKd) {


                    switch (KdStateMachine) {
                        case 0:
                            CntKdSwitch = CntKdSwitchCONST;
                            if (EPlus >= EPrevPlus)
                                KdStateMachine = 1;
                            else
                                KdStateMachine = 2;

                            break;
                        case 1:
                            if (EPlus >= EPrevPlus) {
                                if (CntKdSwitch) {
                                    CntKdSwitch--;
                                    if (!CntKdSwitch)
                                        Kd = KdNoMan;
                                }
                            } else
                                KdStateMachine = 0;
                            break;
                        case 2:
                            if (EPlus < EPrevPlus) {
                                if (CntKdSwitch) {
                                    CntKdSwitch--;
                                    if (!CntKdSwitch)
                                        Kd = KdNoManR;
                                }
                            } else
                                KdStateMachine = 0;
                            break;
                        default:
                            KdStateMachine = 0;
                            break;
                    }

                    if (Kd > KdMax)
                        Kd = KdMax;

                    if (Kd < KdMin)
                        Kd = KdMin;

                } else {
                    Kdd = KdNoMan;



                    if (KdMustBe != (Kdd + KdAddSpd)) {
                        KdMustBe = (Kdd + KdAddSpd);
                    }

                    if (KdMustBe > KdMax)
                        KdMustBe = KdMax;

                    if (KdMustBe < KdMin)
                        KdMustBe = KdMin;

                    if (KdMustBe != KdMustBePrev) {
                        KdDiff = (Kd - KdMustBe) / 100;
                        if (KdDiff == 0)
                            KdDiff = 1;
                        if (KdDiff < 0)
                            KdDiff = -KdDiff;

                        KdMustBePrev = KdMustBe;

                    }


                    if (Kd < KdMustBe) {
                        Kd = Kd + KdDiff;
                        if (Kd > KdMustBe)
                            Kd = KdMustBe;
                    }

                    if (Kd > KdMustBe) {
                        Kd = Kd - KdDiff;
                        if (Kd < KdMustBe)
                            Kd = KdMustBe;
                    }

                }

                Ed = E - EPrev;
                EPrev = E;
                Eid = Ed*KiKd;
                Ed = Ed*Kd;

                if (Ed > 0) {
                    if (Ed > EdPWMmax) {
                        Ed = EdPWMmax;
                    }
                } else {
                    if (Ed<-EdPWMmax) {
                        Ed = -EdPWMmax;
                    }
                }


                float ETemp = E;

                if (E < 0)
                    ETemp = -ETemp;

                if (ETemp < KpKpDeadZone)
                    ETemp = 0;
                else {
                    ETemp = ETemp - KpKpDeadZone;
                    if (ETemp > (KpKpZoneEnd - KpKpDeadZone))
                        ETemp = KpKpZoneEnd - KpKpDeadZone;
                }
                KpK = (ETemp * KpKp);

                if (KpK < 0)
                    KpK = -KpK;

                if (KpKp >= 0)
                    KpK = KpK + 1;
                else {
                    KpK = 1 - KpK;
                    if (KpK < 0)
                        KpK = 0;
                }

                Kp2 = KpK*Kp;

                ETemp = E;

                if (E < 0)
                    ETemp = -ETemp;

                if (ETemp < KpKp2DeadZone)
                    ETemp = 0;
                else {
                    ETemp = ETemp - KpKp2DeadZone;
                    if (ETemp > (KpKp2ZoneEnd - KpKp2DeadZone))
                        ETemp = KpKp2ZoneEnd - KpKp2DeadZone;
                }
                KpK = (ETemp * KpKp2);

                if (KpK < 0)
                    KpK = -KpK;

                if (KpKp2 >= 0)
                    KpK = KpK + 1;
                else {
                    KpK = 1 - KpK;
                    if (KpK < 0)
                        KpK = 0;
                }


                Kp_p = KpK*Kp2;


                if (Kp >= 0) {
                    if (Kp_p > KpMax)
                        Kp_p = KpMax;

                    if (Kp_p < KpMin)
                        Kp_p = KpMin;
                } else {
                    if (Kp_p<-KpMax)
                        Kp_p = -KpMax;
                }

                float EpTmp;

                if (E > 0) {
                    if (E > KpDeadZone)
                        EpTmp = E - KpDeadZone;
                    else
                        EpTmp = 0;
                } else {
                    if (E<-KpDeadZone)
                        EpTmp = E + KpDeadZone;
                    else
                        EpTmp = 0;
                }


                Ep = EpTmp*Kp_p;

                if (Ep > 0) {
                    if (Ep > EpPWMmax) {
                        Ep = EpPWMmax;
                    }
                } else {
                    if (Ep<-EpPWMmax) {
                        Ep = -EpPWMmax;
                    }
                }


                ETemp = E;

                if (E < 0)
                    ETemp = -ETemp;

                if (ETemp < KiKpDeadZone)
                    ETemp = 0;
                else
                    ETemp = ETemp - KiKpDeadZone;
                KiK = (ETemp * KiKp);



                if (KiK < 0)
                    KiK = -KiK;
                KiK = KiK + 1;

                Ki_p = KiK*Ki;

                if (TimeDecreaseKi == 0)
                    TimeDecreaseKi = 100;


                if (Ki_p > Ki_pPrev) {
                    Ki_pp = Ki_p;
                    Ki_ppDelta = (Ki_pp - Ki) / TimeDecreaseKi;
                } else {
                    Ki_pp = Ki_pPrev;
                    if (Ki_pp > Ki) {
                        if (Ki_pp - Ki > 0.05) {
                            float tmpFl = (Ki_pp - Ki) / TimeDecreaseKi;
                            if (tmpFl > Ki_ppDelta)
                                Ki_ppDelta = tmpFl;
                        } else
                            Ki_ppDelta = 0.05;
                        Ki_pp = Ki_pp - Ki_ppDelta;
                        if (Ki_pp < Ki_p)
                            Ki_pp = Ki_p;
                    }
                }


                if (Ki > 0) {
                    if (Ki_pp > KiMax)
                        Ki_pp = KiMax;
                } else {
                    if (Ki_pp<-KiMax)
                        Ki_pp = -KiMax;
                }

                Ki_pPrev = Ki_pp;

                ELimited = E;
                if (ELimited > ELimitedMem)
                    ELimited = ELimitedMem;
                if (ELimited<-ELimitedMem)
                    ELimited = -ELimitedMem;

                ESumm = ESumm + ELimited;
                ESumm = ESumm + Eid;

                float ESummLimit = ESumm*Ki_pp, MAX_PWM_CONSTTmp = ((float) MAX_PWM_CONST) / Ki_pp;

                if (ESummLimit > MAX_PWM_CONST)
                    ESumm = MAX_PWM_CONSTTmp;
                if (ESummLimit<-MAX_PWM_CONST)
                    ESumm = -MAX_PWM_CONSTTmp;



                Ei = ESumm*Ki_pp;


                if (Ei > 0) {
                    if (Ei > EiPWMmax) {
                        Ei = EiPWMmax;
                        ESumm = Ei / Ki_pp;
                        if (I_PWMmaxSignal) {
                            if ((!Sounds)&&(BuzzerOffTime == 0))
                                SoundNum = 10;
                        }

                    }
                } else {
                    if (Ei<-EiPWMmax) {
                        Ei = -EiPWMmax;
                        ESumm = Ei / Ki_pp;
                        if (I_PWMmaxSignal) {
                            if ((!Sounds)&&(BuzzerOffTime == 0))
                                SoundNum = 10;
                        }
                    }
                }

                PWM1Temp = (int) Ep + (int) Ei + (int) Ed;

            }
        }
    }
}
