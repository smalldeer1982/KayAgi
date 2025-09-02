# [JOI 2017 Final] 足球 / Soccer

## 题目描述

**题目译自 [JOI 2017 Final](https://www.ioi-jp.org/joi/2016/2017-ho/) T4「[サッカー](https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho.pdf) / [Soccer](https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho-en.pdf)」**

> 「假定球滚动时可以穿过其他球员」这句是在未修改数据的前提下，为了严谨我补上的，原题没有提这一点。如果撞到其他球员就停下的话似乎做法不同？

你是 JOI 联赛中一所声名卓著的足球俱乐部的经理。

俱乐部有 $N$ 名球员，编号为 $1\ldots N$。球员们每天都刻苦地进行训练，剑指联赛冠军。足球场可视为一个底为 $W$ 米，高 $H$ 米的长方形，底平行于东西方向，高平行于南北方向。如果某个点向北走 $i$ 米，再向西走 $j$ 米恰好到达球场的西北角，这个点可用坐标 $(i, j)$ 来表示。

练习结束后，你要回收练习用的足球。开始回收时，所有球员都在足球场上，球员 $i (1\leqslant i\leqslant N)$ 位于 $(S_i, T_i)$，球在球员 $1$ 脚下。你正和球员 $N$ 一起站在 $(S_N, T_N)$，并准备回收球。球员们把球传到 $(S_N, T_N)$ 时，你才会回收球。

你可以指挥球员，但某些操作会提升球员的**疲劳度**。一个球员不能同时进行多项操作。  
你可以指挥控球的球员进行如下操作：
* **踢球**。在东西南北四个方向中任选一个，并指定一个正整数 $p$，该球员将球朝指定方向踢出恰好 $p$ 米。**假定球滚动时可以穿过其他球员**。该球员不会移动，且自动停止控球，疲劳度上升 $A\times p+B$。
* **运球**。在东西南北四个方向中任选一个，该球员带球，朝指定方向移动 $1$ 米。该球员仍然控球，疲劳度上升 $C$。
* **停止控球**。该球员的疲劳度不改变。

你可以指挥没有控球的球员进行如下操作：
* **移动**。在东西南北四个方向中任选一个，该球员朝指定方向移动 $1$ 米，疲劳度上升 $C$。
* **控球**。如果该球员所在的位置恰好有球，且没有其他球员控球，该球员才能控球。该球员的疲劳度不改变。

球员和球有可能跑出场外，一个位置上可能有多个球员。  
一天的训练结束后，球员们非常疲惫。你想知道在回收球的过程中，所有球员上升的疲劳度之和的最小值。

## 说明/提示

#### 样例解释 1
在这组样例中，球场、球员、球处于如图所示的状态。图中，黑框空心圆圈表示球员，实心圆表示球，你在 $(6,5)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/7t23chgu.png)

最优解如下：
1. 球员 $1$ 把球向东踢出 $3$ 米。疲劳度上升了 $1\times 3+3=6$，球移动到 $(1,4)$。
2. 球员 $2$ 向南移动 $1$ 米。疲劳度又上升了 $6$。
3. 球员 $2$ 开始控球。
4. 球员 $2$ 向东运球 $1$ 米。疲劳度又上升了 $6$。
5. 球员 $2$ 把球向南踢出 $5$ 米，疲劳度上升了 $1\times 5+3=8$，球移动到 $(6,5)$。

此时，疲劳度之和为 $6+6+6+8=26$。没有更好的方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/x0a9bunu.png)

#### 样例解释 2
在最优解中，不需要踢球。

#### 样例解释 4
注意这组样例中有多个球员在同一位置的情况。

#### 数据范围与提示
对于 $5\%$ 的数据，$N=2$。  
对于另外 $30\%$ 的数据，$N\leqslant 1000, A=0$。  
对于所有数据，$1\leqslant H,W\leqslant 500, 0\leqslant A, B, C\leqslant 10^9, 2\leqslant N\leqslant 10^5, 0\leqslant S_i\leqslant H, 0\leqslant T_i\leqslant W(1\leqslant i\leqslant N), (S_1, T_1)\neq(S_N, T_N)$。

## 样例 #1

### 输入

```
6 5
1 3 6
3
1 1
0 4
6 5```

### 输出

```
26```

## 样例 #2

### 输入

```
3 3
0 50 10
2
0 0
3 3```

### 输出

```
60```

## 样例 #3

### 输入

```
4 3
0 15 10
2
0 0
4 3```

### 输出

```
45```

## 样例 #4

### 输入

```
4 6
0 5 1000
6
3 1
4 6
3 0
3 0
4 0
0 4```

### 输出

```
2020```

# 题解

## 作者：¶凉笙 (赞：14)

## [题解] 「JOI 2017 Final」足球

