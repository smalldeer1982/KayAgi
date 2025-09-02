# Propagating Edges

## 题目描述

给定一个有 $N$ 个顶点、$0$ 条边的无向图。请处理 $Q$ 个如下类型的查询：

- add 查询（$type = 1, u, v$）：如果 $u$ 和 $v$ 之间没有边，则在 $u$ 和 $v$ 之间添加一条边。
- complete 查询（$type = 2, u, v = 0$）：对于所有顶点对 $a, b$，如果 $u, a, b$ 三者连通，且 $a, b$ 之间没有边，则在 $a, b$ 之间添加一条边。
- check 查询（$type = 3, u, v$）：给定 $u, v$，如果 $u$ 和 $v$ 之间直接有边，则输出 `Yes`，否则输出 `No`。

## 说明/提示

### 限制条件

- $2 \leq N \leq 100,\!000$
- $1 \leq Q \leq 200,\!000$
- $type_i = 1, 2, 3$
- $1 \leq u_i \leq N$
- 对于 add 和 check 查询，$1 \leq v_i \leq N$ 且 $u_i \neq v_i$
- 对于 complete 查询，$v_i = 0$
- 输入的所有值均为整数

### 样例说明 1

在第 $1$、$2$ 个查询中，分别在 $(1, 2)$、$(2, 3)$ 之间添加了边。然后，在第 $5$ 个查询中，在 $(1, 3)$ 之间添加了边。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 6
1 1 2
1 2 3
3 1 2
3 1 3
2 1 0
3 1 3```

### 输出

```
Yes
No
Yes```

## 样例 #2

### 输入

```
3 6
2 3 0
3 1 3
1 3 1
2 3 0
1 1 2
3 2 1```

### 输出

```
No
Yes```

## 样例 #3

### 输入

```
8 20
1 3 6
2 6 0
2 2 0
2 7 0
1 7 3
3 2 6
1 4 2
3 3 7
1 2 6
2 4 0
2 2 0
3 3 1
2 8 0
2 8 0
1 8 2
2 7 0
3 5 4
1 4 2
3 5 7
3 2 3```

### 输出

```
No
Yes
No
No
No
Yes```

# 题解

## 作者：suzhikz (赞：3)

观察一下，发现第二个操作就是把一个块变成完全图。

而询问要求两个点直接连边。

如果把一个块变成完全图，比较好的想法就是把这些东西用一个并查集存起来。

但是有的时候我们有边的两个点不一定能组成一个完全图。

发现这种情况两个点有边当且仅当有一操作把这两个点连起来了，于是用 map 存一下即可。

我们先用数组存边，然后二操作时在遍历这个联通快，记得弹出用过的边，这样复杂度最多就是边的个数，搜索复杂度 $O(m)$。

加上 map，复杂度是 $O(n\log_2n)$。


```cpp
#include<iostream>//Are dreams merely lost wings in the concrete jungle？
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<string>
#include<deque>
#include<stack>
#include<queue>
#include<vector>
#include<stdio.h>
#include<map>
#include<set>
#include<string.h>
#include<random>
#include<time.h>
#include<stdlib.h>
#include<bitset>
#define il inline
#define reg register
#define ll long long
#define popcount __builtin_popcount
using namespace std;
//#define int __int128
inline void read(int &n){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}n=x*f;}
inline void read(ll &n){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}n=x*f;}
const int N=1e5+5; 
int n,m,fa[N];
vector<int>g[N];
map<int,int>ma[N];
int find(int x){
	if(fa[x]==x)return x;return fa[x]=find(fa[x]);
}
int rt;
void dfs(int x){
	fa[find(x)]=find(rt);
	queue<int>q;
	for(int i=g[x].size()-1;i>=0;i--){
		int v=g[x][i];
		if(g[v].size())
		q.push(v);
		g[x].pop_back();
	} 
	while(!q.empty()){
		int x=q.front();q.pop();
		if(g[x].size())dfs(x);
	}
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)fa[i]=i;
	int op,u,v;
	while(m--){
		read(op);read(u);
		read(v);
//		if(op!=2)read(v);
		if(op==1){
			ma[u][v]=ma[v][u]=1;
			u=find(u);v=find(v);
			g[u].push_back(v);g[v].push_back(u);
		}else if(op==2){
			rt=u;dfs(find(u)); 
		}else{
			if(find(u)==find(v)||ma[u][v]){
				puts("Yes");
			}else{
				puts("No");
			}
		}
	}
	return 0;
}
/*
10 16
1 3 7
1 1 6
3 10 3
1 3 10
1 5 10
2 7
2 6
3 6 10
3 10 3
1 4 6
2 1
2 3
2 3
1 4 10
2 10
3 6 7
*/
```

---

## 作者：SuperCowHorse (赞：1)

不知道为什么要用启发式合并，明明不用也能过呀？

Update：被 Hack 了。看来还是要的。

---

首先看到题目，很容易想到并查集。

对于操作 $1$，我们用一个 `map`，记录 $u,v$ 之间是否有连边，然后再用并查集，把它俩所属集合给合并了。

对于操作 $2$，我们可以定义一个 $bel$ 数组，$bel_u$ 表示 $u$ 所属的**团**，即集合 $bel_u$ 中，所有元素两两之间都已连边。暴力修改并查集中的所有元素的 $bel$ 值，表示在 $bel_u$ 集合中，所有的点之间都有连边。

对于操作 $3$，只需要判定 $bel_u$ 和 $bel_v$ 是否相等，或者 `map` 中是否存在 $u,v$ 的边即可。

这里用了 $n$ 个 `vector`，维护每一个并查集中的元素。

Code:
```cpp
#include<bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
const int maxn=1e5+5;
int n,Q,fa[maxn],t[maxn],bel[maxn];
vector<int>now[maxn];
map<pair<int,int>,bool>p;
inline void init(){for(int i=1;i<=n;++i){fa[i]=i;bel[i]=i;now[i].pb(i);}}
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void merge(int p,int q){
	int u=find(p),v=find(q);
	if(u==v) return;
	if(v!=0){//操作 1
		fa[v]=u;
		for(int i=0;i<now[v].size();++i){
			now[u].pb(now[v][i]);//合并并查集
		}
		now[v].clear();
	}
	else{//操作 2
		for(int i=0;i<now[u].size();++i){
			bel[now[u][i]]=u;//暴力修改 bel 值
		}
	}
}
signed main(){
	scanf("%d%d",&n,&Q);
	init();
	for(int op,u,v;Q;--Q){
		scanf("%d%d%d",&op,&u,&v);
		if(op==1){
			p[{u,v}]=p[{v,u}]=1;//用 map 记录 u,v 之间有连边
			merge(u,v);
		}
		else if(op==2){
			merge(u,v);
		}
		else{
			printf(bel[u]==bel[v]||p[{u,v}]?"Yes\n":"No\n");
		}
	}
	return 0;
}
```
---

以上是错误的解法。可以被 [此帖](https://www.luogu.com.cn/discuss/994775) Hack 成 $O(n^2)$。以下是正解。

操作一仍和之前一样。

操作二我们记录一个 $bel$ 数组，表示 $x$ 节点现在在哪一个团中。使用启发式合并，我们可以将复杂度减至 $O(n\log n)$。

操作三需要运用并查集找祖先的思想，我们把 $bel$ 数组看成并查集的 $fa$ 数组，把团之间的连边看成是并查集的连边，然后用 $\operatorname{find}$ 查询即可。

具体见注释。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int n,Q,fa[maxn],g[maxn],bel[maxn];
vector<int>now[maxn];
inline void init(){
	for(int i=1;i<=n;++i){
		fa[i]=i;g[i]=1;bel[i]=i;now[i].push_back(i);
	}
}
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void merge(int u,int v){
	u=find(u);v=find(v);
	if(v!=0){//操作 1
		if(u==v) return;
		if(g[u]<g[v]) swap(u,v);
		g[u]+=g[v];fa[v]=u;
		for(auto x:now[v]) now[u].push_back(x);//启发式合并
		now[v].clear();
	}
	else{
		for(auto x:now[u]) bel[x]=u;
		now[u].clear();now[u].push_back(u);//注意！这里要把数组清空，否则可能重复赋值，还会被卡成 O(n^2)
	}
}
map<int,bool>mp[maxn];
inline int find1(int x){return x==bel[x]?x:bel[x]=find1(bel[x]);}//类似并查集，找 x 所属的团
signed main(){
//	freopen("a.out","r",stdin);
	scanf("%d%d",&n,&Q);init();
	for(int op,u,v,i=1;i<=Q;++i){
		scanf("%d%d%d",&op,&u,&v);
		if(op==1){
			merge(find1(u),find1(v));
			mp[u][v]=mp[v][u]=1;
		}
		else if(op==2){
			merge(find1(u),v);
		}
		else{
			printf((mp[u][v]||find1(u)==find1(v))?"Yes\n":"No\n");
		}
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：1)

看着就很像并查集的题，但是普通的并查集不好处理。我们考虑像 kruskal 重构树一样操作，每次合并连边时若 $u,v$ 不在同一连通块，建新点连 $u,v$ 并查集的祖先。

![](https://oi-wiki.org/graph/images/mst6.png)

（图片来源：OI-wiki 克鲁斯卡尔重构树）

每次操作 $2$ 时，我们把点 $u$ 所在连通块当前的祖先打上时间戳，如图中的 $1,2,4$。我们有结论：如果两个点 $u,v$ 之间的边是通过操作 $2$ 连的，那么根到 $\operatorname{LCA}(u,v)$ 的路径上必定有一点的时间戳小于当前时间。证明也简单：若存在，则证明 $u,v$ 在一个连通块时进行过操作 $2$；若不存在，则 $u,v$ 在合并为一个连通块后没有过包含 $u,v$ 的操作 $2$。

那么我们写个 kruskal 重构树和 $\operatorname{LCA}$，就可以 AC 这道黑题。时间复杂度 $\mathcal O(n \log n)$。

注意特判没有操作 $2$ 但是两点通过操作 $1$ 连边的情况。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 04.01.2024 21:08:42
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,m,u,v,op,fa[N],a[N],dep[N],tot,f[N][22];vector<int> g[N]; vector<tuple<int,int,int>> p;map<pair<int,int>,int> mp;
int fd(int x){return x == fa[x] ? x : fa[x] = fd(fa[x]);}
void dfs(int u,int fa,int w){
    w = min(a[u],w),a[u] = w,f[u][0] = fa,dep[u] = dep[fa] + 1;
    for(int i = 1;i <= 20;i ++) f[u][i] = f[f[u][i-1]][i-1];
    for(int v : g[u]) dfs(v,u,w);
}int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u,v);
    while(dep[u] > dep[v]) u = f[u][__lg(dep[u] - dep[v])];
    for(int i = 20;i >= 0;i --) if(f[u][i] != f[v][i]) u = f[u][i],v = f[v][i];
    return (u == v ? u : f[u][0]);
}void los(){
    cin >> n >> m,tot = n;
    for(int i = 1;i <= 2*n;i ++) fa[i] = i;
    for(int i = 1;i <= m;i ++){
        cin >> op >> u >> v;
        if(op == 1){
            mp[{u,v}] = mp[{v,u}] = 1;
            if(fd(u) != fd(v)) 
                u = fd(u),v = fd(v),fa[u] = fa[v] = ++tot,g[tot].push_back(u),g[tot].push_back(v),a[tot] = 1e9;
        }else if(op == 2) a[fd(u)] = min(a[fd(u)],i);
        else if(fd(u) != fd(v)) p.emplace_back(0,0,i); else if(mp[{u,v}]) p.emplace_back(-1,-1,i);
        else p.emplace_back(u,v,i);
    }for(int i = 1;i <= tot;i ++) if(fd(i) == i) dfs(i,0,1e9);
    for(auto [u,v,i] : p){
        if(u == -1) cout << "Yes\n"; else if(!u) cout << "No\n";
        else cout << (a[lca(u,v)] <= i ? "Yes\n" : "No\n");
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```


