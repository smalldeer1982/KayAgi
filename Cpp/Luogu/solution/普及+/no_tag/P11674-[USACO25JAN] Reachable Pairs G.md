# [USACO25JAN] Reachable Pairs G

## 题目描述

考虑一个无向图，包含 $N$ 个结点，编号为 $1\dots N$，以及 $M$ 条边（$1\le N\le 2\cdot 10^5$，$0\le M\le 4\cdot 10^5$）。给定一个位串 $s_1s_2\dots s_N$。对于每一个 $t\in [1,N]$，在时刻 $t$ 时，

- 如果 $s_t=0$，则从图中移除结点 $t$。
- 如果 $s_t=1$，则从图中移除结点 $t$，并在结点 $t$ 被移除之前的每对邻居之间添加一条边。

注意在这两种情况下，当一个结点从图中被移除时它的所有相邻边也会被移除。

计算在每一个时刻 $1\ldots N$ 之前，可以通过一组边相互到达的结点对数。

## 说明/提示

样例 1 解释：

在移除之前，所有结点对之间都可以相互到达。结点 $1$ 被移除后，结点 $2$ 和 $3$ 之间添加了一条边，因此它们仍然可以相互到达。

样例 2 解释：

在移除之前，所有结点对之间都可以相互到达。结点 $1$ 被移除后，结点 $2$ 和 $3$ 之间不再可以相互到达。

- 测试点 $4\sim 6$：$N\le 100$。
- 测试点 $7\sim 8$：所有 $s_i$ 均等于 $0$。
- 测试点 $9\sim 11$：所有 $s_i$ 均等于 $1$。
- 测试点 $12\sim 23$：没有额外限制。

## 样例 #1

### 输入

```
3 2
111
1 2
1 3```

### 输出

```
3
1
0```

## 样例 #2

### 输入

```
3 2
000
1 2
1 3```

### 输出

```
3
0
0```

## 样例 #3

### 输入

```
7 8
1101101
6 2
1 2
2 3
6 3
1 3
1 7
4 5
2 7```

### 输出

```
11
7
4
2
1
1
0```

# 题解

## 作者：SmokingTurtle (赞：16)

## 前言

本题属于思维题，本人在结束后 10min 想到了正确做法，写个题解纪念一下。

## 思路

我们仔细观察题目的两个操作，发现包括了删除节点和加入边，一个是删除一个是加入，不是很好处理，于是思考如何转化。

手动模拟一下样例，我们发现“在节点 $t$ 被移除之前的每对邻居之间添加一条边”这个操作不改变连通性，因此我们可以考虑将这个操作懒标记掉。

具体来说，对于 $s_t=1$ 的情况，我们可以将其变为“将节点 $t$ 假装删除”，使得它依旧维持着连通性，但是不计入答案。

我们现在要处理的操作是删除节点和假装删除节点。由于都是删除类操作，我们将时间逆序，变为加入。

此时，我们的操作变成了将假装删除的点添加回来和添加一个节点。

这个问题显然可以使用并查集来维护。

## 细节部分

在并查集中，我们重新定义“大小”这个概念，不是指并查集中有多少个点，而是指并查集中有多少个没有被虚假删除的点，这样方便统计答案。

接着，我们考虑加入一个节点的时候它的哪些邻边应该被加入。这当然是当对面的节点已经被加入以后。

具体的，加入节点 $u$ 的时候，对于他的一条邻边 $u\harr v$，这条边被加入当且仅当 $v$ 此时已经在图里。这包含两种情况：要么 $v>u$，要么 $s_v=1$ （$v$ 只是被虚假删除了）。这样我们就不能按秩合并了，但是加上路径压缩，我们依然能够保证时间复杂度在 $O(m \log n)$ 级别，能够通过本题。

## 概括

总结一下，我们并查集初始每个点是一个集合，但是“大小”为 $0$。接着，倒序遍历每个点，对于他的所有邻边，如果对面的点比自己编号大或者属于虚假删除的点，那么加上这条边。最后，将这个点所在的并查集大小加 $1$。在这个期间维护答案。

## $\color{Red}坑点$

1. 如果两个假装删除的点之间有边，那么在开始计算之间就应该加上。
> 对应的 hack 数据：
> ```
> 4 3
> 0011
> 3 1
> 1 2
> 2 4
> ```
>
> 正确答案
> ```
> 6
> 1
> 0
> 0
> ```

2. 十年 OI 一场空，不开 long long 见祖宗！


## 代码时间

本人比较懒，没有加注释，凑合看吧。

代码曾经有防 CTJ。

```cpp
#include<iostream>
#include<vector>
using namespace std;
int n,m,fa[200005],sz[200005];
long long sum,ans[200005];
vector<int> g[200005];
bool s[200005];
int get(int u){return (u==fa[u])?u:(fa[u]=get(fa[u]));}
void c(int u,int v)
{
	if(get(u)!=get(v))
		u=fa[u],v=fa[v],
		fa[u]=v,
		sum+=(1ll*sz[u]*sz[v]),
		sz[v]+=sz[u]; 
}
void add(int u)
{
	u=get(u);
	sum+=sz[u];
	sz[u]++;
}
int main()
{
	cin>>n>>m;
	char ch;
	for(int i=1;i<=n;i++)
		fa[i]=i,sz[i]=0;
	for(int i=1;i<=n;i++)
		cin>>ch,s[i]=(ch=='1');
	for(int i=1,u,v;i<=m;i++)
	{
		cin>>u>>v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
		if(s[u] && s[v])
			c(u,v);
	}
	for(int i=n;i>=1;i--)
	{
		for(int j:g[i])
			if(j>i || s[j]==1)
				c(i,j);
		add(i);
		ans[i]=sum;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<endl;
}
```

