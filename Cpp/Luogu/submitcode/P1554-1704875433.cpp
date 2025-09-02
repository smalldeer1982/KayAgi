#include <iostream>
using namespace std;
int a[10],m,n,t,b; 
int main()
{
	cin>>m>>n;
	for(int i=0;i<=9;i++)
	{
		a[i]=0;
	}
	for(int i=m;i<=n;i++)
	{
		t=i;
		while(t!=0)
		{
			b=t%10;
			a[b]++;
			t=t/10;
		}
	}
	for(int i=0;i<=9;i++)
	{
		cout<<a[i]<<" ";
	}
    return 0;	
}