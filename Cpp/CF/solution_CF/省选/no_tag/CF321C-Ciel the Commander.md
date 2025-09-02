# Ciel the Commander

## 题目描述

Now Fox Ciel becomes a commander of Tree Land. Tree Land, like its name said, has $ n $ cities connected by $ n-1 $ undirected roads, and for any two cities there always exists a path between them.

Fox Ciel needs to assign an officer to each city. Each officer has a rank — a letter from 'A' to 'Z'. So there will be 26 different ranks, and 'A' is the topmost, so 'Z' is the bottommost.

There are enough officers of each rank. But there is a special rule must obey: if $ x $ and $ y $ are two distinct cities and their officers have the same rank, then on the simple path between $ x $ and $ y $ there must be a city $ z $ that has an officer with higher rank. The rule guarantee that a communications between same rank officers will be monitored by higher rank officer.

Help Ciel to make a valid plan, and if it's impossible, output "Impossible!".

## 说明/提示

In the first example, for any two officers of rank 'B', an officer with rank 'A' will be on the path between them. So it is a valid solution.

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
A B B B
```

## 样例 #2

### 输入

```
10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
```

### 输出

```
D C B A D C B D C D
```

# 题解

## 作者：Lily_White (赞：4)

题目限制了我们最多只能使用 26 个等级。那么，我们就要考虑尽可能节省地使用它们。

如果我们钦定了某个点的等级 X，让它满足：

- 所有跨越这个点的路径，都会被这个点封掉。

那么这个点的所有子树都各变成了一个规模较小的问题。且这个问题与原问题唯一的不同就是 X 不能使用了。

我们要节省使用的等级数量，就要保证分解问题的次数尽可能少，也就是说，要让每次切出来的子树都尽可能小，这是[重心](https://oi-wiki.org/graph/tree-centroid/)的性质。这保证了我们分解问题的次数不会超过 $\log n$，那么 26 个就很显然足够了。

那么，这很明显是一个[点分治](https://oi-wiki.org/graph/tree-divide/)的模型。时间复杂度是 $O(n \log n)$。

参考代码：
```cpp
// Problem: C. Ciel the Commander
// Contest: Codeforces - Codeforces Round #190 (Div. 1)
// URL: https://codeforces.com/problemset/problem/321/C
// Written by RavenclawOIer on 11-15-2020

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define chmax(a, b) a = max(a, b)
#define chmin(a, b) a = min(a, b)
const int INF = 0x3f3f3f3f;
const int N = 100010;
vector<int> g[N];
bool ban[N];
int sz[N];
int n;
void dfs1(int u, int f) {
  sz[u] = 1;
  for (auto v: g[u]) {
    if (v == f || ban[v]) continue;
    dfs1(v, u);
    sz[u] += sz[v];
  }
}
pii dfs2(int u, int f, int s) {
  pii res(INF, -1);
  int msz = -1;
  for (auto v: g[u]) {
    if (v == f || ban[v]) continue;
    chmin(res, dfs2(v, u, s));
    chmax(msz, sz[v]);
  }
  chmax(msz, s - sz[u]);
  chmin(res, make_pair(msz, u));
  return res;
}
int get(int u) {
  dfs1(u, 0);
  return dfs2(u, 0, sz[u]).second;
}
char ans[N];
void solve(int u, int dep) {
  int s = get(u);
  ban[s] = true;
  ans[s] = 'A' + dep;
  for (auto v: g[s]) {
    if (ban[v]) continue;
    solve(v, dep + 1);
  }
  ban[s] = false;
}

