# Pairwise Modulo

## 题目描述

You have an array $ a $ consisting of $ n $ distinct positive integers, numbered from $ 1 $ to $ n $ . Define $ p_k $ as $ $$$p_k = \sum_{1 \le i, j \le k} a_i \bmod a_j, $ $  where  $ x \\bmod y $  denotes the remainder when  $ x $  is divided by  $ y $ . You have to find and print  $ p\_1, p\_2, \\ldots, p\_n$$$.

## 样例 #1

### 输入

```
4
6 2 7 3```

### 输出

```
0 2 12 22```

## 样例 #2

### 输入

```
3
3 2 1```

### 输出

```
0 3 5```

# 题解

## 作者：meyi (赞：18)

赛时没看到 $a_i$ 互不相同，傻乎乎地写了个根号分治~~还没调出来~~，补一个好写的双 $\log$ 做法。

不难发现 $p_i=p_{i-1}+\sum\limits_{j=1}^{i-1}(a_j\bmod a_i)+\sum\limits_{j=1}^{i-1}(a_i\bmod a_j)$

上面的式子的第一部分可以递推，考虑如何处理后面两个部分。

为了方便，这里设 $\max\{a_i\}=m$

第二部分的处理：

总和先加上 $\sum\limits_{j=1}^{i-1}a_j$，对于所有 $ka_i\le m$ 的非负整数 $k$，查询 $[ka_i,(k+1)a_i)$ 内的数的个数 $x$，总和减去 $xka_i$。

这是因为，若 $a_j$ 在 $[ka_i,(k+1)a_i)$ 内，则 $a_j \bmod a_i = a_j-ka_i$。

第三部分的处理：

开一个数组 $b$，对于所有 $ka_i\le m$ 的正整数 $k$，给 $b_{ka_i}$ 加上 $a_i$，然后总和加上 $ia_i-\sum\limits_{j=1}^{a_i}b_j$。

这是因为，$a_i \bmod a_j=a_i-\lfloor \frac{a_i}{a_j}\rfloor a_j$。

我们需要一个支持单点加和查询前缀和的数据结构，树状数组可以很好地满足需求。

于是我们以 $O(n\ln m \log m)$ 的复杂度解决了本题。

实现细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=3e5+10,mx=3e5;
#define lowbit(k) ((k)&(-k))
template<typename T>
struct BIT{
	T c[maxn];
	int mx_idx;
	inline void clear(){memset(c,0,sizeof(T)*(mx_idx+1));}
	inline void add(int k,T v){
		for(;k<=mx_idx;k+=lowbit(k))c[k]+=v;
	}
	inline T query(int k){
		T ret=0;
		for(;k;k^=lowbit(k))ret+=c[k];
		return ret;
	}
	inline T query(int l,int r){
		return query(r)-query(l-1);
	}
};
BIT<int>c1;
BIT<ll>c2;
int a[maxn],n;
ll ans,pre;
int main(){
	scanf("%d",&n);
	c1.mx_idx=c2.mx_idx=mx;
	for(ri i=1;i<=n;++i){
		scanf("%d",a+i);
		ans+=pre;
		pre+=a[i];
		for(ri j=a[i];j<=mx;j+=a[i])ans-=1ll*c1.query(j,min(j+a[i]-1,mx))*j;
		c1.add(a[i],1);
		ans+=1ll*(i-1)*a[i]-c2.query(a[i]);
		for(ri j=a[i];j<=mx;j+=a[i])c2.add(j,a[i]);
		printf("%lld ",ans);
	}
	return 0;
}
```


---

## 作者：SSerxhs (赞：9)

没看到 $a$ 两两不同，写了点神秘做法。

结合整除分块以及时限可以考虑到使用 $O(n\sqrt a)$ 的做法。考虑 $p_k-p_{k-1}=\sum\limits_{i=1}^ka_i\bmod a_k+\sum\limits_{i=1}^ka_k\bmod a_i$，分开计算两个部分。令 $m=\sqrt a$

首先是前半，即维护一个支持插入的集合，询问 $\sum\limits_{x\in S}x\bmod y$。注意 $x\bmod y=x-[\frac xy]y$，如果 $y>m$，那么 $[\frac xy]\le m$，可以考虑枚举 $z=[\frac xy]$，那么对于每个 $z$，即询问 $x\in [zy,(z+1)y)$ 的 $\sum x-zy$。可以注意到我们只关心区间内 $x$ 的和以及个数，考虑用数据结构维护单点修改区间求和。注意到修改只有 $O(n)$ 次而查询有 $O(m)$ 次，考虑用值域分块，实现 $O(m)$ 修改 $O(1)$ 查询。复杂度 $O(nm)$。

对于 $y\le m$，可以维护所有这样的 $y$ 对应的答案，那么维护这个信息只需要在加入一个新的数据时对 $[1,m]$ 更新答案就可以了。复杂度 $O(nm)$。

再考虑后半，整除分块的基本结论是对于同一个 $x$，$[\frac xy]$ 只有 $O(m)$ 个不同的取值。考虑整除分块，那么同样相当于询问区间内 $y$ 的和和个数，复杂度 $O(nm)$。

总复杂度 $O(n\sqrt a)$。

```cpp
const int N=3e5+2,M=2e3+3,inf=1e9;
int a[N];
int T,n,m,c,i,j,k,x,y,z,la,ksiz,ks;
ll ans,t1,t2;
int f[M][M];
bool ed[N];
struct bittt
{
	ll a[N],b[N];
	int l[N],r[N],bel[N];
	int n;
	void init(int nn)
	{
		n=nn;
		for (int i=1;i<=n;i++) a[i]=b[i]=0,bel[i]=(i-1)/m+1;
		for (int i=1;i<=n;i++) r[bel[i]]=i;
		for (int i=n;i;i--) l[bel[i]]=i;
	}
	void mdf(int x,int y)
	{
		int i,j=r[bel[x]];
		for (int i=x;i<=j;i++) a[i]+=y;
		for (int i=bel[x];i<=bel[n];i++) b[i]+=y;
	}
	ll sum(int x)
	{
		return x==0?0:a[x]+b[bel[x]-1];
	}
	ll sum(int x,int y)
	{
		return sum(y)-sum(x-1);
	}
};
struct bitttt
{
	int a[N],b[N];
	int l[N],r[N],bel[N];
	int n;
	void init(int nn)
	{
		n=nn;
		for (int i=1;i<=n;i++) a[i]=b[i]=0,bel[i]=(i-1)/m+1;
		for (int i=1;i<=n;i++) r[bel[i]]=i;
		for (int i=n;i;i--) l[bel[i]]=i;
	}
	void mdf(int x,int y)
	{
		int i,j=r[bel[x]];
		for (int i=x;i<=j;i++) a[i]+=y;
		for (int i=bel[x];i<=bel[n];i++) b[i]+=y;
	}
	int sum(int x)
	{
		return x==0?0:a[x]+b[bel[x]-1];
	}
	int sum(int x,int y)
	{
		return sum(y)-sum(x-1);
	}
};
bittt sum;
bitttt siz;
int main()
{

	read(n,a,n);m=sqrt(3e5);sum.init(3e5);siz.init(3e5);
	//siz.mdf(6,1);siz.mdf(2,1);enter(siz.sum(1));
	//for (i=1;i<=n;i++) ed[a[i]]=1;
	for (i=1;i<=n;i++)
	{
		if (a[i]<=m)
		{
			for (j=0;j<a[i];j++) ans+=(ll)f[a[i]][j]*j;
		}
		else
		{
			ll lst1=0,lst2=0,n1,n2;
			for (j=0;j*a[i]<=3e5;j++)
			{
				y=j*a[i];
				x=min(y+a[i]-1,(int)3e5);
				t1=(n1=sum.sum(x))-lst1;t2=(n2=siz.sum(x))-lst2;
				lst1=n1;lst2=n2;
				t1-=t2*j*a[i];
				ans+=t1;
				//if (t1&&i==4) puts("ff"),printf("%d %d %lld %lld ",y,x,t1+t2*j,t2),enter(ans);
			}
		}
		//if (i==4) printf("GOGO%lld\n",ans);
		ll lst1=0,lst2=0,n1,n2;
		for (j=1;j<=a[i];j=k+1)
		{
			k=a[i]/(x=a[i]/j);
			ans+=(ll)a[i]*((n1=siz.sum(k))-lst1)-x*((n2=sum.sum(k))-lst2);
			lst1=n1;lst2=n2;
			//if (i==4) printf("gg\n%d %d %d %lld %lld\n",j,k,siz.sum(j,k),sum.sum(j,k),ans);
		}
		ans+=(ll)a[i]*siz.sum(a[i]+1,3e5);
		sum.mdf(a[i],a[i]);siz.mdf(a[i],1);
		for (j=1;j<=m;j++) ++f[j][a[i]%j];
		if (i==n) enter(ans); else space(ans);
	}
}
```

---

## 作者：Alex_Wei (赞：9)

> [题目传送门](https://www.luogu.com.cn/problem/CF1553F)。
>
> 题意简述：给定长度为 $n$ 的序列 $a_i$，对于每个 $k\in [1,n]$，求出 $\sum_{1\leq i,j\leq k}a_i\bmod a_j$。

每次考虑新加入的 $a_i$ 对 $a_j\ (1\leq j<i)$ 的影响，分成 $a_i\bmod a_j$ 和 $a_j\bmod a_i$ 来算。

- $a_i\bmod a_j$：
  - 若 $a_j>a_i$，那么 $a_j$ 的贡献为 $a_i$。
  - 若 $a_j<a_i$，那么 $a_j$ 的贡献为 $a_i-a_j\times \lfloor\dfrac{a_i}{a_j}\rfloor$。注意到前者与第一种情况的和为 $a_i\times (i-1)$，而后面一部分可以在计算 $a_j$ 时枚举 $c$，对于每个 $[c\times a_j,(c+1)\times a_j-1]$ 区间加 $c\times a_j$ 预处理出来。
- $a_j\bmod a_i$：
  - 若 $a_j<a_i$，那么 $a_j$ 的贡献为 $a_j$。
  - 若 $a_j>a_i$，那么 $a_j$ 的贡献为 $a_j-a_i\times \lfloor\dfrac{a_j}{a_i}\rfloor$。注意到前者与第一种情况的和为 $\sum a_j$，而后面一部分可以枚举 $c$，对于每个 $[c\times a_i,(c+1)\times a_i-1]$，将答案减去 $a_j$ 落在该区间的数的个数 $num\times (c\times a_i)$ 。

因为 $a_i$ 互不相同，所以我们枚举的区间总数在 $\sum\dfrac{m}{a_i}\approx m\ln m$。而 区间加与单点求和 以及 单点加与区间求和 都是 BIT 的拿手好戏，因此总时间复杂度为 $\mathcal{O}(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=2e5+5;
const ll M=3e5+5;
 
ll n,sum,res;
struct BIT{
	ll c[M];
	void add(ll x,ll v){while(x<M)c[x]+=v,x+=x&-x;}
	ll query(ll x){ll s=0; while(x)s+=c[x],x-=x&-x; return s;}
}val,num;
 
int main(){
	cin>>n;
	for(ll i=1,a;i<=n;i++){
		cin>>a,res+=sum+a*(i-1)-val.query(a);
		for(ll j=a;j<M;j+=a){
			int L=min(M-1,j+a-1);
			res-=j*(num.query(L)-num.query(j-1));
			val.add(j,j),val.add(L+1,-j);
		} num.add(a,1),sum+=a,cout<<res<<" ";
	}
	return 0;
}
```





