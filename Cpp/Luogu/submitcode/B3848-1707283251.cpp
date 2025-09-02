#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,x,a[105],sum=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
		cin>>a[i];
	}
	cin>>x;
	for(int i=1;i<=n;i++)
	{
		if(x>=a[i])
		{
			x-=a[i];
			sum+=1;
		}
	}
	cout<<sum;
    return 0;
}