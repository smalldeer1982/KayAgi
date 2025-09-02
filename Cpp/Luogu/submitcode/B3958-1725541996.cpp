#include<bits/stdc++.h>
using namespace std; 
int t,cnt=0,sum=0;
string a,b;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b;
		cnt=0;
		sum=0;
		if(a==b)
		{
			cout<<"similar"<<endl;
			continue;
		}
		if(a.size()==b.size())
		{
			for(int i=0;i<a.size();i++)
			{
				if(a[i]==b[i])
				{
					cnt+=1;
				}
			}
			if(cnt+1==a.size()||cnt==a.size())
			{
				cout<<"similar"<<endl;
			}
			else
			{
				cout<<"not similar"<<endl;
			}
		}
		else if(a.size()+1==b.size())
		{
			for(int i=0;i<b.size();i++)
			{
				if(a[sum]==b[i])
				{
					cnt+=1;
					sum+=1;
				}
			}
			if(cnt==a.size())
			{
				cout<<"similar"<<endl;
			}
			else
			{
				cout<<"not similar"<<endl;
			}
		}	
		else if(a.size()-1==b.size())
		{
			swap(a,b);
			for(int i=0;i<b.size();i++)
			{
				if(a[sum]==b[i])
				{
					cnt+=1;
					sum+=1;
				}
			}
			if(cnt==a.size())
			{
				cout<<"similar"<<endl;
			}
			else
			{
				cout<<"not similar"<<endl;
			}
		}
		else
		{
			cout<<"not similar"<<endl;
		}
	} 
	return 0;
}