---

## 作者：Zpair (赞：0)

并查集，直接记录每个连通块有哪些团，连边就启发式合并一下。

缩点的话就遍历一遍，把当前连通块的所有团缩成一个。

非团边随便记一下就行。

然后发现团也可以用并查集维护，就做完了，时间复杂度为 $O(n \log n)$。

---

## 作者：FLAMEs_ (赞：0)

睡一觉，会大大提升你的状态。去睡一觉吧，没准有些题就想出来了。

---

本文提供一个短小精悍的解法。

对于 ```add``` 操作的边，我们用一个 ```map``` 去记录它的出现（因为这类边比较特殊，可以直接记录），然后对于两个连通块进行启发式合并。这个过程中，我们需要用 $n$ 个 ```vector``` 记录每个点在哪个连通块里。

对于一次 ```complete``` 操作，我们发现，我们可以给点 $u$ 对应的 ```vector``` 当中的所有点全部丢入一个 ```set```，这个 ```set``` 表示当前容器中的节点能够组成一个团。

然后，将原来 ``` vector``` 当中的所有点全部打上点 $u$ 的标记，同时，清空原来的 ```vector``` 以保证每次合并的时间复杂度。

这时我们发现，对于一个以点 $u$ 为根的连通块内的点，我们将其分为了两部分。一部分是 ```set``` 内的点，表示这个点在所在连通块的团中，而另一部分在 ```vector``` 当中的点则代表不在。

