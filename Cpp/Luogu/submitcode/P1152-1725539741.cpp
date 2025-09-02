#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],b[1000005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++)
	{
		b[abs(a[i]-a[i+1])]=1;
	}
	for(int i=1;i<=n-1;i++)
	{
		if(b[i]==0)
		{
			cout<<"Not jolly";
			return 0;
		}
	}
	cout<<"Jolly";
	return 0;
}