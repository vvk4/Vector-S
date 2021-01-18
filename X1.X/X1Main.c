/*
 * Author: Viacheslav Kulakov
 *
 */




#if defined(__PIC24E__)
#include <p24Exxxx.h>

#elif defined (__PIC24F__)
#include <p24Fxxxx.h>

#elif defined(__PIC24H__)
#include <p24Hxxxx.h>

#elif defined(__dsPIC30F__)
#include <p30Fxxxx.h>

#elif defined (__dsPIC33E__)
#include <p33Exxxx.h>

#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>

#endif


#include "Mn.h"
#include <xc.h>

#include <math.h>


int FGS __attribute__((space(prog), address(0xF80004))) = 0xFFFD;
#if defined INT_FRC
int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0xFF79; 
#else
int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0xFF7B;
#endif
int FOSC __attribute__((space(prog), address(0xF80008))) = 0xff9a; 
int FWDT __attribute__((space(prog), address(0xF8000A))) = 0xff7f; 
int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xFFE7; 
int FICD __attribute__((space(prog), address(0xF8000E))) = 0xffdB; 
int FAS __attribute__((space(prog), address(0xF80010))) = 0xFFCF;


const unsigned char LowDrive[7] = {0b000, //empty
    0b001, //1
    0b010, //2
    0b001, //3
    0b100, //4
    0b100, //5
    0b010}; //6

const unsigned char HiDrive[7] = {0b000, //empty
    0b010, //1
    0b100, //2
    0b100, //3
    0b001, //4
    0b010, //5
    0b001}; //6


unsigned int SensorlessSpdChngCnt, SensorlessSpdChngCntConst;


void SensorlessInit(void);

void SetStartingProfile3PsnBtn(void);
void ResetMPU6000(void);
void MPU60000Init(void);


void VectorInit(void);
void T4_5Init(void);
void T6_7Init(void);

void T8Init(void);
void TrapeziumInit(void);
void UBT_To_V(void);
void CurrentProtectionPID(void);


void ReadMPU6050(unsigned char Addr, unsigned char N);
void ResetPIN_HC05(void);
void PID_OnOff_Func(void);


void SVPWM1(void);

void SVPWM1_SetPWM(void);
void InitPWM_Vector(void);

void SetHallDelay1_F_UP(void);
void SetHallDelay1_B_UP(void);
void SetPWM_ChagerViaMotor();
void CriticalErrorLed(void);
void WheelingFunc(void);

void WriteMPU6050(unsigned char Addr, unsigned char N, unsigned char *Mass);
void writeByte(unsigned char ADDR, unsigned char Data);
unsigned char readByte(unsigned char ADDR);


void AutoNastroykaCMFStart(unsigned int AutoNastroykaStateFin);

void CmdSendUnlockMSG(void);

int MaxSpdCoeff, TemperatureMPU6000;
unsigned int Theta1Cnt = 10, Theta2Cnt = 10, Theta1CntPWM, Theta2CntPWM, CntHvZ_Cr, SpeedControlPIDOffCnt;
unsigned char Sensor1_Prev_OP, CntAcqSensor, CntBEMF, CntBEMFMax, TemperatureTYPE;

unsigned int BackwardCnt, SV_PWM1_0, SV_PWM1_1, SV_PWM1_2, Khard;
float Crr1Corr, DeadZoneHandleBarSegwayMustBe;

char HallDelay1_F = 0, HallDelay1_B = 0;
char HallDelay1_FMustBe, HallDelay1_BMustBe, HallDelay1_FMustBeTemp, HallDelay1_BMustBeTemp;
long int Phase1Period1, Phase1Period2, Phase1PeriodPrev, Phase1PeriodTek, TMR7Sensorless, Phase1Period1Show, T6Hi;
unsigned long int Phase1PeriodMass[PhasePERMASS_DEF], Phase1PeriodSumm;

long int RotAddSumm;

void DefaultProfileOptions(void);
float GetTemperaturePTC_KTY81_210_FETs(unsigned int ResTemp);
void StartCharging(void);
void SegAll(void);

float DiffPidAdd, ButtonBreakOnlyTimeAdd, KpKpDeadZone, KpKp2DeadZone, KiKpDeadZone, KpKpZoneEnd, KpKp2ZoneEnd;

unsigned char KpKpDeadZoneMem, KiKpDeadZoneMem;
const float CurrPerDigitDEF = 48.34;

//unsigned char Sensor1_PrevAfterSND,Sensor1Snd,Sensor1_PrevSND,Sensor1BeforeReadSnd;;
unsigned char Sensor1, Sensor1_Prev, Sensor1_PrevSensorless, T3Cnt = 4, SensOrder1, Sounds, SoundNum;
unsigned char Sensor2, Sensor2_Prev, SpdKpMax, BMS_L, SpdKdMax;
int PWMPrevPID, PWM1, PWM2, PWMMonocycleSlaveFmMaster, PWMNastr, PWM1Show, PWM1Prev, PWM1_Mem, MAX_PWM_CONST, MAX_PWM = MAX_PWM_CONST_MONOCYCLE10kHz, SenosrlessPWM1, SenosrlessPWM1_1Const, SenosrlessPWM1_2Const, PWM1_SIN_TST = 70, DIRPWM1_TstKeys;
unsigned int CntUDPFill, CntUDPFillConst, SpeedLmt, ADCThrottle, ADCThroottleZero, CntCalibrateCurr, PR2Cnt, PR8Cnt, BuzzerOnTimeConst, BuzzerOffTimeConst, BuzzerOnTime, BuzzerOffTime, ADCThrottleBreak, ADCThrottleBreakADC, GazImm;
unsigned int ADCThrottleBreak_Mass[ADCThrottleBreak_SIZE];
unsigned int CntMigStop, CntMigStopConst = 15;
long int ADCThrottleSumm, ADCThrottleBreakSumm;
unsigned long int ADCThrottleBreak_Summ;
int JoystickCalibrX, JoystickCalibrY, RotAddI, PWMChangedThreshold;
int SensorThresholdDn, SensorThresholdUp, BreakThreshold, KFirstBreak;
int BreakThresholdUp, BreakThresholdDn, BreakThresholdDnTmp, SensorThresholdDnTmp;
int Curr1, Curr1_int, PhaseCurr, Crr1, ZeroCurr1, AccXAvRes, AccYAvRes, AccZAvRes;
long int ZeroCurr1Summ;
int TiltX, TiltY, TiltXRes, TiltYResShow;
FLAGS Flgs, Flgs1, Flgs2, Flgs3, Flgs4, Flgs5, Flgs6, Flgs7, Flgs8, FlgsErr, Flgs1Err, Flgs2Err;
STAT_FLAGS StatFlgs, StatFlgs1, StatFlgs2, StatFlgs3, StatFlgs4;


void FindGyroVerticalFunc(void);

unsigned char T3Cnt1 = 4, CurrentMaxCurrentOnly;
float CurrA, CurrC, Curr1Show, CurrUstCurrentOnly;

void Spd0TimerStateMachine(void);
float Throttle, KThrottle, KpAddSpd, KpKpSpd, KdKpSpd, K_HallDelay, DeltaDelay, KdAddSpd;
float E_PWM_Mode, PWM_Mode_Target, ESumm_PWM_Mode, Ep_PWM_Mode, KiUBTCoeff;
int StartRotQuantum, KRotQuantum;
unsigned int MAX_PWM_MEM, MAX_PWM_MEM_WORK, MAX_PWM_Revers, MAX_PWM_MustBe, CurrProtectSoundCnt, SpdStartLevel;

unsigned long int CntSamples, PhaseCnt1, PhaseCnt2, Amplitude1, Amplitude2;
float Ep, Ed, Ei, Kp, Kd = 0, Ki, KiMustBe, KiNoMan, KiWheelingMem, ESumm;
float E, EPlus, EPrevPlus, KdNoMan, KdNoManR, KdOneTwoLeg, EPrev, KpMustBe, KpNoMan, KdMustBe;

float KdMax, KdMin, KiKd, Eid, KdDiff, KdMustBePrev, KiMustBe1, KiAdd, ELimited, ELimitedMem;
float KpRot, KpRotMustBe, KdRot, KiRot, KiRotMustBe, KpMax, KiMax, KpMin;
float KpWheelingMem, KpSlowSpeed, KiKp, KiKpMustBe;

unsigned char TestSIN_Ok_Mass[12][2], TestSINOkMassCnt, TestCWCntMass;
long int CurrSinTSTMass[12], CurrMinSinTST;

long int GyroZFilter;
unsigned char Theta1Zero, Theta2Zero, HallDelayCnt_1, HallDelayCnt_2, Theta1CntPWMSND, Theta2CntPWMSND;
unsigned char _3psnSwitchBtNotPressed, _3psnSwitchBt3, _3psnSwitchBt4, CriticalError, OrderCnt;
unsigned char HighSpeed, GoalSpeed;
int KRotHighSpeed, VectorOnOffSpdLo, VectorOnOffSpdHi;


unsigned char SensorllessSpdThreshold;
unsigned char PacketTrm_U3[40];
unsigned char PacketRec_U3[30];

unsigned char StateOdm = 1, NextHallClbr, CntCalibrHalls;

char HallDelayMem1_F, HallDelayMem1_B;


void FillPINResetMass(void);
void StateMachinePID(void);
void PWM100StateMachine(void);

unsigned int CntUDPTrm, TmrOdmtrWrCnt, SensorLessOnCnt;
int GyroAv[257];
int TiltAv[MAX_TiltYAV];
unsigned char P_U, I_U;
float P_Curr, I_Curr;
int CurrA_P_Av, CurrA_N_Av, CurrC_P_Av, CurrC_N_Av;


float EChagerCurrSumm, EChagerUSumm;

long int GyroYAv;
int RotAddP, RotAddD, RotAdd, MPU6050_TimeOut, BigCurrent, ChagerCurr;
long TiltYAv;

unsigned char ErrorCode, StartCnt, NoBalanceCode, GyroVertical;
unsigned char TiltTimoutCnt, TiltTimoutConst, MPU6050Mass[100], PinCodeMass[28], PinCodeMassOptions[6], PinCodeMassOptionsUnlock[6];

UINT8 Acc_txBuf[30], Acc_rxBuf[30];
unsigned int SPIAccbyteCount, SPIRxCnt, CntAutoNastroykaState257;
int AccX, AccY, AccZ;
int AccXPrev, AccYPrev, AccZPrev, GyroXPrev, GyroYPrev, GyroZPrev;



float AccXFl, AccYFl, AccZFl, AccYFlSpd, AccXFlShow, AccYFlShow, AccZFlShow, AccXFlNoGravity, AccYFlNoGravity, AccZFlNoGravity;
float Din, DinH, Dout, DoutL, Dacc, KH = 1.01, KL = 1;
float Yres, YresPrev, DinPrev;


int _5V, _3V, CurrA_P, CurrA_N, CurrC_P, CurrC_N, _12V;
long int CurrA_P_Summ, CurrA_N_Summ, CurrC_P_Summ, CurrC_N_Summ;

unsigned char CntRecAcc;

UINT8 Gyro_txBuf[30], Gyro_rxBuf[30];
unsigned int SPIGyrobyteCount, SPIRxGyroCnt, PR8Temp, PR2Temp, PR8TempTemp;
int GyroX, GyroVert_Steer, GyroY, GyroZ, GyroXPrev1, GyroYPrev1, GyroZPrev1;
float GyroXFl, GyroYFl, GyroZFl, EPID_Res, EPID_Res_Target, EPID_ResTmp, EPID_Res_Tek;
unsigned char CntRecGyro, MI2C1Interrupt_TimeOut;
unsigned int CurrLimit, CurrLimitWork, SensorLessCurrLimit, CntTestingSinDelay;
unsigned char PhasePERMASS, PhasePERMASS_SHFT, adcBackEMFFilter, MPU6050ReadStateMachine;


unsigned char Sensor1_Prev_Const = 1, CntZero, CntZeroConst = 5, ChangeCurrStateMachine;
unsigned int MassTMPPhaseA[MassTMPSIZE],MassTMPPhaseB[MassTMPSIZE],MassTMPPhaseC[MassTMPSIZE], MassTMPNeutral[MassTMPSIZE], CntPhase = 0, CntGyroAccSameOff, Phase1Period1Up;
float _3VFl, _5VFl, _12VFl, SlowSpeedForKpFl;

unsigned char TrmMass_U3[255], SlowSpeedForKp;


unsigned char _SELF_TEST_X, _SELF_TEST_Y, _SELF_TEST_Z, _SELF_TEST_A, _SMPLRT_DIV, _CONFIG, _GYRO_CONFIG, _ACCEL_CONFIG, _FIFO_EN,
_I2C_MST_CTRL, _I2C_SLV0_ADDR, _I2C_SLV0_REG, _I2C_SLV0_CTRL, _I2C_SLV1_ADDR, _I2C_SLV1_REG, _I2C_SLV1_CTRL, _I2C_SLV2_ADDR,
_I2C_SLV2_REG, _I2C_SLV2_CTRL, _I2C_SLV3_ADDR, _I2C_SLV3_REG, _I2C_SLV3_CTRL, _I2C_SLV4_ADDR, _I2C_SLV4_REG, _I2C_SLV4_DO,
_I2C_SLV4_CTRL, _I2C_SLV4_DI, _I2C_MST_STATUS, _INT_PIN_CFG, _INT_ENABLE, _INT_STATUS, _ACCEL_XOUT_H, _ACCEL_XOUT_L,
_ACCEL_YOUT_H, _ACCEL_YOUT_L, _ACCEL_ZOUT_H, _ACCEL_ZOUT_L, _TEMP_OUT_H, _TEMP_OUT_L, _GYRO_XOUT_H, _GYRO_XOUT_L, _GYRO_YOUT_H,
_GYRO_YOUT_L, _GYRO_ZOUT_H, _GYRO_ZOUT_L, _EXT_SENS_DATA_00, _I2C_SLV0_DO, _I2C_SLV1_DO, _I2C_SLV2_DO, _I2C_SLV3_DO,
_I2C_MST_DELAY_CTRL, _SIGNAL_PATH_RESET, _USER_CTRL, _PWR_MGMT_1, _PWR_MGMT_2, _FIFO_COUNTH, _FIFO_COUNTL, _FIFO_R_W, _WHO_AM_I;



BYTE RecBytes[254];



//	Function Prototypes
void SegMain(void);
void OSC_Init(void);
void InitSegAll(void);
void InitPorts(void);
void T3Init(void);
void InitBLDCPorts(void);
void InitPWM(void);
void WF_GyroSpiEnableChipSelect(void);
void WF_GyroSpiDisableChipSelect(void);
void GyroWFSpiTxRx(UINT8 *p_txBuf, UINT16 txLen, UINT8 *p_rxBuf, UINT16 rxLen);
void TxRxSPI_TST(void);
void MonoWheel(void);
void SendOptions(void);
void GyroAcel(void);



void Phases1(void);
void Phases2(void);
void ChangePWM1(unsigned int PWM);
void TrmControls_U3(void);

void ChangeProfile(void);

void InitPort_U3(void);
void UARTInit_U3(void);
unsigned char CalcCheckSumm(unsigned int N, unsigned char *Mass);
void InitOC4(void);
void InitOC1(void);
void InitOC2(void);
void InitOC3(void);

void AutoNastroyka_Func(void);


void TxRxSPI_ACC(unsigned int rxLen);
void InitAccSPI(void);
void WF_SpiAccDisableChipSelect(void);
void WF_SpiAccEnableChipSelect(void);
void StopCharging(void);

void TxRxSPI_GYRO(unsigned int rxLen);
void InitGyroSPI(void);
void WF_SpiGyroDisableChipSelect(void);
void WF_SpiGyroEnableChipSelect(void);
void HighSpeedQuantum(void);

//float RotX,RotY;
float AccXFlPrev, AccYFlPrev, AccZFlPrev;
float XNew, YNew, ZNew, YNewShow, KpDeadZone;
float AlfaXRes, AlfaYRes, AlfaZRes, AlfaXResPrev, AlfaYResPrev, AlfaZResPrev;

float AlfaXNoGyro, AlfaYNoGyro, AlfaYNoGyro3d, PWMAdd, AddX;
int TiltXThis, TiltYThis, TiltYThis3d, AlfaXResTmpAlm, AlfaYResTmpAlm, AlfaZResTmpAlm, AlfaXResAlmMem, AlfaYResAlmMem, AlfaZResAlmMem, PWMSignalTimer, PWMSignalCnt;
long CalibrX, CalibrY, CalibrZ, CalibrCnt, TiltYSumm, CntTiltYSumm;


int KRotMustBe, MaxSpeed, StartRotMustBe, StartRotNoMan, KRot, KRot1;
float StartRotHighSpeed, StartRot, StartRot1, ECurrChager, EpCurrChager, EiCurrChager;
unsigned char SpdKiMin, CntKdSwitch, CntKdSwitchCONST = 10, KdStateMachine;
float KiMin;


int CalibrationGyroX, CalibrationGyroY, CalibrationGyroZ;
int CalibrationAccX, CalibrationAccY, CalibrationAccZ;
unsigned int SlaveADCThrottle, SlaveADCThrottleBreak;

float TiltZad, TiltZadAdd, TiltZadTmp, TiltChng, TiltZadAddMustBe, TiltZadState5, TiltZadWheeling, SpdStartLevelFl;
unsigned int K_PWM_Nastr = 200, TMR8Temp, CntStopBalanceHumanSensor;
float StrongModeSpdFilterOff;
unsigned char StrongModeSpdFilterOffMem, MixedMode2StateMachine;
unsigned long int HC05_BUSYCnt = 0, HC05_TrmCnt = 0;

void SoundNoBMS(void);
void SensorlessManualStartInit(void);
void U4_9600_On(void);

void PI_Chager(void);
void PhaseToPC(void);
void InitFlash(void);
unsigned char TrmRecByteFLASH(unsigned char Bt);
unsigned char RecStatusFLASH(void);
unsigned char ReadFlash(unsigned long int Addr, unsigned int N, unsigned char * Mass);
void WriteOdometr(void);
void WREN_FLASH(void);
void WriteByte_FLASH(unsigned long int Addr, unsigned char Bt);
void WriteStat_FLASH(unsigned char St);
void EraseSector_FLASH(unsigned long int Addr);
void WriteOptions(void);
void DefaultOptions(void);
unsigned char ReadOptions(void);
unsigned char ReadOptions1(void);
void MassToOptions(void);
void MassToOptions2(void);
void OptionsToMass(void);
void OptionsToMass2(void);
unsigned char FlashMass[FLASHMASS_SIZE];
unsigned char FlashMass1[FLASHMASS_SIZE];
unsigned char FlashMass2[FLASHMASS_SIZE];
unsigned char AutoNastrConfirmWait(void);
unsigned char InvHalls(unsigned char Sensors);

unsigned char ProfileMass[PROFILEMASS_SIZE];
unsigned char ProfileMass1[PROFILEMASS_SIZE];
long int Curr1SinTSTSumm, Curr1SnTST, Curr1SnTST_0;
unsigned int Bt1DnCounter, Bt2DnCounter, Bt3DnCounter, Bt4DnCounter, Bt1UpCounter, Bt2UpCounter, Bt3UpCounter, Bt4UpCounter;
unsigned char Bt1NumPressedCnt, Bt2NumPressedCnt, Bt3NumPressedCnt, Bt4NumPressedCnt, PWM100StateMachineCnt;

unsigned char OnDelay, PWMkHzTmp;
int OnDelayConst, OnDelayCnt;
int Trapezium10kHzLo, Trapezium10kHzHi, Trapezium5kHzLo, Trapezium5kHzHi;


void BzFuncOn(void);
void ChangeCurr(void);

unsigned int AutoNastroyka_ConfirmDelayCnt, Hv2WDMasterCnt = 1;
unsigned char CntCriticalErrorLed, CriticalErrorLedStateMachine, KeyLightBrightness, StopIfPWM100Time;
unsigned int MODE_LED_Cnt, TimeHumanSensorOff, StopIfPWM100TimeCnt;



unsigned char StatusFlash, UBT_V, TemperatureTYPE_FETs, TstPhase;
float KGYRO, KACC;
float CmImp1_t, ImpToKmH1_t;

unsigned char PWMSignal;
unsigned long int UBat;
unsigned int UBT, UBTNoRegen, SensorlessCntAlign, SensorlessCntAlignConst, MustResetPINCnt, CntU3Off;

int SensorLessTimerConstMin, SpdKiLevel;
unsigned int _1sCnt1, _1sCntConst, SpdRstSpeedLim, CntZeroThroottle;
int Spd1Res, Spd1KpLevel = 1000, Spd1KdLevel = 1000, Spd1ResPrev, SpdPID, Spd1ResPlus, Spd1Cnt, SpdTmp, Spd1ResPlusTST = 7;
float Spd1UST, Spd1UST_Tmp, Spd1USTKMH, MixedModeSlowSpeedFl;

void ADC1Init(void);
void ADC2Init(void);
long int AccXFilter, AccYFilter, AccZFilter, KFilterPrev, KFilter;
long int GZFTempPrev;

void T5Init(void);
void T7Init(void);
void T9Init(void);
void Comparator3_Init(void);
void Comparator2_Init(void);
void ChangeCVR(void);


unsigned int BzOnCntSeriaConst, BzOnCntSeriaConstAlm, ResetPassWordCnt = 15000, ButtonBreakOnlyPWM;
unsigned int RegenOffMem, RegenOff;


unsigned char SpeedLimit2, SpeedLimit3, NumSpeedLimit, SpeedLimitSt4, SpeedLimitTmp, MPU6050Err;
unsigned int KpSPD, KdSPD, KiSPD, SpeedLimit1, KpSPDMove, KpSPDMustBe;
unsigned char MPU6050Addr, MPU6050Cnt, MPU6050CntMax, TestSIN_OkCnt, WheelingStateMachine;
float EUChager, EiUChager, EpPWMmax, EiPWMmax, EdPWMmax;



float CurrPerDigit = 1;




unsigned long int ESummSpd;
long int ESpdLim;
int AngleLimit, SpdLimImp, AngleLimitMustBe, AngleLimitMove, JoistickDeadZone, ThrottleLevelUpOff;
float Ki_PWM_Mode, Ki_PWM_ModeOff;
unsigned char ErrOptions, Spd0TimerStateMachineCnt;
unsigned char PWMkHz;
int Round(float Fl);

//int GyroXInd,GyroYInd,GyroZInd,AccXInd,AccYInd,AccZInd;


int XLimit, YLimit, GyroZFlTurn;
unsigned int UBatLow, UBtLim1, UBtLim2, UBatHiMem, UBatHi, LightSensor;
unsigned long int Odometr, PhasesCnt2;

unsigned char OdometrCnt, SensorBEMF;

unsigned int TemperatureCnt, StartingMoveCnt, Odometr10m, CntCanZeroCrossing, ButtonBreakOnlyTime;
char Temperature;
unsigned long int OdometrSectorNum, OdometrSectorNumConst;

void ReadOdometr(void);
void WriteOdometrNew(void);
void writeByteLSM6DS33(unsigned char ADDR, unsigned char Data);
void readBytesLSM6DS33(unsigned char ADDR, unsigned char N);
unsigned char readByteLSM6DS33(unsigned char ADDR);
void SndDebugArrays(void);



void WrOdmtr(void);

unsigned char LightMode, BuzzerOnEvent;
unsigned int LightSensorThresholdLo, LightSensorThresholdHi;

//float  PWMBackTilt;

unsigned char Bt1Cnt, Bt2Cnt, Bt3Cnt, Bt4Cnt, Bt1CntConst, Bt2CntConst, Bt3CntConst, Bt4CntConst;
unsigned int Bt1LongCnt, Bt2LongCnt, Bt3LongCnt, Bt4LongCnt, BtBLongCnt, BeepPause, TimerRegenOff;
void Buttons(void);
void ButtonsSlave(void);

unsigned char CntSingleBeepAlm, StringPINLenght, StringPINLenghtOptions, StringPINLenghtOptionsUnlock;
unsigned int BeepPauseConstAlm, PWMPrev;
int BreakMonocycleSpd, TimeDecreaseKi;


void OptionsToMassProfile(void);
void MassToOptionsProfile(void);

void Bt1Process(void);
void Bt2Process(void);
void Bt3Process(void);
void Bt4Process(void);

void writeFlash(void);
void SensorlessMotorStopStarting(void);


float AlfaXResErr, AlfaYResErr, SteerXErr, SteerYErr, CurrentMaxCurrentOnlyWork;

void WriteErrors(void);
void ReadErrors(void);

unsigned char CntNoBalance, MaxSpd, MaxSpdRevers, CurrSensor, OK_Cnt, _2WDMode;
float GZFTemp;


void InitPort_U4(void);
void UARTInit_U4(void);
void TrmHC05(unsigned char *Mass);
void TrmHC05_AT(char *Mass, int N);
void CloseU4(void);
unsigned char HC05TrmMass[FLASHMASS_SIZE + 10];


unsigned char StateSensorlessMotorStart;

char TrmMassHC05[100];
char RecMassHC05[100];
volatile unsigned int MyTimeOut;

char ThrottleTmpChngMem;

void TrmDataPacketHC05(void);
void TrmFlashMass(void);
void TrmFlashMass2(void);


long int AlfaYResPrevAv;
int AlfaYResPrevAvMass[256];
unsigned char CntTiltAv, CntDiffTiltLimit, CntCalibrateJOYSTICK;
int mt;

int DiffBetweenTilts, TiltSensorAdd, TiltDiff, CntAdd;
float AddTilt, AddTiltLimit, KpKpMustBe, KpKp2MustBe, KpKp, KpKp2, Kp_p, Kp2, KpK, KiK, Ki_p, Ki_pp, Ki_pPrev, Ki_ppDelta = 0.001;
void ClbrJOYSTICK(void);

int LastMainTiltAngleMnErr, LastSteerTiltAngleMnErr, TiltAngleAvMnErr;
int LastMainTiltAngleSteerErr, LastSteerTiltAngleSteerErr, TiltAngleAvSteerErr;
unsigned char MainTiltNumErr, SteerTiltNumErr;
void TrmErrorsHC05(void);
unsigned int TiltControlCnt = 2000;
unsigned int CntU4TimeOut = 100, HallErrCnt;




unsigned int Preas1DnCnt = 100, Preas1UpCnt = 200, PhasesPerRev1 = 100, Diametr1 = 200;
unsigned int Preas2DnCnt = 100, Preas2UpCnt = 200;
void SetTiltZadAdd_UP(void);
void SetKpMustBe_UP(void);
void SetStartRot_UP(void);
void StateMashine(void);

void SendStateOfSinTest(void);
void LighrSensorFunc(void);

void SetKi_UP(void);


float KpRotOneTwoLeg, KiRotOneTwoLeg;
int Curr1SinTST[256], Curr1SinTSTCnt, PhaseCurrShow;

unsigned char State = 1, MixedModeSlowSpeed;
float Kp_PWM_Mode;
int StartRotOneTwoLeg_1;

float KTemperatureSPDControl;
int CurrPhaseLimitSpd0, StartRotFreshmanL;
unsigned int TimeOutHC05 = 500, Spd0TimerConst = 250, Spd0Timer;
unsigned int CurrLimitSpd0;
void RecSlave2WDControls(void);
void LSM6DS33_Init(void);



void SetKpSPD_UP(void);
void SetAngleLimit_UP(void);

void AlmOn(void);
void AlmOff(void);
void Alm(void);

unsigned char DiffAlfaConstL, DiffAlfaConstH;
unsigned int CntHorningL;


void Rbw(void);
void SetPIN_HC05(void);
void GetRbw(void);

void CalibrateCurr(void);

unsigned long int CurrTuda1, CurrRegen1, CurrTuda2, CurrRegen2, Distance;

unsigned int CntCurr = 500;
unsigned int CntWriteCurr = 200;
unsigned int CNT_U, CNT_U_Bits;

void InitSensorsNear(void);

char NearSensors[8][4];
unsigned char CntHrnL, CntHrnLConst, UseTmr;
unsigned int Timer1Mem, Timer2Mem, Cnt30Sec, CntPause, CntUBTLow, CntUBtLim1;
unsigned long int TimerCnt;


unsigned long int TimerConst;
void SetTmrConst(void);
unsigned char BreakFunc(void);
unsigned int SerNumber;
char Str[22];

unsigned char BreakCntConst = 20;




unsigned long LongForTrmBMS;
unsigned char CntBMSBitTrm, BitRec, BMSRecMass[20], ByteRecBMS, BMSBytesCnt;
unsigned int BytesToRec;
#define BMSDelayCnt_CONST  5
unsigned char StartReceiveBMS, PacketBMS, ReceivingBMS, HvPacketBMS, BMSDelayCnt = 50, BMSAddrCnt = 0;

void GetBMS(void);

unsigned long int V1 = 3001, V2 = 3002, V3 = 3003, V4 = 3004, V5 = 3005, V6 = 3006, V7 = 3007, V8 = 3008, V9 = 3009, V10 = 3010, V11 = 3011, V12 = 3012, V13 = 3013, V14 = 3014, V15 = 3015, V16 = 3016, V17 = 3017, V18 = 3000, Vmin, VminTST = 3200;
unsigned long int BatteryKeys;
void DataFrmBMS(void);

unsigned char ChagerKeys;
unsigned long Cmd2BMS, Cmd3BMS, Cmd4BMS, Cmd5BMS;


unsigned int MAH, CntState5, TimerCntWhenLock;

unsigned char BatErr;
#define BMSMASSIZE  18
unsigned char MassToBMS[BMSMASSIZE];
unsigned char CntBytesStorage, CntBitsStrg;


#define CNTSTOR_CONST  1000

unsigned int CntMustStorageData = CNTSTOR_CONST;
int HighSpeedImp, GoalSpeedImp;


float HallDelayMaxSPDNoKMH;


void SensorlessMotorStart(void);
void SensorlessMotorStartInit(void);




void ResetSpdLimSt4(void);

unsigned char BMS1Err, BMS2Err, BMS3Err, BMS4Err, BMS5Err;

void ErrorSound(void);
unsigned int CntOnDelay = 0, CntTicks;

unsigned char StateInd, IndCnt;

unsigned int CntAfterActivate;
void Dbg(void);
unsigned char CntTrmSteer_N, CntTrmSteer, KAccGyroSteer;

unsigned int AutoNastroykaState, AutoNastroykaStateFn;

void TrmSteer(void);
void RdSensors(void);

int MAX_AVARAGE = 128;
unsigned char MAX_AVARAGE_SHIFT = 7, Profile;



char HallDelay1MaxSPD_F, HallDelay1MaxSPD_B;
unsigned char HallDelayMaxSPD;
unsigned char ChangeSensorOrder(unsigned char Sns, unsigned char SendOrder);
unsigned int TS = 0, TS0 = 0, TS1 = 0, TS2 = 0, TS3 = 0, TS4 = 0;

unsigned int Curr1Mass[CURRMASS_SIZE];

unsigned int l;
unsigned long int CrSumm = 0;
long int CurrentControlCurr = 0, CurrentControlCurrUst;


float Spd1Fl, Spd1FlPlus;

void CountSpd(void);


unsigned int FLTSTATCnt, FLTSTATCntConst = 10;
unsigned char Halls;


unsigned char BreakCntOn = 10, BreakCntOff = 10, HvBreakCntOff = 10, HvBreakCntOn = 10;
void TestBreak(void);

unsigned int V_MIN_OFF, V_MIN_Pre_OFF, V_MIN_Sound, V_min_OverV;
unsigned char CntSegMain = 2;

void AccToMemALM(void);

int AccXAv[ACC_AV_TTL], AccYAv[ACC_AV_TTL], AccZAv[ACC_AV_TTL];



long int PI_Curr1Res, PI_Curr1ResPID, CurrControlPIRes;
float KiCurr, KpCurr;
int ECurr1, ECurr1PID, CurrUst, CurrUstSpd0, CurrUstTmp, CurrUstTmpPID, CurrPhaseLimit, CurrPhaseLimitWork, CurrUstWork, SensorlessCurrUst;

unsigned long int Amplitude1Tmp, PhasePWM, Amplitude2Tmp;
float ECurr1Summ, ECurr1SummPID, EpCurr1, EpCurr1PID, CurrUstChager;
unsigned int DIRPWM1;
int PWM_Chager;
unsigned long int CalibrHallsMass[CntCalibrHallsMAX];
long int Hall1ClrbRes, Hall2ClrbRes, Hall3ClrbRes, Hall4ClrbRes, Hall5ClrbRes, Hall6ClrbRes;
void CalculateCalibrationHalls(void);

long int PWM1Temp = 0, PWMTempPID, PWM1TempPreWheeling = 0, PWM1TempPrev;


int Throttle2Tmp, ThrottleTmp, ThrottleTmpMixed, ThrottleTmpChng, ThrottleTmpMustBe, BreakTMP, CntNoSecret, ThrottleTmpPrev, DiffMixed, CntMixedMode;
int MixedModeLevelOn, MixedModeLevelOff, CntMixedModeMax, CurrMixed, iMin, ThrottleTmpAdd;

long int KThreshold, KThresholdBreak;

unsigned char RecStatusFLASH_TST(void);
float UBtFl;

unsigned int MotorPhaseA, MotorPhaseB, MotorPhaseC, MotorNeutralVoltage, ADCCommState, ComparatorOutputs;

unsigned char But1Func, But2Func, But3Func, But4Func, But5Func;
unsigned char SensorLessStartStage, SensorTST = 6, SensorTSTKeys;
unsigned int SensorLessTimer, SensorLessTimerConst = 0, SensorLessTimerConstConst, SensorLessTimerConst2, AutoPID_On_CntConst = 1250;

void AutoPIDStateMachine(void);
void Sound(void);
unsigned long int LockTMR;
unsigned long int ReadProgramMemory(unsigned long int address);






float GetTemperaturePTC_KTY81_210(unsigned int ResTemp);
float GetTemperaturePTC_KTY83_110(unsigned int ResTemp);
float GetTemperaturePTC_KTY83_122(unsigned int ResTemp);
float GetTemperature_NTCALUG03A103H(unsigned int ResTemp);
float GetTemperature_MF58_B_5K(unsigned int ResTemp);
float GetTemperature_MF58_G_10K(unsigned int ResTemp);
float GetTemperature_NCP18XH103F03RB(unsigned int ResTemp);
float GetTemperaturePTC_KTY84_130(unsigned int ResTemp);
float Temperature1, Temperature2, Temperature3, Temperature4, Temperature5, Temperature6, TemperatureMaxOUT, TemperatureMaxOUT_H, TemperatureMaxIN, TemperatureMaxIN_H;
float ETemperIN, EpTemperIN, TemperatureFETs, KiTemperIN, KpTemperIN, ETemperINSumm, PI_Temperature, PITemperIN;
float KiTemperOUT, KpTemperOUT;

unsigned long int T1_ADC, T2_ADC, T3_ADC, T4_ADC, T5_ADC, T6_ADC;
unsigned int CntT_ADC, T1, T2, T3, T4, T5, T6, CntMustBe;
float ETemperOUT, ETemperOUTSumm, PITemperOUT, EpTemperOUT;
unsigned long int PI_TemperatureOUT;

unsigned char AutoPID_On_PWM, AutoPID_On_Speed;

unsigned char AutoPIDState;
long int PWM1TempSumm;
float PWM1TempSummfl = 0;
unsigned int AutoPID_On_Cnt, PWM1TempSummCnt;
void CopyProfiles(void);

void SendProfileMassToPC(void);
void SendFlashMassToPC(void);
void SendFlashMass2ToPC(void);
void CmdOK(void);
void CmdOK2(void);
void CmdOK3(void);
void Lights(void);
unsigned int ProtectValue, CntTurn, RCON_Mem, CntTurnOnConst, CntTurnOffConst;
unsigned char SlowStrtSpd, AntiPolicePower;


//unsigned char __attribute__((address(0x9002))) abcde[20000];
//unsigned char TSTMass[17000];
//__eds__ unsigned char TSTMass1[17000]; __attribute__ ((eds));

int main(void) {
        
#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 0;
#else
    KEY_BT = 1;
#endif
#else
    KEY_BT = 0;
#endif
    TRIS_KEY_BT = 0;






    RCON_Mem = RCON;
    Nop();
    Nop();
    Nop();
    RCON = 0;


    InitSegAll();
   

    MyTimeOut = 500;
    while (MyTimeOut);


#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 1;
#else
    KEY_BT = 0;
#endif
#else
    KEY_BT = 1;
#endif
    Nop();
    Nop();
    Nop();
    HvReplyHC05 = 0;
    MyTimeOut = 550;
    AT_Rec = 1;
    TrmHC05_AT("AT+UART?", sizeof ("AT+UART?")); //AT+NAME=RoboWell
 //   TrmHC05_AT("AT+BAUD38400", sizeof ("AT+BAUD38400")); //AT+NAME=RoboWell
    while ((!HvReplyHC05)&&(MyTimeOut));
    AT_Rec = 0;

#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 0;
#else
    KEY_BT = 1;
#endif
#else
    KEY_BT = 0;
#endif

    Hv_HC05 = 0;


    if (StringPINLenghtOptions == 0xff)
        StringPINLenghtOptions = 0x00;




        Hv_HC05 = 1;



        while (1) {
            Nop();

            LighrSensorFunc();
            ClbrJOYSTICK();

            //TrmControls_U3();
            CalculateCalibrationHalls();
            WrOdmtr();
            writeFlash();
            WriteErrors();
            ReceiveUDP();
            //TrmErrorsHC05();
            Rbw();
            SetPIN_HC05();
            //ResetPIN_HC05();
            GetRbw();
            DataFrmBMS();
            ErrorSound();
            CountSpd();
            UBT_To_V();
            CriticalErrorLed();

            if (MustTrmHC05) {
                MustTrmHC05 = 0;
                TrmHC05(HC05TrmMass);
            }
            FindGyroVerticalFunc();
            Dbg();
            TrmSteer();

        }
    


}

void SegMain(void) {
#if defined MPU6050
    if (I2C1STATbits.BCL) {
        Nop();
        Nop();
        Nop();
        CloseI2C1(); //Disable I2C
        IEC1bits.MI2C1IE = 0;
        HvMPU6050 = 1;
        MPU6050Err = 9;
        SoundNum = 10;
    }
#endif


#if !defined VECTORS
    if (Left)
        LeftPort = 1;
    else
        LeftPort = 0;

    if (Right)
        RightPort = 1;
    else
        RightPort = 0;
#else
    if (Left)
        LeftPort = 0;
    else
        LeftPort = 1;

    if (Right)
        RightPort = 0;
    else
        RightPort = 1;
#endif

    if ((!HvGyroData) || (!HvAccData))
        return;

    ButtonBreakOnly = 0;

    
    
#if !defined SENSORLESS_TEST
        Sensorless2=0;
#endif

    

    if (ErrorCode != CriticalError) {
        if (CriticalError) {
            ErrorCode = CriticalError;
            WriteErr_Fl = 1;
        }
    }


    HvGyroData = 0;
    HvAccData = 0;

    if (GyroAccSameOff) {
        if (CntGyroAccSameOff < 20) {
            if ((AccX == AccXPrev)&&(AccY == AccYPrev)&&(AccZ == AccZPrev)&&
                    (GyroX == GyroXPrev)&&(GyroY == GyroYPrev)&&(GyroZ == GyroZPrev))
                CntGyroAccSameOff++;
            else
                CntGyroAccSameOff = 0;

            AccXPrev = AccX;
            AccYPrev = AccY;
            AccZPrev = AccZ;
            GyroXPrev = GyroX;
            GyroYPrev = GyroY;
            GyroZPrev = GyroZ;
        } else {
            /*          CriticalError=CRERR_GYROACC_DISCONNECTED;
                      NoBalance=1;
                      NoBalanceCode=5;
                      StrongMode=0;
                      DS=1;
             */        }
    }




    if (CntMigStop)
        CntMigStop--;
    if (CntMigStop > CntMigStopConst)
        CntMigStop = CntMigStopConst;



    
    

    if (MODE_LED_Cnt)
        MODE_LED_Cnt--;

    if (ResetPassWordCnt)
        ResetPassWordCnt--;
    else
        Nop();


    /*
        if (UBtFl>99)
            CriticalError=CRERR_UBAT_HI;
        else
        {
            if (CriticalError==CRERR_UBAT_HI)
            {
                CriticalError=0;
                    BuzzerMacroOff
            }
        }
    
     */




    if (_2WDMode == 2) {
        if (HvButtonsFromMaster) {
            HvButtonsFromMaster = 0;
            ButtonsSlave();
        }
    } else
        Buttons();
    Bt1Process();
    Bt2Process();



    if (SIN_MIDDLE)
        StrongMode = 1;



    SetStartingProfile3PsnBtn();

    if (ThreePositionSwitch)
        ChangeProfile();
    else {
        if (!TurnSignal) {
            Bt3Process();
            Bt4Process();
        } else {
            if (But3Pressed)
                LeftTurn = 1;
            else
                LeftTurn = 0;

            if (But4Pressed)
                RightTurn = 1;
            else
                RightTurn = 0;

        }
    }
    StartingBTN = 0;




#ifdef PROTECT
    if (((unsigned int) (ReadProgramMemory(0xf04))) != 0x8287)
        CriticalError = CRERR_SEC_ERROR_1;
#endif









    Sound();
    StateMachinePID();
    if (SoundTmr)
        if (!Sounds)
            SoundNum = 6;

    CntMustBe++;
    if (CntMustBe > 5) {
        CntMustBe = 0;

        if (MAX_PWM_MEM_WORK > MAX_PWM_MustBe) {
            MAX_PWM_MEM_WORK--;
        }

        if (MAX_PWM_MEM_WORK < MAX_PWM_MustBe) {
            MAX_PWM_MEM_WORK++;
        }


    }


    if (ClearCurrentAH) {
        ClearCurrentAH = 0;
        CurrTuda1 = CurrRegen1 = CurrTuda2 = CurrRegen2 = 0;
        RecOdometrFl = 1;
    }
    if (CalibrateGyro) {
        CalibrX = 0;
        CalibrY = 0;
        CalibrZ = 0;

        for (CalibrCnt = 0; CalibrCnt < 256; CalibrCnt++) {
            while (!HvGyroData);
            HvGyroData = 0;
            CalibrX = CalibrX + GyroX;
            CalibrY = CalibrY + GyroY;
            CalibrZ = CalibrZ + GyroZ;
            ClrWdt();
        }
        CalibrateGyro = 0;
        CalibrationGyroX = CalibrX >> 8;
        CalibrationGyroY = CalibrY >> 8;
        CalibrationGyroZ = CalibrZ >> 8;

        OptionsToMass();
        MustTrmFlashMass = 1;

        Nop();
        Nop();
        Nop();
    }

    if (CalibrateAcc) {
        CalibrX = 0;
        CalibrY = 0;
        CalibrZ = 0;

        for (CalibrCnt = 0; CalibrCnt < 256; CalibrCnt++) {
            while (!HvAccData);
            HvAccData = 0;
            CalibrX = CalibrX + AccX;
            CalibrY = CalibrY + AccY;
            CalibrZ = CalibrZ + AccZ;
            ClrWdt();
        }
        CalibrateAcc = 0;
#if defined MPU6500
        CalibrationAccX = 16384 + (CalibrX >> 8);
        CalibrationAccY = CalibrY >> 8;
        CalibrationAccZ = CalibrZ >> 8;
#else
        CalibrationAccX = CalibrX >> 8;
        CalibrationAccY = CalibrY >> 8;
        CalibrationAccZ = 16384 + (CalibrZ >> 8);
#endif
        OptionsToMass();
        MustTrmFlashMass = 1;


        Nop();
        Nop();
        Nop();
    }


    //StateMashine();






    CalibrateCurr();



    if (CntT_ADC >= 64) {
        T1 = T1_ADC >> 6;
        T2 = T2_ADC >> 6;
        T3 = T3_ADC >> 6;
        T4 = T4_ADC >> 6;
#if !defined REV2
        T5 = T5_ADC >> 6;
        T6 = T6_ADC >> 6;
#endif
        T1_ADC = 0;
        T2_ADC = 0;
        T3_ADC = 0;
        T4_ADC = 0;
        T5_ADC = 0;
        T6_ADC = 0;



        CurrA_P_Av = CurrA_P_Summ >> 6;
        CurrA_N_Av = CurrA_N_Summ >> 6;
        CurrC_P_Av = CurrC_P_Summ >> 6;
        CurrC_N_Av = CurrC_N_Summ >> 6;

        // I=(ADC*3.3)/(32768*R)  R=0.0005

        CurrA = ((float) (CurrA_P_Av - CurrA_N_Av))*(float) 0.20141602;
        CurrC = ((float) (CurrC_P_Av - CurrC_N_Av))*(float) 0.20141602;


        CurrA_P_Summ = 0;
        CurrA_N_Summ = 0;
        CurrC_P_Summ = 0;
        CurrC_N_Summ = 0;




        CntT_ADC = 0;
#if defined REV2_NO
        Temperature1 = GetTemperaturePTC_KTY81_210(T1);
        Temperature2 = GetTemperaturePTC_KTY81_210(T2);
        //    Temperature3=GetTemperaturePTC_KTY81_210(T3);

        switch (TemperatureTYPE) {
            case 0:
                Temperature3 = GetTemperaturePTC_KTY81_210(T3);
                break;
            case 1:
                Temperature3 = GetTemperaturePTC_KTY83_110(T3);
                break;
        }

        Temperature4 = GetTemperature_NTCALUG03A103H(T4);
        Temperature5 = GetTemperature_NTCALUG03A103H(T5);
        Temperature6 = GetTemperaturePTC_KTY81_210(T6);
        TemperatureFETs = -100;
        Temperature2 = Temperature4 = Temperature5;
        if (Tmprt2)
            TemperatureFETs = Temperature4;

        if (Tmprt3) {
            if (TemperatureFETs < Temperature5)
                TemperatureFETs = Temperature5;
        }


        if (Tmprt4) {
            if (TemperatureFETs < Temperature6)
                TemperatureFETs = Temperature6;
        }

        if (Tmprt2 || Tmprt3 || Tmprt4) {
            if (TemperatureFETs > TemperatureMaxIN) {
                if (!Sounds) {
                    SoundNum = 13;
                    SoundIN = 1;
                }
                PID_On = 0;

                ETemperIN = TemperatureFETs - TemperatureMaxIN;

                EpTemperIN = ETemperIN*KpTemperIN;

                ETemperINSumm = ETemperINSumm + ETemperIN*KiTemperIN;

                if (ETemperINSumm > MAX_PWM)
                    ETemperINSumm = MAX_PWM;


                PITemperIN = EpTemperIN + ETemperINSumm;

                if (PITemperIN > MAX_PWM)
                    PITemperIN = MAX_PWM;
                PI_Temperature = (unsigned long int) PITemperIN;
            } else {

                if (TemperatureFETs > (TemperatureMaxIN - 5)) {
                    if (!Sounds) {
                        SoundNum = 13;
                        SoundIN = 1;
                    }
                }


                if (SoundIN) {
                    SoundIN = 0;
                    Sounds = 1;
                }

                if (ETemperINSumm > 0) {
                    ETemperIN = TemperatureMaxIN - TemperatureFETs;
                    if (KiTemperIN != 0)
                        ETemperINSumm = ETemperINSumm - ETemperIN * KiTemperIN;
                    else
                        ETemperINSumm = 0;
                    if (ETemperINSumm < 0)
                        ETemperINSumm = 0;
                } else
                    ETemperINSumm = 0;
                PI_Temperature = (unsigned long int) ETemperINSumm;
            }
        } else
            PI_Temperature = 0;



        if (Tmprt1) {
            if (Temperature3 > TemperatureMaxOUT) {
                if (!Sounds) {
                    SoundNum = 8;
                    SoundOUT = 1;
                }
                PID_On = 0;

                ETemperOUT = Temperature3 - TemperatureMaxOUT;

                EpTemperOUT = ETemperOUT*KpTemperOUT;

                ETemperOUTSumm = ETemperOUTSumm + ETemperOUT*KiTemperOUT;

                if (ETemperOUTSumm > MAX_PWM)
                    ETemperOUTSumm = MAX_PWM;

                PITemperOUT = EpTemperOUT + ETemperOUTSumm;

                if (PITemperOUT > MAX_PWM)
                    PITemperOUT = MAX_PWM;
                PI_TemperatureOUT = (unsigned long int) PITemperOUT;
            } else {
                if (SoundOUT) {
                    SoundOUT = 0;
                    Sounds = 1;
                }
                if (ETemperOUTSumm > 0) {
                    ETemperOUT = TemperatureMaxOUT - Temperature3;
                    if (KiTemperOUT != 0)
                        ETemperOUTSumm = ETemperOUTSumm - ETemperOUT * KiTemperOUT;
                    else
                        ETemperOUTSumm = 0;
                    if (ETemperOUTSumm < 0)
                        ETemperOUTSumm = 0;
                } else
                    ETemperOUTSumm = 0;
                PI_TemperatureOUT = (unsigned long int) ETemperOUTSumm;
            }
        } else
            PI_TemperatureOUT = 0;

        if (PI_TemperatureOUT > PI_Temperature)
            PI_Temperature = PI_TemperatureOUT;



#else

#if defined REV2
        switch (TemperatureTYPE) {
            case 0:
                Temperature1 = GetTemperaturePTC_KTY81_210(T1);
                break;
            case 1:
                Temperature1 = GetTemperaturePTC_KTY83_110(T1);
                break;
            case 2:
                Temperature1 = GetTemperaturePTC_KTY83_122(T1);
                break;
            case 3:
                Temperature1 = GetTemperaturePTC_KTY84_130(T1);
                break;
            case 4:
                Temperature1 = GetTemperature_MF58_B_5K(T1);
                break;
            case 5:
                Temperature1 = GetTemperature_MF58_G_10K(T1);
                break;
            case 6:
                Temperature1 = GetTemperature_NCP18XH103F03RB(T1);
                break;
            case 7:
                Temperature1 = GetTemperature_NTCALUG03A103H(T1);
                break;


        }

        switch (TemperatureTYPE_FETs) {
            case 0:
                Temperature2 = GetTemperature_NTCALUG03A103H(T2);
                //Temperature3=GetTemperature_NTCALUG03A103H(T3);
                //Temperature4=GetTemperature_NTCALUG03A103H(T4);
                break;
            case 1:
                Temperature2 = GetTemperaturePTC_KTY81_210_FETs(T2);
                break;
        }



#else
        switch (TemperatureTYPE) {
            case 0:
                Temperature1 = GetTemperaturePTC_KTY81_210(T2);
                break;
            case 1:
                Temperature1 = GetTemperaturePTC_KTY83_110(T2);
                break;
        }

        Temperature2 = GetTemperature_NTCALUG03A103H(T2);
        Temperature3 = GetTemperature_NTCALUG03A103H(T3);
        Temperature4 = GetTemperature_NTCALUG03A103H(T4);
#endif



        TemperatureFETs = -100;

        if (Tmprt2)
            TemperatureFETs = Temperature2;

        if (Tmprt3) {
            if (TemperatureFETs < Temperature3)
                TemperatureFETs = Temperature3;
        }


        if (Tmprt4) {
            if (TemperatureFETs < Temperature4)
                TemperatureFETs = Temperature4;
        }

        if (Tmprt2 || Tmprt3 || Tmprt4) {

            if (TemperatureFETs > TemperatureMaxIN_H)
                CriticalError = CRERR_OVERHEATED_IN;

            if (CriticalError == CRERR_OVERHEATED_IN) {
                if (TemperatureFETs < TemperatureMaxIN_H)
                    CriticalError = 0;
            }


            if (TemperatureFETs > TemperatureMaxIN) {
                if (!Sounds) {
                    SoundNum = 13;
                    SoundIN = 1;
                }
                if (!SpeedControl)
                    PID_On = 0;

                ETemperIN = TemperatureFETs - TemperatureMaxIN;

                EpTemperIN = ETemperIN*KpTemperIN;

                ETemperINSumm = ETemperINSumm + ETemperIN*KiTemperIN;

                if (ETemperINSumm > MAX_PWM)
                    ETemperINSumm = MAX_PWM;


                PITemperIN = EpTemperIN + ETemperINSumm;

                if (PITemperIN > MAX_PWM)
                    PITemperIN = MAX_PWM;
                PI_Temperature = (unsigned long int) PITemperIN;
            } else {
                EpTemperIN = 0;
                if (Monocycle) {
                    if (TemperatureFETs > (TemperatureMaxIN - 5)) {
                        if (!Sounds) {
                            SoundNum = 13;
                            SoundIN = 1;
                        }
                    } else {
                        if (SoundIN) {
                            SoundIN = 0;
                            Sounds = 1;
                        }
                    }
                } else {
                    if (SoundIN) {
                        SoundIN = 0;
                        Sounds = 1;
                    }
                }

                if (ETemperINSumm > 0) {
                    ETemperIN = TemperatureMaxIN - TemperatureFETs;
                    if (KiTemperIN != 0)
                        ETemperINSumm = ETemperINSumm - ETemperIN * KiTemperIN;
                    else
                        ETemperINSumm = 0;
                    if (ETemperINSumm < 0)
                        ETemperINSumm = 0;
                } else
                    ETemperINSumm = 0;
                PI_Temperature = (unsigned long int) ETemperINSumm;
            }
        } else
            PI_Temperature = 0;



        if (Tmprt1) {
            if (Temperature1 > TemperatureMaxOUT_H)
                CriticalError = CRERR_OVERHEATED_OUT;
            else {
                if (CriticalError == CRERR_OVERHEATED_OUT)
                    CriticalError = 0;
            }



            if (Temperature1 > TemperatureMaxOUT) {
                if (!Sounds) {
                    SoundNum = 8;
                    SoundOUT = 1;
                }
                if (!SpeedControl)
                    PID_On = 0;

                ETemperOUT = Temperature1 - TemperatureMaxOUT;

                EpTemperOUT = ETemperOUT*KpTemperOUT;

                ETemperOUTSumm = ETemperOUTSumm + ETemperOUT*KiTemperOUT;

                if (ETemperOUTSumm > MAX_PWM)
                    ETemperOUTSumm = MAX_PWM;

                PITemperOUT = EpTemperOUT + ETemperOUTSumm;

                if (PITemperOUT > MAX_PWM)
                    PITemperOUT = MAX_PWM;
                PI_TemperatureOUT = (unsigned long int) PITemperOUT;
            } else {
                if (Monocycle) {
                    if (Temperature1 > (TemperatureMaxOUT - 5)) {
                        if (!Sounds) {
                            SoundNum = 8;
                            SoundOUT = 1;
                        }
                    } else {
                        if (SoundOUT) {
                            SoundOUT = 0;
                            Sounds = 1;
                        }
                    }
                } else {
                    if (SoundOUT) {
                        SoundOUT = 0;
                        Sounds = 1;
                    }
                }
                if (ETemperOUTSumm > 0) {
                    ETemperOUT = TemperatureMaxOUT - Temperature1;
                    if (KiTemperOUT != 0)
                        ETemperOUTSumm = ETemperOUTSumm - ETemperOUT * KiTemperOUT;
                    else
                        ETemperOUTSumm = 0;
                    if (ETemperOUTSumm < 0)
                        ETemperOUTSumm = 0;
                } else
                    ETemperOUTSumm = 0;
                PI_TemperatureOUT = (unsigned long int) ETemperOUTSumm;
            }
        } else {
            PI_TemperatureOUT = 0;
            if (CriticalError == CRERR_OVERHEATED_OUT) {
                CriticalError = 0;
                Sounds = 1;
            }

        }

        if (PI_TemperatureOUT > PI_Temperature)
            PI_Temperature = PI_TemperatureOUT;



#endif


    }



    //    if (!((HvGyroData)&&(HvAccData)))
    //      return;



    Curr1Mass[CURRMASS_SIZE - 1] = Crr1;

    CrSumm = 0;
    for (l = 0; l < CURRMASS_SIZE; l++)
        CrSumm = CrSumm + Curr1Mass[l];

    for (l = 0; l < (CURRMASS_SIZE - 1); l++)
        Curr1Mass[l] = Curr1Mass[l + 1];

    Curr1Show = CrSumm>>CURRMASS_SHIFT;
    Curr1 = Crr1;

    if (!Calibrating) {
        //  CurrentControlCurr=CrSumm;
#if defined REV2
#if !defined VECTOR
        Curr1 = ZeroCurr1 + 1 - Curr1;
        Curr1Show = ZeroCurr1 + 1 - Curr1Show;
#else
        Curr1 = Curr1 - ZeroCurr1 + 2;
        Curr1Show = Curr1Show - ZeroCurr1 + 2;
#endif
        if (Curr1Show < 0)
            Curr1Show = Curr1Show * 1.25;


        Curr1 = (int) ((float) Curr1 * Crr1Corr);
        Curr1Show = Curr1Show*Crr1Corr;

        //Curr1Show=-2790;


        /*  
              if (CntPhase<MassTMPSIZE)
              {
      MassTMPPhase[CntPhase]=Curr1/10;
      MassTMPNeutral[CntPhase]=0;//PDC1/6;
      CntPhase++;
              }    
    
    
         */

        ChangeCurr();
#if !defined VECTORMS
        CurrentControlCurr = (((long int) ZeroCurr1) << CURRMASS_SHIFT) + CURRMASS_SIZE - CurrentControlCurr;
#else
        //CurrentControlCurr=CurrentControlCurr-((((long int)ZeroCurr1)<<CURRMASS_SHIFT)+CURRMASS_SIZE);
        CurrentControlCurr = Curr1;
#endif

        if (PhasePWM != 0)//&&(Curr1>=CurrMixed))
            PhaseCurr = (int) (((long int) Curr1 * (long int) MAX_PWM_CONST) / (long int) PhasePWM);
        else
            PhaseCurr = 0;

        PhaseCurrShow = (int) (((long int) Curr1Show * (long int) MAX_PWM_CONST) / (long int) PhasePWM);

        // CurrentControlCurr=PhaseCurr;
        // else
        //   PhaseCurr=0;
#else
        Curr1 = Curr1 - ZeroCurr1 + 1;
#endif

        if (SpeedControl || PID_On)
            CURRENT_PROTECTION = 0;
        else
            CURRENT_PROTECTION = 1;

        if (Monocycle)
            CURRENT_PROTECTION = 1;



        if (!StartCnt) {
            if (((Sensor1_Prev == 0) || (Sensor1_Prev == 7)) && But1Pressed && But2Pressed&&!But3Pressed && But4Pressed) {
                if (!ResetedPIN) {
                    MustResetPINCnt++;
                    if (MustResetPINCnt > 1000) {
                        /*PinCodeMass[8]='1';
                        PinCodeMass[9]='2';
                        PinCodeMass[10]='3';
                        PinCodeMass[11]='4';
 
                        StringPINLenght=13;

                        PIN_CODE_HC05=1;
                        MustResetPIN=1;*/

                        SoundNum = 10;
                        ResetedPIN1 = 1;
                        FillPINResetMass();

                    }

                }
            }
        }




        if (CURRENT_PROTECTION) {

            CurrUstTmp = ((long int) CurrPhaseLimit * (long int) PhasePWM) / ((long int) MAX_PWM_CONST);

            if ((CurrUstTmp > CurrUst) || (CurrUstTmp <= 200))
                CurrUstTmp = CurrUst;
            else
                Nop();

            CurrUstTmpPID = CurrUstTmp;


            if (Curr1 > CurrUstTmp) {
                if (!SensorlessNotBEMF)
                    if (!StartCnt) {
                        CurrProtectSoundCnt++;
                        if (CurrProtectSoundCnt > 10) {
                            CurrProtectSoundCnt = 0;
                            if ((Spd1ResPlus <= 5)&&(!Monocycle)) {
                                if ((Spd0TimerStateMachineCnt == 0)&&(Curr1Show > CurrUstTmp)) {
                                    Spd0TimerStateMachineCnt = 1;
                                    if (!AutoNastroykaState)
                                        Spd0Timer = Spd0TimerConst;
                                    else
                                        Spd0Timer = 10000;
                                }
                            }
                            if (CurrLimitSound)
                                SoundNum = 1;
                        }
                    }
                PID_On = 0;
                ECurr1 = Curr1 - CurrUstTmp;
                EpCurr1 = ECurr1*KpCurr;
                ECurr1Summ = ECurr1Summ + (float) ECurr1*KiCurr;
                if (ECurr1Summ > MAX_PWM)
                    ECurr1Summ = MAX_PWM;
            } else {
                EpCurr1 = 0;
                if (ECurr1Summ > 0) {
                    ECurr1 = CurrUstTmp - Curr1;
                    ECurr1Summ = ECurr1Summ - ((float) ECurr1 * KiCurr);
                    if (ECurr1Summ < 0)
                        ECurr1Summ = 0;
                } else {
                    ECurr1Summ = 0;
                }
            }
            PI_Curr1Res = (unsigned long int) ECurr1Summ + (unsigned long int) EpCurr1 + PI_Temperature;
            if (PI_Curr1Res > MAX_PWM)
                PI_Curr1Res = MAX_PWM;
        } else {
            PI_Curr1Res = PI_Temperature;
            if (PI_Curr1Res > MAX_PWM)
                PI_Curr1Res = MAX_PWM;
        }





    }
    //CurrRegen1=2600000;
    if (CntCurr) {
        CntCurr--;
        if (!CntCurr) {
            CntCurr = 27; //25;

            //if ((Curr1<=5)&&(Curr1>=-5))
            //  Curr1=0;
            if (Curr1 > 0)
                CurrTuda1 = CurrTuda1 + Curr1;
            else
                CurrRegen1 = CurrRegen1 - Curr1;
            //            if ((Curr2<=5)&&(Curr2>=-5))
            //              Curr2=0;

            if (CntWriteCurr) {
                CntWriteCurr--;
                if (!CntWriteCurr) {
                    CntWriteCurr = 100;
                    Odometr10m = 0;
                    //             RecOdometrFl=1;
                }
            }


        }
    }









    if (ReversON) {
        if (!Sounds)
            SoundNum = 3;
        if (!ReversChanged) {
            if (Spd1ResPlus <= 1) {

                SpeedControlMem = SpeedControl;
                SpeedControl = 0;
                MAX_PWM_MustBe = MAX_PWM_Revers;

                DirPWM1 = !DirPWM1;
                ReversChanged = 1;
                RdSensors();
            }
        }
    }
    if (ReversChanged) {
        if (!ReversON) {
            if (Spd1ResPlus <= 1) {
                DirPWM1 = !DirPWM1;
                ReversChanged = 0;
                RdSensors();
                Sounds = 1;
                SpeedControl = SpeedControlMem;
                MAX_PWM_MustBe = MAX_PWM_MEM;
            }
        }
    }


    /*
    if ((ReversChanged)&&(Sounds==0))
    {
                SoundNum=3;
    }
     */


    if (Kp < KpMustBe)
        Kp = Kp + 1;
    if (Kp > KpMustBe)
        Kp = Kp - 1;


    if (KpKp2 < KpKp2MustBe) {
        KpKp2 = KpKp2 + 0.001;
    }
    if (KpKp2 > KpKp2MustBe) {
        KpKp2 = KpKp2 - 0.001;
    }
    if (KpKp2MustBe == 0)
        KpKp2 = 0;


    if (KpKp < KpKpMustBe) {
        KpKp = KpKp + 0.001;
    }
    if (KpKp > KpKpMustBe) {
        KpKp = KpKp - 0.001;
    }
    if (KpKpMustBe == 0)
        KpKp = 0;

    if (KiKp < KiKpMustBe) {
        KiKp = KiKp + 0.01;
    }
    if (KiKp > KiKpMustBe) {
        KiKp = KiKp - 0.01;
    }
    if (KiKpMustBe == 0)
        KiKp = 0;


    /*

                        if (KpMustBe_UP)
                        {
                if (Kp<KpMustBe)
                    Kp=Kp+1;
                else
                    Kp=KpMustBe;
                        }
                        else
                        {
                if (Kp>KpMustBe)
                    Kp=Kp-1;
                else
                    Kp=KpMustBe;
                        }
     */
    /*
        if (KdMustBe != (KdNoMan + KdAddSpd)) {
            KdMustBe = (KdNoMan + KdAddSpd);
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

     */


    float DiffUBT;



    if ((UBtFl > UBatLow)&&(UBtFl < UBatHiMem))
        DiffUBT = ((float) UBatHiMem) - UBtFl;
    else
        if (UBtFl < UBatHiMem)
        DiffUBT = UBatHiMem - UBatLow;
    else
        DiffUBT = 0;

    float Ki100;

    if (Spd1ResPlus < SpdKiLevel) {
        if (KiMin < KiMustBe)
            Ki100 = KiMustBe - KiMin;
        else
            Ki100 = 0;

        KiAdd = 1 - (((float) Spd1ResPlus) / ((float) SpdKiLevel));
        KiAdd = KiAdd*Ki100;

    } else
        KiAdd = 0;





    KiMustBe1 = (KiMustBe - KiAdd)*(1 + DiffUBT * KiUBTCoeff);



    if (Ki < KiMustBe1) {
        Ki = Ki + 0.05;
        if (Ki > KiMustBe1)
            Ki = KiMustBe1;
    }

    if (Ki > KiMustBe1) {
        Ki = Ki - 0.05;
        if (Ki < KiMustBe1)
            Ki = KiMustBe1;
    }





    /*          if (Ki_UP)
              {
              if (Ki<KiMustBe)
                  Ki=Ki+0.05;
                  else
                  Ki=KiMustBe;
              }
              else
              {
              if (Ki>KiMustBe)
                  Ki=Ki-0.05;
                  else
                  Ki=KiMustBe;
              }
     */




    ClrWdt();

    HvGyroData = 0;




    //END TILT SENSING



    if ((HvSpd1))//&&(HvSpd2))
    {
        HvSpd1 = 0;
#if defined _5V_TST
        Spd1Res = Spd1ResPlusTST;
#endif

        if (Spd1Res < 0)
            Spd1ResPlus = -Spd1Res;
        else
            Spd1ResPlus = Spd1Res;



        //HallDelay1MaxSPD_F,HallDelay1MaxSPD_B,HallDelayMaxSPD




        if (HallDelayMaxSPDNoKMH) {

            if (Spd1ResPlus < (HallDelayMaxSPDNoKMH - 3)) {
                HallDelay1_FMustBeTemp = HallDelayMem1_F;

                if (HallDelay1_FMustBe != HallDelay1_FMustBeTemp) {
                    HallDelay1_FMustBe = HallDelay1_FMustBeTemp;
                    SetHallDelay1_F_UP();
                }
                HallDelay1_BMustBeTemp = HallDelayMem1_B;

                if (HallDelay1_BMustBe != HallDelay1_BMustBeTemp) {
                    HallDelay1_BMustBe = HallDelay1_BMustBeTemp;
                    SetHallDelay1_B_UP();
                }
            }
            if (Spd1ResPlus > (HallDelayMaxSPDNoKMH + 3)) {
                HallDelay1_FMustBeTemp = HallDelay1MaxSPD_F;

                if (HallDelay1_FMustBe != HallDelay1_FMustBeTemp) {
                    HallDelay1_FMustBe = HallDelay1_FMustBeTemp;
                    SetHallDelay1_F_UP();
                }
                HallDelay1_BMustBeTemp = HallDelay1MaxSPD_B;

                if (HallDelay1_BMustBe != HallDelay1_BMustBeTemp) {
                    HallDelay1_BMustBe = HallDelay1_BMustBeTemp;
                    SetHallDelay1_B_UP();
                }

            }


        } else {
            if (HallDelay1_FMustBe != HallDelayMem1_F) {
                HallDelay1_FMustBe = HallDelayMem1_F;
                SetHallDelay1_F_UP();
            }
            if (HallDelay1_BMustBe != HallDelayMem1_B) {
                HallDelay1_BMustBe = HallDelayMem1_B;
                SetHallDelay1_B_UP();
            }

        }


        /*
            if (Spd1ResPlus<HallDelayMaxSPDNoKMH)
            {
                        
                DeltaDelay=K_HallDelay*(float)Spd1ResPlus;
                HallDelay1_FMustBeTemp=HallDelayMem1_F+(char)DeltaDelay;
                
                if (HallDelay1_FMustBe!=HallDelay1_FMustBeTemp)
                    {
                    HallDelay1_FMustBe=HallDelay1_FMustBeTemp;
                    SetHallDelay1_F_UP();
                    }                
                
                
            }*/



    }






    if (StartCnt)
        StartCnt--;


    GyroAcel();


    //-----------START  PWM  ----------------------------------------------
#ifdef PROTECT
    //ProtectValue=ReadProgramMemory(0x24d6);
    //ProtectValue=ReadProgramMemory(0x1f24);
    if (((unsigned int) (ReadProgramMemory(0x1f24))) != 0x0f85)
        //    if (ProtectValue!=0x0f85)
        CriticalError = CRERR_SEC_ERROR_3;
#endif


    if (!DirectControlMotor) {


        BreakPressedPrev = BreakPressed;
        //        if (Vector)
        //            IEC3bits.T8IE = 0;
        TestBreak();
        if (Monocycle)
            BreakPressed = 0;

        if (Joystick && (_2WDMode))
            AnalogBreak = 0;

        if (!_2WDMode)
            Joystick = 0;


        if (BreakFilter) {
            int Tm;
            ADCThrottleBreak_Summ = 0;
            for (Tm = 0; Tm < ADCThrottleBreak_SIZE; Tm++) {
                ADCThrottleBreak_Summ = ADCThrottleBreak_Summ + ADCThrottleBreak_Mass[Tm];
                if (Tm < ADCThrottleBreak_SIZE - 1)
                    ADCThrottleBreak_Mass[Tm] = ADCThrottleBreak_Mass[Tm + 1];
            }
            ADCThrottleBreak_Mass[ADCThrottleBreak_SIZE - 1] = ADCThrottleBreakADC;


            ADCThrottleBreak_Summ = ADCThrottleBreak_Summ>>ADCThrottleBreak_SIZE_SHFT;
            ADCThrottleBreak = (unsigned int) ADCThrottleBreak_Summ;
        } else {
            ADCThrottleBreak = ADCThrottleBreakADC;
        }



        if (!Monocycle) {


            if (AnalogBreak) {
                SmoothBreak = 0;

                BreakTMP = ADCThrottleBreak;
                if (BreakTMP > BreakThresholdUp)
                    BreakTMP = BreakThresholdUp;
                BreakTMP = BreakTMP - BreakThresholdDn;
                if (BreakTMP < 0)
                    BreakTMP = 0;

                if (TimerRegenOff > 0)
                    TimerRegenOff--;
                if ((UBT > RegenOff)&&!TimerRegenOff) {
                    BreakTMP = 0;
                    TimerRegenOff = 1000;
                    if ((!Sounds)&&(!AlarmOn))
                        SoundNum = 18;

                }
                if (TimerRegenOff) {
                    BreakTMP = 0;
                }

                if (BreakTMP > 50) {
                    BreakPressed = 1;
                    ThrottleTmp = BreakTMP;
                } else {
                    if (!BreakPressed) {






                        if (!WheelingNew) {
                            ThrottleTmp = ADCThrottle;
                        } else
                            ThrottleTmp = 0;

                        if (ThrottleTmp > SensorThresholdUp)
                            ThrottleTmp = SensorThresholdUp;

                        ThrottleTmp = ThrottleTmp - SensorThresholdDn;

                        if (ThrottleTmp < 0)
                            ThrottleTmp = 0;
                    } else {
                        ThrottleTmp = ADCThrottle;

                        if (ThrottleTmp > SensorThresholdUp)
                            ThrottleTmp = SensorThresholdUp;
                        ThrottleTmp = ThrottleTmp - SensorThresholdDn;

                        if (ThrottleTmp < 0)
                            ThrottleTmp = 0;
                        if (ThrottleTmp < 80) {
                            BreakPressed = 0;
                        } else
                            ThrottleTmp = 0;

                    }
                }




            } else {

                ThrottleTmp = ADCThrottle;
                if (BreakPressed) {
                    if (ButtonBreakOnly) {
                        if (ButtonBreakOnlyTime != 0) {
                            if (!ButtonBreakOnlyPrev) {
                                ButtonBreakOnlyPrev = 1;
                                ThrottleTmp = 0;
                                ButtonBreakOnlyTimeAdd = ((float) ButtonBreakOnlyTime)*((float) 2.5);
                                if (ButtonBreakOnlyTimeAdd != 0)
                                    ButtonBreakOnlyTimeAdd = ((float) ButtonBreakOnlyPWM) / ((float) ButtonBreakOnlyTimeAdd);
                                ThrottleTmpAdd = 0;
                            } else {
                                if (ThrottleTmp < ButtonBreakOnlyPWM)
                                    ThrottleTmpAdd = ThrottleTmpAdd + ButtonBreakOnlyTimeAdd;
                                ThrottleTmp = ThrottleTmpAdd;
                            }
                        } else
                            ThrottleTmp = ButtonBreakOnlyPWM;
                    }
                } else
                    ButtonBreakOnlyPrev = 0;

                if (ThrottleTmp > SensorThresholdUp)
                    ThrottleTmp = SensorThresholdUp;
                if (ThrottleTmp > SensorThresholdDn)
                    ThrottleTmp = ThrottleTmp - SensorThresholdDn;
                else
                    ThrottleTmp = 0;


                if (AlarmOn) {
                    if (ThrottleTmp > 150) {
                        if (!HorningH) {
                            HorningH = 1;
                            if (!Sounds)
                                SoundNum = 14;
                        }
                    }
                    ThrottleTmp = 0;
                }





                if (Joystick) {
                    ThrottleTmp = ThrottleTmp - JoystickCalibrX + SensorThresholdDn;
                    if (ThrottleTmp > 0) {
                        if (ThrottleTmp > JoistickDeadZone)
                            ThrottleTmp = ThrottleTmp - JoistickDeadZone;
                        else
                            ThrottleTmp = 0;
                    } else {
                        if (ThrottleTmp<-JoistickDeadZone)
                            ThrottleTmp = ThrottleTmp + JoistickDeadZone;
                        else
                            ThrottleTmp = 0;
                    }
                } else {

                    if (ThrottleTmp < 0)
                        ThrottleTmp = 0;
                }


            }

            ThrottleTmpMixed = ThrottleTmp;







            if (SlowStart && (!PWM_Mode)) {
                if (!BreakPressed) {
                    if (Spd1FlPlus < SlowStrtSpd) {
                        ThrottleTmpMustBe = ThrottleTmp;
                        if (!SlStrt) {
                            SlStrt = 1;
                            ThrottleTmpChng = ThrottleTmp;
                        }
                    }
                } else
                    SlStrt = 0;
            } else
                SlStrt = 0;

            if (SlStrt) {

                if (Curr1Show > ((float) 4000 / CurrPerDigit)) {
                    SlStrt = 0;
                }
                if (ThrottleTmpChng > ThrottleTmp)
                    if (Spd1FlPlus >= SlowStrtSpd)
                        SlStrt = 0;

                if (ThrottleTmpChng < ThrottleTmpMustBe) {
                    ThrottleTmpChng = ThrottleTmpChng + ThrottleTmpChngMem;
                    if (ThrottleTmpChng >= ThrottleTmpMustBe)
                        if (Spd1FlPlus >= SlowStrtSpd)
                            SlStrt = 0;
                }
                if (ThrottleTmpChng > ThrottleTmpMustBe) {
                    if (ThrottleTmpChng >= ThrottleTmpChngMem)
                        ThrottleTmpChng = ThrottleTmpChng - ThrottleTmpChngMem;
                    else
                        ThrottleTmpChng = 0;
                    if (ThrottleTmpChng <= ThrottleTmpMustBe)
                        if (Spd1FlPlus >= SlowStrtSpd)
                            SlStrt = 0;
                }

                ThrottleTmp = ThrottleTmpChng;
                if (ThrottleTmp < 0)
                    ThrottleTmp = 0;
            }



            if (PWM_Mode && (!SlowStart)) {

                if (!BreakPressed) {
                    if ((BreakPressedPrev)&&(!BreakPressed)&&(!ThrottleTmp)) {
                        ESumm_PWM_Mode = 0;
                        PWM_Mode_Target = ThrottleTmp;
                    }

                    if (PWM_Mode_ZeroThrottle) {
                        if (!Joystick) {
                            if (ThrottleTmp < 30) {
                                if ((!StrongMode)&&(!SIN_MIDDLE))
                                    ESumm_PWM_Mode = 0;
                                if (StrongMode && (Spd1ResPlus < StrongModeSpdFilterOff))
                                    ESumm_PWM_Mode = 0;
                                if (SIN_MIDDLE)
                                    ESumm_PWM_Mode = 0;
                                if (MixedMode2)
                                    ESumm_PWM_Mode = 0;
                            }
                        } else {
                            if ((ThrottleTmp < 30)&&(ThrottleTmp>-30)) {
                                if ((!StrongMode)&&(!SIN_MIDDLE))
                                    ESumm_PWM_Mode = 0;
                                if (StrongMode && (Spd1ResPlus < 2))
                                    ESumm_PWM_Mode = 0;
                                if (SIN_MIDDLE)
                                    ESumm_PWM_Mode = 0;
                            }

                        }







                    }


                    E_PWM_Mode = ThrottleTmp - PWM_Mode_Target;

                    Ep_PWM_Mode = ThrottleTmp*Kp_PWM_Mode;

                    if (E_PWM_Mode > 0)
                        ESumm_PWM_Mode = ESumm_PWM_Mode + E_PWM_Mode * Ki_PWM_Mode;
                    else
                        ESumm_PWM_Mode = ESumm_PWM_Mode + E_PWM_Mode*Ki_PWM_ModeOff;

                    /*if (ESumm_PWM_Mode>(SensorThresholdUp-SensorThresholdDn))
                        ESumm_PWM_Mode=SensorThresholdUp-SensorThresholdDn;
                    if (ESumm_PWM_Mode<0)
                        ESumm_PWM_Mode=0;
                     */
                    PWM_Mode_Target = ESumm_PWM_Mode + Ep_PWM_Mode;


                    if (PWM_Mode_Target > (SensorThresholdUp - SensorThresholdDn)) {
                        PWM_Mode_Target = SensorThresholdUp - SensorThresholdDn;
                        ESumm_PWM_Mode = PWM_Mode_Target - Ep_PWM_Mode;
                    }
                    if (!Joystick)
                        if (PWM_Mode_Target < 0) {
                            PWM_Mode_Target = 0;
                            ESumm_PWM_Mode = 0;
                        }


                    ThrottleTmp = PWM_Mode_Target;
                } else {
                    if ((BreakPressedPrev)&&(!BreakPressed)) {
                        if (!ThrottleTmp) {
                            ESumm_PWM_Mode = 0;
                            PWM_Mode_Target = ThrottleTmp;
                        }
                    }

                    Nop();
                    Nop();
                    Nop();
                }




            }

            if (!PWM_Mode) {
                ESumm_PWM_Mode = 0;
                PWM_Mode_Target = ThrottleTmp;

            }


            //  if (!SpeedControl)    
            //    Nop();

            if (SIN_MIDDLE) {
                MixedMode = 0;
                MixedMode2 = 0;
            }

            if (MixedMode) {
                CntMixedMode++;
                if (CntMixedMode > CntMixedModeMax) {
                    CntMixedMode = 0;
                    DiffMixed = ThrottleTmpMixed - ThrottleTmpPrev;
                    ThrottleTmpPrev = ThrottleTmpMixed;


                    if (!((BtPID_Activated && StrongModePID) || (SpeedControlPID && StrongModePID))) {

                        if (!MixedModeSlowSpeedOff) {
                            if (DiffMixed<-MixedModeLevelOff) {
                                StrongMode = 0;
                                StrongModeMixedMustOn = 0;
                            }
                        } else {
                            if ((Spd1ResPlus < MixedModeSlowSpeed)&&(ThrottleTmp < 200)) {
                                StrongMode = 0;
                                StrongModeMixedMustOn = 0;
                            }
                        }

                        if (DiffMixed > MixedModeLevelOn) {
                            StrongModeMixedMustOn = 1;
                        }
                    }
                }
            }

            /*if (Vector)
            {
                if (Curr1>62)
                {
                TrapezoidaRAM1_Temp=TrapezoidaRAM1;
                SetOverCurrTrapezoida=1;
                TrapezoidaRAM1=1;
                }
                if ((Curr1<33)&&(SetOverCurrTrapezoida))
                {
                SetOverCurrTrapezoida=0;
                TrapezoidaRAM1=TrapezoidaRAM1_Temp;
                }
        
            }
             */
            if (StrongModeMixedMustOn) {
                if ((Curr1 > CurrMixed)&&(!BreakPressed)) {
                    StrongModeMixedMustOn = 0;
                    StrongMode = 1;
                }
            }



            if (MixedMode) {
                if (BreakPressed)
                    StrongMode = 0;
            }



            if (StartingMove) {
                StartingMove = 0;
                if (Sensorless)
                    SoundNum = 9;
                else
                    SoundNum = 11;
                if (ThrottleTmp > 100)
                    CriticalError = CRERR_THROTTLE_ON_HIGH;
            }


            if (CriticalError == CRERR_THROTTLE_ON_HIGH) {
                if (ThrottleTmp < 100) {
                    CriticalError = 0;
                    BuzzerMacroOff
                }
            }



            if (CriticalError == CRERR_THROTTLE_AFTER_TUNING) {
                if (ThrottleTmp < 100) {
                    CriticalError = 0;
                    BuzzerMacroOff
                }
            }


            if ((PID_On)&&(BreakPressed)) {
                if ((StrongMode)&&(BtPID_Activated)&&(StrongModePID)) //&&(!SpeedControl))
                {
                    PID_On = 0;
                }
                if (!StrongMode) {
                    PID_On = 0;
                }
            }





            if (SpeedControl && SpeedControlPID && BreakPressed) {
                SoundNum = 10;
                SpeedControlPID = 0;
                if (StrongModePID)
                    StrongMode = PrevStrongMode;
            }

            if (SpeedControl && (BreakPressed)&&(!StrongMode)) {
                ESumm = 0;
                ECurr1Summ = 0;
            }

            if (StrongModeMotorOff) {
                if (StrongMode&&!MixedMode2) {

                    if (!SIN_MIDDLE) {
                        if (!Monocycle)
                            BreakPressed = 0;
                    }

                }
            }


            if (SmoothBreak) {
                if ((!BreakPressedPrev)&&(BreakPressed)) {
                    if (ThrottleTmp) {
                        if ((UBTNoRegen > UBatHi)&&(!Sounds))
                            SoundNum = 18;
                        BreakPressed = 0;
                        BreakCntOn = 3;
                        DisconnectMotor = 1;
                    }
                }

                if ((BreakPressedPrev)&&(!BreakPressed)) {
                    if (ThrottleTmp) {
                        DisconnectMotor = 0;
                        BreakPressed = 1;
                        BreakCntOff = 3;
                    }
                }
                /*          if ((BreakPressedUp)&&(!ThrottleTmp))
                      {
                      BreakPressedUp=0;
                      DisconnectMotor=0;
                      }
                 */
                if (BreakPressedUp) {
                    BreakPressedUp = 0;
                    DisconnectMotor = 0;
                }

                if (StrongModeMotorOff) {
                    if (StrongMode&&!MixedMode2) {

                        if (!SIN_MIDDLE) {
                            if (!Monocycle)
                                BreakPressed = 0;
                            DisconnectMotor = 0;
                        }
                    }
                }

            }


            if ((UBT > RegenOff) && BreakPressed&&!AnalogBreak) {
                ThrottleTmp = 0;
                BreakPressed = 0;
                //DisconnectMotor=0;
                if ((!Sounds)&&(!AlarmOn))
                    SoundNum = 18;

            }

            if ((UBTNoRegen > UBatHi) && BreakPressed) {
                ThrottleTmp = 0;
                //BreakPressed=0;
                //DisconnectMotor=0;
                if ((!Sounds)&&(!AlarmOn))
                    SoundNum = 18;
            }

            if (Vector) {
                if (IFS3bits.T8IF)
                    Phase1Period1Up = TMR8;
                IEC3bits.T8IE = 1;
            }

            if (BreakPressed)
                DisconnectMotor = 0;





            if ((Wheeling)&&(BreakPressed)) {
                Wheeling = 0;
                StrongMode = 0;
                SoundNum = 10;
            }



            if (!Break1 || BreakPressed)
                StpLightsNew = 1;
            else
                StpLightsNew = 0;

            if (BreakPressed) {
                if (StpLights)
                    StopLights = 1;
                else
                    StopLights = 0;
            } else
                StopLights = 0;


            //        if (!Wheeling)
            if (!((!NoBalance)&&(Wheeling))) {





                if (AlarmOn) {
                    BreakPressed = 1;
                }
                if (AlmOffing) {
                    AlmOffing = 0;
                    BreakPressedPrev = 1;
                }


                if (BreakPressedPrev != BreakPressed) {
                    if (BreakPressed) {
                        Forward1 = 0;
                        IEC1bits.CNIE = 0;
                        PrevForward1 = 0;
                        Sensor1 = ReadSensor1_B();
                        Sensor1_Prev = Sensor1;
                        Phases1();
                        IEC1bits.CNIE = 1;


                    } else {
                        if (!Vector) {
                            Forward1 = 1;
                            IEC1bits.CNIE = 0;
                            PrevForward1 = 1;
                            Sensor1 = ReadSensor1_F();
                            Sensor1_Prev = Sensor1;
                            Phases1();
                            IEC1bits.CNIE = 1;
                        } else {
                            //                            IEC3bits.T8IE = 0;
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


                            Sensor1_Prev = Sensor1;
                            if (IFS3bits.T8IF)
                                Phase1Period1Up = TMR8;
                            IEC3bits.T8IE = 1;
                        }
                        OffingBreak = 1;


                    }
                }





                if (!Joystick)
                    Throttle = SensorThresholdUp - SensorThresholdDn;
                else {
                    if (ThrottleTmp > 0)
                        Throttle = SensorThresholdUp - JoystickCalibrX - JoistickDeadZone;
                    else
                        Throttle = JoystickCalibrX - SensorThresholdDn - JoistickDeadZone;
                }











                if (AlarmOn) {
                    ThrottleTmp = SensorThresholdUp;
                }

                if (!BreakPressed) {
                    if (HvOptions)
                        KThrottle = MAX_PWM / Throttle;
                    else
                        KThrottle = 0;

                    PWM1Temp = ThrottleTmp*KThrottle;

                    if ((SpeedControl)&&(!SpeedControlPID)&&(!Sensorless)) {
                        if (!CurrentControlOnly)
                            Spd1UST = ((float) (PWM1Temp * (long int) MaxSpd)) / (((float) MAX_PWM) * ImpToKmH1_t);
                        else
                            CurrUstCurrentOnly = (CurrentMaxCurrentOnlyWork * PWM1Temp) / ((float) MAX_PWM);
                    } else {
                        if (SpeedControlPID)
                            //        Spd1UST_Tmp=(float)((float)PWM1Temp/(float)MaxSpdCoeff);
                            Spd1UST_Tmp = ((float) (PWM1Temp * (long int) MaxSpd)) / (((float) MAX_PWM) * ImpToKmH1_t);
                        if (!Sensorless) {
                                PWM1Temp = (((float) PWM1Temp) / 100) * MAX_PWM_MEM_WORK;
                        }
                    }
                    if (DisconnectMotor)
                        Spd1UST = 0;

                } else {

                    if (ThrottleTmp < (BreakThreshold - SensorThresholdDn)) {
                        if (HvOptions)
                            KThrottle = (float) KFirstBreak / (float) (BreakThreshold - SensorThresholdDn);
                        else
                            KThrottle = 0;
                        PWM1Temp = KFirstBreak - (ThrottleTmp * KThrottle);
                        if (PWM1Temp < 0)
                            PWM1Temp = 0;
                        if (PWM1Temp == KFirstBreak)
                            PWM1Temp = MAX_PWM;
                        _1stBreak = 1;
                    } else {
                        if (HvOptions)
                            KThrottle = (float) MAX_PWM / (float) (SensorThresholdUp - BreakThreshold);
                        else
                            KThrottle = 0;
                        PWM1Temp = ThrottleTmp - (BreakThreshold - SensorThresholdDn);
                        PWM1Temp = MAX_PWM - ((float) PWM1Temp * KThrottle);
                        if (PWM1Temp < 0)
                            PWM1Temp = 0;

                        _1stBreak = 0;

                    }

                    PWM1Temp = -PWM1Temp;

                }

                if (!SpeedControlPrev)
                    if (SpeedControl)
                        ECurr1Summ = 0;

                SpeedControlPrev = SpeedControl;

                if (SpeedControl && (!BreakPressed)&&(!DisconnectMotor)) {
                    if (!PID_On)
                        StrtPID_On = 1;
                }
                AutoPIDStateMachine();
                //-------------  START PID  ---------------------------
                if (StrtPID_On) {
                    StrtPID_On = 0;

                    ESumm = CurrentControlCurr;
                    ECurr1Summ = PWM1Temp;

                    /*if (KiNoMan!=0)
                    ESumm=((float)PWM1Temp)/KiNoMan;
                    else
                    ESumm=0;*/
                    E = 0;
                    if (PWM1Temp < 0)
                        PWM_Minus = 1;
                    else
                        PWM_Minus = 0;
                    Spd1UST_Tmp = 0;
                    PID_On = 1;
                    Spd1UST = (float) Spd1Res;
                    PWMTempPID = PWM1Temp;
                    FlgPID = 1;
                }


                if (PID_On) {
                    Spd1UST = Spd1UST - ((float) PI_Curr1Res) * KTemperatureSPDControl;
                    //    if (!Joystick)
                    if (Spd1UST < 0)
                        Spd1UST = 0;
                    if (!CurrentControlOnly) {

                        CurrentProtectionPID();


                        if (HvSpd1_PID)//&&(!MorePWM))
                        {
                            HvSpd1_PID = 0;


                            E = Spd1UST - Spd1Res;
                            if (E == 0)
                                E = -1;

                            Ep = E*KpNoMan;


                            ESumm = ESumm + E*KiNoMan; //+Ed;

                            //   if (Spd1UST==0)
                            // ESumm=0;


                            Ei = ESumm;
                            EPID_Res = Ep + Ei;

                            if (EPID_Res < 0) {
                                EPID_Res = 0;
                                ESumm = 0;
                            }


                            if (EPID_Res > MAX_PWM_CONST)//<<CURRMASS_SHIFT))
                            {
                                EPID_Res = MAX_PWM_CONST; //<<CURRMASS_SHIFT;
                                ESumm = EPID_Res - Ep;
                            }


                            if (EPID_Res > PI_Curr1ResPID)//<<CURRMASS_SHIFT))
                            {
                                EPID_Res = EPID_Res - PI_Curr1ResPID; //<<CURRMASS_SHIFT;
                                ESumm = EPID_Res - Ep;
                            } else {
                                EPID_Res = 0;
                                ESumm = -Ep;
                            }





                            if (EPID_Res > MAX_PWM_CONST)
                                EPID_Res = MAX_PWM_CONST;
                            if (EPID_Res<-MAX_PWM_CONST)
                                EPID_Res = -MAX_PWM_CONST;

                            /*    
                                    DiffPidAdd=EPID_Res-(float)PWMPrevPID;
                                    DiffPidAdd=DiffPidAdd/5;
                                    if (DiffPidAdd<0)
                                        DiffPidAdd=-DiffPidAdd;
            
                                    PWMPrevPID=(int)EPID_Res;
            
                                    EPID_Res_Target=EPID_Res;
                             */
                        }
                        /*
                                if (EPID_Res_Target>EPID_Res_Tek)
                                {
                                    EPID_Res_Tek=EPID_Res_Tek+DiffPidAdd;
                                }
                                else
                                {
                                    EPID_Res_Tek=EPID_Res_Tek-DiffPidAdd;
                                }
        
                                EPID_Res_Tek=EPID_Res;
                         */


                        if (StrongModePID&&!StrongMode && SpeedControlPID) {
                            //  if ((CurrentControlCurr>>CURRMASS_SHIFT)>CurrMixed)
                            {
                                PrevStrongMode = StrongMode;
                                StrongMode = 1;
                            }
                        }

                        if (StrongModePID&&!StrongMode&&!SpeedControl) {
                            //              if ((CurrentControlCurr>>CURRMASS_SHIFT)>CurrMixed)
                            {
                                PrevStrongMode = StrongMode;
                                StrongMode = 1;
                            }
                        }


                        PWM1_Mem = (int) EPID_Res;
                        /*
                       int DiffPWM;
             
            
                                   if (PWMPrev>PWM1_Mem)
                                       DiffPWM=PWMPrev-PWM1_Mem;
                                   else
                                       DiffPWM=PWM1_Mem-PWMPrev;
            
                                   if (DiffPWM>PWMChangedThreshold)
                                       Nop();
                
                                   PWMPrev=PWM1_Mem;
                         */

                    } else {
                        EPID_Res = CurrUstCurrentOnly;
                        PWM1_Mem = (int) EPID_Res;
                    }
                    EPID_ResTmp = EPID_Res;
                    //----------------
                    if (CurrentControlOnly) {

                        CurrentControlCurrUst = (long int) EPID_Res;
                        //KiCurr=0;
                        if (CurrentControlCurr < 0)
                            CurrentControlCurr = 0;
                        ECurr1 = CurrentControlCurrUst - CurrentControlCurr;
                        EpCurr1 = ECurr1*KpCurr;
                        ECurr1Summ = ECurr1Summ + (float) ECurr1*KiCurr;

                        CurrControlPIRes = (long int) ECurr1Summ + (long int) EpCurr1;

                        if (CurrControlPIRes > MAX_PWM) {
                            CurrControlPIRes = MAX_PWM;
                            ECurr1Summ = CurrControlPIRes - (long int) EpCurr1;

                        }
                        if (CurrControlPIRes < 0) {
                            CurrControlPIRes = 0;
                            if (KiCurr != 0)
                                ECurr1Summ = CurrControlPIRes - (long int) EpCurr1;
                            else
                                ECurr1Summ = 0;
                        }






                        PWM1_Mem = (int) CurrControlPIRes;
                    }
                    //----------------




                    //PWM1_Mem=(int)EPID_Res;



                    if (!PWM_Minus) {
                        if (FlgPID) {
                            if (PWMTempPID > 100) {
                                if (PWM1Temp < (PWMTempPID - 100))
                                    FlgPID = 0;
                            } else
                                FlgPID = 0;
                        }
                        if ((PWM1Temp > (PWM1_Mem + 80))&&(!SpeedControl)&&(!FlgPID))
                            PID_On = 0;

                        if (SpeedControlPIDOffCnt)
                            SpeedControlPIDOffCnt--;
                        if (Spd1UST_Tmp > (Spd1UST + 4) && SpeedControlPID&&!FlgPID && (!SpeedControlPIDOffCnt)) {
                            SpeedControlPID = 0;
                            SoundNum = 10;
                            if (StrongModePID)
                                StrongMode = PrevStrongMode;
                        }

                        // if (!Joystick)
                        if (PWM1_Mem < 0)
                            PWM1_Mem = 0;
                    } else {
                        if (FlgPID) {
                            if (PWMTempPID<-100) {
                                if (PWM1Temp > (PWMTempPID + 100))
                                    FlgPID = 0;
                            } else
                                FlgPID = 0;
                        }

                        if ((PWM1Temp < (PWM1_Mem - 50))&&(!SpeedControl)&&(!FlgPID))
                            PID_On = 0;
                        // if (!Joystick)
                        if (PWM1_Mem > 0)
                            PWM1_Mem = 0;
                    }



                    PWM1Temp = PWM1_Mem;
                }

            }

            //-------------  END  PID  ---------------------------

            if (!Monocycle) {
                if (!BreakPressed) {
                    if (CriticalError == CRERR_PWM_CHANGED_HIGH) {
                        if ((PWM1Temp < 150)&&(PWM1Temp>-150)) {
                            CriticalError = 0;
                            BuzzerMacroOff
                        }
                    }
                    //DisconnectMotor=0;
                    if (!(DisconnectMotor || HvBreak)) {
                        if ((PWM1Temp > 20) || ((PWM1Temp<-20) && Joystick)) {
                            TmrActive = 1;
                            if (!(StartingMoveCnt && CriticalError)) {
                                if (DS) {
                                    DS = 0;
                                    RdSensors();
                                }
                            }
                        } else {
                            if ((!StrongMode)&&(!AutoNastroykaState)) {
                                if (!MonocycleSlave)
                                    DS = 1;
                            }
                            SoundTmr = 0;
                            TimerCnt = 0;
                        }
                    } else {
                        DS = 1;
                    }
                } else {
                    if ((PWM1Temp<-MAX_PWM + 20)&&(_1stBreak))
                        DS = 1;
                    else {
                        if (!(StartingMoveCnt && CriticalError)) {
                            if (DS) {
                                DS = 0;
                                RdSensors();
                            }
                        }

                    }

                }
            }
        }


        //--------------   START  WHEELING ------------------------



        if ((NoBalance)&&(Wheeling)) {
            if ((AlfaXRes>-YLimit)&&(AlfaXRes < YLimit)&&(AlfaYRes > (TiltZad - 1))&&(AlfaYRes < (TiltZad + 1))&&!ChagerViaMotor) {
                NoBalance = 0;
                SoundNum = 1;
                ESumm = ((float) PWM1Temp) / Ki;
                RotAddSumm = 0;
            }
        }
        if ((!NoBalance)&&(Wheeling)) {

            if ((AlfaXRes<-XLimit) || (AlfaXRes > XLimit) || (AlfaYRes < (TiltZad - YLimit)) || (AlfaYRes > (TiltZad + YLimit))) {
                SoundNum = 10;
                StrongMode = 0;
                Wheeling = 0;

            }


            if (DirBalance)
                E = TiltZad - AlfaYRes;
            else
                E = -TiltZad + AlfaYRes;


            Ep = E*Kp;

            ESumm = ESumm + E;

            if (ESumm > 1000000)
                ESumm = 1000000;
            if (ESumm<-1000000)
                ESumm = -1000000;

            Ei = ESumm*Ki;
            PWM1Temp = (int) Ep + (int) Ei;

        }


        //--------------   END  WHEELING ------------------------

        //--------------   START  MONOCYCLE ------------------------
        MonoWheel();
        //--------------   END  MONOCYCLE ------------------------




        if (StrtWheeling) {
            PID_On = 0;
            Wheeling = 1;
            StrongMode = 1;
            //ESumm=((float)PWM1Temp)/Ki;
            StrtWheeling = 0;
            NoBalance = 1;
        }

        WheelingFunc();

        if ((StateOdm == 1)&&(PWM1Temp > 20)&&(Spd1ResPlus > 1)) {
            StateOdm = 2;
        }

        if ((StateOdm == 2)&&(PWM1Temp < 10)&&(Spd1ResPlus <= 1)) {
            StateOdm = 1;
            RecOdometrFl = 1;
            TmrOdmtrWrCnt = 0;
        }

        if (StateOdm == 1) {
            TmrOdmtrWrCnt++;
            if (TmrOdmtrWrCnt > 30000) {
                RecOdometrFl = 1;
                TmrOdmtrWrCnt = 0;
            }
        }

        if (Lock)
            PWM1Temp = 0;


        if (PWM1Temp > MAX_PWM)
            PWM1Temp = MAX_PWM;
        if (PWM1Temp<-MAX_PWM) {
            PWM1Temp = -MAX_PWM;
        }

        if (Monocycle)
            PWM100StateMachine();



        PWM1 = (int) PWM1Temp; //PWM1+RotAddP+RotAddD+RotAddI;




        if (OffingBreak) {
            OffingBreak = 0;
            PWM1 = 1;
        }

        //PWM2=PWM1;
        if (_2WDMode == 1) {
            if (Segway) {
                SegAll();
                if (NoBalance) {
                    PWM1 = 0;
                    PWM2 = 0;
                }

            } else
                PWM2 = 0;


        }
        if (_2WDMode == 2) {
            RecSlave2WDControls();
            if (MonocycleSlave) {
                if (!NoBalanceFmMaster) {
                    PWM1 = PWMMonocycleSlaveFmMaster;
                    PWM1Temp = PWMMonocycleSlaveFmMaster;
                    DS = 0;
                } else {
                    PWM1 = 0;
                    PWM1Temp = 0;
                    DS = 1;
                }
            }
            if (!Hv2WDMasterCnt) {
                PWM1 = 0;
                PWM1Temp = 0;
                DS = 1;
                CriticalError = CRERR_MASTER_DISCONNECTED;
            } else {
                if (CriticalError == CRERR_MASTER_DISCONNECTED) {
                    BuzzerMacroOff
                    CriticalError = 0;
                }
            }

        }

        if (PWM1 < 0) {
            PWM1 = -PWM1;
            PWM1Plus = 0;
            Forward1 = 0;
        } else
            if (PWM1 > 0) {
            Forward1 = 1;
            PWM1Plus = 1;
        }


        //   if (PWM1<100)
        //     Nop();



        if (!PrevForward1) {
            if (Forward1) {
                PrevForward1 = 1;
                //                IEC1bits.CNIE = 0;
                //                IEC3bits.T8IE = 0;
                if (!Vector) {
                    Sensor1 = ReadSensor1_F();
                    Sensor1_Prev = Sensor1;
                    Phases1();

                } else {
                    if (!DirPWM1)
                        Sensor1 = ReadSensor1_F_V();
                    else
                        Sensor1 = ReadSensor1_B_V();
                    Sensor1_Prev = Sensor1;
                    Sensor1_Prev_OP = Sensor1_Prev;
                    SVPWM1();
                }
                if (IFS3bits.T8IF)
                    Phase1Period1Up = TMR8;
                IEC3bits.T8IE = 1;
                IEC1bits.CNIE = 1;
            }


        } else {
            if (!Forward1) {
                PrevForward1 = 0;
                //                IEC1bits.CNIE = 0;
                //                IEC3bits.T8IE = 0;
                if (!Vector) {
                    Sensor1 = ReadSensor1_B();
                    Sensor1_Prev = Sensor1;
                    Phases1();

                } else {
                    if (!DirPWM1)
                        Sensor1 = ReadSensor1_B_V();
                    else
                        Sensor1 = ReadSensor1_F_V();
                    Sensor1_Prev = Sensor1;
                    Sensor1_Prev_OP = Sensor1_Prev;
                    SVPWM1();
                }
                if (IFS3bits.T8IF)
                    Phase1Period1Up = TMR8;
                IEC3bits.T8IE = 1;
                IEC1bits.CNIE = 1;
            }

        }










    } else {
        PWM1 = DIRPWM1;
    }
#ifdef PROTECT
    if (((unsigned int) (ReadProgramMemory(0x11d6))) != 0xf141)
        CriticalError = CRERR_SEC_ERROR_3;
#endif

    Spd0TimerStateMachine();
    Lights();

    if (Monocycle) {
        //    StrongModeMem=1;
        //     StrongMode=1;
        //  MixedMode=0;
        //   MixedMode2=0;
    }

    if (MixedMode2) {
        if (CurrMixed < 1)
            CurrMixed = 1;
        /*
                    CntMixedMode++;
                    if (CntMixedMode>CntMixedModeMax)
                    {
                        CntMixedMode=0;
                        DiffMixed=ThrottleTmpMixed-ThrottleTmpPrev;
                        ThrottleTmpPrev=ThrottleTmpMixed;
                    }    
        
        
                switch (MixedMode2StateMachine)
                {
                    case 0:
                        if ((Curr1Show>CurrMixed+14)&&(!BreakPressed))
                        {
                            if ((DiffMixed>MixedModeLevelOn))
                            {
                            StrongMode=1;
                            MixedMode2StateMachine=1;
                            }
                        }
                        break;
                    case 1:
                        if ((Curr1Show<CurrMixed||BreakPressed)&&(!WheelingNew))
                        {
                            StrongMode=0;
                            MixedMode2StateMachine=0;
                        }
                        if (DiffMixed<-MixedModeLevelOff)
                        {
                            StrongMode=0;
                            MixedMode2StateMachine=0;
                        }
                        break;
                }*/

        if ((Curr1Show > CurrMixed + 14)&&(!BreakPressed))
            StrongMode = 1;


        if ((Curr1Show < CurrMixed || BreakPressed)&&(!WheelingNew))
            StrongMode = 0;


    } else {
        if (MixedModeSlowSpeedOff) {
            if (StrongModeMem) {
                if (StrongMode) {
                    if (Spd1ResPlus < MixedModeSlowSpeedFl)//&&(ThrottleTmp<200))
                    {
                        PrevStrongMode = StrongMode;
                        StrongMode = 0;
                        StrongModeMixedMustOn = 0;
                    }
                } else {
                    if (Spd1ResPlus >= MixedModeSlowSpeedFl)//&&(ThrottleTmp<200))
                    {
                        StrongMode = 1;
                    }
                }
            }
        }
    }



    /*  if (Vector&&TrapezoidaWhenBigCurrent)
      {
        
          if ((Curr1>(BigCurrent+250))&&(!SetOverCurrTrapezoida))
          {
          TrapezoidaRAM1_Temp=TrapezoidaRAM1;
          SetOverCurrTrapezoida=1;
          TrapezoidaRAM1=1;
          }
          if ((Curr1<BigCurrent)&&(SetOverCurrTrapezoida))
          {
          SetOverCurrTrapezoida=0;
          TrapezoidaRAM1=TrapezoidaRAM1_Temp;
          }
        
      }
     */

    /*     
    if (Vector&&TrapezoidaWhenBigCurrent)
 {
        
     if ((Curr1>(625))&&(!SetOverCurrTrapezoida))
     {
     TrapezoidaRAM1_Temp=TrapezoidaRAM1;
     SetOverCurrTrapezoida=1;
     TrapezoidaRAM1=1;
     }
     if ((Curr1<500)&&(SetOverCurrTrapezoida))
     {
     SetOverCurrTrapezoida=0;
     TrapezoidaRAM1=TrapezoidaRAM1_Temp;
     }
        
 }
     */




    if (Vector && TrapezoidaWhenBigSpeed) {
        if (Spd1ResPlus > VectorOnOffSpdHi)
            TrapezoidaRAM1 = 1;

        if (Spd1ResPlus < VectorOnOffSpdLo)
            TrapezoidaRAM1 = 0;

    }



    if (Vector && TrapezoidaWhenBigCurrent) {

        if ((Curr1 > (BigCurrent + 50))&&(!SetOverCurrTrapezoida)) {
            TrapezoidaRAM1_Temp = TrapezoidaRAM1;
            SetOverCurrTrapezoida = 1;
            TrapezoidaRAM1 = 1;
        }
        if ((Curr1 < BigCurrent)&&(SetOverCurrTrapezoida)) {
            SetOverCurrTrapezoida = 0;
            TrapezoidaRAM1 = TrapezoidaRAM1_Temp;
        }

    }


    if (Sensorless) {
        if (ManualStart) {
            //StateSensorlessMotorStart=7;
            //SensorlessStartNoHalls=1;
            //               if (HvZ_Cr)
            {
                if ((PWM1 > 100)&&(PWM1 < 750))
                    PWM1 = 750;
                //                     DS=0;
            }
            //             else
            {
                //               PWM1=0;
                //                    DS=1;
            }
        }


        if (Spd1ResPlus < 25)
            CntZeroConst = 3;
        if (Spd1ResPlus > 35)
            CntZeroConst = 1;


        if ((PWM1 > 750)&&(!StateSensorlessMotorStart)&&(Spd1Res < 1))
            SensorlessMotorStartInit();

        if ((PWM1 < 700)&&(StateSensorlessMotorStart)&&(StateSensorlessMotorStart < 6))
            SensorlessMotorStopStarting();

        if (SensorlessNotBEMF) {
            PWM1 = SenosrlessPWM1;
            if (!(StartingMoveCnt && CriticalError)) {
                if (DS) {
                    DS = 0;
                    RdSensors();
                }
            }

        }
        SensorlessMotorStart();
        if ((!StateSensorlessMotorStart)&&(Spd1Res < 3))
            PWM1 = 0;
        if ((StateSensorlessMotorStart > 6)&&(Spd1Res < (SensorllessSpdThreshold - 2)))
            PWM1 = 0;
    }
    //SensorTSTKeys=4;


    //#ifdef TEST_PWM_KEYS
    if (TEST_PWM_KEYS) {
        //   SensorTSTKeys=1;

        //          if (!Vector)
        //          VectorInit();
        // SensorTSTKeys=2;




        if (Sensor1 != SensorTSTKeys) {
            Sensor1 = SensorTSTKeys;
            StrongMode = 1;
            if (Sensor1_Prev != Sensor1) {
                Sensor1_Prev = Sensor1;
                Phases1();


            }
        }
        DS = 0;

        //  PWM1=300;
        PWM1 = DIRPWM1_TstKeys;
    }
    //#endif
    if (StartingMoveCnt) {
        ECurr1Summ = 0;
        DS = 1;
    }

#if defined VECTOR
    ZeroThroottle = 1;
#endif

    if ((ZeroThroottle)&&(!Monocycle)) {
        if (ADCThroottleZero < 200) {
            CntZeroThroottle++;
            if (CntZeroThroottle > 100) {
                CriticalError = CRERR_THROTTLE_ZERO_ERR;
            }
        } else
            CntZeroThroottle = 0;
    } else
        CntZeroThroottle = 0;

    if (CriticalError) {
        if (CriticalError != CRERR_UBAT_LOW) {
            BuzzerOnEvent = 1;
            BuzzerMacroOn;
        }
        if (!((CriticalError == CRERR_UBAT_LOW)&&(Monocycle)))
            DS = 1;
    }






    AutoNastroyka_Func();

    if (Monocycle) {

        long int MaxPWMTmp = MAX_PWM_CONST * (long int) PWMSignal;
        MaxPWMTmp = MaxPWMTmp / 100;

        if (PWM1 > MaxPWMTmp) {
            if (!PWMSignalCnt) {
                if ((!Sounds)&&(BuzzerOffTime == 0))
                    SoundNum = 10;
            } else {
                PWMSignalCnt--;
            }
        } else {
            PWMSignalCnt = PWMSignalTimer >> 2;
        }
    }


    ChangePWM1(PWM1);
    PWM1Prev = PWM1;

    if (Vector)
        //if (T45Over)
    {
        //        IEC1bits.CNIE = 0;
        //        IEC3bits.T8IE = 0;
        SVPWM1_SetPWM();
        if (IFS3bits.T8IF)
            Phase1Period1Up = TMR8;
        IEC3bits.T8IE = 1;
        IEC1bits.CNIE = 1;
    }



    //FIN  PWM------------------------------

    if (DoNotTestBMS) {
#if !defined VECTOR
#if defined ISOLATED
        if (HvPacketUBat)
#endif
#endif
        {
            HvPacketUBat = 0;
#if defined NO_UBT
            UBT = 100;
#endif


            if (UBT > UBtLim2) {
                CntUBTLow = 0;
                CntUBtLim1 = 0;
                if (CriticalError == CRERR_UBAT_LOW)
                    CriticalError = 0;

            } else
                if (UBT > UBtLim1) {
                CntUBTLow = 0;

                if (CntUBtLim1 < 100)
                    CntUBtLim1++;
                else {
                    CntUBtLim1 = 0;
                    if (!Sounds)
                        SoundNum = 4;
                }
            } else {
                if (!Sounds)
                    SoundNum = 5;
                //#if !defined TEST_PWM_KEYS
                if (!TEST_PWM_KEYS) {
                    if (CntUBTLow < 500)
                        CntUBTLow++;

#if !defined _5V_TST            
                    else
                        CriticalError = CRERR_UBAT_LOW;
#endif
                }
                //#endif
            }
        }
    } else {

        if (BMS_L == 0) {
            Nop();
        } else
            if (BMS_L == 1) {
            if (!Sounds)
                SoundNum = 4;
        } else {
            if (!Sounds)
                SoundNum = 5;
        }
    }


    AlfaXResTmpAlm = AccXFl;
    AlfaYResTmpAlm = AccYFl;
    AlfaZResTmpAlm = AccZFl;

    int k;
    long int tmpL = 0;

    for (k = 0; k < (ACC_AV_TTL - 1); k++)
        AccXAv[k] = AccXAv[k + 1];
    AccXAv[ACC_AV_TTL - 1] = AccXFl;

    for (k = 0; k < ACC_AV_TTL; k++)
        tmpL = tmpL + (long int) AccXAv[k];
    AccXAvRes = (int) (tmpL >> ACC_AV_SHFT);


    tmpL = 0;
    for (k = 0; k < (ACC_AV_TTL - 1); k++)
        AccYAv[k] = AccYAv[k + 1];
    AccYAv[ACC_AV_TTL - 1] = AccYFl;

    for (k = 0; k < ACC_AV_TTL; k++)
        tmpL = tmpL + AccYAv[k];
    AccYAvRes = (int) (tmpL >> ACC_AV_SHFT);


    tmpL = 0;
    for (k = 0; k < (ACC_AV_TTL - 1); k++)
        AccZAv[k] = AccZAv[k + 1];
    AccZAv[ACC_AV_TTL - 1] = AccZFl;

    for (k = 0; k < ACC_AV_TTL; k++)
        tmpL = tmpL + AccZAv[k];
    AccZAvRes = (int) (tmpL >> ACC_AV_SHFT);




    if (AlarmOn) {
        Alm();
    }

    CntSamples++;

    
    SndDebugArrays();
    


    TrmFlashMass();
    TrmFlashMass2();
    SendStateOfSinTest();
    TrmErrorsHC05();
    SendProfileMassToPC();
    SendFlashMassToPC();
    SendFlashMass2ToPC();
    CmdOK();
    CmdOK2();
    CmdOK3();
    CmdSendUnlockMSG();
    TrmDataPacketHC05();

    if (_2WDMode == 0) {
        MonocycleSlave = 0;
    }

    if (_2WDMode == 1) {
        TrmControls_U3();
        MonocycleSlave = 0;
    }

    if (_2WDMode == 2)
        RecSlave2WDControls();


    PI_Chager();

    if (BuzzerOnAlways) {
        BuzzerOnEvent = 2;
        BuzzerMacroOn//Buzzer=1;
    }


    if (NoSecret) {
        BuzzerOnEvent = 3;
        BuzzerMacroOn//Buzzer=1;
    }

    


    



#if defined SERVICE
    if (TestU3ChangeSpd)
#else
    if (0)
#endif
    {
        if (!StartCnt) {
            TestU3ChangeSpd = 0;
            U4_9600_On();
            CntU3Off = 700;
        }
    }
    if (CntU3Off) {
        CntU3Off--;
        if (!CntU3Off) {
            if (!_2WDMode)
                U3MODEbits.UARTEN = 0;
        }
    }



}
float kdkj;

void InitSegAll(void) {
    Flgs4.Flags = 0;
    Flgs5.Flags = 0;


    kdkj = ImpToKmH;
    kdkj = ImpNa10Metr;
    kdkj = _CmImp;

    StartCnt = 128;

    HvOptions = 0;



    InitSensorsNear();



    OSC_Init();
    InitPorts();
    InitBLDCPorts();

    //    T3Init();
    //T5Init();
    //T7Init();
    T9Init();
    //T4_5Init();

    CNT_U = 500;

    /*
#if defined HighDataSpdUART
    T6_7Init();
#endif
*/

    InitPort_U4();
    UARTInit_U4();
#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 0;
#else
    KEY_BT = 1;
#endif
#else
    KEY_BT = 0;
#endif

    InitOC4();
    // InitOC1();
    //   InitOC2();
#if defined VECTORS
    InitOC3();
#endif

    //    InitPWM();


    //InitAccSPI();
    InitGyroSPI();


    T3Init();


    InitFlash();






    OdometrSectorNumConst = 50;

    OdometrCnt = 250;
    OdometrErased = 0;





    ADC1Init();


    //Comparator3_Init();
    Comparator2_Init();
    Sensor1 = 0;
    Sensor1_Prev = 0;

    Sensor2 = 0;
    Sensor2_Prev = 0;



    CntUDPFill = 0;
    CntUDPFillConst = 10;
    CntSamples = 0;
    //ErrorCode=0;
    TiltTimoutConst = 50;
    TiltTimoutCnt = TiltTimoutConst;

    TiltZad = 0;
    //TiltYCorr=2;
    ESumm = 0;

    //KpMustBe=100;
    Kp = 50;

    //Kd=0;
    //Ki=0;

    PhaseCnt1 = 0;
    PhaseCnt2 = 0;
    CntNoBalance = 0;


    Transmitting_U3 = 0;
    GettingPacketU3_FL = 0;
    CHK_Err_U3 = 0;
    HvDataPacketU3_FL = 0;

    MustTrm = 0;
    NoBalance = 1;




    NoBalanceCode = 2;
    PrevForward1 = 0;
    PrevForward2 = 0;
    HvAccData = 0;
    HvGyroData = 0;
    Starting = 1;

    CalibrateAcc = 0;
    MustTrmFlashMass = 0;
    SendPhase = 0;
    TakingPacketUbat = 0;
    HvPacketUBat = 0;
    CanSensor1 = 1;
    CanSensor2 = 1;
    HvSpd1 = 0;

    MeasuringSpd1 = 0;


    //SoundNum=11;


    StartingMoveCnt = 400;
    StartingMove = 0;

    But4Pressed = 0;
    ButBPressed = 0;
    HvBt4 = 0;

    Drebezg4 = 0;
    //DrebezgB=0;
    HvToChangeNumSpdLimFl = 0;
    Stopping = 0;
    PreStopping = 0;

    HvToPrg = 0;
    RecOdometrFl = 0;
    NoValidTilt = 0;
    ErrorTiltFl = 0;
    OnTransmittHC05 = 0;
    HvReplyHC05 = 0;
    ChangingTiltSensor = 0;
    //NoAutoTrm=1;







    CntRecAcc = 2;
    CntRecGyro = 2;

#if !defined LSM6DS33

#if !defined VECTOR_MPU_6000
    Acc_txBuf[0] = 0x20 | 0x40; //Addr | autoincrement
    Acc_txBuf[1] = 0x27;

    TxRxSPI_ACC(2);
    while (!HvAccData);
    HvAccData = 0;
#endif
#if !defined VECTOR
    Gyro_txBuf[0] = 0x20 | 0x40; //Addr | autoincrement
    Gyro_txBuf[1] = 0x3f;
    TxRxSPI_GYRO(2);
    while (!HvGyroData);
    HvGyroData = 0;

    Gyro_txBuf[0] = 0x24 | 0x40; //Addr | autoincrement
    Gyro_txBuf[1] = 0x80;
    TxRxSPI_GYRO(2);
    while (!HvGyroData);
    HvGyroData = 0;

#else
    HvToTest = 1;
    MPU60000Init();
#endif

#else
    LSM6DS33_Init();
#endif


    TiltYSumm = 0;

    CntTiltYSumm = 0;


    ReadOdometr();
    ReadErrors();


    if (ReadOptions())
        HvOptions = 1;



    switch (PWMkHz) {
        case 1:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
            break;
        case 2:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE10kHz;
            TrapezoidaWhenBigSpeed = 1;
            if (VectorOnOffSpdLo > Trapezium10kHzLo)
                VectorOnOffSpdLo = Trapezium10kHzLo;
            if (VectorOnOffSpdHi > Trapezium10kHzHi)
                VectorOnOffSpdHi = Trapezium10kHzHi;
            break;
        case 3:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE5kHz;
            TrapezoidaWhenBigSpeed = 1;
            if (VectorOnOffSpdLo > Trapezium5kHzLo)
                VectorOnOffSpdLo = Trapezium5kHzLo;
            if (VectorOnOffSpdHi > Trapezium5kHzHi)
                VectorOnOffSpdHi = Trapezium5kHzHi;
            break;
        default:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
            PWMkHz = 1;
            break;
    }






    MAX_PWM = MAX_PWM_CONST;
    /*
    if (Monocycle)
        MAX_PWM_CONST=MAX_PWM_CONST_MONOCYCLE;
    else
    {
        if (1)//(PWM32Bits)
        MAX_PWM_CONST=MAX_PWM_CONST_MONOCYCLE;
        else
        MAX_PWM_CONST=MAX_PWM_CONST_EBIKE;
    }
     */

    for (l = 0; l < CURRMASS_SIZE; l++)
        Curr1Mass[l] = ZeroCurr1;

    AccXFilter = 0;
    AccYFilter = 0;
    AccZFilter = 0;
    GyroZFilter = 0;
    KFilterPrev = 127;
    KFilter = 128 - KFilterPrev;


    GZFTempPrev = 0;
    KdRot = 0;

    _1sCntConst = 50;
    _1sCnt1 = _1sCntConst;

    Spd1Res = 0;
    Spd1Cnt = 0;




    ESummSpd = 0;



    DirectControlMotor = 0;

    TemperatureCnt = 550;
    TemperatureFl = 0;

    Odometr10m = 0;


    Bt1CntConst = 10;
    Bt2CntConst = 10;
    Bt3CntConst = 10;
    Bt4CntConst = 10;

    AlfaYResPrevAv = 0;
    CntDiffTiltLimit = 0;

    AddTiltLimit = 2; //10;


    KpSPD = 0;

    Preas1DnCnt = Preas2DnCnt = PhasesPerRev1;
    Preas1UpCnt = Preas2UpCnt = Diametr1;



    KpSPDMustBe = KpSPDMove;
    SetKpSPD_UP();
    Unicycle = 0;
    if (Unicycle)

        CntHrnLConst = 5;

    SetTmrConst();



    TestVibroLR = 0;





    StateInd = 1;




    RdSensors();
#if !defined VECTOR
#if !defined ISOLATED
    if ((Sensor1 == 7) || (Sensor1 == 0) || Sensorless) {
        SensorlessInit(); //7777777777777777777777777777777777777777777777777777777777777777777
        SoundNum = 9;

    } else {
        if (Vector)
            VectorInit();
        else
            TrapeziumInit();
    }
#else
    if (Vector)
        VectorInit();
    else
        TrapeziumInit();
#endif
#else
    if (0)//((Sensor1==7)||(Sensor1==0)||Sensorless)
    {
        SensorlessInit(); //7777777777777777777777777777777777777777777777777777777777777777777
        SoundNum = 9;

    } else {
        if (Vector)
            VectorInit();
        else
            TrapeziumInit();
#if defined SENSORLESS_TEST
        SensorlessInit();
#endif
    }
#endif
    RdSensors();



    NullPtr = 1;
    NullPtrRot = 1;


    Forward1 = 1;
    StartingBTN = 1;
    Locked = 1;


    if (Monocycle)
        SoundNum = 1;

    

    SpeedControlPrev = SpeedControl;

#ifdef MPU6050        
    WriteMPU6050(107, 1, 0);
    HvMPU6050 = 0;

    if (!MPU6050Err) {
        MPU6050_TimeOut = 10;
        ReadMPU6050(0x1A, 3);
        while ((!HvMPU6050)&&(MPU6050_TimeOut));
        if (!MPU6050_TimeOut) {
            MPU6050Err = 5;
            CloseI2C1();
            IEC1bits.MI2C1IE = 0;
            if (Monocycle)
                CriticalError = CRERR_MPU6050;
        }
    } else
        if (Monocycle)
        CriticalError = CRERR_MPU6050;
#endif 










# if !defined TRIS_TST_PIN    
    //    if (_2WDMode)
    {
        InitPort_U3();
        UARTInit_U3();
    }
#else
        TRIS_TST_PIN=0;
#endif
        
        
    CalibrateJOYSTICK = 1;
    InitSensorsNear();
    TestU3ChangeSpd = 1;

    HighDataSpdUART=0;
    
    InitReady = 1;



}

void OSC_Init(void) {
    CLKDIVbits.PLLPOST = 0; // N1=2
#if !defined INT_FRC          
    CLKDIVbits.PLLPRE = 0; // N2=2
    // OSCTUN = 0;                     // Tune FRC oscillator, if FRC is used
    PLLFBDbits.PLLDIV = 118;
#else
    CLKDIVbits.PLLPRE = 2; // N2=2
    OSCTUN = 0; // Tune FRC oscillator, if FRC is used
    PLLFBDbits.PLLDIV = 128;
#endif
    // Disable Watch Dog Timer
    RCONbits.SWDTEN = 0;

    /*
        ACLKCON3bits.ASRCSEL=1;
        ACLKCON3bits.FRCSEL=0;
        ACLKCON3bits.SELACLK=1;


        ACLKDIV3bits.APLLDIV=0b111;
        ACLKCON3bits.APLLPRE = 1;
        ACLKCON3bits.APLLPOST = 0b110;
        ACLKCON3bits.ENAPLL = 1;
     */
}

void InitPorts(void) {

    //BLDC 1

    DS = 1;

#if !defined VECTOR
    TRIS_DS = 1;
#endif


    TRIS_PWM1_A_H = 1;
    ANSEL_PWM1_A_H = 0;

    TRIS_PWM1_A_L = 0;
    ANSEL_PWM1_A_L = 0;

    TRIS_PWM1_B_H = 0;
    ANSEL_PWM1_B_H = 0;

    TRIS_PWM1_B_L = 0;
    ANSEL_PWM1_B_L = 0;

    TRIS_PWM1_C_H = 0;
    ANSEL_PWM1_C_H = 0;

    TRIS_PWM1_C_L = 0;
    ANSEL_PWM1_C_L = 0;

    TRIS_Hall1_A = 1;
    CNEN_Hall1_A = 1;

    TRIS_Hall1_B = 1;
    CNEN_Hall1_B = 1;

    TRIS_Hall1_C = 1;
    CNEN_Hall1_C = 1;


    //BLDC 1 END


    TRIS_But1 = 1;


    TRIS_But2 = 1;
    ANSEL_But2 = 0;

    TRIS_But3 = 1;
    ANSEL_But3 = 0;

    TRIS_But4 = 1;
    ANSEL_But1 = 0;
    //CNPU_But4=1;
#if !defined REV2
    ANSEL_But4 = 0;
    TRIS_But5 = 1;
    ANSEL_But5 = 0;
#else
    CNPU_But1 = 1;
    CNPU_But2 = 1;
    CNPU_But3 = 1;
    CNPU_But4 = 1;
#endif


    TRISBuzzer = 0;
    Buzzer = 0;

#if !defined REV2
    TRISLight = 0;
    Light = 0;
#endif

    TRISHorn = 0;
#if !defined VECTORS
    Horn = 1;
#else
    //Horn=0;
    OC3R = 0;
#endif


    TRISSpd1Sensor = 1;
    TRISSpd2Sensor = 1;

    TRIS_Break1 = 1;
    TRIS_Break2 = 1;
    CNPU_Break1 = 1;
    CNPU_Break2 = 1;

    TRISRight = 0;

    TRISLeft = 0;
#if !defined VECTOR
    Right = 0;
    Left = 0;
#else
    Right = 1;
    Left = 1;
#endif



    TRIS_PAS = 1;
    ANSEL_PAS = 0;

    ANSELAbits.ANSA7 = 1;


#if defined ISOLATED
    TRIS_UBt_SCK = 0;
    TRIS_UBt_DATA = 1;
    ANSEL_UBt_SCK = 0;
    ANSEL_UBt_DATA = 0;
    UBt_SCK = 0;
#endif

    //TRIS_TST_PIN=0;
#if defined VECTORMS
    ChagerOut = 0;
    TRIS_ChagerOut = 0;
    TRIS_ChagerIn = 1;
    CNPU_ChagerIn = 1;
#endif


    TRIS_ALARM_LED = 0;
    TRIS_MODE_LED = 0;

    ALARM_LED = 0;
    MODE_LED = 0;
}

void ADC1Init(void) {

    /* Set port configuration */
    //ANSELA = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    //ANSELB = 0x012C; // Ensure AN2, AN3, AN5 and AN8 are analog
    /* Initialize ADC module */
    AD1CON1 = 0x04E4; // Enable 12-bit mode, auto-sample and auto-conversion
    AD1CON2 = 0x0408; // Sample 4 channels alternately using channel scanning
#if defined REV2
#if !defined VECTOR
#if !defined ISOLATED    
    AD1CON2bits.SMPI = 8;
#else
    AD1CON2bits.SMPI = 7;
#endif
#else
    AD1CON2bits.SMPI = 13;
#endif
    AD1CON3 = 0xff; //0x0F0F; // Sample for 15*TAD before converting
    AD1CON4 = 0x0000;
#if !defined VECTOR
#if !defined ISOLATED    
    AD1CSSH = 0b1000000010101111;
#else
    //AD1CSSH=0b0100000010001111;
    AD1CSSH = 0b1000000010001111;
#endif
#else
    AD1CSSH = 0b1100000011111111;
#endif



#else
    AD1CON2bits.SMPI = 9;
    AD1CON3 = 5; //0x0F0F; // Sample for 15*TAD before converting
    AD1CON4 = 0x0000;
    AD1CSSH = 0b1100000010101111;
#endif



#if defined VECTOR
    AD1CSSL = 0b1110000100000000;
#else
    AD1CSSL = 0b10000100000000;
#endif
    //   AD1CSSL=0b110000000000000;
    //AD1CSSH = 0x0000;
    //AD1CSSL = 0x012C; // Select AN2, AN3, AN5 and AN8 for scanning
    /* Assign MUXA inputs */
    AD1CHS0bits.CH0SA = 0; // CH0SA bits ignored for CH0 +ve input selection
    AD1CHS0bits.CH0NA = 0; // Select VREF- for CH0 -ve input


    AD1CON1bits.SSRC = 7; //
    AD1CON1bits.SSRCG = 0;

    /* Enable ADC module and provide ADC stabilization delay */
    AD1CON1bits.ADON = 1;
    IFS0bits.AD1IF = 0;
    IPC3bits.AD1IP = 3;
    IEC0bits.AD1IE = 1;

    int k;
    for (k = 0; k < 20000; k++);


    TRISFbits.TRISF13 = 0;

}

void __attribute__((interrupt, auto_psv)) _AD1Interrupt(void) {


    //   LATFbits.LATF13=!LATFbits.LATF13;
    //  LATFbits.LATF13=1;

    IFS0bits.AD1IF = 0;
#if defined REV2
#if !defined VECTOR
#if !defined ISOLATED    
    ADCThrottle = ADC1BUF0;
    Crr1 = ADC1BUF1;

    if (CntT_ADC < 64) {
        T1_ADC = T1_ADC + ADC1BUF2;
        T3_ADC = T3_ADC + ADC1BUF3;
        T4_ADC = T4_ADC + ADC1BUF4;
        T2_ADC = T2_ADC + ADC1BUF8;
        CntT_ADC++;
    }

    ADCThrottleBreak = ADC1BUF7;

    ADCThroottleZero = ADC1BUF5;

    UBT = ADC1BUF6;
#else
    if (GAZ_IMMITATOR)
        ADCThrottle = GazImm;
    else
        ADCThrottle = ADC1BUF0;
    Crr1 = ADC1BUF1;

    if (CntT_ADC < 64) {
        T1_ADC = T1_ADC + ADC1BUF2;
        T3_ADC = T3_ADC + ADC1BUF3;
        T4_ADC = T4_ADC + ADC1BUF4;
        T2_ADC = T2_ADC + ADC1BUF7;
        CntT_ADC++;
    }

    ADCThrottleBreak = ADC1BUF6;

    ADCThroottleZero = ADC1BUF5;

    //   UBT=ADC1BUF6;

#endif
#else
    if (GAZ_IMMITATOR)
        ADCThrottle = GazImm;
    else
        ADCThrottle = ADC1BUF0;
    Crr1 = ADC1BUF1;

    _5V = ADC1BUF2;
    _3V = ADC1BUF3;
    CurrA_P = ADC1BUF4;
    CurrA_N = ADC1BUF5;
    CurrC_P = ADC1BUF6;
    CurrC_N = ADC1BUF7;
    _12V = ADC1BUF8;
    UBT = ADC1BUF9;
    LightSensor = ADC1BUFA;
    ADCThrottleBreakADC = ADC1BUFB;


    if (CntT_ADC < 64) {
        T2_ADC = T2_ADC + ADC1BUFC;
        T1_ADC = T1_ADC + ADC1BUFD;

        CurrA_P_Summ = CurrA_P_Summ + CurrA_P;
        CurrA_N_Summ = CurrA_N_Summ + CurrA_N;
        CurrC_P_Summ = CurrC_P_Summ + CurrC_P;
        CurrC_N_Summ = CurrC_N_Summ + CurrC_N;



        CntT_ADC++;


    }


    //  ADCThroottleZero=ADC1BUF5;

    //   UBT=ADC1BUF6;
#endif
#else
    ADCThrottle = ADC1BUF0;
    Crr1 = ADC1BUF1;

    if (CntT_ADC < 64) {
        T1_ADC = T1_ADC + ADC1BUF2;
        T4_ADC = T4_ADC + ADC1BUF3;
        T5_ADC = T5_ADC + ADC1BUF4;
        T6_ADC = T6_ADC + ADC1BUF5;
    }

    UBT = ADC1BUF6;
#endif

    if (!BreakPressed)
        UBTNoRegen = UBT;
#if !defined REV2    
    ADCThrottleBreak = ADC1BUF7;

    if (CntT_ADC < 64) {
        T3_ADC = T3_ADC + ADC1BUF8;
        T2_ADC = T2_ADC + ADC1BUF9;
        CntT_ADC++;
    }
#endif
    /*
        if (FillCurrentMass)
        {
             if (CntPhase<MassTMPSIZE)
            {
    MassTMPPhase[CntPhase]=Curr1/10;
    MassTMPNeutral[CntPhase]=0;//PDC1/6;
    CntPhase++;
            }    
        }
     */

    /*
    if (CURRENT_PROTECTION)
    {
            Curr1_int=ZeroCurr1+1-Crr1;

        if (Curr1_int>CurrUst)
        {
            if (!SensorlessNotBEMF)    
                if (!StartCnt)
                {
                    CurrProtectSoundCnt++;
                    if (CurrProtectSoundCnt>10)
                    {
                        CurrProtectSoundCnt=0;
                        if (CurrLimitSound)
                        SoundNum=1;
                    }
                }
        PID_On=0;
        ECurr1=Curr1_int-CurrUst;
        EpCurr1=ECurr1*KpCurr;
        ECurr1Summ=ECurr1Summ+(float)ECurr1*KiCurr;
        if (ECurr1Summ>MAX_PWM)
            ECurr1Summ=MAX_PWM;

        }
        else
        {
            EpCurr1=0;
            if (ECurr1Summ>0)
            {
            ECurr1=CurrUst-Curr1_int;
            ECurr1Summ=ECurr1Summ-((float)ECurr1*KiCurr);
            if (ECurr1Summ<0)
                ECurr1Summ=0;
            }
            else
            {
                ECurr1Summ=0;
            }
        }
        PI_Curr1Res=(unsigned long int)ECurr1Summ+(unsigned long int)EpCurr1+PI_Temperature;
        if (PI_Curr1Res>MAX_PWM)
            PI_Curr1Res=MAX_PWM;

        }*/
    //LATFbits.LATF13=0;



    if (_2WDMode == 2) {
        if (!Joystick) {
            ADCThrottle = SlaveADCThrottle;
            ADCThrottleBreak = SlaveADCThrottleBreak;
        } else {
            ADCThrottle = SlaveADCThrottleBreak;
            ADCThrottleBreak = 0;
        }
    }

    if (_2WDMode == 1) {
        if (Joystick) {
            if (ChangeAxis) {
                int Tmm = ADCThrottle;
                ADCThrottle = ADCThrottleBreak;
                ADCThrottleBreak = Tmm;
            }
        }
    }

#if defined VECTOR
    if (ADCThrottle > ThrottleLevelUpOff)
        ADCThroottleZero = 0;
    else
        ADCThroottleZero = 300;
#endif


    HvADC1 = 1;

}


void SensorlessInitOld(void) {
#if defined ISOLATED
    return;
#endif

    if (SensorlessInitialized)
        return;
    SpeedControl = 0;
    SensorlessInitialized = 1;
    MAX_PWM = MAX_PWM_SENSORLESS_CONST;
    Sensorless = 1;
    Vector = 0;
    IPC22bits.U4RXIP = 5; //6;
    IPC20bits.U3RXIP = 5; //6;
    IPC2bits.T3IP = 5; //6;
    ADC2Init();
    InitPWM();
    T4_5Init();
    T6_7Init();
    CntAcqSensor = 0;
    CntBEMF = 0;
    if (!ManualStart)
        SensorlessNotBEMF = 1;
    SpeedControl = 0;
    if (ManualStart)
        SensorlessManualStartInit();
}

void T9Init(void) {
    TMR9 = 0;
    T9CON = 0x8000; //0x8030;
    PR9 = 10000; //0xffff;//500 Hz Int
    IPC13bits.T9IP = 7;
    IEC3bits.T9IE = 0;

}

void __attribute__((interrupt, auto_psv)) _T9Interrupt(void) {
    IFS3bits.T9IF = 0;
    IEC3bits.T9IE = 0;
    Nop();
    Nop();
    Nop();
    Nop();




}

void T3Init(void) {
    TMR3 = 0;
    T3CON = 0x8010;
    PR3 = 3750; //938;//2000 Hz Int          //15000;//500 Hz Int
    IPC2bits.T3IP = 5; //7;
    IEC0bits.T3IE = 1;

}

void __attribute__((interrupt, auto_psv)) _T3Interrupt(void) {
    //    unsigned char Secret1, Secret2, Chk, Check;


    IFS0bits.T3IF = 0;
    //GreenLed = !GreenLed;
#if defined BMS
    //GetBMS();
#endif

    /*T3Cnt1--;
    if (T3Cnt1)
        return;
    T3Cnt1=4;
     */
    if (MPU6050_TimeOut)
        MPU6050_TimeOut--;

#if !defined BUZZER_WITH_GENERATOR

    if (Buzzer) {
        BuzzerNoGenerator = !BuzzerNoGenerator;
    } else {
        BuzzerNoGenerator = 0;
    }


#endif



#if defined VECTOR    
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

    }

#endif


    if (Hv2WDMasterCnt) {
        Hv2WDMasterCnt--;
        if (!Hv2WDMasterCnt)
            Hv2WDMaster = 0;
    }







    if (Sensorless) {
        if ((SensorlessNotBEMF)&&(SensorlessStartNoHalls)) {
            if (SensorLessTimer)
                SensorLessTimer--;

            Vector = 0;

            //2 6 4 5 1 3


            if (!SensorLessTimer) {
                SensorLessTimer = SensorLessTimerConst;
                SensorLessStartStage++;
                if ((Alignment)&&(!ManualStart))
                    SensorLessStartStage = 0;

                if (SensorLessStartStage > 5)
                    SensorLessStartStage = 0;
                if (!DirPWM1) {
                    switch (SensorLessStartStage) {
                        case 0:
                            Sensor1 = 3;
                            break;
                        case 1:
                            Sensor1 = 1;
                            break;
                        case 2:
                            Sensor1 = 5;
                            break;
                        case 3:
                            Sensor1 = 4;
                            break;
                        case 4:
                            Sensor1 = 6;
                            break;
                        case 5:
                            Sensor1 = 2;
                            break;
                    }
                } else {
                    switch (SensorLessStartStage) {
                        case 0:
                            Sensor1 = 2;
                            break;
                        case 1:
                            Sensor1 = 6;
                            break;
                        case 2:
                            Sensor1 = 4;
                            break;
                        case 3:
                            Sensor1 = 5;
                            break;
                        case 4:
                            Sensor1 = 1;
                            break;
                        case 5:
                            Sensor1 = 3;
                            break;
                    }

                }
                //Sensor1=ChangeSensorOrder(Sensor1,SensOrder1);
                Sensor1_Prev = Sensor1;
                Phases1();
                if ((!SensorLessOnCnt)&&(ManualStart))
                    SensorlessNotBEMF = 0;

            }

        }

    }




    T3Cnt--;
    if (T3Cnt)
        return;
    T3Cnt = 4;

#if defined MPU6050
    if (MI2C1Interrupt_TimeOut) {
        MI2C1Interrupt_TimeOut--;
        if (!MI2C1Interrupt_TimeOut) {
            CloseI2C1();
            IEC1bits.MI2C1IE = 0;
            MPU6050Err = 10;
        }
    }
#endif        





    if (PWMCON1bits.FLTSTAT || PWMCON2bits.FLTSTAT || PWMCON3bits.FLTSTAT) {
        //Amplitude2=0;
        if (FLTSTATCnt) {
            FLTSTATCnt--;
            if (!FLTSTATCnt) {
                PWMCON1bits.FLTIEN = 0;
                PWMCON1bits.FLTIEN = 1;
                FCLCON1bits.FLTMOD = 0;

                PWMCON2bits.FLTIEN = 0;
                PWMCON2bits.FLTIEN = 1;
                FCLCON2bits.FLTMOD = 0;

                PWMCON3bits.FLTIEN = 0;
                PWMCON3bits.FLTIEN = 1;
                FCLCON3bits.FLTMOD = 0;

                InitPWM_Vector();



                FLTSTATCnt = FLTSTATCntConst;

            }
        } else
            FLTSTATCnt = FLTSTATCntConst;

    } else
        FLTSTATCnt = FLTSTATCntConst;





















    if (TimerCntWhenLock) {
        TimerCntWhenLock--;
    }

    if (LockTMR) {
        LockTMR--;
        if (!LockTMR) {
            SoundNum = 20;
            Locked = 1;
        }
    }



    if (Sounds) {
        if (Buzzer) {
            BuzzerOnTime--;
            if (!BuzzerOnTime) {
                BuzzerOnTime = BuzzerOnTimeConst;
                BuzzerMacroOff//Buzzer=0;
                Sounds--;
                /*if (AlarmOn)
                {
                    AccToMemALM();
                    if (HorningL)
                        HorningL=0;
                    if (HorningH)
                        HorningH=0;
                }*/
            }
        } else {
            BuzzerOffTime--;
            if (!BuzzerOffTime) {
                BuzzerOffTime = BuzzerOffTimeConst;
                //   Sounds--;
                //    {
                //       BuzzerOnEvent=4;
                BuzzerMacroOn//Buzzer=1;
                        //     }
            }
        }
    } else {
        if (BuzzerOffTime)
            BuzzerOffTime--;

        if (AlarmOn) {
            if (HorningL || HorningH)
                AccToMemALM();
            if (HorningL)
                HorningL = 0;
            if (HorningH)
                HorningH = 0;
        }
    }






    if (CntAfterActivate)
        CntAfterActivate--;


    CntSegMain--;
    if (!CntSegMain) {
        CntSegMain = 2;
        IEC1bits.OC4IE = 1;
    }




    CntMustStorageData--;
    if (!CntMustStorageData) {
        CntMustStorageData = CNTSTOR_CONST;
    }

    if (BMSDelayCnt)
        BMSDelayCnt--;


    if (CntPause)
        CntPause--;

    if (UseTmr && TmrActive) {

        if (TimerCnt <= TimerConst) {
            TimerCnt++;

            if (TimerCnt >= TimerConst) {
                SoundTmr = 1;
            }
        }
    }

    if (CntOnDelay)
        CntOnDelay--;

    IndCnt--;
    if (!IndCnt) {
        OnIndFl = !OnIndFl;
        IndCnt = 125;
    }


    if (CntHorningL) {
        CntHorningL--;
        if (!CntHorningL)
            CntHrnL = 0;
    }

    if (TimeOutHC05)
        TimeOutHC05--;

    if (CntU4TimeOut) {
        CntU4TimeOut--;
        if (!CntU4TimeOut)
            GettingPacketU4_FL = 0;
    }

    MyTimeOut--;
    if (TiltControlCnt)
        TiltControlCnt--;
    else
        Nop();

    if (StartingMoveCnt) {
        StartingMoveCnt--;
        if (!StartingMoveCnt) {
            StartingMove = 1;

        }
    }

    if (SensorLessOnCnt)
        SensorLessOnCnt--;


    if (TemperatureCnt) {
        TemperatureCnt = 750;
        TemperatureFl = 0;
    }


    /*
            if (OdometrCnt)
                OdometrCnt--;
            else
            {
                if (!OdometrErased)
                {
                    WriteStat_FLASH(0);
                    EraseSector_FLASH(4096);
                    WriteStat_FLASH(0x3c);

                    OdometrErased=1;
                }
            }

     */




    if (TiltZad < TiltZadTmp) {
        TiltZad = TiltZad + 0.01; //TiltChng;
        if (TiltZad >= TiltZadTmp) {
            if (TiltZadTmp == 0)
                TiltZad = 0;
        }
    } else {
        TiltZad = TiltZad - 0.01; //TiltChng;
        if (TiltZad <= TiltZadTmp) {
            if (TiltZadTmp == 0)
                TiltZad = 0;
        }
    }

    //   }


    if (MeasuringSpd1) {
        _1sCnt1++;
        if (_1sCnt1 >= _1sCntConst) {
            Spd1Res = Spd1Cnt;
            Spd1Cnt = 0;
            HvSpd1 = 1;
            HvSpd1_PID = 1;
            MeasuringSpd1 = 0;
            _1sCnt1 = 0;
        }
    } else {
        _1sCnt1++;
        if (_1sCnt1 >= _1sCntConst) {
            _1sCnt1 = 0;
            Spd1Res = 0;
            HvSpd1_PID = 1;
            HvSpd1 = 1;
        }
    }


    CntRecAcc--;
    if (!CntRecAcc) {
        CntRecAcc = 2;
#if !defined LSM6DS33
#if !defined MPU6050     
#if !defined VECTOR_MPU_6000
        Acc_txBuf[0] = 0x27;
        Acc_txBuf[0] = Acc_txBuf[0] | 0xc0; //Addr | autoincrement | read
        TxRxSPI_ACC(0x10);
#endif
#if defined VECTOR            
        if (MPU6000_Initialized) {
            Gyro_txBuf[0] = 0x80 | 0x3b;
            TxRxSPI_GYRO(15);
        }
#else

        if (!TemperatureFl) {
            Gyro_txBuf[0] = 0x26 | 0xc0; //Addr | autoincrement  //0xf|0xc0;//
            /*Gyro_rxBuf[0]=0;
            Gyro_rxBuf[1]=0;
            Gyro_rxBuf[2]=0;
            Gyro_rxBuf[3]=0;
            Gyro_rxBuf[4]=0;
            Gyro_rxBuf[5]=0;
            Gyro_rxBuf[6]=0;
            Gyro_rxBuf[7]=0;
            Gyro_rxBuf[8]=0;
            Gyro_rxBuf[9]=0;*/
            TxRxSPI_GYRO(9);
        } else {
            Gyro_txBuf[0] = 0x26 | 0xc0; //Addr | autoincrement
            Gyro_rxBuf[0] = 0;
            Gyro_rxBuf[1] = 0;
            Gyro_rxBuf[2] = 0;
            Gyro_rxBuf[3] = 0;
            Gyro_rxBuf[4] = 0;
            Gyro_rxBuf[5] = 0;
            Gyro_rxBuf[6] = 0;
            Gyro_rxBuf[7] = 0;
            Gyro_rxBuf[8] = 0;
            Gyro_rxBuf[9] = 0;
            TxRxSPI_GYRO(4);
        }
#endif
#else
        if (HvMPU6050) {
            HvMPU6050 = 0;
            //if (!TmpFlg)
            if (InitReady)
                ReadMPU6050(0x3b, 14);
        }
#endif

#else
        if (LSM6DS33_Initialized) {
            Gyro_txBuf[0] = 0x20 | 0x80;
            TxRxSPI_GYRO(15);

            //HvGyroData=1;
            //HvAccData=1;
            //IEC1bits.OC4IE=1;
        }

#endif

    }
    /*
            CntRecGyro--;
            if (!CntRecGyro)
            {
                CntRecGyro=2;
                Gyro_txBuf[0] = 0x27|0xc0;//Addr | autoincrement
                TxRxSPI_GYRO(8);
            }

     */
    /*
            if (TiltTimoutCnt)
            TiltTimoutCnt--;

               if ((!TiltTimoutCnt)&&(!Unicycle))
               {
                //ErrorCode=1;

                   Stopping=1;

                if (!ErrorTiltFl)
                {
                WriteErr_Fl=1;
                ErrorTiltFl=1;
                }
               }*/
    /*if (!DirectControlMotor)
    {
                    if ((ErrorCode)||(NoBalance))
            {
               if (!AlarmOn)
               {
                DS=1;
               }
               else
               {
                DS=0;
               }

                 ChangePWM1(0);
             

            }
    }*/
#if !defined VECTOR
#if defined ISOLATED

    CNT_U--;
    if (!CNT_U) {
        CNT_U = 1;
        if (!TakingPacketUbat) {
            UBt_SCK = 0;
            TakingPacketUbat = 1;
            CNT_U_Bits = 0;
        } else {
            if (!UBt_SCK)
                UBt_SCK = 1;
            else {
                if (UBt_DATA)
                    UBat = UBat | 1;
                else
                    UBat = UBat & 0xfffffffe;
                UBt_SCK = 0;
                CNT_U_Bits++;
                if (CNT_U_Bits >= 32) {
                    CNT_U_Bits = 0;
                    TakingPacketUbat = 0;
                    CNT_U = 500;
                    UBt_SCK = 1;
                    Secret2 = (unsigned char) UBat;
                    Secret1 = (unsigned char) (UBat >> 24);
                    UBT = (unsigned char) (UBat >> 16);
                    HvUBT = 1;
                    Chk = (unsigned char) (UBat >> 8);

                    Check = UBT + Secret1 + Secret2;
                    Check = ~Check;

                    Secret1 = Secret1 - UBT;
                    Secret2 = Secret2 + UBT;


                    //          UBT=50;


                    if (Check == Chk) {
                        HvPacketUBat = 1;
#if defined U_2_2k
                        UBT = UBT * 143;
                        UBT = UBT / 100;
#endif
                    } else
                        HvPacketUBat = 0;

                    Nop();
                    Nop();
                    Nop();

                    if ((Secret1 != 0x15) || (Secret2 != 0x9a)) {
#if !defined NO_UBT
                        //                   CriticalError=CRERR_SECRET_UBT;
#endif
                        Nop();
                        Nop();
                        Nop();

                    } else {
                        Nop();
                        Nop();
                        Nop();
                    }


                } else {
                    UBat = UBat << 1;
                }


            }

        }
    }
#endif
#endif


}






void ChangePWM1(unsigned int PWM) {
    unsigned int DiffPWM;
    if (ChagerViaMotor) {
        SetPWM_ChagerViaMotor();
        return;
    }

    PWM_Sensorless=PWM;
    

    if (!Monocycle) {
        if (PWMChanged && (!BreakPressed)) {
            if (PWMPrev > PWM)
                DiffPWM = PWMPrev - PWM;
            else
                DiffPWM = PWM - PWMPrev;

            if (DiffPWM > PWMChangedThreshold)
                CriticalError = CRERR_PWM_CHANGED_HIGH;

            PWMPrev = PWM;
        }
    }


    if ((Vector)&&(!BreakPressed)) {
        //        IEC3bits.T8IE = 0;
        Amplitude1 = PWM;
        if (IFS3bits.T8IF)
            Phase1Period1Up = TMR8;
        IEC3bits.T8IE = 1;
        return;
    }
    //#if !defined TEST_PWM_KEYS
    if (!TEST_PWM_KEYS) {
        if ((CURRENT_PROTECTION)&&(!BreakPressed)) {
            if (PWM > (unsigned int) PI_Curr1Res)
                PWM = PWM - (unsigned int) PI_Curr1Res;
            else
                PWM = 0;
        }
    }
    //#endif

    PhasePWM = PWM;



    if (PWM < DEADTIME_GLUK) {
        DTR1 = DTR2 = DTR3 = DEADTIME * 2; //DTRx Registers are ignored in this mode
        ALTDTR1 = ALTDTR2 = ALTDTR3 = DEADTIME * 2;
        PWM = PWM + DEADTIME + Khard;
    } else {
        DTR1 = DTR2 = DTR3 = DEADTIME; //DTRx Registers are ignored in this mode
        ALTDTR1 = ALTDTR2 = ALTDTR3 = DEADTIME;
        PWM = PWM + DEADTIME_2 + Khard;

    }

    PDC1 = PWM;
    PDC2 = PWM;
    PDC3 = PWM;

    PWM1Show = PWM;

}



void TrmSteer(void) {
    unsigned char N;

    if (!MustTrm_U3)
        return;
    MustTrm_U3 = 0;
    if (OnTransmitt_U3)
        return;

    N = TrmMass_U3[2];

    OnTransmitt_U3 = 1;
    CntTrmSteer = 1;
    CntTrmSteer_N = N + 4;

    U3TXREG = TrmMass_U3[0];
    IEC5bits.U3TXIE = 1;


}



unsigned char CalcCheckSumm(unsigned int N, unsigned char *Mass) {
    unsigned int Summ = 0, j, n = N;

    for (j = 0; j < n; j++)
        Summ = Summ + Mass[j];

    Summ = ~Summ;

    return (unsigned char) Summ;

}

void ReceiveUDP(void) {
    int *Ptr;
    unsigned char Cmmd, Cm;
    if (Hv_HC05) {
        if (!HvPacketU4_FL)
            return;
        HvPacketU4_FL = 0;
        Cmmd = RecBytes[1];
    }
/*#if defined HighDataSpdUART
    Locked = 0;
#endif
*/
    if (Locked) {
        if (Cmmd != 113)
            Nop();

        switch (Cmmd) {
            case 14:
            {
                Nop();
                Nop();
                Nop();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 113:
            {
                MustSendDataPacket = 1;
                break;
            }
            case 114:
            {
                NoAutoTrm = 1;
                break;
            }


            case 146:
            {
                if ((RecBytes[2] > 0)&&(RecBytes[2] < 4)) {
                    Profile = RecBytes[2];
                    MassToOptionsProfile();
                    OptionsToMass();
                    MustTrmFlashMass = 1;

                    switch (Profile) {
                        case 1:
                            SoundNum = 15;
                            break;
                        case 2:
                            SoundNum = 16;
                            break;
                        case 3:
                            SoundNum = 17;
                            break;
                    }
                }

                break;
            }





            case 243:
            {
                if ((RecBytes[2] == 0x37)&&(RecBytes[3] == 0xac)&&(RecBytes[4] == 0x2b)&&(RecBytes[5] == 0x33)&&(RecBytes[6] == 0xf1)&&(RecBytes[7] == 0x91)&&(RecBytes[8] == 0x7a)&&(RecBytes[9] == 0xb0)&&(RecBytes[10] == 0xec)&&(RecBytes[11] == 0x46)&&(RecBytes[12] == 0x10)&&(RecBytes[13] == 0xaa)) {
                    //PinCodeMassOptionsUnlock  StringPINLenghtOptionsUnlock
#if !defined BLE
                    LockTMR = 450000;
                    SoundNum = 19;
                    Locked = 0;

#else
                    LockTMR = 450000;


                    if (!StringPINLenghtOptions)
                        Locked = 0;
                    else {
                        Locked = 0;
                        int i;
                        for (i = 0; i < StringPINLenghtOptions; i++) {
                            if (PinCodeMassOptions[i] != PinCodeMassOptionsUnlock[i])
                                Locked = 1;
                        }
                        if (StringPINLenghtOptions != StringPINLenghtOptionsUnlock)
                            Locked = 1;
                        StringPINLenghtOptionsUnlock = 0;
                    }
                    if (!Locked)
                        SoundNum = 19;
                    else
                        SoundNum = 9;
#endif
                }
                break;
            }
            case 244:
            {
                OptionsToMass();
                MustTrmFlashMass = 1;
                TimerCntWhenLock = 700;
                break;
            }

            case 254:
            {
                Cm = RecBytes[2];

                switch (Cm) {
                    case 1:
                        break;

                    case 64:
                    {
                        unsigned char p;

                        for (p = 0; p < (RecBytes[0] - 2); p++)
                            PinCodeMassOptionsUnlock[p] = RecBytes[p + 3];
                        StringPINLenghtOptionsUnlock = p;
                        break;
                    }
                    case 65:
                        if (ResetPassWordCnt && (Sensor1_Prev == 1)) {
                            StringPINLenghtOptions = 0;
                            Locked = 0;
                            SoundNum = 19;
                        } else
                            SoundNum = 9;
                        break;


                    case 91:
                    {
                        SoundNum = 12;
                        LightMode = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 208:
                    {
                        HighDataSpdUART = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 209:
                    {
                        HighDataSpdUART = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }


                    default:
                    {
                        if (!TimerCntWhenLock) {
                            SendUnlockMSG = 1;
                            SoundNum = 9;
                        }
                        break;
                    }
                }
                break;
            }

            default:
            {
                if (!TimerCntWhenLock) {
                    SendUnlockMSG = 1;
                    SoundNum = 9;
                }
                break;
            }
        }
    } else {
        if ((Cmmd != 14)&&(Cmmd != 113))
            LockTMR = 450000;

        switch (Cmmd) {
            case 1:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                V_MIN_Pre_OFF = (float) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 2:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpNoMan = (float) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 3:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KdNoMan = Tm;
                KdNoMan = KdNoMan * 10;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 4:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KiNoMan = Tm;
                KiNoMan = KiNoMan / 100;
                OptionsToMass();
                MustTrmFlashMass = 1;
                ESumm = 0;
                break;
            }
            case 5:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpSPDMove = Tm;
                if (!Stopping) {
                    KpSPDMustBe = KpSPDMove;
                    SetKpSPD_UP();
                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 6:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KdSPD = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 7:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KiSPD = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                ESummSpd = 0;
                break;
            }
            case 8:
            {
                Odometr++;
                WriteOdometrNew();
                SoundNum = 1;
                SendPhase = 1;
                break;
            }
            case 9:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorlessCurrUst = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 10:
            {
                Ptr = (int *) &RecBytes[2];
                //            CntUDPTrmConst=*Ptr;
                break;
            }
            case 11:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                AngleLimitMove = Tm;
                if (!Stopping) {
                    AngleLimitMustBe = AngleLimitMove;
                    SetAngleLimit_UP();
                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 12:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SenosrlessPWM1_1Const = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 13:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KGYRO = Tm;
                KGYRO = KGYRO / 1000;
                KACC = 1 - KGYRO;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 14:
            {
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 15:
            {

                OptionsToMass();



                unsigned char ts, cnt = 0;
                do {

                    ts = 1;
                    WriteOptions();
                    ReadOptions1();
                    unsigned int g;
                    for (g = 0; g<sizeof (FlashMass); g++) {
                        if (FlashMass[g] != FlashMass1[g])
                            ts = 0;
                    }
                    for (g = 0; g<sizeof (ProfileMass); g++) {
                        if (ProfileMass[g] != ProfileMass1[g])
                            ts = 0;
                    }
                    if (!ts)
                        cnt++;

                } while ((!ts)&&(cnt < 10));
                if (cnt < 10) {
                    SoundNum = 1;
                } else {
                    SoundNum = 9;
                }

                if (cnt != 0)
                    Nop();

                MustTrmFlashMass = 1;
                break;
            }

            case 16:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorLessCurrLimit = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (Sensorless) {
                    CurrLimit = SensorLessCurrLimit;
                    ChangeCVR();
                }

                break;
            }
            case 17:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                V_MIN_Sound = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 18:
            {
                //Ptr=(int *)&RecBytes[2];
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];

                KpKpSpd = (float) Tm;
                KpKpSpd = KpKpSpd / 20;

                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 19:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                V_min_OverV = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 20:
            {

                if ((!Lock)&&(!Spd1ResPlus)) {
                    SoundNum = 1;
                    Lock = 1;
                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 21:
            {
                CntSamples = 0;
                TiltYSumm = 0;
                ESumm = 0;
                CntPhase = 0;
                HallErrCnt = 0;
                Phase1Period1Up = 0;
                Phase1Period1Show = 0;
                AccYFlSpd = AccXFlShow = AccYFlShow = AccZFlShow = 0;
                break;
            }
            case 22:
            {
                if (DirectControlMotor) {
                    //Sensor1=4;
                    Nop();
                    Nop();
                    Nop();
                    Phases1();
                    Sensor1_Prev = Sensor1;


                    if (!Vector) {
                        PWM1 = RecBytes[3];
                        PWM1 = PWM1 << 8;
                        PWM1 = PWM1 + RecBytes[2];
                        DIRPWM1 = PWM1;
                        if (DIRPWM1 < 50)
                            RecOdometrFl = 1;
                    } else {
                        Amplitude1 = RecBytes[3];
                        Amplitude1 = Amplitude1 << 8;
                        Amplitude1 = Amplitude1 + RecBytes[2];
                        DIRPWM1 = Amplitude1;
                        if (DIRPWM1 < 50)
                            RecOdometrFl = 1;

                        //       Amplitude2=Amplitude1;

                    }
                    if (DIRPWM1 > 1000)
                        CntPhase = 0;

                    if (DS) {
                        DS = 0;
                        RdSensors();
                    }



                } else {
                    DIRPWM1_TstKeys = RecBytes[3];
                    DIRPWM1_TstKeys = DIRPWM1_TstKeys << 8;
                    DIRPWM1_TstKeys = DIRPWM1_TstKeys + RecBytes[2];

                    Phases1();

                }


                break;
            }
            case 23:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                MAX_PWM_MEM = Tm;
                if (MAX_PWM_MEM > 100)
                    MAX_PWM_MEM = 100;
                MAX_PWM_MustBe = MAX_PWM_MEM;
                //MAX_PWM=(MAX_PWM_CONST/100)*MAX_PWM_MEM;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 24:
            {
                AutoPID = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 25:
            {
                AutoPID = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 26:
            {
                if (Lock) {
                    Lock = 0;
                    //BreakPressed=0;
                    SoundNum = 7;
                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 27:
            {
                CalibrateAcc = 1;
                break;
            }


            case 28:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                MaxSpeed = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 29:
            {
                if ((But1Func == 4) || (But1Func == 5)) {
                    ProfileMass[13 + 0] = 0;
                    ProfileMass[13 + SIZE_OF_PROFILE] = 0;
                    ProfileMass[13 + (SIZE_OF_PROFILE * 2)] = 0;
                }
                But1Func = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 30:
            {
                PhasePERMASS = RecBytes[2];
                PhasePERMASS_SHFT = RecBytes[3];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 31:
            {
                HallDelayMem1_F = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 32:
            {
                HallDelayMem1_B = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 33:
            {
                if ((But2Func == 4) || (But2Func == 5)) {
                    ProfileMass[14 + 0] = 0;
                    ProfileMass[14 + SIZE_OF_PROFILE] = 0;
                    ProfileMass[14 + (SIZE_OF_PROFILE * 2)] = 0;
                }
                But2Func = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 34:
            {
                //ChangeCurrStateMachine=0;
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CurrLimitWork = Tm;

                if ((!Sensorless)&&(!CurrDecrease))
                    CurrLimit = CurrLimitWork;
                OptionsToMass();
                MustTrmFlashMass = 1;
                ChangeCVR();
                break;
            }

            case 35:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SpeedLimit1 = Tm;


                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 36:
            {
                DirectControlMotor = 1;

                DS = 1;

                DIRPWM1 = 0;


                //                                ChangePWM1(0);


                Sensor1_Prev = Sensor1;
                Phases1();

                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 37:
            {

                DirectControlMotor = 0;



                if (DS) {
                    DS = 0;
                    RdSensors();
                }




                NullPtr = 1;
                NullPtrRot = 1;

                if (Monocycle) {
                    ESumm = 0;
                    NoBalance = 1;
                    DS = 1;
                }



                NoBalanceCode = 3;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 38:
            {
                CalibrateGyro = 1;
                break;
            }

            case 39:
            {
                Theta1Zero = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 40:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                UBatLow = Tm;
#if !defined VECTOR
#if !defined ISOLATED                               
                float UBtFl = (float) UBatLow * (float) 38.388;
                UBtLim1 = (unsigned int) UBtFl;
                UBtLim2 = UBtLim1 + 115;
#else
                float UBtFl = (float) UBatLow / (float) 0.4167965;
                UBtLim1 = (unsigned int) UBtFl;
                UBtLim2 = UBtLim1 + 7;
#endif
#else
                float UBtFl = (float) UBatLow * (float) 38.388;
                UBtLim1 = (unsigned int) UBtFl;
                UBtLim2 = UBtLim1 + 115;
#endif
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 41:
            {
                Odometr = 0;
                PhasesCnt2 = 0;
                SendPhase = 1;
                RecOdometrFl = 1;
                break;
            }

            case 42:
            {
                Beep_10m = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 43:
            {
                Beep_10m = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 44:
            {
                Theta2Zero = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 45:
            {
                if (!Sensorless) {
                    VectorMem = 1;
                    Vector = 1;
                    RdSensors();
                    Amplitude1 = PDC1;
                    Amplitude2 = PDC5;
                    VectorInit();
                }
                OptionsToMass();
                MustTrmFlashMass = 1;

                break;
            }

            case 46:
            {
                VectorMem = 0;
                Vector = 0;
                if (!Sensorless) {
                    RdSensors();
                    TrapeziumInit();
                    PDC1 = Amplitude1;
                    PDC2 = Amplitude1;
                    PDC3 = Amplitude1;
                }
                OptionsToMass();
                MustTrmFlashMass = 1;


                break;
            }

            case 47:
            {
                SpeedLimit3 = RecBytes[2];

                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 48:
            {
                break;
            }

            case 49:
            {
                SendPhase = 1;
                MustTrmErrors = 1;
                break;
            }



            case 50:
            {
                AnalogBreak = 1;
                SmoothBreak = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 51:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpMax = (float) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 52:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                V_MIN_OFF = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;


            }

            case 53:
            {
                SpdKpMax = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 54:
            {
                MustTrmPacketHC05_FL = 1;
                break;
            }

            case 55:
            {
                AnalogBreak = 0;
                BothBreaks = 0;
                SmoothBreak = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 56:
            {
                if ((But3Func == 4) || (But3Func == 5)) {
                    ProfileMass[15 + 0] = 0;
                    ProfileMass[15 + SIZE_OF_PROFILE] = 0;
                    ProfileMass[15 + (SIZE_OF_PROFILE * 2)] = 0;
                }
                But3Func = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 57:
            {
                if ((But4Func == 4) || (But4Func == 5)) {
                    ProfileMass[16 + 0] = 0;
                    ProfileMass[16 + SIZE_OF_PROFILE] = 0;
                    ProfileMass[16 + (SIZE_OF_PROFILE * 2)] = 0;
                }
                But4Func = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 58:
            {
                MAX_PWM_Revers = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 59:
            {
                MaxSpdRevers = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 60:
            {
                ErrOptions = 0;
                ErrorCode = 0;
                NoBalanceCode = 0;
                MainTiltNumErr = 0;
                SteerTiltNumErr = 0;
                EEPROM_CHK_ERR = 0;
                //EEPROM_Limit_ERR=0;
                break;
            }

            case 61:
            {
                WriteErr_Fl = 1;
                break;
            }
            case 62:
            {
                break;
            }

            case 63:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                TemperatureMaxOUT_H = Tm;
                TemperatureMaxOUT_H = TemperatureMaxOUT_H / 10;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 64:
            {
                break;
            }
            case 65:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpWheelingMem = (float) Tm;
                KpMustBe = KpWheelingMem;
                SetKpMustBe_UP();

                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 66:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KiWheelingMem = Tm;
                KiWheelingMem = KiWheelingMem / 1000;
                KiMustBe = KiWheelingMem;
                SetKi_UP();

                OptionsToMass();
                MustTrmFlashMass = 1;
                ESumm = 0;
                break;
            }

            case 67:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpTemperOUT = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 68:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                TiltZadWheeling = (float) Tm;
                TiltZadWheeling = TiltZadWheeling / 10;
                TiltZadTmp = TiltZadWheeling;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 69:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                AutoPID_On_CntConst = (float) Tm;
                AutoPID_On_CntConst = AutoPID_On_CntConst * 250;
                OptionsToMass();
                MustTrmFlashMass = 1;


                break;
            }

            case 70:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                UBatHiMem = Tm;
                UBatHi = (unsigned int) ((float) UBatHiMem * (float) 38.388);
#if !defined VECTOR
#if !defined ISOLATED
                UBatHi = (unsigned int) ((float) UBatHiMem * (float) 38.388);
#else
                UBatHi = (unsigned int) ((float) UBatHiMem / (float) 0.4167965);
#endif
#else
                UBatHi = (unsigned int) ((float) UBatHiMem * (float) 38.388);
#endif





                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 71:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KiTemperIN = (float) Tm;
                KiTemperIN = KiTemperIN / 100;
                ETemperINSumm = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }



            case 72:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KiTemperOUT = (float) Tm;
                KiTemperOUT = KiTemperOUT / 100;
                ETemperOUTSumm = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 73:
            {
                Profile = 1;
                MassToOptionsProfile();
                OptionsToMass();
                CopyProfiles();
                MassToOptions();
                OptionsToMass();
                MustTrmFlashMass = 1;

                break;
            }

            case 74:
            {
                SensorTSTKeys = RecBytes[2];
                break;
            }
            case 75:
            {
                break;
            }

            case 76:
            {
                ZeroThroottle = 1;
                break;
            }

            case 77:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpRotOneTwoLeg = (float) Tm;
                KpRotOneTwoLeg = KpRotOneTwoLeg / 100;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 78:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KiRotOneTwoLeg = (float) Tm;
                KiRotOneTwoLeg = KiRotOneTwoLeg / 10000;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }



            case 79:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                Diametr1 = Tm;
                CmImp1_t = (float) Diametr1 * 0.314159 / (float) PhasesPerRev1;
                ImpToKmH1_t = CmImp1_t * 0.36;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 80:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                PhasesPerRev1 = Tm;
                CmImp1_t = (float) Diametr1 * 0.314159 / (float) PhasesPerRev1;
                ImpToKmH1_t = CmImp1_t * 0.36;

                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 81:
            {
                ZeroThroottle = 0;
                break;
            }

            case 82:
            {
                AutoPID_On_PWM = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 83:
            {
                AutoPID_On_Speed = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }



            case 84:
            {
                StrongModePID = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 85:
            {
                StrongModePID = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 86:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                StartRotFreshmanL = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 87:
            {
                break;
            }

            case 88:
            {
                break;
            }

            case 89:
            {
                SmoothBreak = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 90:
            {
                SmoothBreak = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 91:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CurrUstSpd0 = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 92:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CurrPhaseLimitSpd0 = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 93:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CurrLimitSpd0 = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 94:
            {
                MaxAngleStopBreak = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 95:
            {
                MustTrmFlashMassForSaveOptPC = 1;
                break;
            }
            case 96:
            {
                MustTrmProfileMass = 1;
                break;
            }

            case 97:
            {
                DefaultOptions();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 98:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                BeepPauseConstAlm = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 99:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                BzOnCntSeriaConstAlm = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 100:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CntSingleBeepAlm = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 101:
            {
                DiffAlfaConstL = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 102:
            {
                DiffAlfaConstH = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 103:
            {
                NameRBW = 1;
                SpeedRBW = 0;
                Robowell = 1;

                break;
            }

            case 104:
            {
                NameRBW = 0;
                SpeedRBW = 1;
                Robowell = 1;

                break;
            }
            case 105:
            {
                NameRBW = 1;
                SpeedRBW = 0;
                GetRobowell = 1;
                break;
            }

            case 106:
            {
                NameRBW = 0;
                SpeedRBW = 1;
                GetRobowell = 1;
                break;
            }

            case 107:
            {
                Calibrating = 1;
                break;
            }

            case 108:
            {
                ClearCurrentAH = 1;
                break;
            }

            case 109:
            {
                _3psnSwitchBtNotPressed = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 110:
            {
                _3psnSwitchBt3 = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 111:
            {
                _3psnSwitchBt4 = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 112:
            {
                int Tm;

                for (Tm = 0; Tm<sizeof (FlashMass); Tm++)
                    FlashMass[Tm] = RecBytes[Tm + 4];
                FlashMass[208] = SensOrder1;
                MassToOptions();
                MassToOptionsProfile();
                MustTrmCmdOk = 1;
                break;
            }

            case 113:
            {
                MustSendDataPacket = 1;
                break;
            }
            case 114:
            {
                NoAutoTrm = 1;
                break;
            }
            case 115:
            {
                NoAutoTrm = 0;
                break;
            }
            case 116:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                Timer1Mem = (unsigned int) Tm;
                SetTmrConst();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 117:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                Timer2Mem = (unsigned int) Tm;
                SetTmrConst();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 118:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                UseTmr = (unsigned int) Tm;
                TimerCnt = 0;
                SetTmrConst();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 119:
            {
                TestVibro = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 120:
            {
                TestVibro = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 121:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SerNumber = (unsigned int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 122:
            {
                But5Func = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 123:
            {
                break;
            }

            case 124:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                StartRotOneTwoLeg_1 = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 125:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorlessCntAlignConst = (int) Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;

                break;
            }

            case 126:
            {
                break;
            }

            case 127:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KTemperatureSPDControl = (float) Tm;
                KTemperatureSPDControl = KTemperatureSPDControl / 1000;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 128:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                TemperatureMaxIN_H = Tm;
                TemperatureMaxIN_H = TemperatureMaxIN_H / 10;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 129:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorlessSpdChngCntConst = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;

                break;
            }
            case 130:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorLessTimerConst2 = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 131:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SenosrlessPWM1_2Const = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 132:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorLessTimerConstMin = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 133:
            {
                SensorllessSpdThreshold = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 134:
            {
                Tmprt1 = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 135:
            {
                Tmprt1 = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 136:
            {
                Tmprt2 = 1;
                break;
            }
            case 137:
            {
                Tmprt2 = 0;
                break;
            }
            case 138:
            {
                Tmprt3 = 1;
                break;
            }
            case 139:
            {
                Tmprt3 = 0;
                break;
            }
            case 140:
            {
                Tmprt4 = 1;
                break;
            }
            case 141:
            {
                Tmprt4 = 0;
                break;
            }


            case 142:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                TemperatureMaxOUT = Tm;
                TemperatureMaxOUT = TemperatureMaxOUT / 10;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 143:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                TemperatureMaxIN = Tm;
                TemperatureMaxIN = TemperatureMaxIN / 10;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 144:
            {
                TemperatureTYPE = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 145:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpTemperIN = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 146:
            {
                if ((RecBytes[2] > 0)&&(RecBytes[2] < 4)) {
                    Profile = RecBytes[2];
                    MassToOptionsProfile();
                    OptionsToMass();
                    MustTrmFlashMass = 1;

                    switch (Profile) {
                        case 1:
                            SoundNum = 15;
                            break;
                        case 2:
                            SoundNum = 16;
                            break;
                        case 3:
                            SoundNum = 17;
                            break;
                    }
                }

                break;
            }





                ////////////////  BMS KEYS HERE MUST BE


            case 161:
            {
                unsigned int Tm;
                for (Tm = 0; Tm<sizeof (ProfileMass); Tm++)
                    ProfileMass[Tm] = RecBytes[Tm + 4];
                MassToOptionsProfile();
                MustTrmCmdOk2 = 1;
                MustTrmFlashMass = 1;
                break;
            }
            case 162:
            {

                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                BreakThresholdDn = Tm;
                if (BreakThresholdDn >= BreakThresholdUp) {
                    if (BreakThresholdUp > 0)
                        BreakThresholdDn = BreakThresholdUp - 1;
                    else {
                        BreakThresholdDn = 0;
                        BreakThresholdUp = 1;
                    }

                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;


            }
            case 163:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                MAH = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 164:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorThresholdDn = Tm;
                if (SensorThresholdDn >= SensorThresholdUp) {
                    if (SensorThresholdUp > 0)
                        SensorThresholdDn = SensorThresholdUp - 1;
                    else {
                        SensorThresholdDn = 0;
                        SensorThresholdUp = 1;
                    }

                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 165:
            {
                ManualStart = 1;
                SensorlessManualStartInit();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 166:
            {
                ManualStart = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 167:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                Cmd2BMS = Tm;
                Cmd2BMS = Cmd2BMS << 5;
                Cmd2BMS = Cmd2BMS | ((unsigned char) 0x9);
                Cmd2BMS = Cmd2BMS << 3;
                break;
            }

            case 168:
            {
                Cmd2BMS = ((unsigned char) 0xa) << 3;
                break;
            }

            case 169:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                Cmd3BMS = Tm;
                Cmd3BMS = Cmd3BMS << 5;
                Cmd3BMS = Cmd3BMS | ((unsigned char) 0x9);
                Cmd3BMS = Cmd3BMS << 3;
                break;
            }

            case 170:
            {
                Cmd3BMS = ((unsigned char) 0xa) << 3;
                break;
            }
            case 171:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                Cmd4BMS = Tm;
                Cmd4BMS = Cmd4BMS << 5;
                Cmd4BMS = Cmd4BMS | ((unsigned char) 0x9);
                Cmd4BMS = Cmd4BMS << 3;
                break;
            }

            case 172:
            {
                Cmd4BMS = ((unsigned char) 0xa) << 3;
                break;
            }

            case 173:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                TiltZadState5 = (float) Tm;
                TiltZadState5 = TiltZadState5 / 10;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }



            case 174:
            {

                SpdRstSpeedLim = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 175:
            {
                SpeedControl = 0;
                PID_On = 0;
                ECurr1Summ = 0;
                CurrentControlOnly = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 176:
            {
                if (!Sensorless) {
                    SpeedControl = 1;
                    EPID_Res_Tek = 0;
                    ECurr1Summ = 0;
                    CurrentControlOnly = 0;
                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 177:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                XLimit = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 178:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                YLimit = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 179:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                BreakThresholdUp = Tm;
                if (BreakThresholdUp <= BreakThresholdDn) {
                    if (BreakThresholdDn < 4095) {
                        BreakThresholdUp = BreakThresholdDn + 1;
                    } else {
                        BreakThresholdUp = 4095;
                        BreakThresholdDn = 4094;
                    }
                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 180:
            {
                Monocycle = 1;
                //MAX_PWM_CONST=MAX_PWM_CONST_MONOCYCLE;
                ESumm = 0;
                NoBalance = 1;
                TiltZadAddMustBe = 0;
                if (Vector)
                    VectorInit();
                else
                    TrapeziumInit();
                break;
            }
            case 181:
            {
                Monocycle = 0;
                StrongMode = 0;
                LeftTurn = 0;
                ESumm = 0;
                RightTurn = 0;
                StopLights = 0;
                TiltZadAddMustBe = 0;
                if (Vector)
                    VectorInit();
                else
                    TrapeziumInit();
                break;
            }
            case 182:
            {
                BreakButtonMonocycle = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 183:
            {
                SpeedLimitSt4 = RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 184:
            {
                Distance = 0;
                RecOdometrFl = 1;
                break;
            }

            case 185:
            {
                TestVibroLR = 1;
                break;
            }
            case 186:
            {
                TestVibroLR = 0;
                break;
            }
            case 187:
            {
                CalibrHalls = 1;
                break;
            }
            case 188:
            {
                CalibrHalls = 0;
                break;
            }
            case 189:
            {
                BreakButtonMonocycle = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 190:
            {
                MonoStopDirection = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 191:
            {
                DirPWM1 = 0;
                DirPWM1Mem = DirPWM1;
                RdSensors();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 192:
            {
                DirPWM1 = 1;
                DirPWM1Mem = DirPWM1;
                RdSensors();
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 193:
            {
                MaxSpd = RecBytes[2];
                MaxSpdCoeff = (int) ((((float) MAX_PWM) * ImpToKmH1_t) / ((float) MaxSpd / ImpToKmH1_t));
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 194:
            {
                DirBalance = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 195:
            {
                DirBalance = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 196:
            {
                SensorlessNotBEMF = 1;
                SensorlessStartNoHalls = 1;
                break;
            }

            case 197:
            {
                MonoStopDirection = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 198:
            {
                Alignment = 1;
                break;
            }

            case 199:
            {
                BuzzAndHorn = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 200:
            {
                BuzzAndHorn = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 201:
            {
                DoNotTestBMS = 1;
                break;
            }

            case 202:
            {
                DoNotTestBMS = 0;
                break;
            }

            case 203:
            {
                break;
            }

            case 204:
            {
                break;
            }
            case 205:
            {
                break;
            }

            case 206:
            {
                break;
            }

            case 207:
            {
                Alignment = 0;
                break;
            }

            case 208:
            {
                ThreePositionSwitch = 1;
                TurnSignal = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 209:
            {
                ThreePositionSwitch = 0;
                TurnSignal = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 210:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KdOneTwoLeg = Tm;
                KdOneTwoLeg = KdOneTwoLeg / 100;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 211:
            {
                break;
            }

            case 212:
            {
                break;
            }

            case 213:
            {
                break;
            }
            case 214:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorThresholdUp = Tm;
                if (SensorThresholdUp <= SensorThresholdDn) {
                    if (SensorThresholdDn < 4095) {
                        SensorThresholdUp = SensorThresholdDn + 1;
                    } else {
                        SensorThresholdUp = 4095;
                        SensorThresholdDn = 4094;
                    }
                }
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 215:
            {
                BreakInvBtn = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 216:
            {
                BreakInvBtn = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 217:
            {
                StrongModeMem = 1;
                MixedMode = 0;
                MixedMode2 = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (StrongModeMem) {
                    PrevStrongMode = 1;
                    StrongMode = 1;
                } else {
                    PrevStrongMode = 0;
                    StrongMode = 0;
                }

                break;
            }

            case 218:
            {
                StrongModeMem = 0;
                MixedMode = 0;
                MixedMode2 = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (StrongModeMem) {
                    PrevStrongMode = 1;
                    StrongMode = 1;
                } else {
                    PrevStrongMode = 0;
                    StrongMode = 0;
                }
                break;
            }

            case 219:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                BreakThreshold = Tm;
                KThreshold = (long int) ((((float) MAX_PWM) / (MAX_PWM - BreakThreshold))*256);
                KThresholdBreak = (long int) ((((float) MAX_PWM) / (BreakThreshold))*256);
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 220:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KFirstBreak = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 221:
            {
                /*MaxAngleStopBreak=RecBytes[2];
                OptionsToMass();
                MustTrmFlashMass=1;
                 */
                break;
            }
            case 222:
            {
                if (SensOrder1 != RecBytes[2]) {
                    CurrDecrease = 1;
                    //ChangeCurrStateMachine=2;
                    CurrUst = 300;
                    //CurrUstWork=CurrUst;
                    CurrPhaseLimit = 600;
                    //CurrPhaseLimitWork=CurrPhaseLimit;

#if defined                                REV2
                    CurrLimit = 0;
#else
                    CurrLimit = 1;
#endif
                    //CurrLimitWork=CurrLimit;
                    ChangeCVR();

                    SensOrder1 = RecBytes[2];
                    RdSensors();
                    OptionsToMass();
                    MustTrmFlashMass = 1;

                }

                break;
            }
            case 223:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                Cmd5BMS = Tm;
                Cmd5BMS = Cmd5BMS << 5;
                Cmd5BMS = Cmd5BMS | ((unsigned char) 0x9);
                Cmd5BMS = Cmd5BMS << 3;
                break;
            }

            case 224:
            {
                Cmd5BMS = ((unsigned char) 0xa) << 3;
                break;
            }
            case 225:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                SensorLessTimerConstConst = Tm;
                //SensorLessTimerConst=Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;

                break;
            }

            case 226:
            {
                Sensorless2 = 1;

                /*
                SensorlessNotBEMF=1;
                SensorlessInit();
                */
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 227:
            {
                Sensorless2 = 0;
                /*Sensorless = 0;
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
                */
                OptionsToMass();
                MustTrmFlashMass = 1;


                break;
            }

            case 228:
            {
                if (!AlarmOn) {
                    if (!Spd1ResPlus)
                        AlmOn();
                }
                MustTrmFlashMass = 1;
                break;
            }

            case 229:
            {
                if (AlarmOn) {
                    AlmOff();
                    BreakPressed = 0;
                    AlmOffing = 1;
                }
                MustTrmFlashMass = 1;
                break;
            }
            case 230:
            {
                break;
            }
            case 231:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KpCurr = Tm;
                KpCurr = KpCurr / 100;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
                break;
            }
            case 232:
            {
                TrapezoidaRAM1 = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 233:
            {
                TrapezoidaRAM1 = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 234:
            {
                CURRENT_PROTECTION = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 235:
            {
                CURRENT_PROTECTION = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 236:
            {
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                KiCurr = Tm;
                KiCurr = KiCurr / 100;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 237:
            {
                //ChangeCurrStateMachine=0;
                int Tm;
                Tm = (int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CurrUstWork = Tm;
                if (!Sensorless)
                    CurrUst = CurrUstWork;

                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 238:
            {
                CalibrateHalls = 1;
                SoundNum = 8;


            }

            case 239:
            {
                PWM32Bits = 1;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 240:
            {
                PWM32Bits = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }


            case 241:
            {
                break;
            }


            case 242:
            {
                break;
            }


            case 243:
            {
                break;
            }
            case 244:
            {
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 245:
            {
                Locked = 1;
                SoundNum = 20;
                break;
            }


            case 247:
            {
                SendingMass = 1;
                SndDebugArraysStateMachine=1;
                Idx=0;
                break;
            }


            case 249:
            {
                StrongModeMem = 0;
                MixedMode = 1;
                MixedMode2 = 0;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 250:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CntMixedModeMax = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 251:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                MixedModeLevelOn = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }

            case 252:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                CurrMixed = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 253:
            {
                unsigned int Tm;
                Tm = (unsigned int) RecBytes[3];
                Tm = Tm << 8;
                Tm = Tm + RecBytes[2];
                MixedModeLevelOff = Tm;
                OptionsToMass();
                MustTrmFlashMass = 1;
                break;
            }
            case 254:
            {
                Cmmd = RecBytes[2];

                switch (Cmmd) {
                    case 1:
                        RotAlfaXRes = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 2:
                        RotAlfaXRes = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 3:
                        TurnSignal = 1;
                        ThreePositionSwitch = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 4:
                        LightsTudaSuda = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 5:
                        LightsTudaSuda = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 6:
                        LightsStopMonoDir = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 7:
                        LightsStopMonoDir = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 8:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        GyroZFlTurn = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 9:
                    {
                        ThrottleTmpChngMem = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 10:
                        SlowStart = 1;
                        PWM_Mode = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 11:
                        SlowStart = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 12:


                        break;
                    case 13:
                        break;
                    case 14:
                    {
                        SlowStrtSpd = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 15:
                    {
                        AntiPolicePower = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 16:
                    {
                        MixedModeSlowSpeedOff = 1;
                        if (StrongModeMem)
                            StrongMode = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 17:
                    {
                        MixedModeSlowSpeedOff = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 18:
                    {
                        MixedModeSlowSpeed = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 19:
                    {
                        StrongModeMem = 0;
                        MixedMode = 0;
                        MixedMode2 = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 20:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        Ki_PWM_Mode = Tm;
                        Ki_PWM_Mode = Ki_PWM_Mode / 10000;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 21:
                    {
                        PWM_Mode = 1;
                        SlowStart = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 22:
                    {
                        PWM_Mode = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 23:
                    {
                        PWM_Mode_ZeroThrottle = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 24:
                    {
                        PWM_Mode_ZeroThrottle = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 25:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        Kp_PWM_Mode = Tm;
                        Kp_PWM_Mode = Kp_PWM_Mode / 100;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 26:
                    {

                        if ((!Sensorless) && VectorMem && Vector) {
                            StrongMode = 1;
                            PrevStrongMode = 1;
                            SIN_MIDDLE = 1;
                            StrongModeMem = 1;
                            MixedMode = 0;
                            MixedMode2 = 0;
                            RdSensors();
                            Amplitude1 = PDC1;
                            VectorInit();
                        }

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 27:
                    {
                        SIN_MIDDLE = 0;
                        if ((!Sensorless) && VectorMem && Vector) {
                            if (StrongModeMem)
                                StrongMode = 1;
                            else
                                StrongMode = 0;

                            RdSensors();
                            Amplitude1 = PDC1;
                            VectorInit();
                        }
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 28:
                    {
                        InvSin = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 29:
                    {
                        InvSin = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 30:
                    {
                        CurrLimitSound = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 31:
                    {
                        CurrLimitSound = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 32:
                    {
                        //ChangeCurrStateMachine=0;
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        CurrPhaseLimitWork = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 33:
                    {
                        CurrSensor = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 34:
                    {
                        CurrDecrease = 1;
                        CurrUst = 300;
                        CurrPhaseLimit = 600;
                        CurrLimit = 0;
                        ChangeCVR();
                        break;
                    }

                    case 35:
                    {
                        CurrDecrease = 0;
                        break;
                    }

                    case 36:
                    {
                        //ChangeCurrStateMachine=0;
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        Spd0TimerConst = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 37:
                    {
                        FillCurrentMass = 1;
                        FillSinMass = 0;
                        break;
                    }
                    case 38:
                    {
                        FillCurrentMass = 0;
                        FillSinMass = 1;
                        break;
                    }
                    case 39:
                    {
                        FillCurrentMass = 0;
                        FillSinMass = 0;
                        break;
                    }

                    case 40:
                    {
                        CW_CCW_AnyProfile = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 41:
                    {
                        CW_CCW_AnyProfile = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 42:
                    {
                        BuzzerOff = !BuzzerOff;
                        break;
                    }
                    case 43:
                    {
                        SoundNum = 11;
                        AutoNastroykaState = 1;
                        break;
                    }
                    case 44:
                    {
                        AutoNastroyka_ConfirmMSG = 1;
                        break;
                    }
                    case 45:
                    {
                        AutoNastroykaState = 29;
                        break;
                    }
                    case 46:
                    {
                        AutoNastroykaState = 30;
                        SensorThresholdDn = SensorThresholdDnTmp;
                        AutoNastroykaCMFStart(30);
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 47:
                    {
                        AutoNastroykaState = 31;
                        break;
                    }
                    case 48:
                    {
                        AutoNastroykaState = 32;
                        BreakThresholdDn = BreakThresholdDnTmp;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 49:
                    {
                        AutoNastroykaState = 0;
                        SoundNum = 12;
                        MustTrmFlashMass = 1;

                        if (ThrottleTmp > 100)
                            CriticalError = CRERR_THROTTLE_AFTER_TUNING;


                        break;
                    }
                    case 50:
                        AutoNastroykaState = 0;
                        SoundNum = 10;
                        break;

                    case 51:
                        AutoNastroykaState = 18;
                        SoundNum = 12;
                        break;

                    case 52:
                        HallDelay1MaxSPD_F = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 53:
                        HallDelay1MaxSPD_B = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 54:
                        HallDelayMaxSPD = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 55:
                        ShortCircuit = 1;
//                        Mgnovenniy = 0;
                        VectorInit();
                        Comparator2_Init();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 56:
                        ShortCircuit = 0;
  //                      Mgnovenniy = 1;
                        VectorInit();
                        Comparator2_Init();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 57:
                        ShortCircuit = 0;
    //                    Mgnovenniy = 0;
                        VectorInit();
                        Comparator2_Init();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 58:
                    {
                        unsigned char p;

#if !defined BLE
                        PIN_CODE_HC05 = 1;
                        for (p = 0; p < (RecBytes[0] - 2); p++)
                            PinCodeMass[p + 8] = RecBytes[p + 3];


                        StringPINLenght = p + 8;
                        StringPINLenghtOptions = 0;
#else

                        for (p = 0; p < (RecBytes[0] - 2); p++)
                            PinCodeMassOptions[p] = RecBytes[p + 3];


                        StringPINLenghtOptions = p;



                        OptionsToMass();
                        MustTrmFlashMass = 1;

#endif
                        if (!ResetedPIN1)
                            SoundNum = 1;

                        ResetedPIN1 = 0;

                    }
                        break;

                    case 59:
                        BothBreaks = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 60:
                        BothBreaks = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 61:
                        GAZ_IMMITATOR = 1;
                        GazImm = 500;
                        break;
                    case 62:
                        GAZ_IMMITATOR = 0;
                        break;
                    case 63:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        GazImm = Tm;

                        break;
                    }

                    case 64:
                    {
                        unsigned char p;


                        for (p = 0; p < (RecBytes[0] - 2); p++)
                            PinCodeMassOptionsUnlock[p] = RecBytes[p + 3];


                        StringPINLenghtOptionsUnlock = p;

                    }
                        break;

                    case 66:
                    {
                        if (Monocycle) {
                            StrongMode = 0;
                            DS = 1;
                            NoBalance = 1;
                        }
                        StartCharging();
                    }
                        break;

                    case 67:
                    {
                        StopCharging();
                    }
                        break;


                    case 68:
                    {
                        TrapezoidaWhenBigCurrent = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                    }
                        break;

                    case 69:
                    {
                        TrapezoidaWhenBigCurrent = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                    }
                        break;

                    case 70:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        BigCurrent = Tm;


                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 71:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        ChagerCurr = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 72:
                        P_Curr = RecBytes[3];
                        P_Curr = P_Curr / 100;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 73:
                        I_Curr = RecBytes[3];
                        I_Curr = I_Curr / 100;
                        EChagerCurrSumm = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 74:
                        P_U = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 75:
                        I_U = RecBytes[3];
                        EChagerUSumm = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 76:
                        _2WDMode = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 77:
                        _2WDMode = 1;
                        U3MODEbits.UARTEN = 0;
                        InitPort_U3();
                        UARTInit_U3();
                        OnTransmitt_U3 = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 78:
                        _2WDMode = 2;
                        U3MODEbits.UARTEN = 0;
                        InitPort_U3();
                        UARTInit_U3();
                        OnTransmitt_U3 = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 79:
                        Joystick = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 80:
                        Joystick = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 81:
                        JoystickCalibrOnReset = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 82:
                        JoystickCalibrOnReset = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 83:
                        CalibrateJOYSTICK = 1;
                        ADCThrottleSumm = 0;
                        ADCThrottleBreakSumm = 0;
                        CntCalibrateJOYSTICK = 0;
                        SoundNum = 1;
                        break;
                    case 84:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        JoistickDeadZone = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 85:
                        ChangeAxis = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 86:
                        ChangeAxis = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 87:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpKpMustBe = (float) Tm;
                        KpKpMustBe = KpKpMustBe / 100;
                        /*                                      if (KpKpMinus)
                                                              {
                                                                  if (KpKpMustBe>0)
                                                                      KpKpMustBe=-KpKpMustBe;
                                                              }
                         */
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 88:
                        IRFP4110 = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 89:
                        IRFP4110 = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 90:
                    {
                        //ChangeCurrStateMachine=0;
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        ThrottleLevelUpOff = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 91:
                    {
                        SoundNum = 12;
                        LightMode = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 92:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        LightSensorThresholdLo = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 93:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        LightSensorThresholdHi = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }


                    case 94:
                        MustTrmFlashMass2ForSaveOptPC = 1;
                        break;

                    case 95:
                    {
                        int Tm;

                        for (Tm = 0; Tm<sizeof (FlashMass2); Tm++)
                            FlashMass2[Tm] = RecBytes[Tm + 5];
                        MassToOptions();
                        MassToOptionsProfile();
                        MustTrmCmdOk3 = 1;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 96:
                        LightOn = 1;
                        KeyLightStop = 0;
                        KeyLightStopGabarit = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 97:
                        LightOn = 0;
                        KeyLightStop = 0;
                        KeyLightStopGabarit = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;


                    case 98:
                        if (!Sensorless) {
                            SpeedControl = 1;
                            EPID_Res_Tek = 0;
                            ECurr1Summ = 0;
                            CurrentControlOnly = 1;
                        }
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;


                    case 99:
                    {
                        CurrentMaxCurrentOnly = RecBytes[3];
                        CurrentMaxCurrentOnlyWork = ((float) CurrentMaxCurrentOnly * 1000/**Crr1Corr*/) / CurrPerDigit;


                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 100:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        K_PWM_Nastr = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 101:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        Khard = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 105:
                    {
                        Crr1Corr = (float) RecBytes[3];
                        Crr1Corr = Crr1Corr / 50;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 106:
                    {
                        //                   ButtonBreakOnly = 1;
                        //                   SmoothBreak = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 107:
                    {
                        //                  ButtonBreakOnly = 0;
                        //                 SmoothBreak = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 108:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        ButtonBreakOnlyPWM = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 109:
                    {
                        StpLights = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 110:
                    {
                        StpLights = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 111:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        CntTurnOnConst = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 112:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        CntTurnOffConst = Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 113:
                    {
                        TemperatureTYPE_FETs = RecBytes[3];
                        ;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 114:
                    {
                        TEST_PWM_KEYS = 1;
                        StrongModeMem = 1;
                        MixedMode = 0;
                        MixedMode2 = 0;

                        VectorMem = 0;
                        Vector = 0;
                        RdSensors();
                        TrapeziumInit();


                        OptionsToMass();
                        MustTrmFlashMass = 1;

                        PrevStrongMode = 1;
                        StrongMode = 1;


                        break;
                    }

                    case 115:
                    {
                        TrapeziumInit();
                        TEST_PWM_KEYS = 0;
                        break;
                    }

                    case 116:
                    {
                        TstPhase = RecBytes[3];
                        if (TstPhase == 0)
                            SensorTSTKeys = 4;
                        if (TstPhase == 1)
                            SensorTSTKeys = 1;
                        if (TstPhase == 2)
                            SensorTSTKeys = 2;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 117:
                    {
                        Vertical = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 118:
                    {
                        Vertical = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }


                    case 119:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        SpdStartLevel = Tm;
                        SpdStartLevelFl = ((float) SpdStartLevel) / ImpToKmH1_t;


                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 120:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        Ki_PWM_ModeOff = Tm;
                        Ki_PWM_ModeOff = Ki_PWM_ModeOff / 10000;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 121:
                    {
                        StrongModeSpdFilterOffMem = RecBytes[3];
                        StrongModeSpdFilterOff = ((float) StrongModeSpdFilterOffMem) / ImpToKmH1_t;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 122:
                    {
                        StrongModeBreakOff = 1;
                        StrongModeMotorOff = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 123:
                    {
                        StrongModeBreakOff = 0;
                        StrongModeMotorOff = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 124:
                    {
                        StrongModeBreakOff = 0;
                        StrongModeMotorOff = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 125:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        RegenOffMem = Tm;
#if !defined VECTOR
#if !defined ISOLATED
                        RegenOff = (unsigned int) ((float) RegenOffMem * (float) 38.388);
#else
                        RegenOff = (unsigned int) ((float) RegenOffMem / (float) 0.4167965);
#endif
#else
                        RegenOff = (unsigned int) ((float) RegenOffMem * (float) 38.388);
#endif



                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 126:
                        LightOn = 0;
                        KeyLightStop = 1;
                        KeyLightStopGabarit = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 127:
                    {
                        KeyLightBrightness = RecBytes[3];
                        if (OC3R != 0)
                            OC3R = ((unsigned int) KeyLightBrightness) << 8;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 128:
                        LightOn = 0;
                        KeyLightStop = 0;
                        KeyLightStopGabarit = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 129:
                        MigStop = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 130:
                        MigStop = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 131:
                        AutoNastroykaState = 30;
                        AutoNastroykaCMFStart(29);
                        break;

                    case 132:
                        AutoNastroykaState = 32;
                        AutoNastroykaCMFStart(31);
                        break;
                    case 133:
                        AutoNastroykaState = 27;
                        break;

                    case 134:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        ButtonBreakOnlyTime = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 135:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        BreakMonocycleSpd = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 136:
                        PWMkHz = RecBytes[3];

                        switch (PWMkHz) {
                            case 1:
                                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
                                break;
                            case 2:
                                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE10kHz;
                                TrapezoidaWhenBigSpeed = 1;
                                if (VectorOnOffSpdLo > Trapezium10kHzLo)
                                    VectorOnOffSpdLo = Trapezium10kHzLo;
                                if (VectorOnOffSpdHi > Trapezium10kHzHi)
                                    VectorOnOffSpdHi = Trapezium10kHzHi;
                                break;
                            case 3:
                                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE5kHz;
                                TrapezoidaWhenBigSpeed = 1;
                                if (VectorOnOffSpdLo > Trapezium5kHzLo)
                                    VectorOnOffSpdLo = Trapezium5kHzLo;
                                if (VectorOnOffSpdHi > Trapezium5kHzHi)
                                    VectorOnOffSpdHi = Trapezium5kHzHi;
                                break;
                            default:
                                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
                                PWMkHz = 1;
                                break;
                        }


                        MAX_PWM = MAX_PWM_CONST;
                        PHASE1 = MAX_PWM + DEADTIME + Khard;
                        PHASE2 = MAX_PWM + DEADTIME + Khard;
                        PHASE3 = MAX_PWM + DEADTIME + Khard;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 137:
                        break;

                    case 138:
                        LightsFromButton = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 139:
                        LightsFromButton = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 140:
                        KpKpDeadZoneMem = RecBytes[3];
                        KpKpDeadZone = ((float) (KpKpDeadZoneMem)) / 10;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 141:
                        PWMSignal = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 142:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpSlowSpeed = (float) Tm;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 143:
                        SlowSpeedForKp = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 144:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KiKpMustBe = Tm;
                        KiKpMustBe = KiKpMustBe / 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }


                    case 145:
                        KiKpDeadZoneMem = RecBytes[3];
                        KiKpDeadZone = ((float) (KiKpDeadZoneMem)) / 10;

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 146:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KiMax = Tm;
                        KiMax = KiMax / 1000;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 147:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        TimeDecreaseKi = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 148:
                        KpKpMinus = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 149:
                        KpKpMinus = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 150:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpMin = (float) Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 151:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        EpPWMmax = (float) Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 152:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        EiPWMmax = (float) Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 153:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        EdPWMmax = (float) Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 154:
                        RotAddSumm = 0;
                        Segway = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 155:
                        Segway = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    case 156:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        DeadZoneHandleBarSegwayMustBe = Tm;
                        DeadZoneHandleBarSegwayMustBe = DeadZoneHandleBarSegwayMustBe / 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 157:
                    {
                        int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KRotMustBe = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 158:
                    {
                        int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpRotMustBe = (float) Tm;
                        KpRotMustBe = KpRotMustBe / 1000;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 159:
                    {
                        int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KiRotMustBe = (float) Tm;
                        KiRotMustBe = KiRotMustBe / 10000;
                        RotAddSumm = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 160:
                    {
                        FindGyroVertical = 1;
                        break;
                    }
                    case 161:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        HighSpeed = Tm;
                        HighSpeedQuantum();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 162:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        GoalSpeed = Tm;
                        HighSpeedQuantum();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 163:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        StartRotHighSpeed = (int) Tm;
                        StartRotHighSpeed = StartRotHighSpeed / 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 164:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KRotHighSpeed = (int) Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 165:
                    {
                        GyroAccSameOff = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 166:
                    {
                        GyroAccSameOff = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 167:
                    {
                        HumanSensor = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 168:
                    {
                        HumanSensor = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 169:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        TimeHumanSensorOff = (unsigned int) Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 170:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpKpZoneEnd = (float) Tm;
                        KpKpZoneEnd = KpKpZoneEnd / 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 171:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpKp2MustBe = (float) Tm;
                        KpKp2MustBe = KpKp2MustBe / 100;
                        if (KpKpMinus) {
                            if (KpKp2MustBe > 0)
                                KpKp2MustBe = -KpKp2MustBe;
                        }

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 172:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpKp2DeadZone = (float) Tm;
                        KpKp2DeadZone = KpKp2DeadZone / 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 173:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpKp2ZoneEnd = (float) Tm;
                        KpKp2ZoneEnd = KpKp2ZoneEnd / 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }


                    case 174:
                    {
                        PWMChanged = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 175:
                    {
                        PWMChanged = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 176:
                    {
                        unsigned int Tm;
                        Tm = (unsigned int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        PWMChangedThreshold = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 177:
                    {
                        InvHallA = 1;
                        RdSensors();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 178:
                    {
                        InvHallA = 0;
                        RdSensors();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 179:
                    {
                        InvHallB = 1;
                        RdSensors();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 180:
                    {
                        InvHallB = 0;
                        RdSensors();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 181:
                    {
                        InvHallC = 1;
                        RdSensors();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 182:
                    {
                        InvHallC = 0;
                        RdSensors();
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 183:
                    {
                        BreakFilter = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 184:
                    {
                        BreakFilter = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 185:
                        SpdKdMax = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;

                    case 186:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];

                        KdKpSpd = (float) Tm;
                        KdKpSpd = KdKpSpd * (ImpToKmH1_t);

                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 187:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KdMax = Tm;
                        KdMax = KdMax * 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 188:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KdMin = Tm;
                        KdMin = KdMin * 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 189:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KiKd = Tm;
                        KiKd = KiKd * 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }


                    case 190:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];

                        VectorOnOffSpdLo = Round(((float) Tm) / ImpToKmH1_t);
                        if (PWMkHz == 2) {
                            if (VectorOnOffSpdLo > Trapezium10kHzLo)
                                VectorOnOffSpdLo = Trapezium10kHzLo;
                        }
                        if (PWMkHz == 3) {
                            if (VectorOnOffSpdLo > Trapezium5kHzLo)
                                VectorOnOffSpdLo = Trapezium5kHzLo;
                        }


                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 191:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        VectorOnOffSpdHi = Round(((float) Tm) / ImpToKmH1_t);

                        if (PWMkHz == 2) {
                            if (VectorOnOffSpdHi > Trapezium10kHzHi)
                                VectorOnOffSpdHi = Trapezium10kHzHi;
                        }
                        if (PWMkHz == 3) {
                            if (VectorOnOffSpdHi > Trapezium5kHzHi)
                                VectorOnOffSpdHi = Trapezium5kHzHi;
                        }



                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 192:
                    {
                        TrapezoidaWhenBigSpeed = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 193:
                    {
                        TrapezoidaWhenBigSpeed = 0;
                        TrapezoidaRAM1 = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 194:
                    {
                        I_PWMmaxSignal = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 195:
                    {
                        I_PWMmaxSignal = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 196:
                    {
                        OnDelay = RecBytes[3];
                        OnDelayConst = ((int) OnDelay)*250;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 197:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KiUBTCoeff = ((float) Tm) / 10000;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 198:
                    {
                        SpdKiMin = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 199:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KiMin = ((float) Tm) / 1000;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 200:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        ELimitedMem = ((float) Tm) / 100;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 201:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KdNoManR = (float) Tm * 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 202:
                    {
                        DifferentKd = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 203:
                    {
                        DifferentKd = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 204:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        KpDeadZone = ((float) Tm) / 10;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 205:
                    {
                        StopIfPWM100Time = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }

                    case 206:
                    {
                        CntKdSwitchCONST = RecBytes[3];
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 207:
                    {
                        int Tm;
                        Tm = (int) RecBytes[4];
                        Tm = Tm << 8;
                        Tm = Tm + RecBytes[3];
                        PWMSignalTimer = Tm;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 208:
                    {
                        HighDataSpdUART = 1;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }
                    case 209:
                    {
                        HighDataSpdUART = 0;
                        OptionsToMass();
                        MustTrmFlashMass = 1;
                        break;
                    }


                }
                break;
            }



        }
    }

}

void InitOC4(void) {
    OC4CON1 = 0;
    OC4CON2 = 0;
    OC4CON1bits.OCTSEL = 0x07;
    OC4CON1bits.OCSIDL = 1;
    OC4R = 1;
    OC4RS = 2; //Min -> 2   Max -> 8007
    OC4CON2bits.OCTRIG = 1;

    IEC1bits.OC4IE = 0; //????????? ??????????
    IPC6bits.OC4IP = 2;

    OC4CON2bits.SYNCSEL = 0xd;
    OC4CON1bits.TRIGMODE = 1;
    OC4CON1bits.OCM = 7; //3;
}

void __attribute__((interrupt, auto_psv)) _OC4Interrupt() {
    //if (IFS1bits.OC4IF)
    //IFS1bits.OC4IF=0;
    IEC1bits.OC4IE = 0;
    if (InitReady) {
        SegMain();
    }
}





// ACC SPI

static void ConfigureSpiAcc(void) {
    /*----------------------------------------------------------------*/
    /* After we save context, configure SPI for MRF24W communications */
    /*----------------------------------------------------------------*/
    /* enable the SPI clocks            */
    /* set as master                    */
    /* clock idles high                 */
    /* ms bit first                     */
    /* 8 bit tranfer length             */
    /* data changes on falling edge     */
    /* data is sampled on rising edge   */
    /* set the clock divider            */
    ACC_SPICON1 = 0x0278; //0x027B;    // Fcy Primary prescaler 1:1, secondary prescaler 2:1, CKP=1, CKE=0, SMP=1
    ACC_SPICON2 = 0x0000;
    ACC_SPISTAT = 0x8000; // Enable the module
    ACC_SPISTATbits.SISEL = 1;
    ACC_SPI_IF = 0;


}

#define ClearSPIAccDoneFlag()

static inline __attribute__((__always_inline__)) void WaitForDataByteAcc(void) {
    while ((ACC_SPISTATbits.SPITBF == 1) || (ACC_SPISTATbits.SPIRBF == 0));
}

void InitAccSPI(void) {


    ANSELAbits.ANSA6 = 0;

    ACC_INT1_TRIS = 1;

#if !defined VECTORMS
    ACC_SCK_TRIS = 0;
    ACC_SCK_RPOR = 0b100011; //6;
    ACC_dsPICSDO_TRIS = 0;
    ACC_dsPICSDO_RPOR = 0b100010; //5;
#endif

    ACC_dsPICSDI_TRIS = 1;
    RPINR31bits.SDI4R = ACC_dsPICSDI_RPINR;

    ACC_CS_IO = 1;
    ACC_CS_TRIS = 0;



    /* enable the spi interrupt */
    ACC_SPI_IE = 1;


    // Set up the SPI module on the PIC for communications with the Acc
    ACC_CS_IO = 1;
    ACC_CS_TRIS = 0; // Drive SPI MRF24W chip select pin

    ConfigureSpiAcc();

    ClearSPIAccDoneFlag();
    IPC30bits.SPI4IP = 3;
}

void __attribute__((interrupt, auto_psv)) _SPI4Interrupt(void) {
    ACC_SPI_IF = 0;
    Acc_rxBuf[SPIRxCnt] = ACC_SSPBUF;
    SPIRxCnt++;
    if (SPIRxCnt < SPIAccbyteCount)
        ACC_SSPBUF = Acc_txBuf[SPIRxCnt];

    if (SPIRxCnt >= SPIAccbyteCount) {
#if !defined VECTOR_MPU_6000        
        HvAccData = 1;
        WF_SpiAccDisableChipSelect();

        AccX = Acc_rxBuf[3];
        AccX = AccX << 8;
        AccX = AccX + Acc_rxBuf[2];

        AccY = Acc_rxBuf[5];
        AccY = AccY << 8;
        AccY = AccY + Acc_rxBuf[4];


        AccZ = Acc_rxBuf[7];
        AccZ = AccZ << 8;
        AccZ = AccZ + Acc_rxBuf[6];

        AccXFl = (int) (AccX - CalibrationAccX);
        AccYFl = (int) (AccY - CalibrationAccY);
        AccZFl = (int) (AccZ - CalibrationAccZ);



        //    IEC1bits.OC4IE=1;
#endif
    }
}

void TxRxSPI_ACC(unsigned int txLen) {


    while (SPIRxCnt < SPIAccbyteCount) {
        Nop();
        Nop();
        Nop();
    }
    SPIAccbyteCount = txLen;
    SPIRxCnt = 0;
    WF_SpiAccEnableChipSelect();
    ACC_SSPBUF = Acc_txBuf[0];
}

void WF_SpiAccEnableChipSelect(void) {

    ACC_CS_IO = 0;

}

void WF_SpiAccDisableChipSelect(void) {
    ACC_CS_IO = 1;
}

// END ACC SPI




// GYRO SPI

/*
static void ConfigureSpiGyro(void)
{
        GYRO_SPICON1 = 0x0278;//0x027B;    // Fcy Primary prescaler 1:1, secondary prescaler 2:1, CKP=1, CKE=0, SMP=1
        GYRO_SPICON2 = 0x0000;
        GYRO_SPISTAT = 0x8000;    // Enable the module
        GYRO_SPISTATbits.SISEL=1;
        GYRO_SPI_IF=0;


}
 */
static void ConfigureSpiGyro(void) {
    /*----------------------------------------------------------------*/
    /* After we save context, configure SPI for MRF24W communications */
    /*----------------------------------------------------------------*/
    /* enable the SPI clocks            */
    /* set as master                    */
    /* clock idles high                 */
    /* ms bit first                     */
    /* 8 bit tranfer length             */
    /* data changes on falling edge     */
    /* data is sampled on rising edge   */
    /* set the clock divider            */
    GYRO_SPICON1 = 0x0278; //0x027B;    // Fcy Primary prescaler 1:1, secondary prescaler 2:1, CKP=1, CKE=0, SMP=1
    GYRO_SPICON2 = 0x0000;
    GYRO_SPISTAT = 0x8000; // Enable the module
}



#define ClearSPIGyroDoneFlag()

static inline __attribute__((__always_inline__)) void WaitForDataByteGyro(void) {
    while ((GYRO_SPISTATbits.SPITBF == 1) || (GYRO_SPISTATbits.SPIRBF == 0));
}

void InitGyroSPI(void) {

    GYRO_INT1_TRIS = 1;

    GYRO_SCK_TRIS = 0;
    GYRO_SCK_RPOR = 0b100000; //6;

    GYRO_dsPICSDO_TRIS = 0;
    GYRO_dsPICSDO_RPOR = 0b011111; //5

    GYRO_dsPICSDI_ANSEL = 0;
    GYRO_dsPICSDI_TRIS = 1;
    RPINR29bits.SDI3R = GYRO_dsPICSDI_RPINR;


    GYRO_CS_ANSEL = 0;
    GYRO_CS_IO = 1;
    GYRO_CS_TRIS = 0;

#if defined LSM6DS33
    GYRO_CS1_TRIS = 0;
    GYRO_CS1_ANSEL = 0;
    GYRO_CS1_IO = 1;

#endif

#if defined MPU6500
    GYRO_CS2_TRIS = 0;
    GYRO_CS2_ANSEL = 0;
    GYRO_CS2_IO = 1;

#endif



    /* disable the spi interrupt */
    GYRO_SPI_IE = 1;

    // Set up the SPI module on the PIC for communications with the Acc
    GYRO_CS_IO = 1;
    GYRO_CS_TRIS = 0; // Drive SPI MRF24W chip select pin

    ConfigureSpiGyro();

    IPC22bits.SPI3IP = 3;
    ClearSPIGyroDoneFlag();
}



//void __attribute__((interrupt, no_auto_psv)) _T3Interrupt( void )

void __attribute__((interrupt, auto_psv)) _SPI3Interrupt(void) {
    int GyroYTmp;
    GYRO_SPI_IF = 0;
    Gyro_rxBuf[SPIRxGyroCnt] = GYRO_SSPBUF;
    SPIRxGyroCnt++;
    if (SPIRxGyroCnt < SPIGyrobyteCount)
        GYRO_SSPBUF = Gyro_txBuf[SPIRxGyroCnt];

    if (SPIRxGyroCnt >= SPIGyrobyteCount) {
#if !defined VECTOR
        HvGyroData = 1;
        WF_SpiGyroDisableChipSelect();
        if (!TemperatureFl) {

            Temperature = Gyro_rxBuf[1];
            GyroX = Gyro_rxBuf[4];
            GyroX = GyroX << 8;
            GyroX = GyroX + Gyro_rxBuf[3];

            GyroY = Gyro_rxBuf[6];
            GyroY = GyroY << 8;
            GyroY = GyroY + Gyro_rxBuf[5];


            GyroZ = Gyro_rxBuf[8];
            GyroZ = GyroZ << 8;
            GyroZ = GyroZ + Gyro_rxBuf[7];

            GyroXFl = (float) (GyroX - CalibrationGyroX);
            GyroYFl = (float) (GyroY - CalibrationGyroY);
            GyroZFl = (float) (GyroZ - CalibrationGyroZ);


            //IEC1bits.OC4IE=1;

        } else {
            TemperatureFl = 0;
            Nop();
            Nop();
            Nop();
            Temperature = Gyro_rxBuf[1];
        }
#else
        WF_SpiGyroDisableChipSelect();
#if !defined LSM6DS33
        AccX = Gyro_rxBuf[1];
        AccX = AccX << 8;
        AccX = AccX + Gyro_rxBuf[2];

        AccY = Gyro_rxBuf[3];
        AccY = AccY << 8;
        AccY = AccY + Gyro_rxBuf[4];


        AccZ = Gyro_rxBuf[5];
        AccZ = AccZ << 8;
        AccZ = AccZ + Gyro_rxBuf[6];



        TemperatureMPU6000 = Gyro_rxBuf[7];
        TemperatureMPU6000 = TemperatureMPU6000 << 8;
        TemperatureMPU6000 = TemperatureMPU6000 + Gyro_rxBuf[8];


        GyroX = Gyro_rxBuf[9];
        GyroX = GyroX << 8;
        GyroX = GyroX + Gyro_rxBuf[10];

        GyroY = Gyro_rxBuf[11];
        GyroY = GyroY << 8;
        GyroY = GyroY + Gyro_rxBuf[12];

        GyroZ = Gyro_rxBuf[13];
        GyroZ = GyroZ << 8;
        GyroZ = GyroZ + Gyro_rxBuf[14];

        if (GyroX == 0x8000) {
            GyroX = GyroXPrev1;
        }
        if (GyroY == 0x8000) {
            GyroY = GyroYPrev1;
        }
        if (GyroZ == 0x8000) {
            GyroZ = GyroZPrev1;
        }



        GyroXPrev1 = GyroX;
        GyroYPrev1 = GyroY;
        GyroZPrev1 = GyroZ;



        GyroYTmp = GyroY;
        GyroY = GyroX;
        GyroX = -GyroYTmp;

#if defined MPU6500
        AccX = -AccX;
        AccY = -AccY;
#else
        AccZ = -AccZ;
#endif


        GyroXFl = (float) (GyroX - CalibrationGyroX);
        GyroYFl = (float) (GyroY - CalibrationGyroY);
        GyroZFl = (float) (GyroZ - CalibrationGyroZ);


        AccXFl = (float) (AccX - CalibrationAccX);
        AccYFl = (float) (AccY - CalibrationAccY);
        AccZFl = (float) (AccZ - CalibrationAccZ);

#else


        TemperatureMPU6000 = Gyro_rxBuf[2];
        TemperatureMPU6000 = TemperatureMPU6000 << 8;
        TemperatureMPU6000 = TemperatureMPU6000 + Gyro_rxBuf[1];


        GyroX = Gyro_rxBuf[4];
        GyroX = GyroX << 8;
        GyroX = GyroX + Gyro_rxBuf[3];

        GyroY = Gyro_rxBuf[6];
        GyroY = GyroY << 8;
        GyroY = GyroY + Gyro_rxBuf[5];


        GyroZ = Gyro_rxBuf[8];
        GyroZ = GyroZ << 8;
        GyroZ = GyroZ + Gyro_rxBuf[7];



        AccX = Gyro_rxBuf[10];
        AccX = AccX << 8;
        AccX = AccX + Gyro_rxBuf[9];

        AccY = Gyro_rxBuf[12];
        AccY = AccY << 8;
        AccY = AccY + Gyro_rxBuf[11];


        AccZ = Gyro_rxBuf[14];
        AccZ = AccZ << 8;
        AccZ = AccZ + Gyro_rxBuf[13];


        int GATmp;

        GATmp = AccX; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        AccX = AccZ;
        AccZ = AccY;
        AccY = GATmp;

        GATmp = GyroY;
        GyroY = -GyroZ;
        //GyroX=-GyroZ;
        GyroZ = GATmp;




        /*
        GyroYTmp=GyroY;
        GyroY=GyroX;
        GyroX=-GyroYTmp;


        AccX=-AccX;
        AccY=-AccY;
    
    
    int GATmp;
       GyroYTmp=AccX;
        AccX=AccZ;
        GATmp=AccY;
        AccY=-GyroYTmp;
        AccZ=-GATmp;
    
        GyroYTmp=GyroX;
        GyroX=GyroZ;
        GATmp=GyroY;
        GyroY=-GyroYTmp;
        GyroZ=-GATmp;
    
    
     
     
        GyroYTmp=AccX;
        AccX=AccZ;
        GATmp=AccY;
        AccY=-GyroYTmp;
        AccZ=-GATmp;
    
        GyroYTmp=GyroX;
        GyroX=GyroZ;
        GATmp=GyroY;
        GyroY=-GyroYTmp;
        GyroZ=-GATmp;
    
         */



        GyroXFl = (float) (GyroX - CalibrationGyroX);
        GyroYFl = (float) (GyroY - CalibrationGyroY);
        GyroZFl = (float) (GyroZ - CalibrationGyroZ);


        AccXFl = (float) (AccX - CalibrationAccX);
        AccYFl = (float) (AccY - CalibrationAccY);
        AccZFl = (float) (AccZ - CalibrationAccZ);


        //        if (TestFlag)
        //      GyroX=GyroY=GyroZ=AccX=AccY=AccZ=0xffff;

        /*
    if ((GyroX==0 && GyroY==0 && GyroY==0 && AccX==0  && AccY==0  && AccZ==0))
        MPU6000_ErrZero=1;
    else
        MPU6000_ErrZero=0;
    
    if (GyroX==0xffff && GyroY==0xffff && GyroY==0xffff && AccX==0xffff  && AccY==0xffff  && AccZ==0xffff)
        MPU6000_ErrFF=1;
    else
        MPU6000_ErrFF=0;
    
         */
#endif

        IEC1bits.OC4IE = 1;


        HvGyroData = 1;
#if defined VECTOR_MPU_6000        
        HvAccData = 1;
#endif

#endif
    }
}

void TxRxSPI_GYRO(unsigned int txLen) {
    while (SPIRxGyroCnt < SPIGyrobyteCount) {
        Nop();
        Nop();
        Nop();
    }

    SPIGyrobyteCount = txLen;
    SPIRxGyroCnt = 0;
    WF_SpiGyroEnableChipSelect();
    GYRO_SSPBUF = Gyro_txBuf[0];
}

void WF_SpiGyroEnableChipSelect(void) {

    GYRO_CS_IO = 0;

}

void WF_SpiGyroDisableChipSelect(void) {
    GYRO_CS_IO = 1;
}

// END GYRO SPI

void InitFlash(void) {
    TRIS_CE_FLASH = 0;
    CE_FLASH = 1;

    TRIS_SO_FLASH = 1;

    TRIS_WP_FLASH = 0;
    WP_FLASH = 0;

    TRIS_SI_FLASH = 0;
    SI_FLASH = 0;

    TRIS_SCK_FLASH = 0;
    SCK_FLASH = 0;

    TRIS_HOLD_FLASH = 0;
    HOLD_FLASH = 0;
}

unsigned char TrmRecByteFLASH(unsigned char Bt) {
    unsigned char j, k, BtRec;

    BtRec = 0;

    for (j = 0; j < 8; j++) {
        BtRec = BtRec << 1;
        if (Bt & 0x80)
            SI_FLASH = 1;
        else
            SI_FLASH = 0;
        for (k = 0; k < 30; k++);
        SCK_FLASH = 1;
        for (k = 0; k < 30; k++);
        if (SO_FLASH)
            BtRec = BtRec | 1;
        SCK_FLASH = 0;
        Bt = Bt << 1;
    }
    return BtRec;
}

unsigned char RecStatusFLASH(void) {
    unsigned char Tm;
    HOLD_FLASH = 1;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(5);
    Tm = TrmRecByteFLASH(5);
    CE_FLASH = 1;
    HOLD_FLASH = 0;
    return Tm;
}

unsigned char RecStatusFLASH_TST(void) {
    unsigned char Tm;
    HOLD_FLASH = 0;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(5);
    Tm = TrmRecByteFLASH(5);
    CE_FLASH = 1;
    HOLD_FLASH = 0;
    return Tm;
}

unsigned char ReadFlash(unsigned long int Addr, unsigned int N, unsigned char * Mass) {
    unsigned int Tm;
    unsigned char Chk;
    HOLD_FLASH = 1;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(3);
    TrmRecByteFLASH((unsigned char) (Addr >> 16));
    TrmRecByteFLASH((unsigned char) (Addr >> 8));
    TrmRecByteFLASH((unsigned char) Addr);

    for (Tm = 0; Tm < N; Tm++)
        Mass[Tm] = TrmRecByteFLASH(0);

    Chk = TrmRecByteFLASH(0);

    CE_FLASH = 1;
    HOLD_FLASH = 0;

    return Chk;
}

void WREN_FLASH(void) {
    unsigned int Tm;
    HOLD_FLASH = 1;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(6);

    CE_FLASH = 1;
    HOLD_FLASH = 0;

}

void WRDI_FLASH(void) {
    unsigned int Tm;
    HOLD_FLASH = 1;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(4);

    CE_FLASH = 1;
    HOLD_FLASH = 0;

}

void WriteByte_FLASH(unsigned long int Addr, unsigned char Bt) {
    unsigned int Tm;
    WP_FLASH = 1;
    WREN_FLASH();

    HOLD_FLASH = 1;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(2);
    TrmRecByteFLASH((unsigned char) (Addr >> 16));
    TrmRecByteFLASH((unsigned char) (Addr >> 8));
    TrmRecByteFLASH((unsigned char) Addr);
    TrmRecByteFLASH(Bt);

    CE_FLASH = 1;
    HOLD_FLASH = 0;

    while (RecStatusFLASH()&1)
        Nop();

    WRDI_FLASH();
    StatusFlash = RecStatusFLASH();
    Nop();
    Nop();
    Nop();
    WP_FLASH = 0;
}

void WriteStat_FLASH(unsigned char St) {
    unsigned int Tm;

    WP_FLASH = 1;
    WREN_FLASH();

    HOLD_FLASH = 1;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(1);
    TrmRecByteFLASH(St);

    CE_FLASH = 1;
    HOLD_FLASH = 0;

}

void EraseSector_FLASH(unsigned long int Addr) {
    unsigned int Tm;
    WP_FLASH = 1;
    WREN_FLASH();

    HOLD_FLASH = 1;
    CE_FLASH = 0;
    for (Tm = 0; Tm < 30; Tm++);
    TrmRecByteFLASH(0x20);
    TrmRecByteFLASH((unsigned char) (Addr >> 16));
    TrmRecByteFLASH((unsigned char) (Addr >> 8));
    TrmRecByteFLASH((unsigned char) Addr);
    CE_FLASH = 1;
    HOLD_FLASH = 0;

    while (RecStatusFLASH()&1)
        Nop();

    WRDI_FLASH();
    StatusFlash = RecStatusFLASH();
    Nop();
    Nop();
    Nop();
    WP_FLASH = 0;
}

unsigned char ReadOptions(void) {
    unsigned char Chk, Chk1, ChkTmp = 0;

    for (Chk = 0; Chk<sizeof (FlashMass); Chk++)
        FlashMass[Chk] = 0;
    for (Chk = 0; Chk<sizeof (FlashMass2); Chk++)
        FlashMass2[Chk] = 0;

    Chk = ReadFlash(0, sizeof (FlashMass), FlashMass);
    Chk1 = CalcCheckSumm(sizeof (FlashMass), FlashMass);

    ChkTmp = 1;

    if (Chk != Chk1)
        ChkTmp = 0;


    Chk = ReadFlash(sizeof (FlashMass) + 1, sizeof (ProfileMass), ProfileMass);
    Chk1 = CalcCheckSumm(sizeof (ProfileMass), ProfileMass);

    if (Chk != Chk1)
        ChkTmp = 0;


    Chk = ReadFlash(sizeof (FlashMass) + sizeof (ProfileMass) + 2, sizeof (FlashMass2), FlashMass2);
    Chk1 = CalcCheckSumm(sizeof (FlashMass2), FlashMass2);

    if (Chk != Chk1)
        ChkTmp = 0;

    MassToOptions();

    if (ChkTmp && (FlashMass[0] != 0xff)) {

        return 1;
    }



    //   DefaultOptions();
    EEPROM_CHK_ERR = 1;
    //        WriteOptions();

    if (EEPROM_CHK_ERR) {
        SoundNum = 9;
    }


    return 0;

}

unsigned char ReadOptions1(void) {
    unsigned char Chk, Chk1, ChkTmp = 0;


    for (Chk = 0; Chk<sizeof (FlashMass1); Chk++)
        FlashMass1[Chk] = 0;

    Chk = ReadFlash(0, sizeof (FlashMass1), FlashMass1);
    Chk1 = CalcCheckSumm(sizeof (FlashMass1), FlashMass1);


    if (Chk == Chk1)
        ChkTmp = 1;


    Chk = ReadFlash(sizeof (FlashMass1) + 1, sizeof (ProfileMass1), ProfileMass1);
    Chk1 = CalcCheckSumm(sizeof (ProfileMass1), ProfileMass1);






    if (ChkTmp && (Chk1 == Chk)&&(FlashMass1[0] != 0xff)) {
        // MassToOptions();
        return 1;
    }



    //   DefaultOptions();
    EEPROM_CHK_ERR = 1;
    //        WriteOptions();

    if (EEPROM_CHK_ERR) {
        //SoundNum=9;
    }


    return 0;

}

void OptionsToMass(void) {
    //Mgnovenniy = 0;

    int Tm = (int) KpMustBe;
    FlashMass[0] = 0;
    FlashMass[1] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[2] = (unsigned char) Tm;

    Tm = (int) KpNoMan;
    FlashMass[3] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[4] = (unsigned char) Tm;

    Tm = (int) (KdNoMan / 10);
    FlashMass[5] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[6] = (unsigned char) Tm;

    Tm = (int) (KiNoMan * 100);
    FlashMass[7] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[8] = (unsigned char) Tm;

    Tm = (int) (KpKpSpd * 20);
    FlashMass[9] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[10] = (unsigned char) Tm;


    FlashMass[11] = But1Func;
    FlashMass[12] = But2Func;

    Tm = (int) (KGYRO * 1000);
    FlashMass[13] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[14] = (unsigned char) Tm;


    Tm = SensorLessTimerConst2;
    FlashMass[15] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[16] = (unsigned char) Tm;


    Tm = SenosrlessPWM1_2Const;
    FlashMass[17] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[18] = (unsigned char) Tm;

    Tm = SensorLessTimerConstMin;
    FlashMass[19] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[20] = (unsigned char) Tm;

    Tm = CalibrationGyroX;
    FlashMass[21] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[22] = (unsigned char) Tm;

    Tm = CalibrationGyroY;
    FlashMass[23] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[24] = (unsigned char) Tm;

    Tm = CalibrationGyroZ;
    FlashMass[25] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[26] = (unsigned char) Tm;

    Tm = CalibrationAccX;
    FlashMass[27] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[28] = (unsigned char) Tm;

    Tm = CalibrationAccY;
    FlashMass[29] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[30] = (unsigned char) Tm;

    Tm = CalibrationAccZ;
    FlashMass[31] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[32] = (unsigned char) Tm;

    FlashMass[33] = PhasePERMASS;
    FlashMass[34] = PhasePERMASS_SHFT;


    FlashMass[35] = HallDelayMem1_F;
    FlashMass[36] = HallDelayMem1_B;
    FlashMass[37] = But3Func;
    FlashMass[38] = But4Func;


    FlashMass[39] = Theta1Zero;
    FlashMass[40] = Theta2Zero;

    Tm = CurrLimitWork;
    FlashMass[41] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[42] = (unsigned char) Tm;




    Tm = ChagerCurr;
    FlashMass[43] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[44] = (unsigned char) Tm;


    Tm = (int) (KpSPDMove);
    FlashMass[45] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[46] = (unsigned char) Tm;

    Tm = (int) (KdSPD);
    FlashMass[47] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[48] = (unsigned char) Tm;

    Tm = (int) (KiSPD);
    FlashMass[49] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[50] = (unsigned char) Tm;

    Tm = (int) (AngleLimitMove);
    FlashMass[51] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[52] = (unsigned char) Tm;

    Tm = (int) (SpeedLimit1);
    FlashMass[53] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[54] = (unsigned char) Tm;

    Tm = StatFlgs.StatusFlags;
    FlashMass[55] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[56] = (unsigned char) Tm;

    Tm = XLimit;
    FlashMass[57] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[58] = (unsigned char) Tm;

    Tm = YLimit;
    FlashMass[59] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[60] = (unsigned char) Tm;

    Tm = UBatLow;
    FlashMass[61] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[62] = (unsigned char) Tm;

    Tm = CntMixedModeMax;
    FlashMass[63] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[64] = (unsigned char) Tm;

    Tm = MixedModeLevelOn;
    FlashMass[65] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[66] = (unsigned char) Tm;

    FlashMass[67] = SpeedLimit2;

    FlashMass[68] = SpeedLimit3;

    FlashMass[69] = (unsigned char) (I_Curr * 100);


    Tm = CurrMixed;
    FlashMass[70] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[71] = (unsigned char) Tm;

    Tm = (int) (KpMax);
    FlashMass[72] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[73] = (unsigned char) Tm;

    FlashMass[74] = SensorllessSpdThreshold; //CntKpMustBeConst;

    FlashMass[75] = SpdKpMax;

    Tm = MixedModeLevelOff;
    FlashMass[76] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[77] = (unsigned char) Tm;


    Tm = (int) (KpCurr * 100);
    FlashMass[78] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[79] = (unsigned char) Tm;

    Tm = (int) (Ki_PWM_Mode * 10000);
    FlashMass[80] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[81] = (unsigned char) Tm;


    FlashMass[82] = P_U;
    FlashMass[83] = I_U;


    Tm = (int) KpWheelingMem;
    FlashMass[84] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[85] = (unsigned char) Tm;

    Tm = (int) (KiWheelingMem * 1000);
    FlashMass[86] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[87] = (unsigned char) Tm;

    Tm = (int) (TiltZadWheeling * 10);
    FlashMass[88] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[89] = (unsigned char) Tm;

    Tm = MAX_PWM_MEM;
    FlashMass[90] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[91] = (unsigned char) Tm;

    Tm = (int) (KiTemperIN * (float) 100);
    FlashMass[92] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[93] = (unsigned char) Tm;


    Tm = KpTemperIN;
    FlashMass[94] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[95] = (unsigned char) Tm;

    Tm = KpTemperOUT;
    FlashMass[96] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[97] = (unsigned char) Tm;

    //OneTwoLeg


    Tm = (int) (KiTemperOUT * 100);
    FlashMass[98] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[99] = (unsigned char) Tm;

    FlashMass[100] = MAX_PWM_Revers;
    FlashMass[101] = MaxSpdRevers;


    FlashMass[102] = MixedModeSlowSpeed;

    FlashMass[103] = HallDelay1MaxSPD_B;

    Tm = StatFlgs3.StatusFlags;
    FlashMass[104] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[105] = (unsigned char) Tm;


    FlashMass[106] = StringPINLenghtOptions;
    FlashMass[107] = PinCodeMassOptions[0];




    Tm = AutoPID_On_CntConst;
    FlashMass[108] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[109] = (unsigned char) Tm;

    FlashMass[110] = AutoPID_On_PWM;
    FlashMass[111] = AutoPID_On_Speed;

    Tm = Diametr1;
    FlashMass[112] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[113] = (unsigned char) Tm;

    Tm = PhasesPerRev1;
    FlashMass[114] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[115] = (unsigned char) Tm;

    Tm = UBatHiMem;
    FlashMass[116] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[117] = (unsigned char) Tm;



    //Fresman


    Tm = BreakThresholdDn;
    FlashMass[118] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[119] = (unsigned char) Tm;

    Tm = BreakThresholdUp;
    FlashMass[120] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[121] = (unsigned char) Tm;

    Tm = (int) (KTemperatureSPDControl * 1000);
    FlashMass[122] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[123] = (unsigned char) Tm;


    FlashMass[124] = Profile;
    FlashMass[125] = _3psnSwitchBtNotPressed;


    FlashMass[126] = _3psnSwitchBt3;
    FlashMass[127] = _3psnSwitchBt4;


    Tm = CurrPhaseLimitWork;
    FlashMass[128] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[129] = (unsigned char) Tm;

    //Tm=StartRotFreshmanL;
    FlashMass[130] = CurrSensor; //(unsigned char)Tm;
    //    Tm=Tm>>8;
    FlashMass[131] = HallDelay1MaxSPD_F;

    Tm = CurrUstSpd0;
    FlashMass[132] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[133] = (unsigned char) Tm;

    Tm = CurrPhaseLimitSpd0;
    FlashMass[134] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[135] = (unsigned char) Tm;

    Tm = CurrLimitSpd0;
    FlashMass[136] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[137] = (unsigned char) Tm;



    FlashMass[138] = MaxAngleStopBreak;

    FlashMass[139] = ThrottleTmpChngMem;


    Tm = BeepPauseConstAlm;
    FlashMass[140] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[141] = (unsigned char) Tm;


    Tm = BzOnCntSeriaConstAlm;
    FlashMass[142] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[143] = (unsigned char) Tm;


    FlashMass[144] = CntSingleBeepAlm;

    FlashMass[145] = DiffAlfaConstL;

    FlashMass[146] = DiffAlfaConstH;

    Tm = ZeroCurr1;
    FlashMass[147] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[148] = (unsigned char) Tm;


    FlashMass[149] = MaxSpd;

    FlashMass[150] = But5Func;


    Tm = Timer1Mem;
    FlashMass[151] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[152] = (unsigned char) Tm;

    Tm = Timer2Mem;
    FlashMass[153] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[154] = (unsigned char) Tm;

    FlashMass[155] = UseTmr;

    Tm = SerNumber;
    FlashMass[156] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[157] = (unsigned char) Tm;


    //OneTwoLeg1


    Tm = SensorLessCurrLimit;
    FlashMass[158] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[159] = (unsigned char) Tm;


    FlashMass[160] = SlowStrtSpd;

    FlashMass[161] = AntiPolicePower;

    Tm = SensorlessCurrUst;
    FlashMass[162] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[163] = (unsigned char) Tm;

    Tm = GyroZFlTurn;
    FlashMass[164] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[165] = (unsigned char) Tm;

    Tm = (int) (Kp_PWM_Mode * 100);
    FlashMass[166] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[167] = (unsigned char) Tm;


    Tm = Spd0TimerConst;
    FlashMass[168] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[169] = (unsigned char) Tm;


    FlashMass[170] = HallDelayMaxSPD;


    FlashMass[171] = _2WDMode;

    Tm = MAH;
    FlashMass[172] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[173] = (unsigned char) Tm;

    Tm = SensorThresholdDn;
    FlashMass[174] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[175] = (unsigned char) Tm;


    FlashMass[176] = PinCodeMassOptions[1];
    FlashMass[177] = PinCodeMassOptions[2];

    FlashMass[178] = (unsigned char) SpdRstSpeedLim;




    Tm = SensorlessCntAlignConst;
    FlashMass[179] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[180] = (unsigned char) Tm;

    Tm = SenosrlessPWM1_1Const;
    FlashMass[181] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[182] = (unsigned char) Tm;

    Tm = StatFlgs2.StatusFlags;
    FlashMass[183] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[184] = (unsigned char) Tm;


    Tm = (int) (TemperatureMaxOUT * 10);
    FlashMass[185] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[186] = (unsigned char) Tm;


    FlashMass[187] = PinCodeMassOptions[3];

    Tm = StatFlgs1.StatusFlags;
    FlashMass[188] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[189] = (unsigned char) Tm;

    Tm = SensorLessTimerConstConst;
    FlashMass[190] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[191] = (unsigned char) Tm;


    Tm = (int) (TemperatureMaxIN * 10);
    FlashMass[192] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[193] = (unsigned char) Tm;

    FlashMass[194] = PinCodeMassOptions[4];
    FlashMass[195] = PinCodeMassOptions[5];

    Tm = BigCurrent;
    FlashMass[196] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[197] = (unsigned char) Tm;


    FlashMass[198] = (unsigned char) (P_Curr * 100);

    Tm = JoystickCalibrX;
    FlashMass[199] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[200] = (unsigned char) Tm;





    Tm = SensorThresholdUp;
    FlashMass[201] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[202] = (unsigned char) Tm;

    Tm = BreakThreshold;
    FlashMass[203] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[204] = (unsigned char) Tm;

    Tm = KFirstBreak;
    FlashMass[205] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[206] = (unsigned char) Tm;

    FlashMass[207] = TemperatureTYPE;
    FlashMass[208] = SensOrder1;

    Tm = SensorlessSpdChngCntConst;
    FlashMass[209] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[210] = (unsigned char) Tm;


    Tm = V_MIN_OFF;
    FlashMass[211] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[212] = (unsigned char) Tm;

    Tm = V_MIN_Pre_OFF;
    FlashMass[213] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[214] = (unsigned char) Tm;

    Tm = V_MIN_Sound;
    FlashMass[215] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[216] = (unsigned char) Tm;

    Tm = V_min_OverV;
    FlashMass[217] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[218] = (unsigned char) Tm;


    Tm = (int) (KiCurr * 100);
    FlashMass[219] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[220] = (unsigned char) Tm;

    Tm = CurrUstWork;
    FlashMass[221] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[222] = (unsigned char) Tm;

    FlashMass[223] = (char) (KpKpMustBe * 100); //NearSensors[1][2];


    Tm = ThrottleLevelUpOff;
    FlashMass[224] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[225] = (unsigned char) Tm;


    //    FlashMass[224]=NearSensors[1][3];
    //    FlashMass[225]=NearSensors[2][2];
    FlashMass[226] = NearSensors[2][3];
    FlashMass[227] = NearSensors[3][2];
    FlashMass[228] = NearSensors[3][3];
    FlashMass[229] = NearSensors[4][2];
    FlashMass[230] = NearSensors[4][3];
    FlashMass[231] = NearSensors[5][2];
    FlashMass[232] = NearSensors[5][3];
    FlashMass[233] = NearSensors[6][2];
    FlashMass[234] = NearSensors[6][3];

    Tm = TemperatureMaxIN_H * 10;
    FlashMass[235] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[236] = (unsigned char) Tm;

    Tm = TemperatureMaxOUT_H * 10;
    FlashMass[237] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[238] = (unsigned char) Tm;


    Tm = TemperatureMaxOUT_H * 10;
    FlashMass[237] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[238] = (unsigned char) Tm;

    Tm = JoystickCalibrY;
    FlashMass[239] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[240] = (unsigned char) Tm;

    Tm = JoistickDeadZone;
    FlashMass[241] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass[242] = (unsigned char) Tm;


    OptionsToMass2();

    OptionsToMassProfile();


}

void OptionsToMass2(void) {
    int Tm = (int) 0;


    FlashMass2[0] = LightMode;



    Tm = LightSensorThresholdLo;
    FlashMass2[1] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[2] = (unsigned char) Tm;

    Tm = LightSensorThresholdHi;
    FlashMass2[3] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[4] = (unsigned char) Tm;

    FlashMass2[5] = CurrentMaxCurrentOnly;


    Tm = K_PWM_Nastr;
    FlashMass2[6] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[7] = (unsigned char) Tm;

    Tm = Khard;
    FlashMass2[8] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[9] = (unsigned char) Tm;

    FlashMass2[12] = (unsigned char) (Crr1Corr * 50);

    Tm = ButtonBreakOnlyPWM;
    FlashMass2[13] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[14] = (unsigned char) Tm;

    Tm = CntTurnOnConst;
    FlashMass2[15] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[16] = (unsigned char) Tm;

    Tm = CntTurnOffConst;
    FlashMass2[17] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[18] = (unsigned char) Tm;

    FlashMass2[19] = TemperatureTYPE_FETs;
    FlashMass2[20] = TstPhase;


    CurrPerDigit = CurrPerDigitDEF;

    Tm = (int) (CurrPerDigit * 100);
    FlashMass2[21] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[22] = (unsigned char) Tm;

    Tm = SpdStartLevel;
    FlashMass2[23] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[24] = (unsigned char) Tm;

    Tm = (int) (Ki_PWM_ModeOff * 10000);
    FlashMass2[25] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[26] = (unsigned char) Tm;

    FlashMass2[27] = StrongModeSpdFilterOffMem;

    Tm = RegenOffMem;
    FlashMass2[28] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[29] = (unsigned char) Tm;


    Tm = StatFlgs4.StatusFlags;
    FlashMass2[30] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[31] = (unsigned char) Tm;

    FlashMass2[32] = (unsigned char) KeyLightBrightness;

    Tm = ButtonBreakOnlyTime;
    FlashMass2[33] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[34] = (unsigned char) Tm;


    Tm = BreakMonocycleSpd;
    FlashMass2[35] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[36] = (unsigned char) Tm;

    KpKpDeadZoneMem = (char) (KpKpDeadZone * 10);
    FlashMass2[37] = KpKpDeadZoneMem;
    FlashMass2[38] = PWMSignal;

    Tm = (int) KpSlowSpeed;
    FlashMass2[39] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[40] = (unsigned char) Tm;

    FlashMass2[41] = SlowSpeedForKp;



    Tm = (int) (KiKpMustBe * 10);
    FlashMass2[42] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[43] = (unsigned char) Tm;

    KiKpDeadZoneMem = (char) (KiKpDeadZone * 10);
    FlashMass2[44] = KiKpDeadZoneMem;

    Tm = (int) (KiMax * 1000);
    FlashMass2[45] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[46] = (unsigned char) Tm;

    Tm = TimeDecreaseKi;
    FlashMass2[47] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[48] = (unsigned char) Tm;

    Tm = (int) KpMin;
    FlashMass2[49] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[50] = (unsigned char) Tm;

    Tm = (int) EpPWMmax;
    FlashMass2[51] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[52] = (unsigned char) Tm;

    Tm = (int) EiPWMmax;
    FlashMass2[53] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[54] = (unsigned char) Tm;

    Tm = (int) EdPWMmax;
    FlashMass2[55] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[56] = (unsigned char) Tm;

    Tm = (int) (DeadZoneHandleBarSegwayMustBe * 10);
    FlashMass2[57] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[58] = (unsigned char) Tm;

    Tm = KRotMustBe;
    FlashMass2[59] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[60] = (unsigned char) Tm;

    Tm = (int) (KpRotMustBe * 1000);
    FlashMass2[61] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[62] = (unsigned char) Tm;

    Tm = (int) (KiRotMustBe * 10000);
    FlashMass2[63] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[64] = (unsigned char) Tm;


    FlashMass2[65] = GyroVertical;
    FlashMass2[66] = HighSpeed;
    FlashMass2[67] = GoalSpeed;

    Tm = (int) (StartRotHighSpeed * 10);
    FlashMass2[68] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[69] = (unsigned char) Tm;

    Tm = KRotHighSpeed;
    FlashMass2[70] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[71] = (unsigned char) Tm;

    Tm = TimeHumanSensorOff;
    FlashMass2[72] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[73] = (unsigned char) Tm;


    Tm = (int) (KpKpZoneEnd * 10);
    FlashMass2[74] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[75] = (unsigned char) Tm;


    Tm = (int) (KpKp2MustBe * 100);
    FlashMass2[76] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[77] = (unsigned char) Tm;

    Tm = (int) (KpKp2DeadZone * 10);
    FlashMass2[78] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[79] = (unsigned char) Tm;

    Tm = (int) (KpKp2ZoneEnd * 10);
    FlashMass2[80] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[81] = (unsigned char) Tm;

    Tm = PWMChangedThreshold;
    FlashMass2[82] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[83] = (unsigned char) Tm;

    FlashMass2[84] = SpdKdMax;


    Tm = Round(KdKpSpd / (ImpToKmH1_t));
    FlashMass2[85] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[86] = (unsigned char) Tm;


    Tm = Round(KdMax / 10);
    FlashMass2[87] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[88] = (unsigned char) Tm;

    Tm = Round(KdMin / 10);
    FlashMass2[89] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[90] = (unsigned char) Tm;

    Tm = Round(KiKd / 1);
    FlashMass2[91] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[92] = (unsigned char) Tm;


    Tm = Round(((float) VectorOnOffSpdLo) * ImpToKmH1_t);
    FlashMass2[93] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[94] = (unsigned char) Tm;

    Tm = Round(((float) VectorOnOffSpdHi) * ImpToKmH1_t);
    FlashMass2[95] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[96] = (unsigned char) Tm;


    FlashMass2[97] = OnDelay;

    Tm = ((float) KiUBTCoeff)*10000;
    FlashMass2[98] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[99] = (unsigned char) Tm;

    FlashMass2[100] = SpdKiMin;

    Tm = ((float) KiMin)*1000;
    FlashMass2[101] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[102] = (unsigned char) Tm;

    Tm = ((float) ELimitedMem)*100;
    FlashMass2[103] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[104] = (unsigned char) Tm;

    Tm = (int) (KdNoManR / 10);
    FlashMass2[105] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[106] = (unsigned char) Tm;

    Tm = (int) (KpDeadZone * 10);
    FlashMass2[107] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[108] = (unsigned char) Tm;

    FlashMass2[109] = StopIfPWM100Time;
    FlashMass2[110] = CntKdSwitchCONST;

    Tm = PWMSignalTimer;
    FlashMass2[111] = (unsigned char) Tm;
    Tm = Tm >> 8;
    FlashMass2[112] = (unsigned char) Tm;

    FlashMass2[113] = PWMkHz;

}

void WriteOptions(void) {
    int Tm;
    unsigned char Chk;

    OptionsToMass();

    WriteStat_FLASH(0);
    EraseSector_FLASH(0);



    Chk = CalcCheckSumm(sizeof (FlashMass), FlashMass);

    for (Tm = 0; Tm<sizeof (FlashMass); Tm++)
        WriteByte_FLASH((unsigned long int) Tm, FlashMass[Tm]);
    WriteByte_FLASH((unsigned long int) Tm, Chk);


    Chk = CalcCheckSumm(sizeof (ProfileMass), ProfileMass);

    for (Tm = sizeof (FlashMass) + 1; Tm < (sizeof (ProfileMass) + sizeof (FlashMass) + 1); Tm++)
        WriteByte_FLASH((unsigned long int) Tm, ProfileMass[Tm - 1 - sizeof (FlashMass)]);
    WriteByte_FLASH((unsigned long int) Tm, Chk);



    Chk = CalcCheckSumm(sizeof (FlashMass2), FlashMass2);

    for (Tm = sizeof (FlashMass) + sizeof (ProfileMass) + 2; Tm < (sizeof (FlashMass) + sizeof (FlashMass) + sizeof (ProfileMass) + 2); Tm++)
        WriteByte_FLASH((unsigned long int) Tm, FlashMass2[Tm - (sizeof (FlashMass) + sizeof (ProfileMass) + 2)]);
    WriteByte_FLASH((unsigned long int) Tm, Chk);





    WriteStat_FLASH(0x3c);

}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void MassToOptions(void) {
    ErrOptions = 0;
    int Tm = FlashMass[2];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[1];
    KpMustBe = Tm;

    /*  if (KpMustBe>700)
      {
        
          KpNoMan=150;
          SetKpMustBe_UP();
          ErrOptions=KpMustBeErr;
      }
     */


    Tm = FlashMass[4];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[3];
    KpNoMan = Tm;

    Tm = FlashMass[6];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[5];
    KdNoMan = Tm;

    KdNoMan = KdNoMan * 10;






    Tm = FlashMass[8];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[7];
    KiNoMan = Tm;

    /*  if (KiNoMan>15000)
      {
          KiNoMan=450;
          ErrOptions=KiErr;
      }
     */
    KiNoMan = KiNoMan / 100;

    Tm = FlashMass[10];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[9];
    KpKpSpd = (float) Tm;
    KpKpSpd = KpKpSpd / 20;

    But1Func = FlashMass[11];
    But2Func = FlashMass[12];


    Tm = FlashMass[14];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[13];
    KGYRO = Tm;


    if (KGYRO > 1000) {
        KGYRO = 997;
        ErrOptions = KGYROErr;
    }

    KGYRO = KGYRO / 1000;
    KACC = 1 - KGYRO;




    Tm = FlashMass[16];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[15];
    SensorLessTimerConst2 = Tm;



    Tm = FlashMass[18];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[17];
    SenosrlessPWM1_2Const = Tm;



    Tm = FlashMass[20];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[19];
    SensorLessTimerConstMin = Tm;


    Tm = FlashMass[22];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[21];
    CalibrationGyroX = Tm;

    /*if ((CalibrationGyroX>2000)||(CalibrationGyroX<-2000))
    {
        CalibrationGyroX=0;
        ErrOptions=CalibrationGyroXErr;
    }*/


    Tm = FlashMass[24];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[23];
    CalibrationGyroY = Tm;

    /*  if ((CalibrationGyroY>2000)||(CalibrationGyroY<-2000))
      {
          CalibrationGyroY=0;
          ErrOptions=CalibrationGyroYErr;
      }
     */

    Tm = FlashMass[26];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[25];
    CalibrationGyroZ = Tm;

    /*  if ((CalibrationGyroZ>2000)||(CalibrationGyroZ<-2000))
      {
          CalibrationGyroZ=0;
          ErrOptions=CalibrationGyroZErr;
      }
     */


    Tm = FlashMass[28];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[27];
    CalibrationAccX = Tm;

    /*  if ((CalibrationAccX>1000)||(CalibrationAccX<-1000))
      {
          CalibrationAccX=0;
          ErrOptions=CalibrationAccXErr;
      }
     */

    Tm = FlashMass[30];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[29];
    CalibrationAccY = Tm;

    /*  if ((CalibrationAccY>1000)||(CalibrationAccY<-1000))
      {
          CalibrationAccY=0;
          ErrOptions=CalibrationAccYErr;
      }
     */

    Tm = FlashMass[32];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[31];
    CalibrationAccZ = Tm;

    PhasePERMASS = FlashMass[33];
    PhasePERMASS_SHFT = FlashMass[34];





    /*  if ((KRotNoMan>1000)||(KRotNoMan<0))
      {
          KRotNoMan=100;
          ErrOptions=KRotErr;
      }
     */
    HallDelayMem1_F = FlashMass[35];
    HallDelayMem1_B = FlashMass[36];
    But3Func = FlashMass[37];
    But4Func = FlashMass[38];


    Theta1Zero = FlashMass[39];
    Theta2Zero = FlashMass[40];



    Tm = FlashMass[42];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[41];
    CurrLimitWork = Tm;



    Tm = FlashMass[44];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[43];
    ChagerCurr = Tm;


    //    ChagerCurr=FlashMass[43];
    //    P_Curr=FlashMass[44];




    Tm = FlashMass[46];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[45];
    KpSPDMove = Tm;

    /*      if ((KpSPDMove>100)||(KpSPDMove<0))
      {
          KpSPDMove=4;
          ErrOptions=KpSPDErr;
      }
     */


    Tm = FlashMass[48];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[47];
    KdSPD = Tm;
    //KdSPD=KdSPD/10000;

    Tm = FlashMass[50];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[49];
    KiSPD = Tm;
    //KiSPD=KiSPD/10000;

    Tm = FlashMass[52];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[51];
    AngleLimitMove = Tm;

    /*      if ((AngleLimitMove>50)||(AngleLimitMove<0))
      {
          AngleLimitMove=5;
          ErrOptions=AngleLimitErr;
      }
     */


    Tm = FlashMass[54];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[53];
    SpeedLimit1 = Tm;


    Tm = FlashMass[56];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[55];
    StatFlgs.StatusFlags = Tm;

    Tm = FlashMass[58];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[57];
    XLimit = Tm;

    /*  if ((XLimit>90)||(XLimit<0))
      {
          XLimit=30;
          ErrOptions=XLimitErr;
      }
     */
    Tm = FlashMass[60];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[59];
    YLimit = Tm;

    /*  if ((YLimit>90)||(YLimit<0))
      {
          YLimit=12;
          ErrOptions=YLimitErr;
      }
     */

    Tm = FlashMass[62];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[61];
    UBatLow = Tm;

    /*  if (UBatLow>70)
      {
          UBatLow=41;
          ErrOptions=UBatLowErr;
      }
     */
#if !defined VECTOR
#if !defined ISOLATED                               
    float UBtFl = (float) UBatLow * (float) 38.388;
    UBtLim1 = (unsigned int) UBtFl;
    UBtLim2 = UBtLim1 + 115;
#else
    float UBtFl = (float) UBatLow / (float) 0.4167965;
    UBtLim1 = (unsigned int) UBtFl;
    UBtLim2 = UBtLim1 + 7;
#endif
#else
    float UBtFl = (float) UBatLow * (float) 38.388;
    UBtLim1 = (unsigned int) UBtFl;
    UBtLim2 = UBtLim1 + 115;
#endif
    Tm = FlashMass[64];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[63];
    CntMixedModeMax = Tm;


    Tm = FlashMass[66];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[65];
    MixedModeLevelOn = Tm;



    SpeedLimit2 = FlashMass[67];

    SpeedLimit3 = FlashMass[68];

    I_Curr = (float) FlashMass[69];
    I_Curr = I_Curr / 100;



    Tm = FlashMass[71];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[70];
    CurrMixed = Tm;


    Tm = FlashMass[73];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[72];
    KpMax = (float) Tm;



    SensorllessSpdThreshold = FlashMass[74];


    SpdKpMax = FlashMass[75];

    Tm = FlashMass[77];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[76];
    MixedModeLevelOff = Tm;

    Tm = FlashMass[79];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[78];
    KpCurr = Tm;
    KpCurr = KpCurr / 100;

    Tm = FlashMass[81];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[80];
    Ki_PWM_Mode = Tm;
    Ki_PWM_Mode = Ki_PWM_Mode / 10000;

    P_U = FlashMass[82];
    I_U = FlashMass[83];


    Tm = FlashMass[85];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[84];
    KpWheelingMem = Tm;
    KpMustBe = KpWheelingMem;
    SetKpMustBe_UP();



    Tm = FlashMass[87];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[86];
    KiWheelingMem = Tm;
    KiWheelingMem = KiWheelingMem / 1000;
    KiMustBe = KiWheelingMem;
    SetKi_UP();


    Tm = FlashMass[89];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[88];
    TiltZadWheeling = ((float) Tm) / 10;
    TiltZadTmp = TiltZadWheeling;

    Tm = FlashMass[91];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[90];
    MAX_PWM_MEM = Tm;


    Tm = FlashMass[93];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[92];
    KiTemperIN = Tm;
    KiTemperIN = KiTemperIN / 100;

    Tm = FlashMass[95];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[94];
    KpTemperIN = Tm;

    Tm = FlashMass[97];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[96];
    KpTemperOUT = Tm;


    //OneTwoLeg
    Tm = FlashMass[99];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[98];
    KiTemperOUT = Tm;
    KiTemperOUT = KiTemperOUT / 100;




    MAX_PWM_Revers = FlashMass[100];
    MaxSpdRevers = FlashMass[101];




    MixedModeSlowSpeed = FlashMass[102];
    HallDelay1MaxSPD_B = FlashMass[103];

    Tm = FlashMass[105];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[104];
    StatFlgs3.StatusFlags = Tm;

    StringPINLenghtOptions = FlashMass[106];
    PinCodeMassOptions[0] = FlashMass[107];

#if !defined BLE
    StringPINLenghtOptions = 0;
#endif

    Tm = FlashMass[109];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[108];
    AutoPID_On_CntConst = Tm;

    AutoPID_On_PWM = FlashMass[110];
    AutoPID_On_Speed = FlashMass[111];

    Tm = FlashMass[113];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[112];
    Diametr1 = Tm;

    Tm = FlashMass[115];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[114];
    PhasesPerRev1 = Tm;

    CmImp1_t = (float) Diametr1 * 0.314159 / (float) PhasesPerRev1;
    ImpToKmH1_t = CmImp1_t * 0.36;





    Tm = FlashMass[117];
    Tm = Tm << 8;
    UBatHiMem = Tm + FlashMass[116];
    UBatHi = (unsigned int) ((float) UBatHiMem * (float) 38.388);



    //Freshman
    Tm = FlashMass[119];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[118];
    BreakThresholdDn = Tm;

    Tm = FlashMass[121];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[120];
    BreakThresholdUp = Tm;

    Tm = FlashMass[123];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[122];
    KTemperatureSPDControl = ((float) Tm) / 1000;


    Profile = FlashMass[124];
    _3psnSwitchBtNotPressed = FlashMass[125];


    _3psnSwitchBt4 = FlashMass[127];
    _3psnSwitchBt3 = FlashMass[126];



    Tm = FlashMass[129];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[128];
    CurrPhaseLimitWork = Tm;

    HallDelay1MaxSPD_F = FlashMass[131];
    CurrSensor = FlashMass[130];


    Tm = FlashMass[133];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[132];
    CurrUstSpd0 = Tm;

    Tm = FlashMass[135];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[134];
    CurrPhaseLimitSpd0 = Tm;

    Tm = FlashMass[137];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[136];
    CurrLimitSpd0 = Tm;


    MaxAngleStopBreak = FlashMass[138];
    ThrottleTmpChngMem = FlashMass[139];

    Tm = FlashMass[141];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[140];
    BeepPauseConstAlm = Tm;

    Tm = FlashMass[143];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[142];
    BzOnCntSeriaConstAlm = Tm;

    CntSingleBeepAlm = FlashMass[144];
    DiffAlfaConstL = FlashMass[145];
    DiffAlfaConstH = FlashMass[146];


    Tm = FlashMass[148];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[147];
    ZeroCurr1 = Tm;


    MaxSpd = FlashMass[149];



    But5Func = FlashMass[150];


    Tm = FlashMass[152];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[151];
    Timer1Mem = Tm;


    Tm = FlashMass[154];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[153];
    Timer2Mem = Tm;


    UseTmr = FlashMass[155];

    Tm = FlashMass[157];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[156];
    SerNumber = Tm;




    //OneTwoLeg1
    Tm = FlashMass[159];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[158];
    SensorLessCurrLimit = Tm;




    SlowStrtSpd = FlashMass[160];
    AntiPolicePower = FlashMass[161];




    Tm = FlashMass[163];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[162];
    SensorlessCurrUst = Tm;

    Tm = FlashMass[165];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[164];
    GyroZFlTurn = Tm;



    Tm = FlashMass[167];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[166];
    Kp_PWM_Mode = Tm;
    Kp_PWM_Mode = Kp_PWM_Mode / 100;

    Tm = FlashMass[169];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[168];
    Spd0TimerConst = Tm;

    _2WDMode = FlashMass[171];

    HallDelayMaxSPD = FlashMass[170];


    Tm = FlashMass[173];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[172];
    MAH = Tm;

    Tm = FlashMass[175];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[174];
    SensorThresholdDn = Tm;







    PinCodeMassOptions[1] = FlashMass[176];
    PinCodeMassOptions[2] = FlashMass[177];



    SpdRstSpeedLim = (unsigned int) FlashMass[178];

    Tm = FlashMass[180];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[179];
    SensorlessCntAlignConst = Tm;


    Tm = FlashMass[182];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[181];
    SenosrlessPWM1_1Const = Tm;

    Tm = FlashMass[184];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[183];
    StatFlgs2.StatusFlags = Tm;

    Tm = FlashMass[186];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[185];
    TemperatureMaxOUT = Tm;
    TemperatureMaxOUT = TemperatureMaxOUT / 10;



    PinCodeMassOptions[3] = FlashMass[187];

    Tm = FlashMass[189];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[188];
    StatFlgs1.StatusFlags = Tm;

    Tm = FlashMass[191];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[190];
    SensorLessTimerConstConst = Tm;



    Tm = FlashMass[193];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[192];
    TemperatureMaxIN = Tm;
    TemperatureMaxIN = TemperatureMaxIN / 10;

    PinCodeMassOptions[4] = FlashMass[194];
    PinCodeMassOptions[5] = FlashMass[195];


    Tm = FlashMass[197];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[196];
    BigCurrent = Tm;


    P_Curr = (float) FlashMass[198];
    P_Curr = P_Curr / 100;

    Tm = FlashMass[199];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[200];
    JoystickCalibrX = Tm;






    Tm = FlashMass[202];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[201];
    SensorThresholdUp = Tm;

    Tm = FlashMass[204];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[203];
    BreakThreshold = Tm;
    KThreshold = (long int) ((((float) MAX_PWM) / (MAX_PWM - BreakThreshold))*256);
    KThresholdBreak = (long int) ((((float) MAX_PWM) / (BreakThreshold))*256);

    Tm = FlashMass[206];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[205];
    KFirstBreak = Tm;

    TemperatureTYPE = FlashMass[207];
    SensOrder1 = FlashMass[208];

    Tm = FlashMass[210];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[209];
    SensorlessSpdChngCntConst = Tm;

    Tm = FlashMass[212];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[211];
    V_MIN_OFF = Tm;

    Tm = FlashMass[214];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[213];
    V_MIN_Pre_OFF = Tm;

    Tm = FlashMass[216];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[215];
    V_MIN_Sound = Tm;

    Tm = FlashMass[218];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[217];
    V_min_OverV = Tm;


    Tm = FlashMass[220];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[219];
    KiCurr = Tm;
    KiCurr = KiCurr / 100;


    Tm = FlashMass[222];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[221];
    CurrUstWork = Tm;




    //NearSensors[1][2]
    KpKpMustBe = (float) ((char) FlashMass[223]);
    KpKpMustBe = KpKpMustBe / (float) 100;

    Tm = FlashMass[225];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[224];
    ThrottleLevelUpOff = Tm;





    //NearSensors[1][3]=FlashMass[224];
    //NearSensors[2][2]=FlashMass[225];
    NearSensors[2][3] = FlashMass[226];
    NearSensors[3][2] = FlashMass[227];
    NearSensors[3][3] = FlashMass[228];
    NearSensors[4][2] = FlashMass[229];
    NearSensors[4][3] = FlashMass[230];
    NearSensors[5][2] = FlashMass[231];
    NearSensors[5][3] = FlashMass[232];
    NearSensors[6][2] = FlashMass[233];
    NearSensors[6][3] = FlashMass[234];


    Tm = FlashMass[236];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[235];
    TemperatureMaxIN_H = Tm;
    TemperatureMaxIN_H = TemperatureMaxIN_H / 10;




    Tm = FlashMass[238];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[237];
    TemperatureMaxOUT_H = Tm;
    TemperatureMaxOUT_H = TemperatureMaxOUT_H / 10;


    Tm = FlashMass[240];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[239];
    JoystickCalibrY = Tm;

    Tm = FlashMass[242];
    Tm = Tm << 8;
    Tm = Tm + FlashMass[241];
    JoistickDeadZone = Tm;



    DirPWM1Mem = DirPWM1;






    if (ErrOptions) {
        SoundNum = 9;
        //EEPROM_Limit_ERR=1;

    }


    MassToOptions2();


    MassToOptionsProfile();
    /*
        if (StrongModeMem)
            StrongMode=1;
        else
            StrongMode=0;
    
    if ((VectorMem)&&(!Sensorless))
        Vector=1;
    else
        Vector=0;

    if (!Sensorless)
        CurrUst=CurrUstWork;
    else
        CurrUst=SensorlessCurrUst;


    if (!Sensorless)
        CurrLimit=CurrLimitWork;
    else
    CurrLimit=SensorLessCurrLimit;
    ChangeCVR();

    MAX_PWM_MustBe=MAX_PWM_MEM;
    if (MAX_PWM_MEM>100)
        MAX_PWM_MEM=100;
    
    MaxSpdCoeff=(int)(((float)MAX_PWM)/((float)MaxSpd/ImpToKmH1_t));
     */


    //NoAutoTrm=1;
}

void MassToOptions2(void) {
    int Tm;

    LightMode = FlashMass2[0];



    Tm = FlashMass2[2];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[1];
    LightSensorThresholdLo = Tm;

    Tm = FlashMass2[4];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[3];
    LightSensorThresholdHi = Tm;

    CurrentMaxCurrentOnly = FlashMass2[5];


    Tm = FlashMass2[7];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[6];
    K_PWM_Nastr = Tm;

    Tm = FlashMass2[9];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[8];
    Khard = Tm;

    Crr1Corr = (float) FlashMass2[12];
    Crr1Corr = Crr1Corr / 50;

    Tm = FlashMass2[14];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[13];
    ButtonBreakOnlyPWM = Tm;

    Tm = FlashMass2[16];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[15];
    CntTurnOnConst = Tm;


    Tm = FlashMass2[18];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[17];
    CntTurnOffConst = Tm;

    TemperatureTYPE_FETs = FlashMass2[19];

    TstPhase = FlashMass2[20];


    Tm = FlashMass2[22];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[21];
    CurrPerDigit = Tm;
    CurrPerDigit = CurrPerDigit / 100;



    Tm = FlashMass2[24];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[23];
    SpdStartLevel = Tm;

    Tm = FlashMass2[26];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[25];
    Ki_PWM_ModeOff = Tm;
    Ki_PWM_ModeOff = Ki_PWM_ModeOff / 10000;


    StrongModeSpdFilterOffMem = FlashMass2[27];
    StrongModeSpdFilterOff = ((float) StrongModeSpdFilterOffMem) / ImpToKmH1_t;

    Tm = FlashMass2[29];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[28];
    RegenOffMem = Tm;

    Tm = FlashMass2[31];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[30];
    StatFlgs4.StatusFlags = Tm;

    KeyLightBrightness = FlashMass2[32];


    Tm = FlashMass2[34];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[33];
    ButtonBreakOnlyTime = Tm;

    Tm = FlashMass2[36];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[35];
    BreakMonocycleSpd = Tm;


    KpKpDeadZoneMem = FlashMass2[37];
    KpKpDeadZone = ((float) (KpKpDeadZoneMem)) / 10;


    PWMSignal = FlashMass2[38];


    Tm = FlashMass2[40];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[39];
    KpSlowSpeed = Tm;

    SlowSpeedForKp = FlashMass2[41];



    Tm = FlashMass2[43];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[42];
    KiKpMustBe = Tm;
    KiKpMustBe = KiKpMustBe / 10;

    KiKpDeadZoneMem = FlashMass2[44];
    KiKpDeadZone = ((float) (KiKpDeadZoneMem)) / 10;

    Tm = FlashMass2[46];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[45];
    KiMax = (unsigned int) Tm;
    KiMax = KiMax / 1000;

    Tm = FlashMass2[48];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[47];
    TimeDecreaseKi = Tm;

    Tm = FlashMass2[50];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[49];
    KpMin = (float) Tm;


    Tm = FlashMass2[52];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[51];
    EpPWMmax = (float) Tm;

    Tm = FlashMass2[54];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[53];
    EiPWMmax = (float) Tm;

    Tm = FlashMass2[56];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[55];
    EdPWMmax = (float) Tm;

    Tm = FlashMass2[58];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[57];
    DeadZoneHandleBarSegwayMustBe = (float) Tm;
    DeadZoneHandleBarSegwayMustBe = DeadZoneHandleBarSegwayMustBe / 10;

    Tm = FlashMass2[60];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[59];
    KRotMustBe = (int) Tm;

    Tm = FlashMass2[62];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[61];
    KpRotMustBe = (float) Tm;
    KpRotMustBe = KpRotMustBe / 1000;

    Tm = FlashMass2[64];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[63];
    KiRotMustBe = (float) Tm;
    KiRotMustBe = KiRotMustBe / 10000;

    GyroVertical = FlashMass2[65];





    HighSpeed = FlashMass2[66];
    GoalSpeed = FlashMass2[67];
    HighSpeedQuantum();

    Tm = FlashMass2[69];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[68];
    StartRotHighSpeed = (int) Tm;
    StartRotHighSpeed = StartRotHighSpeed / 10;

    Tm = FlashMass2[71];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[70];
    KRotHighSpeed = (int) Tm;

    Tm = FlashMass2[73];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[72];
    TimeHumanSensorOff = (int) Tm;

    Tm = FlashMass2[75];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[74];
    KpKpZoneEnd = (float) Tm;

    KpKpZoneEnd = KpKpZoneEnd / 10;


    Tm = FlashMass2[77];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[76];
    KpKp2MustBe = (float) Tm;
    KpKp2MustBe = KpKp2MustBe / 100;

    Tm = FlashMass2[79];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[78];
    KpKp2DeadZone = (float) Tm;
    KpKp2DeadZone = KpKp2DeadZone / 10;

    Tm = FlashMass2[81];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[80];
    KpKp2ZoneEnd = (float) Tm;
    KpKp2ZoneEnd = KpKp2ZoneEnd / 10;


    Tm = FlashMass2[83];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[82];
    PWMChangedThreshold = Tm;




    SpdKdMax = FlashMass2[84];



    Tm = FlashMass2[86];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[85];
    KdKpSpd = Tm;
    KdKpSpd = KdKpSpd * (ImpToKmH1_t);




    Tm = FlashMass2[88];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[87];
    KdMax = Tm;
    KdMax = KdMax * 10;


    Tm = FlashMass2[90];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[89];
    KdMin = Tm;
    KdMin = KdMin * 10;


    Tm = FlashMass2[92];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[91];
    KiKd = Tm;
    KiKd = KiKd * 1;

    Tm = FlashMass2[94];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[93];
    VectorOnOffSpdLo = Round(((float) Tm) / ImpToKmH1_t);

    Trapezium10kHzLo = Round(((float) 38) / ImpToKmH1_t);
    Trapezium10kHzHi = Round(((float) 40) / ImpToKmH1_t);
    Trapezium5kHzLo = Round(((float) 18) / ImpToKmH1_t);
    Trapezium5kHzHi = Round(((float) 20) / ImpToKmH1_t);





    Tm = FlashMass2[96];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[95];
    VectorOnOffSpdHi = Round(((float) Tm) / ImpToKmH1_t);

    OnDelay = FlashMass2[97];
    OnDelayConst = ((int) OnDelay)*250;


    Tm = FlashMass2[99];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[98];
    KiUBTCoeff = ((float) Tm) / 10000;

    SpdKiMin = FlashMass2[100];


    Tm = FlashMass2[102];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[101];
    KiMin = ((float) Tm) / 1000;


    Tm = FlashMass2[104];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[103];
    ELimitedMem = ((float) Tm) / 100;


    Tm = FlashMass2[106];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[105];
    KdNoManR = ((float) Tm) *10;


    Tm = FlashMass2[108];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[107];
    KpDeadZone = ((float) Tm) / 10;


    StopIfPWM100Time = FlashMass2[109];
    CntKdSwitchCONST = FlashMass2[110];


    Tm = FlashMass2[112];
    Tm = Tm << 8;
    Tm = Tm + FlashMass2[111];
    PWMSignalTimer = Tm;


    PWMkHz = FlashMass2[113];






    switch (PWMkHz) {
        case 1:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
            break;
        case 2:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE10kHz;
            TrapezoidaWhenBigSpeed = 1;
            if (VectorOnOffSpdLo > Trapezium10kHzLo)
                VectorOnOffSpdLo = Trapezium10kHzLo;
            if (VectorOnOffSpdHi > Trapezium10kHzHi)
                VectorOnOffSpdHi = Trapezium10kHzHi;
            break;
        case 3:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE5kHz;
            TrapezoidaWhenBigSpeed = 1;
            if (VectorOnOffSpdLo > Trapezium5kHzLo)
                VectorOnOffSpdLo = Trapezium5kHzLo;
            if (VectorOnOffSpdHi > Trapezium5kHzHi)
                VectorOnOffSpdHi = Trapezium5kHzHi;
            break;
        default:
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
            PWMkHz = 1;
            break;
    }



    MAX_PWM = MAX_PWM_CONST;
    PHASE1 = MAX_PWM + DEADTIME + Khard;
    PHASE2 = MAX_PWM + DEADTIME + Khard;
    PHASE3 = MAX_PWM + DEADTIME + Khard;




#if !defined VECTOR

#if !defined ISOLATED
    RegenOff = (unsigned int) ((float) RegenOffMem * (float) 38.388);
#else
    RegenOff = (unsigned int) ((float) RegenOffMem / (float) 0.4167965);
#endif
#else
    RegenOff = (unsigned int) ((float) RegenOffMem * (float) 38.388);
#endif






    SpdStartLevelFl = ((float) SpdStartLevel) / ImpToKmH1_t;
    CurrentMaxCurrentOnlyWork = ((float) CurrentMaxCurrentOnly * 1000/**Crr1Corr*/) / CurrPerDigit;

    //Mgnovenniy = 0;
}

void Comparator3_Init(void) {
    CM3CONbits.CON = 0;
    CM3CONbits.COE = 0; //OUTPUT
    CM3CONbits.CPOL = 1; //POLARITY
    CM3CONbits.EVPOL = 3;
    CM3CONbits.CREF = 1;
    CM3CONbits.CCH = 1; //C3IN1
    CM3CONbits.CEVT = 1;


    CVRCONbits.VREFSEL = 0; //CVrefin
    CVRCONbits.CVREN = 1;
    CVRCONbits.CVRR = 0;
    CVRCONbits.CVRSS = 0;
    ChangeCVR();


    CM3FLTRbits.CFDIV = 0b011;
    //  CM3FLTRbits.CFLTREN=1;

    CM3CONbits.CON = 1;



    IEC1bits.CMIE = 0;
    IFS1bits.CMIF = 0;

    //RPOR7bits.RP97R=0b011010;

}

void ChangeCVR(void) {
#if defined REV2 
    switch (CurrLimit) {
        case 15:
            CVRCONbits.CVR = 0; //0A
            break;
        case 14:
            CVRCONbits.CVR = 1; //181A
            break;
        case 13:
            CVRCONbits.CVR = 2; //170A
            break;
        case 12:
            CVRCONbits.CVR = 3; //160A
            break;
        case 11:
            CVRCONbits.CVR = 4; //150A
            break;
        case 10:
            CVRCONbits.CVR = 5; //139A
            break;
        case 9:
            CVRCONbits.CVR = 6; //129A
            break;
        case 8:
            CVRCONbits.CVR = 7; //118A
            break;
        case 7:
            CVRCONbits.CVR = 8; //108A
            break;
        case 6:
            CVRCONbits.CVR = 9; //97.6A
            break;
        case 5:
            CVRCONbits.CVR = 10; //87.2A
            break;
        case 4:
            CVRCONbits.CVR = 11; //76.8A
            break;
        case 3:
            CVRCONbits.CVR = 12; //66.4A
            break;
        case 2:
            CVRCONbits.CVR = 13; //56A
            break;
        case 1:
            CVRCONbits.CVR = 14; //46A
            break;
        case 0:
            CVRCONbits.CVR = 15; //35A
            break;
    }
#else    
    switch (CurrLimit) {
        case 0:
            CVRCONbits.CVR = 0; //0A
            break;
        case 1:
            CVRCONbits.CVR = 1; //10A
            break;
        case 2:
            CVRCONbits.CVR = 2; //20A
            break;
        case 3:
            CVRCONbits.CVR = 3; //30A
            break;
        case 4:
            CVRCONbits.CVR = 4; //40A
            break;
        case 5:
            CVRCONbits.CVR = 5; //50A
            break;
        case 6:
            CVRCONbits.CVR = 6; //60A
            break;
        case 7:
            CVRCONbits.CVR = 7; //70A
            break;
        case 8:
            CVRCONbits.CVR = 8; //80A
            break;
        case 9:
            CVRCONbits.CVR = 9; //90A
            break;
        case 10:
            CVRCONbits.CVR = 10; //100A
            break;
        case 11:
            CVRCONbits.CVR = 11; //110A
            break;
        case 12:
            CVRCONbits.CVR = 12; //120A
            break;
        case 13:
            CVRCONbits.CVR = 13; //130A
            break;
        case 14:
            CVRCONbits.CVR = 14; //140A
            break;
        case 15:
            CVRCONbits.CVR = 15; //150A
            break;

    }
#endif
}

void Comparator2_Init(void) {
    CM2CONbits.CON = 0;
    CM2CONbits.COE = 1; //OUTPUT
    if (ShortCircuit)
        CM2CONbits.CPOL = 0; //1;//POLARITY
    else
        CM2CONbits.CPOL = 1; //POLARITY

    CM2CONbits.EVPOL = 3;
    CM2CONbits.CREF = 1;
    CM2CONbits.CCH = 1; //C3IN1
    CM2CONbits.CEVT = 1;


    CVRCONbits.VREFSEL = 0; //CVrefin
    CVRCONbits.CVREN = 1;
#if defined REV2
    CVRCONbits.CVRR = 1;
#else
    CVRCONbits.CVRR = 0;
#endif    
    CVRCONbits.CVRSS = 0;
    ChangeCVR();


    CM2FLTRbits.CFDIV = 0b011;
    CM2FLTRbits.CFLTREN = 1;

    CM2CONbits.CON = 1;



    IEC1bits.CMIE = 0;
    IFS1bits.CMIF = 0;



}

void WriteOdometr(void) {

    unsigned char Ch[4];

    Ch[0] = (unsigned char) Odometr;
    Ch[1] = (unsigned char) (Odometr >> 8);
    Ch[2] = (unsigned char) (Odometr >> 16);
    Ch[3] = (unsigned char) (Odometr >> 24);


    WriteStat_FLASH(0);

    WriteByte_FLASH((unsigned long int) 4096, Ch[0]);
    WriteByte_FLASH((unsigned long int) 4097, Ch[1]);
    WriteByte_FLASH((unsigned long int) 4098, Ch[2]);
    WriteByte_FLASH((unsigned long int) 4099, Ch[3]);

    WriteStat_FLASH(0x3c);

}

void ReadOdometr(void) {
    unsigned char Ch[24];
    unsigned long int SectorAddr = 8192;


    ReadFlash(SectorAddr, sizeof (Ch), Ch);
    Odometr = (((unsigned long int) Ch[3]) << 24)+(((unsigned long int) Ch[2]) << 16)+(((unsigned long int) Ch[1]) << 8)+(unsigned long int) Ch[0];
    CurrTuda1 = (((unsigned long int) Ch[7]) << 24)+(((unsigned long int) Ch[6]) << 16)+(((unsigned long int) Ch[5]) << 8)+(unsigned long int) Ch[4];
    CurrRegen1 = (((unsigned long int) Ch[11]) << 24)+(((unsigned long int) Ch[10]) << 16)+(((unsigned long int) Ch[9]) << 8)+(unsigned long int) Ch[8];
    CurrTuda2 = (((unsigned long int) Ch[15]) << 24)+(((unsigned long int) Ch[14]) << 16)+(((unsigned long int) Ch[13]) << 8)+(unsigned long int) Ch[12];
    CurrRegen2 = (((unsigned long int) Ch[19]) << 24)+(((unsigned long int) Ch[18]) << 16)+(((unsigned long int) Ch[17]) << 8)+(unsigned long int) Ch[16];
    Distance = (((unsigned long int) Ch[23]) << 24)+(((unsigned long int) Ch[22]) << 16)+(((unsigned long int) Ch[21]) << 8)+(unsigned long int) Ch[20];

}

void WriteOdometrNew(void) {
    unsigned long int SectorAddr;
    unsigned char Ch[24], k;

    //return;
    SectorAddr = 8192; //4096*OdometrSectorNum;

    /*  Odometr=0x12345678;
      CurrTuda1=0x90abcdef;
      CurrRegen1=0x567890ab;
      CurrTuda2=0xcdef1234;
      CurrRegen2=0x12345678;
      Distance=0x90abcdef;
     */

    Ch[0] = (unsigned char) Odometr;
    Ch[1] = (unsigned char) (Odometr >> 8);
    Ch[2] = (unsigned char) (Odometr >> 16);
    Ch[3] = (unsigned char) (Odometr >> 24);

    Ch[4] = (unsigned char) CurrTuda1;
    Ch[5] = (unsigned char) (CurrTuda1 >> 8);
    Ch[6] = (unsigned char) (CurrTuda1 >> 16);
    Ch[7] = (unsigned char) (CurrTuda1 >> 24);

    Ch[8] = (unsigned char) CurrRegen1;
    Ch[9] = (unsigned char) (CurrRegen1 >> 8);
    Ch[10] = (unsigned char) (CurrRegen1 >> 16);
    Ch[11] = (unsigned char) (CurrRegen1 >> 24);

    Ch[12] = (unsigned char) CurrTuda2;
    Ch[13] = (unsigned char) (CurrTuda2 >> 8);
    Ch[14] = (unsigned char) (CurrTuda2 >> 16);
    Ch[15] = (unsigned char) (CurrTuda2 >> 24);

    Ch[16] = (unsigned char) CurrRegen2;
    Ch[17] = (unsigned char) (CurrRegen2 >> 8);
    Ch[18] = (unsigned char) (CurrRegen2 >> 16);
    Ch[19] = (unsigned char) (CurrRegen2 >> 24);

    Ch[20] = (unsigned char) Distance;
    Ch[21] = (unsigned char) (Distance >> 8);
    Ch[22] = (unsigned char) (Distance >> 16);
    Ch[23] = (unsigned char) (Distance >> 24);

    WriteStat_FLASH(0);
    EraseSector_FLASH(SectorAddr);
    WriteStat_FLASH(0x3c);


    WriteStat_FLASH(0);

    for (k = 0; k<sizeof (Ch); k++)
        WriteByte_FLASH(SectorAddr + k, Ch[k]);


    WriteStat_FLASH(0x3c);
    Nop();
    Nop();
    Nop();
    Nop();
    /*
        if (OdometrSectorNum>1)
            OdometrSectorNum--;
        else
            OdometrSectorNum=OdometrSectorNumConst-1;
        SectorAddr=4096*OdometrSectorNum;

        WriteStat_FLASH(0);
        EraseSector_FLASH(SectorAddr);
        WriteStat_FLASH(0x3c);

        OdometrSectorNum++;
        if (OdometrSectorNum>=OdometrSectorNumConst)
            OdometrSectorNum=1;
        OdometrSectorNum++;
        if (OdometrSectorNum>=OdometrSectorNumConst)
            OdometrSectorNum=1;
     */
}

void WrOdmtr(void) {
    if (!RecOdometrFl)
        return;
    RecOdometrFl = 0;
    if (Beep_10m) {
        SoundNum = 12;
    }

    WriteOdometrNew();
    Nop();
    Nop();
    Nop();
    ReadOdometr();
    Nop();
    Nop();
    Nop();

    /*
    if (Beep_10m)
    {
    SingleBeep=1;
   BzOnCnt=0;
   BzOnCntConst=50;
   BuzzerMacroOn//Buzzer=1;
    }
   SendPhase=1;*/
}

void Buttons(void) {
#if !defined REV2
    unsigned char HvBt1Tmp, HvBt2Tmp, HvBt3Tmp, HvBt4Tmp, HvBt5Tmp;
    unsigned char Bt1UpTmp, Bt2UpTmp, Bt3UpTmp, Bt4UpTmp, Bt5UpTmp;
#endif
    if (StartingBTN) {
        if (!But1) {
            But1Pressed = 1;
            HvBt1 = 1;
        } else {
            But1Pressed = 0;
            Bt1Up = 1;
        }
        if (!But2) {
            But2Pressed = 1;
            HvBt2 = 1;
        } else {
            But2Pressed = 0;
            Bt2Up = 1;
        }
        if (!But3) {
            But3Pressed = 1;
            HvBt3 = 1;
        } else {
            But3Pressed = 0;
            Bt3Up = 1;
        }
        if (!But4) {
            But4Pressed = 1;
            HvBt4 = 1;
        } else {
            But4Pressed = 0;
            Bt4Up = 1;
        }

    }
    if (!But1Pressed) {
        if (Bt1Cnt) {
            if (!But1) {
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
            if (!But1) {
                Bt1Cnt = Bt1CntConst;
                But1Pressed = 1;
            }
        }
    } else {
        if (Bt1Cnt) {
            if (But1) {
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
            if (But1) {
                Bt1Cnt = Bt1CntConst;
                But1Pressed = 0;
            }
            Bt1LongCnt++;
        }
    }



    if (!But2Pressed) {
        if (Bt2Cnt) {
            if (!But2) {
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
            if (!But2) {
                Bt2Cnt = Bt2CntConst;
                But2Pressed = 1;
            }
        }
    } else {
        if (Bt2Cnt) {
            if (But2) {
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
            if (But2) {
                Bt2Cnt = Bt2CntConst;
                But2Pressed = 0;
            }
            Bt2LongCnt++;
        }
    }



    if (!But3Pressed) {
        if (Bt3Cnt) {
            if (!But3) {
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
            if (!But3) {
                Bt3Cnt = Bt3CntConst;
                But3Pressed = 1;
            }
        }
    } else {
        if (Bt3Cnt) {
            if (But3) {
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
            if (But3) {
                Bt3Cnt = Bt3CntConst;
                But3Pressed = 0;
            }
            Bt3LongCnt++;
        }
    }




    if (!But4Pressed) {
        if (Bt4Cnt) {
            if (!But4) {
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
            if (!But4) {
                Bt4Cnt = Bt4CntConst;
                But4Pressed = 1;
            }
        }
    } else {
        if (Bt4Cnt) {
            if (But4) {
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
            if (But4) {
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

void Bt1Process(void) {

    switch (But1Func) {
        case 0:
            Bt1Up = 0;
            HvBt1 = 0;
            break;
        case 1:
            if (HvBt1) {
                HvBt1 = 0;
                ReversON = 1;
            }
            if (Bt1Up) {
                Bt1Up = 0;
                ReversON = 0;
                Sounds = 0;
            }
            break;
        case 2:
            if (But1Pressed) {
                if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                    Horn = 0;
#else
                    //Horn=1;
                    OC3R = ((unsigned int) KeyLightBrightness) << 8;
#endif
                {
                    BuzzerOnEvent = 5;
                    BuzzerMacroOn//Buzzer=1;
                }
            } else {

                if (!Sounds) {
                    if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                        Horn = 1;
#else
                        //Horn=0;
                        OC3R = 0;
#endif
                    BuzzerMacroOff;
                }
            }
            break;
        case 3:
            if (HvBt1) {
                if (!PID_On) {
                    if (!Wheeling) {
                        if (!SpeedControl) {
                            SoundNum = 1;
                            Spd1UST = Spd1Res;
                            StrtPID_On = 1;
                            BtPID_Activated = 1;

                            /*if (StrongModePID)
                            {
                                PrevStrongMode=StrongMode;
        //                        StrongMode=1;
                            }*/

                        }
                    }
                } else {
                    if (SpeedControl) {
                        SpeedControlPID = 1;
                        Spd1UST = Spd1Res;
                        SpeedControlPIDOffCnt = 500;
                        SoundNum = 1;
                        /*if (StrongModePID)
                            {
                            PrevStrongMode=StrongMode;
                            StrongMode=1;
                            }*/
                    }
                }
                HvBt1 = 0;
            }
            if (Bt1Up) {

                if (StrongModePID)
                    StrongMode = PrevStrongMode;
                if (!SpeedControl) {
                    PID_On = 0;
                } else {
                    if (!StartingBTN) {
                        if (SpeedControlPID)
                            SoundNum = 10;
                    }
                    SpeedControlPID = 0;

                }

                Bt1Up = 0;
            }
            break;
        case 4:
            if (HvBt1) {
                HvBt1 = 0;
                Profile = 2;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 16;
            }
            if (Bt1Up) {
                Bt1Up = 0;
                Profile = 1;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 15;
            }
            break;
        case 5:
            if (HvBt1) {
                HvBt1 = 0;
                if (Profile < 3)
                    Profile++;
                else
                    Profile = 1;
                if (StartingBTN)
                    Profile = 1;

                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;



                if (!StartingBTN)
                    switch (Profile) {
                        case 1:
                            SoundNum = 15;
                            break;
                        case 2:
                            SoundNum = 16;
                            break;
                        case 3:
                            SoundNum = 17;
                            break;
                    }







            }
            break;
        case 6:
            if (HvBt1) {
                PID_OnOff_Func();
                HvBt1 = 0;
            }
            if (Bt1Up) {
                Bt1Up = 0;
            }
            break;
        case 7:
            if (HvBt1) {
                HvBt1 = 0;
                WheelingStateMachine = 1;
            }
            if (Bt1Up) {
                WheelingStateMachine = 4;
                Bt1Up = 0;
            }
            break;

        case 8:
            if (Bt1DnMustCount) {
                Bt1DnCounter++;

                if (Bt1DnCounter > 500) {
                    Bt1DnMustCount = 0;
                    Bt1NumPressedCnt = 0;

                    if (ChagerViaMotor)
                        StopCharging();
                    else
                        StartCharging();



                }
            }


            if (Bt1UpCounter < 150) {
                Bt1UpCounter++;
                if (Bt1UpCounter == 150) {
                    if (Bt1NumPressedCnt == 1) {
                        Bt1NumPressedCnt = 0;
                        SoundNum = 12;

                        if (LightMode == 1)
                            LightMode = 0;
                        else
                            LightMode = 1;


                    }
                    if (Bt1NumPressedCnt == 2) {
                        SoundNum = 11;
                        Bt1NumPressedCnt = 0;
                        if (Right)
                            Right = 0;
                        else
                            Right = 1;

                    }
                }
            }


            if (HvBt1) {
                HvBt1 = 0;
                Bt1DnCounter = 0;
                Bt1DnMustCount = 1;
                Bt1NumPressedCnt++;
            }
            if (Bt1Up) {
                Bt1Up = 0;
                Bt1UpCounter = 0;
                Bt1DnMustCount = 0;
            }


            break;

        case 9:
            if ((CountingHumanSensor)&&(CntStopBalanceHumanSensor)) {
                CntStopBalanceHumanSensor--;
                if (!Sounds)
                    SoundNum = 10;

                if (!CntStopBalanceHumanSensor) {
                    CountingHumanSensor = 0;
                    OkToBalance = 0;
                    NoBalance = 1;
                    NoBalanceCode = 6;
                    StrongMode = 0;
                    DS = 1;
                }
            }
            if (HvBt1) {
                OkToBalance = 1;
                SoundNum = 12;
                CntStopBalanceHumanSensor = TimeHumanSensorOff;
                CountingHumanSensor = 0;
                HvBt1 = 0;
            }
            if (Bt1Up) {
                CountingHumanSensor = 1;
                Bt1Up = 0;
            }
            break;
        case 10:
            if (HvBt1) {
                if (Spd1FlPlus < 5)
                    StopMotorMonocycle = 1;
                HvBt1 = 0;
            }
            if (Bt1Up) {
                StopMotorMonocycle = 0;
                Sounds = 0;
                Bt1Up = 0;
            }




    }




}

void Bt2Process(void) {

    switch (But2Func) {
        case 0:
            Bt2Up = 0;
            HvBt2 = 0;
            break;
        case 1:
            if (HvBt2) {
                HvBt2 = 0;
                ReversON = 1;
            }
            if (Bt2Up) {
                Bt2Up = 0;
                ReversON = 0;
                Sounds = 0;
            }
            break;
        case 2:
            if (But2Pressed) {
                if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                    Horn = 0;
#else
                    //Horn=1;
                    OC3R = ((unsigned int) KeyLightBrightness) << 8;
#endif
                {
                    BuzzerOnEvent = 6;
                    BuzzerMacroOn//Buzzer=1;
                }
            } else {
                if (!Sounds) {
                    if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                        Horn = 1;
#else
                        //Horn=0;
                        OC3R = 0;
#endif
                    BuzzerMacroOff;
                }
            }
            break;
        case 3:
            if (HvBt2) {

                if (!PID_On) {
                    if (!Wheeling) {
                        if (!SpeedControl) {
                            SoundNum = 1;
                            StrtPID_On = 1;
                            BtPID_Activated = 1;
                            /*    if (StrongModePID)
                         {
                             PrevStrongMode=StrongMode;
                             StrongMode=1;
                         }*/
                        }

                    }
                } else {
                    if (SpeedControl) {
                        /*if (StrongModePID)
                            {
                            PrevStrongMode=StrongMode;
                            StrongMode=1;
                            }*/
                        SpeedControlPID = 1;
                        SpeedControlPIDOffCnt = 500;
                        Spd1UST = Spd1Res;
                        //StrtPID_On=1;
                        SoundNum = 1;
                    }
                }
                HvBt2 = 0;
            }
            if (Bt2Up) {

                if (StrongModePID)
                    StrongMode = PrevStrongMode;

                if (!SpeedControl)
                    PID_On = 0;
                else {
                    if (!StartingBTN) {
                        if (SpeedControlPID)
                            SoundNum = 10;
                    }
                    SpeedControlPID = 0;
                }

                Bt2Up = 0;
            }
            break;
        case 4:
            if (HvBt2) {
                HvBt2 = 0;
                Profile = 2;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 16;
            }
            if (Bt2Up) {
                Bt2Up = 0;
                Profile = 1;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 15;
            }
            break;
        case 5:
            if (HvBt2) {
                HvBt2 = 0;
                if (Profile < 3)
                    Profile++;
                else
                    Profile = 1;
                if (StartingBTN)
                    Profile = 1;

                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;



                if (!StartingBTN)
                    switch (Profile) {
                        case 1:
                            SoundNum = 15;
                            break;
                        case 2:
                            SoundNum = 16;
                            break;
                        case 3:
                            SoundNum = 17;
                            break;
                    }







            }
            break;
        case 6:
            if (HvBt2) {
                PID_OnOff_Func();
                HvBt2 = 0;
            }
            if (Bt2Up) {
                Bt2Up = 0;
            }
            break;
        case 7:
            if (HvBt2) {
                HvBt2 = 0;
                WheelingStateMachine = 1;
            }
            if (Bt2Up) {
                WheelingStateMachine = 4;
                Bt2Up = 0;
            }
            break;
        case 8:
            if (Bt2DnMustCount) {
                Bt2DnCounter++;

                if (Bt2DnCounter > 500) {
                    Bt2DnMustCount = 0;
                    Bt2NumPressedCnt = 0;

                    if (ChagerViaMotor)
                        StopCharging();
                    else
                        StartCharging();



                }
            }


            if (Bt2UpCounter < 150) {
                Bt2UpCounter++;
                if (Bt2UpCounter == 150) {
                    if (Bt2NumPressedCnt == 1) {
                        Bt2NumPressedCnt = 0;
                        SoundNum = 12;
                        if (LightMode == 1)
                            LightMode = 0;
                        else
                            LightMode = 1;



                    }
                    if (Bt2NumPressedCnt == 2) {
                        SoundNum = 11;
                        Bt2NumPressedCnt = 0;
                        if (Right)
                            Right = 0;
                        else
                            Right = 1;

                    }
                }
            }


            if (HvBt2) {
                HvBt2 = 0;
                Bt2DnCounter = 0;
                Bt2DnMustCount = 1;
                Bt2NumPressedCnt++;
            }
            if (Bt2Up) {
                Bt2Up = 0;
                Bt2UpCounter = 0;
                Bt2DnMustCount = 0;
            }


            break;

        case 9:
            if ((CountingHumanSensor)&&(CntStopBalanceHumanSensor)) {
                CntStopBalanceHumanSensor--;
                if (!Sounds)
                    SoundNum = 10;

                if (!CntStopBalanceHumanSensor) {
                    CountingHumanSensor = 0;
                    OkToBalance = 0;
                    NoBalance = 1;
                    NoBalanceCode = 6;
                    StrongMode = 0;
                    DS = 1;
                }
            }
            if (HvBt2) {
                OkToBalance = 1;
                SoundNum = 12;
                CntStopBalanceHumanSensor = TimeHumanSensorOff;
                CountingHumanSensor = 0;
                HvBt2 = 0;
            }
            if (Bt2Up) {
                CountingHumanSensor = 1;
                Bt2Up = 0;
            }
            break;
        case 10:
            if (HvBt2) {
                StopMotorMonocycle = 1;
                HvBt2 = 0;
            }
            if (Bt2Up) {
                StopMotorMonocycle = 0;
                Sounds = 0;
                Bt2Up = 0;
            }








    }




}

void Bt3Process(void) {

    switch (But3Func) {
        case 0:
            Bt3Up = 0;
            HvBt3 = 0;
            break;
        case 1:
            if (HvBt3) {
                HvBt3 = 0;
                ReversON = 1;
            }
            if (Bt3Up) {
                Bt3Up = 0;
                ReversON = 0;
                Sounds = 0;
            }
            break;
        case 2:
            if (But3Pressed) {
                if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                    Horn = 0;
#else
                    //Horn=1;
                    OC3R = ((unsigned int) KeyLightBrightness) << 8;
#endif
                {
                    BuzzerOnEvent = 7;
                    BuzzerMacroOn//Buzzer=1;
                }
            } else {
                if (!Sounds) {
                    if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                        Horn = 1;
#else
                        //Horn=0;
                        OC3R = 0;
#endif
                    BuzzerMacroOff;
                }
            }
            break;
        case 3:
            if (HvBt3) {

                if (!PID_On) {
                    if (!Wheeling) {
                        if (!SpeedControl) {
                            SoundNum = 1;
                            StrtPID_On = 1;
                            BtPID_Activated = 1;
                            /*if (StrongModePID)
                            {
                                PrevStrongMode=StrongMode;
                                StrongMode=1;
                            }*/
                        }
                    }
                } else {
                    if (SpeedControl) {
                        SpeedControlPID = 1;
                        SpeedControlPIDOffCnt = 500;
                        Spd1UST = Spd1Res;
                        SoundNum = 1;
                        /*if (StrongModePID)
                            {
                            PrevStrongMode=StrongMode;
                            StrongMode=1;
                            }*/
                    }
                }
                HvBt3 = 0;
            }
            if (Bt3Up) {

                if (StrongModePID)
                    StrongMode = PrevStrongMode;
                if (!SpeedControl)
                    PID_On = 0;
                else {
                    if (!StartingBTN) {
                        if (SpeedControlPID)
                            SoundNum = 10;
                    }
                    SpeedControlPID = 0;
                }

                Bt3Up = 0;
            }
            break;
        case 4:
            if (HvBt3) {
                HvBt3 = 0;
                Profile = 2;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 16;
            }
            if (Bt3Up) {
                Bt3Up = 0;
                Profile = 1;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 15;
            }
            break;
        case 5:
            if (HvBt3) {
                HvBt3 = 0;
                if (Profile < 3)
                    Profile++;
                else
                    Profile = 1;
                if (StartingBTN)
                    Profile = 1;

                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;



                if (!StartingBTN)
                    switch (Profile) {
                        case 1:
                            SoundNum = 15;
                            break;
                        case 2:
                            SoundNum = 16;
                            break;
                        case 3:
                            SoundNum = 17;
                            break;
                    }







            }
            break;
        case 6:
            if (HvBt3) {
                PID_OnOff_Func();
                HvBt3 = 0;
            }
            if (Bt3Up) {
                Bt3Up = 0;
            }
            break;

        case 7:
            if (HvBt3) {
                HvBt3 = 0;
                WheelingStateMachine = 1;
            }
            if (Bt3Up) {
                WheelingStateMachine = 4;
                Bt3Up = 0;
            }
            break;

        case 8:
            if (Bt3DnMustCount) {
                Bt3DnCounter++;

                if (Bt3DnCounter > 500) {
                    Bt3DnMustCount = 0;
                    Bt3NumPressedCnt = 0;

                    if (ChagerViaMotor)
                        StopCharging();
                    else
                        StartCharging();



                }
            }


            if (Bt3UpCounter < 150) {
                Bt3UpCounter++;
                if (Bt3UpCounter == 150) {
                    if (Bt3NumPressedCnt == 1) {
                        Bt3NumPressedCnt = 0;
                        SoundNum = 12;
                        if (LightMode == 1)
                            LightMode = 0;
                        else
                            LightMode = 1;




                    }
                    if (Bt3NumPressedCnt == 2) {
                        SoundNum = 11;
                        Bt3NumPressedCnt = 0;
                        if (Right)
                            Right = 0;
                        else
                            Right = 1;

                    }
                }
            }


            if (HvBt3) {
                HvBt3 = 0;
                Bt3DnCounter = 0;
                Bt3DnMustCount = 1;
                Bt3NumPressedCnt++;
            }
            if (Bt3Up) {
                Bt3Up = 0;
                Bt3UpCounter = 0;
                Bt3DnMustCount = 0;
            }


            break;

        case 9:
            if ((CountingHumanSensor)&&(CntStopBalanceHumanSensor)) {
                CntStopBalanceHumanSensor--;
                if (!Sounds)
                    SoundNum = 10;

                if (!CntStopBalanceHumanSensor) {
                    CountingHumanSensor = 0;
                    OkToBalance = 0;
                    NoBalance = 1;
                    NoBalanceCode = 6;
                    StrongMode = 0;
                    DS = 1;
                }
            }
            if (HvBt3) {
                OkToBalance = 1;
                SoundNum = 12;
                CntStopBalanceHumanSensor = TimeHumanSensorOff;
                CountingHumanSensor = 0;
                HvBt3 = 0;
            }
            if (Bt3Up) {
                CountingHumanSensor = 1;
                Bt3Up = 0;
            }
            break;
        case 10:
            if (HvBt3) {
                StopMotorMonocycle = 1;
                HvBt3 = 0;
            }
            if (Bt3Up) {
                StopMotorMonocycle = 0;
                Sounds = 0;
                Bt3Up = 0;
            }


    }




}

void Bt4Process(void) {

    switch (But4Func) {
        case 0:
            Bt4Up = 0;
            HvBt4 = 0;
            break;
        case 1:
            if (HvBt4) {
                HvBt4 = 0;
                ReversON = 1;
            }
            if (Bt4Up) {
                Bt4Up = 0;
                ReversON = 0;
                Sounds = 0;
            }
            break;
        case 2:
            if (But4Pressed) {
                if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                    Horn = 0;
#else
                    //Horn=1;
                    OC3R = ((unsigned int) KeyLightBrightness) << 8;
#endif
                {
                    BuzzerOnEvent = 8;
                    BuzzerMacroOn//Buzzer=1;
                }
            } else {
                if (!Sounds) {
                    if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                        Horn = 1;
#else
                        //Horn=0;
                        OC3R = 0;
#endif
                    BuzzerMacroOff;
                }
            }
            break;
        case 3:
            if (HvBt4) {

                if (!PID_On) {
                    if (!Wheeling) {
                        if (!SpeedControl) {
                            SoundNum = 1;
                            StrtPID_On = 1;
                            BtPID_Activated = 1;
                            /*if (StrongModePID)
                            {
                                PrevStrongMode=StrongMode;
                                StrongMode=1;
                            }*/
                        }
                    }
                } else {
                    if (SpeedControl) {
                        SpeedControlPID = 1;
                        Spd1UST = Spd1Res;
                        SpeedControlPIDOffCnt = 500;
                        SoundNum = 1;
                        /*if (StrongModePID)
                            {
                            PrevStrongMode=StrongMode;
                            StrongMode=1;
                            }*/
                    }
                }
                HvBt4 = 0;
            }
            if (Bt4Up) {

                if (StrongModePID)
                    StrongMode = PrevStrongMode;
                if (!SpeedControl)
                    PID_On = 0;
                else {
                    if (!StartingBTN) {
                        if (SpeedControlPID)
                            SoundNum = 10;
                    }
                    SpeedControlPID = 0;
                }

                Bt4Up = 0;
            }
            break;
        case 4:
            if (HvBt4) {
                HvBt4 = 0;
                Profile = 2;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 16;
            }
            if (Bt4Up) {
                Bt4Up = 0;
                Profile = 1;
                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;
                if (!StartingBTN)
                    SoundNum = 15;
            }
            break;
        case 5:
            if (HvBt4) {
                HvBt4 = 0;
                if (Profile < 3)
                    Profile++;
                else
                    Profile = 1;
                if (StartingBTN)
                    Profile = 1;

                MassToOptionsProfile();
                OptionsToMass();
                MustTrmFlashMass = 1;



                if (!StartingBTN)
                    switch (Profile) {
                        case 1:
                            SoundNum = 15;
                            break;
                        case 2:
                            SoundNum = 16;
                            break;
                        case 3:
                            SoundNum = 17;
                            break;
                    }







            }
            break;
        case 6:
            if (HvBt4) {
                PID_OnOff_Func();
                HvBt4 = 0;
            }
            if (Bt4Up) {
                Bt4Up = 0;
            }
            break;
        case 7:
            if (HvBt4) {
                HvBt4 = 0;
                WheelingStateMachine = 1;
            }
            if (Bt4Up) {
                WheelingStateMachine = 4;
                Bt4Up = 0;
            }
            break;
        case 8:
            if (Bt4DnMustCount) {
                Bt4DnCounter++;

                if (Bt4DnCounter > 500) {
                    Bt4DnMustCount = 0;
                    Bt4NumPressedCnt = 0;

                    if (ChagerViaMotor)
                        StopCharging();
                    else
                        StartCharging();



                }
            }


            if (Bt4UpCounter < 150) {
                Bt4UpCounter++;
                if (Bt4UpCounter == 150) {
                    if (Bt4NumPressedCnt == 1) {
                        Bt4NumPressedCnt = 0;
                        SoundNum = 12;

                        if (LightMode == 1)
                            LightMode = 0;
                        else
                            LightMode = 1;




                    }
                    if (Bt4NumPressedCnt == 2) {
                        SoundNum = 11;
                        Bt4NumPressedCnt = 0;
                        if (Right)
                            Right = 0;
                        else
                            Right = 1;

                    }
                }
            }


            if (HvBt4) {
                HvBt4 = 0;
                Bt4DnCounter = 0;
                Bt4DnMustCount = 1;
                Bt4NumPressedCnt++;
            }
            if (Bt4Up) {
                Bt4Up = 0;
                Bt4UpCounter = 0;
                Bt4DnMustCount = 0;
            }


            break;
        case 9:
            if ((CountingHumanSensor)&&(CntStopBalanceHumanSensor)) {
                CntStopBalanceHumanSensor--;
                if (!Sounds)
                    SoundNum = 10;

                if (!CntStopBalanceHumanSensor) {
                    CountingHumanSensor = 0;
                    OkToBalance = 0;
                    NoBalance = 1;
                    NoBalanceCode = 6;
                    StrongMode = 0;
                    DS = 1;
                }
            }
            if (HvBt4) {
                OkToBalance = 1;
                SoundNum = 12;
                CntStopBalanceHumanSensor = TimeHumanSensorOff;
                CountingHumanSensor = 0;
                HvBt4 = 0;
            }
            if (Bt4Up) {
                CountingHumanSensor = 1;
                Bt4Up = 0;
            }
            break;
        case 10:
            if (HvBt4) {
                StopMotorMonocycle = 1;
                HvBt4 = 0;
            }
            if (Bt4Up) {
                StopMotorMonocycle = 0;
                Sounds = 0;
                Bt4Up = 0;
            }




    }




}

void writeFlash(void) {
    if (!HvToWriteFlash)
        return;
    HvToWriteFlash = 0;
    OptionsToMass();
    WriteOptions();
    unsigned char Th = ReadOptions();
    Nop();
    Nop();
    Nop();
    Nop();
    if (ErrOptions)
        OptionsToMass();
    else
        if (Th == 1) {
        SoundNum = 1;
    }

    MustTrmFlashMass = 1;

}

void WriteErrors(void) {
    int Tm = 0;
    unsigned long int SectorAddr;
    unsigned char *Ptr;
    unsigned char j;


    if (!WriteErr_Fl)
        return;
    WriteErr_Fl = 0;

    FlgsErr.Flags = Flgs.Flags;
    Flgs1Err.Flags = Flgs1.Flags;
    Flgs2Err.Flags = Flgs2.Flags;



    SectorAddr = 4096 * OdometrSectorNumConst;



    WriteStat_FLASH(0);
    EraseSector_FLASH(SectorAddr);


    WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, ErrOptions);
    Tm++;

    Ptr = (unsigned char *) &AlfaXResErr;
    for (j = 0; j<sizeof (AlfaXResErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &AlfaYResErr;
    for (j = 0; j<sizeof (AlfaYResErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &SteerXErr;
    for (j = 0; j<sizeof (SteerXErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &SteerYErr;
    for (j = 0; j<sizeof (SteerYErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, ErrorCode);
    Tm++;

    WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, NoBalanceCode);
    Tm++;

    Ptr = (unsigned char *) &FlgsErr.Flags;
    for (j = 0; j<sizeof (FlgsErr.Flags); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }


    Ptr = (unsigned char *) &Flgs1Err.Flags;
    for (j = 0; j<sizeof (Flgs1Err.Flags); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }


    Ptr = (unsigned char *) &LastMainTiltAngleMnErr;
    for (j = 0; j<sizeof (LastMainTiltAngleMnErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &LastSteerTiltAngleMnErr;
    for (j = 0; j<sizeof (LastSteerTiltAngleMnErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &TiltAngleAvMnErr;
    for (j = 0; j<sizeof (TiltAngleAvMnErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }


    WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, MainTiltNumErr);
    Tm++;

    WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, SteerTiltNumErr);
    Tm++;


    Ptr = (unsigned char *) &LastMainTiltAngleSteerErr;
    for (j = 0; j<sizeof (LastMainTiltAngleSteerErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &LastSteerTiltAngleSteerErr;
    for (j = 0; j<sizeof (LastSteerTiltAngleSteerErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &TiltAngleAvSteerErr;
    for (j = 0; j<sizeof (TiltAngleAvSteerErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }


    Ptr = (unsigned char *) &Flgs2Err.Flags;
    for (j = 0; j<sizeof (Flgs2Err.Flags); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }

    Ptr = (unsigned char *) &BatErr;
    for (j = 0; j<sizeof (BatErr); j++) {
        WriteByte_FLASH(SectorAddr + (unsigned long int) Tm, *Ptr);
        Tm++;
        Ptr++;
    }


    WriteStat_FLASH(0x3c);


}

void ReadErrors(void) {
    int Tm = 0;
    unsigned long int SectorAddr;

    SectorAddr = 4096 * OdometrSectorNumConst;


    ReadFlash(SectorAddr + Tm, sizeof (ErrOptions), (unsigned char *) &ErrOptions);
    Tm = Tm + sizeof (ErrOptions);

    ReadFlash(SectorAddr + Tm, sizeof (AlfaXResErr), (unsigned char *) &AlfaXResErr);
    Tm = Tm + sizeof (AlfaXResErr);

    ReadFlash(SectorAddr + Tm, sizeof (AlfaYResErr), (unsigned char *) &AlfaYResErr);
    Tm = Tm + sizeof (AlfaYResErr);

    ReadFlash(SectorAddr + Tm, sizeof (SteerXErr), (unsigned char *) &SteerXErr);
    Tm = Tm + sizeof (SteerXErr);

    ReadFlash(SectorAddr + Tm, sizeof (SteerYErr), (unsigned char *) &SteerYErr);
    Tm = Tm + sizeof (SteerYErr);

    ReadFlash(SectorAddr + Tm, sizeof (ErrorCode), (unsigned char *) &ErrorCode);
    Tm = Tm + sizeof (ErrorCode);

    ReadFlash(SectorAddr + Tm, sizeof (NoBalanceCode), (unsigned char *) &NoBalanceCode);
    Tm = Tm + sizeof (NoBalanceCode);

    ReadFlash(SectorAddr + Tm, sizeof (FlgsErr.Flags), (unsigned char *) &FlgsErr.Flags);
    Tm = Tm + sizeof (FlgsErr.Flags);

    ReadFlash(SectorAddr + Tm, sizeof (Flgs1Err.Flags), (unsigned char *) &Flgs1Err.Flags);
    Tm = Tm + sizeof (Flgs1Err.Flags);

    ReadFlash(SectorAddr + Tm, sizeof (LastMainTiltAngleMnErr), (unsigned char *) &LastMainTiltAngleMnErr);
    Tm = Tm + sizeof (LastMainTiltAngleMnErr);

    ReadFlash(SectorAddr + Tm, sizeof (LastSteerTiltAngleMnErr), (unsigned char *) &LastSteerTiltAngleMnErr);
    Tm = Tm + sizeof (LastSteerTiltAngleMnErr);

    ReadFlash(SectorAddr + Tm, sizeof (TiltAngleAvMnErr), (unsigned char *) &TiltAngleAvMnErr);
    Tm = Tm + sizeof (TiltAngleAvMnErr);

    ReadFlash(SectorAddr + Tm, sizeof (MainTiltNumErr), (unsigned char *) &MainTiltNumErr);
    Tm = Tm + sizeof (MainTiltNumErr);

    ReadFlash(SectorAddr + Tm, sizeof (SteerTiltNumErr), (unsigned char *) &SteerTiltNumErr);
    Tm = Tm + sizeof (SteerTiltNumErr);

    ReadFlash(SectorAddr + Tm, sizeof (LastMainTiltAngleSteerErr), (unsigned char *) &LastMainTiltAngleSteerErr);
    Tm = Tm + sizeof (LastMainTiltAngleSteerErr);

    ReadFlash(SectorAddr + Tm, sizeof (LastSteerTiltAngleSteerErr), (unsigned char *) &LastSteerTiltAngleSteerErr);
    Tm = Tm + sizeof (LastSteerTiltAngleSteerErr);

    ReadFlash(SectorAddr + Tm, sizeof (TiltAngleAvSteerErr), (unsigned char *) &TiltAngleAvSteerErr);
    Tm = Tm + sizeof (TiltAngleAvSteerErr);

    ReadFlash(SectorAddr + Tm, sizeof (Flgs2Err.Flags), (unsigned char *) &Flgs2Err.Flags);
    Tm = Tm + sizeof (Flgs2Err.Flags);

    ReadFlash(SectorAddr + Tm, sizeof (BatErr), (unsigned char *) &BatErr);
    Tm = Tm + sizeof (BatErr);


}

//UART 4  End

void TrmDataPacketHC05(void) {
    unsigned int CntBt = 4;
    int Tmp;

    //   if (!MustTrmPacketHC05_FL)
    //     return;
    //MustTrmPacketHC05_FL=0;
    if (HC05_BUSY) {
        HC05_BUSYCnt++;
        return;
    }



    if (NoAutoTrm) {
        if (!MustSendDataPacket)
            return;
    }





    if ((OnTransmittHC05)&&(TimeOutHC05)) {
        if (!TimeOutHC05)
            BuzzerOnAlways = 1;
        HC05_TrmCnt++;
        return;
    }

    HC05_BUSY = 1;

    MustSendDataPacket = 0;
    MustTrmHC05 = 0;

    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;


    HC05TrmMass[3] = 5; //COMMAND

    if (HighDataSpdUART)
    {
        
        
        
    HC05TrmMass[CntBt++] = (unsigned char)CntSamples;
//    HC05TrmMass[CntBt++] = CntSamples >> 8;
//    HC05TrmMass[CntBt++] = CntSamples >> 16;
//    HC05TrmMass[CntBt++] = CntSamples >> 24;
    
    /*
    
    Tmp = (int) (AlfaXRes * 100);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (AlfaYRes * 100);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) EpLog;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) EiLog;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) EdLog;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    */

    Tmp = (int) (AccXFl);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (AccYFl);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (AccZFl);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;
    

    Tmp = (int) (GyroXFl);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (GyroYFl);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (GyroZFl);
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    
    if (PWM1Plus)
        Tmp = PWM1Show; //PWM1;        8
    else
        Tmp = -PWM1Show;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[2] = CntBt - 3;

    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;

    return;
    }




    HC05TrmMass[CntBt++] = CntSamples;
    HC05TrmMass[CntBt++] = CntSamples >> 8;
    HC05TrmMass[CntBt++] = CntSamples >> 16;
    HC05TrmMass[CntBt++] = CntSamples >> 24;

    Tmp = (int) (AlfaXRes * 100); //AlfaXRes;     1
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (AlfaYRes * 100); //AlfaYRes;     2
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) GyroXFl; //GyroX;        3
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = TiltXRes; //TiltXRes;        4
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = LightSensor; //TiltYRes;        5
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) Ep; //Ep;        6
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) Ei; //Ei;        7
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;




    if (PWM1Plus)
        Tmp = PWM1Show; //PWM1;        8
    else
        Tmp = -PWM1Show;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;




    Tmp = (int) Curr1Show; //Curr1;//                              //(int)Curr1;        9
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (Spd1UST * 10 * ImpToKmH1_t); //KMH;//                              //Spd1UST;        10  
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;



    Tmp = (int) (Temperature3 * 10);
    HC05TrmMass[CntBt++] = Tmp; //                                                 
    HC05TrmMass[CntBt++] = Tmp >> 8;


    HC05TrmMass[CntBt++] = Odometr; //Odometr;        12
    HC05TrmMass[CntBt++] = Odometr >> 8;
    HC05TrmMass[CntBt++] = Odometr >> 16;
    HC05TrmMass[CntBt++] = Odometr >> 24;

    Tmp = (int) Spd1Res; //Spd1Res;        13
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    if (Temperature2 < 10) {
        Nop();
        Nop();
        Nop();
        Nop();
    }


    Tmp = (int) (Temperature2 * 10); //14
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (Temperature1 * 10); //               15
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) Kp_p; //Kp;                              //Kp;        16
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (UBtFl * 10); //UBT;        17
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = GyroVert_Steer; //GyroVert_Steer;        18
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = StatFlgs.StatusFlags; //StatFlgs.StatusFlags;        19
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) GyroZFilter; //GyroZFilter        20
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) AlfaYResPrevAv; //AlfaYResPrevAv        21
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) DiffBetweenTilts; //DiffBetweenTilts        22
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = Flgs.Flags; //Odometr;        23
    HC05TrmMass[CntBt++] = Flgs.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs.Flags >> 24;

    HC05TrmMass[CntBt++] = Flgs1.Flags; //Odometr;        24
    HC05TrmMass[CntBt++] = Flgs1.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs1.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs1.Flags >> 24;

    HC05TrmMass[CntBt++] = Flgs2.Flags; //Odometr;        25
    HC05TrmMass[CntBt++] = Flgs2.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs2.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs2.Flags >> 24;



    Tmp = (int) (TiltZad * 10); //TiltZad        26
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (StartRot1 * 10); //StartRot        27
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (Ki_pp * 1000); //(Ki*1000);                         //StartRot        28
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = KRot1; //KRot1        29
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (KpRot * 1000); //StartRot        30
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (KiRot * 10000); //StartRot        31
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = ADCThrottle; //ADCThrottle        32
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = ThrottleTmp; //Preas2ADC        33
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = CurrLimit; //EMPTY             34

    Tmp = KpSPD; //KpSPD        35
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = AngleLimit; //AngleLimit        36
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    HC05TrmMass[CntBt++] = CurrTuda1; //CurrTuda1;        37
    HC05TrmMass[CntBt++] = CurrTuda1 >> 8;
    HC05TrmMass[CntBt++] = CurrTuda1 >> 16;
    HC05TrmMass[CntBt++] = CurrTuda1 >> 24;

    HC05TrmMass[CntBt++] = CurrRegen1; //CurrRegen1;        38
    HC05TrmMass[CntBt++] = CurrRegen1 >> 8;
    HC05TrmMass[CntBt++] = CurrRegen1 >> 16;
    HC05TrmMass[CntBt++] = CurrRegen1 >> 24;

    HC05TrmMass[CntBt++] = Flgs4.Flags; //Flgs4;        39
    HC05TrmMass[CntBt++] = Flgs4.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs4.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs4.Flags >> 24;

    HC05TrmMass[CntBt++] = Flgs5.Flags; //Flgs5;        40
    HC05TrmMass[CntBt++] = Flgs5.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs5.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs5.Flags >> 24;

    HC05TrmMass[CntBt++] = Flgs3.Flags; //Flgs3;        41
    HC05TrmMass[CntBt++] = Flgs3.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs3.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs3.Flags >> 24;


    HC05TrmMass[CntBt++] = TimerCnt; //TimerCnt;        42
    HC05TrmMass[CntBt++] = TimerCnt >> 8;
    HC05TrmMass[CntBt++] = TimerCnt >> 16;
    HC05TrmMass[CntBt++] = TimerCnt >> 24;



    Tmp = (unsigned int) (_3VFl * 100); //V1        43
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) (_5VFl * 100); //V2        44
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) (_12VFl * 100); //V3        45
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (CurrA * 10); //V4        46
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = CurrA_N_Av; //V5        47
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (CurrC * 10); //V6        48
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = CurrC_N_Av; //V7        49
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) MotorPhaseA;//V8; //V8        50
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) MotorNeutralVoltage;//BEMFHallCntMax;//MotorPhaseB;//V9; //V9        51
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) BemfFilterHi;//MotorPhaseC;//V10; //V10        52
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V11; //V11        53
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V12; //V12        54
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V13; //V13        55
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V14; //V14        56
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V15; //V15        57
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V16; //V16        58
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V17; //V16        59
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (unsigned int) V18; //V16        60
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    //   Tmp=BatteryKeys;                                        //BatteryKeys        61
    HC05TrmMass[CntBt++] = BatteryKeys;
    HC05TrmMass[CntBt++] = BatteryKeys >> 8;
    HC05TrmMass[CntBt++] = BatteryKeys >> 16;
    HC05TrmMass[CntBt++] = BatteryKeys >> 24;

    HC05TrmMass[CntBt++] = ChagerKeys; //ChagerKeys        62

    HC05TrmMass[CntBt++] = (int) AccXFl; //Fl;                        //AccXFl        63
    HC05TrmMass[CntBt++] = (int) AccXFl >> 8; //Fl;



    Tmp = (int) AccYFl;
    HC05TrmMass[CntBt++] = Tmp; //AccYFl        64
    HC05TrmMass[CntBt++] = Tmp >> 8;
    //    HC05TrmMass[CntBt++]=(int)AccYFl;//Fl;                        //AccYFl        64
    //    HC05TrmMass[CntBt++]=(int)AccYFl>>8;

    HC05TrmMass[CntBt++] = (int) AccZFl; //Fl;                        //AccZFl        65
    HC05TrmMass[CntBt++] = (int) AccZFl >> 8;

    HC05TrmMass[CntBt++] = Sensor1_Prev; //Sensor1_Prev        66
    HC05TrmMass[CntBt++] = Sensor2_Prev; //Sensor1_Prev        67

    Tmp = (int) (Temperature4 * 10); //        68
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    HC05TrmMass[CntBt++] = Distance; //Odometr;        69
    HC05TrmMass[CntBt++] = Distance >> 8;
    HC05TrmMass[CntBt++] = Distance >> 16;
    HC05TrmMass[CntBt++] = Distance >> 24;


    Tmp = ProtectValue; //StatFlgs.StatusFlags;        70
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = Temperature; //Temperature                  71

    HC05TrmMass[CntBt++] = 0; //                       EMPTY !!!!!!                  72

    HC05TrmMass[CntBt++] = KAccGyroSteer; //KAccGyroSteer                  73


    Tmp = (int) GyroXFl; //CurrControlPIRes;//PDC1;                               //GyroXFl;        74
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) GyroYFl; //EPID_Res;//PDC2;                               //GyroYFl;        75
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = (int) GyroZFl; //PDC3;                                   //GyroZFl;        76
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) ESumm; //Theta1CntPWMSND;                               //Ed;        77
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) GyroYAv; //GyroYAv;        78
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) Kd; //Kd;        79
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = TS4; //Kd;        80
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    HC05TrmMass[CntBt++] = PhasesCnt2; //PhasesCnt2;        81
    HC05TrmMass[CntBt++] = PhasesCnt2 >> 8;
    HC05TrmMass[CntBt++] = PhasesCnt2 >> 16;
    HC05TrmMass[CntBt++] = PhasesCnt2 >> 24;


    Tmp = (int) Spd1Fl; //Spd1Fl;        82
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = 0; //(int)(Temperature5*10);//                 EMPTY                         83
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) TiltZadAdd; //(int)(Temperature6*10);       //                 84
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    unsigned long int tt = PI_Temperature;
    HC05TrmMass[CntBt++] = tt; //Phase1Period1;        85
    HC05TrmMass[CntBt++] = tt >> 8;
    HC05TrmMass[CntBt++] = tt >> 16;
    HC05TrmMass[CntBt++] = tt >> 24;

    tt = TemperatureFETs * 10;
    HC05TrmMass[CntBt++] = tt; //Phase1Period2;        86
    HC05TrmMass[CntBt++] = tt >> 8;
    HC05TrmMass[CntBt++] = tt >> 16;
    HC05TrmMass[CntBt++] = tt >> 24;

    tt = (long int) EpTemperIN; //EpCurr1;//ADCThroottleZero;
    HC05TrmMass[CntBt++] = tt; //Phase1Period3;        87
    HC05TrmMass[CntBt++] = tt >> 8;
    HC05TrmMass[CntBt++] = tt >> 16;
    HC05TrmMass[CntBt++] = tt >> 24;

    tt = TMR8Temp; //CntBEMF;
    HC05TrmMass[CntBt++] = tt; //Phase1Period4;        88
    HC05TrmMass[CntBt++] = tt >> 8;
    HC05TrmMass[CntBt++] = tt >> 16;
    HC05TrmMass[CntBt++] = tt >> 24;

    tt = SensorLessTimerConst;
    HC05TrmMass[CntBt++] = tt; //Phase1Period5;        89
    HC05TrmMass[CntBt++] = tt >> 8;
    HC05TrmMass[CntBt++] = tt >> 16;
    HC05TrmMass[CntBt++] = tt >> 24;

    tt = (long int) ESumm_PWM_Mode; //Spd1UST_Tmp;//DiffMixed;//CntAcqSensor;
    HC05TrmMass[CntBt++] = tt; //Phase1Period6;        90
    HC05TrmMass[CntBt++] = tt >> 8;
    HC05TrmMass[CntBt++] = tt >> 16;
    HC05TrmMass[CntBt++] = tt >> 24;

    Tmp = (int) (CurrUst); //CurrUst      91  
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = CriticalError; //CriticalError  92


    Tmp = (int) ETemperINSumm; //ECurr1Summ;//;                                    //BreakTMP      93  
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = ADCThrottleBreak; //BreakTMP      94  
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = RCON_Mem; //RCON_Mem      95
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = Version; //Version      96
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = MPU6050Err; //MPU6050Err  97

    Tmp = (int) PhaseCurrShow; //(int)Curr1;        98
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) HallErrCnt; //(int)Curr1;        99
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (CurrPhaseLimit); //CurrPhaseLimit      100  
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;



    tt = (long int) PR8TempTemp; //Phase1Period1;                     //Phase1Period1  101
    HC05TrmMass[CntBt++] = tt;
    HC05TrmMass[CntBt++] = tt >> 8;
    HC05TrmMass[CntBt++] = tt >> 16;
    HC05TrmMass[CntBt++] = tt >> 24;





    //Halls=ReadSensor1_F_V();
    HC05TrmMass[CntBt++] = Sensor1_Prev; //Halls;                      //Sensor  102

    HC05TrmMass[CntBt++] = HallDelay1_F; //HallDelay1_F  103
    HC05TrmMass[CntBt++] = HallDelay1_B; //HallDelay1_B  104

    Tmp = (int) (EPID_ResTmp); //EPID_ResTmp      105
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = BuzzerOnEvent; //106

    HC05TrmMass[CntBt++] = Halls; //107


    Tmp = (int) Eid; //Eid;        108
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;



    HC05TrmMass[2] = CntBt - 3;



    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;




}

void TrmFlashMass(void) {
    int i;

    if (HC05_BUSY)
        return;

    if (!Hv_HC05)
        return;
    if (!MustTrmFlashMass)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;
    MustTrmFlashMass = 0;

    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;
    HC05TrmMass[2] = sizeof (FlashMass) + 1;
    HC05TrmMass[3] = 6; //COMMAND


    for (i = 4; i < (sizeof (FlashMass) + 4); i++)
        HC05TrmMass[i] = FlashMass[i - 4];

    HC05TrmMass[i] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;
    //TrmHC05(HC05TrmMass);
    MustTrmFlashMass2 = 1;
}

void TrmFlashMass2(void) {
    int i;

    if (HC05_BUSY)
        return;

    if (!Hv_HC05)
        return;
    if (!MustTrmFlashMass2)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;
    MustTrmFlashMass2 = 0;

    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;
    HC05TrmMass[2] = sizeof (FlashMass2) + 1;
    HC05TrmMass[3] = 16; //COMMAND


    for (i = 4; i < (sizeof (FlashMass2) + 4); i++)
        HC05TrmMass[i] = FlashMass2[i - 4];

    HC05TrmMass[i] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;
    //TrmHC05(HC05TrmMass);

}

void TrmErrorsHC05(void) {
    unsigned int CntBt = 4;
    int Tmp;

    if (HC05_BUSY)
        return;

    if (!Hv_HC05)
        return;
    if (!MustTrmErrors)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    MustTrmErrors = 0;


    /*
                ErrOptions=0x12;
                AlfaXResErr=34.56;
                AlfaYResErr=78.91;
                SteerXErr=23.45;
                SteerYErr=67.89;
                ErrorCode=12;
                NoBalanceCode=34;
           //     Flgs.Flags=0x12345678;
            //    Flgs1.Flags=0x90abcdef;
                LastMainTiltAngleMnErr=1234;
                LastSteerTiltAngleMnErr=5678;
                TiltAngleAvMnErr=9101;
                MainTiltNumErr=95;
                SteerTiltNumErr=39;
                LastMainTiltAngleSteerErr=1234;
                LastSteerTiltAngleSteerErr=5678;
                TiltAngleAvSteerErr=9101;

     */





    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;


    HC05TrmMass[3] = 7; //COMMAND

    HC05TrmMass[CntBt++] = ErrOptions;

    Tmp = (int) (AlfaXResErr * 100); //AlfaXRes;     1
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = (int) (AlfaYResErr * 100); //AlfaXRes;     1
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (SteerXErr * 100); //AlfaXRes;     1
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = (int) (SteerYErr * 100); //AlfaXRes;     1
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = ErrorCode;

    HC05TrmMass[CntBt++] = NoBalanceCode;

    HC05TrmMass[CntBt++] = FlgsErr.Flags; //Odometr;        12
    HC05TrmMass[CntBt++] = FlgsErr.Flags >> 8;
    HC05TrmMass[CntBt++] = FlgsErr.Flags >> 16;
    HC05TrmMass[CntBt++] = FlgsErr.Flags >> 24;


    HC05TrmMass[CntBt++] = Flgs1Err.Flags; //Odometr;        12
    HC05TrmMass[CntBt++] = Flgs1Err.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs1Err.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs1Err.Flags >> 24;

    Tmp = LastMainTiltAngleMnErr;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = LastSteerTiltAngleMnErr;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = TiltAngleAvMnErr;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[CntBt++] = MainTiltNumErr;

    HC05TrmMass[CntBt++] = SteerTiltNumErr;

    Tmp = StatFlgs.StatusFlags;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = LastMainTiltAngleSteerErr;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = LastSteerTiltAngleSteerErr;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    Tmp = TiltAngleAvSteerErr;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    HC05TrmMass[CntBt++] = Flgs2Err.Flags; //Odometr;        12
    HC05TrmMass[CntBt++] = Flgs2Err.Flags >> 8;
    HC05TrmMass[CntBt++] = Flgs2Err.Flags >> 16;
    HC05TrmMass[CntBt++] = Flgs2Err.Flags >> 24;

    Tmp = BatErr;
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;

    HC05TrmMass[2] = CntBt - 3;


    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;


    //    TrmHC05(HC05TrmMass);




}

void SetKpMustBe_UP(void) {
    if (Kp < KpMustBe)
        KpMustBe_UP = 1;
    else
        KpMustBe_UP = 0;
}

void SetKi_UP(void) {
    if (Ki < KiMustBe)
        Ki_UP = 1;
    else
        Ki_UP = 0;
}

void SetKpSPD_UP(void) {
    if (KpSPD < KpSPDMustBe)
        KpSPD_UP = 1;
    else
        KpSPD_UP = 0;
}

void SetAngleLimit_UP(void) {
    if (AngleLimit < AngleLimitMustBe)
        AngleLimit_UP = 1;
    else
        AngleLimit_UP = 0;

}

void DefaultOptions(void) {
    unsigned char Dr1 = 0;
    if (DirPWM1)
        Dr1 = 1;

    CurrUstWork = 200;

    AutoPID_On_PWM = 20;
    AutoPID_On_Speed = 2;


    DefaultProfileOptions();
    Profile = 1;
    MassToOptionsProfile();

    SensorlessSpdChngCntConst = 12;
    SensorlessCntAlignConst = 50;
    SenosrlessPWM1_1Const = 750;
    SensorlessCurrUst = 24;
    SensorLessCurrLimit = 1;
    TemperatureTYPE = 0;
    TemperatureMaxOUT = 120;
    TemperatureMaxIN = 62;

    SensorllessSpdThreshold = 9;
    SensorLessTimerConstConst = 60;

    KiCurr = 1;
    CurrUst = 10000;

    But1Func = 1;
    But2Func = 2;
    But3Func = 3;
    But4Func = 4;
    But5Func = 0;


    TemperatureMaxOUT_H = 130;
    TemperatureMaxIN_H = 720;

    HallDelayMem1_F = 0;
    HallDelayMem1_B = 0;
    //    HallDelayMem2_F=0;                      EMPTY
    //    HallDelayMem2_B=0;                      EMPTY

    Theta1Zero = 31;
    Theta2Zero = 31;

    BreakThreshold = 2000;
    KThreshold = (long int) ((((float) MAX_PWM) / (MAX_PWM - BreakThreshold))*256);
    KThresholdBreak = (long int) ((((float) MAX_PWM) / (BreakThreshold))*256);


    V_MIN_OFF = 2100;
    V_MIN_Pre_OFF = 2300;
    V_MIN_Sound = 2900;
    V_min_OverV = 3950;

    KFirstBreak = 1500;


    SpeedLimitSt4 = 4;







    MAH = 10000;
    SpdRstSpeedLim = 8;

    TiltZadState5 = 100;

    SensOrder1 = 0;


    KpMustBe = 100;
    KpNoMan = 20;
    KdNoMan = 0;
    KiNoMan = 7;
    KpKpSpd = 0;

    KGYRO = 0.997;
    KACC = 1 - KGYRO;




    SensorLessTimerConst2 = 35;
    SenosrlessPWM1_2Const = 750;
    SensorLessTimerConstMin = 12;

    CalibrationGyroX = -220; //389;
    CalibrationGyroY = 82; //-138;
    CalibrationGyroZ = -164; //50;
    CalibrationAccX = 328;
    CalibrationAccY = 143;
    CalibrationAccZ = 990;

    MaxSpeed = 50;


    StartRotNoMan = 1015;

    KFilterPrev = 96;
    KFilter = 128 - KFilterPrev;
    CurrLimitWork = 2;
    if (!Sensorless)
        CurrLimit = CurrLimitWork;
    ChangeCVR();




    KpSPDMove = 1;
    KdSPD = 0;
    KiSPD = 0;
    AngleLimitMove = 4;
    SpeedLimit1 = 5;

    if (Unicycle) {
        StatFlgs.StatusFlags = 0x30;
        Unicycle = 1;

        SensorThresholdDn = 1000;
    } else {
        SensorThresholdDn = 800;
        StatFlgs.StatusFlags = 0x2214; //0x30;

    }
    SensorThresholdUp = 3200;

    UseTmr = 0;
    SmoothBreak = 1;

    CalibrHalls = 0;

    XLimit = 30;
    YLimit = 20;
    UBatLow = 41;
#if !defined VECTOR
#if !defined ISOLATED                               
    float UBtFl = (float) UBatLow * (float) 38.388;
    UBtLim1 = (unsigned int) UBtFl;
    UBtLim2 = UBtLim1 + 115;
#else
    float UBtFl = (float) UBatLow / (float) 0.4167965;
    UBtLim1 = (unsigned int) UBtFl;
    UBtLim2 = UBtLim1 + 7;
#endif    
#else
    float UBtFl = (float) UBatLow * (float) 38.388;
    UBtLim1 = (unsigned int) UBtFl;
    UBtLim2 = UBtLim1 + 115;
#endif
    CntMixedModeMax = 30;
    MixedModeLevelOn = 100;
    SpeedLimit2 = 10;
    SpeedLimit3 = 20;
    NumSpeedLimit = 1;
    CurrMixed = 25;
    KpMax = 700;


    SpdKpMax = 10;
    MixedModeLevelOff = 100;
    KpCurr = 0.02;
    Ki_PWM_Mode = 10;


    KpWheelingMem = 201;
    KpMustBe = KpWheelingMem;
    SetKpMustBe_UP();


    KiWheelingMem = 0.55;
    KiMustBe = KiWheelingMem;
    SetKi_UP();


    TiltZadWheeling = -4;
    TiltZadTmp = TiltZadWheeling;


    KiTemperIN = 1;
    KpTemperIN = 300;
    KpTemperOUT = 300;


    //OneTwoLeg
    KiTemperOUT = 1; //1
    MAX_PWM_Revers = 30;
    MaxSpdRevers = 10;



    if (Unicycle)//4
        KpRotOneTwoLeg = 0;
    else
        KpRotOneTwoLeg = 0.12;

    if (Unicycle)//5
        KiRotOneTwoLeg = 0;
    else
        KiRotOneTwoLeg = 0.0008;


    AutoPID_On_CntConst = 1250;




    Diametr1 = 610;
    PhasesPerRev1 = 138;
    UBatHiMem = 55;
    UBatHi = (unsigned int) ((float) UBatHiMem * (float) 38.388);


    //Fresman


    BreakThresholdDn = 800;
    BreakThresholdUp = 2900;
    KTemperatureSPDControl = 0.01;
    Profile = 1;

    CurrPhaseLimitWork = 209;
    StartRotFreshmanL = 50;
    CurrUstSpd0 = 100;
    CurrPhaseLimitSpd0 = 100;
    CurrLimitSpd0 = 0;
    MaxAngleStopBreak = 4;


    BeepPauseConstAlm = 200;
    BzOnCntSeriaConstAlm = 200;
    CntSingleBeepAlm = 30;

    DiffAlfaConstL = 3;
    DiffAlfaConstH = 5;

    ZeroCurr1 = 1018;



    Timer1Mem = 5;
    Timer2Mem = 10;




    //OneTwoLeg1


    SlowStrtSpd = 5;
    AntiPolicePower = 25;


    GyroZFlTurn = 1000;




    Spd0TimerConst = 250;


    StartRotOneTwoLeg_1 = 18; //7


    DirPWM1 = Dr1;








    KdOneTwoLeg = 0;


    Beep_10m = 0;
    Unicycle = 0;
    NoAutoTrm = 0;
    SpeedControl = 0;
    DoNotTestBMS = 1;
    Sensorless = 0;
    BreakInvBtn = 0;
    Tmprt1 = 0;
    Tmprt2 = 0;
    Tmprt3 = 0;
    Tmprt4 = 0;
    Lock = 0;

    TrapezoidaRAM1 = 0;
    CURRENT_PROTECTION = 1;
    PWM32Bits = 1;
    StrongModeMem = 0;
}

void AccToMemALM(void) {
    AlfaXResAlmMem = AlfaXResTmpAlm;
    AlfaYResAlmMem = AlfaYResTmpAlm;
    AlfaZResAlmMem = AlfaZResTmpAlm;
}

void AlmOn(void) {
    AccToMemALM();
    AlarmOn = 1;
    HornAlmOn = 1;
    HorningL = 0;
    HorningH = 0;
#if !defined VECTORS
    Horn = 1;
#else
    //Horn=0;
    OC3R = 0;
#endif
    SoundNum = 12;
    VectorMem = 0;

}

void AlmOff(void) {
    AlarmOn = 0;

#if !defined VECTORS
    Horn = 1;
#else
    //Horn=0;
    OC3R = 0;
#endif
    SoundNum = 11;
    HorningL = 0;
    HorningH = 0;
}

void Alm(void) {
    int DiffAlfaX, DiffAlfaY, DiffAlfaZ, DiffAlfa, DiffConstH, DiffConstL;

    if (HvAccData) {
        HvAccData = 0;
    }

    DiffAlfaX = AlfaXResAlmMem - AccXAvRes;
    DiffAlfaY = AlfaYResAlmMem - AccYAvRes;
    DiffAlfaZ = AlfaZResAlmMem - AccZAvRes;

    if (DiffAlfaX < 0)
        DiffAlfaX = -DiffAlfaX;
    if (DiffAlfaY < 0)
        DiffAlfaY = -DiffAlfaY;
    if (DiffAlfaZ < 0)
        DiffAlfaZ = -DiffAlfaZ;


    DiffAlfa = DiffAlfaX;
    if (DiffAlfa < DiffAlfaY)
        DiffAlfa = DiffAlfaY;
    if (DiffAlfa < DiffAlfaZ)
        DiffAlfa = DiffAlfaZ;


    DiffConstH = ((int) DiffAlfaConstH)*100;

    if (DiffAlfa > DiffConstH) {
        if (!HorningH) {
HrnH:
            HorningH = 1;

            if (!Sounds)
                SoundNum = 14;


            return;
        }
    }




    DiffAlfaX = AlfaXResAlmMem - AccXFl;
    DiffAlfaY = AlfaYResAlmMem - AccYFl;
    DiffAlfaZ = AlfaZResAlmMem - AccZFl;

    if (DiffAlfaX < 0)
        DiffAlfaX = -DiffAlfaX;
    if (DiffAlfaY < 0)
        DiffAlfaY = -DiffAlfaY;
    if (DiffAlfaZ < 0)
        DiffAlfaZ = -DiffAlfaZ;


    DiffAlfa = DiffAlfaX;
    if (DiffAlfa < DiffAlfaY)
        DiffAlfa = DiffAlfaY;
    if (DiffAlfa < DiffAlfaZ)
        DiffAlfa = DiffAlfaZ;


    DiffConstL = ((int) DiffAlfaConstL)*100;

    if (DiffAlfa > DiffConstL) {
        if ((!HorningL)&&(!HorningH)) {
            HorningL = 1;
            if (!Sounds)
                SoundNum = 10;

            if (CntHorningL) {
                CntHrnL++;
                if (CntHrnL > CntHrnLConst)
                    goto HrnH;
            }
            CntHorningL = 1500;
        }
    }


}

void Rbw(void) {

    if (!Robowell)
        return;
    if (OnTransmittHC05)
        return;
    if (HC05_BUSY)
        return;
    unsigned int Tm, TmSer = SerNumber;



    Str[0] = 'A';
    Str[1] = 'T';
    Str[2] = '+';
    Str[3] = 'N';
    Str[4] = 'A';
    Str[5] = 'M';
    Str[6] = 'E';
    Str[7] = '=';
    Str[8] = 'V';
    Str[9] = 'e';
    Str[10] = 'c';
    Str[11] = 't';
    Str[12] = 'o';
    Str[13] = 'r';
    Str[14] = '-';
#if defined VECTORS
    Str[15] = 'S';
#else
    Str[15] = 'M';
#endif
    Str[16] = ':';
    Tm = TmSer - (TmSer / 10)*10 + 0x30;
    TmSer = TmSer / 10;
    Str[21] = Tm;
    Tm = TmSer - (TmSer / 10)*10 + 0x30;
    TmSer = TmSer / 10;
    Str[20] = Tm;
    Tm = TmSer - (TmSer / 10)*10 + 0x30;
    TmSer = TmSer / 10;
    Str[19] = Tm;
    Tm = TmSer - (TmSer / 10)*10 + 0x30;
    TmSer = TmSer / 10;
    Str[18] = Tm;
    Tm = TmSer - (TmSer / 10)*10 + 0x30;
    TmSer = TmSer / 10;
    Str[17] = Tm;



    HC05_BUSY = 1;
    Robowell = 0;
#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 1;
#else
    KEY_BT = 0;
#endif
#else
    KEY_BT = 1;
#endif
    Nop();
    long int g;
    for (g = 0; g < 150000; g++);
    HvReplyHC05 = 0;
    MyTimeOut = 550;
    AT_Rec = 1;
    RecMassHC05[0] = 3;
    if (NameRBW)
        //   TrmHC05_AT("AT+NAME=RoboWell",sizeof("AT+NAME=RoboWell"));
        TrmHC05_AT(Str, sizeof (Str) + 1); //
    //TrmHC05_AT("AT+ORGL", sizeof ("AT+ORGL"));

    if (SpeedRBW)
        TrmHC05_AT("AT+UART=38400,1,0", sizeof ("AT+UART=38400,1,0")); //
    //                            TrmHC05_AT("AT+BAUD6",sizeof("AT+BAUD6"));//

    while ((!HvReplyHC05)&&(MyTimeOut));
    if (RecMassHC05[0] == 'O') {
        SoundNum = 1;
    } else {
        Nop();
        Nop();
        Nop();
    }
    AT_Rec = 0;
#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 0;
#else
    KEY_BT = 1;
#endif
#else
    KEY_BT = 0;
#endif
}

void GetRbw(void) {

    if (!GetRobowell)
        return;
    if (OnTransmittHC05)
        return;
    if (HC05_BUSY)
        return;


    HC05_BUSY = 1;
    GetRobowell = 0;

#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 1;
#else
    KEY_BT = 0;
#endif
#else
    KEY_BT = 1;
#endif
    Nop();
    long int g;
    for (g = 0; g < 150000; g++);
    HvReplyHC05 = 0;
    MyTimeOut = 550;
    AT_Rec = 1;
    RecMassHC05[0] = 3;
    if (NameRBW)
        TrmHC05_AT("AT+NAME?", sizeof ("AT+NAME?")); //
    if (SpeedRBW)
        TrmHC05_AT("AT+UART?", sizeof ("AT+UART?")); //

    while ((!HvReplyHC05)&&(MyTimeOut));
    Nop();
    Nop();
    Nop();
    AT_Rec = 0;
#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 0;
#else
    KEY_BT = 1;
#endif
#else
    KEY_BT = 0;
#endif
}

void CalibrateCurr(void) {
    long int tm1;
    if (!Calibrating) {
        ZeroCurr1Summ = 0;
        CntCalibrateCurr = 0;
    } else {
        ZeroCurr1Summ = ZeroCurr1Summ + (long int) Crr1;
        CntCalibrateCurr++;
        if (CntCalibrateCurr >= 1024) {
            Calibrating = 0;
            tm1 = ZeroCurr1Summ >> 10;
            ZeroCurr1 = tm1;
            tm1 = tm1 << 10;
            ZeroCurr1Summ = ZeroCurr1Summ - tm1;
            if (ZeroCurr1Summ > 511)
                ZeroCurr1++;



            OptionsToMass();
            MustTrmFlashMass = 1;

        }

    }

}

void InitSensorsNear(void) {
    NearSensors[0][0] = 0; //_L
    NearSensors[0][1] = 0; //_R

    NearSensors[1][0] = 5; //1_L
    NearSensors[1][1] = 3; //1_R

    NearSensors[2][0] = 3; //2_L
    NearSensors[2][1] = 6; //2_R

    NearSensors[3][0] = 1; //3_L
    NearSensors[3][1] = 2; //3_R

    NearSensors[4][0] = 6; //4_L
    NearSensors[4][1] = 5; //4_R

    NearSensors[5][0] = 4; //5_L
    NearSensors[5][1] = 1; //5_R

    NearSensors[6][0] = 2; //6_L
    NearSensors[6][1] = 4; //6_R

    NearSensors[7][0] = 255; //_L
    NearSensors[7][1] = 255; //_R

}

void SetTmrConst(void) {
    if (UseTmr == 1) {
        TimerConst = Timer1Mem;
        TimerConst = TimerConst * 30000;
    }
    if (UseTmr == 2) {
        TimerConst = Timer2Mem;
        TimerConst = TimerConst * 30000;
    }
}




//Init: BytesToRec  StartReceiveBMS  LongForTrmBMS

void DataFrmBMS(void) {
#if !defined BMS
    return;
#endif
    unsigned char BatErrTmp = BatErr, BMS_V_LowPrev = BMS_V_Low;
    unsigned char *ptr;



    if (((BMS1Err > 100) || (BMS2Err > 100) || (BMS3Err > 100) || (BMS4Err > 100) || (BMS5Err > 100))) {
        BMSErr = 1;
    }

    if (((BMS1Err <= 100)&&(BMS2Err <= 100)&&(BMS3Err <= 100)&&(BMS4Err <= 100)&&(BMS5Err <= 100))) {
        BMSErr = 0;
    }

    if (DoNotTestBMS)
        BMSErr = 0;

    if (!HvPacketBMS)
        return;

    switch (BMSAddrCnt) {
        case 0:
            if (GettingStorage) {

                GettingStorage = 0;

                ptr = (unsigned char *) &Odometr;
                *ptr = BMSRecMass[0];
                ptr++;
                *ptr = BMSRecMass[1];
                ptr++;
                *ptr = BMSRecMass[2];
                ptr++;
                *ptr = BMSRecMass[3];

                ptr = (unsigned char *) &Distance;
                *ptr = BMSRecMass[4];
                ptr++;
                *ptr = BMSRecMass[5];
                ptr++;
                *ptr = BMSRecMass[6];
                ptr++;
                *ptr = BMSRecMass[7];

                ptr = (unsigned char *) &CurrTuda1;
                *ptr = BMSRecMass[8];
                ptr++;
                *ptr = BMSRecMass[9];
                ptr++;
                *ptr = BMSRecMass[10];
                ptr++;
                *ptr = BMSRecMass[11];

                ptr = (unsigned char *) &CurrRegen1;
                *ptr = BMSRecMass[12];
                ptr++;
                *ptr = BMSRecMass[13];
                ptr++;
                *ptr = BMSRecMass[14];
                ptr++;
                *ptr = BMSRecMass[15];









                HvPacketBMS = 0;
                return;
            }
            //    HvPacketBMS=0;
            BMS1Err = 0;
            V1 = BMSRecMass[2];
            V1 = V1 << 8;
            V1 = V1 + BMSRecMass[1];
            V1 = V1 << 8;
            V1 = V1 + BMSRecMass[0];

            V2 = BMSRecMass[5];
            V2 = V2 << 8;
            V2 = V2 + BMSRecMass[4];
            V2 = V2 << 8;
            V2 = V2 + BMSRecMass[3];

            V3 = BMSRecMass[8];
            V3 = V3 << 8;
            V3 = V3 + BMSRecMass[7];
            V3 = V3 << 8;
            V3 = V3 + BMSRecMass[6];

            V4 = BMSRecMass[11];
            V4 = V4 << 8;
            V4 = V4 + BMSRecMass[10];
            V4 = V4 << 8;
            V4 = V4 + BMSRecMass[9];
            BMSAddrCnt = 1;

            if (V1 & 0x800000)
                BatteryKeys = BatteryKeys | 1;
            else
                BatteryKeys = BatteryKeys & 0xfffffffe;
            if (V2 & 0x800000)
                BatteryKeys = BatteryKeys | 2;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 2);
            if (V3 & 0x800000)
                BatteryKeys = BatteryKeys | 4;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 4);
            if (V4 & 0x800000)
                BatteryKeys = BatteryKeys | 8;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 8);

            if (V1 & 0x400000)
                ChagerKeys = ChagerKeys | 1;
            else
                ChagerKeys = ChagerKeys & 0xfffffffe;

            if (V2 & 0x400000)
                ChagerKeys = ChagerKeys | 2;
            else
                ChagerKeys = ChagerKeys & (0xffffffff - 2);

            if (V3 & 0x400000)
                ChagerKeys = ChagerKeys | 4;
            else
                ChagerKeys = ChagerKeys & (0xffffffff - 4);



            V1 = V1 & 0x00ffff;
            V2 = V2 & 0x00ffff;
            V3 = V3 & 0x00ffff;
            V4 = V4 & 0x00ffff;


            if (V1 < V_MIN_OFF) {
                BatErr = 1;
                BMS_V_Low = 1;
            } else {

            }
            if (V2 < V_MIN_OFF) {
                BatErr = 2;
                BMS_V_Low = 1;
            }
            if (V3 < V_MIN_OFF) {
                BatErr = 3;
                BMS_V_Low = 1;
            }
            if (V4 < V_MIN_OFF) {
                BatErr = 4;
                BMS_V_Low = 1;
            }




            break;

        case 1:
            //  HvPacketBMS=0;
            BMS2Err = 0;
            V5 = BMSRecMass[2];
            V5 = V5 << 8;
            V5 = V5 + BMSRecMass[1];
            V5 = V5 << 8;
            V5 = V5 + BMSRecMass[0];

            V6 = BMSRecMass[5];
            V6 = V6 << 8;
            V6 = V6 + BMSRecMass[4];
            V6 = V6 << 8;
            V6 = V6 + BMSRecMass[3];

            V7 = BMSRecMass[8];
            V7 = V7 << 8;
            V7 = V7 + BMSRecMass[7];
            V7 = V7 << 8;
            V7 = V7 + BMSRecMass[6];

            V8 = BMSRecMass[11];
            V8 = V8 << 8;
            V8 = V8 + BMSRecMass[10];
            V8 = V8 << 8;
            V8 = V8 + BMSRecMass[9];
            BMSAddrCnt = 2;

            if (V5 & 0x800000)
                BatteryKeys = BatteryKeys | 0x10;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x10);
            if (V6 & 0x800000)
                BatteryKeys = BatteryKeys | 0x20;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x20);
            if (V7 & 0x800000)
                BatteryKeys = BatteryKeys | 0x40;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x40);
            if (V8 & 0x800000)
                BatteryKeys = BatteryKeys | 0x80;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x80);

            if (V5 & 0x400000)
                ChagerKeys = ChagerKeys | 8;
            else
                ChagerKeys = ChagerKeys & (0xffffffff - 0x8);

            V5 = V5 & 0x00ffff;
            V6 = V6 & 0x00ffff;
            V7 = V7 & 0x00ffff;
            V8 = V8 & 0x00ffff;

            if (V5 < V_MIN_OFF) {
                BatErr = 5;
                BMS_V_Low = 1;
            }
            if (V6 < V_MIN_OFF) {
                BatErr = 6;
                BMS_V_Low = 1;
            }
            if (V7 < V_MIN_OFF) {
                BatErr = 7;
                BMS_V_Low = 1;
            }
            if (V8 < V_MIN_OFF) {
                BatErr = 8;
                BMS_V_Low = 1;
            }


            break;
        case 2:
            //HvPacketBMS=0;
            BMS3Err = 0;
            V9 = BMSRecMass[2];
            V9 = V9 << 8;
            V9 = V9 + BMSRecMass[1];
            V9 = V9 << 8;
            V9 = V9 + BMSRecMass[0];

            V10 = BMSRecMass[5];
            V10 = V10 << 8;
            V10 = V10 + BMSRecMass[4];
            V10 = V10 << 8;
            V10 = V10 + BMSRecMass[3];

            V11 = BMSRecMass[8];
            V11 = V11 << 8;
            V11 = V11 + BMSRecMass[7];
            V11 = V11 << 8;
            V11 = V11 + BMSRecMass[6];

            V12 = BMSRecMass[11];
            V12 = V12 << 8;
            V12 = V12 + BMSRecMass[10];
            V12 = V12 << 8;
            V12 = V12 + BMSRecMass[9];
            BMSAddrCnt = 3;

            if (V9 & 0x800000)
                BatteryKeys = BatteryKeys | 0x100;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x100);

            if (V10 & 0x800000)
                BatteryKeys = BatteryKeys | 0x200;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x200);

            if (V11 & 0x800000)
                BatteryKeys = BatteryKeys | 0x400;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x400);

            if (V12 & 0x800000)
                BatteryKeys = BatteryKeys | 0x800;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x800);


            if (V9 & 0x400000)
                ChagerKeys = ChagerKeys | 0x10;
            else
                ChagerKeys = ChagerKeys & (0xffffffff - 0x10);

            V9 = V9 & 0x00ffff;
            V10 = V10 & 0x00ffff;
            V11 = V11 & 0x00ffff;
            V12 = V12 & 0x00ffff;

            if (V9 < V_MIN_OFF) {
                BatErr = 9;
                BMS_V_Low = 1;
            }
            if (V10 < V_MIN_OFF) {
                BatErr = 10;
                BMS_V_Low = 1;
            }
            if (V11 < V_MIN_OFF) {
                BatErr = 11;
                BMS_V_Low = 1;
            }
            if (V12 < V_MIN_OFF) {
                BatErr = 12;
                BMS_V_Low = 1;
            }



            break;
        case 3:
            //HvPacketBMS=0;
            BMS4Err = 0;
            V13 = BMSRecMass[2];
            V13 = V13 << 8;
            V13 = V13 + BMSRecMass[1];
            V13 = V13 << 8;
            V13 = V13 + BMSRecMass[0];

            V14 = BMSRecMass[5];
            V14 = V14 << 8;
            V14 = V14 + BMSRecMass[4];
            V14 = V14 << 8;
            V14 = V14 + BMSRecMass[3];

            V15 = BMSRecMass[8];
            V15 = V15 << 8;
            V15 = V15 + BMSRecMass[7];
            V15 = V15 << 8;
            V15 = V15 + BMSRecMass[6];

            V16 = BMSRecMass[11];
            V16 = V16 << 8;
            V16 = V16 + BMSRecMass[10];
            V16 = V16 << 8;
            V16 = V16 + BMSRecMass[9];
            BMSAddrCnt = 4;

            if (V13 & 0x800000)
                BatteryKeys = BatteryKeys | 0x1000;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x1000);

            if (V14 & 0x800000)
                BatteryKeys = BatteryKeys | 0x2000;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x2000);

            if (V15 & 0x800000)
                BatteryKeys = BatteryKeys | 0x4000;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x4000);

            if (V16 & 0x800000)
                BatteryKeys = BatteryKeys | 0x8000;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x8000);

            if (V13 & 0x400000)
                ChagerKeys = ChagerKeys | 0x20;
            else
                ChagerKeys = ChagerKeys & (0xffffffff - 0x20);

            V13 = V13 & 0x00ffff;
            V14 = V14 & 0x00ffff;
            V15 = V15 & 0x00ffff;
            V16 = V16 & 0x00ffff;




            if (V13 < V_MIN_OFF) {
                BatErr = 13;
                BMS_V_Low = 1;
            }
            if (V14 < V_MIN_OFF) {
                BatErr = 14;
                BMS_V_Low = 1;
            }
            if (V15 < V_MIN_OFF) {
                BatErr = 15;
                BMS_V_Low = 1;
            }
            if (V16 < V_MIN_OFF) {
                BatErr = 16;
                BMS_V_Low = 1;
            }


            break;


        case 4:
            //HvPacketBMS=0;
            BMS5Err = 0;
            V17 = BMSRecMass[2];
            V17 = V17 << 8;
            V17 = V17 + BMSRecMass[1];
            V17 = V17 << 8;
            V17 = V17 + BMSRecMass[0];

            V18 = BMSRecMass[5];
            V18 = V18 << 8;
            V18 = V18 + BMSRecMass[4];
            V18 = V18 << 8;
            V18 = V18 + BMSRecMass[3];


            if (V17 & 0x800000)
                BatteryKeys = BatteryKeys | 0x10000;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x10000);

            if (V18 & 0x800000)
                BatteryKeys = BatteryKeys | 0x20000;
            else
                BatteryKeys = BatteryKeys & (0xffffffff - 0x20000);


            if (V17 & 0x400000)
                ChagerKeys = ChagerKeys | 0x40;
            else
                ChagerKeys = ChagerKeys & (0xffffffff - 0x40);

            V17 = V17 & 0x00ffff;
            V18 = V18 & 0x00ffff;

            BMSAddrCnt = 0;



            if (V17 < V_MIN_OFF) {
                BatErr = 17;
                BMS_V_Low = 1;
            }
            if (V18 < V_MIN_OFF) {
                BatErr = 18;
                BMS_V_Low = 1;
            }


            break;




    }

    Nop();
    Nop();
    Nop();



    Vmin = V1;
    if (Vmin > V2)
        Vmin = V2;
    if (Vmin > V3)
        Vmin = V3;
    if (Vmin > V4)
        Vmin = V4;
    if (Vmin > V5)
        Vmin = V5;
    if (Vmin > V6)
        Vmin = V6;
    if (Vmin > V7)
        Vmin = V7;
    if (Vmin > V8)
        Vmin = V8;
    if (Vmin > V9)
        Vmin = V9;
    if (Vmin > V10)
        Vmin = V10;
    if (Vmin > V11)
        Vmin = V11;
    if (Vmin > V12)
        Vmin = V12;
    if (Vmin > V13)
        Vmin = V13;
    if (Vmin > V14)
        Vmin = V14;
    if (Vmin > V15)
        Vmin = V15;
    if (Vmin > V16)
        Vmin = V16;
    if (Vmin > V17)
        Vmin = V17;
    if (Vmin > V18)
        Vmin = V18;

    //Vmin=VminTST;

    if (Vmin > 2500)
        StateInd = 1;



    if ((V1 >= V_MIN_OFF)&&(V2 >= V_MIN_OFF)&&(V3 >= V_MIN_OFF)&&(V4 >= V_MIN_OFF)&&(V5 >= V_MIN_OFF)&&(V6 >= V_MIN_OFF)&&(V7 >= V_MIN_OFF)&&(V8 >= V_MIN_OFF)&&(V9 >= V_MIN_OFF)&&(V10 >= V_MIN_OFF)&&(V11 >= V_MIN_OFF)&&(V12 >= V_MIN_OFF)&&(V13 >= V_MIN_OFF)&&(V14 >= V_MIN_OFF)&&(V15 >= V_MIN_OFF)&&(V16 >= V_MIN_OFF)&&(V17 >= V_MIN_OFF)&&(V18 >= V_MIN_OFF))
        BMS_V_Low = 0;

    if ((V1 >= V_min_OverV) || (V2 >= V_min_OverV) || (V3 >= V_min_OverV) || (V4 >= V_min_OverV) || (V5 >= V_min_OverV) || (V6 >= V_min_OverV) || (V7 >= V_min_OverV) || (V8 >= V_min_OverV) || (V9 >= V_min_OverV) || (V10 >= V_min_OverV) || (V11 >= V_min_OverV) || (V12 >= V_min_OverV) || (V13 >= V_min_OverV) || (V14 >= V_min_OverV) || (V15 >= V_min_OverV) || (V16 >= V_min_OverV) || (V17 >= V_min_OverV) || (V18 >= V_min_OverV)) {
        if (!RegenOver3900) {
            RegenOver3900 = 1;

        }
    } else {
        if (RegenOver3900) {
            RegenOver3900 = 0;
            if (!Sounds)
                SoundNum = 1;

        }
    }


    if ((V1 >= V_MIN_Sound)&&(V2 >= V_MIN_Sound)&&(V3 >= V_MIN_Sound)&&(V4 >= V_MIN_Sound)&&(V5 >= V_MIN_Sound)&&(V6 >= V_MIN_Sound)&&(V7 >= V_MIN_Sound)&&(V8 >= V_MIN_Sound)&&(V9 >= V_MIN_Sound)&&(V10 >= V_MIN_Sound)&&(V11 >= V_MIN_Sound)&&(V12 >= V_MIN_Sound)&&(V13 >= V_MIN_Sound)&&(V14 >= V_MIN_Sound)&&(V15 >= V_MIN_Sound)&&(V16 >= V_MIN_Sound)&&(V17 >= V_MIN_Sound)&&(V18 >= V_MIN_Sound))
        BMS_L = 0;
    else {
        if ((V1 >= V_MIN_Pre_OFF)&&(V2 >= V_MIN_Pre_OFF)&&(V3 >= V_MIN_Pre_OFF)&&(V4 >= V_MIN_Pre_OFF)&&(V5 >= V_MIN_Pre_OFF)&&(V6 >= V_MIN_Pre_OFF)&&(V7 >= V_MIN_Pre_OFF)&&(V8 >= V_MIN_Pre_OFF)&&(V9 >= V_MIN_Pre_OFF)&&(V10 >= V_MIN_Pre_OFF)&&(V11 >= V_MIN_Pre_OFF)&&(V12 >= V_MIN_Pre_OFF)&&(V13 >= V_MIN_Pre_OFF)&&(V14 >= V_MIN_Pre_OFF)&&(V15 >= V_MIN_Pre_OFF)&&(V16 >= V_MIN_Pre_OFF)&&(V17 >= V_MIN_Pre_OFF)&&(V18 >= V_MIN_Pre_OFF))
            BMS_L = 1;
        else
            BMS_L = 2;

    }


    if (DoNotTestBMS) {
        BMS_V_Low = 0;
        BMS_L = 0;
    }


    if ((BatErrTmp != BatErr)&&(BatErr != 0)) {
        //WriteErr_Fl=1;
    }

    if (RegenOver3900) {
        if (!Sounds)
            SoundNum = 8;
    }



    if (BMS_V_Low) {
        if (!Sounds)
            SoundNum = 8;
    }
    if ((!BMS_V_Low)&&(BMS_V_LowPrev)&&(Sounds != 0)) {
        Sounds = 1;
    }
    BMSDelayCnt = BMSDelayCnt_CONST;
    HvPacketBMS = 0;

}

void ErrorSound(void) {
    if ((!Sounds)&&(BMSErr || ((!TiltTimoutCnt)&&(!Unicycle)))) {
        if (!Sounds)
            SoundNum = 254;


    }
    if ((Sounds) && ErrorSnd&&!BMSErr && TiltTimoutCnt) {
        ErrorSnd = 0;
        SoundNum = 1;
    }



}

void Dbg(void) {
    unsigned long int TmpO = Odometr / (ImpNa10Metr / 10);
    return;
    TmpO = TmpO / 1000;
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    if (TmpO > 1000) {
        Nop();
        Nop();
        Nop();
        if (!DbgOdmtr) {
            {
                BuzzerOnEvent = 9;
                BuzzerMacroOn//Buzzer=1;
            }
        }
    }

}


void CountSpd(void) {

    Trapezium10kHzLo = Round(((float) 38) / ImpToKmH1_t);
    Trapezium10kHzHi = Round(((float) 40) / ImpToKmH1_t);
    Trapezium5kHzLo = Round(((float) 18) / ImpToKmH1_t);
    Trapezium5kHzHi = Round(((float) 20) / ImpToKmH1_t);


    SlowSpeedForKpFl = (float) SlowSpeedForKp / ImpToKmH1_t;

    Spd1KpLevel = Round((float) SpdKpMax / ImpToKmH1_t);
    Spd1KdLevel = Round((float) SpdKdMax / ImpToKmH1_t);


    SpdKiLevel = Round(((float) SpdKiMin) / ImpToKmH1_t);



    MixedModeSlowSpeedFl = ((float) MixedModeSlowSpeed) / ImpToKmH1_t;

    Spd1Fl = (float) Spd1Res*ImpToKmH1_t;
    if (Spd1Fl < 0)
        Spd1FlPlus = -Spd1Fl;
    else
        Spd1FlPlus = Spd1Fl;
    HvSpdFloat_Fl = 1;

    Spd1USTKMH = Spd1UST * ImpToKmH1_t * 10;

    if (Spd1USTKMH < 0)
        Spd1USTKMH = -Spd1USTKMH;



    HallDelayMaxSPDNoKMH = ((float) HallDelayMaxSPD) / ImpToKmH1_t;

    K_HallDelay = ((float) (HallDelay1MaxSPD_F - HallDelayMem1_F)) / HallDelayMaxSPDNoKMH;


#if !defined VECTOR
    if (HvUBT) {
        HvUBT = 0;
        UBT = ((float) UBT)*1.043956;
    }
#endif

}

void SoundNoBMS(void) {
    if (Sounds == 0) {
        SoundNum = 8;
    }

}

void VectorInit(void) {
    MAX_PWM = MAX_PWM_CONST;
    if (MAX_PWM == 0)
        return;
    Vector = 1;
    //   IPC22bits.U4RXIP = 7;
    //    IPC20bits.U3RXIP = 7;
    //    IPC2bits.T3IP = 7;
    //    IPC5bits.AD2IP=0;
#if !defined SENSORLESS_TEST    
    IEC1bits.AD2IE = 0;
#endif


    T4_5Init();
    T8Init();


    if (SIN_MIDDLE)
        StrongMode = 1;

    SensorlessInitialized = 0;
    InitPWM_Vector();

    //AD2CON1 = 0;

}

void T4_5Init(void) {
    T5CONbits.TON = 0; // Stop any 16-bit Timer3 operation
    T4CONbits.TON = 0; // Stop any 16/32-bit Timer3 operation
    T4CONbits.T32 = 1; // Enable 32-bit Timer mode
    T4CONbits.TCS = 0; // Select internal instruction cycle clock
    T4CONbits.TGATE = 0; // Disable Gated Timer mode
    T4CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR5 = 0x00; // Clear 32-bit Timer (msw)
    TMR4 = 0x00; // Clear 32-bit Timer (lsw)
    PR4 = 0x2d00; // Load 32-bit period value (lsw)
    PR5 = 0x131; // Load 32-bit period value (msw)
    IPC7bits.T5IP = 0x01; // Set Timer3 Interrupt Priority Level
    IFS1bits.T5IF = 0; // Clear Timer3 Interrupt Flag
    IEC1bits.T5IE = 1; // Enable Timer3 interrupt
    T4CONbits.TON = 1; // Start 32-bit Timer

}

void __attribute__((interrupt, auto_psv)) _T5Interrupt(void) {
    IFS1bits.T5IF = 0;

    T45Over = 1;
    T45OverFl = 1;
}

void T6_7Init(void) {

/*#if defined HighDataSpdUART
    TMR6 = 0;
    T6CON = 0x8000;
    PR6 = 0xffff; //33333; //500 Hz Int
    //    IPC12bits.T6IP = 6; //5;//6;//
    IPC11bits.T6IP = 7;
    IEC2bits.T6IE = 1;
#else
    */
    T7CONbits.TON = 0; // Stop any 16-bit Timer3 operation
    T6CONbits.TON = 0; // Stop any 16/32-bit Timer3 operation
    T6CONbits.T32 = 1; // Enable 32-bit Timer mode
    T6CONbits.TCS = 0; // Select internal instruction cycle clock
    T6CONbits.TGATE = 0; // Disable Gated Timer mode
    T6CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR7 = 0x00; // Clear 32-bit Timer (msw)
    TMR6 = 0x00; // Clear 32-bit Timer (lsw)
    PR6 = 0; //0x2d00; // Load 32-bit period value (lsw)
    PR7 = 0; //0x131; // Load 32-bit period value (msw)
    IPC12bits.T7IP = 0x06; // Set Timer3 Interrupt Priority Level
    IFS3bits.T7IF = 0; // Clear Timer3 Interrupt Flag
    IEC3bits.T7IE = 1; // Enable Timer3 interrupt
    T6CONbits.TON = 1; // Start 32-bit Timer

//#endif

}

void __attribute__((interrupt, auto_psv)) _T6Interrupt(void) {

    T6Hi++;
    IFS2bits.T6IF = 0;
}

void __attribute__((interrupt, auto_psv)) _T7Interrupt(void) {
    IFS3bits.T7IF = 0;
/*
#if defined HighDataSpdUART
    return;
#endif
*/


    if (Sensorless) {
        if (!SensorlessNotBEMF) {
            if (!DirPWM1)
                Sensor1_Prev = NearSensors[SensorBEMF][0];
            else
                Sensor1_Prev = NearSensors[SensorBEMF][1];
            Sensor1 = Sensor1_Prev;
            Phases1();

        }
    }



}

void TrapeziumInit(void) {
    MAX_PWM = MAX_PWM_CONST;
    //   IPC22bits.U4RXIP = 7;
    // IPC20bits.U3RXIP = 7;
    //IPC2bits.T3IP = 7;
    //IPC5bits.AD2IP=0;
#if !defined SENSORLESS_TEST    
    IEC1bits.AD2IE = 0;
#endif


    T8CON = 0;
    T4CON = 0; //7777777777777777777777777777777777777777777777777777777777777777777777777777
    T5CON = 0; //7777777777777777777777777777777777777777777777777777777777777777777777777777

    T2CON = 0;
    T6CON = 0;
    T7CON = 0;

    SensorlessInitialized = 0;
    //InitPWM();
    InitPWM_Vector();

//    AD2CON1 = 0;

}

void T8Init(void) {
    TMR8 = 0;
    T8CON = 0x8000;
    PR8 = 33333; //500 Hz Int
    IPC12bits.T8IP = 6; //5;//6;//
    IEC3bits.T8IE = 1;

}

void __attribute__((interrupt, auto_psv)) _T8Interrupt(void) {

    /*
        if (TMR6>50000)
        {
            Phase1Period1Up++;
            Phase1Period1Show=TMR6;
            T6Hi=T6Hi<<16;
            Phase1Period1Show=Phase1Period1Show+T6Hi;
        }
     */

    //Phase1Period1Show++;
    //    Phase1Period1Show=TMR6;
    TMR6 = 0;
    T6Hi = 0;

    //        if (TMR8>100)



    IFS3bits.T8IF = 0;
    if (!Sensorless) {

        PR8Cnt++;



        //Phase1Period1Show=0;

        if (PR8Temp) {
            //           IEC1bits.CNIE = 0;
            PR8 = PR8Temp;

            PR8TempTemp = PR8Temp;

            PR8Temp = 0;
            //          IEC1bits.CNIE = 1;




        }

        if (PR8 < 1200) {
            PR8 = 1200;
        }


        if (HallDelayCnt_1) {
            HallDelayCnt_1--;
            if (!HallDelayCnt_1) {
                Theta1Cnt = 0;
                CanGetHalls1 = 1;

                //   Sensor1_Prev_OP=ReadSensor1_F_V();

                if (!DirPWM1) {
                    if (Forward1)
                        Sensor1_Prev_OP = ReadSensor1_F_V();
                    else
                        Sensor1_Prev_OP = ReadSensor1_B_V();
                } else {
                    if (Forward1)
                        Sensor1_Prev_OP = ReadSensor1_B_V();
                    else
                        Sensor1_Prev_OP = ReadSensor1_F_V();
                }


            }
        }


        SVPWM1();


        if (PWM32Bits) {
            //      if (Theta1Cnt<60)
            //        Theta1Cnt=Theta1Cnt+4;
            if (Theta1Cnt < 56)
                Theta1Cnt = Theta1Cnt + 8;
            else
                Theta1Cnt = 63;
        } else {
            //        if (Theta1Cnt<63)
            //      Theta1Cnt++;
            if (Theta1Cnt < 60)

                Theta1Cnt = Theta1Cnt + 4;
            else
                Theta1Cnt = 63;
        }


        //                  if (Theta1Cnt<63)
        //                  Theta1Cnt++;

        //    Theta1CntPWMSND = Theta1Cnt;

        TMR8Temp = TMR8;

    }

    //        Phase1Period1Show=TMR6;

    //Phase1Period1Up=TMR8;


}


void SetHallDelay1_F_UP(void) {
    if (HallDelay1_F < HallDelay1_FMustBe)
        HallDelay1_F_UP = 1;
    else
        HallDelay1_F_UP = 0;
}

void SetHallDelay1_B_UP(void) {
    if (HallDelay1_B < HallDelay1_BMustBe)
        HallDelay1_B_UP = 1;
    else
        HallDelay1_B_UP = 0;
}

void RdSensors(void) {
    IEC1bits.CNIE = 0;
    if (!Vector) {
        Sensor1 = ReadSensor1_B();
        Sensor1_Prev = Sensor1;
        Phases1();
        PrevForward1 = 0;
    } else {
        //        IEC3bits.T8IE = 0;
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

        Sensor1_Prev = Sensor1;
        Sensor1_Prev_OP = Sensor1_Prev;
        if (IFS3bits.T8IF)
            Phase1Period1Up = TMR8;
        IEC3bits.T8IE = 1;


    }

    IEC1bits.CNIE = 1;
}

void CalculateCalibrationHalls(void) {
    double Diff, Res;
    if (!HvCalibrationHalls)
        return;
    HvCalibrationHalls = 0;


    NearSensors[1][0] = 5; //1_L
    NearSensors[1][1] = 3; //1_R
    Diff = (double) Hall5ClrbRes - (double) Hall1ClrbRes;
    Res = Diff / (double) Hall1ClrbRes;
    Res = Res * 128;
    NearSensors[1][2] = (char) Res;

    Diff = (double) Hall3ClrbRes - (double) Hall1ClrbRes;
    Res = Diff / (double) Hall1ClrbRes;
    Res = Res * 128;
    NearSensors[1][3] = (char) Res;



    NearSensors[2][0] = 3; //2_L
    NearSensors[2][1] = 6; //2_R
    Diff = (double) Hall3ClrbRes - (double) Hall2ClrbRes;
    Res = Diff / (double) Hall2ClrbRes;
    Res = Res * 128;
    NearSensors[2][2] = (char) Res;

    Diff = (double) Hall6ClrbRes - (double) Hall2ClrbRes;
    Res = Diff / (double) Hall2ClrbRes;
    Res = Res * 128;
    NearSensors[2][3] = (char) Res;

    NearSensors[3][0] = 1; //3_L
    NearSensors[3][1] = 2; //3_R
    Diff = (double) Hall1ClrbRes - (double) Hall3ClrbRes;
    Res = Diff / (double) Hall3ClrbRes;
    Res = Res * 128;
    NearSensors[3][2] = (char) Res;

    Diff = (double) Hall2ClrbRes - (double) Hall3ClrbRes;
    Res = Diff / (double) Hall3ClrbRes;
    Res = Res * 128;
    NearSensors[3][3] = (char) Res;

    NearSensors[4][0] = 6; //4_L
    NearSensors[4][1] = 5; //4_R
    Diff = (double) Hall6ClrbRes - (double) Hall4ClrbRes;
    Res = Diff / (double) Hall4ClrbRes;
    Res = Res * 128;
    NearSensors[4][2] = (char) Res;

    Diff = (double) Hall5ClrbRes - (double) Hall4ClrbRes;
    Res = Diff / (double) Hall4ClrbRes;
    Res = Res * 128;
    NearSensors[4][3] = (char) Res;



    NearSensors[5][0] = 4; //5_L
    NearSensors[5][1] = 1; //5_R
    Diff = (double) Hall4ClrbRes - (double) Hall5ClrbRes;
    Res = Diff / (double) Hall5ClrbRes;
    Res = Res * 128;
    NearSensors[5][2] = (char) Res;

    Diff = (double) Hall1ClrbRes - (double) Hall5ClrbRes;
    Res = Diff / (double) Hall5ClrbRes;
    Res = Res * 128;
    NearSensors[5][3] = (char) Res;



    NearSensors[6][0] = 2; //6_L
    NearSensors[6][1] = 4; //6_R
    Diff = (double) Hall2ClrbRes - (double) Hall6ClrbRes;
    Res = Diff / (double) Hall6ClrbRes;
    Res = Res * 128;
    NearSensors[6][2] = (char) Res;

    Diff = (double) Hall4ClrbRes - (double) Hall6ClrbRes;
    Res = Diff / (double) Hall6ClrbRes;
    Res = Res * 128;
    NearSensors[6][3] = (char) Res;


}

void Sound(void) {
    if (StartingMoveCnt)
        return;

    switch (SoundNum) {
        case 1:
            BuzzerOnTimeConst = 100; //1 Normal
            BuzzerOffTimeConst = 500;
            BuzzerOnTime = 150;
            BuzzerOffTime = 500;
            Sounds = 1;
        {
            BuzzerOnEvent = 10;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 2:
            BuzzerOnTimeConst = 500; //2 Long
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 500;
            BuzzerOffTime = 100;
            Sounds = 2;
        {
            BuzzerOnEvent = 11;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 3:
            BuzzerOnTimeConst = 40; //Revers
            BuzzerOffTimeConst = 250;
            BuzzerOnTime = 40;
            BuzzerOffTime = 250;
            Sounds = 254;
        {
            BuzzerOnEvent = 12;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 4:
            BuzzerOnTimeConst = 100; //   UBtLim1   <   UBT   <   UBtLim2    START   OFF
            BuzzerOffTimeConst = 1000;
            BuzzerOnTime = 100;
            BuzzerOffTime = 1000;
            Sounds = 1;
            BuzzerMacroOff
            break;
        case 5:
            BuzzerOnTimeConst = 100; //   UBT   <   UBtLim1
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 100;
            BuzzerOffTime = 100;
            Sounds = 1;
            BuzzerMacroOff
            break;
        case 6:
            BuzzerOnTimeConst = 50; //   Timer
            BuzzerOffTimeConst = 300;
            BuzzerOnTime = 50;
            BuzzerOffTime = 300;
            Sounds = 2;
        {
            BuzzerOnEvent = 13;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 7:
            BuzzerOnTimeConst = 100; //2 Normal
            BuzzerOffTimeConst = 500;
            BuzzerOnTime = 500;
            BuzzerOffTime = 500;
            Sounds = 2;
        {
            BuzzerOnEvent = 14;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 8:
            BuzzerOnTimeConst = 40; //Many Short
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 40;
            BuzzerOffTime = 100;
            Sounds = 254;
        {
            BuzzerOnEvent = 15;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 9:
            BuzzerOnTimeConst = 750; //   1 very long
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 750;
            BuzzerOffTime = 100;
            Sounds = 1;
        {
            BuzzerOnEvent = 16;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 10:
            BuzzerOnTimeConst = 50; //   5 short
            BuzzerOffTimeConst = 50;
            BuzzerOnTime = 50;
            BuzzerOffTime = 50;
            Sounds = 5;
        {
            BuzzerOnEvent = 17;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 11:
            BuzzerOnTimeConst = 50; //   2 short
            BuzzerOffTimeConst = 50;
            BuzzerOnTime = 50;
            BuzzerOffTime = 50;
            Sounds = 2;
        {
            BuzzerOnEvent = 18;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 12:
            BuzzerOnTimeConst = 100; //1 Short
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 50;
            BuzzerOffTime = 100;
            Sounds = 1;
        {
            BuzzerOnEvent = 19;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 13:
            BuzzerOnTimeConst = 40; //Many Short with long pause
            BuzzerOffTimeConst = 300;
            BuzzerOnTime = 40;
            BuzzerOffTime = 300;
            Sounds = 254;
        {
            BuzzerOnEvent = 20;
            BuzzerMacroOn//Buzzer=1;
        }
            break;

        case 14:
            BuzzerOnTimeConst = BzOnCntSeriaConstAlm; //Alarm 
            BuzzerOffTimeConst = BeepPauseConstAlm;
            BuzzerOnTime = BzOnCntSeriaConstAlm;
            BuzzerOffTime = BeepPauseConstAlm;
            Sounds = CntSingleBeepAlm;
        {
            BuzzerOnEvent = 21;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 15:
            BuzzerOnTimeConst = 100; //1 Normal
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 100;
            BuzzerOffTime = 100;
            Sounds = 1;
        {
            BuzzerOnEvent = 22;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 16:
            BuzzerOnTimeConst = 100; //2 Normal
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 100;
            BuzzerOffTime = 100;
            Sounds = 2;
        {
            BuzzerOnEvent = 23;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 17:
            BuzzerOnTimeConst = 100; //3 Normal
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 100;
            BuzzerOffTime = 100;
            Sounds = 3;
        {
            BuzzerOnEvent = 24;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 18:
            BuzzerOnTimeConst = 30; //1 Short LongPause
            BuzzerOffTimeConst = 30;
            BuzzerOnTime = 30;
            BuzzerOffTime = 30;
            Sounds = 10;
        {
            BuzzerOnEvent = 25;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 19:
            BuzzerOnTimeConst = 30; //5 short
            BuzzerOffTimeConst = 30;
            BuzzerOnTime = 30;
            BuzzerOffTime = 30;
            Sounds = 5;
        {
            BuzzerOnEvent = 26;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 20:
            BuzzerOnTimeConst = 30; //2 short
            BuzzerOffTimeConst = 30;
            BuzzerOnTime = 30;
            BuzzerOffTime = 30;
            Sounds = 2;
        {
            BuzzerOnEvent = 27;
            BuzzerMacroOn//Buzzer=1;
        }

            break;

        case 21:
            BuzzerOnTimeConst = 50; //   10 short
            BuzzerOffTimeConst = 50;
            BuzzerOnTime = 50;
            BuzzerOffTime = 50;
            Sounds = 10;
        {
            BuzzerOnEvent = 28;
            BuzzerMacroOn//Buzzer=1;
        }

            break;

        case 22:
            BuzzerOnTimeConst = 500; //3 Long
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 500;
            BuzzerOffTime = 100;
            Sounds = 3;
        {
            BuzzerOnEvent = 29;
            BuzzerMacroOn//Buzzer=1;
        }
            break;
        case 23:
            BuzzerOnTimeConst = 40; //Many Short with long pause
            BuzzerOffTimeConst = 450;
            BuzzerOnTime = 40;
            BuzzerOffTime = 300;
            Sounds = 254;
        {
            BuzzerOnEvent = 30;
            BuzzerMacroOn//Buzzer=1;
        }
            break;

        case 24:
            BuzzerOnTimeConst = 100; //1 Very long
            BuzzerOffTimeConst = 100;
            BuzzerOnTime = 500;
            BuzzerOffTime = 500;
            Sounds = 1;
        {
            BuzzerOnEvent = 31;
            BuzzerMacroOn//Buzzer=1;
        }
            break;



        default:
            break;
    }
    SoundNum = 0;

}

void InitPWM(void) {


    // Set PWM Period on Primary Time Base
    PTPER = MAX_PWM + DEADTIME + Khard;
    // Set Phase Shift
    PHASE1 = 0;
    PHASE2 = 0;
    PHASE3 = 0;


    // Set Duty Cycles
    /////////PDC1 = 0;
    /////////PDC2 = 0;
    /////////PDC3 = 0;

    // Set Dead Time Values
    DTR1 = DTR2 = DTR3 = DEADTIME;
    ALTDTR1 = ALTDTR2 = ALTDTR3 = DEADTIME;
    // Set PWM Mode to Complementary
    IOCON1 = IOCON2 = IOCON3 = 0x0000;
    // Set Primary Time Base, Edge-Aligned Mode and Independent Duty Cycles
    PWMCON1 = PWMCON2 = PWMCON3 = 0x0000;
    // Configure Faults
    FCLCON1 = FCLCON2 = FCLCON3 = 0x0003;
    // 1:1 Prescaler






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

    SEVTCMP = 200;
    //PTCONbits.SEIEN=1;

    PTCON2 = 0x0000;
    /* Enable PWM Module */
    PTCON = 0x8000;




}




void TestBreak(void) {
    if (StrongModeBreakOff && StrongModeMem && StrongMode&&!SIN_MIDDLE&&!Monocycle) {
        HvBreak = 0;
        BreakPressed = 0;
        return;
    }

    if (Break) {
        HvBreakCntOff = BreakCntConst;
        if (HvBreakCntOn) {
            HvBreakCntOn--;
        } else
            if (!BreakInvBtn)
            HvBreak = 1;
        else
            HvBreak = 0;
    } else {
        HvBreakCntOn = BreakCntConst;
        if (HvBreakCntOff) {
            HvBreakCntOff--;
        } else
            if (!BreakInvBtn)
            HvBreak = 0;
        else
            HvBreak = 1;

    }



    if (!BreakInvBtn) {
        if (Break) {
            BreakCntOff = BreakCntConst;
            if (BreakCntOn) {
                BreakCntOn--;
                if (!BreakCntOn) {
                    BreakPressed = 1;
                    BreakPressedMonocycle = 1;
                }
            }
        } else {
            BreakCntOn = BreakCntConst;
            if (BreakCntOff) {
                BreakCntOff--;
                if (!BreakCntOff) {
                    BreakPressed = 0;
                    BreakPressedUp = 1;
                    BreakPressedMonocycle = 0;
                }
            }


        }

    } else {
        if (!Break) {
            BreakCntOff = BreakCntConst;
            if (BreakCntOn) {
                BreakCntOn--;
                if (!BreakCntOn) {
                    BreakPressed = 1;
                    BreakPressedMonocycle = 1;
                }
            }
        } else {
            BreakCntOn = BreakCntConst;
            if (BreakCntOff) {
                BreakCntOff--;
                if (!BreakCntOff) {
                    BreakPressed = 0;
                    BreakPressedUp = 1;
                    BreakPressedMonocycle = 0;
                }
            }
        }

    }



}

void StateMachinePID(void) {
    if ((State == 1)&&(PID_On)) {
        State = 2;
    }

    if ((State == 2)&&(!PID_On)) {
        State = 1;
        if (!Wheeling && BtPID_Activated) {
            SoundNum = 10;
            BtPID_Activated = 0;
            if (StrongModePID)
                StrongMode = PrevStrongMode;


        }
        SpeedControlPID = 0;
    }

}


void SensorlessMotorStartInit(void) {
    StateSensorlessMotorStart = 1;
    if (ManualStart)
        StateSensorlessMotorStart = 7;

    //  CurrLimit=SensorLessCurrLimit;
    //  ChangeCVR();

    //  CurrUst=SensorlessCurrUst;
    Alignment = 1;
    SensorlessNotBEMF = 1;
    SensorlessStartNoHalls = 1;

    SenosrlessPWM1 = 0;
    SensorLessTimerConst = SensorLessTimerConstConst;
    if (!(StartingMoveCnt && CriticalError)) {
        if (DS) {
            DS = 0;
            RdSensors();
        }
    }

    CntBEMF = 0;
}

void SensorlessMotorStart(void) {
    if (!Sensorless)
        return;

    StrongMode = 0;

    //      if (ManualStart)
    //    CurrUst=SensorlessCurrUst;


    switch (StateSensorlessMotorStart) {
        case 1:
            if (SenosrlessPWM1 < SenosrlessPWM1_1Const)
                SenosrlessPWM1 = SenosrlessPWM1 + 10;
            else {
                StateSensorlessMotorStart = 2;
                SensorlessCntAlign = SensorlessCntAlignConst;
            }
            break;
        case 2:
            if (SensorlessCntAlign) {
                SensorlessCntAlign--;
                if (SensorlessCntAlign == 0) {
                    StateSensorlessMotorStart = 3;
                    SensorlessSpdChngCnt = SensorlessSpdChngCntConst;
                    Alignment = 0;
                }
            }
            break;
        case 3:
            if (SensorlessSpdChngCnt) {
                SensorlessSpdChngCnt--;
                if (!SensorlessSpdChngCnt) {
                    SensorlessSpdChngCnt = SensorlessSpdChngCntConst;
                    if (SensorLessTimerConst > SensorLessTimerConst2)
                        SensorLessTimerConst--;
                    else {
                        StateSensorlessMotorStart = 4;
                    }
                }
            } else
                SensorlessSpdChngCnt = SensorlessSpdChngCntConst;

            break;
        case 4:
            /*if (SenosrlessPWM1<SenosrlessPWM1_2Const)
            SenosrlessPWM1=SenosrlessPWM1+1;
            else
            {
                StateSensorlessMotorStart=5;
                SensorlessSpdChngCnt=SensorlessSpdChngCntConst;
            }*/
            StateSensorlessMotorStart = 5;
            break;
        case 5:
            if (SenosrlessPWM1 < SenosrlessPWM1_2Const)
                SenosrlessPWM1 = SenosrlessPWM1 + 1;
            if (SensorlessSpdChngCnt) {
                SensorlessSpdChngCnt--;
                if (!SensorlessSpdChngCnt) {
                    SensorlessSpdChngCnt = SensorlessSpdChngCntConst;
                    if (SensorLessTimerConst > SensorLessTimerConstMin)
                        SensorLessTimerConst--;
                    else {
                        SenosrlessPWM1 = 0;
                        StateSensorlessMotorStart = 6;
                        SensorlessSpdChngCnt = 250;
                    }
                }
            } else
                SensorlessSpdChngCnt = SensorlessSpdChngCntConst;
            PWM1 = SenosrlessPWM1_2Const;
            break;
        case 6:

            if (PWM1Prev < PWM1)
                PWM1 = PWM1Prev + 10;
            else
                StateSensorlessMotorStart = 7;
            break;
        case 7:
            if (Spd1Res < (SensorllessSpdThreshold + 1)) {
                SensorlessSpdChngCnt = 250;
                if (Spd1Res < 1) {
                    if (!ManualStart) {
                        SensorlessNotBEMF = 1;
                        SenosrlessPWM1 = 0;
                        StateSensorlessMotorStart = 0;
                    }
                }
                if (ManualStart)
                    DS = 1;
            } else {
                SensorlessSpdChngCnt--;
                if (!SensorlessSpdChngCnt) {

                    if (DS) {
                        DS = 0;
                        RdSensors();
                    }

                    StateSensorlessMotorStart = 8;
                    SoundNum = 11;
                    //                CurrLimit=CurrLimitWork;
                    //              CurrUst=CurrUstWork;
                    //            ChangeCVR();
                }
            }



            break;
        case 8:

            if (Spd1Res < (SensorllessSpdThreshold - 2)) {
                //          CurrLimit=SensorLessCurrLimit;
                //        ChangeCVR();
                //      CurrUst=SensorlessCurrUst;
                StateSensorlessMotorStart = 7;
            }

            break;
    }
}

void SensorlessMotorStopStarting(void) {
    SenosrlessPWM1 = 0;
    StateSensorlessMotorStart = 0;
    SensorlessNotBEMF = 1;
}

void OptionsToMassProfile(void) {
    unsigned int Prf = Profile - 1, Tmp;




    if ((But1Func == 4) || (But1Func == 5)) {
        ProfileMass[13 + 0] = But1Func;
        ProfileMass[13 + SIZE_OF_PROFILE] = But1Func;
        ProfileMass[13 + (SIZE_OF_PROFILE * 2)] = But1Func;
    }
    if ((But2Func == 4) || (But2Func == 5)) {
        ProfileMass[14 + 0] = But2Func;
        ProfileMass[14 + SIZE_OF_PROFILE] = But2Func;
        ProfileMass[14 + (SIZE_OF_PROFILE * 2)] = But2Func;
    }
    if ((But3Func == 4) || (But3Func == 5)) {
        ProfileMass[15 + 0] = But3Func;
        ProfileMass[15 + SIZE_OF_PROFILE] = But3Func;
        ProfileMass[15 + (SIZE_OF_PROFILE * 2)] = But3Func;
    }
    if ((But4Func == 4) || (But4Func == 5)) {
        ProfileMass[16 + 0] = But4Func;
        ProfileMass[16 + SIZE_OF_PROFILE] = But4Func;
        ProfileMass[16 + (SIZE_OF_PROFILE * 2)] = But4Func;
    }



    if (Prf == 0) {

        if (CW_CCW_AnyProfile) {
            ProfileMass[1 + Prf] = HallDelayMem1_F;
            ProfileMass[2 + Prf] = HallDelayMem1_B;
        }








        ProfileMass[3 + Prf] = 0;
        ProfileMass[4 + Prf] = 0;
        ProfileMass[38 + Prf] = 0;

        if (StrongModeMem)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 1;
        if (VectorMem)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 2;
        if (TrapezoidaRAM1)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 4;
        if (PWM32Bits)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x8;
        if (SpeedControl)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x10;
        if (AutoPID)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x20;
        if (MixedMode)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x40;
        if (StrongModePID)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x80;
        if (SlowStart)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x01;
        if (MixedModeSlowSpeedOff)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x02;
        if (MixedMode2)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x04;
        if (PWM_Mode)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x08;
        if (PWM_Mode_ZeroThrottle)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x10;
        if (SIN_MIDDLE)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x20;
        if (LightOn)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x40;
        if (CurrentControlOnly)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x80;




        ProfileMass[5 + Prf] = CurrUstWork;
        ProfileMass[6 + Prf] = CurrUstWork >> 8;
        ProfileMass[7 + Prf] = CurrLimitWork;
        ProfileMass[8 + Prf] = CurrLimitWork >> 8;
        ProfileMass[9 + Prf] = PhasePERMASS;
        ProfileMass[10 + Prf] = PhasePERMASS_SHFT;
        ProfileMass[11 + Prf] = MAX_PWM_MEM;
        ProfileMass[12 + Prf] = MaxSpd;
        ProfileMass[13 + Prf] = But1Func;
        ProfileMass[14 + Prf] = But2Func;
        ProfileMass[15 + Prf] = But3Func;
        ProfileMass[16 + Prf] = But4Func;
        ProfileMass[17 + Prf] = ThrottleTmpChngMem;
        ProfileMass[18 + Prf] = SlowStrtSpd;

        Tmp = (int) (Ki_PWM_Mode * 10000);
        ProfileMass[19 + Prf] = Tmp;
        ProfileMass[20 + Prf] = Tmp >> 8;

        Tmp = (int) (Kp_PWM_Mode * 100);
        ProfileMass[21 + Prf] = Tmp;
        ProfileMass[22 + Prf] = Tmp >> 8;

        Tmp = CurrPhaseLimitWork;
        ProfileMass[23 + Prf] = Tmp;
        ProfileMass[24 + Prf] = Tmp >> 8;




        if (CW_CCW_AnyProfile) {
            ProfileMass[25 + Prf] = HallDelay1MaxSPD_F;
            ProfileMass[26 + Prf] = HallDelay1MaxSPD_B;
            ProfileMass[27 + Prf] = HallDelayMaxSPD;
        }



        Tmp = (int) KpWheelingMem;
        ProfileMass[28 + Prf] = Tmp;
        ProfileMass[29 + Prf] = Tmp >> 8;

        Tmp = (int) (KiWheelingMem * 1000);
        ProfileMass[30 + Prf] = Tmp;
        ProfileMass[31 + Prf] = Tmp >> 8;

        Tmp = (int) (KdNoMan / 10);
        ProfileMass[32 + Prf] = Tmp;
        ProfileMass[33 + Prf] = Tmp >> 8;
        ProfileMass[34 + Prf] = CurrentMaxCurrentOnly;

        Tmp = (int) (Ki_PWM_ModeOff * 10000);
        ProfileMass[35 + Prf] = Tmp;
        ProfileMass[36 + Prf] = Tmp >> 8;

        ProfileMass[37 + Prf] = StrongModeSpdFilterOffMem;

        //---------------------------------------------------------        

        if (KeyLightStop)
            ProfileMass[38 + Prf] = ProfileMass[38 + Prf] | 0x01;
        if (KeyLightStopGabarit)
            ProfileMass[38 + Prf] = ProfileMass[38 + Prf] | 0x02;
        //---------------------------------------------------------        


        Tmp = CurrUstSpd0;
        ProfileMass[39 + Prf] = Tmp;
        ProfileMass[40 + Prf] = Tmp >> 8;

        Tmp = CurrPhaseLimitSpd0;
        ProfileMass[41 + Prf] = Tmp;
        ProfileMass[42 + Prf] = Tmp >> 8;

        ProfileMass[43 + Prf] = (char) (KpKpMustBe * 100);

        Tmp = (int) (KpKpSpd * 20);
        ProfileMass[44 + Prf] = Tmp;
        ProfileMass[45 + Prf] = Tmp >> 8;

        Tmp = BreakMonocycleSpd;
        ProfileMass[46 + Prf] = Tmp;
        ProfileMass[47 + Prf] = Tmp >> 8;

        KpKpDeadZoneMem = (unsigned char) (KpKpDeadZone * 10);
        ProfileMass[48 + Prf] = KpKpDeadZoneMem;

        Tmp = (int) (DeadZoneHandleBarSegwayMustBe * 10);
        ProfileMass[49 + Prf] = Tmp;
        ProfileMass[50 + Prf] = Tmp >> 8;

        Tmp = KRotMustBe;
        ProfileMass[51 + Prf] = Tmp;
        ProfileMass[52 + Prf] = Tmp >> 8;

        Tmp = (int) (KpRotMustBe * 1000);
        ProfileMass[53 + Prf] = Tmp;
        ProfileMass[54 + Prf] = Tmp >> 8;

        Tmp = (int) (KiRotMustBe * 10000);
        ProfileMass[55 + Prf] = Tmp;
        ProfileMass[56 + Prf] = Tmp >> 8;

    }

    if (Prf == 1) {
        Prf = Prf*SIZE_OF_PROFILE;
        if (CW_CCW_AnyProfile) {
            ProfileMass[1 + Prf] = HallDelayMem1_F;
            ProfileMass[2 + Prf] = HallDelayMem1_B;
        }


        ProfileMass[3 + Prf] = 0;
        ProfileMass[4 + Prf] = 0;
        ProfileMass[38 + Prf] = 0;

        if (StrongModeMem)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 1;
        if (VectorMem)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 2;
        if (TrapezoidaRAM1)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 4;
        if (PWM32Bits)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x8;
        if (SpeedControl)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x10;
        if (AutoPID)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x20;
        if (MixedMode)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x40;
        if (StrongModePID)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x80;
        if (SlowStart)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x01;
        if (MixedModeSlowSpeedOff)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x02;
        if (MixedMode2)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x04;
        if (PWM_Mode)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x08;
        if (PWM_Mode_ZeroThrottle)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x10;
        if (SIN_MIDDLE)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x20;
        if (LightOn)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x40;
        if (CurrentControlOnly)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x80;



        ProfileMass[5 + Prf] = CurrUstWork;
        ProfileMass[6 + Prf] = CurrUstWork >> 8;
        ProfileMass[7 + Prf] = CurrLimitWork;
        ProfileMass[8 + Prf] = CurrLimitWork >> 8;
        ProfileMass[9 + Prf] = PhasePERMASS;
        ProfileMass[10 + Prf] = PhasePERMASS_SHFT;
        ProfileMass[11 + Prf] = MAX_PWM_MEM;
        ProfileMass[12 + Prf] = MaxSpd;
        ProfileMass[13 + Prf] = But1Func;
        ProfileMass[14 + Prf] = But2Func;
        ProfileMass[15 + Prf] = But3Func;
        ProfileMass[16 + Prf] = But4Func;
        ProfileMass[17 + Prf] = ThrottleTmpChngMem;
        ProfileMass[18 + Prf] = SlowStrtSpd;
        Tmp = (int) (Ki_PWM_Mode * 10000);
        ProfileMass[19 + Prf] = Tmp;
        ProfileMass[20 + Prf] = Tmp >> 8;

        Tmp = (int) (Kp_PWM_Mode * 100);
        ProfileMass[21 + Prf] = Tmp;
        ProfileMass[22 + Prf] = Tmp >> 8;
        Tmp = CurrPhaseLimitWork;
        ProfileMass[23 + Prf] = Tmp;
        ProfileMass[24 + Prf] = Tmp >> 8;

        if (CW_CCW_AnyProfile) {
            ProfileMass[25 + Prf] = HallDelay1MaxSPD_F;
            ProfileMass[26 + Prf] = HallDelay1MaxSPD_B;
            ProfileMass[27 + Prf] = HallDelayMaxSPD;
        }
        Tmp = (int) KpWheelingMem;
        ProfileMass[28 + Prf] = Tmp;
        ProfileMass[29 + Prf] = Tmp >> 8;

        Tmp = (int) (KiWheelingMem * 1000);
        ProfileMass[30 + Prf] = Tmp;
        ProfileMass[31 + Prf] = Tmp >> 8;

        Tmp = (int) (KdNoMan / 10);
        ProfileMass[32 + Prf] = Tmp;
        ProfileMass[33 + Prf] = Tmp >> 8;
        ProfileMass[34 + Prf] = CurrentMaxCurrentOnly;

        Tmp = (int) (Ki_PWM_ModeOff * 10000);
        ProfileMass[35 + Prf] = Tmp;
        ProfileMass[36 + Prf] = Tmp >> 8;

        ProfileMass[37 + Prf] = StrongModeSpdFilterOffMem;
        //---------------------------------------------------------        

        if (KeyLightStop)
            ProfileMass[38 + Prf] = ProfileMass[38 + Prf] | 0x01;
        if (KeyLightStopGabarit)
            ProfileMass[38 + Prf] = ProfileMass[38 + Prf] | 0x02;

        //---------------------------------------------------------        
        Tmp = CurrUstSpd0;
        ProfileMass[39 + Prf] = Tmp;
        ProfileMass[40 + Prf] = Tmp >> 8;

        Tmp = CurrPhaseLimitSpd0;
        ProfileMass[41 + Prf] = Tmp;
        ProfileMass[42 + Prf] = Tmp >> 8;

        ProfileMass[43 + Prf] = (char) (KpKpMustBe * 100);

        Tmp = (int) (KpKpSpd * 20);
        ProfileMass[44 + Prf] = Tmp;
        ProfileMass[45 + Prf] = Tmp >> 8;

        Tmp = BreakMonocycleSpd;
        ProfileMass[46 + Prf] = Tmp;
        ProfileMass[47 + Prf] = Tmp >> 8;

        KpKpDeadZoneMem = (unsigned char) (KpKpDeadZone * 10);
        ProfileMass[48 + Prf] = KpKpDeadZoneMem;

        Tmp = (int) (DeadZoneHandleBarSegwayMustBe * 10);
        ProfileMass[49 + Prf] = Tmp;
        ProfileMass[50 + Prf] = Tmp >> 8;

        Tmp = KRotMustBe;
        ProfileMass[51 + Prf] = Tmp;
        ProfileMass[52 + Prf] = Tmp >> 8;

        Tmp = (int) (KpRotMustBe * 1000);
        ProfileMass[53 + Prf] = Tmp;
        ProfileMass[54 + Prf] = Tmp >> 8;

        Tmp = (int) (KiRotMustBe * 10000);
        ProfileMass[55 + Prf] = Tmp;
        ProfileMass[56 + Prf] = Tmp >> 8;

    }
    if (Prf == 2) {
        Prf = Prf*SIZE_OF_PROFILE;

        if (CW_CCW_AnyProfile) {
            ProfileMass[1 + Prf] = HallDelayMem1_F;
            ProfileMass[2 + Prf] = HallDelayMem1_B;
        }
        ProfileMass[3 + Prf] = 0;
        ProfileMass[4 + Prf] = 0;
        ProfileMass[38 + Prf] = 0;

        if (StrongModeMem)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 1;
        if (VectorMem)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 2;
        if (TrapezoidaRAM1)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 4;
        if (PWM32Bits)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x8;
        if (SpeedControl)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x10;
        if (AutoPID)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x20;
        if (MixedMode)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x40;
        if (StrongModePID)
            ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x80;
        if (SlowStart)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x01;
        if (MixedModeSlowSpeedOff)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x02;
        if (MixedMode2)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x04;
        if (PWM_Mode)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x08;
        if (PWM_Mode_ZeroThrottle)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x10;
        if (SIN_MIDDLE)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x20;
        if (LightOn)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x40;
        if (CurrentControlOnly)
            ProfileMass[4 + Prf] = ProfileMass[4 + Prf] | 0x80;


        ProfileMass[5 + Prf] = CurrUstWork;
        ProfileMass[6 + Prf] = CurrUstWork >> 8;
        ProfileMass[7 + Prf] = CurrLimitWork;
        ProfileMass[8 + Prf] = CurrLimitWork >> 8;
        ProfileMass[9 + Prf] = PhasePERMASS;
        ProfileMass[10 + Prf] = PhasePERMASS_SHFT;
        ProfileMass[11 + Prf] = MAX_PWM_MEM;
        ProfileMass[12 + Prf] = MaxSpd;
        ProfileMass[13 + Prf] = But1Func;
        ProfileMass[14 + Prf] = But2Func;
        ProfileMass[15 + Prf] = But3Func;
        ProfileMass[16 + Prf] = But4Func;
        ProfileMass[17 + Prf] = ThrottleTmpChngMem;
        ProfileMass[18 + Prf] = SlowStrtSpd;
        Tmp = (int) (Ki_PWM_Mode * 10000);
        ProfileMass[19 + Prf] = Tmp;
        ProfileMass[20 + Prf] = Tmp >> 8;

        Tmp = (int) (Kp_PWM_Mode * 100);
        ProfileMass[21 + Prf] = Tmp;
        ProfileMass[22 + Prf] = Tmp >> 8;
        Tmp = CurrPhaseLimitWork;
        ProfileMass[23 + Prf] = Tmp;
        ProfileMass[24 + Prf] = Tmp >> 8;

        if (CW_CCW_AnyProfile) {
            ProfileMass[25 + Prf] = HallDelay1MaxSPD_F;
            ProfileMass[26 + Prf] = HallDelay1MaxSPD_B;
            ProfileMass[27 + Prf] = HallDelayMaxSPD;
        }


        Tmp = (int) KpWheelingMem;
        ProfileMass[28 + Prf] = Tmp;
        ProfileMass[29 + Prf] = Tmp >> 8;


        Tmp = (int) (KiWheelingMem * 1000);
        ProfileMass[30 + Prf] = Tmp;
        ProfileMass[31 + Prf] = Tmp >> 8;

        Tmp = (int) (KdNoMan / 10);
        ProfileMass[32 + Prf] = Tmp;
        ProfileMass[33 + Prf] = Tmp >> 8;
        ProfileMass[34 + Prf] = CurrentMaxCurrentOnly;

        Tmp = (int) (Ki_PWM_ModeOff * 10000);
        ProfileMass[35 + Prf] = Tmp;
        ProfileMass[36 + Prf] = Tmp >> 8;

        ProfileMass[37 + Prf] = StrongModeSpdFilterOffMem;

        //---------------------------------------------------------        

        if (KeyLightStop)
            ProfileMass[38 + Prf] = ProfileMass[38 + Prf] | 0x01;
        if (KeyLightStopGabarit)
            ProfileMass[38 + Prf] = ProfileMass[38 + Prf] | 0x02;

        //---------------------------------------------------------        
        Tmp = CurrUstSpd0;
        ProfileMass[39 + Prf] = Tmp;
        ProfileMass[40 + Prf] = Tmp >> 8;

        Tmp = CurrPhaseLimitSpd0;
        ProfileMass[41 + Prf] = Tmp;
        ProfileMass[42 + Prf] = Tmp >> 8;

        ProfileMass[43 + Prf] = (char) (KpKpMustBe * 100);

        Tmp = (int) (KpKpSpd * 20);
        ProfileMass[44 + Prf] = Tmp;
        ProfileMass[45 + Prf] = Tmp >> 8;

        Tmp = BreakMonocycleSpd;
        ProfileMass[46 + Prf] = Tmp;
        ProfileMass[47 + Prf] = Tmp >> 8;

        KpKpDeadZoneMem = (unsigned char) (KpKpDeadZone * 10);
        ProfileMass[48 + Prf] = KpKpDeadZoneMem;

        Tmp = (int) (DeadZoneHandleBarSegwayMustBe * 10);
        ProfileMass[49 + Prf] = Tmp;
        ProfileMass[50 + Prf] = Tmp >> 8;

        Tmp = KRotMustBe;
        ProfileMass[51 + Prf] = Tmp;
        ProfileMass[52 + Prf] = Tmp >> 8;

        Tmp = (int) (KpRotMustBe * 1000);
        ProfileMass[53 + Prf] = Tmp;
        ProfileMass[54 + Prf] = Tmp >> 8;

        Tmp = (int) (KiRotMustBe * 10000);
        ProfileMass[55 + Prf] = Tmp;
        ProfileMass[56 + Prf] = Tmp >> 8;
    }

}

void MassToOptionsProfile(void) {
    unsigned int Prf = Profile - 1;
    unsigned int Tm;
    unsigned char SpdCntrTmp = SpeedControl;




    if (Prf == 0) {
        if (CW_CCW_AnyProfile) {
            HallDelayMem1_F = ProfileMass[1 + Prf];
            HallDelayMem1_B = ProfileMass[2 + Prf];
        }










        //3  AND  4  STATUS
        StrongModeMem = 0;
        if (ProfileMass[3 + Prf]&0x01)
            StrongModeMem = 1;

        if (ProfileMass[3 + Prf]&0x02)
            VectorMem = 1;
        else
            VectorMem = 0;
        if (ProfileMass[3 + Prf]&0x04)
            TrapezoidaRAM1 = 1;
        else
            TrapezoidaRAM1 = 0;
        if (ProfileMass[3 + Prf]&0x08)
            PWM32Bits = 1;
        else
            PWM32Bits = 0;
        if (ProfileMass[3 + Prf]&0x10) {
            if (!Sensorless) {
                SpeedControl = 1;
                EPID_Res_Tek = 0;
            }

        } else
            SpeedControl = 0;
        if (ProfileMass[3 + Prf]&0x20)
            AutoPID = 1;
        else
            AutoPID = 0;

        if (ProfileMass[3 + Prf]&0x40)
            MixedMode = 1;
        else
            MixedMode = 0;
        if (ProfileMass[3 + Prf]&0x80)
            StrongModePID = 1;
        else
            StrongModePID = 0;
        if (ProfileMass[4 + Prf]&0x01)
            SlowStart = 1;
        else
            SlowStart = 0;
        if (ProfileMass[4 + Prf]&0x02)
            MixedModeSlowSpeedOff = 1;
        else
            MixedModeSlowSpeedOff = 0;
        if (ProfileMass[4 + Prf]&0x04)
            MixedMode2 = 1;
        else
            MixedMode2 = 0;
        if (ProfileMass[4 + Prf]&0x08)
            PWM_Mode = 1;
        else
            PWM_Mode = 0;
        if (ProfileMass[4 + Prf]&0x10)
            PWM_Mode_ZeroThrottle = 1;
        else
            PWM_Mode_ZeroThrottle = 0;
        if (ProfileMass[4 + Prf]&0x20)
            SIN_MIDDLE = 1;
        else
            SIN_MIDDLE = 0;
        if (ProfileMass[4 + Prf]&0x40)
            LightOn = 1;
        else
            LightOn = 0;
        if (ProfileMass[4 + Prf]&0x80)
            CurrentControlOnly = 1;
        else
            CurrentControlOnly = 0;




        Tm = ProfileMass[6 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[5 + Prf];
        CurrUstWork = Tm;

        Tm = ProfileMass[8 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[7 + Prf];
        CurrLimitWork = Tm;

        PhasePERMASS = ProfileMass[9 + Prf];
        PhasePERMASS_SHFT = ProfileMass[10 + Prf];

        MAX_PWM_MEM = ProfileMass[11 + Prf];
        MaxSpd = ProfileMass[12 + Prf];

        But1Func = ProfileMass[13 + Prf];
        But2Func = ProfileMass[14 + Prf];
        But3Func = ProfileMass[15 + Prf];
        But4Func = ProfileMass[16 + Prf];
        ThrottleTmpChngMem = ProfileMass[17 + Prf];
        SlowStrtSpd = ProfileMass[18 + Prf];

        Tm = ProfileMass[20 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[19 + Prf];
        Ki_PWM_Mode = Tm;
        Ki_PWM_Mode = Ki_PWM_Mode / 10000;


        Tm = ProfileMass[22 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[21 + Prf];
        Kp_PWM_Mode = Tm;
        Kp_PWM_Mode = Kp_PWM_Mode / 100;

        Tm = ProfileMass[24 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[23 + Prf];
        CurrPhaseLimitWork = Tm;

        if (CW_CCW_AnyProfile) {
            HallDelay1MaxSPD_F = ProfileMass[25 + Prf];
            HallDelay1MaxSPD_B = ProfileMass[26 + Prf];
            HallDelayMaxSPD = ProfileMass[27 + Prf];
        }

        Tm = ProfileMass[29 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[28 + Prf];
        KpWheelingMem = Tm;


        Tm = ProfileMass[31 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[30 + Prf];
        KiWheelingMem = (float) ((int) Tm);


        Tm = ProfileMass[33 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[32 + Prf];
        KdNoMan = (float) ((int) Tm);
        CurrentMaxCurrentOnly = ProfileMass[34 + Prf];
        CurrentMaxCurrentOnlyWork = ((float) CurrentMaxCurrentOnly * 1000/**Crr1Corr*/) / CurrPerDigit;


        Tm = ProfileMass[36 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[35 + Prf];
        Ki_PWM_ModeOff = Tm;
        Ki_PWM_ModeOff = Ki_PWM_ModeOff / 10000;

        StrongModeSpdFilterOffMem = ProfileMass[37 + Prf];
        StrongModeSpdFilterOff = ((float) StrongModeSpdFilterOffMem) / ImpToKmH1_t;


        //---------------------------------------------------------        
        if (ProfileMass[38 + Prf]&0x01)
            KeyLightStop = 1;
        else
            KeyLightStop = 0;
        if (ProfileMass[38 + Prf]&0x02)
            KeyLightStopGabarit = 1;
        else
            KeyLightStopGabarit = 0;
        //---------------------------------------------------------        


        Tm = ProfileMass[40 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[39 + Prf];
        CurrUstSpd0 = Tm;

        Tm = ProfileMass[42 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[41 + Prf];
        CurrPhaseLimitSpd0 = Tm;


        KpKpMustBe = (float) ((char) ProfileMass[43 + Prf]);
        KpKpMustBe = KpKpMustBe / (float) 100;

        Tm = ProfileMass[45 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[44 + Prf];
        KpKpSpd = (float) Tm;
        KpKpSpd = KpKpSpd / 20;


        Tm = ProfileMass[47 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[46 + Prf];
        BreakMonocycleSpd = Tm;

        KpKpDeadZoneMem = ProfileMass[48 + Prf];
        KpKpDeadZone = ((float) (KpKpDeadZoneMem)) / 10;

        Tm = ProfileMass[50 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[49 + Prf];
        DeadZoneHandleBarSegwayMustBe = (float) Tm;
        DeadZoneHandleBarSegwayMustBe = DeadZoneHandleBarSegwayMustBe / 10;

        Tm = ProfileMass[52 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[51 + Prf];
        KRotMustBe = Tm;

        Tm = ProfileMass[54 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[53 + Prf];
        KpRotMustBe = (float) Tm;
        KpRotMustBe = KpRotMustBe / 1000;

        Tm = ProfileMass[56 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[55 + Prf];
        KiRotMustBe = (float) Tm;
        KiRotMustBe = KiRotMustBe / 10000;





        if ((But1Func == 4) || (But1Func == 5)) {
            if ((ProfileMass[13 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[13 + (SIZE_OF_PROFILE * 2)] != 5))
                But1Func = 0;
            if ((ProfileMass[13 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[13 + SIZE_OF_PROFILE] != 5))
                But1Func = 0;
        }
        if ((But2Func == 4) || (But2Func == 5)) {
            if ((ProfileMass[14 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[14 + (SIZE_OF_PROFILE * 2)] != 5))
                But2Func = 0;
            if ((ProfileMass[14 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[14 + SIZE_OF_PROFILE] != 5))
                But2Func = 0;
        }
        if ((But3Func == 4) || (But3Func == 5)) {
            if ((ProfileMass[15 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[15 + (SIZE_OF_PROFILE * 2)] != 5))
                But3Func = 0;
            if ((ProfileMass[15 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[15 + SIZE_OF_PROFILE] != 5))
                But3Func = 0;
        }
        if ((But4Func == 4) || (But4Func == 5)) {
            if ((ProfileMass[16 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[16 + (SIZE_OF_PROFILE * 2)] != 5))
                But4Func = 0;
            if ((ProfileMass[16 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[16 + SIZE_OF_PROFILE] != 5))
                But4Func = 0;
        }


    }

    if (Prf == 1) {
        Prf = Prf*SIZE_OF_PROFILE;

        if (CW_CCW_AnyProfile) {
            HallDelayMem1_F = ProfileMass[1 + Prf];
            HallDelayMem1_B = ProfileMass[2 + Prf];
        }



        //3  AND  4  STATUS
        StrongModeMem = 0;
        if (ProfileMass[3 + Prf]&0x01)
            StrongModeMem = 1;
        if (ProfileMass[3 + Prf]&0x02)
            VectorMem = 1;
        else
            VectorMem = 0;
        if (ProfileMass[3 + Prf]&0x04)
            TrapezoidaRAM1 = 1;
        else
            TrapezoidaRAM1 = 0;
        if (ProfileMass[3 + Prf]&0x08)
            PWM32Bits = 1;
        else
            PWM32Bits = 0;
        if (ProfileMass[3 + Prf]&0x10) {
            if (!Sensorless) {
                SpeedControl = 1;
                EPID_Res_Tek = 0;
            }
        } else
            SpeedControl = 0;
        if (ProfileMass[3 + Prf]&0x20)
            AutoPID = 1;
        else
            AutoPID = 0;

        if (ProfileMass[3 + Prf]&0x40)
            MixedMode = 1;
        else
            MixedMode = 0;
        if (ProfileMass[3 + Prf]&0x80)
            StrongModePID = 1;
        else
            StrongModePID = 0;
        if (ProfileMass[4 + Prf]&0x01)
            SlowStart = 1;
        else
            SlowStart = 0;
        if (ProfileMass[4 + Prf]&0x02)
            MixedModeSlowSpeedOff = 1;
        else
            MixedModeSlowSpeedOff = 0;
        if (ProfileMass[4 + Prf]&0x04)
            MixedMode2 = 1;
        else
            MixedMode2 = 0;
        if (ProfileMass[4 + Prf]&0x08)
            PWM_Mode = 1;
        else
            PWM_Mode = 0;
        if (ProfileMass[4 + Prf]&0x10)
            PWM_Mode_ZeroThrottle = 1;
        else
            PWM_Mode_ZeroThrottle = 0;
        if (ProfileMass[4 + Prf]&0x20)
            SIN_MIDDLE = 1;
        else
            SIN_MIDDLE = 0;
        if (ProfileMass[4 + Prf]&0x40)
            LightOn = 1;
        else
            LightOn = 0;
        if (ProfileMass[4 + Prf]&0x80)
            CurrentControlOnly = 1;
        else
            CurrentControlOnly = 0;




        Tm = ProfileMass[6 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[5 + Prf];
        CurrUstWork = Tm;

        Tm = ProfileMass[8 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[7 + Prf];
        CurrLimitWork = Tm;

        PhasePERMASS = ProfileMass[9 + Prf];
        PhasePERMASS_SHFT = ProfileMass[10 + Prf];

        MAX_PWM_MEM = ProfileMass[11 + Prf];
        MaxSpd = ProfileMass[12 + Prf];

        But1Func = ProfileMass[13 + Prf];
        But2Func = ProfileMass[14 + Prf];
        But3Func = ProfileMass[15 + Prf];
        But4Func = ProfileMass[16 + Prf];
        ThrottleTmpChngMem = ProfileMass[17 + Prf];
        SlowStrtSpd = ProfileMass[18 + Prf];

        Tm = ProfileMass[20 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[19 + Prf];
        Ki_PWM_Mode = Tm;
        Ki_PWM_Mode = Ki_PWM_Mode / 10000;

        Tm = ProfileMass[22 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[21 + Prf];
        Kp_PWM_Mode = Tm;
        Kp_PWM_Mode = Kp_PWM_Mode / 100;

        Tm = ProfileMass[24 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[23 + Prf];
        CurrPhaseLimitWork = Tm;

        if (CW_CCW_AnyProfile) {
            HallDelay1MaxSPD_F = ProfileMass[25 + Prf];
            HallDelay1MaxSPD_B = ProfileMass[26 + Prf];
            HallDelayMaxSPD = ProfileMass[27 + Prf];
        }

        Tm = ProfileMass[29 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[28 + Prf];
        KpWheelingMem = Tm;

        Tm = ProfileMass[31 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[30 + Prf];
        KiWheelingMem = (float) ((int) Tm);

        Tm = ProfileMass[33 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[32 + Prf];
        KdNoMan = (float) ((int) Tm);
        CurrentMaxCurrentOnly = ProfileMass[34 + Prf];
        CurrentMaxCurrentOnlyWork = ((float) CurrentMaxCurrentOnly * 1000/**Crr1Corr*/) / CurrPerDigit;

        Tm = ProfileMass[36 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[35 + Prf];
        Ki_PWM_ModeOff = Tm;
        Ki_PWM_ModeOff = Ki_PWM_ModeOff / 10000;

        StrongModeSpdFilterOffMem = ProfileMass[37 + Prf];
        StrongModeSpdFilterOff = ((float) StrongModeSpdFilterOffMem) / ImpToKmH1_t;

        //---------------------------------------------------------        
        if (ProfileMass[38 + Prf]&0x01)
            KeyLightStop = 1;
        else
            KeyLightStop = 0;
        if (ProfileMass[38 + Prf]&0x02)
            KeyLightStopGabarit = 1;
        else
            KeyLightStopGabarit = 0;
        //---------------------------------------------------------        


        Tm = ProfileMass[40 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[39 + Prf];
        CurrUstSpd0 = Tm;

        Tm = ProfileMass[42 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[41 + Prf];
        CurrPhaseLimitSpd0 = Tm;

        KpKpMustBe = (float) ((char) ProfileMass[43 + Prf]);
        KpKpMustBe = KpKpMustBe / (float) 100;

        Tm = ProfileMass[45 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[44 + Prf];
        KpKpSpd = (float) Tm;
        KpKpSpd = KpKpSpd / 20;


        Tm = ProfileMass[47 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[46 + Prf];
        BreakMonocycleSpd = Tm;


        KpKpDeadZoneMem = ProfileMass[48 + Prf];
        KpKpDeadZone = ((float) (KpKpDeadZoneMem)) / 10;

        Tm = ProfileMass[50 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[49 + Prf];
        DeadZoneHandleBarSegwayMustBe = (float) Tm;
        DeadZoneHandleBarSegwayMustBe = DeadZoneHandleBarSegwayMustBe / 10;

        Tm = ProfileMass[52 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[51 + Prf];
        KRotMustBe = Tm;

        Tm = ProfileMass[54 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[53 + Prf];
        KpRotMustBe = (float) Tm;
        KpRotMustBe = KpRotMustBe / 1000;

        Tm = ProfileMass[56 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[55 + Prf];
        KiRotMustBe = (float) Tm;
        KiRotMustBe = KiRotMustBe / 10000;





        if ((But1Func == 4) || (But1Func == 5)) {
            if ((ProfileMass[13 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[13 + (SIZE_OF_PROFILE * 2)] != 5))
                But1Func = 0;
            if ((ProfileMass[13] != 4)&&(ProfileMass[13] != 5))
                But1Func = 0;
        }
        if ((But2Func == 4) || (But2Func == 5)) {
            if ((ProfileMass[14 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[14 + (SIZE_OF_PROFILE * 2)] != 5))
                But2Func = 0;
            if ((ProfileMass[14] != 4)&&(ProfileMass[14] != 5))
                But2Func = 0;
        }
        if ((But3Func == 4) || (But3Func == 5)) {
            if ((ProfileMass[15 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[15 + (SIZE_OF_PROFILE * 2)] != 5))
                But3Func = 0;
            if ((ProfileMass[15] != 4)&&(ProfileMass[15] != 5))
                But3Func = 0;
        }
        if ((But4Func == 4) || (But4Func == 5)) {
            if ((ProfileMass[16 + (SIZE_OF_PROFILE * 2)] != 4)&&(ProfileMass[16 + (SIZE_OF_PROFILE * 2)] != 5))
                But4Func = 0;
            if ((ProfileMass[16] != 4)&&(ProfileMass[16] != 5))
                But4Func = 0;
        }



    }

    if (Prf == 2) {

        Prf = Prf*SIZE_OF_PROFILE;

        if (CW_CCW_AnyProfile) {
            HallDelayMem1_F = ProfileMass[1 + Prf];
            HallDelayMem1_B = ProfileMass[2 + Prf];
        }


        //3  AND  4  STATUS
        StrongModeMem = 0;
        if (ProfileMass[3 + Prf]&0x01)
            StrongModeMem = 1;
        if (ProfileMass[3 + Prf]&0x02)
            VectorMem = 1;
        else
            VectorMem = 0;
        if (ProfileMass[3 + Prf]&0x04)
            TrapezoidaRAM1 = 1;
        else
            TrapezoidaRAM1 = 0;
        if (ProfileMass[3 + Prf]&0x08)
            PWM32Bits = 1;
        else
            PWM32Bits = 0;
        if (ProfileMass[3 + Prf]&0x10) {
            if (!Sensorless) {
                SpeedControl = 1;
                EPID_Res_Tek = 0;
            }
        } else
            SpeedControl = 0;
        if (ProfileMass[3 + Prf]&0x20)
            AutoPID = 1;
        else
            AutoPID = 0;

        if (ProfileMass[3 + Prf]&0x40)
            MixedMode = 1;
        else
            MixedMode = 0;
        if (ProfileMass[3 + Prf]&0x80)
            StrongModePID = 1;
        else
            StrongModePID = 0;
        if (ProfileMass[4 + Prf]&0x01)
            SlowStart = 1;
        else
            SlowStart = 0;
        if (ProfileMass[4 + Prf]&0x02)
            MixedModeSlowSpeedOff = 1;
        else
            MixedModeSlowSpeedOff = 0;
        if (ProfileMass[4 + Prf]&0x04)
            MixedMode2 = 1;
        else
            MixedMode2 = 0;
        if (ProfileMass[4 + Prf]&0x08)
            PWM_Mode = 1;
        else
            PWM_Mode = 0;
        if (ProfileMass[4 + Prf]&0x10)
            PWM_Mode_ZeroThrottle = 1;
        else
            PWM_Mode_ZeroThrottle = 0;
        if (ProfileMass[4 + Prf]&0x20)
            SIN_MIDDLE = 1;
        else
            SIN_MIDDLE = 0;
        if (ProfileMass[4 + Prf]&0x40)
            LightOn = 1;
        else
            LightOn = 0;
        if (ProfileMass[4 + Prf]&0x80)
            CurrentControlOnly = 1;
        else
            CurrentControlOnly = 0;




        Tm = ProfileMass[6 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[5 + Prf];
        CurrUstWork = Tm;

        Tm = ProfileMass[8 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[7 + Prf];
        CurrLimitWork = Tm;

        PhasePERMASS = ProfileMass[9 + Prf];
        PhasePERMASS_SHFT = ProfileMass[10 + Prf];

        MAX_PWM_MEM = ProfileMass[11 + Prf];
        MaxSpd = ProfileMass[12 + Prf];

        But1Func = ProfileMass[13 + Prf];
        But2Func = ProfileMass[14 + Prf];
        But3Func = ProfileMass[15 + Prf];
        But4Func = ProfileMass[16 + Prf];
        ThrottleTmpChngMem = ProfileMass[17 + Prf];
        SlowStrtSpd = ProfileMass[18 + Prf];

        Tm = ProfileMass[20 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[19 + Prf];
        Ki_PWM_Mode = Tm;
        Ki_PWM_Mode = Ki_PWM_Mode / 10000;

        Tm = ProfileMass[22 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[21 + Prf];
        Kp_PWM_Mode = Tm;
        Kp_PWM_Mode = Kp_PWM_Mode / 100;

        Tm = ProfileMass[24 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[23 + Prf];
        CurrPhaseLimitWork = Tm;

        if (CW_CCW_AnyProfile) {
            HallDelay1MaxSPD_F = ProfileMass[25 + Prf];
            HallDelay1MaxSPD_B = ProfileMass[26 + Prf];
            HallDelayMaxSPD = ProfileMass[27 + Prf];
        }

        Tm = ProfileMass[29 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[28 + Prf];
        KpWheelingMem = Tm;

        Tm = ProfileMass[31 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[30 + Prf];
        KiWheelingMem = (float) ((int) Tm);

        Tm = ProfileMass[33 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[32 + Prf];
        KdNoMan = (float) ((int) Tm);
        CurrentMaxCurrentOnly = ProfileMass[34 + Prf];
        CurrentMaxCurrentOnlyWork = ((float) CurrentMaxCurrentOnly * 1000/**Crr1Corr*/) / CurrPerDigit;

        Tm = ProfileMass[36 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[35 + Prf];
        Ki_PWM_ModeOff = Tm;
        Ki_PWM_ModeOff = Ki_PWM_ModeOff / 10000;

        StrongModeSpdFilterOffMem = ProfileMass[37 + Prf];
        StrongModeSpdFilterOff = ((float) StrongModeSpdFilterOffMem) / ImpToKmH1_t;

        //---------------------------------------------------------        
        if (ProfileMass[38 + Prf]&0x01)
            KeyLightStop = 1;
        else
            KeyLightStop = 0;
        if (ProfileMass[38 + Prf]&0x02)
            KeyLightStopGabarit = 1;
        else
            KeyLightStopGabarit = 0;
        //---------------------------------------------------------        



        Tm = ProfileMass[40 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[39 + Prf];
        CurrUstSpd0 = Tm;

        Tm = ProfileMass[42 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[41 + Prf];
        CurrPhaseLimitSpd0 = Tm;

        KpKpMustBe = (float) ((char) ProfileMass[43 + Prf]);
        KpKpMustBe = KpKpMustBe / (float) 100;

        Tm = ProfileMass[45 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[44 + Prf];
        KpKpSpd = (float) Tm;
        KpKpSpd = KpKpSpd / 20;


        Tm = ProfileMass[47 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[46 + Prf];
        BreakMonocycleSpd = Tm;

        KpKpDeadZoneMem = ProfileMass[48 + Prf];
        KpKpDeadZone = ((float) (KpKpDeadZoneMem)) / 10;

        Tm = ProfileMass[50 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[49 + Prf];
        DeadZoneHandleBarSegwayMustBe = (float) Tm;
        DeadZoneHandleBarSegwayMustBe = DeadZoneHandleBarSegwayMustBe / 10;

        Tm = ProfileMass[52 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[51 + Prf];
        KRotMustBe = Tm;

        Tm = ProfileMass[54 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[53 + Prf];
        KpRotMustBe = (float) Tm;
        KpRotMustBe = KpRotMustBe / 1000;

        Tm = ProfileMass[56 + Prf];
        Tm = Tm << 8;
        Tm = Tm + ProfileMass[55 + Prf];
        KiRotMustBe = (float) Tm;
        KiRotMustBe = KiRotMustBe / 10000;




        if ((But1Func == 4) || (But1Func == 5)) {
            if ((ProfileMass[13] != 4)&&(ProfileMass[13] != 5))
                But1Func = 0;
            if ((ProfileMass[13 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[13 + SIZE_OF_PROFILE] != 5))
                But1Func = 0;
        }
        if ((But2Func == 4) || (But2Func == 5)) {
            if ((ProfileMass[14] != 4)&&(ProfileMass[14] != 5))
                But2Func = 0;
            if ((ProfileMass[14 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[14 + SIZE_OF_PROFILE] != 5))
                But2Func = 0;
        }
        if ((But3Func == 4) || (But3Func == 5)) {
            if ((ProfileMass[15] != 4)&&(ProfileMass[15] != 5))
                But3Func = 0;
            if ((ProfileMass[15 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[15 + SIZE_OF_PROFILE] != 5))
                But3Func = 0;
        }
        if ((But4Func == 4) || (But4Func == 5)) {
            if ((ProfileMass[16] != 4)&&(ProfileMass[16] != 5))
                But4Func = 0;
            if ((ProfileMass[16 + SIZE_OF_PROFILE] != 4)&&(ProfileMass[16 + SIZE_OF_PROFILE] != 5))
                But4Func = 0;
        }




    }

    KpMustBe = KpWheelingMem;
    KiWheelingMem = KiWheelingMem / 1000;
    KiMustBe = KiWheelingMem;
    SetKi_UP();
    ESumm = 0;


    KdNoMan = KdNoMan * 10;

    if (KiMustBe == 65535) {
        KiWheelingMem = 0;
        KiMustBe = 0;
        SetKi_UP();
    }

    if (KpMustBe == 65535) {
        KpWheelingMem = 0;
        KpMustBe = 0;
    }


    if (StrongModeMem) {
        PrevStrongMode = 1;
        StrongMode = 1;
    } else {
        StrongMode = 0;
        PrevStrongMode = 0;
    }



    if ((VectorMem)&&(!Sensorless))
        Vector = 1;
    else
        Vector = 0;

    //    if (!Sensorless)
    CurrUst = CurrUstWork;
    //  else
    //        CurrUst=SensorlessCurrUst;


    if ((!Sensorless)&&(!CurrDecrease))
        CurrLimit = CurrLimitWork;
    else
        if (Sensorless)
        CurrLimit = SensorLessCurrLimit;
    ChangeCVR();

    MAX_PWM_MustBe = MAX_PWM_MEM;
    if (MAX_PWM_MEM > 100)
        MAX_PWM_MEM = 100;

    MaxSpdCoeff = (int) ((((float) MAX_PWM) * ImpToKmH1_t) / ((float) MaxSpd / ImpToKmH1_t));
    MAX_PWM_MustBe = MAX_PWM_MEM;
    /*                                       if (1)//(PWM32Bits)
                                           {
                                            MAX_PWM_CONST=MAX_PWM_CONST_MONOCYCLE;
                                        
                                           }
                                            else
                                            {
                                            MAX_PWM_CONST=MAX_PWM_CONST_EBIKE;
                                        
                                            }*/

#if defined ISOLATED
    Sensorless = 0;
#endif        

    if (Sensorless)
        SensorlessInit();
    else {
        if (Vector)
            VectorInit();
        else
            TrapeziumInit();
    }

    if (SpdCntrTmp != SpeedControl) {
        if (!SpeedControl)
            PID_On = 0;
        ECurr1Summ = 0;
    }

}

void DefaultProfileOptions(void) {
    unsigned int Prf = 0;




    ProfileMass[1 + Prf] = 0; //HallDelayMem1_F;
    ProfileMass[2 + Prf] = 0; //HallDelayMem1_B;


    ProfileMass[3 + Prf] = 0;
    ProfileMass[4 + Prf] = 0;
    ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x8;

    ProfileMass[5 + Prf] = 62; //CurrUstWork;
    ProfileMass[6 + Prf] = 0;
    ProfileMass[7 + Prf] = 1; //CurrLimitWork;
    ProfileMass[8 + Prf] = 0;
    ProfileMass[9 + Prf] = 1; //PhasePERMASS;
    ProfileMass[10 + Prf] = 0; //PhasePERMASS_SHFT;
    ProfileMass[11 + Prf] = 50;
    ProfileMass[12 + Prf] = 30;

    ProfileMass[13 + Prf] = 0;
    ProfileMass[14 + Prf] = 0;
    ProfileMass[15 + Prf] = 0;
    ProfileMass[16 + Prf] = 0;

    Prf = SIZE_OF_PROFILE;


    ProfileMass[1 + Prf] = 0; //HallDelayMem1_F;
    ProfileMass[2 + Prf] = 0; //HallDelayMem1_B;


    ProfileMass[3 + Prf] = 0;
    ProfileMass[4 + Prf] = 0;
    ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x8;

    ProfileMass[5 + Prf] = 62; //CurrUstWork;
    ProfileMass[6 + Prf] = 0;
    ProfileMass[7 + Prf] = 1; //CurrLimitWork;
    ProfileMass[8 + Prf] = 0;
    ProfileMass[9 + Prf] = 1; //PhasePERMASS;
    ProfileMass[10 + Prf] = 0; //PhasePERMASS_SHFT;

    ProfileMass[11 + Prf] = 75;
    ProfileMass[12 + Prf] = 45;

    ProfileMass[13 + Prf] = 0;
    ProfileMass[14 + Prf] = 0;
    ProfileMass[15 + Prf] = 0;
    ProfileMass[16 + Prf] = 0;



    Prf = SIZE_OF_PROFILE * 2;


    ProfileMass[1 + Prf] = 0; //HallDelayMem1_F;
    ProfileMass[2 + Prf] = 0; //HallDelayMem1_B;


    ProfileMass[3 + Prf] = 0;
    ProfileMass[4 + Prf] = 0;
    ProfileMass[3 + Prf] = ProfileMass[3 + Prf] | 0x8;

    ProfileMass[5 + Prf] = 62; //CurrUstWork;
    ProfileMass[6 + Prf] = 0;
    ProfileMass[7 + Prf] = 1; //CurrLimitWork;
    ProfileMass[8 + Prf] = 0;
    ProfileMass[9 + Prf] = 1; //PhasePERMASS;
    ProfileMass[10 + Prf] = 0; //PhasePERMASS_SHFT;

    ProfileMass[11 + Prf] = 100;
    ProfileMass[12 + Prf] = 60;


    ProfileMass[13 + Prf] = 0;
    ProfileMass[14 + Prf] = 0;
    ProfileMass[15 + Prf] = 0;
    ProfileMass[16 + Prf] = 0;





}

void ChangeProfile(void) {
    unsigned char ProfileTMP = Profile;


    if (HvBt4) {
        HvBt4 = 0;
        switch (_3psnSwitchBt4) {
            case 1:
                Profile = 1;
                break;
            case 2:
                Profile = 2;
                break;
            case 3:
                Profile = 3;
                break;
        }
    }
    if (HvBt3) {
        HvBt3 = 0;
        switch (_3psnSwitchBt3) {
            case 1:
                Profile = 1;
                break;
            case 2:
                Profile = 2;
                break;
            case 3:
                Profile = 3;
                break;
        }
    }

    if ((Bt3Up&&!But4Pressed) || (Bt4Up&&!But3Pressed)) {
        Bt3Up = 0;
        Bt4Up = 0;
        switch (_3psnSwitchBtNotPressed) {
            case 1:
                Profile = 1;
                break;
            case 2:
                Profile = 2;
                break;
            case 3:
                Profile = 3;
                break;
        }
    }


    if (ProfileTMP != Profile) {
        MassToOptionsProfile();
        OptionsToMass();
        MustTrmFlashMass = 1;
        switch (Profile) {
            case 1:
                SoundNum = 15;
                break;
            case 2:
                SoundNum = 16;
                break;
            case 3:
                SoundNum = 17;
                break;
        }
        if (!SpeedControl)
            PID_On = 0;

    }


}

void SetStartingProfile3PsnBtn(void) {
    unsigned char ProfileTMP = Profile;

    if (!ThreePositionSwitch)
        return;
    if (!Starting)
        return;

    if (But3Pressed) {
        switch (_3psnSwitchBt3) {
            case 1:
                Profile = 1;
                break;
            case 2:
                Profile = 2;
                break;
            case 3:
                Profile = 3;
                break;
        }
    }
    if (But4Pressed) {
        switch (_3psnSwitchBt4) {
            case 1:
                Profile = 1;
                break;
            case 2:
                Profile = 2;
                break;
            case 3:
                Profile = 3;
                break;
        }
        if (!But3Pressed&&!But4Pressed) {
            switch (_3psnSwitchBtNotPressed) {
                case 1:
                    Profile = 1;
                    break;
                case 2:
                    Profile = 2;
                    break;
                case 3:
                    Profile = 3;
                    break;
            }
        }


    }

    if (ProfileTMP != Profile) {
        MassToOptionsProfile();
        OptionsToMass();
        MustTrmFlashMass = 1;
    }


}


//Spd1UST

void AutoPIDStateMachine(void) {
    float AutoPID_On_SpeedFl = ((float) AutoPID_On_Speed) / 10;

    if (!AutoPID) {
        AutoPIDState = 0;
        return;
    }
    switch (AutoPIDState) {
        case 0:
            PWM1TempSumm = 0;
            PWM1TempSummfl = 0;
            PWM1TempSummCnt = 256;
            AutoPIDState = 1;
            break;
        case 1:
            if (!SpeedControl)
                PWM1TempSumm = PWM1TempSumm + PWM1Temp;
            else
                PWM1TempSummfl = PWM1TempSummfl + Spd1UST;
            PWM1TempSummCnt--;
            if (!PWM1TempSummCnt) {
                PWM1TempSumm = PWM1TempSumm >> 8;
                PWM1TempSummfl = PWM1TempSummfl / 256;
                if (!SpeedControl)
                    AutoPIDState = 2;
                else
                    AutoPIDState = 3;
                AutoPID_On_Cnt = AutoPID_On_CntConst;
            }
            break;
        case 2:
            if (PWM1TempSumm < AutoPID_On_PWM) {
                AutoPIDState = 0;
                return;
            }
            if ((PWM1Temp > (PWM1TempSumm - AutoPID_On_PWM))&&(PWM1Temp < (PWM1TempSumm + AutoPID_On_PWM))) {
                AutoPID_On_Cnt--;
                if (!AutoPID_On_Cnt) {
                    if (!PID_On) {
                        if (!Wheeling) {
                            if (!SpeedControl) {
                                SoundNum = 1;
                                StrtPID_On = 1;
                                AutoPIDState = 7;
                                BtPID_Activated = 1;
                                /*if (StrongModePID)
                                {
                                PrevStrongMode=StrongMode;
                                StrongMode=1;
                                }*/

                            }
                        }
                    }
                }
            } else
                AutoPIDState = 0;
            break;
        case 3:
            if (PWM1TempSummfl < AutoPID_On_SpeedFl) {
                AutoPIDState = 0;
                return;
            }
            if ((Spd1UST > (PWM1TempSummfl - AutoPID_On_SpeedFl))&&(Spd1UST < (PWM1TempSummfl + AutoPID_On_SpeedFl))) {
                AutoPID_On_Cnt--;
                if (!AutoPID_On_Cnt) {
                    if (SpeedControl) {
                        SpeedControlPID = 1;
                        Spd1UST = Spd1Res;
                        SoundNum = 1;
                        AutoPIDState = 7;
                        /*if (StrongModePID)
                            {
                            PrevStrongMode=StrongMode;
                            StrongMode=1;
                            }*/

                    }
                }
            } else
                AutoPIDState = 0;
            break;
        case 7:
            if ((!PID_On)&&(!SpeedControl))
                AutoPIDState = 0;

            if ((!SpeedControlPID)&&(SpeedControl))
                AutoPIDState = 0;

            break;
    }
}

void CopyProfiles(void) {
    int i;
    for (i = 0; i < SIZE_OF_PROFILE; i++) {
        ProfileMass[i + SIZE_OF_PROFILE] = ProfileMass[i];
        ProfileMass[i + (SIZE_OF_PROFILE * 2)] = ProfileMass[i];
    }
    SoundNum = 1;
}

void SendFlashMassToPC(void) {
    unsigned int CntBt = 4;
    int i;

    if (HC05_BUSY)
        return;
    if (MustTrmHC05)
        return;
    if (!Hv_HC05)
        return;
    if (!MustTrmFlashMassForSaveOptPC)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    MustTrmFlashMassForSaveOptPC = 0;





    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;


    HC05TrmMass[3] = 10; //COMMAND

    for (i = 0; i<sizeof (FlashMass); i++)
        HC05TrmMass[CntBt++] = FlashMass[i];


    HC05TrmMass[2] = CntBt - 3;


    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;

}

void SendFlashMass2ToPC(void) {
    unsigned int CntBt = 4;
    int i;

    if (HC05_BUSY)
        return;
    if (MustTrmHC05)
        return;
    if (!Hv_HC05)
        return;
    if (!MustTrmFlashMass2ForSaveOptPC)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    MustTrmFlashMass2ForSaveOptPC = 0;





    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;


    HC05TrmMass[3] = 17; //COMMAND

    for (i = 0; i<sizeof (FlashMass2); i++)
        HC05TrmMass[CntBt++] = FlashMass2[i];


    HC05TrmMass[2] = CntBt - 3;


    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;

}

void SendProfileMassToPC(void) {
    unsigned int CntBt = 4;
    int i;

    if (HC05_BUSY)
        return;

    if (MustTrmHC05)
        return;
    if (!Hv_HC05)
        return;
    if (!MustTrmProfileMass)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    MustTrmProfileMass = 0;





    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;


    HC05TrmMass[3] = 11; //COMMAND

    for (i = 0; i<sizeof (ProfileMass); i++)
        HC05TrmMass[CntBt++] = ProfileMass[i];


    HC05TrmMass[2] = CntBt - 3;


    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;

}

void CmdOK(void) {
    unsigned int CntBt = 4;


    if (HC05_BUSY)
        return;

    if (MustTrmHC05)
        return;
    if (!Hv_HC05)
        return;
    if (!MustTrmCmdOk)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    MustTrmCmdOk = 0;


    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;
    HC05TrmMass[2] = 1;
    HC05TrmMass[3] = 12; //COMMAND
    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;
}

void CmdOK2(void) {
    unsigned int CntBt = 4;


    if (HC05_BUSY)
        return;

    if (MustTrmHC05)
        return;
    if (!Hv_HC05)
        return;
    if (!MustTrmCmdOk2)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    MustTrmCmdOk2 = 0;


    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;
    HC05TrmMass[2] = 1;
    HC05TrmMass[3] = 13; //COMMAND
    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;
}

void CmdOK3(void) {
    unsigned int CntBt = 4;


    if (HC05_BUSY)
        return;

    if (MustTrmHC05)
        return;
    if (!Hv_HC05)
        return;
    if (!MustTrmCmdOk3)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    MustTrmCmdOk3 = 0;


    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;
    HC05TrmMass[2] = 1;
    HC05TrmMass[3] = 18; //COMMAND
    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;
}

void SensorlessManualStartInit(void) {
    SensorLessOnCnt = 250;


    StateSensorlessMotorStart = 1;


    CurrLimit = SensorLessCurrLimit;
    ChangeCVR();

    CurrUst = SensorlessCurrUst;
    Alignment = 1;
    SensorlessNotBEMF = 1;
    SensorlessStartNoHalls = 1;

    SenosrlessPWM1 = 0;
    SensorLessTimerConst = SensorLessTimerConstConst;
    if (!(StartingMoveCnt && CriticalError)) {
        if (DS) {
            DS = 0;
            RdSensors();
        }
    }

    CntBEMF = 0;
}

void CmdSendUnlockMSG(void) {
    unsigned int CntBt = 4;


    if (HC05_BUSY)
        return;

    if (MustTrmHC05)
        return;
    if (!Hv_HC05)
        return;
    if (!SendUnlockMSG)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;

    SendUnlockMSG = 0;


    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;
    HC05TrmMass[2] = 1;
    HC05TrmMass[3] = 14; //COMMAND
    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);

    MustTrmHC05 = 1;
}

typedef union {
    unsigned long int Val;
    unsigned int w[2] __attribute__((packed));
    unsigned char v[4];

    struct __attribute__((packed)) {
        unsigned int LW;
        unsigned int HW;
    }
    word;

    struct __attribute__((packed)) {
        unsigned char LB;
        unsigned char HB;
        unsigned char UB;
        unsigned char MB;
    }
    byte;
} uint32_t_VAL;

unsigned long int ReadProgramMemory(unsigned long int address) {
    uint32_t_VAL dwvResult;
    unsigned int wTBLPAGSave;

    wTBLPAGSave = TBLPAG;
    TBLPAG = ((uint32_t_VAL*) & address)->w[1]; ////->w[1];

    dwvResult.w[1] = __builtin_tblrdh((unsigned int) address);
    dwvResult.w[0] = __builtin_tblrdl((unsigned int) address);
    TBLPAG = wTBLPAGSave;

    return dwvResult.Val;
}

void Lights(void) {
    if (Monocycle && LightsTudaSuda)
        return;
    if (LightsFromButton)
        return;

    if (!CntTurn) {
        if (LeftTurn) {
#if !defined VECTOR
            if (Left)
                Left = 0;
            else {
                if (!Monocycle)
                    SoundNum = 12;
                Left = 1;
            }
#else
            if (!Left) {
                Left = 1;
                CntTurn = CntTurnOffConst;
            } else {
                if (!Monocycle)
                    SoundNum = 12;
                Left = 0;
                CntTurn = CntTurnOnConst;
            }
#endif

            //CntTurn=50;
        } else {
#if !defined VECTOR
            if (!StopLights)
                Left = 0;
            else {
                Left = 1;
            }
#else
            if (!StopLights)
                Left = 1;
            else {
                Left = 0;
            }
#endif
        }

        if (RightTurn) {
#if !defined VECTOR
            if (Right)
                Right = 0;
            else {
                if (!Monocycle)
                    SoundNum = 12;
                Right = 1;
            }
#else
            if (!Right) {
                Right = 1;
                CntTurn = CntTurnOffConst;
            } else {
                if (!Monocycle)
                    SoundNum = 12;
                Right = 0;
                CntTurn = CntTurnOnConst;
            }
#endif
            //CntTurn=150;
        } else {
#if !defined VECTOR
            if (!StopLights)
                Right = 0;
            else {
                Right = 1;
            }
#else
            if (!StopLights)
                Right = 1;
            else {
                Right = 0;
            }
#endif
        }

        if ((!LeftTurn)&&(!RightTurn))
            CntTurn = 0;

    } else
        CntTurn--;

}

void BzFuncOn(void) {
    if (!BuzzerOff) {
        Buzzer = 1;
#if !defined VECTOR
#if !defined ISOLATED
        if (BuzzAndHorn)
            Horn = 1;
        if (HorningL || HorningH)
            Horn = 1;
#else
        if (BuzzAndHorn)
            Horn = 0;

        if (HorningL || HorningH)
            Horn = 0;

#endif
#else
        if (BuzzAndHorn) {
            if (!LightOn&&!KeyLightStop)
#if !defined VECTORS
                Horn = 0;
#else
                //Horn=1;
                OC3R = ((unsigned int) KeyLightBrightness) << 8;
#endif
        }
        if (HorningL || HorningH)
#if !defined VECTORS
            Horn = 0;
#else
            //Horn=1;
            OC3R = ((unsigned int) KeyLightBrightness) << 8;
#endif

#endif
    } else {
        BuzzerMacroOff
    }
}

void ChangeCurr(void) {
    //   if (Monocycle&&(!DirectControlMotor))
    //  if (!DirectControlMotor)
    //    return;



    if (CurrDecrease) {
        CurrUst = 300;
        CurrPhaseLimit = 600;
        if (CurrLimit != 0) {
            CurrLimit = 0;
            ChangeCVR();
        }
        return;
    }


    if (!Sensorless) {
        switch (ChangeCurrStateMachine) {
            case 0:
                if (!Monocycle) {
                    if (CurrPhaseLimit != CurrPhaseLimitSpd0)
                        CurrPhaseLimit = CurrPhaseLimitSpd0;
                    if (CurrUst != CurrUstSpd0)
                        CurrUst = CurrUstSpd0;
                    if (CurrLimit != CurrLimitSpd0) {
                        CurrLimit = CurrLimitSpd0;
                        ChangeCVR();
                    }
                    if (Spd1ResPlus > SpdStartLevelFl)
                        ChangeCurrStateMachine = 1;
                } else {
                    if (CurrPhaseLimit != CurrPhaseLimitWork)
                        CurrPhaseLimit = CurrPhaseLimitWork;
                    if (CurrUst != CurrUstWork)
                        CurrUst = CurrUstWork;
                    if (CurrLimit != CurrLimitWork) {
                        CurrLimit = CurrLimitWork;
                        ChangeCVR();
                    }
                }
                break;
            case 1:
                if (CurrPhaseLimit != CurrPhaseLimitWork)
                    CurrPhaseLimit = CurrPhaseLimitWork;
                if (CurrUst != CurrUstWork)
                    CurrUst = CurrUstWork;
                if (CurrLimit != CurrLimitWork) {
                    CurrLimit = CurrLimitWork;
                    ChangeCVR();
                }
                if (Spd1Res == 0)
                    ChangeCurrStateMachine = 0;
                break;
            default:
                ChangeCurrStateMachine = 0;
                break;
        }
    } else {
        if (StateSensorlessMotorStart != 8) {
            if (CurrPhaseLimit != CurrPhaseLimitSpd0)
                CurrPhaseLimit = CurrPhaseLimitSpd0;
            if (CurrUst != CurrUstSpd0)
                CurrUst = CurrUstSpd0;
            if (CurrLimit != CurrLimitSpd0) {
                CurrLimit = CurrLimitSpd0;
                ChangeCVR();
            }
        }
        if (StateSensorlessMotorStart == 8) {
            if (CurrPhaseLimit != CurrPhaseLimitWork)
                CurrPhaseLimit = CurrPhaseLimitWork;
            if (CurrUst != CurrUstWork)
                CurrUst = CurrUstWork;
            if (CurrLimit != CurrLimitWork) {
                CurrLimit = CurrLimitWork;
                ChangeCVR();
            }
        }
    }




}

void Spd0TimerStateMachine(void) {

    switch (Spd0TimerStateMachineCnt) {
        case 0:
            Nop();
            break;
        case 1:
            if (Spd0Timer) {
                Spd0Timer--;
                if (Spd0Timer == 0) {
                    CriticalError = CRERR_SPD0;
                    Spd0TimerStateMachineCnt = 2;
                }
            }
            if (Spd1ResPlus > SpdStartLevelFl) {
                Spd0TimerStateMachineCnt = 0;
                if (CriticalError == CRERR_SPD0)
                    CriticalError = 0;
            }
            break;
        case 2:
            if ((PWM1>-110)&&(PWM1 < 110)&&(CriticalError == CRERR_SPD0)) {
                CriticalError = 0;
                Spd0TimerStateMachineCnt = 0;
                BuzzerMacroOff
            }
            break;
        default:
            Spd0TimerStateMachineCnt = 0;
            break;
    }

}

void AutoNastroyka_Func(void) {
    int i;


    if (!AutoNastroykaState)
        return;

    BreakPressed = 0;

    if (Curr1SinTSTCnt < (sizeof (Curr1SinTST) / 2))
        Curr1SinTST[Curr1SinTSTCnt++] = Curr1;
    else {
        Curr1SinTSTSumm = 0;
        for (i = 0; i < ((sizeof (Curr1SinTST) / 2) - 1); i++) {
            Curr1SinTST[i] = Curr1SinTST[i + 1];
            Curr1SinTSTSumm = Curr1SinTSTSumm + Curr1SinTST[i];
        }

        Curr1SinTSTSumm = Curr1SinTSTSumm + Curr1;
        Curr1SinTST[Curr1SinTSTCnt - 1] = Curr1;

        Curr1 = Curr1SinTSTSumm;
        Curr1SnTST = Curr1SinTSTSumm;

    }

    /*#if defined ISOLATED
    U_V=UBT/
    #else

    #endif
    38.388;
    0.4167965;
     */


    switch (AutoNastroykaState) {
        case 1:

            OK_Cnt = 0;

            //UBT_To_V();

            PWM1_SIN_TST = (int) (((float) K_PWM_Nastr)*((float) 50 / (float) UBT_V));

            HallDelayMaxSPD = 0;


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


            if (!Sensorless) {
                VectorMem = 1;
                Vector = 1;
                RdSensors();
                Amplitude1 = PDC1;
                Amplitude2 = PDC5;
                VectorInit();
            }
            OptionsToMass();


            StrongModeMem = 0;
            MixedMode = 0;
            MixedMode2 = 0;
            OptionsToMass();
            PrevStrongMode = 0;
            StrongMode = 0;



            InvSin = 0;


            SIN_MIDDLE = 0;

            RdSensors();

            OptionsToMass();


            //                     PWM32Bits=1;
            if (1)//(PWM32Bits)
            {


                switch (PWMkHz) {
                    case 1:
                        MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
                        break;
                    case 2:
                        MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE10kHz;
                        TrapezoidaWhenBigSpeed = 1;
                        if (VectorOnOffSpdLo > Trapezium10kHzLo)
                            VectorOnOffSpdLo = Trapezium10kHzLo;
                        if (VectorOnOffSpdHi > Trapezium10kHzHi)
                            VectorOnOffSpdHi = Trapezium10kHzHi;
                        break;
                    case 3:
                        MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE5kHz;
                        TrapezoidaWhenBigSpeed = 1;
                        if (VectorOnOffSpdLo > Trapezium5kHzLo)
                            VectorOnOffSpdLo = Trapezium5kHzLo;
                        if (VectorOnOffSpdHi > Trapezium5kHzHi)
                            VectorOnOffSpdHi = Trapezium5kHzHi;
                        break;
                    default:
                        MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
                        PWMkHz = 1;
                        break;
                }









                MAX_PWM = MAX_PWM_CONST;
                if (DirectControlMotor) {
                    DIRPWM1 = DIRPWM1 * 2;
                }
            } else {
                MAX_PWM_CONST = MAX_PWM_CONST_EBIKE;
                if (DirectControlMotor) {
                    DIRPWM1 = DIRPWM1 / 2;
                }
            }
            if (VectorMem)
                VectorInit();
            else
                TrapeziumInit();




            Monocycle = 0;
            LeftTurn = 0;
            ESumm = 0;
            RightTurn = 0;
            StopLights = 0;
            TiltZadAddMustBe = 0;




            TrapezoidaRAM1 = 0;


            PWM_Mode = 0;
            SlowStart = 0;

            HallDelayMem1_F = 0;
            HallDelayMem1_B = 0;
            OptionsToMass();
            MustTrmFlashMass = 1;



            CurrDecrease = 1;
            CurrUst = 300;
            CurrPhaseLimit = 600;
            CurrLimit = 0;
            ChangeCVR();



            DIRPWM1 = 0;

            TestSINOkMassCnt = 0;
            PWM1 = 0;

            OrderCnt = 0;


            AutoNastroykaState = 2;

            AutoNastroykaCMFStart(1);


            break;
        case 2:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;
            if (Spd1Res == 0) {

                AutoNastroykaState = 3;
                AutoNastroykaCMFStart(2);
            }
            break;
        case 3:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;
            Calibrating = 1;
            AutoNastroykaState = 4;
            AutoNastroykaCMFStart(3);
            break;
        case 4:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;
            if (Calibrating == 0) {
                AutoNastroykaState = 5;
                AutoNastroykaCMFStart(4);
            }
            break;

        case 5:
            PWM1 = PWM1_SIN_TST;
            if (AutoNastrConfirmWait())
                return;



            if (DS) {
                DS = 0;
                RdSensors();
            }




            SensOrder1 = OrderCnt;
            RdSensors();


            OptionsToMass();
            MustTrmFlashMass = 1;

            CntTestingSinDelay = 250;
            AutoNastroykaState = 6;
            AutoNastroykaCMFStart(5);
            break;

        case 6:
            PWM1 = PWM1_SIN_TST;
            if (AutoNastrConfirmWait())
                return;
            CntTestingSinDelay--;
            if (CntTestingSinDelay == 0) {
                AutoNastroykaState = 7;
                AutoNastroykaCMFStart(6);
                TestingSin = 1;
                StrtTestingSin = 1;
                TestSIN_Ok = 0;
                TestSIN_OkCnt = 3;
                CntTestingSinDelay = 350;
            }
            break;
        case 7:
            PWM1 = PWM1_SIN_TST;
            if (AutoNastrConfirmWait())
                return;
            CntTestingSinDelay--;
            if (CntTestingSinDelay == 0) {
                if (OrderCnt < 5) {
                    OrderCnt++;
                    AutoNastroykaState = 8;
                } else {
                    AutoNastroykaState = 10;
                }
                AutoNastroykaCMFStart(7);
            }
            if (!TestingSin) {
                if (TestSIN_Ok) {
                    TestSIN_Ok_Mass[TestSINOkMassCnt][0] = OrderCnt;
                    TestSIN_Ok_Mass[TestSINOkMassCnt++][1] = InvSin;

                    Nop();
                    Nop();

                    OK_Cnt++;

                } else {
                    Nop();
                    Nop();
                }
                if (OrderCnt < 5) {
                    OrderCnt++;
                    AutoNastroykaState = 8;
                } else {
                    AutoNastroykaState = 10;
                }
                AutoNastroykaCMFStart(7);
            }
            break;
        case 8:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;

            if (Spd1Res == 0) {
                AutoNastroykaState = 5;
                CntTestingSinDelay = 150;
                AutoNastroykaCMFStart(8);
            }
            break;
        case 9:
            PWM1 = 0;
            /*if (AutoNastrConfirmWait())
             return;
          if (!MustTrmStateOfSinTest)//&&!TestSIN_Ok)
         {
             AutoNastroykaState=5;
                 AutoNastroyka_ConfirmMSG=0;           
             MustTrmStateOfSinTest=1;
         }*/
            break;



        case 10:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;

            if (!InvSin) {
                InvSin = 1;
                OrderCnt = 0;
                AutoNastroykaState = 8;
            } else
                AutoNastroykaState = 11;
            AutoNastroykaCMFStart(10);
            break;
        case 11:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;
            if (TestSINOkMassCnt == 0) {
                //AutoNastroykaState=254;
                AutoNastroykaState = 28;
                AutoNastroykaCMFStart(254);
            } else {
                TestCWCntMass = 0;
                CntTestingSinDelay = 50;
                AutoNastroykaState = 12;
                AutoNastroykaCMFStart(11);
            }

            break;








        case 12:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;

            SensOrder1 = TestSIN_Ok_Mass[TestCWCntMass][0];
            InvSin = TestSIN_Ok_Mass[TestCWCntMass][1];
            RdSensors();

            OptionsToMass();
            MustTrmFlashMass = 1;
            AutoNastroykaState = 14;
            //  MustTrmStateOfSinTest=1;
            CntTestingSinDelay = 100;

            PWMNastr = 0;
            AutoNastroykaCMFStart(12);
            break;

        case 13:
            PWM1 = 0;
            /*
                           if (AutoNastrConfirmWait())
                            return;


                        StrongMode=1;
                        CntTestingSinDelay--;
                        if (CntTestingSinDelay==0)
                        {
                            AutoNastroykaState=14;
                            AutoNastroykaCMFStart(13);
                            DS=0;
                        }*/
            break;

        case 14:
            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;

            PWMNastr++;
            if (/*(Spd1ResPlus>10)||*/(PWMNastr > (PWM1_SIN_TST * 2))) {
                AutoNastroykaState = 15;
                CntTestingSinDelay = 400;
                Curr1SinTSTCnt = 0;
                AutoNastroykaCMFStart(14);
            }
            PWM1 = PWMNastr;
            break;

        case 15:
            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;

            CntTestingSinDelay--;
            if (CntTestingSinDelay == 0) {
                CurrSinTSTMass[TestCWCntMass] = Curr1SnTST;
                AutoNastroykaState = 16;
                AutoNastroykaCMFStart(15);
            }
            break;

        case 16:
            if (PWMNastr > 0)
                PWMNastr--;
            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;
            if (Spd1Res == 0) {
                if (TestCWCntMass < (TestSINOkMassCnt - 1)) {
                    TestCWCntMass++;
                    AutoNastroykaState = 12;
                } else {
                    AutoNastroykaState = 17;
                }
                AutoNastroykaCMFStart(16);
            }
            break;

        case 17:
            CurrMinSinTST = 0x7fffffff;
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;

            for (i = 0; i <= TestCWCntMass; i++) {
                if (CurrMinSinTST > CurrSinTSTMass[i]) {
                    CurrMinSinTST = CurrSinTSTMass[i];
                    iMin = i;
                }
            }

            SensOrder1 = TestSIN_Ok_Mass[iMin][0];
            InvSin = TestSIN_Ok_Mass[iMin][1];
            RdSensors();

            OptionsToMass();
            MustTrmFlashMass = 1;

            CntTestingSinDelay = 50;
            AutoNastroykaState = 19;
            AutoNastroykaCMFStart(17);

            break;

        case 18:
            PWM1 = 0;
            //          if (AutoNastrConfirmWait())
            //         return;
            if (CntTestingSinDelay)
                CntTestingSinDelay--;
            if ((CntTestingSinDelay == 0)&&(Spd1ResPlus == 0)) {
                // AutoNastroykaState=25;        //for shift tune
                //
                AutoNastroykaState = 27; //for Throttle and break tune
                PWMNastr = 0;
                AutoNastroykaCMFStart(18);
            }
            break;

        case 25:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;
            Calibrating = 1;
            AutoNastroykaState = 26;
            AutoNastroykaCMFStart(25);
            break;

        case 19:

            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;


            if (PWMNastr < (PWM1_SIN_TST))//*2))
            {
                PWMNastr++;
            } else {
                AutoNastroykaState = 34;
                AutoNastroykaCMFStart(19);

            }


            break;




        case 26:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;
            if (Calibrating == 0) {
                AutoNastroykaState = 20;
                AutoNastroykaCMFStart(26);
            }
            break;



        case 20:
            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;
            PWMNastr++;
            if ((Spd1ResPlus > 10) || (PWMNastr > (PWM1_SIN_TST * 2))) {
                AutoNastroykaState = 21;
                CntTestingSinDelay = 400;
                Curr1SinTSTCnt = 0;
                AutoNastroykaCMFStart(20);
            }
            PWM1 = PWMNastr;
            break;

        case 21:
            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;

            CntTestingSinDelay--;
            if (CntTestingSinDelay == 0) {

                Curr1SnTST_0 = Curr1SnTST;
                if (Curr1SnTST_0 < 0) {
                    AutoNastroykaState = 255;
                    AutoNastroykaCMFStart(255);
                } else {
                    Curr1SnTST_0 = (long int) (((float) Curr1SnTST_0)*1.5);

                    AutoNastroykaState = 22;
                    Shift_F = 1;
                    AutoNastroykaCMFStart(21);
                }
            }
            break;
        case 22:
            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;

            AutoNastroykaState = 23;
            AutoNastroykaCMFStart(22);
            if (Shift_F) {
                if (HallDelayMem1_F>-20)
                    HallDelayMem1_F--;
                else {
                    Shift_F = 0;
                    HallDelayMem1_B--;
                    HallDelayMem1_F = 0;
                }

            } else {
                if (HallDelayMem1_B>-20)
                    HallDelayMem1_B--;
                else {
                    AutoNastroykaState = 256;
                    AutoNastroykaCMFStart(256);
                }
            }
            OptionsToMass();
            MustTrmFlashMass = 1;

            CntTestingSinDelay = 250;
            break;

        case 23:
            PWM1 = PWMNastr;
            if (AutoNastrConfirmWait())
                return;

            CntTestingSinDelay--;
            if (CntTestingSinDelay == 0) {

                if (Curr1SnTST_0 > Curr1SnTST) {
                    AutoNastroykaState = 22;
                } else {
                    AutoNastroykaState = 24;
                    if (Shift_F)
                        HallDelayMem1_F = 0;
                    else
                        HallDelayMem1_B = 0;

                    Curr1SnTST_0 = Curr1SnTST;

                    ShiftUpping = 1;

                }

                AutoNastroykaCMFStart(23);


            }
            break;

        case 24:
            PWM1 = PWMNastr; //HallDelayMem1_x  FOUND
            /* if (AutoNastrConfirmWait())
              return;

          if (ShiftUpping)
          {
              if (Shift_F)
                  if (HallDelayMem1_F<25)
                      HallDelayMem1_F=HallDelayMem1_F+5;
                  else
                  {
                        
                  }
              else
                  if (HallDelayMem1_B<25)
                      HallDelayMem1_B=HallDelayMem1_B+5;
                  else
                  {
                        
                  }
          }
             */

            break;


        case 27:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;

            SensorThresholdDnTmp = SensorThresholdDn;
            BreakThresholdDnTmp = BreakThresholdDn;
            SensorThresholdDn = ADCThrottle + 50;
            BreakThresholdDn = ADCThrottleBreak + 50;
            OptionsToMass();
            MustTrmFlashMass = 1;

            AutoNastroykaState = 28;
            AutoNastroykaCMFStart(27);


            break;



        case 28:
            PWM1 = 0;
            break;

        case 29:
            PWM1 = 0;
            if (ADCThrottle >= 1500)
                SensorThresholdUp = ADCThrottle - 70;
            else {
                SensorThresholdDn = 700;
                SensorThresholdUp = 2900;
                AutoNastroykaState = 35;
                AutoNastroykaCMFStart(33); //Too low SensorThresholdUp
                break;
            }

            if (SensorThresholdDn > 1000) {
                SensorThresholdDn = 700;
                SensorThresholdUp = 2900;
                AutoNastroykaState = 35;
                AutoNastroykaCMFStart(34); //Too low SensorThresholdUp
                break;
            }

            if (SensorThresholdUp < SensorThresholdDn) {
                SensorThresholdDn = 700;
                SensorThresholdUp = 2900;
                AutoNastroykaState = 35;
                AutoNastroykaCMFStart(35); //Too low SensorThresholdUp
                break;
            }
            OptionsToMass();
            MustTrmFlashMass = 1;

            AutoNastroykaState = 30;
            AutoNastroykaCMFStart(29);
            break;


        case 30:
            PWM1 = 0;

            break;

        case 31:
            PWM1 = 0;
            if (ADCThrottleBreak >= 1500)
                BreakThresholdUp = ADCThrottleBreak - 50;
            else {
                BreakThresholdDn = 700;
                BreakThresholdUp = 2900;
                AutoNastroykaState = 36;
                AutoNastroykaCMFStart(36); //Too low SensorThresholdUp
                break;
            }


            if (SensorThresholdDn > 1000) {
                BreakThresholdDn = 700;
                BreakThresholdUp = 2900;
                AutoNastroykaState = 36;
                AutoNastroykaCMFStart(37); //Too low SensorThresholdUp
                break;
            }





            if (BreakThresholdUp < BreakThresholdDn) {
                BreakThresholdDn = 700;
                BreakThresholdUp = 2900;
                AutoNastroykaState = 36;
                AutoNastroykaCMFStart(38); //Too low SensorThresholdUp
                break;
            }

            OptionsToMass();
            MustTrmFlashMass = 1;

            AutoNastroykaState = 32;
            AutoNastroykaCMFStart(31);
            break;


        case 32:
            PWM1 = 0;
            if (AutoNastrConfirmWait())
                return;
            AutoNastroykaState = 33;
            AutoNastroykaCMFStart(32);
            break;

        case 33:
            PWM1 = 0;
            break;

        case 34:
            PWM1 = PWMNastr;
            break;

        case 35:
            PWM1 = 0;

            break;
        case 36:
            PWM1 = 0;

            break;

        case 254:
            PWM1 = 0;
            break;
        case 255:
            PWM1 = 0;
            break;
        case 256:
            PWM1 = 0;
            break;
    }


}

void SendStateOfSinTest(void) {
    unsigned int CntBt = 4;
    int Tmp;

    if (HC05_BUSY)
        return;

    if (!Hv_HC05)
        return;
    if (!MustTrmStateOfSinTest)
        return;
    if (OnTransmittHC05)
        return;
    HC05_BUSY = 1;









    HC05TrmMass[0] = 0xff;
    HC05TrmMass[1] = 0xff;


    HC05TrmMass[3] = 15; //COMMAND



    Tmp = (int) AutoNastroykaStateFn; //AutoNastroykaState;     1
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    AutoNastroykaStateFn = 0;

    HC05TrmMass[CntBt++] = Curr1SnTST; //Curr1SnTST    2
    HC05TrmMass[CntBt++] = Curr1SnTST >> 8;
    HC05TrmMass[CntBt++] = Curr1SnTST >> 16;
    HC05TrmMass[CntBt++] = Curr1SnTST >> 24;

    HC05TrmMass[CntBt++] = TestSIN_Ok; //  TestSIN_Ok      3

    if (TestSIN_Ok)
        TestSIN_Ok = 0;
    HC05TrmMass[CntBt++] = TestSINOkMassCnt; //  TestSINOkMassCnt   4
    HC05TrmMass[CntBt++] = SensOrder1; //  SensOrder1  5
    HC05TrmMass[CntBt++] = InvSin; //  InvSin  6


    HC05TrmMass[CntBt++] = Curr1SnTST_0; //Curr1SnTST_0    7
    HC05TrmMass[CntBt++] = Curr1SnTST_0 >> 8;
    HC05TrmMass[CntBt++] = Curr1SnTST_0 >> 16;
    HC05TrmMass[CntBt++] = Curr1SnTST_0 >> 24;


    HC05TrmMass[CntBt++] = Curr1SnTST; //Curr1SnTST    8
    HC05TrmMass[CntBt++] = Curr1SnTST >> 8;
    HC05TrmMass[CntBt++] = Curr1SnTST >> 16;
    HC05TrmMass[CntBt++] = Curr1SnTST >> 24;


    Tmp = (int) CntAutoNastroykaState257; //CntAutoNastroykaState257;     9
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = (int) SensorThresholdDn; //SensorThresholdDn;     10
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = (int) SensorThresholdUp; //SensorThresholdUp;     11
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = (int) BreakThresholdDn; //BreakThresholdUp;     12
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    Tmp = (int) BreakThresholdUp; //BreakThresholdUp;     13
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;


    HC05TrmMass[CntBt++] = UBT_V; //UBT_V                     14


    Tmp = (int) PWM1_SIN_TST; //PWM1_SIN_TST;     15
    HC05TrmMass[CntBt++] = Tmp;
    HC05TrmMass[CntBt++] = Tmp >> 8;




    HC05TrmMass[2] = CntBt - 3;


    HC05TrmMass[CntBt++] = CalcCheckSumm(HC05TrmMass[2] + 1, &HC05TrmMass[2]);



    MustTrmHC05 = 1;


    //    TrmHC05(HC05TrmMass);


    MustTrmStateOfSinTest = 0;





}

unsigned char AutoNastrConfirmWait(void) {

    if (HvConfirm)
        return 0;
    if (AutoNastroyka_ConfirmDelayCnt != 0) {
        AutoNastroyka_ConfirmDelayCnt--;
        if (AutoNastroyka_ConfirmMSG) {
            HvConfirm = 1;
            return 0;
        } else
            return 1;
    } else {
        HvConfirm = 1;
        CntAutoNastroykaState257++;

        /*AutoNastroykaState=257;
                   AutoNastroyka_ConfirmDelayCnt=200;
                    AutoNastroyka_ConfirmMSG=0;  
                    HvConfirm=0;
                    MustTrmStateOfSinTest=1;
                    
        return 2;
         */
        return 0;
    }
}

void AutoNastroykaCMFStart(unsigned int AutoNastroykaStateFin) {
    AutoNastroykaStateFn = AutoNastroykaStateFin;
    AutoNastroyka_ConfirmDelayCnt = 200;
    AutoNastroyka_ConfirmMSG = 0;
    HvConfirm = 0;
    MustTrmStateOfSinTest = 1;
}

void UBT_To_V(void) {
#if !defined VECTOR
#if !defined ISOLATED                               
    float UBtFl = (float) UBT / (float) 38.388;
    UBT_V = (unsigned int) UBtFl;

#else
    UBtFl = (float) UBT * (float) 0.4167965;
    UBT_V = (unsigned int) UBtFl;

#endif
#else
    UBtFl = (float) UBT / (float) 38.388;
    UBT_V = (unsigned int) UBtFl;
    _12VFl = (float) _12V * (float) 0.00373533;
    _5VFl = (float) _5V * (float) 0.00146484;
    _3VFl = (float) _3V * (float) 0.00097167;

#endif

}

void SetPIN_HC05(void) {
    unsigned int Cnt = 0;
    if (!PIN_CODE_HC05)
        return;

    if (OnTransmittHC05)
        return;
    if (HC05_BUSY)
        return;
    HC05_BUSY = 1;





    PinCodeMass[0] = 'A';
    PinCodeMass[1] = 'T';
    PinCodeMass[2] = '+';
    PinCodeMass[3] = 'P';
    PinCodeMass[4] = 'S';
    PinCodeMass[5] = 'W';
    PinCodeMass[6] = 'D';
    PinCodeMass[7] = '=';



    PIN_CODE_HC05 = 0;
#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 1;
#else
    KEY_BT = 0;
#endif
#else
    KEY_BT = 1;
#endif

    long int g;
    ResetedPIN = 1;

    for (g = 0; g < 150000; g++)
        Nop();
    HvReplyHC05 = 0;
    MyTimeOut = 550;

    AT_Rec = 1;
    RecMassHC05[0] = 3;
oooo:
    //     TrmHC05_AT("AT+PSWD=a0001\r\n",sizeof("AT+PSWD=a0001\r\n"));//
    TrmHC05_AT((char*) PinCodeMass, (int) StringPINLenght); //
    while ((!HvReplyHC05)&&(MyTimeOut));

    if (RecMassHC05[0] == 'O') {
        SoundNum = 10;
    } else {
        //SoundNum=9;
        Cnt++;
        if (Cnt < 30)
            goto oooo;
        else
            SoundNum = 9;
    }
    AT_Rec = 0;

#if !defined VECTOR
#if defined ISOLATED    
    KEY_BT = 0;
#else
    KEY_BT = 1;
#endif
#else
    KEY_BT = 0;
#endif


}

void FillPINResetMass(void) {
    RecBytes[0] = 0x6;
    RecBytes[1] = 0xfe;
    RecBytes[2] = 0x3a;
    RecBytes[3] = 0x31;
    RecBytes[4] = 0x32;
    RecBytes[5] = 0x33;
    RecBytes[6] = 0x34;
    RecBytes[7] = 0xf7;
    RecBytes[8] = 0x7a;


    ResetedPIN = 1;

    Locked = 0;
    HvPacketU4_FL = 1;
}

void PID_OnOff_Func(void) {

    if (SpeedControl) {
        if (!SpeedControlPID) {
            SpeedControlPID = 1;
            Spd1UST = Spd1Res;
            SpeedControlPIDOffCnt = 500;
            SoundNum = 1;
        } else {
            if (!StartingBTN) {
                if (SpeedControlPID)
                    SoundNum = 10;
            }
            SpeedControlPID = 0;
        }
    } else {
        if (!PID_On) {
            if (!Wheeling) {
                SoundNum = 1;
                Spd1UST = Spd1Res;
                StrtPID_On = 1;
                BtPID_Activated = 1;
            }
        } else {
            PID_On = 0;
        }

    }
}

/*

void ResetPIN_HC05(void)
{
    
    if (!MustResetPIN)
        return;
 
     if (OnTransmittHC05)
         return;
        if (HC05_BUSY)
        return;



    
    
    ResetedPIN=1;
    
    
      HC05_BUSY=1;
      
      
#if defined ISOLATED    
    KEY_BT=1;
#else
    KEY_BT=0;
#endif
long int g;
                            for (g=0;g<150000;g++)
                                Nop();
                            HvReplyHC05=0;
                            MyTimeOut=550;
  
                            AT_Rec=1;
                            RecMassHC05[0]=3;
                            
                            TrmHC05_AT("AT+PSWD=1234\r\n",sizeof("AT+PSWD=1234\r\n"));//
                         
                            while ((!HvReplyHC05)&&(MyTimeOut));

                            if (RecMassHC05[0]=='O')
                            {
                                 SoundNum=1;
                                }
                            else
                            {
                                Nop();
                                Nop();
                                Nop();
                            }
                            AT_Rec=0;
            MustResetPIN=0;

#if defined ISOLATED    
                            KEY_BT=0;
#else
                            KEY_BT=1;
#endif



}
 */



void MPU60000Init(void) {

    if (MPU6000_Initialized)
        return;

    //    if (!NoBalance)
    //      return;

    if (!HvToTest)
        return;

    MPU60000_Initializing = 1;

    HvToTest = 0;






    Gyro_rxBuf[0] = 0;
    Gyro_rxBuf[1] = 0;
    Gyro_rxBuf[2] = 0;
    Gyro_rxBuf[3] = 0;
    Gyro_rxBuf[4] = 0;




    _SELF_TEST_X = readByte(SELF_TEST_X);
    _SELF_TEST_Y = readByte(SELF_TEST_Y);
    _SELF_TEST_Z = readByte(SELF_TEST_Z);
    _SELF_TEST_A = readByte(SELF_TEST_A);

    _SMPLRT_DIV = readByte(SMPLRT_DIV);
    _CONFIG = readByte(CONFIG);
    _GYRO_CONFIG = readByte(GYRO_CONFIG);
    _ACCEL_CONFIG = readByte(ACCEL_CONFIG);
    _FIFO_EN = readByte(FIFO_EN);
    _I2C_MST_CTRL = readByte(I2C_MST_CTRL);


    _I2C_SLV0_ADDR = readByte(I2C_SLV0_ADDR);
    _I2C_SLV0_REG = readByte(I2C_SLV0_REG);
    _I2C_SLV0_CTRL = readByte(I2C_SLV0_CTRL);
    _I2C_SLV1_ADDR = readByte(I2C_SLV1_ADDR);
    _I2C_SLV1_REG = readByte(I2C_SLV1_REG);
    _I2C_SLV1_CTRL = readByte(I2C_SLV1_CTRL);
    _I2C_SLV2_ADDR = readByte(I2C_SLV2_ADDR);


    _I2C_SLV2_REG = readByte(I2C_SLV2_REG);
    _I2C_SLV2_CTRL = readByte(I2C_SLV2_CTRL);
    _I2C_SLV3_ADDR = readByte(I2C_SLV3_ADDR);
    _I2C_SLV3_REG = readByte(I2C_SLV3_REG);
    _I2C_SLV3_CTRL = readByte(I2C_SLV3_CTRL);
    _I2C_SLV4_ADDR = readByte(I2C_SLV4_ADDR);
    _I2C_SLV4_REG = readByte(I2C_SLV4_REG);
    _I2C_SLV4_DO = readByte(I2C_SLV4_DO);
    _I2C_SLV4_CTRL = readByte(I2C_SLV4_CTRL);
    _I2C_SLV4_DI = readByte(I2C_SLV4_DI);
    _I2C_MST_STATUS = readByte(I2C_MST_STATUS);
    _INT_PIN_CFG = readByte(INT_PIN_CFG);
    _INT_ENABLE = readByte(INT_ENABLE);
    _INT_STATUS = readByte(INT_STATUS);
    _ACCEL_XOUT_H = readByte(ACCEL_XOUT_H);
    _ACCEL_XOUT_L = readByte(ACCEL_XOUT_L);
    _ACCEL_YOUT_H = readByte(ACCEL_YOUT_H);
    _ACCEL_YOUT_L = readByte(ACCEL_YOUT_L);
    _ACCEL_ZOUT_H = readByte(ACCEL_ZOUT_H);
    _ACCEL_ZOUT_L = readByte(ACCEL_ZOUT_L);
    _TEMP_OUT_H = readByte(TEMP_OUT_H);
    _TEMP_OUT_L = readByte(TEMP_OUT_L);
    _GYRO_XOUT_H = readByte(GYRO_XOUT_H);
    _GYRO_XOUT_L = readByte(GYRO_XOUT_L);
    _GYRO_YOUT_H = readByte(GYRO_YOUT_H);


    _GYRO_YOUT_L = readByte(GYRO_YOUT_L);
    _GYRO_ZOUT_H = readByte(GYRO_ZOUT_H);
    _GYRO_ZOUT_L = readByte(GYRO_ZOUT_L);
    _EXT_SENS_DATA_00 = readByte(EXT_SENS_DATA_00);
    _I2C_SLV0_DO = readByte(I2C_SLV0_DO);
    _I2C_SLV1_DO = readByte(I2C_SLV1_DO);
    _I2C_SLV2_DO = readByte(I2C_SLV2_DO);
    _I2C_SLV3_DO = readByte(I2C_SLV3_DO);
    _I2C_MST_DELAY_CTRL = readByte(I2C_MST_DELAY_CTRL);
    _SIGNAL_PATH_RESET = readByte(SIGNAL_PATH_RESET);
    _USER_CTRL = readByte(USER_CTRL);
    _PWR_MGMT_1 = readByte(PWR_MGMT_1);
    _PWR_MGMT_2 = readByte(PWR_MGMT_2);


    _FIFO_COUNTH = readByte(FIFO_COUNTH);
    _FIFO_COUNTL = readByte(FIFO_COUNTL);
    _FIFO_R_W = readByte(FIFO_R_W);
    _WHO_AM_I = readByte(WHO_AM_I);


    Nop();


    writeByte(ACCEL_CONFIG, 0x0);
    writeByte(GYRO_CONFIG, 0x0);

    writeByte(PWR_MGMT_1, 0x1);
    writeByte(FIFO_EN, 0x0);
    writeByte(CONFIG, 0x0);

    writeByte(USER_CTRL, 0x10);





    //rawData[0] = readByte(SELF_TEST_X); 



    MPU6000_Initialized = 1;

    MPU60000_Initializing = 0;



}

void writeByte(unsigned char ADDR, unsigned char Data) {
    HvGyroData = 0;
    Gyro_txBuf[0] = ADDR;
    Gyro_txBuf[1] = Data;
    TxRxSPI_GYRO(2);
    while (!HvGyroData);
    HvGyroData = 0;
}

unsigned char readByte(unsigned char ADDR) {
    HvGyroData = 0;
    Gyro_txBuf[0] = ADDR | 0x80;
    TxRxSPI_GYRO(2);
    while (!HvGyroData);
    HvGyroData = 0;
    return Gyro_rxBuf[1];

}

void SetPWM_ChagerViaMotor() {
    int PWM_ChagerTmp = PWM_Chager;
    int PWM;



    if (CURRENT_PROTECTION) {
        if (PWM_ChagerTmp > (unsigned int) PI_Curr1Res)
            PWM_ChagerTmp = PWM_ChagerTmp - (unsigned int) PI_Curr1Res;
        else
            PWM_ChagerTmp = 0;
    }




    PWM = MAX_PWM - PWM_ChagerTmp;

    //int PWM=MAX_PWM-DIRPWM1;    


    PWM1_A_H = 0;
    PWM1_A_L = 0;
    PWM1_B_H = 0;
    PWM1_B_L = 0;
    PWM1_C_H = 0;
    PWM1_C_L = 0;

#if !defined CHAGER_VIA_MOTOR_VECTOR_M2
    PEN1_A_H = 0;
    PEN1_A_L = 1;
    PEN1_B_H = 0;
    PEN1_B_L = 0;
    PEN1_C_H = 0;
    PEN1_C_L = 0;
#else
    PEN1_A_H = 0;
    PEN1_A_L = 0;
    PEN1_B_H = 0;
    PEN1_B_L = 0;
    PEN1_C_H = 0;
    PEN1_C_L = 1;
#endif

    //if (DIRPWM1<DEADTIME_GLUK)
    if (PWM_Chager < DEADTIME_GLUK) {
        DTR1 = DTR2 = DTR3 = DEADTIME * 2; //DTRx Registers are ignored in this mode
        ALTDTR1 = ALTDTR2 = ALTDTR3 = DEADTIME * 2;
        PWM = PWM + DEADTIME + Khard;
    } else {
        DTR1 = DTR2 = DTR3 = DEADTIME; //DTRx Registers are ignored in this mode
        ALTDTR1 = ALTDTR2 = ALTDTR3 = DEADTIME;
        PWM = PWM + DEADTIME_2 + Khard;

    }



#if !defined CHAGER_VIA_MOTOR_VECTOR_M2    
    PDC1 = PWM;
    PDC2 = 0;
    PDC3 = 0;
#else
    PDC1 = 0;
    PDC2 = 0;
    PDC3 = PWM;
#endif


    PWM1Show = PWM;


}


#if defined CHAGER_VIA_MOTOR_VECTOR_M2

void PI_Chager(void) {
    float ICurr = I_Curr, PWM_Temp = MAX_PWM;
    float IU = I_U;

    if (!ChagerViaMotor)
        return;

    if (!ChargingComplete) {
        IU = IU / 100;


        if (!CV) {
            CurrUstChager = ChagerCurr;
        } else {
            EUChager = UBatHiMem - UBtFl;



            EChagerUSumm = EChagerUSumm + EUChager;
            EiUChager = EChagerUSumm*IU;

            if (EiUChager > ChagerCurr) {
                EiUChager = ChagerCurr;
                EChagerUSumm = ChagerCurr / IU;
            }

            if (EiUChager < 0)
                EiUChager = 0;

            CurrUstChager = EiUChager;
            if (CurrUstChager < (((float) ChagerCurr)*0.1))
                ChargingComplete = 1;


        }


        ICurr = ICurr / 10;

        if (NoChager)
            PWM_Temp = PWM_Temp * 0.3;
        else
            PWM_Temp = PWM_Temp * 0.7;



        DS = 0;


        ECurrChager = Curr1Show + CurrUstChager;
        EpCurrChager = ECurrChager*P_Curr;


        EChagerCurrSumm = EChagerCurrSumm + ECurrChager;
        EiCurrChager = EChagerCurrSumm*ICurr;

        if (EiCurrChager > PWM_Temp) {
            if ((Curr1Show>-5)&&(!CV))
                NoChager = 1;
            else
                NoChager = 0;
            EChagerCurrSumm = PWM_Temp / ICurr;
        }
        if (EiCurrChager < 0)
            EChagerCurrSumm = 0; //-PWM_Temp/ICurr;





        PWM_Chager = EpCurrChager + EiCurrChager;

        if (PWM_Chager > PWM_Temp)
            PWM_Chager = PWM_Temp;
        if (PWM_Chager<-PWM_Temp)
            PWM_Chager = -PWM_Temp;








        if (UBtFl >= UBatHiMem) {
            if (!CV) {
                EChagerUSumm = CurrUstChager / IU;
                CV = 1;
            }
        }
    } else {
        PWM_Chager = 0;
    }


}
#else

void PI_Chager(void) {
    float ICurr = I_Curr, PWM_Temp = MAX_PWM;
    float IU = I_U;

    if (!ChagerViaMotor)
        return;

    if (!ChargingComplete) {
        IU = IU / 100;


        if (!CV) {
            CurrUstChager = ChagerCurr;
        } else {
            EUChager = UBatHiMem - UBtFl;

            EChagerUSumm = EChagerUSumm + EUChager;
            EiUChager = EChagerUSumm*IU;

            if (EiUChager > ChagerCurr) {
                EiUChager = ChagerCurr;
                EChagerUSumm = ChagerCurr / IU;
            }

            if (EiUChager < 0)
                EiUChager = 0;

            CurrUstChager = EiUChager;
            if (CurrUstChager < (((float) ChagerCurr)*0.1))
                ChargingComplete = 1;


        }


        ICurr = ICurr / 10;

        if (NoChager)
            PWM_Temp = 0; //PWM_Temp*0.3;
        else
            PWM_Temp = PWM_Temp * 0.7;



        DS = 0;


        ECurrChager = Curr1Show + CurrUstChager;
        EpCurrChager = ECurrChager*P_Curr;


        EChagerCurrSumm = EChagerCurrSumm + ECurrChager;
        EiCurrChager = EChagerCurrSumm*ICurr;


        if (ChagerIn)
            NoChager = 1;
        else
            NoChager = 0;

        if (PrevNoChager != NoChager) {
            if (NoChager) {
                if (!Sounds)
                    SoundNum = 11;
            } else {
                if (!Sounds)
                    SoundNum = 12;
            }

            PrevNoChager = NoChager;
        }




        if (EiCurrChager > PWM_Temp) {
            EChagerCurrSumm = PWM_Temp / ICurr;
        }
        if (EiCurrChager < 0)
            EChagerCurrSumm = 0; //-PWM_Temp/ICurr;





        PWM_Chager = EpCurrChager + EiCurrChager;

        if (PWM_Chager > PWM_Temp)
            PWM_Chager = PWM_Temp;
        if (PWM_Chager<-PWM_Temp)
            PWM_Chager = -PWM_Temp;








        if (UBtFl >= UBatHiMem) {
            if (!CV) {
                EChagerUSumm = CurrUstChager / IU;
                CV = 1;
            }
        }
    } else {
        PWM_Chager = 0;
    }


}
#endif

void TrmControls_U3(void) {
    unsigned int CntBt = 4;

    //return;

    if (MustTrm_U3)
        return;

    if (OnTransmitt_U3)
        return;


    TrmMass_U3[0] = 0xff;
    TrmMass_U3[1] = 0xff;
    TrmMass_U3[2] = 1;
    TrmMass_U3[3] = 1; //COMMAND

    TrmMass_U3[CntBt] = 0;

    if (But1)
        TrmMass_U3[CntBt] = TrmMass_U3[CntBt] | 0x01;
    if (But2)
        TrmMass_U3[CntBt] = TrmMass_U3[CntBt] | 0x02;
    if (But3)
        TrmMass_U3[CntBt] = TrmMass_U3[CntBt] | 0x04;
    if (But4)
        TrmMass_U3[CntBt] = TrmMass_U3[CntBt] | 0x08;
    if (Break)
        TrmMass_U3[CntBt] = TrmMass_U3[CntBt] | 0x10;
    if (Monocycle)
        TrmMass_U3[CntBt] = TrmMass_U3[CntBt] | 0x20;
    if (NoBalance)
        TrmMass_U3[CntBt] = TrmMass_U3[CntBt] | 0x40;

    CntBt++;

    TrmMass_U3[CntBt++] = ADCThrottle;
    TrmMass_U3[CntBt++] = ADCThrottle >> 8;


    TrmMass_U3[CntBt++] = ADCThrottleBreak;
    TrmMass_U3[CntBt++] = ADCThrottleBreak >> 8;

    TrmMass_U3[CntBt++] = PWM2;
    TrmMass_U3[CntBt++] = PWM2 >> 8;




    TrmMass_U3[2] = CntBt - 3;

    TrmMass_U3[CntBt++] = CalcCheckSumm(TrmMass_U3[2] + 1, &TrmMass_U3[2]);

    MustTrm_U3 = 1;
}

void U4_9600_On(void) {
    unsigned int CntBt = 4;

    //return;

    if (MustTrm_U3)
        return;

    if (OnTransmitt_U3)
        return;


    TrmMass_U3[0] = 0xff;
    TrmMass_U3[1] = 0xff;
    //TrmMass_U3[2]=1;
    TrmMass_U3[3] = 57; //COMMAND

    TrmMass_U3[CntBt++] = 0;
    TrmMass_U3[CntBt++] = 0x73;
    TrmMass_U3[CntBt++] = 0xb2;
    TrmMass_U3[CntBt++] = SerNumber;
    TrmMass_U3[CntBt++] = SerNumber >> 8;

    TrmMass_U3[2] = CntBt - 3;

    TrmMass_U3[CntBt++] = CalcCheckSumm(TrmMass_U3[2] + 1, &TrmMass_U3[2]);

    MustTrm_U3 = 1;
}


unsigned char BreakFunc(void) {
    if (_2WDMode == 2)
        return (unsigned char) SlaveBreak;
    else
        return (unsigned char) (!Break1);
}

void ClbrJOYSTICK(void) {
    if (!CalibrateJOYSTICK)
        return;

    if (!HvADC1)
        return;

    HvADC1 = 0;

    ADCThrottleSumm = ADCThrottleSumm + ADCThrottle;
    ADCThrottleBreakSumm = ADCThrottleBreakSumm + ADCThrottleBreak;
    CntCalibrateJOYSTICK++;
    if (CntCalibrateJOYSTICK >= 64) {
        JoystickCalibrX = ADCThrottleSumm >> 6;
        JoystickCalibrY = ADCThrottleBreakSumm >> 6;
        CalibrateJOYSTICK = 0;
        OptionsToMass();
        MustTrmFlashMass = 1;

    }


}

void LSM6DS33_Init(void) {
    writeByteLSM6DS33(0x18, 0x38);
    writeByteLSM6DS33(0x10, 0x60);
    writeByteLSM6DS33(0x19, 0x38);
    writeByteLSM6DS33(0x11, 0x60);



    LSM6DS33_Initialized = 1;

}

unsigned char readByteLSM6DS33(unsigned char ADDR) {

    HvGyroData = 0;
    Gyro_txBuf[0] = ADDR | 0x80;
    TxRxSPI_GYRO(2);
    while (!HvGyroData);
    HvGyroData = 0;

    return Gyro_rxBuf[1];

}

void readBytesLSM6DS33(unsigned char ADDR, unsigned char N) {

    HvGyroData = 0;
    Gyro_txBuf[0] = ADDR | 0x80;
    TxRxSPI_GYRO(N);
    while (!HvGyroData);
    HvGyroData = 0;


}

void writeByteLSM6DS33(unsigned char ADDR, unsigned char Data) {
    HvGyroData = 0;
    Gyro_txBuf[0] = ADDR; //Addr | autoincrement
    Gyro_txBuf[1] = Data;
    TxRxSPI_GYRO(2);
    while (!HvGyroData);
    HvGyroData = 0;
}

void LighrSensorFunc(void) {
    if (!LightOn&&!KeyLightStop&&!KeyLightStopGabarit)
        return;

    if (!KeyLightStop&&!KeyLightStopGabarit) {
        switch (LightMode) {
            case 0:
#if !defined VECTORS
                Horn = 0;
#else
                //Horn=1;

                OC3R = ((unsigned int) KeyLightBrightness) << 8;

#endif
                break;
            case 1:
#if !defined VECTORS
                Horn = 1;
#else
                //Horn=0;
                OC3R = 0;
#endif
                break;
            case 2:

                if (LightSensor > LightSensorThresholdLo)
#if !defined VECTORS
                    Horn = 0;
#else
                    //Horn=1;
                    OC3R = ((unsigned int) KeyLightBrightness) << 8;
#endif

                if (LightSensor < LightSensorThresholdHi)
#if !defined VECTORS
                    Horn = 1;
#else
                    //Horn=0;
                    OC3R = 0;
#endif

                break;
        }
    } else {
        if (!KeyLightStopGabarit) {
            if (StpLightsNew) {
                if (!MigStop)
#if defined VECTORS
                    OC3R = ((unsigned int) KeyLightBrightness) << 8;
#else
                    Horn = 0;
#endif
                else {
                    if (!CntMigStop) {
                        CntMigStop = CntMigStopConst;
#if defined VECTORS
                        if (OC3R == 0)
                            OC3R = ((unsigned int) KeyLightBrightness) << 8;
                        else
                            OC3R = 0;
#else
                        if (Horn)
                            Horn = 0;
                        else
                            Horn = 1;

#endif
                    }
                }
            } else {
#if defined VECTORS
                OC3R = 0;
#else
                Horn = 1;
#endif
                CntMigStop = CntMigStopConst;
            }
        } else {
            if (StpLightsNew) {
                if (!MigStop)
                    OC3R = 0xffff;
                else {
                    if (!CntMigStop) {
                        CntMigStop = CntMigStopConst;
                        if (OC3R == 0)
                            OC3R = 0xffff;
                        else
                            OC3R = 0;
                    }

                }
            } else {
                CntMigStop = CntMigStopConst;
                OC3R = ((unsigned int) KeyLightBrightness) << 8;
            }

        }
    }
}

void CriticalErrorLed(void) {


    switch (CriticalErrorLedStateMachine) {
        case 0:
            if (CriticalError) {
                CriticalErrorLedStateMachine = 1;
                CntCriticalErrorLed = CriticalError - 1;
                ALARM_LED = 1;
                MODE_LED_Cnt = 100;
            }
            break;
        case 1:
            if (MODE_LED_Cnt)
                return;
            ALARM_LED = 0;
            MODE_LED_Cnt = 150;
            CriticalErrorLedStateMachine = 2;
            break;
        case 2:
            if (MODE_LED_Cnt)
                return;
            if (CntCriticalErrorLed) {
                CntCriticalErrorLed--;
                CriticalErrorLedStateMachine = 1;
                ALARM_LED = 1;
                MODE_LED_Cnt = 100;
            } else {
                MODE_LED_Cnt = 500;
                CriticalErrorLedStateMachine = 3;
            }



            break;
        case 3:
            if (MODE_LED_Cnt)
                return;
            CriticalErrorLedStateMachine = 0;
            break;

    }



}

void WheelingFunc(void) {
    switch (WheelingStateMachine) {
        case 0:
            break;
        case 1:
            if (!Monocycle) {
                NoBalance = 0;
                RotAddSumm = 0;
                SoundNum = 1;
                //ESumm=((float)PWM1Temp)/Ki;
                PWM1TempPreWheeling = PWM1Temp;
                Monocycle = 1;
                NoBalance = 1;
                WheelingNew = 1;

                ESumm = 0;
                TiltZadAddMustBe = 0;
                StrongMode = 1;




                WheelingStateMachine = 2;
            } else
                WheelingStateMachine = 0;
            break;
        case 2:
            if (NoBalance) {
                PWM1Temp = PWM1TempPreWheeling;

                //                         SpeedControl=1;
                //                       ECurr1Summ=0;
                //                     CurrentControlOnly=0;

                //                           SpeedControl=1;
                ECurr1Summ = 0;
                ESumm = ((float) PWM1Temp) / Ki;
                //                             CurrentControlOnly=1;
            } else
                WheelingStateMachine = 3;

            break;

        case 3:
            if (NoBalance) {
                if (StrongModeMem)
                    StrongMode = 1;
                else
                    StrongMode = 0;

                Monocycle = 0;
                NoBalance = 1;
                ECurr1Summ = 0;
                ESumm = 0;
                WheelingNew = 0;
                WheelingStateMachine = 0;
                LeftTurn = 0;
                RightTurn = 0;
                SoundNum = 10;

            }
            break;
        case 4:
            if (WheelingNew) {
                if (StrongModeMem)
                    StrongMode = 1;
                else
                    StrongMode = 0;

                Monocycle = 0;
                NoBalance = 1;
                ECurr1Summ = 0;
                WheelingNew = 0;
                ESumm = 0;
                LeftTurn = 0;
                RightTurn = 0;
                WheelingStateMachine = 0;
                SoundNum = 10;
            } else
                WheelingStateMachine = 0;
            break;
    }
}

void InitOC1(void) {
    OC1CON1 = 0;
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 0x07;
    OC1R = 0;
    OC1RS = 0xffff;
    OC1CON2bits.SYNCSEL = 0x1F;
    OC1CON1bits.OCM = 6;

    /*


    OC1CON1bits.OCSIDL=1;
    OC1R=1;
    OC1RS=2;//Min -> 2   Max -> 8007
    OC1CON2bits.OCTRIG=1;

    IEC0bits.OC1IE=0;//????????? ??????????
    IPC0bits.OC1IP=2;

    OC1CON2bits.SYNCSEL=0xd;
    OC1CON1bits.TRIGMODE=1;
    OC1CON1bits.OCM=7;//3;
     */


    RPOR2bits.RP68R = 0b010000;



    IEC0bits.OC1IE = 0; //????????? ??????????
    //IPC0bits.OC1IP=2;



}

void __attribute__((interrupt, auto_psv)) _OC1Interrupt() {
    if (IFS0bits.OC1IF)
        IFS0bits.OC1IF = 0;
    //IEC1bits.OC4IE=0;
    //RightPort=!RightPort;
}

void InitOC2(void) {
    OC2CON1 = 0;
    OC2CON2 = 0;
    OC2CON1bits.OCTSEL = 0x07;
    OC2R = 0;
    OC2RS = 0xffff;
    OC2CON2bits.SYNCSEL = 0x1F;
    OC2CON1bits.OCM = 6;



    RPOR2bits.RP69R = 0b010001;



    IEC0bits.OC2IE = 0; //????????? ??????????
    IPC1bits.OC2IP = 2;



}

void InitOC3(void) {
    OC3CON1 = 0;
    OC3CON2 = 0;
    OC3CON1bits.OCTSEL = 0x07;
    OC3R = 0;
    OC3RS = 0xffff;
    OC3CON2bits.SYNCSEL = 0x1F;
    OC3CON1bits.OCM = 6;



    RPOR7bits.RP97R = 0b010010;



    IEC1bits.OC3IE = 0; //????????? ??????????
    IPC6bits.OC3IP = 2;



}

void StartCharging(void) {
    if (Spd1Res == 0) {
        if (SIN_MIDDLE) {

            SIN_MIDDLE = 0;
            if ((!Sensorless) && VectorMem && Vector) {
                if (StrongModeMem)
                    StrongMode = 1;
                else
                    StrongMode = 0;

                RdSensors();
                Amplitude1 = PDC1;
                VectorInit();
            }
        }

        if ((PWMkHz != 1) || PWM10kHzTmp) {
            PWMkHzTmp = PWMkHz;
            PWMkHz = 1;
            PWM10kHzTmp = 1;
            MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
            MAX_PWM = MAX_PWM_CONST;
            PHASE1 = MAX_PWM + DEADTIME + Khard;
            PHASE2 = MAX_PWM + DEADTIME + Khard;
            PHASE3 = MAX_PWM + DEADTIME + Khard;
        } else
            PWM10kHzTmp = 0;


        NoChager = 1;
        ChagerViaMotor = 1;
        EChagerCurrSumm = EChagerUSumm = 0;
        DirectControlMotor = 1;
        ChargingComplete = 0;
        DS = 1;
        CV = 0;
        DIRPWM1 = 0;
        Sensor1_Prev = Sensor1;
        Phases1();
        OptionsToMass();
        MustTrmFlashMass = 1;
        SoundNum = 22;
    } else {
        SoundNum = 9;
    }

}

void StopCharging(void) {
    SoundNum = 19;
    ChagerViaMotor = 0;
    EChagerCurrSumm = EChagerUSumm = 0;
    DirectControlMotor = 0;
    DS = 1;
    PDC1 = 0;
    DIRPWM1 = 0;
    NullPtr = 1;
    NullPtrRot = 1;

    if (PWM10kHzTmp) {
        PWMkHz = PWMkHzTmp;

        switch (PWMkHz) {
            case 1:
                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
                break;
            case 2:
                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE10kHz;
                TrapezoidaWhenBigSpeed = 1;
                if (VectorOnOffSpdLo > Trapezium10kHzLo)
                    VectorOnOffSpdLo = Trapezium10kHzLo;
                if (VectorOnOffSpdHi > Trapezium10kHzHi)
                    VectorOnOffSpdHi = Trapezium10kHzHi;
                break;
            case 3:
                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE5kHz;
                TrapezoidaWhenBigSpeed = 1;
                if (VectorOnOffSpdLo > Trapezium5kHzLo)
                    VectorOnOffSpdLo = Trapezium5kHzLo;
                if (VectorOnOffSpdHi > Trapezium5kHzHi)
                    VectorOnOffSpdHi = Trapezium5kHzHi;
                break;
            default:
                MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE;
                PWMkHz = 1;
                break;
        }



        MAX_PWM_CONST = MAX_PWM_CONST_MONOCYCLE10kHz;
        MAX_PWM = MAX_PWM_CONST;
        PHASE1 = MAX_PWM + DEADTIME + Khard;
        PHASE2 = MAX_PWM + DEADTIME + Khard;
        PHASE3 = MAX_PWM + DEADTIME + Khard;
        PWM32Bits = 1;
    }



    if (Monocycle) {
        ESumm = 0;
        NoBalance = 1;
        DS = 1;
    }
    NoBalanceCode = 4;
    OptionsToMass();
    MustTrmFlashMass = 1;

}

void FindGyroVerticalFunc(void) {
    if (!FindGyroVertical)
        return;
    FindGyroVertical = 0;
    GyroVertical = 0;
    if ((AccXFl > 10000) || (AccXFl<-10000)) {
        GyroVertical = 2;
    }
    if ((AccYFl > 10000) || (AccYFl<-10000)) {
        GyroVertical = 1;
    }
    if ((AccZFl > 10000) || (AccZFl<-10000)) {
        GyroVertical = 3;
    }
    OptionsToMass();
    MustTrmFlashMass = 1;
}

void SegAll(void) {
    long int UstRot;
    float ERot;
    int DiffHighSpeed;
    float StartRotDiff;
    int TmpInt, Spd1ResPlusTmp;


    //PWM1=0;



    if (StartRot > DeadZoneHandleBarSegwayMustBe)
        StartRot = StartRot - 0.1;
    if (StartRot < DeadZoneHandleBarSegwayMustBe)
        StartRot = StartRot + 0.1;

    if (KRot > KRotMustBe)
        KRot = KRot - 1;
    if (KRot < KRotMustBe)
        KRot = KRot + 1;

    if (Spd1ResPlus <= GoalSpeedImp)
        Spd1ResPlusTmp = Spd1ResPlus;
    else
        Spd1ResPlusTmp = GoalSpeedImp;

    TmpInt = Spd1ResPlusTmp - (int) HighSpeedImp;

    if (TmpInt > 0) {
        DiffHighSpeed = GoalSpeedImp - HighSpeedImp;
        StartRotDiff = ((float) StartRotHighSpeed) - StartRot;
        StartRotDiff = StartRotDiff / ((float) DiffHighSpeed);
        StartRot1 = StartRot + Round(StartRotDiff * (float) TmpInt);

        StartRotDiff = ((float) KRotHighSpeed) - KRot;
        StartRotDiff = StartRotDiff / ((float) DiffHighSpeed);
        KRot1 = KRot + Round(StartRotDiff * (float) TmpInt);


    } else {
        StartRot1 = StartRot;
        KRot1 = KRot;
    }


    if (KpRot > KpRotMustBe)
        KpRot = KpRot - 0.0005;
    if (KpRot < KpRotMustBe)
        KpRot = KpRot + 0.0005;




    if (KiRot > KiRotMustBe)
        KiRot = KiRot - 0.00002;
    if (KiRot < KiRotMustBe)
        KiRot = KiRot + 0.00002;



    float TiltYRes = AlfaXRes;



    switch (GyroVertical) {
        case 1:
            GZFTemp = GyroXFl;
            break;
        case 2:
            GZFTemp = GyroYFl;
            break;
        case 3:
            GZFTemp = GyroZFl;
            break;
        default:
            GZFTemp = 0;
            break;
    }




    if (TiltYRes >= 0) {
        if (TiltYRes > StartRot1)
            TiltYRes = TiltYRes - StartRot1;
        else
            TiltYRes = 0;
    } else {
        if (TiltYRes < (-StartRot1))
            TiltYRes = TiltYRes + StartRot1;
        else
            TiltYRes = 0;
    }

    UstRot = (long int) (TiltYRes * KRot1);




    if (UstRot<-25000)
        UstRot = -25000;
    if (UstRot > 25000)
        UstRot = 25000;


    ERot = GZFTemp - (float) UstRot;

    RotAddP = (int) (((float) ERot) * KpRot);

    if (RotAddP > MAX_PWM)
        RotAddP = MAX_PWM;
    if (RotAddP<-MAX_PWM)
        RotAddP = -MAX_PWM;

    RotAddSumm = RotAddSumm + ERot;

    RotAddI = (int) (((float) RotAddSumm) * KiRot);

    if (RotAddI > MAX_PWM) {
        RotAddI = MAX_PWM;
        RotAddSumm = RotAddI / KiRot;
    }
    if (RotAddI<-MAX_PWM) {
        RotAddI = -MAX_PWM;
        RotAddSumm = RotAddI / KiRot;
    }


    //        RotAdd=RotAddP+RotAddI;

    if ((PWM1 > 400) || (PWM1<-400))
        Nop();


    PWM2 = PWM1 - RotAddP - RotAddI;
    PWM1 = PWM1 + RotAddP + RotAddI;


    if (PWM1 > MAX_PWM)
        PWM1 = MAX_PWM;
    if (PWM1<-MAX_PWM)
        PWM1 = -MAX_PWM;

    if (PWM2 > MAX_PWM)
        PWM2 = MAX_PWM;
    if (PWM2<-MAX_PWM)
        PWM2 = -MAX_PWM;




}

void HighSpeedQuantum(void) {

    HighSpeedImp = (int) ((float) HighSpeed / ImpToKmH1_t);
    GoalSpeedImp = (int) ((float) GoalSpeed / ImpToKmH1_t);
}

int Round(float Fl) {
    int TmpI;
    if (Fl >= 0) {
        if ((Fl - (float) ((int) Fl)) >= 0.5) {
            TmpI = (int) Fl;
            if (((float) TmpI) < Fl)
                return (TmpI + 1);
            else
                return (int) (Fl);
        } else
            return (int) Fl;
    } else {
        if ((Fl - (float) ((int) Fl)) <= -0.5)
            TmpI = (int) Fl;
        if (((float) TmpI) > Fl)
            return (TmpI - 1);
        else
            return (int) (Fl);
    }




}

void CurrentProtectionPID(void) {
    CurrUstTmpPID = ((long int) CurrPhaseLimit * (long int) PhasePWM) / ((long int) MAX_PWM_CONST);

    if ((CurrUstTmpPID > CurrUst) || (CurrUstTmpPID <= 200))
        CurrUstTmpPID = CurrUst;

    if (Curr1 > CurrUstTmpPID) {
        if (!SensorlessNotBEMF)
            if (!StartCnt) {
                CurrProtectSoundCnt++;
                if (CurrProtectSoundCnt > 10) {
                    CurrProtectSoundCnt = 0;
                    if ((Spd1ResPlus <= 5)&&(!Monocycle)) {
                        if ((Spd0TimerStateMachineCnt == 0)&&(Curr1Show > CurrUstTmpPID)) {
                            Spd0TimerStateMachineCnt = 1;
                            if (!AutoNastroykaState)
                                Spd0Timer = Spd0TimerConst;
                            else
                                Spd0Timer = 10000;
                        }
                    }
                    if (CurrLimitSound)
                        SoundNum = 1;
                }
            }
        ECurr1PID = Curr1 - CurrUstTmpPID;
        EpCurr1PID = ECurr1PID*KpCurr;
        ECurr1SummPID = ECurr1SummPID + (float) ECurr1PID*KiCurr;
        if (ECurr1SummPID > MAX_PWM)
            ECurr1SummPID = MAX_PWM;
    } else {
        EpCurr1PID = 0;
        if (ECurr1SummPID > 0) {
            ECurr1PID = CurrUstTmpPID - Curr1;
            ECurr1SummPID = ECurr1SummPID - ((float) ECurr1PID * KiCurr);
            if (ECurr1SummPID < 0)
                ECurr1SummPID = 0;
        } else {
            ECurr1SummPID = 0;
        }
    }
    PI_Curr1ResPID = (unsigned long int) ECurr1SummPID + (unsigned long int) EpCurr1PID + PI_Temperature;
    if (PI_Curr1ResPID > MAX_PWM)
        PI_Curr1ResPID = MAX_PWM;
}

void PWM100StateMachine(void) {
    long int PWMTmp = PWM1Temp;

    if (PWMTmp < 0)
        PWMTmp = -PWMTmp;

    switch (PWM100StateMachineCnt) {
        case 0:
            if (PWMTmp == MAX_PWM)
                if (PWM1TempPrev != MAX_PWM) {
                    PWM100StateMachineCnt = 1;
                    StopIfPWM100TimeCnt = ((int) StopIfPWM100Time)*250;
                }
            break;
        case 1:
            if (StopIfPWM100TimeCnt) {
                SoundNum = 24;
                StopIfPWM100TimeCnt--;
                if (!StopIfPWM100TimeCnt) {
                    StrongMode = 0;
                    DS = 1;
                    NoBalance = 1;
                    OnDelayCnt = OnDelayConst;
                    PWM100StateMachineCnt = 0;
                }
            }
            if (PWMTmp != MAX_PWM)
                PWM100StateMachineCnt = 0;

            break;

        default:
            PWM100StateMachineCnt = 0;
            break;

    }
    PWM1TempPrev = PWMTmp;
}


