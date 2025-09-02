# [ABC087D] People on a Line

## 题目描述

在一根数轴上站有 $n$ 个人，我们称第 $i$ 个人的坐标为 $x_i(x_i\in [0,10^{9}],x_i\in Z)$，同一个坐标点上可能有多个人。

你现在手上有 $m$ 条信息，第 $i$ 条信息形如 $(li,ri,di)$，含义是第 $r_i$ 个人在第 $l_i$ 个人右数第 $d_i$ 个坐标点上，换言之，$x_{r_i} - x_{l_i} = d_i$。

不幸的是，这 $m$ 条信息中的一些可能有误，请你求出是否存在一组 $x (x_1,x_2,x_3,\dots ,x_n)$ 满足所有信息。

## 说明/提示

全部的输入数据满足以下条件：

-  $1 \le n \le 100000$；
-  $0 \le m \le 200000$；
- $1\le l_i,r_i\le n (1\le i\le m)$；
- $0\le d_i\le 10000 (1\le i\le m)$；
- $l_i \ne r_i (1 \le i \le m)$；
- 如果 $i\le j$，则有 $(l_i,r_i)\ne (l_j,r_j),(l_i,r_i)\ne (r_j,l_j)$；
- $d_i$ 为整数。


$(0,1,2)$ 与 $(101,102,103)$ 都是合法的解。


若前两条信息是正确的，则有 $x_3 - x_1 = 2$，那么第三条信息就是错误的。

感谢@fbhou  提供的翻译

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
1 3 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 5```

### 输出

```
No```

## 样例 #3

### 输入

```
4 3
2 1 1
2 3 5
3 4 2```

### 输出

```
Yes```

## 样例 #4

### 输入

```
10 3
8 7 100
7 9 100
9 8 100```

### 输出

```
No```

## 样例 #5

### 输入

```
100 0```

### 输出

```
Yes```

# 题解

## 作者：Doraven (赞：6)

这题其实只是一道基础的带权并查集，用不着差分约束

同一般并查集一样，我们需要一个$find(x)$函数，但不同的是，我们可以在记录$fa[x]$的同时再记录一个$dis[x]$数组，表示x至其祖先的距离。

$find(x)$ 写法如下

```
int find(int x){
    if(fa[x]!=x){
        int nf=fa[x];
        fa[x]=find(fa[x]);
        dis[x]+=dis[nf];
    }
    return fa[x];
}
```

当读入一组$(l,r,d)$时，也要更新其至祖先的值，并进行判断。($ok==0$表示不行)
代码：

```
int rl=find(l),rr=find(r);
        if(rl==rr&&dis[l]-dis[r]!=d)
            ok=0;
        if(rl!=rr){
            fa[rl]=rr;
            dis[rl]=d+dis[r]-dis[l];
        }
```
        
综合起来，即可AC

```
#include<cstdio>
int n,m,fa[100005],dis[100005];
bool ok=1;
int find(int x){
    if(fa[x]!=x){
        int nf=fa[x];
        fa[x]=find(fa[x]);
        dis[x]+=dis[nf];
    }
    return fa[x];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++){
        int l,r,d;
        scanf("%d%d%d",&l,&r,&d);
        int rl=find(l),rr=find(r);
        if(rl==rr&&dis[l]-dis[r]!=d)
            ok=0;
        if(rl!=rr){
            fa[rl]=rr;
            dis[rl]=d+dis[r]-dis[l];
        }
    }
    if(ok)printf("Yes");
    else printf("No");
    return 0;
} 
```

---

## 作者：CreeperLordVader (赞：4)

## 给大家提供一种DFS判负环的方式

##### 差分约束建图的过程见楼下大佬，这里主要是dfs

#### 我们先给起点打一个vis标记，表示在本次DFS中它已经被访问过，如果儿子节点的最短路的值(下面的d数组)小于父节点的值加边权，更新节点。

#### 如果新节点没有访问到已经vis的点，那么更新点的最短路权值，继续DFS。否则返回true(有负环)。

#### 如果在继续下一层DFS时返回值为true，那么这一层也返回true。

#### 如果没有负环，那么在函数的最后把vis标记撤除并返回false(没有负环)

## 需要注意的是

#### 图可能会存在多个联通块，因此要用一个use数组来标记是否走过，不同于vis，use不能撤除，用一次循环，没有use标记就以它为起点dfs

##### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long d[100005];
int n,m;
bool vis[100005],use[100005];
vector<int>v[100005];
vector<int>e[100005];
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
}//快读
bool dfs(int fa)
{
	vis[fa]=1;
	use[fa]=1;
	for(int i=0;i<v[fa].size();i++)
	{
		int y=v[fa][i];
		int z=e[fa][i];
		if(d[y]>d[fa]+z)//如果可以更新
		{
			if(vis[y])return 1;//如果新点已经被访问，返回1
			d[y]=d[fa]+z;//更新点权
			if(dfs(y))return 1;//如果在继续下一层dfs时返回了0,这一层也返回0
		}
	}
	vis[fa]=0;撤除vis标记
	return 0;
}
int main()
{
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
	{
		d[i]=200000000000ll;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		read(x);
		read(y);
		read(z);
		v[x].push_back(y);
		e[x].push_back(z);
		v[y].push_back(x);
		e[y].push_back(-z);
	}
	bool ok=0;
	for(int i=1;i<=n;i++)
	{
		if(!use[i])//没走过就走
		{
			d[i]=0;
			if(dfs(i))
			{
				ok=1;
			}
		}
	}
	if(ok)printf("No\n");
	else printf("Yes\n");
	return 0;
}
```