## 吐槽

那句 “十年 OI 一场空，不开 long long 见祖宗” 由于一开始试图使用 `\Huge` + `\texttt` 表示强调，并且忘了加空格，被打回了 $4$ 次，悲

上面这句吐槽因为一开始滥用代码块又被打回了一次，悲

---

## 作者：Register_int (赞：6)

瓶颈显然在于 $1$ 操作。但实际上可以这样转化：最初将所有点设为白色，$0$ 操作不变，$1$ 操作则为将该点染黑，查询可达的白色点对数量。

倒序处理询问，相当于加边并维护连通块内白点数量，并查集简单维护即可。复杂度 $O(n\alpha(n))$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, m, fa[MAXN], sz[MAXN]; ll res, ans[MAXN];

int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }

inline 
void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return ; fa[v] = u;
	res -= (ll)sz[v] * (sz[v] - 1) / 2;
	res -= (ll)sz[u] * (sz[u] - 1) / 2, sz[u] += sz[v];
	res += (ll)sz[u] * (sz[u] - 1) / 2;
}

inline 
void add(int u) {
	u = find(u), res += sz[u]++;
}

char s[MAXN]; vector<int> g[MAXN];

int main() {
	scanf("%d%d%s", &n, &m, s + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		g[u].emplace_back(v), g[v].emplace_back(u);
		if (s[u] == '1' && s[v] == '1') merge(u, v);
	}
	for (int u = n; u; u--) {
		if (~s[u] & 1) for (int v : g[u]) if (v > u || s[v] == '1') merge(u, v);
		add(u), ans[u] = res;
	}
	for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
}
```

---

## 作者：MPLN (赞：4)

## 部分分思路
$N\le100$ 时，考虑每次暴力 DFS ，$O(nm)$ 。

认真读题，很容易想到要用并查集维护点的连接情况。
> 如果  $s_t=0$ 
> ，则从图中移除结点 $t$    
> 如果  $s_t=1$ 
，则从图中移除结点 $t$
，并在结点 $t$
 被移除之前的每对邻居之间添加一条边

观察题目，这意思不就是如果  $s_t=1$ ，移除 $t$ 不可能分裂所在集合，没啥影响！设 $t$ 的祖宗是 $ft$ ，移除后只需要让 $ans$ 减去 $(size[ft]-1)$ （ $t$ 可以到的点数量）就可以了。 

再考虑  $s_i=0$ 的情况。正难则反，倒着加点可以很轻松地维护：每次加点时一条条连接本来有的边，过程中用乘法原理给被连起来的不同集合中的节点组对，然后增加答案。  

至此，我们成功拿到了所有部分分，大概占 50%，~~是不是很水~~。

# 正解
其实正解就是整合一下 $s_i=1$ 和 $s_i=0$ 的方法。但是一个正着走一个反着走，怎么放一起？倒着加点显然更好。

### 初始化

最初让图中只有节点，没有边。
    
对于节点 $i$，若 $s_i=1$ ，可以在最开始赋予 $i$ 一个状态：“仅连接” （此时已经被删除），保留节点和与其他 “仅连接” 点的相连边。集合中的其他点仍然通过 $i$ 相连，但是不能和 $i$ 组对。

为了方便，我们相对应地给被删除之后的 $s_i=0$ 的节点赋予状态 “删除” ，仅保留单个点，相连边不存在。

由于只能统计 **非(“仅连接”或”删除“)状态节点** 的答案。不妨称其为 "激活" 节点。因此我们可以改变原本代表集合大小的 $size$ 数组的意义，这里改名为 $alive$ ：$alive[i]$ 表示 $i$ 统治的集合中有多少个 “激活” 节点，只有“激活”节点才会在计算过程中计入答案，否则只是连接作用。

### 遍历

我们每遍历到一个节点 $i$ ，就需要往图中加入该点原本边集中的边：连接 $i$ 和非同集的 “仅连接” 或 “激活” 节点（其实就是合并集合）。过程中根据两个集合的 $alive[i]$ 增加答案。最后取消 $i$ 的“仅连接”或“删除”状态，再激活 $i$ 即可。

于是我们可以写出代码：加入节点!

```cpp
void cnct(int x) { // 连边
    no[x] = ny[x] = 0; // 状态清除，不再是“删除”或“仅连接”状态
    int fx = find(x);
    for (int v : e[x]) {
        if (no[v]) continue;  // 如果v是“删除”状态，跳过（不能通过这个节点走）
        int fv = find(v);
        if (fv == fx) continue; // 同一组的不需要再合并
        ans += alive[fv] * alive[fx]; // 乘法原理连接不同集合节点
        fa[fv] = fx;  // 合并两组
        alive[fx] += alive[fv];  // 增加本集合的激活节点数量
    }
    ans += alive[fx]; // 点x连接到自己所在集合内的所有激活节点
    alive[fx]++; // 激活节点x
}
```

## Code
时间复杂度约为  $O(n+m)$ ，空间复杂度 $O(n)$  
赛场代码改了改，加上注释，应该很好理解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, fa[200010], alive[200010],ans = 0, output[200010];
bool c[200010], no[200010], ny[200010];
char a[200010];
vector<int> e[200010];
int find(int x) { return fa[x] = (fa[x] == x) ? x : find(fa[x]); }
void cnct(int x) { // 连边
    no[x] = ny[x] = 0; // 状态清除，不再是“删除”或“仅连接”状态
    int fx = find(x);
    for (int v : e[x]) {
        if (no[v]) continue;  // 如果v是“删除”状态，跳过（不能通过这个节点走）
        int fv = find(v);
        if (fv == fx) continue; // 同一组的不需要再合并
        ans += alive[fv] * alive[fx]; // 乘法原理连接不同集合节点
        fa[fv] = fx;  // 合并两组
        alive[fx] += alive[fv];  // 增加本集合的激活节点数量
    }
    ans += alive[fx]; // 点x连接到自己所在集合内的所有激活节点
}
signed main() {
    cin >> n >> m;
    scanf("%s", a + 1);
    for (int i = 1; i <= n; i++) {
        c[i] = a[i] == '1';
        fa[i] = i;
        alive[i] = 0;  // 初始没有激活
        if (c[i]) ny[i] = 1;  // 如果c[i]为1，为“仅连接”状态
        else no[i] = 1;  // 否则为“删除”状态
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) if (ny[i]) cnct(i); // 预合并
    // 反向遍历
    for (int i = n; i >= 1; i--) {
        if (c[i]) {
            cnct(i);     // 合并
            alive[find(i)]++; // 激活
        } else {
            cnct(i);     // 合并
            alive[find(i)]++; // 激活
        }
        output[i] = ans;
    }
    for (int i = 1; i <= n; i++) 
        cout << output[i] << endl;
    return 0;
}
```
###### ~~第一次进金组还切题了，开心~~

