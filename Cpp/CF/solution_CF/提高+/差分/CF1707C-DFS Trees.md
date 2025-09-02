# DFS Trees

## 题目描述

You are given a connected undirected graph consisting of $ n $ vertices and $ m $ edges. The weight of the $ i $ -th edge is $ i $ .

Here is a wrong algorithm of finding a [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) (MST) of a graph:

```
<pre class="verbatim"><br></br>vis := an array of length n<br></br>s := a set of edges<br></br><br></br>function dfs(u):<br></br>    vis[u] := true<br></br>    iterate through each edge (u, v) in the order from smallest to largest edge weight<br></br>        if vis[v] = false<br></br>            add edge (u, v) into the set (s)<br></br>            dfs(v)<br></br><br></br>function findMST(u):<br></br>    reset all elements of (vis) to false<br></br>    reset the edge set (s) to empty<br></br>    dfs(u)<br></br>    return the edge set (s)<br></br>
```

Each of the calls findMST(1), findMST(2), ..., findMST(n) gives you a spanning tree of the graph. Determine which of these trees are minimum spanning trees.

## 说明/提示

Here is the graph given in the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1707C/6866eea697370f9ef4baf895c7023c2ffb357c36.png)There is only one minimum spanning tree in this graph. A minimum spanning tree is $ (1,2),(3,5),(1,3),(2,4) $ which has weight $ 1+2+3+5=11 $ .

Here is a part of the process of calling findMST(1):

- reset the array vis and the edge set s;
- calling dfs(1);
- vis\[1\] := true;
- iterate through each edge $ (1,2),(1,3) $ ;
- add edge $ (1,2) $ into the edge set s, calling dfs(2): 
  - vis\[2\] := true
  - iterate through each edge $ (2,1),(2,3),(2,4) $ ;
  - because vis\[1\] = true, ignore the edge $ (2,1) $ ;
  - add edge $ (2,3) $ into the edge set s, calling dfs(3): 
      - ...

In the end, it will select edges $ (1,2),(2,3),(3,5),(2,4) $ with total weight $ 1+4+2+5=12>11 $ , so findMST(1) does not find a minimum spanning tree.

It can be shown that the other trees are all MSTs, so the answer is 01111.

## 样例 #1

### 输入

```
5 5
1 2
3 5
1 3
3 2
4 2```

### 输出

```
01111```

## 样例 #2

### 输入

```
10 11
1 2
2 5
3 4
4 2
8 1
4 5
10 5
9 5
8 2
5 7
4 6```

### 输出

```
0011111011```

# 题解

## 作者：rui_er (赞：13)

因为所有边权两两不同，所以 MST 是唯一的，我们把 MST 上的边标记出来。

我们知道对图进行 DFS 后，只有树边和返祖边两类边。要使得 MST 上的边均为树边，则不在 MST 上的边只能为返祖边。也就是说，不在 MST 上的边在当前根下必须是祖先后代关系。

至此，原问题转化为：判断每个节点作为根时，所有非 MST 边的两个点是否都是祖先后代关系。

