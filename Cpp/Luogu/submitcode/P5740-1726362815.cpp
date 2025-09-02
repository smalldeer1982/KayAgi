#include<bits/stdc++.h>
using namespace std;
int n;
struct student{
	string name;
	int c,m,e,sum;
	int num;
}stu[1005];
bool cmp(student a,student b)
{
	if(a.sum==b.sum)
	{
		return a.num<b.num;
	}
	return a.sum>b.sum; 
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>stu[i].name>>stu[i].c>>stu[i].m>>stu[i].e;
		stu[i].num=i;
		stu[i].sum=stu[i].c+stu[i].m+stu[i].e;
	}
	sort(stu+1,stu+n+1,cmp);
	cout<<stu[1].name<<" "<<stu[1].c<<" "<<stu[1].m<<" "<<stu[1].e;
	return 0;
}