---

## 作者：cjh20090318 (赞：3)

Gold 组唯一过的一道题。

## 题意

参见[题目描述](https://www.luogu.com.cn/problem/P11674)。

## 分析

移除节点并不方便维护连通性，考虑倒序添加用并查集维护。

考虑移除这两点操作的本质是什么。

所有 $s_t = 0$ 的情况是比较好做的，直接加边即可。

- $s_t = 0$，删除这个点并断开和这个点相连的所有边，倒序处理时只需要加上这个点并和所有边相连。
- $s_t = 1$，移除这个点但是其他点的连通性却没有改变，也就是说这个“实点”转变成了“虚点”，反着做只需要给这个连通块的点数加一。

在开始询问以前只需要添加连接两个虚点的边即可。

使用按秩合并和路径压缩并查集维护总点数和实点数，时间复杂度 $O(N+M)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<vector>
#define MAXN 200002
using namespace std;
typedef long long LL;
int n,m;
bool s[MAXN],vis[MAXN];
vector<int> G[MAXN];
struct dsu{
	int fa[MAXN],sz[MAXN],z[MAXN];
	void init(){*fa=*sz=*z=0;for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1,z[i]=0;}
	int find(const int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	int size(const int x){return z[find(x)];}//当前连通块实点个数。
	void add(const int x){++z[find(x)];}//连通块添加一个实点。
	void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return;
		if(sz[x]<sz[y]) swap(x,y);
		fa[y]=x,sz[x]+=sz[y],z[x]+=z[y];
	}
	bool same(const int x,const int y){return find(x)==find(y);}
}S;
LL ans[MAXN];
int main(){
	scanf("%d%d ",&n,&m),S.init();
	for(int i=1;i<=n;i++) s[i]=getchar()^'0';
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	for(int u=1;u<=n;u++)if(s[u])for(const int v:G[u])if(s[v]) S.merge(u,v);//两个都为虚点，合并。
	LL now=0;
	for(int u=n;u>0;--u){
		if(s[u]){
			int z=S.size(u);
			now-=z*(z-1ll)/2,S.add(u),now+=z*(z+1ll)/2;
		}
		else{
			for(const int v:G[u])if((s[v]||v>u)&&!vis[S.find(v)]){
				int z=S.size(v);
				now-=z*(z-1ll)/2;
				vis[S.find(v)]=1;//删除每个连通块原来贡献的答案，标记防止重复。
			}
			S.add(u);
			for(const int v:G[u])if(s[v]||v>u)S.merge(u,v),vis[S.find(v)]=0;//连通。
			int z=S.size(u);
			now+=z*(z-1ll)/2;//更新答案。
		}
		ans[u]=now;
	}
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：zhaomumu1218 (赞：3)

## 分析
正面模拟有分裂操作，不好维护，考虑时间倒流。   
先把 $1$ 类点和与它相邻的 $1$ 类点合并。倒序枚举 $u$ 点，把它与周围已存在的点和 $1$ 类点合并，并计算贡献。
## 细节
1. 合并时 $size$ 要加到 $father$ 上。
2. 计算贡献时自己联通块的大小要加 $1$。
3. 要开 `long long`。
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
int n,m,a[maxn],fa[maxn],ans[maxn],nans,sz[maxn];
vector<int>e[maxn];
int find_root(int u){ //并查集基本操作 
	if(fa[u]==0) return u;
	return fa[u]=find_root(fa[u]);
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%1lld",a+i);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%lld%lld",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	} 
	for(int i=1;i<=n;i++) for(int v:e[i]) if((a[v]&&a[i])&&find_root(i)!=find_root(v)) fa[find_root(i)]=find_root(v); //把所有相邻的1类点合并 
	for(int i=n;i>=1;i--){
		nans+=sz[find_root(i)],sz[find_root(i)]++; //计算自己的贡献 
		for(int v:e[i]){
			if((v>=i||a[v])&&find_root(i)!=find_root(v)){
				int sz1=sz[find_root(i)],sz2=sz[find_root(v)];
				nans=nans+sz1*sz2;
				sz[find_root(i)]+=sz[find_root(v)];
				fa[find_root(v)]=find_root(i); //合并+计算贡献 
			}
		}
		ans[i]=nans;
	}
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
    return 0;
}
//10 10
//1101100000
//8 1
//5 4
//9 6
//2 9
//7 2
//4 3
//2 8
//2 8
//10 1
//1 10
```

---

## 作者：hyk2019 (赞：2)

数无向图的可达点对数，一般**拆成多个连通块**，对每个连通块设连通块中的点数为 $n$，那么该连通块内的点对都是可达的，计数为 $\frac{n(n-1)}2$，再加起来就可以了。

因此，我们从**连通块**起手研究这个问题。$0$ 操作就是普通的删点，而 $1$ 操作是删了点之后还要在原来与它相邻的点之间两两连边。

如何**转化** $1$ 操作？我们可以建一个**虚点**，让原来和被删除结点连有边的结点**向这个虚点连边**，而虚点**不算连通数**。这可以通过为每个未被删除的点**赋点权** $1$，然后在删除的时候将点权设为 $0$ 来实现。这样，一个连通块的连通数变成了 $\frac{n(n-1)}2$，其中 $n$ 表示**点权和**。

需要注意的是，只有 $0$ 操作才会真正地把点删掉，$1$ 操作**只要修改点权即可**，因此可以**提前**将两头都是 $1$ 操作结点的边**连起来**。

处理删除问题的经典思路：**正难则反**。我们把删边操作变成加边操作，反着来处理就可以了。初始每个点的点权都是 $0$，每处理一个时间点，就把对应点的点权设为 $1$；连通块及其点权和可以利用**按秩合并**的并查集维护，这样可以保证时间复杂度为严格 $O(N\log N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int N, M;
char p[200005];
int fa[200005], sz[200005], dp[200005];
long long ans, anv[200005];
long long cal(long long x) {
	return (x - 1) * x / 2;
}
int find(int u) {
	while(u ^ fa[u])
		u = fa[u];
	return u;
}
void merge(int x, int y) {
	if((x = find(x)) == (y = find(y)))
		return;
	if(dp[x] > dp[y])
		swap(x, y);
	ans -= cal(sz[x]) + cal(sz[y]);
	sz[fa[x] = y] += sz[x];
	ans += cal(sz[y]);
	dp[y] = max(dp[y], dp[x] + 1);
}
void update(int u) {
	for(; u ^ fa[u]; u = fa[u])
		sz[u] ++;
	ans -= cal(sz[u]);
	sz[u] ++;
	ans += cal(sz[u]);
}
struct Edge {
	int x, y, t;
	bool operator<(Edge b) const {
		return t > b.t;
	}
} es[400005];
int main() {
	scanf("%d%d%s", &N, &M, p + 1);
	for(int i = 1; i <= N; i ++)
		fa[i] = i;
	for(int i = 0; i < M; i ++) {
		scanf("%d%d", &es[i].x, &es[i].y);
		es[i].t = 0x7fffffff;
		if(p[es[i].x] == '0')
			es[i].t = min(es[i].t, es[i].x);
		if(p[es[i].y] == '0')
			es[i].t = min(es[i].t, es[i].y);
		if(es[i].t == 0x7fffffff)
			merge(es[i].x, es[i].y), es[i].t = -1;
	}
	sort(es, es + M);
	for(int t = N, i = 0; t; t --) {
		for(; es[i].t == t; i ++)
			merge(es[i].x, es[i].y);
		update(t);
		anv[t] = ans;
	}
	for(int i = 1; i <= N; i ++)
		printf("%lld\n", anv[i]);
	return 0;
}
```

至于为什么写按秩合并，其实主要是怕标记操作麻烦，不想路径压缩，又要保证时间复杂度而已。

---

## 作者：Lijiangjun4 (赞：1)

# P11674 题解
### 12 pts，$n \leq 500$
考虑数据范围，可以直接根据题意进行暴力模拟即可。答案为 $\Sigma\dfrac{size(size-1)}{2}$，其中 $size$ 表示连通块的大小，可以用并查集来维护。复杂度 $O(n^3)$，代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
namespace io{//快读快写
long long read()
{
	long long res=0,neg=1;
	char c='\0';
	while((c=getchar())<'0'||c>'9')
	{
		if(c=='-') neg=-1;
	}
	while(c>='0'&&c<='9')
	{
		res=(res<<1)+(res<<3)+c-'0';
		c=getchar();
	}
	return res*neg;
}
void uwrite(long long x)
{
	if(!x) return;
	uwrite(x/10);
	putchar(x%10+'0');
	return;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	if(x==0)
	{
		putchar('0');
		return;
	}
	uwrite(x);
	return;
}
void writel(long long x)
{
	write(x);
	putchar('\n');
}
void writes(long long x)
{
	write(x);
	putchar(' ');
}
}//namespace io
using namespace io;
set<int> e[200005];
bool s[200005];
int fa[200005];
int n,m;
void pre()
{
	for(int i=1;i<=n;i++) fa[i]=i;
}
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void join(int x,int y)
{
	x=find(x),y=find(y);
	fa[x]=y;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		s[i]=getchar()-'0';
	}
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		e[x].insert(y);
		e[y].insert(x);
	}
	for(int i=1;i<=n;i++)
	{
		long long ans=0;
		pre();
		for(int j=1;j<=n;j++)
		{
			for(auto k:e[j])
			{
				join(j,k);
			}
		}
		for(int j=i;j<=n;j++)
		{
			for(int k=j+1;k<=n;k++)
			{
				if(find(j)==find(k)) ans++;
			}
		}
		writel(ans);
		if(s[i])
		{
			for(auto j:e[i])
			{
				for(auto k:e[i])
				{
					if(j!=k)
					{
						e[j].insert(k);
						e[k].insert(j);
					}
				}
			}
		}
		for(int j=1;j<=n;j++) e[j].erase(i);
		e[i].clear();
	}
	return 0;
}

