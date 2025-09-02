# [ARC085F] NRE

## 题目描述

你有两个长度为 $n$ 的数组 $a, b$，其中 $a$ 初始全 $0$ ，$b$ 是给定的由 $0$ 和 $1$ 组成的数组。

你还有 $q$ 种操作，每种操作形如一个区间 $[l,r]$，表示将 $a$ 数组的 $[l,r]$ 区间内的值全部赋为 $1$。

请通过执行 $q$ 种操作中的若干种，最小化满足 $a_i \ne b_i$ 的位置个数。

## 说明/提示

- $1 \le n,q \le 2 \times 10^5$
- $\forall i \in [1,q], 1 \le l_i \le r_i \le n$
- 所有 $[l_i,r_i]$ 互不相同。

## 样例 #1

### 输入

```
3
1 0 1
1
1 3```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 0 1
2
1 1
3 3```

### 输出

```
0```

## 样例 #3

### 输入

```
3
1 0 1
2
1 1
2 3```

### 输出

```
1```

## 样例 #4

### 输入

```
5
0 1 0 1 0
1
1 5```

### 输出

```
2```

## 样例 #5

### 输入

```
9
0 1 0 1 1 1 0 1 0
3
1 4
5 8
6 7```

### 输出

```
3```

## 样例 #6

### 输入

```
15
1 1 0 0 0 0 0 0 1 0 1 1 1 0 0
9
4 10
13 14
1 7
4 14
9 11
2 6
7 8
3 12
7 13```

### 输出

```
5```

## 样例 #7

### 输入

```
10
0 0 0 1 0 0 1 1 1 0
7
1 4
2 5
1 3
6 7
9 9
1 5
7 9```

### 输出

```
1```

# 题解

## 作者：Skyjoy (赞：9)

upd ：修改了一些笔误

模拟赛见到了这道题并意外地做了出来。赛时觉得好像是我看到过但没去做的一道 ARC 的题，赛后发现还真的是 ARC 的原题。这题挺有意思的，写篇题解纪念一下。

# 思路

- 首先有一个很显然的 dp 思路。我们先讲区间按左端点排序。设 $f_i$ 表示我们考虑完前 $i$ 个区间并**接受第 $i$ 个区间**时**全局的**最小海明距离。然后我们往 $i$ 前面枚举区间 $j$ 。假设原数组的前缀和数组为 $sum$ ，第 $i$ 个区间所对应的集合为 $S_i$ ，那么我们可以得到下面的柿子：

$$f_i=\begin{cases}
\min{f_j+r_i-l_i+1-2(sum_{r_i}-sum_{l_i-1})},S_i\cap S_j=\varnothing\\
\min{f_j+r_i-r_j-2(sum_{r_i}-sum_{r_j})},S_i\cap S_j\neq\varnothing\ \text{且}\ S_i\subsetneq S_j\\
\min{f_j},S_i\subseteq S_j
\end{cases}$$

- 最后答案就是 $f_i$ 的最小值了。因为求的是所有 $f_i$ 的最小值，所以上述转移方程中的第 3 条显然可以忽略，只需要前 2 条就可以转移了。如果暴力转移的话复杂度是 $O(q^2)$ 的，那么怎么优化呢？

- 我们发现冗余的操作主要是出现在取 $\min$ 部分的，所以我们要将这一部分简化。由于我们将区间按左端点排序，我们发现，当 $j<i$ 时， $S_i\cap S_j=\varnothing$ 的充要条件是 $r_j<l_i$ ， $S_i\cap S_j\neq\varnothing\ \text{且}\ S_i\subsetneq S_j$ 的充要条件是 $r_j\in [l_i,r_i]$ 。所以我们只需要建两棵线段树分别维护两个方程就可以了。

- 具体地，我们根据区间的值域开线段树，当我们枚举到区间 $i$ 时，我们将 $f_i$ 和 $f_i-r_i+2sum_{r_i}$ 分别插入两棵线段树的 $r_i$ 处即可。查询时查询第 1 棵线段树的 $[1,l_i-1]$ 区间和第 2 棵线段树的 $[l_i,r_i]$ 区间再加上一些方程里的其他值比大小就行了。当然，不要忘了 $f_i$ 一开始是要从 $f_0$ 开始转移的。时间复杂度是 $O(qlog_2n)$ ，可以通过此题。剩下的细节就看代码吧！

# 代码

```cpp
#include<bits/stdc++.h>
#define I using
#define love namespace
#define Elaina std
I love Elaina;
const int N=200010;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,a[N],sum[N],f[N],ans,res;
struct qry{
	int l,r;
	bool operator<(const qry &rhs)const{
		return (l!=rhs.l)?l<rhs.l:r<rhs.r;
	}
}qwq[N];
namespace AyaseEli{
	#define ls(k) (k<<1)
	#define rs(k) (k<<1|1)
	struct node{
		int minn,l,r;
	}tree[2][N<<2];
	void pushup(node *tree,int k){
		tree[k].minn=min(tree[ls(k)].minn,tree[rs(k)].minn);
	}
	void build(node *tree,int k,int l,int r){
		tree[k].l=l,tree[k].r=r,tree[k].minn=0x3f3f3f3f;
		if(l==r)return;
		int mid=(l+r)/2;
		build(tree,ls(k),l,mid),build(tree,rs(k),mid+1,r);
		pushup(tree,k);
	}
	void modify(node *tree,int k,int q,int v){
		if(tree[k].l==tree[k].r){
			tree[k].minn=v;
			return;
		}
		int mid=(tree[k].l+tree[k].r)/2;
		if(q<=mid)modify(tree,ls(k),q,v);
		else modify(tree,rs(k),q,v);
		pushup(tree,k);
	}
	int query(node *tree,int k,int ql,int qr){
		int res=0x3f3f3f3f;
		if(ql<=tree[k].l&&tree[k].r<=qr)return tree[k].minn;
		int mid=(tree[k].l+tree[k].r)/2;
		if(ql<=mid)res=min(res,query(tree,ls(k),ql,qr));
		if(mid<qr)res=min(res,query(tree,rs(k),ql,qr));
		return res;
	}
}
I love AyaseEli;
int main(){
	memset(f,0x3f,sizeof(f));
	n=read();
	build(tree[0],1,1,n),build(tree[1],1,1,n);
	for(int i=1;i<=n;i++)a[i]=read(),sum[i]=sum[i-1]+a[i];
	ans=sum[n];
	m=read();
	for(int i=1;i<=m;i++)qwq[i]=(qry){read(),read()};
	sort(qwq+1,qwq+m+1);
	for(int i=1;i<=m;i++){
        f[i]=sum[n]+qwq[i].r-qwq[i].l+1-2*(sum[qwq[i].r]-sum[qwq[i].l-1]);
		if(qwq[i].l!=1)f[i]=min(f[i],query(tree[0],1,1,qwq[i].l-1)+qwq[i].r-qwq[i].l+1-2*(sum[qwq[i].r]-sum[qwq[i].l-1]));
		f[i]=min(f[i],query(tree[1],1,qwq[i].l,qwq[i].r)+qwq[i].r-2*sum[qwq[i].r]);
		modify(tree[0],1,qwq[i].r,f[i]),modify(tree[1],1,qwq[i].r,f[i]-qwq[i].r+2*sum[qwq[i].r]);
		ans=min(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}
```

祝各位大神们 NOI 加油！

---

## 作者：奇米 (赞：9)

## 题解- $AT3673 [ARC085D] NRE$

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)


* **题目意思**

	就是你原有一个全是$0$的序列$a$，有$m$个操作，你可以选取其中任意多个，每次操作$(l,r)$，即把$a_l-a_r$的值变为$1$，问$\sum a_i≠b_i$。
    
* $Sol$
	
    一道比较难的思维+数据结构题。
    
    首先我们把$a_i,b_i$看作一个二元组$(a,b)$,其实对答案的贡献$\sum\limits_{i=1}^n(0,1) +\sum\limits_{i=1}^n(1,0)$。同时我们又可以把这个柿子化为$\sum\limits_{i=1}^n(0,1) +\sum\limits_{i=1}^n(?,0)-\sum\limits_{i=1}^n(0,0)$。于是其实现在已经和$(1,?)$没关系了。
    
    于是我们就开始$DP$，设$f_i$表示前$i$个数使得$[(0,1)-(0,0)]$最小值。我们可以用线段树来优化（只要分选或不选的情况即可），具体的$f_i=f_{i-1}+(a[i])?1:-1$，因为由$[(0,1)-(0,0)]$可知，还是比较显然的。
    
    这道题目总体来说还是挺难的，关键是这个思路的转化。
    
    
* $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=2e5+5;

int n,m,suf[N][2],laz[N<<2],tr[N<<2];
int ans,a[N],f[N];
vector<int> po[N];

struct nood
{
	int l,r;
	inline bool friend operator < (const nood&c,const nood &d)
	{
		return c.l<d.l;
	}
};
nood c[N];

inline int min(int x,int y) 
{
	return (x>y)?y:x;
}

inline void build(int rt,int l,int r)
{
	tr[rt]=1e9;
	if(l==r) return;
	int mid=(l+r)/2;
	build(rt<<1,l,mid); 
	build(rt<<1|1,mid+1,r);
	tr[rt]=min(tr[rt<<1],tr[rt<<1|1]);
}

inline void modify(int rt,int l,int r,int pos,int val)
{
	if(l==r)
	{
		tr[rt]=min(tr[rt],val);
		return;
	}
	int mid=(l+r)/2;
	if(pos<=mid) modify(rt<<1,l,mid,pos,val);
	else modify(rt<<1|1,mid+1,r,pos,val);
	tr[rt]=min(tr[rt<<1],tr[rt<<1|1]);
}

inline int query(int rt,int l,int r,int ll,int rr)
{
	if(ll<=l&&r<=rr) return tr[rt];
	int mid=(l+r)/2;
	int ret=1e9;
	if(ll<=mid) ret=min(ret,query(rt<<1,l,mid,ll,rr));
	if(rr>mid) ret=min(ret,query(rt<<1|1,mid+1,r,ll,rr));
	return ret;
}

signed main()
{
	n=read();
	for ( int i=1;i<=n;i++ ) 
	{
		int x=read();
		a[i]=x;
		suf[i][0]=suf[i-1][0]+(x==0);
		suf[i][1]=suf[i-1][1]+(x==1);
	}
	memset(f,127/3,sizeof(f));
	m=read();
	for ( int i=1;i<=m;i++ ) c[i]=(nood){read(),read()};
	sort(c+1,c+m+1);
	for ( int i=1;i<=m;i++ ) po[c[i].l].push_back(c[i].r);
	f[0]=0;
	build(1,1,n);
	for ( int i=1;i<=n;i++ ) 
	{
		for ( int j=0;j<po[i].size();j++ )
		{
			int r=po[i][j];
			int mi=f[i-1];
			mi=min(mi,query(1,1,n,max(i-1,1),r));
			if(mi<f[r])
			{
				f[r]=mi;
				modify(1,1,n,r,mi);
			}
		}
		f[i]=min(f[i],f[i-1]+((a[i]==1)?1:-1));
	}
	printf("%d\n",f[n]+suf[n][0]);
	return 0;
}

	
			 
```


---

## 作者：wwlw (赞：6)

### Descrption
给定序列 $\{a_n\}$，值域为 $\{0,1\}$，和 $m$ 种操作，每个操作可以将 $\{b_n\}$ 的某个区间全部赋为一（$b_i$ 初始时全为零）。最小化 $\sum_{i=1}^n [a_i\neq b_i]$

### Solution

可以看作最大化 $\sum_{i=1}^n [a_i=b_i]$，初始的答案是 0 的个数。考虑赋值操作对答案的影响，原来为 0，贡献就是 -1，原来是 1，贡献就是 1，记为 $c_i$。所以问题就转换为可以使得一个区间的元素都被选择，要使得最后被选择的所有元素的权值和最大。

那就有点类似背包了，但是会有交集的问题，所以考虑按右端点排序，分类讨论。令 $f_i$ 表示将第 $i$ 个区间作为结尾的最大权值和。那么就有两种情况。
  1. 两个区间无交集，可以直接转移，$f_i=f_j+S_{r_i}-S_{l_i-1}$
  2. 区间有交集，但不能有完全覆盖，$f_i=f_j+S_{r_i}-S_{r_j}$
考虑形式化这些限制条件。第一个就是 $r_j <l_i\leq r_i$，第二个是 $r_j\leq r_i$、$r_j\geq l_i$ 并且 $l_j<l_i$。发现是个三维偏序，所以无脑 CDQ 分治就可了。

```cpp
#include<stdio.h>
#include<algorithm>
#include<cassert>
using namespace std;

typedef long long ll;

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

const int N=2e5+7;

struct Seg{
    int l,r,dp;
}a[N];

int s[N],c[N],n;

inline bool Cmp1(const Seg &X,const Seg &Y){return X.r<Y.r;}
inline bool Cmp2(const Seg &X,const Seg &Y){return X.l<Y.l;}

inline int lowbit(int x){return -x&x;}
inline void add(int x,int v){while(x<=n) c[x]=max(c[x],v),x+=lowbit(x);}
inline int query(int x){int ret=-n;while(x)ret=max(ret,c[x]),x-=lowbit(x);return ret;}
inline void Clear(int x){while(x<=n)c[x]=-n,x+=lowbit(x);}

void CDQ(int lf,int rf){
    if(lf==rf) return ;
    int mid=(lf+rf)>>1; CDQ(lf,mid);
    sort(a+mid+1,a+rf+1,Cmp2);
    for(int i=mid+1,ret=0,j=lf;i<=rf;i++){
        while(j<=mid&&a[j].r<=a[i].l)
            ret=max(ret,a[j].dp),j++;
        a[i].dp=max(a[i].dp,ret+s[a[i].r]-s[a[i].l]);
    }
    sort(a+lf,a+mid+1,Cmp1); int j=mid;
    for(int i=rf;i>mid;i--){
        while(j>=lf&&a[j].r>a[i].l)
            add(a[j].l+1,a[j].dp-s[a[j].r]),j--;
        a[i].dp=max(a[i].dp,query(a[i].l)+s[a[i].r]);
    }
    for(int i=mid;i>j;i--) Clear(a[i].l+1);
    sort(a+mid+1,a+rf+1,Cmp1);
    CDQ(mid+1,rf);
}

int main(){
    n=read(); int ans=0;
    for(int i=1,x;i<=n;i++)
        s[i]=((x=read())? 1:-1)+s[i-1],ans+=x;
    int m=read();
    for(int i=1;i<=n;i++) c[i]=-n;
    for(int i=1;i<=m;i++)
        a[i].l=read()-1,a[i].r=read(),a[i].dp=-n;
    a[++m]=(Seg){0,0,0},sort(a+1,a+1+m,Cmp1),CDQ(1,m);
    int ret=0; for(int i=1;i<=m;i++) ret=max(ret,a[i].dp);
    printf("%d",ans-ret);
}
```


---

## 作者：mazihang2025 (赞：4)

### 题目大意:

你有一个全 0 序列 a , 给出一个 0/1 序列 b 和一些区间 [ l , r ]，任意选择一些区间令 a[ l , r ]=1 ,求 $a$ 和 $b$ 最少有多少个数不同。

### 思路：

不同数最少不是很好做，所以可转换为相同数最多，答案就为 $n-k$ 。初始相同数为 b 中 0 的个数，如果 b[ i ]=1 修改后就会加1，否则减1。S[ i ] 为修改 [ 1 , i ] 对相同数的影响。

考虑 dp，现将区间按右端点升序排序，保证 dp 无后效性。

$$dp[i]=dp[j]+s[r[i]]-s[l[i]-1](j < i, r[j]<l[i])$$
$$dp[i]=dp[j]+s[r[i]]-s[r[j]](j<i,r[j]\geq l[i])$$

如果 $l[j]\geq l[i],r[j]\leq r[i]$ 则对答案没有贡献。

很明显，可以用数据结构优化转移方程，考虑线段树。

因为两个方程不太相同，所以建立两棵线段树，分别维护两个方程。

第一个维护 dp[ j ] 的最大值，每个区间只会对右端点之后的区间有贡献。第二个维护 dp[ j ] - s[ r[ j ] ] 的最大值，对左端点在 l[ j ] 到 r[ j ] 之间的区间有贡献。

注意第一个方程要考虑前面不选区间的转移。

### code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() {
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
void put(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) put(x/10);
	putchar(x%10^48);
}
const int Maxn=2e5+10,inf=1e9;
int n,sum,res,m;
int a[Maxn];
struct node {
	int l,r;
	bool operator <(const node &b) const {
		return r!=b.r?r<b.r:l<b.l;
	}
}d[Maxn];
struct Tree {
	#define ls (x<<1)
	#define rs (x<<1|1)
	#define mid (l+r>>1)
	int t[Maxn<<2],tag[Maxn<<2];
	void build(int x,int l,int r) {
		t[x]=tag[x]=-inf;
		if(l==r) return;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void pushdown(int x) {
		t[ls]=max(t[ls],tag[x]),tag[ls]=max(tag[ls],tag[x]);
		t[rs]=max(t[rs],tag[x]),tag[rs]=max(tag[rs],tag[x]);
		tag[x]=-inf;
	}
	void modify(int x,int l,int r,int L,int R,int v) {
		if(L>R) return;
		if(l>=L&&r<=R) {
			t[x]=max(t[x],v),tag[x]=max(tag[x],v);
			return;
		}
		pushdown(x);
		if(mid>=L) modify(ls,l,mid,L,R,v);
		if(mid<R) modify(rs,mid+1,r,L,R,v);
		t[x]=max(t[ls],t[rs]);
	}
	int ask(int x,int l,int r,int p) {
		if(l==r) return t[x];
		pushdown(x);
		if(mid>=p) return ask(ls,l,mid,p);
		return ask(rs,mid+1,r,p);
	}
}t1,t2;
signed main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i) 
		a[i]=a[i-1]+(read()?1:-1);
	sum=(n-a[n])/2;
	m=read(),res=sum;
	for(int i=1;i<=m;++i) d[i].l=read(),d[i].r=read();
	sort(d+1,d+m+1);
	t1.build(1,0,n),t2.build(1,1,n);
	t1.modify(1,0,n,0,n,sum);
	for(int i=1;i<=m;++i) {
		int x=t1.ask(1,0,n,d[i].l)+a[d[i].r]-a[d[i].l-1];
		x=max(x,t2.ask(1,1,n,d[i].l)+a[d[i].r]);
		t1.modify(1,0,n,d[i].r+1,n,x);
		t2.modify(1,1,n,d[i].l,d[i].r,x-a[d[i].r]);
		res=max(res,x);
	}
	put(n-res);
	return 0;
}
```


---

## 作者：Purslane (赞：2)

# Solution

线段树优化 DP 板子题。

我们可以计算出每个位置被覆盖后的贡献，一个 $\pm 1$  序列 $v$。因此问题转化为选择若干个区间，使得这些区间的并覆盖的点的权值最大。

设 $dp_{l,r}$ 表示考虑了所有左端点 $\le l$ 的线段，目前覆盖的最右端的点是 $r$，点权和的最大值。特别的，如果 $r=l-1$ 表示 $l$ 点没有被覆盖。

注意到此时 $[l,r]$ 里面所有点都被覆盖了。因此如果要加入 $(l,R)$ 转移到 $dp_{l,R}$，应有：

$$
dp_{l,R} = \max_{l-1 \le j \le R} dp_{l-1,j} + \sum_{i=j+1}^R v_i
$$

把 $v$ 求前缀和得到 $pre$，有：

$$
dp_{l,R} - pre_R = \max_{l-1 \le j \le R} dp_{l-1,j} - pre_j
$$

特别的，$dp_{l,l-1}$ 可以由 $dp_{l-1,l-2}$ 转移而来。

使用线段树可以简单维护。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200000+10;
int n,q,b[MAXN],cnt,v[MAXN],ans,mx[MAXN<<2];
vector<int> G[MAXN];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void update(int k,int l,int r,int pos,int v) {
	if(l==r) return mx[k]=min(mx[k],v),void();
	if(pos<=mid) update(lson,l,mid,pos,v);
	else update(rson,mid+1,r,pos,v);
	return mx[k]=min(mx[lson],mx[rson]),void();
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return mx[k];
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return min(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>b[i];
	ffor(i,1,n) if(b[i]==1) cnt++,v[i]=-1+v[i-1]; else v[i]=1+v[i-1];
	memset(mx,0x3f,sizeof(mx)),update(1,0,n,0,0),cin>>q;
	ffor(i,1,q) {int l,r;cin>>l>>r,G[l].push_back(r);}
	ffor(i,1,n) {
		if(i!=1) update(1,0,n,i-1,query(1,0,n,i-2,i-2)+v[i-2]-v[i-1]);
		for(auto r:G[i]) {
			int val=query(1,0,n,i-1,r)+v[r];
			ans=min(ans,val),update(1,0,n,r,val-v[r]);	
		}
	}
	cout<<cnt+ans;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
一道比较典的题目。
# 思路
首先可以考虑 dp，但是我们发现如果区间不排序将会有后效性所以考虑将区间按右端点排序，然后我们定义 $f_i$ 表示现在选到了第 $i$ 个区间第 $i$ 个必选的 $\sum (a_i=b_i)$ 的最大值（题目求的是不等于的最小值，转换一下就是这个），考虑转移，发现要分情况，下文都将上一个选的区间定义为 $j$。

- 当 $i$ 与 $j$ 区间包含时，我们发现 $j$ 的存在并没有意义所以无需转移。
- 当 $i$ 与 $j$ 无交集时，$f_i=f_j+sum_{1,r_i}-sum_{1,l_i-1}+sum_{0,l_{i}-1}-sum_{0,r_j}$，此时的条件为 $r_j<l_i$，柿子中的 $sum_{i,j}$ 表示在 $1\sim j$ 中 $b_x=i$ 的 $x$ 的数量。
- 当 $i$ 与 $j$ 有交集时，$f_{i}=f_j+sum_{1,r_i}-sum_{1,r_j}$ 此时的条件为 $l_j<l_i\leq r_j\leq r_i$。

上述过程用暴力实现是 $n^2$ 的所以考虑优化，我们发现后两种情况分别是二维偏序和三维偏序，所以考虑直接用 cdq 去维护。

注：此 cdq 的 $mid+1\sim r$ 这一段区间必须要在 $l\sim r$ 中不在同一边的答案已经求过之后再去递归，不然后面的前一段都没有值，无法转移。还要注意初始将树状数组中的最大值都赋为极小的。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
const int N=2e5+10;
struct nodes{
	int l,r,f;
}s[N];
int tr[N];
bool cmp(nodes a,nodes b) {
	return a.r<b.r;
}
bool cmp1(nodes a,nodes b) {
	return a.l<b.l;
}
int b[N],sum[N],n,m,f[N],sum0[N];
int tt[N];
int lowbit(int x) {
	return x&-x;
}
void add(int x,int k) {
	for(;x<=n;x+=lowbit(x)) tt[x]=max(tt[x],k);
}
void modify(int x,int k) {
	for(;x<=n;x+=lowbit(x)) tr[x]=max(tr[x],k);
}
int Ans(int x) {
	int res=-INT_MAX;
	for(;x;x-=lowbit(x)) res=max(tr[x],res);
	return res;
}
int Ans1(int x) {
	int res=-INT_MAX;
	for(;x;x-=lowbit(x)) res=max(res,tt[x]);
	return res;
}
void clear1(int x,int k) {
	for(;x<=n;x+=lowbit(x)) tr[x]=k;
}
void clear(int x,int k) {
	for(;x<=n;x+=lowbit(x)) tt[x]=k;
}
void get(int l,int r) {
	if(l>=r) {
		if(l==r) s[l].f=max(s[l].f,sum[s[l].r]-sum[s[l].l-1]+sum0[s[l].l-1]);
		return;
	}
	int mid=l+r>>1;
	get(l,mid);
	sort(s+l,s+1+mid,cmp1);
	sort(s+mid+1,s+r+1,cmp1);
	rep(i,l,r) {
		if(i>=mid+1) s[i].f=max(s[i].f,Ans(s[i].l-1)+sum[s[i].r]-sum[s[i].l-1]+sum0[s[i].l-1]);
		if(i<=mid) modify(s[i].r,s[i].f-sum0[s[i].r]);
	}
	rep(i,l,mid) clear1(s[i].r,-INT_MAX);
	int j=l;
	rep(i,mid+1,r) {
		while(s[j].l<s[i].l&&j<=mid) {
			add(n-s[j].r+1,s[j].f-sum[s[j].r]);
			j++;
		}
		s[i].f=max(s[i].f,Ans1(n-s[i].l+1)+sum[s[i].r]);
	}
	rep(k,l,j-1) clear(n-s[k].r+1,-INT_MAX);
	sort(s+mid+1,s+r+1,cmp);
	get(mid+1,r);
}
void solve() {
	in(n);
	rep(i,1,n) in(b[i]);
	in(m);
	rep(i,1,m) in(s[i].l),in(s[i].r);
	sort(s+1,s+1+m,cmp);
	rep(i,1,n) sum[i]=sum[i-1]+(b[i]==1),sum0[i]=sum0[i-1]+(b[i]==0);
	rep(i,1,n) tr[i]=tt[i]=-INT_MAX;
	get(1,m);
	int res=sum0[n];
	rep(i,1,m) {
		res=max(res,s[i].f+sum0[n]-sum0[s[i].r]);
	}
	printf("%lld\n",n-res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：RainFestival (赞：1)

$\rm unofficial~rating=\color{red} 3049$

我们首先把问题转化为选取一些操作后，$a_i=b_i$ 的 $i$ 数量最多。

**注意到操作的顺序是没有关系的**，所以我们可以按照我们喜欢的顺序考虑每一个操作。

**我们把操作按照 $r$ 从小到大进行排序**，依次考虑每一个操作。

记 $s(l,r)$ 为把 $[l,r]$ 这个区间的所有数字全部改成 $1$ 之后，对答案的贡献，如果 $l>r$ 那么 $s(l,r)=0$。

那么 $s(l,r)=b_l\dots r$ 中 $1$ 的个数 $-$ $0$ 的个数。利用前缀和优化，我们可以在 $\mathcal{O(1)}$ 的时间算出任意一个 $s(l,r)$ 的值。

我们记 $dp_i$ 的值为选取的线段中最后一条线段的右端点为 $i$ 的最大答案，$t_i$ 为选取最后一条线段为 $i$ 的最大答案。

记最终选取线段集合为 $S$，那么我们发现 $S$ 中的线段**不存在包含的情况**，只有相离与相交。

我们假设现在正在考虑线段 $i$，如果最优方案中，上一条选取线段为 $j$，那么我们分**两**种情况讨论：

+ $l_j\le r_j<l_i\le r_i$

这时候，线段 $j$ 对线段 $i$ 所包含的区间没有任何影响。于是我们不用关心 $j$ 是哪条线段，只用关心 $r_j<l_i$ 即可。

于是这一种情况的答案 $w_1=s(l_i,r_i)+\max\limits_{k=1}^{l_i-1}{dp_k}$。

我们记 $ps_i=\max\limits_{k=1}^{i}{dp_k}$，那么 $w_1=s(l_i,r_i)+ps_{l_i-1}$。

+ $l_j\le l_i\le r_j\le r_i$


这个时候，$r_i$ 的贡献就没有那么大了。它会受到 $j$ 的影响，具体来说，贡献为 $s(r_j+1,r_i)$。当 $r_i=r_j$ 时，可能出现 $j$ 包含 $i$。

所以，我们来看一看总贡献：

$w_2=\max\limits_{l_j\le l_i\le r_j< r_i} t_j+s(r_j+1,r_i)$

我们把式子拆开，得到

$w_2=s(1,s_i)+\max\limits_{1\le l_j\le l_i,l_i\le r_j\le r_i} t_j-s(1,r_j)$

前半部分只和 $i$ 有关，容易计算；

后半部分我们发现，如果 $(l_j,r_j)$ 这个点表示 $j$ 的话，那么符合条件的 $j$ 的对应的点 $(l_j,r_j)$ 在矩形 $(1\dots l_i,l_i\dots r_i)$，相当于在一个矩形中查询最值。由于第一维的左边界始终为 $1$，所以我们考虑用树状数组套线段树的方式解决这个问题。

至此，两种情况都解决了。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
struct node
{
	int ls,rs,s;
};
node a[20000005];
int n,q,cnt=0,rt[200005];
void pushup(int k)
{
	a[k].s=-1000000000;
	if (a[k].ls) a[k].s=std::max(a[k].s,a[a[k].ls].s);
	if (a[k].rs) a[k].s=std::max(a[k].s,a[a[k].rs].s);
}
int qry(int &k,int x,int y,int l,int r)
{
	if (!k) return -1000000000;
	if (x<=l&&r<=y) return a[k].s;
	int mid=(l+r)/2,ans=-1000000000;
	if (x<=mid) ans=std::max(ans,qry(a[k].ls,x,y,l,mid));
	if (mid<y) ans=std::max(ans,qry(a[k].rs,x,y,mid+1,r));
	return ans;
}
void update(int &k,int x,int val,int l,int r)
{
	if (!k) k=++cnt,a[k].s=-1000000000;
	if (l==r) return a[k].s=std::max(a[k].s,val),void();
	int mid=(l+r)/2;
	if (x<=mid) update(a[k].ls,x,val,l,mid);
	if (mid<x) update(a[k].rs,x,val,mid+1,r);
	pushup(k);
}
std::vector<int> p;
int lowbit(int x){return x&(-x);}
void getask(int x)
{
	p.clear();
	for (;x>=1;x=x-lowbit(x)) p.push_back(x);
}
void getupd(int x)
{
	p.clear();
	for (;x<=n;x=x+lowbit(x)) p.push_back(x);
}
int ask(int id,int x,int y)
{
	getask(id);
	int ans=-1000000000;
	for (int i=0;i<(int)p.size();i++) ans=std::max(ans,qry(rt[p[i]],x,y,1,n));
	return ans;
}
void upd(int id,int x,int val)
{
	getupd(id);
	for (int i=0;i<(int)p.size();i++) update(rt[p[i]],x,val,1,n);
}
int f[200005],s[200005],dp[200005],ps[200005],ans=0;
struct query
{
	int l,r;
};
int cmp(query x,query y){return x.r<y.r;}
query qq[200005];
int calc(int x,int y)
{
	int d=s[y]-s[x-1],len=y-x+1;
	return 2*d-len;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&f[i]),s[i]=s[i-1]+f[i];
	scanf("%d",&q);
	for (int i=1;i<=q;i++) scanf("%d%d",&qq[i].l,&qq[i].r);
	std::sort(qq+1,qq+q+1,cmp);
	ps[0]=dp[0]=n-s[n];
	int now=1;
	for (int i=1;i<=n;i++)
	{
		while (now<=q&&qq[now].r==i)
		{
			int x=qq[now].l,y=qq[now].r;
			int w1=ps[x-1]+calc(x,y);
			int w2=ask(x,x,y)+calc(1,y);
			int ss=std::max(w1,w2);
			upd(x,y,ss-calc(1,i));
			dp[i]=std::max(dp[i],ss);
			++now;
		}
		ps[i]=std::max(ps[i-1],dp[i]);
	}
	for (int i=0;i<=n;i++) ans=std::max(ans,dp[i]);
	printf("%d\n",n-ans);
	return 0;
}
```

