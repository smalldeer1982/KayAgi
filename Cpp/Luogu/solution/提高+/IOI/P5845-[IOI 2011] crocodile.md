# [IOI 2011] crocodile

## 题目描述

考古学家 Benjamas 考察了神秘的鳄鱼地下宫殿之后需要设法逃离。这个地下宫殿包含 $N$ 个洞穴和 $M$ 条双向的通道。每条通道连接一对不同的洞穴，两个洞穴之间最多只有一条通道，在不同的通道上行走可能需要不同的时间。$N$ 个洞穴中有 $K$ 个洞穴是出口洞穴， Benjamas 可以从出口洞穴逃离。Benjamas 从 $0$ 号洞穴出发，她希望尽快地到达一个出口洞穴。

鳄鱼门卫要阻止 Benjamas 逃离宫殿。它可以通过机关来堵住任意一个的通道（任意时刻，只能堵住一个通道）。即无论何时，鳄鱼门卫堵住一个新的通道，则之前堵住的通道就会被打开。

Benjamas 逃离过程可以描述如下：每次她试图离开一个洞穴时，鳄鱼门卫都会封闭一条连接该洞穴的通道。Benjamas 只能选择没有被封闭的通道走到下一个洞穴。Benjamas 一旦进入一条通道，在她到达该通道的另一端前，鳄鱼门卫不能封闭这条通道。当 Benjamas到达下一个洞穴，鳄鱼门卫可以选择再封闭一条通道（可以是 Benjamas 刚刚走过的那条通道）。

Benjamas 需要设计一个逃生计划，确切地说，她希望有一系列指令告诉她如何逃生。

设 $A$ 是一个洞穴，如果 $A$ 是出口洞穴，Benjamas 可以直接逃生。否则，对洞穴 $A$，指令是下列形式中的一种：

- 在洞穴 $A$，优先选择一条通道到洞穴 $B$。如果该通道被封堵，则选择另一通道去洞穴 $C$。

- 不用考虑洞穴 $A$，按照逃生计划不会到达 $A$。

注意：数据保证不管鳄鱼门卫如何封闭通道，总能找到一个好的逃生计划保证 Benjamas 在有限时间内可以到达一个出口洞穴。在所有逃生计划中，在最坏情况下用时最短的逃生计划所用的时间定义为 $T$。

## 说明/提示

**数据范围**

对于 $100\%$ 的数据，$3 \le N \le 10^5$，$2 \le M \le 10^6$，测试数据保证 $T$ 存在，且 $T \le 10^9$。

## 样例 #1

### 输入

```
13 12 9
0 1 1
0 2 4
0 3 11
1 4 11
1 5 7
1 6 15
2 7 3
2 8 13
2 9 23
3 10 3
3 11 1
3 12 2
4 5 6 7 8 9 10 11 12
```

### 输出

```
13
```

# 题解

## 作者：zhouhuanyi (赞：9)

$[IOI2011]crocodile$

这题没有题解，我就来发一篇。

链接：https://www.luogu.com.cn/problem/P5845

题目描述:给定出发点$s$与$k$个终点，有一个鳄鱼门卫可以在每一轮堵住一条边，求最坏情况下走到终点要多长时间。

题解:从出发点像终点考虑十分复杂，不妨从终点向出发点考虑，由于鳄鱼门卫会挡住一条边，所以从一个与终点相邻的点到终点的最短路径一定会被挡住，只能走次短路。由于到该点的路是次短路，所以我们只能用次短路更新。以此类推，每个点每一次用到自己的次短路去扩展即可。

