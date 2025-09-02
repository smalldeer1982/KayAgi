# [ARC177C] Routing

## 题目描述

有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

## 样例 #1

### 输入

```
5
RBRBB
RBRRR
RRRBR
RBBRB
BBRBR```

### 输出

```
3```

## 样例 #2

### 输入

```
5
RBBBB
BBBBB
BBBBB
BBBBB
BBBBR```

### 输出

```
7```

## 样例 #3

### 输入

```
10
RRBBBBBBBB
BRRBBBBBBB
BBRRBBBBBB
BBBRRBBBBB
BBBBRRBBBB
BBBBBRRBBB
BBBBBBRRBB
BBBBBBBRRB
BBBBBBBBRR
BBBBBBBBBR```

### 输出

```
2```

## 样例 #4

### 输入

```
17
RBBRRBRRRRRBBBBBB
BBRBRBRRBRRBRRBBR
BRBRBBBRBBRBBRBBB
RBRRBBBBBBRRBRRRR
RRRRRBRBRRRBBRBBR
RRRRRBRRBRBBRRRBB
BBBRRRBRBRBBRRRBB
BBRRRBRBBBRBRRRBR
RRBBBBBBBBBBBRBRR
RRRBRRBRBRBRBRBBB
RRBRRRRBRBRRBRBBR
RRRBBRBRBBBRBBRBR
BBRBBRRBRRRBBRBBB
BBBRBRRRRRRRBBRBB
RRRRRBRBRBBRRBRRR
BRRRRBBBRRRBRRBBB
BBRRBBRRRBBBRBBBR```

### 输出

```
8```

# 题解

## 作者：Big_Dinosaur (赞：1)

看似是在网格上操作，事实可以用图论。

考虑只符合条件一操作次数：将网格上相邻的点进行连**有向**边，若终点为红色边权为 $0$，否则为 $1$。从左上到右下跑一遍最短路。

接下来，可以证明使只符合条件一与条件二的修改互不相关：条件一只会把蓝色改成紫色，修改后条件二将走蓝色改为走紫色，本质上无差别。反过来也是这样。

将网格上相邻的点重新连有向边，若终点为蓝色边权为 $0$，否则为 $1$。从左下到右上跑一遍最短路。两次路径长度和为答案。

---

## 作者：__Floze3__ (赞：1)

## 思路简介

看到题目给的是网格图，并且 $N \le 500$，我们不妨考虑使用 bfs 求出两组值：从 $(1, 1)$ 开始，走到每一个格子最少需要将几个格子改变颜色，不妨记为 $a_{i, j}$；以及从 $(1, N)$ 开始，走到每一个格子最少需要将几个格子改变颜色，不妨记为 $b_{i, j}$。那么最后的答案即为 $a_{n, n} + b_{n, 1}$。为什么这样不会出现两条路径相交部分重复计算的情况？因为如果有着相交部分，那么一定有一条路径是可以直接穿过这个格子的（因为两条路径的颜色不同），因此一个格子在两次 bfs 中最多被改变一次颜色，这保证了答案的正确性。

现在唯一的问题是：我们如何得出走到每个格点要改变格点颜色的最小数量？我们不妨从图论的角度看待这个问题：每个格点向其四周的格点连了边，如果要改变颜色那么边权为 $1$，反之边权为 $0$。那么我们要求出的就是从起点到每一个点的最短路。题解中采用的是优先队列 bfs，因此复杂度带了一个 $\log$。但是！由于边权只有 $0$ 和 $1$，我们可以使用 01bfs，那么只需要 $O(n^2)$ 的复杂度就可以解决这个问题了！

## 代码

[提交记录](https://atcoder.jp/contests/arc177/submissions/53448196)

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc177_c)

可以发现，如果一个红色格子变成紫色，那么在颜色必须为红色的路径上这个格子照样能走，蓝色的情况同理。

那么这就说明在处理一种颜色的路径时将一个格子变为紫色不会影响到另一种颜色的路径。

所以只需要对于两种路径都求一下需要变几个格子最后加起来就行了。

