# [POI 2018 R2] 自行车道 Bike paths

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5068)。

## 题目描述

**题目译自 [XXV Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi25-2/dashboard/) [Drogi rowerowe](https://szkopul.edu.pl/problemset/problem/aKKSmtjWTtDOEHDqnmQ3-eAA/statement/)**

拜托城国王 Bajtazar 倾听民意，决定将部分预算盈余用于修建自行车道。皇家道路顾问已设计了一套单向自行车道网络，连接各路口，但经国王要求进行了多次修改。网络由连接路口 $u$ 到 $v$ 的单向路段组成。从路口 $u$ 到 $v$ 的路径定义为任意一串不同路口序列 $u=v_0, v_1, \ldots, v_k=v$，其中每对连续路口 $v_i, v_{i+1}$ $(0 \leq i < k)$ 由从 $v_i$ 到 $v_{i+1}$ 的路段连接。

国王要求网络「公平」，即满足：若从路口 $v$ 无法到达路口 $u$（不存在从 $v$ 到 $u$ 的路径），则从 $u$ 到 $v$ 至多只有一条路径。国王认为，这能避免路口 $v$ 的居民嫉妒路口 $u$ 的居民。

市民自行车委员会获取了这一公平网络的设计，却对此不满，认为它不便于城市出行。他们需提交报告，急需确凿数据。你需计算网络的通达度，即对于每个路口 $v$，计算从 $v$ 可达的路口数量。

## 说明/提示

**样例 1 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/hvqu1a0f.png)

**附加样例**

1. $n=25, m=600$，每路口到其他路口均有路段。
2. $n=55, m=54$，含孤立路口及长度 $2$ 至 $10$ 的独立环。
3. $n=50000, m=49999$，所有路口在一条路径上。
4. $n=50000, m=50000$，所有路口在一个环上。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n \leq 60$              | $12$ |
| $2$    | $n, m \leq 5000$         | $8$  |
| $3$    | $n \leq 50000, m \leq 100000$，若 $u > v$，则无从 $u$ 到 $v$ 的路径 | $18$ |
| $4$    | $n \leq 50000, m \leq 100000$，若从 $u$ 可达 $v$，则 $v$ 不可达 $u$ | $18$ |
| $5$    | $n \leq 50000, m \leq 100000$ | $44$ |

## 样例 #1

### 输入

```
7 7
1 4
1 6
4 2
6 2
2 1
5 3
3 7```

### 输出

```
3
3
1
3
2
3
0```

# 题解

## 作者：Lysea (赞：3)

### Description

给你一个图，满足：

>若不存在从 $v$ 到 $u$ 的路径，则从 $u$ 到 $v$ 至多只有一条路径。

问每个点可以到达多少个点。

### Solution

首先一个强连通分量中的点一定能够互相到达，先缩点。

然后考虑这个性质意味着什么：缩点后，若不存在从 $v$ 到 $u$ 的路径，但从 $u$ 到 $v$ 存在多条路径，则这个图存在“环”。

这里的“环”是不考虑方向的，即将整张图视为无向图的情况下的环。

这也就意味着将整张图视为无向图的情况下，缩点后我们会得到一颗树。

但值得注意，这棵树不一定是内向树或者外向树，它的方向是不定的，所以不能直接找一个根进行 dfs。

但可以考虑记忆化记录每个点能够到达的点的个数，跑多次 dfs，那么这题就做完了。

