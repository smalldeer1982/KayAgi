# Fight Against Traffic

## 题目描述

### 题意描述

给你一张无向图，一共有 $n$ 个点（$2 \leq n \leq 1000$），由 $m$ 条边连接起来（$1 \leq m <\leq 10000$），现在要在任意一对没有连边的点之间连上一条边,并且保证 $s$ 到 $t$ 之间的最短路径长度不变（最短路径长度表示 $s$ 到 $t$ 最少经过的边的数量）和图为简单图（无重边,无自环）（$1 \leq s,t \leq n$，$s \neq t$），请你求出一共有多少条这样的边。

## 样例 #1

### 输入

```
5 4 1 5
1 2
2 3
3 4
4 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5 4 3 5
1 2
2 3
3 4
4 5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
5 6 1 5
1 2
1 3
1 4
4 5
3 5
2 5
```

### 输出

```
3
```

# 题解

## 作者：Lips (赞：17)

# 为什么没人用 $dijkstra$ 呢？

- 关于 $spfa$，他早就死了

- 关于 $floyd$，他已慢死了

- 关于 $dijkstra$，他不香么？

题意已经很明显了，给定一个无向图，求最多添加多少边可以保证最短路不会改变。

做法：用 $dijkstra$ 将图正反跑**两次**，分别将 $s$ 设为起点和 $t$ 设为起点，将最短路存入到 $first\_dist$ 与 $second\_dist$ 中，这时，最短路已经求出来了~~废话~~，开始加边。

可以这样想，只有当对于一对节点 $(u,v)$，只有从起点到这个点的最短路加上从终点到另一个点的最短路大于等于从起点到终点的距离，才可以加边（显然有两个判断）。

**注意：** 最后答案 $ans$ 初始值一定要设为 $-m$ 这里最为思考题各位 $dalao$ 珂以自己想想~~读者自证不难~~

$Code:$

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=1010;
int n,m,s,t,second_dist[MAXN],first_dist[MAXN],ans;//变量名称如上述所说 
struct edge
{
	int to,cost;//结构体装星 
	edge(int to,int cost):to(to),cost(cost){}//构造函数，用来存边 
};
vector<edge>G[MAXN];
typedef pair<int,int>P;//定义pair类型的P 
inline int read()//快读 
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
void dijkstra(int s)//最短路dijkstra的板子 
{
	priority_queue<P,vector<P>,greater<P> >q;
	for(register int i=1;i<=n;i++) second_dist[i]=1e9;
	second_dist[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		P p=q.top();
		q.pop();
		int v=p.second;
		if(second_dist[v]<p.first) continue;
		for(register int i=0;i<G[v].size();i++) 
		{
			edge e=G[v][i];
			if(second_dist[e.to]>second_dist[v]+e.cost)
			{
				second_dist[e.to]=second_dist[v]+e.cost;
				q.push(make_pair(second_dist[e.to],e.to));
			}
		}
	}
}
int main()
{
	n=read(),m=read(),ans=-m,s=read(),t=read();//一定要存-m 
	while(m--)
	{
		int u=read(),v=read();
		G[u].push_back(edge(v,1));
		G[v].push_back(edge(u,1));
		//其实这里vector也珂以存int 
	}
	dijkstra(s);
	for(register int i=1;i<=n;i++) first_dist[i]=second_dist[i];//先赋值 
	dijkstra(t);
	for(register int i=1;i<=n;i++)
		for(register int j=i+1;j<=n;j++)
			if(first_dist[i]+second_dist[j]+1>=first_dist[t]&&first_dist[j]+second_dist[i]+1>=first_dist[t])
				//柿子
				ans++;//别忘了更新 
	printf("%d\n",ans);//完美输出 
	return 0;//完结撒花~~ 
}
```

点个赞再走吧Orz



---

## 作者：sysong (赞：4)

# 题解CF954D Fight Against Traffic

### Description

给你一张无向图，一共有 $n$ 个点 $(2 \le n \le 1000)$，由 $m$ 条边连接起来($1 <= m <= 10000$)，现在要在任意一对没有连边的点之间连上一条边，并且保证 $s$ 到 $t$ 之间的最短路径长度不变（最短路径长度表示 $s$ 到 $t$ 最少经过的边的数量）$(1 \le s,t \le n , s \ne t)$，请你求出一共有多少条这样的边。

### Solution

这道题其实可以不用 Dijkstra 来做，因为是边权为 $1$ 的无向图，我们可以直接用 bfs 解决。

首先用两次 bfs 分别求出 $s$ 和 $t$ 到图上其余各点的距离，然后枚举每个点对，判断加边之后最短路是否改变。

**注意：**

**1. 计算答案时要减去原有的 $m$ 条边。**

**2. 第二次跑最短路时要清零。**

**3. 判断最短路是否改变时要加上点对两点之间长度 $1$。**

### Code

```c++
#include <bits/stdc++.h>
#define gc() getchar()
using namespace std;
typedef long long ll;

