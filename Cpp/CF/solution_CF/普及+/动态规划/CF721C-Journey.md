# Journey

## 题目描述

Recently Irina arrived to one of the most famous cities of Berland — the Berlatov city. There are $ n $ showplaces in the city, numbered from $ 1 $ to $ n $ , and some of them are connected by one-directional roads. The roads in Berlatov are designed in a way such that there are no cyclic routes between showplaces.

Initially Irina stands at the showplace $ 1 $ , and the endpoint of her journey is the showplace $ n $ . Naturally, Irina wants to visit as much showplaces as she can during her journey. However, Irina's stay in Berlatov is limited and she can't be there for more than $ T $ time units.

Help Irina determine how many showplaces she may visit during her journey from showplace $ 1 $ to showplace $ n $ within a time not exceeding $ T $ . It is guaranteed that there is at least one route from showplace $ 1 $ to showplace $ n $ such that Irina will spend no more than $ T $ time units passing it.

## 样例 #1

### 输入

```
4 3 13
1 2 5
2 3 7
2 4 8
```

### 输出

```
3
1 2 4 
```

## 样例 #2

### 输入

```
6 6 7
1 2 2
1 3 3
3 6 3
2 4 2
4 6 2
6 5 1
```

### 输出

```
4
1 2 4 6 
```

## 样例 #3

### 输入

```
5 5 6
1 3 3
3 5 3
1 2 2
2 4 3
4 5 2
```

### 输出

```
3
1 3 5 
```

# 题解

## 作者：_ReClouds_ (赞：9)

首先可以发现，本题实际上类似一个 DAG 上的背包问题。

那么我们有一个很显然的做法：

设 $f_{v,t}$ 表示从点 $1$ 到达点 $v$，路径长度为 $t$ 的所有方案中的最大点数，转移方程平凡，这里略去。

但是 $T \le 10^9$，这样做空间会炸飞。

可喜的是，答案一定是小于等于 $n$ 的，同时 $n \leq 5000$，这启发我们可以考虑 $O(n^2)$ 空间的算法。

我们换个角度思考：既然枚举距离求点的最大值不行，那么**枚举点数求距离的最小值**是否可行？

观察数据范围，在复杂度上这显然是可行的。

所以我们试着考虑转移方程：

设 $f_{v, t}$ 表示从点 $1$ 到达点 $v$，经过点数为 $t$ 的所有方案中的**最短路径**。

那么我们有转移方程：（其中 $prefix(v)$ 表示点 $v$ 的前驱，即所有能够到达点 $v$ 的点，$w$ 表示边 $u\to v$ 的长度）

$$
f_{v, t} = \min_{u \in prefix(v)} (f_{u,t - 1} + w)[f_{u,t - 1} + w \le T]
$$

为什么是最短路径呢？因为我们并不关心路径的长度到底是多少，只关心它是否不超过 $T$。从贪心的角度考虑，这里选择最短路径显然最优。

转移的同时，我们记录一个 $g_{v,t}$，表示 $f_{v,t}$ 是由哪个 $u$ 转移过来的，方便最后输出答案。

不过，需要注意一点：数据范围中没有说 DAG 的源点一定是点 $1$！

虽然点 $1$ 的所有直接前驱和间接前驱都不会影响到答案，但是它们会影响拓扑排序的过程。

比如上面的边 $2 \to 3$，虽然点 $2$ 在拓扑排序中没有访问到，但是这条边对点 $3$ 的入度仍然存在 $1$ 的影响。

所以我们需要先 DFS 一遍，把点 $1$ 的所有直接前驱和间接前驱对于拓扑图中点的入度影响去掉。然后，我们就可以从点 $1$ 开始跑这个 DP 了。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<cstring>
#include<vector>
#include<queue>

#define MAXN 5005

using namespace std;

int n, m, k, in[MAXN], f[MAXN][MAXN], g[MAXN][MAXN];
bool vis[MAXN];
vector<pair<int, int> > vec[MAXN];

inline void DFS(int u)
{
    vis[u] = true;
    for(register vector<pair<int, int> > :: iterator it = vec[u].begin(); it != vec[u].end(); it++) if(!vis[it -> first]) DFS(it -> first);
    return;
}

inline void Toposort()
{
    queue<int> q;
    q.push(1), f[1][1] = 0, g[1][1] = 1;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(register vector<pair<int, int> > :: iterator it = vec[u].begin(); it != vec[u].end(); it++)
        {
            int v = it -> first, w = it -> second;
            for(register int i = 1; i <= n; i++)
            {
                if(g[u][i - 1] && f[u][i - 1] + w <= k && f[u][i - 1] + w < f[v][i])
                {
                    f[v][i] = f[u][i - 1] + w;
                    g[v][i] = u;
                }
            }
            --in[v]; if(!in[v]) q.push(v);
        }
    }
    return;
}

inline void Output(int u, int k)
{
    if(u > 1) Output(g[u][k], k - 1);
    printf("%d ", u);
    return;
}

