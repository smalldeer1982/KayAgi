# [USACO15DEC] Max Flow P

## 题目描述

Farmer John 在他的谷仓中安装了 $N-1$ 条管道，用于在 $N$ 个牛棚之间运输牛奶（$2 \leq N \leq 50,000$），牛棚方便地编号为 $1 \ldots N$。每条管道连接一对牛棚，所有牛棚通过这些管道相互连接。

FJ 正在 $K$ 对牛棚之间泵送牛奶（$1 \leq K \leq 100,000$）。对于第 $i$ 对牛棚，你被告知两个牛棚 $s_i$ 和 $t_i$，这是牛奶以单位速率泵送的路径的端点。FJ 担心某些牛棚可能会因为过多的牛奶通过它们而不堪重负，因为一个牛棚可能会作为许多泵送路径的中转站。请帮助他确定通过任何一个牛棚的最大牛奶量。如果牛奶沿着从 $s_i$ 到 $t_i$ 的路径泵送，那么它将被计入端点牛棚 $s_i$ 和 $t_i$，以及它们之间路径上的所有牛棚。

## 说明/提示

$2 \le N \le 5 \times 10^4,1 \le K \le 10^5$。

## 样例 #1

### 输入

```
5 10
3 4
1 5
4 2
5 4
5 4
5 4
3 5
4 3
4 3
1 3
3 5
5 4
1 5
3 4```

### 输出

```
9```

# 题解

## 作者：ModestCoder_ (赞：89)

LCA+树上差分

我们要统计每个点经过几次，也就是在每一条路径上，给路径上的点+1，所以我们此题用树上差分就可以很快得得到每个点经过的次数

具体是这样的：假设一条u到v的路径，那么这条路径是u--->lca(u,v)--->v的，所以我们把u--->lca(u,v)与lca(u,v)--->v两条路径各自加一，也就是++power[u],++power[v],power[lca(u,v)]-=2

但是这样一来，lca(u,v)上+2又-2等于0，也就是u--->v整条路经上除了lca(u,v)都加了1，为了排除这个干扰，我们把power[lca(u,v)]-=2改成- -power[lca(u,v)],- -power[lca(u,v)的父亲]

LCA用倍增比较方便，最后遍历整棵树统计和

Code:
```
#include <bits/stdc++.h>
using namespace std;
#define maxn 50010
#define ll long long
#define res register int
struct Node{
	int to,next;
};
Node edge[maxn<<2]; //链式前向星要多开几倍数组
int head[maxn<<2],power[maxn],n,m,d[maxn],fa[maxn][30],ans,num;

inline int read(){ //快读
	int s=0;
	char c=getchar();
	while (c<'0' || c>'9') c=getchar();
	while (c>='0' && c<='9') s=s*10+c-'0',c=getchar();
	return s;
}
//链式前向星
inline void add(int x,int y){edge[++num].to=y,edge[num].next=head[x],head[x]=num;}
//接下来是初始化
inline void work(int u,int fath){
	d[u]=d[fath]+1,fa[u][0]=fath;
	for (res i=0;fa[u][i];++i) fa[u][i+1]=fa[fa[u][i]][i];
	for (res i=head[u];i;i=edge[i].next){
		int e=edge[i].to;
		if (e!=fath) work(e,u);
	}
}
//倍增求LCA
inline int Lca(int u,int v){
	if (d[u]>d[v]) swap(u,v);
	for (res i=20;i>=0;--i) if (d[u]<=d[v]-(1<<i)) v=fa[v][i];
	if (u==v) return u;
	for (res i=20;i>=0;--i) if (fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
//累计
inline void Get(int u,int fath){
	for (res i=head[u];i;i=edge[i].next){
		int e=edge[i].to;
		if (e==fath) continue;
		Get(e,u);
		power[u]+=power[e];
	}
	ans=max(ans,power[u]);
}

int main(){
	n=read(),m=read();
	int x,y;
	for (res i=1;i<n;++i){
		x=read(),y=read();
		add(x,y); add(y,x);
	}
	work(1,0);
	for (res i=1; i<=m; ++i){
		x=read(),y=read();
		int lca=Lca(x,y);
		++power[x];++power[y];--power[lca];--power[fa[lca][0]]; //树上差分
	}
	Get(1,0);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Sagittarius (赞：78)

[【树上差分模板题】](https://www.luogu.org/problemnew/show/P3128)

矩阵的差分应该很简单，典型题目是这样的：

给你一堆数，有n次修改操作，每次给i..j这个区间加上x。最后问所有数中最大的那个。

差分，通俗一点就是把区间的操作改为点操作，在点上记录变化量。上题只需记录dlt[i]+=x,dlt[j+1]-=x，最后用前缀和扫一遍即可。

树上差分，顾名思义就是在树上搞差分。有两种典型题型，一种是边差分，一种是点差分。边差分裸题长这样：

给你一棵树，有n次修改操作，每次把u..v的路径权值加x，最后问从x..y的路径权值和。

![](https://cdn.luogu.com.cn/upload/pic/25763.png)

例如有一次操作是把红点（u）到绿点（v）之间的路径全部加x。那么我就标记dlt[u]+=x,dlt[v]+=x。

![](https://cdn.luogu.com.cn/upload/pic/25764.png)

这样在最后求解的时候，回溯的时候顺便算一下答案就出来了。

然后我们要在lca(u,v)处标记dlt[lca(u,v)]-=2x。这样就使得加x的效果只局限在u..v，不会向lca(u,v)的爸爸蔓延。

点差分和边差分稍有差别：

有n次修改操作，每次把u..v的所有点权都加x，最后问点权最大的为多少。这道题就是最上方链接的那题了。

做法也是和边差分稍有不同，我们不在dlt[lca(u,v)]-=2x，而是把dlt[lca(u,v)]-=x并把dlt[fa[lca(u,v)]]-=x。为什么呢？因为lca(u,v)也在u..v这条路径上，它同样需要被加x。回溯的时候会从u和v两个方向都给lca(u,v)加一个x，而它只能加一个，因此dlt[lca(u,v)]-=x。而lca(u,v)的爸爸则根本无法被加，在lca(u,v)已经只加一个x了，因此dlt[fa[lca(u,v)]]-=x就能让lca(u,v)的爸爸不加x。

具体看代码：

```
#include<bits/stdc++.h>
#define fsb(a,b,c) for (int a=b;a<=c;a++)
#define maxn 50100
#define maxm 100100
#define mem(a,b) memset(a,b,sizeof(a))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
struct edge{
	int p,nt;
}a[maxn*2];
int n,m,x,y,head[maxn],cnt=0,cntb=0,headb[maxn],fa[maxn],vis[maxn],dlt[maxn],faa[maxn],maxx=0;
struct qus{
	int p,nt,mark;
}b[maxm*2];
struct ablca{
	int x,y,z;
}ans[maxm];
inline void adda(int x,int y){
	a[++cnt].p=y;a[cnt].nt=head[x];head[x]=cnt;
}
inline void addb(int x,int y,int z){
	b[++cntb].p=y;b[cntb].mark=z;b[cntb].nt=headb[x];headb[x]=cntb;
}
inline int getf(int x){
	return x==fa[x]?x:fa[x]=getf(fa[x]);
}
inline void dfs1(int u,int f){//tarjan求lca
	faa[u]=f;
	for (int t=headb[u];t!=-1;t=b[t].nt){
		int v=b[t].p;
		if (vis[v]) ans[b[t].mark].z=getf(v);
	}
	// printf("%d ",u);
	vis[u]=1;
	for (int t=head[u];t!=-1;t=a[t].nt){
		int v=a[t].p;if (v==f) continue;
		dfs1(v,u);
		int fau=getf(u),fav=getf(v);
		if (fau!=fav) fa[fav]=fau;
	}
}
inline int dfs2(int u){
	int now=dlt[u],ans=0;
	for (int t=head[u];t!=-1;t=a[t].nt){
		int v=a[t].p;if (v==faa[u]) continue;
		now+=dfs2(v);//now记录点u的修改后点权
	}
	maxx=max(maxx,now);
	return now;
}
int main(){
	// freopen("std.in","r",stdin);
	scanf("%d%d",&n,&m);
	mem(head,255);
	fsb(i,1,n-1){
		scanf("%d%d",&x,&y);adda(x,y);adda(y,x);
	}
	mem(headb,255);
	fsb(i,1,m){
		scanf("%d%d",&ans[i].x,&ans[i].y);
		addb(ans[i].x,ans[i].y,i);addb(ans[i].y,ans[i].x,i);
	}
	fsb(i,1,n) fa[i]=i;mem(vis,0);
	dfs1(1,0);mem(dlt,0);
	fsb(i,1,m){
		dlt[ans[i].x]++;dlt[ans[i].y]++;dlt[ans[i].z]--;dlt[faa[ans[i].z]]--;
	}
	// printf("!!!\n");
	n=dfs2(1);
	printf("%d\n",maxx);
	return 0;
}
```

差分适用于修改多而询问少的情况，本题中只有一次询问，非常适合【别和我说线段树，树链剖分，LCT云云，赛场上写了1个小时调了1个小时结果炸了岂不心态要崩orz一定是我太菜了调不出来orz

---

## 作者：Niki_C_U (赞：27)

第一次贴代码，不知道要求QWQ


最近新学了倍增和树剖，因此用两种方法都写了。


**这道题没什么复杂的，读入就不用说了，用邻接表存储这棵树（我才学会啊好丢人，真心觉得自己好懒），从1~k计算出（u，v）的LCA值，根据书上差分的思想，w[u]和w[v]分别加1，它们的最近公共祖先（LCA）和LCA的父亲各减1，最后再跑一遍DFS累计一下取最大值即可。

邻接表先放出来（是不是多余了QWQ，别吐槽）***

```cpp
int Head[N],Next[N],adj[N],tot;    //太简单不解释
void add(int i,int j)
{
    tot++;
    Next[tot]=Head[i];
    Head[i]=tot;
    adj[tot]=j;
}
```
**1.倍增求LCA**

第一个dfs用来初始化每一个结点的深度及其父节点

```cpp
void dfs(int a)
{
    for(int i=Head[a];i;i=Next[i])        //邻接表的具体用法
    {
        int k=adj[i];
        if(k==p[a][0])
            continue;
        deep[k]=deep[a]+1;            //deep数组存储结点的深度（显而易见）
        p[k][0]=a;                           //p[i][j]表示i的j次方倍祖先
        dfs(k);
    }
}
```
接下来用简单的两层for循环计算出每个结点的j次方倍祖先

```cpp
void init()
{
    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i<=n;i++)
            p[i][j]=p[p[i][j-1]][j-1];
}
```
然后就是LCA的过程了

```cpp
int lca(int a,int b)
{
    if(deep[a]>deep[b])               //保持b在a下面
    {
        int t=a;
        a=b;
        b=t;
    }
    int f=deep[b]-deep[a];
    for(int i=0;(1<<i)<=f;i++)       //调整b使a与b深度相同
        if((1<<i)&f)
            b=p[b][i];
    if(a!=b)
    {
        for(int i=100;i>=0;i--)
            if(p[a][i]!=p[b][i])
                a=p[a][i],b=p[b][i];  //每次跳转至它们的i次方倍祖先
        a=p[a][0];                               //a的父亲就是最终答案
    }
    return a;
}
```
第二次dfs进行简单的统计，每个结点累加其所有孩子结点的权值，再取最大值

```cpp
void dfs2(int a)
{
    for(int i=Head[a];i;i=Next[i])
    {
        int k=adj[i];
        if(k==p[a][0])
            continue;
        dfs2(k);
        d[a]+=d[k];
    }
    ans=max(ans,d[a]);
}
```
主函数就是用来读入和简单调用与计算的，因为代码太拙劣了，就不贴了，大佬们自行脑补哈~


**2.树链剖分求LCA**

第一次dfs初始化出每个结点的深度，父亲，重孩子及子节点的个数

```cpp
void dfs1(int u,int fa,int d)
{
    deep[u]=d,father[u]=fa,size[u]=1;
    for(int e=Head[u];e;e=Next[e])
    {
        int v=adj[e];
        if(v==fa)
            continue;
        dfs1(v,u,d+1);
        size[u]+=size[v];
        if(size[v]>size[son[u]])
            son[u]=v;
    }
}
```
第二次dfs初始化各结点所在重链的深度最小的结点top（如果不在重链上top就为它自己）

```cpp
void dfs2(int u,int tp)
{
    top[u]=tp;
    if(!son[u])
        return;
    dfs2(son[u],tp);
    for(int e=Head[u];e;e=Next[e])
    {
        int v=adj[e];
        if(v!=son[u]&&v!=father[u])
            dfs2(v,v);
    }
}
```
紧接着lca,比较a，b的top的大小，并不断上调

```cpp
int LCA(int a,int b)
{
    while(top[a]!=top[b])
        deep[top[a]]>deep[top[b]]?a=father[top[a]]:b=father[top[b]];
    return deep[a]>deep[b]?b:a;
}
```
最后一次dfs跟上边一样，用来统计一下

```cpp
void dfs3(int u)
{
    for(int e=Head[u];e;e=Next[e])
    {
        int v=adj[e];
        if(v==father[u])
            continue;
        dfs3(v);
        weight[u]+=weight[v];
    }
    ans=max(ans,weight[u]);
}
```
主函数还是一样的拙劣，傲娇不贴！我很懒所以不想打注释了，反正不打你们也能看得懂，何必让我煞费苦心呢23333


**就这么多了，方法可能比较陈旧或者说很复杂，希望大佬指出并指导我修改，谢谢你们！**


---

## 作者：shame_djj (赞：18)

[原题链接·[USACO15DEC]最大流Max Flow](https://www.luogu.org/problem/P3128)

最近在学习树链剖分，

这题一看就知道是树链剖分，

而且是非常简单的树链剖分，

众所周知，树剖题最难的就是模板（~~滑稽~~）。

本题需要注意的地方：

		1、读题，本题读题时我犯了一个错误：
        
		     我把点修改理解成了边修改，无脑地调了四十分钟，
             
		     所以审题要认真QwQ。
                 
		2、关于写出高效代码而不是写出常用代码的问题：
        
		     树剖，我相信大家写的时候都是用的线段树，
                 
		     但是，本题的树剖，完全可以直接用树状数组水过去，
             
		     而且树状数组常数还小QwQ。
             
（我相信会树剖的人一定知道树状数组差分下就能实现区间加的方法，滑稽滑稽）

本来我也是写线段树，

困的不行，调了近一个小时，还是死在了线段树上，

尽管只有一个操作，怎么都死，（~~唉我太菜了~~）

中途，我突然想到，为什么不写树状数组呢？

是啊，为什么不写树状数组呢？

如果我一开始就想到去写树状数组的话，

写这题，根本就用不了20min（可能说多了）。

所以说，尽管大家用线段树用的非常舒服，

当树状数组能直接完成线段树所需操作时，

当然优先选择树状数组啊！

附上代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

int max (int a, int b) {
    return a > b ? a : b;
}

inline int read() {
    char c = getchar(); int x = 0, f = 1;
    for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
    for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

int dep[maxn], fa[maxn], size[maxn], son[maxn];
int ver[maxn], nxt[maxn], head[maxn], tot;
int id[maxn], top[maxn], cnt;
int n, m, x, y;

void add (int u, int v) {
    ver[++ tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

struct shuzhuangshuzu {
    int z[maxn];
    void add (int i, int x) {
        for (; i <= n; i += i & -i)
            z[i] += x;
    }
    void change (int l, int r) {
        add (l, 1), add (r + 1, -1);
    }
    int ask (int i) {
        int ans = 0;
        for (; i; i -= i & -i)
            ans += z[i];
        return ans;
    }
} t;

void dfs1 (int x, int f, int deep) {
    fa[x] = f;
    size[x] = 1;
    dep[x] = deep;
    int maxson = -1;
    for (register int i = head[x]; i; i = nxt[i]) {
        if (ver[i] == f)
            continue;
        dfs1 (ver[i], x, deep + 1);
        size[x] += size[ver[i]];
        if (size[ver[i]] > maxson)
            maxson = size[ver[i]], son[x] = ver[i];
    }
}

void dfs2 (int x, int topf) {
    top[x] = topf;
    id[x] = ++ cnt;
    if (!son[x])
        return ;
    dfs2 (son[x], topf);
    for (register int i = head[x]; i; i = nxt[i]) {
        if (ver[i] == fa[x] || ver[i] == son[x])
            continue;
        dfs2 (ver[i], ver[i]);
    }
}

void update (int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap (x, y);
        t.change (id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap (x, y);
    t.change (id[x], id[y]);
}

void djj () {
    n = read(), m = read();
    for (register int i = 1; i < n; i ++) {
        x = read(), y = read();
        add (x, y), add (y, x);
    }
    dfs1 (1, 1, 1);
    dfs2 (1, 1);
    for (; m; m --) {
        x = read(), y = read();
        update (x, y);
    }
}

void lxy () {
    int ans = 0;
    for (register int i = 1; i <= n; i ++)
        ans = max (ans, t.ask (i));
    printf ("%d\n", ans);
}

void djj_lxy () {
    djj ();
    lxy ();
    exit (0);
}

int main () {
    djj_lxy ();
}
//样例，本题样例算是良心了，不像什么什么Qtree1啊样例水死了
/*
5 10
3 4
1 5
4 2
5 4
5 4
5 4
3 5
4 3
4 3
1 3
3 5
5 4
1 5
3 4

9
*/

```
码风鬼畜，但请勿复制粘贴

