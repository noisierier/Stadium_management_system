#include <stdio.h>
#include <time.h>

void delay(int delay_time)//ʱ����ʱ������ms��
{
    clock_t start_time = clock();
    while ((clock() - start_time) * 1000 / CLOCKS_PER_SEC < delay_time) 
    {
        // ѭ���ȴ�  
    }
}