# [国家集训队] JZPFAR

## 题目背景

原《零件分组》见 P1233。


## 题目描述

平面上有 $n$ 个点。现在有 $m$ 次询问，每次给定一个点 $(px, py)$ 和一个整数 $k$，输出 $n$ 个点中离 $(px, py)$ 的距离第 $k$ 大的点的标号。如果有两个(或多个)点距离 $(px, py)$ 相同，那么认为标号较小的点距离较大。


## 说明/提示

#### 数据规模与约定

- $50\%$ 的数据中，$n$ 个点的坐标在某范围内随机分布。
- $100\%$ 的数据中，$1\le n\le 10^5$，$1\le m\le 10^4$，$1\le k\le 20$，$-10^9\le x_i,y_i,px_i,py_i\le 10^9$，$n$ 个点中任意两点坐标不同，$m$ 个询问的点的坐标在某范围内随机分布。

## 样例 #1

### 输入

```
3
0 0
0 1
0 2
3
1 1 2
0 0 3
0 1 1```

### 输出

```
3
1
1```

# 题解

## 作者：星空_寻觅 (赞：22)

(哪里排版不整齐了QAQ……)
补充一篇新题解，利用KD-Tree算法，求二维平面内到一定点的第k远点，距离计算方式为欧几里德距离：  
$(sqrt((x2-x1)^2+(y2-y1)^2))$。  
正常建树，由于题目要求输出第k远点的编号，我们需记录一下每个节点的id，利用结构体存储信息，用优先队列（也可手写堆）动态维护小根堆，保持k个最优点，最后输出堆顶元素的编号即可。
```cpp
#include<bits/stdc++.h>
#define int long long
#define re register
#define inf 0x7fffffff
const int L=1<<20|1;
char buffer[L],*S,*T;
#define getchar() ((S==T&&(T=(S=buffer)+fread(buffer,1,L,stdin),S==T))?EOF:*S++)
using namespace std;
int n,m,tot,cmpid,root,X,Y;
inline int read(){
	re int a=0,b=1; re char ch=getchar();
	while(ch<'0'||ch>'9')
		b=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9')
		a=(a<<3)+(a<<1)+(ch^48),ch=getchar();
	return a*b;
}
struct node{int dis,id;};
inline bool operator < (node a,node b){
	return a.dis>b.dis||(a.dis==b.dis&&a.id<b.id);
}
priority_queue<node> q;
struct point{
	int x[2],id;
	friend bool operator < (const point &a,const point &b)
		{return a.x[cmpid]<b.x[cmpid];}
}p[100010];
struct tree{
	point p;int mx[2],mn[2],ls,rs,id;
}t[100010];
inline int dis(tree x){
	re int P=(x.p.x[0]-X)*(x.p.x[0]-X);
	re int Q=(x.p.x[1]-Y)*(x.p.x[1]-Y);
	return P+Q;
}
inline int mxdis(tree x){
	re int P=(x.mn[0]-X)*(x.mn[0]-X);
	re int M=(x.mx[0]-X)*(x.mx[0]-X);
	re int Q=(x.mn[1]-Y)*(x.mn[1]-Y);
	re int N=(x.mx[1]-Y)*(x.mx[1]-Y);
	return max(P,M)+max(Q,N);
}
inline void update(re int x){
	if(!x)  return ; re int l=t[x].ls,r=t[x].rs;
	if(l) t[x].mn[0]=min(t[x].mn[0],t[l].mn[0]),
		  t[x].mn[1]=min(t[x].mn[1],t[l].mn[1]),
		  t[x].mx[0]=max(t[x].mx[0],t[l].mx[0]),
		  t[x].mx[1]=max(t[x].mx[1],t[l].mx[1]);
	if(r) t[x].mn[0]=min(t[x].mn[0],t[r].mn[0]),
		  t[x].mn[1]=min(t[x].mn[1],t[r].mn[1]),
		  t[x].mx[0]=max(t[x].mx[0],t[r].mx[0]),
		  t[x].mx[1]=max(t[x].mx[1],t[r].mx[1]);
}
inline void query(re int x){
	if(!x) return ;
	re int res=dis(t[x]);
	if(res>q.top().dis||(res==q.top().dis&&t[x].id<q.top().id)) 
		q.pop(),q.push((node){res,t[x].id});
	re int l=t[x].ls,r=t[x].rs,ld,rd;
	if(l) ld=mxdis(t[l]);
	if(r) rd=mxdis(t[r]);
	if(ld>rd){
		if(ld>=q.top().dis) query(l);
		if(rd>=q.top().dis) query(r);
	}
	else{
		if(rd>=q.top().dis) query(r);
		if(ld>=q.top().dis) query(l);
	}
}
inline void build(re int &x,re int l,re int r,re int k){
	if(l>r) return ;
	x=++tot;cmpid=k;
	re int mid=(l+r)>>1;
	nth_element(p+l,p+mid,p+r+1);
	t[x].p=p[mid];t[x].id=t[x].p.id;
	t[x].mn[0]=t[x].mx[0]=t[x].p.x[0];
	t[x].mn[1]=t[x].mx[1]=t[x].p.x[1];
	build(t[x].ls,l,mid-1,k^1);
	build(t[x].rs,mid+1,r,k^1);
	update(x);
}
signed main(){
	n=read();
	for(re int i=1;i<=n;i++)
		p[i].x[0]=read(),p[i].x[1]=read(),p[i].id=i;
	build(root,1,n,0);
	m=read();
	for(re int i=1,k;i<=m;i++){
		X=read(),Y=read(),k=read();
		while(q.size()) q.pop();
		for(re int j=1;j<=k;j++) q.push((node){-1,0});
		query(root);
		printf("%lld\n",q.top().id);
	}
	return 0;
}
```


---

## 作者：Su_Zipei (赞：12)

### 题意:求平面内距离给定点第k远的点。

~~不难~~发现这题实际上是 KD-Tree 的模板题。

对于普通的求最大值和最小值，这道题改成了求 $k$ 远的，但是发现 $k$ 最大只有 $20$，所以试着把离他最远的 $k$ 个元素都求出来然后扔到一个小根堆里边最后输出堆顶即可。

