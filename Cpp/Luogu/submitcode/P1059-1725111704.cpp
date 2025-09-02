#include<bits/stdc++.h>
using namespace std;
int n,a[105],b[105],sum=0;
bool flag=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		flag=0;
		for(int j=1;j<=n;j++)
		{
			if(a[i]==b[j])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			sum+=1;
			b[sum]=a[i];
		}
	}
	sort(b+1,b+sum+1);
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++)
	{
		cout<<b[i]<<" ";
	}
	return 0;
}