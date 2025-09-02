# T'ill It's Over

## 题目背景

小正方形被黑暗之主碾成了粉末。

一切，就这么结束了吗？

就当大家都以为再无翻盘的希望时，

已经被净化的两个世界之树的部分，微微闪烁……

## 题目描述

小正方形被三角的力量复活了，它即将与黑暗之主展开最后的战斗。

小正方形最后的目标，就是净化黑暗之主。

黑暗之主的蜈蚣长度为 $n$，一开始每一节的光明程度为 $1$。

当一节蜈蚣的光明程度达到一个指定的值 ($k$)，我们就视作这节蜈蚣被净化。

为了净化黑暗之主，小正方形准备了 $m$ 种方案，这些方案按本质上的不同大约可分为四种：

1. 将一节光明程度为 $a$ 的蜈蚣的光明程度 变为 $b$。（注意，$b$ 可能 $\le a$）

2. 将一节光明程度在 $a1$ 到 $a2$ 区间的蜈蚣的光明程度变为 $b1$。

3. 将一节光明程度为 $a1$ 的蜈蚣的光明程度变为 $b1$ 到 $b2$ 区间的任意值。

4. 将一节光明程度在 $a1$ 到 $a2$ 区间的蜈蚣的光明程度变为 $b1$ 到 $b2$ 区间的任意值。

由于小正方形使用每种方案需要消耗一定程度的属性能量，因此每种方案都有一个独立的使用次数的上限，在一种方案中我们用 $l$ 来表示这个上限。

小正方形想要知道，自己最多能够净化几节黑暗之主的蜈蚣。

## 说明/提示

首先使用方案 1，2，3，将三节光明程度变为 $3$，接着再变为 $2$，再变为 $5$。

然后使用方案 4，将一节的光明程度变为 $5$。

对于 $10\%$ 的数据，$n = 1,op = 1$。

对于另外 $10\%$ 的数据，$n = 1,op \le 3$。

对于另外 $10\%$ 的数据，$n \le 10,op = 1$。

对于另外 $20\%$ 的数据，$n \le 100,m \le 100,op = 1$。

对于 $70\%$ 的数据，$n  \le 1000,m \le 1000,op \le 3,k \le 20000$。

**对于前 $70\%$ 的数据，时限为 $500$ ms**。

对于 $100\%$ 的数据，$n \le 10^7,m \le 20000,1 \le k \le 10^5,1 \le l \le 10^5$。

**对于后 $30\%$ 的数据，时限为 $8000$ ms**。

**数据保证，操作为随机生成**。

## 样例 #1

### 输入

```
5 4 5
1 3 1 3
1 3 3 2
1 3 2 5
4 1 1 1 4 5```

### 输出

```
4```

# 题解

## 作者：Wen_kr (赞：7)

#### 10 Pts

输出 0 或 n 都能得到十分。

#### 0~20 Pts
```
rand()%2 == 1 output(1)
rand()%2 == 0 output(n)
```
#### 20 Pts

$n = 1$，考虑建出一张图，判断从 1 号点能否到 k 号点即可。

#### 另外 10 Pts

使用网络流，暴力建图，$op = 1$，建立一条从 $a$ 到 $b$ 的边，跑 EK 即可。

#### 另外 20 Pts

考虑方案 2 和 3，建立两个虚拟节点，起点(可能有多个)向其中一个建立流量为无限大的边，另一个向终点(可能有多个)建立流量为无限大的边，然后从虚拟节点一个向另一个建立流量为这个方案使用次数限制的边。然后跑 EK 即可。

#### 70 Pts

使用 Dinic(或其他更加优秀的网络流算法)，其他如另外 20 Pts 的建图方式。

#### 100 Pts

考虑上一个连边方式的瓶颈，就是连接的节点数量为 $n$ 个，这不可以接受。

我们考虑使用线段树优化连边，这样连接的节点数量为 $log(n)$ 个，由于数据随机，Dinic(或其他更加优秀的网络流算法) 可以轻松跑过。

---

## 作者：Gmt丶FFF (赞：6)

网络流是显然的，建超级源点 $s$ 向 $1$ 连边，流量为 $n$，$k$ 向超级汇点连边，流量为 $n$，对于每一个询问，建立一个超级点，将所有符合的点向超级点连边，再用超级点向每个能变成的点连边，由于要满足流量限制，拆点建边，流量为 $l$ 即可。

前三组询问明显都等价于第四组询问，所以只需要处理第四组询问即可，那么区间给区间连边，可以看出是线段树优化建图，第一棵树子节点向父亲建边，第二棵树父亲向子节点建边，流量都为 $inf$，然后第一棵树向询问超级点建边，超级点再向第二棵树建边即可。

然后跑 dinic，看是否满流即可。

复杂度：$O(k^2m\log(k))$（网络流玄学复杂度，反正能过）。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N=1e5+5;
struct node
{
	int to,data,next;
}a[40*N];
struct node2
{
	int ls,rs;
}f[8*N];
queue<int>q;
int cnt,h[8*N],cnp,n,m,k,rt[2],dis[8*N],s,t;
bool vis[8*N];
inline void addedge(int x,int y,int k)
{
//	if(x==18||y==18)
//	cout<<x<<" "<<y<<" "<<k<<endl;
	a[cnt]={y,k,h[x]};
	h[x]=cnt++;
	a[cnt]={x,0,h[y]};
	h[y]=cnt++;
}
inline int ls(int x)
{
	if(!f[x].ls)f[x].ls=++cnp;
	return f[x].ls;
}
inline int rs(int x)
{
	if(!f[x].rs)f[x].rs=++cnp;
	return f[x].rs;
}
void build(int x,int y,int l,int r)
{
	if(l==r)return addedge(y,x,1e9);
	int mid=(l+r)>>1;
	build(ls(x),ls(y),l,mid);
	build(rs(x),rs(y),mid+1,r);
	addedge(f[x].ls,x,1e9);
	addedge(f[x].rs,x,1e9);
	addedge(y,f[y].ls,1e9);
	addedge(y,f[y].rs,1e9);
	addedge(y,x,1e9);
}
void update1(int x,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
	{
		addedge(x,k,1e9);
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=nl)update1(ls(x),l,mid,nl,nr,k);
	if(mid<nr)update1(rs(x),mid+1,r,nl,nr,k);
}
void update2(int x,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
	{
		addedge(k,x,1e9);
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=nl)update2(ls(x),l,mid,nl,nr,k);
	if(mid<nr)update2(rs(x),mid+1,r,nl,nr,k);
}
int search(int x,int l,int r,int nl)
{
	if(l==r)return x;
	int mid=(l+r)>>1;
	if(mid>=nl)return search(ls(x),l,mid,nl);
	return search(rs(x),mid+1,r,nl);
}
bool bfs()
{
	memset(dis,0,sizeof(dis));
	q.push(s);
	dis[s]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=h[x];i!=-1;i=a[i].next)
		{
			if(!a[i].data)continue;
			if(!dis[a[i].to])
			{
				dis[a[i].to]=dis[x]+1;
				q.push(a[i].to);
			}
		}
	}
	return dis[t];
}
int dfs(int x,int num)
{
	if(x==t)return num;
	if(vis[x])return 0;
	vis[x]=1;
	for(int i=h[x];i!=-1;i=a[i].next)
	{
		if(!a[i].data||dis[a[i].to]!=dis[x]+1)continue;
		int res=dfs(a[i].to,min(num,a[i].data));
		if(res)
		{
			a[i].data-=res;
			a[i^1].data+=res;
			return res;
		}
	}
	return 0;
}
int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d%d%d",&n,&m,&k);
	cnp=2;
	build(rt[0]=1,rt[1]=2,1,k);
	for(int i=1;i<=m;i++)
	{
		int opt,sum;
		scanf("%d%d",&opt,&sum);
		int num=++cnp;
		int num2=++cnp;
		addedge(num,num2,sum);
		if(opt==1)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			update1(rt[0],1,k,x,x,num);
			update2(rt[1],1,k,y,y,num2);
		}
		if(opt==2)
		{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			update1(rt[0],1,k,l,r,num);
			update2(rt[1],1,k,x,x,num2);
		}
		if(opt==3)
		{
			int l,r,x;
			scanf("%d%d%d",&x,&l,&r);
			update1(rt[0],1,k,x,x,num);
			update2(rt[1],1,k,l,r,num2);
		}
		if(opt==4)
		{
			int l,r,x,y;
			scanf("%d%d%d%d",&x,&y,&l,&r);
			update1(rt[0],1,k,x,y,num);
			update2(rt[1],1,k,l,r,num2);
		}
	}
	s=++cnp,t=++cnp;
	addedge(s,search(rt[0],1,k,1),n);
	addedge(search(rt[0],1,k,k),t,n);
	int res=0;