树状数组也是一个非常优秀的数据结构：

常数小，好写，

当然它作用有限也是不争的事实，

所以数据结构的选用应该是从题目出发的。

最后强调关于树状数组的一点——

不要写一个名为lowbit的函数，

函数调用需要时间吧，lowbit 字符比 i & -i 多吧，

无论怎么看写一个名为lowbit的函数都非常傻，非常的没有效率。

离新Noip只剩几十天了，祝大家rp++，

也希望自己能更努力一些，加油！！

---

## 作者：Rye_Catcher (赞：12)

- 题目链接：

   https://www.luogu.org/problemnew/show/P3128
   
- 分析

   我想说我比较傻，在做这道题的时候我并没有想到树上差分，而是直接暴力的进行树链剖分，对于每一条给出的树上路径进行修改，用线段树维护，最后把所有标记下传，同时统计最大值。
   
   时间复杂度 $O(K \log^2N)$,比不上众大佬的树上差分，但也是一种较暴力的方法
   
- 代码：

  ```
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <algorithm>
#define ll long long 
#define ri register int 
using namespace std;
const int maxn=50005;
const int inf=0x7fffffff;
template <class T>inline void read(T &x){
      x=0;int ne=0;char c;
      while(!isdigit(c=getchar()))ne=c=='-';
      x=c-48;
      while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
      x=ne?-x:x;
      return ;
}
int n,k;
struct Edge{
      int ne,to;
}edge[maxn<<1];
int h[maxn],num_edge=0;
inline void add_edge(int f,int to){
       edge[++num_edge].ne=h[f];
       edge[num_edge].to=to;
       h[f]=num_edge;
       return ;
}
int cnt=0;
int dep[maxn],fa[maxn],son[maxn],top[maxn],dfn[maxn],rnk[maxn],size[maxn];
int L,R,dta;
void dfs_1(int now){
       int  v;
       size[now]=1;
       for(ri i=h[now];i;i=edge[i].ne){
           v=edge[i].to;
           if(v==fa[now])continue;
           dep[v]=dep[now]+1,fa[v]=now;
           dfs_1(v);
           size[now]+=size[v];
           if(!son[now]||size[son[now]]<size[v])son[now]=v;
       }
       return ;
} 
void dfs_2(int now,int t){
       int v;
       top[now]=t,dfn[now]=++cnt,rnk[cnt]=now;
       if(!son[now])return ;
       dfs_2(son[now],t);
       for(ri i=h[now];i;i=edge[i].ne){
             v=edge[i].to;
             if(v==fa[now]||v==son[now])continue;
             dfs_2(v,v);
       }
       return ;
}
int sum[maxn<<2],mx[maxn<<2],tag[maxn<<2];
void build(int now,int l,int r){
       if(l==r){
              sum[now]=mx[now]=0;
              return ;
       }
       int mid=(l+r)>>1;
       build(now<<1,l,mid);
       build(now<<1|1,mid+1,r);
       sum[now]=sum[now<<1]+sum[now<<1];
       mx[now]=max(mx[now<<1],mx[now<<1|1]);
       return ;
}
void pushdown(int now,int ln,int rn){
       if(tag[now]){
             sum[now<<1]+=tag[now]*ln;
             sum[now<<1|1]+=tag[now]*rn;
             mx[now<<1]+=tag[now];
             mx[now<<1|1]+=tag[now];
             tag[now<<1]+=tag[now];
             tag[now<<1|1]+=tag[now];
             tag[now]=0;
       }
       return ;
}
void update(int now,int l,int r){
       if(L<=l&&r<=R){
               sum[now]+=dta*(r-l+1);
               mx[now]+=dta;
               tag[now]+=dta;
               return ;
       }
       int mid=(l+r)>>1;
       if(L<=mid)update(now<<1,l,mid);
       if(mid<R)update(now<<1|1,mid+1,r);
       sum[now]=sum[now<<1]+sum[now<<1|1];
       mx[now]=max(mx[now<<1],mx[now<<1|1]);
       return ;
}
int query_mx(int now,int l,int r){
       if(L<=l&&r<=R){
               return mx[now];
       }
       int mid=(l+r)>>1,ans=-inf;
       pushdown(now,mid-l+1,r-mid);
       if(L<=mid)ans=max(ans,query_mx(now<<1,l,mid));
       if(mid<R)ans=max(ans,query_mx(now<<1|1,mid+1,r));
       sum[now]=sum[now<<1]+sum[now<<1|1];
       mx[now]=max(mx[now<<1],mx[now<<1|1]);
       return ans;
}
int all_push(int now,int l,int r){
       if(l==r){
              return mx[now];
       }
       int mid=(l+r)>>1,ans=-inf;
       pushdown(now,mid-l+1,r-mid);
       ans=max(ans,all_push(now<<1,l,mid));
       ans=max(ans,all_push(now<<1|1,mid+1,r));
       return ans;
}
void update_path(int x,int y,int k){
        dta=k;
        while(top[x]!=top[y]){
                if(dep[top[x]]<dep[top[y]])swap(x,y);
                L=dfn[top[x]],R=dfn[x];
                update(1,1,n);
                x=fa[top[x]];
        }
        if(dfn[x]>dfn[y])swap(x,y);
        L=dfn[x],R=dfn[y];
        update(1,1,n);
        return ;
}
int main(){
     int x,y,z;
     //double st=clock();
     read(n),read(k);
     for(ri i=1;i<n;i++){
             read(x),read(y);
             add_edge(x,y);
             add_edge(y,x);
     }  
     dep[1]=1,fa[1]=1;
     dfs_1(1);
     dfs_2(1,1);
     for(ri i=1;i<=k;i++){
             read(x),read(y);
             update_path(x,y,1);
     }
     //double ed=clock();
     printf("%d\n",all_push(1,1,n));
     //printf("%lf\n",ed-st);
     return 0;
}
```

---

## 作者：Segmentree (赞：10)

1. 首先，我们通过阅读题干的建边不难发现这道题是以**树形结构**为背景的。

2. 继续往下看：给定两个隔间u,v，使得u->v这条路径上的所有隔间的压力（点权）加一，小脑瓜~~疯狂转动~~，这不是区间修改吗！那么是时候运用蒟蒻我~~唯一会的~~修改区间算法———**差分**了！

我们提取这两段的两个关键词 “**树形结构**”，“**差分**”，~~巴啦啦摸仙全身变~~ 树上差分！


因此这道题的思路就非常清晰了：

