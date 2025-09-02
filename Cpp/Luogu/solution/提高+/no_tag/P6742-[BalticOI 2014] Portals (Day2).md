# [BalticOI 2014] Portals (Day2)

## 题目描述

给定一个 $R\times C$ 的迷宫，每个格子都有一种方块：

- `#` 墙，不可以走，不可以穿过
- `.` 路，可以走
- `S` 出生点，玩家从这里开始走，只有一个
- `C` 终点，玩家要到达这里，只有一个

现在要对迷宫进行扩容，周围要增加一个方块 `#`，变成 $(R+2)\times (C+2)$ 的迷宫。

并且在任何时候，它都可以向上、左、下、右四个方向中的一个发射传送门。当一个传送门被发射，它会一直向发射的方向飞行，直到碰触到墙壁。这时，传送门会被放置在这堵墙上。

走一格需要 $1$ 的时间，穿梭传送门也需要 $1$ 的时间。

求从出生点到终点最少需要多少时间。

如果很难理解题意，请配合样例进行理解。

## 说明/提示

#### 样例说明

对于样例 $1$，我们把迷宫模拟出来并且在周围加上 `#` 之后，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/5d381oik.png)

人形物体为 `S`，蛋糕形物体为 `C`。

如图所示，至少需要 $4$ 的时间。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（11 pts）：$R,C \le 10$。
- Subtask 2（20 pts）：$R,C \le 50$。
- Subtask 3（20 pts）：$R,C \le 200$，每个 `.` 周围都至少有一个 `#`。
- Subtask 4（19 pts）：$R,C  \le 200$。
- Subtask 5（30 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le R,C \le 1000$。

**本题强制 $O2$ 优化。**

#### 说明

翻译自 [BalticOI 2014 Day2 B Portals](https://boi.cses.fi/files/boi2014_day2.pdf)。

## 样例 #1

### 输入

```
4 4
.#.C
.#.#
....
S...```

### 输出

```
4```

# 题解

## 作者：Zimo_666 (赞：5)

## P6742 [BalticOI 2014 Day2] Portals 

### Description

给定一个 $R\times C$ 的迷宫，每个格子都有一种方块：

- `#` 墙，不可以走，不可以穿过
- `.` 路，可以走
- `S` 出生点，玩家从这里开始走，只有一个
- `C` 终点，玩家要到达这里，只有一个

现在要对迷宫进行扩容，周围要增加一个方块 `#`，变成 $(R+2)\times (C+2)$ 的迷宫。

并且在任何时候，它都可以向上、左、下、右四个方向中的一个发射传送门。当一个传送门被发射，它会一直向发射的方向飞行，直到碰触到墙壁。这时，传送门会被放置在这堵墙上。

走一格需要 $1$ 的时间，穿梭传送门也需要 $1$ 的时间。

求从出生点到终点最少需要多少时间。

### Solution

我们简单造几组数据后发现有一种最优策略为两个传送门在同一点释放。于是我们考虑建边策略，我们首先可以把点 $u$ 上下左右相邻的并且在图内的点连边。

而后我们考虑传送门的连边方法，我们先预处理出向各个方向可以到的墙的距离，而后我们比较这四种方案，得出一种走到传送门前等待传送的最小 $dis$ 并把这个点连接这四个墙点，边权均为 $dis+1$。注意若 $u$ 与某墙点长度恰好是 $dis$ 也就意味着直接走不需要传送就可以花费 $dis$ 到达，因而这条最小边（可能不唯一）边权应为 $dis$ 而非 $dis+1$。这样我们就完成了建边，直接在图上跑最短路即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e3+7;
int n,r,c;
char mp[N][N];
int s,t;
int lf[N][N],rg[N][N],up[N][N],dn[N][N];
vector<pair<int,int>> G[N*N];
int dis[N*N];
bool _vis[N*N];

struct node{
	int dis,id;
	friend bool operator < (node a,node b){
		return a.dis>b.dis;
	}
};

void Dj(int s){
	memset(_vis,0,sizeof _vis);
	priority_queue<node> q;
	memset(dis,80,sizeof dis);
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(_vis[u]) continue;
		_vis[u]=1;
		for(auto i:G[u]){
			int k=i.first,w=i.second;
			if(dis[k]>dis[u]+w){
				dis[k]=dis[u]+w;
				q.push({dis[k],k});
			}
		}
	}
}