```
### 8 pts，所有 $s_i$ 均等于 $0$
这个部分分没有删完再建的操作，比较简单。一般来说，直接进行删除操作是比较难以维护的，我们要采用正难则反的思想来解决。

将删除操作反过来，用并查集维护连通块，从 $n$ 到 $1$ 倒序加入节点 $i$，对于节点 $i$，与和自己相邻的**编号大于自己的**节点相连（因为这个节点已经被加入图中了，而编号小于的还没被加入），每次连接对答案的贡献就是两个连通块的大小的积（**注意特判，如果已经在一个连通块了，就没有贡献了**）。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
namespace io{//快读快写
long long read()
{
	long long res=0,neg=1;
	char c='\0';
	while((c=getchar())<'0'||c>'9')
	{
		if(c=='-') neg=-1;
	}
	while(c>='0'&&c<='9')
	{
		res=(res<<1)+(res<<3)+c-'0';
		c=getchar();
	}
	return res*neg;
}
void uwrite(long long x)
{
	if(!x) return;
	uwrite(x/10);
	putchar(x%10+'0');
	return;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	if(x==0)
	{
		putchar('0');
		return;
	}
	uwrite(x);
	return;
}
void writel(long long x)
{
	write(x);
	putchar('\n');
}
void writes(long long x)
{
	write(x);
	putchar(' ');
}
}//namespace
using namespace io;
int n,m;
int head[200005],to[400005],nxt[400005];
int fa[200005];
long long sz[200005],res,ans[200005];
bool s[200005];
void add(int x,int y)
{
	static int now=0;
	now++;
	to[now]=y;
	nxt[now]=head[x];
	head[x]=now;
	return;
}
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void join(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y) return;//特判
	res+=sz[x]*sz[y];//对答案的贡献
	fa[x]=y;
	sz[y]+=sz[x];
	return;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		s[i]=getchar()-'0';
	}
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		sz[i]=1;
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=head[i];j;j=nxt[j])
		{
			if(to[j]>i)join(i,to[j]);
		}
		ans[i]=res;
	}
	for(int i=1;i<=n;i++)
	{
		writel(ans[i]);
	}
	return 0;
}
```
### 12 pts，所有 $s_i$ 均等于 $0$
考虑到，删掉 $s_i=1$ 的点后，又马上将之前与这个点相邻的点连在一起了，说明删除这样的点**只影响连通块的大小，不影响联通性**。

