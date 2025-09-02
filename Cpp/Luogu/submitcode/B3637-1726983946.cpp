#include<bits/stdc++.h>
using namespace std;
int n,a[5005],dp[5005],maxn=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		dp[i]=1;
		for(int j=1;j<i;j++)
		{
			if(a[i]>a[j])
			{
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
		maxn=max(dp[i],maxn);
	}
	cout<<maxn;
	return 0;
}