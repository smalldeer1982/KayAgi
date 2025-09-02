# [USACO05DEC] Layout G

## 题目描述

正如其他物种一样，奶牛们也喜欢在排队打饭时与它们的朋友挨在一起。FJ 有编号为 $1\dots N$ 的 $N$ 头奶牛 $(2\le N\le 1000)$。开始时，奶牛们按照编号顺序来排队。奶牛们很笨拙，因此可能有多头奶牛在同一位置上。

有些奶牛是好基友，它们希望彼此之间的距离小于等于某个数。有些奶牛是情敌，它们希望彼此之间的距离大于等于某个数。

给出 $M_L$ 对好基友的编号，以及它们希望彼此之间的距离小于等于多少；又给出 $M_D$ 对情敌的编号，以及它们希望彼此之间的距离大于等于多少 $(1\le M_L,$ $M_D\le 10^4)$。

请计算：如果满足上述所有条件，$1$ 号奶牛和 $N$ 号奶牛之间的距离最大为多少。

## 样例 #1

### 输入

```
4 2 1
1 3 10
2 4 20
2 3 3```

### 输出

```
27```

# 题解

## 作者：BinDir0 (赞：53)

## 差分约束模版题

### 不过后三个点简直是满满的恶意qwq

这里不说做题思路（毕竟纯模板），只说几个坑点：

1. 相邻的两头牛间必须建边（这点好像luogu没有体现），例如一组数据：

	4 1 1
    
	1 4 10
    
	2 3 20
    
    output：-1
    
 	若相邻牛未建边，跑出来的结果是10；而事实如图：

