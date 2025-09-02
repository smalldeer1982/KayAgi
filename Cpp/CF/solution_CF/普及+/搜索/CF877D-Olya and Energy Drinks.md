# Olya and Energy Drinks

## 题目描述

有一NxM的迷宫，'#'是墙，‘.’是路，一秒钟可以向四个方向中的一个移动1~k步，求从起点到终点的最短时间。

## 样例 #1

### 输入

```
3 4 4
....
###.
....
1 1 3 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
3 4 1
....
###.
....
1 1 3 1
```

### 输出

```
8```

## 样例 #3

### 输入

```
2 2 1
.#
#.
1 1 2 2
```

### 输出

```
-1```

# 题解

## 作者：Prurite (赞：5)

## 思路
网络上的很多题的题解都是用 $O(nmk)$ 的方法加剪枝做的，我就来分享一下我的 $O(nm)$ 的做法吧。（虽然事实上剪枝后[他们的方法](http://codeforces.com/contest/877/submission/31703739)比我的还快）

对于一个二维的地图，我们可以用BFS（洪水填充）方便地知道从一个点到另一个点的最短路径。这里我们就只需特判一下k的问题。

实现：我采用的是一种类似于并查集的方法，比如假设k>=2，1,2,3号格子同在一行上且相邻，从1号格子走到2号格子，再从2号格子走到3号格子的过程可以看成从1号格子直接走到3号格子，这样可以节省1秒的行走时间。

注意这样子做要特判十字路口的情况，否则如
```
....#
.##.#
.....
###.#
```
这样的数据可能会挂掉（我第一次就是因为这个WA了）

具体看代码吧，有注释详细讲解。

## 代码
```cpp
#include <cstdio>
#include <queue>
using std::scanf;
using std::printf;
using std::queue; //using防重名
#define rint register int 

const int MAXN=1000+10, INF=1e9;
int n, m, k;
struct cell 
{
	bool empty;
	int from[5], fcnt;
	int dis, time;
	bool isfrom( int direction )
	{
		for ( int i=1; i<=fcnt; i++ )
			if ( from[i]==direction )
				return 1;
		return 0;
	}
//	empty记录是否能通行
//	from记录当前格子是从哪个方向来的，1,2,3,4分别是左，上，右，下
//	dis记录从上次重新出发开始走了多久，
//	time记录到达这个点所需的最短时间 
} map[MAXN][MAXN]; //行-列 
int go[5][2]={ 0,0, 0,1, -1,0, 0,-1, 1,0 }; //向右，向下，向左，向上 

inline void reset( );
inline int bfs( int sx, int sy, int tx, int ty );

int main( )
{
	scanf( "%d %d %d", &n, &m, &k );
	for ( rint i=1; i<=n; i++ )
	{
		getchar( );
		for ( rint j=1; j<=m; j++ )
		{
			char c=getchar( );
			if ( c=='.' )
				map[i][j].empty=1;
			else if ( c=='#' )
				map[i][j].empty=0;
		}
	}
	int x1, y1, x2, y2;
	scanf( "%d %d %d %d", &x1, &y1, &x2, &y2 );
	reset( );
	int ans=bfs( x1, y1, x2, y2 );
	printf( "%d\n", ans!=INF?ans:-1 );
	return 0;
}

inline void reset( )
{
	for ( rint i=1; i<=n; i++ )
		for ( rint j=1; j<=m; j++ )
			map[i][j].time=INF, map[i][j].dis=0, map[i][j].from[1]=0, map[i][j].fcnt=0;
	for ( rint i=1; i<=n; i++ )
		map[i][0].empty=0, map[i][m+1].empty=0;
	for ( rint i=1; i<=m; i++ )
		map[0][i].empty=0, map[n+1][i].empty=0;
	return;
}

queue<int> qx, qy;
inline int bfs( int sx, int sy, int tx, int ty )
{
	queue<int> emptyq;
	qx=qy=emptyq;
	map[sx][sy].dis=0, map[sx][sy].from[1]=0, map[sx][sy].fcnt=1, map[sx][sy].time=0;
	qx.push( sx ), qy.push( sy );
	while ( !qx.empty() )
	{
		int nx=qx.front(), ny=qy.front();
		qx.pop(), qy.pop();
		cell nowc=map[nx][ny]; //nowc表示现在在的格子 
		if ( nx==tx && ny==ty )
			break; //如果已经到达直接break 
		for ( int i=1; i<=4; i++ )
		{
			int gox=nx+go[i][0], goy=ny+go[i][1];
			cell &goc=map[gox][goy]; //goc表示当前前往的格子 
			if ( goc.empty==0 ) //是墙，跳过 
				continue;
			if ( goc.time==INF ) //这个点没有被访问过
				qx.push( gox ), qy.push( goy ); 
			cell temp;
//			新建一个临时点，表示如果从当前点更新后目标点的状态 
			temp.from[1]=i;
			if ( nowc.isfrom( i ) && nowc.dis<k-1 )
//			如果这个点原来可以方向i更新过来 ，并且从之前走过来时已经走了不多于k-1步 
				temp.dis=nowc.dis+1, temp.time=nowc.time;
//				可以理解为是一口气从一开始格子直接走过来 ，已走距离++，所用时间不变 
			else
				temp.dis=0, temp.time=nowc.time+1;
//				有转向或者已经走了k步了，必须重新出发，重置已走距离和所用时间 
			if ( temp.time<goc.time )
				goc.time=temp.time, goc.dis=temp.dis, goc.from[1]=temp.from[1], goc.fcnt=1;
//				如果这样更新过来时间更小，重置为从当前点更新 
			if ( temp.time==goc.time )
				goc.from[++goc.fcnt]=temp.from[1];
//				如果相等，就加入可以从当前方向更新 
		}
	}
	return map[tx][ty].time;
}
```
[提交记录 用时: 2408ms / 内存: 39672KB](https://www.luogu.org/record/show?rid=6795430)

---

## 作者：easy42 (赞：0)

### 思路
看很多人是用 BFS 或剪枝做的，我有一种更快的方法，使用了 A * 算法，我写的代码算是比较快的了。

具体来说，其实就是普通的 BFS，使用优先队列，剩下就是一模一样的广搜，只不过在上面加了优化。

算法具体步骤：

1. 判断是否已经结束，如果结束直接跳出。
2. 初始化，准备各项基本工作，定义起点 $s$，终点 $t$，从起点（初始状态）开始的距离函数 $g(x)$，到终点（最终状态）的距离函数 $h(x)$，$h^*(x)$，以及每个点的估价函数 $f(x)=g(x)+h(x)$。
3. 开始搜索，用了代价估计，首先记录当前代价（已经走的路程），再估计一个到终点代价，加起来就是代价估计，然后把队列改成优先队列，然后就秒了。
### 关于 A * 算法
A * 搜索算法（英文：A*search algorithm，A * 读作 A-star），简称 A * 算法，是一种在图形平面上，对于有多个节点的路径求出最低通过成本的算法。它属于图遍历（英文：Graph traversal）和最佳优先搜索算法（英文：Best-first search），亦是 BFS 的改进。

[_OI-WIKI_](https://oi-wiki.org/search/astar/)
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n,sx,sy,ex,ey,m,k,fx[4][2]= {{1,0},{0,1},{-1,0},{0,-1}},minn=INT_MAX,cnt;
char a[N][N];
bool vis[N][N],flag=true,vvis[N][N],fflag=true;
int dis[N][N]; 
struct node {
	int f,x,y,g,h;//f=g+h,g已经移动了多少步,f估计还要多少步
	bool operator <(const node &a)const {
		return a.f<f;
	}
};
priority_queue<node>q;
int jl(int x,int y,int nx,int ny) {
	return ceil(abs(x-nx)*1.0/(k*1.0))+ceil(abs(y-ny)*1.0/(k*1.0));//曼哈顿距离
}
int Astar() {
	vis[sx][sy]=true;
	if(sx==ex&&sy==ey){
		printf("0");
		exit(0);//直接结束
	} 
	node t;
	t.x=sx;
	t.y=sy;
	t.g=0;
	t.h=jl(sx,sy,ex,ey);
	t.f=t.g+t.h;
	q.push(t);
	while(!q.empty()) {
		t=q.top();
		q.pop();
		vvis[t.x][t.y]=true;
		for(int j=0; j<4; j++) {
			for(int i=1; i<=k; i++) {
				node tt;
				tt.x=t.x+fx[j][0]*i;
				tt.y=t.y+fx[j][1]*i;
				if(!(tt.x>=1&&tt.y>=1&&tt.x<=n&&tt.y<=m&&a[tt.x][tt.y]!='#')) {
					break;//跳出循环
				}
				if(tt.x==ex&&tt.y==ey) {
					flag=false;
					cnt++;
					minn=min(minn,t.g+1);
						fflag=false;
						printf("%d",minn);
						return 0;
				}
				if(tt.x>=1&&tt.y>=1&&tt.x<=n&&tt.y<=m&&a[tt.x][tt.y]!='#'&&(vis[tt.x][tt.y]==false||t.g+1<dis[tt.x][tt.y])) {
					vis[tt.x][tt.y]=true;
					dis[tt.x][tt.y]=t.g+1;
					tt.g=t.g+1;
					tt.h=jl(tt.x,tt.y,ex,ey);
					tt.f=tt.g+tt.h;
					q.push(tt);
				}
			}
		}
	}
	return 0;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	char x;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>a[i][j];//读入
		}
	}
	scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
	Astar();
	if(flag) {
		printf("-1");
	}else{
		if(fflag==true){
			printf("%d",minn);
		}
	}
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路
$n$ 和 $k$ 和 $m$ 都小于 $1000$ 好像暴力也能过，直接洪水填充再在方向里面加一维即可。

注意要判断这个点有没有搜索过，如果没搜索过或有更优解再更新。

### 代码
```
//请使用C++20，否则会TLE
#include <bits/stdc++.h>
#define int long long
#define maxn 2025
#define INF 2e17
using namespace std;

int n, m, k, xt, yt, xe, ye;
char a[maxn][maxn];
int d[maxn][maxn];
int xx[4] = {0, 0, -1, 1};
int yy[4] = {-1, 1, 0, 0};


void bfs()
{
	d[xt][yt] = 0;
	queue<pair<int, int> > q;
	q.push({xt, yt});
	while(!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for(int mv = 0; mv < 4; mv++)
		{
			for(int st = 1; st <= k; st++)
			{
				int nx=x+xx[mv]*st,
				ny= y+yy[mv]*st;				
				if(a[nx][ny] == '#'||nx < 1 || nx > n||ny < 1 || ny > m) break;				
				if(nx == xe && ny == ye)
				{
					d[nx][ny] = d[x][y] + 1;
					return;
				}				
				if(d[nx][ny] > d[x][y] + 1)
				{
					d[nx][ny] = d[x][y] + 1;
					q.push({nx, ny});
				}
			}
		}
	}
}
signed main()
{
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> a[i][j];
	cin >> xt >> yt >> xe >> ye;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			d[i][j] = INF;
	
	bfs();
	if(d[xe][ye] == INF) cout << -1;
	else cout << d[xe][ye];
	return 0;
}
```

---