int main()
{
    #ifdef FILE
        freopen("Input.in", "r", stdin);
        freopen("Output.out", "w", stdout);
    #endif
    scanf("%d%d%d", &n, &m, &k);
    for(register int i = 1; i <= m; i++)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        vec[u].push_back(make_pair(v, w));
        ++in[v];
    }
    memset(f, 0x3F, sizeof f);
    DFS(1);
    for(register int i = 1; i <= n; i++) if(!vis[i]) for(register vector<pair<int, int> > :: iterator it = vec[i].begin(); it != vec[i].end(); it++) --in[it -> first];
    Toposort();
    int t;
    for(t = n; t > 1; t--) if(g[n][t]) break;
    printf("%d\n", t);
    Output(n, t);
    return 0;
}
```

---

## 作者：kouylan (赞：6)

## Journey题解
### 【题意】
有一个n个点m条有向边的无环图，求从1到n总长度不超过k，且经过点最多的路径。
### 【分析】
### 很自然的，我们想到了dp
1. **dp的状态如何设计？**
 
* 告诉大家一个小技巧——在同一个题目而且dp有许多方法都能过的情况下，通常dp维数越多，越简单。所以看数据范围，$n<=5000$，那就设计二维的dp。

* **我们让$f[i][j]$表示从1到i经过j个点的最短路径**(无解就是INF)，最后只要求$f[n][j]<=k$即可

* 还有一个小点，dp要按照拓扑序的顺序(而不是节点序)，这样才能保证每个点都是最小值，又因为是有向无环图(DAG)，所以这样做是成立的。

2. **路径如何记录？**

* 直接记录nm条路径会MLE(此时空间复杂度为$n^2m$)，所以类似于dp，对于一个点x，我们记录$pre[x][j]$，表示从1走到x，经过了j个点，的上一个节点编号，求路径时直接回溯或者用stack模拟(空间复杂度为$nm$)。

### 下面是AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n,m,d; // d就是题中的k
int f[5005][5005],pre[5005][5005],mx; 
int ee,h[5005],nex[5005],to[5005],val[5005]; // 前向星
int rdu[5005];
vector<int> s; // 拓扑序
stack<int> path; // 最终路径

void addedge(int x,int y,int z)
{
	nex[++ee] = h[x];
	to[ee] = y;
	val[ee] = z;
	h[x] = ee;
}

void topo() // 拓扑排序
{
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(rdu[i]==0)
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		s.push_back(x);
		for(int i=h[x];i;i=nex[i])
			if((--rdu[to[i]])==0)
				q.push(to[i]);
	}
}

signed main()
{
	memset(f,INF,sizeof(f));
	memset(pre,-1,sizeof(pre));
	cin>>n>>m>>d;
	for(int i=1,x,y,z;i<=m&&cin>>x>>y>>z;i++)
	{
		addedge(x,y,z);
		rdu[y]++;
	}
	topo(); // 确定dp的顺序
	f[1][1] = 0; // 从1到1且经过一个点的路径长是0
	for(int k=0;k<s.size();k++)
	{
		int x=s[k];
		for(int i=h[x];i;i=nex[i])
			for(int j=2;j<=n;j++) // 枚举经过点数
				if(f[x][j-1]+val[i]<f[to[i]][j]) // 如果当前路径和比原先的好
				{
					f[to[i]][j] = f[x][j-1]+val[i]; // 更新
					pre[to[i]][j] = x; // 记录路径中的上一个点
				}
	}
	for(int i=n;i>=1;i--)
		if(f[n][i]<=d)
		{
			mx = i; // 最多能经过mx个点
			break;
		}
	cout<<mx<<endl;
	int pos=n,dep=mx;
	while(pos!=-1)
	{
		path.push(pos);
		pos = pre[pos][dep]; // 用stack回溯路径
		dep--;
	}
	while(!path.empty())
	{
		cout<<path.top()<<' '; // 输出路径
		path.pop();
	}
	cout<<endl;
	
	return 0;
}
```
祝大家AC愉快！

---

## 作者：傅思维666 (赞：4)

## 题解：

思路：DAG上DP。为了保证无后效性，采用先拓扑排序，再在拓扑序上进行拓展DP的方式。

为什么拓扑排序就能保证DP的无后效性呢？

因为拓扑序的性质是，对于DAG上的任意一个点，它的父亲们在拓扑序中出现的位置都在它之前。这也就保证了，处理出拓扑序后再DP，能使得每个状态阶段都是正确的答案（因为转移而来的节点都被处理完了）。

