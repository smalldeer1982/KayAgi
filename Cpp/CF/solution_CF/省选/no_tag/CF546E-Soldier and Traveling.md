# Soldier and Traveling

## 题目描述

某个国度中有着 $n$ 座城市和 $m$ 条双向道路。$i$ 号城市中有着 $a_i$ 个士兵。现在士兵可以移动，每个士兵可以选择待在原地或者沿着**一条**双向道路走到一个**相邻的**城市。

问：给定数列 $b$，一轮移动后能不能满足对于每个城市 $i$，里边的士兵数是 $b_i$？如果可以，你需要给出士兵的移动方案。

## 说明/提示

Translated by @[Epiphyllumthief ](/user/45212), Updated by @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
4 4
1 2 6 3
3 5 3 1
1 2
2 3
3 4
4 2
```

### 输出

```
YES
1 0 0 0 
2 0 0 0 
0 5 1 0 
0 0 2 1 
```

## 样例 #2

### 输入

```
2 0
1 2
2 1
```

### 输出

```
NO```

# 题解

## 作者：SunnyYuan (赞：5)

本文适合初学者阅读。~~dalao勿喷~~

对于这种类型的题目，又是增加，又是减少的，我们可以使用[网络流](https://baike.baidu.com/item/%E7%BD%91%E7%BB%9C%E6%B5%81%E7%90%86%E8%AE%BA)进行转化。

说句废话：

> ~~网络流这个东西，趣味十足，上可顶替匈牙利算法，下可转化动态规划。它似水一般灵活，总是可以出乎意料地解决问题。~~


而此题要使用到的是[网络最大流](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E6%B5%81%E9%97%AE%E9%A2%98)之[Dinic算法](https://baike.baidu.com/item/Dinic%E7%AE%97%E6%B3%95)。

好了，说回来，看到这种题目，你有什么疑惑？

说说我的吧：

> 1. 信息这么多($a_i$ 和 $b_i$)，怎么保存？
> 
> 2. 这么多的点，无组织，无纪律，怎么办呢？
> 
> 3. 这情况也太多了吧，怎么~~暴搜~~思考呢？
> 
> 4. 即使知道可行，这题的输出怎么办呢？~~真恶心~~

我们从网络最大流的角度一个一个来思考吧！

> **1. 信息这么多，怎么保存？**

我们可以把一个点的信息一分为2，让他们整齐罗列。

![](https://cdn.luogu.com.cn/upload/image_hosting/42xg5yyy.png)

**千万不要误以为 $a_i$ 和 $b_i$ 为节点，图中只是形象化地阐述“把一个点的信息一分为2”**

> **2. 这么多的点，无组织，无纪律，怎么办呢？**

那就找两个领导把他们汇总起来，这两个领导叫做**源点**以及**汇点**。

![](https://cdn.luogu.com.cn/upload/image_hosting/raudy27b.png)

那流量是多少呢？

**看图！**

看左半部分，点 $i$ 的流量为 $a_i$。

同理，右半部分流量为 $b_i$。

~~中间部分暂不考虑~~

![](https://cdn.luogu.com.cn/upload/image_hosting/1wpaxjiy.png)

为什么要这样干呢？

现在假设 $S$ 点有无穷无尽的水资源。

那么可以往每个左边的河道里塞满水，也就是对于左边的点 $i$（图中是靠近红点的四个点）的初始值为 $a_i$。

也就是对应题目中“每个点初始时有 $a_i$ 个人”的条件。

同样的道理，经过中间一番乱七八糟的处理后，从右边流出的水应为 $b_1,b_2,\dots,b_n$，表示最终处理后，对于右边的点 $i$ （图中是靠近绿点的四个点）最终为 $b_i$。

也就是对应题目中“每个点最终有 $b_i$ 个人”的条件。

> **3. 这情况也太多了吧，怎么思考呢？**

也就是考虑中间部分。

首先，有些人可以选择留下。那么对于这些点的水，随它们流，连接 $n$ 条边，流量为 $+\infin$。

![](https://cdn.luogu.com.cn/upload/image_hosting/efft7bzt.png)

当然，如果有边相连，那也随便流，连接 $m$ 条边（与题目中的 $m$ 意义相同），如图（假设有这些边）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vbur743a.png)

于是乎，跑一遍Dinic算法足矣！

> 4. 即使知道可行，这题的输出怎么办呢？~~真恶心~~

~~众所周知~~，Dinic会在找到增广路时，建立反边，以便反悔。

那么这些反边，就是我们利用的对象。

一条边的反边的权值不就是流过该边的流量吗？

![](https://cdn.luogu.com.cn/upload/image_hosting/us0iewzs.png)

把中间部分的每条反边揪出来，在保存到一个数组里即可。

AC Code

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>

const int N = 210, M = 1410, INF = 1e9;

struct Node
{
	int to;
	int next;
	int w;
}e[M];

int head[N], cur[N], idx = 1;

void add(int a, int b, int c)           // 加边
{
	idx++;
	e[idx].to = b;
	e[idx].next = head[a];
	e[idx].w = c;
	head[a] = idx;
	
	idx++;
	e[idx].to = a;
	e[idx].next = head[b];
	e[idx].w = 0;
	head[b] = idx;
}

int n, m;
int a[N];
int b[N];
int S, T;
int sum1, sum2;				// sum1:a sum2:b

int d[N];

bool bfs()
{
	static int q[N];        // 队列
	int hh = 0, tt = 0;
	memset(d, 0, sizeof(d));
	q[0] = S;
	cur[S] = head[S];
	d[S] = 1;
	while (hh <= tt)
	{
		int t = q[hh++];
		for (int i = head[t]; i; i = e[i].next)
		{
			int to = e[i].to;
			if (!d[to] && e[i].w)
			{
				cur[to] = head[to];
				d[to] = d[t] + 1;
				q[++tt] = to;
				if (to == T) return true;
			}
		}
	}
	return false;
}

int dinic(int u, int limit)
{
	if (u == T) return limit;
	int rest = limit;
	for (int i = cur[u]; i && rest; i = e[i].next)
	{
		cur[u] = i;
		int to = e[i].to;
		if (d[to] == d[u] + 1 && e[i].w)
		{
			int k = dinic(to, std::min(rest, e[i].w));
			if (!k) d[to] = 0;
			rest -= k;
			e[i].w -= k;
			e[i ^ 1].w += k;
		}
	}
	return limit - rest;
}

int map[N][N];                  // 记录反边信息，即结果

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++)std::cin >> a[i];
	for (int i = 1; i <= n; i++)std::cin >> b[i];
	sum1 = std::accumulate(a + 1, a + n + 1, 0);    // 求和
	sum2 = std::accumulate(b + 1, b + n + 1, 0);
	if(sum1 != sum2)        //直接排除
	{
		std::cout << "NO" << '\n';
		return 0;
	}
	for (int i = 1; i <= n; i++) add(0, i, a[i]);   // 左
	for (int i = n + 1; i <= n * 2; i++) add(i, n * 2 + 1, b[i - n]);   // 右
	for (int i = 1; i <= n; i++) add(i, i + n, INF);                // 中1
	for (int i = 1; i <= m; i++)        // 中2
	{
		int a, b;
		std::cin >> a >> b;
		add(a, b + n, INF);
		add(b, a + n, INF);
	}
	S = 0, T = n * 2 + 1;
	
	auto query = [&]()					// Dinic 模板
	{
		int maxflow = 0, flow = 0;
		while (bfs())
		{
			while (flow = dinic(S, INF))
			{
				maxflow += flow;
			}
		}
		return maxflow;
	};
	
	if (query() != sum1)                // 直接排除
	{
		std::cout << "NO" << '\n';
		return 0;
	}
	else                                // 扣反边
	{
		std::cout << "YES" << '\n';
		int t = 4 * n + 2;
		for (int i = 1; i <= 2 * m + n; i++)
		{
			map[e[t ^ 1].to][e[t].to - n] += e[t ^ 1].w;                        // 注意要 -n
			t += 2;
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				std::cout << map[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}
	return 0;
}
```

