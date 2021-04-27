/*******************************************************************************
* 实验名称  	: printf重定向实验
* 实验说明  : 注意：打开串口调试助手后，要先勾选DTR后再取消，见实验截图
* 接线说明  : 				
* 实验现象	: 核心板上D1指示灯闪烁，打开串口调试助手，实验现象可见文件内截图
*******************************************************************************/

#include "system.h"
#include "SysTick.h"

#include "usart.h"
extern int usart2_stop_flag;
extern int sbus[200];
 u16 channel[10];
 int ind=-1;
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	int k;
	unsigned char a,b;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组

	USART1_Init(9600);
	
	while(1)
	{
	if(usart2_stop_flag==1)
	{
	    usart2_stop_flag=0;
	  channel[0] = ((sbus[ind + 1] |sbus[ind + 2] << 8) & 0x07FF);
   channel[1] = ((sbus[ind + 2] >> 3 | sbus[ind + 3] << 5) & 0x07FF);
    channel[2] = ((sbus[ind + 3] >> 6 | sbus[ind + 4] << 2 | sbus[ind + 5] << 10) & 0x07FF);
    channel[3] = ((sbus[ind + 5] >> 1 | sbus[ind + 6] << 7) & 0x07FF);
    channel[4] = ((sbus[ind + 6] >> 4 | sbus[ind + 7] << 4) & 0x07FF);
   channel[5] = ((sbus[ind + 7] >> 7 | sbus[ind + 8] << 1 | sbus[ind + 9] << 9) & 0x07FF);
    channel[6] = ((sbus[ind + 9] >> 2 | sbus[ind + 10] << 6) & 0x07FF);
   channel[7] = ((sbus[ind + 10] >> 5 |sbus[ind + 11] << 3) & 0x07FF);
   channel[8] = ((sbus[ind + 12] | sbus[ind + 13] << 8) & 0x07FF);
   channel[9] = ((sbus[ind + 13] >> 3 | sbus[ind + 14] << 5) & 0x07FF);
		USART_SendData(USART1,0);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
		for(k=0;k<10;k++){
		a=(channel[k]/255)+1;
		b=(channel[k]%255)+1;
	
		USART_SendData(USART1,a);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	
		USART_SendData(USART1,b);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
			delay_ms(5);
	}
		

	}
}


	}