时间复杂度 $O(n+m)$。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
#define INF 1e18
using namespace std;
struct star{
	int next,to;
}e[N];
vector<int>vt[N];
bool vis[N];
map<pair<int,int>,bool>mp;
int n,m,dfn[N],low[N],sck[N],fnt,tot,c[N];
int cnt,head[N],qwq,bel[N],in[N],siz[N];
void add(int u,int v){
	e[++cnt].next=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	sck[++fnt]=x,vis[x]=true;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(vis[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		qwq++;
		while(int z=sck[fnt--]){
			vis[z]=false;
			bel[z]=qwq,siz[qwq]++;
			if(x==z) break;
		}
	}
}
void rebuild(){
	for(int i=1;i<=n;i++){
		for(int j=head[i];j;j=e[j].next){
			int y=e[j].to;
			if(bel[i]==bel[y]||mp[{bel[i],bel[y]}]) continue;
			vt[bel[i]].push_back(bel[y]);
			mp[{bel[i],bel[y]}]=1;
		}
	}
}
int dfs(int x){
	if(c[x]) return c[x];
	c[x]=siz[x];
	for(int v:vt[x]){
		dfs(v);
		c[x]+=c[v];
	}
	return c[x];
}
signed main(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) Tarjan(i);
	rebuild();
	for(int i=1;i<=qwq;i++) dfs(i);
	for(int i=1;i<=n;i++) cout<<c[bel[i]]-1<<endl;
	return 0;
}
```

---

## 作者：cuiyuchen (赞：3)

# P12760 解题报告

## 这是一篇不需要注意力的题解

这题有点新，没什么人做，正好最近在练习 tarjan，就写一篇题解来巩固一下。~~刷估值~~

前置知识：tarjan 求 scc，缩点。

如果不会：[【模板】缩点](www.luogu.com.cn/problem/P3387)

首先，不难发现，在同一个连通块中，所有节点的答案相同。所以便有了缩点的想法。

缩点之后怎么办呢？注意到**缩点之后的图一定是 DAG**（有向无环图）就可以愉快地打记搜了。

虽然由题设可知，缩点之后的图是一颗树，相比于 DAG，树的条件显然更强，但是我们记搜只需要 DAG。~~终于不需要注意力了~~

关于记搜的实现：回溯的时候进行转移
不难得到转移方程： 

$$
dp_u = \sum dp_v
$$

初始化如下
$$
dp_u = scc_u
$$

$scc$ 就是强联通分量大小。


注意一下节点本身不加入计数，下面就是喜闻乐见的 AC 环节。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e4;
int n,m;
vector <int> g[N + 5],_g[N + 5];
int dfn[N + 5],low[N + 5];
int cnt;
stack <int> st;
bool inst[N + 5];
int cnte;
int belong[N + 5];
vector <vector <int> > scc;
void tarjan(int x,int fa){
	dfn[x] = low[x] = ++cnt;
	st.push(x);
	inst[x] = true;
	for(auto it : g[x]){
		if(!dfn[it]){
			tarjan(it,x);
			low[x] = min(low[x],low[it]);
		}else if(inst[it])
		    low[x] = min(low[x],dfn[it]);
	}
	if(dfn[x] == low[x]){
		vector <int> v;
		while(st.size() && st.top()!= x){
			v.push_back(st.top());
			inst[st.top()] = false;
			belong[st.top()] = cnte;
			st.pop();
		}
		v.push_back(x);
		inst[x] = false;
		belong[x] = cnte;
		st.pop();
		scc.push_back(v);
		cnte++;
	}
}
int dp[N + 5];
void dfs(int x){
	if(dp[x])
	    return;
	for(auto it : _g[x]){
		dfs(it);
		dp[x] += dp[it];
	}
	dp[x] += scc[x].size();
}
int main(){
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
	}
	for(int i = 1;i <= n;i++){
		if(!dfn[i])
			tarjan(i,0);
	}
	for(int i = 0;i < cnte;i++)
		for(auto it : scc[i])
			for(auto j : g[it])
				if(belong[j] != i){
					_g[i].push_back(belong[j]);
				}
	for(int i = 0;i < cnte;i++)
		if(!dp[i])
			dfs(i);
	for(int i = 1;i <= n;i++)
	    cout << dp[belong[i]] - 1 << endl;
	return 0;
}
```

---

## 作者：Noimityx (赞：2)

# P12760 题解

**前言**：本题是经典的 Tarjan 应用，解法为**缩点 + 重构图 + 拓扑求值**。

