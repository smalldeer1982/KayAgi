#include<bits/stdc++.h>
using namespace std;
int n,d,a[1005],b[1005],sum=1;
int main()
{
	cin>>n>>d;
	for(int i=0;i<=(d-1);i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<=(d-1);i++)
	{
		b[a[i]]+=sum;
		sum+=1;
	}
	for(int i=0;i<=(n-1);i++)
	{
		cout<<b[i]<<" ";
	}
	return 0;
}