我们可以随便找一个点当根，把每条非 MST 边两侧子树每个点的值加一（只有在这些点当根时才是祖先后代关系），然后判断每个点的值是否等于 $m-n+1$ 即可。具体实现方法可以使用树上差分。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
// Problem: C. DFS Trees
// Contest: Codeforces - Codeforces Round #808 (Div. 1)
// URL: https://codeforces.com/contest/1707/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, m, vis[N], fa[N][20], dis[N], s[N];
vector<tuple<int, int> > e;
vector<int> t[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Dsu {
	int fa[N];
	void init(int x) {rep(i, 1, x) fa[i] = i;}
	int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
	bool merge(int x, int y) {
		int u = find(x), v = find(y);
		if(u == v) return 0;
		fa[u] = v;
		return 1;
	}
}dsu;
void kruskal() {
	dsu.init(n);
	rep(i, 0, m-1) {
		int u = get<0>(e[i]), v = get<1>(e[i]);
		if(dsu.merge(u, v)) {
			vis[i] = 1;
			t[u].push_back(v);
			t[v].push_back(u);
		}
	}
}
void dfs1(int u, int f) {
	fa[u][0] = f;
	dis[u] = dis[f] + 1;
	rep(i, 1, 19) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int v : t[u]) if(v != f) dfs1(v, u);
}
int LCA(int u, int v) {
	if(dis[u] < dis[v]) swap(u, v);
	per(i, 19, 0) if(dis[fa[u][i]] >= dis[v]) u = fa[u][i];
	if(u == v) return u;
	per(i, 19, 0) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
void dfs2(int u, int f) {
	s[u] += s[f];
	for(int v : t[u]) if(v != f) dfs2(v, u);
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 0, m-1) {
		int u, v;
		scanf("%d%d", &u, &v);
		e.emplace_back(u, v);
	}
	kruskal();
	dfs1(1, 0);
	rep(i, 0, m-1) {
		if(!vis[i]) {
			int u = get<0>(e[i]), v = get<1>(e[i]);
			int lca = LCA(u, v);
			if(dis[u] > dis[v]) swap(u, v);
			if(lca == u) {
				++s[1], ++s[v];
				int p = v;
				per(j, 19, 0) if(dis[fa[p][j]] > dis[u]) p = fa[p][j];
				--s[p];
			}
			else ++s[u], ++s[v];
		}
	}
	dfs2(1, 0);
	rep(i, 1, n) putchar(s[i]==m-n+1?'1':'0');
	puts("");
	return 0;
}
```

---

## 作者：出言不逊王子 (赞：8)

纪念自己把一个逗号打成分号然后调了一个小时。

不难发现最小生成树唯一，先把最小生成树标记出来。

对于一个根，如果它是合法的，那么在遍历的过程中，不会走过非树边。

也就是说，它可以绕过非树边。

要想绕过非树边，我们肯定得有一个环，然后通过这个环绕过非树边。

很显然遍历到当前子树时你**必须无法走**这条非树边，否则根据规则，你就必须走这条边，无论它花费多大。

我们怎样才能保证自己无法走这条边呢？这条边对应的节点已经被走过了。

也就是说，这条边对应的点是我的祖先，非树边都是**返祖边**。

因此我们得保证一个点作为根时所有的非树边都是返祖边。

因为非树边共 $m-n+1$ 条，所以我们考虑统计每个点作为根时返祖边的数量，再比较二者的数量是否相等。

先假设根是 $1$，遍历最小生成树，枚举非树边 $(u,v)$，我们假设 $\text{LCA}(u,v)=p$。

若 $p\not \in \{u,v\}$，则只有从 $u$ 或 $v$ 的子树开始遍历时这条边才是返祖边，所以给 $u$ 和 $v$ 的子树增加一条返祖边数量。

因为出现了“子树加一”这个需要，所以我们考虑树上差分，用树状数组统计每个点的返祖边数量。

若 $p\in  \{u,v\}$，则只有根是 $u$ 的子树但不是 $v$ 的子树时，这条边才不是返祖边。

所以我们全局加一，再对 $u$ 儿子的子树减一，最后对 $v$ 的子树加一即可。

特别地，$u$ 本身符合条件，所以我们还要倍增找到 $u$ 的儿子。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid (l+r>>1)
#define pii pair<int,int>
#define lb(x) (x&(-x)) 
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=200001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
struct bian{int u,v,w,tag;}g[N];bool cmp(bian x,bian y){return x.w<y.w;}
vector<bian> e[N];
int n,m,f[N],dfn[N],idx,sz[N],fa[N][20],lga[N],dep[N];
struct bit{
	int tr[N];
	void add(int p,int v){while(p<=n)tr[p]+=v,p+=lb(p);}
	int qry(int p,int v=0){while(p)v+=tr[p],p-=lb(p);return v;}
	void reset(int n){fs(i,1,n,1)tr[i]=0;}
}t;
void upd(int p,int v){t.add(dfn[p],v);t.add(dfn[p]+sz[p],-v);}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void kruskal(){
	int res=0;
	fs(i,1,m,1){
		int u=g[i].u,v=g[i].v;
		if(find(u)==find(v))continue;
		f[find(u)]=find(v);g[i].tag=1,res++;
		if(res==n-1) break;
	}
}
void dfs(int now,int dad){
	dfn[now]=++idx,sz[now]=1;fa[now][0]=dad,dep[now]=dep[dad]+1;
	fs(i,1,19,1) fa[now][i]=fa[fa[now][i-1]][i-1];
	for(auto i:e[now]){
		int v=i.v;if(v==dad) continue;
		dfs(v,now);sz[now]+=sz[v];
	}
}
int lca(int x,int y){//计算xy跳到一起的最大开销（x-lca-y），这样可以同时记录x-y路径上的所有边 
//	int pay=0;//最大话费 
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]) x=fa[x][lga[dep[x]-dep[y]]-1];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
signed main(){
	n=read(),m=read();fs(i,1,n,1) f[i]=i;fs(i,1,m,1) g[i].u=read(),g[i].v=read(),g[i].w=i;
	fs(i,1,n,1){lga[i]=lga[i-1];if(i==1<<lga[i-1]) lga[i]++;}
	kruskal();
	fs(i,1,m,1){
		if(!g[i].tag) continue;
		e[g[i].u].push_back(g[i]);swap(g[i].u,g[i].v);
		e[g[i].u].push_back(g[i]);swap(g[i].u,g[i].v);
	}
	dfs(1,0);//fs(i,1,n,1) cout<<dfn[i];puts("");
	fs(i,1,m,1){
		if(g[i].tag) continue;
		if(dep[g[i].u]>dep[g[i].v]) swap(g[i].u,g[i].v);
//		cout<<g[i].u<<','<<g[i].v<<"?\n";
		if(lca(g[i].u,g[i].v)==g[i].u){
			t.add(dfn[1],1);upd(g[i].v,1);int x=g[i].v;
			for(int j=19;j>=0;j--) if(dep[fa[x][j]]>dep[g[i].u]) x=fa[x][j];
			upd(x,-1);
		//	cout<<t.qry(dfn[5])<<"!";
		}else upd(g[i].u,1),upd(g[i].v,1);//他们肯定不是父子关系吧 
	}
	fs(i,1,n,1) cout<<(t.qry(dfn[i])==(m-n+1));
	return 0;
}
//怎么样的根合法？以我为根开始跑，我们要求返祖边刚好是m-n+1条 
/*
6 6
2 3
3 5
2 5
2 6
3 4
1 2
*/ 
```

---

## 作者：I_am_Accepted (赞：8)

**用并查集求出 MST。**

由于题目给的边权两两不同，所以：

**MST 唯一。**

然后观察函数的遍历顺序，发现：

**题目给的函数生成的是从每个点出发的 DFS 搜索树。**

然后就是关键的想法：

**DFS 搜索树没有横向边。**

然而除了横向边就是返祖边，有：

**所有返祖边均可行。**

设 $v$ 向 $u$ 返祖，$u$ 向 $v$ 的第一条边连向 $w$，由于 MST 的性质，得到边权的不等式 $(u,v)>(u,w)$，所以在 $u$ 点要遍历 $v$ 的时候 $v$ 点必然已经被访问过了，所以返祖边可行。

由于横向边不可行，得到本题的充要条件：

**对于每一条非树边 $(u,v)$，树上一个点 $x$ 能作为起始点当且仅当 $x$ 第一次走到 $\text{path}(u,v)$ 时是在 $u$ 或 $v$。**

由于和子树有关，我们想到统计方式：

**树上差分。**

然后就做完了，实现可做到：

**时间复杂度线性。**

[代码](https://codeforces.com/contest/1707/submission/164574252)



---

## 作者：hgzxwzf (赞：6)

## 解题思路：
首先我们可以把最小生成树上的边找出来，因为题目中的边权都不想相同，所以最小生成树是唯一的。

然后我们观察其他边。

如样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/7r1thr86.png)

边权为 $4$ 的那条边不是最小生成树上的边。

如果从 $1$ 号点开始，他会先到 $2$ 号点，然后因为 $3$ 号点没有被访问过，所以他会边权为 $4$ 的那条边走到 $3$，因为这条不是最小生成树上的边，所以最后找出来的就不是最小生成树了。

分别从其他点出发，发现都不会经过边权为 $4$ 的那条边。

所以要想找出最小生成树，就不能经过非树边。

不妨以1为根，那么 $lca(2,3)=1$，我们忽略边权，从 $1$ 出发肯定会先到 $2$ 和 $3$ 其中一个点，再通过这条非树边到另一个点。