> 只用**拆三个点！！**
>
> [不一定更好的阅读体验](https://www.cnblogs.com/Liang-sheng/p/15226678.html)

~~不知道为什么题解都是拆成 $6$ 个点的，所谓的“蝴蝶效应”？~~ 

而且，一个人最多控几次球根本就不用关心。

首先并不好 DP，**传递问题**想到建图。

建一层图肯定是不行的，因为有控球和不控球的状态差别，或者说有球滚动和人移动的不同代价，所以需要拆点或者说**建分层图**（个人感觉本质上是一样的）。

因为人的移动本质上是一样的，所以**人带着球的移动**可以当成一层来看。

球滚动的过程也需要考虑，因为代价不同（也就是踢球的代价）。

注意：**球滚动的过程需要分为两层**，横着滚动和竖着滚动，因为**这两个方向是不相通的！**

> 如何从滚动过程跳跃到运球过程

如果状态的第一层定义的是**人运球的过程**，而不是人移动的过程的话，那么从滚动过程的当前点 $(x,y)$ 跳到运球过程的当前点**一定需要人来接**，这个人一定是离 $(x,y)$ 最近的那个球员，所以如果当前点一定要跳状态到运球状态，需要**强制让最近的球员瞬时过来接**。

> 小结

我觉的一大部分人的思路在**独立思考**的情况下应该是这样拆成三个点来进行最短路的，因为人的一般性思维大部分时间是基于增量法的。

何况上下左右真的没必要，拆成三个点思维难度并没有增加。~~反而降低了（？~~

**要有建图的意识！**

目前 Luogu 全站第二，~~欢迎hack~~

> 坑点

坐标是从 $0$ 开始的，一张图有 $(n+1)\times (m+1)$ 个点而不是 $n\times m$ 个。

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename T>
inline T read(){
	T x=0;char ch=getchar();bool fl=false;
	while(!isdigit(ch)){if(ch=='-')fl=true;ch=getchar();}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);ch=getchar();
	}
	return fl?-x:x;
}
#include <queue>
const int maxn = 1e5 + 10;
const int maxm = 505;
#define LL long long
LL A,B,C;
int n,m,k,X[maxn],Y[maxn];
bool vis[maxm][maxm];
int head[maxm*maxm*3],cnt=0;
struct edge{
	int to,nxt;LL w;
}e[maxm*maxm*30];
inline void link(int u,int v,LL w){
	e[++cnt].to=v;e[cnt].nxt=head[u];head[u]=cnt;e[cnt].w=w;
}
LL dis[maxm*maxm*3];
inline int id(int x,int y){
	return x*(m+1)+y;
}
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
#define read() read<int>()
#define Pair pair<LL,int>
#define mp make_pair
bool visit[maxm*maxm*3];
void dij(int s){
	memset(dis,0x3f,sizeof dis);
	priority_queue<Pair,vector<Pair>,greater<Pair> > q;q.push(mp(0,s));
	dis[s]=0;
	while(q.size()){
		int u=q.top().second;q.pop();
		if(visit[u])continue;
		visit[u]=true;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w && !visit[v]){
				dis[v]=dis[u]+e[i].w;
				q.push(mp(dis[v],v));
			}
		}
	}
}
LL dist[maxm][maxm];
void bfs(){
	queue<Pair> q;
	for(int i=1;i<=k;i++)q.push(mp(X[i],Y[i])),dist[X[i]][Y[i]]=0;
	while(q.size()){
		int x=q.front().first,y=q.front().second;q.pop();
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<0 || xx>n || yy<0 || yy>m)continue;
			if(vis[xx][yy] || dist[xx][yy])continue;
			dist[xx][yy]=dist[x][y]+1;
			q.push(mp(xx,yy));
		}
	}
}
int main(){
	n=read();m=read();
	A=read<LL>();B=read<LL>();C=read<LL>();
	k=read();
	for(int i=1;i<=k;i++)X[i]=read(),Y[i]=read(),vis[X[i]][Y[i]]=true;
	bfs();
	for(int x=0;x<=n;x++){
		for(int y=0;y<=m;y++){
			for(int i=0;i<4;i++){
				int xx=x+dx[i],yy=y+dy[i];
				if(xx<0 || xx>n || yy<0 || yy>m)continue;
				link(id(x,y),id(xx,yy),C);
			}
			link(id(x,y),id(x,y)+(n+1)*(m+1),B);
			link(id(x,y),id(x,y)+2*(n+1)*(m+1),B);
		}
	}
	for(int x=0;x<=n;x++){
		for(int y=0;y<=m;y++){
			for(int i=0;i<2;i++){
				int xx=x+dx[i],yy=y+dy[i];
				if(xx<0 || xx>n || yy<0 || yy>m)continue;
				link(id(x,y)+(n+1)*(m+1),id(xx,yy)+(n+1)*(m+1),A);
			}
			link(id(x,y)+(n+1)*(m+1),id(x,y),dist[x][y]*C);
		}
	}
	for(int x=0;x<=n;x++){
		for(int y=0;y<=m;y++){
			for(int i=2;i<4;i++){
				int xx=x+dx[i],yy=y+dy[i];
				if(xx<0 || xx>n || yy<0 || yy>m)continue;
				link(id(x,y)+2*(n+1)*(m+1),id(xx,yy)+2*(n+1)*(m+1),A);
			}
			link(id(x,y)+2*(n+1)*(m+1),id(x,y),dist[x][y]*C);
		}
	}
	dij(id(X[1],Y[1]));
	printf("%lld\n",dis[id(X[k],Y[k])]);
	return 0;
}
```

---

## 作者：闲鱼 (赞：9)

此题带球传球控球的状态转换~~较为复杂~~，我们可以考虑 _拆点_ 。

首先我们发现最优解一定不会出现一个人重复控球（这个……很容易想到吧）

分析每一个坐标可能出现的状态，分为控球和不控球两种情况

而不控球又分为停留在该坐标和滚动经过该坐标两种情况

而滚动又分为上下左右滚

~~口胡完毕~~，总而言之就是一个坐标要拆成**六个点**（据说可以只拆五个点，但是六个点~~可能更加便于理解？~~）

经过~~简单的~~分析，我们可以想到用**p点的坐标 + k * 场地的点数**来表示拆点后的图中某一个点（k为该点的状态序号），可以用**x * (w + 1) + y**表示一个点的位置（x、y分别表示该点的上下坐标和左右坐标，必须要注意一下**坐标可以为0**，所以w要加1）

定义k值为0、1、2、3时表示球正在滚动状态（四个方向），k为4时表示球在该位置停止，k为5时表示球在该位置被控制，连边代价即为状态转换的代价。

从滚动到停止不需要花费疲劳度，从控球到将球踢出需要花费b点疲劳度（因为传球的计算公式为A * p + B，我们不妨将B在球传出时就处理了），而从静止到控球则需要离球最近的球员跑过来捡球。可以预处理对于每个位置曼哈顿距离最近的球员到该点的曼哈顿距离，用dt[i][j]存储。

具体实现用到广搜的思想，代码如下：

```cpp
inline void Manhattan_Distance()
{
    queue<player> q;
    for(register int i = 0;i <= h;i++) for(register int j = 0;j <= w;j++) dt[i][j] = INF;
    for(register int i = 1; i <= n; i++){ dt[P[i].x][P[i].y] = 0; q.push(P[i]); }
    while(!q.empty())
    {
        int x = q.front().x, y = q.front().y;
        q.pop(); vis[x][y] = false;
        for(register int i = 0; i < 4; i++)
        {
            int xx = x + dx[i], yy = y + dy[i];
            if(xx >= 0 && xx <= h && yy >= 0 && yy <= w && dt[xx][yy] > dt[x][y] + 1) {
                dt[xx][yy] = dt[x][y] + 1;
                if(!vis[xx][yy]) {
                    player graph;
                    graph.x = xx, graph.y = yy;
                    q.push(graph);  vis[xx][yy] = true;
                }
            }
        }
    }
}
```
所以对于每一个位置的拆点如下图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/dynannsk.png)

代码大概是这样：

```cpp
add(p + k * sum, p + 4 * sum, 0);
add(p + 5 * sum, p + k * sum, b);
add(p + 4 * sum, p + 5 * sum, c * (ll)dt[i][j]);
```

在不越界的前提下相邻的位置存在球的滚动和运球的操作，于是我们有了下面这样的代码。

```cpp
int xx = i + dx[k], yy = j + dy[k];
if(xx >= 0 && yy >= 0 && xx <= h && yy <= w) {
    int q = id(xx, yy);
    add(p + k * sum, q + k * sum, a);
    add(p + 5 * sum, q + 5 * sum, c);
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/io9qgjmf.png)

传球代价不妨拆成每一个相邻点的移动代价a的累计。

至此这题就被分解成了一个裸的最短路。

下面是完整代码

