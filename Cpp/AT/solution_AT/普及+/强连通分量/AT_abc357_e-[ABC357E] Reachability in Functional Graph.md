# [ABC357E] Reachability in Functional Graph

## 题目描述

有一个有 $N$ 个顶点和 $N$ 条边的有向图，顶点编号为 $1$ 到 $N$。  
每个顶点的出度都是 $1$，从顶点 $i$ 出发的边指向顶点 $a_i$。  
请你求出所有满足从顶点 $u$ 可以到达顶点 $v$ 的顶点对 $(u, v)$ 的个数。

这里，从顶点 $u$ 可以到达顶点 $v$，是指存在一个长度为 $K+1$ 的顶点序列 $w_0, w_1, \dots, w_K$，满足以下所有条件。特别地，当 $u = v$ 时，总是可以到达。

- $w_0 = u$
- $w_K = v$
- 对于所有满足 $0 \leq i < K$ 的 $i$，都存在一条从顶点 $w_i$ 指向顶点 $w_{i+1}$ 的边。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq a_i \leq N$
- 输入的所有值均为整数

## 样例解释 1

从顶点 $1$ 可以到达的顶点是顶点 $1, 2$。  
从顶点 $2$ 可以到达的顶点是顶点 $1, 2$。  
从顶点 $3$ 可以到达的顶点是顶点 $1, 2, 3$。  
从顶点 $4$ 只能到达顶点 $4$。  
因此，满足条件的顶点对 $(u, v)$ 的个数为 $8$。  
注意，从顶点 $4$ 出发的边是自环，即指向顶点 $4$ 自身。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 1 1 4```

### 输出

```
8```

## 样例 #2

### 输入

```
5
2 4 3 1 2```

### 输出

```
14```

## 样例 #3

### 输入

```
10
6 10 4 1 5 9 8 6 5 1```

### 输出

```
41```

# 题解

## 作者：weilycoder (赞：14)

# 前置知识：基环树

![内向基环树](https://cdn.luogu.com.cn/upload/image_hosting/vazyz2eg.png)

众所周知，树是一个拥有 $n$ 个点和 $n-1$ 条边的无环的连通图，假如我们向图中再添加一条边，一定会形成一个环。

我们将边换成有向边，如果每个点有且只有一条出边，称这个图为“内向基环树”（如上图）。

基环树的题目可以将环看成一个点，转化为树上问题。

# 题意简述

给定一个内向基环树森林，求有序点对 $(u,v)$ 使 $u$ 能到达 $v$ 的数量。点永远可以到达本身。

# 思路

考虑统计每个点能到达点的数量。

看出题目给的图是内向基环树森林就好办了：先在图中找环，每个环上的点的贡献就是环的大小。

不在环上的点可以递推：设存在有向边 $u\to v$，$u$ 不在环上，已知 $v$ 能到达的点的数量，这些点 $u$ 也能到达。由于 $u$ 不在环上，$v$ 不可能到达 $u$，只需再计算 $u$ 到达自己的贡献即可。

# Code

```cpp
#include <iostream>
using namespace std;

const int N = 3e5;
int n, edge[N], mark[N], vis[N], ans[N];

/* 从每个点开始 dfs：
   edge 存边；mark 标记，每次 dfs 用不同颜色；
   vis 记录每次 dfs 到达点的时间，用于快速计算环的大小；
   ans 记录贡献。*/

