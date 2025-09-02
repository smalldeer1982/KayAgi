# Dividing Kingdom II

## 题目描述

Long time ago, there was a great kingdom and it was being ruled by The Great Arya and Pari The Great. These two had some problems about the numbers they like, so they decided to divide the great kingdom between themselves.

The great kingdom consisted of $ n $ cities numbered from $ 1 $ to $ n $ and $ m $ bidirectional roads between these cities, numbered from $ 1 $ to $ m $ . The $ i $ -th road had length equal to $ w_{i} $ . The Great Arya and Pari The Great were discussing about destructing some prefix (all road with numbers less than some $ x $ ) and suffix (all roads with numbers greater than some $ x $ ) of the roads so there will remain only the roads with numbers $ l,l+1,...,r-1 $ and $ r $ .

After that they will divide the great kingdom into two pieces (with each city belonging to exactly one piece) such that the hardness of the division is minimized. The hardness of a division is the maximum length of a road such that its both endpoints are in the same piece of the kingdom. In case there is no such road, the hardness of the division is considered to be equal to $ -1 $ .

Historians found the map of the great kingdom, and they have $ q $ guesses about the $ l $ and $ r $ chosen by those great rulers. Given these data, for each guess $ l_{i} $ and $ r_{i} $ print the minimum possible hardness of the division of the kingdom.

## 样例 #1

### 输入

```
5 6 5
5 4 86
5 1 0
1 3 38
2 1 33
2 4 28
2 3 40
3 5
2 6
1 3
2 3
1 6
```

### 输出

```
-1
33
-1
-1
33
```

# 题解

## 作者：Miko35 (赞：20)

怎么你谷最优解都是暴力啊，哭哭。

大概是第一篇复杂度比较对的题解。

首先考虑暴力怎么做，也就是你要把整个图分成一个二分图，使得两端点在同一部分的边的最大边权最小。然后这个东西显然可以贪心，也就是从大往小枚举每条边，如果可以让它横跨两部，就把两端点分到不同的部分，反之则答案即为这条边的边权。这个可以用并查集维护。

这样做的复杂度是 $O(qm\cdot\alpha(n))$，因为是 CF 的机子所以可以通过此题~~并拿到你谷最优解~~。

---

考虑对于一个给定的边集，如果在里面加上若干条边，成为新的答案的边是什么。

1. 比原答案边权小的边显然不可能。
2. 比答案边权大，但是在原先加边的过程中，这条边没有任何作用，即：加这条边时未改变并查集信息。这也是不可能的，如果它成为了答案，那么其两端点一定在之前的边中被划分到同一个集合，而它没有被选中则表明原边集中权值严格大于它的边让其两端点划分到不同的集合，矛盾一定在它之前产生。

所以，只有对并查集产生修改或产生矛盾的边，才会成为新的答案。

而对并查集产生一次贡献，必然会合并两个连通块，所以，对于任意大的边集，并上一个边集之后，可能有贡献的边是 $O(n)$ 级别。这样的话，对于一个边集，只保留这些可能有贡献的边，在边集进行合并的时候答案不会改变。这样的话，合并两个边集时，暴力合并的复杂度变成了 $O(n\cdot\alpha (n))$。

边集具有了可加的性质，就可以用线段树来维护区间边集的并了。具体来说，一个节点 $[l,r]$ 维护的是区间 $[l,r]$ 所形成的边集中可能产生贡献的边，建树和查询只需要暴力合并区间即可。时间复杂度 $O((m+qn)\log m\cdot \alpha(n))$。

p.s. 区间合并时只用将所有涉及到的节点的并查集信息还原即可，如果像下面有篇题解一样全部还原，时间复杂度会多乘一个 $n$（（

稍微卡卡常可以跑进 1s。卡常前代码：

```cpp
#include<bits/stdc++.h>
#define rgi register int
#define mid (l+r>>1)
#define lc k<<1
#define rc lc|1
using namespace std;
const int N=1010,M=500010;
#define set(x) fa[x]=x,fa[x+n]=x+n
#define ve vector<edge>
#define vl(x) x.begin(),x.end()
int n,m,q,fa[N<<1],l,r;
struct edge{int u,v,w;}e[M];
int fi(int x){return x==fa[x]?x:fa[x]=fi(fa[x]);}
ve t[M<<2],res;
int solve(ve a,int k){
	for(auto e:a)set(e.u),set(e.v);
	for(auto e:a){
		int fx=fi(e.u),fy=fi(e.v),fY=fi(e.v+n);
		if(fx!=fY)t[k].push_back(e),fa[fx]=fY,fa[fy]=fi(e.u+n);
		if(fx==fy)return e.w;
	}
	return -1;
}
ve merge(ve a,ve b){
	ve r(a.size()+b.size());
	return merge(vl(a),vl(b),r.begin(),[&](edge x,edge y){return x.w>y.w;}),r;
}
void build(int k,int l,int r){
	if(l==r)return t[k].push_back(e[l]);
	build(lc,l,mid),build(rc,mid+1,r);
	solve(merge(t[lc],t[rc]),k);
}
ve qry(int x,int y,int k=1,int l=1,int r=m){
	if(l>y||r<x)return res;
	if(l>=x&&r<=y)return t[k];
	return merge(qry(x,y,lc,l,mid),qry(x,y,rc,mid+1,r));
}
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	for(rgi i=1;i<=m;++i)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	build(1,1,m);
	while(q--)scanf("%d%d",&l,&r),printf("%d\n",solve(qry(l,r),0));
	return 0;
}
```


---

## 作者：_maojun_ (赞：7)

提供一个非常神秘做法。

---

首先非常直接的做法就是，对于每个询问二分答案，判断 $[l,r]$ 中权值 $>x$ 的边是否可以黑白染色。复杂度是 $O(qm\log V)$ 的。边权离散化之后做到 $\log m$。

考虑整体二分。每次把权值在 $(mid,r]$ 的边加入，把询问分成仍可以和已不可以两部分。仍可以的询问答案在 $[l,mid]$，递归到左区间，并记录下这一层边对它的贡献；已不可以的询问递归到右区间。

首先判定能否黑白染色可以扩展域并查集。并查集支持 $O(\log n)$ 加边，于是可以通过回滚莫队 $O(m\sqrt q\log n)$ 求出某个区间的并查集。把询问的编号按 $(mid,r]$ 的边编号离散化一下，复杂度就是对的了。

但是每个点还带着之前递归到左时带上的贡献（一个并查集）要合并。事实上，并查集可以 $O(n\log n)$ 合并，具体就是把第一个并查集所有 $i$ 和 $i$ 的根在第二个并查集合并。

于是总复杂度 $O((m\sqrt q+nq)\log n\log m)$，但是回滚莫队的根号跑不满，并查集的 $\log$ 完全跑不满，所以跑出来 765ms，不算特别慢吧。