最后需要注意的是距离是欧几里德距离不要用了别的距离不然会又WA又TLE。
```
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int rt,typ,cnt;
struct Node{
	int x[2],id;
	bool operator < (const Node&A)const{
		return x[typ]<A.x[typ];
	}
}a[N];
struct Tree{
	int ls,rs,Max[2],Min[2],id;
	Node v;
}T[N];
struct Q{
	int id;ll val;
	Q(){}
	Q(int a,ll b){
		id=a;val=b;
	}
	bool operator < (const Q&A)const{
		if(val==A.val)return id<A.id;
		return val>A.val;
	}
	bool operator > (const Q&A)const{
		if(val==A.val)return id<A.id;
		return val>A.val;
	}
};
priority_queue<Q> q;
#define ls T[rt].ls
#define rs T[rt].rs
void up(int rt){
	for(int i=0;i<2;i++){
		T[rt].Max[i]=T[rt].Min[i]=T[rt].v.x[i];
		if(ls){
			T[rt].Max[i]=max(T[rt].Max[i],T[ls].Max[i]);
			T[rt].Min[i]=min(T[rt].Min[i],T[ls].Min[i]);
		}
		if(rs){
			T[rt].Max[i]=max(T[rt].Max[i],T[rs].Max[i]);
			T[rt].Min[i]=min(T[rt].Min[i],T[rs].Min[i]);
		}
	}
}
void Build(int &rt,int l,int r,int d){
	if(l>r)return;
	rt=++cnt;
	int mid=l+r>>1;
	typ=d;
	nth_element(a+l,a+mid,a+r+1);
	T[rt].v=a[mid];T[rt].id=a[mid].id;
	Build(ls,l,mid-1,d^1);
	Build(rs,mid+1,r,d^1);
	up(rt);
}
ll sqr(ll x){return x*x;}
ll getdis(int rt,Node v){
	ll tmp=0;
	for(int i=0;i<2;i++)
		tmp+=sqr(max(abs(v.x[i]-T[rt].Max[i]),abs(v.x[i]-T[rt].Min[i])));
	return tmp;
}
#define dis(x,y,xx,yy) (1ll*(x-xx)*(x-xx)+1ll*(y-yy)*(y-yy))
void query(int rt,Node v){
	Q tmp=Q(T[rt].id,dis(v.x[0],v.x[1],T[rt].v.x[0],T[rt].v.x[1]));
	if(tmp>q.top())q.pop(),q.push(tmp);
	ll ld=-0x7f7f7f7f7f7f,rd=-0x7f7f7f7f7f7f;
	if(ls)ld=getdis(ls,v);
	if(rs)rd=getdis(rs,v);
	if(ld<rd){
		if(rd>=q.top().val)query(rs,v);
		if(ld>=q.top().val)query(ls,v);
	}else{
		if(ld>=q.top().val)query(ls,v);
		if(rd>=q.top().val)query(rs,v);
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<2;j++)
			scanf("%d",&a[i].x[j]);
		a[i].id=i;
	}
	Build(rt,1,n,0);
	int m;
	scanf("%d",&m);
	while(m--){
		int k;Node w;
		scanf("%d%d%d",&w.x[0],&w.x[1],&k);
		while(!q.empty())q.pop();
		while(k--)q.push(Q(0,-1));
		query(rt,w);
		printf("%d\n",q.top().id);
	}
	return 0;
}

```

---

## 作者：elijahqi (赞：9)

http://www.elijahqi.win/2018/01/25/bzoj2626-jzpfar/ 

http://blog.csdn.net/elijahqi/article/details/79157064 

仔细算了发（噗希望必要被巨佬们打脸qwq 似乎最坏情况会炸long long 但我觉得sqrt影响效率和精度 就没写 似乎也A了

大概是裸的kd-tree 估价函数也比较好写 但是样例提示我们需要注意一下几点问题 1、 有可能存在距离相同但是编号比较小的情况这种情况我们不能直接跳过 而是也应该进去暴力算一算2、在定义小根堆的时候由于priority\_queue内部是仍然是按照大根堆来搞 那么由于我应该只可以重载小于号 所以我需要在重载小于号的时候反向即可 其他就是一些常数的优化了 具体可以看下代码 比如我算下左右子树最远的距离 哪个更远去搞那个因为可能搞完这个 另一棵都不用搞了 这题要求维护最远的k点那么我需要维护一个小根堆 每次比较下 如果我比最小的还小就不搞了  对于每个节点 如果我比最小的大就去搞一搞 同时为了避免queue empty一开始我预处理的放入k个非常小的即可

```cpp
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110000
#define inf 1LL<<60
#define ll long long
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++; 
}
inline int read(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=gc();}
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return x*f;
}
int D,n,m,root,k;
struct node1{
    int d[2],id;
    int& operator[](int x){return d[x];}
    friend bool operator<(node1 a,node1 b){return a[D]<b[D];}
}point[N],P;
struct node{
    node1 x;int min[2],max[2],left,right,idmin;node(){idmin=0x3f3f3f3f;} 
}tree[N];
struct node2{
    int id;ll dis;
    node2(int idd,ll diss){id=idd;dis=diss;}
    inline friend bool operator<(const node2 &a,const node2 &b){
        return a.dis==b.dis?a.id<b.id:a.dis>b.dis;
    }
};
inline void update(int x){
    int l=tree[x].left,r=tree[x].right;
    tree[x].idmin=min(tree[x].x.id,min(tree[l].idmin,tree[r].idmin));
    for (int i=0;i<2;++i) tree[x].max[i]=max(tree[x].max[i],max(tree[l].max[i],tree[r].max[i]));
    for (int i=0;i<2;++i) tree[x].min[i]=min(tree[x].min[i],min(tree[l].min[i],tree[r].min[i]));
}
inline void build(int &x,int l,int r,int dim){
    int mid=l+r>>1;x=mid;D=dim;nth_element(point+l,point+mid,point+r+1);
    tree[x].x=point[mid];for (int i=0;i<2;++i) tree[x].min[i]=tree[x].max[i]=point[mid][i];
    if (l<mid) build(tree[x].left,l,mid-1,dim^1);
    if (r>mid) build(tree[x].right,mid+1,r,dim^1);update(x);
}
inline ll calc(node1 a){
    return (ll)(a[0]-P[0])*(a[0]-P[0])+(ll)(a[1]-P[1])*(a[1]-P[1]);
}
priority_queue<node2>q;
inline ll calc1(int x){
    ll tmp=0;
    for (int i=0;i<2;++i){
        ll tmp1=max(abs(P[i]-tree[x].min[i]),abs(P[i]-tree[x].max[i]));
        tmp+=tmp1*tmp1;
    }return tmp; 
}
inline void query(int x){
    ll dis=calc(tree[x].x),ldis=-inf,rdis=-inf;int id=tree[x].x.id;
    if (dis>q.top().dis||(dis==q.top().dis&&id<q.top().id)) q.pop(),q.push(node2(tree[x].x.id,dis));
    if (tree[x].left) ldis=calc1(tree[x].left);if(tree[x].right) rdis=calc1(tree[x].right);
    if(ldis>rdis){
        if (ldis>q.top().dis||(ldis==q.top().dis&&tree[tree[x].left].idmin<q.top().id)) query(tree[x].left);
        if (rdis>q.top().dis||(rdis==q.top().dis&&tree[tree[x].right].idmin<q.top().id)) query(tree[x].right);    
    }else{
        if (rdis>q.top().dis||(rdis==q.top().dis&&tree[tree[x].right].idmin<q.top().id)) query(tree[x].right);
        if (ldis>q.top().dis||(ldis==q.top().dis&&tree[tree[x].left].idmin<q.top().id)) query(tree[x].left);
    }
}
int main(){
    //freopen("bzoj2626.in","r",stdin);
    n=read();for (int i=0;i<2;++i) tree[0].min[i]=0x3f3f3f3f,tree[0].max[i]=-0x3f3f3f3f;
    for (int i=1;i<=n;++i) {point[i].id=i;for (int j=0;j<2;++j) point[i][j]=read();}
    build(root,1,n,0);m=read();
    for (int i=1;i<=m;++i) {
        while(!q.empty()) q.pop();
        P[0]=read();P[1]=read();k=read();
        for (int i=1;i<=k;++i) q.push(node2(0,-inf));
        query(root);printf("%d\n",q.top().id);
    }
    return 0;
}

```