所以，我们先将初始的图用并查集按第一档部分分的方法求出答案，再枚举被删除的点，将被删除的点所在连通块大小减去 $1$，并重新替换该连通块对答案的贡献（减去删除点之前的贡献，加上删除点之后的贡献）。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
namespace io{//快读快写
long long read()
{
	long long res=0,neg=1;
	char c='\0';
	while((c=getchar())<'0'||c>'9')
	{
		if(c=='-') neg=-1;
	}
	while(c>='0'&&c<='9')
	{
		res=(res<<1)+(res<<3)+c-'0';
		c=getchar();
	}
	return res*neg;
}
void uwrite(long long x)
{
	if(!x) return;
	uwrite(x/10);
	putchar(x%10+'0');
	return;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	if(x==0)
	{
		putchar('0');
		return;
	}
	uwrite(x);
	return;
}
void writel(long long x)
{
	write(x);
	putchar('\n');
}
void writes(long long x)
{
	write(x);
	putchar(' ');
}
}//namespace io
using namespace io;
bool s[200005];
int fa[200005];
long long sz[200005],ans;
int n,m;
void pre()
{
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
}
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void join(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y) return;
	fa[x]=y;
	sz[y]+=sz[x];
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		s[i]=getchar()-'0';
	}
	pre();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		join(x,y);
	}
	for(int i=1;i<=n;i++)
	{
		if(fa[i]==i) ans+=sz[i]*(sz[i]-1)/2;
	}
	for(int i=1;i<=n;i++)
	{
		writel(ans);
		int v=find(i);
		if(sz[v]>1)
		{
			ans-=(sz[v]-1)*sz[v]/2;
			sz[v]--;
			ans+=(sz[v]-1)*sz[v]/2;
		}
	}
	return 0;
}

