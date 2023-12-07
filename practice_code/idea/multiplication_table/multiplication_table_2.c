#include <stdio.h>

void cfd(int a,int b,int c)
{
    if(a<=b)
    {
        printf ("%d*%d=%d ",a,b,a*b);
        ++a;
        cfd(a,b,c);
    }
    else if(b < c)
    {
        a=1;
        printf ("\n");
        ++b;
        cfd (a,b,c);
    }
    else if(b==c)
    {
        return;
    }


}

int main()
{
    int a ;
    printf ("请输入:");
    scanf ("%d",&a);
    cfd (1,1,a);
}