# [COTS 2017] 影响 Utjecaj

## 题目背景

译自 [Izborne Pripreme 2017 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2017/) D2T1。$\texttt{1.5s,0.5G}$。


## 题目描述


给定 $n$ 个点 $m$ 条边的无向图（不一定连通，无自环，可能有重边）。

点 $i$ 的点权为 $a_i$。此外，图中有若干个点是**关键点**。

定义关键点 $u$ 的**影响力**为：不经过其他关键点（也不从其他关键点出发），且能到达点 $u$ 的点的点权和。

有 $q$ 次操作：

- $\texttt{1}$ $u$ $x$：令 $a_u\gets x$；
- $\texttt{2}$ $v$：查询关键点 $v$ 的影响力。

依次处理之，并对每个操作 $2$ 输出答案。


## 说明/提示


对于 $100\%$ 的数据，保证：

- $1\le n,m,q\le 2\times 10^5$；
- $0\le a_i,x\le 10^9$；
- $1\le u,v\le n$；
- 图中无自环；
- 操作 $2$ 中给定的点 $v$ 是关键点。


| 子任务编号 | $n,m,q\le $ |  特殊性质 |得分 |  
| :--: | :--: | :--: | :--: |  
| $ 1 $    | $ 10^3 $    |   |  $ 10 $   |  
| $ 2 $    | $ 2\times 10^5 $   |  A |  $ 20 $   |  
| $ 3 $    | $ 2\times 10^5 $ |  | $ 70 $   |  

特殊性质 A：没有操作 $1$。


## 样例 #1

### 输入

```
6 7
0 0 1 0 0 1
4 3 0 9 6 2
1 2
2 3
4 3
4 1
5 3
5 6
3 6
2
2 3
2 6```

### 输出

```
22
8```

## 样例 #2

### 输入

```
6 6
1 0 1 1 0 0
1 2 4 3 5 6
1 2
1 3
3 2
6 5
4 5
1 6
8
2 3
1 2 7
2 3
2 1
1 6 0
1 4 9
2 1
2 4```

### 输出

```
6
11
19
13
14```

# 题解

## 作者：XCDRF_ (赞：5)

# P11287 \[COTS 2017] 影响 Utjecaj

