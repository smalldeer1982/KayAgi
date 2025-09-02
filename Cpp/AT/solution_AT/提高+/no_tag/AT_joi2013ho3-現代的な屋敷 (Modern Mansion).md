# 現代的な屋敷 (Modern Mansion)

## 题目描述

有一座东西 $M$ 列南北 $N$ 行的大宅。

任何相邻的两间房之间都有一扇门连接，若一扇门是打开状态，则可以从门的一边走到另一边，并且花费 $1$ 分钟。

$K$ 个房间设有开关，按下开关会导致所有门的开关状态切换，并且花费 $1$ 分钟。

最开始连接东西相邻房间的所有门都关闭，连接南北相邻房间的所有门都打开，输出从房间 $(1,1)$ 移动到房间 $(M,N)$ 的最短时间。

## 说明/提示

样例 $1$ 解释：

从 $(1,1)$ 到 $(1,2)$，按下开关，然后到 $(2,2)$，最后到达 $(3,2)$，耗时 $4$ 分钟。可以证明不存在时间更短的方案。

![](https://img.atcoder.jp/joi2013ho/088a24305fc2470b9ff17a0cd60c556b.png)

样例 $2$ 解释：

容易证明只能到达 $(1,1)$ 或 $(1,2)$，因此不能到达 $(3,2)$。

样例 $3$ 图示：

![](https://img.atcoder.jp/joi2013ho/128c91a07269803fa720723600260cea.png)

对于 $20\%$ 的数据，$M,N\le10^3$。

对于另外 $30\%$ 的数据，$K\le2\times10^3$。

对于 $100\%$ 的数据，$M,N\le10^5, K\le2 \times 10^5$。

## 样例 #1

### 输入

```
3 2 1
1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2 1
2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
8 9 15
3 1
3 2
3 7
3 8
1 1
4 5
4 3
5 6
5 8
6 3
6 2
7 5
8 9
8 6
8 5```

### 输出

```
25```

# 题解

## 作者：Allan_Xu (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/AT_joi2013ho3)

我们读题时可以抓住关键词——**最短时间** ； 

我们可以很自然的联想到最短路（强调：**用迪杰斯特拉单源最短路**）；

但是，我们发现我们只能同时走 **行** 或 **列** ，直到走到所谓的 **“有开关的房间”**  ，所以很自然的想到将**行和列分为两层** ，分层图的思想，最短路跑分层图最短路，[JLOI2011 飞行路线](https://www.luogu.com.cn/problem/P4568)；

针对这道题，建边的时候，我们不能暴力的建边，那样的时间复杂度是 $O(n^2)$ 的，只能先 **排一下序** ，再进行建边，才能在 $O(n\log n+n)$ 的时间复杂度内建完边，还有，$x,y$ （行、列）都要建边；两层之间穿过的代价是一，所以给每个点两层之间建一条边权为 $1$ 的边，$(1,1),(m,n)$ 除外，他们两个是 $0$ 。（个人觉得建边是这道题的难点，细节有点多）

> 我考试的时候建边就写丑了，挂了，参考了一下其他大佬的代码，把建边调了一下，以前的不想调了（我绝对不会说是我调不出来了），丢在了洛谷讨论区；

*code*

```c++
#include <bits/stdc++.h>//万能头文件
using namespace std;
//#define SIZE (1<<20)
//char in[SIZE],out[SIZE],*p1=in,*p2=in,*p3=out;
//#define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,SIZE,stdin),p1==p2)?EOF:*p1++)
inline long long read(){//快读
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
#define int long long

const int N=4e6+5; 
struct edge{
	int to,next,value;
}e[N<<1];
int head[N],edge_cnt; 
inline void addedge(int u,int v,int w){
	e[++edge_cnt]=(edge){v,head[u],w};
	head[u]=edge_cnt;
}

struct rooms{
	int x,y;
	int id;
}a[N];
int n,m,k;
bool cmp1(rooms a,rooms b){
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
} 
bool cmp2(rooms a,rooms b){
	if(a.y!=b.y)return a.y<b.y;
	return a.x<b.x;
}

int dis[N],vis[N];
priority_queue<pair<int,int> >q;
void dij(int n){
	memset(dis,63,sizeof(dis)); 
//	memset(vis,0,sizeof(vis));
	q.push(make_pair(0,n));
	while(!q.empty()){
		int du=-q.top().first,u=q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;dis[u]=du;
		for(int i=head[u];i;i=e[i].next){
			q.push(make_pair(-du-e[i].value,e[i].to));
		}
	}
}
signed main(){
//	freopen("house.in","r",stdin);
//	freopen("house.out","w",stdout);
	
	m=read(),n=read(),k=read();
	for(int i=1;i<=k;i++){
		a[i].x=read(),a[i].y=read();
		a[i].id=i;
	}
	
	sort(a+1,a+1+k,cmp1);
	for(int i=1;i<=k;i++){
		if(a[i].x==1)addedge(0,a[i].id,a[i].y-1),addedge(a[i].id,0,a[i].y-1);
		if(a[i].x==a[i+1].x){
			addedge(a[i].id,a[i+1].id,a[i+1].y-a[i].y);
			addedge(a[i+1].id,a[i].id,a[i+1].y-a[i].y);
		}
		if(a[i].x==m){
			addedge(a[i].id,k+1,n-a[i].y);
			addedge(k+1,a[i].id,n-a[i].y);
		}
	}
	
	sort(a+1,a+1+k,cmp2);
	for(int i=1;i<=k;i++){
		if(a[i].y==a[i+1].y){
			addedge(a[i].id+k+2,a[i+1].id+k+2,a[i+1].x-a[i].x);
			addedge(a[i+1].id+k+2,a[i].id+k+2,a[i+1].x-a[i].x);
		}
		if(a[i].y==n){
			addedge(a[i].id+k+2,k+1+k+2,m-a[i].x);
			addedge(k+1+k+2,a[i].id+k+2,m-a[i].x);
		}
	}
	
	addedge(k+1,k+1+k+2,0);
	addedge(k+1+k+2,k+1,0);
	
	for(int i=1;i<=k;i++){
		addedge(i,i+k+2,1);
		addedge(i+k+2,i,1);
	}
	
	dij(0);
	
	if(dis[k+1]==4557430888798830399)cout << -1 << "\n";
	else cout << dis[k+1] << "\n"; 
	return 0;
}



```

---

## 作者：立柱已选162534 (赞：1)

## 题意

- 要在一个 $M$ 行 $N$ 列的矩阵中从 $(1,1)$ 走到 $(M,N)$ ，每走一步消耗 1 分钟，求最短时间。

- 但是，开始时只能上下走，有 $K$ 个点可以消耗 1 分钟让走的方式从上下走变为左右走，或从左右走变为上下走（就叫**关键点**好了）。

- 注意样例的图上下颠倒了。

## 思路

$M,N\leq 10^5$，显然不可能直接在网格上跑。

一开始考虑扫描线 DP，即一直试图往右走，更新到每个关键点的距离。

这种方法在样例是对的（左图），但是很容易被卡（右图）。
![](https://cdn.luogu.com.cn/upload/image_hosting/rn5r70eu.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/dsh44kd5.png)

鉴于每个点最多能往 4 个方向走，并且在非关键点上只能按一个方向走（相当于边），想到按照关键点（加上起点和终点）跑最短路。

做法如下：

- 将每个点拆成上下走与左右走两个点，对关键点在这两个点之间连一条距离为 1 的边（由于还要算起点与终点所以不能全连）。

- 按横纵坐标分别排序扫一遍找出在上下左右方向上离这个点最近的点与它们间的距离，连边。

- 跑堆优化的 dijkstra 即可。

## 注意点

- 在排序后扫描时要按原来的坐标存储结果（不然会乱）

- 实现时我选择把原来的点的编号与拆出来的点的状态合在一起（若原来的编号为 $x$，状态为 $p$ ，则新编号为 $2x+p$），方便塞进堆里。

- 别忘了最后输换行！（不知道第几次忘了）

## 代码

因为洛谷 Remotejudge 炸了所以直接交到了 AT 上。

[评测记录](https://atcoder.jp/contests/joi2013ho/submissions/47451865)

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[現代的な屋敷 (Modern Mansion)](https://www.luogu.com.cn/problem/AT_joi2013ho3)
## 分析
注意到 $K \le 2 \times 10^5$。直接考虑每行每列相邻的点建边，还好网络流学的好，建边不是很难。

建完边跑最短路就行了。

感觉蓝题高了，顶多就黄绿左右。
## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct nnode
{
	int nxt,to,w,f;
}edge[1600010];
int head[800010],tot;
void add(int x,int y,int z,int f)
{
	edge[++tot].nxt=head[x];
	edge[tot].to=y;
	edge[tot].w=z;
	edge[tot].f=f;
	head[x]=tot;
}
vector<int> a[100010][2];
int n,m,k;;
pair<int,int> dis[200010];
int vis[200010];
int s;
map<pair<int,int>,int>mp;
struct node{
	int dis;
	int pos;
	bool operator <(const node &x) const
	{
		return x.dis<dis;
	}
};
priority_queue<node> q;
void dij()
{
	for(int i=1;i<=k+1;i++)
	{
		dis[i].first=1e18;
	}
	q.push( ( node ) {0,s} );
	while(!q.empty())
	{
		node tmp=q.top();
		q.pop();
		int x=tmp.pos,d=tmp.dis;
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int y=edge[i].to;
			if(edge[i].w+dis[x].first+(dis[x].second!=edge[i].f)<dis[y].first)
			{
				dis[y].first=edge[i].w+dis[x].first+(dis[x].second!=edge[i].f);
				dis[y].second=edge[i].f;;
				if(!vis[y])
				q.push( ( node ) {dis[y].first,y});
			}
		}
	}
}
;signed main()
{
//	freopen("house.in","r",stdin);
//	freopen("house.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		mp[make_pair(x,y)]=i;
		a[x][0].push_back(y);
		a[y][1].push_back(x);
		if(x==1&&y==1)continue;
		if(x==1)
		{
			add(0,i,y-1,0);
			add(i,0,y-1,0);
		}
		else if(y==1)
		{
//			add(0,i,x-1,1);
			add(i,0,x-1,1);	
		}
		if(x==n&&y==m)continue;
		if(x==n)
		{
			add(k+1,i,m-y,0);
			add(i,k+1,m-y,0);			
		}
		if(y==m)
		{
			add(k+1,i,n-x,1);
			add(i,k+1,n-x,1);			
		}		
	}
	mp[make_pair(1,1)]=0;
	mp[make_pair(n,m)]=k+1;	
//	cout<<"check#1\n";
	for(int i=1;i<=n;i++)
	{	
		if(a[i][0].size()==0)continue;
		sort(a[i][0].begin(),a[i][0].end());
		for(int j=0;j<a[i][0].size()-1;j++)
		{
			int id1=mp[make_pair(i,a[i][0][j])];
			int id2=mp[make_pair(i,a[i][0][j+1])];
			int w=a[i][0][j+1]-a[i][0][j];
			add(id1,id2,w,0);
			add(id2,id1,w,0);
		}
	}
//	cout<<"check#2\n";
	for(int i=1;i<=m;i++)
	{
		if(a[i][1].size()==0)continue;
		sort(a[i][1].begin(),a[i][1].end());
		for(int j=0;j<a[i][1].size()-1;j++)
		{
			int id1=mp[make_pair(a[i][1][j],i)];
			int id2=mp[make_pair(a[i][1][j+1],i)];
			int w=a[i][1][j+1]-a[i][1][j];
			add(id1,id2,w,1);
			add(id2,id1,w,1);
		}	
	}	
//	cout<<"check";
	dij();
	if(dis[k+1].first==1e18)dis[k+1].first=-1;
	cout<<dis[k+1].first<<endl;
	return 0;;
}
```

---

## 作者：Cells (赞：0)

### 思路

考场上脑子抽了，以为建图空间是 $n^2$ 级别的，写炸了，无语了。



能够很明显的发现除非走到终点，走到其他没有开关的房间就是死路一条。所以建图只需要在这些开关房间之间来建。最短路 Dijkstrta 和 SPFA 虽然简单，但是建图不简单。



首先你需要了解一下分层图，其实分层图就是一种思想，拿这里举例子，对于同一个房间，它有南北开通和东西开通两种状态，并且这两种状态相互转换需要 $1$ 的代价，那么我们可以将一个房间变成两个房间，分别表示上述的状态。存图的话，因为有开关的房间有 $k$ 个，所以你只需要在原来的点的基础上加上 $k$ 就可以存下了。也就是自己建向自己的另一种状态，双向边，边权为 $1$。



另外，起点终点需要甩到序列里面，记得判重。然后因为同行同列需要建边，所以需要把同行同列甩进 `vector`，然后遍历，相邻的两个建边，边权是距离，建边还需要离散化，就是排序，二分查排名就完了。有同班神犇说不需要，我不知道怎么实现的，有兴趣自行了解。



那么大体思路有了，脑子里面胡一下，先建图，再跑最短路，最后记得输出空行，该开两倍的数组开两倍，秒了！

**Code**

```c++
# include <bits/stdc++.h>
# define int LL
# define fr front
# define sc scanf
# define pr printf
# define il inline
# define fir first
# define sec second
# define pb push_back
# define eb emplace_back
# define ls(x) (x << 1)
# define rs(x) (x << 1 | 1)
# define lson ls(p), l, mid
# define rson rs(p), mid + 1, r
# define mem(a, b) memset(a, b, sizeof (a))
# define debug(x) cerr << #x << "=" << x << ' '
# define rep(i, a, b) for(int i = a; i <= b; i ++)
# define pre(i, a, b) for(int i = a; i >= b; i --)
using namespace std;

using DB = double;
using LL = long long;
using LDB = long double;
using PII = pair<int, int>;
using ULL = unsigned long long;

const int N = 1e5 + 10, K = 2e5 + 10, E = 2e6 + 10;
const int INF = 1145141919810;

int n, m, k, idx;
int dis[K << 1], h[K << 1], e[E], w[E], ne[E];
bool vis[K << 1];

PII p[K];
vector<int> col[N], row[N];

int getid(PII x){//查排名离散化 
	return lower_bound(p + 1, p + 1 + k, x) - p;
}

void add(int a, int b, int c){//加边，记得是双向的 
	e[++ idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
	swap(a, b);
	e[++ idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

void dijkstra(){//最短路 
	priority_queue<PII, vector<PII>, greater<PII> > heap;
	rep(i, 1, k << 1) dis[i] = INF;
	mem(vis, false);
	
	dis[1 + k] = 0;//起点只能是这个，因为最开始连接东西相邻房间的所有门都关闭，连接南北相邻房间的所有门都打开
	heap.push({0, 1 + k});
	
	while(!heap.empty()){
		int u = heap.top().sec;
		heap.pop();
		
		if(vis[u]) continue;
		vis[u] = true;
		
		for(int i = h[u]; i; i = ne[i]){
			int v = e[i];
			if(vis[v] || dis[v] <= dis[u] + w[i]) continue;
			dis[v] = dis[u] + w[i];
			heap.push({dis[v], v});
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m >> k;
	bool flag1 = false, flag2 = false;
	rep(i, 1, k){
		cin >> p[i].fir >> p[i].sec;
		if(p[i].fir == 1 && p[i].sec == 1) flag1 = true;//判重标记 
		if(p[i].fir == n && p[i].sec == m) flag2 = true;
		row[p[i].fir].eb(p[i].sec);//行 
		col[p[i].sec].eb(p[i].fir);//列 
	}
	
	if(!flag1){//把起点和终点放进去 
		k ++;
		p[k].fir = 1;
		p[k].sec = 1;
		row[1].eb(1);
		col[1].eb(1);
	}
	
	if(!flag2){
		k ++;
		p[k].fir = n;
		p[k].sec = m;
		row[n].eb(m);
		col[m].eb(n);
	}
	
	sort(p + 1, p + 1 + k);//排序来离散化 
	
	rep(i, 1, k){
		if(i == 1 && !flag1) continue;
		if(i == k && !flag2) continue;
		int id = getid(p[i]);
		add(id, id + k, 1);
	}
	
	rep(y, 1, m){
		if(col[y].empty()) continue;
		sort(col[y].begin(), col[y].end());//先排序
		
		rep(x, 1, col[y].size() - 1){
			add(getid({col[y][x - 1], y}), getid({col[y][x], y}), col[y][x] - col[y][x - 1]);//同列建边 
		}
	}
	
	rep(x, 1, n){
		if(row[x].empty()) continue;
		sort(row[x].begin(), row[x].end());
		
		rep(y, 1, row[x].size() - 1){
			add(getid({x, row[x][y - 1]}) + k, getid({x, row[x][y]}) + k, row[x][y] - row[x][y - 1]);//同行建边 
		}
	}
	
	dijkstra();
	
	if(dis[k] == INF && dis[k << 1] == INF){//无解 
		cout << "-1\n";
		return 0;
	}
	
	cout << min(dis[k], dis[k << 1]) << "\n";//记得输出空行 
	
	return 0;
}
```

**感谢观看！！！我们下次再见！！！**

---

