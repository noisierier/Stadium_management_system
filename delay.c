#include <stdio.h>
#include <time.h>

void delay(int delay_time)//时间延时函数（ms）
{
    clock_t start_time = clock();
    while ((clock() - start_time) * 1000 / CLOCKS_PER_SEC < delay_time) 
    {
        // 循环等待  
    }
}