# Trees and XOR Queries Again

## 题目描述

You are given a tree consisting of $ n $ vertices. There is an integer written on each vertex; the $ i $ -th vertex has integer $ a_i $ written on it.

You have to process $ q $ queries. The $ i $ -th query consists of three integers $ x_i $ , $ y_i $ and $ k_i $ . For this query, you have to answer if it is possible to choose a set of vertices $ v_1, v_2, \dots, v_m $ (possibly empty) such that:

- every vertex $ v_j $ is on the simple path between $ x_i $ and $ y_i $ (endpoints can be used as well);
- $ a_{v_1} \oplus a_{v_2} \oplus \dots \oplus a_{v_m} = k_i $ , where $ \oplus $ denotes the bitwise XOR operator.

## 样例 #1

### 输入

```
4
0 1 2 10
2 1
3 2
4 2
8
3 3 0
3 4 1
3 4 7
1 3 1
1 3 2
1 3 10
1 4 10
1 4 11```

### 输出

```
YES
YES
NO
YES
YES
NO
YES
YES```

# 题解

## 作者：EuphoricStar (赞：12)

如果我们能把 $x \to y$ 路径上的所有点权插入到线性基，那么可以 $O(\log V)$ 查询。

但是因为线性基合并只能 $O(\log^2 V)$（把一个线性基的所有元素插入到另一个），所以只能倍增做 $O((n + q) \log n \log^2 V)$，过不了。

考虑 $O(n \log V)$ 预处理出每个点到根的所有点权的线性基 $f_u$，那么对于一个询问，把 $f_x$ 和 $f_y$ 合并，再抠掉 $\text{lca}(x, y)$ 以上部分的点权即可。

