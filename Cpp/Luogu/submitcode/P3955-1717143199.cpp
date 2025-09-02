#include<bits/stdc++.h>
using namespace std;
int book[1005];
int main()
{
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>book[i];
	sort(book+1,book+n+1);
	for(int i=1,k,code;i<=q;i++)
	{
		cin>>k>>code;
		bool flag=0;
		for(int j=1;j<=n;j++)
		{
			int s=pow(10,k);
			if(book[j]%s==code)
			{
				cout<<book[j]<<endl;
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			cout<<-1<<endl;
		}	
	}
	return 0;
}