# [LMXOI Round 2] Annihilation

## 题目背景

LMX 和 HQZ 在研究上次被毙掉的题目 Impacter 时，他们提出了一个新的问题。

## 题目描述

给定一棵 $n$ 个节点的，以 $1$ 为根的树，每个点有权值 $a_i$。

对于一个点 $u$，定义函数 $f(u,v,d)$ 表示在 $u$ 的子树内选择一些点（至少需要选取一个点），选出的点中最大权值为 $v$，且它们编号的最大公约数为 $d$ 的方案数。

给定一个常数 $k$ 和一个序列 $b$，对于每个点 $u$，你需要求出 $ \sum\limits_{k|i}^{n}\sum\limits_{j=1}^nf(u,i,j)\times b_j$ 的值，其中 $k|i$ 表示 $k$ 可以整除 $i$。由于该值可能很大，所以你需要输出其对 $998244353$ 取模的结果。

## 说明/提示

**样例解释 #1**

节点 $3$ 可以选择 $\{3\}$，因为是求最大值为 $1$ 的倍数，所以贡献为 $2$。

节点 $2$ 可以选择 $\{2\},\{3\},\{2,3\}$，因为是求最大值为 $1$ 的倍数，所以贡献是 $1+2+1=4$ 。

节点 $1$ 可以选择 $\{1\},\{2\},\{3\},\{1,2\},\{1,3\},\{2,3\},\{1,2,3\}$，因为是求最大值为 $1$ 的倍数，所以贡献是 $1+1+2+1+1+1+1=8$ 。

对于所有数据，$1 \le a_i\le n\le  10^5$，$1\le b_i\le 10^9$。

| 子任务编号 |        $n$         |    特殊性质    | 分值 |
| :--------: | :----------------: | :------------: | :--: |
| Subtask #1 |      $\le 20$      |       无       |  $10$   |
| Subtask #2 |     $\le 200$      |       无       |  $10$  |
| Subtask #3 |     $\le 2000$     |       无       |  $10$  |
| Subtask #4 |     $\le 10^5$     | 树随机生成* |  $10$   |
| Subtask #5 |     $\le 10^5$     | $k=1$ |  $20$  |
| Subtask #6 | $\le 5\times 10^4$ |       无       |  $20$  |
| Subtask #7 |     $\le 10^5$     |       无       |  $20$  |

树随机生成*：指对于 $u=2,3,\ldots n$ 每个点，其父亲从 $[1,u-1]$ 的整数中均匀随机选取。

## 样例 #1

### 输入

```
3 1
1 2
2 3
1 1 2
1 1 2```

### 输出

```
8 4 2```

## 样例 #2

### 输入

```
4 1
1 2
2 4
1 3
1 1 2 1
1 2 3 1```

### 输出

```
19 5 3 1```

## 样例 #3

### 输入

```
10 3
1 2
1 3
2 4
2 5
3 6
3 7
7 8
5 9
9 10
1 3 7 3 6 6 6 9 4 8 
450163553 649444963 324825063 696619525 758594756 594697697 750550965 907640826 118301481 755848673 
```

### 输出

```
475170649 914027313 64013204 696619525 210513956 594697697 111866638 907640826 0 0```

# 题解

## 作者：SwordDance (赞：5)

~~你这题怎么紫的发黑啊。~~

## 前置知识
虚树、线段树合并。

## 问题转化
由于选点编号最大公约数 $d$ 的值不同时，方案产生的贡献 $b_{d}$ 不同，并且选点方案过多，无法简单实现对最大公约数的维护。所以我们考虑枚举最大公约数 $d$，每次只选编号为 $d$ 的倍数的结点，这样我们算出的方案的最大公约数只会是 $d$ 的倍数。

不过这样会产生多余贡献。~~简单~~，直接将 $d$ 减去他的所有除本身外因子的贡献即可。即：$ b_{d}\gets b_{d}- \begin{aligned} \sum _ {x | d} ^ {d-1} b_{x}\end{aligned}$。

考虑到在直接原树上计算会超时，我们只需要建出虚树即可。总点数为 $\begin{aligned} \sum _ {i=1} ^ {n} \operatorname{d}(i)\end{aligned}$，$n=10^{5}$ 时约为 $10^{6}$。（$\operatorname{d}(i)$ 表示 $i$ 的因子个数）

