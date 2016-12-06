#include "func.h"
//抽签

void *Lots()
{
    sleep(SLEEP_TIME);
    int luckyGuy = rand()%MEMBER_SIZE;
    printf("the number of our lucky guy is %d\n", luckyGuy);
}

