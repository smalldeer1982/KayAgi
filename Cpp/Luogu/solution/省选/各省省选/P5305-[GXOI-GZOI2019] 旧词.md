# [GXOI/GZOI2019] 旧词

## 题目描述

> 浮生有梦三千场  
> 穷尽千里诗酒荒  
> 徒把理想倾倒  
> 不如早还乡
>
> 温一壶风尘的酒  
> 独饮往事迢迢  
> 举杯轻思量  
> 泪如潮青丝留他方
>
> ——乌糟兽/愚青《旧词》

你已经解决了五个问题，不妨在这大树之下，吟唱旧词一首抒怀。最后的问题就是关于这棵树的，它的描述很简单。

给定一棵 $n$ 个点的有根树，节点标号 $1 \sim n$，$1$ 号节点为根。  
给定常数 $k$。  
给定 $Q$ 个询问，每次询问给定 $x,y$。  
求：

$$\sum\limits_{i \le x} \text{depth}(\text{lca}(i,y))^k$$

$\text{lca}(x,y)$ 表示节点 $x$ 与节点 $y$ 在有根树上的最近公共祖先。  
$\text{depth}(x)$ 表示节点 $x$ 的深度，根节点的深度为 $1$。  
由于答案可能很大，你只需要输出答案模 $998244353$ 的结果。


## 说明/提示

### 样例解释

输入的树：

![poetry.png](https://cdn.luogu.com.cn/upload/pic/56737.png)

每个点的深度分别为 $1,2,3,2,3$。

第一个询问 $x = 4,y = 3$，容易求出：  

$$\text{lca}(1, 3) = 1,\text{lca}(2, 3) = 1,\text{lca}(3, 3) = 3,\text{lca}(4, 3) = 4$$

于是 $\text{depth}(1)^2+\text{depth}(1)^2+\text{depth}(3)^2+\text{depth}(4)^2 = 1+1+9+4 = 15$。

### 数据范围

|测试点编号|$n$ 的规模|$Q$ 的规模|$k$ 的规模|约定|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$n \le 2,000$|$Q \le 2,000$|$1 \le k \le 10^9$|无|
|$2$|$n \le 2,000$|$Q \le 2,000$|$1 \le k \le 10^9$|无|
|$3$|$n \le 2,000$|$Q \le 2,000$|$1 \le k \le 10^9$|无|
|$4$|$n \le 2,000$|$Q \le 2,000$|$1 \le k \le 10^9$|无|
|$5$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|存在某个点，其深度为 $n$|
|$6$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|存在某个点，其深度为 $n$|
|$7$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|存在某个点，其深度为 $n$|
|$8$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|存在某个点，其深度为 $n$|
|$9$|$n \le 50,000$|$Q = n$|$1 \le k \le 10^9$|对于第 $i$ 个询问，有 $x = i$|
|$10$|$n \le 50,000$|$Q = n$|$1 \le k \le 10^9$|对于第 $i$ 个询问，有 $x = i$|
|$11$|$n \le 50,000$|$Q \le 50,000$|$k = 1$|无|
|$12$|$n \le 50,000$|$Q \le 50,000$|$k = 1$|无|
|$13$|$n \le 50,000$|$Q \le 50,000$|$k = 2$|无|
|$14$|$n \le 50,000$|$Q \le 50,000$|$k = 2$|无|
|$15$|$n \le 50,000$|$Q \le 50,000$|$k = 3$|无|
|$16$|$n \le 50,000$|$Q \le 50,000$|$k = 3$|无|
|$17$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|无|
|$18$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|无|
|$19$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|无|
|$20$|$n \le 50,000$|$Q \le 50,000$|$1 \le k \le 10^9$|无|

## 样例 #1

### 输入

```
5 5 2
1
4
1
2
4 3
5 4
2 5
1 2
3 2```

### 输出

```
15
11
5
1
6```

# 题解

## 作者：x义x (赞：23)

[$$\color{green}\Large\texttt{『菜鸡的blog』}$$](https://www.luogu.org/blog/zyxxs/)

如果$k=1$，那么就是一道原题：[P4211 [LNOI2014]LCA](https://www.luogu.org/problem/P4211)，顺便挂一下我此题的题解：[click here](https://www.luogu.org/blog/zyxxs/solution-p4211)。下面的讲解以这题为基础。

在上面那道题中，我们提到，要对$u$到根的路径上所有点+1，$v$到根的路径的权值就是$u,v$的LCA的深度（的1次方）。修改和查询使用树剖再加线段树维护。

思考$k\neq1$的情况。原来$k=1$的+1是从哪里来的？深度从$d$变成$d+1$，对答案的贡献就会增长$(d+1)^1-d^1=1$，所以我们+1。

如果把1改成$k$呢？$(d+1)^k-d^k=\dots$算了我们也不是很关心柿子，反正每个点的深度只有一个，直接算出来就好了。

现在的问题是，我们需要用线段树维护一个序列，使得我们可以：

- 对$[l,r]$的每一个数加$A[i]=dep[i]^k-(dep[i]-1)^k$

- 求$[l,r]$的区间和

这非常sb，处理出每个区间$[l,r]$的$\sum _{i=l}^rA[i]$就可以轻松维护了。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int tt=998244353;

int N,M,K;
int lnk[50005];
int pre[50005],tgt[50005],cnt;
void add_E(int u,int v){
	pre[++cnt]=lnk[u],tgt[cnt]=v,lnk[u]=cnt;
}

int fa[50005],son[50005],s[50005],dep[50005];
int top[50005],seg[50005],rev[50005],idx;
void dfs1(int x){
	s[x]=1;dep[x]=dep[fa[x]]+1;
	for(int e=lnk[x];e;e=pre[e]){
		dfs1(tgt[e]),s[x]+=s[tgt[e]];
		if(s[tgt[e]]>s[son[x]]) son[x]=tgt[e];
	}
}
void dfs2(int x){
	seg[x]=++idx;rev[idx]=x;
	if(son[x]) top[son[x]]=top[x],dfs2(son[x]);
	for(int e=lnk[x];e;e=pre[e])if(tgt[e]!=son[x])
		top[tgt[e]]=tgt[e],dfs2(tgt[e]);
}

int A[50005];

int ANS[50005];
struct Qs{
	int u,v,pos;
	bool operator <(const Qs b)const{return u<b.u;}
}Q[50005];

int Key[200005],Sum[200005],Lzy[200005];
void push_up(int x){Sum[x]=(Sum[x<<1]+Sum[x<<1|1])%tt;}
void push_down(int x,int l,int r){
	int mid=(l+r)>>1;
	Sum[x<<1]=(Sum[x<<1]+1LL*Key[x<<1]*Lzy[x]%tt)%tt;
	Lzy[x<<1]=(Lzy[x<<1]+Lzy[x])%tt;
	Sum[x<<1|1]=(Sum[x<<1|1]+1LL*Key[x<<1|1]*Lzy[x]%tt)%tt;
	Lzy[x<<1|1]=(Lzy[x<<1|1]+Lzy[x])%tt;
	Lzy[x]=0;
}
void Build(int x,int l,int r){
	if(l==r){Key[x]=A[rev[l]];return;}
	int mid=(l+r)>>1;
	Build(x<<1,l,mid);Build(x<<1|1,mid+1,r);
	Key[x]=(Key[x<<1]+Key[x<<1|1])%tt;
}
void Update(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R){Sum[x]=(Sum[x]+Key[x]%tt)%tt;Lzy[x]=(Lzy[x]+1)%tt;return;}
	push_down(x,l,r);
	int mid=(l+r)>>1;
	if(L<=mid) Update(x<<1,l,mid,L,R);
	if(R>mid) Update(x<<1|1,mid+1,r,L,R);
	push_up(x);
}
int Query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return Sum[x];
	push_down(x,l,r);
	int mid=(l+r)>>1,ans=0;
	if(L<=mid) ans=(ans+Query(x<<1,l,mid,L,R))%tt;
	if(R>mid) ans=(ans+Query(x<<1|1,mid+1,r,L,R))%tt;
	push_up(x);
	return ans;
}

void Chain_Update(int x){
	while(x){
		Update(1,1,N,seg[top[x]],seg[x]);
		x=fa[top[x]];
	}
}
int Chain_Query(int x){
	int ans=0;
	while(x){
		ans=(ans+Query(1,1,N,seg[top[x]],seg[x]))%tt;
		x=fa[top[x]];
	}
	return ans;
}

int now_id=1;
int qpow(int a,int k){
	int ans=1;
	while(k){
		if(k&1) ans=1LL*ans*a%tt;
		a=1LL*a*a%tt;
		k>>=1;
	}
	return ans;
}

int main(){
	scanf("%d%d%d",&N,&M,&K);
	fa[1]=0;
	for(int i=2;i<=N;i++) scanf("%d",&fa[i]),add_E(fa[i],i);
	dfs1(1);top[1]=1;dfs2(1);
	for(int i=1;i<=N;i++) A[i]=(qpow(dep[i],K)-qpow(dep[i]-1,K)+tt)%tt;
	Build(1,1,N);
	for(int i=1;i<=M;i++){
		int r,z;scanf("%d%d",&r,&z);
		Q[i].u=r,Q[i].v=z,Q[i].pos=i;
	}
	sort(Q+1,Q+M+1);
	for(int i=1;i<=N;i++){
		Chain_Update(i);
		while(Q[now_id].u==i&&now_id<=M){
			ANS[Q[now_id].pos]=Chain_Query(Q[now_id].v);
			now_id++;
		}
	}
	for(int i=1;i<=M;i++) printf("%d\n",ANS[i]);
	
	return 0;
}
```


---

## 作者：Nemlit (赞：18)

## [原文地址](https://www.cnblogs.com/bcoier/p/10788658.html)

### 前置芝士：[[LNOI2014]LCA](https://www.luogu.org/problemnew/show/P4211)

~~要是这题放HNOI就好了~~

原题：$\sum_{l≤i≤r}dep[LCA(i,z)]$

这题：$\sum_{i≤r}dep[LCA(i,z)]^k$

对于原题，我们需要把每个询问拆成1~l-1 & 1~r再进行差分（~~所以这题帮我们省去了一个步骤~~）

### 先考虑$k=1$~~原题~~

我们先转化题意

$dep[lca]\ ==\ dis[1][lca]+1\ ==\ lca->1$的点数

所以我们每一个点(x)对答案的贡献($dep[lca(x, z)]$)，就是他们到根节点的公共路径的点数

于是，对于每一个点，我们只需要把1->x的链上加1即可

对于每一个询问，我们只需要求出1->z的链上的和即可

这一点我们可以利用树剖$/LCT$解决

但是直接做是$O(N^2*$树剖/$LCT)$的，我们考虑莫队

这样复杂度变成了$O(N\sqrt{N}*$树剖/$LCT)$

~~什么？你觉得这个算法还不够优秀？所以我们来考虑优化莫队~~

莫队的$\sqrt{N}$是怎么来的？不停的移动左右端点

但是这道题的左端点是固定的$(1)$，所以只需要移动右端点即可，而右端点不需要动来动去，只需要往后扫一遍即可，复杂度是$O(N*$树剖/$LCT)$

代码的话可以参考[[LNOI2014]LCA](https://www.luogu.org/problemnew/show/P4211)

### 考虑k!=1

我们为什么k=1的时候对于每个点是$1->x$路径上+1？

这个1的本质是树上差分，即：$(dep[x]+1)^1-dep[x]^1 = 1$

所以我们只需要把1改成k即可

所以现在问题变成了：给定一个序列，每一个点有两个权值$(a, b)$，每一个点的点权为$a*b$，支持a权值区间加1和区间查询

因为b不会改变，所以我们考虑线段树

把线段树的每一个节点新弄一个权值，为$\sum_{l≤i≤r} b$，每次更新区间的时候用这个权值$\times sum$即可

```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define debug printf("Now is Line : %d\n",__LINE__)
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define int long long
#define inf 123456789
#define mod 998244353
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define mem(k, p) memset(k, p, sizeof(k))
#define ls k * 2
#define rs k * 2 + 1
#define _ 500005
struct edge {int v, next;}e[_];
struct ques {
    int u, z, id;
    il bool operator < (const ques x) const {return u < x.u;}
}q[_];
int n, m, k, val[_ << 2], sum[_ << 2], mi[_], head[_], cnt, ans[_], tag[_ << 2], now;
int fa[_], dep[_], size[_], son[_], top[_], seg[_], col, rev[_];
il void add(int u, int v) {
    e[++ cnt] = (edge) {v, head[u]}, head[u] = cnt;
}
il int qpow(int a, int b) {
    int r = 1;
    while(b) {
        if(b & 1) r = 1ll * r * a % mod;
        b >>= 1, a = 1ll * a * a % mod;
    }
    return r;
}
il void dfs1(int u) {
    dep[u] = dep[fa[u]] + 1, size[u] = 1;
    Next(i, u) {
        if(e[i].v == fa[u]) continue;
        dfs1(e[i].v), size[u] += size[e[i].v];
        if(size[son[u]] < size[e[i].v]) son[u] = e[i].v;
    }
}
il void dfs2(int u, int fr) {
    top[u] = fr, seg[u] = ++ col, rev[col] = u;
    if(son[u]) dfs2(son[u], fr);
    Next(i, u) if(e[i].v != son[u] && e[i].v != fa[u]) dfs2(e[i].v, e[i].v);
}
il void build(int k, int l, int r) {
    if(l == r) return (void)(val[k] = (mi[dep[rev[l]]] - mi[dep[rev[l]] - 1] + mod) % mod);
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r), val[k] = (val[ls] + val[rs]) % mod;
}
il void pushdown(int k) {
    if(!tag[k]) return;
    sum[ls] = (sum[ls] + ((tag[k] * val[ls]) % mod)) % mod;
    sum[rs] = (sum[rs] + ((tag[k] * val[rs]) % mod)) % mod;
    tag[ls] += tag[k], tag[rs] += tag[k], tag[k] = 0;
}
il void change(int k, int l, int r, int ll, int rr) {
    if(l > rr || ll > r) return;
    if(l >= ll && r <= rr) {sum[k] = (sum[k] + val[k]) % mod, ++ tag[k]; return;}
    int mid = (l + r) >> 1;
    pushdown(k), change(ls, l, mid, ll, rr), change(rs, mid + 1, r, ll, rr);
    sum[k] = (sum[ls] + sum[rs]) % mod;
}
il int query(int k, int l, int r, int ll, int rr) {
    if(l > rr || ll > r) return 0;
    if(l >= ll && r <= rr) return sum[k];
    int mid = (l + r) >> 1;
    pushdown(k);
    return (query(ls, l, mid, ll, rr) + query(rs, mid + 1, r, ll, rr)) % mod;
}
il int query(int u) {
    int ans = 0;
    while(top[u]) ans = (ans + query(1, 1, n, seg[top[u]], seg[u])) % mod, u = fa[top[u]];
    return ans;
}
il void change(int u) {
    while(top[u]) change(1, 1, n, seg[top[u]], seg[u]), u = fa[top[u]];
}
signed main() {
    n = read(), m = read(), k = read() % (mod - 1), now = 1;
    rep(i, 1, n) mi[i] = qpow(i, k);
    rep(i, 2, n) fa[i] = read(), add(fa[i], i);
    rep(i, 1, m) q[i].id = i, q[i].u = read(), q[i].z = read();
    sort(q + 1, q + m + 1), dfs1(1), dfs2(1, 1), build(1, 1, n);
    rep(i, 1, n) {
        change(i);
        while(i == q[now].u) ans[q[now].id] = query(q[now].z), ++ now;
    }
    rep(i, 1, m) printf("%lld\n", ans[i]);
    return 0;
}
```

---

## 作者：xht (赞：17)

题目地址：[P5305 [GXOI/GZOI2019]旧词](https://www.luogu.org/problemnew/show/P5305)

这里是官方题解

$$\sum_{i \leq x}^{}\ depth(lca(i,y))^k$$

### $k = 1$

求的是 $\sum_{i \leq x}^{}\ depth(lca(i,y))$ ，一堆点然后每个点和 $y$ 求 $lca$ 然后深度求和。

总体思路是把 $lca$ 的值摊派到这个点到根的路径上（这个东西也叫树上差分？），再离线解决所有询问。

维护一个点权数组 $sum$ ，初始为 $0$ ，然后将 $y$ 到根的每个点的点权设为 $1$ ，然后对于每个点 $i \leq x$ ，求从 $i$ 到根的权值和为上面要求的答案，但这样就 $O(n)$ 了。

（可以反向考虑），维护一个点权数组 $sum$ ，初始为 $0$ ，对于小于等于 $x$ 的点 $i$ ，将 $i$ 到根的路径上所有点的点权 **++** 。然后求从 $y$ 到根的权值和也是上面要求的答案。这种方法求可以按 $x$ 排序，然后离线， $x$ 相等的询问一块问。

可以树链剖分 + 线段树解决。 $O(nlog^2n)$ 。或者 **LCT** 也行。

### $k > 1$

$k = 2$ 的话，按照上述思路想，把 $lca^2$ 的值摊到到根的路径上的话就不是之前的 $1,1,1,...$ ，变成了 $1,3,5,...$ 直接看的话问题变成了线段树区间加等差数列，好像改一下线段树实现也能做（所以给了点部分分）。

但是 $k > 2$ 的时候就比较麻烦了。

基于把 $lca^k$ 摊到从这个点到根的路径上这个思路，实际上对于深度是 $x$ 的点来说，这个点每次点权增加的值固定是 $x ^ k - (x - 1) ^ k$ 。

所以实际上，线段树打标记只用记录每个点被算了多少次 $cnt$ 即可。然后实际上的权值和是 $sum_i = cnt_i * (dep_i^k -(dep_i - 1)^k)$ ，每次操作只有 $cnt$ 区间加 $1$ ，于是预处理线段树上每个区间的 $\sum (dep_i^k -(dep_i - 1)^k)$ 后就可以直接拿线段树维护 $sum$ 数组。

于是还是之前的树链剖分 + 线段树解决。 $O(nlog^2n)$ 。或者 **LCT** 也行。


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

// by zrt
// zhangruotian@foxmail.com

using namespace std;

typedef long long LL;

const int MAXN = 50000+5;
const LL mod = 998244353;

int n,Q,k;
int H[MAXN], X[MAXN], P[MAXN], tot;
int fa[MAXN], dep[MAXN], dfn[MAXN], invdfn[MAXN], siz[MAXN], son[MAXN], top[MAXN];

inline void add(int x,int y) {
	P[++tot]=y;
	X[tot]=H[x];
	H[x]=tot;
}

struct Query {
	int x,y,id;
} query[MAXN];

int ans[MAXN];


bool cmp_by_x(Query a, Query b) {
	return a.x<b.x;
}

void dfs1(int x) {
	dep[x] = dep[fa[x]] + 1;
	siz[x] = 1;
	for(int i=H[x]; i; i=X[i]) {
		dfs1(P[i]);
		siz[x] += siz[P[i]];
		if(siz[P[i]]>siz[son[x]]) {
			son[x] = P[i];
		}
	}
}

int tim;

void dfs2(int x) {
	dfn[x] = ++tim;
	if(!top[x]) top[x]=x;
	if(son[x]) top[son[x]] = top[x], dfs2(son[x]);
	for(int i=H[x]; i; i=X[i]) {
		if(P[i] == son[x]) continue;
		dfs2(P[i]);
	}
}

LL pow(LL a,LL b,LL p) {
	LL ret = 1%p;
	while(b) {
		if(b&1) ret = ret*a%p;
		b>>=1;
		a=a*a%p;
	}
	return ret;
}

const int MAXN4 = MAXN*4;
struct SEGMENT_TREE {
	LL sum[MAXN4], cnt[MAXN4], pre[MAXN4];
	void updsum(int o) {
		sum[o] = (sum[o<<1] + sum[o<<1|1])%mod;
	}
	void bd(int o,int l,int r) {
		if(l==r) {
			pre[o] = (pow(dep[invdfn[l]],k,mod) - pow(dep[invdfn[l]]-1,k,mod) + mod)%mod;
			cnt[o] = sum[o] = 0;
		} else {
			int mid=(l+r)/2;
			bd(o<<1,l,mid);
			bd(o<<1|1,mid+1,r);
			pre[o] = (pre[o<<1]+pre[o<<1|1])%mod;
		}
	}
	void build() {
		bd(1,1,n);
	}
	void down(int o) {
		if(cnt[o]>0) {
			sum[o<<1] = (sum[o<<1]+(pre[o<<1]*cnt[o])%mod)%mod;
			cnt[o<<1] += cnt[o];
			sum[o<<1|1] = (sum[o<<1|1]+(pre[o<<1|1]*cnt[o])%mod)%mod;
			cnt[o<<1|1] += cnt[o];
			cnt[o]=0;
		}
	}
	void add(int o,int l,int r,int L,int R) {
		if(l == L && r == R) {
			sum[o] = (sum[o]+pre[o]) % mod;
			cnt[o] ++;
		} else {
			int mid=(l+r)/2;
			down(o);
			if(R<=mid) add(o<<1,l,mid,L,R);
			else if(L>mid) add(o<<1|1,mid+1,r,L,R);
			else add(o<<1,l,mid,L,mid), add(o<<1|1,mid+1,r,mid+1,R);
			updsum(o);
		}
	}
	void add(int l,int r) {
		assert(l<=r);
		add(1,1,n,l,r);
	}
	LL ask(int o,int l,int r,int L,int R) {
		if(l==L && r == R) {
			return sum[o];
		} else {
			int mid=(l+r)/2;
			down(o);
			if(R<=mid) return ask(o<<1,l,mid,L,R);
			else if(L>mid) return ask(o<<1|1,mid+1,r,L,R);
			else return (ask(o<<1,l,mid,L,mid) + ask(o<<1|1,mid+1,r,mid+1,R))%mod;
		}
	}
	LL ask(int l,int r) {
		assert(l<=r);
		return ask(1,1,n,l,r);
	}
} tree;

void prepare() {
	dfs1(1);
	dfs2(1);
	assert(tim == n);
	for(int i=1; i<=n; i++) invdfn[dfn[i]] = i;
	tree.build();
}

void add_point(int x) {
	while(x) {
		tree.add(dfn[top[x]], dfn[x]);
		x=fa[top[x]];
	}
}

LL ask(int x) {
	LL ret = 0;
	while(x) {
		ret = (ret + tree.ask(dfn[top[x]], dfn[x]))%mod;
		x=fa[top[x]];
	}
	return ret;
}

int main() {
	scanf("%d%d%d",&n,&Q,&k);
	assert(n+5 <= MAXN );
	assert(Q+5 <= MAXN );

	for(int i=2,x; i<=n; i++) {
		scanf("%d",&x);
		add(x,i);
		fa[i]=x;
	}
	for(int i=1; i<=Q; i++) {
		scanf("%d%d",&query[i].x,&query[i].y);
		query[i].id = i;
	}

	prepare();

	sort(query+1,query+Q+1,cmp_by_x);
	int p = 1;
	for(int i=1; i<=n; i++) {
		add_point(i);
		while(p <= Q && query[p].x == i) {
			ans[query[p].id] = ask(query[p].y);
			p++;
		}
	}
	assert(p==Q+1);

	for(int i=1; i<=Q; i++) {
		printf("%d\n",ans[i]);
	}

	return 0;
}
```

