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
	for(int j=1;j<=n;j++)
	{
		x=0;
		for(int k=j;k>=1;k--)
		{
			if(a[k]<a[j])
			x++;	
		}
		cout<<x<<" ";
	}
	return 0;
}