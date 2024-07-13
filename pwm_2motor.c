#include <msp430.h>

void set_pwm (int Motor ,int PWM)
{
    switch (Motor)
    {
        case 1:
            if(PWM > 0)
            {
                TA0CCR1 = PWM;
                TA0CCR2 = 0;
            }
            else
            {
                TA0CCR1 = 0;
                TA0CCR2 = -PWM;
            }
            break;

        case 2:
            if(PWM > 0)
            {
                TA0CCR3 = 0;
                TA0CCR4 = PWM;
            }
            else
            {
                TA0CCR3 = -PWM;
                TA0CCR4 = 0;
            }
            break;

        default:
            TA0CCR1 = 0;
            TA0CCR2 = 0;
            TA0CCR1 = 0;
            TA0CCR2 = 0;
            break;
    }
}

void PWM_Init(void)
{
    P1DIR |= BIT2 + BIT3 + BIT4 + BIT5;    //����P1.2/3/4/5���
    P1SEL |= BIT2 + BIT3 + BIT4 + BIT5;    //SEL��������IO�����⹦�ܣ�BIT2/3/4/5��ӦCCR1/2/3/4
    TA0CCR0 = 500 ;                        //����Ϊ500��ΪԼ1MHz / 500 = 2KHz��PWM
    TA0CTL |= TASSEL_2 + MC_1 + TACLR;     //ʱ��ΪSMCLK������������0

    //����PWM�����ģʽΪģʽ7(reset/set)
    TA0CCTL1 |= OUTMOD_7;
    TA0CCTL2 |= OUTMOD_7;
    TA0CCTL3 |= OUTMOD_7;
    TA0CCTL4 |= OUTMOD_7;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    PWM_Init();

    int i;

    while(1)//test��������
    {
        for(i=0; i <= 400 ; i++)
        {
            set_pwm(1,i);                        //PWM��������0-500; PWM/500��ռ�ձ�
            __delay_cycles(2000);
        }
        for(i=400; i >= 0 ; i--)
        {
            set_pwm(1,i);                        //PWM��������0-500; PWM/500��ռ�ձ�
            __delay_cycles(2000);
        }

    }
}



