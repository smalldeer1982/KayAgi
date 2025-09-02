# [USACO20JAN] Time is Mooney G

## 题目描述

Bessie 正在安排前往牛尼亚的一次出差，那里有 $N$（$2 \leq N \leq 1000$）个编号为 $1 \ldots N$ 的城市，由 $M$（$1 \leq M \leq 2000$）条单向的道路连接。Bessie 每次访问城市 $i$ 都可以赚到 $m_i$ 哞尼（$0 \leq m_i \leq 1000$）。从城市 $1$ 出发，Bessie 想要赚到尽可能多的哞尼，最后回到城市 $1$。为了避免争议，$m_1=0$。

沿着两个城市之间的道路移动需要消耗一天。出差的准备工作十分费钱；旅行 $T$ 天需要花费 $C \times T^2$ 哞尼（$1 \leq C \leq 1000$）。

Bessie 在一次出差中最多可以赚到多少哞尼？注意有可能最优方案是 Bessie 不访问城市 $1$ 之外的任何城市，在这种情况下结果应当为 $0$。

## 说明/提示

最优的旅行方案是 $1 \to 2 \to 3 \to 1 \to 2 \to 3 \to1$。Bessie 总共赚到了 $10+20+10+20-1 \times 6^2=24$ 哞尼。

## 样例 #1

### 输入

```
3 3 1
0 10 20
1 2
2 3
3 1```

### 输出

```
24```

# 题解

## 作者：奇米 (赞：12)

## 题解-P6005 Time is Mooney G

* **题目意思**

 就是给你一个有向图，你在上面走，没经过一个点可以获得$m_i$，最后你要减去$sum^2$(走过的边数)$*C$
 
* $Sol$
 
 考虑$DP$,我们设$f_{i,j}$表示第$i$天到达城市$j$的最大收益。
 
 转移很简单$f_{i,j}=max\{f_{i-1,las_j}+m_j,f_{i,j}\}$
 
 对于$las_j$的处理我们只需要反向建有向边即可，答案就是$max\{f_{i,1}-i^2*C\}$
 
 但是这样$i$的枚举范围无法确定，但是我们发现$i\leq 1000$即可，因为$max\{m_i\}*day-day^2*C\leq 1$
 
* $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1005;

int n,m,C,cnt,head[N];
int M[N],f[N][N],ans; 

struct nood {
	int nex,to;
};
nood e[N<<2];

inline void jia(int u,int v) {
	e[++cnt].nex=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}

inline int read() {
	int sum=0; char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) 
		sum=sum*10+(ch^48),ch=getchar();
	return sum;
}

int main() {
	n=read();
	m=read();
	C=read();
	for ( int i=1;i<=n;i++ ) M[i]=read();
	for ( int i=1;i<=m;i++ ) {
		int u,v;
		u=read();
		v=read();
		jia(v,u);
	}
	//f[i][j]表示第i天到达第j座城市的最大收益
	memset(f,-1,sizeof(f));
	f[0][1]=0;
	for ( int i=1;i<=1000;i++ ) {
		for ( int j=1;j<=n;j++ )
			for ( int k=head[j];k;k=e[k].nex ) {
				int v=e[k].to;
				if(~f[i-1][v]) 
					f[i][j]=max(f[i][j],f[i-1][v]+M[j]);
			}
		if(ans<f[i][1]-C*i*i) ans=f[i][1]-C*i*i;
	}
	printf("%d\n",ans);
	return 0;
}
	