## 题意
给定有向图，满足性质：
> 若路口 $v$ 无法到达 $u$（不存在 $v \to u$ 的路径），则 $u \to v$ 至多只有一条路径

求每个点能到达的除自身外的点数。

## Solution
1. **缩点**：强连通分量内的点可达数量相同
2. **重构图**：对强连通分量缩点后反向建图
3. **拓扑求值**：按拓扑序递推 $ans[u] \gets ans[u] + ans[v]$

## Code
```cpp
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
const int Maxn = 5e4 + 100, Maxm = 1e5 + 100;

struct Edge { int u, v, nxt; } edge[Maxm], se[Maxn];
int head[Maxn], cnt, sh[Maxn], cnts;
int dfn[Maxn], low[Maxn], dfncnt;
stack<int> sta, e;
bool Instack[Maxn];
int Scc[Maxn], scccnt, Size_Scc[Maxn], d[Maxn];
int s[Maxn], ans[Maxn];

int Find(int u) { return s[u] == u ? u : s[u] = Find(s[u]); }
void merge(int u, int v) { s[Find(u)] = Find(v); }

void Add(int u, int v, int &cnt, int head[], Edge edge[]) {
    edge[++cnt] = {u, v, head[u]};
    head[u] = cnt;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++dfncnt;
    sta.push(u); Instack[u] = 1;
    for(int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        e.push(i);
        if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if(Instack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) {
        scccnt++;
        while(sta.top() != u) {
            Scc[sta.top()] = scccnt;
            Instack[sta.top()] = 0;
            Size_Scc[scccnt]++;
            sta.pop();
        }
        Scc[u] = scccnt;
        Instack[u] = 0;
        Size_Scc[scccnt]++;
        sta.pop();
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for(int u,v; m--;) {
        cin >> u >> v;
        Add(u, v, cnt, head, edge);
    }
    for(int i = 1; i <= n; i++) 
        if(!dfn[i]) tarjan(i);

    for(int i = 1; i <= scccnt; i++) s[i] = i;
    while(!e.empty()) {
        int i = e.top(); e.pop();
        int u = edge[i].u, v = edge[i].v;
        if(Scc[u] == Scc[v] || Find(Scc[u]) == Find(Scc[v])) continue;
        merge(Scc[u], Scc[v]);
        Add(Scc[v], Scc[u], cnts, sh, se);
        d[Scc[u]]++;
    }

    queue<int> q;
    for(int i = 1; i <= scccnt; i++) {
        if(!d[i]) q.push(i);
        ans[i] = Size_Scc[i];
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = sh[u]; i; i = se[i].nxt) {
            int v = se[i].v;
            ans[v] += ans[u];
            if(!--d[v]) q.push(v);
        }
    }
    for(int i = 1; i <= n; i++)
        cout << ans[Scc[i]] - 1 << '\n';
}

---

## 作者：MaiJingYao666 (赞：1)

# P12760 [POI 2018 R2] 自行车道 Bike paths 题解  
### 题面分析  
根据题目，我们知道当前的道路设计是皇帝在“公平”政策下设计的，因此满足“若从路口 $v$ 无法到达路口 $u$（不存在从 $v$ 到 $u$ 的路径），则从 $u$ 到 $v$ 至多只有一条路径”的原则。这有啥用？好不管了，我们要求的就是每个路口 $v$，计算从 $v$ 可达的路口数量。  
### 解题思路  
很自然想到可以缩点，显然构成环的点能到达的路口数是一样的，所以先用 `tarjan` 缩点。缩完点后因为要求可以到达的地方，所以可以建反图。但这时候我们该如何高效求能到达的点的个数呢？这时候我们前面提到的“公平”原则就发挥了作用，仔细一想，这不就是树的意思吗。再根据 `DAG` 的性质，很容易得出缩完点后会得到“类有向森林”。那就用反图拓扑，下传下去就可以了。为什么说是“类”呢，因为很显然是没有“有向森林”的，只是说讲将有向边视作无向边后是森林，所以要注意要像拓扑一样，等到入度减到 0 再入队。  
最后记得减 1（自己）。  
### AC 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
int n,m;
vector<int> G[N],G2[N];
int dfn[N],low[N],cnt,stk[N],top,scc,sc[N],siz[N];
bool in[N];
void tarjan(int p){
	dfn[p]=low[p]=++cnt;
	stk[++top]=p;
	in[p]=1;
	for(auto j:G[p]){
		if(!dfn[j]){
			tarjan(j);
			low[p]=min(low[p],low[j]);
		}
		else if(in[j]) low[p]=min(low[p],dfn[j]);
	}
	if(low[p]==dfn[p]){
		scc++;
		int y;
		while(1){
			y=stk[top--];
			siz[scc]++;
			sc[y]=scc;
			in[y]=0;
			if(y==p) return;
		}
	}
}
int d[N];
int ans[N];
inline void topsort(){
	queue<int> q;
	for(int i=1;i<=scc;i++){
		if(d[i]==0) q.push(i);
		ans[i]=siz[i];
	}
	while(q.size()){
		int ver=q.front();
		q.pop();
		for(auto j:G2[ver]){
			d[j]--;
			ans[j]+=ans[ver];
			if(d[j]==0) q.push(j);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++){
		for(auto j:G[i]){
			if(sc[i]!=sc[j]){
				G2[sc[j]].push_back(sc[i]);
				d[sc[i]]++;
			}
		}
	}
	topsort();
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[sc[i]]-1);
	}
}
```

