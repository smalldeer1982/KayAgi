# Super Jaber

## 题目描述

$ Jaber $ 是一个大国家的超级英雄，该国可以描述为一个具有 $ n $ 行和 $ m $ 列的网格，其中网格中的每个单元格都包含一个不同的城市。

$ Jaber $ 给该国的每个城市都指定了$ 1 $ 到 $ k $ 的特定颜色。 一秒钟之内，他可以从当前城市转到相邻（左右相邻或上下相邻，即四连通）的任何城市，或者到与当前城市颜色相同颜色的任何城市。

$ Jaber $ 必须执行 $ q $ 个任务。 在每个任务中，他都会在 $ r_1 $行和 $ c_1 $ 列所在的城市中，他应该在 $ r_2 $ 行和 $ c_2 $ 列中帮助该城市中的某个人。

$ Jaber $ 需要你的帮助，告诉他每次任务从出发城市到终点城市的最短时间。

## 说明/提示

在第一个样例中：
- 任务$ 1 $：$ Jaber $ 应该从单元格$（1,1）$到单元格$（3,3）$，因为它们具有相同的颜色，然后从单元格$（3,3）$到单元格$ （3,4）$，因为它们并排相邻（总共移动了两个）；
- 任务$ 2 $：Jaber已经在终点位置。

在第二个样例中：
- 任务 $ 1 $ : $ (1,1) $ $ \rightarrow $ $ (1,2) $ $ \rightarrow $ $ (2,2) $ ;
- 任务 $ 2 $ : $ (1,1) $ $ \rightarrow $ $ (3,2) $ $ \rightarrow $ $ (3,3) $ $ \rightarrow $ $ (3,4) $ ;
- 任务 $ 3 $ : $ (1,1) $ $ \rightarrow $ $ (3,2) $ $ \rightarrow $ $ (3,3) $ $ \rightarrow $ $ (2,4) $ ;
- 任务 $ 4 $ : $ (1,1) $ $ \rightarrow $ $ (1,2) $ $ \rightarrow $ $ (1,3) $ $ \rightarrow $ $ (1,4) $ $ \rightarrow $ $ (4,4) $ .

## 样例 #1

### 输入

```
3 4 5
1 2 1 3
4 4 5 5
1 2 1 3
2
1 1 3 4
2 2 2 2```

### 输出

```
2
0```

## 样例 #2

### 输入

```
4 4 8
1 2 2 8
1 3 4 7
5 1 7 6
2 3 8 8
4
1 1 2 2
1 1 3 4
1 1 2 4
1 1 4 4```

### 输出

```
2
3
3
4```

# 题解

## 作者：万弘 (赞：14)

从$(x1,y1)$到$(x2,y2)$只有两种方法：直接走过去，或**至少使用一次传送。**  

先预处理$dis(k,x,y)$表示从$(x,y)$走到任何颜色为$k$的格子的最小代价（注意，可以使用传送，可见样例2），显然这等价于从颜色为$k$的格子开始走到$(x,y)$的最小代价。将所有颜色为$k$的点入队，进行多源bfs即可。  
注意，bfs时转移的形式有两种：1.走相邻的格子；2.传送到颜色相同的格子（注意到一种颜色只需要处理一次，这样才能保证每次bfs的时间复杂度为$\mathcal O(nm)$，可见代码）。

处理询问：首先答案不可能大于两点间曼哈顿距离，即直接走的代价。然后枚举中转颜色$k$,则
$$ans=\min_{k=1}^{col}dis(k,x1,y1)+dis(k,x2,y2)+1$$