```cpp
#include <queue>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#define INF 0x3f3f3f3f
#define MAX 0x7f7f7f7f7f7f7f7f
using namespace std;
typedef long long ll;
const int W = 505;
const int N = 100005;

struct Node{ int x; ll y; };
struct player{ int x, y; }P[N];
struct Edge{ int to, next; ll weight; }edge[W * W * 36];
struct cmp{ bool operator()(Node x, Node y){ return x.y > y.y; } };

ll dis[W * W * 6], ans = MAX;
bool vis[W][W], vis2[W * W * 6];
int h, w, a, b, c, n, sum, cnt = 1;
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int head[W * W * 6], dt[W][W];

template<typename T> inline void read(T &x)
{
    x = 0; char ch = getchar(); bool flag = false;
    while(ch < '0' || ch > '9'){if(ch == '-') flag = true; ch = getchar();}
    while('0' <= ch && ch <= '9'){x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    if(flag) x = -x;
}

inline void add(int u, int v, ll w)
{
    edge[cnt].to = v, edge[cnt].weight = w;
    edge[cnt].next = head[u], head[u] = cnt++;
}

inline ll Min(ll x, ll y){ return x < y ? x : y; }
inline int id(int x, int y){ return x * (w + 1) + y; } //用一个数字表示一个平面坐标 

inline void Manhattan_Distance()
{
    queue<player> q;
    for(register int i = 0; i <= h; i++) for(register int j = 0; j <= w; j++) dt[i][j] = INF;
    for(register int i = 1; i <= n; i++){ dt[P[i].x][P[i].y] = 0; q.push(P[i]); }
    while(!q.empty())
    {
        int x = q.front().x, y = q.front().y;
        q.pop(); vis[x][y] = false;
        for(register int i = 0; i < 4; i++)
        {
            int xx = x + dx[i], yy = y + dy[i];
            if(xx >= 0 && xx <= h && yy >= 0 && yy <= w && dt[xx][yy] > dt[x][y] + 1) {
                dt[xx][yy] = dt[x][y] + 1;
                if(!vis[xx][yy]) {
                    player graph;
                    graph.x = xx, graph.y = yy;
                    q.push(graph);  vis[xx][yy] = true;
                }
            }
        }
    }
}

inline void Dijkstra()
{
    priority_queue<Node, vector<Node>, cmp> q;
    for(register int i = 0; i <= W * W * 6; i++) dis[i] = MAX;
    Node graph; graph.x = id(P[1].x, P[1].y) + 4 * sum, graph.y = 0;
    q.push(graph); dis[id(P[1].x, P[1].y) + 4 * sum] = 0;
    while(!q.empty())
    {
        int x = q.top().x;
        q.pop(); if(!vis2[x])
        {
            vis2[x] = true;
            for(register int i = head[x]; i != 0; i = edge[i].next)
            {
                int v = edge[i].to;
                if (dis[v] > dis[x] + edge[i].weight) {
                    dis[v] = dis[x] + edge[i].weight; Node graph;
                    graph.x = v, graph.y = dis[v];
                    q.push(graph);
                }
            }
        }
    }
}

int main()
{
    read(h), read(w), read(a), read(b), read(c), read(n);
    for(register int i = 1; i <= n; i++) read(P[i].x), read(P[i].y);
    Manhattan_Distance();
    sum = (w + 1) * (h + 1); //因为横纵坐标可以为0，所以要+1
    //通过k * sum的表示方法拆点 
    for(register int i = 0; i <= h; i++)
    {
        for(register int j = 0; j <= w; j++)
        {
            int p = id(i, j);
            for(register int k = 0; k < 4; k++)
            {
                add(p + k * sum, p + 4 * sum, 0); //球从滚动状态（无人控球）到停止 
                add(p + 5 * sum, p + k * sum, b); //球从静止状态（有人控球）到将球传出 
                add(p + 4 * sum, p + 5 * sum, c * (ll)dt[i][j]); //离球最近的球员（曼哈顿距离）跑过来控球 int xx = i + dx[k], yy = j + dy[k];
                if(xx >= 0 && yy >= 0 && xx <= h && yy <= w) {
                    int q = id(xx, yy);
                    add(p + k * sum, q + k * sum, a); //球从一个位置按照其方向滚到相邻的位置（传球） 
                    add(p + 5 * sum, q + 5 * sum, c); //球从一个位置按照其方向滚到相邻的位置（带球） 
                }
            }
        }
    }
    Dijkstra();
    for(register int i = 0; i < 6; i++) {
        ans = Min(ans, dis[id(P[n].x, P[n].y) + i * sum]);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：pipiispig (赞：7)

观察几个性质：

1.一个人最多控一次球（至少进行了传球或者带球）；

2.一个人的路线一定是：（无球跑动->）（带球->）传球/带球（带括号表示非必选项）；

那么当一个球停在了位置(x,y)，那么在某种最优解中，移动至(x,y)并继续控球的一定是离(x,y)
曼哈顿距离最小的一个。

那么我们可以把一个位置(x,y)拆点：（设总点数为m）
设为(x,y)k（k∈{0,1,2,3,4,5}）

其中，(x,y)4
表示球到了(x,y)，且没有人控球状态小最小疲惫值；(x,y)5表示球到了(x,y)，且有人在控球状态下的最小疲惫值；(x,y)0,1,2,3

分别表示球正在向上下左右滚动状态下的最小疲惫值。则就可以建图跑最短路。

那其中有一个代价，就是一个人传球时，代价为a∗p+b（a,b是常数，p是传球的距离），此时我们把a∗p的贡献分配到每条边上，b
的话也是可以分配到某条边上的。

最终跑一个dij最短路即可。（常数挺大的）

#####
std:
 ```c++
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>
#define ll long long
const int N = 251005;
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
bool vis[505][505], Vis[N * 6];
int minn[505][505];
int x[100005], y[100005];
int n;
ll dis[N * 6], ans = 0x7f7f7f7f7f7f7f7f;
int h, w, a, b, c, m;
struct node {
    int x, y;
};
struct Node {
    int x;
    ll y;
};
struct cmp {
    bool operator()(Node x, Node y) { return x.y > y.y; }
};
using namespace std;
int e, ver[N * 6 * 6], head[N * 6], nexts[N * 6 * 6];
ll edge[N * 6 * 6];
inline void add(int x, int y, ll z) { ver[++e] = y, nexts[e] = head[x], head[x] = e, edge[e] = z; }
inline int id(int x, int y) { return x * (w + 1) + y; }
inline void bfs() {
    queue<node> q;
    memset(minn, 0x3f, sizeof(minn));
    for (int i = 1; i <= m; i++) {
        minn[x[i]][y[i]] = 0;
        q.push((node){ x[i], y[i] });
    }
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
        vis[x][y] = false;
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx < 0 || yy < 0 || xx > h || yy > w)
                continue;
            if (minn[xx][yy] > minn[x][y] + 1) {
                minn[xx][yy] = minn[x][y] + 1;
                if (!vis[xx][yy]) {
                    q.push((node){ xx, yy });
                    vis[xx][yy] = true;
                }
            }
        }
    }
}
inline void build() {
    n = (w + 1) * (h + 1);
    for (int i = 0; i <= h; i++)
        for (int j = 0; j <= w; j++) {
            int p = id(i, j);
            for (int k = 0; k < 4; k++) {
                add(p + k * n, p + 4 * n, 0);
                add(p + 4 * n, p + 5 * n, 1ll * c * minn[i][j]);
                add(p + 5 * n, p + k * n, b);
                int xx = i + dx[k];
                int yy = j + dy[k];
                if (xx < 0 || yy < 0 || xx > h || yy > w)
                    continue;
                int q = id(xx, yy);
                add(p + k * n, q + k * n, a);
                add(p + 5 * n, q + 5 * n, c);
            }
        }
}
inline void Dij() {
    priority_queue<Node, vector<Node>, cmp> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[id(x[1], y[1]) + 4 * n] = 0;
    q.push((Node){ id(x[1], y[1]) + 4 * n, 0 });
    while (!q.empty()) {
        int x = q.top().x;
        int y = q.top().y;
        q.pop();
        if (Vis[x])
            continue;
        Vis[x] = true;
        for (int i = head[x]; i; i = nexts[i]) {
            int v = ver[i];
            if (dis[v] > dis[x] + edge[i]) {
                dis[v] = dis[x] + edge[i];
                q.push((Node){ v, dis[v] });
            }
        }
    }
}
int main() {
    scanf("%d%d", &h, &w);
    scanf("%d%d%d", &a, &b, &c);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%d%d", &x[i], &y[i]);
    bfs();
    build();
    Dij();
    for (int i = 0; i < 6; i++) {
        ans = min(ans, dis[id(x[m], y[m]) + i * n]);
    }
    printf("%lld\n", ans);
    return 0;
}
```
好像也不难是不是，就是代码长度大，有点难调！

---

## 作者：daniEl_lElE (赞：6)

我们考虑球的状态。有两种。目前在自由滑行或在人脚下。

考虑每一步球可以怎么做。

* 如果他在自由滑行，那么可以向相同方向走一步（其实可以只考虑上下，左右两种移动情况），疲劳度我们延迟计算，那么分担到这里疲劳度就是 $A$；
* 如果他在自由滑行，那么可以在这个位置停下来，转换到在人脚下的状态。此时可以看作要喊一个人过来踢它。疲劳度为 $d_{pos}\times c$，其中 $d_{pos}$ 表示距离 $pos$ 位置最近的人距离该位置的距离。
* 如果他在人脚下，那么可以随意向任意方向走一步。这步的疲劳度是 $C$。
* 如果他在人脚下，那么可以从这个位置开始滑行，也就是转换到自由滑行状态。这步的疲劳度是 $B$。

对所有位置的三种情况进行图论建模，跑一遍最短路即可。总复杂度 $O(N+WH(\log W+\log H))$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define s(i,j) ((i-1)*w+j)
using namespace std;
vector<pair<int,int>> vc[1000005];
int dist[505][505],f[1000005],vis[1000005];
signed main(){
	memset(dist,1,sizeof(dist));
	int h,w; cin>>h>>w; h++,w++;
	int a,b,c; cin>>a>>b>>c;
	int n; cin>>n;
	memset(f,1,sizeof(f));
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	int s,t;
	for(int i=1;i<=n;i++){
		cin>>s>>t;
		s++,t++;
		dist[s][t]=0;
		if(i==1) f[s(s,t)]=0,pq.push(make_pair(0,s(s,t)));
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			dist[i+1][j]=min(dist[i][j]+1,dist[i+1][j]);
			dist[i][j+1]=min(dist[i][j]+1,dist[i][j+1]);
		}
	}
	for(int i=h;i>=1;i--){
		for(int j=w;j>=1;j--){
			dist[i-1][j]=min(dist[i][j]+1,dist[i-1][j]);
			dist[i][j-1]=min(dist[i][j]+1,dist[i][j-1]);
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			vc[s(i,j)+h*w].push_back(make_pair(s(i,j),dist[i][j]*c));
			vc[s(i,j)+2*h*w].push_back(make_pair(s(i,j),dist[i][j]*c));
			vc[s(i,j)].push_back(make_pair(s(i,j)+h*w,b));
			vc[s(i,j)].push_back(make_pair(s(i,j)+2*h*w,b));
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<w;j++){
			vc[s(i,j)].push_back(make_pair(s(i,j+1),c));
			vc[s(i,j+1)].push_back(make_pair(s(i,j),c));
			vc[s(i,j)+h*w].push_back(make_pair(s(i,j+1)+h*w,a));
			vc[s(i,j+1)+h*w].push_back(make_pair(s(i,j)+h*w,a));
		}
	}
	for(int i=1;i<h;i++){
		for(int j=1;j<=w;j++){
			vc[s(i,j)].push_back(make_pair(s(i+1,j),c));
			vc[s(i+1,j)].push_back(make_pair(s(i,j),c));
			vc[s(i,j)+2*h*w].push_back(make_pair(s(i+1,j)+2*h*w,a));
			vc[s(i+1,j)+2*h*w].push_back(make_pair(s(i,j)+2*h*w,a));
		}
	}
	while(!pq.empty()){
		int now=pq.top().second; pq.pop();
		if(vis[now]) continue; vis[now]=1;
		for(auto v:vc[now]){
			if(f[v.first]>f[now]+v.second){
				f[v.first]=f[now]+v.second;
				pq.push(make_pair(f[v.first],v.first));
			}
		}
	}
	cout<<f[s(s,t)];
	return 0;
}
```

