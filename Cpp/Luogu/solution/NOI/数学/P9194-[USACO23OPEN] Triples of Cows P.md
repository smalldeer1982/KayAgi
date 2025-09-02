# [USACO23OPEN] Triples of Cows P

## 题目描述

最初，农夫 John 的 $N$ 头编号为 $1 \dots N$ 的奶牛中有 $N-1$ 对朋友关系，形成一棵树。奶牛们依次离开农场去度假。在第 $i$ 天，第 $i$ 头奶牛离开农场，然后所有仍在农场中的第 $i$ 头奶牛的朋友之间会成为朋友。

对于每个 $i$ 从 $1$ 到 $N$，在第 $i$ 头奶牛离开之前，有多少个有序三元组 $(a, b, c)$ 满足以下条件：$a, b, c$ 均未离开农场，$a$ 与 $b$ 是朋友，且 $b$ 与 $c$ 是朋友？

## 说明/提示

对于第一个样例：  
- 在第 $1$ 头奶牛离开之前，三元组为 $(1, 2, 3)$ 和 $(3, 2, 1)$。  
- 在第 $1$ 头奶牛离开后，剩下的奶牛少于 $3$ 头，因此没有三元组。

对于第二个样例：  
- 最初，奶牛 $1$ 与所有其他奶牛是朋友，而其他奶牛之间没有朋友关系，因此三元组为 $(a, 1, c)$，其中 $a, c$ 是 $\{2, 3, 4\}$ 中的不同奶牛，共有 $3 \cdot 2 = 6$ 个三元组。  
- 在第 $1$ 头奶牛离开后，剩下的三头奶牛彼此都是朋友，因此三元组为这三头奶牛的任意排列，共有 $3! = 6$ 个三元组。  
- 在第 $2$ 头奶牛离开后，剩下的奶牛少于 $3$ 头，因此没有三元组。  

$2 \le N \le 2 \cdot 10^5$，$1 \le u_i, v_i \le N$。

- 输入 4-5：$N \le 500$。
- 输入 6-10：$N \le 5000$。
- 输入 11-20：没有额外限制。

## 样例 #1

### 输入

```
3
1 2
2 3
```

### 输出

```
2
0
0
```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
6
6
0
0
```

## 样例 #3

### 输入

```
5
3 5
5 1
1 4
1 2
```

### 输出

```
8
10
2
0
0
```

# 题解

## 作者：by_chance (赞：17)

[Link](https://www.luogu.com.cn/problem/P9194)

由于每次删点之后新增的边数太多，所以考虑拆边。用一个白点表示一条边，并将原来树中的点称为黑点，编号不变。对于第 $i$ 条边 $(u_i,v_i)$，在 $(u_i,n+i),(v_i,n+i)$ 间连边，得到一棵树 $T$。

删除点 $i$ 时，我们将点 $i$ 相邻的所有白点合并为一个点，然后删除 $i$。容易归纳证明：每次删除后 $T$ 仍然是树；真实的 $u,v$ 间有边等价于树 $T$ 中存在一个白点与 $u,v$ 均相邻。

因为依次删除 $1,2,...,n$，所以在树 $T$ 中，可以把点 $n$ 作为根。这样每次删除时，就可以把 $i$ 的所有相邻白点合并到 $i$ 的父亲白点上去。然后，用并查集维护每个白点被合并到了哪个点。

用 $fa_u$ 表示在初始的 $T$ 中 $u$ 的父亲结点，$p_u$ 表示某个时刻白点 $u$ 被合并到的点。那么，在这一时刻，黑点 $u$ 的父亲结点是 $p_{fa_u}$，白点 $u$ 的父亲节点是 $fa_{p_u}$。

下面来考虑如何统计答案。对白点 $u$，记 $s_u$ 为 $u$ 的儿子个数。

对于一个符合要求的 $(a,b,c)$，设 $a,b$ 通过白点 $x$ 相连，$b,c$ 通过白点 $y$ 相连。

1. 如果 $x=y$：固定 $x$，在 $x$ 的邻点中任选 $3$ 个，则对答案的贡献为
	$$\sum_{x} (s_x+1)s_x(s_x-1)$$
	求和的条件是 $x$ 是白点。
2. 如果 $x\not=y$，且 $x,y$ 都是 $b$ 的子节点：固定 $b$，先任取 $b$ 的两个子结点 $x,y$，此时贡献 $s_xs_y$。则总的贡献为
	$$\sum_{b} (\sum_{x} s_x) ^2 - \sum_{x} s_x^2$$
	第一个求和的条件是 $b$ 是黑点，后两个求和的条件是 $x$ 是 $b$ 的儿子。
	注意到后一项拆出来就是对所有白点 $x$ 求 $s_x^2$ 的和，那就拆出来吧。
3. 如果 $x\not=y$，且 $x,y$ 一个是 $b$ 的子结点，另一个是 $b$ 的父亲结点：不妨 $x$ 是 $b$ 的父亲结点，固定 $x$，$b$ 是 $x$ 的一个子结点，$y$ 又是 $b$ 的一个子结点，则对答案的贡献为
	$$\sum_{x} 2\times s_x \times \sum_{b} \sum_{y} s_y$$
	三个求和的条件分别为 $x$ 是白点，$b$ 是 $x$ 的子结点，$y$ 是 $b$ 的结点。

列出式子后，我们发现需要维护以下数据：
1. 白点 $u$ 的儿子数目 $s_u$
2. 黑点 $u$ 的儿子的 $s$ 值之和，也可以存到数组 $s$ 里
3. 白点 $u$ 的儿子的 $s$ 值之和 $t_u$

答案是 $\sum_{x}(f(s_x)+2s_xt_x)+\sum_{y} s_y^2$，其中 $f(x)=x^3-x^2-x$，两个求和的条件分别是 $x$ 是黑点，$y$ 是白点。

删除点 $u$ 时，枚举它初始的的儿子（一定没有被合并过），在并查集中将其合并到 $u$ 的父亲中。然后清零 $u$ 和 $u$ 的儿子的值，更新 $u$ 的三层祖先的值，并更新答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+5;
int n,fa[N],p[N];ll s[N],t[N],ans;
int head[N],ver[N<<1],nxt[N<<1],tot;
void add(int u,int v){ver[++tot]=v;nxt[tot]=head[u];head[u]=tot;}
void dfs(int u){
	for(int i=head[u],v;i;i=nxt[i])
		if((v=ver[i])!=fa[u]){
			fa[v]=u;dfs(v);
			if(u<=n)s[u]+=s[v];
			else ++s[u],t[u]+=s[v];
		}
}
int find(int x){return (x==p[x]?x:(p[x]=find(p[x])));}
ll f(ll x){return x*x*x-x*x-x;}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,n+i);add(v,n+i);add(n+i,u);add(n+i,v);
	}
	dfs(n);
	for(int i=1;i<2*n;i++)p[i]=i;
	for(int i=1;i<=n;i++)ans+=s[i]*s[i];
	for(int i=n+1;i<2*n;i++)ans+=f(s[i])+2*s[i]*t[i];
	for(int u=1;u<=n;u++){
		printf("%lld\n",ans);
		int g=find(fa[u]),w=fa[g];ll del=-1;
		ans-=f(s[g])+2*s[g]*t[g]+s[w]*s[w];s[w]-=s[g];--s[g];
		t[g]-=s[u];ans-=s[u]*s[u];s[u]=0;
		for(int i=head[u],v;i;i=nxt[i])
			if((v=ver[i])!=fa[u]){
				p[v]=g;s[g]+=s[v];t[g]+=t[v];del+=s[v];
				ans-=f(s[v])+2*s[v]*t[v];s[v]=t[v]=0;
			}
		s[w]+=s[g];ans+=f(s[g])+2*s[g]*t[g]+s[w]*s[w];
		t[w=find(fa[fa[g]])]+=del;ans+=2*s[w]*del;
	}
	return 0;
}
```

