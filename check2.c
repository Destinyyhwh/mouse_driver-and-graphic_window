#define __LIBRARY__
#include <unistd.h>
#include <stdio.h>

typedef struct {
    int mid;  
    int pid;
}message;

#define CLICK_LEFT 1
#define CLICK_RIGHT 2
#define TIMER_ARRIVE 3

#define TYPE 0
#define SECONDS 1000

_syscall1(void,get_message,message *,msg);
_syscall2(int,timer_create,long,ms,int,type);



int main()
{
	message * msg;
    timer_create(SECONDS,TYPE);
    while(1){
        get_message(msg);
        if (msg->mid > 0)
        {
            switch(msg->mid)
            {
            case CLICK_LEFT:
                printf("CLICK_LEFT\n");
                break;
            case CLICK_RIGHT:
                printf("CLICK_RIGHT\n");
                break;
            case TIMER_ARRIVE:
                printf("TIMER_ARRIVE\n");
                break;
            }
        }
    }
}