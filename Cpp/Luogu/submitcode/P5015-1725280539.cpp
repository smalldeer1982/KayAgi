#include<bits/stdc++.h>
using namespace std;
string n;
int x,ans=0;
int main()
{
	while(cin>>n)
	{		
		x=n.length();
		for(int i=0;i<x;i++)
		{
			if((n[i]>='0'&&n[i]<='9')||(n[i]>='a'&&n[i]<='z')||(n[i]>='A'&&n[i]<='Z'))
			{
				ans+=1;
			}
		}
	}
	cout<<ans;
	return 0;
}