```

 
 

---

## 作者：wmy_goes_to_thu (赞：8)

大家都写 dp，我写 spfa 吧。一看到图和最值，肯定会想到最短路。但是如果就用一维表示状态，那么无法表示天数，所以我们用二维的状态，在这里第二维表示天数，这叫做分层图最短路。那么，我们如何判断状态是否可以呢？我们需要再记录一个数组表示答案，然后直接跑最短路就行了。

upd：原文写的是 dij 也可以，但是笔者没实现过，认为正权最长路可以，其实等价于取反跑最短路，dij 显然不正确。在此感谢指出[错误](https://www.luogu.com.cn/discuss/331899)。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[1005];
vector<pair<int,int> >g[1005];
int dist[1005][5005],vist[1005][5005],ans[1005];
int q1[5000005],q2[5000005];
int main()
{
	int n,m,c;
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++)scanf("%d",&s[i]);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(make_pair(v,s[v]));
	}
	memset(dist,-63,sizeof(dist));
	memset(ans,-63,sizeof(ans));
	ans[1]=0;
	dist[1][0]=0;
	vist[1][0]=1;
	int head=0,tail=0;
	q1[++tail]=1,q2[tail]=0;
	while(head<tail&&tail<=5000000)
	{
		int p1=q1[++head],p2=q2[head];
		vist[p1][p2]=0;
		int sd=g[p1].size();
		for(int i=0;i<sd;i++)
		{
			int cu1=g[p1][i].first;
			int cu2=g[p1][i].second;
			int dj=dist[p1][p2]+cu2-c*(p2+p2+1);
			if(dist[cu1][p2+1]<dj&&ans[cu1]<dj)
			{
				dist[cu1][p2+1]=ans[cu1]=dj;
				if(!vist[cu1][p2+1])
				{
					vist[cu1][p2+1]=1;
					q1[++tail]=cu1,q2[tail]=p2+1;
				}
			}
		}
	}
	cout<<ans[1];
	return 0;
}
```


---

## 作者：UltiMadow (赞：6)

看到没人写题解，我就来写一篇

### 前言
考场上看到这道题我是崩溃的，感觉没有思路

后来仔细分析了一下这道题的数据范围，好像不大

于是我暴力+一些优化过了
### 解法
考虑bfs

bfs的方法我就不说了，比较简单；我们来说说我加的两个优化

#### 优化1：搜索时间限制
这里有一个看似没用的简单结论：

当我之后走的每一步都会亏本，我就不走了

正确性自然不用证明，但是这个结论有啥用呢？

我们设 $T$ 为走的总时间，$maxval$ 为所有的城市中得钱最多的

于是我们可以得到这样的一个不等式：
$$
maxval\times T-cT^2>0
$$
什么意思呢？就是假设每次走都可以得到 $maxval$ 块钱，走这些路程能赚的钱数

解得：
$$
T<\frac{maxval}{c}
$$
这样，我们就可以限制bfs时搜索的时间，也就是一个搜索边界
#### 优化2：最优性剪枝
原理：当我们在 $t_1$ 时刻走到一个点，而在此之前，存在一个 $t_2\le t_1$ 时刻在当前点的得钱比现在多，那么当前的搜索是没有意义的，结束当前分枝的搜索

应该比较好理解吧

### 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 2010
using namespace std;
int n,m,c;
int val[MAXN];
struct Node
{
	int to,next;
}Edge[MAXN<<1];
int Head[MAXN],cnt_Edge;
void Add_Edge(int u,int v)
{
	Edge[++cnt_Edge].to=v;
	Edge[cnt_Edge].next=Head[u];
	Head[u]=cnt_Edge;
}//链表存图
int T,ans;
int ear[MAXN][MAXN];//这里是earn的缩写，不是耳朵qwq，用于最优性剪枝
struct Nodex
{
	int now,tim,dis;
};
void bfs()
{
	queue<Nodex>Q;
	Q.push((Nodex){1,0,0});//队列中存当前节点，到达当前节点的时间，到达当前节点赚的钱
	while(!Q.empty())
	{
		Nodex tmp=Q.front();Q.pop();
		int u=tmp.now,t=tmp.tim,w=tmp.dis;
		for(int i=Head[u];i;i=Edge[i].next)
		{
			int v=Edge[i].to,nowt=t+1,noww=w+val[v];
			if(v==1)ans=max(ans,w-c*nowt*nowt);//统计答案
			bool fl=true;
			for(int j=nowt;j>=1;j--)
				if(ear[v][j]>=noww-c*nowt*nowt)
				{
					fl=false;
					break;
				}//最优性剪枝
			if(!fl)continue;
			ear[v][nowt]=noww-c*nowt*nowt;
			if(nowt<T)Q.push((Nodex){v,nowt,noww});//搜索边界
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&c);
	int val_max=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i]);
		val_max=max(val_max,val[i]);
	}
	T=val_max/c;//搜索边界
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	bfs();
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Jayun (赞：4)

# 题目大意：

$N$ 个城市，由 $M$ 条单向道路连接，每次去城市 $i$ 都能赚 $m_i$ 元，但是每去一个城市都会花费一天，旅行 $T$ 天就要花费 $C\cdot T^{2}$ 元，求最多能赚到多少钱。

