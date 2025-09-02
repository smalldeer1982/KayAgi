#include<bits/stdc++.h>
using namespace std;
int n,a[10005],ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++)
	{
		for(int j=1;j<=n-i;j++)
		{
			if(a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
				ans+=1;
			}
		}	
	}
	cout<<ans;
	return 0;
}