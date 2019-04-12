/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L151K4������GPIO����
*******************************************************************************/
#include "stm8l15x.h"
#include "24c0x.h"
//����LED�밴���ӿ�
#define LED1_GPIO_PORT  GPIOD
#define LED1_GPIO_PINS  GPIO_Pin_2
#define LED2_GPIO_PORT  GPIOB
#define LED2_GPIO_PINS  GPIO_Pin_0
#define LED3_GPIO_PORT  GPIOC
#define LED3_GPIO_PINS  GPIO_Pin_4

unsigned char WBuf[]={"STM8S IIC��д24C0X!\r\n"};
#define BufferSize  30
unsigned char RBuf[BufferSize];
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����ʱ����
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
****������ע��
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED1�ӿ�
    CLK_PeripheralClockConfig (CLK_Peripheral_I2C1,ENABLE);//����IIC1ʱ��
    
     //UART_Init();  
  //Send_Str("STM8S IIC��д����:\r\n");
  
  InitIIC();
  EEPROM_WriteData(WBuf,EEPROM_BASE_ADDRESS,BufferSize);
  EEPROM_ReadData(RBuf,EEPROM_BASE_ADDRESS,BufferSize);
 
  //Send_Str(RBuf);
    while(1)
    {
        GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//��תLED1�ӿڵ�ƽ��ʵ��LED1��˸
        Delay(0xFFFF);//��ʱ�����ڹ۲�ʵ������
    }

}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