---

## 作者：lzdll (赞：0)

## 前言

练习 Tarjan 时做到了这道题目，然后看到保证公平的性质非常的懵，感觉对题目影响不大，于是就开写了。事实证明本题比较诈骗，题目给出的「公平」性质根本没用。

## 做法

首先我们看到题目让求能到达多少点，可以自然地想到缩点后拓扑排序。然后观察样例，发现我们需要手动减一（减去自己），然后就做完了。

值得注意的是，我们在建图的时候需要建反图，因为我们要从入度为 $0$ 的点开始往后算。当然，也可以正常建图，然后使用树形 DP 来求解。

然后建图的时候别忘了判重边和自环就行了。

## 关于国王要求的「公平」

题目的本意应该是这样的：保证缩完点之后，可以变成一颗有向树。但是我们缩点后的 DAG 与有向树没有本质上的区别，都没有环，所以无后效性。而我们的 Tarjan 缩点和拓扑排序复杂度是 $\Theta(n+m)$ 的。由于我们读入就是 $\Theta(m)$，输出是 $\Theta(n)$。所以本题最优复杂度就是 $\Theta(n+m)$ 的了，就算能使用题目的性质也不会更优了。

~~突然想到皇室战争的老国王~~
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define R(x) x=read()
using namespace std;
inline int read() {
	int x=0,y=1;
	char e=getchar();
	while(e<'0'||e>'9') {
		if(e=='-')y=-1;
		e=getchar();
	}
	while(e>='0'&&e<='9') {
		x=(x<<1)+(x<<3)+(e^'0');
		e=getchar();
	}
	return x*y;
}
const int N=50005;
int n,m;
vector<int>G1[N],G2[N];
int dfn[N],low[N],times,ins[N],bel[N],sum[N],cnt;
stack<int>s;
int ind[N];
queue<int>q;
unordered_map<int,bool>mp;
int hax(int x,int y){
	return x*1000000+y;
}
void Tarjan(int u){
	dfn[u]=low[u]=++times;
	ins[u]=1;
	s.push(u);
	for(auto v:G1[u]){
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		int v;
		++cnt;
		do{
			v=s.top();
			s.pop();
			ins[v]=0;
			bel[v]=cnt;
			++sum[cnt];
		}while(v!=u);
	}
}
signed main() {
	R(n),R(m);
	for(int i=1;i<=m;++i){
		int u,v;
		R(u),R(v);
		G1[u].push_back(v);
	}
	for(int i=1;i<=n;++i){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=1;i<=n;++i){
		for(auto j:G1[i]){
			int u=bel[i],v=bel[j],h=hax(u,v);
			if(u==v||mp[h])continue;
			mp[h]=1;
			G2[v].push_back(u);//opposite graph
			++ind[u];
		}
	}
	for(int i=1;i<=cnt;++i){
		if(!ind[i])q.push(i);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto v:G2[u]){
			sum[v]+=sum[u];
			if((--ind[v])==0)q.push(v);
		}
	}
	for(int i=1;i<=n;++i){
		cout<<sum[bel[i]]-1<<"\n";
	}
	return 0;
}

