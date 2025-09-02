#include<bits/stdc++.h>
using namespace std;
struct student{
	int max1,min1;
	double sum;
}stu[105];
int n,m;
double ans=0;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		stu[i].min1=10;
		for(int j=1;j<=m;j++)
		{
			int a;
			cin>>a;
			stu[i].max1=max(stu[i].max1,a);
			stu[i].min1=min(stu[i].min1,a);
			stu[i].sum+=a;
		}
		stu[i].sum=stu[i].sum-stu[i].max1-stu[i].min1;
		stu[i].sum/=(m-2);
		ans=max(ans,stu[i].sum);
	}
	printf("%.2lf\n",ans);
	return 0;
}
