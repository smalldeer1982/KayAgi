#include<iostream>
using namespace std;
int main()
{
    float s,b,sum;
    int a;
    a=1;
    b=2;
    sum=2;
    cin>>s;
    while(sum<=s)
    {
        b=b*98/100;
        sum+=b;
        a+=1;
    }
    cout<<a;
    return 0; 
}