码字不易，点个赞吧！

---

## 作者：pikabi (赞：2)

### 前置芝士：

~~网络瘤~~

### 题意：

将每个城市的军人调动到相邻城市或按兵不动，问能否从初始状态  ( 我们记作 $a$ )  转移到目标状态 ( 记作 $b$ )，并输出调动情况。

看到这种人数转移后一增一减的情况，我们自然而然想到用网络流来解决。从超级源出点 $s$ 向每个节点的入点 $i$ 伸出一条流量为 $a_i$ 的边，每个节点的出点 $i + n $ 像超级源汇点伸出一条流量为 $b_i$ 的边，自己的入点向自己的出点和邻点入点伸出流量为 $inf$ 的边，跑一遍模板就好了。

关于 YES NO 的判定，只需判断源汇点汇入的总量 $ans$ 是否等于总人数就 ok 了。而具体的调动情况则看每一条边的反边的流量（因为正边减少的流量等于反边的流量）。

目前排在最优解 rank 1.

### Code $--->$

```
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#define ll long long
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

struct node{
	int from, to, nxt, flow;
}e[2000005];

int n, m, s, t, head[205], cur[205], dep[205], cnt = 1, ans, res[205][205];

queue <int> que;

inline void add_edge(int from, int to, int flow){
	e[++cnt].nxt = head[from];
	head[from] = cnt;
	e[cnt].from = from;
 	e[cnt].flow = flow;
	e[cnt].to = to;
}

inline void add(int from, int to, int flow){
	add_edge(from, to, flow);
	add_edge(to, from, 0);
}

inline int bfs(){
	memset(dep, 0, sizeof(dep));
	while(!que.empty() ) que.pop();
	dep[s] = 1;
	que.push(s);
	while(!que.empty() ){
		int u = que.front() ;
		que.pop() ;
		for(int i = head[u]; i; i = e[i].nxt ){
			if(!dep[e[i].to ] && e[i].flow ){
				que.push(e[i].to );
				dep[e[i].to ] = dep[u] + 1; 
			}
		}
	} 
	return dep[t] != 0;
}

inline int dfs(int p, int dis){
	if(p == t) return dis;
	int flow = 0;
	for(int &i = cur[p]; i; i = e[i].nxt ){
		if(dep[e[i].to ] == dep[p] + 1 && e[i].flow ){
			int di = dfs(e[i].to , min(dis, e[i].flow ));
			if(di){
				e[i].flow -= di;
				e[i ^ 1].flow += di;
				flow += di;
				dis -= di;
				if(!dis) return flow;
			}
		}
	}
	return flow;
}

inline void dinic(){
	while(bfs()){
		memcpy(cur, head, sizeof(cur));
		ans += dfs(s, inf);
	}
}

int main(){
	n = read(), m = read();
	s = 2 * n + 1;
	t = s + 1;
	int sum1 = 0, sum2 = 0;
	for(int i = 1; i <= n; i++){
		int x = read();
		sum1 += x;
		add(s, i, x);
	}
	for(int i = 1; i <= n; i++){
		int x = read();
		sum2 += x;
		add(i + n, t, x);
	}
	for(int i = 1; i <= m; i++){
		int x = read(), y = read();
		add(x, y + n, inf);
		add(y, x + n, inf);
	}
	for(int i = 1; i <= n; i++){
		add(i, i + n, inf);
	}
	if(sum1 != sum2){
		puts("NO");
		return 0;
	}
	dinic();
	if(ans != sum1){
		puts("NO");
		return 0;
	}
	for(int i = 4 * n + 2 ; i <= cnt; i += 2){
		if(e[i ^ 1].flow ){
			res[e[i].from ][e[i].to - n] = e[i ^ 1].flow ;
		}
	}
	puts("YES");
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
		printf("%d ",res[i][j]);
		puts("");
	}
}

```

