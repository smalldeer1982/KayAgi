# [USACO12NOV] Distant Pastures S

## 题目描述

Farmer John's farm is made up of an N x N grid of pastures, where each pasture contains one of two different types of grass.  To specify these two types of grass, we use the characters ( and ), so for example FJ's farm might look like the following grid:

(()) 
)()( 
)((( 
))))
When Bessie the cow travels around the farm, it takes her A units of time to move from a pasture to an adjacent pasture (one step north, south, east, or west) with the same grass type, or B units of time to move to an adjacent pasture with a different grass type.  Whenever Bessie travels from one pasture to a distant pasture, she always uses a sequence of steps that takes the minimum amount of time.  Please compute the greatest amount of time Bessie will ever need to take while traveling between some pair of pastures on the farm.

给出一个n\*n的括号矩阵，从一个点走到相邻的同字符点需付出A的代价，到不同字符点需付出B的代价。求所有点对之间最短路的最大值。


## 说明/提示

It takes Bessie 5 units of time to travel between the upper-left corner and the lower-right corner of the grid.  No other pair of pastures causes her to travel for more time than this.


## 样例 #1

### 输入

```
3 1 2 
((( 
()( 
(() 
```

### 输出

```
5 
```

# 题解

## 作者：风格雨关 (赞：4)

~~蒟蒻~~又来发题解啦！

这道题是一道非常神奇的图论小题，对于两个相邻的括号：    
如果括号相同则连一条权值为 _**a**_ 的边，否则连一条权值为 _**b**_ 的边。   
鉴于此题的 _**n**_ 较大，使用**Floyd-Warshall**算法会超时，这里使用**Dijkstr**a单源最短路径算法。      


------------

代码来啦！！！（伸手党勿扰，有坑！！！）

```cpp
//代码改编自USACO的官方题解
#include<bits\stdc++.h>
//万能头文件
using namespace std;
#define NMAX 40
int grid[NMAX][NMAX];
int di[4]={1,-1,0,0};
int dj[4]={0,0,1,-1};
bool visited[NMAX][NMAX];
struct node
{
	int i,j;
	int dist;
	node(int i,int j,int dist):i(i),j(j),dist(dist){ }
	bool operator<(node const& other)const {
		return dist > other.dist;
	}
};
int getRadius(int n,int sourcei,int sourcej,int costSame,int costDiff)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++) visited[i][j]=false;
	}
	priority_queue<node> q;
	q.push(node(sourcei, sourcej, 0));
	int maxDist=0;
	while(q.size()>0)
	{
    	node v=q.top();
    	q.pop();
    	if(!visited[v.i][v.j])
		{
			visited[v.i][v.j]=true;
			for(int d=0;d<4;d++)
			{
				int i1=v.i+di[d];
        		int j1=v.j+dj[d];
        		if(i1>=0&&i1<n&&j1>=0&&j1<n)
				{
					int dist=v.dist+(grid[v.i][v.j]==grid[i1][j1]?costSame:costDiff);
					q.push(node(i1, j1, dist));
				}
			}
			maxDist=max(maxDist, v.dist);
		}
	}
	return maxDist;
}
int main()
{
	int n,costSame,costDiff;
	cin<<n<<costSame<<costDiff;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			char c;
			do 
			{
				c=fgetc(stdin);
			}while(c!='('&&c!=')');
			grid[i][j]=c;
		}
	}
	int diam=0;
	for(int i=0;i<n;i++)
	{
    	for(int j=0;j<n;j++)
		{
			int radius=getRadius(n,i,j,costSame,costDiff);
      		diam=max(diam,radius);
		}
	}
	cout<<diam<<'/n';
	return 0;
}
```
但是...TLE...233333333333   
于是如何处理TLE呢？   
1. 读入优化！！！    
c++中的流输入比c中的scanf满了太多，所以可以在主程序一开始加上这样一句话：
```cpp
ios::sync_with_stdio(false);
```
这样可以将cin的速度加速到scanf甚至更快！！！   
2. 读入优化！！！(2)   
利用自定义函数read加速读入。

