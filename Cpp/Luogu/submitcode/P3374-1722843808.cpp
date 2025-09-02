#include<bits/stdc++.h> 
using namespace std;
const int maxn=5e5+10;
int n,m,op,x,y,a[maxn];
int sum[maxn*4];
void build(int o,int L,int R)
{
	if(L==R)
	{
		sum[o]=a[L];
		return;
	}
	int M=(L+R)/2;
	build(o*2,L,M);
	build(o*2+1,M+1,R);
	sum[o]=sum[o*2]+sum[o*2+1];
}
void update(int o,int L,int R)
{
	if(L==R)
	{
		sum[o]+=y;
		return;
	}
	int M=(L+R)/2;
	if(x<=M)
	{
		update(o*2,L,M);
	}
	else
	{
		update(o*2+1,M+1,R);
	}
	sum[o]=sum[o*2]+sum[o*2+1];
}
int query(int o,int L,int R)
{
	if(x<=L&&R<=y)
	{
		return sum[o];
	}
	int M=(L+R)/2;
	int ans=0;
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
			update(1,1,n);
		}
		else if(op==2)
		{
			cout<<query(1,1,n)<<endl;
		}
	}
	return 0;
}