#include<bits/stdc++.h>
using namespace std;
int n;
struct student {
	int c,m,e,sum;
	string name;
}a[1001];
bool cmp(student a,student b)
{
	return a.name<b.name;
}
int main() 
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i].name>>a[i].c>>a[i].m>>a[i].e;
		a[i].sum=a[i].c+a[i].m+a[i].e;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<n;i++)
	{
		for(int j=i+1;j<=n;j++) 
		{
			if(abs(a[i].c-a[j].c)<=5&&abs(a[i].m-a[j].m)<=5&&abs(a[i].e-a[j].e)<=5&&abs(a[i].sum-a[j].sum)<=10) 
			{
				cout<<a[i].name<<" "<<a[j].name<<endl;
			}
		}
	}		
	return 0;
}