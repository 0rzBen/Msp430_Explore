#include <msp430.h>

int t1,t2,c1,c2,cnt,count,flag;
double duty;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    TA0CTL = TASSEL__SMCLK + MC_2 + TACLR + TAIE;
    TA0CCTL0 = CCIE;//ʹ��CCR0�жϣ�Ĭ��CAP = 0, ����Ƚ�
    TA0CCR0 = 52428;

    P1SEL|=BIT2; // ���Ÿ��ã����P1.2��ӦTA0 CCR1
    
    _EINT();
    while(1)
    {
       __no_operation();
    }

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)    //ÿ��1s��ȡһ�¼���
{
    count++;
    if(count == 20)
    {
        flag=cnt;
        cnt=0;
        count=0;
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
    switch(__even_in_range(TA0IV,14))
    {
        case 0:   break;//��
        case 2:
            cnt++;
 //����duty rate������δ֪���
//        t1=t2;
//        t2=TA0CCR1;
//        c1=c2;
//        c2=t2-t1;
//        duty=1.0*c2/(c1 + c2);
            break;      //CCR1
        case 4:  break;//CCR2
        case 6:  break;//CCR3
        case 8:  break;//CCR4
        case 10: break;//CCR5
        case 12: break;//CCR6
        case 14: break;//���IFG
        default: break;
    }
}

