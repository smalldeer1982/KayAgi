# Boring Queries

## 题目描述

Yura owns a quite ordinary and boring array $ a $ of length $ n $ . You think there is nothing more boring than that, but Vladik doesn't agree!

In order to make Yura's array even more boring, Vladik makes $ q $ boring queries. Each query consists of two integers $ x $ and $ y $ . Before answering a query, the bounds $ l $ and $ r $ for this query are calculated: $ l = (last + x) \bmod n + 1 $ , $ r = (last + y) \bmod n + 1 $ , where $ last $ is the answer on the previous query (zero initially), and $ \bmod $ is the remainder operation. Whenever $ l > r $ , they are swapped.

After Vladik computes $ l $ and $ r $ for a query, he is to compute the least common multiple (LCM) on the segment $ [l; r] $ of the initial array $ a $ modulo $ 10^9 + 7 $ . LCM of a multiset of integers is the smallest positive integer that is divisible by all the elements of the multiset. The obtained LCM is the answer for this query.

Help Vladik and compute the answer for each query!

## 说明/提示

Consider the example:

- boundaries for first query are $ (0 + 1) \bmod 3 + 1 = 2 $ and $ (0 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 2] $ is equal to $ 6 $ ;
- boundaries for second query are $ (6 + 3) \bmod 3 + 1 = 1 $ and $ (6 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 1] $ is equal to $ 2 $ ;
- boundaries for third query are $ (2 + 2) \bmod 3 + 1 = 2 $ and $ (2 + 3) \bmod 3 + 1 = 3 $ . LCM for segment $ [2, 3] $ is equal to $ 15 $ ;
- boundaries for fourth query are $ (15 + 2) \bmod 3 + 1 = 3 $ and $ (15 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 3] $ is equal to $ 30 $ .

## 样例 #1

### 输入

```
3
2 3 5
4
1 3
3 3
2 3
2 3```

### 输出

```
6
2
15
30```

# 题解

## 作者：louhao088 (赞：30)

主席树好题。


------------

看其他题解都是根号分治做法，来一种不带根号做法。


------------

首先考虑简单情况，没有模数，那么这个问题可以用线段树解决，因为最小公倍数可以合并。

但有了模数，我们就不能简单合并了，但我们考虑最小公倍数的性质，即乘积之和再除以两两数之间的最大公约数。所以这个问题可以转换为求一段区间两两最大公约数。

解决这个问题，我们可以先把每个数质因数分解，那么对于他的每个质因数的 $x$ 次幂都可以找到之前第一次出现的地方，具体的我们可以用桶记录每个数出现位置。

这样一种思路就出现了，即在每个质因数的 $x$ 次幂之前第一次出现的地方乘上 $x$ 的逆元，这样就可以消掉两数的最小公倍数。然后最后在这个数的位置乘上他的值，这样查询 $l\to r$ 这一段区间时，只需查询再加到第 $i$ 个数时 $l \to r$ 的值，这个问题很容易用主席树解决。


------------


由于质因数个数是 $\log n$ 级别，所以插入操作要进行 $n \log n$ 次。
故时间复杂度为 $n \log^2 n$ ，空间复杂度为 $n \log^2 n$。


------------

注意本题略微卡空间，数组要用 int 存储。


------------
代码如下，仅供参考

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define mid (l+r>>1)
#define lowbit (x&-x)
const int maxn=1e5+5,M=2e5,mod=1e9+7;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,Rt[maxn],sum[maxn*400],tot,inv[M+5],f[M+5],s[M+5],x,ans=0,l,r;
int ls[maxn*400],rs[maxn*400];
int merge(int pre,int l,int r,int x,int num)
{
	if(l>x||r<x)return pre;
	int rt=++tot;
	if(l==r){sum[rt]=1ll*sum[pre]*num%mod;return rt;}
	ls[rt]=merge(ls[pre],l,mid,x,num),rs[rt]=merge(rs[pre],mid+1,r,x,num);
	sum[rt]=1ll*sum[ls[rt]]*sum[rs[rt]]%mod;return rt;
}
int query(int rt,int l,int r,int x)
{
	if(l>=x)return sum[rt];
	if(r<x)return 1;
	return 1ll*query(ls[rt],l,mid,x)*query(rs[rt],mid+1,r,x)%mod;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();inv[1]=1,sum[0]=1;
	for(int i=2;i<=M;i++)
	{
		inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
		if(!f[i]){for(int k=i;k<=M;k+=i)f[k]=i;}
	}
	for(int i=1;i<=n;i++)
	{
		x=read();Rt[i]=Rt[i-1];
		while(f[x])
		{
			int k=f[x],t=1;
			while(x%k==0)
			{
				t=t*k;x=x/k;
				if(s[t])Rt[i]=merge(Rt[i],1,n,s[t],inv[k]);
				s[t]=i;
			}Rt[i]=merge(Rt[i],1,n,i,t);
		}
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		l=read(),r=read();l=(l+ans)%n+1,r=(r+ans)%n+1;
		if(l>r)swap(l,r);
		ans=query(Rt[r],1,n,l);printf("%d\n",ans);
	}
 	return 0;
}

```



---

## 作者：IntrepidStrayer (赞：24)

$\operatorname{lcm}$ 能被区间内的每个数整除。考虑一个质数 $p$，它在 $a_i~(l\le i\le r)$ 中的次数（质因数分解后 $p$ 的指数）一定小于等于它在 $\operatorname{lcm}$ 中的次数。那么可以把 $\operatorname{lcm}$ 表示成 $\prod\limits_{p\text{ 是质数}}p^{\max\limits_{l\le i\le r}\{cnt_{i,p}\}}$，其中 $cnt_{i,p}$ 表示 $a_i$ 中 $p$ 的次数。

考虑根号分治。小于 $450$ 的质数有 $87$ 个，这些可以用 $87$ 个 st 表做。

我们知道一个数 $x$ 最多有一个大于 $\sqrt x$ 的质因子。把每个 $a_i$ 中小于 $450$ 的质因子全部除掉，剩下的是 $1$ 或大于 $450$ 的质数。

现在问题变成了求区间 $[l,r]$ 中出现过的数的乘积（重复的只算一次）。设 $pre_i$ 表示 $[1,i-1]$ 中 $a_i$ 最后一次出现的位置，没有出现则为 $0$。这个可以 $O(n)$ 求。

对于一个 $i~(l\le i\le r)$，若 $l\le pre_i$，说明 $[l,i-1]$ 中出现了一个与 $a_i$ 相等的数，那么这个 $i$ 是不能算贡献的。

问题又变成了 $\prod\limits_{i=l}^r[pre_i\le l-1]a_i$。考虑建 $n$ 棵线段树，第 $j$ 棵维护满足 $pre_i\le j$ 的数的乘积（$pre_i>j$ 的位置上都为 $1$）。容易发现对于 $j~(j>0)$，最多存在一个 $i$ 满足 $pre_i=j$，也就是说从第 $j-1~(j>0)$ 棵线段树到第 $j$ 棵，最多只用修改一个数。那么可以用主席树做。

整体思路：

1. 线性筛求质数
1. 计算每个数中各个质数的次数并把它们除掉
1. 建 ST 表
1. 建主席树
1. 回答询问

下面是代码（$pre$ 没有用数组记录下来）

```cpp
#include <cstdio>

using namespace std;

typedef long long ll;
inline int max(int x, int y) {return x > y ? x : y;}
inline int min(int x, int y) {return x < y ? x : y;}
inline void swap(int &x, int &y) {x ^= y ^= x ^= y;}
#define rei register int
#define rep(i, l, r) for(rei i = l, i##end = r; i <= i##end; ++i)
#define per(i, r, l) for(rei i = r, i##end = l; i >= i##end; --i)
#define ci const int
char inputbuf[1 << 23], *p1 = inputbuf, *p2 = inputbuf;
#define getchar() (p1 == p2 && (p2 = (p1 = inputbuf) + fread(inputbuf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
	int res = 0; char ch = getchar(); bool f = true;
	for(; ch < '0' || ch > '9'; ch = getchar())
		if(ch == '-') f = false;
	for(; ch >= '0' && ch <= '9'; ch = getchar())
		res = res * 10 + (ch ^ 48);
	return f ? res : -res;
}
const int N = 2e5 + 15, SQRT = 450, P = 1e9 + 7;
int n, a[N], b[N], rt[N], tot, lg[N], lc[N * 20], rc[N * 20], pos[N * 2], pr[SQRT], cnt;
bool npr[SQRT];
char st[90][N][18];
ll mul[N * 18], poww[100][20];

inline void upd(int p) {
	mul[p] = mul[lc[p]] * mul[rc[p]] % P;
}

