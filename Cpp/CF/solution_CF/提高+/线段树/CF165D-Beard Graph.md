# Beard Graph

## 题目描述

Let's define a non-oriented connected graph of $ n $ vertices and $ n-1 $ edges as a beard, if all of its vertices except, perhaps, one, have the degree of 2 or 1 (that is, there exists no more than one vertex, whose degree is more than two). Let us remind you that the degree of a vertex is the number of edges that connect to it.

Let each edge be either black or white. Initially all edges are black.

You are given the description of the beard graph. Your task is to analyze requests of the following types:

- paint the edge number $ i $ black. The edge number $ i $ is the edge that has this number in the description. It is guaranteed that by the moment of this request the $ i $ -th edge is white
- paint the edge number $ i $ white. It is guaranteed that by the moment of this request the $ i $ -th edge is black
- find the length of the shortest path going only along the black edges between vertices $ a $ and $ b $ or indicate that no such path exists between them (a path's length is the number of edges in it)

The vertices are numbered with integers from $ 1 $ to $ n $ , and the edges are numbered with integers from $ 1 $ to $ n-1 $ .

## 说明/提示

In the first sample vertices $ 1 $ and $ 2 $ are connected with edge number $ 1 $ , and vertices $ 2 $ and $ 3 $ are connected with edge number $ 2 $ . Before the repainting edge number $ 2 $ each vertex is reachable from each one along the black edges. Specifically, the shortest path between $ 1 $ and $ 3 $ goes along both edges.

If we paint edge number $ 2 $ white, vertex $ 3 $ will end up cut off from other vertices, that is, no path exists from it to any other vertex along the black edges.

## 样例 #1

### 输入

```
3
1 2
2 3
7
3 1 2
3 1 3
3 2 3
2 2
3 1 2
3 1 3
3 2 3
```

### 输出

```
1
2
1
1
-1
-1
```

## 样例 #2

### 输入

```
6
1 5
6 4
2 3
3 5
5 6
6
3 3 4
2 5
3 2 6
3 1 2
2 3
3 3 1
```

### 输出

```
3
-1
3
2
```

# 题解

## 作者：doby (赞：8)

树上对链的操作，可以用树链剖分

把点权下推到同一条边上深度更大的点

黑边将对应点权赋为0，白边将对应点权赋为1

一条重链上黑点的个数为dfn[]-dfn[top[]]+1

如果两点间路径上点权的和大于0，说明有白边

两点间LCA所代表的边不在两点间的路径上，在统计时需要去除
```cpp
#include<cstdio>
using namespace std;
int n,m,opt,x,y,cnt,tot,u[100010],v[100010],h[100010],dad[100010],top[100010],dep[100010],size[100010],son[100010],id[100010],out;
char c;
struct Edge
{
	int to,next;
}e[200010];
struct SegT
{
	int s;
}t[400010];
int read()
{
	out=0,c=getchar();
	while(c<48||c>57){c=getchar();}
	while(c>=48&&c<=57){out=(out<<3)+(out<<1)+(c&15),c=getchar();}
	return out;
}
void Add(int x,int y)
{	
	e[++cnt].next=h[x],
	e[cnt].to=y,
	h[x]=cnt;
}
void DFS1(int x)
{
	dep[x]=dep[dad[x]]+1,size[x]=1;
	for(int i=h[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(y^dad[x])
		{
			dad[y]=x;
			DFS1(y);
			size[x]+=size[y],
			son[x]=size[y]>size[son[x]]?y:son[x];
		}
	}
}
void DFS2(int x)
{
	id[x]=++tot,
	top[x]=x==son[dad[x]]?top[dad[x]]:x;
	if(!son[x]){return;}
	DFS2(son[x]);
	for(int i=h[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(y^dad[x]&&y^son[x]){DFS2(y);}
	}
}
void DFS(int x)
{
	DFS1(x);
	DFS2(x);
}
void Pushup(int k)
{
	t[k].s=t[k<<1].s+t[k<<1|1].s;
}
void Change(int k,int l,int r,int p,int x)
{
	if(l==r)
	{
		t[k].s=x;
		return;
	}
	int mid=l+r>>1;
	if(p<=mid){Change(k<<1,l,mid,p,x);}
	else{Change(k<<1|1,mid+1,r,p,x);}
	Pushup(k);
}
int Query(int k,int l,int r,int ll,int rr)
{
	if(r<ll||rr<l){return 0;}
	if(ll<=l&&r<=rr){return t[k].s;}
	int mid=l+r>>1;
	return Query(k<<1,l,mid,ll,rr)+Query(k<<1|1,mid+1,r,ll,rr);
}
int LCA(int x,int y)
{
	int ans=0,now;
	while(top[x]^top[y])
	{
		if(dep[top[x]]<dep[top[y]]){x^=y,y^=x,x^=y;}
		now=Query(1,1,n,id[top[x]],id[x]);
		if(now){return -1;}
		ans+=id[x]-id[top[x]]+1,
		x=dad[top[x]];
	}
	if(dep[x]>dep[y]){x^=y,y^=x,x^=y;}
	now=Query(1,1,n,id[x]+1,id[y]);
	if(now){return -1;}
	ans+=id[y]-id[x];
	return ans;
}
int main()
{
	n=read();
	for(int i=1;i<n;++i)
	{
		u[i]=read(),v[i]=read();
		Add(u[i],v[i]);Add(v[i],u[i]);
	}
	DFS(1);
	m=read();
	while(m--)
	{
		opt=read();
		if(opt==1)
		{
			x=read();
			if(dep[u[x]]>dep[v[x]]){Change(1,1,n,id[u[x]],0);}
			else{Change(1,1,n,id[v[x]],0);}
		}
		if(opt==2)
		{
			x=read();
			if(dep[u[x]]>dep[v[x]]){Change(1,1,n,id[u[x]],1);}
			else{Change(1,1,n,id[v[x]],1);}
		}
		if(opt==3)
		{
			x=read(),y=read();
			printf("%d\n",LCA(x,y));
		}
	}
	return 0;
}
```

---

## 作者：Farkas_W (赞：7)

$$\text{关于题意}$$

$\quad$一道很简单的树剖题，只有三种操作(其实是两种)，唯一要考虑的点是如何将边权转化成点权，考虑到每个点都有且只有一个父亲节点(除根节点1之外)，那么我们就可以将父亲与儿子连接的边权记录到儿子身上，这样 $n-1$ 条边就可以合理的分配到 $n-1$ 个点上(除了根节点)，这样就转化成了普通的树链剖分模板了(如果还不能理解就看看图吧)。

原图

![](https://cdn.luogu.com.cn/upload/image_hosting/o4y4z8vc.png)

经过转化后的图(将边权转化为点权)

![](https://cdn.luogu.com.cn/upload/image_hosting/qtsmvd97.png)

注意：对于路径$4-2-5$，只需访问点 $4$ 和点 $5$，对于 $4$ 和 $5$ 的 $LCA$ (最近公共祖先)不可取，因为 $2$ 在原图中对应的是边 $1-2$，并不在路径$4-2-5$上，所以在树链剖分中当 $x$ 和 $y$ 在同一条链上时($dep[x]<dep[y]$)，只需询问 $x+1$ 到 $y$ 的路径。

$$\text{对于三种操作}$$

1. 操作 $1$：修改操作，把第 $u$ 条边改成黑边。

2. 操作 $2$：修改操作，把第 $u$ 条边改成白边。

3. 操作 $3$：询问操作，若 $u$ 号节点和 $v$ 号节点间存在白边，输出 $-1$，否则输出 $u$ 号节点和 $v$ 号节点间的黑边数。

$\quad$可以很容易发现操作 $1$和操作 $2$ 其实是一种操作，只需开一个数组 $u$[$x$][$2$] 来记录第 $x$ 条边的两个端点，操作 $2$将这条边标记为 $0$，意为白边，操作 $1$ 就把这条边标记为 $1$，意为黑边，用线段树维护区间和(也可以是最小值)，询问时当$sum$[$k$]==$r$-$l$+$1$ 时说明这个区间内所有边都是黑边，ans+=sum[k]，否则至少有 $1$ 条边是白边，输出-1。

$\quad$下面贴出AC代码，建议反复阅读，深刻理解。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<algorithm>
#define il inline
#define inf 1e18
#define next nne
#define re register int
using namespace std;
il int read()		//快速读入
{
	int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x*f;
}
il void print(int x)	//快速输出
{
	if(x<0)putchar('-'),x=-x;
    if(x/10)print(x/10);
    putchar(x%10+'0');
}
const int N=3e5+5;
int n,m,next[N<<1],go[N<<1],head[N],tot,u[N][2],sum[N<<2];
int seg[N],son[N],father[N],top[N],size[N],dep[N],ans;
il void Add(int x,int y)
{
  next[++tot]=head[x];
  head[x]=tot;
  go[tot]=y;
}
il void dfs1(int x,int fa)
{
  father[x]=fa;dep[x]=dep[fa]+1;size[x]=1;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;
      dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;
    }
}
il void dfs2(int x,int topf)
{
  top[x]=topf;seg[x]=++seg[0];
  if(!son[x])return;
  dfs2(son[x],topf);
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(top[y])continue;
      dfs2(y,y);
    }
}
il void build(int k,int l,int r)//建树，每个点初始为1，每条边都是黑边
{
  if(l==r){sum[k]=1;return;}
  int mid=l+r>>1;
  build(k<<1,l,mid);build(k<<1|1,mid+1,r);
  sum[k]=sum[k<<1]+sum[k<<1|1];
}
il void change(int k,int l,int r,int x,int z)
{
  if(z&&sum[k]==r-l+1)return;
  if(l==r){sum[k]=z;return;}
  int mid=l+r>>1;
  if(x<=mid)change(k<<1,l,mid,x,z);
  else change(k<<1|1,mid+1,r,x,z);
  sum[k]=sum[k<<1]+sum[k<<1|1];
}
il bool query1(int k,int l,int r,int x,int y)
{
  if(x<=l&&y>=r){if(sum[k]==r-l+1){ans+=sum[k];return 1;}return 0;}		//统计答案
  int mid=l+r>>1;
  if(x<=mid)if(!query1(k<<1,l,mid,x,y))return 0;
  if(y>mid)if(!query1(k<<1|1,mid+1,r,x,y))return 0;
  return 1;
}
il void change1(int x,int z)
{
  int xx=u[x][0],yy=u[x][1];
  if(father[xx]==yy)change(1,1,n,seg[xx],z);	//修改儿子节点
  else change(1,1,n,seg[yy],z);
}
il bool query(int x,int y)
{
  int fx=top[x],fy=top[y];
  while(fx!=fy)
    {
      if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
      if(!query1(1,1,n,seg[fx],seg[x]))return 0;
      x=father[fx];fx=top[x];
    }
  if(dep[x]>dep[y])swap(x,y);
  if(seg[x]+1<=seg[y])if(!query1(1,1,n,seg[x]+1,seg[y]))return 0;		//记得seg[x]+1
  return 1;
}
signed main()
{
  n=read();
  for(re i=1;i<n;i++){re x=read(),y=read();u[i][0]=x;u[i][1]=y;Add(x,y);Add(y,x);}
  dfs1(1,0);dfs2(1,1);build(1,1,n);tot=0;m=read();
  while(m--)
    {
      re k=read(),x=read();
      if(k==1)change1(x,1);
      else if(k==2)change1(x,0);
      else {re y=read();ans=0;if(query(x,y))print(ans);else print(-1);putchar('\n');}	//ans记得要清零
    }
  return 0;
}

```
$$\text{后话}$$

$\quad$此题和[P3950 部落冲突](https://www.luogu.com.cn/problem/P3950)很像，那题也有[我的题解](https://www.luogu.com.cn/blog/Farkas/solution-p3950)，欢迎支持。

$\quad$谢谢观赏，写题解不易，点个赞吧！

---

## 作者：Natsume_Rin (赞：4)

### 修改了一些小错误。

这其实就是一道树剖的水题。

我们的程序需要支持三种操作。

- `1 x`，将第 $x$ 条边变为黑边。
- `2 x`，将第 $x$ 条边变为白边。
- `3 x y`，询问 $x \to y$ 路径上是否有白边，有的话，输出 `-1`，否则输出 $x \to y$ 的黑边数量。

前两个操作都用一个函数 `update` 来维护。唯一的小问题是，这题是边权，不好转化，所以我们要先将边权转为点权，再写个树剖。

```cpp
void update(int L, int R, int l, int r, int k, int v){
//v表示当前更新的边要变成黑边(1)还是白边(0)。
	if(L<=l&&r<=R){
		tree[k]=v;//黑边数量总和。
		maxx[k]=!v;
//maxx[k]表示k号点区间内的最大值。maxx[k]=1表示这个区间有白边，否则表示没有白边。
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) update(L,R,l,mid,k<<1,v);
	if(R>mid) update(L,R,mid+1,r,k<<1|1,v);
	tree[k]=tree[k<<1]+tree[k<<1|1];
	maxx[k]=max(maxx[k<<1],maxx[k<<1|1]);//记得要更新！！！
	return ;
}
```

处理完前两个操作后，再来看第三个操作。

第三个操作相当于是一个查询操作。查询 $x \to y$ 的边上是否有白边。

这里可以先用树链剖分求解。至于树链剖分，这里不再详解。

树链剖分代码:

```cpp
inline int dfs1(int now, int fath){
	fa[now]=fath;//记录当前点的父亲节点。
	siz[now]=1;//siz[x]表示在以1为整棵树的根节点的情况下，以x为根的子树的大小。
	de[now]=de[fath]+1;//记录深度。
	int maxn=-1;
	for(RI i=head[now];i;i=nxt[i]){
		if(to[i]==fath) continue;
		siz[now]+=dfs1(to[i],now);
		if(siz[to[i]]>maxn){
			maxn=siz[to[i]];
			son[to[i]]=to[i];//更新重儿子。
		}
	}
	return siz[now];
}
inline void dfs2(int now, int _top){
	top_[now]=_top;//记录链顶
	id[now]=++tot;//将每个节点重新标号。
	if(!son[now]) return ;//如果这个点是叶子节点，直接退出。
	dfs2(son[now],_top);//顺着重儿子继续找。
	for(RI i=head[now];i;i=nxt[i]){
		if(to[i]==fa[now]||to[i]==son[now]) continue;
		dfs2(to[i],to[i]);
	}
	return ;
}
inline int Qquery(int x, int y){
	int res=0, now=0;
	while(top_[x]!=top_[y]){//如果x,y不在同一条链上。
		if(de[top_[x]]<de[top_[y]]) swap(x,y);
		res+=query(id[top_[x]],id[x],1,n,1);
		now+=Mquery(id[top_[x]],id[x],1,n,1);//记录一下本次移动得到的答案。
		x=fa[top_[x]];//让深度大的向上移。
	}
	if(id[x]>id[y]) swap(x,y);
	res+=query(id[x]+1,id[y],1,n,1);//这里是边权，所以是id[x]=1
	now+=Mquery(id[x]+1,id[y],1,n,1);//最后还要来一次。
	if(now) return -1;//这里！！！如果now=0，说明 x -> y 路径上没有白边。否则，说明有白边。
	return res;
}
```

 ### 谢谢！！！

---

## 作者：hyfhaha (赞：3)

思路：将黑边标记为1，白边标记为100000，树链剖分

如果查询时ans超过100000，那就有白边，输出-1，不然直接输出ans

```cpp
#include<bits/stdc++.h>
#define maxn 800001
#define int long long
#define L(x) (x<<1)
#define R(x) ((x<<1)|1)
using namespace std;
int tree[maxn],tag[maxn];
int rev[maxn],dep[maxn],size[maxn],seg[maxn],top[maxn],son[maxn],father[maxn];
int n,m,root,x,y,z,a[maxn],tot,mode;
int cnt,from[maxn],to[maxn],Next[maxn],head[maxn];
int Gx,Gy,Gz,Gd;
int fa[maxn],X[maxn],Y[maxn],Z[maxn];
void add(int x,int y){
    cnt++;
    from[cnt]=x;to[cnt]=y;
    Next[cnt]=head[x];head[x]=cnt;
}
void update(int node,int begin,int end,int x,int y,int val){
    if(begin>y||end<x)return;
    if(begin>=x&&end<=y){
        tree[node]=val;
        return;
    }else{
        int mid=(begin+end)>>1;
        if(x<=mid)update(L(node),begin,mid,x,y,val);
        if(y>mid) update(R(node),mid+1,end,x,y,val);
        tree[node]=tree[L(node)]+tree[R(node)];
    }
}
int query(int node,int begin,int end,int x,int y){
    if(begin>=x&&end<=y){
        return tree[node];
    }else{
        int mid=(begin+end)>>1,sum=0;
        if(x<=mid)sum+=query(L(node),begin,mid,x,y);
        if(y>mid) sum+=query(R(node),mid+1,end,x,y);
        return sum;
    }
}
int dfs1(int x){
    size[x]=1;
    dep[x]=dep[father[x]]+1;
    for(int i=head[x];i!=-1;i=Next[i]){
        int v=to[i],big=0;
        if(father[x]==v)continue;
        father[v]=x;
        big=dfs1(v);
        size[x]+=big;
        if(big>size[son[x]])son[x]=v;
    }
    return size[x]; 
}
void dfs2(int x){
    if(son[x]){
        seg[son[x]]=++seg[0];
        top[son[x]]=top[x];
        rev[seg[0]]=son[x];
        dfs2(son[x]);
    }
    for(int i=head[x];i!=-1;i=Next[i]){
        int v=to[i];
        if(!top[v]){
            seg[v]=++seg[0];
            top[v]=v;
            rev[seg[0]]=v;
            dfs2(v);
        }
    }
}
int linkquery(int x,int y){
    int fx=top[x],fy=top[y],ans=0;
    while(fx!=fy){
        if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
        ans+=query(1,1,seg[0],seg[fx],seg[x]);
        x=father[fx];fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    ans+=query(1,1,seg[0],seg[x],seg[y]);
    ans-=query(1,1,seg[0],seg[x],seg[x]);
    return ans;
}
void change(int x,int y){
    x*=2;
    x=dep[from[x]]>dep[to[x]]?from[x]:to[x];
    update(1,1,seg[0],seg[x],seg[x],y);
}
signed main(){
    memset(head,-1,sizeof(head));
    scanf("%lld",&n);root=1;
    for(int i=1;i<=n-1;i++){
        scanf("%lld%lld",&x,&y);
        add(x,y),add(y,x);
    }
    dfs1(root);
    seg[root]=++seg[0];
    rev[seg[0]]=root;
    top[root]=root;
    dfs2(root);
    scanf("%lld",&m);
    for(int i=1;i<=n-1;i++)change(i,1);
    for(int i=1;i<=m;i++){
        scanf("%lld%lld",&mode,&x);
        if(mode==1)change(x,1);
        if(mode==2)change(x,100000);
        if(mode==3){
            scanf("%lld",&y);
            int ans=0;
            ans=linkquery(x,y);
            if(ans>=100000)printf("-1\n");else
            printf("%lld\n",ans);
        }
    }
}
```

---

## 作者：hsfzLZH1 (赞：3)

题目大意：有一个 $n$ 个节点的树，每条边有一个颜色：黑色或白色。有 $q$ 个询问，对于每个询问，你需要修改一条边的颜色，或者回答树上两个节点 $x$ 和 $y$ 之间的唯一路径上是否所有边都是黑色，然后输出这两个点在树上的距离。

这是树链剖分的模板题。如果您不知道什么是树链剖分，请您阅读 [树链剖分入门](https://oi-wiki.org/graph/heavy-light-decomposition/)。

树链剖分能解决的问题往往都是权值在节点上的情况，然后将树利用轻重路径拆分成一条链，用线段树维护并修改查询区间信息，但是这道题的**权值是出在树边上**的。我们考虑这样一种解法，指定一个根节点，然后将边权分配到另外的 $n-1$ 个节点上。有这样一种分配方式，将边权分配给一条边所连两个点在有根树上深度更大的那个点，这样可以保证不会重复且无遗漏地分配到所有其他点上。

在进行树链剖分的过程中，我们发现如果查询两个节点 $x$ 和 $y$ 之间的路径时，会多余计算 $LCA(x,y)$ 到它的父亲这条边，所以我们需要求出这两个点的LCA，然后在求得的答案中减去这个值。

在树链剖分时，我们需要维护这样一个数据结构：

1.单点修改一个节点的值，0或1，0代表这条边为黑色，1代表这条边为白色；

2.查询区间和。

对于每次询问，我们只需查询这两个节点之间的路径上的权值和，如果是0，代表存在一条全是黑色的路径，则输出 $depth(a)+depth(b)-2\times depth(LCA(a,b))$。否则输出-1.

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lc o<<1
#define rc o<<1|1
using namespace std;
typedef int ll;
const int maxn=200010;
int n,m,op,a,b,x[maxn],y[maxn],lg[maxn];
int cur,h[maxn],nxt[maxn],p[maxn];
int siz[maxn],top[maxn],son[maxn],dep[maxn],fa[maxn][20],tid[maxn],rnk[maxn],cnt;
inline void add_edge(int x,int y)
{
	cur++;
	nxt[cur]=h[x];
	h[x]=cur;
	p[cur]=y;
}
void dfs1(int o)
{
	siz[o]=1;son[o]=-1;
	for(int j=h[o];j;j=nxt[j])if(!dep[p[j]])
	{
		dep[p[j]]=dep[o]+1;
		fa[p[j]][0]=o;
		dfs1(p[j]);
		siz[o]+=siz[p[j]];
		if(son[o]==-1||siz[p[j]]>siz[son[o]])son[o]=p[j];
	}
}
void dfs2(int o,int t)
{
	top[o]=t;cnt++;tid[o]=cnt;rnk[cnt]=o;
	if(son[o]==-1)return;
	dfs2(son[o],t);
	for(int j=h[o];j;j=nxt[j])if(p[j]!=son[o]&&p[j]!=fa[o][0])dfs2(p[j],p[j]);
}
struct SegTree
{
	struct SegTreeNode{ll Val=0,AddMark=0;}SegTree[maxn*4];
	void Update(int o,int l,int r,int ul,int ur,ll AddVal)
	{
		if(l>ur||r<ul)return;
		if(l>=ul&&r<=ur)
		{
			SegTree[o].AddMark+=AddVal;
			SegTree[o].Val+=AddVal*(r-l+1);
			return;
		}
		int mid=(l+r)>>1;
		if(SegTree[o].AddMark!=0)
		{
			SegTree[o*2].AddMark+=SegTree[o].AddMark;
			SegTree[o*2+1].AddMark+=SegTree[o].AddMark;
			SegTree[o*2].Val+=SegTree[o].AddMark*(mid-l+1);
			SegTree[o*2+1].Val+=SegTree[o].AddMark*(r-mid);
			SegTree[o].AddMark=0;
		}
		Update(o*2,l,mid,ul,ur,AddVal);
		Update(o*2+1,mid+1,r,ul,ur,AddVal);
		SegTree[o].Val=(SegTree[o*2].Val+SegTree[o*2+1].Val);
	}
	ll Query(int o,int l,int r,int ql,int qr)
	{
		if(ql>r||qr<l)return 0;
		if(ql<=l&&qr>=r)return SegTree[o].Val;
		int mid=(l+r)>>1;
		if(SegTree[o].AddMark!=0)
		{
			SegTree[o*2].AddMark+=SegTree[o].AddMark;
			SegTree[o*2+1].AddMark+=SegTree[o].AddMark;
			SegTree[o*2].Val+=SegTree[o].AddMark*(mid-l+1);
			SegTree[o*2+1].Val+=SegTree[o].AddMark*(r-mid);
			SegTree[o].AddMark=0;
		}
		return (Query(o*2,l,mid,ql,qr)+Query(o*2+1,mid+1,r,ql,qr));
	}
}st;
ll query(int x,int y)
{
	ll ret=0,fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]>=dep[fy])ret+=st.Query(1,1,n,tid[fx],tid[x]),x=fa[fx][0];
        else ret+=st.Query(1,1,n,tid[fy],tid[y]),y=fa[fy][0];
        fx=top[x];fy=top[y];
    }
    if(x!=y)
    {
        if(tid[x]<tid[y])ret+=st.Query(1,1,n,tid[x],tid[y]);
        else ret+=st.Query(1,1,n,tid[y],tid[x]);
    }
    else ret+=st.Query(1,1,n,tid[x],tid[y]);
    return ret;
}
int LCA(int x,int y)
{
	if(dep[x]>dep[y])swap(x,y);
	int k=dep[y]-dep[x];
	for(int i=0;k;k>>=1,i++)if(k&1)y=fa[y][i];
	if(x==y)return x;
	k=dep[x];
	for(int i=lg[k];i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)scanf("%d%d",x+i,y+i),add_edge(x[i],y[i]),add_edge(y[i],x[i]);
	dep[1]=1;dfs1(1);dfs2(1,1);
	for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=lg[n];i++)for(int j=1;j<=n;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d",&op);
		if(op==3)
		{
			scanf("%d%d",&a,&b);
			int t=LCA(a,b);
			//printf("j %d %d %d\n",a,b,t);
			//printf("%d %d\n",query(a,b),st.Query(1,1,n,t,t));
			if(query(a,b)-st.Query(1,1,n,tid[t],tid[t]))printf("-1\n");
			else printf("%d\n",dep[a]+dep[b]-dep[t]*2);
		}
		else
		{
			scanf("%d",&a);
			if(fa[x[a]][0]==y[a])a=x[a];
			else a=y[a];
			if(op==1)if(st.Query(1,1,n,tid[a],tid[a])==1)
			st.Update(1,1,n,tid[a],tid[a],-1);
			if(op==2)if(st.Query(1,1,n,tid[a],tid[a])==0)
			st.Update(1,1,n,tid[a],tid[a],1);
		}
	}
	return 0;
}
```

---

## 作者：是个妹子啦 (赞：2)

题意很裸

修改边权，询问黑边数量

类似于求距离：$u$到$v$的黑边数量=$1$到$u$的黑边数量$+1$到$v$的黑边数量$-lca(u,v)$到$1$的黑边数量

考虑将一条边$u,v$变黑，相当于将$v$子树每个点到根黑边数$+1$，

所以记录$dfs$序，线段树维护即可

```cpp
#include<bits/stdc++.h>
using namespace std ;
int n , m ;
const int N = 1e5 + 10 ;
struct Edge { int u , v ; } edge[N] ;
struct node { int v , nxt ; } e[N << 1] ;
int head[N] , cnt = 0 ;
inline void add(int u , int v) { e[++ cnt] = {v , head[u]} ; head[u] = cnt ; }
int sz[N] , d[N] , fa[N] , son[N] ;
inline void dfs(int u) {
    sz[u] = 1 ;
    for(register int i = head[u] ; i ; i = e[i].nxt) {
    	int v = e[i].v ;
    	if(v == fa[u]) continue ;
    fa[v] = u ;
    d[v] = d[u] + 1 ;
    dfs(v) ;
    sz[u] += sz[v] ;
    if(sz[v] > sz[son[u]]) son[u] = v ;
	}
}
int top[N] , id[N] , idx = 0 ;
    inline void dfs(int u , int t) {
      top[u] = t ; id[u] = ++ idx ;
      if(son[u]) dfs(son[u] , t) ;
      for(register int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].v ;
        if(v == fa[u] || v == son[u]) continue ;
        dfs(v , v) ;
      }
    }
    struct Seg {
      int sum[N << 2] ;
      inline void build(int l , int r , int rt) {
        sum[rt] = r - l + 1 ;
        if(l == r) return ;
        int mid = l + r >> 1 ;
        build(l , mid , rt << 1) ;
        build(mid + 1 , r , rt << 1 | 1) ;
      }
      inline void change(int x , int l , int r , int rt , int val) {
        if(l == r) { sum[rt] = val ; return ; }
        int mid = l + r >> 1 ;
        if(x <= mid) change(x , l , mid , rt << 1 , val) ;
        else change(x , mid + 1 , r , rt << 1 | 1 , val) ;
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1] ;
      }
      inline int query(int a , int b , int l , int r , int rt) {
        if(a <= l && r <= b) return sum[rt] ;
        int mid = l + r >> 1 ;
        int ans = 0 ;
        if(a <= mid) ans += query(a , b , l , mid , rt << 1) ;
        if(b > mid) ans += query(a , b , mid + 1 , r , rt << 1 | 1) ;
        return ans ;
      }
    } s[3] ;
    inline int query_black(int x , int y) {
      int fx = top[x] , fy = top[y] ; int ans = 0 ;
      while(fx ^ fy) {
        if(d[fx] < d[fy]) swap(x , y) , swap(fx , fy) ;
        ans += s[1].query(id[fx] , id[x] , 1 , n , 1) ;
        x = fa[fx] , fx = top[x] ;
      }
      if(d[x] > d[y]) swap(x , y) ;
      ans += s[1].query(id[x] + 1 , id[y] , 1 , n , 1) ;
      return ans ;
    }
    inline int query_white(int x , int y) {
      int fx = top[x] , fy = top[y] ; int ans = 0 ;
      while(fx ^ fy) {
        if(d[fx] < d[fy]) swap(x , y) , swap(fx , fy) ;
        ans += s[2].query(id[fx] , id[x] , 1 , n , 1) ;
        x = fa[fx] , fx = top[x] ;
      }
      if(d[x] > d[y]) swap(x , y) ;
      ans += s[2].query(id[x] + 1 , id[y] , 1 , n , 1) ;
      return ans ;
    }
    signed main() {
      ios :: sync_with_stdio(false) ;
      cin.tie(nullptr) ;
      cout.tie(nullptr) ;
      cin >> n ;
      for(register int i = 1 ; i < n ; i ++) {
        int u , v ;
        cin >> u >> v ;
        add(u , v) ;
        add(v , u) ;
        edge[i] = { u , v } ;
      }
      dfs(1) ; dfs(1 , 1) ;
      s[1].build(1 , n , 1) ;
      for(cin >> m ; m -- ; ) {
        int opt ; cin >> opt ;
        if(opt == 3) {
          int x , y ; cin >> x >> y ;
          if(! query_white(x , y))
            cout << query_black(x , y) << '\n' ;
          else
            cout << -1 << '\n' ;
        }
        else {
          int x ; cin >> x ;
          int u = edge[x].u , v = edge[x].v ;
          if(fa[u] == v) swap(u , v) ;
          s[opt == 2 ? 1 : 2].change(id[v] , 1 , n , 1 , 0) ;
          s[opt].change(id[v] , 1 , n , 1 , 1) ;
        }
      }
      cout << '\n' ;
      return 0 ;
    }
```



---

## 作者：iwprc (赞：2)

- ~~最近发现很多树链剖分的题目都可以使用O(mlogn)的DFS序解法~~
## 正题
- 在阅读本题解前，请确保自己已经会这题的$O(mlog^2n)$做法
- 通过仔细阅读题目，我们发现这道题需要我们干三件事
   1. 给树上的一条边+1，或-1
   2. 求树上的路径和
   3. 求树上路径长度
- 首先3就是 $dep[x]+dep[y]-2*dep[LCA(x,y)]$,使用树链剖分求LCA可以做到$O(mlogn)$
- 而1,2操作如果直接使用树链剖分是$O(mlog^2n)$的(参见树链剖分模板)，也是这题的瓶颈所在，那么有没有$O(mlogn)$的解法($LCT$常数大，可能还不如树剖)呢？
- 事实上是存在的，我们考虑以下三件事：
   1. $valsum(x,y)$
   $=valsum(x,LCA(x,t))+valsum(y,LCA(x,y))$
   $=valsum(x,1)-valsum(LCA(x,y),1)+valsum(y,1)-valsum(LCA(x,y),1)$
   2. 由于子树的$DFS$序连续，所以使用树链剖分解决树上的单点修改，查询子树和的题目可以$O(mlogn)$
   3. 以下两个问题是等价的
      1. 操作1：给点$x$的值加$a$，操作2：查询点$y$到点$1$的和
      1. 操作1：给以$x$为根的子树加$a$，操作2：查询点$y$的值
- 接下来，我们就可以$O(mlogn)$解决树链剖分问题了

---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF165D)

# 题解

这类题目，不多说可以直接上树剖板子，时间复杂度 $\mathcal O(n\log ^2n)$，此处不作过多赘述，毕竟重点不是这个方法。

实际上我们有比树剖的俩 $\log$ 更优的解法，但是还是利用线段树。

分析这道题实际要我们干的事是什么：

1. 能够任意改边的颜色；
2. 询问俩点之间的距离，以及俩点路径上黑边的数量；

由于所有的工作都是为询问服务，我们先考虑怎么解决询问。

由于是询问两点之间的距离，以及黑边数量，我们能够联想到 $lca$，从 $lca$ 的角度来说，对于距离是很好解决的，但是黑边数量？我们可以用类似求距离的方法，来求黑边的数量，考虑有这样的一个变换：
$$
\text{cnt_black}(u,v)=\text{cnt_black}(u,1)+\text{cnt_black}(v,1)-\text{cnt_black}(lca,1)
$$
也就是说，只要我们可以维护一个点到根节点的黑边数量，我们便亦能求得两点间黑边数量，考虑对于一条边 $(u,v)$（假定 $v$ 更深），如果这条边变黑，即相当于 $v$ 子树内部整体到根的黑边数加一，对于黑变白同理，所以我们可以先得到每个点的 $dfs$ 序，再用线段树维护黑边数即可，时间复杂度 $\mathcal O(n\log n)$.

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13552974.html
```



---

## 作者：zhengrunzhe (赞：1)

这里大力lct不是很爽吗

考虑维护一个森林，上面的点有边仅当原树中有黑边

那么染成白色就是个$Cut$

那么染成黑色就是个$Link$

维护个size,查询如果两点不连通就说明有白边返回-1否则split之后输出size-1即可

时间复杂度:$O((n+m) log n)$+~~常数~~

~~跑得比两个log的树剖线段树还慢~~
```cpp
#include<cstdio>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
template<class type>inline const void swap(type &a,type &b)
{
	type c=a;a=b;b=c;
}
const int N=1e5+10;
int n,m,u[N],v[N];
class Link_Cut_Tree
{
	private:
		struct tree
		{
			bool rev;
			int size,son[2],fa;
			inline const void reverse()
			{
				rev^=1;swap(son[0],son[1]);
			}
		}t[N];
		inline const void pushup(int p)
		{
			t[p].size=t[t[p].son[0]].size+1+t[t[p].son[1]].size;
		}
		inline const void pushdown(int p)
		{
			if (t[p].rev)
				t[t[p].son[0]].reverse(),
				t[t[p].son[1]].reverse(),
				t[p].rev=0;
		}
		inline const bool identity(int p)
		{
			return t[t[p].fa].son[1]==p;
		}
		inline const bool nroot(int p)
		{
			return t[t[p].fa].son[0]==p||identity(p);
		}
		inline const void rotate(int p)
		{
			bool f=identity(p);
			int fa=t[p].fa,gfa=t[fa].fa,q=t[p].son[f^1];
			if (nroot(fa))t[gfa].son[identity(fa)]=p;
			t[t[p].son[f^1]=fa].son[f]=q;
			t[t[t[q].fa=fa].fa=p].fa=gfa;
			pushup(fa);
		}
		inline const void relieve(int p)
		{
			if (nroot(p))relieve(t[p].fa);
			pushdown(p);
		}
		inline const void splay(int p)
		{
			relieve(p);
			for (int fa;nroot(p);rotate(p))
				if (nroot(fa=t[p].fa))
					rotate(identity(p)^identity(fa)?p:fa);
			pushup(p);
		}
		inline const void access(int x)
		{
			for (int y=0;x;x=t[y=x].fa)
				splay(x),t[x].son[1]=y,pushup(x);
		}
		inline const void makeroot(int x)
		{
			access(x);splay(x);t[x].reverse();
		}
		inline const void split(int x,int y)
		{
			makeroot(x);access(y);splay(y);
		}
		inline const int findroot(int x)
		{
			access(x);splay(x);
			while (t[x].son[0])pushdown(x=t[x].son[0]);
			splay(x);return x;
		}
	public:
		inline const void link(int x,int y)
		{
			if (findroot(x)==findroot(y))return;
			makeroot(x);t[x].fa=y;
		}
		inline const void cut(int x,int y)
		{
			if (findroot(x)^findroot(y))return;
			split(x,y);
			if (t[y].size>2)return;
			t[y].son[0]=t[x].fa=0;
			pushup(y);
		}
		inline const int distance(int x,int y)
		{
			if (findroot(x)^findroot(y))return -1;
			split(x,y);return t[y].size-1;
		}
}lct;
int main()
{
	read(n);
	for (int i=1;i<n;i++)read(u[i]),read(v[i]),lct.link(u[i],v[i]);
	read(m);
	for (int opt,x,y;m--;)
		switch (read(opt),read(x),opt)
		{
			case 1:lct.link(u[x],v[x]);break;
			case 2:lct.cut(u[x],v[x]);break;
			case 3:read(y);writeln(lct.distance(x,y));break;
		}
	return 0;
}
```

---

## 作者：流逝丶 (赞：1)

这就是一个树剖裸题，但给的是边权。

这题会板子的话，只需考虑如何来写线段树维护这道题维护的东西和边权化点权。

我对于边权化点权是在两点连线之间建立一个点，把边

权给它，节点数就会变为$2*n+1$，而代表边的点编号都为边的编号加n。

每次修改的时候把x改成x+n就是要修改边所对应的的编号。

对于黑边，给它赋值为1，而白边赋值为0，修改就是单点修改，查询的话，查询区

间和，再利用树剖LCA判断两点之间的距离是否是ans的2倍，若是，则全是黑边，

若不是则输出-1。然后这题就做完了。

AC代码

```cpp
#include<iostream>
#include<cstdio>
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
using namespace std;
const int N=200005;
int n,m,cnt,tot,ans;
int head[N],id[N],top[N],fa[N],siz[N],son[N],dep[N],dfn[N];
int tr[N<<2];
bool flag;
struct node{
	int to,nxt;
}e[N<<1];
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline void add(int from,int to){
	e[++cnt]=(node){to,head[from]};
	head[from]=cnt;
}
void dfs1(int x,int f){
	dep[x]=dep[f]+1;fa[x]=f;siz[x]=1;
	int y;
	for(int i=head[x];i;i=e[i].nxt){
		y=e[i].to;
		if(y==f)continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])son[x]=y;
	}
}
void dfs2(int x,int topf){
	top[x]=topf;id[x]=++tot;dfn[tot]=x;
	if(!son[x])return ;
	dfs2(son[x],topf);
	int y;
	for(int i=head[x];i;i=e[i].nxt){
		y=e[i].to;
		if(y==fa[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
inline void update(int k){
	tr[k]=tr[ls]+tr[rs];
}
void build(int k,int l,int r){
	if(l==r){
		tr[k]=dfn[l]>n?1:0;
		return ;
	}
	build(lson);build(rson);
	update(k);
}
void change(int k,int l,int r,int x,int y){
	if(l==r&&x==l){
		tr[k]=y;
		return ;
	}
	if(x<=mid)change(lson,x,y);
	else change(rson,x,y);
	update(k);
}
int ask(int k,int l,int r,int x,int y){
	if(l==x&&y==r){
		return tr[k];
	}
	if(y<=mid)return ask(lson,x,y);
	else if(x>mid)return ask(rson,x,y);
	else return ask(lson,x,mid)+ask(rson,mid+1,y);
}
inline void qurey(int x,int y){
	ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=ask(1,1,n*2-1,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans+=ask(1,1,n*2-1,id[x],id[y]);
}
inline int LCA(int x, int y) {
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
inline void check(int x,int y){
	int dis=dep[x]+dep[y]-2*dep[LCA(x,y)];
	if(dis!=ans*2)flag=1;
}
int main(){
	n=read();
	int x,y;
	for(int i=1;i<n;++i){
		x=read();y=read();
		add(x,i+n);add(i+n,x);
		add(i+n,y);add(y,i+n);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n*2-1);
	m=read();
	int opt;
	while(m--){
		opt=read();x=read();
		if(opt==1)change(1,1,n*2-1,id[x+n],1);
		else if(opt==2)change(1,1,n*2-1,id[x+n],0);
		else {
			flag=0;
			y=read();
			qurey(x,y);
			check(x,y);
			if(flag)printf("-1\n");
			else printf("%d\n",ans);
		}
	}
}
```


---

## 作者：JK_LOVER (赞：0)

## 题意
求问 $m$ 次询问:
-  1 ：把第 $u$ 条边改成黑边。
-  2 ：把第 $u$ 条边改成白边。
-  3 ：若 $u$ 号节点和 $v$ 号节点间存在白边，输出 $-1$ ，否则输出 $u$ 号节点和 $v$ 号节点间的黑边数。
## 分析
主要问题是如何快速的区分是否有白边。否则就是一个裸的树上距离。考虑用极值来分别黑白。考虑到最多只有 $n-1$ 个黑边。所以只要将白边赋值为 $n$ ，黑边为 $1$ 。当 $ans\ge n$ 时，一定是不合法的。
$$
ans =\begin{cases}ans(ans\le {n-1})\\ -1(ans\ge n)\end{cases}
$$
或者用第二个数组来判断，黑边权值为 $0$ ，白为 $1$ 。
$$
ans =\begin{cases}ans(sum =0)\\ -1(sum \ge 1)\end{cases}
$$
代码就只是一个链上查询了。这里采用 $LCT$ 的 $O(n\log n)$ 的做法。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 4e5+100;
const int inf = 2e5+10;
int c[N][2],f[N],n,m,val[N];
long long sum[N];
bool r[N];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
inline void write(int x)
{
	if(x>9)write(x/10);
    putchar(x%10+'0');
}

void pushr(int x)
{
	swap(c[x][1],c[x][0]);
	r[x] ^= 1;
}
void pushdown(int x)
{
	if(r[x])
	{
		if(c[x][1]) pushr(c[x][1]);
		if(c[x][0]) pushr(c[x][0]);
		r[x] = 0;
	}		
}
void pushup(int x)
{
	sum[x] = val[x];
	sum[x] += sum[c[x][1]] + sum[c[x][0]]; 
}
bool nroot(int x)
{
	return c[f[x]][0] == x || c[f[x]][1] == x; 
}
void rotate(int x)
{
	int y = f[x],z = f[y],k = c[y][1] == x,w = c[x][!k];
	if(nroot(y)) c[z][c[z][1] == y] = x;
	c[x][!k] = y;c[y][k] = w;
	f[w] = y;f[y] = x;f[x] = z;
	pushup(y);
}
void push(int x)
{
	if(nroot(x)) push(f[x]);
	pushdown(x);
}
void splay(int x)
{
	push(x);
	while(nroot(x))
	{
	
		int y = f[x],z = f[y];
		if(nroot(y))
		{
			rotate((c[y][1]==x)^(c[z][1]==y)?x:y);
		}
		rotate(x);
		pushup(x);
	}
}
void access(int x)
{
	for(int y = 0;x;x = f[y=x])
	splay(x),c[x][1] = y,pushup(x);
}
void makeroot(int x)
{
	access(x);splay(x);pushr(x);
}
void link(int x,int y)
{
	makeroot(x);
	f[x] = y;
}
signed main()
{
	n = read();
	for(int i = 1;i < n;i++)
	{
		int a = read(),b = read();
		val[i+n] = 1;
		val[a] = val[b] = 0;
		link(a,i+n);
		link(b,i+n);
	}
	m = read();
	for(int i = 1;i <= m;i++)
	{
		int opt = read();
		if(opt == 1)
		{
			int u = read();
			makeroot(u+n);
			val[u+n] = 1; 
		}
		if(opt == 2)
		{
			int u = read();
			makeroot(u+n);
			val[u+n] = n;
		}
		if(opt == 3)
		{
			int u = read(),v = read();
			makeroot(u);
			access(v);
			splay(v);
			if(sum[v] >= n) printf("-1\n");
			else printf("%lld\n",sum[v]);
		}
	}
}
```
[地址](https://www.luogu.com.cn/blog/xzc/solution-cf165d)

---

## 作者：vocaloid (赞：0)

树链剖分。这道题非常有意思，只是让查询区间内是否有白边，而输出的是 $-1$ 或两点的距离。我们首先考虑如何维护区间内是否有白边。首先依然是用将边转到深点，忽略 $\text{LCA}$ 的做法，将边转点，然后我们考虑，将黑边的值赋为 $0$，白边的值赋为 $1$，此时我们要做的事情就很简单了：查询区间和，如果区间和大于 $0$，那么就显然有白边，输出 $-1$，否则我们可以在查询区间和的时候顺便求出 $\text{LCA}$（因为在退出 $top[u]\not=top[v]$）这个循环的时候，深度更浅的那个点必然就是 $\text{LCA}$，记录一下即可。然后就可以输出两点间的距离，即 $dep[u]+dep[v]-dep[lca]*2$。

然后考虑怎么修改，题中有两句很重要的话没有翻译出来：在修改某边为黑边时，它原本一定是白边；在修改某边为白边时，它原本一定是黑边。所以我们只需要一个单点加函数，在修改为黑边时加上 $-1$，修改为白边时加上 $1$ 即可。

树链剖分入门见：[树链剖分瞎入门](http://www.luogu.org/blog/Venus/tree-train-split)

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1];
int n,Q,fr[MAXN],tx[MAXN],t[MAXN<<2],tag[MAXN<<2],lca;
int siz[MAXN],son[MAXN],top[MAXN],dep[MAXN],faz[MAXN],dfn[MAXN],Index;
void AddEdge(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
void Dfs1(int u)
{
	siz[u]=1;
	son[u]=0;
	for(int i=fst[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==faz[u]) continue;
		dep[v]=dep[u]+1;
		faz[v]=u;
		Dfs1(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}
void Dfs2(int u,int rt)
{
	dfn[u]=++Index;
	top[u]=rt;
	if(son[u]) Dfs2(son[u],rt);
	for(int i=fst[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==faz[u] || v==son[u]) continue;
		Dfs2(v,v);
	}
}
void PushUp(int rt)
{
	t[rt]=t[rt<<1]+t[rt<<1|1];
}
void PushDown(int rt,int len)
{
	t[rt<<1]+=tag[rt]*(len-(len>>1));
	t[rt<<1|1]+=tag[rt]*(len>>1);
	tag[rt<<1]+=tag[rt];
	tag[rt<<1|1]+=tag[rt];
	tag[rt]=0;
}
void Modify(int rt,int l,int r,int pos,int val)
{
	if(l==r)
	{
		t[rt]+=val*(r-l+1);
		tag[rt]+=val;
		return;
	}
	PushDown(rt,r-l+1);
	int mid=l+r>>1;
	if(pos<=mid) Modify(rt<<1,l,mid,pos,val);
	else Modify(rt<<1|1,mid+1,r,pos,val);
	PushUp(rt);
}
int Query(int rt,int l,int r,int tl,int tr)
{
	if(tl<=l && r<=tr) return t[rt];
	PushDown(rt,r-l+1);
	int mid=l+r>>1,res=0;
	if(tl<=mid) res+=Query(rt<<1,l,mid,tl,tr);
	if(tr>mid) res+=Query(rt<<1|1,mid+1,r,tl,tr);
	return res;
}
int QueryOnTree(int u,int v)
{
	int res=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		res+=Query(1,1,n,dfn[top[u]],dfn[u]);
		u=faz[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	lca=u;
	res+=Query(1,1,n,dfn[u]+1,dfn[v]);
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
		fr[i]=x;
		tx[i]=y;
	}
	Dfs1(1);
	Dfs2(1,1);
	scanf("%d",&Q);
	while(Q--)
	{
		int opt,x,y;
		scanf("%d %d",&opt,&x);
		if(opt==1)
		{
			int u=fr[x],v=tx[x];
			if(dep[u]<dep[v]) swap(u,v);
			Modify(1,1,n,dfn[u],-1);
		}
		else if(opt==2)
		{
			int u=fr[x],v=tx[x];
			if(dep[u]<dep[v]) swap(u,v);
			Modify(1,1,n,dfn[u],1);
		}
		else if(opt==3)
		{
			scanf("%d",&y);
			int res=QueryOnTree(x,y);
			if(res) puts("-1");
			else printf("%d\n",dep[x]+dep[y]-dep[lca]*2);
		}
	}
	return 0;
}
```

---