---

## 作者：mrsrz (赞：15)

不同于其他题解的树链剖分+树状数组做法。

第一步还是离线，然后按照$x$从小到大插入。

我们考虑询问$y$时，$y$到根路径上的每个节点的贡献。

令$sz_i$表示当前以节点$i$为根的子树中，已经被插入的数的个数。

则$y$的贡献为$dep(y)^k\times sz_y$，而$y$的祖先$z$的贡献为$dep(y)^k\times (sz_z-sz_p)$，其中$p$为$y$到根的路径中，最浅的比$z$深的节点。

如果$y$到根是一条重链，那么我们只需要对每个点维护轻儿子的子树贡献和$S_x$（包括自己本身），然后用数据结构维护就好了。

所以我们对原树进行树链剖分，每次询问都是若干段重链和若干条轻边。重链上的我们直接在数据结构上查，轻边上的特殊处理一下就好了。

我们具体来看一下如何维护：

考虑新插入一个节点$x$，则其到根路径上的每个点的子树节点个数都要加1。而$S$中需要变化的节点只有节点$x$本身和每条轻边的顶。

考虑查询一个节点，对于每条轻边顶的点，我们已经维护了每个点的子树大小，所以可以直接计算出其真实有贡献的节点个数，然后统计进答案。其他的点的贡献在$S$中已经维护，直接查询即可。

所以我们需要一个资瓷区间修改，单点查询的数据结构和一个资瓷单点修改，区间查询的数据结构。

两者都可以用树状数组。

时间复杂度$O(n\log^2 n)$。

在2019年4月23日拿到当时洛谷和LOJ的双最优解。

~~加那个读入优化纯属是因为强迫症，不加也是当时最优解~~

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
typedef long long LL;
const int md=998244353,N=50005;
char buf[(int)5e6],*ss=buf;
inline void init(){buf[fread(buf,1,(int)5e6-1,stdin)]='\n';fclose(stdin);}
inline int readint(){
	int d=0;
	while(!isdigit(*ss))++ss;
	while(isdigit(*ss))d=d*10+(*ss++&15);
	return d;
}
int n,Q,k,fa[N],head[N],cnt,ans[N],dep[N],sz[N],top[N],son[N],dfn[N],idx,dp[N];
int b1[N],b2[N],c[N];
inline void upd(int&a){a+=a>>31&md;}
inline void add1(int i,int x){for(;i<=n;i+=i&-i)b1[i]+=x;}
inline int ask1(int i){int x=0;for(;i;i^=i&-i)x+=b1[i];return x;}
inline void add2(int i,int x){for(x>0?x-=md:0;i<=n;i+=i&-i)upd(b2[i]+=x);}
inline int ask2(int i){int x=0;for(;i;i^=i&-i)upd(x+=b2[i]-md);return x;}
struct edge{
	int to,nxt;
}e[N];
inline int pow(int a){
	int ret=1,b=k;
	for(;b;b>>=1,a=(LL)a*a%md)if(b&1)ret=(LL)ret*a%md;
	return ret;
}
struct que{
	int x,y,id;
	inline bool operator<(const que&rhs)const{return x<rhs.x;}
}q[N];
void dfs(int now){
	sz[now]=1,son[now]=0;
	for(int i=head[now];i;i=e[i].nxt){
		dep[e[i].to]=dep[now]+1,dfs(e[i].to),sz[now]+=sz[e[i].to];
		if(!son[now]||sz[son[now]]<sz[e[i].to])son[now]=e[i].to;
	}
}
void dfs2(int now){
	dfn[now]=++idx;
	if(son[now])top[son[now]]=top[now],dfs2(son[now]);
	for(int i=head[now];i;i=e[i].nxt)
	if(e[i].to!=son[now])dfs2(top[e[i].to]=e[i].to);
}
void add(int x){
	for(;x;x=fa[top[x]])
	add1(dfn[top[x]],1),add1(dfn[x]+1,-1),
	add2(dfn[x],-c[x]),add2(dfn[x],c[x]=(LL)dp[x]*(ask1(dfn[x])-ask1(dfn[son[x]]))%md);
}
int query(int x){
	int ret=0,pre=0;
	for(;x;x=fa[top[x]]){
		ret=(ret+(LL)dp[x]*(ask1(dfn[x])-ask1(dfn[pre])))%md;
		if(x!=top[x])x=fa[x],upd(ret+=ask2(dfn[x])-md),upd(ret-=ask2(dfn[top[x]]-1));
		pre=top[x];
	}
	return ret;
}
int main(){
	init();
	n=readint(),Q=readint(),k=readint();
	for(int i=2;i<=n;++i)
	e[++cnt]=(edge){i,head[fa[i]=readint()]},head[fa[i]]=cnt;
	dfs(dep[1]=1),dfs2(top[1]=1);
	for(int i=1;i<=n;++i)dp[i]=pow(dep[i]);
	for(int i=1;i<=Q;++i)q[i].x=readint(),q[q[i].id=i].y=readint();
	std::sort(q+1,q+Q+1);
	for(int i=1,x=0;i<=Q;++i){
		while(x<q[i].x)
		add(++x);
		ans[q[i].id]=query(q[i].y);
	}
	for(int i=1;i<=Q;++i)
	printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Karry5307 (赞：11)

### 题意

给一棵 $n$ 个点，以 $1$ 为根的有根树和一个整数 $k$，$q$ 组询问，每组给定 $x,y$，求：

$$\sum\limits_{i=1}^{x}\operatorname{depth}\left(\operatorname{lca}(x,y)\right)^k$$

对 $998244353$ 取模。

$\texttt{Data Range:}1\leq n,q\leq 5\times 10^4,1\leq k\leq 10^9$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13656239.html)

一定要过啊 >_<