3. 玄学加速
以下是 @ttyclear 大神给我的玄学加速，需要加在头文件前
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```
4. 氧优化（O2）

---

## 作者：liangbowen (赞：3)

### 前言
[题目传送门](https://www.luogu.com.cn/problem/P3057)

[$\color{red}{see}\space \color{green}{in}\space \color{blue}{my}\space \color{purple}{blog}$](https://www.luogu.com.cn/blog/liangbowen/solution-P3057)

在学校比赛时遇到了这一题，写一篇题解纪念一下。

本题是最短路好题。

### 思路

此题明显是最短路。

我们需要求任意两点的最短路的最大值，即全源最短路。

本题共有 $n^2$ 个点，如果跑 Floyd 时间复杂度是 $O(n^6)$，非常极限，不是本题正解。

但是，我又不会写 Johnson 全源最短路，怎么办呢?

每个点朝四周建边，容易发现，边的数量不超过 $4 \times n^2$。

想到这里，明显可以跑 $n^2$ 次 dijkstra 实现，因为当边数较小时，跑多次 dijkstra 会比 Floyd 快。

此处 dijkstra 是使用优先队列实现。

那么就很容易写出代码了。

### 思路总结

1. 读入数据。

2. 每个点朝四周建边。
3. 写一个 dijkstra 的模版。
4. 统计最大值，输出。

### 代码

最短路模版没有强制要求，按照自己的习惯写 dijkstra 当然可以。

还有一个小细节：边数 $m$ 最多有多少？

$m = 905 * 4 * 2 = 7200$。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define N 905
#define M 7205
using namespace std;
int n, nn, A, B;
int dict[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool a[35][35];
struct Node
{
	int now, nxt, w;
}e[M];
int head[N], cur;
void add(int x, int y, int k)
{
	e[++cur].now = y;
	e[cur].nxt = head[x];
	e[cur].w = k;
	head[x] = cur;
}
struct Dis
{
	int pos, len;
	bool operator <(const Dis &t) const
	{
		return len > t.len; 
	}
}dis[N];
bool vis[N];
int dijkstra(int first) 
{
	priority_queue <Dis> Q;
	for (int i = 1; i <= nn; i++) dis[i].pos = i, dis[i].len = 2147483647, vis[i] = false;
	dis[first].len = 0;
	Q.push(dis[first]);
	while (!Q.empty())
	{
		int topi = Q.top().pos;
		Q.pop();
		if (vis[topi]) continue;
		vis[topi] = true;
		for (int i = head[topi]; i; i = e[i].nxt)
			if (dis[topi].len + e[i].w < dis[e[i].now].len)
			{
				dis[e[i].now].len = dis[topi].len + e[i].w;
				Q.push(dis[e[i].now]);
			}
	}
    //此处有是惟一与普通模版不同的地方，需要找出最大值。
	int maxn = 0;
	for (int i = 1; i <= nn; i++) maxn = max(maxn, dis[i].len);
	return maxn;
}
void Input()
{
	scanf("%d%d%d", &n, &A, &B);
	nn = n * n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			char x;
			cin >> x;
			if (x == '(') a[i][j] = true;
		}
}
void get_edge()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 0; k < 4; k++)
			{
				int x = i + dict[k][0], y = j + dict[k][1];
				if (!(1 <= x && x <= n && 1 <= y && y <= n)) continue;
				int t1 = n * (i-1) + j, t2 = n * (x-1) + y;
				if (a[i][j] == a[x][y]) add(t1, t2, A);
				else add(t1, t2, B);
			}
}
void solve()
{
	int maxn = 0;
	for (int i = 1; i <= nn; i++) maxn = max(maxn, dijkstra(i));
	printf("%d", maxn);
}
int main()
{
	Input();
	get_edge();
	solve();
	return 0;
}
```

