#include <bits/stdc++.h>
using namespace std;
int n,s[25],b[25],ans=1000000000;
void f(int sd,int kd,int step)
{
	if(step==n)
	{
		int tmp=abs(sd-kd);
		if(tmp<ans&&kd!=0)
		{
			ans=tmp;
		}
		return;
	}
	step+=1;
	f(sd*s[step],kd+b[step],step);
	f(sd,kd,step);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i]>>b[i];
	}
	f(1,0,0);
	cout<<ans;
}