//	cout<<s<<" "<<t<<endl;
	while(bfs())
	{
		memset(vis,0,sizeof(vis));
		int num=dfs(s,1e9);
		while(num)memset(vis,0,sizeof(vis)),res+=num,num=dfs(s,1e9);
	}
	printf("%d",res);
	return 0;
}
```


---

## 作者：PurpleWonder (赞：5)

出题人已经把思路说的很清楚了……我就只是发一下丑陋的代码

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
#define s 0
#define t 1000001
#define r(x) ((x<<1)+(k<<2))
#define c(x) ((x<<1|1)+(k<<2))
using namespace std;

int n,m,k,xl,xr,yl,yr,qi,com;
int nxt[4000100],to[4000100],head[1000100],quan[4000100],gs=1;
int l[400010],r[400010],cx,d[400010],d2[400010];
int v[400010],top,ans;
int ju[1000100];
queue<int> q;

inline void lb(int x,int y,int z){
	nxt[++gs]=head[x];
	head[x]=gs;
	to[gs]=y;
	quan[gs]=z;
}
//d存储的是蜈蚣到达的光明程度的大小，d2存储的是蜈蚣出发的光明程度的大小
void build(int x,int li,int ri){
	l[x]=li;r[x]=ri;d[x]=++cx;
	if(li!=ri)d2[x]=++cx;
	else d2[x]=d[x];
	if(li==ri){
		if(li==1)lb(s,d[x],n),lb(d[x],s,0);
		if(li==k)lb(d[x],t,n),lb(t,d[x],0);
		return;
	}
	int mid=(li+ri)>>1;
	build(x<<1,li,mid);build(x<<1|1,mid+1,ri);
    //向自己的叶子节点连边
	lb(d[x],d[x<<1],0x3f3f3f3f);lb(d[x<<1],d[x],0);
	lb(d[x],d[x<<1|1],0x3f3f3f3f);lb(d[x<<1|1],d[x],0);
	lb(d2[x<<1],d2[x],0x3f3f3f3f);lb(d2[x],d2[x<<1],0);
	lb(d2[x<<1|1],d2[x],0x3f3f3f3f);lb(d2[x],d2[x<<1|1],0);
}

void query(int x,int li,int ri,int *ar){
	if(l[x]>ri || r[x]<li)return;
	if(l[x]>=li && r[x]<=ri){
		v[++top]=ar[x];return;
	}
	query(x<<1,li,ri,ar);query(x<<1|1,li,ri,ar);
}
//dicnic网络流
int bfs(){
	memset(ju,0,sizeof(ju));
	q.push(s);
	ju[s]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if(!ju[to[i]] && quan[i]){
				ju[to[i]]=ju[x]+1;
				q.push(to[i]);
			}
		}
	}
	return ju[t];
}

int dfs(int x,int di){
	if(x==t)return di;
	int si=0;
	for(int i=head[x];i;i=nxt[i]){
		if(si<di && quan[i] && ju[to[i]]-ju[x]==1){
			int li=dfs(to[i],min(di-si,quan[i]));
			si+=li;
			quan[i]-=li;
			quan[i^1]+=li;
		}
	}
	if(!si)ju[x]=0;
	return si;
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	build(1,1,k);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&com,&qi);
		int ci=++cx,ri=++cx;
		lb(ri,ci,qi);lb(ci,ri,0);
		switch(com){
        //分类讨论几种情况，其实本质上是差不多的，写好第一个之后复制粘贴即可
        //注意的点就是需要把输入的大小和k取较小值，因为线段树只开到了k
			case 1:{
				scanf("%d %d",&xl,&yl);xl=min(xl,k);yl=min(yl,k);
				query(1,xl,xl,d2);
				while(top)lb(v[top],ri,0x3f3f3f3f),lb(ri,v[top--],0);
				query(1,yl,yl,d);
				while(top)lb(ci,v[top],0x3f3f3f3f),lb(v[top--],ci,0);
				break;
			}
			case 2:{
				scanf("%d %d %d",&xl,&xr,&yl);xl=min(xl,k);yl=min(yl,k);xr=min(xr,k);
				query(1,xl,xr,d2);
				while(top)lb(v[top],ri,0x3f3f3f3f),lb(ri,v[top--],0);
				query(1,yl,yl,d);
				while(top)lb(ci,v[top],0x3f3f3f3f),lb(v[top--],ci,0);
				break;
			}
			case 3:{
				scanf("%d %d %d",&xl,&yl,&yr);xl=min(xl,k);yl=min(yl,k);yr=min(yr,k);
				query(1,xl,xl,d2);
				while(top)lb(v[top],ri,0x3f3f3f3f),lb(ri,v[top--],0);
				query(1,yl,yr,d);
				while(top)lb(ci,v[top],0x3f3f3f3f),lb(v[top--],ci,0);
				break;
			}
			case 4:{
				scanf("%d %d %d %d",&xl,&xr,&yl,&yr);xl=min(xl,k);xr=min(xr,k);yl=min(yl,k);yr=min(yr,k);
				query(1,xl,xr,d2);
				while(top)lb(v[top],ri,0x3f3f3f3f),lb(ri,v[top--],0);
				query(1,yl,yr,d);
				while(top)lb(ci,v[top],0x3f3f3f3f),lb(v[top--],ci,0);
				break;
			}
		}
	}
	while(bfs()){
		ans+=dfs(s,0x7fffffff);
	}
	printf("%d",ans);
}
```

---

## 作者：GKxx (赞：2)

线段树优化连边+网络流模板题。

考虑一张$k$个结点的图。操作1直接连边，操作2、3就枚举区间的每个点连边，操作4就分别枚举两个区间的点连边，以上边的容量都设为相应的$l$。然后源点向$1$连边，$k$向汇点连边，容量都为$n$，跑最大流即可。

这个复杂度肯定不行，显然可以用线段树优化连边。

开两棵线段树$T_1,T_2$，$T_1$体现外部结点连入区间，$T_2$体现区间连出到外部结点。$T_1$内部从上往下连边，$T_2$内部从下往上连边。注意两棵树的叶子节点应该共用。

我们可以将这4种连边都统一为区间$[l_1,r_1]$向区间$[l_2,r_2]$连边，单个点也可以看做左右端点相等的区间。我们新建两个点$u,v$，从$u$向$v$连边容量为$l$，然后在$T_2$上从区间$[l_1,r_1]$向$u$连边，在$T_1$上从$v$向区间$[l_2,r_2]$连边，这些边容量都是$\infty$。