如果还有其他子树和 $1$ 号连接，那么为了保证最小生成树，那些点肯定通过树边到 $1$ 好点，之后就和从 $1$ 号点出发的情况一样了。

我们考虑普遍情况，对于一条非树边连接的两个点 $u,v(dep_u>dep_v)$，如果 $lca(u,v)\not=v$，除了 $u,v$ 子树以外的的点全部都不合法（从那个点出发不能找到最小生成树）。

可以用树上差分解决，即 $p_i$ 为 $p=i$ 子树内的点都不合法，每次我们都执行 $p_{root}+1,p_u-1,p_v-1$ 的操作。

注意到我们上面有 $lca(u,v)\not=v$ 的条件限制，如果 $lca(u,v)=v$,以从 $u$ 到 $v$ 链上的点为根的子树上的所有点都不合法，因为从这些点要先走到链上，然后就会出现先走到 $u,v$ 两个点其中一个，再通过非树边走到另一个点的情况了。注意 $u,v$ 两点是合法的，因为从他们出发，一开始访问了他们自己。

对于 $lca(u,v)=v$ 的情况，先将 $p_u-1$，将 $u$ 跳到 $v$ 下面，再将 $p_u-1$。

最后 $dfs$ 下传 $p$ 即可，$p=0$ 的点就是合法点。

## 代码：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<stack>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)

using namespace std;

const int N=2e5+10;

struct UNMST
{
	int u,v;
}un[N];

vector<int>e[N];
int fa[N],pa[N][25],dep[N],p[N];
bool ans[N];

int find(int x)
{
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}

void dfs(int cur)
{
	for(int i=0;i<e[cur].size();i++)
	{
		int nt=e[cur][i];
		if(nt==pa[cur][0]) continue;
		pa[nt][0]=cur;
		dep[nt]=dep[cur]+1;
		dfs(nt);
	}
}