bool query(int x,int y){
	return (mp[x][y]=='.'||mp[x][y]=='S'||mp[x][y]=='C');
}

int get(int x,int y){
	return x*c+y-c;
}

void add(int u,int v,int w){
	G[u].push_back(make_pair(v,w));
}

void read(){
	scanf("%d%d",&r,&c);
	n=r*c;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>mp[i][j];
			if(mp[i][j]=='S') s=get(i,j);
			if(mp[i][j]=='C') t=get(i,j);
		}
	}
}

void deal(){
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(mp[i][j]=='#') lf[i][j]=j;
			else lf[i][j]=lf[i][j-1];
		}
	}
	for(int j=1;j<=c;j++){
		for(int i=1;i<=r;i++){
			if(mp[i][j]=='#') up[i][j]=i;
			else up[i][j]=up[i-1][j];
		}
	}
	for(int i=1;i<=r;i++){
		rg[i][c+1]=c+1;
		for(int j=c;j;j--){
			if(mp[i][j]=='#') rg[i][j]=j;
			else rg[i][j]=rg[i][j+1];
		}
	}
	for(int j=1;j<=c;j++){
		dn[r+1][j]=r+1;
		for(int i=r;i;i--){
			if(mp[i][j]=='#') dn[i][j]=i;
			else dn[i][j]=dn[i+1][j];
		}
	}
}

void work(){
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(query(i,j)){
				int L=lf[i][j]+1,R=rg[i][j]-1,U=up[i][j]+1,D=dn[i][j]-1;
				int _dis=min({j-L+1,R-j+1,i-U+1,D-i+1});
				int _L=get(i,L),_R=get(i,R),_U=get(U,j),_D=get(D,j);
				int _pos=get(i,j);
				add(_pos,_L,min(_dis,j-L)),add(_pos,_R,min(_dis,R-j)),add(_pos,_U,min(_dis,i-U)),add(_pos,_D,min(_dis,D-i));
				if(query(i,j+1)) add(_pos,get(i,j+1),1); 
				if(query(i+1,j)) add(_pos,get(i+1,j),1); 
				if(query(i-1,j)) add(_pos,get(i-1,j),1); 
				if(query(i,j-1)) add(_pos,get(i,j-1),1);
			}
		}
	}
	Dj(s);
	printf("%d\n",dis[t]);
//	for(int i=1;i<=n;i++) printf("%d ",dis[i]);
}