```

---

## 作者：wydqwq (赞：0)

[题面](https://www.luogu.com.cn/problem/P12760)

## 思路

题面说了一大堆没用的，只需要看到最后一句：**计算从 $v$ 可达的路口数量**。

明显地，一个强连通分量中的点可以互相到达，于是我们可以先使用 Tarjan 进行缩点。

然后，我们就得到了一张 DAG，容易发现如果用正图的话要递归计算其他点权，于是我们就可以建一张反图，再用 Topsort 递推。

对于每个点 $v$，他自己是不能对自己产生贡献的，所以最后的答案要 $-1$。

于是这题就做完了。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10,M=1e6+10,inf=1e18;
int n,m;
int tot;
int a[N];
int u[M],v[M];
vector<int> e[N];
vector<int> ne[N];
int fa[N],dfn[N],low[N];
int SCC,scc[N],sz[N];
stack<int> s;
bool ins[N];
int ans;
int in[N],f[N];
void add(int x,int y){
	e[x].push_back(y);
}
void Tarjan(int u){
	tot++;
	dfn[u]=low[u]=tot;
	s.push(u);
	ins[u]=1;
	for(int v:e[u]){
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		SCC++;
		while(1){
			int cur=s.top();
			s.pop();
			ins[cur]=0;
			scc[cur]=SCC;
			sz[SCC]++;
			if(cur==u) break;
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		add(u[i],v[i]);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) Tarjan(i);
	}
	for(int i=1;i<=m;i++){
		if(scc[u[i]]!=scc[v[i]]){
			ne[scc[v[i]]].push_back(scc[u[i]]);
			in[scc[u[i]]]++;
		}
	}
	queue<int> q;
	for(int i=1;i<=SCC;i++){
		f[i]=sz[i];
		if(!in[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:ne[u]){
			in[v]--;
			f[v]+=f[u];
			if(!in[v]) q.push(v);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<f[scc[i]]-1<<"\n";
	}
	return 0;
}
```

---

## 作者：lw393 (赞：0)

有向图上面跑可达点问题，先无脑缩点。

然后就是经典的建缩点后的反图，再配上拓扑排序来进行：

$$dp_u = siz_u + \sum_{(v,u)\in E}dp_v$$

其中 $E$ 为缩完点以后的边集。最后答案就是每个点所在的代表的答案减一。

代码：

```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

vector<int>G[N], G_scc[N];
#define pb push_back
int dfn[N], low[N], ins[N], num;
stack<int>s;
int scc[N], siz[N], scc_cnt;

void tarjan(int u) {
  dfn[u] = low[u] = ++num, ins[u] = 1; s.push(u);
  for(auto v : G[u]){
    if(!dfn[v]) { tarjan(v); low[u] = min(low[u], low[v]); }
    else if(ins[v]) { low[u] = min(low[u], dfn[v]); }
  }
  if(low[u] == dfn[u]) {
    int v; scc_cnt++;
    do{
      v = s.top(); s.pop();
      scc[v] = scc_cnt; siz[scc_cnt]++;
      ins[v] = 0;
    }while(v != u);
  }
}

int in[N], dp[N];

void solve(){
  int n, m; cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    G[u].pb(v);    
  }
  for(int i = 1; i <= n; i++)
    if(!dfn[i]) tarjan(i);
  map<pair<int, int>, int>mm;
  for(int u = 1; u <= n; u++)
    for(auto v : G[u]) {
      if(scc[u] == scc[v]) continue;
      if(mm.count({scc[v], scc[u]})) continue;
      G_scc[scc[v]].pb(scc[u]); mm[{scc[v], scc[u]}] = 1;
      in[scc[u]]++;
    }
  queue<int>q;
  for(int i = 1; i <= scc_cnt; i++) {
    if(!in[i]) q.push(i);
    dp[i] = siz[i];
  }
  while(!q.empty()){
    int u = q.front(); q.pop();
    for(auto v : G_scc[u]) {
      in[v]--; dp[v] += dp[u];
      if(!in[v]) q.push(v);
    }
  }
  for(int i = 1; i <= n; i++)
    cout << dp[scc[i]] - 1 << '\n';
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
```

