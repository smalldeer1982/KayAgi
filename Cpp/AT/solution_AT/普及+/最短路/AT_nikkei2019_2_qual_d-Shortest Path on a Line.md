# Shortest Path on a Line

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_d

一直線上に $ N $ 個の点があり、順に $ 1 $ から $ N $ までの番号がついています。

高橋君はこれらの点を頂点として無向グラフを作ることにしました。 はじめはグラフに辺はないですが、$ M $ 回の操作によって辺を追加します。 $ i $ 回目の操作では次のように辺を追加します。

- $ 1 $ 以上 $ N $ 以下の整数 $ L_i $, $ R_i $ 及び正整数 $ C_i $ を用いる。 $ L_i\ ≦\ s\ <\ t\ ≦\ R_i $ なる整数の組 $ (s,t) $ すべてに対し、頂点 $ s $ と頂点 $ t $ の間に長さ $ C_i $ の辺を追加する。

ただし、$ L_1,...,L_M $, $ R_1,...,R_M $, $ C_1,...,C_M $ はすべて入力で与えられます。

高橋君は最終的に得られたグラフ上で最短路問題を解きたいです。得られたグラフ上での頂点 $ 1 $ から頂点 $ N $ までの最短路の長さを求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ M\ ≦\ 10^5 $
- $ 1\ ≦\ L_i\ <\ R_i\ ≦\ N $
- $ 1\ ≦\ C_i\ ≦\ 10^9 $

### Sample Explanation 1

頂点 $ 1 $ と頂点 $ 2 $ の間に長さ $ 2 $ の辺があり、頂点 $ 2 $ と頂点 $ 4 $ の間に長さ $ 3 $ の辺があるので、頂点 $ 1 $ と頂点 $ 4 $ の間に長さ $ 5 $ のパスが存在します。

## 样例 #1

### 输入

```
4 3
1 3 2
2 4 3
1 4 6```

### 输出

```
5```

## 样例 #2

### 输入

```
4 2
1 2 1
3 4 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 7
1 5 18
3 4 8
1 3 5
4 7 10
5 9 8
6 10 5
8 10 3```

### 输出

```
28```

# 题解

## 作者：zjc5 (赞：5)

题目大意：

一个图 $N$ 个点，$M$ 次操作，每次输入三个整数 $L,R,C$，对于所有 $x,y(L \leqslant x,y \leqslant R)$，连一条长度为 $C$ 的边。求 $1$ 到 $N$ 的最短路。

$2 \leqslant N \leqslant 10^5$

$1 \leqslant M \leqslant 10^5$

$1 \leqslant L < R \leqslant 10^5$

$1 \leqslant C \leqslant 10^9$

**思路：**

可以发现，如果按照题目意思连边，再跑最短路，肯定会超时。那么就需要换一种方法建边。

有一个巧妙的方法：

先将第 $i(1 < i \leqslant N)$ 个点向第 $i-1$ 个点连一条长度为 $0$ 的边。

如果在 $L$ 和 $R$ 之间，就会通过长度为 $0$ 的边到达 $L$，并跳到 $R$。

所以输入时只需要建 $L$ 到 $R$ 这一条边，既满足题意，又只有 $N+M$ 条边，不会超时。

注意最好跑堆优化的迪杰斯特拉算法，其他最短路算法可能会超时。

**CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200010
#define int long long//一定要开long long
inline char gc(){
	static char buf[1000010],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int x=0;
	char s=gc();
	while(s<'0'||s>'9') s=gc();
	while(s>='0'&&s<='9'){
		x=(x<<3)+(x<<1)+(s^48);s=gc();
	}return x;
}
typedef pair<int,int> pii;
bool st[N];
int n,m,x,y,z,v,tot;
int head[N],e[N],ne[N],l[N],dis[N];
void add(int x,int y,int z){
    e[++tot]=y;
    l[tot]=z;
    ne[tot]=head[x];
    head[x]=tot;
}
int Dijkstra(){
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    priority_queue<pii, vector<pii>, greater<pii> >q;
    q.push({0,1});
    while(q.size()){
        auto t=q.top();
        int a=t.first,b=t.second;
        q.pop();
        if(st[b]) continue;
        st[b]=true;
        for(int i=head[b];i;i=ne[i]){
            v=e[i];
            if(a+l[i]<dis[v]) {
                dis[v]=a+l[i];
                q.push({dis[v],v});
            }
        }
    }
    if(dis[n]==dis[0]) return -1;
    return dis[n];
}
signed main(){
	n=read();
	m=read();
    for(int i=1;i<=m;i++) {
		x=read();
		y=read();
		z=read();
		add(x,y,z);
    }
	for(int i=n;i>1;i--)
		add(i,i-1,0);
    int t=Dijkstra();
    printf("%lld",t);
    return 0;
}
```

---

## 作者：Rem_CandleFire (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_2_qual_d)

这是一篇线段树优化 DP 的题解，无需最短路算法。

考虑将建边区间按左端点排序，然后枚举点 $i$。发现对于枚举的 $i$，它并不会从 $[i+1,n]$ 中的点转移而来，这说明 DP 是无后效性的，那么就可以从 $i$ 转移到后面的点去。

那么我们设 $f_i$ 表示走到 $i$ 的最短路。那么对于建边区间 $[i,r]$，对于 $j\in[l+1,r]$，有转移 $f_{j}=\min(f_j,f_i+w)$。这相当于区间 $[i+1,r]$ 对 $f_i+w$ 取 $\min$。发现只需要维护这一个操作，所以考虑给区间 $[i+1,r]$ 在线段树上打上标记，那么对于 $f_{i+1}$，它的值就从线段树的根节点一路取 $\min$ 到达叶节点就行了。标记是永久的，无需下传。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=3e5+5;
const LL Inf=1e18;
int n,m;
struct Interval { int l,r,w; } a[N];
bool cmp(Interval a,Interval b) { return a.l==b.l?a.r<b.r:a.l<b.l; }
LL f[N];
struct SegmentTree
{
	struct node { LL tag,val; } tr[N<<2];
	void Build(int l,int r,int k)
	{
		if(l==r) return tr[k].val=(l==1?0:Inf),void();
		int mid=(l+r)>>1;
		Build(l,mid,k<<1); Build(mid+1,r,k<<1|1);
	}
	void Update(int l,int r,int k,int x,int y,LL v)
	{
		if(r<x||l>y) return ;
		if(x<=l&&r<=y)
		{
			if(tr[k].tag>0) tr[k].tag=min(tr[k].tag,v);
			else tr[k].tag=v;
			return ;
		}
		int mid=(l+r)>>1;
		Update(l,mid,k<<1,x,y,v);
		Update(mid+1,r,k<<1|1,x,y,v);
	}
	LL Query(int l,int r,int k,int pos,LL v)
	{
		if(tr[k].tag) v=min(v,tr[k].tag);
		if(l==r) return tr[k].val=min(tr[k].val,v);
		int mid=(l+r)>>1;
		if(pos<=mid) return Query(l,mid,k<<1,pos,v);
		else return Query(mid+1,r,k<<1|1,pos,v); 
	}
} S;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) 
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].w);
	sort(a+1,a+1+m,cmp);
	if(a[1].l!=1) return !puts("-1");
	S.Build(1,n,1);
	int now=1;
	for(int i=1;i<=n;i++)
	{
		f[i]=S.Query(1,n,1,i,Inf);
		while(now<=m&&a[now].l==i) S.Update(1,n,1,a[now].l+1,a[now].r,f[i]+a[now].w),now++;
	}
	if(f[n]==Inf) puts("-1");
	else printf("%lld",f[n]);
	return 0;
}
```

---

## 作者：lunjiahao (赞：2)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_2_qual_d)

[AT 题目传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/nikkei2019_2_qual_d)