---

## 作者：12345678hzx (赞：2)

一眼图论题。

由于此题数据较小，并且可以朝四个方向走，所以考虑建图跑最短路，如果此题只能朝右下两个方向走，就考虑动态规划，因为动态规划是通过最优子结构性质得到答案的，而本题一个点可能会被重复更新。

对于每一个点，朝与它相邻的四个点建边，介于此题的数据范围，Floyd 算法无法通过，所以我们采用堆优化的 Dijkstra 算法，时间复杂度为 $O(nm\log m)$，其中 $m$ 为边数。

但由于此题数据较水，所以 Floyd 算法也能通过，但我们接下来重点讲的是对 Floyd 算法的优化。

以下是正常的 Floyd 算法代码：
```cpp
for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
```
以下是优化的 Floyd 算法代码：
```cpp
for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) {
	if(a[i][k]==1e9) continue;
	for(int j=1;j<=n;j++) a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
}
```
非常好理解，如果这一条边无法对任何边进行松弛，则这条边无用。

优化后的 Floyd 算法时间复杂度上界为 $O(n^3)$，下界为 $O(n^2)$。

这是我两份代码的时间差距，[这一篇代码](https://www.luogu.com.cn/record/102893135)没有加优化，而[另一篇代码](https://www.luogu.com.cn/record/102890804)有。

可以看到，两份代码的时间差距还是非常大的，差了将近两倍。

---

## 作者：苏联小渣 (赞：1)

如果只能向右、下走，考虑 dp；可以向四个方向走，如本题，考虑建图跑最短路。

而 $n \le 30$ 的数据范围就十分允许我们建图枚举。对于建图，我们把每个位置 $a_{i,j}$ 抽象成一个点 $(i-1) \times n+j$，代表这个点的编号。对于每一个位置，我们枚举四周的四个点，如果括号相同，就连一条长度为 $a$ 的边；否则连一条长度为 $b$ 的边。接着就可以跑最短路。我们枚举 $n^2$ 个点，以每个点为源点分别跑一次单源最短路。然后再进行 $n^2$ 次枚举，取最短路的最大值。这里我使用堆优化的 dijkstra，总时间复杂度为 $O(n^4 \log (n^2))$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, s, p, x, y, h[910], dis[910], vis[910];
char a[35][35];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
struct node{
	int x, y, z, next;
}d[7510];
struct edge{
	int p, d;
	bool operator < (const edge &A) const{
		return A.d < d;
	}
};
void add(int x, int y, int z){
	d[++p].y = y, d[p].z = z, d[p].next = h[x], h[x] = p;
}
void dijkstra(int s){
	memset(vis, 0, sizeof(vis));
	memset(dis, 9, sizeof(dis));
	priority_queue <edge> q;
	q.push((edge){s, 0});
	dis[s] = 0;
	while (!q.empty()){
		edge T = q.top(); q.pop();
		if (vis[T.p]) continue; vis[T.p] = 1;
		for (int i=h[T.p]; i; i=d[i].next){
			int sy = d[i].y;
			if (dis[sy] > dis[T.p] + d[i].z){
				dis[sy] = dis[T.p] + d[i].z; q.push((edge){sy, dis[sy]});
			}
		}
	}
}
int main(){
	scanf ("%d%d%d", &n, &x, &y);
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			cin >> a[i][j];
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			for (int k=0; k<4; k++){
				int nx = i + dx[k], ny = j + dy[k];
				if (nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
				if (a[nx][ny] == a[i][j]) add((i-1)*n+j, (nx-1)*n+ny, x);
				else add((i-1)*n+j, (nx-1)*n+ny, y);
			}
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			dijkstra((i-1)*n+j);
			for (int k=1; k<=n; k++){
				for (int l=1; l<=n; l++){
					s = max(s, dis[(k-1)*n+l]);
				}
			}
		}
	}
	printf ("%d\n", s);
	return 0;
}