所以就是先topsort再DP。DP过程中需要记录一个前缀序列。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<iostream>
using namespace std;
const int maxn=5002;
int n,m,dist,maxx;
int tot,to[maxn],nxt[maxn],val[maxn],head[maxn];
int rudu[maxn];
queue<int> q;
vector<int> vec;
stack<int> st;
int dp[maxn][maxn];
//dp[i][j]表示从1-i，经过j个点的最短距离
int pre[maxn][maxn],ans[maxn],cnt;
void add(int x,int y,int z)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	val[tot]=z;
	head[x]=tot;
}
void topsort()
{
	for(int i=1;i<=n;i++)
		if(!rudu[i])
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vec.push_back(x);
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			rudu[y]--;
			if(!rudu[y])
				q.push(y);
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&dist);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		rudu[y]++;
	}
	topsort();
	memset(dp,127,sizeof(dp));
	dp[1][1]=0;
	for(int k=0;k<vec.size();k++)
	{
		int x=vec[k];
		for(int i=head[x];i;i=nxt[i])
			for(int j=2;j<=n;j++)
			{
				int y=to[i];
				if(dp[x][j-1]+val[i]<dp[y][j])
				{
					dp[y][j]=dp[x][j-1]+val[i];
					pre[y][j]=x;
				}
			}
	}
	for(int i=n;i>=1;i--)
		if(dp[n][i]<=dist)
		{
			maxx=i;
			printf("%d\n",i);
			break;
		}
	int pos=n,dep=maxx;
	while(pos)
	{
		st.push(pos);
		pos=pre[pos][dep];
		dep--;
	}
	while(!st.empty())
	{
		cout<<st.top()<<' ';
		st.pop();
	}
	cout<<endl;
	return 0;
}
```



---

## 作者：Purslane (赞：3)

## Solution

显然 DAG 上 DP . 设 $dp_{i,j}$ 表示边长总和为 $j$ , 到 $i$ 的最长路径 . 转移时 $dp_{v,j} = \text{max} \{dp_{u,j-w} \} + 1 $ , 类似背包问题 .

但是第二位过大 , 可是答案值域比较小 . 考虑背包问题的一个变形 : [AT4526](https://www.luogu.com.cn/problem/AT4526) . 重新设定状态 : $ dp_{i,j}$ 表示到 $i$ , 经过 $j$ 个点最短长度 . 统计答案时在 $dp_n$ 倒叙找到第一个小于等于 $T$ 的 $j$ 即可 . 

可以在转移时记录每一个点的前驱 . 注意不能开 `long long` 会暴空间 . 转移时如果 $dp_{u,i}+w > T$ , 那么直接不合法 , 舍掉即可 .

DAG 上 DP 可以记忆化 , 也可以拓扑排序 . 这里使用了拓扑排序 .

[code](https://codeforces.com/contest/721/submission/149975800) .

---

## 作者：To_our_starry_sea (赞：1)

# CF721C Journey 题解

## 思路
发现大部分题解用的都是拓扑排序，那么我就来发一篇记忆化的题解。

~~主要是图论太差。~~

首先我们可以考虑朴素做法：

设 $f_{v,t}$ 表示从点 $1$ 到达点 $v$，路径长度为 $t$ 时的所有方案中的最大点数。但 $T \le 10^9$，显然空间会炸飞。

进而我们可以设 $f_{v,t}$ 表示从点 $1$ 到达点 $v$，经过点数为 $t$ 时的所有方案中的最短路径长度。

于是我们有转移方程：

$f_{v, t} = \min_{u \in prefix(v)} (f_{u,t - 1} + w)[f_{u,t - 1} + w \le T]$

其中 $prefix(v)$ 表示点 $v$ 的前驱，即所有能够到达点 $v$ 的点，$w$ 表示边权。

之后跑一下记忆化搜索就行了。但值得注意的是应将已搜索但无解的状态值设为 $-2$，避免无用状态多次求解。而路径的输出可以通过边权的转移递归求解。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=5005;
int n,m,cnt=0,head[MAXN];
ll W,dp[MAXN][MAXN];
struct edge{
	int to,next;
	ll w;
}e[MAXN<<2];
inline ll minn(ll x,ll y){return x<y?x:y;}
inline void print(int u,int t){//递归求出路径 
	if(u==1){
		printf("1 ");
		return;
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(dp[v][t-1]==-1||dp[v][t-1]==-2||dp[v][t-1]+e[i].w!=dp[u][t]) continue;
		print(v,t-1);
		printf("%d ",u);
		return;
	}
}
inline ll dfs(int u,int t){//记忆化求从1到u经过t个点时的最短路径 
	//cout<<u<<" "<<t<<endl;
	if(t==1&&u!=1) return -2;
	if(dp[u][t]!=-1||dp[u][t]==-2) return dp[u][t];
	ll res=-2;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		ll now=dfs(v,t-1);
		if(now==-1||now==-2) continue;
		if(now+e[i].w>W) continue;
		if(res==-2) res=now+e[i].w;
		else res=minn(res,now+e[i].w);
	}
	return dp[u][t]=res;
}
inline void add(int u,int v,ll w){
	cnt++;
	e[cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
inline ll R(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int main(){
	n=read(),m=read(),W=R();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		ll w=R();
		add(v,u,w);//注意建反向图 
	}
	memset(dp,-1,sizeof(dp));
	dp[1][1]=0;
	int ans=0;
	for(int i=1;i<=n;i++){//从1至n枚举 记忆化求dp[n][i] 
		ll now=dfs(n,i);
		if(now!=-1&&now!=-2) ans=max(ans,i);
	}
	printf("%d\n",ans);
	print(n,ans);
	return 0;
}
```

蒟蒻的第一篇题解，如有谬误还请大家指正。

---

## 作者：hulean (赞：1)

