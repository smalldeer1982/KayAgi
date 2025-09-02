# Information Graph

## 题目描述

在某公司中有n名员工（编号为1至n），开始时员工之间没有任何关系，在接下来的m天会发生以下事：

1.y成为了x的上司（x在那之前不会有上司）

2.员工x得到了一份文件，然后x把文件传给了他的上司，然后上司又传给了他的上司，以此类推，直到某人没有上司，将文件销毁

3.询问x是否看过某份文件。



1.	如果t=1，然后读入两个整数x,y（1<=x,y<=n）表示员工编号，y成为了x的上司，保证这时x不会有上司。


3.	如果t=3，然后读入两个整数x，i，表示查询员工x是否阅读过文件i，保证i已经被输入。(就是不会出现这份文件还没被任何人读过的情况)。

 保证输入至少有一个第三种类型的操作。

## 样例 #1

### 输入

```
4 9
1 4 3
2 4
3 3 1
1 2 3
2 2
3 1 2
1 3 1
2 2
3 1 3
```

### 输出

```
YES
NO
YES
```

# 题解

## 作者：Treaker (赞：8)

考虑在线维护非常难以维护。所以，我们考虑离线。而且，当一个点成为另一个点的祖先时，就不会再改变了。

我们用并查集来维护操作1的集合连边问题。

然后，我们对于操作2，考虑一个文件会被一个人看见，当且仅当这个人在当前操作的这个人和最顶端的人之间的链上，那么我们记录一下这两个人。

最后，对于操作3，只需要看这个人是不是在这个文件对应记录的两个人之间的链上即可。

（至于怎么判断，就可以各显神通了，可以倍增也可以入栈出栈序来判断，我用的入栈出栈序）

```cpp
const int N = 1e5 + 5;
typedef std::pair<int,int> pp;
#define mp std::make_pair
int n , m , num , cnt;
int fa[N] , s[N] , t[N] , c[N];
bool vis[N];
std::vector<pp> v[N];
struct Edge
{
	int to; Edge *nxt;
	Edge(int to = 0,Edge *nxt = NULL) : to(to) , nxt(nxt) {}
} *head[N] , pool[N] , *tail = pool;
inline void add(int u,int v) { head[u] = new (tail ++) Edge(v,head[u]);}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]);}
void dfs(int x)
{
	vis[x] = 1;
	for(Edge *i = head[x];i;i = i -> nxt) dfs(i -> to);
	for(int i = 0;i < (int)v[x].size();i ++) if(vis[v[x][i].first]) c[v[x][i].second] ++;
	vis[x] = 0;
}
int main()
{
	n = read(); m = read();
	for(int i = 1;i <= n;i ++) fa[i] = i;
	for(int i = 1;i <= m;i ++)
	{
		int opt = read() , x = read() , y;
		if(opt != 2) y = read();
		if(opt == 1)
		{
			add(y,x);
			fa[x] = find(y);
		}
		else if(opt == 2) 
		{
			num ++;
			s[num] = x; t[num] = find(x);
		}
		else
		{
			cnt ++;
			v[x].push_back(mp(t[y],cnt));
			v[s[y]].push_back(mp(x,cnt));
		}
	}
	for(int i = 1;i <= n;i ++) if(i == find(i)) dfs(i);
	for(int i = 1;i <= cnt;i ++) puts(c[i] == 2 ? "YES" : "NO");
	return 0;
}
```


---

## 作者：co7ahang (赞：4)