```

---

## 作者：yinhee (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/P3057)

## 解题思路：最短路（dijkstra）

阅读题面，可以知道是求点对间最短路的最大值。先考虑floyed，时间复杂度高达 $\large O(n^6)$ ，明显会超时。~~虽然有个同学还真卡过去了~~

这个时候其实可以考虑跑 $n^2$ 遍单源最短路。这里我用的是dijkstra,设 $m$ 为边数，则时间复杂度 $\large O(n^2(n^2+m)\log n^2)$ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1007;
int n,A,B,ans,dis[maxn][maxn];
bool bk[50][50],vis[50][50];
const int pyx[5]={0,-1,0,1,0},pyy[5]={0,0,-1,0,1};
struct zb{
	int x,y,c;
	bool operator <(const zb &x)const{return c>x.c;}
}d[maxn];
priority_queue<zb> q;
inline int plc(int x,int y){//求图上(x,y)点在d数组中的位置
	return (x-1)*n+y;
}
void dij(int x,int y){
	while(!q.empty())q.pop();
	for(int i=1;i<=n*n;i++)d[i]={i%n?i/n+1:i/n,i%n?i%n:n,2147483647};
	d[plc(x,y)].c=0;
	memset(vis,false,sizeof(vis));
	q.push(d[plc(x,y)]);
	while(!q.empty()){
		zb now=q.top();q.pop();
		if(vis[now.x][now.y])continue;
		vis[now.x][now.y]=true;
		for(int i=1;i<=4;i++){
			int nx=now.x+pyx[i],ny=now.y+pyy[i],nc=d[plc(now.x,now.y)].c+(bk[now.x][now.y]==bk[nx][ny]?A:B);
			if(nx>=1&&ny>=1&&nx<=n&&ny<=n&&!vis[nx][ny]&&nc<d[plc(nx,ny)].c){
				d[plc(nx,ny)].c=nc;
				q.push(d[plc(nx,ny)]);
			}
		}
	}
	for(int i=1;i<=n*n;i++){
		if(vis[i%n?i/n+1:i/n][i%n?i%n:n])ans=max(d[i].c,ans);
	}
}
int main(){
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char tmp;
			cin>>tmp;
			bk[i][j]=(tmp=='(');
		}
	}
	memset(dis,0x7f,sizeof(dis));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dij(i,j);
		}
	}
	printf("%d",ans);
}
```


---

## 作者：Иɔlɔ (赞：1)

不难想到，将矩阵的每个点都看成图中的一个节点，连边跑最短路。我们令矩阵中 $(i,\,j)$ 的节点编号为 $n \times (i-1) + j$，设 $N$ 为节点数，那么图中一共会有 $N=n^2$ 个节点。连边时若 $maze_{i,\,j} = maze_{k,\,l}$ 则连一条边权为 $a$ 的边，否则边权为 $b$。

题目要求任意两点之间最短路的最大值，首先想到 $\text{Floyd}$ 算法，然而 $O(N^3)$，即 $O(n^6)$ 的时间复杂度无法通过。考虑使用堆优化 $\text{Dijkstra}$ 算法，时间复杂度 $O(N(N+M) \log N)$，其中 $M$ 为边数，足以通过本题。

注意，哪些地方的数组要开 $n \times n$，哪些不需要。

$\text{Code}$：