显然单次询问时间复杂度为$\mathcal O(k),$总时间复杂度$\mathcal O(nmk+Qk)$
```cpp
/**********/
#define MAXN 1011
#define MAXK 41
std::vector<pll>g[MAXK];//颜色为k的点集
ll a[MAXN][MAXN],dis[MAXK][MAXN][MAXN];//颜色和距离
ll n,m,col;
bool viscol[MAXK];//颜色是否已处理过
std::queue<pll>q;//bfs的队列
const ll mx[4]={1,0,-1,0},my[4]={0,1,0,-1};//移动
void bfs(ll k)//bfs求dis[k][x][y]
{
	memset(viscol,0,sizeof viscol);
	for(ll i=0;i<g[k].size();++i)
	{
		ll x=g[k][i].first,y=g[k][i].second;
		dis[k][x][y]=0;
		q.push(pll(x,y));//颜色为k的所有点入队
	}
	viscol[k]=1;
	while(!q.empty())
	{
		ll x=q.front().first,y=q.front().second;q.pop();
		ll c=a[x][y],cur=dis[k][x][y];
		if(!viscol[c])//颜色c未被处理则处理
		{
			viscol[c]=1;
			for(ll i=0;i<g[c].size();++i)
			{
				ll vx=g[c][i].first,vy=g[c][i].second;
				if(dis[k][vx][vy]<0)//初始化为-1，所以<0表示之前未到达过
				{
					dis[k][vx][vy]=cur+1;//传送
					q.push(pll(vx,vy));
				}
			}
		}
		for(ll i=0;i<4;++i)
		{
			ll vx=x+mx[i],vy=y+my[i];//直接走
			if(vx>0&&vx<=n&&vy>0&&vy<=m&&dis[k][vx][vy]<0)
			{
				dis[k][vx][vy]=cur+1;
				q.push(pll(vx,vy));
			}
		}
	}
}
int main()
{
	memset(dis,-1,sizeof dis);
	n=read(),m=read(),col=read();
	for(ll i=1;i<=n;++i)
		for(ll j=1;j<=m;++j)
		{
			ll x=read();
			a[i][j]=x;
			g[x].push_back(pll(i,j));
		}
	for(ll i=1;i<=col;++i)
	{
		bfs(i);
		/*
		printf("col %d:\n",i);
		for(ll x=1;x<=n;++x)
		{
			for(ll y=1;y<=m;++y)
				printf("%d ",dis[i][x][y]);
			putchar('\n');
		}
		*/
	}
	ll task=read();
	while(task--)
	{
		ll x1=read(),y1=read(),x2=read(),y2=read();
		ll ans=abs(x1-x2)+abs(y1-y2);
		for(ll i=1;i<=col;++i)
			umin(ans,dis[i][x1][y1]+dis[i][x2][y2]+1);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：jianhe (赞：4)

切了个 *2600 /cy。

与 [CF590C](https://www.luogu.com.cn/problem/CF590C) 类似，注意到颜色数很少。因此想到可以每次枚举传送的颜色，与曼哈顿距离取最小值来计算答案。

考虑如何预处理。枚举每一种颜色，之后类似于 [CF1920F1](https://www.luogu.com.cn/problem/CF1920F1)，用广度优先搜索来预处理。需要注意的是，处理传送时只需第一次遇到这种颜色时入队，否则跳过来优化时间复杂度。

注意：不要全开 `long long`！

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define pb push_back
#define pii pair<ll,ll> 
#define fi first
#define se second
const ll N=1e3+10,K=44;
ll n,m,k,q,r1,c1,r2,c2,px,py,ans,a[N][N],dis[K][N][N];
ll dx[]={-1,0,0,1};
ll dy[]={0,-1,1,0};
bool vis[K];
vector<pii> c[K];
bool check(ll x,ll y){return 1<=x&&x<=n&&1<=y&&y<=m;}
void bfs(ll col){
	queue<pii> q;memset(vis,0,sizeof vis);
	for(auto xx:c[col]) q.push({px=xx.fi,py=xx.se}),dis[col][px][py]=0;
	while(!q.empty()){
		auto p=q.front();q.pop();
		ll x=p.fi,y=p.se,s=dis[col][x][y];
		for(int k=0;k<4;k++)
			if(check(px=x+dx[k],py=y+dy[k])&&dis[col][px][py]>s+1) q.push({px,py}),dis[col][px][py]=s+1;
		if(!vis[a[x][y]]){
			vis[a[x][y]]=1;
			for(auto xx:c[a[x][y]])
				if(dis[col][px=xx.fi][py=xx.se]>s+1) q.push({px,py}),dis[col][px][py]=s+1;
		}		
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>a[i][j],c[a[i][j]].pb({i,j});
	for(int i=1;i<=k;i++) bfs(i);
	cin>>q;
	while(q--){
		cin>>r1>>c1>>r2>>c2;
		ans=abs(r1-r2)+abs(c1-c2);
		for(int i=1;i<=k;i++) ans=min(ans,dis[i][r1][c1]+dis[i][r2][c2]+1);
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：peterwuyihong (赞：3)

单词询问的话明显直接做最短路。

但是有多次询问，发现 k 很小后考虑使用传统艺能预处理。

使用一个 $f(k,x,y)$ ，表示从 $(x,y)$ 走到 k 颜色的最短步数，因为边是双向的，所以 $f(k,x,y)$ 也表示从 k 颜色走到 $(x,y)$ 的最短步数。

其中我们瞬移算 $0$ 步，最后加上 $1$ 就行了，这样可以忽略在 $k$ 颜色上反复横跳的锅，最后再将答案与曼哈顿距离取 $\min$ 即可。

对于询问枚举 k 即可。

于是你就整出来一个 $O(nmk+Qk)$ 的做法

现在是 $13:45$，看我什么时候写完

现在是 $14:37$，我写完了

```cpp
#define maxn 1010
int n,m,k;
int a[maxn][maxn];
int f[45][maxn][maxn];
struct pos{
	int x,y;
	pos(int xx=0,int yy=0):x(xx),y(yy){}
}q[maxn*maxn];
int l,r;
vector<pos>g[45];
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
bool col[45];
void bfs(int k){
	memset(col,0,sizeof col);
	l=r=0;
	for(pos o:g[k])q[++r]=o,f[k][o.x][o.y]=0;
	col[k]=1;
	while(l<=r){
		pos x=q[l++];
		if(!col[a[x.x][x.y]]){
			col[a[x.x][x.y]]=1;
			for(pos o:g[a[x.x][x.y]])
				if(f[k][o.x][o.y]>f[k][x.x][x.y]+1){
					f[k][o.x][o.y]=f[k][x.x][x.y]+1;
					q[++r]=o;
				}
		}
		for(int i=0;i<4;i++){
			int xx=x.x+dx[i],yy=x.y+dy[i];
			if(xx<1||yy<1||xx>n||yy>m)continue;
			if(f[k][xx][yy]>f[k][x.x][x.y]+1){
				f[k][xx][yy]=f[k][x.x][x.y]+1;
				q[++r]=pos(xx,yy);
			}
		}
	}
}
int T,x1,x2,y1,y2;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>m>>k;
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			g[a[i][j]].push_back(pos(i,j));
		}
	for(int i=1;i<=k;i++)bfs(i);
	for(cin>>T;T;T--){
		cin>>x1>>y1>>x2>>y2;
		int ans=abs(x1-x2)+abs(y1-y2);
		for(int i=1;i<=k;i++)ans=min(ans,f[i][x1][y1]+f[i][x2][y2]+1);
		cout<<ans<<endl;
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
被卡了一会儿空间才发现我的超快读竟然在CF里是占空间的！

---

## 作者：program_xwl (赞：2)

# 思路：
看到题目的第一反应就是每次询问跑一遍广搜，输出答案，但如果是这样，时间复杂度就是 $O(qnm)$，带入极限数据就是 $(10^3)^2\times 10^5=10^{11}$，爆的很彻底。

虽然这些询问很多，但都用的是同一张地图，考虑预处理。

求答案的过程中我们需要考虑很多种情况，我们可以分开讨论。
## 前往目标城市的两种情况：
### 直接腿过去：
虽然这题每个点都是一个传送门，但还是要考虑一下直接腿过去的情况，因为地图中没有障碍，所以腿过去的步数就是起点到终点的曼哈顿距离。
### 通过城市分配颜色传送：
本题的难点就在这里，我们知道怎么预处理，但不知道怎么使用预处理，因为起点和终点每次询问都不同。
在这种情况中，我们必定要传送至少一次，不然就是情况 $1$ 了。所以**我们必定需要进入一个传送体系**（分配颜色相同的城市）。那么在想想为什么这题难，是因为起点和终点每次都不同，但如果我们将我们一个到达终点必定经过的传送体系看做一个中转站，在加上地图不会变化，**说明我们的中转站会在之后的询问中一直保持不变，这也意味着，每个点到达这个中转站的最少步数也是不变的**，既然两个关于中转站的关键信息都可以不变，关于对中转站预处理不是简单了吗？那么，该怎么选择中转站呢？其实非常简单粗暴，再看看题目，$k$ 也就是地图中传送体系的数量，是小于等于 $40$ 的，每次询问时暴力枚举一遍都不会超时。

设 $dis_{c,i,j}$ 表示从 $(i,j)$ 点到达最近的颜色分配为 $c$ 的城市的最少步数，$stx、sty、edx、edy$ 分别代表起点的 $x,y$ 坐标，终点的 $x,y$ 坐标。

很容易看出答案为：

$$
\min(| stx-edx|+| sty-edy |,\min_{i=1}^{i=k}(dis_{i,stx,sty}+dis_{i,edx,edy}+1))
$$

那么，具体该怎么预处理呢？

这需要用到多源 BFS。别看它名字高级，实际上只与普通 BFS 有~~亿~~一点差别。具体可以看我的代码，它的思路和代码都不难。
# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {int x,y;};
struct pos {int x,y;};
int n,m,k,a[1005][1005],T,dis[45][1005][1005];
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};
bool isusethe_color[45],vis[1005][1005];
queue<node>q;
vector<pos> door[45];