```
#include<iostream>
#include<queue>
using namespace std;
struct node
{
	int v,data,nxt;
};
node edge[10000001];
struct reads
{
	int num,data;
	bool operator < (const reads &a)const
	{
		return data>a.data;
	}
};
reads tmp;
int head[10000001],len;
int n,m,dis[10000001],dis2[10000001];
bool used[10000001];
priority_queue<reads>q;
void add(int x,int y,int z)
{
	edge[++len].v=y;
	edge[len].data=z;
	edge[len].nxt=head[x];
	head[x]=len;
	return;
}
reads make_reads(int x,int y)
{
	tmp.num=x;
	tmp.data=y;
	return tmp;
}
void dijkstra()
{
	int top;
	while (!q.empty())
	{
		top=q.top().num;
		q.pop();
		if (used[top])
			continue;
		used[top]=1;
		for (int i=head[top];i>0;i=edge[i].nxt)
		{
			if (dis[edge[i].v]>dis2[top]+edge[i].data)
			{
				dis2[edge[i].v]=dis[edge[i].v];
				dis[edge[i].v]=dis2[top]+edge[i].data;
				q.push(make_reads(edge[i].v,dis2[edge[i].v]));
			}
			else if (dis2[edge[i].v]>dis2[top]+edge[i].data)
			{
				dis2[edge[i].v]=dis2[top]+edge[i].data;
				q.push(make_reads(edge[i].v,dis2[edge[i].v]));
			}
		}
	}
	cout<<dis2[0]<<endl;
	return;
}
int main()
{
	int k,x,y,z;
	cin>>n>>m>>k;
	for (int i=0;i<=n-1;++i)
		dis[i]=dis2[i]=1e9;
	for (int i=1;i<=m;++i)
	{
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	for (int i=1;i<=k;++i)
	{
		cin>>x;
		dis[x]=dis2[x]=0;
		q.push(make_reads(x,0));
	}
	dijkstra();
	return 0;
}

---

## 作者：summ1t (赞：2)

## [P5845 [IOI2011] crocodile](https://www.luogu.com.cn/problem/P5845)
# Solution
**题目大意：** 给你 $n$ 个点 $m$ 条边的无向图，以及 $k$ 个终点，在每一次移动中都有一条边被堵住。问你最坏情况下，以 $0$ 为起点，到终点的最短路。

首先终点很多，从 $0$ 开始跑最短路实在太麻烦。正难则反，因为是无向图，所以考虑以 $k$ 个终点作为起点，找到 $0$ 的最短路。

再考虑如何处理限制，最坏情况下一定是鳄鱼门卫恰好堵在最短路上，这样的话我们只能去找次短路。而由于每次行动鳄鱼门卫都会堵住最短路上的边，所以更新最短路时，我们必须用次短路更新。

具体地，设 $dist_{i,0/1}$ 分别表示到$i$的最短路和次短路。

当我们从 $t$ 走到 $y$ 时，若 $dist_{y,0}>dist_{t,1}+w$，则我们令 $dist_{y,1}=dist_{y,0}$，然后再更新最短路。否则再考虑能否更新到 $y$ 的次短路。

答案即为 $dist_{0,1}$。

# Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define fi first
#define se second
const int N=1e5+10,M=1e6+10;

int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*f;
}

int n,m,k,dist[N][2],vis[N],head[N],tot,a[N];
priority_queue<PII,vector<PII>,greater<PII> > q;
struct node{
	int to,nxt,w;
}edge[M*2];

void add(int x,int y,int w){
	edge[++tot].to=y;
	edge[tot].w=w;
	edge[tot].nxt=head[x];
	head[x]=tot;
}

void dijkstra(){
	memset(dist,0x3f,sizeof(dist));
	for(int i=1;i<=k;i++) q.push(make_pair(0,a[i])),dist[a[i]][0]=dist[a[i]][1]=0;
	while(!q.empty()){
		int t=q.top().se;q.pop();
		if(vis[t]) continue;vis[t]=1;
		for(int i=head[t];i;i=edge[i].nxt){
			int y=edge[i].to;
			if(dist[y][0]>dist[t][1]+edge[i].w){
				dist[y][1]=dist[y][0];
				dist[y][0]=dist[t][1]+edge[i].w;
				q.push(make_pair(dist[y][1],y));//入队的是次短路
			}
			else if(dist[y][1]>dist[t][1]+edge[i].w){
				dist[y][1]=dist[t][1]+edge[i].w;
				q.push(make_pair(dist[y][1],y));
			}
		}
	}
}

int main(){
	
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){int x=read(),y=read(),w=read();add(x,y,w),add(y,x,w);}
	for(int i=1;i<=k;i++) a[i]=read();
	dijkstra();
	cout<<dist[0][1]<<endl;
	
	return 0;
}
```

---

## 作者：松鼠的星星 (赞：2)

先考虑什么是最坏情况，现在假设你是这只鳄鱼，你会怎么堵？