int LCA(int x,int y)
{
	for(int i=20;i>=0;i--) if(dep[pa[x][i]]>=dep[y]) x=pa[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
	if(pa[x][i]!=pa[y][i])
	{
		x=pa[x][i];
		y=pa[y][i];
	}
	return pa[x][0];
}

void dfs2(int cur)
{
	for(int i=0;i<e[cur].size();i++)
	{
		int nt=e[cur][i];
		if(nt==pa[cur][0]) continue;
		p[nt]+=p[cur];
		dfs2(nt);
	}
	if(p[cur]==0) ans[cur]=1;
}

int x[N],y[N];

int main()
{
	int n,m,num=0;
	scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d",&x[i],&y[i]);
	rep(i,1,n) fa[i]=i;
	rep(i,1,m)
	{
		int fx=find(x[i]),fy=find(y[i]);
		if(fx==fy) un[++num]=(UNMST) {x[i],y[i]};
		else
		{
			fa[fx]=fy;
			e[x[i]].push_back(y[i]);
			e[y[i]].push_back(x[i]);
		}
	}
	dep[1]=1;
	dfs(1);
	rep(j,1,20)
		rep(i,1,n)
			pa[i][j]=pa[pa[i][j-1]][j-1];
	rep(i,1,num)
	{
		int u=un[i].u,v=un[i].v;
		if(dep[u]<dep[v]) swap(u,v);
		int lca=LCA(u,v);
		if(lca==v)
		{
			p[u]--;
			per(j,0,20) if(dep[pa[u][j]]>dep[v]) u=pa[u][j];
			p[u]++;
			continue;
		}
		p[1]++;
		p[u]--;
		p[v]--;
	}
	dfs2(1);
	rep(i,1,n)
		printf("%d",ans[i]);
	return 0;
}
```


---

## 作者：Halberd_Cease (赞：3)

题解全部都是树上差分，我来表演一下小丑的树剖 + 线段树。

首先，因为边权互不相同，所以最小生成树唯一，题目转化为判断以 $i$ 为起点的图的 dfs 树会不会走到其它边。

建出原图 MST 后分类讨论，以任意一点为根，对于不在 MST 中的一条边，如果两点没有祖先关系，那么以不在两点子树中（包括两点）的点为起点一定生成错误的 MST。

感性理解：如图

![](https://cdn.luogu.com.cn/upload/image_hosting/n9rzdvfc.png)

不在两点子树内的点，在进入先一点子树的时候，另一点一定未被访问，所以在先访问一个点的时候，一定会通过红色边。

反之，如果是两点子树内的点做起点，在遍历到一个红色点的时候，一定会先通过不是红色边的 MST 树边访问到另一个红色点，所以生成树是正确的。

如果两点有祖先关系，先手动模拟，钦定两点路径上的一个点为根，两点就没有祖先关系了，发现和上面的情况是一样的，和原图对比考虑，令靠近根的点为 $X$，另一点为 $Y$。不合法的点应该是 $X$ 在 $X$ 到 $Y$ 路径上的儿子的子树中，除 $Y$ 子树中的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/3zi8lq5z.png)

考虑多条红色边，只要走到一条红色边就是错误的生成树，于是我们考虑标记合法点。总共有 $m-n+1$ 条红色边，对于每一条，都是合法点的点才是真正的合法点。所以枚举每一条边，合法点加上 $1$，最后值为 $m-n+1$ 的点就是真正的合法点。

直接大力树剖 + 线段树，其实这题不写树剖也可以，我是为了方便求 $X$ 路径上子节点不想写倍增于是写了树剖，如果你写倍增，直接一个 dfs 序就可以。

对于第一种情况，直接标记两个点的子树。第二种稍微复杂，LCA 求出 $X$ 到 $Y$ 路径上 $X$ 的儿子，先标记整棵树，然后给求出的儿子的子树取消标记（即整棵子树 $-1$），然后再给 $Y$ 的子树打上标记。

最后每个点查询即可。

时间复杂度 $O(n\log n)$ 瓶颈在求 LCA（线段树可以优化成差分）。

[submission](https://codeforces.com/contest/1707/submission/256227379)

---

## 作者：pldzy (赞：2)

差分。

不知道为什么题解区都要人云亦云地写树上差分。

## Solution

题面很小清新。

- 很显然的一个突破口是第 $i$ 条边的权值为 $i$，根据非严格次小生成树的求法，即添加一条边成环再删去环上另外一条边，可知，由于边权互不相同，所以 MST 的形态是唯一确定的。

- 故考虑一边输入一边得到 MST。思考一条非树边 $(u,v)$，不妨假设 $u$ 为 $v$ 父亲，通过手动模拟加点过程可以发现，在错误做法中，这条边被添加，当且仅当在 $u$ 的子树中，已经被添加的节点中不包含 $v$。

- 所以如果非树边 $(u,v)$ 不被添加，当且仅当在 $findMST(i)$ 中，$(u,v)$ 是祖先-后代关系。也即是说，若 $findMST(i)$ 合法，则它对于任意非树边 $(u,v)$，都满足二者间祖先后代关系。

- 分情况讨论。不妨假设 $u$ 的深度小于等于 $v$ 的深度。则：
	
    - 若 $u$ 与 $v$ 各自的子树相互独立，即无交，那么对于 $(u,v)$ 而言合法的根一定存在于二者子树的并集中。
    - 若 $v$ 包含在 $u$ 的子树中。记 $u$ 的一个直接儿子 $k$，满足 $v$ 在 $k$ 的子树内，$v$ 可能等于 $k$。通过画图可知，此时不合法的根，满足，在 $k$ 的子树内，并且不在 $v$ 的子树内。除了这些点以外，其他所有的点都可能成为合法根。
   
- 然后用 dfs 序套个差分数组就可以做了，每次 $O(1)$ 修改，最后 $O(n)$ 合并答案，过程中维护一个 vector，每次用来寻找 $v$ 在 $u$ 的哪个直接儿子中即可。若将反阿克曼函数复杂度视为常数，$m,n$ 视为同级，则最终的时间复杂度为 $O(n\log n)$。

## Code

不用多写个 dfs 求 LCA，码量也少挺多。

````cpp
#include<bits/stdc++.h>

#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)
#define pb push_back
const int maxn = 3e5 + 5;
int n, m, qu[maxn], qv[maxn], vis[maxn];
int fa[maxn], dep[maxn];
int dfn[maxn], tot, rev[maxn], sz[maxn];
int val[maxn];
std::vector<int> e[maxn], p[maxn];

inline int fnd(int x){ return fa[x] == x ? x : fa[x] = fnd(fa[x]);}
inline void dfs(int x, int fat){
	tot += 1; dfn[x] = tot, rev[tot] = x, sz[x] = 1;
	dep[x] = dep[fat] + 1;
	for(int v : e[x]) if(v != fat)
		p[dfn[x]].pb(tot + 1), dfs(v, x), sz[x] += sz[v];
	p[dfn[x]].pb(tot + 1);
}

int main(){
	scanf("%d%d", &n, &m);
	rep(i, 1, n) fa[i] = i;
	rep(i, 1, m){ vis[i] = 0;
		scanf("%d%d", &qu[i], &qv[i]);
		int u = fnd(qu[i]), v = fnd(qv[i]);
		if(u == v) continue;
		fa[u] = v;
		e[qu[i]].pb(qv[i]), e[qv[i]].pb(qu[i]);
		vis[i] = 1;
	}
	dfs(1, 0);
	rep(i, 1, m) if(!vis[i]){
		int u = dfn[qu[i]], v = dfn[qv[i]];
		if(dep[qu[i]] > dep[qv[i]]) std::swap(u, v), std::swap(qu[i], qv[i]);
		if(!(v >= u and v < u + sz[rev[u]])){
			val[u] += 1, val[u + sz[rev[u]]] -= 1;
			val[v] += 1, val[v + sz[rev[v]]] -= 1;
		} else{
			val[v] += 1, val[v + sz[rev[v]]] -= 1;
			int pos = std::upper_bound(p[u].begin(), p[u].end(), v) - p[u].begin(); pos -= 1;
			int l = p[u][pos], r = p[u][pos + 1] - 1;
			val[l] -= 1, val[r + 1] += 1;
			val[1] += 1;
		}
	}
	rep(i, 2, tot) val[i] += val[i - 1];
	rep(i, 1, n) if(val[dfn[i]] == m - n + 1) printf("1"); else printf("0"); printf("\n");
	return 0;
}
````
---
Thanks for reading.

---

## 作者：_lyx111 (赞：2)

# CF1707C DFS Trees

[link](https://codeforces.com/problemset/problem/1707/C)

## 题意

给定一个 $n$ 个点，$m$ 条边的无向连通图，第 $i$ 条边的权值为 $i$。

题目中给了一个求最小生成树的错误算法，要求判断 `findMST(i)` 是否是最小生成树 $(1\le i\le n)$。

$2\le n\le 10^5,n-1\le m\le 2\times 10^5$。

## 分析

首先由于图中的边权两两不同，所以 MST（ 最小生成树 ）唯一，使用 Kruskal 算法求出原图的 MST。

现在观察一下题目中给定的函数是在做什么：`findMST(i)` 生成的是从点 $i$ 出发的 DFS 搜索树。那么原问题转化为：判断每个节点作为根时，所有在 MST 中的边的两个点是否都不是祖先后代关系。

定义一个数组 $t_i(1\le i\le n)$ 表示所有满足在以点 $i$ 为根的 DFS 搜索树中边的两个点不是祖先后代关系的边的个数，初始时 $t_1=t_2=\dots=t_n=0$。

钦定点 $1$ 为根，对于每条不在 MST 中的边 $(u,v)$，将 $u$ 的子树和 $v$ 的子树中每个点的 $t_i$ 加 $1$（ 只有在这些点当根时 $(u,v)$ 这条边才是祖先后代关系 ）。最后 `findMST(i)` 是否是最小生成树就等价于 $t_i$ 是否等于 $m-(n-1)$。

时间复杂度：$O(n\log n)$。Kruskal 时间复杂度 $O(m)$（ 因为第 $i$ 条边的权值为 $i$，所以不需要排序 ），使用树上差分完成 " 对于每条不在 MST 中的边 $(u,v)$，将 $u$ 的子树和 $v$ 的子树中每个点的 $t_i$ 加 $1$ " 这步，单次时间复杂度为 $O(\log n)$，共 $(m-n+1)$ 条边需要完成此操作，时间复杂度为 $O((m-n+1)\log n)$。那么总时间复杂度为 $O(m+n+(m-n+1)\log n)=O(n\log n)$。

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10,MAXM=2e5+10;
int n,m; //点数 n，边数 m 
int U[MAXM],V[MAXM]; //原图中的边 
int f[MAXN]; //并查集 
int getfa(int x) //向上找祖先 
{
	if(x==f[x]) return x;
	else return f[x]=getfa(f[x]); //路径压缩 
}
bool merge(int x,int y) //合并 x,y 
{
	int fx=getfa(x),fy=getfa(y);
	if(fx!=fy) { f[fx]=fy; return 1;}
	else return 0; //已在同一个连通块内 
}
struct node
{
	int to,nxt;
} edg[MAXN<<1];
int cnt,hea[MAXN];
void add(int u,int v)
{
	cnt++;
	edg[cnt].to=v;
	edg[cnt].nxt=hea[u];
	hea[u]=cnt;
} //链式前向星存最小生成树 
int vis[MAXM]; //第 i 条边是否在最小生成树内 
void Kruskal() //Kruskal 求最小生成树 
{
	for(int i=1;i<=n;i++) f[i]=i; //初始化并查集 
	for(int i=1;i<=m;i++)
		if(merge(U[i],V[i])) //加入最小生成树 
		{
			vis[i]=1;
			add(U[i],V[i]);
			add(V[i],U[i]);
		}
}
int fa[MAXN][30],dep[MAXN]; //祖先 fa，深度 dep 
void dfs1(int u,int fat) //遍历最小生成树，求出祖先 fa，深度 dep 
{
	fa[u][0]=fat;
	for(int i=1;i<=19;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1]; //倍增 
	dep[u]=dep[fat]+1;
	for(int i=hea[u];i;i=edg[i].nxt)
		if(edg[i].to!=fat) dfs1(edg[i].to,u);
}
int lca(int x,int y) //倍增 lca 
{
	for(int i=19;i>=0;i--)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			{ x=fa[x][i]; y=fa[y][i];}
	return fa[x][0];
}
int t[MAXN];
void dfs2(int u,int fat)
{
	t[u]+=t[fat]; //树上差分之后要前缀和 
	for(int i=hea[u];i;i=edg[i].nxt)
		if(edg[i].to!=fat) dfs2(edg[i].to,u);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&U[i],&V[i]);
	Kruskal();
	dfs1(1,0);
	for(int i=1;i<=m;i++)
		if(!vis[i]) //树上差分计算 
		{
			if(dep[U[i]]>dep[V[i]]) swap(U[i],V[i]);
			int lc=lca(U[i],V[i]);
			if(U[i]==lc)
			{
				t[1]++; t[V[i]]++;
				int x=V[i];
				for(int j=19;j>=0;j--)
					if(dep[fa[x][j]]>dep[U[i]])
						x=fa[x][j];
				t[x]--;
			}
			else { t[U[i]]++; t[V[i]]++;}
		}
	dfs2(1,0);
	for(int i=1;i<=n;i++)
		if(t[i]==m-(n-1)) printf("1");
		else printf("0");
	return 0;
}
~~~

[AC记录](https://codeforces.com/problemset/submission/1707/175522294)

## 写在最后

笔者水平有限，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正

---

## 作者：Fzrcy (赞：2)

观察伪代码，对于每个节点总是走未走过且边权最小的边 。 

首先我们要先求出求出最小生成树 $G$。

非最小生成树的边分为返祖边和横叉边。

![](https://cdn.luogu.com.cn/upload/image_hosting/0hin28by.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

接下来，分类讨论 :
	
设非树边的两个节点为 $x,y$，根据最小生成树的性质，可以得到非树边的权值 $edge(x,y)$ 大于 $x,y$ 在图 $G$ 的路径上所有边的权值。


1.返祖边 

以此图为例:

![](https://cdn.luogu.com.cn/upload/image_hosting/a40uv4wh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$4$ 到 $1$ 的返祖边的权值一定大于 $edge(2,4),edge(2,1)$ 。

从 $2$ 开始遍历，先走 $edge(1,2)$ 这条边，遍历完子树 $5$ 后回溯到节点 $1$，走 $edge(1,4)$，显然形成的兔变为最小生成树。

从 $4$ 开始遍历，先走 $edge(2,4),edge(2,1)$，遍历完子树 $5$ 后回溯到节点 $1$，不会走 $edge(1,4)$。

从 $4$ 的子树的任意一个节点开始遍历， 一定先到 $4$ 然后按上一种方式遍历，从 $1$ 的其他子树开始遍历同理。

所以在 $x,y$ 在图 $G$ 的路径上的所有节点（不含 $x,y$）不能容纳这条返祖边 $edge(x,y)$。 

2. 横叉边

以此图为例:

![](https://cdn.luogu.com.cn/upload/image_hosting/tzl7cpz4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

证明的方法与返祖边类似，所以直接说结论： 所有非 $x$ 或 $y$ 子树的所有节点都不能容纳这条横叉边 $edge(x,y)$。

## $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int n,m,tot,num;
int fa[N];
int dep[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
vector < int > to[N];//树边
vector < pair < int , int > > ex;//非树边对，分为返祖边与横叉边
vector < int > exto[N];
void find_dep(int x,int fa)
{
	dep[x]=dep[fa]+1;
	for(int i=0; i<to[x].size(); i++)
	{
		static int y;
		y=to[x][i];
		if(y==fa)continue;
		find_dep(y,x);
	}
	return;
}
int vis[N];
int now[N];
int could[N];
void find_exto(int x,int fa)
{
	now[dep[x]]=x;
	for(int i=0; i<exto[x].size(); i++)
	{
		static int y;
		y=exto[x][i];
		if(now[dep[y]]==y)
		{
			could[1]++;
			could[now[dep[y]+1]]--;
			could[x]++;
		}
		else
		{
			could[x]++;
			could[y]++;
		}
	}
	for(int i=0; i<to[x].size(); i++)
	{
		if(to[x][i]==fa)continue;
		find_exto(to[x][i],x);
	}
}
void find_add(int x,int fa)
{
	could[x]+=could[fa];
	for(int i=0; i<to[x].size(); i++)
	{
		static int y;
		y=to[x][i];
		if(y==fa)continue;
		find_add(y,x);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)fa[i]=i;
	for(int i=1; i<=m; i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);
		if(fx!=fy)
		{
			fa[fx]=fy;
			to[x].push_back(y);
			to[y].push_back(x); 
		}
		else
		{
			tot++;
			ex.push_back(make_pair(x,y));
		}
	}
	find_dep(1,0);
	for(int i=0; i<ex.size(); i++)
	{
		static int x,y;
		x=ex[i].first;
		y=ex[i].second;
		if(dep[x]<dep[y])swap( x,y );
		exto[x].push_back(y);
	}
	find_exto(1,0);
	find_add(1,0);
	for(int i=1; i<=n; i++)cout<<(could[i]==tot);
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

看懂题目给的伪代码还是容易的，`findMST(i)` 进行的是寻找以 $i$ 为根的 dfs 生成树。边权不相同所以 MST 唯一，我们先建出来。

```cpp
if vis[v] = false
	add edge (u, v) into the set (s)
	dfs(v)
```

这一句是最重要的。因为只要没访问过，这条边就必须走。如果 dfs 生成树刚好走成了 MST，则对于 MST 的非树边他都**走不了**，换句话说就是，这些非树边两点在这个点为根时，是祖先后代关系。

形式化一点的，钦定目前枚举到的作为根点是 $x$，则对于不在 MST 中的任意一边 $(x,y)$，$x,y$ 都满足祖先后代关系。

如何维护？我们随便挑一个点作为根，然后对于一条边 $(u,v)$，考虑什么样的点作为根时他们成为祖先后代？

![](https://cdn.luogu.com.cn/upload/image_hosting/mko6ja27.png)

在 $(u,v)$ 目前不是祖先后代关系时，在两者的子树内则可以满足（显然 $u,v$ 自己都可以，图中为了清楚没有图上阴影）。

如果两者目前已经是祖先后代关系了，如何维护呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/m89de4tw.png)

$1$ 的直接儿子 $4$ 是 $5$ 的祖先，而在 $4$ 子树而不在 $5$ 子树的点不加。

则先加 $u$ 子树，再减 $u$ 某个是 $v$ 的祖先的直接儿子的子树，再加 $v$ 子树。$u,v$ 反过来同理。

那么我们需要维护一个子树加的玩意，差分就好了。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
const int N=2e5+5;
int n, m, i;
bool mark[N];
int f[N][25], dep[N], d[N];
class echi
{
public:
	int u, v; inline void input(){ scanf("%d %d", &u, &v); }
};
vector<echi> e;
vector<int> tr[N];
int fa[N]; inline int find(int x) {while(x!=fa[x]) x=fa[x]=fa[fa[x]]; return x;}
inline void dfs(int id, int fa)
{
	f[id][0]=fa; dep[id]=dep[fa]+1;// printf("f[%d][0] into %d\n", id, fa);
	rep(i, 1, 20) f[id][i]=f[f[id][i-1]][i-1];
	for(auto nxt : tr[id]) if(nxt!=fa) dfs(nxt, id);
	return ;
}
inline int lca(int x, int y)
{
    if(dep[x]<dep[y]) swap(x, y);
//  printf("%d %d\n", x, y);
    int i; req(i, 20, 0) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
//  printf("%d %d\n", x, y);
    if(x==y) return x;
    req(i, 20, 0) if(f[x][i]!=f[y][i]) x=f[x][i], y=f[y][i];
//  printf("%d %d\n", x, y);
    return f[x][0];
}
inline void pre(int id, int fa)
{
	d[id]+=d[fa];
	for(auto nxt : tr[id]) if(nxt!=fa) pre(nxt, id);
}
int main()
{	int u, v, lc, j;
	scanf("%d %d", &n, &m); e.resize(m+5);
	rep(i, 1, m) e[i].input();
	rep(i, 1, n) fa[i]=i;
	rep(i, 1, m)
	{
		u=e[i].u; v=e[i].v;
//		rep(j, 1, n) printf("%d ",fa[j]); printf(": %d %d\n", u, v);
		if(find(u) !=find(v))
		{
			fa[find(u)]=find(v);
			tr[u].emplace_back(v);
			tr[v].emplace_back(u);
			mark[i]=true;
		}
	}
	dfs(1, 0);
//	rep(i, 1, n) printf("%d %d %d\n", dep[i], f[i][0], i);
	rep(i, 1, m)
	{
		if(!mark[i])
		{
			u=e[i].u; v=e[i].v;
			lc=lca(u, v);// printf("%d %d %d\n", u, v, lc);
			if(dep[u]>dep[v]) swap(u, v);
			if(lc==u)
			{
				++d[1]; ++d[v];
				req(j, 20, 0) if(dep[f[v][j]]>dep[u]) v=f[v][j];
				--d[v];
			}else {++d[u]; ++d[v];}
		}
	} pre(1, 0);// rep(i, 1, n) printf("%d ", d[i]); puts("");
	rep(i, 1, n) if(d[i]==m-(n-1)) putchar('1'); else putchar('0');
	return 0;
}
```

---

## 作者：云浅知处 (赞：1)

挺妙的题。独立做出来了一个 `*2400`，好耶

下面我试图说明一下思考的路线。

- 由于边权不同，最小生成树实际上是唯一的。
- 因此，考虑一条非树边 $(u,v)$，观察样例一，一开始我猜测这代表 $u\to v$ 路径上不包括端点的所有点都会走歪，得不到真正的 MST。
- 证明很简单：考虑路径上的一个点 $x$，不妨设 $x$ 第一步会朝 $u$ 的方向走（注意 MST 唯一，因此只要走错一步就意味着 $x$ 不符合要求，故可行的路径其实是唯一的），那么想要回到 $v$，必然要经过 $(u,v)$，选取这条不优的边。因为在 DFS 的过程中我们不会走回头路。
- 但样例二是一个反例。

![](https://cdn.luogu.com.cn/upload/image_hosting/2vtyaqa6.png)

> 图中的 $8$ 号点也会走歪，但它不满足上面的要求。

经过一些思考可以得到正确的结论：

- 对于一个点 $r$，若 MST 以 $r$ 为根时图中不存在横叉边，那么 $r$ 是合法的。也就是说，若以 $r$ 为根是，任意非树边 $(u,v)$ 总是满足 $u,v$ 中的一个是另一个的祖先，那么 $r$ 是符合要求的。
- 充分性显然。必要性也不难证明：如果 $u,v$ 是一条横叉边，设 $z=\text{LCA}(u,v)$，若 $r$ 在走向 $z$ 的过程中已经走歪了显然不行；否则 $r$ 在走到 $z$ 后就变成了上面讨论的情况，必然会走向一边然后歪掉 $(u,v)$ 这条边。

因此现在只需要算出来以每个点为根时是否存在横叉边。

我们先随便提一个根出来，设 $S_u$ 表示 $u$ 子树内所有节点的集合，对于一条路径 $(u,v)$：

- 若 $u,v$ 互不为对方的祖先，那么所有在 $S_{\text{root}}-S_u-S_v$ 中的节点均不符合要求。
- 否则，不妨设 $u$ 是 $v$ 的祖先，设 $x$ 是 $v$ 的 $\text{dep}_v-\text{dep}_u-1$ 级祖先（即 $u$ 的某个直接儿子，同时也是 $v$ 的祖先），那么所有在 $S_x-S_v$ 中的节点均不符合要求。

于是现在相当要给一个子树做一个覆盖之类的东西。可以直接拍平成 $\text{DFS}$ 序转成序列问题差分解决。

算上求 $k$ 级祖先/并查集之类的东西，时间复杂度不超过 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=2e5+5;
int fa[MN],dfn[MN],dep[MN],fp[MN],top[MN],hson[MN],sz[MN];
int n,m,fr[MN],to[MN];

int find(int x){return x==fp[x]?x:fp[x]=find(fp[x]);}

vector<int>G[MN];
void adde(int u,int v){
	G[u].push_back(v),G[v].push_back(u);
}

void dfs1(int u,int de){
	dep[u]=de,sz[u]=1;
	for(int v:G[u]){
		if(v==fa[u])continue;
		fa[v]=u,dfs1(v,de+1),sz[u]+=sz[v];
		if(sz[v]>sz[hson[u]])hson[u]=v;
	}
}

int tot=0,id[MN];
void dfs2(int u,int tp){
	top[u]=tp,dfn[u]=++tot,id[tot]=u;
	if(hson[u])dfs2(hson[u],tp);
	for(int v:G[u]){
		if(v==hson[u]||v==fa[u])continue;
		dfs2(v,v);
	}
}

int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	return u;
}

bool used[MN];
int d[MN];

void add(int l,int r,int k){
	d[l]+=k,d[r+1]-=k;
}

int get(int u,int v){
	assert(dfn[v]>=dfn[u]&&dfn[v]<=dfn[u]+sz[u]-1);
	int de=dep[u]+1;
	while(dep[top[v]]>de)v=fa[top[v]];
	int dis=dep[v]-de;
	return id[dfn[v]-dis];
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read(),m=read();
	for(int i=1;i<=m;i++)fr[i]=read(),to[i]=read();
	for(int i=1;i<=n;i++)fp[i]=i;
	for(int i=1;i<=m;i++){
		int u=find(fr[i]),v=find(to[i]);
		if(u==v)continue;
		adde(fr[i],to[i]),fp[u]=v,used[i]=1;
	}

	dfs1(1,1),dfs2(1,1);
	for(int i=1;i<=m;i++){
		if(used[i])continue;
		int u=fr[i],v=to[i],z=LCA(u,v);
		if(z!=u&&z!=v){
			add(1,n,1);
			add(dfn[u],dfn[u]+sz[u]-1,-1);
			add(dfn[v],dfn[v]+sz[v]-1,-1);
		}
		else{
			if(z==v)swap(u,v);assert(z==u);
			int x=get(u,v);if(x==v){continue;}
			add(dfn[x],dfn[x]+sz[x]-1,1);
			add(dfn[v],dfn[v]+sz[v]-1,-1);
		}
	}

	for(int i=1;i<=n;i++)d[i]+=d[i-1];
	for(int i=1;i<=n;i++)cout<<(!(d[dfn[i]]>0));puts("");

	return 0;
}
```

---

## 作者：SnowFlavour (赞：0)

## 题意

有一个有问题的最小生成树算法，问从哪些起点出发，可以得到正确的最小生成树。

## 我会模拟！

既然错解都有伪代码了，我们就直接把他翻译成 C++，然后对每一个根节点都跑一遍 DFS，检查是否符合条件，也就是暴力对拍，复杂度 $O(n^2)$。唯一的问题是本题没有部分分。

但是……等等，我们怎么判断这个答案是不是最小生成树？

有一个简单的办法，就是把所有的边权加起来，因为老师上课讲过，“最小生成树不唯一”。

不对！这里的最小生成树真的不唯一吗？

我们来考虑一下最小生成树的算法。以克鲁斯卡尔为例，这个算法从小到大枚举所有的边，然后将他们加入最小生成树。在这个过程中，如果最小生成树不唯一，那么就必然是有多个边权相同的边，加哪一条都行。

但是现在，整个图所有的边权都不一样。

所以，**最小生成树是唯一的！**

## 我会画图！

首先，我们要知道一个最小生成树中有多少种边。

1. 树边。最小生成树上的边。
2. 返祖边。回到祖先的边。
3. 横叉边。到达其他子树的边。

这个时候，考虑找一个样例进行研究。

这是样例二的图：

![](https://s21.ax1x.com/2024/10/07/pAGuUOA.png)

其中横向的两条边是横叉边。那么现在，我们就用题目中的逻辑，对这个树进行一遍 DFS。

首先，我们尝试从 $1$ 节点出发：

![](https://s21.ax1x.com/2024/10/07/pAGuwwt.png)

其中，绿色的边是正确的边，而红色的边是本来不应该走的横叉边。

这个时候，我们再看看如果以 $5$ 为起点会发生什么：

![](https://s21.ax1x.com/2024/10/07/pAGuclQ.png)

这个时候，我们会发现，刚才的两条横叉边（$2-8$，$4-5$）都变成了返祖边。

这就使我们意识到，这个问题可能与横叉边和返祖边的区别有关。

我们思考：这两种非树边都是不能经过的，否则将会导致答案错误。

当我们搜索到一条返祖边时，分两种情况考虑：

1. 这个节点在这条边靠上（深度较小）的边上。可以证明，这时这条返祖边肯定比树边的权值要大。为什么呢？以上图为例，如果 $4-5$ 这条边的边权小于 $5-2$，那么我们的最小生成树一定是将 $4-5$ 加入树，然后通过 $2-4$ 连接，这样 $4$ 就变成了 $5$ 的儿子，而 $2$ 变成了 $4$ 的儿子。因此，我们在搜索的时候一定会先搜索树边。
2. 这个节点在这条边靠下（深度较大）的边上。这个时候，由于这条边会回到祖先，而祖先显然已经被搜索过了，所以根本就不会搜索到这条边。

综上所述，我们会发现：如果一条最小生成树上的边是非树边，那么用搜索的方式也能得到正确答案。

那么横叉边呢？我们会发现：当我们访问到横叉边的某一个节点的时候，我们会遍历与他相邻的所有的边。这是深度优先搜索的特性，如果你不明白，我们来看看一个标准的代码是怎么写的：

```cpp
void dfs(int u,int fa){
    //这里可能会有别的东西
    for(int i=0;i<e[u].size();i++){
        int v=e[u][i];
        if(v==fa)continue;
        //这里也可能会有别的东西
        dfs(v,u);
    }
}
```

这就是说，他会遍历所有的子节点，直到遍历完成才会返回。

怎么才能阻止他访问这条横叉边呢？很简单，在遍历到这条边之前就**通过树边**遍历到横叉边的另一个节点。那么我们怎么才能过去呢？由于两个节点在不同的子树上，从这个节点如果不回到父亲，是永远无法通过树边到达另一端的。

因此，只要最小生成树含有横叉边，这个图用搜索的方式就会炸。

问题就转化为了：以哪些节点为根，可以让最小生成树上没有横叉边。

## 我会树上差分！

这个时候有同学可能就想到了换根 DP。别着急，先想想~~毕竟换根这么难推式子，能不用就不用~~。

怎么才能让一条边是返祖边？

答案就是让两个节点有祖孙关系。换句话说，就是其中一个节点要在另一个节点的子树内。

这个时候我们再考虑：

1. 其中本来就有一个是另一个的祖先。这个时候，只要我们不把这个树从这两个节点间的链上“拎”起来，这两个节点就依然会满足祖孙关系。
2. 其中本来没有祖孙关系。当我们换根的时候，就需要从这两个节点的子树上把他“拎”起来，这样这两条边就会形成祖孙关系。

看懵了？看看图就明白了。

![pAGKc4K.png](https://s21.ax1x.com/2024/10/07/pAGKc4K.png)
![pAGK6N6.png](https://s21.ax1x.com/2024/10/07/pAGK6N6.png)

左图是原本有祖孙关系的 $1-3$，从 $2$ 拎起来以后变成了横叉边。


![pAGK29O.png](https://s21.ax1x.com/2024/10/07/pAGK29O.png)
![pAGKyAx.png](https://s21.ax1x.com/2024/10/07/pAGKyAx.png)

左图是原本无祖孙关系的 $1-3$，从 $4$ 拎起来以后变成了返祖边。

也就是说，我们随便找一个节点为根，求出最小生成树，然后遍历所有的非树边。

当一条边是横叉边的时候，答案包含在他们的子树中。

当一条边是返祖边的时候，答案包含在除了他们的链的所有节点中。

然后树上差分就好了。

```cpp
#include<iostream>
#include<vector>
#include<cstdio>
#include<ctime>
#include<cmath>
#define endl '\n'
using namespace std;
const int N=3e5+10;
int fa[N],pa[N][25],dep[N],cf[N],dbg;
bool can[N];
inline int Find(int x){
    if(x==fa[x])return x;
    return fa[x]=Find(fa[x]);
}

struct edge{int u,v,w;}e[N];
vector<int>t[N];
edge fei[N];
int n,m,tot,H=20;
inline long long read(){register long long d=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')d=(d<<3)+(d<<1)+(ch^48),ch=getchar();return d*f;}
inline void init(){
    for(int j=1;j<=H;j++)
        for(int i=1;i<=n;i++)
        pa[i][j]=pa[pa[i][j-1]][j-1];
}

inline int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=H;i>=0;i--){
        if(dep[pa[x][i]]>=dep[y])x=pa[x][i];
    }
    if(x==y)return x;
    for(int i=H;i>=0;i--){
        if(pa[x][i]!=pa[y][i])x=pa[x][i],y=pa[x][i];
    }
    return pa[x][0];
}