---

## 作者：Karry5307 (赞：6)

### 题意

给定平面上 $n$ 个点，$m$ 次询问，每次询问给定一个点 $(x,y)$ 和一个整数 $k$，求出平面上 $n$ 个点距离 $(x,y)$ 第 $k$ 远的点是哪个。其中如果距离相同则编号小的距离更远。

$\texttt{Data Range:}1\leq n\leq 10^5,1\leq m\leq 10^4,k\leq 20$

### 题解

K-D Tree 好题。

首先考虑一个很简单的问题，给一个序列如何求第 $k$ 大。

一个时间复杂度很优的做法是类似与 nth-element 一样的实现方法，但是这个做法拓展性不强。

而一个拓展性比较强的方法是，类似与对顶堆一样开一个小根堆（注意不是大根堆）。先往这个堆里面填 $k$ 个 $-\infty$，然后扫每个元素的时候判断这个元素与堆顶的大小，如果大于堆顶的话就把堆顶弹出，并把这个数加入堆，把所有数扫完之后堆顶就是答案。

对于这个题来说，因为没有插入操作所以可以预先把树建出来，然后每一次询问找一下就好了，记得剪枝。

一个小的优化是这题只让你输出点的编号所以算距离的时候可以不用开平方。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
typedef pair<li,ll> pii;
const ll MAXN=6e5+51;
const li inf=0x3f3f3f3f3f3f3f3f;
const double alpha=0.6;
struct Node{
	ll d[2];
};
Node s[MAXN];
priority_queue<pii,vector<pii>,greater<pii> >q;
ll n,qcnt,x,y,kk,rt,dim,totn,ptr;
ll ls[MAXN],rs[MAXN],L[MAXN],R[MAXN],D[MAXN],U[MAXN];
ll sz[MAXN],g[MAXN];
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
inline bool cmp(ll x,ll y)
{
	return s[x].d[dim]<s[y].d[dim];
}
inline void update(ll node,ll x)
{
	L[node]=min(L[node],L[x]),R[node]=max(R[node],R[x]);
	D[node]=min(D[node],D[x]),U[node]=max(U[node],U[x]);
}
inline void update(ll node)
{
	sz[node]=sz[ls[node]]+sz[rs[node]]+1;
	L[node]=R[node]=s[node].d[0],U[node]=D[node]=s[node].d[1];
	ls[node]?update(node,ls[node]):(void)1;
	rs[node]?update(node,rs[node]):(void)1;
}
inline ll create(ll l,ll r,ll d)
{
	if(l>r)
	{
		return 0;
	}
	ll mid=(l+r)>>1;
	dim=d,nth_element(g+l,g+mid,g+r+1,cmp);
	ls[g[mid]]=create(l,mid-1,d^1),rs[g[mid]]=create(mid+1,r,d^1);
	return update(g[mid]),g[mid];
}
inline li dist(ll x,ll y,ll kk)
{
	li dx=max(abs(x-R[kk]),abs(x-L[kk])),dy=max(abs(y-U[kk]),abs(y-D[kk]));
	return dx*dx+dy*dy;
}
inline li dist(ll x1,ll y1,ll x2,ll y2)
{
	li dx=(x1-x2),dy=(y1-y2);
	return dx*dx+dy*dy;
}
inline void query(ll x,ll y,ll node)
{
	if(!node)
	{
		return;
	}
	pii d=(pii){dist(x,y,s[node].d[0],s[node].d[1]),-node};
	d>q.top()?q.pop(),q.push(d):(void)1;
	li dl=-inf,dr=-inf,dirl=ls[node],dirr=rs[node];
	ls[node]?dl=dist(x,y,ls[node]):1,rs[node]?dr=dist(x,y,rs[node]):1;
	dl<dr?swap(dl,dr),swap(dirl,dirr):(void)1;
	dl>=q.top().first?query(x,y,dirl):(void)1;
	dr>=q.top().first?query(x,y,dirr):(void)1;
}
int main()
{
	totn=n=read();
	for(register int i=1;i<=n;i++)
	{
		s[i].d[0]=read(),s[i].d[1]=read(),g[i]=i;
	}
	rt=create(1,n,0),qcnt=read();
	for(register int i=1;i<=qcnt;i++)
	{
		x=read(),y=read(),kk=read();
		while(!q.empty())
		{
			q.pop();
		}
		for(register int i=0;i<kk;i++)
		{
			q.push((pii){-1,1});
		}
		query(x,y,rt),printf("%d\n",-q.top().second);
	}
}
```

---

## 作者：fanypcd (赞：3)

k-D Tree 邻域查询板题。
不会的看[这里](https://oi-wiki.org/ds/kdt/)。

k-D Tree 的本质就是将数据点进行特殊的空间组织，来满足（加速）大部分的查询操作。

然后提一嘴复杂度。（参考[这篇](https://blog.csdn.net/qq_50332374/article/details/123242226)）

结论：2-d Tree 矩阵查询 **平均** $\Theta (\log n)$，**最坏** $\Theta (n ^{1 \over 2})$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + (ch - 48);
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define ll long long
#define fir first
#define sec second
#define N 100005
struct node {int x, y, id;}; node a[N];
bool cmpx(node aa, node bb) {return aa.x < bb.x;}
bool cmpy(node aa, node bb) {return aa.y < bb.y;}
ll sq(ll x) {return x * x;}
int lc[N], rc[N], L[N], R[N], D[N], U[N];
void pushup(int x) {
	L[x] = R[x] = a[x].x;
	D[x] = U[x] = a[x].y;
	if(lc[x]) {
		L[x] = min(L[x], L[lc[x]]), R[x] = max(R[x], R[lc[x]]);
		D[x] = min(D[x], D[lc[x]]), U[x] = max(U[x], U[lc[x]]);
	}
	if(rc[x]) {
		L[x] = min(L[x], L[rc[x]]), R[x] = max(R[x], R[rc[x]]);
		D[x] = min(D[x], D[rc[x]]), U[x] = max(U[x], U[rc[x]]);
	}
	return;
}
int build(int l, int r) {
	if(l > r) return 0;
	double avx = 0, avy = 0, vax = 0, vay = 0;
	for(int i = l; i <= r; i++)
		avx += a[i].x, avy += a[i].y;
	avx /= (r - l + 1), avy /= (r - l + 1);
	for(int i = l; i <= r; i++)
		vax += sq(avx - a[i].x), vay += sq(avy - a[i].y);
	int mid = (l + r) >> 1;
	if(vax > vay) nth_element(a + l, a + mid, a + r + 1, cmpx);
	else nth_element(a + l, a + mid, a + r + 1, cmpy);
	lc[mid] = build(l, mid - 1), rc[mid] = build(mid + 1, r);
	pushup(mid); return mid;
}
struct answer {int id;}; int tar;
ll dis(int x, int y) {
	if(!x || !y) return -1;
	return sq(a[x].x - a[y].x) + sq(a[x].y - a[y].y);
}
bool operator < (answer aa, answer bb) {
	ll tmpa = dis(aa.id, tar), tmpb = dis(bb.id, tar);
	if(tmpa != tmpb) return tmpa > tmpb;
	return a[aa.id].id < a[bb.id].id;
}
priority_queue<answer> q;
ll calc(int x) {
	return max(sq(L[x] - a[tar].x), sq(R[x] - a[tar].x))
	 + max(sq(D[x] - a[tar].y), sq(U[x] - a[tar].y));
}
void query(int l, int r) {
	if(l > r) return;
	int mid = (l + r) >> 1;
	if((answer){mid} < q.top()) q.pop(), q.push({mid});
	ll dl = calc(lc[mid]), dr = calc(rc[mid]), dnow = dis(q.top().id, tar);
	if(dl >= dnow && dr >= dnow) {
		if(dl > dr) {
			query(l, mid - 1); dnow = dis(q.top().id, tar);
			if(dr >= dnow) query(mid + 1, r);
		}
		else {
			query(mid + 1, r); dnow = dis(q.top().id, tar);
			if(dl >= dnow) query(l, mid - 1);
		}
	}	
	else if(dl >= dnow) query(l, mid - 1);
	else if(dr >= dnow) query(mid + 1, r);
	return;
}
int n, m, k;
signed main() {
	read(n); for(int i = 1; i <= n; i++) read(a[i].x), read(a[i].y), a[i].id = i;
	build(1, n); tar = n + 1; read(m); while(m--) {
		read(a[tar].x), read(a[tar].y), read(k);
		while(!q.empty()) q.pop();
		for(int i = 1; i <= k; i++) q.push({0});
		query(1, n); printf("%d\n", a[q.top().id].id);
	}
	return 0;
}
```

