#include<bits/stdc++.h>
using namespace std;
int n;
struct student {
	int c,m,e,sum;
	string name;
}a[1005];
int main() 
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i].name>>a[i].c>>a[i].m>>a[i].e;
		a[i].sum=a[i].c+a[i].m+a[i].e;
	}
	for(int i=1;i<=n-1;i++)
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