```cpp
#define def(N, K, b) const K N = b;
#define rep(i, b, s) for(int i = b; i <= s; ++i)
#define fi first
#define se second
#define pii pair<int, int>

def(N, int, 31)
def(M, int, 3605)
def(inf, int, 0x3f3f3f3f)

struct Edge {
	int to, val, nxt;
} e[M << 1];

int n, a, b, mx;
char mze[N][N];
int head[N * N], cnt;
int dis[N * N];
bool vis[N * N];

void add(int u, int v, int type) {
	e[++cnt].to = v;
	e[cnt].val = (type ? a : b);
	e[cnt].nxt = head[u];
	head[u]	= cnt;
}

void Add(int u, int v, int type) { add(u, v, type), add(v, u, type); }

void Dijkstra(int x) {
	memset(dis, 0x3f, sizeof dis); memset(vis, 0, sizeof vis);
	dis[x] = 0;
	priority_queue<pii, vector<pii >, greater<pii > > q;
	q.push(mp(0, x));
	while(!q.empty()) {
		int u = q.top().se;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(dis[v] > dis[u] + e[i].val) {
				dis[v] = dis[u] + e[i].val;
				if(!vis[v]) q.push(mp(dis[v], v));
			}
		}
	}
}

int main() {
	cin >> n >> a >> b;
	rep(i, 1, n) scanf("%s", mze[i] + 1);
	rep(i, 1, n) rep(j, 1, n) {
		int now = (i - 1) * n + j;
		if(i > 1) Add(now, now - n, (mze[i][j] == mze[i - 1][j]));
		if(j > 1) Add(now, now - 1, (mze[i][j] == mze[i][j - 1]));
	}
	rep(i, 1, n * n) {
		Dijkstra(i);
		rep(j, 1, n * n) To_max(mx, (dis[j] == inf ? 0 : dis[j]));
	}
	printf("%d\n", mx);
 	return 0;
}
```


---

## 作者：ZolaWatle (赞：0)

## P3057 题解

显然，对于每一个点，记为 $ (i,j) $，我们以它为图中的节点，向它四周的点（如果有）连边，跑最短路。

为了方便，我们可以先将每个点进行**离散化**，这样就不用在跑最短路的判断每个点在第几行第几列了。

在这个 $ N \cdot N $ 的矩阵中，对于 $ \forall (i,j),\ i,j\in [1,N] $，给它添加一个编号。编号从 $ (1,1) $ 开始的 $1$ 到 $ (N,N) $ 的 $n^2$，我们先看一个例子：

$$ 1\ \ 2\ \ 3 $$

$$ 4\ \ 5\ \ 6 $$

$$ 7\ \ 8\ \ 9 $$

那么容易推得编号计算的公式：

$$ idx[(i,j)]=n\cdot (i-1)+j $$

离散化进行完毕，现在考虑连边。显然，在最好的情况下，有以下四种情况：

- 上面的点：应该满足 $ i\in [2,N] $，根据上面的公式，这个点的编号是 $ idx[(i,j)]-n $

- 下面的点：应该满足 $ i\in [1,N-1] $，根据上面的公式，这个点的编号是 $ idx[(i,j)]+n $

- 左面的点：应该满足 $ j\in [2,N] $，根据上面的公式，这个点的编号是 $ idx[(i,j)]-1 $

- 右面的点：应该满足 $ j\in [1,N-1] $，根据上面的公式，这个点的编号是 $ idx[(i,j)]+1 $

- $ i,j\in [1,N] $

由于每个点都会被扫描到一次，在每次连边的时候连单向边即可，节省空间和时间。

接下就只需要跑一边全源最短路，并输出其中最大值即可。最优的当然是 $ \text{Johnson} $，但本题的数据完全可以跑 $n$ 次 $ \text{Dijkstra} $ 求解。时间复杂度是 $ O(n\cdot (logn+n)) $。

完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN=31;
int n,dat[MAXN*MAXN+1];
long long A,B,ans,dist[MAXN*MAXN+1];
bool vis[MAXN*MAXN+1];
char tmp;
vector < pair <int,long long> > E[MAXN*MAXN+1];

inline void add(int i,int j)
{
	long long w=dat[i]==dat[j]?A:B;
	E[i].push_back(make_pair(j,w));
}