```

### 100 pts，正解

会发现以上部分分做法都是用并查集维护的，而并查集难以处理删除的情况，所以我们还是考虑**倒着加点**。

如图，红点的 $s$ 值均为 $1$：![](https://cdn.luogu.com.cn/upload/image_hosting/6apeqha4.png)根据题目定义，**红色点无论删未删去，左右的点都是可以互相到达的**。以此类推，上图中只要 $a$ 点和 $b$ 点都存在，无论中间的红色点存不存在，这两个点就应当连接起来。所以，我们定义一个点的点权表示这个点是否真正加入到图中，我们初始把每个点的点权设为 $0$，并将所有 $s$ 值为 $1$ 的点连起来（保证像上图中的点 $a$ 和点 $b$ 可以互相连通）。每次枚举到点 $u$，就将这个点的点权设为 $1$，并将 $size$（所在连通块内的点权之和）贡献到答案中（因为这个点正式存在了，与连通块内所有有点权的点相连通了），再枚举相邻的点 $v$，如果 $v>u$ 或 $s_v=1$，都应当将 $u$ 和 $v$ 加入到同一个联通快中，按第二档部分分的方法贡献到答案即可。

详见代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
namespace io{//快读快写
long long read()
{
	long long res=0,neg=1;
	char c='\0';
	while((c=getchar())<'0'||c>'9')
	{
		if(c=='-') neg=-1;
	}
	while(c>='0'&&c<='9')
	{
		res=(res<<1)+(res<<3)+c-'0';
		c=getchar();
	}
	return res*neg;
}
void uwrite(long long x)
{
	if(!x) return;
	uwrite(x/10);
	putchar(x%10+'0');
	return;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	if(x==0)
	{
		putchar('0');
		return;
	}
	uwrite(x);
	return;
}
void writel(long long x)
{
	write(x);
	putchar('\n');
}
void writes(long long x)
{
	write(x);
	putchar(' ');
}
}//namespace
using namespace io;
int n,m;
set<int> e[200005];
bool s[200005];
long long ans[200005],res;
int fa[200005];
long long sz[200005];
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void join(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y) return;//注意特判
	res+=sz[x]*sz[y];//两个联通块相连时，每个联通快中有点权的点都与另一个联通块中有点权的点联通，贡献应为两个联通块各自点权之和的积。
	fa[x]=y;
	sz[y]+=sz[x];
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) s[i]=getchar()-'0';
    //建图
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		if(x==y) continue;
		e[x].insert(y);
		e[y].insert(x);
	}
    //初始化并查集
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		sz[i]=0;//最开始联通块点权之和为0
	}
    //将红点连起来
	for(int i=1;i<=n;i++)
	{
		if(s[i])
		{
			for(auto j:e[i])
			{
				if(s[j]) join(i,j);
			}
		}
	}
    //计算答案
	for(int i=n;i>=1;i--)
	{
		res+=sz[find(i)];
		sz[find(i)]++;//将点权加一并贡献到答案
		for(auto j:e[i])
		{
			if(j>i||s[j]) join(i,j);//连并查集
		}
		ans[i]=res;
	}
	for(int i=1;i<=n;i++)
	{
		writel(ans[i]);
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/205939383)

---

## 作者：block_in_mc (赞：1)

由于 $s_i=1$ 并不会改变图的联通性，我们可以对这个问题进行转化，每个点有一个点权，默认为 $1$：

* 若 $s_i=0$，删除节点 $i$ 及与其相连的边；
* 若 $s_i=1$，将节点 $i$ 的点权改为 $0$。

在每执行完一次操作后求出每个联通块的权值 $\dfrac{sz(sz-1)}{2}$ 之和，其中 $sz$ 为联通块中点权之和。

很容易使用并查集维护。由于并查集不支持删除操作，考虑正难则反，我们倒着执行这 $n$ 次操作。先考虑执行完 $n$ 次操作后的图中的边，即为每一条满足 $s_x=s_y=0$ 的边 $(x, y)$，将其在并查集上合并。$s_i=0$ 的点点权为 $1$，$s_i=1$ 的点点权为 $0$。答案初始时为 $0$。

对于 $s_i=0$，我们遍历以 $s_i$ 起点或终点的边 $(s_i,p)$，若 $s_p=0$ 或者 $p>i$，代表这条边在第 $i$ 次操作中被删除，反着做时应当在并查集上合并。对答案的贡献即为两个点所在的联通块 $sz$ 之积，代表每一对不在同一个联通块的点都能造成新的贡献。

对于 $s_i=1$，我们将 $i$ 所在的联通块的 $sz$ 加上 $1$，并将答案加上原先的 $sz$，代表点 $i$ 和其所在的联通块中的每个点都能造成新的贡献。

实现时注意开 `long long`，AC 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x[400100], y[400100], f[200100], sz[200100];
string s;
vector<int> g[200100], g2[200100];
long long ans;
int find(int p) {
	return p == f[p] ? p : (f[p] = find(f[p]));
}
void merge(int x, int y) {
	int a = find(x), b = find(y);
	if (a == b) return;
	ans += 1ll * sz[a] * sz[b];
	f[b] = a, sz[a] += sz[b];
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> s;
	s = " " + s; 
	for (int i = 1; i <= m; i++) 
		cin >> x[i] >> y[i];
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		sz[i] = (s[i] == '0');
	}
	for (int i = 1; i <= m; i++) {
		if (s[x[i]] == '1' && s[y[i]] == '1') merge(x[i], y[i]);
		else g[x[i]].push_back(y[i]), g[y[i]].push_back(x[i]);
	}
	vector<long long> res;
	for (int i = n; i >= 1; i--) {
		if (s[i] == '1') {
			int p = find(i);
			ans += sz[p];
			sz[p]++;
		}
		else {
			for (int ed : g[i])
				if (s[ed] == '1' || ed > i)
					merge(i, ed);
		}
		res.push_back(ans);
	}
	reverse(res.begin(), res.end());
	for (long long vl : res)
		cout << vl << endl;
	return 0;
}
```

---

## 作者：yokai_ing (赞：1)

显然正面直接并查集模拟，由于普及组算法无法处理分裂，所以排除，正难则反，倒着做就是合并所以考虑倒过来。

若只有操作 $1:~$
此时，我们只需要正遍历每个点，把与自己相邻的所有没删的点记录下来，再倒着做。加一个点合并一群并查集并更新答案。

