#include<stdio.h>
#define add(a,b,c)((a)+(a)*(b)*((c)/100))
int main()
{
    float a;
    float b;
    float c;
    printf("银行本利计算器 \n");
    printf("请输入本金:");
    scanf("%f", &a);
    printf("请输入年份:");
    scanf("%f", &b);
    printf("请输入利率(例如2%%只需要填2):");
    scanf("%f", &c);
    float z = add(a, b, c);
    printf("本金加利息为:%f \n", z);
    return 0;
}
