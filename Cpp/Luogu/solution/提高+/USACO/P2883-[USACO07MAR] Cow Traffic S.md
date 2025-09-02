# [USACO07MAR] Cow Traffic S

## 题目描述

The bovine population boom down on the farm has caused serious congestion on the cow trails leading to the barn. Farmer John has decided to conduct a study to find the bottlenecks in order to relieve the 'traffic jams' at milking time.

The pasture contains a network of M (1 ≤ M ≤ 50,000) one-way trails, each of which connects exactly two different intersections from the set of N (1 ≤ N ≤ 5,000) intersections conveniently numbered 1..N; the barn is at intersection number N. Each trail connects one intersection point to another intersection point with a higher number. As a result, there are no cycles and, as they say on the farm, all trails lead to the barn. A pair of intersection points might be connected by more than one trail.

During milking time rush hour, the cows start from their respective grazing locations and head to the barn. The grazing locations are exactly those intersection points with no trails connecting into them. Each cow traverses a 'path', which is defined as a sequence of trails from a grazing location to the barn.

Help FJ finding the busiest trail(s) by computing the largest number of possible paths that contain any one trail. The answer is guaranteed to fit in a signed 32-bit integer.

随着牛的数量增加，农场的道路的拥挤现象十分严重，特别是在每天晚上的挤奶时间。为了解决这个问题，FJ决定研究这个问题，以能找到导致拥堵现象的瓶颈所在。


牧场共有M条单向道路，每条道路连接着两个不同的交叉路口，为了方便研究，FJ将这些交叉路口编号为1..N,而牛圈位于交叉路口N。任意一条单向道路的方向一定是是从编号低的路口到编号高的路口，因此农场中不会有环型路径。同时，可能存在某两个交叉路口不止一条单向道路径连接的情况。


在挤奶时间到来的时候，奶牛们开始从各自的放牧地点回到牛圈。放牧地点是指那些没有道路连接进来的路口（入度为0的顶点）。


现在请你帮助fj通过计算从放牧点到达牛圈的路径数目来找到最繁忙的道路，即求出所有可行路径中通过某条道路的最大值（答案保证是不超过32位整数）。


## 说明/提示

Here are the four possible paths that lead to the barn:


1 3 4 6 7


1 3 5 6 7


2 3 4 6 7


2 3 5 6 7


## 样例 #1

### 输入

```
7 7
1 3
3 4
3 5
4 6
2 3
5 6
6 7```

### 输出

```
4```

# 题解

## 作者：yimuhua (赞：11)

## 题意：

1. $n$ 个点，$m$ 条边；

2. 边从编号小的连到编号大的，有向无环图；

3. 起点为入度为 $0$ 的点，终点为 $n$；

目标：求所有起点到终点经过的边中经过的最多次数；

## 策略：

考虑如何计数，发现对于一条边 $(x,y)$ 其被经过时应为从起点到达点 $x$ 后经过该边再从点 $y$ 走到点 $n$，于是可以乘法原理：

1. 建正向图，设 $dp_i$ 为从入度为 $0$ 的点到达点 $i$ 的方案数，则：
    ```
    dp[next] += dp[cur];
    ```

2. 建正向图，设 $dp2_i$ 为从点 $n$ 到达点 $i$ 的方案数，则：
    ```
    dp2[next] += dp2[cur];
    ```

3. 枚举每一条边 $(x, y)$，设编号为 $i$，则：
    ```
    maxi = max(maxi, dp[i] * dp2[i]);
    ```
## AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
queue<int> q, q2;
vector<int> nbr[5005], nbr2[5005];
int n, m, maxi, dp[5005], dp2[5005], in[5005], in2[5005], u[50005], v[50005];
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        nbr[u[i]].push_back(v[i]);
        nbr2[v[i]].push_back(u[i]);
        in[v[i]]++, in2[u[i]]++;
    }
    for(int i = 1; i <= n; i++)
        if(!in[i])
            dp[i] = 1, q.push(i);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = 0; i < nbr[x].size(); i++) {
            in[nbr[x][i]]--;
            dp[nbr[x][i]] += dp[x];
            if(!in[nbr[x][i]])
                q.push(nbr[x][i]);
        }
    }
    dp2[n] = 1;
    q2.push(n);
    while(!q2.empty()) {
        int x = q2.front();
        q2.pop();
        for(int i = 0; i < nbr2[x].size(); i++) {
            in2[nbr2[x][i]]--;
            dp2[nbr2[x][i]] += dp2[x];
            if(!in2[nbr2[x][i]])
                q2.push(nbr2[x][i]);
        }
    }
    for(int i = 1; i <= m; i++)
        maxi = max(maxi, dp[u[i]] * dp2[v[i]]);
    cout << maxi;
    return 0;
}
```

---

## 作者：AugustineYang (赞：9)

题意很简单，求每一条边被几条从入度为0的点到n号点的路径覆盖过。

画一下图，再结合数学思想，可以发现对于一条边 x--->y，它的答案 = 从每个入度为0的点到x的路径数 * y到n号点的路径数。

那么怎么算入度为0的点到x的路径数呢？
![正图](https://cdn.luogu.com.cn/upload/pic/41148.png)

观察这张图，其中红色数字表示的是从入度为0的点到该点的路径数。

若设为v[i]，可以发现对于一个点i，它的答案是$\sum_{} v[j]{}$，其中j是i的前驱节点。

同理可以得到y到n号点的路径数的计算方法。
![反图](https://cdn.luogu.com.cn/upload/pic/41140.png)

这样我们就可以建两张图，一张正图一张反图。

这样对于一条边x--->y (x<y)，它的答案就是v[正图][x] * v[反图][y]。统计并输出即可。
![](https://cdn.luogu.com.cn/upload/pic/41237.png)

```cpp
//0为正图，1为反图 
#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
#define rint register int 
#define MAXN 5005
#define MAXM (int)(5e4+5)
using namespace std;
int n, m, num_edge[2], head[2][MAXN], ans;
int val[2][MAXN], in_degree[2][MAXN];
struct add1
{
	int to, next;
}edge[2][MAXM];
struct add2
{
	int x, y;
}save_edge[MAXM];
inline int read()
{
	int tt = 0, flag = 1;
	char c = getchar();
	while(!isdigit(c))
	{
		if(c == '-') flag = 0;
		c = getchar();
	}
	while(isdigit(c))
	{
		tt = (tt<<3)+(tt<<1)+(c&15);
		c = getchar();	
	}
	return flag?tt:-tt;
}
inline void write(int x)
{
	if(x < 0) putchar('-'), x=-x;
	if(x > 9) write(x/10);
	putchar(x%10+'0'); 
}
inline void swap(int &x, int &y)
{
	int temp=x; x=y; y=temp;
}
inline int max(int x, int y)
{
	return x>y?x:y;
}
inline int min(int x, int y)
{
	return x<y?x:y;
}
inline void add_edge(int from, int to, int opt)
{
	edge[opt][++num_edge[opt]] = (add1){to, head[opt][from]};
	head[opt][from] = num_edge[opt];
	in_degree[opt][to]++;
}
inline void work(int opt)
{
	queue<int> q;
	bool vis[MAXN];
	memset(vis, 0, sizeof vis);
	for(int i=1; i<=n; ++i)
		if(!in_degree[opt][i]) 
        	q.push(i), val[opt][i]=1;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		vis[u] = 1;
		for(rint i=head[opt][u]; i; i=edge[opt][i].next)
		{
			int v = edge[opt][i].to;
			if(vis[v]) continue;
			val[opt][v] += val[opt][u]; //更新后继节点
			in_degree[opt][v]--;
			if(!in_degree[opt][v]) q.push(v);
            //对于一个节点，每从某个前驱节点更新一次，
            //就把它与该前驱节点的连边“删掉”，
            //当这个节点“没有”前驱节点时，
            //说明该节点的val更新完毕，
            //可以用它来更新后继了，此时入队列
		}
	}
}
int main()
{
	n = read(), m = read();
	for(rint i=1; i<=m; ++i)
	{
		int x = read(), y = read();
		if(x>y) swap(x, y);
		save_edge[i] = (add2){x, y}; //存下边的信息
		add_edge(x, y, 0);
		add_edge(y, x, 1);
	}
	work(0); work(1);
	for(int i=1; i<=m; ++i)
		ans = max(ans, val[0][save_edge[i].x]*val[1][save_edge[i].y]);
	write(ans);
	return 0;	
}
```

---

## 作者：巨型方块 (赞：7)

诶呦，这道题目问你

在所有的路径里面，那一条边被访问的最多？

我们这么想

对于一条边a-b（a<b）

我们计算出来所有的入度为0的点到a的方案，在计算n点到b的方案

两者相乘，岂不是所有入度为0 的点到n且经过这条边的方案？

那么2次拓扑排序然后求max就好啦


```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
inline Ll RR(){Ll v=0,k=1;char c=0;while('0'>c||c>'9'){if(c=='-')k=-1;c=getchar();}while('0'<=c&&c<='9')v=v*10+c-48,c=getchar();return v*k;}
inline void W(Ll x){if(x<0)putchar('-'),x=-x;if(x>9)W(x/10);putchar(x%10+48);}
inline void WW(Ll x){W(x);puts("");}
inline void read(int &x,int &y){x=RR();y=RR();}
const int N=5e3+5;
vector<int>h[N],H[N];
int A[N],d[N],D[N],B[N];
int n,m,x,y,ans;
int main()
{
    read(n,m);
    for(int i=1;i<=m;i++){
        read(x,y);
        h[min(x,y)].push_back(max(x,y));
        H[max(x,y)].push_back(min(x,y));
        A[max(x,y)]++;B[min(x,y)]++;
    }
    queue<int>Q;
    for(int i=1;i<=n;i++)if(!A[i])d[i]=1,Q.push(i);
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int k=0;k<h[x].size();k++){
            d[h[x][k]]+=d[x];
            A[h[x][k]]--;
            if(!A[h[x][k]])Q.push(h[x][k]);
        }
    }
    D[n]=1;Q.push(n);
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int k=0;k<H[x].size();k++){
            D[H[x][k]]+=D[x];
            B[H[x][k]]--;
            if(!B[H[x][k]])Q.push(H[x][k]);
        }
    }
    for(int i=1;i<=n;i++)
        for(int k=0;k<h[i].size();k++)
            ans=max(ans,d[i]*D[h[i][k]]);
    W(ans);
}

