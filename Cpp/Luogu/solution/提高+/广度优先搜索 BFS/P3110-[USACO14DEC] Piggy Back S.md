# [USACO14DEC] Piggy Back S

## 题目描述

Bessie 和 Elsie 在不同的区域放牧，他们希望花费最小的能量返回谷仓。从一个区域走到一个相连区域，Bessie 要花费 $B$ 单位的能量，Elsie要花费 $E$ 单位的能量。

如果某次他们两走到同一个区域，Bessie 可以背着 Elsie 走路，花费 $P$ 单位的能量走到另外一个相连的区域。当然，存在 $P>B+E$ 的情况。

相遇后，他们可以一直背着走，也可以独立分开。

Bessie 从 $1$ 号区域出发，Elsie 从 $2$ 号区域出发，两个人都要返回到位于 $n$ 号区域的谷仓。

## 说明/提示

$1 \leq B,E,P,n,m \leq 4 \times 10^4$。

#### 样例解释：
Bessie 从 1 走到 4，Elsie 从 2 走到 3 再走到 4。然后，两个人一起从 4 走到 7，再走到 8。

## 样例 #1

### 输入

```
4 4 5 8 8 
1 4 
2 3 
3 4 
4 7 
2 5 
5 6 
6 8 
7 8 ```

### 输出

```
22 
```

# 题解

## 作者：基地A_I (赞：27)

# 题解：P3110 驮运Piggy Back
### 题目大意：
- 给出一个无向图，Bessie从1号仓库走到n号（每次花费B）， Elsie从2号仓库走到n号（每次花费E），如果两个人走同一条路花费P，求总花费最小。
- 输入B，E，P，n，m和m条边的联通情况
- 输出最少花费。
### 题目分析：
- （~~dalao跳过~~）我刚开始看到这个题目的时候，确实无法动笔。于是我抱着学(jie)习(jian)的心态打开了题解，发现题解里的大佬都在说什么3个SPFA，3个Dijkstra，跑三遍最短路等等。经过一番思索后，我终于明白了他的意思，所以在这里给还没有弄懂的同学解释一下。
### 解题方法
- 先跑三遍最短路（SPFA或者是Dijkstra ~~当然如果你是大佬Bfs也可以~~），分别得到Bessie从①出发的最短路,Elsie从②出发的最短路,和从n出发到其他每个点的最短路。最后枚举所以的点
```cpp
ans = max(ans ,B*disB[i]+E*disE[i]+P*disP[i]);
```

- #### 解释：这个式子代表走着条路的花费，分别是Bessie到i点的距离+Elsie到i点的距离+B&&E到n点的花费。

### 最后
- 感谢 题解dalao @ezoixx♂130 提供思路（~~这个名字有点哲学啊~~）
- ## 祝你AC（~~其实这道题还是蛮水的~~）
- 具体代码如下（温馨提示：不要抄袭）：
```cpp
#include<algorithm>
#include<iostream>
#include<string.h>
#include<cstdio>
#include<cmath>
#include<queue>
#define N 100007
using namespace std;
int B,P,E,n,m,cnt,ans;	 
int head[N],disB[N],disP[N],disE[N];
struct Edge
{
	int next,to;	//边没有权值 
}edge[N];	//链式前向星存图 
void add(int u,int v)	//增加边 
{
	edge[++cnt].next = head[u];
	edge[cnt].to = v;
	head[u] = cnt;
}
//	一个朴素的SPFA（QWQ） ，传入s源点，和dis数组（最短路数组） 
void SPFA(int s,int dis[])	 
{
//	int num[N];		//无负环
	queue<int> q;
	bool vis[N];
	for(int i=1;i<=n;++i) dis[i] = 88888888;
//	printf("BiG TesT : dis=%d",dis[5]);
	memset(vis,0,sizeof(vis));
	q.push(s) ,vis[s] = 1 ,dis[s] = 0;
	while(!q.empty())
	{
		int cur = q.front();
		q.pop() ,vis[cur] = 0;
		for(int i=head[cur];i;i=edge[i].next)
		{
			int v = edge[i].to ,w=1;	//权值设置为1 
			if(dis[v] > dis[cur]+w)
			{
				dis[v] = dis[cur]+w;
				if(!vis[v]) vis[v] = 1 ,q.push(v);
			}
		}
	}
	while(1) cout << "Plagiarists are shameless" << endl;
//	请大家自行翻译一下QWQ 
}
int main()
{
//	printf("%d",ans);
	scanf("%d%d%d%d%d",&B,&E,&P,&n,&m);
	for(int i=1,u,v;i<=m;++i)
		scanf("%d%d",&u,&v) ,add(u,v) ,add(v,u);
//	以上输入不用解释吧？ 
	SPFA(1,disB);	//搜B 
	SPFA(2,disE);	//搜E 
	SPFA(n,disP);	//从n开始搜的P 
//	打擂台 
	ans = 0xfffffff;
	for(int i=1;i<=n;++i)
		ans = min(ans ,B*disB[i]+E*disE[i]+P*disP[i]);
	printf("%d",ans);
	return 0;	//完美结束 
}
```
求管理大大批过 QWQ ！

---

## 作者：一只书虫仔 (赞：8)