但是线性基不支持删除，考虑**贪心**地在不影响线性基能组成的数的前提下，每个 $f_u$ 中保留**深度最大**的点的点权（就是 [CF1100F Ivan and Burgers 第一篇题解](https://www.luogu.com.cn/problem/solution/CF1100F)）。查询只考虑深度 $\ge dep_{\text{lca}(x, y)}$ 的元素即可。

于是时间复杂度降至 $O((n + q \log V) \log V)$（瓶颈在合并线性基），可过。

[code](https://codeforces.com/contest/1902/submission/235856193)

---

## 作者：Zi_Gao (赞：2)

## 前言

本题是简单的、一眼的、普通的、显然的。

## 正文

### 0x00 分析题目

> 给定一颗带点权无根树，每次询问给定两个点 $u,v$ 和参数 $k$，回答是否有一个 $u\leftarrow v$ 简单路径的点权子集其异或和是 $k$。
> $n,q\leq 2\times 10^5$ 时间限制为 $6.5$ 秒。

可以肯定的是这个题需要线性基，以及线性基合并等知识，不会的推荐[线性基学习笔记 | Menci's OI Blog](https://oi.men.ci/linear-basis-notes/)。下文默认 $n,q$ 同阶。

### 0x01 树上倍增 $\mathcal{O}\left(n\log^3{n}\right)$

#### 做法

首先考虑到一个显然的做法，树上倍增，对于每个 $u$ 处理出 $B_{u,k}$ 表示 $u$ 到其 $2^k$ 级祖先这条链的线性基，和普通树上倍增一样只不过合并两个 $2^{k-1}$ 的信息时用线性基合并，则预处理时间复杂度 $\mathcal{O}\left(n\log^3{n}\right)$。

询问时，$u,v$ 不断向上倍增跳，直到其 $lca$ 的位置，这样一共需要合并 $\mathcal{O}\left(\log{n}\right)$ 个线性基，单次询问时间复杂度 $\mathcal{O}\left(\log^3{n}\right)$。

#### 代码实现

实测使用一定的常数优化可以轻松通过：

1. 线性基插入一个数 $x$ 时从 $\log_2 x$ 位开始枚举，每次插入后重新取 $\log_2 x$ 寻找下一位。
2. 树上倍增时从 $\log dep$ 开始倍增。
3. 取 $\log_2 x$ 使用 `31^__builtin_clz(x)` 计算最快。

[AC CODE](https://codeforces.com/problemset/submission/1902/235700039)，最大点跑了 $6114 ms$。


### 0x02 点分治做法 $\mathcal{O}\left(n\log^2{n}\right)$

#### 做法

观察发现树上倍增做法之所以慢是应为我们钦定了两个点在他们的 $lca$ 处相遇然后合并线性基，所以需要预处理和查询很多东西。但是对于这个这个题他是无根树，不需要一定在 $lca$ 处才能算。这启发我们使用点分治来处理树上询问。

具体的，对于每次点分治，处理跨越当前子树重心的所有询问。对于每个子树的点 $u$ 处理出其到重心链上的线性基，这一部分不需要线性基合并，只需要直接继承他父亲的线性基然后加入 $u$ 的点权即可。处理查询时合并以 $u$ 到重心的线性基和 $v$ 到重心的线性基即可。单次查询时间复杂度 $\mathcal{O}\left(\log^2{n}\right)$，点分治的时间复杂度 $\mathcal{O}\left(n\log^2{n}\right)$。

思考，点分治的好处是每次查询只需要合并两个线性基，并且预处理不需要合并线性基所以可以得到更优的时间复杂度。

#### 代码实现

加上前面的优化甚至可以跑进一秒，[AC CODE](https://codeforces.com/problemset/submission/1902/235707047)。


## 总结

本题利用了点分治对询问优秀的拆分方式解决了本题。

---

## 作者：蒟蒻君HJT (赞：2)

点分治。

每次取出分治重心 $r$，回答所有经过分治重心的询问。具体来说，从分治重心开始 dfs，求出以 $r$ 为根的每个点 $x$ 的前缀线性基 $ca_x$：从父节点继承过来并插入一个 $a_x$。这里复杂度是 $\Theta(n\log n\log A)$。

对于经过分治重心的询问 $(x,y,k)$，先合并 $ca_x$ 和 $ca_y$，再 check $k$ 是否在合并出来的线性基的线性空间里即可。这里复杂度 $\Theta(q\log^2A)$ 因为每个询问只会产生一次合并。

实现上在分治的递归中需要传入完全位于当前分治连通块内部的询问。判断是否过 $r$ 可以用 $x$ 到 $y$ 的距离 $dis(x,y)$ 是否等于 $dis(x,z)+dis(z,y)$。

[for reference only.](https://codeforces.com/contest/1902/submission/235647986)

---

## 作者：Iniaugoty (赞：2)

大水板子题，建议评蓝或紫。~~可惜我未知原因被 C 卡了 1h 都没看这题，差点 AK 了唉。~~

前置知识：[异或线性基](/problem/P3812)。

如何判断一个序列里选一些数，是否能异或出 $k$ ？考虑往线性基里插一个数 $k$ 的过程，如果不能成功插入，意味着有一些数的异或和为 $k$。那么模拟一下这个过程即可。

问题转移到了，对每次询问，如何在 $\log$ 或者 $\log ^ 2$ 的时间内求出 $x, y$ 路径上的所有元素的线性基。

~~容易想到树剖，但是我不知道怎么搞。~~

还容易想到倍增，预处理出每个结点往上跳 $2 ^ i$ 层结点的线性基。询问时同树剖做法，也是暴力跳，过程中合并线性基，预处理和查询都是 $\mathcal O (\log ^ 2 V \log n)$ 的，不知道能不能过。

倍增有一个经典的优化技巧，想想 ST 表是怎么查最值的？将一个区间分成两个可能有重合，但是长度都是 $2 ^ i$ 的区间，将两个区间的信息合并。能这么搞因为最大值是个 RMQ 问题，重复的数不会造成影响。线性基也是符合这个性质的，重复插同一个数并不会造成什么影响。

那么把 ST 表的这种方式套到树上。这样只用合并 $\mathcal O (1)$ 而非 $\mathcal O (\log n)$ 次线性基，查询复杂度降到 $\mathcal O (\log ^ 2 V)$。

算上预处理，总时间复杂度是 $\mathcal O ((n \log n + q)\log  ^ 2 V)$。常数小卡不满，加上 CF 神机，是可以过的。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define dF(i, a, b) for(int i = a; i >= (b); --i)

using namespace std;
typedef long long LL;
const int N = 2e5 + 5;
const int K = 20;

int n, q, a[N];
vector<int> e[N];
void Addedge(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
    return ;
}

void Insert(int* c, int x) {
	dF(i, K, 0) if (x & 1 << i)
		if (!c[i]) { c[i] = x; break; }
		else x ^= c[i];
	return ;
}
void Merge(int* c1, int* c2) {
    dF(i, K, 0) if (c2[i]) Insert(c1, c2[i]);
    return ;
}
bool Query(int* c, int k) {
    dF(i, K, 0) if (k & 1 << i)
		if (!c[i]) return 0;
		else k ^= c[i];
    return !k;
}

int dep[N], f[N][18];
int c[N][18][K + 1];
void Dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    Insert(c[u][0], a[u]);
    for (int i = 1; 1 << i <= dep[u]; ++i)
        f[u][i] = f[f[u][i - 1]][i - 1],
        Merge(c[u][i], c[u][i - 1]),
        Merge(c[u][i], c[f[u][i - 1]][i - 1]);
    for (auto v : e[u])
        if (v != fa)
            Dfs(v, u);
    return ;
}

int Lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    dF(i, 17, 0)
        if (dep[f[u][i]] >= dep[v])
            u = f[u][i];
    if (u == v) return u;
    dF(i, 17, 0)
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}
int fa(int u, int k) {
    dF(i, 17, 0)
        if (k & (1 << i))
            u = f[u][i];
    return u;
}
bool Query(int u, int v, int w) {
    int res[K + 1];
    F(i, 0, K) res[i] = 0;
    int l = Lca(u, v);
    Merge(res, c[l][0]);
    int k = log2(dep[u] - dep[l] + 1);
    Merge(res, c[u][k]);
    Merge(res, c[fa(u, (dep[u] - dep[l] - (1 << k)))][k]);
    k = log2(dep[v] - dep[l] + 1);
    Merge(res, c[v][k]);
    Merge(res, c[fa(v, (dep[v] - dep[l] - (1 << k)))][k]);
    return Query(res, w);
}

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    cin >> n;
    F(i, 1, n) cin >> a[i];
    F(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        Addedge(u, v);
    }
    Dfs(1, 0);
    cin >> q;
    while (q--) {
        int x, y, k; cin >> x >> y >> k;
        if (Query(x, y, k)) cout << "Yes\n";
        else cout << "No\n";
	}
	return 0;
}
```

---

## 作者：arrow_king (赞：1)

给定一棵树，点有点权 $a_i$，多次询问，每次给定一条路径 $x\rightarrow y$ 和一个数 $k$，问能不能在路径上选择若干个点使得它们点权的异或和为 $k$。$n,q\le200000$。

# 前缀线性基

与这个题很类似的题是 [CF1100F](https://codeforces.com/problemset/problem/1100/F)，本题只是将这个题换到了树上查询。

线性基只能 $O(\log^2 V)$ 合并，因此如果要暴力合并只能树链剖分，单次查询复杂度高达 $O(\log n\log^2 V)$，无法通过，考虑使用线性基差分。

我们对于每个点处理出它到根这条路径的线性基 $b_i$，那么 $u\rightarrow v$ 这条路径上的线性基就是 $b_u,b_v$ 的并除去根到 $\operatorname{lca}(u,v)$ 的值。仿照 1100F 的套路，对于每个线性基额外维护 $dep_i$ 表示对第 $i$ 位产生影响的点所在的深度。我们需要查询 $b_u,b_v$ 的并中 $dep_i\ge dep_{\operatorname{lca}(u,v)}$ 的 $i$ 位置，所以我们需要维护产生影响中最大的 $dep$。

考虑插入一个数 $x$，如果它对 $i$ 位置产生了影响，则比较它的深度 $d$ 和 $dep_i$ 的关系，如果 $d\le dep_i$ 则无影响，异或后继续向下；否则我们需要让 $d$ 代替原来的值成为新的 $dep_i$，同时更新新的 $bas_i$。

插入一个数的复杂度保持不变，因此复杂度优化为 $O(n\log n+q\log^2 V)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define L 20
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
struct Lbase {
	int lbas[L+5],dep[L+5];
	Lbase operator =(const Lbase b) {for(int i=0;i<=L;i++) lbas[i]=b.lbas[i],dep[i]=b.dep[i];return *this;}
	il void insert(int x,int d) {
		for(int i=L;i>=0;i--) {
			if(!(x&(1<<i))) continue;
			if(!lbas[i]) {lbas[i]=x,dep[i]=d;return;}
			if(dep[i]<d) swap(dep[i],d),swap(x,lbas[i]);
			x^=lbas[i];
		}
	}
	il bool Comb(int x,int d) {
		for(int i=L;i>=0;i--) {
			if(dep[i]<d) continue;
			if(x&(1<<i)) x^=lbas[i];
		}
		return x==0;
	}
};
Lbase bas[N],tmp;
int n,q,a[N],dep[N],f[N][19];
vector<int> g[N];
il int LCA(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=18;i>=0;i--) if(dep[f[u][i]]>=dep[v]) u=f[u][i];
	if(u==v) return u;
	for(int i=18;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
il void dfs(int u,int fa) {
	dep[u]=dep[fa]+1,f[u][0]=fa;
	for(int i=1;i<=18;i++) f[u][i]=f[f[u][i-1]][i-1];
	bas[u]=bas[fa];
	bas[u].insert(a[u],dep[u]);
	for(auto v:g[u]) {
		if(v==fa) continue;
		dfs(v,u);
	}
}
int main() {
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1,u,v;i<n;i++) {
		u=read(),v=read();
		g[u].push_back(v),g[v].push_back(u);
	}
	dfs(1,0);
	q=read();
	while(q--) {
		int x=read(),y=read(),k=read();
		tmp=bas[x];
		for(int i=L;i>=0;i--) {
			if(!bas[y].lbas[i]) continue;
			tmp.insert(bas[y].lbas[i],bas[y].dep[i]);
		}
		bool flag=tmp.Comb(k,dep[LCA(x,y)]);
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```

小声：怎么 Burger 那道题是 2500，上树的本题只有 2400。。。

---

## 作者：Purslane (赞：0)

# Solution

做法很多。

首先是点分治，很容易做到 $O(n \log n \log V+q \log V)$。过于无脑而且是离线的就不提了。

主要说一说前缀线性基，之前我也没用过类似的东西。

考虑弱化的问题：给定一个序列 $a$，多次计算 $[l,r]$ 中元素构成的线性基。

平时用线性基的时候，都是从高位往低位插入。如果发现某一位已经有元素了，就让当且正在插入的基异或上这一位的元素。这样做缺点在于，基中所有元素都是最早出现的、陈旧的，如果 $l$ 比较大显然不能利用这些信息。

固定 $r$ 的时候，我们自然希望基中的元素尽可能靠后出现，这样对于更多的 $l$ 都能起到作用。

所以贪心的将时间戳更靠后的元素插入线性基中。

正确性看起来非常显然，严谨证明却不那么容易，略去 ~~（因为我不会线性代数。。）~~

对于树上问题，做法是类似的——将深度作为时间戳。询问找到 lca 即可。复杂度 $O(n \log V)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,q,a[MAXN],fa[MAXN][20],dep[MAXN];
struct BS {
	pair<int,int> bs[31];
	void insert(pair<int,int> pr) {
		roff(i,29,0) if(pr.first&(1<<i)) {
			if(!bs[i].first) return bs[i]=pr,void();
			if(bs[i].second<pr.second) swap(bs[i],pr);
			pr.first^=bs[i].first;
		}
		return ;
	}
}bs[MAXN],tmp;
vector<int> G[MAXN];
void dfs(int u,int f) {
	fa[u][0]=f,dep[u]=dep[f]+1,bs[u]=bs[f],bs[u].insert({a[u],dep[u]});
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]) if(v!=f) dfs(v,u);
	return ;	
}
int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	int dt=dep[u]-dep[v];
	ffor(i,0,19) if(dt&(1<<i)) u=fa[u][i];
	if(u==v) return u;
	roff(i,19,0) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int solve(int u,int v,int k) {
	memset(tmp.bs,0,sizeof(tmp.bs));	
	int l=lca(u,v);
	ffor(i,0,29) if(bs[u].bs[i].second>=dep[l]) tmp.insert({bs[u].bs[i].first,0});
	ffor(i,0,29) if(bs[v].bs[i].second>=dep[l]) tmp.insert({bs[v].bs[i].first,0});
	roff(i,29,0) if(k&(1<<i)) k^=tmp.bs[i].first;
	return k==0;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n-1) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);	
	}
	dfs(1,0);
	cin>>q;
	ffor(i,1,q) {
		int u,v,x;
		cin>>u>>v>>x;
		if(solve(u,v,x)) cout<<"YES\n";
		else cout<<"NO\n";	
	}
	return 0;
}
```

---

## 作者：liaoz123 (赞：0)

同学使用 $O(n\log^3n)$ 倍增+线性基通过了此题，对此感到十分震惊。

这是比较易于理解 $O(n\log^2n)$ 算法，同样采用了线性基，不过特殊地，我们采用了时间戳线性基，这里的时间戳可以代指每个基在原树上的深度，我们想让他尽可能大，因为深度 $<dep_{lca}$ 的基均不能取用，而深度越大越有效。

我们维护每个点到根上的元素所构成的线性基，询问时，将 $x,y$ 的线性基合并，并找到 $lca$，检查是否只可以通过时间戳 $>dep_{lca}$ 的基合成 $k$。

简单说明一下时间戳线性基的实现方法，假设我们插入了一个数 $x$，当前枚举到线性基的第 $i$ 位，如果当前位位空，则直接插入。否则比较基与 $x$ 的时间戳（深度）的大小关系，如果 $x$ 的戳更大，则交换 $x$ 和原来的基，并用原来的基继续往下插入；如果原来的基戳更大，就继续向下插入。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
struct node{
	int nxt,to;
}e[N];
struct Base{
	int dfn[32],p[32];
	Base(){
		memset(dfn,0,sizeof(dfn));
		memset(p,0,sizeof(p));
	} 
	void insert(int x,int d){
		for(int i=31;i>=0;i--){
			if(!((x>>i)&1))continue;
			if(!p[i]){
				p[i]=x;
				dfn[i]=d;
				return;
			}
			else if(dfn[i]<d){
				swap(p[i],x);
				swap(dfn[i],d);
			}
			x^=p[i];
		}
	} 
	bool query(int x,int d){
		for(int i=31;i>=0;i--){
			if(!((x>>i)&1))continue;
			if(!p[i]||dfn[i]<d)return false;
			x^=p[i];
		}
		return true;
	}
}s[N];
int num,head[N],dep[N],n;
int f[N][22],lg[N],a[N];
void add(int x,int y){
	e[++num]=node{head[x],y};head[x]=num;
}
void dfs(int u,int fa){
	f[u][0]=fa,dep[u]=dep[fa]+1;
	for(int i=1;i<=20;i++)
	f[u][i]=f[f[u][i-1]][i-1];
	s[u]=s[fa];s[u].insert(a[u],dep[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]!=dep[y])
	x=f[x][lg[dep[x]-dep[y]]];
	if(x==y)return x;
	for(int i=20;i>=0;i--)
	if(f[x][i]!=f[y][i])
	x=f[x][i],y=f[y][i];
	return f[x][0];
}
Base merge(Base x,Base y){
	Base ss=x;
	for(int i=31;i>=0;i--)
	if(y.p[i])ss.insert(y.p[i],y.dfn[i]);
	return ss;
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<N;i++)
	lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	int q;scanf("%d",&q);
	while(q--){
		int x,y,k;
		scanf("%d%d%d",&x,&y,&k);
		Base c=merge(s[x],s[y]);
		int lca=LCA(x,y);
		if(c.query(k,dep[lca]))puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

板子二合一是这样的。
### 题意
给定一棵 $n$ 个点的树，每次询问一条路径 $(u,v)$ 上能否选出若干点使得点权异或和为 $k$。
### 分析
选若干个能否异或出一个数，直接往线性基上想。

然后要查一条路径的线性基，可以离线，直接套个点分治。

具体地，从当前分治中心往下 dfs，维护每个点到分治中心的链上构建出的线性基。然后把跨过分治中心的询问拉出来，直接暴力合并两个端点上维护的线性基，查询即可。

想要拉出跨过分治中心的询问，可以把询问挂在点上，分治到每一层时先搜一遍，给每个点标记一下在哪个子树里，然后把询问找出来的时候判断一下是不是跨子树且没有处理过。

时间复杂度 $O(n\log n\log V+q\log^2V)$，不太卡。
### 代码

```cpp
//From: ifffer_2137
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
class Linear_Basic{
public:
	int b[20];
	inline void init(){for(int i=0;i<20;i++) b[i]=0;}
	inline void insert(int x){
		for(int i=19;i>=0;i--){
			if((x>>i)&1){
				if(!b[i]){b[i]=x;return;}
				else x^=b[i];
			}
		}
	}
	inline int check(int x){
		for(int i=19;i>=0;i--) if((x>>i)&1) x^=b[i];
		return x?0:1;
	}
};
int n,q;
int a[maxn],ans[maxn];
struct ask{int u,v,k;}Q[maxn];
vector<int> T[maxn],Eq[maxn];
int siz[maxn],mx[maxn],vis[maxn];
int cg,tot;
inline void getcg(int u,int f){
	siz[u]=1,mx[u]=0;
	for(int v:T[u]){
		if(v==f||vis[v]) continue;
		getcg(v,u);
		siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],tot-siz[u]);
	if(!cg||mx[u]<mx[cg]) cg=u;
}
Linear_Basic bas[maxn];
vector<int> sol;
int sub[maxn];
inline void dfs1(int u,int f,int t){
	sub[u]=t;
	for(int v:T[u]){
		if(v==f||vis[v]) continue;
		dfs1(v,u,t);
	}
}
inline void dfs2(int u,int f){
	bas[u]=bas[f];
	bas[u].insert(a[u]);
	for(int i:Eq[u]){
		if(ans[i]!=-1) continue;
		if(sub[Q[i].u]!=sub[Q[i].v]) sol.eb(i);
	}
	for(int v:T[u]){
		if(v==f||vis[v]) continue;
		dfs2(v,u);
	}
}
inline void solve(int u,int m){
	cg=0,tot=m;
	getcg(u,0);vis[cg]=1;
	sub[cg]=cg;
	for(int v:T[cg]){
		if(vis[v]) continue;
		dfs1(v,cg,v);
	}
	sol.clear();dfs2(cg,0);Linear_Basic x;
	for(int i:sol){
		if(ans[i]!=-1) continue;
		x.init();
		for(int j=0;j<20;j++) x.insert(bas[Q[i].u].b[j]),x.insert(bas[Q[i].v].b[j]);
		ans[i]=x.check(Q[i].k);
	}
	for(int v:T[cg]){
		if(vis[v]) continue;
		solve(v,m-mx[v]);
	}
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		T[u].eb(v),T[v].eb(u);
	}
	q=read();
	for(int i=1;i<=q;i++){
		int u=read(),v=read(),k=read();
		Q[i]={u,v,k};Eq[u].eb(i),Eq[v].eb(i);
		if(u==v) ans[i]=(a[u]==k||!k);
		else ans[i]=-1;
	}
	bas[0].init();solve(1,n);
	for(int i=1;i<=q;i++) if(ans[i]) puts("YES"); else puts("NO");
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