但这样我们又会出现一个问题：对于那些未建出的结点，我们如何更新他们的答案。注意到，若结点 $v$ 的原树父亲 $u$ 未建出，那么节点 $u$ 的本轮答案和节点 $v$ 是一样的。

简单证明一下：节点 $u$ 不能选本身和它其他儿子的子树中的点，否则它一定被建出。那么节点 $u$ 和 $v$ 可选的点集是一样的，所以它们的选法方案数和答案一定一样。

这样，我们在最后只需要将节点 $v$ 的答案传递给它的 $u$ 即可。但是这样 $u$ 虚树中的父亲 $w$ 答案会重复计算，~~简单，~~ 将 $w$ 的当轮答案减去 $u$ 的当轮答案即可。

## 计算贡献

建好虚树后，我们接下来需要考虑如何计算贡献。我们考虑枚举所选点集的点权最大值 $x$，显然，需满足 $k\mid x$。 记 $u$ 子树内点权小于 $x$ 的点的个数为 $y$ , 那么可行选法就是 $2^{y}$ 。结点 $u$ 的答案就是这些可行选法的和。

一种简单的想法是，按 $a_{u}$ 从小到大枚举 $u$，$u$ 暴力跳父亲，将沿途上的点的 $sz$ 值加一。若 $k\mid u$，暴力跳父亲，更新沿途上的点的答案。由于随机数据树的深度为 $\log N$，特判掉 $k=1$ 的点可以获得 60pts ~~和一份对拍代码~~。

鉴于我们只关心点的数量，而且加入一个点相当于将其到根路径上的点的答案 $\times 2$。我们可以考虑线段树合并。

具体的，记 $sum_{p}$ 为 $p$ 子树内的点数，$sun_{p}$ 为 $p$ 子树内满足 $k\mid a_{x}$ 的点 $x$ 的总答案。合并结点 $u$ 和 $v$ 时，记 $suma$ 为 $u$ 结点内值小于当前合并值的点的个数，$sumb$ 为 $v$ 节点内值小于当前合并值的点的个数。合并子树 $a$ 和 $b$ 时，若没有 $a$ 子树，那么就有 $sun_{b}\gets sun_{b} \times 2^{suma}$，没有 $b$ 子树时同理。否则为 $sun_{a} \gets sun_{a} \times 2^{ sumb+sum_{b} }+sun_{b} \times 2^{suma}$。同时更新 $suma$、$sumb$、$sum_{a}$ 即可。

但这样我们仍然存在一个问题。当我们更新区间 $l\sim r$ 时，它的子区间没有被更新，若后续需要子区间进行更新的时候会出问题，所以我们需要懒标记下传。~~没想到吧，还要懒标记。~~

最后，注意下初始化的细节已经空间大小，~~就可以创造你的最长 $AC$ 代码了。~~

