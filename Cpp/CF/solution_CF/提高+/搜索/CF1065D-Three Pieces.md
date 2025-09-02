# Three Pieces

## 题目描述

You stumbled upon a new kind of chess puzzles. The chessboard you are given is not necesserily $ 8 \times 8 $ , but it still is $ N \times N $ . Each square has some number written on it, all the numbers are from $ 1 $ to $ N^2 $ and all the numbers are pairwise distinct. The $ j $ -th square in the $ i $ -th row has a number $ A_{ij} $ written on it.

In your chess set you have only three pieces: a knight, a bishop and a rook. At first, you put one of them on the square with the number $ 1 $ (you can choose which one). Then you want to reach square $ 2 $ (possibly passing through some other squares in process), then square $ 3 $ and so on until you reach square $ N^2 $ . In one step you are allowed to either make a valid move with the current piece or replace it with some other piece. Each square can be visited arbitrary number of times.

A knight can move to a square that is two squares away horizontally and one square vertically, or two squares vertically and one square horizontally. A bishop moves diagonally. A rook moves horizontally or vertically. The move should be performed to a different square from the one a piece is currently standing on.

You want to minimize the number of steps of the whole traversal. Among all the paths to have the same number of steps you want to choose the one with the lowest number of piece replacements.

What is the path you should take to satisfy all conditions?

## 说明/提示

Here are the steps for the first example (the starting piece is a knight):

1. Move to $ (3, 2) $
2. Move to $ (1, 3) $
3. Move to $ (3, 2) $
4. Replace the knight with a rook
5. Move to $ (3, 1) $
6. Move to $ (3, 3) $
7. Move to $ (3, 2) $
8. Move to $ (2, 2) $
9. Move to $ (2, 3) $
10. Move to $ (2, 1) $
11. Move to $ (1, 1) $
12. Move to $ (1, 2) $

## 样例 #1

### 输入

```
3
1 9 3
8 6 7
4 2 5
```

### 输出

```
12 1
```

# 题解

## 作者：Weng_Weijie (赞：4)

很容易想到dp

令f[0/1/2][i][j][k]表示当前用的是哪个棋子，在(i,j)位置，已经填完了1~k中的所有数的最小花费

（由于要求步数最小同时交换次数最少于是考虑设一个较大的阈值M, 将步数乘上M作为代价，这样就可以实现双关键字）

但是这样dp会有一个问题：不知道转移的顺序

于是考虑用最短路

对每个状态建一个点，对每种转移连一条边

这样就可以不考虑转移顺序求出dp值了

具体的，转移有以下几种：

交换棋子：棋子变，位置、填的数不变，花费为M+1

移动棋子：位置变，棋子、填的数不变，花费为M
（需要对3种棋子单独考虑）

填数（当(i,j)位置的数为下一个数）：填的数变，棋子、位置不变，花费为0

跑dijkstra即可

```cpp
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 11;
int p[N][N], px[N * N], py[N * N], n, vis[N * N * N * N * 3];
int status[3][N][N][N * N], tot, head[N * N * N * N * 3];
const int M = 1000000;
typedef long long LL;
LL dis[N * N * N * N * 3];
const int dx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int dy[8] = {1, -1, 2, 2, 1, -1, -2, -2};
const int _dx[4] = {1, -1, 1, -1};
const int _dy[4] = {1, 1, -1, -1};
struct edge {
	int to, nxt, cost;
} e[9999999];
void addedge(int x, int y, int z) {
	e[++tot] = (edge) {y, head[x], z}; head[x] = tot;
}
int main() {
	std::scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			std::scanf("%d", &p[i][j]);
			px[p[i][j]] = i;
			py[p[i][j]] = j;
		}
	for (int i = 0; i < 3; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				for (int l = 1; l <= n * n; l++) 
					status[i][j][k][l] = ++tot;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n * n; k++) {
				addedge(status[0][i][j][k], status[1][i][j][k], M + 1);
				addedge(status[0][i][j][k], status[2][i][j][k], M + 1);
				addedge(status[1][i][j][k], status[0][i][j][k], M + 1);
				addedge(status[1][i][j][k], status[2][i][j][k], M + 1);
				addedge(status[2][i][j][k], status[0][i][j][k], M + 1);
				addedge(status[2][i][j][k], status[1][i][j][k], M + 1);
				if (k + 1 == p[i][j]) {
					addedge(status[0][i][j][k], status[0][i][j][k + 1], 0);
					addedge(status[1][i][j][k], status[1][i][j][k + 1], 0);
					addedge(status[2][i][j][k], status[2][i][j][k + 1], 0);
				}
				for (int p = 1; p <= n; p++) {
					if (p != i)
						addedge(status[0][i][j][k], status[0][p][j][k], M);
					if (p != j)
						addedge(status[0][i][j][k], status[0][i][p][k], M);
				}
				for (int p = 0; p < 8; p++) {
					int _x = i + dx[p], _y = j + dy[p];
					if (_x < 0 || _x > n || _y < 0 || _y > n) continue;
					addedge(status[1][i][j][k], status[1][_x][_y][k], M);
				}
				for (int p = 1; p <= n; p++) {
					for (int d = 0; d < 4; d++) {
						int _x = i + _dx[d] * p, _y = j + _dy[d] * p;
						if (_x < 0 || _x > n || _y < 0 || _y > n) continue;
						addedge(status[2][i][j][k], status[2][_x][_y][k], M);
					}
				}
			}
		}
	std::memset(dis, 0x3f, sizeof dis);
	std::priority_queue<std::pair<LL, int> > q;
	for (int i = 0; i < 3; i++) {
		dis[status[i][px[1]][py[1]][1]] = 0;
		q.push(std::make_pair(0, status[i][px[1]][py[1]][1]));
	}
	while (q.size()) {
		int tmp = q.top().second; q.pop();
		if (vis[tmp]) continue;
		for (int i = head[tmp]; i; i = e[i].nxt)
			if (dis[e[i].to] > dis[tmp] + e[i].cost) {
				dis[e[i].to] = dis[tmp] + e[i].cost;
				q.push(std::make_pair(-dis[e[i].to], e[i].to));
			}
	}
	LL ans = 0x3f3f3f3f3f3f3f3fLL;
	for (int k = 0; k < 3; k++) 
		ans = std::min(ans, dis[status[k][px[n * n]][py[n * n]][n * n]]);
	std::printf("%lld %lld\n", ans / M, ans % M);
	return 0;
}

```