典中典的题目，几乎已经被出烂了。

考虑对于路径构造出线性基，这不太方便，考虑拆分为两条链后再构造线性基，具体而言，从根开始往下 dp，令 $dp_{u}$ 表示从 $u$ 到根界点链上所有点构成的线性基，那么我们要对 $dp_{u}$ 维护的操作形如加入一个有着数的节点与查询深度大于等于某个值的节点对应的数能否异或出 $k$ 也就是这些数组成的线性基。

考虑在线性基上对于每个位置维护可以插入这个位置的值在原树上对应节点的最大深度，那么当插入一个新的数时，还是从高往低按位考虑，假若遇到一个有值的位置，那么在消元前先判断是否这个数对应节点深度更大，假若深度更大，则将其替换为这一位上的值，并将原来的值取出来消元并向后遍历。

注意到这么做有一个令人费解之处，当你替换掉某一位置上的值时，可能在之前的插入中有的数对这个位置原先的值进行消元而现在需要对新值进行消元，这是难以处理的，但是在上面的策略中我们并没有处理这个东西，这是因为一个值与这个位置上原来的值进行消元说明贡献这个值的节点的深度大于等于这个原来可以插入到这个位置上的值在原树上的最大深度，那么关于深度的后缀询问在包含前者时一定包含了后者，所以既然一定都被包含了，将前者对后缀做消元是不影响的。