---

## 作者：zsaskk (赞：3)

[传送门](https://www.luogu.com.cn/problem/P2093)

题意：给定若干个点，求距离某个点第$k$远的点



------------


类比一下$A^*$算法，$A^*$算法可以用来求$k$短路，并且往往使用估价函数与优先队列来降低复杂度。

在$A^*$算法中，一个点第$k$次被取出，对应的结果就是$k$短路，所以我们可以开一个优先队列，存$k$大的结果动态维护。

同时使用估价函数剪枝排除无效状态。

同样类比$A^*$，估价函数要把决策集合放大，才能得到正确答案，也就是说：

~~宁可错杀100，不可放过1个~~

虽然这么说，但是无效状态还是居多，~~所以还是有效果的~~

而这里还有一种剪枝，就是估价结果更优的优先处理，这样估价不优的可能就不用处理了。

------------

建树的话，就是普通的平衡树建树，这里采用~~容易被卡的~~方法，就是每一层比较不同的维度，每层做出改变。

在每一维度内进行普通的$BST$建树即可，并维护最值方便估价。

划分左右子树直接使用库函数函数，格式：

```
nth_element(a+1,a+k,a+n+1)
```



作用是：返回$[1,n]$排序后的$a[k]$，并且小于的放前面，大于的放后面。

我最开始接触到这个函数，以为它会改变顺序，所以一无是处，~~没想到现在却需要常常使用它.....~~

~~它的原理类似快排~~，复杂度线性。

------------

```
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define int long long
#define chk_digit(c) (c>='0'&&c<='9')
inline int read() {
	reg int x=0,f=1;reg char c=getchar();
	while(!chk_digit(c)) { if(c=='-') f=-1;c=getchar(); }
	while(chk_digit(c)) x=x*10+c-'0',c=getchar(); 
	return x*f;
}
#define maxn 301000
#define inf (1ll<<58)
#define mymin(x,y) (x>=y?y:x)
#define mymax(x,y) (x>=y?x:y)
#define mid (l+r>>1)
int n,m,root,ymh;
struct kd{ int d[3],mx[3],mn[3],l,r,num; }tr[maxn],now;
inline bool operator < (kd a,kd b) { return a.d[ymh]<b.d[ymh]; }
inline void update(int root) {
	for(reg int i=0;i<=1;++i) {
		tr[root].mn[i]=mymin(tr[root].mn[i],mymin(tr[tr[root].l].mn[i],tr[tr[root].r].mn[i]));
		tr[root].mx[i]=mymax(tr[root].mx[i],mymax(tr[tr[root].l].mx[i],tr[tr[root].r].mx[i]));
	}
}
inline void build(int &x,int l,int r,int dimension) {
	ymh=dimension,x=mid;
	nth_element(tr+l,tr+x,tr+r+1);
	for(reg int i=0;i<=1;++i) tr[x].mx[i]=tr[x].mn[i]=tr[x].d[i];
	if(l<x) build(tr[x].l,l,mid-1,dimension^1);
	if(r>x) build(tr[x].r,mid+1,r,dimension^1);
	update(x);
}
struct node{ int dis,num; };
inline bool operator < (node a,node b) { return a.dis>b.dis||((a.dis==b.dis)&&(a.num<b.num)); }
priority_queue<node> q;
#define power(x) ((x)*(x))
//小心这个define，或者更稳妥的做法是写成函数 
inline int get_dis(kd a,kd b) { return power(a.d[0]-b.d[0])+power(a.d[1]-b.d[1]); }
inline int caculate(int x) {//估价函数 
	if(!x) return -100;
	int ans=0;
	for(reg int i=0;i<=1;++i) ans+=mymax(power(tr[x].mx[i]-now.d[i]),power(tr[x].mn[i]-now.d[i]));
	return ans;
}
inline void query(int x) {
	if(!x) return;
	int dl=caculate(tr[x].l),dr=caculate(tr[x].r),d=get_dis(tr[x],now);
	if(d>q.top().dis||((d==q.top().dis)&&tr[x].num<q.top().num)) q.pop(),q.push((node){d,tr[x].num});
	//只有在某个节点且合法才更新该节点的答案 
	if(dl>dr) {
		if(dl>=q.top().dis) query(tr[x].l);//按顺序更新答案 
		if(dr>=q.top().dis) query(tr[x].r);
	}
	else {
		if(dr>=q.top().dis) query(tr[x].r);
		if(dl>=q.top().dis) query(tr[x].l);
	}
}
signed main() {
	tr[0].mn[0]=tr[0].mn[1]=inf,tr[0].mx[0]=tr[0].mx[1]=-inf;
	n=read();
	for(reg int i=1;i<=n;++i) tr[i].d[0]=read(),tr[i].d[1]=read(),tr[i].num=i;
	build(root,1,n,1),m=read();
	for(reg int i=1;i<=m;++i) {
		while(q.size()) q.pop();
		now.d[0]=read(),now.d[1]=read();
		int k=read();
		for(reg int i=1;i<=k;++i) q.push((node){-1,-1});
		query(root);
		printf("%lld\n",q.top().num);
	}
}
```



---

## 作者：LastKismet (赞：1)

## 题意
题面很简洁，不作复述。

## 思路
考虑 `2DTree`，对于每个所求点，想办法找出其前 $k$ 大的距离——可以使用小根堆维护。注意题目中的特殊要求，编号小的视作距离更大，所以建议手写 `cmp` 或 `operator`。

我们考虑两种情况：
* 堆中元素不足 $k$ 个，能加就加。
* 堆中元素已有 $k$ 个，那么减枝：
     * 如果当前区间到查询元素的**理想最大距离**小与当前堆顶，直接返回。
     * 否则，尝试用当前节点更新，递归判断子区间。

递归返回之前维护堆大小，那么答案就是堆顶元素。

## 优化
不难发现直接这么写会 $\rm T$，我们每次都先递归**理想最大距离更大**的子区间，就能过了。

## 细节
在建树之后，节点编号与原编号是**不同**的，注意储存原编号。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef double db;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
template <typename Type>
using vec=vector<Type>;
template <typename Type>
using grheap=priority_queue<Type>;
template <typename Type>
using lrheap=priority_queue<Type,vector<Type>,greater<Type> >;
#define fir first
#define sec second
#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define chmax(a,b) a=max(a,b)
#define chmin(a,b) a=min(a,b)
#define dprint(x) cout<<#x<<"="<<x<<"\n"

const int inf=0x3f3f3f3f;
const ll INF=4e18;
const int mod=1e9+7/*998244353*/;

const int N=1e5+5,K=2;

struct node{
    int id;
    ll v[K];
    ll mx[K],mn[K];
    int lson,rson;
}ns[N];
int n,m;

int ak;
inline bool cmp(node a,node b){return a.v[ak]<b.v[ak];}

inline ll dis(ll a,ll b,ll c,ll d){
    return (a-c)*(a-c)+(b-d)*(b-d);
}

struct mpli{
    ll first;
    int second;
};
inline bool operator>(const mpli a,const mpli b){
    if(a.fir!=b.fir)return a.fir>b.fir;
    else return a.sec<b.sec;
}

lrheap<mpli> ans;

struct kdtree{
    inline void update(int x){
        for(int k=0;k<K;k++){
            ns[x].mx[k]=ns[x].mn[k]=ns[x].v[k];
            if(ns[x].lson)chmax(ns[x].mx[k],ns[ns[x].lson].mx[k]),chmin(ns[x].mn[k],ns[ns[x].lson].mn[k]);
            if(ns[x].rson)chmax(ns[x].mx[k],ns[ns[x].rson].mx[k]),chmin(ns[x].mn[k],ns[ns[x].rson].mn[k]);
        }
    }
    inline int build(int l,int r,int k=0){
        int m=l+r>>1;
        ak=k;nth_element(ns+l,ns+m,ns+r+1,cmp);
        if(l<m)ns[m].lson=build(l,m-1,(k+1)%K);
        if(m<r)ns[m].rson=build(m+1,r,(k+1)%K);
        update(m);
        return m;
    }
    inline ll mxdis(pii q,int x){
        return max({
            dis(q.fir,q.sec,ns[x].mx[0],ns[x].mx[1]),
            dis(q.fir,q.sec,ns[x].mx[0],ns[x].mn[1]),
            dis(q.fir,q.sec,ns[x].mn[0],ns[x].mx[1]),
            dis(q.fir,q.sec,ns[x].mn[0],ns[x].mn[1])
        });
    }
    inline void query(pii q,int x,int kk){
        if(ans.size()>=kk&&mxdis(q,x)<ans.top().fir)return;
        if(ans.size()<kk||dis(q.fir,q.sec,ns[x].v[0],ns[x].v[1])>=ans.top().fir)ans.push({dis(q.fir,q.sec,ns[x].v[0],ns[x].v[1]),ns[x].id});
        if(ns[x].lson&&ns[x].rson){
            if(mxdis(q,ns[x].lson)>mxdis(q,ns[x].rson)){
                query(q,ns[x].lson,kk);
                query(q,ns[x].rson,kk);
            }else{
                query(q,ns[x].rson,kk);
                query(q,ns[x].lson,kk);
            }
        }else if(ns[x].lson)query(q,ns[x].lson,kk);
        else if(ns[x].rson)query(q,ns[x].rson,kk);
        while(ans.size()>kk)ans.pop();
        return;
    }
}kdt;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        ns[i].id=i;
        cin>>ns[i].v[0]>>ns[i].v[1];
        ns[i].lson=ns[i].rson=0;
    }
    int rt=kdt.build(1,n);
    cin>>m;
    int a,b,c;
    while(m--){
        cin>>a>>b>>c;
        while(!ans.empty())ans.pop();
        kdt.query({a,b},rt,c);
        cout<<ans.top().sec<<"\n";
    }
    return 0;
}
```

---

## 作者：P_VICVIC_R (赞：0)

~~再不写题解又要橙回去了~~

----

### 前置知识：

[KD-Tree](https://oi-wiki.org/ds/kdt/)：一种可以**高效处理  $k$ 维空间信息**的数据结构。

### 题意：

求平面内距离给定点**第 $k$ 远**的点。

### 思路：

邻域查询的板板，类似于求最近的点，可以先找出离他最远的 $k$ 个点，然后搞个优先队列（小根堆）输出堆顶就行。

### code:

```c++
#include <bits/stdc++.h>
#define int long long 
using namespace std;
static const int N=1000000;
static const int INF=LONG_LONG_MAX;
int n,m;
int idx,Root;
struct Point{
    int cr[2];
    int id;
    inline int& operator[](int k){
        return cr[k];
    }
}P[N];
struct Node{
    int Ls,Rs;
    int Hg[2];
    int Lw[2];
    Point cr;
}T[N];