Upd：修改了格式。

---

## 作者：spider_oyster (赞：8)

删除一个点影响太大，考虑增加一些额外结点。

把第 $i$ 条边拆为 $(u,n+i),(v,n+i)$。

记原来的点是黑点，新加的点为白点。

不难发现新生成的图还是一棵树，且一个白点所连的所有黑点在原图两两有边。

考虑删除一个黑点 $u$，就是让 $u$ 的子白点 $v$ 合并到父亲白点 $fa_u$ 上。

并查集维护即可。

考虑计算答案。不妨三元组 $(a,b,c)$ 变为五元组 $(a,x,b,y,c)$，其中 $x,y$ 为白点，其余为黑点。那么有以下情况：

- $x=y$

设 $f_x$ 为白点 $x$ 的黑儿子个数，随便选三个即可，贡献 $(f_x+1)\times f_x \times (f_x-1)$。

- $x,y$ 为 $b$ 的儿子。

枚举 $x,y$，贡献 $\sum\limits_{x,y\in son_b,x\neq y} f_x\times f_y=(\sum\limits_{x} f_x)^2-\sum\limits_{x} f_x^2$。

- $x$ 为 $b$ 的父亲，$y$ 为 $b$ 的儿子。

贡献为 $2\times f_x\sum\limits_{b\in son_x} \sum\limits_{y\in son_b} f_y$，前面为选 $a$（除 $b$ 以外的其他儿子和 $x$ 的父亲）的方案，后面为选 $c$ 的方案。

若 $i$ 为黑点，定义 $g_i=\sum\limits_{j\in son_i} f_j$。

若 $i$ 为白点，定义 $h_i=\sum\limits_{j\in son_i} g_i$。

考虑对上面的所有情况贡献求和，那么答案为：

$\sum\limits_{1\leq i\leq n} g_i^2+\sum\limits_{n<j<2n} (f_i+1)\times f_i\times (f_i-1)-f_i^2+2\times f_i\times h_i$。

删除一个点 $u$，受影响的有子结点 $v$，父结点 $x$，父父结点 $y$，父父父结点 $z$。

合并 $v \rightarrow x$，维护 $f,g,h$ 值即可。

尤其注意合并时要剔除 $f_v$ 对 $t_x$ 的贡献。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=4e5+5;
int n,ans,f[N],g[N],h[N],fa[N],F[N];
vector<int> G[N];
int find(int x) {return x==F[x]?x:F[x]=find(F[x]);}
int calc(int i) {if(!i) return 0;return (f[i]+1)*f[i]*(f[i]-1)-f[i]*f[i]+2*f[i]*h[i];}

void dfs(int u)
{
    for(int v:G[u])
    {
        if(v==fa[u]) continue;
        fa[v]=u,dfs(v);
        if(u<=n) g[u]+=f[v];
        else f[u]++,h[u]+=g[v];
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        G[u].push_back(n+i),G[n+i].push_back(u);
        G[v].push_back(n+i),G[n+i].push_back(v);
    }
    dfs(n);//以 n 为根因为 n 是最后一个删除的
    for(int i=1;i<=n;i++) ans+=g[i]*g[i];
    for(int i=n+1;i<2*n;i++) ans+=calc(i),F[i]=i;
    cout<<ans<<'\n';
    for(int i=1;i<n;i++)
    {
        int u=i,x=find(fa[u]),y=fa[x],z=find(fa[y]);
        ans-=g[u]*g[u]+calc(x)+g[y]*g[y]+calc(z);
        f[x]--,g[y]--,h[z]--;
        for(int v:G[u])
        {
            if(v==fa[u]) continue;
            F[v]=x;
            ans-=calc(v);
            f[x]+=f[v];
            h[x]-=f[v],h[x]+=h[v];
            g[y]+=f[v],h[z]+=f[v];
        }
        ans+=calc(x)+g[y]*g[y]+calc(z);
        cout<<ans<<'\n';
    }
}
```

---

## 作者：EuphoricStar (赞：3)

hot tea.

一次删点操作的影响太大了，考虑**添加虚点**以减小影响（相同的套路在 [CF1882E2 Two Permutations (Hard Version)](https://www.luogu.com.cn/problem/CF1882E2) 也出现过）。

具体而言，我们把第 $i$ 条边 $(u, v)$ 变成 $(u, n + i), (v, n + i)$。称编号 $\le n$ 的点为黑点，编号 $> n$ 的点为白点。

因为最后只剩 $n$ 一个单点，所以不妨以 $n$ 为根。

那么删掉一个黑点 $u$ 就可以看成，把 $u$ 的所有儿子（白点）**合并**到 $fa_u$，也就是把 $u$ 的所有儿子的所有子树都接到 $fa_u$ 下面。

然后经过若干次删点操作后两个黑点有边等价于存在一个白点连接这两个黑点。因为操作后原本的这棵树还是一棵树，所以这样的白点最多只有一个。

先考虑一次怎么算答案。对于一个三元组 $(a, b, c)$ 把它看成 $(a, x, b, y, c)$，其中 $x$ 和 $y$ 分别为 $a, b$ 和 $b, c$ 之间的白点。

分类讨论一下。

- 若 $x = y$，$x$ 的相邻点可以任选 $3$ 个。若设 $f_u$ 为白点 $u$ 的儿子数量，那么这个对答案的贡献即为 $(f_x + 1) \times f_x \times (f_x - 1)$。
- 若 $x \ne y$ 且 $x, y$ 是 $b$ 的两个儿子，我们在 $b$ 处统计贡献。若设 $g_u$ 为黑点 $u$ 的**二级儿子**数量，贡献即为 $g_b^2 - \sum\limits_{u \in son_b} f_u^2$。观察到每个 $u$ 会恰好被算一遍 $- f_u^2$，于是可以把这个扔到上一种情况的贡献。
- 若 $x \ne y$ 且 $x, y$ 分别是 $b$ 的一个儿子和父亲，不妨设 $x$ 为 $b$ 的父亲。我们在 $x$ 处统计答案。若设 $h_u$ 为白点 $u$ 的**三级儿子**数量，贡献即为 $2 \times f_x \times h_x$，其中 $f_x$ 为选择 $a$ 的方案。

综上，我们需要维护：

$$\sum\limits_{i = 1}^n g_i^2 - \sum\limits_{i = n + 1}^{2n - 1} f_i (f_i + 1) (f_i - 1) - f_i^2 - 2 f_i h_i$$

一次对 $u$ 的删除操作，只会影响 $u$ 的不超过三级的祖先。暴力更新这些点的 $f, g, h$ 即可。还要去除 $u$ 和 $u$ 的儿子原来的贡献。

使用并查集维护白点 $u$ 最终被合并到了哪个点。时间复杂度取决于并查集。

```cpp
// Problem: P9194 [USACO23OPEN] Triples of Cows P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9194
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 400100;

