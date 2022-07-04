/*可视化应用程序*/

#define __LIBRARY__
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int mid;
    int pid;
} message;

typedef struct{
	long x;
	long y;
	long dx;
	long dy;
	long color;
} object;

#define sti() __asm__ ("sti"::)
#define cli() __asm__ ("cli"::)

#define CLICK_LEFT 1
#define CLICK_RIGHT 2
#define TIMER_ARRIVE 3

#define BIRD_X 120
#define BIRD_Y 100
#define BIRD_WIDTH 10
#define BIRD_HEIGHT 8

#define MAX_BARRIER 20

#define SECONDS 400
#define TYPE 0
#define DROP 1
#define FLY_CLICK_LEFT 10
#define FLY_CLICK_RIGHT 10
#define LEFT_MOVE 5

#define BIRD_COLOR 12
#define BARRIER_COLOR 12
#define BACKGROUND_COLOR 3
#define GAME_OVER_COLOR 12

#define VAG_WIDTH 320
#define VGA_HEIGHT 200

#define BARRIER_WIDTH 10
#define BARRIER_INTERVAL 40
#define BARRIER_HEIGHT (rand() % (VGA_HEIGHT * 3 / 4))

object bird;
int fron, rear;
object barriers[MAX_BARRIER];
int i;


_syscall0(int, init_graphics);
_syscall1(int, get_message, message*, msg);
_syscall1(int, paint,object*,p);
_syscall2(int,timer_create,long,seconds,int,type);

void init(void)
{
	bird.x = BIRD_X;
	bird.y = BIRD_Y;
	bird.dx = BIRD_WIDTH;
	bird.dy = BIRD_HEIGHT;
	fron = rear = 0;
	return ;
}


void Paint(void)
{
	object yyh1,yyh2,yyh3;
	int i;
	yyh1.x = 0;yyh2.x = bird.x;
	yyh1.y = 0;yyh2.y = bird.y;
	yyh1.dx = VAG_WIDTH;yyh2.dx = bird.dx;
	yyh1.dy = VGA_HEIGHT;yyh2.dy = bird.dy;
	yyh1.color = BACKGROUND_COLOR;yyh2.color = BIRD_COLOR;
	paint(&yyh1);paint(&yyh2);
	for (i = fron; i != rear; i = (i + 1) % MAX_BARRIER)
	{
		yyh3.x = barriers[i].x;
		yyh3.y = barriers[i].y;
		yyh3.dx = barriers[i].dx;
		yyh3.dy = barriers[i].dy;
		yyh3.color = BARRIER_COLOR;
		paint(&yyh3);
	}
}

int main(void)
{
	message msg;
	timer_create(SECONDS, 0); 
	init_graphics();			
	init();
	while (1){
		get_message(&msg); 
		switch (msg.mid)
		{
		case CLICK_LEFT:
			bird.y -= FLY_CLICK_LEFT;
			Paint();
			break;
		case CLICK_RIGHT:
			bird.x += FLY_CLICK_RIGHT;
			Paint();
			break;
		case TIMER_ARRIVE:
			Paint();
			for (i = fron; i != rear; i = (i + 1) % MAX_BARRIER)
				if (barriers[i].x < bird.x + bird.dx && bird.x < barriers[i].x + barriers[i].dx)
					if (barriers[i].y < bird.y + bird.dy && bird.y < barriers[i].y + barriers[i].dy){
						object temp;
						temp.x = 0;
						temp.y = 0;
						temp.dx = VAG_WIDTH;
						temp.dy = VGA_HEIGHT;
						temp.color = GAME_OVER_COLOR;
						paint(&temp);
						goto GAME_OVER;
					}
			bird.y += DROP;
			for (i = fron; i != rear; i = (i + 1) % MAX_BARRIER)
				barriers[i].x -= LEFT_MOVE;
			if (fron == rear){
				object temp;
				temp.dx = BARRIER_WIDTH;
				temp.dy = BARRIER_HEIGHT;
				temp.x = VAG_WIDTH;
				temp.y = 0;
				temp.color = BARRIER_COLOR;
				if (rear != (fron + MAX_BARRIER - 1) % MAX_BARRIER){
					barriers[rear].x = temp.x;
					barriers[rear].y = temp.y;
					barriers[rear].dx = temp.dx;
					barriers[rear].dy = temp.dy;
					rear = (rear + 1) % MAX_BARRIER;
				}
			}
			else
			{
				if (barriers[(rear + MAX_BARRIER - 1) % MAX_BARRIER].x + barriers[(rear + MAX_BARRIER - 1) % MAX_BARRIER].dx + BARRIER_INTERVAL <= VAG_WIDTH)
				{
					object temp;
					temp.dx = BARRIER_WIDTH;
					temp.dy = BARRIER_HEIGHT;
					temp.x = VAG_WIDTH;
					if (barriers[(rear + MAX_BARRIER - 1) % MAX_BARRIER].y)  /* 一上一下 */
						temp.y = 0;
					else
						temp.y = VGA_HEIGHT - temp.dy;
					if (rear != (fron + MAX_BARRIER - 1) % MAX_BARRIER){
						barriers[rear].x = temp.x;
						barriers[rear].y = temp.y;
						barriers[rear].dx = temp.dx;
						barriers[rear].dy = temp.dy;
						rear = (rear + 1) % MAX_BARRIER;
					}
				}
				if (barriers[fron].x + barriers[fron].dx <= 0)
					fron = (fron + 1) % MAX_BARRIER;
			}
			break;
		}
	}
GAME_OVER:
	return 0;
} 