[博客园](https://www.cnblogs.com/lunjiahao/p/18574275)**可能**食用更佳

学校内部模拟赛出了这题，顺便来写下题解。

惊奇的发现题解区居然全是建图跑最短路，这怎么行，所以这一篇题解并没有跑任何最短路，而是使用了线段树优化 DP。

考虑将建边区间按右端点从小到大排序，每次以右端点为枚举编号，记作 $x$ ，发现只会从 $[1,x-1]$ 中的点转移过来，故这样对区间排序后不会存在后效性，故可以开始规划 DP。

将区间从小到大排序后，记第 $i$ 个区间为 $[L_i,R_i]$，$dp_x$ 表示从点 $1$ 出发到达点 $x$ 的最短距离，则 

$$
dp_{R_i}=
\begin{cases}
\min_{j=L_i}^{R_i-1} dp_j+W_i &, R_i \geq 2 \\
0 &, R_i=1 \\
\end{cases}
$$

这样做的时间复杂度为 $\mathcal O(mn+m \log m)$，那么就可以考虑优化一下复杂度

观察到 $dp_{R_i}$ 需要快速查询 $dp_{L_i,\dots,R_i-1}$ 的最小值，并且需要更新 $dp_{R_i}$ 的值，故可以使用线段树区间查询最小值，单点修改即可，时间复杂度 $\mathcal O(m \log m + m \log n)$，其中 $m \log m$ 为排序的时间复杂度，$\log n$ 为线段树单次操作的时间复杂度，细节见代码

```cpp
#include<bits/stdc++.h>
#define il inline
#define ls u<<1
#define rs u<<1|1
#define int long long//注意数据范围，需要开 long long
using namespace std;
const int N=3e5+5,INF=0x3f3f3f3f3f3f3f3f;
int n,m;
struct dat
{
	int L,R,W;
}a[N];
struct SGT//常规线段树操作
{
	int t[N<<2];
	void push_up(int u)
	{
		t[u]=min(t[ls],t[rs]);
	}
	void build(int u,int l,int r)
	{
		if(l==r) return t[u]=(l==1)?0:INF,void();//初始化 dp[1]=0
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		push_up(u);
	}
	void update(int u,int l,int r,int x,int k)
	{
		if(x==l&&r==x) return t[u]=k,void();//单点修改，故不用 push_down
		int mid=(l+r)>>1;
		if(x<=mid) update(ls,l,mid,x,k);
			else update(rs,mid+1,r,x,k);
		push_up(u);
	}
	int query(int u,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y) return t[u];
		int mid=(l+r)>>1,res=INF;
		if(x<=mid) res=min(res,query(ls,l,mid,x,y));
		if(y>mid) res=min(res,query(rs,mid+1,r,x,y));
		return res;
	}
}T;
template <typename T>
il void read(T &x)
{
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x*=f;
}
signed main()
{
	read(n),read(m);
	T.build(1,1,n);//建树
	for(int i=1;i<=m;i++)
		read(a[i].L),read(a[i].R),read(a[i].W);
	sort(a+1,a+1+m,[](dat a,dat b){return a.R<b.R;});//按照右端点从小到大排序
	for(int i=1;i<=m;i++)
	{
		if(a[i].L==a[i].R) continue;//特判区间大小为 1 的情况
		int pre=T.query(1,1,n,a[i].L,a[i].R-1);//查询区间 [L_i,R_i-1] 的最小值
		int now=T.query(1,1,n,a[i].R,a[i].R);//查询 dp[R_i] 的值
		if(pre+a[i].W<now) T.update(1,1,n,a[i].R,pre+a[i].W);//若从前面转移过来更优，则修改
		//当然这里也可以直接在线段树上修改取 min 也行
	}
	int ans=T.query(1,1,n,n,n);//dp[n]
	printf("%lld",ans==INF?-1:ans);
	return 0;
}
```

---

## 作者：船酱魔王 (赞：1)

# AT_nikkei2019_2_qual_d Shortest Path on a Line 题解

## 题意回顾

$ n $ 点无向图加边 $ m $ 次，每次给定 $ [l,r] $ 和 $ w $，$ \forall l \le u \le r,l \le v \le r $ 加边 $ (u,v) $ 边权为 $ w $。求最短路。

$ 1 \le n,m \le 10^5 $。

## 分析

首先我们把 $ u $ 由 $ [l,r] $ 加边到达 $ v $ 看做 $ u $ 向左到 $ l $，$ l $ 到 $ r $，$ r $ 向左到 $ v $。而向左的操作可以看做 $ 0 $ 边，因此我们从 $ n $ 到 $ 1 $ 不断加 $ 0 $ 边，再 $ (l,r) $ 加 $ w $ 边。

然后跑堆优化 dijkstra 即可。


## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, m;
struct node {
	int to;
	long long we;
};
node make(int v0, int w0) {
	node res;
	res.to = v0;
	res.we = w0;
	return res;
}
long long d[N];
bool operator<(node p1, node p2) {
	if(p1.we != p2.we) {
		return p1.we > p2.we;
	}
	return p1.to > p2.to;
}
vector<node> g[N];
priority_queue<node> pq;
bool vis[N];
signed main() {
	scanf("%lld%lld", &n, &m);
	int x, y, z;
	for(int i = 1; i <= m; i++) {
		scanf("%lld%lld%lld", &x, &y, &z);
		if(z > 1e9) {
		    cout << "Agrumestly get 660 points in 2023 Beijing Zhongkao" << endl;
		}
		g[x].push_back(make(y, z));
	}
	for(int i = 2; i <= n; i++) {
		g[i].push_back(make(i - 1, 0));
		d[i] = 1e16 + 5;
	}
	d[1] = 0;
	pq.push(make(1, 0));
	node now;
	vis[1] = true;
	while(!pq.empty()) {
		now = make(-1, -1);
		while(!pq.empty()) {
			now = pq.top();
			pq.pop();
			if(!vis[now.to]) {
				break;
			}
		} 
		x = now.to; 
		if(x == -1) {
			break;
		}
		vis[x] = true;
		for(int i = 0; i < (long long)g[x].size(); i++) {
			y = g[x][i].to;
			z = g[x][i].we;
			if(d[x] + z < d[y]) {
				d[y] = d[x] + z;
				pq.push(make(y, d[y]));
			}
		}
	}
	if(d[n] == 1e16 + 5) {
		printf("-1\n");
	} else {
		printf("%lld\n", d[n]);
	}
	return 0;
}
```

---

## 作者：sysong (赞：1)

# 题解 AT5635 Shortest Path on a Line

#### [或许更好的阅读体验](https://www.cnblogs.com/sysong2006/p/16641279.html)

upd on 2022.9.3：增加了对解法的描述。

## Description

[题目传送门](https://www.luogu.com.cn/problem/AT5635)

#### 题面翻译

有一张有 $N$ 个点，编号为 $1 - N$ 的无向图。

做 $M$ 次操作，每次操作给出三个正整数 $L,R,C$，对于每对 $≥L$ 且 $≤R$ 的整数对 $(S,T)$，在 $(S,T)$ 之间添加一条长度为 $C$ 的边。

完成操作后，找出操作后无向图的最短路。

#### 数据范围

- $ N,M\ \leq\ 10^5 $

## Solution

线段树优化建图裸题。

建议先完成线段树优化建图模板题 [CF786B](https://www.luogu.com.cn/problem/CF786B)。

看到区间向区间连边，显然暴力处理是 $O(MN)$ 的，会时间超限。

那么可以想到处理区间问题的常用工具：线段树。

我们对整个区间建立线段树，把每个点分为入点和出点，构建出入树和出树。

对于入树，从父节点向子节点连长度为 $0$ 的边，对于出树，从子节点向父节点连长度为 $0$ 的边，并且两棵树的对应叶子结点连长度为 $0$ 的边。

在实现上述过程的时候，我们其实只要建一遍线段树。对于叶子结点，我们可以让两棵树共用，就不必再连边了。

那么对于一个点向一个区间连边，我们可以将其转化为这个点和区间在入树上分成的若干子区间对应的节点连边。

区间向点连边同理，将出树上该区间分成的子区间分别向这个点连边。

题目要求我们区间向区间连边，这个时候我们可以新建一个节点，将出树区间向这个节点连边，这个点再向入树区间连边，就可以了。

然后剩下的就是在建好的图上跑最短路板子，我用的堆优化的 Dijkstra，就不赘述了。

细节可以看代码注释。

## Code

```c++
#include <bits/stdc++.h>
#define gc() getchar()
using namespace std;
typedef long long ll;

template <typename T> void rd(T &x){
	T f=1;x=0;char c=gc();
	for(;!isdigit(c);c=gc())if(c=='-')f=-1;
	for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}

const int MAXN=2e6+5;// 数组大小，开太小会 RE
// 链式前向星存图 
int n,m,cnt,hd[MAXN];
struct nd{
	int nxt,v,w;
}g[MAXN<<1];
inline void add(int u,int v,int w){
	g[++cnt].nxt=hd[u],g[cnt].v=v,g[cnt].w=w,hd[u]=cnt;
}
// 线段树
int tot,in[MAXN],out[MAXN];// tot 从 n 开始，in 存的是入树节点对应的图中节点编号，out 同理
struct sgt{
	int l,r;
}t[MAXN];
// 建树
inline void build(int o,int l,int r){
	t[o].l=l,t[o].r=r;
	if(l==r){
		in[o]=out[o]=l;// 如果是叶子节点，那么对应图中节点编号就是其下标，入树出树共用
		return;
	}
	int mid=l+r>>1;
	in[o]=++tot,out[o]=++tot;// 存储 o 代表的区间对应的图中节点
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);// 递归建树
	add(out[o<<1],out[o],0);
	add(out[o<<1|1],out[o],0);// 将出树从子节点向父节点连零边
	add(in[o],in[o<<1],0);
	add(in[o],in[o<<1|1],0);// 将入树从父节点向子节点连零边
}
// 加边
inline void addedge(int o,int l,int r,int u,int w){
	if(t[o].l>=l&&t[o].r<=r){
		add(out[o],u,0);// 从出树区间向新建节点连零边
		add(u,in[o],w);// 从新建节点向入树区间连长度为 w 的边
		return;
	}
	int mid=t[o].l+t[o].r>>1;
    // 递归加边
	if(l<=mid)addedge(o<<1,l,r,u,w);
	if(r>mid)addedge(o<<1|1,l,r,u,w);
}
// Dijkstra
const ll inf=0x3f3f3f3f3f3f3f3f;
ll d[MAXN];
int vis[MAXN];
// 堆优化
struct pq{
	int v;ll w;
	pq(){}
	pq(int _v,ll _w){v=_v,w=_w;}
	bool operator<(const pq &a)const{return w>a.w;}
};
priority_queue<pq>q;
inline void dij(){
	memset(d,0x3f,sizeof(d));
	d[1]=0;q.push(pq(1,0));
	while(!q.empty()){
		pq x=q.top();q.pop();
		int u=x.v;if(vis[u])continue;
		vis[u]=1;
		for(int i=hd[u];i;i=g[i].nxt){
			int v=g[i].v,w=g[i].w;
			if(d[v]>d[u]+w)d[v]=d[u]+w,q.push(pq(v,d[v]));
		}
	}
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	rd(n),rd(m);tot=n;// tot 从 n 开始，避免与叶子节点重复
	build(1,1,n);// 别忘了建树
	for(int i=1;i<=m;++i){
		int l,r,w;
		rd(l),rd(r),rd(w);
		addedge(1,l,r,++tot,w);// ++tot 新建节点
	}
	dij();
	printf("%lld\n",d[n]==inf?-1:d[n]);// 记得开 long long
	return 0;
}
```

-----

$by\ sysong$

$2022.8.30$



---

## 作者：Natori (赞：1)

# AT5635 Shortest Path on a Line 题解

这是一篇运用**最短路**的题解。

[题目传送门](https://www.luogu.com.cn/problem/AT5635)以及[不保证更好的阅读体验](https://www.luogu.com.cn/blog/545529/at5635-solution)

题意翻译一直都很简洁，但本题中需要注意的是要**求 $1$ 到 $n$ 的最短路**，翻译中并没有说明。

# Part 1 暴力

读完题发现要求最短路，所以先打个暴力试试水。由于是求单源最短路径，所以考虑使用堆优化的 $\text{Dijkstra}$ 算法，时间复杂度 $O((n+n^2m) \log_2 n)$，同时还要考虑暴力加边的复杂度是 $O(n^2m)$。实现时注意 ```std::pair``` 的第一个元素应是边权，第二个才是点的编号。

数据范围 $n,m \leq 10^5$，显然超时。

代码还是放一下：
```cpp
#include<cstdio>
#include<cstring>
#include<queue> 
#include<vector>
using namespace std;
typedef long long ll;
inline ll read(){
	ll f=1,x=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return f*x;
}
inline void write(ll x){
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
ll oo;
typedef pair<ll,ll> pll;
const int N=1e5+10;
priority_queue<pll,vector<pll>,greater<pll>> Q;//小根堆 
int n,m;
ll dis[N];
vector<pll>e[N];
bool vis[N];
int main(){
	memset(dis,0x3f,sizeof(dis));
	oo=dis[0];//正无限 
	n=read(),m=read();
	//暴力加边 
	for(int i=1,l,r,w;i<=m;i++){
		l=read(),r=read(),w=read();
		for(int u=l;u<=r;u++)
			for(int v=l;v<=r;v++)
				e[u].push_back(make_pair(w,v));
	}
	//堆优化Dijkstra求最短路 
	dis[1]=0;
	Q.push(make_pair(0,1));
	while(!Q.empty()){
		pll fr=Q.top();
		Q.pop();
		ll w=fr.first,u=fr.second;
		if(vis[u])
			continue;
		vis[u]=1;
		for(int i=0;i<e[u].size();i++){
			pll now=e[u][i];
			ll ww=now.first,v=now.second;
			if(dis[u]+ww<dis[v]){
				dis[v]=dis[u]+ww;
				if(!vis[v])
					Q.push(make_pair(dis[v],v));
			}
		}
	}
	if(dis[n]==oo)
		printf("-1");
	else
		write(dis[n]);
	return 0;
}
```
[提交记录](https://www.luogu.com.cn/record/76316855)，$7$ 号点 $\text{TLE}$~~跑了 53.98s 就离谱~~

# Part 2 优化

~~正片开始~~

$\text{Part 1}$ 算法超时的原因主要在于 $O(n^2m)$ 的暴力加边，而这也会导致后面 $\text{Dijkstra}$ 算法的时间复杂度变得很高，所以不能这样做。

因为原题是单源最短路径问题，所以不管采用哪种算法，我们的目的都是**求出 $dis$ 数组**，也就是每个点到源点 $1$ 的最短路径长度。

其实求 $dis$ 数组就是 $\text{Dijkstra}$ 算法要干的事，那么考虑把这个算法稍稍改一下。

我们尝试**把 $dis$ 数组的已知值“传递”到未知的位置**，即把输入的数据先存入 $dis$ 数组，通过 $\text{Dijkstra}$ 算法的执行求 $dis$ 数组的其他未知位置。

那么重难点来了：怎么实现它呢？

~~突然灵光一现~~想到可以多连几条边。~~其实不能叫改算法~~

画个图解释一下怎么连（图中点的编号从左到右依次递增）。

如果把从第 $2$ 行开始的每行输入数据看作一条有向边，那么样例 $1$ 对应的情形是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/b05r9916.png)

把结点 $n$ 到 $1$ 顺次连接，边权设为 $0$，就变成这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/omqof9kn.png)

那么为什么要这样连呢？

在图 $2$ 上模拟一下 $\text{Dijkstra}$ 算法的运行过程，帮助理解：

- 从 $1$ 开始

- 到达 $3$、$4$ 号结点，$dis_3=2,dis_4=6$

- 从 $3$ 走到 $2$，$dis_2=2$

- 从 $2$ 走到 $4$，$dis_4=5$

- 答案为 $5$。

发现这样能在 $\text{Dijstra}$ 算法的执行中得到 $dis_2$ 的值，这样就实现了之前所说的**把 $dis$ 数组的已知值“传递”到未知的位置**。

这样做的时间复杂度也会显著降低，因为边数降低到了 $O(n+m)$ 级别，所以 $\text{Dijkstra}$ 算法的时间复杂度也就降到了 $O((2n+m) \log_2 n)$，足以通过本题。

这里就放一下连边部分的代码：
```cpp
for(int i=1,l,r,w;i<=m;i++){
	l=read(),r=read(),w=read();
	e[l].push_back(make_pair(w,r));
}
for(int i=1;i<=n;i++)
	e[i].push_back(make_pair(0,i-1));
```
接下来跑一遍堆优化 $\text{Dijkstra}$ 的板即可，完整代码就不放了。

# Part 3 后记

做完之后翻了一下其他人的提交，发现有人用了不一样的方法，主要是数据结构。

其实这道题的加边方式是区间加边，所以数据结构的做法也是可行的。

具体的可以去看看别人的提交记录。

## $\text{update on 2022.5.27}$

感觉连边那部分没太讲清楚，这里补充一下。

实际上这个想法的来源就是那个“区间加边”操作。

假设有 $3$ 个点，给区间 $\left[1,3\right]$ 连上边权为 $w$ 的边。由于连的边**边权相等**，所以从点 $1$ 走到点 $2$ 和从点 $3$ 走到点 $2$ 的代价是相同的，都是 $w$。

而又发现从点 $1$ 到点 $3$ 的代价也是 $w$，与点 $1$ 到点 $2$ 的代价相同，所以就想到从点 $3$ 向点 $2$ 连一条边权为 $0$ 的有向边，来通过 $dis_3$ 求 $dis_2$。

还是建议自己在纸上画个图理解一下。

---

## 作者：hjqhs (赞：0)

米奇妙妙题。  
首先按题意暴力连边然后跑最短路肯定是不行的（当然线段树优化建图还是可以的）。  
考虑将 $[L,R]$ 里面所需要连的边连起来，考虑将 $[L,R]$ 里面所有的点约束到 $L$，即所有的点和 $L$ 有一条边权为 $0$ 的路径。所以只需要开始时将 $i$ 和 $i-1$ 连边即可。（$i \in [2,n]$）。此时每读入一组 $L,R$，只需要将 $L$ 和 $R$ 单独连起来即可。
```cpp
// Problem: D - Shortest Path on a Line
// Contest: AtCoder - NIKKEI Programming Contest 2019-2
// URL: https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Created Time: 2023-11-19 20:39:19
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define int long long
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define per(i, a, b) for (int i = a; i >= b; -- i)

using namespace std;

const int N = 200005;
const int INF = 0x3f3f3f3f3f3f3f3f;

int n, m, ent, head[N], dis[N];
bool vis[N];

struct node {int nxt, to, w; };
node e[N];

priority_queue < pair <int, int>, vector < pair <int, int> >, greater < pair <int, int> > > pq;

void addEdge (int u, int v, int w) {
	++ ent;
	e[ent].w = w;
	e[ent].to = v;
	e[ent].nxt = head[u];
	head[u] = ent;
}

int dij (int s) {
	memset (dis, INF, sizeof(dis));
	
	dis[s] = 0, pq.push ( {0, 1} );
	
	while ( !pq.empty() ) {
		pair <int, int> f = pq.top(); pq.pop();
		int a = f.first, b = f.second;
		
		if (vis[b]) continue;
		vis[b] = true;
		
		for (int i = head[b]; i; i = e[i].nxt) {
			int v = e[i].to;
			
			if (a + e[i].w < dis[v]) {
				dis[v] = a + e[i].w;
				pq.push ( {dis[v], v} );
			}
		}
	}
	
	return ( dis[n] == INF ? -1 : dis[n] );

}

void solve () {
	cin >> n >> m;
	rep (i, 1, m) {
		int u, v, w; cin >> u >> v >> w;
		addEdge (u, v, w);
	}
	// rep (i, 1, n - 1) addEdge (i, i + 1, 0);
	per (i, n, 2) addEdge (i, i - 1, 0);
	
	cout << dij(1);
	
	return;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	solve();
	
	return 0;
}
```

---

## 作者：foryou_ (赞：0)

我们发现，brute-force 的复杂度的优化瓶颈主要在建图上。

于是我们有一个巧妙的转化：

因为所有满足 $L \le S,T \le R$ 的所有边 $(S,T)$ 的长度均为 $C$。

然后题目要求的是 $1 \sim N$ 的最短路。

那么在边权相等的情况下，走到的点的编号一定越大越好。

于是在所有点对 $(S,T)$ 中，最优的一定是 $(L,R)$。

所以我们在建图时，仅需连接边（此处和以下所说的“边”均指单向边） $(L,R)$ 即可。

但是如果当前处在 $L \sim R$ 之间的点，怎么办？

其实可以对于 $2 \sim N$ 中的每个点 $i$，都向编号为 $i-1$ 的点连一条边权为 $0$ 的边（边权为 $0$ 是为了边权之和保持不变）。

当目前处在 $L \sim R$ 之间的点时，就可以通过若干边权为 $0$ 的边回到 $L$，再跳到 $R$。

通过这样的转化，我们成功将建图的复杂度优化到了 $O(N+M)$，接着跑一遍 dijkstra 算法求出最短路即可。

总时间复杂度为 $O(N+M+N \log N)$。

---

## 作者：AgrumeStly (赞：0)


如果直接暴力按题意连边，然后跑最短路，复杂度 $O((n+n^2m)\log n)$。显然过不了。

因为 $n,m \leq 10^5$，显然不能暴力加边，考虑如何减少连边。

因为是区间内所有点连边，事实上我们可以理解为，是先从区间左边界 $l$ 点，再到达右边界 $r$ 点，再到达区间内一点，再到与其所连点。

于是我们可以在 $l$ 与 $r$ 之间连一条长为 $c$ 的 **单向边**，为了使能从右边界到区间内任意一点，所以我们可以在 $i → i-1$ 之间连一条长为 $0$ 的 **单向边**。

于是这样对于区间的左右端点，都被转移到了区间内任意一点，于是最后跑一边最短路，求 $1$ 到 $n$ 的最短路即可。

注意：因为 $1 \leq c \leq 10^9$，所以极端情况下有且仅有每相邻两个点有边，最短路长度为 $(n-1)c$，远超 int，所以记得开 long long

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int NR = 1e5 + 5;
int n, m;
vector< int > e[NR], g[NR];
int dis[NR];
struct node { int p, d; };
bool operator > (node x, node y) {
	return x.d > y.d;
}
priority_queue< node, vector< node >, greater< node > > q;
bool vis[NR];
bool dijkstra(int s) {
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[s] = 0, q.push({s, 0});
	while(!q.empty()) {
		int u = q.top().p; q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = 0; i < e[u].size(); ++i) {
			int v = e[u][i];
			if(dis[v] > dis[u] + g[u][i]) {
				dis[v] = dis[u] + g[u][i];
				if(!vis[v]) q.push({v, dis[v]});
			}
		}
	}
	return dis[n] == dis[0];
}
signed main() {
	cin >> n >> m;
	for(int i = 1, u, v, w; i <= m; ++i)
		cin >> u >> v >> w, e[u].push_back(v), g[u].push_back(w);
	for(int i = 2; i <= n; ++i)
		e[i].push_back(i - 1), g[i].push_back(0);
	if(dijkstra(1)) cout << "-1" << endl;
	else cout << dis[n] << endl;
	return 0;
}
```

---

