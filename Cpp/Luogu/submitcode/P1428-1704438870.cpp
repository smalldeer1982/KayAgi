#include <iostream>
using namespace std;
int main()
{
	int n,x=0,a[105];
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		x=0;
		for(int j=i;j>=1;j--)
		{
			if(a[j]<a[i])
			x++;	
		}
		cout<<x<<" ";
	}
	return 0;
}