---

## 作者：ivyjiao (赞：0)

这是一篇 kosaraju 题解。

题面有用的其实就一句话。

> 你需计算对于每个路口 $u$，从 $u$ 可达的路口数量。

想到缩点成 DAG，然后每个强连通分量的点权为 $sum_u$，建立新图后对每个点进行一次深搜就行了。

方程式：

$$dp_u=sum_u+\sum_{存在边(u,v)} dp_v$$

最后别忘了每个点的答案要 $-1$，因为不包括自己。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50001;
int T,n,m,u,v,vis[N],col[N],dp[N],rd[N],sum[N],cnt,ans;
vector<int>G[N],H[N],I[N],s;
void dfs1(int u){
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(!vis[v]) dfs1(v);
	}
	s.push_back(u);
}
void dfs2(int u){
	col[u]=cnt;
	sum[cnt]++;
	for(int i=0;i<H[u].size();i++){
		int v=H[u][i];
		if(!col[v]) dfs2(v);
	}
}
void kosaraju(){
	for(int i=1;i<=n;i++) if(!vis[i]) dfs1(i);
	for(int i=n-1;i>=0;i--){
		if(!col[s[i]]){
			cnt++;
			dfs2(s[i]);
		}
	}
}
void dfs(int u){
	dp[u]=sum[u];
	for(int i=0;i<I[u].size();i++){
		int v=I[u][i];
		if(!dp[v]) dfs(v);
		dp[u]+=dp[v];
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		G[u].push_back(v);
		H[v].push_back(u);
	}
	kosaraju();
	for(int i=1;i<=n;i++){
		for(int j=0;j<G[i].size();j++){
			int v=G[i][j];
			if(col[i]!=col[v]){
				I[col[i]].push_back(col[v]);
				rd[col[v]]++;
			}
		}
	}
	for(int i=1;i<=cnt;i++) if(!dp[i]) dfs(i);
	for(int i=1;i<=n;i++) cout<<dp[col[i]]-1<<endl;
}
```

---

## 作者：Hhy140516 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12760)
# 题意
计算每个点可以到达的点的个数。
# 分析
前置知识：[强连通分量](https://oi.wiki/graph/scc/)。

这题是强连通分量的拓展缩点，发现一个强连通分量所有点都可以到，所以可以看作一个点。

这样再进行一个树上 DP。对于一个点任意儿子，他都可以到达，所以需要 $dp _ u + dp_ v$。
```cpp
//Code by hhy
#include<bits/stdc++.h>
//#define int long long
#define ull unsigned long long
#define ll long long
using namespace std ;
const int kMaxN = 5e4 + 5 , MOD = 998244353 , INF = 1e18 ;
struct node
{
	int v , nxt ;
}edge[100005] ;
struct edge
{
	int u , v ;
}Node[100005] ;
int n , m ;
int color[kMaxN] , siz[kMaxN] , dfn[kMaxN] , low[kMaxN] , head[kMaxN] , dp[kMaxN] , tim , cnt , scc ; 
bool vis[kMaxN] ;
stack<int> st ;
void add_edge(int u , int v)
{
	edge[++cnt] = {v , head[u]} ;
	head[u] = cnt ;
}
void tanjan(int u)
{
	dfn[u] = low[u] = ++tim ;
	vis[u] = 1 ;
	st.push(u) ;
	for( int i = head[u] ; i ; i = edge[i].nxt )
	{
		int v = edge[i].v ;
		if(dfn[v] == 0)
		{
			tanjan(v) ;
			low[u] = min(low[u] , low[v]) ;
		}
		else if(vis[v])
		{
			low[u] = min(low[u] , dfn[v]) ;
		}
	}
	if(low[u] == dfn[u])
	{
		scc++ ;
		while(!st.empty())
		{
			vis[st.top()] = 0 ;
			siz[scc]++ ;
			color[st.top()] = scc ;
			if(u == st.top())
			{
				st.pop() ;
				break ;
			}
			st.pop() ;
		}
	}
}
void dfs(int u)
{
	if(dp[u] != -1) return ;
	dp[u] = siz[u] ;
	for( int i = head[u] ; i ; i = edge[i].nxt )
	{
		int v = edge[i].v ;
		if(dp[v] == -1) dfs(v) ;
		dp[u] += dp[v] ;
	}
}
void work()
{
	cin >> n >> m ;
	for( int i = 1 ; i <= m ; i++ ) 
	{
		int u , v ;
		cin >> u >> v ;
		add_edge(u , v) ;
		Node[i] = {u , v} ;
	}
	for( int i = 1 ; i <= n ; i++ )
	{
		if(dfn[i] == 0)
		{
			tanjan(i) ;
		}
	}
	cnt = 0 ;
	memset(head , 0 , sizeof head) ;
	for( int i = 1 ; i <= m ; i++ )
	{
		if(color[Node[i].u] != color[Node[i].v])
		{
			add_edge(color[Node[i].u] , color[Node[i].v]) ;
		}
	}
	memset(dp , -1 , sizeof dp) ;
	for( int i = 1 ; i <= scc ; i++ )
	{
		if(dp[i] == -1)
		{
			dfs(i) ;
		}
	}
	for( int i = 1 ; i <= n ; i++ )
	{
		cout << dp[color[i]] - 1 << "\n" ;
	}
}
signed main()
{
//	freopen("T2.in" , "r" , stdin) ;
//	freopen("T2.out" , "w" , stdout) ;
	ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
  int t = 1 ;
  // cin >> t ;
  while(t--) work() ;
  return 0 ;
}

