#include<bits/stdc++.h>
using namespace std;
int a[10005],n,x,f[10005],ans=-1,b[10005],p=-1,k;
int main()
{
	while(cin>>x) 
	{
		a[++n]=x;
		p=-1;
		for(int i=1;i<=k;i++)
		{
			if(b[i]>=x)
			{
				p=i;
				break;
			}
		}
		if(p==-1)
		{
			k++;
			b[k]=x;
		}
		else
		{
			b[p]=x;
		}
	}
	for(int i=1;i<=n;i++)
	{
		f[i]=1;
		for(int j=1;j<=i-1;j++) 
		{
			if(a[j]>=a[i])
			{
				f[i]=max(f[i],f[j]+1);
			}
		}
		ans=max(ans,f[i]);
	}
	cout<<ans<<endl;
	cout<<k<<endl;
	return 0;
}