记 $M=\begin{aligned} \sum _ {i=1} ^ {n}\operatorname{d}(i)\end{aligned}$，总时间复杂度为 $O(M \log N+N \sqrt{N})$。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e5+3,M=5e6+3,MOD=998244353;
int n,k,a[N],h[N],idx;
int fa[N],d[N],dfn[N],now;
int seq[N<<1],deep[N<<1],first[N],num,st[N<<1][20];
int stk[N],tp;
int node,sum[M],suma,sumb,rt[N],ls[M],rs[M];
LL sun[M],tag[M];
LL b[N],p[N],ans[N];
vector<int>V[N];
bool _;
struct node{
	int v,ne;
}e[N<<1];
void add(int x,int y,bool op){
	e[++idx]={y,h[x]};
	h[x]=idx;
} 
bool cmp(int X,int Y){
	return dfn[X]<dfn[Y];
}
bool tmp(int X,int Y){
	return a[X]<a[Y];
}
void qm(LL &x){
	if(x>=MOD||x<=-MOD) x%=MOD;
	if(x<0) x+=MOD;
}
void dfs1(int u){
	dfn[u]=++now;
	for(int i=h[u];i;i=e[i].ne){
		int v=e[i].v;
		if(fa[u]==v) continue;
		fa[v]=u;d[v]=d[u]+1;
		dfs1(v);
	}
}
void dfs2(int u){
	seq[++num]=u;deep[num]=d[u];first[u]=num;
	for(int i=h[u];i;i=e[i].ne){
		int v=e[i].v;
		if(fa[u]==v) continue;
		dfs2(v);
		seq[++num]=u;
		deep[num]=d[u];
	}
}
void up(int p){
	sum[p]=sum[ls[p]]+sum[rs[p]];
	sun[p]=sun[ls[p]]+sun[rs[p]];
	qm(sun[p]);
}
void down(int u){
	if(tag[u]){
		if(ls[u]) tag[ls[u]]+=tag[u],sun[ls[u]]=sun[ls[u]]*p[tag[u]]%MOD;
		if(rs[u]) tag[rs[u]]+=tag[u],sun[rs[u]]=sun[rs[u]]*p[tag[u]]%MOD;
		tag[u]=0;
	}
}
int modify(int p,int l,int r,int z){
	if(!p) p=++node;
	if(l==r){
    	sum[p]++;
    	if(z%k==0) sun[p]++;
    	return p;
    }
	int mid=l+r>>1;
	if(z<=mid) ls[p]=modify(ls[p],l,mid,z);
	else rs[p]=modify(rs[p],mid+1,r,z);
	up(p);
	return p;
}
int merge(int a,int b,int l,int r){
	down(a),down(b);
	if(!a){
		sumb+=sum[b];
		sun[b]=sun[b]*p[suma]%MOD;
		tag[b]+=suma;
		return b;
	}
	if(!b){
		suma+=sum[a];
		sun[a]=sun[a]*p[sumb]%MOD;
		tag[a]+=sumb;
		return a;
	}
	if(l==r){
        sun[a]=sun[a]*p[sumb+sum[b]]%MOD;
		sun[b]=sun[b]*p[suma]%MOD;
    	suma+=sum[a];
    	sumb+=sum[b];
		sum[a]+=sum[b];
		sun[a]+=sun[b];
		qm(sun[a]);
		tag[a]+=sumb;
		return a;
	}
	int mid=l+r>>1;
	ls[a]=merge(ls[a],ls[b],l,mid);
	rs[a]=merge(rs[a],rs[b],mid+1,r);
	up(a);
	return a;
}
void clac(int u,LL val){
	for(int i=h[u];i;i=e[i].ne){
		int v=e[i].v;
		clac(v,val);
		suma=sumb=0;
		ans[u]-=sun[rt[v]]*val;
		qm(ans[u]);
		rt[u]=merge(rt[u],rt[v],1,n);
		if(!_) h[v]=rt[v]=0; 
	}
	ans[u]+=sun[rt[u]]*val;
	qm(ans[u]);
}
void upd(int u){
	for(int i=h[u];i;i=e[i].ne){
		int v=e[i].v;
		upd(v);
		ans[u]+=ans[v];
	}
	qm(ans[u]);
}
int LCA(int x,int y){
	int l=first[x],r=first[y];
	if(l>r) swap(l,r);
	int len=__lg(r-l+1);
	int L=st[l][len],R=st[r-(1<<len)+1][len];
	return deep[L]<deep[R]?seq[L]:seq[R];
}
void insert(int u){
	if(!tp){
		stk[++tp]=u;
		return;
	}
	int lca=LCA(u,stk[tp]);
	while(tp>1&&d[lca]<d[stk[tp-1]])
		add(stk[tp-1],stk[tp],1),tp--;
	if(d[lca]<d[stk[tp]]) add(lca,stk[tp--],1);
	if(stk[tp]!=lca) stk[++tp]=lca;
	stk[++tp]=u;
}
void work(int x){//将结点x推入其因数的vector，以及处理b[x] 
	for(int i=1;i*i<=x;i++)
	    if(x%i==0){
	    	V[i].emplace_back(x);
			if(x!=1) b[x]-=b[i];
			if(i!=x/i){
	     		V[x/i].emplace_back(x);
				if(i!=1) b[x]-=b[x/i];
	    	}
    	}
}
void clear(){//初始化别写错了 
    for(int i=1;i<=node;i++) rt[i]=ls[i]=rs[i]=sum[i]=sun[i]=tag[i]=0;
	idx=node=h[1]=rt[1]=0;
}
int main()
{
    scanf("%d%d",&n,&k);
	p[0]=1;
    for(int i=1;i<=n;i++) p[i]=p[i-1]*2%MOD;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y,0);add(y,x,0);
	} 
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++) work(i),qm(b[i]); //更新 bi 
	dfs1(1);
	dfs2(1);
	for(int i=1;i<=num;i++) st[i][0]=i;
	for(int i=1;i<=__lg(num);i++)
	    for(int j=1;j+(1<<i)-1<=num;j++){
	    	int l=st[j][i-1],r=st[j+(1<<i-1)][i-1];
	    	if(deep[l]<deep[r]) st[j][i]=l;
	    	else st[j][i]=r;
		}
	memset(h,0,sizeof h);
	idx=0;
	for(int i=n;i>=1;i--){//从后往前处理，这样最后就不用重新建原树了 
		if(i==1) _=1;
		sort(V[i].begin(),V[i].end(),cmp);
		if(V[i][0]!=1) stk[++tp]=1;
		for(int j=0;j<V[i].size();j++) insert(V[i][j]);
		while(--tp) add(stk[tp],stk[tp+1],1);
		for(int j=0;j<V[i].size();j++) rt[V[i][j]]=modify(rt[V[i][j]],1,n,a[V[i][j]]);
		clac(1,b[i]);
		if(i==1) upd(1);//最后将儿子的贡献传给父亲 
		clear();
	}
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：KAxdd (赞：4)