[原题传送门](https://www.luogu.com.cn/problem/P11287)

[更好的阅读体验](https://www.luogu.com.cn/article/drec19sa)

## 解题思路

在做本题之前，我们先来考虑一个简单的问题。

给定一个 $n$ 个点 $m$ 条边的无向图，点 $i$ 的点权为 $a_i$。定义一个点的影响力为这个点周围所有点和自己的点权和。

有 $q$ 次操作：

- $\texttt{1}$ $u$ $x$：令 $a_u\gets x$；
- $\texttt{2}$ $v$：查询点 $v$ 的影响力。

$1\le n,m,q \le 2\times 10^5$。

如果暴力的话，每次修改点权都要改周围所有点的值，最坏条件下可能会被卡到 $O(qn)$。考虑设定一个阈值 $B$，度数 $>B$ 和 $\le B$ 的点用两种方法处理。修改时如果这个点的度数 $\le B$ 则暴力修改点权；如果这个点的度数 $>B$ 则打上标记，记录现点权和原点权的差值，修改时间复杂度为 $O(B)$。查询时答案为暴力修改后的值加上相邻的度数 $>B$ 的点的标记。因为总共有 $m$ 条边，所以度数 $>B$ 的点最多有 $\frac{2m}{B}$ 个，查询时间复杂度为 $O(\frac{m}{B})$。总时间复杂度即为 $O(q(B+\frac{m}{B}))$。

由基本不等式得 $B+\frac{m}{B}\ge 2\sqrt m$，当且仅当 $B=\frac{m}{B}$ 即 $B=\sqrt m$ 时等号成立，所以总时间复杂度为 $O(q\sqrt m)$。

再来看本题，可以将所有关键点删去，整个图会分成若干个连通块。如果一个关键点和一个连通块相连，则整个连通块都可达。不妨将每个连通块缩成一个点，则一个关键点的影响力就是周围所有点和自己的点权和。这样我们就将本题转化成了上文提到的题目。时间复杂度为 $O(q\sqrt m)$。

## 参考代码

```cpp
#include<iostream>
#include<unordered_map> 
#include<cmath>
#define int long long
using namespace std;
const int N=2e5+5;
unordered_map<long long,bool> vis;
int n,m,tot,tot2,tot3,cnt,cnt2,B,q;
int head[N],h[N],b[N],sum[N],a[N],t[N],deg[N],big[N],ans[N];
struct Edge{
	int nxt,to;
}edge[N<<1],e[N<<1];
struct E{
	int fr,to;
}ee[N];
void add(int x,int y){
	edge[++tot]={head[x],y};
	head[x]=tot;
}
void add2(int x,int y){
	e[++tot2]={h[x],y};
	h[x]=tot2;
}
void dfs(int x){
	for(int i=head[x];i;i=edge[i].nxt){
		int xx=edge[i].to;
		if(b[xx]) continue;
		b[xx]=cnt;//存该点属于哪个连通块
		sum[cnt]+=a[xx];
		dfs(xx);
	}
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>t[i];
    	if(t[i]) b[i]=++cnt;//关键点自己是一个连通块
	}
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	if(t[i]) sum[b[i]]=a[i];//存关键点的点权
	}
    for(int i=1,x,y;i<=m;i++){
    	cin>>x>>y;
    	if((!t[x])&&(!t[y])){
    		add(x,y);//求连通块时用的边
    		add(y,x);
		}
		if(t[x]&&t[y]) continue;
		ee[++tot3]={x,y};//连通块之间的边，关键点和关键点之间没有边
	}
	for(int i=1;i<=n;i++){
		if(t[i]||b[i]) continue;
		b[i]=++cnt;
		sum[b[i]]+=a[i];
		dfs(i);//求出连通块大小和点权和
	}
	for(int i=1;i<=tot3;i++){
		int x=ee[i].fr,y=ee[i].to;
		x=b[x],y=b[y];
		if(x!=y&&!vis[x*2e5+y]){//如果这两个点不属于一个连通块且两个连通块间没有连边就连一条边
			add2(x,y);
			add2(y,x);
			vis[x*2e5+y]=vis[y*2e5+x]=1;
			deg[x]++,deg[y]++;
			cnt2+=2;
		}
	}
	vis.clear();
	B=sqrt(cnt2);//阈值大小
	cnt2=0;
	for(int x=1;x<=cnt;x++){
		if(deg[x]>B) big[++cnt2]=x;//记录大点信息
		for(int i=h[x];i;i=e[i].nxt){
			int xx=e[i].to;
			if(deg[xx]>B) vis[xx*2e5+x]=1;
			if(deg[x]>B) ans[x]+=sum[xx];//大点初始答案
		}
	}
	cin>>q;
	//本代码与思路中描述稍有区别，修改复杂度O(m/B)，查询复杂度O(B)
	while(q--){
		int op,x,y;
		cin>>op;
		if(op==1){
			cin>>x>>y;
			int w=y-a[x];
			sum[b[x]]+=w;//修改连通块点权和
			for(int i=1;i<=cnt2;i++)
				if(vis[big[i]*2e5+b[x]]) ans[big[i]]+=w;//枚举与该点有连边的大点进行修改
			a[x]=y;
		}
		else{
			cin>>x;
			x=b[x];
			if(deg[x]<=B){//小点直接枚举所有相邻连通块
				int anss=sum[x];
				for(int i=h[x];i;i=e[i].nxt){
					int xx=e[i].to;
					anss+=sum[xx];
				}
				cout<<anss<<'\n';
			}
			else cout<<ans[x]+sum[x]<<'\n';//大点答案已预处理，直接输出
		}
	}
	return 0;
}
```
本题细节较多，写代码时需要仔细。

[AC 记录](https://www.luogu.com.cn/record/203163727)

---

## 作者：lam_dyr (赞：2)

首先将关键点删去后用并查集找联通块并将剩下的连通块缩成点，然后考虑按度数分治。

修改操作对于相连小于 $
\sqrt{n}$ 的，我们直接暴力修改贡献，反之我们打上标记。

询问操作除了已经处理的度数小于 $\sqrt{n}$ 的部分，我们还需要加上度数大于根号的点的权值。

总复杂度 $O(n\sqrt{n})$。

---

## 作者：EityDawn (赞：2)

# 思路：

注：分析默认 $n$，$m$，$q$ 同阶。

假设从图中删去关键节点，那么图将被划分成若干个联通块。如果有关键点与联通块相连，那么这个联通块内的点都是可达的。

所以考虑将联通块打包，缩成一个点，断开关键节点之间的边。

那么一个点的影响力就是所有与之直接相连的点和自身的权值之和。

那么问题转化为了：

1. 对点 $x$ 和直接相连的点加上一个值。
2. 查询点 $x$ 和直接相连的点的权值和。

直接做是 $O(n\sum deg_i)$，$deg_i$ 是点 $i$ 的出度。

考虑根号分治。我们设立一个阈值 $B$，初始时先将点 $x$ 和直接相连的点的权值和预处理出来。对于修改操作，若 $deg_x\le B$，直接暴力修改，反之，我们对 $x$ 打上标记。询问时，我们再在权值和的基础加上与 $x$ 相连的且出度 $>B$ 的点上的标记。修改操作是 $O(B)$，而对于询问，默认 $\sum deg_i \le 2\times n$，那么出度 $> B$ 的点不超过 ${n}\over B$，询问复杂度为 $O({n\over B})$。

$B$ 取 $\sqrt n$ 时复杂度最优，为 $O(n\sqrt n)$。

## code

```cpp
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define mset(x,y) memset((x),(y),sizeof((x)))
#define mcpy(x,y) memcpy((x),(y),sizeof((y)))
#define FileIn(x) freopen(""#x".in","r",stdin)
#define FileOut(x) freopen(""#x".out","w",stdout)
#define debug(x) cerr<<""#x" = "<<(x)<<'\n'
#define Assert(x) if(!(x)) cerr<<"Failed: "#x" at line "<<__LINE__,exit(1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 Int;
const int N=2e5+10,B=400;
bool StM;
int c[N],a[N],n,m,k,q;
int in[N],Be[N];
ll b[N],sum[N],tag[N];
vector<int>G[N],E[N],H[N],Fa[N];
map<int,bool>Cenect[N];
map<pair<int,int>,bool>edge;
void dfs(int now)
{
    Be[now]=k,b[k]+=a[now];
    for(int to:E[now])
        if(!Be[to]) dfs(to);
    return;
}
void Main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,x,y;i<=m;i++)
    {
        cin>>x>>y;
        if(x>y) swap(x,y);
        if(edge.count({x,y})) continue;
        edge[{x,y}]=1;
        G[x].push_back(y);
        G[y].push_back(x);
        if(c[x]|c[y]) continue;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
        if(!Be[i]) ++k,dfs(i);
    for(int now=1;now<=n;now++)
    {
        if(c[now]){
            for(int to:G[now])
                if(Be[to]^Be[now]&&!c[to])
                {
                    if(Cenect[Be[now]].count(Be[to])) continue;
                    H[Be[now]].push_back(Be[to]),++in[Be[to]];
                    Cenect[Be[now]][Be[to]]=1;
                } 
        }
        else{
            for(int to:G[now])
                if(Be[to]^Be[now])
                {
                    if(Cenect[Be[now]].count(Be[to])) continue;
                    H[Be[now]].push_back(Be[to]),++in[Be[to]];
                    Cenect[Be[now]][Be[to]]=1;
                }
        }
    }
    for(int now=1;now<=k;now++)
    {
        sum[now]=b[now];
        for(int to:H[now]) sum[now]+=b[to];
        if(in[now]>B)
            for(int to:H[now]) Fa[to].push_back(now);
    }
    cin>>q;
    int op,x,y,now;
    while(q--)
    {
        cin>>op>>x;
        if(op==1){
            cin>>y;now=Be[x];
            int val=y-a[x];
            a[x]=y,b[now]+=val,sum[now]+=val;
            if(in[now]>B)
                tag[now]+=val;
            else for(int to:H[now]) sum[to]+=val;
        }
        else{
            ll delta=0;now=Be[x];
            for(int to:Fa[now])
                delta+=tag[to];
            cout<<sum[now]+delta<<'\n';
        }
    }
}
bool EdM;
int main()
{
    cerr<<fabs(&StM-&EdM)/1024.0/1024.0<<" MB\n";
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int StT=clock();
    int T=1;
    while(T--) Main();
    int EdT=clock();
    cerr<<1e3*(EdT-StT)/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：Twlight！ (赞：2)

这题怎么写啊，~~我复杂度还标错了，还有 Day2 T2 好难。~~

## 题目大意
给定 $n$ 个点 $m$ 条边的无向图，每个点有点权 $a_i$，有些点为关键点（$x_i = 1$）。保证无自环，但可能有重边。

你需要支持 $q$ 次操作：
1. 修改某个点的点权。
2. 查询所有不经过别的关键点就能到关键点 $u$ 的点的点权和。

其中 $n, m, q \leq 2 \times 10^5$，$a_i \leq 10^9$。

## 思路
显然，不能到达关键点 $u$ 的点一定经过了其他关键点，或根本不与 $u$ 连通，因此我们可以考虑直接把关键点删了，把剩下的连通块缩成一个点，再把关键点加回去。

此时每个关键点连到的连通块里的所有点都可以到达该关键点，查询的时候只需要关心关键点周围的若干个连通块即可。

我们先考虑两种不同的暴力：
1. 更改点权时直接暴力更新与它相邻的关键点的答案，此时修改 $O(n)$，查询 $O(1)$。
2. 更改点权时直接修改一个连通块的点权和，每次查询时直接暴力枚举与他相邻的非关键点连通块，对答案求和，此时修改 $O(1)$，查询 $O(n)$。

两种做法都可以被菊花图卡掉，不过这样已经有 $10\text{pts}$ 了。

不过我们可以发现，第一种做法在领域数较小的普通点适用，第二种做法在领域数较小的关键点适用，因此考虑对度数根号分治。

记缩点后的点数、边数分别为 $n', m'$，此时无向图的度数和为 $2m'$，所以度数超过 $\sqrt{m'}$ 的点不超过 $2\sqrt{m'}$ 个。

这样一来，修改时对于度数不超过 $\sqrt{m'}$ 的连通块，我们直接修改它的领域点的答案；对于度数超过 $\sqrt{m'}$ 的连通块，我们直接给它打一个标记（即只修改自己的权值）；而在查询的时候，除了关键点自己的答案，我们还需要加上与关键点联通但度数大于 $\sqrt{m'}$ 的连通块的点权，这样便是最后的答案。

注意些细节问题和写法，时间复杂度 $O(n + q\sqrt{m})$。

## 参考代码
写的很丑，请见谅。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int ll

const int N = 500000 + 10;
const int inf = 998244353;
using namespace std;

int read () {
	int x = 0, k = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return (1ll * x * k);
}

int n, m, q; 
int nn, bm;
int op, u, v;
int tp[N], a[N], b[N];
int col[N], dep[N];
vector<int> G[N], g[N]; 
unordered_set<int> H[N];

void bfs (int o) {
	static queue<int> Q;
	while (!Q.empty()) Q.pop();
	if (tp[o]) return b[o] += a[o], col[o] = o, void();
	Q.push(o); while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		if (col[u]) continue; col[u] = o, b[o] += a[u];
	 	for (int v: G[u]) if (!col[v] && !tp[v]) Q.push(v);
	}
}

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) tp[i] = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= m; ++i) u = read(), v = read(), G[u].push_back(v), G[v].push_back(u);
	for (int i = 1; i <= n; ++i) if (!col[i]) bfs(i);
	for (int i = 1; i <= n; ++i) for (int v: G[i]) if (col[i] != col[v] && tp[i] + tp[v] != 2) H[col[i]].insert(col[v]), H[col[v]].insert(col[i]);
	for (int i = 1; i <= n; ++i) nn += (dep[i] = H[i].size()); bm = sqrt(nn);
	for (int i = 1; i <= n; ++i) if (tp[i]) for (int v: H[i]) (dep[v] <= bm) ? (b[i] += b[v]) : (g[i].push_back(v), 0);

	q = read();
	for (int i = 1; i <= q; ++i) {
		op = read(), u = read(), v = (op == 1) ? read() : 0;
		if (op == 1) {
			if (dep[col[u]] <= bm) for (int o: H[col[u]]) if (tp[o]) b[o] += v - a[u];
			b[col[u]] += v - a[u], a[u] = v;
		} else {
			int ret = b[u]; for (int o: g[u]) ret += b[o]; 
			cout << ret << endl;
		}
	}
	return 0;
}
```

---

## 作者：Bobi2014 (赞：1)

这是一道使用根号分治~~优雅的暴力~~的题目。

### 前置知识

- [根号分治~~优雅的暴力~~](https://www.luogu.com.cn/article/5gtqzd4a)
- [并查集~~不会并查集做什么蓝题~~](https://oi.wiki/ds/dsu/)

### 思路

考虑把所以关键点删除，把剩下的图缩点，也就是把一个连通块变成一个点，权值为连通块内所有权值之和，因为是无向图，所以可以使用并查集，再把关键点和缩点后的图连接。

接下来就变为根号分治模板了，如果一个点的度数 $< \sqrt{n}$，那么直接使用暴力求解，否则使用 $ans$ 数组快速查询。

时间复杂度 $O(q \sqrt{n} \log n)$，~~懒得再开数组，写了个二分~~。

> 十年 OI 一场空，不开 long long 见祖宗。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n,m,Q,fa[N],w[N],sum[N],lim,ans[N];
bool vis[N];
vector<int> e[N],g[N],big;
void init(){
    for(int i = 1;i <= n;i ++){
        fa[i] = i;
    }
}
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    lim = sqrt(n);
    init();
    for(int i = 1;i <= n;i ++){
        cin >> vis[i];
    }
    for(int i = 1;i <= n;i ++){
        cin >> w[i];
    }
    for(int i = 1;i <= m;i ++){
        int u,v;
        cin >> u >> v;
        if(vis[u] == true or vis[v] == true){
            e[u].push_back(v);
            e[v].push_back(u);
            continue;
        }
        fa[find(u)] = find(v);
    }
    for(int i = 1;i <= n;i ++){
        if(vis[i] == true){
            for(int v : e[i]){
                if(vis[v] == false){
                    g[i].push_back(find(v));
                }
            }
            sort(g[i].begin(),g[i].end());
            g[i].erase(unique(g[i].begin(),g[i].end()),g[i].end());
        }
    }
    for(int i = 1;i <= n;i ++){
        if(vis[i] == false){
            sum[find(i)] += w[i]; 
        }
    }
    for(int i = 1;i <= n;i ++){
        if(vis[i] == true and g[i].size() >= lim){
            big.push_back(i);
            ans[i] = w[i];
            for(int v : g[i]){
                ans[i] += sum[v];
            }
        }
    }
    int sz = big.size();
    cin >> Q;
    while(Q --){
        int opt;
        cin >> opt;
        if(opt == 1){
            int x,v;
            cin >> x >> v;
            if(vis[x] == true){
                ans[x] += v - w[x];
                w[x] = v;
                continue;
            }
            for(int i : big){
                if(lower_bound(g[i].begin(),g[i].end(),find(x)) != g[i].end() and (*lower_bound(g[i].begin(),g[i].end(),find(x))) == find(x)){
                    ans[i] += v - w[x];
                }
            }
            sum[find(x)] += v - w[x];
            w[x] = v;
        }else{
            int x;
            cin >> x;
            if(lower_bound(big.begin(),big.end(),x) != big.end() and (*lower_bound(big.begin(),big.end(),x)) == x){
                cout << ans[x] << "\n";
            }else{
                int res = w[x];
                for(int v : g[x]){
                    res += sum[v];
                }
                cout << res << "\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：summ1t (赞：1)

首先不难想到以关键点为分界线，进行缩点，这个可以 dfs 预处理。

接下来可以用每个块去更新它所连的关键点的权值，进行预处理，然后就可以 $O(1)$ 修改和查询了。

但预处理最坏会被卡到 $O(n^2)$。

发现所连关键点数量非常多的块并不是很多，所以可以用根号分治。设阈值为 $B$：

* 若所连关键点数量 $< B$，直接按上述思路预处理。

* 若所连关键点数量 $\ge B$，则算出来块内点权值总和，让关键点向块连边，每次查询时暴力查找这些块统计答案。

第二类块最多只会有 $\frac{n}{B}$ 个，则时间复杂度为 $O(nB+q\frac{n}{B})$。

$q$ 与 $n$ 同阶，$B$ 取 $\sqrt{n}$ 即可。

时间复杂度 $O(n\sqrt{n})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rd read()
#define gc getchar()
#define dg(ch) isdigit(ch)
#define _mul(x) ((x<<3)+(x<<1))
#define ll long long
#define pb push_back
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define ROF(i,j,k) for(int i=j;i>=k;i--)
#define debug cout<<"cnm"<<endl;
int read(){int x=0,f=1;char ch=gc;while(!dg(ch)){if(ch=='-')f=1;ch=gc;}while(dg(ch))x=_mul(x)+(ch^48),ch=gc;return x*f;}
const int N=2e5+10,M=500;
int n,m,q,im[N],c[N],v[N],head[N],tot,cnt;ll va[N],vb[N];
vector<int> A[N],B[N];
struct node{int to,nxt;}edge[N<<1];
void add(int x,int y){edge[++tot]={y,head[x]},head[x]=tot;}
void dfs(int x){
	c[x]=cnt;
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].to;if(c[y]||im[y]) continue;
		dfs(y);
	}
}
void modify(int x,int y){
	int del=y-v[x];v[x]=y;
	if(A[c[x]].size()<M) for(auto j:A[c[x]]) vb[j]+=del;
	else va[c[x]]+=del;
}
ll query(int x){
	ll res=vb[x]+v[x];
	for(auto j:B[x]) res+=va[j];
	return res;
}
int main(){
	n=rd,m=rd;
	FOR(i,1,n) im[i]=rd;FOR(i,1,n) v[i]=rd;
	FOR(i,1,m){int x=rd,y=rd;add(x,y),add(y,x);}
	FOR(i,1,n){if(!c[i]&&!im[i])cnt++,dfs(i);}
	FOR(x,1,n){
		if(im[x]) continue;
		for(int i=head[x];i;i=edge[i].nxt){
			int y=edge[i].to;if(c[y]) continue;
			A[c[x]].pb(y);
		}
	}
	FOR(i,1,n) sort(A[i].begin(),A[i].end()),A[i].resize(unique(A[i].begin(),A[i].end())-A[i].begin());
	FOR(x,1,n){
		if(!im[x]) continue;
		for(int i=head[x];i;i=edge[i].nxt){
			int y=edge[i].to;if(!c[y]) continue;
			if(A[c[y]].size()<M) continue;
			B[x].pb(c[y]);
		}
	}
	FOR(i,1,n) sort(B[i].begin(),B[i].end()),B[i].resize(unique(B[i].begin(),B[i].end())-B[i].begin());
	FOR(x,1,n){
		if(A[c[x]].size()<M) for(auto j:A[c[x]]) vb[j]+=v[x];
		else va[c[x]]+=v[x];
	}q=rd;
	while(q--){
		int op=rd,x,y;
		if(op==1) x=rd,y=rd,modify(x,y);
		else x=rd,printf("%lld\n",query(x));
	}
	return 0;
}
```

---

## 作者：H3PO4 (赞：1)

从原图中去掉所有关键点得到若干连通块，把这些连通块变成新的点，新点权为连通块的点权和，新点再与关键点相连得到一个新的图。
于是问题转化为在新的图上修改点权、查询与某个点相邻的点（包含自己）的点权和。

考虑根号分治。设新图边数为 $m$，度数超过 $\sqrt{m}$ 的非关键点称为“大点”，显然“大点”只有 $O(\sqrt{m})$ 个。
维护关键点的影响力，
修改点权时，若修改“大点”的点权，那么给这个点打上标记，否则直接加到相邻的关键点的影响力上。
查询时，答案就是我们维护的这个点的影响力加上相邻“大点”的标记。

时间复杂度 $O(n+q\sqrt{m})$。

```cpp
#include<bits/stdc++.h>
using I=long long;
template<class T>using V=std::vector<T>;
template<class T,I N>using A=std::array<T,N>;
int main(){
  std::cin.tie(0)->sync_with_stdio(0);
  I n,m;std::cin>>n>>m;
  V<I>key(n);for(I&e:key)std::cin>>e;
  V<I>a(n);for(I&e:a)std::cin>>e;
  V<V<I>>g(n);
  for(I i=0;i<m;i++){
    I u,v;std::cin>>u>>v;u--;v--;
    g[u].push_back(v);g[v].push_back(u);
  }

  I z=0;V<I>bl(n,-1),b;
  for(I i=0;i<n;i++)if(key[i])bl[i]=z++,b.push_back(a[i]);
  V<std::unordered_set<I>>g2(z);I nk=z;V<I>ww(nk);
  auto dfs=[&](auto&&dfs,I u,I c)->void{
    bl[u]=c;b[c]+=a[u];
    for(I v:g[u]){
      if(bl[v]==-1)dfs(dfs,v,c);
      else if(bl[v]!=c)g2[c].insert(bl[v]),g2[bl[v]].insert(c);
    }
  };
  for(I i=0;i<n;i++){
    if(bl[i]==-1)g2.push_back(std::unordered_set<I>()),b.push_back(0),dfs(dfs,i,z++);
  }
  for(I i=0;i<nk;i++){
    ww[i]=b[i];
    for(I v:g2[i])if(v>=nk)ww[i]+=b[v];
  }

  I sd=0;for(I i=0;i<z;i++)sd+=g2[i].size();
  I blk=sqrt(sd);V<I>big,tag(n);
  for(I i=0;i<z;i++)if(g2[i].size()>blk)big.push_back(i);

  I q;std::cin>>q;
  while(q--){
    I o,x,y;std::cin>>o>>x;x--;I u=bl[x];
    if(o==1){
      std::cin>>y;
      if(u<nk)ww[u]+=y-a[x];
      else if(g2[u].size()>blk)tag[u]+=y-a[x];
      else for(I v:g2[u])if(v<nk)ww[v]+=y-a[x];
      a[x]=y;
    }else{
      I w=ww[u];
      for(I i:big)if(g2[u].count(i))w+=tag[i];
      std::cout<<w<<'\n';
    }
  }
  return 0;
}
```

---

## 作者：冷却心 (赞：0)

如果把原图中和关键点有关的边全部去掉，得到的新图再把同一个连通块缩成一个点，再把关键点放回去，那么我们的操作事实上就是维护单点加法，关键点邻域查询，经典问题。我们设新图的边数为 $e$，点数为 $v$。暴力做最坏 $O(ve)$，考虑根号分治，设阈值为 $B$，对于度数小于等于 $B$ 的关键点，我们暴力枚举邻域求答案，单次时间复杂度最坏 $O(B)$，对于度数大于 $B$ 的关键点，我们在修改的时候就加入贡献，查询 $O(1)$，因为总边数为 $e$，此类点只有 $O(\frac{e}{B})$ 个，所以修改复杂度 $O(\frac{e}{B})$。总时间复杂度 $O(q(B+\frac{e}{B}))$，取 $B=\sqrt{e}$ 得到复杂度 $O(q\sqrt e)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e5 + 10;
int n, m; bool key[N];
int fa[N]; int Find(int x) { return (fa[x] == x ? x : fa[x] = Find(fa[x])); };
LL A[N], S[N], Ans[N];
pair<int, int> e[N]; int etot;
vector<int> G[N];
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) cin >> key[i];
	for (int i = 1; i <= n; i ++) cin >> A[i], fa[i] = i;
	for (int i = 1, u, v; i <= m; i ++) {
		cin >> u >> v; if (key[u] && key[v]) continue;
		if (!key[u] && !key[v]) fa[Find(u)] = Find(v);
		else if (key[u]) e[++ etot] = {u, v};
		else e[++ etot] = {v, u};
	}
	for (int i = 1; i <= n; i ++) if (!key[i]) S[Find(i)] += A[i];
	for (int i = 1; i <= etot; i ++) G[e[i].first].push_back(Find(e[i].second));
	unsigned int T = sqrt(etot) + 1;
	for (int i = 1; i <= n; i ++) if (key[i]) {
		sort(G[i].begin(), G[i].end()); 
		unsigned int len = unique(G[i].begin(), G[i].end()) - G[i].begin();
		while (G[i].size() > len) G[i].erase(prev(G[i].end()));
		if (G[i].size() > T) {
			for (int x : G[i]) G[x].push_back(i), Ans[i] += S[x];
		}
	}
	int Q; cin >> Q; int opt, x, y;
	while (Q --) {
		cin >> opt >> x;
		if (opt == 1) {
			cin >> y;
			LL d = y - A[x]; A[x] = y; S[Find(x)] += d;
			if (key[x]) continue;
			for (int v : G[Find(x)]) Ans[v] += d;
		} else {
			if (G[x].size() > T) cout << Ans[x] + A[x] << "\n";
			else {
				LL res = A[x]; for (int y : G[x]) res += S[y];
				cout << res << "\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：To_our_starry_sea (赞：0)

### Solution

比较板的题。

考虑关键点对答案的影响，发现将所有关键点及其相连的边全部删去之后，剩余的每一个非关键点的联通块内可以不经过关键点相互到达，可以将其缩成若干个点。而重新加上关键点后，发现其能到达的点即为与该关键点的邻居（缩点后）。

考虑如何维护操作。对于两类操作，发现若没有第一类操作的情况是容易的。否则，注意到 $\sum du_i$ 是 $O(m)$ 的，这启发我们根号分治。设阀值为 $B$。对于一个关键点 $u$，若 $du_u < B$，则在询问时可以扫一遍邻居直接统计答案，单次复杂度为 $O(B)$。否则，对于一个非关键点 $v$，每次 $a_v$ 改变时更新与其相邻的度数大于 $B$ 的关键点的答案，显然复杂度为 $O(\frac{m}{B})$，平衡一下就是 $O(q \sqrt{m})$。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 200005;
int n, m, q, lim, cnt = 0, tot = 0, rt = 0, Sum = 0, head[MAXN], belong[MAXN], zt[MAXN], id[MAXN], du[MAXN];
int dfn[MAXN], low[MAXN], col[MAXN], fa[MAXN];
ll a[MAXN], sum[MAXN], ans[MAXN];
bool x[MAXN], cut[MAXN], vis[MAXN];
struct edge {
	int to, next;
} e[MAXN << 1];
vector<int> edge[MAXN], E[2][MAXN];
stack<int> s;
inline void add(int u, int v) {
	cnt++;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}
inline int find(int k) {
    if (fa[k] == k) return k;
    else return fa[k] = find(fa[k]);
}
inline void tarjan(int u) {
	dfn[u] = low[u] = ++tot, s.push(u);
	if (u == rt && head[u] == 0) return;
	int flag = 0;
	for (int i = head[u]; i; i = e[i].next) {
	    int v = e[i].to;
	    if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			if (dfn[u] <= low[v]){
				 flag++;
				 if (flag > 1 || u != rt) cut[u] = 1;
				 Sum++;
				 int z;
				 do{
					 z = s.top(), s.pop();
					 col[z] = Sum;
				 } while(v != z);
				 col[u] = Sum;
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
}
inline void dfs(int u, int w) {
    vis[u] = 1, col[u] = w, sum[col[u]] += a[u];
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (vis[v]) continue;
        dfs(v, w);
    }
}
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
int main(){
    //freopen("node.in", "r", stdin);
    //freopen("node.out", "w", stdout);
    n = read(), m = read();
    for (int i = 1; i <= n; i++) x[i] = read(), fa[i] = i;
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		if ((!x[u]) && (!x[v])) add(u, v), add(v, u);
		if (x[u] && x[v]) continue;
		if (x[u]) edge[u].push_back(v);
		if (x[v]) edge[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        Sum++, dfs(i, Sum);
	}
	lim = max(1, (int)(sqrt(m)));
	for (int u = 1; u <= n; u++) {
        if (!x[u]) continue;
        for (auto v : edge[u]) E[0][u].push_back(col[v]);
        sort(E[0][u].begin(), E[0][u].end());
        auto it = unique(E[0][u].begin(), E[0][u].end());
        E[0][u].erase(it, E[0][u].end());
        du[u] = E[0][u].size();
        if (du[u] > lim) {
            for (auto v : E[0][u]) E[1][v].push_back(u), ans[u] += sum[v];
        }
	}
	q = read();
	while (q--) {
        int op = read();
        if (op == 1) {
            int u = read();
            ll w = read();
            if (x[u]) {
                a[u] = w;
                continue;
            }
            for (auto v : E[1][col[u]]) ans[v] += w - a[u];
            sum[col[u]] += w - a[u], a[u] = w;
        }
        else {
            int u = read();
            if (du[u] <= lim) {
                ll res = a[u];
                for (auto v : E[0][u]) res += sum[v];
                printf("%lld\n", res);
            }
            else printf("%lld\n", ans[u] + a[u]);
        }
	}
    return 0;
}
```

---

## 作者：LEE114514 (赞：0)

同机房同学推荐的幽默题，想到正解没分析出复杂度……根本没想过用边数 $m$ 分析复杂度。

## 思路

首先可以不经过关键点互相到达的非关键点可以缩成一个连通块，对一个关键点查询答案相当于查询它的相邻连通块的和。

我们发现由于 $n,m$ 同阶，所以将连通块视作一个点后，度数超过 $\sqrt{n}$ 的连通块不会超过 $\sqrt{n} 个$。

所以，我们根号分治。

对于修改：
- 对于度数 $\le \sqrt{n}$ 的点，我们每次更新都暴力修改与它相邻的关键点的答案。
- 否则，我们维护该连通块的点权和。

对于查询：
- 我们在维护好的小度点的答案上，遍历所有大度点，并判断是否联通，是则加上贡献。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,q,lim,sz;
const int maxn=2e5+5;
int iskey[maxn];
long long ans[maxn];
long long tag[maxn];
int a[maxn];
vector<int> H[maxn],G[maxn],T;
int fa[maxn];
bool to[450][maxn];
void dfs(int u,int rt){
	if(iskey[u]){
		H[rt].emplace_back(u);
		return;
	}
	tag[rt]+=a[u];
	fa[u]=rt;
	for(int v:G[u]) if(!fa[v]) dfs(v,rt);
}
int op,x,y;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	lim=sqrt(n);
	for(int i=1;i<=n;++i) cin>>iskey[i];
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1,u,v;i<=m;++i){
		cin>>u>>v;
		G[u].emplace_back(v),G[v].emplace_back(u);
	}
	for(int i=1;i<=n;++i){
		if(fa[i]||iskey[i]) continue;
		dfs(i,i);

		sort(H[i].begin(),H[i].end());
		H[i].erase(unique(H[i].begin(),H[i].end()),H[i].end());

		if(H[i].size()>lim) T.emplace_back(i);
		else for(int v:H[i]) ans[v]+=tag[i];
	}
	sz=T.size();
	for(int i=0;i<sz;++i)
		for(auto iter:H[T[i]]) to[i][iter]=1;
	cin>>q;
	while(q--){
		cin>>op>>x;
		if(op==1){
			cin>>y;
			if(H[fa[x]].size()<=lim) for(int v:H[fa[x]]) ans[v]+=y-a[x];
			else tag[fa[x]]+=y-a[x];
			a[x]=y;
		}else{
			long long res=ans[x]+a[x];
			for(int i=0;i<sz;++i) if(to[i][x]) res+=tag[T[i]];
			cout<<res<<'\n';
		}
	}
}
```

---