int main(){
	read();
	deal();
	work();
	return 0;
}
```



---

## 作者：Lazy_Labs (赞：4)

本题所有题解对于 使用传送门时发射两个门只用在同一个位置的最优性 都没有证明，均使用了显然或者直接给出这样的连边方式。

证明如下：

首先令一次传送过程的进入传送门的格子为入门 $I$，出口传送门的格子为出门 $O$。（格子指的是进入传送门前一步所在的格子）$dis_{i,j}$ 表示不使用传送门时两个格子间的距离。

下面我们先证明上一次的入门 $I_0$ 不会被再次使用：

1. 若再次作为入门使用，那么假设我们在 $P_1$ 处打出下一次的出门 $O_1$，那么再次使用 $I_0$ 走到 $O_1$，从上一次进入 $I_0$ 开始计算，时间为 $1+dis_{O_0,P_1}+dis_{P_1,I_0}+1$。  
若 $dis_{O_0,P_1}<dis_{P_1,I_0}$，那么考虑让 $I_1=O_0$，小于上述时间。  
若 $dis_{P_1,I_0}\le dis_{O_0,P_1}$，则不走前一次传送门，直接从 $I_0$ 走到 $P_1$，打完 $O_1$ 再走回来进入 $I_0$，小于上述时间。
2. 若再次作为出门使用，由于 1，所以若再次使用上一次的 $I$，则一定都是作为出门使用。  
考虑第一个不作为出门使用的 $I_n$（最后一次传送的入门一定不作为出门使用），在此之前， $I_i=O_{i+1}$。  
因为 $I_n\rightarrow O_n$ 之后，一定不会再次使用 $I_n$ 及之前的传送门，所以可以直接考虑 $I_1\rightarrow O_n$ 的路径可以直接省略为 $I_1\rightarrow I_{n-1}=O_n$ 并直接走就行，显然比作为出门使用步数少。于是可以回溯到 $I_0$ 也不作为出门使用。  

再次证明上一次的出门不会用于下一次的出门：

由于不会重复使用入门，所以可以直接排除掉入门，发现两次状态相同，后面一次的传送是不必要的。

同时如果上一次的出门作为下一次的入门，那么可以直接假设原先就没有上一次的出门，重新发射一扇入门即可。

至此，我们证明了每两次传送间不会有影响（即上一次的传送门不会干扰下一次的传送）。这部分实际上是比较显然的，但是还是使用了较为严谨的方式证明。（如果有更简单的方法欢迎告诉笔者）

那么对于每次传送，我们钦定入门的发射一定在进入入门前的一个格子，那么对于发射出门的点 $P_0$，我们肯定是将入点选定在距离 $P_0$ 最近的墙的位置。传送到 $O_0$ 的时间为 $dis_{P_0,I_0}$。

接下来我们对于每次传送证明两次发射在同一个位置发射一定是最优的。（也就是各个题解中说的 $I_0$ 在 $P_0$ 四个方向上最短的墙的距离）

考虑 $I_0$ 所在的墙 $W_0$（即 $I_0$ 发射的传送门墙面所在的墙，和 $I_0$ 不同）和 $P_0$ 围成的长方形中一定不存在别的墙（若存在，则最优不为 $I_0$），那么这个长方形中一定有一个顶点可以同时看到 $W_0$ 和 $O_0$，选择这个点发射传送门即可。

---

## 作者：jiazhichen844 (赞：3)

## 题意
你需要走一个迷宫，且你手里有一个传送枪，由于你单身二十年的手速，发射传送门不需要时间，当你走进一个传送门，你会穿越到另一个门外，并且这对门会消失，只能重新发射，求走到终点的最小时间。
## 思路历程
### 如何骗分
我是在模拟赛上看到这题的，当时不会这题（暴力都不会），然后我就当传送枪不存在，起手 bfs，水了 $20$ pts。
### 正解
首先，这肯定是最短路，尝试如何建图，把每个空地和相邻的空地连上。

首先，穿越时的两个传送门必定在同一位置发射（显然啊），于是，考虑在 $(i,j)$ 点发射的传送门作用。

求出距离 $(i,j)$ 最近的且在同一行或同一列的墙，设距离为 $l$，不难发现，穿越的起点一定在这面墙**上**，穿越终点就是四个方向上最近的墙，$(i,j)$ 点到他们的距离也会变成 $l$。所以可以往这四个点连长度为 $l$ 的边。

那如何求出上下左右最近的墙呢？和[种花](https://www.luogu.com.cn/problem/P8865)一样的思路，上下左右分别扫一遍，递推即可。

时间复杂度 $O(nm \log (nm))$，空间复杂度 $O(nm)$。

## code
```cpp
#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
int n,m;
struct node
{
	int x,y;
	long long l;
	bool operator < (const node a) const
	{
		return l>a.l;
	}
};
long long dis[1005][1005];
bool f[1005][1005];
char a[1005][1005];
int up[1005][1005],down[1005][1005],lft[1005][1005],rght[1005][1005];
vector<node> e[1005][1005];
int nxt[4][2]={
	{0,1},
	{0,-1},
	{1,0},
	{-1,0}
};
priority_queue<node> q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!='#')
				up[i][j]=up[i-1][j]+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!='#')
				lft[i][j]=lft[i][j-1]+1;
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			if(a[i][j]!='#')
				down[i][j]=down[i+1][j]+1;
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			if(a[i][j]!='#')
				rght[i][j]=rght[i][j+1]+1;//求出上下左右的距离
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!='#')
			{
				for(int k=0;k<=3;k++)
					if(a[i+nxt[k][0]][j+nxt[k][1]]=='S'||a[i+nxt[k][0]][j+nxt[k][1]]=='C'||a[i+nxt[k][0]][j+nxt[k][1]]=='.')
						e[i][j].push_back({i+nxt[k][0],j+nxt[k][1],1});
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]!='#')
			{
				int x=min(min(up[i][j],down[i][j]),min(lft[i][j],rght[i][j]));
				e[i][j].push_back({i,j-lft[i][j]+1,x});
				e[i][j].push_back({i,j+rght[i][j]-1,x});
				e[i][j].push_back({i+down[i][j]-1,j,x});
				e[i][j].push_back({i-up[i][j]+1,j,x});
			}
		}//建边
	memset(dis,31,sizeof(dis));
	int x,y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='S')
			{
				x=i;
				y=j;
			}
		}
	int sx,sy;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='C')
			{
				sx=i;
				sy=j;
			}
		}
	dis[x][y]=0;
	q.push({x,y,0});
	while(!q.empty())
	{
		node t=q.top();
		q.pop();
		if(f[t.x][t.y])
			continue;
		f[t.x][t.y]=1;
		if(t.x==sx&&t.y==sy)
			break;
		for(int i=0;i<e[t.x][t.y].size();i++)
		{
			long long pre=dis[e[t.x][t.y][i].x][e[t.x][t.y][i].y];
			dis[e[t.x][t.y][i].x][e[t.x][t.y][i].y]=min(dis[e[t.x][t.y][i].x][e[t.x][t.y][i].y],dis[t.x][t.y]+e[t.x][t.y][i].l);
			if(pre!=dis[e[t.x][t.y][i].x][e[t.x][t.y][i].y])
				q.push({e[t.x][t.y][i].x,e[t.x][t.y][i].y,dis[e[t.x][t.y][i].x][e[t.x][t.y][i].y]});
		}
	}
	cout<<dis[sx][sy];//直接暴力dijkstra
}
```

---

## 作者：紊莫 (赞：2)

提供一份使用 BFS 且较为简单的代码。

迷宫问题是裸的，但是加上了一个传送门的处理，所谓传送，实际上就是在两个边界地方进行传送，也就是说我们知道传送门能到哪里，这个可以预处理出来。

对于每个点，我们有两种选择，一个是走一步，另一个是打两个传送门，传送到某一边，那么这一步的代价是到达最近的边界的距离，所以边权有多种，要使用优先队列的 BFS。

[参考代码。](https://www.luogu.com.cn/paste/c0vxwe11)

---

## 作者：JK_LOVER (赞：2)

## 题意
在 $n\times m$ 的网格图中，求出原点到目标点的最短路。并且可以发送传送门。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p6742)

- 传送门：当有两个传送门同时存在时，你可以进入这个传送门并到达另一个传送门所在的位置，可以使用多次。
## 分析
题目读懂了就很简单了。对于一个点来说，它只有两种移动方式。

- 直接走一格，花费为 $1$ 。

- 走到最近的一面墙上，开门。可以证明如果要用传送门走最近的墙是最优的。

现在就只需要预处理一个点向四个方向可以到达哪些墙了。那么这道题就转化为一道最短路的模板题了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2010;
int cnt=1,n,m,dx[4]={0,0,-1,1},S,T,dy[4]={1,-1,0,0},dis[N*N],vis[N*N],head[N*N];
struct Edge{int to,w,nxt;}e[N*N<<2];
struct node{int x,y;}end[N][N][4];
struct Node{int pos,dis; 
	bool operator <(const Node a)const {
		return dis > a.dis;
	}
};
priority_queue<Node> heap;
char Map[N][N];
int id(int x,int y){
	return (x-1)*m+y;
}
void add(int x,int y,int w){
	e[++cnt].to = y;e[cnt].nxt = head[x];e[cnt].w = w;head[x] = cnt;
}
node make(int x,int y,int k){
	if(end[x][y][k].x!=0&&end[x][y][k].y!=0) return end[x][y][k];
	int X = x + dx[k],Y = y + dy[k];
	if(X>n||Y>m||X<1||Y<1||Map[X][Y] == '#') end[x][y][k] = (node){x,y};
	else end[x][y][k] = make(X,Y,k);
	return end[x][y][k];
}
void Dij(int s,int t){
	memset(dis,0x3f,sizeof(dis));
	heap.push((Node){s,dis[s]=0});
	while(heap.size()){
		int x = heap.top().pos;heap.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(int i = head[x];i;i = e[i].nxt){
			int y = e[i].to;
			if(dis[y]>dis[x]+e[i].w){
				dis[y] = dis[x]+e[i].w;
				heap.push((Node){y,dis[y]});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++)
		{
			cin>>Map[i][j];
			if(Map[i][j] == 'S') S = id(i,j);
			if(Map[i][j] == 'C') T = id(i,j);
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(Map[i][j] == '#') continue;
			for(int k = 0;k < 4;k++){
				int x = dx[k] + i,y = dy[k] + j;
				if(x>n||y>m||x<1||y<1||Map[x][y]=='#') continue;
				add(id(i,j),id(x,y),1);
			}
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			for(int k = 0;k < 4;k++){
				end[i][j][k] = make(i,j,k);
			}
			int Min = 0x3f3f3f3f;
			for(int k = 0;k < 4;k++)
			Min = min(Min,abs(i-end[i][j][k].x)+abs(j-end[i][j][k].y)+1);
			for(int k = 0;k < 4;k++)
			add(id(i,j),id(end[i][j][k].x,end[i][j][k].y),Min);
		}
	}
	Dij(S,T);
	cout<<dis[T]<<endl;
	return 0;
}
/*
5 7
S.#....
.#..##.
.......
#.#...#
.#C.##.
*/
```


