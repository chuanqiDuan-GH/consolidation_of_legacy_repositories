#include "func.h"
//抽签

void *Lots()
{
    sleep(SLEEP_TIME);
    int luckyGuy = rand()%MEMBER_SIZE;
    printf("the number of our lucky dog is %d\n", luckyGuy);
}