---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 2200}$
---
### 解题思路：

实际上是两个 $\text{trick}$ 的考。

考虑只有一个棋子，直接根据棋子的移动建图，然后跑一下最短路，依次计算就行了。

问题在于有三种棋子，而且转化是有代价的，那不妨将一个点建成三个，分别表示骑士（也就是马），相，车，然后这些点之间能够在同一个点上进行转化，其它的都是一样的。这就是一个经典的分层建图的 $\text{trick}$。

但是边权直接按照 $1$ 建立是会出问题的，不仅无法解决双关键字排序，就连输出转化次数都做不到。这里就用到第二个 $\text{trick}$，将同一层点与点之间的边权设置为一个很大的值，然后将同一个点上棋子的转化的权值设置为那个值加上一个很小的值，这样就实现了提取棋子转化次数和双关键字代价（方法不唯一，这是比较简单的一种）。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[1005][1005],p[10005],cnt,f[1005][1005],f2[10005][3],ans;
int calc(int x,int y){
	if(x<=0||y<=0||x>n||y>n)return -1;
	return 3*((x-1)*n+y);
}
void add(int x,int y,int num){
	f[x][y]=f[y][x]=num;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		scanf("%d",&a[i][j]);
		p[a[i][j]]=calc(i,j);
	}
	cnt=3*n*n;
	for(int i=1;i<=cnt;i++)
	for(int j=1;j<=cnt;j++)
	f[i][j]=10000000;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(calc(i+1,j+2)!=-1)add(calc(i,j),calc(i+1,j+2),1000);
			if(calc(i+1,j-2)!=-1)add(calc(i,j),calc(i+1,j-2),1000);
			if(calc(i-1,j+2)!=-1)add(calc(i,j),calc(i-1,j+2),1000);
			if(calc(i-1,j-2)!=-1)add(calc(i,j),calc(i-1,j-2),1000);
			if(calc(i+2,j+1)!=-1)add(calc(i,j),calc(i+2,j+1),1000);
			if(calc(i+2,j-1)!=-1)add(calc(i,j),calc(i+2,j-1),1000);
			if(calc(i-2,j+1)!=-1)add(calc(i,j),calc(i-2,j+1),1000);
			if(calc(i-2,j-1)!=-1)add(calc(i,j),calc(i-2,j-1),1000);
			//马的同层建图，一共八个方向 
			
			for(int k=1;k<=n;k++){
				if(calc(i+k,j+k)!=-1)add(calc(i,j)-1,calc(i+k,j+k)-1,1000);
				if(calc(i+k,j-k)!=-1)add(calc(i,j)-1,calc(i+k,j-k)-1,1000);
				if(calc(i-k,j+k)!=-1)add(calc(i,j)-1,calc(i-k,j+k)-1,1000);
				if(calc(i-k,j-k)!=-1)add(calc(i,j)-1,calc(i-k,j-k)-1,1000);
			}//相的同层建图 
			
			for(int k=1;k<=n;k++){
				if(calc(i,k)!=-1)add(calc(i,j)-2,calc(i,k)-2,1000);
				if(calc(k,j)!=-1)add(calc(i,j)-2,calc(k,j)-2,1000);
			}//车的同层建图 
			
			add(calc(i,j),calc(i,j)-1,1001);
			add(calc(i,j),calc(i,j)-2,1001);
			add(calc(i,j)-2,calc(i,j)-1,1001);
			//同点棋子转化 
		}
	}
	for(int i=1;i<=cnt;i++)
	f[i][i]=0;
	
	for(int k=1;k<=cnt;k++)
	for(int i=1;i<=cnt;i++)
	if(i!=k)
	for(int j=1;j<=cnt;j++)
	if(i!=j&&j!=k)
	f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	//平凡的最短路，反正点少，随便欺负。 
	
	for(int i=2;i<=n*n;i++){
		f2[i][2]=min(f2[i-1][2]+f[p[i]  ][p[i-1]],min(f2[i-1][1]+f[p[i]  ][p[i-1]-1],f2[i-1][0]+f[p[i]  ][p[i-1]-2]));
		f2[i][1]=min(f2[i-1][2]+f[p[i]-1][p[i-1]],min(f2[i-1][1]+f[p[i]-1][p[i-1]-1],f2[i-1][0]+f[p[i]-1][p[i-1]-2]));
		f2[i][0]=min(f2[i-1][2]+f[p[i]-2][p[i-1]],min(f2[i-1][1]+f[p[i]-2][p[i-1]-1],f2[i-1][0]+f[p[i]-2][p[i-1]-2]));
	}
	//一个一个点走。 
	ans=min(min(f2[n*n][1],f2[n*n][0]),f2[n*n][2]);
	printf("%d %d\n",ans/1000,ans%1000);
	return 0;
}
```


---

## 作者：EityDawn (赞：2)

# 思路：

拆点跑最短路。

把 $n^2$ 个点拆成 $3n^2$ 个，对应马，象和车三种状态。

不同状态之间连一条 $1$ 的边，相同的连 $0$，连边按照三种棋的走法连即可。

对于要依次遍历 $1,2,3,...,n^2$ 的限制，我们可以先以 $1$ 的三种状态为起点跑最短路，接着以 $2$ 的三种状态跑最短路，以此类推，到以 $n^2-1$ 的三种状态为起点跑最短路，即可得出最终到 $n^2$ 的最短路、

注意每次换起点跑最短路，除起点外上一次最短路的状态都要清除。

复杂度为 $O(n^4\log n)$。

```cpp
const int N=11,inf=1e9;
int id[N][N],val[N*N],n;
vector<pair<int,int>>G[N*N*3];
int ds[N*N*3],dc[N*N*3];
bool vis[N*N*3];
int dx[8]={-2,-2,-1,-1,1,1,2,2},dy[8]={-1,1,-2,2,-2,2,-1,1};
void Dijistra(int St)
{
    for(int i=1;i<=n*n;i++)
    {
        if(St==i) continue;
        else for(int j=1;j<=3;j++)
            ds[(i-1)*3+j]=dc[(i-1)*3+j]=inf;
    }
    memset(vis,0,sizeof(vis));
    priority_queue<pair<int,int>>q;
    q.push({-ds[(St-1)*3+1],(St-1)*3+1});
    q.push({-ds[(St-1)*3+2],(St-1)*3+2});
    q.push({-ds[(St-1)*3+3],(St-1)*3+3});
    while(q.size())
    {
        auto [D,now]=q.top();q.pop();
	    if(vis[now]) continue;
        vis[now]=1;
        for(auto [to,val]:G[now])
        {
            if(ds[to]>ds[now]+1+val){
                ds[to]=ds[now]+1+val,dc[to]=dc[now]+val;
                q.push({-ds[to],to});
            }
            else if(ds[to]==ds[now]+1+val){
                if(dc[to]>dc[now]+val){
                    dc[to]=dc[now]+val,q.push({-ds[to],to});
                }
            }
        }
    }
    return;
}
int main()
{
    fin>>n;
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=n;j++) 
            fin>>x,val[x]=(id[i][j]=(i-1)*n+j);
    for(int i=1,x,y;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            x=id[i][j];
            for(int p=1;p<=3;p++)
                for(int q=1;q<=3;q++)
                {
                    if(q==1){
                        for(int k=0;k<8;k++)
                        {
                            int nx=i+dx[k],ny=j+dy[k];
                            if(nx<1||ny<1||nx>n||ny>n) continue;
                            y=id[nx][ny];
                            G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                        }
                    }
                    if(q==2){
                        for(int nx=i-1,ny=j-1;nx&&ny;nx--,ny--)
                            y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                        for(int nx=i-1,ny=j+1;nx&&ny<=n;nx--,ny++)
                            y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                        for(int nx=i+1,ny=j-1;nx<=n&&ny;nx++,ny--)
                            y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                        for(int nx=i+1,ny=j+1;nx<=n&&ny<=n;nx++,ny++)
                            y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                    }
                    if(q==3){
                        for(int nx=i,ny=j+1;ny<=n;ny++)
                             y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                        for(int nx=i,ny=j-1;ny;ny--)
                             y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                        for(int nx=i-1,ny=j;nx;nx--)
                             y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                        for(int nx=i+1,ny=j;nx<=n;nx++)
                             y=id[nx][ny],G[(x-1)*3+p].push_back({(y-1)*3+q,p!=q});
                    }
                }
        }
    for(int i=1;i<n*n;i++) Dijistra(val[i]);
    pair<int,int>x={ds[(val[n*n]-1)*3+1],dc[(val[n*n]-1)*3+1]};
    pair<int,int>y={ds[(val[n*n]-1)*3+2],dc[(val[n*n]-1)*3+2]};
    pair<int,int>z={ds[(val[n*n]-1)*3+3],dc[(val[n*n]-1)*3+3]};
    pair<int,int>Ans=min({x,y,z});
    fout<<Ans.first<<' '<<Ans.second;
    return 0;
}
```

---

## 作者：leozhang (赞：2)

如果不喜欢过长代码的看官，请移步其他题解...

这题其实思想极其简单：

棋盘问题常见的算法都比较暴力，常用的有搜索和状压dp

而这道题显然没啥能状压的，所以我们考虑搜索

但是仅仅搜索是不够的，因为有极大的可能搜到死...

所以我们引入记忆化

设状态f[i][j][k][0/1/2]代表目前在点（i，j）处，上一个到达的点（注意是达成要求而非经过）的编号为k，目前的棋子种类为1/2/3时，所需要的最小代价

当然这还不够，我们还要保证在代价最小时更换棋子次数最小，所以我们再用状态g[i][j][k][0/1/2]更新，下标含义与上述相同，表示对应状态所需的最小棋子更换次数

注意优先更新f，在保证f合法的情况下维护g

然后用bfs更新即可

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <set>
#include <deque>
#include <bitset>
using namespace std;
int dp[15][15][105][3];
int g[15][15][105][3];
int xp[105],yp[105];
int maps[15][15];
int dir[8][2]={{1,2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,-1},{1,-2},{-2,1}};
int n;
bool check(int x,int y)
{
	if(x>0&&x<=n&&y>0&&y<=n)
	{
		return 1;
	}
	return 0;
}
void bfs()
{
	memset(dp,0x3f,sizeof(dp));
	memset(g,0x3f,sizeof(g));
	dp[xp[1]][yp[1]][1][0]=0;//车 
	dp[xp[1]][yp[1]][1][1]=0;//马 
	dp[xp[1]][yp[1]][1][2]=0;//象 
	g[xp[1]][yp[1]][1][0]=0;
	g[xp[1]][yp[1]][1][1]=0;
	g[xp[1]][yp[1]][1][2]=0;
	queue <int> Qx,Qy,Qz,Qv;
	for(int i=0;i<=2;i++)
	{
		Qx.push(xp[1]);
		Qy.push(yp[1]);
		Qz.push(i);
		Qv.push(1);
	}
	while(!Qx.empty())
	{
		int ux=Qx.front();
		int uy=Qy.front();
		int uz=Qz.front();
		int uv=Qv.front();
		Qx.pop();
		Qy.pop();
		Qz.pop();
		Qv.pop();
		if(uv==n*n)
		{
			continue;
		}
		if(uz==0)
		{
			for(int i=1;i<=n;i++)
			{
				if(i==uy)
				{
					continue;
				}
				if(maps[ux][i]==uv+1)
				{
					if(dp[ux][i][uv+1][uz]>dp[ux][uy][uv][uz]+1)
					{
						dp[ux][i][uv+1][uz]=dp[ux][uy][uv][uz]+1;
						g[ux][i][uv+1][uz]=g[ux][uy][uv][uz];
						Qx.push(ux);
						Qy.push(i);
						Qz.push(uz);
						Qv.push(uv+1);
					}else if(dp[ux][i][uv+1][uz]==dp[ux][uy][uv][uz]+1&&g[ux][i][uv+1][uz]>g[ux][uy][uv][uz])
					{
						g[ux][i][uv+1][uz]=g[ux][uy][uv][uz];
						Qx.push(ux);
						Qy.push(i);
						Qz.push(uz);
						Qv.push(uv+1);
					}
				}else
				{
					if(dp[ux][i][uv][uz]>dp[ux][uy][uv][uz]+1)
					{
						dp[ux][i][uv][uz]=dp[ux][uy][uv][uz]+1;
						g[ux][i][uv][uz]=g[ux][uy][uv][uz];
						Qx.push(ux);
						Qy.push(i);
						Qz.push(uz);
						Qv.push(uv);
					}else if(dp[ux][i][uv][uz]==dp[ux][uy][uv][uz]+1&&g[ux][i][uv][uz]>g[ux][uy][uv][uz])
					{
						g[ux][i][uv][uz]=g[ux][uy][uv][uz];
						Qx.push(ux);
						Qy.push(i);
						Qz.push(uz);
						Qv.push(uv);
					}
				}
			}
			for(int i=1;i<=n;i++)
			{
				if(i==ux)
				{
					continue;
				}
				if(maps[i][uy]==uv+1)
				{
					if(dp[i][uy][uv+1][uz]>dp[ux][uy][uv][uz]+1)
					{
						dp[i][uy][uv+1][uz]=dp[ux][uy][uv][uz]+1;
						g[i][uy][uv+1][uz]=g[ux][uy][uv][uz];
						Qx.push(i);
						Qy.push(uy);
						Qz.push(uz);
						Qv.push(uv+1);
					}else if(dp[i][uy][uv+1][uz]==dp[ux][uy][uv][uz]+1&&g[i][uy][uv+1][uz]>g[ux][uy][uv][uz])
					{
						g[i][uy][uv+1][uz]=g[ux][uy][uv][uz];
						Qx.push(i);
						Qy.push(uy);
						Qz.push(uz);
						Qv.push(uv+1);
					}
				}else
				{
					if(dp[i][uy][uv][uz]>dp[ux][uy][uv][uz]+1)
					{
						dp[i][uy][uv][uz]=dp[ux][uy][uv][uz]+1;
						g[i][uy][uv][uz]=g[ux][uy][uv][uz];
						Qx.push(i);
						Qy.push(uy);
						Qz.push(uz);
						Qv.push(uv);
					}else if(dp[i][uy][uv][uz]==dp[ux][uy][uv][uz]+1&&g[i][uy][uv][uz]>g[ux][uy][uv][uz])
					{
						g[i][uy][uv][uz]=g[ux][uy][uv][uz];
						Qx.push(i);
						Qy.push(uy);
						Qz.push(uz);
						Qv.push(uv);
					}
				}
			}
			if(dp[ux][uy][uv][1]>dp[ux][uy][uv][uz]+1)
			{
				dp[ux][uy][uv][1]=dp[ux][uy][uv][uz]+1;
				g[ux][uy][uv][1]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(1);
				Qv.push(uv);
			}else if(dp[ux][uy][uv][1]==dp[ux][uy][uv][uz]+1&&g[ux][uy][uv][1]>g[ux][uy][uv][uz]+1)
			{
				g[ux][uy][uv][1]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(1);
				Qv.push(uv);
			}
			if(dp[ux][uy][uv][2]>dp[ux][uy][uv][uz]+1)
			{
				dp[ux][uy][uv][2]=dp[ux][uy][uv][uz]+1;
				g[ux][uy][uv][2]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(2);
				Qv.push(uv);
			}else if(dp[ux][uy][uv][2]==dp[ux][uy][uv][uz]+1&&g[ux][uy][uv][2]>g[ux][uy][uv][uz]+1)
			{
				g[ux][uy][uv][2]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(2);
				Qv.push(uv);
			}
		}else if(uz==1)//马 
		{
			for(int i=0;i<8;i++)
			{
				int tx=ux+dir[i][0];
				int ty=uy+dir[i][1];
				if(tx<=0||tx>n||ty<=0||ty>n)
				{
					continue;
				}
				if(maps[tx][ty]==uv+1)
				{
					if(dp[tx][ty][uv+1][1]>dp[ux][uy][uv][1]+1)
					{
						dp[tx][ty][uv+1][1]=dp[ux][uy][uv][1]+1;
						g[tx][ty][uv+1][1]=g[ux][uy][uv][1];
						Qx.push(tx);
						Qy.push(ty);
						Qv.push(uv+1);
						Qz.push(1);
					}else if(dp[tx][ty][uv+1][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv+1][uz]>g[ux][uy][uv][uz])
					{
						g[tx][ty][uv+1][uz]=g[ux][uy][uv][uz];
						Qx.push(tx);
						Qy.push(ty);
						Qz.push(uz);
						Qv.push(uv+1);
					} 
				}else
				{
					if(dp[tx][ty][uv][1]>dp[ux][uy][uv][1]+1)
					{
						dp[tx][ty][uv][1]=dp[ux][uy][uv][1]+1;
						g[tx][ty][uv][1]=g[ux][uy][uv][1];
						Qx.push(tx);
						Qy.push(ty);
						Qv.push(uv);
						Qz.push(1);
					}else if(dp[tx][ty][uv][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv][uz]>g[ux][uy][uv][uz])
					{
						g[tx][ty][uv][uz]=g[ux][uy][uv][uz];
						Qx.push(tx);
						Qy.push(ty);
						Qz.push(uz);
						Qv.push(uv);
					} 
				}
			}
			if(dp[ux][uy][uv][0]>dp[ux][uy][uv][uz]+1)
			{
				dp[ux][uy][uv][0]=dp[ux][uy][uv][uz]+1;
				g[ux][uy][uv][0]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(0);
				Qv.push(uv);
			}else if(dp[ux][uy][uv][0]==dp[ux][uy][uv][uz]+1&&g[ux][uy][uv][0]>g[ux][uy][uv][uz]+1)
			{
				g[ux][uy][uv][0]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(0);
				Qv.push(uv);
			}
			if(dp[ux][uy][uv][2]>dp[ux][uy][uv][uz]+1)
			{
				dp[ux][uy][uv][2]=dp[ux][uy][uv][uz]+1;
				g[ux][uy][uv][2]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(2);
				Qv.push(uv);
			}else if(dp[ux][uy][uv][2]==dp[ux][uy][uv][uz]+1&&g[ux][uy][uv][2]>g[ux][uy][uv][uz]+1)
			{
				g[ux][uy][uv][2]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(2);
				Qv.push(uv);
			}
		}else if(uz==2)
		{
			for(int i=1;i<=n;i++)
			{
				int tx=ux+i;
				int ty=uy+i;
				if(check(tx,ty))
				{
					if(maps[tx][ty]==uv+1)
					{
						if(dp[tx][ty][uv+1][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv+1][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv+1][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv+1);
							Qz.push(2);
						}else if(dp[tx][ty][uv+1][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv+1][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv+1][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv+1);
						} 
					}else
					{
						if(dp[tx][ty][uv][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv);
							Qz.push(2);
						}else if(dp[tx][ty][uv][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv+1][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv+1);
						} 
					}
				}
				tx=ux+i;
				ty=uy-i;
				if(check(tx,ty))
				{
					if(maps[tx][ty]==uv+1)
					{
						if(dp[tx][ty][uv+1][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv+1][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv+1][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv+1);
							Qz.push(2);
						}else if(dp[tx][ty][uv+1][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv+1][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv+1][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv+1);
						} 
					}else
					{
						if(dp[tx][ty][uv][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv);
							Qz.push(2);
						}else if(dp[tx][ty][uv][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv);
						} 
					}
				}
				tx=ux-i;
				ty=uy+i;
				if(check(tx,ty))
				{
					if(maps[tx][ty]==uv+1)
					{
						if(dp[tx][ty][uv+1][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv+1][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv+1][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv+1);
							Qz.push(2);
						}else if(dp[tx][ty][uv+1][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv+1][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv+1][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv+1);
						} 
					}else
					{
						if(dp[tx][ty][uv][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv);
							Qz.push(2);
						}else if(dp[tx][ty][uv][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv);
						} 
					}
				}
				tx=ux-i;
				ty=uy-i;
				if(check(tx,ty))
				{
					if(maps[tx][ty]==uv+1)
					{
						if(dp[tx][ty][uv+1][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv+1][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv+1][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv+1);
							Qz.push(2);
						}else if(dp[tx][ty][uv+1][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv+1][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv+1][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv+1);
						}  
					}else
					{
						if(dp[tx][ty][uv][2]>dp[ux][uy][uv][2]+1)
						{
							dp[tx][ty][uv][2]=dp[ux][uy][uv][2]+1;
							g[tx][ty][uv][2]=g[ux][uy][uv][2];
							Qx.push(tx);
							Qy.push(ty);
							Qv.push(uv);
							Qz.push(2);
						}else if(dp[tx][ty][uv][uz]==dp[ux][uy][uv][uz]+1&&g[tx][ty][uv][uz]>g[ux][uy][uv][uz])
						{
							g[tx][ty][uv][uz]=g[ux][uy][uv][uz];
							Qx.push(tx);
							Qy.push(ty);
							Qz.push(uz);
							Qv.push(uv);
						} 
					}
				}
			}
			if(dp[ux][uy][uv][0]>dp[ux][uy][uv][uz]+1)
			{
				dp[ux][uy][uv][0]=dp[ux][uy][uv][uz]+1;
				g[ux][uy][uv][0]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(0);
				Qv.push(uv);
			}else if(dp[ux][uy][uv][1]>dp[ux][uy][uv][uz]+1&&g[ux][uy][uv][0]>g[ux][uy][uv][uz]+1)
			{
				g[ux][uy][uv][0]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(0);
				Qv.push(uv);
			}
			if(dp[ux][uy][uv][1]>dp[ux][uy][uv][uz]+1)
			{
				dp[ux][uy][uv][1]=dp[ux][uy][uv][uz]+1;
				g[ux][uy][uv][1]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(1);
				Qv.push(uv);
			}else if(dp[ux][uy][uv][1]==dp[ux][uy][uv][uz]+1&&g[ux][uy][uv][1]>g[ux][uy][uv][uz]+1)
			{
				g[ux][uy][uv][1]=g[ux][uy][uv][uz]+1;
				Qx.push(ux);
				Qy.push(uy);
				Qz.push(1);
				Qv.push(uv);
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&maps[i][j]);
			xp[maps[i][j]]=i;
			yp[maps[i][j]]=j;
		}
	}
	bfs();
	int ans=0x3f3f3f3f;
	int ret=0x3f3f3f3f;
	for(int i=0;i<=2;i++)
	{
		if(ans>dp[xp[n*n]][yp[n*n]][n*n][i])
		{
			ans=dp[xp[n*n]][yp[n*n]][n*n][i];
			ret=g[xp[n*n]][yp[n*n]][n*n][i];
		}else if(ret>g[xp[n*n]][yp[n*n]][n*n][i]&&ans==dp[xp[n*n]][yp[n*n]][n*n][i])
		{
			ret=g[xp[n*n]][yp[n*n]][n*n][i];
		}
	}
	printf("%d %d\n",ans,ret);
	return 0;
}

```