void bfs(int color)
{
	while(q.size()) q.pop();
	isusethe_color[color] = 1;
	for(int i = 0;i < door[color].size();i++)
	{
		q.push({door[color][i].x,door[color][i].y});
		dis[color][door[color][i].x][door[color][i].y] = 0;
		vis[door[color][i].x][door[color][i].y] = 1;
	}
	while(q.size())
	{
		node u = q.front();
		q.pop();
		for(int i = 0;i < 4;i++)
		{
			int nx = u.x+dx[i],ny = u.y+dy[i];
			if(nx < 1 || ny < 1 || nx > n || ny > m || vis[nx][ny]) continue;
			if(dis[color][nx][ny] > dis[color][u.x][u.y]+1)
			{
				dis[color][nx][ny] = dis[color][u.x][u.y]+1;
				q.push({nx,ny});
			}
		}
		if(isusethe_color[a[u.x][u.y]] == 0)
		{
			isusethe_color[a[u.x][u.y]] = 1;
			for(int i = 0;i < door[a[u.x][u.y]].size();i++)
			{
				int nx = door[a[u.x][u.y]][i].x,ny = door[a[u.x][u.y]][i].y;
				if(vis[nx][ny] == 0 && dis[color][nx][ny] > dis[color][u.x][u.y]+1)
				{
					q.push({nx,ny});
					dis[color][nx][ny] = dis[color][u.x][u.y]+1;
					vis[nx][ny] = 1;
				}
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			cin >> a[i][j];
			door[a[i][j]].push_back({i,j});
		}
	}
	for(int c = 1;c <= k;c++) for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++) dis[c][i][j] = 1e9;
	for(int i = 1;i <= k;i++)
	{
		for(int j = 1;j <= k;j++) isusethe_color[j] = 0;
		for(int j = 1;j <= n;j++) for(int c = 1;c <= m;c++) vis[j][c] = 0;
		bfs(i);
	}
	cin >> T;
	while(T--)
	{
		int stx,sty,edx,edy,mini;
		cin >> stx >> sty >> edx >> edy;
		mini = abs(stx-edx)+abs(sty-edy);
		for(int i = 1;i <= k;i++) mini = min(mini,dis[i][stx][sty]+dis[i][edx][edy]+1);
		cout << mini << '\n';
	}
	return 0;
}
```

---

## 作者：sccc_ (赞：1)

## 思路  
考虑 BFS。  

因为多次询问的原因，考虑先预处理。  

接着我们需考虑两种情况：
1. 不使用传送门。  
  因为题目给出的矩阵中无障碍，所以不使用传送门的最短距离就是曼哈顿距离。

2. 使用传送门。  
   我们发现，其实从传送门 A -> 传送门 B -> 传送门 C 其实就等于从传送门 A -> 传送门 C 的。所以相同颜色的传送门只会使用一次。  
  我们可以用 $dis_{k,i,j}$ 表示从 $(i,j)$ 至 $k$ 颜色传送门的最短距离。  
  那么这个最短距离就是：起点到颜色为 $k$ 的格子的最短距离 + 终点到这个颜色相同的格子的最短距离 $+$ $1$（因为从前一个颜色相同的要跳到下一个颜色相同的）。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

struct node 
{
	int x, y;
};

int n, m, q, k, a[1005][1005];
int dis[45][1005][1005];
bool vis[45];
vector<pair<int, int> > nbr[45];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

bool check (int x, int y, int op)
{
	return (x >= 1 and x <= n and y >= 1 and y <= m and dis[op][x][y] == -1);
}

void bfs (int op) 
{
	queue<node> q;
	memset (vis, 0, sizeof vis);
	vis[op] = 1;
	for (int i = 0; i < nbr[op].size(); i ++) 
	{
		int xx = nbr[op][i].first;
		int yy = nbr[op][i].second;
		dis[op][xx][yy] = 0;
		q.push({xx, yy});
	}
	while (!q.empty()) 
	{
		node u = q.front(); 
		q.pop();
		if (vis[a[u.x][u.y]] == 0) 
		{
			vis[a[u.x][u.y]] = 1;
			for (int i = 0; i < nbr[a[u.x][u.y]].size(); i ++) 
			{
				int xx = nbr[a[u.x][u.y]][i].first;
				int yy = nbr[a[u.x][u.y]][i].second;
				if (dis[op][xx][yy] == -1)
				{
					dis[op][xx][yy] = dis[op][u.x][u.y] + 1; 
					q.push({xx, yy}); 
				}
			} 
		}
		for (int i = 0; i < 4; i++) 
		{
			int xx = u.x + dx[i]; 
			int yy = u.y + dy[i]; 
			if (check (xx, yy, op))
			{
				dis[op][xx][yy] = dis[op][u.x][u.y] + 1; 
				q.push ({xx, yy});
			}
		} 
	}
}
int main() 
{
	cin >> n >> m >> k; 
	for (int i = 1; i <= n; i ++) 
	{
		for (int j = 1; j <= m; j ++) 
		{
			cin >> a[i][j];
			nbr[a[i][j]].push_back (make_pair(i, j));
		}
	}
	memset (dis, -1, sizeof dis);
	for (int i = 1; i <= k; i ++) 
		bfs (i);
	cin >> q;
	while (q --) 
	{
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int ans = abs(x1 - x2) + abs(y1 - y2);
		for (int i = 1; i <= k; i ++) 
			ans = min (ans, dis[i][x1][y1] + dis[i][x2][y2] + 1); 
		cout << ans << endl;
	} 
	return 0;
}
```

---

## 作者：Microperson (赞：1)

## Sol:
- 考虑这个人的行程是否传送了至少一次。
- 如果没有传送过，显然距离就是曼哈顿距离。
- 否则，我们就枚举他传送的颜色 c，答案等于任何一个包含元素 c 的格子到 $(x_1,y_1)$ 的最短路+任何一个包含元素 c 的格子到 $(x_2,y_2)$ 的最短路+1。
- 因此，对于每个元素，我们只需要预处理出包含这个元素的任何一个格子到每个坐标的最短路。
- 枚举元素的值，将包含这个元素的所有格子一起丢进队列里进行 bfs 即可。
- bfs 过程中可以转移和移动。

## code：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>

using namespace std;

int n,m,k,q,map[1010][1010],dis[45][1010][1010];
int dx[5]={0,1,0,-1,0};
int dy[5]={0,0,-1,0,1};
bool v[1000010],vv[1010][1010];

struct Node{
	int x,y;
};