struct ans{
    int id,val;
    ans(int a=0,int b=0):id(a),val(b){}
    inline bool operator<(const ans& orh)const {
        return (val==orh.val?id<orh.id:val>orh.val);
    }
    inline bool operator>(const ans& orh)const {
        return (val==orh.val?id<orh.id:val>orh.val);
    }
};
priority_queue<ans> AnsSet;

inline void PushUp(int rt){
    for(auto i:{0,1}){
        T[rt].Hg[i]=T[rt].Lw[i]=T[rt].cr[i];
        if(T[rt].Ls){
            T[rt].Hg[i]=max(T[rt].Hg[i],T[T[rt].Ls].Hg[i]);
            T[rt].Lw[i]=min(T[rt].Lw[i],T[T[rt].Ls].Lw[i]);
        }
        if(T[rt].Rs){
            T[rt].Hg[i]=max(T[rt].Hg[i],T[T[rt].Rs].Hg[i]);
            T[rt].Lw[i]=min(T[rt].Lw[i],T[T[rt].Rs].Lw[i]);
        }
    }
}
inline int SetUp(int l,int r,int k){
    if(l>r)
        return 0;
    int rt=++idx;
    int mid=(l+r)>>1;
    auto judge=[k](Point a,Point b)->bool{return a[k]<b[k];};
    nth_element(P+l,P+mid,P+r,judge);
    T[rt].cr=P[mid];
    T[rt].Ls=SetUp(l,mid-1,k^1);
    T[rt].Rs=SetUp(mid+1,r,k^1);
    PushUp(rt);
    return rt;
}
inline int Dis(Point a,Point b){
    return 1ll*(a[0]-b[0])*(a[0]-b[0])+1ll*(a[1]-b[1])*(a[1]-b[1]);
}
inline int measure (Node T,Point Pl){
    int res=0;
    for(int i:{0,1})
		res+=(max(abs(Pl[i]-T.Hg[i]),abs(Pl[i]-T.Lw[i])))*(max(abs(Pl[i]-T.Hg[i]),abs(Pl[i]-T.Lw[i])));
    return res;
}
inline void Query(int rt,Point P){
    if(!rt)
        return ;
    ans p(T[rt].cr.id,Dis(P,T[rt].cr));
    if(p>AnsSet.top())
        AnsSet.pop(),
        AnsSet.push(p);

    int Lv=-LONG_LONG_MAX;
    int Rv=-LONG_LONG_MAX;                                
    if(T[rt].Ls)
        Lv=measure(T[T[rt].Ls],P);
    if(T[rt].Rs)
        Rv=measure(T[T[rt].Rs],P);
    if(Lv<Rv){
        if(Rv>=AnsSet.top().val)
            Query(T[rt].Rs,P);
        if(Lv>=AnsSet.top().val)
            Query(T[rt].Ls,P);
    }
    else{
        if(Lv>=AnsSet.top().val)
            Query(T[rt].Ls,P);
        if(Rv>=AnsSet.top().val)
            Query(T[rt].Rs,P);
    }
}