时间复杂度 $O((n + q \log V) \log V)$。

瓶颈在于合并两条链的线性基。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct info{
    int d[21],dp[21];
    bool ins(int u,int tm){
        for(int i=20;i>=0;i--){
            if((1<<i)&u){
                if(d[i]==0){
                    d[i]=u;
                    dp[i]=tm;
                    return true;
                }else{
                    if(tm>dp[i]) swap(u,d[i]),swap(tm,dp[i]);
                    u^=d[i];
                }
            }
        }
        return false;
    }
    info(){
        for(int i=0;i<21;i++) d[i]=0,dp[i]=0;
    }
};
const int maxn = 2e5+114;
int n,q,dep[maxn];
long long a[maxn];
int sz[maxn],son[maxn],top[maxn];
int t[maxn];
int father[maxn];
vector<int> E[maxn];
info e[maxn];
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    father[u]=fa;
    sz[u]=1;
    e[u]=e[fa];
    e[u].ins(a[u],dep[u]);
    for(int v:E[u]){
        if(v!=fa) dfs(v,u),son[u]=(sz[v]>sz[son[u]]?v:son[u]),sz[u]+=sz[v];
    }
}
void init(int u,int tp){
    top[u]=tp;
    if(son[u]!=0) init(son[u],tp);
    for(int v:E[u]){
        if(v!=father[u]&&v!=son[u]) init(v,v);
    }
}
int LCA(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=father[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    return v;
}
info chi;
void ask(int u,int depth){
    for(int i=0;i<21;i++){
        if(e[u].dp[i]>=depth) chi.ins(e[u].d[i],0);
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    cin>>q;
    dfs(1,0);
    init(1,1);
    while(q--){
        int u,v,k;
        cin>>u>>v>>k;
        int lca=LCA(u,v);
        chi=info();
        ask(u,dep[lca]);
        ask(v,dep[lca]);
        cout<<(chi.ins(k,0)==true?"NO\n":"YES\n");
    }
    return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：0)

没想到奇怪的技巧，但是这个题看起来好板子啊。

路径问题考虑点分治。设分治中心为点 $u$，记 $D_x$ 表示路径 $(u,x)$ 的点权线性基。那么一个跨过 $u$ 的询问 $(v,w)$，因为线性基有 $\rm RMQ$ 特性，只需要求解 $D_v\cup D_w$，判断是否可以组成 $k$ 即可。

复杂度 $O(n\log n\log V+q\log^2V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define MAXN 200005
 
int n,q,a[MAXN],vis[MAXN],rvis[MAXN],Ans[MAXN],maxp[MAXN],siz[MAXN],Rt = 0,Sum = 0;
vector<int> E[MAXN];
 
struct node{ int oth,k,id; };
vector<node> T[MAXN];
 
struct VirBase{
	int dort[25];
	inline void clear(){ memset( dort , 0 , sizeof( dort ) ); }
	inline void insert( int x ){
		for( int i = 24 ; ~i ; i -- ){
			if( !( x >> i & 1 ) ) continue;
			if( dort[i] ) x ^= dort[i];
			else{ dort[i] = x; break; }
		}
	}
	inline VirBase operator *( VirBase X ){
		VirBase ret = *this;
		for( int i = 0 ; i <= 24 ; i ++ ) ret.insert( X.dort[i] );
		return ret;
	}
	inline int queryK( int x ){
		for( int i = 24 ; ~i ; i -- ){
			if( !( x >> i & 1 ) ) continue;
			if( dort[i] ) x ^= dort[i];
		} return !x;
	}
}V[MAXN];
 
void get_root( int x , int fa ){
	siz[x] = 1,maxp[x] = 0;
	for( int v : E[x] ){
		if( v == fa || vis[v] ) continue;
		get_root( v , x ),siz[x] += siz[v];
		maxp[x] = max( maxp[x] , siz[v] );
	} maxp[x] = max( maxp[x] , Sum - siz[x] );
	if( maxp[Rt] > maxp[x] ) Rt = x;
}
 
void dfs_back( int x , int fa ){
	V[x].insert( a[x] ),rvis[x] = 1; siz[x] = 1;
	for( node N : T[x] ){
		int oth = N.oth,k = N.k,id = N.id;
		if( rvis[oth] ){
			VirBase R = V[x] * V[oth];
			Ans[id] = R.queryK( k );
		}
	}
	for( int v : E[x] ){
		if( v == fa || vis[v] ) continue;
		V[v] = V[x],dfs_back( v , x ),siz[x] += siz[v];
	}
}
 
void dfs_clear( int x , int fa ){
	rvis[x] = 0,V[x].clear();
	for( int v : E[x] ){
		if( v == fa || vis[v] ) continue;
		dfs_clear( v , x );
	}
}
 
void get_tree( int x ){
	vis[x] = 1,dfs_back( x , 0 ),dfs_clear( x , 0 );
	for( int v : E[x] ){
		if( vis[v] ) continue;
		maxp[Rt = 0] = 1e9,Sum = siz[v],get_root( v , x );
		get_tree( Rt );
	}
}
 
signed main(){
	scanf("%d",&n);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%d",&a[i]);
	for( int i = 1 ; i < n ; i ++ ){
		int u,v; scanf("%d%d",&u,&v);
		E[u].emplace_back( v ),E[v].emplace_back( u );
	}
	scanf("%d",&q);
	for( int i = 1 ; i <= q ; i ++ ){
		int u,v,k; scanf("%d%d%d",&u,&v,&k);
		T[u].emplace_back( node{ v , k , i } );
		T[v].emplace_back( node{ u , k , i } );
	}
	Sum = n,maxp[Rt = 0] = 1e9,get_root( 1 , 0 ),get_tree( Rt );
	for( int i = 1 ; i <= q ; i ++ ) puts( Ans[i] ? "YES" : "NO" );
	return 0;
}
```

---

