
       case 3:
               if (HvBt2)
                {
                   if (AntiPolice)
                   {
                       HvBt2=0;
                       return;
                   }

                    if (!PID_On)
                    {
                        if (!Wheeling)
                        {
                            if (!SpeedControl)
                            {
                    SoundNum=1;
                    StrtPID_On=1;
                    BtPID_Activated=1;
                       /*    if (StrongModePID)
                    {
                        PrevStrongMode=StrongMode;
                        StrongMode=1;
                    }*/
                            }

                        }
                    }
                    else
                    {
                    if (SpeedControl)
                    {
                        /*if (StrongModePID)
                            {
                            PrevStrongMode=StrongMode;
                            StrongMode=1;
                            }*/
                    SpeedControlPID=1;
                    SpeedControlPIDOffCnt=500;
                    Spd1UST=Spd1Res;
                    //StrtPID_On=1;
                    SoundNum=1;
                    }
                    }
                HvBt2=0;
                }
              if (Bt2Up)
                {
                   if (AntiPolice)
                   {
                       Bt2Up=0;
                       return;
                   }

                         if (StrongModePID)
                        StrongMode=PrevStrongMode;
 
                    if (!SpeedControl)
                PID_On=0;
                    else
                    {
                        if (!StartingBTN)
                        {
                            if (SpeedControlPID)
                                SoundNum=10;
                        }
                    SpeedControlPID=0;
                    }

                Bt2Up=0;
                }
            break;