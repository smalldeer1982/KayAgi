#include <bits/stdc++.h>
using namespace std;
int n,m,a[100005],sum[100005],x,y;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cin>>m;
	sum[1]=a[1];
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		cout<<sum[y]-sum[x-1]<<endl;
	}
	return 0;
}