[Best Wath in the Blog](https://www.luogu.com.cn/blog/Shuchong/)

### Description

> [P3110](https://www.luogu.com.cn/problem/P3110)    
> 一张 $n$ 点 $m$ 边的无向图，小 B 要从 $1$ 走到 $n$，每条边要花费 $b$，小 E 要从 $2$ 走到 $n$，每条边花费 $e$，当小 B 和小 E 一块走的时候，因为 $\color{Orange}\text{友谊}$ 地久天长他们一共只需要花费 $p$，他们也可以各走各的。求最小花费。    
> $1 \le n,m,b,e,p\le 4 \times 10^4$，$n \ge 3$

### Solution

模拟赛题目，感谢昨天在做 P3106 时 @limaopipi2022 给了我特殊的带数组 SPFA 的方法。（今天做这题用上了）

主要就是分三个 SPFA：

- 第一个 SPFA 是小 B 的，从 $1$ 到 $n$
- 第二个 SPFA 是小 E 的，从 $2$ 到 $n$
- 第三个 SPFA 是全局的，反向全图最短路

在最后对于每一个点 $i$，计算 
$$disb_i\times b+dise_i \times e+disa_i \times p$$
的最小值。

需要注意的就是，不知道是否有些人跟我一样爱用优先队列搞 SPFA，这题的 SPFA 不能用优先队列，只能用普通的队列。

那我在最开始说的带数组 SPFA 是怎样的呢？就是把 SPFA 后面的参数加上两个，$s$ 和 $dist$ `void SPFA (int s, int *dist)` 然后底下就正常 SPFA 就可以了啦。可以这么搞得原因就是因为数组是指针，指向函数的数组指针对于进行 SPFA 的数组也有影响。（高精应该有人就是这么打的，比如我）

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node {
	int val, next, len;
} e[100086];

int b, e1, p, n, m, cnt;
int head[100086];
int disb[100086], dise[100086], disa[100086];
int sum[100086];


void AddEdge (int u, int v, int w) {
	e[++cnt].val = v;
	e[cnt].next = head[u];
	e[cnt].len = w;
	head[u] = cnt;
}

void SPFA (int s, int *dist) {
	queue <int> q;
	for (int i = 1; i <= n; i++)
		dist[i] = 0x3f3f3f3f;
	dist[s] = 0;
	sum[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		sum[cur] = 0;
		for (int p = head[cur]; p > 0; p = e[p].next)
			if (dist[e[p].val] > dist[cur] + e[p].len) {
				dist[e[p].val] = dist[cur] + e[p].len;
				if (!sum[e[p].val]) {
					q.push(e[p].val);
					sum[e[p].val] = 1;
				}
			}
	}
}

int main () {
	scanf("%d%d%d%d%d", &b, &e1, &p, &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v, 1);
		AddEdge(v, u, 1);
	}
	SPFA(1, disb), SPFA(2, dise), SPFA(n, disa);
	int Min = 1e9;
	for (int i = 1; i <= n; i++)
		Min = min(Min, disb[i] * b + dise[i] * e1 + disa[i] * p);
	printf("%d", Min);
	return 0;
}
```

By Shuchong     
2020.7.12

---

## 作者：雨季 (赞：6)

# 题意
Bessie 和 Elsie 分别从 $1$ , $2$ 出发到 $n$ ，Bessie移动一次的代价是 $B$，Elsie移动一次的代价是 $E$，两人相遇后Bessie可以驮Elsie代价是 $P$。问到达终点 $n$ 的最小代价和。
# 题解
其实两人相遇后又分开的情况不用考虑，由于从一个点到达终点的最短路径的长度是一定的，所以哪个更优就取决于所加的权值。  
如果 $B+E<=P$ ，那么不分开一定不会差；  
如果 $B+E\ \ \ >P$ ，那么两人还不如不相遇，各走各自的路，也就是最后在 $n$ 相遇。  
所以，只需要分别从 $1$，$2$，$n$ 跑一边 $bfs$ ，求出最短路径的长度，然后暴力枚举两个人相遇的点，取最小值即可。
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define N 40005
#define M 1000005

int B,E,P,n,m;

inline int read() {
	int tmp=0,w=1;
	char ch=0;
	while(!isdigit(ch)) {if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)) tmp=(tmp<<1)+(tmp<<3)+ch-'0',ch=getchar();
	return tmp*w;
}

struct node {
	int v,nex;
}e[M<<1];
int tot,h[N];
void add(int u,int v) {
	e[++tot].v=v,e[tot].nex=h[u],h[u]=tot;
}

int dis[3][N];
bool vis[3][N];
queue<int>q;
void bfs(int t) {
	if(t==0) vis[t][1]=1,q.push(1);
	else if(t==1) vis[t][2]=1,q.push(2);
	else vis[t][n]=1,q.push(n);
	int x,xx;
	while(!q.empty()) {
		x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].nex) {
			xx=e[i].v;
			if(!vis[t][xx]) {
				vis[t][xx]=1;
				dis[t][xx]=dis[t][x]+1;
				q.push(xx);
			}
		}
	}
} 

int main()
{
	B=read(),E=read(),P=read(),n=read(),m=read();
	int u,v;
	for(int i=1;i<=m;++i) u=read(),v=read(),add(u,v),add(v,u);
	bfs(0);
	bfs(1);
	bfs(2);
	int ans=1e9;
	for(int i=1;i<=n;++i) ans=min(ans,dis[0][i]*B+dis[1][i]*E+dis[2][i]*P);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：SymphonyOfEuler (赞：5)

这是我做过相当简单的最短路好题，而且还是蓝色的。

说白了就是最短路，变一下。

Bessie和Elsie是两头USACOW的著名牛~~鬼都知道~~，他们放牧的时候，希望花费尽量少的力气回谷仓，他们自己走花费的精力单位分别为b和e，但是他们可以一个背着一个一起走。问花费最小的力量回到谷仓。

### **题解：**

我们可以把这个问题拆成三个最短路问题，一个是Bessie的，一个是Elsie的，还有一个是一个背着一个的，这样，我们所有的最短路dis数组里乘以他们的单位的和就是他们所花费的最小体力，所以我们跑完三遍最短路，枚举一下dis数组，记录最小值就行了。

注意，我们不需要写三个最短路，可以调函数时传进去两个参数，一个是起始点，还有就是这次要操作的dis数组，比如第一次掉disB，第二次disE，第三次disP。第一次起始点为1，第二次为2，第三次为n，具体题目中已经说了。

**Bessie and Elsie start in fields 1 and 2, respectively. The barn resides in field N.**

这题还没有给数据范围，我就是开了$10^5$，就可以过。

程序看不懂的可以看注释

代码：

```
#include <bits/stdc++.h>//万能头

using namespace std;

const int N = 100005;

struct node {//结构体写前向星
    int v, u, w;
} pool[N];

int b, e, p, n, m, nn;
int head[N];
int disB[N], disE[N], disP[N];
int vis[N];


void add(int u, int v, int w) {//前向星
    pool[++nn].v = v;
    pool[nn].u = head[u];
    pool[nn].w = w;
    head[u] = nn;
}

void spfa(int s/*起始点*/, int dis[N]/*操作的dis*/) {//spfa函数
    for (int i = 1; i <= n; i++) dis[i] = 0x3f3f3f3f;//初始化
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i > 0; i = pool[i].u)
            if (dis[pool[i].v] > dis[u] + pool[i].w) {
                dis[pool[i].v] = dis[u] + pool[i].w;
                if (!vis[pool[i].v]) {
                    q.push(pool[i].v);
                    vis[pool[i].v] = 1;
                }
            }
    }
}

int main() {
    cin >> b >> e >> p >> n >> m;
    for (int i = 1; i <= m; i++) {//无向图建图
        int u, v;
        cin >> u >> v;
        add(u, v, 1);
        add(v, u, 1);
    }
    spfa(1, disB);//Bessie的SPFA
    spfa(2, disE);//Elsie的SPFA
    spfa(n, disP);//一起的SPFA
    int minn = 0x3f3f3f3f;//minn定的大一点
    for (int i = 1; i <= n; i++) {
        minn = min(minn, disB[i] * b /*bessie体力*/ + disE[i] * e /*Elsie体力*/ + disP[i] * p/*together 体力*/);//求最小体力
    }
    cout << minn << '\n';//输出
    return 0;
}
```

看蒟蒻写的这么认真，点个赞再走呗~


---

## 作者：My_666 (赞：3)

# 算法：最短路＋枚举
## 题目概括：

Bessie 在 1 号点，Elsie在 2 号点，且移动一次的代价分别为a、b。但是 Bessie 可以背着 Elsie 走路（前提是必须相遇），代价变为c。求： Bessie 和 Elsie 都到达 n 号点的最小代价。

## 题目分析：

题意还是比较清晰的，一看就是最短路的板子题（不是）。算法不难，难就难在如何处理　Bessie　和　Elsie　何时相遇，所以，处理好这个问题是解题的关键。

## 解题技巧：

- 一开始把边权赋为１，要使用时乘一下各自的代价即可，从而避免多次建图带来的不便。

- 如果B + E >= P，则相遇后更优。依次枚举在哪个点相遇，并求出最小的代价即可。这就需要我们在１、２、ｎ分别跑一遍最短路（这里推荐dijkstra，毕竟出题组可以~~轻松~~卡掉spfa），最后求出最小的dis1+dis2+disn即可。

- 如果B + E < P ,就让P = E + B（想想为什么）。

- 虽然题目说相遇之后可以分开，但是如果我们这样操作后其实根本不需要考虑这种情况。

## 代码如下：

``` cpp
#include <bits/stdc++.h>//万能头大法好

