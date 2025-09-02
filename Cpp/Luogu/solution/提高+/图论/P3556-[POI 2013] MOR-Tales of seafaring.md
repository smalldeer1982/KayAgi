# [POI 2013] MOR-Tales of seafaring

## 题目描述

Young Bytensson loves to hang out in the port tavern, where he often    listens to the sea dogs telling their tales of seafaring.

Initially, he believed them all, however incredible they sounded.

Over time though, he became suspicious.

He has decided to write a program that will verify if there may be    any grain of truth in those tall stories.

Bytensson reasoned that while he cannot tell if the sailors indeed    weathered all those storms, he can at least find out if their travel    itineraries make sense.

This is a task for a programmer, which Bytensson, unfortunately, is not.

Help him out!

There are $n$ ports and $m$ waterways connecting them in the waters    frequented by the sailors Bytensson listened to.

If there is a waterway between two ports, then sailing from one to the    other is possible.  Any waterway can be sailed in both    directions.

Bytensson got to know $k$ seafaring tales.

Each tells of a sailor who began his journey in one port,    sailed a number of waterways, and ended up in another port,    which may have been the one he initially set sail from.

The sailor in question may have sailed through the same waterway    many times, each time in any direction.

给n个点m条边无向图，每次询问两个点之间是否有长度为d的路径（不一定是简单路径）


## 说明/提示

给n个点m条边无向图，每次询问两个点之间是否有长度为d的路径（不一定是简单路径）


## 样例 #1

### 输入

```
8 7 4
1 2
2 3
3 4
5 6
6 7
7 8
8 5
2 3 1
1 4 1
5 5 8
1 8 10
```

### 输出

```
TAK
NIE
TAK
NIE
```

# 题解

## 作者：liangbowen (赞：34)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/P3556)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16991082.html)

最短路应用。内容抄自某校课件。

## 思路

首先想到题目与最短路有关。

假如 $a$ 到 $b$ 的最短路径长度是 $x$，那么对于一个询问是否存在长度为 $d$ 的路径：

+ 如果 $x$ 和 $d$ 同奇偶，且 $d \ge x$，那么这个长度为 $d$ 的路径一定存在。

	因为可以从 $a$ 走 $x$ 步到 $b$，然后走两步在 $b$ 与它相邻的点左右横跳，直到走的步数为 $d$。

+ 但是如果 $x$ 与 $d$ 不同奇偶，路径就一定不存在吗？

考虑下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/n38a0t42.png)

随便两个点，奇偶的路径都是合法的。

那么容易想到，我们可以维护从 $a$ 到 $b$ 的**偶数步最短路径**长度和**奇数步最短路径**长度。这一点显然可以用 Dijkstra 搞出来。

然后我们根据 $d$ 的奇偶，判断对应的 $a$ 到 $b$ 的最短路径长度是否存在，存在的话并且长度小于等于 $d$，那么长度为 $d$ 的路径就可以被构造出来。

于是这题就差不多结束了。

---

但是还有一组恶心的特判：

```
3 1 1
1 2
3 3 2
```