对于一次查询，我们只需要查询这两个点之间是否有 ```add``` 操作带来的边，或者两个点的标记的值是否相等即可。

复杂度 $O(n \log^2 n)$。

又及：你可以不用将点丢入 ```set``` 内部，但是这样的话你无法清空 ```vector```，跑的会比较慢（亲测）。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> Pii;
const int N = 5e5 + 5;
map <Pii, bool> os;
int n, q, fa[N], siz[N], bel[N];
vector <int> c[N]; set <int> s[N];
int find(int u) {return (fa[u] == u ? u : fa[u] = find(fa[u]));}
inline void Merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if(fx == fy) return ;
	if(siz[fy] > siz[fx]) swap(fx, fy);
	siz[fx] += siz[fy]; fa[fy] = fx;
	for(auto p : c[fy]) c[fx].push_back(p);
	for(auto p : s[fy]) c[fx].push_back(p);
	c[fy].clear();
}
inline void grow(int x) {
	int fx = find(x);
	for(auto p : c[fx]) s[fx].insert(p), bel[p] = fx;
	c[fx].clear();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; ++ i) fa[i] = i, siz[i] = 1, c[i].push_back(i), s[i].insert(i), bel[i] = i;
	for(int i = 1, opt, u, v; i <= q; ++ i) {
		cin >> opt >> u >> v;
		if(opt == 1) {
			os[{u, v}] = os[{v, u}] = true;
			Merge(u, v);
		} else if(opt == 2) grow(u);
		else {
			if(os[{u, v}] || os[{v, u}] || bel[u] == bel[v]) cout << "Yes\n";
			else cout << "No\n";
		}
	}
	return 0;
}
```

---

