#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x,y,minecraft=1,n=0,sum=1;
	cin>>x>>y;
	for(int i=x;i<=y;i++)
	{
		minecraft=1;
		sum=1;
		n=0;
		for(int j=2;j<=sqrt(i);j++)
		{
			if(i%j==0)
			{
				minecraft=0;
			}
		}
		if(minecraft==1)
		{
			string m=to_string(i);
			for(int j=0;j<=m.length()-1;j++)
			{
				n+=(m[j]-'0')*sum;
				sum*=10;
			}
			for(int j=2;j<=sqrt(n);j++)
			{
				if(n%j==0)
				{
					minecraft=0;
				}
			}
		}
		if(minecraft==1)
		{
			cout<<i<<endl;
		}
	}
	return 0;
}