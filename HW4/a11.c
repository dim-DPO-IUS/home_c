#include <stdio.h>
#include <inttypes.h>

// Сумма максимума и минимума

int main(void)
{
	int32_t a=0,b=0,c=0,d=0,e=0;
    int32_t min=0,max=0;

	scanf("%d%d%d%d%d", &a,&b,&c,&d,&e);
    // min
    min = a<=b?a:b;
    min = c<=min?c:min;
    min = d<=min?d:min;
    min = e<=min?e:min;
    // max
    max = a>=b?a:b;
    max = c>=max?c:max;
    max = d>=max?d:max;
    max = e>=max?e:max;

	printf("%d\n", min+max);

	return 0;
}