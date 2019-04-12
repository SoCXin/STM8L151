/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L151K4�����̹���Demo
*******************************************************************************/
#include "stm8l15x.h"
//����LED�밴���ӿ�
#define LED_GPIO_PORT  GPIOA
#define LED_GPIO_PINS  GPIO_Pin_6
#define KEY_GPIO_PORT  GPIOB
#define KEY_GPIO_PINS  GPIO_Pin_4
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע���Ǿ�ȷ��ʱ����
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void Delay(__IO uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��ʱ�����ú�������
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void CLK_Config(void)
{
  
  /* Select HSE as system clock source */
  CLK_SYSCLKSourceSwitchCmd(ENABLE);//ʹ��ʱ���л�
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);//ѡ���ⲿ����ʱ����Ϊʱ��Դ
  /* system clock prescaler: 1*/
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����ϵͳʱ�ӷ�Ƶ
  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_LSI)//�ȴ�ʱ���ȶ�
  {}
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��RTC���ú���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void RTC_Config(void)
{
        CLK_LSEConfig(CLK_LSE_ON);//RTCʱ��Դѡ��
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//RTCʱ�ӷ�Ƶ
        while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);//�ȴ�ʱ��Դ����
        
        RTC_WakeUpCmd(DISABLE);//�ر�RTC����
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTCʱ���ſ�ʹ��
        RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//RTC����ʱ�ӷ�Ƶ
        RTC_ITConfig(RTC_IT_WUT, ENABLE);//RTC�����ж�ʹ��
        RTC_SetWakeUpCounter(2047);

        ITC_SetSoftwarePriority(RTC_IRQn, ITC_PriorityLevel_3);//���ȼ�
        
        enableInterrupts();//ʹ���ж�
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��Ҫʵ����͹���CPU��IO��Ҫ���ȷ���ĵ�ƽ�����̳��˰�����LED�ӿ�����IOȫ������ͣ�
              ����Ҫʹ�ó��͹���ָ�
                            
              ʵ�������
              ACTIVE-HALT��������/CPU/���������ֹͣ��LSI/LSE���У�BEEP/IWDG/RTC/LCD��һ������
              ʹ�ܣ�����ͨ��HALTָ�����ACTIVD-HALTģʽ��
              
              ����ʱʵ�������Լ1.4ua
              RTC�жϻ��ѣ�LED��һ��Ƶ����˸
              ���������AN3147
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
     PWR_FastWakeUpCmd(ENABLE);  //���ٻ���ʹ��
     RTC_Config();
     //����IO����͵�ƽ
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
       
    PWR_UltraLowPowerCmd(ENABLE);//���͹���
    
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//���Ѷ�ʱ���ж�ʹ��
    RTC_WakeUpCmd(ENABLE);//RTC����ʹ��
    
    while(1)
    {
        halt();
    }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
