# Legacy

## 题目描述

Rick and his co-workers have made a new radioactive formula and a lot of bad guys are after them. So Rick wants to give his legacy to Morty before bad guys catch them.

There are $ n $ planets in their universe numbered from $ 1 $ to $ n $ . Rick is in planet number $ s $ (the earth) and he doesn't know where Morty is. As we all know, Rick owns a portal gun. With this gun he can open one-way portal from a planet he is in to any other planet (including that planet). But there are limits on this gun because he's still using its free trial.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786B/9ce8ffb5132d0e638eaee42e56a9bbc8517d720d.png)By default he can not open any portal by this gun. There are $ q $ plans in the website that sells these guns. Every time you purchase a plan you can only use it once but you can purchase it again if you want to use it more.

Plans on the website have three types:

1. With a plan of this type you can open a portal from planet $ v $ to planet $ u $ .
2. With a plan of this type you can open a portal from planet $ v $ to any planet with index in range $ [l,r] $ .
3. With a plan of this type you can open a portal from any planet with index in range $ [l,r] $ to planet $ v $ .

Rick doesn't known where Morty is, but Unity is going to inform him and he wants to be prepared for when he finds and start his journey immediately. So for each planet (including earth itself) he wants to know the minimum amount of money he needs to get from earth to that planet.

## 说明/提示

In the first sample testcase, Rick can purchase $ 4 $ th plan once and then $ 2 $ nd plan in order to get to get to planet number $ 2 $ .

## 样例 #1

### 输入

```
3 5 1
2 3 2 3 17
2 3 2 2 16
2 2 2 3 3
3 3 1 1 12
1 3 3 17
```

### 输出

```
0 28 12 
```

## 样例 #2

### 输入

```
4 3 1
3 4 1 3 12
2 2 3 4 10
1 2 4 16
```

### 输出

```
0 -1 -1 12 
```

# 题解

## 作者：tzc_wk (赞：113)

线段树优化建图板子题。。。。。。

暴力建边 $\mathcal O(n^2)$ 肯定会 TLE

但仔细分析可以发现，题面中有一个我们非常熟悉的字眼“**区间**”，这启示我们，可不可以以此作为解题的突破口呢？

答案是肯定的。想到区间我们可以联想到各种我们很熟悉的 trick，如前缀和、差分、线段树等。

但对于此题而言前缀和、差分似乎都不太行，于是我们考虑线段树，利用“每一个区间都可以表示为线段树上 $\log n$ 个区间“来减少边的个数。

我们就拿 $2$ 操作来举例吧。现在假设假如有一个点要与 $[1,3]$ 的点连边权为 $w$ 的边，那么我们建出线段树：