using namespace std;

const int N = 1e7;
const int maxn = 200005;
const int maxm = 500005;

typedef long long ll; //做题的好习惯
typedef long double ld;

#define ms(a) memset(a, 0, sizeof(a))

int n, m, a, b, c;//a，b，c分别是题目中的B、E、P

struct Edge{
	int nxt, to, w;
}e[maxm];

int head[maxn], cnt;

void addEdge(int u, int v, int w) {
	e[++cnt] = (Edge){head[u], v, w}, head[u] = cnt;
}

int vis[maxn], dis[maxn];

//d1、d2、dn分别为从1、2、n出发的最短路
ll d1[maxn], d2[maxn], dn[maxn], minn = 1e12;//不清楚？最好用long long吧……

void dijkstra(int s) {
	for (int i = 1; i <= n; i++) dis[i] = 0x3f3f3f3f;
	priority_queue< pair<int, int> > q;
	q.push(make_pair(0, s));
	dis[s] = 0;
	while (q.size()) {
		int u = q.top().second;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
} 

int main() {
	cin >> a >> b >> c >> n >> m;
	if (c > a + b) c = a + b;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		addEdge(u, v, 1);
		addEdge(v, u, 1);
	}
	//剩下的不想注释了，大家看看解题技巧就明白了
	dijkstra(1);
	for (int i = 1; i <= n; i++) d1[i] = (ll)dis[i] * a;
	ms(vis);
	dijkstra(2);
	for (int i = 1; i <= n; i++) d2[i] = (ll)dis[i] * b;
	ms(vis);
	dijkstra(n);
	for (int i = 1; i <= n; i++) dn[i] = (ll)dis[i] * c;
	for (int i = 1; i <= n; i++) 
		if (d1[i] + d2[i] + dn[i] < minn) minn = d1[i] + d2[i] + dn[i];
	cout << minn;
	return 0;
}
```

# 感谢！

---

## 作者：shadowice1984 (赞：2)

杀鸡焉用牛刀，bfs即可无需spfa

思路是处理这个点到1号点，2号点，n号点的距离。

然后枚举在每一个点会和的情况

花费=d1\*b+d2\*e+d3\*p;

别告诉我bfs你还不会写，

简单粗暴，算法复杂度O（n)

上代码~

```cpp
#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;
int b;int e;int p;int nx;int m;
struct node//保存到点1，2，n的距离
{
    int num;int d1;int d2;int d3;
}n[40010];int now;
struct data//邻接表
{
    int v;int next;
}edge[80020];int cnt;int alist[40010];
void add(int u,int v)
{
    edge[++cnt].v=v;
    edge[cnt].next=alist[u];
    alist[u]=cnt;
    return;
}
queue <node> q;
int res=0x3f3f3f3f;
int main()
{
    scanf("%d%d%d%d%d",&b,&e,&p,&nx,&m);
    for(int i=0;i<m;i++)//建图
    {
        int u;int v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    for(int i=1;i<=nx;i++)//初始化
    {
        n[i].num=i;
        n[i].d1=-1;
        n[i].d2=-1;
        n[i].d3=-1;
    }
    n[1].d1=0;n[2].d2=0;n[nx].d3=0;
    q.push(n[1]);//bfs膜板，裸的bfs
    while(!q.empty())
    {
        now=q.front().num;q.pop();
        int next=alist[now];
        while(next)
        {
            int v=edge[next].v;
            if(n[v].d1==-1)
            {
                n[v].d1=n[now].d1+1;
                q.push(n[v]);
            }
            next=edge[next].next;
        }
    }
    q.push(n[2]);//同上
    while(!q.empty())
    {
        now=q.front().num;q.pop();
        int next=alist[now];
        while(next)
        {
            int v=edge[next].v;
            if(n[v].d2==-1)
            {
                n[v].d2=n[now].d2+1;
                q.push(n[v]);
            }
            next=edge[next].next;
        }
    }
    q.push(n[nx]);//同上
    while(!q.empty())
    {
        now=q.front().num;q.pop();
        int next=alist[now];
        while(next)
        {
            int v=edge[next].v;
            if(n[v].d3==-1)
            {
                n[v].d3=n[now].d3+1;
                q.push(n[v]);
            }
            next=edge[next].next;
        }
    }
    for(int i=1;i<=nx;i++)//处理答案
    {
        if(n[i].d1==-1||n[i].d2==-1||n[i].d3==-1)//前提是该点必须能到达1，2，和n
        continue;
        res=min(res,n[i].d1*b+n[i].d2*e+n[i].d3*p);
    }
    printf("%d",res);
    return 0;//拜拜程序~
}
```

---

## 作者：奔波儿霸 (赞：2)

#### 瞎扯淡
建议去[我的博客](https://www.cnblogs.com/bljfy/p/9494330.html)阅读，以便有更好的阅读体验

#### 解题思路

看到下面很多人都在说什么遇到了之后要不要背着走，其实根本不需要，同样的我也是跑了三遍$SPFA$，求出了以$1$为起点到个点的$dist$，和以$2$为起点到个点的$dist$，还有以$n$为起点到个点的$dist$。

之后直接枚举两头牛在哪里相遇，相遇之后一起背着走的路程乘以$p+$相遇之前$B$走的距离乘以$b+$相遇之前$E$走的距离乘以$e$，去一个最小的这样的值就是答案。

关于为什么不需要分类讨论，因为你把每个点都枚举了一遍，即使存在$p>b+e$的情况，那这种情况就等价于两头奶牛在$n$点相遇。

#### 附上代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
const int maxn = 8e4+3, INF = 2147483647;
int b, e, p, n, m, fir[maxn], nxt[maxn], u[maxn], v[maxn], cnt;
int dist_n[maxn], dist_1[maxn], dist_2[maxn], w[maxn], Ans = INF;
bool vis[maxn];
inline int read() {
	int x = 0, f = 1; char c;
	while (c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while (c <= '9' && c >= '0') {x = x*10 + c-'0'; c = getchar();}
	return x * f;
}
inline void addedge(int x, int y, int z) {
	nxt[++cnt] = fir[x];
	fir[x] = cnt;
	u[cnt] = x, v[cnt] = y, w[cnt] = z;
}
inline void SPFA(int s, int *dist) {
	std::queue<int> Q;
	std::memset(vis, 0, sizeof(vis));
	std::fill(dist+1, dist+1+n, INF);
	vis[s] = 1, dist[s] = 0;
	Q.push(s);
	int x, k;
	while (!Q.empty()) {
		x = Q.front(), Q.pop();
		int k = fir[x];
		while (k != -1) {
			if(dist[v[k]] > dist[u[k]] + w[k]) {
				dist[v[k]] = dist[u[k]] + w[k];
				if(!vis[v[k]]) Q.push(v[k]);
			}
			k = nxt[k];
		}
		vis[x] = 0;
	}
}
int main() {
	b = read(), e = read(), p = read(), n = read(), m = read();
	std::memset(fir, -1, sizeof(fir));
	int x, y, z = 1;
	for(register int i=1; i<=m; i++) {
		x = read(), y = read();
		addedge(x, y, z), addedge(y, x, z);
	}
	SPFA(1, dist_1), SPFA(2, dist_2), SPFA(n, dist_n);
	for(int i=1; i<=n; i++)
		Ans = std::min(Ans, dist_1[i] * b + dist_2[i] * e + dist_n[i] * p);
	printf("%d", Ans);
}
```

---

## 作者：OIerAlbedo (赞：1)

首先我们要明白：如果两头牛背着走了，那么肯定是直接这样子走到终点了。
因为如果走走停停，最后加起来的能量与刚才所说的值是一样的。
因此问题就转换成了：两头牛分别从1，2两点走到一点，再从这一点两牛合二为一用P的能量走到N这个终点。
所以问题最后就变成了三个最短路
而观察发现N<=40000,所以就只能用SPFA或Dijkstra+堆优化
而还有一点很难想到，就是那个切换的地点只有知道了才能进行第三个最短路，而如果先枚举那个点在进行最短路的话，是肯定会超时的，所以我们又要换个思路：
因为所有的点他们都是要走到N这个点去的，所以我们不妨做一个从N开始的最短路，那么从任意一点到N的距离就都知道了，所以最后只要枚举那个切换点，然后再求出第一头奶牛他那个点的能量与第二头奶牛到那个点的能量与从那个点到终点的总和求个最小值就是问题的答案了。
```pascal
var min,cnt,x1,x2,x3,n,m,x,y,t,w:int64;
i:longint;
a,b,d,f1,f2,f3,f4:array[0..1000001] of int64;
f5:array[0..1000001] of boolean;
procedure add(x,y:longint);
begin
cnt:=cnt+1;a[cnt]:=y;b[cnt]:=d[x];d[x]:=cnt;
end;
begin
readln(x1,x2,x3,n,m);
for i:=1 to m do
   begin
   readln(x,y);
   add(x,y);add(y,x);
   end;
fillchar(f5,sizeof(f5),0);
t:=1;w:=1;f1[1]:=0;f4[1]:=1;f5[1]:=true;
while t<=w do
   begin
   i:=d[f4[t]];
   while i>0 do
       begin
       if f5[a[i]]=false then
          begin
          f5[a[i]]:=true;
          f1[a[i]]:=f1[f4[t]]+1;
          w:=w+1;f4[w]:=a[i];
          end;
       i:=b[i];
       end;
   t:=t+1;
   end;
fillchar(f5,sizeof(f5),0);
t:=1;w:=1;f2[2]:=0;f4[1]:=2;f5[2]:=true;
while t<=w do
   begin
   i:=d[f4[t]];
   while i>0 do
       begin
       if f5[a[i]]=false then
          begin
          f5[a[i]]:=true;
          f2[a[i]]:=f2[f4[t]]+1;
          w:=w+1;f4[w]:=a[i];
          end;
       i:=b[i];
       end;
   t:=t+1;
   end;
fillchar(f5,sizeof(f5),0);
t:=1;w:=1;f3[n]:=0;f4[1]:=n;f5[n]:=true;
while t<=w do
   begin
   i:=d[f4[t]];
   while i>0 do
       begin
       if f5[a[i]]=false then
          begin
          f5[a[i]]:=true;
          f3[a[i]]:=f3[f4[t]]+1;
          w:=w+1;f4[w]:=a[i];
          end;
       i:=b[i];
       end;
   t:=t+1;
   end;
min:=maxlongint*maxlongint div 4;
for i:=1 to n do
   if min>x1*f1[i]+x2*f2[i]+x3*f3[i] then
      min:=x1*f1[i]+x2*f2[i]+x3*f3[i];
writeln(min);
end.
```

---

## 作者：ezоixx130 (赞：1)

思路：

这是一道最短路的题目，然而要求3遍最短路。

Tips：可以将数组作为参数传入spfa()中。

用SPFA求出b、e、p的单源最短路db[]、de[]、dp[]。

然后暴力枚举她们相遇的点，更新答案，即ans=min(b\*db[i]+e\*de[i]+p\*dp[i])。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int b,e,p,n,m;

#define MAXN 100000

vector<int> edge[MAXN],we[MAXN];
int db[MAXN],de[MAXN],dp[MAXN],inque[MAXN];

void spfa(int x,int *d)
{
    queue<int> q;
    q.push(x);
    for(int i=1;i<=n;++i)
    {
        d[i]=100000;
    }
    d[x]=0;
    memset(inque,false,sizeof(inque));
    inque[x]=true;
    do
    {
        int u=q.front();
        q.pop();
        inque[u]=false;
        for(unsigned i=0;i<edge[u].size();++i)
        {
            int v=edge[u][i],w=we[u][i];
            if(d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if(!inque[v])
                {
                    inque[v]=true;
                    q.push(v);
                }
            }
        }
    }
    while(!q.empty());
}

int main()
{
    scanf("%d%d%d%d%d",&b,&e,&p,&n,&m);
    for(int i=1;i<=m;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        we[u].push_back(1);
        edge[v].push_back(u);
        we[v].push_back(1);
    }
    spfa(1,db);
    spfa(2,de);
    spfa(n,dp);
    int ans=2147483647;
    for(int i=1;i<=n;++i)
    {
        ans=min(ans,b*db[i]+e*de[i]+p*dp[i]);
    }
    printf("%d\n",ans);
}
```

---

## 作者：winmt (赞：1)

【分析】最短路大水题。先用SPFA求3次最短路，第一次是牛B从一号仓库为起始点的单源最短路db[]，第二次是牛E从二号仓库为起始点的单源最短路de[]，第三次是从n号仓库为起始点倒过来求的单源最短路dp[]。然后就类似于DP了：枚举每一个仓库为顶点i，每次计算db[i]+de[i]+dp[i]，意思是牛B单独到这个顶点最短路+牛E单独到这个顶点最短路+终点仓库n到这个顶点最短路（到达这个顶点i之后就可以背着走以至于只需要花费p的体力了），然后打擂台比最小值即可。

【代码】



    
        
     
    
    
    
    
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<deque>
#include<utility>
#include<map>
#include<set>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<sstream>
#include<cstring>
#include<bitset>
#include<stack>
using namespace std;
int b,e,p,n,m,x,y,z,s,ans;
struct sdt
{
    int to,w;
}v;
int d[40005],db[40005],de[40005],dp[40005];
bool vis[40005];
vector<sdt>cp[40005];
vector<pair<int,int> >rec;
void spfa(int st)
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)d[i]=2147483647;
    queue<int>q;
    d[st]=0;
    q.push(st);
    vis[st]=1;
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        vis[k]=0;
        for(int i=0;i<cp[k].size();i++)
        {
            v=cp[k][i];
            if(d[k]!=2147483647 && d[v.to]>d[k]+v.w)
            {
                d[v.to]=d[k]+v.w;
                if(!vis[v.to])
                {
                    vis[v.to]=1;
                    q.push(v.to);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d%d",&b,&e,&p,&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        rec.push_back(make_pair(x,y));
        v.to=y;
        v.w=b;
        cp[x].push_back(v);
        v.to=x;
        v.w=b;
        cp[y].push_back(v);
    }
    spfa(1);
    for(int i=1;i<=n;i++)
    {
        db[i]=d[i];
        cp[i].clear();
    }
    for(int i=0;i<rec.size();i++)
    {
        x=rec[i].first;
        y=rec[i].second;
        v.to=y;
        v.w=e;
        cp[x].push_back(v);
        v.to=x;
        v.w=e;
        cp[y].push_back(v);
    }
    spfa(2);
    for(int i=1;i<=n;i++)
    {
        de[i]=d[i];
        cp[i].clear();
    }
    for(int i=0;i<rec.size();i++)
    {
        x=rec[i].first;
        y=rec[i].second;
        v.to=y;
        v.w=p;
        cp[x].push_back(v);
        v.to=x;
        v.w=p;
        cp[y].push_back(v);
    }
    spfa(n);
    for(int i=1;i<=n;i++)
    {
        dp[i]=d[i];
        cp[i].clear();
    }
    ans=2147483647;
    for(int i=1;i<=n;i++)
    {
        ans=min(ans,db[i]+de[i]+dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：thelast (赞：0)

## 开心开心开心
### 第一次蓝题一遍过！！！哦耶。
(恶心的是英文，不知道数组要开多大。。)

### 正题：
首先翻译一下题
```
给出一个无向图，Bessie从1号仓库走到n号（每次花费B）， Elsie从2号仓库走到n号（每次花费E），如果两个人走同一条路花费P，求总花费最小。
输入B，E，P，n，m和m条边的联通情况
输出最少花费。
```
那么来看一下，由于我们不知道他们是否需要相遇，或者说在那个点相遇，但是有一点是明确的，如果说在相遇后背着走代价小，那么，往后就一定是一直背着的，而且在走到相遇的地点之前一定是自己走自己的。

那么，我们就要考虑他们在每一个点相遇的情况，而且已知对不同的情况来看，边权一定相同，所以只用求出需要经过的边数，再乘以对应情况即可。

so，在走到相遇点之前，两人一定走的是对应最短路才能减小话费，所以说可以的出min1=min(dis1[i]*b+dis2[i]*e+dis3[i]*p);这样得出的一定是走这个点的最小值。不相遇的情况即为在点n相遇。

那么，走三遍最短路，分别求出点1,点2，点n到每个点的最短路即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int b,e,p,n,m,disA[40001],disB[40001],disC[40001],head[40001];
int min1=2147483647,num;
bool dian[40001];
struct edge{
	int to,next,w;
}f[1000000];
struct node{
	int hao,dis1;
	bool operator<(const node &x)const{
		return x.dis1<dis1;
	}
};
void add(int a,int b,int c){
	f[++num].to=b;
	f[num].w=c;
	f[num].next=head[a];
	head[a]=num;return;
}
void dijstra(int fr){
	priority_queue< node >q;
	memset(disA,0x3f,sizeof(disA));
	memset(dian,0,sizeof(dian));
	disA[fr]=0;
	q.push((node){fr,0});
	while(!q.empty()){
		int x=q.top().hao;q.pop();
		if(dian[x])continue;
		dian[x]=1;
		for(int i=head[x];i;i=f[i].next){
			int y=f[i].to;
			if(disA[y]>disA[x]+f[i].w){
				disA[y]=disA[x]+f[i].w;
				q.push((node){y,disA[y]});
			}
		}
	}
}
int main(){
	cin>>b>>e>>p>>n>>m;
	for(int a,c,i=1;i<=m;i++){
		scanf("%d%d",&a,&c);
		add(a,c,1);add(c,a,1);
	}
	dijstra(2);
	for(int i=1;i<=n;i++)disB[i]=disA[i];
	dijstra(n);
	for(int i=1;i<=n;i++)disC[i]=disA[i];
	dijstra(1);
	for(int i=1;i<=n;i++)
		min1=min(min1,disA[i]*b+disB[i]*e+disC[i]*p);
	cout<<min1<<endl;
	return 0;
}
```

---

## 作者：Create_Random (赞：0)

在学校的模拟赛上做了类似的题，于是来写一下题解

本蒟蒻的思路：

返回谷仓的情况有两种

一是两头牛均单独走

二是在某个点进行驮运

可以先从1点和2点跑两遍最短路

求出两头牛均单独走时的花费

并存下到每个点的最短距离

然后从n点跑一遍最短路

求出从n点到i点的最短路

（也就是i点到n点的最短路）

并遍历两头牛分别单独走到一个点再驮运到n点的最优解

与两头牛均单独走的最短路进行比较

找到较小值即可得到最优解

本蒟蒻使用了堆优化的Dijkstra

~~SPFA被卡到不敢用了~~

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int to,w;
};
vector<node>g[40010];//本蒟蒻只会vector建图
struct point
{
    int d,dis;
    bool operator<(const point b)const//运算符重载
    {
        return dis>b.dis;
    }
};
int r,s,p,n,m;
int ans1,ans2=1e9;
int dis[40010],dis1[40010],dis2[40010],dis3[40010];
void pri_dij(int s)//堆优化Dijkstra模板
{
    priority_queue<point>q;
    bool vis[40010]={0};
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push({s,0});
    while(!q.empty())
    {
        point p=q.top();
        q.pop();
        long long u=p.d;
        if(vis[u])
        {
            continue;
        }
        vis[u]=1;
        for(int j=0; j<g[u].size();j++) 
        { 
            long long v=g[u][j].to,w=g[u][j].w;
            if(!vis[v]&&dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                q.push({v,dis[v]});
            }
        }
    }
}
int main()
{
	scanf("%d%d%d%d%d",&r,&s,&p,&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		node tmp;
		tmp.to=v;
		tmp.w=1;//由于权值不同，所以这里先存边数
		g[u].push_back(tmp);
		tmp.to=u;
		g[v].push_back(tmp);//存无向图
	}
	pri_dij(1);//从1点跑最短路
	for(int i=1;i<=n;i++)
	{
		dis1[i]=dis[i]*r;//求出第一只牛到i点的最短路
	}
	pri_dij(2);//从2点跑最短路
	for(int i=1;i<=n;i++)
	{
		dis2[i]=dis[i]*s;//求出第二只牛到i点的最短路
	}
	ans1=dis1[n]+dis2[n];//先存下单独走时的最小花费
	pri_dij(n);//从n点跑最短路
	for(int i=1;i<=n;i++)
	{
		dis3[i]=dis[i]*p;//求出从i点驮运至n点的最小花费
		ans2=min(ans2,dis1[i]+dis2[i]+dis3[i]);//存下两只牛先走到i点，再驮运至n点的最小花费
	}
	cout<<min(ans1,ans2);//输出单独走时和有驮运中的较小值
	return 0;
}
```


---

## 作者：AC_Automation (赞：0)

### 堆优$Dijkstra$

看到题，发现很明显，是最短路。那么，怎样求呢（毕竟不是[模板](https://www.luogu.org/problemnew/show/P4779)）

首先，如果两人不能背着走，那么直接以两人位置为源点跑两次$Dijkstra$，答案相加就好了

那么如果允许背着呢？

我们可以让$p=min(p,b+e)$，这样**只要两人相遇，就不会分开**

考虑再跑一遍$Dijkstra$，只不过以谷仓为源点。之后枚举每一个点作为两人相遇的地方，计算答案即可。

#### 一些小提示：
- 不确定自己写的$Dijkstra$对不对的，可以去[P4779](https://www.luogu.org/problemnew/show/P4779)提交一下试试~
- $SPFA$，$Dijkstra$，甚至$BFS$都能过
- 记得清空数组！记得清空数组！记得清空数组！

接下来就是代码了~

$code:$
```
#include<iostream>
#include<queue>
#include<functional>
#include<utility>
#include<cstring>
using namespace std;
struct edge{
	int v,next;
} a[80005];
int head[40005],cnt=0;
long long dis[3][40005];
bool vis[40005];
void add_edge(int u,int v){
	cnt++;a[cnt].next=head[u];
	a[cnt].v=v;head[u]=cnt;
}//链式前向星
void dijkstra(int val,int opt,int u){
	memset(dis[opt],0x7f,sizeof(dis[opt]));
	memset(vis,0,sizeof(vis));
	priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > pq;
	pq.push(make_pair(0,u));
	dis[opt][u]=0;pair<long long,int> v;
	while(!pq.empty()){
		v=pq.top();pq.pop();
		if(vis[v.second])continue;
		vis[v.second]=1;
		for(int i=head[v.second];i;i=a[i].next){
			if(dis[opt][a[i].v]>v.first+val&&!vis[a[i].v]){
				dis[opt][a[i].v]=v.first+val;
				pq.push(make_pair(dis[opt][a[i].v],a[i].v));
			}//松弛
		}
	}
}//Dijkstra
int main(){
	int b,e,p,n,m,u,v;
	cin>>b>>e>>p>>n>>m;p=min(p,b+e);
	for(int i=0;i<m;i++){
		cin>>u>>v;add_edge(u,v);add_edge(v,u);
	}
	dijkstra(b,0,1);
	dijkstra(e,1,2);
	dijkstra(p,2,n);//三次最短路
	long long ans=0x7f7f7f7f;
	for(int i=1;i<=n;i++)
		ans=min(ans,dis[0][i]+dis[1][i]+dis[2][i]);//计算答案
	cout<<ans;
	return 0;
}