int main() {
  scanf("%d", &n);
  rep(i, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  solve(get(1), 0);
  for (int i = 1; i <= n; i++) {
    putchar(ans[i]);
    putchar(' ');
  }
  puts("");
}
```

---

## 作者：Prophesy_One (赞：2)

#### 题意：

给定一棵树，每个点都有一个等级（$A$ 最大，$Z$ 最小），要求所有两个等级相同的点的路径上存在比它们等级高的点，求构造合法方案，或判断无解。

满足 $n \leq 10^5$。

#### 思路：

由题意可知一定只存在一个点等级为 $A$，故要尽可能的让更多的路径穿过这个点，显然选取树的重心最优。

到这里思路已经很明显了，类似于点分治的思想，在每颗子树中选取重心不断迭代即可。

由于 $\log_2 10^5 < 17 < 26$，所以本题一定有解。

#### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
struct edge
{
	int next,to;
}e[N<<1];
bool vis[N];
int n,rt,cnt,in[N],f[N],siz[N],ans[N];
int read()
{
	int res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
	res=(res<<1)+(res<<3)+(ch^48);
	return res*f;
}
void add(int x,int y)
{
	e[++cnt].next=in[x];
	e[cnt].to=y;
	in[x]=cnt;
}
void dfs(int u,int fa)
{
	int i,v;
	siz[u]=1;
	for(i=in[u];i;i=e[i].next)
	{
		v=e[i].to;
		if(v==fa||vis[v])
		continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
void getrt(int u,int fa,int sz)
{
	int i,v;
	f[u]=0;
	for(i=in[u];i;i=e[i].next)
	{
		v=e[i].to;
		if(v==fa||vis[v])
		continue;
		getrt(v,u,sz);
		f[u]=max(f[u],siz[v]);
	}
	f[u]=max(f[u],sz-siz[u]);
	if(f[u]<f[rt]||!rt)
	rt=u;
}
void solve(int u,int pos)
{
	int i,v;
	dfs(u,0);rt=0;getrt(u,0,siz[u]);
	ans[rt]=pos;vis[rt]=1;
	for(i=in[rt];i;i=e[i].next)
	{
		v=e[i].to;
		if(vis[v])
		continue;
		solve(v,pos+1);
	}
}
int main()
{
	int i,x,y;
	n=read();
	for(i=1;i<=n-1;i++)
	{
		x=read();y=read();
		add(x,y);add(y,x);
	}
	solve(1,0);
	for(i=1;i<=n;i++)
	printf("%c ",'A'+ans[i]);
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：2)

可以yy一下，发现选在重心越大。于是就是点分治板子

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+5,INF=1e9;
struct edge{
	int link,next;
}e[N<<1];
bool vis[N];
char ans[N];
int sz[N],fa[N],n,tot,mn,All,rt,head[N];
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
inline void init(){
	n=read();
	for (int i=1;i<n;i++) insert(read(),read());
}
void getroot(int u,int Fa){
	sz[u]=1; int mx=0; fa[u]=Fa;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=Fa&&!vis[v]){
			getroot(v,u);
			sz[u]+=sz[v];
			mx=max(mx,sz[v]);
		}
	}
	mx=max(mx,All-sz[u]);
	if (mx<mn) mn=mx,rt=u;
}
void divide(int u,int dep){
	ans[u]=dep+'A'; vis[u]=1; int tmp=All;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (!vis[v]) {
			All=(fa[u]==v)?tmp-sz[u]:sz[v];
			mn=INF; getroot(v,u); divide(rt,dep+1);
		}
	}
}
inline void solve(){
	All=n; mn=INF; 
	getroot(1,0); divide(rt,0);
	for (int i=1;i<=n;i++) putchar(ans[i]),putchar(' ');
}
int main(){
	init(); solve();
	return 0;
}
```



---

## 作者：Butterfly_qwq (赞：1)

点分治经典结论题。

首先，由于题目要求我们至多用 $26$ 个等级，也就是说我们要用的等级越少越好。

想到重心，易证重心最优。

那么这明显就是一个点分治的框架。

Code:

```cpp
#include<bits/stdc++.h>
#define ptc(x) putchar(x+64),putchar(32);
using namespace std;
const int N=114514;
int n,sz[N],mxz[N],rt,lv[N],ndc,vis[N];
vector<int>g[N];
void getrt(int u,int fa)
{
	sz[u]=1;
	mxz[u]=0;
	for(int v:g[u])
	{
		if(fa==v||vis[v])continue;
		getrt(v,u);
		sz[u]+=sz[v];
		mxz[u]=max(mxz[u],sz[v]);
	}
	mxz[u]=max(mxz[u],ndc-sz[u]);
	if(mxz[u]<mxz[rt])rt=u;
}
void solve(int u,int l)
{
	vis[u]=1;
	lv[u]=l;
	for(int v:g[u])
	{
		if(vis[v])continue;
		ndc=sz[v];
		mxz[rt=0]=n;
		getrt(v,0);
		solve(rt,l+1);
	}
}
int main()
{
	cin>>n;
	for(int i=1,u,v;i<n;i++)
	{
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	mxz[rt]=ndc=n;
	getrt(1,0);
	solve(rt,1);
	for(int i=1;i<=n;i++)ptc(lv[i]);
}
```

---

## 作者：DJRzjl (赞：1)

# [CF321C](https://www.luogu.com.cn/problem/CF321C)  Ciel the Commander

一个初步想法是将根标记为 `A`，往下每一层的点依次标记为 `B`,`C`......，这样做可以使每对相同标号点路径上都是这种标号之前的字母，一定符合要求，但是我们只有 $26$​ 种字母，显然如果树退化成一条链，这个做法就无法满足题意。

回想这个过程，我们其实是先取根把树划分为几个子树，根为最高等级 `A`，所以根不同子树之间的点一定满足题意，然后我们将问题划分为几个子问题，也就是只需要考虑各个子树内的点对是否满足题意，那么我们再令子树根为目前最高等级 `B`，然后递归下去，直到叶子。

那么我们要解决的无非是递归层数过多字母不够用的情况，联系刚才的分析，不难想到点分治来实现。

具体做法是，每次找重心，标记为递归层数对应的字母（第一层对应 `A`，第二层 `B` 以此类推），然后将重心子树抽离继续递归直到孤点。

于是我们最多递归 $\log_2n$ 次，最多所用层数不超过 $20$，也就不存在无解，按如上方案模拟构造即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

int n;
vector<int>e[N];

bool foc[N];
int siz[N],rt,totsz;
char col[N];

void dfs1(int u,int fa){
	siz[u]=1;
	for(int v:e[u]){
		if(v==fa||foc[v]) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int fa){
	int mx=0;
	for(int v:e[u]){
		if(v==fa||foc[v]) continue;
		dfs2(v,u);
		mx=max(mx,siz[v]);
	}
	mx=max(mx,totsz-siz[u]);
	if(mx<=(totsz>>1)) rt=u;
}

void solve(int u,int dep){
	rt=0;
	dfs1(u,0);
	totsz=siz[u];
	dfs2(u,0);
	foc[rt]=1;
	col[rt]='A'+dep;
	for(int v:e[rt]) if(!foc[v]) solve(v,dep+1);
}

int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	solve(1,0);
	for(int i=1;i<=n;i++) putchar(col[i]),putchar(' ');
	return 0;
}
```


---

## 作者：UhhhQQQU (赞：0)

### **题意简述**
* 给出一棵有n个点的无根树，要求构造出一种方案，使得树上的每一个结点的权值都满足 $1 \leq v_i \leq 26$ ，且对于每一对拥有相同权值 $x$ 的点，在它们的简单路径上至少有一个权值小于 $x$ 的点。

* $2 \leq n \leq 10^5$

### **题目分析**

* 做法：**点分治**

* 不难发现，用的权值种类越少越好，考虑在原树上贪心地一层层赋值，但这样不是最优的（样例二就是一个反例）。

* 进一步思考，发现赋值其实可以不用依照深度来赋值，因为限制条件仅要求在两点之间的路径上有一个更小的点。那么对于一棵子树，可以先固定子树中的一个点，使其权值为子树中最小，然后子树中剩下的点就被分成了多个部分。这个问题可以递归处理。

* 由于需要尽可能少地使用权值，所以需要想办法处理出固定结点的顺序，使得方案最优，从局部上看，就是要使得每次分出的多棵子树的大小尽可能平均——这正是树的重心所能做到的。

* 总结一下点分治的做法：从整棵树开始，每一次都先找出当前树的结点，将其赋值为子树中最小的值，然后对于分出来的多棵子树递归地处理权值。

* 由于最多递归 $log_n$ 层，所以时间复杂度为 $O(nlog_n)$ 。

* 注意：为了表述方便，题解中以数字 $1$ 至 $26$ 替代了题目中的 $26$ 个字母，输出时还是要输出字母。

* 代码
```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
struct edge{
	int nxt,go;
}e[N*2];
int head[N],cnt;
void add(int u,int v){e[++cnt]=(edge){head[u],v},head[u]=cnt;}
int sz[N],maxn[N];
int n,rt;
bool vis[N];
void findrt(int u,int f,int rsz)
{
	sz[u]=1;
	maxn[u]=0;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].go;
		if(v!=f&&!vis[v])
			findrt(v,u,rsz),sz[u]+=sz[v],maxn[u]=max(maxn[u],sz[v]);
	}
	maxn[u]=max(maxn[u],rsz-sz[u]);
	if(maxn[u]<maxn[rt]||!rt)
		rt=u;
}
int d[N];
void dfs(int u,int f,int dep)
{
	d[u]=dep,vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].go;
		if(v!=f&&!vis[v])
		{
			rt=0;
			findrt(v,u,sz[v]);
			dfs(rt,u,dep+1);
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		add(u,v),add(v,u);
	}
	findrt(1,0,n);
	dfs(rt,0,0);
	for(int i=1;i<=n;i++)
		printf("%c ",d[i]+'A');
	return 0;
}
```


---