template <typename T> void rd(T &x){
	ll f=1;x=0;char c=gc();
	for(;!isdigit(c);c=gc())if(c=='-')f=-1;
	for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}

int n,m,s,t,ans,hd[1010],cnt;
int vis[1010],d[1010],c[1010];	// c 存储 s 到各点最短路，d 存储 t 到各点最短路。
struct nd{
	int to,nxt;
}e[10010];						// 链式前向星存图

inline void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=hd[u];
	hd[u]=cnt;
}

inline void bfs(int k){			// 宽搜最短路
	vis[k]=1,d[k]=0;
	queue<int> q;
	q.push(k);
	while(!q.empty()){
		int nt=q.front();q.pop();
		for(int i=hd[nt],nx;i;i=e[i].nxt){
			nx=e[i].to;
			if(!vis[nx]){
				vis[nx]=1;
				d[nx]=d[nt]+1;	// 边权为 1
				q.push(nx);
			}
		}
	}
}

int main(){
	rd(n),rd(m),rd(s),rd(t);
	for(int i=1,u,v;i<=m;i++)
        rd(u),rd(v),
    	add(u,v),add(v,u);		// 无向图双向加边
	bfs(s);
	for(int i=1;i<=n;i++)
        c[i]=d[i];				// 把最短路存到 c 中
	memset(vis,0,sizeof(vis));	// 清零
	bfs(t);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(d[i]+c[j]+1>=d[s]&&d[j]+c[i]+1>=d[s])
                ++ans;			// 注意这里两个点都要判断是否会使最短路改变
	printf("%d\n",ans-m);		// 要减掉原有的 m 条边
	return 0;
}

