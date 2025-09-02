# Caterpillar

## 题目描述

一个毛毛虫定义为 一个无向联通无环图上 存在一条路径 $p$ 使得任意一个节点距离 $p$ 的距离至多为 $1$ 。
毛毛虫可以包含自环 （ 一条从一个顶点连向自己的边 ），但是不可以包含重边。

这个图片是一个毛毛虫的例子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF51F/c75bb54dfb4fc3a4d0709384b3d4f7a809015076.png)

现在你有一张无向图 $G$ 。你被允许做一些合并操作。

每次操作将两个顶点合并成一个顶点 。 每次选择任意两个顶点 $a ,b (a≠b)$ , 这些顶点以及它们的边 （ 至少连接着 $a,b$ 中一个点的边 ） 将被删除 ，而后顶点 $w$ 会被加入，以及对于每条边 $(x,a),(x,b)$ 都会有新边 $( x,w)$ 加入 。 如果有一条边 $(a,b)$ 它会被转换成自环 $(w,w)$ 。 得到的图 （ 操作结束后 ） 可能会有重边。我们注意到这个操作减少了 $1$ 个顶点 ，却没有改变边的数量。

合并操作可以简单的描述为 将图中两个顶点合并为图中的一个顶点并继承原来所有的边。

你可以连续地使用合并操作，从而将给定的图转变成一个毛毛虫。

