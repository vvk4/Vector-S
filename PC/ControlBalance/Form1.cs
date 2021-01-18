using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using X1;



namespace ControlBalance
{
    public delegate void MyDelegate(int dlg);


    public partial class Form1 : Form
    {

        Form F2;
        uint StartCNT = 30;
        String LogFileString;
        byte LightMode, Crr1Corr, PWMSignal, HallsLines, StopIfPWM100Time, CntKdSwitchCONST, PWMkHz;
        short EpLog, EiLog, EdLog;
        ushort LightSensorThresholdLo, LightSensorThresholdHi, CurrentMaxCurrentOnly, K_PWM_Nastr, SpdStartLevel, RegenOffMem, KpKpDeadZoneMem, KiKpDeadZoneMem, TimeHumanSensorOff;
        ushort FaultStatus1Res, VGSStatus2Res, KiMax, DeadZoneHandleBarSegway, PWMChangedThreshold;
        short JoystickCalibrX, JoystickCalibrY, JoistickDeadZone, KpSlowSpeed, KiKpMustBe, KRotMustBe, KpRotMustBe, KiRotMustBe, Eid, KdNoManR, KpDeadZone, PWMSignalTimer;
        public ushort AutoNastroykaState;
        public int StatFlags2;
        public Socket s;
        FileStream w;
        int CntMixedModeMax, MixedModeLevelOn, MixedModeLevelOff, CurrMixed, numericUpDown173PrevValue;
        float Temperature1, Temperature2, Temperature3, TemperatureMaxOUT, TemperatureMaxIN, TemperatureMaxOUT_H, TemperatureMaxIN_H, Temperature4, Temperature5, Temperature6, Spd1USTKMH, _3VFl, _5VFl, _12VFl;
        bool radioButton7CannotSndCMD, radioButton10CannotSndCMD, radioButton11CannotSndCMD, radioButton12CannotSndCMD, CanShowMsgChargingComplete, DataShown, ShowPassword;
        bool radioButton25CannotSndCMD, radioButton26CannotSndCMD, radioButton27CannotSndCMD, radioButton28CannotSndCMD;
        bool GettinPhase = false, RunningThread = false;
        uint PhasesCnt2, Phase1Period1, Phase1Period2, Phase1Period4, Phase1Period5, TimeOutLoadOptions1, TimeOutLoadOptions2, DataShownCnt;
        int BMSTimeOt, SummOk, SummNOk, KiCurr, KpCurr, CurrUst, CurrUstSpd0, CurrUstTek, SensorlessCurrUst, ConnectionCnt, MsgOpenPortCnt, KpTemperIN, KpTemperOUT, KiTemperIN, KiTemperOUT, BigCurrent;
        int MAX_PWM_MEM, MaxSpdRevers, MAX_PWM_Revers, AutoPID_On_CntConst, SaveTimeOut, Phase1Period6, CurrPhaseLimit, CurrPhaseLimitSpd0, CurrPhaseLimitTek, CntNoChange;
        short CurrA_P, CurrA_N, CurrC_P, CurrC_N, ThrottleLevelUpOff;
        short KdOneTwoLeg, Spd1Fl, EPID_Res, V_MIN_OFF, V_MIN_Pre_OFF, V_MIN_Sound, V_min_OverV, SensorlessCntAlignConst, KpKpSpd, Spd1UST_Tmp;
        short TiltYCorr, HighSpeed, GoalSpeed, StartRotHighSpeed, KRotHighSpeed, GyroYFl, GyroXFl, GyroZFl, Ki_PWM_Mode, KpKpZoneEnd;
        ushort SpdRstSpeedLim, SpeedLimitSt4, KFirstBreak, SensorLessTimerConst, SensorLessTimerConst2, SensorlessSpdChngCntConst, ADCThrottleBreak;
        double Cr1, GyroYAv;
        uint V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, BatteryKeys, UBatHi;
        ushort BatErr, SensorThreshold, SensorThresholdUp, BreakThreshold, RCON_Mem;
        byte ChagerKeys, KAccGyroSteer, KdAverage, PhasePERMASS, PhasePERMASS_SHFT, HallDelay1_F, HallDelay1_B, CriticalError, ThrottleTmpChngMem, HallDelay1_Tek_F, HallDelay1_Tek_B;
        byte Theta1Zero, Theta2Zero, But1Func, But2Func, But3Func, But4Func, But5Func, SensorllessSpdThreshold, CurrLimitTek, TemperatureTYPE, Profile, MaxAngleStopBreak, MixedModeSlowSpeed;
        byte _3psnSwitchBt3, _3psnSwitchBtNotPressed, _3psnSwitchBt4, _2WDMode;
        ushort UseTmr, TmrCntDelay = 5, DEADTIME_Si8233, Ki_PWM_ModeOff, KeyLightBrightness, ButtonBreakOnlyTime, SpdKiMin, KiMin, ELimitedMem;
        uint CurrTuda1, CurrRegen1, Timer1Mem, Timer2Mem, TimerCnt, SerNumber, ProtectValue;

        int DiffAlfaConstL, DiffAlfaConstH, TiltZadState5, Temperature;
        int BeepPauseConstAlm, BzOnCntSeriaConstAlm, CntSingleBeepAlm;
        int KpSPD, ZeroCurr1, EpCurr1;
        bool HeaderOk = false;


        byte HallDelay1MaxSPD_F, HallDelay1MaxSPD_B, HallDelayMaxSPD, OCP_DEG, VDS_LVL, TemperatureTYPE_FETs;

        StreamWriter sw;


        public byte SensOrder1;
        uint PhasePer1;

        short ChagerCurr, P_Curr, I_Curr, P_U, I_U, BreakMonocycleSpd, TimeDecreaseKi, KdMax, KdMin, KiKd, VectorOnOffSpdLo, VectorOnOffSpdHi, KiUBTCoeff;

        int Diametr1, PhasesPerRev1;
        byte AutoPID_On_Speed, SlowStrtSpd, AntiPolicePower, MPU6050Err, CurrSensor, Halls;

        float AutoPID_On_PWM;
        string SSID = null;
        string passwordWiFi = null;




        short TiltZadAddNoManOneLeg, BreakThresholdDn, BreakThresholdUp, GyroZFlTurn, ECurr1Summ, KpNoManOneLeg;
        int Preas1ADC, Preas2ADC;


        int KiRotOneTwoLeg;





        int LastMainTiltAngleMnErr, LastSteerTiltAngleMnErr, TiltAngleAvMnErr, StatFlgs, StatFlgs3, StatFlgs4;
        int LastMainTiltAngleSteerErr, LastSteerTiltAngleSteerErr, TiltAngleAvSteerErr, TmrLocked;
        short AccX, AccY, AccZ;
        byte MainTiltNumErr, SteerTiltNumErr;
        double PhaseCr;
        ushort Spd0TimerConst, EpPWMmax, EiPWMmax, EdPWMmax, OnDelay;
        uint CntSamples;
        short AlfaXRes, AlfaYRes, GyroX, TiltXRes, PWM1, SenosrlessPWM1_1Const, SenosrlessPWM1_2Const, Curr1, PhaseCurr, Spd1Res, GyroVert_Steer, GyroZFilter, AlfaYResPrevAv, DiffBetweenTilts, KiNoManOneLeg;
        float UBT;
        byte[] TrmMass = new byte[255];
        byte[] SaveOptionsMass = new byte[1024];
        byte[] bytes = new byte[255];


        byte TstPhase, GyroVertical;
        bool CanChangePWM10kHz = true;
        short CanChangePWM10kHzCnt = 0, KpKpMustBe;

        //Seg
        float AlfaXResErr, AlfaYResErr, SteerXErr, SteerYErr;
        public uint Flgs3;
        byte Sensor2_Prev, Sensor1_Prev, ErrOptions, ErrorCode, NoBalanceCode;
        uint Speed, FlgsErr, Flgs1Err, Flgs2Err;
        uint Flgs, Flgs1, Flgs2, Flgs4, Flgs5;
        uint CntTilt, Distance;
        int CntSerialPort = 1;
        //Seg end

        public bool AutoNastroykaFl = false;

        bool GettingPacket_FL = false;
        //bool CHK_Err = false;
        byte BtRcPrev = 0;
        int CntRec = 0;
        byte[] PacketRec = new byte[255];
        byte _48V, MaxSpdPID;

        ushort MAH, SensorLessTimerConstMin, HallErrCnt, CntTurnOnConst, CntTurnOffConst;


        int _continue;
        int AngleLimitInt, AngleLimitReal, KpSPDReal, KdSPD, KiSPD, SpeedLimit1, SpeedLimit2, SpeedLimit3, NumSpeedLimit, XLimit, YLimit, UBatLow, KpBack, TiltBackLimit, SpdKpMax, SpdKdMax;
        int KpMax, KpMin;
        int KpMustBe, SpeedAdd, KpNoMan, KiNoMan, KGYRO, Kpx, Prorez = 0, TiltXSteerCorr, KpRot, KFilterPrev;
        short CalibrationAccX, CalibrationAccY, CalibrationAccZ, LightSensor, KdKpSpd;
        short CalibrationGyroX, CalibrationGyroY, CalibrationGyroZ;
        int KRot, StartRot, CurrLimit, Kp, CurrLimitSpd0, SensorlessCurrLimit, KiRot;

        ushort StrongModeSpdFilterOffMem;
        short CntPosConst, TiltYRes, Gyro4Y, PWMResR, CntUDPTrmConst, PWMRotR, PWMRotL, TiltZad, TiltCorr, RudderToSend;
        short PWMResL, Kp_PWM_Mode, KdMem;
        int CntPackets, E, Ep, CntImpR, CntImpL, Ediff, CntTST, StatFlags, Ki, StatFlags1;
        float ESumm, Ei, Kd, Ed, KdI;
        short KpKp2, KpKp2DeadZone, KpKp2ZoneEnd;

        float EPos, EPosPrev, EdPos, EPosSumm, EiPos, Angle, EpPos, T, Tj;
        short KpPos, KdPos, KiPos, AngleLimit, MaxSpdKMH, KTemperatureSPDControl;

        byte FirstTime, ShowSer, MovingON, Sensor1Snd, SlowSpeedForKp;
        uint Odometr, OdometrMem;

        ushort FirmwareVersion, ButtonBreakOnlyPWM, BuzzerOnEvent;

        short[] _11, _15;
        short[] TiltYMass, GyroXMass, GyroYMass, PWMMass;
        int[] _9, _10, TiltXMass, EpMass;
        float[] EdMass, EiMass;
        int[] CntPacketsMass, _12, _13, _14, _16;

        Thread UDPThread;

        IPAddress IPaddr, thisIP;
        int TrmPort = 51731;
        int listenPort = 51722;
        IPEndPoint ep;


        //const byte SEND_V_MIN_Pre_OFF = 1;
        const byte SEND_Kp = 2;
        const byte SEND_Kd = 3;
        const byte SEND_Ki = 4;
        //        const byte SEND_KpPos = 5;
        //        const byte SEND_KdPos = 6;
        //        const byte SEND_KiPos = 7;
        const byte SEND_StrtPOS = 8;
        const byte SEND_SensorlessCurrUst = 9;
        const byte SEND_CntUDPTrmConst = 10;
        //const byte SEND_AngleLimit = 11;
        const byte SEND_SenosrlessPWM1_1Const = 12;
        const byte SEND_KGYRO = 13;
        const byte SEND_GetOptions = 14;
        const byte SEND_ProgrammOptions = 15;
        const byte SEND_SensorlessCurrLimit = 16;
        const byte SEND_V_MIN_Sound = 17;
        const byte SEND_KpKpSpd = 18;
        //const byte SEND_V_min_OverV = 19;
        const byte SEND_NotAll = 20;
        const byte SEND_Clear = 21;
        const byte SEND_PWM1 = 22;
        const byte SEND_MAX_PWM_MEM = 23;
        const byte SEND_AutoPIDOn = 24;
        const byte SEND_AutoPIDOff = 25;
        //const byte SEND_CalibrGyro = 26;
        const byte SEND_CalibrAcc = 27;
        //const byte SEND_KRot = 28;
        const byte SEND_But1Func = 29;
        const byte SEND_PhasePERMASS = 30;
        const byte SEND_HallDelay1_F = 31;
        const byte SEND_HallDelay1_B = 32;
        const byte SEND_But2Func = 33;
        const byte SEND_CurrLimit = 34;
        //const byte SEND_SpeedLimit1 = 35;
        const byte SEND_DirectMotor = 36;
        const byte SEND_NotDirectMotor = 37;
        const byte SEND_CalibrGyro = 38;
        //const byte SEND_Theta1Zero = 39;
        const byte SEND_UBatLow = 40;
        const byte SEND_SbrosOdometra = 41;
        const byte SEND_Beep_10m = 42;
        const byte SEND_No_Beep_10m = 43;
        //        const byte SEND_Theta2Zero = 44;
        const byte SEND_VectorOn = 45;
        const byte SEND_VectorOff = 46;
        //const byte SEND_SpeedLimit3 = 47;
        //const byte SEND_NumSpeedLimit = 48;
        const byte SEND_GetErrors = 49;
        const byte SEND_AnalogBreakOn = 50;
        const byte SEND_KpMax = 51;
        //        const byte SEND_V_MIN_OFF = 52;
        const byte SEND_SpdKpMax = 53;
        const byte SEND_GetDataPacket = 54;
        const byte SEND_AnalogBreakOff = 55;
        const byte SEND_But3Func = 56;
        const byte SEND_But4Func = 57;
        const byte SEND_MAX_PWM_Revers = 58;
        const byte SEND_MaxSpdRevers = 59;
        const byte SEND_ClearErrors = 60;
        const byte SEND_WriteErrors = 61;
        //const byte SEND_KpStp = 62;
        const byte SEND_TemperatureMaxOUT_H = 63;
        //const byte SEND_TiltZadAddNoMan = 64;
        const byte SEND_KpNoManOneLeg = 65;
        const byte SEND_KiNoManOneLeg = 66;
        const byte SEND_KpTemperOUT = 67;
        const byte SEND_TiltZadAddNoManOneLeg = 68;
        const byte SEND_AutoPID_On_CntConst = 69;
        const byte SEND_UBatHi = 70;
        const byte SEND_KiTemperIN = 71;

        const byte SEND_KiTemperOUT = 72;
        const byte SEND_CopyProfiles = 73;
        const byte SEND_SensorTSTKeys = 74;
        //const byte SEND_TiltZadAddOneTwoLeg = 75;
        const byte SEND_ZeroThroottleOn = 76;
        const byte SEND_KpRotOneTwoLeg = 77;
        //const byte SEND_KiRotOneTwoLeg = 78;

        const byte SEND_PreasUpCntConst = 79;
        const byte SEND_PreasDnCntConst = 80;
        const byte SEND_ZeroThroottleOff = 81;
        const byte SEND_AutoPID_On_PWM = 82;
        const byte SEND_AutoPID_On_Speed = 83;

        const byte SEND_StrongModePIDOn = 84;
        const byte SEND_StrongModePIDOff = 85;
        //const byte SEND_StartRotFreshmanL = 86;
        //const byte SEND_TiltZadAddFreshman = 87;
        //const byte SEND_KRotFreshmanL = 88;
        const byte SEND_SmoothBreakOn = 89;
        const byte SEND_SmoothBreakOff = 90;
        const byte SEND_CurrUstSpd0 = 91;
        const byte SEND_CurrPhaseLimitSpd0 = 92;
        const byte SEND_CurrLimitSpd0 = 93;
        const byte SEND_MaxAngleStopBreak = 94;
        const byte SEND_SaveOptions1 = 95;
        const byte SEND_SaveOptionsProfile = 96;
        const byte SEND_DefaultOptions = 97;
        const byte SEND_BeepPauseConstAlm = 98;
        const byte SEND_BzOnCntSeriaConstAlm = 99;
        const byte SEND_CntSingleBeepAlm = 100;

        const byte SEND_DiffAlfaConstL = 101;
        const byte SEND_DiffAlfaConstH = 102;
        const byte SEND_Robowell = 103;
        const byte SEND_RobowellSpd = 104;
        const byte SEND_GetRobowell = 105;
        const byte SEND_GetRobowellSpd = 106;
        const byte SEND_CalibrCurr = 107;
        const byte SEND_ClearCurrentAH = 108;
        const byte SEND__3psnSwitchBtNotPressed = 109;
        const byte SEND__3psnSwitchBt3 = 110;
        const byte SEND__3psnSwitchBt4 = 111;
        const byte SEND_Options1 = 112;
        const byte SEND_TrmRqst = 113;
        const byte SEND_NoAutoTrmOn = 114;
        const byte SEND_NoAutoTrmOff = 115;
        const byte SEND_SetTmr1 = 116;
        const byte SEND_SetTmr2 = 117;
        const byte SEND_UseTmr = 118;
        const byte SEND_TmrLoudOn = 119;
        const byte SEND_TmrLoudOff = 120;
        const byte SEND_SerBynber = 121;

        //const byte SEND_But5Func = 122;
        //const byte SEND_KiOneTwoLeg_1 = 123;
        //const byte SEND_StartRotOneTwoLeg_1 = 124;
        const byte SEND_SensorlessCntAlignConst = 125;
        //const byte SEND_KRotOneTwoLeg_1 = 126;
        const byte SEND_KTemperatureSPDControl = 127;
        const byte SEND_TemperatureMaxIN_H = 128;
        const byte SEND_SensorlessSpdChngCntConst = 129;
        const byte SEND_SensorLessTimerConst2 = 130;
        const byte SEND_SenosrlessPWM1_2Const = 131;
        const byte SEND_SensorLessTimerConstMin = 132;
        const byte SEND_SensorllessSpdThreshold = 133;
        const byte SEND_Temperature3On = 134;
        const byte SEND_Temperature3Off = 135;
        const byte SEND_Temperature4On = 136;
        const byte SEND_Temperature4Off = 137;
        const byte SEND_Temperature5On = 138;
        const byte SEND_Temperature5Off = 139;
        const byte SEND_Temperature6On = 140;
        const byte SEND_Temperature6Off = 141;
        const byte SEND_TemperatureMaxOUT = 142;
        const byte SEND_TemperatureMaxIN = 143;
        const byte SEND_TemperatureTYPE = 144;
        const byte SEND_KpTemperIN = 145;
        const byte SEND_Profile = 146;
        //        const byte SEND_Key10_On = 147;
        //      const byte SEND_Key10_Off = 148;
        //const byte SEND_Key11_On = 149;
        //        const byte SEND_Key11_Off = 150;
        //        const byte SEND_Key12_On = 151;
        //        const byte SEND_Key12_Off = 152;
        //        const byte SEND_Key13_On = 153;
        //        const byte SEND_Key13_Off = 154;
        //        const byte SEND_Key14_On = 155;
        //        const byte SEND_Key14_Off = 156;
        //        const byte SEND_Key15_On = 157;
        //        const byte SEND_Key15_Off = 158;
        //        const byte SEND_Key16_On = 159;
        //        const byte SEND_Key16_Off = 160;
        const byte SEND_Options2 = 161;
        const byte SEND_BreakThresholdDn = 162;
        //const byte SEND_MAH = 163;
        const byte SEND_SensorThreshold = 164;
        const byte SEND_ManualStartOn = 165;
        const byte SEND_ManualStartOff = 166;
        //        const byte SEND_Balance2 = 167;
        const byte SEND_StopBalance2 = 168;
        //const byte SEND_Balance3 = 169;
        const byte SEND_StopBalance3 = 170;
        //const byte SEND_Balance4 = 171;
        const byte SEND_StopBalance4 = 172;
        //const byte SEND_TiltZadState5 = 173;
        //        const byte SEND_SpdRstSpeedLim = 174;
        const byte SEND_PWMControlOn = 175;
        const byte SEND_SpeedControlOn = 176;
        const byte SEND_XLimit = 177;
        const byte SEND_YLimit = 178;
        const byte SEND_BreakThresholdUp = 179;
        const byte SEND_MonocycleOn = 180;
        const byte SEND_MonocycleOff = 181;
        const byte SEND_BreakButtonMonocycleOn = 182;
        //        const byte SEND_SpeedLimitSt4 = 183;
        const byte SEND_ResetDistance = 184;
        //const byte SEND_TestVibroLROn = 185;
        const byte SEND_TestVibroLROff = 186;
        //const byte SEND_StopVibroOn = 187;
        const byte SEND_StopVibroOff = 188;
        const byte SEND_BreakButtonMonocycleOff = 189;
        const byte SEND_MonoStopDirectionOn = 190;
        const byte SEND_DirPWM1_0 = 191;
        const byte SEND_DirPWM1_1 = 192;
        const byte SEND_MaxSpdPID = 193;
        const byte SEND_DirBalance1 = 194;
        const byte SEND_DirBalance0 = 195;
        //        const byte SEND_ResetBMS_RAM = 196;
        const byte SEND_MonoStopDirectionOff = 197;
        const byte SEND_AlignmentON = 198;
        const byte BuzzAndHornOn = 199;
        const byte BuzzAndHornOff = 200;
        const byte DoNotTestBMSOn = 201;
        const byte DoNotTestBMSOff = 202;
        const byte SEND_GetOptionsSteer = 203;
        //const byte SEND_KGyroSteer = 204;
        const byte SEND_WriteEEPROMSteer = 205;
        const byte SEND_CalibrGyroSteer = 206;
        const byte SEND_AlignmentOff = 207;
        const byte SEND_ThreePositionSwitchOn = 208;
        const byte SEND_ThreePositionSwitchOff = 209;
        //        const byte SEND_KdOneTwoLeg = 210;
        //        const byte SEND_KdOneTwoLeg_1 = 211;
        //const byte SEND_KdFreshman = 212;
        //const byte SEND_Num_KdAverage = 213;
        const byte SEND_SensorThresholdUp = 214;
        const byte SEND_BreakInvBtnOn = 215;
        const byte SEND_BreakInvBtnOff = 216;
        const byte SEND_StrongModeOn = 217;
        const byte SEND_NormalMode = 218;
        const byte SEND_BreakThreshold = 219;
        const byte SEND_KFirstBreak = 220;
        const byte SEND_SensOrder2 = 221;
        const byte SEND_SensOrder1 = 222;
        //const byte SEND_Balance5 = 223;
        const byte SEND_StopBalance5 = 224;
        const byte SEND_SensorLessTimerConst = 225;

        const byte SEND_SensorlessON = 226;
        const byte SEND_SensorlessOff = 227;
        const byte SEND_SignalizaciaON = 228;
        const byte SEND_SignalizaciaOFF = 229;
        const byte SEND_FixPeriod = 230;
        const byte SEND_KpCurr = 231;
        const byte SEND_VectorTrapezoidaOn = 232;
        const byte SEND_VectorTrapezoidaOff = 233;
        //        const byte SEND_CurrLimII_On = 234;
        //      const byte SEND_CurrLimII_Off = 235;
        const byte SEND_KiCurr = 236;
        const byte SEND_CurrUst = 237;
        const byte SEND_ClbrHalls = 238;
        const byte SEND_PWM32BitsOn = 239;
        const byte SEND_PWM32BitsOff = 240;
        const byte SEND_Sensor2Threshold = 241;
        const byte SEND_Sensor2ThresholdUp = 242;
        const byte SEND_Unlock = 243;
        const byte SEND_GetOptionsWhenLock = 244;
        const byte SEND_lock = 245;
        const byte SEND_GetPhase = 247;
        const byte SEND_GetNeutral = 248;
        const byte SEND_MixedMode = 249;
        const byte SEND_CntMixedModeMax = 250;
        const byte SEND_MixedModeLevelOn = 251;
        const byte SEND_CurrMixed = 252;
        const byte SEND_MixedModeLevelOff = 253;
        const byte SEND_SecondCMD = 254;


        const byte SEND_SecondCMD_RotAlfaXResOn = 1;
        const byte SEND_SecondCMD_RotAlfaXResOff = 2;
        const byte SEND_TurnSignalOn = 3;
        const byte SEND_LightsTudaSudaOn = 4;
        const byte SEND_LightsTudaSudaOff = 5;
        const byte SEND_LightsStopMonoDirOn = 6;
        const byte SEND_LightsStopMonoDirOff = 7;
        const byte SEND_GyroZFlTurn = 8;
        const byte SEND_ThrottleTmpChngMem = 9;
        const byte SEND_SlowStartOn = 10;
        const byte SEND_SlowStartOff = 11;
        const byte SEND_AntiPoliceOn = 12;
        const byte SEND_AntiPoliceOff = 13;
        const byte SEND_SlowStrtSpd = 14;
        const byte SEND_AntiPolicePower = 15;
        const byte SEND_MixedModeSlowSpeedOffOn = 16;
        const byte SEND_MixedModeSlowSpeedOffOff = 17;
        const byte SEND_MixedModeSlowSpeed = 18;
        const byte SEND_MixedMode2 = 19;
        const byte SEND_Ki_PWM_Mode = 20;
        const byte SEND_PWM_ModeOn = 21;
        const byte SEND_PWM_ModeOff = 22;
        const byte SEND_PWM_Mode_ZeroThrottleOn = 23;
        const byte SEND_PWM_Mode_ZeroThrottleOff = 24;
        const byte SEND_Kp_PWM_Mode = 25;
        const byte SEND_SIN_MIDDLEOn = 26;
        const byte SEND_SIN_MIDDLEOff = 27;
        const byte SEND_InvSinOn = 28;
        const byte SEND_InvSinOff = 29;
        const byte SEND_CurrLimitSoundOn = 30;
        const byte SEND_CurrLimitSoundOff = 31;
        const byte SEND_CurrPhaseLimit = 32;
        const byte SEND_CurrSensor = 33;
        const byte SEND_DecreaseCurrentOn = 34;
        const byte SEND_DecreaseCurrentOff = 35;
        const byte SEND_Spd0TimerConst = 36;
        const byte SEND_FillCurrentMassOn = 37;
        const byte SEND_FillSinMassOn = 38;
        const byte SEND_FillMassOff = 39;
        const byte SEND_CW_CCW_AnyProfileOn = 40;
        const byte SEND_CW_CCW_AnyProfileOff = 41;
        const byte SEND_BuzzerOnOff = 42;
        const byte SEND_AutoNastroyka = 43;
        const byte SEND_AutoNastroyka_ConfirmMSG = 44;
        const byte SEND_SensorThresholdUp_OK = 45;
        const byte SEND_SensorThresholdUp_nOK = 46;
        const byte SEND_BreakThresholdUp_OK = 47;
        const byte SEND_BreakThresholdUp_nOK = 48;
        const byte SEND_FinishOptionsTune = 49;
        const byte SEND_StopAutoNastroyka = 50;
        const byte SEND_AutoNastroykaOK = 51;
        const byte SEND_HallDelay1MaxSPD_F = 52;
        const byte SEND_HallDelay1MaxSPD_B = 53;
        const byte SEND_HallDelayMaxSPD = 54;
        const byte SEND_KZPhasesOn = 55;
        const byte SEND_Mgnovenniy = 56;
        const byte SEND_KZ_Mgnovenniy_Off = 57;
        const byte SEND_PINCODE = 58;
        const byte SEND_BothBreaksOn = 59;
        const byte SEND_BothBreaksOff = 60;
        const byte SEND_GAZ_IMMITATOROn = 61;
        const byte SEND_GAZ_IMMITATOROff = 62;
        const byte SEND_GazImm = 63;
        const byte SEND_PINCODE_Unlock = 64;
        const byte SEND_RESET_PASSWORD = 65;
        const byte SEND_ChagerViaMotorOn = 66;
        const byte SEND_ChagerViaMotorOff = 67;
        const byte SEND_TrapezoidaWhenBigCurrentOn = 68;
        const byte SEND_TrapezoidaWhenBigCurrentOff = 69;
        const byte SEND_BigCurrent = 70;
        const byte SEND_ChagerCurr = 71;
        const byte SEND_P_Curr = 72;
        const byte SEND_I_Curr = 73;
        const byte SEND_P_U = 74;
        const byte SEND_I_U = 75;
        const byte SEND_X1 = 76;
        const byte SEND_2WDMaster = 77;
        const byte SEND_2WDSlave = 78;
        const byte SEND_JOYSTICKOn = 79;
        const byte SEND_JOYSTICKOff = 80;
        const byte SEND_JOYSTICKCalibrOn = 81;
        const byte SEND_JOYSTICKCalibrOff = 82;
        const byte SEND_CalibrateJOYSTICK = 83;
        const byte SEND_JoistickDeadZone = 84;
        const byte SEND_CHANGE_AXISOn = 85;
        const byte SEND_CHANGE_AXISOff = 86;
        const byte SEND_KpKp = 87;
        const byte SEND_IRFP4110On = 88;
        const byte SEND_IRFP4110Off = 89;
        const byte SEND_ThrottleLevelUpOff = 90;
        const byte SEND_LightMode = 91;
        const byte SEND_LightSensorThresholdLo = 92;
        const byte SEND_LightSensorThresholdHi = 93;
        const byte SEND_SaveOptionsFlashMass2 = 94;
        const byte SEND_Options3 = 95;
        const byte SEND_LightOnOn = 96;
        const byte SEND_LightOnOff = 97;
        const byte SEND_CurrentControlOnly = 98;
        const byte SEND_CurrentMaxCurrentOnly = 99;
        const byte SEND_K_PWM_Nastr = 100;
        const byte SEND_DEADTIME_Si8233 = 101;
        const byte SEND_OCP_DEG = 102;
        const byte SEND_VDS_LVL = 103;
        const byte SEND_CLR_FLT = 104;

        const byte SEND_Crr1Corr = 105;
        const byte SEND_ButtonBreakOnlyOn = 106;
        const byte SEND_ButtonBreakOnlyOff = 107;
        const byte SEND_ButtonBreakOnlyPWM = 108;
        const byte SEND_StpLightsOn = 109;
        const byte SEND_StpLightsOff = 110;
        const byte SEND_CntTurnOnConst = 111;
        const byte SEND_CntTurnOffConst = 112;

        const byte SEND_TemperatureTYPE_FETs = 113;
        const byte SEND_TEST_PWM_KEYSOn = 114;
        const byte SEND_TEST_PWM_KEYSOff = 115;
        const byte SEND_TstPhase = 116;
        const byte SEND_VerticalOn = 117;
        const byte SEND_VerticalOff = 118;
        const byte SEND_SpdStartLevel = 119;
        const byte SEND_Ki_PWM_ModeOff = 120;
        const byte SEND_StrongModeSpdFilterOffMem = 121;
        const byte SEND_StrongModeBreakOffOn = 122;
        const byte SEND_StrongModeMotorOffOn = 123;
        const byte SEND_StrongModeBreakOffModeMotorOffOff = 124;
        const byte SEND_RegenOff = 125;
        const byte SEND_KeyLightStopOn = 126;
        const byte SEND_KeyLightBrightness = 127;
        const byte SEND_KeyLightStopGabaritOn = 128;
        const byte SEND_MigStopOn = 129;
        const byte SEND_MigStopOff = 130;
        const byte SEND_AutoNastroyka_State30 = 131;
        const byte SEND_AutoNastroyka_State32 = 132;
        const byte SEND_AutoNastroyka_State27 = 133;
        const byte SEND_ButtonBreakOnlyTime = 134;
        const byte SEND_BreakMonocycleSpd = 135;
        const byte SEND_PWMkHz = 136;
        //        const byte SEND_PWM10kHzOff = 137;
        const byte SEND_LightsFromButtonOn = 138;
        const byte SEND_LightsFromButtonOff = 139;
        const byte SEND_KpKpDeadZoneMem = 140;
        const byte SEND_PWMSignal = 141;
        const byte SEND_KpSlowSpeed = 142;
        const byte SEND_SlowSpeedForKp = 143;
        const byte SEND_KiKp = 144;
        const byte SEND_KiKpDeadZone = 145;
        const byte SEND_KiMax = 146;
        const byte SEND_TimeDecreaseKi = 147;
        const byte SEND_KpKpMinusOn = 148;
        const byte SEND_KpKpMinusOff = 149;
        const byte SEND_KpMin = 150;
        const byte SEND_EpPWMmax = 151;
        const byte SEND_EiPWMmax = 152;
        const byte SEND_EdPWMmax = 153;
        const byte SEND_SegwayOn = 154;
        const byte SEND_SegwayOff = 155;
        const byte SEND_DeadZoneHandleBarSegway = 156;
        const byte SEND_KRotSegway = 157;
        const byte SEND_KpRotSegway = 158;
        const byte SEND_KiRotSegway = 159;
        const byte SEND_FindGyroVertical = 160;
        const byte SEND_HighSpeed = 161;
        const byte SEND_GoalSpeed = 162;
        const byte SEND_StartRotHighSpeed = 163;
        const byte SEND_KRotHighSpeed = 164;
        const byte SEND_GyroAccSameOffOn = 165;
        const byte SEND_GyroAccSameOffOff = 166;
        const byte SEND_HumanSensorOn = 167;
        const byte SEND_HumanSensorOff = 168;
        const byte SEND_TimeHumanSensorOff = 169;
        const byte SEND_KpKpZoneEnd = 170;
        const byte SEND_KpKp2 = 171;
        const byte SEND_KpKp2DeadZone = 172;
        const byte SEND_KpKp2ZoneEnd = 173;
        const byte SEND_PWMChangedOn = 174;
        const byte SEND_PWMChangedOff = 175;
        const byte SEND_PWMChangedThreshold = 176;
        const byte SEND_InvHallAOn = 177;
        const byte SEND_InvHallAOff = 178;
        const byte SEND_InvHallBOn = 179;
        const byte SEND_InvHallBOff = 180;
        const byte SEND_InvHallCOn = 181;
        const byte SEND_InvHallCOff = 182;
        const byte SEND_BreakFilterOn = 183;
        const byte SEND_BreakFilterOff = 184;
        const byte SEND_SpdKdMax = 185;
        const byte SEND_KdKpSpd = 186;
        const byte SEND_KdMax = 187;
        const byte SEND_KdMin = 188;
        const byte SEND_KiKd = 189;
        const byte SEND_VectorOnOffSpdLo = 190;
        const byte SEND_VectorOnOffSpdHi = 191;
        const byte SEND_TrapezoidaWhenBigSpeedOn = 192;
        const byte SEND_TrapezoidaWhenBigSpeedOff = 193;
        const byte SEND_I_PWMmaxSignalOn = 194;
        const byte SEND_I_PWMmaxSignalOff = 195;
        const byte SEND_OnDelay = 196;
        const byte SEND_KiUBTCoeff = 197;
        const byte SEND_SpdKiMin = 198;
        const byte SEND_KiMin = 199;
        const byte SEND_ELimitedMem = 200;
        const byte SEND_KdNoManR = 201;
        const byte SEND_DifferentKdOn = 202;
        const byte SEND_DifferentKdOff = 203;
        const byte SEND_KpDeadZone = 204;
        const byte SEND_StopIfPWM100Time = 205;
        const byte SEND_CntKdSwitchCONST = 206;
        const byte SEND_PWMSignalTimer = 207;
        const byte SEND_LogOn = 208;
        const byte SEND_LogOff = 209;

        const bool REV1 = false;
        const String Version = "4.06";//01.11.2020
        double CurrPerDigit = 111;//48.34;//64.45;//80.5664;//29.296;//14.648;