```

---

## 作者：Stone_Xz (赞：4)

## [传送门](https://www.luogu.com.cn/problem/P2883)

## 题意：

 - 给定 $n$ 个点，$m$ 条边的有向无环图。
 
 - 目标：从入度为 $0$ 的点到点 $n$ 的所有路径中，被经过次数最多的边的经过次数。

## 分析：拓扑排序

1. 肥肠简单的一个数学知识：一条边经过次数的是：以自己左边的点为终点的的路径方案数 $\times$ 以自己右边的点为起点的路径方案数。

2. 现在的问题是，“每个点以自己为终点的的路径方案数”和“每个点以自己为起点的路径方案数”分别是多少。

3. 每个点以自己为终点的的路径方案数很好求，设 $dp[i]$ 表示以点 $i$ 为终点的的路径方案数，跑拓扑排序，每次往下走时，```dp[下一个点] += dp[当前的点]```。

4. 那以自己为起点的路径方案数怎么求呢？我们直接在原图上是不好求的，**可以建一个反图**，然后在反图上跑拓扑排序。此时往前走就相当于往后走，反图上以点 $i$ 为终点的的路径方案数就相当于正图上以点 $i$ 为起点的路径方案数。

5. 设 $f[i]$ 表示以点 $i$ 为起点的的路径方案数，**在反图上**跟 $dp[i]$ 跑一样的拓扑排序。

6. 最后枚举每条路径，这条路径的经过次数就是 $dp[x[i]] \times f[y[i]]$，更新答案。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5, M = 5e4 + 5;
int n,m,in[N];
int x[M],y[M];

int dp[N],f[N];
// dp[i]表示以点 i为终点的路径方案数
// f[i] 表示以点 i为起点的路径方案数 
vector<int> nbr[N];

void topo(int DP[])
{
	queue<int> q;
	for(int i = 1; i <= n; i++)
		if(in[i] == 0){
			DP[i] = 1; // 初始化
			q.push(i);
		}
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		for(int i = 0; i < nbr[cur].size(); i++)
		{
			int nxt = nbr[cur][i];
			DP[nxt] += DP[cur];
			in[nxt]--;
			if(in[nxt] == 0)
				q.push(nxt);
		}
	} 
	return ;
}
int main()
{
	cin >> n >> m;
	
	for(int i = 1; i <= m; i++){
		cin >> x[i] >> y[i];
		nbr[x[i]].push_back(y[i]);
		in[y[i]]++;
	}
	topo(dp);
	
	for(int i = 1; i <= n; i++){ // 清空原来的图 
		nbr[i].clear();
		in[i] = 0;
	}
	for(int i = 1; i <= m; i++){ // 建反图 
		nbr[y[i]].push_back(x[i]);
		in[x[i]]++;
	}
	topo(f);
	
	int ans = -1e9;
	for(int i = 1; i <= m; i++) // 答案 
		ans = max(ans,dp[x[i]] * f[y[i]]);
	cout << ans;
	return 0;
}

```


