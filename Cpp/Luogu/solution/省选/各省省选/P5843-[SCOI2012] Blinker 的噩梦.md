# [SCOI2012] Blinker 的噩梦

## 题目描述

一天 Blinker 醒来，发现自己成为了一个二维世界的点，而且被标记上了一个奇怪的值。

这个世界是由 $N$ 个边界互不相交（且不相切）的图形组成，这里图形仅包括圆和凸多边形。每个图形还有一个权值。每次 Blinker 走进或走出某个图形时（相切时经过不算），Blinker 的标记值就会被异或上那个值。

现在，我们记录了 Blinker 在这个世界的 $M$ 天的信息。每天可能发生两种事情，一种是某个图形的权值更改为某个值；另一种是 Blinker 从某个点走到另一个点。 

我们假设 Blinker 首次出发前的标记值为 $0$，我们希望知道他每次到达目的地后的标记值。

## 说明/提示

**样例解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/mj50qefg.png)

样例的世界形如上图：

第一天 Binker 的初始标记值为 $0$，可能从 $A$ 沿直线走到 $B$，或者他绕过圆走到 $B$，他的标记值最终都保持不变为 $0$（假设沿直线从 $A$ 走到 $B$，共穿过 $4$ 次边界，Binker 的标记值变化过程为 $1,3,1,0$）;

第二天 Binker 的初始标记值为 $0$，他通过某种不经过图形边界的方法到达了 $C$ 点（即 Binker 瞬间移动或闪烁），然后从 $C$ 沿某种路径走到 $D$，这时他的标记值变为 $2$；

第三天圆的权值变为 $1005$；

第四天 Binker 的初始标记值为 $2$，他再次回到 $C$，并再次从 $C$ 走到 $D$，这时他的标记值又变为 $0$。

**数据范围**
- 对于 $30\%$ 的数据，$1 \le M \le 10.00$，凸多边形的点数加上圆的个数小于等于 $1000$；
- 对于 $100\%$ 的数据，$1 \le N \le 10^5$，$1 \le M \le 10^5$，单个凸多边形的点数小于等于 $34$。图形互不相交，且 Binker 的出发点和目的地不在图形的边界。

## 样例 #1

### 输入

```
2 4
C 0 0 2 1
P 4 -1 -1 -1 1 1 1 1 -1 2
Q -2 -2 2 2
Q -1.5 0 0.0 0.0
C 1 1005
Q -1.5 0 0.0 0.0```

### 输出

```
0
2
0```

# 题解

## 作者：hsfzLZH1 (赞：12)

一道很好的提高组数据结构综合题。（强烈推荐！）

平衡树维护扫描线+线段树或树状数组维护树链剖分

### 题目大意

给定 $n$ 个 **互不相交** 的圆或凸多边形，每个图形还有一个权值 $v$ ， $m$ 次操作：

`Q x0 y0 x1 y1` ： 查询从 $(x0,y0)$ 到 $(x1,y1)$ 的线段所经过的图形的边界的异或和。这个答案要异或上一个询问的答案。保证 $(x0,y0)$ 和 $(x1,y1)$ 均不在图形的边界上。

`C i v` ： 将第 $i$ 个给出的图形的权值改为 $v$ 。

$1\le n\le 10^5,1\le m\le 10^5$ ，单个凸多边形的点数 $\le 34$ 。

凸多边形的顶点坐标按顺时针顺序给出。

### 树链剖分部分

优先考虑这一部分有助于我们明晰扫描线部分要维护哪些值。

由于异或的性质，题目所求等价于求任意一条从 $(x0,y0)$ 到 $(x1,y1)$ 的任意曲线经过的图形边界的权值和。将这条直线特殊化为从 $(x0,y0)$ 走到平面内不在任何一个图形内的地方，再从这个地方走到 $(x1,y1)$ 的权值和。这样可以 **将一对点的询问拆成两个对单点的询问** 。

由于给出的图形互不相交，则两个图形只有相离和包含两种情况，则它们之间的相互包含关系构成了一棵 **树** （若一个图形 $A$ 完全包含另一个图形 $B$ ，则 $A$ 在树上为 $B$ 的祖先，再设一个超级根节点表示整个平面）。

假设我们已经通过扫描线预处理出了这棵树，和包含每个询问中的点的最小图形。令树上一个点的权值为该点对应图形的权值。一个点走到平面内不在任何一个图形内的区域的权值异或和，为该点所在最小图形对应点到根的路径异或和。

树上单点修改，树上查询路径异或和，这一部分可以用线段树或树状数组维护树链剖分实现。参考代码中用的是线段树实现。

