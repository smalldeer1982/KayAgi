#include<bits/stdc++.h>
using namespace std;
int n,a[305][5],b[305][5],sum=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		b[i][1]=i;
		sum=0;
		for(int j=1;j<=3;j++)
		{
			cin>>a[i][j];
			sum+=a[i][j];
		}
		b[i][2]=sum;
		b[i][3]=a[i][1];
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<n;j++)
		{
			if(b[j][2]<b[j+1][2])
			{
				swap(b[j][2],b[j+1][2]);
				swap(b[j][1],b[j+1][1]);
				swap(b[j][3],b[j+1][3]);
			}
			if(b[j][2]==b[j+1][2])
			{
				if(b[j][3]<b[j+1][3])
				{
					swap(b[j][2],b[j+1][2]);
					swap(b[j][1],b[j+1][1]);
					swap(b[j][3],b[j+1][3]);
				}
			}
		}
	}
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=2;j++)
		{
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}