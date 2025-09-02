# [POI 2007] DRZ-Trees

## 题目描述

Byteasar has a cottage. Lately, he has bought $n$ trees and had them planted all in one row. Byteasar does not,  however, like the order which the trees have been planted in. It particularly annoys him that tall and short  ones have been mixed up, and the composition does not meet his aesthetic criteria.

Byteasar has invented a disorder coefficient so as to allow the gardener to comprehend his intentions: thelower the value of the coefficient the prettier the row of trees. It is defined in the following way:

$|h_1-h_2|+|h_2-h_3|+\cdots+|h_{n-1}-h_n|$, where $h_1,h_2,\cdots,h_n$ are the heights of consecutive trees in a row.
Replanting is a very toilsome and cumbersome task, therefore Byteasar has ordered the gardener to replanttwo trees at the most (i.e. interchange their positions). The task of the gardener is to choose the pair to replantin a way that makes the disorder coefficient the smallest.

The gardener is not sure if he has chosen the correct pair of trees and he fears he may lose his job ifhe is mistaken. Help him: for each tree calculate the minimal disorder coefficient that may be attained byswitching places with any other tree.

TaskWrite a programme which:

reads the height of the consecutive trees in a row from the standard input,        for each tree calculates the minimal disorder coefficient that may be attained should it switch places    with some other tree (or should there be no change at all),        writes the outcome to the standard output.

定义一排树的不整齐程度为相邻两树的高度差的和。设树高分别为 $h _ 1, h _ 2, \cdots, h _ n$，那么不整齐程度定义为：$|h_1-h_2|+|h_2-h_3|+\cdots+|h_{n-1}-h_n|$。

请对于每个 $i$ 求出，如果只把 $i$ 和另一棵树交换高度（可以不交换），那么不整齐度最小是多少。


## 样例 #1

### 输入

```
5
7 4 5 2 5```

### 输出

```
7
7
8
7
7```

# 题解

## 作者：Dispwnl (赞：3)

### [博客qwq](https://a-failure.github.io/2019/01/04/POI2007-%E6%A0%91Drz/)

分情况讨论，假设交换的是$i,j$，则答案是$ans-val_i-val_j+\vert h_i-L_j\vert+\vert h_i-R_j\vert+\vert h_j-L_i\vert+\vert h_j-R_i\vert$，其中$val_i$表示原来$i$位置的答案，$L_i$表示$min(h_{i-1},h_{i+1})$，$R_i$表示$max(h_{i-1},h_{i+1})$，这样就有了$3\times 3=9$种情况（……）：

$h_i<L_j,h_i>R_j,L_j\le h_i\le R_j$

$j$同理

这样就可以用线段树+扫描线做了，写起来还是挺麻烦的~~写出一种情况然后```ctrl+A+C+V```改改就行了~~

