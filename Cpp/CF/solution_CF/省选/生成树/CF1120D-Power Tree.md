# Power Tree

## 题目描述

You are given a rooted tree with $ n $ vertices, the root of the tree is the vertex $ 1 $ . Each vertex has some non-negative price. A leaf of the tree is a non-root vertex that has degree $ 1 $ .

Arkady and Vasily play a strange game on the tree. The game consists of three stages. On the first stage Arkady buys some non-empty set of vertices of the tree. On the second stage Vasily puts some integers into all leaves of the tree. On the third stage Arkady can perform several (possibly none) operations of the following kind: choose some vertex $ v $ he bought on the first stage and some integer $ x $ , and then add $ x $ to all integers in the leaves in the subtree of $ v $ . The integer $ x $ can be positive, negative of zero.

A leaf $ a $ is in the subtree of a vertex $ b $ if and only if the simple path between $ a $ and the root goes through $ b $ .

Arkady's task is to make all integers in the leaves equal to zero. What is the minimum total cost $ s $ he has to pay on the first stage to guarantee his own win independently of the integers Vasily puts on the second stage? Also, we ask you to find all such vertices that there is an optimal (i.e. with cost $ s $ ) set of vertices containing this one such that Arkady can guarantee his own win buying this set on the first stage.

## 说明/提示

In the second example all sets of two vertices are optimal. So, each vertex is in at least one optimal set.

## 样例 #1

### 输入

```
5
5 1 3 2 1
1 2
2 3
2 4
1 5
```

### 输出

```
4 3
2 4 5 
```

## 样例 #2

### 输入

```
3
1 1 1
1 2
1 3
```

### 输出

```
2 3
1 2 3 
```

# 题解

## 作者：liangbowen (赞：44)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1120D)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16668271.html)

这是一道巧妙的问题。前置芝士：dfs 序、最小生成树（kruskal）。

另外的题解讲得都很不详细，我就补篇题解。

## 思路

我们可以先找出这棵树的 dfs 序。dfs 序的特点是，相邻叶节点的 dfs 序总是连续的。

那对于每个点，我们就可以求出，它所能控制的叶节点对应的 dfn 序的一个区间。

这样就转化为一个区间问题了：

> 给定若干段区间 $[l, r]$，每个区间有一个代价 $a_i$（对应原图的点权）。
>
> 还有一段 $[1, n]$ 的序列 $a$。
>
> 控制一个区间，表示可以对区间里的数任意加减。
> 
> 求出最少代价以及方案，不管 $a_i$ 是多少，总能将 $a$ 的所有数变为 $0$。

区间多次修改，单次查询，很容易想到差分。

每次相当于在差分数组 $c$ 上执行：$c_l$ 加 $x$，$c_{r + 1}$ 减 $x$。

并且显然有 $1 \le l, r \le n$，$2 \le r + 1 \le n + 1$（因为 $l$ 和 $r$ 是 dfs 序）。

换句话说，我们所能更改的数是 $c_1$ 到 $c_{n + 1}$，要想让所有 $c_i$（$1 \le i \le n$）为 $0$，则所有数都要移到 $c_{n + 1}$ 头上。

那么接下来就非常简单了：$[l, r]$ 对应着一条 $l \to r + 1$ 的边，边权为 $a_i$。求出最少边权和及方案，使得选择了这些边后，$(n + 1)$ 号点能与所有点连通。

然后跑一遍 kruskal 即可。事实上转化为区间这一步只是推导过程，实际代码只需要在求出区间 $[l, r]$ 时，直接连边即可。

在输出方案的时候注意：这里的方案是并集！也就是**全部**可能存在于最优方案的点。