int dfs(int s, int c, int d) {
  if (mark[s]) { // s 被标记过
    if (mark[s] == c) {
       // 如果是本轮 dfs 标记的，则找到一个环
      ans[s] = d - vis[s];
      return s;
    } // 若不是本轮标记的，则先前一定处理过了
    return -1;
  }
  mark[s] = c, vis[s] = d; // 标记并记录时间
  int e = dfs(edge[s], c, d + 1);
  if (e == -1) ans[s] = ans[edge[s]] + 1; // 上一个点不在环里
  else if (e == s) return -1; // 到达环的终点
  else ans[s] = ans[edge[s]]; // 两个点都在环里
  return e;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> edge[i];
  long long sum = 0;
  for (int i = 1; i <= n; ++i) {
    dfs(i, i, 1);
    sum += ans[i];
  }
  cout << sum << "\n";
  return 0;
}
```

---

## 作者：ttq012 (赞：6)

不理解为什么题目保证边数不大于点数。这个题 $m>n$ 不是也可以做吗。

首先建反图，然后考虑使用 Tarjan 算法将有向图中的每一个强连通分量在新图中缩为一个点，然后剩下一个 DAG 森林考虑搞一下。

设 $f_i$ 表示可以到达新图 $i$ 点的点的数量，$g_i$ 表示以新图 $i$ 点结尾的不同的路径的总数目。

那么对于每一条 $j\to i$ 的边，必然有：

+ $f_i=f_i+f_j$。
+ $g_i=g_i+f_j\times \text{CNT}_i$。

其中 $\text{CNT}_i$ 表示新图中 $i$ 点在原图中对应的强连通分量中点的数目。

因为新的图是 DAG 森林，所以每一次从入度为 $0$ 的结点开始转移，在拓扑排序的过程中就可以直接求出答案。

因为不同的 $i$ 对应的 $g_i$ 对应的路径是互不重复的，所以答案就是 $\sum\limits_{i=1}^ng_i$，不需要容斥。

时间复杂度为 $O(n+m)$。如果写丑了可能会出问题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define said(...)
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;++i)
#define G(i,x,y) for(int i=x;i>=y;--i)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#define inf (7611257611378358090ll/2)
using namespace std;
const int N = 500100;
const int mod = 998244353;

stack<int> stk;
vector<int> z[N], scc[N];
int idx, tot, instk[N], dfn[N], low[N], bel[N], cnt[N], dis[N], vis[N], en[N], deg[N];
struct Edg { int u, v; } ed[N];
void dfs(int u) {
    dfn[u] = low[u] = ++idx;
    stk.push(u), instk[u] = true;
    W(z, j, u) {
        if (!dfn[j]) {
            dfs(j);
            low[u] = min(low[u], low[j]);
        } else if (instk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (dfn[u] == low[u]) {
        tot++;
        while (stk.top() != u) {
            int t = stk.top();
            stk.pop(), instk[t] = false;
            bel[t] = tot, scc[tot].pb(t);
        }
        int t = stk.top();
        stk.pop(), instk[t] = false;
        bel[t] = tot, scc[tot].pb(t);
    }
}
int a[N], dp[N], gg[N];
auto main() [[O3]] -> signed {
    int n;
    cin >> n;
    F(i, 1, n) {
        int x;
        cin >> x;
        a[i] = x;
        z[i].push_back(x);
    }
    F(i, 1, n) {
        if (!dfn[i]) {
            dfs(i);
        }
    }
    F(i, 1, n) {
        z[i].clear();
    }
    F(i, 1, n) {
        if (bel[i] != bel[a[i]]) {
            deg[bel[i]]++;
            z[bel[a[i]]].push_back(bel[i]);
        }
    }
    queue<int> q;
    F(i, 1, tot) {
        if (!deg[i]) {
            q.push(i);
        }
        gg[i] = scc[i].size();
        dp[i] = scc[i].size() * scc[i].size();
    }
    while (q.size()) {
        int f = q.front();
        q.pop();
        for (auto &g : z[f]) {
            gg[g] = (gg[g] + gg[f]) % mod;
            dp[g] = (dp[g] + scc[g].size() * gg[f] % mod) % mod;
            if (!--deg[g]) {
                q.push(g);
            }
        }
    }
    cout << accumulate(dp + 1, dp + tot + 1, 0ll) << '\n';
}

```

---

## 作者：Down_syndrome (赞：2)

## 题意
给定一个每个点有且仅有一条出边的有向图，求使得 $u$ 能到达 $v$ 的有序点对 $(u,v)$ 的个数。
## 思路
每个点仅有一条出边是一个关键信息，这使得原图是一个基环内向森林。但是这有什么用呢？我们可以知道，在基环内向森林上从一个节点 $u$ 出发一定会最终走到一个环上（可以一直走，但是节点数量是有限的）。我们分类讨论一下。

1. 假设 $u$ 在这个环上

此时这个环上的所有点构成一个强连通块。因为 $u$ 只能走到环上的点，所以其它点不可能在这个块上，且环肯定强联通。那么假设这个强连通块的大小是 $siz$，这个强联通块对答案的贡献是 $siz^2$。一个点的贡献定义为以这个点为起点的合法答案数量。

2. 假设 $u$ 不在环上