### 代码
```
# include<iostream>
# include<cstring>
# include<cstdlib>
# include<cstdio>
# include<algorithm>
# define tl (k<<1)
# define tr (k<<1|1)
# define mid (l+r>>1)
# define LL long long
using namespace std;
const int MAX=5e4+5;
struct p{
	LL x;
}s[MAX<<2];
struct q{
	int x,id;
	bool operator< (const q &a)
	const{
		return x<a.x;
	}
}A[MAX],val[MAX],val_l[MAX],val_r[MAX];
int n,m,_n;
LL Ans;
int h[MAX],H[MAX],_h[MAX],HL[MAX],HR[MAX],_H[MAX],_L[MAX],_R[MAX],__L[MAX],__R[MAX];
LL ans[MAX];
bool use[MAX];
bool cmp(q a,q b) {return a.x>b.x;}
void pus(int k) {s[k].x=min(s[tl].x,s[tr].x);}
void change(int l,int r,int k,int x,LL dis)
{
	if(l==r) return void(s[k].x=min(s[k].x,dis));
	if(x<=mid) change(l,mid,tl,x,dis);
	else change(mid+1,r,tr,x,dis);
	pus(k);
}
void update(int l,int r,int k,int x,LL dis)
{
	if(l==r) return void(s[k].x=dis);
	if(x<=mid) update(l,mid,tl,x,dis);
	else update(mid+1,r,tr,x,dis);
	pus(k);
}
LL ask(int l,int r,int k,int L,int R)
{
	if(r<L||R<l) return 1e18;
	if(l>=L&&r<=R) return s[k].x;
	return min(ask(l,mid,tl,L,R),ask(mid+1,r,tr,L,R));
}
int read()
{
	int x(0);
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);x=x*10+ch-48,ch=getchar());
	return x;
}
int look(int x)
{
	int l=1,r=n,ans;
	while(l<=r)
	{
		if(_h[mid]<=x) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int _look(int x)
{
	int l=1,r=n,ans;
	while(l<=r)
	{
		if(_h[mid]>=x) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
void Init()
{
	memcpy(_h,h,sizeof(h));
	sort(_h+1,_h+1+n);
	for(int i=1;i<=n;++i)
	  {
		if(i!=1) _H[i]+=abs(h[i]-h[i-1]);
		if(i!=n) _H[i]+=abs(h[i]-h[i+1]);
		if(i!=1&&i!=n) HL[i]=min(h[i-1],h[i+1]),HR[i]=max(h[i-1],h[i+1]),_L[i]=_look(HL[i]),_R[i]=look(HR[i]),__L[i]=look(HL[i]),__R[i]=look(HR[i]);
	  }
	for(int i=2;i<=n;++i)
	  Ans+=abs(h[i]-h[i-1]);
	for(int i=1;i<=n;++i)
	  ans[i]=Ans;
	LL x;
	for(int i=1;i<=n;++i)
	  {
	  	if(i>2) ans[1]=min(ans[1],x=Ans-_H[i]-_H[1]+abs(h[i]-h[2])+abs(h[1]-h[i-1])+(i!=n?abs(h[1]-h[i+1]):0)),ans[i]=min(ans[i],x);
	  	if(i<n-1) ans[n]=min(ans[n],x=Ans-_H[i]-_H[n]+abs(h[i]-h[n-1])+abs(h[n]-h[i+1])+(i!=1?abs(h[n]-h[i-1]):0)),ans[i]=min(ans[i],x);
	  	if(i!=1) ans[i]=min(ans[i],Ans-(i!=n?abs(h[i]-h[i+1]):0)-(i>2?abs(h[i-1]-h[i-2]):0)+((i!=n&&i!=1)?abs(h[i-1]-h[i+1]):0)+(i>2?abs(h[i]-h[i-2]):0));
	  	if(i!=n) ans[i]=min(ans[i],Ans-(i!=1?abs(h[i]-h[i-1]):0)-(i<n-1?abs(h[i+1]-h[i+2]):0)+((i!=n&&i!=1)?abs(h[i-1]-h[i+1]):0)+(i<n-1?abs(h[i]-h[i+2]):0));
	  }
	for(int i=1;i<=n;++i)
	  val[i]=(q){h[i],i},val_l[i]=(q){HL[i],i},val_r[i]=(q){HR[i],i};
}
void Solve1()
{
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	sort(val+2,val+n),sort(val_r+2,val_r+n);
	for(int i=2,L=2,x;i<n;++i)
	  {
	  	while(val_r[L].x<=val[i].x&&L<n) x=val_r[L].id,use[x]=1,change(1,n,1,H[x],-HL[x]-HR[x]-2*h[x]-_H[x]),++L;
	  	x=val[i].id;
		if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,1,__L[x])-_H[x]+2*h[x]+HL[x]+HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],-HL[x-1]-HR[x-1]-2*h[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],-HL[x+1]-HR[x+1]-2*h[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],-HL[x]-HR[x]-2*h[x]-_H[x]);
	  }
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	for(int i=2,L=2,x;i<n;++i)
	  {
	  	while(val_r[L].x<=val[i].x&&L<n) x=val_r[L].id,use[x]=1,change(1,n,1,H[x],-HL[x]-HR[x]+2*h[x]-_H[x]),++L;
		x=val[i].id;
		if(use[x-1])
		update(1,n,1,H[x-1],1e18);
		if(use[x+1]) 
		update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,__R[x],n)-_H[x]+2*h[x]-HL[x]-HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],-HL[x-1]-HR[x-1]+2*h[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],-HL[x+1]-HR[x+1]+2*h[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],-HL[x]-HR[x]+2*h[x]-_H[x]);
	  }
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	for(int i=2,L=2,x;i<n;++i)
	  {
	  	while(val_r[L].x<=val[i].x&&L<n) x=val_r[L].id,use[x]=1,change(1,n,1,H[x],-HL[x]-HR[x]-_H[x]),++L;
	  	x=val[i].id;
		if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,_L[x],_R[x])-_H[x]+2*h[x]-HL[x]+HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],-HL[x-1]-HR[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],-HL[x+1]-HR[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],-HL[x]-HR[x]-_H[x]);
	  }
}
void Solve2()
{
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	sort(val+2,val+n,cmp),sort(val_l+2,val_l+n,cmp);
	for(int i=2,L=2,x;i<n;++i)
	  {
	  	while(val_l[L].x>=val[i].x&&L<n) x=val_l[L].id,use[x]=1,change(1,n,1,H[x],HL[x]+HR[x]-2*h[x]-_H[x]),++L;
	  	x=val[i].id;
		if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,1,__L[x])-_H[x]-2*h[x]+HL[x]+HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],HL[x-1]+HR[x-1]-2*h[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],HL[x+1]+HR[x+1]-2*h[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],HL[x]+HR[x]-2*h[x]-_H[x]);
	  }
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	for(int i=2,L=2,x;i<n;++i)
	  {
	  	while(val_l[L].x>=val[i].x&&L<n) x=val_l[L].id,use[x]=1,change(1,n,1,H[x],HL[x]+HR[x]+2*h[x]-_H[x]),++L;
	  	x=val[i].id;
		if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,__R[x],n)-_H[x]-2*h[x]-HL[x]-HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],HL[x-1]+HR[x-1]+2*h[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],HL[x+1]+HR[x+1]+2*h[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],HL[x]+HR[x]+2*h[x]-_H[x]);
	  }
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	for(int i=2,L=2,x;i<n;++i)
	  {
	  	while(val_l[L].x>=val[i].x&&L<n) x=val_l[L].id,use[x]=1,change(1,n,1,H[x],HL[x]+HR[x]-_H[x]),++L;
	  	x=val[i].id;
	  	if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,_L[x],_R[x])-_H[x]-2*h[x]-HL[x]+HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],HL[x-1]+HR[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],HL[x+1]+HR[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],HL[x]+HR[x]-_H[x]);
	  }
}
void Solve3()
{
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	sort(val+2,val+n),sort(val_l+2,val_l+n),sort(val_r+2,val_r+n);
	for(int i=2,L=2,R=2,x;i<n;++i)
	  {
	  	while(val_l[L].x<=val[i].x&&L<n) x=val_l[L].id,use[x]=1,change(1,n,1,H[x],-HL[x]+HR[x]-2*h[x]-_H[x]),++L;
	  	while(val_r[R].x<val[i].x&&R<n) x=val_r[R].id,use[x]=0,update(1,n,1,H[x],1e18),++R;
	  	x=val[i].id;
	  	if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,1,__L[x])-_H[x]+HL[x]+HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],-HL[x-1]+HR[x-1]-2*h[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],-HL[x+1]+HR[x+1]-2*h[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],-HL[x]+HR[x]-2*h[x]-_H[x]);
	   }
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	for(int i=2,L=2,R=2,x;i<n;++i)
	  {
	  	while(val_l[L].x<=val[i].x&&L<n) x=val_l[L].id,use[x]=1,change(1,n,1,H[x],-HL[x]+HR[x]+2*h[x]-_H[x]),++L;
	  	while(val_r[R].x<val[i].x&&R<n) x=val_r[R].id,use[x]=0,update(1,n,1,H[x],1e18),++R;
	  	x=val[i].id;
	  	if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,__R[x],n)-_H[x]-HL[x]-HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],-HL[x-1]+HR[x-1]+2*h[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],-HL[x+1]+HR[x+1]+2*h[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],-HL[x]+HR[x]+2*h[x]-_H[x]);
	   }
	memset(s,1,sizeof(s));
	memset(use,0,sizeof(use));
	for(int i=2,L=2,R=2,x;i<n;++i)
	  {
	  	while(val_l[L].x<=val[i].x&&L<n) x=val_l[L].id,use[x]=1,change(1,n,1,H[x],-HL[x]+HR[x]-_H[x]),++L;
	  	while(val_r[R].x<val[i].x&&R<n) x=val_r[R].id,use[x]=0,update(1,n,1,H[x],1e18),++R;
	  	x=val[i].id;
	  	if(use[x-1]) update(1,n,1,H[x-1],1e18);
		if(use[x+1]) update(1,n,1,H[x+1],1e18);
		if(use[x]) update(1,n,1,H[x],1e18);
		ans[x]=min(ans[x],Ans+ask(1,n,1,_L[x],_R[x])-_H[x]-HL[x]+HR[x]);
		if(use[x-1]) update(1,n,1,H[x-1],-HL[x-1]+HR[x-1]-_H[x-1]);
		if(use[x+1]) update(1,n,1,H[x+1],-HL[x+1]+HR[x+1]-_H[x+1]);
		if(use[x]) update(1,n,1,H[x],-HL[x]+HR[x]-_H[x]);
	   }
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	  h[i]=read(),A[i]=(q){h[i],i};
	if(n==2) return printf("%d\n%d",abs(h[1]-h[2]),abs(h[1]-h[2])),0;
	sort(A+1,A+1+n);
	for(int i=1;i<=n;++i)
	  H[A[i].id]=i;
	Init(),Solve1(),Solve2(),Solve3();
	for(int i=1;i<=n;++i)
	  printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：Code_星云 (赞：1)

分类讨论 + 数据结构好题。

以下设 $s_i =|a_i - a_{i-1}|+|a_i-a_{i+1}|$，$l_i = \min(a_{i-1},a_{i+1})$，$r_i = \max(a_{i-1},a_{i+1})$。

首先考虑每次交换两个数的可能方案。这里可以讨论绝对值拆开的情况。

比如说第一种情况，即 $a_i < l_j < r_j$，$a_j<r_i<l_i$ 时（令 $i,j$ 为交换的元）。此时的答案偏移量明显为 $l_j+r_j-2a_i+l_i+r_i-2a_j-s_i-s_j$。其他情况可同理推出。

然后此时就可以用扫描线，即将 $j$ 当做线段修改，$i$ 当做询问。

需要注意的是，$1$ 和 $n$ 的情况需要单独考虑，相邻值交换的影响也可以单独直接计算出。

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
typedef pair<int, int> pii;
#define lc (x << 1)
#define rc (x << 1 | 1)
#define mpr make_pair
#define pb push_back
#define px first
#define py second

const int N = 50005;
const int inf = 1e18;
int n, ori; 
int a[N], id[N], rev[N], ans[N], s[N], bl[N], br[N];
vector<pii> vc[N];

namespace sgtree{
	struct segtree{
		int l, r, mn;
		#define l(x) tree[x].l
		#define r(x) tree[x].r
		#define mn(x) tree[x].mn
	};
	segtree tree[N << 2];
	void pushup(int x){mn(x) = min(mn(lc), mn(rc));}
	void build(int x, int l, int r){
		mn(x) = inf; l(x) = l; r(x) = r;
		if(l == r) return; int mid = (l + r) >> 1;
		build(lc, l, mid); build(rc, mid + 1, r);
		pushup(x);
	}
	void modify(int x, int p, int val){
		if(l(x) == r(x)){mn(x)= val; return;}
		int mid = (l(x) + r(x)) >> 1;
		if(p <= mid) modify(lc, p, val); else modify(rc, p, val);
		pushup(x);
	}
	int query(int x, int l, int r){
		if(l <= l(x) && r(x) <= r) return mn(x);
		int mid = (l(x) + r(x)) >> 1;
		if(r <= mid) return query(lc, l, r);
		if(l > mid) return query(rc, l, r);
		return min(query(lc, l, r), query(rc, l, r)); 
	}
};
using namespace sgtree;

int ask(int p, int l, int r){
	int x = bl[p], y = br[p];
	if(r == y) -- r; if(r == x) -- r;
	if(l == x) ++ l; if(l == y) ++ l;
	if(l > r) return inf;
	return query(1, l, r);
	if((x < l && r < y) || r < x || l > y) return query(1, l, r);
	if(l < x && r > y) return min(query(1, l, x - 1), min(query(1, x + 1, y - 1), query(1, y + 1, r)));
	if(l < x) return min(query(1, l, x - 1), query(1, x + 1, r));
	return min(query(1, l, y - 1), query(1, y + 1, r));
}
void solve1(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++){
		vc[1].pb(mpr(id[i], a[i - 1] + a[i + 1] - 2 * a[i] - s[i]));
		vc[bl[i]].pb(mpr(id[i], inf));
	}
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, 1, bl[p] - 1) + a[p - 1] + a[p + 1] - 2 * a[p] - s[p]);
	}
}
void solve2(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++){
		vc[bl[i]].pb(mpr(id[i], abs(a[i - 1] - a[i + 1]) - 2 * a[i] - s[i]));
		vc[br[i]].pb(mpr(id[i], inf));
	}
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n){
			ans[p] = min(ans[p], ask(p, 1, bl[p] - 1) + a[p - 1] + a[p + 1] - s[p]);
		}
	}
}
void solve3(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++)
		vc[br[i]].pb(mpr(id[i], - 2 * a[i] - a[i - 1] - a[i + 1] - s[i]));
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, 1, bl[p] - 1) + a[p - 1] + a[p + 1] + 2 * a[p] - s[p]);
	}
}
void solve4(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++){
		vc[1].pb(mpr(id[i], a[i - 1] + a[i + 1] - s[i]));
		vc[bl[i]].pb(mpr(id[i], inf));
	}
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, bl[p], br[p] - 1) + abs(a[p + 1] - a[p - 1]) - 2 * a[p] - s[p]);
	}
}
void solve5(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++){
		vc[bl[i]].pb(mpr(id[i], abs(a[i + 1] - a[i - 1]) - s[i]));
		vc[br[i]].pb(mpr(id[i], inf));
	}
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, bl[p], br[p] - 1) + abs(a[p + 1] - a[p - 1]) - s[p]);
	}
}
void solve6(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++)
		vc[br[i]].pb(mpr(id[i], - a[i + 1] - a[i - 1] - s[i]));
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, bl[p], br[p] - 1) + abs(a[p + 1] - a[p - 1]) + 2 * a[p] - s[p]);
	}
}
void solve7(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++){
		vc[1].pb(mpr(id[i], a[i + 1] + a[i - 1] + 2 * a[i] - s[i]));
		vc[bl[i]].pb(mpr(id[i], inf));
	}
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, br[p], n) - a[p - 1] - a[p + 1] - 2 * a[p] - s[p]);
	}
}
void solve8(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++){
		vc[bl[i]].pb(mpr(id[i], abs(a[i + 1] - a[i - 1]) + 2 * a[i] - s[i]));
		vc[br[i]].pb(mpr(id[i], inf));
	}
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, br[p], n) - a[p - 1] - a[p + 1] - s[p]);
	}
}
void solve9(){
	for(int i = 1; i <= n; i ++) vc[i].clear(); build(1, 1, n);
	for(int i = 2; i < n; i ++)
		vc[br[i]].pb(mpr(id[i], 2 * a[i] - a[i + 1] - a[i - 1] - s[i]));
	for(int i = 1; i <= n; i ++){
		for(auto k: vc[i]) modify(1, k.px, k.py);
		int p = rev[i];
		if(p != 1 && p != n)
		  ans[p] = min(ans[p], ask(p, br[p], n) + 2 * a[p] - a[p - 1] - a[p + 1] - s[p]);
	}
}
int calc(int x, int y){
	if(x > y) swap(x, y);
	int res = 0;
	if(x != 1) res += abs(a[y] - a[x - 1]) - abs(a[x] - a[x - 1]);
	if(y != n) res += abs(a[x] - a[y + 1]) - abs(a[y] - a[y + 1]);
	if(x + 1 != y) res += abs(a[y] - a[x + 1]) + abs(a[x] - a[y - 1]) - abs(a[x + 1] - a[x]) - abs(a[y] - a[y - 1]);
	return res;
}

signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]), rev[i] = i;
	for(int i = 2; i <= n; i ++) ori += abs(a[i] - a[i - 1]);
	sort(rev + 1, rev + n + 1, [](int x, int y){return a[x] < a[y];});
	for(int i = 1; i <= n; i ++) id[rev[i]] = i;
	for(int i = 2; i <= n; i ++) ans[1] = min(ans[1], calc(1, i));
	for(int i = 1; i < n; i ++) ans[n] = min(ans[n], calc(i, n)); 
	for(int i = 2; i < n; i ++){
		ans[i] = min(ans[i], min(min(calc(1, i), calc(i, n)), min(calc(i, i - 1), calc(i, i + 1))));
		s[i] = abs(a[i] - a[i - 1]) + abs(a[i + 1] - a[i]);
		bl[i] = min(id[i - 1], id[i + 1]); br[i] = max(id[i - 1], id[i + 1]);
	}
	solve1(); solve2(); solve3();
	solve4(); solve5(); solve6();
	solve7(); solve8(); solve9();
	for(int i = 1; i <= n; i ++) printf("%lld\n", ori + ans[i]); return 0; 
}
```


