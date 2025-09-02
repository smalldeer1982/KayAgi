# [USACO20FEB] Help Yourself P

## 题目描述

在一个数轴上有 $N$ 条线段，第 $i$ 条线段覆盖了从 $l_i$ 到 $r_i$ 的所有实数（包含 $l_i$ 和 $r_i$）。

定义若干条线段的**并**为一个包含了所有被至少一个线段覆盖的点的集合。

定义若干条线段的**复杂度**为这些线段的并形成的连通块的数目的 $K$ 次方。

现在 Bessie 想要求出给定 $N$ 条线段的所有子集（共有 $2^N$ 个）的复杂度之和对 $10^9+7$ 取模的结果。

你也许猜到了，你需要帮 Bessie 解决这个问题。但不幸的是，你猜错了！在这道题中你就是 Bessie，而且没有人来帮助你。一切就靠你自己了！

## 说明/提示

### 样例解释

所有非空子集的复杂度如下所示（显然空集的复杂度为零）：

$$
\{[1,6]\} \implies 1, \{[2,3]\} \implies 1, \{[4,5]\} \implies 1
$$

$$
\{[1,6],[2,3]\} \implies 1, \{[1,6],[4,5]\} \implies 1, \{[2,3],[4,5]\} \implies 4
$$

$$
\{[1,6],[2,3],[4,5]\} \implies 1
$$

故答案为 $1+1+1+1+1+4+1=10$。

### 子任务

- 测试点 $2$ 满足 $N \leq 16$；
- 测试点 $3 \sim 5$ 满足 $N \leq 10^3$，且 $K=2$；
- 测试点 $6 \sim 8$ 满足 $N \leq 10^3$；
- 对于测试点 $T$（$T \in [9,16]$），满足 $K=3+(T-9)$。

## 样例 #1

### 输入

```
3 2
1 6
2 3
4 5```

### 输出

```
10```

# 题解

## 作者：lahlah (赞：14)

我丢： https://www.luogu.com.cn/problem/P6144


先考虑 k = 1

考虑DP

首先将所有的线段按照左端点排序，考虑 $f[r]$表示最右以$r$结尾的线段集合的连通块的数量的和.

插入一个线段$[l,r]$

对于右端点在$[1,l-1]$的每种情况，都可以使它们的连通块加$1$,再加到$f[r]$里面

对于右端点在$[l,r]$的每种情况，可以直接加到$f[r]$里面
对于右端点在$[r+1,n]$的$f[i]$,要全部*2  (选当前线段或不选)

也就是要一个数据结构，支持区间*2,区间求和，显然线段树


对于$k != 1$, 可以考虑把它的 $[0，k]$次的结果分别维护，计算的时候用二项式定理合并就好了

就是对于$[1,l-1]$的 要把 $x^k -> (x+1)^k$再加到$f[r]$里，这里可以用二项式定理把$[0,k]$次方的结果乘上二项式系数再加起来就好

就是线段树每个点要维护各个次方的结果

看代码好理解一点