# 正文：

考虑用动态规划解决本题，设 $f_{i,j}$ 表示第 $i$ 天在城市 $j$ 时赚到的钱。那么目标状态显然是 $(f_{T,1}-C\cdot T^{2})$。

动态转移方程是：

$$f_{i,j}=\max\{f_{i-1,k}+m_j\}$$

因为是单向边，在用邻接表存图的时候最好是倒着存，以辅助动态转移，那么方程式中的 $k$ 代表上一个城市，也就是代码（见下文）中的 $e[i].to$。

# 代码：

```cpp

memset(f, -1, sizeof f);
f[0][1] = 0;
for (int i = 1; i <= N - 10; i++)
	for (int j = 1; j <= n; j++)
		for (int I = head[j]; I; I = e[I].next)
			if(f[i - 1][e[I].to] != -1)
				f[i][j] = max(f[i][j], f[i - 1][e[I].to] + a[j]);

for (int i = 1; i < N - 10; i++)
	ans = max(f[i][1] - c * i * i, ans);
```

---

## 作者：gznpp (赞：2)

感觉像是 [[NOI2019] 回家路线](https://www.luogu.com.cn/problem/P5468) 的简化版。

按照时间建分层图，原图上的边 $u \rightarrow v$ 对应分层图上 $(time, u) \rightarrow (time + 1, v)$，其中 $0 \le time < 1000$，因为 $m_i$ 取最大值 $1000$，$C$ 取最小值 $1$ 时，答案的最大值为 $1000t - t^2$，在 $t > 1000$ 时会变成负的。

这题数据范围比较小，直接暴力跑就可以了。复杂度 $O(TM)$。

Code:
```cpp
// orh::ru ui() 是快读，orh::wu ui() 是快写
// 
// template <typename typ> 
// inline bool up(typ &x, const typ &y) {
// return x < y ? x = y, 1 : 0; }

signed main() {
	//flio("time");
	
	n = orh::ru ui(), m = orh::ru ui(), c = orh::ru ui();
	for (rg int i = 1; i <= n; ++i) a[i] = orh::ru ui();
	for (rg int i = 1; i <= m; ++i) {
		u[i] = orh::ru ui(), v[i] = orh::ru ui();
		nxt[i] = fst[u[i]], fst[u[i]] = i;
	}
	
	memset(dp, -1, sizeof(dp));
	dp[0][1] = 0;
	for (rg int t = 1; t <= 1000; ++t) {
		for (rg int i = 1; i <= m; ++i) 
			if (~dp[t - 1][u[i]])
				up(dp[t][v[i]], dp[t - 1][u[i]] + a[v[i]]);
		up(ans, dp[t][1] - c * t * t);
	}
	
	orh::wu ui(ans);
	
	return 0;
}
```

---

## 作者：pocafup (赞：1)

抢第一篇题解

这题的思路其实就是一个非常简单的dijkstra,如果跑到第一个点的数据不能更新的时候就输出

很多人不知道要跑多少次才停.其实这题因为答案要减去 $T*c^2$,而每条边的值 $<= 1000$,稍微推一下就可以发现这个程序最多跑1000次.

所以,简单暴力的做法就是暴力写1000次dijkstra (01dij或者二维1000*1000都可以).这个方法当然可以优化,~~但是没有超时谁理他呢~~

现在剩下一个小问题(如果没有经过的点,我们不能更新连同他的路).那么怎么办呢?

摆在眼前的路有两条.第一:到所有点的初始值设成-1跑.如果目前的点的值为-1就证明他没有被经过,所以需要跳过

第二:做一个vis,记录每次经过并且以前没有经过过的点.这里我用的是queue,记录所有这一次被拿到的点.

注意不要马上更新,因为如果你马上更新就会出现没有经过的点被更新了

01的意义就是保证所有点更新的都是之前更新过但这一次没有更新的,保证不会出现一条边被更新很多次的情况

话不多说,上代码

```cpp
#include <iostream>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
int dp[1005][2],head[100005],tot = 0,n,m,c, cost[1005],ans=0,vis[1005];
struct Edge{
  int from, to,next;
}edge[100005];
void add(int f,int t){
  edge[++tot].from = f;
  edge[tot].to = t;
  edge[tot].next = head[f];
  head[f] = tot;
}
void setIO(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
	ios_base::sync_with_stdio(0);
}
//以上不解释
void dij(int curr){
  queue<int> q;//记经过的边
  for (int i=1;i<=n;i++){
    if (!vis[i]) continue;//如果没有经过就不跑
    for (int j=head[i];j;j=edge[j].next){
      if (!vis[edge[j].to]) q.push(edge[j].to);//没经过就加进queue待会更新
      dp[edge[j].to][curr%2] = max(dp[edge[j].from][(curr+1)%2]+cost[edge[j].to],dp[edge[j].to][curr%2]);
      //要去的点的值现在的点的值+那个点的权值.
    }
  }
  while(!q.empty()){vis[q.front()] = true;q.pop();}
  //将所有经过的点的vis设成true
  ans = max(ans,(int)(dp[1][curr%2]-c*pow(curr,2)));
  //更新答案
}

int main(){
  // setIO("time");
  cin >> n >> m >> c;
  for (int i=1;i<=n;i++) cin >> cost[i];
  for (int i=0;i<m;i++){
    int a,b; cin >> a >> b;
    add(a,b);//连边,如果要转化为权值问题只需将权值设为cost[b]就行
  }
  vis[1] = true;//将初始点设为已经过
  for (int i=1;i<1000;i++){
    dij(i);//跑1000次
  }
  cout << ans;//输出
}

```


---

## 作者：寒冰大大 (赞：0)

这个暴力很好想，设$f[i][j]$ 表示第$j$ 天在  $i$ 点能取得的最大收获

最后答案就是$\max\limits_{j=0}^{n*2}{f[1][j]-c*j^2}$

看上去貌似没啥可以优化的，我们考虑一下后面那个 $j^2$ 有什么用

我们不好找到最长的环的长度，因此我们设整个环的长度为 $w_{sum}$ ，显然，当 $j$ 在 $\sqrt{\frac{2*w_{sum}}{c}}$ 的时候，每次多 $1s$ 的时候答案无论如何都会减小了，无论 $w_i$ 如何，尽快跑回 $1$ 号点才是最优的

无论的时际运行要快$70%$ ($1.05s\to 276ms$)

然后就可以在 $O(n*\sqrt{\frac{2*w_{sum}}{c}})$ 时间复杂度内解决这题。

~~然后发现正常的不用队列的写法100多ms我直接暴毙~~

按理来说只需要前面的那部分改成循环然后后面的再用一个队列$O(N)$ 应该可以卡进100ms？

```cpp
#include<touwenjian.h>

#define int long long

using namespace std;

const int maxn=1020;

int n,m,head[maxn],size,wsum;
int f[maxn][maxn];
int target;
int a[maxn];

struct edge{
	int next,to;
}e[maxn*2];

inline void addedge(int next,int to)
{
	e[++size].to=to;
	e[size].next=head[next];
	head[next]=size;
}

int vis[maxn][maxn],ans;
int v[maxn];

void bfs()
{
	int looker=sqrt(wsum/target)+1;
	queue <pair<int,int> > q;
	q.push(make_pair(1,0));
	while(!q.empty())
	{
		int t=q.front().first;
		int tm=q.front().second;
		if(t==1&&ans<f[t][tm]-target*tm*tm) ans=f[t][tm]-target*tm*tm;
		q.pop();
		int i,j,k;
		if(tm+1<=looker)
		{
			for(i=head[t];i;i=e[i].next)
			{
				j=e[i].to;
				k=a[j];
				f[j][tm+1]=max(f[j][tm+1],f[t][tm]+k);
				if(!vis[j][tm+1]) vis[j][tm+1]=1,q.push(make_pair(j,tm+1));
			}
		}
		else
		{
			for(i=head[t];i;i=e[i].next)
			{
				j=e[i].to;
				k=a[j];
				f[j][tm+1]=max(f[j][tm+1],f[t][tm]+k);
				if(!v[j]) v[j]=1,q.push(make_pair(j,tm+1));
			}
		}
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	register int i,j;
	cin>>n>>m>>target;
	int t1,t2,t3;
	for(i=1;i<=n;i++) cin>>a[i],wsum+=a[i];
	for(i=1;i<=m;i++)
	{
		cin>>t1>>t2;
		addedge(t1,t2);
	}
	bfs();
	cout<<ans<<endl;
	return 0;
}

```



---