显然，你会堵在最短路上，或者说，是堵在以考古学家所在的点为起点的最短路上。

那么，作为这个考古学家，他的最佳选项是每次走除去被占用的道路的最小的次短路（因为无论在哪个点最短路都会被堵）。

我们先来看特殊情况，即给的图是一棵树，我们可以考虑树形 DP，我们记 $dis[x][0/1]$ 分别表示以 $x$ 为根的子树可到达的最短路和次短路的长度。那么对于出口洞穴 $k$，有 $dis[k][0] = dis[k][1] = 0$，对于其它节点，设 $len_{x,y}$ 为 $x$ 到 $y$ 的边的长度，有 
$$ dis[x][0] = \min_{y \in son(x)}(dis[y][1] + len_{x,y}) $$
$ dis[x][1] $ 同理，只不过是次小值。

对于一般情况，我们仍然可以延续这种思路，但是因为上面的方程是从下往上转移的，所以我们可以使用从出口向起点转移的方法，用类似 Dijkstra 的过程来进行转移，最后的答案就是 $dp[0][1]$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
typedef pair<int, int> PII;
vector<PII> node[MAXN];
int n, m, k;
int dis[MAXN];
int dis_s[MAXN];
bool vis[MAXN];
priority_queue<PII, vector<PII>, greater<PII> > q;
void dij()
{
    while (!q.empty())
    {
        int t = q.top().second;
        q.pop();
        if (vis[t])  continue;
        vis[t] = true;
        for (auto i : node[t])
        {
            if (dis[i.first] > dis_s[t] + i.second)
            {
                dis_s[i.first] = dis[i.first];
                dis[i.first] = dis_s[t] + i.second;
                q.push(make_pair(dis_s[i.first], i.first));
            }
            else if (dis_s[i.first] > dis_s[t] + i.second)
            {
                dis_s[i.first] = dis_s[t] + i.second;
                q.push(make_pair(dis_s[i.first], i.first));
            }
        }
    }
}
int main()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(dis_s, 0x3f, sizeof(dis_s));
    cin >> n >> m >> k;
    for (; m; m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        node[u].push_back(make_pair(v, w));
        node[v].push_back(make_pair(u, w));
    }
    int tmp;
    for (; k; k--)
    {
        cin >> tmp;
        q.push(make_pair(0, tmp));
        dis[tmp] = dis_s[tmp] = 0;
    }
    dij();
    cout << dis_s[0] << endl;
    return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

题意不过多赘述。

你注意到正向考虑很难，不如倒着考虑从 $k$ 个中电走向起点的最优解。

因为这个鳄鱼它每轮能够堵边，而且它够聪明。所以它每次一定是堵在某个最短路上的边。所以我们就不能走最短路，而是次短路。

所以我们就直接用次短路更新最短路就可以了。

时间复杂度 $O((n+m) \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct Point{
	int v,val;
	bool operator <(const Point &y)const{
		return val>y.val;
	}
};
int n,m,u,v,dis1[N],k,x,w,dis2[N];
vector <Point> e[N];
priority_queue <Point> q;
bool vis[N];
void dij(){
	while(!q.empty()){
		Point head=q.top();
		q.pop();
		if(vis[head.v])continue;
		vis[head.v]=1;
		for(int i = 0;i < e[head.v].size();i++){
			int v=e[head.v][i].v;
			if(dis1[v]>dis2[head.v]+e[head.v][i].val){
				dis2[v]=dis1[v],dis1[v]=dis2[head.v]+e[head.v][i].val;
				q.push((Point){v,dis2[v]});
			}
			else if(dis2[v]>dis2[head.v]+e[head.v][i].val){
				dis2[v]=dis2[head.v]+e[head.v][i].val;
				q.push((Point){v,dis2[v]});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	memset(dis1,0x3f,sizeof(dis1));
	memset(dis2,0x3f,sizeof(dis2));
	for(int i = 1;i <= m;i++){
		cin >> u >> v >> w;u++,v++;
		e[u].push_back((Point){v,w});
		e[v].push_back((Point){u,w});
	}
	for(int i = 1;i <= k;i++){
		cin >> u;u++;
		dis1[u]=dis2[u]=0ll;
		q.push((Point){u,0});
	}
	dij();
	cout << dis2[1];
	return 0;
}

```

---