code:
```cpp
#include<bits/stdc++.h>
#define N 400005
#define int long long
#define mod 1000000007
using namespace std;
struct haha {
	int a[13];
};
struct A {
	int l, r;
} a[N];
int cmp(A x, A y) {
	return x.l < y.l;
}
int ha[N << 3][12], tag[N << 3], n, k, C[25][25];
void update(int rt) {
	for(int i = 0; i <= k; i ++)
	 	ha[rt][i] = (ha[rt << 1][i] + ha[rt << 1 | 1][i]) % mod;
}
void pushdown(int rt) {
	if(tag[rt] == 1) return;
	tag[rt << 1] *= tag[rt], tag[rt << 1 | 1] *= tag[rt], tag[rt << 1 | 1] %= mod, tag[rt << 1] %= mod;
	int t = 1;
	for(int i = 0; i <= k; i ++) 
		ha[rt << 1][i] *= tag[rt], ha[rt << 1 | 1][i] *= tag[rt], ha[rt << 1][i] %= mod, ha[rt << 1 | 1][i] %= mod;
	tag[rt] = 1;
}	
void add(int rt, int l, int r, int x, haha b) { 
	if(l == r) {
		for(int i = 0; i <= k; i ++) ha[rt][i] = (ha[rt][i] + b.a[i]) % mod;
		return;
	}
	pushdown(rt);
	int mid = (l + r) >> 1;
	if(x <= mid) add(rt << 1, l, mid, x, b);
	else add(rt << 1 | 1, mid + 1, r, x, b);
	update(rt);
}
void mul(int rt, int l, int r, int L, int R) {
	if(L > R) return;
	if(L <= l && r <= R) {
		tag[rt] = tag[rt] * 2 % mod;
		int t = 1;
		for(int i = 0; i <= k; i ++)
			ha[rt][i] = ha[rt][i] * 2 % mod;
		return;
	}
	pushdown(rt);
	int mid = (l + r) >> 1;
	if(L <= mid) mul(rt << 1, l, mid, L, R);
	if(R > mid) mul(rt << 1 | 1, mid + 1, r, L, R);
	update(rt);
}
haha query(int rt, int l, int r, int L, int R) { 
	if(L > R) {
		haha b;
		for(int i = 0; i <= k; i ++) b.a[i] = 0;
		return b;
	}
	if(L <= l && r <= R) {
		haha d;
		for(int i = 0; i <= k; i ++) d.a[i] = ha[rt][i];
		return d;
	}
	pushdown(rt);
	int mid = (l + r) >> 1; haha ret;
	ret.a[0] = 1;
	for(int i =  0; i <= k; i ++) ret.a[i] = 0;
	if(L <= mid) {
		haha b = query(rt << 1, l, mid, L, R);
		for(int i = 0; i <= k; i ++) ret.a[i] += b.a[i], ret.a[i] %= mod;
	} 
	if(R > mid) {
		haha b = query(rt << 1 | 1, mid + 1, r, L, R);
		for(int i = 0; i <= k; i ++) ret.a[i] += b.a[i], ret.a[i] %= mod;
	}
	return ret;
}
signed main() {
	scanf("%lld%lld", &n, &k); int lim = 2 * n;
	for(int i = 0; i <= lim * 4; i ++) ha[i][0] = 0	;
	for(int i = 0; i <= k; i ++) C[i][0] = 1;
	for(int i = 1; i <= k; i ++)
		for(int j = 1; j <= i; j ++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	for(int i = 1; i <= n; i ++) scanf("%lld%lld", &a[i].l, &a[i].r);
	sort(a + 1, a + 1 + n, cmp);
	haha d;
	for(int i = 0; i <= k; i ++) d.a[i] = 0;
	d.a[0] = 1;
	add(1, 0, lim, 0, d);
	for(int tt = 1; tt <= n; tt ++) {
		int l = a[tt].l, r = a[tt].r;
		haha b = query(1, 0, lim, 0, l - 1);
		haha c;
		for(int i = 0; i <= k; i ++) c.a[i] = 0;
		for(int i = 0; i <= k; i ++){
			int ret = 0;
			for(int j = 0; j <= i; j ++)
				c.a[i] += b.a[j] * C[i][j] % mod, c.a[i] %= mod;
		}
		b = query(1, 0, lim, l, r - 1);
		for(int i = 0; i <= k; i ++) c.a[i] = (c.a[i] + b.a[i]) % mod;
		add(1, 0, lim, r, c);
		mul(1, 0, lim, r + 1, lim);
	}
	printf("%lld", query(1, 0, lim, 0, lim).a[k]);
	return 0;
}
```

这一场就这题值得写一下QWQ

---

## 作者：qwaszx (赞：14)

都是做烂了的套路了....大爷们都不屑于写题解我来整一个

按照套路斯特林数一下，设$ans(S)$为$S$集合的连通块数，有

$$
\sum_S ans(S)^K=\sum_S\sum_{i=0}^KS(K,i)i!\binom{ans(S)}{i}=\sum_{i=0}^KS(K,i)i!\sum_S\binom{ans(S)}{i}
$$

按$l$排个序，然后一个个加入，设$f[i]$表示所有右端点为$i$的子集的答案，那么假设当前区间为$[l,r]$，分三种情况:

1. $i<r$ ，那么$i$会对$r$造成贡献，具体地就是$i$对应的这些子集并上$[l,r]$得到$r$对应的子集，这时连通块数$+1$，用$\binom{n+1}{k}=\binom{n}{k}+\binom{n}{k-1}$转移即可.

2. $i\in [l,r]$，那么$i$会对$r$造成贡献，这时连通块数不变，直接加上即可.

3. $i>r$，那么$r$会对$i$造成贡献，这时$i$对应的子集选不选$[l,r]$答案相同，所以$f[i]$应该乘上$2$

这三种操作都是线段树基本操作，直接上就完了.

