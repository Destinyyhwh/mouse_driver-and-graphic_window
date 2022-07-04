#define __LIBRARY__
#include<unistd.h>
#include<stdlib.h>

typedef struct{
	long x;
	long y;
	long dx;
	long dy;
	long color;
} object;

_syscall0(int,init_graphics);
_syscall1(int,paint,object *,yyh);

int main(void)
{
    object yyh;
    init_graphics();
    yyh.x = 50;
    yyh.y = 50;
    yyh.dx = 10;
    yyh.dy = 10;
	yyh.color = 12;
    paint(&yyh);
}
