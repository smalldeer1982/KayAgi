#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+10;
int x,y,n,m,k,a[maxn],maxv[maxn*4],minv[maxn*4],mi,mx;
void build(int o,int L,int R)
{
	if(L==R)
	{
		maxv[o]=a[L];
		minv[o]=a[L];
		return;
	}
	int M=(L+R)/2;
	build(o*2,L,M);
	build(o*2+1,M+1,R);
	maxv[o]=max(maxv[o*2],maxv[o*2+1]);
	minv[o]=min(minv[o*2],minv[o*2+1]);
}
void query(int o,int L,int R)
{
	if(x<=L&&R<=y)
	{
		mi=min(mi,minv[o]);
		mx=max(mx,maxv[o]);
		return;
	}
	int M=(L+R)/2;
	if(x<=M)
	{
		query(o*2,L,M);
	}
	if(y>M)
	{
		query(o*2+1,M+1,R);
	}
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
		cin>>x>>y;
		mi=INT_MAX;
		mx=INT_MIN;
		query(1,1,n);
		cout<<mx-mi<<endl;
	}
	return 0;
} 