编写一个程序，这个程序将要输出这张图转变成一个毛毛虫的最少操作次数。

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
4 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6 3
1 2
3 4
5 6
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7 6
1 2
2 3
1 4
4 5
1 6
6 7
```

### 输出

```
1
```

# 题解

## 作者：yyxmy (赞：7)

这道题有一个比较直观的想法， 最后的毛毛虫显然是不会有环的，所以得先对这个图缩点，得到一棵树， 或者是一个森林；

 对一棵树，考虑如何用最少的次数合并使其变成一个毛毛虫， 我们发现所有叶节点是没有必要与其它点合并的，因为当它父亲与其它点合并的时候，它就会依附到合并的点上去，而除了叶节点的点， 要么在唯一的主链上， 要么与其他的点合并， 直至成为一条链。那么答案就很显然了，实际上就是要找到除去叶节点之后树的直径。 因为直径的两端必然都是叶节点， 那么实际上求得的就是原树的直径。

对于森林，还得需要$cnt - 1$的代价使其两两合并。 

代码也不是很难写:
```cpp
#include<bits/stdc++.h>
#define reg register
#define maxn 200001
using namespace std;
int n, m, x[maxn], y[maxn], tag[maxn], fi[maxn << 1], nt[maxn << 1], go[maxn << 1], root;
int cnt, top, low[maxn], dfn[maxn], id[maxn], deg[maxn], st[maxn], ans, cntx, sum, maxx;
void add(int u, int v){
	nt[++cnt] = fi[u]; fi[u] = cnt; go[cnt] = v;
}
void tarjan(int u, int fa){
	dfn[u] = ++cnt; low[u] = dfn[u]; st[++top] = u;
	int t = 0;
	for(int i = fi[u]; i; i = nt[i]){
		int v = go[i];
		if(v == fa && !t) { t++; continue;}
		if(dfn[v]) { low[u] = min(low[u], low[v]); continue;}
		tarjan(v, u);  low[u] = min(low[u], low[v]);
	}
	if(low[u] == dfn[u]){
		int y;  while(y = st[top--]){
			tag[y] = u;  if(y == u) break;
		}
	}
}
void dfs1(int u, int dep){
	dfn[u] = 1;
	for(int i = fi[u]; i; i = nt[i]){
		int v = go[i]; if(dfn[v]) continue;
		dfs1(v, dep + 1);
	}
	if(dep> maxx) root = u, maxx = dep;
}
void dfs2(int u, int dep, int fa){
	for(int i = fi[u]; i; i = nt[i]){
		int v = go[i]; if(v == fa) continue;
		dfs2(v, dep + 1, u);
	}
	if(dep >= maxx) maxx = dep;
}
int main()
{
	scanf("%d %d", &n, &m); 
	for(int i = 1; i <= m; i++){
		scanf("%d %d", &x[i], &y[i]);
		add(x[i], y[i]); add(y[i], x[i]); 
	}
		
	for(int i = 1; i <= n; i++) {
		top = 0; cnt = 0; if(!dfn[i]) tarjan(i, 0);
	}
	memset(fi, 0, sizeof fi); cnt = 0; top = 0;
	for(int i = 1; i <= n; i++) if(tag[i] == i) id[i] = ++top;
	for(int i = 1; i <= m; i++){
		if(tag[x[i]] != tag[y[i]]) {
		add(id[tag[x[i]]], id[tag[y[i]]]), add(id[tag[y[i]]], id[tag[x[i]]]);
		deg[id[tag[x[i]]]]++; deg[id[tag[y[i]]]]++;
		}
	}
	for(int i = 1; i <= top; i++) {  if(deg[i] == 1) ans++; }
	memset(dfn, 0, sizeof dfn);
	for(int i = 1; i <= top; i++){
		if(!dfn[i] && deg[i] == 0) sum++, ans++;
		if(!dfn[i] && deg[i] != 0) { 
			sum++;
			dfs1(i, 1), dfs2(root, 1, 0);
			root = 0; ans += maxx - 2; maxx = 0;
		}
	}
	sum--;	ans = sum + n - ans;
	cout << ans << endl;
}
```


---

## 作者：空の軌跡 (赞：5)

首先，我们用 $tarjan$ 把原图中的所有的环缩成一个点，然和记录这个双连通分量的 $size$ ，当把所有的环都缩完后，由于每个双连通分量中共有 $ size$ 个点，最终缩成一个点共需 $size-1$ 次操作，所以最终把各个点的$size-1$加入答案。

现在我们每个联通块都被缩成了树，考虑这个树内应当怎么处理。

我们可以假设这个树内已经存在了主链，为了使得每个点距离他的距离都不大于 $1$ ,我们需要把最远的节点也就是叶子节点到他的路径上的所有非叶子点合并。也就是我们最终只剩下了主链以及叶子节点，中间的节点都会被合并操作合并走。共计 （叶子节点个数 + 主链点的个数 - 相交的点的个数） 。可以看到叶子节点的个数是固定的，那么我们为了使得步数最少，需要使主链上点的个数尽量多。

所以我们需要求出这棵树的直径，以及叶子节点的个数，最后就可以求出所需要的合并步数了。但是我们要特判这棵树只有一个节点的情况。

最后就是把森林合并成一个连通块，我们直接让各棵树的主链首尾相接，计算一下就可以了。

### 代码（写丑了，大致看一下）:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
#include<stack>
#include<queue>
using namespace std;
int dfn[2010],low[2010],bel[2010],siz[2010],maxx[2010],dep[2010];
vector<int>side[2010],newside[2010];
stack<int>sta;
bool ins[2010];
int ti,cnt;
void tarjan(int x,int pre)
{
	low[x]=dfn[x]=++ti;
	ins[x]=1;sta.push(x);
	for(int i=0;i<side[x].size();i++)
	{
		int to=side[x][i];
		if(to==pre)continue;
		if(!dfn[to])
		{
			tarjan(to,x);
			low[x]=min(low[x],low[to]);
		}
		else if(ins[to])low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x])
	{
		ins[x]=0;
		bel[x]=++cnt;
		siz[cnt]=1;
		while(x!=sta.top())
		{
			ins[sta.top()]=0;
			bel[sta.top()]=cnt;
			++siz[cnt];
			sta.pop();
		}
		sta.pop();
	}
}
int id,tot,maxxx,sum;
void dfs(int x)
{
	++sum;
	if(dep[x]>maxxx)
	{
		id=x;
		maxxx=dep[x];
	}
	for(int i=0;i<newside[x].size();i++)
	{
		int to=newside[x][i];
		if(dep[to])continue;
		dep[to]=dep[x]+1;
		dfs(to);
		dep[to]=0;
	}
}
void dfs2(int x)
{
	if(dep[x]>dep[id])id=x;
	int qaq=0;
	for(int i=0;i<newside[x].size();i++)
	{
		int to=newside[x][i];
		if(dep[to])continue;
		++qaq;
		dep[to]=dep[x]+1;
		dfs2(to);
	}
	if(qaq==0)++tot;
}
int main()
{
	ios::sync_with_stdio(0);
	int n,m,a,b,ans=0;cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		side[a].push_back(b);
		side[b].push_back(a);
	}
	for(int i=1;i<=n;i++)
	if(!dfn[i])tarjan(i,0);
	for(int x=1;x<=n;x++)
	for(int i=0;i<side[x].size();i++)
	{
		int to=side[x][i];
		if(bel[to]!=bel[x])newside[bel[x]].push_back(bel[to]);
	}
	for(int i=1;i<=cnt;i++)ans+=siz[i]-1;
	--ans;
	for(int i=1;i<=cnt;i++)
	{
		if(!dep[i])
		{
			dep[i]=1;
			sum=0;maxxx=0;
			dfs(i);
			dep[i]=0;
			dep[id]=1;
			tot=1;maxxx=0;
			dfs2(id);
			if(tot!=1)ans+=sum-tot-dep[id]+2;
			++ans;
		}
	}
	cout<<ans;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF51F)

我们就分析下面这一段。

>一个毛毛虫定义为 一个无向联通无环图上 存在一条路径 $p$ 使得任意一个节点距离 $p$ 的距离至多为 $1$ 。 毛毛虫可以包含自环 （ 一条从一个顶点连向自己的边 ），但是不可以包含重边。

“无向连通无环图”即一棵无根树。树要满足以下条件：

1. 没有环（自环除外）
2. 连通

先看第一个要求。既然要没有环，那就要把所有的环，即边双连通分量全都合并。如果这个边双有两个点，就会出现重边，所以只能合并成一个点。

部分代码：
```cpp
// 1. 边双连通分量
int dfn[MAXN],low[MAXN],sum,cnt=0;
int in[MAXN];//in表示在哪个边双
stack<int> s;
void dfs(int x,int fa){//正常边双
	dfn[x]=low[x]=++sum;
	s.push(x);
	for(auto i:V[x]){
		if(!dfn[i]){
			dfs(i,x);
			low[x]=min(low[x],low[i]);
		}else if(fa!=i&&dfn[i]<dfn[x]) low[x]=min(low[x],dfn[i]);
	}
	if(low[x]==dfn[x]){
		cnt++;//新增一个
		in[x]=cnt;
		int v=s.top();
		s.pop();
		while(v!=x){
			in[v]=cnt;//记录属于哪个边双
			v=s.top();
			tot++;//合并次数多了一个
			s.pop();
		}
	}
}
```
于是，现在满足了“无环”。

接下来，现在整张图是森林，我们先分析一棵树的情况。

对于一棵树，首先我们可以知道，叶子节点肯定要用来合并其他节点，所以先忽略它们。

在剩下来的这棵树上，节点分为“在路径上”和“不在路径上”。“不在路径上”又不是叶子节点的点就需要被合并掉。

想要让被合并的尽量少，就需要让路径尽量长。

一棵树上最长的路径是什么？直径！

注意到直径两头都是叶子节点，所以合并的次数是要被合并的节点也就是：

总计点数-(直径 $+$ 度为 $1$ 的节点个数 $-2$)

这是一棵树的情况。不过要注意，如果树只有一个点，那么就不需要合并。

那森林呢？每一棵树都找出直径，然后首尾相连即可。所以答案是最开始缩边双的合并次数 $+$ 每一棵树的合并次数 $+$ 树的棵数 $-1$。

总代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 2005
// 0. 整体变量
int n,m;
int ans=0,tot=0;
vector<int> V[MAXN],G[MAXN]; 
// 1. 边双连通分量
int dfn[MAXN],low[MAXN],sum,cnt=0;
int in[MAXN];
stack<int> s;
void dfs(int x,int fa){
	dfn[x]=low[x]=++sum;
	s.push(x);
	for(auto i:V[x]){
		if(!dfn[i]){
			dfs(i,x);
			low[x]=min(low[x],low[i]);
		}else if(fa!=i&&dfn[i]<dfn[x]) low[x]=min(low[x],dfn[i]);
	}
	if(low[x]==dfn[x]){
		cnt++;
		in[x]=cnt;
		int v=s.top();
		s.pop();
		while(v!=x){
            in[v]=cnt;
			v=s.top();
            tot++;
			s.pop();
		}
	}
}
// 2. 重构树
void rebuild(){
    for(int i=1,t;i<=n;i++){
        t=in[i];
        for(auto v:V[i]){//和每一个对应的点连边（有重边没关系）
            if(t==in[v]) continue;
            G[t].push_back(in[v]);
            G[in[v]].push_back(t);
        }
    }
    n=cnt;
}
// 3. 树的直径
int L,tmp;
bool vis[100005],vis2[100005];
void dfs2(int now,int step){
	if(step>L) L=step,tmp=now;
	vis[now]=vis2[now]=1;//vis2表示这个点所在的树是否访问过
	for(auto i:G[now]){
		if(!vis[i]) dfs2(i,step+1);
	}
	return ;
}
int get_diameter(int root){
    memset(vis,0,sizeof(vis));
    L=-1;
	dfs2(root,1);//注意是1
	memset(vis,0,sizeof(vis));
	dfs2(tmp,1);
    return L;
}
// 4. 计算度为 1 的节点数和总结点数
int find_D1(int root,int fa){
    int ans=0,cnt=0;
    vis[root]=1;
    for(auto i:G[root]){
        if(!vis[i]) ans+=find_D1(i,root),cnt++;
    }
    return ans+(cnt==(fa==-1));
}
int find_ALL(int root){
    int ans=1;
    vis[root]=1;
    for(auto i:G[root]){
        if(!vis[i]) ans+=find_ALL(i);
    }
    return ans;
}
// 5. 计算
int main(){
    // 5.1. 输入
    cin>>n>>m;
    int x,y;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    // 5.2. 合并边双联通分量，重构树
    for(int i=1;i<=n;i++){
        if(!dfn[i]) dfs(i,-1);
    }
    rebuild();
    // 5.3. 对于每一棵树
    for(int Rt=1;Rt<=n;Rt++){
        if(!vis2[Rt]){
            // 5.3.1. 计算直径和度为 1 的节点数和N
            int _L=get_diameter(Rt);
            memset(vis,0,sizeof(vis));
            int _D1=find_D1(Rt,-1);
            memset(vis,0,sizeof(vis));
            int _N=find_ALL(Rt);
            // 5.3.2. 一棵树的ans：`N-(直径长度+度为1的节点数-2)`
            tot++;
            if(_N==1) continue;//注意特判
			ans+=_N-(_L+_D1-2);
        }
    }
    // 5.4. 森林：`每一棵树的ans+树的数量-1`
    cout<<ans+tot-1<<endl;
    return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

> IV. [CF51F Caterpillar](https://www.luogu.com.cn/problem/CF51F)
>
> [初级图论](https://www.cnblogs.com/alex-wei/p/basic_graph_theory.html)。

题目要求不能存在环，我们自然地想到将所有 E-BCC 缩成一个点。缩点后整张图会变成一棵森林，先处理每一棵树，再用连通块数量 $-1$ 次操作将它们连起来。

考虑确定主链后如何用最少的操作使得一棵树变成毛毛虫。

对于除了主链以外的节点，考虑它是否作为最终挂在主链旁边的叶子。将主链看成根，具有祖先后代关系的点对不能同时被选中作为叶子，因为此时后代和主链之间隔了一个祖先，说明它到主链的距离 $\geq 2$，与题意不符。

因此相当于选择最多的节点使得这些节点之间没有祖先后代关系。我们的决策是选择所有叶子，因为若一个非叶子被选，我们一定可以取消选择它，并选择它的所有儿子，这样一定更优。不断调整即可得到该结论。

因此，最终保留的节点为所有主链上的节点和我们选中作为叶子的节点。这意味着对于某条路径 $P$ 而言，它作为主链时对应的最少操作次数为 $n - |P| - L$，其中 $n$ 是树的大小，$L$ 是主链外叶子节点的数量。

容易发现，当 $P$ 的两端不是叶子时，我们总可以调整使得 $P$ 的两端是叶子且 $n - |P| - L$ 不变或变小：向任意一个可以延伸的方向延伸，每次 $|P|$ 增加 $1$，但 $L$ 要么不变（当延伸的点是非叶子），要么只减少 $1$（当延伸的点是叶子）。

因此，设原图的叶子数量为 $K$，则操作次数为 $n - K + 2 - |P|$。$n - K + 2$ 是定值，我们希望 $|P|$ 最大，自然是选取树的直径，同时恰好满足了 $P$ 的两端是叶子的要求。

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5;
int n, m;
vector<pair<int, int>> e[N];
vector<int> g[N];
int dn, dfn[N], low[N], top, stc[N], cn, col[N];
void form(int id) {cn++; for(int x = 0; x != id; ) col[x = stc[top--]] = cn;}
void tarjan(int id, int eid) {
  stc[++top] = id, dfn[id] = low[id] = ++dn;
  for(auto _ : e[id]) {
    if(_.second == eid) continue;
    int it = _.first;
    if(!dfn[it]) {
      tarjan(it, _.second), low[id] = min(low[id], low[it]);
      if(low[it] > dfn[id]) form(it);
    }
    else low[id] = min(low[id], dfn[it]);
  }
  if(!eid) form(id);
}
int ans, comp, vis[N], dis[N];
vector<int> cur;
void find(int id) {
  cur.push_back(id), vis[id] = 1;
  for(int it : g[id]) if(!vis[it]) find(it);
}
void dfs(int id, int ff) {
  dis[id] = dis[ff] + 1;
  for(int it : g[id]) if(it != ff) dfs(it, id);
}
void deal(int id) {
  if(g[id].empty()) return ans++, void();
  cur.clear(), find(id);
  dfs(id, 0);
  int u = id, leaf = 0;
  for(int it : cur) if(dis[it] > dis[u]) u = it;
  dfs(u, 0);
  for(int it : cur) if(dis[it] > dis[u]) u = it;
  for(int it : cur) leaf += g[it].size() == 1;
  ans += dis[u] + leaf - 2;
}
int main() {
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back({v, i});
    e[v].push_back({u, i});
  }
  for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, 0);
  for(int i = 1; i <= n; i++)
    for(auto _ : e[i])
      if(col[i] != col[_.first])
        g[col[i]].push_back(col[_.first]);
  for(int i = 1; i <= n; i++) if(!vis[i]) deal(i), comp++;
  cout << n - ans + comp - 1 << endl;
  return cerr << "Time: " << clock() << endl, 0;
}
/*
2022/5/26
start coding at 6:41
finish debugging at 7:00
*/
```

