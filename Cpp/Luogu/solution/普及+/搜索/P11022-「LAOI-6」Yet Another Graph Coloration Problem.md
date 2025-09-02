# 「LAOI-6」Yet Another Graph Coloration Problem

## 题目描述

小 R 有一张 $n$ 个节点和 $m$ 条的边简单无向图，节点的编号依次为 $1 \sim n$。她想要为图中的每个节点分配黑色或白色的颜色，使得：

- 有至少 $1$ 个黑色节点；
- 有至少 $1$ 个白色节点；
- 对于任何一对点对 $(u, v)$，只要 $u$ 和 $v$ 的颜色不同，就存在至少 $2$ 条从 $u$ 到 $v$ 的不同的简单路径。
	- 简单路径是图上指不重复经过同一点的路径。
	- 若两条简单路径不同，要么其长度不同，要么至少存在一个正整数 $i$ 使两条路径经过的第 $i$ 个点不同。

或者，报告解不存在。

## 说明/提示

**本题采用捆绑测试**。

- Subtask 0（15 pts）：$\sum 2^n \leq 2^{16}$。
- Subtask 1（25 pts）：$n \leq 3\times 10^3$，$m \leq 3\times 10^3$，$\sum n \leq 10^4$，$\sum m \leq 2\times 10^4$。
- Subtask 2（5 pts）：保证图不连通。
- Subtask 3（10 pts）：保证每个点的度数均为 $2$。
- Subtask 4（20 pts）：保证 $n = m$。
- Subtask 5（25 pts）：无特殊限制。

对于所有数据，保证 $1 \leq T \leq 10^5$，$2 \leq n \leq 2 \times 10^5$，$0 \leq m \leq 2 \times 10^5$，$\sum n \leq 2\times 10^6$，$\sum m \leq 2\times 10^6$，保证给出的图无重边、无自环。

## 样例 #1

### 输入

```
3
4 5
1 2
1 3
1 4
2 3
3 4
5 6
1 2
1 3
1 5
2 3
2 4
3 4
6 10
1 2
1 3
1 5
2 3
2 4
2 5
2 6
3 5
3 6
4 6```

### 输出

```
BWBW
BBWWB
BWBWBW```

## 样例 #2

### 输入

```
1
4 3
1 2
1 3
2 3```

### 输出

```
-1```

# 题解

## 作者：晴空一鹤 (赞：8)

~~比赛时这题唐了一个小时，写篇题解纪念一下。~~

首先要求黑白之间至少有 $2$ 条简单路径，这很容易让我们想到缩点相关内容。

考虑使用类似的套路，我们随便选个点开始搜，得到一棵 `dfs` 搜索树，那么原图就是这棵树加上若干条返祖边（因为是无向图所以没有横叉边）。

记某条返祖边连接的两个节点中深度较深的节点为 $x$，那么我们可以把 $x$ 的整棵子树染成黑色，子树外染成白色。

那么此时黑白之间显然有 $2$ 条路径：一条是通过 `dfs` 树的路径，一条是先走 `dfs` 树到达返祖边的一端，通过返祖边再走 `dfs` 树的路径。

因此存在返祖边即有解，无解的情况就是树与不连通图。

