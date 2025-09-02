# 水筒

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_e



# 题解

## 作者：_zy_ (赞：14)

## [题目传送门](https://www.luogu.com.cn/problem/AT1221)

题目大意：

对于一个矩阵，求$a$到$b$两点间城市之间最大的距离.

~~很容易~~想到把矩阵扔到图上。

~~很容易~~想到把图扔到树上。

~~很容易~~想到用倍增处理最大值。

-  如何将矩阵转化为一个图？？

    我们可以跑一遍$bfs$。（类似于双源$bf$s跑多源$bfs$）

   先将读入的点都入队，然后将其拓展，我们知道$JOI$君他并不傻，肯定不会绕来绕去，于是联通块最先相交的点肯定是则正常的道路$zzz$。

   用结构体来存储起点终点和边权(~~因为我们一会要跑最大生成树~~)

```cpp
void bfs()
{
	while(!q.empty()) {
		E now=q.front(); 
		q.pop();
		int x=now.x;
		int y=now.y;
		v[x][y]=1;
		for(int i=1;i<=4;i++) {
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]=='#'||v[xx][yy])	continue;
			v[x][y]=1;
			if(!b[xx][yy]) {
				b[xx][yy]=b[x][y];
				dis[xx][yy]=dis[x][y]+1;
				q.push((E){xx,yy});
				continue;
			} 
			if(b[xx][yy]!=b[x][y]) 
			{
				e[++cnt].from=b[xx][yy];
				e[cnt].to=b[x][y];
				e[cnt].w=dis[xx][yy]+dis[x][y];
			}
		}
	}
}
```

- 如何把图扔到树上？？

	$MST$

	既然想要使水壶最小，那些比较大的边就尽量别走嘛，贪心一下。

	就通过 $Kruskal$ 处理出来最小生成树。

```cpp
for(int i=1;i<=p;i++)	fa[i]=i;
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=cnt;i++) 
	{
		int fx=find(e[i].from);
		int fy=find(e[i].to);
		if(fx==fy)	continue;
		fa[fy]=fx;
		k++;
		ins(e[i].from,e[i].to,e[i].w);
		ins(e[i].to,e[i].from,e[i].w);
		if(k==p-1)	break;
	}
```

- 如何倍增处理最大边权？？

	记录 $f[u][i]$表示从u跳$2^{i}$到达的点。

	$t[u][i]$就是从u到$2^{i}$的最大边权了。
    
    就像跑 $LCA$ 一样跑最大边权就可以了。

```cpp
vid dfs(int x,int father,int deep)
{
	dep[x]=deep; used[x]=1;
	for(int i=fir[x];i;i=nex[i]) {
		int p=poi[i];
		if(p==father)	continue;
		f[p][0]=x;
		t[p][0]=val[i];
		dfs(p,x,deep+1);
	}
}
void Dp() {
	for(int j=1;j<=19;j++)
	for(int i=1;i<=p;i++)
		f[i][j]=f[f[i][j-1]][j-1],
		t[i][j]=max(t[i][j-1],t[f[i][j-1]][j-1]);
}
int Lca(int x,int y)
{
	if(find(fa[x])!=find(fa[y])) return -1;
	int ans=0;
	if(dep[x]<dep[y])	swap(x,y);
	for(int i=18;i>=0;i--)	
		if(dep[f[x][i]]>=dep[y])
			ans=max(ans,t[x][i]),x=f[x][i];
	if(x==y)	return ans;
	for(int i=19;i>=0;i--)
	{
		if(f[x][i]==f[y][i]||!f[x][i]||!f[y][i])	continue;
		ans=max(ans,max(t[x][i],t[y][i]));
		x=f[x][i]; y=f[y][i];
	}
	ans=max(ans,max(t[x][0],t[y][0]));
	return ans;
}
```
## 注意事项：

1. 跑出来可能是个森林，于是要从里面每一棵树上跑$dfs$。

2. 先取$max$再跳，不然会有没取到最大值的边。

