#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    int s;
    scanf("%d%d%d",&a,&b,&c);
    s=(int)(a*0.2+b*0.3+c*0.5);//第一次强制转化
    printf("%.lf",(double)s);//第二、三次强制转化
} 