$u$ 的贡献就为它走到环的路径上的点的数量加环上的点的数量。

怎么快速统计答案呢？先缩点，如果一个强连通块的大小大于 $1$，那显然是第一种情况，直接加上 $siz^2$，否则在 DAG 上 dp。

极端数据下答案会爆 int，记得 long long。

[code](https://atcoder.jp/contests/abc357/submissions/54359882)

---

## 作者：DrAlfred (赞：2)

摘要：图论，反图，拓扑排序，dfs

[传送门：https://www.luogu.com.cn/problem/AT_abc357_e](https://www.luogu.com.cn/problem/AT_abc357_e)

## 题意

有一个 $N$ 个点 $N$ 条边的有向图。每个点的出度为 $1$，第 $i$ 个点有一条指向 $a_i$ 的有向边。若从节点 $u$ 能走到节点 $v$，则称 $(u, v)$ 为可达点对。注意 $(u, u)$也是可达点对。求给定的有向图中可达点对的个数。

## 分析思路

注意到 $N$ 个点 $N$ 条边这一性质，可以想象这个图类似一个基环森林，比如样例二如下图。

```
5
2 4 3 1 2
```

![](https://cdn.luogu.com.cn/upload/image_hosting/dmrxrjbp.png)

容易发现，对于每个联通分量，都会有一个环，有一些点直接或者间接指向环上的点，每个环上的点对应了一颗树。如图可以看作这样几棵树。

![](https://cdn.luogu.com.cn/upload/image_hosting/ncv889eb.png)

观察上图，发现对于每棵树上的点（包括在环上的树根），都能到达：

- 根链上的所有点；
- 环上的所有点。

于是我们分几步处理此问题：

1. 使用拓扑排序，预处理出所有的环。
2. 建反图。对于环上的每个点所对应的树进行 `dfs`，求出树上每个点根链的长度，加入答案。对于每个树上的点还需要加上它所在联通分量的环的大小。

于是我们在 $O\left(n + m\right)$ 的时间复杂度内解决了此问题，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
using i64 = long long;
std::vector<int> fr[N];
i64 n, u, to[N], in[N], ans, onC[N], siz[N];
inline void dfs(int x, int fa, int dep) {
    ++siz[fa], ans += dep;
    for (auto y : fr[x]) {
        if (!onC[y]) dfs(y, fa, dep + 1);
    }
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> to[i], in[to[i]]++;
        fr[to[i]].push_back(i);
    }
    std::queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) Q.push(i);
    }
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        if (--in[to[u]] == 0) Q.push(to[u]);
    }
    for (int i = 1; i <= n; i++) {
        std::vector<int> pos;
        for (int j = i; in[j]; j = to[j]) {
            in[j] = 0, pos.push_back(j), onC[j] = 1;
        }
        for (auto j : pos) {
            dfs(j, j, 0), ans += pos.size() * siz[j];
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：1)

发现这张图就是一棵有向基环树，而且环上边同向。tarjan 缩点之后是一棵根向树。发现一个点能到的点，只有其所在环中的点和根向树上的祖先。建反树以后在树上做 dp 即可。[submission](https://atcoder.jp/contests/abc357/submissions/54356788)。

---

## 作者：_anll_ (赞：0)

~~感觉这场的 E 比 D 简单。~~
## 题目大意
给你 $n$ 个点 $n$ 条边的有向图，让你求有多少对 $(u,v)$ 可以从 $u$ 到达 $v$。特别地，每个点总是可以到达自己。

## 大体思路
有向图加上到达点，再看看样例发现有环，一眼强连通分量。tarjan 套上去后再加个记忆化 dfs 就完事了。

具体而言，在一个强连通的点一定相互可达，其余的正常 dfs 即可。缩完之后的图是向根树，理论上来说需要建反图的，但 vp 的时候困迷糊了就正着跑的记忆化搜索。

不过 tarjan 在这有点大材小用了，应该有神犇可以用更简洁的代码实现本题。

注意，不开 long long 见祖宗。（落泪）

## 代码演示
大体思路就是这样，如果有不清晰的地方欢迎结合代码理解。
``` cpp
#include<iostream>
#define int long long
using namespace std;
const int N=3e5+5;
struct Edge{
	int l,nxt;
}ed[N];
int n,ans,t=1,fas[N],h[N],anu[N],du[N];
int tot,top,cnt,low[N],dfn[N],stk[N],instk[N],scc[N],scs[N];
void add(int f,int l){
	ed[++t]={l,h[f]};
	h[f]=t;
}
void tarjan(int x){
	dfn[x]=low[x]=++tot;
	stk[++top]=x,instk[x]=1;
	int l=fas[x];
	if(!low[l]){
		tarjan(l);
		low[x]=min(low[x],low[l]);
	}
	else if(instk[l]) low[x]=min(low[x],dfn[l]);
	if(dfn[x]==low[x]){
		int y;cnt+=1;
		do{
			y=stk[top--];instk[y]=0;
			scs[cnt]++;scc[y]=cnt;
		}while(y!=x);
	}
}
void dfs(int x){//正着跑需要加记忆化不然会出问题
	if(anu[x]) return;
	for(int i=h[x];i;i=ed[i].nxt){
		int l=ed[i].l;
		dfs(l);
		anu[x]+=anu[l];
	}
	anu[x]+=scs[x];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>fas[i];
	for(int i=1;i<=n;i++) if(!low[i]) tarjan(i);
	for(int i=1;i<=n;i++)
		if(scc[fas[i]]!=scc[i])
			add(scc[i],scc[fas[i]]),du[scc[fas[i]]]++;
	for(int i=1;i<=cnt;i++) if(!du[i]) dfs(i);
	for(int i=1;i<=n;i++) ans+=anu[scc[i]];
	cout<<ans;
	return 0;
}
```

---

## 作者：Empty_Dream (赞：0)

## 题意

给你 $N$ 条边，求有多少对点能从 $u$ 出发到 $v$。

## 分析

如果没做过缩点，先做[【模板】缩点 ](https://www.luogu.com.cn/problem/P3387)。这题如果用缩点的方法做会比模板题更模板……

看到有向图能否到达，第一时间想到强连通分量，那就可以开始分类讨论：

- 强连通分量内点对的贡献：不难得到就是大小的平方。
- 强连通分量内对外的贡献：那就是连出去的强连通分量的大小……吗？测完样例后发现好像并不是，而是一直到“头”的所有强连通分量的大小。

接下来就是计算到“头”的所有强连通分量大小。首先明确什么是“头”：就是可以只有内部贡献的强连通分量，不需要计算对外，也就是出度为 $0$。那我们就可以缩点，把每一个强连通分量看成一个点，具体建图方式见[模板题](https://www.luogu.com.cn/problem/P3387)，这里我们只需要建反图，让出度为 $0$ 变成入度，方便之后拓扑。之后来遍拓扑记录一下所有强连通分量的前缀和就好了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, m, tot, dfc, cnt, top, ans;
int lst[N], a[N], rd[N], s[N], cd[N], sz[N];
int dfn[N], stk[N], instk[N], low[N], scc[N];
vector<int> g[N];
struct edge{
    int to, nxt, from;
}e[2 * N];

void add(int u, int v){
    e[++tot].to = v;
	e[tot].from = u;
    e[tot].nxt = lst[u];
    lst[u] = tot;
}

void tarjan(int u){//强连通分量
    low[u] = dfn[u] = ++dfc;
    stk[++top] = u;
    instk[u] = 1;
    for (int i = lst[u]; i; i = e[i].nxt){
        int v = e[i].to;
        if (!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instk[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]){
        ++cnt;
        int tmp = 0;
        do{
            tmp = stk[top--];
            scc[tmp] = cnt;
            sz[cnt]++;
            instk[tmp] = 0;
        }while(tmp != u);
    }
}

void tuopu(){//拓扑统计前缀和
	queue<int> q;
	for (int i = 1; i <= cnt; i++){
		if (rd[i] == 0) q.push(i);
	}
	while (!q.empty()){
		int u = q.front(); q.pop();
		for (int i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			rd[v]--, s[v] += sz[u] + s[u];//统计前缀和
			if (rd[v] == 0) q.push(v);
 		}
	}
}

signed main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        add(i, a[i]);
    }
    for (int i = 1; i <= n; i++){
        if (!dfn[i]) tarjan(i);
    }
	for (int i = 1; i <= tot; i++){//参考模板题在强连通分量上建图
		if (scc[e[i].from] != scc[e[i].to]){
			int u = scc[e[i].from], v = scc[e[i].to];
			g[v].push_back(u);//反图，出度边入度
			rd[u]++;
		}
	}
	tuopu();
    for (int i = 1; i <= cnt; i++) ans += s[i] + sz[i] * sz[i];//最后答案分量内+分量外
	cout << ans;
    return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

对于每个没遍历过的点 $i$，我们都要不断遍历所有 $i$ 能到达的节点（即每次让 $i=a_i$），直到遍历到这次遍历过的点，或者遍历到以前遍历过的点。

如果遍历到这次遍历过的点，则发现一个新环，环中节点可到达的节点数就是环的节点数。其他的点能到达的节点数为环中节点数加到环的距离在加一（自己别忘了）。遍历到之前遍历过的结点的话，新遍历到的点的能到达节点个数为之前的节点能到达的节点个数加上到那个节点的距离加一（同样也是不要忘了自己）。

这样其实是会超时的。其实我们可以存一个数组 $p$，每次遍历都要归零，$p_i$ 存的是 $i$ 是这次第几个被遍历的，遍历变量肯定是在 $p_i$ 最小，且 $i$ 在环中的那个 $i$。那么这次遍历遍历到的节点个数减去 $p_i-1$ 就是环中节点个数，没必要在搜一次找环中节点个数。

最后一个点超时！

继续优化：对于 $a_i=i$ 的 $i$（即出现自环），他能到达的节点个数肯定只有他本身。

~~最后一个测试点跑的超快！~~

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],si[200010];
long long ans;
void read(int &a){
	a=0;int flag=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')flag=-1;
		ch=getchar();
	}
	do{a=a*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	a*=flag;
}
int main(){
	read(n);
	for(int w=1;w<=n;w++)read(a[w]);
	for(int w=1;w<=n;w++){
		if(a[w]==w&&!si[w])si[w]=1,ans++;
		if(!si[w]){
			int p[200010]={0},x=w,t=0,y=w,z=0,h=0;
			while(!p[x]&&!si[x])p[x]=++t,x=a[x];
			if(si[x])while(!si[y])z++,si[y]=si[x]+t-z+1,ans+=si[y],y=a[y];
			else{
				y=x,z=p[x]-1;
				int u[200010]={0};
				while(!u[y])u[y]=1,si[y]=t-z,ans+=si[y],y=a[y];
				y=w;
				while(!u[y])h++,si[y]=t-h+1,ans+=si[y],y=a[y];
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Starrykiller (赞：0)

由于每个点有且仅有一条出边，不难发现，对应的图的形态是内向基环树森林。

每棵树是独立的，我们可以分开考虑。

对于每棵树，我们找到唯一的环，记环大小为 $x$。对环上的点，遍历每一棵以它为根的子树（这里是反着建图）。记环上的点的深度为 $0$，不难发现每个深度为 $d$ 的点的贡献就是 $d+x$。

时间复杂度 $\Theta(n)$。

[My submission](https://atcoder.jp/contests/abc357/submissions/54354785).

---

## 作者：MicroSun (赞：0)

板子题。

图中有环，结果较难计算；考虑缩点，将原图转换为有向无环图。

缩点后，每一个强连通分量中的点都可以互相到达，且不在同一个强连通分量中的点都可以用拓扑或记忆化搜索计算。

注意图不一定连通。

Code:

```cpp
// Problem: E - Reachability in Functional Graph
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=2e5+10;

struct edge{
	int to,nxt;
}a[maxn<<1],a1[maxn<<1];
int head[maxn],cnt,head1[maxn],cnt1;
void add(int u,int v){
	a[++cnt]={v,head[u]};
	head[u]=cnt;
}
void add1(int u,int v){
	a1[++cnt1]={v,head1[u]};
	head1[u]=cnt1;
}
int dfn[maxn],low[maxn],tms,st[maxn],vis[maxn],idx,tot;
int w[maxn],c[maxn];
void tarjan(int x){
	dfn[x]=low[x]=++tms;
	st[++idx]=x;
	vis[x]=1;
	for(int i=head1[x];i;i=a1[i].nxt){
		int t=a1[i].to;
		if(!dfn[t]){
			tarjan(t);
			low[x]=min(low[x],low[t]);
		}
		else if(vis[t]) low[x]=min(low[x],dfn[t]);
	}
	if(low[x]==dfn[x]){
		++tot;
		while(x!=st[idx+1]){
			++w[tot];
			vis[st[idx]]=0;
			c[st[idx]]=tot;
			--idx;
		}
	}
}
ll vvis[maxn];
ll get(int x){
	if(vvis[x]) return vvis[x];
	vvis[x]=w[x];
	for(int i=head[x];i;i=a[i].nxt){
		vvis[x]+=get(a[i].to);
	}
	return vvis[x];
}
void solve(){
	int n;
	cin>>n;
	rep(i,1,n){
		int t;
		cin>>t;
		add1(i,t);
	}
	rep(i,1,n)
		if(!dfn[i]) tarjan(i);
	rep(j,1,n)
		for(int i=head1[j];i;i=a1[i].nxt){
			if(c[j]!=c[a1[i].to]){
				add(c[j],c[a1[i].to]);
			}
		}
	rep(i,1,n)
		if(!vvis[i]) get(i);
	ll ans=0;
	rep(i,1,n) ans+=vvis[c[i]];
	cout<<ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

其实可以说是基环树？

## Idea

我们都知道，$n$ 个点 $n-1$ 条边的图是树。

那么在上面加一条边，它就会产生一个环。

如果我们把本题的图画一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ueerc9mp.png)

（这只是一种可能情况，不是样例。）

虽然这个图很复杂，但是它其实只由 $2$ 部分组成：

![](https://cdn.luogu.com.cn/upload/image_hosting/qe7hwima.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ceqbn9i3.png)

（下面这个图是将对应连通块重新整排之后得到的，点的关系不变）

分析一下，无论这个连通块长什么样子，它都有一个环，环上的每个点为根牵引着一颗子树。

所以我们的第一步是找环。

找环我们可以使用拓扑排序，当然也可以直接模拟。

这里讲一讲模拟的做法：从随便一个点出发，往它的后继跳，途中记录哪个点被走到了，如果走到了已经被走到的点，则说明这个点一定在环上，从上次到这次之间被走到的点都在环上。

可以手搓一下：

对于以下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qe7hwima.png)

我们选择 $6$ 号点出发。

首先，$6$ 号点只能往 $4$ 号点跳。

接着到 $5$ 号点。

接着到 $1$ 号点。

然后不断地沿着它的出边跳，依次经过 $8$ 号、$9$ 号、$7$ 号点，然后又回到 $1$ 号点。

然后就会发现 $1$ 号、$8$ 号、$9$ 号、$7$ 号点都在环上了。

设这个环的长度为 $q$，则环上的点可通达的点数就是 $q$。

然后对于每个环上的点进行 dfs，为了 dfs 我们需要建反图。

dfs 到了一个点，它的答案就是它父亲的答案加 $1$。

注意可能有多个连通块，因此记录哪个点有答案了，然后多找几个环。

## Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node {
	int u,v,nxt;
} e[200005];
int n,x[200005],cnt,head[200005],huan[200005],t[200005],vis[200005],viss[200005],tot,tott,ans[200005];
void add(int u,int v) {
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int now,int ceng) {
	ans[now]=tott+ceng;
	vis[now]=1;
	for(int i=head[now]; i; i=e[i].nxt) {
		if(!vis[e[i].v])dfs(e[i].v,ceng+1);
	}
	return;
}
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>x[i];
		add(x[i],i);
	}
	for(int j=1; j<=n; j++) {
		tot=0;tott=0;
		while(vis[j])j++;
	//	cout<<j<<endl;
		if(j>n)break;
		t[++tot]=j;
		int ii;
		for(ii=j;; ii=x[ii]) {
			t[++tot]=ii;
			if(viss[ii])break;
			viss[ii]=1;
		}
	//	memset(viss,0,sizeof(viss));
		for(int i=tot-1; i>=1; i--) {
			huan[++tott]=t[i];
		//	cout<<huan[tott]<<' ';
			if(t[i]==t[tot])break;
		}
	//	cout<<endl;
		for(int i=1; i<=tott; i++) {
			ans[huan[i]]=tott;
			vis[huan[i]]=1;
		}
		for(int i=1; i<=tott; i++) {
			dfs(huan[i],0);
		}
		//memset(vis,0,sizeof(vis));
	}
	long long sum=0;
	for(int i=1; i<=n; i++){
		sum+=ans[i];
	//	cout<<ans[i]<<' ';
	}
	cout<<sum;
	return 0;
}
```

---