![](https://i.loli.net/2019/03/18/5c8f6c092c1de.png)

        存在负权环。
        因此我在代码里写了一条：
```cpp
for(int i=1;i<n;i++)
{
    add(i+1,i,0);
}
```


2. 应跑两遍SPFA，一遍从超级源点0判断有无解，一遍从1计算结果。

	如果不跑0那一遍，则可能判不出题目原图是否联通或有无负权环（毕竟从点1不一定能到达所有点）。
    
    所以要建边qwq
    
```cpp
for(int i=1;i<=n;i++)
{
    add(0,i,0);
}
```
似乎可以了qwq

AC代码：
```cpp
//Author:pawn
#include<bits/stdc++.h>
using namespace std;
int n,ml,md,a,b,c,fst[10100],nex[50010],v[50010],w[50010],cnt,vis[10100],dis[10100],tim[10100];
queue<int> q;
void add(int a,int b,int c)
{
    nex[++cnt]=fst[a];
    fst[a]=cnt;
    v[cnt]=b;
    w[cnt]=c;
    return ;
}
int spfa(int k)
{
    memset(dis,0x7f/3,sizeof(dis));
    memset(vis,0,sizeof(vis));
    memset(tim,0,sizeof(tim));
    q.push(k);
    dis[k]=0;
    vis[k]=1;
    while(!q.empty())
    {
        int u=q.front();
        //cout<<u<<" ";
        q.pop();
        tim[u]++;
        vis[u]=0;
        if(tim[u]>n)
        return -1;
        for(int i=fst[u];i!=-1;i=nex[i])
        {
            if(dis[v[i]]>dis[u]+w[i])
            {
                dis[v[i]]=dis[u]+w[i];
                if(!vis[v[i]])
                {
                    q.push(v[i]);
                    vis[v[i]]=1;
                }
            }
        }
    }
    /*cout<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<dis[i]<<" ";
    }*/
    if(dis[n]>1e8)
    return -2;
    return dis[n];
}
int main()
{
    memset(fst,-1,sizeof(fst));
    cin>>n>>ml>>md;
    for(int i=1;i<=ml;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    for(int i=1;i<=md;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(b,a,-c);
    }
    for(int i=1;i<n;i++)
    {
        add(i+1,i,0);
    }
    for(int i=1;i<=n;i++)
    {
        add(0,i,0);
    }
    int sp=spfa(0); 
    if(sp<=-1)
    {
    	cout<<sp;
    	return 0;
    }
    else
    {
    	cout<<spfa(1);
    }
    //cout<<" "<<sp;
    return 0;
}
/*
5 1 1
1 5 10
2 3 20
*/
//output:-1

```
求过qwq

---

## 作者：ROY1994 (赞：30)

> ~~这是我们学校的小网管上传的题，我居然来写题解了QWQ~~


很显然，这是一道差分约束的裸题，瞎搞一下跑个最短路就可以了，但是~~丧心病狂~~的小网管出了三个~~DB~~数据，你还得去从0开始跑spfa判断图是不是联通的，然后就A了QAQ

##  差分约束
这玩意主要就是给你几个不等式，让你求一个东西的范围，

$x_2-x_1\leq a_1$

$x_3-x_2\leq a_2$

$x_4-x_3\leq a_3$

$x_5-x_4\leq a_4$

比方说我们有以上几个不等式，求 $x_5-x_1$的最大值，直接代入计算就可以，但是要计算机能拿来计算，我们得有一个规矩点的方法

我们可以通过移项，发现 $x_i\leq x_j +a_k$
然后可以~~自然而然~~地想到求最短路时的松弛操作，但是这里符号是反的，这并无大碍，因为我们是求 $x_5-x_1$ 的最大值，就等于 $x_1$ ~ $x_5$ 的最小值（这里请好好理解），如果 $dis[n]$ 是无穷大，就表明 $x_5-x_1$ 可以无穷大，如果出现负环，就表明无解

## code：
方便~~复制~~的代码QWQ

```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define main mian
using namespace std;
const int N=1005;
const int M=40005;
int n,ml,md,a,b,d;
struct EDGE
{
	int nxt,to,wei,;
}edge[M];
int head[N],tot;
inline void add(int x,int y,int v)
{
	edge[++tot].nxt=head[x];
	edge[tot].to=y;
	edge[tot].wei=v;
	head[x]=tot;
}
queue<int> q;
int vis[N],dis[N],circle[N];
void spfa(int s)
{
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(circle,0,sizeof(circle));
	q.push(s);
	vis[s]=1,dis[s]=0;
	while(!q.empty())
	{
		int now=q.front(); q.pop(); vis[now]=0;
		for(int i=head[now];i;i=edge[i].nxt)
		{
			int tt=edge[i].to;
			if(dis[now]+edge[i].wei<dis[tt])
			{
				dis[tt]=dis[now]+edge[i].wei;
				circle[tt]=circle[now]+1;
				if(circle[tt]>=n)
				{
					puts("-1");exit(0);
				}
				if(!vis[tt])
				{
					vis[tt]=1;
					q.push(tt);
				}
			}
		}
	}
	
}
int main()
{
	int n;
	scanf("%d%d%d",&n,&ml,&md);
	for(int i=1;i<=n;i++) add(0,i,0);
	for(int i=1;i<=ml;i++)
	{
		scanf("%d%d%d",a,b,d);
		add(a,b,d);
	}
	for(int i=1;i<=md;i++)
	{
		scanf("%d%d%d",a,b,d);
		add(b,a,-d);
	}
	spfa(0);
	spfa(1);
	if(dis[n]==INF) puts("-2");
	else printf("%d",dis[n]);
	return 0;
}
```



---

## 作者：Eleven谦 (赞：11)

# Layout G
[题目传送门qwq](https://www.luogu.com.cn/problem/P4878)

#### 前言

不得不说，这道题读下来完全就是 **模板题！**（~~当然除最后三个万恶的$hack$数据以外~~）

如果有不了解的差分约束系统的，珂以看[这篇博客](https://www.cnblogs.com/Eleven-Qian-Shan/p/13226903.html)啊

------------
#### 分析

- $N$个点，给出$M_L$组$≤$的关系，$M_D$组$≥$的关系

这....不就是**约束条件**嘛！那最直观的解决方法不就是**差分约束系统**嘛！

- 对于差分约束系统的题，我们还是要先判断是**跑最短路还是最长路**

继续看题，发现要求出从$1$到$N$的**最大**距离

我们知道，**求最大解就是跑最短路，求最小解就是跑最长路**（不知道的还是上面那篇博客qwq）

初步思路已经出来了：跑最短路的差分约束系统模板

- 我们再来看看输出格式：

1. 如果从$1$到$N$没有合法方案，则输出“$-1$”

2. 如果从$1$到$N$的距离为无限大，则输出“$-2$”

3. 否则输出从$1$到$N$的最大距离

如果不好理解，可以转换成如下：

1. 如果从$1$到$N$**存在环**，则是“$-1$”

2. 如果$1$**无法到达**$N$，则是“$-2$”

3. 否则输出从$1$到$N$的最大距离

- 好了，来看看上面思路编出来的代码（别急着说为什么A不了，因为还有$hack$在）

PS：这里和下面的代码皆使用 **$deque$（双端队列）**，这是 **$SPFA$的一种叫做$SLF$的优化**

```cpp
#include <bits/stdc++.h>
using namespace std;
deque<int> q;
int n,ml,md,u,v,w,flag;
int tot,dis[520010],vis[520010],cnt[520010],head[520010];

struct node {
	int to,net,val;
} e[520010];

inline void add(int u,int v,int w) {
	e[++tot].to=v;
	e[tot].val=w;
	e[tot].net=head[u];
	head[u]=tot;
}

inline void spfa() {
	for(register int i=1;i<=n;i++) {
		vis[i]=0;
		dis[i]=2005020600;
	}
	dis[1]=0;
	vis[1]=1;
	cnt[1]=1;
	q.push_back(1);
	while(!q.empty()) {
		int x=q.front();
		q.pop_front();
		vis[x]=0;
		for(register int i=head[x];i;i=e[i].net) {
			int v=e[i].to;
			if(dis[v]>dis[x]+e[i].val) {
				dis[v]=dis[x]+e[i].val;
				if(cnt[v]==n) {
					flag=1;
					return ;
				}
				if(!vis[v]) {
					vis[v]=1;
					cnt[v]++;
					if(!q.empty()&&dis[q.front()]<dis[v]) q.push_back(v);
					else q.push_front(v);
				}
			}
		}
	}
}

int main() {
	scanf("%d%d%d",&n,&ml,&md);
	for(register int i=1;i<=ml;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	for(register int i=1;i<=md;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(v,u,-w);
	}
	spfa();
	if(flag==1) puts("-1");
	else {
		if(dis[n]==2005020600) puts("-2");
		else printf("%d",dis[n]);
	}
	return 0;
}
```

------------
#### 优化

我们发现，最后三组$hack$数据过不了（~~可恶啊~~）

- 为什么？

因为题目给出的数据**并不保证图的连通性！**

- 什么意思？

$1$有可能是“孤儿点”啊！那**图就不连通**了，结果就是上面的程序WA掉了

- 怎么优化？

我们就先特别跑一遍，判断图是否连通，如果连通就继续进行上面的操作；如果不连通就直接输出“$-1$”即可

- 特别处理

这里我们引入“**超级源点**”来帮助我们**判断图的连通性**

即：**建立一个点$0$，然后与$1$到$N$的每个点都连一条边权为$0$的边**，这样我们就可以通过跑一遍额外的$SPFA$来判断图的连通性了（这也算作差分约束系统的一种基础操作吧）

- 最后给出$100pts$的$Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
deque<int> q;
int n,ml,md,u,v,w,flag;
int tot,dis[520010],vis[520010],cnt[520010],head[520010];

struct node {
	int to,net,val;
} e[520010];

inline void add(int u,int v,int w) {
	e[++tot].to=v;
	e[tot].val=w;
	e[tot].net=head[u];
	head[u]=tot;
}

inline void spfa(int s) {
	for(register int i=1;i<=n;i++) {
		vis[i]=0;
		dis[i]=2005020600;
	}
	dis[s]=0;
	vis[s]=1;
	cnt[s]=1;
	q.push_back(s);
	while(!q.empty()) {
		int x=q.front();
		q.pop_front();
		vis[x]=0;
		for(register int i=head[x];i;i=e[i].net) {
			int v=e[i].to;
			if(dis[v]>dis[x]+e[i].val) {
				dis[v]=dis[x]+e[i].val;
				if(cnt[v]==n) {
					flag=1;
					return ;
				}
				if(!vis[v]) {
					vis[v]=1;
					cnt[v]++;
					if(!q.empty()&&dis[q.front()]<dis[v]) q.push_back(v);
					else q.push_front(v);
				}
			}
		}
	}
}

int main() {
	scanf("%d%d%d",&n,&ml,&md);
	for(register int i=1;i<=n;i++) add(0,i,0);
	for(register int i=1;i<=ml;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	for(register int i=1;i<=md;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(v,u,-w);
	}
	spfa(0);
	if(flag==1) {
		puts("-1");
		return 0;
	}
	spfa(1);
	if(flag==1) puts("-1");
	else {
		if(dis[n]==2005020600) puts("-2");
		else printf("%d",dis[n]);
	}
	return 0;
}
```


------------

最后，如果这篇题解有任何错误或您有任何不懂的，欢迎留言区评论啊，我会及时改正和回复，谢谢各位dalao啊qwq

------------



---

## 作者：清远学会 (赞：4)

**一道差分约束的吼题**

对于此题，状态无非两种：**基友与敌人**

那么，**就有$u-v \le c$ 或者 $u - v \ge c$**

对于$u-v \le c$，**可以用求最短路中**的$dis[v] = dis[u] + e[i].dis$

我们对$u - v \ge c$ 转换成 $v-u \le -c$

这样，我们就可以**很愉快的跑路**啦

那么建图就酱：

```cpp
for(int i = 1;i <= ml;i ++) {
	int u = read(),v = read(),w = read();
	cp(u,v,w); 
}
for(int i = 1;i <= md;i ++) {
	int u = read(),v = read(),w = read();
	cp(v,u,-w);
}
```
但是，求解过程中会有三种情况：

1.如果**没有合法方案**，输出 -1

2.如果**有合法方案**，但 1 号奶牛可以与 N 号奶牛**相距无穷远**，输出 -2. 

3.否则，**输出 1 号奶牛与 N 号奶牛间的最大距离**

对于第一种情况，在**跑最短路时要判定是否存在负环**，原理不用我解释吧，
但一点要注意，在求解方案中，**判负环的优先级最高**

所以，有时候图并不联通，这时**不要着急输出-2，要先判定负环的有无**

所以我干脆对**每个联通块求一个SPFA，判定负环**，**最后在从1跑到n，求最短路**

完整代码在这里：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#define N 50500
#define INF 999999999
using namespace std;

inline int read() {
	int x = 0,f = 1; char s = getchar();
	while(s < '0' || s > '9') {if(s == '-') f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	return x * f;
}

int n,ml,md;
int head[N],cnt;
struct node {
	int nxt,to,dis;
}e[N];
int dis[N],vis[N],tot[N],tvs[N];

inline void cp(int u,int v,int w) {
	cnt ++;
	e[cnt].to = v;
	e[cnt].dis = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

queue<int> q;
inline bool SPFA(int s) {
	for(int i = 1;i <= n;i ++) dis[i] = INF,tot[i] = 0;
	q.push(s); dis[s] = 0; 
	vis[s] = tot[s] = tvs[s] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		if(tot[u] >= n) return true; tot[u] ++;
		for(int i = head[u];i;i = e[i].nxt) {
			int v = e[i].to; tvs[v] = 1;
			if(dis[v] > dis[u] + e[i].dis) {
				dis[v] = dis[u] + e[i].dis;
				if(!vis[v]) vis[v] = 1,q.push(v); 
			}
		}
	}
	return false;
}

int main() {
	n = read(),ml = read(),md = read();
	for(int i = 1;i <= ml;i ++) {
		int u = read(),v = read(),w = read();
		cp(u,v,w); 
	}
	for(int i = 1;i <= md;i ++) {
		int u = read(),v = read(),w = read();
		cp(v,u,-w);
	}
	for(int i = 1;i <= n;i ++) 
		if(!tvs[i]) 
			if(SPFA(i)) {
				printf("-1\n");
				return 0;
			}
	SPFA(1);	
	printf("%d\n",dis[n] == INF ? -2 : dis[n]);
    	//对于dis[n]仍未更新，则图不连通，为情况2
	return 0;
}
```

---

## 作者：Awdrgysxc (赞：3)

关于为什么要从0先跑最短路（其他题解写的好像不是很清楚~~也许是我语文太差~~）

## 【分析】

不难看出这是一道差分的题目

建边就不说了(注意别漏了）

## 【Code】
```cpp
	n = read(),m = read(),k = read();
    For(i,1,m)
    {
        int x,y,z;
        x = read(),y = read(),z = read();
        Add_edge(x,y,z);
    }
    For(i,1,k)
    {
        int x,y,z;
        x = read(),y = read(),z = read();
        Add_edge(y,x,-z);
    }
    For(i,1,n - 1)
    {
        Add_edge(i + 1,i,0);
    }
```
这样的话就有80分了

那另外2的点为什么会WA呢,见下图

![](https://cdn.luogu.com.cn/upload/pic/46928.png)

即

5 0 4

5 2 1

4 5 1

4 3 1

3 2 1

Ans = -1

~~如果按照题意，这数据并不存在，因为B>=A~~

如果从一开始的话就会被认为是-2，但其实是无解的（存在负环）

我们可以从每个点进行SPFA,找到负环，printf("-1");exit(0);

我们可以在建一个点，比如：0（任意一个不在图中的点），往每一个点建一条0的边，再从0 SPFA，这样就实现了每个点SPFA

![](https://cdn.luogu.com.cn/upload/pic/46936.png)

## 【Code】
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
#define max(x,y)(x>y?x:y)
#define re register
#define min(x,y)(x<y?x:y)
#define For(a,b,c) for(register int a = b;a <= c; a++)
#define IL inline 

using namespace std;

typedef long long LL;
IL int read() {
    re int ret=0;re bool flag=0;re char c=getchar();
    while((c<'0')|(c>'9'))flag^=!(c^'-'),c=getchar();
    while((c>='0')&(c<='9'))ret=(ret<<3)+(ret<<1)+(c^'0'),c=getchar();
    return flag?-ret:ret;
}

IL void Put(char * s) { puts(s); }
IL void Put(char c) { Put(&c); }
IL void Put(LL x) { char c[55]={0}; sprintf(c,"%lld",x); Put(c); }
IL void Put(int x) { Put(x|0LL); }

const int M = 1e7 + 10;
const int INF = 0xffff;

queue <int> Q;

int Dis[M],Gis[M],Nxt[M],Fir[M],go[M],val[M],n,Tot,m,k,Min;
bool vis[M];

inline void Add_edge(int x,int y,int z)
{
    Nxt[++Tot] = Fir[x],go[Tot] = y,val[Tot] = z,Fir[x] = Tot;
}

inline void SPFA(int x)
{
    Q.push(x),Gis[x] = 1,Dis[x] = 0;
    while(!Q.empty())
    {
        int Now = Q.front();Q.pop();
        vis[Now] = 0;
        for(re int i = Fir[Now];i;i = Nxt[i])
        {
            int Go = go[i];
            int Val = val[i];
            if(Dis[Go] > Dis[Now] + Val)
            {
                Dis[Go] = Dis[Now] + Val;
                if(!vis[Go])
                {
                    if(++Gis[Go] >= n + 1)
                    {
                        Put(-1);
                        exit(0);
                    }
                    Q.push(Go);
                    vis[Go] = 1;
                }
            }
        }
    }
}

inline bool check()
{
    int Max = Dis[1];
    For(i,2,n)
    {
        if(Dis[i] < Max) return 1;
        Max = max(Max,Dis[i]);
    }
    return 0;
}

inline void init()
{
    n = read(),m = read(),k = read();
    For(i,1,m)
    {
        int x,y,z;
        x = read(),y = read(),z = read();
        Add_edge(x,y,z);
    }
    For(i,1,k)
    {
        int x,y,z;
        x = read(),y = read(),z = read();
        Add_edge(y,x,-z);
    }
    
    For(i,1,n) Add_edge(i + 1,i,0);
    
    For(i,1,n)
    {
        Add_edge(0,i,0);
    }
}

inline void solve()
{
    memset(Dis,127/3,sizeof(Dis));
    int p = Dis[n];
    
    SPFA(0);//每个点进行SPFA
    
    memset(Dis,127/3,sizeof(Dis));
    memset(vis,0,sizeof(vis));
    
    SPFA(1);
    if(Dis[n] == p) Put(-2);
    else Put(Dis[n]);
}

int main(void)
{
    init();
    solve();
    return 0;
}

```

---

## 作者：CreeperLordVader (赞：2)

## 其实，没有HACK数据我们也应该想到图不连通的情况，关于差分约束可以看看楼下题解
# 这里提供一种DFS判负环的方法，顺带提一下本题的一点注意事项
##### 对每个点，记一个VIS，在DFS进入该点时VIS=1，正常回溯时VIS=0，表示该点在此次DFS中被访问，返回0
### 遍历所有出边，并更新最短路，如果该点有VIS标记，说明DFS了一圈又回到了它，只能是因为有负环，返回1
#### 举个栗子
 我们要找小明的祖先，于是找小明的爸爸，再找小明的爷爷。。。结果找了一圈回来突然找到了小明（~~乱伦了~~）说明有问题（~~小明是自己的祖先~~）
这个例子不严谨，但类比在判负环的情况中很浅显易懂
当然，图中可能有多个联通块，因此，对每个点记一个USE，在DFS时把USE记为1，循环每个点取USE=0的点开始DFS
# 最后，强调一个问题
## 每头奶牛开始时都是有序排列的，这说明d[x]-d[x-1]>=0，加这一个就够了

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=10005;
vector<int>v[1005];
vector<int>e[1005];
int n,ml,md,d[1005];
bool ok;
int vis[1005],use[1005];
void read(int& x)
{
    char c=getchar();
    x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
}
bool dfs(int x)//这是重点
{
    vis[x]=1;
    use[x]=1;
    for(unsigned int i=0;i<v[x].size();i++)
    {
        int y=v[x][i];
        int z=e[x][i];
        if(d[y]>d[x]+z)
        {
            if(vis[y])return 1;//在此次DFS中找到了一个访问过的点，是负环
            d[y]=d[x]+z;
            if(dfs(y))return 1;//如果继续访问时发现了负环
        }
    }
    vis[x]=0;//清标记
    return 0;
}
int main()
{
//	freopen("layout.4.in","r",stdin);
    read(n);
    read(ml);
    read(md);
    for(int i=1;i<=ml;i++)
    {
        int x,y,z;
        read(x);
        read(y);
        read(z);
        v[x].push_back(y);
        e[x].push_back(z);
    }
    for(int i=1;i<=md;i++)
    {
        int x,y,z;
        read(x);
        read(y);
        read(z);
        v[y].push_back(x);
        e[y].push_back(-z);
    }
    for(int i=2;i<=n;i++)
    {
    	v[i].push_back(i-1);
    	e[i].push_back(0);
	}
    memset(d,0x3f3f3f3f,sizeof(d));
    for(int i=1;i<=n;i++)
    {
        if(!use[i])
        {
            use[i]=1;
            d[i]=0;
            memset(vis,0,sizeof(vis));
            if(dfs(i))
            {
                printf("-1\n");
                return 0;
            }
            if(d[n]==0x3f3f3f3f)ok=1;
        }
    }
    if(!ok)printf("%d\n",d[n]);
    else printf("-2\n");
}
```

---

## 作者：旗木五五开 (赞：2)

## 一道裸的差分约束题目
~~（本蒟蒻一开始居然没想到用差分，直到后来听取WA声一片。。。QwQ）~~

------------

## 什么是差分约束
  - 给定n个变量和m个不等式，每个不等式的形式为 **a[i] - a[j] <= dis **  (0 <= i, j < n, 0 <= k < m，dis已知) ，求 a[i] - a[j] 的最大值或最小值。
 
  - 对于每个不等式：a[i] - a[j] <= dis 或 a[i] - a[j] >= dis；建立**点 j 到点 i **的有向边，边权为dis。
 
  - 求 a[i] - a[j] 的**最大值**，就是求 j 到 i 的**最短路**。(a[i] - a[j] <= dis)。
  
  求 a[i] - a[j] 的**最小值**，就是求 j 到 i 的**最长路**。(a[i] - a[j] >= dis)
 
  - 若所建立的有向图有**负环**则这些不等式**无解**。

~~（由此可见这是一个灰常灰常毒瘤的算法QwQ）~~

##  


 ##  

** 所以说，这题 ~~显而易见~~ 是差分惹~**

  
## 另外还有几点要注意哒：
 
  - 可能有负边权，因此可以把最短路确定为**SPFA**。
  
  - 题目中有些条件是 a[j] - a[i] >= dis , 还需要乘一个 −1 ，把它变成 a[j] - a[i] <= −dis 就可以啦。
  
  - 图可能不连通，因此要从0开始向每个点建一条权值为0的边，然后还要以0为顶点跑一遍SPFA，最后才能以1为顶点跑最短路求解。
  
  ~~（当初没想到这点，结果那三组hack数据怼到肝疼QwQ）~~



## code：
```cpp
#include <bits /stdc++.h>
#define N 1000005
#define inf 0x3f3f3f3
using namespace std;

inline void r(int &a) {
	char c;
	a=0;
	while((c=getchar())<48);
	while(c>47) a=a*10+c-'0',c=getchar();
}

inline void wr(int x) {
	if(x<0) x=-x,putchar (45);
	if(x<10) {putchar (x+48);return;}
	wr(x/10);
	putchar (x%10+48);
}

struct edge {
	int nt,to,w;
} e[2*N];

int n,ml,md,t;
int head[2*N],vis[2*N],dis[2*N],use[2*N];

queue<int> q;

inline void add(int x,int y,int v) {
	e[++t].nt=head[x];
	e[t].to=y;
	e[t].w=v;
	head[x]=t;
}

viod SPFA(int s) {
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(use,0,sizeof(use));
	q.push(s);
	vis[s]=1,dis[s]=0;
	while(!q.empty()) {
		int u=q.front();
		q.pop(),vis[u]=0;
		for(int i=head[u]; i; i=e[i].nt) {
			int z=e[i].to,v=e[i].w;
			if(dis[u]+v<dis[z]) {
				dis[z]=dis[u]+v,use[z]=use[u]+1;
				if(use[z]>=n) puts("-1"),exit(0);
				if(!vis[z]) vis[z]=1,q.push(z);
			}
		}
	}
}

int main() {
	r(n),r(ml),r(md);
	for(int i=1; i<=n; i++) add(0,i,0);
	int a,b,d;
	for(int i=1; i<=ml; i++) 
		r(a),r(b),r(d),add(a,b,d);
	for(int i=1; i<=md; i++)
		r(a),r(b),r(d),add(b,a,-d);
	SPFA(0),SPFA(1);
	if(dis[n]==inf) puts("-2");
	else wr(dis[n]);
	return 0;
}

```
 
 

---

## 作者：Refined_heart (赞：1)

看到不等式就能想到差分约束。

对于这样的题，我们有：

当$X_i-X_j<=C$时，我们可以把它看成$X_i<=C+X_j$，我们可以从$j$向$i$连一条长度为$C$的边。

当$X_i-X_j>=C$时，我们两边乘以$-1$得：

$X_j-X_i<=-C$，从$i$向$j$连一条长度为$-C$的边即可。

然后跑一遍最短路即可。

这道题我们发现两个不一样的地方：两个无解情况。

对于无解情况，我们知道，如果这个图有负环，则说明这个差分约束系统无解。

用$Spfa$即可。

那么对于不连通情况呢？

我们可以用建立超级源点的思路，建一个点$0$，使得它与所有点都相连，且边权为$0$.然后从$0$开始跑最短路即可。

对于负环和无解情况，都可以用这一步判出来。

那么，如果有解，再从$1$跑一遍记录答案就好了。

~~这道紫题其实没那么难，不是吗？（逃）~~

$Code:$

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=500000;
#define inf 0x7f/3
int head[MAXN],dis[MAXN],vis[MAXN];
int tot,n,m,cnt[MAXN],d;
queue<int>q;
struct edge{
	int nxt,to,dis;
}e[MAXN];
inline void add(int x,int y,int w){
	e[++tot].nxt=head[x];
	e[tot].to=y;
	e[tot].dis=w;
	head[x]=tot;
}
bool Spfa(int s){
	memset(dis,inf,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(cnt,0,sizeof(cnt));
	dis[s]=0;vis[s]=1;q.push(s);
	while(!q.empty()){
		int k=q.front();
		q.pop();vis[k]=0;
		cnt[k]++;
		if(cnt[k]>n){
			printf("-1\n");
			return 0;
		}
		for(int i=head[k];i;i=e[i].nxt){
			int j=e[i].to;
			if(dis[j]>dis[k]+e[i].dis){
				dis[j]=dis[k]+e[i].dis;
				if(!vis[j])vis[j]=1,q.push(j);
			}
		}
	}
	return 1;
}int main(){
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=m;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
	}
	for(int i=1;i<=d;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(b,a,-c);
	}
	for(int i=1;i<=n;++i)add(0,i,0);
	for(int i=1;i<=n;++i)add(i+1,i,0);
	int K=Spfa(0);
	if(!K)return 0;
	if(dis[n]>1e8){
		printf("-2\n");
		return 0;
	}
	int C=Spfa(1);
	if(!K||!C)return 0;
	else if(dis[n]>1e8)printf("-2\n");
	else printf("%d\n",dis[n]);
	return 0;
}
```
$(PS:$对于最后为什么是$dis[n]>1e8$我也不太清楚，当时我没有这样写$WA$ $on$第六个点,是判不连通的时候错了。如果有大佬知道是为什么，请私信，我会修改，不胜感激。

---

## 作者：King丨帝御威 (赞：1)

做这道题之前，大家应该先学习一下差分约束。

给大家推荐个博客：[不是我的……](http://www.cnblogs.com/void/archive/2011/08/26/2153928.html)

然后回到这个题目上来，首先这道题有负环的出现，那显然不能用$dijkstra$了，那就把解法锁定为$spfa$。

对于给出的前$M_L$种关系：

就是这个样子：$d[B]-d[A] \leq D$

后$M_D$种关系是：$d[B]-d[A] \geq D$,即$d[A]-d[B] \leq -D$

那对于第一种关系，根据差分约束，我们需要建从$A$到$B$，边权为D的边，对于第二种关系，我们就需要建从$B$到$A$，边权为$-D$的边。

这样建完图跑直接调用$spfa(1)$就可以得$70$分了，那为什么不能$AC$
呢？

因为我们差分约束时的起点是$0$，所以我们要先跑一遍$spfa(0)$,并建一条从0到$i(1 \leq i \leq n)$的边权为0的边，为什么呢？

难道不应该是$d[0]-d[i] \leq 0$么？这样不是应该从i到0的边么？但是，有没有想过，如果你这样建，那你以0为起点跑spfa有意义么？0没法到达任何一个点，所以，我们需要建一条从0到i的边的边权为0的边。这样这题就能AC啦！


下面是我~~丑陋(学长说的)~~的代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<queue>
#define maxn 1007
using namespace std;
int num,n,m,p,head[maxn],dis[maxn],vis[maxn],in[maxn];
inline int qread() {
  char c=getchar();int num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
struct node {
  int v,w,nxt;
}e[20007];
inline void ct(int u, int v, int w) {
  e[++num].v=v;
  e[num].w=w;
  e[num].nxt=head[u];
  head[u]=num;
}
const int inf=0x3f3f3f3f;
inline void spfa(int s) {
  memset(dis,0x3f,sizeof(dis));
  memset(vis,0,sizeof(vis));
  memset(in,0,sizeof(in));
  queue<int>q;
  q.push(s),vis[s]=1,in[s]=1;
  dis[s]=0;
  while(!q.empty()) {
    int u=q.front();
    q.pop();vis[u]=0;
    for(int i=head[u];i;i=e[i].nxt) {
      int v=e[i].v;
      if(dis[v]>dis[u]+e[i].w) {
        dis[v]=dis[u]+e[i].w;
        if(!vis[v]) {
          vis[v]=1;
          in[v]++;
          if(in[v]>n) {
            printf("-1\n");
            exit(0);
          }
          q.push(v);
        }
      }
    }
  }
}
int main() {
  n=qread(),m=qread(),p=qread();
  for(int i=1,u,v,d;i<=m;++i) {
    u=qread(),v=qread(),d=qread();
    ct(u,v,d);
  }
  for(int i=1,u,v,d;i<=p;++i) {
    u=qread(),v=qread(),d=qread();
    ct(v,u,-d);
  }
  for(int i=1;i<=n;++i) ct(0,i,0);
  spfa(0);
  spfa(1);
  if(dis[n]==inf) {
    printf("-2\n");
    return 0;
  }
  printf("%d\n",dis[n]);
  return 0;
}
```

---

## 作者：kodiak (赞：1)

### 差分约束的题
用前向星把差分约束的图做出来,然后跑spfa

注意这个地方因为要考虑没有方案的情况，也就是输出-1的情况，需要从0开始预跑spfa，判断线路有没有断了的地方，然后再从1开始跑

~~上代码QωQ~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ml,md;
struct edge
{
	int v,to,nxt;
}e[4010];
int head[1010],ei=0;
int dis[1010];
inline void add(int x,int y,int v)
{
	ei++;
	e[ei].to=y;
	e[ei].nxt=head[x];
	e[ei].v=v;
	head[x]=ei;
}
int vis[1010];
int tag[1010];
void spfa(int s)
{
	int i;
	queue<int>qu;
	qu.push(s);
	vis[s]=1;
	dis[s]=0;
	while(!qu.empty())
	{
		int x=qu.front();
		vis[x]=0;
		qu.pop();
		if(tag[x]>=2*n)		
		{
			cout<<"-1";
			exit(0);
		}
		for(i=head[x];i!=0;i=e[i].nxt)
		{
			int y=e[i].to;
			if(dis[y]>dis[x]+e[i].v)
			{
				dis[y]=dis[x]+e[i].v;
				tag[y]=tag[x]+1;
				if(vis[y]==0)
				{
					qu.push(y);
					vis[y]++;
				}
			}
		}
	}
}
int main()
{
	int i,j;
	cin>>n>>ml>>md;
	memset(dis,0x3f,sizeof(dis));
	for(i=1;i<=ml;i++)
	{
		int x,y,l;
		scanf("%d%d%d",&x,&y,&l);
		if(x>y)
		{
			swap(x,y);
		}
		add(x,y,l);
	}
	for(i=1;i<=md;i++)
	{
		int x,y,l;
		scanf("%d%d%d",&x,&y,&l);
		if(x>y)
		{
			swap(x,y);
		}
		add(y,x,-l);
	}
	for(i=0;i<n;i++)
	{
		add(0,i,0);
	}
	spfa(0);			
	memset(dis,0x3f,sizeof(dis));
	memset(tag,0,sizeof(dis));
	spfa(1);
	if(dis[n]==0x3f3f3f3f)
	{
		cout<<"-2";
		return 0;
	}
	cout<<dis[n];
}
```

---

## 作者：thhhty (赞：1)

做法：差分约束~（第一次A差分约束的题，有点小开心~）

我们根据题意不难得到点与点之间的不等式：

x[j]-x[i]<=0 (按编号排序)

x[j]-x[i]<=c1[i] (m1组点距离小于某数)

x[j]-x[i]>=c2[i] (m2组点距离大于某数)

(即x[i]-x[j]<=-c1[i],我们保证统一左边小于右边~)

我们最终的结果就是找到x[1]-x[n]<=T中，T的最小值

因为不等式左右的>或者<统一，所以不等式之间可以相加，
比如：x1-x2<=5；x2-x3<=3,那么也可以得到x1-x3<=8

我们把xi-xj<=c看成一条从i连向j的权值为c的边的话，
就相当于x->y要c1,y->z要c2,x->z就可以花费c1+c2来连接（就类似于最短路的松弛啦）

于是---我们根据题目建好边，跑一次SPFA就可以啦~

PS：有几个需要注意的地方：
1、当存在负权环时，我们不存在最短路，于是输出-1，1->n不存在最优关系（另外从原点出发不会经过的负权环虽然不会影响我们求出最短路，但是因为我们弄不出一个整体合法的方案，所以虽然求出最短路但是也是要报-1的！--因为这个想了好久）

2、当1联系不上n,那么就代表n不受1约束了。他（和他的小伙伴）爱是多少是多少，我们就输出-2

代码：（spfa这里可以倒着找，for(int i=n;i>=1;i--),每次初始化，会更方便一点）

~~（AND虽然上面说的是xi-xj<=c看成i->j的边，但是代码里打的是j->i的边。。。）~~
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int n,m1,m2,d[2100];//d[i]=T:   f(i)-f(1)<=T,
struct node
{
	int x,y,c,next;
}a[41000];int len,last[2100];//有向边a,x->y :f(y)-f(x)<=c
//
void ins(int x,int y,int c)
{
	int now=++len;
	a[now].x=x;a[now].y=y;a[now].c=c;
	a[now].next=last[x];last[x]=len;
}
int list[2100],head,tail;bool v[2100];
int jl[2100];
void spfa(int st)
{
	
	memset(v,true,sizeof(v));v[st]=false;
	d[st]=0;
	list[1]=st;head=1;tail=2;
	while(head!=tail)
	{
		int x=list[head];
		for(int k=last[x];k;k=a[k].next)
		{
			int y=a[k].y;
			if(d[y]>d[x]+a[k].c)
			{
				d[y]=d[x]+a[k].c;
				if(v[y])
				{
					jl[y]++;
					if(jl[y]==n)//被更新入队了n次，但是我们一般来说最多被n-1个点更新到（不可能自己更新自己吧），于是这就是负环粗线了！
					{
						printf("-1\n");
						exit(0);
					}
					v[y]=false;
					list[tail++]=y;
					if(tail>n)tail-=n;
				}
				
			}
		}
		head++;
		v[x]=true;
		if(head>n)head-=n;
	}
}
int main()
{
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1;i<=n-1;i++)ins(i+1,i,0);//f(i)-f(i+1)<=0
	for(int i=1;i<=m1;i++)//f(y)-f(x)<=c
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);
	}
	for(int i=1;i<=m2;i++)//f(x)-f(y)<=-c
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		ins(y,x,-c);
	}
	memset(d,63,sizeof(d));int pd=d[n];
	spfa(1);
	int ans=d[n];
	memset(jl,0,sizeof(jl));
	for(int i=1;i<=n;i++)
	{
		if(jl[i]==0)spfa(i);//判定源点不经过的负环是否可能出现 
	}
	if(ans==pd)printf("-2\n");//无更新：1和n不连通
	else printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：lzcjoe (赞：0)

### 题面

1512 排队布局

时间限制: 1000 ms 内存限制: 65536 KB

【题目描述】

当排队等候喂食时，奶牛喜欢和它们的朋友站得靠近些。FJ有N头奶牛，编号从1到N，沿一条直线站着等候喂食。奶牛排在队伍中的顺序和它们的编号是相同的。因为奶牛相当苗条，所以可能有两头或者更多奶牛站在同一位置上。即使说，如果我们想象奶牛是站在一条数轴上的话，允许有两头或更多奶牛拥有相同的横坐标。一些奶牛相互间存有好感，它们希望两者之间的距离不超过一个给定的数L。另一方面，一些奶牛相互间非常反感，它们希望两者间的距离不小于一个给定的数D。

给出ML条关于两头奶牛间有好感的描述，再给出MD条关于两头奶牛间存有反感的描述。你的工作是：如果不存在满足要求的方案，输出−1；如果1号奶牛和N号奶牛间的距离可以任意大，输出−2；否则，计算出在满足所有要求的情况下，1号奶牛和N号奶牛间可能的最大距离。

【输入】

第一行三个整数N,ML,MD；接下来ML行，每行三个正整数A,B,D，表示奶牛A和奶牛B至多相隔D的距离；接下来MD行，每行三个正整数A,B,D，表示奶牛A和奶牛B至少相隔D的距离。

【输出】

如果不存在满足要求的方案，输出−1；如果1号奶牛和N号奶牛间的距离可以任意大，输出−2；否则，计算出在满足所有要求的情况下，1号奶牛和N号奶牛间可能的最大距离。

【输入样例】

4 2 1

1 3 10

2 4 20

2 3 3

【输出样例】

27

【提示】

样例说明：

这四头牛分别位于 0,7,10,27。

数据范围:

对于全部数据，2≤N≤1000,1≤ML,MD≤10^4,1≤L,D≤10^6。

### 算法

差分约束系统（最短路 / 最长路）、SPFA判负（正）环

#### 差分约束系统

给定若干个**不等式（约束条件）**，不等式形如 $x_i-x_j<=a$ （其中 $a$ 为常数），要求一组解使得所以不等式成立。

不等式可以变形为 $x_i<=x_j+a$ 这和**单源最短路中的松弛的式子** $dis[edge[j].to]<=dis[i]+edge[j].w$ 非常相似，因此，我们把**每一个变量看作有向图中的一个点，对于约束条件建立有向边，求出此图的单源最短路。**

如果 ${dis[1],dis[2],……,dis[n]}$ 是一组解，则 ${dis[1]+x,dis[2]+x,……,dis[n]+x}$ 也是一组解（作差抵消）。

#### 建图方法

对于普通的差分约束的式子，建图的方法有如下两种

1. 单源最短路建图

**对于** $x_i-x_j<=a$ **从结点j向结点i连一条长度为a的边。** 所求最短路的长度就是原不等式组的一组解。

对于 $x_i-x_j>=a$ 的条件可以转换为 $x_i-x_j<=-a$ 求解。

**建立超级源点0号点**，从0号点向每一个点连接一条长度为0的有向边。这样可以保证图的联通性，也不会增加最短路的长度，**可以找出最小的正整数解**。

如果把0号点向每一个点连接的有向边的长度**调整为a**，则可以是解**都大于a**。

2. 单源最长路建图

**对于** $x_i-x_j>=a$ **从结点j向结点i连一条长度为a的边。** 所求**最长路**的长度就是原不等式组的一组解。

在求最长路的时候，要将dis数组初始化为-inf，求解时的松弛式子要变为 $dis[edge[j].to]>=dis[i]+edge[j].w$ 。

#### 解的判断

要判断差分约束系统是否有解，需要判断图中是否有正（负）环（其实就是判断图是否有最短路 / 最长路）。

#### 判断方法

1. 在SPFA迭代时，记录点入队的次数，若次数大于点数，则存在负环。

2. 在SPFA迭代时，记录每个点最短路经过的点的数目，若大于总点数，则存在负环。

正环（最长路）的判断方法也是相似的。

#### 本题中的差分约束条件

本题中牛的距离要求就是差分约束条件。

注意：本题中对牛的距离的要求有两种，不等式符号相反，需要将式子变形后使符号方向一致才能进行差分约束算法。

本题也要判断1号点与n号点的联通性，需要进行2次SPFA。

### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
unsigned short int n,ml,md,a,b;
unsigned int d;
struct node
{
	unsigned short int to,next;
	int w;
}edge[40005];
unsigned short int cnt,head[1005];
inline void add(unsigned short int u,unsigned short int v,int w)
{
	cnt++;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
	edge[cnt].w=w;
}//邻接表
int dis[1005];
unsigned int sum[1005];
char book[1005];
char spfa(unsigned short int start)
{
	memset(dis,0x3f,sizeof(dis));
	memset(sum,0,sizeof(sum));
	memset(book,0,sizeof(book));
	std::queue<unsigned short int> q;
	q.push(start);
	dis[start]=0;
	while(!q.empty())
	{
		unsigned short int i=q.front();
		q.pop();
		book[i]=0;
		for(unsigned short int j=head[i];j!=0;j=edge[j].next)
		{
			if(dis[edge[j].to]>dis[i]+edge[j].w)
			{
				dis[edge[j].to]=dis[i]+edge[j].w;
				sum[edge[j].to]=sum[i]+1;//经过的点统计
				if(sum[edge[j].to]>=n)
				{
					puts("-1");
					return 1;
				}
				if(book[edge[j].to]==0)
				{
					book[edge[j].to]=1;
					q.push(edge[j].to);
				}
			}
		}
	}
	return 0;
}//最短路SPFA
int main()
{
	scanf("%hu%hu%hu",&n,&ml,&md);
	for(unsigned short int i=n;i>=1;i--)
	{
		add(0,i,0);
	}//虚拟源点
	for(unsigned short int i=1;i<=ml;i++)
	{
		scanf("%hu%hu%u",&a,&b,&d);
		add(a,b,d);
	}
	for(unsigned short int i=1;i<=md;i++)
	{
		scanf("%hu%hu%u",&a,&b,&d);
		add(b,a,-d);
	}
	if(spfa(0)==1)//判断解
	{
		return 0;
	}
	spfa(1);//此处从1开始，判断联通性和最短距离
	if(dis[n]==0x3f3f3f3f)
	{
		puts("-2");
		return 0;
	}
	printf("%u",dis[n]);
	return 0;
}
```
#### 运行结果

一本通OJ：

1512

通过 100分

测试点1: 答案正确 428KB 2MS 

测试点2: 答案正确 424KB 1MS 

测试点3: 答案正确 436KB 1MS 

测试点4: 答案正确 436KB 1MS 

测试点5: 答案正确 452KB 1MS 

测试点6: 答案正确 440KB 2MS 

测试点7: 答案正确 452KB 2MS 

测试点8: 答案正确 484KB 6MS 

测试点9: 答案正确 508KB 5MS 

测试点10: 答案正确 516KB 5MS 

洛谷：

评测状态 Accepted

评测分数 100

用时 105ms 内存 912.00KB

测试点信息

2ms/640.00KB AC #1

3ms/656.00KB AC #2

3ms/656.00KB AC #3

3ms/664.00KB AC #4

3ms/772.00KB AC #5

3ms/656.00KB AC #6

3ms/664.00KB AC #7

4ms/692.00KB AC #8

5ms/804.00KB AC #9

5ms/760.00KB AC #10

3ms/692.00KB AC #11

32ms/512.00KB AC #12

36ms/912.00KB AC #13

//第一个AC的紫题！！！

---

## 作者：Sakurajima_Mai (赞：0)

此题差分约束系统，
同时据题意奶牛顺序必须从左到右

设1号奶牛为x1，
2号奶牛为x2
以此类推
 
奶牛间距离不得小于或大于某个值相当于将这个题转化为：
有若干个变量、有若干的不等式
根据不等式列出取值范围确定答案

但又要求最后答案为从1到n号点的距离最大 ，因此
转化为最短路问题

我们设s为起点，则
$dis[i]$表示$s$到$i$的最短路

因此不等式可以写成$dis[a]-dis[b] \leq c$;

如果有大于的情况，通过移项，将其变为小于

据此建边连图

跑最短路

得到取值最大范围的值



---