inline void kru(){
    for(int i=1;i<=n;i++)fa[i]=i;
    int cnt=0;
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v,w=e[i].w;
        int x=Find(u),y=Find(v);
        if(x!=y){
            cnt++;
            fa[y]=x;
            t[u].push_back(v);
            t[v].push_back(u);
        }
        else{
            fei[++tot]=(edge){u,v,w};
        }
    }
}

void dfs(int u,int p){
    pa[u][0]=p;
    dep[u]=dep[p]+1;
    for(int i=0;i<t[u].size();i++){
        int v=t[u][i];
        if(v==p)continue;
        dfs(v,u);
    }
}
inline int findson(int x,int v){
    for(int i=H;i>=0;i--)if(dep[pa[x][i]]>dep[v])x=pa[x][i];
    return x;
}
inline void chafen(){
    for(int i=1;i<=tot;i++){
        int v=fei[i].v,u=fei[i].u;
        if(dep[u]<dep[v])swap(u,v);
        int l=lca(u,v);
        // cout<<u<<" "<<v<<" "<<l<<endl;
        if(l!=v){cf[1]++;cf[u]--;cf[v]--;}
        else{
            int s=findson(u,v);
            // cout<<s<<endl;
            cf[s]++;cf[u]--;
        }
    }
}

inline void dfs3(int u,int p){
    cf[u]+=cf[p];
    // cout<<u<<" "<<cf[u]<<endl;
    if(cf[u]==0)can[u]=1;
    for(int i=0;i<t[u].size();i++){
        int v=t[u][i];
        if(v==p)continue;
        dfs3(v,u);
    }
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test2.out","w",stdout);
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        e[i]=(edge){u,v,i};
    }
    // cout<<clock()<<endl;
    kru();
    // cout<<clock()<<endl;
    dfs(1,0);
    // cout<<clock()<<endl;
    init();
    // cout<<clock()<<endl;
    chafen();
    // cout<<clock()<<endl;
    dfs3(1,0);
    // cout<<clock()<<endl;
    for(int i=1;i<=n;i++)printf("%d",can[i]);
}
```

---