这一点具体看代码。很容易理解。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define space putchar(' ')
#define endl putchar('\n')
using namespace std;
typedef long long LL;
typedef long double LD;
void fastio()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
int read()
{
	char op = getchar(); int x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(LL x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
const int N = 2e5 + 5;
int n, m, a[N];
struct zltAK
{
	int u, v, w, pos; //a[pos] = w
}e[N];
void zltakioi(int u, int v, int pos)
{
	e[++m].u = u, e[m].v = v;
	e[m].w = a[pos], e[m].pos = pos;
}
bool cmp(zltAK IOI, zltAK CTSC) {return IOI.w < CTSC.w;} //膜拜 @zlttql 
int fa[N]; //并查集 
void init() {for (int i = 1; i <= n+1; i++) fa[i] = i;}
int get(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = get(fa[x]);
}
struct Edge
{
	int now, nxt, w;
}edge[N << 1];
int head[N], cur;
void add(int u, int v)
{
	edge[++cur].now = v;
	edge[cur].nxt = head[u];
	head[u] = cur;
}
//dfnl[i] 和 dfnr[i] 表示叶节点 dfn 序，如果控制 i，可以更改 dfnl[i]~dfnr[i] 的全部对应叶节点。 
int dfnl[N], dfnr[N];
void dfs(int u, int fa)
{
	bool leaf = true;
	dfnl[u] = 2147483647;
	for (int i = head[u]; i; i = edge[i].nxt)
	{
		int v = edge[i].now;
		if (v == fa) continue;
		leaf = false, dfs(v, u);
		dfnl[u] = min(dfnl[u], dfnl[v]), dfnr[u] = max(dfnr[u], dfnr[v]);
	}
	if (leaf) dfnl[u] = dfnr[u] = ++cur;
	zltakioi(dfnl[u], dfnr[u] + 1, u); //建边，差分思想如上所述 
}
int tot;
bool ans[N];
LL kruskal()
{
	init(), sort(e+1, e+m+1, cmp);
	LL sum = 0;
	for (int l = 1; l <= n;)
	{
		int r;
		for (r = l; r + 1 <= n && e[r].w == e[r+1].w; r++); //这样 [l,r] 的 w 都是一样的
		
		for (int i = l; i <= r; i++) //记录答案并集，注意不能一边合并一边统计，显然会错误 
			if (get(e[i].u) != get(e[i].v))
				ans[e[i].pos] = true, tot++;
				
		for (int i = l; i <= r; i++) //真正的kruskal操作 
		{
			int fu = get(e[i].u), fv = get(e[i].v);
			if (fu == fv) continue;
			fa[fu] = fv, sum += e[i].w;
		}
		l = r + 1;
	}
	return sum;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i < n; i++)
	{
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	cur = 0, dfs(1, 0);
	write(kruskal()), space, write(tot), endl;
	for (int i = 1; i <= n; i++)
		if (ans[i])
			write(i), space;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：影辰 (赞：18)

沙发~~

# 题意简述

给你一棵有根树，定义叶子为度数为1的点。

你可以以$ w_x $的代价控制$x$点。选择控制之后可以给它的子树里的叶子加
上$t (t \in Z )$。

你要以最小的总代价使得：另一个人在叶子上任意放数，你都可以把它
们都变成0。

最后输出最小的总代价，以及有多少点可能被控制，以及每个可能被控制的点的编号

# 思路索引

首先，我们可以把所有的叶子节点按照 dfs序 抽象成一个序列

接下来，我们可以很神奇的发现，每一个点就对应着一个区间~~这不是废话吗~~

然后，选择某个区间后，我们就可以对它进行区间加的操作

既然是区间操作，肯定是不方便的，然后就很自然的想到了差分~~哪里自然了~~

若点$x$对应区间$[l,r]$，那么，我们控制点x，就等同于在$l$处$+t$,在$r+1$处$-t$(因此，我们需要虚构出一个新的叶子节点，以保证不会爆掉)

我们观察一下这个序列，发现如果原数组均为0，则差分数组也均为0

所以说，我们可以在$l$到$r+1$之间连一条边权为$w_x$的边，我们可以在这条边的一端加上一个数，而在另一端减去一个相同的数

我们发现，若所有叶子都联通，那么因为差分数组的和为0，所以我们必然能将每一个点都变成0

求一遍最小生成树即可

# 代码实现

```cpp
//``` 
#include<bits/stdc++.h>
#define ll long long
#define now edge[i].v
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
const int SZ=2e5+7;
ll ans;
int cnt;
int L,R;
int u,v;
int n,T;
int w[SZ];
int fa[SZ];
int sz[SZ];
bool vis[SZ];
int head[SZ];
bool f[SZ];
int l[SZ],r[SZ];
struct wxp{
    int v,nxt;
}edge[SZ<<1];
struct pb{
    int u,v,w,o;
}E[SZ];
bool cmp(pb p1,pb p2){
    return p1.w<p2.w;
}
int getfa(int x){
    return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void add(int u,int v){
    edge[++cnt]=(wxp){v,head[u]};
    head[u]=cnt;
}
void dfs(int x){
    sz[x]=1;
    vis[x]=1;
    for(int i=head[x];i;i=edge[i].nxt)
    if(!vis[now]){
        dfs(now);
        sz[x]+=sz[now];
        l[x]=min(l[x],l[now]);
        r[x]=max(r[x],r[now]);
    }
    if(sz[x]==1) l[x]=r[x]=++T;
    E[x]=(pb){l[x],r[x]+1,w[x],x};
}
int main(){
    scanf("%d",&n);
    rep(i,1,n) scanf("%d",&w[i]);
    rep(i,1,n-1){
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    memset(l,0x3f,sizeof(l));
    dfs(1);
    sort(E+1,E+n+1,cmp);
    rep(i,1,T+1) fa[i]=i;
    int sum=0;
    for(L=1;L<=n;L=R+1){
        R=L;
        while(E[R+1].w==E[L].w&&R<n) R++;
        rep(i,L,R){
            u=E[i].u,v=E[i].v;
            if(getfa(u)!=getfa(v)) f[E[i].o]=1,sum++;
        }
        rep(i,L,R){
            u=E[i].u,v=E[i].v;
            if(getfa(u)!=getfa(v)){
                ans+=1ll*E[i].w;
                fa[fa[u]]=fa[v];
            }
        }
    }
    printf("%I64d %d\n",ans,sum);
    rep(i,1,n) if(f[i]) printf("%d ",i);
} 
//```
```


---

## 作者：Tony2 (赞：13)

[题目描述](https://www.luogu.com.cn/problem/CF1120D)

先讲一下后面输出的“方案”：其实就是**所有最优方案**中可能被控制的节点编号，以及个数

很明显，这是一道树形dp题

那我们就来列~~玄学~~转移方程吧

首先，f[i][0]表示i节点可以把他的叶子变为相同（只能变为几种数，看它放了什么，最少一种）的最小代价，举个栗子：
![1.png](https://i.loli.net/2020/02/16/KUEWOfIb1GDqsYR.png)
有啥用呢？先往后看。

f[i][1]表示i节点可以把他的叶子**一起**变为**任意数**（包括0）的最小代价。

转移方程：

我们通过栗子1得到了这样一个转移方程：

f[i][0] = f[j][0] + f[k][1]

注意：j是i的所有儿子中的一个，k是除了j的所有i的儿子。

为什么可以这样做呢？因为所有k都可以变为任意数，自然也能变为j下面被放的数，这样不就都相同了吗？

当i下面的数都相同时，控制i是不是就可以将下面的数变为任意数了？

所以：

f[i][1] = f[j][1]

j是i的所有儿子节点。
很明显，i的所有儿子都能任意，自己也能任意。

f[i][1] = f[j][0] + f[k][1] + w[i]

注意：j是i的所有儿子中的一个，k是除了j的所有i的儿子。
当i的儿子其中一个是 _相同_ 时，其他不能是相同，否则无法保证所有数都相同。其他的儿子节点一定要任意，然后变成那个~~特例~~相同的儿子节点，再控制i，将所有相同的数变成任意数。

还是举个栗子吧：
![2.png](https://i.loli.net/2020/02/16/wJOjxR1iDNrXLm8.png)
很好懂吧？

ok，下面就处理这个~~变态~~方案了。

我们发现，上面说的那个~~特例~~相同的儿子节点是可以记录下来的，它要达到-f[j][1]+f[j][0]最小，其实就是**替换**了一个f[k][1]到f[j][0]（从1到0），只有最小才能保证f[i][0]最小。

还有，f[i][1]的第二种情况其实就是f[i][0]+w[i]，只要比较f[j][1]（j是i的所有儿子节点）和f[i][0]+w[i]就好了。

解释完了，就上结构体记录方案！！！

```cpp
struct msg{
	bool now_ct=0, all=0;
	vector<int> u;
}g[N][2];
```
now_ct表示当前要不要控制这个节点，就是当f[j][1]（j是i的所有儿子节点） <= f[i][0]+w[i]的时候。

all表示f[j][1]（j是i的所有儿子节点） == f[i][0]+w[i]，即两种转移方程都是最优解。

u是一个vector，记录所有可以达到最优解的~~特例~~相同的儿子节点。

## ok，上代码！！！（注释一起上！）

```cpp
#include <bits/stdc++.h>
#define add push_back
#define ll long long
using namespace std;
const int N = 200005;
int n;
ll w[N];//如题中的w
bool ans[N]/*最优解中可能被控制的点*/, vis[N][2]/*递归去重*/;
ll f[N][2];
struct msg{
	bool now_ct=0, all=0;
	vector<int> u;
}g[N][2];
vector<int> a[N];/*记录树*/
void dfs(int u, int fa){
	bool bo = 1;//记录自己是不是叶子节点
	ll k = 1e17;//记录可以达到最优解的相同的儿子节点的-f[i][1]+f[i][0]
	for (int i = 0; i < a[u].size(); i++){
		int v = a[u][i];
		if (v == fa) continue;
		dfs(v, u);
		f[u][0] += f[v][1];
		f[u][1] += f[v][1];
		if (f[v][0]-f[v][1] < k){//有更优策略
			g[u][0].u.clear();//清空假的相同的儿子节点
			g[u][0].u.add(v);//“我才是最优解！”
		}else if (f[v][0]-f[v][1] == k) g[u][0].u.add(v);//如上
		k = min(f[v][0]-f[v][1], k);//更新
		bo = 0;
	}
	if (bo){//如果自己是叶子节点
		f[u][0] = 0;//相同没有代价
		f[u][1] = w[u];//任意 控制自己就好
		g[u][1].now_ct = 1;//控制自己了
		return;
	}
	f[u][0] += k;//加上最优解的相同的儿子节点（变化值）
	if (f[u][0]+w[u] <= f[u][1]){
		g[u][1].now_ct = 1;
		g[u][1].u.assign(g[u][0].u.begin(), g[u][0].u.end());//把f[i][0]的信息拷过来
	}
	if (f[u][0]+w[u] == f[u][1]) g[u][1].all = 1;//两种方案都可行
	f[u][1] = min(f[u][0]+w[u], f[u][1]);//更新
}
void find_ans(int i, int j, int fa){
	if (vis[i][j]) return;//重复了
	if (g[i][j].now_ct) ans[i] = 1;//要控制i节点
	vis[i][j] = 1;
	if (!g[i][j].all){//如果只有f[i][0]+w[i]可行
		map<int, bool> can;//STL大法好（bitset会MLE）
		for (int _i = 0; _i < g[i][j].u.size(); _i++) can[g[i][j].u[_i]] = 1;//记录
		for (int _i = 0; _i < a[i].size(); _i++) if (a[i][_i] != fa){
			find_ans(a[i][_i], !can[a[i][_i]], i);
			if (g[i][j].u.size() > 1 && can[a[i][_i]]) find_ans(a[i][_i], 1, i);//卡了我3h！！！如果有多个“最优解”要都走一次1（控制）！因为另一个不控制“我”就要控制，也就是所有都要控制一次！
		}
	}else{
		for (int _i = 0; _i < a[i].size(); _i++) if (a[i][_i] != fa) find_ans(a[i][_i], 1, i);
		for (int _i = 0; _i < g[i][j].u.size(); _i++) if (g[i][j].u[_i] != fa) find_ans(g[i][j].u[_i], 0, i);//两种方案一起上！
	}
}
int main(){
//	freopen("test_file/in.txt", "r", stdin);
//	freopen("test_file/out.out", "w", stdout);
	memset(f, 0, sizeof(f));
	memset(ans, 0, sizeof(ans));
	memset(vis, 0, sizeof(vis));
    //输入
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++){
    	int u, v;
    	cin >> u >> v;
    	a[u].add(v);
    	a[v].add(u);
    } 
    //重点x1
    dfs(1, 0);
    cout << f[1][1] << ' ';
    //重点x2
    find_ans(1, 1, 0);
    int cnt = 0;
    for (int i = 1; i <= n; i++) if (ans[i]) cnt++;
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) if (ans[i]) cout << i << " ";
    cout << endl;
//    for (int i = 1; i <= n; i++){
//    	for (int j = 0; j < 2; j++){
//    		printf("%d %d # ", g[i][j].now_ct, g[i][j].all);
//    		for (int k = 0; k < g[i][j].u.size(); k++) cout << g[i][j].u[k] << ' ';
//    		cout << "| ";
//    	}
//    	cout << endl;
//    }
	return 0;//华丽的结束！
}
```

## 求管理员大大通过qwq，我的方法和第一篇题解不一样！

---

## 作者：ez_lcw (赞：11)

很巧妙的一种方法。

首先我们可以把叶子节点按 dfs 序抽象成一个序列，不妨设这个序列长 $k$。

那么控制一棵子树内的叶子节点的点权等同于控制序列一段区间的点权。

全体置零的要求和区间加的操作容易联想到差分数组，不妨设差分数组 $b_i=a_i-a_{i-1}$，$a_0=0$。

对于操作区间 $[l,r]$ 加 $x$，就可以看作是 $b_l$ 加 $x$，$b_{r+1}$ 减 $x$，那么我们就得新建出一个虚点 $k+1$。

对于要求全体置零，就可以看做是要求 $\forall i\in[1,k],b_i=0$。

发现每次操作后差分数组的总和不会变，所以为了达到要求，必须把所有的值转移到 $b_{k+1}$ 上去。

对于操作区间 $[l,r]$ 加 $x$，我们可以连边 $(l,r+1)$，边权为 $x$。

不难发现当且仅当两个点联通时，才能把一个点的 $b$ 值转移到另一个点上去，且代价为边权和（注意代价与 $b$ 值大小无关，所以这道题不是用网络流）。

所以题目的要求就是所有的点都要和 $k+1$ 联通，然后问最小代价。

那么这就是一个最小生成树能解决的事情了。

至于输出所有可能在最优方案中的点，也就是输出所有可能出现在最小生成树中的边，可以直接在 kruskal 的过程中判断一下就好了。~~（我差点写了最小生成树的树剖）~~

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 200010
#define ll long long

using namespace std;

struct Edge
{
	int u,v,w,id;
	Edge(){};
	Edge(int a,int b,int c,int d){u=a,v=b,w=c,id=d;}
}e[N];

int n,m,c[N],fa[N];
int cnt,head[N],nxt[N<<1],to[N<<1];
int idx,lp[N],rp[N],size[N];
bool vis[N];
int num;
ll ans;

void adde(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

void dfs(int u,int fa)
{
	bool leaf=true;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa) continue;
		leaf=0;
		dfs(v,u);
		if(!lp[u]) lp[u]=lp[v];
		rp[u]=rp[v];
	}
	if(leaf) lp[u]=rp[u]=++idx;
	e[++m]=Edge(lp[u],rp[u]+1,c[u],u);
}

bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}

int find(int x)
{
	return x==fa[x]?x:(fa[x]=find(fa[x]));
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		adde(u,v),adde(v,u);
	}
	dfs(1,0);
	sort(e+1,e+m+1,cmp);
	idx++;
	for(int i=1;i<=idx;i++) fa[i]=i;
	for(int l=1,r;l<=m;l=r+1)
	{
		r=l;
		while(r+1<=m&&e[r].w==e[r+1].w) r++;
		for(int i=l;i<=r;i++)
		{
			int a=find(e[i].u),b=find(e[i].v);
			if(a!=b)
			{
				num++;
				vis[e[i].id]=1;
			}
		}
		for(int i=l;i<=r;i++)
		{
			int a=find(e[i].u),b=find(e[i].v);
			if(a!=b)
			{
				fa[a]=b;
				ans+=e[i].w;
			}
		}
	}
	printf("%lld %d\n",ans,num);
	for(int i=1;i<=n;i++)
		if(vis[i]) printf("%d ",i);
	return 0;
}
```

---

## 作者：psoet (赞：4)

另一种思路？
### CF1120D Power Tree

从简单的情况出发往往是解决问题的一种优秀的策略。

先来看看菊花图的情况（1为根节点，其余为叶子）。容易发现，合法解即为控制所有的叶子或少控制一个叶子并控制根。

稍微推一推就会发现如下的性质。我们先定义一个叶子的**最近控制点**为离它最近的被控制的祖先。显然每个叶子都必须有最近控制点。

#### 性质一   方案合法当且仅当每个叶子的最近控制点两两不同

~~OIER管什么证明~~

必要性：如果两个叶子的最近控制点相同，则它们“并联”，只能被一起控制。

充分性：将所有控制点按深度从小到大排序，从前往后操作，则后面的操作不会影响前面。

#### 性质二   每棵子树中最多有一个叶子的最近控制点在子树外

由性质一可知两个叶子的LCA必定为它们的最近控制点的祖先。对于子树$u$ 中的两个叶子，如果它们的最优控制点都在子树$u$ 外，显然它们的lca为$u$或$u$的后代，这不行。

当然，只有一个叶子在子树外是可能的，

------

由上面的两个性质，状态及状态转移不难看出。（我们称子树被控制当且仅当其所有叶子的最近控制点都在其中。）令$d(u,1)$表示子树$u$被控制的最小费用，$d(u,0)$表示子树$u$没有被完全控制，**仅有一个节点的最优控制点在$u$之外的最小费用**。

然后就有：

$$d(u,1)=\min\{\sum_{v\in ch[u]}d(v,1), \sum_{v\in ch[u]} d(v,1) - \max_{v\in ch[u]}\{d(v,1)-d(v,0)\}+w[u]\}$$



$$d(u,0)=\min\{\sum_{v\in ch[u]}d(v,1),\sum_{v\in ch[u]}d(v,1)-\max_{v\in ch[u]}\{d(v,1)-d(v,0)\}\}$$

------

~~什么？你天真地以为这就是紫题的难度?~~

个人感觉这题的输出及其毒瘤……比较容易的实现方法：用bfs,在dp的过程中存一下转移（就是之前那个特殊的v），同时要进行很多特判……不妨具体见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int maxn=2e5+5;
int n,deg[maxn],w[maxn];
LL d[maxn][2];
vector<int> G[maxn];
vector<int> p[maxn][2];
void dfs(int u,int fa)
{
	if(deg[u]==1&&fa)
	{
		d[u][1]=w[u],d[u][0]=0;
		return;
	}
	LL tmp=0;
	for(int i=0,v;i<G[u].size();++i) if((v=G[u][i])!=fa)
	{
		dfs(v,u);
		tmp+=d[v][1];
	}
	d[u][1]=d[u][0]=tmp;
	for(int i=0,v;i<G[u].size();++i) if((v=G[u][i])!=fa)
	{
	    d[u][1]=min(d[u][1],tmp-d[v][1]+d[v][0]+w[u]),d[u][0]=min(d[u][0],tmp-d[v][1]+d[v][0]);
	}
	for(int i=0,v;i<G[u].size();++i) if((v=G[u][i])!=fa)
	{
		if(d[u][1]==tmp-d[v][1]+d[v][0]+w[u]) p[u][1].push_back(v);
		if(d[u][0]==tmp-d[v][1]+d[v][0]) p[u][0].push_back(v);
        //转移可能多于一种，用vector存
	}
}
bool chose[maxn],vis[maxn][2];
struct Node
{
	int u,fa,tp;
};
queue<Node> Q;
void bfs()
{
	Q.push((Node){1,0,1});
	while(!Q.empty())
	{
		int u=Q.front().u,fa=Q.front().fa,tp=Q.front().tp;
		Q.pop();
		if(deg[u]==1&&fa)
		{
			if(tp) chose[u]=1;
			continue;
		}
        //在这里重新做一遍……主要是要特判一些特殊的情况
		LL tmp=0;
		for(int i=0,v;i<G[u].size();++i) if((v=G[u][i])!=fa)
		{
			tmp+=d[v][1];
		}
		if(tmp==d[u][tp])//在这种情况下p不一定为空，而如果不进行这个特判可能会使后面原本可以作为d(v,1)的v被跳过
		{
			for(int i=0,v;i<G[u].size();++i) if((v=G[u][i])!=fa&&!vis[v][1]) vis[v][1]=1,Q.push((Node){v,u,1});
		}
		if(p[u][tp].size()==1)//它和之前的并不互斥
		{
			if(tp||w[u]==0) chose[u]=1;
			for(int i=0,v;i<G[u].size();++i) if((v=G[u][i])!=fa&&v!=p[u][tp][0]&&!vis[v][1])
			{
				 vis[v][1]=1;
				 Q.push((Node){v,u,1});
			}
			if(!vis[p[u][tp][0]][0]) vis[p[u][tp][0]][0]=1,Q.push((Node){p[u][tp][0],u,0}); 
		} else if(p[u][tp].size()>1){//在这种情况下，所有子节点都有可能作为d(v,1)加入
			if(tp||w[u]==0)chose[u]=1;
			for(int i=0,v;i<G[u].size();++i) if((v=G[u][i])!=fa&&!vis[v][1]) Q.push((Node){v,u,1});
			for(int i=0;i<p[u][tp].size();++i)
			{
				if(!vis[p[u][tp][i]][0]) vis[p[u][tp][i]][0]=1,Q.push((Node){p[u][tp][i],u,0});
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&w[i]);
	for(int i=1;i<n;++i)
	{
		int x,y;scanf("%d%d",&x,&y);
		G[x].push_back(y),G[y].push_back(x);
		++deg[x],++deg[y]; 
	}
	dfs(1,0);
	bfs();
	int tot=0;
	for(int i=1;i<=n;++i) if(chose[i]) ++tot;
	printf("%lld %d\n",d[1][1],tot);
	for(int i=1;i<=n;++i) if(chose[i]) printf("%d ",i);
	return 0;
 } 
```



---

## 作者：tommy0221 (赞：3)

[更棒的阅读体验](https://www.cnblogs.com/zzctommy/p/14066084.html)

[CF1120D Power Tree](https://www.luogu.com.cn/problem/CF1120D)

这题如果不要输出方案绝对没有2500。状态10分钟就开出来了，输出方案搞了2两个多小时。。。那个最小生成树解法太牛逼了，完全想不到，只能用树形dp了。

光靠题目所给的那个很像博弈的题面必然没法做，第一步先转化题面：对于每一个叶子找一个"控制"它的点，这个点在它到根的路径上，使得选出的点不重复且权值和最小。

显然对于每一个叶子必须且仅需一个点就可以把它控制成需要的权值。

然后是需要直觉的一步了，我也不知道我怎么想到的：一个以 $u$ 为根的子树**除 $u$ 外的部分**，**至多一个**叶子没有控制的节点，否则子树不合法。

如果有一叶子没被控制，那么我们选择 $u$ 即可，都被控制了就不用选了。

那么dp方程就呼之欲出了：

$dp[u][0]$ 表示：以 $u$ 为根的子树内，叶子个数等于选出的节点个数的最小代价

$dp[u][1]$ 表示：以 $u$ 为根的子树内，**不包括 $u$**，叶子个数等于选出的节点个数加一的最小代价。这里的不包括 $u$ 很重要，不然没法转移（或者说我不会转移）。

$dp[u][1]=(\sum dp[v][0])-\max\{dp[v][0]-dp[v][1] \}$ ，也就是说我们必须选择恰好一棵子树让它叶子个数等于选出节点个数加一。

$dp[u][0]=\max(\sum dp[v][0],dp[u][1]+w[u])$，要么不包括 $u$ 的地方少了一个，那么 $u$ 必须选。要么每一个子树都恰好选满。

最小代价就是 $dp[1][0]$

------------------------

然后就是输出方案了。其实不走弯路也还好，就是要想清楚，然后**大力乱搞**。

输出方案可以参考一下我的思路，**最好自己乱搞**，毕竟乱搞还是自己想比较清楚。

我们发现一个点可能可以取必须满足 $dp[u][0]=dp[u][1]+w[u]$ 。如果只取 $dp[u][1]$ 说明这个点没取，取这个点就必须从 $dp[u][1]$ 转移然后加上 $w[u]$ ，又要让这颗子树代价最小，那么 $dp[u][0]$ 就必须从 $dp[u][1]+w[u]$ 转移过来。

但是这样还不够（好像过不去样例），因为 $dp[u][0]$ 不一定可以转移到 $dp[1][0]$ ，所以我们还需要判断每一个状态 $dp[u][i]$ 是否可以转移到  $dp[1][0]$，我们再用一个数组 $can[i][j]$ 来记录这个。

再记一些辅助变量：

$g[u]$ 表示 $\max\{dp[v][0]-dp[v][1] \}$，那么 $dp[u][0]=(\sum dp[v][0])-g[u]$；

$num[u]$ 表示 $dp[u][0]$ 可以从多少个 $dp[v][1]$ 转移过来

$sum[u]$ 表示 $\sum dp[v][0]$

然后转移 $can$ ，主要思想就是判断 $v$ 是否只能从 $dp[v][0]$ 或 $dp[v][1]$ 转移上来。

+ 如果 $can[u][0]=1$ 

  + 转移到 $can[v][0]$

    + 如果 $num[u]$ 大于 $1$ ，那么 $can[v][0]$ 等于 $1$ ，因为它不必须从 $dp[u][1]$ 转移上去。

    + 如果 $g[u]\not= dp[v][0]-dp[v][1]$ ，那么 $can[v][0]$ 等于 $1$，因为 $dp[u][0]$ 根本不是从 $dp[v][1]$ 转移上去的，必然是从 $dp[v][0]$ 转移上去。

    + 如果 $sum[u]=dp[u][0]$ ，那么 $can[v][0]$ 等于 $1$ ，因为 $u$ 可以全部从 $dp[v][0]$ 转移上来。

  + 转移到 $can[v][1]$
 
    + 如果 $sum[u]-dp[v][0]+dp[v][1]+w[u]=dp[u][0]$ ，那么 $can[v][1]=1$ ，即强制从 $dp[v][1]$ 转移上来，看看是否改变最优解。

+ 如果 $can[u][1]=1$

  + 转移到 $can[v][0]$

    + 如果 $g[u]\not= dp[v][0]-dp[v][1]$ ，那么 $can[v][0]$ 等于 $1$ ，因为它根本不会转移到 $dp[u][1]$。

    + 如果 $num[u]>1$ ，那么 $can[v][0]$ 等于 $1$ ，因为 $dp[u][1]$ 有多种选择，$dp[v]$ 可以从 $0$ 转移上去。

  + 转移到 $can[v][1]$

    + 如果 $g[u]=dp[v][0]-dp[v][1]$ ，那么 $can[v][1]$ 等于 $1$ ，从上面的转移方程可以看出 $dp[u][1]$ 可以从 $dp[v][1]$ 转移上来。

~~调死我了，太乱搞了~~ 

而且为啥没有spj啊/fn，好好的 $O(n)$ 又因为输出变成了 $O(n\log n)$ ，和那种非常牛逼的最小生成树解法复杂度相同了。本来还以为“理论复杂度更优”的/kk


```cpp
//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N = 200005;
int n, w[N], deg[N], num[N];
vector <int> ans;
LL dp[N][2], sum[N], g[N];
int hed[N], et;
bool lef[N], can[N][2];
struct edge { int nx, to; }e[N << 1];
void adde(int u, int v) { e[++ et].nx = hed[u], e[et].to = v, hed[u] = et; }
void dfs(int u, int ft) {
	if (deg[u] == 1 && u != 1) {
		dp[u][0] = w[u], dp[u][1] = 0, lef[u] = 1;
		return;
	}
	LL mx = 0;
	for (int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if (v == ft) continue;
		dfs(v, u);
		sum[u] += dp[v][0];
		if(mx < dp[v][0] - dp[v][1]) mx = dp[v][0] - dp[v][1], g[u] = mx, num[u] = 1;
		else if (mx == dp[v][0] - dp[v][1]) ++ num[u];
	}
	dp[u][1] = sum[u] - mx;
	dp[u][0] = min(dp[u][1] + w[u], sum[u]);
}
void calc(int u, int ft) {
	if (can[u][0] && dp[u][0] == dp[u][1] + w[u]) ans.pb(u);
	for (int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if (v == ft) continue;
		if (can[u][0]) {
			if (sum[u] - dp[v][0] + dp[v][1] + w[u] == dp[u][0]) can[v][1] = 1;
			if (sum[u] == dp[u][0] || g[u] != dp[v][0] - dp[v][1] || num[u] > 1) can[v][0] = 1;
		}
		if (can[u][1]) {
			if (g[u] == dp[v][0] - dp[v][1]) can[v][1] = 1;
			if (g[u] != dp[v][0] - dp[v][1] || num[u] > 1) can[v][0] = 1;
		}
		calc(v, u);
	}
}
signed main() {
	n=read();
	rep (i, 1, n) w[i] = read();
	rep (i, 2, n) {
		int x = read(), y = read();
		adde(x, y), adde(y, x), ++ deg[x], ++ deg[y];
	}
	dfs(1, 0), can[1][0] = 1, can[1][1] = dp[1][0] == dp[1][1] + w[1], calc(1, 0);
	printf("%lld %d\n",dp[1][0], sz(ans));
	sort(ans.begin(), ans.end());
	rep(i, 0, sz(ans) - 1) printf("%d ", ans[i]);
	puts("");
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：2)

### Solve

求出该树每个**叶子结点**的 DFS 序，并记录每个结点的子树中叶子结点最大和最小的 DFS 序 $r_u$ 和 $l_u$。把所有的叶子结点单独拎出来，以它们的 DFS 序为下标，组成一个序列 $a$，下文中称叶子序列。对叶子序列构建差分序列 $c$。

对于一次控制，考虑对叶子序列的差分序列的影响，即 $c_{l_u}+x$，$c_{r_u+1}-x$。最坏情况下一定可以将 $c_{l_u}$ 或 $c_{r_u+1}$ 其中一个置为 $0$，最后的目的是将整个差分序列除了 $c_{n+1}$ 以外都为 $0$。

考虑对于一次可能的控制，连接一条 $l_u$ 到 $r_u+1$，边权为 $w_u$ 的无向边，可以发现，整个图的最小生成树就是所求答案。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, cur, cnt, w[200010], l[200010], r[200010], fa[400010];
bool b[200010];
vector<int> g[200010];
struct node {
	int u, v, w, d;
	node() {}
	node(int x, int y, int z, int s) {
		u = x, v = y, w = z, d = s;
	} 
	bool operator < (const node &y) const {
		return w < y.w;
	}
} e[400010];
void addedge(int u, int v, int w, int d) {
	e[++cnt] = node(u, v, w, d);
}
void dfs(int u, int fa) {
	l[u] = 1e18;
	bool flag = true;
	for (int i = 0; i < g[u].size(); i++) {
		if (g[u][i] == fa) continue;
		flag = false;
		dfs(g[u][i], u);
		l[u] = min(l[u], l[g[u][i]]), r[u] = max(r[u], r[g[u][i]]);
	}
	if (flag) l[u] = r[u] = ++cur;
	addedge(l[u], r[u] + 1, w[u], u);
}
int find(int u) {
	if (fa[u] == u) return u;
	else return fa[u] = find(fa[u]);
}
int kruskal() {
	sort(e + 1, e + cnt + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	int res = 0;
	for (int i = 1; i <= cnt; i++) {
		int lst = i, now = i;
		if (find(e[now].u) != find(e[now].v)) b[e[now].d] = 1;
		while (now < cnt && e[now + 1].w == e[lst].w) {
			now++;
			if (find(e[now].u) != find(e[now].v)) b[e[now].d] = 1;
		}
		for (int j = lst; j <= now; j++)
			if (find(e[j].u) != find(e[j].v)) {
				res += e[j].w;
				fa[find(e[j].u)] = find(e[j].v);
			}
		i = now;
	}
	return res;
}
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1, 0);
	cout << kruskal() << " ";
	int tmp = 0;
	for (int i = 1; i <= n; i++)
		if (b[i]) tmp++;
	cout << tmp << "\n";
	for (int i = 1; i <= n; i++)
		if (b[i]) cout << i << " ";
	return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：2)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16629268.html)  

[题目传送门](http://codeforces.com/problemset/problem/1120/D)  
### 题目大意
给定一棵 $n$ 个点的有根树，$1$ 为根。  
你可以选择花费 $w_u$ 的代价控制 $u$ 点。当一个点被控制时你可以选择给它的子树内的叶子的点权都加上一个值 $v$。你需要控制若干个点，使得花费的代价尽量少，无论怎样规定叶子的初始点权，都可以通过操作你选择的点来让所有叶子的点权清空。  
你需要输出代价和的最小值以及所有点，满足它存在于某一种最优选择中。
### 题目解析
显然我们如果按照 dfs 序对所有的叶子节点重标号，那么每一个点都对应的是一个区间。  
所以问题就转化成：给定一个序列，现在又 $n$ 个区间，对于一个区间可以花费代价 $w_i$ 然后将这个区间区间加、减任意一个数，使得序列初始值为任何值时，都能清空。  

这样就可以联想到一道题：给定一个序列，给出一些区间的和，询问每个给出区间的和是否会与前面的条件矛盾。 

其实两道题的解法是类似的。  
对于一个区间 $[l,r]$，操作的代价为 $w$，如果将整个序列差分那么就相当于在 $a_l$ 加上一个数，然后在 $a_{r+1}$ 减去这个数，显然就转化为图中节点 $l,r+1$ 两个点之间一条边权为 $w$ 的无向边。然后最后的代价就是最小生成树。  

这样就转化为求一张图中最小生成树的边权和以及可能在最小生成树里面的边。  
前者不难求出吗，主要的问题在于后者。  
其实这个问题很简单。我们考虑 Kruskal 的过程。  
如果我们当前处理到一条边，我们需要同时考虑边权与这条边相同的边是否能够加到最小生成树里面，如果可以加入就代表这条边可能出现在最小生成树中。统计完之后再依次把这些边能加入的都加入到最小生成树里面去就可以了。

算法复杂度：$O(n\log n)$

核心代码：
```cpp
int n,u,v,head[maxn],to[maxn<<1],nex[maxn<<1],w[maxn],kkk;
#define add(x,y) nex[++kkk]=head[x]; head[x]=kkk; to[kkk]=y
int minx[maxn],maxx[maxn],cnt;
void dfs(int x,int pre){
	int i; maxx[x]=-1; minx[x]=INF;
	for(i=head[x];i;i=nex[i]) if(to[i]!=pre){
		dfs(to[i],x); maxx[x]=mmax(maxx[x],maxx[to[i]]); minx[x]=mmin(minx[x],minx[to[i]]);
	} if(maxx[x]==-1) maxx[x]=minx[x]=++cnt; return;
}
struct JTZ{
	int num,l,r,w;
	bool operator < (const JTZ x) const {
		return this->w < x.w;
	}
}e[maxn];
int fa[maxn]; int getfa(int x){ if(fa[x]==x) return x; return fa[x]=getfa(fa[x]); }
int ans[maxn],top; ll sum;
int main(){
	n=read(); int i,j,k; for(i=1;i<=n;i++) w[i]=read();
	for(i=1;i<n;i++){ u=read(); v=read(); add(u,v); add(v,u); }
	dfs(1,-1); for(i=1;i<=n;i++) e[i].num=i,e[i].l=minx[i],e[i].r=maxx[i]+1,e[i].w=w[i];
	sort(e+1,e+n+1); for(i=1;i<=cnt+1;i++) fa[i]=i;
	for(i=1;i<=n;i=j+1){
		j=i; while(e[i].w==e[j+1].w&&j<n) j++;
		for(k=i;k<=j;k++){
			u=getfa(e[k].l); v=getfa(e[k].r);
			if(u!=v) ans[++top]=e[k].num;
		}
		for(k=i;k<=j;k++){
			u=getfa(e[k].l); v=getfa(e[k].r);
			if(u!=v) fa[u]=v,sum+=e[i].w;
		}
	}
	sort(ans+1,ans+top+1);
	print(sum),pc(' '),print(top),pc('\n');
	for(i=1;i<=top;i++) print(ans[i]),pc(" \n"[i==top]);
	return 0;
}
```

---

## 作者：yijan (赞：2)

### CF1120D Power Tree

为了可能更好的阅读体验，建议到 luogu 博客或者 [这里](https://www.yijan.co/cf1120d-power-tree/) 阅读。


首先这题有个非常显然的做法。考虑自深向浅放点，那么当决定在 $u$ 是否放点的时候子树内的叶子都被正好一个观察点覆盖或者只有一个没有被覆盖。否则是无法完成题目的条件的。所以我们可以 $dp[u][0/1]$ 表示 $u$ 子树内有 $0/1$ 个剩下的点做一次树形 dp。

可是还有一个更加优秀的做法。

我们考虑这个操作的本意其实是区间进行 + / - 。根据 NOIP 2018 的经验我们知道这个东西很多时候会转化成差分的 + 或者 - 。于是我们考虑把叶子提出来按照 dfs 序摆放。对于一次放东西操作，放下去后就是 区间内可以同时增加一个值，也就是区间前面的差分加后面的差分减。我们可以连一条从区间开头到结尾后一个位置的边，表示可以同时操作这俩地方（一个加一个减）。

我们考虑连出来的图：

- 它有 $c + 1$ 个节点（其中 $c$ 为叶子数），因为可能连向最后一个叶子后一个节点。

- 这个图没有重边和自环（想一想发现显然）

- 因为想要选择最少的边，所以我们希望选边形成一棵树。为什么呢？差分的变换是不会让总大小和变化的。我们最终希望的是能够把所有权值都堆到最后一个叶子后面的那个虚点上，否则就得到的一定不是一个全 $0$ 的叶子序列。

    于是选边的时候选出环来一定是不明智的，因为环上必然有一条边直到最后都不需要进行任何操作就可以完成把权值全部转移的目的（其他的点的权值向往外输的点通过一条链过去就好了），可以直接删掉这条边。

    同时，如果不联通一定不可取。如果不联通了，必然有些点向最后一个叶子后面的那个虚点没有路，永远过不去，就爆炸了。

    所以，最终选得到的一定就是这个图的最小生成树。

最后说一下输出答案。。这题不知道为啥要让你输出这种奇妙的东西，大概就是对每个权值分别判下哪些边可取再统一加入并查集就好了。。具体实现可以见代码。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n;
int A[MAXN] , deg[MAXN];
vi G[MAXN];

struct ed {
    int u , v , w , id;
} E[MAXN] ; int id;

int dfn[MAXN] , clo;
void dfs( int u , int fa ) {
    dfn[u] = clo + 1;
    if( u != 1 && deg[u] == 1 ) ++ clo;
    for( int v : G[u] ) if( v != fa ) dfs( v , u );
    E[++ id] = { dfn[u] , clo + 1 , A[u] , u };
}

bool cmp( ed u , ed v ) {
    return u.w < v.w;
}

int fa[MAXN];
int find( int x ) { return x == fa[x] ? x : fa[x] = find( fa[x] ); }

void solve() {
    cin >> n;
    rep( i , 1 , n ) scanf("%d",A + i);
    int u , v;
    rep( i , 2 , n ) scanf("%d%d",&u,&v) , G[u].pb( v ) , G[v].pb( u ) , ++ deg[u] , ++ deg[v];
    dfs( 1 , 1 );
    sort( E + 1 , E + 1 + n , cmp );
    rep( i , 1 , clo + 1 ) fa[i] = i;
    ll ans = 0;
    vi re;
    for( int i = 1 , j ; i <= n ; i = j ) {
        j = i;
        while( j != n + 1 && E[j].w == E[i].w ) {
            u = find( E[j].u ) , v = find( E[j].v );
            if( u != v ) re.pb( E[j].id );
            ++ j;
        }
        rep( k , i , j - 1 ) {
            u = find( E[k].u ) , v = find( E[k].v );
            if( u != v ) fa[u] = v , ans += E[k].w;
        }
    }
    cout << ans << ' ' << re.size() << endl;
    sort( all( re ) );
    for( int i : re ) printf("%d ",i);
}

signed main() {
//    freopen("input","r",stdin);
//    freopen("fuckout","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
```



---

## 作者：NinT_W (赞：1)

## 题意

> 给出一棵n个节点的树，每个节点有一个代价，你可以花费这个代价来使以其为根节点的子树内的叶子节点的权值同时增加v（可以为负数），花费最小代价，使其所有叶子节点权值都变为0，输出最小权值及所有可能在最优解内的点

## 思路

很巧妙的做法，也是钟神上课讲的

对叶子节点权值进行差分，那么每次对节点修改，相当于对一个节点可控制的叶子节点的dfs序的左端点加上 $v$，右端点$+1$的位置减去 $v$（毕竟是差分么），我们可以产生 $n$ 个区间 $[l,r+1]$ ，因为要清空权值，相当于把差分序列的权值也清空即可，可以看作对每个区间从 $l$ 到 $r+1$ 进行连边，然后把区间  $[l,r]$ 的权值转移到 $r+1$ ，最后把dfs序区间 $[1,n]$ 的权值全部转移到 $n+1$ 即可，那我们就要保证连边后所有区间是连通的，且代价最小，那么我们就可以对新产生的边求最小生成树，最小生成树的大小就是最小代价

然后再看所有可能在最优解内的点，这一点也是在保证连通的前提下进行的，而之所以是可能是因为可能含有边权相同的边，即大小相等的最小生成树有多种形成的方法，在kruskal求最小生成树的过程中就可以进行判断处理

AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<climits>
#include<string>
#include<cmath>
#include<algorithm>
#define int long long

using namespace std;

const int maxn=200010;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

bool ok[maxn];
int head[maxn],n,tot,cnt;
int w[maxn],fa[maxn],ans;
int dfn_l[maxn],dfn_r[maxn];

struct edge
{
	int to,next;
}e[maxn*2];

struct node
{
	int from,to,val,point;
}edg[maxn];

void add(int x,int y)
{
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void e_add(int x,int y,int p)
{
	edg[++tot].from=x,edg[tot].to=y;
	edg[tot].val=w[p],edg[tot].point=p;
}

void dfs(int x,int fa)
{
	bool check=true;dfn_l[x]=INT_MAX;
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==fa) continue;
		check=false;
		dfs(to,x);
		dfn_l[x]=min(dfn_l[x],dfn_l[to]);
		dfn_r[x]=max(dfn_r[x],dfn_r[to]);
	}
	if(check)
	{
		 dfn_l[x]=dfn_r[x]=++cnt;
	}
	e_add(dfn_l[x],dfn_r[x]+1,x);
}

int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

void merger(int x,int y)
{
	fa[x]=y;
}

bool cmp(node a,node b)
{
	return a.val<b.val;
}

void kruskal()
{
	for(int i=1;i<=n+1;i++)
	{
		fa[i]=i;
	}
	sort(edg+1,edg+n+1,cmp);
	int l,r;
	for(l=1;l<=n;l=r+1)
	{
		r=l;
		while(r<n && edg[r].val==edg[r+1].val) r++;
		for(int i=l;i<=r;i++)
		{
			int u=edg[i].from,v=edg[i].to;
			if(find(u)==find(v)) continue;
			cnt++,ok[edg[i].point]=true;
		}
		for(int i=l;i<=r;i++)
		{
			int u=find(edg[i].from);
			int v=find(edg[i].to);
			if(u==v) continue;
			merger(u,v);
			ans+=edg[i].val;
		}
	}
}

signed main()
{
	n=read();

	for(int i=1;i<=n;i++)
	{
		w[i]=read();
	}
	
	for(int i=1;i<n;i++)
	{
		int u=read();
		int v=read();
		add(u,v),add(v,u);
	}
	
	tot=0,dfs(1,0);
	
	cnt=0,kruskal();
	
	cout<<ans<<" "<<cnt<<endl;
	
	for(int i=1;i<=n;i++)
	{
		if(ok[i]) cout<<i<<" ";
	}

	return 0;
}
```


---

## 作者：Yuby (赞：1)


### CF1120D Power Tree

#### 题意

给定一棵 $n$ 个点的有根树，$1$ 为根。定义 $u$ 为叶子当且仅当它不是根且度数为 $1$。

你可以选择花费 $w_u$ 的代价控制 $u$ 点。当一个点被控制时你可以选择给它的子树内的叶子的点权都加上一个值 $v$ 。你需要控制若干个点，使得花费的代价尽量少，无论怎样规定叶子的初始点权，都可以通过操作你选择的点来让所有叶子的点权清空。你需要输出代价和的最小值以及所有点，满足它存在于某一种最优选择中。还可以输出方案数。

$n\le 2\times 10^5$。模拟赛时被加强到 $2\times 10^6$。

#### 题解

模拟赛场上切了 2500，虽然水的离谱，还是写一篇题解吧。

题意转化为：给每个节点选择一个祖先（或者自己）对于点 $u$，其子树的叶子最多只能有一个还没有选择，求最小代价即方案，方案数。模拟赛的时候出题人还要输出方案数。

那么设 $dp_{u,1/0}$ 表示 $u$ 的子树内有 $1/0$ 个没有选择的。转移：设 $sum_u=\sum\limits_{v\in son_u}dp_{u,1}$。

$dp_{u,0}=\min\limits_{v\in son_u} dp_{v,0}+sum_u-dp_{v,1}$。

$dp_{u,1}=\min\limits_{v\in son_u} \min(sum_u,dp_{v,0}+a_u+sum_u-dp_{v,1})$。

对于可以在最优方案中的点，直接再搜一遍判断从哪里转移过就行。方案数可以跟着一起 $dp$ 更简单，略。

复杂度 $O(n)$。

```cpp
const ll MAXN=2e6+7;
ll n,a[MAXN],dp[MAXN][2];
bitset<MAXN>vis;
vector<ll>tree[MAXN],P;
void dfs(ll u,ll fa)
{
	if(tree[u].size()==1&&u!=1)
	{
		dp[u][0]=0;dp[u][1]=a[u];
		return ;
	}
	ll sum=0;
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		dfs(v,u);
		sum+=dp[v][1];
	}
	dp[u][1]=sum;
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		dp[u][0]=min(dp[u][0],dp[v][0]+sum-dp[v][1]);
		dp[u][1]=min(dp[u][1],sum-dp[v][1]+dp[v][0]+a[u]);
	}
}
bool mp[MAXN][2];
void dfs1(ll u,ll fa,ll op)
{
	if(mp[u][op])return ;
	mp[u][op]=1;
	if(tree[u].size()==1&&u!=1)
	{
		if(op)P.push_back(u);
		return ;
	}
	ll sum=0;
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		sum+=dp[v][1];vis[v]=0;
	}
	if(op==0)
	{
		ll cnt=0;
		for(ll i=0;i<tree[u].size();i++)
		{
			ll v=tree[u][i];
			if(v==fa)continue;
			if(dp[u][0]==dp[v][0]+sum-dp[v][1])
			{
				cnt++;
				vis[v]=1;
			}
		}
		for(ll i=0;i<tree[u].size();i++)
		{
			ll v=tree[u][i];
			if(v==fa)continue;
			if(vis[v])dfs1(v,u,0);
			if(cnt>1)dfs1(v,u,1);
			else if(cnt==1&&!vis[v])dfs1(v,u,1);
		}
		return ;
	}
	if(dp[u][1]==sum)
	{
		for(ll i=0;i<tree[u].size();i++)
		{
			ll v=tree[u][i];
			if(v==fa)continue;
			dfs1(v,u,1);
		}
	}
	ll cnt=0;
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		if(dp[u][1]==sum-dp[v][1]+dp[v][0]+a[u])
		{
			cnt++;
			vis[v]=1;
			dfs1(v,u,0);
		}
	}
	for(ll i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		if(v==fa)continue;
		if(vis[v])dfs1(v,u,0);
		if(cnt>1)dfs1(v,u,1);
		else if(cnt==1&&!vis[v])dfs1(v,u,1);
	}
	if(cnt)P.push_back(u);
	return ;
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read();
    for(ll i=1;i<=n;i++)a[i]=read();
    for(ll i=1;i<n;i++)
    {
    	ll u=read(),v=read();
    	tree[u].push_back(v);
    	tree[v].push_back(u);
	}
	for(ll i=1;i<=n;i++)dp[i][0]=dp[i][1]=LLINF;
	dfs(1,0);dfs1(1,0,1);
	sort(P.begin(),P.end());P.resize(unique(P.begin(),P.end())-P.begin());
	write(dp[1][1]),pc(32),write(P.size()),pc(10);
	for(ll i=0;i<P.size();i++)write(P[i]),pc(32);
	return 0;
}
```



---

## 作者：FutaRimeWoawaSete (赞：1)

~~进我的收藏夹吃土去吧~~              

感觉转化的很好，主要是也能树 dp 吧还是只评了 $2500$。

自己做的时候猜测一个点应该要转化成连边关系但是还是没想到差分……          

首先树上 dfn 序对于叶子节点重排成一个有序序列，然后选一个点就相当于区间加一个数，这个比较套路就不说了。               

接着一个比较优秀的性质就是你发现一个长为 $n$ 的序列全为 $0$ 等价为原序列的差分数组值全为 $0$ 但要除开第 $n + 1$ 位的值，然后区间加就是选择区间的差分数组左右端点左端点加右端点减。                 

令差分数组为 $c$，那么相当于现在所有的 $i \in [1 , n],c_i$ 值要往 $c_{n + 1}$ 值转移，比较好的是你可以自己指定加的值。           

我们考虑将“加值”这个操作看成“转移值”，那么我们只需要一个合理的转移顺序就可以保证不管你怎么给值我最后都可以把 $c$ 数组的值都转移到 $c_{n + 1}$ 上面去。           

不难发现树从底向上即是一种合法的转移顺序，所以对于原来的差分数组左端点加右端点减就可以看成连一条有边权的边，那么现在在所有的边里面将 $n + 1$ 个点连接成一棵树然后令 $n + 1$ 为根就好了，到此问题终于转化成了最小生成树。              

当然此题一个难点在于输出总方案的并。用树上 dp 虽然思想简单做问题以时也及其好写但是在处理问题二就显得很棘手，而用最小生成树就发现问题二变得很简单。将边权相同的边拎出来，那么只要之前的所有情况里没有连起来的连通块现在你不论怎么连只要保证能连满不漏边就行，这个就拿出来多问一遍就好了。          

时间复杂度 $O(n \log n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,m,val[Len],head[Len],cnt,dfn[Len],tot,L[Len],R[Len],Print[Len],num;
long long ans;
bool chs[Len];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
struct Node
{
	int x,y,z,w;
	Node(){x = y = z = w = 0;}
	Node(int X,int Y,int Z,int W){x = X , y = Y , z = Z , w = W;}
}Edge[Len << 1];
bool cmp(Node x,Node y){return x.w < y.w;}
void dfs(int x,int f)
{
	bool flag = 0;L[x] = 1e9 , R[x] = 0;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs(to , x);
		L[x] = min(L[x] , L[to]);
		R[x] = max(R[x] , R[to]);
		flag |= 1;	
	}	
	if(!flag) L[x] = R[x] = dfn[x] = ++ tot;
	Edge[++ m] = Node(L[x] , R[x] + 1 , x , val[x]);
}
int fa[Len << 2];
void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i;}
int findSet(int x){return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);}
void unionSet(int x,int y)
{
	int u = findSet(x) , v = findSet(y);
	if(u == v) return;
	fa[v] = u;
}
int main()
{
	scanf("%d",&n);for(int i = 1 ; i <= n ; i ++) scanf("%d",&val[i]);
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
	}
	dfs(1 , 0);sort(Edge + 1 , Edge + 1 + m , cmp);
	int l , r;
	makeSet(tot + 1);
	for(int i = 1 ; i <= m ; i = r + 1)
	{
		l = r = i;
		while(r + 1 <= m && Edge[r + 1].w == Edge[l].w) r ++;
		for(int j = l ; j <= r ; j ++) 
		{
			int u = findSet(Edge[j].x) , v = findSet(Edge[j].y);
			if(u == v) continue;
			Print[++ num] = Edge[j].z;
		}
		for(int j = l ; j <= r ; j ++)
		{
			int u = findSet(Edge[j].x) , v = findSet(Edge[j].y);
			if(u == v) continue;
			unionSet(u , v);
			ans += Edge[j].w;
		}
	}
	sort(Print + 1 , Print + 1 + num);
	printf("%lld %d\n",ans,num);
	for(int i = 1 ; i <= num ; i ++) printf("%d ",Print[i]);
	return 0;
}
```

---

## 作者：caidzh (赞：1)

考虑先跑出一个只包含叶子结点的 dfs 序

然后考虑把这些叶子结点单独取出成一条链，此时问题转化为，有$n$种操作，每种操作可以同时给$[l,r]$这个区间中的数加上一个数，选取一些操作，问最后使得所有数都可以等于$0$的最小代价

这个问题有一个非常精妙的解法：在链最后创建一个虚点，对于第$i$个操作，给$l_i$和$r_i+1$两个点连上一条边权为$w_i$的边，对这个图求一棵最小生成树即为答案

为什么？可以这样考虑：由于所有点的值为$0$，所以其差分数组也都为$0$

把操作视为在差分数组的$l_i$加上数$x$，在$r_i+1$减去数$x$，由于之前的差分数组肯定存在不为$0$的构造方式，所以我们必须把所有的差分值都转移到**虚点的位置**

而上面的边的含义是差分值的转移，所以充要条件是：每个点都可以通过选择的有向边到达虚点

由于边都是从前往后连的，所以有向边可以视为无向边，最后必然形成了一棵以虚点为根的树，最小代价为最小生成树大小

这个题还需要输出所有存在于一种最优解的点，这个可以考虑对于所有权值相同的边，看它能不能加入最小生成树决定
```cpp
const int maxn=200010,mod=998244353;
int n,w[maxn];vector<int>g[maxn];
int L[maxn],R[maxn],cnt;
void dfs(int x,int fa){
	if(g[x].size()==1&&fa){
		L[x]=++cnt;R[x]=cnt;
	}else L[x]=inf,R[x]=0;
	for(int i=0;i<g[x].size();i++){
		int v=g[x][i];if(v==fa)continue;dfs(v,x);
		L[x]=min(L[x],L[v]);R[x]=max(R[x],R[v]);
	}
}int fa[maxn],tot;ll ans;
int Find(int x){
	return fa[x]==x?x:fa[x]=Find(fa[x]);
}int a[maxn],len;
struct Edge{
	int u,v,w,id;
}edge[maxn];
bool cmp(Edge x,Edge y){
	return x.w<y.w;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		w[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		g[x].pb(y);g[y].pb(x);
	}dfs(1,0);
	for(int i=1;i<=n;i++)R[i]++;
	for(int i=1;i<=n+1;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		edge[i].u=L[i];edge[i].v=R[i];edge[i].w=w[i];edge[i].id=i;
	}sort(edge+1,edge+n+1,cmp);edge[n+1].w=inf;int pl,lst=0;
	while(lst!=n){
		pl=lst+1;
		while(edge[pl+1].w==edge[pl].w)pl++;
		for(int i=lst+1;i<=pl;i++){
			int u=Find(edge[i].u),v=Find(edge[i].v);
			if(u!=v)a[++len]=edge[i].id;
		}
		for(int i=lst+1;i<=pl;i++){
			int u=Find(edge[i].u),v=Find(edge[i].v);
			if(u!=v){
				fa[u]=v;ans+=edge[i].w;
			}
		}lst=pl;
	}
	cout<<ans<<" "<<len<<endl;sort(a+1,a+len+1);
	for(int i=1;i<=len;i++)cout<<a[i]<<" ";return 0;
}
```


---