---

## 作者：igAC (赞：1)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1065D)

[CFlink](https://codeforces.com/problemset/problem/1065/D)

简要题意：

给定一个 $n \times n$ 的矩阵，里面的元素可以构成 $1 \sim n \times n$ 的排列。

你要从 $1$ 依次走到 $n \times n$，中途走到其他点也是可以的。

有三种走的方式（国际象棋中的车、马、象），走一步需要一秒，变换方式需要一秒。

求最短时间，以及在最短时间的要求下，最少的变换次数。

# $\text{Solution}$

vp 的时候看到的一道比较有细节的题。

看到最短时间，第一时间想到最短路，但是这道题要两个变量，用 struct 即可。

现在考虑如何建图。

设 $pos(i,j,k,p)$ 表示当前在 $(i,j)$ 目前已经走到了 $1 \sim k$，且移动的方式是 $p$ 的节点编号。

转变移动方式非常简单 $pos(i,j,k,p) \overset{1,1}{\rightarrow} pos(i,j,k,q)(p \neq q)$。

代码实现：

```cpp
for(int i=1;i<=n;++i){
	for(int j=1;j<=n;++j){
		for(int k=1;k<=n*n;++k){
			for(int p=0;p<3;++p){
				for(int q=0;q<3;++q){
					if(p==q) continue;
					add_edge(pos(i,j,k,p),pos(i,j,k,q),{1,1});//change
				}
			}
		}
	}
}
```

接下来是各种移动方式的移动，这里直接给出代码。

建边：

```cpp
int head[3*N*N*N*N],tot;
struct node{
	ll stp,chan;
};
struct Edge{
	int to,nxt;
	node val;
}e[9400005];
void add_edge(int x,int y,node z){
	e[++tot].to=y;
	e[tot].val=z;
	e[tot].nxt=head[x];
	head[x]=tot;
}
```

车的移动：

```cpp
const int dx_c[4]={1,0,-1,0};
const int dy_c[4]={0,1,0,-1};
//car_move
for(int t=1;t<=n;++t){//枚举距离
	for(int p=0;p<4;++p){//枚举方向
		int nx=i+dx_c[p]*t;
		int ny=j+dy_c[p]*t;
		if(!check(nx,ny)) continue;
		if(a[nx][ny]==k+1) add_edge(pos(i,j,k,0),pos(nx,ny,k+1,0),{1,0});
		else add_edge(pos(i,j,k,0),pos(nx,ny,k,0),{1,0});
	}
}
```

马的移动：

```cpp
const int dx_h[8]={1,2,2,1,-1,-2,-2,-1};
const int dy_h[8]={2,1,-1,-2,2,1,-1,-2};
//horse_move
for(int p=0;p<8;++p){
	int nx=i+dx_h[p];
	int ny=j+dy_h[p];
	if(!check(nx,ny)) continue;
	if(a[nx][ny]==k+1) add_edge(pos(i,j,k,1),pos(nx,ny,k+1,1),{1,0});
	else add_edge(pos(i,j,k,1),pos(nx,ny,k,1),{1,0});
}
```

象的移动：

```cpp
const int dx_e[4]={1,-1,1,-1};
const int dy_e[4]={1,1,-1,-1};
//elephant_move
for(int t=1;t<=n;++t){
	for(int p=0;p<4;++p){
		int nx=i+dx_e[p]*t;
		int ny=j+dy_e[p]*t;
		if(!check(nx,ny)) continue;
		if(a[nx][ny]==k+1) add_edge(pos(i,j,k,2),pos(nx,ny,k+1,2),{1,0});
		else add_edge(pos(i,j,k,2),pos(nx,ny,k,2),{1,0});
	}
}
```

具体实现可参考完整代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define LLINF 1e18
#define N 11
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,a[N][N],sx,sy,tx,ty;
int head[3*N*N*N*N],tot;
bool vis[3*N*N*N*N];
struct node{//这里的各种重定义更加方便，大家也可以去看看第一篇题解的解决方法，很精妙
	ll stp,chan;
	friend bool operator < (const node &a,const node &b){
		return a.stp==b.stp?a.chan<b.chan:a.stp<b.stp;
	}
	friend bool operator > (const node &a,const node &b){
		return a.stp==b.stp?a.chan>b.chan:a.stp>b.stp;
	}
};
node dis[3*N*N*N*N],ans={(ll)LLINF,(ll)LLINF};
node operator + (const node &a,const node &b){
	node c;
	c.stp=a.stp+b.stp;
	c.chan=a.chan+b.chan;
	return c;
}
struct Edge{
	int to,nxt;
	node val;
}e[9400005];
void add_edge(int x,int y,node z){
	e[++tot].to=y;
	e[tot].val=z;
	e[tot].nxt=head[x];
	head[x]=tot;
}
int pos(int i,int j,int k,int p){return p*n*n*n*n+(i-1)*n*n*n+(j-1)*n*n+k;}
const int dx_c[4]={1,0,-1,0};
const int dy_c[4]={0,1,0,-1};
const int dx_h[8]={1,2,2,1,-1,-2,-2,-1};
const int dy_h[8]={2,1,-1,-2,2,1,-1,-2};
const int dx_e[4]={1,-1,1,-1};
const int dy_e[4]={1,1,-1,-1};
bool check(int i,int j){return (1<=i && i<=n && 1<=j && j<=n);}
void Dij(){
	for(int i=0;i<=3*n*n*n*n;++i) dis[i]={(ll)LLINF,(ll)LLINF};
	priority_queue<pair<node,int>>q;
	for(int i=0;i<3;++i) q.push({dis[pos(sx,sy,1,i)]={0,0},pos(sx,sy,1,i)});
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;node z=e[i].val;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				q.push({{-dis[y].stp,-dis[y].chan},y});
			}
		}
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			a[i][j]=read();
			if(a[i][j]==1) sx=i,sy=j;
			if(a[i][j]==n*n) tx=i,ty=j;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=n*n;++k){
				for(int p=0;p<3;++p){
					for(int q=0;q<3;++q){
						if(p==q) continue;
						add_edge(pos(i,j,k,p),pos(i,j,k,q),{1,1});//change
					}
				}
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<n*n;++k){
				//car_move
				for(int t=1;t<=n;++t){
					for(int p=0;p<4;++p){
						int nx=i+dx_c[p]*t;
						int ny=j+dy_c[p]*t;
						if(!check(nx,ny)) continue;
						if(a[nx][ny]==k+1) add_edge(pos(i,j,k,0),pos(nx,ny,k+1,0),{1,0});
						else add_edge(pos(i,j,k,0),pos(nx,ny,k,0),{1,0});
					}
				}
				//horse_move
				for(int p=0;p<8;++p){
					int nx=i+dx_h[p];
					int ny=j+dy_h[p];
					if(!check(nx,ny)) continue;
					if(a[nx][ny]==k+1) add_edge(pos(i,j,k,1),pos(nx,ny,k+1,1),{1,0});
					else add_edge(pos(i,j,k,1),pos(nx,ny,k,1),{1,0});
				}
				//elephant_move
				for(int t=1;t<=n;++t){
					for(int p=0;p<4;++p){
						int nx=i+dx_e[p]*t;
						int ny=j+dy_e[p]*t;
						if(!check(nx,ny)) continue;
						if(a[nx][ny]==k+1) add_edge(pos(i,j,k,2),pos(nx,ny,k+1,2),{1,0});
						else add_edge(pos(i,j,k,2),pos(nx,ny,k,2),{1,0});
					}
				}
			}
		}
	}
	Dij();
	for(int i=0;i<3;++i) if(ans>dis[pos(tx,ty,n*n,i)]) ans=dis[pos(tx,ty,n*n,i)];
	printf("%lld %lld",ans.stp,ans.chan);
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
第一次切这种难度的状压 dp，上一次差点切的是 abc349F。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
这个题一拿到的时候就很没思路了，感觉不是很可做。