---

## 作者：_Dreamer_ (赞：4)

## P5100 [JOI 2017 Final]足球

显然 每个人最多控球一次 因为如果控多次球的话为什么不一次控球控到底呢？

那么对于球来说 它的行动就是 一个离他最近的人跑过来控球 然后把球踢出去 另一个距离球最近的人又跑过来控球……

对于每个可能的位置存在六种可能的情况

1. 向上滚动 
2. 向下滚动
3. 向左滚动
4. 向右滚动
5. 被每个球员控球
6. 在某个位置且不是被控的状态

对于 1~4 种情况向它对应的方向的下一个点连一条代价为 a 的边 表示继续滚动

对于 1~4 种情况向这个点第6种情况连一条代价为 0 的边 表示从滚动状态停下来了

对于 5 向这个点的1~4 各连接一条代价为b的边 表示被某个球员踢起来了

对于 5 向四个方向的下一个点连一条代价为c的边 表示一个球员带着球跑动

对于 6 向第5种情况连一条代价为 c*（离球最近的队员的曼哈顿距离）表示一个球员跑过来控球了


------------
到这里 这个题目需要我们 bfs 处理出曼哈顿距离

对于每个点枚举上述连边可能

最后跑一遍Dijkstra求出到最后一个球员的最短路就可以了

