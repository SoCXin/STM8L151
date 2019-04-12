/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L151K4������RTC����
*******************************************************************************/
#include "stm8l15x.h"
#include "1621.h"


typedef uint8_t* string;
unsigned char Ht1621Tab[]={0x00,0x00,0x00,0x00};
//����RTC
RTC_InitTypeDef   RTC_InitStr;
RTC_TimeTypeDef   RTC_TimeStr;
RTC_DateTypeDef   RTC_DateStr;
RTC_AlarmTypeDef  RTC_AlarmStr;
/* Days names definition */
CONST string WeekDayNames[7] =
  {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

/* Months names definition */
CONST   uint8_t MonthNames[] = {'J', 'A', 'N', 'F', 'E', 'B', 'M', 'A', 'R', 'A', 'P', 'R',
                                  'M', 'A', 'Y', 'J', 'U', 'N', 'J', 'U', 'L', 'A', 'U', 'G',
                                  'S', 'E', 'P', 'O', 'C', 'T', 'N', 'O', 'V', 'D', 'E', 'C'};
/*******************************************************************************
****��������:
****��������:����ȷ��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʱ����Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��RTC��ʼ������
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void Calendar_Init(void)
{
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStr.RTC_AsynchPrediv = 0x7F;
  RTC_InitStr.RTC_SynchPrediv = 0x00FF;
  RTC_Init(&RTC_InitStr);

  RTC_DateStructInit(&RTC_DateStr);
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Friday;
  RTC_DateStr.RTC_Date = 13;
  RTC_DateStr.RTC_Month = RTC_Month_May;
  RTC_DateStr.RTC_Year = 11;
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);

  RTC_TimeStructInit(&RTC_TimeStr);
  RTC_TimeStr.RTC_Hours   = 01;
  RTC_TimeStr.RTC_Minutes = 00;
  RTC_TimeStr.RTC_Seconds = 00;
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);


  RTC_AlarmStructInit(&RTC_AlarmStr);
  RTC_AlarmStr.RTC_AlarmTime.RTC_Hours   = 01;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes = 01;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds = 00;
  RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
  RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStr);

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  RTC_AlarmCmd(ENABLE);
}

/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��RTC���Գ���ʱ����Һ����Ļ��ʾ
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    unsigned short temp1,temp2;
    
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//RTCʱ��Դ
    CLK_PeripheralClockConfig (CLK_Peripheral_RTC,ENABLE);//����RTCʱ��
    
    RTC_DeInit( ); //RTC������ø�λ��Ĭ��״̬
    Calendar_Init();//RTC��ʼ��
       
    Delay(100);           //��ʱһ��ʱ�� 
    Ht1621_Init();        //�ϵ��ʼ��LCD 
    Delay(100);           //��ʱһ��ʱ�� 
    Ht1621WrAllData(0,Ht1621Tab,16);// ����
  
    while (1)
    {
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);//��ȡRTC��ǰʱ��
        temp1 = RTC_TimeStr.RTC_Seconds;//��
        temp2=RTC_TimeStr.RTC_Minutes;  //��
        data_convertor(temp2*100+temp1);//ת��Ϊ��ʾֵ
        Display();                      //��ʾʱ��
        Display_lcd_dot();              //��ʾ����
       
    }

}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