**关于$-1$：不在一个并查集里面。**

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define N 5000010
#define M 10010
using namespace std;
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int n,m,p,T,sum,cnt,k;
char a[M][M];
int dis[M][M],b[M][M],fa[N];
int fir[N],nex[N],poi[N],val[N];
int dep[N],f[N][20],t[N][20];
bool v[M][M],used[N];
const int dx[]={0,1,-1,0,0}; const int dy[]={0,0,0,1,-1};
struct zy {
	int from,to;
	int w;
}e[N];
struct E {
	int x,y;
}que[N];
queue<E > q;
void ins(int x,int y,int z) {
	nex[++sum]=fir[x];
	poi[sum]=y;
	val[sum]=z;
	fir[x]=sum;
}
void bfs()
{
	while(!q.empty()) {
		E now=q.front(); 
		q.pop();
		int x=now.x;
		int y=now.y;
		v[x][y]=1;
		for(int i=1;i<=4;i++) {
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]=='#'||v[xx][yy])	continue;
			v[x][y]=1;
			if(!b[xx][yy]) {
				b[xx][yy]=b[x][y];
				dis[xx][yy]=dis[x][y]+1;
				q.push((E){xx,yy});
				continue;
			} 
			if(b[xx][yy]!=b[x][y]) 
			{
				e[++cnt].from=b[xx][yy];
				e[cnt].to=b[x][y];
				e[cnt].w=dis[xx][yy]+dis[x][y];
			}
		}
	}
}
bool cmp(zy x,zy y) {
	return x.w<y.w;
}
int find(int x) {
	if(fa[x]!=x)	return fa[x]=find(fa[x]);
	return fa[x];
}
void dfs(int x,int father,int deep)
{
	dep[x]=deep; used[x]=1;
	for(int i=fir[x];i;i=nex[i]) {
		int p=poi[i];
		if(p==father)	continue;
		f[p][0]=x;
		t[p][0]=val[i];
		dfs(p,x,deep+1);
	}
}
void Dp() {
	for(int j=1;j<=19;j++)
	for(int i=1;i<=p;i++)
		f[i][j]=f[f[i][j-1]][j-1],
		t[i][j]=max(t[i][j-1],t[f[i][j-1]][j-1]);
}
int Lca(int x,int y)
{
	if(find(fa[x])!=find(fa[y])) return -1;
	int ans=0;
	if(dep[x]<dep[y])	swap(x,y);
	for(int i=18;i>=0;i--)	
		if(dep[f[x][i]]>=dep[y])
			ans=max(ans,t[x][i]),x=f[x][i];
	if(x==y)	return ans;
	for(int i=19;i>=0;i--)
	{
		if(f[x][i]==f[y][i]||!f[x][i]||!f[y][i])	continue;
		ans=max(ans,max(t[x][i],t[y][i]));
		x=f[x][i]; y=f[y][i];
	}
	ans=max(ans,max(t[x][0],t[y][0]));
	return ans;
}
int main()
{
	n=re(); m=re(); p=re(); T=re();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)	cin>>a[i][j];
	for(int i=1;i<=p;i++) {
		int X,Y;
		X=re(); Y=re();
		b[X][Y]=i;
		q.push((E){X,Y});
	}
	bfs();
	for(int i=1;i<=p;i++)	fa[i]=i;
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=cnt;i++) 
	{
		int fx=find(e[i].from);
		int fy=find(e[i].to);
		if(fx==fy)	continue;
		fa[fy]=fx;
		k++;
		ins(e[i].from,e[i].to,e[i].w);
		ins(e[i].to,e[i].from,e[i].w);
		if(k==p-1)	break;
	}
	for(int i=1;i<=p;i++)
		if(!used[i])	dfs(i,0,1);
	Dp();
	while(T--) {
		int x,y;
		x=re(); y=re();
		printf("%d\n",Lca(x,y));
	}
	return 0;
}
```
另：

可以先做一下[此题](https://www.luogu.com.cn/problem/P1967)。

----

如有不妥或者是不明白的，欢迎指出！

望管理大大通过。

---

## 作者：Shunpower (赞：5)

考虑一个 naive 的想法，我们把整个完全图建出来，两两建筑物之间的边权为它们的最短路径长度。然后我们希望求得一个最小的边权 $x$ 满足只考虑 $\le x$ 的边使得 $S,T$ 连通。

这就是货车运输。根据 truck's trick，我们造一个最小生成树，然后考虑最小生成树上 $(S,T)$ 路径的最大边权即可。容易用最小生成树定义证明不可能有更小的最大边权。

但是我们不可能把完全图造出来。你发现完全图上有极多废边，这种 $x\to y$ 的边之所以废就是因为 $x\to z$ 和 $z\to y$ 都比它还短，那么 $x\to y$ 就一定不会被选择到最小生成树里面。如此递归下去，我们可以把废边拆成若干条有用边。

考虑有用边满足什么性质。这里薅一张 JOI 的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/m63ri08l.png)

我们对网格图进行多源 BFS 染色，这样可以求出来每个点最近的建筑物在哪里。有一个很强的性质可以证明：任何一条有用边在网格图上的路径都不会经过两种以上颜色。

> Proof.
> 考虑 $x\to z\to y$，其中 $x,y,z$ 这三者颜色互不相同，且 $x,y$ 是建筑物。令 $z'$ 为 $z$ 的颜色对应的建筑物，可以证明：
> - $x\to z'$ 的距离小于 $x\to z\to y$。因为 $z$ 这个点属于 $z'$ 的颜色，所以 $z\to y$ 肯定比 $z\to z'$ 远，所以 $x\to z\to z'$ 的距离小于 $x\to z\to y$。
> - $z'\to y$ 的距离小于 $x\to z\to y$。因为 $z$ 这个点属于 $z'$ 的颜色，所以 $z'\to z$ 肯定比 $x\to z$ 近，所以 $z'\to z\to y$ 的距离小于 $x\to z\to y$。
>
> 所以，把废边 $x\to y$ 拆成 $x\to z'$ 和 $z'\to y$ 就比原来好。一直拆下去就可以拆出有用边，而所有有用边必然满足不会经过两种以上的颜色。

考虑到任意一条边必然至少会经过两种颜色（毕竟必须要连接两个不同建筑物），所以任何一条有用边都会恰好经过两种颜色。而两种颜色必然有一个分界点。

所以做法就呼之欲出了。我们直接跑一遍多源 BFS 给网格图染色，在颜色分界点处统计加边，这样最多只会有四倍网格图大小的边，但实际上远远跑不满。弄完之后随便拉一个最小生成树算法像完全图一样做就行，稠密图推荐使用 Prim，但是 Kruskal 也过了。

---

## 作者：STrAduts (赞：4)

首先，我们来证明一个性质：

对于一个图，其中任意两个点间的路径我们记为 $p$。每个路径上最大的权值为 $q$。则满足 $q$ 最小的路径 $p_0$ 一定在原图的最小生成树（森林）上。

我们设这颗最小生成树（森林）为 $T$，两点间路径 $p$ 上的最大值为 $\max(p)$。假设 $p$ 不是 $T$ 上的路径，则一定存在一条路径 $p_1$ 使得 $\max(p_1)$ 比 $\max(p)$ 更小。我们考虑将 $p_1$ 加入 $T$。

将这个路径加入后，一定会在原树上出现一个环，而这个环上的最大值一定为 $\max(p)$。

你会惊讶的发现，如果删掉那条权值为 $\max(p)$ 的边，你会得到一颗新的树，而明显这才是真正的最小生成树。

推出矛盾！原性质得证。

那么我们现在得到了这样一个性质，抽象概括出来也就是说我们的答案一定在原图的 **最小生成树（森林）** 上，因为树上两点路径唯一，所以答案就是两点间路径上的最大边。这显然可以 **树上倍增** 解决。

最后讲讲预处理，也就是如何去建图。很显然，暴力 **BFS** 是不可取的。于是我们考虑更高效的预处理方法。

其实还是 BFS，类双向 BFS。我们首先将所有的城市装入 BFS 的队列，然后同时开始进行扩展。对一个点我们打两种标记：$flag$ 表示这个点是由哪个城市第一次走到的，$ans$ 表示第一个走到这个点的城市到它的距离。那么对于当前扩展到的节点，它的标记有两种情况。

假设上一个点为 $v$，当前点为 $u$。

* $ans_u$ 里没有值，也就是说当前是第一次走到，更新 $flag_u$ 继续扩展即可。

```cpp
ans[u] = ans[v] + 1;
flag[u] = flag[v];
```

* ans 里有值，也就是说之前有城市扩展到了，那么就可以将当前这个城市和之前扩展的城市进行连边，权值就是上一个点和这个点的 $ans$ 之和。

```cpp
Add_Edge(flag[u], flag[v], ans[u] + ans[v]);
```

然后按正常 BFS 继续遍历即可，完结撒花。

（代码略显冗长，仅供参考。

```cpp
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int read() {
    int k = 1, x = 0;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = (x << 3) + (x << 1) + s - '0';
        s = getchar();
    }
    return x * k;
}