---

## 作者：chenxia25 (赞：1)

不能有重边这个条件很有趣啊。就是认为重边也算环，而且把重边定义成环确实是最合理的。那么对于每个环，你只要不把这个环上所有点并成一个点，这个环就永远存在。所以需要先 eDCC 缩点（把每个 DCC 合并成一个点），得到一个森林。

下面考虑对任意一棵树，怎么用最少的合并次数合并出一个毛毛虫。考虑最终毛毛虫的一个主干路径，那么将这个路径还原之后长度一定是不变的，也就是说不会通过合并路径上的点来造主干路径，因为这不起丝毫作用。

那现在钦定一条路径，看怎么能把所有点都压到离路径只有 $1$ 距离。手玩一波知道最优方案是把所有不在路径上的叶子保留下来，其它点全部坍塌到路径上。这样操作次数是 $n-(len+leaf-2)$，其中 $len$ 是钦定路径长度，$leaf$ 是叶子个数。只有 $len$ 是变量，找直径就好了（bzd 为啥这题 $n$ 只有 $2000$？正好我可以抄之前写过的 eDCC 缩点 + LCA 的板子暴力枚举路径，平方对数（））。

对多个连通分量（森林里的多个树），只需要两两合并即可，操作次数 $c-1$，其中 $c$ 是树的棵树。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=200010,LOG_N=20;
int n,m,qu;
vector<int> nei[N],rv[N];
vector<bool> brg[N];
int dfn[N],low[N],nowdfn;
void tar(int x=1,int fa=0){//to modify
	dfn[x]=low[x]=++nowdfn;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa){fa=-1;continue;}
		if(!dfn[y]){
			tar(y,x),low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y])brg[x][i]=brg[y][rv[x][i]]=true;
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
int cnt;
int cid[N];
void dfs(int x=1){
	cid[x]=cnt;
	for(int i=0;i<nei[x].size();i++)if(!brg[x][i]){
		int y=nei[x][i];
		if(!cid[y])dfs(y);
	}
}
vector<int> cnei[N];
int fa[N][LOG_N],dep[N];
vector<int> cc;
void dfs0(int x){
	cc.pb(x);
	for(int i=1;i<LOG_N;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=0;i<cnei[x].size();i++){
		int y=cnei[x][i];
		if(y==fa[x][0])continue;
		fa[y][0]=x;
		dep[y]=dep[x]+1;
		dfs0(y);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=LOG_N-1;~i;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=LOG_N-1;~i;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main(){
	cin>>n>>m;
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		nei[x].pb(y),nei[y].pb(x);
		rv[x].pb(nei[y].size()-1),rv[y].pb(nei[x].size()-1);
		brg[x].pb(false),brg[y].pb(false);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int i=1;i<=n;i++)if(!cid[i])cnt++,dfs(i);
	for(int i=1;i<=n;i++)for(int j=0;j<nei[i].size();j++){
		int x=nei[i][j];
		if(cid[i]!=cid[x])cnei[cid[i]].pb(cid[x]);
	}
	for(int i=1;i<=cnt;i++){
		vector<int> &v=cnei[i];
		sort(v.begin(),v.end());
		v.resize(unique(v.begin(),v.end())-v.begin());
	}
	int final=-1;
	for(int i=1;i<=n;i++)if(!dep[i]){
		dep[i]=1;
		cc.clear();
		dfs0(i);
		if(cc.size()==1)continue;
		int ans=0,leaf=0;
		for(int j=0;j<cc.size();j++)leaf+=cnei[cc[j]].size()==1;
		for(int ii=0;ii<cc.size();ii++)for(int jj=0;jj<cc.size();jj++){
			int i=cc[ii],j=cc[jj],k=lca(i,j);
			if(cnei[i].size()==1&cnei[j].size()==1&&i!=j)ans=max(ans,dep[i]+dep[j]-dep[k]-dep[fa[k][0]]+(leaf-2));
		}
		final+=-ans+1;
	}
	cout<<n+final;
	return 0;
}
```

---

## 作者：lhm_ (赞：1)

根据毛毛虫的定义，我们不难发现在双连通分量中的点我们都需要进行合并操作，所以我们先进行$tarjan$缩边双连通分量，使原图变成一棵树，缩点对答案产生的贡献为每个双连通分量的$size-1$

然后我们继续考虑树的情况，发现，若要将树变成毛毛虫，最优的操作是保留叶子节点和除去叶子后的直径，于是我们记录叶子节点个数$le$，除去叶子后的直径长度$dist$

但可能不止不止一棵树，缩点后可能为森林，所以最后还需将森林合并，我们再记录树的个数$num$

则最终答案为$ans= \displaystyle\sum_{i=1}^{co\_cnt}(siz[i]-1)+co\_cnt-dist-le+num-1$

其他实现的细节就看代码吧

$code:$
```cpp
#include<bits/stdc++.h>
#define maxn 20010
#define maxm 200010
using namespace std;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,m,ans,num;
struct Edge
{
	int x,y;
}ed[maxm];
struct edge
{
	int to,nxt;
}e[maxm];
int head[maxn],edge_cnt=1;
void add(int from,int to)
{
	e[++edge_cnt]=(edge){to,head[from]};
	head[from]=edge_cnt;
}
int dfn[maxn],low[maxn],dfn_cnt;
bool bri[maxn];
void tarjan(int x,int ed)
{
	dfn[x]=low[x]=++dfn_cnt;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(!dfn[y])
		{
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]) bri[i]=bri[i^1]=true;
		}
		else if(i!=(ed^1)) low[x]=min(low[x],dfn[y]);
	}
}
int co_cnt;
int co[maxn],siz[maxn];
void dfs_co(int x)
{
	co[x]=co_cnt;
	siz[co_cnt]++;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(co[y]||bri[i]) continue;
		dfs_co(y);
	}
}
void clear()
{
	edge_cnt=1;
	memset(head,0,sizeof(head));
}
int le;
bool vis[maxn],leaf[maxn];
void dfs_le(int x)
{
	vis[x]=true;
	bool son=true;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(vis[y]) continue;
		son=false;
		dfs_le(y);
	}
	if(son)
	{
		leaf[x]=true;
		le++;
	}
}
int nd,maxd,dist;
int dis[maxn];
void dfs_find(int x,int fa,int de)
{ 
    vis[x]=true; 
    if(de>=maxd)
    {
        maxd=de;
        nd=x;
	}
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to,v=1;
        if(y==fa||leaf[y]) continue;
        dfs_find(y,x,de+v);
    }
}	
int main()
{
	read(n),read(m);
	for(int i=1;i<=m;++i)
	{
		int a,b;
		read(a),read(b);
		add(a,b),add(b,a);
		ed[i]=(Edge){a,b};
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i,0);
	for(int i=1;i<=n;++i)
	{
		if(!co[i])
		{
			co_cnt++;
			dfs_co(i);
		}
	}
	for(int i=1;i<=co_cnt;++i)
		ans+=siz[i]-1;
	clear();
	for(int i=1;i<=m;++i)
	{
		int x=ed[i].x,y=ed[i].y;
		if(co[x]==co[y]) continue;
		add(co[x],co[y]),add(co[y],co[x]);
	}
	for(int i=1;i<=co_cnt;++i)
	{
		if(!vis[i])
		{
			dfs_le(i);
			num++;
			int tot=0;
			for(int p=head[i];p;p=e[p].nxt) tot++;
			if(tot==1)
			{
				leaf[i]=true;
				le++;
			}
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=co_cnt;++i)
	{
		if(!vis[i]&&!leaf[i])
		{
			nd=maxd=0;
			dfs_find(i,0,1);
			dfs_find(nd,0,1);
			dist+=maxd;
		}
	}
	printf("%d",ans+co_cnt-dist-le+num-1);
	return 0;
}
```


---