```

---

## 作者：muller (赞：0)

发现好像要枚举一下那个点

但是每当枚举一次就要bfs一次

发现非常耗时

多算了许多无用的东西

所以我们考虑只bfs一边的高效算法

于是考虑直接反见图，然后bfs3遍

最后求一下和，去个min即可

当时比较菜，写的好像是spfa

连bfs都不会

qwq

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define         INF         99999999
#define         MAXN        40010
int B, F, P, mindis = INT_MAX, n, m;
int dis_1[MAXN], dis_2[MAXN], dis_n[MAXN];
vector<int>E[MAXN];
bool inq[MAXN];
void spfa_1() {
    queue<int>q;
    memset(inq, 0, sizeof(inq));
    while(!q.empty())q.pop();
    for(int i = 2;i <= n;i++)dis_1[i] = INF;
    q.push(1);dis_1[1] = 0;inq[1] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        int le = E[x].size();
        for(int i = 0;i < le;i++) {
            int y = E[x][i];
            if(dis_1[y] > dis_1[x] + 1) {
                dis_1[y] = dis_1[x] + 1;
                if(!inq[y]) {inq[y] = 1;q.push(y);}
            }
        }
        inq[x] = 0;
    }
}
void spfa_2() {
    queue<int>q;
    memset(inq, 0, sizeof(inq));
    while(!q.empty())q.pop();
    for(int i = 1;i <= n;i++)dis_2[i] = INF;
    q.push(2);dis_2[2] = 0;inq[2] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        int le = E[x].size();
        for(int i = 0;i < le;i++) {
            int y = E[x][i];
            if(dis_2[y] > dis_2[x] + 1) {
                dis_2[y] = dis_2[x] + 1;
                if(!inq[y]) {inq[y] = 1;q.push(y);}
            }
        }
        inq[x] = 0;
    }
}
void spfa_n() {
    queue<int>q;
    memset(inq, 0, sizeof(inq));
    while(!q.empty())q.pop();
    for(int i = 1;i < n;i++)dis_n[i] = INF;
    q.push(n);dis_n[n] = 0;inq[n] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        int le = E[x].size();
        for(int i = 0;i < le;i++) {
            int y = E[x][i];
            if(dis_n[y] > dis_n[x] + 1) {
                dis_n[y] = dis_n[x] + 1;
                if(!inq[y]) {inq[y] = 1;q.push(y);}
            }
        }
        inq[x] = 0;
    }
}
int main() {
    ios :: sync_with_stdio(false);
    cin >> B >> F >> P >> n >> m;
    for(int i = 1;i <= m;i++) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    spfa_1();spfa_2();spfa_n();
    for(int i = 1;i <= n;i++)mindis = min(mindis, dis_1[i] * B + dis_2[i] * F + dis_n[i] * P);
    cout << mindis << endl;
    return 0;
}
```