ll n, a[maxn], f[maxn], g[maxn], h[maxn], fa[maxn];
vector<int> G[maxn];

int find(int x) {
	return a[x] == x ? x : a[x] = find(a[x]);
}

void dfs(int u, int fa) {
	for (int v : G[u]) {
		if (v == fa) {
			continue;
		}
		::fa[v] = u;
		dfs(v, u);
		if (u <= n) {
			g[u] += f[v];
		} else {
			++f[u];
			h[u] += g[v];
		}
	}
}

void solve() {
	scanf("%lld", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(n + i);
		G[n + i].pb(u);
		G[v].pb(n + i);
		G[n + i].pb(v);
	}
	dfs(n, -1);
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += g[i] * g[i];
	}
	for (int i = n + 1; i < n * 2; ++i) {
		ans += (f[i] + 1) * f[i] * (f[i] - 1) - f[i] * f[i] + f[i] * h[i] * 2;
		a[i] = i;
	}
	printf("%lld\n", ans);
	for (int u = 1; u < n; ++u) {
		ans -= g[u] * g[u];
		int x = find(fa[u]);
		int y = fa[x];
		int z = find(fa[y]);
		// printf("%d %d %d %d\n", u, x, y, z);
		ans -= (f[x] + 1) * f[x] * (f[x] - 1) - f[x] * f[x] + f[x] * h[x] * 2;
		ans -= g[y] * g[y];
		if (z) {
			ans -= (f[z] + 1) * f[z] * (f[z] - 1) - f[z] * f[z] + f[z] * h[z] * 2;
		}
		--f[x];
		--g[y];
		if (z) {
			--h[z];
		}
		for (int v : G[u]) {
			if (v == fa[u]) {
				continue;
			}
			a[v] = x;
			f[x] += f[v];
			h[x] -= f[v];
			h[x] += h[v];
			g[y] += f[v];
			if (z) {
				h[z] += f[v];
			}
			ans -= (f[v] + 1) * f[v] * (f[v] - 1) - f[v] * f[v] + f[v] * h[v] * 2;
		}
		ans += (f[x] + 1) * f[x] * (f[x] - 1) - f[x] * f[x] + f[x] * h[x] * 2;
		ans += g[y] * g[y];
		if (z) {
			ans += (f[z] + 1) * f[z] * (f[z] - 1) - f[z] * f[z] + f[z] * h[z] * 2;
		}
		// for (int i = 1; i <= n * 2 - 1; ++i) {
			// printf("%lld %lld %lld\n", f[i], g[i], h[i]);
		// }
		printf("%lld\n", ans);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：tuxuanming2024 (赞：2)

一个不需要圆方树，不需要分讨的无脑做法。

首先答案显然是 $\sum_i \deg_i(\deg_i - 1)$，$\deg_i$ 表示 $i$ 的度数。那么问题就是怎么在每次删点后维护这个东西。

我们定这棵树的根为 $1$。令任意一个时刻，树上一个点表示一个完全子图，这个完全子图同时与这个点**真实的父亲**构成完全子图。比如如下是这棵树在删去点 $1 \sim 4$ 之后的状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/tzplj9f0.png)

那么此时这棵树就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/9u8dvtt5.png)

这个性质对初始树也是成立的。

当删除点 $x$ 时，将 $x$ 所在的点与 $x$ **真实的儿子**所在的点合并，那么这个新点也就满足点内部是完全图，并与其父亲也构成完全图。我们在每一个结点上记录这个点内的所有点度数信息。这样的好处在于每个真实点都被唯一储存在了一个连通块中。

具体地，我们要记录每个连通块内点的个数，点的度数和，度数的平方和。当删去点 $x$ 时，做如下操作：

1. 将 $x$ 所在连通块的各项信息减去 $x$ 的贡献
2. 将 $x$ 的父亲与 $x$ 的所有儿子的度数整体 $-1$。
3. 计算当前有多少个点与 $x$ 相邻，即 $x$ 儿子的连通块点数之和，加 $x$ 连通块内部的点数，再加上父亲的 $1$（如果存在父亲）。设这个数为 $s$。
4. 将 $x$ 连通块的度数整体加：$s-$ ($x$ 连通块内部点数)。
5. 将 $x$ 的所有儿子连通块的度数整体加： $s-$ (这个儿子内部的点数)。
6. 将 $x$ **真实的父亲**度数增加 $s-1$。
7. 将 $x$ 与其所有儿子所在的连通块合并。

合并可以用并查集维护。度数和、度数平方和整体增加是好维护的。但同时我们也要维护每个单点的度数，这就需要在并查集上打标记。具体实现可以看一下代码。

