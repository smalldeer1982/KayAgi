# Towering Arrays

## 题目描述

称一个长度为 $m$ 的数组 $b = [b_1, b_2, \ldots, b_m]$ 为 $p$-towering，当且仅当存在一个下标 $i$（$1 \le i \le m$），使得对于所有下标 $j$（$1 \le j \le m$）满足以下条件：

$$b_j \ge p - |i - j|. $$

给定一个长度为 $n$ 的数组 $a = [a_1, a_2, \ldots, a_n]$，你可以删除最多 $k$ 个元素。求剩余数组能够构成 $p$-towering 的最大 $p$ 值。

## 说明/提示

第一个测试用例中，无法删除任何元素。剩余数组为 $[2, 1, 4, {\color{red}{5}}, 2]$，当选择 $i = 4$ 时满足 $p = 3$：
- $a_1 = 2 \ge p - |i - 1| = 3 - |4 - 1| = 0$；
- $a_2 = 1 \ge p - |i - 2| = 3 - |4 - 2| = 1$；
- $a_3 = 4 \ge p - |i - 3| = 3 - |4 - 3| = 2$；
- $a_4 = 5 \ge p - |i - 4| = 3 - |4 - 4| = 3$；
- $a_5 = 2 \ge p - |i - 5| = 3 - |4 - 5| = 2$。

第二个测试用例中，可以删除第 1、2、5 个元素得到数组 $[4, \color{red}{5}]$。当选择 $i = 2$ 时，该数组满足 $p = 5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
5 0
2 1 4 5 2
5 3
2 1 4 5 2
6 1
1 2 3 4 5 1
11 6
6 3 8 5 8 3 2 1 2 7 1
14 3
3 2 3 5 5 2 6 7 4 8 10 1 8 9
2 0
1 1```

### 输出

```
3
5
5
7
9
1```

# 题解

## 作者：未来姚班zyl (赞：3)

首先二分 $p$，这让我们的思考过程有更多的保障。

对于我们选择的位置 $i$，它的左右两边是毫不相干的两个部分。

我们考虑求出以 $i$ 结尾的最长子序列，使其半边满足题目要求的性质。

设 $dp_{i,j}$ 表示前 $i$ 个，要求总长度为 $j$，现在最多填了多少个数。

那么转移为：如果 $a_{i+1}\ge p-(j-dp_{i,j})+1$，则有 $dp_{i,j}+1$ 转移到 $dp_{i+1,j}$。

整个过程中 $p-(j-dp_{i,j})+1$ 是单调不升的，所以可以用线段树二分维护这个 $dp$，复杂度 $O(n\log V\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=2e5+5,M=1e6+5,inf=(1LL<<30)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,a[N],W;
struct seg{
	int mx,mn,laz;
}xd[N<<2];
inline void insert(int x,int k){
	xd[x].laz+=k,xd[x].mx+=k,xd[x].mn+=k;
}
inline void pushdown(int x){
	insert(L,xd[x].laz),insert(R,xd[x].laz),xd[x].laz=0;
}
inline void getup(int x){
	xd[x].mn=min(xd[L].mn,xd[R].mn),xd[x].mx=max(xd[L].mx,xd[R].mx);
}
inline void build(int x,int l,int r){
	xd[x].laz=0;
	if(l==r)return xd[x].mx=xd[x].mn=W-l+1,void();
	build(lc),build(rc),getup(x);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int k){
	if(OK)return insert(x,k);
	pushdown(x);
	if(Ll<=mid)modify(lc,Ll,Rr,k);
	if(Rr>mid)modify(rc,Ll,Rr,k);
	getup(x);
}
inline int findl(int x,int l,int r,int k){
	if(l==r)return xd[x].mx<=k?l:n+1;
	pushdown(x);
	if(xd[L].mn<=k)return findl(lc,k);
	return findl(rc,k);
}
inline int findr(int x,int l,int r){
	if(l==r)return xd[x].mx==W+1?l:-1;
	pushdown(x);
	if(xd[R].mx==W+1)return findr(rc);
	return findr(lc);
}
int G[N];
inline bool check(int w){
	W=w,build(Root);
	repn(i){
		int Ps=findl(Root,min(a[i],w));
		if(Ps!=n+1)modify(Root,Ps,n,1);
		if(a[i]>=w)G[i]=findr(Root);
		else G[i]=-1;
	}
	build(Root);
	per(i,n,1){
		int Ps=findl(Root,min(a[i],w));
		if(Ps!=n+1)modify(Root,Ps,n,1);
		if(a[i]>=w){
			if(findr(Root)+G[i]-1>=n-m)return 1;
		}
	}
	return 0;
}
inline void Main(){
	n=read(),m=read();
	repn(i)a[i]=read();
	int l=1,r=1e9,ans=0;
	while(l<=r)if(check(mid))ans=mid,l=mid+1;
	else r=mid-1;
	cout <<ans<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}

```

---

