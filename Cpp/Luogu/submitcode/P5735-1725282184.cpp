#include<bits/stdc++.h>
using namespace std;
int x=0;
float ans=0,a[5],b[5];
float dis(float x1,float x2,float y1,float y2)
{
	return sqrt(abs((x2-x1)*(x2-x1))+abs((y2-y1)*(y2-y1)));
}
int main()
{
	for(int i=1;i<=3;i++)
	{
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=3;i++)
	{
		if(i==3)
		{
			x=1;
		}
		else
		{
			x=i+1;
		}
		ans+=dis(a[i],a[x],b[i],b[x]);
	}
	printf("%.2f",ans);
	return 0;
}