##  [LMXOI Round 2] Annihilation 题解

出题人题解

#### Part1.假设没有 $\gcd$ 

如果没有 $\gcd$ 的话就很典了。我们设 $f_{i,j}$ 为第 $i$ 个点，其最大值为 $j$ 的方案数。则有转移：

$$f_{x,y}\gets \sum \limits _{u\in son_x}(f_{x,y}+\sum\limits _{i=1}^{y}f_{u,i}+  f_{x,y}\times\sum\limits _{i=1}^{y}f_{u,i})$$

 很明显这个东西可以用前缀和优化。这样子我们就可以求出对于每个点每个最大值的方案数，因为是树上问题，所以需要用线段树合并来解决，还需要记住 $laz$ 标记合并的时候需要将方案数分类讨论一下。然后考虑维护 $k$ 的最大值的倍数，这个东西用线段树上也是好解决的，我们只需要只计算其为 $k$ 倍数的贡献，然后维护的前缀和也是相同的。

#### Part2.加入 $\gcd$ 的做法

我们可以发现，假设我们枚举 $\gcd$ 会有很多重复的部分。具体就体现在对于一个集合内的数字其 $\gcd > x$，而 $x$ 又是其 $\gcd$ 的因数，那么对于这个贡献我们就会计算多次，这样子我们是肯定不想得到的。那么我们尝试去暴力容斥，我们枚举因数，将拥有枚举因数的点拿出来，建立一颗虚树，可以证明虚树中点数总和最多为 $O(n \ln n)$ 级别的因为我们题目保证了所有数字为 $1\sim n$ 的集合，所以可以对每个数字的因数贡献记录下来，直接暴力容斥，对于虚点可以直接计算，虚边可以用树上前缀和计算。时间复杂度为 $n\ln n \log^2 n $ 无法通过，大概可以过 $5 \times 10^4$ 的点？

我们可以考虑更为优雅的容斥方法。我们设 $f(n),g(n)$ 为最大值相同的情况下 $\gcd$ 恰好为 $n$ 的方案数，以及 $\gcd$ 为 $n$ 因数的方案数。然后我们就可以得到式子。

$$g(n)=\sum\limits_{n \mid d}f(d)$$

这个式子的形式很熟悉，就像莫比乌斯函数的反演形式，所以我们可以引入。

$$g(n)=\sum\limits _{n \mid d}f(d)\iff f(n)=\sum\limits_{d \mid n}\mu(\frac{n}{d})g(d)$$

我们尝试通过逆推法来证明。

$$\begin{aligned}
\sum_{n\mid d}g(d)\mu\left(\dfrac{d}{n}\right)
&=\sum_{d=1}^{+\infty} \mu(d)g(dn) \\
&=\sum_{d=1}^{+\infty}\mu(d)\sum_{dn\mid k}f(k) \\
&=\sum_{n \mid k}f(k)\sum_{d \mid\frac{k}{n}}\mu(d)\\ &=\sum_{n\mid k}f(d)\left[\dfrac{k}{n}=1\right]\\
&=f(n) \end{aligned}$$

这样子我们就可以得到一个反向式子。

$$f(n)=\sum\limits_{d \mid n}\mu(\frac{n}{d})g(d)$$

我们可以发现，对于 $g(n)$ 来说是很好求的，我们只需要直接枚举因数对于虚树计算即可，我们计算出来的值就是为 $\gcd$ 因数的答案 。所以我们直接把 $b$ 数组按照上述式子容斥一下即可。

