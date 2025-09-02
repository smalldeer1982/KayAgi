#include<bits/stdc++.h>
using namespace std;
int t,m,w[105],v[105],dp[105][1005];
int main()
{
	cin>>t>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>w[i]>>v[i];
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=t;j++)
		{
			if(w[i]<=j)
			{
				dp[i][j]=max(dp[i-1][j],v[i]+dp[i-1][j-w[i]]);
			}
			else
			{
				dp[i][j]=dp[i-1][j];
			}
		}
	}
	cout<<dp[m][t];
	return 0;
}