不会Topo，只能写SPFA了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5000+10;
int n,m,k;
struct Node
{
    int to,next;
    int w;
}edge[MAXN];//链式前向星存图
int head[MAXN],cnt;
int d[MAXN][MAXN];//d[i][j]表示当前在第i号结点，经过了j条边，所经过的最小路程
bool inq[MAXN][MAXN];//判断是否在队列中
int pre[MAXN][MAXN];//记录路径
typedef pair<int,int>p;
inline int read()
{
    int tot=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9'){tot=(tot<<1)+(tot<<3)+c-'0';c=getchar();}
    return tot;
}
inline void add(int x,int y,int z)
{
    edge[++cnt].to=y;
    edge[cnt].next=head[x];
    edge[cnt].w=z;
    head[x]=cnt;
}
inline int SPFA()
{
    memset(d,0x3f,sizeof(d));
    queue<p>q;
    q.push(p(1,0));
    d[1][0]=0;inq[1][0]=1;//初始化
    while(q.size())
    {
        p now=q.front();
        q.pop();
        int x=now.first,y=now.second;//取出队首元素
        inq[x][y]=0;
        for(int i=head[x];i;i=edge[i].next)//遍历相邻结点
        {
            int v=edge[i].to;
            if(d[x][y]+edge[i].w<d[v][y+1]&&d[x][y]+edge[i].w<=k)//更新其他结点的值
            {
                d[v][y+1]=d[x][y]+edge[i].w;
                pre[v][y+1]=x;//记录下路径
                if(!inq[v][y+1])//避免重复搜索
                {
                    inq[v][y+1]=1;
                    q.push(p(v,y+1));
                }
            }
        }
    }
}
inline void print(int now,int t)//递归输出
{
    if(pre[now][t]==0){if(now==1)printf("%d ",now);return;}
    print(pre[now][t],t-1);
    printf("%d ",now);
}
int main()
{
    n=read();m=read();k=read();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read(),z=read();
        add(x,y,z);
    }
    SPFA();
    int i;
    for(i=n;i>=1;i--)
        if(d[n][i]<=k)break;//找到最优解
    printf("%d\n",i+1);//由于记录的是经过了几条边，所以结点数还要+1
    print(n,i);
    printf("\n");
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：1)

简单题。

设计 dp 状态，第一维显然是下标。把权值设进转移状态是不明智的，考虑转化问题，第二维是经过了多少个点，由此找到最大的满足最短路不大于 $T$ 的即可。 

dp 是需要无后效性的，对此进行拓扑排序。维护一个队列，找到当前入度为 $0$ 的点，然后对每个出边枚举点数进行暴力转移即可。注意初始值全部定为无穷大。

记录方案即为记录每个状态是从哪个状态转移来的即可。

因为空间很紧，对权值和大于无穷大的直接取无穷大，记录从哪里转移来的数组开 `short`，可以省空间。

注意还有可能有无法从起点到达的点向普通点连边的情况，这样会直接统计入度会出错，所以还需要搜一遍求入度。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=5010;
const int inf=1e9+1;
int n,m,k,f[N][N],in[N];
short g[N][N],h[N][N];
bool vis[N][N];
vector<int>a[N],b[N];
void calc(int x,int y,int u,int v,int w){
	int val=min(f[u][v]+w,inf);
	if(val>=f[x][y])
		return;
	f[x][y]=val;
	g[x][y]=u;
	h[x][y]=v;
}
void dfs(int u){
	for(int v:a[u]){
		if(vis[u][v])
			continue;
		in[v]++;
		vis[u][v]=1;
		dfs(v);
	}
}
void solve(){
	queue<int>q;
	q.push(1);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			f[i][j]=inf;
	f[1][1]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<a[u].size();i++){
			int v=a[u][i],w=b[u][i];
			for(int j=1;j<n;j++)
				calc(v,j+1,u,j,w);
			in[v]--;
			if(!in[v])
				q.push(v);
		}
	}
}
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		a[u].push_back(v);
		b[u].push_back(w);
	}
	dfs(1);
	solve();
	int p=0;
	for(int i=n;i>=1;i--)
		if(f[n][i]<=k){
			p=i;
			break;
		}
	cout<<p<<'\n';
	stack<int>st;
	int x=n,y=p;
	while(1){
		st.push(x);
		if(x==1)
			break;
		int u=g[x][y],v=h[x][y];
		x=u,y=v;
	}
	while(!st.empty()){
		cout<<st.top()<<' ';
		st.pop();
	}
	return 0;
}