首先看一个弱化版：[[LNOI2014]LCA](https://www.luogu.com.cn/problem/P4211)，先考虑这个题目怎么做。

注意到这里有一个很朴素的求 $x,y$ 的 LCA 的方法：首先先将 $x$ 到根的路径上的所有点打个标记，然后 $y$ 到根的路径中深度最大的点就是两个点的 LCA。

注意到在 $y$ 到根的路径上，如果一个点被打了标记，那么这个点的所有祖先都会被打标记。所以说，$x,y$ 的 LCA 的所有祖先都是被打标记的，而 $y$ 到 LCA 的这一段都是没打标记的。

于是可以通过数一下 $y$ 到根中被打标记点的个数得到 $\operatorname{depth}\left(\operatorname{lca}(x,y)\right)$。

在这个的基础之上，我们就有了一个方法：

对于所有满足 $l\leq x\leq r$ 的 $x$ 都将 $x$ 到根的所有点点权加一，然后查询一下 $z$ 到根的所有点的点权和即可。

但是这么做是 $O(qn\log^2n)$ 的，很明显无法通过。

我们考虑对询问 $[l,r]$ 拆成 $[1,r]$ 和 $[1,l-1]$ 的形式。然后类似于莫队一样，因为所有询问的左端点都是一样的，所以可以先按照右端点排序，用一个指针扫一下即可，复杂度 $O(n\log^2n)$。

现在考虑这个题，瓶颈是看能不能有一个普适性的方法来求出 $\operatorname{depth}\left(\operatorname{lca}(x,y)\right)^k$。

注意到我们可以对这个东西进行差分。设 $w_x=\operatorname{depth}(x)^k-\operatorname{depth}\left(fa_x\right)^k$，那么根到 $x$ 路径上的 $w_x$ 之和恰好就是 $\operatorname{depth}(x)^k$！

于是还是按照原来一样，将所有询问按照右端点排序（因为左端点都为 $1$），然后用一个指针扫一遍所有询问即可。

但是会出现一个问题，就是需要对于所有 $l\leq i\leq r$ 的 位置 $i$ 加 $w_i$。

这里大多数题解都没讲清楚。考虑记一个 $v_i$ 在**树剖求出的 dfn** 的前缀和 $w_i$。然后如果递归到某个被询问区间包含的线段树区间 $[l,r]$，将这一段区间的和加上一个 $w_r-w_{l-1}$，然后打标记。

对于标记下传的话也是差不多的，然后这道题就解决了，具体实现可以看代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,MOD=998244353;
struct Edge{
	ll to,prev;
};
struct SegmentTree{
	ll l,r,sm,tag;
};
struct Query{
	ll r,u,id;
	inline bool operator <(const Query &rhs)const
	{
		return this->r<rhs.r;
	}
};
Edge ed[MAXN<<1];
SegmentTree tree[MAXN<<2];
Query qry[MAXN];
ll n,qcnt,kk,to,tot,totd,r,u,lst;
ll last[MAXN],fa[MAXN],depth[MAXN],sz[MAXN],hv[MAXN],dfn[MAXN];
ll top[MAXN],w[MAXN],v[MAXN],pw[MAXN],res[MAXN],rdfn[MAXN];
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
inline ll qpow(ll base,ll exponent)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline void addEdge(ll from,ll to)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	last[from]=tot;
}
inline void dfs(ll node,ll f)
{
	ll mx=-1;
	sz[node]=1,pw[node]=qpow(depth[node]=depth[fa[node]=f]+1,kk);
	for(register int i=last[node];i;i=ed[i].prev)
	{
		if(ed[i].to!=f)
		{
			dfs(ed[i].to,node),sz[node]+=sz[ed[i].to];
			sz[ed[i].to]>mx?mx=sz[hv[node]=ed[i].to]:1;
		}
	}
}
inline void dfs2(ll node,ll link)
{
	ll to;
	rdfn[dfn[node]=++totd]=node,top[node]=link;
	if(!hv[node])
	{
		return;
	}
	dfs2(hv[node],link);
	for(register int i=last[node];i;i=ed[i].prev)
	{
		(to=ed[i].to)!=fa[node]&&to!=hv[node]?dfs2(to,to):(void)1;	
	}
}
#define ls node<<1
#define rs (node<<1)|1
inline void update(ll node)
{
	tree[node].sm=(tree[ls].sm+tree[rs].sm)%MOD;
}
inline void create(ll l,ll r,ll node)
{
	tree[node]=(SegmentTree){l,r,0,0};
	if(l==r)
	{
		return;
	}
	ll mid=(l+r)>>1;
	create(l,mid,ls),create(mid+1,r,rs),update(node);
}
inline void spread(ll node)
{
	if(tree[node].tag)
	{
		ll tag=tree[node].tag;
		tree[ls].sm+=(li)tag*(v[tree[ls].r]-v[tree[ls].l-1]+MOD)%MOD;
		tree[rs].sm+=(li)tag*(v[tree[rs].r]-v[tree[rs].l-1]+MOD)%MOD;
		tree[ls].sm%=MOD,tree[rs].sm%=MOD;
		tree[ls].tag+=tag,tree[rs].tag+=tag,tree[node].tag=0;
	}
}
inline void add(ll l,ll r,ll node)
{
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		tree[node].sm+=(v[tree[node].r]-v[tree[node].l-1]+MOD)%MOD;
		return (void)(tree[node].sm%=MOD,tree[node].tag++);
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	spread(node);
	l<=mid?add(l,r,ls):(void)1,r>mid?add(l,r,rs):(void)1,update(node);
}
inline ll query(ll l,ll r,ll node)
{
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		return tree[node].sm;
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	spread(node);
	return ((l<=mid?query(l,r,ls):0)+(r>mid?query(l,r,rs):0))%MOD;
}
inline void add(ll x,ll y)
{
	while(top[x]!=top[y])
	{
		depth[top[x]]<depth[top[y]]?swap(x,y):(void)1;
		add(dfn[top[x]],dfn[x],1),x=fa[top[x]];
	}
	depth[x]>depth[y]?swap(x,y):(void)1;
	add(dfn[x],dfn[y],1);
}
inline ll query(ll x,ll y)
{
	ll res=0;
	while(top[x]!=top[y])
	{
		depth[top[x]]<depth[top[y]]?swap(x,y):(void)1;
		res=(res+query(dfn[top[x]],dfn[x],1))%MOD,x=fa[top[x]];
	}
	depth[x]>depth[y]?swap(x,y):(void)1;
	return (res+query(dfn[x],dfn[y],1))%MOD;
}
int main()
{
	n=read(),qcnt=read(),kk=read();
	for(register int i=2;i<=n;i++)
	{
		to=read(),addEdge(i,to),addEdge(to,i);
	}
	for(register int i=1;i<=qcnt;i++)
	{
		r=read(),u=read(),qry[i]=(Query){r,u,i};
	}
	dfs(1,0),dfs2(1,1),create(1,n,1);
	for(register int i=1;i<=n;i++)
	{
		w[i]=(pw[i]-pw[fa[i]]+MOD)%MOD;
	}
	for(register int i=1;i<=n;i++)
	{
		v[i]=(v[i-1]+w[rdfn[i]])%MOD;
	}
	sort(qry,qry+qcnt+1);
	for(register int i=1;i<=qcnt;i++)
	{
		for(register int j=lst+1;j<=qry[i].r;j++)
		{
			add(1,j);
		}
		lst=qry[i].r,res[qry[i].id]=query(1,qry[i].u);
	}
	for(register int i=1;i<=qcnt;i++)
	{
		printf("%d\n",res[i]);
	}
}
```

---

## 作者：CyanSineSin (赞：4)

这道题目非常简洁：要求 $\sum_{i\le x}depth(lca(i,y))^k$ ~~（都写在题面里了）~~

要直接解决这个问题是有点困难的，那么——

**我们先看它的弱化版**：[[LNOI2014]LCA](https://www.luogu.com.cn/problem/P4211)

要求 $\sum_{i=l}^rdepth(lca(i,z))$

~~少了个k次方呢！~~

首先转化一下   $\sum_{i=l}^rdepth(lca(i,z))=\sum_{i=1}^rdepth(lca(i,z))-\sum_{i=1}^{l-1}depth(lca(i,z))$

可以用前缀和来解决这个问题。

把每个询问拆成 $(1,l-1)$ 和 $(1,r)$ 分别解决。

那么我们可以按顺序把 $1$ 到 $n$ 的点加进来，同时计算加到每个点时的询问答案。

那么现在考虑加到第 $i$ 个点时如何计算贡献。

先上张图举个例子~

![](https://s1.ax1x.com/2020/07/28/aEbJr6.png)

其中涂成红色的点就是已经加入的点。

我们先计算一下每个节点的子树中有多少已经加入的点，用 $siz[x]$ 表示。没有加入的节点对当前询问肯定没有贡献。所以我们直接统计加入的节点就好了。

那么 $siz[1]=4$ , $siz[2]=2$,  $siz[3]=1$, $siz[4]=1$ ,  $siz[5]=1$ , $siz[6]=0$ 。

现在考虑计算当前加入的节点到4的LCA深度和。

$ans=siz[4]\times dep[4]+(siz[2]-siz[4])\times dep[2]+(siz[1]-siz[2])\times dep[1]$

即加入的节点中在 $4$ 的子树中的到 $4$ 的 $LCA$ 肯定为 $4$。在 $2$ 的子树但不在 $4$ 的子树中的到 $4$ 的 $LCA$ 肯定为 $2$，在 $1$ 的子树但不在 $2$ 的子树中的到 $4$ 的 $LCA$ 肯定为 $1$。

把式子拆开化简得到:

$ans=siz[4]\times (dep[4]-dep[2])+siz[2]\times (dep[2]-dep[1])+siz[1]$

$ans=siz[4]+siz[2]+siz[1]$

于是我们发现其实答案就是该节点到根路径的节点子树大小之和。

普遍形式：设查询节点到根的路径为 $\{v_1,v_2,v_3\dots v_k\}$。

$ans=siz[v_1]\times dep[v_1]+(siz[v_2]-siz[v_1])\times dep[v_2]+(siz[v_3]-siz[v_2])\times dep[v_3]+\dots +(siz[v_k]-siz[v_{k-1}])\times dep[v_k]$

由于是到根节点的路径，所以 $dep[v_i]=dep[v_{i+1}]+1$。

于是化简得：

$ans=siz[v_1]\times (dep[v_1]-dep[v_2])+siz[v_2]\times (dep[v_2]-dep[v_3])+siz[v_3]\times (dep[v_3]-dep[v_4])+\dots +siz[v_k]\times dep[v_k]$

$ans=siz[v_1]+siz[v_2]+siz[v_3]+\dots +siz[v_k]$

就此得出结论：答案就是该节点到根路径的节点子树大小之和。

查询直接查询要查询的节点到根路径上的节点的子树大小之和。

加入节点时只有它到根的路径上的节点的子树大小加了一。

使用树链剖分加线段树维护即可。

---

**回到本题**

本题没有 $l$ 的限制，所以我们不用前缀和拆询问处理了。

那么我们抬出之前的式子改成这道题的样子。

$ans=siz[v1]\times dep[v1]^k+(siz[v2]-siz[v1])\times dep[v2]^k+(siz[v3]-siz[v2])\times dep[v3]^k+\dots+(siz[vk]-siz[vk-1])\times dep[vk]^k$

化简一下，得到：

$ans=siz[v_1]\times (dep[v_1]^k-dep[v_2]^k)+siz[v_2]\times (dep[v_2]^k-dep[v_3]^k)+siz[v_3]\times (dep[v_3]^k-dep[v4]^k)+\dots  siz[v_k]\times dep[v_k]^k$

可以发现，$dep[v_2]$ 总等于 $dep[v_1]-1$（因为是从查询节点到根节点的路径嘛）。

所以对于$(dep[v_i]^k-dep[v_{i+1}]^k)$这种东西，我们可以对它进行预处理。

设对于点i的预处理答案为 $val[i]$。

则答案为:

$ans=siz[v_1]\times  val[v_1]+siz[v_2]\times  val[v_2]+siz[v_3]\times  val[v_3]+...siz[v_k]\times  val[v_k]$

就是在线段树维护时多加一个权值的问题了。

在线段树的每个节点上附加一个权值，表示这个区间里所有点的 $val$ 之和。

这样就可以区间修改和下传标记了。

~~跟上面那道弱化版差得不多吧~~~

代码：

```cpp
//直接用 LCA 代码改的，可能有点迷惑（？ 
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<long long> e[50010];
struct node
{
	long long bas,sum,tag;//bas为附加的权值
}nodes[400010];
struct ask
{
	long long pos,val,ID,nag;
}q[100010];
bool cmp(ask one,ask ano)
{
	return one.pos<ano.pos;
}
long long n,m,s,opl,opr,opz,f,cnt,tot,waste,ans[50010],kkk,dep[50010],fa[50010],son[50010],siz[50010],hb[50010],dfn[50010],ton[50010],power[50010],bruh;
const long long mod=998244353;
long long qpow(long long bas,long long tim)//快速幂用来处理val 
{
	long long res=1,fur=bas;
	while(tim)
	{
		if(tim&1)	res=(res*fur)%mod;
		fur=(fur*fur)%mod;
		tim>>=1;
	}
	return res;
}
void dfs(long long x,long long las)
{
	fa[x]=las;
	dep[x]=dep[las]+1;
	siz[x]=1;
	long long b=0,s=0;
	for(long long i=0;i<e[x].size();++i)
	{
		long long y=e[x][i];
		dfs(y,x);
		siz[x]+=siz[y];
		if(siz[y]>b)
		{
			b=siz[y];
			s=y;
		}
	}
	son[x]=s;
}
void dfs2(long long x,long long las,long long heavy)//树剖dfs
{
	if(heavy)	hb[x]=hb[las];
	else	hb[x]=x;
	dfn[x]=++cnt;
	ton[cnt]=x;
	if(son[x])	dfs2(son[x],x,1);
	for(long long i=0;i<e[x].size();++i)
	{
		long long y=e[x][i];
		if(y^son[x])	dfs2(y,x,0);
	}
}
void pushdown(long long x)
{
	if(nodes[x].tag)
	{
		//(siz[x]+a)*val[x]+(siz[y]+a)*val[y]+...+(siz[z]+a)*val[z]
		//=siz[x]*val[x]+siz[y]*val[y]+...+siz[z]*val[z]+a*(val[x]+val[y]+...+val[z])
		nodes[x].sum+=(nodes[x].bas*nodes[x].tag);
		nodes[x].sum%=mod;
		nodes[x<<1].tag+=nodes[x].tag;
		nodes[x<<1].tag%=mod;
		nodes[x<<1|1].tag+=nodes[x].tag;
		nodes[x<<1|1].tag%=mod;
		nodes[x].tag=0;
	}
}
void build(long long l,long long r,long long x)//预处理val区间和 
{
	if(l^r)
	{
		long long mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		nodes[x].bas=(nodes[x<<1].bas+nodes[x<<1|1].bas)%mod;
	}
	else	nodes[x].bas=power[dep[ton[l]]]-power[dep[ton[l]]-1];
//	printf(" %lld %lld %lld\n",l,r,nodes[x].bas);
} 
void update(long long l,long long r,long long x,long long fr,long long ba)
{
	if(l>ba||r<fr)	return;
	if(l>=fr&&r<=ba)	nodes[x].tag=(nodes[x].tag+1)%mod;
	else
	{
		pushdown(x);
		long long mid=(l+r)>>1;
		update(l,mid,x<<1,fr,ba);
		update(mid+1,r,x<<1|1,fr,ba);
		pushdown(x<<1);
		pushdown(x<<1|1);
		nodes[x].sum=(nodes[x<<1].sum+nodes[x<<1|1].sum)%mod;
	}
}
long long find(long long l,long long r,long long x,long long fr,long long ba)
{
	if(l>ba||r<fr)	return 0;
	pushdown(x);
	if(l>=fr&&r<=ba)	return nodes[x].sum;
	else
	{
		long long mid=(l+r)>>1;
		return (find(l,mid,x<<1,fr,ba)+find(mid+1,r,x<<1|1,fr,ba))%mod;
	}
}
void output(long long l,long long r,long long x)
{
	pushdown(x);
	printf(" %lld %lld %lld\n",l,r,nodes[x].sum);
	if(l^r)
	{
		long long mid=(l+r)>>1;
		output(l,mid,x<<1);
		output(mid+1,r,x<<1|1);
	}
}
void update_LCA(long long x,long long y)
{
	long long fx=hb[x],fy=hb[y];
	while(fx^fy)
	{
		if(dep[fx]<dep[fy])
		{
			swap(fx,fy);
			swap(x,y);
		}
		update(1,s,1,dfn[fx],dfn[x]);
		x=fa[fx];
		fx=hb[x];
	}
	update(1,s,1,min(dfn[x],dfn[y]),max(dfn[x],dfn[y]));
}
long long find_LCA(long long x,long long y)
{
	long long res=0;
	long long fx=hb[x],fy=hb[y];
	while(fx^fy)
	{
		if(dep[fx]<dep[fy])
		{
			swap(fx,fy);
			swap(x,y);
		}
		res+=find(1,s,1,dfn[fx],dfn[x]);
		res%=mod;
		x=fa[fx];
		fx=hb[x];
	}
	res+=find(1,s,1,min(dfn[x],dfn[y]),max(dfn[x],dfn[y]));
	res%=mod;
	return res;
}
int main()
{
	scanf("%lld %lld %lld",&n,&m,&bruh);
	s=n;
	for(long long i=1;i<=n;++i)	power[i]=qpow(i,bruh);
	for(long long i=2;i<=n;++i)
	{
		scanf("%lld",&f);
		e[f].push_back(i);
	}
	dfs(1,1);
	dfs2(1,1,0);
	build(1,s,1);
	for(long long i=1;i<=m;++i)
	{
		scanf("%lld %lld",&opr,&opz);
		q[++tot].ID=i;
		q[tot].nag=1;
		q[tot].pos=opr;
		q[tot].val=opz;
	}
	sort(q+1,q+1+tot,cmp);
	while(q[kkk].pos<=0&&kkk<=tot)
	{
		ans[q[kkk].ID]+=(q[kkk].nag*0);
		++kkk;
	}
	for(long long i=1;i<=n;++i)
	{
		update_LCA(1,i);
		while(q[kkk].pos<=i&&kkk<=tot)
		{
			ans[q[kkk].ID]+=(q[kkk].nag*find_LCA(1,q[kkk].val));
			ans[q[kkk].ID]%=mod;
			++kkk;
		}
//		puts("");
//		output(1,s,1);
//		puts("\n");
	}
	for(long long i=1;i<=m;++i)	printf("%lld\n",((ans[i]%mod)+mod)%mod);
	return 0;
}
```

---

## 作者：tommymio (赞：4)

[$\texttt{可能更好的阅读体验}$](https://www.cnblogs.com/tommy0103/p/13050433.html)

## 链接

[LOJ 3088](https://loj.ac/problem/3088)

[Luogu P5305](https://www.luogu.com.cn/problem/P5305)

## 题意

给定一棵 $n$ 个点的有根树，节点标号 $1 \sim n$，$1$ 号节点为根。

给定常数 $k$。

给定 $Q$ 个询问，每次询问给定 $x,y$。
求：
$$
\sum\limits_{i \le x} \text{depth}(\text{lca}(i,y))^k
$$
$\text{lca}(x,y)$ 表示节点 $x$ 与节点 $y$ 在有根树上的最近公共祖先。

$\text{depth}(x)$ 表示节点 $x$ 的深度，根节点的深度为 $1$。

由于答案可能很大，你只需要输出答案模 $998244353$ 的结果。

$\texttt{Data Range:}1\leq n \leq 5\times 10^4,1\leq q \leq 5\times 10^4$。 

## 题解

考虑一下这个问题的弱化版，即 **[LNOI2014]LCA**。

求：
$$
\sum_{i\leq x} \text{depth}(\text{lca}(i,y))
$$
可以想到最暴力的方法，依次将 $i,y$ 上的路径染色，求 $\text{lca}$。 

这样我们可以发现一个性质，$y$ 的 $\text{lca}$ 一定在从根节点 $1$ 到 $y$ 的路径上，$i$ 的 $\text{lca}$ 也一定在点 $i$ 到根节点 $1$ 的路径上。**并且进一步可以得出，$\text{lca}(i,y)$ 就在两者路径的公共部分上，并且就是这个公共部分所包含的深度最大的点。**正确性显然。

![](https://cdn.luogu.com.cn/upload/image_hosting/etg1e17j.png)

例如，在上图中，点 $i$ 到根节点 $1$ 的路径与点 $y$ 到根节点 $1$ 的路径的公共部分，就为根节点 $1$ 到点 $z$ 的路径，并且 $\text{lca}(i,y)=z$。

回想一下上面的性质，**点 $i$ 到根节点 $1$ 与点 $y$ 到根节点 $1$ 的公共路径所包含的深度最大的点** 就是 $\text{lca}(i,y)$，那么我们先对从根节点 $1$ 到每个点 $i$ 的路径染色，再查询根节点 $1$ 到点 $y$ ，就相当于取了这些公共路径，问题是如何查询 点 $y$ 到根节点 $1$ 的路径 与 点 $i$ 到根节点 $1$ 的路径 的公共部分的深度最大的节点的 **深度**？

可以想到差分，设 $b[x]=\text{depth}(x)-\text{depth}(fa[x])$，则 $\text{depth}(x)$ 即为从 $1$ 到点 $x$ 的路径上所有$b[j]$ 和。由于此弱化版求解的是一个幂为 $1$ 的情况，所以 $\forall x\geq 1,b[x]=1$。 

通过上述结论可以得到，对于每一个 $i$ ，将它到根节点 $1$ 的路径上的所有点 $j$ 的权值加上 $b[j]$（$j$ 是点 $i$ 到根节点 $1$ 的路径上包含的点），查询时直接查询点 $y$ 到根节点 $1$ 的点权和，即为每次询问的答案。

对于此弱化版问题，区间加 $b[j]$ 可直接视为区间 $+1$。



但对于此题，要求求解 $k$ 次方，应令 $b[x]=\text{depth}(x)^k-\text{depth}(fa[x])^k$。需要维护一个对于每个 $x\in [l,r]$，点权 $val[x]=val[x]+b[x]$ 的操作，其实也非常简单，对 $b[i]$ 做前缀和，进行此操作时在线段树上直接加上对应的和即可。

~~每次询问不是 $n \log^2 n$ 的么？没看出比暴力优秀多少啊？~~

我们可以将询问离线，将 $x$ 从小到大排序，保证每次询问时都维护了点 $1\sim x$的贡献（当前询问的 $x$）并统计答案。这样保证每个点到根节点 $1$ 的路径只会在树上被操作一次，减少了冗余操作。其实就是个 $one-pointer$，很好理解。

经过上述分析，对于该题，我们需要一个支持路径修改，路径查询的数据结构，使用 **树链剖分+线段树** 即可。时间复杂度为 $O(n+q \log^2 n)$。

**Show the Code**

```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
const ll mod=998244353;
int tot=0,cnt=0;
int h[500005],to[500005],ver[500005];
int d[500005],fa[500005],size[500005],son[500005];
int seg[500005],rev[500005],top[500005];
ll sum[2000005],tag[2000005],b[500005],ans[500005];
struct node {int x,y,id;} q[500005];
inline void swap(int &x,int &y) {int tmp=y;y=x;x=tmp;}
inline bool cmp(node x,node y) {return x.x<y.x;}
inline ll Add(ll x,ll y) {return (((x+y)%mod)+mod)%mod;}
inline ll read() {
	register ll x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y) {
	to[++cnt]=y;
	ver[cnt]=h[x];
	h[x]=cnt;
}
inline ll qpow(ll x,ll p) {
	ll res=1;
	for(;p;p>>=1) {
		if(p&1) res=res*x%mod;
		x=x*x%mod;
	}
	return res;
}
inline void dfs1(int x) {
	size[x]=1;son[x]=-1;
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i];
		d[y]=d[x]+1;fa[y]=x;
		dfs1(y);size[x]+=size[y];
		if(son[x]==-1||size[son[x]]<size[y]) son[x]=y;
	}
}
inline void dfs2(int x,int t) {
	seg[x]=++tot;rev[tot]=x;top[x]=t;
	if(son[x]!=-1) dfs2(son[x],t);
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i];
		if(y==son[x]) continue;
		dfs2(y,y);
	}
}
inline void work(int p,int l,int r,ll val) {
	val%=mod;
	tag[p]=Add(tag[p],val);
	sum[p]=Add(sum[p],val*Add(b[r],-b[l-1]));
}
inline void spread(int p,int l,int r) {
	if(tag[p]) {
		int mid=l+r>>1;
		work(p<<1,l,mid,tag[p]);
		work(p<<1|1,mid+1,r,tag[p]);
		tag[p]=0;
	}
}
inline void change(int p,int L,int R,int l=1,int r=tot) {
	if(L<=l&&r<=R) {work(p,l,r,1);return;}
	spread(p,l,r);
	int mid=l+r>>1;
	if(L<=mid) change(p<<1,L,R,l,mid);
	if(R>mid) change(p<<1|1,L,R,mid+1,r);
	sum[p]=sum[p<<1]+sum[p<<1|1];
}
inline ll ask(int p,int L,int R,int l=1,int r=tot) {
	if(L<=l&&r<=R) return sum[p];
	spread(p,l,r);
	int mid=l+r>>1;ll res=0;
	if(L<=mid) res=Add(res,ask(p<<1,L,R,l,mid));
	if(R>mid) res=Add(res,ask(p<<1|1,L,R,mid+1,r));
	return res;
}
inline void Modify(int x,int y) {
	while(top[x]!=top[y]) {
		if(d[top[x]]<d[top[y]]) swap(x,y);//d[top[x]]>=d[top[y]]
		change(1,seg[top[x]],seg[x]);
		x=fa[top[x]];
	}
	if(d[x]>d[y]) swap(x,y);//d[x]<=d[y]
	change(1,seg[x],seg[y]);
}
inline ll Qsum(int x,int y) {
	ll res=0;
	while(top[x]!=top[y]) {
		if(d[top[x]]<d[top[y]]) swap(x,y);
		res=Add(res,ask(1,seg[top[x]],seg[x]));
		x=fa[top[x]];
	}
	if(d[x]>d[y]) swap(x,y);//d[x]<=d[y]
	return Add(res,ask(1,seg[x],seg[y]));
}
int main() {
	int n=read(),T=read(),k=read();
	for(register int i=2;i<=n;++i) add(read(),i);
	for(register int i=1;i<=T;++i) {q[i].x=read();q[i].y=read();q[i].id=i;}
	std::sort(q+1,q+1+T,cmp);
	d[1]=1;dfs1(1);dfs2(1,1);//printf("%d\n",tot);
	for(register int i=1;i<=tot;++i) {int x=rev[i];b[i]=Add(b[i-1],qpow(d[x],k)-qpow(d[fa[x]],k)+mod);}
	int now=1;
	for(register int i=1;i<=T;++i) {
		while(now<=q[i].x) {Modify(1,now);++now;}
		ans[q[i].id]=Qsum(1,q[i].y);
	}	
	for(register int i=1;i<=T;++i) printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：wyx__ (赞：3)

这里提供一种 $O(n \sqrt n)$ 的做法。

思路和[这题](https://www.luogu.com.cn/problem/P4211)第二篇题解是一样的，就是把所有的点按编号进行分块，对于每一块预处理出这一块对于每个节点的贡献，对于每个询问，整块的用预处理的结果，边角部分用 $O(1)$ 的倍增 RMQ 暴力求 LCA 深度即可。

接下来讲一下如何预处理每一块的贡献。

设要处理的块在 $l$~$r$，我们先把 $l$~$r$ 之间的节点的标记值 $+1$，然后用一次 DFS 把这些点的祖先节点的标记值都 $+1$，设 $f(i)=i^k-(i-1)^k$，参照前面几篇题解的方法，对于每个节点 $i$，把在这个点到根的路径上所有的点 $k$ （包括节点 $i$ 本身）的 $f(dep[k]) * tag[k]$ 加起来即为这个点的答案。（ $dep$ 为深度，$tag$ 为是否有标记）而计算这个答案的过程也可以用DFS实现。

当然这个方法常数比较大，需要卡一下常数。

code：（最慢的点用时846ms）
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
const ll mod=998244353,siz=800;//实测块的大小开800时比较快
int belong[50005],block[105],bin[50005],dfn[100005],dep[100005],cnt
,st[100005][20],lg2[100005],n,q,k;
ll temp[50005],pw[50005],pw1[50005],ans[105][50005];
int head[50005],nex[50005],var[50005],tot;
//bin即为前面讲到的tag，ans为每一块对每个点的贡献
char buf[(int)5e6],*ss=buf;
inline void init(){buf[fread(buf,1,(int)5e6-1,stdin)]='\n';fclose(stdin);}
inline int readint(){
	int d=0;
	while(!isdigit(*ss))++ss;
	while(isdigit(*ss))d=d*10+(*ss++&15);
	return d;
}
void add(int x,int y){
	var[++tot]=y;
	nex[tot]=head[x];
	head[x]=tot;
}
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void dfs_1(int x){
	st[++cnt][0]=dep[x];
	dfn[x]=cnt;
	for(ri i=head[x];i;i=nex[i]){
		int y=var[i];
		dep[y]=dep[x]+1;
		dfs_1(y);
		st[++cnt][0]=dep[x];
	}
}
//预处理每个点的深度，存在ST表中

void dfs_2(int x){
	for(ri i=head[x];i;i=nex[i]){
		int y=var[i];
		dfs_2(y);
		bin[x]+=bin[y];
	}
}
//向上给标记值+1

void dfs_3(int x,ll dist){
	for(ri i=head[x];i;i=nex[i]){
		int y=var[i];
		dfs_3(y,dist+bin[x]*pw1[dep[x]]);	
	}
	temp[x]+=dist+bin[x]*pw1[dep[x]];
}
//根据标记值处理每个点的贡献

void prework(){
	for(ri i=1;i<=n;i++)pw[i]=qpow(i,k);
	for(ri i=1;i<=n;i++)pw1[i]=(pw[i]-pw[i-1]+mod)%mod;
   //pw1即为之前讲到的f
	dep[1]=1;
	dfs_1(1);
	for(ri i=2;i<=2*n;i++)lg2[i]=lg2[i/2]+1;
	for(ri i=1;i<=17;i++)
		for(ri j=1;j<=2*n-(1<<i);j++)
			st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
   //预处理ST表
	for(ri i=1;i<=n;i++){
		belong[i]=i/siz+1;
		if(belong[i]-belong[i-1]>0)block[belong[i]]=i;
	}
	belong[0]=0;belong[n+1]=belong[n]+1;
    block[0]=0;block[belong[n+1]]=n+1;
    for(ri i=1;i<=belong[n];i++){
    	memset(bin,0,sizeof(bin));
    	memset(temp,0,sizeof(temp));
    	for(ri j=1;j<=n;j++)if(belong[j]==i)bin[j]=1;
    	dfs_2(1);dfs_3(1,0);
    	for(ri j=1;j<=n;j++)ans[i][j]=temp[j];
	}
   //预处理每个块的贡献
}
int lca(int x,int y){
	x=dfn[x],y=dfn[y];
	if(x>y)swap(x,y);
	int p=lg2[y-x+1];
	return min(st[x][p],st[y-(1<<p)+1][p]);
}
//用RMQ求LCA深度

int main(){
	init();
	n=readint(),q=readint(),k=readint();
	for(ri i=2;i<=n;i++){
		int x;
		x=readint();
		add(x,i);
	}
	prework();
	while(q--){
		int r,x;
		r=readint(),x=readint();
		int r1=belong[r]-1;
		ll res=0;
		for(int i=1;i<=r1;i++)res+=ans[i][x];
		for(;belong[r]!=r1&&r>=1;r--)res+=pw[lca(r,x)];
		printf("%lld\n",res%mod);
	}
}
```


---

## 作者：玫葵之蝶 (赞：2)

显然这题和LNOI2014基本是一个题。

~~至少我的做法改了两三行就过了~~

考虑分块，块大小$\sqrt n$

块内用树形dp跑出来每个点y在这个块内的答案$\sum dep\big(lca(i,y)\big)^k$

块外可以预处理$O(1)LCA$，就可以$O(1)$回答了

那么显然总时间复杂度就是$O(n\sqrt n)$了。

改的几行就是加了个k次幂。

代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;

inline int read(){
    int x=0,f=1;char ch=' ';
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return f==1?x:-x;
}

const int N=1e5+5,sqN=250,mod=998244353;
inline int ksm(int a,int n){
	int ans=1;
	while(n){
		if(n&1)ans=(LL)ans*a%mod;
		a=(LL)a*a%mod;
		n>>=1;
	}
	return ans;
}

int n,q,tot,k;
int head[N],to[N],Next[N];
inline void addedge(int x,int y){
    to[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
}

int cnt,dep[N],depk[N],a[N],p[N],st[N][17],Log[N];
inline void dfs1(int x){
    a[++cnt]=x;
    p[x]=cnt;
    st[cnt][0]=x;
    depk[x]=ksm(dep[x],k);
    for(int i=head[x];i;i=Next[i]){
        int u=to[i];
        dep[u]=dep[x]+1;
        dfs1(u);
        a[++cnt]=x;
        st[cnt][0]=x;
    }
}
inline int Min(int x,int y){
    if(p[x]<p[y])return x;
    else return y;
}
inline int getlca(int x,int y){
    if(p[x]>p[y])swap(x,y);
    int k=Log[p[y]-p[x]+1];
    return Min(st[p[x]][k],st[p[y]-(1<<k)+1][k]);
}

int block,bcnt,L[sqN],R[sqN],belong[N];
int f[sqN][N],dp[N];
int vis[N],size[N];
inline void dfs2(int x){
    size[x]=vis[x];
    for(int i=head[x];i;i=Next[i]){
        int u=to[i];
        dfs2(u);
        size[x]+=size[u];
    }
}
inline void dfs3(int x){
    for(int i=head[x];i;i=Next[i]){
        int u=to[i];
        dp[u]=(dp[x]+(LL)(size[x]-size[u])*depk[x])%mod;
        dfs3(u);
    }
    dp[x]=(dp[x]+(LL)size[x]*depk[x])%mod;
}

int main(){
    n=read();q=read();k=read();
    for(int i=2;i<=n;++i){
        int x=read();
        addedge(x,i);
    }
    dep[1]=1;
    dfs1(1);
    for(int k=1;k<=16;++k)
        for(int i=1;i+(1<<k)-1<=cnt;++i)
            st[i][k]=Min(st[i][k-1],st[i+(1<<(k-1))][k-1]);
    Log[0]=-1;
    for(int i=1;i<=cnt;++i)Log[i]=Log[i>>1]+1;
    block=min(n,400);
    bcnt=n/block;
    if(n%block)bcnt++;
    for(int i=1;i<=bcnt;++i)L[i]=(i-1)*block+1,R[i]=i*block;
    R[bcnt]=n;
    for(int i=1;i<=n;++i)belong[i]=(i-1)/block+1;
    for(int i=1;i<=bcnt;++i){
        for(int j=1;j<=n;++j)size[j]=vis[j]=dp[j]=0;
        for(int j=L[i];j<=R[i];++j)vis[j]=1;
        dfs2(1);
        dfs3(1);
        for(int j=1;j<=n;++j)f[i][j]=dp[j];
    }
    for(int s=1;s<=q;++s){
        int l=1,r=read(),x=read();
        LL ans=0;
        if(belong[l]==belong[r]){
            for(int i=l;i<=r;++i)
                ans+=depk[getlca(x,i)];
        }
        else{
            for(int i=l;i<=R[belong[l]];++i)
                ans+=depk[getlca(x,i)];
            for(int i=L[belong[r]];i<=r;++i)
                ans+=depk[getlca(x,i)];
            for(int i=belong[l]+1;i<belong[r];++i)
                ans+=f[i][x];
        }
        printf("%lld\n",ans%mod);
    }
    return 0;
}
```

---

## 作者：iostream (赞：2)

前面的题解都说了树剖的做法，这里贴一下LCT实现的代码。

思路是一样的，在根到节点的路径上进行$dep_i-dep_{fa_i}$的差分，离线之后扫描线，就不作赘述了。

由于$N\le 50000$，所以1/2个log的做法都可以轻松通过。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

const int N=100010,P=998244353;

int n,k,q,fa[N],dep[N],b[N],ans[N];
vector<int>G[N];

void dfs(int u)
{
	for(auto&v:G[u])
		dep[v]=dep[u]+1,dfs(v);
}

int fpow(int a,int b)
{
	ll w(1),o(a);
	while(b) {
		if(b&1) w=w*o%P;
		o=o*o%P;
		b>>=1;
	}
	return w;
}

namespace LCT
{
	int cnt,ch[N][2],fa[N],st[N],top;
	struct node
	{
		int tg;
		ll sb;
		ll s;
		ll ans;
	}t[N];
	
	#define lc(x) (ch[x][0])
	#define rc(x) (ch[x][1])
	
	bool get(int x)
	{
		return rc(fa[x])==x;
	}
	
	bool nrt(int x)
	{
		return rc(fa[x])==x || lc(fa[x])==x;
	}
	
	void up(int x)
	{
		t[x].sb=t[lc(x)].sb+t[rc(x)].sb+b[x];
		t[x].ans=t[lc(x)].ans+t[rc(x)].ans+(ll)b[x]*t[x].s;
	}
	
	void down(int x)
	{
		if(t[x].tg)
		{
			int y=t[x].tg;
			t[x].tg=0;
			if(lc(x))
			{
				t[lc(x)].tg+=y;
				t[lc(x)].s+=y;
				t[lc(x)].ans+=(ll)y*t[lc(x)].sb;
			}
			if(rc(x))
			{
				t[rc(x)].tg+=y;
				t[rc(x)].s+=y;
				t[rc(x)].ans+=(ll)y*t[rc(x)].sb;
			}
		}
	}
	
	void rot(int x)
	{
		int y=fa[x],i=get(x);
		if(nrt(y))
			ch[fa[y]][get(y)]=x;
		fa[x]=fa[y];
		ch[y][i]=ch[x][i^1];
		fa[ch[x][i^1]]=y;
		ch[x][i^1]=y;
		fa[y]=x;
		up(y);
	}
	
	void splay(int x)
	{
		st[top=1]=x;
		for(int y=x;nrt(y);y=fa[y])
			st[++top]=fa[y];
		for(int i=top;i;i--)
			down(st[i]);
		for(int y=fa[x];nrt(x);rot(x),y=fa[x])
			if(nrt(y))
				rot(get(x)==get(y)?y:x);
		up(x);
	}
	
	void access(int x)
	{
		for(int y=0;x;y=x,x=fa[x])
		{
			splay(x);
			rc(x)=y;
		}
	}
	
	void upd(int x,int y)
	{
		t[x].tg+=y;
		t[x].s+=y;
		t[x].ans+=(ll)y*t[x].sb;
	}
	
	void link(int x,int y)
	{
		fa[x]=y;
	}
}

struct Ques {
	int x,y,id;
}a[N];

bool cmp(Ques a,Ques b)
{
	return a.x<b.x;
}

int main()
{
	scanf("%d%d%d",&n,&q,&k);
	for(int i=2; i<=n; i++)
		scanf("%d",&fa[i]),G[fa[i]].push_back(i);
	dep[1]=1;
	dfs(1);
	for(int i=1; i<=n; i++)
	{
		dep[i]=fpow(dep[i],k);
	}
	for(int i=1; i<=n; i++)
	{
		b[i]=(dep[i]-dep[fa[i]]+P)%P;
		LCT::link(i,fa[i]);
	}
	for(int i=1; i<=q; i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].id=i;
	}
	sort(a+1,a+1+q,cmp);
	for(int i=1,j=1; i<=q; i++)
	{
		while(j<=n && j<=a[i].x)
		{
			LCT::access(j);
			LCT::splay(j);
			LCT::upd(j,1);
			j++;
		}
		int o=a[i].y;
		LCT::access(o);
		LCT::splay(o);
		ans[a[i].id]=LCT::t[o].ans%P;
	}
	for(int i=1; i<=q; i++)
		printf("%d\n",ans[i]);
	return 0;
}

---

## 作者：VenusM1nT (赞：2)

树链剖分。

```
我真傻，真的。我单知道 NOIP 会出原题，我没想到省选也会出原题。
——鲁迅
```

亲，这边建议去看一下 $\texttt{[LNOI2014]LCA}$ 呢。

考虑 $k=1$ 时，每次询问 $(x,y)$，可以考虑把 $\text{dep}$ 均摊到根到 $y$ 的路径上，然后可以直接查询，但是这样显然会变成 $\text{O}(n)$ 处理，我们反过来考虑，对 $x$ 进行处理，那么可以离线做，把询问排序，然后每个询问把所有 $i\in[1,x]$ 的点到根的权值都加 $1$，然后直接查询根到 $y$ 的权值和，所有 $x$ 相同的询问都可以一起处理。

那么要怎么扩展到 $k>1$ 呢？我们分析一下 $k=1$ 时的本质，我们加上的这个 $1$ 其实就是 $\text{dep}_x-\text{dep}_{fa[x]}$，那么现在是 $\text{dep}^k$ 的情况，所以我们可以直接扩展到 $k$ 次的情况，即加上的就是 $\text{dep}_x^k-\text{dep}_{fa[x]}^k$，那么依然和 $k=1$ 时一样做，询问离线，然后把 $x$ 相等的一起处理了。不过这个 $\text{dep}_x^k-\text{dep}_{fa[x]}^k$ 需要预处理一下，不然处理非常麻烦。

算法当然就是树剖+线段树了。（听说 $\texttt{LCT}$ 也可以做，当然我是不会的）

```cpp
#include<bits/stdc++.h>
#define MAXN 50005
#define reg register
#define inl inline
#define stc static
#define int long long
using namespace std;
const int Mod=998244353;
stc int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1];
stc int n,q,k,a[MAXN],sum[MAXN],ans[MAXN];
inl int Add(reg int x,reg int y)
{
	return x+y>Mod?x+y-Mod:x+y;
}
inl int Dec(reg int x,reg int y)
{
	return x-y<0?x-y+Mod:(x-y>Mod?x-y-Mod:x-y);
}
inl int Mul(reg int x,reg int y)
{
	return x*y-x*y/Mod*Mod;
}
inl int Pow(reg int x,reg int y)
{
	reg int res=1;
	for(;y;y>>=1,x=Mul(x,x)) if(y&1) res=Mul(res,x);
	return res;
}
inl void AddEdge(reg int u,reg int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
template <typename T> inl void Read(reg T &x)
{
	x=0;
	reg int fu=1;
	reg char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
	x*=fu;
}
struct TreeSplit
{
	int t[MAXN<<2],tag[MAXN<<2];
	int siz[MAXN],son[MAXN],dfn[MAXN],Idx,top[MAXN],faz[MAXN],rk[MAXN],dep[MAXN];
	void Dfs1(reg int u)
	{
		siz[u]=1;
		son[u]=0;
		for(reg int i=fst[u];i;i=nxt[i])
		{
			reg int v=to[i];
			if(v==faz[u]) continue;
			faz[v]=u;
			dep[v]=dep[u]+1;
			Dfs1(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]]) son[u]=v;
		}
	}
	void Dfs2(reg int u,reg int rt)
	{
		dfn[u]=++Idx;
		rk[Idx]=u;
		top[u]=rt;
		if(son[u]) Dfs2(son[u],rt);
		for(reg int i=fst[u];i;i=nxt[i])
		{
			reg int v=to[i];
			if(v==son[u] || v==faz[u]) continue;
			Dfs2(v,v);
		}
	}
	inl void PushUp(reg int rt)
	{
		t[rt]=Add(t[rt<<1],t[rt<<1|1]);
	}
	inl void PushDown(reg int rt,reg int l,reg int r)
	{
		if(tag[rt])
		{
			reg int mid=l+r>>1;
			t[rt<<1]=Add(t[rt<<1],Mul(tag[rt],Dec(sum[mid],sum[l-1])));
			t[rt<<1|1]=Add(t[rt<<1|1],Mul(tag[rt],Dec(sum[r],sum[mid])));
			tag[rt<<1]=Add(tag[rt<<1],tag[rt]);
			tag[rt<<1|1]=Add(tag[rt<<1|1],tag[rt]);
			tag[rt]=0;
		}
	}
	void Modify(reg int rt,reg int l,reg int r,reg int tl,reg int tr)
	{
		if(tl<=l && r<=tr)
		{
			t[rt]=Add(t[rt],Dec(sum[r],sum[l-1]));
			tag[rt]++;
			return;
		}
		reg int mid=l+r>>1;
		PushDown(rt,l,r);
		if(tl<=mid) Modify(rt<<1,l,mid,tl,tr);
		if(tr>mid) Modify(rt<<1|1,mid+1,r,tl,tr);
		PushUp(rt);
	}
	int Query(reg int rt,reg int l,reg int r,reg int tl,reg int tr)
	{
		if(tl<=l && r<=tr) return t[rt];
		reg int mid=l+r>>1,res=0;
		PushDown(rt,l,r);
		if(tl<=mid) res=Add(res,Query(rt<<1,l,mid,tl,tr));
		if(tr>mid) res=Add(res,Query(rt<<1|1,mid+1,r,tl,tr));
		return res;
	}
	inl void Mdy(reg int u)
	{
		for(;u;u=faz[top[u]]) Modify(1,1,n,dfn[top[u]],dfn[u]);
	}
	inl int Qry(reg int u)
	{
		reg int res=0;
		for(;u;u=faz[top[u]]) res=Add(res,Query(1,1,n,dfn[top[u]],dfn[u]));
		return res;
	}
}T;
struct Query
{
	int v,id;
};
vector <Query> vec[MAXN];
signed main()
{
	Read(n);
	Read(q);
	Read(k);
	for(reg int i=2;i<=n;i++)
	{
		Read(T.faz[i]);
		AddEdge(T.faz[i],i);
		AddEdge(i,T.faz[i]);
	}
	T.dep[1]=1;
	T.Dfs1(1);
	T.Dfs2(1,0);
	for(reg int i=1;i<=n;i++) a[i]=Dec(Pow(T.dep[i],k),Pow(T.dep[i]-1,k));
	for(reg int i=1;i<=n;i++) sum[i]=Add(sum[i-1],a[T.rk[i]]);
	for(reg int i=1;i<=q;i++)
	{
		reg int x,y;
		Read(x);
		Read(y);
		vec[x].push_back((Query){y,i});
	}
	for(reg int i=1;i<=n;i++)
	{
		T.Mdy(i);
		for(reg int j=0;j<(int)vec[i].size();j++) ans[vec[i][j].id]=T.Qry(vec[i][j].v);
	}
	for(reg int i=1;i<=q;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：行吟啸九州 (赞：0)

GXOI的题相当水，这个题我估计可以出成TG组D2T3吧。建议可以加强一下数据，加强到4e5最好。

算法一：对于前$1-4$个点，我们可以去暴力枚举统计贡献，通过ST+欧拉序找LCA，可以达到O($n^2$)的复杂度，期望得分20。

算法二：对于$5-8$个点，考虑以1为根的链上的问题，深度为i的点对于下面的点的贡献是$i^k$，对于他上面的深度为j的点的贡献是$j^k$，这两种贡献可以分开统计。

我们发现这个题可以离线做，再加上$9-10$个点的暗示，不难想到把询问离线下来，按x排序，不断加点，然后统计贡献。

单点修改，区间求和，这个东西用两个树状数组维护即可，复杂度O($nlogn$)，期望得分40。

之后的思路就是正解了，其他部分分的存在意义我感觉就是暗示正解。

算法三：结合上面的思路，我们可以想到，对于每次询问，把对$i <= x$统计答案转化成对于y的每个祖先统计贡献。

然后我们考虑各个祖先的贡献，我们可以容斥地统计这个贡献，对于$i$的某个祖先$j$，$j$的儿子$k$的后代里有$i$, 我们把$sum[j] * dep[j] ^ k$统计到贡献里，再容斥掉$sum[k] * dep[j] ^ k$， 其中$sum[i]$代表$i$子树内已被加入的点的数量。

$Si$代表i的祖先集合，统计答案的式子为$\sum\limits_{j ∈ Si}(dep[j]^k-(dep[j] - 1)^k) * sum[j]$。

然后我们的问题就是如何用数据结构维护这个式子。

不难发现，```j```点的子树内每多一个点，它的权值就要加上$dep[j]^k-{(dep[j] - 1)}^k$。每次x修改只涉及直上直下的路径，对于一条起点为```i```，终点为```j```的路径，权值的增值是$dep[j]^k - (dep[i] - 1) ^ k$。

所以这个数据结构需要干两件事。

第一件事：把一个点到根的路径加上某个值。

第二件事：查询一个点到根路径的权值和。

我们可以树剖或者LCT维护。前者复杂度O($n\log ^2n$)，后者复杂度O($n\log n$)。不过效率都是差不多的，基本跑个$4e5$压力不大。

```
#include<bits/stdc++.h>
using namespace std;
#define maxn 50005
#define maxt 200005
#define int long long
#define mod 998244353
#define For(i, j, n) for(register int i = j ; i <= n ; ++i)
int n, k, Q, tot, po[maxn];
int c[maxt], fa[maxn], ans[maxn], dep[maxn], dfn[maxn], lis[maxn], siz[maxn], top[maxn], lazy[maxt], mson[maxn]; 
vector<int>E[maxn];
struct node{ int x, y, id; }q[maxn];
//线段树 
#define ls x << 1
#define rs x << 1 | 1
#define mid (l + r >> 1) 
inline void pushup(int x){ c[x] = c[ls] + c[rs]; }
inline void add(int x, int l, int r, int y){ c[x] = (c[x] + (po[dep[lis[r]]] - po[dep[lis[l]] - 1] + mod) * y) % mod, lazy[x] += y; }
inline void pushdown(int x, int l, int r){ add(ls, l, mid, lazy[x]), add(rs, mid + 1, r, lazy[x]), lazy[x] = 0; }
inline int query(int x, int l, int r, int ql, int qr){\
	if(ql <= l && r <= qr) return c[x];
	if(lazy[x]) pushdown(x, l, r);
	int ans = 0;
	if(ql <= mid) ans += query(ls, l, mid, ql, qr);
	if(qr > mid) ans += query(rs, mid + 1, r, ql, qr);
	return ans % mod; 
}
inline void revise(int x, int l, int r, int ql, int qr){\
	if(ql <= l && r <= qr) return add(x, l, r, 1);
	if(lazy[x]) pushdown(x, l, r);
	if(ql <= mid) revise(ls, l, mid, ql, qr);
	if(qr > mid) revise(rs, mid + 1, r, ql, qr);
	pushup(x);
}
//树剖 
inline void dfs(int x){
	dep[x] = dep[fa[x]] + (siz[x] = 1);
	for(auto i : E[x]){
		dfs(i), siz[x] += siz[i];
		if(siz[i] > siz[mson[x]]) mson[x] = i;
	}
}
inline void dfs(int x, int tp){
	top[x] = tp, lis[dfn[x] = ++tot] = x;
	if(mson[x]) dfs(mson[x], tp);
	for(auto i : E[x]) if(!dfn[i]) dfs(i, i);
}
//jump 
inline void Insert(int x){
	for( ; top[x] ^ 1 ; x = fa[top[x]]) revise(1, 1, n, dfn[top[x]], dfn[x]);
	revise(1, 1, n, 1, dfn[x]);
}
inline int Query(int x){
	int ans = 0;
	for( ;top[x] ^ 1 ; x = fa[top[x]]) ans += query(1, 1, n, dfn[top[x]], dfn[x]);
	return ans + query(1, 1, n, 1, dfn[x]);
}
//主函数 
inline bool cmp(node a, node b){ return a.x < b.x; }
inline int quickpow(int x, int y){
	int sum = 1;
	for( ; y ; x = x * x % mod, y >>= 1) if(y & 1) sum = sum * x % mod;
	return sum;
}
signed main(){
	scanf("%lld %lld %lld", &n, &Q, &k);
	For(i, 2, n) scanf("%lld", &fa[i]), E[fa[i]].push_back(i);
	dfs(1), dfs(1, 1);
	For(i, 1, n) po[i] = quickpow(i, k);
	For(i, 1, Q) q[i].id = i, scanf("%lld %lld", &q[i].x, &q[i].y);
	sort(q + 1, q + Q + 1, cmp);
	For(i, 1, Q){
		For(j, q[i - 1].x + 1, q[i].x) Insert(j);
		ans[q[i].id] = Query(q[i].y);
	}
	For(i, 1, Q) printf("%lld\n", ans[i] % mod);
	return 0;
}

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P5305)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~据说这是板子题，可是我没有做过。~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;从简化版本开始分析：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当$k=1$的时候，这是一个经典的树链剖分的问题（双倍经验[$[LNOI2014]LCA$](https://www.luogu.com.cn/problem/P4211)）。把询问离线下来，按照$x$排序。顺序加入$1\sim n$，每次加入一个数$i$就将$i$到根的路径上的点$+1$。查询就查询$y$到根的路径上的点和。这个方法很好理解，不再详说。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑$k>1$的时候该怎么做。不难发现，在$k=1$的时候，我们对于一个点$u$加上的相当于$dep(u)-(dep(u)-1)$。所以我们依葫芦画瓢，对于一个点$u$，修改的时候就加上$dep(i)^k-(dep(i)-1)^k$（$i$为$u$对应的输入的树上的点）。对于线段树上的节点，如果它是叶子节点，就可以直接算出来一次该加多少；如果不是，为了保证标记下传答案不变，它一次加的值就是左右儿子一次加的和。比如$v$和$w$是共属一个父亲$u$的叶子节点，对应输入的树上的点$i$和$j$，那么$v$一次增加$dep(i)^k-(dep(i)-1)^k$，$w$一次增加$dep(j)^k-(dep(j)-1)^k$，而$u$一次就应该增加$dep(i)^k-(dep(i)-1)^k+dep(j)^k-(dep(j)-1)^k$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;时间是$O(q\log_2q+(n+q)\log_2n)$。  
# 代码
```cpp
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, pair<int, int> > queries;

#define xx first
#define yy second.first
#define zz second.second

const int mod = 998244353;
const int MAXN = 50005, MAXQ = 50005, MAXLOG = 20;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct edge
{
	int to, nxt;
}Graph[MAXN << 1];

struct segmentTreeNode
{
	int s, adup, tag;
	#define s( a ) ( segTree[a].s )
	#define tag( a ) ( segTree[a].tag )
	#define adup( a ) ( segTree[a].adup )
}segTree[MAXN << 2];

queries q[MAXQ];
int ans[MAXQ];

int f[MAXN];
int LTail[MAXN], seq[MAXN];
int dep[MAXN], head[MAXN], heavy[MAXN], siz[MAXN], bel[MAXN], LPos[MAXN];
int N, Q, K, cnt, ID, tot;
 
int fix( const int x ) { return ( x % mod + mod ) % mod; }
void add( const int x, const int val ) { s( x ) = ( s( x ) + 1ll * val * adup( x ) % mod ) % mod, tag( x ) += val; }
void upt( const int x ) { s( x ) = ( s( x << 1 ) + s( x << 1 | 1 ) ) % mod, adup( x ) = ( adup( x << 1 ) + adup( x << 1 | 1 ) ) % mod; }
void normalize( const int x ) { if( ! tag( x ) ) return ; add( x << 1, tag( x ) ), add( x << 1 | 1, tag( x ) ), tag( x ) = 0; }

int qkpow( int base, int indx )
{
	int res = 1;
	while( indx )
	{
		if( indx & 1 ) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod, indx >>= 1;
	}
	return res;
}

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void DFS1( const int u, const int fa )
{
	dep[u] = dep[fa] + 1, siz[u] = 1, heavy[u] = -1;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa ) 
		{
			DFS1( v, u ), siz[u] += siz[v];
			if( heavy[u] == -1 || siz[heavy[u]] < siz[v] ) heavy[u] = v;
		}
}

void DFS2( const int u, const int fa )
{
	LPos[u] = ++ ID, seq[ID] = u;
	if( ~ heavy[u] ) DFS2( heavy[u], u ), bel[u] = bel[heavy[u]];
	else bel[u] = ++ tot;
	LTail[bel[u]] = u;
	for( int i = head[u], v ; i ; i = Graph[i].nxt ) 
		if( ( v = Graph[i].to ) ^ fa && v ^ heavy[u] ) DFS2( v, u );
}

void build( const int u, const int l, const int r )
{
	if( l > r ) return ;
	int mid = l + r >> 1;
	if( l == r ) 
	{ s ( u ) = 0, adup( u ) = fix( qkpow( dep[seq[l]], K ) - qkpow( dep[seq[l]] - 1, K ) ), tag( u ) = 0; return ; }
	build( u << 1, l, mid ), build( u << 1 | 1, mid + 1, r ), upt( u );
}

void update( const int u, const int l, const int r, const int segL, const int segR, const int val )
{
	if( l > r ) return ;
	int mid = l + r >> 1;
	if( segL <= l && r <= segR ) { add( u, val ); return ; }
	if( l == r ) return; normalize( u );
	if( segL <= mid ) update( u << 1, l, mid, segL, segR, val );
	if( segR > mid ) update( u << 1 | 1, mid + 1, r, segL, segR, val );
	upt( u );
}

int query( const int u, const int l, const int r, const int segL, const int segR )
{
	if( l > r ) return 0;
	int mid = l + r >> 1, ret = 0;
	if( segL <= l && r <= segR ) return s( u );
	if( l == r ) return 0; normalize( u );
	if( segL <= mid ) ret = ( ret + query( u << 1, l, mid, segL, segR ) ) % mod;
	if( segR > mid ) ret = ( ret + query( u << 1 | 1, mid + 1, r, segL, segR ) ) % mod;
	return ret;
}

void change( const int x )
{ 
	for( int i = x ; i ; i = f[LTail[bel[i]]] ) 
		update( 1, 1, N, LPos[LTail[bel[i]]], LPos[i], 1 ); 
}

int ask( const int x )
{
	int ret = 0;
	for( int i = x ; i ; i = f[LTail[bel[i]]] )
		ret = ( ret + query( 1, 1, N, LPos[LTail[bel[i]]], LPos[i] ) ) % mod;
	return ret;
}

int main()
{
	read( N ), read( Q ), read( K );
	for( int i = 2 ; i <= N ; i ++ ) read( f[i] ), addEdge( f[i], i );
	DFS1( 1, 0 ), DFS2( 1, 0 );
	for( int i = 1 ; i <= Q ; i ++ ) read( q[i].xx ), read( q[i].yy ), q[i].zz = i;
	sort( q + 1, q + 1 + Q );
	build( 1, 1, N );
	for( int i = 1 ; i <= Q ; i ++ )
	{
		if( q[i].xx ^ q[i - 1].xx ) for( int j = q[i - 1].xx + 1 ; j <= q[i].xx ; j ++ ) change( j );
		ans[q[i].zz] = ask( q[i].yy );
	}
	for( int i = 1 ; i <= Q ; i ++ ) write( ans[i] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Rainybunny (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.com.cn/problem/P5305).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们先考虑简单的情况, $k=1$.
## $k=1$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此时, 我们相当于要求:
$$
Ans_i=\sum_{j\le x_i}depth(LCA(j,y_i))
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;注意到, 一个点到根路径上的结点个数就是该点的深度. 所以我们把询问离线, 按$x$从小到大排序. 当求和的下标从$x_1$增大到$x_2$, 对于$(x_1,x_2]$中所有点, 我们将其到根的路径所有点点权全部$+1$. 求答案时, 统计$y$到根的点权和即可.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[双倍经验](https://www.luogu.com.cn/problem/P4211).
## $k\not=1$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;为什么我们在$k=1$时只把$x$到根的路径点权$+1$?  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;因为$x$到根的点权和就是$x$的深度.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以, 我们就要设计一种加点权的方法使得一个点到根的路径点权和就是该点深度的$k$次方.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;很简单, 利用差分, 对于结点$u$, 点权加上$depth(u)^k-(depth(u)-1)^k$就行了. 在树链剖分建树的时候, 我们顺便处理处每个区间的$adv$, 表示当这个区间整体$'+1'$时, 其实是加上$adv$, 就转化成$k=1$的情况了.
## 代码
```cpp
#include <cstdio>
#include <utility>
#include <algorithm>

#define Int register int

using namespace std;

const int MAXN = 5e4, MOD = 998244353;
int n, Q, k, Cnte, Head[MAXN + 5];
int Depth[MAXN + 5], Heav[MAXN + 5], Siz[MAXN + 5], Fa[MAXN + 5];
int Indx, Top[MAXN + 5], DFN[MAXN + 5], Rank[MAXN + 5], Ans[MAXN + 5];
pair<int, pair<int, int> > q[MAXN + 5];

struct Edge {
	int To, _nxt;
	Edge () {}
	Edge ( const int t, const int n ): To ( t ), _nxt ( n ) {}
} Graph[MAXN + 5];

inline int qkpow ( int a, int b, const int p ) {
	int ret = 1;
	for ( ; b; a = 1LL * a * a % p, b >>= 1 ) ret = 1LL * ret * ( b & 1 ? a : 1 ) % p;
	return ret;
}

class Segment_Tree {
private:
	struct Node {
		int l, r, Sum, Adv, Lazy;
	} Tree[MAXN << 2];

public:
	inline void Push_up ( const int i, const bool upadv = false ) {
		Tree[i].Sum = ( Tree[i << 1].Sum + Tree[i << 1 | 1].Sum ) % MOD;
		if ( upadv ) Tree[i].Adv = ( Tree[i << 1].Adv + Tree[i << 1 | 1].Adv ) % MOD;
	}
	inline void Push_dn ( const int i ) {
		if ( ! Tree[i].Lazy ) return ;
		int& k = Tree[i].Lazy;
		Tree[i << 1].Lazy += k, Tree[i << 1 | 1].Lazy += k;
		Tree[i << 1].Sum = ( Tree[i << 1].Sum + 1LL * Tree[i << 1].Adv * k % MOD ) % MOD;
		Tree[i << 1 | 1].Sum = ( Tree[i << 1 | 1].Sum + 1LL * Tree[i << 1 | 1].Adv * k % MOD ) % MOD;
		k = 0;
	}
	inline void Build ( const int i, const int l, const int r ) {
		Tree[i] = { l, r, 0, 0, 0 };
		if ( l == r ) return Tree[i].Adv = ( qkpow ( Depth[Rank[l]], k, MOD ) - qkpow ( Depth[Rank[l]] - 1, k, MOD ) + MOD ) % MOD, void ();
		int mid = l + r >> 1;
		Build ( i << 1, l, mid ), Build ( i << 1 | 1, mid + 1, r );
		Push_up ( i, true );
	}
	inline void Update ( const int i, const int l, const int r, const int x ) {
		if ( r < Tree[i].l || Tree[i].r < l ) return ;
		if ( l <= Tree[i].l && Tree[i].r <= r ) {
			Tree[i].Sum = ( Tree[i].Sum + 1LL * Tree[i].Adv * x % MOD ) % MOD;
			return Tree[i].Lazy += x, void ();
		}
		Push_dn ( i );
		Update ( i << 1, l, r, x ), Update ( i << 1 | 1, l, r, x );
		Push_up ( i );
	}
	inline int Query ( const int i, const int l, const int r ) {
		if ( r < Tree[i].l || Tree[i].r < l ) return 0;
		if ( l <= Tree[i].l && Tree[i].r <= r ) return Tree[i].Sum;
		return Push_dn ( i ), ( Query ( i << 1, l, r ) + Query ( i << 1 | 1, l, r ) ) % MOD;
	}
} ST;

inline int rint () {
	int x = 0; char s = getchar ();
	for ( ; s < '0' || '9' < s; s = getchar () );
	for ( ; '0' <= s && s <= '9'; s = getchar () ) x = ( x << 3 ) + ( x << 1 ) + ( s ^ '0' );
	return x;
}

inline void Link ( const int f, const int t ) {
	Graph[++ Cnte] = Edge ( t, Head[f] );
	Head[f] = Cnte;
}

inline void DFS1 ( const int u, const int fa ) {
	Depth[u] = Depth[Fa[u] = fa] + ( Siz[u] = 1 );
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		DFS1 ( v = Graph[i].To, u ), Siz[u] += Siz[v];
		if ( Siz[v] > Siz[Heav[u]] ) Heav[u] = v;
	}
}

