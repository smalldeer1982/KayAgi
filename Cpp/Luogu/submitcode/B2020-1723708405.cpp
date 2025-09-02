#include<bits/stdc++.h>
using namespace std;
int a[10],sum=0;
int main()
{
	for(int i=1;i<=5;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=5;i++)
	{
		sum+=a[i]%3;
		a[i]-=a[i]%3;
		if(i==1)
		{
			a[2]+=a[i]/3;
			a[5]+=a[i]/3;
		}
		else if(i==5)
		{
			a[1]+=a[i]/3;
			a[4]+=a[i]/3;
		}
		else
		{
			a[i+1]+=a[i]/3;
			a[i-1]+=a[i]/3;
		}
		a[i]-=a[i]/3*2;
	}
	for(int i=1;i<=5;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	cout<<sum;
	return 0;
}