```

---

## 作者：Plozia (赞：1)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/113508373)

题目给了我们一张 DAG，对于 DAG 常用的方法就是拓扑排序。

题目要求一条从 1 到 $n$ 的路径， 点数尽量多但是距离不能超过 $k$，那么我们考虑 DP 解决这个问题。

设 $f_{i,j}$ 表示从 1 开始经过 $i$ 个点，到达 $j$ 点的最短路径，那么首先满足最优性。

而拓扑排序的一条重要性质就是只有入度为 0 的点才能处理，恰好满足无后效性。

于是我们就可以设计出这样的状态转移方程：

$$f_{i+1,v}=\min\{f_{i,u}+dis_{u->v}|u \in S\}$$

$S$ 表示所有能够到达 $u$ 的点集。

初始状态为 $f_{1,1}=0$，其余为正无穷。

同时为了记录方案，我们还需要一个 $g_{i,j}$ 表示当前状态是由哪个点转移而来的。

最后输出时，从大到小枚举 $i \in [1,n]$，找到第一个 $f_{i,n} \ne \inf$ 就输出答案以及方案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 5000 + 10;
int n, m, f[MAXN][MAXN], g[MAXN][MAXN], t, cnt[MAXN];
vector <int> Next[MAXN], Num[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void topsort()
{
	queue <int> q;
	for (int i = 1; i <= n; ++i)
		if (!cnt[i]) q.push(i);
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = 0; i < Next[x].size(); ++i)
		{
			int u = Next[x][i], w = Num[x][i];
			for (int j = 1; j <= n; ++j)
			{
				if (f[j][x] == 0x3f3f3f3f) continue;
				if (f[j][x] + w > t) continue;
				if (f[j + 1][u] > f[j][x] + w) {f[j + 1][u] = f[j][x] + w; g[j + 1][u] = x;}
			}
			--cnt[u];
			if (cnt[u] == 0) q.push(u);
		}
	}
}

void print(int last, int now)
{
	if (last > 1) print(last - 1, g[last][now]);
	printf("%d ", now);
}

int main()
{
	n = read(), m = read(), t = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read(), z = read(); cnt[y]++;
		Next[x].push_back(y), Num[x].push_back(z);
	}
	memset(f, 0x3f, sizeof(f));
	f[1][1] = 0;
	topsort();
	for (int i = n; i >= 1; --i)
		if (f[i][n] < 0x3f3f3f3f)
		{
			printf("%d\n", i);
			print(i, n); printf("\n");
			return 0;
		}
}
```

---

## 作者：Alarm5854 (赞：1)

这种求有向无环图的题目很自然的想法就是动态规划，再看数据范围，发现 $n\le 5\times 10^3$ ，空间限制为 $256\text{MB}$，于是，可以用二维的动态规划。

记 $f_{i,j}$ 为经过 $i$ 个点，终点为 $j$，能走的最短路径，$g_{i,j}$ 为转移到 $f_{i,j}$ 这个状态的前一个状态的 $j$。利用拓扑排序，来转移后面的状态，转移方程为 $f_{i,u}=\min(f_{i-1,v}+\text{dis}(u,v))$，同时，遇到更小的值的时候，要更新 $g_{i,u}$。初始状态 $f_{1,1}=0$。

最后，倒序循环，找到第一个 $i$ 使得 $f_{i,j}\le k$，输出方案即可。

```cpp
#include<ctime>
#include<queue>
#include<cctype>
#include<cstdio>
const int N = 5e3 + 7;
const int INF = 0x3f3f3f3f;
using namespace std;
inline int read() {
	int x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
int n, m, k, tot, in[N], head[N], f[N][N], g[N][N];
struct Edge {
	int to, val, nxt; Edge(int to = 0, int val = 0, int nxt = 0): to(to), val(val), nxt(nxt){}
} e[N];
void add(int u, int v, int w) {
	e[++tot] = Edge(v, w, head[u]);
	head[u] = tot, ++in[v];
}
void out(int x, int p) {
	if (x > 1) out(x - 1, g[x][p]);
	printf("%d ", p);
}
void topo() {
	queue<int> q;
	for (int i = 1; i <= n; ++i) if (!in[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to, w = e[i].val;
			for (int j = 1; j <= n; ++j) {
				if (f[j][u] == INF) continue;
				if (f[j][u] + w > k) continue;//防止炸int，以节省空间，否则会炸
				if (f[j + 1][v] > f[j][u] + w)
					f[j + 1][v] = f[j][u] + w, g[j + 1][v] = u;
			}
			if (!--in[v]) q.push(v);
		}
	}
}
int main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j) f[i][j] = INF;
	f[1][1] = 0;
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		add(u, v, w);
	}
	topo();
	for (int i = n; i; --i)
	if (f[i][n] < INF) {//所以，这里只要小于INF，就一定小于等于k，输出方案
		printf("%d\n", i);
		out(i, n); break;
	}
	return 0;
}
```

时间复杂度与空间复杂度均为 $O(n^2)$。

---

## 作者：Ryder00 (赞：0)

题意清晰，不再阐述。

## 思路
注意到这是一张 DAG，容易想到拓扑排序。观察到 $n,m$ 同阶且都在平方级别，而值域很大，转换 DP 思路。设 $f_{i,j}$ 表示第 $i$ 个点，是从起点开始（不算起点）经过的第 $j$ 个点，路上产生的最小费用。容易得到方程：

$f_{i,j}= \min \left\{ {f_{k,j-1}+dis_{k,i}} \right\}$

其中 $k$ 是 $i$ 的前驱。

所以一边进行拓扑排序，一边进行 DP。最后输出方案，只需要逆流回去寻找即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=5e3+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,m,k,dis[N][N],in[N],f[N][N];
vector<int> to[N],from[N];
queue<int> q;
stack<int> ans;
void work(int tim){
    int x=n;
    ans.push(x);
    while(x!=1){
        for(int y:from[x]){
            if(f[x][tim]==f[y][tim-1]+dis[y][x]){
                ans.push(y);
                x=y,tim--;
                break;
            }
        }
    }
}
void solve(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=w;
        to[u].pb(v);
        from[v].pb(u);
        in[v]++;
    }
    for(int i=1;i<=n;i++){
        if(!in[i]){
            q.push(i);
        }
    }
    memset(f,0x3f,sizeof(f));
    f[1][0]=0;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int y:to[x]){
            in[y]--;
            if(!in[y]) q.push(y);
        }
        if(x==1) continue;
        for(int j=1;j<n;j++){
            for(int y:from[x]){
                f[x][j]=min(f[x][j],f[y][j-1]+dis[y][x]);
            }
        }
    }
    for(int i=n;i>=1;i--){
        if(f[n][i]<=k){
            cout<<i+1<<endl;
            work(i);
            while(!ans.empty()){
                cout<<ans.top()<<" ";
                ans.pop();
            }
            return ;
        }
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0);
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