---

## 作者：Cxs3 (赞：0)

题目链接：https://www.luogu.org/problemnew/show/P3110

---

## 题目分析

题目大意就是：  
$Bessie$  从点$1$出发，$Elsie$从点$2$出发，向点$n$走去；其中$Bessie$每走一步需代价$B$，$Elsie$需代价$E$；两人相遇后，可以一起以$P$的代价继续走，也可以分开各走各的，求他们都到达点$n$所需的最小代价。  

很容易可以看出这是一个最短路的问题。  
易知：  
当$P<=B+E$时，相遇后一起走更好。  
当$P>B+E$时，各走各的更好。

所以我们可以枚举两人相遇的点$i(1<=i<=n)$，计算$f[1][i]*B+f[2][i]*E+f[n][i]*P$，并将它与$ans$进行比较，若小于$ans$则更新。  
（其中$f[a][b]$表示$a$到$b$的最短距离）

当$i==n$时，就是两人最终在$n$点相遇，即各走各的，中途不一起走，这样就不怕有$P>B+E$的情况了。

那么，$f$数组该如何处理呢？  
显然，我们可以跑$SPFA$。由于$n$较大（$40000$），所以不能开二维数组，只需开三个一维数组即可。

---

## 代码实现

```cpp
//代码丑勿喷QAQ
#include<bits/stdc++.h>
const int N=40000+10;
const int inf=0x3f3f3f3f;
using namespace std;
int b,e,p,n,m,ans;
int f1[N],f2[N],fn[N];
bool k[N];
vector<int> v[N];
void spfa(int now)
{
    int i,u,c;
    queue<int> q;
    memset(k,0,sizeof(k));
    q.push(now);
    k[now]=1;
    while(!q.empty())
    {
      u=q.front();
      q.pop();
      k[u]=0;
      for(i=0;i<v[u].size();i++)
      {
      	c=v[u][i];
      	if(now==1)
      	{
      	  if(f1[u]+1<f1[c])
      	  {
      	    f1[c]=f1[u]+1;
      	    if(!k[c]){q.push(c); k[c]=1;}
          }
          continue;
        }
        
        if(now==2)
        {
          if(f2[u]+1<f2[c])
      	  {
      	    f2[c]=f2[u]+1;
      	    if(!k[c]){q.push(c); k[c]=1;}
          }
          continue;
        }
        
        if(now==n)
        {
          if(fn[u]+1<fn[c])
      	  {
      	    fn[c]=fn[u]+1;
      	    if(!k[c]){q.push(c); k[c]=1;}
          }
        }
        
      }
    }
}
void csh()
{
    memset(f1,inf,sizeof(f1));
    f1[1]=0;
    memset(f2,inf,sizeof(f2));
    f2[2]=0;
    memset(fn,inf,sizeof(fn));
    fn[n]=0;
}
int main()
{
    int i,x,y,now;
    cin>>b>>e>>p>>n>>m;
    for(i=1;i<=m;i++)
    {
      cin>>x>>y;
      v[x].push_back(y);
      v[y].push_back(x);
    }
    csh();	
    spfa(1);
    spfa(2);
    spfa(n);
    ans=inf;
    for(i=1;i<=n;i++)
    {
      if(f1[i]==inf||f2[i]==inf||fn[i]==inf) continue;
      now=f1[i]*b+f2[i]*e+fn[i]*p;
      ans=min(ans,now);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：bits (赞：0)

**解题思路**

我们知道：$Bessie$和$Elsie$最终会汇合的。因此我们考虑汇合点的问题。这样自然就知道要不要驮着走了。

- 若在第$1$到$n-1$个点汇合，$Bessie$需要驮着$Elsie$到终点。

- 若在第$n$个点汇合，即是让$Bessie$和$Elsie$自己分别到终点。

所以，我们需要枚举汇合点，然后求出该点到第$1$，$2$，$n$个点的最短路即可。

由于边是无向的，我们可以预处理出第$1$，$2$，$n$个点的单源最短路径。

预处理时我们先将边权设为$1$，统计的时候分别乘上$B$，$E$，$P$即可。

**附上代码**

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cstdlib>
using namespace std;

//二进制快速读入
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){
    return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?EOF:*A++;
}
inline void qr(int &s){
    char c=gc(); s=0;
    for(;c<'0'||c>'9';c=gc());
    for(;c>='0'&&c<='9';c=gc())
        s=(s<<1)+(s<<3)+(c^48);
}
inline int mn(int x,int y){
    return x<y?x:y;
}

const int N=40001,K=3;
struct edge{
    int node,next;
}Edge[N<<1];
int n,m,tot,Dis[K][N],Head[N],v0,v1,v2,i,u,v,ans=2e9;
bool Inq[N];
inline void Add(int x,int y){
    Edge[++tot].node=y;
    Edge[tot].next=Head[x];
    Head[x]=tot;
}

void SPFA(int k,int s){//模板
//我们将三次求的最短路分别保存下来
    for(i=1;i<=n;++i){
        Dis[k][i]=1e9; Inq[i]=0;
    }
    Dis[k][s]=0; Inq[s]=1;
    queue<int> q; q.push(s);
    while(!q.empty()){
        u=q.front(); q.pop(); Inq[u]=0;
        for(int t=Head[u];t;t=Edge[t].next){
            v=Edge[t].node;
            if(Dis[k][u]+1<Dis[k][v]){
          	//边权初始为1
                Dis[k][v]=Dis[k][u]+1;
                if(!Inq[v]){
                    q.push(v); Inq[v]=1;
                }
            }
        }
    }
}

int main(){
    qr(v0); qr(v1); qr(v2); qr(n); qr(m);
    while(m--){
        qr(u); qr(v);
        Add(u,v); Add(v,u);
    }
    SPFA(0,1); SPFA(1,2); SPFA(2,n);//预处理
    for(i=1;i<=n;++i)//枚举汇合点
        ans=mn(ans,Dis[0][i]*v0+Dis[1][i]*v1+Dis[2][i]*v2);
    printf("%d\n",ans);
    return 0;
}
```