### 扫描线部分

由上一部分可知，扫描线部分要求出图形包含关系的树，和每个点最小被包含在哪个图形内。

考虑以 $x$ 坐标为时间进行扫描线。每个图形有贡献的时间段就是该图形的最左和最右顶点的 $x$ 坐标之间的区间。我们在左顶点 $x$ 坐标插入这个图形的上下边界，在右顶点 $x$ 坐标删除这个图形的上下边界。

在插入一个图形 $a$ 时，求出在它 **下方且最近** 的图形边界。设下方的边界属于图形 $b$ 。若这个边界是 $b$ 的上边界，则恰好包含 $a$ 的最小图形应是恰好包含 $b$ 的最小图形；若是下边界，则恰好包含 $a$ 的最小图形应是 $b$ 。恰好包含 $a$ 的最小图形在树上就是 $a$ 的父亲。

对于一个点，我们也可以求出它下方的最近的图形边界，用相同的方法求出包含该点的最小图形。

我们发现在时间变化后，每个边界的 $y$ 坐标都发生了变化，这个变化不可维护。但是，由于图形互不相交，边界之间的排列顺序不会发生变化。我们可以用平衡树来维护边界的排列顺序，在查询时只需求出当前结点对应的边界的 $y$ 坐标值，来确定是向左还是向右走。

总的时间复杂度为 $O((n+m)\log (n+m))$ ，空间复杂度为 $O(n+m)$ 。

### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
const int maxn=400010;
const double inf=1e18;
const double eps=1e-9;
bool eq(double x,double y){return fabs(x-y)<=eps;}
int n,m,tid,nm[maxn][3],lst;
char op;
struct Query
{
	char op;
	double xa,ya,xb,yb;
	int aid,bid,id,v;
}s[maxn];
struct Node
{
	double x,y;int col;
}a[maxn];
struct Poly
{
	char op;
	int v,l;
	double x[36],y[36],r;
	double upper(double t)
	{
		if(op=='C')return y[0]+sqrt(max(0.0,r*r-(x[0]-t)*(x[0]-t)));
		double ret=-inf;
		for(int i=1;i<l;i++)
		{
			if(eq(x[i],x[i+1])&&eq(x[i],t))ret=max(ret,max(y[i],y[i+1])); 
			else if(x[i]<=t&&t<=x[i+1])ret=max(ret,y[i]+(t-x[i])/(x[i+1]-x[i])*(y[i+1]-y[i]));
			else if(x[i+1]<=t&&t<=x[i])ret=max(ret,y[i+1]+(t-x[i+1])/(x[i]-x[i+1])*(y[i]-y[i+1]));
		}
		if(eq(x[1],x[l])&&eq(x[1],t))ret=max(ret,max(y[1],y[l]));
		else if(x[l]<=t&&t<=x[1])ret=max(ret,y[l]+(t-x[l])/(x[1]-x[l])*(y[1]-y[l]));
		else if(x[1]<=t&&t<=x[l])ret=max(ret,y[1]+(t-x[1])/(x[l]-x[1])*(y[l]-y[1]));
		return ret;
	}
	double lower(double t)
	{
		if(op=='C')return y[0]-sqrt(max(0.0,r*r-(x[0]-t)*(x[0]-t)));
		double ret=inf;
		for(int i=1;i<l;i++)
		{
			if(eq(x[i],x[i+1])&&eq(x[i],t))ret=min(ret,min(y[i],y[i+1])); 
			else if(x[i]<=t&&t<=x[i+1])ret=min(ret,y[i]+(t-x[i])/(x[i+1]-x[i])*(y[i+1]-y[i]));
			else if(x[i+1]<=t&&t<=x[i])ret=min(ret,y[i+1]+(t-x[i+1])/(x[i]-x[i+1])*(y[i]-y[i+1]));
		}
		if(eq(x[1],x[l])&&eq(x[1],t))ret=min(ret,min(y[1],y[l]));
		else if(x[l]<=t&&t<=x[1])ret=min(ret,y[l]+(t-x[l])/(x[1]-x[l])*(y[1]-y[l]));
		else if(x[1]<=t&&t<=x[l])ret=min(ret,y[1]+(t-x[1])/(x[l]-x[1])*(y[l]-y[1]));
		return ret;
	}
}po[maxn];
int cur;
struct Oper
{
	int op,id;double t;
	bool operator<(Oper x)const{return t==x.t?op<x.op:t<x.t;}
}q[maxn];
struct FHQ
{
	int rt,cur,siz[maxn],fa[maxn],lc[maxn],rc[maxn],id[maxn],op[maxn];
	int newnode(int i,int o){cur++;siz[cur]=1;id[cur]=i;op[cur]=o;return cur;}
	void maintain(int o){siz[o]=siz[lc[o]]+siz[rc[o]]+1;}
	int merge(int x,int y)
	{
		if((!x)||(!y))return x+y;
		if(rand()%(siz[x]+siz[y])<siz[x]){rc[x]=merge(rc[x],y);fa[rc[x]]=x;maintain(x);return x;}
		else{lc[y]=merge(x,lc[y]);fa[lc[y]]=y;maintain(y);return y;}
	}
	void split_siz(int o,int k,int&x,int&y)
	{
		if(!o){x=y=0;return;}
		if(k<=siz[lc[o]]){y=o;fa[lc[y]]=0;split_siz(lc[y],k,x,lc[y]);fa[lc[y]]=y;maintain(y);}
		else{x=o;fa[rc[x]]=0;split_siz(rc[x],k-siz[lc[o]]-1,rc[x],y);fa[rc[x]]=x;maintain(x);}
	}
	void split(int o,double t,double v,int&x,int&y)
	{
		if(!o){x=y=0;return;}
		double u;if(op[o]==1)u=po[id[o]].upper(t);else u=po[id[o]].lower(t);
		if(u>v){x=o;fa[rc[x]]=0;split(rc[x],t,v,rc[x],y);fa[rc[x]]=x;maintain(x);}
		else{y=o;fa[lc[y]]=0;split(lc[y],t,v,x,lc[y]);fa[lc[y]]=y;maintain(y);}
	}
	int rnk(int o)
	{
		int ret=siz[lc[o]]+1;
		while(fa[o]){if(o==rc[fa[o]])ret+=siz[lc[fa[o]]]+1;o=fa[o];}
		return ret;
	}
	int leftist(int o){while(lc[o])o=lc[o];return o;}
}st;
int cnt,h[maxn],nxt[maxn],p[maxn];
void add_edge(int x,int y)
{
	cnt++;
	nxt[cnt]=h[x];
	h[x]=cnt;
	p[cnt]=y;
}
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],clk,dfn[maxn],rnk[maxn];
void dfs1(int x,int f)
{
	siz[x]=1;
	for(int j=h[x];j;j=nxt[j])if(p[j]!=f)
	{
		fa[p[j]]=x;
		dep[p[j]]=dep[x]+1;
		dfs1(p[j],x);
		siz[x]+=siz[p[j]];
		if((!son[x])||(siz[p[j]]>siz[son[x]]))son[x]=p[j];
	}
}
void dfs2(int x,int t)
{
	top[x]=t;
	dfn[x]=++clk;rnk[clk]=x;
	if(son[x])dfs2(son[x],t);
	for(int j=h[x];j;j=nxt[j])if(p[j]!=fa[x]&&p[j]!=son[x])dfs2(p[j],p[j]);
}
int sum[maxn];
#define lc (o<<1)
#define rc (o<<1|1)
void update(int o,int l,int r,int x,int v)
{
	if(l==r){sum[o]=v;return;}
	int mid=(l+r)>>1;
	if(x<=mid)update(lc,l,mid,x,v);
	else update(rc,mid+1,r,x,v);
	sum[o]=sum[lc]^sum[rc];
}
int query(int o,int l,int r,int ql,int qr)
{
	if(r<ql||l>qr)return 0;
	if(ql<=l&&r<=qr)return sum[o];
	int mid=(l+r)>>1;
	return query(lc,l,mid,ql,qr)^query(rc,mid+1,r,ql,qr); 
}
int qdist(int x)
{
	int ret=0;
	while(x)
	{
		ret^=query(1,1,n+1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf(" %c",&op);po[i].op=op;
		if(op=='C')scanf("%lf%lf%lf%d",&po[i].x[0],&po[i].y[0],&po[i].r,&po[i].v),q[++cur]={1,i,po[i].x[0]-po[i].r},q[++cur]={2,i,po[i].x[0]+po[i].r};
		if(op=='P')
		{
			scanf("%d",&po[i].l);
			double minx=inf,maxx=-inf;
			for(int j=1;j<=po[i].l;j++)scanf("%lf%lf",po[i].x+j,po[i].y+j),minx=min(minx,po[i].x[j]),maxx=max(maxx,po[i].x[j]);
			q[++cur]={1,i,minx};q[++cur]={2,i,maxx};
			scanf("%d",&po[i].v);
		}
	}
	tid=0;
	for(int i=1;i<=m;i++)
	{
		scanf(" %c",&s[i].op);
		if(s[i].op=='Q')
		{
			scanf("%lf%lf%lf%lf",&s[i].xa,&s[i].ya,&s[i].xb,&s[i].yb);
			s[i].aid=++tid;q[++cur]={3,tid,s[i].xa};a[tid]={s[i].xa,s[i].ya};
			s[i].bid=++tid;q[++cur]={3,tid,s[i].xb};a[tid]={s[i].xb,s[i].yb};
		}
		else scanf("%d%d",&s[i].id,&s[i].v);
	}
	sort(q+1,q+cur+1);
	for(int i=1;i<=cur;i++)
	{
		if(q[i].op==1)
		{
			double v=po[q[i].id].upper(q[i].t);
			int a,b,c,d;
			st.split(st.rt,q[i].t,v,a,c);
			if(!st.siz[c])fa[q[i].id]=n+1;
			else
			{
				d=st.leftist(c);
				if(st.op[d]==1)fa[q[i].id]=fa[st.id[d]];
				else fa[q[i].id]=st.id[d];
			}
			add_edge(q[i].id,fa[q[i].id]);add_edge(fa[q[i].id],q[i].id);
			b=st.merge(st.newnode(q[i].id,1),st.newnode(q[i].id,2));
			nm[q[i].id][1]=st.cur-1;nm[q[i].id][2]=st.cur;
			st.rt=st.merge(st.merge(a,b),c);
		}
		else if(q[i].op==2)
		{
			int a,b,c,d;
			d=st.rnk(nm[q[i].id][1]);
			st.split_siz(st.rt,d-1,a,b);
			st.split_siz(b,1,b,c);
			st.rt=st.merge(a,c);
			d=st.rnk(nm[q[i].id][2]);
			st.split_siz(st.rt,d-1,a,b);
			st.split_siz(b,1,b,c);
			st.rt=st.merge(a,c);
		}
		else
		{
			double v=a[q[i].id].y;
			int A,B,C;
			st.split(st.rt,q[i].t,v,A,B);
			if(!st.siz[B])a[q[i].id].col=n+1;
			else
			{
				C=st.leftist(B);
				if(st.op[C]==1)a[q[i].id].col=fa[st.id[C]];
				else a[q[i].id].col=st.id[C];
			}
			st.rt=st.merge(A,B);
		}
	}
	dep[n+1]=1;dfs1(n+1,0);dfs2(n+1,n+1);
	for(int i=1;i<=n;i++)update(1,1,n+1,dfn[i],po[i].v);
	for(int i=1;i<=m;i++)
	{
		if(s[i].op=='Q')printf("%d\n",lst^=(qdist(a[s[i].aid].col)^qdist(a[s[i].bid].col)));
		else update(1,1,n+1,dfn[s[i].id],s[i].v);
	}
	return 0;
}
```

---

## 作者：panyf (赞：3)

一道强行二合一题。

首先根据题目中图形不交的性质，想到建树，每个图形的父亲表示包含其的最小图形。

建树的过程可以用扫描线。

一条与 $y$ 轴平行的直线与某个图形至多有两个交点，其中 $y$ 坐标小的所有点称为上边界，$y$ 坐标大的称为下边界。

给定直线的 $x$ 坐标如何求交点的纵坐标？圆可以直接套解析式，多边形可以枚举每条边判断，或者二分。此题点数不超过 $34$ 所以代码中是枚举。

从左到右扫描，在一个图形的左端点加入上下边界，右端点删除。

根据图形不交的性质，求一个图形的父亲相当于求其某个顶点所在的最小图形。

将所有边界按 $y$ 坐标排序，二分找到这个点下方的第一个边界。如果是图形 $i$ 的上边界，则所求为 $fa_i$；如果是下边界，则所求为 $i$。

需要支持插入删除求后继，用 set 实现。

建出树之后，问题转化为单点修改，求某个点到根路径异或和。

求前缀异或之后，相当于子树异或一个值，单点查询，dfs 序 + 树状数组即可。

时间复杂度 $O((nl+m)\log n)$ 或者 $O((n\log l+m)\log n)$，取决于求交点的方式。

```cpp
#include<bits/stdc++.h>
using namespace std;
using db=double;
const db eps=1e-7;
const int N=1e5+3,M=N*3;
db w,u;
struct C{//圆
	db x,y,r;
	void in(){scanf("%lf%lf%lf",&x,&y,&r),r=max(r,eps);}
	db up(){return y-sqrt(abs(r*r-(x-w)*(x-w)));}
	db dn(){return y+sqrt(abs(r*r-(x-w)*(x-w)));}
};
struct P{//多边形
	int l;db x[37],y[37];
	void in(){
		scanf("%d",&l);
		for(int i=0;i<l;++i)scanf("%lf%lf",x+i,y+i);
		x[l]=x[0],y[l]=y[0];
	}
	db up(){
		db r=1e99;
		for(int i=0;i<l;++i)if((x[i]-eps<w&&x[i+1]+eps>w)||(x[i+1]-eps<w&&x[i]+eps>w))r=min(r,abs(x[i]-x[i+1])<eps?min(y[i],y[i+1]):(y[i+1]-y[i])/(x[i+1]-x[i])*(w-x[i])+y[i]);
		return r;
	}
	db dn(){
		db r=-1e99;
		for(int i=0;i<l;++i)if((x[i]-eps<w&&x[i+1]+eps>w)||(x[i+1]-eps<w&&x[i]+eps>w))r=max(r,abs(x[i]-x[i+1])<eps?max(y[i],y[i+1]):(y[i+1]-y[i])/(x[i+1]-x[i])*(w-x[i])+y[i]);
		return r;
	}
};
struct G{//图形
	bool o;C c;P p;
	void in(){char t;scanf(" %c",&t),t=='C'?c.in():(o=1,p.in());}
	db up(){return o?p.up():c.up();}
	db dn(){return o?p.dn():c.dn();}
}g[N];
db get(int x){return x<M?(x<N?g[x].up():g[x-N].dn()):u;}
struct cmp{
	bool operator()(int x,int y)const{
		if(x+N==y||y+N==x)return x<y;
		return get(x)<get(y);
	}
};
struct D{//点
	db x,y;int id,o;
	bool operator<(D a)const{return x<a.x;}
}d[M];
struct Q{bool o;int u,v;}q[N];//询问
set<int,cmp>s;
int v[N],sv[N],fa[N],n,id,l[N],r[N],t[N];
basic_string<int>e[N];
void dfs(int x){for(int i:e[x])l[i]=++id,sv[i]=sv[x]^v[i],dfs(i),r[i]=id+1;}
void add(int x,int v){for(;x<=n;x+=x&-x)t[x]^=v;}
int sum(int x){int r=0;for(;x;x-=x&-x)r^=t[x];return r;}//树状数组部分
int main(){
	int m,i,j,k,t=0,ans=0;
	char c;
	db x0,y0,x1,y1;
	scanf("%d%d",&n,&m),g[0].c.r=1e99;
	for(i=1;i<=n;++i)if(g[i].in(),scanf("%d",v+i),g[i].o){
		for(j=0,x0=1e99,x1=-1e99;j<g[i].p.l;++j){
			if(x0>g[i].p.x[j])x0=g[i].p.x[j],y0=g[i].p.y[j];
			if(x1<g[i].p.x[j])x1=g[i].p.x[j],y1=g[i].p.y[j];
		}
		d[++t]={x0,y0,i,0},d[++t]={x1,y1,i,3};
	}else d[++t]={g[i].c.x-g[i].c.r,g[i].c.y,i,0},d[++t]={g[i].c.x+g[i].c.r,g[i].c.y,i,3};
	for(i=1;i<=m;++i)if(scanf(" %c",&c),c=='Q')scanf("%lf%lf%lf%lf",&x0,&y0,&x1,&y1),d[++t]={x0,y0,i,1},d[++t]={x1,y1,i,2};
	else q[i].o=1,scanf("%d%d",&q[i].u,&q[i].v);
	for(sort(d+1,d+t+1),s.insert(0),s.insert(N),i=1;i<=t;++i)if(k=d[i].id,d[i].o>2)s.erase(k),s.erase(k+N);else{
		w=d[i].x,u=d[i].y,j=*s.upper_bound(M),j=j<N?fa[j]:j-N;
		if(!d[i].o)fa[k]=j,e[j]+=k,s.insert(k),s.insert(k+N);
		else if(d[i].o==1)q[k].u=j;else q[k].v=j;
	}//扫描线部分
	for(dfs(0),i=1;i<=m;++i)if(q[i].o)j=q[i].u,k=q[i].v^v[j],v[j]=q[i].v,add(l[j],k),add(r[j],k);
	else printf("%d\n",ans^=sv[q[i].u]^sv[q[i].v]^sum(l[q[i].u])^sum(l[q[i].v]));
	return 0;
}
```


---

