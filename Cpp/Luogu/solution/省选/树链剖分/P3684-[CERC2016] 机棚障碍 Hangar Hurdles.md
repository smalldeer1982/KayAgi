# [CERC2016] 机棚障碍 Hangar Hurdles

## 题目描述

你正在评估一些关于一个巨型飞机仓库的建设计划。飞机仓库的地面可以表示为 $n$ 行 $n$ 列的网格图，其中每个格子要么是空的，要么有障碍物。行从上到下依次被编号为 $1$ 到 $n$，列从左到右依次被编号为 $1$ 到 $n$。

存放飞机零件的大型集装箱能在飞机仓库的地面上自由移动是很重要的。我们可以将每个集装箱看作一个以某个格子为中心的边平行于坐标轴的正方形。对于一个奇数 $k$，一个尺寸为 $k$ 的集装箱是一个包含 $k$ 行 $k$ 列的正方形。一个集装箱的坐标为其中心格子的坐标。集装箱可以向上下左右移动，但不能碰到障碍物，且不能移出仓库的边界。

给定 $q$ 对格子 $A_k$ 和 $B_k$，对于每对格子，请找到能从 $A_k$ 移动到 $B_k$ 的集装箱的最大尺寸，注意这个尺寸也要是一个奇数。

## 样例 #1

### 输入

```
7
.....#.
...#.#.
....#..
....###
....#..
#......
.......
5
2 5 5 2
2 5 3 6
2 2 6 3
2 2 6 6
1 1 7 7```

### 输出

```
1
0
3
1
1```

# 题解

## 作者：柳苏明 (赞：9)