因为每一步都有换/不换种类和不同移动方式的可能性，看上去就非常难办。

仔细一看，$n\le10$，直接考虑乱搞，保证正确性即可。

对于点要按顺序一个个经过，考虑设计 $dp_{i,x,y}$ 表示其棋子为 $i$ （分别表示车马象），走到点 $x,y$ 的最短距离。

转移考虑按照经过的顺序转移最后取 $\min$ 即可获得答案。

接着考虑转移方程中要用到 $e_{i,x',y',x,y}$ 代表从 $x',y'$ 点走到 $x,y$，最后棋子是 $i$ 的最短路径长度，貌似很难处理？

因为最短路径上棋子可以没走几步就换一个种类再继续走，也就是由多段不同种类棋子走的路径拼接而来。

状态有整整四维：棋子种类，$x,y$ 坐标，所用时间。

考虑状压给前三维压在一起，这样就可以对每个状态建立一个点构建图论模型了。

因为数据范围很小，所以考虑直接把图建出来大力跑 fload 最短路求出两个状态的最短距离。

接着再扔回原本那个 dp 上就可以解决了。

但这样就会有一个问题：**以及在确保时间最短的情况下，棋子更换次数的最小值**无法处理了。

考虑经典 trick，把时间的边权从 $1$ 变为极大值，而更换一次的额外边权为 $1$，这样就相当于是双关键字排序了（本质也就是状压）。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=15,M=675,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,ans,a[M];int e[M][M],f[3][M];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int get(int x,int y){return (x<1||y<1||x>n||y>n)?0:3*((x-1)*n+y);}
inline void add(int x,int y,int w){e[x][y]=e[y][x]=w;}
signed main()
{
    n=read();memset(e,0x3f,sizeof e);m=3*n*n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[read()]=get(i,j);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(get(i+1,j+2)) add(get(i,j),get(i+1,j+2),1000);
            if(get(i+1,j-2)) add(get(i,j),get(i+1,j-2),1000);
            if(get(i-1,j+2)) add(get(i,j),get(i-1,j+2),1000);
            if(get(i-1,j-2)) add(get(i,j),get(i-1,j-2),1000);
            if(get(i+2,j+1)) add(get(i,j),get(i+2,j+1),1000);
            if(get(i+2,j-1)) add(get(i,j),get(i+2,j-1),1000);
            if(get(i-2,j+1)) add(get(i,j),get(i-2,j+1),1000);
            if(get(i-2,j-1)) add(get(i,j),get(i-2,j-1),1000);
            for(int k=1;k<=n;k++)
            {
                if(get(i+k,j+k)) add(get(i,j)-1,get(i+k,j+k)-1,1000);
                if(get(i+k,j-k)) add(get(i,j)-1,get(i+k,j-k)-1,1000);
                if(get(i-k,j+k)) add(get(i,j)-1,get(i-k,j+k)-1,1000);
                if(get(i-k,j-k)) add(get(i,j)-1,get(i-k,j-k)-1,1000);
            }
            for(int k=1;k<=n;k++)
            {
                if(get(i,k)) add(get(i,j)-2,get(i,k)-2,1000);
                if(get(k,j)) add(get(i,j)-2,get(k,j)-2,1000);
            } 
            add(get(i,j),get(i,j)-1,1001);add(get(i,j),get(i,j)-2,1001);add(get(i,j)-2,get(i,j)-1,1001);
        }
    for(int i=1;i<=m;i++) e[i][i]=0;
    for(int k=1;k<=m;k++) for(int i=1;i<=m;i++)
        if(i^k) for(int j=1;j<=m;j++) if(i^j&&j^k)
            e[i][j]=min(e[i][j],e[i][k]+e[k][j]);
    for(int i=2;i<=n*n;i++)
        f[0][i]=min(f[2][i-1]+e[a[i]-2][a[i-1]],min(f[1][i-1]+e[a[i]-2][a[i-1]-1],f[0][i-1]+e[a[i]-2][a[i-1]-2])),
        f[1][i]=min(f[2][i-1]+e[a[i]-1][a[i-1]],min(f[1][i-1]+e[a[i]-1][a[i-1]-1],f[0][i-1]+e[a[i]-1][a[i-1]-2])),
        f[2][i]=min(f[2][i-1]+e[a[i]][a[i-1]],min(f[1][i-1]+e[a[i]][a[i-1]-1],f[0][i-1]+e[a[i]][a[i-1]-2]));
    ans=min(min(f[0][n*n],f[1][n*n]),f[2][n*n]);
    print(ans/1000);put(' ');print(ans%1000);
    genshin:;flush();return 0;
}
```

---

## 作者：RainFestival (赞：0)

$\tt{codeforces}$ 评分 $2200$。

设 $dp_{{s},{x},{y},{k}}=$ 现在使用的是第 $s$ 种棋子，现在在 $(x,y)$ 位置已经走过 $k$ 个数的代价。

要求在时间最短的情况下要求换棋子种类数尽量少。

换棋子次数不可能超过 $1000$。所以可以将移动一步的代价设为 $1000$，换一次棋子的代价设为 $1001$。

我们发现不好转移，所以就用最短路进行转移即可。

代码：

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<cstdlib>
std::vector<int> a[30005],b[30005];
std::priority_queue< std::pair<int,int> > pq;
int dis[30005],vis[30005],n,m,ans,f[15][15],s,t;
void add(int x,int y,int v){a[x].push_back(y);b[x].push_back(v);}
int po(int x,int y,int k,int p){return ((k-1)*n*n+(y-1)*n+x-1)*3+p;}
int dijkstra(int s,int t)
{
	for (int i=1;i<=n*n*n*n*3+2;i++) dis[i]=1000000000,vis[i]=0;
	dis[s]=0;pq.push(std::make_pair(-dis[s],s));
	while (!pq.empty())
	{
		int v=pq.top().second;pq.pop();
		if (vis[v]) continue;
		else vis[v]=1;
		for (int i=0;i<a[v].size();i++)
		{
			int u=a[v][i],w=b[v][i];
			if (dis[v]+w<dis[u])
			    dis[u]=dis[v]+w,pq.push(std::make_pair(-dis[u],u));
		}
	}
	return dis[t];
} 
void add_edge()
{
	int sx,sy,ex,ey;
	s=n*n*n*n*3+1,t=n*n*n*n*3+2;
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
	        for (int k=1;k<=n*n;k++)
	        {
	        	add(po(i,j,k,1),po(i,j,k,2),1001);
	        	add(po(i,j,k,1),po(i,j,k,3),1001);
    	    	add(po(i,j,k,2),po(i,j,k,1),1001);
	        	add(po(i,j,k,2),po(i,j,k,3),1001);
	        	add(po(i,j,k,3),po(i,j,k,1),1001);
	    	    add(po(i,j,k,3),po(i,j,k,2),1001);
	    	    if (f[i][j]==k&&k!=1)
	    	    {
	    	    	add(po(i,j,k-1,1),po(i,j,k,1),0);
	        	    add(po(i,j,k-1,2),po(i,j,k,2),0);
	    	        add(po(i,j,k-1,3),po(i,j,k,3),0);
				}
				if (f[i][j]==1) sx=i,sy=j;
				if (f[i][j]==n*n) ex=i,ey=j;
				//1
	    	    for (int p=1;p<=n;p++) if (p!=i) add(po(i,j,k,1),po(p,j,k,1),1000);
	    	    for (int p=1;p<=n;p++) if (p!=j) add(po(i,j,k,1),po(i,p,k,1),1000);
	    	    //2
	    	    if (i+1<=n&&i+1>=1&&j+2<=n&&j+2>=1) add(po(i,j,k,2),po(i+1,j+2,k,2),1000);
	    	    if (i-1<=n&&i-1>=1&&j+2<=n&&j+2>=1) add(po(i,j,k,2),po(i-1,j+2,k,2),1000);
	    	    if (i+1<=n&&i+1>=1&&j-2<=n&&j-2>=1) add(po(i,j,k,2),po(i+1,j-2,k,2),1000);
	    	    if (i-1<=n&&i-1>=1&&j-2<=n&&j-2>=1) add(po(i,j,k,2),po(i-1,j-2,k,2),1000);
	    	    if (i+2<=n&&i+2>=1&&j+1<=n&&j+1>=1) add(po(i,j,k,2),po(i+2,j+1,k,2),1000);
	    	    if (i-2<=n&&i-2>=1&&j+1<=n&&j+1>=1) add(po(i,j,k,2),po(i-2,j+1,k,2),1000);
	    	    if (i+2<=n&&i+2>=1&&j-1<=n&&j-1>=1) add(po(i,j,k,2),po(i+2,j-1,k,2),1000);
	    	    if (i-2<=n&&i-2>=1&&j-1<=n&&j-1>=1) add(po(i,j,k,2),po(i-2,j-1,k,2),1000);
	    	    //3
	    	    int x,y;
				x=i,y=j;
	    	    for (;;)
	    	    {
	    	    	x--,y--;
	    	    	if (x<=n&&x>=1&&y<=n&&y>=1) add(po(i,j,k,3),po(x,y,k,3),1000);
	    	    	else break;
				}
				x=i,y=j;
				for (;;)
	    	    {
	    	    	x++,y--;
	    	    	if (x<=n&&x>=1&&y<=n&&y>=1) add(po(i,j,k,3),po(x,y,k,3),1000);
	    	    	else break;
				}
				x=i,y=j;
				for (;;)
	    	    {
	    	    	x--,y++;
	    	    	if (x<=n&&x>=1&&y<=n&&y>=1) add(po(i,j,k,3),po(x,y,k,3),1000);
	    	    	else break;
				}
				x=i,y=j;
				for (;;)
	    	    {
	    	    	x++,y++;
	    	    	if (x<=n&&x>=1&&y<=n&&y>=1) add(po(i,j,k,3),po(x,y,k,3),1000);
	    	    	else break;
				}
		    }
	add(s,po(sx,sy,1,1),0);
	add(s,po(sx,sy,1,2),0);
	add(s,po(sx,sy,1,3),0);
	add(po(ex,ey,n*n,1),t,0);
	add(po(ex,ey,n*n,2),t,0);
	add(po(ex,ey,n*n,3),t,0);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
	        scanf("%d",&f[i][j]);
	add_edge();
	ans=dijkstra(s,t);
	printf("%d %d\n",ans/1000,ans%1000);
	return 0;
}
```

$98$ 个测试点，时间 $\tt{2.29s}$，内存 $\tt{6.48MB}$，代码长度 $\tt{3.36KB}$。

---