inline void Dijkstra(int s)
{
	priority_queue < pair <long long,int> > q;
	for(int i=1;i<=n*n;i++)
	{
		dist[i]=1e18;
		vis[i]=false;
	}
	q.push(make_pair(0,s)),dist[s]=0;
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x])
			continue;
		vis[x]=true;
		for(int i=0;i<E[x].size();i++)
		{
			int y=E[x][i].first;
			long long z=E[x][i].second;
			if(dist[x]+z<dist[y])
			{
				dist[y]=dist[x]+z;
				q.push(make_pair(-dist[y],y));
			}
		}
	}
}

int main()
{
	scanf("%d%lld%lld",&n,&A,&B);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>tmp;
			int k=n*(i-1)+j;
			dat[k]=tmp=='('?0:1;
		}
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			int k=n*(i-1)+j;
			if(i>1)
			{ 
				int u=n*(i-2)+j;
				add(k,u);
			}
			if(i<n)
			{
				int d=n*i+j;
				add(k,d);
			}
			if(j>1)
			{
				int l=k-1;
				add(k,l);
			}
			if(j<n)
			{
				int r=k+1;
				add(k,r);
			}
		}
		
	for(int i=1;i<=n*n;i++)
	{
		Dijkstra(i);
		for(int j=1;j<=n*n;j++)
			ans=max(ans,dist[j]);
	}
	
	printf("%lld",ans);
	return 0;
}
```

------------

关于本题的离散化：

笔者认为离散化之后连边和跑图的代码能更加美观，方便调试和进行查错。与我同机房的一位大佬就是这样写挂了。

------------

感谢阅读！

---

## 作者：grass8cow (赞：0)

一道简单的最短路。

给方格里每个点一个序号，$id(i,j)=n(i-1)+j$ 

于是每个点可以向四周建边。

跑 $n^2$ 次 Dijkstra ，以求出图上的最长路径。

注意要用堆优化，不然 $O(n^4)$ 要T飞。

时间复杂度：$O(n^3 \log n)$ 空间复杂度：$O(n^2)$

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[40][40];
struct qq
{
    int v,w;
};
vector<qq>g[910];
int n,a,b;
int id(int i,int j)
{
    return n*(i-1)+j;
}
struct node
{
    int u,dis;
    bool operator < (const node &x) const
    {
        return x.dis<dis;
    }
};
priority_queue<node>q;
int xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
int vis[901],dis[901],ans;
void dij(int s)
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;q.push((node){s,0});
    while(!q.empty())
    {
        node qp=q.top();q.pop();int u=qp.u;
        if(vis[u])continue;vis[u]=1;
        for(int i=0,v,w;i<g[u].size();i++)
        {
            v=g[u][i].v;w=g[u][i].w;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                q.push((node){v,dis[v]});
            }
        }
    }
    for(int i=1;i<=n*n;i++)ans=max(ans,dis[i]);
}
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>c[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=0;k<4;k++)
    {
        int xc=xx[k]+i,yc=yy[k]+j;
        if(xc<1||xc>n||yc<1||yc>n)continue;
        g[id(i,j)].push_back((qq){id(xc,yc),(c[i][j]==c[xc][yc])?a:b});
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dij(id(i,j));
    cout<<ans;
    return 0;
}
```



---

## 作者：dunko (赞：0)

好多天没写题解了。
##**题目**