inline void DFS2 ( const int u, const int tp ) {
	Top[Rank[DFN[u] = ++ Indx] = u] = tp;
	if ( Heav[u] ) DFS2 ( Heav[u], tp );
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ( v = Graph[i].To ) ^ Heav[u] ) {
			DFS2 ( v, v );
		}
	}
}

inline void Add ( int x, int y, const int v ) {
	for ( ; Top[x] ^ Top[y]; ) {
		if ( Depth[Top[x]] < Depth[Top[y]] ) x ^= y, y ^= x, x ^= y;
		ST.Update ( 1, DFN[Top[x]], DFN[x], 1 );
		x = Fa[Top[x]];
	}
	if ( Depth[x] < Depth[y] ) x ^= y, y ^= x, x ^= y;
	ST.Update ( 1, DFN[y], DFN[x], 1 );
}

inline int Sum ( int x, int y ) {
	int ret = 0;
	for ( ; Top[x] ^ Top[y]; ) {
		if ( Depth[Top[x]] < Depth[Top[y]] ) x ^= y, y ^= x, x ^= y;
		ret = ( ret + ST.Query ( 1, DFN[Top[x]], DFN[x] ) ) % MOD;
		x = Fa[Top[x]];
	}
	if ( Depth[x] < Depth[y] ) x ^= y, y ^= x, x ^= y;
	ret = ( ret + ST.Query ( 1, DFN[y], DFN[x] ) ) % MOD;
	return ret;
}