**管理员大佬求通过**

---

## 作者：aha浮云 (赞：0)

水一波题解....
嗯这个题很坑是无向图...
首先我们分析一下 
就是两个人如果要相遇并且一起走的话
一定会选择最短路（把路的边权看做1）
而若P < B + E
他们就不会再分开 因为一起走最短路一定比分开走最短路优
那么3遍spfa就够了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n = 40010;

struct Edge
{
	int to, val;
	Edge(){}
	Edge(int a, int b)
	{
		to = a;
		val = b;
	}
};

int n, m, B, E, P;
vector<Edge> G[max_n], RG[max_n];
int dis_fir[max_n], dis_sec[max_n], rdis[max_n];
bool vis[max_n];

void spfa(int s)
{
	memset(vis, 0, sizeof(vis));
	memset(dis_fir, 0x3f, sizeof(dis_fir));
	vis[s] = 1;
	dis_fir[s] = 0;
	deque<int> q;
	q.push_back(s);
	while(!q.empty())
	{
		int top = q.front();
		q.pop_front();
		vis[top] ^= 1;
		for(int i = 0;i < G[top].size(); i++)
		{
			int u = G[top][i].to;
			if(dis_fir[u] > dis_fir[top] + G[top][i].val)
			{
				dis_fir[u] = dis_fir[top] + G[top][i].val;
				if(!vis[u])
				{
					if(!q.empty() && dis_fir[u] < dis_fir[q.front()])
					q.push_front(u);
					else q.push_back(u);
					vis[u] ^= 1;
				}
			}
		}
	}
}

