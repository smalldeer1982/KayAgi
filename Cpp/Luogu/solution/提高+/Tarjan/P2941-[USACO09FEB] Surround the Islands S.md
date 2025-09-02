# [USACO09FEB] Surround the Islands S

## 题目描述

Farmer John 在加勒比海购置了一片地产，准备在由一系列岛屿组成的农场上养奶牛。 出于他的意愿，他要把所有的岛屿都用篱笆围上。
每个岛都是多边形的。每一次，FJ 会给多边形的一个边（即相邻的两个顶点之间）装上篱笆。对于整个岛屿，他会按照顺时针顺序装上篱笆。由于他想要给所有的岛屿都装上篱笆，某些时候，他必须从一个岛屿坐船到另一个岛屿去。  
FJ 可以从任何一个顶点开始装篱笆，也可以从任何一个顶点坐船到另一个岛的某个顶点上，从这个顶点开始把该岛屿的篱笆全都装好，然后**马上**坐船原路返回。保证任意两个顶点间都有航线。在任意两个顶点之间坐船的费用会在一个矩阵中给出。  

所有的岛屿由给定的 $N$ 对顶点 $V_1$，$V_2$ 描述（即：给定顶点 $V_1$ 与 $V_2$ 相邻）。每个顶点具体属于哪个岛屿**不会**在输入中给出。所有顶点由 $1$ 到 $N$ 标号。  
在顶点间坐船旅行的费用由一个 $N \times N$ 的矩阵给出。保证两个岛屿间两个方向的旅行费用相等且不会超过 $1000$。   

请求出 FJ 把篱笆装完所需要的最小花费。

## 说明/提示

对于所有数据，保证：
+ $3 \leq N \leq 500$
+ $1 \leq V_1,V_2 \leq N$
+ 任意两个顶点之间的旅行花费 $\leq 1000$

## 样例 #1

### 输入

```
12 
1 7 
7 3 
3 6 
6 10 
10 1 
2 12 
2 9 
8 9 
8 12 
11 5 
5 4 
11 4 
0 15 9 20 25 8 10 13 17 8 8 7 
15 0 12 12 10 10 8 15 15 8 8 9 
9 12 0 25 20 18 16 14 13 7 12 12 
20 12 25 0 8 13 14 15 15 10 10 10 
25 10 20 8 0 16 20 18 17 18 9 11 
8 10 18 13 16 0 10 9 11 10 8 12 
10 8 16 14 20 10 0 18 20 6 16 15 
13 15 14 15 18 9 18 0 5 12 12 13 
17 15 13 15 17 11 20 5 0 22 8 10 
8 8 7 10 18 10 6 12 22 0 11 12 
8 8 12 10 9 8 16 12 8 11 0 9 
7 9 12 10 11 12 15 13 10 12 9 0 
```

### 输出

```
30 
```

# 题解

## 作者：BriMon (赞：17)

第一个题解诶！

