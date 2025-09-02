#include <bits/stdc++.h>
using namespace std;
int n,m,k,r;
int a[11],w[11],c[11],f[501]={0};
int stt,stn=0;
int main()
{
    cin>>n>>m>>k>>r;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=m;i++)
    {
        cin>>w[i];
    }
    for(int i=1;i<=m;i++)
    {
        cin>>c[i];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=r;j>=w[i];j--)
        {
            f[j]=max(f[j],f[j-w[i]]+c[i]);
        }
    }
    for(int i=1;i<=r;i++)
    {
        if(f[i]>=k)
        {
            stt=r-i;
            break;
        }
    }
    for(int i=1;i<=n;i++)
    {
        stt-=a[i];
        if(stt<=0)
		{
			break;
		} 
        stn++;
    }
    cout<<stn<<endl;
	return 0;
} 