现在想操作 $2:~$ 显然不能暴力删加边。注意到删了这个点，不会改变连通性，没被删的点能到达的点除了这个被删的没有变化。所以我们可以想能不能做一个**伪删除**。

于是， $2$ 操作我们只在这点上打标记，作为**虚点**，在正遍历时，把虚点视作永远存活，即不管当前点删在它之前还是之后，只要遍历到虚点就连它。

但倒着遍历也不能直接遍历到虚点就遍历他的所有点，所以我们**提前处理他的影响**，他连的实点不用管，在实点加入进来时合并就行，他连的虚点就提前加入一个并查集，这样复杂度正确且把点之间的关系都处理好了。

需要注意，虚点合并不能计算贡献，我们可以提前把虚点的 $size$ 设为 $0$ ，在加入虚点时直接把他所在连通块的 $size+1$ 就行。

非虚点加入方式同只有操作 $1$ 时没有变化，见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 200010
#define MAXM 800010
#define ll long long
int Next[MAXM],edge[MAXM],size[MAXN];
int head[MAXN],vis[MAXN],mk[MAXN];
int n,m,tot,fa[MAXN];
ll ans[MAXN],now;
char s[MAXN];
vector<int>p[MAXN],q[MAXN];
void add(int x,int y)
{
    edge[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
}
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
void join(int x,int y)
{
    int f1=find(x),f2=find(y);
    if(f1!=f2){
        now+=1ll*size[f1]*size[f2];
        size[f2]+=size[f1],fa[f1]=f2;
    }
}
void solve(int x)
{
    for(int i=0;i<q[x].size();i++)
    {
        int y=q[x][i];
        join(x,y);
        if(!vis[y]&&mk[i]){
            vis[y]=1;
            solve(y);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    cin>>(s+1);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;i++)
        fa[i]=i,size[i]=1;
    for(int i=1;i<=n;i++)
    {
        mk[i]=s[i]-'0';
        if(mk[i])size[i]--;
        for(int j=head[i];j;j=Next[j])
        {
            int v=edge[j];
            if(v>i||mk[v])p[i].push_back(v);
            if(mk[v]&&mk[i])
                join(v,i);
        }
    }
    for(int i=n;i>=1;i--)
    {
        d[i]=1;
        if(mk[i]){
            now+=size[find(i)]++;
            ans[i]=now;
            if(vis[i])continue;
            vis[i]=1;
        }
        for(int j=0;j<p[i].size();j++)
            join(p[i][j],i);
        ans[i]=now;
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：HYdroKomide (赞：1)

第一道场切的 Gold，希望不是最后一道。

### 题意：

无向图上两类操作：$0$ 直接删点； $1$ 删点但保留互相连边。问每次操作结束后连通的点对数量。

### 思路：

看到无向图以及删除类操作，_Recalling_ 同为金组的 [P8097](https://www.luogu.com.cn/problem/P8097)，考虑反向操作。

首先，不难发现，所有删点操作为 $0$ 的点，直接遍历它的连边即可更新结果。但 $1$ 类节点删除后的添边有后效性，似乎不太好处理。

接着，思考操作 $1$ 后效的性质，我们发现所有连通的 $1$ 类点，以及与它们有连边的其它 $0$ 点，可以组成一个 Cluster。这些点之间随时都保证互有连边（只要点存在）。

于是，每个点的不同类型已经无关紧要了。添加一个点时，直接找它当前所在的 Cluster 是否已经有点被添加了进来。如果有，直接将它们连通并计算答案。否则，按照 $0$ 类点的方式处理即可。

复杂度瓶颈在于并查集（~~和一个没啥卵用的 Cluster 内部排序~~）。懒得优化直接路径压缩就带一个 log，当然不影响过题。

### 程序如下：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<cstring>
using namespace std;
const int N=4e5+5;
long long n,m,fa[N],sz[N];
bool vis[N];
char s[N];
long long ans[N];
vector<int>g[N],clu[N],inclu[N];
int find(int x){
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
void dfs(int ori,int u){
	if(vis[u])return;
	clu[ori].push_back(u);
	if(s[u]!='1')return;
	vis[u]=true;
	for(auto v:g[u])dfs(ori,v);
}
int main(){
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		if(s[i]=='1'&&!vis[i]){
			dfs(i,i);
			sort(clu[i].begin(),clu[i].end());
			for(auto cur:clu[i])inclu[cur].push_back(i);
		}
	for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	for(int i=n;i>=1;i--){
		ans[i]=ans[i+1];
		for(auto cur:inclu[i]){
			int nth=clu[cur].size()-1;
			if(clu[cur][nth]>i){
				int un1=find(clu[cur][nth]),un2=find(i);
				if(un1==un2)continue;
				ans[i]+=1ll*sz[un1]*sz[un2];
				fa[un2]=un1;
				sz[un1]+=sz[un2];
			}
		}
		for(auto v:g[i]){
			if(v<i)continue;
			int un1=find(v),un2=find(i);
			if(un1==un2)continue;
			ans[i]+=1ll*sz[un1]*sz[un2];
			fa[un2]=un1;
			sz[un1]+=sz[un2];
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

### THE END

---

## 作者：xrcmk23568 (赞：0)

[P11674 [USACO25JAN] Reachable Pairs G](https://www.luogu.com.cn/problem/P11674)

题意：给定一张 $n$ 点 $m$ 边的无向图，从小到大删除每个节点及其所有邻边，如果 $s_t=1$ ，则删除节点后将其所有邻居两两连边。每次操作前输出可以互相到达的点对数。

由于题目中涉及删点操作，直接处理较为麻烦，因此考虑简化。

容易想到，删点的反向操作是加点，使用并查集即可简单维护，所以可以反向处理，从后往前依次加入图中节点并统计琪对答案的贡献。

进一步分析题目中的操作，可得：如果$s_t=1$, 则时刻t的操作不会对其余节点的连通性造成影响。

这样，题目中的两种操作分别转换为：
1. $s_t=0$ ，加入该节点及其所有邻边，可能会合并多个连通块
2. $s_t=1$ ，将当前节点加入其所属连通块 

此时，在预处理时遇到 $s_t=1$ 的节点时仍需暴力将其邻居两两连边，极端时间复杂度和空间复杂度均为 $O( n^2 )$ ，还需优化。

考虑定义一种节点，称为“虚点”。“虚点”是所有 $s_t=1$ 的节点删除后的形态，正常参与连边，但本身不计入连通块大小，也不对答案产生贡献。这样，处理时就无需额外连边。加入“虚点”后，只需改变其所属连通块大小，并统计答案。这样在优化时间复杂度的同时还便于处理。

注意：由于“虚点”本身参与连边，因此在加点时连边不能跳过虚点。两个虚点之间的边应预先连接。

时间复杂度 $O((n+m) \cdot α(n))$

代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,fa[200001],sz[200001],ans[200001];
vector<int>v[200001];
ll getfa(ll x){//并查集
	if(fa[x]==x)return x;
	return fa[x]=getfa(fa[x]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    string s;
    cin>>s;
    s='0'+s;//统一下标，方便处理
	for(int i=1;i<=n;i++)fa[i]=i;//并查集初始化
    for(int i=1;i<=m;i++){
    	ll a,b;
    	cin>>a>>b;
    	v[a].push_back(b);
    	v[b].push_back(a);
    	if(s[a]=='1'&&s[b]=='1'){
    		fa[getfa(a)]=getfa(b);
            //为确保连通性，预处理虚点连边
		}
	}
	ll jans=0;//当前答案
	for(int i=n;i>=1;i--){
		if(s[i]=='1'){
            //处理虚点
			ll jfa=getfa(i);
			jans+=sz[jfa];//贡献为其所在连通块大小
			sz[jfa]++;//加入虚点
            //不改变原图连通性
		}
		else{
            //处理普通点
			sz[i]=1;//初始化当前节点大小，方便计算
			for(int j=0;j<v[i].size();j++){
				if(v[i][j]<i&&s[v[i][j]]=='0')continue;
                //跳过未加入的普通点，后续加入时再处理
				ll fa_i=getfa(i),fa_to=getfa(v[i][j]);
				if(fa_i==fa_to)continue;
                //对答案贡献为待合并连通块中节点个数乘积（两两配对即可）
				jans+=sz[fa_i]*sz[fa_to];
                //合并连通块
				sz[fa_i]+=sz[fa_to];
				fa[fa_to]=fa_i;
			}
		}
		ans[i]=jans;//记录答案
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
    return 0;
} 
```

---

## 作者：RainWetPeopleStart (赞：0)

Gold 签到题。

首先发现答案可以用每个连通块的大小表示。

考虑 $s_t=0$，这部分可以使用离线思想和并查集解决。

如果这样做 $s_t=1$ 会因为连 $O(deg_t^2)$ 条边导致复杂度变为 $O(n^2)$。

考虑转化一下。因为本题只关心连通块大小，而进行 $s_t=1$ 的操作等价于将 $t$ 所在的连通块的大小 $-1$。

这样就可以套用上文做法了，复杂度 $O(n+m)$。（这里设 $\alpha$ 为常数）

赛时代码：


```cpp
#include<bits/stdc++.h>
#define vi vector<int>
#define ll long long
using namespace std;
const int N=5e5+10,mod=998244353;
struct edge{
    int u,v;
};
vector<edge> e[N];
int t[N];
int fa[N],sz[N];
ll ans=0;
int fd(int x){
    if(x==fa[x]) return x;
    return fa[x]=fd(fa[x]); 
}void mg(int x,int y){
    x=fd(x),y=fd(y);
    if(x==y) return ;
    ans-=1ll*sz[x]*(sz[x]-1)/2;
    ans-=1ll*sz[y]*(sz[y]-1)/2;
    fa[x]=y,sz[y]+=sz[x];
    ans+=1ll*sz[y]*(sz[y]-1)/2;
}void upd(int x){
    x=fd(x);
    ans-=1ll*sz[x]*(sz[x]-1)/2;
    sz[x]++;
    ans+=1ll*sz[x]*(sz[x]-1)/2;
}
int n,m;
string s;
int main(){
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    cin>>n>>m;cin>>s;s=' '+s;
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        if(s[u]==s[v]){
            e[min(u,v)].push_back((edge){u,v});
        }else{
            if(s[u]=='0'){
                e[u].push_back((edge){u,v});
            }else{
                e[v].push_back((edge){u,v});
            }
        }
        
    }for(int i=1;i<=n;i++) fa[i]=i,sz[i]=0;
    for(int i=1;i<=n;i++) if(s[i]=='1'){
        for(auto ed:e[i]){
            mg(ed.u,ed.v);
        }
    }
    vector<ll> a;
    for(int i=n;i>=1;i--){
        if(s[i]=='0') for(auto ed:e[i]){
            mg(ed.u,ed.v);
        }upd(i);
        a.push_back(ans);
    }reverse(a.begin(),a.end());
    for(auto ed:a) cout<<ed<<endl;
    return 0;
}
```

---

