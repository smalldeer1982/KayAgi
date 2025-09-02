# [USACO06FEB] Steady Cow Assignment G

## 题目描述

农夫约翰的 $N$ 头牛（$1 \leq N \leq 1000$）各自居住在 $B$ 个谷仓中的一个（$1 \leq B \leq 20$），当然，谷仓的容量是有限的。有些牛非常喜欢她们当前的谷仓，而有些则不太开心。

FJ 想要重新安排这些牛，使得牛群的快乐程度尽可能均衡，即使这意味着所有的牛都讨厌她们被分配的谷仓。


每头牛都会告诉 FJ 她对谷仓的偏好顺序。牛对特定分配的快乐程度是她对该谷仓的排名。你的任务是找到一种将牛分配到谷仓的方法，使得没有谷仓的容量被超出，并且牛给她们被分配的谷仓的排名范围（即最高排名谷仓和最低排名谷仓之间的正差加一）的大小尽可能小。


## 说明/提示

样例解释：




每头牛可以被分配到她们的第一或第二选择：谷仓 1 得到牛 1 和 5，谷仓 2 得到牛 2，谷仓 3 得到牛 4，谷仓 4 得到牛 3 和 6。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
6 4
1 2 3 4
2 3 1 4
4 2 3 1
3 1 2 4
1 3 4 2
1 4 2 3
2 1 3 2```

### 输出

```
2```

# 题解

## 作者：Heartlessly (赞：15)

## Description

给定 $n$ 头牛和 $b$ 座牛棚，已知每头牛最喜欢，第 $2$ 喜欢，第 $3$ 喜欢，……，第 $b$ 喜欢的牛棚分别是什么，以及每个牛棚的容量 $v_i$（最多能住 $v_i$ 头牛）。如果某头牛住在第 $i$ 喜欢的牛棚里，则这头牛的不满意度为 $i$ 。求如何分配牛棚，使所有牛的 **最大不满意度 - 最小不满意度 + 1** 的值最小。输出这个值是多少。

$(1 \leq n \leq 10^3,1 \leq b \leq 20,\sum\limits_{i = 1}^n v_i = n)$

## Solution

考虑 **网络流 + 二分答案** 。

我们可以把图分成两部分。左部点是牛，右部点是牛棚。

在源点与每头牛之间连一条流量为 $1$ 的边（一头牛最大贡献为 $1$），在第 $i$ 个牛棚与汇点之间连一条流量为 $v_i$ 的边（一个牛棚最大贡献为 $v_i$）。

对于样例所建出的图：

![VlHlCQ.png](https://s2.ax1x.com/2019/05/31/VlHlCQ.png)

牛和牛棚之间的边呢？显然不能直接全部连上。

我们可以 **二分答案**（假设答案为 $x$），然后枚举所有牛的 **最小不满意度** $i$，那么 **最大不满意度** 为 $i + x - 1$ 。

即每头牛不满意度所在的区间为 $[i,i + x - 1]$ 。也就是说，对于每一头牛，我们只需要在它与它第 $i \sim i + x - 1$ 喜欢的牛棚之间连一条流量为 $1$ 的边。接着用 $\rm dinic$ 跑一遍最大流，若最大流为 $n$，则这个答案可行。

不过由于数据范围比较小，暴力枚举也能过。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 2e3, MAXB = 20, MAXM = 1e5, INF = 0x3f3f3f3f;
int n, b, ans, tot, head[MAXN + 5], cur[MAXN + 5], depth[MAXN + 5];
int v[MAXB + 5], f[MAXN + 5][MAXB + 5];
struct Edge {
    int next, to, dis;
} e[MAXM + 5];

inline void addEdge(int u, int v, int w) {
    e[++tot] = (Edge) { head[u], v, w };
    head[u] = tot;
}

inline bool bfs(int s, int t) {
    for (int i = 0; i <= t; ++i) cur[i] = head[i];
    memset(depth, 0, sizeof (depth));
    queue<int> q;
    depth[s] = 1;
    q.push(s);
    for (; !q.empty(); ) {
        int u = q.front();
        q.pop();
        for (int v, w, i = head[u]; v = e[i].to, w = e[i].dis, i; i = e[i].next) {
            if (depth[v] || !w) continue;
            depth[v] = depth[u] + 1;
            if (v == t) return 1;
            q.push(v);
        }
    }
    return 0;
}

int dinic(int u, int t, int flow) {
    if (u == t) return flow;
    int rest = flow;
    for (int v, w, i = cur[u]; v = e[i].to, w = e[i].dis, i && rest; i = e[i].next) {
        cur[u] = i;//当前弧优化 
        if (depth[v] != depth[u] + 1 || !w) continue;
        int k = dinic(v, t, min(rest, w));
        if (!k) depth[v] = 0;
        else {
            e[i].dis -= k;
            e[i ^ 1].dis += k;
            rest -= k;
        }
    }
    return flow - rest;
}

inline int maxFlow(int s, int t) {
    int res = 0;
    for (; bfs(s, t); ) res += dinic(s, t, INF);
    return res;
}

inline bool check(int x) {//检查答案 x
    for (int i = 1; i + x - 1 <= b; ++i) {
        //最小满意度为 i，最大满意度为 i + x - 1
        tot = 1;
        memset(head, 0, sizeof (head));
        int s = 0, t = n + b + 1;//源点编号和汇点编号 
        for (int j = 1; j <= n; ++j)//源点与牛连一条流量为 1 的边 
            addEdge(s, j, 1), addEdge(j, s, 0);
        for (int j = 1; j <= b; ++j)//牛棚与汇点连一条流量为 v[j] 的边 
            addEdge(j + n, t, v[j]), addEdge(t, j + n, 0);
        //与第 i ~ i + x - 1 喜欢的牛棚连一条流量为 1 的边
        for (int j = 1; j <= n; ++j)
            for (int k = i; k <= i + x - 1; ++k)
                addEdge(j, f[j][k] + n, 1), addEdge(f[j][k] + n, j, 0);
        if (maxFlow(s, t) == n) return 1;//若最大流为 n，则该答案可行 
    }
    return 0;
}

int main() {
    read(n), read(b);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= b; ++j)
            read(f[i][j]);//第 i 头牛第 j 喜欢的牛棚是 f[i][j] 
    for (int i = 1; i <= b; ++i) read(v[i]);
    for (int mid, l = 1, r = b; l <= r; ) {//二分答案 
        mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        } else l = mid + 1;
    }
    write(ans);
    putchar('\n');
    return 0;
}
```


