#include <bits/stdc++.h>
using namespace std;
int n,m,b[15][15],maxn=0,sum0=0,sum1=0;
string a[15];
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			b[i][j]=a[i][j]-'0';
		}
	}
	for(int x1=0;x1<n;x1++)
	{
		for(int y1=0;y1<m;y1++)
		{
			for(int x2=0;x2<n;x2++)
			{
				for(int y2=0;y2<m;y2++)
				{
					sum0=0;
					sum1=0;
//					cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
					for(int i=x1;i<=x2;i++)
					{
						for(int j=y1;j<=y2;j++)
						{
//							cout<<i<<" "<<j<<" "<<b[i][j]<<endl;
							if(b[i][j]==0)
							{
								sum0+=1;
							}
							else
							{
								sum1+=1;
							}
						}
					}
					if(sum0==sum1&&sum0!=0&&sum1!=0)
					{
						maxn=max((x2-x1+1)*(y2-y1+1),maxn);
					}
//					cout<<sum0<<" "<<sum1<<endl;
				}
			}
		}
	}
	cout<<maxn;
	return 0;
}