signed main(){
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>P[i][0]>>P[i][1];
        P[i].id=i;
    }
    Root=SetUp(1,n,0);
    cin>>m;
    while(m--){
        int k;
        Point lp;
        cin>>lp[0]>>lp[1]>>k;
        while(!AnsSet.empty())
            AnsSet.pop();
        while(k--)
            AnsSet.push(ans(0,-1));
        Query(Root,lp);
        cout<<AnsSet.top().id<<'\n';
    }
    return 0;
}
```

---

## 作者：ケロシ (赞：0)

这道题询问 $n$ 个点中离给出的点的距离第 $k$ 大的点的标号。   
想这类问题可以想到 K-D Tree 解决。  
但是题目要求第 $k$ 大的点的标号，考虑使用一个小根堆来维护前 $k$ 大点的信息。   
如果当前求出来的答案比小根堆堆顶的答案更优，那么就把旧的堆顶弹出并插入更优的答案，   
那么遍历完成后堆顶就是第 $k$ 大值。  
在计算过程中，因为需要求点的编号，所以需要在记录点和答案是需要同时记录点的编号信息。   
```cpp
const int N = 2e5 + 5;
int n, q, d[N], lc[N], rc[N];
ll ans = 2e18;
struct node {
    ll dis;
    int id;
};
bool operator < (node x, node y) {
    if(x.dis == y.dis) return x.id < y.id;
    return x.dis > y.dis;
}
priority_queue<node> pq;
struct Point {
    ll x, y;
    int id;
} s[N];
ll L[N], R[N], D[N], U[N];
ll sq(ll x) {
    return x * x;
}
ll dist(int x, int y) {
    return max(sq(s[x].x - L[y]), sq(s[x].x - R[y])) +
    max(sq(s[x].y - D[y]), sq(s[x].y - U[y]));
} 
bool cmp1(Point x, Point y) {
    return x.x < y.x;
}
bool cmp2(Point x, Point y) {
    return x.y < y.y;
}
void maintain(int x) {
    L[x] = R[x] = s[x].x;
    D[x] = U[x] = s[x].y;
    if(lc[x]) {
        chmin(L[x], L[lc[x]]);
        chmax(R[x], R[lc[x]]);
        chmin(D[x], D[lc[x]]);
        chmax(U[x], U[lc[x]]);
    }
    if(rc[x]) {
        chmin(L[x], L[rc[x]]);
        chmax(R[x], R[rc[x]]);
        chmin(D[x], D[rc[x]]);
        chmax(U[x], U[rc[x]]);
    }
}
int build(int l, int r) {
    if(l > r) return 0;
    if(l == r) {
        maintain(l);
        return l;
    }
    int mid = (l + r) >> 1;
    double avx = 0, avy = 0, vax = 0, vay = 0;
    FOR(i, l, r) {
        avx += s[i].x;
        avy += s[i].y;
    }
    avx /= (double)(r - l + 1);
    avy /= (double)(r - l + 1);
    FOR(i, l, r) {
        vax += (s[i].x - avx) * (s[i].x - avx);
        vay += (s[i].y - avy) * (s[i].y - avy);
    }
    if(vax >= vay) {
        d[mid] = 1;
        nth_element(s + l, s + mid, s + r + 1, cmp1);
    }
    else {
        d[mid] = 2;
        nth_element(s + l, s + mid, s + r + 1, cmp2);
    }
    lc[mid] = build(l, mid - 1);
    rc[mid] = build(mid + 1, r);
    maintain(mid);
    return mid;
}
void query(int l, int r) {
    if(l > r) return;
    int mid = (l + r) >> 1;
    ll res = sq(s[mid].x - s[n + 1].x) + sq(s[mid].y - s[n + 1].y);
    if(res > pq.top().dis) {
        pq.pop();
        pq.push({res, s[mid].id});
    }
    else if(res == pq.top().dis && s[mid].id < pq.top().id){
        pq.pop();
        pq.push({res, s[mid].id});
    }
    ll dl = dist(n + 1, lc[mid]);
    ll dr = dist(n + 1, rc[mid]);
    if(dl >= pq.top().dis && dr >= pq.top().dis) {
        if(dl > dr) {
            query(l, mid - 1);
            if(dr >= pq.top().dis) query(mid + 1, r);
        }
        else {
            query(mid + 1, r);
            if(dl >= pq.top().dis) query(l, mid - 1);
        }
    }
    else {
        if(dl >= pq.top().dis) query(l, mid - 1);
        if(dr >= pq.top().dis) query(mid + 1, r);
    }
}
void solve() {
    cin >> n;
    FOR(i, 1, n) {
        cin >> s[i].x >> s[i].y;
        s[i].id = i;
    }
    build(1, n);
    cin >> q;
    REP(i, q) {
        int k;
        cin >> s[n + 1].x >> s[n + 1].y >> k;
        while(!pq.empty()) pq.pop();
        REP(j, k) pq.push({0, INF});
        query(1, n);
        cout << pq.top().id << endl;
    }
}
```

---

## 作者：Llx2022 (赞：0)

# **Description**
每次给定一个点 $(px, py)$ 和一个整数 $k$，求距离 $(px, py)$ 第 $k$ 大的点的标号。

**注意**：若有多个距离相同的点，则选择标号较小的点。
# **Solution**
先看数据规模，**坐标在范围内随机分布**，肯定不会被卡的，那么我们就用 K-D Tree 就好了。


让求 $k$ 远点，并且 $k$ 的范围非常小，我们其实就可以维护一个**小根堆**，初始时先放 $k$ 个空的点，查询时进行更新，最后答案就时堆顶的元素对应的节点下标。


**以下**是 **K-D Tree** 基本操作，详细的 **K-D Tree** 操作就不解释了。


**建树**：建树时对于每个节点，我们保存子树内的边界信息，其实就是维护一下矩形的边界，与此同时每个节点还保存当前点的坐标信息。


**查询**：我们搜索我们建好的树，从根节点进入，每次先判断当前节点是否更优，与栈顶进行比较，进行答案的更新，再比较当前节点存的子树的最大值到我们要求 $(px, py)$ 的距离和堆顶（堆顶现在存放的是第 $k$ 大）比较，判断是否有必要递归子树。若子树中对应的最大值都不比堆顶更优，那么对答案必然也是没有贡献的，因为是让求 $k$ 远点肯定时越远越好，如果连当前堆顶都不如，肯定就不选了。

**注意**：坐标区间还是很大的，再求距离时可能会爆 **int**，记得开 **long long** 这样可以保证不溢出。

# **Code**

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1e5+9;
int now;
struct qqq{
    int id;
    long long val;
    qqq(int a,long long b){
        id=a;val=b;
    }
    //优先队列重载的是小于号
    bool operator<(const qqq &a)const{
        if(val==a.val) return id<a.id;
        return val>a.val;
    }
    //比较重载的是大于号
    bool operator>(const qqq &a)const{
        if(val==a.val) return id<a.id;
        return val>a.val;
    }
};
priority_queue<qqq> q;
int n,m;
int x,y,k;
struct node{
    int d[2],lc,rc,mn[2],mx[2];
    int id;
    bool operator<(const node&a) const{
        return d[now]<a.d[now];
    }
}dat[N],t[N];
int rt;
void maintain(int mid){
    for(int i=0;i<2;i++){
        t[mid].mx[i]=t[mid].mn[i]=dat[mid].d[i];
        if(t[mid].lc){
            t[mid].mn[i]=min(t[mid].mn[i],t[t[mid].lc].mn[i]);
            t[mid].mx[i]=max(t[mid].mx[i],t[t[mid].lc].mx[i]);
        }
        if(t[mid].rc){
            t[mid].mn[i]=min(t[mid].mn[i],t[t[mid].rc].mn[i]);
            t[mid].mx[i]=max(t[mid].mx[i],t[t[mid].rc].mx[i]);
        }
    }
}
//pl是维度
int build(int l,int r,int pl){
    now=pl;
    int mid=l+r>>1;
    nth_element(dat+l,dat+mid,dat+r+1);
    t[mid]=dat[mid];
    if(l<mid) t[mid].lc=build(l,mid-1,pl^1);
    if(r>mid) t[mid].rc=build(mid+1,r,pl^1);
    maintain(mid);
    return mid;
}
long long dis(int x,int y,int rt){
	long long s1=max(abs(x-t[rt].mx[0]),abs(x-t[rt].mn[0]));
	long long s2=max(abs(y-t[rt].mx[1]),abs(y-t[rt].mn[1]));
    return s1*s1+s2*s2;
}
long long getdis(int x,int y,int rt){
	return 1ll*(x-t[rt].d[0])*(x-t[rt].d[0])+1ll*(y-t[rt].d[1])*(y-t[rt].d[1]);
} 
void query(int x,int y,int rt){
    qqq tmp=qqq(t[rt].id,getdis(x,y,rt));
    if(tmp>q.top()) q.pop(),q.push(tmp);
    long long ld=-0x7f7f7f7f7f7f,rd=-0x7f7f7f7f7f7f;
    if(t[rt].lc) ld=dis(x,y,t[rt].lc);
    if(t[rt].rc) rd=dis(x,y,t[rt].rc);
    if(ld<rd){
        if(rd>=q.top().val) query(x,y,t[rt].rc);
        if(ld>=q.top().val) query(x,y,t[rt].lc);
    }
    else{
        if(ld>=q.top().val) query(x,y,t[rt].lc);
        if(rd>=q.top().val) query(x,y,t[rt].rc);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&dat[i].d[0],&dat[i].d[1]);
        dat[i].id=i;
    }
    rt=build(1,n,0);
    scanf("%d",&m);
    while(m--){
        scanf("%d%d%d",&x,&y,&k);
        while(!q.empty()) q.pop();
        for(int i=1;i<=k;i++){
            q.push(qqq(0,-1));
        }
        query(x,y,rt);
        printf("%lld\n",q.top().id);
    }
    return 0;
}
```
Upd：2023.8.29，修改了一处错误，我们维护是一个**小根堆**。