复杂度$O(nK\log n)$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod=1000000007,N=1e6;
struct P{int l,r;}w[N];
int s[20][20],n,K,f[11],tmp[11];
struct Seg
{
	int a[N][11],tag[N];
	void upd(int rot,int w)
	{
		for(int i=0;i<=K;i++)a[rot][i]=(1ll*w*a[rot][i])%mod;tag[rot]=1ll*tag[rot]*w%mod;
	}
	void pushdown(int rot)
	{
		if(tag[rot]!=1)
		{
			int t=tag[rot];tag[rot]=1;
			upd(rot<<1,t),upd(rot<<1|1,t);
		}
	}
	void update(int rot,int lt,int rt,int lq,int rq)
	{
		if(lt>=lq&&rt<=rq){upd(rot,2);return;}
		int mid=(lt+rt)>>1;pushdown(rot);
		if(lq<=mid)update(rot<<1,lt,mid,lq,rq);
		if(rq>mid)update(rot<<1|1,mid+1,rt,lq,rq);
		for(int i=0;i<=K;i++)a[rot][i]=(a[rot<<1][i]+a[rot<<1|1][i])%mod;
	}
	void ins(int rot,int lt,int rt,int q,int w[])
	{
		for(int i=0;i<=K;i++)a[rot][i]=(a[rot][i]+w[i])%mod;
		if(lt==rt)return;
		int mid=(lt+rt)>>1;pushdown(rot);
		if(q<=mid)ins(rot<<1,lt,mid,q,w);
		else ins(rot<<1|1,mid+1,rt,q,w);
	}
	void query(int rot,int lt,int rt,int lq,int rq,int w[])
	{
		if(lt>=lq&&rt<=rq){for(int i=0;i<=K;i++)w[i]=(w[i]+a[rot][i])%mod;return;}
		pushdown(rot);
		int mid=(lt+rt)>>1;
		if(lq<=mid)query(rot<<1,lt,mid,lq,rq,w);
		if(rq>mid)query(rot<<1|1,mid+1,rt,lq,rq,w);
	}
	void build(int rot,int lt,int rt)
	{
		tag[rot]=1;if(lt==rt)return;
		int mid=(lt+rt)>>1;build(rot<<1,lt,mid),build(rot<<1|1,mid+1,rt);
	}
}a;
void clear(int w[]){for(int i=0;i<=K;i++)w[i]=0;}
int cmp(const P &a,const P &b){return a.l<b.l;}
int main()
{
	scanf("%d%d",&n,&K);
	s[0][0]=1;
	for(int i=1;i<=K;i++)
	{
		s[i][0]=0,s[i][i]=1;
		for(int j=1;j<i;j++)s[i][j]=(s[i-1][j-1]+1ll*j*s[i-1][j])%mod;
	}
	for(int i=1;i<=n;i++)scanf("%d%d",&w[i].l,&w[i].r);
	sort(w+1,w+n+1,cmp);
	tmp[0]=1;a.ins(1,0,2*n,0,tmp);
	for(int i=1;i<=n;i++)
	{
		clear(tmp);a.query(1,0,2*n,0,w[i].l-1,tmp);
		f[0]=tmp[0];for(int k=1;k<=K;k++)f[k]=(tmp[k-1]+tmp[k])%mod;
		clear(tmp);a.query(1,0,2*n,w[i].l,w[i].r,tmp);
		for(int k=0;k<=K;k++)f[k]=(f[k]+tmp[k])%mod;
		a.update(1,0,2*n,w[i].r+1,2*n);
		a.ins(1,0,2*n,w[i].r,f);
	}
	int ans=0;
	for(int i=0,fac=1;i<=K;i++,fac*=i)ans=(ans+1ll*fac*s[K][i]%mod*a.a[1][i])%mod;
	cout<<ans<<endl;
}
```

---

## 作者：xzzduang (赞：7)

题目要我们求这些线段共 $2^n$ 个的复杂度的 $K$ 次方之和，我们首先想想当 $K=1$ 怎么做。

我们设 $f_i$ 表示以 $i$ 为结尾的线段对答案产生的贡献（因为所以线段左右端点各不相同，所以不用考虑重复）

显然是要排序的，应该**按左端点排**，因为我们用右端点作数组下标，用左端点排的话就不容易丢失信息。

当我们加入一个新的线段 $l$ 到 $r$ 时，它会对前面的线段产生贡献：

1. 对于右端点 $1$ 到 $l-1$ ，现在的线段与它没交集，所以连通块数量会多一，所以把 $f_1$ 到 $f_{l-1}$ 的值都加一再累加到 $f_r$

2. 对于右端点 $l$ 到 $r-1$ ，现在的线段与之相交，连通块数量不变，把 $f_l$ 到 $f_{r-1}$ 直接累加到 $f_r$

3. 对于右端点 $r+1$ 到 $2*n$ ，这些线段包含了现在的线段，**这时就不能把贡献记到 $f_r$ 了**，因为后面的线段判断是否与之相交是判断 $r$ 与后面的线段端点的位置关系，而 $r+1$ 到 $2*n$ 的线段右端点比 $r$ 还右，所以判断是否相交应该由 $r+1$ 到 $2*n$ 的线段来判断，所以应该把贡献累计到 $f_{r+1}$ 到 $f_{2*n}$上

最终把所得的值放入 $f_r$。

### 综上所述，这些状态转移需要单点修改，区间修改，区间查询，采用线段树维护。



------------

现在我们来考虑 $K\ne 1$ 的情况。

唯一的问题就是把$　f_1$ 到 $f_{l-1}$ 的值加一再累计到 $f_r$ 怎么做。

其实就是这样：$(x+1)^k$

用二项式定理展开：

$(x+1)^k=\sum_{i=0}^k C_k^i x^i$

$K\le 10$ ，所以把 $x$ 的 $0$ 到 $k$ 次方都维护一下就完了


------------

时间复杂度 $O(NK^2log_n)$，空间 $O(NKlog_n)$

用第二类斯特林数可以优化时间的一个 $K$ ，可是我太蒻了，不会。
### $Code$

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#define ls k<<1
#define rs k<<1|1
#define N 100005
#define mo 1000000007
#define int long long
using namespace std;
struct segment{
	int l,r;
	bool operator < (const segment &A)const{
		return l<A.l;
	}
}s[N];
struct node{
	int a[11];
}val[N*8];
struct segment_tree{
	int l,r,lazy;
}d[N*8];
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
int n,lim,K,C[11][11];
void pushup(int k){
	for(int i=0;i<=K;++i) val[k].a[i]=(val[ls].a[i]+val[rs].a[i])%mo;
}
void pushdown(int k){
	if(d[k].lazy!=1){
		int t=d[k].lazy;
		for(int i=0;i<=K;++i){
			val[ls].a[i]=(val[ls].a[i]*t)%mo;
			val[rs].a[i]=(val[rs].a[i]*t)%mo;
		}
		d[ls].lazy=(d[ls].lazy*t)%mo;
		d[rs].lazy=(d[rs].lazy*t)%mo;
		d[k].lazy=1;
	}
}
void build(int k,int l,int r){
	d[k].l=l,d[k].r=r;
	d[k].lazy=1;
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void add(int k,int x,node v){
	if(d[k].l==d[k].r){
		for(int i=0;i<=K;++i) val[k].a[i]=(val[k].a[i]+v.a[i])%mo;
		return;
	}
	pushdown(k);
	if(x<=d[ls].r) add(ls,x,v);
	else add(rs,x,v);
	pushup(k);
}
void mul(int k,int x,int y,int v){
	if(x>y) return;
	if(x<=d[k].l && d[k].r<=y){
		d[k].lazy=(d[k].lazy*v)%mo;
		for(int i=0;i<=K;++i) val[k].a[i]=(val[k].a[i]*v)%mo;
		return;
	}
	pushdown(k);
	if(x<=d[ls].r) mul(ls,x,y,v); 
	if(d[rs].l<=y) mul(rs,x,y,v);
	pushup(k);
}
node query(int k,int x,int y){
	if(x>y){
		node fuck;
		for(int i=0;i<=K;++i) fuck.a[i]=0;
		return fuck;
	}
	if(x<=d[k].l && d[k].r<=y) return val[k];
	pushdown(k);
	node res;
	for(int i=0;i<=K;++i) res.a[i]=0;
	if(x<=d[ls].r){
		node tmp=query(ls,x,y);
		for(int i=0;i<=K;++i) res.a[i]=(res.a[i]+tmp.a[i])%mo;
	}
	if(d[rs].l<=y){
		node tmp=query(rs,x,y);
		for(int i=0;i<=K;++i) res.a[i]=(res.a[i]+tmp.a[i])%mo;
	}
	return res;
}
signed main(){
	n=read(),lim=n*2,K=read();
	for(int i=0;i<=K;++i) C[i][0]=1;
	for(int i=1;i<=K;++i){
		for(int j=1;j<=K;++j){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mo;
		}
	}
	build(1,0,lim);
	for(int i=1;i<=n;++i) s[i].l=read(),s[i].r=read();
	sort(s+1,s+n+1);
	node tmp,res;
	for(int lsy=1;lsy<=n;++lsy){
		int l=s[lsy].l,r=s[lsy].r;
		tmp=query(1,0,l-1);
		for(int i=0;i<=K;++i){
			res.a[i]=0;
			for(int j=0;j<=i;++j){
				res.a[i]=(res.a[i]+C[i][j]*tmp.a[j]%mo)%mo;
			}
		}
		tmp=query(1,l,r-1);
		for(int i=0;i<=K;++i)
			res.a[i]=(res.a[i]+tmp.a[i]+1)%mo;
		add(1,r,res);
		mul(1,r+1,lim,2);
	}
	printf("%lld",query(1,0,lim).a[K]);
	return 0;
}
```

