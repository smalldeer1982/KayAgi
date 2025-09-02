#include <iostream>
using namespace std;
int a[105],n=0;
int main()
{
	for(int i=1;;i++)
	{
		cin>>a[i];
		if(a[i]==0)
		{
			break;
		}
		n+=1;
	}
	for (int i=n;i>=1;i--)
	{
		cout<<a[i]<<" ";
	}
    return 0;	
}