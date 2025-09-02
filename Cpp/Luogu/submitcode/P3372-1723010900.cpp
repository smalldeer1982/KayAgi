#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
long long op,n,m,k;
int x,y;
long long a[maxn],sumv[maxn*4],addv[maxn*4];
void build(int o,int L,int R)
{
	if(L==R)
	{
		sumv[o]=a[L];
		return;
	}
	int M=(L+R)/2;
	build(o*2,L,M);
	build(o*2+1,M+1,R);
	sumv[o]=sumv[o*2]+sumv[o*2+1];
}
void update(int o,int L,int R)
{
	if(x<=L&&R<=y)
	{
		addv[o]+=k;
		sumv[o]+=(R-L+1)*k;
		return;
	}
	int M=(L+R)/2;
	if(x<=M)
	{
		update(o*2,L,M);
	}
	if(y>M)
	{
		update(o*2+1,M+1,R);
	}
	sumv[o]=sumv[o*2]+sumv[o*2+1]+addv[o]*(R-L+1);
}
long long query(int o,int L,int R)
{
	if(x<=L&&R<=y)
	{
		return sumv[o];
	}
	int M=(L+R)/2;
	long long ans=addv[o]*(min(R,y)-max(L,x)+1);
	if(x<=M)
	{
		ans+=query(o*2,L,M);
	}
	if(y>M)
	{
		ans+=query(o*2+1,M+1,R);
	}
	return ans;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		cin>>op>>x>>y;
		if(op==1)
		{
			cin>>k;
			update(1,1,n);
		}
		else
		{
			cout<<query(1,1,n)<<endl;
		}
	}
	return 0;
} 