1. ~~建树~~
2. 树上差分（用lca辅助其实现，如果还有对lca不熟的同学可以前往[**P3379 【模板】最近公共祖先（LCA）**](https://www.luogu.org/problem/P3379)理解一下这个在树上巨有用的算法）

# Code：
```cpp
/*Coded By Lxhao*/
/*Full Of Stars*/
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define re register
#define r(x) x=read()
#define c getchar()
#define ll long long
inline int read()
{
    int w=1,s=0;
    char ch=c;
    while(ch>'9'||ch<'0'){if(ch=='-')w=-1;ch=c;}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=c;
    return s*w;
}
const int maxn=5e4+10;
int n,k,cnt,x,y,fnl;
int f[maxn][21],depth[maxn],head[maxn],sum[maxn];
//f[i][j]表示以i为起点往上跳2^j个点，depth表示深度，sum为前缀和数组
struct node
{
    int to,next,dis;
}edge[maxn<<1];
inline void add(int from,int to)
{
    edge[++cnt].next=head[from];
    edge[cnt].to=to;
    head[from]=cnt;
}
inline int max(int a,int b){return a>b?a:b;}
inline void dfs(int u,int fa)
{
    f[u][0]=fa;//2^0=1,所以f[u][0]存的是他的父亲节点
    depth[u]=depth[fa]+1;//叶子结点的深度比父亲节点大一
    for(re int i=1;(1<<i)<=depth[u];++i)f[u][i]=f[f[u][i-1]][i-1];//往上跳（倍增思想）
    for(re int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v!=fa) dfs(v,u);
    }
}//建树
inline int lca(int u,int v)
{
    if(depth[u]<depth[v])swap(u,v);
    for(re int i=20;i>=0;--i)
    {
        if((1<<i)<=depth[u]-depth[v])
            u=f[u][i];
    }//u为深度较深的一点，先跳u使u，v达到同一深度
    if(u==v) return u;
    for(re int i=20;i>=0;--i)
    {
        if(f[u][i]!=f[v][i])
        {
            u=f[u][i];
            v=f[v][i];
        }
    }//达到同一深度后一起跳
    return f[u][0];
}
inline void Gmax(int u,int fa)
{
    for(re int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v!=fa)
        {
            Gmax(v,u);
            sum[u]+=sum[v];
        }
    }
    fnl=max(fnl,sum[u]);
}//用dfs来求以树为基础的查分数组的最大值
int main()
{
    r(n),r(k);
    for(re int i=1,u,v;i<=n-1;++i)
    {
        r(u),r(v);
        add(u,v),add(v,u);
    }//建双向边
    dfs(1,0);
    for(;k;k--)
    {
        r(x),r(y);
        int fa=lca(x,y);
        ++sum[x],++sum[y];
        --sum[fa],--sum[f[fa][0]];
    }//树上差分修改区间值
    Gmax(1,0);//求最值
    printf("%d",fnl);
}
```
谢谢观看，如有不足请多指出qwq

---

## 作者：hyfhaha (赞：8)

# 简单树剖
没什么好讲的，只把几个操作说一下：

1、每一次操作都把x到y的点权都加1

2、最后查一下整个树的点权最大值

只需要对【模板】树链剖分 的线段树部分略加修改就OK了，修改就是把累加变成求最大值，简单得不行了。

# 代码：
```cpp
#include<bits/stdc++.h>
#define maxn 4000001
#define L(x) (x<<1)
#define R(x) ((x<<1)|1)
using namespace std;
int tree[maxn],tag[maxn];
int rev[maxn],dep[maxn],size[maxn],seg[maxn],top[maxn],son[maxn],father[maxn];
int n,m,root,x,y,z,a[maxn],visx[maxn],visy[maxn],tot;
int cnt,from[maxn],to[maxn],Next[maxn],head[maxn];
char mode;
void add(int x,int y){
    cnt++;
    from[cnt]=x;to[cnt]=y;
    Next[cnt]=head[x];head[x]=cnt;
}
void pushdown(int node,int begin,int end){
    if(tag[node]){
        tag[L(node)]+=tag[node];
        tag[R(node)]+=tag[node];
        int mid=(begin+end)>>1;
        tree[L(node)]+=tag[node];
        tree[R(node)]+=tag[node];
        tag[node]=0;
    }
}
void update(int node,int begin,int end,int x,int y,int val){
    if(begin>y||end<x)return;
    if(begin>=x&&end<=y){
        tag[node]+=val;
        tree[node]+=val;
        return;
    }else{
        pushdown(node,begin,end);
        int mid=(begin+end)>>1;
        if(x<=mid)update(L(node),begin,mid,x,y,val);
        if(y>mid) update(R(node),mid+1,end,x,y,val);
        tree[node]=max(tree[L(node)],tree[R(node)]);
    }
}
int query(int node,int begin,int end,int x,int y){
    if(begin>=x&&end<=y){
        return tree[node];
    }else{
        pushdown(node,begin,end);
        int mid=(begin+end)>>1,sum=0;
        if(x<=mid)sum=max(query(L(node),begin,mid,x,y),sum);
        if(y>mid) sum=max(query(R(node),mid+1,end,x,y),sum);
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
int treequery(int x){
    return query(1,1,seg[0],seg[x],seg[x]+size[x]-1);
}
void linkadd(int x,int y,int z){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
        update(1,1,seg[0],seg[fx],seg[x],z);
        x=father[fx];fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    update(1,1,seg[0],seg[x],seg[y],z);
}
int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);root=1;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        add(x,y);add(y,x);
    }
    dfs1(root);
    seg[root]=++seg[0];
    rev[seg[0]]=root;
    top[root]=root;
    dfs2(root);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        linkadd(x,y,1);
    }
    printf("%d\n",treequery(root));
}
```

---

## 作者：QwQ2000 (赞：7)

真的不需要树剖啦

LCA裸题

这是一个标准的树上差分问题

做法是这样的

对于一个路径(u,v)

使得u v 权值各+1

lca(u,v)和lca(u,v)的父亲 权值都-1

然后最后做一遍dfs 从叶子开始 使每个点的权值等于其子树的权值和

那么每个点的权值就是他的答案了

讲道理很多USACO题真的非常非常简单啦 而且都有中文翻译

洛谷的广大OIER们 是不是看见英文就打怵啊……

其实这些题完全可以做一做嘛 QAQ

上代码

[codec]












```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N=50005;
int n=0,k=0;
int head[N*2],next[N*2],to[N*2],edge=0;
int fa[N][20],depth[N],w1[N],w2[N];
int ans=0;
inline void addEdge(int u,int v) {
    to[edge]=v,next[edge]=head[u],head[u]=edge++;
    to[edge]=u,next[edge]=head[v],head[v]=edge++;
}
void dfs1(int x,int f,int d) {
    depth[x]=d;
    fa[x][0]=f;
    for (int e=head[x];~e;e=next[e]) {
        int& v=to[e];
        if (v!=f)
            dfs1(v,x,d+1);
    }    
}
inline void init() {
    for (int j=1;(1<<j)<=n;++j)
        for (int i=1;i<=n;++i)
            if (fa[i][j-1]!=-1)
                fa[i][j]=fa[fa[i][j-1]][j-1];
}
inline int lca(int u,int v) {
    if (depth[u]<depth[v])
        swap(u,v);    
    int i=0;
    for (;(1<<i)<=n;++i)
        ;
    --i;
    for (int j=i;j>=0;--j)
        if (depth[u]-(1<<j)>=depth[v])
            u=fa[u][j];
    if (u==v)
        return u;
    for (int j=i;j>=0;--j)
        if (fa[v][j]!=fa[u][j] && fa[u][j]!=-1) {
            u=fa[u][j];
            v=fa[v][j];
        }
    return fa[u][0];
}
inline void plus(int x,int y) {
    int z=lca(x,y);
    ++w1[x],++w1[y];
    --w1[z];
    if (fa[z][0]!=-1)
        --w1[fa[z][0]];
}
void dfs2(int x,int f) {
    w2[x]=w1[x];
    for (int e=head[x];~e;e=next[e]) {
        int& v=to[e];
        if (v!=f) {
            dfs2(v,x);
            w2[x]+=w2[v];
        }
    }        
    ans=max(ans,w2[x]);
}
int main(void) {
    memset(head,-1,sizeof(head));
    memset(fa,-1,sizeof(fa));
    scanf("%d %d",&n,&k);
    for (int i=1;i<=n-1;++i) {
        int u=0,v=0;
        scanf("%d %d",&u,&v);
        addEdge(u,v);
    }    
    dfs1(1,-1,1);
    init();
    while (k--) {
        int x=0,y=0;
        scanf("%d %d",&x,&y);
        plus(x,y);
    } 
    dfs2(1,-1);
    printf("%d\n",ans);
    return 0;
} 
[codec/]
```

---

## 作者：da32s1da (赞：5)

这道题可看做[P3258 [JLOI2014]松鼠的新家](https://www.luogu.org/problemnew/show/P3258)的简化版。

思路显然，树剖LCA+差分

另外，$a[b[c[d]]]=d[c][b][a]$
```
#include<cstdio>
const int N=50050;
int to[N<<1],la[N<<1],fi[N<<1],CNT;
inline void add_edge(int u,int v){ //存边
	to[++CNT]=v;la[CNT]=fi[u];fi[u]=CNT;
	to[++CNT]=u;la[CNT]=fi[v];fi[v]=CNT;
}
int dep[N],fa[N],siz[N],son[N]; //第一遍dfs需要
int rnk[N],bh[N],top[N],BH; //第二遍dfs需要
void dfs1(int u,int v,int depth){
	dep[u]=depth;fa[u]=v;siz[u]=1; //设置深度，父亲，大小
	for(int i=fi[u];i;i=la[i])
	if(to[i]!=v){
		dfs1(to[i],u,depth+1);siz[u]+=siz[to[i]]; //子树最大的为儿子
		if(i[to][siz]>u[son][siz]) son[u]=to[i];
	}
}
void dfs2(int u,int v){
	top[u]=v;bh[u]=BH;rnk[BH]=u;BH++; //设置top，编号，编号对应节点
	if(son[u]) dfs2(son[u],v); //优先搜索重儿子
	for(int i=fi[u];i;i=la[i])
	if(to[i]!=fa[u]&&to[i]!=son[u])
	dfs2(to[i],to[i]);
}
int lca(int u,int v){ //树剖LCA
	while(top[u]!=top[v]){
		if(u[top][dep]<v[top][dep]) u^=v^=u^=v;
		u=u[top][fa];
	}
	return dep[u]<dep[v]?u:v;
}
int n,m,p,q,f[N],ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	scanf("%d%d",&p,&q),add_edge(p,q);
	dfs1(1,0,1);
	dfs2(1,1);
	for(int i=1;i<=m;i++){//显然，两节点+1，LCA及其父亲-1
		scanf("%d%d",&p,&q);int lc=lca(p,q);
		p[bh][f]++;q[bh][f]++;lc[bh][f]--;lc[fa][bh][f]--;
	}
	for(int i=n;i>=1;i--){
		ans=ans<f[i]?f[i]:ans;//更新答案
		i[rnk][fa][bh][f]+=f[i];
	}
	printf("%d\n",ans);
}
```

---

## 作者：zpl__hhd (赞：4)

# 蒟蒻的第一个题解 ，各位DALAO勿喷
## 纪念A的~~第二道蓝题~~（小蒟蒻惶恐）
~~一道裸的树剖题~~，过了模板的人应该都知道怎么做。

这里直接贴代码，具体的讲解看代码就行。

连线段树都不知道的请移步（蒟蒻的成长之路（滑稽））[浅谈线段树](https://www.cnblogs.com/TheRoadToTheGold/p/6254255.html)
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,tot,s,cnt,a,b,x,y=1,p=1,mod=200000000,ans1=0;
int ans[5],son[50010],f[50010],top[50010],id[50010];
int d[50010],head[50010],size[50010],q[50010];
struct tree
{
	int l,r,w,f;
}tree[200010];//线段树 
inline void build(int k,int ll,int rr)//建树
{
	tree[k].l=ll;tree[k].r=rr;
	if(tree[k].l==tree[k].r)
	{
		tree[k].w=0;//初值为0
		return;
	}
	build(2*k,ll,(ll+rr)/2);
	build(2*k+1,(ll+rr)/2+1,rr);
	tree[k].w=(tree[2*k].w+tree[2*k+1].w)%mod;
    //直接CV的模板，把mod设为最大就行，可以去掉
}
inline void down(int k)//下传
{
	(tree[2*k].f+=tree[k].f)%=mod;
	(tree[2*k+1].f+=tree[k].f)%=mod;
	(tree[2*k].w+=(tree[2*k].r-tree[2*k].l+1)*tree[k].f)%=mod;
	(tree[2*k+1].w+=(tree[2*k+1].r-tree[2*k+1].l+1)*tree[k].f)%=mod;
	tree[k].f=0;
}
inline void check1(int k)
{
	if(tree[k].l==tree[k].r)
	{
		(ans[p]+=tree[k].w)%=mod;
		return;
	}
	if(tree[k].f)down(k);
	int mid=(tree[k].l+tree[k].r)/2;
	if(x<=mid)check1(2*k);
	else check1(2*k+1);
}
inline void add1(int k)
{
	if(tree[k].l==tree[k].r)
	{
		(tree[k].w+=y)%=mod;
		return;
	}
	if(tree[k].f)down(k);
	int mid=(tree[k].l+tree[k].r)/2;
	if(x<=mid)add1(2*k);
	else add1(2*k+1);
	tree[k].w=(tree[2*k].w+tree[2*k+1].w)%mod;
}
inline void add2(int k)
{
	if(a<=tree[k].l&&b>=tree[k].r)
	{
		(tree[k].w+=(tree[k].r-tree[k].l+1)*y)%=mod;
		(tree[k].f+=y)%=mod;
		return;
	}
	if(tree[k].f)down(k);
	int m=(tree[k].l+tree[k].r)/2;
	if(a<=m)add2(2*k);
	if(b>m)add2(2*k+1);
	tree[k].w=(tree[2*k].w+tree[2*k+1].w)%mod;
}
struct edge 
{
	int to,next;//邻接表标配 
}e[100010];
void add(int f,int t)
{
	e[++tot].to=t;
	e[tot].next=head[f];
	head[f]=tot;//邻接表加边函数 
}
void dfs(int k)//这个DFS用来求最大值
{
	x=id[k];
	check1(1);
	ans1=max(ans1,ans[p]);
	ans[p]=0;
	for(int i=head[k];i;i=e[i].next)
	{
		if(e[i].to==f[k])continue;
		dfs(e[i].to);
	}
}
void dfs1(int k)//确定size,d,f,son; 
{
	size[k]=1;
	d[k]=d[f[k]]+1;
	for(int i=head[k];i;i=e[i].next)
	{
		if(e[i].to==f[k])continue;//父节点过滤 
		f[e[i].to]=k;
		dfs1(e[i].to);
		size[k]+=size[e[i].to];
		if(!son[k]||size[e[i].to]>size[son[k]])//确定重儿子 
		son[k]=e[i].to;
	}
}
void dfs2(int k,int t)//确定id,top 
{
	id[k]=++cnt;//DFS序 
	top[k]=t;
	if(!son[k])return;//叶节点过滤 
	dfs2(son[k],t);//先遍历重链，保证重链的DSF序连续，方便线段树维护 
	for(int i=head[k];i;i=e[i].next)
	{
		if(e[i].to==f[k]||e[i].to==son[k])//父节点和重儿子过滤（很重要） 
		continue;
		dfs2(e[i].to,e[i].to);//轻边的链顶要改变 
	}
}
void tree_add1(int u,int v)//两点间路径修改 
{
	while(top[u]!=top[v])
	{
		if(d[top[u]]<d[top[v]])swap(u,v);
		//切记是d[top[u]]而不是d[u] 蒟蒻第一次学树剖时就一直卡在这里 
		a=id[top[u]];b=id[u];
		add2(1);
		u=f[top[u]];
	}
	if(u==v){x=id[u];add1(1);return;}//u=v时特判，加上V的权 
	if(d[u]<d[v])
	{a=id[u];b=id[v];}
	else {a=id[v];b=id[u];}
	add2(1);
}
int main()
{ 
	cin>>n>>m;
	for(int i=1;i<=n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
        //如果想更快一点，加个快读，这里就不打了。
	}
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		tree_add1(u,v);
	}
	dfs(1);
	cout<<ans1;
}

```
用时约2.3s。（毕竟是蒟蒻）

### 现在介绍一种新的方法：伟大的树上差分

顾名思义，树上差分，即树的差分。

不知道差分的移步[差分和前缀和](https://www.cnblogs.com/MS903/p/11244969.html)

真的是一种贼厉害的方法，可以把O(n)的复杂度变成O（1），快了n倍。

如果要将u,v间的路径每一个权值都加上x

设a=lca（u，v），b为a的父亲。

则将v+x,u+x,a-x,b-x，我们就完成了一次树上差分

怎么样？是不是很简洁?~~就像嗑了金坷垃。~~

在最后统计一次DFS每个节点的子树和就完成啦！不理解的可以自己画图试试。

可以顺便在DFS中求出最大值

愉快的贴上代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,tot,s,ans=-1;
int son[50010],f[50010],top[50010];
int d[50010],head[50010],size[50010],q[50010],ve[50010];
struct edge 
{
	int to,next;//邻接表标配 
}e[100010];
void add(int f,int t)
{
	e[++tot].to=t;
	e[tot].next=head[f];
	head[f]=tot;//邻接表加边函数 
}
void dfs1(int k)//确定size,d,f,son; 
{
	size[k]=1;
	d[k]=d[f[k]]+1;
	for(int i=head[k];i;i=e[i].next)
	{
		if(e[i].to==f[k])continue;//父节点过滤 
		f[e[i].to]=k;
		dfs1(e[i].to);
		size[k]+=size[e[i].to];
		if(!son[k]||size[e[i].to]>size[son[k]])//确定重儿子 
		son[k]=e[i].to;
	}
}
void dfs2(int k,int t)//确定id,top 
{
	top[k]=t;
	if(!son[k])return;//叶节点过滤 
	dfs2(son[k],t);//先遍历重链，保证重链的DSF序连续，方便线段树维护 
	for(int i=head[k];i;i=e[i].next)
	{
		if(e[i].to==f[k]||e[i].to==son[k])//父节点和重儿子过滤（很重要） 
		continue;
		dfs2(e[i].to,e[i].to);//轻边的链顶要改变 
	}
}
int lca(int u,int v)//树剖求LCA
{
	while(top[u]!=top[v])
	{
	 if(d[top[u]]>d[top[v]])
	 u=f[top[u]];
	 else v=f[top[v]];
	}
	if(d[u]<d[v])return u;
	else return v;
}
void cf(int u,int v)//差分函数
{
	q[u]+=1;
	q[v]+=1;
	int k=lca(u,v);
	q[k]-=1;
	q[f[k]]-=1;
}
void dfs(int k)
{
	ve[k]=q[k];
	for(int i=head[k];i;i=e[i].next)
	{
		if(e[i].to==f[k])continue;
		dfs(e[i].to);
		ve[k]+=ve[e[i].to];
	}
	ans=max(ans,ve[k]);//求最大值
}
int main()
{ 
	cin>>n>>m;
	for(int i=1;i<=n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs1(1);
	dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		cf(u,v); 
	}
	dfs(1);
	cout<<ans;
}

```

约500ms，完美！














---

## 作者：Long·J·William (赞：4)

GPP树链剖分

储存：

e~边相关；

p~ 点相关；

t~线段树相关；

函数：

DFS1 get 点的深度，父亲，重儿子，子树大小；

DFS2 get 点的dfs序，链首节点；

change 线段树区间修改；

```cpp
down 线段树标记下传；
#include<cstdio>
const int maxn=5e4+10;
inline int min_(int x,int y){return x<y?x:y;}
inline int max_(int x,int y){return x>y?x:y;}
inline int swap_(int&x,int&y){x^=y,y^=x,x^=y;}
int n,k;
int a,b;
int eh[maxn],hs,et[maxn<<1],en[maxn<<1];
int pd[maxn],pf[maxn],pws[maxn],psz[maxn],pps,pp[maxn],pt[maxn];
int ts[maxn<<2],tf[maxn<<2];
void dfs1(int k,int f,int d){
    psz[k]=1,pd[k]=d,pf[k]=f;
    for(int i=eh[k];i;i=en[i])
    if(et[i]!=f){
        dfs1(et[i],k,d+1);
        psz[k]+=psz[et[i]];
        if(psz[et[i]]>psz[pws[k]]) pws[k]=et[i];
    }
}
void dfs2(int k,int t){
    pp[k]=++pps,pt[k]=t;
    if(pws[k]) dfs2(pws[k],t);
    for(int i=eh[k];i;i=en[i])
    if(et[i]!=pf[k]&&et[i]!=pws[k])
    dfs2(et[i],et[i]);
}
void down(int k){
    int ls=k<<1,rs=ls|1;
    ts[ls]+=tf[k],ts[rs]+=tf[k];
    tf[ls]+=tf[k],tf[rs]+=tf[k];
    tf[k]=0;
}
void change(int k,int l,int r,int al,int ar){
    if(l==al&&r==ar){ts[k]++,tf[k]++;return;}
    if(tf[k]) down(k);
    int mid=l+r>>1,ls=k<<1,rs=ls|1;
    if(al<=mid) change(ls,l,mid,al,min_(ar,mid));
    if(ar>mid) change(rs,mid+1,r,max_(al,mid+1),ar);
    ts[k]=max_(ts[ls],ts[rs]);
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        ++hs,et[hs]=b,en[hs]=eh[a],eh[a]=hs;
        ++hs,et[hs]=a,en[hs]=eh[b],eh[b]=hs;
    }
    dfs1(1,0,1);
    dfs2(1,1);
    while(k--){
        scanf("%d%d",&a,&b);
        while(pt[a]!=pt[b]){
            if(pd[pt[a]]<pd[pt[b]]) swap_(a,b);
            change(1,1,n,pp[pt[a]],pp[a]);
            a=pf[pt[a]];
        }
        if(pd[a]<pd[b]) swap_(a,b);
        change(1,1,n,pp[b],pp[a]);
    }
    printf("%d\n",ts[1]);
    return 0;
}
```
吐槽一下，楼下对线段上值的处理有问题，方法是可行的，但是逻辑有问题，不信各位可以试一试这组数据：
2 4
1 2

2 1
2 2
2 2
2 1

---

## 作者：Enzymii (赞：4)

###为这个题通过率的降低做出了巨大的贡献……

这题，说白了，裸树上差分。。。

###**树上差分**：对于树上x,y之间的路径区间修改时，设数组为c，则c[x]+1,c[y]+1,c[lca(x,y)]-1,c[father[lca(x,y)]-1.

###最后dfs一下，使每个节点c[x]+=每个子节点的c值就ok了..

就是用这个性质。。。重点就是在于求LCA的地方了。。这里我用的Tarjan，话说是真快。。

第一遍：我试图在Tarjan过程中就差分，结果……6分（就过了样例），后来调了一晚上不行，然后……忘了。。。

今天学了网络流，然后luogu搜最大流，发现了这道题，然后6分挂着不爽，就来做啊。。

第二遍：发现自己可以先端点都加上，处理出所有的LCA，顺便求父亲，然后再差分。。结果交的时候把调试输出的c数组输出了orz...

第三遍：终于A了，来写题解。。

好吧，闲话说了不少，下面上代码：

```cpp
#include<cstdio>
#define N 50005
#define M 100005
#define gc getchar //足可见我懒得皮疼
struct edge
{
    int to,next;
}e[N<<1];
struct ques
{
    int to,next,id;
}f[M<<1];
int n,m,u[N],v[N],c[N],fa[N],up[N],ans[M],tot,tit=0,maxn=0;
bool vis[N],vis2[N];
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]); //据说这样写并查集的find比较优美..
}
void qin(int &a)                                   //臃肿的快读
{
    a=0;char c=gc();bool f=0;
    for(;(c<'0'||c>'9')&&c!='-';c=gc());
    if(c=='-') f=1,c=gc();
    for(;c>='0'&&c<='9';c=gc()) a=a*10+c-'0';
    if(f) a=-a;
}
void build(int x,int y)
{
    e[++tot].to=y; e[tot].next=v[x]; v[x]=tot;
    e[++tot].to=x; e[tot].next=v[y]; v[y]=tot;
}
void quest(int x,int y,int z)
{
    f[++tit].to=y; f[tit].next=u[x]; u[x]=tit; f[tit].id=z;
    f[++tit].to=x; f[tit].next=u[y]; u[y]=tit; f[tit].id=z;
}
void dfs(int x)                                          //Tarjan
{
    vis[x]=1; fa[x]=x;
    for(int i=v[x];i;i=e[i].next)
        if(!vis[e[i].to])
            up[e[i].to]=x,dfs(e[i].to),fa[e[i].to]=x;
    for(int i=u[x];i;i=f[i].next)
        if(vis[f[i].to])
            ans[f[i].id]=find(f[i].to);
}
void dfs2(int x)                                      //差分，遍历树
{
    vis2[x]=1;
    for(int i=v[x];i;i=e[i].next)
    {
        int y=e[i].to;
        if(!vis2[y]) dfs2(y),c[x]+=c[y];
    }
    if(c[x]>maxn) maxn=c[x];
}
int main()
{
    qin(n);qin(m);
    for(int i=1;i<n;i++)
    {
        int a,b;qin(a),qin(b);
        build(a,b);
    }
    for(int i=1;i<=m;i++)
    {
        int a,b;qin(a),qin(b);
        c[a]++;c[b]++;
        quest(a,b,i);
    }
    dfs(1);
    for(int i=1;i<=m;i++)
        c[ans[i]]--,c[up[ans[i]]]--;    
    dfs2(1);
    printf("%d\n",maxn);
}
```
//就是这样了。。


---

## 作者：XG_Zepto (赞：4)

## 思路

实际上就是求被每个点被不同的路径覆盖了几次。只要把每条路径经过的点的答案加1即可。树剖和树状数组或线段树可以轻松搞定。

但是我们发现，这道题可以用LCA和树上查分更加优美而快速地解决。对于一条路径，将两个端点的值加1，它们的LCA和LCA的父亲分别减1，最后DFS累加一下就可以得到每个点的答案，取最大值即可。

## 代码

不同的模块写得非常清楚了，变量和函数解释如下：

- $l$数组和$head$数组：前向星存边。
- $s$数组：记录每个点的答案。
- $d$数组：每个点的深度。
- $p[i][j]$：第j个点向上走i^2步到达的点。
- $Pre$_$Work$函数：预处理出d和p。
- $Solve$函数：求LCA，单点修改。
- $Sum$函数：累加。
```
#include <bits/stdc++.h>
#define maxn 50001
using namespace std;
struct Edge{
    int to,next;
    Edge(int a=0,int b=0){
        to=a,next=b;
    }
}l[maxn*4];
int head[maxn],s[maxn],n,k,t1,t2;
int d[maxn],p[30][maxn],cnt,ans;
void Add(int x,int y){
    l[++cnt]=Edge(y,head[x]);
    head[x]=cnt;
}
void Pre_Work(int u,int f){
    d[u]=d[f]+1;
    p[0][u]=f;
    for (int i=1;(1<<i)<=d[u];i++)
    p[i][u]=p[i-1][p[i-1][u]];
    for (int i=head[u];i;i=l[i].next){
        int v=l[i].to;
        if (v!=f) Pre_Work(v,u);
    }
}
void Solve(int a,int b){
    int lca;s[a]++,s[b]++;
    if (d[a]<d[b]) swap(a,b);
    for (int i=28;i>=0;i--)
    if (d[p[i][a]]>=d[b]) a=p[i][a];
    if (a==b) lca=a;
    else {
        for (int i=28;i>=0;i--)
        if (p[i][a]!=p[i][b])
        a=p[i][a],b=p[i][b];
        lca=p[0][a];
    }
    s[lca]--;
    s[p[0][lca]]--;
}
void Sum(int u,int f){
    for (int i=head[u];i;i=l[i].next){
        int v=l[i].to;
        if (v==f) continue;
        Sum(v,u);
        s[u]+=s[v];
    }
    ans=max(s[u],ans);
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for (int i=1;i<n;i++){
        cin>>t1>>t2;
        Add(t1,t2);
        Add(t2,t1);
    }
    Pre_Work(1,0);
    for (int i=1;i<=k;i++){
        cin>>t1>>t2;
        Solve(t1,t2);
    }
    Sum(1,0);
    cout<<ans<<endl;
}
```

---

## 作者：夏色祭 (赞：3)

最近新学了树剖。。。明明知道可以用树上差分。。。但是我还是花了30min写了个简单的线段树+树剖。。。


第一次交的时候居然线段树里的down写了++。。。然后没有爆0是最骚的。。写的时候也是石乐志明明想着要写+=lazy却写了++。。。~~感觉我已经是条废鱼了~~


好了不多xjb哔哔了，还是讲思路。


**华丽丽的分割线--------------------------------------------------------------------**


~~好像没什么好讲的。。。~~裸的树剖套个线段树，线段树每个节点的sum表示当前结点所表示的区间的最大值。


不难发现每次的操作都是整段区间所有的数+1，也就是说最大值肯定是之前的最大值+1，而一开始全为0。。。~~那不就很简单了吗~~


还是再给同学们留下点思考空间吧。。。


直接上代码：

```cpp
#include<cstdio>
#define For(i,x,y) for (int i=x;i<=y;i++)
#define cross(i,k) for (int i=first[k];i!=0;i=last[i])
#define N 50010
using namespace std;
struct tree{
    int sum,lazy;
}a[8*N];
int to[2*N],last[2*N],first[N];
int n,m,x,y,tot;
void add(int u,int v){tot++,to[tot]=v,last[tot]=first[u],first[u]=tot;}
int size[N],son[N],fa[N],dep[N];
void dfs1(int k){
    size[k]=1,dep[k]=dep[fa[k]]+1;
    cross(i,k){
        int v=to[i];
        if (v==fa[k]) continue;
        fa[v]=k,dfs1(v);
        size[k]+=size[v];
        if (!son[k]||size[son[k]]<size[v]) son[k]=v;
    }
}
int idc,tree[N],idx[N],top[N];
void dfs2(int k,int tp){
    top[k]=tp,idc++,idx[k]=idc,tree[idc]=k;
    if (!son[k]) return;
    dfs2(son[k],tp);
    cross(i,k){
        int v=to[i];
        if (v==son[k]||v==fa[k]) continue;
        dfs2(v,v);
    }
```
}//简单的树剖

```cpp
void down(int k){
    if (!a[k].lazy) return;
    a[k << 1].lazy+=a[k].lazy,a[k << 1^1].lazy+=a[k].lazy;
    a[k << 1].sum+=a[k].lazy,a[k << 1^1].sum+=a[k].lazy;
    a[k].lazy=0;
}
int max(int x,int y){
    if (x>y) return x;
        else return y;
}
void ud(int k,int l,int r,int ql,int qr){
    if (l>qr||ql>r) return;
    if (l>=ql&&r<=qr){
        a[k].lazy++,a[k].sum++;
        down(k);
        return;    
    }
    down(k);
    int mid=l+r >> 1;
    ud(k << 1,l,mid,ql,qr),ud(k << 1^1,mid+1,r,ql,qr);
    a[k].sum=max(a[k << 1].sum,a[k << 1^1].sum);
```
}//简单的线段树

