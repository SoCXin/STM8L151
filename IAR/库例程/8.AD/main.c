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

uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
/*******************************************************************************
****��ڲ�������Ҫ���͵��ַ���
****���ڲ�������
****������ע��USART���ͺ���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//��Ϊ����
        {
            USART_SendData8(USART1,*Str);     //�������� 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
            Str++;//��һ������
        }
}
/*******************************************************************************
****��ڲ�������Ҫ���͵�16������
****���ڲ�������
****������ע��USART����16���ƺ���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void USART1_SendHex(unsigned char dat)
{
      USART_SendData8(USART1,'0');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,'x');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,HexTable[dat>>4]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,HexTable[dat&0x0f]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,' ');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����������RXD-UT TXD-UR����ñ�̽ӣ�ͨ��USB�����Ӽ�����뿪���壬��
              ������Ĵ��ڵ���������������ò��������Խ��յ������巢�͵�ADC������
              ���ݡ�ʹ��ǰ��������Ȱ�װCH340������
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
     u16 u16_adc1_value;  
     CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����ADC/USARTʱ��
     CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//����ADC/USARTʱ��
     USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART��ʼ����9600��8N1
     USART_Cmd (USART1,ENABLE);//ʹ��USART
     
     ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);//����ת����12λ��ת��ʱ��1��Ƶ
     ADC_Cmd(ADC1,ENABLE);//ADCʹ��
     ADC_ChannelCmd (ADC1,ADC_Channel_11,ENABLE);//ʹ��ͨ��11
     
     while(1)
     {
         ADC_SoftwareStartConv (ADC1);//�������ת��
         
         USART1_SendStr("ADCת�����Ϊ: ");
         while(!ADC_GetFlagStatus (ADC1,ADC_FLAG_EOC));//�ȴ�ת������
         ADC_ClearFlag (ADC1,ADC_FLAG_EOC);//�����Ӧ��־
         u16_adc1_value=ADC_GetConversionValue (ADC1);//��ȡת��ֵ
         
         USART1_SendHex((u16_adc1_value>>8)); 
         USART1_SendHex((u16_adc1_value&0xff));
         
         USART1_SendStr("\r\n");//����
     }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
