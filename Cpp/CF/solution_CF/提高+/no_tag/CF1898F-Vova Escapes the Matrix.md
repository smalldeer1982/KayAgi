# Vova Escapes the Matrix

## 题目描述

Following a world tour, Vova got himself trapped inside an $ n \times m $ matrix. Rows of this matrix are numbered by integers from $ 1 $ to $ n $ from top to bottom, and the columns are numbered by integers from $ 1 $ to $ m $ from left to right. The cell $ (i, j) $ is the cell on the intersection of row $ i $ and column $ j $ for $ 1 \leq i \leq n $ and $ 1 \leq j \leq m $ .

Some cells of this matrix are blocked by obstacles, while all other cells are empty. Vova occupies one of the empty cells. It is guaranteed that cells $ (1, 1) $ , $ (1, m) $ , $ (n, 1) $ , $ (n, m) $ (that is, corners of the matrix) are blocked.

Vova can move from one empty cell to another empty cell if they share a side. Vova can escape the matrix from any empty cell on the boundary of the matrix; these cells are called exits.

Vova defines the type of the matrix based on the number of exits he can use to escape the matrix:

- The $ 1 $ -st type: matrices with no exits he can use to escape.
- The $ 2 $ -nd type: matrices with exactly one exit he can use to escape.
- The $ 3 $ -rd type: matrices with multiple (two or more) exits he can use to escape.

Before Vova starts moving, Misha can create more obstacles to block more cells. However, he cannot change the type of the matrix. What is the maximum number of cells Misha can block, so that the type of the matrix remains the same? Misha cannot block the cell Vova is currently standing on.

## 说明/提示

In the first test case, the matrix is of the $ 3 $ -rd type. Misha can create obstacles in all empty cells except the cells $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ . There are $ 9 $ such cells, and adding such obstacles does not change the type of the matrix.

In the second test case, the matrix is of the $ 3 $ -rd type. Blocking any cell changes the matrix type to the $ 2 $ -nd: one of the two exits will become unavailable for Vova. Thus, the answer is $ 0 $ .

