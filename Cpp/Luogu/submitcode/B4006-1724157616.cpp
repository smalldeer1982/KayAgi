#include <bits/stdc++.h>
using namespace std;
int n,k,a[1005],sum=0,ans=0;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		sum=0;
		for(int j = i;j>=1;j--) 
		{
			if(a[i]-a[j]<=k)
			{
				sum+=a[j];
			}
		}
		ans=max(ans,sum);
	}
	cout<<ans;
	return 0;
}