```cpp
void swap(int &x,int &y) {int t;t=x,x=y,y=t;}
void change(int x,int y){
    while (top[x]!=top[y]){
        if (dep[top[x]]>=dep[top[y]]) ud(1,1,n,idx[top[x]],idx[x]),x=fa[top[x]]; 
            else ud(1,1,n,idx[top[y]],idx[y]),y=fa[top[y]];
    }
    if (dep[x]>dep[y]) swap(x,y);
    ud(1,1,n,idx[x],idx[y]);
```
}//简单的修改

```cpp
int main(){
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    scanf("%d%d",&n,&m);
    For(i,1,n-1){
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    For(i,1,m){
        scanf("%d%d",&x,&y);
        change(x,y);
    }
    printf("%d",a[1].sum);
    return 0;
}

```

---

## 作者：poorpool (赞：3)

蒟蒻也能写出来的AC代码！对于从s到t的路径，一种自然的想法是把路径上的每一个点都+1，但这样复杂度会起飞。

我们便联想到**树上差分**。对于从s到t的路径，它的lca可求，那么就要

- c[s]++

- c[t]++

- c[lca]--（因为重复了）

- c[fa[lca][0]]--（因为lca的值也是要+1的）

如果不理解手画一棵树就行啦


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, k, hea[50005], cnt, c[50005], uu, vv, fa[50005][16], lca, depth[50005];
int sum[50005], maxn=0;
struct Edge{
    int too, nxt;
}edge[100005];
void add_edge(int fro, int too){
    edge[++cnt].nxt = hea[fro];
    edge[cnt].too = too;
    hea[fro] = cnt;
}
void build(int u){
    for(int i=hea[u]; i; i=edge[i].nxt){
        int t=edge[i].too;
        if(!depth[t]){
            depth[t] = depth[u] + 1;
            fa[t][0] = u;
            build(t);
        }
    }
}
int getLca(int u, int v){
    if(depth[u]<depth[v]){
        int temp=u;
        u = v;
        v = temp;
    }
    for(int i=15; i>=0; i--)
        if(depth[fa[u][i]]>=depth[v])
            u = fa[u][i];
    if(u==v)    return u;
    for(int i=15; i>=0; i--)
        if(fa[u][i]!=fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
void getSum(int u){
    sum[u] = c[u];
    for(int i=hea[u]; i; i=edge[i].nxt){
        int t=edge[i].too;
        if(t!=fa[u][0]){
            getSum(t);
            sum[u] += sum[t];
        }
    }
    maxn = max(maxn, sum[u]);
}
int main(){
    cin>>n>>k;
    for(int i=1; i<n; i++){
        scanf("%d %d", &uu, &vv);
        add_edge(uu, vv);
        add_edge(vv, uu);
    }
    depth[1] = 1;
    build(1);
    for(int i=1; i<=15; i++)
        for(int j=1; j<=n; j++)
            fa[j][i] = fa[fa[j][i-1]][i-1];
    for(int i=1; i<=k; i++){
        scanf("%d %d", &uu, &vv);
        c[uu]++;
        c[vv]++;
        lca = getLca(uu, vv);
        c[lca]--;
        if(fa[lca][0])c[fa[lca][0]]--;
    }
    getSum(1);
    cout<<maxn;
    return 0;
}
```

---

## 作者：Margoo√ (赞：3)

1、树上差分板子题（可以用来树上差分入门。
 
2、树上差分：通俗理解为把一条树链上的整体修改操作转化为这

条链两端端点的修改操作来优化时间。

3、分类：（1：点差分

		（2：边差分
         
4、实现：点差分每个点统计一个计数的数组 例如 cnt[x] 来记录

差分的权值。而以这个点为根的子树的所有节点（包括这个点）的

cnt[i]之和即为这个点的权值。

5、修改：修改一条树链时需要知道它的两个端点 和 两端点的

lca（最近公共祖先）,两端点cnt数组各加上要修改的权值 k(正负

都可以)，cnt[lca]减去要修改的权值k,对于lca的父亲节点

fa[lca]其对应的cnt[fa[lca]]也要减去k。

6、查询：无根树可以视作一颗有根树，以任一点为根去遍历整颗

树的时候，在回溯过程中去统计每个点子树的cnt和，并且顺便更

新ans的最大值。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;

struct Edge{int next,to;}ed[200100];
int n,m,head[100100],num_edge;
int fa[100100][22],dep[100100];
ll ans,cnt[100100];
bool vis[100100];

void Pre(int x,int dept)
	{
		vis[x]=1;
		dep[x]=dept;
		for(int i=1;i<=20;i++)
		{
			fa[x][i]=fa[fa[x][i-1]][i-1];
		}
		for(int i=head[x];i;i=ed[i].next)
		{
			int t=ed[i].to;
			if(vis[t]) continue;
			fa[t][0]=x;
			Pre(t,dept+1);
		}
	}
ll LCA(int x,int y)
	{
		if(dep[x]<dep[y])
		{
			swap(x,y);
		}
		for(int i=20;i>=0;i--)
		{
			if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
			if(x==y) return x;
		}
		for(int i=20;i>=0;i--)
		{
			if(fa[x][i]!=fa[y][i]) 
			{
				x=fa[x][i];
				y=fa[y][i];
			}
		}
		return fa[x][0];
	}
void DFS(int x)
	{
		vis[x]=1;
		for(int i=head[x];i;i=ed[i].next)
		{
			int t=ed[i].to;
			if(vis[t]) continue;
			DFS(t);
			cnt[x]+=cnt[t];
		}
		ans=max(cnt[x],ans);
	}
void Add(int f,int t)
	{
		ed[++num_edge].next=head[f];
		ed[num_edge].to=t;
		head[f]=num_edge;
	}
int main()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n-1;i++)
		{
			int f,t;
			scanf("%d%d",&f,&t);
			Add(f,t);
			Add(t,f);	
		}	
		Pre(1,0);
		for(int i=1;i<=m;i++)
		{
			int f,t;
			scanf("%d%d",&f,&t);
			cnt[f]++;
			cnt[t]++;
			int lca=LCA(f,t);
			cnt[lca]--;
			cnt[fa[lca][0]]--;
		}
		memset(vis,0,sizeof(vis));
		DFS(1);
		printf("%lld",ans);
		return 0;
	 } 
```


---

## 作者：Treaker (赞：2)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 树链剖分
这不就是个树剖裸题嘛。

他的每次运输路线就相当于给树上两个节点之间的路径加上1。

维护一个最大值。

那么我们打个标记维护一下就行了。 

最后查询时，直接输出root的最大值即可。

指针大法吼啊！！！

完整代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 50005;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n , m , cnt;
int size[N] , dep[N] , fa[N] , top[N] , hs[N] , dfn[N] , id[N];
struct Tree_Div
{
	struct Edge
	{
		int to; Edge *nxt;
		Edge(int to,Edge *nxt) : to(to) , nxt(nxt) {}
	}*head[N];
	inline void add(int u,int v) {head[u] = new Edge(v,head[u]);}
	void get_tree(int x)
	{
		size[x] = 1;
		for(Edge *i = head[x];i;i = i -> nxt)
		{
			int to = i -> to;
			if(dep[to]) continue;
			dep[to] = dep[x] + 1;
			fa[to] = x;
			get_tree(to);
			size[x] += size[to];
			if(size[to] > size[hs[x]]) hs[x] = to;
		}
	}
	void dfs(int x,int topfa)
	{
		top[x] = topfa;
		dfn[x] = ++cnt;
		id[cnt] = x;
		if(hs[x]) dfs(hs[x],topfa);
		for(Edge *i = head[x];i;i = i -> nxt)
		{
			int to = i -> to;
			if(to == hs[x] || to == fa[x]) continue;
			dfs(to,to);
		}
	}
	#define mid ((p -> l + p -> r) >> 1)
	struct node
	{
		node *ls , *rs;
		int l , r , tag , maxn;
		node(int l,int r) : l(l) , r(r) {ls = rs = NULL;tag = maxn = 0;}
		inline void up() {maxn = max(ls -> maxn,rs -> maxn);}
		inline void down() 
		{
			ls -> tag += tag; ls -> maxn += tag;
			rs -> tag += tag; rs -> maxn += tag;
			tag = 0;
		}
	}*root;
	void build(node *&p,int l,int r)
	{
		p = new node(l,r);
		if(l == r) return ;
		build(p -> ls,l,mid); build(p -> rs,mid+1,r);
	}
	void chenge(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y) return (void)(p -> tag ++ , p -> maxn ++);
		if(p -> tag) p -> down();
		if(x <= mid) chenge(p -> ls,x,y);
		if(y > mid) chenge(p -> rs,x,y);
		p -> up();
	}
	inline void sec_chenge(int x,int y)
	{
		if(dep[x] < dep[y]) swap(x,y);
		while(top[x] != top[y])
		{
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			chenge(root,dfn[top[x]],dfn[x]);
			x = fa[top[x]];
		}
		if(dep[x] < dep[y]) swap(x,y);
		chenge(root,dfn[y],dfn[x]);
	}
	inline void LOL()
	{
		n = read(); m = read();
		for(int i = 1 , u , v;i < n;i ++)
		{
			u = read(); v = read();
			add(u,v); add(v,u);
		} dep[1] = 1;
		get_tree(1); dfs(1,1);
		build(root,1,n);
		for(int i = 1 , u , v;i <= m;i ++)
		{
			u = read(); v = read();
			sec_chenge(u,v);
		}
		printf("%d\n",root->maxn);
	}
}CF;
int main(){CF.LOL();}
```


---

## 作者：梅川丘库 (赞：2)

非常开心，因为1A过了...之前做NOIP2015运输计划时，自己YY出了边上差分（运气....），然后就想来试一试点上差分，结果让我高兴...

如果不理解树上差分的话，可以讲个大概：对于此题来说，就是要求经过次数最多的点的次数，我们可以证明：对于一个点来说,如果要想经过它的话，必须符合某条路径的有且只有一个点在其子树内,所以对与某条路径的两个端点都在其子树内的情况，我们可以知道是经过该点的,但不经过该点的父节点.所以我们得令value[s[i]]++,value[t[i]]--;（因为端点表示s[i],t[i]的子树的末端（大概这意思，说不太清楚...2333理解一下...就是这两点代表这两点的子树走完了.所以得直接+1，因为后面没法更新了））value[lca(s[i],t[i])]--,value[fa[lca(s[i],t[i])]]--;关于为什么要使lca的父节点-1，我们可以考虑这样一棵树，1为根节点，2为1的唯一子节点，3，4为2的直接子节点，且路径为3->4.那么不-1的话，得出的答案就有value[1]=1,显然，这是不可能的,本来是该value[lca]-2的，但是lca存在此条路径上，所以我们把剩下的-1延后处理在lca的父节点上，对答案无影响...

现在考虑计算，如果我们按照移动的顺序来计算，显然退化为朴素算法.我们可以用树形DP保存状态,

value[i]表示包含i点的子树中只存在一条路径的一个端点以及以该店为lca的路径经过i点的次数，经典的DP方程：value[i]+=value[j],j为i的子节点，再求出最大值即可..















```cpp
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
char ch;
inline void read(int & x)
{
    x=0;
    ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
}
struct Edge
{
    int to,next;
}edge[100001];
int cnt,head[50001];
void Addedge(int u,int v)
{
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
int s[100001],t[100001];
int deep[50001];
int p[50001][20];
void dfs(int u,int fa)
{
    for(int i=head[u];i;i=edge[i].next)
    {
        Edge & e=edge[i];
        if(e.to==fa) continue;
        deep[e.to]=deep[u]+1;
        p[e.to][0]=u;
        dfs(e.to,u);
    }
}
int lca(int a,int b)
{
    int i,j;
    if(deep[a]<deep[b]) swap(a,b);
    for(i=0;(1<<i)<=deep[a];i++);
    i--;
    for(j=i;j>=0;j--)
    {
        if(deep[a]-(1<<j)>=deep[b])
        {
            a=p[a][j];
        }
    }
    if(a==b) return a;
    for(j=i;j>=0;j--)
    {
        if(p[a][j]!=p[b][j])
        {
            a=p[a][j];
            b=p[b][j];
        }
    }
    return p[a][0];
}
int size[100001];
int value[100001];
int index[100001];
int main()
{
    int n,k;
    read(n),read(k);
    int x,y;
    for(int i=1;i<=n-1;i++)
    {
        read(x);read(y);
        size[x]++;
        size[y]++;
        Addedge(x,y);
        Addedge(y,x);
    }
    for(int i=1;i<=k;i++)
    {
        read(s[i]);read(t[i]);
    }
    dfs(1,0);
    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(p[i][j-1]) p[i][j]=p[p[i][j-1]][j-1];
        }
    }
    int LCA;
    for(int i=1;i<=k;i++)
    {
        LCA=lca(s[i],t[i]);
        value[LCA]--;
        value[p[LCA][0]]--;
        value[s[i]]++;value[t[i]]++;
    }
    index[1]=size[1];
    queue<int> Q;
    for(int i=2;i<=n;i++)
    {
        if(size[i]==1)
        {
            Q.push(i);
            continue;
        }
        index[i]=size[i]-1;
    }
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        value[p[u][0]]+=value[u];
        index[p[u][0]]--;
        if(!index[p[u][0]]) Q.push(p[u][0]);
    }
    int maxn=-1;
    for(int i=1;i<=n;i++) maxn=max(maxn,value[i]); 
    printf("%d",maxn);
    return 0;
}
```

---

## 作者：fengtube (赞：2)

该题首先一看，属于在树上解决最大值问题。以及对于路径间的点权进行修改。

朴素的暴力去修改显然超时。那么，如何对于一条路径的点就行修改呢？我们首先将其简化为一条线，将一个序列的某个子区间进行修改，可以用前缀和维护差分实现o（1）修改，o（查询）。推广到树上即为树上差分。起点，终点++，lca，及fa[lca]++，然后递归对差分数组进行前缀和的求取就好了。代码如下。



    


```cpp
#include "iostream"
#include "cstdio"
#include "cmath"
#include "cctype"
#include "vector"
using namespace std;
void read(int &x)
{
    x = 0;
    char c = getchar();
    while(c<'0' || c>'9')
    {
        c = getchar();
    }
    while(isdigit(c))
    {
        x = (x<<3) + (x<<1) + c - '0';
        c = getchar();
    }
    return ;
}
const int maxn = 500005;
vector<int>s[maxn];
int anc[maxn][30] ,maxx ,cha[maxn] ,deep[maxn] ,a[maxn];
int n ,k ,son[maxn] ,tot;
void dfs(int x)
{
    for(int i=1; i<=19; i++)
        anc[x][i] = anc[anc[x][i-1]][i-1];
    for(int i=0; i<s[x].size(); i++)
        if(!deep[s[x][i]])
        {
            deep[s[x][i]] = deep[x]+1;
            anc[s[x][i]][0] = x;
            dfs(s[x][i]); 
        }
}
void lca(int x,int y)
{
    cha[x]++;
    cha[y]++;
    int fa;
    if(deep[x] != deep[y])
    {
        if(deep[x] < deep[y])
            swap(x ,y);
        for(int i=19; i>=0; i--)
            if(deep[anc[x][i]] >= deep[y])
                x = anc[x][i];
    }
    if(x == y)
        fa = x;
    else{
    for(int i=19; i>=0; i--)
        if(anc[x][i] != anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
        fa = anc[x][0];
    }
    cha[fa]--;
    cha[anc[fa][0]]--;
}
void solve(int x ,int y)
{
    for(int i=0; i<s[x].size(); i++)
        if(s[x][i]!=y)
        {
            solve(s[x][i] ,x);
            cha[x] += cha[s[x][i]];
        }
    maxx = max(maxx ,cha[x]);
}
int m;
int main()
{
    int x ,y;
    read(n);read(k);
            deep[1] = 1;
    for(int i=1; i<n; i++)
    {
        read(x),read(y);
        s[x].push_back(y);
        s[y].push_back(x);
    }
    dfs(1);
    for(int i=1; i<=k; i++)
    {
        read(x),read(y);
        lca(x ,y);
    }
    solve(1 ,0);
    printf("%d" ,maxx);
}
```

---

## 作者：wawcac (赞：2)

[广告（骗访问量）](http://www.cnblogs.com/wawcac-blog/p/6869850.html)

感谢@j\_william 指出我的错误，抱歉……改正了重发一个

我之前并没有听说过树上差分这么高级的东东，为了练手速花了40min敲了一个树剖套线段树(蒟蒻码力不足)，写好了线段树的一堆函数定义（maketree() pushdown() query() update()），剩着函数内部等待填充，感觉到一种绝望：还有那么多，要敲到啥时候啊。。。正在调整心态准备敲线段树时，突然想到，这题好像只是区间修改、单点查询？差分的树状数组！

于是内心一片愉悦啊，愉快地敲完短得多的树状数组，顺利1A！

正经的题解

增加一条x到y的路径，就是把x到y的所有点的点权加1，很容易想到这是树剖板题的第一个操作,又由于这题只用单点查询，于是再套单点修改、区间查询的树状数组即可


```cpp
#include<bits/stdc++.h>
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
#define lowbit(x) (x)&(-(x))
using namespace std;
int n,k;
struct Edge{
    int next,to;
}e[100010];
int cnt=1,head[50010];
void add_e(int u,int v)
{
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt++;
}
struct tree{
    int fa;
    vector<int> son;
    int dep;
    int num_to;
    int wson;
    int top;
    int new_id;
}t[50010];
bool vis[50010];
int dfs1(int u,int fa,int depth)
{
    vis[u]=1;
    t[u].fa=fa;
    t[u].dep=depth;
    t[u].num_to=1;
    for(int i=head[u],weightest=-1,w;i;i=e[i].next)
    {
        int v=e[i].to;
        if(vis[v]) continue;
        t[u].son.push_back(v);
        w=dfs1(v,u,depth+1);
        if(w>weightest)
        {
            t[u].wson=v;
            weightest=w;
        }
        t[u].num_to+=w;
    }
    return t[u].num_to;
}
int num_id=1;
void dfs2(int u,int top)
{
    t[u].top=top;
    t[u].new_id=num_id++;
    int sz=t[u].son.size();
    if(sz==0)
        return;
    dfs2(t[u].wson,top);
    for(int i=0;i<sz;i++)
    {
        int v=t[u].son[i];
        if(v==t[u].wson) continue;
        dfs2(v,v);
    }
}
int s[50010]={0};
void add(int node,int w)
{
    while(node<=n)//就是这里错了，我原来的题解没写'='，数据水没被卡，，，
    {
        s[node]+=w;
        node+=lowbit(node);
    }
}
int ask(int node)
{
    int ans=0;
    while(node)
    {
        ans+=s[node];
        node-=lowbit(node);
    }
    return ans;
}
void up(int x,int y)//////////////////////////////////////
{
    while(t[x].top!=t[y].top)//x向y上靠 即y.top 更高 
    {
        if(t[t[x].top].dep<t[t[y].top].dep) swap(x,y);
        add(t[x].new_id-1,-1);
        add(t[t[x].top].new_id,1);
        x=t[t[x].top].fa;
    }
    if(t[x].new_id>t[y].new_id) swap(x,y);
    add(t[x].new_id,1);
    add(t[y].new_id+1,-1);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1,x,y;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        add_e(x,y);
        add_e(y,x);
    }
    dfs1(1,1,1);
    dfs2(1,1);
    for(int i=0,x,y;i<k;i++)
    {
        scanf("%d%d",&x,&y);
        up(x,y);
    }
    int maxn=s[1];
    for(int i=2;i<=n+1;i++)//还有这里，我不知道当时咋想的，写了个i<=50001
    {
        maxn=max(maxn,ask(i));
    }
    printf("%d",maxn);
    return 0;
}
```

---

## 作者：zx2003 (赞：2)

树上差分即可。本蒟蒻不会什么a[lca(a,b)]-=2之类的，所以采用了树链剖分，以投射成连续区间

type
 bi=record

go,next:longint



```cpp
 end;