[~~获得更差的阅读体验~~](https://ignotusjee.github.io/2020/09/13/SolutionOfHangarHurdles/)

并查集写成`Merge(e[i].v,e[i].v)`调了三天奥里给都给我调出来了。~~不过这都70分可见数据有多水~~

# 题意

给定一个$n\times n$的网格图，其中部分格点有障碍物使得箱子不能置于其上。规定箱子是一个奇数边长的正方形，其坐标为其中心格点的坐标。箱子只能上下左右移动，每次询问从一个格点能移动到另一个格点的最大箱子。

# 分析

此题看似简单，实则恶心的一匹。

* 我们先考虑将问题转化。如果求出每个格点能放置的最大箱子，设为格点权，那么每次询问就变成了求出两点路径上最小点权最大的路径。每次bfs，复杂度无法承受。
* 接着发现联通的点权相同的格点可以缩成一个点，因为在这个联通块内移动是不会改变经过的最小点权的。
* 于是在上下左右四个方向移动转化为了在相邻的联通块内移动。我们可以在相邻的联通块内连边，将边权设为两点点权的最小值，于是只要求出最大瓶颈路就可以了。
* 任意两点间的最大瓶颈路可以用如下算法求：将边降序排序，依次加入图中，两点第一次联通时其路径即为最大瓶颈路。正确性显然。
* 发现这就是Kruskal求最大生成树的过程，于是只要在生成树上查询路径最小值就可以了。

经过以上转化，此题解决（指口头）。

# 实现

实现才是这道题的重头戏。

## part1 求出MaxSize

* 首先设图中障碍为1，其余为0，对原图进行前缀和，以快速求出目标矩阵中有没有障碍物。

* 对每个格点进行二分，得到每个格点能放置的最大箱子设为MaxSize。其中因为边长只能为奇数，二分时是对中心点到边界的距离进行二分。

* 复杂度$O(n^2logn)$

  代码：

  ```cpp
  //第一部分：预处理出每个点的最大矩形
  namespace DealMatrix {
  	int sum[maxn][maxn];//前缀和，障碍为1
  	int maxsize[maxn][maxn];
  
  	inline char check(const int &i,const int &j,const int &s) {
  		if(i-s<1||j-s<1||i+s>n||j+s>n) return false;//大了
  		if(sum[i+s][j+s]-sum[i-s-1][j+s]-sum[i+s][j-s-1]+sum[i-s-1][j-s-1]) return 0x0;
  		return 0xff;
  	}
  	inline int getsize(const int &i,const int &j) {
  		int l=0,r=n/2,mid,ans=0;
  		while(l<=r) {
  			mid=(l+r)>>1;
  			if(!~check(i,j,mid)) ans=mid,l=mid+1;
  			else r=mid-1;
  		}
  		return ans*2+1;
  	}
  	void main() {
  		for(int i(1);i<=n;i++)
  			for(int j(1);j<=n;j++)
  				sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+(map[i][j]=='#');
  		for(int i(1);i<=n;i++)
  			for(int j(1);j<=n;j++) {
  				if(map[i][j]=='.')
  					maxsize[i][j]=getsize(i,j);
  				else maxsize[i][j]=-1;
  			}
  	}
  }
  ```

  ## part2 缩点并连边

* 将MaxSize相同的点缩在一起，可以使用bfs或者并查集。我这里使用的是bfs。
* 连边时设$u<v$，先加入要求生成树的图里。注意要判重，我这里使用的是`unordered_map`。
* 复杂度$O(n^2)$，将`unordered_map`的每次操作当成常数级别。

代码：

```cpp
namespace BuildGraph {
	int belong[maxn][maxn],cnt;//联通块编号
	const int dx[]={0,1,0,-1};
	const int dy[]={1,0,-1,0};

	using DealMatrix::maxsize;
	char vis[maxn][maxn];
	inline void Search(const int &i,const int &j,const int &col) {
		static std::queue< std::pair<int,int> > q;
		vis[i][j]=0xff;belong[i][j]=col;
		q.push(std::make_pair(i,j));
		while(!q.empty()) {
			int x=q.front().first;
			int y=q.front().second;
			q.pop();
			for(int k(0);k<4;k++) {
				int nx=x+dx[k],ny=y+dy[k];
				if(nx<1||ny<1||nx>n||ny>n||maxsize[nx][ny]!=maxsize[i][j]||!~vis[nx][ny])
					continue;
				vis[nx][ny]=0xff;
				belong[nx][ny]=col;
				q.push(std::make_pair(nx,ny));
			}
		}
	}

	void main() {
		static std::unordered_map< int,std::unordered_map<int,char> > s;
		for(int i(1);i<=n;i++)
			for(int j(1);j<=n;j++)
				if(~vis[i][j]&&~maxsize[i][j])
					Search(i,j,++cnt);
		for(int i(1);i<=n;i++)
			for(int j(1);j<=n;j++) {
				if(!~maxsize[i][j]) continue;
				for(int k(0);k<4;k++) {
					int x=i+dx[k],y=j+dy[k];
					int p=belong[i][j],q=belong[x][y];
					if(x<1||y<1||x>n||y>n||!q||p==q) continue;
					if(p>q) swap(p,q);
					if(!~s[p][q]) continue;
					s[p][q]=0xff;
					Graph_1::e[++Graph_1::m]=Graph_1::Edge(p,q,min(maxsize[i][j],maxsize[x][y]));
				}
			}
		N=cnt;
		Graph_1::Kruscal();
	}
}
```

## part3 求出最大生成树

这个没什么说的。并查集我使用的是路径压缩+按秩合并版本，复杂度最优。复杂度$O(m\alpha(n^2))$，其中$m$为边数。

代码：

```cpp
namespace Graph_1 {
	struct Edge {
		int u,v,w;
		Edge(const int &u,const int &v,const int &w)
			:u(u),v(v),w(w) {}
		Edge() {}
	}e[maxm<<2];
	int m;char InTree[maxm<<2];
	struct Compare {
		bool operator () (const Edge &a,const Edge &b) {
			return a.w<b.w;
		}
	}cmp;

	struct UnoinFindSet {
		int fa[maxm],rank[maxm];
		void Init() {
			for(int i(1);i<=N;i++) fa[i]=i,rank[i]=1;
		}
		int Find(const int &x) {
			return (x == fa[x]) ? x : (fa[x] = Find( fa[x] ));
		}
		inline void Merge(const int &u,const int &v) {
			int x(Find(u)),y(Find(v));
			if(x!=y) {
				if(rank[x]<rank[y]) fa[x]=y,rank[y]=max(rank[y],rank[x]+1);
				else fa[y]=x,rank[x]=max(rank[x],rank[y]+1);
			}
		}
		inline bool Same(const int &u,const int &v) {
			return Find(u)==Find(v);
		}
	}U;

	void Kruscal() {
		std::sort(e+1,e+1+m,cmp);
		U.Init();
		for(int i(1);i<=m;i++) {
			if(U.Same(e[i].u,e[i].v)) continue;
			U.Merge(e[i].u,e[i].v);
			InTree[i]=0xff;
		}
	}
}
```

## part4 树上快速查询

* 这里方法很多，可以倍增，树剖~~还有LCT~~。这里采用的是树剖+ST表。复杂度预处理$n^2logn$，每次查询$logn$。
* 注意求出的生成树可能是森林。
* 另外，因为前面把点权转化为边权，这里又把边权转化为点权处理，所以树剖询问时不能加上lca的贡献。

代码：

```cpp
// 第三部分树剖最小值，在最小生成树上查询瓶颈路。注意，可能是一个森林
namespace Tree {
	struct Edge {
		int v,next,w;
		Edge(const int &v,const int &next,const int &w)
			:v(v),next(next),w(w) {}
		Edge() {}
	}e[maxm<<1];
	int head[maxm],cnt;
	inline void AddEdge(const int &u,const int &v,const int &w) {
		e[++cnt]=Edge(v,head[u],w);
		head[u]=cnt;
	}

	int val[maxm];//边权转化为点权
	namespace STTable {
		int f[maxm][21],Log[maxm];
		void Init() {
			memset(f,0x3f,sizeof f);
			for(int i(0),w(1);w<=N;i++,w<<=1) Log[w]=i;
			for(int i(1);i<=N;i++) if(!Log[i]) Log[i]=Log[i-1];
			for(int i(1);i<=N;i++)
				f[i][0]=val[i];
			for(int j(1);j<21;j++)
				for(int i(1);i<=N;i++)
					if(1+(1<<j)-1<=N)
						f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
		inline int QueryMin(const int &l,const int &r) {
			if(l>r) return inf;
			int o(Log[r-l+1]);
			return min(f[l][o],f[r-(1<<o)+1][o]);
		}
	}

	int size[maxm],fa[maxm],son[maxm],w[maxm],depth[maxm],belong[maxm],Cnt_Tree;
	void dfs1(const int &u) {
		belong[u]=Cnt_Tree;
		size[u]=1;depth[u]=depth[fa[u]]+1;
		for(int i(head[u]);i;i=e[i].next) {
			const int &v=e[i].v;
			if(v==fa[u]) continue;
			fa[v]=u;
			dfs1(v);
			size[u]+=size[v];
			if(size[v]>size[son[u]]) son[u]=v,w[u]=e[i].w;
		}
	}
	int top[maxm],dfn[maxm],stamp;
	void dfs2(const int &u,const int &anc) {
		dfn[u]=++stamp;
		top[u]=anc;
		if(son[u]) dfs2(son[u],anc),val[dfn[son[u]]]=w[u];
		for(int i(head[u]);i;i=e[i].next) {
			const int &v=e[i].v;
			if(v==fa[u]||v==son[u]) continue;
			dfs2(v,v);val[dfn[v]]=e[i].w;
		}
	}

	inline int GetMin(int u,int v) {
		int ans=inf;
		while(top[u]!=top[v]) {
			if(depth[top[u]]<depth[top[v]]) swap(u,v);
			ans=min(ans,STTable::QueryMin(dfn[top[u]],dfn[u]));
			u=fa[top[u]];
		}
		if(depth[u]>depth[v]) swap(u,v);
		ans=min(ans,STTable::QueryMin(dfn[u]+1,dfn[v]));
		return ans;
	}

	void main() {
		for(int i(1);i<=Graph_1::m;i++)
			if(!~Graph_1::InTree[i]) {
				AddEdge(Graph_1::e[i].u,Graph_1::e[i].v,Graph_1::e[i].w);
				AddEdge(Graph_1::e[i].v,Graph_1::e[i].u,Graph_1::e[i].w);
			}
		for(int i(1);i<=N;i++)
			if(!dfn[i]) {
				Cnt_Tree++;
				dfs1(i);
				dfs2(i,i);
			}
		STTable::Init();
	}
}
```

## part5 处理询问

注意亿点细节。例如，不在一棵树上以及所询问的点就是障碍时，返回无解。

代码：

```cpp
inline int Query(const int &x1,const int &y1,const int &x2,const int &y2) {
	if(map[x1][y1]=='#'||map[x2][y2]=='#') return 0;
	int u=BuildGraph::belong[x1][y1],v=BuildGraph::belong[x2][y2];
	if(u==v) return DealMatrix::maxsize[x1][y1];
	if(Tree::belong[u]!=Tree::belong[v]) return 0;
	int ans=Tree::GetMin(u,v);
	if(ans==inf) return 0;
	return ans;
}
```



总复杂度$O((n^2+q)logn+m\alpha(n^2))$。可以将$m$看作是$n^2$级别，但实际远远要小。

至此，此题终于做完了。我的代码共354行，算得上是我打过的最长的代码了。~~还不是因为加了个七十多行的快速读写~~

---

## 作者：Loser_King (赞：8)

基础图论作业题。感觉难度不及黑？

可能是我之前写过这玩意或者现在的做法相对简单很多。

## 题意

给定一个长宽均为 $n$ 的黑白矩阵，你需要回答 $q$ 组询问：

给定起点坐标和终点坐标，你有一个初始中心在起点，边长为 $x$ 的正方形。在“存在一条从起点到终点的路径，使得正方形的中心在路径上移动时不碰到任何黑格子”的条件下，求出最大可能的奇整数 $x$。如果不存在，输出 $0$。

## 做法

感性理解有“路径上最宽的部分影响答案”，于是可以想到瓶颈路。

在这里给出一个复杂度较劣，但是相当好写的离线瓶颈路做法（基于 Kruskal，但是不需要用到 Kruskal 重构树相关知识）：

1. 将边按边权排序。

2. 维护 `set<int>s[N]`，对于每个询问 $x_i,y_i$，把询问编号 $i$ 插入对应的 `set` 中。

3. 按照边权顺序处理每一条边。对于一条边 $x\xleftrightarrow w y$，如果 $x,y$ 不在一个连通块内，启发式合并两个集合 $s_x,s_y$。如果 $s_x,s_y$ 中有相同元素，将两个元素同时删除，并标记该元素对应询问答案为 $w$。最后合并 $x,y$ 所在连通块。

时间复杂度 $O(q\log m\log q)$，$m$ 为边数，$q$ 为询问数。复杂度瓶颈为启发式合并和 `set` 的 `insert` 操作。

回到这个问题。首先用朴素的 DP 求出一个坐标可以拓展的最大正方形的边长 $w_{i,j}$。（左上，右上，左下，右下直接 DP，然后合并）然后套用上面的方法，将所有点按照 $w$ 降序排序，然后依次如上处理，向四个方向合并即可。

时间复杂度 $O(q\log n^2\log q)$，较题解区的 $O(n^2\log n^2)$ 劣。但是因为本题中 $q<n^2$ 且开了 4s，所以实际上跑起来也不会超时，但是好像卡到时限了。

## 代码

变量和上面数组对应。

没有刻意缩减代码，代码比题解代码短不少（很多重复），且保留了可读性。

```c++
//P3684 AC Code
//written by Loser_King(159686)
//C++14 (GCC 9) | 1.94KB | 7.93s | 112.96MB
#include<bits/stdc++.h>
#define ord(x,y) (((x)-1)*n+(y))
#define getx(k) (((k)-1)/n+1)
#define gety(k) (((k)-1)%n+1)
using namespace std;
int const N=1010,K=N*N,dx[]={-1,0,0,1},dy[]={0,-1,1,0};
int n,q,w[N][N],ul[N][N],ur[N][N],dl[N][N],dr[N][N],f[K],ans[K];
char a[N][N];
set<int>s[K];
pair<int,int>p[K];
int find(int x){
	return x^f[x]?f[x]=find(f[x]):x;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n*n;i++)
		f[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]=='.')
				ul[i][j]=min(ul[i-1][j-1],
					min(ul[i][j-1],ul[i-1][j]))+1;
	for(int i=1;i<=n;i++)
		for(int j=n;j>=1;j--)
			if(a[i][j]=='.')
				ur[i][j]=min(ur[i-1][j+1],
					min(ur[i-1][j],ur[i][j+1]))+1;
	for(int i=n;i>=1;i--)
		for(int j=1;j<=n;j++)
			if(a[i][j]=='.')
				dl[i][j]=min(dl[i+1][j-1],
					min(dl[i+1][j],dl[i][j-1]))+1;
	for(int i=n;i>=1;i--)
		for(int j=n;j>=1;j--)
			if(a[i][j]=='.')
				dr[i][j]=min(dr[i+1][j+1],
					min(dr[i+1][j],dr[i][j+1]))+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			p[ord(i,j)]={w[i][j]=min(ul[i][j],min(ur[i][j],
				min(dl[i][j],dr[i][j])))*2-1,ord(i,j)};
	sort(p+1,p+1+n*n,greater<pair<int,int> >());
	cin>>q;
	for(int i=1;i<=q;i++){
		int ax,ay,bx,by;
		cin>>ax>>ay>>bx>>by;
		s[ord(ax,ay)].insert(i);
		s[ord(bx,by)].insert(i);
	}
	for(int i=1;i<=n*n;i++){
		int x=getx(p[i].second),y=gety(p[i].second),
			fa=find(p[i].second),k=p[i].first;
		if(a[x][y]=='#')
			continue;
		for(int j=0;j<4;j++){
			int tx=x+dx[j],ty=y+dy[j],tfa=find(ord(tx,ty));
			if(tx<1||ty<1||tx>n||ty>n||w[tx][ty]<w[x][y]||fa==tfa)
				continue;
			int fx=fa,fy=tfa;
			if(s[fx].size()>s[fy].size())
				swap(fx,fy);
			f[fx]=fa=fy;
			for(int w:s[fx])
				if(s[fy].count(w))
					ans[w]=k,s[fy].erase(w);
				else
					s[fy].insert(w);
			s[fx].clear();
		}
	}
	for(int i=1;i<=q;i++)
		cout<<ans[i]<<"\n";
}
```

---

## 作者：zhengrunzhe (赞：5)

最开始的思路借鉴了一下原题解 后续的算法是我自己瞎搞的

前缀和+二分+缩点+kruskal重构树+树剖lca

先常规操作把#转化成1，.转化成0

然后n²统计每个点自身能往外拓展的最大正方形边长记作mx[][]

如果强行枚举每个点的mx的话复杂度明显超出

考虑前缀和优化，把原来的01数组算出个前缀和数组，就可以算出一个正方形区域和了，二分正方形边长，check条件是如果覆盖的区域和是否为0，即无阻挡

把mx相同的连通块缩成一个点，我用tarjan求强连通分量实现的，用并查集也行，每个块我赋予个权值就是该块的点的mx值

在原图中把相邻的快用无向带权边连起来，边权为两个块权值的最小值，代表从A块走到B块最大边长只能为这个边权    建边的时候不能重复建，开个set判重就好了

询问问两个点间能走的最大正方形边长，就转化为了该两点所在的块间的最小边权最大为多少  求多条路径中最小边权的最大值，便考虑到使用kruskal重构树

类似P1967货车运输，kruskal跑一边最大生成树，一开始所有的块点(缩点后的点编号)形成一片森林，森林中每棵树只有根节点且根节点为块点，把树边从大到小操作：新建一个点，点权为边权，往该边所连结的两个块点所在树的根节点分别往新点连边

这样便重构出了一棵树，两点所在的块就可以对应到树点上，两树点的lca的权值便是答案

```cpp
#include<set>
#include<stack>
#include<cstdio>
#include<algorithm>
#define mp make_pair
using namespace std;
const int N=1e3+10,S=2e6+10;
int n,q;
bool map[N][N];
int sum[N][N],mx[S];
short fx[4]={-1,1,0,0},fy[4]={0,0,-1,1}; //方向数组
inline const int id(int x,int y) //二维坐标转一维编号
{
	return (x-1)*n+y;
}
inline const bool exist(int x,int y) //判断是否越界
{
	return x>=1&x<=n&&y>=1&&y<=n;
}
inline const bool check(int x1,int y1,int x2,int y2)
{
	return !(sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1])&&exist(x1,y1)&&exist(x2,y2);
}
inline const void getsum() //获取前缀和数组
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+map[i][j];
}
inline const void getmax()  //统计mx数组
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (!map[i][j])
			{
				int l=0,r=n>>1,p;
				while (l<r)
				{
					int mid=l+r>>1;
					if (check(i-mid,j-mid,i+mid,j+mid))l=(p=mid)+1;
					else r=mid;
				}
				mx[id(i,j)]=(p<<1)+1;
			}
}
class Graph
{
	private:
		int cnt;
		struct edge{int to,w,next;};
	public:
	int head[S<<1];
	edge e[S<<2];
	inline const void addedge(int u,int v,int w=0)
	{
		cnt++;e[cnt]=(edge){v,w,head[u]};
		head[u]=cnt;
	}
	inline const void connect(int u,int v,int w=0)
	{
		addedge(u,v,w);
		addedge(v,u,w);
	}
}g,t;
inline const void build() //把所有点与其相邻的同mx的点连接，便于接下来的缩点
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int nx,ny,k=0;k<4;k++)
				if (exist(nx=i+fx[k],ny=j+fy[k])&&mx[id(i,j)]==mx[id(nx,ny)])
					g.addedge(id(i,j),id(nx,ny));
}
stack<int>s;
int scc[S],low[S],dfn[S],w[S<<1],cnt,tot;
inline const void tarjan(int u)
{
	int v;s.push(u);low[u]=dfn[u]=++cnt;
	for (int i=g.head[u];i;i=g.e[i].next)
		if (!dfn[v=g.e[i].to])tarjan(v),low[u]=min(low[u],low[v]);
		else if (!scc[v])low[u]=min(low[u],low[v]);
	if (low[u]!=dfn[u])return;w[++tot]=mx[u];
	do v=s.top(),s.pop(),scc[v]=tot;while (u!=v);
}
inline const void tarjan()
{
	for (int i=1;i<=n*n;i++)
		if (!dfn[i])
			tarjan(i);
}
struct edge
{
	int x,y,w;
	inline const bool operator<(const edge &e)const
	{
		return w>e.w; //最大生成树
	}
}e[S<<2];
set<pair<int,int> >st;
inline const void addedge(int x,int y,int w)
{
	cnt++;e[cnt]=(edge){x,y,w};
}
inline const void rebuild() //缩点并建出新图
{
	cnt=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int u,v,k=0;k<4;k++)
				if (exist(i+fx[k],j+fy[k])&&(u=scc[id(i,j)])!=(v=scc[id(i+fx[k],j+fy[k])])&&st.find(mp(u,v))==st.end()) //判重
					addedge(u,v,min(w[u],w[v])),st.insert(mp(u,v)),st.insert(mp(v,u));//无向图，两个方向都要塞进set
}
class Union_Find_Set //并查集
{
	protected:
		int fa[S<<1];
	public:
		inline const void Init()
		{
			for (int i=1;i<tot<<1;i++)fa[i]=i;
		}
		inline const int Find(int x)
		{
			return fa[x]==x?x:fa[x]=Find(fa[x]);
		}
		inline const void Union(int x,int y)
		{
			int fx=Find(x),fy=Find(y);
			if (fx==fy)return;
			fa[fx]=fy;
		}
}ufs;
int chosen[S],lst;
inline const void kruskal()
{
	ufs.Init();
	sort(e+1,e+cnt+1);
	for (int i=1;i<=cnt;i++)
		if (ufs.Find(e[i].x)!=ufs.Find(e[i].y))
			ufs.Union(e[i].x,e[i].y),chosen[++lst]=i;
}
inline const void rebuildtree()//重构树
{
	ufs.Init();
	for (int x,y,i=1;i<=lst;i++)
		x=ufs.Find(e[chosen[i]].x),y=ufs.Find(e[chosen[i]].y),
		t.connect(x,tot+i),t.connect(y,tot+i),w[tot+i]=e[chosen[i]].w,
		ufs.Union(x,tot+i),ufs.Union(y,tot+i);
}
int size[S<<1],top[S<<1],dep[S<<1],fa[S<<1],wson[S<<1];
inline const void dfs(int p)
{
	size[p]=1;
	for (int i=t.head[p];i;i=t.e[i].next)
	{
		int son=t.e[i].to;
		if (son==fa[p])continue;
		fa[son]=p;dep[son]=dep[p]+1;
		dfs(son);size[p]+=size[son];
		if (size[son]>size[wson[p]])wson[p]=son;
	}
}
inline const void dfs(int p,int tp)
{
	top[p]=tp;
	if (wson[p])dfs(wson[p],tp);
	for (int son,i=t.head[p];i;i=t.e[i].next)
		if ((son=t.e[i].to)!=fa[p]&&son!=wson[p])
			dfs(son,son);
}
inline const int lca(int a,int b)
{
	while (top[a]^top[b])
		dep[top[a]]>dep[top[b]]
		?a=fa[top[a]]:b=fa[top[b]];
	return dep[a]<dep[b]?a:b;
}
int main()
{
	scanf("%d",&n);char c;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf(" %c",&c),map[i][j]=c=='#';
	getsum();getmax();
	build();tarjan();rebuild();
	kruskal();rebuildtree();
	dfs(tot+lst);dfs(tot+lst,tot+lst); //有多少条树边就会有多少个点，而最小的那条树边必定产生最上方的点，所以根节点编号是原块数+最大生成树边数
	scanf("%d",&q);
	int x1,y1,x2,y2;
	while (q--)
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2),
		printf("%d\n",w[lca(scc[id(x1,y1)],scc[id(x2,y2)])]);
	return 0;
}
```

---

## 作者：Forever1507 (赞：3)

大杂烩好题 ~~(bushi~~

首先，每个格子为中心的正方形的最大边长可以提前二位前缀和出井号的数量然后二分求出。

然后因为要是最小答案最大，这里排除二分（反正这个 check 我除了 bfs 就不会了）后可以考虑**最大生成树**以实现**最大**的目的。至于建边，就是一个点向上下左右不是障碍物的建边了，边权应当是两个点的最大边长（点 $i$ 的最大正方形边长记为 $d_i$）。

注意一点，这个生成树可能是森林，要分别 LCA。

树上求简单路径我选择**倍增**，具体就是在 LCA 里面多维护一个 `dis[i][j]` 表示 点 $i$ 向上走 $2^j$ 步能够取到的**最小边长**。

初始值显然就是 `dp[cur][0]=min(d[cur],d[fa/*父亲节点*/])`，在 LCA 的时候一起维护即可。

码量较大，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char mp[1005][1005];
int sum[1005][1005],d[1005][1005];
int q;
bool check(int x,int y,int r){
	if(r>=x||r>=y||r+x>n||r+y>n)return 0;
	if(sum[x+r][y+r]-sum[x-r-1][y+r]-sum[x+r][y-r-1]+sum[x-r-1][y-r-1]>=1)return 0;
//	cout<<"Check: "<<x<<' '<<y<<' '<<r<<'\n';
	return 1;
}
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int tot;
int calc(int x,int y){
	return (x-1)*n+y;
}
int X(int x){
	return (x-1)/n+1;
}
int Y(int x){
	return (x%n==0)?n:x%n;
}//以上三个函数实现了坐标与编号的互换 
struct node{
	int u,v,w;
}e[4000005];
int fa[1000005];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void unionn(int x,int y){
	int a=find(x),b=find(y);
	if(a!=b)fa[a]=b;
	return;
}
bool cmp(node a,node b){
	return a.w>b.w;
}
int _d[1000005],dp[1000005][21],dis[1000005][21];
vector<node>nbr[1000005];
void before(int cur,int fa){
	_d[cur]=_d[fa]+1;
	dp[cur][0]=fa;
	dis[cur][0]=min(d[X(cur)][Y(cur)],d[X(fa)][Y(fa)]); 
	for(int i=1;i<=20;++i)dp[cur][i]=dp[dp[cur][i-1]][i-1],dis[cur][i]=min(dis[cur][i-1],dis[dp[cur][i-1]][i-1]);
	for(int i=0;i<nbr[cur].size();++i){
		node to=nbr[cur][i];
		if(fa==to.v)continue;
//		dis[to.v][0]=to.w;
		before(to.v,cur);
	}
	return;
}
int LCA(int u,int v){
	int lens=d[X(u)][Y(u)],_lens=d[X(v)][Y(v)];
	if(_d[u]>_d[v])swap(u,v);
	for(int i=20;i>=0;i--){
		if((1<<i)<=_d[v]-_d[u])_lens=min(_lens,dis[v][i]),v=dp[v][i];
	}
	if(u==v)return min(lens,_lens);
	for(int i=20;i>=0;i--){
		if(dp[u][i]!=dp[v][i]){
			lens=min(lens,dis[u][i]);
			_lens=min(_lens,dis[v][i]);//一定要先维护距离，不然u/v的值就改了 
			u=dp[u][i];
			v=dp[v][i];
		}
	}
	return min(lens,_lens);
}
void MST(){
	for(int i=1;i<=n*n;++i)fa[i]=i;
	sort(e+1,e+tot+1,cmp);
	for(int i=1;i<=tot;++i){
		int x=e[i].u,y=e[i].v;
		if(find(x)==find(y))continue;
		nbr[x].push_back({x,y,e[i].w});
		nbr[y].push_back({y,x,e[i].w});
// 		cout<<"W: "<<x<<' '<<y<<' '<<X(x)<<' '<<Y(x)<<' '<<X(y)<<' '<<Y(y)<<' '<<e[i].w<<'\n';
//		cout<<x<<' '
		unionn(x,y);
	}
	return;
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cin>>mp[i][j];
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
			if(mp[i][j]=='#')sum[i][j]++;		
			//二位前缀和 
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int lt=-1,rt=n/2;
			while(lt+1<rt){
				int mid=lt+rt>>1;
				if(check(i,j,mid))lt=mid;
				else rt=mid;
			}
			d[i][j]=2*lt+1;//懒得保证奇数了，只二分一半的距离 
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=0;k<=3;++k){
				int x=i+dx[k],y=j+dy[k];
				if(x>=1&&y>=1&&x<=n&&y<=n&&mp[x][y]=='.'&&mp[i][j]=='.'){
					e[++tot]={calc(i,j),calc(x,y),min(d[i][j],d[x][y])};
				}
			}
		}
	}
	MST();
	for(int i=1;i<=n*n;++i)if(!_d[i]&&mp[X(i)][Y(i)]=='.')before(i,0);//可能是森林！ 
	cin>>q;
	for(int i=1;i<=q;++i){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		if(find(calc(x1,y1))!=find(calc(x2,y2))){
			cout<<0<<'\n';//可能不连通，判无解 
			continue;
		}
		cout<<LCA(calc(x1,y1),calc(x2,y2))<<'\n';
	}
	return 0;
}