自己看看吧[点这里](https://www.luogu.org/problemnew/show/P3057)

##**思路**

不要看它是字符串，其实很水。看完题目了之后先是想到了最短路找最大的一条路径。
突然想起了BFS与最短路之间不可描述的关系，最后蒟蒻打了一个又像SPFA又像BFS的东西。但在写代码时也是要注意好一些小细节！


注意好起点不一定是（1,1）点，还可能是其他点，脑中蹦出来TLE的感觉，看了一眼范围才注意到不必担心。那就开始了打代码的快乐时光。

##**代码**

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
struct node{
    int x,y;
};//存当前的坐标
int n,a,b;long long dis[101][101],ans;
char s[101][101]; int mv[4][2]={{1,0},{-1,0},{0,-1},{0,1}};//扩展节点四个方向
bool mapp[101][101];//标记是否在队列之中
void BFS(int sx,int sy){
    queue<node>que; memset(dis,0x7f7f7f7f,sizeof(dis));
    memset(mapp,0,sizeof(mapp));//注意初始化
    mapp[sx][sy]=1; que.push((node){sx,sy}); dis[sx][sy]=0;
    while(que.size()){//开始了我们的最短路之旅
        node d=que.front(); que.pop(); mapp[d.x][d.y]=0;//取出队首
        for(int i=0;i<4;i++){//扩展节点
            int tx=mv[i][0]+d.x;
            int ty=mv[i][1]+d.y;
            if(tx>0&&tx<=n&&ty>0&&ty<=n){//是否符合地图范围
                int t;
                if(s[tx][ty]==s[d.x][d.y]) t=a;
                else t=b;//看当前与扩展点是否相同
                if(dis[tx][ty]>dis[d.x][d.y]+t){//松弛操作
                    dis[tx][ty]=dis[d.x][d.y]+t;
                    if(mapp[tx][ty]==0) mapp[tx][ty]=1,que.push((node){tx,ty});
                }//不在队列之中要放入队列
            }
        }
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    ans=max(ans,dis[i][j]);//在整个地图中找最大的最短路
}
int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    cin>>s[i][j];//输入
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    BFS(i,j);//不断枚举开始点
    cout<<ans<<endl;//输出
    return 0;
}
```

最后说几句，看到这种题不必担心，不会就暴力点，总是会有分的。但之后有想法来改进那是一定要来尝试一下。

蒟蒻表示又水了一天，开心。

---

## 作者：依依 (赞：0)

spfa最短路
开两个队列分别存储坐标
然后判断两种情况
```c
#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#include<queue>
#define ll long long
#define DB double
#define inf 2147480000
using namespace std;
inline int read()
{
	int x=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*w;
}
const int N=40;
int n,A,B,ans,d[N][N],v[N][N];
int dx[]={0,0,1,-1},dy[]={1,-1,0,0}; 
char a[N][N];
queue<int>qx,qy;
void spfa(int sx,int sy)
{
	for(int i=1;i<=n;++i)
	 for(int j=1;j<=n;++j)
	  d[i][j]=inf,v[i][j]=0;
	qx.push(sx);qy.push(sy);
	d[sx][sy]=0;v[sx][sy]=1;
	while(!qx.empty())
	{
		int fx=qx.front();qx.pop();
		int fy=qy.front();qy.pop();
		v[fx][fy]=0;
		for(int i=0;i<=3;++i)
		{
			int rx=fx+dx[i];
			int ry=fy+dy[i];
			if(rx<1 || rx>n || ry<1 || ry>n) continue;
			if(a[rx][ry]==a[fx][fy])//---A
			{
				if(d[rx][ry]>d[fx][fy]+A)
				{
					d[rx][ry]=d[fx][fy]+A;
					if(!v[rx][ry])
					 qx.push(rx),qy.push(ry),v[rx][ry]=1;
				}
			}else{//---B
			    if(d[rx][ry]>d[fx][fy]+B)
				{
					d[rx][ry]=d[fx][fy]+B;
					if(!v[rx][ry])
					 qx.push(rx),qy.push(ry),v[rx][ry]=1;
				}
			}
		} 
	}
	for(int i=1;i<=n;++i)
	 for(int j=1;j<=n;++j)
	  ans=max(ans,d[i][j]);
} 
int main()
{
	n=read();A=read();B=read();
	for(int i=1;i<=n;++i) scanf("%s",a[i]+1);
	for(int i=1;i<=n;++i)
	 for(int j=1;j<=n;++j)
	  spfa(i,j);
	cout<<ans;
	return 0;
}
```
//看了TOT

---