复杂度 $O(n \log n)$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,prt[N],sz[N],deg[N],fa[N],tag[N],tot[N];
ll s1[N],s2[N],ans;
vector<int>e[N],g[N];
void Addedge(int x,int y) {e[x].push_back(y),e[y].push_back(x);}
void dfs(int x)
{
	for(auto y:e[x]) if(y!=fa[x]) fa[y]=x,g[x].push_back(y),dfs(y);
}
int getdeg(int x)
{
	int res=deg[x];
	while(prt[x]!=x) res+=tag[x],x=prt[x];
	return res+tag[x];
}
int find(int x) {return x==prt[x]?x:find(prt[x]);}
void add(int x,ll v) // 连通块的度数整体增加
{
	if(!x) return;
	ans-=s2[x]-s1[x];
	tag[x]+=v,s2[x]+=2*v*s1[x]+v*v*tot[x],s1[x]+=v*tot[x];
	ans+=s2[x]-s1[x];
}
void merge(int x,int y)
{
	if((x=find(x))==(y=find(y))) return;
	if(sz[x]>sz[y]) swap(x,y);
	prt[x]=y,sz[y]+=sz[x];
	s1[y]+=s1[x],s2[y]+=s2[x],tot[y]+=tot[x],tag[x]-=tag[y]; // 合并的时候儿子要把父亲的 tag 减掉
}
void mdf(int x,int v) // 单点修改一个点的度数
{
	if(!x) return;
	int p=find(x),d=getdeg(x);
	ans-=1ll*d*(d-1),s2[p]-=1ll*d*d;
	deg[x]+=v,s1[p]+=v,d+=v;
	ans+=1ll*d*(d-1),s2[p]+=1ll*d*d;
}
int main()
{
#ifdef LOCAL
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	freopen("1.err","w",stderr);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1,x,y;i<n;i++) cin>>x>>y,Addedge(x,y);
	for(int i=1;i<=n;i++) prt[i]=i,sz[i]=1,tot[i]=1;
	for(int i=1;i<=n;i++)
	{
		s1[i]=deg[i]=e[i].size(),s2[i]=s1[i]*s1[i];
		ans+=1ll*deg[i]*(deg[i]-1);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		cout<<ans<<"\n";
		int d=getdeg(i),p=fa[find(i)]; ans-=1ll*d*(d-1);
		tot[find(i)]--,s1[find(i)]-=d,s2[find(i)]-=d*d;
		add(find(i),-1),mdf(p,-1);
		int ss=0,sz=tot[find(i)];
		for(auto j:g[i]) add(find(j),-1),ss+=tot[find(j)];
		add(find(i),ss),ss+=bool(p);
		for(auto j:g[i]) add(find(j),ss-tot[find(j)]+sz),fa[find(j)]=p,merge(i,j);
		mdf(p,ss-1);
	}
	return 0;
}
```

---

## 作者：Felix72 (赞：2)

这些操作会带来很多额外的边，因此我们必须思考一个另外的方式来刻画这个图。挖掘这个图的特点：每条边恰好属于一个**团**里。

我们知道，这和仙人掌的定义极为相似，因此我们定义**仙人球：每条边恰好属于一个团的图**。仙人掌一般用什么统计信息？答案是圆方树，相应的，仙人球也可以用圆方树维护。

刻画完这个图，我们再来想想怎么刻画所求内容。用 $\sum dg_i (deg_i - 1)$ 表示固然可以，但是和圆方树关系好像不大。再思考一下，我们要求的是原图中长度为三的链，在圆方树上就应该是三个两两经过方点个数不超过 $2$ 的圆点三元组，一次合并操作就是把一个圆点和它周围的方点合并成一个方点。

求这个，我们有一个小技巧：以 $n$ 这个点作为树根，这样根节点始终不会被改变，且每个方点都有父亲节点。这样，我们能够简单地分类计算以下贡献：

- 两个圆点，且他们的 $\operatorname{LCA}$ 是一个圆点；
- 两个圆点，且上面那个圆点和另一棵子树的原点共有一个方点父亲；
- 三个圆点，两个方点构成一条从上而下的链；
- 一个方点，周围随便选三个圆点。

求这些都需要用到某些信息：$f_{i, j}$ 表示 $i$ 子树内与 $i$ 距离为 $j$ 的节点数量。这是可以并查集维护的。

```cpp
/*Good Game, Well Play.*/
#include <bits/stdc++.h>
using namespace std;

const int N = 400010;
int n, m, fa[N]; vector < int > edge[N];
long long res;

