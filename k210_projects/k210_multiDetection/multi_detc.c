
#include <msp430.h>
#include <OLED.h>
#include <UART.h>

#define BUFFER_SIZE 128
u8 buffer[BUFFER_SIZE];
u8 buffer_index = 0;

volatile unsigned int i;
void delay()
{
    for(i=50000;i>0;i--);
}

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    Uart_Init();
    OLED_Init();
    OLED_Clear();
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;

    OLED_ShowString(0, 1, "Recognition", 8);
    int cnt = 0;

    while(1)
    {
        if(!(P1IN & BIT1))
        {
            cnt++;
        }

        if(cnt == 1)
        {
            sendstring("1\r\n");
        }
        else if(cnt == 2)
        {
            sendstring("2\r\n");
        }
        else if(cnt == 3)
        {
            sendstring("3\r\n");
        }


        delay();
        //__no_operation();
    }
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch(__even_in_range(UCA0IV,4))
    {
        case 0:break;                             // Vector 0 - no interrupt
        case 2:                                   // Vector 2 - RXIFG

            buffer[buffer_index] = UCA0RXBUF; // ��ȡ���յ�����
            buffer_index++;
            //OLED_ShowChar(0, 2, UCA0RXBUF, 8); // for debug
            if (buffer[buffer_index-1] == '~') // '~' ��־����
            {
                buffer[buffer_index-1] = '\0';

                OLED_Clearlines(4, 4); //����ɾȥ����Ȼ�ȳ���̻��ж����ַ�
                OLED_ShowString(0, 4, buffer, 8); // ��ʾ���յ�������
                buffer_index = 0; // ���û���������
            }

            break;
        case 4:break;                             // Vector 4 - TXIFG
        default: break;
    }
}