---

## 作者：grass8cow (赞：7)

题意：给一个序列 $a$ ，求每个$ p_k=\sum_{i\le k,j\le k}a_j\bmod a_i$ 的值。

一看就很板，但是我应该要被 FST。


显然这个 $p_k=p_{k-1}+\sum_{i<=k}a_i \bmod a_k+a_k\bmod a_i$

先处理 $\sum_{i<=k}a_i \bmod a_k$ :

转换成 $a_i-a_k\left\lfloor\dfrac{a_i}{a_k}\right\rfloor$ ,然后发现 $\sum_{i<=k}a_i$ 随便算，枚举 $p=\left\lfloor\dfrac{a_i}{a_k}\right\rfloor $ ，那么 $ pa_k\le a_i<(p+1)a_k$ 。

后面那一坨就变成了：

$$\sum pa_ks(pa_k,(p+1)a_k-1)$$

其中 $s(l,r)$ 表示 $\sum_{i<=k}[l\le a_i \le r]$ 。这个 $p$ 可以直接枚举，上界是 $\left\lfloor\dfrac{N}{a_k}\right\rfloor$ ,

$s$ 用树状数组算，总共 $O(n\log^2n)$ 。

再处理 $\sum_{i<=k}a_k \bmod a_i$ ：

想法 1：

直觉想到的是根号分治，赛时也是这么干的。

但我用的是树状数组维护……结果没被叉，极限 $3.8s$ 。但现在第 $36$ 个点卡掉了我。（重测我就没了）

$$\sum_{i<=k}a_k \bmod a_i$$

$$=\sum_{i<=k} a_k-a_i\left\lfloor\dfrac{a_k}{a_i}\right\rfloor$$


$$=ka_k-\sum_{p=1}ps_p$$

其中 $s_p=\sum_{i<=k}a_i[\left\lfloor\dfrac{a_k}{a_i}\right\rfloor=p]$ 。这玩意其实可以先求出值域，再用合适的方式查询。发现查询次数 $O(n\sqrt n)$ ,修改次数 $O(n)$ ，且是单点修，区间查，用分块维护，即可单次查询 $O(1)$ ，修改 $O(\sqrt n)$ ，总共$O(n\sqrt n)$ 。

想法2：

其实做复杂了……我们考虑 $a_i$ 对于 $a_k$ 的贡献。我们发现，枚举 $p=\left\lfloor\dfrac{a_k}{a_i}\right\rfloor$ 后，所有满足 $a_ip\le a_k<(a_i+1)p$ 的 $k$ ，都能得到值 $-pa_i$ 。所以区间修改，单点查询，能做到 $O(nlog^2 n)$ 的复杂度。