struct DSU
{
	long long f[N][4]; int prt[N];
	inline void refresh(int now, int to, int opt)
	{
		if(!now) return ;
		f[now][1] += opt;
		f[now][2] += f[to][1] * opt;
		f[now][3] += f[to][2] * opt;
	}
	inline int find(int x)
	{return ((x == prt[x]) ? x : (prt[x] = find(prt[x])));}
}; DSU dsu;
inline void debug(int i) {cerr << "debug " << i << " : " << dsu.f[i][1] << " " << dsu.f[i][2] << " " << dsu.f[i][3] << '\n';}
inline void get(int i, int opt)
{
	if(!i) return ;
	if(i <= n) res += opt * (dsu.f[i][2] * dsu.f[i][2]);
	else res += opt * (2ll * dsu.f[i][3] * dsu.f[i][1] - dsu.f[i][1] * dsu.f[i][1] + (dsu.f[i][1] + 1) * dsu.f[i][1] * (dsu.f[i][1] - 1));
}
inline void init(int now, int prt)
{
	fa[now] = prt; dsu.prt[now] = now;
	for(int to : edge[now])
	{
		if(to == prt) continue;
		init(to, now);
		dsu.refresh(now, to, 1);
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n; m = n;
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		++m;
		edge[x].push_back(m), edge[m].push_back(x);
		edge[y].push_back(m), edge[m].push_back(y);
	}
	init(n, 0);
	for(int i = 1; i <= m; ++i) get(i, 1);
	cout << res << '\n';
	for(int i = 1; i < n; ++i)
	{
		int pos[4] = {i, 0, 0, 0};
		for(int to : edge[pos[0]])
		{
			if(to == fa[pos[0]]) continue;
			get(dsu.find(to), -1);
		}
		for(int j = 1; j <= 3; ++j) pos[j] = dsu.find(fa[pos[j - 1]]);
		for(int j = 0; j <= 3; ++j) get(pos[j], -1);
		for(int j = 2; j >= 0; --j) dsu.refresh(pos[j + 1], pos[j], -1);
		
		dsu.f[i][1] = dsu.f[i][2] = dsu.f[i][3] = 0;
		for(int to : edge[pos[0]])
		{
			if(to == fa[pos[0]]) continue;
			for(int j = 1; j <= 3; ++j)
				dsu.f[i][j] += dsu.f[to][j];
			dsu.prt[to] = i;
		}
		for(int j = 1; j <= 3; ++j)
			dsu.f[pos[1]][j] += dsu.f[pos[0]][j];
		dsu.prt[pos[0]] = pos[1];
		
//		debug(pos[0]);

		for(int j = 2; j <= 3; ++j)
			dsu.refresh(pos[j], pos[j - 1], 1);
		
		for(int j = 1; j <= 3; ++j) get(pos[j], 1);
		
//		cerr << "result " << i << '\n';
//		for(int j = 1; j <= m; ++j)
//			if(dsu.find(j) == j)
//				cerr << "! " << j << " " << dsu.f[j][1] << " " << dsu.f[j][2] << " " << dsu.f[j][3] << '\n'; 
		
		cout << res << '\n';
	}
	return 0;
}
```

---

## 作者：Drimpossible (赞：1)

## [Link](https://www.luogu.com.cn/problem/P9194)

首先因为一个点连接的点可能会有很多个，每次重新连边复杂度会爆炸。

那我们考虑对于每条边建立一个虚拟点（称为白点，原来的点称为黑点），原来的一条边 $(u_i,v_i)$ 变成 $(u_i,n+i)$ 和 $(n+i,v_i)$。那么两个黑点在原图上有连边，当且仅当它们在新图上只隔了一个白点。

我们发现通过这样建出来的图具有非常好的性质：

1. 仍然是一颗**树**（证明显然，一共 $2N-1$ 个点，$2N-2$ 条边，且一定联通）。
1. 黑点只和白点相连，白点也只和黑点相连。
1. 每次删点只需将黑点删掉，把和它相连的白点合并到一起，这样修改过的图仍然满足这几条性质。

有了这几条性质，这道题的思路就清晰了，接着我们考虑答案会在哪些地方出现：

因为我们加入了白点，那么原来的**有序**三元组 $(a,b,c)$ 就变成 $(a,x,b,y,c)$，其中 $x,y$ 为白点。再定义 $s_u$ 表示白点 $u$ 有几个儿子。

1. $x=y$ 那么只需要考虑一个白点 $x$。在与 $x$ 相连的点里随便选 $3$ 个，排列一下，有：
$$
\sum_x A_{s_x+1}^{3}
$$
因为和 $x$ 相连的黑点不只有儿子，还有父亲，所以总个数为 $s_x+1$。

2. $x \ne y$ 且 $x,y$ 为同一个黑点 $u$ 的儿子，有：
$$
\sum_u \Sigma_{x,y}^{x!=y}s_xs_y
$$
$$
=\sum_u (\Sigma_x s_x)^2-\Sigma_x s_x^2
$$
$x$ 任意选 $y$，但是要除掉选自己的情况。

3. $x \ne y$ 且 $x$ 为一个黑点 $u$ 的父亲，$y$ 为 $u$ 的儿子，有：
$$
\sum_x 2 \times s_x \times \Sigma_u \Sigma_y s_y
$$
因为统计**有序**，所以 $u$ 在中间，但是两头可以置换，所以要乘 $2$。

综上所述，答案即为 $\sum_x (s_x^3-s_x^2-s_x+2 \times \sum_u \sum_ys_y)+\sum_u (\sum_x s_x)^2$。

然后每次合并白点用并查集实现，更新三代祖先的贡献即可（因为一个点被删是影响不了三代以上祖先的答案的）。还有些细节看注释吧。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2009421;
int n,ans;
struct edge{
	int v,nxt;
}e[N];
int head[N],ct;
void adde(int u,int v){
	e[++ct]={v,head[u]};
	head[u]=ct;
}
int f[N];
int find(int k){
	if(f[k]==k)return k;
	return f[k]=find(f[k]);
}
int s[N],t[N],fa[N];
/*白点s看上文，黑点s表示所有白点儿子的s之和，白点t表示所有黑点儿子的s之和*/
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa[u])continue;
		fa[v]=u,dfs(v);
		if(u<=n)s[u]+=s[v];
		else s[u]++,t[u]+=s[v];
	}
}
int calc(int x){
	return x*x*x-x*x-x;
}
signed main(){
	cin>>n;
	for(int i=1;i<=(n<<1);i++)f[i]=i;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		adde(u,n+i),adde(n+i,u);
		adde(v,n+i),adde(n+i,v);//双向边
	}
	dfs(n);//因为n号点被删不影响答案，所以以n为根方便合并
	for(int i=1;i<=n;i++)ans+=s[i]*s[i];//黑点初始答案
	for(int i=n+1;i<(n<<1);i++)ans+=calc(s[i])+2*s[i]*t[i];//白点初始答案
	for(int u=1;u<=n;u++){
		printf("%lld\n",ans);
		int fu=find(fa[u]),ffu=fa[fu],sum=-1;//这里-1是因为u的三代祖先的t要去掉u这个点
		ans-=calc(s[fu])+2*s[fu]*t[fu]+s[ffu]*s[ffu];
		s[ffu]-=s[fu],s[fu]--,t[fu]-=s[u];
		ans-=s[u]*s[u],s[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa[u])continue;
			f[v]=fu,s[fu]+=s[v],t[fu]+=t[v],sum+=s[v];//把u的儿子合并到u的父亲
			ans-=calc(s[v])+2*s[v]*t[v],s[v]=t[v]=0;//减掉之前的贡献
		}
		s[ffu]+=s[fu],ans+=calc(s[fu])+2*s[fu]*t[fu]+s[ffu]*s[ffu];//重新计算贡献
		int fffu=find(fa[fa[fu]]);
		t[fffu]+=sum,ans+=2*s[fffu]*sum;//加上三代祖先增加的贡献
	}
	return 0;
}
```

---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9194)

首先答案显然是 $\sum\limits_{i=1}^nd_i(d_i-1)$。

其中，$d_i$ 表示 $i$ 的度数。

考虑两个点在什么时候会被连接。

可以发现，第 $t$ 天后，若点 $x,y$ 路径上（不包括端点）的所有点都被删了，也就是路径上编号的最大值不超过 $t$，则 $x,y$ 会被连接。

考虑动态维护 $\sum d_i$ 和 $\sum d_i^2$。

当前第 $t$ 天后，我们称编号不超过 $t$ 的点为虚点，编号大于 $t$ 的点为实点。

为了方便维护，在每条边中间插入一个虚点。

每次，会把一个实点转化为虚点。

用并查集维护虚点构成的连通块，把连通的虚点缩到一起。

这样，树上所有边的两端点都是一个实点和一个虚点。

此时，一个实点的度数就是与它距离为 $2$ 的点的个数。

考虑合并两个连通块会有什么影响。

对于度数和的维护，我们只需要维护每个虚点的度数即可。