---

## 作者：Cure_Wing (赞：0)

[P6742 [BalticOI 2014 Day2] Portals](https://www.luogu.com.cn/problem/P6742)

### 思路

重新解释一下题目，这里的任意时刻说的是任意实数时刻。

考虑没有传送门，那就是一个简单的搜索。

有了传送门，考虑怎么利用它。由于传送门一定会发送到墙上，所以传送出去的位置也一定也会在墙上。假设我们固定传送的终点，那么首先要在这个墙所在的行或列发射一个传送门，然后找一个墙钻进去。由于终点固定了下来，所以我们找一堵最近的墙传送。所以我们计算一下每一个点到四周墙的距离，选取最近的墙钻进去，然后枚举从四周那一堵墙出来。

由于这样搜索使得边权不再全为 $1$，所以我们要用优先队列进行广度优先搜索，决定搜索顺序。

时间复杂度 $O(RC\log(RC))$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using std::cin;using std::cout;
constexpr int N=1005,inf=1e9;
int n,m,u[N][N],d[N][N],l[N][N],r[N][N],sx,sy,ans[N][N],dx[]={-1,1,0,0},dy[]={0,0,1,-1},ex,ey;
std::string s[N];
struct node{int x,y,dis;inline bool operator<(const node &a)const{return dis>a.dis;}};
std::priority_queue<node>q;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>s[i];s[i]="#"+s[i]+"#";
		for(int j=1;j<=m;++j){
			if(s[i][j]=='S'){sx=i;sy=j;}
			if(s[i][j]=='C'){ex=i;ey=j;}
			ans[i][j]=inf;
		}
	}
	for(int i=0;i<=m+1;++i){s[0]+='#';s[n+1]+='#';}//统计一点到四周墙的距离
	for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) if(s[j][i]!='#') u[j][i]=u[j-1][i]+1;
	for(int i=1;i<=m;++i) for(int j=n;j>=1;--j) if(s[j][i]!='#') d[j][i]=d[j+1][i]+1;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(s[i][j]!='#') l[i][j]=l[i][j-1]+1;
	for(int i=1;i<=n;++i) for(int j=m;j>=1;--j) if(s[i][j]!='#') r[i][j]=r[i][j+1]+1;
	q.push(node{sx,sy,0});ans[sx][sy]=0;
	while(!q.empty()){
		node k=q.top();q.pop();
		for(int i=0;i<4;++i){//不使用传送门
			int cx=k.x+dx[i],cy=k.y+dy[i];
			if(1<=cx&&cx<=n&&1<=cy&&cy<=m&&s[cx][cy]!='#'&&ans[k.x][k.y]+1<ans[cx][cy]){ans[cx][cy]=ans[k.x][k.y]+1;q.push(node{cx,cy,ans[cx][cy]});}
		}
		int cost=std::min({u[k.x][k.y],d[k.x][k.y],l[k.x][k.y],r[k.x][k.y]})-1,k1=k.x-u[k.x][k.y]+1,k2=k.x+d[k.x][k.y]-1,k3=k.y-l[k.x][k.y]+1,k4=k.y+r[k.x][k.y]-1;//四个方向枚举传送门的出口
		if(ans[k.x][k.y]+cost+1<ans[k1][k.y]){ans[k1][k.y]=ans[k.x][k.y]+cost+1;q.push(node{k1,k.y,ans[k1][k.y]});}
		if(ans[k.x][k.y]+cost+1<ans[k2][k.y]){ans[k2][k.y]=ans[k.x][k.y]+cost+1;q.push(node{k2,k.y,ans[k2][k.y]});}
		if(ans[k.x][k.y]+cost+1<ans[k.x][k3]){ans[k.x][k3]=ans[k.x][k.y]+cost+1;q.push(node{k.x,k3,ans[k.x][k3]});}
		if(ans[k.x][k.y]+cost+1<ans[k.x][k4]){ans[k.x][k4]=ans[k.x][k.y]+cost+1;q.push(node{k.x,k4,ans[k.x][k4]});}
	}
	cout<<ans[ex][ey];
	return 0;
}
```

---

## 作者：zymooll (赞：0)

### 前言

这边给一个 BFS 的做法。

### 题目大意

给定一个 $R \times C$ 的地图，需要求出从起点到终点的最短时间。

对于每次行动，有如下三种操作：

- 移动操作，可以将人物移动到上下左右的非墙的位置，花费 $1$ 个时间。

- 传送操作，可以将人物从墙边已有的传送门移动至另一个传送门，花费 $1$ 个时间。

- 打门操作，可以在人物上下左右的最近的墙上打一个传送门，花费 $0$ 个时间。

### 题目思路

我们不妨分为如下几个操作：

1. 预处理每个点到 __墙边__ 的最短时间花费（不使用传送门），时间复杂度 $O(R \times C)$。

2. 预处理每个点上下左右最近的 __墙边__ 的位置，时间复杂度 $O(R \times C)$。

3. 一遍 BFS，时间复杂度 $\Omega( ( R \times C ) \cdot \log ( R  \times C))$。

对于第一个操作，我们可以预处理出所有墙边的坐标，加入 BFS 队列，再跑一遍 BFS 即可得到结果。

对于第二个操作，我们可以采用以下方法记录。

对于每一个格子：

- 如果是墙，不处理。

- 如果是墙边，则记录位置。

- 如果既非墙，也非墙边，则继承上一次处理的记录值。

四个方向都来一遍就行。

对于第三种操作，我们不妨开一个堆作为 BFS 队列（因为 BFS 队列要求有序才是对的，而用门传送因为有可能要走回去所以单次加入队列加的值不为 $1$，直接加入队尾可能会破坏有序性，所以要堆维护）。

对于移动操作，我们直接借鉴传统 BFS，简单移动即可。

对于传送操作，我们同样的枚举上下左右的最近墙边，将对应的传送点加上走到墙边的距离再加传送时间。

特别的，如果队列中存储的对应点的时间大于目前计算出来的时间，需要直接弹出这个点，不做运算。

可以发现，当 BFS 队列为空时，即有正确答案。

### 参考代码

大量代码警告！！！

```cpp
// Author:zymooll

