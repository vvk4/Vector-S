using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ControlBalance
{
    public partial class Form2 : Form
    {

        public Form1 frm;
        int AutoNastroykaStatePrev = 0, Cnt = 0;

        MyDelegate d;
        public Form2(MyDelegate sender)
        {


   //         System.Threading.Thread.CurrentThread.CurrentUICulture = System.Globalization.CultureInfo.GetCultureInfo("en-US");
  //          System.Threading.Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.GetCultureInfo("en-US");







            InitializeComponent();
            d = sender;
            backgroundWorker1.RunWorkerAsync();
            frm = (Form1)this.Owner;

/*            textBoxDescription.AppendText("--------  Старт автонастройки  ---------- " + Environment.NewLine);
            textBoxDescription.AppendText(Environment.NewLine);
            textBoxDescription.AppendText(Environment.NewLine);
            textBoxDescription.AppendText("Включение режима: " + Environment.NewLine);
            textBoxDescription.AppendText("Векторный, жесткий, ШИМ = 20кГц, ток ограничен " + Environment.NewLine);
            textBoxDescription.AppendText(Environment.NewLine);
            */
            frm = (Form1)this.Owner;
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button49_Click(object sender, EventArgs e)
        {


            


        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            frm = (Form1)this.Owner;
            int r = frm.AutoNastroykaState;
            int InvSin = frm.StatFlags2 & 0x8000;
            byte SnsOrder = frm.SensOrder1;
            uint TestSIN_Ok = frm.Flgs3 & 0x40000;
            String SnsOrderStr;









            switch (SnsOrder)
            {
                case 0:
                    SnsOrderStr = "1: ABC";
                    break;
                case 1:
                    SnsOrderStr = "2: BAC";
                    break;
                case 2:
                    SnsOrderStr = "3: BCA";
                    break;
                case 3:
                    SnsOrderStr = "4: ACB";
                    break;
                case 4:
                    SnsOrderStr = "5: CAB";
                    break;
                case 5:
                    SnsOrderStr = "6: CBA";
                    break;
                default:
                    SnsOrderStr = "-----";
                    break;
            }





            if (AutoNastroykaStatePrev != r)
            {
                switch (r)
                {
                    case 1:
                        //                        textBoxDescription.AppendText("Включение режима: " + Environment.NewLine);
                        //                      textBoxDescription.AppendText("Векторный, жесткий, ШИМ = 20кГц, ток ограничен " + Environment.NewLine);

                        break;
                    case 2:
                        textBoxDescription.AppendText(MyStrings.Stopping + Environment.NewLine);
                        break;
                    case 4:
                        textBoxDescription.AppendText(MyStrings.CurrSenorCalibrate + Environment.NewLine);
                        break;
                    case 6:
                        textBoxDescription.AppendText(Environment.NewLine);
                        if (InvSin == 0)
                            textBoxDescription.AppendText("Phase - " + SnsOrderStr + " Inv. SVPWM = " + "0" + Environment.NewLine);
                        else
                            textBoxDescription.AppendText("Phase - " + SnsOrderStr + " Inv. SVPWM = " + "1" + Environment.NewLine);
                        break;
                    case 9:
                        if (TestSIN_Ok == 0)
                            textBoxDescription.AppendText(MyStrings.ResultUnsuccessful + Environment.NewLine);
                        else
                            textBoxDescription.AppendText(MyStrings.ResultOK + Environment.NewLine);

                        break;
                    case 13:
                        if (TestSIN_Ok == 0)
                            textBoxDescription.AppendText(MyStrings.ResultUnsuccessful + Environment.NewLine);
                        else
                            textBoxDescription.AppendText(MyStrings.ResultOK + Environment.NewLine);

                        break;


                    case 254:
                        textBoxDescription.AppendText(MyStrings.OrderNotDetected + Environment.NewLine);
                        MessageBox.Show(MyStrings.OrderNotDetectedMSG, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                        break;





                }




                AutoNastroykaStatePrev = r;
            }


        }




        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {

            /*frm = (Form1)this.Owner;
            int r = frm.AutoNastroykaState;
            bool bl = frm.AutoNastroykaFl;

    */
            while (true)
            {
                
                System.Threading.Thread.Sleep(1);
                    
                if (Class1.bl)
                {
                    Class1.bl = false;
                    backgroundWorker1.ReportProgress(1);
                    d(1);
                }
            }
            


        }

        private void button1_Click(object sender, EventArgs e)
        {
            d(7);
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBoxDescription.Clear();
        }

        private void button3_Click(object sender, EventArgs e)
        {


            DialogResult result = MessageBox.Show(MyStrings.RestartQ, MyStrings.Inform, MessageBoxButtons.YesNo, MessageBoxIcon.Question);


            if (result == DialogResult.Yes)
                d(8);





        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            String SnsOrderStr;
            DialogResult result;
            /*frm = (Form1)this.Owner;
            int r = frm.AutoNastroykaState;
            switch (e.ProgressPercentage)
            {

                case 1:
                    textBoxDescription.AppendText(r.ToString() + Environment.NewLine);
                    break;
            }*/



            switch (Class1.SensOrder1)
            {
                case 0:
                    SnsOrderStr = "1: ABC";
                    break;
                case 1:
                    SnsOrderStr = "2: BAC";
                    break;
                case 2:
                    SnsOrderStr = "3: BCA";
                    break;
                case 3:
                    SnsOrderStr = "4: ACB";
                    break;
                case 4:
                    SnsOrderStr = "5: CAB";
                    break;
                case 5:
                    SnsOrderStr = "6: CBA";
                    break;
                default:
                    SnsOrderStr = "-----";
                    break;
            }



            //            textBoxDescription.AppendText(Class1.CntAutoNastroykaState257.ToString() + Environment.NewLine);


            /*


                        switch (Class1.AutoNastroykaState)
                        {
                            case 1:
                                textBoxDescription.AppendText("--------  Старт автонастройки  ---------- " + Environment.NewLine);
                                textBoxDescription.AppendText(Environment.NewLine);
                                textBoxDescription.AppendText(Environment.NewLine);
                                textBoxDescription.AppendText("Включение режима: " + Environment.NewLine);
                                                      textBoxDescription.AppendText("Векторный, обычный, фильтр отключен, режим моноцикла выключен, частота ШИМ = 20кГц, ток ограничен " + Environment.NewLine);
                                textBoxDescription.AppendText(Environment.NewLine);
                                textBoxDescription.AppendText(Environment.NewLine);

                                break;
                            case 2:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Остановка..." + Environment.NewLine);
                                break;
                            case 3:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Калибровка датчика тока . . . ");
                                textBoxDescription.AppendText(Environment.NewLine);
                                break;
                            case 4:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Калибровка датчика тока закончена. ");
                                textBoxDescription.AppendText(Environment.NewLine);
                                break;
                            case 5:
                                textBoxDescription.AppendText(Environment.NewLine);
                                if (Class1.InvSin == 0)
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Фазы - " + SnsOrderStr + " Инв. SVPWM = " + "0" + Environment.NewLine);
                                 else
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Фазы - " + SnsOrderStr + " Инв. SVPWM = " + "1" + Environment.NewLine);
                                break;

                            case 6:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Задержка 1 сек." + Environment.NewLine);
                                break;

                            case 7:
                                if (Class1.TestSIN_Ok == 0)
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Результат: неудачный" + Environment.NewLine);
                                else
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Результат: ---OK---" + Environment.NewLine);

                                break;
                            case 8:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Остановка" + Environment.NewLine);
                                break;

                            case 10:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + Environment.NewLine);
                                break;


                            case 11:
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Обнаружено рабочих комбинаций: " + Class1.TestSINOkMassCnt.ToString() + Environment.NewLine);
                                    textBoxDescription.AppendText("Определение оптимальной..."  + Environment.NewLine);
                                    textBoxDescription.AppendText(Environment.NewLine);
                                    textBoxDescription.AppendText(Environment.NewLine);
                                break;


                            case 12:
                                if (Class1.InvSin == 0)
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Фазы - " + SnsOrderStr + " Инв. SVPWM = " + "0" + Environment.NewLine);
                                else
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Фазы - " + SnsOrderStr + " Инв. SVPWM = " + "1" + Environment.NewLine);
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": Увеличение ШИМ..." );
                                textBoxDescription.AppendText(Environment.NewLine);
                                break;

                            case 14:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": Скважность ШИМ увеличена" );
                                textBoxDescription.AppendText(Environment.NewLine);
                                break;

                            case 15:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": Задержка. +++   " + Class1.Curr1SnTST);
                                textBoxDescription.AppendText(Environment.NewLine);
                                break;



                            case 16:
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": Остановка");
                                    textBoxDescription.AppendText(Environment.NewLine);

                                break;



                            case 17:
                                textBoxDescription.AppendText(Environment.NewLine);
                                if (Class1.InvSin == 0)
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Определен рабочий порядок фаз: " + Environment.NewLine + "-->" +SnsOrderStr + " Инв. SVPWM = " + "0 <--" + Environment.NewLine);
                                else
                                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Определен рабочий порядок фаз: " + Environment.NewLine + "--> " + SnsOrderStr + " Инв. SVPWM = " + "1 <--" + Environment.NewLine);
                                textBoxDescription.AppendText(Environment.NewLine);
                                    textBoxDescription.AppendText(Environment.NewLine);
                                  //  textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Оптимизация фазового сдвига... " + Environment.NewLine);

                                break;

                            case 18:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": Остановка" + Environment.NewLine);
                                break;

                            case 20:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": Скважность ШИМ увеличена" + Environment.NewLine);
                                break;

                            case 21:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + Class1.Curr1SnTST_0.ToString() + Environment.NewLine);
                                break;

                            case 22:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": Сдвиг фазы: " + Class1.Curr1SnTST.ToString() + Environment.NewLine);
                                break;


                            case 23:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + Class1.Curr1SnTST_0.ToString() + " - " + Class1.Curr1SnTST.ToString() + Environment.NewLine);

                                break;


                            case 27:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Нижний порог ручки газа: " + Class1.SensorThresholdDn.ToString() + Environment.NewLine);
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Нижний порог ручки тормоза: " + Class1.BreakThresholdDn.ToString() + Environment.NewLine);
                                DialogResult result = MessageBox.Show("Нажмите ручку газа до упора и выберите ОК, для пропуска выберите NO", "Информация", MessageBoxButtons.YesNo, MessageBoxIcon.Question);


                                if (result == DialogResult.Yes)
                                {
                                    d(2);
                                }
                                else
                                {
                                    d(3);
                                }
                                break;

                            case 29:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Верхний порог ручки газа: " + Class1.SensorThresholdUp.ToString() + Environment.NewLine);
                                result = MessageBox.Show("Нажмите ручку тормоза до упора и выберите ОК, для пропуска выберите NO", "Информация", MessageBoxButtons.YesNo, MessageBoxIcon.Question);


                                if (result == DialogResult.Yes)
                                {
                                    d(4);
                                }
                                else
                                {
                                    d(5);
                                }
                                break;


                            case 30:
                                result = MessageBox.Show("Нажмите ручку тормоза до упора и выберите ОК, для пропуска выберите NO", "Информация", MessageBoxButtons.YesNo, MessageBoxIcon.Question);


                                if (result == DialogResult.Yes)
                                {
                                    d(4);
                                }
                                else
                                {
                                    d(5);
                                }
                                break;





                            case 31:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Верхний порог ручки тормоза: " + Class1.BreakThresholdUp.ToString() + Environment.NewLine);
                                break;

                            case 32:
                                textBoxDescription.AppendText(Environment.NewLine);
                                textBoxDescription.AppendText(Environment.NewLine);
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Автонастройка завершена" + Environment.NewLine);
                                MessageBox.Show("Настройка закончена, не забудьте сохранить их в памяти.", "Информация", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                d(6);
                                break;




                            case 254:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Рабочие комбинации фаз не обнаружены" + Environment.NewLine);
                                MessageBox.Show("Не обнаружены рабочие комбинации фаз. Проверьте проводку или попробуйте настроить вручную.", "Ошибка", MessageBoxButtons.OK);
                                break;

                            case 255:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Ошибка 255. Произведите настройку сдвига фаз вручную" + Environment.NewLine);
                                MessageBox.Show("Ошибка 255. Произведите настройку сдвига фаз вручную", "Ошибка", MessageBoxButtons.OK);
                                break;

                            case 256:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Ошибка 256. Произведите настройку сдвига фаз вручную" + Environment.NewLine);
                                MessageBox.Show("Ошибка 256. Произведите настройку сдвига фаз вручную", "Ошибка", MessageBoxButtons.OK);
                                break;


                            default:
                                textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + Environment.NewLine);
                                break;


                        }

                        */

            Cnt++;


            switch (Class1.AutoNastroykaState)
            {
                case 1:
                    textBoxDescription.AppendText(MyStrings.StartingAutosettings + Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText("Set mode" + Environment.NewLine);
                    textBoxDescription.AppendText(MyStrings.VectorMode + Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);

                    textBoxDescription.AppendText(Cnt.ToString() + ": " + "U_BAT = " + Class1.UBT_V + Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + "PWM = " + Class1.PWM1_SIN_TST + Environment.NewLine);

                    textBoxDescription.AppendText(Environment.NewLine);



                    break;
                case 2:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.Stopping + Environment.NewLine);
                    break;
                case 3:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.CurrSenorCalibrate);
                    textBoxDescription.AppendText(Environment.NewLine);
                    break;
                case 4:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.CurrSenorCalibrateFinished);
                    textBoxDescription.AppendText(Environment.NewLine);
                    d(13);
                    break;
                case 5:
                    textBoxDescription.AppendText(Environment.NewLine);
                    if (Class1.InvSin == 0)
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + "Phases - " + SnsOrderStr + " Inv. SVPWM = " + "0" + Environment.NewLine);
                    else
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + "Phases - " + SnsOrderStr + " Inv. SVPWM = " + "1" + Environment.NewLine);
                    break;

                case 6:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.Delay1s + Environment.NewLine);
                    break;

                case 7:
                    if (Class1.TestSIN_Ok == 0)
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.ResultUnsuccessful + Environment.NewLine);
                    else
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.ResultOK + Environment.NewLine);

                    break;
                case 8:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.Stopping + Environment.NewLine);
                    break;

                case 10:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + Environment.NewLine);
                    break;


                case 11:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.FoundOrders + Class1.TestSINOkMassCnt.ToString() + Environment.NewLine);
                    textBoxDescription.AppendText(MyStrings.FindingOptimal + Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    break;


                case 12:
                    if (Class1.InvSin == 0)
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + "Phases - " + SnsOrderStr + " Inv. SVPWM = " + "0" + Environment.NewLine);
                    else
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + "Phases - " + SnsOrderStr + " Inv. SVPWM = " + "1" + Environment.NewLine);
                    textBoxDescription.AppendText(MyStrings.IncPWM);
                    textBoxDescription.AppendText(Environment.NewLine);
                    break;

                case 14:
                    textBoxDescription.AppendText(Cnt.ToString() + MyStrings.PWMIncreased);
                    textBoxDescription.AppendText(Environment.NewLine);
                    break;

                case 15:
                    textBoxDescription.AppendText(Cnt.ToString() + MyStrings.DelayU + Class1.Curr1SnTST);
                    textBoxDescription.AppendText(Environment.NewLine);
                    break;



                case 16:
                    textBoxDescription.AppendText(Cnt.ToString() + MyStrings.Stp);
                    textBoxDescription.AppendText(Environment.NewLine);

                    break;



                case 17:
                    textBoxDescription.AppendText(Environment.NewLine);
                    if (Class1.InvSin == 0)
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.OrderFound + Environment.NewLine + "-->" + SnsOrderStr + " Inv. SVPWM = " + "0 <--" + Environment.NewLine);
                    else
                        textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.OrderFound + Environment.NewLine + "--> " + SnsOrderStr + " Inv. SVPWM = " + "1 <--" + Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    //  textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + ": " + "Оптимизация фазового сдвига... " + Environment.NewLine);

                    break;

                case 18:
                    textBoxDescription.AppendText(Cnt.ToString() + MyStrings.Stp + Environment.NewLine);
                    break;



                case 19:
                    textBoxDescription.AppendText(Cnt.ToString() + MyStrings.Stp + Environment.NewLine);

                    result = MessageBox.Show(MyStrings.MotorMovingOkNo, MyStrings.Inform, MessageBoxButtons.YesNo, MessageBoxIcon.Question);


                    if (result == DialogResult.Yes)
                    {
                        d(9);
                    }
                    else
                    {
                        d(7);
                    }

                    break;











                case 20:
                    textBoxDescription.AppendText(Cnt.ToString() + MyStrings.PWMIncreased + Environment.NewLine);
                    break;

                case 21:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + Class1.Curr1SnTST_0.ToString() + Environment.NewLine);
                    break;

                case 22:
                    textBoxDescription.AppendText(Cnt.ToString() + ": Phase shift: " + Class1.Curr1SnTST.ToString() + Environment.NewLine);
                    break;


                case 23:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + Class1.Curr1SnTST_0.ToString() + " - " + Class1.Curr1SnTST.ToString() + Environment.NewLine);

                    break;


                case 27:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.LowLevelThrottle + Class1.SensorThresholdDn.ToString() + Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.LowLevelHallBreak + Class1.BreakThresholdDn.ToString() + Environment.NewLine);
                    d(14);
                    result = MessageBox.Show(MyStrings.ThrottleCalibration, MyStrings.Inform, MessageBoxButtons.YesNo, MessageBoxIcon.Question);


                    if (result == DialogResult.Yes)
                    {
                        d(2);
                    }
                    else
                    {
                        d(3);
                    }
                    break;

                case 29:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.ThrottleHighLevel + Class1.SensorThresholdUp.ToString() + Environment.NewLine);
                    result = MessageBox.Show(MyStrings.BreakCalibration, MyStrings.Inform, MessageBoxButtons.YesNo, MessageBoxIcon.Question);


                    if (result == DialogResult.Yes)
                    {
                        d(4);
                    }
                    else
                    {
                        d(5);
                    }
                    break;


                case 30:
                    result = MessageBox.Show(MyStrings.BreakCalibration, MyStrings.Inform, MessageBoxButtons.YesNo, MessageBoxIcon.Question);


                    if (result == DialogResult.Yes)
                    {
                        d(4);
                    }
                    else
                    {
                        d(5);
                    }
                    break;





                case 31:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.HighLevelHallBreak + Class1.BreakThresholdUp.ToString() + Environment.NewLine);
                    break;

                case 32:
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.AutosettingsCompleted + Environment.NewLine);
                    MessageBox.Show(MyStrings.AutosettingsCompletedMSG, MyStrings.Inform, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    d(6);
                    break;

                case 33:
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.TooLowThrottle + Environment.NewLine);
                    MessageBox.Show(MyStrings.TooLowThrottleMSG, MyStrings.Inform, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    d(10);
                    break;

                case 34:
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.TooHighThrottle + Environment.NewLine);
                    MessageBox.Show(MyStrings.TooHighThrottleMsg, MyStrings.Inform, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    d(10);
                    break;

                case 35:
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.LowMoreHighThrottle + Environment.NewLine);
                    MessageBox.Show(MyStrings.LowMoreHighThrottleMSG, MyStrings.Inform, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    d(10);
                    break;


                case 36:
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.TooLowBreak + Environment.NewLine);
                    MessageBox.Show(MyStrings.TooLowBreakMSG, MyStrings.Inform, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    d(11);
                    break;

                case 37:
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.TooHighBreak + Environment.NewLine);
                    MessageBox.Show(MyStrings.TooHighBreakMSG, MyStrings.Inform, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    d(11);
                    break;

                case 38:
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Environment.NewLine);
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.LowMoreHighBreak + Environment.NewLine);
                    MessageBox.Show(MyStrings.LowMoreHighBreakMSG, MyStrings.Inform, MessageBoxButtons.OK, MessageBoxIcon.Information);
                    d(11);
                    break;






                case 254:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.OrderNotDetected + Environment.NewLine);
                    MessageBox.Show(MyStrings.OrderNotDetectedMSG, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                    d(12);
                    break;

                case 255:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.Error255 + Environment.NewLine);
                    MessageBox.Show(MyStrings.Error255, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                    break;

                case 256:
                    textBoxDescription.AppendText(Cnt.ToString() + ": " + MyStrings.Error256 + Environment.NewLine);
                    MessageBox.Show(MyStrings.Error256, MyStrings.ErrorMsg, MessageBoxButtons.OK);
                    break;


                default:
                    textBoxDescription.AppendText(Class1.AutoNastroykaState.ToString() + Environment.NewLine);
                    break;


            }



        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show("Stop autosettings?", MyStrings.Inform, MessageBoxButtons.YesNo, MessageBoxIcon.Question);


            if (result == DialogResult.Yes)
            {
                d(6);
                this.Close();
            }
        }
    }
}
