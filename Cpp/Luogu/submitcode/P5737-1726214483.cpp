#include<bits/stdc++.h>
using namespace std;
int x,y,sum=0,a[3005];
bool flag=0;
int main()
{
	cin>>x>>y;
	for(int i=x;i<=y;i++)
	{
		flag=0;
		if((i%4==0&&i%100!=0)||i%400==0)
		{
			flag=1;
		}
		if(flag==1)
		{
			sum+=1;
			a[sum]=i;
		}
	}
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++)
	{
		cout<<a[i]<<" ";
	}
	return 0;
}