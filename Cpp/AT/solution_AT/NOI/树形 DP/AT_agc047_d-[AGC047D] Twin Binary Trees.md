# [AGC047D] Twin Binary Trees

## 题目描述

受到电视剧《怪奇物语》的启发，熊的 Rimac 决定在现实世界和镜像世界之间来回穿梭。

有两棵高度为 $H$ 的完全二叉树，每个顶点按照标准方式编号，从 $1$ 到 $2^H-1$。也就是说，根节点编号为 $1$，编号为 $x$ 的节点的子节点编号分别为 $2 \cdot x$ 和 $2 \cdot x + 1$。

设一棵树的叶子数为 $L$，即 $L = 2^{H-1}$。

给定 $1, \ldots, L$ 的一个排列 $P_1, P_2, \ldots, P_L$。这表示两棵树之间有 $L$ 条*特殊边*。即，第一棵树中编号为 $L+i-1$ 的顶点与第二棵树中编号为 $L+P_i-1$ 的顶点通过一条特殊边相连。

![输入样例 1 的图示](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc047_d/4c625be33a7fdc66e88ab8ed10969ab25c77b603.png)

*输入样例 1 的图示。$P = (2, 3, 1, 4)$，绿色的边为特殊边*

定义一个环的*积*为其包含的所有顶点编号的乘积。请你求出**恰好包含两条特殊边的**所有简单环的积之和，并对 $10^9+7$ 取模。

这里，简单环指的是长度不少于 $3$，且没有重复顶点和边的环。

## 说明/提示

### 限制

- $2 \leq H \leq 18$
- $1 \leq P_i \leq L$（其中 $L = 2^{H-1}$）
- $P_i \neq P_j$（即该数列是 $1, \ldots, L$ 的一个排列）

### 样例解释 1