如果一个点是**孤立**的，那么怎么走都无解！

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int N = 5005, K = 1e6 + 5;
struct Edge {int now, nxt;} e[N << 1];
int head[N], cur;
void add(int u, int v)
{
	e[++cur].now = v, e[cur].nxt = head[u];
	head[u] = cur;
}
int dis[N][2]; //分奇偶
bool inque[N];
void spfa(int s)
{
	memset(dis, 0x3f, sizeof dis);
	memset(inque, false, sizeof inque);
	queue <int> q;
	q.push(s), inque[s] = true, dis[s][0] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop(), inque[u] = false;
		for (int i = head[u]; i; i = e[i].nxt)
		{
			int v = e[i].now;
			if (dis[u][0] + 1 < dis[v][1])
			{
				dis[v][1] = dis[u][0] + 1;
				if (!inque[v]) inque[v] = true, q.push(v);
			}
			if (dis[u][1] + 1 < dis[v][0])
			{
				dis[v][0] = dis[u][1] + 1;
				if (!inque[v]) inque[v] = true, q.push(v);
			}
		}
	}
}
struct Query {int id, v, w;};
vector <Query> query[N];
bool ans[K];
int main()
{
	//ios::sync_with_stdio(false);
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	while (m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for (int i = 1; i <= k; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		query[u].push_back((Query){i, v, w});
	}
	for (int u = 1; u <= n; u++)
		if (!query[u].empty() && head[u]) //特别注意！如果这个点是孤立的，怎么走都是无解
		{
			spfa(u);
			for (Query t : query[u]) ans[t.id] = (t.w >= dis[t.v][t.w & 1]);
		}
	for (int i = 1; i <= k; i++)
		if (ans[i]) puts("TAK"); else puts("NIE");
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Blunt_Feeling (赞：13)

## P3556 [POI2013]Tales of seafaring 题解

### 题意

这是一道最短路的简单变形。

给你一个含有 $n$ 个点 $m$ 条边无向图，每次询问两个点之间是否有长度为 $d$ 的路径（不一定是简单路径）。

### 思路

不一定是简单路径，即意味着可以多次经过同一个点，所以联想到找一条最短路径，将多余的路程在最后经过的那条边上来回跑以消耗掉。设一次询问为 $\{u,v,d\}$，因此，一种简单的想法是，只要 $d$ 大于等于 $u$ 到 $v$ 的最短路径，且 $d$ 的奇偶性与最短路径的奇偶性相同，即可做出判断。**然而，这样想显然是错的。**

![](https://cdn.luogu.com.cn/upload/image_hosting/mpwxovof.png)

在这张图中，从点 $1$ 到点 $2$，有 $2$ 条路径，奇数路径为 $3$，偶数路径为 $2$，显然 $\forall d\ge 2$，都是可以的。所以，我们要分别求 $u$ 到 $v$ 的奇数最短路径和偶数最短路径。

因为 $k$ 的值非常大，$n$ 又非常小，为了不 TLE，可以将询问离线，枚举 $s=1\sim n$ 跑 SPFA，一次性将 $s$ 有关的询问全解决掉，~~混个[最优解](https://www.luogu.com.cn/record/list?pid=P3556&orderBy=1&status=&page=1)~~。

### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
	char c=getchar();int x=0;bool f=0;
	for(;!isdigit(c);c=getchar())f^=!(c^45);
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	if(f)x=-x; return x;
}
const int maxn=5050;
int n,m,k,dis[2][maxn];
vector<int> g[maxn];
typedef pair<int,int> P;
#define fi first
#define se second
vector<pair<P,int>> qwq[maxn]; //存储询问，依次为{{v,d},i}
bool ans[1000050];
bool inq[maxn];
queue<int> que;
void spfa(int s)
{
	memset(dis,0x3f,sizeof(dis));
	que.push(s);
	inq[s]=true;
	dis[0][s]=0;
	while(!que.empty())
	{
		int u=que.front();
		que.pop(); inq[u]=false;
		for(auto v:g[u])
		{
			if(dis[0][v]>dis[1][u]+1) //由奇数->偶数
			{
				dis[0][v]=dis[1][u]+1;
				if(!inq[v])
				{
					inq[v]=true;
					que.push(v);
				}
			}
			if(dis[1][v]>dis[0][u]+1) //由偶数->奇数
			{
				dis[1][v]=dis[0][u]+1;
				if(!inq[v])
				{
					inq[v]=true;
					que.push(v);
				}
			}
		}
	}
}
int main()
{
	n=read(); m=read(); k=read();
	while(m--)
	{
		int u=read(),v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	For(i,1,k)
	{
		int u=read();
		qwq[u].push_back({{read(),read()},i});
	}
	For(s,1,n)
	{
		if(qwq[s].empty()||g[s].empty()) continue;
		spfa(s);
		for(auto q:qwq[s])
			if(q.fi.se>=dis[q.fi.se%2][q.fi.fi])
				ans[q.se]=true;
	}
	For(i,1,k) puts(ans[i]?"TAK":"NIE");
	return 0;
}
```

---

## 作者：Cylete (赞：8)

给n个点m条边无向图，每次询问两个点之间是否有长度为d的路径（不一定是简单路径）

因为不一定简单路径，且路径长度都为1

所以可以x->y,y->x（即来回走）

判断d的奇偶性，大于最短路径即可

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define next net
#define N 222222
int n,m,k;
int cut,head[N],next[N<<1],ver[N<<1];//前向星 
int dis[2][N],book[N];//dis[0][x]：长度为偶数  dis[1][x] ：长度为奇数 
bool ans[10000010];//每个问题的答案 
vector<int>qwq[N];//qwq[x][y]： x：从x出发 y：y个从x出发的问题    qwq[x][y]:第几个从x出发的问题 
//这个是为了减少搜索次数 
struct node{
	int x,y,z;
}e[N];
void add(int x,int y){
	ver[++cut]=y;next[cut]=head[x];head[x]=cut;
}
void spfa(int s){//搜索 
	memset(dis,0x3f,sizeof(dis));
	sizeof(book,0,sizeof(book));
	queue<int>q;
	q.push(s);
	dis[0][s]=0;
	while(!q.empty()){
		int x=q.front(),kkk=0;
		q.pop();
		book[x]=0;
		for(int j=head[x];j;j=next[j]){
			int y=ver[j];
			if(dis[0][x]!=dis[0][0]){
				if(dis[1][y]>dis[0][x]+1){
					dis[1][y]=dis[0][x]+1;
					kkk=1;
				}
			}
			if(dis[1][x]!=dis[0][0]){
				if(dis[0][y]>dis[1][x]+1){
					dis[0][y]=dis[1][x]+1;
					kkk=1;
				}
			}
			if(kkk&&!book[y]){
				q.push(y);
				book[y]=1; 
			}
		}
	} 
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){//存边 
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=k;i++){
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
		qwq[e[i].x].push_back(i);//储存问题编号 
	}
	for(int i=1;i<=n;i++){
		if(qwq[i].empty())continue;
		spfa(i);//search 
		for(int j=0;j<qwq[i].size();j++){
			int o=qwq[i][j];//第几个问题 
			int num=e[o].z%2;//长度奇偶 
			if(e[o].z>=dis[num][e[o].y]/*大于最短路径*/&&head[i]/*有边*/)ans[o]=1;
		}
	} 
	for(int i=1;i<=k;i++){
		if(ans[i])printf("TAK\n");
		else printf("NIE\n");
	}
    return 0;
}
```


---

## 作者：wuzhaoxin (赞：8)

85pt Hack:
```text
1 0 2
1 1 0
1 1 2
```
```text
TAK
NIE
```

# 拆点+广搜

首先看到每条边无向且权值为1，那么如果 x 到 y 的最短路为 dis ，则一定存在一条 x 与 y 之间的长度为 $2 \times k + dis$ 的路径

所以我们只需要把每个点拆成两个，分别表示到这个点且路径长度为奇数（偶数）的最短路径长度，这个可以对每个表示偶数的点开始广搜的出，再加上几个特判就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int gi() {
	register int x,op=1,c;
	while(c=getchar(),c<'0'||c>'9')if(c=='-')op=-op;
	x=c^48;
	while(c=getchar(),c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48);
	return x*op;
}
int head[10001],nxt[200001],ver[200001],tot=0;
void add(int x,int y) {
	ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
	ver[++tot]=x,nxt[tot]=head[y],head[y]=tot;
}
queue<int>q;
int n,m,k;
short dis[5001][10001]={0};
void bfs(int x) {
	dis[x][x]=1;
	q.push(x);
	while(!q.empty()) {
		int t=q.front();
		q.pop();
		for(int i=head[t];i;i=nxt[i])
			if(!dis[x][ver[i]])
				dis[x][ver[i]]=dis[x][t]+1,q.push(ver[i]);
	}
}
int main() {
	n=gi(),m=gi(),k=gi();
	for(int i=1,x,y;i<=m;i++)
		x=gi(),y=gi(),add(x+n,y),add(x,y+n);
	for(int i=1;i<=n;i++)if(head[i])bfs(i);
	int x,y,p;
	while(k--) {
		x=gi(),y=gi(),p=gi();
		if(x==y&&!p) { puts("TAK");continue;}
		int d=dis[x][y+n*(p&1)]-1;
		puts(d>=0&&p>=d?"TAK":"NIE");
	}
	return 0;
}
```

---

## 作者：kczno1 (赞：8)

由于边权为1又可以反复走，所以我们只用求出和d奇偶性相同的最短路即可。

预处理两两间的最短路，由于可以枚举起点后广搜，所以时间O(nm)。

询问可以O(1)回答。

128MB的空间，用short可以n\*n\*2\*2=100MB存下。。

但是我们可以离线，枚举起点bfs后顺便解决询问，这样空间就只用O(n+k)了。


---

## 作者：do_while_true (赞：4)

给 $n$ 个点 $m$ 条边无向图，每次询问两个点之间是否有长度为 $d$ 的路径（不一定是简单路径）

[题目链接](https://www.luogu.com.cn/problem/P3556)

### 题意分析

注意题目中的 “**（不一定是简单路径）**”，也就是说可以在一条边重复走多次，也就是可以在两个点之间**反复横跳**

反复横跳意味着什么，如果从 $s$ (起点)走到 $t$ (终点)如果没有 $d$ 那么长，比 $d$ 要短，可以在最后两个点不断来回重复走，使路径 $=d$ ，但是要注意一点，反复横跳每次都会把路径长度 $+2$，所以 $s$ 走到 $t$ 的路径必须是和 $d$ **奇偶性相同**，我们只需要求出 $s$ 到 $t$ 的**奇数最短路径**和**偶数最短路径**即可。

另外要注意这个最短路必须 $\leq d$。如果连最短路都比 $d$ 长，$d$ 步肯定不能从 $s$ 走到 $t$ 。

###  _CODE:_ 

```cpp
#include<iostream>
#include<cstdio>
#define re register//卡常技巧 
using namespace std;
int n,m,k;
int hed[20002],next[20002],to[20002],tot;
int dis[10002][10002];
short q[50000001];
int head=1,tail=1;
inline int read()
{
	re int r=0,w=1;
	re char ch=getchar();
	while(ch<'0'||ch>'9')
	  {
	  	if(ch=='-') w=~w+1; 
	  	ch=getchar();
	  }
	while(ch>='0'&&ch<='9')
	  {
	  	r=(r<<3)+(r<<1)+(ch^48);
	  	ch=getchar();
	  }
	return r*w;
}
void add(int x,int y) {
	to[++tot]=y;next[tot]=hed[x];hed[x]=tot;
	to[++tot]=x;next[tot]=hed[y];hed[y]=tot;
	//建x,y的双向边 使用了邻接表 
}
void bfs(int i)
{
	re int x;
	q[1]=i;
	head=1;
	tail=1;
	while(head<=tail) {
		x=q[head];
		head++;//每次处理队头 
		for(int j=hed[x]; j; j=next[j]) {
			if(!dis[i][to[j]]) {//如果当前没被bfs搜到过，因为先被bfs到的一定是最短路 
				dis[i][to[j]]=dis[i][x]+1;//从i到to[j]的最短路可视为从i到x再到to[j]
				//有点像dp或者Floyd的思想，只不过我们这里转移一次就是最优解
				q[++tail]=to[j];//如果搜到就入队 
			}
		}
	}
}
int main() {
	n=read();
	m=read();
	k=read();
	re int x,y;
	for(re int i=1; i<=m; i++) {
		x=read();y=read();
		add(x,y+n);
		add(y,x+n);//建边 
	}
	for(re int i=1;i<=n;i++)
	   bfs(i);
	//这里使用了离线处理 
	re int sx,sy,d;
	for(re int i=1; i<=k; i++) {
		sx=read();sy=read();d=read();
		if(d%2==1) if(dis[sx][sy+n]<=d&&dis[sx][sy+n]) {puts("TAK"); continue ;}
		//如果d是奇数，那么查询sx到sy的奇数最短路 
		//如果sx到sy有奇数最短路并且这个最短路<=d就TAK 
		if(d%2==0) if(dis[sx][sy]<=d&&dis[sx][sy]) {puts("TAK"); continue ;}
		//反之，查询sx到sy的偶数最短路 
		//如果sx到sy有偶数最短路并且这个最短路<=d也TAK
		puts("NIE");
		//如果前面都没有输出TAK，这里就输出NIE 
	}
	return 0; 
}
```


---

## 作者：LYqwq (赞：3)

$\textsf{update on 2022/6/5}$ 修改了一下代码。

---

[题目传送门](https://www.luogu.com.cn/problem/P3556)

# 题目大意

给 $n$ 个点 $m$ 条边无向图，每次询问两个点之间是否有长度为 $d$ 的路径（不一定是简单路径）。

# 思路

使用 bfs 广搜。

题目求的路径长度 $d$ 不一定为简单路径，意为可以重复走边。

可以重复走边，那么我们只需求出每个点的长度为奇数的最短路径和长度为偶数的最短路径。

为什么这么说呢？观察重复走边，就是你回去一次，再跑过来一次，那么每次要加上 $2$ 长度。那么只需判断 $d$ 是否比最短路径大且与最短路长度奇偶性相同。

如何求出奇数最短路和偶数最短路呢？利用[拆点](https://blog.csdn.net/qq_44013342/article/details/89332046)，将每个点拆成两个，分别表示到这个点且路径长度为奇数和偶数的路径长度。

广搜时从每个偶数点开始搜索，建立 dis，查询时可 $\mathcal{O}(1)$ 复杂度。

查询时，奇数和偶数情况都判断一下，如果 $d$ 为奇数，就去奇数最短路径表中查询，如果奇数情况下的最短路径有，并且小于或等于 $d$ 那么就有长度为 $d$ 的路径。反之亦然。

# 代码

```cpp
#include <iostream>
#include <queue>
using namespace std;
template<typename T=int>
inline T read(){
    T X=0; bool flag=1; char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
    if(flag) return X;
    return ~(X-1);
}

template<typename T=int>
inline void write(T X){
    if(X<0) putchar('-'),X=~(X-1);
    T s[20],top=0;
    while(X) s[++top]=X%10,X/=10;
    if(!top) s[++top]=0;
    while(top) putchar(s[top--]+'0');
    putchar('\n');
}

const int N=2e4+5,M=2e5+5;
struct edge{ // 链式前向星存图
	int to,next;
}e[M];
int n,m,k,u,v,d;
int head[N],top;
int dis[N][N]; // dis[i][j]：i->j的最短路径长度
queue<int> q; // bfs所用队列

void add(int u,int v){ // 加边不多说
	top++;
	e[top].to=v;
	e[top].next=head[u];
	head[u]=top;
}

void bfs(int id){ // id 表示搜索的点的编号
	// 广搜差不多是模板
	q.push(id);
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(int i=head[u]; i; i=e[i].next){ // 遍历，更新最短路径
			v=e[i].to;
			if(!dis[id][v]){ // 只 bfs 一次，首先被遍历的才是最短的
				dis[id][v]=dis[id][u]+1; // 因为边权始终为 1，所以更新一次就行。
				q.push(v);
			}
		}
	}
}

int main(){
	n=read(),m=read(),k=read();
	while(m--){
		u=read(),v=read();
		add(u+n,v),add(v,u+n); // 拆点&建边（双向）
		add(u,v+n),add(v+n,u);
	}
	for(int i=1; i<=n; i++) bfs(i); // 预处理 distance
	while(k--){
		u=read(),v=read(),d=read();
		if(d&1 && dis[u][v+n]<=d && dis[u][v+n] // 奇数情况：查询u->v的奇数最短路
		|| !(d&1) && dis[u][v]<=d && dis[u][v]) // 偶数情况：查询u->v的偶数最短路
			puts("TAK"); // 如果最短路径小于等于要求路径，且两种情况满足任意一个，就OK
		else puts("NIE"); // 否则输出 NIE
	}
	return 0;
}
```



---

## 作者：MikeC (赞：2)

## 分析

给定的图是无向图，边权都为一，且不一定是简单路径，故可以在两点间反复横跳。故我们可以采用拆点的方法，将每个点拆成奇数点（即一条长度为奇数的路径的端点）和偶数点（即一条长度为偶数的路径的端点）。由于边权一定，故通过广度优先搜索得到的路径一定是两点间的最短路径。于是我们得到了这样一种解题方案：

- 首先，拆点建边。
- 然后，以每个点为起点进行搜索。
- 最后，离线回答询问。

注意当最短路长度 $dis \gt d$ 时不可能在 $s$ 和 $t$ 间存在一条长度为 $d$ 的路径，需要在回答询问时进行判断。

时间复杂度 $O(n^2)$。

## 代码

``````cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct egde{
    int next;
    int to;
}e[20001];
int head[20001],cnt;
void add(int from,int to){
    e[++cnt].to=to;
    e[cnt].next=head[from];
    head[from]=cnt;
}
int dis[5001][5001];
void bfs(int s){
    queue<int> q;
    q.push(s);
    while(q.size()){
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].next){
            int to=e[i].to;
            if(!dis[s][to]){
                dis[s][to]=dis[s][x]+1;
                q.push(to);
            }
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v+n),add(v+n,u);
        add(v,u+n),add(u+n,v);
    }
    for(int i=1;i<=n;i++)bfs(i);
    for(int i=1;i<=k;i++){
        int s,t,d;
        scanf("%d%d%d",&s,&t,&d);
        if(d%2==1){
            if(dis[s][t+n]<=d&&dis[s][t+n])printf("TAK\n");
            else printf("NIE\n");
        }else{
            if(dis[s][t]<=d&&dis[s][t])printf("TAK\n");
            else printf("NIE\n");
        }
    }
    return 0;
}

``````



---

## 作者：Leianha (赞：2)

## 最短路

先膜拜一下考场上直接A掉这道题的大佬 STO[燃情](https://www.luogu.org/space/show?uid=153897) ~~蒟蒻我考场上竟然连一点思路都没有TAT~~

首先我们珂以发现一个非常重要的条件，就是能重复的走一些边。这说明了什么？只要存在一条奇偶性和$d$相同，并且长度$\le d$的路径，我们就能找到一条符合条件的路径。所以我们就需要找一下从起点到终点的奇数最短路和偶数最短路。

那么怎么找呢？我们又发现它的边权全都是1，所以我们用奇数最短路来更新偶数最短路，用偶数最短路来更新奇数最短路。另外，因为有很多询问的起点都是一样的，所以我们珂以离线来做。

然而还并没有结束。就像下面这组数据：
```
1 0 1
1 1 2
```
应该输出NIE，但我们会发现我们的程序输出的是TAK，为什么呢？因为我们对1号节点赋的初值为0，但我们在后面并没有更新它，所以我们应该记录一下我们队列里进了几个元素，倘若只进了一个元素，就说明这是一个孤立的点，那就是不存在了。

最后献上我~~丑陋~~的代码
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
int n,m,x,y,z,k,s,t,tot,las;
const int N=1000100,inf=999999999;
int head[N],fa[N],dis1[N],dis2[N];
bool vis[N],ans[N];
struct bian
{
	int to,nt;
}e[N];
struct ask
{
	int s,t,lu,id;
	friend bool operator <(const ask &a,const ask &b)
	{return a.s<b.s;}
}Q[1000100];
void add(int f,int t)
{
	e[++tot].to=t;
	e[tot].nt=head[f];
	head[f]=tot;
}
int find(int x){return x==fa[x]?fa[x]:fa[x]=find(fa[x]);}
void he(int x,int y){fa[find(x)]=fa[find(y)];}
queue<int>q;
void spfa(int s)
{
	int x,in=0;
	for(int i=1;i<=n;++i)dis1[i]=dis2[i]=inf;
	dis2[s]=0;q.push(s);vis[s]=1;
	while(!q.empty())
	{
		x=q.front();q.pop();vis[x]=0;in++;
		for(int i=head[x];i;i=e[i].nt)
		{
			if(dis2[e[i].to]>dis1[x]+1)
			{
				dis2[e[i].to]=dis1[x]+1;
				if(!vis[e[i].to])
				{
					q.push(e[i].to);
					vis[e[i].to]=1;
				}
			}
			
			if(dis1[e[i].to]>dis2[x]+1)
			{
				dis1[e[i].to]=dis2[x]+1;
				if(!vis[e[i].to])
				{
					q.push(e[i].to);
					vis[e[i].to]=1;
				}
			}
		}
	}
	if(in==1)dis1[s]=dis2[s]=inf;
	for(int i=las;Q[i].s==Q[las].s;++i)
	{
		if(Q[i].lu&1)ans[Q[i].id]=(dis1[Q[i].t]<=Q[i].lu);
		else ans[Q[i].id]=(dis2[Q[i].t]<=Q[i].lu);
	}
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		he(x,y);
		add(x,y);add(y,x);
	}
	for(int i=1;i<=k;++i)
	{
		scanf("%d%d%d",&Q[i].s,&Q[i].t,&Q[i].lu);
		Q[i].id=i;
		if(Q[i].s>Q[i].t)swap(Q[i].s,Q[i].t);
	}
	sort(Q+1,Q+1+k);
	for(int i=1;i<=k;++i)
	{
		while(Q[i].s==Q[las].s)++i;
		las=i;spfa(Q[i].s);
	}
	for(int i=1;i<=k;++i)
	{
		if(ans[i])puts("TAK");
		else puts("NIE");
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
/*
8 7 4
1 2
2 3
3 4
5 6
6 7
7 8
8 5
2 3 1
1 4 1
5 5 8
1 8 10
*/
```


---

## 作者：KaguyaH (赞：1)

> [P3556](https://www.luogu.com.cn/problem/P3556).

---

**Changelog:**

重构题解，删去大量无意义内容。

---

给定一张 $n$ 个点 $m$ 条边的无向无权图，$k$ 次询问，每次询问给定两点 $s, t$ 间是否有长度为 $d$ 的[途径](https://oi-wiki.org/graph/concept/#_5)。

$2 \leqslant n \leqslant 5 \times 10^3$，$1 \leqslant m \leqslant 5 \times 10^3$，$1 \leqslant k \leqslant 10^6$，$1 \leqslant d \leqslant 10^9$，空间限制 125MB。

---

定义点 $v$ 的度数为 $d(v)$。

有一个比较显然的结论：

- 若 $s, t$ 互不可达，答案为假；

- 若 $s = t$ 且 $d(s) = 0$，则答案（指是否有长度为 $d$ 的途径）等价于 $d = 0$；

- 否则，显然我们可以通过重复走一条边使 $s \rightarrow t$ 的途径长增加 $2$，设 $s, t$ 间长度与 $d$ 奇偶性相同的最短路径长度为 $dis$，则答案等价于 $dis \leqslant d$。

---

我们定义 $dis_{t, u, v}$ 为奇偶性为 $t$（$\in \{0, 1\}$）的从 $u$ 到 $v$ 的最短路径，

用 BFS 算出 $dis$ 数组，按照上面的方式判断即可。

时间复杂度 $\mathcal O(n^2 + nm + k)$，空间复杂度 $\mathcal O(nm)$。

---

注意 $dis$ 数组所占空间，要用 `short` 类型。

---

```cpp
# include <cstdio>
# include <cstring>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
    }
    using namespace Source;
    enum { N = 5000, M = 5000 };
    static hu n, m;
    static uint k;
    static hu out[N + 1][M], deg[N + 1];
    static hu dis[2][N + 1][N + 1];
    static inline const void add() {
        static hu a, b; scanf("%hu%hu", &a, &b);
        out[a][deg[a]++] = b, out[b][deg[b]++] = a;
    }
    static inline const void search(const hu s) {
        static hu q[N * 2]; hu head(0), tail(0);
        dis[0][s][s] = 0, q[tail++] = s << 1;
        while (head < tail) {
            hu t(q[head] >> 1), u(q[head] bitand 1); ++head;
            for (hu i(0); i < deg[t]; ++i)
                if (dis[u][s][t] + 1 < dis[u ^ 1][s][out[t][i]])
                    dis[u ^ 1][s][out[t][i]] = dis[u][s][t] + 1,
                    q[tail++] = out[t][i] << 1 | u ^ 1;
        }
    }
    static inline const void query() {
        static hu s, t; static uint d; scanf("%hu%hu%u", &s, &t, &d);
        puts(
            (
                dis[d & 1][s][t] == dis[0][0][0] ? false :
                s == t and deg[s] == 0 ? d == 0 : dis[d & 1][s][t] <= d
            ) ? "TAK" : "NIE"
        );
    }
    static inline const void main() {
        memset(dis, 0xff, sizeof dis);
        scanf("%hu%hu%u", &n, &m, &k);
        for (hu i(0); i < m; ++i) add();
        for (hu i(1); i <= n; ++i) search(i);
        for (register uint i(0); i < k; ++i) query();
    }
}

signed int main() { Main::main(); return 0; }
```



---

