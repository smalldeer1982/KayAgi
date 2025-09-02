#include<bits/stdc++.h>
using namespace std;
int n,sum=1;
int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		sum+=1;
		sum*=2;
	}
	cout<<sum;
	return 0;
}