时间复杂度 $O(n\ln n\log n)$ 。带有巨大常数。

代码比较长 [link](https://www.luogu.com.cn/paste/yupc0dwa)

---

## 作者：Tomle (赞：0)

真是紫题吗 /yun，写吐了。

我们记 $S(u,d)$ 表示 $u$ 子树内编号为 $d$ 的倍数的点集。

化式子

$$
\begin{aligned}
ans_u&=\sum_{d=1}^nb_d\sum_{S'\subset S(u,d)}[\gcd\{S'\}=d\land k\mid\max_{x\in S'}\{a_x\}]
\\&=\sum_{T=1}^n(\sum_{d\mid T}b_d\mu(\frac Td))\sum_{S'\subset S(u,T)}[k\mid\max_{x\in S'}\{a_x\}]
\end{aligned}
$$

$\sum_{d\mid T}b_d\mu(\frac Td)$ 可在 $O(n\ln n)$ 或 $O(n\ln\ln n)$ 的时间复杂度内计算。

对于每个 $T$ 枚举所有编号为 $T$ 倍数的点集 $S_{all}$，显然对于所有 $u$ 有 $S(u,T)\subset S_{all}$。

我们可以对 $S_{all}$ 的所有点建虚树，接下来需要解决 $k\mid\max\{a\}$ 的限制。

假如我们能够得到 $u$ 子树内所有点的点权，我们可以对点权建权值线段树，然后在线段树上维护区间包含多少点权，以及区间内选点使最大值为 $k$ 倍数的方案数。pushup 是容易的。

然后在虚树上线段树合并即可。统计答案树上差分即可。

复杂度？每种 $T$ 的 $S_{all}$ 大小之和是 $O(n\ln n)$，加上线段树合并是 $O(n\ln n\log n)$。

史：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
// const int V = ;
const int mod = 998244353;
typedef unsigned us;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair <int, int> pii;
typedef vector <int> vi;
typedef vector <pii> vpi;
typedef vector <ll> vl;
template <class T> using pq = priority_queue <T>;
template <class T> using pqg = priority_queue <T, vector <T>, greater <T> >;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i < (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
#define perr(i, a, b) for (int i = (a); i > (b); --i)

#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pb push_back

template <class T1, class T2> inline void ckmn(T1 &a, T2 b) { (a > b) && (a = b, 0); }
template <class T1, class T2> inline void ckmx(T1 &a, T2 b) { (a < b) && (a = b, 0); }

namespace IO {
    // char buf[1 << 23], *p1 = buf, *p2 = buf;
    // #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
    template <class T> void rd(T &a, unsigned c = 0) {
        while (c = getchar(), c < 48 || c > 57);
        for (a = 0; c >= 48 && c <= 57; c = getchar()) a = (a << 3) + (a << 1) + (c ^ 48);
    }
    template <class T> void wrt(T x) { if (x > 9) wrt(x / 10); putchar(x % 10 ^ 48); }
} using IO::rd; using IO::wrt;

int n, k, u, v;
int a[N], b[N];
vi T[N], vT[N];
int dep[N], anc[N][20], dfn[N], ind;
int ans[N];
int mk[N];
int A[N], B[N];
int p[N], pc, np[N], mu[N];
int pw2[N];

struct Seg {
    int ls, rs, cnt, dat;
    #define ls(p) tr[p].ls
    #define rs(p) tr[p].rs
    #define cnt(p) tr[p].cnt
    #define dat(p) tr[p].dat
} tr[N << 5];
#define M (L + R >> 1)
int stot;
inline int Nw() { stot++, ls(stot) = rs(stot) = cnt(stot) = dat(stot) = 0; return stot; }

void sieve() {
    mu[1] = 1;
    rep(i, 2, 1e5) {
        if (!np[i]) p[++pc] = i, mu[i] = mod - 1;
        for (int j = 1; i * p[j] <= 1e5; j++) {
            np[i * p[j]] = 1;
            if (i % p[j]) mu[i * p[j]] = mu[i] ? mod - mu[i] : 0;
            else break;
        }
    }
}
void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1, anc[u][0] = fa, dfn[u] = ++ind;
    for (auto v : T[u]) if (v != fa) dfs1(v, u);
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    per(i, 18, 0) if (dep[anc[u][i]] >= dep[v]) u = anc[u][i];
    if (u == v) return u;
    per(i, 18, 0) if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}
bool cmp(int x, int y) { return dfn[x] < dfn[y]; }
int make_vtree(int len) {
    sort(A + 1, A + len + 1, cmp);
    int len2 = 0;
    repr(i, 1, len) {
        B[++len2] = A[i];
        B[++len2] = lca(A[i], A[i + 1]);
    }
    B[++len2] = A[len];
    sort(B + 1, B + len2 + 1, cmp);
    len2 = unique(B + 1, B + len2 + 1) - B - 1;
    rep(i, 1, len2) vT[B[i]].clear();
    repr(i, 1, len2) {
        int lc = lca(B[i], B[i + 1]);
        // cout << B[i] << "  " << B[i + 1] << "  " << lc  << endl;
        vT[lc].pb(B[i + 1]);
    }
    return B[1];
}
inline void pushup(int p) {
    dat(p) = (dat(ls(p)) + 1ll * pw2[cnt(ls(p))] * dat(rs(p))) % mod;
    cnt(p) = cnt(ls(p)) + cnt(rs(p));
}
void ins(int p, int x, int L, int R) {
    if (L == R) {
        cnt(p)++;
        if (x % k == 0) dat(p) = (pw2[cnt(p)] - 1 + mod) % mod;
        else dat(p) = 0;
        return;
    }
    if (x <= M) {
        if (!ls(p)) ls(p) = Nw();
        ins(ls(p), x, L, M);
    } else {
        if (!rs(p)) rs(p) = Nw();
        ins(rs(p), x, M + 1, R);
    }
    pushup(p);
}
int merge(int u, int v, int L, int R) {
    if (!u || !v) return u | v;
    if (L == R) {
        cnt(u) += cnt(v);
        if (L % k == 0) dat(u) = (pw2[cnt(u)] - 1 + mod) % mod;
        else dat(u) = 0;
        return u;
    }
    ls(u) = merge(ls(u), ls(v), L, M);
    rs(u) = merge(rs(u), rs(v), M + 1, R);
    pushup(u);
    return u;
}
// void out(int p, int L, int R) {
//     if (!p) return;
//     cout << p << " "  << L << " " << R << " " << cnt(p) << " " << dat(p) << endl;
//     out(ls(p), L, M), out(rs(p), M + 1, R);
// }
int dfs2(int u, int fa, int ca) {
    int rt = Nw();
    if (mk[u]) ins(rt, a[u], 1, n);
    for (auto v : vT[u]) {
        int x = dfs2(v, u, ca);
        rt = merge(rt, x, 1, n);
    }
    int e = 1ll * dat(rt) * ca % mod;
    // cout << u << "  " << fa << "  " << ca << "  " << e << "  " << mk[u] << endl;
    ans[u] = (ans[u] + e) % mod;
    ans[fa] = (ans[fa] - e + mod) % mod;
    // puts("tree:");
    // out(rt, 1, n);
    return rt;
}
void dfs3(int u, int fa) {
    for (auto v : T[u]) {
        if (v == fa) continue;
        dfs3(v, u);
        ans[u] = (ans[u] + ans[v]) % mod;
    }
}
void solve() {
    rd(n), rd(k);
    repr(i, 1, n) {
        rd(u), rd(v);
        T[u].pb(v), T[v].pb(u);
    }
    rep(i, 1, n) rd(a[i]);
    rep(i, 1, n) rd(b[i]);
    sieve();
    rep(i, 1, n) {
        for (int j = 1; i * j <= n; j++) {
            A[i * j] = (A[i * j] + 1ll * mu[i] * b[j]) % mod;
        }
    }
    swap(b, A);
    dfs1(1, 0);
    rep(j, 1, 18) {
        rep(i, 1, n) {
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
        }
    }
    rep(i, pw2[0] = 1, n) pw2[i] = 2 * pw2[i - 1] % mod;
    rep(i, 1, n) {
        // cout << i << endl;
        int tot = 0;
        for (int j = i; j <= n; j += i) A[++tot] = j, mk[j] = 1;
        int rt = make_vtree(tot);
        stot = 0;
        dfs2(rt, 0, b[i]);
        for (int j = i; j <= n; j += i) mk[j] = 0;
    }
    dfs3(1, 0);
    rep(i, 1, n) wrt(ans[i]), putchar(32);
}
int main() {
    int T = 1;
    if (0) rd(T);
    while (T--) solve();
}
```

---

