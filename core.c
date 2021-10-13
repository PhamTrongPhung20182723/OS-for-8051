#include "core.h"

task_t tasks[TASK_MAX];
unsigned char TASK_NUM_POS = 15;
extern int count = 0;
int j = 0;
char todo_flag = 0;
void (*todo_task)(void);

void timer_init(void)
{
    TMOD &= 0xf0;
    TMOD |= 0x00;
    ET0 = 1;
    TR0 = 1;
    TL0 = TL0_0;
    TH0 = TH0_0;
    EA = 1;	
}

void task_init(void)
{
    EA = 0;
    tasks[0].runit = &task1;
	tasks[0].delay = 300;
    tasks[1].runit = &task2;
    tasks[1].delay = 500;
    for(j = 0; j< TASK_MAX; ++j){
        tasks[j].counter = 0;
    }
    EA = 1;
}
void task_schedule(void)
{
    EA = 0;
    for(j = 0; j< TASK_MAX; ++j){
        if(  (tasks[j].counter >= tasks[j].delay ) && (tasks[j].runit)){
            tasks[j].counter = 0;
            todo_task = tasks[j].runit;
            todo_flag = 1;
        }
    }
    EA = 1;
}

void run_task(void)
{
    task2();
    task1();
    gotosleep();
}

void app_add(void (*task)(), int delay )
{
   int  index = 0;
    EA = 0;
    while( (tasks[index].runit ) && (index < TASK_MAX)){
        ++index;
    }
    if(index == TASK_MAX){
        return;
    }
            tasks[index].runit = task;
            tasks[index].delay = delay;
    EA = 1;
}
void gotosleep(void)
{
    PCON != 0x01;
}
void task1(void)
{
 // make your task
}
void task2(void)
{	
 // make your task
}