```


---

## 作者：acranker (赞：3)

这是我写过的代码最长的题，289行！

他考了图论+数据结构大串烧！

大概用了前缀和，二分答案，并查集，hash，bfs，二叉堆（优先队列），树链剖分，st表。

以下均为对样例的说明

初始样例：

![](https://cdn.luogu.com.cn/upload/pic/21691.png)
- 前缀和：将#处理为1，其余处理为0。O（n^2）

![](https://cdn.luogu.com.cn/upload/pic/21692.png)
- 二分答案：处理出在任意一个点可以存在的最大的箱子的边长，因为f(x)={1,1,1,1,...,1,0,0,...0}，具有可二分性，避免500次的暴力判断，这样只要判断log（2，500）~=9次；O（9*n^2）

最大边长:

![](https://cdn.luogu.com.cn/upload/pic/21693.png)

- 缩点：上图中我们发现，很多1、3是连在一起的，所以可以用并查集将这些联通的相同的书变成一个点（因为题目不问怎么走，所以联通的相同的数其实是一样的）。O（n^2）

   其实dfs和bfs也可以，但是我感觉并查集最快，他只要用两层循环判断每个点上面和左边即可，而搜索必须要判断四个方向。

- 建图：（本文中，将缩点之后的联通的相同数字称为块），缩点之后，块与块是否相邻是不能判断的，只能在原图中判断，但在原图中重复判断很多（比如上图中第二行第二列的3和第三行第二列的3会重复），所以需要判重（这里我用了hash，STL的map也可以，但是有点慢）。O（n^2）

   缩点之后，预计点数最多10^4数量级，边数最多10^6数量级（因为联通的变成一块，所以图不会很密集）

   图中已经可以处理了，我们可以用dijkstra对于每次询问查询最短路（类似于最短路，就是起点到终点路径上最小点权的最大值），但一看300000的询问数量，有点慌，看看有没有更优秀的做法

![](https://cdn.luogu.com.cn/upload/pic/21700.png)

- 建树：如上图（画图画的，有点丑），我们可以贪心，因为在图中很多边是不会被走到的，比如2到5当然不会从1走，而会从3走，我们只要在bfs的时候每次选队列中最大的那个继续扩展即可（正确性就不证明了）。O（10^4*log（10^4））

- st表+树链剖分：都有树了，查询路径上的最小值怎么做？树链剖分啊！这里不用线段树是因为q=300000，你说qlog（10^4）^2优秀还是10^4*log（10^4）+qlog（10^4）优秀？

  标准的口头AC五分钟，写写两小时的题，太恶心了，做法上这应该是时间复杂度最低的了吧，不知道有没有好写一点的做法，不得不说，算法套算法的数组套用很麻烦的。
  
  AC代码：
  
```cpp
#include <bits/stdc++.h>
const int N=1000050;
const int _N=1050;
int n,c=0;
int a[_N][_N],sum[_N][_N],b[_N][_N];
bool vis[N];
int first[N],dext[N<<1],d[N<<1],cnt_edge=0;
int root[N];
namespace Init
{
	inline int check(int i,int j,int mid)
	{
		return sum[i+mid][j+mid]-sum[i-mid-1][j+mid]-sum[i+mid][j-mid-1]+sum[i-mid-1][j-mid-1];
	}
	inline void work()
	{
		scanf("%d",&n);
		for(int i=0;i<=n;i++) sum[0][i]=sum[i][0]=0;
		for(int i=1;i<=n;i++)
		{
			while(c!=10) c=getchar();
			for(int j=1;j<=n;j++)
			{
				c=getchar();a[i][j]=(c=='#');//前缀和
				sum[i][j]=a[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(a[i][j]) a[i][j]=0;
				else
				{
					int l=0,r=std::min(std::min(i-1,j-1),std::min(n-i,n-j)),ans=0;//r控制范围
					while(l<=r)//二分答案
					{
						int mid=(l+r)>>1;
						if(check(i,j,mid)) r=mid-1;
						else ans=mid,l=mid+1;
					}
					a[i][j]=ans<<1|1;
				}
	}
}
namespace Hash//hash+链式前向星判重
{
	const int N=5000000;
	const int MOD=1000003;
	struct node{int x,y;}d[N];
	int first[::N],dext[N],cnt=0;
	inline void init()
	{
		memset(first,0,sizeof(first));
		dext[0]=0;
	}
	inline bool add(int x,int y)
	{
		if(x>y) std::swap(x,y);
		int z=((long long)x*n+y)%MOD;
		for(int i=first[z];i;i=dext[i])
			if(d[i].x==x&&d[i].y==d[i].y) return false;
		dext[++cnt]=first[z],first[z]=cnt,d[cnt]=node{x,y};
		return true;
	}
}
namespace Graph//建图
{
	const int N=5000000;
	int f[::N],vis[::N],max[::N],maxr[::N],num[::N],cnt=0;
	int first[::N],dext[N<<1],d[N<<1],cnt_edge=0;
	inline void init(int n)
	{
		for(int i=1;i<=n;i++) f[i]=i;
	}
	inline int find(int x)
	{
		if(f[x]==x) return x;
		return f[x]=find(f[x]);
	}
	inline void unity(int x,int y){f[find(x)]=f[find(y)];}
	inline void add(int x,int y)
	{
		dext[++cnt_edge]=first[x],first[x]=cnt_edge,d[cnt_edge]=y;
	}
	inline void work()
	{
		//并查集缩点
		init(n*n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(a[i][j])
				{
					int x=(i-1)*n+j;//不加j-1是要把0空出来，vis中用0判是否已访问，在链式前向星中用0判结束
					if(i!=1&&a[i-1][j]==a[i][j])
					{
						int y=(i-2)*n+j;
						unity(x,y);
					}
					if(j!=1&&a[i][j-1]==a[i][j])
					{
						int y=(i-1)*n+j-1;
						unity(x,y);
					}
				}
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(a[i][j])
				{
					int x=(i-1)*n+j;
					b[i][j]=vis[find(x)]?vis[f[x]]:(num[++cnt]=a[i][j],vis[f[x]]=cnt);
				}
				else b[i][j]=0;
		Hash::init();
		init(cnt);
		//这里的add连边，再次使用并查集判断联通块（能联通就行，数字可以不同，用来判断无法到达（输出为0）的情况）
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(a[i][j])
				{
					if(i!=1&&b[i-1][j]&&b[i-1][j]!=b[i][j])
						if(Hash::add(b[i][j],b[i-1][j]))
							add(b[i][j],b[i-1][j]),add(b[i-1][j],b[i][j]),unity(b[i][j],b[i-1][j]);
					if(j!=1&&b[i][j-1]&&b[i][j-1]!=b[i][j])
						if(Hash::add(b[i][j],b[i][j-1]))
							add(b[i][j],b[i][j-1]),add(b[i][j-1],b[i][j]),unity(b[i][j],b[i][j-1]);
				}
		n=cnt;cnt=0;
		for(int i=1;i<=n;i++) cnt=std::max(cnt,f[i]);
		for(int i=1;i<=n;i++) max[i]=0;
		for(int i=1;i<=n;i++)
			if(max[f[i]]<num[i])
			{
				max[f[i]]=num[i];
				maxr[f[i]]=i;//找到每一个联通块中最大的，为bfs建树做准备
			}
	}
}
namespace Tree
{
	#define lch (id<<1)
	#define rch (id<<1|1)
	#define tx term.x
	#define ty term.y
	#define tp term.pre
	struct node
	{
		int x,y,pre;//pre记录由哪个点扩展来的，方便连边
		bool operator>(const node& b)const{return y>b.y;}
	}h[N];
	int hsize=0;//二叉堆（优先队列）
	inline void insert(node val)
	{
	    h[++hsize]=val;
	    int id=hsize;
	    while(id)
	    {
	        if(lch==hsize&&h[lch]>h[id]) std::swap(h[lch],h[id]);
	        else if(lch<hsize&&(h[lch]>h[id]||h[rch]>h[id]))
	        {
	            if(h[lch]>h[rch]) std::swap(h[lch],h[id]);
	            else std::swap(h[rch],h[id]);
	        }
	        id>>=1;
	    }
	}
	inline node del()
	{
	    node ans=h[1];
	    std::swap(h[1],h[hsize--]);
	    int id=1;
	    while(lch<=hsize)
	    {
	        if(lch==hsize&&h[lch]>h[id]) std::swap(h[lch],h[id]),id=lch;
	        else if(lch<hsize&&(h[lch]>h[id]||h[rch]>h[id]))
	        {
	            if(h[lch]>h[rch]) std::swap(h[lch],h[id]),id=lch;
	            else std::swap(h[rch],h[id]),id=rch;
	        }
	        else break;
	    }
	    return ans;
	}
	//树的连边
	inline void add(int x,int y)
	{
		dext[++cnt_edge]=first[x],first[x]=cnt_edge,d[cnt_edge]=y;
	}
	inline void bfs(int x)
	{
		hsize=0;
		root[x]=Graph::maxr[x];
		insert(node{Graph::maxr[x],Graph::max[x],0});
		vis[Graph::maxr[x]]=true;
		while(hsize)
		{
			node term;
			term=del();
			if(tp) add(tx,tp),add(tp,tx);
			for(int i=Graph::first[tx];i;i=Graph::dext[i])
			{
				int v=Graph::d[i];
				if(vis[v]) continue;
				vis[v]=true;
				insert(node{v,Graph::num[v],tx});
			}
		}
	}
	inline void work()
	{
		memset(first,0,sizeof(first));
		memset(vis,false,sizeof(vis));
		dext[0]=0;
		for(int i=1;i<=Graph::cnt;i++) bfs(i);
	}
}
namespace Final//终于要结束了qwq
{
	const int INF=1<<30;
	int wson[N],deep[N],size[N],f[N],top[N],r[N],rr[N],cnt=0;
	int st[N][20],len[N];//st表
	int q,r1,c1,r2,c2;
	inline int query(int l,int r)
	{
	    int k=len[r-l+1];
	    return std::min(st[l][k],st[r-(1<<k)+1][k]);
	}
	inline void dfs(int x,int fa,int dep)
	{
	    deep[x]=dep,f[x]=fa,size[x]=1;
	    for(int i=first[x];i;i=dext[i])
	        if(d[i]!=fa)
	        {
	            dfs(d[i],x,dep+1);
	            size[x]+=size[d[i]];
	            if(size[d[i]]>size[wson[x]])
	                wson[x]=d[i];
	        }
	}
	inline void dfs2(int x,int pre)
	{
	    top[x]=pre,r[x]=++cnt,rr[cnt]=x;
	    if(wson[x]) dfs2(wson[x],pre);
	    for(int i=first[x];i;i=dext[i])
	        if(d[i]!=f[x]&&d[i]!=wson[x])
	            dfs2(d[i],d[i]);
	}
	//树链剖分
	inline int seek(int x,int y)
	{
		//x==0或y==0表示其中一个点是障碍物，f[x]不同表示不再一个联通块
	    if(x==0||y==0||Graph::f[x]!=Graph::f[y]) return 0;
	    int t1=top[x],t2=top[y],ans=INF;
	    while(t1!=t2)
	    {
	        if(deep[t1]<deep[t2])
	            std::swap(t1,t2),std::swap(x,y);
	        ans=std::min(ans,query(r[t1],r[x]));
	        x=f[t1],t1=top[x];
	    }
	    if(deep[x]>deep[y]) std::swap(x,y);
	    ans=std::min(ans,query(r[x],r[y]));
	    return ans;
	}
	inline void work()
	{
		//树链剖分预处理
		memset(wson,0,sizeof(wson));
		size[0]=0;
		for(int i=1;i<=Graph::cnt;i++)
		{
			dfs(root[i],root[i],1);
			dfs2(root[i],root[i]);
		}
		//st表预处理
	    for(int i=1;i<=cnt;i++) st[i][0]=Graph::num[rr[i]];
	    for(int j=1;1<<j<=cnt;j++)
	        for(int i=1;i+(1<<j)-1<=cnt;i++)
	            st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
	    len[1]=0;
	    for(int i=2;i<=cnt;i++) len[i]=len[i-1]+((i&-i)==i);
	    //真正的回答问题刚刚开始，前面都是预处理
	    scanf("%d",&q);
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
			printf("%d\n",seek(b[r1][c1],b[r2][c2]));
		}
	}
}
int main()
{
	Init::work();
	Graph::work();
	Tree::work();
	Final::work();
	return 0;
}
```


---

## 作者：ImmortalWatcher (赞：2)

**solution**

如果我们求出了每个点能容纳的最大集装箱大小 $d$，那么实际上本题要求的就是所有起点到终点的路径上边的权值最小值的最大值。

容易想到 $\text{Kruskal}$ 重构树，将每个点与四周连边，然后建树，跑倍增求 $\text{LCA}$ 点权即可。

$d$ 可以二分加二维前缀和求，可以在 $O(n^2\log n)$ 完成。

但是我们发现每个点都连边实在太多了，存不下。考虑观察性质，我们发现，如果在 $d$ 相同的点之间移动，是不会对最终答案造成影响的，所以我们完全可以把相邻的 $d$ 相同的点合并起来，再连边，这样边数就少的多。合并的过程可以采用 $\text{BFS}$ 在 $O(n^2)$ 内完成。关于去重，可以使用 $\text{unordered\_map}$，可以认为它是常数级别的。

在实现细节方面，我们注意到，由于障碍的存在，所以可能最后得到的是森林而不是一棵树。考虑到树与树之间是不连通的，所以我们完全可以新建一个节点连向这些树，并把点权设为 $0$，就可以直接按照普通一棵树的情况来做了。

在实现的时候，分步调试，也就是每写一个架构就测试一下这个架构是不是对的，这样可以让最后调试的时候轻松很多。个人写完加调完只用了 1 个小时左右，一遍过，总之不是很难写，但是码量确实有点长，相信各位可以有耐心完成这道题，是一道不错的思维难度适中的，练习码力的题目。

**code**

```cpp
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<queue>
using namespace std;
struct Hash
{
	size_t operator()(pair<int,int> a)const
	{
		return ((long long)a.first<<32)|a.second; 
	}
}; 
unordered_map<pair<int,int>,bool,Hash> ma;
struct node1{int x,y,z;} g[2000010];
int n,a[1010][1010],d[1010][1010],cnt,id[1010][1010];
int val[2000010],fa[2000010],f[2000010][21];
int fx[5][3],tot1,tot;
struct node{int last,en,next;} e[10000010];
char ch[1010][1010];
bool bz[1010][1010],ru[2000010];
int dep[2000010];
int q,x1,y1,x2,y2;
bool check(int d,int x,int y)
{
    int x1=x-d,y1=y-d,x2=x+d,y2=y+d;
    if (x1<=0||y1<=0||x2>n||y2>n) return false;
    if (a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1]>0) return false;
    return true;
}
void bfs(int s,int t)
{
    queue<pair<int,int> > q;
    bz[s][t]=true;
    q.push(make_pair(s,t));
    id[s][t]=++cnt;
    while (!q.empty())
    {
        int x=q.front().first,y=q.front().second;q.pop();
        for (int k=1;k<=4;k++)
        {
            int xx=fx[k][1]+x,yy=fx[k][2]+y;
            if (xx>0&&xx<=n&&yy>0&&yy<=n&&ch[xx][yy]=='.'&&!bz[xx][yy]&&d[xx][yy]==d[x][y])
            {
                bz[xx][yy]=true;
                q.push(make_pair(xx,yy));
                id[xx][yy]=cnt;
            }
        }
    }
}
void insert(int x,int y,int z)
{
    g[++tot1].x=x;g[tot1].y=y;g[tot1].z=z;
}
bool cmp(node1 x,node1 y){return x.z>y.z;}
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void add(int x,int y)
{
    e[++tot].en=y;
    e[tot].next=e[x].last;
    e[x].last=tot;
}
void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1;f[x][0]=fa;
    for (int i=e[x].last;i;i=e[i].next)
        if (e[i].en!=fa) dfs(e[i].en,x);
}
int lca(int x,int y)
{
    if (dep[x]<dep[y]) swap(x,y);
    for (int i=20;i>=0;i--)
        if (dep[f[x][i]]>=dep[y]) x=f[x][i];
    if (x==y) return x;
    for (int i=20;i>=0;i--)
        if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
int main()
{
    fx[1][1]=fx[3][2]=-1;fx[2][1]=fx[4][2]=1;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",ch[i]+1);
        for (int j=1;j<=n;j++)
            a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+(ch[i][j]=='#');
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        if (ch[i][j]=='.')
        {
            int l=0,r=n/2,mid,ret=0;
            while (l<=r)
            {
                mid=(l+r)>>1;
                if (check(mid,i,j)) l=mid+1,ret=mid;
                else r=mid-1;
            }
            d[i][j]=ret*2+1;
        }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (ch[i][j]=='.'&&!bz[i][j]) bfs(i,j);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (ch[i][j]=='.')
            {
                for (int k=1;k<=4;k++)
                {
                    int xx=fx[k][1]+i,yy=fx[k][2]+j;
                    if (xx>0&&xx<=n&&yy>0&&yy<=n&&ch[xx][yy]=='.'&&id[xx][yy]!=id[i][j]&&!ma[make_pair(id[xx][yy],id[i][j])])
                    {
                        ma[make_pair(id[xx][yy],id[i][j])]=true;
                        ma[make_pair(id[i][j],id[xx][yy])]=true;
                        insert(id[i][j],id[xx][yy],min(d[i][j],d[xx][yy]));
                        insert(id[xx][yy],id[i][j],min(d[i][j],d[xx][yy]));
                    }
                }
            }
    sort(g+1,g+tot1+1,cmp);
    for (int i=1;i<=2*cnt;i++) fa[i]=i;
    for (int i=1;i<=tot1;i++)
    {
        int u=get(g[i].x),v=get(g[i].y);
        if (u!=v)
        {
            ++cnt;ru[u]=true;ru[v]=true;
            fa[u]=fa[v]=cnt;val[cnt]=g[i].z;
            add(cnt,u);add(cnt,v);
        }
    }
    int bj=0;
    for (int i=1;i<=cnt;i++)
        if (!ru[i]) bj++;
    if (bj>1)
    {
        for (int i=1;i<=cnt;i++)
            if (!ru[i]) add(cnt+1,i);
        val[++cnt]=0;
    }
    dfs(cnt,0);
    for (int j=1;j<=20;j++)
        for (int i=1;i<=cnt;i++)
            f[i][j]=f[f[i][j-1]][j-1];
    scanf("%d",&q);
    for (int i=1;i<=q;i++)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if (id[x1][y1]==id[x2][y2]) printf("%d\n",d[x1][y1]);
        else printf("%d\n",val[lca(id[x1][y1],id[x2][y2])]);
    }
    return 0;
}
```

---

## 作者：wuzhaoxin (赞：2)

# 剪枝 $O(n^3log_2n)$ 吸氧过1k

首先我们把每个障碍看成1，每个空位看成0，那么如果一个矩阵的和为0那么这个矩阵是空的，于是我们只需要做一个二维前缀和，然后就可以查询每个矩阵是否为空了

根据题意，所求即为两点之间路径可放置集装箱的大小的最小值的最大值（这个可以预处理然后建最大生成树，但是我傻了），一看就是一个可以二分的东西，对于一个询问，我们二分一个答案，然后对于整张图跑一边BFS，把所有可以互相到达的点放在一个连通块中，可以用染色来标记，如果两个点在同一连通块之间，那么答案可以被满足，由于是多组数据，直接**整体二分**即可

时间复杂度 $O(n^3log_2n)$

那么所谓的剪枝在哪呢？就是一句 ``if(v.empty()) return;`` 然后由于数据的原因此处大量剪枝然后吸氧过了

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
char mp[1001][1001];
int sum[1001][1001] = {0};
int get(int x1, int y1, int x2, int y2) {
    x1 --, y1 --;
    return sum[x2][y2] + sum[x1][y1] - sum[x1][y2] - sum[x2][y1];
}
int n;
int ans[300001];
struct qu {
    int x1, y1, x2, y2, id;
};
int vis[1001][1001];
queue<int> qx, qy;
void bfs(int x, int y, int r, int c) {
    qx.push(x), qy.push(y);
    vis[x][y] = c;
    while(! qx.empty()) {
        x = qx.front(), y = qy.front();
        qx.pop(), qy.pop();
        if(x + 1 + r <= n && ! vis[x + 1][y] && get(x + 1 - r, y - r, x + 1 + r, y + r) == 0) {
            vis[x + 1][y] = c;
            qx.push(x + 1), qy.push(y);
        }
        if(x - 1 - r >= 1 && ! vis[x - 1][y] && get(x - 1 - r, y - r, x - 1 + r, y + r) == 0) {
            vis[x - 1][y] = c;
            qx.push(x - 1), qy.push(y);
        }
        if(y + 1 + r <= n && ! vis[x][y + 1] && get(x - r, y + 1 - r, x + r, y + 1 + r) == 0) {
            vis[x][y + 1] = c;
            qx.push(x), qy.push(y + 1);
        }
        if(y - 1 - r >= 1 && ! vis[x][y - 1] && get(x - r, y - 1 - r, x + r, y - 1 + r) == 0) {
            vis[x][y - 1] = c;
            qx.push(x), qy.push(y - 1);
        }
    }
}
void solve(vector<qu> v, int l, int r) {
    if(v.empty()) return;
    if(l == r) {
        for(int i = v.size() - 1; i >= 0; i --)
            ans[v[i].id] = max(l * 2 - 1, 0);
        return;
    }
    int mid = (l + r) >> 1;
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(! vis[i][j] && i - mid >= 1 && i + mid <= n && j - mid >= 1 && j - mid <= n && get(i - mid, j - mid, i + mid, j + mid) == 0)
                bfs(i, j, mid, i * n + j);
    vector<qu> tl, tr;
    for(int i = v.size() - 1; i >= 0; i --) {
        if(vis[v[i].x1][v[i].y1] != 0 && vis[v[i].x1][v[i].y1] == vis[v[i].x2][v[i].y2]) tr.push_back(v[i]);
        else tl.push_back(v[i]);
    }
    v.clear();
    solve(tl, l, mid), solve(tr, mid + 1, r);
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%s", mp[i] + 1);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (mp[i][j] == '#');
    int q;
    scanf("%d", &q);
    vector<qu> v;
    for(int i = 1; i <= q; i ++) {
        qu p;
        scanf("%d%d%d%d", &p.x1, &p.y1, &p.x2, &p.y2);
        p.id = i;
        v.push_back(p);
    }
    solve(v, 0, (n + 1) / 2);
    for(int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15912336.html)

首黑祭，这道题思维难度紫，但是代码难度黑。。。

调了一上午，足足三个小时。

# 题目大意

你正在评估一些关于一个巨型飞机仓库的建设计划。飞机仓库的地面可以表示为 $n$ 行 $n$ 列的网格图，其中每个格子要么是空的，要么有障碍物。行从上到下依次被编号为 $1$ 到 $n$，列从左到右依次被编号为 $1$ 到 $n$。

存放飞机零件的大型集装箱能在飞机仓库的地面上自由移动是很重要的。我们可以将每个集装箱看作一个以某个格子为中心的边平行于坐标轴的正方形。对于一个奇数 $k$，一个尺寸为 $k$ 的集装箱是一个包含 $k$ 行 $k$ 列的正方形。一个集装箱的坐标为其中心格子的坐标。集装箱可以向上下左右移动，但不能碰到障碍物，且不能移出仓库的边界。

给定 $q$ 对格子 $A_k$ 和 $B_k$，对于每对格子，请找到能从 $A_k$ 移动到 $B_k$ 的集装箱的最大尺寸，注意这个尺寸也要是一个奇数。

# 前置知识

+ $\rm Kruskal$ 重构树。

从下面的例子入手：

![](https://cdn.luogu.com.cn/upload/image_hosting/190404v9.png)

-----------
该例最小生成树为：

![](https://cdn.luogu.com.cn/upload/image_hosting/s289duoo.png)

我们按照 $\rm Kruskal$ 的方式建树，设要连接的边为 $(u,v)$，通过并查集可求得 $u$ 的祖先节点为 $x$，$v$ 的祖先节点为 $y$。

若 $x\neq y$，则新建一个节点 $z$ 作为 $x,y$ 的父亲来合并 $x,y$，$z$ 的点权为边 $(x,y)$ 的长度。

最后我们建出来了一棵二叉树，具体长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/3lekyexq.png)

这棵树拥有以下性质：

+ 叶子节点都是构成最小生成树的节点。

+ 生成树中有 $n$ 个节点，会产生 $n-1$ 个含有点权的节点，共 $n+n-1=2\cdot n-1$ 个节点。

+ 按最小生成树重构的重构树是大根堆，按最大生成树重构的重构树是小根堆。

+ 按最小生成树重构的重构树中任意两点 $a,b$ 的路径中的最大边权为它们 $\operatorname{LCA}(a,b)$ 的点权，也是 $a,b$ 路径中最大边权的最小值，按最大生成树重构的重构树中任意两点 $a,b$ 的路径中的最小边权为它们 $\operatorname{LCA}(a,b)$ 的点权，也是 $a,b$ 路径中最小边权的最大值。

------------
模板代码：

```cpp
namespace ex_Kruskal{
	// 注意数组开两倍! 
	