用时 $\tt 73s$，花费 $\tt 205.93MB$ 内存，代码长度 $\tt 2.13KB$。

---

## 作者：TLE_AK (赞：0)

#### 前言
一种更显然的 dp 思路。
### 题意
有一个全是 $0$ 的长度为 $n$ 的序列 $A$，给你一个长度为 $n$ 的 $01$ 序列 $B$ 与 $q$ 个区间，你可以任意选取对应的区间铺成 $1$，求最少有多少 $i$ 满足 $A_i \ne B_i$。

## 思路
为了方便处理，我们把求最少不等改为求最多相等，最后只要减去即可。

发现不好贪心，考虑动态规划，设 $dp_{i,j}$ 表示考虑第 $i$ 个数，现在**必须**覆盖 $1$ 到第 $j$ 个数。  
想一下转移：

- 当 $B_i=0$，有 $dp_{i,j}=dp_{i-1,j}+[i<j])$。
- 当 $B_i=1$，有 $dp_{i,j}=dp_{i-1,j}+[j\ge i])$。
- 当有操作的左端点于 $i$ 时，$dp_{i,j}=\max dp_{i-1,k}(0 \le k \le r)$。

发现 $i$ 这一维可以被滚掉，剩下一维可以线段树优化，然后就做完啦！
## 代码
```
#include<bits/stdc++.h>
using namespace std;

namespace acac
{
	int A[200010];
	 
	struct node
	{
		int l,r;	
	}line[200010];
	
	bool cmp(node a,node b)
	{
		if(a.l==b.l)return a.r<b.r;
		return a.l<b.l;
	}
	
	int tree[800010][3];
	
	void pd(int u)
	{
		if(tree[u][1])
		{
			tree[2*u][0]+=tree[u][1];
			tree[2*u+1][0]+=tree[u][1];
			tree[2*u][1]+=tree[u][1];
			tree[2*u+1][1]+=tree[u][1];
			tree[u][1]=0;
		}
	}
	
	void pu(int u)
	{
		tree[u][0]=max(tree[2*u][0],tree[2*u+1][0]);
	}
	
	void build(int u,int l,int r)
	{
		if(l==r)
		{
			if(l==0)tree[u][0]=0;
			else tree[u][0]=-1e9;
			return ;
		}
		int mid=(l+r)>>1;
		build(2*u,l,mid);
		build(2*u+1,mid+1,r);
		pu(u);
	}
	//这里线段树偷了个懒，当dp数组用了 
	void c(int u,int l,int r,int L,int R,int op,int num)
	{
		if(L>R||L>r||l>R)return ;
		if(L<=l&&R>=r)
		{
			if(op)
			{
				tree[u][0]=num;
				return ;
			}
			tree[u][0]++;
			tree[u][1]++;
			return ;
		}
		pd(u);
		int mid=(l+r)>>1;
		c(2*u,l,mid,L,R,op,num);
		c(2*u+1,mid+1,r,L,R,op,num);
		pu(u);
	}
	
	int q(int u,int l,int r,int L,int R)
	{
		if(L>R||L>r||l>R)return -1e9;
		if(L<=l&&R>=r)return tree[u][0];
		pd(u);
		int mid=(l+r)>>1;
		return max(q(2*u,l,mid,L,R),q(2*u+1,mid+1,r,L,R));
	}
	
	int main()
	{
		int n,m;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&A[i]);
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&line[i].l,&line[i].r);
		}
		sort(line+1,line+1+m,cmp);
		build(1,0,n);
		int w=1;
		for(int i=1;i<=n;i++)
		{
			//前两种转移 
			if(A[i])c(1,0,n,i,n,0,0);
			else c(1,0,n,0,i-1,0,0);
			//最后一种 
			while(w<=m&&line[w].l==i)
			{
				int maxn=-1e9;
				if(A[i])maxn=max(q(1,0,n,0,i-1)+1,q(1,0,n,i,line[w].r));
				else maxn=max(q(1,0,n,0,i-1)-1,q(1,0,n,i,line[w].r));
				c(1,0,n,line[w].r,line[w].r,1,maxn);
				w++;
			}
			
		}	
		cout<<n-q(1,0,n,0,n);
		return 0;
	}
}

int main()
{
	acac::main();
	return 0;
}
```

---