```

---

## 作者：liyp (赞：0)

## 前置芝士
首先你要学会 [缩点](https://www.luogu.com.cn/problem/P3387) 和 [DFS](https://oi.wiki/search/dfs/)。

~~但是好像会缩点都会DFS~~
## 题目简述
给你一个 $n$ 个点 $m$ 条边的有向图，求从一个点出发最多可以到达多少个除了这个点以外的点。

## 思路
赤裸裸的缩点。

### 缩点
很简单，对于这种有向图，如果直接在原图上搜索找最长，但凡有一个环，就会 ``TLE``。

所以我们要把图上的所有环去掉，最好**表示成一个点**，这样就可以快乐的搜索了！

恭喜你，这就是缩点的本质，**环变点**！

缩点看似很简单，不就是把所有的环统计出来，然后建一个新图，把一个环上所有点的边集中起来，把点权加和即可。

但是有个坑！

首先，我在对环上的所有点统计边的时候，**有可能两个点实际上在同一个环（又称强连通分量）上**，在新图中就会出现一个自环，这毫无疑问是影响答案的。

所以我们要加一个特判。

```cpp
if(color[i]!=color[j] and !mp2[color[i]][color[j]])
```
如果你没有判自环的话你多半会和我一样 ``TLE``。

### 统计
显然的，一个强连通分量（环）上的点的答案一定是相同的，因为强连通分量上的点是互通的。

所以直接在新图上搜索。

你以为这道题可以爆切了，结果你 ``TLE`` 了。

加个记忆化。由于缩点完成后的点是一个有向无环图，所以一个点上的答案是唯一的。

完结撒花！

## 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 5e4 + 10;
int n,m;
vector<int>v[MAXN],v2[MAXN];// 原图和新图
bool inst[MAXN];int dfn[MAXN],low[MAXN]; //inst数组判断是否在栈中
stack<int>st;int cnt=0,color[MAXN],sccnum=0; //color染色
vector<int>sccs[MAXN];//记录强连通分量（环）
int sccsum[MAXN];//记录新图点权
void tarjan(int x){//标准
	dfn[x]=low[x]=++cnt;
	st.push(x);
	inst[x]=1;
	for(auto i:v[x]){
		if(!dfn[i]){
			tarjan(i);
			low[x]=min(low[x],low[i]);
		}
		else if(inst[i]==1){
			low[x]=min(low[x],dfn[i]);
		}
	}
	if(low[x]==dfn[x]){
		sccnum++;
		while(!st.empty()){
			inst[st.top()]=0;
			color[st.top()]=sccnum;
			sccsum[sccnum]+=1;
			sccs[sccnum].push_back(st.top());
			if(st.top()==x){
				st.pop();
				break;
			}
			st.pop();
		}
	}
	return;
}
unordered_map<int,unordered_map<int,bool> >mp,mp2;
// mp为原图判重边，mp2为新图判自环
int vis[MAXN];
int dfs(int x){// dfs求最值
	if(vis[x]) return vis[x];
	vis[x]=sccsum[x];
	for(auto i:v2[x]){
		vis[x]+=dfs(i);
	}
	return vis[x];
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,t;
		cin>>u>>t;
		if(mp[u][t]) continue;
		mp[u][t]=1;
		v[u].push_back(t);
	}
	
	//SCC
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(auto j:v[i]){
			// 防止自环
			if(color[i]!=color[j] and !mp2[color[i]][color[j]]){
				v2[color[i]].push_back(color[j]);
				mp2[color[i]][color[j]]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		
		cout<<dfs(color[i])-1<<endl;
	}
	return 0;
} 
```