题目：CF466E
[洛谷链接](https://www.luogu.com.cn/problem/CF466E)
[CF 链接](https://codeforces.com/problemset/problem/466/E)

模拟赛把 T1 跳了来写这个（T3），离线思路很简单，比 T1 思维题好想。

首先，最终状态是若干颗上下级关系的树，所以我们可以将整个问题放在最后建好的树树上考虑。

对于操作一，将 $x$ 与 $y$ 连边即可。

对于操作二，可以用并查集优化复杂度快速找出当前的最高上司。

对于操作三，我们在每次操作二时把上下两个节点 $(u_p, u_d)$ 储存下来，判断节点 $x$ 是否在路径 $i$ 上可以使用最近公共祖先（LCA），若 $\text{LCA}(u_p, x) = u_p \land \text{LCA}(x, u_d) = x$，则 $x$ 在路径上，反之则不在。

需要注意的是，最终状态不一定是一棵树，可能有多棵树，在 LCA 初始化时要处理一下。

倍增写 LCA 的话时间复杂度为 $O(n \log n)$。

赛时代码如下：

```cpp
namespace dsu {
	int fa[N];
	void init(int n) {
		for(int i = 1; i <= n; i++) fa[i] = i;
	}
	int find(int u) {
		if(fa[u] == u) return u;
		fa[u] = find(fa[u]);
		return fa[u];
	}
	void connect(int u, int v) {
		fa[u] = v;
	}
}
typedef pair<int, int> pii;
 
vector <int> G[N]; // 存图
int n, m;
vector <pii> ask; // 离线询问
pii cov[N]; // 操作二区间存储
int tp = 0;
int root;
int st[N][20];
int dep[N];
bool vis[N];
 
void dfs(int u, int f, int d) {
	vis[u] = 1;
	st[u][0] = f;
	dep[u] = d;
	for(int i = 1; i <= 19; i++) st[u][i] = st[ st[u][i - 1] ][i - 1];
	for(auto v : G[u]) {
		if(v == f) continue;
		dfs(v, u, d + 1);
	}
	return;
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	if(u == v) return u;
	for(int i = 19; i >= 0; i--) {
		if(dep[st[u][i]] >= dep[v]) u = st[u][i];
	}
	if(u == v) return u;
	for(int i = 19; i >= 0; i--) {
		if(st[u][i] != st[v][i]) u = st[u][i], v = st[v][i];
	}
	return st[u][0];
}
vector <int> rootl;
 
int32_t main() {
	n = read(), m = read();
	dsu::init(n);
	while(m--) {
		int opt = read();
		if(opt == -1) break;
		if(opt == 1) {
			int u = read(), v = read();
			dsu::connect(u, v);
			G[u].push_back(v);
			G[v].push_back(u);
			rootl.push_back(v);		
		} else if(opt == 2) {
			int u = read();
			cov[++tp] = {u, dsu::find(u)};
			//cout << "Line: " << tp <<" / "<< u << " -> " << dsu::find(u) << endl;
		} else {
			int u = read(), v = read();
			ask.push_back({u, v});
		}
	}
	for(int i = 1; i <= n; i++) {
		int root = dsu::find(i);
		if(!vis[root]) 	dfs(root, root, 1);
	}//不止一棵树，有多个根节点要初始化 
	for(auto [x, i]:ask) {
		int upp = cov[i].second, udd = cov[i].first;
		if(dsu::find(x) != dsu::find(upp)) cout << "NO" << endl;
		else if(x == upp || x == udd) cout << "YES" << endl;	
		else cout << (lca(upp, x) == upp && lca(udd, x) == x ? "YES" : "NO") << endl;
	}
	return 0;
}
```

---

## 作者：myzzym (赞：4)

## 思路：
### 整体思路
我这个~~大 cong ming~~是在线维护 lca 的（主要不会离线）（什么是 lca 就不说了）。

设 $f_{i,j}$ 是 $x$ 点往上跳 $2^{y}$ 步（倍增）。

当 $t$ 是 $1$ 的时候就维护每个点的 $f$ 数组和深度。

当 $t$ 是 $2$ 的时候用数组 $d1,d2$ 记录一开始知道的那个人和最后销毁文件的那个人，则 $d1_{i}$ 至 $d2_{i}$ 的这一段人都看过文件。

当 $t$ 是 $3$ 的时候只需要看这个人是不是在这个文件对应记录的两个人之间的链上就ok了。

~~这个思路看起来非常的ok啊~~，那我们就来解决在线维护的问题。

### 维护
#### 1. 维护深度

设 $dep_{x}$ 是 $x$ 的深度，那我们可以用并查集来维护 $dep_{x}$，一开始连上 $x$ 和 $y$ 就可以了。

代码如下：

#### 更新
```cpp
int getfa(int x){
	if(g[x]==x) return x;
	int r=getfa(g[x]);
	dep[x]+=dep[g[x]]-1;
	g[x]=r;
	return r;
}
```
#### 连接
```cpp
int fy=getfa(y);
g[x]=fy,dep[x]+=dep[y];
```
#### 2. 维护 $f$ 数组

设 $fi_{x}$ 记录 $f_{x}$ 已经更新到哪里了（避免重复更新），先更新 $x$ 的深度，然后更新 $f_{f_{x,fi_{x}-1},fi_{x}-1}$，然后先更新 $dep_{f_{x,fi_{x}-1}} \dots$ 以此类推。

代码如下：
#### 更新
```cpp
void change(int u){
	int r=getfa(u);
	int x=fi[u];
	for(;(1<<x)<dep[u];x++){
		if(!f[f[u][x-1]][x-1])
			change(f[u][x-1]);
		f[u][x]=f[f[u][x-1]][x-1];
	}
	fi[u]=x;
}
```
#### 连接
```cpp
int fy=getfa(y);
f[x][0]=y,fi[x]=1;
```

#### 3. lca

正常倍增 lca 去掉后面部分，然后加判断（只需要判断他们是不是祖孙关系就可以了），边跳边更新 $f$ 数组和更新深度。

代码如下：
```cpp
int lca(int x,int y){
	change(x),change(y);
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=fi[x]-1;i>=0;i--){
		if(dep[f[x][i]])
			change(f[x][i]);
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	}
	if(x==y)
		return x;
	else
		return 0;
}
```

然后把上面的结合起来，就 ok 了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
int f[N][25],fi[N];
int dep[N],g[N];
int d[N],td[N],di;
int getfa(int x){
	if(g[x]==x) return x;
	int r=getfa(g[x]);
	dep[x]+=dep[g[x]]-1;
	g[x]=r;
	return r;
}
void change(int u){
	int r=getfa(u);
	int x=fi[u];
	for(;(1<<x)<dep[u];x++){
		if(!f[f[u][x-1]][x-1])
			change(f[u][x-1]);
		f[u][x]=f[f[u][x-1]][x-1];
	}
	fi[u]=x;
}
int lca(int x,int y){
	change(x),change(y);
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=fi[x]-1;i>=0;i--){
		if(dep[f[x][i]])
			change(f[x][i]);
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	}
	if(x==y)
		return x;
	else
		return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		g[i]=i,dep[i]=1;
	for(int i=1;i<=m;i++){
		int t,x,y;
		scanf("%d",&t);
		if(t==1){
			scanf("%d%d",&x,&y);
			int fy=getfa(y);
			g[x]=fy,f[x][0]=y,fi[x]=1,dep[x]+=dep[y];
		}
		if(t==2){
			scanf("%d",&x);
			d[++di]=x,td[di]=getfa(x);
		}
		if(t==3){
			scanf("%d%d",&x,&y);
			if(lca(x,td[y])==td[y]&&lca(x,d[y])==x)
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	
	return 0;
}
```

---

## 作者：ZolaWatle (赞：3)

## CF466E 题解

判词：一道比较好的综合题。

显然地，在若干次操作后，员工们的关系一定类似于**树**（为什么是类似于稍后解释）。考虑到在线更新和询问较为麻烦，我们可以离线处理。

我们注意到这样一句话：

> $y$ 成为了 $x$ 的上司，保证这时 $x$ 不会有上司。

可以证明离线处理的正确性。

离线的具体操作如下。

- 对于文件 $i$，我们记录第一个看到它的员工 $ st $ 以及最后一个看见它并且将其销毁的员工 $ ed $ 。

- 对于询问 $i$，我们记录员工编号 $ cur $ 以及文件编号 $id$ 。离线回答询问。

容易想到，对于任何一份文件 $i$，员工能读到文件，**当且仅当**此员工在从 $ st_i $ 到 $ ed_i $ 的这一条链上。这是因为员工传递文件时，只会向其**直接上司**（可以抽象理解为父亲节点）传递。

考虑如何求出 $ ed_i $ 。我们可以使用**并查集**维护题目中的操作一。对于每一个 $ st_i $，可以知道相对应的 $ ed_i $ 应是此连通块的根（也就是当前官最大的上司）。显然地，$ ed_i $ 应该在线求得。

考虑如何回答询问。如何判断当前询问中的员工是否处于当前询问中的文件所在的链上呢？

来看下面这张图片。

![](https://cdn.luogu.com.cn/upload/image_hosting/hipk18na.png)

设 $ low(5) $ 是文件的起点，$ hig(1) $ 是文件的终点，$ cur(4) $ 代表当前询问的员工。那么 $ 1\to  5 $ 即是这一条链。

我们发现，如果在这样的一条链上求**最近公共祖先**，一定有 $ \text{LCA(low,cur)} = \text{cur} $；$ \text{LCA(hig,cur)} = \text{hig} $。当然，前提是 $ cur $ 的深度在 $ low $ 和 $ hig $ 之间。

这样一来，维护一个 $ \text{LCA} $，询问的判断就能够求解了。

值得注意的是，在本题中，所有员工构成的关系网络并不一定是一颗树。很有可能在 $m$ 次操作中，有很多的员工根本没有被提及。这意味着，所有员工之间的关系并不是树，而是**森林**，而且还有可能存在孤点。

因此，在回答询问时，我们应该先判断员工和文件的始终**是否都处于同一连通块内**，才能通过求 $ \text{LCA} $ 进行判断。

同样地，在进行 $ \text{LCA} $ 的预处理时，我们应该枚举每一个点：如果该点是其所属的连通块的根，我们都要以它为根节点进行一次 $ \text{dfs} $ 的预处理。

讲得应该是挺清楚了，更多的细节请看完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN=1e5+1;
int n,m,fa[MAXN],dep[MAXN],F[MAXN][21];
int file_tot,query_tot;
vector <int> E[MAXN];
struct File{int st,ed;}file[MAXN];
struct Q{int worker,id;}query[MAXN];

inline int root(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=root(fa[x]);
}//并查集+路径压缩 

inline void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	F[x][0]=fa;
	for(int i=1;i<=20;i++)
		F[x][i]=F[F[x][i-1]][i-1];  //倍增 
	for(int i=0;i<E[x].size();i++)
		dfs(E[x][i],x); 
}//预处理 

inline int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[F[x][i]]>=dep[y])
			x=F[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
		if(F[x][i]!=F[y][i])
		{
			x=F[x][i];
			y=F[y][i];
		}
	return F[x][0];
}//LCA板子 

int main()
{
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++)
		fa[i]=i;  //并查集的初始化 
	
	while(m--)
	{
		int idx;
		scanf("%d",&idx);
		if(idx==1)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			E[y].push_back(x);  //题中明确给出了x, y两点的从属关系，无须建双向边 
			fa[x]=root(y);  //保证root函数查询到的是连通块的根 
		}
		else if(idx==2)
		{
			int x;
			scanf("%d",&x);
			file[++file_tot].st=x;  //存储为链的起始点 
			file[file_tot].ed=root(x);  //查询连通块的根，存储为链的终止点 
		}
		else
		{
			int x,i;
			scanf("%d%d",&x,&i);
			query[++query_tot].worker=x;
			query[query_tot].id=i;
		}//离线处理 
	}
	
	for(int i=1;i<=n;i++)
		if(i==root(i))
			dfs(i,0);  //森林！ 
			
	for(int i=1;i<=query_tot;i++)
	{
		int fid=query[i].id;
		int low=file[fid].st,hig=file[fid].ed,cur=query[i].worker;
		int rl=root(low),rh=root(hig),rc=root(cur);  //分别找到三者的根 
		if(rl!=rh||rl!=rc||rh!=rc)  //判断是否处于同一连通块中 
		{
			puts("NO");
			continue;
		}
		if(LCA(low,cur)==cur&&LCA(hig,cur)==hig)  //满足刚才所说的性质 
			puts("YES");
		else
			puts("NO");
	}
	
	return 0;
}
```

------------

一点题外话：

$ \text{MnZn} $ 的第一篇紫题题解，谢谢大家的阅读。

---

## 作者：Svemit (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Svemit/p/17783903.html)

[题目传送门](https://www.luogu.com.cn/problem/CF466E)

这个人只会做这种水题了。。。

# Solution

直接做显然不太好做，考虑把询问离线下来在静态森林中查询。

对于操作 1，直接连边就可以了。

对于操作 2，容易发现能看到这个文件的一定是一条从祖先到子节点的一条链，记录这个文件被看到的链顶和链底即可。

对于操作 3，只需要知道 $x$ 在不在某条链上。显然可以大力树剖，不过这里有更简单的方法。

利用这条链是祖先向下的性质，$x$ 在这条链上的充要条件是 $x$ 在链顶的子树中，链底在 $x$ 的子树中。

判断是否在子树中直接欧拉序就好了。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = (j); i <= (k); i ++)
#define per(i, j, k) for(int i = (j); i >= (k); i --)
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
const int N = 1e5 + 5, INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
int n, m, idx;
vector<int> e[N];
int st[N], ed[N];
int fa[N];
int L[N], R[N], tim;
vector<array<int, 3>> event;
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void dfs(int u) {
	L[u] = ++ tim;
	for(auto v : e[u]) dfs(v);
	R[u] = tim;
}
bool ins(int u, int v) { // v 是否在 u子树里 
	return L[u] <= L[v] && L[v] <= R[u];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> m;
	rep(i, 1, n) fa[i] = i;
	while(m --) {
		int op, u, v;
		cin >> op >> u;
		if(op == 1) {
			cin >> v;
			e[v].push_back(u);
			fa[u] = find(v);
		} 
		else if(op == 2) {
			st[++ idx] = find(u);
			ed[idx] = u;
		}
		else {
			cin >> v;
			event.push_back({st[v], ed[v], u});
		}
	}
	rep(i, 1, n) if(find(i) == i) dfs(i);
	for(auto evt : event) {
		if(ins(evt[0], evt[2]) && ins(evt[2], evt[1])) cout << "YES\n";
		else cout << "NO\n";
	}
    return 0;
}
```

---

## 作者：SCma (赞：1)

# 思路
1. 离线处理与并查集：将上司的更替理解为建边操作，再完成所有操作之后我们会获得一个**森林**。而处于在线操作时，我们则通过使用并查集记录每一次文件传递的起点和终点。
2. 最近公共祖先：若某位员工看到过某一份文件，则不难发现，这份文件的起始传递员工和被查询者的最近公共祖先为被查询者、这份文件的结束传递员工（最终上司）和被查询者的最近公共祖先为结束传递员工。

# 代码实现
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define MIN(a,b,c) min(min(a,b),c)
#define MAX(a,b,c) max(max(a,b),c)
#define ri register int
#define int long long
#define fixedset(a) fixed << setprecision(a)
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
#define ls(x) x<<1
#define rs(x) x<<1|1
#define MAXN 9.2211e18
#define inf 2114514
#define mf 5011
#define sf 1011
using namespace std;
mt19937_64 randint{std::chrono::steady_clock::now().time_since_epoch().count()};
int n,m,a,b,c,idx,cnt,dsu[mf*20],dep[mf*20],lca[mf*20][sf/33];
pii res[inf],rcd[inf];
vector<int> edge[inf];
int find(int u){
	if(dsu[u]==u) return u;
	else return dsu[u]=find(dsu[u]);
}
void merge(int u,int v){
	dsu[find(u)]=find(v);
	return ;
}
void dfs(int u,int fa){
	lca[u][0]=fa,dep[u]=dep[fa]+1;
	for(ri i=1;i<=(int)(log2(dep[u]));i++) lca[u][i]=lca[lca[u][i-1]][i-1];
	for(auto v:edge[u]) if(v!=fa) dfs(v,u);
	return ;
}
int LCA(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	while(dep[u]>dep[v]) u=lca[u][(int)(log2(dep[u]-dep[v]))];
	if(u==v) return u;
	for(ri i=(int)(log2(dep[u]));i>=0;i--) if(lca[u][i]!=lca[v][i]) u=lca[u][i],v=lca[v][i];
	return lca[u][0];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin >> n >> m;
    for(ri i=1;i<=n;i++) dsu[i]=i;
    for(ri i=1;i<=m;i++){
    	cin >> a >> b;
    	if(a==1){
    		cin >> c;
    		edge[b].push_back(c); edge[c].push_back(b); merge(b,c); 
		}else if(a==2) rcd[++cnt]=mp(b,find(b));
		else if(a==3){
			cin >> c;
			res[++idx]=mp(b,c); 
		}
	}
    
    for(ri i=1;i<=n;i++) if(dsu[i]==i) dfs(i,0);
    for(ri i=1;i<=idx;i++){
    	int x=res[i].first,y=rcd[res[i].second].first,z=rcd[res[i].second].second;
    	if(LCA(x,y)==x && LCA(x,z)==z) cout << "YES" << endl;
    	else cout << "NO" << endl;
	}
	return 0;
}

```

---

## 作者：Alexxtl (赞：1)

[**更好的阅读体验**](https://www.cnblogs.com/Alexxtl/p/18312437)

## 题目链接

[**Luogu**](https://www.luogu.com.cn/problem/CF466E)

[**Codeforces**](https://codeforces.com/problemset/problem/466/E)

## 题意简述

某公司中有 $n$ 名员工。为方便起见，将这些员工从 1 至 $n$ 编号。起初，员工之间相互独立。接下来，会有以下 $m$ 次操作：

1. 员工 $y$ 成为员工 $x$ 的上司。**保证此前 $x$ 没有上司**。

2. 员工 $x$ 拿到一份文件并签字，随后交给他的上司。他的上司签字后，再交给更上一级。依此类推，直到文件传递到的那个人没有上司为止。

3. 询问员工 $x$ 是否在第 $i$ 件文件上签过字。文件编号为上一件文件的编号再加 1，第一件文件的编号为 1。如果是，输出 ```YES```，否则输出 ```NO```。

## 解法说明

显然，我们可以将员工之间的关系看作**森林**，将每个员工看作一个节点，其与上司的关系看作一条边。之所以不是一棵树，是因为在 $m$ 次操作中，有些人可能并没有被指定上司，所以员工之间的关系很可能并不是一棵树而是**森林**。

通过观察题面可以发现，一个员工在成为另一个员工的上司后，就不会再有更改了。由于在线操作过于麻烦，我们可以考虑**离线**。

具体离线方法如下：

- 对于操作 1，直接连边即可，不过这里还要**在线**维护一个**并查集**；

- 对于操作 2，分别记下第一个和最后一个对文件签字的员工，后者就是**前者所在的连通块的根**，利用**并查集**查找；

- 对于操作 3，分别记下员工编号及文件编号，**离线回答**。

接下来分析如何回答询问。可以发现，如果询问的员工 $x$ 在 最开始看到文件 $i$ 的员工与最后看到文件 $i$ 的员工之间的链上，那么 $x$ 就看过文件。所以，问题就被转化为了**判断 $x$ 是否在这条链上**。

考虑如何判断。

设 $st$ 为链的起始点，$ed$ 为截止点，可推得如 $x$ 在链上，则 $\text{lca}(x,st) = x$ 且 $\text{lca}(x,ed) = ed$，维护一个 **LCA** 即可求解。我这里用的是树剖求 LCA，倍增也可以。

还有一些细节需要注意。由于员工之间的关系是**森林**而非一棵树，所以我们在预处理树剖时应枚举每个点，如果该点**是其所属的连通块的根**，就对其进行一次预处理，且回答询问时应首先判断 $x$ 与 $st$、$ed$ **是否在同一连通块内**，如果不在直接输出 ```NO```，否则再执行下一步操作。

剩余细节详见下面代码中的注释。

## 通过代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define mp make_pair
const int N=1e5+10;

namespace IO{
    //快读 
    inline int read(){
        int x=0,f=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){
            if(ch=='-'){
                f=-1;
            }
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            x=(x<<1)+(x<<3)+(ch^48);
            ch=getchar();
        }
        return x*f;
    }
    
    //快写 
    inline void write(int x){
        if(x<0){
            putchar('-');
            x=-x;
        }
        if(x>9){
            write(x/10);
        }
        putchar(x%10+'0');
    }
} 

using namespace IO;

namespace code{
    //链式前向星存图 
    int head[N],tot;
    
    struct node{
        int ver,next;
    }t[N<<1];
    
    void add(int x,int y){
        t[++tot].ver=y,t[tot].next=head[x],head[x]=tot;
    }
    
    //并查集
    int fa[N];
    
    int getfa(int x){
        if(fa[x]==x){
            return x;
        }
        return fa[x]=getfa(fa[x]);
    } 
    
    //树链剖分 
    int fat[N],size[N],son[N],deep[N],top[N];
    
    void dfs1(int x){
        size[x]=1;
        int maxson=-1;
        for(int i=head[x];i;i=t[i].next){
            int y=t[i].ver;
            if(y==fat[x]){
                continue;
            } 
            fat[y]=x;
            deep[y]=deep[x]+1;
            dfs1(y);
            if(size[y]>maxson){
                maxson=size[y];
                son[x]=y;
            }
            size[x]+=size[y];
        }
    }
    
    void dfs2(int x,int from){
        top[x]=from;
        if(!son[x]){
            return;
        }
        dfs2(son[x],from);
        for(int i=head[x];i;i=t[i].next){
            int y=t[i].ver;
            if(y==son[x]||y==fat[x]){
                continue;
            }
            dfs2(y,y);
        }
    }
    
    //求LCA
    int lca(int x,int y){
        while(top[x]!=top[y]){
            if(deep[top[x]]<deep[top[y]]){
                swap(x,y);
            }
            x=fat[top[x]];
        }
        if(deep[x]<deep[y]){
            return x;
        }
        return y;
    }
    
    //主程序 
    int n,m,f_tot,q_tot;
    PII file[N],query[N];
    
    void solve(){
        n=read(),m=read();
        for(int i=1;i<=n;i++){//并查集预处理 
            fa[i]=i;
        }
        for(int i=1;i<=m;i++){//离线处理 
            int op=read();
            if(op==1){
                int x=read(),y=read();
                add(y,x);//单向边 
                fa[x]=getfa(y);//在线维护并查集 
            }else if(op==2){
                int x=read();
                file[++f_tot]=mp(x,getfa(x));
            }else{
                int x=read(),y=read();
                query[++q_tot]=mp(x,y);
            }
        }
        for(int i=1;i<=n;i++){//枚举所有点 
            if(getfa(i)==i){//判断是否为所在连通块的根 
                deep[i]=1;//树剖预处理 
                fat[i]=i;
                dfs1(i);
                dfs2(i,i);
            }
        }
        for(int i=1;i<=q_tot;i++){
            int x=query[i].first,y=query[i].second,st=file[y].first,ed=file[y].second;
            if(getfa(x)!=getfa(st)){//是否在同一个连通块 
                printf("NO\n");
                continue;
            }
            if(lca(x,st)==x&&lca(x,ed)==ed){//判断 
                printf("YES\n");
            }else{
                printf("NO\n");
            }
        }
    }
}

using namespace code;

signed main(){
    solve();
    return 0;
}
```

---

## 作者：yyz1005 (赞：0)

上司什么的显然联想到并查集。

注意到任意时刻 $n$ 个员工根据上司下属关系构成森林。

对于一份文件 $u$，不妨将询问离线，在 $x$ 收到其时记录此时的 $x$ 与 $x$ 的当前最高的（相当于没有上司的）上司 $y$，取 $st_u = x,ed_u = y$。

事实上对于关于文件 $x$ 的询问 $S$ 是否查询过该文件，只需要询问 $x$ 是否在 $st_S$ 到 $ed_S$，对于这一问题，不妨在最终的森林上通过欧拉序来判定。

[Code](https://codeforces.com/contest/466/submission/280040441)

---

## 作者：MiPloRAs_3316 (赞：0)

[可能更好的食用体验](/blog/560595/solution-cf466e) $|$ 
[题目传送门](/problem/CF466E)

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Analysis 思路}}}}$

> $y$ 成为了 $x$ 的上司（$x$ 在那之前不会有上司）

通过对题目的分析，显而易见地，各个成员之间的关系会形成**很多棵树（森林）**。

而且每一个成员（任意节点）最多只会有一个上司（祖先节点）。（也有可能没有上司……）

所以，一棵树的形态是确定的。鉴于在线查询会有些复杂，所以可以将每个询问储存下来，进行离线查询。

---
为了更好的讲述每一种操作，举个简单的例子：
```txt
5 10
1 3 2
2 2
1 2 1
3 3 1
1 5 1
1 4 2
2 5
2 4
3 2 2
3 1 1 
//↑，这里查询了第1个文件，而不是像样例一样，传输一个，查询一个
```

1. $y$ 是 $x$ 的上司：   
在 $x$ 和 $y$ 之间建立一条**有向边**。

2. $x$ 将文件向上传输：   
每一个文件的传输路径一定是一条链，但成员结构是在不断变化的，所以需要将当前传输路径的开始节点和结束节点记录一下。     
此处，为了优化时间，使用**并查集**记录每个节点的最高级上司。（但不用每次更新，只需要在执行第二种操作时更新，具体见代码。）

3. $x$ 是否在 $y$ 号文件的传输路径上：     
判断 $\operatorname{lca(x,y_{st})}$ 是否为 $x$，$\operatorname{lca(x,y_{ed})}$ 是否为 $y_{ed}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/o5cwlb7o.png)

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Code 代码}}}}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m,x,y,idx=0,cnt=0,op,numq;
int ans[maxn],fa[maxn],head[maxn],dep[maxn],f[maxn][20];
struct Edge{//邻接表
	int next,to;
}edge[maxn<<1];
struct Q{//qry 记录查询，doc 记录文件的开始和结束
	int x,y;
}qry[maxn],doc[maxn];

int find(int a){
	if(fa[a]!=a) return fa[a]=find(fa[a]);
	return fa[a];
}
void merge(int x,int y){
	if(find(x)!=find(y)) fa[find(x)]=find(y);
}//并查集

void add(int u,int v)
{
	edge[++idx].next=head[u];
	edge[idx].to=v;
	head[u]=idx;
}//建邻接表

void dfs(int u,int root)
{
	dep[u]=dep[root]+1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==root) continue;
		f[to][0]=u;
		for(int k=1; (1<<k)<=dep[u]; k++)
			f[to][k]=f[f[to][k-1]][k-1];
		dfs(to,u);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19; i>=0; i--)
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return y;
	for(int i=19; i>=0; i--)
		if(f[x][i]!=f[y][i])
		x=f[x][i],y=f[y][i];
	return f[x][0];
}//LCA基本操作

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) fa[i]=i;
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d",&op,&x);
		if(op==1)
		{
			scanf("%d",&y);
			add(y,x),merge(x,y);
		}
		if(op==2)
			doc[++cnt]=(Q){x,find(x)};
		if(op==3)
		{
			scanf("%d",&y);
			qry[++numq]=(Q){x,y};
		}
	}
	for(int i=1; i<=n; i++)//可能是森林，每一棵树都要跑一次
		if(fa[i]==i) dfs(i,0);
	for(int i=1; i<=numq; i++)//离线查询
	{
		int x=qry[i].x,ii=qry[i].y,st=doc[ii].x,ed=doc[ii].y;
		if(lca(x,st)==x && lca(x,ed)==ed) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：__stick (赞：0)

# 题意
相信看了题大家都能明白，首先是一个动态加边的操作，然后是从当前点到他的根节点全部打上标记，询问一个节点有没有标记。
# 思路
首先没有想到在线做法，所以考虑离线。

最麻烦的是这个加边操作，我们想可不可以将加边操作离线下来变成一个森林，将问题转化为链上的问题，发现这是可以的。

由于题目的加边操作保证了这是一棵森林，所以我们只需要确定链的两个端点就能得到答案。发现每次都是一路穿到目前的根节点，所以我们只需要维护当前森林中每棵树的根节点即可，这就可以使用并查集解决问题了，每次我们都将 $x$ 合并到 $y$ 保证 $y$ 的祖先也是 $x$ 的祖先，这样我们就能快速找出每个节点所在的根节点了，所以第二个操作就变成了一个链上问题，我们直接暴力处理出来每个文件对应的链即可，这里我（~~十分sb的~~）使用了树剖，将链划分成若干个区间，由于每个区间上的 dfs 序都是连续的，所以查询的时候暴力判断当前点的 dfs 序是否被包含于某个个区间即可。

这样时空复杂度复杂度都是是 $O(n\log n)$。

显然可以使用一些更智慧的解决方案，由于每个文件对应的链的两个端点一定有祖孙关系，即 lca 在某一点上，所以我们就可知直接判断要询问的点是不是深度较小点的后代，是不是深度较大点的祖先就行了，这个可以通过 dfs 序做到 $O(1)$ 所以这个题就能在线性时间内解决。

# 代码
树剖的代码就不贴了，想看的翻我提交记录，然后这里在说一下判断祖先的操作，将核心代码贴出来：
```cpp
vi in(n+1),out(n+1);int tt=0;
function<void(int)>dfs=[&](int u)
{
	in[u]=++tt;
	for(const int& v:e[u])dfs(v);	
	out[u]=tt;	
};
for(int i=1;i<=n;i++)if(getf(i)==i)dfs(i);
auto is=[&](int u,int v){return in[v]>=in[u]&&out[v]<=out[u];};//询问u 是不是v 的祖先 
```

那个 is 函数就是关键，in 就是 dfs 序，out 就是结束遍历当前子树时的 dfs 序，其他的看一下代码就懂了。
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
const int mod=998244353;
signed main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	vii e(n+1);
	vector<pii> as;as.reserve(m+1);
	vi F(n+1);
	iota(F.begin(),F.end(),0);
	function<int(int)>getf=[&](int x){return F[x]==x?x:F[x]=getf(F[x]);};
	vector<pii> ch;ch.reserve(m+1);
	int op,x,y;
	for(int i=1;i<=m;i++)
	{
		cin>>op>>x;
		if(op==1)
		{
			cin>>y;
			e[y].push_back(x);
			F[getf(x)]=getf(y);
		}
		else if(op==2)ch.push_back({getf(x),x});	
		else
		{
			cin>>y;
			as.push_back({x,y});
		}
	}
	vi in(n+1),out(n+1);int tt=0;
	function<void(int)>dfs=[&](int u)
	{
		in[u]=++tt;
		for(const int& v:e[u])dfs(v);	
		out[u]=tt;	
	};
	for(int i=1;i<=n;i++)if(getf(i)==i)dfs(i);
	auto is=[&](int u,int v){return in[v]>=in[u]&&out[v]<=out[u];};//询问u 是不是v 的祖先 
	for(const pii& p:as)
	{
		int i=p.Y-1,x=p.X;
		if(is(ch[i].X,x)&&is(x,ch[i].Y))cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```




---

