#include<bits/stdc++.h>
using namespace std;	
int a[10005],m,n,minn=100000,sum=0;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n-m+1;i++)
	{
		sum=0;
		for(int j=i;j<=i+m-1;j++){
			sum+=a[j];
		}
		minn=min(minn,sum);
	}
	cout<<minn;
    return 0;
}