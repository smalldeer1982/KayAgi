#include<bits/stdc++.h>
using namespace std;
int main()
{
	int sum=1,n,a[1000005];
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]<sum)
		{
			continue;
		} 
		else 
		{
			sum++;
		} 
	}
	cout<<sum-1<<endl;
}