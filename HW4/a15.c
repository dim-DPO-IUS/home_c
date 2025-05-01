#include <stdio.h>
#include <inttypes.h>

// Определить уравнение прямой по координатам двух точек. 
// Уравнение вида: y=k*x+b

int main(void)
{
	int32_t x1=0,y1=0,x2=0,y2=0;
    float k=0.0,b=0.0;

	scanf("%d%d%d%d", &x1,&y1,&x2,&y2);

    k = (float)(y2-y1) / (x2-x1);
    b = y1 - k*x1;

    printf("%.2f %.2f\n", k,b);

	return 0;
}