```



***by sysong***

$2021.5.23$



---

## 作者：KSToki (赞：4)

作业题，~~水一水~~题解。

考虑分别以 $s$ 和 $t$ 为起点跑最短路（题解中用的 dijkstra 堆优化，~~因为 SPFA 它已经死了~~）。此时 $n^2$ 枚举 $i,j$ 暴力判断即可。

如何判断？将 $s->i->j->t$ 和 $s->j->i->t$ 与最短路比较即可（都不比最短路短）。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	    ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
int n,m,s,t,x,y,head[1001],to[2001],nxt[2001],dis1[1001],dis2[1001],tot,ans;
bool vis1[1001],vis2[1001],e[1001][1001];
inline void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
priority_queue< pair<int,int> >q;
void dijkstra1()
{
	memset(dis1,127/3,sizeof(dis1));
	dis1[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis1[x])
			continue;
		vis1[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			if(dis1[y]>dis1[x]+1)
			{
				dis1[y]=dis1[x]+1;
				q.push(make_pair(-dis1[y],y));
			}
		}
	}
}
void dijkstra2()
{
	memset(dis2,127/3,sizeof(dis2));
	dis2[t]=0;
	q.push(make_pair(0,t));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis2[x])
			continue;
		vis2[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			if(dis2[y]>dis2[x]+1)
			{
				dis2[y]=dis2[x]+1;
				q.push(make_pair(-dis2[y],y));
			}
		}
	}
}
int main()
{
	n=read();
	m=read();
	s=read();
	t=read();
	while(m--)
	{
		x=read();
		y=read();
		add(x,y);
		add(y,x);
		e[x][y]=e[y][x]=1;
	}
	dijkstra1();
	dijkstra2();
	for(register int i=1;i<n;++i)
		for(register int j=i+1;j<=n;++j)
			if(!e[i][j]&&dis1[i]+dis2[j]+1>=dis1[t]&&dis1[j]+dis2[i]+1>=dis1[t])
				++ans;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：rain2021 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF954D)
* * *

这道题之所以是蓝题，是因为他的思路十分难想，但是代码很好写。

先理解一下题目:

在一个无向联通图上找到一条边，使得$s \to t$的最短路变小。

求这种边的个数。

* * *

![](https://cdn.luogu.com.cn/upload/image_hosting/tudz1lri.png)

比如这个图，我们要使$s \to t$的距离变短，就得加一条边权为1的边$x \to y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/b5ov6m7b.png)

一共有两种路径可选

第一种：
$s \to y \to x \to t$
![](https://cdn.luogu.com.cn/upload/image_hosting/kmq6sjg4.png)


第二种：
$s \to x \to y \to t$
![](https://cdn.luogu.com.cn/upload/image_hosting/v9zzm35b.png)



所以代码是这样实现的：

`dis1[id]`表示从s开始到`id`的最短路径。
`dis2[id]`表示从t开始到`id`的最短路径。

先从s和t分别做一遍`dijkstra`,他们的`dis`分别存在dis1和dis2里。

然后再$O(n^2)$找两个点`(i, j)`，表示`(i, j)`之间连了一条边，如果`dis1[i] + dis2[j] + 1 >= dis1[t]`即$s \to x \to y \to t$就说明加的这条边成功的让$s \to t$的最短路径变小了,`ans++;`

如果`dis1[j] + dis2[i] + 1 >= dis1[t]`即$s \to y \to x \to t$就说明加的这条边成功的也让$s \to t$的最短路径变小了,`ans++;`

还有一个细节，就是已经有的边就不能加了，所以用一个flag记录已经有的边，如果`flag[i][j]`就`continue`

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
vector<int> myv[MAXN];
int dis1[MAXN], dis2[MAXN];
bool vis[MAXN];
bool flg[MAXN][MAXN];
void adde(int x, int y)
{
	myv[x].push_back(y);
}
void dijkstra(int s, int *dis)
{
	priority_queue<pair<int, int> > myq;
	memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	myq.push(make_pair(0, s));
	while(!myq.empty())
	{
		int id = myq.top().second;
		int sum = myq.top().first;
		myq.pop();
		if(vis[id])
			continue;
		vis[id] = 1;
		for(int i = 0; i < myv[id].size(); i++)
		{
			int nxt = myv[id][i];
			if(dis[nxt] > dis[id] + 1)
			{
				dis[nxt] = dis[id] + 1;
				myq.push(make_pair(-dis[nxt], nxt));
			}
		}
	}
}
int main()
{
	int n, m, s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		flg[u][v]=1;
		flg[v][u]=1;
		adde(u, v);
		adde(v, u);
	}
	memset(dis1, 0x3f, sizeof(dis1));
	dijkstra(s, dis1);
	memset(dis2, 0x3f, sizeof(dis2));
	dijkstra(t, dis2);
	int ans = 0;
	for(int i = 1; i <= n-1; i++)
	{
		for(int j = i+1; j <= n; j++)
		{	
			if(flg[i][j])
				continue;
			if(dis1[i]+dis2[j]+1 >= dis1[t] && dis1[j]+dis2[i]+1>=dis1[t])
			{
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Shunpower (赞：3)

## 题目大意

对于一个**无向无权联通**图 $G$，有 $n$ 个点 $m$ 条边，往这个**图里没有被连接的两个点**之间连边，问有多少连法可以使得 $s$ 到 $t$ 的最短路长度不变。

## 解决思路

### 2.1 暴力做法

可以枚举任意两个点，对于每次连接使用 bfs 求最短路，计算出时间复杂度为 $O(n^2(n+m))$，不可通过。

### 2.2 预处理

如果连接 $x,y$ 两个点，我们可以通过先从 $s$ 走到 $x$ 或 $y$ 点，再从另一端前往 $t$ 点，计算出这样走的路线长度。如果这样走的路线长度大于等于两者间的最短路长度（也就是不会使最短路长度变化），那么就将计数器加一。

那我们可以预处理出 $s$ 点到任何一个点的最短路，用 $p1_i$ 表示。

再预处理出任意一点到 $t$ 点的最短路，由于这是无向图，等同于求出 $t$ 点到任意一点的最短路，用 $p2_i$ 表示。

最后枚举两个点 $x,y$，计算 $p1_x+p2_y$ 和 $p1_y+p2_x$，再和 $p1_t$ 或者 $p2_s$ 比较（这两者是等价的，下文中都使用 $p1_t$）。如果 $p1_t \leqslant p1_x+p2_y+1 \ \land \ p1_t \leqslant p1_y+p2_x+1$ 就让计数器变量加一。

## 代码实现

### 3.1 建图

采用邻接表建无向图：

```
for(int i=1;i<=m;i++){
	int a1,a2;
	cin>>a1>>a2;
	l[a1].push_back(a2);
	l[a2].push_back(a1);//无向图建图
    bol[a1][a2]=1;
	bol[a2][a1]=1;//表示a1和a2间有了一条边
}
```

这里的 $l$ 是邻接表。

### 3.2 bfs 预处理最短路

```
q1.push(s);
p1[s]=0;
ok1[s]=1; //状态初始化，起点为s
while(!q1.empty()){
	int x=q1.front();
	q1.pop();
	for(int i=0;i<l[x].size();i++){
		if(!ok1[l[x][i]]){ //排除了反复走一个点的情况
			if(p1[l[x][i]]!=0){ //如果这个点的最短路值不是0
				p1[l[x][i]]=min(p1[l[x][i]],p1[x]+1);//比较已知的最短路和现在这条路
			}
			else{
				p1[l[x][i]]=p1[x]+1;//如果这个点还没有最短路值，就将现在这条路的长度赋值给它
			}
			q1.push(l[x][i]);//push新的状态
			ok1[l[x][i]]=1;//这个点已经走过了
		}
	}
}
```
用一个队列 $q1$ 存储 bfs 的状态，用 $\texttt{bool}$ 数组 $ok$ 存储这个点是否走过以避免出现环的情况，用 $p1$ 数组存储最短路的长度。

从 $t$ 点开始的 bfs 预处理如法炮制，基本没有区别。

### 3.3 枚举每一个 $x,y$

现在我们得到了从 $s$ 点到任意一点的最短路数组 $p1$，从 $t$ 点到任意一点的最短路数组 $p2$。

先用二重循环枚举 $x,y$，为避免重复计算，$y$ 的枚举从 $x+1$ 开始，并排除掉已有边的情况。

在枚举中比较 $p1_t$ 与 $p1_x+p2_y+1$ 和 $p1_y+p2_x+1$ 的值。

```
for(int i=1;i<=n;i++){
	for(int j=i+1;j<=n;j++){
		if(bol[i][j]){//排除掉有边的情况，这就是建图时多存储一个bool数组的作用
			continue;
		}
		if((p1[i]+p2[j])+1>=p1[t]&&(p2[i]+p1[j])+1>=p1[t]){//比较
			cnt++;//如果这条新路的长度比原最短路长，计数器加一
		}
	}
}
```

[洛谷 AC记录](https://www.luogu.com.cn/record/51753530)

[CF AC记录](https://codeforces.com/contest/954/submission/119305840)

---

## 作者：StayAlone (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF954D)
### 题意

给定一个 $n$ 个点，$m$ 条边的**无向联通图**。你现在可以随意将两个没有连起来的点相连（只能连一条），输出有多少种连法不影响点 $s$ 到点 $t$ 的最短路径长度。  

**点的编号由 $1$ 到 $n$，且边权均为 $1$。**  

### 思路  

要从 $s$ 到 $t$，若会影响最小值，肯定经过了刚才连上的一条边。  
现称：

- $d1_i$ 表示从 $s \to i$ 的最短路长度；
- $d2_i$ 表示从 $i \to t$ 的最短路长度，同时因为这是无向图，故 $d2_i$ 的含义 $\Leftrightarrow t \to i$ 的最短路长度；
- 连上的边是 $x$ 与 $y$ 这条边。

则，从 $s$ 到 $t$ 有两种情况：  
1. $s \to x \to y \to t$；
1. $s \to y \to x \to t$。  

由于 $x \to y$ 的权是 $1$，
则两种情况所对应的距离分别是：  
1. $ans1 = d1_x + 1 + d2_y$
1. $ans2 = d1_y + 1 + d2_x$

由于 $s \to t$ 的最短路的长度是 $d1_t$ $(d1_t = d2_s$，都是这个最短的长度$)$。  

如果 $\min(x1, x2) < d1_t$，说明影响了，我们要求不影响的条数，故
- 如果 $\min(x1, x2) \geqslant d1_t$，`cnt++`。


**本题的大体思路总结：**  
1. 预处理 $d1$ 和 $d2$；
1. $O(n^2)$ 枚举每一对 $x$ 和 $y$，如果 $x \ne y \land x$ 和 $y$ 之间没有连边，求出 $ans1$ 和 $ans2$，并判断是否合法；
1. 输出答案。  

下面简单说一下预处理 $d1$ 和 $d2$。  
本题没有重边，故可以邻接矩阵来存图。  
直接用 bfs 算出所有点的最短路。  

- 求 $d1$ 时，队列中先插入 $s$，接下来扩展到下一个点；  
- 求 $d2$ 时，队列中先插入 $t$，接下来同上。  

解释一下第三个~~最简单的~~样例：  
![](https://cdn.luogu.com.cn/upload/image_hosting/tvqt5lrq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  

如图，从 $1 \to 5$，原图的最短路长度为 $2$， 有以下 $3$ 中连法使得最短路长度不变：  

![](https://cdn.luogu.com.cn/upload/image_hosting/dq1sn3g5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
1. 连接 $2 \to 3$，最短路长度不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/hdgk77yk.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
2. 连接 $2 \to 4$，最短路长度不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/81wc8vkb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
3. 连接 $3 \to 4$，最短路长度不变。  

故输出 $3$。

[AC code记录](https://www.luogu.com.cn/record/51754453)

```cpp
#include <bits/stdc++.h>
#define fr(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
int n, m, s, t, x, y, cnt, d1[1010], d2[1010], link[1010][1010];
bool vis[1010];
queue<int>q;

