#include<bits/stdc++.h>
using namespace std;
int main()
{
    char a[200];//开个大点的字符串
    int n,i,la,b[200];//b数组用来转换
    cin>>n>>a;
    la=strlen(a);//取长度
    for(i=0;i<la;i++)
        b[i]=a[i];//转换
    for(i=0;i<la;i++)
        b[i]=b[i]+n;//破解密码
    for(i=0;i<la;i++)
    {
        if(b[i]>122)//z的ASCLL码是122
            b[i]=b[i]%122+96; //循环会'a'，a的ASCLL码是96
    }
    for(i=0;i<la;i++)
    {
        a[i]=b[i];//转换回去，输出
        cout<<a[i];
    }
    return 0;
}