记 $f_{i,j}$ 表示到点 $i$，总共经过 $j$ 个点，需要距离的最小值。

接下来考虑转移。如果一个点 $u$，到达该点时经过了 $k$ 个点，能到达点 $v$，那么 $f_{v,k+1}=\min(f_{v,k+1},f_{u,k}+w)$，$w$ 是两点间的边权。

然后就是记录路径的问题了。可以用 $pre_u$ 表示点 $u$ 由 $pre_u$ 来，那么最后只要从点 $n$ 开始，不断找到这个点的 $pre$ 值，直到为 $1$ 即可。

跑一遍记忆化搜索就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
struct edge{
	int to,nxt,w;
}e[N];
int n,m,k,cnt,head[N],pre[N],lstid,dp[N][N],ans,id[N],ttt;//到第i个点，经过j个点距离最小值 
bool flag[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	e[cnt].w=w;
	head[u]=cnt;
}
void dfs(int u,int dis,int w){//到哪个点，距离多少，点数 
	//cout<<u<<" "<<dis<<" "<<w<<endl;
	//flag[u]=1;
	if(dis>k)return;
	if(w>=ans&&u==n){
		ans=w;
		lstid=u;
		ttt=0;
		id[++ttt]=lstid;
		for(int i=1;i<ans;i++){
			id[++ttt]=pre[lstid];
			lstid=pre[lstid];
		}
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(dp[v][w+1]>dp[u][w]+e[i].w){
			dp[v][w+1]=dp[u][w]+e[i].w;
			pre[v]=u;
			dfs(v,dis+e[i].w,w+1);
		}
	}
}
signed main(){
	freopen("std.in","r",stdin);
	memset(dp,0x3f,sizeof(dp));
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u,v,w;u=read();v=read();w=read();
		add(u,v,w);;
	}
	for(int i=1;i<=n;i++)dp[i][1]=0;
	//for(int i=1;i<=n;i++){
		//memset(flag,0,sizeof(flag));
		dfs(1,0,1);
	//}
	printf("%lld\n",ans);
	for(int i=ttt;i>=1;i--)printf("%lld ",id[i]);
	return 0;
}