答案就是上面六种情况的最小值


```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,a,b,c,n,m;
const int N=300005;
//存边 
int head[N*10],ver[N*40],nxt[N*40],cnt;
long long edge[N*40];
void add(int x,int y,long long z)
{
	ver[++cnt]=y;
	edge[cnt]=z;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
//曼哈顿距离 
int x[100005],y[100005];
int dis[505][505];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int v[505][505];
struct node {int x,y;};
void bfs()
{
	queue<node> q;
	memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=m;i++)
	{
		dis[x[i]][y[i]]=0;
		q.push((node){x[i],y[i]});
	}
	while(!q.empty())
	{
		int x=q.front().x;
		int y=q.front().y;
		q.pop();
		for(int i=0;i<4;i++)
		{
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(nx<0||ny<0||nx>h||ny>w)continue;
			if(dis[nx][ny]>dis[x][y]+1)
			{
				dis[nx][ny]=dis[x][y]+1;
				q.push((node){nx,ny});
			}
		}
	}
}
//id
int id(int x,int y){return x*(w+1)+y;}
//建图 
void build()
{
	n=(w+1)*(h+1);
	for(int i=0;i<=h;i++)
	{
		for(int j=0;j<=w;j++)
		{
			int x=id(i,j);
//			一共拆了6个点
//			0,1,2,3代表球向四个方向滚动
//			4代表求在这里停下没有人控球
//			5代表有人控球 
			for(int k=0;k<4;k++)
			{
				add(x+k*n,x+4*n,0);//球在这个位置从滚动停下来
				add(x+5*n,x+k*n,b);//在有人控球的情况下踢球 
				int nx=i+dx[k];
				int ny=j+dy[k];
				if(nx<0||ny<0||nx>h||ny>w)continue;
				int y=id(nx,ny);
				add(x+k*n,y+k*n,a);//球向前滚动 
				add(x+5*n,y+5*n,c);//一个人控球向前 
			}
			add(x+4*n,x+5*n,1ll*c*dis[i][j]);//一个球员跑过来控球 
		}
	}
}
//dij
struct Node
{
	int x;
	long long d;
	bool operator<(const Node& B)const
	{
		return d>B.d;
	}
};
long long d[N*10];
bool V[N*10];
long long ans=0x7f7f7f7f7f7f7f7f;
void dij()
{
	priority_queue<Node>q;
	memset(d,0x3f,sizeof d);
	d[id(x[1],y[1])+4*n]=0;
	q.push((Node){id(x[1],y[1])+4*n,0});
	while(!q.empty())
	{
		int x=q.top().x;
		q.pop();
		if(V[x])continue;
		V[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=ver[i];
			if(d[y]>d[x]+edge[i])
			{
				d[y]=d[x]+edge[i];
				q.push((Node){y,d[y]});
			}
		}
	}
}

int main()
{
	scanf("%d%d",&h,&w);
	scanf("%d%d%d",&a,&b,&c);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	bfs();
	build();
	dij();
	for(int i=0;i<6;i++)
	{
		ans=min(ans,d[id(x[m],y[m])+i*n]);
	}
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：Le0Chan (赞：3)

这篇题解里有对做题思路的详细阐述，对于其他题解中分各种各样层图的思路来源进行了小小的总结。

方便起见，称原题中的 $H,W$ 为 $n,m$。

首先考虑什么样的策略是最优的。一个球员多次控球显然不优。换句话说，他要多次把球踢出去然后追上再踢出去，浪费了踢出去后比他离球近的球员。

也就是说，我们可以大致刻画出收球的过程：

$1$ 号踢出球/运球到某个地方。

$\to$ 离这个地方最近的球员跑步到球这里，然后踢出球/运球到某个地方。

$\to \dots$

$\to$ 球自己滚/被运到终点，注意不一定是 $n$ 号球员的位置，因为 $n$ 号球员可能去接球了，不在他本来的位置。

也就是说每个球员拿到球后只有 **两种** 本质不同的选择：运球和踢球。从球的角度看，球也只有**两种**本质不同的选择：自己滚和被运，其中被运和上面球员运球是一样的。

综上，考虑建三层图：一层表示球员在运球，一层表示球员在跑步，一层表示球在滚。

考虑第一层如何连边：第一层是球员运球，走一步消耗 $C$，所以任意相邻两点连权值为 $C$ 的边。

第二层是球员跑步，同理任意相邻两点连权值为 $C$ 的边。

第三层是球自己滚，任意相邻两点连权值 $A$ 的边。

发现第一层和第二层权值一样，不如合并，这样就成了两层图。

整理一下：

第一层表示球员在**控球**/球员在跑步，任意相邻两点连权值 $C$ 的边。

第二层表示球在自己滚，任意相邻两点连权值 $A$ 的边。

第一层向第二层走是什么呢？球从被人拿捏到自己滚，不就是被踢出去了吗？所以，同一个地点，第一层向第二层连权值为 $B$ 的边。

第二层向第一层走是什么呢？球从自己滚到被球员抓住，不就是离这个点最近的球员跑过来接住了球吗？所以：同一个地点，第一层向第二层连权值为 $mn_{i,j}\times C$ 的边。这里的 $mn_{i,j}$ 表示到 $(i,j)$ 最近的球员到 $(i,j)$ 的曼哈顿距离。（就是球员跑过来的距离）

$mn_{i,j}$ 怎么求呢，考虑 bfs。先将所有球员加进队列。然后向四个方向拓展，跑边权为 $1$ 的 bfs。每个点只会被算到 $1$ 遍，时间复杂度 $O(nm)$。

然后是不是在分层图上跑最短路就行了呢？戳啦，再看看第二层，球自己滚，但是球一次只能朝一个方向滚，如果只建一层相当于球一次可以四个方向随便乱滚。

那怎么办？把第二层图拆成四层（代表四个方向）？当然可以，但是仔细想想，只拆成两层行不行呢？上下滚拆一层，左右滚拆一层。

这样真的是对的吗？实际上是对的，因为这样做可能不对的原因是球滚**回头路**，比如在一次滚动中先向前滚，再向后滚。但是这样一定**不如**直接滚优啊！我们跑的是**最短路**！所以就可以放心的把第二层拆成两层就好啦！

一共 $nm$ 个点。（实际上是 $(n+1)(m+1)$ 个，下标从 $0$ 开始）相邻两个都要连，一共三层图，层与层也要连。总的边数是 $nm$ 级别的。如果使用堆优化的 dijkstra，时间复杂度是 $O(nm\log_2{nm})$

我比较菜，代码实现很丑陋，建议学习别的大佬的题解。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define mk make_tuple
#define tii tuple<int,int,int>
#define LL long long
#define PII pair<int,LL>
#define pii pair<int,int>
#define fi first
#define se second

const LL inf=4e18;
const int K=1e5+5;
const int N=505;

int n,m,k,ncnt,s,t;
LL A,B,C,ans=inf;
int xx[K],yy[K],mn[N][N];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
bool vis[N*N*4];
LL dis[N*N*4];

struct node{
	int x,y,f;LL ds;//f是层数 
	bool operator<(const node &x)const{
		return ds>x.ds;
	}
};

tii a[500*500*4];

map<tii,int> mp;

int id(int x,int y,int f){
	if(!mp[mk(x,y,f)]){
		mp[mk(x,y,f)]=++ncnt;
		a[ncnt]=mk(x,y,f);
	}
	return mp[mk(x,y,f)];
}

tii getpos(int x){
	return a[x];
}

bool ck(int x,int y){
	if(x>=0&&y>=0&&x<=n&&y<=m) return 1;
	return 0;
}

vector<PII> g[505*505*4];

void add(int x,int y,LL w){
	g[x].push_back({y,w});
}

void bfs(){//求解 mn 数组 
	queue<pii> q;
	for(int i=1;i<=k;i++){
		q.push({xx[i],yy[i]});
		mn[xx[i]][yy[i]]=0;
	}
	while(!q.empty()){
		int x=q.front().fi,y=q.front().se;q.pop();
		for(int i=0;i<4;i++){
			int nx=dx[i]+x,ny=dy[i]+y;
			if(ck(nx,ny)){
				if(mn[nx][ny]==0x3f3f3f3f){
					mn[nx][ny]=mn[x][y]+1;
					q.push({nx,ny});
				}
			}
		}
	}
}

void init(){
	for(int x=0;x<=n;x++){
		for(int y=0;y<=m;y++){
			for(int i=0;i<4;i++){
				int nx=dx[i]+x;
				int ny=dy[i]+y;
				if(ck(nx,ny)){
					add(id(x,y,0),id(nx,ny,0),C);//球员控球 
				}
			}
			for(int i=0;i<2;i++){
				int nx=dx[i]+x;
				int ny=dy[i]+y;
				if(ck(nx,ny)){
					add(id(x,y,1),id(nx,ny,1),A);//球自己前后滚 
				}
			} 
			for(int i=2;i<4;i++){
				int nx=dx[i]+x;
				int ny=dy[i]+y;
				if(ck(nx,ny)){
					add(id(x,y,2),id(nx,ny,2),A);//球自己左右滚 
				}
			}
			add(id(x,y,0),id(x,y,1),B);//球从球员脚下飞出去了 
			add(id(x,y,0),id(x,y,2),B);
			add(id(x,y,1),id(x,y,0),mn[x][y]*C);//球员跑过来接球 
			add(id(x,y,2),id(x,y,0),mn[x][y]*C);
		}
	}
}

void dijk(){
	priority_queue<node> q;
	for(int i=1;i<=ncnt;i++){
		dis[i]=inf;
	}
	dis[id(s,t,0)]=0;
	q.push((node){s,t,0,0});
	while(!q.empty()){
		int x=q.top().x,y=q.top().y,f=q.top().f;
		q.pop();
		int nm=id(x,y,f);
		if(vis[nm]) continue;
		vis[nm]=1;
		for(auto z:g[nm]){
			int y=z.fi;LL w=z.se;
			if(dis[y]>dis[nm]+w){
				dis[y]=dis[nm]+w;
				auto as=getpos(y);
				q.push({get<0>(as),get<1>(as),get<2>(as),dis[y]});
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>A>>B>>C>>k;
	memset(mn,0x3f,sizeof(mn));
	for(int i=1;i<=k;i++){
		cin>>xx[i]>>yy[i];
		if(i==1) s=xx[i],t=yy[i];
	}
	bfs();
	init();
	dijk();
	ans=min(min(ans,dis[id(xx[k],yy[k],0)]),min(dis[id(xx[k],yy[k],1)],dis[id(xx[k],yy[k],2)]));
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：Zheng_iii (赞：1)

## 题意简介

在二维网格平面上有 $N$ 个球员，球最初位于第 $1$ 个球员处。我们需要将球转移到第 $N$ 个球员处，求所有球员疲劳度之和的最小值。

持球的球员可以选择踢球或运球，不持球的球员只能进行移动，踢球时可以从东南西北中选定一个方向将球踢出 $p$ 米，所提升的疲劳度为 $A \times p + B$，且球滚动时可以穿过其它球员。

运球以及移动时可以从东南西北中选定一个方向前进 $p$ 米，所提升的疲劳度为 $C \times p$。

一个球员控球以及停止控球都不会对该球员的疲劳度造成影响。

## 前置知识

这道题是一道比较明显的分层图，我下面将会讲解什么是分层图以及分层图问题的解题思路。此外你还需要知道一种求解单源最短路问题的算法，在这里我就不阐述了。

分层图，顾名思义就是一张有很多层的图（）。

每一层可以看作原图的一个“副本”，但不同层之间通过特定的边连接，这些边代表了某些**特殊操作**或**状态转移**。通过这种方式，我们可以将复杂的问题转化为在分层图上求解最短路、连通性等经典图论问题。

分层图中的每一层对应原图的一种**状态**或**阶段**，层与层之间的边代表了**状态转移**，即进行某种特殊操作后从当前状态进入下一状态。

- 普通操作（如原图的边）通常在同一层内连接节点。
- 特殊操作（如跳过边、反向边、改变权值等）通过**跨层边**实现。

例如在[飞行路线](https://www.luogu.com.cn/problem/P4568)一题中，每一层表示已使用的特权次数。

我们建出图来的效果就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/fz5jfonj.png)

然后我们建 $k$ 层相同的图跑最短路就好了。

相信看到这你已经明白分层图的含义以及大致思路了。

那接下来我们就步入正题吧。

## 解题思路

其实做这道题之前，如果你做过[回家的路](https://www.luogu.com.cn/problem/P3831)这道题，那你会发现这两道题在球滚动的不同方向的处理上有异曲同工之妙，我们就可以把球竖着滚动和横着滚动的状态分别建出两层图，只有球被人拦截到我们才能改变球的滚动方向。

此时我们对于这道题就有大致的思路了，建三层图，一层表示人正在运球的状态，剩下的两层表示球不同滚动方向的状态。

此外我们还需要预处理出每个点到最近球员的曼哈顿距离，因为我们每次需要让离球最近的人去捡球，一个 BFS 就可以解决了。

BFS 的代码如下。

```cpp
il void bfs() {
    queue<node> q;
    memset(mhd, 0x3f, sizeof(mhd));
    for(int i=1; i<=n; i++)
    {
        mhd[s[i]][t[i]] = 0;
        q.push({s[i], t[i]});
    }
    while(!q.empty())
    {
        node u = q.front(); q.pop();
        int x = u.x, y = u.y;
        for(int k=1; k<=4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if(nx<0 || nx>h || ny<0 || ny>w) continue;
            if(mhd[nx][ny] > mhd[x][y] + 1)
            {
                mhd[nx][ny] = mhd[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}
```

建图的代码如下。

```cpp
il void build()
{
    int mx = (w+1)*(h+1);
    for(int i = 0;i <= h;i++)
        for(int j = 0;j <= w;j++)
        {
            int u = p(i,j);
            for(int k = 1;k <= 4;k++)
            {
                int x = i+dx[k];
                int y = j+dy[k];
                if(x<0||x>h||y<0||y>w) continue;
                int v = p(x,y);
                E[u].emplace_back(e{v,C});
            }
            E[u].emplace_back(e{u+mx,B});
            E[u].emplace_back(e{u+mx*2,B});
        }

    for(int i = 0;i <= h;i++)
        for(int j = 0;j <= w;j++)
        {
            int u = p(i,j);
            for(int k = 1;k <= 2;k++)
            {
                int x = i+dx[k];
                int y = j+dy[k];
                if(x<0||x>h||y<0||y>w) continue;
                int v = p(x,y);
                E[u+mx].emplace_back(e{v+mx,A});
            }
            E[u+mx].emplace_back(e{u,mhd[i][j]*C});
            for(int k = 3;k <= 4;k++)
            {
                int x = i+dx[k];
                int y = j+dy[k];
                if(x<0||x>h||y<0||y>w) continue;
                int v = p(x,y);
                E[u+mx*2].emplace_back(e{v+mx*2,A});
            }
            E[u+mx*2].emplace_back(e{u,mhd[i][j]*C});
        }
}
```

初始时球处于第一层，结束时球也需要处于第一层，此时我们求解这两个点的最短路即可。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define debug(a) cout<<#a<<"="<<a<<'\n';
#define il inline
#define Coded_By_Zheng_iii 0

using namespace std;
using ll = long long;
using ull = unsigned long long;
#define int ll//不开long long见祖宗

const int N = 1e5+10;
const int M = 510;

const int dx[] = {0,0,0,-1,1};
const int dy[] = {0,1,-1,0,0};

struct e{
    int to,w;
};

struct node{
    int x,y;
};

vector<e> E[M*M*4];
int n,h,w,A,B,C,s[N],t[N],mhd[M][M];

il int p(int x,int y){return x*(w+1)+y;}

il void build()
{
    int mx = (w+1)*(h+1);
    for(int i = 0;i <= h;i++)
        for(int j = 0;j <= w;j++)
        {
            int u = p(i,j);
            for(int k = 1;k <= 4;k++)
            {
                int x = i+dx[k];
                int y = j+dy[k];
                if(x<0||x>h||y<0||y>w) continue;
                int v = p(x,y);
                E[u].emplace_back(e{v,C});
            }
            E[u].emplace_back(e{u+mx,B});
            E[u].emplace_back(e{u+mx*2,B});
        }

    for(int i = 0;i <= h;i++)
        for(int j = 0;j <= w;j++)
        {
            int u = p(i,j);
            for(int k = 1;k <= 2;k++)
            {
                int x = i+dx[k];
                int y = j+dy[k];
                if(x<0||x>h||y<0||y>w) continue;
                int v = p(x,y);
                E[u+mx].emplace_back(e{v+mx,A});
            }
            E[u+mx].emplace_back(e{u,mhd[i][j]*C});
            for(int k = 3;k <= 4;k++)
            {
                int x = i+dx[k];
                int y = j+dy[k];
                if(x<0||x>h||y<0||y>w) continue;
                int v = p(x,y);
                E[u+mx*2].emplace_back(e{v+mx*2,A});
            }
            E[u+mx*2].emplace_back(e{u,mhd[i][j]*C});
        }
}

il void bfs() {
    queue<node> q;
    memset(mhd, 0x3f, sizeof(mhd));
    for(int i=1; i<=n; i++)
    {
        mhd[s[i]][t[i]] = 0;
        q.push({s[i], t[i]});
    }
    while(!q.empty())
    {
        node u = q.front(); q.pop();
        int x = u.x, y = u.y;
        for(int k=1; k<=4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if(nx<0 || nx>h || ny<0 || ny>w) continue;
            if(mhd[nx][ny] > mhd[x][y] + 1)
            {
                mhd[nx][ny] = mhd[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int dis[M*M*4];
bool vs[M*M*4];

struct pr{
    int u,d;
};
priority_queue<pr> q;

il bool operator<(const pr &a,const pr &b){
    return a.d > b.d;
}

il void dij(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    q.push(pr{s,dis[s]});
    while(!q.empty()){
        pr x = q.top();
        q.pop();
        int u = x.u;
        if(vs[u])continue;
        vs[u] = 1;
        for(e ee : E[u]){
            int v = ee.to;
            int w = ee.w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                q.push({v,dis[v]});
            }
        }
    }
}

signed main(){
	// freopen("test.in","r",stdin);
	// freopen("test.out","w",stdout);
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
    cin>>h>>w>>A>>B>>C>>n;
    for(int i = 1;i <= n;i++)
        cin>>s[i]>>t[i];

    bfs();//预处理曼哈顿距离
    build();//建图
    dij(p(s[1],t[1]));//跑最短路

    cout<<dis[p(s[n],t[n])];

	return Coded_By_Zheng_iii;
}

```

---

## 作者：The_BJX (赞：1)

不愧是本子国，题目真会玩。

------------

看到求最小代价，还有格子形状的地图，想到了建图然后求最短路径。

怎么建图呢？根据一些玄学经验，如果难以直接转化为图，一般可以拆点，构造分层图。

首先拆出人运球的一层（$0$层），因为人运球的代价和球自己滚的代价不一样，并且这两种状态互相转化代价不为 $0$。

然后把球滚的一层拆成两层，上下滚（$1$层）和左右（$2$层），因为球滚动中不能随意拐弯。

考虑如何构造跨层电梯。

从运球到传出去需要开一脚的代价 $B$。

设 $(i,j)$ 最近的球员赶过来的步数为 $mindist_{i,j}$。

接球需要最近的球员火速赶过来，即代价为 $mindist_{i,j}\times C$。

图示。

![](https://cdn.luogu.com.cn/upload/image_hosting/25eylaxz.png)

$$\color{grey}{\tiny\text{抱歉 1 层和 2 层放反了，你们知道就好。}}$$

所以建图就是这样的：

* $0$ 层建网格图，所有代价为 $C$。

* $1$ 层建只有上下边的图。所有代价为 $A$。

* $2$ 层建只有左右边的图。所有代价为 $A$。

* $0$ 到 $1,2$ 层点内建单向边，代价为 $B$。

* $1,2$ 到 $0$ 层点内建单向边，代价为 $mindist_{i,j}\times C$。

开始用一个 BFS 预处理 $mindist$ 数组即可。

什么东西都可以看代码知道。

```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#define int long long
#define MAXPLAYERS 100010
#define MLEN 510
using namespace std;
struct edge
{
    int b;
    int next;
    int w;
} e[4001000];
int tot;
int head[4000010];
void add(int a, int b, int c)
{
    e[++tot].b = b;
    e[tot].next = head[a];
    head[a] = tot;
    e[tot].w = c;
}
void cadd(int u, int v, int w)
{
    add(u, v, w);
    add(v, u, w);
}
int n, w, h;
int A,B,C;
int read()
{
    char ch=getchar();
    int x=0,cf=1;
    while(ch<'0'||ch>'9') {if(ch=='-') cf=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*cf;
}
struct block{
    int S;
    int T;
    block operator+(block b)
    {
        return block{S+b.S,T+b.T};
    }
}players[MAXPLAYERS];//存储一个坐标。
int mapping[MLEN][MLEN][3];
int mindist[MLEN][MLEN];//最近的球员赶过来的步数

//广搜处理mindist
int shiftx[4]={1,0,-1,0};
int shifty[4]={0,1,0,-1};
void get_Mindist()
{
    memset(mindist,0x3f,sizeof(mindist));
    queue<block> q;//用于BFS
    for(int i = 1; i <= n; i++)
    {
        mindist[players[i].S][players[i].T]=0;
        q.push(players[i]);
    }
    while(q.size())
    {
        block cur=q.front();
        q.pop();
        for(int i = 0;i<4;i++)
        {
            if(0<=cur.S+shiftx[i]&&cur.S+shiftx[i]<=h)
                if(0<=cur.T+shifty[i]&&cur.T+shifty[i]<=w)
                    if(mindist[cur.S+shiftx[i]][cur.T+shifty[i]]>mindist[cur.S][cur.T]+1)
                    {
                        mindist[cur.S+shiftx[i]][cur.T+shifty[i]]
                            =mindist[cur.S][cur.T]+1;
                        q.push(block{cur.S+shiftx[i],cur.T+shifty[i]});
                    }
        }
    }
    // for(int i = 0; i <= h; i++)
    // {
    //     for(int j = 0; j <= w; j++)
    //         cout << mindist[i][j]<<" ";
    //     cout << endl;
    // }    
    
}
//得到分层图所有点的映射
int tot_count;
void get_Mapping()
{
    //0层，运球
    for(int i = 0; i <= h+1; i++)
        for(int j = 0; j <= w+1; j++)
            mapping[i][j][0]=++tot_count;
    //1层，上下踢球，沿第一维
    for(int i = 0; i <= h+1; i++)
        for(int j = 0; j <= w+1; j++)
            mapping[i][j][1]=++tot_count;
    //2层，左右踢球，沿第二维
    for(int i = 0; i <= h+1; i++)
        for(int j = 0; j <= w+1; j++)
            mapping[i][j][2]=++tot_count;
}

void linkup()
{
    //运球
    for(int i = 0; i <= h; i++)
        for(int j = 0; j <= w; j++)
        {
            cadd(mapping[i][j][0],mapping[i][j+1][0],C);
            cadd(mapping[i][j][0],mapping[i+1][j][0],C);
        }
    //上下踢
    for(int i = 0; i <= h; i++)
        for(int j = 0; j <= w; j++)
            cadd(mapping[i][j][1],mapping[i+1][j][1],A);
    //左右踢
    for(int i = 0; i <= h; i++)
        for(int j = 0; j <= w; j++)
            cadd(mapping[i][j][2],mapping[i][j+1][2],A);
    //运球变传球
    //注意，是单向的
    for(int i = 0; i <= h; i++)
        for(int j = 0; j <= w; j++)
        {
            add(mapping[i][j][0],mapping[i][j][1],B);
            add(mapping[i][j][0],mapping[i][j][2],B);
        }
    //传球变运球，逼最近球员来接住
    for(int i = 0; i <= h; i++)
        for(int j = 0; j <= w; j++)
        {
            add(mapping[i][j][1],mapping[i][j][0],mindist[i][j]*C);
            add(mapping[i][j][2],mapping[i][j][0],mindist[i][j]*C);
        }
    
}
int s;

struct node{
    int u;
    int dist;
    const bool operator<(const node b)const{
        return dist>b.dist;
    }
};priority_queue<node> dijkq;
int ddist[MLEN*MLEN*4];
int last[MLEN*MLEN*4];
void dijkstra()
{
    s=mapping[players[1].S][players[1].T][0];
    memset(ddist,0x3f,sizeof(ddist));
    
    ddist[s]=0;
    dijkq.push({s,0});
    while(dijkq.size())
    {
        node cur=dijkq.top();
        dijkq.pop();
        int u=cur.u;
        if(ddist[u]!=cur.dist)continue;
        for(int i = head[u];i;i=e[i].next)
        {
            int v=e[i].b;
            int w=e[i].w;
            if(ddist[v]>ddist[u]+w)
            {
                ddist[v]=ddist[u]+w;
                last[v]=u;
                dijkq.push({v,ddist[v]});
            }
        }
    }
}
signed main()
{
    h=read();w=read();
    A=read();B=read();C=read();
    n=read();
    for(int i = 1; i <= n; i++)
    {
        players[i].S=read();
        players[i].T=read();
    }
    get_Mindist();
    get_Mapping();
    linkup();
    dijkstra();
    cout << min({
        ddist[mapping[players[n].S][players[n].T][0]],
        ddist[mapping[players[n].S][players[n].T][1]],
        ddist[mapping[players[n].S][players[n].T][2]]});
        //到终点，没说怎么到，取min即可。
}
```

---

## 作者：masonpop (赞：0)

~~题意杀？~~

首先明确最优方案，其实形式是固定的：某个人跑来控球，踢出去，又来一个人控球，踢出去，循环进行。这样可以总结出两条性质：

① 每个人最多控一次球。

② 来控球的人一定是距离球最近的人。

然后发现，一个点是否有球并不足以转移，实际有 $6$ 种状态：有球且没人控，有球且正在朝某个方向滚动（$4$ 种），有球且有人正在控球。于是将其拆成 $6$ 个点，建图：

对于情况 $1$，需要一个距离最近的人来控球。于是向情况 $6$ 连对应代价的边。

对于情况 $2\sim 5$，要么停下来转移到 $1$，要么继续向对应方向滚动。代价分别为 $0$ 和 $A$。

对于情况 $6$，要么停下来并朝某个方向踢出去，要么继续控球跑，代价分别为 $B$ 和 $C$。

关于最近的点这件事，看上去是变化的，无法处理。但是实际上开头做一遍广搜就是对的。因为这样带来的唯一后果就是可能会出现多次控球，但是由性质 $1$ 这样不会计入答案。

注意下标从 $0$ 开始。[代码](https://www.luogu.com.cn/paste/l0zj6oex)。

---