#include<bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
//#define int long long
using namespace std;
int read(){
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=s*10+c-'0';
		c=getchar();
	}
	return s*w;
}
void print(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>=10)print(x/10);
	putchar(x%10+'0');
	return;
}
const int NMax=1e3;
int n,m;
int sx,sy,ex,ey;
int dmap[NMax+10][NMax+10];
int ans[NMax+10][NMax+10];
struct Node{
    int info[4];
    //up,down,left,right
}node[NMax+10][NMax+10];
int fx[4][2]={-1,0,0,-1,1,0,0,1};
struct Info{
    int x,y,len;
    friend bool operator < (Info aa,Info bb){
        return aa.len>bb.len;
    }
};
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char ch=getchar();
            if(ch!='#'){
                dmap[i][j]=INT_MAX;
                if(ch=='S')sx=i,sy=j;
                else if(ch=='C')ex=i,ey=j;
            }
        }
        getchar();
    }
    queue<pair<int,int> >q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!dmap[i][j])continue;
            int flag=0;
            for(int k=0;k<4;k++){
                int dx=i+fx[k][0],dy=j+fx[k][1];
                if(!dmap[dx][dy]){
                    flag=1;
                    break;
                }
            }
            if(!flag)continue;
            dmap[i][j]=1;
            q.push(make_pair(i,j));
        }
    }
    while(!q.empty()){
        pair<int,int> u=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int dx=u.first+fx[i][0],dy=u.second+fx[i][1];
            if(dmap[dx][dy]&&dmap[dx][dy]>dmap[u.first][u.second]+1){
                dmap[dx][dy]=dmap[u.first][u.second]+1;
                q.push(make_pair(dx,dy));
            }
        }
    }
    for(int i=1;i<=m;i++){//control ---
        for(int j=1;j<=n;j++){
            if(!dmap[j-1][i])node[j][i].info[0]=j;
            else node[j][i].info[0]=node[j-1][i].info[0];
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=n;j>=1;j--){
            if(!dmap[j+1][i])node[j][i].info[1]=j;
            else node[j][i].info[1]=node[j+1][i].info[1];
        }
    }
    for(int i=1;i<=n;i++){//control |
        for(int j=1;j<=m;j++){
            if(!dmap[i][j-1])node[i][j].info[2]=j;
            else node[i][j].info[2]=node[i][j-1].info[2];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            if(!dmap[i][j+1])node[i][j].info[3]=j;
            else node[i][j].info[3]=node[i][j+1].info[3];
        }
    }
    memset(ans,0x3f,sizeof(ans));
    priority_queue<Info>qq;
    qq.push((Info){sx,sy,0});
    ans[sx][sy]=0;
    while(!qq.empty()){
        int ux=qq.top().x,uy=qq.top().y,ud=qq.top().len;
        qq.pop();
        if(ans[ux][uy]<ud)continue;
        for(int i=0;i<4;i++){
            int dx=ux+fx[i][0],dy=uy+fx[i][1];
            if(dmap[dx][dy]&&ans[dx][dy]>ans[ux][uy]+1){
                ans[dx][dy]=ans[ux][uy]+1;
                qq.push((Info){dx,dy,ans[dx][dy]});
            }
        }
        for(int i=0;i<4;i++){
            int dx=(i<=1?node[ux][uy].info[i]:ux),dy=(i<=1?uy:node[ux][uy].info[i]);
            if(dmap[dx][dy]&&ans[dx][dy]>ans[ux][uy]+dmap[ux][uy]){
                ans[dx][dy]=ans[ux][uy]+dmap[ux][uy];
                qq.push((Info){dx,dy,ans[dx][dy]});
            }
        }
    }
    print(ans[ex][ey]);
	return 0;
}