---

## 作者：Jayun (赞：9)

# 声明：

本题解借鉴了@Heartlessly（luogu UID=32139）的内容

# 题目大意：

每只牛对于每个牛棚有一个差评值，现在分配牛棚，使得所有牛的最大差评值与最小差评值的差最小，求这个值。

# 正文：

因为题目中有提到过每个牛棚的限度，也就是说我们可以用网络瘤来求解。

样例图：

![样例图](https://s2.ax1x.com/2019/12/27/lZsxKO.png)

牛棚编号要加上$n$因为牛那边已经用过

接着怎么办？我们考虑到二分答案。

那我们先想一想最大差评值与最小差评值的差最大是多少，因为最大差评值最大$=b$, 最小差评值最小$=1$,那么最大差评值与最小差评值的差最大是$b-1$

我们可以再$[1,b]$中找到我们的答案。

---

假设我们二分到$x$（最大差评值与最小差评值的差），最小差评值$=i$，那么最大差评值$=i+x-1$。先把上图情况存入邻接表，我们肯定不能直接把牛连到所有牛棚只能连部分的。既然二分到$x$的最小差评值$=i$，最大差评值$=i+x-1$，那么每头牛就只能连它第$i$个到第$(i+x-1)$个牛棚。

做完~~连一连~~后，跑一遍最大流，毕竟我们本身就是$n$头牛，如果最大流不是$n$那么方案就是不可行的。

# 代码：

```cpp


bool check(int x)
{
	for (int i = 1; i + x - 1 <= b; i++)
	{
		memset(head, 0, sizeof(head));
		tot = 0;
		s = n + b + 1, t = n + b + 2;
		for (int j = 1; j <= n; j++) Add(s, j, 1);       //连成上图
		for (int j = 1; j <= b; j++) Add(j + n, t, v[j]);
		for (int j = 1; j <= n; j++)
			for (int k = i; k <= i + x - 1; k++)
				Add(j, like[j][k] + n, 1);        //连第i个到第(i+x-1)个牛棚
		int ans = dinic();
		if(ans == n) return 1;     // 网络瘤
	}
	return 0;
}

int main()
{
	scanf("%d%d", &n, &b); 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= b; j++)
			scanf("%d", &like[i][j]);  //like[i][j] 表示第i只牛差评度为j的牛棚
	for (int j = 1; j <= b; j++)
		scanf("%d", &v[j]);   // v[i] 表示第i个牛棚的限度
	int l = 1, r = b, mid, ans = 0;
	while(l <= r)           //二分开始
	{
		mid = (l + r) >> 1;
		if(check(mid))
		{
			ans = mid;
			r = mid - 1;
		} 
		else 
			l = mid + 1;
	}
	printf("%d", ans);
	return 0;
}

```

---

## 作者：灵华 (赞：3)

## P2857 Steady Cow Assignment G

[My blog](https://www.cnblogs.com/linghuabaobao/p/15733002.html)

### 题目描述：

[题目链接](https://www.luogu.com.cn/problem/P2857)

有 $N$ 头牛， $B$ 个牛棚。告诉你每头牛心里牛棚的座次，即哪个牛棚他最喜欢，哪个第二喜欢， 哪个第三喜欢，等等。但牛棚容量一定，所以每头牛分配到的牛棚在该牛心中的座次有高有低。现在求一种最公平的方法分配牛到牛棚，使所有牛中，所居牛棚的座次最高与最低的跨度最小。

其中 $1\le N \le 1000 , 1\le B \le 20$。

### 解法：

直接求好像是不大好做，所以我们考虑二分答案，二分这个最小的跨度是多少。如果当前跨度不行，就更改左端点，否则就更改右端点。

关于判断当前这个跨度是否可行的时候，我们要枚举到这个跨度所有可能出现的情况。比如当前枚举到的跨度是 $d$，那么我们要枚举 $1\sim d,2\sim d+1,3\sim d+2,\cdots,B-d+1\sim B$ 这所有的情况，然后把所有的牛的喜欢度在当前这个情况的区间的连边。

然后如何判断当前这种连边情况是否合法呢，我们考虑使用网络流。

把源点连向牛，容量是一，因为一条边只会连一头牛。

把牛棚连向汇点，容量是牛棚的容量。

牛与牛棚的连边任意（只要不为零即可）。

如果说当前这种情况的最大流等于 $N$，那么说明所有连向牛的边都能连向汇点，意味着这种情况是可以的，所以这个跨度就是可以的，之后继续二分就可以了。

注意事项：

每次跑完最大流的时候记得清空当前连的边。

记得二分跨度的时候从零开始（虽然好像洛谷的数据从一开始也能过）。



### Code：

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std ;

int n , m , a[1005][25] , b[25] , dis[1025] ;

struct Edge
{
	int nxt , to , len ;
} edge[400005] ;

int cnt = 1 , head[1025] ;
void insert ( int u , int v , int w )
{
	edge [ ++ cnt ] .nxt = head [ u ] ;
	edge [ cnt ] .to = v ;
	edge [ cnt ] .len = w ;
	head [ u ] = cnt ;
}

queue < int > q ;
bool bfs ( )
{
	memset ( dis , 0 , sizeof ( dis ) ) ;
	dis [ 0 ] = 1 ;
	q .push ( 0 ) ;
	while ( ! q .empty ( ) )
	{
		int x = q .front ( ) ; q .pop ( ) ;
		for ( int i = head [ x ] ; i ; i = edge [ i ] .nxt )
		{
			int y = edge [ i ] .to ;
			if ( ! edge [ i ] .len || dis [ y ] )
				continue ;
			dis [ y ] = dis [ x ] + 1 ;
			q .push ( y ) ;
		}
	}
	return dis [ n + m + 1 ] ;
}

int dfs ( int x , int now )
{
	if ( x == n + m + 1 )
		return now ;
	int res = now ;
	for ( int i = head [ x ] ; i && res ; i = edge [ i ] .nxt )
	{
		int y = edge [ i ] .to ;
		if ( ! edge [ i ] .len || dis [ y ] != dis [ x ] + 1 )
			continue ;
		int w = dfs ( y , min ( res , edge [ i ] .len ) ) ;
		if ( ! w ) dis [ y ] = 0 ;
		edge [ i ] .len -= w ;
		edge [ i ^ 1 ] .len += w ;
		res -= w ;
	}
	return now - res ;
}

int main ( )
{
	cin >> n >> m ;
	for ( int i = 1 ; i <= n ; ++ i )
		for ( int j = 1 ; j <= m ; ++ j )
		{
			cin >> a [ i ] [ j ] ;
			a [ i ] [ j ] += n ;
		}
	for ( int i = 1 ; i <= m ; ++ i )
		cin >> b [ i ] ;
	int l = 0 , r = m , mid ;
	while ( l < r )
	{
		mid = ( l + r ) >> 1 ;
		for ( int i = 0 ; i <= m - mid ; ++ i )
		{
			memset ( head , 0 , sizeof ( head ) ) ;
			cnt = 1 ;
			for ( int u = 1 ; u <= n ; ++ u )
				for ( int j = 1 ; j <= mid ; ++ j )
					insert ( u , a [ u ] [ i + j ] , 1000 ) , insert ( a [ u ] [ i + j ] , u , 0 ) ;
			for ( int u = 1 ; u <= n ; ++ u )
				insert ( 0 , u , 1 ) , insert ( u , 0 , 0 ) ;
			for ( int u = n + 1 ; u <= n + m ; ++ u )
				insert ( u , n + m + 1 , b [ u - n ] ) , insert ( n + m + 1 , u , 0 ) ;
			int tmp = 0 , ans = 0 ;
			while ( bfs ( ) )
				ans += dfs ( 0 , 2000 ) ;
			if ( ans == n )
			{
				r = mid ;
				break ;
			}
		}
		if ( r != mid )
			l = mid + 1 ;
	}
	cout << r << '\n' ;
	return 0 ;
}
```


---

## 作者：xsxshxs (赞：2)

一道枚举+最大流

正好很久没写网络流了，对着版抄了一遍Dinic(雾

目测过去将枚举替换为二分也能写过(并且快)，但是由于本人太弱一直调不过，注释掉的部分仅供参考

连边：

1.将猪圈和源点连边，容量为猪圈容量

2.猪与汇点连边，容量1;

具体详见代码

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 200001;
const int MAXX = 2001;
int n, b, map[MAXX][MAXX], c[MAXN], m;
int flag[MAXN], E[MAXN];
int head[MAXN], next[MAXN], to[MAXN], dis[MAXN], tot = 0;

inline int get()
{
    char c;bool f = 0; int res = 0;
    while (( (c=getchar())<48||c>57) && c!= '-');
     if (c=='-') f = 1;
      else res = c- '0';
    while ( (c = getchar()) >= 48 && c <= 57)
     res = res * 10 + c -'0';
    return f ? -res:res;
}
inline void put(int x)
{
    if (x<0)
    { 
        x = ~x + 1;
        putchar('-');
    }
    if (x>9) 
    put(x / 10);
    putchar(x % 10 + 48);
}
void add(int x, int y, int z)
{
    tot++;
    next[tot] = head[x];
    head[x] = tot;
    to[tot] = y;
    dis[tot] = z;
    next[++tot] = head[y];
    head[y] = tot;
    to[tot] = x;
    dis[tot] = 0;
}
int bfs()
{
    static int que[MAXN], q;
    for (int i = 0; i <= 100001; i++)
    {
        flag[i] = -1;
        E[i] = head[i];
    }
    int u, v, e;
    que[q = 1] = 0;
    flag[0] = 0;
    for (int i = 1; i <= q; i++)
    {
        u = que[i];
        for (e = head[u]; e; e = next[e])
        {
            if (dis[e] > 0 && flag[v = to[e]] == -1)
            {
                flag[v] = flag[u] + 1;
                que[++q] = v;
                if (v == m) return true;
            }
        }
    }
    return false;
}
int dfs(const int &u, const int &l)
{
    if (u == m) return l;
    int cnt = 0, v, d;
    for (int &e = E[u]; e; e = next[e])
    {
        if (dis[e] > 0 && flag[u] < flag[v = to[e]])
        {
            d = dfs(v, min(dis[e], l - cnt));
            if (d)
            {
                dis[e] -= d;
                dis[e ^ 1] += d;
                cnt += d;
                if (cnt == l) break;
            }
        }
    }
    if (cnt != l) flag[u] = -1;
    return cnt;
}
int Dinic()  
{  
    int ans = 0, a;  
    while (bfs())  
    {
        ans += dfs(0, INF);
    }
    return ans;  
}  
int Work(int k,int p)
{
/*    for(int i = 1; i <= b - mid + 1; i++)
    {
        memset(head, 0, sizeof(head));
        for(int j = 1; j <= b; j++)
        add(0, j, c[j]);
        for(int j = 1; j <= n; j++)
        {
            for(int k = 1; k <= i + mid - 1; k++)
            add(map[j][k], j + b, 1);
            add(j + b, m, 1);
        }
        if(Dinic() == n) return true;
    }
    return false;*/
    for(int i = 1; i <= n; i++)
    { 
        for(int j = k; j <= p; j++)
        add(map[i][j], i + b, 1); 
        add(i + b, m, 1); 
    } 
    for(int i = 1; i <= b; i++)
    add(0, i, c[i]) ; 
}
int Solve()
{
    int ans = INF;
    for(int i = 1; i <= b; i++)
    {
        for(int j = 1; j <= b; j++)
        {
            memset(head, 0, sizeof(head));
            tot = 0;
            Work(i, j);
            int t = Dinic();
            if(t == n)
            {
                ans = min(ans, j - i + 1);
                if(ans == 1) return ans;
            }
        }
    }
    return ans;
}
int main()
{
    n = get(); b = get();
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= b; j++)
    map[i][j] = get();
    for(int i = 1; i <= b; i++)
    c[i] = get();
    m = n + b + 1; 
    /*int l = 1, r = b, s = -1;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        if(Work(mid))
        {
            s = mid;
            r = mid - 1;
        }
        else
        l = mid + 1;
    }
    put(s);*/
    put(Solve());
}
```

---

## 作者：破忆 (赞：1)

## 【题目大意】
有n头牛和b个棚

每头牛心目中都有对棚的排名

每头牛只能选一个棚，每个棚有一定的容量

安排一个方案，使牛去的棚的最大排名与最小排名的差最小，输出最小的差

## 【分析】
牛棚座次的跨度越大，就越容易满足牛的需求

两者之间满足单调性，那题目就是求跨度最小的能满足牛需求的方案

所以可以**二分**答案

二分枚举一个差值，再枚举最小排名与最大排名

检验是否可以满足牛的要求，可以用**网络流**

* S向奶牛连边，流量为1

* 奶牛向可以选择的牛棚连边，流量为1

* 牛棚向T连边，流量为棚的容量

这样，就可以满足每头牛只能选一个棚，每个棚有一定的容量

最大流就是可以满足需求的牛数的最大值

这个结果如果等于牛数，表示可行

## 【算法】
二分+网络流
## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005,maxb=25,maxt=maxn+maxb,maxe=maxn*maxb*2,INF=1<<30;
int n,m,S,T;
int tot,lnk[maxt];
int cur[maxt],dep[maxt],que[maxt];
int a[maxn][maxb],b[maxb];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int ans;
struct edge{
	int to,nxt,f;
}e[maxe];
void add_e(int x,int y,int f){
	e[++tot]=(edge){y,lnk[x],f};
	lnk[x]=tot;
}
void ADD(int x,int y,int f){
	add_e(x,y,f),add_e(y,x,0);
}
void make_e(int l,int r){
	tot=1;
	memset(lnk,0,sizeof lnk);//重新建边需清空
	for(int i=1;i<=n;i++) ADD(S,i,1);
	for(int j=1;j<=m;j++) ADD(j+n,T,b[j]);
	for(int i=1;i<=n;i++)
	for(int j=l;j<=r;j++) ADD(i,a[i][j]+n,1);
}
bool BFS(){
	for(int i=1;i<=T;i++) cur[i]=lnk[i],dep[i]=INF;
	int hed=0,til=1;
	que[1]=S,dep[S]=0;
	while(hed!=til){
		int x=que[++hed];
		for(int j=lnk[x];j;j=e[j].nxt){
			int y=e[j].to;
			if(dep[y]==INF&&e[j].f){
				dep[y]=dep[x]+1;
				que[++til]=y;
			}
		}
	}
	return dep[T]!=INF;
}
int DFS(int x,int limit){
	if(x==T||!limit) return limit;
	int flow=0,f;
	for(int j=cur[x];j;j=e[j].nxt){
		cur[x]=j;
		int y=e[j].to;
		if(dep[y]==dep[x]+1&&(f=DFS(y,min(limit,e[j].f)))){
			flow+=f;
			limit-=f;
			e[j].f-=f;
			e[j^1].f+=f;
			if(!limit) return flow;
		}
	}
	return flow;
}
int Dinic(){
	int ret=0;
	while(BFS()) ret+=DFS(S,INF);
	return ret;
}
bool check(int x){
	for(int i=1;i+x-1<=m;i++){
		make_e(i,i+x-1);
		if(Dinic()==n) return 1;
	}
	return 0;
}
int main(){
	freopen("P2857.in","r",stdin);
	freopen("P2857.out","w",stdout);
	n=read(),m=read();
	S=n+m+1,T=S+1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) a[i][j]=read();
	for(int i=1;i<=m;i++) b[i]=read();
	int L=0,R=m,mid;
	while(L<=R){
		mid=L+R>>1;
		if(check(mid)) ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Newuser (赞：1)

本蒟蒻的同步博客，[Newuser小站！](http://www.newuser.top/2018/04/13/%e3%80%90usaco06feb%e7%a8%b3%e5%ae%9a%e5%a5%b6%e7%89%9b%e5%88%86%e9%85%8dsteady-cow-assignment%e3%80%91/)

为什么luogu标签是前缀和贪心和线段树，，，为什么，，，这里是SAP最大流做法

刚学SAP，蒟蒻默默%%%dalao们。

两层的枚举：
第一层：首先二分本题答案（很小，也可以直接枚举）

第二层：然后再套一个枚举，枚举选择哪几个等级。

建图：考虑将所有的牛棚与汇点连边，容量为牛棚容量。再将每一只牛与牛棚连边，容量为1，再将源点与每一只牛连边，容量为1，这样就把一道题转化为了最大流问题了。最后只要汇点爬出最大流为牛的总数就搞定。

于是 就这样一道题 搞定了！

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
const int inf = 0x3f3f3f3f;
using namespace std;
int n,m;
int dis[205],cnt[10005],v[205][205];
queue<int>q; bool rd[205];
void spfa(int x)
{
for(int i=1;i<=m;i++) dis[i]=inf;
dis[x]=0; q.push(x);
while(q.size())
{
x=q.front(); q.pop(); rd[x]=0;
for(int i=1;i<=m;i++)
{
if(i==x) continue;
if(v[i][x]&&dis[i]>dis[x]+1)
{
dis[i]=dis[x]+1;
if(!rd[i])
{
rd[i]=1;
q.push(i);
}
}
}
}
}
int dfs(int x,int flow)
{
int y,tmp,delta;
if(x==m) return flow;
delta=0;
for(y=1;y<=m;y++)
if(v[x][y]>0&&dis[x]==dis[y]+1)
{
tmp=dfs(y,min(flow-delta,v[x][y]));
delta+=tmp;
v[x][y]-=tmp;
v[y][x]+=tmp;
if(delta==flow||dis[1]>=m) return delta;
}
if(dis[1]>=m) return delta;
cnt[dis[x]]--;
if(!cnt[dis[x]]) dis[1]=m;
dis[x]++;
cnt[dis[x]]++;
return delta;
}
int main()
{
scanf("%d%d",&n,&m);
int x,y,z;
for(int i=1;i<=n;i++)
{
scanf("%d%d%d",&x,&y,&z);
v[x][y]+=z;
}
// spfa(m);
int ans=0;
while(dis[1]<m)
{
int flow=dfs(1,inf);
ans+=flow;
}
printf("%d",ans);
}

```




---

## 作者：happy_dengziyue (赞：0)

### 1 思路

因为数据非常小，所以枚举答案。

设答案为 $ans$，那么，要求每头牛只能住它第 $l$ 喜欢到第 $l+ans-1$ 喜欢的牛棚。

每次枚举的时候注意连边：

+ 连源点到所有牛的容量为 $1$ 的边；

+ 连所有牛到所有它能住的牛棚的容量为 $1$ 的边；

+ 连所有牛棚到汇点的容量为牛棚容量的边。

如果最大流等于 $n$，就说明这个方案可行。

输出 $ans$ 即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define max_n 1000//最大牛数
#define max_b 200//最大牛棚数
#define inf 0x3f3f3f3f//很大的数
int n;//牛数
int b;//牛棚数
#define s 0//源点
#define t 1210//汇点
int a[max_n+2][max_b+2];//喜好排名
int v[max_b+2];//牛棚容量
struct E{
	int u,v,w,a,nx;
}e[220000];//边
int ei;//下标
int fir[1220];//开始路径
int de[1220];//深度
int ans;//答案
inline void addedge(int u,int v,int w){
	++ei; e[ei].u=u; e[ei].v=v; e[ei].w=w; e[ei].a=ei+1; e[ei].nx=fir[u]; fir[u]=ei;
	++ei; e[ei].u=v; e[ei].v=u; e[ei].w=0; e[ei].a=ei-1; e[ei].nx=fir[v]; fir[v]=ei;
}
inline int mi(int a,int b){
	return a<b?a:b;
}
bool bfs(){
	memset(de,0,sizeof(de));
	queue<int>q;
	int u;
	de[s]=1;
	q.push(s);
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(int i=fir[u],v,x,y;i;i=e[i].nx){
			v=e[i].v;
			if(e[i].w&&!de[v]){
				de[v]=de[u]+1;
				q.push(v);
			}
		}
	}
	return de[t];
}
int dfs(int u,int f){
	if(u==t||!f)return f;
	int res=0;
	for(int i=fir[u],v,w;i;i=e[i].nx){
		v=e[i].v;
		if(e[i].w&&de[u]+1==de[v]){
			w=dfs(v,mi(f,e[i].w));
			if(w){
				e[i].w-=w;
				e[e[i].a].w+=w;
				f-=w;
				res+=w;
				if(!f)break;
			}else de[v]=0;//加个优化
		}
	}
	return res;
}
int dinic(){
	int res=0;
	while(bfs())res+=dfs(s,inf);
	return res;
}
bool check(int x){
	for(int l=1,r;l+x-1<=b;++l){
		r=l+x-1;
		ei=0;
		memset(fir,0,sizeof(fir));
		for(int i=1;i<=n;++i)addedge(s,i,1);
		for(int i=1;i<=n;++i){
			for(int j=l;j<=r;++j)addedge(i,a[i][j]+n,v[a[i][j]]);
		}
		for(int i=1;i<=b;++i)addedge(i+n,t,v[i]);
		if(dinic()>=n)return true;
	}
	return false;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P2857_1.in","r",stdin);
	freopen("P2857_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=b;++j){
			scanf("%d",a[i]+j);
		}
	}
	for(int i=1;i<=n;++i){
		scanf("%d",v+i);
	}
	for(ans=1;!check(ans);++ans);
	printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58023659)

By **dengziyue**

---

## 作者：ycyaw (赞：0)

考虑$B$的范围比较小，那就$B^2$暴力枚举所有的座次区间。枚举到一个座次从$l$到$r$的区间，意义是奶牛只能选它心目中座次从$l$到$r$区间的牛棚。

然后就是判断区间是否可行，考虑网络流，源点向奶牛连边，奶牛向可选牛棚连边，牛棚向汇点连它容量的边。$Dinic$判断最大流是否是$n$。

不用当前弧优化好像会$T$？

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
using namespace std;
int n,b,g[1005][25],ans=1e9,st,ed,tot,can[25],head[1025],cnt,d[1025],cur[1025];
struct Edge{
    int v,nx,s;
}e[100005];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+ch-'0';ch=getchar();}
    return ret*ff;
}
void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+48);
}
inline void add(int x,int y,int s){
    e[++cnt].v=y;
    e[cnt].s=s;
    e[cnt].nx=head[x];
    head[x]=cnt;
}
inline bool bfs(){
    for(int i=st;i<=ed;i++) cur[i]=head[i],d[i]=0;
    d[st]=1;
    queue<int> q;
    q.push(st);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=head[now];i;i=e[i].nx){
            int v=e[i].v;
            if(!d[v]&&e[i].s){
                d[v]=d[now]+1;
                q.push(v);
            }
        }
    }
    return d[ed];
}
int dfs(int now,int ma){
    if(now==ed){
        tot+=ma;
        return ma;
    }
    int used=0,t;
    for(int i=cur[now];i;i=e[i].nx){
        cur[now]=i;
        int v=e[i].v;
        if(d[v]==d[now]+1&&e[i].s){
            if(t=dfs(v,min(e[i].s,ma-used))){
                e[i].s-=t;
                e[i^1].s+=t;
                used+=t;
                if(used==ma) break;
            }
        }
    }
    return used;
}
void build(int l,int r){
    cnt=1;
    memset(head,0,sizeof(head));
    for(int i=1;i<=n;i++) add(st,i,1),add(i,st,0);
    for(int i=1;i<=n;i++)
        for(int j=l;j<=r;j++)
            add(i,n+g[i][j],1),add(n+g[i][j],i,0);
    for(int i=1;i<=b;i++) add(n+i,ed,can[i]),add(ed,n+i,0);
}
signed main(){
    n=read(),b=read();
    st=0,ed=n+b+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=b;j++)
            g[i][j]=read();
    for(int i=1;i<=b;i++) can[i]=read();
    for(int i=1;i<=b;i++)
        for(int j=i;j<=b;j++){
            if(j-i+1>=ans) continue;
            build(i,j);
            tot=0;
            while(bfs()) dfs(st,1e9);
            if(tot==n) ans=j-i+1;
        }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：mydiplomacy (赞：0)

在一种方案中，我们设所有牛中，分到最高位次牛棚的位次为$mina$，分到最低位牛棚的位次为$maxa$。于是题意为寻找一种方案使$maxa-mina$最小。

由于$b$最小，我们可以枚举$maxa$与$mina$。当给定$mina$与$maxa$以后，我们就可以确定每头牛可以选择的牛棚。同时，我们也可以知道每个牛棚的容量。此时，问题转化为：给定每头牛可选择的牛棚和每个牛棚的容量，求出是否有满足条件的方案。我们只要在所有满足条件的方案中寻找最小的$maxa-mina$即可。

考虑最大流算法。

我们将源点$（src）$与每个牛棚相连，容量为牛棚最大容量。

如果存在一组$(i,j)$使得第$i$头牛可以选择第$j$个牛棚，那么将第$j$个牛棚连到第$i$头牛，容量为$1$。

最后，将每头牛连到汇点$sink$，容量为$1$。

那么，如果最大流跑出的结果与牛的数量相等，那么就存在一种合符条件的方案。

具体细节见代码。


```
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=10005, maxm=1000005, maxb=105;

/*******以下为dinic模板********/

struct Node
{
	int v,c;
	Node *next,*rev;
}*h[maxn],pool[maxm];
int tot;

int a[maxn][maxb];

void addEdge(int u, int v, int c)
{
	Node *p=&pool[++tot], *q=&pool[++tot];
	p->v=v; p->next=h[u]; h[u]=p; p->rev=q; p->c=c;
	q->v=u; q->next=h[v]; h[v]=q; q->rev=p; q->c=0;
}

int level[maxn];
int q[maxn],head,tail;
int m,src,sink;

bool bfs()
{
	//cout<<"here"<<endl;
	head = tail = 0;
	memset(level,-1,sizeof(level));
	level[src]=0; q[tail++]=src;
	while(head<tail)
	{
		int u=q[head++];
		for(Node *p=h[u];p;p=p->next)
		{
			if(level[p->v]==-1 && p->c>0)
			{
				level[p->v]=level[u]+1;
				q[tail++]=p->v;
			}
		}
		if(level[sink]>0) return true;
	}
	return false;
}

int dfs(int u, int key)
{
	//cout<<u<<' '<<key<<endl;
	if(u==sink) return key;
	int res=0;
	for(Node *p=h[u];p;p=p->next)
	{
		if(level[p->v]==level[u]+1 && p->c>0)
		{
			//cout<<"here1"<<endl;
			int t=dfs(p->v,min(p->c,key));
			//cout<<"here2"<<endl;
			if(t)
			{
				p->c-=t;
				p->rev->c+=t;
				res+=t;
				key-=t;
			}
		}
		if(key<=0) break;
	}
	if(res==0) level[u]=-1;
	return res;
}

int dinic()
{
	int totflow=0;
	while(bfs()) totflow+=dfs(src,1<<30);
	return totflow;
}

/*******以上为dinic模板********/

void reset() //每次需要重新跑最大流，所以写一个初始化函数
{
	tot=0;
	memset(h,NULL,sizeof(h));
}

int n,b;
int num[maxn]; //num代表牛棚最大容量

void build(int left, int right) //代表mina为left，maxa为right时的建图
{
	src=n+b+1; sink=src+1;
	for(int i=1;i<=b;i++)
		addEdge(src,i,num[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=left;j<=right;j++)
		{
			addEdge(a[i][j],i+b,1);
		}
		addEdge(i+b,sink,1);
	}
}

int main()
{
	freopen("1.in","r",stdin);
	int ans=1<<30;
	cin>>n>>b;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=b;j++)
			cin>>a[i][j];
	}
	for(int i=1;i<=b;i++)
		cin>>num[i];
	for(int left=1;left<=b;left++)
	{
		for(int right=left;right<=b;right++)
		{
			reset();
			//cout<<"here "<<left<<' '<<right<<endl;
			build(left,right);
			//cout<<"graph "<<left<<' '<<right<<endl;
			if(dinic()==n)
			{
				ans=min(ans,right-left+1);
				if(ans==1) break;
			}
			//cout<<"finish "<<left<<' '<<right<<endl;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

