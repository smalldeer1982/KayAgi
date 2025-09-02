#include <bits/stdc++.h>
using namespace std;
int n,a[125][125],b[125][125],maxn=-1e9;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
		}
	}
	for(int x=1;x<=n;x++)
	{
		for(int y=1;y<=n;y++)
		{
			for(int x2=x;x2<=n;x2++)
			{
				for(int y2=y;y2<=n;y2++)
				{
					int s=b[x2][y2]-b[x-1][y2]-b[x2][y-1]+b[x-1][y-1];
					maxn=max(maxn,s);
				}
			}
		}
	}
	cout<<maxn;
	return 0;
}