inline void Work () {
	n = rint (), Q = rint (), k = rint ();
	for ( Int i = 2; i <= n; ++ i ) Link ( rint (), i );
	DFS1 ( 1, 0 ), DFS2 ( 1, 1 );
	ST.Build ( 1, 1, n );
	for ( Int i = 1; i <= Q; ++ i ) q[i].first = rint (), q[i].second = { rint (), i };
	sort ( q + 1, q + Q + 1 );
	for ( Int i = 1, lstx = 0; i <= Q; ++ i ) {
		int x = q[i].first, y = q[i].second.first, id = q[i].second.second;
		for ( Int j = lstx + 1; j <= x; ++ j ) Add ( 1, j, 1 );
		Ans[id] = Sum ( 1, y );
		lstx = x;
	}
	for ( Int i = 1; i <= Q; ++ i ) printf ( "%d\n", Ans[i] );
}

int main () {
//	freopen ( "poetry.in", "r", stdin );
//	freopen ( "poetry.out", "w", stdout );
	Work ();
	return 0;
}

/*
5 1 2
1
4
1
2
2 5
*/
```

---

## 作者：Iota2029 (赞：0)

这道题十分明显。不就是线段树（主席树）？  
但是如何维护?  
既然是$LCA$，那么我们考虑用树剖来求。

若果题目中没有那个$k$，那么容易想到差分：将跟到每个$i$的路径值加一，那么跟到$y$的路径值就是答案。

那么这道题也可以用类似的思想。于是点$x$的贡献就不仅仅是1，而是$dep_{x}^k - dep_{fa_{x}}^k$。然后就可以维护了。

和一道题很像，[Luogu P4211](https://www.luogu.org/problem/P4211)，只不过是套了个$k$次方。

上个代码？   
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#define ll long long
using namespace std;

const int N = 5e4 + 10;
const int mod = 998244353;
int n, q, k;
int to[N], nxt[N], last[N], cnt = 0, tot = 0;
int fa[N], id[N], rk[N], son[N], sz[N], dep[N], top[N], val[N];
struct Tree {int ls, rs, tag, sum, val;}t[N <<7];
int rt[N], seg_tot = 0;

pair<int,int> operator + (const pair<int,int> &a, const pair<int,int> &b)
{
	return make_pair((a.first + b.first) % mod, (a.second + b.second) % mod);
}
int f_pow(int a,int x) 
{
	int ret = 1;
	for (;x;x >>= 1)
		(x & 1) && (ret = (ll)ret * a % mod), a = (ll)a * a % mod;
	return ret;
}
void add(int u,int v) {to[ ++cnt] = v, nxt[cnt] = last[u], last[u] = cnt;}
void Dfs1(int p)
{
	sz[p] = 1, val[p] = (f_pow(dep[p], k) - f_pow(dep[fa[p]], k) % mod + mod) % mod;
	for (int i = last[p];i;i = nxt[i])
		if (to[i] ^ fa[p])
			{
				fa[to[i]] = p, dep[to[i]] = dep[p] + 1, 
				Dfs1(to[i]), sz[p] += sz[to[i]];
				if (!son[p] || sz[son[p]] < sz[to[i]]) son[p] = to[i];
			}
}
void Dfs2(int p)
{
	rk[id[p] = ++tot] = p;
	if (son[p]) 
		top[son[p]] = top[p], Dfs2(son[p]);
	for (int i = last[p];i;i = nxt[i])
		if (!id[to[i]]) 
			top[to[i]] = to[i], Dfs2(to[i]);
}
struct SGT 
{
	#define ls(p) t[p].ls
	#define rs(p) t[p].rs
	void build(int &p,int l,int r)
	{
		p = ++seg_tot;
		if (l == r) {t[p].val = val[rk[l]]; return;}
		int mid = l + r >>1;
		build(ls(p), l, mid), build(rs(p), mid + 1, r);
		t[p].val = (t[ls(p)].val + t[rs(p)].val) % mod;
	}
	void change(int l,int r,int &p,int tl,int tr)
	{
		t[ ++seg_tot] = t[p], p = seg_tot;
		if (l <= tl && tr <= r) 
		{
			t[p].sum = (t[p].sum + t[p].val) % mod, t[p].tag = (t[p].tag + 1) % mod;
			return;
		}
		int mid = tl + tr >>1;
		if (mid >= l) change(l, r, ls(p), tl, mid);
		if (mid < r) change(l, r, rs(p), mid + 1, tr);
		t[p].sum = ((t[ls(p)].sum + t[rs(p)].sum) % mod + (ll)t[p].tag * t[p].val) % mod;
	}
	pair<int,int> query(int l,int r,int p,int tl,int tr)
	{
		if (!p || l <= tl && tr <= r) 
			return make_pair(t[p].sum, t[p].val);
		int mid = tl + tr >>1;
		pair<int,int> ret = make_pair(0, 0);
		if (mid >= l) ret = ret + query(l, r, ls(p), tl ,mid);
		if (mid < r) ret = ret + query(l, r, rs(p), mid + 1, tr);
		ret.first = (ll)(ret.first + (ll)ret.second * t[p].tag) % mod;
		return ret;
	}
}T;
int query(int x,int p)
{
	int ret = 0;
	while (x) 
		ret = (ret + T.query(id[top[x]], id[x], rt[p], 1, n).first) % mod, x = fa[top[x]];
	return ret;
}

int main()
{
	scanf("%d %d %d", &n, &q, &k);
	for (int i = 2, u;i <= n; ++i)
		scanf("%d", &u), add(u, i);
	dep[1] = top[1] = 1, Dfs1(1), Dfs2(1);
	T.build(rt[0], 1, n);
	for (int i = 1, x;i <= n && (x = i, rt[i] = rt[i - 1], 1); ++i)
		while (x)
			T.change(id[top[x]], id[x], rt[i], 1, n), x = fa[top[x]];
	for (int x, y;q--;)
	{
		scanf("%d %d", &x, &y);
		printf("%d\n", query(y, x));
	}
	return 0;
}
```