var
 e:array[0..100000] of bi;
 a,h,dad,dfn,id,size,ma,dep,top:array[0..50000] of longint;
 n,k,i,u,v,xb:longint;
procedure adde(u,v:longint);
begin
 inc(xb);
 e[xb].go:=v;
 e[xb].next:=h[u];
 h[u]:=xb
end;
procedure dfs1(x:longint);
var
 i,m,id:longint;
begin
 if x=6 then
 begin
  i:=i
 end;
 i:=h[x];
 m:=0;
 id:=0;
 while i>0 do
 begin
  if dep[e[i].go]=0 then
  begin
   dep[e[i].go]:=dep[x]+1;
   dad[e[i].go]:=x;
   dfs1(e[i].go);
   inc(size[x],size[e[i].go]);
   if size[e[i].go]>m then
   begin
    m:=size[e[i].go];
    id:=e[i].go
   end
  end;
  i:=e[i].next
 end;
 ma[x]:=id
end;
procedure dfs2(x:longint);
var
 i:longint;
begin
 inc(xb);
 dfn[xb]:=x;
 id[x]:=xb;
 if ma[x]=0 then exit;
 top[ma[x]]:=top[x];
 dfs2(ma[x]);
 i:=h[x];
 while i>0 do
 begin
  if (e[i].go<>ma[x])and(dep[x]=dep[e[i].go]-1) then
  begin
   top[e[i].go]:=e[i].go;
   dfs2(e[i].go)
  end;
  i:=e[i].next
 end