int min(int x, int y)
{
	return x < y ? x : y;
}

void bfs(int *dis)
{
	while (q.size())
	{
		int now = q.front(); q.pop();
		fr(i, 1, n)
		{
			if (!link[now][i] || vis[i]) continue;
			vis[i] = true, dis[i] = dis[now] + 1, q.push(i);
		}
	}
	fr(i, 1, n) vis[i] = false; // 清空数组 
	while (q.size()) q.pop();
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	fr(i, 1, m) scanf("%d%d", &x, &y), link[x][y] = 1, link[y][x] = 1;
	vis[s] = true, /*这里数组标 true 不能忘*/q.push(s), bfs(d1);
	vis[t] = true, q.push(t), bfs(d2);
	fr(i, 1, n) fr(j, i, n)
	{
		if (i == j || link[i][j]) continue; // 如果本来就有边或者 i = j，continue 
		int ans1 = d1[i] + 1 + d2[j],
			ans2 = d1[j] + 1 + d2[i];
		cnt += min(ans1, ans2) >= d1[t]; // 如果两种方案的最小值大于等于原本的最短路的长度，说明合法 
	}
	printf("%d", cnt);
	return 0;
}
}
```

---

## 作者：bwoi (赞：2)

### 为什么没有人用floyd呢？

让我们先做一道不等式题(~~关于不等式其实我一道也不会~~)

已知

$$2<=n<=1000$$ 
求
$$n^3$$
的取值范围 

**不难发现一个秘密:**

$$8<=n^3<=10^9$$

 可以~~通过卡常的方法~~通过本题

### 作为本题目前唯一一个以 floyd AC的，荣幸的以他人10多倍的时间稳居榜单最后一名。

**下面是极简代码：**

```
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstdlib>
using namespace std;