对于该类问题的求法这里使用的是 01bfs，这个算法的模板题这里放一道：[模板题](https://www.luogu.com.cn/problem/AT_abc213_e)，在此不对此算法进行讲解。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
char mp[510][510];
struct aaa
{
	int x,y,s;
};
deque<aaa> q;
int dis[510][510];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int ans=0;
inline void bfs(int sx,int sy,int ex,int ey,char ch)
{
	q.push_front(aaa{sx,sy,(mp[sx][sy]!=ch)});
	dis[sx][sy]=(mp[sx][sy]!=ch);
	while(!q.empty())
	{
		aaa now=q.front();
		q.pop_front();
		if(now.x==ex&&now.y==ey)
		{
			ans+=dis[ex][ey];
			while(!q.empty()) q.pop_front();
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					dis[i][j]=1e9;
			return;
		}
		for(int i=0;i<4;i++)
		{
			int x=now.x+dx[i],y=now.y+dy[i];
			if(x<1||x>n||y<1||y>n) continue;
			if(dis[now.x][now.y]+(ch!=mp[x][y])<dis[x][y])
			{
				dis[x][y]=dis[now.x][now.y]+(ch!=mp[x][y]);
				if(ch!=mp[x][y])
					q.push_back(aaa{x,y,dis[x][y]});
				else
					q.push_front(aaa{x,y,dis[x][y]});
			}
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>mp[i][j],dis[i][j]=1e9;
	bfs(1,1,n,n,'R');
	bfs(1,n,n,1,'B');
	cout<<ans;
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

幽默 500 题目。

# 正文

![](https://img.atcoder.jp/arc177/7f2b28ec79263ffd4381a20038c7daef.png)

这张图就有许多值得意淫的点了。令 $R$ 路线为 $(1, 1) \to (N, N)$ 的路线，$B$ 路线为 $(1, N) \to (N, 1)$ 的路线。

我们猜：当走 $R$ 路线时，每走一步所到达的格子若为 $B$，则认为我们必须把这个格子改成 $P$。这样做的代价为 $1$。

而在走 $B$ 路线时，每走一步所到达的格子若为 $R$，则认为我们必须把这个格子改成 $P$。这样做的代价也为 $1$。

仔细一想感觉非常对啊。因为由一条路线的决策产生的一个点的改，并不影响另一条路线的决策；所以我们可以无脑建图，两种路线分别跑个最短路，答案相加即可。~~其实可以 01 BFS。~~

---

## 作者：I_will_AKIOI (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/7b7g46wy.png)

观察可知，将一个 R 改为 P 后，红色的路还是可以正常行走，蓝色的路则从不能通过该点变成可以通过该点。因此让蓝色的路能到终点需要染色的格子数就是 $(1,n)$ 到 $(n,1)$ 需要经过的最少 R 的数量，红色的路同理由于。可以上下左右移动，所以不能使用动态规划。

考虑转化为图论问题，然后求解最短路，两个相邻的格子可以看做连有一条边，若边的终点为 R，则说明要经过一个 R，可以认为这条边的边权为  $1$，反之为 $0$。红色的路反之。然后建图跑两遍最短路就行了，答案就是两条最短路之和。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Data
{
  int to,val;
  bool operator <(const Data &w)const {return w.val<val;}
}w;
vector<Data>G[500005];
priority_queue<Data>q;
int n,m,x,y,z,ans,d[500005],fx[4]={0,1,0,-1},fy[4]={1,0,-1,0};
char c[505][505];
bool vis[500005];
int main()
{
  ios::sync_with_stdio(0);
  memset(d,0x3f,sizeof(d));
  cin>>n;
  for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>c[i][j];
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      for(int k=0;k<4;k++)
      {
        int nx=i+fx[k],ny=j+fy[k];//往一个点的四个方向尝试连边
        if(nx<1||nx>n||ny<1||ny>n) continue;
        G[(i-1)*n+j].push_back(Data{(nx-1)*n+ny,(c[nx][ny]=='B')});
      }
    }
  }
  d[1]=0;
  q.push(Data{1,0});
  while(!q.empty())//跑红色的最短路
  {
  	w=q.top(),x=w.to;
  	q.pop();
    if(vis[x]) continue;
    vis[x]=1;
    for(int i=0;i<G[x].size();i++)
    {
      int y=G[x][i].to;
      if(d[x]+G[x][i].val<d[y])
      {
      	d[y]=d[x]+G[x][i].val;
      	if(!vis[y]) q.push(Data{y,d[y]});
	    }
	  }
  }
  ans+=d[n*n];
  memset(d,0x3f,sizeof(d));
  memset(vis,0,sizeof(vis));
  for(int i=1;i<=n*n;i++) G[i].clear(); 
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      for(int k=0;k<4;k++)
      {
        int nx=i+fx[k],ny=j+fy[k];//建边
        if(nx<1||nx>n||ny<1||ny>n) continue;
        G[(i-1)*n+j].push_back(Data{(nx-1)*n+ny,(c[nx][ny]=='R')});
      }
    }
  }
  d[n]=0;
  q.push(Data{n,0});
  while(!q.empty())//跑蓝色最短路
  {
  	w=q.top(),x=w.to;
  	q.pop();
    if(vis[x]) continue;
    vis[x]=1;
    for(int i=0;i<G[x].size();i++)
    {
      int y=G[x][i].to;
      if(d[x]+G[x][i].val<d[y])
      {
      	d[y]=d[x]+G[x][i].val;
      	if(!vis[y]) q.push(Data{y,d[y]});
	    }
	  }
  }
  ans+=d[(n-1)*n+1];
  cout<<ans;
  return 0;
}
```

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[AtCoder](https://atcoder.jp/contests/arc177/tasks/arc177_c)/[洛谷](https://www.luogu.com.cn/problem/AT_arc177_c)

## 题目大意

给出一张 $n\times n$ 大小的已经涂成红蓝双色的网格图，其中 $(1,1)$ 和 $(n,n)$ 是红色，$(1,n)$ 和 $(n,1)$ 是蓝色，问最少将几个格子涂成紫色能够找到一条从 $(1,1)$ 到 $(n,n)$ 的不经过蓝色格子的路线以及一条从 $(1,n)$ 到 $(n,1)$ 的不经过红色格子的路线。

## 解题思路

将红色涂成紫色不会对 $(1,1)$ 到 $(n,n)$ 的路径产生影响，将蓝色涂成紫色不会对 $(n,1)$ 到 $(1,n)$ 的路径产生影响，故问题可以分成两个子问题：

- 将多少个蓝色格子涂成紫色能够找到一条从 $(1,1)$ 到 $(n,n)$ 的不经过蓝色格子的路径；
- 将多少个红色格子涂成紫色能够找到一条从 $(1,n)$ 到 $(n,1)$ 的不经过红色格子的路径。

再简化一下，原问题就可转化为如下问题：

- 从 $(1,1)$ 到 $(n,n)$ 至少需要经过多少个蓝色格子；
- 从 $(1,n)$ 到 $(n,1)$ 至少需要经过多少个红色格子。

设 $C_{x,y}$ 表示格子 $(x,y)$ 的颜色，$B_{x,y}$ 表示从 $(1,1)$ 到 $(x,y)$ 经过的蓝色格子的数量，$R_{x,y}$ 表示从 $(1,n)$ 到 $(x,y)$ 经过的红色格子的数量，我们可以得到：

$$B_{x,y}=\begin{cases}
0&,(x,y)=(1,1)\\
\min(B_{x-1,y},B_{x+1,y},B_{x,y-1},B_{x,y+1})+1&,C_{x,y}=B\\
\min(B_{x-1,y},B_{x+1,y},B_{x,y-1},B_{x,y+1})&,C_{x,y}=R
\end{cases}\\
R_{x,y}=\begin{cases}
0&,(x,y)=(1,n)\\
\min(R_{x-1,y},R_{x+1,y},R_{x,y-1},R_{x,y+1})+1&,C_{x,y}=R\\
\min(R_{x-1,y},R_{x+1,y},R_{x,y-1},R_{x,y+1})&,C_{x,y}=B
\end{cases}$$

因为同一个蓝色连通块的 $R_{x,y}$ 值相同，同一个红色连通块中的 $B_{x,y}$ 值相同，我们可以使用广度优先搜索解决，每次优先搜索目标值（$R_{x,y}$ 或 $B_{x,y}$）相同的方块，这样就可以确保得到的答案是最小的。

最终输出 $B_{n,n}+R_{n,1}$ 即可。时间复杂度 $O(n^2)$，可以轻松通过。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int Read(){
	char c=getchar();while(c<'0'||c>'9')c=getchar();
	int r=0;while(c>='0'&&c<='9'){r=r*10+(c^48);c=getchar();}
	return r;
}
char c[502][502];
int val[501][501][2];
bool vis[501][501][2];
int main(){
	int n=Read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		do{
			c[i][j]=getchar();
		}while(c[i][j]!='B'&&c[i][j]!='R');
	}
	queue<pair<int,int> >q,qp;
	int cnt=1;q.push(make_pair(1,1));vis[1][1][0]=1;
	while(cnt<n*n){
		if(q.empty())swap(q,qp);
		pair<int,int>p=q.front();q.pop();
		p.first--;
		if(p.first&&!vis[p.first][p.second][0]){
			cnt++;vis[p.first][p.second][0]=1;
			if(c[p.first][p.second]=='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][0]=val[p.first+1][p.second][0]+(c[p.first][p.second]!='R');
		}
		p.first+=2;
		if(p.first<=n&&!vis[p.first][p.second][0]){
			cnt++;vis[p.first][p.second][0]=1;
			if(c[p.first][p.second]=='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][0]=val[p.first-1][p.second][0]+(c[p.first][p.second]!='R');
		}
		p.first--;p.second--;
		if(p.second&&!vis[p.first][p.second][0]){
			cnt++;vis[p.first][p.second][0]=1;
			if(c[p.first][p.second]=='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][0]=val[p.first][p.second+1][0]+(c[p.first][p.second]!='R');
		}
		p.second+=2;
		if(p.second<=n&&!vis[p.first][p.second][0]){
			cnt++;vis[p.first][p.second][0]=1;
			if(c[p.first][p.second]=='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][0]=val[p.first][p.second-1][0]+(c[p.first][p.second]!='R');
		}
	}
	queue<pair<int,int> >q1,qp1;swap(q1,q);swap(qp1,qp);
	cnt=1;q.push(make_pair(1,n));vis[1][n][1]=1;
	while(cnt<n*n){
		if(q.empty())swap(q,qp);
		pair<int,int>p=q.front();q.pop();
		p.first--;
		if(p.first&&!vis[p.first][p.second][1]){
			cnt++;vis[p.first][p.second][1]=1;
			if(c[p.first][p.second]!='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][1]=val[p.first+1][p.second][1]+(c[p.first][p.second]=='R');
		}
		p.first+=2;
		if(p.first<=n&&!vis[p.first][p.second][1]){
			cnt++;vis[p.first][p.second][1]=1;
			if(c[p.first][p.second]!='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][1]=val[p.first-1][p.second][1]+(c[p.first][p.second]=='R');
		}
		p.first--;p.second--;
		if(p.second&&!vis[p.first][p.second][1]){
			cnt++;vis[p.first][p.second][1]=1;
			if(c[p.first][p.second]!='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][1]=val[p.first][p.second+1][1]+(c[p.first][p.second]=='R');
		}
		p.second+=2;
		if(p.second<=n&&!vis[p.first][p.second][1]){
			cnt++;vis[p.first][p.second][1]=1;
			if(c[p.first][p.second]!='R')q.push(p);
			else qp.push(p);
			val[p.first][p.second][1]=val[p.first][p.second-1][1]+(c[p.first][p.second]=='R');
		}
	}
	printf("%d",val[n][n][0]+val[n][1][1]);
	return 0;
}
```

---

## 作者：wyyqwq (赞：0)

即为求从 $(1,1)$ 走到 $(n,n)$ 经过的最少的蓝色的数量与从 $(1,n)$ 走到 $(n,1)$ 经过最少的红色的数量的和。对于这个，可以每个点向周围四个点连边，建图。总点数 $n^2$，总边数 $m = 4n^2$，可以通过。

[提交记录](https://atcoder.jp/contests/arc177/submissions/53431891)

---

## 作者：ma_niu_bi (赞：0)

### C - Routing

### 思路

广搜或最短路板子。

搜一遍或跑一遍，求出 $(1,1)$ 到 $(N,N)$ 最少经过多少蓝色，$(1,N)$ 到 $(N,1)$ 最少经过多少红色，相加即答案。这里给出最短路代码。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[505][505];
int n, b[505][505], r[505][505];
bool vis[505][505];
int xz[] = {1, 0, -1, 0};
int yz[] = {0, 1, 0, -1};
struct node {int x, y, d;};
bool operator < (node a, node b) {
    return a.d > b.d;
}
priority_queue <node> q;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) scanf("%s", s[i] + 1);
    memset(b, 0x3f, sizeof(b));
    memset(r, 0x3f, sizeof(r));
    b[1][1] = (s[1][1] == 'B');
    q.push({1, 1, b[1][1]});
    while (!q.empty()) {
        node now = q.top(); q.pop();
        if (vis[now.x][now.y]) continue;
        vis[now.x][now.y] = 1;
        if (now.x == n && now.y == n) continue;
        for (int i = 0; i < 4; i ++) {
            int xx = now.x + xz[i], yy = now.y + yz[i];
            if (xx < 1 || xx > n || yy < 1 || yy > n) continue;
            if (b[xx][yy] > now.d + (s[xx][yy] == 'B')) {
                b[xx][yy] = now.d + (s[xx][yy] == 'B');
                q.push({xx, yy, b[xx][yy]}); 
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    r[n][1] = (s[n][1] == 'R');
    q.push({n, 1, r[n][1]});
    while (!q.empty()) {
        node now = q.top(); q.pop();
        if (vis[now.x][now.y]) continue;
        vis[now.x][now.y] = 1;
        if (now.x == 1 && now.y == n) continue;
        for (int i = 0; i < 4; i ++) {
            int xx = now.x + xz[i], yy = now.y + yz[i];
            if (xx < 1 || xx > n || yy < 1 || yy > n) continue;
            if (r[xx][yy] > now.d + (s[xx][yy] == 'R')) {
                r[xx][yy] = now.d + (s[xx][yy] == 'R');
                q.push({xx, yy, r[xx][yy]}); 
            }
        }
    }
    printf("%d\n", b[n][n] + r[1][n]);
    return 0;
}
```

---

