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
****������ע������ȷ��ʱ����
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
****������ע��ϵͳ�ϵ�Ĭ��ʱ��ΪHSI/8=2M������LED��˸Ƶ�����ж�ʱ��Դ�л��Ƿ�ɹ�
              ���÷��������ֶ��л�ʱ��Դ
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    uint8_t i;  
   
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED�˿�
    
    //ϵͳʱ��ΪHSI 16M
    CLK_HSICmd(ENABLE);//��ʼ�ڲ���ƵRC��16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSIΪϵͳʱ��
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����Ƶ,16M 
    for(i=0;i<10;i++)
    {
       GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);//��תLED״̬
       Delay(0xFFFF);
    }
    //ϵͳʱ��ΪHSI/8=2M
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);//8��Ƶ��16M/8=2M
    for(i=0;i<10;i++)
    {
       GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);//��תLED״̬
       Delay(0xFFFF);
    }
    
    //����ΪHSEΪϵͳʱ��    16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);//ϵͳ��ʱ��ΪHSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_HSERDY)==RESET);//�ȴ�HSE׼������
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//ʹ���л�
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_HSE)//����л��ɹ�
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);//2��Ƶ,8M
       for(i=0;i<10;i++)
       {
          GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PINS);
          Delay(0xFFFF);
        }
    }
    
    //����ΪLSEΪϵͳʱ��    32768
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSE);//ϵͳ��ʱ��ΪLSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_LSERDY)==RESET);//�ȴ�LSE׼������
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//ʹ���л�
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSE)//����л��ɹ�
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//
       for(i=0;i<2;i++)
       {
          GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PINS);
          Delay(0x0FFF);
        }
    }
    
    
    //����ΪLSIΪϵͳʱ�� 32K
    while(1)
    {
        CLK_LSICmd (ENABLE);    //ʹ��LSI
        CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);//LSIΪϵͳʱ��
        while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY)==RESET);//�ȴ�LSI׼������
        CLK_SYSCLKSourceSwitchCmd (ENABLE);//ʹ���л�
        if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSI)//����л��ɹ�
       {
          
          CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����Ƶ  
          for(i=0;i<2;i++)
          {
             GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
             Delay(0x0FFF);
          }  
       }  
    }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
