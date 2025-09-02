#include <iostream>
using namespace std;
int a[10],b[10],t=0,maxx=0;
int main()
{
	for(int i=1;i<=7;i++)
	{
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=7;i++)
	{
		if(a[i]+b[i]>8&&a[i]+b[i]>maxx)
		{
			t=i;
			maxx=a[i]+b[i];
		}
	}
	if (t==0)
	{
		cout<<"0";
	}
	else
	{
		cout<<t;
	}
    return 0;	
}