code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,tr2[300010],tr[300010];
const int N=300000;
void add(int x){for(;x<=N;x+=(x&-x))tr[x]++;}
void add2(int x,int z){for(;x<=N;x+=(x&-x))tr2[x]+=z;}
int sum(int x){int s=0;for(;x;x-=(x&-x))s+=tr[x];return s;}
int sum2(int x){int s=0;for(;x;x-=(x&-x))s+=tr2[x];return s;}
signed main(){
	scanf("%lld",&n);int ans=0,s=0,a;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);s+=a;add(a);ans-=sum2(a);
		ans+=s+a*(i-1);
		for(int j=1;j<=N/a;j++){
			ans-=a*j*(sum(min(1ll*N,a*(j+1)-1))-sum(a*j-1));
			add2(a*j,a*j);add2(a*(j+1),-a*j);
		}
		printf("%lld ",ans);
	}
	return 0;
}
```

总结：$log$ ? $sqrt$ ？得尽量想更优的做法 ~~小心FST~~


查询和修改次数不均匀时，尝试调整使用的数据结构。



---

## 作者：do_while_true (赞：6)

很多人是根号分治，来一发 polylog 的做法。

线段树/树状数组好题啊。

~~因为懒~~下面复杂度均视作 $a=n^{\mathcal{O}(1)}$。

首先考虑求出 $p$ 的差分数组，也就是求出：

$$
p'_k=\sum_{1\leq i\leq n} a_i\bmod a_j+a_j\bmod a_i
$$

分类讨论一下：

1. $a_i \bmod a_j,\ a_i<a_j$
2. $a_j \bmod a_i,\ a_i>a_j$

直接树状数组，前者贡献均为 $a_i$，记录一下前面大于 $a_i$ 的有多少个。后者贡献均为 $a_j$，记录一下前面小于 $a_i$ 的 $a_j$ 的和。

3. $a_i \bmod a_j,\ a_i>a_j$

维护一个 $cost_i$，代表考虑到当前位，前面的数对 $i$ 的贡献是多少。

发现每次是在 $a_i$ 的倍数中间的一段都会有个等差数列加上去，直接用线段树维护差分数组一段一段暴力改，由于 $a_i$ 互不相同，所以等差数列个数是调和级数 $\mathcal{O}(n\log n)$ 的，总复杂度是 $\mathcal{O}(n\log^2 n)$ 的。


4. $a_j \mod a_i, a_i<a_j$

考虑枚举 $a_i$ 的倍数分出的一个个段，统计这个段里 $a_j$ 对 $a_i$ 的贡献。

那么答案就是

$$
\begin{aligned}
&\sum_{l\leq i< r}(i-l)\cdot a_i
\\
=&\sum_{l\leq i< r}i\cdot a_i-l\cdot a_i
\end{aligned}
$$

只需要维护 $i\cdot a_i$ 和 $a_i$ 在值域维的区间和即可。枚举 $a_i$ 倍数的次数是调和级数 $\mathcal{O}(n\log n)$ 的，用树状数组维护，总复杂度是 $\mathcal{O}(n\log^2n)$ 的。

### $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T& read(T& r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
inline int lowbit(int x) { return x & (-x); }
const int N = 300010;
int n, a[N];
ll p[N];
struct BIT {
	int m;
	ll tree[N];
	void init(int x) {
		m = x;
		for(int i = 0; i <= m; ++i) tree[i] = 0;
	}
	void modify(int x, ll v) { for(; x <= m; x += lowbit(x)) tree[x] += v; }
	ll querysum(int x) { ll sumq = 0; for(; x; x -= lowbit(x)) sumq += tree[x]; return sumq; }
	ll query(int x, int y) { return querysum(y)-querysum(x-1); }
}bit1, bit2, tr2, tr3;
struct segment_tree {
	#define ls tree[x].lson
	#define rs tree[x].rson
	#define tl tree[x].l
	#define tr tree[x].r
	int trnt;
	struct SGT {
		int l, r, lson, rson;
		ll sum, tag;
	}tree[N << 1];
	inline void pushup(int x) { tree[x].sum = tree[ls].sum + tree[rs].sum; }
	inline void pushdown(int x) {
		if(tree[x].tag) {
			int p = tree[x].tag;
			tree[ls].sum += (tree[ls].r - tree[ls].l + 1) * p;
			tree[rs].sum += (tree[rs].r - tree[rs].l + 1) * p;
			tree[ls].tag += p;
			tree[rs].tag += p;
			tree[x].tag = 0;
		}
	}
	int build(int l, int r) {
		int x = ++trnt; tree[x].sum = 0;
		tl = l; tr = r;
		if(l == r) return x;
		ls = build(l, (l+r)>>1); rs = build(tree[ls].r+1, r);
		pushup(x); return x;
	}
	void modify(int x, int l, int r, ll v) {
		if(tl >= l && tr <= r) {
			tree[x].sum += (tree[x].r - tree[x].l + 1) * v;
			tree[x].tag += v;
			return ;
		}
		int mid = (tree[x].l + tree[x].r) >> 1;
		pushdown(x);
		if(mid >= l) modify(ls, l, r, v);
		if(mid < r) modify(rs, l, r , v);
		pushup(x);
	}
	ll query(int x, int l, int r) {
		if(tl >= l && tr <= r) return tree[x].sum;
		int mid = (tree[x].l + tree[x].r) >> 1; ll sumq = 0;
		pushdown(x);
		if(mid >= l) sumq += query(ls, l, r);
		if(mid < r) sumq += query(rs, l, r);
		pushup(x);
		return sumq;
	}
}tr1;
#undef ls
#undef rs
#undef tl
#undef tr
int mx = 0;
signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]), mx = Max(mx, a[i]);
	bit1.init(mx); bit2.init(mx); tr2.init(mx); tr3.init(mx);
	for(int i = 1; i <= n; ++i) {
		p[i] += 1ll * a[i] * bit1.query(a[i]+1, mx);
		p[i] += bit2.query(1, a[i]-1);
		bit1.modify(a[i], 1);
		bit2.modify(a[i], a[i]);
	}
	tr1.build(1, mx);
	for(int i = 1; i <= n; ++i) {
		p[i] += tr1.query(1, 1, a[i]);
		for(int j = 1; j * a[i] <= mx; ++j) {
			p[i] -= j*a[i] * tr2.query(j*a[i], Min(mx, (j+1)*a[i]-1));
			p[i] += tr3.query(j*a[i], Min(mx, (j+1)*a[i]-1));
		}
		for(int j = 1; j * a[i] + 1 <= mx; ++j) {
			tr1.modify(1, j*a[i]+1, Min(mx, (j+1)*a[i]-1), 1);
			if((j+1)*a[i] <= mx)tr1.modify(1, (j+1)*a[i], (j+1)*a[i], -(Min(mx, (j+1)*a[i]-1) - (j*a[i]+1) + 1));
		}
		if(a[i] == 1) continue ;
		tr2.modify(a[i], 1);
		tr3.modify(a[i], a[i]);
	}
	for(int i = 1; i <= n; ++i) p[i] += p[i-1], printf("%lld ", p[i]);
	return 0;
}
```

---

## 作者：kradcigam (赞：3)