有解时的方案构造直接模拟上述过程即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,ans,vis[200005],u,v,opt,qwq[200005],sum[200005],low[200005],dfn[200005],d;
vector<int>q[200005];
void inline dfs(int x,int fa){
   vis[x]=1;
   for(int i=0;i<q[x].size();i++){
   if(q[x][i]==fa)continue;
   if(vis[q[x][i]]){if(ans==0)ans=1,qwq[x]=1;}
   else {dfs(q[x][i],x);}
   }
}
void inline dfs2(int x,int y){

  vis[x]=1;qwq[x]=max(qwq[x],y);
   for(int i=0;i<q[x].size();i++){
   if(!vis[q[x][i]])
   {dfs2(q[x][i],max(y,qwq[x]));}
   }
}
int main(){
   cin>>t;
   while(t--){
   cin>>n>>m;
   ans=0;
   for(int i=1;i<=n;i++)q[i].clear();
   for(int i=1;i<=n;i++)vis[i]=qwq[i]=0,low[i]=1e9;
   for(int i=1;i<=m;i++){
   cin>>u>>v;
   q[u].push_back(v);
   q[v].push_back(u);
   }d=0;
   dfs(1,0);opt=0;
   for(int i=1;i<=n;i++)
   if(vis[i]==0||ans==0){opt=1;cout<<-1<<"\n";break;}
   if(opt)continue;for(int i=1;i<=n;i++)vis[i]=0;dfs2(1,0);
   for(int i=1;i<=n;i++)
   if(qwq[i])cout<<"B";
   else cout<<"W";
   cout<<"\n";
   }
}
```

---

## 作者：pigeonteam (赞：4)

## 前置
我们假设这张图最开始全部是白色的。  

## 分析
首先，我们很容易就可以得出，一个不联通的图一定不存在合法的染色方案。~~至于为什么可以自己想一想~~。  
因为一定会存在两个点不同色且不在一个连通块中，不然就是全部点都是一个颜色。  

其次，我们不难发现，在一个无向图上要有两条不同的简单路径到同一个点，那这个点就一定会在一个环上。  

然后，我们从环上任取一个点染黑，发现从这个点出去的不经过在这个环上的点的点仍然可能和这个点只有一条简单路径。并且别的点由于环的存在一定有两条简单路径通向这些点。所以我们把我们选择的点能不经过环上的点直接通向的点也染成黑色的。  
然后这道题就做完了。

## 其余提示
本题有多测，记得清空。

下面是部分代码。  
``` c++
#define maxn 200005

int t, n, m, u, v;
vector<int> g[maxn];
// 存图
bool color[maxn], vis[maxn], in[maxn], sizvis[maxn];
// color:目前的颜色 vis:在染色过程中是否被访问过
// in:是否在选中的环上 sizvis:在搜索连通块大小是是否被访问过
vector<int> lst;
// lst:表示在环上的数有哪些
int p;
// 记录dfs染色时环到哪里截止

inline int siz(int x)
{
    int ans = 1;
    sizvis[x] = 1;
    for (auto i : g[x])
    {
        if (!sizvis[i])
            ans += siz(i);
    }
    return ans;
}

inline bool dfs(int x, int fa)
{
    if (vis[x])
    {
        p = x;
        in[x] = 1;
        return true;
    }
    vis[x] = 1;
    for (auto i : g[x])
    {
        if (i == fa)
            continue;
        if (dfs(i, x))
        {
            in[x] = 1;
            lst.push_back(x);
            break;
        }
    }
    return x == p ? 0 : in[x];
}

inline void paint(int id) // 染色
{
    color[id] = 1;
    for (auto i : g[id])
    {
        if (color[i] || in[i])
            continue;
        paint(i);
    }
}

inline void init() // 初始化
{
    lst.clear();
    p = 0;
    for (int i = 1; i <= n; ++i)
    {
        g[i].clear();
        color[i] = 0;
        vis[i] = 0;
        in[i] = 0;
        sizvis[i] = 0;
    }
}