---

## 作者：CuriousCat (赞：0)

网上的题解其实挺详细了，我就举一个例子说一下思想是什么吧

我们先定义一些变量

$$i$$,$$L_i=min(H_{i-1},H_{i+1})$$,$$R_i=max(H_{i-1},H_{i+1})$$

$$j$$,$$L_j=mjn(H_{j-1},H_{j+1})$$,$$R_j=max(H_{j-1},H_{j+1})$$

然后我们考虑这个关系


$$L_j<=H_i<=R_j$$

$$L_i<=H_j<=R_i$$

答案就是

$$old_ans=|H_j-L_j|+|H_j-R_j|+|H_i-L_i|+|H_i-R_i|$$
$$new\_ans=|H\_i-L\_j|+|H\_i-R\_j|+|H\_j-L\_i|+|H\_j-R\_i|=
(R\_i-L\_i)+(R\_j-L\_j)$$


如果我们把$$H_i$$递增排序，可以证明每个$$[L_j,R_j]$$的限制只会出现一次，消失一次

所以我们把$$H_j$$丢到线段树里面，查询$$[L_i,R_i]$$就行了

乱用auto导致bz交不了23333

```cpp
#pragma GCC optimize ("O2")
#include <bits/stdc++.h>
#define cmax(a,b) (a<b?a=b:a)
#define cmin(a,b) (a>b?a=b:a)
#define R(i,k) for(int i=0;i<(k);++i)
using namespace std;

typedef long long ll;

const int N=5e4+50;
const ll INF=1e12; 

int n,rk[N],rkl[N],rkr[N]; 
ll h[N],res[N],raw,l[N],r[N],val[N];

void ReadData(){
    scanf("%d",&n); 
    for(int i=1;i<=n;++i)
        scanf("%lld",&h[i]); 
}

ll cal(int x,int y)
{
     if (x==y) return raw;
     if (x>y) swap(x,y);
     if (x==1&&y==n) 
         return raw-abs(h[1]-h[2])-abs(h[n-1]-h[n])+abs(h[n]-h[2])+abs(h[1]-h[n-1]);
     if (x==1&&y==2) return raw-abs(h[2]-h[3])+abs(h[1]-h[3]);
     if (x==n-1&&y==n) return raw-abs(h[n-1]-h[n-2])+abs(h[n-2]-h[n]);
     if (x+1==y) return 
         raw-abs(h[x-1]-h[x])-abs(h[y+1]-h[y])+abs(h[x]-h[y+1])+abs(h[y]-h[x-1]);
     long long ans=raw;
     if (x!=1) ans=ans-abs(h[x-1]-h[x])+abs(h[x-1]-h[y]);
     ans=ans-abs(h[x+1]-h[x])+abs(h[x+1]-h[y]);
     ans=ans-abs(h[y-1]-h[y])+abs(h[y-1]-h[x]);
     if (y!=n) ans=ans-abs(h[y+1]-h[y])+abs(h[y+1]-h[x]);
     return ans;
}

ll g(int i){ return abs(h[i]-h[i-1])+abs(h[i+1]-h[i]); }

void Init(){
    //并不能去重
    static int id[N]; int i;
    for(i=1;i<=n;++i)id[i]=i,val[i]=h[i];
    sort(id+1,id+n+1,[](int a,int b){return h[a]<h[b];});
    sort(val+1,val+n+1);
    for(i=1;i<=n;++i){
        rk[id[i]]=i;
    }
    for(i=2;i+1<=n;++i){
        l[i]=min(h[i-1],h[i+1]); 
        r[i]=max(h[i-1],h[i+1]); 
        rkl[i]=lower_bound(val+1,val+n+1,l[i])-val;
        rkr[i]=upper_bound(val+1,val+n+1,r[i])-val-1; 
    }
}

void CheckForSpecailCases(){
    int i;
    for(i=2;i<=n;++i)raw+=abs(h[i]-h[i-1]); 
    for(i=1;i<=n;++i)res[i]=raw; 
    for(i=1;i<n;i++)cmin(res[i],cal(i,i+1));
    for(i=2;i<=n;i++)cmin(res[i],cal(i,i-1));
    for(i=2;i<=n;i++)cmin(res[1],cal(1,i)),cmin(res[i],cal(1,i));
    for(i=1;i<n;i++)cmin(res[n],cal(n,i)),cmin(res[i],cal(n,i));
}

namespace ST{
#define ls (v<<1)
#define rs (v<<1^1)
#define mid ((l+r)>>1)
    const int S=N<<2; 
    struct D { ll a[3]; } t[S],temp;
    int st,ed,pos; 
    void up(int v){
        R(k,3) t[v].a[k]=min(t[ls].a[k],t[rs].a[k]); 
    }
    void setInf(){
        R(k,3) temp.a[k]=INF;
    }
    void clear(){
        memset(t,0x3f,sizeof(t));
        setInf(); 
    }
    D& get() { return temp; }
    void _update(int v,int l,int r){
        if(r<pos||l>pos);
        else if(l==pos&&r==pos){
            t[v]=temp; 
        }else{
            _update(ls,l,mid);
            _update(rs,mid+1,r); 
            up(v); 
        }
    }
    void update(int _pos){ pos=_pos,_update(1,1,n); }
    void _query(int v,int l,int r){
        if(r<st||l>ed)return;
        else if(st<=l&&r<=ed){
            R(k,3) cmin(temp.a[k],t[v].a[k]); 
        }else{
            _query(ls,l,mid); 
            _query(rs,mid+1,r); 
        }
    }
    D query(int l,int r){
        st=l; ed=r; setInf(); 
        _query(1,1,n); 
        return temp;
    }
    /*
    void setInf(){
        R(k,3) temp.a[k]=INF;
    }
    D query(int l,int r){
        setInf(); 
        for(int i=l;i<=r;++i)R(k,3)cmin(temp.a[k],t[i].a[k]); 
        return temp;
    }
    void update(int p){
        t[p]=temp; 
    }
    void clear(){
        memset(t,0x3f,sizeof(t));
        setInf(); 
    }
    D& get() { return temp; }
    */
#undef ls 
#undef rs
#undef mid
}

int top,aj[N]; bool in[N]; 
int ajl[N],ajr[N],ai[N],topl,topr;
void Solve1(){
    int i,k; ST::D ans; 
    ST::clear();
    for(i=2;i+1<=n;++i)
        aj[i]=ai[i]=i;
    sort(ai+2,ai+n,[](int a,int b){ return h[a]>h[b]; }); 
    sort(aj+2,aj+n,[](int a,int b){ return l[a]>l[b]; }); 
    auto setData=[](ST::D &x,int j){
        ll now=g(j); 
        x.a[0]=-now+l[j]+r[j]-2*h[j];
        x.a[1]=-now+l[j]+r[j];
        x.a[2]=-now+l[j]+r[j]+2*h[j]; 
    };
    top=2; 
    memset(in,0,sizeof(in)); 
    for(k=2;k+1<=n;++k){
        i=ai[k]; 
        for(;top+1<=n&&h[i]<=l[aj[top]];++top){
            setData(ST::get(),aj[top]);
            in[aj[top]]=true;
            ST::update(rk[aj[top]]); 
        }

        for(int d=-1;d<=1;++d){
            if(in[i+d]){
                ST::setInf(); 
                ST::update(rk[i+d]);
            }
        }
        ll now=g(i);
        ans=ST::query(1,rkl[i]); 
        cmin(res[i],raw-now+ans.a[0]+l[i]+r[i]-2*h[i]); 
        ans=ST::query(rkl[i],rkr[i]); 
        cmin(res[i],raw-now+ans.a[1]-l[i]+r[i]-2*h[i]); 
        ans=ST::query(rkr[i],n); 
        cmin(res[i],raw-now+ans.a[2]-l[i]-r[i]-2*h[i]); 

        for(int d=-1;d<=1;++d){
            if(in[i+d]){
                setData(ST::get(),i+d); 
                ST::update(rk[i+d]);
            }
        }
    }
}

void Solve2(){
    int i,k; ST::D ans; 
    ST::clear(); 
    for(i=2;i+1<=n;++i)
        aj[i]=ai[i]=i;
    sort(ai+2,ai+n,[](int a,int b){ return h[a]<h[b]; }); 
    sort(aj+2,aj+n,[](int a,int b){ return r[a]<r[b]; }); 
    auto setData=[](ST::D &x,int j){
        ll now=g(j); 
        x.a[0]=-now-l[j]-r[j]-2*h[j]; 
        x.a[1]=-now-l[j]-r[j]; 
        x.a[2]=-now-l[j]-r[j]+2*h[j];
    };
    top=2; 
    memset(in,0,sizeof(in)); 
    for(k=2;k+1<=n;++k){
        i=ai[k]; 

        for(;top+1<=n&&r[aj[top]]<=h[i];++top){
            setData(ST::get(),aj[top]);
            in[aj[top]]=true;
            ST::update(rk[aj[top]]); 
        }

        for(int d=-1;d<=1;++d){
            if(in[i+d]){
                ST::setInf(); 
                ST::update(rk[i+d]);
            }
        }

        ll now=g(i); 
        ans=ST::query(1,rkl[i]); 
        cmin(res[i],ans.a[0]+raw-now+l[i]+r[i]+2*h[i]);
        ans=ST::query(rkl[i],rkr[i]); 
        cmin(res[i],ans.a[1]+raw-now-l[i]+r[i]+2*h[i]); 
        ans=ST::query(rkr[i],n); 
        cmin(res[i],ans.a[2]+raw-now-l[i]-r[i]+2*h[i]); 

        for(int d=-1;d<=1;++d){
            if(in[i+d]){
                setData(ST::get(),i+d); 
                ST::update(rk[i+d]);
            }
        }
    }
}

void Solve3(){
    int i,k; ST::D ans; 
    ST::clear(); 
    for(i=2;i+1<=n;++i)
        ajl[i]=ajr[i]=ai[i]=i;
    sort(ai+2,ai+n,[](int a,int b){ return h[a]<h[b]; }); 
    sort(ajl+2,ajl+n,[](int a,int b){ return l[a]<l[b]; }); 
    sort(ajr+2,ajr+n,[](int a,int b){ return r[a]<r[b]; }); 
    auto setData=[](ST::D &x,int j){
        ll now=g(j); 
        x.a[0]=-now-l[j]+r[j]-2*h[j]; 
        x.a[1]=-now-l[j]+r[j]; 
        x.a[2]=-now-l[j]+r[j]+2*h[j];
    };
    topl=topr=2; 
    memset(in,0,sizeof(in)); 
    for(k=2;k+1<=n;++k){
        i=ai[k]; 

        for(;topl+1<=n&&h[i]>=l[ajl[topl]];++topl){
            setData(ST::get(),ajl[topl]);
            in[ajl[topl]]=true;
            ST::update(rk[ajl[topl]]); 
        }
        for(;topr+1<=n&&r[ajr[topr]]<h[i];++topr){
            ST::setInf(); 
            in[ajr[topr]]=false;
            ST::update(rk[ajr[topr]]); 
        }

        for(int d=-1;d<=1;++d){
            if(in[i+d]){
                ST::setInf(); 
                ST::update(rk[i+d]);
            }
        }

        ll now=g(i); 
        ans=ST::query(1,rkl[i]); 
        cmin(res[i],ans.a[0]+raw-now+l[i]+r[i]);
        ans=ST::query(rkl[i],rkr[i]); 
        cmin(res[i],ans.a[1]+raw-now-l[i]+r[i]); 
        ans=ST::query(rkr[i],n); 
        cmin(res[i],ans.a[2]+raw-now-l[i]-r[i]); 

        for(int d=-1;d<=1;++d){
            if(in[i+d]){
                setData(ST::get(),i+d); 
                ST::update(rk[i+d]);
            }
        }
    }

}

int main(int argc,char *argv[]){
#ifndef ONLINE_JUDGE
    freopen("dat.in","r",stdin); 
    freopen("my.out","w",stdout); 
#endif
    int i;
    ReadData(); 
    Init(); 
    if(n<=2) { 
        ll t=abs(h[1]-h[2]); 
        printf("%lld\n%lld\n",t,t); 
        return 0; 
    }
    CheckForSpecailCases(); 
    Solve1(); 
    Solve2(); 
    Solve3(); 
    for(i=1;i<=n;++i)printf("%lld\n",res[i]); 
    return 0; 
}
```

---