---

## 作者：naoliaok_lovely (赞：4)

###### 各位大佬的题解结论来的有点快，蒟蒻看不太懂，于是决定在自己折腾大半天后自己写一篇...

# 次方和
看到 $k$ 次方之和，显然是套路，需要用到**二项式定理**存储下 $0\sim k$ 每个次方之和。这里不多叙述。

# DP 推导
首先按照左端点把线段进行排序（这也算是套路了）。  

手搓样例，于是发现所谓的“复杂度”与之前选择线段的右端点有关。定义状态 $f_i$ 表示右端点为 $i$ 的所有选法，对应的次方和。考虑新加入一条 $[l,r] $ 的线段：

- 之前的右端点 $\in[1,l-1]$，那么设之前的复杂度为 $w$，则 $f_i$ 要加上 $(w+1)^k$。
- 之前的右端点 $\in[l,r]$，则 $f_i$ 要加上 $w^k$。
- 之前的右端点 $\in[r+1,2n]$，则 $f_{r+1\sim2n}$ 要乘一个 $2$（是否选择当前线段）。

于是一个 $O(n^2)$ 的暴力就写完了，期望得分 $50pts$。

# 线段树优化
上述操作均为区间操作，可以使用线段树优化。

# Code
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define PII pair<int, int>

const int N = 2e5 + 10, mod = 1e9 + 7;
int n, m;
PII seg[N];
struct tree
{
	int l, r;
	LL sum[20];
	int lazy = 1;
}a[N * 4];

