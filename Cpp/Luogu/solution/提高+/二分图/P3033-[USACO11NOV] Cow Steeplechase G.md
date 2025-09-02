# [USACO11NOV] Cow Steeplechase G

## 题目描述

Farmer John has a brilliant idea for the next great spectator sport: Cow Steeplechase! As everyone knows, regular steeplechase involves a group of horses that race around a course filled with obstacles they must jump over. FJ figures the same contest should work with highly-trained cows, as long as the obstacles are made short enough.

In order to design his course, FJ makes a diagram of all the N (1 <= N <= 250) possible obstacles he could potentially build. Each one is represented by a line segment in the 2D plane that is parallel to the horizontal or vertical axis. Obstacle i has distinct endpoints (X1\_i, Y1\_i) and (X2\_i, Y2\_i) (1 <= X1\_i, Y1\_i, X2\_i, Y2\_i <= 1,000,000,000). An example is as follows:

```cpp

   --+-------   
-----+-----
  ---+---     |
     |     |  |
   --+-----+--+-   |
     |     |  |  | |
     |   --+--+--+-+-
           |  |  | |
              |
```
FJ would like to build as many of these obstacles as possible, subject to the constraint that no two of them intersect. Starting with the diagram above, FJ can build 7 obstacles:

```cpp

   ----------   
-----------
  -------     |
           |  |
           |  |    |
           |  |  | |
           |  |  | |
           |  |  | |
              |

```
Two segments are said to intersect if they share any point in common, even an endpoint of one or both of the segments.  FJ is certain that no two horizontal segments in the original input diagram will intersect, and that similarly no two vertical segments in the input diagram will intersect.

Please help FJ determine the maximum number of obstacles he can build.

给出 $N$ 条**平行于坐标轴**的线段，要你选出尽量多的线段使得这些线段两两没有交点（顶点也算）。横的与横的，竖的与竖的线段之间保证没有交点，输出最多能选出多少条线段。


## 说明/提示

There are three potential obstacles. The first is a horizontal segment connecting (4, 5) to (10, 5); the second and third are vertical segments connecting (6, 2) to (6, 12) and (8, 3) to (8, 5).


The optimal solution is to choose both vertical segments.


## 样例 #1

### 输入

```
3 
4 5 10 5 
6 2 6 12 
8 3 8 5 
```

### 输出

```
2 
```

# 题解

## 作者：FreeTimeLove (赞：17)

## 题意

 $n$ 条线段或横或竖，横与横、竖与竖之间**互不相交**，给出每条线段的端点坐标，问从中**最多**选出几条线段使得被选线段**互不相交**（一条的端点在另一条线段上也算相交）。

## 思路

我们注意到一共有两种线段：横或竖，而且相同种类线段之间都没有交点。为了使最后所有的线段互不相交，只要两条线段有交点，我们就必须从中删去**至少**一条线段。

那么我们可以进行**二分图最大匹配**，令横和竖分别为左右部点，如果两条线段之间有交点，就令对应的点连边。用匈牙利算法求出最大匹配对数 $cnt$，那么最多可以选 $(n-cnt)$ 条线段。

这样做的正确性是显而易见的。我们用**反证法**证明：

假设删完线段后还有交点，那么在二分图中一定有两个点之间**有边**（因为有交点）而且**都未完成匹配**（否则就被删了），那么此时匈牙利算法还没有结束，与删完线段相矛盾。所以如果删完了线段，一定是没有交点的。

那么为什么我们要求**最多**选几条线段，即**最少**删去几条线段，却用二分图**最大**匹配呢？因为如果两点之间有边，它们所代表的两条线段一定要**至少**删去一条线段。我们用二分图最大匹配求出最大匹配对数 $cnt$，即有 $cnt$ 对线段**不能**同时存在，从中至少删去一条。那么我们从每一对中删去**一**条，既保证了答案没有交点，又让删线段数**最小**，选线段数**最大**，因此最后的答案 $(n-cnt)$ 就是能够选的**最大条数**。