```


---

## 作者：Sktic (赞：0)

[CF721C  Journey](https://www.luogu.com.cn/problem/CF721C)

2022/8/24 upd : 修改了部分 latex 。


题目简介： 在 DAG 上找到一条从点 $1$ 到点 $n$ 的路径，并使得在总距离 $\le k$ 的情况下经过尽可能多的点。



看到数据范围， $1\le n\le 5\times10^3$ ，可以考虑 $O(n^2)$ 的 DAG 上动态规划。



设 $dp_{i,j}$ 表示从点 $1$ 走到点 $i$ 时路径长度为 $j$ 经过的最大点数。那么可以得到转移方程：
$$
dp_{i,j}=\max\{dp_{x,j-w}+1\}(x\overset{w}\to i)
$$
但是由于本题的数据范围是 $1\le T\le10^9$ 因此开二位数组的话会喜提 MLE 。



考虑变形 $dp$ 模式，将 $dp_{i,j}$ 的意义改为从点 $1$ 走到点 $i$ 时经过 $j$ 个点的最短长度。因为此时的 $i,j\le n\le 5\times10^3$ ，所以不会炸空间。可以得到转移方程：
$$
\left\{
\begin{aligned}
&dp_{1,1}=0\\
&dp_{i,j}=\min\{dp_{x,j-1}+w\}(x\overset{w}\to i)\\
&ans=\max\{j\}(dp_{n,j}\le T)
\end{aligned}
\right.
$$
于是只要将整个图进行一遍拓扑排序，再按照拓补序进行 $\text{dp}$ 即可。



对于存路径，我们记录一个数组 $pre_{i,j}$ ，表示从点 $1$ 走到点 $i$ 时经过的第 $j$ 个点的前驱，那么对于答案来说，我们可以用一个栈来模拟路径。



于是时间复杂度 $O(n^2)$ ，空间复杂度 $O(nm)$ ，可以通过本题。



AC code：

```C++
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=5e3+10;
int dp[maxn][maxn],pre[maxn][maxn]; 
int to[maxn],vis[maxn],head[maxn],nxt[maxn],cnt;
int upd[maxn];
int topology[maxn],tot;
stack<int>stk;
queue<int>q;
void topu(int n)
{
	for(int i=1;i<=n;i++)
		if(upd[i]==0)
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		topology[++tot]=x;;
		for(int i=head[x];i!=0;i=nxt[i])
			if(!(--upd[to[i]]))
				q.push(to[i]);
	}
}
int main()
{
	int n,m,t;
	ios::sync_with_stdio(false);
	cin>>n>>m>>t;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		nxt[++cnt]=head[u];
		to[cnt]=v;
		vis[cnt]=w;
		head[u]=cnt;
		upd[v]++;
	}
	topu(n);
	memset(dp,INF,sizeof(dp));
	dp[1][1]=0;
	for(int k=1;k<=tot;k++)
	{
		int cur=topology[k];
		for(int i=head[cur];i!=0;i=nxt[i])
		{
			for(int j=2;j<=n;j++)
			{
				if(dp[cur][j-1]+vis[i]<dp[to[i]][j])
				{
					dp[to[i]][j]=dp[cur][j-1]+vis[i];
					pre[to[i]][j]=cur;
				}
			}
		}		
	}
	int ans=0;
	for(int k=n;k>=1;k--)
	{
		if(dp[n][k]<=t)
		{
			ans=k;
			break;
		}
	}
	cout<<ans<<endl;
	int pos=n;
	while(pos)
	{
		stk.push(pos);
		pos=pre[pos][ans];
		ans--;
	}
	while(!stk.empty())
	{
		cout<<stk.top()<<" ";
		stk.pop();
	}
	return 0;
}
```



---

## 作者：Supor__Shoep (赞：0)

众所周知，这是一道典型的 DAG 上的 DP。

首先一谈到 DAG 上的 DP 我们一定会想到拓扑排序，拓扑排序呢就是给一个图的所有节点进行排序，这刚好和我们这道题有那么一丢丢关系。于是本题就自然转化成了拓扑排序求最小的花费。

可是这道题加了一个限制条件，也就是限制了走的路程。其实也不难，只用拿求到的花费，找到其中满足条件的最大值就可以了。而存路径更是老掉牙的套路了，在最长上升子序列和最长公共子序列中我们都有用到，也就是用数组记录。

这里我详细讲一下动态规划的过程。

定义 $dp_{i,j}$ 表示从第一个点到第 $i$ 个点经过 $j$ 个点的最小路程。我们枚举点 $t$，这个点 $t$ 指的是能够到达第 $l$ 个节点的所有节点之一，而 $l$ 也是枚举的 $2$ 到 $n$ 的终止节点，定义 vector 数组 $g_{i,j}$，其作用将在后文代码呈现，我们可以得到：

$$dp[g_{t,i~first}][j]=max(dp[g_{t,i~first}][j],dp[t][j-1]+g_{t,i~second})$$

原因是从 $1$ 到 $i$ 的路径是由从 $1$ 到 $i-1$ 加上从 $i-1$ 到 $i$ 的路径相加得到的。为了方便未来输出答案，我们可以用另一个二维数组进行储存，但是这个答案是逆序储存的，所以我们在输出是要再逆序处理输出，毕竟负负得正。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int in[100005];
int n,m,t;
vector< pair<int,int> > g[100005];
int dp[5005][5005];
//定义状态：dp[i][j]表示从第一个节点到第i个节点经过j个点的最少路程 
int pre[5005][5005];
vector<int> num;
void work()//拓扑 
{
    queue<int> que;
    memset(dp,0x3f,sizeof(dp));
    dp[1][1]=0;//初始化，1到1不用走，故为0 
    for(int i=1;i<=n;i++)
	{
        if(!in[i])    que.push(i);
    }
    while(!que.empty())
	{
        int t=que.front();
        que.pop();
        for(int i=0;i<g[t].size();i++)
		{
            in[g[t][i].first]--;//已经判断此节点，不用二次操作，因此直接减掉 
            for(int j=2;j<=n;j++)
			{
                if(dp[g[t][i].first][j]>dp[t][j-1]+g[t][i].second)//由于要记录，不能直接max 
				{
                    dp[g[t][i].first][j]=dp[t][j-1]+g[t][i].second;
                    pre[g[t][i].first][j]=t;//记录节点顺序 
                }
            }
            if(!in[g[t][i].first])    que.push(g[t][i].first);//变成起始节点继续搜索 
        }
    }
}
int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=m;i++)
	{
        int u,v,c;
        cin>>u>>v>>c; 
        g[u].push_back(pair<int,int> {v,c});
        in[v]++;
    }
    work();
    int res=-1;
    for(int i=n;i>=1;i--)
    {
    	if(dp[n][i]<=t)
    	{
    		res=i;
    		break;
		}
	}
    cout<<res<<endl;
    int now=n;
    while(res)
	{
        num.push_back(now);
        now=pre[now][res];
        res--;
    }
    for(int i=num.size()-1;i>=0;i--)    cout<<num[i]<<" ";//逆序输出 
    return 0;
}
```

---

## 作者：JWRuixi (赞：0)

看一眼标签可以无脑动规，本篇将讲解如何动规。

- **题意**

在一个 DAG 上进行枚举，查找头到尾的最大点数，距离小于 $T$。

- **分析**

首先可以确定算法为树上动规，考虑第一维为节点编号：

设 $g_{u,k}$ 表示第 $u$ 个节点距离为 $k$ 的最大点数。

看一看数据范围，明显会炸空间。

所以反向，在三个变量中只能取点数和节点编号：

设 $g_{u,k}$ 表示第 $u$ 个节点点数为 $k$ 的最小距离。

于是推出朴素的表达式：

$$g_{v, k} = \min(g_{v, k}, g_{u, k - 1})$$