void bfs(int x){
	queue<Node> q;
	memset(v,0,sizeof(v));
	memset(vv,0,sizeof(vv));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(map[i][j]==x){
				Node tmp;
				tmp.x=i;tmp.y=j;
				q.push(tmp); 
				vv[i][j]=1;
				dis[x][i][j]=0;
			}
		}
	}
	v[x]=1;
	while(q.size()){
		Node u = q.front();q.pop();
	//转移
		if(!v[map[u.x][u.y]]){
			v[map[u.x][u.y]]=1;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					if(map[i][j]==map[u.x][u.y]){
						Node t;
						t.x=i;t.y=j;
						if(vv[t.x][t.y]) continue;
						q.push(t);
						vv[t.x][t.y]=1;
						dis[x][t.x][t.y] = dis[x][u.x][u.y] + 1;
					}
				}
			}
		}
	//移动
		for(int i=1;i<=4;i++){
			Node t;
			t.x = u.x + dx[i];
			t.y = u.y + dy[i];
			if(t.x<1 || t.y<1 || t.x>n || t.y>m || vv[t.x][t.y]) continue;
			dis[x][t.x][t.y] = dis[x][u.x][u.y] + 1;
			vv[t.x][t.y]=1;
			q.push(t);
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&map[i][j]);
		}
	}
	for(int i=1;i<=k;i++) bfs(i);	
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int ans = abs(c - a) + abs(d - b);
		for(int j=1;j<=k;j++){
			ans = min(ans , dis[j][a][b] + dis[j][c][d] + 1);
		}
		printf("%d\n",ans);
	}
	return 0;
}

```




---

## 作者：Sai0511 (赞：1)

感觉有很多类似的题目。   
记 $dis(i,j,col)$ 表示从 $(i,j)$ 走到任意颜色为 $col$ 的格子的最小步数（可以使用顺移）。显然等价于从颜色为 $col$ 的格子走到 $(i,j)$ 的最小步数（可用瞬移）。   
所以可以进行多源 $bfs$，复杂度 $\mathcal{O}(nmk)$。    
那么对于 $(r1,c1)$ 走到 $(r2,c2)$ 的最小步数就是 $\text{min}(|r1-r2|+|c1-c2|,min\{ col_{i=1}^k dis(r1,c1,i)+1+dis(r2,c2,i) \})$   
第一部分是曼哈顿距离，表示直接走。  
剩下那部分中 $1$ 一定是要加的，表示同颜色中跳的那一下，如果距离最近的同色格子是同一个那么走的就是曼哈顿距离，一定会被另一个颜色所统计到，不用管。  
总复杂度 $\mathcal{O((nm+q)k)}$。   
这个垃圾题还卡空间。    
```cpp
#include <bits/stdc++.h>

using pii = std::pair<int, int>;  
const int N = 1010;
const int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};  

int n, m, i, j, k;
int col[N][N]; 
bool usecol[45];   
int dis[N * N][45];
std::vector<int> colE[45];  

inline int id(int x, int y) {
  return 1ll * (x - 1) * m + 1ll * y;    
}
inline pii unid(int x) {
  return std::make_pair((x - (x % m == 0 ? m : x % m)) / m + 1, x % m == 0 ? m : x % m);
}
inline void bfs(int c) {
  std::queue<int> q;  
  for (int pos : colE[c]) {
    dis[pos][c] = 0;       
    q.push(pos);      
  }   
  usecol[c] = 1;     
  while (!q.empty()) {
    int pos = q.front(); q.pop();    
    pii P = unid(pos);  
    int x = P.first, y = P.second, nowc = col[x][y];    
    if (!usecol[nowc]) {
      usecol[nowc] = 1;
      for (int nxt : colE[nowc]) {
        if (dis[pos][c] + 1 < dis[nxt][c]) {
          dis[nxt][c] = dis[pos][c] + 1;
          q.push(nxt);  
        }
      }
    }
    for (int i = 0; i < 4; i++) {
      int nxtx = x + dir[i][0], nxty = y + dir[i][1], nxt = id(nxtx, nxty);   
      if (nxtx < 1 || nxtx > n || nxty < 1 || nxty > m) {
        continue;
      }
      if (dis[pos][c] + 1 < dis[nxt][c]) {
        dis[nxt][c] = dis[pos][c] + 1;
        q.push(nxt);
      }
    }
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &col[i][j]);
      colE[col[i][j]].push_back(id(i, j));
    }
  }
  memset(dis, 0x3f, sizeof(dis));
  for (int i = 1; i <= k; i++) {
    memset(usecol, 0, sizeof(usecol));     
    bfs(i);
  }
  int q; scanf("%d", &q);
  while (q--) {
    int r1, c1, r2, c2;
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2); 
    int ans = std::abs(r1 - r2) + std::abs(c1 - c2), idS = id(r1, c1), idT = id(r2, c2);   
    for (int i = 1; i <= k; i++) {   
      ans = std::min(ans, dis[idS][i] + dis[idT][i] + 1);
    }
    printf("%d\n", ans);
  }
  return 0;  
}