---

## 作者：Wen_kr (赞：4)

差分约束，裸的模板。

使用SPFA跑一遍最短路，如果没有访问过一个节点，则访问该节点，记录距离并且将节点入队。

当访问到一个访问过的节点时，若当前距离不符合上次的距离，则不合法return false，否则继续访问。

若能顺利访问所有节点，则返回true.

因为没有限制的范围，甚至差分约束都不需要，暴力搜索即可。

这里判了一下如果坐标之差 > $10^9$ 则不合法，然而并没有这种数据。

这里只给出差分约束的写法：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
 
using namespace std;
 
struct edge
{
    int v,w,nxt;
}e[400050];
 
int head[100050],ecnt;
 
void adde(int u,int v,int w)
{
    e[++ecnt].v = v;
    e[ecnt].w = w;
    e[ecnt].nxt = head[u];
    head[u] = ecnt;
}
 
int N,M;
int l[200050],r[200050];
int d[200050];
long long dist[100005];
queue<int> que;
bool vis[100050],inq[100050];
 
bool spfa(int st)
{
    que.push(st);
    inq[st] = true;
    dist[st] = 0;
    long long curmax = 0,curmin = 0;
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        for(int i = head[u];i;i = e[i].nxt)
        {
            int v = e[i].v;
            if(dist[v] == 12345678987654321)
            {
                dist[v] = dist[u] + e[i].w;
                curmax = max(curmax,dist[v]);
                curmin = min(curmin,dist[v]);
                if(curmax - curmin > 1000000000)
                    return false;
                vis[v] = 1;
                if(!inq[v])
                    que.push(v);
            }
            else if(dist[v] != dist[u] + e[i].w)
                return false;
        }
        inq[u] = false;
    }
    return true;
}
 
int main()
{
    for(int i = 1;i <= 100000; ++ i)
        dist[i] = 12345678987654321;
    scanf("%d%d",&N,&M);
    for(int i = 1;i <= M; ++ i)
    {
        scanf("%d%d%d",&l[i],&r[i],&d[i]);
        adde(l[i],r[i],d[i]);
        adde(r[i],l[i],-d[i]);
    }
    for(int i = 1;i <= N; ++ i)
    {
        if(!vis[i])
        {
            vis[i] = 1;bool l = spfa(i);
            if(!l)
            {
                printf("No\n");
                return 0;
            }
        }
    }
    printf("Yes\n");
    return 0;
}
```

---

## 作者：lkjzyd20 (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/solution/AT3882)
___
### 思路

这道题很简单，就是纯 Dfs。

先建图，表示 $l$ 在 $r$ 的左边，距离为 $d$，$r$ 在 $l$ 的右边，距离为 $-d$。

再开一个 $f$ 数组，只要这个点没有访问过，就跑一遍 Dfs。

如果发现结果一个点有两个不同的坐标，输出 `No`，否则就输出 `Yes`，
___

代码如下：

```cpp
#include <bits/stdc++.h> 

using namespace std;

const int N = 2e7 + 10;

void add (int x, int y, int z) ;
void Ios () ;
void dfs (int x) ;

bool f[N];

int n, m;
int tot;
int pre[N], now[N], son[N], val[N];
int l[N], r[N], d[N];
int deep[N];

main () {
	Ios () ;
	
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		cin >> l[i] >> r[i] >> d[i];
		
        // 连边，表示 l 在 r 的左边，距离为 d，r 在 l 的右边，距离为 -d。
		add (l[i], r[i], -d[i]) ;
		add (r[i], l[i], d[i]) ;
	}
	
    // 只要这个点没有访问过，就跑一遍 Dfs。
	for (int i = 1; i <= n; ++ i)
		if (f[i] == 0)
			dfs (i) ;
	
    // 判断是否合法。
	for (int i = 1; i <= m; ++ i) 
		if (deep[r[i]] - deep[l[i]] != d[i]) {
			cout << "No\n" ;
			return 0; 
		}
	
	cout << "Yes \n" ;
}

void add (int x, int y, int z) { // 建图。
	pre[++ tot] = now[x];
	son[tot] =y;
	now[x] = tot;
	val[tot] = z;
}

void Ios () { // cin 加速。
	ios :: sync_with_stdio (0) ;
	cin.tie () ;
	cout.tie () ;
}