---

## 作者：hl666 (赞：0)

好套路的题目，和[Luogu P4211 [LNOI2014]LCA](https://www.luogu.org/problemnew/show/P4211)基本上就是一个题

先考虑$\sum{i\le x}\ depth(lca(i,y))$怎么做（其实就是LNOI那题）

很容易发现此时我们两个点对的贡献为$\operatorname{lca}$的深度$\Leftrightarrow$两点与根节点公共路径长度

所以我们可以利用**莫队+树剖**，每次加一个点就是到根的一条链加$1$，查询就是查某个点到根的路径和，复杂度是$O(n\sqrt n\log^2 n)$

然后发现删除其实完全没有必要，因此我们**离线**一下就变成$O(n\log^2 n)$的了

那么考虑这题怎么做，上面的算法相当于这里的$k=1$，而这个累加的$1$其实就是$( depth(x)+1)^1-depth(x)^1$，是一个**树上差分**的过程

因此这题每个点每次要加上的值就是$( depth(x)+1)^k-depth(x)^k$，乍一看不好维护，其实仔细想一想每次加的都是定值

那么我们线段树处理出所有对应区间的每次增加值的和，修改的时候加上这个值即可。总体复杂度$O(n\log^2 n)$

CODE

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
#include<utility>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
typedef pair <int,int> pi;
const int N=50005,mod=998244353;
struct edge
{
	int to,nxt;
}e[N]; int head[N],n,q,k,cnt,anc[N],dep[N],id[N],s[N],x,y,ans[N]; vector <pi> et[N];
class FileInputOutput
{
	private:
		static const int S=1<<21;
		#define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
		#define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
		char Fin[S],Fout[S],*A,*B; int Ftop,pt[15];
	public:
		Tp inline void read(T& x)
		{
			x=0; char ch; while (!isdigit(ch=tc()));
			while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
		}
		Tp inline void write(T x)
		{
			if (!x) return (void)(pc('0'),pc('\n')); RI ptop=0;
			while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc('\n');
		}
		inline void Fend(void)
		{
			fwrite(Fout,1,Ftop,stdout);
		}
		#undef tc
		#undef pc
}F;
inline void inc(int& x,CI y)
{
	if ((x+=y)>=mod) x-=mod;
}
inline int sum(CI a,CI b)
{
	int t=a+b; return t>=mod?t-mod:t;
}
inline int sub(CI a,CI b)
{
	int t=a-b; return t<0?t+mod:t;
}
inline int quick_pow(int x,int p,int mul=1)
{
	for (;p;p>>=1,x=1LL*x*x%mod) if (p&1) mul=1LL*mul*x%mod; return mul;
}
inline void addedge(CI x,CI y)
{
	e[++cnt]=(edge){y,head[x]}; head[x]=cnt;
}
class Segment_Tree
{
	private:
		struct segment
		{
			int sum,val,tag;
		}node[N<<2];
		#define ls now<<1
		#define rs now<<1|1
		#define S(x) node[x].sum
		#define V(x) node[x].val
		#define T(x) node[x].tag
		inline void pushdown(CI now)
		{
			if (!T(now)) return; T(ls)+=T(now); inc(S(ls),1LL*T(now)*V(ls)%mod);
			T(rs)+=T(now); inc(S(rs),1LL*T(now)*V(rs)%mod); T(now)=0;
		}
	public:
		#define TN CI now=1,CI l=1,CI r=n
		#define LS ls,l,mid
		#define RS rs,mid+1,r
		inline void build(TN)
		{
			if (l==r) return (void)(V(now)=sub(quick_pow(dep[s[l]]+1,k),quick_pow(dep[s[l]],k)));
			int mid=l+r>>1; build(LS); build(RS); V(now)=sum(V(ls),V(rs));
		}
		inline int query(CI beg,CI end,TN)
		{
			if (beg<=l&&r<=end) return S(now); int mid=l+r>>1,ret=0; pushdown(now);
			if (beg<=mid) inc(ret,query(beg,end,LS)); if (end>mid) inc(ret,query(beg,end,RS)); return ret;
		}
		inline void modify(CI beg,CI end,TN)
		{
			if (beg<=l&&r<=end) return ++T(now),inc(S(now),V(now)); int mid=l+r>>1; pushdown(now);
			if (beg<=mid) modify(beg,end,LS); if (end>mid) modify(beg,end,RS); S(now)=sum(S(ls),S(rs));
		}
		#undef ls
		#undef rs
		#undef S
		#undef V
		#undef T
		#undef TN
		#undef LS
		#undef RS
}SEG;
class Heavy_Light_Division
{
	private:
		int son[N],top[N],size[N],idx;
	public:
		#define to e[i].to
		inline void DFS1(CI now)
		{
			size[now]=1; for (RI i=head[now];i;i=e[i].nxt)
			{
				dep[to]=dep[now]+1; DFS1(to); size[now]+=size[to];
				if (size[to]>size[son[now]]) son[now]=to;
			}
		}
		inline void DFS2(CI now,CI topf=1)
		{
			s[id[now]=++idx]=now; top[now]=topf; if (son[now]) DFS2(son[now],topf);
			for (RI i=head[now];i;i=e[i].nxt) if (to!=son[now]) DFS2(to,to);
		}
		inline int query(int nw,int ret=0)
		{
			while (top[nw]) inc(ret,SEG.query(id[top[nw]],id[nw])),nw=anc[top[nw]]; return ret;
		}
		inline void modify(int nw)
		{
			while (top[nw]) SEG.modify(id[top[nw]],id[nw]),nw=anc[top[nw]];
		}
		#undef to
}T;
int main()
{
	//freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
	RI i; for (F.read(n),F.read(q),F.read(k),i=2;i<=n;++i)
	F.read(anc[i]),addedge(anc[i],i); for (i=1;i<=q;++i)
	F.read(x),F.read(y),et[x].push_back(make_pair(y,i));
	for (T.DFS1(1),T.DFS2(1),SEG.build(),i=1;i<=n;++i)
	{
		T.modify(i); for (pi it:et[i]) ans[it.second]=T.query(it.first);
	}
	for (i=1;i<=q;++i) F.write(ans[i]); return F.Fend(),0;
}
```



---

## 作者：MLEAutoMaton (赞：0)

## 传送门
[Loj](https://loj.ac/problem/3088)

## Solution
我们先想一下答案怎么转换(如果$k=1$)?
把$y$到根节点的路径打上标记,答案就是$i \leq x$到根节点的路径的标记总数.
这个又可以变成:
$i \leq x$到根节点的路径打标记,然后$y$到根节点的标记总数.
然后如果$k!=1$,也可以差分就好了.

## 代码实现
```cpp
/*
  mail: mleautomaton@foxmail.com
  author: MLEAutoMaton
  This Code is made by MLEAutoMaton
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<iostream>
using namespace std;
#define ll long long
#define re register
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi()
{
	int f=1,sum=0;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=50010,Mod=998244353;
struct node{int to,nxt;}e[N<<1];
struct ques{int x,y,id;}q[N];
int front[N],cnt,dep[N],fa[N],siz[N],son[N],dfn[N],top[N],Time,n,Q,k,id[N],sum[N];
int qpow(int a,int b){int ret=1;while(b){if(b&1)ret=1ll*ret*a%Mod;a=1ll*a*a%Mod;b>>=1;}return ret;}
void Add(int u,int v){e[++cnt]=(node){v,front[u]};front[u]=cnt;}
bool cmp(ques a,ques b){return a.x<b.x;}
void dfs1(int u,int ff)
{
	dep[u]=dep[ff]+1;siz[u]=1;
	for(int i=front[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void dfs2(int u,int tp)
{
	dfn[u]=++Time;top[u]=tp;id[dfn[u]]=u;
	if(!son[u])return;
	dfs2(son[u],tp);
	for(int i=front[u];i;i=e[i].nxt)
	{
		int v=e[i].to;if(v==son[u])continue;
		dfs2(v,v);
	}
}
struct Tree{int sum,atag;}t[N<<2];
void pushup(int x)
{
	t[x].sum=(t[x<<1].sum+t[x<<1|1].sum)%Mod;
}
void pushdown(int x,int l,int r)
{
	if(t[x].atag)
	{
		int mid=(l+r)>>1;
		t[x<<1].sum=(t[x<<1].sum+1ll*t[x].atag*((sum[mid]-sum[l-1]+Mod)%Mod)%Mod)%Mod;
		t[x<<1|1].sum=(t[x<<1|1].sum+1ll*t[x].atag*((sum[r]-sum[mid]+Mod)%Mod)%Mod)%Mod;
		t[x<<1].atag+=t[x].atag;t[x<<1|1].atag+=t[x].atag;
		t[x].atag=0;
	}
}
void modify(int o,int l,int r,int posl,int posr)
{
	if(posl<=l && r<=posr)
	{
		t[o].sum=((t[o].sum+sum[r])%Mod-sum[l-1]+Mod)%Mod;
		t[o].atag++;
		return;
	}
	int mid=(l+r)>>1;pushdown(o,l,r);
	if(posl<=mid)modify(o<<1,l,mid,posl,posr);
	if(mid<posr)modify(o<<1|1,mid+1,r,posl,posr);
	pushup(o);
}
int query(int o,int l,int r,int posl,int posr)
{
	if(posl<=l && r<=posr)return t[o].sum;
	int mid=(l+r)>>1,s=0;pushdown(o,l,r);
	if(posl<=mid)s=query(o<<1,l,mid,posl,posr);
	if(mid<posr)s=(s+query(o<<1|1,mid+1,r,posl,posr))%Mod;
	return s;
}
void Modify(int x)
{
	while(x)
	{
		modify(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
}
int Query(int x)
{
	int ret=0;
	while(x)
	{
		ret=(ret+query(1,1,n,dfn[top[x]],dfn[x]))%Mod;
		x=fa[top[x]];
	}
	return ret;
}
int ans[N];
int main()
{
	freopen("poetry.in","r",stdin);
	freopen("poetry.out","w",stdout);
	n=gi();Q=gi();k=gi();
	for(int i=2;i<=n;i++)fa[i]=gi(),Add(fa[i],i);
	for(int i=1;i<=Q;i++)q[i].x=gi(),q[i].y=gi(),q[i].id=i;
	sort(q+1,q+Q+1,cmp);
	dfs1(1,1);dfs2(1,1);
	for(int i=1;i<=n;i++)sum[i]=(sum[i-1]+(qpow(dep[id[i]],k)-qpow(dep[id[i]]-1,k)+Mod)%Mod)%Mod;
	int pos=1;
	for(int i=1;i<=Q;i++)
	{
		while(pos<=q[i].x)
		{
			Modify(pos);pos++;
		}
		ans[q[i].id]=Query(q[i].y);
	}
	for(int i=1;i<=Q;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：GKxx (赞：0)

来个稍微有点不一样的

其实大体思路大家都已经讲得比较到位了

就是把[LNOI2014]LCA那题改一改，把加$1$改成加$k$次差分

可是询问离线什么的最讨厌了

我这种懒人当然是写可持久化线段树了

空间要开大一点，注意标记下传的时候也要复制节点

按可持久化的方法写就行了

所以其实这题完全可以强制在线嘛！

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

typedef long long LL;

const LL mod = 998244353;
const int maxn = 5e4 + 207;

inline LL qpow(LL x, LL k) {
	LL s = 1;
	for (; k; x = x * x % mod, k >>= 1)
		if (k & 1) s = s * x % mod;
	return s;
}

int v[maxn], head[maxn], next[maxn], etot;
int dep[maxn], top[maxn], fa[maxn], size[maxn], son[maxn], dfn[maxn], arcdfn[maxn], xys;
LL s[maxn], a[maxn];
int n, q, K;

inline void ae(int x, int y) {
	v[++etot] = y; next[etot] = head[x]; head[x] = etot;
}

void dfs(int x) {
	dep[x] = dep[fa[x]] + 1; size[x] = 1;
	for (int i = head[x]; i; i = next[i]) {
		fa[v[i]] = x;
		dfs(v[i]);
		size[x] += size[v[i]];
		if (size[v[i]] >= size[son[x]]) son[x] = v[i];
	}
}
void dfs(int x, int t) {
	top[x] = t; dfn[x] = ++xys; arcdfn[xys] = x;
	if (son[x]) dfs(son[x], t);
	for (int i = head[x]; i; i = next[i])
		if (v[i] != son[x]) dfs(v[i], v[i]);
}

struct Node {
	int lc, rc;
	LL sum, add;
	Node() : lc(0), rc(0), sum(0), add(0) {}
	
};
Node T[maxn << 7];
int root[maxn], tot;

inline void update(int o) {
	T[o].sum = (T[T[o].lc].sum + T[T[o].rc].sum) % mod;
}
inline void pushdown(int o, int l, int mid, int r) {
	if (T[o].add) {
		LL &d = T[o].add;
		T[++tot] = T[T[o].lc];
		T[o].lc = tot;
		T[++tot] = T[T[o].rc];
		T[o].rc = tot;
		T[T[o].lc].sum = (T[T[o].lc].sum + d * (s[mid] - s[l - 1] + mod) % mod) % mod;
		T[T[o].rc].sum = (T[T[o].rc].sum + d * (s[r] - s[mid] + mod) % mod) % mod;
		T[T[o].lc].add += d;
		T[T[o].rc].add += d;
		d = 0;
	}
}
void modify(int &o, int lb, int rb, int l, int r) {
	if (l > rb || r < lb) return;
	T[++tot] = T[o]; o = tot;
	if (l <= lb && r >= rb) {
		T[o].sum = (T[o].sum + s[rb] - s[lb - 1] + mod) % mod;
		++T[o].add;
		return;
	}
	int mid = (lb + rb) >> 1;
	pushdown(o, lb, mid, rb);
	modify(T[o].lc, lb, mid, l, r);
	modify(T[o].rc, mid + 1, rb, l, r);
	update(o);
}
LL query(int o, int lb, int rb, int l, int r) {
	if (!o || l > rb || r < lb) return 0;
	if (l <= lb && r >= rb) return T[o].sum;
	int mid = (lb + rb) >> 1;
	pushdown(o, lb, mid, rb);
	return (query(T[o].lc, lb, mid, l, r) + query(T[o].rc, mid + 1, rb, l, r)) % mod;
}

inline void add(int x, int i) {
	for (; x; x = fa[top[x]])
		modify(root[i], 1, n, dfn[top[x]], dfn[x]);
}
inline LL query(int x, int i) {
	LL ans = 0;
	for (; x; x = fa[top[x]])
		ans = (ans + query(root[i], 1, n, dfn[top[x]], dfn[x])) % mod;
	return ans;
}

int main() {
	read(n, q, K);
	for (int i = 2, f; i <= n; ++i)
		read(f), ae(f, i);
	dfs(1); dfs(1, 1);
	for (int i = 1; i <= n; ++i)
		a[i] = (qpow(dep[i], K) - qpow(dep[i] - 1, K) + mod) % mod;
	for (int i = 1; i <= n; ++i)
		s[i] = (s[i - 1] + a[arcdfn[i]]) % mod;
	for (int i = 1; i <= n; ++i) {
		root[i] = root[i - 1];
		add(i, i);
	}
	while (q--) {
		int x, y; read(x, y);
		writeln(query(y, x));
	}
	return 0;
}
```


---

## 作者：Great_Influence (赞：0)

和[这道题](https://www.luogu.org/problemnew/show/P4211)简直一模一样。

当 $k=1$ 时，问题为给关键点到根路径上每个点加上答案的差分值 $1$，然后询问前 $x$ 个点到根权值之和的和。这等价于给前 $x$ 个点到根的路径每个点加 $1$ ，然后询问查询点到根路径之和。

我们将询问离线，然后按照编号从小到大插入树中，每次给插入点到根节点加上和上一个点答案的差分值 $1$ ，然后询问询问点到根的路径权值和即可。

但是这次要求的是 $dep(lca)^k$ ，我们将差分值变成 $dep_i^k-(dep_i-1)^k$ 即可。这样修改就变成了链上加不同的固定值。仍然可以用树剖线段树实现。

复杂度 $O((n+q)\log^2 n)$ 。

代码:
```cpp
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<queue>
#include<iostream>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
	const uint32 Buffsize=1<<15,Output=1<<24;
	static char Ch[Buffsize],*S=Ch,*T=Ch;
	inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
	static char Out[Output],*nowps=Out;
	
	inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

	template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

void file()
{
#ifndef ONLINE_JUDGE
	FILE*DSD=freopen("water.in","r",stdin);
	FILE*CSC=freopen("water.out","w",stdout);
#endif
}

const int MAXN=5e4+7,mod=998244353;

static int n,Q,k,fa[MAXN];

vector<int>ed[MAXN];

static struct quer
{
	int x,y,id;

	bool operator<(const quer&a)const{return x<a.x;}
}q[MAXN];

inline void init()
{
	read(n),read(Q),read(k),k%=mod-1;
	Rep(i,2,n)read(fa[i]),ed[fa[i]].pb(i);
	Rep(i,1,Q)read(q[i].x),read(q[i].y),q[i].id=i;
	sort(q+1,q+Q+1);
}

static int dep[MAXN],son[MAXN],sz[MAXN],dfs_clock,dfn[MAXN],top[MAXN],ri[MAXN];

void dfs1(int u)
{
	dep[u]=dep[fa[u]]+1,sz[u]=1;
	for(int v:ed[u])
	{
		dfs1(v),sz[u]+=sz[v];
		if(sz[son[u]]<sz[v])son[u]=v;
	}
}

void dfs2(int u,int tp)
{
	ri[dfn[u]=++dfs_clock]=u,top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	else return;
	for(int v:ed[u])if(v^son[u])dfs2(v,v);
}

static int sm[MAXN];

inline int power(int u,int v)
{
	register int sm=1;
	for(;v;v>>=1,u=(ll)u*u%mod)if(v&1)
		sm=(ll)sm*u%mod;
	return sm;
}

inline int ad(int u,int v){return(u+=v)>=mod?u-mod:u;}

namespace Segment_Tree
{
	static int p[MAXN<<2],laz[MAXN<<2];

	inline void pushdown(int h,int l,int r)
	{
		if(laz[h])
		{
			int md=(l+r)>>1;
			p[h<<1]=(p[h<<1]+(ll)laz[h]*(sm[md]-sm[l-1]+mod))%mod;
			p[h<<1|1]=(p[h<<1|1]+(ll)laz[h]*(sm[r]-sm[md]+mod))%mod;
			laz[h<<1]+=laz[h],laz[h<<1|1]+=laz[h];
			laz[h]=0;
		}
	}

	void mf(int h,int l,int r,int x,int y)
	{
		if(l>=x&&r<=y)
		{
			p[h]=((ll)p[h]+sm[r]-sm[l-1]+mod)%mod;
			++laz[h];
			return;
		}
		int md=(l+r)>>1;pushdown(h,l,r);
		if(x<=md)mf(h<<1,l,md,x,y);
		if(y>md)mf(h<<1|1,md+1,r,x,y);
		p[h]=ad(p[h<<1],p[h<<1|1]);
	}

	int qr(int h,int l,int r,int x,int y)
	{
		if(l>=x&&r<=y)return p[h];
		int md=(l+r)>>1,s=0;pushdown(h,l,r);
		if(x<=md)s=qr(h<<1,l,md,x,y);
		if(y>md)s=ad(s,qr(h<<1|1,md+1,r,x,y));
		return s;
	}
}
using Segment_Tree::mf;
using Segment_Tree::qr;

inline void change(int u)
{
	while(u)
	{
		mf(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
}

inline int query(int u)
{
	int sm=0;
	while(u)
	{
		sm=ad(sm,qr(1,1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	return sm;
}

static int ans[MAXN];

inline void solve()
{
	dfs1(1),dfs2(1,1);
	Rep(i,1,n)sm[i]=
((ll)sm[i-1]+power(dep[ri[i]],k)-power(dep[ri[i]]-1,k)+mod)%mod;
	int cr=1;
	Rep(i,1,Q)
	{
		while(cr<=q[i].x)change(cr++);
		ans[q[i].id]=query(q[i].y);
	}
	Rep(i,1,Q)write(ans[i]);
	flush();
}

int main()
{
	file();
	init();
	solve();
	return 0;
}
```

---

## 作者：Owen_codeisking (赞：0)

$GXOI/GZOI2019$ 居然出原题？？？

[原题传送门](https://www.luogu.org/problemnew/show/P4211)

### 树上差分 + 树剖 + 线段树

我们把每个点的权值差分成 $dep_i^k-(dep_i-1)^k$，然后就愉快区间加+区间和了。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=50000+10;
const int mod=998244353;
int n,m,k,a[maxn];ll sumE[maxn],sum[maxn<<2],add[maxn<<2],ans[maxn];
int top[maxn],dep[maxn],siz[maxn],son[maxn],fa[maxn],id[maxn],mp[maxn],tim;
int head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
vector<pair<int,int> > q[maxn];

inline int read()
{
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

void print(ll x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

inline ll fpow(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1) ret=ret*a%mod;
	return ret;
}

inline void addedge(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

void dfs1(int x,int f)
{
	siz[x]=1;fa[x]=f;dep[x]=dep[f]+1;
	int maxson=-1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f) continue;
		dfs1(y,x);siz[x]+=siz[y];
		if(siz[y]>maxson) maxson=siz[y],son[x]=y;
	}
}

void dfs2(int x,int topf)
{
	id[x]=++tim;mp[tim]=x;top[x]=topf;
	if(son[x]) dfs2(son[x],topf);
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}

#define lson (rt<<1)
#define rson (rt<<1|1)

inline void pushup(int rt)
{
	sum[rt]=(sum[lson]+sum[rson])%mod;
}

inline void pushdown(int rt,int l,int r)
{
	if(add[rt])
	{
		int mid=(l+r)>>1;
		(sum[lson]+=add[rt]*(sumE[mid]-sumE[l-1]))%=mod;
		(sum[rson]+=add[rt]*(sumE[r]-sumE[mid]))%=mod;
		add[lson]+=add[rt];add[rson]+=add[rt];add[rt]=0;
	}
}

void update(int L,int R,int l,int r,int rt)
{
	if(L <= l && r <= R)
	{
		(sum[rt]+=sumE[r]-sumE[l-1])%=mod;
		add[rt]++;
		return ;
	}
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	if(L <= mid) update(L,R,l,mid,lson);
	if(R > mid) update(L,R,mid+1,r,rson);
	pushup(rt);
}

ll query(int L,int R,int l,int r,int rt)
{
	if(L <= l && r <= R) return sum[rt];
	pushdown(rt,l,r);
	int mid=(l+r)>>1;ll ans=0;
	if(L <= mid) (ans+=query(L,R,l,mid,lson))%=mod;
	if(R > mid) (ans+=query(L,R,mid+1,r,rson))%=mod;
	return ans;
}

inline void modify(int x)
{
	for(;x;x=fa[top[x]]) update(id[top[x]],id[x],1,n,1);
}

inline ll ask(int x)
{
	ll ans=0;
	for(;x;x=fa[top[x]]) (ans+=query(id[top[x]],id[x],1,n,1))%=mod;
	return ans;
}

int main()
{
	n=read(),m=read(),k=read();
	for(int i=2;i<=n;i++) fa[i]=read(),addedge(fa[i],i),addedge(i,fa[i]);
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=n;i++) a[i]=(fpow(dep[i],k)-fpow(dep[i]-1,k))%mod;
	for(int i=1;i<=n;i++) sumE[i]=(sumE[i-1]+a[mp[i]])%mod;
	int x,y;
	for(int i=1;i<=m;i++) x=read(),y=read(),q[x].push_back(make_pair(y,i));
	for(int i=1;i<=n;i++)
	{
		modify(i);
		for(int j=0,k=q[i].size();j<k;j++) ans[q[i][j].second]=ask(q[i][j].first);
	}
	for(int i=1;i<=m;i++) print((ans[i]+mod)%mod),putchar('\n');
	return 0;
}
```

---