完结撒花 ✿✿ヽ(°▽°)ノ✿

---

## 作者：Epiphyllumthief (赞：2)

[蒟蒻宣传一下自己的blog(qwq)](https://www.cnblogs.com/hhh1109/p/9362553.html)

## 题解

题意大概就是给你 $n$ 个城市，$m$ 条边。
然后人只能从走相邻边相连的城市。
现在给你初始城市的每一个人数，再给一组每个城市人数。询问是否可以从当前人数变换到给定人数。如果能，输入“YES”并输出方案，不能则输出“NO”。

网络流就是建图嘛。。。
建好图一般就没有什么难度了qwq（dalao雾怼）
那么怎么建呢？
我们设一个源点和汇点。
然后把一个城市拆成两个点。
入点 $i$ 限度设为 $a_i$ ，出点 $i+n$ 限度设为 $b_{i}$ 。
这样就只要判断汇点的最大流是否与 $b_i$ 相等了。
Ps: 原本的人数和后来方案的人数应该相等，且一定要先判定。

怎么输出方案？
看反悔路径的流量就好了。
有就标记一下并输出。

---

## 代码


```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int N=1001;
struct node{
    int c,to,next;
}e[N<<1];
int num=1,head[N<<3],flag;
int dep[N<<3],n,m,a[N<<3],b[N<<3],sum,tot,s,t;
int map[N][N];
int read(){
    int x=0,w=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*w;
}

void add(int from,int to,int c){
    num++;
    e[num].to=to;
    e[num].c=c;
    e[num].next=head[from];
    head[from]=num;
}

bool bfs(){
    memset(dep,0,sizeof(dep));
    queue<int>q;q.push(s);dep[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            if(!dep[v]&&e[i].c){
                dep[v]=dep[u]+1;q.push(v);
            }
        }
    }
    return dep[t];
}

int dfs(int x,int cap){
    if(x==t)return cap;
    int addx=0;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        if(dep[v]==dep[x]+1&&e[i].c){
            int tmp=dfs(v,min(cap-addx,e[i].c));
            e[i].c-=tmp;e[i^1].c+=tmp;addx+=tmp;
        }
    }
    return addx;
}

int dinic(){
    int ans=0;
    while(bfs())ans+=dfs(s,10000000);
    return ans;
}

int main()
{
    n=read();m=read();s=0,t=n+n+1;
    for(int i=1;i<=n;i++)a[i]=read(),add(s,i,a[i]),add(i,s,0),tot+=a[i];
    for(int i=1;i<=n;i++)b[i]=read(),sum+=b[i],add(i+n,t,b[i]),add(t,i+n,0);
    for(int i=1;i<=n;i++)add(i,i+n,99999999),add(i+n,i,0);
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
    //	if(x<y)swap(x,y);
        add(x,y+n,99999999);add(y+n,x,0);
        add(y,x+n,99999999);add(x+n,y,0);
    }
    //cout<<sum<<' '<<dinic();
    if(tot!=sum){printf("NO");return 0;}
    int ans=dinic();
    if(sum==ans){printf("YES\n");
        for(int i=1;i<=n;i++){
            for(int j=head[i];j;j=e[j].next){
                int v=e[j].to;
                if(v>n)
                map[i][v-n]=e[j^1].c;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
            cout<<map[i][j]<<' ';
            cout<<endl;
        }
    }
    else printf("NO");
    return 0;
}
```


---

## 作者：AIskeleton (赞：1)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16323368.html)

## 题意
> [CF546E Soldier and Traveling](https://codeforces.com/problemset/problem/546/E)

> 有 $n$ 个点，$m$ 条无向边，人只能在有边相连的点之间移动。

> 给定每个点的初始人数 $a_i$ 和目标人数 $b_i$，询问是否可以使每个点的人数变换到目标人数，若可行输出方案。

> $1\le n\le 100,0\le m\le 200,0\le a_i,b_i\le 100$。

## 题解
### 思路
看到一个人匹配一个点，可以想到这是一个二分图。

考虑拆点，每个点分成出入点构造二分图。
### 建图
从源点向每个入点连一条容量为 $a_i$ 的边，再从每个出点向汇点连一条容量为 $b_i$ 的边。

然后对于每个点，从入点向出点连一条容量为 $\infty$ 的边，因为每个点经过的人数无限制。

至于每条边，边的两端点之间连容量为 $\infty$ 的**无向边**。
### 输出
很明显，如果 $\sum_{i=1}^n b_i \ne \sum_{i=1}^n a_i$ 或是没有满流，就是无解的情况。

至于输出方案，就直接遍历每一条边的反向边，记录反向边的流量就是两点间转移的人数。

最后就是要注意，边数 $m$ 可能为 0。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5000,M=2e6,INF=1e9;
int rd(){
	int w=0,v=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')v=-1;c=getchar();}
	while(c>='0'&&c<='9')w=(w<<1)+(w<<3)+(c&15),c=getchar();return w*v;
}void wr(int x){if(x<0)putchar('-'),x=-x;if(x>9)wr(x/10);putchar(x%10+'0');}

int fir[M],cnt=1;
struct E{int v,w,nt;}e[M];
void I(int u,int v,int w){
	e[++cnt]=(E){v,w,fir[u]};fir[u]=cnt;
	e[++cnt]=(E){u,0,fir[v]};fir[v]=cnt;
}

int cur[N],d[N],st,ed;
queue <int>q;
bool bfs(){
	memset(d,0,sizeof(d));
	for(int i=0;i<=ed;i++)	cur[i]=fir[i];
	q.push(st);d[st]=1;
	while(q.size()){
		int u=q.front(),V;q.pop();
		for(int i=fir[u];i;i=e[i].nt)
			if(e[i].w&&!d[V=e[i].v])
				q.push(V),d[V]=d[u]+1;
	}return d[ed];
}int dfs(int u,int fl){
	if(u==ed)return fl;int f,V,s=0;
	for(int i=cur[u];i;i=e[i].nt){
		cur[u]=i;
		if(e[i].w&&d[V=e[i].v]==d[u]+1){
			f=dfs(V,min(fl,e[i].w));
			e[i].w-=f;e[i^1].w+=f;
			s+=f;fl-=f;if(!fl)break;
		}
	}if(!s)d[u]=0;return s;
}int dinic(){int ans=0;while(bfs())ans+=dfs(st,INF);return ans;}

int n,m,a[N],b[N],s1,s2;
int out[N][N];

signed main(){
    // freopen("test.in","r",stdin);freopen("test.out","w",stdout);
	n=rd(),m=rd();
    ed=n*2+1;
    for(int i=1;i<=n;i++)a[i]=rd(),s1+=a[i];
    for(int i=1;i<=n;i++)b[i]=rd(),s2+=b[i];

    for(int i=1;i<=n;i++){
        I(i,i+n,INF);
        I(st,i,a[i]);
        I(i+n,ed,b[i]);
    }for(int i=1,u,v;i<=m;i++){
        u=rd(),v=rd();
        I(u,v+n,INF);I(v,u+n,INF);
    }

    if(dinic()!=s2||s1!=s2)    puts("NO");
    else{
        puts("YES");
        for(int i=1;i<=n;i++)
            for(int j=fir[i];j;j=e[j].nt)
                if(e[j].v>n)
                    out[i][e[j].v-n]=e[j^1].w;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                wr(out[i][j]),putchar(' ');
            }putchar('\n');
        }
    }
}
```

---

## 作者：WuMin4 (赞：0)

## [CF546E Soldier and Traveling](https://codeforces.com/problemset/problem/546/E)

## 题意

给出一个无向图，第 $i$ 个点上有 $a_i$ 个士兵。每个士兵可以移动到跟自己相邻的点上，问是否可以使一些士兵移动后使得第 $i$ 个点上有 $b_i$ 个士兵，并给出方案。

## 思路

根据数据范围~~和标签~~我们可以大致猜到这是一道网络流题目。考虑该怎么建图。

我们可以建立二分图，其中左边部分的点表示原来的士兵，右边部分的点表示移动后的士兵，再建立超级源点和汇点 $S,T$。

显然原来 $i$ 点士兵有 $a_i$ 个，可以贡献 $a_i$ 的容量；移动后 $i$ 点士兵有 $b_i$ 个，需要接受 $b_i$ 的容量。于是我们将 $S$ 与左部的第 $i$ 个点连边，容量为 $a_i$，将右边的点 $i$ 与 $T$ 连边，容量为 $b_i$。

对于每个点的士兵可以停留在原地，也可以移动到相邻的点。于是我们将左部 $i$ 号点与右部 $i$ 号点连边，这条边表示不动的士兵。对于原图上的无向边 $(i,j)$，我们将左部的 $i$ 号点与右部的 $j$ 号点连边，左部的 $j$ 号点与右部的 $i$ 号点连边，表示移动的士兵。因为可以移动任意数量的士兵，所以容量均为无限大。

跑完一遍网络流后，我们判一下 $S\to i$ 与 $j\to T$ 的边是否满流，若满流，则表示所有士兵都顺利转移，否则无解。求方案只需要看图上 $i\to j$ 的每条边减少的流量即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace mf{
	const int N=205,INF=0x3f3f3f3f;
	struct node{
		int x,w,rev;bool is;
	};
	vector<node> t[N];
	int dep[N],gap[N],maxflow;
	int n,m,S,T;
	void add(int x,int y,int w){
		t[x].push_back({y,w,t[y].size(),0});
		t[y].push_back({x,0,t[x].size()-1,1});
	}
	void bfs(){
		memset(gap,0,sizeof(gap));
		memset(dep,-1,sizeof(dep));
		queue<int> q;
		q.push(T),dep[T]=0,gap[dep[T]]++;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(node v:t[u])
				if(!~dep[v.x])
					dep[v.x]=dep[u]+1,gap[dep[v.x]]++,q.push(v.x);
		}
	}
	int dfs(int x,int flow){
		if(x==T) return maxflow+=flow,flow;
		int used=0;
		for(auto&[v,w,rev,is]:t[x]){
			if(w&&dep[v]+1==dep[x]){
				int mn=dfs(v,min(w,flow-used));
				if(mn) w-=mn,t[v][rev].w+=mn,used+=mn;
				if(flow==used) return used;
			}
		}
		gap[dep[x]]--;
		if(!gap[dep[x]]) dep[S]=n+1;
		dep[x]++,gap[dep[x]]++;
		return used;
	}
	int isap(){
		maxflow=0;
		bfs();
		while(dep[S]<n) dfs(S,INF);
		return maxflow;
	}
}
int n,m,ans[105][105];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	int tot1=0,tot2=0;
	mf::n=n*2+2,mf::S=n*2+1,mf::T=n*2+2;
	for(int x,i=1;i<=n;i++)
		cin>>x,mf::add(mf::S,i,x),mf::add(i,i+n,mf::INF),tot1+=x;
	for(int x,i=1;i<=n;i++)
		cin>>x,mf::add(i+n,mf::T,x),tot2+=x;
	for(int x,y,i=1;i<=m;i++){
		cin>>x>>y;
		mf::add(x,y+n,mf::INF);
		mf::add(y,x+n,mf::INF);
	}
	int res=mf::isap();
	if(tot1==tot2&&tot2==res){
		for(int i=1;i<=n;i++){
			for(mf::node v:mf::t[i]){
				if(v.is) continue;
				ans[i][v.x-n]=mf::INF-v.w;
			}
		}
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++,cout<<endl)
			for(int j=1;j<=n;j++)
				cout<<ans[i][j]<<" ";
	}
	else cout<<"NO";
	return 0;
}
```