	int nowidx,idx;
	inline bool cmp1(Node x,Node y) { // 按最小生成树重构的重构树
		return x.w < y.w;
	}
	inline bool cmp2(Node x,Node y) { // 按最大生成树重构的重构树
		return x.w > y.w;
	}
	inline void add(int u,int v) {
		gra[++ idx].v = v,gra[idx].nxt = head[u];
		head[u] = idx;
	}
	
	inline void Kruskal() {
		for (register int i = 1;i <= n * 2 - 1; ++ i) {
			fa[i] = i;
		}
		sort (node + 1,node + m + 1,ex_Kruskal::cmp);
		
		nowidx = n;
		for (register int i = 1;i <= m; ++ i) {
			int x = getf(node[i].u),y = getf(node[i].v);
			if (x != y) {
				val[++ nowidx] = node[i].w;//存储当前节点的点权
				fa[x] = fa[y] = nowidx;
				
				add(nowidx,x),add(nowidx,y);
			}
		}
	}
}
```

# 题目分析

首先来考虑一下思路。

求出每个坐标能放置的最大正方形边长，并令其为该个坐标的点权，每次询问转换为求出两点路径上最小点权的最大值，注意到“最小/最大”，考虑 $\rm Kruskal$ 重构树。

对于每个坐标，都对它相邻的坐标连边，但是直接连边空间爆炸，所以每个坐标，点权相同且相邻的缩为一个点。再连边即可。我们连出来了一棵树（**可能是森林！！！因为如果周围是障碍物的话不会连边**），重构树即可。

------
怎么求每个坐标能放置的最大正方形边长呢？我们先 $\mathcal{O(n^2)}$ 求出每个矩阵的障碍物数量。如果一个坐标不是障碍物，那么二分从正方形中心点到正方形边界的距离，因为是奇数这样好算，再看看这个正方形内有没有障碍物就 $\mathbf{ok}$ 了。

# 代码

```cpp
//2022/2/18
//2022/2/19
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <algorithm>
#include <utility>
#include <queue>
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;
typedef pair<int,int> PII;

const short dx[] = {0,0,-1,1};
const short dy[] = {1,-1,0,0};
const int INF = 0x3f3f3f3f;
const int ma = 1005;
int fa[ma * ma],dep[ma * ma],fath[ma * ma],du[ma * ma],head[ma * ma],val[ma * ma],sum[ma][ma],maxsiz[ma][ma],bel[ma][ma],f[ma * ma][21];// 每个点的最大矩形
bool vis[ma][ma];
char mp[ma][ma];
int n,m,cnt,idx,num,nowidx;
struct Node {
	int u,v,w;
} node[(ma * ma) << 1];
struct Gragh {
	int v,nxt;
} gra[(ma * ma) << 1];
inline bool check(int i,int j,int len) {
	if (i - len < 1 || i + len > n || j - len < 1 || j + len > n) return false;
	if (sum[i + len][j + len] - sum[i - len - 1][j + len] - sum[i + len][j - len - 1] + sum[i - len - 1][j - len - 1] == 0){
		return true;
	}
	return false;
}
inline int getsiz(int i,int j) {
	int l = 0,r = n / 2,ans;
	while (l <= r) {
		int mid = l + r >> 1;// 二分矩阵中心点到边界的距离
		if (check(i,j,mid)) {
			l = mid + 1;
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	return ans * 2 + 1;
}
inline void bfs(int i,int j,int belong) {
	queue<PII>q;
	vis[i][j] = true,bel[i][j] = belong;
	q.push({i,j});
	while (!q.empty()) {
		PII u = q.front();q.pop();
		int x = u.first,y = u.second;
		for (register int k = 0;k < 4; ++ k) {
			int nx = x + dx[k],ny = y + dy[k];
			if (nx >= 1 && ny >= 1 && nx <= n && ny <= n && maxsiz[nx][ny] == maxsiz[x][y] && vis[nx][ny] == false) {
				vis[nx][ny] = true,bel[nx][ny] = belong;
				q.push({nx,ny});
			}
		}
	}
}
inline int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
inline void merge(int x,int y) {
	int f1 = getf(x),f2 = getf(y);
	if (f1 != f2) fa[f1] = f2;
}
inline void ADD(int u,int v,int w) {
	node[++ idx].u = u,node[idx].v = v,node[idx].w = w;
}
inline void add(int u,int v) {
	gra[++ num].v = v,gra[num].nxt = head[u],head[u] = num;
}
namespace ex_Kruskal {
	inline bool cmp(Node x,Node y) {
		return x.w > y.w;
	}
	inline int getfath(int x) {
		return fath[x] == x ? x : fath[x] = getfath(fath[x]);
	}
	inline void Kruskal() {
		nowidx = cnt;
		for (register int i = 1;i <= n * n; ++ i) {
			fath[i] = i;
		}
		for (register int i = 1;i <= idx; ++ i) {
			int x = getfath(node[i].u),y = getfath(node[i].v);
			if (x != y) {
				val[++ nowidx] = node[i].w;
				du[x] ++,du[y] ++;
				fath[x] = fath[y] = nowidx;
				add(nowidx,x),add(nowidx,y);
			}
		}
	}
}
inline void dfs(int now,int dad,int depth) {
	dep[now] = depth,f[now][0] = dad;
	for (register int i = 1;i <= 20; ++ i) {
		f[now][i] = f[f[now][i - 1]][i - 1];
	}
	for (register int i = head[now];i;i = gra[i].nxt) {
		int v = gra[i].v;
		if (v != dad) {
			dfs(v,now,depth + 1);
		}
	}
}
inline int LCA(int x,int y) {
	if (dep[x] < dep[y]) swap(x,y);
	for (register int i = 20;i >= 0; -- i) {
		if (dep[f[x][i]] >= dep[y]) {
			x = f[x][i];
		}
	}
	if (x == y) return x;
	for (register int i = 20;i >= 0; -- i) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i],y = f[y][i];
		}
	}
	return f[x][0];
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	mst(val,0x3f);
	scanf("%d",&n);
	for (register int i = 1;i <= n; ++ i) {
		scanf("%s",mp[i] + 1);
	}
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = 1;j <= n; ++ j) {
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
			if (mp[i][j] == '#') sum[i][j] ++;//有障碍物
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = 1;j <= n; ++ j) {
			if (mp[i][j] == '.') {
				maxsiz[i][j] = getsiz(i,j);
			} else {
				maxsiz[i][j] = -1;
			}
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = 1;j <= n; ++ j) {
			if (vis[i][j] == false && mp[i][j] == '.') {
				bfs(i,j,++ cnt);
			}
		}
	}
	for (register int i = 1;i <= n * n; ++ i) fa[i] = i;
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = 1;j <= n; ++ j) {
			if (mp[i][j] == '.') {
				for (register int k = 0;k < 4; ++ k) {
					int nx = i + dx[k],ny = j + dy[k];
					if (nx >= 1 && ny >= 1 && nx <= n && ny <= n && bel[i][j] != bel[nx][ny] && mp[nx][ny] == '.' && getf(bel[i][j]) != getf(bel[nx][ny])) {
						ADD(bel[i][j],bel[nx][ny],min(maxsiz[i][j],maxsiz[nx][ny])),ADD(bel[nx][ny],bel[i][j],min(maxsiz[i][j],maxsiz[nx][ny]));
						merge(bel[i][j],bel[nx][ny]);
					}
				}
			}
		}
	}
	sort(node + 1,node + idx + 1,ex_Kruskal::cmp);
	ex_Kruskal::Kruskal();
	for (register int i = 1;i <= nowidx; ++ i) {
		if (!du[i]) {
			dfs(i,0,1);
		}
	}
	m = read();
	while (m --) {
		int x1 = read(),y1 = read(),x2 = read(),y2 = read();
		if (bel[x1][y1] == bel[x2][y2]) {
			printf("%d\n",maxsiz[x1][y1]);
		} else if (ex_Kruskal::getfath(bel[x1][y1]) != ex_Kruskal::getfath(bel[x2][y2])) {
			puts("0");
		} else {
			int lca = LCA(bel[x1][y1],bel[x2][y2]);
			if (val[lca] == INF) puts("0");
			else printf("%d\n",val[lca]);
		}
	}

	return 0;
}
```

---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P3684)

---

前置知识：$\text{Kruskal}$重构树

码农题，思维难度不大，就是码。

本体基本是裸的 $\text{Kruskal}$重构树板题，但其实打裸板子会超时。

这道题是个二维的图，可以上下左右移动，所以很容易想到这样建边：

```cpp
	int cnt = 0;
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= n ; ++ j) {
			if (s[i][j] == '#') continue;
			for (int k = 1 ; k <= 4 ; ++ k) {
				int xx = i + movex[k];
				int yy = j + movey[k];
				if (xx < 1 || xx > n || yy < 1 || yy > n || s[xx][yy] == '#') continue;
				p[++ cnt] = node(h[i][j],h[xx][yy],Min(maxx[i][j] * 2 + 1,maxx[xx][yy] * 2 + 1));
			}
		}
	}