void sec_spfa(int s)
{
	memset(vis, 0, sizeof(vis));
	memset(dis_sec, 0x3f, sizeof(dis_sec));
	vis[s] = 1;
	dis_sec[s] = 0;
	deque<int> q;
	q.push_back(s);
	while(!q.empty())
	{
		int top = q.front();
		q.pop_front();
		vis[top] ^= 1;
		for(int i = 0;i < G[top].size(); i++)
		{
			int u = G[top][i].to;
			if(dis_sec[u] > dis_sec[top] + G[top][i].val)
			{
				dis_sec[u] = dis_sec[top] + G[top][i].val;
				if(!vis[u])
				{
					if(!q.empty() && dis_sec[u] < dis_sec[q.front()])
					q.push_front(u);
					else q.push_back(u);
					vis[u] ^= 1;
				}
			}
		}
	}
}

void rspfa(int s)
{
	memset(vis, 0, sizeof(vis));
	memset(rdis, 0x3f, sizeof(rdis));
	vis[s] = 1;
	rdis[s] = 0;
	deque<int> q;
	q.push_back(s);
	while(!q.empty())
	{
		int top = q.front();
		q.pop_front();
		vis[top] ^= 1;
		for(int i = 0;i < G[top].size(); i++)
		{
			int u = G[top][i].to;
			if(rdis[u] > rdis[top] + G[top][i].val)
			{
				rdis[u] = rdis[top] + G[top][i].val;
				if(!vis[u])
				{
					if(!q.empty() && rdis[u] < rdis[q.front()])
					q.push_front(u);
					else q.push_back(u);
					vis[u] ^= 1;
				}
			}
		}
	}
}
int main()
{
	cin >> B >> E >> P >> n >> m;
	int a, b;
	for(int i = 1;i <= m; i++)
	{
		scanf("%d%d", &a, &b);
		G[a].push_back(Edge(b, 1));
		G[b].push_back(Edge(a, 1));
	}
	spfa(1);
	sec_spfa(2);
	rspfa(n);
	if(B + E < P)
	printf("%d", dis_fir[n] * B + dis_sec[n] * E);
	else 
	{
		int ans = 9999999;
		for(int i = 1;i <= n; i++)
		ans = min(ans, dis_fir[i] * B + dis_sec[i] * E + rdis[i] * P);
		cout << ans << endl;
	}
	return 0;
}
```
注释我就不加了
spfa三遍都是复制的
所以看着码的很长实际只有一点点
关键是贪心选择

---

## 作者：曹老师 (赞：0)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco14dec-piggyback.html)

最短路径。貌似没有dij的代码，~~虽然dij此题比spfa跑得慢罢了。~~

做三次最短路径，求出每一个点到1 ， 2 ， $n$之间的距离，枚举每一个点作为B 和 E 相遇的点，求答案。

答案 $= B * disB[i] + E * disE[i] + P * disP[i]$

PS：没必要写三遍最短路的程序，直接函数传数组和起始位置的参数就好。

时间复杂度：$O(3 × dij + N)$

## Code ##

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#define INF 2147483647
using namespace std;

const int L = 40005;
struct Node {
	int to , next;
};
Node e[2 * L];
struct Road {
	int num , len;
	Road(int nn , int dd) {
		num = nn , len = dd;
	}
	bool operator < (const Road &a) const {
		return len > a.len;
	}
};
priority_queue<Road>q;
int head[L] , tot = 0;
int B , E , P , n , m , ans = INF;
int disb[L] , dise[L] , disp[L];

void add(int x , int y) {
	tot++;
	e[tot].next = head[x];
	e[tot].to = y;
	head[x] = tot;
}

void dij(int dis[] , int s) {
	for(int i=1; i<=n; i++)
		dis[i] = INF;
	dis[s] = 0;
	q.push(Road(s , dis[s]));
	while(!q.empty()) {
		Road u = q.top();
		q.pop();
		if(u.len != dis[u.num])
			continue;
		for(int i=head[u.num]; i; i=e[i].next) {
			int v = e[i].to;
			if(dis[v] > u.len + 1) {
				dis[v] = u.len + 1;
				q.push(Road(v , dis[v]));
			}
		}
	}
}

int main() {
	scanf("%d%d%d%d%d",&B,&E,&P,&n,&m);
	for(int i=1; i<=m; i++) {
		int x , y;
		scanf("%d%d",&x,&y);
		add(x , y);
		add(y , x);
	}
	dij(disb , 1);
	dij(dise , 2);
	dij(disp , n);
	for(int i=1; i<=n; i++)
		ans = min(ans , B * disb[i] + E * dise[i] + P * disp[i]);
	printf("%d",ans);
	return 0;
}
```


  [1]: http://usaco.org/index.php?page=viewproblem2&cpid=491
  [2]: https://www.luogu.org/problemnew/show/P3110

