
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,a,ans;//开long long是好习惯
    string b,e;
    char c;
	cin>>n;
	for(int i=0;i<n;i++)
	{ 
		cin>>a>>b>>c>>c>>e;//一个一个输入
		if(b=="g")
		{
			if(e=="mg")
			ans=a*1000;
			else 
			ans=a*1;//也可以不写*1，但这样更直观
		}
		else if(b=="kg")
		{
			if(e=="g")
			ans=a*1000;
			else if(e=="mg")
			ans=a*1000000;
			else 
			ans=a*1;
		}
		else if(b=="mg")
		{
			ans=a*1;
		}
		else if (b=="m")
		{
		 if(e=="mm")
			ans=a*1000;
			else 
			ans=a*1;
		}
		else if(b=="km")
		{
			if(e=="m")
			ans=a*1000;
			else if(e=="mm")
			ans=a*1000000;
			else 
			ans=a*1;
		}
		else if(b=="mm")
		{
			ans=a*1;
		}
		cout<<a<<" "<<b<<" = "<<ans<<" "<<e<<endl;
	}
	return 0;//return 0是好习惯
}