end;
procedure swap(var x,y:longint);
var
 t:longint;
begin
 t:=x;
 x:=y;
 y:=t
end;
procedure add(x,y:longint);
var
 u,v:longint;
begin
 u:=x;
 v:=y;
 while top[u]<>top[v] do
 begin
  if dep[top[u]]>dep[top[v]] then swap(u,v);//u is qian
  inc(a[id[top[v]]+1]);
  dec(a[id[v]+1]);
  v:=dad[top[v]]
 end;
 if dep[u]>dep[v] then swap(u,v);
 inc(a[id[u]]);
 dec(a[id[v]+1])
end;
begin
 filldword(size,sizeof(size) shr 2,1);
 readln(n,k);
 for i:=1 to n-1 do
 begin
  readln(u,v);
  adde(u,v);
  adde(v,u)
 end;
 dep[1]:=1;
 dad[1]:=1;
 dfs1(1);
 xb:=0;
 top[1]:=1;
 dfs2(1);
 for i:=1 to k do
 begin
  readln(u,v);
  add(u,v)
 end;
 u:=0;
 v:=0;
 for i:=1 to n do
 begin
  inc(u,a[i]);
  if u>v then v:=u
 end;
 writeln(v)
end.
```
树剖练手题，不知为何没什么人做

---

## 作者：Nero_Claudius (赞：2)

此类型题目有两种比较常见的做法：树链剖分和树上差分。

本题有多组修改一组询问，因此树上差分会比树链剖分优秀很多。

这里两种方法都进行介绍。

------------

树链剖分和树上差分的本质都是将一颗树转换为一个区间，然后进行操作。

也就是说，先将一颗树变成区间，然后套用线段树/树状数组和差分。

------------

树链剖分的具体流程不多加叙述，可以自己去翻它的模板题。

本题维护区间修改单点查询就OK了，最后输出答案的时候直接遍历所有节点取最大值。

1956ms,9805kb

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define qwq int
#define re register
using namespace std;
namespace Solve{
	#define N 200200
	qwq n,m;
	qwq cnt;
	qwq head[N];
	struct node{
		qwq to,next;
	}edge[N<<1];
	inline void add(qwq a,qwq b){
		edge[++cnt].to=b,edge[cnt].next=head[a],head[a]=cnt;
	}
	qwq dfn;
	qwq dep[N],fa[N],size[N],son[N],top[N],id[N];
	inline void dfs1(qwq now,qwq father,qwq deep){
		dep[now]=deep,fa[now]=father,size[now]=1;qwq max_son=-1;
		for(re qwq i=head[now];i;i=edge[i].next){
			qwq to=edge[i].to;
			if(to==father)continue;
			dfs1(to,now,deep+1);
			size[now]+=size[to];
			if(size[to]>max_son)max_son=size[to],son[now]=to;
		}
	}
	inline void dfs2(qwq now,qwq topf){
		id[now]=++dfn,top[now]=topf;
		if(!son[now])return;
		dfs2(son[now],topf);
		for(re qwq i=head[now];i;i=edge[i].next){
			qwq to=edge[i].to;
			if(to==son[now]||to==fa[now])continue;
			dfs2(to,to);
		}
	}
	struct tnode{
		qwq l,r,val,tag;
	}tree[N<<2];
	inline void pushup(qwq pos){
		tree[pos].val=tree[pos<<1].val+tree[pos<<1|1].val;
	}
	inline void pushdown(qwq pos){
		if(tree[pos].tag){
			tree[pos<<1].tag+=tree[pos].tag,tree[pos<<1|1].tag+=tree[pos].tag;
			tree[pos<<1].val+=tree[pos].tag*(tree[pos<<1].r-tree[pos<<1].l+1);
			tree[pos<<1|1].val+=tree[pos].tag*(tree[pos<<1|1].r-tree[pos<<1|1].l+1);
			tree[pos].tag=0;
		}
	}
	inline void build(qwq l,qwq r,qwq pos){
		tree[pos].l=l,tree[pos].r=r;
		if(l==r){
			tree[pos].val=0;
			return;
		}
		qwq mid=(l+r)>>1;
		build(l,mid,pos<<1),build(mid+1,r,pos<<1|1);
		pushup(pos);
	}
	inline void update(qwq l,qwq r,qwq v,qwq pos){
		if(l<=tree[pos].l&&tree[pos].r<=r){
			tree[pos].val+=v*(tree[pos].r-tree[pos].l+1);
			tree[pos].tag+=v;
			return;
		}
		pushdown(pos);
		qwq mid=(tree[pos].l+tree[pos].r)>>1;
		if(l<=mid)update(l,r,v,pos<<1);
		if(mid<r)update(l,r,v,pos<<1|1);
		pushup(pos);
	}
	inline qwq query(qwq l,qwq r,qwq pos){
		if(l<=tree[pos].l&&tree[pos].r<=r){
			return tree[pos].val;
		}
		pushdown(pos);
		qwq mid=(tree[pos].l+tree[pos].r)>>1,ans=0;
		if(l<=mid)ans=max(ans,query(l,r,pos<<1));
		if(mid<r)ans=max(ans,query(l,r,pos<<1|1));
		return ans;
	}
	inline qwq queryRange(qwq x,qwq y){
		qwq ans=0;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			ans=max(ans,query(id[top[x]],id[x],1));
			x=fa[top[x]];
		}
		if(dep[x]>dep[y])swap(x,y);
		ans=max(ans,query(id[x],id[y],1));
		return ans;
	}
	inline void updateRange(qwq x,qwq y,qwq v){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			update(id[top[x]],id[x],v,1);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y])swap(x,y);
		update(id[x],id[y],v,1);
	}
	inline void solve(){
		scanf("%d%d",&n,&m);
		for(re qwq i=1;i<=n-1;++i){
			qwq x,y;
			scanf("%d%d",&x,&y);
			add(x,y),add(y,x);
		}
		dfs1(1,1,1);
		dfs2(1,1);
		build(1,n,1);
		while(m--){
			qwq x,y;
			scanf("%d%d",&x,&y);
			updateRange(x,y,1);
		}
		qwq ans=0;
		for(re qwq i=1;i<=n;++i)ans=max(ans,query(id[i],id[i],1));
		cout<<ans;
	}
}
using namespace Solve;
qwq main(){
	solve();
}

```