对于度数的平方和，由于 $(d_i+k)^2=d_i^2+k^2+2kd_i$。

所以我们还要动态维护与每个虚点相邻的实点的度数和。

随便钦定一个根。

设 $f_x$ 为虚点 $x$ 的所有儿子的度数之和，$g_x$ 为实点 $x$ 的子树中距离 $x$ 等于 $2$ 的点的个数。

这样，一个点度数改变时只需要更新其父节点的 $f_x$，两个虚点合并时只需要更新父节点的 $g_x$。

查询的时候也只需要用 $f_x$ 或 $g_x$ 加上父节点的贡献。

总复杂度 $O(n)$ 乘上并查集复杂度。细节很多。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+5;
int n,res1,res2,ds[N],siz[N],fa[N],fs[N],cnt,mk[N],d[N],g[N];
vector<int>p[N],q[N];
int f(int x){
	if(x==fa[x])return x;
	return fa[x]=f(fa[x]);
}
int solve(){
	int res=0;
	for(int i=1;i<=n;i++)res+=ds[i]*(ds[i]-1);
	return res;
}
int gds(int x){
	if(!x)return 0;
	if(fs[x])return d[x]+siz[f(fs[x])]-1;
	return d[x];
}
int gets(int x){
	return g[x]+gds(fs[x]);
}
void hb(int a,int b){
	a=f(a);b=f(b);
	res2+=siz[a]*siz[b]*2;
	res1+=siz[b]*siz[b]*siz[a]+siz[a]*siz[a]*siz[b]+2*siz[b]*gets(a)+2*siz[a]*g[b];
	g[a]+=g[b]+(siz[a]-(a!=1))*siz[b]+siz[b]*siz[a];
	d[fs[a]]+=siz[b];
	if(fs[fs[a]])g[f(fs[fs[a]])]+=siz[b];
	siz[a]+=siz[b];fa[b]=a;
}
void dfs(int x){
	mk[x]=1;
	for(auto c:p[x]){
		if(mk[c])continue;
		dfs(c);
		fs[c]=x;
	}
}
void add(int x){
    fa[x]=x;
    int k=gds(x);
    res1-=k*k;
    res2-=k;
	for(auto c:p[x]){
		if(c==fs[x]){
			c=f(c);
			res1+=siz[c]-1-2*(gets(c)-k);
			if(c!=1){
				d[fs[c]]--;
				g[f(fs[fs[c]])]--;
			}
			g[c]-=k+siz[c]-(c!=1)-1;
			siz[c]--;
			res2-=siz[c];
			hb(c,x);
		}
	}
	for(auto c:p[x]){
		if(c==fs[x])continue;
		else{
			c=f(c);
			res1+=siz[c]-1-2*g[c];
			siz[c]--;
			res2-=siz[c];
			g[c]-=siz[c];
			hb(x,c);
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;cnt=n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		cnt++;
		p[x].push_back(cnt);
		p[cnt].push_back(x);
		p[y].push_back(cnt);
		p[cnt].push_back(y);
		siz[cnt]+=2;
	}
	dfs(1);
	for(int i=n+1;i<=cnt;i++){
		fa[i]=i;
		d[fs[i]]+=siz[i]-1;
	}
	for(int i=2;i<=n;i++)g[fs[i]]+=p[i].size();
	for(int i=1;i<=n;i++)res1+=p[i].size()*p[i].size(),res2+=p[i].size();
	for(int i=1;i<=n;i++){
		cout<<res1-res2<<"\n";
		add(i);
	}
}
```

---

## 作者：IamZZ (赞：0)

**P组练习总结#7**

~~今天打 USACO2024JAN P 爆零了，破大防，过来解解气。~~

网站不大给力啊，一个黑客给你弄崩了？

第一次写黑题的题解，有点挑战性，希望能写好！

### 题目大意

FJ 的奶牛每天都在放假吗？现在它们又迎来了欢乐的假期~~但我还没有~~。

$n(n\leq2\times10^5)$ 头奶牛两两配对形成了一棵树的形态，现在假期来了，在第 $i$ 天，$i$ 号奶牛会离开农场去嗨。

为了保证朋友的数量，当奶牛 $i$ 离开的时候，它还在农场的朋友们会互相交个朋友，这样就可以一定程度维持朋友的数量啦！

现在要求的是：在 $i$ 号奶牛**离开前**，整个农场中，存在多少个形如 $a,b,c$ 的三元组，满足 $a$ 与 $b$ 是朋友，同时 $a$ 与 $c$ 是朋友。

### 解题思路

如果暴力模拟去连接新的边的话，我们会浪费大量的时间复杂度做重复的事，复杂度 $\Theta(n^3)$，只能过 5 个点。

我们思考一下，如果我们用一个点来代替完全图的连边关系了，圆点表示本来就存在的点，方点表示与方点相连的圆点互相都有连一条边。

当然，这题和圆方树无关，只不过方便描述，而且最后长得很像，效果很相似……

这样，我们就把一个边很多很多的图，用点来代替了，控制了总边数，不仅如此，一棵树在处理之后，仍然是一棵树！

我们再思考一下，删去一个圆点 $i$ 的操作在图上怎么体现呢？

相当于把所有 $i$ 相连的方点**合并**为一个方点，这样子，本来和 $i$ 相连的点都连着这个新的方点了，就完成了题目所需的操作了。

一个小技巧，我们钦定一个圆点为根，这样就可以保证**每一个方点都有一个圆点父亲**。

我们先通过遍历，处理一下信息：

对于一个方点 $p$，统计 $s_p(size)$ 和 $ts_p(triplesize)$ 分别表示 $p$ 子树中 $dist(p,x)=1$ 和 $dist(p,x)=3$ 的黑点个数

对于一个圆点 $p$，统计 $ds_p(doublesize)$，表示 $p$ 点子树中 $dist(p,x)=2$ 的黑点个数。

转移很简单，$s_p$ 直接算，$ds_p$ 为儿子的 $s_v$ 之和，$ts_p$ 为儿子的 $ds_v$ 之和

现在，考虑在这棵树上算答案，设当前点是 $p$：

第一种：

如果 $p$ 是方点，我们可以在 $p$ 点连着的圆点中找三个组成三元组，$p$ 周围共有 $s_p+1$ 个圆点（**包括父亲那一个**），共有 $(s_p+1)\times s_p\times(s_p-1)$ 个组合。

大概长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/si09z85i.png)

第二种：

$p$ 还是方点，先取它的一个三级儿子，从 $ts_p$ 中取一个 $a$，再从 $p$ 直接相连的圆点中取一个 $b$，当然 $b$ 不能是 $a$ 的祖先，搭配 $a$ 祖先的那一个圆点 $c$。

看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/n93yu55f.png)

$ts_p$ 个中选一个，乘上 $p$ 周围选一个又不能是 $c$，$p$ 周围本来有 $s_p+1$ 个，减去一个剩下 $s_p$ 个，开头结尾可以互换，总共就有 $2\times ts_p\times s_p$ 个啦~

第三种：

$p$ 这次是圆点了！

找到两个不同的方点儿子（如果相同就和第一种重复了一部分），$u,v$，统计 $2\sum_u\sum_{v(u<v)}s_u\times s_v$。

上图！

![](https://cdn.luogu.com.cn/upload/image_hosting/7lerlgw5.png)

至此，所有圆点方点的答案都统计出来了，合并处理就好了！

### 参考代码（暴力）

先给个抽象的暴力代码，复杂度 $\Theta(n^2)$，用了极其抽象的合并方法！

就当个乐子看看算了，不重要……

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=2e5+5;
int n,x,y,c=1,o,f[N<<3];
ll ans,s[N<<3],ds[N<<3],ts[N<<3];
struct edge
{
	int t,e,h;
}e[N<<3];
void add(int u,int v)
{
	++c;
	e[c].t=v;
	e[c].e=e[u].h;
	e[u].h=c;
	return ;
}
void merge(int p)//合并，当个乐子看就好了
{
	int i,j,v,tp;
	if(p==n)
	  return ;
	if(s[p]==1)
	{
		for(i=e[p].h;i;i=e[i].e)
		{
			if(e[i].t!=-1)
			{
				v=e[i].t;
				break;
			}
		}
		if(s[v]==1)
		{
			f[v]=1;
			for(i=e[v].h;i;i=e[i].e)
			{
				if(e[i].t!=p&&e[i].t!=-1)
				{
					e[i^1].t=-1;
					break;
				}
			}
		}
		else
		{
			for(i=e[v].h;i;i=e[i].e)
			{
				if(e[i].t==p)
				{
					e[i].t=-1;
					break;
				}
			}
		}
		return ;
	}
	++o;
	for(i=e[p].h;i;i=e[i].e)
	{
		v=e[i].t;
		f[v]=1;
		for(j=e[v].h;j;j=tp)
		{
			tp=e[j].e;
			if(e[j].t==p)
			  continue;
			e[j^1].t=o;
			e[j].e=e[o].h;
			e[o].h=j;
		}
	}
	return ;
}
void search(int p,int fa)
{
	int i;
	s[p]=0,ts[p]=0,ds[p]=0;
	for(i=e[p].h;i;i=e[i].e)
	{
		if(e[i].t==fa||e[i].t==-1)
		  continue;
		search(e[i].t,p);
		if(p>n)
		  ts[p]=ts[p]+ds[e[i].t],++s[p];
		else
		  ans=ans+s[e[i].t]*ds[p]*2,ds[p]=ds[p]+s[e[i].t];//这里会统计第三种答案
	}
	return ;
}
int main()
{
	int i,j;
	scanf("%d",&n);
	o=n;
	for(i=2;i<=n;++i)
	{
		++o;
		scanf("%d%d",&x,&y);
		add(x,o);
		add(o,x);
		add(o,y);
		add(y,o);
	}
	for(i=1;i<=n;++i)
	{
		ans=0;
		search(i,0);
		for(j=n+1;j<=o;++j)
		{
			if(f[j])
			  continue;
			ans=ans+(s[j]+1)*s[j]*(s[j]-1)+s[j]*ts[j]*2;//统计第一种，第二种
		}
		merge(i);
		printf("%lld\n",ans);
	}
	return 0;
}
```

好长啊(⊙_⊙;)，想法就是合并点之后重新遍历树统计答案，暴力得不能再暴力了！

### 参考代码（正解）

甜点结束，现在开始正餐！

我们发现，一个点的删除，只会影响它的父亲，祖父，曾祖（乐，挺多的）。

大家不要用我的垃圾乱搞合并法，更简单的，我们可以使用并查集直接把它们并起来，在查找父亲的时候也更方便，具体看代码。

我们在最开始的遍历中记录每个点的答案，当它们被删除或者合并的时候，删掉。

而我们对于修改过的父亲，祖父，曾祖，重新算它们的答案，整体思路并不难，对实现有些技巧。

一个困扰过我的问题，我们的答案计算方式，有一个大前提，每一个方点必须有一个父亲圆点，否则会算错的！

但是我们一直再删圆点，若是把根节点删掉了，下面的就没有父亲了怎么办？

愚蠢限制了我的想象！纵观整个过程，点 $n$ 是最后删的，而且对答案是不会有影响的，我们为什么不从一开始就设 $n$ 为根呢？感谢 USACO 的指点。

来，看看代码吧，复杂度 $\Theta(n\alpha(n))$，注释尽量都解释了：

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=2e5+5; 
int n,x,y,c,fa[N<<2],f[N<<2],o,bz[N<<2];
ll m,s[N<<2],ds[N<<2],ts[N<<2],ans[N<<2];
struct edge
{
	int t,e,h;
}e[N<<3];
void add(int u,int v)
{
	++c;
	e[c].t=v;
	e[c].e=e[u].h;
	e[u].h=c;
	return ;
}
int find(int p)//并查集
{
	if(f[p]!=p)
	  f[p]=find(f[p]);
	return f[p];
}
void merge(int x,int y)
{
	x=find(x);
	y=find(y);
	if(x==y)
	  return ;
	f[y]=x;//细节，把p的儿子们并到p的父亲
	return ;
}
void search(int p,int f)
{
	int i;
	fa[p]=f;
	for(i=e[p].h;i;i=e[i].e)
	{
		if(e[i].t==f)
		  continue;
		search(e[i].t,p);
		if(p<=n)
		  ans[p]=ans[p]+ds[p]*s[e[i].t]*2,ds[p]=ds[p]+s[e[i].t];//提前算圆点
		else
		  ++s[p],ts[p]=ts[p]+ds[e[i].t];
	}
	if(p>n)
	  ans[p]=(s[p]+1)*s[p]*(s[p]-1)+s[p]*ts[p]*2;//计算方点
	return ;
}
void update(int p)
{
	int i,u,v,w,o;
	m=m-ans[p];//删掉p点的答案
	u=find(fa[p]);//p的父亲
	o=s[u];//记录一下原本的
	s[u]=s[u]-1+ds[p],ts[u]=ts[u]-ds[p];
	for(i=e[p].h;i;i=e[i].e)
	{
		if(e[i].t==fa[p]||bz[e[i].t])
		  continue;
		ts[u]=ts[u]+ts[e[i].t];
	}
	m=m-ans[u];//去掉父亲的
	ans[u]=(s[u]+1)*s[u]*(s[u]-1)+s[u]*ts[u]*2;//更新父亲的
	m=m+ans[u];//加回新的父亲的
	v=fa[u];//找到祖父
	if(v)//这里没有用暴力的爆搜一遍求第三种答案，而是直接求变化量
	{
		m=m-ans[v];//去掉祖父
		ans[v]=ans[v]-o*(ds[v]-o)*2;//祖父答案去掉旧的
		ds[v]=ds[v]-1+ds[p];//更新ds
		ans[v]=ans[v]+s[u]*(ds[v]-s[u])*2;//加上新的 
		m=m+ans[v];//加回祖父
	}
	w=find(fa[v]);//曾祖了!
	if(w)
	{
		m=m-ans[w];
		ans[w]=ans[w]-s[w]*ts[w]*2;//第二种
		ts[w]=ts[w]-1+ds[p];
		ans[w]=ans[w]+s[w]*ts[w]*2;
		m=m+ans[w];//更新就好了
	}
	for(i=e[p].h;i;i=e[i].e)
	{
		if(e[i].t==fa[p]||bz[e[i].t])
		  continue;
		m=m-ans[e[i].t];//被合并的点将不复存在，删
		merge(u,e[i].t);//注意！儿子并到父亲上，好处理
	}
	bz[p]=1;//p点没了
	if(!ds[p]&&!s[u])
	  bz[u]=1;//如果p点上方的方点只有p一个圆点儿子，那这个方点也没有存在的意义了
	return ;
}
int main()
{
	int i;
	scanf("%d",&n),o=n;
	for(i=2;i<=n;++i)//建图
	{
		++o;
		scanf("%d%d",&x,&y);
		add(x,o),add(o,x);
		add(o,y),add(y,o);
	}
	search(n,0);//聪明！用n做根
	for(i=1;i<=o;++i)
	  f[i]=i,m=m+ans[i];
	for(i=1;i<=n;++i)
	{
		printf("%lld\n",m);
		update(i);//并i点
	}
	return 0;
}
```

完结撒花(●'◡'●)！

---

## 作者：SunsetLake (赞：0)

直接建边边数过多，不好处理。我们可以考虑建一些虚点，让 $u_i$ 和 $n+i$ 连边，$v_i$ 和 $n+i$ 连边。设这些新连的点为白点，与白点有连边的点在原图中一定相连，并且一定是一棵树。删除操作相当于把 $u$ 的子白点连到他的父白点上，使用并查集维护即可。

这时再考虑如何算答案。把三元组 $(a,b,c)$ 变成 $(a,x,b,y,c)$ （$x,y$ 就是白色点），再记 $f_u$ 表示白点 $u$ 的黑儿子个数，分情况讨论一下：

- 当 $x=y$ 时，相当于在 $x$ 的邻点中任选三个，$x$ 的邻点有 $f_x+1$ 个（因为要算上他的父亲）。故对答案的贡献为 $\displaystyle\sum_{x \in white} (f_x+1)f_x(f_x-1)$。
- 当 $x \ne y$ 时，若 $x,y$ 为 $b$ 的儿子，那么相当于在 $x,y$ 中选 $a,c$，贡献为 $\displaystyle\sum_{x,y \in son_b,x \ne y}  f_x f_y$。变一下形，即 $(\sum f_x)^2 - \sum (f_x)^2$。
- 当 $x$ 为 $b$ 父亲，$y$ 为 $b$ 儿子时，相当于我们要在 $x$ 子树中找 $a$，$y$ 子树中找 $c$，其答案为 $2 \times f_x \displaystyle\sum_{b \in son_x}\displaystyle\sum_{y \in son_b}f_y$。乘二是因为三元组是有序的，$(a,c),(c,a)$ 应该被算两遍。

这时再记 $g_{u,u\in black}=\displaystyle\sum_{x\in son_u}f_x$，$h_{u,u\in white}=\displaystyle\sum_{x \in son_u}g_x$。

那么分析一下 $f$ 相当于一级儿子，$g$ 为二级儿子，$h$ 为三级儿子。每次删除一个点会影响他的一级儿子与他的上三级父亲，对于儿子，每个点只会被更新一遍，总复杂度 $O(n)$，对父亲每次只有 $3$ 个，复杂度 $O(1)$。故全局复杂度 $O(n)$。更新把 $h,g,f$ 更新即可。

# code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
int n,vis[200005],ffa[400005],fa[400005];
ll ans,f[400005],g[400005],h[400005];
vector<int>e[400005];
int root(int x){
	if(x==fa[x])return x;
	return fa[x]=root(fa[x]);
}
ll qur(int x){
	if(!x)return 0;
	return (f[x]+1)*f[x]*(f[x]-1)-f[x]*f[x]+2*f[x]*h[x];//统计一个点的答案
}
void dfs(int u,int ft){
	ffa[u]=ft;
	for(auto v:e[u]){
		if(v==ft)continue;
		dfs(v,u);
		if(u<=n)g[u]+=f[v];
		else{
			f[u]++;
			h[u]+=g[v];
		}
	}
}
void del(int u){
	int f1=root(ffa[u]),f2=ffa[f1],f3=root(ffa[f2]);
	ans-=g[u]*g[u];
	ans-=qur(f1)+g[f2]*g[f2]+qur(f3);
	f[f1]--;g[f2]--;h[f3]--;
	for(auto v:e[u]){
		if(v==ffa[u])continue;
		ans-=qur(v);
		fa[v]=f1;
		f[f1]+=f[v];
		
		g[f2]+=f[v];
		
		h[f1]-=f[v];h[f1]+=h[v];
		
		h[f3]+=f[v];
	}
	ans+=qur(f1)+g[f2]*g[f2]+qur(f3);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;++i){
		int a,b;
		cin>>a>>b;
		e[a].pb(n+i);e[n+i].pb(a);
		e[b].pb(n+i);e[n+i].pb(b);
	}
	dfs(n,0);
	for(int i=1;i<=n;++i)ans+=g[i]*g[i];
	for(int i=n+1;i<=2*n-1;++i)ans+=qur(i);
	for(int i=n+1;i<=2*n-1;++i)fa[i]=i;
	cout<<ans<<endl;
	for(int i=1;i<n;++i){
		del(i);//每次先删点进行更新
		cout<<ans<<endl;
	}
	return 0;
}
```


---

