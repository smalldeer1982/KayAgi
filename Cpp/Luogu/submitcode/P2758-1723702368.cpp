#include<bits/stdc++.h>
using namespace std;
int n,m,dp[2010][2010];
char a[2010],b[2010];
int main()
{
	cin>>a+1>>b+1;	
	n=strlen(a+1);
	m=strlen(b+1);
	for(int i=1;i<=n;i++)
	{
		dp[i][0]=i;
	} 
	for(int i=1;i<=m;i++)
	{
		dp[0][i]=i;
	} 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i]==b[j])
			{
				dp[i][j]=dp[i-1][j-1];
			}
			else 
			{
				dp[i][j]=min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]))+1;
			}
		}
	}
	cout<<dp[n][m];
	return 0;
} 
