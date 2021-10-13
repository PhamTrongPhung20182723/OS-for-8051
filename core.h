#include <REGX51.H>

enum count_num{
    TIMER_1S = 200,
    TASK_MAX = 2,
};

#define TIMES (5000)
#define TH0_0 ((8192 - TIMES) >> 8 )
#define TL0_0 (8192 - TIMES)

struct task{
    void (*runit)(void);
    int delay;                  
    int counter;         
};
typedef struct task task_t;

void task_schedule(void);
void task_init(void);
void timer_init(void);
void gotosleep(void);
void run_task(void);
void app_add(void (*task)(void), int delay);
void task1(void);
void task2(void);