void dfs (int x) { // dfs
	f[x] = 1;
	
	for (int i = now[x]; i; i = pre[i]) {
		int y = son[i];
		if (f[y] == 0) {
			deep[y] = deep[x] - val[i];
			dfs (y) ;
		}
	}
}
```

### 完结撒花 $\sim\sim\sim$

---

## 作者：Error_666 (赞：1)

- 今天一天都是刷着差分约束的题来着

- 这一题，点进来，乍一看，好像是差分约束

- 其实的确是差分约束

- 但我觉得纯Dfs可行，于是敲了一发上去就A掉了

- 纯Dfs的思路很简单。就是先建图。add(a, b, c), add(b, a, -c)。表示b在a的右边，a在b的左边。然后只要没有访问过的点就以它为**基准点**去扩展Dfs。如果在Dfs的过程中发现一个点有两个**不同**的坐标。就直接输出No。

- 代码↓

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 400005
#define inf 0x7fffffff
using namespace std;

struct E {int next, to, dis;} e[N];
int n, m, num, flag, cnt;
int h[N], a[N], pos[N], obj[N];
bool vis[N];

int read()
{
	int x = 0; char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
	return x;
}

void add(int u, int v, int w)
{
	e[++num].next = h[u];
	e[num].to = v;
	e[num].dis = w;
	h[u] = num;
}

void dfs(int x)
{
	if(flag) return;
	vis[x] = 1;
	for(int i = h[x]; i != 0; i = e[i].next)
	{
		int t = pos[x] + e[i].dis;
		if(pos[e[i].to] == inf) pos[e[i].to] = t, dfs(e[i].to);
		else if(t != pos[e[i].to]) {flag = 1; return;}
	}
}

int main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read();
		add(a, b, c), add(b, a, -c);
		pos[a] = pos[b] = inf;
		obj[++cnt] = a, obj[++cnt] = b;
	}
	sort(obj + 1, obj + 1 + cnt);
	cnt = unique(obj + 1, obj + 1 + cnt) - obj - 1;
	for(int i = 1; i <= cnt; i++)
		if(!vis[obj[i]])
		{
			flag = 0;
			pos[obj[i]] = 0;
			dfs(obj[i]);
			if(flag) {cout << "No"; return 0;}
		}
	cout << "Yes";
	return 0;
}
```


---

## 作者：VectorChange (赞：0)

[点我传送至原题](https://www.luogu.com.cn/problem/AT3882)

[点我获得更好的阅读体验](https://www.luogu.com.cn/blog/includebits/solution-at3882)

让我们先翻译翻译题意：

- 给定一些人之间的距离，其中可能有一些关系相矛盾，判断是否有存在矛盾。

是不是还有点闷，让我们看下面一组样例：

```
3 3
1 2 1
2 3 1
1 3 5
```
图画出来就是下面的样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ewsfgsah.png)

可以看到，$1$ 到 $3$ 有两种走法，一种是经过 $2$ 到 $3$，还有一种是直接走到 $3$ ,这两种走法的路径长度是不一样的，但根据题意，两个人在数轴上的距离是唯一的，所以存在矛盾，这组样例输出的是 No.

现在理解题意了，让我们来分析一下这道题。

首先我们通过上述样例可以得知，这道题是求是否存在矛盾，我们在跑 Spfa 时，是不是会随时更新两个点之间的距离，但我们要看他是不是矛盾，只要我们在更新距离时，存在一条道路与原有的道路长不同，那么就一定存在矛盾。

但用给定我们的条件建图，不一定联通，所以我们应该把每个点都扫一遍，如果这个点在前面没跑，那么就跑一遍 Spfa.

最后放上 AC 代码（仅供参考）：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Maxm=400050;
const int Maxn=100050;
int n,m;
struct node {
	ll v,nxt,w;
} edge[Maxm];
int tot,head[Maxn];
ll dis[Maxn];
queue<int> q;
bool vis[Maxn],in[Maxn];

inline void Add_edge(ll u,ll v,ll w) {
	edge[++tot]=(node) {v,head[u],w};
	head[u]=tot;
}

inline bool Spfa(ll s) {
	q.push(s);
	dis[s]=0;
	in[s]=true;
	while(!q.empty()) {
		int now=q.front();
		q.pop();
		for(int i=head[now]; i; i=edge[i].nxt) {
			int v=edge[i].v;
			if(dis[v]>=0x7fffffff) {
				dis[v]=dis[now]+edge[i].w;
				vis[v]=true;
				if(!in[v]) q.push(v);
			} 
			else if(dis[v]!=dis[now]+edge[i].w)
				return false;
		}
		in[now]=false;
	}
	return true;
}

int main() {
	for(int i=1; i<=100005; ++i)
		dis[i]=12345678987654321;
	cin>>n>>m;
	for(int i=1,u,v,w; i<=m; ++i) {
		cin>>u>>v>>w;
		Add_edge(u,v,w);
		Add_edge(v,u,-w);
	}
	for(int i=1; i<=n; ++i) {
		if(!vis[i]) {
			vis[i]=true;
			if(!Spfa(i)) {
				puts("No");
				return 0;
			}
		}
	}
	puts("Yes");
	return 0;
}
```

---

