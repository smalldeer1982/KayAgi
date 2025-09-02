# [BalticOI 2016] Park (day1)

## 题目描述

在 Byteland 的首都，有一个以围墙包裹的矩形公园，其中以圆形表示游客和树。  
公园里有四个入口，分别在四个角落（$1, 2, 3, 4$ 分别对应左下、右下、右上、左上）。游客只能从入口进出。  
游客可以在他们与公园的两邻边相切的时候进出对应的入口。游客可以在公园里自由活动但不允许与树重叠。  
你的任务是为每个游客计算，给定他们进入公园的入口，他们可以从哪个入口离开公园。

## 说明/提示

两个物体有重叠定义为它们不止一个公共点。

下图展示了每个游客的入口和可能的路线：

![](https://i.loli.net/2018/08/11/5b6e30c4b5a35.png)

对于每个子任务，$4k \leq w,h \leq 10^9$，$k$表示最大的游客半径。

|子任务|分数|数据范围|
|:-:|:-:|-|
|1|27|$1 \leq n \leq 2000,m=1$|
|2|31|$1 \leq n \leq 200,1 \leq m \leq 10^5$|
|3|42|$1 \leq n \leq 2000,1 \leq m \leq 10^5$|

由 @I_love_him52 提供翻译

## 样例 #1

### 输入

```
5 3
16 11
11 8 1
6 10 1
7 3 2
10 4 1
15 5 1
1 1
2 2
2 1
```

### 输出

```
1234
2
14
```

# 题解

## 作者：⚡LZSY01_XZY⚡ (赞：15)

做题目时因为没有题解，自己调试了半天，于是想把自己的程序分享一下，给后来者参考参考。

# 进入正题
这道题目运用到了[$\color{#ff0481}\boxed{\small\texttt{并查集}}$](https://www.luogu.org/problemnew/lists?name=&orderitem=pid&tag=47&content=0&type=)、$\color{#ff0481}\boxed{\small\texttt{离线}}$。  
上述算法不清楚不要紧，我们慢慢来。

## 并查集
并查集从字面意思上来理解，是一种支持**合并**与**查询**的数据结构。并查集的合并指的是将两颗有根树合并，查询指的是查询节点的根。

并查集的基本思路是**路径压缩**，对于任意节点$x$，我们让节点$x$的父指针指向根，根的父指针指向自己，这样查询时便可以一步到位。对于合并，就只需查找根节点，然后将其中一个根的父指针指向另一个根就行了。但是，你可能有疑惑，这样并没有路径压缩呀。其实，路径压缩是在查询时进行的。我们一边查询一边用返回值更新父指针，如代码：
```cpp
inline int find(int x)                    //查询根节点
{
    if (f[x]==x) return x;                //如果当前节点为根节点，返回本身。
    f[x]=find(f[x]);                      //否则，查询父节点，并将父指针指向根节点。
    return f[x];                          //返回根节点
}
```
合并的代码就更加简单了：
```cpp
inline void together(int x,int y)
{
	int r1,r2;
    r1=find(x);r2=find(y);       //查询x、y的根
    if (r1==r2) return ;         //若x、y以在同一棵树中，不合并
    f[r1]=r2;                    //将r1的根置为r2
}
```
这一题，我们可以用并查集来判断**连通情况**，如果树与边界相交或树与树相交(相切也算)，合并。最后，判断两边界是否处于同一集合中，若是，则不能通行，否则，能过。但这也仅仅只是判断了相交的情况，一些情况下，即使是两树不相交，它们的距离过小，~~长得胖的~~人也过不去。

对与这个情况，一种解决方法是建立$m$个并查集，枚举距离，小于人的直径时，就合并。当这种方法时间复杂度太高。于是，我便想到了第二种方法，离线处理，将人按直径(输入是半径)由小到大排序，距离也按由小到大排序，这样原先无法通过的距离，之后任然无法通过。就不需要重复处理，还可以用一个$last$变量记录上次判断到的距离。

## $code:$
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=2015;
const int MAXM=100015;
const double eps=1e-4;
int n,m,id,last,k;
long long l,r;

struct tree
{
    long long x,y,d;
    
    inline double operator - (struct tree tmp) 
    {
        return sqrt((x-tmp.x)*(x-tmp.x)+(y-tmp.y)*(y-tmp.y))-d-tmp.d;
    }
}t[MAXN];

struct man
{
    long long from,id,d;
    
    inline bool operator < (const man &tmp) const
    {
        return d<tmp.d;
    }
}w[MAXM];

struct cost
{
    long long a,b;double dis;
    
    inline bool operator < (const cost &tmp) const
    {
        return dis<tmp.dis;
    }
}h[MAXN*MAXN];
int f[MAXM];
bool ans[MAXM][5],map[5][5];

inline int find(int x)
{
    return f[x]==x?x:f[x]=find(f[x]);
}

inline void together(int x,int y)
{
    int r1,r2;
    r1=find(x);r2=find(y);
    if (r1==r2) return ;
    f[r1]=r2;
}

inline void turn_off(int x,int y)
{
    map[x][y]=map[y][x]=false;
}

int main()
{
    cin>>n>>m>>l>>r;
    for (int i=1;i<=n;i++) cin>>t[i].x>>t[i].y>>t[i].d;
    for (int i=1;i<=m;i++) {cin>>w[i].d>>w[i].from;w[i].d*=2;w[i].id=i;}
    for (int i=1;i<=n;i++)
    {
        h[++id]=(cost){i,n+1,(double)t[i].x-t[i].d};
        h[++id]=(cost){i,n+2,(double)t[i].y-t[i].d};
        h[++id]=(cost){i,n+3,(double)l-t[i].x-t[i].d};
        h[++id]=(cost){i,n+4,(double)r-t[i].y-t[i].d};
        for (int j=i+1;j<=n;j++) h[++id]={i,j,fabs(t[i]-t[j])};
    }
    last=1;
    sort(h+1,h+id+1); sort(w+1,w+m+1);
    for (int i=1;i<=4;i++)
        for (int j=1;j<=4;j++) map[i][j]=true;
    for (int i=1;i<=n+10;i++) f[i]=i;
    for (int i=1;i<=m;i++)
    {
        while (last<=id&&h[last].dis+eps<=w[i].d) {together(h[last].a,h[last].b);last++;}
        if (find(n+1)==find(n+3)) turn_off(1,3),turn_off(1,4),turn_off(2,3),turn_off(2,4);
        if (find(n+2)==find(n+4)) turn_off(1,2),turn_off(1,3),turn_off(2,4),turn_off(3,4);
        if (find(n+1)==find(n+2)) turn_off(1,2),turn_off(1,3),turn_off(1,4);
        if (find(n+2)==find(n+3)) turn_off(1,2),turn_off(2,4),turn_off(2,3);
        if (find(n+3)==find(n+4)) turn_off(3,1),turn_off(3,2),turn_off(3,4);
        if (find(n+4)==find(n+1)) turn_off(4,1),turn_off(4,2),turn_off(4,3);
        for (int j=1;j<=4;j++) ans[w[i].id][j]=map[w[i].from][j];
    }
    for (int i=1;i<=m;i++)
    {
        for (int j=1;j<=4;j++)
            if (ans[i][j]) putchar(j+'0');
        putchar('\n');
    }
    return 0;
}
```
$Please~give~a~like.~~Thanks~for~reading~my~passage.$

---

## 作者：123456zmy (赞：3)

~~好像此题我能查看的 AC 记录都是写的离线的？？？~~
___
观察发现，如果一个人不能从 $A$ 走到 $B$，那么比他半径大的人一定不能从 $A$ 走到 $B$，所以考虑预处理这些入口两两间所能通过的人的最大半径。

![](https://cdn.luogu.com.cn/upload/image_hosting/lxwpl544.png)

对每棵树和边界建点，然后对于每棵树求出其到其他所有点的距离作为边权建边。

上图建完边大概长这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/a1v59sfb.png)

我们按照边的长度由短到长加入这些边，起点和终点会将矩形的边界分为两段，当且仅当不能通过已有边从将这两段连通时可以从起点走到终点（对应上图就是 $l_1$ 与 $l_2,l_3,l_4$ 均不连通时可以从 $1$ 走到 $4$，其他情况同理）当加入一条边使其连通性改变时更新答案，询问时直接与数组内的值进行比较。

代码（因为询问都是整数所以将距离下取整不影响正确性，$O(n^2\log(n^2)+m)$）：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{int x,y,r;}a[2001];
struct e{int u,v,d;}b[5000001];
bool cmp(e i,e j){return i.d<j.d;}
int n,m,cnt,fa[5000001];
int dis(node i,node j){return sqrt((i.x-j.x)*(i.x-j.x)+(i.y-j.y)*(i.y-j.y));}
int ans[5][5],w,h;
int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
signed main()
{
	scanf("%lld%lld",&n,&m);
	scanf("%lld%lld",&w,&h);
	for(int i=1;i<=5000000;i++)fa[i]=i;
	for(int i=1;i<=n;i++)scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].r);
	for(int i=1;i<=4;i++)for(int j=1;j<i;j++)ans[i][j]=ans[j][i]=1e18;
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)b[++cnt]={i,j,dis(a[i],a[j])-a[i].r-a[j].r};
	for(int i=1;i<=n;i++)
	b[++cnt]={i,n+1,a[i].x-a[i].r},b[++cnt]={i,n+2,a[i].y-a[i].r},
	b[++cnt]={i,n+3,w-a[i].x-a[i].r},b[++cnt]={i,n+4,h-a[i].y-a[i].r};
	sort(b+1,b+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		fa[find(b[i].u)]=fa[find(b[i].v)],find(n+1),find(n+2),find(n+3),find(n+4);
		if(fa[n+2]==fa[n+1]||fa[n+2]==fa[n+3]||fa[n+2]==fa[n+4])ans[1][2]=min(ans[1][2],b[i].d);
		if(fa[n+1]==fa[n+2]||fa[n+1]==fa[n+3]||fa[n+1]==fa[n+4])ans[1][4]=min(ans[1][4],b[i].d);
		if(fa[n+3]==fa[n+1]||fa[n+3]==fa[n+2]||fa[n+3]==fa[n+4])ans[2][3]=min(ans[2][3],b[i].d);
		if(fa[n+4]==fa[n+1]||fa[n+4]==fa[n+2]||fa[n+4]==fa[n+3])ans[3][4]=min(ans[3][4],b[i].d);
		if(fa[n+1]==fa[n+3]||fa[n+1]==fa[n+4]||fa[n+2]==fa[n+3]||fa[n+2]==fa[n+4])ans[2][4]=min(ans[2][4],b[i].d);
		if(fa[n+1]==fa[n+2]||fa[n+1]==fa[n+3]||fa[n+4]==fa[n+2]||fa[n+4]==fa[n+3])ans[1][3]=min(ans[1][3],b[i].d);
	}
	while(m--)
	{
		int r,e;
		scanf("%lld%lld",&r,&e);
		for(int i=1;i<e;i++)if(ans[i][e]>=r*2)putchar(i+48);//注意输入的是半径需要乘2
		putchar(e+48);
		for(int i=e+1;i<=4;i++)if(ans[e][i]>=r*2)putchar(i+48);
		puts("");
	}
	return 0;
}
```

---

## 作者：WaReTle (赞：0)

这是一种**在线**的，复杂度 $O(n^2\log n+m)$ 的做法。

考虑什么情况下游客不能从一个出口到达另一个出口。

设 $dis(i,j)$ 表示第 $i$ 棵树和第 $j$ 棵树之间的欧几里得距离。

先建图。对于两棵树 $i$ 和 $j (i<j)$，在它们之间连一条边权为 $dis(i,j)-r[i]-r[j]$ 的边，表示**直径**不大于此边权的游客**有可能**通过这两棵树之间的缝隙。再新建 $4$ 个点表示地图的 $4$ 条边界，编号 $n+1$ 至 $n+4$。对于一棵树，在它和每个边界之间分别连一条边权为树的边界到公园的边界的距离的边，表示直径不大于此边权的游客有可能从这棵树和对应边界之间过去。

这样，不难发现以下结论：

对于某个游客，如果 $i$ 和 $j(n+1\le i<j\le n+4)$ 之间存在一条路径使得路径上的最大边权**小于**当前游客的直径，那么可以视作这两条边界之间有一堵墙阻挡这个游客通过，使得这两条边界的“一侧”和“另一侧”不连通。

举个例子：对于当前游客，假如上下边界之间存在这样的路径，那么从左边的入口（①和④）无法到达右边的出口（②和③）。

感性的证明：如果这样的路径存在，那么这个游客不可能从这条路径上的连续两个点通过，因此对于这个游客来说这条路径将公园分成两部分。

在处理出任两个边界之间的路径上的最大边权的最小值后大力分讨即可解决此问题。这一段用语言表述可能比较混乱，可以参考代码。

于是可以暴力建出所有边并按边权从小到大排序，用并查集维护四个边界所对应的点的联通情况（思想类似kruskal）。

回答询问时考虑当前游客受到的限制分类讨论即可。

代码

```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
typedef long long ll;
int n,m,w,h,x[2005],y[2005],r[2005],cnt,f[3005];
ll dis[5][5];//边界之间的路径上边权最大的边的最小值
const double eps=1e-9;
struct edge
{
	int a,b;
	double c;//事实上可以用long long，因为询问的半径都是整数
}e[5000005];
bool operator<(const edge&a,const edge&b)
{
	return a.c<b.c;
}
int fd(int x)
{
	return f[x]==x?x:f[x]=fd(f[x]);
}
void mer(int x,int y)
{
	x=fd(x),y=fd(y);
	if(x!=y)
		f[y]=x;
}
void solve(int r,int e)
{
	r*=2;//半径->直径
	for(int i=1;i<=4;++i)//这里用了并查集来判断边界的四个点的连通情况
		f[i]=i;       //两个边界连通则可以在它们之间连线阻挡游客
	for(int i=1;i<=4;++i)
		for(int j=i+1;j<=4;++j)
			if(dis[i][j]<r)
				mer(i,j);
	bool ok[5]={0,1,1,1,1};
	for(int i=1;i<=4;++i)
		if(fd(i)==fd(i%4+1))
			if(i!=e)
				ok[i]=0;
			else
				memset(ok,0,sizeof(ok));
	switch(e)//分类讨论部分，虽然长但是不难写
	{
		case 1:
			if(fd(2)==fd(4))
				ok[2]=ok[3]=0;
			if(fd(1)==fd(3))
				ok[3]=ok[4]=0;
			break;
		case 2:
			if(fd(1)==fd(3))
				ok[3]=ok[4]=0;
			if(fd(2)==fd(4))
				ok[1]=ok[4]=0;
			break;
		case 3:
			if(fd(2)==fd(4))
				ok[1]=ok[4]=0;
			if(fd(1)==fd(3))
				ok[1]=ok[2]=0;
			break;
		case 4:
			if(fd(1)==fd(3))
				ok[1]=ok[2]=0;
			if(fd(2)==fd(4))
				ok[2]=ok[3]=0;
			break;
	}
	ok[e]=1;
	for(int i=1;i<=4;++i)
		if(ok[i])
			putchar(i+'0');
	puts("");
}
ll di(int i,int j)
{
	ll a=1ll*(x[i]-x[j])*(x[i]-x[j])+1ll*(y[i]-y[j])*(y[i]-y[j]);
	return (ll)sqrt(a);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&w,&h);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&x[i],&y[i],&r[i]);
		e[++cnt]={i,n+1,(double)max(0,x[i]-r[i])+eps};
        //建树和边界之间的边
		e[++cnt]={i,n+2,(double)max(0,y[i]-r[i])+eps};
		e[++cnt]={i,n+3,(double)max(0,w-x[i]-r[i])+eps};
		e[++cnt]={i,n+4,(double)max(0,h-y[i]-r[i])+eps};
	}
	for(int i=1;i<=4;++i)
		for(int j=i+1;j<=4;++j)
			dis[i][j]=-1;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)//建树和树之间的边
			e[++cnt]={i,j,di(i,j)-r[i]-r[j]};
	for(int i=1;i<=n+4;++i)
		f[i]=i;
	sort(e+1,e+cnt+1);
	for(int i=1;i<=cnt;++i)//按边权从小到大加入边，用并查集维护连通情况
	{
		int x=fd(e[i].a),y=fd(e[i].b);
		double z=e[i].c;
		if(x!=y)
		{
			f[y]=x;
			for(int j=1;j<=4;++j)
				for(int k=j+1;k<=4;++k)
					if(dis[j][k]<0&&fd(n+j)==fd(n+k))
						dis[j][k]=z;
		}
	}
	for(int i=1;i<=m;++i)
	{
		int r,e;
		scanf("%d%d",&r,&e);
		solve(r,e);
	}
	return 0;
}
```

复杂度瓶颈在对边的排序。

---

## 作者：Purslane (赞：0)

## Solution

经典 Trick :

我们发现不同的游客的大小不一样 , 这很麻烦 .

那么想办法 , 把游客的大小转化成树的大小 . 

**最显然的方法 , 就是对于每个半径为 $r$ 的游客 , 让所有的树的半径加上 $r$  .** 如图 .

![Hv7bkQ.png](https://s4.ax1x.com/2022/02/21/Hv7bkQ.png)

这样我们就可以把游客看做点了 . 这是后可以判段四个角之间是否联通 . 方法参考普及组难度题目《奶酪》 , 把四条边也都当作一个点 .

当 A 与 B 不能联通有如下 3 种情况 :

![Hv7qYj.png](https://s4.ax1x.com/2022/02/21/Hv7qYj.png)

对于这道题 , 我们可以考虑离线 . 预处理出任意两棵树 ( 包括边界 ) 中间的路堵上所需的游客直径 . 拿一个指针扫描 , 然后判段连通性即可 . 注意根据题目 , 一个点总是可以到达其起点的 .

关于边界的编号 , 我们可以从最左开始逆时针编为 $n+1 \sim n+4$ , 这样更方便实现 .

code :

```cpp
const int MAXN=2000+10,MAXM=1e5+10;
struct Query {
	int idx,st,r;	
}qr[MAXM];
struct Union {
	int x,y;
	double r;	
}un[MAXN*MAXN];
inline bool cmp(const Query A,const Query B) {
	return A.r<B.r;	
}
inline bool Cmp(const Union A,const Union B) {
	return A.r<B.r;	
}
int n,m,w,h,ans[MAXM][5],fa[MAXN];
int cnt,x[MAXN],y[MAXN],r[MAXN];
inline int find(const int k) {
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);	
}
inline double distance(const double x,const double y,const double X,const double Y) {
	return sqrt((x-X)*(x-X)+(y-Y)*(y-Y));	
}
inline void init(void) {
	for(int i=1;i<=n+4;i++) fa[i]=i;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<i;j++) un[++cnt]=Union{i,j,distance(x[i],y[i],x[j],y[j])-r[i]-r[j]};
		un[++cnt]=Union{i,n+1,x[i]-r[i]};
		un[++cnt]=Union{i,n+2,y[i]-r[i]};
		un[++cnt]=Union{i,n+3,w-x[i]-r[i]};
		un[++cnt]=Union{i,n+4,h-y[i]-r[i]};
	}
	sort(un+1,un+cnt+1,Cmp);
	return ;	
}
inline void Merge(int x,int y) {
    x=find(x),y=find(y),fa[x]=y;
    return ;
}
inline int trapped(const int idx) { //困在拐角出不去
    return find(n+idx)==find(n+idx%4+1);
}
inline int cross_row(void) { //横向
    return find(n+1)==find(n+3);
}
inline int cross_line(void) { //纵向
    return find(n+2)==find(n+4);
}
inline int able_to_reach(const int idx1,const int idx2) {
    if(idx1==idx2) return 1;
	if(trapped(idx1)||trapped(idx2)) return 0;
    if(abs(idx1-idx2)==2) {
        if(cross_line()||cross_row()) return 0;
        return 1;
    }
    if(idx1+idx2==3||idx1+idx2==7) {
        if(cross_line()) return 0;
        return 1;
    }
    if(cross_row()) return 0;
    return 1;
}
signed main() {
	n=read(),m=read(),w=read(),h=read();
	for(int i=1;i<=n;i++) x[i]=read(),y[i]=read(),r[i]=read();
	init();
	for(int i=1,st,r;i<=m;i++) r=read(),st=read(),qr[i]=Query{i,st,r};
    sort(qr+1,qr+m+1,cmp);
    int pos=0;
    for(int i=1;i<=m;i++) {
        while(pos<cnt&&un[pos+1].r-2*qr[i].r<=-1e-7) pos++,Merge(un[pos].x,un[pos].y);
        for(int j=1;j<=4;j++) if(able_to_reach(qr[i].st,j)) ans[qr[i].idx][j]=1;
    }
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=4;j++) if(ans[i][j]) printf("%d",j);
        printf("\n");
    }
	return 0;
}
```

PS :

1. 注意数组大小 .

2. 这种我一眼爆切的题目不大可能是黑题吧 ......

---

## 作者：破忆 (赞：0)

[P4675 [BalticOI 2016 day1]Park](https://www.luogu.com.cn/problem/P4675)

## 【题意】

有若干坐标为 $(x,y)$、半径为 $r$ 障碍，和若干半径为 $k$ 的游客。

每个游客从地图的某个角落出发，询问他们能到达哪些角落。

## 【分析】

### 什么情况下半径为 $k$ 的游客不能到达另一个角落？

必然是某几个障碍物组成了一道“屏障”，阻止该游客经过。

屏障中的相邻两个障碍之间的间隙都小于 $2k$，头尾障碍物与边界的间隙也小于 $2k$。

### 怎么判断是否存在这样一个“屏障”？

若将两个障碍（或障碍与边界）联通定义为二者间隙小于 $2k$。

则存在屏障就等价于某两个边界联通~~银河将牛郎和织女分隔~~。

连通性可以用**并查集**维护。

### 怎么处理多组询问？

若游客半径递增，则需要在合并一些联通快。

先求出所有障碍对的距离，排序。

把询问**离线**下来，排序。

对于每个询问，合并所有距离小于当前游客直径的障碍对所在的联通块，判断边界联通性即可。

### 一个小细节

此题eps太小会炸精度，调到 $1e-4$ 能过。

## 【算法】

离线+并查集

## 【代码】

```cpp
#include<bits/stdc++.h>
#define LL long long 
#define DB double
const int maxn=2005,maxm=1e5+5,maxe=2e6+5;
int n,m,w,h;
struct obj{
	int x,y,r,id;
}a[maxn],a0[maxn],a1[maxn];
bool cmp0(obj i,obj j){
	return i.x<j.x;
}
bool cmp1(obj i,obj j){
	return i.y<j.y;
}
struct data{
	int x,y;
	DB r;
	bool operator <(data b)const{return r<b.r;}
}e[maxe+maxn*4];
struct hum{
	int id,E,r;
	bool operator <(hum b)const{return r<b.r;} 
}b[maxm];
int tot;
int cnt;
DB sqr(int x){
	return (DB)x*x;
}
DB dis(int i,int j){
	return sqrt(sqr(a[i].x-a[j].x)+sqr(a[i].y-a[j].y))-a[i].r-a[j].r;
}
int fa[maxn+5];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void merge(int x,int y){
	int fx=getfa(x),fy=getfa(y);
	if(fx!=fy) fa[fx]=fy;
}
bool G(int x,int y){
	int fx=getfa(x),fy=getfa(y);
	return fx==fy;
}
int U,D,L,R;
bool ans[maxm][5];
void check(int i){
	#define ID b[i].id
	if(b[i].E==1){
		if(G(L,D)) ans[ID][2]=ans[ID][3]=ans[ID][4]=1;else
		if(G(U,D)) ans[ID][2]=ans[ID][3]=1;else
		if(G(L,R)) ans[ID][3]=ans[ID][4]=1;
		else{
			if(G(L,U)) ans[ID][4]=1;
			if(G(U,R)) ans[ID][3]=1;
			if(G(R,D)) ans[ID][2]=1;
		}
	}else
	if(b[i].E==2){
		if(G(R,D)) ans[ID][1]=ans[ID][3]=ans[ID][4]=1;else
		if(G(U,D)) ans[ID][1]=ans[ID][4]=1;else
		if(G(L,R)) ans[ID][3]=ans[ID][4]=1;
		else{
			if(G(L,U)) ans[ID][4]=1;
			if(G(U,R)) ans[ID][3]=1;
			if(G(L,D)) ans[ID][1]=1;
		}
	}else
	if(b[i].E==3){
		if(G(U,R)) ans[ID][1]=ans[ID][2]=ans[ID][4]=1;else
		if(G(U,D)) ans[ID][1]=ans[ID][4]=1;else
		if(G(L,R)) ans[ID][1]=ans[ID][2]=1;
		else{
			if(G(L,U)) ans[ID][4]=1;
			if(G(D,R)) ans[ID][2]=1;
			if(G(L,D)) ans[ID][1]=1;
		}
	}else
	if(b[i].E==4){
		if(G(L,U)) ans[ID][1]=ans[ID][2]=ans[ID][3]=1;else
		if(G(U,D)) ans[ID][2]=ans[ID][3]=1;else
		if(G(L,R)) ans[ID][1]=ans[ID][2]=1;
		else{
			if(G(R,U)) ans[ID][3]=1;
			if(G(D,R)) ans[ID][2]=1;
			if(G(L,D)) ans[ID][1]=1;
		}
	}
}
const DB eps=1e-4;
void work(){
	for(int i=1;i<=n;i++) fa[i]=i;
	fa[U]=U,fa[D]=D,fa[L]=L,fa[R]=R;
	for(int i=1,j=1;i<=m;i++){
		while(j<=cnt&&e[j].r-b[i].r*2<=-eps) merge(e[j].x,e[j].y),j++;
		check(i);
	}
}
void init(){
	scanf("%d%d%d%d",&n,&m,&w,&h);
	for(int i=1,x,y,r;i<=n;i++){
		scanf("%d%d%d",&x,&y,&r);
		a[i]=a0[i]=a1[i]=(obj){x,y,r,i};
	}
	std::sort(a0+1,a0+1+n,cmp0);
	std::sort(a1+1,a1+1+n,cmp1);
	for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++) e[++cnt]=(data){i,j,dis(i,j)};
	L=n+1,D=n+2,R=n+3,U=n+4;
	for(int i=1;i<=n;i++){
		e[++cnt]=(data){i,L,(DB)a[i].x-a[i].r};
		e[++cnt]=(data){i,D,(DB)a[i].y-a[i].r};
		e[++cnt]=(data){i,R,(DB)w-a[i].x-a[i].r};
		e[++cnt]=(data){i,U,(DB)h-a[i].y-a[i].r};
	}
	std::sort(e+1,e+1+cnt);
	for(int i=1,r,E;i<=m;i++){
		scanf("%d%d",&r,&E);
		b[i]=(hum){i,E,r};
	}
	std::sort(b+1,b+1+m);
}
void print(){
	for(int i=1;i<=m;i++){
		for(int j=1;j<=4;j++) if(!ans[i][j]) printf("%d",j);
		putchar(10);
	} 
}
int main(){
    #ifndef ONLINE_JUDGE
	freopen("P4675.in","r",stdin);
	freopen("P4675.out","w",stdout);
	#endif
	init();
	work();
	print();
	return 0;
}
```


---