---

## 作者：Slient_QwQ (赞：0)

## Main Meaning

有 $n$ 个点的坐标 $(x_i, y_i)$，$m$ 次询问，每次输入 $(px, py)$ 和 $k$，求离点 $(px, py)$ 第 $k$ 远点的**编号**。

## Solution

二维平面？直接使用 Kd Tree。

最远的点可以直接查询，但是 $k$ 远点不行。于是考虑用小根堆维护。在查询过程中若一个节点的答案比堆顶答案更优，那么直接将堆顶弹出，替换掉，答案即为堆顶元素的编号。

剩下的就是 Kd Tree 板子了，应该没有不会的吧（逃

```cpp
/*Code By Manipula*/
#include <bits/stdc++.h>
#define endl '\n'
#define INF 0x3f3f3f3f
#define int long long
#define fi first
#define sc second
#define lb lower_bound
#define YES printf("YES\n")
#define Yes printf("Yes\n")
#define NO printf("NO\n")
#define No printf("No\n")
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define Debug(fmt, arg...) fprintf(stderr, fmt, ##arg)
#define DEBUG() debug("In Function [%s] Line %lld\n", __FUNCTION__, __LINE__) 

const int N = 4e5 + 5;

struct Point {
	int x[2], id;
	
	Point() {}
	Point(int _x, int _y, int id) : id(id) { x[0] = _x; x[1] = _y; }
} order[N];

struct QWQ {
	int dis, id;
	
	QWQ(int dis = 0, int id = 0) : dis(dis), id(id) {  }
	
	bool operator < (const QWQ &rhs) const { 
		return dis > rhs.dis || (dis == rhs.dis && id < rhs.id); 
	}
};

std::priority_queue<QWQ> q;

int TEXT, n, rt, tot, ans;

namespace KDT {
	struct Node {
		int ls, rs, L[2], R[2];
		Point P;
		
		#define ls(p) (tr[p].ls)
		#define rs(p) (tr[p].rs)
	} tr[N];
	
	void init() {
		tr[0].L[0] = tr[0].L[1] = INF;
		tr[0].R[0] = tr[0].R[1] = -1;
	}
	
	void pushup(int p) {
		auto L = tr[ls(p)], R = tr[rs(p)];
				
		for (int i = 0; i <= 1; i++) {
			tr[p].L[i] = tr[p].R[i] = tr[p].P.x[i];
			
			if (ls(p)) tr[p].L[i] = std::min(tr[p].L[i], L.L[i]);
			if (rs(p)) tr[p].L[i] = std::min(tr[p].L[i], R.L[i]);
			if (ls(p)) tr[p].R[i] = std::max(tr[p].R[i], L.R[i]);
			if (rs(p)) tr[p].R[i] = std::max(tr[p].R[i], R.R[i]);
		}
	}
	
	int Add() { return ++tot; }
	
	int Rebuild(int l, int r, int WD) {
		if (l > r) return 0;
		int mid = (l + r) >> 1, p = Add();
		
		std::nth_element(order + l, order + mid, order + r + 1, [&](Point A, Point B) { return A.x[WD] < B.x[WD]; });
		tr[p].P = order[mid];
		
		ls(p) = Rebuild(l, mid - 1, WD ^ 1);
		rs(p) = Rebuild(mid + 1, r, WD ^ 1);
		pushup(p);
		
		return p;
	}
	
	int dis(Point P1, Point P2) { return pow(P1.x[0] - P2.x[0], 2) + pow(P1.x[1] - P2.x[1], 2); }
	int mxdis(Node P1, Point P2) {
		int A = (P1.L[0] - P2.x[0]) * (P1.L[0] - P2.x[0]);
		int B = (P1.R[0] - P2.x[0]) * (P1.R[0] - P2.x[0]);
		int C = (P1.L[1] - P2.x[1]) * (P1.L[1] - P2.x[1]);
		int D = (P1.R[1] - P2.x[1]) * (P1.R[1] - P2.x[1]);
		
		return std::max(A, B) + std::max(C, D);
	}
	
	void Query(int p, Point P) {
		if (!p) return;
		
		QWQ Q = QWQ(dis(tr[p].P, P), tr[p].P.id);
		
		if (Q < q.top()) q.pop(), q.push(Q);
				
		int dL = -1, dR = -1;
				
		if (ls(p)) dL = mxdis(tr[ls(p)], P);
		if (rs(p)) dR = mxdis(tr[rs(p)], P);
		
		if (dL > dR) {
			if (dL >= q.top().dis) Query(ls(p), P);
			if (dR >= q.top().dis) Query(rs(p), P);
		}
		else {
			if (dR >= q.top().dis) Query(rs(p), P);
			if (dL >= q.top().dis) Query(ls(p), P);
		}
	}
}

signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	
	scanf("%lld", &n);
	
	KDT::init();
	
	for (int i = 1; i <= n; i++)
		scanf("%lld%lld", &order[i].x[0], &order[i].x[1]), order[i].id = i;
	
	rt = KDT::Rebuild(1, n, 0);
	
	scanf("%lld", &TEXT);
	
	while (TEXT--) {
		int x, y, k; scanf("%lld%lld%lld", &x, &y, &k);
		
		while (!q.empty()) q.pop();
		for (int i = 1; i <= k; i++) q.push(QWQ(-1, 0));
		
		KDT::Query(rt, Point(x, y, 0));
		
		printf("%lld\n", q.top().id);
	}
	
	return 0;
}
```

---