---

## 作者：__ZTY__ (赞：0)

## 思路

~~看到题目第一眼，给人一种贪心的感觉，如果人少就从相邻城市要，但是注意题目要求，一个人只能移动一次，显然地，假了。~~

于是，就想，人移动，且只能移动一次，这感觉像什么，大声地说出来，没错，流。

人的移动我们就可以看成水在流，自然地，网络流解决。

## 建图

可以把图按照，超级源点与左边城市连，左边城市与能到达的右边城市连，右边城市与超级汇点连的思路。

先从第一部分考虑，思考从一个左边城市能出发多少人，显然地，就是刚开始是城市的人数，故边权为一个城市的初始人数。

再看中间部分，考虑连哪些边，从一个城市出发，人可以到达与其相邻的城市，或者待在本城市，因此，连的边就明确了。

接下来考虑边权是多少，从一个城市出发，最多去一个城市的人不超过这个城市的初始人数，因此可以赋值为大于初始人数的任意值，为了方便，将其设为极大值。

最后，看与汇点之间的边权，我们的目标是什么，是让每个城市中的人最后变为给定人数，那就相当于最后可以从某个城市离开的人为给定人数，边权即为此。

![](https://cdn.luogu.com.cn/upload/image_hosting/4jayd0ch.png)

那么，图就这么建好了，接下来流完就考虑输出。

## 输出

最最先考虑的，是特殊情况，即初始人数和与给定人数和不一样，是肯定不可以的，毕竟没有人会走丢。

那么什么情况下是有解的呢？当最后能过从右边城市走出的人数，也就是最大流等于初始人数和时，皆大欢喜，可以变换。反之，则不行。

题目还要求输出方案数，乍一看很麻烦的，其实仔细一想很简单的，就是中间部分每条边水流的量，那么直接输出反向边流量即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9,inf=(1<<30);
inline int read(){
	char c=getchar();int s=0,f=1;
	while(!isdigit(c)){if(c=='-'){f=-1;}c=getchar();}
	while(isdigit(c)){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Edge{int to,next,w;}edge[20*N];
int cnt=1,head[4*N];
inline void add(int u,int v,int w){
	edge[++cnt]=(Edge){v,head[u],w};
	head[u]=cnt;
}
int dep[4*N];
int n,m,s,t;
inline bool bfs(){
	memset(dep,0,sizeof(dep));
	queue<int>q;q.push(s);
	dep[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to,w=edge[i].w;
			if(w>0&&!dep[v]){
				dep[v]=dep[u]+1;q.push(v);
			}
		}
	} 
	return dep[t]!=0;
}
inline int dfs(int u,int flow){
	if(u==t){return flow;}
	int rest=flow;
	for(int i=head[u];i&&rest;i=edge[i].next){
		int v=edge[i].to,w=edge[i].w;
		if(w>0&&dep[v]==dep[u]+1){
			int tmp=dfs(v,min(w,rest));
			rest-=tmp;
			edge[i].w-=tmp;
			edge[i^1].w+=tmp;
			if(!tmp){dep[v]=0;} 
		}
	}
	return flow-rest;
}
inline int dinic(){
	int ans=0;
	while(bfs()){ans+=dfs(s,inf);}
	return ans;
}
int sch[N][N];
int main(){
	n=read();m=read();s=0;t=2*n+1;
	int sum=0;
	for(int i=1;i<=n;i++){
		int x=read();sum+=x;
		add(s,i,x);add(i,s,0);
	}
	int check=0;
	for(int i=1;i<=n;i++){
		int x=read();check+=x;
		add(i+n,t,x);add(t,i+n,0);
	}
	if(sum!=check){cout<<"NO";return 0;}
	for(int i=1;i<=n;i++){
		add(i,i+n,inf);add(i+n,i,0);
		sch[i][i]=cnt;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v+n,inf);add(v+n,u,0);
		sch[u][v]=cnt;
		add(v,u+n,inf);add(u+n,v,0);
		sch[v][u]=cnt;
	}
	if(dinic()!=sum){
		cout<<"NO";return 0;
	}
	else{
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cout<<(sch[i][j]==0?0:edge[sch[i][j]].w)<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}

```


---

## 作者：Imiya (赞：0)

考虑网络流。每一个城市的人只能去与该城市直接相连的城市，但我们不关心最终城里的人有多少是原来的，所以每一座城市的人口都可以任意流向与其相邻的城，不需要考虑哪些人走哪些人留，可以直接让所有人都离开城市，重新排入城市，每个人可选城市固定。具体实现可以建每个城市的副本，源点向城市 $i$ 连 $a_i$ 流量限制每个城市原本的人口，城市 $i$ 的副本 $i'$ 向汇点连 $b_i$ 流量限制目标的人口。若 $u$ 和 $v$ 之间有边，则 $u$ 的人口可以任意向 $v$ 流，$v$ 的人口也可以任意向 $u$ 流，也就是 $u$ 向 $v'$ 连 $\infty$ 流量，且 $v$ 向 $u'$ 连 $\infty$ 流量。

求出网络最大流 $f$，若 $f=\sum b=\sum a$，则有方案，反之则无方案。

最后还需要输出方案，稍微想一下，发现若 $u$ 向 $v$ 流了 $k$ 人，则边 $u\rarr v'$ 有大小为 $k$ 的流流过，所以直接查这些边的剩余流量情况输出即可。

```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N=110,M=210,V=210,E=710,inf=0x3f3f3f3f;
int n,m,a[N],b[N];
int edge[N][N];
int S,T,head[V],to[E<<1],nex[E<<1],flow[E<<1],cnt;
inline void insert(int u,int v,int f){
    cnt++;
    to[cnt<<1]=v;
    nex[cnt<<1]=head[u];
    head[u]=cnt<<1;
    flow[cnt<<1]=f;
    to[cnt<<1|1]=u;
    nex[cnt<<1|1]=head[v];
    head[v]=cnt<<1|1;
}
void init(){
    cin>>n>>m;
    S=2*n+1,T=2*n+2;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++){
        insert(S,i,a[i]);
        insert(i+n,T,b[i]);
        insert(i,i+n,inf);
        edge[i][i]=cnt;
    }
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        insert(u,v+n,inf);
        edge[u][v]=cnt;
        insert(v,u+n,inf);
        edge[v][u]=cnt;
    }
}
queue<int>q;
bool tag[E<<1];
int dep[V];
bool bfs(){//cout<<1<<endl;
    memset(dep,0,sizeof(dep));
    memset(tag,0,sizeof(tag));
    dep[S]=1;
    q.push(S);
    bool flg=false;
    while(!q.empty()){
        int nd=q.front();
        q.pop();
        if(nd==T)flg=true;
        for(int i=head[nd];i;i=nex[i]){
            if(!dep[to[i]]&&flow[i]){
                dep[to[i]]=dep[nd]+1;
                q.push(to[i]);
            }
        }
    }
    return flg;
}
int dfs(int nd,int mflow){
    if(nd==T)return mflow;
    int sum=0;
    for(int i=head[nd];i;i=nex[i]){
        if(flow[i]&&dep[nd]+1==dep[to[i]]&&!tag[i]){
            int f=dfs(to[i],min(mflow,flow[i]));
            if(!f)tag[i]=true;
            sum+=f;
            flow[i^1]+=f;
            mflow-=f;
            flow[i]-=f;
            if(!mflow)break;
        }
    }
    return sum;
}
int dinic(){
    int sum=0;
    while(bfs())sum+=dfs(S,inf);
    return sum;
}
int main(){
    // freopen("read.in","r",stdin);
    init();
    int sum=0;
    for(int i=1;i<=n;i++)sum+=a[i]-b[i];
    if(sum!=0){cout<<"NO";return 0;}
    int f=dinic();
    // cout<<f<<' ';
    for(int i=1;i<=n;i++)f-=b[i];
    if(f!=0){cout<<"NO";return 0;}
    printf("YES\n");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)cout<<flow[edge[i][j]<<1|1]<<' ';
        cout<<endl;
    }
    return 0;
}
```

---

