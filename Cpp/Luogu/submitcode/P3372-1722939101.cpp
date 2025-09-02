#include <bits/stdc++.h>
using namespace std;
long long a[100005],n,m,t[400005],tag[400005];
void push_up(long long f)
{
	t[f]=t[f<<1]+t[f<<1|1];
}
void push_down(long long L,long long R,long long f)
{
	long long mid=(L+R)>>1;
	t[f<<1]+=tag[f]*(mid-L+1);
	tag[f<<1]+=tag[f];
	t[f<<1|1]+=tag[f]*(R-mid);
	tag[f<<1|1]+=tag[f];
	tag[f]=0;
}
void build(long long f,long long L,long long R)
{
	if(L==R)
	{
		t[f]=a[L];
		return;
	}
	long long mid=(L+R)>>1;
	build(f<<1,L,mid);
	build(f<<1|1,mid+1,R);
	push_up(f);
}
long long query(long long ql,long long qr,long long L,long long R,long long f)
{
	long long ans=0;
	if(ql<=L&&qr>=R)
	{
		return t[f];
	}
	long long mid=(L+R)>>1;
	push_down(L,R,f);
	if(ql<=mid)
	{
		ans+=query(ql,qr,L,mid,f<<1);
	}
	if(qr>mid)
	{
		ans+=query(ql,qr,mid+1,R,f<<1|1);
	}
	return ans;
}
void update(long long ql,long long qr,long long L,long long R,long long f,long long k)
{
	if(ql<=L&&qr>=R)
	{
		t[f]+=k*(R-L+1);
		tag[f]+=k;
		return;
	}
	push_down(L,R,f);
	long long mid=(L+R)>>1;
	if(ql<=mid)
	{
		update(ql,qr,L,mid,f<<1,k);
	}
	if(qr>mid)
	{
		update(ql,qr,mid+1,R,f<<1|1,k);
	}
	push_up(f);
}
void lesson1()
{
	long long type,left,right,k;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		cin>>type>>left>>right;
		if(type==2)
		{
			cout<<query(left,right,1,n,1)<<endl;
		}
		else
		{
			cin>>k;
			update(left,right,1,n,1,k);
		}
	}
}
int main()
{
	lesson1();
	return 0;
}