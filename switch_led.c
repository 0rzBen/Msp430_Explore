#include <msp430.h> 

//���¿��ص��

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // ֹͣ���Ź���ʱ��

    P1DIR |= BIT0;              // �� P1.0 ����Ϊ��������� LED��
    P1REN |= BIT1;              // ���� P1.1 ���ڲ�����/��������
    P1OUT |= BIT1;              // �� P1.1 ����Ϊ��������


    while(1)
    {
        if (P1IN & BIT1)        // ��� P1.1 ����ߵ�ƽ������δ���£�

            P1OUT &= ~BIT0;     // Ϩ�� LED��P1.0 ����͵�ƽ��

        else                    // ��� P1.1 ����͵�ƽ���������£�

            P1OUT |= BIT0;      // ���� LED��P1.0 ����ߵ�ƽ��

    }
}

