#include <bits/stdc++.h>
using namespace std;
string arr,s,a[105],b[105];
bool flag=0,flag1=0;
int sum=0,n;
int main() 
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
	}
	cin>>arr;
	while (sum<arr.length()) 
	{
		if (arr[sum]>='a'&&arr[sum]<='z')
		{
			s+=arr[sum];
		} 
		else 
		{
			flag=0;
			flag1=0;
			if((arr[sum-1]<'a'||arr[sum-1]>'z')&&(arr[sum]<'a'||arr[sum]>'z'))
			{
				cout<<arr[sum];
				s="";
				flag1=1;
			}
			if(flag1==0)
			{
				for(int i=1;i<=n;i++)
				{
					if(s==a[i])
					{
						cout<<b[i];
						flag=1;
					}
				}
				if(flag==0)
				{
					cout<<"UNK";
				}
				cout<<arr[sum];
				s="";
			}
		}
		sum++;
	}
	if (!s.empty())
	{
		flag=0;
		for(int i=1;i<=n;i++)
		{
			if(s==a[i])
			{
				cout<<b[i];
				flag=1;
			}
		}
		if(flag==0)
		{
			cout<<"UNK";
		}
	}
	return 0;
}