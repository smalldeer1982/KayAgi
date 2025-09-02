#include <iostream>
using namespace std;
int a,b,c,x;
int main()
{	
	cin>>x;
    a=x/100;
    b=x%100/10;
    c=x%100%10/1;
	cout<<c<<b<<a;
}