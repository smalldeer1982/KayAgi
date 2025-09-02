#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,q,a[1005],b[1005][5];
	long miny=10000005;
	bool flag=1;
	cin>>n>>q;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<q;i++)
	{
		cin>>b[i][0];
		cin>>b[i][1];
	}
	for(int i=0;i<q;i++)
	{

		miny=10000005;
		string x=to_string(b[i][1]);
		for(int j=0;j<n;j++)
		{
			flag=1;
			string y=to_string(a[j]);
			for(int k=b[i][0]-1;k>=0;k--)
			{
				
				if(y[y.length()-b[i][0]+k]!=x[k])
				{
					flag=0;
				}
			}
			if(flag==1&&a[j]<miny)
			{
				miny=a[j];
			}	
		}
		if(miny==10000005)
		{
			cout<<-1<<endl;
		}
		else
		{
			cout<<miny<<endl;
		}		
	}
}