```cpp
const int N=1005,E=1e6+5,Q=1005;
int n,m,q,V=0,d[E],eu[E],ev[E],ew[E];

inline void init(int*f){for(int i=1;i<=n*2;i++)f[i]=i;}
int fd(int*f,int x){return x==f[x]?x:f[x]=fd(f,f[x]);}
inline bool mg0(int*f,int u,int v){
	int su=u>n?u-n:u+n,sv=v>n?v-n:v+n;
	if(fd(f,su)==fd(f,v)||fd(f,sv)==fd(f,u))return 0;
	f[fd(f,u)]=fd(f,v);f[fd(f,su)]=fd(f,sv);return 1;
}
inline bool mg1(int*f,int u,int v){
	if(fd(f,u)==fd(f,v)||fd(f,u+n)==fd(f,v+n))return 0;
	f[fd(f,u)]=fd(f,v+n);f[fd(f,v)]=fd(f,u+n);return 1;
}
struct QRY{int l,r,i;}q1[Q],q2[Q];int as[Q];
vector<int>ve[E];
int G[Q][N*2],G2[Q][N*2];bool FL[Q];
int V2=0,d2[E];
int I[E],L[E],R[E],nw[N*2],_w[N*2];bool nf;
inline void ad(int x){nf&=mg1(nw,eu[d2[x]],ev[d2[x]]);}
void dvd(int l,int r,int ql,int qr){
	if(ql>qr)return;
	if(l==r){for(int i=ql;i<=qr;i++)as[q1[i].i]=l;return;}
	int md=l+r>>1;V2=0;
	for(int w=md+1;w<=r;w++)for(int i:ve[w])d2[++V2]=i;sort(d2+1,d2+V2+1);
	int tt=0;
	for_each(q1+ql,q1+qr+1,[&](QRY x){
		FL[x.i]=1;
		q2[++tt].i=x.i;	
		q2[tt].l=lower_bound(d2+1,d2+V2+1,x.l)-d2;
		q2[tt].r=upper_bound(d2+1,d2+V2+1,x.r)-d2-1;
	});
	for(int i=1;i<=tt;i++)if(q2[i].l>q2[i].r)swap(q2[i--],q2[tt--]);
	const int B=ceil(V2/sqrt(tt));
	for(int i=1;i<=V2;i++)I[i]=(i-1)/B+1;int k=I[V2];
	for(int i=1;i<=k;i++){L[i]=R[i-1]+1;R[i]=R[i-1]+B;}R[k]=V2;
	sort(q2+1,q2+tt+1,[&](QRY x,QRY y){return I[x.l]^I[y.l]?x.l<y.l:x.r<y.r;});
	for(int t=1,o=1,l,r;t<=k;t++){
		init(nw);nf=1;r=R[t];
		for(;o<=tt&&I[q2[o].l]==t;o++){
#define UPD if(FL[q2[o].i]=nf)for(int i=1;i<=n;i++)if(!mg0(G2[q2[o].i],i,fd(nw,i))){FL[q2[o].i]=0;break;}
			if(I[q2[o].r]==t){
				for(int i=q2[o].l;i<=q2[o].r;i++)ad(i);
				UPD;init(nw);nf=1;
			}else{
				while(r<q2[o].r)ad(++r);l=R[t]+1;
				if(!nf){FL[q2[o].i]=0;continue;}
				memcpy(_w,nw,sizeof nw);
				while(l>q2[o].l)ad(--l);UPD;
				memcpy(nw,_w,sizeof nw);nf=1;
			}
		}
	}
	int qm=stable_partition(q1+ql,q1+qr+1,[&](QRY x){return FL[x.i];})-q1-1;
	for_each(q1+ql,q1+qm+1,[&](QRY x){memcpy(G[x.i],G2[x.i],sizeof*G);});
	for_each(q1+qm+1,q1+qr+1,[&](QRY x){memcpy(G2[x.i],G[x.i],sizeof*G);});
	dvd(l,md,ql,qm);dvd(md+1,r,qm+1,qr);
}
int main(){
	n=rd();m=rd();q=rd();
	for(int i=1;i<=m;i++){eu[i]=rd();ev[i]=rd();d[++V]=ew[i]=rd();if(eu[i]>ev[i])swap(eu[i],ev[i]);}
	sort(d+1,d+V+1);V=unique(d+1,d+V+1)-d-1;
	for(int i=1;i<=m;i++)ew[i]=lower_bound(d+1,d+V+1,ew[i])-d;
	for(int i=1;i<=q;i++){q1[i].l=rd();q1[i].r=rd();q1[i].i=i;}
	for(int i=1;i<=m;i++)ve[ew[i]].emplace_back(i);
	for(int i=1;i<=q;i++){init(G[i]);init(G2[i]);}
	dvd(0,V,1,q);
	for(int i=1;i<=q;i++)printf("%d\n",as[i]?d[as[i]]:-1);
	return 0;
}
```

---

## 作者：_agKc_ (赞：6)

# 翻译重置版
**有N个点，M条无向边(编号为1~M)，Q个问题。每条边有U,V,W(U,V为边链接的两点，为边权)。**

**完整边：一条边的两个端点都在一个区块中** 

**一个区块的价值：该区块中单条完整边的最大权值（如果没有完整边则为-1）**

**每次提问：L、R，只保留编号为[L，R]的边及其端点，将这些端点分入两个不同的区块（每个点只能属于一个区块）。你需要输出这两个区块中最大的区块价值的最小值**

# 正题开始
**涉及算法：贪心排序，并查集**

**主要思路：将每条边的两个端点都尽可能分入不同区块，防止形成完整边。将边从大到小排序，优先拆掉权值大的边**
## 代码部分
**father[i]数组开两倍，i表示与这个点在同一区块中的点，i+N表示与这个点在不同区块**

**对于每一条边，先检查两个端点是否在同一区间中，如果在就直接输出这条边的边权，否则就把两个端点连入互相的对立边**

# 警告，前方有AC代码出没
```cpp 
#define Tokisaki return
#define Kurumi  0;
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#define rint register int
typedef long long ll;
using namespace std;
struct road
{
	int start,end,len,id;
}rd[500005];
int fa[2005]; //两倍father数组
inline bool cmp (road x,road y)
{
	return x.len>y.len;
}
inline int getf (int x)
{
	if(fa[x]==x) return fa[x];
	return fa[x]=getf(fa[x]);
}
inline void con (int x,int y)
{
	int f1,f2;
	f1=getf(x),f2=getf(y);
	if(f1!=f2) fa[f1]=f2;
}
ll read (){ll ret=0,f=1;char c=getchar();while(!isdigit(c)) f=c=='-'?-1:1,c=getchar();while( isdigit(c)) ret=ret*10+c-'0',c=getchar();return ret*f;}

int main(){
	rint n,m,q;
	n=read(),m=read(),q=read();
	for(rint i=1;i<=m;i++)
	{
		rd[i].start=read();
		rd[i].end=read();
		rd[i].len=read();
		rd[i].id=i;
	}
	sort(rd+1,rd+1+m,cmp);
	while(q--)
	{
		rint ans=-1,l,r;
		l=read(),r=read();
		for(rint i=1;i<=n*2;i++)
		{
			fa[i]=i;
		}
		for(rint i=1;i<=m;i++) //暴力枚举每一条边
		{
			if(rd[i].id>=l&&rd[i].id<=r)
			{
				if(getf(rd[i].start)==getf(rd[i].end)) //两个端点在同一区块中
				{
					ans=rd[i].len;
					break;
				}
				else
				{
					con(rd[i].start+n,rd[i].end); //连入互相的对立点
					con(rd[i].start,rd[i].end+n);
				}
			}
		}
		printf("%d\n",ans);
	}
	Tokisaki Kurumi //狂三天下第一！！！
}
```