```

---

## 作者：miracle0609 (赞：1)

## 题目大意：
给出一个 $ n $ * $ m $ 的网格，每个单元格都有一个颜色，颜色的种类不超过$ 40 $种，如果想从一个单元格到达另一个单元格，有两种方法：

- 消耗一个单位的时间从某种颜色移动到相同的颜色

- 消耗一个单位的时间走到相邻的格子中

- 现在给出 $ q $ 个任务，每次任务计算从起点到终点的最短时间

## 题目分析：

 $ q $ 的范围为 $ 1 - 10^{5} $ ，所以必须进行预处理：
 
$ Firstly $ 我们需要预处理出 $ dsu[color][x][y] $ 数组，代表的是从点 $ ( x , y  )$ 到 $ color $ 颜色的**最短路径**

$ Secondly $ 对于每个任务，我们就可以以每个颜色为中转点q求解最小值了，在预处理时和通常的 $ bfs $ 写法大同小异，在每次更新时可能加入多个起点，同时进行多个状态求解出最小值。

## 实现代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ull;

const int N = 1e3+100;
const int b[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
//上下左右四个方向的数组

struct stu {
	int x, y;
	stu(int x,int y):x(x), y(y) {};
};
// 结构体存储每个单元格及其颜色
int w[N][N], n, m, k;

vector<stu>color[45];//颜色值数组

int dsu[45][N][N];//从点 ( x , y  )到 color 颜色的最短路径

bool visit[N][N], visit_color[45];

void read(int &x) {//快速读入 
	char ch = getchar();
	int flag = 0;
	x = 0;
	while (ch < '0' || ch > '9')
		flag |= (ch == '-'), ch = getchar();
	while (ch >= '0' && ch <= '9')
		 x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	if (flag)
		x = -x;
}

void print(int x)//快速输出 
{
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
//常规的bfs
void bfs(int id) {
	memset(visit, false, sizeof(visit));
	memset(visit_color, false, sizeof(visit_color));
	queue<stu>q;
	for(int i = 0; i < color[id].size(); i++) {
		int x = color[id][i].x, y = color[id][i].y;
		q.push(stu(x, y));
		visit[x][y] = true;
		dsu[id][x][y] = 0;
	}
	visit_color[id] = true;
	while(q.size()) {
		stu cur = q.front();
		q.pop();
		int x = cur.x, y = cur.y;
		if(!visit_color[w[x][y]]) { //移动
			visit_color[w[x][y]] = true;
			for(int i = 0; i < color[w[x][y]].size(); i++) {
				int xx = color[w[x][y]][i].x, yy = color[w[x][y]][i].y;
				if(visit[xx][yy])
					continue;
				q.push(stu(xx,yy));
				visit[xx][yy] = true;
				dsu[id][xx][yy] = dsu[id][x][y] + 1;
			}
		}
		for(int i = 0; i < 4; i++) { //不移动
			int xx = x + b[i][0];
			int yy = y + b[i][1];
			if(xx <= 0 || xx > n || yy <= 0 || yy > m)
				continue;
			if(visit[xx][yy])
				continue;
			visit[xx][yy] = true;
			q.push(stu(xx,yy));
			dsu[id][xx][yy] = dsu[id][x][y] + 1;
		}
	}
}

int main() {
	int q;//任务数
	read(n);
	read(m);
	read(k);
	//输入行数和列数以及颜色数
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			cin >> w[i][j];
			color[w[i][j]].push_back(stu(i,j));//加入颜色值
		}
	for(int i = 1; i <= k; i++)//预处理
		bfs(i);
	read(q);//输入总的任务数
	while(q--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;//输入起点城市和终点城市坐标
		int ans = abs(x1 - x2) + abs(y1 - y2);
		for(int i = 1; i <= k; i++)
			ans = min(ans, dsu[i][x1][y1] + dsu[i][x2][y2] + 1);
		print(ans); 
		cout << endl;
	}
	return 0;
}

```
本蒟蒻发布的第一篇题解，~~本蒟蒻太蒟蒻了~~。


---

## 作者：LRRabcd (赞：0)

# [Super Jaber](https://www.luogu.com.cn/problem/CF1301F)

如果每次询问都 BFS 一次，肯定会超时，于是我们换种思路先预处理，每次询问直接调用。

## 预处理
| $\color{orange}{2步}$ | $\color{orange}{2步}$ | $\color{red}{1步}$ | $\color{orange}{2步}$ | $\color{green}{3步}$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $\color{red}{1步}$ | $\color{red}{1步}$ | 传送门 $1$ | $\color{red}{1步}$ | $\color{orange}{2步}$ |
| 传送门 $2$ | $\color{red}{1步}$ | $\color{red}{1步}$ | $\color{orange}{2步}$ | $\color{orange}{2步}$ |
| $\color{red}{1步}$ | $\color{orange}{2步}$ | $\color{orange}{2步}$ | $\color{orange}{2步}$ | $\color{red}{1步}$ |
| $\color{orange}{2步}$ | $\color{green}{3步}$ | $\color{orange}{2步}$ | $\color{red}{1步}$ | 传送门 $3$ |
| $\color{red}{1步}$ | $\color{orange}{2步}$ | $\color{green}{3步}$ | $\color{orange}{2步}$ | $\color{red}{1步}$ |
| 传送门 $4$ | $\color{red}{1步}$ | $\color{orange}{2步}$ | $\color{green}{3步}$ | $\color{orange}{2步}$ |

上图是一个多源（既有多个起点）BFS，如果枚举起点，时间复杂度并不优。于是我们反过来想，从传送门出发，找每个点的最短距离。

最多 $40$ 种颜色，假设当前枚举到了 $i$ 颜色传送门，那么从起点到终点的最短步数就是起点到 $i$ 颜色传送门 $+i$ 颜色传送门到终点 的最短距离。

## 注意点：