void write(int x) {
    if(x < 0) {
    	putchar('-');
		x = -x;
    }
    if(x > 9)
		write(x / 10);
    putchar(x % 10 + '0');
}

void print(int x, char s) {
	write(x);
	putchar(s);
}

int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }
void Swap(int &X, int &Y) {
    int t = X;
    X = Y;
    Y = t;
}

const int MAXN = 2e3 + 5;
const int MAXL = 4e6 + 5;
int mp[MAXN][MAXN], h, w, p;
char s[MAXN];

struct node {
    int x, y;
    node() {}
    node(int X, int Y) {
        x = X;
        y = Y;
    }
};

struct edge {
    int u, v, w;
    edge() {}
    edge(int U, int V, int W) {
        u = U;
        v = V;
        w = W;
    }
} e[MAXL];
int len = 0;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int ans[MAXN][MAXN], flag[MAXN][MAXN];
queue<node> q;

void bfs() {
    while (!q.empty()) {
        node now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int cx = now.x + dx[i];
            int cy = now.y + dy[i];
            if (cx < 1 || cx > h)
                continue;
            if (cy < 1 || cy > w)
                continue;
            if (mp[cx][cy])
                continue;
            if (ans[cx][cy] == -1) {
                ans[cx][cy] = ans[now.x][now.y] + 1;
                flag[cx][cy] = flag[now.x][now.y];
                q.push(node(cx, cy));
            } else if (flag[cx][cy] != flag[now.x][now.y])
                e[++len] = edge(flag[now.x][now.y], flag[cx][cy], ans[cx][cy] + ans[now.x][now.y]);
        }
    }
}

struct data {
    int ma, fa;
    data() {}
    data(int Ma, int Fa) {
        ma = Ma;
        fa = Fa;
    }
} f[MAXL][25];

int fa[MAXL];

bool cmp(edge x, edge y) { return x.w < y.w; }

void Make_Set(int n) {
    for (int i = 1; i <= n; i++) fa[i] = i;
}

int Find_Set(int x) {
    if (fa[x] == x)
        return x;
    return fa[x] = Find_Set(fa[x]);
}

struct graph {
    int v, w;
    graph() {}
    graph(int V, int W) {
        v = V;
        w = W;
    }
};

vector<graph> g[MAXL];

void Add_Edge(int u, int v, int w) {
    g[u].push_back(graph(v, w));
    g[v].push_back(graph(u, w));
}

void kruskal() {
    Make_Set(p);
    sort(e + 1, e + len + 1, cmp);
    for (int i = 1; i <= len; i++) {
        int S = Find_Set(e[i].u), E = Find_Set(e[i].v);
        if (S == E)
            continue;
        Add_Edge(S, E, e[i].w);
        fa[S] = E;
    }
}

int dep[MAXL];

