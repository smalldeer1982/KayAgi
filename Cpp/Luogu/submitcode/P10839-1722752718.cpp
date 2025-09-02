#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,d;
	cin>>a>>b>>c>>d;	
	int sum=a,sum1=a,sum2=a;
	int x=a,y=a,z=a;
	for(int i=1;i<=3;i++)
	{
		if(i==1)
		{
			x+=b;
		}
		else if(i==2)
		{
			y-=b;
		}
		else if(i==3)
		{
			z*=b;
		}
	}
	for(int i=1;i<=3;i++)
	{
		sum=x;
		sum1=y;
		sum2=z;
		if(i==1)
		{
		    sum+=c;
			sum1+=c;
			sum2+=c;
			if(sum==d||sum1==d||sum2==d)
			{
				cout<<"Yes";
				return 0;
			}
		}
		else if(i==2)
		{
			sum-=c;
			sum1-=c;
			sum2-=c;
			if(sum==d||sum1==d||sum2==d)
			{
				cout<<"Yes";
				return 0;
			}
		}
		else if(i==3)
		{
			sum*=c;
			sum1*=c;
			sum2*=c;
			if(sum==d||sum1==d||sum2==d)
			{
				cout<<"Yes";
				return 0;
			}
		}
	}
	cout<<"No";
	return 0;
}