---

## 作者：初雪_matt (赞：4)

## 题目大意

给你一个有向无环图，让你求 $1 \rightarrow n$ 的路径所经过的最多次数的 $u \rightarrow v$。

## 题目思路

这道题其实并没有蓝题的难度。。。

题目给了以下条件给我们：

- $N$ 个点 $M$ 条有向边
- 编号小的点向编号多的点连边，没有环
- 起点为入度为 $0$ 的点，终点为 $n$

我们可以分析出一下策略：

- 先建一编正向图，设 $dp[i]$ 表示从入读为 $0$ 的点到达点 $i$ 的方案数，则 ```dp[nxt]+=dp[cur]```
- 建反向图，设 $f[i]$ 表示从点 $n$ 的点到达点 $i$ 的次数，则 ```f[nxt]+=f[cur]```
- 枚举每一条边 $(x,y)$，设编号 $i$，则经过的次数 ```cnt[i]=dp[x]*f[y]```
- 求 $cnt[i]$ 中的最大值

代码就算了，要就私信

感谢 @apple365 

---

## 作者：Adove (赞：4)

此题有个小技巧

题目中说边从编号小的连到编号大的

那么我们循环时一定先访问小的，后访问大的

可以省去队列和入度的记录

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=5005;
const int MAXM=5e4+5;

int n,m,np,ans;
int h[MAXN],siz[2][MAXN];
int x[MAXM],y[MAXM];
struct rpg{
	int li,nx;
}a[MAXM];

void add(int ls,int nx){a[++np]=(rpg){h[ls],nx};h[ls]=np;}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){scanf("%d%d",&x[i],&y[i]);add(x[i],y[i]);}
	for(int i=1;i<=n;++i){
		if(!siz[0][i]) siz[0][i]=1;
		for(int j=h[i];j;j=a[j].li) siz[0][a[j].nx]+=siz[0][i];
	}memset(h,0,sizeof(h));np=0;
	for(int i=1;i<=m;++i) add(y[i],x[i]);
	for(int i=n;i;--i){
		if(!siz[1][i]) siz[1][i]=1;
		for(int j=h[i];j;j=a[j].li) siz[1][a[j].nx]+=siz[1][i],ans=max(ans,siz[0][a[j].nx]*siz[1][i]);
	}printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lutaoquan2012 (赞：3)

## 题意
给定一个图，一共有 $n$ 个点， $m$ 条边。
求其中最多的一条边被经过的数量。
## 思路
这道题呢，应该是个图论。
看下图:

![](https://cdn.luogu.com.cn/upload/image_hosting/h3czc457.png)

- 星星：指一条从放牧点（入度为 $0$ 的点）到节点 $i$ 的方案数。

- 旗子：指一条从牛圈（出度为 $0$ 的点）到节点 $i$ 的方案数。

由此可见，一条边 $(x,y)$ 的被经过的数目一定是节点 $x$ 的星星数量 $\times$ 节点 $y$ 旗子的数量。

- 节点 $x$ 的星星数量代表的是**前面经过这条边的数量**

- 节点 $y$ 的旗子数量代表的是**后面经过这条边的数量**

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,ans;
ll p[1010][1010],q[1010][1010];//正向建图，反向建图
ll f[1010],g[1010];//前面的图里画的"星星"，"旗子"
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) f[i]=1;//一开始设所有地方都是牧场
    for(int i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        p[u][v]++;//正向建图
        q[v][u]++;//反向建图
        f[v]=0;//因为有边能到达 v ，所以 v 不可能是牧场。题目中给出入读为 0 的才是牧场
    }
    for(int i=1;i<=n;i++)//枚举每一个点
        for(int j=i+1;j<=n;j++) f[j]+=f[i]*p[i][j];//牧场到 j 的路径数目 = 所以能到 j 的牧场路径数目和
    g[n]=1;
    for(int i=n;i>=1;i--)//同上面求"星星数"一样，只不过是反着来的。
        for(int j=1;j<i;j++) g[j]+=g[i]*q[i][j];
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(p[i][j]) ans=max(ans,f[i]*g[j]);//求最值
    cout<<ans;
    return 0;
}
```

---

## 作者：ruanshaochuan______ (赞：2)

# 题意
一个 $n$ 个点，$m$ 条边的有向无环图，求起点为入度为的 $0$ 点，终点为 $n$ 的所有路径中，每一条边经过次数的最大值。
# 解题思路
根据乘法原理，一条边经过的次数等于它的终点到 $n$ 的路径数乘上所有入度为 $0$ 的点到它的起点的路径数，记忆化搜索即可。
# 具体实现
1. 定义 $dp[i]$ 为所有入度为 $0$ 的点到编号为 $i$ 的边的起点的路径数，$pd[i]$ 为编号为 $i$ 的边的终点到 $n$ 的路径数,定义 $from(i)$ 为编号为 $i$ 的边的起点，$to(i)$ 为终点。
2. 转移方程：$\begin{aligned} dp[i]=\sum_{(j,from(i)) \in E}  dp[j] \end{aligned}$，$\begin{aligned} pd[i]=\sum_{(to(i),j) \in E}  pd[j] \end{aligned}$。
3. 边界条件：若编号为 $i$ 的边的起点为入度为 $0$ 的点，则 $dp[i]=1$，若编号为 $i$ 的边的终点为 $n$，则 $pd[i]=1$。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=5e4+5;
struct Node{
	int to,id;
};
struct line{
	int u,v;
}a[maxn];
vector<Node>vt[maxn],tv[maxn];
int n,m,maxi,dp[maxn],pd[maxn],in[maxn],ni[maxn];
int dfs(int x)
{
	if(dp[x]!=-1)
		return dp[x];
	dp[x]=0;
	if(in[a[x].u]!=0)
	for(Node v:tv[a[x].u])
		dp[x]+=dfs(v.id);
	else
		dp[x]=1;
	return dp[x];
}
int fds(int x)
{
	if(pd[x]!=-1)
		return pd[x];
	pd[x]=0;
	if(a[x].v!=n)
	for(Node v:vt[a[x].v])
		pd[x]+=fds(v.id);
	else
		pd[x]=1;
	return pd[x];
}
signed main()
{
	cin>>n>>m; 
	for(int i=1;i<=m;i++)
	{
		dp[i]=pd[i]=-1;
		int u,v;
		cin>>u>>v;
		vt[u].push_back({v,i});
		tv[v].push_back({u,i});
		in[v]++;
		ni[u]++;
		a[i].u=u,a[i].v=v;
	}
	for(int i=1;i<=m;i++)
	{
		dp[i]=dfs(i);
		pd[i]=fds(i);
		maxi=max(maxi,pd[i]*dp[i]);
	}
	cout<<maxi;
}
```


---

## 作者：斗神_君莫笑 (赞：0)

