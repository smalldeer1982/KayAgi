#include<bits/stdc++.h>
using namespace std;
const int inf=-1e9;
int a[200],b[200],f[200][20000];
int t,n,sum=0;
int main()
{
	cin>>t>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		sum+=a[i];
	}
	for(int i=1;i<=sum;i++)
	{
		f[0][i]=inf;
	}
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=sum;j++)
		{
			f[i][j]=f[i-1][j];
			if(j>=a[i])
			{
				f[i][j]=max(f[i][j],f[i-1][j-a[i]]+b[i]);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=t;i++)
	{
		ans=max(ans,f[n][i]);
	}
	cout<<ans;
	return 0;
}