---

## 作者：yangzechenc (赞：0)

标签dp真的有问题  XD   这是一道图论题=v=

------------

- First，从Bessie所在的1号点bfs，得到disB[i]为1号点到i的距离；
- Secondly，从Elsie所在的2号点bfs，得到disE[i]为2号点到i的距离；
- Finally，从终点所在的N号点bfs，得到disS[i]为终点到i的距离；
- 接着枚举1~n，即枚举Bessie和Elsie在哪个点会和然后一起走。obviously，答案为：ans=min{disB[i]xB+disE[i]xE+disS[i]xP},1<=i<=n
- code XD

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct Lin{
	int nt,v;
};
Lin e[80010];
int list[40010],l;
inline void add(int u,int v){
	l++;
	e[l].v=v; e[l].nt=list[u]; list[u]=l;
	return;
}
queue<int>q;
bool vis[40010];
int de[40010],db[40010],ds[40010];
int b,E,p,n,m;
void bfs(int s,int *d){
	memset(vis,0,sizeof(vis));
	int f;	vis[s]=1;	d[s]=0;
	q.push(s);
	while (!q.empty()){
		f=q.front();
		q.pop();
		for (int i=list[f];i;i=e[i].nt){
			int v=e[i].v;
			if (!vis[v]){
				d[v]=d[f]+1;
				q.push(v);
				vis[v]=1;
			}
		}
	}
	return;
}
int main(){
	scanf("%d%d%d%d%d",&b,&E,&p,&n,&m);
	int u,v;
	for (int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);	add(v,u);
	}
	bfs(1,db);	bfs(2,de);	bfs(n,ds);
	int ans=(1e9+7);
	for (int i=1;i<=n;i++){
		ans=min(ans,db[i]*b+de[i]*E+ds[i]*p);
	}
	cout<<ans<<endl;
	return 0;
		
}
```

---

## 作者：封禁用户 (赞：0)

题目大意：给定一张无向图，第一个人从点1出发每走一条边消耗A，第二个人从点2出发每走一条边消耗B，两个人相遇后一起走每走一条边消耗C，两个人到达点n的最小花销

分别从点1、点2、点n出发BFS一遍，预处理出每个点到点1、点2、点n的最短路

然后枚举两人相遇的点，计算消耗之和即可

```cpp
#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define M 40400  
using namespace std;  
struct abcd{  
    int to,next;  
}table[M<<1];  
int head[M],tot;  
int n,m,A,B,C;  
long long ans=2147483647;  
int f[M],g[M],t[M];  
int q[M],r,h;  
bool v[M];  
void Add(int x,int y)  
{  
    table[++tot].to=y;  
    table[tot].next=head[x];  
    head[x]=tot;  
}  
void BFS(int f[])  
{  
    int i;  
    while(r!=h)  
    {  
        int x=q[++h];  
        for(i=head[x];i;i=table[i].next)  
            if(!v[table[i].to])  
            {  
                v[table[i].to]=true;  
                q[++r]=table[i].to;  
                f[table[i].to]=f[x]+1;  
            }  
    }  
}  
int main()  
{  
    int i,x,y;  
    cin>>A>>B>>C>>n>>m;  
    for(i=1;i<=m;i++)  
    {  
        scanf("%d%d",&x,&y);  
        Add(x,y);Add(y,x);  
    }  
    memset(v,0,sizeof v);r=h=0;v[q[++r]=1]=true;BFS(f);  
    memset(v,0,sizeof v);r=h=0;v[q[++r]=2]=true;BFS(g);  
    memset(v,0,sizeof v);r=h=0;v[q[++r]=n]=true;BFS(t);  
    for(i=1;i<=n;i++)  
        ans=min(ans,(long long)A\*f[i]+B\*g[i]+C\*t[i]);  
    cout<<ans<<endl;  
    return 0;  
}  
'''

---