int c[30][30];
void init(int n)
{
	for(int i = 0; i <= n; i++)
	{
		c[i][0] = 1;
		for(int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
}

void pushup(tree &a, tree &x, tree &y)
{
	for(int i = 0; i <= m; i++) a.sum[i] = (x.sum[i] + y.sum[i]) % mod;
}
void pushup(int p)
{
	pushup(a[p], a[p << 1], a[p << 1 | 1]);
}
void pushdown(int p)
{
	for(int i = 0; i <= m; i++) a[p << 1].sum[i] = a[p << 1].sum[i] * a[p].lazy % mod;
	for(int i = 0; i <= m; i++) a[p << 1 | 1].sum[i] = a[p << 1 | 1].sum[i] * a[p].lazy % mod;
	a[p << 1].lazy = 1ll * a[p << 1].lazy * a[p].lazy % mod, a[p << 1 | 1].lazy = 1ll * a[p << 1 | 1].lazy * a[p].lazy % mod, a[p].lazy = 1;
}

void maketree(int p, int l, int r)
{
	a[p].l = l, a[p].r = r;
	if(l != r)
	{
		int mid = l + r >> 1;
		maketree(p << 1, l, mid);
		maketree(p << 1 | 1, mid + 1, r);
	}
}

void modify(int p, int l, int r)
{
	if(l <= a[p].l && a[p].r <= r)
	{
		for(int i = 0; i <= m; i++) a[p].sum[i] = a[p].sum[i] * 2 % mod;
		a[p].lazy = a[p].lazy * 2 % mod;
		return;
	}
	
	pushdown(p);
	int mid = a[p].l + a[p].r >> 1;
	if(l <= mid) modify(p << 1, l, r);
	if(r > mid) modify(p << 1 | 1, l, r);
	pushup(p);
}

void modify(int p, int x, tree &d)
{
	if(a[p].l == a[p].r)
	{
		for(int i = 0; i <= m; i++) a[p].sum[i] = (a[p].sum[i] + d.sum[i]) % mod;
		return;
	}
	
	pushdown(p);
	int mid = a[p].l + a[p].r >> 1;
	if(x <= mid) modify(p << 1, x, d);
	else modify(p << 1 | 1, x, d);
	pushup(p);
}

tree getans(int p, int l, int r)
{
	if(l <= a[p].l && a[p].r <= r)
		return a[p];
	
	pushdown(p);
	int mid = a[p].l + a[p].r >> 1;
	if(r <= mid) return getans(p << 1, l, r);
	if(l > mid) return getans(p << 1 | 1, l, r);
	tree ans, x = getans(p << 1, l, r), y = getans(p << 1 | 1, l, r);
	pushup(ans, x, y);
	return ans;
}

int main()
{
	init(20);
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++) scanf("%d%d", &seg[i].first, &seg[i].second);
	sort(seg + 1, seg + n + 1);
	maketree(1, 1, 2 * n);
	
	for(int i = 1; i <= n; i++)
	{
		tree ans = getans(1, seg[i].first, seg[i].second);
		modify(1, seg[i].second, ans);
		if(seg[i].second != 2 * n) modify(1, seg[i].second + 1, 2 * n);
		memset(ans.sum, 0, sizeof(ans.sum));
		if(seg[i].first != 1) ans = getans(1, 1, seg[i].first - 1);
		for(int j = m; j >= 0; j--)
		{
			for(int k = j - 1; k >= 0; k--)
				ans.sum[j] = (ans.sum[j] + c[j][k] * ans.sum[k]) % mod;
			ans.sum[j] = (ans.sum[j] + 1) % mod;
		}
		modify(1, seg[i].second, ans);
	}
	
	cout << a[1].sum[m] << endl;
	return 0;
}
```

---

## 作者：pomelo_nene (赞：4)

处理线段覆盖段数造成贡献的问题，有一个好的解决方法是将所有线段按左端点排序，这样的话，按顺序加入线段，线段覆盖成的段数显然单调不减。

然后再分析数据范围，发现 $k \leq 10$，又因为有 $k$ 次幂这种东西存在，显然斯特林数处理。定义 $f(S)$ 为集合 $S$ 中所有线段覆盖后形成的段数，有答案：

$$
\sum_{i=0}^k i! \begin{Bmatrix} k \\ i \end{Bmatrix} \sum_{S \subseteq U} \dbinom{f(S)}{i}
$$

注意到，直接维护答案不会很合理，根据经验想到将 $0$ 到 $k$ 全部都维护一遍。并且发现 $f(S)$ 在特殊的枚举过程中显然不会减少，加入一条线段增量至多为 $1$。因为 $\dbinom{n+1}{m} = \dbinom{n}{m} + \dbinom{n}{m-1}$，当 $f(S)$ 增加 $1$ 的时候可以以 $O(k)$ 的时间快速更新。

考虑 dp。定义 $dp_{i,j}$ 为选择了前面 $i$ 条线段的一些，其中最大的右端点在位置 $j$。注意到 $dp_{i,j}$ 实质上是一个长度为 $k+1$ 的数组，保存了形似于答案式子中 $i=0,1,\cdots ,k$ 时的答案。

考虑枚举 $j$ 表示上一层中最大的右端点所在位置，分类讨论：

- $j < l_i$：显然会形成新的一段，$f(S)$ 增加 $1$，按上面说的方法 $O(k)$ 更新到 $dp_{i,r_i}$；   
- $l_i \leq j \leq r_i$：不会形成新的一段，直接继承状态（或者说，加起来）至 $dp_{i,r_i}$；   
- $r_i < j$：因为已经按 $l_i$ 排序了，因此线段 $j$ 包含线段 $i$，线段 $i$ 只有存在和不存在两种情况。这个状态对当前的 $dp_{i,r_i}$ 没有任何影响，影响的是 $dp_{i,j}$，相当于将 $dp_{i,j} \gets dp_{i-1,j}$，并且将 $dp_{i,j}$ 中所有元素乘上 $2$。

分析，发现可以线段树维护:

- $j < l_i$：需要对所有的 $0 \leq p < l_i$，将 $dp_{i-1,p}$ 全部加起来（即，对于答案数组 $t$，有 $t_q \gets \sum_{p=0}^{l_i-1} dp_{i-1,p,q}$，下述同理），记为 $t$；然后再从大到小更新 $t_i \gets t_i + t_{i-1}$，最后再更新至 $dp_{i,r_i}$，需要一个区间和；   
- $l_i \leq j \leq r_i$：对所有的 $l_i \leq p \leq r_i$，将 $dp_{i-1,p}$ 加起来，再更新至 $dp_{i,r_i}$，需要区间和。

以上两种情况中更新 $dp_{i,r_i}$ 相当于单点加。

- $r_i < j$：对所有 $r_i < p \leq 2n$，将 $dp_{i,j} \gets dp_{i-1,j}$，再将 $dp_{i,j}$ 中所有元素乘上 $k$。

忽略掉「继承」这一操作（相当于在 dp 过程中将第一维滚掉），这是一个区间乘法。

区间和，区间乘，单点加，这些都是线段树的经典操作，直接做就行了。

有一个细节是，初始状态是 $dp_{0,0,0}=1$。这个东西第一点是要单点加，第二点是左端点是 $0$，处理方法是将后面的所有端点加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL QuickPow(LL x,LL p)
{
	LL ans=1,base=x;
	while(p)
	{
		if(p&1)	ans=ans*base%MOD;
		base=base*base%MOD;
		p>>=1;
	}
	return ans;
}
struct Segment{
	LL l,r;
	bool operator < (Segment ano) const {return l<ano.l;}
}seg[200005];
LL k;
struct SegmentTree{
	LL sum[800010][11],tag[800010];
	#define lc(x) (x<<1)
	#define rc(x) (lc(x)|1)
	#define Mm LL mid=(l+r)>>1
	void build(LL l,LL r,LL now)
	{
		tag[now]=1;
		if(l==r)	return ;
		Mm;
		build(l,mid,lc(now));
		build(mid+1,r,rc(now));
	}
	void push_up(LL now){for(LL i=0;i<=k;++i)	sum[now][i]=(sum[lc(now)][i]+sum[rc(now)][i])%MOD;}
	void push_down(LL now)
	{
		if(tag[now]!=1)
		{
			tag[lc(now)]=tag[lc(now)]*tag[now]%MOD;
			tag[rc(now)]=tag[rc(now)]*tag[now]%MOD;
			for(LL i=0;i<=k;++i)	sum[lc(now)][i]=sum[lc(now)][i]*tag[now]%MOD,sum[rc(now)][i]=sum[rc(now)][i]*tag[now]%MOD;
			tag[now]=1;
		}
	}
	void modify(LL l,LL r,LL now,LL x,LL y,LL val)
	{
		if(x<=l && r<=y)
		{
			tag[now]=tag[now]*val%MOD;
			for(LL i=0;i<=k;++i)	sum[now][i]=sum[now][i]*val%MOD;
			return ;
		}
		push_down(now);
		Mm;
		if(x<=mid)	modify(l,mid,lc(now),x,y,val);
		if(mid<y)	modify(mid+1,r,rc(now),x,y,val);
		push_up(now);
	}
	void modify(LL l,LL r,LL now,LL pos,LL *val)
	{
		for(LL i=0;i<=k;++i)	sum[now][i]=(sum[now][i]+val[i])%MOD;
		if(l==r)	return ;
		push_down(now);
		Mm;
		if(pos<=mid)	modify(l,mid,lc(now),pos,val);
		else	modify(mid+1,r,rc(now),pos,val);
		push_up(now);
	}
	void query(LL l,LL r,LL now,LL x,LL y,LL *ret)
	{
		if(x<=l && r<=y)
		{
			for(LL i=0;i<=k;++i)	ret[i]=(ret[i]+sum[now][i])%MOD;
			return ;
		}
		push_down(now);
		Mm;
		if(x<=mid)	query(l,mid,lc(now),x,y,ret);
		if(mid<y)	query(mid+1,r,rc(now),x,y,ret);
	}
	#undef lc
	#undef rc
	#undef Mm
}tr;
LL n,S[15][15],tek[15],tmp[15],R;
int main(){
	S[0][0]=1;
	for(LL i=1;i<=13;++i)	for(LL j=1;j<=i;++j)	S[i][j]=(S[i-1][j-1]+S[i-1][j]*j%MOD)%MOD;
	scanf("%lld %lld",&n,&k);
	for(LL i=1;i<=n;++i)	scanf("%lld %lld",&seg[i].l,&seg[i].r);
	sort(seg+1,seg+1+n);
	R=2*n+1;
	tmp[0]=1;
	tr.modify(1,R,1,1,tmp);
	for(LL i=1;i<=n;++i)
	{
		memset(tek,0,sizeof tek);
		memset(tmp,0,sizeof tmp);
		tr.query(1,R,1,1,seg[i].l,tek);
		tmp[0]=tek[0];
		for(LL j=1;j<=k;++j)	tmp[j]=(tek[j]+tek[j-1])%MOD;
		memset(tek,0,sizeof tek);
		tr.query(1,R,1,seg[i].l+1,seg[i].r+1,tek);
		for(LL j=0;j<=k;++j)	tmp[j]=(tmp[j]+tek[j])%MOD;
		if(seg[i].r<2*n)	tr.modify(1,R,1,seg[i].r+2,R,2);
		tr.modify(1,R,1,seg[i].r+1,tmp);
	}
	LL ans=0,fac=1;
	for(LL i=1;i<=k;++i)
	{
		fac=fac*i%MOD;
		ans=(ans+fac*S[k][i]%MOD*tr.sum[1][i]%MOD)%MOD;
	}
	printf("%lld",ans);
	return 0;
}
```




---

## 作者：Karry5307 (赞：4)

### 题意

题意很明显，我不想讲了。

$\texttt{Data Range:}n\leq 10^5,k\leq 10$

### 题解

线段树维护低次多项式优化 $\texttt{dp}$。

这题与同名金组题目强的不是一点点。

注意到有这个东西

$$\sum\limits_{i=0}^{\infty}\frac{a^i}{i!}x^i=e^{ax}$$

所以说我们可以直接将幂用生成函数的形式表示出来：

$$a^k=k![x^k]e^{ax}$$

类似于同名金组题目，我们对区间左端点排序，依次加入每个区间。设 $f_i$ 表示以 $i$ 为右端点的区间集合对应的 $\texttt{egf}$ 之和，那么我们可以通过 $\texttt{dp}$ 来搞。

考虑新加入的区间 $[l,r]$ 对答案的影响，可以分为如下几种：

- $i<l$，此时加进来的 $[l,r]$ 会使贡献增加 $1$，所以可以写成 $f_r\gets e^x(\sum\limits_{i<l}f_i)$。

- $i\in [l,r]$，此时贡献不变，而右端点变成 $r$，即 $f_r\gets\sum\limits_{l\leq i\leq r}f_i$。

- $i>r$ 的话，由于区间按照左端点排序，所以存在之前的区间 $[l_0,r_0]$ 满足 $l_0<l,r_0>r$，所以 $[l,r]$ 被完全覆盖，于是就有 $f_i\gets 2f_i(i>r)$

这三个操作涉及到区间查询多项式的和，区间多项式乘常数和单点修改，而且 $k$ 的范围很小，可以很方便的用线段树来维护这些多项式。

时间复杂度 $O(nk\log n+nk^2)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1e5+51,MOD=1e9+7;
struct Polynomial{
    ll cof[18];
    Polynomial()
	{
		memset(cof,0,sizeof(cof));
	}
};
struct SegmentTree{
    ll l,r,tag;
    Polynomial poly;
};
struct Interval{
    ll l,r;
    inline bool operator <(const Interval &rhs)const
	{
		return this->l<rhs.l;
	}
};
Polynomial p0;
SegmentTree tree[MAXN<<3];
Interval x[MAXN];
ll n,kk,l,r;
ll fact[18],finv[18];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline Polynomial operator +(Polynomial x,Polynomial y)
{
    Polynomial res=Polynomial();
    for(register int i=0;i<kk;i++)
    {
		res.cof[i]=(x.cof[i]+y.cof[i])%MOD;
    }
    return res;
}
inline Polynomial operator *(Polynomial x,ll y)
{
    Polynomial res=Polynomial();
    for(register int i=0;i<kk;i++)
    {
		res.cof[i]=(li)x.cof[i]*y%MOD;
    }
    return res;
}
inline ll binom(ll m,ll n)
{
    return (li)fact[m]*finv[n]%MOD*finv[m-n]%MOD;
}
inline Polynomial exMul(Polynomial x)
{
    Polynomial res=Polynomial();
    for(register int i=0;i<kk;i++)
    {
		for(register int j=0;j<=i;j++)
		{
			res.cof[i]=(res.cof[i]+(li)x.cof[j]*binom(i,j)%MOD)%MOD;
		}
    }
    return res;
}
inline void update(ll node)
{
    tree[node].poly=tree[node<<1].poly+tree[(node<<1)|1].poly;
}
inline void create(ll l,ll r,ll node)
{
    tree[node].l=l,tree[node].r=r,tree[node].tag=1;
    tree[node].poly=Polynomial();
    if(l==r)
    {
		return;
    }
    ll mid=(l+r)>>1;
    create(l,mid,node<<1),create(mid+1,r,(node<<1)|1);
}
inline void spread(ll node)
{
    if(tree[node].tag!=1)
    {
		ll ls=node<<1,rs=ls|1;
		tree[ls].poly=tree[ls].poly*tree[node].tag;
		tree[ls].tag=(li)tree[ls].tag*tree[node].tag%MOD;
		tree[rs].poly=tree[rs].poly*tree[node].tag;
		tree[rs].tag=(li)tree[rs].tag*tree[node].tag%MOD;
		tree[node].tag=1;
    }
}
inline void change(ll pos,Polynomial poly,ll node)
{
    if(tree[node].l==tree[node].r)
    {
		tree[node].poly=tree[node].poly+poly;
		return;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(pos<=mid)
    {
		change(pos,poly,node<<1);
    }
    else
    {
		change(pos,poly,(node<<1)|1);
    }
    update(node);
}
inline void multiply(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
		tree[node].poly=tree[node].poly*2;
		tree[node].tag=(li)tree[node].tag*2%MOD;
		return;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(l<=mid)
    {
		multiply(l,r,node<<1);
    }
    if(r>mid)
    {
		multiply(l,r,(node<<1)|1);
    }
    update(node);
}
inline Polynomial query(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
		return tree[node].poly;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    Polynomial poly=Polynomial();
    if(l<=mid)
    {
		poly=poly+query(l,r,node<<1);
    }
    if(r>mid)
    {
		poly=poly+query(l,r,(node<<1)|1);
    }
    return poly;
}
int main()
{
    n=read(),kk=read()+1,p0.cof[0]=1;
    fact[0]=fact[1]=finv[0]=1,finv[14]=320774361;
    for(register int i=2;i<=14;i++)
    {
		fact[i]=(li)fact[i-1]*i%MOD;
    }
    for(register int i=13;i;i--)
    {
		finv[i]=(li)finv[i+1]*(i+1)%MOD;
    }
    for(register int i=1;i<=n;i++)
    {
		x[i].l=read(),x[i].r=read();
    }
    sort(x+1,x+n+1),create(0,n<<1,1),change(0,p0,1);
    for(register int i=1;i<=n;i++)
    {
		l=x[i].l,r=x[i].r;
		change(r,exMul(query(0,l-1,1)),1);
		if(l+1<r)
		{
			change(r,query(l+1,r-1,1),1);
		}
		if(r<n+n)
		{
			multiply(r+1,n<<1,1);
		}
    }
    printf("%d\n",tree[1].poly.cof[kk-1]);
}
```

---