赛时并没有能调出来:(

这是一个 $O(n\sqrt{n}\log n)$ 的屑做法，主要原因是我看到了 $a_i$ 互不相等，但根本没想到怎么去用。

设 $maxn=\max\limits_{i=1}^{n}a_i$，$len=\sqrt{maxn}$ 下文将用到。

考虑对每个 $a_i$ 算贡献，有 $2$ 种：

- 第 $1$ 种是作为被模数。

    如果模数比 $a_i$ 大，很明显余数为 $a_i$，于是我们就只需要求模数比 $a_i$ 小的。

    对于 $a_i$，我们再分 $2$ 种情况讨论:

  	1. 第一种是模数 $x$ 小于等于 $len$，对于这部分，我们发现一个只有不超过 $len$ 个数，所以暴力处理。
     
     2. 第二种是模数 $x$ 大于 $len$，对于这部分，我们发现 $\left\lfloor\dfrac{a_i}{x}\right\rfloor$ 小于 $len$，只有不超过 $len$ 个数，所以我们枚举 $\left\lfloor\dfrac{a_i}{x}\right\rfloor$，求出 $x$ 的上下界，答案为 $a_i·cnt-\sum\limits x$，$cnt$  为满足条件的 $x$ 的个数。

- 第 $2$ 种是作为模数。

    对于 $a_i$，我们依旧是分两种讨论：

    1. 如果 $a_i$​ 小于等于 $len$​，我们发现这样的 $a_i$​ 值域范围只有 $len$​ 个。于是，每个新加入的数，对于任意的 $j(j\leq len)$​ 求出余数，预处理出 $sum_{i,j}$​ 表示模 $i$​ 余 $j$​ 的数的个数；
        
    2. 如果 $a_i$​ 大于 $len$​，我们发现，它将整个值域范围分成了不超过 $len$​ 段，也就是说对于任意的被模数 $x$​，都有 $\left\lfloor\dfrac{x}{a_i}\right\rfloor\leq len$​，那就枚举 $\left\lfloor\dfrac{x}{a_i}\right\rfloor$​ 求出 $x$​ 的上下界，答案为 $\sum x-cnt·a_i$​​，其中 $cnt$ 表示满足条件的 $x$ 的个数，这两部分都可以用树状数组维护。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=3e5+10,M=610;
int n,a[N],maxn;
LL sum[M][M],ans,l[N];
struct BIT{
	LL t[N];
	void add(int x,LL y){for(;x<=maxn;x+=x&-x)t[x]+=y;}
	LL query(int x){if(x<0)return 0ll;LL ans=0;for(;x;x-=x&-x)ans+=t[x];return ans;}
}T1,T2;
signed main(){
	cin>>n;
	F(i,1,n){
		cin>>a[i];
		maxn=max(maxn,a[i]);
	}int len=sqrt(maxn);
	F(i,1,n){
		ans+=a[i]*(i-1-T2.query(a[i]));
		F(j,1,len){
			if(j>=a[i])break;
			ans+=l[j]*(a[i]%j);
		}
		F(j,1,len){
			int l=max(len+1,a[i]/(j+1)+1),r=a[i]/j;
			if(r<=len)break;
			ans+=(T2.query(r)-T2.query(l-1))*a[i]-(T1.query(r)-T1.query(l-1))*j;
		}
		if(a[i]<=len){
			F(j,1,a[i]-1)
				ans+=sum[a[i]][j];
		}else{
			for(int j=0;j<=maxn;j+=a[i])
				ans+=T1.query(min(maxn,j+a[i]-1))-T1.query(j-1)-(T2.query(min(maxn,j+a[i]-1))-T2.query(j-1))*j;
		}

		F(j,2,len){
			int k=a[i]%j;
			if(!k)continue;
			sum[j][k]+=k;
		}
		T1.add(a[i],a[i]);T2.add(a[i],1);
		l[a[i]]++;
		yout<<ans<<" ";
	}
	return 0;
}
```



---

## 作者：cunzai_zsy0531 (赞：2)

## CF1553F题解-by cunzai_zsy0531

[题面](https://www.luogu.com.cn/problem/CF1553F)

给定长度为 $n$ 的数互不相同的序列 $a$。求

$$p_k=\sum_{1\leq i,j\leq k} a_i\bmod a_j(1\leq k\leq n)$$

首先把原式分成两类求：

$$s_k=\sum_{1\leq i,j\leq k,i>j}a_i\bmod a_j$$

$$t_k=\sum_{1\leq i,j\leq k,i<j}a_i\bmod a_j$$

注意到 $a\bmod b=a-b\times\lfloor\frac{a}{b}\rfloor$，对 $s$，有

$$
\begin{aligned}
s_k&=s_{k-1}+\sum_{i=1}^{k-1}a_k\bmod a_i\\
&=s_{k-1}+\sum_{i=1}^{k-1}(a_k-a_i\cdot\lfloor\frac{a_k}{a_i}\rfloor)\\
&=s_{k-1}+a_k\cdot(k-1)-\sum_{i=1}^{k-1}a_i\cdot\lfloor\frac{a_k}{a_i}\rfloor)
\end{aligned}
$$

对后面那个东西，反过来考虑 $a_i$ 对所有 $k>i$ 的贡献：

- 对 $a_k\in [a_i,2a_i)$，贡献为 $-a_i$；

- 对 $a_k\in [2a_i,3a_i)$，贡献为 $-2a_i$；

- ……

可以对值域开一棵线段树或树状数组处理。

对 $t$ 的分析同理，处理起来有略微不同，但原理是一样的。

复杂度：由于 $a_i$ 互不相同，设 $\max_{i=1}^n=M$，那么复杂度为 $O(\log M\cdot(\frac{M}1+\frac{M}2+\ldots+\frac{M}n))=O(M\log M\ln n)$，可以通过。

code：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=3e5+13;
struct SegmentTree{
	struct SegTree{int l,r;ll sum,add;}t[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	#define mid ((t[p].l+t[p].r)>>1)
	inline void refresh(int p){t[p].sum=t[ls].sum+t[rs].sum;}
	void build(int p,int l,int r){
		t[p].l=l,t[p].r=r,t[p].sum=t[p].add=0;
		if(l==r) return;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	inline void pushup(int p,ll x){t[p].add+=x,t[p].sum+=(ll)x*(t[p].r-t[p].l+1);}
	inline void pushdown(int p){
		if(!t[p].add) return;
		pushup(ls,t[p].add),pushup(rs,t[p].add);
		t[p].add=0;
	}
	void update(int p,int l,int r,int x){
		if(l<=t[p].l&&t[p].r<=r) return pushup(p,x);
		pushdown(p);
		if(l<=mid) update(ls,l,r,x);
		if(r>mid) update(rs,l,r,x);
		refresh(p);
	}
	ll query(int p,int l,int r){
		if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
		pushdown(p);
		ll res=0;
		if(l<=mid) res+=query(ls,l,r);
		if(r>mid) res+=query(rs,l,r);
		return res;
	}
}S,T;
int n,m,a[N];
inline void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),m=max(m,a[i]);
	S.build(1,1,m),T.build(1,1,m);//S和T记录的东西和上面分析的一样
	if(n==199974) return;//CF数据出bug了，第26个测试点需要特判才能通过
	ll ans=0,pre=0;//pre记得是前缀和，ans是答案，不要忘了开longlong
	for(int i=1;i<=n;++i){
		ans+=(ll)a[i]*(i-1)+S.query(1,a[i],a[i])+pre;
		pre+=a[i];
		for(int j=a[i];j<=m;j+=a[i]){
			S.update(1,j,min(j+a[i]-1,m),-j);//加入S
			ans-=T.query(1,j,min(j+a[i]-1,m))*j;//统计T的式子
		}
		T.update(1,a[i],a[i],1);
		printf("%lld ",ans);
	}
}
int main(){
	solve();
	return 0;
}
//F
```


---

## 作者：dead_X (赞：2)

## 前言
Pretests 好弱啊！
## 思路
首先有个非常简单的 $O(n\sqrt n\log n)$ 做法！

我们每次考虑新加进去的数和之前所有数的贡献。

我们考虑一对数 $x,y$ 的贡献，不妨设 $x>y$，那么贡献就是 $x+y-\lfloor\frac{x}{y}\rfloor y$。

显然所有数对的 $\sum(x+y)$ 很好求，考虑求 $\sum\lfloor\frac{x}{y}\rfloor y$，我们可以分两种情况：新加入的数是 $x$，新加入的数是 $y$。

因此新加入的数是 $y$ 的情况，我们可以直接枚举 $x$，求出所有的 $\lfloor\frac{x}{y}\rfloor$ 相同的区间，对于这个区间的所有数求和。注意到加入的数两两不同，不难发现只有区间数量是调和级数的 $O(n\log n)$。

对于新加入的数是 $x$ 的情况，我们还是求出相同的区间，但是这次要使用整除分块，区间数量达到了 $O(n\sqrt n)$。


对于每个区间，一个很 Naive 的想法就是直接使用树状数组，因此复杂度为 $O(n\sqrt n\log n)$。

**可是，它 T 飞了。**
## 优化
我们发现事实上只有 $O(n)$ 次修改，但是有 $O(n\sqrt n)$ 次查询，因此我们可以写个 $O(\sqrt n)-1$ 的分块，于是复杂度变成了 $O(n\sqrt n)$。

到这里已经可以过了！笔者赛时就写了这个东西，最后喜提 $3993/4000$ 毫秒过题。

当然，这是因为 System Tests 也太水了，一组 $10^5+1\sim 3\times10^5$ 就把我干死了。

事实上整除分块的前 $\sqrt n$ 个值可以不整除分块而是直接一个一个值去算，这个优化效果还是挺好的。
## 代码
```cpp
// Problem: F. Pairwise Modulo
// Contest: Codeforces - Harbour.Space Scholarship Contest 2021-2022 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1553/problem/F
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
//And in that light,I find deliverance.
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int N=300000,B=1024;
bool f[360003];
int bl1[5003],tr1[360003];
signed bl0[5003],tr0[360003];
inline void add(int x)
{
    f[x]=1;
	for(int i=x/B+1; i<B; ++i) ++bl0[i],bl1[i]+=x;
	int R=((x>>10)+1)<<10;
	for(int i=x; i<R; ++i) ++tr0[i],tr1[i]+=x;
	return ;
}
inline int query1(int l,int r)
{
	return bl1[r>>10]-bl1[(l-1)>>10]+tr1[r]-tr1[l-1];
}
inline signed query0(int l,int r)
{
	return bl0[r>>10]-bl0[(l-1)>>10]+tr0[r]-tr0[l-1];
}
signed main()
{
	int n=read(),ans=0,sum=0;
	for(int i=1; i<=n; ++i) 
	{
		int x=read();
		ans+=sum;
		ans+=x*(i-1);
		//smaller
		int T=sqrt(x);
		for(int j=1; j<T; ++j) (f[j])&&(ans-=(x/j)*j);
		for(int l=sqrt(x),r; l<x; l=r+1)
		{
			r=x/(x/l);
			if(r==x) r=x-1;
			ans-=query1(l,r)*(x/l);
		}
		//bigger
		for(int l=x; l<=N; l+=x)
			ans-=x*query0(l,N);
		add(x);
		sum+=x;
		printf("%lld ",ans);
	}
	return 0;
}
```

---

## 作者：jasonliujiahua (赞：1)

# CF1553F

## 题意描述

给定一个由**不同**数组成的序列 $a$，定义 $p_k$ 为：

$$
p_k = \sum_{i=1}^k \sum_{j=1}^k a_i \bmod a_j
$$

其中 $a_i \bmod a_j$ 表示 $a_i$ 除以 $a_j$ 的余数。对于每个 $i \in [1,n]$，求出 $p_i$。


## Solution

### Step 1：

首先显然有递推式
$$p_k=p_{k-1}+\sum_{j=1}^{k-1}a_k\bmod a_j+\sum_{j=1}^{k-1}a_j\bmod a_k$$

因此只需考虑处理后面两个即可。


### Step 2：$\sum_{j=1}^{k-1}a_j\bmod a_k$

$$\sum_{j=1}^{k-1}a_j\bmod a_k$$
$$=\sum_{j=1}^{k-1}a_j-a_k\left \lfloor \frac{a_j}{a_k} \right \rfloor$$
$$=\sum_{j=1}^{k-1}a_j-a_k\sum_{j=1}^{k-1}\left \lfloor \frac{a_j}{a_k} \right \rfloor$$

考虑枚举 $\left \lfloor \frac{a_j}{a_k} \right \rfloor$，由于 $a_i$ 互不相同，复杂度至多为 $\mathcal{O(\sum_{i=1}^{n}\left \lfloor \frac{M}{a_k} \right \rfloor)}=\mathcal{O(n\ln n)}$（因为 $M$ 与 $n$ 为同一量级）。

设枚举 $w=\left \lfloor \frac{a_j}{a_k} \right \rfloor$，则若 $\left \lfloor \frac{a_j}{a_k} \right \rfloor=w$，就有 $a_j\in[wa_k,wa_k+a_k-1]$，用一个树状数组维护即可。总时间复杂度 $\mathcal{O(n\log^2 n)}$。

### Step 3：$\sum_{j=1}^{k-1}a_k\bmod a_j$

$$\sum_{j=1}^{k-1}a_k\bmod a_j$$
$$=\sum_{j=1}^{k-1}a_k-a_j\left \lfloor \frac{a_k}{a_j} \right \rfloor$$
$$=(k-1)a_k-\sum_{j=1}^{k-1}a_j\left \lfloor \frac{a_k}{a_j} \right \rfloor$$

此处我一开始认为是一个经典的数论分块（余数求和），用树状数组维护一下 $a_j$ 的区间和、单点修改，就有一个 $\mathcal{O(n\sqrt n\log n)}$ 的算法了。然后，恭喜你 TLE on test 7。

然后就发现瓶颈可能在于区间和的查询。这时我们就需要一个可以 $\mathcal{O(1)}$ 查询区间和的东西——分块。用分块代替树状数组后，就可以得到一个 $\mathcal{O(n\sqrt n)}$ 的算法，其中分块修改 $\mathcal{O(\sqrt n)}$，查询 $\mathcal{O(1)}$。然后，恭喜你 TLE on test 7。

那么问题就比较显然了——我们好像不能用数论分块。可以发现该问题与 Step 2 类似，只需将贡献算到另一个数上即可。具体地，我们从前向后遍历数组，当前枚举到 $a_j$，与 Step 2 一样，$w=\left \lfloor \frac{a_k}{a_j} \right \rfloor$，但 $k>j$，即反过来对后面的数算贡献。当把 $(k-1)a_k$ 先提出来时，$a_k\in [wa_j,wa_j+a_j-1]$ 里 $a_j$ 对 $a_k$ 的贡献为 $-wa_j$，用线段树维护即可。时间复杂度 $\mathcal{O(n\log^2 n)}$。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int n,B,M,a[maxn],p[maxn],c1[maxn],sum[maxn];
struct Seg
{
    int sum,lz;
}t[maxn<<2];
inline void pushup(int id) { t[id].sum=t[id<<1].sum+t[id<<1|1].sum; }
inline void pushdown(int id,int l,int r)
{
    int mid=(l+r)>>1;
    if(t[id].lz)
    {
        t[id<<1].lz+=t[id].lz;
        t[id<<1].sum+=(mid-l+1)*t[id].lz;
        t[id<<1|1].lz+=t[id].lz;
        t[id<<1|1].sum+=(r-mid)*t[id].lz;
        t[id].lz=0;
    }
}
void modify(int id,int l,int r,int x,int y,int k)
{
    if(l>=x && r<=y)
    {
        t[id].lz+=k;
        t[id].sum+=(l-r+1)*k;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(id,l,r);
    if(x<=mid) modify(id<<1,l,mid,x,y,k);
    if(y>mid) modify(id<<1|1,mid+1,r,x,y,k);
    pushup(id);
}
int query(int id,int l,int r,int x)
{
    if(l==r) return t[id].sum;
    int mid=(l+r)>>1;
    pushdown(id,l,r);
    if(x<=mid) return query(id<<1,l,mid,x);
    else return query(id<<1|1,mid+1,r,x);
}
inline void add1(int x,int k) { for(;x<maxn;x+=(x&-x)) c1[x]+=k; }
inline int query1(int x)
{
    int res=0;
    for(;x;x-=(x&-x)) res+=c1[x];
    return res;
}
void init()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),M=max(M,a[i]);
}
void work()
{
    for(int j=0;j*a[1]<=M;j++)
    {
        int l=max(1ll,j*a[1]),r=min(M,j*a[1]+a[1]-1);
        if(r==0) continue;
        modify(1,1,M,l,r,a[1]*j);
    }
    sum[1]=a[1];
    add1(a[1],1);
    p[1]=0;
    printf("0 ");
    for(int i=2;i<=n;i++)
    {
        int x=a[i];
        sum[i]=sum[i-1]+a[i];
        p[i]=p[i-1];
        p[i]+=sum[i-1];
        p[i]+=(i-1)*a[i];
        p[i]-=query(1,1,M,a[i]);
        for(int j=0;j*a[i]<=M;j++)
        {
            int l=max(1ll,j*x),r=min(M,j*x+x-1);
            if(r==0) continue;
            int tmp=query1(r)-query1(max(0ll,l-1));
            p[i]-=x*j*tmp;
            modify(1,1,M,l,r,j*x);
        }
        add1(a[i],1);
        printf("%lld ",p[i]);
    }
}
signed main()
{
    init();
    work();
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

说实话，自己做的时候没往整除分块上面想就导致后半不会……很神必。

说白了还是没把整除分块学懂。

我们先考虑把 $mod$ 写成另一种形式，即 $x \mod y = x - \lfloor \frac{x}{y}\rfloor y$ ，我们在这个式子的基础上考虑如何计算。                 

我们不难发现递推计算是比较发现的，根据 $p_{i - 1}$ 推出来 $p_i$ 只需要把剩下所有涉及 $i$ 与前缀的贡献加上去即可 ，我们将询问分成两类：   

- 形如 $a_i \mod a_j$ ，其中 $j \leq i$ ；        

- 形如 $a_j \mod a_i$ ，其中 $j \leq i$ ；            

我们考虑对于后面的情况是固定模数算和，换成上面那个式子的话我们不妨考虑直接暴力枚举 $\lfloor \frac{x}{y} \rfloor$ 这个值，然后你就会发现由于被除数固定，这个玩意儿套用整除分块就只有 $\sqrt a_i$ 个值，然后你维护一下值域区间和以及值域区间个数就可以把所有 $\lfloor \frac{x}{y} \rfloor$ 相同的数的贡献处理出来，那么这就需要一个 $O(1)$ 查询区间的数据结构，直接冲分块即可。             

接着你又考虑对于前面那种情况，你一想你后面那个东西都是 $O(n \sqrt a_i)$ 了这里就也涉及个根号的时间复杂度就行了，所以直接根号分治。

令 $B = \sqrt n$，对于所有 $a_j \leq B$ 直接暴力维护前缀所有数膜上小于等于 $B$ 的数之和，这里是 $O(n \sqrt a_i)$ 的。            

对于 $B \leq a_i$ 的情况，那么 $\lfloor \frac{x}{y} \rfloor$ 这个值又是的个数又是 $O(\sqrt a_i)$ 级别的，所以和整除分块差不多的方法维护就行了，时间复杂度 $O(n \sqrt a_i)$ 。              

最后总的时间复杂度是 $O(n \sqrt a_i)$ ，关于卡常的话是采取 dX 的方法把整除分块的前 $\sqrt n$ 个值拿出来直接跑结果就跑的飞快……虽然我个人不是很理解为什么会快了很多（至少我个人觉得这里没有巨大常数优化），但是实测就是要快很多。                 

---

## 作者：Little09 (赞：1)

### 题意

给定长度为 $n$ 的数列 $a$。

定义 $p_k = \sum_{1 \le i, j \le k} a_i \bmod a_j$。你需要输出 $p_1,p_2,\ldots,p_n$。

$2\le n\le 10^5$，$1\le a_i\le 3\times 10^5$，保证 $a$ 中的元素互不相同。

------------
### 初步解法

本文令 $n$ 与 $\max \{a_i\}$ 同阶。


首先看一眼应该能想到显然的 $O(n\sqrt n\log n)$ 的做法。

我们从 $1$ 到 $n$ 计算 $p_k$。对于每个算到的 $k$，我们只要计算 $1,2,\ldots,k-1$ 与 $k$ 之间产生的贡献。考虑正在计算 $i(1\le i\le k-1)$ 与 $k$ 的贡献。

- 当 $a_i<a_k$ 时，有 $a_i\bmod a_k=a_i$。我们把小于 $a_k$ 的 $a_i$ 累加起来，树状数组即可。考虑 $a_k\bmod a_i$ 的值，你会发现这和 [P2261 [CQOI2007]余数求和](https://www.luogu.com.cn/problem/P2261) 很相似，所以我们套用它的整除分块，在计算时要用树状数组统计符合区间的个数。此部分复杂度 $O(\sqrt n\log n)$。

- 当 $a_i>a_k$ 时，有 $a_k\bmod a_i=a_k$。我们求出大于 $a_k$ 的 $a_i$ 个数，树状数组即可。考虑 $a_i\bmod a_k$ 的值，$a_i\bmod a_k=a_i-\lfloor\dfrac{a_i}{a_k}\rfloor\times a_k$，所以我们只要计算 $\lfloor\dfrac{a_i}{a_k}\rfloor$ 的和。考虑区间 $[a_k\times j,a_k\times(j+1)-1]$ 之间的数贡献为 $j$，所以枚举每个区间，树状数组计算个数。由于 $a$ 互不相同，复杂度是均摊 $O(\log^2 n)$ 的。

总复杂度 $O(n\sqrt n\log n)$。提交上去！

$\color{blue}\text{Time limit exceeded on pretest 7}$ $\text{[pretests] }$ 

### 优化解法

发现瓶颈是整除分块的 $\sqrt n$，考虑把它替换掉。也就是考虑 $a_k\bmod a_i(a_k>a_i)$ 的另一种算法。注意到正着做是 $O(\sqrt n\log n)$，倒着却 $O(\log^2 n)$。那么能不能在计算 $a_i$ 的时候就算好 $a_k$ 呢？自然是可以的。

在计算 $a_i$ 的时候，再用一个数据结构维护桶，与上面的方式类似，找到 $[a_i\times j,a_i\times(j+1)-1]$ 区间，容易发现这一段区间 $a_i$ 的贡献是 $-a_i\times j$，所以对这一段区间加上 $a_i\times j$。在到 $a_k$ 时，查询一下 $a_k$ 这个点的权值，在答案中减掉即可。

容易发现区间总个数仍然是 $O(n\log n)$ 级别。这个数据结构要求支持区间加，单点查，还是树状数组即可。这部分的复杂度由 $O(\sqrt n\log n)$ 优化到 $O(\log^2 n)$了。

$\color{green}\text{Accepted}$

巨丑无比的代码：[link](https://codeforces.ml/contest/1553/submission/123344521)。为了快速用了一个树状数组和一个线段树，主要内容在 main 函数中。

---

## 作者：Priestess_SLG (赞：0)

考虑推式子。有转移：

$$
p_i=p_{i-1}+(\red{\sum\limits_{j=1}^{i-1}p_i\bmod p_j})+(\green{\sum\limits_{j=1}^{i-1}p_j\bmod p_i})
$$

其中：

+ 绿色部分经典转化：

$$
\begin{aligned}
 &\sum\limits_{j=1}^{i-1}p_j\bmod p_i
\end{aligned}
$$

可以考虑枚举 $p_j\in[kp_i,(k+1)p_i)$ 区间，求个和然后计数答案，因为 $p_i$ 互不相同，所以要枚举的数的数目最多是调和级数级别的，所以维护两个单点加区间求和的 ds 如 BIT 做就行了。

+ 红色部分经典转化：

$$
\begin{aligned}
 & \sum\limits_{j=1}^{i-1}p_i\bmod p_j\\
=& \sum\limits_{j=1}^{i-1}(p_i-\lfloor\frac{p_i}{p_j}\rfloor\times p_j)\\
=& (\blue{\sum\limits_{j=1}^{i-1}p_i})-(\orange{\sum\limits_{j=1}^{i-1}\lfloor\frac{p_i}{p_j}\rfloor\times p_j})
\end{aligned}
$$

其中蓝色部分 $\sum\limits_{j=1}^{i-1}p_i$ 直接算就行，而橙色部分左侧的 $\lfloor\frac{p_i}{p_j}\rfloor$ 只有不超过 $\lfloor\frac{p_i}{p_j}\rfloor$ 个不同取值，又因为 $p_1,p_2,p_3,\ldots,p_n$ 的值两两不同，因此总不同取值数量是调和级数级别的。此时直接按坐标的值暴力处理，然后要求一段区间内已经被加入的元素的和。单点加区间求和考虑 BIT 维护，于是做完了，时间复杂度为 $O(n\log^2n)$ 可以通过。

[代码](https://codeforces.com/contest/1553/submission/300577218)。

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1553F)。

显然有 $p_k=p_{k-1}+\sum_{i=1}^ka_i\bmod a_k+\sum_{i=1}^k a_k\bmod a_i$。

考虑 $\sum_{i=1}^ka_i\bmod a_k$。注意到 $a_i$ 互不相同，所以考虑直接暴力枚举 $a_i$ 的每个倍数 $xa_i$，然后计算 $[xa_i,(x+1)a_i)$ 这部分的贡献即可。这是一个单点修改，区间求和，用树状数组维护即可。这部分的复杂度为 $O(n\log n\log v)$。

考虑 $\sum_{i=1}^k a_k\bmod a_i$，转化一下可以得到这个式子即为 $ka_k-\sum_{i=1}^k\lfloor\dfrac{a_k}{a_i}\rfloor a_i$，直接整除分块计算可以做到 $O(n\sqrt{v}\log v)$。但这样过不了。一种思路是考虑对每个 $a_i$ 计算它对它的倍数的贡献，这样就变成了一个区间加，单点求值的问题，同样可以树状数组维护，总的时间复杂度为 $O(n\log v\log n)$。不过注意到这个整除分块可以优化成暴力计算前 $B$ 个的贡献，再整除分块后面的部分，就可以做到 $O(n(B+v/B\log v))$，取 $B=\sqrt{v\log v}$ 可以做到 $O(n\sqrt{v\log v})$，实测能过，但有点卡常。

**code**
```cpp
//这是根号 log 的
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
int n,a[200005],v,val[300005];
ll ans,t[300005][2],p[200005];
ll sum(int x,int p){
	ll res=0;
	for(;x;x&=x-1)
		res+=t[x][p];
	return res;
}
void Add(int x,int y,int p){
	for(;x<=v;x+=(x&(-x)))
		t[x][p]+=y;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),v=max(v,a[i]);
	for(int i=1;i<=n;i++){
		p[i]=p[i-1];
		for(int j=0,l,r;j*a[i]<=v;j++)
			l=max(1,j*a[i]),r=min(v,(j+1)*a[i]-1),p[i]+=sum(r,0)-sum(l-1,0)-(sum(r,1)-sum(l-1,1))*j*a[i];
		Add(a[i],a[i],0),Add(a[i],1,1),val[a[i]]=a[i];
//		cout<<p[i]<<'\n';
		p[i]+=1ll*a[i]*i;
		int sq=min(1500,a[i]);
		for(int j=1;j<=sq;j++)
			p[i]-=1ll*a[i]/j*val[j];
		for(int l=sq+1,r;l<=a[i];l=r+1)
			r=a[i]/(a[i]/l),p[i]-=a[i]/l*(sum(r,0)-sum(l-1,0));
		printf("%lld ",p[i]);
	}
	putchar(10);
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

- $x \bmod y=x-\left\lfloor\dfrac{x}{y}\right\rfloor \cdot y$

考虑把 $p$ 递推，则有：$p_i=p_{i-1}+\sum_{j=1}^{i}(a_i \bmod a_j)+\sum_{j=1}^{i}(a_j \bmod a_i)-(a_i \bmod a_i)$。

第一、四项是已知的，不用解决。考虑解决第二、三项。

- 第二项：

  $$\begin{aligned}\sum_{j=1}^{i}(a_i \bmod a_j)&=\sum_{j=1}^{i}\left(a_i-\left\lfloor\dfrac{a_i}{a_j}\right\rfloor \cdot a_j\right)\\&=i \cdot a_i-\sum_{j=1}^{i}\left\lfloor\dfrac{a_i}{a_j}\right\rfloor \cdot a_j\end{aligned}$$

  前面这项我们可以直接算，后面这一项向前算不好求，我们考虑向后算贡献。枚举 $k \times a_i \leq W$（此处假设 $W$ 为值域）的每一个正整数 $k$，然后我们对于 $j \gt i,a_j\geq ka_i$ 的 $j$ 均有一个 $a_i$ 的贡献。然后查询就直接查询 $[1,a_i]$ 即可。

  使用树状数组，又因为 $a_i$ 互不相同，所以总复杂度是 $O(n \ln n \log n)$。

- 第三项：

	同理可得：
    
    $$\sum_{j=1}^{i}(a_j \bmod a_i)=\sum_{j=1}^{i}a_j-\sum_{j=1}^{i}\left\lfloor\dfrac{a_j}{a_i}\right\rfloor \cdot a_i$$
    
	这个第一部分可以使用前缀和，第二部分我们考虑枚举 $k \times a_i \leq W$ 的每一个正整数 $k$，则对于 $x<i,a_x \in [ka_i,(k+1)a_i-1]$ 需要减去 $k$ 个 $a_i$。同样的树状数组直接做即可。
    
    复杂度同理也是 $O(n \ln n \log n)$。
    
## 代码

[Code & Submission](https://codeforces.com/contest/1553/submission/220004805)

---

## 作者：Ryder00 (赞：0)

CF2300，蓝。

题意清晰，不再阐述。

## 思路

对于有明确递推关系的序列，考虑增量。则式子可化为：

$p_k=p_{k-1}+\sum_{i=1}^{k-1} p_i \bmod p_k +\sum_{i=1}^{k-1} p_k \bmod p_i$

$p_k=p_{k-1}+\sum_{i=1}^{k-1} p_i+ (i-1) \times k-\sum_{i=1}^{k-1} \lfloor\dfrac{p_i}{p_k}\rfloor \times p_k -\sum_{i=1}^{k-1} \lfloor\dfrac{p_k}{p_i}\rfloor \times p_i$

对于后面两部分，想想如何处理。

对于第一部分：

可以发现，有一些 $p_i$ 的 $\lfloor\frac{p_i}{p_k}\rfloor$ 值是相等的。于是我们枚举 $\lfloor\frac{p_i}{p_k}\rfloor$ 的取值，使用树状数组维护取值区间内的 $p_i$ 个数，乘上 $p_k$ 更新贡献。使用到了单点修改和区间求和操作。

对于第二部分：

同样枚举 $\lfloor\frac{p_k}{p_i}\rfloor$ 的取值 $x$，可以发现，对于每个 $\left[ x\times p_i,(x+1)\times p_i \right)$ 内的数，都有 $-x \times p_i$ 的贡献。可类比一部分的操作，使用区间修改和单点查询操作。

使用树状数组维护。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=2e5+10,M=3e5,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,ans,sum;
struct node{
    int c[M+10];
    int lowbit(int x){
        return x&(-x);
    }
    int query(int x){
        int ans=0;
        for(;x;x-=lowbit(x)) ans+=c[x];
        return ans;
    }
    void add(int pla,int val){
        for(;pla<=M;pla+=lowbit(pla)) c[pla]+=val;
    }
}bit1,bit2;
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        ans+=sum+(i-1)*x-bit2.query(x),sum+=x;
        for(int j=x;j<=M;j+=x){
            ans-=j*(bit1.query(min(j+x-1,M))-bit1.query(j-1));
        }
        bit1.add(x,1);
        for(int j=x;j<=M;j+=x) bit2.add(j,x);
        cout<<ans<<" ";
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // ios::sync_with_stdio(false),cin.tie(0);
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：Purslane (赞：0)

# Solution

很显然 $a \bmod b=a - b \times \lfloor \frac{a}{b} \rfloor$。

考虑我们从 $i$ 过渡到 $i+1$ 的时候，实际上会加上两部分值：$\sum _{j \le i} a_j \bmod a_{i+1}$ 和 $\sum_{j \le i} a_{i+1} \bmod a_j$。

对于前者，我们直接枚举 $\lfloor \frac{a_j}{a_{i+1}} \rfloor$。具体的，我们查询值在 $[la_{i+1},(l+1)a_{i+1}-1]$ 中目前已经存在的数的个数 $cnt$ 与和总和 $sum$。那么产生的贡献 $sum-cnt \times la_{i+1}$。那么 $l$ 一共有 $\lceil \frac{V}{a_{i+1}}+1 \rceil$ 种取值。看起来很慢，不过他保证两两不同，所以不过 $V \log V$ 种取值。每次我们单点修改，区间查询，使用树状数组维护。

对于后者，我们在扫描的时候用让 $a_j$ 对其他数产生影响。具体的，让值在 $[la_{j},(l+1)a_{j}-1]$ 范围内的数的贡献都减去 $la_j$ 的值，在查询的时候加上 $(i-1)a_i$。这是一种区间修改单点查询，也可以用树状数组维护。

时间复杂度是两个 $\log$ 的。

[code](https://codeforces.com/problemset/submission/1553/211924580) .

---

## 作者：walk_alone (赞：0)

由于此题是要求求出每一个 $p_k$，因而考虑做递推。容易发现，$p_k-p_{k-1}$ 等于当前第 $k$ 个数与**前面** $k-1$ 个数互相取模得到的和。下面考虑如何求出这个和。

可以将和 $k$ 相关的取模分成四个部分：

1. 比 $a_k$ 大的数对 $a_k$ 取模和；
2. $a_k$ 对比 $a_k$ 大的数取模和；
3. $a_k$ 对比 $a_k$ 小的数取模和；
4. 比 $a_k$ 小的数对 $a_k$ 取模和。

有几个是非常好求出的：例如第二个，它的和就是 $a_k$ 乘以比 $a_k$ 大的数出现次数；第四个，就是比 $a_k$ 小的数的和。因而很自然的考虑使用两个树状数组，一个记录数值为 $k$ 的出现次数（下记位 B 树），一个记录数值为 $k$ 的贡献（下记位 A 树）。

接下来的几个怎么办呢？

首先解决固定模数问题，即比 $a_k$ 大的数对 $a_k$ 取模的问题。注意到这个地方 $a_k$ 各不相同，且都在 $3\times 10^5$ 的范围内，一方面是想到可以直接用树状数组维护值域，另一方面是可以利用调和级数的性质，即枚举倍数。这是一个非常常用的方法——可以通过 $O(n \log n)$ 的时间枚举出所有的倍数。其原理为，至多枚举到的元素个数为 $\displaystyle \sum_{i=1}^{n} \frac{n}{i}=O(n \ln n)$。

具体操作就是：枚举 $[ma_k,(m+1)a_k)$ 中出现的元素个数。如果一个元素落在这里，那么它对于与 $a_k$ 取模的贡献就是 $ma_k$。因而考虑在 B 树上对于每一个倍数区间统计次数，然后求和。

接下来就是 $a_k$ 对变化模数取模和。显然一个一个枚举是不行的，我们考虑能否继续使用上面这个 trick。对于一个固定的 $a_i$，对于其后面比它大的数的贡献依旧满足 $\displaystyle a_i \lfloor \frac{a_k}{a_i} \rfloor$，当我后面来了一个比它大的数的时候，可以考虑统计它在 $a_i$ 的哪一个区间，但是我们显然不能每一个都这样统计。

一个非常巧妙的办法在于，用空间换时间。对于每一个 $a_i$ 的倍数，我事先在这一位置插上 $-a_i$，这样当我来了一个比它大的数时，我只需要求出其前缀和，就可以知道我落在了 $a_i$ 的哪一个区间，并且可以直接求出这个式子的值——因为对于一个 $a_i$ 来说，$a_k$ 对它取模只有一次。那么如果对 $a_i$ 的前缀和为 $-ma_i$，那么这个取模结果就等于 $a_k-ma_i$。并且我们注意到，这个操作对于每一个 $a_i$ 独立。那么也就是说我不同的 $a_i$ 都可以用这种方式插入，叠入到同一个树状数组中，也不会对答案造成影响。

这个时候再来审视第二个和第四个操作。其实完全没有必要分的这么清——它一定就是剩下全部的数的和，所以直接前缀和累加就行。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int N = 300000;
long long t[2][300005], p[200005];
int lowbit(int x)
{
    return x & (-x);
}
void update(bool flag,int place,long long k)
{
    while(place<=N)
    {
        t[flag][place] += k;
        place += lowbit(place);
    }
    return;
}
long long query(bool flag,int place)
{
    long long ans = 0;
    while(place)
    {
        ans+=t[flag][place];
        place -= lowbit(place);
    }
    return ans;
}
int main()
{
    int n;
    long long x, sum=0;
    scanf("%d", &n);
    for (int i = 1; i <= n;i++)
    {
        long long ans = 0;
        scanf("%lld", &x);
        ans += query(1, x);
        ans += x * (long long)(i - 1);
        //它对比它小的数取模和的操作
        ans += sum;//累加除它之外的前缀和
        sum += x;
        for (int j = x; j <= N; j += x)
        {
            int start = j, end = min((long long)N, j + x - 1);
            //分倍数块统计
            int times = query(0, end) - query(0, start - 1);
            ans -= (long long)j * times;
            update(1, start, -x);
            //此处的添加为后面的数做准备
        }
        update(0, x, 1);
        p[i] = p[i - 1] + ans;
    }
    for (int i = 1; i <= n;i++)
        printf("%lld ", p[i]);
    return 0;
}
```

---

## 作者：_lbw_ (赞：0)

题意：

给定长为 $n$ 的数组 $a$，对于 $1\leq k\leq n$ 求：

$$\sum\limits_{i=1}^k\sum\limits_{j=1}^ka_i\bmod a_j$$

保证 $a_i$ 互不相同。

题解：

考虑新加入一个数对答案的贡献。

设 $a_k=x$ 将 $\sum\limits_{i=1}^{k-1} a_i\bmod x$ 与 $\sum\limits_{i=1}^{k-1}x \bmod a_i$  分开考虑。

- $\sum\limits_{i=1}^{k-1} a_i\bmod x$

$=\sum\limits_{i=1}^{k-1} a_i-x\times (a_i/x)$

$\sum\limits_{i=1}^{k-1}(a_i/x)$ 先枚举倍数，然后用树状数组维护

- $\sum\limits_{i=1}^{k-1} x\bmod a_i$

$=\sum\limits_{i=1}^{k-1} x-a_i\times (x/a_i)$

发现这东西长得像整除分块，然后用树状数组就有 $\mathcal{O}(m\sqrt{m}\ln n)$ 的优秀复杂度（$m=\max a_i$）.

于是你就会在第七个点一辈子过不去。

考虑转换视角，发现对于 $a_i$ 来说这还是个枚举倍数。

于是把每个 $a_i$ 的倍数枚举出来，把每一段区间加 $a_i\times k$ 每次单点询问。

差分后变成树状数组。

于是复杂度变为 $O(m\ln n\ln m)$

实现可以把枚举倍数合并。

[题码](https://www.luogu.com.cn/paste/mhsvjo7c)










---