void dfs(int x, int fa) {
    for (int i = 0; i < g[x].size(); i++) {
        int v = g[x][i].v;
        if (v == fa)
            continue;
        dep[v] = dep[x] + 1;
        f[v][0].fa = x;
        f[v][0].ma = g[x][i].w;
        for (int j = 0; j <= 20; j++) {
            f[v][j + 1].fa = f[f[v][j].fa][j].fa;
            f[v][j + 1].ma = Max(f[v][j].ma, f[f[v][j].fa][j].ma);
        }
        dfs(v, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        Swap(x, y);
    int ans = 0;
    for (int i = 20; i >= 0; i--)
        if (dep[f[x][i].fa] >= dep[y]) {
            ans = Max(ans, f[x][i].ma);
            x = f[x][i].fa;
        }
    if (x == y)
        return ans;
    for (int i = 20; i >= 0; i--)
        if (f[x][i].fa != f[y][i].fa) {
            ans = Max(ans, f[x][i].ma);
            ans = Max(ans, f[y][i].ma);
            x = f[x][i].fa;
            y = f[y][i].fa;
        }
    ans = Max(ans, f[x][0].ma);
    ans = Max(ans, f[y][0].ma);
    return ans;
}

int main() {
//    freopen("04-04.in", "r", stdin);
//    freopen("ans1.out", "w", stdout);
    int Q;
    h = read(), w = read(), p = read(), Q = read();
    for (int i = 1; i <= h; i++) {
        scanf("%s", s + 1);
        for (int j = 1; j <= w; j++)
            if (s[j] == '.')
                mp[i][j] = 0;
            else
                mp[i][j] = 1;
    }
    memset(ans, -1, sizeof ans);
    for (int i = 1; i <= p; i++) {
        int x = read(), y = read();
        flag[x][y] = i;
        ans[x][y] = 0;
        q.push(node(x, y));
    }
    bfs();
    //	printf("%d\n", len);
    kruskal();
    for (int i = 1; i <= p; i++)
        if (fa[i] == i)
            dfs(i, -1);
    for (int i = 1; i <= Q; i++) {
        int x = read(), y = read();
        if (Find_Set(x) != Find_Set(y))
            print(-1, '\n');
        else
            print(lca(x, y), '\n');
    }
    return 0;
}
```

---

## 作者：NXYorz (赞：4)

[题目链接](https://www.luogu.com.cn/problem/AT1221)

看到题解区都是$Kruskal$重构树的题解，我来一发平易近人的$Lca$倍增题解qwq。

容易想到放到图上来做。

发现每一次询问的都是建筑物。 如果把建筑物看成点，也就是说对于任意两个点之间， 肯定有**若干条**路径。 其中肯定有一条最优的，也就是说**其余**的路径都是不需要的， 我们关心的只是最优的那一条。 把这些边**删去**， 我们就会~~惊讶~~的发现所有的建筑物连成了一棵树!

因此我们要求的就是这张网格图的$MST$了。 对于每一条边的长度， 我们可以多源 $bfs$ 来求。 最早即最优。 如果两个源点所扩张到的点相交了， 那么这一条边的长度就是两个源点到该点距离和。 把
所有的边压入堆里， 最后并查集来实现 $Kruskal$ 即可。

于是就得到了一棵树， 对于每一次询问这棵树的节点 $x,y$ 之间的最大距离。 我们可以在 $Lca$ 的同
时倍增解决了qwq!~~类似于[货车运输](https://www.luogu.com.cn/problem/P1967)~~。

### $Code$
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N = 2e3 + 10;
const int Q = 2e5 + 10;
int h,w,p,qq,sum;
int first[Q],d[N][N],star[N][N],f[Q][21],dis[Q][21],dep[Q];
int father[Q];
int fx[5] = {0 , 1 , -1 , 0 , 0};
int fy[5] = {0 , 0 , 0 , 1 , -1};
string s[N];
char dt[N][N];
bool v[Q],b[N][N];
void in(int &x) {
	x = 0;
	char ee = getchar();
	while(ee < '0' || ee > '9') ee = getchar();
	while(ee >= '0' && ee <= '9') x = (x << 1) + (x << 3) + ee - '0' , ee = getchar();
} struct NO
{int x,y;} Node[N * N],Build[N * N];
struct queue {
	int head,tail;
	NO a[N * N];
	void clear() {
		head = tail = 0;
	}
	void push(NO x) {
		a[tail++] = x;
	}
	NO front() {
		return a[head];
	}
	void pop() {
		head++;
	}
	bool empty() {
		return head == tail ? true : false;
	}
} q;
struct E {
	int next;
	int to;
	int w;
	void add(int x , int y , int w_) {
		next = first[x];
		to = y;
		w = w_;
		first[x] = sum;
	}
} e[Q * 2];
struct Edge {
	int l,r,w;
	bool operator < (const Edge b) const {
		return w > b.w;
	}
};
priority_queue<Edge> G;
inline int find(int x) {
	return father[x] == x ? x : father[x] = find(father[x]);
}
void bfs() {
	while(!q.empty()) {
		NO top = q.front();
		q.pop();
		int x = top.x;
		int y = top.y;
		b[x][y] = 1;
		for(int i = 1 ; i <= 4 ; i++) {
			int xx = x + fx[i];
			int yy = y + fy[i];
			if(xx <= 0 || xx > h || yy <= 0 || yy > w || dt[xx][yy] == '#' || b[xx][yy])
				continue;
			b[x][y] = 1;
			if(!star[xx][yy]) {
				star[xx][yy] = star[x][y];
				d[xx][yy] = d[x][y] + 1;
				q.push((NO) {
					xx , yy
				});
			} else if(star[xx][yy] != star[x][y])
				G.push((Edge) {
				star[x][y] , star[xx][yy] , d[xx][yy] + d[x][y]
			});
		}
	}
} void Kruskal() {
	while(!G.empty()) {
		Edge now = G.top();
		G.pop();
		int x = now.l;
		int y = now.r;
		int fx = find(x);
		int fy = find(y);
		if(fx == fy) continue;
		father[fx] = fy;
		e[++sum].add(x , y , now.w);
		e[++sum].add(y , x , now.w);
	}
} void dfs(int x , int fa) {
	dep[x] = dep[fa] + 1;
	v[x] = 1;
	f[x][0] = fa;
	for(int i = first[x] ; i ; i = e[i].next) {
		int to = e[i].to;
		if(to == fa) continue;
		dis[to][0] = e[i].w;
		dfs(to , x);
	}
} void Dp() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <=p ; i++) {
			f[i][j] = f[f[i][j - 1]][j - 1];
			dis[i][j] = max(dis[f[i][j - 1]][j - 1] , dis[i][j - 1]);
		}
} int Lca(int x , int y) {
	int ans = 0;
	if(dep[x] < dep[y]) swap(x , y);
	for(int i = 20; i >= 0; i--)
		if(dep[f[x][i]] >= dep[y]) {
			ans =max(ans , dis[x][i]);
			x = f[x][i];
		}
	if(x == y) return ans;
	for(int i = 20; i >= 0; i--)
		if(f[x][i] && f[y][i])
			if(f[x][i] != f[y][i]) {
				ans =max(ans , max(dis[y][i] , dis[x][i]));
				x = f[x][i];
				y = f[y][i];
			}
	return max(ans , max(dis[x][0] , dis[y][0]));
} int main() {
//	freopen("2.in","r",stdin);
//	freopen("2.out","w",stdout);
	in(h);
	in(w);
	in(p);
	in(qq);
	for(int i = 1; i <= h; i++)
		cin>>s[i];
	for(int i = 1; i <= h; i++)
		for(int j = 0; j < w; j++)
			dt[i][j + 1] = s[i][j];
	for(int i = 1; i <= p; i++) {
		in(Build[i].x);
		in(Build[i].y);
		int ai = Build[i].x;
		int bi = Build[i].y;
		star[ai][bi] = i;
		father[i] = i;
		q.push((NO) {
			ai , bi
		});
	} bfs();
	Kruskal();
	for(int i = 1; i <= p; i++)
		if(!v[star[Build[i].x][Build[i].y]])
			dfs(star[Build[i].x][Build[i].y] , 0);
	Dp();
	for(int i = 1; i <= qq; i++) {
		int x,y;
		in(x);
		in(y);
		if(find(x) != find(y)) printf("-1\n");
		else printf("%d\n",Lca(x , y));
	} return 0;
}
```

---

## 作者：too_later (赞：3)

[这里看题面](https://www.luogu.com.cn/problem/AT1221)

### 一句话题意

有一块 $n\times m$ 的地，上面有不能通行 `#` ，可以通行的 `.`，有 $w$ 个建筑物。

你每次从一个建筑物出发，到另一个建筑物的代价是中间的格子数。

让你求从 $s_i$ 建筑物出发到 $t_i$ 的建筑物所经过所有路线中，最大代价最小的那个代价。

$1\le n,m\le 2000,1\le m,q \le 10^5$。（希望管理员吧数据范围、数据约束加上）。

### 思路

这不显然是求一个 MST 中，a 到 b 所有权值最大的嘛？

这不显然是 kruskal 重构树嘛？（不会的可以[左转](https://www.cnblogs.com/zwfymqz/p/9683523.html)）

那这样我们又要保证边权从小到大啊，如果暴力添边的话会添 $w^2$ 条边，显然会 T。

这里我们要学会~~灵活~~思考，kruskal 的话不是只需要最小的那几条边嘛，我要你大的干嘛？

这样就可以减去很多时间了。

这里又是一个神奇的算法：多源 BFS。

如果把所有的建筑物都作为起点开始 BFS 的话，**似乎**就可以保证边权单调性了！

手动模拟一下，多源 BFS 往外扩张像什么？

多个区域一起往外扩张直至合并！像“水滴扩散”！

当每个水滴碰到的时候，就把他们连起来，这样一定是最优的（最短的）。

给每个 BFS 到的点打上标记，显然第一个到达这里的点是最优的（第二个水滴扩散到这个格子的不算数 23333 ）。

由于有阻碍，开一个 dis 记录最近的建筑物到他的距离。当两个碰到的时候就当前步数+dis 作为边权。（两边扩散）

这样就可做了，刚好这题数据也不怎么死，直接倍增 LCA 即可。

### Code:

```cpp
// 鄙人码风不清爽请见谅
#include <bits/stdc++.h>
using namespace std;
const int N = 2005, M = 800005;
const int dx[10] = {0, 0, 0, -1, 1};
const int dy[10] = {0, 1, -1, 0, 0};
struct edg {
    int a, b, w;
    bool operator < (const edg &a1) const {
        return w < a1.w;
    }
} ed[N * N];
struct edge {
    int to, next;
} e[M * 2];
struct node {
    int id, x, y, w;
    node(int iid, int xx, int yy, int ww) {
        id = iid, x = xx, y = yy, w = ww;
    };
};
int cnt, n, m, w, q, xx, yy, fa[M], x[M], y[M], val[M], dep[M], id[N][N], head[M * 2];
int ql, qr, tot, vis[M], dis[N][N], f[M][20];
char c[N][N];
inline int find(int u) {
    if (u == fa[u])
        return u;

    return fa[u] = find(fa[u]);
}
inline void add(int from, int to) {
    e[++cnt] = (edge) {
        to, head[from]
    };
    head[from] = cnt;
}
inline void dfs(int u, int fat) {
    dep[u] = dep[fat] + 1;
    f[u][0] = fat;
    vis[u] = 1;

    for (int i = 1; i < 20; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];

    for (int v, i = head[u]; i; i = e[i].next)
        if ((v = e[i].to) != fat)
            dfs(v, u);

    return;
}
inline int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 19; ~i; --i)
        if (dep[x] - dep[y] >= (1 << i))
            x = f[x][i];

    if (x == y)
        return x;

    for (int i = 19; ~i; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];

    return f[x][0];
}
int main() {
    queue<node> qq;
    scanf("%d%d%d%d", &n, &m, &w, &q);

    for (int i = 1; i < M; i++)
        fa[i] = i;

    for (int i = 1; i <= n; i++)
        scanf("%s", c[i] + 1);

    for (int i = 1; i <= w; i++)
        scanf("%d%d", &x[i], &y[i]), qq.push(node(id[x[i]][y[i]] = i, x[i], y[i], 0));

    while (!qq.empty()) {
        node k = qq.front();
        qq.pop();
        id[k.x][k.y] = k.id;

        for (int i = 1; i <= 4; i++) {
            int tx = dx[i] + k.x, ty = dy[i] + k.y;

            if (tx <= 0 || tx > n || ty <= 0 || ty > m || c[tx][ty] == '#')
                continue;

            if (id[tx][ty]) {
                if (id[tx][ty] != id[k.x][k.y])
                    ed[++tot] = (edg) {
                    id[k.x][k.y], id[tx][ty], k.w + dis[tx][ty]
                };
            } else
                qq.push(node(id[tx][ty] = k.id, tx, ty, dis[tx][ty] = k.w + 1));
        }
    }

    sort(ed + 1, ed + tot + 1);

    for (int i = 1; i <= tot; i++) {
        int ex = find(ed[i].a), ey = find(ed[i].b);

        if (ex != ey)
            add(ex, ++w), add(ey, w), add(w, ex), add(w, ey), fa[ex] = fa[ey] = w, val[w] = ed[i].w;
    }

    for (int i = 1; i <= w; i++)
        if (!vis[i])
            dfs(find(i), 0);

    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &ql, &qr);

        if (find(ql) != find(qr))
            puts("-1");
        else
            printf("%d\n", val[lca(ql, qr)]);
    }

    return 0;
}
```

### 总结

要有爆炸性思维，这个思路不行赶紧换，不要死磕没有意思！

要有创新性思维，感觉自己优化不行模拟说不定会给自己一些思路。

还有 too_late 可爱！

---

## 作者：Leasier (赞：1)

前置芝士：[bfs](https://oi-wiki.org/graph/bfs/)、[Kruskal 重构树](https://www.cnblogs.com/zwfymqz/p/9683523.html)

显然可以暴力建边，即：设 $dis_u$ 表示 $u$ 到离 $u$ 最近的建筑物的距离，对于两个格子 $u, v$，建边 $u \to v$，边权为 $dis_u + dis_v$。$dis_v$ 可以用双端队列 bfs 求出。

有人说，这不对，因为来去的边权可能不同，但可以证明它**没有影响**。

证明：假设 $u$ 和 $v$ 均为原野或建筑物，显然成立；设离 $u$ 最近的建筑物为 $building_u$，假设 $u$ 为建筑物，$v$ 为原野，则从 $u$ 到 $v$ 需要消耗 $1$ 的水量，从 $v$ 到 $building_v$ 需要消耗 $dis_v - 1$ 的水量，则边权应为 $dis_v$。由于 $dis_u = 0$，原式成立。

但是这样做会被卡空间。于是我们可以考虑在 bfs 的同时建边。但这样貌似还会被卡空间。于是我们可以考虑**缩点**，即将最近建筑物相同的原野缩成一个点。

建完图后跑 Kruskal 重构树（边权从小到大），查询时直接查 LCA 即可。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

typedef struct Set_tag {
	int x;
	int y;
	Set_tag(int x_, int y_){
		x = x_;
		y = y_;
	}
} Set;

typedef struct {
	int start;
	int end;
	int dis;
} Edge1;

typedef struct {
	int nxt;
	int end;
} Edge2;

const int N = 2e5 + 7, M = 4, K = 8e6 + 7, P = 22, Q = 2e3 + 7, R = 1.6e7 + 7;
int dot_cnt, edge_cnt = 0;
int city[N], dx[M + 7] = {0, -1, 0, 0, 1}, dy[M + 7] = {0, 0, -1, 1, 0}, dis[K], belong[K], root[K], head[K], depth[K], fa[K][P + 1];
char mp[Q][Q];
bool mark[Q][Q], vis[Q][Q];
Edge1 edge1[R];
Edge2 edge2[K];
deque<Set> q;

bool operator <(const Edge1 a, const Edge1 b){
	return a.dis < b.dis;
}

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		root[i] = i;
	}
}

inline int bfs(int h, int w){
	int n = 0;
	for (register int i = 1; i <= h; i++){
		for (register int j = 1; j <= w; j++){
			int id = w * (i - 1) + j;
			if (mark[i][j]){
				dis[id] = 0;
				belong[id] = id;
				q.push_back(Set(i, j));
			} else {
				dis[id] = 0x7fffffff;
			}
		}
	}
	while (!q.empty()){
		int cur_x, cur_y;
		Set cur = q.front();
		q.pop_front();
		cur_x = cur.x;
		cur_y = cur.y;
		if (vis[cur_x][cur_y]) continue;
		int id = w * (cur_x - 1) + cur_y;
		vis[cur_x][cur_y] = true;
		for (register int i = 1; i <= M; i++){
			int new_x = cur_x + dx[i], new_y = cur_y + dy[i], new_id = w * (new_x - 1) + new_y;
			if (new_x >= 1 && new_x <= h && new_y >= 1 && new_y <= w && mp[new_x][new_y] == '.' && belong[id] != belong[new_id]){
				if (belong[new_id] == 0){
					belong[new_id] = belong[id];
					dis[new_id] = dis[id] + (mark[new_x][new_y] ? 0 : 1);
					if (mark[new_x][new_y]){
						q.push_front(Set(new_x, new_y));
					} else {
						q.push_back(Set(new_x, new_y));
					}
				} else if (belong[id] != belong[new_id]){
					n++;
					edge1[n].start = belong[id];
					edge1[n].end = belong[new_id];
					edge1[n].dis = dis[id] + dis[new_id];
				}
			}
		}
	}
	return n;
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void add_edge(int start, int end){
	edge_cnt++;
	edge2[edge_cnt].nxt = head[start];
	head[start] = edge_cnt;
	edge2[edge_cnt].end = end;
}

inline void kruskal(int n){
	int m = dot_cnt * 2 - 1;
	for (register int i = 1; i <= n; i++){
		int x_root = get_root(edge1[i].start), y_root = get_root(edge1[i].end);
		if (x_root != y_root){
			dot_cnt++;
			root[x_root] = root[y_root] = dot_cnt;
			dis[dot_cnt] = edge1[i].dis;
			add_edge(dot_cnt, x_root);
			add_edge(dot_cnt, y_root);
			if (dot_cnt == m) break;
		}
	}
}

void dfs(int u, int father){
	int t;
	depth[u] = depth[father] + 1;
	t = log2(depth[u]);
	fa[u][0] = father;
	for (register int i = 1; i <= t; i++){
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (register int i = head[u]; i != 0; i = edge2[i].nxt){
		dfs(edge2[i].end, u);
	}
}

inline int lca(int u, int v){
	if (depth[u] < depth[v]) swap(u, v);
	while (depth[u] > depth[v]) u = fa[u][(int)log2(depth[u] - depth[v])];
	if (u == v) return u;
	for (register int i = log2(depth[u]); i >= 0; i--){
		if (fa[u][i] != fa[v][i]){
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

int main(){
	int h, w, p, q, n;
	cin >> h >> w >> p >> q;
	dot_cnt = h * w;
	init(dot_cnt * 2 - 1);
	for (register int i = 1; i <= h; i++){
		cin >> &mp[i][1];
	}
	for (register int i = 1; i <= p; i++){
		int a, b;
		cin >> a >> b;
		city[i] = w * (a - 1) + b;
		mark[a][b] = true;
	}
	n = bfs(h, w);
	sort(edge1 + 1, edge1 + n + 1);
	kruskal(n);
	for (register int i = 1; i <= dot_cnt; i++){
		if (get_root(i) == i) dfs(i, 0);
	}
	for (register int i = 1; i <= q; i++){
		int s, t;
		cin >> s >> t;
		s = belong[city[s]];
		t = belong[city[t]];
		if (get_root(s) != get_root(t)){
			cout << -1 << endl;
		} else {
			cout << dis[lca(s, t)] << endl;
		}
	}
	return 0;
}
```

---

## 作者：zymooll (赞：1)

## 简要题意

给定一个 $H \times W$ 的图，规定图上每个点分为三类，原野、建筑物和墙壁。求在不经过墙壁的情况下最小化从 $S$ 建筑物到 $T$ 建筑物所要经过的建筑物间曼哈顿距离的最大值。

## 主要思路

在原图上跑一遍多源 BFS 抽象出一张图，然后对该图跑最小生成树，因为可能原图不只有一个连通块。所以对于每个连通块都有一颗最小生成树，故需要建立超级源点连接每个最小生成树，然后以超级源点为根节点跑一遍重链剖分，再根据 DFS 序边权下放点权来建立 ST 表求出区间最大值。最后对于单次查询，先确定是否在一个连通块内，不是则输出 `-1`，否则在剖分树上跑一遍，顺便求出路径的最大值即可。

参考时间复杂度：$O(n \log n)$。

## 参考代码

```cpp
// Author:zymooll

#include<bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define int long long
using namespace std;
int read(){
  int s = 0, w = 1;
  char c = getchar();
  while(c < '0' || c > '9'){
    if(c == '-')w = -1;
    c = getchar();
  }
  while(c >= '0' && c <= '9'){
    s = s * 10 + c - '0';
    c = getchar();
  }
  return s * w;
}
void print(int x){
  if(x < 0){
    putchar('-');
    x = -x;
  }
  if(x >= 10)print(x / 10);
  putchar(x % 10 + '0');
  return;
}
const int XMax = 2e3;
const int PMax = 2e5;
int n, m, p, Q;
char dmap[XMax + 10][XMax + 10];
int bel[XMax + 10][XMax + 10];
int dis[XMax + 10][XMax + 10];
bitset<XMax + 10>vis[XMax + 10];
int fx[4][2] = {-1,0,0,-1,1,0,0,1};
struct EdgeP{
  int u, v, w;
}g1[(PMax << 3) + 10];
int g1cnt;
struct Edge{
  int v, w, next;
}g[(PMax << 4) + 10];
int h[PMax + 10], h2[PMax + 10], cnt;
inline void addedge(int u, int v, int w){
  g[++cnt] = (Edge) {v,w,h[u]};
  h[u] = cnt++;
}
int fa[PMax + 10], fa1[PMax + 10];
inline int find(int x){
  if(fa[x] != x)fa[x] = find(fa[x]);
  return fa[x];
}
inline void merge(int x, int y){
  fa[find(y)] = find(x);
}
inline bool check(int x, int y){
  return find(x) == find(y);
}
struct Node{
  int dep, dfn, htop, hson, fa, size, n;
}node[PMax + 10];
int ncnt;
int st[20][PMax + 10];
void dfs1(int u, int dep){
  node[u].dep = dep;
  node[u].size = 1;
  for(int i = h[u]; i; i = g[i].next){
    int& v = g[i].v, & w = g[i].w;
    if(node[v].dep)continue;
    node[v].fa = u, node[v].n = w;
    dfs1(v, dep + 1);
    node[u].size += node[v].size;
    if(node[v].size > node[node[u].hson].size){
      node[u].hson = v;
    }
  }
}
void dfs2(int u, int top){
  node[u].htop = top;
  node[u].dfn = ++ncnt;
  st[0][node[u].dfn] = node[u].n;
  if(!node[u].hson)return;
  dfs2(node[u].hson, top);
  for(int i = h[u]; i; i = g[i].next){
    int& v = g[i].v;
    if(v == node[u].fa || v == node[u].hson)continue;
    dfs2(v, v);
  }
}
inline int askmax(int l, int r){
  int len = r - l + 1;
  int tg = __lg(len);
  return max(st[tg][l], st[tg][r - (1 << tg) + 1]);
}
char getcharS(){
  char ch = getchar();
  while(ch == ' ' || ch == '\r' || ch == '\n')ch = getchar();
  return ch;
}
signed main(){
  n = read(), m = read(), p = read(), Q = read();
  for(int i = 1; i <= p + 1; i++){
    fa[i] = i;
  }
  for(int i = 1; i <= n; i++){
    dmap[i][1] = getcharS();
    for(int j = 2; j <= m; j++){
      dmap[i][j] = getchar();
    }
  }
  queue<pair<int, int> >q;
  for(int i = 1; i <= p; i++){
    int x = read(), y = read();
    q.push(make_pair(x, y));
    bel[x][y] = i;
  }
  while(!q.empty()){
    int ux = q.front().first, uy = q.front().second; q.pop();
    vis[ux][uy] = 1;
    for(int i = 0; i < 4; i++){
      int dx = ux + fx[i][0], dy = uy + fx[i][1];
      if(dmap[dx][dy] == '#' || dx<1 || dx>n || dy<1 || dy>m || vis[dx][dy])continue;
      if(!bel[dx][dy])bel[dx][dy] = bel[ux][uy], dis[dx][dy] = dis[ux][uy] + 1, q.push(make_pair(dx, dy));
      else if(bel[dx][dy] != bel[ux][uy])g1[++g1cnt] = (EdgeP) {bel[ux][uy], bel[dx][dy], dis[ux][uy] + dis[dx][dy]};
    }
  }
  sort(g1 + 1, g1 + 1 + g1cnt, [&](EdgeP aa, EdgeP bb){return aa.w < bb.w; });
  int js = 0;
  for(int i = 1; i <= g1cnt; i++){
    int& u = g1[i].u, & v = g1[i].v, & w = g1[i].w;
    if(check(u, v))continue;
    merge(u, v);
    addedge(u, v, w), addedge(v, u, w);
    if(++js == p - 1)break;
  }
  memcpy(fa1, fa, sizeof(fa));
  for(int i = 1; i <= p; i++){
    if(!check(p + 1, i)){
      merge(p + 1, i);
      addedge(p + 1, i, 0), addedge(i, p + 1, 0);
    }
  }
  dfs1(p + 1, 1);
  dfs2(p + 1, p + 1);
  for(int i = 1; i <= __lg(p + 1); i++){
    for(int j = 1; j <= p + 1 - (1 << i) + 1; j++){
      st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
  memcpy(fa, fa1, sizeof(fa1));
  while(Q--){
    int u = read(), v = read();
    if(!check(u, v)){ puts("-1"); continue; }
    int maxn = INT_MIN;
    while(node[u].htop != node[v].htop){
      if(node[node[u].htop].dep < node[node[v].htop].dep)swap(u, v);
      maxn = max(maxn, askmax(node[node[u].htop].dfn, node[u].dfn));
      u = node[node[u].htop].fa;
    }
    if(node[u].dfn != node[v].dfn)maxn = max(maxn, askmax(min(node[u].dfn, node[v].dfn) + 1, max(node[u].dfn, node[v].dfn)));
    print(maxn), putchar('\n');
  }
  return 0;
}
```

## 后记

因为众所周知的原因，洛谷上没有本人的通过记录，但是 Atcoder 是过了的。

这道题实际上就是 [P1967](/problem/P1967) 的加强版，所以可以喜加一了。

---

## 作者：cryozwq (赞：0)

写一篇题解证明一下，算是对题解区写这种做法的老哥们的补充。

前置知识：克鲁斯卡尔重构树。

由于题目限制了是个网格图并且边权为 $1$ 或者 $0$ ，可以直接 BFS。

然后对于每个非城市节点记录离它最近的城市节点，对于 BFS 当前考虑的两个点。如果有一个还没被城市节点覆盖，那么就覆盖这个节点，如果被不同城市节点覆盖就保留这条边，边权变为两者 dis 值之和， dis 值表示离自己最近的城市的距离，再把这些边跑一次最小生成树，建出重构树，每次询问即查询两者 LCA 的点权，这些东西大家可以去看 [Query_LCA
的题解](https://www.luogu.com.cn/blog/AlFepular/solution-at1221)。我想补充一下一个细节：

考虑如果当前这条边连接着一个城市和一个原野，那么其实原野到城市的边权应该是 $0$ ，但是我们并没有判这种情况，为什么呢？考虑一条路径上要走到某个城市，但是我们有一个结论：先走到这个点的最近城市补充水，然后再走回来，这样一定最优，这个结论也是非常好证的，限于篇幅就不写了，如果有疑惑可以私信找我。这样一来你回到原野的过程中一定至少经过了一个 $1$，而且这题比较特殊之处是边权固定为 $1$，所以最优方案一定是会走到城市再走回来再走过去，那么 $0$ 这条边一定没有用了。所以连成 $1$ 一定没有问题。

---

## 作者：DQYdqy (赞：0)

## Solution:

考虑把给定的地图建出图来，那么询问实际上就是询问图上两点所有路径中最大边权的最小值

询问是一个老问题了，把边按权升序排列，用kruskal重构树，答案即为树上两点lca的点权

考虑如何建图，我们用一个bfs来建图即可，每次扩展到一个被其他城市扩展过的点，就加入一条边

因为不知道有多少条边，我们用vector来存边，注意判断两点是否在一个连通块内，注意路径压缩(不能直接用fa[x]啊)

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+11;
const int M=2e3+11;
const int dx[]={0,1,-1,0};
const int dy[]={1,0,0,-1};
struct E{int x,y,val;};
char s[M][M];
int n,m,P,Q,col[M][M],dis[M][M];
int v[N],rt[N],dep[N],f[N][20];
int tot,fa[N],block;
bitset<N> vis;
queue<E> q;
vector<E> edge;
vector<int> g[N];
inline bool cmp(E u,E v){return u.val<v.val;}
inline bool in(int x,int y,int id){
    if(s[x][y]=='#'||col[x][y]==id) return 0;
    if(x<1||x>n||y<1||y>m) return 0;
    return 1;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void ins(int x,int y){g[x].push_back(y);}
void bfs(){
    while(!q.empty()){
        E u=q.front();q.pop();
        int x=u.x,y=u.y;
        for(int i=0;i<4;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(!in(nx,ny,col[x][y])) continue;
            if(col[nx][ny]){
                int id1=col[x][y],id2=col[nx][ny];
                int Dis=dis[x][y]+dis[nx][ny];
                edge.push_back((E){id1,id2,Dis});
            }else{
                col[nx][ny]=col[x][y];
                dis[nx][ny]=dis[x][y]+1;
                q.push(E{nx,ny,0});
            }
        }
    }
    sort(edge.begin(),edge.end(),cmp);
}
void kruskal(){
    tot=P;
    for(int i=1;i<=P*2;i++) fa[i]=i;
    for(int i=0;i<edge.size();i++){
        int x=edge[i].x,y=edge[i].y;
        x=find(x),y=find(y);
        if(x==y) continue;
        int z=edge[i].val;
        ++tot;v[tot]=z;
        ins(x,tot),ins(tot,x);
        ins(y,tot),ins(tot,y);
        fa[x]=fa[y]=tot;
    }
    for(int i=1;i<=tot;i++) find(i);
    for(int i=1;i<=tot;i++)
        if(!vis[fa[i]]) rt[++block]=fa[i],vis[fa[i]]=1;
}
void dfs(int x){
    for(int i=0;i<g[x].size();i++){
        int y=g[x][i];
        if(y==f[x][0]) continue;
        f[y][0]=x,dep[y]=dep[x]+1;
        dfs(y);
    }
}
void trans(){
    for(int i=1;i<=19;i++)
        for(int j=1;j<=tot;j++)
            f[j][i]=f[f[j][i-1]][i-1];
}
int lca(int x,int y){
    if(fa[x]!=fa[y]) return 0;
    if(dep[y]>dep[x]) swap(x,y);
    for(int i=19;i>=0;i--)
        if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--)
        if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
signed main(){
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    n=read(),m=read();
    P=read(),Q=read();
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    for(int i=1;i<=P;i++){
        int x=read(),y=read();
        col[x][y]=i;
        q.push((E){x,y,0});
    }
    bfs();kruskal();
    for(int i=1;i<=block;i++) dfs(rt[i]);
    trans();v[0]=-1;
    for(int i=1;i<=Q;i++){
        int x=read(),y=read();
        printf("%d\n",v[lca(x,y)]);
    }
    return 0;
}
```

---