然后跑最大流即可。

最近做了好几道这种线段树优化建图的题了，比如十二省联考2019字符串问题，SNOI2019通信

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

const int maxv = 1e6 + 7, maxe = 2e6 + 7, inf = INT_MAX;

struct Network {
    int v[maxe << 1], cap[maxe << 1], flow[maxe << 1], next[maxe << 1], tot;
    int head[maxv], curr[maxv], height[maxv];
    int s, t, V;
    Network() : tot(-1) {}
    void addedge(int x, int y, int c) {
        v[++tot] = y; cap[tot] = c; next[tot] = head[x]; head[x] = tot;
        v[++tot] = x; cap[tot] = 0; next[tot] = head[y]; head[y] = tot;
    }
    bool bfs() {
        static int q[maxv] = {0};
        int l = 0, r = 1;
        for (int i = 1; i <= V; ++i) height[i] = 0;
        height[q[1] = s] = 1;
        while (l < r) {
            int x = q[++l];
            for (int i = head[x]; ~i; i = next[i])
                if (cap[i] > flow[i] && !height[v[i]])
                    height[q[++r] = v[i]] = height[x] + 1;
        }
        return height[t];
    }
    int dfs(int x, int cf) {
        if (x == t || !cf) return cf;
        int getf = 0;
        for (int i = curr[x]; ~i; i = next[i], curr[x] = i)
            if (cap[i] > flow[i] && height[v[i]] == height[x] + 1) {
                int nf = dfs(v[i], std::min(cap[i] - flow[i], cf));
                if (nf) {
                    flow[i] += nf; flow[i ^ 1] -= nf; getf += nf;
                    if (!(cf -= nf)) break;
                }
            }
        return getf;
    }
    int maxflow() {
        int ans = 0;
        while (bfs()) {
            for (int i = 1; i <= V; ++i) curr[i] = head[i];
            ans += dfs(s, inf);
        }
        return ans;
    }
};
Network G;

struct Node {
    int lc, rc;
    Node() : lc(0), rc(0) {}
};
Node T[maxv];
int tot, root1, root2;
int n, m, K, s, t;

inline int newNode() { G.head[++tot] = -1; return tot; }

void build(int &o1, int &o2, int l, int r) {
    o1 = newNode();
    o2 = l == r ? o1 : newNode();
    if (l == r) {
        if (l == 1) G.addedge(s, o1, n);
        if (l == K) G.addedge(o1, t, n);
        return;
    }
    int mid = (l + r) >> 1;
    build(T[o1].lc, T[o2].lc, l, mid);
    build(T[o1].rc, T[o2].rc, mid + 1, r);
    G.addedge(o1, T[o1].lc, inf);
    G.addedge(o1, T[o1].rc, inf);
    G.addedge(T[o2].lc, o2, inf);
    G.addedge(T[o2].rc, o2, inf);
}
void link(int o, int lb, int rb, int l, int r, int u, int d) {
    if (!o || l > rb || r < lb) return;
    if (l <= lb && r >= rb) {
        if (d == 1) G.addedge(u, o, inf);
        else G.addedge(o, u, inf);
        return;
    }
    int mid = (lb + rb) >> 1;
    link(T[o].lc, lb, mid, l, r, u, d);
    link(T[o].rc, mid + 1, rb, l, r, u, d);
}