void get_prime() {
	npr[1] = 1;
	rep(i, 2, SQRT - 1) {
		if(!npr[i]) pr[++ cnt] = i;
		for(rei j = 1; j <= cnt && i * pr[j] < SQRT; ++ j) {
			npr[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

inline int query(int k, int l, int r) {
	int p = lg[r - l + 1];
	return max(st[k][l][p], st[k][r - (1 << p) + 1][p]);
}

int build(int l, int r) {
	int p = ++ tot, mid = l + r >> 1;
	mul[p] = 1;
	if(l == r) return p;
	lc[p] = build(l, mid);
	rc[p] = build(mid + 1, r);
	return p;
}

void modify(int p, int l, int r, ci &t, ci &x) {
	if(l == r) { mul[p] = x; return ; }
	int mid = l + r >> 1;
	if(t <= mid) modify(lc[p], l, mid, t, x);
	else modify(rc[p], mid + 1, r, t, x);
	upd(p);
}

int modify2(int rt, int l, int r, ci &t, ci &x) {
	int p = ++ tot, mid = l + r >> 1;
	if(l == r) { mul[p] = x; return p; }
	if(t <= mid) lc[p] = modify2(lc[rt], l, mid, t, x), rc[p] = rc[rt];
	else rc[p] = modify2(rc[rt], mid + 1, r, t, x), lc[p] = lc[rt];
	upd(p);
	return p;
}

ll query(int p, int l, int r, ci &tl, ci &tr) {
	if(tl <= l && r <= tr) return mul[p];
	int mid = l + r >> 1;
	ll res = 1;
	if(tl <= mid) res = query(lc[p], l, mid, tl, tr);
	if(mid < tr) res = res * query(rc[p], mid + 1, r, tl, tr) % P;
	return res;
}

void input() {
	n = read();
	rep(i, 1, n) {
		a[i] = read();
		rep(j, 1, cnt)
			while(a[i] % pr[j] == 0) {
				a[i] /= pr[j];
				st[j][i][0] ++ ;
			}
	}
}

void build_st() {
	rep(i, 2, n) lg[i] = lg[i / 2] + 1;
	rep(k, 1, cnt) rep(j, 1, lg[n])
		for(rei i = 1; i + (1 << j) - 1 <= n; ++ i)
			st[k][i][j] = max(st[k][i][j - 1], st[k][i + (1 << j - 1)][j - 1]);
}

void build_sgt() {
	rt[0] = build(1, n);
	rep(i, 1, n) {
		if(!pos[a[i]]) modify(rt[0], 1, n, i, a[i]);
		else b[pos[a[i]]] = i;
		pos[a[i]] = i;
	}
	rep(i, 1, n) {
		if(b[i]) rt[i] = modify2(rt[i - 1], 1, n, b[i], a[b[i]]);
		else rt[i] = rt[i - 1];
	}
}

void solve() {
	int l, r;
	ll ans = 0;
	rep(i, 1, cnt) {
		poww[i][0] = 1;
		rep(j, 1, 20) poww[i][j] = (poww[i][j - 1] * pr[i]) % P;
	}
	for(int q = read(); q; -- q) {
		l = (read() + ans) % n + 1;
		r = (read() + ans) % n + 1;
		if(l > r) swap(l, r);
		ans = 1;
		rep(i, 1, cnt) ans = ans * poww[i][query(i, l, r)] % P;
		ans = ans * query(rt[l - 1], 1, n, l, r) % P;
		printf("%lld\n", ans);
	}
}

signed main() {
	get_prime();
	input();
	build_st();
	build_sgt();
	solve();
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：12)

## 题意
给出一个长度为 $n$ 的数列 $a$，$m$ 组询问，每次给出 $l,r$，求 $\mathrm{lcm}(a_l,\dots,a_r)\bmod 10^9+7$。

强制在线，$n\le 10^5,a_i\le2\times 10^5$
## 题解
首先这个问题有一个严格弱化的问题，也就是求 $n$ 个数的 $\mathrm{lcm}$，这也就启示我们不能够直接暴力求 $\mathrm {lcm}$ 而应该在每个质因子时统计贡献最后乘起来。

这个问题同样要从质因子的角度分析。考虑当右端点固定时，一个质因子的贡献一定是单调不降的，因为 $[l,r]$ 质因子的贡献是最多出现次数。考虑这样一段折线：

![](https://cdn.luogu.com.cn/upload/image_hosting/dcuq90vp.png)

在每一个拐点的地方记录乘上了 $p$ 的多少次，然后查询就相当于求一段区间的积。可以用单调栈维护这些拐点。

![](https://cdn.luogu.com.cn/upload/image_hosting/se89nucx.png)

如果现在又新加入了一个值（绿线），那么比绿线低的拐点（蓝点）先给删掉，把更新折线，然后更新绿点的值。

因为质因子的个数和是 $\mathcal O(n\log n)$ 级别的，所以不同质因子的拐点个数也是这个级别的，如果用线段树修改和查询那么就是两只 $\log$。

如果可以离线那么这样就做完了，但出题人强制在线还需要可持久化数据结构。可能有一定卡空间但总体思路还是比较自然的。
## 代码
```cpp
// Problem: CF1422F Boring Queries
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1422F
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define pb push_back
#define pc putchar
#define mp make_pair
#define fi first
#define se second
#define chkmx(a,b) ((a)=max((a),(b)))
#define chkmn(a,b) ((a)=min((a),(b)))
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool f=false;for(;!isdigit(c);c=getchar())f|=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<typename T ,typename ...Arg>inline void read(T &x,Arg &...args){read(x);read(args...);}
template<typename T>inline void write(T x){if(x<0)putchar('-'),x=-x;if(x>=10)write(x/10);putchar(x%10+'0');}
//#define int long long
#define mid ((l+r)>>1)
typedef long long ll;
template<const int mod>
struct modint{
    int x;
    modint<mod>(int o=0){x=o;}
    modint<mod> &operator = (int o){return x=o,*this;}
    modint<mod> &operator +=(modint<mod> o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint<mod> &operator -=(modint<mod> o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint<mod> &operator *=(modint<mod> o){return x=1ll*x*o.x%mod,*this;}
    template<class I>friend modint<mod> operator +(modint<mod> a,I b){return a+=b;}
    template<class I>friend modint<mod> operator -(modint<mod> a,I b){return a-=b;}
    template<class I>friend modint<mod> operator *(modint<mod> a,I b){return a*=b;}
    modint<mod> operator - () {return x?mod-x:0;}
};
enum{mod=1000000000+7};
using mint=modint<mod>;
const int N=2e5+100;
int n,m,a[N],rt[N];
struct node{
	mint prod;
	int lc,rc;
}t[N*150];
int tot;
int build(int l,int r){
	int x=++tot;
	t[x].prod=1;
	if(l==r)return x;
	t[x].lc=build(l,mid);
	t[x].rc=build(mid+1,r);
	return x;
}
int mdf(int y,int l,int r,int pos,mint val){
	int x=++tot;t[x]=t[y];t[x].prod*=val;
	if(l==r)return x;
	if(pos<=mid)t[x].lc=mdf(t[y].lc,l,mid,pos,val);
	else t[x].rc=mdf(t[y].rc,mid+1,r,pos,val);
	return x;
}
mint qry(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return t[x].prod;
	if(r<ql||qr<l)return 1;
	return qry(t[x].lc,l,mid,ql,qr)*qry(t[x].rc,mid+1,r,ql,qr);
}
int f[N];
stack<pair<int,int>>s[N];
mint inv[N];
signed main(){
	inv[1]=1;for(int i=2;i<N;i++)inv[i]=-inv[mod%i]*(mod/i);
	for(int i=2;i<N;i++)if(!f[i])
		for(int j=i;j<N;j+=i)f[j]=i;
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	rt[0]=build(1,n);
	for(int i=1;i<=n;i++){
		rt[i]=rt[i-1];
		while(a[i]>1){
			int p=f[a[i]],kk=1;
			while(a[i]%p==0)a[i]/=p,kk*=p;mint lst=1;
			while(s[p].size()&&s[p].top().se<=kk){
				int pos=s[p].top().fi;
				int val=s[p].top().se;s[p].pop();
				rt[i]=mdf(rt[i],1,n,pos,inv[val]*lst);
				lst=val;
			}
			if(s[p].size())
				rt[i]=mdf(rt[i],1,n,s[p].top().fi,inv[kk]*lst);
			rt[i]=mdf(rt[i],1,n,i,kk);
			s[p].push(mp(i,kk));
		}
	}
	read(m);mint lst=0;
	while(m--){
		int l,r;read(l,r);
		l=(l+lst.x)%n+1,r=(r+lst.x)%n+1;
		if(l>r)swap(l,r);
		//printf("%d %d\n",l,r);
		write((lst=qry(rt[r],1,n,l,r)).x);pc('\n');
	}
}
```

---

## 作者：George_Plover (赞：12)

看了一下题解区的大佬们，无一例外的全部上了可持久化线段树，实在佩服。

鄙人不才，虽然早就做过了 HH的项链 这道题，但是想题的时候还是没有自然的去想可持久化线段树的写法。

这里提供一个分块预处理的做法。总复杂度 $O(222(n+q) +(n+q)\sqrt n )$ 。

-----

### 题意描述：

给出 $n$ 个整数 $1\le a_i \le 2\times 10^5$ ，给出 $q$ 组询问 $[l,r]$ ，每次询问区间内数的 lcm ，强制在线，答案对 $10^9+7$ 取模。 $n,q \le 10^5$ 。

------

### 题目分析：

* 首先考虑到 lcm 非常大，必须在计算中取模，因此不能够直接的用区间求 lcm 的算法解决。所以考虑答案是质数幂次之积的形式，即 $ans=p_1^{k_1}p_2^{k_2}\dots p_s^{k_s}$ 。

* 观察性质， $a_i$ 范围很小，因此，对于 $\sqrt{2\times 10^5} ≈ 447 $ 以内的质因子，幂次才可能大于 $1$ ，其余的质因子的幂次要么是 $1$ ，要么是 $0$ 。因此我们考虑分段处理。

-----

### 做法：

#### 第一部分

考虑处理 $447$ 以内的质因子对答案的贡献，打表发现，这样的质因子一共有 $86$ 个。到了这里，很多人就想用 $86$ 个 ST 表来搞了。但我们暂时不慌，再考虑每个质因子 $p_i$ 最高的幂次是 $\log_{p_i}200000$，所以我们可以继续打表，发现 $447$ 以内的质因子对答案的贡献只有 $\sum_{i=1}^{86} (log_{p_i}200000) ≈ 222$ 种状态。每个状态对应的值形如 $p_i^{k}$ 。

因此，我们可以用一个 $222 \times n$ 的数组 `pre[222][n]`，其中`pre[][i]`存下的是每个质因子的某个幂次在 $[1,i]$ 范围内最后出现的位置。 那么我们在求解这一段对答案的贡献的时候，可以直接枚举所有 $86$ 个质因子，对每个质因子从大到小枚举幂次，找到第一个`pre[][r]>=l` 幂次，这就是这个质因子对答案的贡献。这样我们就可以 $O(222)$ 处理每个询问的第一部分了。

-----

#### 第二部分

考虑第二部分，我们先把原来的 $a_i$ 商掉所有 $447$ 以内的质因子。那么接下来求解的贡献，其实就是区间 $[l,r]$ 范围内出现过的数字的积。这里很多人就可持久化线段树上去搞了，但是我们考虑分块的做法。首先我们先要明白一点，假如我们已经处理出区间 $[a,b]$ 的答案了，如果我们想拓展这个区间到 $[a,b+1]$ 或 $[a-1,b]$，是可以 $O(1)$ 做到的，只需要我们预处理出每个 $a_i$ 左边最近一次出现的位置和右边最近一次出现的位置就可以了。因为利用预处理的值我们可以 $O(1) $ 判断新拓展的值有没有在 $[a,b]$ 出现过。既然如此，我们为什么不考虑分块呢？

每 $\sqrt n$ 长度一个块，我们用一个二维数组 `itv[L][R]` 表示从第 $L$ 块到第 $R$ 块的区间的答案。这个二维数组的空间只有 $O(n)$ ，并且我们可以 $O(n\sqrt n)$ 预处理出这个二维数组。有了这个二维数组，我们就可以把询问区间 $[l,r]$ 分为三段 $[l,L-1],[L,R],[R+1,r]$ ，其中 $[L,R]$ 是整块的一个区间，可以直接用预处理的 `itv[][]` 数组得到其贡献，然后再把这个区间向左右拓展，因此不满整块的 $[l,L-1],[R+1,r]$ 长度都不超过 $\sqrt n$，因此我们只需要做 $O(2\sqrt n)$ 次拓展即可求出区间 $[l,r]$ 的贡献。

-----

于是把上面两个过程结合起来，就可以以 $O(222(n+q) +(n+q)\sqrt n )$ 的时间复杂度和 $O(222n)$ 的空间复杂度解决问题了。 不需要用到可持久化线段树的技巧。

----

### 代码：

```cpp
#include <map>
#include <cmath> 
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
#define MOD 1000000007
#define MAXN 220000
#define MAXC 230
#define LSQRT 87
#define BSIZE 350
using namespace std;
int n,m,a[MAXN];
int Div[MAXN],prime[MAXN],cnt;
int range[MAXN];
int base[MAXN];
int power[LSQRT][20];
int pre[MAXC][MAXN];
int loc[MAXN],lm[MAXN],rm[MAXN];
int itv[BSIZE][BSIZE];
bool vis[MAXN];
void get_p()
{
    for(int i=2;i<MAXN;i++)
    {
        if(!Div[i])
        {
            prime[++cnt]=i;
            Div[i]=i;
        }
        for(int j=1;j<=cnt&&prime[j]*i<MAXN;j++)
        {
            Div[prime[j]*i]=prime[j];
            if(prime[j]==Div[i])
                break;
        }
    }
}
void prepare_first()
{
    
    int sum=0;
    for(int i=1;i<LSQRT;i++)
    {
        range[i]=(log(200000)/log(prime[i]));
        base[i]=sum;
        sum+=range[i];
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<MAXC;j++)
            pre[j][i]=pre[j][i-1];
        for(int j=1;j<LSQRT;j++)
        {
            int cnt = 0;
            while(!(a[i]%prime[j]))
            {
                cnt++;
                a[i]/=prime[j];
            }
            if(cnt)
                pre[base[j]+cnt-1][i]=i;
        }
    }
    for(int i=1;i<LSQRT;i++)
    {
        int tmp=1;
        for(int j=1;j<20;j++)
        {
            tmp=1ll*tmp*prime[i]%MOD;
            power[i][j]=tmp;
        }
    }
}

void prepare_second()
{
    for(int i=1;i<=n;i++)
    {
        lm[i]=loc[a[i]];
        loc[a[i]]=i;
    }
    for(int i=1;i<MAXN;i++)loc[i]=n+1;
    for(int i=n;i>=1;i--)
    {
        rm[i]=loc[a[i]];
        loc[a[i]]=i;
    }

    for(int i=1;i<=n;i+=BSIZE)
    {
        memset(vis,0,sizeof(vis));
        int tmp=1;
        for(int j=i;j<=n;j++)
        {
            if(!vis[a[j]])
            {
                vis[a[j]]=1;
                tmp=1ll*tmp*a[j]%MOD;
            }
            if( !(j%BSIZE) || j==n)
            {
                itv[i/BSIZE][(j-1)/BSIZE]=tmp;
            }
        }
    }
}
int main()
{
    get_p();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    prepare_first();
    prepare_second();
    scanf("%d",&m);
    int lst=0;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x=(lst+x)%n+1;
        y=(lst+y)%n+1;
        if(x>y)
            swap(x,y);
        lst=1;
        for(int i=1;i<LSQRT;i++)
        {
            for(int j=base[i]+range[i]-1;j>=base[i];j--)
            {
                if(pre[j][y]>=x)
                {
                    lst=1ll*lst*power[i][j-base[i]+1]%MOD;
                    break;
                }
            }
        }

        if(y-x+1 <= 2*BSIZE)
        {
            for(int i=x;i<=y;i++)
                if(lm[i]<x)
                    lst=1ll*lst*a[i]%MOD;
        }
        else
        {
            int L=(x-1)/BSIZE + 1,R=(y-1)/BSIZE - 1;
            lst=1ll*lst*itv[L][R]%MOD;
            for(int i=x;i<=L*BSIZE;i++)
                if(rm[i]>(R+1)*BSIZE)
                    lst=1ll*lst*a[i]%MOD;
            for(int i=(R+1)*BSIZE+1;i<=y;i++)
                if(lm[i]<x)
                    lst=1ll*lst*a[i]%MOD;
        }
        printf("%d\n",lst);
    }
    
    
    return 0;
}
```




---

## 作者：7KByte (赞：7)

裸题就是神题。

强制在线区间 $\rm lcm$。

我们可以像区间 $\gcd$ 一样，直接建立线段树，然后每个节点维护对应子区间的 $\rm lcm$。

由于 $ \rm lcm$ 和 $\gcd$ 具有相似的性质。所以$\gcd$可做，$\rm lcm$ 也可做，于是这道题就做完了。

但当你开始码代码后才发现不能这么做。因为$\gcd$只减不增，但$\rm lcm$只增不减，且$\rm lcm$的增长速度很快，我们不开高精不能保存完整信息，开了高精时空复杂度会爆，取模会得到错误的结果。

我们需要寻求更好的算法。

一个比较套路的做法，强制在线算法应该先考虑离线做法。

我们对询问离线，按区间右端点排序。

对于区间右端点固定，当左端点向左移动时，每次会增加一个数。当且仅当增加的数存在一个因子$p^w$，原来的$\rm lcm$的$p$的指数小于$w$时，答案会增大。更具体一点，原来$\rm lcm$的$p$的指数会对$w$取$\max$。

这样对于两个数$a_i,a_j(i<j)$，质因子$p$对应的指数分别为$x,y$，若$x<y$，则$a_i$一定不会更新答案。这样的$a_i$可以直接丢掉。

我们发现这非常类似单调栈的过程。但是我们还有区间左端点的限制，这可以用线段树维护一下。

回到原题，我们要强制在线，一个比较套路的做法是直接上可持久化线段树，然后这道题就做完了。

时间复杂度与$a_i$的质因子的指数和有关，不大会算复杂度/kk。不过粗略的上下界是$\rm O(N\ log\ N )\sim O(N\ log^2\ N)$。主席树时间和空间同阶。

轻微卡空间/kk。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
#define P 1000000007
using namespace std;
int n,u[N],m,tot,rt[N];
struct node{
	int l,r,mul;
}a[20000000];
#define ls a[x].l
#define rs a[x].r
int build(int l,int r){
	int x=++tot;a[x].mul=1;
	if(l==r)return x;
	int mid=(l+r)>>1;
	a[x].l=build(l,mid);
	a[x].r=build(mid+1,r);
	return x;
}
int ins(int x,int l,int r,int pos,int val){
	int y=++tot;a[y]=a[x];a[y].mul=a[y].mul*val%P;
	if(l==r)return y;
	int mid=(l+r)>>1;
	if(mid>=pos)a[y].l=ins(ls,l,mid,pos,val);
	else a[y].r=ins(rs,mid+1,r,pos,val);
	return y;
}
int ask(int x,int l,int r,int L,int R){
	if(L>=l&&R<=r)return a[x].mul;
	int mid=(L+R)>>1,now=1;
	if(mid>=l)now=now*ask(ls,l,r,L,mid)%P;
	if(mid<r)now=now*ask(rs,l,r,mid+1,R)%P;
	return now;
}
int Pow(int x,int y){
	int now=1;
	for(;y;y>>=1,x=x*x%P)if(y&1)now=now*x%P;
	return now;
}
int pre[N],pm[N];const int w = 200000 ;
vector<pair<int,int> >c;
signed main(){
	rep(i,2,w)if(!pm[i])rep(j,1,w){
		if(i*j>w)break;
		pm[i*j]=i;
	}
	scanf("%lld",&n);
	rep(i,1,n)scanf("%lld",&u[i]);
	rt[0]=build(1,n);
	rep(i,1,n){
		int x=u[i];rt[i]=rt[i-1];
		c.clear();
		while(pm[x]){
			int now=pm[x],cnt=0,k=1;
			int inv=Pow(now,P-2);
			while(x%now==0){
				x/=now,cnt++,k*=now;
				if(pre[k])c.push_back(make_pair(pre[k],inv));
				pre[k]=i;
			}
			pre[k]=i;rt[i]=ins(rt[i],1,n,i,k);
		}
		if(x){
			if(pre[x])c.push_back(make_pair(pre[x],Pow(x,P-2)));
			pre[x]=i;rt[i]=ins(rt[i],1,n,i,x);
		}
		int res;
		for(int j=0;j<(int)c.size();j++){
			if(j==0||c[j-1].first!=c[j].first)res=1;
			res=res*c[j].second%P;
			if(j+1==(int)c.size()||c[j].first!=c[j+1].first)rt[i]=ins(rt[i],1,n,c[j].first,res);
		}
	}
	int lastans=0;
	scanf("%lld",&m);
	rep(i,1,m){
		int l,r;scanf("%lld%lld",&l,&r);
		l=(l+lastans)%n+1;r=(r+lastans)%n+1;
		if(l>r)swap(l,r);
		printf("%lld\n",lastans=ask(rt[r],l,r,1,n));
	}
	return 0;
}
```

---

## 作者：Leasier (赞：4)

前置芝士：[ST 表](https://oi-wiki.org/ds/sparse-table/)、[可持久化线段树](https://oi-wiki.org/ds/persistent-seg/)

首先将 $\operatorname{lcm}$ 转化为对各个质因数取 $\max$。

套路地，我们对 $N = 2 \times 10^5$ 内的质因数根号分治。

对于 $\leq \sqrt{N}$ 的质因数，不难发现这个范围内只有 $86$ 个，于是我们可以用 ST 表对每个质因数的幂次求区间 $\max$。

对于 $> \sqrt{N}$ 的质因数，不难发现每个 $a_i$ 至多包含一个这个范围内的质因数，于是问题转化为 $[l, r]$ 中出现过的该类质因数的积。看到“出现”，设 $a'_i$ 表示考虑维护 $pre_i$ 表示 $i$ 上一次出现的位置，若此前未出现则为 $0$。问题转化为到 $r$ 为止，求 $[l, r]$ 中所有不同的 $a'_i$ 之积。这可以用一棵单点修改、区间查询乘积的主席树维护。

综上，时间复杂度为 $O(\frac{n \sqrt{N} \log n}{\ln N} + \frac{q \sqrt{N} \log \log n}{\ln N})$。

代码：
```cpp
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

typedef struct {
	int ls;
	int rs;
	ll mul;
} Node;

const int N = 86 + 7, M = 1e5 + 7, K = 16 + 1, P = 2e5 + 7, Q = 447, R = 3999982 + 7, mod = 1e9 + 7;
int id = 0;
short power[N][M], st[N][M][K];
int prime[N], root[M], pre[P];
bool p[Q + 7];
Node tree[R];

inline int init1(){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i <= Q; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= Q; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	return cnt;
}

inline void init2(int n, int pos){
	int m = log2(n);
	for (register int i = 1; i <= n; i++){
		st[pos][i][0] = power[pos][i];
	}
	for (register int i = 1; i <= m; i++){
		int id = i - 1, t1 = n - (1 << i) + 1, t2 = 1 << id;
		for (register int j = 1; j <= t1; j++){
			st[pos][j][i] = max(st[pos][j][id], st[pos][j + t2][id]);
		}
	}
}

inline void update(int x){
	tree[x].mul = tree[tree[x].ls].mul * tree[tree[x].rs].mul % mod;
}

void build(int &x, int l, int r){
	if (x == 0) x = ++id;
	if (l == r){
		tree[x].mul = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(tree[x].ls, l, mid);
	build(tree[x].rs, mid + 1, r);
	update(x);
}

void assign(int &x, int l, int r, int pos, int val){
	id++;
	tree[id] = tree[x];
	x = id;
	if (l == r){
		tree[x].mul = val;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid){
		assign(tree[x].ls, l, mid, pos, val);
	} else {
		assign(tree[x].rs, mid + 1, r, pos, val);
	}
	update(x);
}

ll get_product(int x, int L, int R, ll l, ll r){
	if (l <= L && R <= r) return tree[x].mul;
	int mid = (L + R) >> 1;
	ll ans = 1;
	if (l <= mid) ans = get_product(tree[x].ls, L, mid, l, r);
	if (r > mid) ans = ans * get_product(tree[x].rs, mid + 1, R, l, r) % mod;
	return ans;
}

inline short get_max(int l, int r, int pos){
	int t = log2(r - l + 1);
	return max(st[pos][l][t], st[pos][r - (1 << t) + 1][t]);
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

int main(){
	int n, cnt, q;
	ll last_ans = 0;
	cin >> n;
	cnt = init1();
	build(root[0], 1, n);
	for (register int i = 1; i <= n; i++){
		int a;
		cin >> a;
		for (register int j = 1; j <= cnt; j++){
			while (a % prime[j] == 0){
				a /= prime[j];
				power[j][i]++;
			}
		}
		root[i] = root[i - 1];
		if (a > 1){
			if (pre[a] != 0) assign(root[i], 1, n, pre[a], 1);
			pre[a] = i;
			assign(root[i], 1, n, i, a);
		}
	}
	for (register int i = 1; i <= cnt; i++){
		init2(n, i);
	}
	cin >> q;
	for (register int i = 1; i <= q; i++){
		ll l, r;
		cin >> l >> r;
		l = (l + last_ans) % n + 1;
		r = (r + last_ans) % n + 1;
		if (l > r) swap(l, r);
		last_ans = get_product(root[r], 1, n, l, r);
		for (register int j = 1; j <= cnt; j++){
			last_ans = last_ans * quick_pow(prime[j], get_max(l, r, j), mod) % mod;
		}
		cout << last_ans << endl;
	}
	return 0;
}
```

---

## 作者：FZzzz (赞：4)

写个被卡空间的做法，大家可以当笑话看。

------------
先写一下我最开始的想法，不想看的可以直接划到下面。

套路根号分治，对于每个小于根号的质因子我们需要求出它指数的最大值，拿一个线段树维护。这里线段树跟 st 表的时间是一样的，但 st 表空间多个 log。

对于大于根号的质因子，它的指数不超过一，我们处理出每个数的这样的因子，则我们需要求出区间内所有出现过的因子的乘积。这个可以像 HH 的项链一样拿个主席树维护。

鉴于 $n$ 以内质数个数是 $O(\dfrac n{\log n})$ 的，时间空复杂度一个根号，不知道为什么可以过，但是似乎就是可以过，离谱。

但是这样的话两部分的复杂度其实是非常不平衡的，考虑继续优化。

------------
这里也不是最后的解法，还是可以跳过。

沿用把大因子和小因子分块处理的思想，我们考虑如果一个因子最多出现 $S$ 次怎么做。

上面的做法其实是维护了上一个指数为一的地方，那我维护指数为 $1$ 到 $S$ 的上一个地方就可以了。这部分的复杂度是 $O(nS^2\log n)$。

如果我们对所有的因子都这样处理，那实际上 $S=O(\log n)$，总的复杂度为 $O(n\log^3n)$，时空复杂度相同。注意分解质因数时不能每次暴力分解。

我觉得过不去，但是似乎没人实现过。

------------
这里是正解。

考虑上面的算法的优化，如果有一个质因数，它在 $i$ 处的指数比 $j>i$ 处的出现次数要少，那实际上没必要对 $j$ 处的这个质因子计算贡献。

对于每一个质因子开一个单调栈，维护这个过程，用主席树维护贡献即可。

如果你看不懂这个算法那我还是建议你回去再看看上面的两个非正解（

根据单调栈的复杂度分析，这个时空复杂度应该是 $O(nw(n)\log n)$，$w(n)$ 表示 $n$ 以内的数不同质因数个数最大值，上界为 $O(\log n)$。

感觉是能过的，然而不能过，我也没啥办法。

@Inf_Voltage 神仙似乎也写的是这个做法，但是我看不懂他的代码，也不清楚他为什么能过/fad

放个卡不过去的代码好了，在 31 个点 MLE。

所以这题开强制在线的意义是啥啊强制选手写个主席树被卡空间吗……
```cpp
#include<stack>
#include<cstdio>
#include<cctype>
using namespace std;
inline int readint(){
	int x=0;
	char c=getchar();
	bool f=0;
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=1e5+5,maxa=2e5+5;
int n,q;
int mf[maxa];
const int mod=1e9+7;
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b%2==1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b/=2;
	}
	return ans;
}
struct node{
	node* ch[2];
	int prod,t;
	node(int l,int r):prod(1),t(0){
		if(l==r) return;
		int mid=l+(r-l)/2;
		ch[0]=new node(l,mid);
		ch[1]=new node(mid+1,r);
	}
	node(node* x){
		*this=*x;
		t++;
	}
	void modify(int l,int r,int x,int k){
		prod=1ll*prod*k%mod;
		if(l==r) return;
		int mid=l+(r-l)/2;
		if(x<=mid){
			if(ch[0]->t!=t) ch[0]=new node(ch[0]);
			ch[0]->modify(l,mid,x,k);
		}
		else{
			if(ch[1]->t!=t) ch[1]=new node(ch[1]);
			ch[1]->modify(mid+1,r,x,k);
		}
	}
	int query(int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r) return prod;
		int mid=l+(r-l)/2,ans=1;
		if(ql<=mid) ans=1ll*ans*ch[0]->query(l,mid,ql,qr)%mod;
		if(qr>mid) ans=1ll*ans*ch[1]->query(mid+1,r,ql,qr)%mod;
		return ans;
	}
}*rt[maxn];
typedef pair<int,int> pii;
stack<pii> s[maxa];
void insert(int x,int p,int m){
	int lst=0;
	while(s[p].size()&&s[p].top().second<=m){
		rt[x]->modify(1,n,s[p].top().first,ksm(ksm(p,s[p].top().second-lst),mod-2));
		lst=s[p].top().second;
		s[p].pop();
	}
	if(s[p].size()) rt[x]->modify(1,n,s[p].top().first,ksm(ksm(p,m-lst),mod-2));
	s[p].push(pii(x,m));
	rt[x]->modify(1,n,x,ksm(p,m));
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	for(int i=2;i<maxa;i++) if(!mf[i]){
		mf[i]=i;
		for(int j=i;1ll*i*j<maxa;j++) mf[i*j]=i;
	}
	n=readint();
	rt[0]=new node(1,n);
	for(int i=1;i<=n;i++){
		int a=readint();
		rt[i]=new node(rt[i-1]);
		while(a!=1){
			int tmp=mf[a],cnt=0;
			while(a%tmp==0){
				a/=tmp;
				cnt++;
			}
			insert(i,tmp,cnt);
		}
	}
	q=readint();
	int last=0;
	while(q--){
		int l,r;
		l=(readint()+last)%n+1;
		r=(readint()+last)%n+1;
		if(l>r) swap(l,r);
		printf("%d\n",last=rt[r]->query(1,n,l,r));
	}
	return 0;
}
```

---

## 作者：Piwry (赞：3)

好像有一道 [类似的题目](https://www.luogu.com.cn/problem/P5655?contestId=23455)...不过由于值域的原因，两者做法有很大的差别

## 解析

$\text{lcm}$ 和 $\gcd$ 的性质类似，可以想到也用线段树维护。然而 $\text{lcm}$ 的值单调不减，且线段树维护时是不能取模的；结点的 $\text{lcm}$ 值很快就会随着区间范围的扩大而炸掉

$\text{lcm}$ 看起来和 $\gcd$ 有很多联系，因此接着会想到推式子将维护的东西化成和 $\gcd$ 有关的形式。但我推了几个式子都不像能过这个数据范围的样子，有几个还假掉了（\kk）

于是再观察值域，发现仅有 $2\cdot 10^5$，考虑根号分治。具体来说，$\text{lcm}$ 可以看做对每个的质因子幂次取 $\max$

对于小于等于 $\sqrt{2\cdot 10^5}$ 的质因子，直接各开一个线段树暴力维护

对于大于 $\sqrt{2\cdot 10^5}$ 的质因子，每个元素至多有一个。这有点像维护区间不同颜色个数，只不过每个颜色还带了权值（强制在线）；我们把原来的做法稍微改下就行了

（可能还有其它方法，这里仅提一种）

具体来说，我们设 $i$ 版本的维护区间乘积的线段树为右端点为 $i$ 的答案。预处理时，每次从 $i-1$ 版本的线段树得到 $i$ 版本的线段树，其中 $0$ 版本的线段树为空，且设线段树维护的每个位置的缺省值为 $0$；预处理第 $i$ 版本的线段树时，将 $i$ 位置的权值乘上 $a_i$ 的大质因子，并将 $a_i$ 上次出现的位置除掉该质因子（为了避免多次统计同一质因子）。查询 $[l, r]$ 的答案时，只需在 $r$ 版本的线段树上查询 $[l, r]$ 的值即可

## CODE

（不知为何这份代码会在 Codeforces 迷之[吸氧中毒](https://www.luogu.com.cn/discuss/show/265731)（`O3`, `Ofast`）...）

注意我的代码中没有显式地将线段树的每个位置的缺省值设为 $0$（可能造成理解上的问题，于是就提醒下）

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdlib>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast", "-funroll-loops", "-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3", "sse3", "sse2", "sse", "avx2", "avx")
#define ll long long
using std::max;

const int M =1e9+7;
const int MAXN =1e5+20, MAXV =2e5+20, sqrt_MAXV =sqrt(MAXV)+20;
const int MAXN_Seg1 =(1<<18)+20, MAXN_Seg2 =(1<<18)+7e6, MAXNUM_Seg1 =86;/*<- 86 是测数据范围得到的*/

/*------------------------------Math------------------------------*/

int pow(int x, int k){
	int ret =1;
	for(; k; x =1ll*x*x%M, k >>=1)
		if(k&1)
			ret =1ll*ret*x%M;
	return ret;
}

int inv[MAXV];

void pre_inv(){
	inv[1] =1;
	for(int i =2; i < MAXV; ++i)
		inv[i] =1ll*(M-M/i)*inv[M%i]%M;
}

bool np[sqrt_MAXV];
int prim[sqrt_MAXV], totp;

void getprim(int n){
	for(int i =2; i <= (int)sqrt(n); ++i){
		if(!np[i])
			prim[totp++] =i;
		for(int j =0; i*prim[j] <= (int)sqrt(n); ++j){
			np[i*prim[j]] =1;
			if(i%prim[j] == 0)
				break;
		}
	}
}

/*------------------------------Seg------------------------------*/

int N =1;

struct Seg1{
	int Seg_mx[MAXN_Seg1];
	
	inline void pushup(int x){ Seg_mx[x] =max(Seg_mx[(x<<1)], Seg_mx[(x<<1)|1]); }
	
	void modify(int pos, int x =1, int nl =1, int nr =N){
		if(nl == nr){
			++Seg_mx[x];
			return;
		}
		int mid =(nl+nr)>>1;
		if(pos <= mid)
			modify(pos, x<<1, nl, mid);
		else
			modify(pos, (x<<1)|1, mid+1, nr);
		pushup(x);
	}
	
	int query(int l, int r, int x =1, int nl =1, int nr =N){
		if(l == nl && r == nr)
			return Seg_mx[x];
		int mid =(nl+nr)>>1;
		if(r <= mid)
			return query(l, r, x<<1, nl, mid);
		else if(l >= mid+1)
			return query(l, r, (x<<1)|1, mid+1, nr);
		else
			return max(query(l, mid, x<<1, nl, mid), query(mid+1, r, (x<<1)|1, mid+1, nr));
	}
}t_small[MAXNUM_Seg1];

struct Seg2{
	int root[MAXN], tot;
	int ls[MAXN_Seg2], rs[MAXN_Seg2];
	int Seg_mul[MAXN_Seg2];
	
	inline int New(int x){
		++tot;
		ls[tot] =ls[x], rs[tot] =rs[x];
		Seg_mul[tot] =max(1, Seg_mul[x]);
		return tot;
	}
	
	inline void pushup(int x){ Seg_mul[x] =1ll*max(1, Seg_mul[ls[x]])*max(1, Seg_mul[rs[x]])%M; }
	
	void modify(int pos, int val, int &x, int nl =1, int nr =N){
		x =New(x);
		if(nl == nr){
			Seg_mul[x] =1ll*Seg_mul[x]*val%M;
			return;
		}
		int mid =(nl+nr)>>1;
		if(pos <= mid)
			modify(pos, val, ls[x], nl, mid);
		else
			modify(pos, val, rs[x], mid+1, nr);
		pushup(x);
	}
	
	int query(int l, int r, int x, int nl =1, int nr =N){
		if(l == nl && r == nr)
			return Seg_mul[x];
		int mid =(nl+nr)>>1;
		if(r <= mid)
			return query(l, r, ls[x], nl, mid);
		else if(l >= mid+1)
			return query(l, r, rs[x], mid+1, nr);
		else
			return 1ll*query(l, mid, ls[x], nl, mid)*query(mid+1, r, rs[x], mid+1, nr)%M;
	}
}t_large;

/*------------------------------Pre------------------------------*/

int a[MAXN], max_fact[MAXN], last_pos[MAXV];

void pre_Seg1(int n){
	for(int i =1; i <= n; ++i){
		for(int j =0; j < totp; ++j){
			while(a[i]%prim[j] == 0){
				a[i] /=prim[j];
				t_small[j].modify(i);
			}
		}
		max_fact[i] =a[i];
	}
}

void pre_Seg2(int n){
	for(int i =1; i <= n; ++i){
		t_large.modify(i, max_fact[i], t_large.root[i] =t_large.root[i-1]);
		if(last_pos[max_fact[i]] != 0)
			t_large.modify(last_pos[max_fact[i]], inv[max_fact[i]], t_large.root[i]);
		last_pos[max_fact[i]] =i;
	}
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	int n =read(), maxa =1;
	for(int i =1; i <= n; ++i)
		a[i] =read(), maxa =max(maxa, a[i]);
	
	pre_inv();
	getprim(maxa);
	while(N < n)
		N <<=1;
	pre_Seg1(n);
	pre_Seg2(n);
	
	int q =read();
	for(int last =0; q; q--){
		int x =read(), y =read();
		int l =(last+x)%n+1, r =(last+y)%n+1;
		if(l > r)
			l ^=r ^=l ^=r;
		last =1;
		for(int j =0; j < totp; ++j)
			last =1ll*last*pow(prim[j], t_small[j].query(l, r))%M;
		last =1ll*last*t_large.query(l, r, t_large.root[r])%M;
		printf("%d\n", last);
	}
}
```

---

## 作者：Mobius127 (赞：2)

[题传](https://www.luogu.com.cn/problem/CF1422F)

简化题意：在线区间 $\operatorname{lcm}$。

显然不能直接上线段树，因为 $\operatorname{lcm}$ 只增不减，在这种情况下直接开高精都是不可行的，($10^5$ 个 $10^8$ 级别的数乘起来稳定飞天)，所以我们考虑分开算每个质因子的贡献。

设素数集 $P=\{p_1, p_2, \dots p_m \}$，则序列中的数 $a_i$ 可表示成：

$$\prod_{j=1}^m p_j^{c_{i, j}}$$

记 $C_j =\max_{i=l}^r c_{i, j}$，

那么根据定义，区间最小公倍数为：

$$\prod_{j=1}^m p_j^{C_j}$$

大眼观察 $Max_{a}=2 \times 10^5$，由于任何数只会有一个大于 $\sqrt{Max_{a}} \approx 450$ 的素数，打表后发现这个范围内只有 $87$ 个素数，显然根号分治了：

- 对于 $\le 450$ 的质因子，预处理 ST 表，每次询问暴力枚举质因子，空间复杂度 $O(87 n \log n)$，时间复杂度 $O(87n+87 \log \log n + 87q)$。

- 对于大于 $\ge 450$ 的质因子，由于只有一个，令 $b_i$ 为 $a_i$ 的最大值因子，那么就是求区间内不同种类数的乘积，类似于 [ HH 的项链 ](https://www.luogu.com.cn/problem/P1972) 这题的在线做法，用主席树，每次把上一次出现的 $b$ 拔掉即可，空间复杂度 $O(n \log n)$，时间复杂度 $O((n+q) \log n)$。


大概算了一下 ST 表空间会被卡，改成 `char` 类即可。

```cpp
const int mo=1e9+7;
const int N=1e5+5;
const int R=450;
const int Pcnt=87;
int Su[Pcnt]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449};
int n, m, Lg[N], a[N], pre[N*2], root[N], Mi[Pcnt][18];
char f[Pcnt][N][18];
namespace ZQF_AKIOI_LH_AKCTSC_CHT_AKWC{
	int tot;
	struct node{int pro, lc, rc;}d[N*40];
	#define ls d[k].lc
	#define rs d[k].rc
	#define mid (l+r>>1)
	void pushup(int k){d[k].pro=1ll*d[ls].pro*d[rs].pro%mo;}
	void build(int &k, int l, int r){
		k=++tot;d[k].pro=1;
		if(l==r){d[k].pro=a[l&r];return ;}
		build(ls, l, mid), build(rs, mid+1, r);
		pushup(k);
	}
	void insert(int &k, int l, int r, int x, int v){
		d[++tot]=d[k];k=tot;
		if(l==r){d[k].pro=v;return ;}
		if(x<=mid) insert(ls, l, mid, x, v);
		else insert(rs, mid+1, r, x, v);
		pushup(k);
	}
	int query(int k, int l, int r, int x, int y){
		if((!k)||l>y||r<x) return 1;
		if(x<=l&&r<=y) return d[k].pro;
		return 1ll*query(ls, l, mid, x, y)*query(rs, mid+1, r, x, y)%mo;
	}
	#undef ls
	#undef rs
	#undef mid
}
int query(int j, int l, int r){
	int k=Lg[r-l+1];
	return max(f[j][l][k], f[j][r-(1<<k)+1][k]);
}
signed main(){
	n=read();Lg[0]=-1;
	for(int i=1; i<=n; i++){
		a[i]=read();Lg[i]=Lg[i>>1]+1;
		for(int j=0; j<Pcnt; j++)
			while(a[i]%Su[j]==0) f[j][i][0]++, a[i]/=Su[j];
	}
	ZQF_AKIOI_LH_AKCTSC_CHT_AKWC :: build(root[0], 1, n);
	for(int i=1; i<=n; i++){
		root[i]=root[i-1];if(a[i]==1) continue;
		if(pre[a[i]]) ZQF_AKIOI_LH_AKCTSC_CHT_AKWC :: insert(root[i], 1, n, pre[a[i]], 1);
		pre[a[i]]=i;
	}
	for(int k=0; k<Pcnt; k++){
		for(int j=1; j<18; j++)
			for(int i=1; i+(1<<j)-1<=n; i++)
				f[k][i][j]=max(f[k][i][j-1], f[k][i+(1<<j-1)][j-1]);
		Mi[k][0]=1;
		for(int i=1; i<18; i++) Mi[k][i]=1ll*Mi[k][i-1]*Su[k]%mo;
	}
	m=read();int last=0;
	for(int i=1; i<=m; i++){
		int l=(read()%n+last%n)%n+1, r=(read()%n+last%n)%n+1;if(l>r) swap(l, r);last=1;
		for(int j=0; j<Pcnt; j++){
			int x=query(j, l, r);
			last=1ll*last*Mi[j][x]%mo;
		}
		last=1ll*last*(ZQF_AKIOI_LH_AKCTSC_CHT_AKWC :: query(root[r], 1, n, l, r))%mo;
		printf("%d\n", last);
	}
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：2)

提供一个复杂度优秀的对质因子根号分治的做法，完全不用卡空间~~就是被卡细节了~~，而且理论复杂度与单调栈+可持久化线段树不相上下。

首先自然的想到对于每种质数统计贡献，然后更自然的想到一个数 $x$ 至多只有一个质因子大于 $\sqrt{x}$，于是对质因子的值域分块。

设值域为 $W=2\times10^5$，对于小于 $\sqrt{W}$ 的质数只有 $86$ 个，直接对每个做 ST 表，开个挂用 $O(n)-O(1)$，时间和空间都是 $O(86n)$ 的。

对于大于 $\sqrt{W}$ 的质数每个 $i$ 只会贡献一个数，那么用可持久化线段树处理询问，暴力在对应区间上贡献即可，时间和空间都是 $O(n\log n)$。

理论上来说 $O(86n)$ 应该与 $O(nw(n)\log n)$ 不相上下，但实际上常数被吊打了。（悲）

[代码](https://www.luogu.com.cn/paste/8h2epgld)仅供参考。

---

## 作者：FutaRimeWoawaSete (赞：1)

一道很好的题。       

做法有两种，第一种就是第一篇题解，不得不说我没看懂。      

于是就讲讲此题的第二种根号分治的做法，你看这 $3s,2e5$ ，虽然不是 $Ynoi$ 但是用脚想也知道这种题肯定是放 $O(n\sqrt nlog_n)$ 过的，不然 $1s$ 就足矣。        
           
如果我们直接像维护区间 $gcd$ 一样的话我们就需要个高精，然后我们就开开心心爆掉了这道题。          

所以我们考虑 $lcm$ 的性质，对于一段数的 $lcm$ 我们有两种做法，一种是 $O(lenlog_{len})$ 一个个暴力合起来，还有一个就是拆分所有数的质因数然后指数取 $max$ ，对于此题我们考虑第二种做法。       

不过考虑很难维护所有质因数，我们只能先根号分治压缩空间，对于 $\leq \sqrt {200000}$ 的玩意儿我们直接暴力开相应数量的线段树然后维护对于每个质因子的指数区间最大值，接着我们发现对于 $\sqrt{200000} \leq$ 的质因子它的指数只会为 $1$ 并且只会出现 $1$ 个这样的质因子，所以把这些数暴力乘起来就可以了。我们用 $HH$ 的项链的搞法加主席树来维护。     


具体的，我们考虑每个版本的主席树，在 $root_r$ 的意义下相当于维护的是所有右端点在 $r$ 的查询。      

为什么这样的维护是对的呢？       

因为我们如果直接维护的话很有可能会算重一些数，所以我们只能考虑去重。    
我们可以来个小小的证明：首先在 $root_r$ 的线段树中，我们的 $[1,r]$ 的区间的答案肯定没有问题，接着我们来看 $[2,r]$ 的区间，此时我们 $1$ 位置的最大质因子本来可能是和 $[2,r]$ 中一个数的最大质因子算重了，但现在就没有任何影响，反之如果我们 $1$ 位置的最大质因子本来就没重，我们直接除去他就好了，所以可以证明这样的方法是对的，而此时比如说你要在这棵树上查询区间 $[1 , r - 1]$ ，假如我们的 $r - 1$ 位和 $r$ 位的最大质因子重了，那么我们就已经把贡献移到了 $r$ 位去，就产生了错误。          

具体实现参考的 $piwry$ 的代码。        

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 2e5 + 5 , sqrtV = 455 , Maxn = 2e5 + 7e6 + 5 , Mseg1 = (1 << 18) + 5;
const long long Mod = 1e9 + 7;
int inv[200005];
int n,m,ans[Mseg1][86],a[200005],last[200005],maxn[200005];
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x,int op){ans[x][op] = max(ans[ls(x)][op] , ans[rs(x)][op]);}
void update(int p,int l,int r,int idx,int op)
{
	if(l == r)
	{
		ans[p][op] ++;
		return;	
	} 
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx , op);
	else update(rs(p) , mid + 1 , r , idx , op);
	push_up(p , op);
}
int query(int p,int l,int r,int nl,int nr,int op)
{
	if(nl <= l && nr >= r) return ans[p][op];
	int mid = (l + r) >> 1 , res = 0;
	if(nl <= mid) res = max(res , query(ls(p) , l , mid , nl , nr , op));
	if(nr > mid) res = max(res , query(rs(p) , mid + 1 , r , nl , nr , op));
	return res;
}
int pow(int x, int k)
{
	int ret = 1;
	for(; k ; x = 1LL * x * x % Mod , k >>= 1)
		if(k & 1)
			ret = 1LL * ret * x % Mod;
	return ret;
}
void pre_inv()
{
	inv[1] = 1;
	for(int i = 2 ; i < Len ; ++ i)
		inv[i] = 1LL * (Mod - Mod / i) * inv[Mod % i] % Mod;
}
bool np[455];
int prim[455], totp;
void getprim(int N){
	for(int i = 2 ; i <= sqrt(N) ; i ++){
		if(!np[i])
			prim[++ totp] = i;
		for(int j = 1 ; i * prim[j] <= sqrt(N) ; j ++){
			np[i * prim[j]] = 1;
			if(i % prim[j] == 0)
				break;
		}
	}
}
int top,root[Len];
struct node
{
	int l,r,mul;
}tree[Maxn];
int clone(int p)
{
	top ++;
	tree[top] = tree[p];
	tree[top].mul = max(1 , tree[p].mul);
	return top;
}
void Push_up_t(int p){tree[p].mul = 1LL * max(1 , tree[tree[p].l].mul) * max(1 , tree[tree[p].r].mul) % Mod;}
int build(int p,int l,int r)
{
	p = ++ top;
	if(l == r){tree[p].mul = 1 ; return p;}
	int mid = (l + r) >> 1;
	tree[p].l = build(tree[p].l , l , mid);
	tree[p].r = build(tree[p].r , mid + 1 , r);
	Push_up_t(p);
	return p;
}
int Update_t(int p,int l,int r,int idx,int val)
{
	p = clone(p);
	if(l == r)
	{
		tree[p].mul = 1LL * tree[p].mul * val % Mod;
		return p;
	}	
	int mid = (l + r) >> 1;
	if(idx <= mid) tree[p].l = Update_t(tree[p].l , l , mid , idx , val);
	else tree[p].r = Update_t(tree[p].r , mid + 1 , r , idx , val);
	Push_up_t(p);
	return p;
} 
int Query_t(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return tree[p].mul;
	int mid = (l + r) >> 1 , res = 1;
	if(nl <= mid) res = 1LL * res * Query_t(tree[p].l , l , mid , nl , nr) % Mod;
	if(nr > mid) res = 1LL * res * Query_t(tree[p].r , mid + 1 , r , nl , nr) % Mod;
	return res;	
}
void Pre1()
{
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= totp ; j ++)
		{
			while(a[i] % prim[j] == 0)
			{
				a[i] /= prim[j];
				update(1 , 1 , n , i , j);
			}
		}
		maxn[i] = a[i];
	}
}
void Pre2()
{
	root[0] = build(1 , 1 , n);
	int cnt = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		root[i] = Update_t(root[i - 1] , 1 , n , i , maxn[i]);
		if(last[maxn[i]]) root[i] = Update_t(root[i] , 1 , n , last[maxn[i]] , inv[maxn[i]]);
		last[maxn[i]] = i;
	}
}
signed main()
{
	int maxa = 0;
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++){scanf("%d",&a[i]);maxa = max(maxa , a[i]);}
	pre_inv();
	getprim(maxa);
	Pre1();
	Pre2();
	scanf("%d",&m);
	int lastans = 0;
	for(int i = 1 ; i <= m ; i ++)
	{
		int l,r;scanf("%d %d",&l,&r);
		l = (l + lastans) % n + 1 , r = (r + lastans) % n + 1;
		if(l > r) swap(l , r);
		lastans = 1;
		for(int j = 1 ; j <= totp ; j ++) lastans = 1LL * lastans * pow(prim[j] , query(1 , 1 , n , l , r , j)) % Mod;
		lastans = 1LL * lastans * Query_t(root[r] , 1 , n , l , r) % Mod;
		printf("%d\n",lastans);
	}
	return 0;
}
```

---

## 作者：peterwuyihong (赞：0)

题意：值域小于等于 $2\times10^5$，给定一个序列，进行 $q$ 次在线的询问 $[l,r]$，求区间 $\text{lcm}$，$n\le 10^5,q\le10^5$。

值域分块，对小于 $\sqrt{2\times10^5}$ 的质数，使用 $\text{ST}$ 表记录区间出现的最大次幂。

对于大于值域的质数，每个数只会分解出一个，这个时候使用 HH の 项链 的套路，用 $pre_i$ 表示 $i$ 的上一次出现在哪里，然后只统计的 $pre<l$ 的值的乘积就行了，使用主席树简单维护。

现在是 $20:00$，我看我什么时候写完。

$\text{ST}$ 表 $\text{MLE}$ 了。

忽然意识到可以改成 short，现在是 $20:30$，过了。


```cpp
const int p=1e9+7;
template<class _Tp,class _tp>void add(_Tp&x,const _tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp,class _tp>_Tp Add(_Tp x,const _tp y){add(x,y);return x;}
template<class _Tp,class _tp>void sub(_Tp&x,const _tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp,class _tp>_Tp Sub(_Tp x,const _tp y){sub(x,y);return x;}
template<class _Tp,class _tp>void mul(_Tp&x,const _tp&y){x=1ll*x*y%p;}template<class _Tp,class _tp>_Tp Mul(const _Tp x,const _tp y){return 1ll*x*y%p;}
template<class _Tp,class _tp>_Tp ksm(_Tp a,_tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
#define maxn 100010
int n;
int a[maxn];
int pri[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443};
short st[86][19][maxn],lg[maxn];
short rmq(int o,int l,int r){
  int k=lg[r-l+1];
  return max(st[o][k][l],st[o][k][r-(1<<k)+1]);
}
struct prpr{
  int sm;
  int l,r;
}tree[maxn<<5];
int rt[maxn],tot;
int pre[maxn],app[maxn];
int build(int l,int r){
  int x=++tot;
  int mid=(l+r)>>1;
  tree[x].sm=1;
  if(l==r)return x;
  tree[x].l=build(l,mid);
  tree[x].r=build(mid+1,r);
  return x;
}
int insert(int now,int pos,int d,int l=0,int r=n){
  int x=++tot;
  tree[x]=tree[now];
  mul(tree[x].sm,d);
  if(l==r)return x;
  int mid=(l+r)>>1;
  if(pos<=mid)tree[x].l=insert(tree[now].l,pos,d,l,mid);
  else tree[x].r=insert(tree[now].r,pos,d,mid+1,r);
  return x;
}
int ask(int x,int pos,int l=0,int r=n){
  if(l==r)return tree[x].sm;
  int mid=(l+r)>>1;
  if(pos<=mid)return ask(tree[x].l,pos,l,mid);
  else return Mul(tree[tree[x].l].sm,ask(tree[x].r,pos,mid+1,r));
}
signed main(){
  cin>>n;
  rep(i,1,n)cin>>a[i];
  rep(i,2,n)lg[i]=lg[i>>1]+1;
  rep(j,0,85)rep(i,1,n)
  while(a[i]%pri[j]==0)st[j][0][i]++,a[i]/=pri[j];
  rep(k,0,85)rep(j,1,lg[n])rep(i,1,n-(1<<j)+1)st[k][j][i]=max(st[k][j-1][i],st[k][j-1][i+(1<<(j-1))]);
  rt[0]=build(0,n);
  tree[0].sm=1;//避免乘0？
  rep(i,1,n){
    if(a[i]!=1)rt[i]=insert(rt[i-1],app[a[i]],a[i]),app[a[i]]=i;
    else rt[i]=rt[i-1];
  }
  int m;
  cin>>m;
  int ans=0;
  while(m--){
    int l,r;
    cin>>l>>r;
    l=(ans+l)%n+1;
    r=(ans+r)%n+1;
    if(l>r)swap(l,r);
    ans=1;
    rep(i,0,85)mul(ans,ksm(pri[i],rmq(i,l,r)));
    int a=ask(rt[r],l-1);
    int b=ask(rt[l-1],l-1);
    mul(ans,a);
    mul(ans,ksm(b,p-2));
    cout<<ans<<endl;
  }
}
```

---

## 作者：S00021 (赞：0)

### 题意：

给定一个长度为 $n$ 的序列 $a$ 以及 $q$ 次询问 。

每次询问包含 $2$ 个整数 $l,r$ ，你需要求出区间 $[l,r]$ 的最小公倍数对 $10^9 + 7$ 取模的结果。
询问强制在线 。

数据范围： 

$$1≤x,y≤10^5, 1\leq n,q\leq 10^5,1 \leq a_i\leq 2\cdot 10^5$$

### Sol

区间 $\text{lcm}$ ? 这不是简单数据结构题？

想多了，发现 $\text{lcm}$ 并没有 $\text{gcd}$ 那种单调不增的性质，ST 表行不通了！

而取模之后再 ST 表显然没有了结合律，于是我们只能从 $\text{lcm}$ 的定义入手，尝试发掘一些性质。

- 对于 $k$ 个数 $a_i=\prod_{i=1}^k p_i^{s_i}$， 
	它们的最小公倍数 $\text{lcm} = \prod_{i=1}^k p_i^{\max _{j=1}^p{s_j}}$
  其中 $p$ 是质因子总数。
  
发现了什么，可以对指数 ST 表！

仿照 NOI2015 寿司晚宴 的套路，对质因子根号分治，选取阈值 $K$ ，对不大于 $K$ 的质因子暴力 ST 表预处理，并将原序列中这些质因子去除。

当将这些质因子去除后，原序列只剩下大于 $K$ 的质数和 $1$ ，$1$ 可以忽略不计；对于大于 $K$ 的质数，我们想要求出一段区间中这些数去重后的乘积。

想到了什么？可持久化！

我们可以建 $n$ 棵主席树，第 $i$ 棵主席树保存序列中 $pre_p \le i$ 的 $p$ 的乘积，每次在第 $l-1$ 主席树上查询下标位于 $[l,r]$ 间的 $\prod p$ ，这也是最直观的做法。

除此以外，这个问题也可以类比 [HH 的项链](https://www.luogu.com.cn/problem/P1972) 的在线做法求解 ，我们同样是建 $n$ 棵主席树，但不同的是，当处理到第 $i$ 棵主席树的时候，我们将 $pre_{a_i}$ 上乘上的 $a_i$ 的贡献去掉，并在下标 $i$ 处添加 $a_i$ 的贡献，每次在第 $r$ 主席树上查询下标位于 $[l,r]$ 间的 $\prod p$。为了方便处理，可以再新建第 $0$ 棵主席树，存储没有删除贡献的 $a_i$ 值，这样每次只要从上一棵树处删除相应的贡献，不需要添加新贡献。

当然，两种做法本质相同。

但到了这一步，你还远远没有做完，因为这题丧心病狂的一点不在于算法，而在于卡空间！

首先你需要算好主席树的内存，能开 $10\times MAXN$ 就不要开 $20 \times MAXN$ 。

其次你应该注意到空间的瓶颈在于 ST 表，所以你选定的阈值 $K$ 不能太大，并且要算好 $K$ 内的质数个数，卡着开。

最后，你的 ST 表开 short 也过不去，必须要开成 char。

代码：

```cpp
#include<bits/stdc++.h>
#define MAXN 200010
#define MOD 1000000007
#define B 450
using namespace std;
int n,a[MAXN+5],vis[B+5],pri[B+5],pricnt,mn[MAXN+5],pre[MAXN+5],lg[MAXN+5];
char f[90][MAXN+5][18];
int Fast(int x,int y){
	int ret=1;
	while(y){
		if(y&1) ret=1ll*ret*x%MOD;
		x=1ll*x*x%MOD,y>>=1;
	}return ret;
}int root[MAXN];
int numc,mul[MAXN*10];
int ls[MAXN*10],rs[MAXN*10];	
void pushup(int rt){mul[rt]=1ll*mul[ls[rt]]*mul[rs[rt]]%MOD;}
void build(int &rt,int l,int r){
	mul[rt=(++numc)]=1;
	if(l==r){mul[rt]=a[l]; return;}
	int md=(l+r)>>1; 
	build(ls[rt],l,md);
	build(rs[rt],md+1,r); 
	pushup(rt);
}int modify(int pre,int l,int r,int x){
	int rt=(++numc); 
	ls[rt]=ls[pre];
	rs[rt]=rs[pre];
	mul[rt]=mul[pre];
	if(l==r){mul[rt]=1; return rt;} //在叶节点赋值，通过 pushup 传上去 
	//这里将叶节点赋成1，相当于去除了从根通向 x 的链上 x 的贡献  
	int md=(l+r)>>1;
	if(x<=md) ls[rt]=modify(ls[pre],l,md,x);
	else rs[rt]=modify(rs[pre],md+1,r,x);
	pushup(rt); return rt;
}int ask(int rt,int l,int r,int L,int R){
	if(!rt) return 1;
	if(L<=l&&r<=R) return mul[rt];
	int md=(l+r)>>1,ret=1;
	if(L<=md) ret=1ll*ret*ask(ls[rt],l,md,L,R)%MOD;
	if(R>md) ret=1ll*ret*ask(rs[rt],md+1,r,L,R)%MOD;
	return ret;
}
int que(int id,int l,int r){
	int p=lg[r-l+1];
	return max(f[id][l][p],f[id][r-(1<<p)+1][p]);
}signed main(){
	scanf("%d",&n); vis[0]=vis[1]=1,lg[0]=-1;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=MAXN;i++) lg[i]=lg[i>>1]+1;
	for(int i=2;i<=B;i++){
		if(!vis[i]) pri[++pricnt]=i,mn[i]=i;
		for(int j=1;j<=pricnt&&i*pri[j]<=B;j++){
			vis[i*pri[j]]=1;
			mn[i*pri[j]]=min(mn[i],pri[j]);
			if(i%pri[j]==0) break;
		}
	}for(int i=1;i<=n;i++)
		for(int j=1;j<=pricnt;j++)
			while(a[i]%pri[j]==0) a[i]/=pri[j],f[j][i][0]++;
	build(root[0],1,n);
	for(int i=1;i<=n;i++){
		root[i]=root[i-1]; if(a[i]==1) continue;
		if(pre[a[i]]) root[i]=modify(root[i-1],1,n,pre[a[i]]);
		pre[a[i]]=i;
		//已经有a[i]了，那么pre[a[i]]的贡献要去除 
	}for(int k=1;k<=pricnt;k++)
		for(int j=1;j<=17;j++)
			for(int i=1;i+(1<<(j-1))<=n;i++)
				f[k][i][j]=max(f[k][i][j-1],f[k][i+(1<<(j-1))][j-1]);
	int Q; scanf("%d",&Q); int lstans=0;
	while(Q--){
		int l,r; scanf("%d%d",&l,&r);
		l=(l+lstans)%n+1,r=(r+lstans)%n+1;
		if(l>r) swap(l,r); lstans=1;
		for(int i=1;i<=pricnt;i++) lstans=1ll*lstans*Fast(pri[i],que(i,l,r))%MOD;
		lstans=1ll*lstans*ask(root[r],1,n,l,r)%MOD; printf("%d\n",lstans);
	}
	return 0;
}
```


---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/1422/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1422F)

没往“每个数最多只有一个 $>\sqrt{x}$ 的质因子”这个性质的蒟蒻来一发特别暴力的解法。

首先看到这个强制在线显然无法用 cdq 分治或者扫描线一类离线算法维护，因此考虑主席树或者树套树这一类在线算法。注意到对于一个质因子 $p$​​，显然 $p$​​ 对一段区间的贡献就是 $p^\text{maxc}$​​，其中 $\text{maxc}$​​ 表示区间 $[l,r]$​​ 中 $p$​​ 次数的最大值。这个最大值显然不好维护，因此转化为对于每个数 $p$​​ 的次数 $p^c$​​，它会对哪些区间产生贡献，根据笛卡尔树那一套理论，满足 $[l,r]$​​ 中 $p$​​ 次数的最大值刚好为 $c$​​ 的区间左端点形成一个区间 $[L_l,R_l]$​​，右端点也形成一个区间 $[L_r,R_r]$​​，因此对于 $l\in[L_l,R_l],r\in[L_r,R_r]$​​，$[l,r]$​​ 区间的答案应乘上 $p^c$​​。$L_l,R_l,L_l,R_r$​​ 可以单调栈求，当然也可以从小到大将所有 $c$​​ 插入 `set` 中然后在 `set` 中用 `lower_bound` 之类的东西求得。由于只有 $c\ne 0$​​ 的 $c$​​ 是有意义的，而对于所有 $p$​​，有意义的 $c$​​ 的个数之和应为所有 $a_i$​​ 质因子个数之和，而这显然不超过 $\max\{\omega(n)\}·n\approx 7n$​​，因此这样复杂度是 $\mathcal O(7n)$​​ 或 $\mathcal O(7n\log n)$​​​，在可接受范围内。

接下来考虑怎样计算答案。显然经过我们这么一分析，所有贡献都可以转化为以下形式：初始有一个全为 $1$ 的矩阵 $a$，有若干次操作：对于 $i\in[l_1,r_1],j\in[l_2,r_2],a_{i,j}\leftarrow a_{i,j}·v$，求 $a_{l,r}$。看到这个设问一眼树套树，直接树套树大概是 $7n·\log^2n$，空间和时间都很危，我第一次提交大约是 TLE #21。考虑加一点小小的优化，根据复杂度平衡的思想，我们设一个阈值 $B$（$30\sim 50$），那么对于 $\le B$ 的质因子，有意义的 $c$ 的个数可能很多，此时直接 ST 表维护最大值是 $n\log n$ 的，反而优于树套树的 2log，因此考虑对 $\le B$ 的质因子每个建一个 ST 表，然后每次询问这些质因子的贡献就暴力遍历即可。

```cpp
const int MAXN=1e5;
const int MAXV=2e5;
const int MAXP=MAXN<<8;
const int LOG_N=17;
const int MOD=1e9+7;
int n,qu,a[MAXN+5];
int pr[MAXV/6+5],prcnt=0,mnp[MAXV+5];
bitset<MAXV+5> vis;
vector<pii> ps[MAXV+5];
void sieve(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i]) pr[++prcnt]=i,mnp[i]=i;
		for(int j=1;j<=prcnt&&pr[j]*i<=n;j++){
			vis[pr[j]*i]=1;mnp[pr[j]*i]=pr[j];
			if(i%pr[j]==0) break;
		}
	}
}
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
struct node{int ch[2],val;} s[MAXP+5];
int rt[MAXN+5],ncnt=0;
void pushup(int k){s[k].val=1ll*s[s[k].ch[0]].val*s[s[k].ch[1]].val%MOD;}
void insert_in(int &k,int l,int r,int p,int v){
	if(!k) k=++ncnt,s[k].val=1;
	if(l==r) return s[k].val=1ll*s[k].val*v%MOD,void();
	int mid=l+r>>1;
	if(p<=mid) insert_in(s[k].ch[0],l,mid,p,v);
	else insert_in(s[k].ch[1],mid+1,r,p,v);
	pushup(k);
}
void insert(int x,int l,int r,int v){
	int iv=qpow(v,MOD-2);
	for(int i=x;i<=n;i+=(i&(-i))){
		insert_in(rt[i],1,n,l,v);
		if(r!=n) insert_in(rt[i],1,n,r+1,iv);
	}
}
int query_in(int k,int l,int r,int ql,int qr){
	if(!k) return 1;if(ql<=l&&r<=qr) return s[k].val;
	int mid=l+r>>1;
	if(qr<=mid) return query_in(s[k].ch[0],l,mid,ql,qr);
	else if(ql>mid) return query_in(s[k].ch[1],mid+1,r,ql,qr);
	else return 1ll*query_in(s[k].ch[0],l,mid,ql,mid)*query_in(s[k].ch[1],mid+1,r,mid+1,qr)%MOD;
}
int query(int x,int y){
	int ret=1;
	for(;x;x&=(x-1)) ret=1ll*ret*query_in(rt[x],1,n,1,y)%MOD;
	return ret;
}
void add(int l1,int r1,int l2,int r2,int v){
//	printf("%d %d %d %d %d\n",l1,r1,l2,r2,v);
	insert(l1,l2,r2,v);if(r1^n) insert(r1+1,l2,r2,qpow(v,MOD-2));
}
int st[11][MAXN+5][LOG_N+2];
int query_st(int x,int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return max(st[x][l][k],st[x][r-(1<<k)+1][k]);
}
int main(){
	scanf("%d",&n,&qu);sieve(MAXV);s[0].val=1;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		int tmp=a[i];
		while(tmp^1){
			int p=mnp[tmp],cnt=0;
			while(tmp%p==0) tmp/=p,cnt++;
			ps[p].pb(mp(cnt,i));
		}
	}
	for(int i=1;i<=10;i++){
		for(pii p:ps[pr[i]]) st[i][p.se][0]=p.fi;
		for(int j=1;j<=LOG_N;j++) for(int k=1;k+(1<<j)-1<=n;k++)
			st[i][k][j]=max(st[i][k][j-1],st[i][k+(1<<j-1)][j-1]);
	}
	for(int i=31;i<=MAXV;i++) if(!ps[i].empty()){
		sort(ps[i].begin(),ps[i].end());
		reverse(ps[i].begin(),ps[i].end());
		set<int> st;st.insert(0);st.insert(n+1);
		for(pii p:ps[i]){
			st.insert(p.se);
			set<int>::iterator it=st.find(p.se);
			int pre=*--it,nxt=*++ ++it;
//			printf("%d %d\n",pre,nxt);
			add(pre+1,p.se,p.se,nxt-1,qpow(i,p.fi));
		}
	} scanf("%d",&qu);int pre=0;
	while(qu--){
		int x,y;scanf("%d%d",&x,&y);
		x=(x+pre)%n+1;y=(y+pre)%n+1;
		if(x>y) swap(x,y);
//		printf("%d %d\n",x,y);
		pre=query(x,y);
		for(int i=1;i<=10;i++) pre=1ll*pre*qpow(pr[i],query_st(i,x,y))%MOD;
		printf("%d\n",pre);
	}
	return 0;
}
```



---

## 作者：ExplodingKonjac (赞：0)

### [原题链接](https://www.luogu.com.cn/problem/CF1422F)

## 解题思路

一个显然的事实是，$\operatorname{lcm}(a\mod p,b\mod p)\neq\operatorname{lcm}(a,b)\mod p$。用高精度计算的话~~在n=100时复杂度直接爆炸~~，我们考虑用因式分解做这道题。

假设 $\displaystyle a_i=\prod p_j^{\alpha_{i,j}}$，则有

$$
\operatorname{lcm}(a_l,a_{l+1},\dots,a_r)=\prod p_j^{\max\{a_{i,j}\ |\ l\le i\le r\}}
$$

但是 $2\times10^5$ 以内的质数数量太多，上式无法直接计算，考虑使用根号分治解决。

设 $m=\max\{a_i\}$，我们将大于 $\sqrt{m}$ 和小于等于 $\sqrt{m}$ 的质因数分别考虑。

$(\sqrt m)_{max}=\sqrt{200000}\approx447.21$。$447$ 以内的质数仅有 $90$ 个左右，用ST表记录每个质数区间内指数的最大值，然后暴力计算其贡献，复杂度是可以接受的。

不难发现，大于 $\sqrt{m}$ 的质因数在每一个数中指数不超过 $1$（如果存在 $p>\sqrt{m}$ 且其指数 $\alpha\ge2$，那么 $p^\alpha>(\sqrt{m})^2=\max\{a_i\}$，与前提矛盾）。问题转化为求一个区间出现过的不同的数的乘积。

由于没有修改，先考虑离线做法。一般处理区间去重的做法是将询问按照右端点排序处理。具体地，设当前处理到的右端点为 $r$。如果 $a_r$ 在 $[1,r]$ 中出现过，就将上一次出现的位置 $pos_{a_r}$ 上乘上 $a_r^{-1}$，并更新 $pos_{a_r}\gets r$。整个过程可以用线段树维护。

但是本题强制在线，可以使用可持久化线段树完成上述的操作。

## 注意事项

ST表的数组要开成`char`类型，否则
![](https://cdn.luogu.com.cn/upload/image_hosting/czhko0id.png)

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD=1e9+7;
int n,m,maxx,msqt,a[100005],no[505],pos[200005];
char f[90][100005][18];
bool vis[200005];
vector<int> prm;
void euler(int mx)
{
    for(int i=2;i<=mx;i++)
    {
        if(!vis[i]) prm.push_back(i);
        for(int j: prm)
        {
            if(i*j>mx)  break;
            vis[i*j]=true;
            if(i%j==0)  break;
        }
    }
}
inline void ST()
{
    for(int k=1;k<=maxx;k++)
        for(int i=1;i<=17;i++)
            for(int j=1;(j+(1<<i)-1)<=n;j++)
                f[k][j][i]=max(f[k][j][i-1],f[k][j+(1<<i-1)][i-1]);
}
inline char stQuery(int l,int r,int i)
{
    if(i>maxx)  return 0;
    int siz=log2(r-l+1);
    return max(f[i][l][siz],f[i][r-(1<<siz)+1][siz]);
}
struct TreeNode
{
    LL val;int ver;
    TreeNode *lc,*rc;
    TreeNode(): val(1),ver(0)
        { lc=rc=nullptr; }
}*rt[200005];
typedef TreeNode *pNode;
void modify(int p,LL x,int v,pNode &i,int l=1,int r=n)
{
    if(!i)  i=new TreeNode,i->ver=v;
    if(i->ver!=v)   i=new TreeNode(*i),i->ver=v;
    i->val=i->val*x%MOD;
    if(l!=r)
    {
        int mid=(l+r)>>1;
        if(mid>=p)  modify(p,x,v,i->lc,l,mid);
        else    modify(p,x,v,i->rc,mid+1,r);
    }
}
LL query(int lq,int rq,pNode i,int l=1,int r=n)
{
    if(!i)	return 1;
    if(l>=lq && r<=rq)	return i->val;
    LL mid=(l+r)>>1,res=1;
    if(mid>=lq) res*=query(lq,rq,i->lc,l,mid);
    if(mid<rq)  res*=query(lq,rq,i->rc,mid+1,r);
    return res%MOD;
}
inline LL quickPow(LL a,LL b)
{
    LL res=1;a%=MOD;
    while(b)
    {
        if(b&1)	res=res*a%MOD;
        a=a*a%MOD,b>>=1;
    }
    return res;
}
inline void ztt(int x,int i)
{
    if(pos[x])
        modify(pos[x],quickPow(x,MOD-2),i,rt[i]);
    modify(pos[x]=i,x,i,rt[i]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)    scanf("%d",&a[i]),maxx=max(maxx,a[i]);
    msqt=sqrt(maxx);
    euler(msqt);
    for(int i=0;i<prm.size();i++)   no[prm[i]]=i+1;
    maxx=prm.size();
    for(int i=1;i<=n;i++)
    {
        int x=a[i];rt[i]=rt[i-1];
        for(int j=2;j*j<=x;j++)
            while(x%j==0)   f[no[j]][i][0]++,x/=j;
        if(x!=1)
            if(x>msqt)  ztt(x,i);
            else    f[no[x]][i][0]++;
    }
    ST();
    scanf("%d",&m);
    LL ans=0;
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l=(l+ans)%n+1,r=(r+ans)%n+1;
        if(l>r) swap(l,r);
        ans=query(l,r,rt[r]);
        for(int i: prm)
            ans=ans*quickPow(i,stQuery(l,r,no[i]))%MOD;
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