------------

很明显，树链剖分码量比较高，在赛场上码力不足的选手容易陷入调试的巨坑，因此还是首推码量小并且（对于本题而言）速度快的树上差分。

需注意的是：树上差分适用于多组修改单组询问的题目，其他情况会T上天。

对于要更新的两个点而言，我们只要在他们上面各标记+1，然后在他们的lca和lca的父亲上各标记-1即可。

然后在询问的时候跑一下dfs统计一下就出答案了。

（lca用倍增，当然tarjan树剖都行，反正别裸的直接套上去）

懒得打代码了。~~光速逃~~

---

## 作者：斯德哥尔摩 (赞：2)

这题，首先应该看出这是一棵树。。。

其次，才是 LCA+树上差分 的算法。。。

树上差分的核心是：起点++，终点++，LCA（起点，终点）--，father[ LCA（起点，终点） ]--

LCA 建议用倍增，因为要用到 LCA 的 父亲（本人不会用 Tarjan 同时求 LCA 与 LCA 的父亲，吃枣药丸）。。。

如果上述算法还是看不懂，还有最后一招，上代码！！！

附注释的代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#define MAXN 100010//防止 MLE 
using namespace std;
int n,m,ans=0,c=1;
int head[MAXN<<1],f[MAXN][20],deep[MAXN],s1[MAXN],s2[MAXN];
struct node{
       int next,to;
}a[MAXN<<1];//前向星存图
inline int read(){//读优。。。
       int date=0,w=1;char c=0;
       while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
       while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
       return date*w;
}
void add(int x,int y){//在 x 与 y 之间加入一条双向边
     a[c].to=y;
     a[c].next=head[x];
     head[x]=c++;
     a[c].to=x;
     a[c].next=head[y];
     head[y]=c++;
}
void buildtree(int rt){//建树，顺便处理了 每个节点的深度 与 每个节点的父亲 。。。
     int will;
     for(int i=head[rt];i;i=a[i].next){
             will=a[i].to;//每条边的终点
             if(!deep[will]){
                             deep[will]=deep[rt]+1;
                             f[will][0]=rt;
                             buildtree(will);//遍历子节点（当初就是因为手残，将 will 敲成了 rt ，瞬间爆炸，于是调了半小时。。。）
                             }
             }
}
void step(){//跳跃步数
     for(int i=1;i<=19;i++)
     for(int j=1;j<=n;j++)
     f[j][i]=f[f[j][i-1]][i-1];//倍增思想应该都理解吧。。。
}
int LCA(int x,int y){//求LCA
    if(deep[x]<deep[y])swap(x,y);//总是将 x 设为深度较深的节点
    for(int i=19;i>=0;i--)//将 x 与 y 拉至同一深度
    if(deep[f[x][i]]>=deep[y])
    x=f[x][i];
    if(x==y)return x;
    for(int i=19;i>=0;i--)//寻找深度比 LCA大1 的节点
    if(f[x][i]!=f[y][i]){
                         x=f[x][i];
                         y=f[y][i];
                         }
    return f[x][0];//返回 深度比 LCA大1 的节点 的上一层，即LCA
}
void work(int x,int y){//差分
     int fa=LCA(x,y);
     s1[x]++;s1[y]++;s1[fa]--;
     if(f[fa][0]!=0)s1[f[fa][0]]--;
}
void getsum(int now,int rt){//求出每个节点的压力。。。
     int t;
     s2[now]=s1[now];
     for(int i=head[now];i;i=a[i].next){
             t=a[i].to;
             if(t!=rt){
                       getsum(t,now);
                       s2[now]+=s2[t];
                       }
             }
     ans=max(ans,s2[now]);//比较大小并更新。。。
}
int main(){//主函数 So easy!
    int x,y;
    n=read();m=read();
    for(int i=1;i<n;i++){
            x=read();y=read();
            add(x,y);//建边
            s1[i]=deep[i]=0;//表示不想用 memset,已经被坑过无数次。。。
            }
    deep[1]=1;
    buildtree(1);
    step();
    while(m--){
               x=read();y=read();
               work(x,y);
               }
    getsum(1,0);
    printf("%d\n",ans);//输出答案。。。
    return 0;//结束，撒花~~~
}