```

但这样是建了很多边的，毕竟上下左右都建了边嘛。

这样跑 $\text{LCA}$ 会耗极长的时间，自然是不行的。

我们可以发现，我们这些点，如果它们能放的最大的货物是一样的，并且是联通的。

我们可以把它们看成一个点，这样就可以少见很多边了，我用的是并查集$+bfs$缩点。

~~说到并查集缩点我想推荐[这道水蓝题](https://www.luogu.com.cn/problem/CF734E)。~~

之后输出的时候要判一下这两个点是否缩成了一个点，缩成一个点就直接输出。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (ch > '9' || ch < '0') {if (ch == '-') f = -1;ch = getchar();}
	while (ch <= '9' && ch >= '0') {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) x = -x,putchar('-');
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<typename T>T Min(T x,T y) {
	return x < y ? x : y;
}
const int maxn = 5000005;
int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int u,int v) {
    ver[++ tot] = v;nxt[tot] = head[u];head[u] = tot;
}

struct node {
	int u,v,w;
	node(){}
	node(int U,int V,int W) {u = U;v = V;w = W;}
	bool operator <(node x) const {
		return this->w > x.w;
	}
}p[maxn];

int n,m,q,val[maxn],f[maxn],fath[maxn],fa[maxn][20],dep[maxn],lg[maxn],vis[maxn];

int finds(int x) {
	while (x != f[x]) x = f[x] = f[f[x]] = f[f[f[x]]];
	return x;
}

int findset(int x) {
	while (x != fath[x]) x = fath[x] = fath[fath[x]] = fath[fath[fath[x]]];
	return x;
}

void dfs(int u,int father) {
	vis[u] = 1;
	fa[u][0] = father;
	dep[u] = dep[father] + 1;
	for (int i = 1 ; i <= lg[dep[u]] ; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int e = head[u] ; e ; e = nxt[e]) {
		int v = ver[e];
		if (v == father) continue;
		dfs(v,u);
	}
}

int LCA(int x,int y) {
	if (dep[x] < dep[y]) swap(x,y);
	while (dep[x] > dep[y]) x = fa[x][lg[dep[x] - dep[y]] - 1];
	if (x == y) return x;
	for (int i = lg[dep[x]] ; ~i ; -- i)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}

char s[1005][1005];
int a[1005][1005],maxx[1005][1005],h[1005][1005],app[1005][1005];
int movex[5] = {0,0,0,1,-1};
int movey[5] = {0,1,-1,0,0};

void bfs(int x,int y,int col) {
	app[x][y] = col;
	queue<int> q;
	q.push(x * 10000 + y);
	while (!q.empty()) {
		int u = q.front(),v;
		q.pop();
		v = u % 10000;
		u = u / 10000;
		for (int i = 1 ; i <= 4 ; ++ i) {
			int xx = u + movex[i];
			int yy = v + movey[i];
			if (maxx[xx][yy] != maxx[u][v] || app[xx][yy] || xx < 1 || xx > n || yy < 1 || yy > n || s[xx][yy] == '#') continue;
			q.push(xx * 10000 + yy);
			app[xx][yy] = col;
			fath[h[xx][yy]] = h[x][y];
		}
	}
}

bool check(int x,int y,int z) {
	if (x + z > n || y + z > n || x - z < 1 || y - z < 1) return false;
	return !(a[x + z][y + z] + a[x - z - 1][y - z - 1] - a[x + z][y - z - 1] - a[x - z - 1][y + z]);
}

int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i) {
		scanf("%s",s[i] + 1);
		for (int j = 1 ; j <= n ; ++ j) {
			a[i][j] = s[i][j] == '#';
		}
	}
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= n ; ++ j) {
			a[i][j] = a[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}
	int tmp = 0;
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= n ; ++ j) {
			h[i][j] = ++ tmp;
			if (s[i][j] != '#') {
				int l = 0,r = Min(Min(i - 1,n - i),Min(j - 1,n - j)),ans;
				while (l < r) {
					int mid = l + r + 1 >> 1;
					if (check(i,j,mid)) l = mid;
					else r = mid - 1;
				}
				maxx[i][j] = l * 2 + 1;
			}
		}
	}
	for (int i = 1 ; i < maxn ; ++ i) fath[i] = f[i] = i,lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
	int cnt = 0,points = 0;
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= n ; ++ j) {
			if (s[i][j] == '#') {
				fath[h[i][j]] = 0;
				continue;
			}
			if (!app[i][j]) {
				++ points;
				bfs(i,j,points);
			}
		}
	}
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= n ; ++ j) {
			if (s[i][j] == '#') continue;
			for (int k = 1 ; k <= 4 ; ++ k) {
				int xx = i + movex[k];
				int yy = j + movey[k];
				if (xx < 1 || xx > n || yy < 1 || yy > n || s[xx][yy] == '#') continue;
				if (fath[h[i][j]] != fath[h[xx][yy]]) p[++ cnt] = node(fath[h[i][j]],fath[h[xx][yy]],Min(maxx[i][j],maxx[xx][yy]));
			}
		}
	}
	sort(p + 1,p + 1 + cnt);
	for (int i = 1 ; i <= cnt ; ++ i) {
		int u = p[i].u,v = p[i].v;
		int x = finds(u),y = finds(v);
		if (x != y) {
			val[++ tmp] = p[i].w;
			addEdge(tmp,x);
			addEdge(tmp,y);
			f[x] = tmp;f[y] = tmp;
		}
	}
	for (int i = 1 ; i <= n ; ++ i)
		for (int j = 1 ; j <= n ; ++ j)
			if (!vis[finds(fath[h[i][j]])] && s[i][j] == '.')
				dfs(finds(fath[h[i][j]]),0);
	read(q);
	int ax,ay,bx,by;
	while (q --) {
		read(ax);read(ay);read(bx);read(by);
		if (fath[h[ax][ay]] == fath[h[bx][by]]) print(maxx[ax][ay]),putchar('\n');
		else print(val[LCA(fath[h[ax][ay]],fath[h[bx][by]])]),putchar('\n');
	}
	return 0;
}
```

---

