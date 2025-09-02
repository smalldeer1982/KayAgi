#include<bits/stdc++.h>
using namespace std;
int n,a[50005],b[50005],ans=0,sum=1;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=b[sum])
		{
			ans+=1;
			sum+=1;
		}
	}
	cout<<ans;
	return 0;
}