对于本题，最大的难点就在于怎么求出一条边的路径数  
第一次做的时候我只考虑了前驱，然而现实是还要考虑后继   
每条边经过的路径数是前驱\*后继（归到点上）   
因此建两张正反图，分别处理出到每个点的路径数就可以了  
顺便吐槽一句数据真水  
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int u,v,w,nxt;
}e[100010],a[100010];
int head[5010],cnt;
void add(int u,int v){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int head1[5010],cnt1;
void add1(int u,int v){
	a[++cnt1].u=u;
	a[cnt1].v=v;
	a[cnt1].nxt=head1[u];
	head1[u]=cnt1;
}
int ru[5010],kind[5010],st[5010];
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		kind[v]+=kind[u];
		ru[v]--;
		if(!ru[v])dfs(v);
	}
}
int chu[5010],kind1[5010];
void dfs1(int u){
	for(int i=head1[u];i;i=a[i].nxt){
		int v=a[i].v;
		kind1[v]+=kind1[u];
		chu[v]--;
		if(!chu[v])dfs1(v);
	}
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add1(v,u);
		ru[v]++;chu[u]++;
	}
	for(int i=1;i<=n;++i)
		if(ru[i]==0)
			st[i]=1;
	for(int i=1;i<=n;++i)
		if(st[i]){
			kind[i]=1;
			dfs(i);
		}
	memset(st,0,sizeof(st));
	for(int i=1;i<=n;++i)
		if(chu[i]==0)
			st[i]=1;
	for(int i=1;i<=n;++i)
		if(st[i]){
			kind1[i]=1;
			dfs1(i);
		}
	int maxx=0;
	//for(int i=1;i<=m;++i)
	//	printf("%d\n",e[i].w);
	for(int i=1;i<=m;++i)
		maxx=max(maxx,kind[e[i].u]*kind1[e[i].v]);
	printf("%d",maxx);
	return 0;
}
```


---

## 作者：qzhwlzy (赞：0)

## 题目大意  
[传送门](https://www.luogu.com.cn/problem/P2883)  
题目不太难理解，在一张有向图中，所有入度为0的点到所有出度为0的点的路径中，输出经过的次数最多的路径的经过次数。  
## 思路
其实对于某一条路径来说，它的经过次数就是前面入度为0的点到路径起点的方法数 $x$ 乘路径终点到后面所有出度为0的点的方法数 $y$ ，即 $xy$ 。  
所以，我们就可以这样算出每个点的 $x_i$ （图中红色）与 $y_i$ （图中绿色）以及路径经过次数。
![](https://cdn.luogu.com.cn/upload/image_hosting/xc5ml4w9.png)  
计算方法：  
1. $x_i$ 即为以它为终点的路径的起点的点的 $x$ 之和，所以要顺着推。
2. $y_i$ 即为以它为起点的路径的终点的点的 $y$ 之和，所以要反着推。（详见代码~~详细注释~~）  
## 代码  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 50005
using namespace std;
long long n,m,x,y;
long long head[maxn],cnt=0;
long long inde[maxn],outde[maxn];
long long f[maxn],f2[maxn];//f记录上述x，f2记录上述y
struct edge{
	long long to,next;
}a[2*maxn];
void add(long long fr,long long to){//邻接表
	a[++cnt].to=to;
	a[cnt].next=head[fr];
	head[fr]=cnt;
}
int main(){
//	freopen("traffic.in","r",stdin);
//	freopen("traffic.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		add(x,y);
		inde[y]++;//记录入度
		outde[x]++;//记录出度
	}
	
	
	for(long long i=1;i<=n;i++){//起点设为1
		if(inde[i]==0){
			f[i]=1;
		}
	}
	for(long long i=1;i<=n;i++){//顺推x
		for(long long x=head[i];x!=0;x=a[x].next){//以这个点为起点的所有边终点加上这个点的x
			f[a[x].to]+=f[i];
		}
	}
	
	
   for(long long i=1;i<=n;i++){//y的方法同x
		if(outde[i]==0){
			f2[i]=1;
		}
	}
	for(long long i=n;i>=1;i--){
		if(f2[i]){
			continue;
		}
		for(long long x=head[i];x!=0;x=a[x].next){
			f2[i]+=f2[a[x].to];
		}
	}
	long long ans=-1;
    
    
	for(long long i=1;i<=n;i++){
		for(long long x=head[i];x!=0;x=a[x].next){
			ans=max(ans,f[i]*f2[a[x].to]);
		}
	}
	printf("%lld",ans);
	return 0;//完结撒花
}

```


---