同时关注到还需要维护路径，于是我们设出一个记录路径前驱的数组 $pre$

对于 DAG 图，我们考虑直接用拓扑排序来优化时间。

- **code**

```cpp
#include <bits/stdc++.h>
using namespace std;
//
namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

const int maxn = 5005;

struct edge {
	int v, nxt, w;
} e[maxn];

int n, m, T, g[maxn][maxn], pre[maxn][maxn], ans, tot, head[maxn], in[maxn];

int a[maxn], cnt;

void add (int u, int v, int w) {
	e[++tot] = {v, head[u], w};
	head[u] = tot;
}

void topo () {
	queue <int> q;
	for (int i = 1; i <= n; i++) if(!in[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].w;
			for (int j = 1; j <= n; j++) {
				if (g[v][j] > g[u][j - 1] + w && g[u][j - 1] + w <= T) {//优化一下，只有在满足时间的情况下才继续更新
					g[v][j] = g[u][j - 1] + w;
					pre[v][j] = u;
					if (v == n && j > ans) ans = j;
				}
			}
			if (!--in[v]) q.push(v);
		}
	}
}

int main () {
	n = read(), m = read(), T = read();
	for (int i = 0, u, v, w; i < m; i++) {
		u = read(), v = read(), w = read();
		in[v]++;
		add(u, v, w);
	}
	memset(g, 0x3f3f3f3f, sizeof(g));
	g[1][1] = 0;
	topo();
	int pos = n;
	for (int i = ans; i > 0; i--) {
		a[i] = pos;
		pos = pre[pos][i];
	}//前驱维护路径
	write(ans), putchar('\n');
	for (int i = 1; i <= ans; i++) {
		write(a[i]), putchar(' ');
	}
}
```

---

## 作者：轻绘 (赞：0)

# 算法

~~简单的~~DP+拓扑。

# 思路

通过枚举一个点 $i$ 在路径上所有可能的情况，最后得出点 $n$ 所有可能情况。

具体的，在考虑点 $i$ 时，我们需要枚举所有可以直接到达 $i$ 的点，通过这些点已有的状态推出点 $i$ 在路径上所有状态。

因此，我们需要在考虑 $i$ 之前将所有可以直接到达 $i$ 的点处理完。

显而易见，拓扑序可以保证在处理 $i$ 之前将所有可以直接到达 $i$ 的点处理完。

![](https://cdn.luogu.com.cn/upload/image_hosting/icyflqlz.png)

如图所示，在处理 $i$ 时，我们可以通过 $1,2,3$ 三条边直接到达 $i$ ,在任意包含 $i$ 的路径中， $a_1,a_2,a_3$  必有一个排在 $i$ 之前。 

所以我们需要在 $i$ 之前将 $a_1,a_2,a_3$ 处理完毕。

根据需求，我们只要根据拓扑序遍历即可。

### 定义：

$f(i,j,1)$ 第 $i$ 个点作为路径上第 $j$ 个点时最小路程。

$f(i,j,0)$ 第 $i$ 个点作为路径上第 $j$ 个点时上一个点（记录路径）。

### 状态转移方程

$f(i,j,1)=\min(f(i,j,1),f(k,j-1,1)+ed(k,i))$

我们枚举 $k,j$ 

最后即可通过枚举 $f(n,1...n,1)$ 得到答案。

# 程序

```
#include<bits/stdc++.h>
const int MAX=100000;
using namespace std;
int h[MAX],nex[MAX],v[MAX],ed[MAX],tot,in[MAX];
inline void add(int x,int y,int z){
	nex[++tot]=h[x],h[x]=tot,v[tot]=y,ed[tot]=z;++in[y];//入度数
}
int n,m,k;
int dis[MAX],ans[MAX];
bool used[MAX];
int f[5010][5010][2];
queue<int> q;
inline void topo(){//根据拓扑序
	for(int i=1;i<=n;++i) if(!in[i]) q.push(i);//入度为零直接加入
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=h[now];i;i=nex[i]){//枚举边
			for(int j=2;j<=n;++j){//枚举作为第几个点
				if(f[now][j-1][0]){
					if(f[now][j-1][1]+ed[i]>k)	continue;
					if(f[v[i]][j][1]>f[now][j-1][1]+ed[i]){
						f[v[i]][j][1]=f[now][j-1][1]+ed[i];
						f[v[i]][j][0]=now;
					}
				}
			}
			if(!--in[v[i]]) q.push(v[i]);//拓扑操作
		}
		used[now]=1;
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	for(int i=1;i<=n;++i)
		dis[i]=0x3f3f3f3f;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			f[i][j][1]=0x3f3f3f3f;
		}
	}
	dis[1]=0;
	f[1][1][1]=0;
	f[1][1][0]=-1;
	topo();
	int p,o=0;
	for(int i=n;i>=1;--i){//将答案路径取出
		if(f[n][i][1]<=k){
			o=i;
			ans[o]=n;
			p=f[n][o][0];
			while(p!=-1){
				ans[--o]=p;
				p=f[p][o][0];
			}
			o=i;
			break;
		}
	}
	printf("%d\n",o);
	for(int i=1;i<=o;++i)
		printf("%d ",ans[i]);
	return 0;
} 
```


---

