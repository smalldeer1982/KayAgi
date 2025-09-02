#include<bits/stdc++.h>
using namespace std;
int n,x,a[10],y;
int main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		string str=to_string(i);
		for(char c:str)
		{
			y=c-'0';
			a[y]+=1;
		}
	}
	cout<<a[x];
	return 0;
}