## 后言
**这道题难度不大（适合并查集初学者）**

这道题花了我一个小时，其中40分钟在看题目（英语不好），20分钟敲完代码


---

## 作者：是个汉子 (赞：4)



[洛谷传送门](https://www.luogu.com.cn/problem/CF687D)	[CF传送门](http://codeforces.com/problemset/problem/687/D)

### Solution

题解里都是暴力的做法，这里也介绍一下。

既然要求找最小的边，那么必然要将 $(l,r)$ 的边从大到小排序，然后将每条边的两个端点尽量分到不同的集合，直到分不了，就可以输出答案了。

时间复杂度：$O(mq)$ 

~~要不是时限 $6$ 秒，就都得没了~~

---

但是想法是好的，我们可以沿着这个想法继续思考。

将要加入并查集的边分为三种：

1.  $u$ 和 $v$ 不在同一个连通块里，那么将连通块联通，并标记 $u,v$ 不在同一集合
2.  $u$ 和 $v$ 在同一连通块中，但是不在同一集合，那么跳过即可
3.  $u$ 和 $v$ 在同一连通块中，但是在一个集合里，输出这条边

我们发现第 $1$ 种边最多有 $n-1$ 条，第 $3$ 种边有 $1$ 条，并且最后的答案和第 $2$ 种边是没有关系的。 

也就是说第 $1$ 种的这 $n-1$ 边就足以确定那个并查集了。

那么将这 $n-1$ 条边和第 $3$ 种边，即总共 $n$ 条边存下来最后用来判断答案，就可以将复杂度 $O(m)\rightarrow O(n)$ 。

用什么来存储呢？

我们发现还有一个细节没说——它是对于一个**区间**来询问的

哦，那就用线段树存吧(\*^▽^*)

但是问题是在建树时怎么向上pushup呢？

我们需要维护每个区间最多不超过 $n$ 条边而且边还要从大到小排序。排序好说，在合并两个区间的边时，归并排序即可；那么当两个区间合并时，怎么判断剩下的是哪几条边呢？还是拿并查集来维护嘛╮(╯-╰)╭

查询的时候同理。

建树复杂度为 $O[nm\alpha(n)]$ ，查询复杂度为 $O[qn\alpha(n)\log m]$ ，总时间复杂度为 $O[\alpha(n)n(m+q\log  m)]$ 。

### Code

```c++
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ls rt<<1
#define rs rt<<1|1
#define VI vector<int>

using namespace std;
const int N=1010,M=500010;
int n,m,q,X[M],Y[M],W[M],f[N],g[N],p[M];
VI tr[M<<2];
VI::iterator ia,ib;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int find(int x){
    if(f[x]==x) return x;
    int t=f[x];
    f[x]=find(t);
    g[x]^=g[t];
    return f[x];
}

inline VI merge(VI a,VI b){
    int cnt=0;
    VI res;
    for(ia=a.begin();ia!=a.end();ia++)
        f[X[*ia]]=X[*ia],f[Y[*ia]]=Y[*ia],g[X[*ia]]=g[Y[*ia]]=0;
    for(ia=b.begin();ia!=b.end();ia++)
        f[X[*ia]]=X[*ia],f[Y[*ia]]=Y[*ia],g[X[*ia]]=g[Y[*ia]]=0;
    for(ia=a.begin(),ib=b.begin();ia!=a.end()||ib!=b.end();){
        if(ia!=a.end()&&(ib==b.end()||W[*ia]>W[*ib]))
             p[++cnt]=*ia,ia++;
        else p[++cnt]=*ib,ib++;         //归并排序思想
    }
    for(int i=1,x,y;i<=cnt;i++){
        x=X[p[i]],y=Y[p[i]];
        if(find(x)!=find(y)) g[find(x)]=g[x]^g[y]^1,f[f[x]]=f[y],res.push_back(p[i]);
        else if(g[x]!=g[y]) continue;
        else{
            res.push_back(p[i]);
            break;
        }
    }
    return res;
}

void build(int rt,int l,int r){
    if(l==r){
        tr[rt].push_back(l);
        return ;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid); build(rs,mid+1,r);
    tr[rt]=merge(tr[ls],tr[rs]);
}

VI query(int rt,int l,int r,int L,int R){
    if(L<=l&&r<=R) return tr[rt];
    int mid=(l+r)>>1;
    if(R<=mid) return query(ls,l,mid,L,R);
    if(L>mid) return query(rs,mid+1,r,L,R);
    return merge(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
}

int main(){
    VI t;
    n=read(); m=read(); q=read();
    for(int i=1;i<=m;i++)
        X[i]=read(),Y[i]=read(),W[i]=read();
    build(1,1,m);
    for(int i=1,l,r,x,y;i<=q;i++){
        l=read(),r=read();
        t=query(1,1,m,l,r);
        for(ia=t.begin();ia!=t.end();ia++) f[X[*ia]]=X[*ia],f[Y[*ia]]=Y[*ia];
        for(ia=t.begin();ia!=t.end();ia++){
            x=X[*ia],y=Y[*ia];
            if(find(x)==find(y)) break;
            f[find(x)]=find(y);
        }
        if(ia==t.end()) puts("-1");
        else printf("%d\n",W[*ia]);
    }
    return 0;
}
```



---

## 作者：Larryyu (赞：3)

## _Description_

给定一个 $n$ 个点、$m$ 条边的图，有 $q$ 次询问，每次询问一个 $[l,r]$ 的区间，求将 $n$ 个点分为两个部分后，编号在 $[l,r]$ 内的边中，两端点属于同一部分的边权最大值最小是多少。

## _Solution_

转换一下题意，删去一些边使得剩下的图是一个二分图，使得删去的边权最大值最小。

上来看到最大值最小，立马想到二分答案，每次二分一个边权 $mid$，将所有边权大于 $mid$ 的加入图中，用扩展域并查集判断是否是二分图。

时间复杂度 $O(q\log m(n+m\alpha(n)))$。

但是你发现 $O(\log m)$ 是没必要的，先将边按边权从大到小排序，若编号属于 $[l,r]$ 就加入图中，如果加完这条边变奇图了那么这条边的边权就是答案。

时间复杂度 $O(q(n+m\alpha(n)))$，由于 ```CF``` 的神仙机子以及 $6$ 秒的实现可以暴力通过。

考虑如何优化，发现每一次加入边后的图实际上只有 $O(n)$ 条边会对下次加边造成影响，即一些树边（可能是森林）和可能有的一条边权最大的非树边（当前答案），它们可以代表当前的图，同时一些边在多组询问中都被并入一次，而将询问上到线段树上就可以避免。

所以我们开一棵线段树，节点 $[l,r]$ 表示将编号 $[l,r]$ 的边并完后能代表这个图的 $O(n)$ 条边，同时按边权从大到小排序，合并时先归并排序，将左右儿子的代表边集和在一起，然后求出新图的代表边集，建树复杂度为 $O(m\log m\alpha(n))$。

查询时将 $[l,r]$ 的代表边集暴力求答案，复杂度 $O(qn\alpha(n)\log m)$。

还可以继续，将询问离线离散化，树上节点 $[l,r]$ 表示 $[b_l,b_{r+1})$ 区间的代表边集，其中 $b$ 是离散数组。

记得离散询问 $[l,r]$ 时，离散 $l$ 和 $r+1$，查询时取出 $[c_l,c_{r+1}-1]$ 的代表集暴力即可，其中 $c_i$ 表示 $i$ 离散后的编号，若询问中没有 $1$ 和 $m$，记得加进离散。

时间复杂度 $O(m\log q\alpha(n)+qn\alpha(n)\log q)$。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls x<<1
#define rs x<<1|1
struct edge{
	int x,y,z;
}e[1000010];
bool cmp(edge x,edge y){
	return x.z>y.z;
}
#define ve vector<edge> 
int n,m,q,tot;
int b[6060],siz[2020],fa[2020];
ve tr[4000040];
struct que{
	int l,r;
}qu[3030];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
bool uni(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy) return 0;
	if(siz[fx]>siz[fy]) swap(fx,fy);
	siz[fy]+=siz[fx];
	fa[fx]=fy;
	return 1;
}
void reset(int x){
	fa[x]=x,fa[x+n]=x+n;
	siz[x]=1,siz[x+n]=1;
}
pair<ve,int> solve(ve tmp){
	ve ans;
	for(auto x:tmp){
		reset(x.x),reset(x.y);
	}
	for(auto i:tmp){
		int x=find(i.x),y=find(i.y);
		if(x!=y){
			if(uni(i.x,i.y+n)&&uni(i.y,i.x+n)){
				ans.push_back(i);
			}
		}else{
			ans.push_back(i);
			return {ans,i.z};
			break;
		}
	}
	return {ans,-1};
}
ve merge(ve l,ve r){
	ve tmp;
	int fl1=0,fl2=0;
	while(fl1<l.size()&&fl2<r.size()){
		if(cmp(l[fl1],r[fl2])){
			tmp.push_back(l[fl1++]);
		}else{
			tmp.push_back(r[fl2++]);
		}
	}
	while(fl1<l.size()) tmp.push_back(l[fl1++]);
	while(fl2<r.size()) tmp.push_back(r[fl2++]);
	auto ans=solve(tmp);
	return ans.first;
}
void build(int x,int l,int r){
	if(l==r){
		ve tmp;
		for(int i=b[l];i<b[l+1];i++){
			tmp.push_back(e[i]);
		}
		sort(tmp.begin(),tmp.end(),cmp);
		auto ans=solve(tmp);
		tr[x]=ans.first;
		return ;
	}
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	tr[x]=merge(tr[ls],tr[rs]);
}
ve query(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R){
		return tr[x];
	}
	int mid=l+r>>1;
	if(R<=mid) return query(ls,l,mid,L,R);
	if(L>=mid+1) return query(rs,mid+1,r,L,R);
	return merge(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>e[i].x>>e[i].y>>e[i].z;
	}
	for(int i=1;i<=q;i++){
		cin>>b[++tot]>>b[++tot];
		b[tot]++;
		qu[i]={b[tot-1],b[tot]};
	}
	b[++tot]=1;
	sort(b+1,b+1+tot);
	tot=unique(b+1,b+1+tot)-b-1;
	b[tot+1]=m+1;  //注意细节
	build(1,1,tot);
	for(int i=1;i<=q;i++){
		int l=lower_bound(b+1,b+1+tot,qu[i].l)-b;
		int r=lower_bound(b+1,b+1+tot,qu[i].r)-b-1;
		ve tmp=query(1,1,tot,l,r);
		int ans=solve(tmp).second;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Inui_Sana (赞：2)

来个抽象点的做法。

首先显然可以将条件转化成，将 $[l,r]$ 中的边从大到小加入一个图中，找出加入哪条边后不是一个二分图。显然可以用一个拓展域并查集维护。

观察到朴素暴力是 $O(nm)=O(n^3)$，几乎已经能过了（其实就是能过）。于是考虑进行一些小的处理，把它变成实际上就是能过的。

再观察，发现 $n=1000$ 也是相对小的，考虑利用这个性质，$n$ 小说明可能可以 $O(n)$ 合并两个并查集，于是尝试预处理一些并查集再合并。

因为每次肯定是从大往小加边，于是考虑先按照边权从小到大排序。发现大概 $10^5q$ 次操作是可以接受的，所以值域上每 $10^5$ 分一块。

对于每一块内，我们想要快速判断，当前的并查集再并上这个区间内的所有编号 $\in[l,r]$ 的边后，是否还满足是一个二分图。

于是考虑对每一块开一棵线段树，线段树上每个节点都是一个并查集，存储编号区间 $l,r$ 且边权属于这个块内的所有边加入一个并查集的结果。

对于每一次询问 $[ql,qr]$，从后往前检查每一个块。每次尝试加入这块内 $[ql,qr]$ 的所有边。这在线段树上是 $O(\log m)$ 个区间，找出这些区间并把所有并查集合并。再检查此时是否还是一个二分图。若不是，则将并查集回退到这次操作前，暴力尝试加入该块内的所有边。否则检查下一个块。

这样的时间复杂度，设块长为 $B$，是 $O(\frac{m^2\log m}{B}+\frac{mqn\log m}{B}+qB)$ 的，在 $B$ 取 $10^5$ 时理论上可过。但是有个大问题，就是空间是 $O(\frac{m^2n}{B})$ 显然爆炸。

解决这个问题可以考虑，其实我们并不关心每条边编号的具体位置，只关心它们是否在一个询问区间内。于是将所有 $[ql,qr]$ 离线下来离散化，初始化每个块内的线段树时只用判断当前编号属于哪个区间就行了。

于是空间复杂度变成 $O(\frac{mnq}{B})$，时间 $O(\frac{m^2\log q}{B}+\frac{mqn\log q}{B}+qB)$。换个 short 就过了。

另外，作者在写这篇题解的时候突然发现，如果把线段树换成猫树可以做到 $O(\frac{m^2\log q}{B}+\frac{mqn}{B}+qB)$，似乎会快很多。可能会补一个，也有可能咕咕咕了。

code：

```cpp
#define L(i) ((i)*B+1)
#define R(i) min(((i)+1)*B,m)
bool Mbe;
int n,m,q,k,B=1e5+44,id[M],ls[Q<<1];
struct node{
	int u,v,w,id;
}a[M],b[M];
struct Node{
	int l,r;
}d[Q];
struct DSU{
	short fa[N<<1];
	void init(){
		rep(i,1,n+n){
			fa[i]=i;
		}
	}
	int fd(int x){
		return fa[x]==x?x:fa[x]=fd(fa[x]);
	}
	il void mrg(int x,int y){
		fa[fd(x)]=fd(y);
	}
};
struct SGT{
	DSU tr[Q<<3];
	void bld(int l,int r,int u){
		tr[u].init();
		if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		bld(l,mid,u<<1),bld(mid+1,r,u<<1|1);
	}
	void upd(int l,int r,int u,int x,int y){
		tr[u].mrg(a[y].u,a[y].v+n);
		tr[u].mrg(a[y].u+n,a[y].v);
		if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			upd(l,mid,u<<1,x,y);
		}else{
			upd(mid+1,r,u<<1|1,x,y);
		}
	}
	void qry(int l,int r,int u,int x,int y,DSU &D){
		if(r<x||l>y){
			return;
		}
		if(l>=x&&r<=y){
			rep(i,1,n+n){
				D.mrg(i,tr[u].fd(i));
			}
			return;
		}
		int mid=(l+r)>>1;
		qry(l,mid,u<<1,x,y,D),qry(mid+1,r,u<<1|1,x,y,D);
	}
}T[6];
il bool cmp(node x,node y){
	return x.w<y.w;
}
void Yorushika(){
	read(n,m,q);
	rep(i,1,m){
		read(a[i].u,a[i].v,a[i].w);
		a[i].id=i,b[i]=a[i];
	}
	sort(b+1,b+m+1,cmp);
	rep(i,1,m){
		id[b[i].id]=(i-1)/B;
	}
	rep(i,1,q){
		read(d[i].l,d[i].r);
		ls[i+i-1]=d[i].l,ls[i+i]=d[i].r+1;
	}
	sort(ls+1,ls+q+q+1);
	k=unique(ls+1,ls+q+q+1)-ls-1;
	rep(i,0,(m-1)/B){
		T[i].bld(1,k,1);
	}
	rep(i,1,m){
		int p=upper_bound(ls+1,ls+k+1,i)-ls-1;
		T[id[i]].upd(1,k,1,p,i);
	}
	rep(i,1,q){
		DSU x;x.init();
		int p=-1,l=lower_bound(ls+1,ls+k+1,d[i].l)-ls,r=lower_bound(ls+1,ls+k+1,d[i].r+1)-ls;
		drep(j,(m-1)/B,0){
			DSU tmp=x;
			T[j].qry(1,k,1,l,r-1,x);
			rep(k,1,n){
				if(x.fd(k)==x.fd(k+n)){
					p=j,x=tmp;
					break;
				}
			}
			if(~p){
				break;
			}
		}
		if(p==-1){
			puts("-1");
			continue;
		}
		drep(j,R(p),L(p)){
			if(b[j].id<d[i].l||b[j].id>d[i].r){
				continue;
			}
			if(x.fd(b[j].u)==x.fd(b[j].v)){
				printf("%d\n",b[j].w);
				break;
			}
			x.mrg(b[j].u,b[j].v+n);
			x.mrg(b[j].u+n,b[j].v);
		}
	}
}
bool Med;
signed main(){
	cerr<<(&Mbe-&Med)/1048576.0<<'\n';
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：noble_ (赞：1)

把边从大到小排序。

然后对于每个询问跑暴力，贪心地把边从大到小访问，如果当前边没有冲突，那么就用并查集连边，否则直接输出。

并查集连边时注意要连到对称点去。（a -> b + n）



```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10050;
int pa[maxn];
struct Point { int u,v,dis,id; }a[maxn*100];
bool cmp(Point x,Point y) { return x.dis > y.dis; }
int find(int x) { if(pa[x]==x) return x; return pa[x] = find(pa[x]); }
void unite(int x,int y) {
	x = find(x), y = find(y);
	pa[x] = y;
}

int main() {
	int n, m, q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&a[i].u,&a[i].v,&a[i].dis);
		a[i].id = i;
	}
	sort(a+1, a+1+m, cmp);

	while(q--) {
		int l, r; scanf("%d%d",&l,&r);
		int ans=-1;
		for(int i=1;i<=2*n;i++) pa[i]=i;
		for(int i=1;i<=m;i++) {
			if(!(a[i].id<=r && a[i].id>=l)) continue;
			if(find(a[i].u)==find(a[i].v)) {
				ans = a[i].dis;
				break;
			}
			else {
				unite(a[i].u, a[i].v+n);
				unite(a[i].u+n, a[i].v);
			}
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：Yanami_Anna (赞：1)

首先这个东西有一个最基本的思路，就是先二分，然后枚举一遍，把比这个小的都丢掉，然后看是不是二分图。

这个很明显没有办法通过。

我们发现虽然 $m$ 巨大但是 $n$ 却不一般地小，我们对这个做文章。

合并两个并查集的时间复杂度是 $O(n)$，加一条边的时间复杂度是 $O(1)$，边的数量很多，但是如果我们能够预处理一些可合并的结构，然后查询的时候直接 $O(n)$ 把并查集放在一起，那就好做了。

自然而然地想到分块，分块之后预处理出大块区间的并查集，但是这个东西肯定没办法二分，所以考虑再做一个值域分块，假设值域分块块长为 $C$，序列分块块长为 $B$，那么这里就需要 $O(\frac{m^3n}{B^2C})$ 的时间复杂度，查询的时候就不要二分了，直接用值域分块试就解决了，单次询问时间复杂度 $O(\frac{mn}{C}+B+C)$，但是你发现 $B$ 和 $C$ 只挂在询问次数 $q$ 上，$q$ 又特别小，大头在前面的预处理，所以你可以把 $B$ 和 $C$ 开得特别大，然后复杂度就平衡了。

然后你随一组数据一测，哇居然要跑十三秒，赶紧来卡常。

首先就是并查集的构造，不要每次都从头构造，考虑把少一个序列块的和少一个值域块的合并，再合并他自己，这样构造一个区间从本来直接 $O(m)$，变成了 $O(n+B)$。

然后就是散块，散块别排序，sort 非常慢，你考虑你预先排序整块，然后对于散块把他们全块直接归并进来然后直接取用就行了。

然后就可以过了。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define ll long long
#define rep(i, f, t) for (int i = (f), ed##i = (t); i <= ed##i; ++i)
#define re(i, t) rep (i, 1, t)
#define per(i, t, f) for (int i = (t), ed##i = (f); i >= ed##i; --i)
#define ste(i, f, t, s) for (int i = (f), ed##i = (t); i <= ed##i; i += s)
#define each(i, x) for (auto& i : (x))
#define nxt(i, f, g) for (int i = g.h[f]; i; i = g.e[i].n)
#define dbg(x) (cerr << "(dbg) " << #x " = " << (x) << '\n')
#define umod(x) ((x) >= mo && ((x) -= mo))
#define dmod(x) ((x) < 0 && ((x) += mo))
#define up(x, y) (((x) < (y)) && ((x) = (y)))
#define down(x, y) (((x) > (y)) && ((x) = (y)))
#define y1 y1__
namespace FastIO {
    const int SZ=(1<<23)+1;
    struct I {
        char ibuf[SZ],*iS,*iT,c;int f,_eof;FILE*fi;
        I(FILE*f):fi(f){}
        inline char Gc(){return iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SZ,fi),(iS==iT?EOF:*iS++)):*iS++;}
        inline ll operator()(){ll x;operator()(x);return x;}
        inline I&operator()(char&x){x=Gc();return*this;}
        inline I&operator()(char*s){for(c=Gc();c<32||c>126||c==' ';)c=Gc();for(;c>31&&c<127&&c!=' '&&c!='\n'&&c!='\r';++s,c=Gc())*s=c;*s=0;return*this;}
        template<class T>inline I&operator()(T&x){_eof=0;for(f=1,c=Gc();(c<'0'||c>'9')&&!_eof;c=Gc()){if(c=='-')f=-1;_eof|=c==EOF;}for(x=0;c<='9'&&c>='0'&&!_eof;c=Gc())x=x*10+(c&15),_eof|=c==EOF;x*=f;return*this;}
        template<class T>I&operator()(T*x,const int&n,const int&st=1){rep(i,st,n){operator()(x[i]);}return*this;}
    } in(stdin);
    struct O {
        char obuf[SZ],*oS=obuf,*oT=oS+SZ-1,qu[55];int f,qr;FILE*fi;
        O(FILE*f):fi(f){}
        ~O(){Flush();}
        inline void Flush(){fwrite(obuf,1,oS-obuf,fi),oS=obuf;}
        inline O&operator()(char x){*oS++=x;if(oS==oT)Flush();return*this;}
        inline O&operator()(const char*s){int len=strlen(s);for(f=0;f<len;++f)operator()(s[f]);return*this;}
        template<class T>inline O&operator()(T x){if(!x)operator()('0');if(x<0)operator()('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)operator()(qu[qr--]);return*this;}
        template<class T>O&operator()(T*x,const int&n,const char&ed=' ',const int&st=1){rep(i,st,n)operator()(x[i])(ed);return*this;}
    } out(stdout);
}
using FastIO::in;using FastIO::out;
// using namespace std;
int n,m,q;
struct edge{
    int u,v,w;
    bool friend operator < (const edge &a,const edge &b){
        return a.w>b.w;
    }
}E[1000005];
struct lsh{
    int id,val;
    bool friend operator < (const lsh &a,const lsh &b){
        return a.val>b.val;
    }
}test[1000005];
const int B=30000,C=100000;
int numB,numC;
int rnk[1000005];
int frnk[1000005];
int stB[1000005];
int edB[1000005];
int stC[1000005];
int edC[1000005];
int belone[1000005];
int need[1000005];

int neta[50][50005];

class UFS{
    public:
    int father[2005];
    void init(int n){for(int i=1;i<=n;i++)father[i]=i;return;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unionn(int x,int y){return father[find(x)]=find(y),void();}
    bool check(int x){return find(x)==find(x+n);}
}S[35][35][12];//S[lt][rt][c]表示在编号上分块[lt,rt]，在权值上分块[1,c]的时候的并查集长什么样。

bool cmp(int a,int b){
    return E[a].w>E[b].w;
}

int main(){
    in(n)(m)(q);
    for(int i=1;i<=m;i++){
        int u,v,w;
        in(u)(v)(w);
        E[i]=edge{u,v,w};
        test[i]=lsh{i,w};
    }
    std::sort(test+1,test+1+m);
    for(int i=1;i<=m;i++){
        rnk[i]=test[i].id;
        frnk[test[i].id]=i;
    }
    numB=(m+B-1)/B,numC=(m+C-1)/C;
    for(int i=1;i<=numB;i++){
        stB[i]=(i-1)*B+1;
        edB[i]=std::min(i*B,m);
        for(int j=stB[i];j<=edB[i];j++)belone[j]=i;
        for(int j=stB[i];j<=edB[i];j++){
            neta[i][j-stB[i]+1]=j;
        }
        std::sort(neta[i]+1,neta[i]+1+(edB[i]-stB[i]+1),cmp);
    }
    // return 0;
    for(int i=1;i<=numC;i++){
        stC[i]=(i-1)*C+1;
        edC[i]=std::min(i*C,m);
    }
    // return 0;
    //对于每个点明明只有块长的更新量,却做了m次?
    for(int lt=1;lt<=numB;lt++){
        for(int rt=lt;rt<=lt;rt++){
            S[lt][rt][0].init(2*n);
            for(int i=1;i<=numC;i++){
                S[lt][rt][i]=S[lt][rt][i-1];
                for(int j=stC[i];j<=edC[i];j++){//
                    int id=rnk[j];
                    if(id<stB[lt]||id>edB[rt])continue;
                    S[lt][rt][i].unionn(E[id].u,E[id].v+n);
                    S[lt][rt][i].unionn(E[id].u+n,E[id].v);
                }
            }
        }
        for(int rt=lt+1;rt<=numB;rt++){
            int pos=1;
            S[lt][rt][0].init(2*n);
            for(int i=1;i<=numC;i++){
                S[lt][rt][i]=S[lt][rt][i-1];
                for(int j=1;j<=2*n;j++){
                    S[lt][rt][i].unionn(S[lt][rt-1][i].father[j],j);
                }
                while(pos<=edB[rt]-stB[rt]+1&&frnk[neta[rt][pos]]<=edC[i]){
                    S[lt][rt][i].unionn(E[neta[rt][pos]].u+n,E[neta[rt][pos]].v);
                    S[lt][rt][i].unionn(E[neta[rt][pos]].u,E[neta[rt][pos]].v+n);
                    pos++;
                }
            }
        }
    }
    
    // printf("%d\n",q);
    // return 0;
    UFS tmp;
    while(q--){
        // if(E[1].u==53&&E[1].v==8&&E[1].w==2&&q==200)return 0;
        int lt,rt;
        in(lt)(rt);
        tmp.init(2*n);
        // continue;
        //如果lt和rt在同一个或者相邻块里，应该可以直接操作，把他们搞下来排序不难
        //必须丢掉排序的复杂度。
        if(belone[lt]+1>=belone[rt]){
            int tot=0;
            if(belone[lt]==belone[rt]){
                for(int i=1;i<=edB[belone[lt]]-stB[belone[lt]]+1;i++){
                    need[++tot]=neta[belone[lt]][i];
                }
            }
            else{
                int posL=1,posR=1;
                while(posL<=edB[belone[lt]]-stB[belone[lt]]+1&&posR<=edB[belone[rt]]-stB[belone[rt]]+1){
                    if(cmp(neta[belone[lt]][posL],neta[belone[rt]][posR])){
                        need[++tot]=neta[belone[lt]][posL++];
                    }
                    else{
                        need[++tot]=neta[belone[rt]][posR++];
                    }
                }
                while(posL<=edB[belone[lt]]-stB[belone[lt]]+1)need[++tot]=neta[belone[lt]][posL++];
                while(posR<=edB[belone[rt]]-stB[belone[rt]]+1)need[++tot]=neta[belone[rt]][posR++];
            }
            // printf("[%d,%d]\n",lt,rt);
            // for(int i=1;i<=tot;i++){
            //     printf("%d ",need[i]);
            // }
            // puts("");
            // return 0;
            int ans=-1;
            for(int i=1;i<=tot;i++){
                if(need[i]<lt||need[i]>rt)continue;
                tmp.unionn(E[need[i]].u,E[need[i]].v+n);
                tmp.unionn(E[need[i]].u+n,E[need[i]].v);
                if(tmp.check(E[need[i]].u)){
                    ans=E[need[i]].w;
                    break;
                }
            }
            if(ans==-1){
                out("-1\n");
            }
            else{
                out(ans)('\n');
                // printf("%d\n",ans);
            }
            continue;
        }
        // continue;
        int tot=0;
        int posL=1,posR=1;
        while(posL<=edB[belone[lt]]-stB[belone[lt]]+1&&posR<=edB[belone[rt]]-stB[belone[rt]]+1){
            if(cmp(neta[belone[lt]][posL],neta[belone[rt]][posR])){
                need[++tot]=neta[belone[lt]][posL++];
            }
            else{
                need[++tot]=neta[belone[rt]][posR++];
            }
        }
        while(posL<=edB[belone[lt]]-stB[belone[lt]]+1)need[++tot]=neta[belone[lt]][posL++];
        while(posR<=edB[belone[rt]]-stB[belone[rt]]+1)need[++tot]=neta[belone[rt]][posR++];
        // sort(need+1,need+tot,cmp);
        // continue;
        int L=belone[lt]+1,R=belone[rt]-1;
        int pos=1;//
        int ans=-1;
        for(int i=1;i<=numC;i++){
            for(int j=1;j<=2*n;j++){
                tmp.unionn(S[L][R][i].father[j],j);
            }
            while(pos<=tot&&frnk[need[pos]]<=edC[i]){
                if(need[pos]<lt||need[pos]>rt){
                    pos++;
                    continue;
                }
                tmp.unionn(E[need[pos]].u+n,E[need[pos]].v);
                tmp.unionn(E[need[pos]].u,E[need[pos]].v+n);
                pos++;
            }
            bool flg=false;
            for(int j=1;j<=n;j++){
                if(tmp.check(j)){
                    flg=true;
                    break;
                }
            }
            if(!flg)continue;
            //说明第i个出问题了，那就考虑把i-1的一个一个加进来，但是我没记id
            tmp=S[L][R][i-1];
            pos=1;
            while(pos<=tot&&frnk[need[pos]]<=edC[i-1]){
                if(need[pos]<lt||need[pos]>rt){
                    pos++;
                    continue;
                }
                tmp.unionn(E[need[pos]].u+n,E[need[pos]].v);
                tmp.unionn(E[need[pos]].u,E[need[pos]].v+n);
                pos++;
            }
            //现在的tmp是没问题的，然后考虑开始一点一点枚举
            ans=-2;
            for(int j=stC[i];j<=edC[i];j++){
                int now=rnk[j];
                if(now<lt||now>rt)continue;
                tmp.unionn(E[now].u,E[now].v+n);
                tmp.unionn(E[now].u+n,E[now].v);
                if(tmp.check(E[now].u)){
                    ans=E[now].w;
                    break;
                }
            }
            break;
        }
        // assert(0);
        if(ans==-1){
            out("-1\n");
        }
        else{
            if(ans==-2){
                puts("hamood");
            }
            else{
                out(ans)('\n');
            }
        }
    }
    return 0;
}


```

---

## 作者：gyydp123_LIM (赞：0)

小记：模拟赛搬了这道题。场上花了 3h 终于想了出来，然后没时间写。发 result 了之后发现有人 $O(n^2q)$ 过了。。。

首先发现对于一个区间只有 $O(n)$ 条边是有用的，也就是只有 $O(n)$ 条边会在并查集上进行合并操作，然后我们发现这道题 $nq$ 和 $m$ 同阶，所以我们考虑能不能通过少量的预处理算出这 $O(n)$ 条边。我有考虑过二区间并（也就是猫树），但是无法预处理出前后缀的情况，所以这种做法没有前途。

考虑万能的分块。令块长为 $B$，对于散块我们有 $O(B)$ 条边，暴力排序后处理即可。对于整块我们考虑处理出 $O(n)$ 条边，发现一条边被算两次是不会影响的，所以用 ST 表预处理即可。对于两个区间的合并可以模仿归并实现。计算一个整块的复杂度是 $O(m\alpha(n)\log B)$ 的，ST 表预处理是 $O(n\alpha(n)\frac mB\log(\frac mB))$ 的。查询的时候只有 $O(B+n)$ 条边，所以直接排序后用并查集直接做，时间复杂度是 $O(Bq\log B+nq)$。取 $B=n$ 时时间复杂度是 $O(m\alpha(n)\log m+nq\log n)$。

代码

```c++
#define LJY main
// ------------------------- template -------------------------------
int n,m,q,u[M],v[M],w[M];
int tot,L[S],R[S],bel[M];
struct DSU{
  int fa[N<<1];
  void init(int n){For(i,1,n*2) fa[i]=i;}
  int find(int u){return fa[u]==u?u:fa[u]=find(fa[u]);}
  int addedge(int u,int v){
    int f1=find(u),f2=find(v);
    if(f1==f2) return 0; // 表示不是二分图
    int f3=find(u+n),f4=find(v+n);
    if(f1!=f4){fa[f1]=f4,fa[f2]=f3;return 1;} // 表示插入成功
    return -1; // 表示没有贡献，不用插入
  }
}tmp; //扩展域并查集
struct Node{
  int ans;vector<int>e;Node(){ans=0;} // ans 表示被删除的边中的权值最大值，e 表示有用的边集
  void init(vector<int>&p){ // 按权值排序，暴力预处理出 O(n) 的边集
    sort(p.begin(),p.end(),[&](int a,int b){return w[a]>w[b];});
    tmp.init(n);bool flg=0;ans=-1;
    for(int j=0;j<p.size();j++){
      int x=p[j],op=tmp.addedge(u[x],v[x]);
      if(!op){ans=w[x];flg=1;break;}
      else if(op==1) e.emplace_back(x);
    }
  }
}st[10][S];
Node operator+(Node a,Node b){ // 归并合并两个区间的边集，同时更新 ans
  Node c;c.ans=max(a.ans,b.ans);tmp.init(n);
  auto& v1=a.e,v2=b.e;
  int i=0,j=0,s1=v1.size(),s2=v2.size();
  while(i<s1&&j<s2){
    if(w[v1[i]]>w[v2[j]]){
      int op=tmp.addedge(u[v1[i]],v[v1[i]]);
      if(!op){c.ans=max(c.ans,w[v1[i]]);return c;}
      else if(op==1){c.e.emplace_back(v1[i]);}i++;
    }else{
      int op=tmp.addedge(u[v2[j]],v[v2[j]]);
      if(!op){c.ans=max(c.ans,w[v2[j]]);return c;}
      else if(op==1){c.e.emplace_back(v2[j]);}j++;
    }
  }
  while(i<s1){
    int op=tmp.addedge(u[v1[i]],v[v1[i]]);
    if(!op){c.ans=max(c.ans,w[v1[i]]);return c;}
    else if(op==1){c.e.emplace_back(v1[i]);}i++;
  }while(j<s2){
    int op=tmp.addedge(u[v2[j]],v[v2[j]]);
    if(!op){c.ans=max(c.ans,w[v2[j]]);return c;}
    else if(op==1){c.e.emplace_back(v2[j]);}j++;
  }return c;
}
signed LJY(){
  n=read();m=read();q=read();
  For(i,1,m) u[i]=read(),v[i]=read(),w[i]=read();
  tot=(m-1)/B+1;For(i,1,tot) L[i]=R[i-1]+1,R[i]=R[i-1]+B;R[tot]=m;
  For(i,1,tot){
    For(j,L[i],R[i]) bel[j]=i;
    vector<int>p(R[i]-L[i]+1),tp;
    For(j,L[i],R[i]) p[j-L[i]]=j;
    sort(p.begin(),p.end(),[&](int a,int b){return w[a]>w[b];});
    st[0][i].init(p);
  } // 分块，这里块长取的 1000
  For(i,1,31^__builtin_clz(tot))
    For(j,1,tot-(1<<i)+1)
      st[i][j]=st[i-1][j]+st[i-1][j+(1<<i-1)]; // ST 表
  while(q--){
    int l=read(),r=read(),ql=bel[l],qr=bel[r];
    if(ql+1>=qr){ // 散块暴力
      vector<int>p(r-l+1);For(i,l,r) p[i-l]=i;
      sort(p.begin(),p.end(),[&](int a,int b){return w[a]>w[b];});
      tmp.init(n);bool flg=0;
      for(int x:p){
        int op=tmp.addedge(u[x],v[x]);
        if(!op){printf("%d\n",w[x]);flg=1;break;}
      }if(!flg) puts("-1");continue;
    }vector<int>p;
    For(i,l,R[ql]) p.emplace_back(i);
    For(i,L[qr],r) p.emplace_back(i);
    Node x;x.init(p); // 散块暴力
    int len=31^__builtin_clz(qr-ql-1);
    x=st[len][ql+1]+st[len][qr-(1<<len)]+x;// 整块 ST 表查询
    if(x.ans!=-1) printf("%d\n",x.ans);else puts("-1");
  }
  return 0;
}
```

---

## 作者：Aw顿顿 (赞：0)

有 $n$ 个点，$m$ 条边，要求进行一些询问，每组询问会给出区间 $[l,r]$，要求保留编号在该区间内的边，以及他们所连的端点。接下来你要把这些端点划分成两个区域，区域中存在一条完整的边（两个端点都在这个区域内）的边权最大值为这个集合的得分，对于每一组询问求得分最小值。

不过，如果划分使得不存在完整边，那就输出 `-1`。

由于时限充裕，考虑贪心。从大到小去枚举边，这些边当然要尽可能把他们的点分到两个不同的集合中，正确性能保证，我们考虑一下实现。先边排序好之后跳过不在区间内的边，然后对于每一条边进行判断。如果两个端点已经在同一个集合内，那当前值就是最大值（因为已经排过序了）那么就可以结束循环。如果没有，就考虑分成两个集合，这个东西可以用种类并查集维护。

然后就是 $res$ 值设为 $-1$，记得每次询问要重新初始化。最后来算一下复杂度，一共 $q$ 次循环每次要遍历所有的 $m$ 条边，然后有一个 $\log n$ 级别的并查集维护，你会发现这东西的复杂度高的离谱。然而跑不满，而且数据水，所以能过；现在看代码：

```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
struct edge{int u,v,w,id;}e[N*N];
int n,m,q,fa[N<<1];
bool cmp(edge x,edge y){return x.w>y.w;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)fa[fx]=fy;
}void init(){
	for(int i=1;i<=(n<<1);i++)fa[i]=i;
}signed main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		int u,v,w;e[i].id=i;
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	}sort(e+1,e+1+m,cmp);
	for(int i=1;i<=q;i++){
		int res=-1,l,r;init();
		scanf("%d%d",&l,&r);
		for(int i=1;i<=m;i++){
			int u=e[i].u,v=e[i].v,w=e[i].w,id=e[i].id;
			if(id<l||id>r)continue;
			if(find(u)==find(v)){res=w;break;}
			else merge(u,v+n),merge(u+n,v);
		}printf("%d\n",res);
	}return 0;
}
```

---

## 作者：Trimsteanima (赞：0)

# $\mathtt{CF 687D}$

## $\mathcal{Description}$

[博客](https://www.cnblogs.com/wjnclln/p/11748895.html)

给你一个图有 $n$ 个点 $(1 \leq n \leq 10^3)$ 和 $m$ 条边 $(1  \leq m \leq \dfrac{n*(n-1)}{2})$ ，边有边权。给定 $q$ 组询问，每次询问给定 $l$ 和 $r$，用编号为 $[l,r]$ 去构成图，使得两边端点在同一个部分的边的最大值最小。

## $\mathcal{Solution}$

看到题第一反应是线段树，看看标签好像不太对劲的样子，考虑简单点的做法。

考虑如果构成的图是二分图的话，不可能存在一条边的两个端点在同一部分，所以可以得出构成的图一定不是二分图，于是题目可以转化成找奇环的最小变的最大值。

我们可以把边按权值从大到小排序，从最大的开始，不断加边，如果当前构成的图还是一个二分图，则继续加边，如果不是，就是最后我们要构成的图，所以就可以用带权二分图来做。

## $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;

int n, m, q;
int fa[N], fa1[N];

struct Node {
	int u, v, w, id;
} edge[N << 1];

inline int read() {
	int x = 0, k = 1; char c = getchar();
	for (; c < 48 || c > 57; c = getchar()) k ^= (c == '-');
	for (; c >= 48 && c <= 57; c = getchar()) x = x * 10 + (c ^ 48);
	return k ? x : -x;
}

inline bool cmp(Node x, Node y) {	
	return x.w > y.w;
}

int find(int x) {
	return (fa[x] == x) ? x : (fa[x] = find(fa[x]));
}

inline void match(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx == fy)
		return;
	if (fa1[fx] < fa1[fy]) swap(fx, fy);
	fa[fy] = fa[fx];
	if (fa1[fx] == fa1[fy])
		fa1[fx]++;
	return;
}

inline int query(int l, int r) {
	for (int i = 1; i <= m; i++) {
		if (edge[i].id < l || edge[i].id > r)
			continue;
		if (find(edge[i].u) != find(edge[i].v)) {
			match(edge[i].u, edge[i].v + n);
			match(edge[i].u + n, edge[i].v);
		}
		else 
			return edge[i].w;
	}
	return -1;
}

int main() {
    n = read(), m = read(), q = read();
    for (int i = 1; i <= m; i++)
		edge[i].u = read(), edge[i].v = read(), edge[i].w = read(), edge[i].id = i;
	std::sort(edge + 1, edge + 1 + m, cmp);
	for (int i = 1; i <= 2 * n; i++)
		fa[i] = i, fa1[i] = 0;
	for (int l = 0, r = 0, ans = -1; q--; ) {
		l = read(), r = read();
		printf("%d\n", query(l, r));
		for (int i = 1; i <= 2 * n; i++)
			fa[i] = i, fa1[i] = 0;
	}
	return 0;
}
```

---