```

---

## 作者：ComplexPug (赞：1)


这个题哪里有那么费脑筋

我们可以树链剖分嘛~~LCT昨天学的时候睡着了，不是太会~~

两遍dfs+一个5行的BIT

其实树链剖分学好了对倍增和LCT理解上都有好处

一条路径上的修改

由于一条剖出来的链是连续的，我们要选择数据结构维护

不过这里不用维护太多东西，只是区间+1

我们可以选择常数小，好写的树状数组(从50行的线段树变成5行的
BIT)

而且使得$O(nlog_{2})$的算法跑的并不慢

具体就是用差分思想，修改区间[L,R]时

$[1,R] +1 $ $[1,L-1] -1$达到修改的目的

最后查询时

直接每次查询[1,i]的值就可得到i的最终压力值

```cpp
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int maxn=2e5+7;
int read() {
    int x=0,f=1;char s=getchar();
    for(;s>'9'||s<'0';s=getchar()) if(s=='-') f=-1;
    for(;s>='0'&&s<='9';s=getchar()) x=x*10+s-'0';
    return x*f;
}
vector<int> G[maxn];
int n,m,top[maxn],f[maxn],siz[maxn],idx[maxn],cnt,son[maxn],dep[maxn];
void dfs1(int u,int fa) {
    f[u]=fa;
    siz[u]=1;
    dep[u]=dep[fa]+1;
    for(vector<int>::iterator it=G[u].begin();it!=G[u].end();++it) {
        if(*it==fa) continue;
        dfs1(*it,u);
        siz[u]+=siz[*it];
        if(siz[son[u]] < siz[*it]) son[u]=*it;
    }
}
void dfs2(int u,int topf) {
    idx[u]=++cnt;
    top[u]=topf;
    if(!son[u]) return;
    dfs2(son[u],topf);
    for(std::vector<int>::iterator it=G[u].begin();it!=G[u].end();++it)
        if(!idx[*it]) dfs2(*it,*it);
}
namespace BIT {
    int sum[maxn];
    int lowbit(int x) {return x&-x;}
    void add(int x,int k) {for(int i=x;i<=n;i+=lowbit(i)) sum[i]+=k;}
    int query(int x) {int ans=0;for(int i=x;i>=1;i-=lowbit(i)) ans+=sum[i];return ans;}
    void modify(int x,int y) {if(x!=n)add(y+1,-1);add(x,1);}
}
void change(int x,int y) {
    while(top[x]!=top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        BIT::modify(idx[top[x]],idx[x]);
        x=f[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    BIT::modify(idx[x],idx[y]);
}
int main() {
    n=read(),m=read();
    FOR(i,2,n) {
        int x=read(),y=read();
        G[x].push_back(y),G[y].push_back(x);
    }
    dfs1(1,0);dfs2(1,1);
    FOR(i,1,m) change(read(),read());
    int ans=0;
    FOR(i,1,n) ans=max(ans,BIT::query(i));
    cout<<ans<<"\n";
    return 0;
}
```


---

## 作者：yizimi远欣 (赞：1)

### 题目描述

FJ给他的牛棚的N(2≤N≤50,000)个隔间之间安装了N-1根管道，隔间编号从1到N。所有隔间都被管道连通了。

FJ有K(1≤K≤100,000)条运输牛奶的路线，第i条路线从隔间si运输到隔间ti。一条运输路线会给它的两个端点处的隔间以及中间途径的所有隔间带来一个单位的运输压力，你需要计算压力最大的隔间的压力是多少。

### 主要思路 ： LCA + 树上差分

如果您还不会差分，那就去这个[神奇的网站](www.baidu.com)去找一找差分吧（逃

这是道树上差分裸题。

论如何树上做差分，，，

还记得序列上差分是怎么做的吗$QAQ$？

假如我们要把一段区间的数据+1，我们根据差的性质把左端点维护差分的数组相应位置+1，右端点-1。

树上差分也类似。我们只需要把两个端点-1，两个端点的lca -2,（为啥-2，emmm，因为有两个端点要+1啊）。

但是这样就会发现lca处求出的并没有+1，我们可以使得lca处-1就好，保证之后的点加的时候会有+1的效果，我们在lca的父节点处也-1，保证lca处是有+1效果的。

所以就这么搞啦！

### code ：

P.S. ： （树剖LCA打习惯了QAQ

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
using namespace std;
#define go(i, j, n, k) for(int i = j; i <= n; i += k)
#define fo(i, j, n, k) for(int i = j; i >= n; i -= k)
#define rep(i, x) for(int i = h[x]; i; i = e[i].nxt)
#define mn 100010
#define inf 1 << 30
#define ll long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x * f;
}
struct edge{
	int v, nxt;
}e[mn << 1];
int h[mn], p;
inline void add(int a, int b) {
	e[++p].nxt = h[a], h[a] = p, e[p].v = b;
}
int dep[mn], sze[mn], fa[mn], son[mn], top[mn], cnt, n, m, _minus[mn], ans = -1;
void dfs1(int x, int f, int deep) {
	dep[x] = deep;
	sze[x] = 1;
	fa[x] = f;
	int maxson = -1;
	rep(i, x) {
		int v = e[i].v;
		if(v == f) continue;
		dfs1(v, x, deep + 1);
		sze[x] += sze[v];
		if(sze[v] > maxson)
			maxson = sze[v], son[x] = v;
	}
}
void dfs2(int x, int topf) {
	top[x] = topf;
	if(!son[x]) return;
	dfs2(son[x], topf);
	rep(i, x) {
		int v = e[i].v;
		if(v == fa[x] || v == son[x]) continue;
		dfs2(v, v);
	}
}
inline int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return dep[x] > dep[y] ? y : x;
}
inline void dfs(int x, int f) {
	rep(i, x) {
		int v = e[i].v;
		if(v == f) continue;
		dfs(v, x);
		_minus[x] += _minus[v];
	}
	ans = max(ans, _minus[x]);
}
int main() {
	n = read(), m = read();
	go(i, 1, n - 1, 1) {
		int a = read(), b = read();
		add(a, b), add(b, a);
	}
	dfs1(1, 0, 1); // 树剖预处理的哦QAQ
	dfs2(1, 1);    // 树剖预处理的哦QAQ
	go(i, 1, m, 1) {
		int a = read(), b = read(), lca = LCA(a, b);
		_minus[a]++, _minus[b]++, _minus[lca]--, _minus[fa[lca]]--; 
        // 不要问我的数组变量名之前加‘_’，你可以试一下不加 
	}
	dfs(1, 0);     // 差分完了就做个树上前缀和就好辣！~\(≧▽≦)/~
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：eros1on (赞：0)

[博客食用更佳](https://tle666.github.io/2019/02/23/[USACO15DEC]%20%E6%9C%80%E5%A4%A7%E6%B5%81/)

# **Description**

给你一颗$n$个结点的树。

有$k$个操作，每个操作有两个数$u$和$v$，使$u$到$v$路径上的所有点权都加一。

最后输出最大的点权值。

对于$100$%的的数据，满足$2 \leq n \leq 50000,\ 1 \leq k \leq 100000$

[题目链接戳这里](https://www.luogu.org/problemnew/show/P3128)

# **Solution**

树链剖分模板题！~~[没学过的戳这里](https://tle666.github.io/2019/02/02/%E6%A0%91%E9%93%BE%E5%89%96%E5%88%86%E8%AF%A6%E8%A7%A3/)~~

对于每次操作$u$，$v$，我们只需要执行一次树链剖分里最基本的修改操作：路径修改即可。

最后你再用基本操作$query$求一次区间点权最大值就A了啊！

~~详见代码~~

# **Code**

```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#define MAXN 100100
int n, k, tot, wson[MAXN], dep[MAXN], fa[MAXN], dfn[MAXN], pre[MAXN], size[MAXN], top[MAXN];
struct edge { // 存图
    int v;
    edge *next;
} epool[MAXN << 1], *h[MAXN], *ecnt = epool;
struct node { // 存树
    int left, right, Max, tag;
    node *ls, *rs;
    inline void seta(int x) { tag += x, Max += x;}
    inline void upd() { Max = max(ls->Max, rs->Max);}
    inline void push() {
        if(tag) {
            if(ls) ls->seta(tag);
            if(rs) rs->seta(tag);
            tag = 0;
        }
    }
} pool[MAXN << 3], *root, *cnt = pool;
inline void addedge(int u, int v) { // 加边
    edge *p = ++ecnt, *q = ++ecnt;
    p->v = v, p->next = h[u], h[u] = p;
    q->v = u, q->next = h[v], h[v] = q;
}
inline void dfs1(int u, int f) {
    int v; size[u] = 1;
    for(edge *p = h[u]; p; p = p->next)
        if((v = p->v) != f) {
            fa[v] = u,
            dep[v] = dep[u] + 1;
            dfs1(v, u);
            size[u] += size[v];
            if(size[wson[u]] < size[v]) wson[u] = v;
        }
}
inline void dfs2(int u, int tp) {
    int v; top[u] = tp;
    dfn[u] = ++tot, pre[tot] = u;
    if(wson[u]) dfs2(wson[u], tp);
    for(edge *p = h[u]; p; p = p->next)
        if((v = p->v) != fa[u] && v != wson[u])
            dfs2(v, v);
}
inline void build(node *r, int left, int right) {
    r->left = left, r->right = right;
    if(left == right) {
        r->Max = 0;
        return ;
    }
    int mid = (left + right) >> 1;
    node *ls = ++cnt, *rs = ++cnt;
    r->ls = ls, r->rs = rs;
    build(ls, left, mid), build(rs, mid + 1, right);
    r->upd();
}
inline void change(node *r, int left, int right) {
    if(r->left == left && r->right == right) {
        r->seta(1); return ;
    } r->push();
    if(r->ls->right >= right) change(r->ls, left, right);
    else if(r->rs->left <= left) change(r->rs, left, right);
    else change(r->ls, left, r->ls->right),
         change(r->rs, r->rs->left, right);
    r->upd();
}
inline int query(node *r, int left, int right) { // 区间求 max
    r->push();
    if(r->left == left && r->right == right) return r->Max;
    if(r->ls->right >= right) return query(r->ls, left, right);
    else if(r->rs->left <= left) return query(r->rs, left, right);
    else return max(query(r->ls, left, r->ls->right),
                    query(r->rs, r->rs->left, right));
}
inline void Qchange(int u, int v) { // 路径点权加一
    int left, right;
    while(top[u] != top[v]) {
        if(dep[top[u]] > dep[top[v]]) swap(u, v);
        change(root, dfn[top[v]], dfn[v]);
        v = fa[top[v]];
    } left = dfn[u], right = dfn[v];
    if(left > right) swap(left, right);
    change(root, left, right);
}
int main() {
    int u, v;
    scanf("%d%d", &n, &k);
    for(int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        addedge(u, v);
    } dep[1] = 1;
    dfs1(1, 0), dfs2(1, 1);
    build(root = cnt, 1, n);
    while(k--) {
        scanf("%d%d", &u, &v);
        Qchange(u, v);
    } printf("%d\n", query(root, 1, n)); // 最后输出最大值
    return 0;
}
```



---