![](https://cdn.luogu.com.cn/upload/image_hosting/uxcyzg3d.png)
将 $[1,3]$ 拆成 $[1,2]$ 与 $[3,3]$ 然后分别连边，边权为 $w$（图中橙色的边）：

![](https://cdn.luogu.com.cn/upload/image_hosting/sy08ow6r.png)
但是仅仅只连这两条边是远远不够的，因为你只将这个点与**一个区间**表示的点连了边，并没有将其连到**具体的单点**上。

因此我们还从每个区间向其子区间连边，由于你向下走，从一个大区间对应到一个小区间**没有代价**，因此这些边的边权为 $0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/p9kcyjv8.png)

操作 $3$ 也同理，只不过把之前连的所有边都反向。

![](https://cdn.luogu.com.cn/upload/image_hosting/plxxps82.png)

---

以上是操作 $2$ 与操作 $3$ 分开来考虑的情形，那么操作 $2$ 与操作 $3$ 相结合该怎么办呢？

显然你不能把它们揉在一棵线段树上，因为你线段树上每条边向上向下边权都为 $0$，故从原点到每个点的最短路也为 $0$，这……还玩个什么啊。。。。。。

因此可以想到建两棵线段树，第一棵只连自上而下的边，第二棵只连自下而上的边：

![](https://cdn.luogu.com.cn/upload/image_hosting/7s51hcxi.png)

对于 $2$ 操作，你就从第二棵线段树的叶子节点向第一棵线段树中的对应区间连边（下图中橙色的边）。

对于 $3$ 操作，你就从第二棵线段树中的对应区间向第一棵线段树中的叶子节点连边（下图中粉色的边）。

![](https://cdn.luogu.com.cn/upload/image_hosting/v62b75pr.png)

还有一点，就是两棵线段树的叶子节点实际上是同一个点，因此要在它们互相之间连边权为 $0$ 的边（下图中黄色的边）

![](https://cdn.luogu.com.cn/upload/image_hosting/nciq2uft.png)

---

图建好了，剩下来就是板子：

```cpp
const int D=5e5;
int n=read(),m=read(),st=read(),dist[1000005],leaf[100005];
vector<pii> g[1000005];
struct node{
	int l,r;
} s[100005<<2];
inline void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;
	if(l==r){
		leaf[l]=k;
		return;
	}
	int mid=(l+r)>>1;
	g[k].push_back(pii(k<<1,0));
	g[k].push_back(pii(k<<1|1,0));
	g[(k<<1)+D].push_back(pii(k+D,0));
	g[(k<<1|1)+D].push_back(pii(k+D,0));
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
inline void connect(int k,int l,int r,int v,int w,int tp){
	if(l<=s[k].l&&s[k].r<=r){
		if(tp) g[k+D].push_back(pii(v,w));
		else g[v].push_back(pii(k,w));
		return;
	}
	int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) connect(k<<1,l,r,v,w,tp);
	else if(l>mid) connect(k<<1|1,l,r,v,w,tp);
	else connect(k<<1,l,mid,v,w,tp),connect(k<<1|1,mid+1,r,v,w,tp);
}
signed main(){
	build(1,1,n);
	fz(i,1,m){
		int opt=read();
		if(opt==1){
			int v=read(),u=read(),w=read();
			g[leaf[v]].push_back(pii(leaf[u],w));
		}
		else{
			int v=read(),l=read(),r=read(),w=read();
			connect(1,l,r,leaf[v],w,opt%2);
		}
	}
	fz(i,1,n) g[leaf[i]].push_back(pii(leaf[i]+D,0)),g[leaf[i]+D].push_back(pii(leaf[i],0));
	priority_queue<pii,vector<pii>,greater<pii> > q;
	fillbig(dist);dist[leaf[st]+D]=0;q.push(pii(0,leaf[st]+D));
	while(!q.empty()){
		pii p=q.top();q.pop();
		int x=p.se,sum=p.fi;
//		cout<<x<<endl;
		if(dist[x]<sum) continue;
		foreach(it,g[x]){
			int y=it->fi,z=it->se;
			if(dist[y]>sum+z){
				dist[y]=sum+z;
				q.push(pii(dist[y],y));
			}
		}
	}
	fz(i,1,n){
		if(dist[leaf[i]]==0x3f3f3f3f3f3f3f3fll) printf("-1 ");
		else printf("%lld ",dist[leaf[i]]);
	}
	return 0;
}
```

---

## 作者：maoyiting (赞：80)

宣传一波 [blog](https://www.cnblogs.com/maoyiting/)~

### 题目大意

有 $n$ 个点、$q$ 次操作。每一种操作为以下三种类型中的一种：

- 操作一：连一条 $u\to v$ 的有向边，权值为 $w$。

- 操作二：对于所有 $i\in [l,r]$ 连一条 $u\to i$ 的有向边，权值为 $w$。

- 操作三：对于所有 $i\in [l,r]$ 连一条 $i\to u$ 的有向边，权值为 $w$。

求从点 $s$ 到其他点的最短路。$1\leq n,q\leq 10^5,1\leq w\leq 10^9$。

### Solution

考虑暴力建图。显然不能通过此题。

这时候就需要用线段树优化建图了。线段树优化建图就是利用线段树，减少连边数量，从而降低复杂度。

#### 线段树优化建图

先建一棵线段树。假如现在我们要从 $8$ 号点向区间 $[3,7]$ 的所有点连一条权值为 $w$ 有向边。

![https://img2020.cnblogs.com/blog/1859218/202010/1859218-20201003152331500-2047892066.png](https://i.loli.net/2020/10/03/5kstpAXrwGiTdBc.png)

那么怎么连边？把区间 $[3,7]$ 拆成 $[3,4]$、$[5,6]$ 和 $[7,7]$ 然后分别连边。

就这样：（如下图所示。其中黑色普通边的边权为 $0$，粉色边的边权为 $w$。）

![https://img2020.cnblogs.com/blog/1859218/202010/1859218-20201003152713737-813466449.png](https://i.loli.net/2020/10/03/A6u3Bw5vSJXmRqF.png)

原来我们要连 $5$ 条边，现在只需要连 $3$ 条边，也就是 $\lceil \log_2 7\rceil$ 条边。

于是 $O(n)$ 的边数就优化成了 $O(\log n)$。

那么操作三用和操作二类似的方法连边。从区间 $[3,7]$ 的所有点向 $8$ 号点连一条权值为 $w$ 有向边：（其实就是边反了个方向）

![https://img2020.cnblogs.com/blog/1859218/202010/1859218-20201003155545073-505477788.png](https://i.loli.net/2020/10/03/C59jaEubSL3Rfd4.png)

以上是操作二与操作三分开来考虑的情形，那么操作二与操作三相结合该怎么办呢？

考虑建两棵线段树，第一棵只连自上而下的边，第二棵只连自下而上的边。方便起见，我们把第一棵树称作“出树”，第二棵树称作“入树”。

初始时自上而下或自下而上地在每个节点与它的父亲之间连边。由于两棵线段树的叶子节点实际上是同一个点，因此要在它们互相之间连边权为 $0$ 的边。初始时是这样的：

![https://img2020.cnblogs.com/blog/1859218/202010/1859218-20201003175442575-1059055629.png](https://i.loli.net/2020/10/03/MsNixweUIfAVojp.png)

建树部分的代码：（代码中的 $K$ 是一个常数，根据数据范围而定。建出树和入树也可以分别用两个函数实现，这样就用不到 $K$ 了。）

```cpp
void build(int p,int l,int r){
      if(l==r){a[l]=p;return ;}    //a: 记录叶子节点的编号 
      add(p,p<<1,0),add(p,p<<1|1,0);    //出树（从 p 向 p 的左右儿子连一条边权为 0 的边） 
      add((p<<1)+K,p+K,0),add((p<<1|1)+K,p+K,0);    //入树（从 p 的左右儿子向 p 连一条边权为 0 的边） 
      build(p<<1,l,mid);
      build(p<<1|1,mid+1,r); 
}
//主函数中： 
for(int i=1;i<=n;i++)
      add(a[i],a[i]+K,0),add(a[i]+K,a[i],0);     //两棵线段树的叶子节点之间连边 
```

接下来：

- 对于操作一，就从入树的叶子节点向出树的叶子节点连边。

- 对于操作二，就从入树的叶子节点向出树中的对应区间连边。

- 对于操作三，就从入树中的对应区间向出树中的叶子节点连边。

举个栗子。比如现在我们要从 $8$ 号点向区间 $[3,7]$ 的所有点连一条权值为 $w$ 有向边。那么就如图所示连边：（为了让图更清楚，图中把入树和出树叶子节点之间相连的边省略了。）

![https://img2020.cnblogs.com/blog/1859218/202010/1859218-20201003180159361-1510386633.png](https://i.loli.net/2020/10/03/bnOMekypKX4aEQs.png)

连边部分的代码：

```cpp
void modify(int p,int l,int r,int lx,int rx,int v,int w){
	if(l>=lx&&r<=rx){	//如果当前区间被涵盖
		if(opt==2) add(v+K,p,w);	//对于操作二，就从入树的叶子节点向出树中的对应区间连边。
		else add(p+K,v,w);	//对于操作三，就从入树中的对应区间向出树中的叶子节点连边。
		return;
	}
	int mid=(l+r)/2;
	if(lx<=mid) modify(p<<1,l,mid,lx,rx,v,w);
	if(rx>mid) modify(p<<1|1,mid+1,r,lx,rx,v,w);
} 
//主函数中：
for(int i=1;i<=m;i++){
	scanf("%lld",&opt);
	if(opt==1) scanf("%lld%lld%lld",&x,&y,&z),add(a[x]+K,a[y],z);	//对于操作一，就从入树的叶子节点向出树的叶子节点连边。
	else{
		scanf("%lld%lld%lld%lld",&x,&l,&r,&w);
		modify(1,1,n,l,r,a[x],w);
	}
}
```

[完整代码](https://www.cnblogs.com/maoyiting/p/13764109.html)

---

## 作者：张鑫杰 (赞：40)

**题意分析**

这一题最主要是有三种操作：1.进行单点与单点连有向边 2.进行单点与区间连有向边 3.进行区间与单点连有向边。然后求最短路。

这一道题，最大的难点不在最短路（直接套Dij模板），而在于如何连边。如果按照题意模拟，一个点到区间中的一个点进行连接，其复杂度在最坏情况下会达到O(n*n)（即每一个点向整个区间连边），任何一个有常识的人都能看出这样一定会TLE的。

对于我们来说，最大的难点就是要解决单点与区间之间的操作。一看到区间，我们首先想到的就是前缀和、差分、ST表、树状数组、线段树。其实，这一题本质上就是一道特殊的线段树题。

那么怎么把一个线段树放到图里面呢？这里我们发现，如果只建立一个线段树是很难实现的，那么我们一不做二不休，就建立两个线段树。

```cpp
int n,q,s,cnt,treeOut[MAXN<<2],treeIn[MAXN<<2];
```

我们用treeOut专门处理由线段树向外连边，其效果如图所示：
![treeOut]( https://cdn.luogu.com.cn/upload/pic/36910.png)

有图可见，我们在线段树内建立了多条有向虚边。且treeIn和treeOut的线段树虚边的方向是相反的，如图则是treeIn：
![treeIn](https://cdn.luogu.com.cn/upload/pic/36911.png)

那么为什么要这样建立虚边，这里就用一张图来演示一下：
![ErrTreeIn](https://cdn.luogu.com.cn/upload/pic/36912.png)
由图可知，错误的连边会导致访问的区间出错。比如在这张错误的图中，一个只能访问[mid+1,right]的连边却访问到了[left,right]。

***代码***

```cpp
static vector<pair<int,int>> edge[MAXN*10];
```
我们使用vector建图，相比于链表来说会方便一些（2s,STL不怂）。
```cpp
inline void build(int k,int l,int r){
    if(l==r){
        treeOut[k]=l;
        treeIn[k]=l;
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    treeOut[k]=++cnt;
    treeIn[k]=++cnt;
    edge[treeOut[k<<1]].push_back make(treeOut[k],0);
    edge[treeOut[k<<1|1]].push_back make(treeOut[k],0);
    edge[treeIn[k]].push_back make(treeIn[k<<1],0);
    edge[treeIn[k]].push_back make(treeIn[k<<1|1],0);
}
inline void updateIn(int k,int l,int r,int L,int R,int from,int cost){
    if(L<=l&&r<=R){
        edge[from].push_back(make(treeIn[k],cost));
        return ;
    }
    int mid=(l+r)>>1;
    if(L<=mid){
        updateIn(k<<1,l,mid,L,R,from,cost);
    }
    if(mid<R){
        updateIn(k<<1|1,mid+1,r,L,R,from,cost);
    }
}
inline void updateOut(int k,int l,int r,int L,int R,int from,int cost){
    if(L<=l&&r<=R){
        edge[treeOut[k]].push_back(make(from,cost));
        return ;
    }
    int mid=(l+r)>>1;
    if(L<=mid){
        updateOut(k<<1,l,mid,L,R,from,cost);
    }
    if(mid<R){
        updateOut(k<<1|1,mid+1,r,L,R,from,cost);
    }
}
```
常规的建树操作，最大的区别是要在建树的时候还要进行建图操作。树的每一个节点储存着该区间在图中的编号。需要注意的是，当该区间就是一个点时,树中储存的就是改点的便后，即：
```cpp
if(l==r){
        treeOut[k]=l;
        treeIn[k]=l;
        return;
}
```
在这道题中，update的作用不在于修改树中的值，而是在于建图，这是他与一般线段树的区别。
以下是全部代码：
```cpp
#include<bits/stdc++.h>
#define ini(x,y) memset(x,y,sizeof(x))
#define all(x) x.begin(),x.end()
#define F(x,y,z) for(int x=y;x<=z;++x)
#define D(x,y,z) for(int x=y;x>=z;--x)
#define cint const int&
using namespace std;
/*请以C++11提交,Develop By ZhangXinjie（江南柚子）*/
const int MAXN=static_cast<int>(1e5)+100;
const long long INF=0x3f3f3f3f3f3f3f3f;
const int oo=0x3f3f3f3f;
#define int long long
inline int read(){
    int x = 0, y = 1, c = getchar();
    while (c>'9' || c<'0') { if (c == '-')y = -1; c = getchar(); }
    while (c >= '0'&&c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * y;
}
#define make(x,y) (make_pair(x,y))
#define to first
#define v second
static vector<pair<int,int>> edge[MAXN*10];
static int n,q,s,cnt,treeOut[MAXN<<2],treeIn[MAXN<<2];
inline void build(int k,int l,int r){
    if(l==r){
        treeOut[k]=l;
        treeIn[k]=l;
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    treeOut[k]=++cnt;
    treeIn[k]=++cnt;
    edge[treeOut[k<<1]].push_back make(treeOut[k],0);
    edge[treeOut[k<<1|1]].push_back make(treeOut[k],0);
    edge[treeIn[k]].push_back make(treeIn[k<<1],0);
    edge[treeIn[k]].push_back make(treeIn[k<<1|1],0);
}
inline void updateIn(int k,int l,int r,int L,int R,int from,int cost){
    if(L<=l&&r<=R){
        edge[from].push_back(make(treeIn[k],cost));
        return ;
    }
    int mid=(l+r)>>1;
    if(L<=mid){
        updateIn(k<<1,l,mid,L,R,from,cost);
    }
    if(mid<R){
        updateIn(k<<1|1,mid+1,r,L,R,from,cost);
    }
}
inline void updateOut(int k,int l,int r,int L,int R,int from,int cost){
    if(L<=l&&r<=R){
        edge[treeOut[k]].push_back(make(from,cost));
        return ;
    }
    int mid=(l+r)>>1;
    if(L<=mid){
        updateOut(k<<1,l,mid,L,R,from,cost);
    }
    if(mid<R){
        updateOut(k<<1|1,mid+1,r,L,R,from,cost);
    }
}
struct heapnode{
    int pos,dis;
    bool operator<(heapnode right)const{
        return dis>right.dis;
    }
};

static int dis[MAXN*10];
static priority_queue<heapnode>heap;
inline void dij(){
    ini(dis,0x3f);
    dis[s]=0;
    heapnode tmp;
    tmp.dis=0;
    tmp.pos=s;
    heap.push(tmp);
    while(!heap.empty()){
        heapnode now=heap.top();
        heap.pop();
        if(dis[now.pos]!=now.dis){
            continue;
        }
        for(auto &i:edge[now.pos]){
            if(i.to==0){
                continue;
            }
            if(i.v+now.dis<dis[i.to]){
                dis[i.to]=i.v+now.dis;
                tmp.pos=i.to;
                tmp.dis=dis[i.to];
                heap.push(tmp);
            }
        }
    }
}
signed main(){
    n=read();
    q=read();
    s=read();
    cnt=n;
    build(1,1,n);
    F(i,1,q){
        int com=read();
        if(com==1){
            int from=read(),to=read(),v=read();
            edge[from].push_back(make(to,v));
        }else{
            if(com==2){
                int from=read(),l=read(),r=read(),v=read();
                updateIn(1,1,n,l,r,from,v);
            }else{
                int from=read(),l=read(),r=read(),v=read();
                updateOut(1,1,n,l,r,from,v);
            }
        }
    }
    dij();
    F(i,1,n){
        printf("%lld ",(dis[i]==INF)?-1:dis[i]);
    }
    return 0;
}

```
至于为什么使用dij算法而不用SPFA，因为
```
1<=w<=10^9
```
以及NOI2018D1T1的血的教训。

还有，记得使用long long

---

## 作者：Nekroz (赞：15)

具体参考我的[blog][blog](~~顺便骗一波点击量~~)

题目意思很简单，就是你有三种操作：

 `$1$ $u$ $v$ $w$` 从$u$向$v$连一条权值为$w$的有向边
 
 `$2$ $u$ $L$ $R$ $w$` 从$u$向$L$至$R$的所有结点连一条权值为w的有向边
 
 `$3$ $u$ $L$ $R$ $w$` 从$L$至$R$的所有结点向$u$连一条权值为w的有向边
 
首先看到题目，马上就明白不是暴力能够解决的事情（毕竟人家是Div.1的B啊），但是看到L和R，正常人应该都会往线段树这里想一想。没错，标算就是线段树图论建模+最短路。

由于连的是有向边，一棵线段树可能难以满足我们的要求，那就建两棵线段树吧。

举个例子：

----
```
样例输入：
4 3 1
3 4 1 3 1
2 1 2 4 2
1 2 3 3
样例输出：
0 2 2 1
```
----

样例解释：
你有三个操作，首先由[1, 3]中所有结点向4号结点连一条权值为1的有向边
其次，从1号结点出发向[2, 4]中左右结点连一条权值为2的有向边，最后，从2到3连一条权值为1的有向边。
写贴一个亲自画的图~
![](https://img-blog.csdn.net/20180521210255103?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0Rpb2dlbmVzXw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
看到这张图应该就比较清晰了，给1和2两个操作分别建一棵线段树，加边（具体解释起来有点麻烦，贴代码的时候写写注释解释一下），然后就能很清晰的看到一个图论的模型，然后跑一遍最短路就可以啦~

----

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define N 100010
#define M 300110
#define lint long long
#define min(x, y) ((x) < (y) ? (x) : (y))
int n, m, s, cnt, root1, root2;
int head[M], lc[M], rc[M], tot;
struct edge {
	int v, w, nxt; 
}edge[N * 20];
inline void AddEdge(int u, int v, int w) { //在图中添加一条从u连向v的权值为w的单向边
    edge[++tot].v = v, edge[tot].w = w, edge[tot].nxt = head[u]; head[u] = tot; //前向星存边
}
void build1(int &p,int l,int r) { //build关于2操作的线段树
    if (l == r) {
		p = l; //已经是子节点，直接赋值，以便后面加边。
		return;
	}
    p = ++cnt;  //数组模拟链表
    int mid = (l + r) >> 1;
    build1(lc[p], l, mid);
    build1(rc[p], mid + 1, r);
    AddEdge(p, lc[p], 0); //从p向p的左右子树添加一条权值为0的有向边
	AddEdge(p, rc[p], 0); //上图的左边一半的灰色边就是这个build创建的
}
void build2(int &p, int l, int r) { //build关于3操作的线段树
    if (l == r) { 
		p = l; 
		return;
	}
    p = ++cnt;
    int mid = (l + r) >> 1;
    build2(lc[p], l, mid);
    build2(rc[p], mid + 1, r);
    AddEdge(lc[p], p, 0); //从p的左右子树向p添加一条权值为0的有向边
	AddEdge(rc[p], p, 0); //右边一半的灰色边就是这个build创建的
}
int L, R;
void updata(int p, int l, int r, int u, int w, int type) {
    if(L <= l && r <= R) { //完全涵盖直接根据type加边
        type == 2 ? AddEdge(u, p, w) : AddEdge(p, u, w);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) updata(lc[p], l, mid, u, w, type);
    if (mid < R) updata(rc[p], mid + 1, r, u, w, type);
}
const lint INF = 0x3F3F3F3F3F3F3F3F;
lint dist[M];
std::queue<int> Q;
void SPFA(int s) {  //最短路部分
    memset(dist, 0x3F, sizeof dist);
    dist[s] = 0; Q.push(s);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].v, w = edge[i].w;
            if (dist[u] + w < dist[v]) 
				dist[v] = dist[u] + w,
				Q.push(v);
        }
    }
}
int main() {
	scanf("%d%d%d", &n, &m, &s);
    cnt = n; //由于建边要求，线段树的结点从n+1开始编号
    build1(root1, 1, n); 
	build2(root2, 1, n);
    while (m--) {
        int opt, u, v, w;
		scanf("%d", &opt);
        if(opt == 1) {
			scanf("%d%d%d", &u, &v, &w);
            AddEdge(u, v, w); //由于上面对叶子结点的处理，这里可以直接加边
        }
        else {
			scanf("%d%d%d%d", &u, &L, &R, &w);
        	updata(opt == 2 ? root1 : root2, 1, n, u, w, opt);
        }
    }
    SPFA(s);
    for(int i = 1; i <= n; i++) 
		std::cout << (dist[i] < INF ? dist[i] : -1) << " ";
    return 0;
}
```


[blog]:https://blog.csdn.net/diogenes_/article/details/80396914

---

## 作者：LawrenceSivan (赞：14)

# 线段树优化建图学习笔记

## 前言

做了题总还是要写一篇博客记录一下。

毕竟是比较经典的 trick

虽然咕了很久但为时不晚。

## 概述

对于一类题目，我们需要对于一个区间 $[l_0,r_0]$ 向另外一个区间 $[l_1,r_1]$ 中对应的两点一一连边。

如果一一连边，那么复杂度是 $\mathcal{O(n^2)}$ 的，时空不足。

对于区间问题，一般可以使用一些数据结构进行处理。

线段树是不错的选择。

我们可以使用每一个区间都可以对应线段树上 $\mathcal{\log n}$ 个区间的性质来减少边的个数。

## 算法流程

对于一个具体的区间，我们必定可以在线段树上找到合理的对应区间，并且向他们连边。

如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/vqsxuyxc.png)

只这样连边是不足的。

我们需要做的是对于区间中的所有点都需要连边。

解决方案是直接将父区间向子区间连边就可以了，边权是 $0$ 。

实际意义是父亲区间可以直接进入子区间，代价是零。

父区间可以认为是所有子区间的状态叠加，或者是总体状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/15j9cfog.png)

相对应的，还需要另外一颗树，内部是子节点向父节点连边，边权是 $0$​.

![](https://cdn.luogu.com.cn/upload/image_hosting/yqlhz857.png)

接下来需要考虑的问题就是，这两棵树内叶子节点都是原图中的节点，本质上其实是相同的节点，所以对应的叶子节点也要互相连边，边权是 $0$​​ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/80hxa22q.png)

需要注意的问题是连边的方向。

首先明确以下定义：

**入树** ：处理进入节点的树

**出树** ：处理输出节点的树

也就是说，入树中的节点应该是对应起始节点，而出树中的节点应该是对应结束节点。

自然连边也应该是由初始节点向结束节点连边。

根据上面的说法，我们应当称上图中右侧的树为入树，左侧的树为出树。

这一点可能会与一部分线段树优化建图的入门博客有所不同，但是我个人在经过斟酌之后选择了这一种更方便记忆与理解的说法。

对于出树与入树的连边方向是有着严格要求的。

如果不慎将边连反，比如造成了入树中却出现了边向树中连的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/uo7x9c7c.png)



可以发现，原本节点 $u$ 只能访问到 $[l,mid]$ ，但是通过入树中的父向连边，却能够访问到整个的 $[l,r]$ ，这样就出现了严重的问题。

一种简单的记忆方法是，变的方向与父子边方向相同（自然是直观图画上）

对于具体的建边操作，我们通过例题来看：

[CF786B Legacy](https://www.luogu.com.cn/problem/CF786B)

简单来说，要求最短路。

建边方式有三种：

- 给定两个节点，节点之间直接建边。

- 给定一个节点和一个区间，要求建立有向边 $u \rightarrow [l,r]$ ，即点区间边

- 给定一个区间和一个节点，要求建立有向边 $[l,r]\rightarrow v$ ，即区间点边。

  

对于第一种建边，只需要在入树和出树上的叶子节点直接建边就可以了。

对于第二种建边，由入树的对应叶子节点向出树中对应区间建边即可。

对于第三种建边，由入树的对应区间向出数中对应叶子节点建边即可。

于是相当于是单点操作，线段树随便维护。

题就做完了。

## 代码：

```cpp
//#define LawrenceSivan
 
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define INF 0x3f3f3f3f3f3f3f3f
#define re register
#define int ll
 
const int maxn=1e5+5;
 
int n,m,s,op;
 
namespace SegTree_for_graph{
    int head[maxn*10],to[maxn*30],nxt[maxn*30],w[maxn*30],cnt;
 
    inline void add(int u,int v,int val){
        nxt[++cnt]=head[u];
        to[cnt]=v;
        w[cnt]=val;
        head[u]=cnt;
    }
 
    int rt1,rt2,tot;
    
    int ls[maxn*30],rs[maxn*30];
 
    int in[maxn*30],out[maxn*30];
 
    #define ls ls[rt]
    #define rs rs[rt]
 
    void build_in(int &rt,int l,int r){
        rt=++tot;
        if(l==r){
            in[l]=rt;
            return;
        }
 
        int mid=(l+r)>>1;
        build_in(ls,l,mid);
        build_in(rs,mid+1,r);
 
        add(ls,rt,0);add(rs,rt,0);
    }
 
    void build_out(int &rt,int l,int r){
        rt=++tot;
        if(l==r){
            out[l]=rt;
            return;
        }
 
        int mid=(l+r)>>1;
        build_out(ls,l,mid);
        build_out(rs,mid+1,r);
 
        add(rt,ls,0);add(rt,rs,0);
    }
 
    void modify_in(int rt,int l,int r,int ql,int qr,int pos,int val){
        if(ql>r||qr<l)return;
        if(ql<=l&&qr>=r){
            add(rt,pos,val);
            return;
        }
        int mid=(l+r)>>1;
        modify_in(ls,l,mid,ql,qr,pos,val);
        modify_in(rs,mid+1,r,ql,qr,pos,val);
    }
 
    void modify_out(int rt,int l,int r,int ql,int qr,int pos,int val){
        if(ql>r||qr<l)return;
        if(ql<=l&&qr>=r){
            add(pos,rt,val);
            return;
        }
        int mid=(l+r)>>1;
        modify_out(ls,l,mid,ql,qr,pos,val);
        modify_out(rs,mid+1,r,ql,qr,pos,val);
    }
    
}
 
using namespace SegTree_for_graph;
 
#define P pair<int,int> 
#define mp make_pair
 
priority_queue<P,vector<P>,greater<P> > q;
 
int dis[maxn*10];
 
bool vis[maxn*10];
 
inline void Dijkstra(int s){
    s=in[s];
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push(mp(0,s));
    while(!q.empty()){
        int u=q.top().second;q.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(re int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dis[v]>dis[u]+w[i]){
                dis[v]=dis[u]+w[i];
                q.push(mp(dis[v],v));
            }
        }
    }
}
 
namespace Read{
    template<typename T>
    inline void read(T &x){
        x=0;T f=1;char ch=getchar();
        while (!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
        while (isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
        x*=f;
    }
 
    template <typename T, typename... Args>
    inline void read(T& t, Args&... args) {
        read(t); read(args...);
    }
}
 
using namespace Read;
 
signed main() {
#ifdef LawrenceSivan
    freopen("aa.in","r", stdin);
    freopen("aa.out","w", stdout);
#endif
    read(n,m,s);
 
    build_in(rt1,1,n);
    build_out(rt2,1,n);
 
    for(re int i=1;i<=n;i++){
        add(in[i],out[i],0);
        add(out[i],in[i],0);
    }
 
    for(re int i=1;i<=m;i++){
        read(op);
        if(op==1){
            int u,v,val;
            read(u,v,val);
            add(in[u],out[v],val);
        }
 
        if(op==2){
            int u,l,r,val;
            read(u,l,r,val);
            modify_out(rt2,1,n,l,r,in[u],val);
        }
 
        if(op==3){
            int v,l,r,val;
            read(v,l,r,val);
            modify_in(rt1,1,n,l,r,out[v],val);
        }
    }
 
    Dijkstra(s);
 
    for(re int i=1;i<=n;i++){
        if(dis[out[i]]==INF)printf("-1 ");
        else printf("%lld ",dis[out[i]]);
    }
 
 
    return 0;
}
```



---

## 作者：Karry5307 (赞：13)

### 题意

有 $n$ 个点和 $q$ 次操作，每一次操作为以下三种类型中的一种 ：

- `1 u v w`：连一条 $u\to v$ 的单向边，权值为 $w$。

- `2 u l r w`：对于所有 $i\in [l,r]$ 连一条 $u\to i$ 的单向边，权值为 $w$。

- `3 u l r w`：对于所有 $i\in [l,r]$ 连一条 $i\to u$ 的单向边，权值为 $w$。

最后你需要求出点 $s$ 到其他点的最短路。

$\texttt{Data Range:}1\leq n,q\leq 10^5,1\leq w\leq 10^9$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13583069.html)

好久没看线段树优化连边了，这次写篇题解来复习复习。

注意到如果 $2$ 和 $3$ 操作暴力搞的话那边数会爆炸，所以我们需要考虑将一个区间内的点缩成一个，于是自然想到用线段树来优化。

首先考虑只有 $2$ 操作时怎么做。

考虑先建出线段树，对于某一个 $u$ 向 $[l,r]$ 连边的操作，在线段树上搞出 $[l,r]$ 所对应的若干区间，然后 $u$ 依次向这些区间连边即可。

但是这样是错的，因为一个线段树上代表的区间与子区间没有边连接所以跑最短路会出问题。所以在建树的时候，应该从这个区间向两个子区间连边权为 $0$ 的边才行。

接下来考虑 $3$ 操作，同样的思路，其实就是 $[l,r]$ 对应的若干区间向 $u$ 连边，然后线段树中两个子区间向这个区间连边即可。

最后考虑 $1$ 操作，由于线段树上的叶节点就是一个一个的单点，所以我们可以直接拿叶子节点互相连边即可。

这里有一个处理方法就是使用动态开点线段树，叶节点编号为 $1\sim n$，线段树上的非叶节点一个一个编号。也就是建两棵线段树，一棵代表往子区间连边，另一棵往父节点连边，其中叶节点是重合的，如图所示：

![dHPLmd.jpg](https://s1.ax1x.com/2020/08/29/dHPLmd.jpg)

蓝色的节点代表从上往下连的，红色的代表从下往上连的，叶节点为两棵树所共享。

最后的最后，有一个实现细节，就是你写结构体式线段树会让你 T 到怀疑人生。

### 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1e5+51;
const li inf=0x3f3f3f3f3f3f3f3f;
struct Edge{
	ll to,prev,dist;
};
struct Tuple{
	li x,y;
	inline bool operator <(const Tuple &rhs)const
	{
		return this->x>rhs.x;
	}
};
Edge ed[MAXN*20];
priority_queue<Tuple>pq;
ll cnt,nc,tot,rt,rtx,qcnt,source,op,x,y,l,r,dist;
ll last[MAXN<<2],inQueue[MAXN<<2],ls[MAXN<<2],rs[MAXN<<2];
li dis[MAXN<<2];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void addEdge(ll from,ll to,ll dist)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	ed[tot].dist=dist;
	last[from]=tot;
}
inline ll createDown(ll l,ll r)
{
	if(l==r)
	{
		return l;
	}
	ll mid=(l+r)>>1,cur=++nc;
	ls[cur]=createDown(l,mid),rs[cur]=createDown(mid+1,r);
	addEdge(cur,ls[cur],0),addEdge(cur,rs[cur],0);
	return cur;
}
inline ll createUp(ll l,ll r)
{
	if(l==r)
	{
		return l;
	}
	ll mid=(l+r)>>1,cur=++nc;
	ls[cur]=createUp(l,mid),rs[cur]=createUp(mid+1,r);
	addEdge(ls[cur],cur,0),addEdge(rs[cur],cur,0);
	return cur;
}
ll lx,rx;
inline void link(ll l,ll r,ll x,ll dist,ll node,ll type)
{
	if(lx<=l&&rx>=r)
	{
		type?addEdge(node,x,dist):addEdge(x,node,dist);
		return;
	}
	ll mid=(l+r)>>1;
	if(lx<=mid)
	{
		link(l,mid,x,dist,ls[node],type);
	}
	if(rx>mid)
	{
		link(mid+1,r,x,dist,rs[node],type);
	}
}
inline void Dijkstra(ll source)
{
	ll top;
	dis[source]=0,inQueue[source]=1,pq.push((Tuple){0,source});
	while(!pq.empty())
	{
		top=pq.top().y,pq.pop(),inQueue[top]=0;
		for(register int i=last[top];i;i=ed[i].prev)
		{
			if(dis[ed[i].to]>dis[top]+ed[i].dist)
			{
				dis[ed[i].to]=dis[top]+ed[i].dist;
				if(!inQueue[ed[i].to])
				{
					inQueue[ed[i].to]=1;
					pq.push((Tuple){dis[ed[i].to],ed[i].to});
				}
			}
		}
	}
} 
int main()
{
	cnt=nc=read(),qcnt=read(),source=read();
	rt=nc+1,createDown(1,cnt),rtx=nc+1,createUp(1,cnt);
	for(register int i=0;i<qcnt;i++)
	{
		op=read();
		if(op==1)
		{
			x=read(),y=read(),dist=read(),addEdge(x,y,dist);
			continue;
		}
		x=read(),lx=read(),rx=read(),dist=read();
		link(1,cnt,x,dist,op^3?rt:rtx,op-2);
	}
	memset(dis,0x3f,sizeof(dis)),Dijkstra(source);
	for(register int i=1;i<=cnt;i++)
	{
		printf("%lld ",dis[i]==inf?-1:dis[i]);
	}
}
```

---

## 作者：Y15BeTa (赞：10)

在qbxt某营集体做的

题解里以及外地OIer基本上都写两颗线段树的

而我们六安的OIer神TM思维一致——只用一颗线段树，类似于一维分层图的思想，第二层上与第一层相对应的结点的编号是第一层结点编号+NUM，而且貌似比分颗的思维正常一点，因为满足lson=k<<1,rson=k<<1|1，和一般的线段树相似度高。

至于为什么要分颗或分层，容易想明白树边（辅助边）必须是双向的（因为要用祖先结点的出入信息），但如果不分颗或分层的话求出来最短路不很明显是0了吗QwQ

所以分层的话父向子应是一层，子向父应在另一层，两层之间通过叶节点相连

另外关于叶结点的处理问题，YoOXiii和Pride205是把原图第i结点投影到树上第i+n结点（n为原图结点个数）

这个详见他们的代码（其实我也没仔细研究清楚他们的处理方法），这里不偷了（偷窃犯罪w），要看自己找

由于我和他们不坐一块，想思路时没有交流，所以我没有这样写，我是把第一层按照一般线段树的编号建，这样容易一点。然后把原图结点直接向叶子结点映射即可（开一个pos数组）（才知道szsz46也是这么写的，原来六安OIer的思维同步性不随空间改变QwQ）

然后......

上代码吧

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
#define NUM 1000000
#define maxn 100005<<5
//这两个范围要调好 
#define int long long
using namespace std;
typedef long long ll;

inline void input(ll &x){
    ll ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        ans=ans*10+c-48;
        c=getchar();
    }
    x=ans*f;
}

inline void output(ll x){
    if(x<0)x=-x,putchar('-');
    if(x>9)output(x/10);
    putchar(x%10+48);
}

inline void writeln(ll x){
    output(x);
    putchar('\n');
}

int n,m,s,head[maxn],c[maxn],pos[maxn],vis[maxn],dis[maxn],cnt;

//pos:题中结点在树上的编号 

struct edge{
	int v,w,next;
}e[maxn];

struct node{
	int dis,u;
	bool operator<(const node &x)const{return x.dis<dis;}
};

inline void add(int u,int v,int w){
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
//	cout<<u<<' '<<v<<' '<<w<<endl;
}

inline void build(int k,int l,int r){
	if(l==r){
		pos[l]=k;
		add(k+NUM,k,0);
		add(k,k+NUM,0);
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	add(k<<1,k,0);
	add(k<<1|1,k,0);
	add(k+NUM,(k<<1)+NUM,0);//调了一个小时：加括号；在括号外加NUM而不是给k加NUM 
	add(k+NUM,(k<<1|1)+NUM,0);
}

inline void add(int k,int l,int r,int xl,int xr,int from,int w,int opt){
	if(xl<=l&&r<=xr){
		if(opt==2)add(from,k+NUM,w);
		else if(opt==3)add(k,from,w);
		return;
	}
	int mid=(l+r)>>1;
	if(xl<=mid)add(k<<1,l,mid,xl,xr,from,w,opt);
	if(xr>=mid+1)add(k<<1|1,mid+1,r,xl,xr,from,w,opt);
}

priority_queue<node> q;

inline void dijkstra(){
	s=pos[s];
	q.push((node){0,s});
	dis[s]=0;
	while(!q.empty()){
		int x=q.top().u;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i!=-1;i=e[i].next){
			int y=e[i].v;
			if(!vis[y]&&dis[y]>dis[x]+e[i].w){
				dis[y]=dis[x]+e[i].w;
				q.push((node){dis[y],y});//想不到吧，这一行打错使我调了半个小时 
			}
		}
	}
	s<<=1;
	if(s>=1)dijkstra();
}

signed main(){
	memset(head,-1,sizeof(head));
	memset(dis,127,sizeof(dis));
	memset(vis,0,sizeof(vis));
	input(n);input(m);input(s);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int opt;
		input(opt);
		if(opt==1){
			int u,v,w;
			input(u);input(v);input(w);
			add(pos[u],pos[v],w);
		}
		else if(opt==2){
			int u,l,r,w;
			input(u);input(l);input(r);input(w);
			add(1,1,n,l,r,pos[u],w,opt);
		}
		else if(opt==3){
			int u,l,r,w;
			input(u);input(l);input(r);input(w);
			add(1,1,n,l,r,pos[u],w,opt);
		}
	}
	dijkstra();
//	for(int i=1;i<=4*n;i++)cout<<i<<' '<<dis[i]<<endl;
	for(int i=1;i<=n;i++)output(dis[pos[i]]<=1e15?dis[pos[i]]:-1),putchar(' ');
}

```

在此感谢Layz的三位神仙OIer

---

## 作者：Miko35 (赞：9)

萌新刚学 OI，不会线段树，更不会线段树优化建图，所以写了 ST 表优化建图过了。

~~萌新刚学 OI，不会 dij，所以写了 SPFA 过了。~~

## ST 表优化建图

线段树优化建图利用了线段树能把一段区间拆成 $\log n$ 份的特性。

ST 表也可以处理区间问题，并且有着“能把一段区间拆成 $O(1)$ 个区间的并”的优秀性质，在处理极值问题上有优秀的查询复杂度。

最短路要最短，不也是个 $\textrm{min}$ 嘛，那就考虑如何 ST 表优化区间连边。

然后就可以发现一条有意思的性质：对于原图中任意一条边，把这条边重复地连一万遍，对最短路的结果不产生影响。

这说明，把一个点分别连到某些区间上，等价于连到这些区间的并上。回顾 ST 表的性质，然后就会发现很简单了。

具体而言，观察 ST 表上的一个区间，你发现它维护的信息是这个区间内所有节点信息的并。如果对于每个区间，往下向“通过合并直接得到它的两个区间”连权值为 $0$ 的边，那向这个区间所代表的节点连一条权值为 $w$ 的边，就等价于向区间内每个点连了一条这样的边了。

举例说明：$8$ 个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/fu6dfcb6.png)

如果点 $u$ 要像 $[2,7]$ 连边，首先把 $[2,7]$ 变为 $[2,5] \cup [4,7]$，然后分别向它们连边：

![](https://cdn.luogu.com.cn/upload/image_hosting/d7xqr64m.png)

可以看到，经过绿色节点和边，最终等价于连向了 $[2,7]$。

这是从上往下走的 ST 表，从下往上走同理，与线段树优化建图相似。最后在叶子节点连上 $0$ 边，我的实现是直接共用了叶子节点。

预处理建了 $O(n\log n)$ 条边，一次修改会建 $O(1)$ 条，所以共 $O(n\log n+q)$ 条边。

```cpp
for(rgi i=1;i<=n;++i)st[0][i][0]=st[0][i][1]=i;
for(rgi w=1;w<LOG;++w){
	for(rgi i=1;i+(1<<w)-1<=n;++i){
		st[w][i][0]=++tot;
		link(st[w-1][i][0],tot,0),link(st[w-1][i+(1<<w-1)][0],tot,0);
		st[w][i][1]=++tot;
		link(tot,st[w-1][i][1],0),link(tot,st[w-1][i+(1<<w-1)][1],0);
	}
}
while(m--){
	read(opt,v);
	if(opt==1)read(u,w),link(v,u,w);
	else{
		read(l,r,w),k=log2(r-l+1);
		if(opt==2)link(v,st[k][l][1],w),link(v,st[k][r-(1<<k)+1][1],w);
		else link(st[k][l][0],v,w),link(st[k][r-(1<<k)+1][0],v,w);
	}
}
```

~~这不比线段树好写~~

## SPFA 活了 

吗？

参考了 [复活 SPFA - TOE 的博客](https://toe.blog.uoj.ac/blog/6660) 这篇文章。

我的实现主要来讲有两个：

- 取出队尾若干项与队首判断，若距离更小则交换之。

- 队内随机取出若干项与队首判断，若距离更小则交换之。

第二个很重要，能有效规避很多怪异的数据。

~~这不比 dij 好写~~

完整的代码实现，时间复杂度 $O(n^2\log^2 n+qn\log n)$ 或 $O(kn\log n+kq)$，其中 $k$ 为常数。

```cpp
#include<bits/stdc++.h>
#define rgi register int
typedef long long ll;
using namespace std;
inline void read(){}template <typename T,typename... Ts> inline void read(T& A,Ts&... As){
	T x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	A=x*f,read(As...);
}
const int N=100010,LOG=20;
const ll inf=1e18;
int n,m,s,tot,st[LOG][N][2];
int nxt[N<<6],to[N<<6],hd[N<<6],C;
int opt,v,l,r,u,k;
ll d[N<<6],val[N<<6],w;
void link(int u,int v,int w){
	to[++C]=v,val[C]=w,nxt[C]=hd[u],hd[u]=C;
}
int q[N<<6],x,in[N<<6];
mt19937 rnd(time(0));
void chk(int g){
	if(d[q[l]]>d[q[g]])swap(q[g],q[l]);
}
signed main(){
	read(n,m,s),tot=n;
	for(rgi i=1;i<=n;++i)st[0][i][0]=st[0][i][1]=i;
	for(rgi w=1;w<LOG;++w){
		for(rgi i=1;i+(1<<w)-1<=n;++i){
			st[w][i][0]=++tot;
			link(st[w-1][i][0],tot,0),link(st[w-1][i+(1<<w-1)][0],tot,0);
			st[w][i][1]=++tot;
			link(tot,st[w-1][i][1],0),link(tot,st[w-1][i+(1<<w-1)][1],0);
		}
	}
	while(m--){
		read(opt,v);
		if(opt==1)read(u,w),link(v,u,w);
		else{
			read(l,r,w),k=log2(r-l+1);
			if(opt==2)link(v,st[k][l][1],w),link(v,st[k][r-(1<<k)+1][1],w);
			else link(st[k][l][0],v,w),link(st[k][r-(1<<k)+1][0],v,w);
		}
	}
	for(rgi i=1;i<=tot;++i)d[i]=inf;
	d[q[l=r=1]=s]=0;
	while(r>=l){
		for(rgi i=r;i>=l&&i>=r-3;--i)chk(i);
		for(rgi i=5;i;--i)chk(l+rnd()%(r-l+1));
		in[x=q[l++]]=0;
		for(rgi i=hd[x];i;i=nxt[i]){
			if(d[v=to[i]]>d[x]+val[i]){
				d[v]=d[x]+val[i];
				if(!in[v])in[q[++r]=v]=1;
			}
		}
	}
	for(rgi i=1;i<=n;++i)printf("%lld ",d[i]==inf?-1:d[i]);
	return 0;
}
```




---

## 作者：rui_er (赞：8)

线段树优化建图模板题。

题意：

三种连边方式：

- $v\to u$ 点到点连边。
- $v\to [l,r]$ 点到区间所有点连边。
- $[l,r]\to v$ 区间所有点到点连边。

给定源点，求到所有点的最短路。

---

思路：

暴力连边显然会炸，考虑优化。

看到 $10^5$ 的数据范围和区间连边，自然而然地想到线段树，可以建线段树，在线段树上连边。

我们首先建两棵线段树，一棵是“出树”一棵是“入树”，“出树”从根 $[1,n]$ 向叶子方向连边，“入树”从叶子向根 $[1,n]$ 方向连边，边权均为 $0$。

然后对于点到点连边，直接连即可。对于点到区间连边，我们采用类似线段树区间修改的方式，递归“出树”找到被区间恰好覆盖的若干个节点进行连边。对于区间到点连边，递归“入树”连边即可。

建图完毕后，跑一遍堆优化 Dijkstra 即可。

---

坑点：

- 因为 $1\sim n$ 是单点，所以线段树动态开点的编号应该从 $n+1$ 开始。
- 线段树优化建图的点数、边数远大于 $n$，数组记得开大。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
using namespace std;
typedef long long ll;
const ll N = 3e6+5, inf = 0x3f3f3f3f3f3f3f3fll;

ll n, q, s, tot, dis[N], vis[N], rt[2];
struct Edge {
	ll v, w, nxt;
	Edge(ll a=0, ll b=0, ll c=0) : v(a), w(b), nxt(c) {}
	~Edge() {}
}e[N];
ll ne = 1, h[N];
void add(ll u, ll v, ll w) {e[++ne] = Edge(v, w, h[u]); h[u] = ne;}
struct Node {
	ll l, r, lc, rc;
}t[N];
void build(ll &u, ll l, ll r, ll k) { // k=0,1 <=> In/Out Tree
	t[u].l = l; t[u].r = r;
	if(l == r) {u = l; return;}
	u = ++tot;
	ll mid = (l + r) >> 1;
	build(t[u].lc, l, mid, k);
	build(t[u].rc, mid+1, r, k);
	if(k) add(u, t[u].lc, 0), add(u, t[u].rc, 0);
	else add(t[u].lc, u, 0), add(t[u].rc, u, 0);
}
void modify(ll u, ll l, ll r, ll st, ll ql, ll qr, ll w, ll k) { // k=0,1 <=> []->#/#->[] 
	if(ql <= l && r <= qr) {
		if(k) add(st, u, w);
		else add(u, st, w);
		return;
	}
	ll mid = (l + r) >> 1;
	if(ql <= mid) modify(t[u].lc, l, mid, st, ql, qr, w, k);
	if(qr > mid) modify(t[u].rc, mid+1, r, st, ql, qr, w, k);
}
priority_queue<pair<ll, ll> > hp;
void dijkstra(ll s) {
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0; hp.push(make_pair(0, s));
	while(!hp.empty()) {
		ll u = hp.top().second; hp.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(ll i=h[u];i;i=e[i].nxt) {
			ll v = e[i].v, w = e[i].w;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				hp.push(make_pair(-dis[v], v));
			}
		}
	}
}

int main() {
	scanf("%lld%lld%lld", &n, &q, &s);
	tot = n;
	build(rt[0], 1, n, 0);
	build(rt[1], 1, n, 1);
	rep(i, 1, q) {
		ll op, a, b, c, d;
		scanf("%lld%lld%lld%lld", &op, &a, &b, &c);
		if(op != 1) scanf("%lld", &d);
		if(op == 1) add(a, b, c);
		else if(op == 2) modify(rt[1], 1, n, a, b, c, d, 1);
		else modify(rt[0], 1, n, a, b, c, d, 0);
	}
	dijkstra(s);
	rep(i, 1, n) printf("%lld%c", dis[i]<inf?dis[i]:-1, " \n"[i==n]);
	return 0;
}
```

---

## 作者：suxxsfe (赞：5)

[模板题CF786B Legacy](https://www.luogu.com.cn/problem/CF786B)  
先说算法  
如果需要有n个点需要建图  
给m个需要建边的信息，从单点（或区间内所有点）向一区间所有点连边  
如果暴力建图复杂度$mn^2$  
以单点连向区间为例，在n个点上建一颗线段树，叶子节点即为这n个点，每个节点向它的左右儿子连一个权值为0的边，这样我们只要向一个节点连边，也就相当于向它所在的区间每个点都连边了（因为连到这个节点，就能顺着线段树中0边权的路一路走到叶子节点，也就是真正存在的节点）  
这样可以用类似与线段树区间查找的方法，以$logn$的复杂度向$[l,r]$内所有点连边  
如果是区间连向区间（$[l,r]$连向$[l',r']$），可以建两颗线段树，一棵in（由外面往这颗树连边）树，一棵out（由这棵树向外连边）树，和一个虚拟节点  
在out树中从$[l,r]$向虚拟节点连边，再由虚拟节点向in树中的$[l',r']$连边  
注意这里out树是有区间往外连，所以线段树中的边是由儿子连向父亲，因为如果编号为pos的节点要向外连一条边，它要先顺着线段树中的边走到某一个父亲，再由此去其他节点  
再看这道题就简单了  
也是要建一颗in树一颗out树  
第一种方案直接连边  
第二种方案由节点v向in树中$[l,r]$连边  
第三种由out树中$[l,r]$向v节点连边  
最后跑个最短路就行了  
具体实现见代码  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define R register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n,m,s,nn;
int fir[500006],nex[4000005],to[4000006],len[4000006],tot;
struct tr{
	tr *ls,*rs;
	int id;
}dizhi[400006],*rootin=&dizhi[0],*rootout=&dizhi[1];
int dizhitot=1;
LL dis[500006];
int in[500006];
int dui[500006],size;
inline void push(int x){
	dui[size++]=x;
	R int i=size-1,fa;
	while(i){
		fa=i>>1;
		if(dis[dui[fa]]<=dis[dui[i]]) return;
		std::swap(dui[fa],dui[i]);i=fa;
	}
}
inline int pop(){
	int ret=dui[0];dui[0]=dui[--size];
	R int i=0,ls,rs;
	while((i<<1)<size){
		ls=i<<1;rs=ls|1;
		if(rs<size&&dis[dui[rs]]<dis[dui[ls]]) ls=rs;
		if(dis[dui[ls]]>=dis[dui[i]]) break;
		std::swap(dui[ls],dui[i]);i=ls;
	}
	return ret;
}
inline void dij(){
	std::memset(dis,0x3f,sizeof dis);
	in[s]=1;push(s);dis[s]=0;
	while(size){
		R int u=pop();in[u]=0;
		for(R int i=fir[u];i;i=nex[i]){
			R int v=to[i];
			if(dis[v]>dis[u]+len[i]){
				dis[v]=dis[u]+len[i];
				if(!in[v]) push(v),in[v]=1;
			}
		}
	}
}
inline void add(int u,int v,int w){
	to[++tot]=v;len[tot]=w;
	nex[tot]=fir[u];fir[u]=tot;
}
void build(tr *treein,tr *treeout,int l,int r){
	if(l==r){treein->id=treeout->id=l;return;}
	int mid=(l+r)>>1;
	treein->ls=&dizhi[++dizhitot];treein->rs=&dizhi[++dizhitot];
	treeout->ls=&dizhi[++dizhitot];treeout->rs=&dizhi[++dizhitot];
	build(treein->ls,treeout->ls,l,mid);build(treein->rs,treeout->rs,mid+1,r);
	treein->id=++nn;treeout->id=++nn;
	add(treein->id,treein->ls->id,0);add(treein->id,treein->rs->id,0);
	add(treeout->ls->id,treeout->id,0);add(treeout->rs->id,treeout->id,0);
}
void addtreein(tr *tree,int l,int r,int ql,int qr,int u,int w){
	if(ql<=l&&r<=qr){add(u,tree->id,w);return;}
	int mid=(l+r)>>1;
	if(ql<=mid) addtreein(tree->ls,l,mid,ql,qr,u,w);
	if(qr>mid) addtreein(tree->rs,mid+1,r,ql,qr,u,w);
}
void addtreeout(tr *tree,int l,int r,int ql,int qr,int v,int w){
	if(ql<=l&&r<=qr){add(tree->id,v,w);return;}
	int mid=(l+r)>>1;
	if(ql<=mid) addtreeout(tree->ls,l,mid,ql,qr,v,w);
	if(qr>mid) addtreeout(tree->rs,mid+1,r,ql,qr,v,w);
}
int main(){
	nn=n=read();m=read();s=read();
	build(rootin,rootout,1,n);
	while(m--){
		int op=read();
		if(op==1){
			int u=read(),v=read(),w=read();
			add(u,v,w);
		}
		else if(op==2){
			int u=read(),l=read(),r=read(),w=read();
			addtreein(rootin,1,n,l,r,u,w);
		}
		else{
			int v=read(),l=read(),r=read(),w=read();
			addtreeout(rootout,1,n,l,r,v,w);
		}
	}
	dij();
	for(R int i=1;i<=n;i++)
		std::printf("%lld ",dis[i]==0x3f3f3f3f3f3f3f3f?-1:dis[i]);
	return 0;
}
```  
### 最后丢下几个例题  
[洛谷P3588 [POI2015]PUS](https://www.luogu.com.cn/problem/P3588)  
[题解](https://www.luogu.com.cn/blog/suxxsfe/solution-p3588)  
&nbsp;  
[bzoj5017[Snoi2017]炸弹](https://www.lydsy.com/JudgeOnline/problem.php?id=5017) /[洛谷P5025 [SNOI2017]炸弹](https://www.luogu.com.cn/problem/P5025)  
[题解](https://www.luogu.com.cn/blog/suxxsfe/ti-xie-bzoj5017snoi2017-zha-tan)，~~当时交了一页最后发现是没开long long~~  
&nbsp;  
[bzoj3073[Pa2011]Journeys](https://www.lydsy.com/JudgeOnline/problem.php?id=3073)，算是一个模板题了，就是那种边从区间连向区间的情况，而且这是01边权，用双端队列bfs就行，看网上好多人都写的dij  
但需要权限，所以可以去[这上面](https://darkbzoj.tk/problem/3073)看看  
~~题解没写~~  
&nbsp;  
[bzoj2143飞飞侠](https://www.lydsy.com/JudgeOnline/problem.php?id=2143)，一开始写了个那种三维的dp，但不知道是常数问题还是写炸了已知TLE，之后改的线段树建边  
~~题解依旧没写~~  
&nbsp;  
[CF1045A Last chance](http://codeforces.com/contest/1045/problem/A)，这个还需要网络流，不会，以后再写吧。。  


---

## 作者：lhm_ (赞：5)

本题要求我们支持三种操作：

① 点向点连边。 ② 点向区间连边。 ③ 区间向点连边。

然后跑最短路得出答案。

考虑使用线段树优化建图。

建两颗线段树，入树和出树，每个节点为一段区间的原节点集合。入树内部为儿子向父亲连有向边，出树内部为父亲连有向边，因为入树和出树的叶子节点都为原图中的点，所以两棵树的对应叶子节点连无向边，这些边边权都为$0$。

示意图如下，左边为入树，右边为出树。

![](https://s2.ax1x.com/2019/12/17/QI3ZWj.png)

操作一时，从入树叶子节点向出树叶子节点连边（红色的线）。

操作二时，从入树叶子节点向出树所对应的区间节点连边（蓝色的线）。

操作三时，从入树所对应的区间节点向出树叶子节点连边（绿色的线）。

具体实现细节看代码吧。

记得开$long\ long$和开大数组。

$code:$
```cpp
#include<bits/stdc++.h>
#define maxn 800010
#define inf 2000000000
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,m,s,flag;
struct edge
{
    int to,nxt,v;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to,int val)
{
    e[++edge_cnt]=(edge){to,head[from],val};
    head[from]=edge_cnt;
}
int in_root,out_root,tree_cnt;
int ls[maxn],rs[maxn],in_num[maxn],out_num[maxn];
void build_in(int L,int R,int &cur)
{
    cur=++tree_cnt;
    if(L==R)
    {
        in_num[L]=cur;
        return;
    }
    int mid=(L+R)>>1;
    build_in(L,mid,ls[cur]);
    build_in(mid+1,R,rs[cur]);
    add(ls[cur],cur,0),add(rs[cur],cur,0);
}
void build_out(int L,int R,int &cur)
{
    cur=++tree_cnt;
    if(L==R)
    {
        out_num[L]=cur;
        return;
    }
    int mid=(L+R)>>1;
    build_out(L,mid,ls[cur]);
    build_out(mid+1,R,rs[cur]);
    add(cur,ls[cur],0),add(cur,rs[cur],0);
}
void modify_in(int L,int R,int l,int r,int pos,int val,int &cur)
{
    if(L<=l&&R>=r)
    {
        add(cur,pos,val);
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid) modify_in(L,R,l,mid,pos,val,ls[cur]);
    if(R>mid) modify_in(L,R,mid+1,r,pos,val,rs[cur]);
}
void modify_out(int L,int R,int l,int r,int pos,int val,int &cur)
{
    if(L<=l&&R>=r)
    {
        add(pos,cur,val);
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid) modify_out(L,R,l,mid,pos,val,ls[cur]);
    if(R>mid) modify_out(L,R,mid+1,r,pos,val,rs[cur]);
}
ll dis[maxn];
bool vis[maxn];
struct node
{
    ll val;
    int num;
};  
bool operator <(const node &x,const node &y)
{
    return x.val>y.val;
}
priority_queue<node> q;
void dijkstra()
{
    s=in_num[s];
    for(int i=1;i<=tree_cnt;++i) dis[i]=inf;
    dis[s]=0;
    q.push((node){0,s});
    while(!q.empty())
    {
        node tmp=q.top();
        q.pop();
        int x=tmp.num;
        if(vis[x]) continue;
        vis[x]=true;
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to,v=e[i].v;
            if(dis[y]>dis[x]+v)
            {
                dis[y]=dis[x]+v;
                q.push((node){dis[y],y});
            }
        }
    }
}
int main()
{
	read(n),read(m),read(s);
    build_in(1,n,in_root);
    build_out(1,n,out_root);
    for(int i=1;i<=n;++i)
        add(in_num[i],out_num[i],0),add(out_num[i],in_num[i],0);
    while(m--)
    {
        read(flag);
        int x,y,l,r,v;
        if(flag==1)
        {
            read(x),read(y),read(v);
            add(in_num[x],out_num[y],v);
        }
        if(flag==2)
        {
            read(x),read(l),read(r),read(v);
            modify_out(l,r,1,n,in_num[x],v,out_root);
        }
        if(flag==3)
        {
            read(x),read(l),read(r),read(v);
            modify_in(l,r,1,n,out_num[x],v,in_root);
        }
    }
    dijkstra();
    for(int i=1;i<=n;++i)
    {
        if(dis[out_num[i]]==inf) printf("-1 ");
        else printf("%lld ",dis[out_num[i]]);
    }
	return 0;
}
```


---

## 作者：Kelin (赞：5)

看到区间很容易就能想到线段树


一个线段树上的节点代表它在线段树上代表的区间的所有点


一棵线段树表示进,另一颗表示出


表示进的线段树要向上连边


表示出的线段树要向下连边


(画个图理解一下?)


所以进来的线段树$son->fa$长度为$0$


出去的线段树$fa->son$长度为$0$


对于操作$2$


设$pos_u$表示$u$在第一棵线段树上的节点编号


那么就把$pos_u$向所有$[ql,qr]∈[l,r]$的极大子区间的节点编号连一条长度为$w$的边


操作$3$同理,只要反过来建边就好了


每一次新建边的操作复杂度是 $O(2logn)$


最后就只要输出$s$到所有点在第二棵树上位置的点的距离就$ok$了


---

## 作者：Demoe (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/CF786B)

## 题意

- 给定一张 $n$ 个节点的有向正权图，起点为 $s$，共有 $q$ 次操作，操作分三种。

	- 点连点
    
    - 点连区间
    
    - 区间连点
   
- 求从起点出发到各个点的最短路长度，若不连通则输出 $-1$。

## 题解

先考虑暴力连边，发现时间复杂度达到了 $O(n^2)$。

考虑到区间连边，那么可以对于一个区间进行拆分。

我们很容易想到线段树。

考虑将线段树的节点作为代替一个区间的虚点。

![](https://cdn.luogu.com.cn/upload/image_hosting/7y0ylsg9.png)

显然我们需要两棵线段树，不然跑出来距离都是 $0$ 了还跑啥。（（（

我们以左边线段树的叶子节点为实际的点。

用红线代表双向边，橙色代表向下的单向边，蓝色代表向上的单向边，紫色代表向右的单向边。

![](https://cdn.luogu.com.cn/upload/image_hosting/c36xb8ma.png)

显然这是初始必须要连的边，同时这些边的边权为 $0$。

初始化时间复杂度 $O(n)$。

---

考虑操作 $1$。

直接实际的点连单向边即可。

单次操作时间复杂度 $O(1)$。

例如连 $2 \to 3$ 这条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/tupl269i.png)

---

考虑操作 $2$。

点连区间，我们将区间剖分成线段树上的节点，然后实际的点向各个表示区间的点连接即可。

单次操作时间复杂度 $O(\log n)$。

例如 $1 \to [5,8]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/8blo2lu4.png)

---

考虑操作 $3$。

单次操作时间复杂度 $O(\log n)$。

区间连点，同样我们将区间剖分为线段树上的节点，然后表示区间的点连向实际的点即可。

例如 $[1,4] \to 1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jrjnljoz.png)

---

最后合起来图就成了这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/d1f6qp14.png)

然后从原点对应的实点开始跑 Dijkstra 即可。

记得空间开大！记得开 long long！

空间复杂度上界 $O(n+q\log n)$。

时间复杂度上界 $O(n\log^2 n)$。

---

## 代码

```cpp
const int N=5e5+5,D=5e5,INF=1e17;
int n,m,st,dis[N<<1],node[N];
bool vst[N<<1];
vector<pair<int,int> >es[N<<1];

#define mid ((l+r)>>1)
#define xl (x<<1)
#define xr (x<<1|1)

inline void build(int x,int l,int r){
	if(l==r){node[l]=x;return ;}
	es[x].pb(mp(0,xl));es[x].pb(mp(0,xr));
	es[xl+D].pb(mp(0,x+D));es[xr+D].pb(mp(0,x+D));
	build(xl,l,mid);build(xr,mid+1,r);
}

inline void add(int x,int l,int r,int L,int R,int v,int w,int op){
	if(L<=l&&r<=R){
		if(op==2) es[v].pb(mp(w,x));
		else es[x+D].pb(mp(w,v));
		return ;
	}
	if(L<=mid) add(xl,l,mid,L,R,v,w,op);
	if(R>mid) add(xr,mid+1,r,L,R,v,w,op);
}

inline void dijkstra(int s){
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q; 
	fill(dis,dis+(N<<1)+1,INF);dis[s]=0;q.push(mp(0,s));
	while(!q.empty()){
		int x=q.top().second,sum=q.top().first;
		q.pop();
		if(vst[x]) continue;
		vst[x]=1;
		for(re i=0;i<es[x].size();++i){
			int t=es[x][i].second,w=es[x][i].first;
			if(dis[t]>sum+w){
				dis[t]=sum+w;
				q.push(mp(dis[t],t));
			}
		}
	}
}

// ---------- Graph ---------- //

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(m);rd(st);
	build(1,1,n);
	for(re i=1;i<=n;++i) es[node[i]].pb(mp(0,node[i]+D)),es[node[i]+D].pb(mp(0,node[i]));
	for(re i=1;i<=m;++i){
		int op,u,v,w,l,r;
		rd(op);
		if(op==1){
			rd(v);rd(u);rd(w);
			es[node[v]].pb(mp(w,node[u]));
		}
		else{
			rd(v);rd(l);rd(r);rd(w);
			add(1,1,n,l,r,node[v],w,op);
		}
	}
	dijkstra(node[st]);
	for(re i=1;i<=n;++i){
		if(dis[node[i]]==INF) cout<<"-1 ";
		else wr(dis[node[i]]),putchar(' ');
	}puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：lgswdn_SA (赞：3)

线段树优化建图模板题。

### 题面简述

有 $n$ 个点的有向图，有 $3$ 种边，分别为
- $u\to v$ 边权为 $w$  
- $u\to $ $[l,r]$ 的所有点 边权为 $w$  
- $[l,r]$ 的所有点 $\to u$ 边权为 $u$

求从 $s$ 号点到所有点的单源最短路。

### 线段树优化建图

首先最无脑的方法就是把所有的边全部都建出来跑单源最短路，$O(n^2\log n)$ 立马让你暴毙。

于是就有了线段树优化建图。线段树优化建图在于这些连接区间的边不用全部建出来，到底是什么意思我们等下再解释。先拿一个线段树过来。

![image.png](https://i.loli.net/2020/08/20/bDK1drAPmyScLeO.png)

对于第二个连边操作，$u\to [l,r]$，我们只需要从原图种的 $u$ 连向 $[l,r]$ 对应的线段树上的点就可以了。于是 $O(n)$ 的边数优化成了 $O(\log n)$。（下图例子为 $4\to [1,3]$）。

![image.png](https://i.loli.net/2020/08/20/rvPSwxLpzVJcZlC.png)  
（绿色边边权为 $w$，蓝色边边权为 $0$）。

但是这道题还可以区间连向点，于是我们再建立一棵线段树，方向为根向，然后相同的方法连边。（下图例子为 $[1,3]\to 4$。

![image.png](https://i.loli.net/2020/08/20/lYJb2ndquoSm1t9.png)

综合起来是这样的。

![image.png](https://i.loli.net/2020/08/20/sY7txHgRSzcUZyE.png)

最后一个问题，每棵树的叶节点其实就是绿色节点。你可以选择合并叶节点和绿色节点，也可以选择直接连 $0$ 权无向边。我选择后者因为更加方便一点。

![image.png](https://i.loli.net/2020/08/20/r5Lu3wFHaWq6Rd8.png)

这个建树用 zkw 更加方便一点，但是我不会，所以就递归弄。

（WA 了好久，才发现是加边出了问题 qwq）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=9e5+9, M=5e6+9; //2棵线段树+普通节点 

struct edge {int to,nxt,w;}e[M]; int hd[N],tot;
void add(int u,int v,int w) {e[++tot]=(edge){v,hd[u],w};hd[u]=tot;}

int n,q,s;

struct Node {int l,r;}t[N];
void build(int p,int l,int r) {
	t[p].l=l, t[p].r=r;
	if(l==r) {
		add(l+8*n,p,0), add(p+4*n,l+8*n,0);
		add(p,l+8*n,0), add(l+8*n,p+4*n,0);
		return;
	}
	add(p,p*2,0), add(p*2+n*4,p+n*4,0);
	add(p,p*2+1,0), add(p*2+1+n*4,p+n*4,0);
	build(p*2,l,(l+r)/2), build(p*2+1,(l+r)/2+1,r);
}
void addh(int p,int x,int y,bool type,int u,int w) {
	int l=t[p].l, r=t[p].r, mid=((l+r)>>1);
	if(l==x&&y==r) {
		if(!type) return add(u+8*n,p,w);
		else return add(p+4*n,u+8*n,w);
	}
	if(y<=mid) addh(p*2,x,y,type,u,w);
	else if(x>mid) addh(p*2+1,x,y,type,u,w);
	else addh(p*2,x,mid,type,u,w), addh(p*2+1,mid+1,y,type,u,w);
}

int d[N];
namespace ShortestPath{
	bool vst[N];
	struct Node {
		int u,w;
		bool operator < (const Node &a) const {
			return w>a.w;
		}
	};
	void dijkstra() {
		memset(d,0x3f,sizeof(d)); d[s]=0;
		priority_queue<Node>q; q.push((Node){s,0ll});
		while(!q.empty()) {
			int u=q.top().u; q.pop();
			if(vst[u]) continue;
			vst[u]=1;
			for(int i=hd[u],v;i;i=e[i].nxt) {
				if(!vst[v=e[i].to]&&d[v]>d[u]+e[i].w) {
					d[v]=min(d[v],d[u]+e[i].w);
					q.push((Node){v,d[v]});
				}
			}
		}
	}
}

signed main() {
	scanf("%lld%lld%lld",&n,&q,&s);
	build(1,1,n);
	for(int i=1,op,v,u,w,l,r;i<=q;i++) {
		scanf("%lld",&op);
		if(op==1)
			scanf("%lld%lld%lld",&v,&u,&w), add(v+8*n,u+8*n,w);
		else if(op==2)
			scanf("%lld%lld%lld%lld",&v,&l,&r,&w),
			addh(1,l,r,0,v,w);
		else if(op==3)
			scanf("%lld%lld%lld%lld",&v,&l,&r,&w),
			addh(1,l,r,1,v,w);
	}
	s+=8*n;
	ShortestPath::dijkstra();
	for(int i=1;i<=n;i++)
		if(d[i+8*n]<2e18) printf("%lld ",d[i+8*n]);
		else printf("-1 ");
	return 0;
}
```

---

## 作者：0x3F (赞：2)

题意大概是：

已知有 $n$ 个点，有三种操作：

1. `1 v u w` 表示从 $v$ 向 $u$ 连一条权值为 $w$ 的有向边。
1. `2 v l r w` 表示从 $v$ 向编号在 $l$ 到 $r$ 之间的所有点各连一条权值为 $w$ 的有向边。
1. `3 v l r w` 表示从编号在 $l$ 到 $r$ 之间的所有点向 $v$ 各连一条权值为 $w$ 的有向边。

求从 $s$ 出发到所有点的最短路，若不连通则为 $-1$。

暴力连边肯定不行，因为如果暴力连边那么总边数会达到 $n^2$ 的级别。

考虑建立一个点代表一个区间。

对于 $2$ 操作，建立一个点表示区间 $[l,r]$，从该点向区间内每一个点连一条权值为零的边，再从 $v$ 向该点连一条权值为 $w$ 的边。

对于 $3$ 操作，同理，只不过边的方向反过来而已。

但是这样还是不行，因为它不但没有减少边数，反而增加了点数。

但是这是一个很好的思路。看到“区间”，想必都会想到线段树。

由于是有向边，所以一颗线段树不够，那么就建两颗线段树。

一颗边从儿子到父亲，一颗边从父亲到儿子。

边权均为零。

然后从一个点到区间连边可以从这个点连到覆盖目标区间的所有区间。

注意一点：

# 关于SPFA：

- 它死了

```
#include <bits/stdc++.h>
#define add(u, v, w) G[u].push_back(make_pair(v, w))
using namespace std;
int n, o, v, u, l, r, w, q, s, c;
vector<pair<int, int> > G[500000];
long long dis[500000];

struct SEG_TREE_NODE {
	int l, r;
	int ls, rs;
}st[500000];
int t1, t2;

void dijskra(void) {
	bool vis[500000];
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3F, sizeof(dis));
	dis[s] = 0;
	priority_queue<pair<long long, int> > Q;
	Q.push(make_pair(0ll, s));
	while (!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if (!vis[u]) {
			vis[u] = 1;
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i].first;
				int d = G[u][i].second;
				if (d + dis[u] < dis[v]) {
					dis[v] = d + dis[u];
					Q.push(make_pair(-dis[v], v));
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) dis[i] = -1;
	}
}

int create_st(int l, int r, bool f) {
	int ret;
	if (l == r) ret = l;
	else ret = ++c;
	st[ret].l = l;
	st[ret].r = r;
	if (l != r) {
		int m = (l + r) / 2;
		st[ret].ls = create_st(l, m, f);
		st[ret].rs = create_st(m+1,r,f);
		if (f) {
			add(ret, st[ret].ls, 0);
			add(ret, st[ret].rs, 0);
		} else {
			add(st[ret].ls, ret, 0);
			add(st[ret].rs, ret, 0);
		}
	} else st[ret].ls = st[ret].rs = -1e9;
	return ret;
}

void addedge(int v, int w, int p, int l, int r, bool f) {
	if (l == st[p].l && r == st[p].r) {
		if (f) add(p, v, w);
		else add(v, p, w);
	} else {
		int m = (st[p].l + st[p].r) / 2;
		if (r <= m) addedge(v, w, st[p].ls, l, r, f);
		else if (l > m) addedge(v, w, st[p].rs, l, r, f);
		else addedge(v, w, st[p].ls, l, m, f), addedge(v, w, st[p].rs, m+1, r, f);
	}
}

int main() {
	cin >> n >> q >> s, c = n;
	t1 = create_st(1, n, 1);
	t2 = create_st(1, n, 0);
	while (q--) {
		cin >> o;
		switch (o) {
			case 1: {
				cin >> v >> u >> w;
				add(v, u, w);
				break;
			}
			case 2: {
				cin >> v >> l >> r >> w;
				addedge(v, w, t1, l, r, 0);
				break;
			}
			case 3: {
				cin >> v >> l >> r >> w;
				addedge(v, w, t2, l, r, 1);
				break;
			}
		}
	}
	dijskra();
	for (int i = 1; i <= n; i++) {
		cout << dis[i] << ' ';
	}
	cout << endl;
	return 0;
}
```


---

## 作者：lamboo (赞：2)

### 题解

有一个比较经典的做法是线段树优化建图，时间复杂度约为 $O(n\log^2n)$。也可以使用高级数据结构优化。不过不是本文的重点。

还有一个方法是不用线段树显式建图，直接用线段树维护最短路。分别考虑一下两种操作：

- 点 $u$ 向区间连边：直接在用 $u$ 松弛的时候对该区间取 $\min$ 即可。
- 区间向点 $u$ 连边：注意到一个区间只会被区间内 $dis$ 最小的点松弛，在枚举到区间的点时，直接在线段树上更新点 $u$，然后把该区间删去即可。直接把区间对应到线段树上的结点即可。

对于两个操作分别开线段树维护。

时间复杂度：每个区间只会使用 $1$ 次，每次更新对应的结点 $O(log n)$。总时间复杂度就是 $O(n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>

using ll = long long;
using pli = std::pair<ll, int>;
using pii = std::pair<int, int>;
#define mkp(a, b) std::make_pair(a, b)

const ll inf = 1LL << 60;
const int N = 1e5 + 10;

namespace Fast_IO
{
    const int bufsize = 1 << 22;
    inline char Getchar()
    {
        static char buf[bufsize], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin), p1 == p2) ? EOF : *p1++;
    }

    template<typename T = int> inline T read()
    {
        T x = 0, f = 0; char ch = Getchar();
        while (!isdigit(ch)) f |= ch == '-', ch = Getchar();
        while ( isdigit(ch)) x = x * 10 + ch - '0', ch = Getchar();
        return f ? -x : x;
    }

    char Buf[bufsize], *fout = Buf;
    inline void flush() 
    {
        fwrite(Buf, 1, fout - Buf, stdout), fflush(stdout);
    }

    inline void print(char *s) { while (*s) *fout++ = *s++; }
    inline void print(char c) { *fout++ = c; }

    template<typename T> inline void Write(T u) 
    {
        u > 9 ? Write(u / 10), *fout++ = u % 10 + '0' : *fout++ = u + '0';
    }

    template<typename T> inline void write(T u, char ch = ' ') 
    {
        if (u < 0) print('-'), u = -u; Write(u), print(ch);
    }
}
using namespace Fast_IO;

struct Node {int l, r, w;};
std::vector<Node> vec[N];
int w[N]; ll dis[N];

struct SegmentTree1
{
    static const int M = N << 2;
    int del[M]; ll tag[M]; pli Min[M];
    #define mid ((l + r) >> 1)

    inline void down(int k, ll dat, int d)
    {
        if (d) del[k] = 1, tag[k] = inf + 10, Min[k] = mkp(inf + 10, -1);
        if (del[k]) return;
        Min[k].first = std::min(Min[k].first, dat);
        tag[k] = std::min(tag[k], dat);
    }

    inline void upd(int k)
    {
        del[k] = del[k << 1] & del[k << 1 | 1];
        Min[k] = del[k] ? mkp(inf + 10, -1) : std::min(Min[k << 1], Min[k << 1 | 1]);
    }

    inline void down(int k)
    {
        if (del[k]) return;
        down(k << 1, tag[k], 0), down(k << 1 | 1, tag[k], 0), tag[k] = inf;
    }

    inline void build(int k, int l, int r)
    {
        tag[k] = inf;
        if (l == r) Min[k] = mkp(inf, l), del[k] = 0;
        if (l != r) build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r), upd(k);
    }

    inline void Mod(int k, int l, int r, int ql, int qr, ll dat, int d = 0)
    {
        if (ql >  r || l >  qr) return;
        if (ql <= l && r <= qr) return down(k, dat, d);
        down(k), Mod(k << 1, l, mid, ql, qr, dat, d), Mod(k << 1 | 1 , mid + 1, r, ql, qr, dat, d), upd(k);
    }

    inline int query() {return Min[1].second;}
}T1;
// 区间取min 单点删除 查询全局最小值

struct SegmentTree2
{
    static const int M = N << 2;
    std::vector<pii> vec[M]; int del[M], vis[M];
    #define mid ((l + r) >> 1)

    inline void Add(int k, int l, int r, int ql, int qr, pii dat)
    {
        if (ql >  r || l >  qr) return;
        if (ql <= l && r <= qr) return vec[k].push_back(dat), void();
        Add(k << 1, l, mid, ql, qr, dat), Add(k << 1 | 1, mid + 1, r, ql, qr, dat);
    }

    inline void upd(int k, int l, int r, int p, ll dat, int n)
    {
        for (int i = 0; i < vec[k].size(); ++i)
        {
            int u = vec[k][i].first, idx = vec[k][i].second;
            if (!vis[idx]) T1.Mod(1, 1, n, u, u, (ll)::w[idx] + dat, 0), vis[idx] = true;
        }
        vec[k].clear();
        if (l != r) p <= mid ? upd(k << 1, l, mid, p, dat, n) : upd(k << 1 | 1, mid + 1, r, p, dat, n);
    }
}T2;

int main()
{
    int n = read(), m = read(), s = read();
    for (int i = 1; i <= m; ++i)
    {
        int opt = read(), u = read();
        if (opt == 1) 
        {
            int v = read(), w = read();
            vec[u].push_back(Node{v, v, w});
        }
        if (opt == 2)
        {
            int l = read(), r = read(), w = read();
            vec[u].push_back(Node{l, r, w});
        }
        if (opt == 3)
        {
            int l = read(), r = read(), w = read(); ::w[i] = w;
            T2.Add(1, 1, n, l, r, mkp(u, i));
        }
    }
    memset(dis, 0x3f, sizeof(dis));
    T1.build(1, 1, n), T1.Mod(1, 1, n, s, s, 0), dis[s] = 0;
    while (true)
    {
        pli dat = T1.Min[1]; int u = T1.query(); 
        if (u == -1 || dat.first >= 1e18) break;
        T1.Mod(1, 1, n, u, u, inf + 10, 1);
        T2.upd(1, 1, n, u, dis[u] = dat.first, n);
        for (int i = 0; i < vec[u].size(); ++i)
        {
            int l = vec[u][i].l, r = vec[u][i].r;
            T1.Mod(1, 1, n, l, r, vec[u][i].w + dis[u]);
        }
    }
    for (int i = 1; i <= n; ++i) write(dis[i] >= 1e18 ? -1 : dis[i]);
    return flush(), 0;
}

```



---

## 作者：Night_Bringer (赞：0)

# 前言
[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14771453.html)
# 题意
有 $n$ 个点，$q$ 次连边，以及起点 $s$ 。连边具体分三种：
1. $1$ $v$ $u$ $w$ 从 $v$ 到 $u$ 连一条边。
2. $2$ $v$ $l$ $r$ $w$ 从 $v$ 向 $l$ 到 $r$ 所有点连一条边。
3. $3$ $v$ $l$ $r$ $w$ 从 $l$ 到 $r$ 所有点向 $v$ 连一条边。 

求所有点的最短路。
# 思路
以前做过一道比较类似的题：[T'ill It's Over](https://www.cnblogs.com/C202202chenkelin/p/14612686.html) 都是线段树优化连边。

建立两棵线段树记为 $A$ ， $B$ ，线段树 $A$ 的所有结点向上连结父节点，线段树 $B$ 的所有节点向下连结自己的子节点。

那么操作就可以看成 $A$ 树对应区间连向 $B$ 树对应区间，就转换为普通的线段树区间查询了。

现在需要考虑如何将 $B$ 树的状态转换到 $A$ 树上。

只需要将 $B$ 树的结点连向 $A$ 的对应结点就好了。

由于状态最后都会回归到 $A$ 树中，所以最后查询 $A$ 树中叶子结点区间为 $[i,i](i\in [1,n])$ 的点的最短路径，即为答案。

算法总时间复杂度为 $O(n\log n*log((n+q)\log n))$ ，大概就是 $O(n\log^2n)$ 级别的。
# Code
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
namespace Quick_Function {
	template <typename Temp> void Read(Temp &x) {
		x = 0; char ch = getchar(); bool op = 0;
		while(ch < '0' || ch > '9') { if(ch == '-') op = 1; ch = getchar(); }
		while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
		if(op) x = -x;
	}
	template <typename T, typename... Args> void Read(T &t, Args &... args) { Read(t); Read(args...); }
	template <typename Temp> Temp Max(Temp x, Temp y) { return x > y ? x : y; }
	template <typename Temp> Temp Min(Temp x, Temp y) { return x < y ? x : y; }
	template <typename Temp> Temp Abs(Temp x) { return x < 0 ? (-x) : x; }
	template <typename Temp> void Swap(Temp &x, Temp &y) { x ^= y ^= x ^= y; }
}
using namespace Quick_Function;
#define INF 1e17
#define int long long
const int MAXN = 5e5 + 5;
const int MAXM = 5e6 + 5;
struct Edge { int To, Dist, Next; };
int head[MAXN], edgetot = 1;
Edge edge[MAXM];
void Addedge(int u, int v, int w) { edge[++edgetot].Next = head[u], edge[edgetot].To = v, edge[edgetot].Dist = w, head[u] = edgetot; }
struct Node {
	int id, dis;
	Node() {}
	Node(int I, int D) { id = I, dis = D; }
	friend bool operator < (Node x, Node y) { return x.dis > y.dis; }
};
priority_queue<Node> que;
int dis[MAXN];
bool vis[MAXN];
int n, q, s, p;
struct Segment_Node {
	int l, r, id;
	#define LS(x) (x << 1)
	#define RS(x) (x << 1 | 1)
};
struct Segment_Tree {
	Segment_Node t[MAXN << 2][2];//0为A线段树，1为B线段树
	int tot;
	void Build(int pos, int l, int r, int flag) {//初始化建树
		t[pos][flag].l = l, t[pos][flag].r = r, t[pos][flag].id = ++tot;
		if(l == r) {
			if(l == s && !flag) p = t[pos][flag].id;
			if(flag) Addedge(t[pos][1].id, t[pos][0].id, 0);//这里忘写调了半个小时QAQ
			return;
		}
		int mid = (l + r) >> 1;
		Build(LS(pos), l, mid, flag); Build(RS(pos), mid + 1, r, flag);
		if(!flag) {
			Addedge(t[LS(pos)][flag].id, t[pos][flag].id, 0);
			Addedge(t[RS(pos)][flag].id, t[pos][flag].id, 0);
		}
		else {
			Addedge(t[pos][flag].id, t[LS(pos)][flag].id, 0);
			Addedge(t[pos][flag].id, t[RS(pos)][flag].id, 0);
			Addedge(t[pos][1].id, t[pos][0].id, 0);
		}
	}
	int Query(int pos, int x, int flag) {//查询区间为[x,x]的叶子结点
		if(t[pos][flag].l == t[pos][flag].r) return t[pos][flag].id;
		if(x <= t[LS(pos)][flag].r) return Query(LS(pos), x, flag);
		else return Query(RS(pos), x, flag);
	}
	void Update1(int pos, int l, int r, int x, int w) {//一连多
		if(l <= t[pos][1].l && t[pos][1].r <= r) {
			Addedge(Query(1, x, 0), t[pos][1].id, w);
			return;
		}
		if(l <= t[LS(pos)][1].r) Update1(LS(pos), l, r, x, w);
		if(r >= t[RS(pos)][1].l) Update1(RS(pos), l, r, x, w);
	}
	void Update2(int pos, int l, int r, int x, int w) {//多连一
		if(l <= t[pos][0].l && t[pos][0].r <= r) {
			Addedge(t[pos][0].id, Query(1, x, 1), w);
			return;
		}
		if(l <= t[LS(pos)][0].r) Update2(LS(pos), l, r, x, w);
		if(r >= t[RS(pos)][0].l) Update2(RS(pos), l, r, x, w);
	}
};
Segment_Tree tree;
void Dijkstra() {//最短路
	for(int i = 1; i <= tree.tot; i++) dis[i] = INF;
	que.push(Node(p, 0)); dis[p] = 0;
	while(!que.empty()) {
		int u = que.top().id; que.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i; i = edge[i].Next) {
			int v = edge[i].To;
			if(dis[v] > dis[u] + edge[i].Dist) {
				dis[v] = dis[u] + edge[i].Dist;
				que.push(Node(v, dis[v]));
			}
		}
	}
}
signed main() {
	Read(n, q, s);
	tree.Build(1, 1, n, 0); tree.Build(1, 1, n, 1);
	for(int i = 1, opt, u, v, l, r, w; i <= q; i++) {
		Read(opt, u);
		if(opt == 1) {
			Read(v, w);
			tree.Update1(1, v, v, u, w);
		}
		else if(opt == 2) {
			Read(l, r, w);
			tree.Update1(1, l, r, u, w);
		}
		else {
			Read(l, r, w);
			tree.Update2(1, l, r, u, w);
		}
	}
	Dijkstra();
	for(int i = 1; i <= n; i++) printf("%lld ", dis[tree.Query(1, i, 0)] == INF? -1 : dis[tree.Query(1, i, 0)]);
	return 0;
}
```

---