---

## 作者：Zyh20101221 (赞：0)

好不容易发现这么水的题，赶紧来一发题解。

题目大意很简单，看看样例的解释后就会明白了。我这里采用的是缩点 $+$ dfs。

为什么会想到缩点？因为每个联通块中每个节点的答案是相同的（仅限在块中），~~而最近又恰好学了缩点~~。

随后就是 dfs 了，用 $dp$ 数组来记录答案，非常简单，具体看代码：

```cpp
//
// Created by Administrator on 2025/7/31.
//
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
vector<int>g[N],ng[N];
int dfn[N],low[N],num,cnt,belong[N],sum[N],u[N],v[N],dp[N];
stack<int>s;

void tarjan(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    for(auto to:g[u]){
        if(!dfn[to]){
            tarjan(to);
            low[u]=min(low[u],low[to]);
        }
        else if(!belong[to]){
            low[u]=min(low[u],dfn[to]);
        }
    }
    if(low[u]==dfn[u]){
        int to;cnt++;
        do{
            to=s.top();
            s.pop();
            belong[to]=cnt;
            sum[cnt]++;
        }while(to!=u);
    }
}

void dfs(int u){
    if(dp[u]) return ;   //记忆化
    dp[u]=sum[u];
    for(auto to:ng[u]){
        dfs(to);
        dp[u]+=dp[to];
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        g[u[i]].push_back(v[i]);
    }
    for(int i=1;i<=n;i++) {
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=m;i++){
        int x=belong[u[i]],y=belong[v[i]];
        if(x!=y){
            ng[x].push_back(y);
        }
    }
    for(int i=1;i<=cnt;i++){
        dfs(i);
    }
    for(int i=1;i<=n;i++){
        cout<<dp[belong[i]]-1<<endl;
    }
    return 0;
}
```
注意最后答案一定要减 $1$。

---