```

### 后记

绿本人觉着还是低了点，人 P4442 还是个紫题，其实跟这道题差不多，只多了一个特殊情况，建议蓝。

完结撒花！！

---

## 作者：ZPB2011 (赞：0)

# Portals

## 前言

[加强版](https://www.luogu.com.cn/problem/P6742)。

~~在灌水区看到了这题。~~

## 思路

我们可以注意到 $N$ 很小，所以可以考虑一些非常暴力的想法。

如果没有传送门，这题就是一题非常水的题。

由于传送门一定要放在墙上，我们可以预处理出每个点到墙的距离。

然后选一个位置作为终点，然后再选一个最近得墙作为传送点，枚举即可。

我们可以用 bfs 实现代码。

## AC code

```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int N = 1e3 + 5;

struct node {
	int x, y, w;
	bool operator < (node x) const {
		return w > x.w;
	}
};

int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};
char board[N][N];
int a[N][N], b[N][N], c[N][N], d[N][N], dis[N][N];

int main() {
	memset(dis, 0x3f, sizeof(dis));//初始化 
	int n, m, sx, sy, ex, ey;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {//输入 
		for(int j = 1; j <= m; j++) {
			cin >> board[i][j];
			if(board[i][j] == 'C') {
				sx = i;
				sy = j;
			}
			if(board[i][j] == 'F') {
				ex = i;
				ey = j;
			}
		}
	}
	for(int i = 0; i <= n + 1; i++) board[i][0] = '#';
	for(int i = 0; i <= n + 1; i++) board[i][m + 1] = '#';
	for(int i = 0; i <= m + 1; i++) board[0][i] = '#';
	for(int i = 0; i <= m + 1; i++) board[m + 1][0] = '#';//补充墙 
	for(int j = 1; j <= m; j++) {//预处理 
		for(int i = 1; i <= n; i++) {
			if(board[i][j] != '#') a[i][j] = a[i - 1][j] + 1;
		} 
	}
	for(int j = 1; j <= m; j++) {
		for(int i = n; i >= 1; i--) {
			if(board[i][j] != '#') b[i][j] = b[i + 1][j] + 1;
		} 
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(board[i][j] != '#') c[i][j] = c[i][j - 1] + 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = m; j >= 1; j--) {
			if(board[i][j] != '#') d[i][j] = d[i][j + 1] + 1;
		} 
	}
	dis[sx][sy] = 0;
	priority_queue<node> que;
	que.push({sx, sy, 0});
	while(!que.empty()) {//bfs 
		node u = que.top();
//		cout << u.x << ' ' << u.y << endl;
		que.pop();
		for(int i = 1; i <= 4; i++) {//普通搜索 
			int nx = u.x + dx[i], ny = u.y + dy[i];
			if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && board[nx][ny] != '#' && dis[u.x][u.y] + 1 < dis[nx][ny]) {
				dis[nx][ny] = dis[u.x][u.y] + 1;
				que.push({nx, ny, dis[nx][ny]});
			}
		}
		int minn = min(min(a[u.x][u.y], b[u.x][u.y]), min(c[u.x][u.y], d[u.x][u.y])) - 1;//选传送门 
		int x1 = u.x - a[u.x][u.y] + 1;
		int x2 = u.x + b[u.x][u.y] - 1;
		int y1 = u.y - c[u.x][u.y] + 1;
		int y2 = u.y + d[u.x][u.y] - 1;
//		cout << a[u.x][u.y] << ' ' << b[u.x][u.y] << ' ' << c[u.x][u.y] << ' ' << d[u.x][u.y] << endl;
//		cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << endl;
		int val = dis[u.x][u.y];
		if(val + minn + 1 < dis[x1][u.y]) {
			dis[x1][u.y] = val + minn + 1;
			que.push({x1, u.y, dis[x1][u.y]});
		}
		if(val + minn + 1 < dis[x2][u.y]) {
			dis[x2][u.y] = val + minn + 1;
			que.push({x2, u.y, dis[x2][u.y]});
		}
		if(val + minn + 1 < dis[u.x][y1]) {
			dis[u.x][y1] = val + minn + 1;
			que.push({u.x, y1, dis[u.x][y1]});
		}
		if(val + minn + 1 < dis[u.x][y2]) {
			dis[u.x][y2] = val + minn + 1;
			que.push({u.x, y2, dis[u.x][y2]});
		}
	}
	if(dis[ex][ey] == 0x3f3f3f3f) cout << "nemoguce" << endl;//不成立 
	else cout << dis[ex][ey] << endl;
	return 0;
}
```

---