In the third test case, the matrix is of the $ 1 $ -st type. No free cell exists (besides Vova's), so Misha cannot block any cell.

In the fourth test case, the matrix is of the $ 2 $ -nd type. Misha can create $ 3 $ obstacles in cells $ (5, 2) $ , $ (6, 3) $ , $ (6, 4) $ without changing the type of the matrix.

In the fifth test case, the matrix is of the $ 3 $ -rd type. Misha can create $ 4 $ obstacles in cells $ (2, 2) $ , $ (3, 2) $ , $ (4, 2) $ , $ (5, 2) $ or $ 4 $ obstacles in cells $ (2, 4) $ , $ (3, 4) $ , $ (4, 4) $ , $ (5, 4) $ without changing the type of the matrix.

## 样例 #1

### 输入

```
8
4 4
#..#
..V.
....
#..#
3 6
#.####
#....#
####V#
3 3
###
#V#
###
6 5
#.###
#...#
###.#
#V..#
#.###
##..#
7 5
#####
#.V.#
#.#.#
#.#.#
#.#.#
#...#
#.#.#
3 7
#.....#
.#####.
#...V.#
5 8
####.###
#..V#..#
#...#..#
#...##.#
###.####
5 5
#...#
##.##
##V##
##.##
#...#```

### 输出

```
9
0
0
3
4
10
12
5```

# 题解

## 作者：huangrenheluogu (赞：4)

我的翻译：

$n\times m$ 的矩阵，有一些点有障碍物。保证边角是有障碍物的。

定义在边缘的点为出口。

定义一个点有三种类型：

- `1 型点`：恰好可以到 $0$ 个出口。

- `2 型点`：恰好可以到 $1$ 个出口。

- `3 型点`：可以到 $2$ 个或 $2$ 个以上的出口。

Vova 在一个点，Misha 可以将一些空点变成有障碍物的点（Vova 所在的点除外），但是 Misha 不能改变 Vova 所在点的类型。

求 Misha 可以增加障碍物数量的最大值。

$t\le10^4,1\le n,m\le1000,\sum n\times m\le10^6$。

------------------------------

先跑图，知道 Vova 所在的点是哪种类型的点。

分类讨论：

- `1 型点`

那么直接输出 $tot-1$，$tot$ 为总共空的点。

- `2 型点`

输出 $tot-minn$，其中 $minn$ 是中心点到周围至少经过的点。

- `3 型点`

考虑保留两条路径，我们可以在第一次跑图的过程中得出第 $(x,y)$ 这个点距离不同的出口最短距离、次短距离。

然后从 Vova 所在的点出发，到一个点就判断，总路程就是 $(x,y)$ 到出口的最小距离加次小距离，和 Vova 所在点到 $(x,y)$ 的距离。

注意处理一下点数和边数的差距即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005, inf = 1e9;
int n, m, dis[N][N][2], T, cnt, tot, X, Y, t, h, x, y, nx, ny, dist, Dis[N][N], a[N][N], xx, yy;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
char c;
struct nod{
    int x, y, frox, froy, dis;//frox, froy 记录点的来源
}q[N * N * 2], id[N][N];
inline bool check(int x, int y){
    return x < 1 || x > n || y < 1 || y > m || a[x][y];
}
inline void work(){
    scanf("%d%d", &n, &m);
    h = t = tot = cnt = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            c = getchar();
            while(c != '#' && c != '.' && c != 'V') c = getchar();
            if(c == '#') a[i][j] = 1;
            else a[i][j] = 0;
            if(c == 'V') X = i, Y = j;
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            dis[i][j][0] = dis[i][j][1] = inf, id[i][j] = (nod){-1, -1, 0, 0};
            if(a[i][j] == 0){
                tot++;
                if(i == 1 || j == 1 || i == n || j == m) q[++t] = (nod){i, j, i, j, 0}, dis[i][j][0] = 0, id[i][j] = (nod){i, j, 0, 0, 0};//第一遍，我用边数记录
            }
        }
    }
    while(h < t){
        h++;
        x = q[h].x, y = q[h].y, dist;
        xx = q[h].frox, yy = q[h].froy;
        dist = q[h].dis;
        for(int i = 0; i < 4; i++){
            nx = x + dx[i];
            ny = y + dy[i];
            if(check(nx, ny)) continue ;
            if(dis[nx][ny][0] > dist + 1){
                dis[nx][ny][0] = dist + 1;
                id[nx][ny] = (nod){xx, yy};
                q[++t] = (nod){nx, ny, xx, yy, dist + 1};
            }
            else{
                if(dis[nx][ny][1] > dist + 1 && (xx != id[nx][ny].x || yy != id[nx][ny].y)){
                    dis[nx][ny][1] = dist + 1;
                    id[nx][ny] = (nod){xx, yy, 0, 0, 0};
                    q[++t] = (nod){nx, ny, xx, yy, dist + 1};
                }
            }
        }
    }
    if(dis[X][Y][0] == inf){//1型点
        printf("%d\n", tot - 1);
        return ;
    }
    if(dis[X][Y][1] == inf){//2型点
        printf("%d\n", tot - dis[X][Y][0] - 1);
        return ;
    }
    h = t = 0;
    q[++t] = (nod){X, Y};
    cnt = tot;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            Dis[i][j] = inf;
        }
    }
    Dis[X][Y] = 1;//第二遍，我用经过的点数记录，这样加起来刚好
    while(h < t){
        h++;
        x = q[h].x, y = q[h].y;
        dist = Dis[x][y];
        cnt = min(cnt, dist + dis[x][y][0] + dis[x][y][1]);
        for(int i = 0; i < 4; i++){
            nx = x + dx[i];
            ny = y + dy[i];
            if(check(nx, ny)) continue ;
            if(Dis[nx][ny] > dist + 1){
                Dis[nx][ny] = dist + 1;
                q[++t] = (nod){nx, ny, 0, 0, dist + 1};
            }
        }
    }
    printf("%d\n", tot - cnt);
    return ;
}
int main(){
    scanf("%d", &T);
    while(T--){
        work();
    }
    return 0;
}
```

洛谷上 UKE 了， 放一张 CF 的评测图吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ebi2lxt.png)

upd：洛谷上过了。

---

## 作者：EuphoricStar (赞：1)

Type $1$ 是简单的。直接输出空格个数即可。

Type $2$ 也是简单的。显然要堵住不在起点和出口最短路上的格子，答案为空格个数减去起点到任一出口的最短路。

考虑 Type $3$。容易发现答案为空格个数减去起点到任两个出口的最短路（公共部分只算一次）。考虑从起点开始出发，一定最多存在一个格子，使得从起点走到它后，两条路径分道扬镳，不再相交。那我们可以枚举这个格子，求出它到最近的两个**不同**出口的距离（就是最小和次小）。可以简单 bfs 求出。

总时间复杂度 $O(nm)$。

---

## 作者：王熙文 (赞：1)

不会“简单 bfs”，所以写一篇题解记录一下这个做法。

## 思路

如果 Vova 所在的点（下文称起点）可以到达 $0$ 个出口，则所有没有障碍物的点都可以放上障碍物。

如果起点可以到达 $1$ 个出口，可以将问题转化为保留一条到达出口的道路，因此从起点出发跑一遍最短路，并对每个出口的距离取最小值即可。

如果起点可以到达 $2$ 个出口，问题转化为求两条到达出口的路径的并最小。发现两条路径的形态一定是重合一段，然后永远不重合。因为如果再重合了那么中间的两条路径可以变成一条路径。

因此枚举重合到了哪个点。问题转化为了在一张边权为 $1$ 的无向图上有若干个起点，要对每个点求每个起点到这里距离中的最短和次短。这个问题被别的题解称为“简单 bfs”，但是我觉得也没有这么简单吧，所以讲一下。

首先考虑一种松弛算法，类似 Bellman-Ford。循环 $m$ 轮，每次对于一条边 $(u,v)$ 互相更新一遍。具体地，对于 $u \to v$，首先用 $u$ 的最短路更新 $v$ 的最短路，然后根据起点是否相同看 $u$ 的最短路、次短路是否能更新 $v$ 的次短路。

为什么上述算法可以只记录最短路和次短路呢？因为最短路和次短路至少有一个可以使起点不同，这样更长的路就没有意义了。

接着考虑 BFS/Dijkstra 算法的正确性。它们的本质是每次取出距离最小的，它不会被更新。但是现在这个问题每个点有两个值，所以无法保证它的某个值以后不会被更新。

但是我们可以将每个点的两个值单独考虑。如果最短路更新了就将最短路放到队列中，次短路更新了就将次短路放到队列中。每次从队列中取出来的也不是一个点，而是一个点的某个值。这样就可以保证算法的正确性了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int n,m;
string s[1010];
int dis1[1010][1010];
queue<pair<int,int>> q;
int dis2[1010][1010][2]; pair<int,int> id[1010][1010];
struct Queue { int x,y,fx,fy,dis; }; queue<Queue> qq;
int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int t; cin>>t; while(t--)
	{
		cin>>n>>m;
		int sx,sy;
		int cnt=0;
		for(int i=1; i<=n; ++i)
		{
			cin>>s[i],s[i]=' '+s[i];
			for(int j=1; j<=m; ++j)
			{
				if(s[i][j]=='V') sx=i,sy=j;
				else if(s[i][j]=='.') ++cnt;
			}
		}
		for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j) dis1[i][j]=1e9;
		while(!q.empty()) q.pop();
		q.push({sx,sy}),dis1[sx][sy]=0;
		int ccnt=0,in;
		while(!q.empty())
		{
			int x=q.front().first,y=q.front().second; q.pop();
			if(x==1 || x==n || y==1 || y==m) ++ccnt,in=dis1[x][y];
			for(int i=0; i<4; ++i)
			{
				int tx=x+dx[i],ty=y+dy[i];
				if(1<=tx && tx<=n && 1<=ty && ty<=m && s[tx][ty]!='#' && dis1[tx][ty]==1e9) q.push({tx,ty}),dis1[tx][ty]=dis1[x][y]+1;
			}
		}
		if(ccnt==0) cout<<cnt<<'\n';
		else if(ccnt==1) cout<<cnt-in<<'\n';
		else
		{
			while(!qq.empty()) qq.pop();
			for(int i=1; i<=n; ++i)
			{
				for(int j=1; j<=m; ++j)
				{
					if(s[i][j]=='#') continue;
					if(i==1 || i==n || j==1 || j==m) dis2[i][j][0]=0,dis2[i][j][1]=1e9,id[i][j]={i,j},qq.push({i,j,i,j,0});
					else dis2[i][j][0]=dis2[i][j][1]=1e9;
				}
			}
			while(!qq.empty())
			{
				int x=qq.front().x,y=qq.front().y,fx=qq.front().fx,fy=qq.front().fy,dis=qq.front().dis; qq.pop();
				for(int i=0; i<4; ++i)
				{
					int tx=x+dx[i],ty=y+dy[i];
					if(tx<1 || n<tx || ty<1 || m<ty || s[tx][ty]=='#') continue;
					if(dis2[tx][ty][0]==1e9) dis2[tx][ty][0]=dis+1,id[tx][ty]={fx,fy},qq.push({tx,ty,fx,fy,dis+1});
					else if(dis2[tx][ty][1]==1e9 && make_pair(fx,fy)!=id[tx][ty]) dis2[tx][ty][1]=dis+1,qq.push({tx,ty,fx,fy,dis+1});
				}
			}
			int ans=1e9;
			for(int i=1; i<=n; ++i)
			{
				for(int j=1; j<=m; ++j)
				{
					if(s[i][j]!='#' && dis1[i][j]!=1e9) ans=min(ans,dis1[i][j]+dis2[i][j][0]+dis2[i][j][1]);
				}
			}
			cout<<cnt-ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

E>D>C>F>B>A。

分三种情况。

$1$ 型。全部放障碍物即可。

$2$ 型。找到一条往终点的最短路，除了这条路上，都放障碍物即可。

$3$ 型。相当于是找到两条往不同终点的路，除了这两条路的并之外全部删掉。于是问题变为最小化路径并。

容易发现如果两条路径先分开再相交，这样非常蠢，因为我们只要求最后终点不同。于是可以枚举两条路径最后一个交点 $(x,y)$，求出 $(x,y)$ 到起点以及两个不同终点的最短路，求和并求出全部 $(x,y)$ 中的最小值 $+1$ 即为答案。

全部都可以 $O(n)$ bfs 解决。

code：

```cpp
int n,m,a[N][N],f[N][N][2],g[N][N][2],dis[N][N];
char s[N];
const int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
void bfs(int sx,int sy){
	queue<pii> q;
	rep(i,1,n){
		rep(j,1,m){
			dis[i][j]=inf;
		}
	}
	dis[sx][sy]=0;
	q.emplace(sx,sy);
	while(q.size()){
		auto [x,y]=q.front();
		q.pop();
		rep(i,0,3){
			int nx=x+dx[i],ny=y+dy[i];
			if(a[nx][ny]||dis[nx][ny]<=dis[x][y]+1){
				continue;
			}
			dis[nx][ny]=dis[x][y]+1;
			q.emplace(nx,ny);
		}
	}
}
void Bfs(){
	queue<tuple<int,int,int>> q;
	rep(i,1,n){
		rep(j,1,m){
			f[i][j][0]=f[i][j][1]=inf;
			g[i][j][0]=g[i][j][1]=0;
		}
	}
	rep(i,1,n){
		rep(j,1,m){
			if((i==1||i==n||j==1||j==m)&&!a[i][j]){
				q.emplace(i,j,0);
				f[i][j][0]=0;
				g[i][j][0]=(i-1)*m+j;
			}
		}
	}
	while(q.size()){
		auto [x,y,z]=q.front();
		q.pop();
		rep(i,0,3){
			int nx=x+dx[i],ny=y+dy[i];
			if(a[nx][ny]||f[nx][ny][1]<1e9){
				continue;
			}else if(f[nx][ny][0]<1e9){
				if(g[nx][ny][0]==g[x][y][z]){
					continue;
				}
				f[nx][ny][1]=f[x][y][z]+1;
				g[nx][ny][1]=g[x][y][z];
				q.emplace(nx,ny,1);
			}else{
				f[nx][ny][0]=f[x][y][z]+1;
				g[nx][ny][0]=g[x][y][z];
				q.emplace(nx,ny,0);
			}
		}
	}
}
void Yorushika(){
	read(n,m);
	int sx,sy;
	rep(i,1,n){
		scanf("%s",s+1);
		rep(j,1,m){
			if(s[j]=='V'){
				sx=i,sy=j;
			}
			a[i][j]=s[j]=='#';
		}
	}
	bfs(sx,sy);
	int cnt=0,mn=inf;
	rep(i,1,n){
		rep(j,1,m){
			if(i==1||i==n||j==1||j==m){
				cnt+=dis[i][j]<1e9;
				mn=min(mn,dis[i][j]);
			}
		}
	}
	int ans=0;
	rep(i,1,n){
		rep(j,1,m){
			ans+=!a[i][j];
		}
	}
	if(!cnt){
		printf("%d\n",ans-1);
		return;
	}
	if(cnt==1){
		printf("%d\n",ans-mn-1);
		return;
	}
	Bfs();
	int res=inf;
	rep(i,1,n){
		rep(j,1,m){
			if(!a[i][j]&&f[i][j][0]<1e9&&f[i][j][1]<1e9&&dis[i][j]<1e9){
				res=min(res,f[i][j][0]+f[i][j][1]+dis[i][j]+1);
			}
		}
	}
	printf("%d\n",ans-res);
}
signed main(){
	int t=1;
	read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Msents (赞：0)

## 题意：
给你一个矩阵和起始点，有些位置不能走，定义能被到达的边界为出口。

现在将矩阵分为三种类型：
- 没有出口的。
- 有一个出口的。
- 有多个出口的。

你可以填充一些位置，使其不能走，但不能改变矩阵类型，求最多能填充多少个位置。

## 思路：
对于没有出口的矩阵，答案就是能走的位置之和。

对于有一个出口的矩阵，答案是能走的位置减去起点到出口的最短路的长度。

对于有多个出口的矩阵，可以由上面推广过来，减去两个最近出口的最短路的长度。

但若两个出口的最短路有重叠，答案就会多算。

可以求出每个位置到起点的最短路和最近的两个出口，答案就是空格减去两个出口的距离再减去到起点的距离的最大值，这样就能去掉重叠距离。

---

