#include<bits/stdc++.h>
using namespace std;
int n,j,a[110],dpa[110],dpb[110],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		dpa[i]=1;
		for(int j=1;j<i;j++)
		{
			if(a[j]<a[i])
			{
				dpa[i]=max(dpa[i],dpa[j]+1);
			}
		}
	}
	for(int i=n;i>=1;i--)
	{
		dpb[i]=1;
		for(int j=n;j>i;j--)
		{
			if(a[j]<a[i])
			{
				dpb[i]=max(dpb[i],dpb[j]+1);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,dpa[i]+dpb[i]-1);
	}
	cout<<n-ans;
	return 0;
}