- 有一种情况，就是不使用传送门，这样从起点到终点的最少步数就是起点终点间的曼哈顿距离。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int a[1005][1005];
int dis[45][1005][1005];
bool flag[45];
int dx[5]={0,0,-1,1};
int dy[5]={-1,1,0,0};
struct node{
	int x,y;
	int step;
};
vector<pair<int,int>>v[45];
void bfs(int s){
    for(int i=1;i<=k;i++){
        flag[i]=0;
    }
    queue<node>q;
	for(int i=0;i<v[s].size();i++){
		q.push({v[s][i].first,v[s][i].second,0});
		dis[s][v[s][i].first][v[s][i].second]=0;
	}
	while(q.size()){
		node t=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int tx=t.x+dx[i];
			int ty=t.y+dy[i];
			if(tx<1||ty<1||tx>n||ty>m||dis[s][tx][ty]<=t.step+1){
				continue;
			}
			dis[s][tx][ty]=t.step+1;
			q.push({tx,ty,t.step+1});
		}
		if(flag[a[t.x][t.y]]==0){
			flag[a[t.x][t.y]]=1;
			for(int i=0;i<v[a[t.x][t.y]].size();i++){
				int tx=v[a[t.x][t.y]][i].first;
				int ty=v[a[t.x][t.y]][i].second;
				if(dis[s][tx][ty]>t.step+1){
					dis[s][tx][ty]=t.step+1;
					q.push({tx,ty,t.step+1});
				}
			}
		}
	}
}
int main(){
	cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            v[a[i][j]].push_back({i,j});
        }
    }
    for(int i=1;i<=k;i++){
    	for(int j=1;j<=n;j++){
    		for(int l=1;l<=m;l++){
    			dis[i][j][l]=1e9;
			}
		}
	}
    for(int i=1;i<=k;i++){
    	bfs(i);
	}
    int q;
    cin>>q;
    while(q--){
        int sx,sy;
        int ex,ey;
        cin>>sx>>sy>>ex>>ey;
        int cnt=abs(sx-ex)+abs(sy-ey);
		for(int i=1;i<=k;i++){
			cnt=min(cnt,dis[i][sx][sy]+dis[i][ex][ey]+1);
		}
		cout<<cnt<<"\n";
    }
    return 0;
}
```

---

## 作者：ATION001 (赞：0)

每次询问就跑一遍 BFS，必定会超时。

考虑预处理。

对于不使用传送门的情况：由于地图上不存在障碍，所以距离为曼哈顿距离。

曼哈顿距离公式：

$$
|dx-ex|+|ey-ey|
$$

对于使用了传送门的情况：

可以证明，**相同颜色传送门只需要使用一次**（间接传送不如直接就进行传送）。

设 $dis_{i,j,k}$ 表示从 $(i,j)$ 出发，到达离其最近的颜色 $k$ 传送门需要多少代价。

最终答案为 $dis_{dx,dy,k}+dis_{ex,ey,k}+1$（起点（$dx,dy$）到达 $k$ 传送门的代价+终点（$ex,ey$）到达 $k$ 传送门的代价+传送的代价）。
### 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,t,a[1005][1005],dis[1005][1005][45],xyx[5][3]={{-1,0},{1,0},{0,1},{0,-1}};
bool vis[45];
vector<pair<int,int>>v[45];
int Dis(int dx,int dy,int ex,int ey){
	return abs(dx-ex)+abs(dy-ey);
}
void bfs(int color){
	fill(vis,vis+k+1,false);
	queue<pair<int,int>>q;
	vis[color]=true;
	for(auto z:v[color]){
		dis[z.first][z.second][color]=0;
		q.push(z);
	}
	while(q.size()){
		auto p=q.front();
		q.pop();
		if(!vis[a[p.first][p.second]]){
			vis[a[p.first][p.second]]=true;
			for(auto z:v[a[p.first][p.second]]){
				if(dis[z.first][z.second][color]>dis[p.first][p.second][color]+1){
					dis[z.first][z.second][color]=dis[p.first][p.second][color]+1;
					q.push(z);
				}
			}
		}
		for(int i=0;i<4;i++){
			int dx=p.first+xyx[i][0],dy=p.second+xyx[i][1];
			if(dx&&dy&&dx<=n&&dy<=m&&dis[dx][dy][color]>dis[p.first][p.second][color]+1){
				dis[dx][dy][color]=dis[p.first][p.second][color]+1;
				q.push({dx,dy});
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			v[a[i][j]].push_back({i,j});
		}
	}
	fill(dis[0][0],dis[n+1][m+1],1e18);
	for(int i=1;i<=k;i++){
		bfs(i);
	}
	for(cin>>t;t;t--){
		int Bx,By,Ex,Ey;
		cin>>Bx>>By>>Ex>>Ey;
		int ans=Dis(Bx,By,Ex,Ey);
		for(int i=1;i<=k;i++){
			ans=min(ans,dis[Bx][By][i]+dis[Ex][Ey][i]+1);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

写了个基于 dp 的巨大烂做法。

下文称走同颜色点之间的边为瞬移。

如果一次都不瞬移，计算是简单的。

如果瞬移了至少一次，那你发现第一次瞬移之后与最后一次瞬移之前的事和起点终点是啥没啥关系。

于是设计状态 $dp_{u,v,0/1,0/1}$ 表示从某个颜色为 $u$ 的点走到某个颜色为 $v$ 的不同点，且第一次走的边是不是瞬移，最后一次走的边是不是瞬移的最短距离，考虑对每种颜色跑一次多源最短路求解出距离每个点距离最近的某种颜色的点以处理 $dp_{u,v,0/1,0/1}$ 的初始值，然后对 $dp$ 做一遍类 Floyd 状物求解真实值，转移方程大概是 $dp_{i,j,t,w} = \min(dp_{i,k,t,z}+dp_{k,j,d,w} + cost(z,d))$ 其中 $cost(z,d)$ 在 $z=0,d=0$ 时为 $1$ 否则为 $0$，询问时枚举第一次瞬移与最后一次瞬移的颜色即可做到 $O(n \times m \times k + k^3 + q \times k^2)$。

[代码](https://codeforces.com/contest/1301/submission/290703457)

---

## 作者：yr409892525 (赞：0)

## [Super Jaber CF1301F](https://www.luogu.com.cn/problem/CF1301F)

### 暴力做法

每一次都跑一遍 BFS，时间复杂度为：$O(q \cdot nm)$，$n,m \le 10^3 , q \le 10^5$。

$10^{11}$ 次肯定会超时。  

### 分析

因为终点和起点不唯一，不妨反向思考，从每一种传送门到每一个点的最小距离。  

- 枚举  

因为传送门的颜色数量只有 $40$ 种，假装当前使用的是第 $i$ 种传送门，枚举 $i$ 从 $1 \sim k$，每一种颜色跑一边 BFS。  

- BFS

这个 BFS 不像之前只有一个起点，因为每种颜色的传送门有多个需要全部设为起点，我们还需要一个数组 $dis$ 数组和一个 $f$ 数组。  

$dis_{i,j,k}$ 表示通过第 $i$ 种颜色的传送门，终点为 $(j,k)$ 的最少步数。  

$f_i$ 表示第 $i$ 种颜色的传送门是否使用，通过上一讲的分析，如果传送门类型一样只会使用一次。  

- 易错点

  - $dis$ 数组开始要赋成极大值。
  - $f$ 数组每次记得清空。
  - $dis$ 数组的起点为 $0$。

- 答案

答案分为两种：  

走传送门：  

曼哈顿距离：$|sx - ex| + |ex - ey|$。  

不走传送门：  

枚举每一种颜色，$dis_{sx,sy} + dis_{ex,ey} + 1$，再取最小值就是答案。    

### 实现代码
```cpp
//Super Jaber CF1301F
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int a[1005][1005];
int v[41][1001][1001];
bool f[45];
vector < pair<int,int> > g[45];
int dx[10]={1,-1};
int dy[10]={0,0,1,-1};
struct code{
	int x,y;
};
bool check(int x,int y){
	if(x>=1 && x<=n && y>=1 && y<=m) return 1;
	else return 0;
}
void bfs(int num){
	memset(f,0,sizeof(f));
	queue <code> q;
	for(int i=0;i<g[num].size();i++){
		q.push({g[num][i].first,g[num][i].second});
		v[num][g[num][i].first][g[num][i].second]=0; 
	}
	while(!q.empty()){
		code u=q.front();
		q.pop();
		int x=u.x;
		int y=u.y;
		for(int i=0;i<4;i++){
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(check(xx,yy)){
				if(v[num][xx][yy]>v[num][x][y]+1){
					q.push({xx,yy});
					v[num][xx][yy]=v[num][x][y]+1;
				}
			}
			if(f[a[x][y]]==0){
				f[a[x][y]]=1;
				for(int j=0;j<g[a[x][y]].size();j++){
					int xx=g[a[x][y]][j].first;
					int yy=g[a[x][y]][j].second;
					if(v[num][xx][yy]>v[num][x][y]+1){
						q.push({xx,yy});
						v[num][xx][yy]=v[num][x][y]+1;
					}
				}
			}
		}
		
	}
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			g[a[i][j]].push_back(make_pair(i,j));
		}
	}
	memset(v,0x3f,sizeof(v));
	for(int i=1;i<=k;i++){
		bfs(i);
	}
	int q;
	cin>>q;
	while(q--){
		int sx,sy,ex,ey;
		cin>>sx>>sy>>ex>>ey;
		int ans=abs(sx-ex)+abs(sy-ey);
		for(int i=1;i<=k;i++){
			ans=min(ans,v[i][sx][sy]+v[i][ex][ey]+1);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：2b2b2bbb (赞：0)

# 思路
这道题有多次的查询那么我们就不能枚举了而要先进行预处理。                  
首先我们知道传送门并不是强制传送的那么我们要找距离，那么我们只有两种情况。          
1，不使用传送门。          
因为题目给出的网格中是没有障碍的，所以如果我们不使用传送门的话，距离就是曼哈顿距离。     
2，使用传送门          
我们可以发现从传送门 $A \rightarrow$ 传送门 $B \rightarrow$ 传送门 $C$ 还不如直接从传送门 $A \rightarrow$ 传送门 $C$ 。                 
因此我们可以发现相同的传送门我们最多也就只能用1次。   
根据这个结论我们可以用 $dis_{k,i,j}$ 表示从 $(i , j)$ 到第 $k$ 种颜色传送门的距离。                
因此我们就知道了使用传送门的最短距离就是：起点到一个颜色为 $x$ 的距离 + 终点到这个颜色的格子的距离加上一。                       
因为传送门是从一个颜色相同的地方，跳到另一个颜色相同的地方。                
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
bool flag[50];
int dis[45][1005][1005];
int a[1005][1005];
bool vis[1005][1005];
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
vector<pair<int,int> > p[1005];
struct pi{
	int x,y,step;
};
bool check(int x,int y){
	if(x>=1&&x<=n&&y>=1&&y<=m&&!vis[x][y])return true;
	return false;
}
void bfs(int num){
	memset(vis, 0, sizeof(vis));
	memset(flag, 0, sizeof(flag));
	queue<pi> q;
	for(int i = 0 ; i < p[num].size() ; i ++){
		q.push({p[num][i].first , p[num][i].second,0});
		vis[p[num][i].first][p[num][i].second] = 1; 
		dis[num][p[num][i].first][p[num][i].second] = 0; 
	} 
	while(!q.empty()){
		pi u = q.front();
		q.pop();
		for(int i = 0 ; i < 4 ; i ++){
			int xx = dx[i] + u.x;
			int yy = dy[i] + u.y;
			if(check(xx,yy)){
				if(dis[num][xx][yy] > dis[num][u.x][u.y] + 1){
//					vis[xx][yy]=1;
	                q.push({xx, yy, u.step + 1});
	                dis[num][xx][yy] = dis[num][u.x][u.y] + 1;
	            }
			}
		}
		if(!flag[a[u.x][u.y]]){
			flag[a[u.x][u.y]] = 1;
			for(int i = 0 ; i < p[a[u.x][u.y]].size() ; i ++){
				int xx = p[a[u.x][u.y]][i].first;
				int yy = p[a[u.x][u.y]][i].second;
				if(!vis[xx][yy]){
					if(dis[num][xx][yy] > dis[num][u.x][u.y] + 1){
						vis[xx][yy] = 1;
		                q.push({xx, yy, u.step + 1});
		                dis[num][xx][yy] = dis[num][u.x][u.y] + 1;
					}	
				}
				
			}
		}
	}
} 
int main(){
	cin >> n >> m >> k;
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= m ; j ++){
			cin >> a[i][j];
			p[a[i][j]].push_back({i,j});
		}
	}
	memset(dis , 0x3f , sizeof(dis));
	for(int i = 1 ; i <= k ; i ++){
		bfs(i);
	} 
	int T;
	cin >> T;
	while(T --){
		int x,y,u,d;
		cin >> x >> y >> u >> d;
		int ans = abs(u - x) + abs(d - y);
		for(int i = 1 ; i <= k ; i ++)ans = min(ans , dis[i][x][y] + dis[i][u][d] + 1);
		cout << ans << endl;
	} 
	return 0;
}
```

---

## 作者：sieve (赞：0)

# 题解：[Super Jaber](https://www.luogu.com.cn/problem/CF1301F)

某同学：这题看上去一点都不难嘛，咋会有紫题捏？

（看了一眼数据范围）

Oh my god! 这时间复杂度不得巨高！！！怪不得有紫题难度。

那么，处理这种超大数据的方法是什么呢？

既然地图都是一个，直接**预处理**！

我们怎样预处理呢？针对每种颜色进行处理，最后直接取曼哈顿距离和使用各种颜色所需的最小距离进行对比，最后输出最小值。

既然是对每种颜色进行处理，那么，我们就要循环 $k$ 次，算一下时间复杂度：$O(nmk)$，好险，没超。

针对每种颜色，我们需要在 BFS 里面再传一个参数 $sum$ 表示当前使用的是第几种颜色，对于每个颜色，我们有两种选择：普通 BFS，使用传送门的 BFS。

那么，对于使用传送门的 BFS，我们循环所有能传送到的颜色，然后打上标记，防止重复走。

那么，我们怎样存储时间？开个数组。

注意，开了 long long 见祖宗，这样做会爆空间的！因为 long long 运算时会有两倍的常数。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
const int N=1002;
int a[N][N];
int dis[42][N][N];
bool vis2[42];
vector<pair<int,int> > v[42];
int dx[]={0,1,-1,0,0};
int dy[]={0,0,0,1,-1};
struct no{
	int x,y;
};
void bfs(int sum)
{
	memset(vis2,0,sizeof(vis2));
	vis2[sum]=1;
	queue<no> q;
	for(int i=0;i<v[sum].size();++i)
	{
		q.push(no{v[sum][i].first,v[sum][i].second});
		dis[sum][v[sum][i].first][v[sum][i].second]=0;
	}
	while(!q.empty())
	{
		no tmp=q.front();
		q.pop();
		for(int i=1;i<=4;++i)
		{
			int nx=tmp.x+dx[i];
			int ny=tmp.y+dy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&dis[sum][nx][ny]>dis[sum][tmp.x][tmp.y]+1)
			{
				q.push(no{nx,ny});
				dis[sum][nx][ny]=dis[sum][tmp.x][tmp.y]+1;
			}
		}
		if(vis2[a[tmp.x][tmp.y]]==0)
		{
			vis2[a[tmp.x][tmp.y]]=1;
			for(int j=0;j<v[a[tmp.x][tmp.y]].size();++j)
			{
				int nx=v[a[tmp.x][tmp.y]][j].first;
				int ny=v[a[tmp.x][tmp.y]][j].second;
				if(dis[sum][nx][ny]>dis[sum][tmp.x][tmp.y]+1)
				{
					q.push(no{nx,ny});
					dis[sum][nx][ny]=dis[sum][tmp.x][tmp.y]+1;
				}
			}
		}
	}
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			cin>>a[i][j];
			v[a[i][j]].push_back(make_pair(i,j));
		}
	}
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=k;++i) bfs(i);
	int t;
	cin>>t;
	while(t--)
	{
		int sx,sy,ex,ey;
		cin>>sx>>sy>>ex>>ey;
		int mn=abs(sx-ex)+abs(sy-ey);
		for(int i=1;i<=k;++i)
		{
			mn=min(mn,dis[i][sx][sy]+dis[i][ex][ey]+1);
//			cout<<dis[i][sx][sy]<<' '<<dis[i][ex][ey]+1<<'\n'; 
		}
		cout<<mn<<'\n';
	}
	return 0;
}
```

