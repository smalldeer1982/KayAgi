#include<bits/stdc++.h>
using namespace std;
int n;
struct student{
	string name;
	int age,NOIP;
}stu[1005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>stu[i].name>>stu[i].age>>stu[i].NOIP;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<stu[i].name<<" "<<stu[i].age+1<<" ";
		if(stu[i].NOIP*1.2>600)
		{
			cout<<600<<endl;
		}
		else
		{
			cout<<stu[i].NOIP*1.2<<endl;
		}
	}
	return 0;
}