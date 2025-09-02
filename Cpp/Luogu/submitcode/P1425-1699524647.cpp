#include <iostream>
using namespace std;
int main()
{
    int a,b,c,d,x,y;
    cin>>a>>b>>c>>d;
    x=c-a,y=d-b;
    if(y<0){x--;y+=60;}
    cout<<x<<" "<<y;
    return 0;
}