下图展示了需要考虑的两个环（实际上还有其他）。第一个环的积为 $2 \cdot 5 \cdot 6 \cdot 3 \cdot 1 \cdot 2 \cdot 5 \cdot 4 = 7200$，第二个环的积为 $1 \cdot 3 \cdot 7 \cdot 7 \cdot 3 \cdot 1 \cdot 2 \cdot 5 \cdot 4 \cdot 2 = 35280$。第三个环不满足恰好有两条特殊边，因此不计入答案。 ![three cycles](https://img.atcoder.jp/agc047/3_trees_font.png)

### 样例解释 2

图中唯一的环确实包含两条特殊边，其顶点编号的积为 $1 \cdot 3 \cdot 3 \cdot 1 \cdot 2 \cdot 2 = 36$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 3 1 4```

### 输出

```
121788```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
36```

## 样例 #3

### 输入

```
5
6 14 15 7 12 16 5 4 11 9 3 10 8 2 13 1```

### 输出

```
10199246```

# 题解

## 作者：JWRuixi (赞：3)

~~根本不会 FFT……~~

- 题意

给定两棵完全相同的 $n$ 层完全二叉树，其中第 $i$ 层编号依次为 $2^{i-1},2^{i-1}+1,\dots, 2^i-1$。

给定一个 $1$ 到 $2^{n-1}$ 的排列 $p$，将第一棵树的第 $i$ 个叶子节点连向第二棵树的第 $p_i$ 个叶子节点。

求此图中合法的环的权值和。

称一个环合法当且仅当它恰好经过 $2$ 条非树边，定义一个环的权值为环上点的编号乘积。

答案对 $10^9 + 7$ 取模。

$2 \le n \le 18$。

- 分析

考虑对于一个合法的环，因为其恰好经过两条非树边，所以考虑如果从 $u$ 的左子树中的一个叶子节点出发，一定会从其右子树中一个叶子节点返回。

所以可以将整个过程分为两个部分，枚举 $u$：
1. 从 $u$ 左子树出发，统计对于第二棵树上以每个点 $u^\prime$ 为结尾路径的权值，记作 $f_{u^\prime}$；
2. 从 $u$ 右子树出发，统计以每个点 $u^\prime$ 结尾的环的贡献和，具体实现细节可以对于 $u^\prime$，$ans \leftarrow f_{u^\prime}\times now \times fa_u$，就不会算重了！

时间复杂度 $O(n^22^n)$。

- code

```cpp
#include <bits/stdc++.h>
#define LL long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(20), maxm(1 << 19), mod(1e9 + 7);
int n, p[maxm], f[maxm], ans;

#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)

void dfs1 (int u, int now, int opt) {
	if (u == 1) return;
	now = (LL)now * u % mod;
	if (!opt)
		f[u] = (LL)(f[u] + now) % mod;
	else 
		ans = (ans + (LL)f[u ^ 1] * now % mod * (u >> 1) % mod) % mod;
	dfs1(u >> 1, now, opt);
}

void dfs2 (int u, int now, int opt) {
	now = (LL)now * u % mod;
	if (u >= (1 << (n - 1))) {
		dfs1(p[u], now, opt);
		return;
	}
	dfs2(ls(u), now, opt);
	dfs2(rs(u), now, opt);
}

void clr (int u) {
	if (!f[u] || u == 1) return;
	f[u] = 0;
	clr(u >> 1);
}

void clear (int u) {
	if (u >= (1 << (n - 1))) {
		clr(p[u]);
		return;
	}
	clear(ls(u));
	clear(rs(u));
}

int main () {
	n = read();
	for (int i = 0; i < (1 << (n - 1)); i++) p[i + (1 << (n - 1))] = (1 << (n - 1)) + read() - 1;
	for (int i = 1; i < (1 << (n - 1)); i++) {
		dfs2(ls(i), i, 0);
		dfs2(rs(i), 1, 1);//初值设为 1，避免算重 i。
		clear(i);
	}
	write(ans);
}
```

---

## 作者：forest114514 (赞：1)

为啥一定要线段树合并？

枚举环上两个在第一个树的叶子 $i,j$，考虑他们的 LCA $k$，注意是满二叉树可以每个 $k$ 的子树都做一遍，复杂度是 $\sum dep=O(n\log n)$ 的。

每次枚举一个非叶子 $k$ 的子树内的叶子，在第二颗树上建虚树，我们把 $k$ 两边的子树分别染上不同颜色看做在不同集合 $S_1,S_2$ 中，我们对每个叶子的权值是在第二个树中到根的点权积乘上第一个树中到枚举点 $k$ 的点权积，对第二个树中作为 LCA 的非叶子节点权值就是到根的点权积的平方除去自己的点权，这样方便容斥计算一条链的点权积因为 LCA 也算了一次，发现我们此时需要求的大概是 $\sum\limits_{i\in S_1}\sum\limits_{j\in S_2}val_i\times val_j\times val2_{LCA(i,j)}$，可以在虚树上 dfs 的时候枚举一个点，统计子树内两个不同集合的点权和就可以合并贡献了。因为是枚举子树，所以可以归并两个子树按 dfs 序排序的顺序+线性建虚树做到 $O(n\log n)$。

注意不一定是枚举 LCA，可以变成路径上任意一个点，对于任意树可以直接边分治，类似暴力写挂，对分治的点集的叶子对应的在第二颗树叶子建虚树，然后 dfs 统计贡献，因为点分树是树高不超过 $O(\log n)$ 的二叉树所以复杂度同样是单 $\log$ 的。

时间复杂度 $O(n\log n)$，只是常数确实有点大就是了。

---

## 作者：Yansuan_HCl (赞：0)

来个不牛做法。

记 $h(i)$ 为点 $i$ 的深度，1 的深度为 $1$。

考虑根号分治：设阈值 $B$，对于点对 $(i,j)$，若 $\max(h(\text{LCA}(i,j)), h(\text{LCA}(p_i, p_j))) > n - B$，则可以直接枚举点对，复杂度 $O(2^{2B+n-B})$。否则点对的 LCA 只有 $O(2^{2n-2B})$ 种，对每个 $(i,p_i)$ 分别枚举二进制前缀，贡献到 LCA pair 即可；预处理复杂度 $O(n^22^n)$，枚举复杂度 $O(2^{2n-2B})$。

取 $B=\frac n 3$ 时，时空复杂度 $O(2^{\frac {4n}{3}})$。

[代码](https://atcoder.jp/contests/agc047/submissions/65343312)。

---

## 作者：lzqy_ (赞：0)

重铸 $3\log$ 荣光！

平凡地，考虑在 $T_1$ 中枚举起点 $x$，在 $T_1,T_2$ 中枚举 $lca\rightarrow (y_1,y_2)$，此时问题转化为 $T_1$ 的一个叶节点区间排到 $T2$ 的一个叶节点区间后剩余节点的权值和（权值是两个叶节点到根的权值乘积），线段树合并即可。

设 $N=2^n$，时间复杂度 $O(N\log^3N)$。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define il inline
using namespace std;
const int maxn=300010;
const int MAXN=maxn*30;
const int mod=1e9+7;
il int read(){
    int x=0;
    char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;
}
il void mul(int &x,int y){x=1ll*x*y%mod;}
il void ad(int &x,int y){if((x+=y)>=mod)x-=mod;}
il void de(int &x,int y){if((x-=y)<0)x+=mod;}
il int fpow(int n,int m,int x=1){
    for(;m;m>>=1,n=1ll*n*n%mod)
        if(m&1) x=1ll*x*n%mod;
    return x;
}
il int Inv(int x){return fpow(x,mod-2);}
int ls[MAXN],rs[MAXN],d[MAXN],rt[maxn],cnt;
int n,N,p[maxn],ipre[maxn],pre[maxn],L[maxn],R[maxn];
void Add(int &i,int l,int r,int x,int k){
    if(!i) i=++cnt;
    if(l==r){
        ad(d[i],k);
        return ;
    }int mid=l+r>>1;
    if(mid>=x) Add(ls[i],l,mid,x,k);
    else Add(rs[i],mid+1,r,x,k); 
    d[i]=(d[ls[i]]+d[rs[i]])%mod;
}
int merge(int a,int b,int l,int r){
    if(!a||!b) return a|b;
    if(l==r){
        d[++cnt]=(d[a]+d[b])%mod;
        return cnt;
    }int mid=l+r>>1,t=++cnt;
    ls[t]=merge(ls[a],ls[b],l,mid);
    rs[t]=merge(rs[a],rs[b],mid+1,r);
    d[t]=(d[ls[t]]+d[rs[t]])%mod;
    return t;
}
int Que(int i,int l,int r,int L,int R){
    if(!i||l>R||r<L) return 0;
    if(l>=L&&r<=R) return d[i];
    int mid=l+r>>1;
    return (Que(ls[i],l,mid,L,R)+Que(rs[i],mid+1,r,L,R))%mod;
}
void init(int x,int d){
    pre[x]=1ll*pre[x>>1]*x%mod;
    if(d!=n) init(x<<1,d+1),init(x<<1|1,d+1);
}
void dfs(int x,int d){
    if(d!=n){
        dfs(x<<1,d+1),dfs(x<<1|1,d+1);
        rt[x]=merge(rt[x],rt[x<<1],1,N);
        rt[x]=merge(rt[x],rt[x<<1|1],1,N);
        L[x]=L[x<<1],R[x]=R[x<<1|1];
        return ;
    }
    Add(rt[x],1,N,p[x-(1<<n-1)+1],
    1ll*pre[x]*pre[p[x-(1<<n-1)+1]+(1<<n-1)-1]%mod);
    L[x]=R[x]=x-(1<<n-1)+1;
}
bool In(int x,int l,int r){return x>=l&&x<=r;}
int main(){
    n=read(),N=(1<<n-1);
    for(int i=1;i<=N;i++) p[i]=read();
    pre[0]=1,init(1,1),dfs(1,1);
    int ans=0;
    for(int i=0;i<(1<<n);i++)
        ipre[i]=Inv(pre[i]);
    for(int i=1;i<=N;i++)
        for(int j=(i+(1<<n-1)-1)/2,jj;j;j/=2)
            for(int k=(p[i]+(1<<n-1)-1)/2,kk;k;k/=2){
                In(i,L[j<<1],R[j<<1])?(jj=j<<1|1):(jj=j<<1);
                In(p[i],L[k<<1],R[k<<1])?(kk=k<<1|1):(kk=k<<1);
                int tmp=Que(rt[jj],1,N,L[kk],R[kk]);
                if(!tmp) continue;
                mul(tmp,pre[i+(1<<n-1)-1]);
                mul(tmp,pre[p[i]+(1<<n-1)-1]);
                mul(tmp,ipre[j]),mul(tmp,ipre[j>>1]);
                mul(tmp,ipre[k]),mul(tmp,ipre[k>>1]);
                ad(ans,tmp);
            }
    mul(ans,Inv(2));
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：zhiyin123 (赞：0)

这是一个**常数较大**的 $O(n\log ^ 2 n)$ 做法。（其中 $n$ 为树的**节点个数**）

# 一

不妨称连接两棵树的叶子节点的**边**为**关键边**。

这道题感觉上就是**数据结构题**，做法可能是：枚举每一条**关键边**，然后在**数据结构**中查询**这条边**和**另外的边**组成的环对答案的贡献。

不妨用**有序二元组** $(i, P_i)$ 表示第 $i$ 条**关键边**，那么，就可以将所有的**关键边**看作**二维平面上的点** $(i,P_i)$。

设**二维平面上的点** $(x,y)$ 的**权值**为 $w[(x,y)]$。然后，$\forall i$，我们令 $w[(i,P_i)]$ 为**树上**：节点 $i$ 到根的路径权值**乘以**节点 $P_i$ 到根的路径权值。（其中，一条路径的权值定义为：路径上点的编号乘积）

然后，我们用**二维数据结构**维护二维平面上所有点的**点权**。那么，关键边 $(i,P_i)$ 与其他关键边**组成的环**对答案的贡献是多少呢？不妨记平面上所有点的**点权和**为 $sum$，那么贡献是 $w[(i,P_i)]\times sum$ 吗？发现不是，因为有的点权被多余的计入了贡献。

所以，考虑用**修改操作**修正这个做法。发现一个叶子 $i$ 和其他叶子的本质不同的**最近公共祖先**只有 $O(\log n)$ 个，所以可以使用类似于**树上差分**的方法对平面上的点进行**区间除**的操作，每次操作都是计算出一个范围 $[l,r]$，然后对所有满足 $l\leq x\leq r$（也有可能是 $l\leq y\leq r$）的点 $(x,y)$ 的权值**除以**一个数。

修改操作要进行 $O(n\log n)$ 次，一次操作复杂度为 $O(\log ^ 2 n)$ 或者 $O(\sqrt n)$（树套树或分块），所以总复杂度为 $O(n\log ^ 3 n)$ 或者 $O(n\sqrt n\log n)$。不太能过。

# 二

考虑优化这个过程。

首先，我们希望不使用大常数的二维数据结构，因为平面上点的**纵坐标**互不相同，所以考虑直接试图用**一维数据结构**（线段树）维护纵轴。

一维数据结构会带来一个麻烦，就是**横轴的区间除**无法进行。不过，我们可以确定**枚举关键边的顺序**，以**第一关键字升序**枚举，这样就可以用树上 dfs 实现枚举，对于横轴的区间除可以被拆成总共 $O(n\log n)$ 次**单点除**，每次除的复杂度维 $O(\log n)$，总复杂度就变成了 $O(n\log ^ 2 n)$，可以通过。

# 代码

不知道为什么常数比想象中的大，最慢的点要跑大约 $2.3\operatorname{s}$。

```cpp
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
using std::cerr; using std::endl; using std::setw;
using std::cin; using std::cout;
using ll = long long;
constexpr ll MO = 1e9 + 7;
ll mo(ll x) {return x >= MO ? x - MO : x;}
void n_add(ll &x, ll y) {x = mo(x + y); return ;}
constexpr int MAXH = 18, MAXN = 131072, MAXV = MAXN * 2 + 5;
ll inv[MAXV * 2 + 5] = {};
int H = 0, N = 0, P[MAXN + 5] = {};
namespace seg {
    constexpr int NSI = MAXN * 2 + 5;
    struct no_t {
        ll sum, tim;
        int ls, rs;
        no_t() : sum(0), tim(1), ls(0), rs(0) {}
        void dotim(ll t) {
            sum = sum * t % MO;
            tim = tim * t % MO;
            return ;
        } 
    } no[NSI + 5] {};
#define n no[it]
    int root = 0, ncnt = 0;
    void build(int &it = root, int l = 1, int r = N) {
        it = ++ncnt;
        if (l == r) return ;
        int mid = (l + r) >> 1;
        build(n.ls, l, mid);
        build(n.rs, mid + 1, r);
        return ;
    }
    void pushup(int it) {
        n.sum = mo(no[n.ls].sum + no[n.rs].sum);
        return ;
    }
    void pushdown(int it) {
        if (n.tim == 1) return ;
        no[n.ls].dotim(n.tim);
        no[n.rs].dotim(n.tim);
        n.tim = 1;
        return ;
    }
    void prod(int ql, int qr, ll val, int it = root, int l = 1, int r = N) {
        if (ql <= l && r <= qr) {
            n.dotim(val);
            return ;
        }
        int mid = (l + r) >> 1;
        pushdown(it);
        if (ql <= mid) prod(ql, qr, val, n.ls, l, mid);
        if (mid < qr) prod(ql, qr, val, n.rs, mid + 1, r);
        pushup(it);
        return ;
    }
    void set(int pos, ll val, int it = root, int l = 1, int r = N) {
        if (l == r) {n.sum = val; return ;}
        int mid = (l + r) >> 1;
        pushdown(it);
        if (pos <= mid) set(pos, val, n.ls, l, mid);
        else set(pos, val, n.rs, mid + 1, r);
        pushup(it);
        return ; 
    }
    ll getsum() {return no[root].sum;}
#undef n
}
void bfprod(int l, int r, ll val) {
    for (int i = l; i <= r; i++) seg::prod(P[i], P[i], val);
    return ;
}
struct no_t {int l, r, h;} no[MAXN * 2 + 5] {};
int It[MAXN + 5] = {};
#define lson (it << 1)
#define rson ((it << 1) | 1)
void build(int it, int h) {
    static int id = 0;
    if (h == H) {
        ++id;
        It[id] = it;
        no[it] = {id, id, h};
        return ;
    }
    build(lson, h + 1);
    build(rson, h + 1);
    no[it] = {no[lson].l, no[rson].r, h};
    return ;
}
ll getprod(ll it) {
    ll y = 1; while(it > 0) {y = y * it % MO; it >>= 1;}
    return y;
}
void dowork(ll it) {
    while(it > 0) {
        if ((it >> 1) > 0) seg::prod(no[it].l, no[it].r, inv[it >> 1]);
        seg::prod(no[it].l, no[it].r, inv[it]);
        it >>= 1;
    }
    return ;
}
void undowork(ll it) {
    while(it > 0) {
        if ((it >> 1) > 0) seg::prod(no[it].l, no[it].r, it >> 1);
        seg::prod(no[it].l, no[it].r, it);
        it >>= 1;
    }
    return ;
}
ll ans = 0;
void dfs(int it, ll prod, ll iprod) {
    prod = prod * it % MO; iprod = iprod * inv[it] % MO;
    bfprod(no[it].l, no[it].r, inv[it]);
    if (no[it].h == H) {
        ll plink = getprod(It[P[no[it].l]]);
        dowork(It[P[no[it].l]]);
        ll rec = seg::getsum() * prod % MO * plink % MO;
        n_add(ans, rec);
        undowork(It[P[no[it].l]]);
        ll tval = plink * iprod % MO * it % MO;
        seg::set(P[no[it].l], tval);
    } else {
        bfprod(no[lson].l, no[lson].r, inv[it]);
        dfs(lson, prod, iprod);
        bfprod(no[lson].l, no[lson].r, it);
        bfprod(no[rson].l, no[rson].r, inv[it]);
        dfs(rson, prod, iprod);
        bfprod(no[rson].l, no[rson].r, it);
    }
    bfprod(no[it].l, no[it].r, it);
    return ;
}
#undef lson
#undef rson
int main() {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    inv[1] = 1ll; for (ll i = 2; i <= MAXV; i++) inv[i] = MO - MO / i * inv[MO % i] % MO;
    cin >> H; N = 1 << (H - 1);
    for (int i = 1; i <= N; i++) cin >> P[i];
    build(1, 1);
    seg::build();
    dfs(1, 1ll, 1ll);
    cout << ans << '\n';
    return 0;
}
```

---