想要食用效果更佳[戳这里](http://www.cnblogs.com/zZh-Brim/p/9029310.html)

其实就是暴力；

可能是因为看不懂题才没做；

一看样例就不想做系列；并没有好好看样例；

大致看了一下分的岛屿

![](https://images2018.cnblogs.com/blog/1354256/201805/1354256-20180512171840291-1236067146.png)


大概是这个样子的，然后每个点之间都有一些连线表示之间是通路，每条路都有一个权值；


其实仔细想想，既然在每个岛屿中行走不算进总花费，那么可以进行一波缩点，我是用并查集维护，直接求出每个联通块；

这样，我们就把一堆点，抽象成了一堆互不联通的块；

这时再加边劝，在每一个联通块内，任何 一个点向外的连线都可看做是这个联通块向外连得线， 这样， 我们把每一个联通块向外的边的权值最小记录下来，当做这个联通块向外的边；

所以，我们只要枚举从哪一个联通块开始出发，把这个联通块与其他联通块的边权和加起来取min再乘2就是答案；


代码奉上：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
#define regi register 

int n;

int fa[505];

inline int Find(int x)
{
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

int dis[505][505];

int cnt;

int ans = 0x7f7f7f7f;

int pos[505];

int main()
{
    cin >> n;
    
    for (regi int i = 1 ; i <= n ; i ++) fa[i] = i;
    
    memset(dis, 0x7f, sizeof dis);
    
    for (regi int i = 1 ; i <= n ; i ++){
        int x, y;
        scanf("%d%d", &x, &y);
        int fx = Find(x), fy = Find(y);
        if (fx != fy) fa[fx] = fy;
    }
    
    for (regi int i = 1 ; i <= n ; i ++){
        if (fa[i] == i) pos[++cnt] = i;
    }
    
    for (regi int i = 1 ; i <= n ; i ++){
        int fi = Find(i);
        for (regi int j = 1 ; j <= n ; j ++){
            int fj = Find(j);
            int d;
            scanf("%d", &d);
            dis[fi][fj] = min(dis[fi][fj], d);            
        }
    }
    
    for (regi int i = 1 ; i <= cnt ; i ++){
        int sum = 0;
        for (regi int j = 1 ; j <= cnt ; j ++){
            if (i == j) continue;
            sum += dis[pos[i]][pos[j]];
        }
        ans = min(ans, sum);
    }
    
//    printf("dis==%d\n", dis[4][10]);
    
    cout << ans * 2 << endl;
    
    return 0;
}

zZhBr
```

---

## 作者：隐隐约约妖艳 (赞：9)

~~好多大佬用TJ，蒟蒻用不来~~  
#### 直接搜索就好了呀 
因为顶点相连就是一个岛，直接找一下岛并找一下每个岛之间的最短距离。  
找到之后因为每个点都相连，直接双重for就行
因为去了其他岛要回来，就不存在最短路  
最后记得*2


------------
上代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m[501][501],ans;//m是存的每个点的距离 
int num,f[501],ne[1001],to[1001];//邻接表存储 
void add(int a,int b)//邻接表添加 
{
	ne[++num]=f[a];
	f[a]=num;
	to[num]=b;
}
int sa[501][501],s[501],v[501];
//sa为每个岛之间的最短距离，s为每个点属于哪个岛，v是标记这个点有没有被找过 
void dfs(int u)//找岛 
{
	if(v[u])//如果找过 
		return;
	s[u]=num;//标记为某个岛 
	v[u]=1;
	for(int i=f[u];i!=0;i=ne[i])//邻接表查找 
	{
		int w=to[i];
		if(!v[w])//如果没找过 
		{
			dfs(w);
		}
	}
}
int main()
{

scanf("%d",&n);
for(int i=1;i<=n;i++)
{
	int x,y;
	scanf("%d%d",&x,&y);
	add(x,y);
	add(y,x);
}
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		scanf("%d",&m[i][j]);
//输入不解释 

num=0;//岛的标号及数量 
for(int i=1;i<=n;i++)
	if(!v[i])//如果没找过 
	{
		num++;
		dfs(i);
	}

for(int i=1;i<=num;i++)
	for(int j=1;j<=num;j++)
		sa[i][j]=999999999;//初始化 

for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)//找每个岛之间的距离 
	if(s[i]!=s[j])//同岛距离为零 
	{
		sa[s[i]][s[j]]=min(sa[s[i]][s[j]],m[i][j]);
	}
	else
		sa[s[i]][s[j]]=0;

ans=99999999;//初始化 
for(int i=1;i<=num;i++)//暴力枚举每个岛 
{
	int ss=0;
	for(int j=1;j<=num;j++)//枚举距离 
		ss+=sa[i][j];
	//同岛距离为零，不影响 
	ans=min(ans,ss);
}
cout<<ans*2;//往返是两次距离 

return 0;
}
```


------------
代码有点长，但想起来简单  
求赞QwQ

---

## 作者：Shikita (赞：8)

题目大意：给定n个点，求一条遍历所有点的最短路径

已知题目中所说的不同岛屿，易得为不同联通块，即 将每个岛屿缩成一个点

然后求一个最小生成树（其实没有必要写）

其实就是一个缩点的板子题吧。。。

本题说一条路径要走来回两次，所以最后答案需要$*2$

code

```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9') {if(c=='-')flag=1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+ c-'0';c=getchar();}
    return flag?-x:x;
}
const int N=5005;
int n,step,tcl,ans=1e9+7; 
vector<int>G[N];
vector<int>cg[N];
int dfn[N],vis[N],col[N],low[N];
stack<int>s;
int d[N][N];
inline void tarjan(int now)
{
	vis[now]=1;
	s.push(now);
	low[now]=dfn[now]=++step;
	for(int i=0;i<G[now].size();++i)
	{
		int to=G[now][i];
		if(!dfn[to])
		{
			tarjan(to);
			low[now]=min(low[now],low[to]);
		}
		else if(vis[to]) low[now]=min(low[now],dfn[to]);
	}
	if(dfn[now]==low[now])
	{
		col[now]=++tcl;
		vis[now]=0;
		while(1)
		{
			int x=s.top();s.pop();
			col[x]=tcl;
			vis[x]=0;
			if(now==x) break;
		}
	}
}//板子
int main()
{
	n=read();
	for(int i=1;i<=n;++i) 
	{
		int x=read(),y=read();
		G[x].push_back(y),G[y].push_back(x);
	}//双向边
	for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
	memset(d,0x3f3f,sizeof(d));//初始化（我就是忘记然后挂了一次）
	for(int i=1;i<=n;++i)
	{
	  for(int j=1;j<=n;++j) 
	  {
	  	int x=read();
	  	if(i==j) continue;
	  	d[col[i]][col[j]]=min(d[col[i]][col[j]],x);
	  }
	}
	for(int i=1;i<=tcl;++i)
	{
		int res=0;
		for(int j=1;j<=tcl;++j) if(i!=j) res+=d[i][j];
		ans=min(ans,res);
	}//暴力枚举答案
	printf("%d\n",ans*2);
}
```

---

## 作者：GTAyin (赞：3)

## **题意分析**

其目的是将点归并在一起，使用缩点求出小岛个数，再在小岛之间暴力枚举，求出距离最小值。
具体分析在代码里有注释，希望对你们有所帮助。

## **code**

```c
#include<iostream>
#include<cstdio>
const int N=1010,inf=99999999;
using namespace std;
struct node {
	int to,nex;
} e[N];
int head[N],tot,ans=inf;
int low[N],dfn[N],viz[N],index,n;
int color[N],col;//col表示缩点之后岛的编号，color[i]=col表示第i个点属于col这个岛 
int stack[N],top;
int d[N][N];//表示两个岛之间的最短距离 
void add(int u,int v) {
	e[++tot].to=v;
	e[tot].nex =head[u];
	head[u]=tot;
}
void tarjan(int x) {
	low[x]=dfn[x]=++index;
	viz[x]=true;
	stack[++top]=x;
	for(int i=head[x]; i; i=e[i].nex) {
		int v=e[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[x]=min(low[x],low[v]);
		} else if(viz[v]) {
			low[x]=min(low[x],low[v]);
		}
	}
	if(dfn[x]==low[x]) {
		int y;
		col++;//每次能够缩点时，就要新开一个岛 
		while(y=stack[top--]) {
			viz[y]=false;
			color[y]=col;//每个缩点计划里的点都属于这个岛 
			if(x==y) break;
		}
	}
}
int main() {
	cin>>n;
	int x;
	for(int i=1; i<=n; i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);//双向建边（刚开始把我卡住了） 
	}
	for(int i=1; i<=n; i++) if(!dfn[i]) tarjan(i);// tarjan模板 
	for(int i=1; i<=col; i++) {
		for(int j=1; j<=col; j++) d[i][j]=inf;//初始化，因为取最小值，所以开始就赋最大值 
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cin>>x;
			if(i==j) continue;//自己不能赋值,因为为零 
			d[color[i]][color[j]]=min(d[color[i]][color[j]],x);/*
			color[i]表示i所属小岛，color[j]同理，
			 d[color[i]][color[j]]表示i所属小岛到j所属小岛的最短距离。 
			*/ 
		}
	}
	for(int i=1; i<=col; i++) {//枚举小岛个数 
		int sum=0;
		for(int j=1; j<=col; j++) if(j!=i)sum+=d[i][j];//枚举联通的岛，自己不能到自己 
		ans=min(sum,ans);//取最小值 
	}
	cout<<ans*2;//原路返回，所以ans*2; 
	return 0;
}
```


完结撒花（留个赞呗）


---

## 作者：nao_nao (赞：3)

[这道题](https://www.luogu.com.cn/problem/P2941)并不是特别复杂，~~或许是翻译不清？~~

### 题意+分析：

约翰需要给每个岛围上围栏，他从一个顶点出发进行修建工作，他可以从任意顶点出发前往任意的另一个岛屿并且修建好那个岛上的围栏，然后立即返回。也就是说：**约翰不能从起始岛航行到下一个岛，然后再前往另一个岛。**

如果我们将所有的航线画出来，那么将会发现它是一棵树，并且深度为$2$，起始岛为根节点，其它的岛都是根的儿子。**（所以这并不是最小生成树）**

### 题解：

输入数据并没有告诉我们有哪些岛，只告诉了我们顶点对，通过样例解释我们可以知道，顶点对表示的是一个岛上的相邻顶点。我们可以将顶点对间连一条边，会形成多个连通块，每一个连通块就是一座岛。所以有没有想到什么？**我们不用连边，只需要并查集就足以维护出连通块！**

然后我们再看那个~~辣么大~~的矩阵，我们就可以将顶点与顶点间连的边转化为岛与岛之间的航线。我们也使用矩阵存边，将岛与岛之间最短的航线记录下来（$arr[i][j]$ $=$ $min$($arr[i][j]$,$tmp$)）

接下来的操作非常简单~~粗暴~~：我们枚举每一个岛作为出发点，求取此时的答案，然后更新最后的结果。($ans$ $=$ $min$($ans$,$tmp$))

$code:$

```#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=1e3+7,inf = 2e9+7;;
int n;
int fa[N],coloffa[N],cnt = 0,col[N];
int arr[N][N];

inline int find(int a)//并查集 
{
	if(fa[a] == a) return a;
	return fa[a] = find(fa[a]);
}

void in_it()
{
	//处理岛 
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++) fa[i] = i;//并查集预处理 
	
	for(int i = 1;i <= n;i ++){
		int v1,v2;
		scanf("%d %d",&v1,&v2);
		if(find(v1) != find(v2)){
			fa[find(v1)] = v2;//连边 
		}
	}
	
	//此处是将连通块边号整理一下，方便使用 
	for(int i = 1;i <= n;i ++){
		if(!coloffa[find(i)]) coloffa[find(i)] =++cnt;
	}
	
	for(int i = 1;i <= n;i ++){
		col[i] = coloffa[find(i)];
	}
	//此时连通块数 = cnt
	
	//预处理航线长度 
	for(int i = 1;i <= cnt;i ++)
		for(int j = 1;j <= cnt;j ++)
			arr[i][j] = inf;
	
}



int main()
{
	in_it();//预处理
	
	//处理航线 
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++){
			int tmp;
			scanf("%d",&tmp);
			if(col[i]==col[j]) continue;//如果在一个岛上，不用坐船，走就完了 
			arr[col[i]][col[j]] = min(arr[col[i]][col[j]],tmp);//更新航线长度 
		}
	}
	
	int tmp = 0,ans = inf;
	
	for(int i = 1;i <= cnt;i ++){//枚举出发岛 
		tmp = 0;//tmp清零预备 
		for(int j = 1;j <= cnt;j ++){
			if(i == j) continue;//当然不用自己坐船到自己，跳过！ 
			tmp += arr[i][j];
		}
		ans = min(ans,tmp);//更新ans 
	}
	printf("%d",ans*2);//每个航线有去一次，回一次，一个来回所以答案乘以二 
	return 0;
}
```
### 写在最后：

因为每个岛为了围围栏，都要转一圈，因此对于出发岛来说，前往别的岛屿再返回到原位置，不会对出发岛产生影响，~~就像什么也没发生~~，对于别的岛，从任何一点开始修围栏都可，因此我们在处理航线时可以忽略掉顶点的不同，而只考虑岛。

---

## 作者：pldzy (赞：0)

[P2941 [USACO09FEB]Surround the Islands S 传送门](https://www.luogu.com.cn/problem/P2941)

~~感觉其他有些题解有点简略，wtcl，一开始理解不了题意，我现在就写篇详细点点的吧。~~

## 题目分析

- 我们最开始输入的 $n$ 条边 $(u,v)$ 都是可以直接以 0 费用从 u 到 v 的。

	也就是题目中的走路，**即 u 和 v 是同一岛上的不同顶点**。

- 接着输入的是从第 i 个点乘船到达其他 i（包括 i 点自己）所需要的费用。

## 求解

概述：为了保证最小费用，我们当然是走路到达同一岛上的点，乘船到达不同岛上的点。

**不同岛：开始没有给出连边的两个点。**

 _1. 既然已经确定了我们只会把费用花在乘船上，那我们怎么最小化乘船费用呢？_ 
 
我们可以**选择两岛中相隔近的两顶点作为当前到达两岛的出发点以及终点**。

相隔近，也就是费用小。

所以我们可以开数组记录两岛之间，到达所需的费用，这样，我们最后只需要统计看看哪个岛到其他岛的总费用最小，输出总费用的两倍（题中说了要往返）即可。

 _2. 如何确定岛？_ 
 
 我们已知岛上任意两点可以互相到达（0 费用），任意两岛不可直接互达（需要花费钱）。
 
 那这不就是[强联通分量（算法笔记）](https://469672.blog.luogu.org/solution-b3609)吗？
 
 在任意一个强连通分量中，任意两点我们可以 0 费用到达。所以我们只需要在最开始输入边的时候建边，然后跑一边 Tarjan，确定所有岛即可。
 
**注意建边要双向边，因为岛上任意两顶点是互达的。**

## 代码（更多细节见代码）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 505;
int n, m;
int cnt, hd[maxn];
struct node{
	int to, nxt;
}e[maxn * 2]; 
int dfn[maxn], low[maxn];
int tmp, top;
int st[maxn];
int co[maxn], col;
bool vis[maxn];
int ans;

void add (int u, int v)
{
	e[++cnt].to = v;
	e[cnt].nxt = hd[u];
	hd[u] = cnt;
}

void tarjan (int u)//跑 Tarjan 确定岛 
{
	dfn[u] = low[u] = ++tmp;
	st[++top] = u;
	for (int i = hd[u]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (!dfn[v])
		{
			tarjan (v);
			low[u] = min (low[u], low[v]);
		}
		else if (!co[v]) low[u] = min (low[u], dfn[v]);
	}
	if (low[u] == dfn[u])
	{
		co[u] = ++col;
		while (st[top] != u)
		{
			co[st[top]] = col;
			top--;
		} 
		top--;
	}
}

int dis[maxn][maxn];

signed main ()
{
	scanf ("%d", &m);
	for	(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf ("%d %d", &u, &v);
		add (u, v), add (v, u);//双向建边 
		n = max (n, max (u, v));
	}
	for (int i = 1; i <= n; i++)
	{
		if (!dfn[i]) tarjan (i);
	}
	for(int i = 1; i <= col; i++) 
	for(int j = 1; j <= col; j++) dis[i][j] = 2147483647;//记得要初始化 
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
	{
		int t;
		scanf ("%d", &t);
		dis[co[i]][co[j]] = min (dis[co[i]][co[j]], t);//两岛间到达所需最小的费用 
	}
	ans = 2147483647;
	for (int i = 1; i <= col; i++)
	{
		int res = 0;
		for (int j = 1; j <= col; j++)
		{
			if (i == j) continue;
			res += dis[i][j]; 
		}
		ans = min (ans, res);//统计答案 
	}
	printf ("%d\n", ans * 2);//往返 
	return 0;
}
```

感谢阅读题解 ~~（啊求赞）~~ ~

如有问题求大佬斧正。

---

## 作者：Marginal_world (赞：0)

题意分析：其实这题本身不难，大部分同学是被翻译和可怕的样例逼退了。整体来说，理解题目之后，实际上就是一个缩点。

思路历程：既然在每个岛屿中行走不算进总花费，那么可以进行一波缩点，直接求出每个连通块。

这样，我们就把一堆点，抽象成了一堆互不连通的块。

然后，就是模板啦。记得最后答案要乘以二。

代码：

```cpp
#include<bits/stdc++.h>
const int N=1010,inf=99999999;
using namespace std;
struct node {
	int to,nex;
} e[N];
int head[N],tot,ans=inf;
int low[N],dfn[N],viz[N],time1,n;
int color[N],col;//col表示缩点之后岛的编号，color[i]=col表示第i个点属于col这个岛 
int d[N][N];//表示两个岛之间的最短距离 
stack<int> q;
void add(int u,int v) {
	e[++tot].to=v;
	e[tot].nex =head[u];
	head[u]=tot;
}
void tarjan(int x) {
	low[x]=dfn[x]=++time1;
	q.push(x);
	for(int i=head[x]; i; i=e[i].nex) {
		int v=e[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[x]=min(low[x],low[v]);
		} else if(!color[v]) {
			low[x]=min(low[x],dfn[v]);
		}
	}
	if(dfn[x]==low[x]) {
		col++;//每次能够缩点时，就要新开一个岛 
		while(1) {
			int v=q.top();
			q.pop();
			color[v]=col;//每个缩点计划里的点都属于这个岛 
			if(x==v) break;
		}
	}
}
int main() {
	cin>>n;
	int x;
	for(int i=1; i<=n; i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1; i<=n; i++) if(!dfn[i]) tarjan(i);// tarjan模板 
	for(int i=1; i<=col; i++) {
		for(int j=1; j<=col; j++) d[i][j]=inf;//初始化，因为取最小值，所以开始就赋最大值 
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cin>>x;
			if(i==j) continue;//自己不能赋值,因为为零 
			d[color[i]][color[j]]=min(d[color[i]][color[j]],x);/*
			color[i]表示i所属小岛，color[j]同理，
			 d[color[i]][color[j]]表示i所属小岛到j所属小岛的最短距离。 
			*/ 
		}
	}
	for(int i=1; i<=col; i++) {//枚举小岛个数 
		int sum=0;
		for(int j=1; j<=col; j++) if(j!=i)sum+=d[i][j];//枚举联通的岛，自己不能到自己 
		ans=min(sum,ans);//取最小值 
	}
	cout<<ans*2;//原路返回，所以ans*2; 
	return 0;
}
```


---

## 作者：Ink_Render (赞：0)

## 一、题目大意

[题目传送门](https://www.luogu.com.cn/problem/P2941)

其实这道题真的不难，但讲实话题意十分的模糊。~~我第一次看的时候也理解错了~~

分析题目，我们可以了解到：这是一个有 $n$ 个点的图，其中会有一些 **独立** 的环（这一点很重要），任意两个点之间都会有长度，同一个环的两点之间的代价为 0 。

所以，我们可以把每个环缩成一个点，然后用最小生成树计算总最小代价。

但是，这个题目最大的坑点在于：题目中说 **"但修完那个岛的篱笆，他必须马上原路返回这个出发的岛屿顶点"** ，指的是从起始点出发后必须要直接修完这个岛的篱笆，然后直接返回（中途不能去其他岛屿），这也就意味着这个图一定是一个菊花图！！！（不懂的童鞋自己去百度优先搜索）

修改思路，可以枚举菊花图的中心，直接计算即可。

**ps :因为去了还要回来，答案记得乘2。**

## 二、实现方法

本蒟蒻在题解区里看到很多大佬使用了 Tarjan 缩点。然而，我们仔细思考一下， Tarjan 的使用是为了保证缩点之后还可以与原图相连，而我们刚刚分析题意时已经知道了，各个环之间是互不连通的，所以说我们可以使用一种更为简单直接的办法：并查集。

直接将在同一个环内的点并入同一个集合，最后再进行重新编号即可

```
  int find(int x)
  {
      return fa[x]==x?x:fa[x]=find(fa[x]);
  }
  for(int i=1;i<=n;i++)
      fa[i]=i;
  for(int i=1;i<=n;i++)
  {
	int x,y;
		scanf("%d%d",&x,&y);
		if(x>y) swap(x,y);
		int xx=find(x),yy=find(y);
		if(xx!=yy) fa[xx]=yy;
	}
	for(int i=1;i<=n;i++)
	{
		int x=find(i);
		if(!ord[x])
		{
			col[i]=++sum;
			ord[x]=sum;
		}
		else col[i]=ord[x];
	}
```

重新编号后，我们可以查找所有原来的边，用一个二维数组直接找到两个新编号之间的长度。

```
memset(mapp,0x7f,sizeof mapp);
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		int x;
		scanf("%d",&x);
		if(i==j) continue;
		mapp[col[i]][col[j]]=min(mapp[col[i]][col[j]],x);
        }
```

最后，枚举菊花图中心。

```
ans=INF;
	for(int i=1;i<=sum;i++)
	{
		int now=0;
		for(int j=1;j<=sum;j++)
		{
			if(j==i) continue;
			now+=mapp[i][j];
		}
		ans=min(ans,now);
	}
```

## 三、完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,INF=2139062143;
int n,sum,ans;
int fa[N],col[N],ord[N],mapp[N][N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(x>y) swap(x,y);
		int xx=find(x),yy=find(y);
		if(xx!=yy) fa[xx]=yy;//并查集  
	}
	for(int i=1;i<=n;i++)//旧编号  
	{
		int x=find(i);
		if(!ord[x])//第一次搜到这个新编号  
		{
			col[i]=++sum;//新编号  
			ord[x]=sum;
		}
		else col[i]=ord[x];
	}
	memset(mapp,0x7f,sizeof mapp);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			int x;
			scanf("%d",&x);
			if(i==j) continue;
			mapp[col[i]][col[j]]=min(mapp[col[i]][col[j]],x);//用原边计算缩点后的边 
		}
	ans=INF;
	for(int i=1;i<=sum;i++)//枚举菊花图中心  
	{
		int now=0;
		for(int j=1;j<=sum;j++)
		{
			if(j==i) continue;
			now+=mapp[i][j];
		}
		ans=min(ans,now);
	}
	printf("%d",ans<<1);
	return 0;
}
```

---