int n,m,s,t,ans; 
int f[1005][1005]; 

int main()
{	
	cin>>n>>m>>s>>t; 
	
	for(int i=1;i<=n;++i) 
	    for(int j=1;j<=n;++j)
	        if(i!=j) //初始化
		    f[i][j]=1000000000; 
	
	for(int i=1;i<=m;++i) 
	{
	    int x,y;
            cin>>x>>y; 
	    f[x][y]=f[y][x]=1; //建图
	} 
	
	for(int k=1;k<=n;++k) //floyd
	    for(int i=1;i<=n;++i) 
	        for(int j=1;j<=n;++j) 
                    f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	
	for(int i=1;i<n;++i)
	    for(int j=i+1;j<=n;++j) 
		if(f[i][j]!=1&&min(f[i][s]+f[t][j],f[i][t]+f[s][j])+1>=f[s][t]) //判断是否有边及比较
	    	    ans++;
	
	cout<<ans<<'\n'; 
	 
	return 0;
}
```

---

## 作者：ifyml (赞：1)

## 这是一道类似模板的模板题...
### 用两次Dijkstra：从S开始，从T开始
### 然后判断<i,j>这条边是否会影响最短路
```cpp
#include<cstdio>
#include<vector>
#include<queue>
#define NN 1001
#define inf 0x7fffffff
using namespace std;
int N,M,S,T,A,B,C,D1,D2,ANS;
int used[NN][3],dis[NN][3],map[NN][NN];
struct ss{
	int to,c;
	bool operator < (const ss &r)const{return r.c<c;}
};
vector<int>q[NN];
void Dij(int s,int c)
{
	for(int i=1;i<=N;i++)dis[i][c]=inf;
	dis[s][c]=0;
	priority_queue<ss>que;
	que.push((ss){s,0});
	while(!que.empty())
	{
		ss t=que.top();que.pop();
		int u=t.to;
		if(used[u][c])continue;
		used[u][c]=1;
		for(int i=0;i<q[u].size();i++)
		{
			int v=q[u][i];
			if(!used[v][c]&&dis[v][c]>dis[u][c]+1)
			{
				dis[v][c]=dis[u][c]+1;
				que.push((ss){v,dis[v][c]});
			}
		}
	}
}
int main()
{
	//freopen("c.in","r",stdin);
	scanf("%d%d%d%d",&N,&M,&S,&T);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d",&A,&B);
		map[B][A]=map[A][B]=1;
		q[A].push_back(B);
		q[B].push_back(A);
	}
	Dij(S,1);//从S开始
    Dij(T,2);//从T开始
	for(int i=1;i<N;i++)
	 for(int j=i+1;j<=N;j++)
	  if(!map[i][j])//两个点是否连通
	  {
	  	D1=dis[i][1]+dis[j][2]+1;
	  	D2=dis[i][2]+dis[j][1]+1;
	  	if(min(D1,D2)>=dis[T][1])//用最短的这条和最优解比较
        //因为最短的这条才是当前图中的这条
	  	 ANS++;//如果不影响最优解，则ans++
	  }
	printf("%d\n",ANS);
	return 0;//OK.
}
```

---

## 作者：HC20050615 (赞：0)

# 题意分析
对没有连边的两个点连边，问有多少种连边方式不会影响s->t的最短路长度？
# 思路
分别以s、t为源点跑最短路（我用的dijkstra）

新建立一条边后，若最短路发生变化，则一定经过了这条新边。

故我们可枚举点i、j。

如果s->i->j->t或者s->j->i->t的路径长度都不小于原最短路长度。
则可知连接边i,j后不会改变最短路。

（以数组f表示s到其他点的最短路，以f'表示t到其他点的最短路,最短路长度为L）

则上述条件可表示为f[i]+f'[j]+1>=L&&f[j]+f'[i]+1>=L

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,t;
bool b[1001][1001];//用临接表存储较为方便
int f[200001];
int _f[200001];
typedef pair<int,int>p;
struct cmp{
	bool operator()(const p a,const p b)
	{
		return a.second>b.second;
	}
};
priority_queue<pair<int,int>,vector<pair<int,int> >,cmp>q;
inline int read() {
    int x=0,w=1; 
	char c=getchar();
    while(c<'0'||c>'9') 
	{ 
		c=getchar(); 
	}
    while(c>='0'&&c<='9') 
	{
		x=x*10+c-'0';
		c=getchar();
	}
    return x;
}
int main()
{
	cin>>n>>m>>s>>t;
	int tot=0;
	for(register int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		b[x][y]=b[y][x]=1;
	}
	for(register int i=1;i<=n;i++)
	{
		f[i]=0x7fffffff;
		_f[i]=0x7fffffff;
	}
	q.push(make_pair(s,0));
	f[s]=0;
	while(!q.empty())
	{
		int now=q.top().first;
		int k=q.top().second;
		q.pop();
		if(k!=f[now])
		{
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(b[now][i])
			{
				if(f[i]>f[now]+1)
				{
					f[i]=f[now]+1;
					q.push(make_pair(i,f[i]));
				}
			}
		}
	}
	q.push(make_pair(t,0));
	_f[t]=0;
	while(!q.empty())
	{
		int now=q.top().first;
		int k=q.top().second;
		q.pop();
		if(k!=_f[now])
		{
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(b[now][i])
			{
				if(_f[i]>_f[now]+1)
				{
					_f[i]=_f[now]+1;
					q.push(make_pair(i,_f[i]));
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(!b[i][j])
			{
				if(f[i]+_f[j]+1>=f[t]&&f[j]+_f[i]+1>=f[t])
				{
					ans++;
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Create_Random (赞：0)

蒟蒻思路：

先求出$s$到$t$的最短路

再$n^2$求出走这条加上的路的最短路

具体操作：

先分别从$s$和$t$开始跑最短路

当要添加的地方没有边时添加上

然后求添的边的两个端点分别到$s$和$t$的最短路

(如果都小于原先的最短路就$ans++$)

贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,s,t;
int g[1010][1010];
int dis[1010];
int dis2[1010];
bool vis[1010];
int ans;
void dij(int s)//Dijkstra模板
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    int minn,next;
    dis[s]=0;
    for(int i=1;i<=n;i++) 
	{
        minn=0x3f3f3f3f;
        for(int j=1;j<=n;j++) 
		{
            if(!vis[j]&&dis[j]<minn) 
			{
                minn=dis[j];
                next=j;
            }
        }
        vis[next]=1;
        for(int j=1;j<=n;j++) 
		{
            if(!vis[j]&&dis[j]>dis[next]+g[next][j]&&g[next][j])
			{
                dis[j]=dis[next]+g[next][j];
            }
        }
    }
}
void dij2(int s) 
{
    memset(dis2,0x3f,sizeof(dis2));
    memset(vis,0,sizeof(vis));
    int minn,next;
    dis2[s]=0;
    for(int i=1;i<=n;i++) 
	{
        minn=0x3f3f3f3f;
        for(int j=1;j<=n;j++) 
		{
            if(!vis[j]&&dis2[j]<minn) 
			{
                minn=dis2[j];
                next=j;
            }
        }
        vis[next]=1;
        for(int j=1;j<=n;j++) 
		{
            if(!vis[j]&&dis2[j]>dis2[next]+g[next][j]&&g[next][j])
			{
                dis2[j]=dis2[next]+g[next][j];
            }
        }
    }
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u][v]=1;
		g[v][u]=1;//无向图！
	}
	dij(s);
	dij2(t);//分别从s和t跑最短路
	for(int i=1;i<n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(g[i][j]==0&&dis[t]<=dis[i]+dis2[j]+1&&dis[t]<=dis[j]+dis2[i]+1)
			{
				ans++;//如果添的边的两个端点分别到s和t的最短路都小于原先的最短路就ans++
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