---

## 作者：_yang_yi_bo_ (赞：0)

这道题的起点与终点不唯一，需要 $q$ 次询问，可以想到预处理，而由于是迷宫问题，容易想到是用 BFS 预处理。

我们可以反向思考，从传送门出发，找每个点的最近距离。

最多 $40$ 种颜色，当在使用颜色 $k$ 的传送门时，答案是起点到 $k$ 颜色的最短距离 $+$ 终点到 $k$ 颜色的最短距离。

那不使用传送门呢？还要跑一遍 BFS 吗？由于这题没有障碍物，最短距离为曼哈顿距离。

贴心给出曼哈顿距离的公式：

$dis=\lvert x_1 - x_2 \rvert + \lvert y_1 - y_2 \rvert $

那么，如何求起点与终点到 $k$ 颜色的最短距离呢？

![map](https://cdn.luogu.com.cn/upload/image_hosting/rh0d2xb8.png)

~~excel 大法好。~~

如图，我们要实现多个起点的 BFS，也就是多源 BFS。

实现方法很简单：将一堆起点一股脑塞入队列中，在正常进行 BFS 就行了。

给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,q;
int a[1005][1005];
int dis[45][1005][1005];
bool flag[45];
struct kkk{
	int x,y,step;
};
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
vector<pair<int,int> > o[45];
void bfs(int x){
	queue<kkk> q;
	for(int i=1;i<=k;i++){
		flag[i]=0;
	}for(int i=0;i<o[x].size();i++){
		q.push({o[x][i].first,o[x][i].second,0});
		dis[x][o[x][i].first][o[x][i].second]=0;
	}while(!q.empty()){
		kkk u=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int xx=u.x+dx[i];
			int yy=u.y+dy[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m){
				if(dis[x][xx][yy]>dis[x][u.x][u.y]+1){
					q.push({xx,yy,u.step+1});
					dis[x][xx][yy]=dis[x][u.x][u.y]+1;
				}
			}if(flag[a[u.x][u.y]]==0){
				flag[a[u.x][u.y]]=1;
				for(int i=0;i<o[a[u.x][u.y]].size();i++){
					int xx=o[a[u.x][u.y]][i].first;
					int yy=o[a[u.x][u.y]][i].second;
					if(dis[x][xx][yy]>dis[x][u.x][u.y]+1){
						q.push({xx,yy,u.step+1});
						dis[x][xx][yy]=dis[x][u.x][u.y]+1;
					}
				}
			}
		}
	}
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			o[a[i][j]].push_back(make_pair(i,j));
		}
	}memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=k;i++){
		bfs(i);
	}cin>>q;
	while(q--){
		int sx,sy,ex,ey,cnt;
		cin>>sx>>sy>>ex>>ey;
		cnt=abs(sx-ex)+abs(sy-ey);
		for(int i=1;i<=k;i++){
			cnt=min(cnt,dis[i][sx][sy]+dis[i][ex][ey]+1);
		}cout<<cnt<<"\n";
	}
	return 0;
}
```

---

## 作者：柠檬草苏打水 (赞：0)

### 思路：

由于q次询问,那么至少必须O(1) ~ log(n)解决。
有与图中无障碍，那么如果不使用跳跃的话，起点到终点的距离就是曼哈顿距离。
接下来考虑跳跃。可以用d[k][i][j] 代表(i, j)这个点到达颜色为k的格子的最小距离。 那么使用跳跃的到达终点的最少距离就是：起点到达颜色k的最短距离 + 1（从这个格子跳到另外一个颜色相同的）+ 终点到达这个颜色相同的格子的最短距离。
答案就是2者取个最小值就是。 注意加上的1是因为我必须要跳一次，如果不跳的话那么就是曼哈顿距离了。因为某点到达某个颜色最后一步肯定是通过走的，那么起点和终点都是通过走的到达这个颜色，那么如果颜色位置相同的那么就等于是曼哈顿距离了，如果不相同的话那么就要跳一次，跳到终点的那个相同颜色的位置出。

### Code：
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;
const int N = 1005, M = 45;
struct Node {
	int x, y;
	Node(int x, int y): x(x), y(y){}
};
int n, m, q, k, g[N][N], d[M][N][N];
bool vis[M];
vector<Node> c[M];
int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, -1, 1, 0};
void bfs(int k) {
	queue<Node> q;
	memset(vis, false, sizeof(vis));
	for (int i = 0; i < c[k].size(); i++) {
		int x = c[k][i].x, y = c[k][i].y;
		d[k][x][y] = 0; q.push(Node(x, y));
	}
	vis[k] = true;
	while (!q.empty()) {
		Node t = q.front(); q.pop();
		int tx = t.x, ty = t.y, td = d[k][t.x][t.y], tc = g[t.x][t.y];
		//代表可以这个颜色可以跳
		if (!vis[tc]) {
			vis[tc] = true;
			for (int i = 0; i < c[tc].size(); i++) {
				int x = c[tc][i].x ,y = c[tc][i].y;
				if (d[k][x][y] != -1) continue;
				d[k][x][y] = td + 1; q.push(Node(x, y)); 
			} 
		}
		for (int i = 0; i < 4; i++) {
			int x = tx + dx[i]; 
			int y = ty + dy[i]; 
			if (x <= 0 || y <= 0 || x > n || y > m || d[k][x][y] != -1) continue;
			d[k][x][y] = td + 1; q.push(Node(x, y));
		} 
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &g[i][j]); c[g[i][j]].push_back(Node(i, j));
		}
	}
	memset(d, -1, sizeof(d));
	for (int i = 1; i <= k; i++) bfs(i);
	scanf("%d", &q);
	while (q--) {
		int x1, x2, y1, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		int ans = abs(x1 - x2) + abs(y1 - y2); //曼哈顿距离
		for (int i = 1; i <= k; i++) ans = min(ans, d[i][x1][y1] + d[i][x2][y2] + 1); //1代表必须跳一次 
		printf("%d\n", ans); 
	} 
	return 0;
}

---

