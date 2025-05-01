#include <stdio.h>
#include <inttypes.h>

//Ввести два числа и вывести их в порядке возрастания.

int main(void)
{
	int32_t a=0,b=0;

	scanf("%d%d", &a,&b);

	a>=b?printf("%d %d\n", b,a):printf("%d %d\n", a,b);

	return 0;
}