int main()
{
    FastIO::read(t);
    while (t--)
    {
        init();
        FastIO::read(n, m);
        for (int i = 1; i < n; ++i)
            g[i].clear();
        for (int i = 0; i < m; ++i)
        {
            FastIO::read(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int sizee = siz(1);
        if (sizee != n) // 不是联通图
        {
            puts("-1");
            continue;
        }
        dfs(1, 0);
        if (lst.empty()) // 没有环
        {
            puts("-1");
            continue;
        }
        paint(lst.front());
        for (int i = 1; i <= n; ++i)
            putchar(color[i] ? 'B' : 'W');
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：Eternatis (赞：3)

题目中“两条不同的简单路径”显然提示了边双，即不同色的点在一个边双内，于是猜测只有整张图为一个边双时合法，但这样会被样例卡住。

注意到在给一个点数 $\geq 3$ 的边双染色后，对于其他的点，找到离它最近的边双上的点，设置为同色即可。这样的点一定是唯一的，否则边双就不是极大的。

正确性显然：不同色的点之间的路径一定经过边双，于是存在两条不同的路径。

只需要判断连通性以及是否存在点数 $\geq 3$ 的边双即可，染色可以直接 dfs。

---

## 作者：NATO (赞：3)

简单的诈骗题，赛时倒开成功。

### 思路浅析：

看到联通，考虑生成树。

先乱做一棵生成树出来，这样两两点对之间就有一条简单路径了。

然后随便找一条非树边 $u,v$，若 $lca(u,v)=c,c\neq u,v$（这里就直接以 $1$ 为子树考虑的），那么随便将 $u$ 或 $v$ 的子树全部染白，剩下染黑即可，否则将小的那颗子树染白即可，为什么对是显然的，我其它点走树边必有一条简单路径到那颗子树内，通过走到没有被染的那个点再走选的那条非树边走到那颗子树的根节点，再走树边就是第二条简单路径，符合题意。

#### 赛时代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define db long double
using namespace std;
ll n,m,t;
struct ed
{
	ll u,v;
	bool ys;
}e[200005];
ll f[200005];
ll find(ll x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
ll sz[200005];
ll head[200005],cnt,pf[200005];
struct px
{
	ll v,next;
}edge[400005];
void add(ll u,ll v)
{
	edge[++cnt].v=v;edge[cnt].next=head[u];head[u]=cnt;
	edge[++cnt].v=u;edge[cnt].next=head[v];head[v]=cnt;
}
void dfs(ll id,ll fa)
{
	sz[id]=1;pf[id]=fa;
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(v==fa)continue;
		dfs(v,id);
		sz[id]+=sz[v];
	}
}
char col[200005];
void dfs2(ll id,ll fa)
{
	col[id]='W';
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(v==fa)continue;
		dfs2(v,id);
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cnt=0;
		cin>>n>>m;
		for(ll i=1;i<=n;++i)f[i]=i,head[i]=0,col[i]='B';
		ll cot=0;
		for(ll i=1;i<=m;++i)
		{
			cin>>e[i].u>>e[i].v;
			if(find(e[i].u)!=find(e[i].v))
			f[find(e[i].u)]=f[find(e[i].v)],e[i].ys=1,add(e[i].u,e[i].v),++cot;
			else e[i].ys=0;
		}
		if(cot!=n-1)
		{
			cout<<-1<<'\n';continue;
		}
		dfs(1,0);
		bool ok=1;
		for(ll i=1;i<=m;++i)
		{
			if(!e[i].ys)
			{
				if(sz[e[i].u]<sz[e[i].v])
				dfs2(e[i].u,pf[e[i].u]);
				else 
				dfs2(e[i].v,pf[e[i].v]);
				ok=0;
				break;
			}
		}
		if(ok)
		{
			cout<<-1<<'\n';continue;
		}
		for(ll i=1;i<=n;++i)cout<<col[i];
		cout<<'\n';
	}
}
```

---

## 作者：shuqiang (赞：2)

### Subtask 0
可以暴力枚举方案，然后遍历出两个点，如果两个点颜色不相同，就用 dfs 枚举路径。时间复杂度 $\mathcal{O(\sum (2^n+n^3))}$。

### Subtask 2
这个子任务保证图不连通，又因为题目要求必须同时有黑色节点和白色节点，所以必然有不在同一连通块的 $(u,v)$ 不同色，所以直接输出 $-1$ 即可。

代码：
```cpp
#include<iostream>
using namespace std;
int main(){
	int t; cin >> t;
	while(t--) cout << "-1\n";
	return 0;
}
```

### Subtask 3

这个子任务保证每个点的度数均为 $2$，也就是说图是由一个或多个环组成的，此时如果只有一个环，任意一个节点到另外一个节点都有两条路径，所以只需要判断图是否连通即可。

代码：
```cpp
#include<iostream>
#include<vector>

using namespace std;

const int N = 2 * 1e5 + 10;
int t, n, m, u, v, fg = 1;
vector<int> g[N];
bool vis[N];

void dfs(int u){
	vis[u] = 1;
	for(int v: g[u]){
		if(vis[v]) continue;
		dfs(v);
	}
}

int main(){
	cin >> t;
	while(t--){
		fg = 1;
		cin >> n >> m;
		for(int i = 1; i <= n; i++) g[i].clear(), vis[i] = 0;
		for(int i = 0; i < m; i++){
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(1);
		for(int i = 1; i <= n; i++) fg &= vis[i];
		if(fg){
			cout << 'B';
			for(int i = 2; i <= n; i++) cout << 'W';
			cout << '\n';
		}
		else{
			cout << "-1\n";
		}
	}
    return 0;
}
```

### Subtask 5

考虑如何简单的构造一个方案，当两个点 $(u,v)$ 连接了一条边且有一条长度大于 $1$ 的简单路径，我们就可以构造出一种方案：
- 当一个节点 $w$ 和 $u$ 存在一条不经过 $v$ 的简单路径时，把节点 $w$ 涂成白色，特别的，把点 $u$ 也涂成白色。
- 当一个节点 $w$ 和 $v$ 存在一条不经过 $u$ 的简单路径时，把节点 $w$ 涂成黑色，特别的，把点 $v$ 也涂成黑色。
- 如果没有涂完颜色，就是图不连通，无解。

如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/sc3i3ynz.png)
在这个例子中，点 $4$ 和点 $5$ 有一条边和一条简单路径 $4 \rightarrow 2 \rightarrow 3 \rightarrow 5$，而点 $1,2,3$ 都可以通过点 $4$ 或者通过点 $4$ 和点 $5$ 的简单路径的一部分到达点 $5$ 和点 $6$，所以正确性显然。

剩余的情况只能是这张图是一棵树，这种情况任意两个点之间只有一条简单路径，所以也无解。

而一条边 $(u,v)$ 有一条长度大于 $1$ 的简单路径当且仅当它不是割边，而求割边可以用 targan 算法，具体可以看[【模板】边双连通分量](https://www.luogu.com.cn/problem/P8436)，时间复杂度 $\mathcal{O(\sum (n+m))}$。

代码：

```cpp
#include<iostream>
#include<vector>
#include<map>

using namespace std;

const int N = 2 * 1e5 + 10, M = 2 * 1e5 + 10;

struct pii{
	int v, id;
};
vector<pii> g[N];
int t, n, m, u, v, tt = 0, low[N], dfn[N], a[M][2];
bool brg[M], fg = 0;
string s;

int read_int(){
    int x = 0; char ch = ' '; while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar();} return x;
}

void dfs(int u, int ine){
	low[u] = dfn[u] = ++tt;
	for(auto vv: g[u]){
		int v = vv.v, id = vv.id;
		if(id == ine) continue;
		if(dfn[v] == 0){
			dfs(v, id);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) brg[id] = 1;
		}
		else{
			low[u] = min(low[u], dfn[v]);
		}
	}
}

void dfs2(int u, int z, char c){
	s[u-1] = c;
	for(pii vv: g[u]){
		if(s[vv.v-1] != '.' || vv.v == z) continue;
		dfs2(vv.v, z, c);
	}
}

int main(){
	t = read_int();
	for(int i = 0; i < 2e5; i++) s.push_back('.');
	while(t--){
		n = read_int(); m = read_int();
		tt = fg = 0; 
		for(int i = 0; i <= n; i++) {low[i] = dfn[i] = 0; g[i].clear();}
		for(int i = 0; i <= m; i++) brg[i] = 0, s[i] = '.';
		for(int i = 1; i <= m; i++){
			u = read_int(); v = read_int();
			g[u].push_back({v, i});
			g[v].push_back({u, i});
			a[i][0] = u, a[i][1] = v;
		}
		dfs(1, 0);
		for(int i = 1; i <= n; i++){
			if(!dfn[i]) fg = 1;
		}
		if(fg) {cout << "-1\n"; continue;}
		for(int i = 1; i <= m; i++){
			if(!brg[i]){
				dfs2(a[i][0], a[i][1], 'W');
				dfs2(a[i][1], a[i][0], 'B');
				cout << s.substr(0, n) << '\n';
				break;
			}
			if(i == m) cout << "-1\n";
		}
		if(m == 0) cout << "-1\n";
	}
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：1)

一看见至少两条路径，直接想到边双联通分量。

发现一个边双中的所有点可以赋任意颜色。

对于在两个边双中有连边的两个点，也是这两个边双仅有的一条连边，不然就不满足边双性质，它们的颜色必须一样。

因为它们不能绕道边双里去走路径，否则会通过自身两次，形成环。

并且根据边双的性质，没有其他连接这两个边双的边了。

所以它们颜色相同。

用并查集维护即可。

如果所有点被合并在一个集合里了，说明这只有一个颜色，或者图不连通，直接输出负一。

否则可以有方案。

将其中一个集合赋为黑色，其它都是白色即可。

注意清空不要暴力 `memset`，会超时间，要用多少清多少。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int head[400010],to[400010],nxt[400010],tot=1;//tot=1 为了好找反向边
void add(int x,int y){
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	nxt[tot]=head[y];
	head[y]=tot;
}
int idx,cnt;
int dfn[400010],low[400010];
bool p[400010];
int st[400010],top;
int edcc[400010],edcc_cnt;
void dfs(int x,int from){//边双缩点
	dfn[x]=low[x]=++idx;
	st[++top]=x;
	for(int i=head[x];i;i=nxt[i]){
		if(!dfn[to[i]]){
			dfs(to[i],i);
			low[x]=min(low[x],low[to[i]]);
			if(low[to[i]]>dfn[x]) p[i]=p[i^1]=1;
		}
		else if((i^1)!=from) low[x]=min(low[x],dfn[to[i]]);
	}
	if(dfn[x]==low[x]){
		edcc_cnt++;
		while(st[top]!=x) edcc[st[top--]]=edcc_cnt;
		edcc[x]=edcc_cnt,top--;
	}
}
int fa[400010];
inline int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
inline void join(int x,int y){
	fa[find(x)]=find(y);
}
int CNT[400010],ans[400010];
#define f0(a) for(int i=1;i<=2*m;i++) a[i]=0;//要用多少清多少
void solve() {
	f0(head);f0(nxt);f0(dfn);f0(low);f0(p);f0(st);f0(edcc);f0(fa);f0(CNT);f0(ans);//清空
	tot=1,idx=cnt=top=edcc_cnt=0;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++) fa[i]=i;//并查集
	dfs(1,-1);
	for(int i=1;i<=n;i++) if(!dfn[i]){//图不连通
		cout<<"-1\n";
		return;
	}
	int WHITE=0;
	for(int i=1;i<=n;i++) for(int j=head[i];j;j=nxt[j]) if(edcc[to[j]]!=edcc[i]) join(i,to[j]);//维护颜色相同
	for(int i=1;i<=n;i++) CNT[find(i)]++;//统计集合大小
	if(CNT[find(1)]==n) cout<<"-1\n";//只有一个集合
	else{
		for(int i=1;i<=n;i++) if(find(i)==find(1)) ans[i]=1;else ans[i]=0;//第一个集合赋为一个颜色
		char col[2]={rand()%2 ? 'B' : 'W'};//随性  
		if(col[0]=='B') col[1]='W';
		else col[1]='B';
		for(int i=1;i<=n;i++) if(ans[i]) cout<<col[0];else cout<<col[1];//否则是其它颜色
		cout<<"\n";
	}
} 
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：luogu_starblue (赞：1)

提供一种 tarjan 的做法，~~虽然这是 Div3~~。

关于本题解的一些概念可以参照 OI Wiki [边双连通分量](https://oi-wiki.org/graph/bcc/) [割边](https://oi-wiki.org/graph/cut/)。

不会 tarjan 求割边的可以跳转至[模板题](https://www.luogu.com.cn/problem/P1656)。

注意到同一个边双联通分量中的所有点的颜色是任意的，因为他们之间都互相存在至少 $2$ 条简单路径。

然后发现在割边上的 $2$ 个节点之间不可能会有 $2$ 条及以上的简单路径，因此割边上的 $2$ 个节点之间的颜色必须相同。

因此我们先用 tarjan 求出割边然后将所有的割边上点按 dfn 排序，详细见代码，排序是为了使选的点有序，可以自己试验一下不排序会怎么样。

需要特判一下图不连通的情况。

时间复杂度 $O(\sum(n+m)+\sum(m\log m))$，瓶颈在排序。

细节见代码。

~~赛时没发挥好花费 3 个半小时多写了一坨shi山，还 WA 了。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+9;
vector<int>G[maxn];
void add(int u,int v)
{
    G[u].push_back(v);
}
int st[maxn],top;
int cnt;
int dfn[maxn],low[maxn];
struct node
{
	int u,v;
	bool operator<(const node &you)const
	{
		return dfn[u]<dfn[you.u];
	}
};
vector<node>edge;
void dfs(int u,int lst)
{
	low[u]=dfn[u]=++cnt;
	for(auto v:G[u])
	{
        if(v==lst)continue;
		if(!dfn[v])
		{
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v])
			{
				edge.push_back({u,v});
			}
		}
		else
		{
			low[u]=min(low[u],low[v]);
		}
	}
}//tarjan 
char ans[maxn];
void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    edge.clear();
    for(int i=1;i<=n;i++)
    {
        G[i].clear();
        dfn[i]=low[i]=0;
        ans[i]=0;
	}//清零不要用memset 
    cnt=0; 
    while(m--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    if(cnt!=n)
    {
    	printf("-1\n");
    	return ;
	}//特判不连通的情况 
    int tot=0;
    sort(edge.begin(),edge.end());
	for(auto it:edge)
	{
		int u=it.u,v=it.v;
		if(ans[u])
		{
			ans[v]=ans[u];
		}
		else if(ans[v])
		{
			ans[u]=ans[v];
		}
		else
		{
			++tot;//为了使染上的色多种，每有一对点就换一种颜色 
			if(tot%2==0)
			{
				ans[u]=ans[v]='B';
			}
			else
			{
				ans[u]=ans[v]='W';
			}
		}
	}
	bool b=false,w=false;//是否有黑色或白色节点 
	bool flag=false;
	for(int i=1;i<=n;i++)
	{
		if(ans[i]=='B')
		{
			b=true;
		}
		else if(ans[i]=='W')
		{
			w=true;
		}
		else if(!ans[i])//ans中空的地方可以随意放置 
		{
			flag=true;
		}
	}
	if((!b||!w)&&!flag)
	{
		printf("-1\n");
		return ;
	}//全是b或w 
	else
	{
		tot=0;
		for(int i=1;i<=n;i++)
		{
			if(ans[i])printf("%c",ans[i]);
			else
			{
				if(!b)
				{
					printf("B");
					b=true;
				}//没有b就补充b 
				else
				{
					printf("W");
				}//有b的话可能没有w于是就补充w 
			}
		}
		printf("\n");
		return ;
	}
}
int main()
{
   	int t;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

真可怕，这题我写了 140 行，估计是我写的最长基础赛代码。

两条不同的简单路径。这一看就知道是跟图上的环有关系了。

首先如果不连通或者是一棵树的话显然无解。

先随便找到一个环，并取其中一个点 $p$。不妨令 $p$ 为黑色。如果一个点不经过 $p$ 就能到达环上不为 $p$ 的其它点，那这个点到 $p$ 就一定有两条路（因为可以走环的两个方向）。这个点设为白色。

否则的话，因为连通图，点到任意其它点一定有路径，所以这个路径一定经过 $p$。这种点设为黑色。因为它到 $p$ 不一定有两条路，而且白色点到 $p$ 一定有两条以上的路径，到这种点也一定有两条以上的路径。

把 $p$ 的边中不在环上的都删掉，看这个点跟 $p$ 连不连通即可判断是上面所说的哪一种。连通的话就是第一种（黑色），否则是第二种（白色）。

判连通性使用并查集非常方便。

时间复杂度约为 $O(n+m)$。

```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
struct edge{int x,id;};
vector<edge>v[200010];
int t,n,m,xx[200010],yy[200010];
int fa[200010];
void pre(){
    for(int i=1;i<=n;i++)fa[i]=i;
}
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    fa[find(x)]=find(y);
}
bool flag[200010];
int pos;
void dfs1(int x,int last)
{
    for(auto e:v[x])
    {
        int y=e.x;
        if(y!=last)
        {
            if(flag[y])pos=y;
            else
            {
                flag[y]=1;
                dfs1(y,x);
            }
        }
    }
}
int lst[200010];
void dfs2(int x,int last)
{
    lst[x]=last;
    for(auto e:v[x])
    {
        int y=e.x;
        if(y!=last)
            if(!lst[y])
            {
                lst[y]=x;
                dfs2(y,x);
            }
    }
}
bool nodeinloop[200010];
bool edgeinloop[200010];
void dfs3(int x)
{
    for(auto e:v[x])
    {
        int y=e.x;
        if(!edgeinloop[e.id])
            if(!flag[y])
            {
                flag[y]=1;
                dfs3(y);
            }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)v[i].clear();
        pre();
        for(int i=1;i<=m;i++)
        {
            int x,y;
            cin>>x>>y;
            v[x].push_back({y,i});
            v[y].push_back({x,i});
            merge(x,y);
            xx[i]=x,yy[i]=y;
        }
        if(m<n)
        {
            cout<<-1<<endl;
            continue;
        }
        bool ff=1;
        for(int i=2;i<=n;i++)
            if(find(i)!=find(1))
            {
                cout<<-1<<endl;
                ff=0;
                break;
            }
        if(!ff)continue;
        for(int i=1;i<=n;i++)flag[i]=0;
        flag[1]=1;
        dfs1(1,0);
        for(int i=1;i<=n;i++)lst[i]=0;
        dfs2(pos,0);
        for(int i=1;i<=n;i++)nodeinloop[i]=0;
        for(int i=1;i<=m;i++)edgeinloop[i]=0;
        int now=pos;
        do
        {
            nodeinloop[now]=1;
            for(auto e:v[now])
                if(e.x==lst[now])
                {
                    edgeinloop[e.id]=1;
                    break;
                }
            now=lst[now];
        }
        while(now!=pos);
        for(int i=1;i<=n;i++)flag[i]=0;
        flag[pos]=1;
        pre();
        for(int i=1;i<=m;i++)
            if((xx[i]!=pos&&yy[i]!=pos)||edgeinloop[i])
                merge(xx[i],yy[i]);
        for(auto e:v[pos])
        {
            int y=e.x;
            if(!edgeinloop[e.id]&&find(y)!=find(pos))
            {
                flag[y]=1;
                dfs3(y);
            }
        }
        for(int i=1;i<=n;i++)
            if(flag[i])cout<<"B";
            else cout<<"W";
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

其实比较容易想到大方向，但是需要注意一些细节。

首先，至少两条路径其实很容易想到边双。同一边双内的都一定两两间至少有两条路径。因此，我们可以选择从某个边双中选一个点作为其中一色的点。

但是这样显然存在问题。如果这个点还有连向其他的边双的边，那么另一个边双上的点将只有一条路径到达这个点。

就此判无解？显然还是错的。比如有这样一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6bof1icx.png)

按照上面所说的办法则无解，可实际上我们可以将 $1,2$ 染上一个色，其余的染另一个色。

而这也恰恰启示了我们：我们可以选择将这些连向其他边双的两端染上相同的颜色。

最后注意特判一下，如果所有点都被染上了色，那么也是无解。以及不连通的照样无解。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int p, nt;
}e[400005]; int h[200005], cnt;
inline void adde(int l, int r) {
	e[++cnt].nt = h[l]; e[cnt].p = r; h[l] = cnt;
	e[++cnt].nt = h[r]; e[cnt].p = l; h[r] = cnt;
}
bitset<200008>vis;
inline void dfc(int p) {
	if (vis[p]) return; vis[p] = 1;
	for (int i = h[p]; i; i = e[i].nt) dfc(e[i].p);
}
int t, n, m, ans, cp; bitset<200005 << 1> bz; vector<int>an;
int bcc_cnt, dfn[200005], low[200005], ibc[200005];
void tarjan(int x, int in) {
	dfn[x] = low[x] = ++bcc_cnt;
	for (int i = h[x]; i; i = e[i].nt) {
		int v = e[i].p;
		if (dfn[v] == 0) {
			tarjan(v, i ^ 1);
			if (dfn[x] < low[v]) bz[i] = bz[i ^ 1] = 1;
			low[x] = min(low[x], low[v]);
		}
		else if (i != in) low[x] = min(low[x], dfn[v]);
	}
}
void dfs(int x) {
	ibc[x] = ans;
	for (int i = h[x]; i; i = e[i].nt) {
		int v = e[i].p;
		if (ibc[v] || bz[i]) continue;
		dfs(v);
	}
}
inline void dfcol(int p) {
	if (vis[p]) return; vis[p] = 1;
	for (int i = h[p]; i; i = e[i].nt)
		if (ibc[p] != ibc[e[i].p]) dfcol(e[i].p);
}
int main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n >> m; cnt = 1; bcc_cnt = 0;
		ans = 0;
		for (int i = 1; i <= n; ++i) ibc[i] = h[i] = dfn[i] = 0;
		bz.reset();
		for (int i = 1, l, r; i <= m; ++i)
			cin >> l >> r, adde(l, r);
		vis.reset(); dfc(1);
		if (vis.count() != n) {
			cout << "-1\n";
			continue;
		}
		tarjan(1, 0); vis.reset();
		for (int i = 1; i <= n; ++i)
			if (!ibc[i]) ans++, dfs(i);
		dfcol(1);
		if (vis.count() == n) {
			cout << "-1\n";
			continue;
		}
		for (int i = 1; i <= n; ++i) cout << (vis[i] ? 'B' : 'W');
		cout << endl;
	}
}
```

---