### AC code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
const int N=1e5+5;
int n,n1,tot,nd[N],cnt;
int x1[N],x2[N],y1[N],y2[N],bk[N],a[N],cp[N];
struct edge{
	int v,nxt;
}ed[N];
void add(int u,int v){
	ed[++tot]={v,nd[u]};
	nd[u]=tot;
}
int hung(int u){//匈牙利算法 
	bk[u]=1;
	for(int i=nd[u];i;i=ed[i].nxt){
		int v=ed[i].v;
		if(bk[cp[v]])continue;
		if(cp[v]==0||hung(cp[v]))return cp[v]=u;//相当于return true 
	}
	return 0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x1[i]>>y1[i]>>x2[i]>>y2[i];
		if(x1[i]>x2[i])swap(x1[i],x2[i]);//不一定x1<=x2,y1<=y2
		if(y1[i]>y2[i])swap(y1[i],y2[i]);
		if(x1[i]==x2[i])a[i]=1,n1++;//竖 
		else a[i]=2;//横 
	}
	for(int i=1;i<n;i++)//有交点就建边 
		for(int j=i+1;j<=n;j++){
			if(a[i]==1&&a[j]==2)
				if(x1[i]>=x1[j]&&x2[i]<=x2[j]&&y1[j]>=y1[i]&&y2[j]<=y2[i])
					add(i,j+n1);
			if(a[i]==2&&a[j]==1)
				if(x1[j]>=x1[i]&&x2[j]<=x2[i]&&y1[i]>=y1[j]&&y2[i]<=y2[j])
					add(j,i+n1);
		}
	for(int i=1;i<=n;i++){
		if(a[i]==2)continue;
		memset(bk,0,sizeof(bk));
		if(hung(i))cnt++;
	}
	cout<<n-cnt<<endl;
	return 0;
}
```

## 后记

这其实是二分图求**最大独立集**类型的典型题目，标准做法即求出**最小点覆盖**（最大匹配对数），答案即**总点数** $-$ **最小点覆盖**。

### The End.

---

## 作者：hovny (赞：6)


$\mathtt{Updata\ 2019.11.13}$ 今天膜你赛做到了原题，不得不来修一下 [$blog$](https://hovnySiLenCe.github.io/)

## [题面](https://www.luogu.org/problemnew/show/P3033)

有 $n$ 条平行于坐标轴线段，取的线段要求不相交，最大化所取线段数目

## 解题思路

**二分图匹配**

### 分析

把平行于 $x$ 轴和平行于 $y$ 轴的线段分别看成两个集合，这样就和二分图有关了

从最小割的方面想，要想所选的数目尽量多，那么就是不能选的尽量少

显然，如果两条线段有相交的部分，则有一条必不能取，因此以是否相交为依据建边，再跑一个最小割，或者说就是二分图的最大匹配，答案即为 $n-Maxflow$

可以用 $Dinic$ 或者匈牙利算法实现

### warning

个人认为最大的坑点是所给的线段的端点不是有序的，比如平行于 $x$ 轴的线段的两个端点可能并不是按照两点 $x$ 坐标的大小给出，要特别判断，否则，判断相交的时候就 $GG$ 了，~~当然不要忘记网络流建边开四十倍~~

## Code

```cpp
#include<bits/stdc++.h>
#define rgt register
#define rint rgt int
#define LL long long
#define rll rgt LL
#define inf 0x7f7f7f7f
#define M 3000003
#define N 257
using namespace std;
template<class K>inline bool cmax(K&a,const K&b){return(a<b)?a=b,1:0;}
template<class K>inline bool cmin(K&a,const K&b){return(a>b)?a=b,1:0;}
inline int read() {
	rint s=0;
	rgt char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) s=(s<<1)+(s<<3)+c-'0',c=getchar();
	return s;
}
struct Edge{
	int to,nxt,cap;
	Edge(int a,int b,int c):to(a),nxt(b),cap(c){}
	Edge(){}
}b[M];
struct segment{
	int lx,ly,rx,ry;
	inline void in() {
		lx=read(),ly=read(),
		rx=read(),ry=read();
		if(lx>rx) lx^=rx^=lx^=rx;//可能不是有序的
		if(ly>ry) ly^=ry^=ly^=ry;
	}
}A[N],B[N],c;
int n,la,lb,t=1,S,T,head[N],dep[N],Maxflow;
inline void add(rint x,rint y) {
	b[++t]=Edge(y,head[x],1),head[x]=t,
	b[++t]=Edge(x,head[y],0),head[y]=t;
}
inline bool cross(rgt segment a,rgt segment b) {//判断相交
	return b.lx<=a.lx&&a.lx<=b.rx&&a.ly<=b.ly&&b.ly<=a.ry;
}
inline bool BFS() {
	rint i,to,cur,cap;
	queue<int>p;
	memset(dep,0,sizeof(dep));
	dep[S]=1,p.push(S);
	while(!p.empty()) {
		cur=p.front(),p.pop();
		for(i=head[cur];i;i=b[i].nxt) {
			to=b[i].to;
			if(b[i].cap&&!dep[to]) {
				dep[to]=dep[cur]+1;
				if(to==T) return 1;
				p.push(to);
			}
		}
	}return 0;
}
inline int Dinic(rint k,rint flow) {
	if(k==T) return flow;
	rint i,to,cap,res,rest=flow;
	for(i=head[k];i&&rest;i=b[i].nxt) {
		to=b[i].to,cap=b[i].cap;
		if(cap&&dep[to]==dep[k]+1) {
			res=Dinic(to,min(rest,cap));
			if(!res) dep[to]=0;
			b[i].cap-=res,
			b[i^1].cap+=res,
			rest-=res;
		}
	}
	return flow-rest;
}
int main() {
	rint i,j,flow;n=read();
	for(i=1;i<=n;i++) {
		c.in();
		if(c.lx==c.rx) A[++la]=c;//按照平行的坐标分组
		else B[++lb]=c;
	}T=n+1;
	for(i=1;i<=la;i++) add(S,i);//超源和超汇
	for(i=1;i<=lb;i++) add(i+la,T);
	for(i=1;i<=la;i++)
		for(j=1;j<=lb;j++)
			if(cross(A[i],B[j]))//相交就建边
				add(i,j+la);
	while(BFS())//Dinic大法吼
		while((flow=Dinic(S,inf)))
			Maxflow+=flow;
	printf("%d",n-Maxflow);
	return 0;
}
```

---

## 作者：Mr_Wolfram (赞：3)

[蒟蒻的博客](http://www.cnblogs.com/Mr-WolframsMgcBox/)

##利用二分图匹配求最大独立集

本题的边一定平行于坐标轴，且同向的线段一定不重合，这是经典的二分图建图方法，本题要求的是最大不重合的线段数，那就是求二分图的最大独立集，最大独立集=总点数-最大匹配数。

**本题有一个坑点，就是输入的数据不一定有序，也就是x1不一定比x2小**



```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int init(){
    int rv=0,fh=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') fh=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        rv=(rv<<1)+(rv<<3)+c-'0';
        c=getchar();
    }
    return rv*fh;
}
int n,x,y,g[300][300],match[300];
bool f[300];
struct line{
    int a,b,c;
}col[300],row[300];
bool hungarian(int u){
    for(int i=1;i<=g[u][0];i++){
        int v=g[u][i];
        if(!f[v]){
            f[v]=1;
            if(!match[v]||hungarian(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    n=init();
    for(int i=1;i<=n;i++){
        int a=init(),b=init(),c=init(),d=init();
        if(a==c){
            col[++x].a=a;
            col[x].b=min(b,d);
            col[x].c=max(b,d);
        }else{
            row[++y].a=b;
            row[y].b=min(a,c);
            row[y].c=max(a,c);
        }
    }
    for(int i=1;i<=x;i++){
        for(int j=1;j<=y;j++){
            if(col[i].b<=row[j].a&&col[i].c>=row[j].a&&row[j].b<=col[i].a&&row[j].c>=col[i].a){
                g[i][++g[i][0]]=j;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=x;i++){
        memset(f,0,sizeof(f));
        if(hungarian(i)) ans++;
    }
    cout<<n-ans<<endl;
    return 0;
}
```

---

## 作者：Tzs_yousa (赞：1)

## 算法
显而易见，是匈牙利的板子算法，然而光知道匈牙利是不行的，这题核心在于它的建边。遇到这种题我们是必须要有核心在建边的意识。
## 建边
首先，我们需要开四个数组来存坐标，我们可以知道横坐标一样就是横边，纵坐标一样就是竖边。然后，为了让它满足二分图的性质以方便建图，我们可以新定义一个 $num$ 来存它的竖边的个数，最后就可以很方便的建图。建图是我们需要两个循环，如果有交点，就连边，表示建边。然后最后求出来需要删掉的边数再用总边数删去即可。
看代码：
```cpp
for (int i = 1; i <= n; i++)
	{
		cin >> p1[i] >> p2[i] >> p3[i] >> p4[i];
		if(p1[i] > p3[i]) swap(p1[i], p3[i]);
		if(p2[i] > p4[i]) swap(p2[i], p4[i]);
		if(p1[i] == p3[i]) f[i] = 1, num++;//竖边
		else f[i] = 2;//横边 
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if(f[i] == 1 && f[j] == 2)
				if(p1[j] <= p1[i] && p3[j] >= p1[i] && p2[j] <= p4[i] && p2[j] >= p2[i]) add(i, j + num);
			if(f[i] == 2 && f[j] == 1)
				if(p2[j] <= p2[i] && p4[j] >= p2[i] && p1[j] >= p1[i] && p1[j] <= p3[i]) add(j, i + num);
		}
	} 
```
## 匈牙利算法
可以去 [匈牙利算法](https://oi-wiki.org/graph/graph-matching/bigraph-weight-match/) 这里看一下。实在看不懂可以背过。

总代码：
```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXN = 1e5 + 10;
using namespace std;
int n, p1[MAXN], p2[MAXN], p3[MAXN], p4[MAXN], f[MAXN], cnt, head[MAXN], num, tot, vis[MAXN], mc[MAXN];
struct edge{
	int to, next;
}e[MAXN];
void add(int u, int v)
{
	e[++cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}
bool solve(int x)
{ 
	for (int i = head[x]; i; i = e[i].next)
	{
		int v = e[i].to;
		if(!vis[v])
		{
			vis[v] = 1;
			if(mc[v] == 0 || solve(mc[v]))
			{
				mc[v] = x;
				return true;
			}
		}
	}
	return false;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> p1[i] >> p2[i] >> p3[i] >> p4[i];
		if(p1[i] > p3[i]) swap(p1[i], p3[i]);
		if(p2[i] > p4[i]) swap(p2[i], p4[i]);
		if(p1[i] == p3[i]) f[i] = 1, num++;//竖边
		else f[i] = 2;//横边 
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if(f[i] == 1 && f[j] == 2)
				if(p1[j] <= p1[i] && p3[j] >= p1[i] && p2[j] <= p4[i] && p2[j] >= p2[i]) add(i, j + num);
			if(f[i] == 2 && f[j] == 1)
				if(p2[j] <= p2[i] && p4[j] >= p2[i] && p1[j] >= p1[i] && p1[j] <= p3[i]) add(j, i + num);
		}
	} 
	for (int i = 1; i <= n; i++)
	{
		if(f[i] == 1)
		{
			memset(vis, 0, sizeof(vis));
			if(solve(i)) tot++;
		}
	}
	cout << n - tot;
	return 0;
}
```


---

## 作者：谦谦君子 (赞：1)

### [博客查看~](https://blog.csdn.net/Modestr/article/details/105350037)

## 算法标签：二分图最大独立集

二分图各种类型题目数不胜数，这一题便是一个二分图的最大独立集问题

### 前置芝士
**先简短介绍一下匈牙利算法**

其实匈牙利算法就是一个**妥协**的过程，即若一点$A$于另一点$B$相连，而该边已有匹配$C$，则尽可能的让$C$去寻求其他点进行匹配，然后让$A,B$完成匹配(~~不太地道的感觉~~）

核心代码：
```
inline bool dfs(int x)
{
	for (int i=head[x];i;i=edge[i].next)
	{
		int y=edge[i].to;
		if (vis[y]==false)
		{
			vis[y]=true;
			if (match[y]==0||dfs(match[y])==true)
			{
				match[y]=x;
				return true;
			}
		}
	}
}
```

## 二分图最大独立集
**定义**：
对于一张**无向图**$G(V,E)$，选出一个$V$的子集$S$，使得$S$中**任意两点之间都没有边**，且$S$是最大这样的子集。

求解方法：
**二分图的最大独立集的点的数量=总点数N-最大匹配**而最大匹配用匈牙利即可求得

简单的证明：要使得独立集越大，那么删掉的点就要越少，同时话要保证删掉的点覆盖到所有边，所以删掉的因该是最小点覆盖。

推荐题目：

- Example1.[[LGOJ] P5030长脖子鹿防置](https://www.luogu.com.cn/problem/P5030)
- Example2.[[LGOJ]P3355 骑士共存问题](https://www.luogu.com.cn/problem/P3355)

好的，那么介绍完最大独立集，讲回我们这道题

这题是一个非常典型的二分图最大独立集问题，发现每两条均均是不重合的，于是想到直接将相交的两条线段连接，得到的一点是一个二分图（同边的（即同方向）没有边相连，符合二分图定义）

于是呢我们发现题目所求是"选出尽量多的线段使得这些线段两两没有交点",那么在二分图中间也就是选出尽量多的点使得他们之间没有连边，通过这个**建模**，我们就将这个题完美地转化成了一个裸的**二分图最大独立集**问题了，根据

二分图最大独立集=点的个数$-$最大匹配于是乎这题就可以求解了

最后再讲一下怎么判断**相交**的问题
- 判断线段方向即看横纵做坐标哪个相等即可，若$X1=X2$则方向为竖，若$Y1=Y2$则为横
- 对每个坐标进行排序，于是我们得到：
```
inline bool intersect(node2 x,node2 y)	//x为竖边，y为横边，且横纵坐标均为从小到大
{
	if (x.a.x>=y.a.x&&x.a.x<=y.b.x&&x.a.y<=y.a.y&&x.a.y>=y.b.y)
	{
		return 1;
	}
	return 0;
}
```
即竖边的$x$坐标位于横边的两个端点的$x$坐标之间并且横边的$y$坐标位于竖边的两个端点的$y$坐标之间

ok，于是我们便愉快地得到了代码：
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int n,cnt,tot,ans;
int head[maxn],vis[maxn],match[maxn];
struct node
{
	int x,y;
};
struct node2
{
	int dir;
	node a,b;
}seg[maxn];
struct node3
{
	int from,to,next;
}edge[maxn];
inline int add(int x,int y)
{
	edge[++tot].next=head[x];
	edge[tot].from=x;
	edge[tot].to=y;
	head[x]=tot;
}
inline int read()
{
	int s=0,f=1;
	char c=getchar();
	while (c<'0'||c>'9')
	{
		if (c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while (c>='0'&&c<='9')
	{
		s=s*10+c-48;
		c=getchar();
	}
	return s*f;
}
inline bool cmp(node2 x,node2 y)
{
	return x.dir<y.dir;
}
inline bool intersect(node2 x,node2 y)
{
	if (x.a.x>=y.a.x&&x.a.x<=y.b.x&&y.a.y>=x.a.y&&y.a.y<=x.b.y)
	{
		return 1;
	}
	return 0;
}
inline bool dfs(int x)
{
	for (int i=head[x];i;i=edge[i].next)
	{
		int y=edge[i].to;
		if (vis[y]==false)
		{
			vis[y]=true;
			if (match[y]==0||dfs(match[y])==true)
			{
				match[y]=x;
				return true;
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	n=read();
	for (int i=1;i<=n;i++)
	{
		seg[i].a.x=read();
		seg[i].a.y=read();
		seg[i].b.x=read();
		seg[i].b.y=read();
		if (seg[i].a.x==seg[i].b.x)
        {
			seg[i].dir=1;
			cnt++;
			if (seg[i].a.y>seg[i].b.y)
			{
				swap(seg[i].a.y,seg[i].b.y);
			}
        }
        if (seg[i].a.y==seg[i].b.y)
        {
            seg[i].dir=2;
            if (seg[i].a.x>seg[i].b.x)
			{
				swap(seg[i].a.x,seg[i].b.x);
			}
        }
	}
	sort(seg+1,seg+n+1,cmp);
	for (int i=1;i<=cnt;i++)
	{
		for (int j=cnt+1;j<=n;j++)
		{
			if (intersect(seg[i],seg[j]))
			{
				add(i,j);
			}
		}
	}
	for (int i=1;i<=cnt;i++)
	{
		memset(vis,0,sizeof(vis));
		if (dfs(i))
		{
			ans++;
		}
	}
	cout<<n-ans<<endl;
	return 0;
}

```


---

## 作者：zht467 (赞：1)

因为横的与横的，竖的与竖的没有交点，所以直接把相交的线段相连，然后肯定是个二分图。

选出多少个线段，就是求二分图的最大独立集，等于节点数(N) - 最大匹配数。

由于线段的4个坐标太大 (X1\_i, Y1\_i) and (X2\_i, Y2\_i) (1 <= X1\_i, Y1\_i, X2\_i, Y2\_i <= 1,000,000,000)，不能用二维矩阵来记录。

又看到线段数量很少 (1 <= N <= 250)，所以可以用结构体来存，然后通过两重循环判断线段是否相连。

最后用匈牙利算法求最大匹配数，就好了。







```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int n, lh, ll, cnt, sum;
int next[62501], to[62501], head[251], g[251];
bool vis[251];
struct node
{
    int pos, minn, maxx;
}h[10001], l[10001];
void add(int x, int y)
{
    to[cnt] = y;
    next[cnt] = head[x];
    head[x] = cnt++;
}
bool check(int i, int j)
{
    if(h[i].pos < l[j].minn || h[i].pos > l[j].maxx) return 0;
    if(l[j].pos < h[i].minn || l[j].pos > h[i].maxx) return 0;
    return 1;
}
bool find(int u)
{
    int i, v;
    for(i = head[u]; i != -1; i = next[i])
    {
        v = to[i];
        if(!vis[v])
        {
            vis[v] = 1;
            if(!g[v] || find(g[v]))
            {
                g[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    int i, j, x1, y1, x2, y2;
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for(i = 1; i <= n; i++)
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if(x1 == x2)
        {
            ++lh;
            h[lh].pos = x1;
            h[lh].minn = min(y1, y2);
            h[lh].maxx = max(y1, y2);
        }
        else if(y1 == y2)
        {
            ++ll;
            l[ll].pos = y1;
            l[ll].minn = min(x1, x2);
            l[ll].maxx = max(x1, x2);
        }
    }
    for(i = 1; i <= lh; i++)
     for(j = 1; j <= ll; j++)
      if(check(i, j))
       add(i, j);
    for(i = 1; i <= lh; i++)
    {
        memset(vis, 0, sizeof(vis));
        if(find(i)) sum++;
    }
    printf("%d", n - sum);
    return 0;
}
```

---

## 作者：mcDinic (赞：0)

这题就是道模板，毫无难度，简单介绍下吧。

把每条线段给化为一个点，答案即对应图的最大独立集。至于图中的边，也很好连的，两条线段相交就加边，至于判断线段相交的参见代码。

唯一有一点点坑的就是输入数据无序，不保证两个点一定是从上到下或从左到右。

## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,pf[305],o[305][10],cnt,h[305],b[305],vis[305],ti,ans;
struct node{
	int u,nxt;
}e[500005];
void add(int x,int y){e[cnt].u=y,e[cnt].nxt=h[x],h[x]=cnt++;}
bool fd(int x){
	for(int i=h[x];i!=-1;i=e[i].nxt){
		if(b[e[i].u]<ti){
			b[e[i].u]=ti;
			if(!vis[e[i].u]||fd(vis[e[i].u])){vis[e[i].u]=x;return 1;}
		}
	}
	return 0;
}
signed main(){
	memset(h,-1,sizeof(h));
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int o1,o2,o3,o4;
		scanf("%lld%lld%lld%lld",&o1,&o2,&o3,&o4);
		if(o1>o3)swap(o1,o3);
		if(o2>o4)swap(o2,o4);
		if(o1==o3)pf[i]=1;
		else pf[i]=2;
		o[i][1]=o1,o[i][2]=o2,o[i][3]=o3,o[i][4]=o4;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(pf[i]+pf[j]==3){
				if(pf[i]==1&&o[j][2]>=o[i][2]&&o[j][2]<=o[i][4]&&o[i][1]>=o[j][1]&&o[i][1]<=o[j][3])add(i,j),add(j,i);
				if(pf[j]==1&&o[i][2]>=o[j][2]&&o[i][2]<=o[j][4]&&o[j][1]>=o[i][1]&&o[j][1]<=o[i][3])add(i,j),add(j,i);
			}
		}
	}
	for(int i=1;i<=n;i++)if(pf[i]==1)ti++,ans+=fd(i);
	printf("%lld",n-ans);
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

设一条线段的端点坐标分别为 $(x_1,y_1),(x_2,y_2)$。所有线段构成集合 $S$。

很明显，$x_1=x_2$ 和 $y_1=y_2$ 满足且仅满足一个。所以，为了方便，不妨设 $x_1\le x_2$ 且 $y_1\le y_2$。

首先，我们可以将满足 $x_1=x_2$ 的线段放入一个集合 $X$，在将满足 $y_1=y_2$ 的线段放入集合 $Y$。很明显，$X\cap Y=\emptyset$ 且 $X\cup Y=S$。

这样就满足二分图的性质了。

对于选择一些边，很明显，不能有任意两个边相交。那么，答案就是 $n$ 减去最大匹配数。

设集合 $X$，$Y$ 的大小分别为 $nx$，$ny$。

如果 $X[i]\perp Y[j]$，则连一条容量为 $1$ 的边 $i\to j+nx$。

然后，设源点为 $s$，汇点为 $t$。对于所有 $i\ (i\in[1,nx])$，连一条容量为 $1$ 的边 $s\to i$。同样，对于所有 $i\ (i\in[1,ny])$，连一条容量为 $1$ 的边 $i+nx\to t$。

然后就跑 `dinic` 网络流就行了。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define max_n 250//最大线段数
int n;//线段数
#define s 0//源点
#define t 520//汇点（皮一下）
int nx=0;//X相等数
int ny=0;//Y相等数
struct L{
	int x1,y1,x2,y2;//端点
};
L l[max_n+2];//线段
int x[max_n+2];//对应线段编号
int y[max_n+2];//对应线段编号
struct E{
	int v,w,a,nx;//端点、流量、反边、下一条
}e[100002/*10^5+2*/];//边
int ei=0;//下标
int fir[max_n<<2];//第一条边
int de[max_n<<2];//深度
int ans=0;//答案
inline void sw(int &a,int &b){
	a^=b^=a^=b;//神奇的交换
}
inline int mi(int a,int b){
	return a<b?a:b;
}
inline bool cr(int i,int j){
	return l[j].x1<=l[i].x1&&l[i].x1<=l[j].x2&&l[i].y1<=l[j].y1&&l[j].y1<=l[i].y2;//注意这条公式
}
inline void addedge(int u,int v,int w){
	++ei; e[ei].v=v; e[ei].w=w; e[ei].a=ei+1; e[ei].nx=fir[u]; fir[u]=ei;
	++ei; e[ei].v=u; e[ei].w=0; e[ei].a=ei-1; e[ei].nx=fir[v]; fir[v]=ei;
}
bool bfs(){
	memset(de,0,sizeof(de));
	queue<int>q;
	de[s]=1;
	q.push(s);
	int u;
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(int i=fir[u],v;i;i=e[i].nx){
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
	if(u==t)return f;//到达终点
	int res=0;
	for(int i=fir[u],v;i;i=e[i].nx){
		v=e[i].v;
		if(e[i].w&&de[u]+1==de[v]){
			int w=dfs(v,mi(e[i].w,f));
			e[i].w-=w;
			e[e[i].a].w+=w;
			f-=w;
			res+=w;
		}
	}
	return res;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P3033_1.in","r",stdin);
	freopen("P3033_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d%d%d",&l[i].x1,&l[i].y1,&l[i].x2,&l[i].y2);
		if(l[i].x1>l[i].x2)sw(l[i].x1,l[i].x2);//记得交换
		if(l[i].y1>l[i].y2)sw(l[i].y1,l[i].y2);//同上
		if(l[i].x1==l[i].x2)x[++nx]=i;
		else y[++ny]=i;
	}
	for(int i=1;i<=nx;++i){
		for(int j=1;j<=ny;++j){
			if(cr(x[i],y[j])){//相交
				addedge(i,j+nx,1);
			}
		}
	}
	for(int i=1;i<=nx;++i){
		addedge(s,i,1);
	}
	for(int i=1;i<=ny;++i){
		addedge(i+nx,t,1);
	}
	while(bfs())ans+=dfs(s,0x3f3f3f3f);
	printf("%d\n",n-ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56771320)

By **dengziyue**

---

## 作者：YinyuDream (赞：0)

# 二分图最大独立集

本题是给定$n$条垂直于坐标轴的线段，让我们选尽量多的线段，使得他们的交集为空。观察发现，设线段$l_1$和$l_2$交于点$p$，那么$p$只能与其中的一条线段匹配，于是我们可以建立如下的二分图模型：将横着的线段和竖着的线段分别看做两个点集，若两条线段有交点，则在其中连一条边，那么问题就被转化成了二分图的最大独立集问题。因为如果选取的点集中是不存在边连接其中两点的，那么任意两条线段之间就必然没有交点，而我们又求的是最大的独立集，那么满足线段的个数尽量多的要求，根据最大独立集=点数-最大匹配，那么我们只需求得二分图的最大匹配即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+10;
int n,cnt1,cnt2,ans;
struct seg{
	int c,l,r;
}a[maxn],b[maxn];
int mapp[maxn][maxn],use[maxn],result[maxn];
bool dfs(int x)
{
	for(int i=1;i<=cnt2;i++){
		if(mapp[x][i]&&!use[i]){
			use[i]=1;
			if(!result[i]||dfs(result[i])){
				result[i]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d",&n);
	for(int i=1,_a,_b,_c,_d;i<=n;i++){
		scanf("%d%d%d%d",&_a,&_b,&_c,&_d);
		if(_a==_c)a[++cnt1]={_a,_b,_d};
		if(_b==_d)b[++cnt2]={_b,_a,_c};
	}
	for(int i=1;i<=cnt1;i++)
		if(a[i].l>a[i].r)
			swap(a[i].l,a[i].r);
	for(int i=1;i<=cnt2;i++)
		if(b[i].l>b[i].r)
			swap(b[i].l,b[i].r);
	for(int i=1;i<=cnt1;i++){
		for(int j=1;j<=cnt2;j++){
			if(a[i].l<=b[j].c&&a[i].r>=b[j].c&&b[j].l<=a[i].c&&b[j].r>=a[i].c){
				mapp[i][j]=1;
			}
		}
	}
	for(int i=1;i<=cnt1;i++){
		memset(use,0,sizeof use);
		if(dfs(i))ans++;
	}
	printf("%d",n-ans);
	return 0;
}
```


---

## 作者：KobeWu (赞：0)

### 解题之前
其实这道题我从大概接触简单的动态规划的时候就开始关注了，如果数据范围更小一点，此题似乎是一个状压DP。然而，$1 \leq N \leq 250$。~~bitset~~
### 题目分析
根据题目描述，在一个平面直角坐标系中，对于一些给定的垂直或平行于x轴的线段，我们需要求最多能选出多少条互不相交的线段。

题目描述其实已经将这些给定的线段分成了两类：横的（平行于x轴）和竖的（垂直于x轴）。除此之外，题目还保证同一类线段（横的$/$竖的）之间没有交点。事实上，这些线段的组合可以抽象成一个二分图，即

- 线段 $\rightarrow$ 节点
- 两条线段之间是否有交点$\rightarrow$两条线段对应的两个点之间是否连边

如此，我们需要求的便转化为这个二分图的最大独立集的元素数目。

~~众所周知，~~一个二分图的最大独立集的元素数目等于这个二分图的节点总数于其最大匹配数之差。于是，经过一番对题意的转化后，你就能非常轻松的拿到100分的好成绩！

以下是我的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MXN 260
int N,hd[MXN],ed[MXN*MXN<<1],nxt[MXN*MXN<<1],tot;
struct Point {int x,y;};
struct Segment {int typ;Point p1,p2;}a[MXN];
int match[MXN]; bool vis[MXN];
inline int rd()
{
	int ret=0,f_f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f_f=-1; c=getchar();}
	while(c>='0' && c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ret*f_f;
}
inline void Swap(int &x,int &y) {x^=y,y^=x,x^=y;}
inline bool cmp(Segment x,Segment y) {return x.typ < y.typ;}
inline bool Judge_intersect(Segment x,Segment y) {return x.p1.x>=y.p1.x && x.p1.x<=y.p2.x && y.p1.y>=x.p1.y && y.p1.y<=x.p2.y;}
inline void AddEdge(int u,int v) {ed[++tot]=v,nxt[tot]=hd[u],hd[u]=tot;}
inline bool Dfs(int u)
{
	for (int p=hd[u];p!=-1;p=nxt[p])
	{
		int v=ed[p];
		if (!vis[v])
		{
			vis[v]=true;
			if (match[v] == -1 || Dfs(match[v]))
			{
				match[v]=u;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	N=rd(); int ct=0;
	for (int i=1;i<=N;i++)
	{
		a[i].p1.x=rd(),a[i].p1.y=rd();
		a[i].p2.x=rd(),a[i].p2.y=rd();
		if (a[i].p1.x == a[i].p2.x)
		{
			a[i].typ=1,ct++;
			if (a[i].p1.y > a[i].p2.y) Swap(a[i].p1.y,a[i].p2.y); // 为了更方便的判断两条线段是否相交 
		}
		if (a[i].p1.y == a[i].p2.y)
		{
			a[i].typ=2;
			if (a[i].p1.x > a[i].p2.x) Swap(a[i].p1.x,a[i].p2.x); // 为了更方便的判断两条线段是否相交
		}
	}
	sort(a+1,a+1+N,cmp);
	memset(hd,-1,sizeof(hd)),tot=0;
	for (int i=1;i<=ct;i++)
		for (int j=ct+1;j<=N;j++)
			if (Judge_intersect(a[i],a[j])) AddEdge(i,j); // 建二分图 
	int ans=0;
	memset(match,-1,sizeof(match));
	for (int i=1;i<=ct;i++) // 求二分图最大匹配——匈牙利算法 
	{
		memset(vis,0,sizeof(vis));
		if (Dfs(i)) ans++;
	}
	return printf("%d\n",N-ans),0;
}
```

---