int main() {
    read(n, m, K);
    s = newNode(); t = newNode();
    G.s = s; G.t = t;
    build(root1, root2, 1, K);
    for (int i = 1; i <= m; ++i) {
        int op, lim; read(op, lim);
        int from = newNode(), to = newNode();
        G.addedge(from, to, lim);
        int l1, r1, l2, r2;
        if (op == 1) {
            read(l1, l2);
            r1 = l1; r2 = l2;
        } else if (op == 2) {
            read(l1, r1, l2);
            r2 = l2;
        } else if (op == 3) {
            read(l1, l2, r2);
            r1 = l1;
        } else read(l1, r1, l2, r2);
        link(root1, 1, K, l2, r2, to, 1);
        link(root2, 1, K, l1, r1, from, 2);
    }
    G.V = tot;
    writeln(G.maxflow());
    return 0;
}
```


---

## 作者：OldDriverTree (赞：1)

唐氏题，不到半个小时就切出来了。

# Solution

对于前三个操作显然都可以归约为最后一个，所以这里只考虑最后一个操作。

先考虑暴力应该怎么做，考虑最大流，一开始先把源点向 $1$ 连一条容量为 $s$ 的边，$k$ 向汇点连一条容量为 $s$ 的边。接下来考虑每种操作怎么做，这里由于限制了使用次数上限 $l$，这个东西显然要放到边的容量上，所以对于一个操作新建两个点 $a$ 和 $b$，将区间 $[a1,a2]$ 内的点都向 $a$ 连边，容量都为 $+\infty$，再将 $b$ 都向区间 $[b1,b2]$ 内的点连边，容量同样也都为 $+\infty$，最后再将 $a$ 向 $b$ 连边，容量为 $l$，最后跑一遍最大流就能得到答案。

直接这样做边数显然会爆炸，由于连边都是一个区间中的所有点都和一个点连边，所以直接上线段树优化建图即可，点数为 $O(m+k)$，边数为 $O(k+m\log k)$，由于最大流跑不满，所以能过。
# Code
```
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
#define in first
#define out second
#define v to[i]
#define f val[i]
using namespace std;
//using namespace atcoder;
const int N=1e5+1,V=5e5,E=1e7;
int n,m,s,cnt,S,T,dep[V],cur[V];
int tot,head[V],nxt[E],to[E],val[E];
P ODT[V];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
void add(int x,int y,int z) {
	to[tot]=y,val[tot]=z,nxt[tot]=head[x],head[x]=tot++;
	to[tot]=x,val[tot]=0,nxt[tot]=head[y],head[y]=tot++;
}
bool bfs()
{
	memset(dep,0,sizeof dep);
	queue<int> q; q.push(S);
	dep[S]=1,cur[S]=head[S];
	while (!q.empty() ) {
		int u=q.front(); q.pop(); for (int i=head[u];~i;i=nxt[i]) if (f&&!dep[v])
		{ dep[v]=dep[u]+1,cur[v]=head[v],q.push(v); if (v==T) return true; }
	}
	return false;
}
int dfs(int u,int limit)
{
	if (u==T) return limit; int flow=0;
	for (int i=cur[u];~i&&flow<limit;i=nxt[i])
	{
		cur[u]=i;
		if (f&&dep[u]+1==dep[v]) {
			int t=dfs(v,min(limit-flow,f) );
			val[i]-=t,val[i^1]+=t,flow+=t;
			if (!t) dep[v]=0;
		}
	}
	return flow;
}
void build(int rt,int l,int r) {
	if (l==r) return ODT[rt].in=ODT[rt].out=l,void();
	ODT[rt].in=++cnt,ODT[rt].out=++cnt,build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
	add(ODT[rt].in,ODT[rt<<1].in,INT_MAX),add(ODT[rt].in,ODT[rt<<1|1].in,INT_MAX);
	add(ODT[rt<<1].out,ODT[rt].out,INT_MAX),add(ODT[rt<<1|1].out,ODT[rt].out,INT_MAX);
}
void change(int rt,int l,int r,int s,int t,int x) {
	if (s<=l&&r<=t) return add(x,ODT[rt].in,INT_MAX);
	if (s<=mid) change(rt<<1,l,mid,s,t,x);
	if (mid<t) change(rt<<1|1,mid+1,r,s,t,x);
}
void Change(int rt,int l,int r,int s,int t,int x) {
	if (s<=l&&r<=t) return add(ODT[rt].out,x,INT_MAX);
	if (s<=mid) Change(rt<<1,l,mid,s,t,x);
	if (mid<t) Change(rt<<1|1,mid+1,r,s,t,x);
}
main()
{
	s=read(),m=read(),n=cnt=read();
	memset(head,-1,sizeof head),build(1,1,n);
	S=++cnt,T=++cnt,add(S,1,s),add(n,T,s);
	while (m--) {
		int o=read(),w=read(),x,y,l,r,a,b;
		if (o==1) x=y=read(),l=r=read();
		else if (o==2) x=read(),y=read(),l=r=read();
		else if (o==3) x=y=read(),l=read(),r=read();
		else if (o==4) x=read(),y=read(),l=read(),r=read();
		Change(1,1,n,x,y,a=++cnt),change(1,1,n,l,r,b=++cnt),add(a,b,w);
	}
	int flow=0;
	while (bfs() ) flow+=dfs(S,INT_MAX);
	return !printf("%lld",flow);
}
```

---

## 作者：ForgotDream_CHN (赞：1)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17608132.html)

> 一个序列 $d\{n\} = \{1\}$，有 $m$ 种操作，每种操作都有一个操作次数的最大限制，且可以分为 $4$ 类：  
	1. 将任意一个满足 $d_i = a$ 的 $d_i$ 改为 $b$；  
	2. 将任意一个满足 $d_i \in [a1, a2]$ 的 $d_i$ 改为 $b$；  
	3. 将任意一个满足 $d_i = a$ 的 $d_i$ 改为 $[b1, b2]$ 中的一个数；  
	4. 将任意一个满足 $d_i \in [a1, a2]$ 的 $d_i$ 改为 $[b1, b2]$ 中的一个数。  
    
> 求最后序列中最多有多少个值为 $k$ 的数。  
$n \le 10^7, k \le 2 \times 10^4, m \le 10^5$。

不难看出这是一道网络流的题目，我们先考虑暴力。记源汇点分别为 $s, t$，对于题目的每一种限制，我们直接暴力连边，容量为对应的限制，再连边 $(s, 1, n)$ 与 $(k, t, n)$，求从 $s$ 到 $t$ 的最大流即可。

真的是这样吗？其实不是，观察可以发现，题目要求的是**总的次数不超过限制**，而如果直接连边则是**对于每一对 $a, b$ 均不超过限制**，而这是不对的，还有可能有多的~~但是题目数据太水了，这一点好像没有怎么体现~~。因此，对于每一个操作都应该新建两个虚拟节点 $l$ 与 $r$，对于所有的 $a$，连边 $(a, l, \inf)$，对于所有的 $b$，连边 $(r, b, \inf)$，再连边 $(l, r, lim)$ 即可，其中 $lim$ 为这种操作的限制次数。这样总体的点数为 $\mathcal{O}(k)$ 的，而总边数达到了惊人的 $\mathcal{O}(mk ^ 2)$，这显然是不行的。

观察到题目给出的形式是点向点连边、区间向区间连边、点与区间互相连边，非常符合线段树优化建图的形式，于是我们直接套一个线段树优化建图的板子，就可以将点数与边数均优化至 $\mathcal{O}(k \log k)$ 级别。

具体在实现时，我们队线段树上的每一个区间都赋予一个标号，然后在连边时，通过在线段树上 DFS，找出所有有用的区间标号并将其存储至一个栈里，然后再连边即可。

```cpp
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50, inf = 0x3f3f3f3f, M = 1e6 + 50;
int n, m, k, cnt;
template<int N = 1000050, int M = 3000050>
struct Dinic {
  static const int inf = 0x3f3f3f3f;
  struct Edge {
    int u, v, cap, flow;
    Edge() = default;
    Edge(int _u, int _v, int _c) { u = _u, v = _v, cap = _c, flow = 0; }
  } edges[M];
  int cnt = 0;
  std::vector<int> adj[N];
  int s, t, dis[N], cur[N];
  void add(int u, int v, int cap) {
    edges[cnt++] = Edge(u, v, cap), edges[cnt++] = Edge(v, u, 0);
    adj[u].push_back(cnt - 2), adj[v].push_back(cnt - 1);
  }
  bool bfs() {
    std::memset(cur, 0, sizeof(cur));
    std::memset(dis, 0x3f, sizeof(dis));
    std::queue<int> q;
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (dis[v] == inf && cap > flow) dis[v] = dis[u] + 1, q.push(v);
      }
    }
    return dis[t] != inf;
  }
  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;
    int res = 0;
    for (int &i = cur[u], f; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      if (dis[v] == dis[u] + 1 && (f = dfs(v, std::min(lim, cap - flow)))) {
        res += f, lim -= f;
        flow += f, edges[adj[u][i] ^ 1].flow -= f;
        if (!lim) break;
      }
    }
    return res;
  }
  int maxFlow(int _s, int _t) {
    int res = 0;
    s = _s, t = _t;
    while (bfs()) res += dfs(s, inf);
    return res;
  }
};
Dinic solver;
int idx[M], rev[M];
void build(int s, int t, int u) {
  idx[u] = ++cnt, rev[u] = ++cnt;
  if (s == t) {
    solver.add(idx[u], rev[u], inf), solver.add(rev[u], idx[u], inf);
    return;
  }
  int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
  build(s, mid, lc), build(mid + 1, t, rc);
  solver.add(idx[u], idx[lc], inf), solver.add(idx[u], idx[rc], inf);
  solver.add(rev[lc], rev[u], inf), solver.add(rev[rc], rev[u], inf);
}
int st[N], top;
void find(int l, int r, int s, int t, int u) {
  if (l <= s && t <= r) {
    st[++top] = u;
    return;
  }
  int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
  if (mid >= l) find(l, r, s, mid, lc);
  if (mid <  r) find(l, r, mid + 1, t, rc);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> k;
  build(1, k, 1);
  for (int i = 1; i <= m; i++) {
    int opt, lim;
    std::cin >> opt >> lim;
    int ts = ++cnt, tt = ++cnt;
    solver.add(ts, tt, lim);
    if (opt == 1) {
      int a, b;
      std::cin >> a >> b;
      find(a, a, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b, b, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    } else if (opt == 2) {
      int a1, a2, b;
      std::cin >> a1 >> a2 >> b;
      find(a1, a2, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b, b, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    } else if (opt == 3) {
      int a, b1, b2;
      std::cin >> a >> b1 >> b2;
      find(a, a, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b1, b2, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    } else {
      int a1, a2, b1, b2;
      std::cin >> a1 >> a2 >> b1 >> b2;
      find(a1, a2, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b1, b2, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    }
  }
  int s = ++cnt, t = ++cnt;
  find(1, 1, 1, k, 1);
  int p1 = st[top];
  top = 0;
  find(k, k, 1, k, 1);
  int pk = st[top];
  top = 0;
  solver.add(s, rev[p1], n), solver.add(idx[pk], t, n);
  std::cout << solver.maxFlow(s, t) << "\n";
  return 0;
}
```

---

## 作者：2018LZY (赞：1)

> 给你n个1,你需要尽可能多地把他们变为k.
>
> 有m种操作,每种操作都有一个限定次数.
>
> 操作有4种类型:
>
> 1. $x ~y$ 把一个x变为y
> 2. $x ~y~ a$ 把一个$[x,y]$内的数变为a
> 3. $x~ a ~b$把一个x变为$[a,b]$中的一个数.
> 4. $x ~y~ a~ b$把一个$[x,y]$内的数变为$[a,b]$内的一个数.

我们可以把4中类型划归为第4种:$[x,y]->[a,b]$.

然后考虑线段树优化建边.

线段树分两棵,代表入树和出树.

对于入树,线段树儿子向父亲连有向边.

对于出树,父亲向儿子连边.


我们先把他们对应的线段树节点找到,然后对于入,我们把节点连向一个新节点$left$,对于出,我们用新节点$right$连向对应线段树节点.(这样我们就可以用$\log$的空间完成一次连接)

最后连$(left,right,limit)$,表示限制次数.

又因为一个数可能有多次操作,所以出树的叶子结点应该连回入树的对应节点.


小细节:对于$[1,n]$的线段树查区间的话,对应的线段树节点**准确**来讲是$2\log n$的,所以空间要注意一下.

```cpp
#include<bits/stdc++.h>
#define gc getchar()
using namespace std;
const int N=4e5+10,M=N*8,inf=2e9;
template<class o>void qr(o&x) {
	char c=gc;int f=1;x=0;
	while(!isdigit(c)){if(c=='-')f=-1;c=gc;}
	while(isdigit(c))x=x*10+c-'0',c=gc;
	x*=f;
}
template<class o>void qw(o x) {
	if(x/10)qw(x/10);
	putchar(x%10+'0');
}
template<class o> void pr1(o x) {
	if(x<0)x=-x,putchar('-');
	qw(x); putchar(' ');
}
template<class o>void pr2(o x) {
	if(x<0)x=-x,putchar('-');
	qw(x);puts("");
}

int n,m,kk,st,ed,d[N],ans;

//Dicnic
struct edge{int y,next,c;}a[M]; int len=1,last[N],cur[N];
void ins(int x,int y,int z) {a[++len]=(edge){y,last[x],z}; last[x]=len;}
void add(int x,int y,int z) {ins(x,y,z); ins(y,x,0);}

bool bfs() {
	memset(d,0,sizeof d); 
	static int q[N],l,r;
	q[l=r=1]=st; d[st]=1;
	memcpy(cur,last,sizeof cur);
	while(l<=r) {
		int x=q[l++];
		for(int k=last[x],y;k;k=a[k].next)
			if(!d[y=a[k].y]&&a[k].c) {
				d[y]=d[x]+1;
				q[++r]=y;
			}
	}
	return d[ed];
}

int dfs(int x,int f) {
	if(x==ed) return f;
	int s=0,t;
	for(int &k=cur[x],y,z;k;k=a[k].next) {
		y=a[k].y; z=a[k].c;
		if(z>0&&d[y]==d[x]+1) {
			s+=t=dfs(y,min(f-s,z));
			a[k].c-=t; a[k^1].c+=t;
			if(s==f) return f;
		}
	}
	if(!s) d[x]=0;
	return s;
}

int dicnic() {
	int s=0;
	while(bfs())
		s+=dfs(st,inf);
	return s;
}

//Disc/Queries
struct rec {
	int op,lim,x,y,a,b;
} q[N];
int val[N],num;
void disc() {
	sort(val+1,val+num+1);
	num=unique(val+1,val+num+1)-(val+1);
}
int find(int x) {return lower_bound(val+1,val+num+1,x)-val;}

//Segment Tree
int cnt;
struct Segment_Tree {
	int son[2][N],root,id[N];
	#define lc son[0][x]
	#define rc son[1][x]
	void bt(int &x,int l,int r,int op) {
		x=++cnt;
		if(l==r) {id[l]=x; return ;}
		int mid=(l+r)/2;
		bt(lc,l,mid,op);
		bt(rc,mid+1,r,op);
		if(op==1) add(lc,x,inf),add(rc,x,inf);
		else add(x,lc,inf),add(x,rc,inf);
	}
	int sta[44],top;
	void ask(int x,int l,int r,int L,int R) {
		if(L<=l&&r<=R) {sta[++top]=x; return ;}
		int mid=(l+r)>>1;
		if(L<=mid) ask(lc,l,mid,L,R);
		if(mid< R) ask(rc,mid+1,r,L,R);
	}
	void Find(int L,int R) {top=0;ask(root,1,num,L,R);}
} in,out;//入树,出树.

int main() {
	qr(n); qr(m); qr(kk); if(kk==1) {pr2(n); return 0;}
	for(int i=1;i<=m;i++) {
		qr(q[i].op); qr(q[i].lim);
		switch(q[i].op) {
			case 1:qr(q[i].x); qr(q[i].a); break;
			case 2:qr(q[i].x); qr(q[i].y); qr(q[i].a); break;
			case 3:qr(q[i].x); qr(q[i].a); qr(q[i].b); break;
			case 4:qr(q[i].x); qr(q[i].y); qr(q[i].a); qr(q[i].b); break;
		}
		val[++num]=q[i].x;
		val[++num]=q[i].y; 
		val[++num]=q[i].a;
		val[++num]=q[i].b;
	}
	val[++num]=1; val[++num]=kk; disc();
	in.bt(in.root,1,num,1);
	out.bt(out.root,1,num,2);
	st=in.id[find(1)]; add(out.id[find(kk)],ed=++cnt,n);
	for(int i=1;i<=num;i++) add(out.id[i],in.id[i],inf);
	for(int i=1;i<=m;i++) {
		int op=q[i].op,t=q[i].lim,x=find(q[i].x),y=q[i].y,l=find(q[i].a),r=q[i].b,left,right;
		if(op==1) add(in.id[x],out.id[l],t);
		else if(op==3) {
			out.Find(l,find(r));
			right=++cnt;
			add(in.id[x],right,t);
			for(int j=1;j<=out.top;j++) add(right,out.sta[j],t);
		}
		else if(op==2) {
			in.Find(x,find(y));
			left=++cnt;
			add(left,out.id[l],t);
			for(int j=1;j<=in.top;j++) add(in.sta[j],left,t);
		}
		else {
			left=++cnt; right=++cnt;
			in.Find(x,find(y));
			out.Find(l,find(r));
			for(int j=1;j<=in.top;j++) add(in.sta[j],left,t);
			for(int j=1;j<=out.top;j++) add(right,out.sta[j],t);
			add(left,right,t);
		}
	}
	pr2(dicnic());
	return 0;
}


```


---

## 作者：win114514 (赞：0)

### 思路

考虑最大流。

线段树优化网络流板子题。

容易发现原题是网络流形式。

套一个线段树优化建图即可。

具体的。

我们可以建出两颗线段树。

在第一颗线段树中，连 $(L_p,p,inf),(R_p,p,inf)$。

在第二颗线段树中，连 $(p,L_p,inf),(p,R_p,inf)$。

另外在叶子节点处，连 $(p_2,p_1,inf)$。

发现所有的操作都被操作 $4$ 包含。

我们可以建两个虚拟节点 $x,y$，连 $(x,y,l)$。

把第一个线段树的对应区间连向 $x$。

把 $y$ 连向第二个线段树的对应区间。

最后，在第一颗线段树上，连 $(s,1,n),(k,t,n)$，其中 $1,t$ 分别代表对应的叶子节点。

### Code

```cpp
/*
  ! 如果没有天赋，那就一直重复
  ! Created: 2024/06/03 15:10:11
*/
#include <bits/stdc++.h>
using namespace std;

#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

struct NetWork {
  using i64 = long long;
  struct edge { int to, nxt; i64 v; };
  int ct, n, s, t; i64 mf;
  vector<edge> e;
  vector<int> dp, gp, cr, hd;
  inline NetWork(int N) {
    n = N, ct = 1;
    dp.resize(N + 5), gp.resize(N + 5);
    cr.resize(N + 5), hd.resize(N + 5);
    e.push_back({}), e.push_back({});
  }
  inline void add(int x, int y, int z) {
    e.push_back({y, hd[x], z}), hd[x] = ++ct;
    e.push_back({x, hd[y], 0}), hd[y] = ++ct;
  }
  inline void bfs() {
    queue<int> q;
    fill(dp.begin(), dp.end(), 0);
    fill(gp.begin(), gp.end(), 0);
    q.push(t), gp[dp[t] = 1] = 1;
    while (q.empty() == 0) {
      int x = q.front(); q.pop();
      for (int i = hd[x]; i; i = e[i].nxt) {
        if (!dp[e[i].to]) {
          gp[dp[e[i].to] = dp[x] + 1]++;
          q.push(e[i].to);
        }
      }
    }
  }
  inline i64 dfs(int now, i64 flow) {
    if (now == t) return mf += flow, flow;
    i64 used = 0;
    for (int&i = cr[now]; i; i = e[i].nxt) {
      if (dp[e[i].to] + 1 == dp[now] && e[i].v) {
        int x = dfs(e[i].to, min(e[i].v, flow - used));
        e[i].v -= x, e[i ^ 1].v += x, used += x;
        if (used == flow) return used;
      }
    }
    if (--gp[dp[now]] == 0) dp[s] = n + 1;
    return gp[++dp[now]]++, used;
  }
  inline i64 isap(int S, int T) {
    s = S, t = T, mf = 0, bfs();
    while (dp[s] <= n) copy(hd.begin(), hd.end(), cr.begin()), dfs(s, 1e18);
    return mf;
  }
};

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  
  int n, m, k, s, t, ct = 0;

  cin >> n >> m >> k;
  
  vector<int> d1(2 * k);
  vector<int> d2(2 * k);

  NetWork sol(4 * k + 2 * m);

  auto build = [&](int p, int l, int r, auto build) -> void {
    d1[p] = ++ct, d2[p] = ++ct;
    if (l == r) {
      sol.add(d2[p], d1[p], 1e9);
      if (l == 1) s = ++ct, sol.add(s, d1[p], n);
      if (l == k) t = ++ct, sol.add(d1[p], t, n);
      return;
    }
    int mid = (l + r) >> 1;
    build(mid<<1, l, mid, build);
    build(mid<<1|1, mid + 1, r, build);
    sol.add(d1[mid<<1], d1[p], 1e9);
    sol.add(d1[mid<<1|1], d1[p], 1e9);
    sol.add(d2[p], d2[mid<<1], 1e9);
    sol.add(d2[p], d2[mid<<1|1], 1e9);
  };
  auto upd = [&](int p, int l, int r, int L, int R, int k, int op, auto upd) -> void {
    if (L <= l && r <= R) {
      if (op == 0) sol.add(d1[p], k, 1e9);
      if (op == 1) sol.add(k, d2[p], 1e9);
      return;
    }
    int mid = (l + r) >> 1;
    if (mid >= L) upd(mid<<1, l, mid, L, R, k, op, upd);
    if (mid <  R) upd(mid<<1|1, mid + 1, r, L, R, k, op, upd);
  };

  build(1, 1, k, build);
  fro(i, 1, m) {
    int op, l, a1, a2, b1, b2, x, y;
    cin >> op >> l, sol.add(x = ++ct, y = ++ct, l);
    if (op == 1) cin >> a1 >> b1, a2 = a1, b2 = b1;
    if (op == 2) cin >> a1 >> a2 >> b1, b2 = b1;
    if (op == 3) cin >> a1 >> b1 >> b2, a2 = a1;
    if (op == 4) cin >> a1 >> a2 >> b1 >> b2;
    upd(1, 1, k, a1, a2, x, 0, upd);
    upd(1, 1, k, b1, b2, y, 1, upd);
  }
  cout << sol.isap(s, t) << "\n";

  return 0;
}
```

---

## 作者：simonG (赞：0)

题意：有 $m$ 个操作，可以将一定区间内的数变成另一区间里任意数，有限制操作次数。有几个数，初始值为 $1$，问最多使多少个数变为 $t$。

考虑最大流，源点为 $1$，汇点为 $k$。

设某一操作，可以将 $[a1,a2]$ 的数变成 $[b1,b2]$ 的数。

我们考虑建模。操作的话就是将 $[a1,a2]$ 数都向 $[b1,b2]$ 里建一条容量为限制操作次数的边。

那么最大流就是能有多少个数能变成 $t$。

每个依此建边是不行的。

我们模仿 [P6348 [PA2011]Journeys](https://www.luogu.com.cn/problem/P6348) 一题，考虑 DS 优化建图即可，这里用线段树。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10,M=4e6+10,K=1e5+10;
const int inf=1061109567;
struct flow {
	int n,head[N],nxt[M],ver[M],limit[M],tot=1;
	void add(int u,int v,int w) {
		ver[++tot]=v; nxt[tot]=head[u]; head[u]=tot; limit[tot]=w;
		ver[++tot]=u; nxt[tot]=head[v]; head[v]=tot; limit[tot]=0;
	}
	int T,cur[N],dis[N];
	int dfs(int u,int res) {
		if(u==T) return res;
		int flow=0;
		for(int i=cur[u]; i&&res; i=nxt[i]) {
			cur[u]=i;
			int c=min(res,limit[i]),v=ver[i];
			if(dis[u]+1==dis[v]&&c) {
				int k=dfs(v,c);
				flow+=k; res-=k;
				limit[i]-=k; limit[i^1]+=k;
			}
		}
		if(!flow) dis[u]=-1;
		return flow;
	}
	int maxflow(int s,int t) {
		T=t;
		int flow=0;
		for(; ; ) {
			memcpy(cur,head,sizeof head);
			memset(dis,-1,sizeof dis);
			queue<int> Q;
			Q.push(s); dis[s]=0;
			for(; Q.size(); ) {
				int u=Q.front(); Q.pop();
				for(int i=head[u],v; i; i=nxt[i])
					if(dis[v=ver[i]]==-1&&limit[i])
						dis[v]=dis[u]+1,Q.push(v);
			}
			if(dis[t]==-1) return flow;
			flow+=dfs(s,inf);
		}
	}
} g;
int n,m,k;
int tot,ls[N],rs[N],rt1,rt2;
void build(int &p1,int &p2,int l,int r) {
	if(l==r) return p1=l,p2=l,void();
	if(!p1) p1=++tot;
	if(!p2) p2=++tot;
	int mid=(l+r)/2;
	build(ls[p1],ls[p2],l,mid); g.add(ls[p1],p1,inf); g.add(p2,ls[p2],inf);
	build(rs[p1],rs[p2],mid+1,r); g.add(rs[p1],p1,inf); g.add(p2,rs[p2],inf);
}
void Add(int p,int l,int r,int x,int y,int z,int flag) {
	if(x<=l&&r<=y) {
		if(flag) g.add(p,z,inf);
		else g.add(z,p,inf);
		return ;
	}
	int mid=(l+r)/2;
	if(x<=mid) Add(ls[p],l,mid,x,y,z,flag);
	if(y>mid) Add(rs[p],mid+1,r,x,y,z,flag);
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	tot=k;
	build(rt1,rt2,1,k);
	for(int i=1,op,l,a1,a2,b1,b2; i<=m; i++) {
		scanf("%d%d",&op,&l);
		if(op==1) {
			scanf("%d%d",&a1,&b1);
			a2=a1,b2=b1;
		} else if(op==2) {
			scanf("%d%d%d",&a1,&a2,&b1);
			b2=b1;
		} else if(op==3) {
			scanf("%d%d%d",&a1,&b1,&b2);
			a2=a1; 
		} else if(op==4) {
			scanf("%d%d%d%d",&a1,&a2,&b1,&b2);
		}
		int z1=++tot,z2=++tot;
		Add(rt1,1,k,a1,a2,z1,1);
		Add(rt2,1,k,b1,b2,z2,0);
		g.add(z1,z2,l);
	}
	int ans=g.maxflow(1,k);
	printf("%d\n",ans>n?n:ans);
	return 0;
}
```

---

## 作者：AIskeleton (赞：0)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16313133.html)

> [P5029 T'ill It's Over](https://www.luogu.com.cn/problem/P5029)

> 给定 $n$ 个 1，用要求的操作使得其中尽可能多的数变成 $k$。
> $m$ 个不同操作，其中每个操作有限定次数 $l$。
> 操作分为四种类型：
> 1. 给出 $a,b$，把一个值为 $a$ 的数变成 $b$。
> 2. 给出 $a_1,a_2,b$，把一个值在 $\left[ a_1,a_2 \right]$ 范围内的数变成 $b$。
> 3. 给出 $a,b_1,b_2$，把一个值为 $a$ 的数变成在 $\left[ b_1,b_2 \right]$ 范围内的一个数。
> 4. 给出 $a_1,a_2,b_1,b_2$，把一个值在 $\left[ a_1,a_2 \right]$ 范围内的数变成在 $\left[ b_1,b_2 \right]$ 范围内的一个数。

容易发现，对于每个数的最优决策相同。

因此可以想到网络流，把 $n$ 作为源点的流量即可。

对于每个在 $\left[1,k\right]$ 范围内的值建一个点，其中源点连 1，汇点连 $k$，流量为 $n$。

看到有区间连边的操作，所以要用到**线段树优化建图**，把所有操作看成是两个区间的连边，然后线段树加虚点优化建边即可。

线段树的父子节点之间连流量无穷大的边。

一定要注意是在 $k$ 上开线段树。

点数 $O(4\times k +m)$，边数 $O(m \log_2 k)$，因为数据随机，dinic 跑的挺快。

```cpp
#include <bits/stdc++.h>
#define MI int m=(l+r)>>1;
using namespace std;
const int N=1e6,INF=2e9;
int n,m,k,op,len,ans;

int fir[N<<1],cnt=1;struct E{int v,w,nt;}e[N<<1];
void I(int u,int v,int w=0){e[++cnt]=(E){v,w,fir[u]};fir[u]=cnt;}
void in(int u,int v,int w){I(u,v,w),I(v,u);}

int d[N<<1],cur[N<<1],st,ed;queue <int>q;
bool bfs(){
	for(int i=st;i<=ed;i++)d[i]=0,cur[i]=fir[i];d[st]=1;q.push(st);
	while(!q.empty()){
		int u=q.front(),V;q.pop();
		for(int i=fir[u];i;i=e[i].nt)
			if(!d[V=e[i].v]&&e[i].w)
				d[V]=d[u]+1,q.push(V);
	}return d[ed];
}int dfs(int u,int fl){
	if(u==ed)return fl;int ans=0,V,re;
	for(int i=cur[u];i;i=e[i].nt){
		cur[u]=i;if(d[V=e[i].v]==d[u]+1&&e[i].w){
			re=dfs(V,min(fl,e[i].w));
			e[i].w-=re,e[i^1].w+=re;fl-=re,ans+=re;
			if(!fl)break;
		}
	}if(!ans)d[u]=0;return ans;
}void dinic(){while(bfs())ans+=dfs(st,INF);cout<<ans;}

int ls[N<<1],rs[N<<1],c,r1,r2;
void b1(int &p,int l,int r){
	if(l==r){p=l;return;}p=++c;MI 
	b1(ls[p],l,m);b1(rs[p],m+1,r);
	in(p,ls[p],INF);in(p,rs[p],INF);
}void b2(int &p,int l,int r){
	if(l==r){p=l;return;}p=++c;MI 
	b2(ls[p],l,m);b2(rs[p],m+1,r);
	in(ls[p],p,INF);in(rs[p],p,INF);
}void C(int p,int l,int r,int L,int R,int k,bool f){
	if(l>=L&&r<=R){in(f?p:k,f?k:p,INF);return;}
	MI if(L<=m)C(ls[p],l,m,L,R,k,f);
	if(R>m)C(rs[p],m+1,r,L,R,k,f);
}

int main(){
	cin>>n>>m>>k;c=k;b1(r1,1,k);b2(r2,1,k);
	for(int i=1,a,b,x,y,t1,t2;i<=m;i++){
		cin>>op>>len>>a>>b;t1=++c;t2=++c;
		if(op==1)C(r2,1,k,a,a,t1,1),C(r1,1,k,b,b,t2,0);
		else if(op==2)cin>>x,C(r2,1,k,a,b,t1,1),C(r1,1,k,x,x,t2,0);
		else if(op==3)cin>>x,C(r2,1,k,a,a,t1,1),C(r1,1,k,b,x,t2,0);
		else cin>>x>>y,C(r2,1,k,a,b,t1,1),C(r1,1,k,x,y,t2,0);
		in(t1,t2,len);
	}ed=c+1;in(st,1,n),in(k,ed,n);dinic();return 0;
}
```

---

## 作者：Night_Bringer (赞：0)

# 前言
线段树+网络最大流的建模题。

[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14612686.html)
# 题目大意
最初时有 $n$ 个 $1$ 。给定 $op$ 、 $l$ ，其中， $l$ 为操作次数上限。你有四个操作：
1. 若 $op=1$ ，则接下来两个整数 $a,b$ ，表示可以将 $a$ 变为 $b$ 。
2. 若 $op=2$ ，则接下来三个整数 $a_1,a_2,b_1$ ，表示可以将范围在 $a_1$ 到 $a_2$ 的任意的数变为 $b_1$ 。
3. 若 $op=3$ ，则接下来三个整数 $a_1,b_1,b_2$ ，表示可以将 $a_1$ 变为范围在 $b_1$ 到 $b_2$ 的任意的数。
4. 若 $op=4$ ，则接下来四个整数 $a_1,a_2,b_1,b_2$ ，表示可以将范围在 $a_1$ 到 $a_2$ 的任意的数变为范围在 $b_1$ 到 $b_2$ 的任意的数。

问最后能有多少个数字变为 $k$ ，其中 $1\leqslant a,b,a1,b1,a2,b2\leqslant k$ 。
# 思路
首先用暴力建图跑网络流。如果看出使用网络流，则建图就变得非常简单了。

把所有单个数字的查询都看为一个区间，那么四个操作都将是区间的连边。

使用一个类似于中转站的两个节点记为 $tmp1$ 和 $tmp2$ ，将 $a$ 区间的所有值连向 $tmp1$ ，将 $tmp2$ 连向 $b$ 区间的所有值，容量为无穷大。则 $tmp1$ 到 $tmp2$ 连一条容量为 $l$ 的边用来限制操作次数。

跑最大流即可得出答案。暴力建图伪代码：
```cpp
int tot = k;
int opt, l;
for(int i = 1; i <= m; i++) {
	scanf("%d %d", &opt, &l);
	if(opt == 1) {
		int a, b;
		scanf("%d %d", &a, &b);
		Addedge(a, b, l);
	}
	else if(opt == 2) {
		int a1, a2, b1;
		scanf("%d %d %d", &a1, &a2, &b1);
		int tmp1 = ++tot;
		int tmp2 = ++tot;
		for(int i = a1; i <= a2; i++)
			Addedge(i, tmp1, INF);
		Addedge(tmp2, b1, INF);
		Addedge(tmp1, tmp2, l);
	}
	else if(opt == 3) {
		int a1, b1, b2;
		scanf("%d %d %d", &a1, &b1, &b2);
		int tmp1 = ++tot;
		int tmp2 = ++tot;
		Addedge(a1, tmp1, INF);
		for(int i = b1; i <= b2; i++)
			Addedge(tmp2, i, INF);
		Addedge(tmp1, tmp2, l);
	}
	else {
		int a1, a2, b1, b2;
		scanf("%d %d %d %d", &a1, &a2, &b1, &b2);
		int tmp1 = ++tot;
		int tmp2 = ++tot;
		for(int i = a1; i <= a2; i++)
			Addedge(i, tmp1, INF);
		for(int i = b1; i <= b2; i++)
			Addedge(tmp2, i, INF);
		Addedge(tmp1, tmp2, l);
	}
}
t = tot + 1;
Addedge(s, 1, n);
Addedge(k, t, INF);
```
显然，一次操作会产生最多 $2k+2$ 条边，在观察这个数据范围，过不了。亲测 50 Pts。可能是常数太大。。。

由于是区间操作，可以想到使用数据结构来优化建图。

使用线段树，建立两颗线段树，如下图。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210402221307884.png?type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0ZhY2VfdGhlX0JsYXN0,size_16,color_FFFFFF,t_70#pic_center)

$s$ 连向第一棵线段树的 $[1,1]$ 区间的点，容量为 $n$ ，第二棵线段树的 $[k,k]$ 区间的点连向 $t$ ，容量为极大值，和暴力差不多。

可以把第二棵树理解为是操作树，是用来进行操作的。第一棵树的儿子连向自己的父亲，方便选定被操作前的范围。第二棵的父亲连向自己的儿子，方便选定操作后的范围。以上边的容量均为极大值。

最后第二棵树的节点连向第一棵树的对应点，方便操作后被再次操作。

最后跑一边最大流 Dinic ，在随机图上 Dinic 普遍优于其他 $O(nm\log(m))$ 的算法。
# Code
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
const int MAXN = 1e6 + 5;
const int MAXM = 5e6 + 5;
struct Segment_Tree {
	int Left_Section, Right_Section, Data;
	#define LC(x) (x << 1)
	#define RC(x) (x << 1 | 1)
	#define L(x) tree[0][x].Left_Section
	#define R(x) tree[0][x].Right_Section
	#define D(x, y) tree[y][x].Data
};
Segment_Tree tree[2][MAXN];
struct Edge { 
	int Next, To, Cap;
};
Edge edge[MAXM << 1];
int head[MAXM << 1];
int edgetot = 1;
int tot;
int n, m, k, s, t;
queue<int> q;
int dep[MAXN], stt[MAXN];
int Begin, End;
void Addedge(int x, int y, int z) {
	edge[++edgetot].Next = head[x], edge[edgetot].To = y, edge[edgetot].Cap = z, head[x] = edgetot;
	edge[++edgetot].Next = head[y], edge[edgetot].To = x, edge[edgetot].Cap = 0, head[y] = edgetot;
}
void Build(int pos, int l, int r, int flag) {//初始化线段树的节点信息 
	D(pos, flag) = ++tot;//开辟新的节点 
	L(pos) = l;//初始化左区间 
	R(pos) = r;//初始化右区间 
	if(l == r) {
		if(flag && l == 1)//记录左树的1节点 
			Begin = D(pos, flag);
		if(!flag && l == k)//记录右树的k节点
			End = D(pos, flag);
		if(!flag)//右树连左树的对应节点 
			Addedge(D(pos, flag), D(pos, 1 - flag), INF);
		return;
	}
	int mid = (l + r) >> 1;
	Build(LC(pos), l, mid, flag);//初始化 
	Build(RC(pos), mid + 1, r, flag);//同上 
	if(flag) {//左树儿子连父亲 
		Addedge(D(LC(pos), flag), D(pos, flag), INF);
		Addedge(D(RC(pos), flag), D(pos, flag), INF);
	}
	else {//右树父亲连儿子 
		Addedge(D(pos, flag), D(LC(pos), flag), INF);
		Addedge(D(pos, flag), D(RC(pos), flag), INF);
	}
}
void Query(int pos, int l, int r, int tmp, int flag) {//区间连边 
	if(l <= L(pos) && R(pos) <= r) {
		if(flag)
			Addedge(D(pos, flag), tmp, INF);//若是左树则连接中转站 
		else
			Addedge(tmp, D(pos, flag), INF);//若是右树被中转站连接 
		return;
	}
	if(l <= R(LC(pos)))
		Query(LC(pos), l, r, tmp, flag);//处理子树 
	if(r >= L(RC(pos)))
		Query(RC(pos), l, r, tmp, flag);//同上 
}
bool bfs() {//Dinic板子，不详写 
	for(int i = s; i <= t; i++)
		dep[i] = 0;
	stt[s] = head[s];
	dep[s] = 1;
	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = head[u]; i; i = edge[i].Next) {
			int v = edge[i].To;
			if(!dep[v] && edge[i].Cap) {
				dep[v] = dep[u] + 1;
				stt[v] = head[v];
				q.push(v);
			}
		}
	}
	return dep[t] != 0;
}
int dfs(int u, int flow) {//同上 
	if(u == t || !flow)
		return flow;
	int rest = flow;
	for(int i = stt[u]; i && rest; i = edge[i].Next) {
		stt[u] = i;
		int v = edge[i].To;
		if(dep[v] == dep[u] + 1 && edge[i].Cap) {
			int nextflow = dfs(v, min(rest, edge[i].Cap));
			if(!nextflow)
				dep[v] = -1;
			edge[i].Cap -= nextflow;
			edge[i ^ 1].Cap += nextflow;
			rest -= nextflow;
		}
	}
	return flow - rest;
}
int Dinic() {//同上 
	int res = 0;
	int flow;
	while(bfs())
		while(flow = dfs(s, INF))
			res += flow;
	return res;
}
int main() {
	scanf("%d %d %d", &n, &m, &k);
	Build(1, 1, k, 1); 
	Build(1, 1, k, 0);
	int opt, l;
	for(int i = 1; i <= m; i++) {
		scanf("%d %d", &opt, &l);
		int tmp1 = ++tot;
		int tmp2 = ++tot;
		if(opt == 1) {
			int a, b;
			scanf("%d %d", &a, &b);
			Query(1, a, a, tmp1, 1);
			Query(1, b, b, tmp2, 0);
		}
		else if(opt == 2) {
			int a1, a2, b1;
			scanf("%d %d %d", &a1, &a2, &b1);
			Query(1, a1, a2, tmp1, 1);
			Query(1, b1, b1, tmp2, 0);
		}
		else if(opt == 3) {
			int a1, b1, b2;
			scanf("%d %d %d", &a1, &b1, &b2);
			Query(1, a1, a1, tmp1, 1);
			Query(1, b1, b2, tmp2, 0);
		}
		else {
			int a1, a2, b1, b2;
			scanf("%d %d %d %d", &a1, &a2, &b1, &b2);
			Query(1, a1, a2, tmp1, 1);
			Query(1, b1, b2, tmp2, 0);
		}
		Addedge(tmp1, tmp2, l);
	}
	t = tot + 1;
	Addedge(s, Begin, n);//连接源点到左树1的点 
	Addedge(End, t, INF);//连接右树k的点到汇点 
	printf("%d", Dinic());
	return 0;
}
```

---