        int[] sine_array = new int[]/*{
	1,3,4,6,7,9,10,12,13,15,16,18,19,21,22,24,25,27,28,30,31,32,34,35,37,38,40,41,43,44,46,47,
	49,50,51,53,54,56,57,59,60,61,63,64,66,67,69,70,71,73,74,76,77,78,80,81,83,84,85,87,88,90,
	91,92,94,95,96,98,99,100,102,103,105,106,107,108,110,111,112,114,115,116,118,119,120,122,
	123,124,125,127,128,129,130,132,133,134,135,137,138,139,140,141,143,144,145,146,147,148,
	150,151,152,153,154,155,156,158,159,160,161,162,163,164,165,166,167,169,170,171,172,173,
	174,175,176,177,178,179,180,181,182,183,184,185,186,187,187,188,189,190,191,192,193,194,
	195,196,196,197,198,199,200,201,201,202,203,204,205,205,206,207,208,208,209,210,211,211,
	212,213,214,214,215,216,216,217,217,218,219,219,220,221,221,222,222,223,223,224,225,225,
	226,226,227,227,228,228,229,229,230,230,230,231,231,232,232,233,233,233,234,234,234,235,
	235,235,236,236,236,237,237,237,237,238,238,238,238,239,239,239,239,239,240,240,240,240,
	240,240,241,241,241,241,241,241,241,241,241,241,241,241,241,241
};*/
    /*{2, 6, 10, 15, 19, 23, 27, 31,
35, 39, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 99,103,107,111,115,118,121,124,
127,131,135,138,142,145,149,152,155,159,162,165,168,171,174,177,180,183,186,189,192,194,197,200,
202,205,207,210, 212,214,217,219,221,223,225,227,229,231,232,234,236,237,239,240,242,243,244,245,
247,248,249,250,250,251,252,253,253,254,254,255,255,255,255,255,255,255,255,255,255,255,254,254,
253,253,252,252,251,250,249,248,247,246,245,244,242,241,240,238,237,235,233,232,230,228,226,224,
222,222,225,226,228,230,232,234,235,237,238,240,241,243,244,245,246,247,248,249,250,251,252,252,
253,254,254,254,255,255,255,255,255,255,255,255,255,255,254,254,254,253,252,252,251,250,249,248,
247,246,245,244,243,241,240,238,237,235,234,232,230,228,227,225,223,220,218,216,214,212,209,207,
204,202,199,197,194,191,188,185,183,180,177,174,171,167,164,161,158,154,151,148,144,141,137,134,
130,127,123,119,116,112,108,104,101, 97, 93, 89, 85, 81, 77, 73, 69, 65, 61, 57, 53, 49, 45, 41,
36, 32, 28, 24, 20, 16, 12, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        */
    {0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0, 0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


        int[] sine_Res = new int[384];


        const byte PACKETSIZE = 10;
        public Form1()
        {

            if (!String.IsNullOrEmpty(Properties.Settings.Default.Language))
            {
                ////                System.Threading.Thread.CurrentThread.CurrentUICulture = System.Globalization.CultureInfo.GetCultureInfo("en-US");
                ////                System.Threading.Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.GetCultureInfo("en-US");
                System.Threading.Thread.CurrentThread.CurrentUICulture = System.Globalization.CultureInfo.GetCultureInfo(Properties.Settings.Default.Language);
                System.Threading.Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.GetCultureInfo(Properties.Settings.Default.Language);
            }


            InitializeComponent();
            backgroundWorker1.RunWorkerAsync();//numberToCompute );
            FirstTime = 0;
            s = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            ShowSer = 1;
            MovingON = 0;

            string Host = System.Net.Dns.GetHostName();
            //thisIP = 
            IPAddress[] IPs = System.Net.Dns.GetHostByName(Host).AddressList;

            for (int i = 0; i < System.Net.Dns.GetHostByName(Host).AddressList.Length; i++)
            {
                //comboBox6.Items.Add(IPs[i]);
                //comboBox6.SelectedIndex = 0;
            }




            //            label16.Text = thisIP.ToString();

            SaveTimeOut = 0;
            TmrLocked = 0;
            OdometrMem = 0;

            F2 = new Form2(new MyDelegate(func));
            F2.Owner = this;
            _9 = new int[PACKETSIZE];
            _10 = new int[PACKETSIZE];
            _11 = new short[PACKETSIZE];
            _12 = new int[PACKETSIZE];
            _13 = new int[PACKETSIZE];
            _14 = new int[PACKETSIZE];
            _15 = new short[PACKETSIZE];
            _16 = new int[PACKETSIZE];
            TiltXMass = new int[PACKETSIZE];
            TiltYMass = new short[PACKETSIZE];
            GyroXMass = new short[PACKETSIZE];
            GyroYMass = new short[PACKETSIZE];

            PWMMass = new short[PACKETSIZE];
            EpMass = new int[PACKETSIZE];
            EdMass = new float[PACKETSIZE];
            EiMass = new float[PACKETSIZE];
            CntPacketsMass = new int[PACKETSIZE];

            radioButton7CannotSndCMD = false;
            radioButton10CannotSndCMD = radioButton11CannotSndCMD = radioButton12CannotSndCMD = false;
            radioButton25CannotSndCMD = radioButton26CannotSndCMD = radioButton27CannotSndCMD = false;





            CntTST = 0;

            comboBox18.SelectedIndex = 0;


            comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 0;
            comboBox5.SelectedIndex = 0;

            COMPorts();
            //comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 8;
            comboBox5.SelectedIndex = 31;

            /*
            if (REV1)
            {
                CurrPerDigit = 128;
                comboBox1.Items.Clear();
                comboBox1.Items.Add("0A");
                comboBox1.Items.Add("16.5A");
                comboBox1.Items.Add("33A");
                comboBox1.Items.Add("49.5A");
                comboBox1.Items.Add("66A");
                comboBox1.Items.Add("82.5A");
                comboBox1.Items.Add("99A");
                comboBox1.Items.Add("115.5A");
                comboBox1.Items.Add("132A");
            }



            if (CurrPerDigit == 48.34)
            {
                comboBox1.Items.Clear();
                comboBox1.Items.Add("26A");
                comboBox1.Items.Add("34A");
                comboBox1.Items.Add("42A");
                comboBox1.Items.Add("50A");
                comboBox1.Items.Add("58A");
                comboBox1.Items.Add("65A");
                comboBox1.Items.Add("74A");
                comboBox1.Items.Add("81A");
                comboBox1.Items.Add("89A");
                comboBox1.Items.Add("97A");
                comboBox1.Items.Add("104A");
                comboBox1.Items.Add("113A");
                comboBox1.Items.Add("120A");
                comboBox1.Items.Add("128A");
                comboBox1.Items.Add("136A");

                comboBox19.Items.Clear();
                comboBox19.Items.Add("26A");
                comboBox19.Items.Add("34A");
                comboBox19.Items.Add("42A");
                comboBox19.Items.Add("50A");
                comboBox19.Items.Add("58A");
                comboBox19.Items.Add("65A");
                comboBox19.Items.Add("74A");
                comboBox19.Items.Add("81A");
                comboBox19.Items.Add("89A");
                comboBox19.Items.Add("97A");
                comboBox19.Items.Add("104A");
                comboBox19.Items.Add("113A");
                comboBox19.Items.Add("120A");
                comboBox19.Items.Add("128A");
                comboBox19.Items.Add("136A");



            }
            */
            //label654.Text =  "н\nа\nз\nв\nа\nн\nи\nе\n \nо\nс\nи\n";

        }

        void func(int param)
        {
            switch (param)
            {
                case 1:

                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_AutoNastroyka_ConfirmMSG;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();

                    break;
                case 2:

                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_SensorThresholdUp_OK;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();

                    break;
                case 3:

                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_SensorThresholdUp_nOK;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();

                    break;
                case 4:

                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_BreakThresholdUp_OK;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();

                    break;
                case 5:

                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_BreakThresholdUp_nOK;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();

                    break;

                case 6:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_FinishOptionsTune;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                    break;

                case 7:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_StopAutoNastroyka;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                    break;



                case 8:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_AutoNastroyka;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                    break;

                case 9:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_AutoNastroykaOK;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                    break;

                case 10:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_AutoNastroyka_State30;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                    break;

                case 11:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_AutoNastroyka_State32;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                    break;
                case 12:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_AutoNastroyka_State27;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                    break;



                case 13:
                    chart1.Series[0].Points.Clear();
                    chart1.Series[1].Points.Clear();
                    break;

                case 14:
                    chart1.Series[0].Points.Clear();
                    chart1.Series[1].Points.Clear();
                    comboBox3.SelectedIndex = 0;
                    //           comboBox4.SelectedIndex = 21;
                    break;





            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                //byte[] sendbuf = new byte[4];

                sendbuf[0] = SEND_StrtPOS;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_StrtPOS;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }


        private unsafe void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            //int listenPort = 51722;
            short* TmpShort;
            int* TmpInt;
            uint* TmpUInt;
            float* TmpFloat;
            byte* TmpByte;
            byte Cmd;
            int i = 0;
            ushort* TmpUShort;

            //          UdpClient listener = new UdpClient(listenPort);
            //        IPEndPoint groupEP = new IPEndPoint(IPAddress.Any, listenPort);

            while (true)
            {
                Thread.Sleep(1);

                //short *ss=new short;

                //byte[] bytes =  listener.Receive(ref groupEP);

                i = 0;

                fixed (byte* p = &bytes[i])
                {                                   //Cmd
                    TmpByte = p;
                    i = i + sizeof(byte);
                    Cmd = *TmpByte;
                }

                Cmd = 0;
                switch (Cmd)
                {
                    case 1:

                        fixed (byte* p = &bytes[i])
                        {                                   //CntPosConst
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            CntPosConst = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //CntPackets
                            TmpInt = (int*)p;
                            i = i + sizeof(int);
                            CntPackets = *TmpInt;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //TiltYRes
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            TiltYRes = *TmpShort;
                        }




                        fixed (byte* p = &bytes[i])
                        {                                   //E
                            TmpInt = (int*)p;
                            i = i + sizeof(int);
                            E = *TmpInt;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //Ep
                            TmpInt = (int*)p;
                            i = i + sizeof(int);
                            Ep = *TmpInt;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //Kp
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            Kp = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //Ed
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            Ed = *TmpFloat;
                        }



                        fixed (byte* p = &bytes[i])
                        {                                   //Gyro4Y       ??????
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            Gyro4Y = *TmpShort;
                        }



                        fixed (byte* p = &bytes[i])
                        {                                   //Kd
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            Kd = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //ESumm
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            ESumm = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //Ei
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            Ei = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //Ki
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            Ki = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //PWMResR
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            PWMResR = *TmpShort;
                        }



                        fixed (byte* p = &bytes[i])
                        {                                   //PWMResL
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            PWMResL = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //CntImpR
                            TmpInt = (int*)p;
                            i = i + sizeof(int);
                            CntImpR = *TmpInt;
                        }



                        fixed (byte* p = &bytes[i])
                        {                                   //CntImpL
                            TmpInt = (int*)p;
                            i = i + sizeof(int);
                            CntImpL = *TmpInt;
                        }





                        fixed (byte* p = &bytes[i])
                        {                                   //EpPos
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            EpPos = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //EPos
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            EPos = *TmpFloat;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //KpPos
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            KpPos = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //EPosPrev
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            EPosPrev = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //EdPos
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            EdPos = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //KdPos
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            KdPos = *TmpShort;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //EPosSumm
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            EPosSumm = *TmpFloat;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //EiPos
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            EiPos = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //KiPos
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            KiPos = *TmpShort;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //Angle
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            Angle = *TmpFloat;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //AngleLimit
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            AngleLimit = *TmpShort;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //CntUDPTrmConst
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            CntUDPTrmConst = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //Ediff
                            TmpInt = (int*)p;
                            i = i + sizeof(int);
                            Ediff = *TmpInt;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //T
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            T = *TmpFloat;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //Tj
                            TmpFloat = (float*)p;
                            i = i + sizeof(float);
                            Tj = *TmpFloat;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //PWMRotR
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            PWMRotR = *TmpShort;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //PWMRotL
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            PWMRotL = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //TiltZad
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            TiltZad = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //TiltCorr
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            TiltCorr = *TmpShort;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //Speed
                            TmpUInt = (uint*)p;
                            i = i + sizeof(uint);
                            Speed = *TmpUInt;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //CntTilt
                            TmpUInt = (uint*)p;
                            i = i + sizeof(uint);
                            CntTilt = *TmpUInt;
                        }


                        fixed (byte* p = &bytes[i])
                        {                                   //RudderToSend
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            RudderToSend = *TmpShort;
                        }

                        fixed (byte* p = &bytes[i])
                        {                                   //PWMResL
                            TmpShort = (short*)p;
                            i = i + sizeof(short);
                            PWMResL = *TmpShort;
                        }




                        backgroundWorker1.ReportProgress(1);
                        break;


                    case 2:

                        int l;
                        for (l = 0; l < PACKETSIZE; l++)
                        {

                            fixed (byte* p = &bytes[i])
                            {                                   //CntPackets
                                TmpInt = (int*)p;
                                i = i + sizeof(int);
                                CntPacketsMass[l] = *TmpInt;
                            }


                            fixed (byte* p = &bytes[i])
                            {                                   //TiltXMass
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                TiltXMass[l] = *TmpShort;




                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //TiltYMass
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                TiltYMass[l] = *TmpShort;
                            }




                            fixed (byte* p = &bytes[i])
                            {                                   //GyroXMass
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                GyroXMass[l] = *TmpShort;
                            }


                            fixed (byte* p = &bytes[i])
                            {                                   //GyroYMass
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                GyroYMass[l] = *TmpShort;
                            }



                            fixed (byte* p = &bytes[i])
                            {                                   //EpMass
                                TmpInt = (int*)p;
                                i = i + sizeof(int);
                                EpMass[l] = *TmpInt;
                            }


                            fixed (byte* p = &bytes[i])
                            {                                   //EdMass
                                TmpFloat = (float*)p;
                                i = i + sizeof(float);
                                EdMass[l] = *TmpFloat;
                            }



                            fixed (byte* p = &bytes[i])
                            {                                   //EiMass
                                TmpFloat = (float*)p;
                                i = i + sizeof(float);
                                EiMass[l] = *TmpFloat;
                            }


                            fixed (byte* p = &bytes[i])
                            {                                   //PWMMass
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                PWMMass[l] = *TmpShort;
                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //_9  (Curr1)
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                _9[l] = (int)(*TmpShort);// (int)(((int)*TmpShort) - 528);
                                //float Tg = ((float)_9[l]) * (float)56.8;
                                //_9[l] = (int)Tg;


                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //_10  (Curr2)
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                _10[l] = (int)(*TmpShort);//(int)(((int)*TmpShort) - 388);
                                //float Tg = ((float)_10[l]) *(float)77.3;
                                //_10[l] = (int)Tg;
                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //_11   PWM2
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                _11[l] = *TmpShort;
                            }

                            uint iu;

                            fixed (byte* p = &bytes[i])
                            {                                    //_12  (Spd1)
                                //iu = (uint)(short*)p;
                                TmpUShort = (ushort*)p;
                                iu = (uint)*TmpUShort;

                                i = i + sizeof(short);

                                //_12[l] = *TmpShort;
                                //   float Tg = ((float)_12[l]) * (float)0.327818;
                                //  _12[l] = (int)Tg;
                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //_13   (Spd2)
                                TmpUShort = (ushort*)p;
                                Odometr = (uint)*TmpUShort;
                                Odometr = Odometr * 256 * 256 + iu;

                                i = i + sizeof(short);
                                //_13[l] = *TmpShort;
                                //float Tg = ((float)_13[l]) * (float)0.327818;
                                //_13[l] = (int)Tg;
                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //_14   (SpdAv)
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                _14[l] = *TmpShort;
                                float Tg = ((float)_14[l]) * (float)0.3606;//0.31464;
                                _14[l] = (int)Tg;
                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //_15
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                _15[l] = *TmpShort;
                            }

                            fixed (byte* p = &bytes[i])
                            {                                   //_16 (UBAT)
                                TmpShort = (short*)p;
                                i = i + sizeof(short);
                                _16[l] = (int)*TmpShort;

                                float Tg = ((float)_16[l]) * (float)0.21097;
                                _16[l] = (int)Tg;
                            }

                        }

                        CntTST++;

                        backgroundWorker1.ReportProgress(2);
                        break;
                    case 3:

                        int Tm;

                        Tm = bytes[3];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[2];
                        KpMustBe = Tm;

                        Tm = bytes[5];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[4];
                        KpNoMan = Tm;

                        Tm = bytes[7];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[6];
                        KdI = Tm;

                        Tm = bytes[9];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[8];
                        KiNoMan = Tm;

                        Tm = bytes[11];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[10];
                        TiltYCorr = (short)Tm;


                        Tm = bytes[13];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[12];
                        SpeedAdd = Tm;


                        Tm = bytes[15];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[14];
                        KGYRO = Tm;

                        Tm = bytes[17];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[16];
                        Kpx = Tm;

                        Tm = bytes[19];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[18];
                        TiltXSteerCorr = Tm;

                        Tm = bytes[21];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[20];
                        SensorLessTimerConstMin = (ushort)Tm;

                        Tm = bytes[23];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[22];
                        CalibrationGyroX = (short)Tm;

                        Tm = bytes[25];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[24];
                        CalibrationGyroY = (short)Tm;

                        Tm = bytes[27];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[26];
                        CalibrationGyroZ = (short)Tm;


                        Tm = bytes[29];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[28];
                        CalibrationAccX = (short)Tm;

                        Tm = bytes[31];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[30];
                        CalibrationAccY = (short)Tm;

                        Tm = bytes[33];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[32];
                        CalibrationAccZ = (short)Tm;

                        Tm = bytes[35];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[34];
                        KRot = Tm;

                        Tm = bytes[37];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[36];
                        StartRot = Tm;

                        Tm = bytes[39];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[38];
                        KpRot = Tm;


                        Tm = bytes[41];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[40];
                        KFilterPrev = Tm;

                        Tm = bytes[43];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[42];
                        CurrLimit = Tm;

                        Tm = bytes[45];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[44];
                        KiRot = Tm;


                        Tm = bytes[47];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[46];
                        KpSPDReal = Tm;

                        Tm = bytes[49];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[48];
                        KdSPD = Tm;


                        Tm = bytes[51];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[50];
                        KiSPD = Tm;

                        Tm = bytes[53];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[52];
                        AngleLimitInt = Tm;

                        Tm = bytes[55];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[54];
                        SpeedLimit1 = Tm;

                        Tm = bytes[57];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[56];
                        StatFlags = Tm;

                        Tm = bytes[59];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[58];
                        XLimit = Tm;

                        Tm = bytes[61];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[60];
                        YLimit = Tm;


                        Tm = bytes[63];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[62];
                        UBatLow = Tm;

                        Tm = bytes[65];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[64];
                        KpBack = Tm;


                        Tm = bytes[67];
                        Tm = Tm << 8;
                        Tm = Tm + bytes[66];
                        TiltBackLimit = Tm;

                        SpeedLimit2 = bytes[68];
                        SpeedLimit3 = bytes[69];
                        NumSpeedLimit = bytes[70];

                        /*
               Tm = bytes[72];
               Tm=Tm<<8;
               Tm = Tm + bytes[71];
               KpMustBeMax = Tm;

               Tm = bytes[74];
               Tm=Tm<<8;
               Tm = Tm + bytes[73];
               KpSpeed = Tm;

               CntKpMustBe = bytes[75];

               SpdKpMax = bytes[76];
                        */
                        backgroundWorker1.ReportProgress(3);





                        break;

                    case 4:
                        Sensor1Snd = bytes[1];

                        uint Tt;
                        Tt = bytes[2];
                        Tt = Tt << 8;
                        Tt = Tt + bytes[1];
                        Distance = (uint)((float)Tt * 1);// 0.874);


                        ErrOptions = bytes[5];

                        i = 6;

                        fixed (byte* p = &bytes[i])
                        {
                            TmpFloat = (float*)p;
                            AlfaXResErr = *TmpFloat;
                            i = i + sizeof(float);

                        }

                        fixed (byte* p = &bytes[i])
                        {
                            TmpFloat = (float*)p;
                            AlfaYResErr = *TmpFloat;
                            i = i + sizeof(float);

                        }


                        fixed (byte* p = &bytes[i])
                        {
                            TmpFloat = (float*)p;
                            SteerXErr = *TmpFloat;
                            i = i + sizeof(float);

                        }


                        fixed (byte* p = &bytes[i])
                        {
                            TmpFloat = (float*)p;
                            SteerYErr = *TmpFloat;
                            i = i + sizeof(float);

                        }

                        ErrorCode = bytes[i];
                        i++;

                        NoBalanceCode = bytes[i];
                        i++;

                        fixed (byte* p = &bytes[i])
                        {
                            TmpUInt = (uint*)p;
                            FlgsErr = *TmpUInt;
                            i = i + sizeof(float);

                        }

                        fixed (byte* p = &bytes[i])
                        {
                            TmpUInt = (uint*)p;
                            Flgs1Err = *TmpUInt;
                            i = i + sizeof(float);

                        }


                        backgroundWorker1.ReportProgress(4);



                        break;




                }


            }




        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {


            switch (e.ProgressPercentage)
            {

                case 10:
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 1;//N
                    TrmMass[3] = SEND_SaveOptionsProfile;
                    TrmMass[4] = CalcCheckSummTrm();
                    Trm();

                    break;
                case 11:


                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_SaveOptionsFlashMass2;
                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();



                    break;



                case 17:


                    for (int k = 0; k < 1024; k++)
                        w.WriteByte(SaveOptionsMass[k]);
                    w.Flush();
                    w.Close();
                    MessageBox.Show(MyStrings.OptionsSaved, MyStrings.Inform, MessageBoxButtons.OK);

                    break;


                case 18:

                    TimeOutLoadOptions2 = 0;
                    MessageBox.Show(MyStrings.OptionsLoaded, MyStrings.Inform, MessageBoxButtons.OK);


                    break;











                case 12:
                    int Cnt, Tm, r;
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;

                    TrmMass[3] = SEND_Options2;
                    Cnt = 4;
                    Tm = SaveOptionsMass[0] + 2 + SaveOptionsMass[SaveOptionsMass[0] + 2] + 1;
                    for (r = SaveOptionsMass[0] + 2; r < Tm; r++)
                    {
                        TrmMass[Cnt++] = (byte)SaveOptionsMass[r];
                    }

                    TrmMass[2] = (byte)(Cnt - 3);

                    TrmMass[Cnt++] = CalcCheckSummTrm();
                    Trm();
                    TimeOutLoadOptions1 = 0;
                    TimeOutLoadOptions2 = 40;
                    break;

                case 13:
                    int TmStrt;
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_Options3;
                    Cnt = 5;
                    TmStrt = SaveOptionsMass[0] + 2 + SaveOptionsMass[SaveOptionsMass[0] + 2] + 2;
                    for (r = TmStrt; r <= TmStrt + SaveOptionsMass[TmStrt]; r++)
                    {
                        TrmMass[Cnt++] = (byte)SaveOptionsMass[r];
                    }

                    TrmMass[2] = (byte)(Cnt - 3);

                    TrmMass[Cnt++] = CalcCheckSummTrm();
                    Trm();
                    TimeOutLoadOptions1 = 0;
                    TimeOutLoadOptions2 = 40;

                    break;
                case 14:
                    TimeOutLoadOptions2 = 0;
                    //if (TmrLocked == 0)
                    //{
                    //    DialogResult result = MessageBox.Show(
                    //"Разблокировать контроллер?",
                    //"Контроллер заблокирован", MessageBoxButtons.YesNo,
                    //MessageBoxIcon.Error, MessageBoxDefaultButton.Button2);
                    //    if (result == DialogResult.Yes)
                    //    {
                    //        TrmMass[0] = 0xff;
                    //        TrmMass[1] = 0xff;
                    //        TrmMass[2] = 13;//N
                    //        TrmMass[3] = SEND_Unlock;

                    //        TrmMass[4] = 0x37;
                    //        TrmMass[5] = 0xac;
                    //        TrmMass[6] = 0x2b;
                    //        TrmMass[7] = 0x33;
                    //        TrmMass[8] = 0xf1;
                    //        TrmMass[9] = 0x91;
                    //        TrmMass[10] = 0x7a;
                    //        TrmMass[11] = 0xb0;
                    //        TrmMass[12] = 0xec;
                    //        TrmMass[13] = 0x46;
                    //        TrmMass[14] = 0x10;
                    //        TrmMass[15] = 0xaa;


                    //        TrmMass[16] = CalcCheckSummTrm();
                    //        Trm();
                    //    }
                    //}

                    break;

                case 22:

                    break;

                case 200:

                    if (PacketRec[15] != 0)
                        PacketRec[15] = 0;
                    uint tm = ((uint)PacketRec[15]) << 16;
                    tm = tm + ((uint)PacketRec[14]) << 8;
                    tm = tm + ((uint)PacketRec[13]);

                    break;


                case 1:

                    label11.Text = Kp.ToString();
                    label23.Text = Ki.ToString();

                    label57.Text = Tj.ToString();




                    if (FirstTime == 0)
                    {
                        FirstTime = 1;

                        numericUpDown2.Value = Kp;

                        numericUpDown4.Value = Ki;
                        numericUpDown10.Value = (int)(Tj * 100);
                    }
                    break;
                case 2:
                    //label11.Text = KpFl.ToString();
                    //label17.Text = KdFl.ToString();
                    //label59.Text = KEtmp.ToString();
                    //label57.Text = KRot.ToString();
                    if (ShowSer == 1)
                    {


                        int l;
                        for (l = 0; l < PACKETSIZE; l++)
                        {
                            Prorez++;
                            if (Prorez == 1)
                            {
                                Prorez = 0;
                                label110.Text = Odometr.ToString();

                            }
                        }


                    }
                    break;
                case 3:
                    label11.Text = KpNoMan.ToString();
                    label23.Text = KiNoMan.ToString();
                    label57.Text = KGYRO.ToString();


                    label82.Text = CalibrationGyroX.ToString();
                    label84.Text = CalibrationGyroY.ToString();
                    label88.Text = CalibrationGyroZ.ToString();
                    label90.Text = CalibrationAccX.ToString();
                    label92.Text = CalibrationAccY.ToString();
                    label94.Text = CalibrationAccZ.ToString();


                    label46.Text = StatFlags.ToString();

                    label40.Text = YLimit.ToString();
                    label34.Text = XLimit.ToString();
                    label56.Text = UBatLow.ToString();
                    label560.Text = UBatHi.ToString();




                    label206.Text = KpNoManOneLeg.ToString();
                    label198.Text = TiltZadAddNoManOneLeg.ToString();
                    label194.Text = KiNoManOneLeg.ToString();

                    label222.Text = Diametr1.ToString();
                    label224.Text = PhasesPerRev1.ToString();

                    label634.Text = CurrPhaseLimitSpd0.ToString();
                    label640.Text = Spd0TimerConst.ToString();
                    label685.Text = BigCurrent.ToString();

                    label777.Text = Crr1Corr.ToString();
                    label794.Text = SpdStartLevel.ToString();


                    label778.Text = ButtonBreakOnlyPWM.ToString();
                    label809.Text = ButtonBreakOnlyTime.ToString();


                    label811.Text = BreakMonocycleSpd.ToString();




                    label610.Text = K_PWM_Nastr.ToString();



                    label676.Text = KdMem.ToString();
                    label713.Text = KpKpMustBe.ToString();
                    label715.Text = ThrottleLevelUpOff.ToString();
                    label725.Text = DEADTIME_Si8233.ToString();

                    label894.Text = OnDelay.ToString();

                    label896.Text = KiUBTCoeff.ToString();




                    label632.Text = CurrPhaseLimit.ToString();
                    if (CurrSensor < comboBox18.Items.Count)
                        comboBox18.SelectedIndex = CurrSensor;




                    label231.Text = BeepPauseConstAlm.ToString();
                    label76.Text = BzOnCntSeriaConstAlm.ToString();
                    label5.Text = CntSingleBeepAlm.ToString();

                    label237.Text = DiffAlfaConstL.ToString();
                    label234.Text = DiffAlfaConstH.ToString();

                    label259.Text = Timer1Mem.ToString();
                    label257.Text = Timer2Mem.ToString();






                    label333.Text = SensorThreshold.ToString();

                    label396.Text = SensorThresholdUp.ToString();

                    label400.Text = KFirstBreak.ToString();

                    label398.Text = BreakThreshold.ToString();

                    if (SensOrder1 <= comboBox8.Items.Count)//MaxLength)
                        comboBox8.SelectedIndex = SensOrder1;







                    label636.Text = CurrUstSpd0.ToString();



                    label792.Text = String.Format("{0:0.00}", CurrPerDigit);

                    label571.Text = KpCurr.ToString();
                    label468.Text = KiCurr.ToString();
                    label466.Text = CurrUst.ToString();
                    label487.Text = SensorlessCurrUst.ToString();
                    label490.Text = SenosrlessPWM1_1Const.ToString();
                    label493.Text = SensorlessCntAlignConst.ToString();
                    label495.Text = SensorLessTimerConst.ToString();
                    label497.Text = SensorlessSpdChngCntConst.ToString();
                    label499.Text = SensorLessTimerConst2.ToString();
                    label501.Text = SenosrlessPWM1_2Const.ToString();
                    label503.Text = SensorLessTimerConstMin.ToString();
                    label505.Text = SensorllessSpdThreshold.ToString();

                    label507.Text = SerNumber.ToString();
                    label509.Text = SerNumber.ToString();


                    label516.Text = String.Format("{0:0.0}", TemperatureMaxOUT / 10);
                    label518.Text = String.Format("{0:0.0}", TemperatureMaxIN / 10);
                    label629.Text = String.Format("{0:0.0}", TemperatureMaxOUT_H / 10);
                    label627.Text = String.Format("{0:0.0}", TemperatureMaxIN_H / 10);


                    label523.Text = KpTemperIN.ToString();
                    label525.Text = KiTemperIN.ToString();

                    label531.Text = KpTemperOUT.ToString();
                    label533.Text = KiTemperOUT.ToString();
                    label704.Text = JoistickDeadZone.ToString();
                    label706.Text = JoystickCalibrX.ToString();
                    label708.Text = JoystickCalibrY.ToString();

                    label528.Text = Profile.ToString();

                    label855.Text = DeadZoneHandleBarSegway.ToString();
                    label857.Text = KRotMustBe.ToString();
                    label852.Text = KpRotMustBe.ToString();
                    label843.Text = KiRotMustBe.ToString();

                    label848.Text = HighSpeed.ToString();
                    label844.Text = GoalSpeed.ToString();
                    label861.Text = StartRotHighSpeed.ToString();
                    label863.Text = KRotHighSpeed.ToString();

                    label850.Text = TimeHumanSensorOff.ToString();


                    label884.Text = SpdKdMax.ToString();
                    label883.Text = KdKpSpd.ToString();


                    label886.Text = KdMax.ToString();
                    label888.Text = KdMin.ToString();

                    label890.Text = KiKd.ToString();

                    label900.Text = SpdKiMin.ToString();
                    label902.Text = KiMin.ToString();

                    label904.Text = ELimitedMem.ToString();



                    switch (GyroVertical)
                    {
                        case 0:
                            label841.Text = "Not found";
                            break;
                        case 1:
                            label841.Text = "Gyro X";
                            break;
                        case 2:
                            label841.Text = "Gyro Y";
                            break;
                        case 3:
                            label841.Text = "Gyro Z";
                            break;
                    }





                    //if ((StatFlgs4 & 0x0008) == 0x0008)
                    //    checkBox100.Checked = true;
                    //else
                    //    checkBox100.Checked = false;





                    if (TemperatureTYPE_FETs <= (byte)comboBox23.Items.Count)
                        comboBox23.SelectedIndex = TemperatureTYPE_FETs;

                    if (TemperatureTYPE <= comboBox15.Items.Count)
                        comboBox15.SelectedIndex = TemperatureTYPE;
                    if (LightMode <= comboBox20.MaxLength)
                        comboBox20.SelectedIndex = LightMode;
                    label722.Text = LightSensorThresholdLo.ToString();
                    label719.Text = LightSensorThresholdHi.ToString();
                    label723.Text = CurrentMaxCurrentOnly.ToString();

                    label781.Text = CntTurnOffConst.ToString();
                    label783.Text = CntTurnOnConst.ToString();

                    label808.Text = KeyLightBrightness.ToString();

                    label911.Text = StopIfPWM100Time.ToString();




                    label815.Text = KpKpDeadZoneMem.ToString();
                    label822.Text = KpSlowSpeed.ToString();
                    label819.Text = SlowSpeedForKp.ToString();

                    label864.Text = KpKpZoneEnd.ToString();
                    label867.Text = KpKp2.ToString();
                    label870.Text = KpKp2DeadZone.ToString();
                    label868.Text = KpKp2ZoneEnd.ToString();


                    switch (PWMkHz)
                    {
                        case 1:
                            comboBox25.SelectedIndex = 0;
                            break;
                        case 2:
                            comboBox25.SelectedIndex = 1;
                            break;
                        case 3:
                            comboBox25.SelectedIndex = 2;
                            break;
                        default:
                            comboBox25.SelectedIndex = -1;

                            break;
                    }



                    label825.Text = KiKpMustBe.ToString();
                    label824.Text = KiKpDeadZoneMem.ToString();
                    label829.Text = KiMax.ToString();
                    label831.Text = TimeDecreaseKi.ToString();
                    label833.Text = KpMin.ToString();

                    label835.Text = EpPWMmax.ToString();
                    label837.Text = EiPWMmax.ToString();
                    label839.Text = EdPWMmax.ToString();

                    label907.Text = KdNoManR.ToString();
                    label914.Text = CntKdSwitchCONST.ToString();
                    label915.Text = PWMSignalTimer.ToString();



                    label909.Text = KpDeadZone.ToString();



                    label570.Text = CntMixedModeMax.ToString();
                    label568.Text = MixedModeLevelOn.ToString();
                    label566.Text = CurrMixed.ToString();
                    label575.Text = MixedModeLevelOff.ToString();

                    label584.Text = SpdKpMax.ToString();

                    if (_2WDMode == 0)
                    {
                        radioButton21.Checked = false;
                        radioButton20.Checked = false;
                        radioButton19.Checked = true;
                    }

                    if (_2WDMode == 1)
                    {
                        radioButton21.Checked = true;
                        radioButton20.Checked = false;
                        radioButton19.Checked = false;
                    }

                    if (_2WDMode == 2)
                    {
                        radioButton21.Checked = false;
                        radioButton20.Checked = true;
                        radioButton19.Checked = false;
                    }














                    label579.Text = BreakThresholdDn.ToString();
                    label581.Text = BreakThresholdUp.ToString();

                    label586.Text = KpMax.ToString();
                    label588.Text = KpKpSpd.ToString();
                    label604.Text = MaxAngleStopBreak.ToString();
                    label583.Text = GyroZFlTurn.ToString();
                    label818.Text = PWMSignal.ToString();


                    label593.Text = ThrottleTmpChngMem.ToString();



                    label591.Text = SlowStrtSpd.ToString();
                    label595.Text = AntiPolicePower.ToString();


                    label617.Text = KTemperatureSPDControl.ToString();
                    label609.Text = KTemperatureSPDControl.ToString();
                    label611.Text = MixedModeSlowSpeed.ToString();

                    label615.Text = Ki_PWM_Mode.ToString();
                    label798.Text = Ki_PWM_ModeOff.ToString();
                    label800.Text = StrongModeSpdFilterOffMem.ToString();
                    label804.Text = RegenOffMem.ToString();





                    label620.Text = Kp_PWM_Mode.ToString();

                    //label426.Text = String.Format("{0:0.0}", UBT) + " V";

                    label694.Text = String.Format("{0:0}", ((float)ChagerCurr) * CurrPerDigit);

                    //                    label694.Text = (((float)ChagerCurr) * CurrPerDigit).ToString();
                    label687.Text = P_Curr.ToString();
                    label689.Text = I_Curr.ToString();
                    label691.Text = P_U.ToString();
                    label693.Text = I_U.ToString();
                    label873.Text = PWMChangedThreshold.ToString();

                    label898.Text = VectorOnOffSpdLo.ToString();
                    label892.Text = VectorOnOffSpdHi.ToString();



                    if (PhasePERMASS_SHFT <= comboBox9.Items.Count)//MaxLength)
                        comboBox9.SelectedIndex = PhasePERMASS_SHFT;



                    switch (UseTmr)
                    {
                        case 0:
                            label261.Text = "Not used";
                            //                        radioButton3.Checked = true;
                            //                      radioButton1.Checked = false;
                            //                    radioButton2.Checked = false;
                            break;
                        case 1:
                            label261.Text = "Timer 1";
                            break;
                        case 2:
                            label261.Text = "Timer 2";
                            break;
                    }


                    TmrCntDelay = 5;



                    if ((StatFlags & 0x400) == 0x400)
                        checkBox25.Checked = false;
                    else
                        checkBox25.Checked = true;

                    /*  if ((StatFlags & 0x800) == 0x800)
                          checkBox26.Checked = true;
                      else
                          checkBox26.Checked = false;
                  */

                    if ((StatFlags2 & 0x0200) == 0x0200)
                        checkBox78.Checked = true;
                    else
                        checkBox78.Checked = false;

                    if ((StatFlags2 & 0x0100) == 0x0100)
                        checkBox77.Checked = true;
                    else
                        checkBox77.Checked = false;






                    if ((StatFlags2 & 0x1000) == 0x1000)
                    {
                        checkBox80.Checked = true;
                        checkBox77.Enabled = false;
                    }
                    else
                    {
                        checkBox80.Checked = false;
                        checkBox77.Enabled = true;
                    }

                    if ((StatFlgs3 & 0x4000) == 0x4000)
                    {
                        radioButton16.Checked = true;
                        radioButton23.Checked = false;
                        radioButton24.Checked = false;
                    }
                    if ((StatFlgs3 & 0x8000) == 0x8000)
                    {
                        radioButton16.Checked = false;
                        radioButton23.Checked = true;
                        radioButton24.Checked = false;
                    }
                    if (((StatFlgs3 & 0x8000) != 0x8000) && ((StatFlgs3 & 0x4000) != 0x4000))
                    {
                        radioButton16.Checked = false;
                        radioButton23.Checked = false;
                        radioButton24.Checked = true;
                    }

                    if ((StatFlgs4 & 0x0200) == 0x0200)
                        checkBox107.Checked = true;
                    else
                        checkBox107.Checked = false;

                    if ((StatFlgs4 & 0x0400) == 0x0400)
                        checkBox108.Checked = true;
                    else
                        checkBox108.Checked = false;

                    if ((StatFlgs4 & 0x0800) == 0x0800)
                        checkBox109.Checked = true;
                    else
                        checkBox109.Checked = false;

                    if ((StatFlgs4 & 0x1000) == 0x1000)
                        checkBox111.Checked = true;
                    else
                        checkBox111.Checked = false;




                    if ((StatFlgs4 & 0x0004) == 0x0004)
                        checkBox95.Checked = true;
                    else
                        checkBox95.Checked = false;

                    if ((StatFlgs4 & 0x0100) == 0x0100)
                        checkBox106.Checked = true;
                    else
                        checkBox106.Checked = false;

                    if (((StatFlgs3 & 0x200) == 0x200) && ((StatFlgs4 & 0x001) == 0x000) && ((StatFlgs4 & 0x002) == 0x000))
                    {
                        if (radioButton25.Checked == false)
                            radioButton25CannotSndCMD = true;


                        radioButton26.Checked = false;
                        radioButton25.Checked = true;
                        radioButton27.Checked = false;
                        radioButton28.Checked = false;
                    }

                    if (((StatFlgs3 & 0x200) == 0x000) && ((StatFlgs4 & 0x001) == 0x000) && ((StatFlgs4 & 0x002) == 0x000))
                    {
                        if (radioButton26.Checked == false)
                            radioButton26CannotSndCMD = true;
                        radioButton26.Checked = true;
                        radioButton25.Checked = false;
                        radioButton27.Checked = false;
                        radioButton28.Checked = false;
                    }

                    if (((StatFlgs3 & 0x200) == 0x000) && ((StatFlgs4 & 0x001) == 0x001) && ((StatFlgs4 & 0x002) == 0x000))
                    {
                        if (radioButton27.Checked == false)
                            radioButton27CannotSndCMD = true;
                        radioButton26.Checked = false;
                        radioButton25.Checked = false;
                        radioButton27.Checked = true;
                        radioButton28.Checked = false;
                    }

                    if (((StatFlgs3 & 0x200) == 0x000) && ((StatFlgs4 & 0x001) == 0x000) && ((StatFlgs4 & 0x002) == 0x002))
                    {
                        if (radioButton28.Checked == false)
                            radioButton28CannotSndCMD = true;
                        radioButton26.Checked = false;
                        radioButton25.Checked = false;
                        radioButton27.Checked = false;
                        radioButton28.Checked = true;
                    }


                    if ((StatFlgs3 & 0x0004) == 0x0004)
                        checkBox1.Checked = true;
                    else
                        checkBox1.Checked = false;


                    if ((StatFlgs3 & 0x1000) == 0x1000)
                        checkBox96.Checked = true;
                    else
                        checkBox96.Checked = false;

                    if ((StatFlgs3 & 0x2000) == 0x2000)
                        checkBox97.Checked = true;
                    else
                        checkBox97.Checked = false;


                    if ((StatFlags2 & 0x2000) == 0x2000)
                    {
                        checkBox81.Checked = true;
                    }
                    else
                    {
                        checkBox81.Checked = false;
                    }


                    if ((StatFlgs3 & 0x100) == 0x100)
                        checkBox94.Checked = true;
                    else
                        checkBox94.Checked = false;



                    if ((StatFlgs3 & 0x20) == 0x20)
                        checkBox91.Checked = true;
                    else
                        checkBox91.Checked = false;



                    if ((StatFlgs3 & 0x40) == 0x40)
                        checkBox92.Checked = true;
                    else
                        checkBox92.Checked = false;

                    if ((StatFlgs3 & 0x80) == 0x80)
                        checkBox93.Checked = true;
                    else
                        checkBox93.Checked = false;


                    if ((StatFlgs4 & 0x0008) == 0x0008)
                        checkBox101.Checked = true;
                    else
                        checkBox101.Checked = false;



                    if ((StatFlags2 & 0x0080) == 0x0080)
                        checkBox75.Checked = true;
                    else
                        checkBox75.Checked = false;

                    if ((StatFlags2 & 0x0040) == 0x0040)
                        checkBox76.Checked = true;
                    else
                        checkBox76.Checked = false;



                    if ((StatFlgs3 & 0x800) == 0x800)
                        checkBox99.Checked = true;
                    else
                        checkBox99.Checked = false;





                    if ((StatFlags2 & 0x0010) == 0x0010)
                        checkBox74.Checked = true;
                    else
                        checkBox74.Checked = false;


                    if ((StatFlags2 & 0x0008) == 0x0008)
                        checkBox73.Checked = true;
                    else
                        checkBox73.Checked = false;



                    if ((StatFlgs4 & 0x8000) == 0x8000)
                        checkBox114.Checked = true;
                    else
                        checkBox114.Checked = false;

                    if ((StatFlgs4 & 0x4000) == 0x4000)
                        checkBox113.Checked = true;
                    else
                        checkBox113.Checked = false;



                    if ((StatFlgs4 & 0x0010) == 0x0010)
                        checkBox102.Checked = true;
                    else
                        checkBox102.Checked = false;

                    if ((StatFlgs4 & 0x0020) == 0x0020)
                        checkBox103.Checked = true;
                    else
                        checkBox103.Checked = false;


                    if ((StatFlgs4 & 0x2000) == 0x2000)
                        checkBox112.Checked = true;
                    else
                        checkBox112.Checked = false;




                    if ((StatFlgs4 & 0x0040) == 0x0040)
                        checkBox104.Checked = true;
                    else
                        checkBox104.Checked = false;

                    if ((StatFlgs4 & 0x0080) == 0x0080)
                        checkBox105.Checked = true;
                    else
                        checkBox105.Checked = false;


                    if ((StatFlags1 & 0x4000) == 0x4000)
                        checkBox72.Checked = true;
                    else
                        checkBox72.Checked = false;


                    if ((StatFlags1 & 0x004) == 0x004)
                        checkBox49.Checked = true;
                    else
                        checkBox49.Checked = false;

                    if ((StatFlags1 & 0x001) == 0x001)
                        checkBox47.Checked = true;
                    else
                        checkBox47.Checked = false;



                    if ((StatFlags1 & 0x008) == 0x008)
                        checkBox51.Checked = true;
                    else
                        checkBox51.Checked = false;



                    if ((StatFlags1 & 0x040) == 0x040)
                        checkBox54.Checked = true;
                    else
                        checkBox54.Checked = false;

                    if ((StatFlags & 0x1000) == 0x1000)
                        checkBox71.Checked = true;
                    else
                        checkBox71.Checked = false;





                    if (((StatFlags2 & 0x0004) == 0x0004) && ((StatFlags & 0x0800) != 0x0800) && ((StatFlags2 & 0x0800) != 0x0800))
                    {
                        if (radioButton7.Checked == false)
                            radioButton7CannotSndCMD = true;
                        if (radioButton10.Checked == true)
                            radioButton10CannotSndCMD = true;
                        if (radioButton11.Checked == true)
                            radioButton11CannotSndCMD = true;
                        if (radioButton12.Checked == true)
                            radioButton12CannotSndCMD = true;

                        radioButton7.Checked = true;
                        radioButton10.Checked = false;
                        radioButton11.Checked = false;
                        radioButton12.Checked = false;
                    }

                    if (((StatFlags2 & 0x0004) != 0x0004) && ((StatFlags & 0x0800) == 0x0800) && ((StatFlags2 & 0x0800) != 0x0800))
                    {
                        if (radioButton7.Checked == true)
                            radioButton7CannotSndCMD = true;
                        if (radioButton10.Checked == false)
                            radioButton10CannotSndCMD = true;
                        if (radioButton11.Checked == true)
                            radioButton11CannotSndCMD = true;
                        if (radioButton12.Checked == true)
                            radioButton12CannotSndCMD = true;

                        radioButton7.Checked = false;
                        radioButton10.Checked = true;
                        radioButton11.Checked = false;
                        radioButton12.Checked = false;
                    }

                    if (((StatFlags2 & 0x0004) != 0x0004) && ((StatFlags & 0x0800) != 0x0800) && ((StatFlags2 & 0x0800) != 0x0800))
                    {
                        if (radioButton7.Checked == true)
                            radioButton7CannotSndCMD = true;
                        if (radioButton10.Checked == true)
                            radioButton10CannotSndCMD = true;
                        if (radioButton11.Checked == false)
                            radioButton11CannotSndCMD = true;
                        if (radioButton12.Checked == true)
                            radioButton12CannotSndCMD = true;

                        radioButton7.Checked = false;
                        radioButton10.Checked = false;
                        radioButton11.Checked = true;
                        radioButton12.Checked = false;
                    }

                    if (((StatFlags2 & 0x0004) != 0x0004) && ((StatFlags & 0x0800) != 0x0800) && ((StatFlags2 & 0x0800) == 0x0800))
                    {
                        if (radioButton7.Checked == true)
                            radioButton7CannotSndCMD = true;
                        if (radioButton10.Checked == true)
                            radioButton10CannotSndCMD = true;
                        if (radioButton11.Checked == true)
                            radioButton11CannotSndCMD = true;
                        if (radioButton12.Checked == false)
                            radioButton12CannotSndCMD = true;

                        radioButton7.Checked = false;
                        radioButton10.Checked = false;
                        radioButton11.Checked = false;
                        radioButton12.Checked = true;
                    }





                    if ((StatFlags & 0x0020) == 0x0020)
                        checkBox67.Checked = true;
                    else
                        checkBox67.Checked = false;

                    if ((StatFlags & 0x0100) == 0x0100)
                        checkBox26.Checked = true;
                    else
                        checkBox26.Checked = false;


                    if ((StatFlgs3 & 0x400) == 0x400)
                    {
                        radioButton4.Checked = false;
                        radioButton5.Checked = false;//ток
                        radioButton22.Checked = true;
                    }
                    else
                    {
                        if ((StatFlags1 & 0x02) == 0x02)
                        {
                            radioButton4.Checked = false;
                            radioButton5.Checked = true;
                            radioButton22.Checked = false;
                        }
                        else
                        {
                            radioButton4.Checked = true;
                            radioButton5.Checked = false;//момент
                            radioButton22.Checked = false;
                        }
                    }

                    if ((StatFlags2 & 0x20) != 0x20)
                    {
                        if ((StatFlags & 0x10) == 0x10)
                        {
                            radioButton6.Checked = false;
                            radioButton8.Checked = false;
                            radioButton9.Checked = true;
                        }
                        else
                        {
                            radioButton6.Checked = false;
                            radioButton8.Checked = true;
                            radioButton9.Checked = false;
                        }
                    }
                    else
                    {
                        radioButton6.Checked = true;
                        radioButton8.Checked = false;
                        radioButton9.Checked = false;
                    }










                    if ((StatFlags & 0x200) == 0x200)
                        checkBox44.Checked = true;
                    else
                        checkBox44.Checked = false;



                    if ((StatFlags & 0x08) == 0x8)
                        checkBox15.Checked = true;
                    else
                        checkBox15.Checked = false;



                    if ((StatFlags & 1) == 0)
                    {
                        checkBox14.Checked = false;
                    }
                    else
                    {
                        checkBox14.Checked = true;
                    }




                    if ((StatFlags1 & 0x400) == 0x400)
                        checkBox57.Checked = true;
                    else
                        checkBox57.Checked = false;


                    if ((StatFlags1 & 0x1000) == 0x1000)
                        checkBox58.Checked = true;
                    else
                        checkBox58.Checked = false;


                    if ((StatFlags1 & 0x8000) == 0x8000)
                        checkBox61.Checked = true;
                    else
                        checkBox61.Checked = false;



                    if ((StatFlags2 & 0x4000) == 0x4000)
                        checkBox82.Checked = true;
                    else
                        checkBox82.Checked = false;

                    if ((StatFlags2 & 0x8000) == 0x8000)
                        checkBox83.Checked = true;
                    else
                        checkBox83.Checked = false;



                    if ((StatFlgs3 & 0x001) == 0x001)
                        checkBox85.Checked = true;
                    else
                        checkBox85.Checked = false;

                    if ((StatFlgs3 & 0x0010) == 0x0010)
                        checkBox90.Checked = true;
                    else
                        checkBox90.Checked = false;

                    if ((StatFlgs3 & 0x800) == 0x800)
                    {
                        radioButton17.Checked = true;
                        radioButton18.Checked = false;
                    }
                    else
                    {
                        radioButton17.Checked = false;
                        radioButton18.Checked = true;
                    }




                    /*
                    if ((!((StatFlgs3 & 0x002) == 0x002)) && (!((StatFlgs3 & 0x004) == 0x004)))
                    {
//                        radioButton16.Checked = false;
                        radioButton17.Checked = false;
                        radioButton18.Checked = true;
                    }
                    else
                    {
                        if ((StatFlgs3 & 0x002) == 0x002)
                            {
  //                          radioButton16.Checked = true;
                            radioButton17.Checked = false;
                            radioButton18.Checked = false;
                            }
                        if ((StatFlgs3 & 0x004) == 0x004)
                        {
    //                        radioButton16.Checked = false;
                            radioButton17.Checked = true;
                            radioButton18.Checked = false;
                        }


                    }

                    */

                    //if ((StatFlgs3 & 0x008) == 0x0008)
                    //    checkBox86.Checked = true;
                    //else
                    //    checkBox86.Checked = false;







                    if ((StatFlags1 & 0x800) == 0x800)
                        checkBox84.Checked = true;
                    else
                        checkBox84.Checked = false;


                    if ((StatFlags2 & 0x200) == 0x200)
                        checkBox56.Checked = true;
                    else
                        checkBox56.Checked = false;

                    if ((StatFlags2 & 0x400) == 0x400)
                        checkBox79.Checked = true;
                    else
                        checkBox79.Checked = false;


                    if ((StatFlags1 & 0x80) == 0x80)
                        checkBox63.Checked = true;
                    else
                        checkBox63.Checked = false;

                    if ((StatFlags1 & 0x200) == 0x200)
                        checkBox64.Checked = true;
                    else
                        checkBox64.Checked = false;


                    if ((StatFlags2 & 0x01) == 0x01)
                        checkBox65.Checked = true;
                    else
                        checkBox65.Checked = false;


                    if ((StatFlags2 & 0x02) == 0x02)
                        checkBox66.Checked = true;
                    else
                        checkBox66.Checked = false;

                    if ((StatFlags & 0x40) == 0x40)
                        checkBox68.Checked = true;
                    else
                        checkBox68.Checked = false;


                    if ((StatFlags & 0x2000) == 0x2000)
                        checkBox55.Checked = true;
                    else
                        checkBox55.Checked = false;

                    if ((StatFlags & 0x8000) == 0x8000)
                        checkBox70.Checked = true;
                    else
                        checkBox70.Checked = false;



                    // if ((StatFlags & 0x100) == 0x100)
                    //     checkBox24.Checked = false;
                    // else
                    //     checkBox24.Checked = true;


                    // if ((StatFlags & 0x400) == 0x400)
                    //    checkBox25.Checked = false;
                    //else
                    //    checkBox25.Checked = true;

                    //if ((StatFlags & 0x800) == 0x800)
                    //    checkBox26.Checked = true;
                    //else
                    //    checkBox26.Checked = false;

                    // if ((StatFlags & 0x200) == 0x200)
                    //     checkBox11.Checked = false;
                    // else
                    //     checkBox11.Checked = true;




                    // if ((StatFlags & 0x40) == 0x40)
                    //     checkBox21.Checked = false;
                    // else
                    //     checkBox21.Checked = true;



                    // if ((StatFlags & 0x20) == 0x20)
                    //     checkBox23.Checked = false;
                    // else
                    //     checkBox23.Checked = true;



                    // if ((StatFlags & 0x10) == 0x10)
                    //     checkBox22.Checked = false;
                    // else
                    //     checkBox22.Checked = true;

                    // if ((StatFlags & 0x08) == 0x8)
                    //     checkBox15.Checked = false;
                    // else
                    //     checkBox15.Checked = true;



                    // if ((StatFlags & 1) == 0)
                    // {
                    //     checkBox14.Checked = false;
                    // }
                    // else
                    // {
                    //     checkBox14.Checked = true;
                    // }

                    // if ((StatFlags & 8) == 0)
                    // {
                    //     checkBox15.Checked = false;
                    // }
                    // else
                    // {
                    //     checkBox15.Checked = true;
                    // }



                    //if (VDS_LVL < comboBox22.Items.Count)
                    //              comboBox22.SelectedIndex = VDS_LVL;
                    //if (OCP_DEG < comboBox21.Items.Count)
                    //              comboBox21.SelectedIndex = OCP_DEG;


                    if (TstPhase < comboBox24.Items.Count)
                        comboBox24.SelectedIndex = TstPhase;





                    if (CurrLimitSpd0 <= comboBox19.MaxLength)
                        comboBox19.SelectedIndex = CurrLimitSpd0;
                    //if (CurrLimit < comboBox1.Items.Count)
                    //       comboBox1.SelectedIndex = CurrLimit;
                    try
                    {
                        comboBox14.SelectedIndex = SensorlessCurrLimit;
                    }
                    catch (System.ArgumentOutOfRangeException)
                    {

                    }

                    if (But1Func < comboBox7.Items.Count)
                        comboBox7.SelectedIndex = But1Func;
                    if (But2Func < comboBox10.Items.Count)
                        comboBox10.SelectedIndex = But2Func;
                    if (But3Func < comboBox11.Items.Count)
                        comboBox11.SelectedIndex = But3Func;
                    if (But4Func < comboBox12.Items.Count)
                        comboBox12.SelectedIndex = But4Func;

                    if (_3psnSwitchBt3 < comboBox13.Items.Count)
                        comboBox13.SelectedIndex = _3psnSwitchBt3;
                    if (_3psnSwitchBtNotPressed < comboBox16.Items.Count)
                        comboBox16.SelectedIndex = _3psnSwitchBtNotPressed;
                    if (_3psnSwitchBt4 < comboBox17.Items.Count)
                        comboBox17.SelectedIndex = _3psnSwitchBt4;



                    break;

                case 4:

                    label122.Text = ErrOptions.ToString();
                    label124.Text = AlfaXResErr.ToString();
                    label126.Text = AlfaYResErr.ToString();
                    label128.Text = SteerXErr.ToString();
                    label130.Text = SteerYErr.ToString();
                    label132.Text = ErrorCode.ToString();
                    label134.Text = NoBalanceCode.ToString();
                    label136.Text = FlgsErr.ToString();
                    label138.Text = Flgs1Err.ToString();
                    label172.Text = Flgs2Err.ToString();


                    label162.Text = LastMainTiltAngleMnErr.ToString();
                    label160.Text = LastSteerTiltAngleMnErr.ToString();
                    label158.Text = TiltAngleAvMnErr.ToString();
                    label156.Text = MainTiltNumErr.ToString();
                    label154.Text = SteerTiltNumErr.ToString();

                    label170.Text = LastMainTiltAngleSteerErr.ToString();
                    label168.Text = LastSteerTiltAngleSteerErr.ToString();
                    label166.Text = TiltAngleAvSteerErr.ToString();


                    label164.Text = StatFlgs.ToString();

                    label330.Text = BatErr.ToString();


                    break;


                case 5:






                    uint h = Flgs2 & 0x400;
                    if (h != 0)
                        label148.Text = "1";
                    else
                        label148.Text = "0";

                    h = Flgs2 & 0x800;
                    if (h != 0)
                        label150.Text = "1";
                    else
                        label150.Text = "0";

                    h = Flgs2 & 0x20;           //        TiltSensor2
                    if (h != 0)
                        label175.Text = "1";
                    else
                        label175.Text = "0";

                    h = Flgs2 & 0x80;           //        MainTiltError
                    if (h != 0)
                        label173.Text = "1";
                    else
                        label173.Text = "0";

                    h = Flgs2 & 0x40;           //        TiltSteerError
                    if (h != 0)
                        label177.Text = "1";
                    else
                        label177.Text = "0";


                    label184.Text = Flgs.ToString();
                    label182.Text = Flgs1.ToString();
                    label180.Text = Flgs2.ToString();
                    label256.Text = (TimerCnt / 500).ToString();

                    if ((Flgs1 & 0x20000000) == 0x20000000)
                    {
                        label457.ForeColor = Color.Black;
                        label459.ForeColor = Color.Black;
                        label455.ForeColor = Color.Blue;
                        label456.ForeColor = Color.Blue;


                        label650.ForeColor = Color.Black;
                        label649.ForeColor = Color.Black;
                        label648.ForeColor = Color.Blue;
                        label651.ForeColor = Color.Blue;


                    }
                    else
                    {
                        label457.ForeColor = Color.Blue;
                        label459.ForeColor = Color.Blue;
                        label455.ForeColor = Color.Black;
                        label456.ForeColor = Color.Black;


                        label650.ForeColor = Color.Blue;
                        label649.ForeColor = Color.Blue;
                        label648.ForeColor = Color.Black;
                        label651.ForeColor = Color.Black;


                    }















                    float ObMin;
                    ObMin = Spd1Res * 600;
                    ObMin = ObMin / (float)PhasesPerRev1;

                    label368.Text = ObMin.ToString();


                    label322.Text = Sensor1_Prev.ToString();
                    label380.Text = Temperature.ToString();

                    label423.Text = Spd1Fl.ToString() + " " + MyStrings.KMH;
                    label426.Text = String.Format("{0:0.0}", UBT) + " V";
                    label699.Text = String.Format("{0:0.0}", UBT) + " V";


                    uint rr = HallDelay1_F;

                    if (HallDelay1_F > 127)
                    {
                        rr = rr | 0xffffff00;
                    }
                    int ewq = (int)rr;

                    //                    label459.Text = HallDelay1_F.ToString();
                    label459.Text = ewq.ToString();




                    label653.Text = HallDelayMaxSPD.ToString();


                    if (HallDelayMaxSPD == 0)
                    {
                        label648.Enabled = false;
                        label649.Enabled = false;
                        label650.Enabled = false;
                        label651.Enabled = false;
                        numericUpDown171.Enabled = false;
                        numericUpDown172.Enabled = false;
                    }
                    else
                    {
                        label648.Enabled = true;
                        label649.Enabled = true;
                        label650.Enabled = true;
                        label651.Enabled = true;
                        numericUpDown171.Enabled = true;
                        numericUpDown172.Enabled = true;
                    }



                    rr = HallDelay1MaxSPD_F;

                    if (HallDelay1MaxSPD_F > 127)
                    {
                        rr = rr | 0xffffff00;
                    }
                    ewq = (int)rr;





                    label649.Text = ewq.ToString();






                    rr = HallDelay1MaxSPD_B;

                    if (HallDelay1MaxSPD_B > 127)
                    {
                        rr = rr | 0xffffff00;
                    }
                    ewq = (int)rr;









                    label651.Text = ewq.ToString();




                    rr = HallDelay1_B;

                    if (HallDelay1_B > 127)
                    {
                        rr = rr | 0xffffff00;
                    }
                    ewq = (int)rr;

                    //label456.Text = HallDelay1_B.ToString();
                    label456.Text = ewq.ToString();




                    label470.Text = MaxSpdPID.ToString();
                    label372.Text = MAX_PWM_MEM.ToString();

                    label537.Text = MAX_PWM_Revers.ToString();
                    label540.Text = MaxSpdRevers.ToString();

                    label543.Text = AutoPID_On_PWM.ToString();
                    label546.Text = String.Format("{0:0.0}", ((float)AutoPID_On_Speed) / 10);//AutoPID_On_Speed.ToString();

                    label548.Text = AutoPID_On_CntConst.ToString();
                    label511.Text = LightSensor.ToString();





                    if (CntNoChange == 0)
                    {
                        if ((Flgs1 & 0x00000002) == 0x00000002)
                            checkBox89.Checked = true;
                        else
                            checkBox89.Checked = false;

                    }


                    if ((Flgs & 0x40000000) == 0x40000000)
                    {
                        label403.Text = "On";
                        label403.ForeColor = Color.Green;
                    }
                    else
                    {
                        label403.Text = "Off";
                        label403.ForeColor = Color.Blue;
                    }


                    if ((Flgs5 & 0x400000) == 0x400000)
                    {
                        button44.BackColor = Color.HotPink;
                        button44.Text = MyStrings.Unlock;
                    }
                    else
                    {
                        button44.BackColor = Color.Aquamarine;
                        button44.Text = MyStrings.Lock;
                    }

                    if ((Flgs5 & 0x100) == 0x100)
                    {
                        label701.Text = "Off";
                        label702.Text = "On";
                        label701.ForeColor = Color.Blue;
                        label702.ForeColor = Color.Red;
                    }
                    else
                    {
                        label701.Text = "On";
                        label702.Text = "Off";
                        label701.ForeColor = Color.Red;
                        label702.ForeColor = Color.Blue;
                    }



                    //label471.Text = Temperature1.ToString();
                    //label474.Text = Temperature2.ToString();

                    //label680.Text = (_12VFl/100).ToString();
                    label680.Text = String.Format("{0:0.0}", (_12VFl / 100)) + " V";
                    label681.Text = String.Format("{0:0.0}", (_5VFl / 100)) + " V";
                    label684.Text = String.Format("{0:0.0}", (_3VFl / 100)) + " V";
                    label790.Text = BuzzerOnEvent.ToString();


                    //label681.Text = (_5VFl/100).ToString();
                    //label684.Text = (_3VFl/100).ToString();


                    Temperature1 = Temperature1 / 10;
                    Temperature2 = Temperature2 / 10;
                    Temperature3 = Temperature3 / 10;
                    Temperature4 = Temperature4 / 10;
                    Temperature5 = Temperature5 / 10;
                    Temperature6 = Temperature6 / 10;

                    if (checkBox63.Checked)
                    {
                        label476.Text = Temperature1.ToString();
                        label474.Text = String.Format("{0:0.0}", (Temperature1));
                    }
                    else
                    {
                        label476.Text = "---";
                        label474.Text = "---";
                    }


                    if (checkBox64.Checked)
                    {
                        label478.Text = Temperature2.ToString();
                        label477.Text = String.Format("{0:0.0}", (Temperature2));
                    }
                    else
                    {
                        label478.Text = "---";
                        label477.Text = "---";
                    }





                    if (checkBox70.Checked)
                    {
                        if ((Flgs & 0x800) == 0x800)
                        {
                            label860.Text = "Stopped";
                            label860.ForeColor = Color.Blue;
                        }
                        else
                        {
                            label860.Text = "Running";
                            label860.ForeColor = Color.Red;
                        }

                    }
                    else
                    {
                        label860.Text = "eBike mode";
                        label860.ForeColor = Color.Black;
                    }





                    rr = HallDelay1_Tek_F;

                    if (HallDelay1_Tek_F > 127)
                    {
                        rr = rr | 0xffffff00;
                    }
                    ewq = (int)rr;



                    label656.Text = ewq.ToString();


                    rr = HallDelay1_Tek_B;

                    if (HallDelay1_Tek_B > 127)
                    {
                        rr = rr | 0xffffff00;
                    }
                    ewq = (int)rr;


                    label657.Text = ewq.ToString();



                    if (checkBox65.Checked)
                    {
                        label512.Text = Temperature3.ToString();
                        //label513.Text = String.Format("{0:0.0}", (Temperature3));
                        label643.Text = String.Format("{0:0.0}", (Temperature3));
                    }
                    else
                    {
                        label512.Text = "---";
                        //label513.Text = "---";
                        label643.Text = "---";
                    }


                    //label527.Text = String.Format("{0:0.0}", (Phase1Period2/10));


                    if (checkBox66.Checked)
                    {
                        label484.Text = Temperature4.ToString();
                        //label515.Text = String.Format("{0:0.0}", (Temperature4));
                        label645.Text = String.Format("{0:0.0}", (Temperature4));
                    }
                    else
                    {
                        label484.Text = "---";
                        //label515.Text = "---";
                        label645.Text = "---";
                    }
                    if (radioButton20.Checked)
                    {
                        if ((Flgs4 & 0x01) == 0x01)
                        {
                            label710.Text = MyStrings.ConnectedWithMaster;
                            label710.ForeColor = Color.Green;
                        }
                        else
                        {
                            label710.Text = MyStrings.DisconnectedWithMaster;
                            label710.ForeColor = Color.Red;
                        }

                    }
                    else
                        label710.Text = "";
                    label678.Text = KdI.ToString();


                    if ((HallsLines & 0x1) == 0x1)
                        label874.Text = "1";
                    else
                        label874.Text = "0";

                    if ((HallsLines & 0x2) == 0x2)
                        label875.Text = "1";
                    else
                        label875.Text = "0";

                    if ((HallsLines & 0x4) == 0x4)
                        label876.Text = "1";
                    else
                        label876.Text = "0";


                    switch (CriticalError)
                    {
                        case 0:
                            toolStripStatusLabel3.ForeColor = Color.Black;
                            toolStripStatusLabel3.Text = MyStrings.No;
                            break;
                        case 1:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.HighLevelThrottleOn;
                            break;
                        case 2:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.DisconnectedZeroWire;
                            break;
                        case 3:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.TooLowVoltage;
                            break;
                        case 5:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.FETsOverTemperature;
                            break;
                        case 6:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.MotorOverheated;
                            break;
                        case 7:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.ZeroSpeedTimeOut;
                            break;
                        case 8:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.TooHighVoltage;
                            break;
                        case 9:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.HighLevelFromThrottleAfterAutoSettings;
                            break;
                        case 10:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.Err_CRERR_GYROACC_DISCONNECTED;
                            break;
                        case 11:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.Err_CRERR_MASTER_DISCONNECTED;
                            break;
                        case 12:
                            toolStripStatusLabel3.ForeColor = Color.Red;
                            toolStripStatusLabel3.Text = MyStrings.Err_CRERR_PWM_CHANGED_HIGH;
                            break;






                    }


                    label415.Text = String.Format("{0:0.0}", (float)CurrUstTek / 1000) + " A";
                    label638.Text = String.Format("{0:0.0}", (float)CurrPhaseLimitTek / 1000) + " A";
                    label563.Text = CriticalError.ToString();
                    label623.Text = MPU6050Err.ToString();

                    label482.Text = Kp.ToString();
                    label639.Text = Ki.ToString();

                    label666.Text = AccX.ToString();
                    label668.Text = AccY.ToString();
                    label670.Text = AccZ.ToString();

                    label661.Text = GyroXFl.ToString();
                    label663.Text = GyroYFl.ToString();
                    label665.Text = GyroZFl.ToString();


                    if ((FaultStatus1Res & 0x8000) == 0x8000)
                    {
                        label773.Text = "No errors";
                        label773.ForeColor = Color.Green;
                    }
                    else
                    {
                        label773.Text = "Error(s)";
                        label773.ForeColor = Color.Red;

                    }
                    //  if ((FaultStatus1Res) == 0x000)
                    //{
                    label749.Text = "0";
                    label749.ForeColor = Color.Green;
                    label747.Text = "0";
                    label747.ForeColor = Color.Green;
                    label745.Text = "0";
                    label745.ForeColor = Color.Green;
                    label737.Text = "0";
                    label737.ForeColor = Color.Green;
                    label739.Text = "0";
                    label739.ForeColor = Color.Green;
                    label741.Text = "0";
                    label741.ForeColor = Color.Green;
                    label743.Text = "0";
                    label743.ForeColor = Color.Green;
                    label735.Text = "0";
                    label735.ForeColor = Color.Green;
                    label733.Text = "0";
                    label733.ForeColor = Color.Green;
                    label731.Text = "0";
                    label731.ForeColor = Color.Green;
                    label729.Text = "0";
                    label729.ForeColor = Color.Green;
                    // }


                    if ((FaultStatus1Res & 0x0001) == 0x0001)
                    {
                        label749.Text = "1";
                        label749.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0002) == 0x0002)
                    {
                        label747.Text = "1";
                        label747.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0004) == 0x0004)
                    {
                        label745.Text = "1";
                        label745.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0008) == 0x0008)
                    {
                        label737.Text = "1";
                        label737.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0010) == 0x0010)
                    {
                        label739.Text = "1";
                        label739.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0020) == 0x0020)
                    {
                        label741.Text = "1";
                        label741.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0040) == 0x0040)
                    {
                        label743.Text = "1";
                        label743.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0080) == 0x0080)
                    {
                        label735.Text = "1";
                        label735.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0100) == 0x0100)
                    {
                        label733.Text = "1";
                        label733.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0200) == 0x0200)
                    {
                        label731.Text = "1";
                        label731.ForeColor = Color.Red;
                    }
                    if ((FaultStatus1Res & 0x0400) == 0x0400)
                    {
                        label729.Text = "1";
                        label729.ForeColor = Color.Red;
                    }

                    //if ((FaultStatus1Res) == 0x000)
                    //{
                    label751.Text = "0";
                    label751.ForeColor = Color.Green;
                    label753.Text = "0";
                    label753.ForeColor = Color.Green;
                    label755.Text = "0";
                    label755.ForeColor = Color.Green;
                    label757.Text = "0";
                    label757.ForeColor = Color.Green;
                    label759.Text = "0";
                    label759.ForeColor = Color.Green;
                    label761.Text = "0";
                    label761.ForeColor = Color.Green;
                    label763.Text = "0";
                    label763.ForeColor = Color.Green;
                    label765.Text = "0";
                    label765.ForeColor = Color.Green;
                    label767.Text = "0";
                    label767.ForeColor = Color.Green;
                    label769.Text = "0";
                    label769.ForeColor = Color.Green;
                    label771.Text = "0";
                    label771.ForeColor = Color.Green;
                    // }


                    if ((VGSStatus2Res & 0x0001) == 0x0001)
                    {
                        label751.Text = "1";
                        label751.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0002) == 0x0002)
                    {
                        label753.Text = "1";
                        label753.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0004) == 0x0004)
                    {
                        label755.Text = "1";
                        label755.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0008) == 0x0008)
                    {
                        label757.Text = "1";
                        label757.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0010) == 0x0010)
                    {
                        label759.Text = "1";
                        label759.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0020) == 0x0020)
                    {
                        label761.Text = "1";
                        label761.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0040) == 0x0040)
                    {
                        label763.Text = "1";
                        label763.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0080) == 0x0080)
                    {
                        label765.Text = "1";
                        label765.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0100) == 0x0100)
                    {
                        label767.Text = "1";
                        label767.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0200) == 0x0200)
                    {
                        label769.Text = "1";
                        label769.ForeColor = Color.Red;
                    }
                    if ((VGSStatus2Res & 0x0400) == 0x0400)
                    {
                        label771.Text = "1";
                        label771.ForeColor = Color.Red;
                    }




                    float ttm = AlfaYRes;
                    ttm = ttm / 100;

                    label672.Text = String.Format("{0:0.00}", (ttm));

                    ttm = AlfaXRes;
                    ttm = ttm / 100;

                    label674.Text = String.Format("{0:0.00}", (ttm));



                    /*
                    switch (comboBox18.SelectedIndex)
                    {
                        case 0:
                            switch (CurrLimitTek)
                            {
                                case 0:
                                    label481.Text = "26A";
                                    break;
                                case 1:
                                    label481.Text = "34A";
                                    break;
                                case 2:
                                    label481.Text = "42A";
                                    break;
                                case 3:
                                    label481.Text = "50A";
                                    break;
                                case 4:
                                    label481.Text = "58A";
                                    break;
                                case 5:
                                    label481.Text = "65A";
                                    break;
                                case 6:
                                    label481.Text = "74A";
                                    break;
                                case 7:
                                    label481.Text = "81A";
                                    break;
                                case 8:
                                    label481.Text = "89A";
                                    break;
                                case 9:
                                    label481.Text = "97A";
                                    break;
                                case 10:
                                    label481.Text = "104A";
                                    break;
                                case 11:
                                    label481.Text = "113A";
                                    break;
                                case 12:
                                    label481.Text = "120A";
                                    break;
                                case 13:
                                    label481.Text = "128A";
                                    break;
                                case 14:
                                    label481.Text = "136A";
                                    break;
                            }
                            break;
                        case 1:
                            switch (CurrLimitTek)
                            {
                                case 0:
                                    label481.Text = "35A";
                                    break;
                                case 1:
                                    label481.Text = "46A";
                                    break;
                                case 2:
                                    label481.Text = "56A";
                                    break;
                                case 3:
                                    label481.Text = "66A";
                                    break;
                                case 4:
                                    label481.Text = "77A";
                                    break;
                                case 5:
                                    label481.Text = "87A";
                                    break;
                                case 6:
                                    label481.Text = "98A";
                                    break;
                                case 7:
                                    label481.Text = "108A";
                                    break;
                                case 8:
                                    label481.Text = "118A";
                                    break;
                                case 9:
                                    label481.Text = "129A";
                                    break;
                                case 10:
                                    label481.Text = "139A";
                                    break;
                                case 11:
                                    label481.Text = "150A";
                                    break;
                                case 12:
                                    label481.Text = "160A";
                                    break;
                                case 13:
                                    label481.Text = "170A";
                                    break;
                                case 14:
                                    label481.Text = "181A";
                                    break;
                            }
                            break;
                        case 2:
                            switch (CurrLimitTek)
                            {
                                case 0:
                                    label481.Text = "52A";
                                    break;
                                case 1:
                                    label481.Text = "68A";
                                    break;
                                case 2:
                                    label481.Text = "84A";
                                    break;
                                case 3:
                                    label481.Text = "100A";
                                    break;
                                case 4:
                                    label481.Text = "116A";
                                    break;
                                case 5:
                                    label481.Text = "130A";
                                    break;
                                case 6:
                                    label481.Text = "148A";
                                    break;
                                case 7:
                                    label481.Text = "162A";
                                    break;
                                case 8:
                                    label481.Text = "178A";
                                    break;
                                case 9:
                                    label481.Text = "194A";
                                    break;
                                case 10:
                                    label481.Text = "208A";
                                    break;
                                case 11:
                                    label481.Text = "226A";
                                    break;
                                case 12:
                                    label481.Text = "240A";
                                    break;
                                case 13:
                                    label481.Text = "256A";
                                    break;
                                case 14:
                                    label481.Text = "272A";
                                    break;
                            }
                            break;

                    }*/




                    uint df = Flgs2 & 0x40000000;

                    if (df == 0x40000000)
                        button36.BackColor = Color.Red;
                    else
                        button36.BackColor = Color.Transparent;


                    if ((Flgs3 & 0x100) == 0x100)
                    {
                        label621.Text = "Контроллер с гальваноразвязкой";
                    }
                    else
                    {
                        label621.Text = "Not isolated";
                    }



                    try
                    {
                        if (toolStripProgressBar1 != null)
                            toolStripProgressBar1.ForeColor = Color.Blue;
                    }
                    catch (System.NullReferenceException)
                    {
                    }

                    try
                    {
                        toolStripProgressBar1.Value = ((int)(CntSamples & 0xff) * 100) / 256;// / 2.56);
                    }
                    catch (System.NullReferenceException)
                    {
                    }


                    ConnectionCnt = 20;
                    toolStripStatusLabel1.Text = MyStrings.Connected;
                    toolStripStatusLabel1.ForeColor = Color.Green;

                    label599.Text = EPID_Res.ToString();
                    label605.Text = Ed.ToString();
                    label606.Text = GyroXFl.ToString();
                    label607.Text = GyroZFl.ToString();

                    label612.Text = RCON_Mem.ToString();


                    if (checkBox89.Checked)
                    {
                        if ((Flgs4 & 0x40000000) == 0x40000000)
                        {
                            label514.Text = MyStrings.Disconnected;
                            label514.ForeColor = Color.Green;
                        }
                        else
                        {
                            label514.Text = MyStrings.Connected;
                            label514.ForeColor = Color.Red;
                        }
                    }
                    else
                    {
                        label514.Text = "----------";
                        label514.ForeColor = Color.Black;
                    }



                    if (ShowSer == 1)
                    {
                        int comboBox3Num;


                        if ((Flgs & 0x40000000) == 0x40000000)
                        {
                            label226.Text = MyStrings.ComplementaryMode;
                            label226.Enabled = false;
                        }
                        else
                        {
                            label226.Enabled = true;
                            if ((Flgs1 & 0x10000) == 0x10000)
                            {
                                label226.Text = "On";
                                label226.ForeColor = Color.Green;
                            }
                            else
                            {
                                label226.Text = "Off";
                                label226.ForeColor = Color.Blue;
                            }
                        }




                        if ((Flgs1 & 0x80) == 0x80)
                        {
                            label424.Text = "On";
                            label424.ForeColor = Color.Green;
                        }
                        else
                        {
                            label424.Text = "Off";
                            label424.ForeColor = Color.Blue;
                        }


                        if ((Flgs2 & 0x200) == 0x200)
                        {
                            label414.Text = "On";
                            label414.ForeColor = Color.Green;
                        }
                        else
                        {
                            label414.Text = "Off";
                            label414.ForeColor = Color.Blue;
                        }


                        if ((Flgs5 & 0x4) == 0x4)
                        {
                            label252.Text = "On";
                            label252.ForeColor = Color.Green;
                        }
                        else
                        {
                            label252.Text = "Off";
                            label252.ForeColor = Color.Blue;
                        }


                        if ((Flgs5 & 0x800) == 0x800)
                        {
                            label342.Text = "On";
                            label342.ForeColor = Color.Green;
                        }
                        else
                        {
                            label342.Text = "Off";
                            label342.ForeColor = Color.Blue;
                        }



                        GraphSeries();


                    }
                    float ut = (float)Cr1;
                    ut = ut / 1000;

                    label251.Text = String.Format("{0:0.000}", ut) + " A";
                    label696.Text = String.Format("{0:0.000}", ut) + " A";
                    //ut = (float)Cr2;
                    //ut = ut / 1000;


                    label241.Text = ZeroCurr1.ToString();


                    double tt = CurrTuda1;
                    tt = ((tt * CurrPerDigit) / 36000);
                    float ttf = ((float)tt) / 1000;

                    label243.Text = String.Format("{0:0.000}", ttf) + " A*h";

                    float C1, C2, C3;

                    C1 = ttf;

                    tt = CurrRegen1;
                    tt = (tt / 36000) * CurrPerDigit;
                    ttf = ((float)tt) / 1000;
                    label244.Text = String.Format("{0:0.000}", ttf) + " A*h";
                    C2 = ttf;


                    //                    tt = CurrTuda2;
                    //                  tt = (tt / 36000) * CurrPerDigit;
                    //                ttf = ((float)tt) / 1000;

                    C3 = ttf;

                    //                    tt = CurrRegen2;
                    //                  tt = (tt / 36000) * CurrPerDigit;
                    //                ttf = ((float)tt) / 1000;

                    C1 = C1 - C2 + C3 - ttf;




                    //label109.Text = _15[l].ToString();

                    float wp = (float)Odometr;
                    float CmImp1_t = (float)Diametr1 * (float)0.314159 / (float)PhasesPerRev1;
                    float ImpNa1m = 100 / CmImp1_t;
                    wp = wp / ImpNa1m;//(float)99.8;

                    label325.Text = ((int)(Odometr - OdometrMem)).ToString();



                    label110.Text = ((int)wp).ToString() + " m";

                    wp = (float)Distance;

                    wp = wp / ImpNa1m;//(float)99.8;

                    label366.Text = ((int)wp).ToString() + " m";

                    if ((Flgs3 & 0x4000000) == 0x4000000)
                    {
                        label787.Text = "On";
                        label787.ForeColor = Color.Red;
                    }
                    else
                    {
                        label787.Text = "Off";
                        label787.ForeColor = Color.Blue;
                    }


                    //label483.Text = CntPhaseMEM.ToString();
                    //label483.Text = Phase1Period3.ToString();
                    if ((radioButton20.Checked) && (!((Flgs4 & 0x01) == 0x01)))
                    {
                        label553.ForeColor = Color.Blue;
                        label555.ForeColor = Color.Blue;
                        label553.Text = "xWD Slave";
                        label555.Text = "xWD Slave";
                    }
                    else
                    {
                        label553.ForeColor = Color.Black;
                        label553.Text = Preas1ADC.ToString();
                        label555.ForeColor = Color.Black;
                        label555.Text = Preas2ADC.ToString();
                    }


                    if ((radioButton20.Checked) && ((Flgs4 & 0x01) != 0x01))
                    {
                        label534.ForeColor = Color.Blue;
                        label577.ForeColor = Color.Blue;
                        label577.Text = "xWD Slave";
                        label534.Text = "xWD Slave";
                    }
                    else
                    {
                        label534.ForeColor = Color.Black;
                        label577.ForeColor = Color.Black;

                        label577.Text = ADCThrottleBreak.ToString();
                        if (checkBox71.Checked)
                            label534.Text = Preas2ADC.ToString();
                        //                      else
                        //                            label534.Text = BreakTMP.ToString();
                    }




                    label625.Text = HallErrCnt.ToString();

                    label4.Text = V8.ToString();
                    label8.Text = V9.ToString();
                    label10.Text = V10.ToString();



                    DataShown = true;

                    //DataRequest();

                    break;

                case 8:
                    int i = 0;
                    ushort Tmp;
                    for (i = 1; i < 124; i++)
                    {
                        Tmp = (ushort)PacketRec[i * 2];
                        Tmp = (ushort)(Tmp + (PacketRec[i * 2 + 1] * 256));
                        if (checkBox2.Checked)
                            chart1.Series[10].Points.Add(Tmp);
                    }
                    break;


                case 9:
                    for (i = 1; i < 124; i++)
                    {
                        Tmp = (ushort)PacketRec[i * 2];
                        Tmp = (ushort)(Tmp + (PacketRec[i * 2 + 1] * 256));
                        if (checkBox3.Checked)
                            chart1.Series[9].Points.Add(Tmp);
                    }
                    break;
                case 19:
                    for (i = 1; i < 124; i++)
                    {
                        Tmp = (ushort)PacketRec[i * 2];
                        Tmp = (ushort)(Tmp + (PacketRec[i * 2 + 1] * 256));
                        if (checkBox4.Checked)
                            chart1.Series[8].Points.Add(Tmp);
                    }
                    break;
                case 20:
                    for (i = 1; i < 124; i++)
                    {
                        Tmp = (ushort)PacketRec[i * 2];
                        Tmp = (ushort)(Tmp + (PacketRec[i * 2 + 1] * 256));
                        if (checkBox5.Checked)
                            chart1.Series[7].Points.Add(Tmp);
                    }
                    break;

                case 25:
                    GraphSeries();
                    break;

                case 21:
                    label17.Text = SSID;
                    label19.Text = passwordWiFi;
                    break;

            }

        }

        private void label18_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox26.DataSource = new System.Globalization.CultureInfo[]{
                System.Globalization.CultureInfo.GetCultureInfo("ru-RU"),
                System.Globalization.CultureInfo.GetCultureInfo("en-US")
            };


            comboBox26.DisplayMember = "NativeName";
            comboBox26.ValueMember = "Name";


            if (!String.IsNullOrEmpty(Properties.Settings.Default.Language))
            {
                comboBox26.SelectedValue = Properties.Settings.Default.Language;
            }

        }

        private unsafe void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown2.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            if (checkBox19.Checked)
            {

                sendbuf[0] = SEND_Kp;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);


            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_Kp;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }




        }

        private unsafe void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {

        }


        private unsafe void numericUpDown4_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown4.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_Ki;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_Ki;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }


        private void button3_Click(object sender, EventArgs e)
        {
            chart1.Series[0].Points.Clear();
            chart1.Series[1].Points.Clear();
            chart1.Series[2].Points.Clear();
            chart1.Series[3].Points.Clear();
            chart1.Series[4].Points.Clear();
            chart1.Series[5].Points.Clear();
            chart1.Series[6].Points.Clear();
            chart1.Series[7].Points.Clear();
            chart1.Series[8].Points.Clear();
            chart1.Series[9].Points.Clear();
            chart1.Series[10].Points.Clear();

            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_Clear;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_Clear;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

            CntTST = 0;



        }


        private unsafe void numericUpDown10_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown10.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_KGYRO;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_KGYRO;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (ShowSer == 1)
            {
                ShowSer = 0;
                button4.Text = MyStrings.Continue;
            }
            else
            {
                ShowSer = 1;
                button4.Text = MyStrings.ToStop;
            }
        }


        private void button5_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                sendbuf[0] = SEND_GetOptions;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetOptions;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }
        }

        public void Trm1()
        {
            if (serialPort1.IsOpen == false)
                return;
            for (int j = 0; j < TrmMass[2] + 4; j++)
            {
                try
                {
                    serialPort1.Write(TrmMass, j, 1);
                }
                catch (System.TimeoutException)//IOException e)
                {
                    _continue = 0;
                    try
                    {
                        serialPort1.Close();
                    }
                    catch (System.IO.IOException)
                    {
                    }
                    //                    MessageBox.Show("Ошибка передачи. Проверьте BlueTooth и откройте порт заново", "Ошибка", MessageBoxButtons.OK);
                    return;
                }
                catch (System.IO.IOException)
                {
                    _continue = 0;
                    try
                    {
                        serialPort1.Close();
                    }
                    catch (System.IO.IOException)
                    {
                    }
                    MessageBox.Show(MyStrings.ConnectionErr2, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                    return;
                }

            }
        }


        public void Trm()
        {
            if (!checkBox6.Checked)
            {
                if (serialPort1.IsOpen == false)
                    return;
                //    for (int j = 0; j < TrmMass[2] + 4; j++)
                {
                    try
                    {
                        serialPort1.Write(TrmMass, 0, (TrmMass[2] + 4));
                    }
                    catch (System.TimeoutException)//IOException e)
                    {
                        _continue = 0;
                        try
                        {
                            serialPort1.Close();
                        }
                        catch (System.IO.IOException)
                        {
                        }
                        //                    MessageBox.Show("Ошибка передачи. Проверьте BlueTooth и откройте порт заново", "Ошибка", MessageBoxButtons.OK);
                        return;
                    }
                    catch (System.IO.IOException)
                    {
                        _continue = 0;
                        try
                        {
                            serialPort1.Close();
                        }
                        catch (System.IO.IOException)
                        {
                        }
                        MessageBox.Show(MyStrings.ConnectionErr2, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                        return;
                    }

                }
            }
            else
            {





                //IPaddr = IPAddress.Parse("192.168.1.114");
                if (IPaddr != null)
                {
                    ep = new IPEndPoint(IPaddr, TrmPort);
                    //       s.SendBufferSize = 4;


                    byte[] sendbuf = new byte[TrmMass[2] + 4];
                    int i;
                    for (i = 0; i < TrmMass[2] + 4; i++)
                        sendbuf[i] = TrmMass[i];

                    s.SendTo(sendbuf, ep);
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_ProgrammOptions;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_ProgrammOptions;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }
        }

        private unsafe void Form1_KeyDown(object sender, KeyEventArgs e)
        {

        }



        private void button7_Click(object sender, EventArgs e)
        {
            if (MovingON == 1)
            {
                MovingON = 0;
            }
            else
            {
                MovingON = 1;
            }

        }

        private unsafe void Form1_KeyUp(object sender, KeyEventArgs e)
        {

        }

        private unsafe void numericUpDown14_ValueChanged(object sender, EventArgs e)
        {



        }

        private void checkBox12_CheckedChanged(object sender, EventArgs e)
        {


        }

        private unsafe void numericUpDown15_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown15.Value);

            switch (comboBox25.SelectedIndex)
            {
                case 0:
                    Trmm = (short)(Trmm * 2);
                    break;
                case 1:
                    Trmm = (short)(Trmm * 4);
                    break;
                case 2:
                    Trmm = (short)(Trmm * 8);
                    break;
            }





            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_PWM1;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_PWM1;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }
        }

        private unsafe void numericUpDown12_ValueChanged(object sender, EventArgs e)
        {


        }

        private unsafe void numericUpDown16_ValueChanged(object sender, EventArgs e)
        {



        }

        private unsafe void numericUpDown17_ValueChanged(object sender, EventArgs e)
        {


        }

        private void button8_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show(
                MyStrings.GyroCalibr,
        MyStrings.GyroCalibrTittle, MessageBoxButtons.YesNo,
        MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
            if (result == DialogResult.Yes)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                if (checkBox19.Checked)
                {
                    sendbuf[0] = SEND_CalibrGyro;
                    s.SendTo(sendbuf, ep);
                }
                else
                {
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 1;//N
                    TrmMass[3] = SEND_CalibrGyro;
                    TrmMass[4] = CalcCheckSummTrm();
                    Trm();
                }
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show(
        MyStrings.AccCalibrate,
        MyStrings.GyroCalibrTittle, MessageBoxButtons.YesNo,
        MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
            if (result == DialogResult.Yes)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                if (checkBox19.Checked)
                {
                    sendbuf[0] = SEND_CalibrAcc;
                    s.SendTo(sendbuf, ep);
                }
                else
                {
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 1;//N
                    TrmMass[3] = SEND_CalibrAcc;
                    TrmMass[4] = CalcCheckSummTrm();
                    Trm();
                }
            }
        }



        private unsafe void numericUpDown19_ValueChanged(object sender, EventArgs e)
        {
            // short* TmpShort;
            // short Trmm = Decimal.ToInt16(numericUpDown19.Value);
            // byte[] sendbuf = new byte[sizeof(short) + 2];
            // if (checkBox19.Checked)
            // {
            // sendbuf[0] = SEND_StartRot;
            // fixed (byte* p = &sendbuf[2])
            // {
            //     TmpShort = (short*)p;
            //     *TmpShort = Trmm;
            // }

            // s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_StartRot;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}     
        }

        private unsafe void numericUpDown20_ValueChanged(object sender, EventArgs e)
        {
            // short* TmpShort;
            // short Trmm = Decimal.ToInt16(numericUpDown20.Value);
            // byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            // {
            // sendbuf[0] = SEND_KpRot;
            // fixed (byte* p = &sendbuf[2])
            // {
            //     TmpShort = (short*)p;
            //     *TmpShort = Trmm;
            // }

            // s.SendTo(sendbuf, ep);
            // }
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_KpRot;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}     
        }

        private unsafe void numericUpDown21_ValueChanged(object sender, EventArgs e)
        {
            // short* TmpShort;
            // short Trmm = Decimal.ToInt16(numericUpDown21.Value);
            // byte[] sendbuf = new byte[sizeof(short) + 2];
            // if (checkBox19.Checked)
            // {
            // sendbuf[0] = SEND_KFilterPrev;
            // fixed (byte* p = &sendbuf[2])
            // {
            //     TmpShort = (short*)p;
            //     *TmpShort = Trmm;
            // }

            // s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_KFilterPrev;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}     
        }

        private unsafe void numericUpDown22_ValueChanged(object sender, EventArgs e)
        {
            //  short* TmpShort;
            //  short Trmm = Decimal.ToInt16(numericUpDown22.Value);
            //  byte[] sendbuf = new byte[sizeof(short) + 2];
            //  if (checkBox19.Checked)
            //  {
            //  sendbuf[0] = SEND_KdRot;
            //  fixed (byte* p = &sendbuf[2])
            //  {
            //      TmpShort = (short*)p;
            //      *TmpShort = Trmm;
            //  }

            //  s.SendTo(sendbuf, ep);
            //}
            // else
            // {
            //     TrmMass[0] = 0xff;
            //     TrmMass[1] = 0xff;
            //     TrmMass[2] = 3;//N
            //     TrmMass[3] = SEND_KdRot;
            //     TrmMass[4] = (byte)Trmm;
            //     TrmMass[5] = (byte)(Trmm >> 8);
            //     TrmMass[6] = CalcCheckSummTrm();
            //     Trm();
            // }     
        }

        private unsafe void numericUpDown23_ValueChanged(object sender, EventArgs e)
        {
            //short* TmpShort;
            //short Trmm = Decimal.ToInt16(numericUpDown23.Value);
            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            //{
            //    sendbuf[0] = SEND_KiRot;
            //    fixed (byte* p = &sendbuf[2])
            //    {
            //        TmpShort = (short*)p;
            //        *TmpShort = Trmm;
            //    }

            //    s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_KiRot;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}     

        }

        private unsafe void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //short* TmpShort;
            //short Trmm = Decimal.ToInt16(comboBox1.SelectedIndex);

            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            //{
            //    sendbuf[0] = SEND_CurrLimit;
            //    fixed (byte* p = &sendbuf[2])
            //    {
            //        TmpShort = (short*)p;
            //        *TmpShort = Trmm;
            //    }

            //    s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_CurrLimit;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}
        }



        private void checkBox14_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox14.Checked)
                    sendbuf[0] = SEND_DirectMotor;
                else
                    sendbuf[0] = SEND_NotDirectMotor;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox14.Checked)
                {
                    //  numericUpDown15.Value = 0;
                    TrmMass[3] = SEND_DirectMotor;
                }
                else
                    TrmMass[3] = SEND_NotDirectMotor;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown26_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown26.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_YLimit;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_YLimit;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }
        }

        private unsafe void numericUpDown25_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown25.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_XLimit;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_XLimit;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void label34_Click(object sender, EventArgs e)
        {

        }

        private void label36_Click(object sender, EventArgs e)
        {

        }

        private void label40_Click(object sender, EventArgs e)
        {

        }

        private void label42_Click(object sender, EventArgs e)
        {

        }

        private unsafe void numericUpDown27_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown27.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_UBatLow;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_UBatLow;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button10_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_SbrosOdometra;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_SbrosOdometra;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }


        }

        private void checkBox15_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox15.Checked)
                    sendbuf[0] = SEND_Beep_10m;
                else
                    sendbuf[0] = SEND_No_Beep_10m;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox15.Checked)
                    TrmMass[3] = SEND_Beep_10m;
                else
                    TrmMass[3] = SEND_No_Beep_10m;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void label79_Click(object sender, EventArgs e)
        {

        }

        private void label78_Click(object sender, EventArgs e)
        {

        }

        private unsafe void numericUpDown28_ValueChanged(object sender, EventArgs e)
        {
            // short* TmpShort;
            // short Trmm = Decimal.ToInt16(numericUpDown28.Value);
            // byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            // {
            // sendbuf[0] = SEND_KpBack;
            // fixed (byte* p = &sendbuf[2])
            // {
            //     TmpShort = (short*)p;
            //     *TmpShort = Trmm;
            // }

            // s.SendTo(sendbuf, ep);
            // }
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_KpBack;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}     
        }

        private unsafe void numericUpDown29_ValueChanged(object sender, EventArgs e)
        {
            // short* TmpShort;
            // short Trmm = Decimal.ToInt16(numericUpDown29.Value);
            // byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            // {
            // sendbuf[0] = SEND_TiltBackLimit;
            // fixed (byte* p = &sendbuf[2])
            // {
            //     TmpShort = (short*)p;
            //     *TmpShort = Trmm;
            // }

            // s.SendTo(sendbuf, ep);
            // }
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_TiltBackLimit;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}     

        }

        private unsafe void numericUpDown30_ValueChanged(object sender, EventArgs e)
        {
            // short* TmpShort;
            // short Trmm = Decimal.ToInt16(numericUpDown30.Value);
            // byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            // {
            // sendbuf[0] = SEND_SpeedLimit2;
            // fixed (byte* p = &sendbuf[2])
            // {
            //     TmpShort = (short*)p;
            //     *TmpShort = Trmm;
            // }

            // s.SendTo(sendbuf, ep);
            // }
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_SpeedLimit2;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }



        private void numericUpDown165_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown165.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_TemperatureMaxIN_H;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown170_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown170.Value);



            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_Spd0TimerConst;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void radioButton13_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (radioButton13.Checked)
            {
                TrmMass[4] = SEND_FillCurrentMassOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void radioButton14_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (radioButton14.Checked)
            {
                TrmMass[4] = SEND_FillSinMassOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void radioButton15_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (radioButton15.Checked)
            {
                TrmMass[4] = SEND_FillMassOff;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button47_Click(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_BuzzerOnOff;
            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void button49_Click(object sender, EventArgs e)
        {
        }

        private void button48_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show(
        MyStrings.WheelCanTurn,
        MyStrings.GyroCalibrTittle, MessageBoxButtons.YesNo,
        MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
            if (result == DialogResult.Yes)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_AutoNastroyka;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();

                comboBox3.SelectedIndex = 5;
                comboBox4.SelectedIndex = 6;
                chart1.Series[0].Points.Clear();
                chart1.Series[1].Points.Clear();




                //F2 = new Form2(new MyDelegate(func));
                //F2.Owner = this;


                //Form F2 = new Form2(new MyDelegate(func));
                //F2.Owner = this;
                F2.ShowDialog();
                //  F2.Show();


            }
        }

        private void checkBox85_CheckedChanged(object sender, EventArgs e)
        {

            /*        if (checkBox85.Checked)
                    {

                        DialogResult result = MessageBox.Show(
                    "Неправильное задание сдвига фазы может привести к выходу контроллера или двигателя из строя. Это не является гарантийным случаем. Продолжить?",
                    "ВАЖНО!!!", MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
                        if (result == DialogResult.Yes)
                        {

                            TrmMass[0] = 0xff;
                            TrmMass[1] = 0xff;
                            TrmMass[2] = 2;//N
                            TrmMass[3] = SEND_SecondCMD;
                                TrmMass[4] = SEND_CW_CCW_AnyProfileOn;
                                label455.ForeColor = Color.Red;
                                label456.ForeColor = Color.Red;
                                label457.ForeColor = Color.Red;
                                label459.ForeColor = Color.Red;
                                numericUpDown115.ForeColor = Color.Red;
                                numericUpDown116.ForeColor = Color.Red;

                            TrmMass[5] = CalcCheckSummTrm();
                            Trm();
                        }
                        else
                            checkBox85.Checked = false;
                    }
                    else
                    {
                        TrmMass[0] = 0xff;
                        TrmMass[1] = 0xff;
                        TrmMass[2] = 2;//N
                        TrmMass[3] = SEND_SecondCMD;
                            TrmMass[4] = SEND_CW_CCW_AnyProfileOff;
                            label455.ForeColor = Color.Black;
                            label456.ForeColor = Color.Black;
                            label457.ForeColor = Color.Black;
                            label459.ForeColor = Color.Black;
                            numericUpDown115.ForeColor = Color.Black;
                            numericUpDown116.ForeColor = Color.Black;

                        TrmMass[5] = CalcCheckSummTrm();
                        Trm();

                    }*/



            if (checkBox85.Checked)
            {


                label455.ForeColor = Color.Red;
                label456.ForeColor = Color.Red;
                label457.ForeColor = Color.Red;
                label459.ForeColor = Color.Red;
                numericUpDown115.ForeColor = Color.Red;
                numericUpDown116.ForeColor = Color.Red;



                label648.ForeColor = Color.Red;
                label649.ForeColor = Color.Red;
                label650.ForeColor = Color.Red;
                label651.ForeColor = Color.Red;
                label653.ForeColor = Color.Red;


                numericUpDown171.ForeColor = Color.Red;
                numericUpDown172.ForeColor = Color.Red;
                numericUpDown173.ForeColor = Color.Red;



            }
            else
            {
                label455.ForeColor = Color.Black;
                label456.ForeColor = Color.Black;
                label457.ForeColor = Color.Black;
                label459.ForeColor = Color.Black;
                numericUpDown115.ForeColor = Color.Black;
                numericUpDown116.ForeColor = Color.Black;



                label648.ForeColor = Color.Black;
                label649.ForeColor = Color.Black;
                label650.ForeColor = Color.Black;
                label651.ForeColor = Color.Black;
                label653.ForeColor = Color.Black;


                numericUpDown171.ForeColor = Color.Black;
                numericUpDown172.ForeColor = Color.Black;
                numericUpDown173.ForeColor = Color.Black;




            }











        }

        private void label516_Click(object sender, EventArgs e)
        {

        }

        private void checkBox86_CheckedChanged(object sender, EventArgs e)
        {
            /*          byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                      TrmMass[0] = 0xff;
                      TrmMass[1] = 0xff;
                      TrmMass[2] = 2;//N
                      TrmMass[3] = SEND_SecondCMD;
                      if (checkBox86.Checked)
                          TrmMass[4] = SEND_KZPhasesOn;
                      else
                          TrmMass[4] = SEND_KZPhasesOff;

                      TrmMass[5] = CalcCheckSummTrm();
                      Trm();
          */
        }

        private void radioButton16_CheckedChanged(object sender, EventArgs e)
        {
            /*if (radioButton16.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_KZPhasesOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }*/
        }

        private void radioButton17_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton17.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_Mgnovenniy;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void radioButton18_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton18.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_KZ_Mgnovenniy_Off;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button49_Click_1(object sender, EventArgs e)
        {
            //  short Trmm = Decimal.ToInt16(numericUpDown174.Value);

            String Str = textBox1.Text;
            char ch;

            byte[] sendbuf = new byte[sizeof(short) + 2];
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_PINCODE;

            int i;
            for (i = 0; i < textBox1.Text.Length; i++)
            {
                ch = (char)Str[i];
                TrmMass[5 + i] = (byte)ch;
            }



            TrmMass[2] = (byte)(2 + i);//N


            TrmMass[5 + i] = CalcCheckSummTrm();


            Trm();

        }

        private void radioButton19_CheckedChanged(object sender, EventArgs e)
        {
            //if (DoNotSendCmd != 0)
            //  return;
            if (radioButton19.Checked)
            {

                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_X1;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
                //DoNotSendCmd = 10;
            }

        }

        private void checkBox91_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox91.Checked)
                TrmMass[4] = SEND_JOYSTICKOn;
            else
                TrmMass[4] = SEND_JOYSTICKOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox92_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox92.Checked)
                TrmMass[4] = SEND_JOYSTICKCalibrOn;
            else
                TrmMass[4] = SEND_JOYSTICKCalibrOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();


        }

        private void checkBox93_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox93.Checked)
                TrmMass[4] = SEND_CHANGE_AXISOn;
            else
                TrmMass[4] = SEND_CHANGE_AXISOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown183_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown183.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpKp;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox94_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox94.Checked)
                TrmMass[4] = SEND_IRFP4110On;
            else
                TrmMass[4] = SEND_IRFP4110Off;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox20_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void numericUpDown185_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown185.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CurrentMaxCurrentOnly;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void radioButton22_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton22.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_CurrentControlOnly;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void numericUpDown189_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown189.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_LightSensorThresholdLo;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void numericUpDown187_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown187.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_LightSensorThresholdHi;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void button52_Click(object sender, EventArgs e)
        {

        }



        private void comboBox20_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox20.SelectedIndex);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_LightMode;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown184_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown184.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_ThrottleLevelUpOff;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();

        }

        private void button51_Click(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CalibrateJOYSTICK;
            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown182_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown182.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_JoistickDeadZone;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();

        }

        private void radioButton21_CheckedChanged(object sender, EventArgs e)
        {
            //    if (DoNotSendCmd != 0)
            //      return;
            if (radioButton21.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_2WDMaster;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
                //DoNotSendCmd = 10;
            }
        }

        private void radioButton20_CheckedChanged(object sender, EventArgs e)
        {
            //if (DoNotSendCmd != 0)
            //  return;
            if (radioButton20.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_2WDSlave;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
                //DoNotSendCmd = 10;
            }
        }

        private void checkBox90_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox90.Checked)
                TrmMass[4] = SEND_TrapezoidaWhenBigCurrentOn;
            else
                TrmMass[4] = SEND_TrapezoidaWhenBigCurrentOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown181_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown181.Value);

            Trmm = Trmm / CurrPerDigit;


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_ChagerCurr;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown177_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown177.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_P_Curr;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown178_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown178.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_I_Curr;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown179_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown179.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_P_U;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown180_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown180.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_I_U;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown176_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown176.Value);


            Trmm = Trmm / CurrPerDigit;


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_BigCurrent;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void checkBox86_CheckedChanged_1(object sender, EventArgs e)
        {
            /*
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox86.Checked)
            {
                TrmMass[4] = SEND_BothBreaksOn;
            }
            else
            {
                TrmMass[4] = SEND_BothBreaksOff;
            }

            TrmMass[5] = CalcCheckSummTrm();
            Trm();
            */
            /*if (checkBox86.Checked)
            {
                MessageBox.Show("Функция пока не поддерживается", "Информация", MessageBoxButtons.OK);
                checkBox86.Checked = false;
            }*/
        }

        private void checkBox87_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox87.Checked)
                TrmMass[4] = SEND_GAZ_IMMITATOROn;
            else
                TrmMass[4] = SEND_GAZ_IMMITATOROff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown174_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown174.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_GazImm;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox88_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox88.Checked)
                textBox2.Enabled = true;
            else
                textBox2.Enabled = false;
        }

        private void button50_Click(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_RESET_PASSWORD;
            TrmMass[5] = CalcCheckSummTrm();


            Trm();

        }

        private void checkBox89_CheckedChanged(object sender, EventArgs e)
        {







            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox89.Checked)
            {
                if (checkBox82.Checked)
                    MessageBox.Show(MyStrings.RestartSin2, MyStrings.Inform, MessageBoxButtons.OK);
                TrmMass[4] = SEND_ChagerViaMotorOn;
            }
            else
                TrmMass[4] = SEND_ChagerViaMotorOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

            CntNoChange = 10;

        }

        private void numericUpDown175_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown175.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_Kd;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox85_CheckStateChanged(object sender, EventArgs e)
        {
            //MessageBox.Show("You are in the CheckBox.CheckStateChanged event.");
        }

        private void checkBox85_MouseClick(object sender, MouseEventArgs e)
        {

            if (checkBox85.Checked)
            {

                DialogResult result = MessageBox.Show(
            MyStrings.WrongShift,
            MyStrings.GyroCalibrTittle, MessageBoxButtons.YesNo,
            MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
                if (result == DialogResult.Yes)
                {

                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 2;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_CW_CCW_AnyProfileOn;
                    label455.ForeColor = Color.Red;
                    label456.ForeColor = Color.Red;
                    label457.ForeColor = Color.Red;
                    label459.ForeColor = Color.Red;
                    numericUpDown115.ForeColor = Color.Red;
                    numericUpDown116.ForeColor = Color.Red;



                    label648.ForeColor = Color.Red;
                    label649.ForeColor = Color.Red;
                    label650.ForeColor = Color.Red;
                    label651.ForeColor = Color.Red;
                    label653.ForeColor = Color.Red;


                    numericUpDown171.ForeColor = Color.Red;
                    numericUpDown172.ForeColor = Color.Red;
                    numericUpDown173.ForeColor = Color.Red;





                    TrmMass[5] = CalcCheckSummTrm();
                    Trm();
                }
                else
                    checkBox85.Checked = false;
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_CW_CCW_AnyProfileOff;
                label455.ForeColor = Color.Black;
                label456.ForeColor = Color.Black;
                label457.ForeColor = Color.Black;
                label459.ForeColor = Color.Black;
                numericUpDown115.ForeColor = Color.Black;
                numericUpDown116.ForeColor = Color.Black;



                label648.ForeColor = Color.Black;
                label649.ForeColor = Color.Black;
                label650.ForeColor = Color.Black;
                label651.ForeColor = Color.Black;
                label653.ForeColor = Color.Black;


                numericUpDown171.ForeColor = Color.Black;
                numericUpDown172.ForeColor = Color.Black;
                numericUpDown173.ForeColor = Color.Black;










                TrmMass[5] = CalcCheckSummTrm();
                Trm();

            }
        }

        private void numericUpDown173_ValueChanged(object sender, EventArgs e)
        {
            if ((numericUpDown173.Value < 10) && (numericUpDown173PrevValue >= 10))
                numericUpDown173.Value = 0;


            if ((numericUpDown173.Value > 0) && (numericUpDown173PrevValue == 0))
                numericUpDown173.Value = 10;




            numericUpDown173PrevValue = Decimal.ToInt16(numericUpDown173.Value);


            short Trmm = Decimal.ToInt16(numericUpDown173.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_HallDelayMaxSPD;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown172_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown172.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_HallDelay1MaxSPD_F;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown171_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown171.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_HallDelay1MaxSPD_B;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown168_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown168.Value);


            Trmm = Trmm / CurrPerDigit;


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_CurrPhaseLimitSpd0;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown169_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown169.Value);


            Trmm = Trmm / CurrPerDigit;

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_CurrUstSpd0;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox19_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox19.SelectedIndex);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_CurrLimitSpd0;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox18_SelectionChangeCommitted(object sender, EventArgs e)
        {
            //CurrSensor

            short Trmm = Decimal.ToInt16(comboBox18.SelectedIndex);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CurrSensor;// CurrLimit;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

            /*
            switch (comboBox18.SelectedIndex)
            {
                case 0:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("26A");
                    comboBox1.Items.Add("34A");
                    comboBox1.Items.Add("42A");
                    comboBox1.Items.Add("50A");
                    comboBox1.Items.Add("58A");
                    comboBox1.Items.Add("65A");
                    comboBox1.Items.Add("74A");
                    comboBox1.Items.Add("81A");
                    comboBox1.Items.Add("89A");
                    comboBox1.Items.Add("97A");
                    comboBox1.Items.Add("104A");
                    comboBox1.Items.Add("113A");
                    comboBox1.Items.Add("120A");
                    comboBox1.Items.Add("128A");
                    comboBox1.Items.Add("136A");

                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("26A");
                    comboBox19.Items.Add("34A");
                    comboBox19.Items.Add("42A");
                    comboBox19.Items.Add("50A");
                    comboBox19.Items.Add("58A");
                    comboBox19.Items.Add("65A");
                    comboBox19.Items.Add("74A");
                    comboBox19.Items.Add("81A");
                    comboBox19.Items.Add("89A");
                    comboBox19.Items.Add("97A");
                    comboBox19.Items.Add("104A");
                    comboBox19.Items.Add("113A");
                    comboBox19.Items.Add("120A");
                    comboBox19.Items.Add("128A");
                    comboBox19.Items.Add("136A");

                    CurrPerDigit = 48.34;



                    break;
                case 1:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("35A");
                    comboBox1.Items.Add("46A");
                    comboBox1.Items.Add("56A");
                    comboBox1.Items.Add("66A");
                    comboBox1.Items.Add("77A");
                    comboBox1.Items.Add("87A");
                    comboBox1.Items.Add("98A");
                    comboBox1.Items.Add("108A");
                    comboBox1.Items.Add("118A");
                    comboBox1.Items.Add("129A");
                    comboBox1.Items.Add("139A");
                    comboBox1.Items.Add("150A");
                    comboBox1.Items.Add("160A");
                    comboBox1.Items.Add("170A");
                    comboBox1.Items.Add("181A");


                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("35A");
                    comboBox19.Items.Add("46A");
                    comboBox19.Items.Add("56A");
                    comboBox19.Items.Add("66A");
                    comboBox19.Items.Add("77A");
                    comboBox19.Items.Add("87A");
                    comboBox19.Items.Add("98A");
                    comboBox19.Items.Add("108A");
                    comboBox19.Items.Add("118A");
                    comboBox19.Items.Add("129A");
                    comboBox19.Items.Add("139A");
                    comboBox19.Items.Add("150A");
                    comboBox19.Items.Add("160A");
                    comboBox19.Items.Add("170A");
                    comboBox19.Items.Add("181A");


                    CurrPerDigit = 64.45;


                    break;

                case 2:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("52A");
                    comboBox1.Items.Add("68A");
                    comboBox1.Items.Add("84A");
                    comboBox1.Items.Add("100A");
                    comboBox1.Items.Add("116A");
                    comboBox1.Items.Add("130A");
                    comboBox1.Items.Add("148A");
                    comboBox1.Items.Add("162A");
                    comboBox1.Items.Add("178A");
                    comboBox1.Items.Add("194A");
                    comboBox1.Items.Add("208A");
                    comboBox1.Items.Add("226A");
                    comboBox1.Items.Add("240A");
                    comboBox1.Items.Add("256A");
                    comboBox1.Items.Add("272A");


                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("52A");
                    comboBox19.Items.Add("68A");
                    comboBox19.Items.Add("84A");
                    comboBox19.Items.Add("100A");
                    comboBox19.Items.Add("116A");
                    comboBox19.Items.Add("130A");
                    comboBox19.Items.Add("148A");
                    comboBox19.Items.Add("162A");
                    comboBox19.Items.Add("178A");
                    comboBox19.Items.Add("194A");
                    comboBox19.Items.Add("208A");
                    comboBox19.Items.Add("226A");
                    comboBox19.Items.Add("240A");
                    comboBox19.Items.Add("256A");
                    comboBox19.Items.Add("272A");



                    CurrPerDigit = 96.68;


                    break;
                case 3:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("108A");
                    comboBox1.Items.Add("142A");
                    comboBox1.Items.Add("175A");
                    comboBox1.Items.Add("208A");
                    comboBox1.Items.Add("242A");
                    comboBox1.Items.Add("271A");
                    comboBox1.Items.Add("308A");
                    comboBox1.Items.Add("337A");
                    comboBox1.Items.Add("371A");
                    comboBox1.Items.Add("404A");
                    comboBox1.Items.Add("433A");
                    comboBox1.Items.Add("471A");
                    comboBox1.Items.Add("500A");
                    comboBox1.Items.Add("533A");
                    comboBox1.Items.Add("567A");


                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("108A");
                    comboBox19.Items.Add("142A");
                    comboBox19.Items.Add("175A");
                    comboBox19.Items.Add("208A");
                    comboBox19.Items.Add("242A");
                    comboBox19.Items.Add("271A");
                    comboBox19.Items.Add("308A");
                    comboBox19.Items.Add("337A");
                    comboBox19.Items.Add("371A");
                    comboBox19.Items.Add("404A");
                    comboBox19.Items.Add("433A");
                    comboBox19.Items.Add("471A");
                    comboBox19.Items.Add("500A");
                    comboBox19.Items.Add("533A");
                    comboBox19.Items.Add("567A");
                    break;
            }
            */
        }

        private void numericUpDown167_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown167.Value);


            Trmm = Trmm / CurrPerDigit;


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CurrPhaseLimit;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void label517_Click(object sender, EventArgs e)
        {

        }

        private void numericUpDown166_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown166.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_TemperatureMaxOUT_H;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void button11_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_GetErrors;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetErrors;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
                chart1.Series[10].Enabled = true;
            else
                chart1.Series[10].Enabled = false;

        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked)
                chart1.Series[9].Enabled = true;
            else
                chart1.Series[9].Enabled = false;

        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked)
                chart1.Series[8].Enabled = true;
            else
                chart1.Series[8].Enabled = false;

        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked)
                chart1.Series[7].Enabled = true;
            else
                chart1.Series[7].Enabled = false;

        }

        private void checkBox19_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (ShowPassword)
                ShowPassword = false;
            else
                ShowPassword = true;
        }

        private void button7_Click_1(object sender, EventArgs e)
        {
            int i, cntBytes = 8;
            String SSIDSet=textBox3.Text, passwordSet= textBox4.Text;

  /*          string str = comboBox6.Text;
            int n = str.LastIndexOf('.');
            str = str.Substring(0, n + 1);
            str = str + "255";

            IPAddress IP = IPAddress.Parse(str);
*/

            if (SSIDSet.Length==0)
            {
                MessageBox.Show("SSID is not set","error", MessageBoxButtons.OK);
                return;
            }



            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            //TrmMass[2] = 1;
            TrmMass[3] = 2;
            TrmMass[4] = 0;// (byte)IP.Address;
            TrmMass[5] = 0;//(byte)(IP.Address >> 8);
            TrmMass[6] = 0;//(byte)(IP.Address >> 16);
            TrmMass[7] = 0;//(byte)(IP.Address >> 24);




            TrmMass[cntBytes++] = (byte)SSIDSet.Length;
            for (i = 0; i < SSIDSet.Length; i++)
            {
                TrmMass[cntBytes++] = (byte)SSIDSet[i];
            }

            TrmMass[cntBytes++] = (byte)passwordSet.Length;
            for (i = 0; i < passwordSet.Length; i++)
            {
                TrmMass[cntBytes++] = (byte)passwordSet[i];
            }

            TrmMass[2] = (byte)(cntBytes-3);

            TrmMass[cntBytes] = CalcCheckSummTrm();
            Trm();









        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox6.Checked)
            {
                if (UDPThread == null)
                    UDPThread = new Thread(UDPRead);
                UDPThread.Start();


            }
            else
            {
                if (UDPThread != null)
                    if (UDPThread.IsAlive)
                    {
                        UDPThread.Abort();
                        UDPThread = null;
                    }

            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

            if (checkBox1.Checked)
            {
                saveFileDialog2.FileName = "";
                saveFileDialog2.ShowDialog();
                if (saveFileDialog2.FileName != "")
                {
                    LogFileString = saveFileDialog2.FileName;
                    sw = new StreamWriter(LogFileString, true, Encoding.ASCII);
                    sw.WriteLine(DateTime.Now);
                    sw.Write("N TiltAlong TiltAcross EpLog EiLog EdLog PWM Time");
                    sw.WriteLine("");
                    sw.Close();
                    HeaderOk = true;
                }

                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                if (checkBox1.Checked)
                    TrmMass[4] = SEND_LogOn;
                else
                    TrmMass[4] = SEND_LogOff;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();

                checkBox1.Enabled = false;
            }

        }

        private void COMPorts()
        {
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            comboBox2.Items.Clear();
            for (int i = 0; i < ports.Length; i++)
                comboBox2.Items.Add(ports[i]);
        }


        int OnConnect(int NumPort)
        {
            Thread readThread = new Thread(Read);

            if (!serialPort1.IsOpen)
            {
                serialPort1.PortName = comboBox2.Text;

                serialPort1.BaudRate = 38400;//9600;//
                serialPort1.ReadBufferSize = 1000000;

                serialPort1.Parity = Parity.None;
                serialPort1.DataBits = 8;
                serialPort1.StopBits = StopBits.One;
                serialPort1.Handshake = Handshake.None;

                serialPort1.ReadTimeout = 100;
                serialPort1.WriteTimeout = 100;



                try
                {
                    serialPort1.Open();
                }
                catch (IOException)
                {
                    _continue = 0;
                    try
                    {
                        serialPort1.Close();
                    }
                    catch (System.IO.IOException)
                    {
                    }
                    MessageBox.Show(MyStrings.CannotToConnect, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                    return 1;
                }

                _continue = 1;

                readThread.Start();

                MsgOpenPortCnt = 10;




                return 0;
            }
            else
                return 1;
        }



        public byte CalcCheckSummRec()
        {
            uint Summ = 0, j;
            byte n = (byte)(PacketRec[0] + 1);
            for (j = 0; j < n; j++)
                Summ = Summ + PacketRec[j];

            Summ = ~Summ;

            return (byte)Summ;

        }

        public byte CalcCheckSummTrm()
        {
            uint Summ = 0, j;
            byte n = (byte)(TrmMass[2] + 3);
            for (j = 2; j < n; j++)
                Summ = Summ + TrmMass[j];

            Summ = ~Summ;

            return (byte)Summ;

        }






        private /*static*/ void Read()
        {
            int BtRc = 0;




            while (_continue == 1)
            {
                RunningThread = true;

                //backgroundWorker


                try
                {
                    BtRc = 0;

                    if (serialPort1.IsOpen)
                    {
                        try
                        {
                            BtRc = serialPort1.ReadByte();
                        }
                        catch (System.ArgumentNullException)
                        {
                            //MessageBox.Show(e.ToString, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                        }
                        catch (System.IO.IOException)
                        {
                            _continue = 0;
                            try
                            {
                                serialPort1.Close();
                            }
                            catch (System.IO.IOException)
                            {
                            }
                            String str = MyStrings.TMout;
                            MessageBox.Show(str, "Error"/*MyStrings.ErrorMsg*/, MessageBoxButtons.OK);
                            //MessageBox.Show(MyStrings.TMout, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                            RunningThread = false;
                            return;
                        }

                    }
                    else
                    {
                        _continue = 0;
                        try
                        {
                            serialPort1.Close();
                        }
                        catch (System.IO.IOException)
                        {
                        }
                        MessageBox.Show(MyStrings.DisconnectedController, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                        RunningThread = false;
                        return;
                    }



                    CntSerialPort = 5;

                    if (!GettingPacket_FL)
                    {
                        if ((BtRc == BtRcPrev) && (BtRc == 0xff))
                        {
                            BtRcPrev = 0;
                            GettingPacket_FL = true;
                            CntRec = 0;
                        }
                        else
                        {
                            BtRcPrev = (byte)BtRc;
                        }
                    }
                    else
                    {
                        if (CntRec > 253)
                            GettingPacket_FL = false;
                        else
                        {
                            PacketRec[CntRec] = (byte)BtRc;
                            if (PacketRec[0] > 250)
                            {
                                GettingPacket_FL = false;
                            }
                            CntRec++;
                            if (CntRec > (PacketRec[0] + 1))
                            {
                                GettingPacket_FL = false;



                                if (CalcCheckSummRec() != PacketRec[PacketRec[0] + 1])
                                {
                                    //                                    CHK_Err = true;
                                }
                                else
                                {
                                    //                                    CHK_Err = false;
                                    RaspakHC05();


                                    //Есть пакет
                                }
                            }
                        }
                    }

                }
                catch (TimeoutException e)
                {
                    //          MessageBox.Show("Исключение. Связь с устройством потеряна. Проверьте BlueTooth и откройте порт заново", "Ошибка", MessageBoxButtons.OK);
                    //        _continue = 0;
                    //    serialPort1.Close();

                    String St = e.ToString();
                    int s = 3;
                    s++;


                }
            }

            RunningThread = false;


        }





        private void button12_Click(object sender, EventArgs e)
        {
            if (comboBox2.SelectedIndex != -1)
            {
                if (OnConnect(comboBox2.SelectedIndex) != 0)
                {
                    //backgroundWorker1->RunWorkerAsync( );//numberToCompute );
                    //this->button23->Enabled=false;
                    //this->comboBox1->Enabled=false;
                    //this->button24->Enabled=true;
                }
            }
            else
            {
                //MessageBox::Show(TEXT("Не выбран порт"), TEXT("Ошибка"),
                //MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
            }
        }

        private void button13_Click(object sender, EventArgs e)
        {
            _continue = 0;

            try
            {
                serialPort1.Close();
            }
            catch (System.IO.IOException)
            {
            }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            byte[] BtTrm = new byte[10];


            BtTrm[0] = 0x19;
            BtTrm[2] = 0x29;
            if (serialPort1.IsOpen)
                serialPort1.Write(BtTrm, 0, 1);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //backgroundWorker1.CancelAsync();
            _continue = 0;
            ShowSer = 0;
            while (RunningThread) ;
            try
            {
                serialPort1.Close();
            }
            catch (System.IO.IOException)
            {
            }

            if (UDPThread != null)
                if (UDPThread.IsAlive)
                {
                    UDPThread.Abort();
                    UDPThread = null;
                }



            Properties.Settings.Default.Language = comboBox26.SelectedValue.ToString();
            Properties.Settings.Default.Save();


        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (StartCNT != 0)
                StartCNT--;

            if (ShowPassword)
            {
                textBox4.PasswordChar = '\0';
                button2.Text = "Hide password";
            }
            else
            {
                button2.Text = "Show password";
                textBox4.PasswordChar = '*';
            }


            if (checkBox114.Checked)
            {
                label907.Enabled = true;
                label908.Enabled = true;
                numericUpDown240.Enabled = true;
            }
            else
            {
                label907.Enabled = false;
                label908.Enabled = false;
                numericUpDown240.Enabled = false;
            }

            if (checkBox110.Checked)
                panel57.Enabled = true;
            else
                panel57.Enabled = false;




            if (radioButton21.Checked)
                panel76.Enabled = true;
            else
                panel76.Enabled = false;


            if ((!CanChangePWM10kHz) && (CanChangePWM10kHzCnt == 0))
                CanChangePWM10kHz = true;

            if (CanChangePWM10kHzCnt > 0)
            {
                CanChangePWM10kHzCnt--;
                if (CanChangePWM10kHzCnt == 0)
                    CanChangePWM10kHz = true;

            }


            if ((radioButton7.Checked) && (!checkBox82.Checked))
            {
                //    checkBox81.Enabled = false;
                //    checkBox81.Text = "Жесткий режим";
                label799.Enabled = true;
                label800.Enabled = true;
                numericUpDown197.Enabled = true;
            }
            else
            {
                //   checkBox81.Enabled = true;
                //    checkBox81.Text="Сброс фильтра";
                label799.Enabled = false;
                label800.Enabled = false;
                numericUpDown197.Enabled = false;
            }



            if (comboBox18.SelectedIndex == 3)
                checkBox26.Enabled = false;
            else
                checkBox26.Enabled = true;



            //if (DoNotSendCmd != 0)
            //  DoNotSendCmd--;

            if (radioButton20.Checked || radioButton21.Checked)
            {
                checkBox91.Enabled = true;
                if (checkBox91.Checked)
                    checkBox93.Enabled = true;
            }
            else
            {
                checkBox91.Enabled = false;
                if (!checkBox91.Checked)
                    checkBox93.Enabled = false;
            }

            if (checkBox99.Checked)
                checkBox74.Enabled = false;
            else
                checkBox74.Enabled = true;


            if ((Flgs5 & 0x00008) == 0x00008)
                if (CanShowMsgChargingComplete)
                {
                    CanShowMsgChargingComplete = false;
                    MessageBox.Show(MyStrings.ChargingCompleted, MyStrings.Inform, MessageBoxButtons.OK);
                }

            if (checkBox89.Checked)
                if ((Flgs5 & 0x00008) != 0x00008)
                    CanShowMsgChargingComplete = true;

            if (CntNoChange != 0)
                CntNoChange--;

            if (checkBox82.Checked)
            {
                label473.Enabled = false;
                comboBox1.Enabled = false;
            }
            else
            {
                label473.Enabled = true;
                comboBox1.Enabled = true;
            }

            DataShownCnt++;
            if (DataShownCnt > 50)
                DataShown = true;

            if ((!checkBox25.Checked) && (DataShown))
            {
                DataShown = false;
                DataRequest();
                DataShownCnt = 0;

            }



            if (TmrLocked != 0)
            {
                TmrLocked--;
                if (TmrLocked == 0)
                    TmrLocked = 0;
            }
            if (MsgOpenPortCnt != 0)
            {
                MsgOpenPortCnt--;
                if (MsgOpenPortCnt == 0)
                {
                    if (serialPort1.IsOpen)
                    {
                        TmrLocked = 50;
                        TrmMass[0] = 0xff;
                        TrmMass[1] = 0xff;
                        TrmMass[2] = 1;//N
                        TrmMass[3] = SEND_GetOptionsWhenLock;
                        TrmMass[4] = CalcCheckSummTrm();
                        Trm();

                        MessageBox.Show(MyStrings.ConnectedController, MyStrings.Inform, MessageBoxButtons.OK);
                    }
                }

            }

            if (TimeOutLoadOptions1 != 0)
            {
                TimeOutLoadOptions1--;
                if (TimeOutLoadOptions1 == 0)
                {
                    MessageBox.Show(MyStrings.OptionsNotSaved + " (4)", MyStrings.ErrorMsg, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }

            if (TimeOutLoadOptions2 != 0)
            {
                TimeOutLoadOptions2--;
                if (TimeOutLoadOptions2 == 0)
                {
                    MessageBox.Show(MyStrings.OptionsNotSaved + " (5)", MyStrings.ErrorMsg, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }


            if (SaveTimeOut != 0)
            {
                SaveTimeOut--;
                if (SaveTimeOut == 0)
                    MessageBox.Show(MyStrings.OptionsNotSaved + " (6)", MyStrings.ErrorMsg, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            if (ConnectionCnt != 0)
            {
                ConnectionCnt--;
                if (ConnectionCnt == 0)
                {
                    toolStripStatusLabel1.Text = MyStrings.ControllerNotDetected;
                    toolStripStatusLabel1.ForeColor = Color.Red;
                    toolStripProgressBar1.ForeColor = Color.Red;
                    toolStripProgressBar1.Value = 100;
                }
            }
            if (serialPort1.IsOpen)
            {
                label264.Text = MyStrings.PortOpened;
                label264.ForeColor = Color.Green;
            }
            else
            {
                label264.Text = MyStrings.PortClosed;
                label264.ForeColor = Color.Red;
            }




            if (CntSerialPort != 0)
            {
                CntSerialPort--;
                if (CntSerialPort == 0)
                    GettingPacket_FL = false;
            }

            if (TmrCntDelay != 0)
            {
                TmrCntDelay--;
                if (TmrCntDelay == 0)
                {


                }
            }







        }
        private void RaspakHC05()
        {
            int Cnt = 2;
            int Tmp;

            switch (PacketRec[1])
            {
                case 22:
                    BMSTimeOt = PacketRec[39];

                    BMSTimeOt = BMSTimeOt << 8;
                    BMSTimeOt = BMSTimeOt + PacketRec[38];

                    SummOk = PacketRec[41];
                    SummOk = SummOk << 8;
                    SummOk = SummOk + PacketRec[40];

                    SummNOk = PacketRec[43];
                    SummNOk = SummNOk << 8;
                    SummNOk = SummNOk + PacketRec[42];

                    backgroundWorker1.ReportProgress(22);

                    break;
                case 200:
                    backgroundWorker1.ReportProgress(200);

                    break;
                case 5:
                    if (checkBox1.Checked)
                    {
                        //CntSamples = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //1
                        CntSamples++;
                        ushort N = (ushort)PacketRec[Cnt++];

                        short AccXFl, AccYFl, AccZFl, GyroXFl, GyroYFl, GyroZFl;

                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        AccXFl = (short)Tmp;
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        AccYFl = (short)Tmp;
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        AccZFl = (short)Tmp;
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        GyroXFl = (short)Tmp;
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        GyroYFl = (short)Tmp;
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        GyroZFl = (short)Tmp;



                        /*
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        
                        AlfaXRes = (short)Tmp;

                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        
                        AlfaYRes = (short)Tmp;

                        
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        EpLog = (short)Tmp;
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        EiLog = (short)Tmp;
                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        EdLog = (short)Tmp;

                        */

                        Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);
                        PWM1 = (short)Tmp;

                        //= PacketRec[Cnt++];
                        //Theta1CntPWMSND = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //1
                        //Phase1Period1Up = (ushort)(PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8));        //2
                        if ((LogFileString != null) && (HeaderOk))
                        {
                            sw = new StreamWriter(LogFileString, true, Encoding.ASCII);
                            if (PWM1 == 0)
                                sw.Write("Stopped : " + N + " ");
                            else
                                sw.Write("Running : " + N + " ");

                            sw.Write(AccXFl + " ");
                            sw.Write(AccYFl + " ");
                            sw.Write(AccZFl + " ");
                            sw.Write(GyroXFl + " ");
                            sw.Write(GyroYFl + " ");
                            sw.Write(GyroZFl + " ");
                            sw.Write(PWM1 + " ");
                            sw.Write(DateTime.Now.Hour + ":" + DateTime.Now.Minute + ":" + DateTime.Now.Millisecond);
                            sw.WriteLine("");
                            sw.Close();
                        }


                        backgroundWorker1.ReportProgress(25);
                        break;
                    }

                    CntSamples = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //1
                    AlfaXRes = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //2
                    AlfaYRes = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //3
                    GyroX = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //4
                    TiltXRes = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //5
                    //TiltYRes
                    LightSensor = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //6
                    Ep = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //7
                    Ei = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //8
                    PWM1 = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //9
                    Curr1 = (short)Tmp;

                    Cr1 = (double)Curr1 * CurrPerDigit;
                    short tt;
                    tt = (short)((short)PacketRec[Cnt++] + (((short)PacketRec[Cnt++]) << 8));        //10
                    Spd1USTKMH = ((float)tt) / 10;

                    //Cr2 = (double)Curr2 * CurrPerDigit;



                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //11
                    Temperature3 = (short)Tmp;

                    Odometr = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //12

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //13
                    Spd1Res = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //14
                    Temperature2 = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //15
                    Temperature1 = (float)(short)Tmp;


                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //16
                    Kp = (int)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);//PacketRec[Cnt++];        //17
                    UBT = ((float)Tmp) / 10;




                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //18
                    GyroVert_Steer = (short)Tmp;


                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //19
                    StatFlags = (short)Tmp;



                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //20
                    GyroZFilter = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //21
                    AlfaYResPrevAv = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //22
                    DiffBetweenTilts = (short)Tmp;

                    Flgs = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //23
                    Flgs1 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //24
                    Flgs2 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //25


                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //26
                    TiltZad = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //27
                    StartRot = (int)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //28
                    Ki = (int)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //29
                    KRot = (int)Tmp;


                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //30
                    KpRot = (int)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //31
                    KiRot = (int)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //32
                    Preas1ADC = (int)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //33
                    Preas2ADC = (int)Tmp;

                    CurrLimitTek = PacketRec[Cnt++];                                       //34

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //35
                    KpSPD = (int)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //36
                    AngleLimitReal = (int)Tmp;


                    CurrTuda1 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //37
                    CurrRegen1 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //38

                    Flgs4 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //39
                    Flgs5 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //40

                    Flgs3 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //41


                    TimerCnt = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //42

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //43
                    _3VFl = (float)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //44
                    _5VFl = (float)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //45
                    _12VFl = (float)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //46
                    CurrA_P = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //47
                    CurrA_N = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //48
                    CurrC_P = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //49
                    CurrC_N = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //50
                    V8 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //51
                    V9 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //52
                    V10 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //53
                    V11 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //54
                    V12 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //55
                    V13 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //56
                    V14 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //57
                    V15 = (uint)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //58
                    V16 = (uint)Tmp;
                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //59
                    V17 = (uint)Tmp;
                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //60
                    V18 = (uint)Tmp;

                    BatteryKeys = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //61


                    ChagerKeys = PacketRec[Cnt++];                                  //62

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);          //63
                    AccX = (short)Tmp;

                    FaultStatus1Res = (ushort)AccX;


                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);           //64
                    AccY = (short)Tmp;
                    VGSStatus2Res = (ushort)AccX;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);           //65
                    AccZ = (short)Tmp;

                    Sensor1_Prev = PacketRec[Cnt++];                                  //66
                    Sensor2_Prev = PacketRec[Cnt++];                                  //67

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //68
                    Temperature4 = (short)Tmp;

                    Distance = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);  //69

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //70
                    ProtectValue = (uint)Tmp;


                    Temperature = PacketRec[Cnt++];                                 //71
                    if ((Temperature & 0x80) == 0x80)
                    {
                        Temperature = (int)(((uint)Temperature) | 0xffffff00);
                    }


                    _48V = PacketRec[Cnt++];                                          //72
                    KAccGyroSteer = PacketRec[Cnt++];                                 //73


                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //74
                    GyroXFl = (short)Tmp;

                    double wt;
                    //= ((double)KdI) / (double)100;

                    // GyroXFl = ((double)GyroXFl);// * wt;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //75
                    GyroYFl = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //76
                    GyroZFl = (short)Tmp;


                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //77
                    Ed = (short)Tmp;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //78
                    GyroYAv = (short)Tmp;

                    wt = ((double)KdI) / (double)100;

                    //                    GyroYAv = ((double)GyroYAv);// * wt;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //79
                    KdI = (float)(short)Tmp;
                    KdI = KdI / 10;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //80
                    MaxSpdKMH = (short)Tmp;

                    PhasesCnt2 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //81



                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //82
                    Spd1Fl = (short)Tmp;

                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //83
                    Temperature5 = (short)Tmp;

                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //84
                    Temperature6 = (short)Tmp;

                    Phase1Period1 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //85
                    Phase1Period2 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //86
                    //Phase1Period3 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //87
                    EpCurr1 = (int)PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8) + (((int)PacketRec[Cnt++]) << 16) + (((int)PacketRec[Cnt++]) << 24);        //87
                    Phase1Period4 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //88
                    Phase1Period5 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //89
                    Phase1Period6 = (int)PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8) + (((int)PacketRec[Cnt++]) << 16) + (((int)PacketRec[Cnt++]) << 24);        //90
                    //Phase1PeriodTTL = Phase1Period1 + Phase1Period2 + Phase1Period3 + Phase1Period4 + Phase1Period5 + Phase1Period6;

                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //91
                    //CurrUstTek = (short)Tmp;
                    int u = (int)CurrPerDigit;
                    CurrUstTek = (int)(Tmp * u);

                    CriticalError = PacketRec[Cnt++];              //92

                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //93
                    //BreakTMP
                    Spd1UST_Tmp = (short)Tmp;

                    ECurr1Summ = (short)Tmp;



                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //94
                    ADCThrottleBreak = (ushort)Tmp;

                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //95
                    RCON_Mem = (ushort)Tmp;

                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //96
                    FirmwareVersion = (ushort)Tmp;


                    MPU6050Err = PacketRec[Cnt++];                                    //97

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //98
                    PhaseCurr = (short)Tmp;

                    PhaseCr = (double)PhaseCurr * CurrPerDigit;

                    Tmp = PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8);        //99
                    HallErrCnt = (ushort)Tmp;



                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //100
                    u = (int)CurrPerDigit;
                    CurrPhaseLimitTek = (int)(Tmp * u);


                    PhasePer1 = PacketRec[Cnt++] + (((uint)PacketRec[Cnt++]) << 8) + (((uint)PacketRec[Cnt++]) << 16) + (((uint)PacketRec[Cnt++]) << 24);        //101

                    Halls = PacketRec[Cnt++];                                       //102


                    HallDelay1_Tek_F = PacketRec[Cnt++];                             //103 

                    HallDelay1_Tek_B = PacketRec[Cnt++];                             //104


                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //105
                    EPID_Res = (short)Tmp;

                    BuzzerOnEvent = (ushort)PacketRec[Cnt++];                       //106


                    HallsLines = (byte)PacketRec[Cnt++];                          //107

                    Tmp = (PacketRec[Cnt++] + (((int)PacketRec[Cnt++]) << 8));        //108
                    Eid = (short)Tmp;

                    backgroundWorker1.ReportProgress(5);


                    break;
                case 6:
                    int Tm;
                    short Tm1;
                    Tm = PacketRec[3 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[2 + 1];
                    KpMustBe = Tm;

                    Tm = PacketRec[5 + 1];      //KpNoMan
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[4 + 1];
                    KpNoMan = Tm;

                    Tm = PacketRec[7 + 1];      //Kd
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[6 + 1];
                    KdMem = (short)Tm;

                    Tm = PacketRec[9 + 1];      //KiNoMan
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[8 + 1];
                    KiNoMan = Tm;

                    Tm = PacketRec[11 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[10 + 1];
                    KpKpSpd = (short)Tm;



                    But1Func = PacketRec[12 + 1];
                    But2Func = PacketRec[13 + 1];



                    Tm = PacketRec[15 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[14 + 1];
                    KGYRO = Tm;

                    Tm = PacketRec[17 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[16 + 1];
                    SensorLessTimerConst2 = (ushort)Tm;

                    Tm = PacketRec[19 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[18 + 1];
                    SenosrlessPWM1_2Const = (short)Tm;

                    Tm = PacketRec[21 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[20 + 1];
                    SensorLessTimerConstMin = (ushort)Tm;

                    Tm = PacketRec[23 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[22 + 1];
                    CalibrationGyroX = (short)Tm;

                    Tm = PacketRec[25 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[24 + 1];
                    CalibrationGyroY = (short)Tm;

                    Tm = PacketRec[27 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[26 + 1];
                    CalibrationGyroZ = (short)Tm;


                    Tm = PacketRec[29 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[28 + 1];
                    CalibrationAccX = (short)Tm;

                    Tm = PacketRec[31 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[30 + 1];
                    CalibrationAccY = (short)Tm;

                    Tm = PacketRec[33 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[32 + 1];
                    CalibrationAccZ = (short)Tm;


                    PhasePERMASS = PacketRec[35];
                    PhasePERMASS_SHFT = PacketRec[36];

                    HallDelay1_F = PacketRec[37];
                    HallDelay1_B = PacketRec[38];
                    But3Func = PacketRec[39];
                    But4Func = PacketRec[40];


                    Theta1Zero = PacketRec[41];
                    Theta2Zero = PacketRec[42];



                    Tm = PacketRec[43 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[42 + 1];
                    CurrLimit = Tm;


                    Tm = PacketRec[46];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[45];
                    ChagerCurr = (short)Tm;




                    Tm = PacketRec[47 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[46 + 1];
                    KpSPDReal = Tm;

                    Tm = PacketRec[49 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[48 + 1];
                    KdSPD = Tm;


                    Tm = PacketRec[51 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[50 + 1];
                    KiSPD = Tm;

                    Tm = PacketRec[53 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[52 + 1];
                    AngleLimitInt = Tm;

                    Tm = PacketRec[55 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[54 + 1];
                    SpeedLimit1 = Tm;

                    Tm = PacketRec[57 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[56 + 1];
                    StatFlags = Tm;

                    Tm = PacketRec[59 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[58 + 1];
                    XLimit = Tm;

                    Tm = PacketRec[61 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[60 + 1];
                    YLimit = Tm;


                    Tm = PacketRec[63 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[62 + 1];
                    UBatLow = Tm;

                    Tm = PacketRec[65 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[64 + 1];
                    CntMixedModeMax = Tm;


                    Tm = PacketRec[67 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[66 + 1];
                    MixedModeLevelOn = Tm;

                    SpeedLimit2 = PacketRec[68 + 1];
                    SpeedLimit3 = PacketRec[69 + 1];
                    I_Curr = PacketRec[70 + 1];


                    Tm = PacketRec[72 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[71 + 1];

                    CurrMixed = (int)(Tm * CurrPerDigit);



                    Tm = PacketRec[74 + 1];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[73 + 1];
                    KpMax = Tm;

                    SensorllessSpdThreshold = PacketRec[75 + 1];

                    SpdKpMax = PacketRec[77];

                    Tm = PacketRec[79];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[78];
                    MixedModeLevelOff = Tm;

                    Tm = PacketRec[81];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[80];
                    KpCurr = (int)Tm;

                    Tm = PacketRec[83];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[82];
                    Ki_PWM_Mode = (short)Tm;

                    P_U = PacketRec[84];
                    I_U = PacketRec[85];

                    Tm = PacketRec[87];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[86];
                    KpNoManOneLeg = (short)Tm;

                    Tm = PacketRec[89];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[88];
                    KiNoManOneLeg = (short)Tm;

                    Tm = PacketRec[91];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[90];
                    TiltZadAddNoManOneLeg = (short)Tm;


                    Tm = PacketRec[93];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[92];
                    MAX_PWM_MEM = Tm;


                    Tm = PacketRec[95];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[94];
                    KiTemperIN = Tm;

                    Tm = PacketRec[97];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[96];
                    KpTemperIN = Tm;

                    Tm = PacketRec[99];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[98];
                    KpTemperOUT = Tm;

                    //OneTwoLeg
                    Tm = PacketRec[101];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[100];
                    KiTemperOUT = Tm;


                    MAX_PWM_Revers = PacketRec[102];
                    MaxSpdRevers = PacketRec[103];



                    MixedModeSlowSpeed = PacketRec[104];
                    HallDelay1MaxSPD_B = PacketRec[105];


                    Tm = PacketRec[107];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[106];
                    StatFlgs3 = Tm;


                    Tm = PacketRec[109];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[108];
                    KiRotOneTwoLeg = Tm;

                    Tm = PacketRec[111];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[110];
                    AutoPID_On_CntConst = Tm / 250;


                    AutoPID_On_PWM = PacketRec[112];
                    AutoPID_On_Speed = PacketRec[113];


                    Tm = PacketRec[115];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[114];
                    Diametr1 = Tm;

                    Tm = PacketRec[117];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[116];
                    PhasesPerRev1 = Tm;

                    Tm = PacketRec[119];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[118];
                    UBatHi = (uint)Tm;

                    //Freshman
                    Tm = PacketRec[121];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[120];
                    BreakThresholdDn = (short)Tm;

                    Tm = PacketRec[123];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[122];
                    BreakThresholdUp = (short)Tm;

                    Tm = PacketRec[125];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[124];
                    KTemperatureSPDControl = (short)Tm;



                    Profile = PacketRec[126];
                    _3psnSwitchBtNotPressed = PacketRec[127];





                    _3psnSwitchBt3 = PacketRec[128];
                    _3psnSwitchBt4 = PacketRec[129];

                    Tm = PacketRec[131];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[130];
                    CurrPhaseLimit = (int)Tm;
                    CurrPhaseLimit = (int)((float)CurrPhaseLimit * CurrPerDigit);

                    HallDelay1MaxSPD_F = PacketRec[133];
                    /*Tm = Tm << 8;
                    Tm = Tm + PacketRec[132];
                    StartRotFreshmanL = Tm;
                    */

                    CurrSensor = PacketRec[132];


                    Tm = PacketRec[135];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[134];
                    u = (int)CurrPerDigit;
                    CurrUstSpd0 = (int)(Tm * u);

                    Tm = PacketRec[137];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[136];
                    CurrPhaseLimitSpd0 = Tm;
                    CurrPhaseLimitSpd0 = (int)((float)CurrPhaseLimitSpd0 * CurrPerDigit);




                    Tm = PacketRec[139];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[138];
                    CurrLimitSpd0 = Tm;

                    MaxAngleStopBreak = PacketRec[140];

                    ThrottleTmpChngMem = PacketRec[141];

                    Tm = PacketRec[143];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[142];
                    BeepPauseConstAlm = Tm;

                    Tm = PacketRec[145];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[144];
                    BzOnCntSeriaConstAlm = Tm;

                    CntSingleBeepAlm = PacketRec[146];

                    DiffAlfaConstL = PacketRec[147];
                    DiffAlfaConstH = PacketRec[148];

                    Tm = PacketRec[150];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[149];
                    ZeroCurr1 = Tm;

                    But5Func = PacketRec[152];

                    MaxSpdPID = PacketRec[151];


                    Tm = PacketRec[154];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[153];
                    Timer1Mem = (uint)Tm;


                    Tm = PacketRec[156];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[155];
                    Timer2Mem = (uint)Tm;

                    UseTmr = PacketRec[157];


                    Tm = PacketRec[159];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[158];
                    SerNumber = (uint)Tm;


                    //OneTwoLeg_1
                    Tm = PacketRec[161];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[160];
                    SensorlessCurrLimit = Tm;
                    //NullPointRot = Tm;

                    SlowStrtSpd = PacketRec[162];
                    AntiPolicePower = PacketRec[163];


                    Tm = PacketRec[165];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[164];
                    u = (int)CurrPerDigit;
                    SensorlessCurrUst = (int)(Tm * u);



                    Tm = PacketRec[167];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[166];
                    GyroZFlTurn = (short)Tm;


                    Tm = PacketRec[169];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[168];
                    Kp_PWM_Mode = (short)Tm;

                    Tm = PacketRec[171];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[170];
                    Spd0TimerConst = (ushort)Tm;

                    HallDelayMaxSPD = PacketRec[172];
                    _2WDMode = PacketRec[173];

                    Tm = PacketRec[175];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[174];
                    MAH = (ushort)Tm;

                    Tm = PacketRec[177];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[176];
                    SensorThreshold = (ushort)Tm;

                    Tm = PacketRec[179];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[178];
                    TiltZadState5 = Tm;

                    SpdRstSpeedLim = (ushort)PacketRec[180];

                    Tm = PacketRec[182];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[181];
                    SensorlessCntAlignConst = (short)Tm;

                    Tm = PacketRec[184];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[183];
                    SenosrlessPWM1_1Const = (short)Tm;

                    Tm = PacketRec[186];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[185];
                    StatFlags2 = (short)Tm;

                    Tm = PacketRec[188];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[187];
                    TemperatureMaxOUT = (short)Tm;

                    SpeedLimitSt4 = (ushort)PacketRec[189];


                    Tm = PacketRec[191];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[190];
                    StatFlags1 = Tm;

                    if ((StatFlags1 & 8) != 8)
                    {
                        Tm++;
                    }
                    Tm = PacketRec[193];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[192];
                    SensorLessTimerConst = (ushort)Tm;


                    Tm = PacketRec[195];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[194];
                    TemperatureMaxIN = (float)Tm;


                    Tm = PacketRec[197];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[196];
                    KdOneTwoLeg = (short)Tm;

                    Tm = PacketRec[199];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[198];
                    BigCurrent = (int)Tm;
                    BigCurrent = (int)(((double)BigCurrent) * CurrPerDigit);


                    P_Curr = PacketRec[200];

                    Tm = PacketRec[202];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[201];
                    JoystickCalibrX = (short)Tm;




                    KdAverage = PacketRec[202];

                    Tm = PacketRec[204];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[203];
                    SensorThresholdUp = (ushort)Tm;

                    Tm = PacketRec[206];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[205];
                    BreakThreshold = (ushort)Tm;

                    Tm = PacketRec[208];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[207];
                    KFirstBreak = (ushort)Tm;

                    TemperatureTYPE = PacketRec[209];
                    SensOrder1 = PacketRec[210];


                    Tm = PacketRec[212];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[211];
                    SensorlessSpdChngCntConst = (ushort)Tm;

                    Tm = PacketRec[214];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[213];
                    V_MIN_OFF = (short)Tm;

                    Tm = PacketRec[216];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[215];
                    V_MIN_Pre_OFF = (short)Tm;

                    Tm = PacketRec[218];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[217];
                    V_MIN_Sound = (short)Tm;

                    Tm = PacketRec[220];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[219];
                    V_min_OverV = (short)Tm;



                    Tm = PacketRec[222];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[221];
                    KiCurr = (short)Tm;

                    Tm = PacketRec[224];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[223];
                    u = (int)CurrPerDigit;
                    CurrUst = (int)(Tm * u);

                    KpKpMustBe = (short)PacketRec[225];
                    if (PacketRec[225] > 127)
                    {
                        KpKpMustBe = (short)(((int)KpKpMustBe) | 0xff00);
                    }



                    Tm = PacketRec[227];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[226];
                    ThrottleLevelUpOff = (short)Tm;


                    Tm = PacketRec[238];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[237];
                    //                    Sensor2ThresholdDn = (ushort)Tm;
                    TemperatureMaxIN_H = (ushort)Tm;


                    Tm = PacketRec[240];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[239];
                    //Sensor2ThresholdUp = (ushort)Tm;
                    TemperatureMaxOUT_H = (ushort)Tm;




                    Tm = PacketRec[242];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[241];
                    JoystickCalibrY = (short)Tm;

                    Tm = PacketRec[244];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[243];
                    JoistickDeadZone = (short)Tm;









                    //CurrUst = (short)Tm;






                    backgroundWorker1.ReportProgress(3);




                    break;
                case 7:
                    //short Tm1;

                    ErrOptions = PacketRec[2];

                    Tm = PacketRec[4];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[3];
                    AlfaXResErr = Tm;

                    Tm = PacketRec[6];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[5];
                    AlfaYResErr = Tm;

                    Tm = PacketRec[8];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[7];
                    SteerXErr = Tm;

                    Tm = PacketRec[10];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[9];
                    SteerYErr = Tm;

                    ErrorCode = PacketRec[11];

                    NoBalanceCode = PacketRec[12];

                    Tm = PacketRec[16];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[15];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[14];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[13];
                    FlgsErr = (uint)Tm;

                    Tm = PacketRec[20];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[19];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[18];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[17];
                    Flgs1Err = (uint)Tm;

                    Tm = PacketRec[22];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[21];
                    Tm1 = (short)Tm;
                    LastMainTiltAngleMnErr = (int)Tm1;

                    Tm = PacketRec[24];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[23];
                    Tm1 = (short)Tm;
                    LastSteerTiltAngleMnErr = (int)Tm1;

                    Tm = PacketRec[26];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[25];
                    Tm1 = (short)Tm;
                    TiltAngleAvMnErr = (int)Tm1;


                    MainTiltNumErr = PacketRec[27];

                    SteerTiltNumErr = PacketRec[28];


                    Tm = PacketRec[30];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[29];
                    StatFlgs = Tm;


                    Tm = PacketRec[32];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[31];
                    Tm1 = (short)Tm;
                    LastMainTiltAngleSteerErr = (int)Tm1;


                    Tm = PacketRec[34];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[33];
                    Tm1 = (short)Tm;
                    LastSteerTiltAngleSteerErr = (int)Tm1;

                    Tm = PacketRec[36];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[35];
                    Tm1 = (short)Tm;
                    TiltAngleAvSteerErr = (int)Tm1;


                    Tm = PacketRec[40];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[39];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[38];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[37];
                    Flgs2Err = (uint)Tm;


                    Tm = PacketRec[42];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[41];
                    Tm1 = (short)Tm;
                    BatErr = (ushort)Tm1;





                    backgroundWorker1.ReportProgress(4);
                    break;

                case 8:
                    backgroundWorker1.ReportProgress(8);
                    break;
                case 9:
                    backgroundWorker1.ReportProgress(9);
                    break;
                case 10:
                    for (int i = 0; i < (PacketRec[0] + 2); i++)
                        SaveOptionsMass[i] = PacketRec[i];
                    backgroundWorker1.ReportProgress(10);

                    break;
                case 11:
                    {
                        int i = 0;
                        for (i = SaveOptionsMass[0]; i < (PacketRec[0] + 2 + SaveOptionsMass[0]); i++)
                            SaveOptionsMass[i + 2] = PacketRec[i - SaveOptionsMass[0]];
                        backgroundWorker1.ReportProgress(11);
                        //SaveTimeOut = 0;
                    }
                    break;
                case 12:
                    backgroundWorker1.ReportProgress(12);

                    break;
                case 13:
                    backgroundWorker1.ReportProgress(13);
                    break;
                case 14:
                    backgroundWorker1.ReportProgress(14);
                    break;

                case 15:

                    Tm = PacketRec[3];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[2];
                    Class1.AutoNastroykaState = Tm;         //1

                    Tm = PacketRec[7];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[6];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[5];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[4];
                    Class1.Curr1SnTST = (int)Tm;            //2


                    Class1.TestSIN_Ok = PacketRec[8];        //3

                    Class1.TestSINOkMassCnt = PacketRec[9];        //4
                    Class1.SensOrder1 = PacketRec[10];        //5
                    Class1.InvSin = PacketRec[11];        //6


                    Tm = PacketRec[15];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[14];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[13];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[12];
                    Class1.Curr1SnTST_0 = (int)Tm;            //7

                    Tm = PacketRec[19];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[18];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[17];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[16];
                    Class1.Curr1SnTST = (int)Tm;            //8



                    Tm = PacketRec[21];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[20];
                    Class1.CntAutoNastroykaState257 = Tm;         //9


                    Tm = PacketRec[23];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[22];
                    Class1.SensorThresholdDn = Tm;         //10


                    Tm = PacketRec[25];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[24];
                    Class1.SensorThresholdUp = Tm;         //11


                    Tm = PacketRec[27];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[26];
                    Class1.BreakThresholdDn = Tm;         //12


                    Tm = PacketRec[29];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[28];
                    Class1.BreakThresholdUp = Tm;         //13


                    Class1.UBT_V = PacketRec[30];         //14


                    Tm = PacketRec[32];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[31];
                    Class1.PWM1_SIN_TST = Tm;         //15



                    Class1.bl = true;


                    //    backgroundWorker1.ReportProgress(15);


                    break;


                case 16:
                    LightMode = PacketRec[2];

                    Tm = PacketRec[4];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[3];
                    LightSensorThresholdLo = (ushort)Tm;

                    Tm = PacketRec[6];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[5];
                    LightSensorThresholdHi = (ushort)Tm;


                    CurrentMaxCurrentOnly = (ushort)PacketRec[7];


                    Tm = PacketRec[9];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[8];
                    K_PWM_Nastr = (ushort)Tm;

                    Tm = PacketRec[11];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[10];
                    DEADTIME_Si8233 = (ushort)Tm;

                    OCP_DEG = PacketRec[12];
                    VDS_LVL = PacketRec[13];


                    Crr1Corr = PacketRec[14];

                    Tm = PacketRec[16];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[15];
                    ButtonBreakOnlyPWM = (ushort)Tm;

                    Tm = PacketRec[18];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[17];
                    CntTurnOnConst = (ushort)Tm;

                    Tm = PacketRec[20];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[19];
                    CntTurnOffConst = (ushort)Tm;

                    TemperatureTYPE_FETs = PacketRec[21];

                    TstPhase = PacketRec[22];



                    Tm = PacketRec[24];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[23];
                    CurrPerDigit = (double)Tm;
                    CurrPerDigit = CurrPerDigit / 100;

                    Tm = PacketRec[26];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[25];
                    SpdStartLevel = (ushort)Tm;

                    Tm = PacketRec[28];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[27];
                    Ki_PWM_ModeOff = (ushort)Tm;


                    StrongModeSpdFilterOffMem = (ushort)PacketRec[29];


                    Tm = PacketRec[31];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[30];
                    RegenOffMem = (ushort)Tm;


                    Tm = PacketRec[33];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[32];
                    StatFlgs4 = (ushort)Tm;

                    KeyLightBrightness = (ushort)PacketRec[34];


                    Tm = PacketRec[36];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[35];
                    ButtonBreakOnlyTime = (ushort)Tm;

                    Tm = PacketRec[38];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[37];
                    BreakMonocycleSpd = (short)Tm;

                    KpKpDeadZoneMem = (ushort)PacketRec[39];

                    PWMSignal = (byte)PacketRec[40];




                    Tm = PacketRec[42];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[41];
                    KpSlowSpeed = (short)Tm;

                    SlowSpeedForKp = (byte)PacketRec[43];


                    Tm = PacketRec[45];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[44];
                    KiKpMustBe = (short)Tm;

                    KiKpDeadZoneMem = PacketRec[46];

                    Tm = PacketRec[48];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[47];
                    KiMax = (ushort)Tm;



                    Tm = PacketRec[50];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[49];
                    TimeDecreaseKi = (short)Tm;

                    TimeDecreaseKi = (short)(TimeDecreaseKi / 25);


                    Tm = PacketRec[52];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[51];
                    KpMin = (int)Tm;



                    Tm = PacketRec[54];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[53];
                    EpPWMmax = (ushort)Tm;


                    Tm = PacketRec[56];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[55];
                    EiPWMmax = (ushort)Tm;


                    Tm = PacketRec[58];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[57];
                    EdPWMmax = (ushort)Tm;


                    Tm = PacketRec[60];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[59];
                    DeadZoneHandleBarSegway = (ushort)Tm;

                    Tm = PacketRec[62];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[61];
                    KRotMustBe = (short)Tm;

                    Tm = PacketRec[64];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[63];
                    KpRotMustBe = (short)Tm;

                    Tm = PacketRec[66];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[65];
                    KiRotMustBe = (short)Tm;


                    GyroVertical = (byte)PacketRec[67];
                    HighSpeed = (short)PacketRec[68];
                    GoalSpeed = (short)PacketRec[69];


                    Tm = PacketRec[71];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[70];
                    StartRotHighSpeed = (short)Tm;

                    Tm = PacketRec[73];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[72];
                    KRotHighSpeed = (short)Tm;


                    Tm = PacketRec[75];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[74];
                    TimeHumanSensorOff = (ushort)Tm;

                    Tm = PacketRec[77];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[76];
                    KpKpZoneEnd = (short)Tm;

                    Tm = PacketRec[79];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[78];
                    KpKp2 = (short)Tm;

                    Tm = PacketRec[81];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[80];
                    KpKp2DeadZone = (short)Tm;

                    Tm = PacketRec[83];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[82];
                    KpKp2ZoneEnd = (short)Tm;

                    Tm = PacketRec[85];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[84];
                    PWMChangedThreshold = (ushort)Tm;

                    SpdKdMax = PacketRec[86];

                    Tm = PacketRec[88];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[87];
                    KdKpSpd = (short)Tm;

                    Tm = PacketRec[90];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[89];
                    KdMax = (short)Tm;

                    Tm = PacketRec[92];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[91];
                    KdMin = (short)Tm;

                    Tm = PacketRec[94];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[93];
                    KiKd = (short)Tm;

                    Tm = PacketRec[96];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[95];
                    VectorOnOffSpdLo = (short)Tm;

                    Tm = PacketRec[98];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[97];
                    VectorOnOffSpdHi = (short)Tm;


                    OnDelay = (ushort)PacketRec[99];

                    Tm = PacketRec[101];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[100];
                    KiUBTCoeff = (short)Tm;

                    SpdKiMin = (ushort)PacketRec[102];

                    Tm = PacketRec[104];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[103];
                    KiMin = (ushort)Tm;


                    Tm = PacketRec[106];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[105];
                    ELimitedMem = (ushort)Tm;

                    Tm = PacketRec[108];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[107];
                    KdNoManR = (short)Tm;


                    Tm = PacketRec[110];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[109];
                    KpDeadZone = (short)Tm;

                    StopIfPWM100Time = PacketRec[111];

                    CntKdSwitchCONST = PacketRec[112];

                    Tm = PacketRec[114];
                    Tm = Tm << 8;
                    Tm = Tm + PacketRec[113];
                    PWMSignalTimer = (short)Tm;

                    PWMkHz = PacketRec[115];



                    backgroundWorker1.ReportProgress(3);






                    break;



                case 17:
                    for (int i = 489; i < (489 + PacketRec[0] + 2); i++)
                        SaveOptionsMass[i] = PacketRec[i - 489];
                    backgroundWorker1.ReportProgress(17);
                    SaveTimeOut = 0;

                    break;

                case 18:
                    backgroundWorker1.ReportProgress(18);
                    break;
                case 19:
                    backgroundWorker1.ReportProgress(19);
                    break;
                case 20:
                    backgroundWorker1.ReportProgress(20);
                    break;

                case 21:

                    int SizeSSID = PacketRec[2];
                    int j;
                    SSID = null;


                    for (j = 0; j < SizeSSID; j++)
                    {
                        if (PacketRec[j + 3] != 0)
                            SSID = SSID + (char)PacketRec[j + 3];
                        else
                            j = SizeSSID;
                    }


                    int SizePasswordWiFi = PacketRec[3 + SizeSSID];

                    passwordWiFi = null;

                    for (j = 0; j < SizePasswordWiFi; j++)
                    {
                        if (PacketRec[j + 4 + SizeSSID] != 0)
                        {
                            if (ShowPassword)
                                passwordWiFi = passwordWiFi + (char)PacketRec[j + 4 + SizeSSID];
                            else
                                passwordWiFi = passwordWiFi + '*';
                        }
                        else
                            j = SizePasswordWiFi;
                    }



                    backgroundWorker1.ReportProgress(21);
                    break;


            }


        }

        private void button15_Click(object sender, EventArgs e)
        {
            chart1.Series[0].Points.Clear();
            chart1.Series[1].Points.Clear();
            chart1.Series[2].Points.Clear();
            chart1.Series[3].Points.Clear();
            chart1.Series[4].Points.Clear();
            chart1.Series[5].Points.Clear();
            chart1.Series[6].Points.Clear();
            chart1.Series[7].Points.Clear();
            chart1.Series[8].Points.Clear();
            chart1.Series[9].Points.Clear();
            chart1.Series[10].Points.Clear();


            CntSamples = 0;
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");

            sendbuf[0] = SEND_Clear;
  //          s.SendTo(sendbuf, ep);

            CntTST = 0;


        }

        private void button16_Click(object sender, EventArgs e)
        {
            /*        if (ShowSer == 1)
                    {
                        ShowSer = 0;
                        button16.Text = "Продолжить";
                    }
                    else
                    {
                        ShowSer = 1;
                        button16.Text = "Остановить";
                    }
                    */
        }

        private unsafe void numericUpDown13_ValueChanged(object sender, EventArgs e)
        {


        }

        private void checkBox20_CheckedChanged(object sender, EventArgs e)
        {


        }

        private void checkBox21_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button17_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_ClearErrors;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_ClearErrors;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button18_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_WriteErrors;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_WriteErrors;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }


        private unsafe void numericUpDown46_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown46.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            if (checkBox19.Checked)
            {

                sendbuf[0] = SEND_KpNoManOneLeg;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);


            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_KpNoManOneLeg;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }



        }

        private unsafe void numericUpDown42_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown42.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            if (checkBox19.Checked)
            {

                sendbuf[0] = SEND_TiltZadAddNoManOneLeg;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);


            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_TiltZadAddNoManOneLeg;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }



        }

        private unsafe void numericUpDown44_ValueChanged(object sender, EventArgs e)
        {



        }

        private unsafe void numericUpDown41_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown41.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            if (checkBox19.Checked)
            {

                sendbuf[0] = SEND_KiNoManOneLeg;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);


            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_KiNoManOneLeg;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown45_ValueChanged(object sender, EventArgs e)
        {

        }

        private unsafe void numericUpDown43_ValueChanged(object sender, EventArgs e)
        {

        }

        private unsafe void numericUpDown40_ValueChanged(object sender, EventArgs e)
        {


        }


        private unsafe void numericUpDown48_ValueChanged(object sender, EventArgs e)
        {


        }

        private unsafe void numericUpDown52_ValueChanged(object sender, EventArgs e)
        {


        }


        private unsafe void numericUpDown54_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown54.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_PreasUpCntConst;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_PreasUpCntConst;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown55_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown55.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_PreasDnCntConst;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_PreasDnCntConst;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }




        private void checkBox22_CheckedChanged(object sender, EventArgs e)
        {


        }



        private void button2_Click_1(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                sendbuf[0] = SEND_DefaultOptions;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_DefaultOptions;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void panel8_Paint(object sender, PaintEventArgs e)
        {

        }

        private unsafe void numericUpDown68_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown68.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_BeepPauseConstAlm;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_BeepPauseConstAlm;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown8_ValueChanged_1(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown8.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_BzOnCntSeriaConstAlm;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_BzOnCntSeriaConstAlm;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown1_ValueChanged_1(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown1.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_CntSingleBeepAlm;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_CntSingleBeepAlm;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown70_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown70.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_DiffAlfaConstL;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_DiffAlfaConstL;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown69_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown69.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_DiffAlfaConstH;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_DiffAlfaConstH;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button19_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_Robowell;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_Robowell;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button20_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_RobowellSpd;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_RobowellSpd;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button21_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_GetRobowell;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetRobowell;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button22_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_GetRobowellSpd;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetRobowellSpd;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }


        }

        private void button23_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                //byte[] sendbuf = new byte[4];

                sendbuf[0] = SEND_CalibrCurr;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_CalibrCurr;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button24_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                //byte[] sendbuf = new byte[4];

                sendbuf[0] = SEND_ClearCurrentAH;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_ClearCurrentAH;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void checkBox11_CheckedChanged_1(object sender, EventArgs e)
        {


        }

        private void checkBox24_CheckedChanged(object sender, EventArgs e)
        {


        }

        private void checkBox16_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox16.Checked)
                chart1.Series[0].Enabled = true;
            else
                chart1.Series[0].Enabled = false;


        }

        private void checkBox17_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox17.Checked)
                chart1.Series[1].Enabled = true;
            else
                chart1.Series[1].Enabled = false;

        }

        private void checkBox18_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox18.Checked)
                chart1.Series[2].Enabled = true;
            else
                chart1.Series[2].Enabled = false;

        }

        private void label256_Click(object sender, EventArgs e)
        {

        }

        private void label255_Click(object sender, EventArgs e)
        {

        }

        private void numericUpDown71_ValueChanged(object sender, EventArgs e)
        {

        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void label52_Click(object sender, EventArgs e)
        {

        }

        private void checkBox25_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox25.Checked)
                    sendbuf[0] = SEND_NoAutoTrmOff;
                else
                    sendbuf[0] = SEND_NoAutoTrmOn;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox25.Checked)
                    TrmMass[3] = SEND_NoAutoTrmOff;
                else
                    TrmMass[3] = SEND_NoAutoTrmOn;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }



        }

        private unsafe void numericUpDown73_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown73.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_SetTmr1;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_SetTmr1;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown72_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown72.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_SetTmr2;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_SetTmr2;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = 0;

            if (radioButton3.Checked)
                Trmm = 0;
            if (radioButton1.Checked)
                Trmm = 1;
            if (radioButton2.Checked)
                Trmm = 2;

            UseTmr = (ushort)Trmm;
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_UseTmr;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_UseTmr;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void checkBox26_CheckedChanged(object sender, EventArgs e)
        {
            //byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            //if (checkBox19.Checked)
            //{
            //    if (checkBox26.Checked)
            //        sendbuf[0] = SEND_TmrLoudOn;
            //    else
            //        sendbuf[0] = SEND_TmrLoudOff;

            //    s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 1;//N
            //    if (checkBox26.Checked)
            //        TrmMass[3] = SEND_TmrLoudOn;
            //    else
            //        TrmMass[3] = SEND_TmrLoudOff;

            //    TrmMass[4] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private unsafe void numericUpDown71_ValueChanged_1(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown71.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_SerBynber;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_SerBynber;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }



        private unsafe void numericUpDown82_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown82.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)//ФЛАГ ВСЕГДА СБРОШЕН
            {
                sendbuf[0] = SEND_SensorThreshold;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;//ИСПОЛЬЗУЕТСЯ ЭТОТ КОД
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_SensorThreshold;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }



        private void button26_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                sendbuf[0] = SEND_StopBalance2;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_StopBalance2;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button27_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                sendbuf[0] = SEND_StopBalance3;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_StopBalance3;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button28_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                sendbuf[0] = SEND_StopBalance4;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_StopBalance4;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button29_Click(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            TrmMass[3] = 9;
            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private unsafe void numericUpDown90_ValueChanged(object sender, EventArgs e)
        {


        }

        private unsafe void numericUpDown94_ValueChanged(object sender, EventArgs e)
        {
            //short* TmpShort;
            //short Trmm = Decimal.ToInt16(numericUpDown94.Value);
            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            //{
            //    sendbuf[0] = SEND_StartRotHighSpeed;
            //    fixed (byte* p = &sendbuf[2])
            //    {
            //        TmpShort = (short*)p;
            //        *TmpShort = Trmm;
            //    }

            //    s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_StartRotHighSpeed;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}


        }

        private unsafe void numericUpDown95_ValueChanged(object sender, EventArgs e)
        {
            //short* TmpShort;
            //short Trmm = Decimal.ToInt16(numericUpDown95.Value);
            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //if (checkBox19.Checked)
            //{
            //    sendbuf[0] = SEND_KRotHighSpeed;
            //    fixed (byte* p = &sendbuf[2])
            //    {
            //        TmpShort = (short*)p;
            //        *TmpShort = Trmm;
            //    }

            //    s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_KRotHighSpeed;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private unsafe void numericUpDown92_ValueChanged(object sender, EventArgs e)
        {


        }

        private unsafe void numericUpDown96_ValueChanged(object sender, EventArgs e)
        {

        }

        private void button30_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_ResetDistance;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_ResetDistance;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }


        }



        private void checkBox47_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");





            if (Spd1Res == 0)
            {

                if (checkBox19.Checked)
                {
                    if (checkBox47.Checked)
                        sendbuf[0] = SEND_DirPWM1_1;
                    else
                        sendbuf[0] = SEND_DirPWM1_0;

                    s.SendTo(sendbuf, ep);
                }
                else
                {
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 1;//N
                    if (checkBox47.Checked)
                        TrmMass[3] = SEND_DirPWM1_1;
                    else
                        TrmMass[3] = SEND_DirPWM1_0;

                    TrmMass[4] = CalcCheckSummTrm();
                    Trm();
                }
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetOptions;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();



            }



        }


        private unsafe void numericUpDown98_ValueChanged(object sender, EventArgs e)
        {



        }



        private void checkBox50_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox51_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox51.Checked)
                    sendbuf[0] = BuzzAndHornOn;
                else
                    sendbuf[0] = BuzzAndHornOff;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox51.Checked)
                    TrmMass[3] = BuzzAndHornOn;
                else
                    TrmMass[3] = BuzzAndHornOff;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }


        }

        private void button32_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_GetOptionsSteer;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetOptionsSteer;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }


        private void button33_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_WriteEEPROMSteer;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_WriteEEPROMSteer;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button34_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_CalibrGyroSteer;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_CalibrGyroSteer;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void checkBox53_CheckedChanged(object sender, EventArgs e)
        {
            /*byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox53.Checked)
                    sendbuf[0] = SEND_FilterOnSteer;
                else
                    sendbuf[0] = SEND_FilterOffSteer;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox53.Checked)
                    TrmMass[3] = SEND_FilterOnSteer;
                else
                    TrmMass[3] = SEND_FilterOffSteer;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
                
            }
            */
        }


        private unsafe void numericUpDown104_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown104.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_SensorThresholdUp;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_SensorThresholdUp;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void checkBox54_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox54.Checked)
                    sendbuf[0] = SEND_BreakInvBtnOn;
                else
                    sendbuf[0] = SEND_BreakInvBtnOff;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox54.Checked)
                    TrmMass[3] = SEND_BreakInvBtnOn;
                else
                    TrmMass[3] = SEND_BreakInvBtnOff;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void checkBox55_CheckedChanged(object sender, EventArgs e)
        {

        }

        private unsafe void numericUpDown105_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown105.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_BreakThreshold;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_BreakThreshold;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }


        }

        private unsafe void numericUpDown106_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown106.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_KFirstBreak;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_KFirstBreak;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }



        private unsafe void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(comboBox8.SelectedIndex);

            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_SensOrder1;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_SensOrder1;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }
            //DecreaseCurrent();

        }

        private void button35_Click(object sender, EventArgs e)
        {
            if (checkBox19.Checked)
            {
                byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
                sendbuf[0] = SEND_StopBalance5;
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_StopBalance5;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void label222_Click(object sender, EventArgs e)
        {

        }

        private void label224_Click(object sender, EventArgs e)
        {

        }

        private void label225_Click(object sender, EventArgs e)
        {

        }


        private void label223_Click(object sender, EventArgs e)
        {

        }






        private unsafe void button36_Click(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if ((Flgs2 & 0x40000000) == 0x40000000)
                TrmMass[3] = SEND_SignalizaciaOFF;
            else
                TrmMass[3] = SEND_SignalizaciaON;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();


        }

        private void button37_Click(object sender, EventArgs e)
        {
            ushort N;

            chart1.Series[5].Enabled = true;

            for (N = 0; N < 384; N++)
            {
                sine_Res[N] = sine_array[N] + sine_array[383 - N];

                chart1.Series[5].Points.AddXY(CntSamples, sine_array[N]);
            }





        }

        private void button38_Click(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_FixPeriod;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_FixPeriod;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button39_Click(object sender, EventArgs e)
        {
            //byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            //sendbuf[0] = SEND_UnFixPeriod;
            //if (checkBox19.Checked)
            //{
            //    s.SendTo(sendbuf, ep);
            //}
            //else
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 1;//N
            //    TrmMass[3] = SEND_UnFixPeriod;
            //    TrmMass[4] = CalcCheckSummTrm();
            //    Trm();
            //}

        }



        private void comboBox9_SelectedIndexChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox9.SelectedIndex);
            byte Trm2;

            switch (Trmm)
            {
                case 0:
                    Trmm = 1;
                    Trm2 = 0;
                    break;
                case 1:
                    Trmm = 2;
                    Trm2 = 1;
                    break;
                case 2:
                    Trmm = 4;
                    Trm2 = 2;
                    break;
                case 3:
                    Trmm = 8;
                    Trm2 = 3;
                    break;
                case 4:
                    Trmm = 16;
                    Trm2 = 4;
                    break;
                case 5:
                    Trmm = 32;
                    Trm2 = 5;
                    break;
                case 6:
                    Trmm = 64;
                    Trm2 = 6;
                    break;
                case 7:
                    Trmm = 0;
                    Trm2 = 7;
                    break;
                default:
                    Trmm = 1;
                    Trm2 = 0;
                    break;
            }

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_PhasePERMASS;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = Trm2;
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

            //DecreaseCurrent();

        }

        private unsafe void numericUpDown115_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown115.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_HallDelay1_F;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_HallDelay1_F;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }
            //DecreaseCurrent();


        }

        private unsafe void numericUpDown116_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown116.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_HallDelay1_B;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_HallDelay1_B;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }
            //DecreaseCurrent();

        }

        private unsafe void numericUpDown118_ValueChanged(object sender, EventArgs e)
        {


        }

        private void checkBox57_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");


            if (checkBox57.Checked)
            {
                comboBox9.Enabled = true;
                numericUpDown115.Enabled = true;
                numericUpDown116.Enabled = true;
                checkBox58.Enabled = true;
            }
            else
            {
                comboBox9.Enabled = false;
                numericUpDown115.Enabled = false;
                numericUpDown116.Enabled = false;
                checkBox58.Enabled = false;
            }



            if (checkBox19.Checked)
            {
                if (checkBox57.Checked)
                    sendbuf[0] = SEND_VectorOn;
                else
                    sendbuf[0] = SEND_VectorOff;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox57.Checked)
                    TrmMass[3] = SEND_VectorOn;
                else
                    TrmMass[3] = SEND_VectorOff;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }
            //DecreaseCurrent();


        }

        private void checkBox58_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox58.Checked)
                    sendbuf[0] = SEND_VectorTrapezoidaOn;
                else
                    sendbuf[0] = SEND_VectorTrapezoidaOff;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox58.Checked)
                    TrmMass[3] = SEND_VectorTrapezoidaOn;
                else
                    TrmMass[3] = SEND_VectorTrapezoidaOff;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

            //DecreaseCurrent();


        }

        private unsafe void numericUpDown126_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown126.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_KiCurr;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_KiCurr;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private unsafe void numericUpDown127_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            double Trmm = Decimal.ToInt32(numericUpDown127.Value);


            Trmm = Trmm / CurrPerDigit;

            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_CurrUst;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = (short)Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_CurrUst;
                TrmMass[4] = (byte)(int)Trmm;
                TrmMass[5] = (byte)(((int)Trmm) >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }


        private unsafe void DecreaseCurrent()
        {
            short* TmpShort;
            short Trmm = 1;

            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_CurrLimit;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_CurrLimit;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }


            Trmm = 2000;


            Trmm = (short)((double)Trmm / CurrPerDigit);


            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_CurrUst;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = (short)Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_CurrUst;
                TrmMass[4] = (byte)(int)Trmm;
                TrmMass[5] = (byte)(((int)Trmm) >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }



        }

        private void panel16_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel16_MouseClick(object sender, MouseEventArgs e)
        {

        }

        private void checkBox59_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");


            if (checkBox59.Checked == true)
            {
                panel16.Enabled = true;
                //checkBox60.Checked = true;
                //comboBox1.SelectedIndex = 2;
                //numericUpDown127.Value = 500;
                MessageBox.Show(MyStrings.DecreaseCurrentSettings, MyStrings.Inform, MessageBoxButtons.OK);
                //DecreaseCurrent();
            }
            else
                panel16.Enabled = false;



            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox59.Checked)
                TrmMass[4] = SEND_DecreaseCurrentOn;
            else
                TrmMass[4] = SEND_DecreaseCurrentOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();









        }

        private void button38_Click_1(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_ClbrHalls;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_ClbrHalls;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }


        }

        private void checkBox61_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            if (checkBox19.Checked)
            {
                if (checkBox61.Checked)
                    sendbuf[0] = SEND_PWM32BitsOn;
                else
                    sendbuf[0] = SEND_PWM32BitsOff;

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                if (checkBox61.Checked)
                    TrmMass[3] = SEND_PWM32BitsOn;
                else
                    TrmMass[3] = SEND_PWM32BitsOff;

                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }
            //DecreaseCurrent();


        }







        private void button39_Click_1(object sender, EventArgs e)
        {

        }




        private void button40_Click(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            TrmMass[3] = SEND_GetPhase;
            TrmMass[4] = CalcCheckSummTrm();
            Trm();

            if (!GettinPhase)
                GettinPhase = true;
            else
                GettinPhase = false;


        }



        private void DataRequest()
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            sendbuf[0] = SEND_TrmRqst;
            if (checkBox19.Checked)
            {
                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_TrmRqst;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void label478_Click(object sender, EventArgs e)
        {

        }

        private void tabPage9_Click(object sender, EventArgs e)
        {

        }

        private void button31_Click(object sender, EventArgs e)
        {
            COMPorts();
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void numericUpDown56_ValueChanged(object sender, EventArgs e)
        {

        }

        private unsafe void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
        {
            //short Trmm = Decimal.ToInt16(comboBox7.SelectedIndex);

            //if ((Trmm == 4) || (Trmm == 5))
            //{
            //    label253.ForeColor = Color.Black;
            //    comboBox7.ForeColor = Color.Black;
            //}
            //else
            //{
            //    label253.ForeColor = Color.Red;
            //    comboBox7.ForeColor = Color.Red;
            //}




            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_But1Func;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private void comboBox10_SelectedIndexChanged(object sender, EventArgs e)
        {
            //short Trmm = Decimal.ToInt16(comboBox10.SelectedIndex);

            //if ((Trmm == 4) || (Trmm == 5))
            //{
            //    label265.ForeColor = Color.Black;
            //    comboBox10.ForeColor = Color.Black;
            //}
            //else
            //{
            //    label265.ForeColor = Color.Red;
            //    comboBox10.ForeColor = Color.Red;
            //}




            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_But2Func;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private void comboBox11_SelectedIndexChanged(object sender, EventArgs e)
        {
            //short Trmm = Decimal.ToInt16(comboBox11.SelectedIndex);

            //if ((Trmm == 4) || (Trmm == 5))
            //{
            //    label343.ForeColor = Color.Black;
            //    comboBox11.ForeColor = Color.Black;
            //}
            //else
            //{
            //    label343.ForeColor = Color.Red;
            //    comboBox11.ForeColor = Color.Red;
            //}


            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_But3Func;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private void comboBox12_SelectedIndexChanged(object sender, EventArgs e)
        {
            //short Trmm = Decimal.ToInt16(comboBox12.SelectedIndex);

            //if ((Trmm == 4) || (Trmm == 5))
            //{
            //    label419.ForeColor = Color.Black;
            //    comboBox12.ForeColor = Color.Black;
            //}
            //else
            //{
            //    label419.ForeColor = Color.Red;
            //    comboBox12.ForeColor = Color.Red;
            //}



            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND_But4Func;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private void comboBox13_SelectedIndexChanged(object sender, EventArgs e)
        {


        }

        private unsafe void numericUpDown56_ValueChanged_1(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown56.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_MaxSpdPID;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_MaxSpdPID;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (radioButton4.Checked)
            {
                TrmMass[3] = SEND_PWMControlOn;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }





        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (radioButton5.Checked)
            {
                TrmMass[3] = SEND_SpeedControlOn;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void label205_Click(object sender, EventArgs e)
        {

        }

        private void label206_Click(object sender, EventArgs e)
        {

        }

        private void checkBox49_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox49.Checked)
                TrmMass[3] = SEND_DirBalance1;
            else
                TrmMass[3] = SEND_DirBalance0;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private void button16_Click_1(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            TrmMass[3] = 196;
            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private void button39_Click_2(object sender, EventArgs e)
        {
            //TrmMass[0] = 0xff;
            //TrmMass[1] = 0xff;
            //TrmMass[2] = 1;//N
            //TrmMass[3] = 197;
            //TrmMass[4] = CalcCheckSummTrm();
            //Trm();

        }

        private unsafe void numericUpDown108_ValueChanged(object sender, EventArgs e)
        {
            short* TmpShort;
            short Trmm = Decimal.ToInt16(numericUpDown108.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            if (checkBox19.Checked)
            {
                sendbuf[0] = SEND_SensorLessTimerConst;
                fixed (byte* p = &sendbuf[2])
                {
                    TmpShort = (short*)p;
                    *TmpShort = Trmm;
                }

                s.SendTo(sendbuf, ep);
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_SensorLessTimerConst;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void checkBox56_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox56.Checked)
                TrmMass[3] = SEND_SensorlessON;
            else
                TrmMass[3] = SEND_SensorlessOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();


        }

        private void checkBox62_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox62.Checked)
                TrmMass[3] = SEND_AlignmentON;
            else
                TrmMass[3] = SEND_AlignmentOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox14_SelectedIndexChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox14.SelectedIndex);

            byte[] sendbuf = new byte[sizeof(short) + 2];
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorlessCurrLimit;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown113_ValueChanged_1(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown113.Value);


            Trmm = Trmm / CurrPerDigit;

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorlessCurrUst;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown114_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown114.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SenosrlessPWM1_1Const;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown117_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown117.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorlessCntAlignConst;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown122_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown122.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorlessSpdChngCntConst;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown123_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown123.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorLessTimerConst2;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown124_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown124.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SenosrlessPWM1_2Const;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown125_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown125.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorLessTimerConstMin;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown128_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown128.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorllessSpdThreshold;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void panel10_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label243_Click(object sender, EventArgs e)
        {

        }

        private void checkBox63_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox63.Checked)
                TrmMass[3] = SEND_Temperature3On;
            else
                TrmMass[3] = SEND_Temperature3Off;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();


        }

        private void checkBox64_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox64.Checked)
                TrmMass[3] = SEND_Temperature4On;
            else
                TrmMass[3] = SEND_Temperature4Off;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();
        }

        private void checkBox65_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox65.Checked)
                TrmMass[3] = SEND_Temperature5On;
            else
                TrmMass[3] = SEND_Temperature5Off;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();
        }

        private void checkBox66_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox66.Checked)
                TrmMass[3] = SEND_Temperature6On;
            else
                TrmMass[3] = SEND_Temperature6Off;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();
        }

        private void panel10_Paint_1(object sender, PaintEventArgs e)
        {

        }

        private void numericUpDown129_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown129.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_TemperatureMaxOUT;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown130_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown130.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_TemperatureMaxIN;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void comboBox15_SelectedIndexChanged(object sender, EventArgs e)
        {


        }

        private void numericUpDown131_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown131.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KpTemperIN;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown132_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown132.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KiTemperIN;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown133_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown133.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KpTemperOUT;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();



        }

        private void numericUpDown134_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown134.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KiTemperOUT;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown135_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown135.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_Profile;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown136_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown136.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_MAX_PWM_MEM;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void radioButton9_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (radioButton9.Checked)
            {
                TrmMass[3] = SEND_ThreePositionSwitchOn;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
                label343.Enabled = false;
                label419.Enabled = false;
                comboBox11.Enabled = false;
                comboBox12.Enabled = false;
                comboBox13.Enabled = true;
                comboBox16.Enabled = true;
                comboBox17.Enabled = true;
                label448.Enabled = true;
                label449.Enabled = true;
                label464.Enabled = true;

            }
            else
            {
                label343.Enabled = true;
                label419.Enabled = true;
                comboBox11.Enabled = true;
                comboBox12.Enabled = true;
                comboBox13.Enabled = false;
                comboBox16.Enabled = false;
                comboBox17.Enabled = false;
                label448.Enabled = false;
                label449.Enabled = false;
                label464.Enabled = false;

            }

        }

        private void radioButton8_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (radioButton8.Checked)
            {
                TrmMass[3] = SEND_ThreePositionSwitchOff;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
                label343.Enabled = true;
                label419.Enabled = true;
                comboBox11.Enabled = true;
                comboBox12.Enabled = true;
                comboBox13.Enabled = false;
                comboBox16.Enabled = false;
                comboBox17.Enabled = false;
                label448.Enabled = false;
                label449.Enabled = false;
                label464.Enabled = false;


            }
            else
            {
                label343.Enabled = false;
                label419.Enabled = false;
                comboBox11.Enabled = false;
                comboBox12.Enabled = false;
                comboBox13.Enabled = true;
                comboBox16.Enabled = true;
                comboBox17.Enabled = true;
                label448.Enabled = true;
                label449.Enabled = true;
                label464.Enabled = true;


            }
        }

        private void label535_Click(object sender, EventArgs e)
        {

        }

        private void comboBox13_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            //short Trmm = Decimal.ToInt16(comboBox13.SelectedIndex);

            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND__3psnSwitchBt3;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}
        }

        private void comboBox16_SelectedIndexChanged(object sender, EventArgs e)
        {
            //short Trmm = Decimal.ToInt16(comboBox16.SelectedIndex);

            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND__3psnSwitchBtNotPressed;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private void comboBox17_SelectedIndexChanged(object sender, EventArgs e)
        {
            //short Trmm = Decimal.ToInt16(comboBox17.SelectedIndex);

            //byte[] sendbuf = new byte[sizeof(short) + 2];
            //{
            //    TrmMass[0] = 0xff;
            //    TrmMass[1] = 0xff;
            //    TrmMass[2] = 3;//N
            //    TrmMass[3] = SEND__3psnSwitchBt4;
            //    TrmMass[4] = (byte)Trmm;
            //    TrmMass[5] = (byte)(Trmm >> 8);
            //    TrmMass[6] = CalcCheckSummTrm();
            //    Trm();
            //}

        }

        private void numericUpDown138_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown138.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_MAX_PWM_Revers;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown139_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown139.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_MaxSpdRevers;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox67_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox67.Checked)
                TrmMass[3] = SEND_SmoothBreakOn;
            else
                TrmMass[3] = SEND_SmoothBreakOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown140_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown140.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_AutoPID_On_PWM;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }




        private void numericUpDown141_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown141.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_AutoPID_On_Speed;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown142_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown142.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_AutoPID_On_CntConst;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox68_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox68.Checked)
                TrmMass[3] = SEND_AutoPIDOn;
            else
                TrmMass[3] = SEND_AutoPIDOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox69_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox69.Checked)
                panel36.Enabled = true;
            else
                panel36.Enabled = false;
        }

        private void numericUpDown143_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown143.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_UBatHi;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void button43_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show(
        MyStrings.CopySettings,
        MyStrings.CopySettingsZ, MessageBoxButtons.YesNo,
        MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
            if (result == DialogResult.Yes)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_CopyProfiles;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }



        }

        private void numericUpDown144_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown144.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SensorTSTKeys;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox26_CheckedChanged_1(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox26.Checked)
                TrmMass[3] = SEND_ZeroThroottleOn;
            else
                TrmMass[3] = SEND_ZeroThroottleOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private void button42_Click(object sender, EventArgs e)
        {

            saveFileDialog1.FileName = "";
            saveFileDialog1.ShowDialog();

            if (saveFileDialog1.FileName != "")
            {
                if (w == null)
                    w = File.Create(saveFileDialog1.FileName);
                else
                {

                    //w.Flush();
                    w.Close();
                    w = File.Create(saveFileDialog1.FileName);

                }
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_SaveOptions1;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
                SaveTimeOut = 30;
            }


        }

        private void button41_Click(object sender, EventArgs e)
        {
            FileStream w;
            int Tm;
            byte Sm;
            int r;
            int Cnt;

            openFileDialog1.FileName = "";
            openFileDialog1.ShowDialog();
            if (openFileDialog1.FileName != "")
            {

                w = File.OpenRead(openFileDialog1.FileName);

                for (Tm = 0; Tm < 1024; Tm++)
                {
                    SaveOptionsMass[Tm] = (byte)w.ReadByte();
                }


                w.Close();

                Sm = 0;
                for (r = 0; r < (SaveOptionsMass[0] + 1); r++)
                {
                    Sm = (byte)(Sm + SaveOptionsMass[r]);
                }
                Sm = (byte)(~Sm);

                if (Sm != SaveOptionsMass[SaveOptionsMass[0] + 1])
                {
                    MessageBox.Show(MyStrings.CHKErr + " 2", MyStrings.ErrorMsg, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                Sm = 0;
                Tm = SaveOptionsMass[0] + 2 + SaveOptionsMass[SaveOptionsMass[0] + 2] + 1;
                for (r = SaveOptionsMass[0] + 2; r < Tm; r++)
                {
                    Sm = (byte)(Sm + SaveOptionsMass[r]);
                }
                Sm = (byte)(~Sm);

                if (Sm != SaveOptionsMass[Tm])
                {
                    MessageBox.Show(MyStrings.CHKErr + " 3", MyStrings.ErrorMsg, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }


                Sm = 0;
                for (r = 489; r < (489 + SaveOptionsMass[489] + 1); r++)
                {
                    Sm = (byte)(Sm + SaveOptionsMass[r]);
                }
                Sm = (byte)(~Sm);

                if (Sm != SaveOptionsMass[SaveOptionsMass[489] + 1 + 489])
                {
                    MessageBox.Show(MyStrings.CHKErr + " 4", MyStrings.ErrorMsg, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }




                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                //                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_Options1;
                Cnt = 4;
                for (r = 0; r < (SaveOptionsMass[0] + 1); r++)
                {
                    TrmMass[Cnt++] = SaveOptionsMass[r];
                }

                TrmMass[2] = (byte)(Cnt - 3);

                TrmMass[Cnt++] = CalcCheckSummTrm();
                Trm();
                TimeOutLoadOptions1 = 30;



            }

        }

        private void checkBox44_CheckedChanged_1(object sender, EventArgs e)
        {

            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox44.Checked)
                TrmMass[3] = SEND_ManualStartOn;
            else
                TrmMass[3] = SEND_ManualStartOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();








        }

        private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
        {

            short Trmm = Decimal.ToInt16(comboBox1.SelectedIndex);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_CurrLimit;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox54_CheckStateChanged(object sender, EventArgs e)
        {

        }

        private void comboBox7_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox7.SelectedIndex);

            if ((Trmm == 4) || (Trmm == 5))
            {
                label253.ForeColor = Color.Black;
                comboBox7.ForeColor = Color.Black;
            }
            else
            {
                label253.ForeColor = Color.Red;
                comboBox7.ForeColor = Color.Red;
            }




            byte[] sendbuf = new byte[sizeof(short) + 2];
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_But1Func;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void comboBox10_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox10.SelectedIndex);

            if ((Trmm == 4) || (Trmm == 5))
            {
                label265.ForeColor = Color.Black;
                comboBox10.ForeColor = Color.Black;
            }
            else
            {
                label265.ForeColor = Color.Red;
                comboBox10.ForeColor = Color.Red;
            }




            byte[] sendbuf = new byte[sizeof(short) + 2];
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_But2Func;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void comboBox13_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox13.SelectedIndex);

            byte[] sendbuf = new byte[sizeof(short) + 2];
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND__3psnSwitchBt3;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void comboBox16_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox16.SelectedIndex);

            byte[] sendbuf = new byte[sizeof(short) + 2];
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND__3psnSwitchBtNotPressed;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void comboBox17_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox17.SelectedIndex);

            byte[] sendbuf = new byte[sizeof(short) + 2];
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND__3psnSwitchBt4;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void comboBox11_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox11.SelectedIndex);

            if ((Trmm == 4) || (Trmm == 5))
            {
                label343.ForeColor = Color.Black;
                comboBox11.ForeColor = Color.Black;
            }
            else
            {
                label343.ForeColor = Color.Red;
                comboBox11.ForeColor = Color.Red;
            }


            byte[] sendbuf = new byte[sizeof(short) + 2];
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_But3Func;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void comboBox12_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox12.SelectedIndex);

            if ((Trmm == 4) || (Trmm == 5))
            {
                label419.ForeColor = Color.Black;
                comboBox12.ForeColor = Color.Black;
            }
            else
            {
                label419.ForeColor = Color.Red;
                comboBox12.ForeColor = Color.Red;
            }



            //        byte[] sendbuf = new byte[sizeof(short) + 2];
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_But4Func;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void button44_Click(object sender, EventArgs e)
        {
            if ((Flgs5 & 0x400000) == 0x400000)
            {


                if (checkBox88.Checked)
                {
                    String Str = textBox2.Text;
                    char ch;

                    byte[] sendbuf = new byte[sizeof(short) + 2];
                    TrmMass[0] = 0xff;
                    TrmMass[1] = 0xff;
                    TrmMass[2] = 3;//N
                    TrmMass[3] = SEND_SecondCMD;
                    TrmMass[4] = SEND_PINCODE_Unlock;

                    int i;
                    for (i = 0; i < textBox2.Text.Length; i++)
                    {
                        ch = (char)Str[i];
                        TrmMass[5 + i] = (byte)ch;
                    }



                    TrmMass[2] = (byte)(2 + i);//N


                    TrmMass[5 + i] = CalcCheckSummTrm();


                    Trm();



                }






                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 13;//N
                TrmMass[3] = SEND_Unlock;

                TrmMass[4] = 0x37;
                TrmMass[5] = 0xac;
                TrmMass[6] = 0x2b;
                TrmMass[7] = 0x33;
                TrmMass[8] = 0xf1;
                TrmMass[9] = 0x91;
                TrmMass[10] = 0x7a;
                TrmMass[11] = 0xb0;
                TrmMass[12] = 0xec;
                TrmMass[13] = 0x46;
                TrmMass[14] = 0x10;
                TrmMass[15] = 0xaa;


                TrmMass[16] = CalcCheckSummTrm();
                Trm();
            }
            else
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_lock;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();

            }

        }

        private void button45_Click(object sender, EventArgs e)
        {
            OdometrMem = Odometr;
        }

        private void radioButton7_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton7CannotSndCMD)
            {
                radioButton7CannotSndCMD = false;
                return;
            }
            if (radioButton7.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_StrongModeOn;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void radioButton11_CheckedChanged(object sender, EventArgs e)
        {
            /*if (checkBox70.Checked)
            { 
                MessageBox.Show("Операция невозможна, т.к. включен режим моноцилка", "Информация", MessageBoxButtons.OK);
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetOptions;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();



                return;
            }
            */
            if (radioButton11CannotSndCMD)
            {
                radioButton11CannotSndCMD = false;
                return;
            }

            if (radioButton11.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_NormalMode;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void radioButton10_CheckedChanged(object sender, EventArgs e)
        {

            if (checkBox70.Checked)
            {
                MessageBox.Show(MyStrings.OperationNotPossible, MyStrings.Inform, MessageBoxButtons.OK);
                return;
            }


            if (radioButton10CannotSndCMD)
            {
                radioButton10CannotSndCMD = false;
                return;
            }


            if (radioButton10.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_MixedMode;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void panel26_Paint(object sender, PaintEventArgs e)
        {

        }

        private void numericUpDown147_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown147.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_CntMixedModeMax;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown146_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown146.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_MixedModeLevelOn;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown145_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown145.Value);
            Trmm = Trmm / CurrPerDigit;

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_CurrMixed;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown148_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown148.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KpCurr;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown149_ValueChanged(object sender, EventArgs e)
        {


            double Trmm = Decimal.ToInt32(numericUpDown149.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_MixedModeLevelOff;
            TrmMass[4] = (byte)(int)Trmm;
            TrmMass[5] = (byte)(((int)Trmm) >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();






        }

        private void checkBox71_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox71.Checked)
            {
                panel41.Enabled = true;
                // checkBox86.Enabled = true;
                TrmMass[3] = SEND_AnalogBreakOn;
            }
            else
            {
                TrmMass[3] = SEND_AnalogBreakOff;
                //                checkBox86.Enabled = false;
                panel41.Enabled = false;
                //    checkBox86.Checked = false;
            }

            TrmMass[4] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown137_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown137.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_BreakThresholdDn;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown150_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown150.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_BreakThresholdUp;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox55_CheckedChanged_1(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox55.Checked)
                TrmMass[3] = SEND_StrongModePIDOn;
            else
                TrmMass[3] = SEND_StrongModePIDOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox70_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox70.Checked)
            {
                TrmMass[3] = SEND_MonocycleOn;
                panel35.Enabled = true;
                panel44.Enabled = true;
                panel45.Enabled = true;
                panel46.Enabled = true;
            }
            else
            {
                TrmMass[3] = SEND_MonocycleOff;
                //                panel35.Enabled = false;
                //              panel44.Enabled = false;
                //            panel45.Enabled = false;
                //          panel46.Enabled = false;
            }

            TrmMass[4] = CalcCheckSummTrm();
            Trm();




        }

        private void numericUpDown151_ValueChanged(object sender, EventArgs e)
        {


            short Trmm = Decimal.ToInt16(numericUpDown151.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SpdKpMax;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();






        }

        private void numericUpDown153_ValueChanged(object sender, EventArgs e)
        {


            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown153.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KpMax;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();




        }

        private void numericUpDown154_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown154.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KpKpSpd;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();
        }

        private void checkBox73_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox73.Checked)
                TrmMass[3] = SEND_MonoStopDirectionOn;
            else
                TrmMass[3] = SEND_MonoStopDirectionOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();
        }

        private void checkBox72_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 1;//N
            if (checkBox72.Checked)
                TrmMass[3] = SEND_BreakButtonMonocycleOn;
            else
                TrmMass[3] = SEND_BreakButtonMonocycleOff;

            TrmMass[4] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown152_ValueChanged(object sender, EventArgs e)
        {

        }

        private void numericUpDown156_ValueChanged(object sender, EventArgs e)
        {


            short Trmm = Decimal.ToInt16(numericUpDown156.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_MaxAngleStopBreak;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();



        }

        private void checkBox74_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox74.Checked)
                TrmMass[4] = SEND_SecondCMD_RotAlfaXResOn;
            else
                TrmMass[4] = SEND_SecondCMD_RotAlfaXResOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void radioButton6_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (radioButton6.Checked)
            {
                TrmMass[4] = SEND_TurnSignalOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
                label343.Enabled = false;
                label419.Enabled = false;
                comboBox11.Enabled = false;
                comboBox12.Enabled = false;
                comboBox13.Enabled = false;
                comboBox16.Enabled = false;
                comboBox17.Enabled = false;
                label448.Enabled = false;
                label449.Enabled = false;
                label464.Enabled = false;
            }
        }

        private void checkBox76_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox76.Checked)
                TrmMass[4] = SEND_LightsTudaSudaOn;
            else
                TrmMass[4] = SEND_LightsTudaSudaOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox75_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox75.Checked)
                TrmMass[4] = SEND_LightsStopMonoDirOn;
            else
                TrmMass[4] = SEND_LightsStopMonoDirOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox77_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox77.Checked)
                TrmMass[4] = SEND_SlowStartOn;
            else
                TrmMass[4] = SEND_SlowStartOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown157_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown157.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_ThrottleTmpChngMem;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox78_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox78.Checked)
                TrmMass[4] = SEND_AntiPoliceOn;
            else
                TrmMass[4] = SEND_AntiPoliceOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown155_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown155.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_SlowStrtSpd;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown158_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown158.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_AntiPolicePower;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown159_ValueChanged(object sender, EventArgs e)
        {

        }

        private void numericUpDown160_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown160.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KTemperatureSPDControl;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void radioButton12_CheckedChanged(object sender, EventArgs e)
        {
        }

        private void checkBox79_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox79.Checked)
                TrmMass[4] = SEND_MixedModeSlowSpeedOffOn;
            else
                TrmMass[4] = SEND_MixedModeSlowSpeedOffOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown161_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown161.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_MixedModeSlowSpeed;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void radioButton12_CheckedChanged_1(object sender, EventArgs e)
        {
            /*if (checkBox70.Checked)
            {
                MessageBox.Show("Операция невозможна, т.к. включен режим моноцилка", MyStrings.Inform, MessageBoxButtons.OK);

                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetOptions;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();


                return;
            }
            */


            if (radioButton12CannotSndCMD)
            {
                radioButton12CannotSndCMD = false;
                return;
            }


            if (radioButton12.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_MixedMode2;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void numericUpDown162_ValueChanged(object sender, EventArgs e)
        {

            short Trmm = Decimal.ToInt16(numericUpDown162.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_Ki_PWM_Mode;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();



        }

        private void checkBox80_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox80.Checked)
                TrmMass[4] = SEND_PWM_ModeOn;
            else
                TrmMass[4] = SEND_PWM_ModeOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown152_ValueChanged_1(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown152.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_GyroZFlTurn;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown163_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown160.Value);
            byte[] sendbuf = new byte[sizeof(short) + 2];
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_KTemperatureSPDControl;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            button12.Enabled = true;
        }

        private void checkBox81_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox81.Checked)
                TrmMass[4] = SEND_PWM_Mode_ZeroThrottleOn;
            else
                TrmMass[4] = SEND_PWM_Mode_ZeroThrottleOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown164_ValueChanged(object sender, EventArgs e)
        {

            short Trmm = Decimal.ToInt16(numericUpDown164.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_Kp_PWM_Mode;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void button46_Click(object sender, EventArgs e)
        {
            String Str = MyStrings.Version + Version;
            byte Lo, Hi;
            Str += Environment.NewLine;
            if (FirmwareVersion != 0)
            {
                Lo = (byte)FirmwareVersion;
                Hi = (byte)(FirmwareVersion >> 8);
                Str = Str + MyStrings.FirmwareVer + Hi.ToString() + "." + Lo.ToString();
            }
            else
            {
                Str = Str + MyStrings.FirmwareNotConnected;
            }
            //AboutBox1 a = new AboutBox1();
            //a.Show();
            Str += Environment.NewLine;


            MessageBox.Show(Str, MyStrings.About1333, MessageBoxButtons.OK);

        }

        private void comboBox18_SelectedIndexChanged(object sender, EventArgs e)
        {
            /*
            switch (comboBox18.SelectedIndex)
            {
                case 0:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("26A");
                    comboBox1.Items.Add("34A");
                    comboBox1.Items.Add("42A");
                    comboBox1.Items.Add("50A");
                    comboBox1.Items.Add("58A");
                    comboBox1.Items.Add("65A");
                    comboBox1.Items.Add("74A");
                    comboBox1.Items.Add("81A");
                    comboBox1.Items.Add("89A");
                    comboBox1.Items.Add("97A");
                    comboBox1.Items.Add("104A");
                    comboBox1.Items.Add("113A");
                    comboBox1.Items.Add("120A");
                    comboBox1.Items.Add("128A");
                    comboBox1.Items.Add("136A");

                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("26A");
                    comboBox19.Items.Add("34A");
                    comboBox19.Items.Add("42A");
                    comboBox19.Items.Add("50A");
                    comboBox19.Items.Add("58A");
                    comboBox19.Items.Add("65A");
                    comboBox19.Items.Add("74A");
                    comboBox19.Items.Add("81A");
                    comboBox19.Items.Add("89A");
                    comboBox19.Items.Add("97A");
                    comboBox19.Items.Add("104A");
                    comboBox19.Items.Add("113A");
                    comboBox19.Items.Add("120A");
                    comboBox19.Items.Add("128A");
                    comboBox19.Items.Add("136A");

                    CurrPerDigit = 48.34;



                    break;
                case 1:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("35A");
                    comboBox1.Items.Add("46A");
                    comboBox1.Items.Add("56A");
                    comboBox1.Items.Add("66A");
                    comboBox1.Items.Add("77A");
                    comboBox1.Items.Add("87A");
                    comboBox1.Items.Add("98A");
                    comboBox1.Items.Add("108A");
                    comboBox1.Items.Add("118A");
                    comboBox1.Items.Add("129A");
                    comboBox1.Items.Add("139A");
                    comboBox1.Items.Add("150A");
                    comboBox1.Items.Add("160A");
                    comboBox1.Items.Add("170A");
                    comboBox1.Items.Add("181A");


                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("35A");
                    comboBox19.Items.Add("46A");
                    comboBox19.Items.Add("56A");
                    comboBox19.Items.Add("66A");
                    comboBox19.Items.Add("77A");
                    comboBox19.Items.Add("87A");
                    comboBox19.Items.Add("98A");
                    comboBox19.Items.Add("108A");
                    comboBox19.Items.Add("118A");
                    comboBox19.Items.Add("129A");
                    comboBox19.Items.Add("139A");
                    comboBox19.Items.Add("150A");
                    comboBox19.Items.Add("160A");
                    comboBox19.Items.Add("170A");
                    comboBox19.Items.Add("181A");


                    CurrPerDigit = 64.45;


                    break;

                case 2:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("52A");
                    comboBox1.Items.Add("68A");
                    comboBox1.Items.Add("84A");
                    comboBox1.Items.Add("100A");
                    comboBox1.Items.Add("116A");
                    comboBox1.Items.Add("130A");
                    comboBox1.Items.Add("148A");
                    comboBox1.Items.Add("162A");
                    comboBox1.Items.Add("178A");
                    comboBox1.Items.Add("194A");
                    comboBox1.Items.Add("208A");
                    comboBox1.Items.Add("226A");
                    comboBox1.Items.Add("240A");
                    comboBox1.Items.Add("256A");
                    comboBox1.Items.Add("272A");


                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("52A");
                    comboBox19.Items.Add("68A");
                    comboBox19.Items.Add("84A");
                    comboBox19.Items.Add("100A");
                    comboBox19.Items.Add("116A");
                    comboBox19.Items.Add("130A");
                    comboBox19.Items.Add("148A");
                    comboBox19.Items.Add("162A");
                    comboBox19.Items.Add("178A");
                    comboBox19.Items.Add("194A");
                    comboBox19.Items.Add("208A");
                    comboBox19.Items.Add("226A");
                    comboBox19.Items.Add("240A");
                    comboBox19.Items.Add("256A");
                    comboBox19.Items.Add("272A");



                    CurrPerDigit = 96.68;


                    break;

                case 3:
                    comboBox1.Items.Clear();
                    comboBox1.Items.Add("108A");
                    comboBox1.Items.Add("142A");
                    comboBox1.Items.Add("175A");
                    comboBox1.Items.Add("208A");
                    comboBox1.Items.Add("242A");
                    comboBox1.Items.Add("271A");
                    comboBox1.Items.Add("308A");
                    comboBox1.Items.Add("337A");
                    comboBox1.Items.Add("371A");
                    comboBox1.Items.Add("404A");
                    comboBox1.Items.Add("433A");
                    comboBox1.Items.Add("471A");
                    comboBox1.Items.Add("500A");
                    comboBox1.Items.Add("533A");
                    comboBox1.Items.Add("567A");


                    comboBox19.Items.Clear();
                    comboBox19.Items.Add("108A");
                    comboBox19.Items.Add("142A");
                    comboBox19.Items.Add("175A");
                    comboBox19.Items.Add("208A");
                    comboBox19.Items.Add("242A");
                    comboBox19.Items.Add("271A");
                    comboBox19.Items.Add("308A");
                    comboBox19.Items.Add("337A");
                    comboBox19.Items.Add("371A");
                    comboBox19.Items.Add("404A");
                    comboBox19.Items.Add("433A");
                    comboBox19.Items.Add("471A");
                    comboBox19.Items.Add("500A");
                    comboBox19.Items.Add("533A");
                    comboBox19.Items.Add("567A");



                    CurrPerDigit = 134;// 201;// 80;// 100.708;// 201.416;


                    break;



            }

            */
        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void checkBox82_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");

            /*
            if (checkBox70.Checked)
            {
                MessageBox.Show("Операция невозможна, т.к. включен режим моноцилка", "Информация", MessageBoxButtons.OK);

                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 1;//N
                TrmMass[3] = SEND_GetOptions;
                TrmMass[4] = CalcCheckSummTrm();
                Trm();

                return;
            }
            */



            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox82.Checked)
                TrmMass[4] = SEND_SIN_MIDDLEOn;
            else
                TrmMass[4] = SEND_SIN_MIDDLEOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox83_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox83.Checked)
                TrmMass[4] = SEND_InvSinOn;
            else
                TrmMass[4] = SEND_InvSinOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox84_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox84.Checked)
                TrmMass[4] = SEND_CurrLimitSoundOn;
            else
                TrmMass[4] = SEND_CurrLimitSoundOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown186_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown186.Value);



            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_K_PWM_Nastr;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown188_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown188.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_DEADTIME_Si8233;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox21_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox21.SelectedIndex);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_OCP_DEG;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void comboBox22_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox22.SelectedIndex);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_VDS_LVL;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void button52_Click_1(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CLR_FLT;
            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown190_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown190.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_Crr1Corr;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox96_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox96.Checked)
                TrmMass[4] = SEND_ButtonBreakOnlyOn;
            else
                TrmMass[4] = SEND_ButtonBreakOnlyOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown191_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown191.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_ButtonBreakOnlyPWM;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox97_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox97.Checked)
                TrmMass[4] = SEND_StpLightsOn;
            else
                TrmMass[4] = SEND_StpLightsOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown192_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown192.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CntTurnOffConst;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();

        }

        private void numericUpDown193_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown193.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CntTurnOnConst;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void comboBox23_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboBox15_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox15.SelectedIndex);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_TemperatureTYPE;
            TrmMass[4] = (byte)Trmm;
            TrmMass[5] = (byte)(Trmm >> 8);
            TrmMass[6] = CalcCheckSummTrm();
            Trm();
        }

        private void comboBox23_SelectionChangeCommitted(object sender, EventArgs e)
        {


            short Trmm = Decimal.ToInt16(comboBox23.SelectedIndex);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_TemperatureTYPE_FETs;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void checkBox98_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox98.Checked)
                TrmMass[4] = SEND_TEST_PWM_KEYSOn;
            else
                TrmMass[4] = SEND_TEST_PWM_KEYSOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox24_SelectionChangeCommitted(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(comboBox24.SelectedIndex);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_TstPhase;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown194_ValueChanged(object sender, EventArgs e)
        {

            short Trmm = Decimal.ToInt16(numericUpDown194.Value);
            if (checkBox61.Checked)
                Trmm = (short)(Trmm * 2);




            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 3;//N
                TrmMass[3] = SEND_PWM1;
                TrmMass[4] = (byte)Trmm;
                TrmMass[5] = (byte)(Trmm >> 8);
                TrmMass[6] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void checkBox99_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox99.Checked)
                TrmMass[4] = SEND_VerticalOn;
            else
                TrmMass[4] = SEND_VerticalOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown195_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown195.Value);



            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_SpdStartLevel;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown196_ValueChanged(object sender, EventArgs e)
        {

            short Trmm = Decimal.ToInt16(numericUpDown196.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_Ki_PWM_ModeOff;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown197_ValueChanged(object sender, EventArgs e)
        {

            short Trmm = Decimal.ToInt16(numericUpDown197.Value);
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_StrongModeSpdFilterOffMem;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void panel28_Paint(object sender, PaintEventArgs e)
        {

        }

        private void radioButton16_CheckedChanged_1(object sender, EventArgs e)
        {

            if (radioButton16.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_StrongModeBreakOffOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void radioButton23_CheckedChanged(object sender, EventArgs e)
        {

            if (radioButton23.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_StrongModeMotorOffOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();

            }







        }

        private void radioButton24_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton24.Checked)
            {
                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_StrongModeBreakOffModeMotorOffOff;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();

            }


        }

        private void numericUpDown198_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown198.Value);




            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_RegenOff;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void radioButton25_CheckedChanged(object sender, EventArgs e)
        {

            if (radioButton25.Checked)
            {

                if (radioButton25CannotSndCMD)
                {
                    radioButton25CannotSndCMD = false;
                    return;
                }


                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_LightOnOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void radioButton26_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton26.Checked)
            {

                if (radioButton26CannotSndCMD)
                {
                    radioButton26CannotSndCMD = false;
                    return;
                }



                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_LightOnOff;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void radioButton27_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton27.Checked)
            {

                if (radioButton27CannotSndCMD)
                {
                    radioButton27CannotSndCMD = false;
                    return;
                }



                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_KeyLightStopOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }
        }

        private void numericUpDown199_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown199.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KeyLightBrightness;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();

        }

        private void radioButton28_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton28.Checked)
            {

                if (radioButton28CannotSndCMD)
                {
                    radioButton28CannotSndCMD = false;
                    return;
                }



                TrmMass[0] = 0xff;
                TrmMass[1] = 0xff;
                TrmMass[2] = 2;//N
                TrmMass[3] = SEND_SecondCMD;
                TrmMass[4] = SEND_KeyLightStopGabaritOn;
                TrmMass[5] = CalcCheckSummTrm();
                Trm();
            }

        }

        private void checkBox95_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox95.Checked)
                TrmMass[4] = SEND_MigStopOn;
            else
                TrmMass[4] = SEND_MigStopOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown200_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown200.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_ButtonBreakOnlyTime;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();



        }

        private void label634_Click(object sender, EventArgs e)
        {

        }

        private void label633_Click(object sender, EventArgs e)
        {

        }

        private void label636_Click(object sender, EventArgs e)
        {

        }

        private void label635_Click(object sender, EventArgs e)
        {

        }

        private void numericUpDown201_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown201.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_BreakMonocycleSpd;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }


        private void checkBox100_CheckedChanged(object sender, EventArgs e)
        {

            //CanChangePWM10kHz = false;
            //CanChangePWM10kHzCnt = 20;

            //TrmMass[0] = 0xff;
            //TrmMass[1] = 0xff;
            //TrmMass[2] = 2;//N
            //TrmMass[3] = SEND_SecondCMD;
            //if (checkBox100.Checked)
            //    TrmMass[4] = SEND_PWM10kHzOn;
            //else
            //    TrmMass[4] = SEND_PWM10kHzOff;

            //TrmMass[5] = CalcCheckSummTrm();
            //Trm();

        }

        private void checkBox101_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox101.Checked)
                TrmMass[4] = SEND_LightsFromButtonOn;
            else
                TrmMass[4] = SEND_LightsFromButtonOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void label712_Click(object sender, EventArgs e)
        {

        }

        private void numericUpDown202_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown202.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpKpDeadZoneMem;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown203_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown203.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_PWMSignal;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown205_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown205.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpSlowSpeed;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown204_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown204.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_SlowSpeedForKp;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown207_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown207.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KiKp;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown206_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown206.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KiKpDeadZone;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown208_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown208.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KiMax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown209_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown209.Value);
            Trmm = (short)(Trmm * 25);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_TimeDecreaseKi;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox102_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox102.Checked)
                TrmMass[4] = SEND_KpKpMinusOn;
            else
                TrmMass[4] = SEND_KpKpMinusOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown210_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown210.Value);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpMin;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown211_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown211.Value);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_EpPWMmax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown212_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown212.Value);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_EiPWMmax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown213_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown213.Value);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_EdPWMmax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown211_ValueChanged_1(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown211.Value);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_EpPWMmax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown212_ValueChanged_1(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown212.Value);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_EiPWMmax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown213_ValueChanged_1(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown213.Value);


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_EdPWMmax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void checkBox103_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox103.Checked)
                TrmMass[4] = SEND_SegwayOn;
            else
                TrmMass[4] = SEND_SegwayOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown220_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown220.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_DeadZoneHandleBarSegway;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();
        }

        private void numericUpDown221_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown221.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KRotSegway;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();
        }

        private void numericUpDown219_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown219.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpRotSegway;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();

        }

        private void numericUpDown215_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown215.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KiRotSegway;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_FindGyroVertical;
            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown217_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown217.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_HighSpeed;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();

        }

        private void numericUpDown214_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown214.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_GoalSpeed;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();

        }

        private void numericUpDown222_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown222.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_StartRotHighSpeed;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void numericUpDown223_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown223.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KRotHighSpeed;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void checkBox104_CheckedChanged(object sender, EventArgs e)
        {

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox104.Checked)
                TrmMass[4] = SEND_GyroAccSameOffOn;
            else
                TrmMass[4] = SEND_GyroAccSameOffOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox105_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox105.Checked)
                TrmMass[4] = SEND_HumanSensorOn;
            else
                TrmMass[4] = SEND_HumanSensorOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown216_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown216.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_TimeHumanSensorOff;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();

            Trm();


        }

        private void panel35_Paint(object sender, PaintEventArgs e)
        {

        }

        private void numericUpDown218_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown218.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpKpZoneEnd;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown224_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown224.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpKp2;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown226_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown226.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpKp2DeadZone;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown225_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown225.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpKp2ZoneEnd;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox106_CheckedChanged(object sender, EventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox106.Checked)
                TrmMass[4] = SEND_PWMChangedOn;
            else
                TrmMass[4] = SEND_PWMChangedOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown227_ValueChanged(object sender, EventArgs e)
        {
            double Trmm = Decimal.ToInt32(numericUpDown227.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_PWMChangedThreshold;
            TrmMass[5] = (byte)(int)Trmm;
            TrmMass[6] = (byte)(((int)Trmm) >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox24_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void checkBox107_CheckedChanged(object sender, EventArgs e)
        {
            /*          TrmMass[0] = 0xff;
                      TrmMass[1] = 0xff;
                      TrmMass[2] = 2;//N
                      TrmMass[3] = SEND_SecondCMD;
                      if (checkBox107.Checked)
                          TrmMass[4] = SEND_InvHallAOn;
                      else
                          TrmMass[4] = SEND_InvHallAOff;

                      TrmMass[5] = CalcCheckSummTrm();
                      Trm();

          */
        }

        private void checkBox108_CheckedChanged(object sender, EventArgs e)
        {
            /*TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox108.Checked)
                TrmMass[4] = SEND_InvHallBOn;
            else
                TrmMass[4] = SEND_InvHallBOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();*/

        }

        private void checkBox109_CheckedChanged(object sender, EventArgs e)
        {
            /*          TrmMass[0] = 0xff;
                      TrmMass[1] = 0xff;
                      TrmMass[2] = 2;//N
                      TrmMass[3] = SEND_SecondCMD;
                      if (checkBox109.Checked)
                          TrmMass[4] = SEND_InvHallCOn;
                      else
                          TrmMass[4] = SEND_InvHallCOff;

                      TrmMass[5] = CalcCheckSummTrm();
                      Trm();
          */
        }

        private void checkBox107_CheckStateChanged(object sender, EventArgs e)
        {
            /*          TrmMass[0] = 0xff;
                      TrmMass[1] = 0xff;
                      TrmMass[2] = 2;//N
                      TrmMass[3] = SEND_SecondCMD;
                      if (checkBox107.Checked)
                          TrmMass[4] = SEND_InvHallAOn;
                      else
                          TrmMass[4] = SEND_InvHallAOff;

                      TrmMass[5] = CalcCheckSummTrm();
                      Trm();
          */
        }

        private void checkBox107_MouseEnter(object sender, EventArgs e)
        {

        }

        private void panel50_MouseClick(object sender, MouseEventArgs e)
        {

        }

        private void checkBox107_MouseClick(object sender, MouseEventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox107.Checked)
                TrmMass[4] = SEND_InvHallAOn;
            else
                TrmMass[4] = SEND_InvHallAOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox108_MouseClick(object sender, MouseEventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox108.Checked)
                TrmMass[4] = SEND_InvHallBOn;
            else
                TrmMass[4] = SEND_InvHallBOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox109_MouseClick(object sender, MouseEventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox109.Checked)
                TrmMass[4] = SEND_InvHallCOn;
            else
                TrmMass[4] = SEND_InvHallCOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox111_CheckedChanged(object sender, EventArgs e)
        {
        }

        private void checkBox111_MouseClick(object sender, MouseEventArgs e)
        {
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox111.Checked)
                TrmMass[4] = SEND_BreakFilterOn;
            else
                TrmMass[4] = SEND_BreakFilterOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void tabPage3_Click(object sender, EventArgs e)
        {

        }

        private void numericUpDown229_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown229.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_SpdKdMax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown228_ValueChanged(object sender, EventArgs e)
        {

            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown228.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KdKpSpd;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();



        }

        private void numericUpDown230_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown230.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KdMax;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown231_ValueChanged(object sender, EventArgs e)
        {

            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown231.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KdMin;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown232_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown232.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KiKd;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown235_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown235.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_VectorOnOffSpdLo;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown233_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown233.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_VectorOnOffSpdHi;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void checkBox112_CheckedChanged(object sender, EventArgs e)
        {

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox112.Checked)
                TrmMass[4] = SEND_TrapezoidaWhenBigSpeedOn;
            else
                TrmMass[4] = SEND_TrapezoidaWhenBigSpeedOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();


        }

        private void checkBox113_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox113.Checked)
                TrmMass[4] = SEND_I_PWMmaxSignalOn;
            else
                TrmMass[4] = SEND_I_PWMmaxSignalOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown234_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown234.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_OnDelay;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown236_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown236.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KiUBTCoeff;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown237_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown237.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_SpdKiMin;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown238_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown238.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KiMin;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void numericUpDown239_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown239.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_ELimitedMem;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();
        }

        private void checkBox114_CheckedChanged(object sender, EventArgs e)
        {
            byte[] sendbuf = Encoding.ASCII.GetBytes("Is anybody there?");
            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 2;//N
            TrmMass[3] = SEND_SecondCMD;
            if (checkBox114.Checked)
                TrmMass[4] = SEND_DifferentKdOn;
            else
                TrmMass[4] = SEND_DifferentKdOff;

            TrmMass[5] = CalcCheckSummTrm();
            Trm();


        }

        private void numericUpDown240_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown240.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KdNoManR;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown241_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown241.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_KpDeadZone;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown242_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown242.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_StopIfPWM100Time;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown243_ValueChanged(object sender, EventArgs e)
        {
            ushort Trmm = (ushort)Decimal.ToInt32(numericUpDown243.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_CntKdSwitchCONST;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void numericUpDown244_ValueChanged(object sender, EventArgs e)
        {
            short Trmm = Decimal.ToInt16(numericUpDown244.Value);

            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 4;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_PWMSignalTimer;
            TrmMass[5] = (byte)Trmm;
            TrmMass[6] = (byte)(Trmm >> 8);
            TrmMass[7] = CalcCheckSummTrm();
            Trm();

        }

        private void comboBox25_SelectionChangeCommitted(object sender, EventArgs e)
        {

            switch (comboBox25.SelectedIndex)
            {
                case 1:
                    MessageBox.Show(MyStrings.SpeedLimitSin10kHz, MyStrings.Inform, MessageBoxButtons.OK);
                    break;
                case 2:
                    MessageBox.Show(MyStrings.SpeedLimitSin5kHz, MyStrings.Inform, MessageBoxButtons.OK);
                    break;
            }


            TrmMass[0] = 0xff;
            TrmMass[1] = 0xff;
            TrmMass[2] = 3;//N
            TrmMass[3] = SEND_SecondCMD;
            TrmMass[4] = SEND_PWMkHz;
            switch (comboBox25.SelectedIndex)
            {
                case 0:
                    TrmMass[5] = 1;
                    break;
                case 1:
                    TrmMass[5] = 2;
                    break;
                case 2:
                    TrmMass[5] = 3;
                    break;
            }

            TrmMass[6] = CalcCheckSummTrm();
            Trm();


        }

        private void comboBox25_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button53_Click(object sender, EventArgs e)
        {

        }

        private void button53_Click_1(object sender, EventArgs e)
        {

        }

        private void comboBox26_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (StartCNT == 0)
                MessageBox.Show(MyStrings.CloseOpen, MyStrings.Inform, MessageBoxButtons.OK);
        }
        void GraphSeries()
        {
            if (checkBox16.Checked)
            {
                int comboBox3Num;

                switch (comboBox3.SelectedIndex)
                {
                    case 0:
                        comboBox3Num = 26;
                        break;
                    case 1:
                        comboBox3Num = 27;
                        break;
                    case 2:
                        comboBox3Num = 51;
                        break;
                    case 3:
                        comboBox3Num = 43;
                        break;
                    case 4:
                        comboBox3Num = 7;
                        break;
                    case 5:
                        comboBox3Num = 9;
                        break;
                    case 6:
                        comboBox3Num = 15;
                        break;
                    case 7:
                        comboBox3Num = 11;
                        break;
                    case 8:
                        comboBox3Num = 41;
                        break;
                    case 9:
                        comboBox3Num = 30;
                        break;
                    case 10:
                        comboBox3Num = 31;
                        break;
                    case 11:
                        comboBox3Num = 32;
                        break;
                    case 12:
                        comboBox3Num = 35;
                        break;
                    case 13:
                        comboBox3Num = 36;
                        break;
                    case 14:
                        comboBox3Num = 37;
                        break;
                    case 15:
                        comboBox3Num = 1;
                        break;
                    case 16:
                        comboBox3Num = 0;
                        break;
                    case 17:
                        comboBox3Num = 64;
                        break;
                    case 18:
                        comboBox3Num = 65;
                        break;
                    case 19:
                        comboBox3Num = 66;
                        break;
                    case 20:
                        comboBox3Num = 61;
                        break;
                    case 21:
                        comboBox3Num = 64;
                        break;
                    case 22:
                        comboBox3Num = 65;
                        break;
                    case 23:
                        comboBox3Num = 66;
                        break;

                    default:
                        comboBox3Num = 1;
                        break;
                }


                //Газ с ручки газа
                //Газ после коррекции
                //ШИМ
                //Ток
                //Напряжение батареи
                //Скорость относительная
                //Скорость в км/ч


                switch (comboBox3Num)
                {
                    case 0:
                        chart1.Series[0].Points.AddXY(CntSamples, AlfaXRes);
                        break;
                    case 1:
                        chart1.Series[0].Points.AddXY(CntSamples, AlfaYRes);
                        break;
                    case 2:
                        chart1.Series[0].Points.AddXY(CntSamples, GyroX);
                        break;
                    case 3:
                        chart1.Series[0].Points.AddXY(CntSamples, TiltXRes);
                        break;
                    case 4:
                        chart1.Series[0].Points.AddXY(CntSamples, TiltYRes);
                        break;
                    case 5:
                        chart1.Series[0].Points.AddXY(CntSamples, Ep);
                        break;
                    case 6:
                        chart1.Series[0].Points.AddXY(CntSamples, Ei);
                        break;
                    case 7:
                        chart1.Series[0].Points.AddXY(CntSamples, PWM1);
                        break;
                    case 8:
                        //chart1.Series[0].Points.AddXY(CntSamples, PWM2);
                        break;
                    case 9:
                        chart1.Series[0].Points.AddXY(CntSamples, Cr1 / 1000);
                        break;
                    case 10:
                        //chart1.Series[0].Points.AddXY(CntSamples, Cr2);
                        break;
                    case 11:
                        chart1.Series[0].Points.AddXY(CntSamples, Spd1Res);
                        break;
                    case 12:
                        //chart1.Series[0].Points.AddXY(CntSamples, Spd2Res);
                        break;
                    case 13:
                        //chart1.Series[0].Points.AddXY(CntSamples, SpdAv);
                        break;
                    case 14:
                        chart1.Series[0].Points.AddXY(CntSamples, Kp);
                        break;
                    case 15:
                        chart1.Series[0].Points.AddXY(CntSamples, UBT);
                        break;
                    case 16:
                        chart1.Series[0].Points.AddXY(CntSamples, GyroVert_Steer);
                        break;
                    case 17:
                        chart1.Series[0].Points.AddXY(CntSamples, GyroZFilter);
                        break;
                    case 18:
                        chart1.Series[0].Points.AddXY(CntSamples, AlfaYResPrevAv);
                        break;
                    case 19:
                        chart1.Series[0].Points.AddXY(CntSamples, DiffBetweenTilts);
                        break;
                    case 20:
                        chart1.Series[0].Points.AddXY(CntSamples, TiltZad);
                        break;
                    case 21:
                        chart1.Series[0].Points.AddXY(CntSamples, StartRot);
                        break;
                    case 22:
                        chart1.Series[0].Points.AddXY(CntSamples, Ki);
                        break;
                    case 23:
                        chart1.Series[0].Points.AddXY(CntSamples, KRot);
                        break;
                    case 24:
                        chart1.Series[0].Points.AddXY(CntSamples, KpRot);
                        break;
                    case 25:
                        chart1.Series[0].Points.AddXY(CntSamples, KiRot);
                        break;
                    case 26:
                        chart1.Series[0].Points.AddXY(CntSamples, Preas1ADC);
                        break;
                    case 27:
                        chart1.Series[0].Points.AddXY(CntSamples, Preas2ADC);
                        break;
                    case 28:
                        chart1.Series[0].Points.AddXY(CntSamples, KpSPD);
                        break;
                    case 29:
                        chart1.Series[0].Points.AddXY(CntSamples, AngleLimitReal);
                        break;
                    case 30:
                        chart1.Series[0].Points.AddXY(CntSamples, AccX);
                        break;
                    case 31:
                        chart1.Series[0].Points.AddXY(CntSamples, AccY);
                        break;
                    case 32:
                        chart1.Series[0].Points.AddXY(CntSamples, AccZ);
                        break;
                    case 33:
                        chart1.Series[0].Points.AddXY(CntSamples, TiltZad);
                        break;
                    case 34:
                        chart1.Series[0].Points.AddXY(CntSamples, _48V);
                        break;
                    case 35:
                        chart1.Series[0].Points.AddXY(CntSamples, GyroXFl);
                        break;
                    case 36:
                        chart1.Series[0].Points.AddXY(CntSamples, GyroYFl);
                        break;
                    case 37:
                        chart1.Series[0].Points.AddXY(CntSamples, GyroZFl);
                        break;
                    case 38:
                        chart1.Series[0].Points.AddXY(CntSamples, Ed);
                        break;
                    case 39:
                        chart1.Series[0].Points.AddXY(CntSamples, GyroYAv);
                        break;
                    case 40:
                        chart1.Series[0].Points.AddXY(CntSamples, KdI);
                        break;
                    case 41:
                        chart1.Series[0].Points.AddXY(CntSamples, Spd1Fl);
                        break;
                    case 42:
                        //chart1.Series[0].Points.AddXY(CntSamples, Spd2Fl);
                        break;
                    case 43:
                        int u = (int)CurrPerDigit;
                        u = (int)(EPID_Res * u);
                        chart1.Series[0].Points.AddXY(CntSamples, (float)(((float)u) / 1000));
                        break;
                    case 44:
                        chart1.Series[0].Points.AddXY(CntSamples, Phase1Period1);
                        break;
                    case 45:
                        chart1.Series[0].Points.AddXY(CntSamples, Phase1Period2);
                        break;
                    case 46:
                        //chart1.Series[0].Points.AddXY(CntSamples, Phase1Period3);
                        break;
                    case 47:
                        chart1.Series[0].Points.AddXY(CntSamples, Phase1Period4);
                        break;
                    case 48:
                        chart1.Series[0].Points.AddXY(CntSamples, Phase1Period5);
                        break;
                    case 49:
                        chart1.Series[0].Points.AddXY(CntSamples, Phase1Period6);
                        break;
                    case 50:
                        //chart1.Series[0].Points.AddXY(CntSamples, Phase1PeriodTTL);
                        break;
                    case 51:
                        chart1.Series[0].Points.AddXY(CntSamples, Spd1USTKMH);
                        break;
                    case 52:
                        chart1.Series[0].Points.AddXY(CntSamples, PhaseCr);
                        break;
                    case 53:
                        chart1.Series[0].Points.AddXY(CntSamples, EpCurr1);
                        break;
                    case 54:
                        chart1.Series[0].Points.AddXY(CntSamples, ECurr1Summ);
                        break;
                    case 55:
                        chart1.Series[0].Points.AddXY(CntSamples, PhasePer1);
                        break;
                    case 56:
                        chart1.Series[0].Points.AddXY(CntSamples, Halls);
                        break;
                    case 57:
                        chart1.Series[0].Points.AddXY(CntSamples, CurrA_P);
                        break;
                    case 58:
                        chart1.Series[0].Points.AddXY(CntSamples, CurrA_N);
                        break;
                    case 59:
                        chart1.Series[0].Points.AddXY(CntSamples, CurrC_P);
                        break;
                    case 60:
                        chart1.Series[0].Points.AddXY(CntSamples, CurrC_N);
                        break;
                    case 61:
                        chart1.Series[0].Points.AddXY(CntSamples, ADCThrottleBreak);
                        break;
                    case 62:
                        chart1.Series[0].Points.AddXY(CntSamples, Eid);
                        break;
                    case 63:
                        //chart1.Series[0].Points.AddXY(CntSamples, Theta1CntPWMSND);
                        break;
                    case 64:
                        chart1.Series[0].Points.AddXY(CntSamples, EpLog);
                        break;
                    case 65:
                        chart1.Series[0].Points.AddXY(CntSamples, EiLog);
                        break;
                    case 66:
                        chart1.Series[0].Points.AddXY(CntSamples, EdLog);
                        break;




                }

            }



            if (checkBox17.Checked)
            {
                int comboBox3Num;
                switch (comboBox4.SelectedIndex)
                {
                    case 0:
                        comboBox3Num = 26;
                        break;
                    case 1:
                        comboBox3Num = 27;
                        break;
                    case 2:
                        comboBox3Num = 51;
                        break;
                    case 3:
                        comboBox3Num = 43;
                        break;
                    case 4:
                        comboBox3Num = 7;
                        break;
                    case 5:
                        comboBox3Num = 9;
                        break;
                    case 6:
                        comboBox3Num = 15;
                        break;
                    case 7:
                        comboBox3Num = 11;
                        break;
                    case 8:
                        comboBox3Num = 41;
                        break;
                    case 9:
                        comboBox3Num = 30;
                        break;
                    case 10:
                        comboBox3Num = 31;
                        break;
                    case 11:
                        comboBox3Num = 32;
                        break;
                    case 12:
                        comboBox3Num = 35;
                        break;
                    case 13:
                        comboBox3Num = 36;
                        break;
                    case 14:
                        comboBox3Num = 37;
                        break;
                    case 15:
                        comboBox3Num = 1;
                        break;
                    case 16:
                        comboBox3Num = 0;
                        break;
                    case 17:
                        comboBox3Num = 64;
                        break;
                    case 18:
                        comboBox3Num = 65;
                        break;
                    case 19:
                        comboBox3Num = 66;
                        break;
                    case 20:
                        comboBox3Num = 61;
                        break;
                    case 21:
                        comboBox3Num = 64;
                        break;
                    case 22:
                        comboBox3Num = 65;
                        break;
                    case 23:
                        comboBox3Num = 66;
                        break;

                    default:
                        comboBox3Num = 1;
                        break;
                }

                switch (comboBox3Num)
                {
                    case 0:
                        chart1.Series[1].Points.AddXY(CntSamples, AlfaXRes);
                        break;
                    case 1:
                        chart1.Series[1].Points.AddXY(CntSamples, AlfaYRes);
                        break;
                    case 2:
                        chart1.Series[1].Points.AddXY(CntSamples, GyroX);
                        break;
                    case 3:
                        chart1.Series[1].Points.AddXY(CntSamples, TiltXRes);
                        break;
                    case 4:
                        chart1.Series[1].Points.AddXY(CntSamples, TiltYRes);
                        break;
                    case 5:
                        chart1.Series[1].Points.AddXY(CntSamples, Ep);
                        break;
                    case 6:
                        chart1.Series[1].Points.AddXY(CntSamples, Ei);
                        break;
                    case 7:
                        chart1.Series[1].Points.AddXY(CntSamples, PWM1);
                        break;
                    case 8:
                        //chart1.Series[1].Points.AddXY(CntSamples, PWM2);
                        break;
                    case 9:
                        chart1.Series[1].Points.AddXY(CntSamples, Cr1 / 1000);
                        break;
                    case 10:
                        //chart1.Series[1].Points.AddXY(CntSamples, Cr2);
                        break;
                    case 11:
                        chart1.Series[1].Points.AddXY(CntSamples, Spd1Res);
                        break;
                    case 12:
                        //chart1.Series[1].Points.AddXY(CntSamples, Spd2Res);
                        break;
                    case 13:
                        //chart1.Series[1].Points.AddXY(CntSamples, SpdAv);
                        break;
                    case 14:
                        chart1.Series[1].Points.AddXY(CntSamples, Kp);
                        break;
                    case 15:
                        chart1.Series[1].Points.AddXY(CntSamples, UBT);
                        break;
                    case 16:
                        chart1.Series[1].Points.AddXY(CntSamples, GyroVert_Steer);
                        break;
                    case 17:
                        chart1.Series[1].Points.AddXY(CntSamples, GyroZFilter);
                        break;
                    case 18:
                        chart1.Series[1].Points.AddXY(CntSamples, AlfaYResPrevAv);
                        break;
                    case 19:
                        chart1.Series[1].Points.AddXY(CntSamples, DiffBetweenTilts);
                        break;
                    case 20:
                        chart1.Series[1].Points.AddXY(CntSamples, TiltZad);
                        break;
                    case 21:
                        chart1.Series[1].Points.AddXY(CntSamples, StartRot);
                        break;
                    case 22:
                        chart1.Series[1].Points.AddXY(CntSamples, Ki);
                        break;
                    case 23:
                        chart1.Series[1].Points.AddXY(CntSamples, KRot);
                        break;
                    case 24:
                        chart1.Series[1].Points.AddXY(CntSamples, KpRot);
                        break;
                    case 25:
                        chart1.Series[1].Points.AddXY(CntSamples, KiRot);
                        break;
                    case 26:
                        chart1.Series[1].Points.AddXY(CntSamples, Preas1ADC);
                        break;
                    case 27:
                        chart1.Series[1].Points.AddXY(CntSamples, Preas2ADC);
                        break;
                    case 28:
                        chart1.Series[1].Points.AddXY(CntSamples, KpSPD);
                        break;
                    case 29:
                        chart1.Series[1].Points.AddXY(CntSamples, AngleLimitReal);
                        break;
                    case 30:
                        chart1.Series[1].Points.AddXY(CntSamples, AccX);
                        break;
                    case 31:
                        chart1.Series[1].Points.AddXY(CntSamples, AccY);
                        break;
                    case 32:
                        chart1.Series[1].Points.AddXY(CntSamples, AccZ);
                        break;
                    case 33:
                        chart1.Series[1].Points.AddXY(CntSamples, TiltZad);
                        break;
                    case 34:
                        chart1.Series[1].Points.AddXY(CntSamples, _48V);
                        break;
                    case 35:
                        chart1.Series[1].Points.AddXY(CntSamples, GyroXFl);
                        break;
                    case 36:
                        chart1.Series[1].Points.AddXY(CntSamples, GyroYFl);
                        break;
                    case 37:
                        chart1.Series[1].Points.AddXY(CntSamples, GyroZFl);
                        break;
                    case 38:
                        chart1.Series[1].Points.AddXY(CntSamples, Ed);
                        break;
                    case 39:
                        chart1.Series[1].Points.AddXY(CntSamples, GyroYAv);
                        break;
                    case 40:
                        chart1.Series[1].Points.AddXY(CntSamples, KdI);
                        break;
                    case 41:
                        chart1.Series[1].Points.AddXY(CntSamples, Spd1Fl);
                        break;
                    case 42:
                        //chart1.Series[1].Points.AddXY(CntSamples, Spd2Fl);
                        break;
                    case 43:
                        int u = (int)CurrPerDigit;
                        u = (int)(EPID_Res * u);
                        chart1.Series[1].Points.AddXY(CntSamples, (float)(((float)u) / 1000));
                        break;
                    case 44:
                        chart1.Series[1].Points.AddXY(CntSamples, Phase1Period1);
                        break;
                    case 45:
                        chart1.Series[1].Points.AddXY(CntSamples, Phase1Period2);
                        break;
                    case 46:
                        //chart1.Series[1].Points.AddXY(CntSamples, Phase1Period3);
                        break;
                    case 47:
                        chart1.Series[1].Points.AddXY(CntSamples, Phase1Period4);
                        break;
                    case 48:
                        chart1.Series[1].Points.AddXY(CntSamples, Phase1Period5);
                        break;
                    case 49:
                        chart1.Series[1].Points.AddXY(CntSamples, Phase1Period6);
                        break;
                    case 50:
                        //chart1.Series[1].Points.AddXY(CntSamples, Phase1PeriodTTL);
                        break;
                    case 51:
                        chart1.Series[1].Points.AddXY(CntSamples, Spd1USTKMH);
                        break;
                    case 52:
                        chart1.Series[1].Points.AddXY(CntSamples, PhaseCr);
                        break;
                    case 53:
                        chart1.Series[1].Points.AddXY(CntSamples, EpCurr1);
                        break;
                    case 54:
                        chart1.Series[1].Points.AddXY(CntSamples, ECurr1Summ);
                        break;
                    case 55:
                        chart1.Series[1].Points.AddXY(CntSamples, PhasePer1);
                        break;
                    case 56:
                        chart1.Series[1].Points.AddXY(CntSamples, Halls);
                        break;
                    case 57:
                        chart1.Series[1].Points.AddXY(CntSamples, CurrA_P);
                        break;
                    case 58:
                        chart1.Series[1].Points.AddXY(CntSamples, CurrA_N);
                        break;
                    case 59:
                        chart1.Series[1].Points.AddXY(CntSamples, CurrC_P);
                        break;
                    case 60:
                        chart1.Series[1].Points.AddXY(CntSamples, CurrC_N);
                        break;
                    case 61:
                        chart1.Series[1].Points.AddXY(CntSamples, ADCThrottleBreak);
                        break;
                    case 62:
                        chart1.Series[1].Points.AddXY(CntSamples, Eid);
                        break;
                    case 63:
                        //chart1.Series[1].Points.AddXY(CntSamples, Phase1Period1Up);
                        break;
                    case 64:
                        chart1.Series[1].Points.AddXY(CntSamples, EpLog);
                        break;
                    case 65:
                        chart1.Series[1].Points.AddXY(CntSamples, EiLog);
                        break;
                    case 66:
                        chart1.Series[1].Points.AddXY(CntSamples, EdLog);
                        break;


                }

            }


            if (checkBox18.Checked)
                switch (comboBox5.SelectedIndex)
                {
                    case 0:
                        chart1.Series[2].Points.AddXY(CntSamples, AlfaXRes);
                        break;
                    case 1:
                        chart1.Series[2].Points.AddXY(CntSamples, AlfaYRes);
                        break;
                    case 2:
                        chart1.Series[2].Points.AddXY(CntSamples, GyroX);
                        break;
                    case 3:
                        chart1.Series[2].Points.AddXY(CntSamples, TiltXRes);
                        break;
                    case 4:
                        chart1.Series[2].Points.AddXY(CntSamples, TiltYRes);
                        break;
                    case 5:
                        chart1.Series[2].Points.AddXY(CntSamples, Ep);
                        break;
                    case 6:
                        chart1.Series[2].Points.AddXY(CntSamples, Ei);
                        break;
                    case 7:
                        chart1.Series[2].Points.AddXY(CntSamples, PWM1);
                        break;
                    case 8:
                        //chart1.Series[2].Points.AddXY(CntSamples, PWM2);
                        break;
                    case 9:
                        chart1.Series[2].Points.AddXY(CntSamples, Cr1 / 1000);
                        break;
                    case 10:
                        //chart1.Series[2].Points.AddXY(CntSamples, Cr2);
                        break;
                    case 11:
                        chart1.Series[2].Points.AddXY(CntSamples, Spd1Res);
                        break;
                    case 12:
                        //chart1.Series[2].Points.AddXY(CntSamples, Spd2Res);
                        break;
                    case 13:
                        //chart1.Series[2].Points.AddXY(CntSamples, SpdAv);
                        break;
                    case 14:
                        chart1.Series[2].Points.AddXY(CntSamples, Kp);
                        break;
                    case 15:
                        chart1.Series[2].Points.AddXY(CntSamples, UBT);
                        break;
                    case 16:
                        chart1.Series[2].Points.AddXY(CntSamples, GyroVert_Steer);
                        break;
                    case 17:
                        chart1.Series[2].Points.AddXY(CntSamples, GyroZFilter);
                        break;
                    case 18:
                        chart1.Series[2].Points.AddXY(CntSamples, AlfaYResPrevAv);
                        break;
                    case 19:
                        chart1.Series[2].Points.AddXY(CntSamples, DiffBetweenTilts);
                        break;
                    case 20:
                        chart1.Series[2].Points.AddXY(CntSamples, TiltZad);
                        break;
                    case 21:
                        chart1.Series[2].Points.AddXY(CntSamples, StartRot);
                        break;
                    case 22:
                        chart1.Series[2].Points.AddXY(CntSamples, Ki);
                        break;
                    case 23:
                        chart1.Series[2].Points.AddXY(CntSamples, KRot);
                        break;
                    case 24:
                        chart1.Series[2].Points.AddXY(CntSamples, KpRot);
                        break;
                    case 25:
                        chart1.Series[2].Points.AddXY(CntSamples, KiRot);
                        break;
                    case 26:
                        chart1.Series[2].Points.AddXY(CntSamples, Preas1ADC);
                        break;
                    case 27:
                        chart1.Series[2].Points.AddXY(CntSamples, Preas2ADC);
                        break;
                    case 28:
                        chart1.Series[2].Points.AddXY(CntSamples, KpSPD);
                        break;
                    case 29:
                        chart1.Series[2].Points.AddXY(CntSamples, AngleLimitReal);
                        break;
                    case 30:
                        chart1.Series[2].Points.AddXY(CntSamples, AccX);
                        break;
                    case 31:
                        chart1.Series[2].Points.AddXY(CntSamples, AccY);
                        break;
                    case 32:
                        chart1.Series[2].Points.AddXY(CntSamples, AccZ);
                        break;
                    case 33:
                        chart1.Series[2].Points.AddXY(CntSamples, TiltZad);
                        break;
                    case 34:
                        chart1.Series[2].Points.AddXY(CntSamples, _48V);
                        break;
                    case 35:
                        chart1.Series[2].Points.AddXY(CntSamples, GyroXFl);
                        break;
                    case 36:
                        chart1.Series[2].Points.AddXY(CntSamples, GyroYFl);
                        break;
                    case 37:
                        chart1.Series[2].Points.AddXY(CntSamples, GyroZFl);
                        break;
                    case 38:
                        chart1.Series[2].Points.AddXY(CntSamples, Ed);
                        break;
                    case 39:
                        chart1.Series[2].Points.AddXY(CntSamples, GyroYAv);
                        break;
                    case 40:
                        chart1.Series[2].Points.AddXY(CntSamples, KdI);
                        break;
                    case 41:
                        chart1.Series[2].Points.AddXY(CntSamples, Spd1Fl);
                        break;
                    case 42:
                        //chart1.Series[2].Points.AddXY(CntSamples, Spd2Fl);
                        break;
                    case 43:
                        int u = (int)CurrPerDigit;
                        u = (int)(EPID_Res * u);
                        chart1.Series[2].Points.AddXY(CntSamples, (float)(((float)u) / 1000));
                        break;
                    case 44:
                        chart1.Series[2].Points.AddXY(CntSamples, Phase1Period1);
                        break;
                    case 45:
                        chart1.Series[2].Points.AddXY(CntSamples, Phase1Period2);
                        break;
                    case 46:
                        //chart1.Series[2].Points.AddXY(CntSamples, Phase1Period3);
                        break;
                    case 47:
                        chart1.Series[2].Points.AddXY(CntSamples, Phase1Period4);
                        break;
                    case 48:
                        chart1.Series[2].Points.AddXY(CntSamples, Phase1Period5);
                        break;
                    case 49:
                        chart1.Series[2].Points.AddXY(CntSamples, Phase1Period6);
                        break;
                    case 50:
                        //chart1.Series[2].Points.AddXY(CntSamples, Phase1PeriodTTL);
                        break;
                    case 51:
                        chart1.Series[2].Points.AddXY(CntSamples, Spd1USTKMH);
                        break;
                    case 52:
                        chart1.Series[2].Points.AddXY(CntSamples, PhaseCr);
                        break;
                    case 53:
                        chart1.Series[2].Points.AddXY(CntSamples, EpCurr1);
                        break;
                    case 54:
                        chart1.Series[2].Points.AddXY(CntSamples, ECurr1Summ);
                        break;
                    case 55:
                        chart1.Series[2].Points.AddXY(CntSamples, PhasePer1);
                        break;
                    case 56:
                        chart1.Series[2].Points.AddXY(CntSamples, Halls);
                        break;
                    case 57:
                        chart1.Series[2].Points.AddXY(CntSamples, CurrA_P);
                        break;
                    case 58:
                        chart1.Series[2].Points.AddXY(CntSamples, CurrA_N);
                        break;
                    case 59:
                        chart1.Series[2].Points.AddXY(CntSamples, CurrC_P);
                        break;
                    case 60:
                        chart1.Series[2].Points.AddXY(CntSamples, CurrC_N);
                        break;
                    case 61:
                        chart1.Series[2].Points.AddXY(CntSamples, ADCThrottleBreak);
                        break;
                    case 62:
                        chart1.Series[2].Points.AddXY(CntSamples, Eid);
                        break;

                    case 63:
                        //chart1.Series[2].Points.AddXY(CntSamples, Theta1CntPWMSND);
                        break;


                    /*                              case 64:
                                                      chart1.Series[2].Points.AddXY(CntSamples, GyroZFl);
                                                      break;

                  */
                    case 65:
                        chart1.Series[2].Points.AddXY(CntSamples, EpLog);
                        break;
                    case 66:
                        chart1.Series[2].Points.AddXY(CntSamples, EiLog);
                        break;
                    case 67:
                        chart1.Series[2].Points.AddXY(CntSamples, EdLog);
                        break;


                }

        }




        private void UDPRead()
        {
            int i;
            String Str;
            UdpClient listener = new UdpClient(listenPort);
            IPEndPoint EP = new IPEndPoint(IPAddress.Any, listenPort);


            while (true)
            {
                byte[] bytes = listener.Receive(ref EP);

                for (i = 0; i < bytes.Length - 2; i++)
                    PacketRec[i] = bytes[i + 2];

                IPaddr = EP.Address;

                this.Invoke((MethodInvoker)delegate ()
                {
                    label14.Text = EP.Address.ToString();
                });


                if (CalcCheckSummRec() == PacketRec[PacketRec[0] + 1])
                    RaspakHC05();
            }

        }




    }
}

