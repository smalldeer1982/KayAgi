# [USACO14DEC] Marathon G

## 题目描述

贝茜自己是一名狂热的马拉松跑者，她喜欢为她的牛朋友们设计马拉松路线。最近，她设计了一条由 N 个检查点（1 <= N <= 100,000）组成的路线，这些检查点必须按顺序访问。

不幸的是，贝茜意识到其他牛可能没有足够的耐力跑完整条路线。因此，她想知道某些子路线需要多长时间，其中子路线是完整路线中连续的一段。更复杂的是，贝茜知道其他牛可能会因为懒惰而选择在跑子路线时跳过一个检查点——无论哪个检查点能使总旅行时间最短。然而，他们不允许跳过子路线的第一个或最后一个检查点。

为了构建最佳的马拉松路线，贝茜想研究对当前路线中的检查点位置进行更改的影响。请帮助她确定对检查点位置的某些更改将如何影响跑不同子路线所需的时间（考虑到牛可能会在跑子路线时选择省略一个检查点）。

由于路线设置在市中心的街道网格中，位于 (x1, y1) 和 (x2, y2) 的两个检查点之间的距离由 |x1-x2| + |y1-y2| 给出。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 5 
-4 4 
-5 -3 
-1 5 
-3 4 
0 5 
Q 1 5 
U 4 0 1 
U 4 -1 1 
Q 2 4 
Q 1 4 
```

### 输出

```
11 
8 
8 
```

# 题解

## 作者：Zory (赞：4)

那个，推广一下个人网站。。



http://zory.cf/2017-12/马拉松赛跑Marathon.html

## 来源和评测点

USACO14DEC Gold


[Luogu3113](https://daniu.luogu.org/problemnew/show/3113)

## 题目

**【题目大意】**

N个点的路线(1<=N<=100,000)，必须按顺序经过。


询问特定的子路线需要多长时间才能跑完，

其中的子路线是从完整路线的检查点中截取的的连续子序列。


牛可能会选择在任何时候跳过一个检查点，但不允许在子路线中跳过第一个或最后一个点


可能修改点的坐标


由于该课程设置在市中心的街道网络中，

两个点之间的距离(x1,y1)和(x2,y2)是由|x1-x2|+|y1-y2|得出的。
**【输入格式】**

第一行N和Q (1<=Q<=100,000).


下面N行 每个点的坐标(x,y)，大小范围是-1000..1000

下面Q行 每行一个操作

"U I X Y" 修改 点I (1<=I<=N) 的坐标为(X, Y).

"Q I J" 询问从I到J的最短距离（可以跳过除起点、终点外的其他点）(I <= J)

**【输出格式】**

每个Q输出距离值

**【输入样例】**

5 5
-4 4
-5 -3
-1 5
-3 4
0 5
Q 1 5
U 4 0 1

U 4 -1 1

Q 2 4
Q 1 4

**【输出样例】**

11
8
8

## 分析

使用线段树维护两个完全不同的信息。

值1是每个节点到上一个节点的距离

值2是每个节点被忽略后的收益（一般是负数）

维护值1的和、值2的最小值


每次修改影响两个值1，三个值2


信息的维护用线段树达到log，树状数组则比较麻烦


玄学AC之

本来线段树不忽略编号1，wa几个点都是个位数级别差异

后来想着顺便加速（因为编号1从来不用），结果AC

如果有人知道，可以在讨论区评论一下


## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
ll myabs(ll x) {return x>0?x:-x;}
ll mymin(ll x,ll y) {return x<y?x:y;}

const int MAXN=110000;
int n;

struct nod
{
    int l,r,mid,lc,rc;
    ll s,mi;//分别维护值1的和、值2的最小值
}s[MAXN*2];
int ln=0;
int build(int l,int r)
{
    int t=++ln;
    s[t].l=l;s[t].r=r;s[t].mid=(l+r)>>1;
    if(l<r)
    {
        s[t].lc=build(l,s[t].mid);
        s[t].rc=build(s[t].mid+1,r);
    }
    return t;
}
void change1(int w,int x,ll c)
{
    if(s[w].l==s[w].r)
    {
        s[w].s=c;
        return;
    }
    int lc=s[w].lc,rc=s[w].rc;
    if(x<=s[w].mid) change1(lc,x,c);
    else change1(rc,x,c);
    s[w].s=s[lc].s+s[rc].s;
}
void change2(int w,int x,ll c)
{
    if(s[w].l==s[w].r)
    {
        s[w].mi=c;
        return;
    }
    int lc=s[w].lc,rc=s[w].rc;
    if(x<=s[w].mid) change2(lc,x,c);
    else change2(rc,x,c);
    s[w].mi=mymin(s[lc].mi,s[rc].mi);
}
ll ask1(int w,int l,int r)
{
    if(s[w].l==l and s[w].r==r) return s[w].s;
    int lc=s[w].lc,rc=s[w].rc;
    if(r<=s[w].mid) return ask1(lc,l,r);
    if(l>s[w].mid) return ask1(rc,l,r);
    return ask1(lc,l,s[w].mid)+ask1(rc,s[w].mid+1,r);
}
ll ask2(int w,int l,int r)
{
    if(l>r) return 0;
    if(s[w].l==l and s[w].r==r) return s[w].mi;
    int lc=s[w].lc,rc=s[w].rc;
    if(r<=s[w].mid) return ask2(lc,l,r);
    if(l>s[w].mid) return ask2(rc,l,r);
    return mymin(ask2(lc,l,s[w].mid),ask2(rc,s[w].mid+1,r));
}
//值1是每个节点到上一个节点的距离
//值2是每个节点被忽略后的收益（一般是负数）

int xx[MAXN],yy[MAXN];
ll get(int x,int sf)//与往前sf个节点的距离
{
    return myabs(xx[x]-xx[x-sf])+myabs(yy[x]-yy[x-sf]);
}

ll p[MAXN];//顺便存储值
char ss[10];
int main()
{
    int q;scanf("%d%d",&n,&q);
    build(1,n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&xx[i],&yy[i]);
        if(i==1) continue;
        change1(1,i-1,p[i]=get(i,1));
    }
    for(int i=2;i<=n-1;i++) change2(1,i-1,get(i+1,2)-p[i]-p[i+1]);
    
    while(q--)
    {
        scanf("%s",ss);
        if(ss[0]=='Q')
        {
            int x,y;scanf("%d%d",&x,&y);
            printf("%lld\n",ask1(1,x+1-1,y-1)+ask2(1,x+1-1,y-1-1));
        }
        else
        {
            int a;scanf("%d",&a);
            scanf("%d%d",&xx[a],&yy[a]);
            
            //修改值1两处
            change1(1,a-1,p[a]=get(a,1));
            change1(1,a+1-1,p[a+1]=get(a+1,1));
            
            //对应值2三处
            change2(1,a-1-1,get(a,2)-p[a-1]-p[a]);
            change2(1,a-1,get(a+1,2)-p[a]-p[a+1]);
            change2(1,a+1-1,get(a+2,2)-p[a+1]-p[a+2]);
        }
    }
}
```

---

## 作者：DengDuck (赞：2)

这道题我们发现重点在于维护出最优的点，维护出路径的长度。

我们可以维护出不走某个点对路径长度的影响，对于修改一个点，相当于修改了这个点和相邻两个点的影响值，我们发现这相当于单点修改，区间查询。

对于维护路径长度就更简单了，我们用线段树存储每条边的长度，求区间和即可，也是单点修改，区间查询。

我们发现在点已知，方向已知的情况下，求出边长和影响值都是 $\mathcal O(1)$，因此我们相当于要在直接修改值的情况下维护区间最小值和区间和。

所以直接上线段树即可，对于修改的值，我们可以求出之后嗯造到线段树里即可。

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5+5;
const LL inf=1e15;
LL n,m,x[N],y[N],dis[N],chan[N],l,a,b;
char c[N];
struct node
{
	LL l,r,sum,mn;
}t[N*15];
LL cal(LL i,LL j)
{
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}
void build(LL pos,LL l,LL r)
{
	t[pos].l=l,t[pos].r=r;
	if(l==r)
	{
		t[pos].sum=dis[l];
		t[pos].mn=chan[l];
		return;
	}
	LL mid=(l+r)/2;
	build(pos*2,l,mid),build(pos*2+1,mid+1,r);
	t[pos].sum=t[pos*2].sum+t[pos*2+1].sum;
	t[pos].mn=min(t[pos*2].mn,t[pos*2+1].mn);
}
LL querysum(LL pos,LL l,LL r)
{
	if(r<t[pos].l||t[pos].r<l)return 0;
	if(l<=t[pos].l&&t[pos].r<=r)return t[pos].sum;
	return querysum(pos*2,l,r)+querysum(pos*2+1,l,r);
}
LL querymn(LL pos,LL l,LL r)
{
	if(r<t[pos].l||t[pos].r<l)return inf;
	if(l<=t[pos].l&&t[pos].r<=r)return t[pos].mn;
	return min(querymn(pos*2,l,r),querymn(pos*2+1,l,r));
}
void updsum(LL pos,LL x)
{
	if(x<t[pos].l||t[pos].r<x)return;
	if(t[pos].l==x&&x==t[pos].r)
	{
		t[pos].sum=dis[x];
		return;
	}
	updsum(pos*2,x),updsum(pos*2+1,x);
	t[pos].sum=t[pos*2].sum+t[pos*2+1].sum;
}
void updmn(LL pos,LL x)
{
	if(x<t[pos].l||t[pos].r<x)return;
	if(t[pos].l==x&&x==t[pos].r)
	{
		t[pos].mn=chan[x];
		return;
	}
	updmn(pos*2,x),updmn(pos*2+1,x);
	t[pos].mn=min(t[pos*2].mn,t[pos*2+1].mn);
} 
void upd(LL x)
{
	if(x==0||x==n+1)return;
	chan[x]=-dis[x-1]-dis[x]+cal(x-1,x+1);
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&x[i],&y[i]);
		dis[i-1]=cal(i,i-1);
	}
	for(int i=2;i<=n-1;i++)
	{
		upd(i);
	}
	build(1,1,n);
	while(m--)
	{
		scanf("%s",c);
		if(c[0]=='U')
		{
			scanf("%lld%lld%lld",&l,&a,&b);
			x[l]=a,y[l]=b;
			dis[l-1]=cal(l,l-1),dis[l]=cal(l,l+1);
			upd(l-1),upd(l),upd(l+1);
			updsum(1,l-1),updsum(1,l);
			updmn(1,l-1),updmn(1,l),updmn(1,l+1);
		}
		if(c[0]=='Q')
		{
			scanf("%lld%lld",&a,&b);
			printf("%lld\n",querysum(1,a,b-1)+querymn(1,a+1,b-1));
		}
	}
}
```

---

## 作者：普通的名字 (赞：1)

使用两个线段树维护。

记 $\operatorname{dis}(i,j)$ 表示点 $i$ 与点 $j$ 之间的距离。

线段树 $1$ 维护连续两个点之间的距离的和。下标 $x$ 存 $\operatorname{dis}(x,x+1)$。

线段树 $2$ 维护跳过某个点与不跳过二者距离的差的最小值。下标 $x$ 存 $\operatorname{dis}(x-1,x+1)-\operatorname{dis}(x-1,x)-\operatorname{dis}(x,x+1)$。

对于操作一，在线段树 $1$ 对下标 $x$ 和 $x-1$ 修改。在线段树 $2$ 对下标 $x-1,x,x+1$ 修改（如果可以的话）。具体见代码。

对于操作二，直接查询 $l\sim r$ 之间的和再加上跳过某个点所变化的最小值。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=9e18;
const int N=1e5+1;
int n,q;
ll tr[N<<2],tr1[N<<2];
struct node
{
    ll x,y;
}a[N];
ll dis(node a,node b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}
void build(int rt,int l,int r)
{
    if(l==r){
        tr[rt]=dis(a[l],a[l+1]);
        return;
    }
    int mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    tr[rt]=tr[rt<<1]+tr[rt<<1|1];
}
void build1(int rt,int l,int r)
{
    if(l==r){
        tr1[rt]=dis(a[l-1],a[l+1])-dis(a[l-1],a[l])-dis(a[l],a[l+1]);
        return;
    }
    int mid=l+r>>1;
    build1(rt<<1,l,mid);
    build1(rt<<1|1,mid+1,r);
    tr1[rt]=min(tr1[rt<<1],tr1[rt<<1|1]);
}
void update(int rt,int l,int r,int x,int d)
{
    if(l==r){
        tr[rt]+=d;
        return;
    }
    int mid=l+r>>1;
    if(x<=mid) update(rt<<1,l,mid,x,d);
    else update(rt<<1|1,mid+1,r,x,d);
    tr[rt]=tr[rt<<1]+tr[rt<<1|1];
}
void update1(int rt,int l,int r,int x,int d)
{
    if(l==r){
        tr1[rt]+=d;
        return;
    }
    int mid=l+r>>1;
    if(x<=mid) update1(rt<<1,l,mid,x,d);
    else update1(rt<<1|1,mid+1,r,x,d);
    tr1[rt]=min(tr1[rt<<1],tr1[rt<<1|1]);
}
ll query(int rt,int l,int r,int x,int y)
{
    if(x>y) return 0;
    if(r<x||y<l) return 0;
    if(x<=l&&r<=y) return tr[rt];
    int mid=l+r>>1;
    return query(rt<<1,l,mid,x,y)+query(rt<<1|1,mid+1,r,x,y);
}
ll query1(int rt,int l,int r,int x,int y)
{
    if(x>y) return 0;
    if(r<x||y<l) return INF;
    if(x<=l&&r<=y) return tr1[rt];
    int mid=l+r>>1;
    return min(query1(rt<<1,l,mid,x,y),query1(rt<<1|1,mid+1,r,x,y));
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
    build(1,1,n-1);
    build1(1,2,n-1);
    for(int i=1,x,y,z;i<=q;i++){
        char s[1];
        scanf("%s%d%d",s,&x,&y);
        if(s[0]=='U'){
            scanf("%d",&z);
            if(x!=n) update(1,1,n-1,x,dis({y,z},a[x+1])-dis(a[x],a[x+1]));//线段树1对下标x修改
            if(x!=1) update(1,1,n-1,x-1,dis({y,z},a[x-1])-dis(a[x],a[x-1]));//线段树1对下标x-1修改
            if(x<=n-2） update1(1,2,n-1,x+1,dis({y,z},a[x+2])-dis({y,z},a[x+1])-dis(a[x+1],a[x+2])-(dis(a[x],a[x+2])-dis(a[x],a[x+1])-dis(a[x+2],a[x+1])));
            //线段树2对下标x+1修改
            if(1<x&&x<n) update1(1,2,n-1,x,dis(a[x-1],a[x+1])-dis(a[x-1],{y,z})-dis({y,z},a[x+1])-(dis(a[x-1],a[x+1])-dis(a[x-1],a[x])-dis(a[x],a[x+1])));
            //线段树2对下标x修改
            if(x>=3) update1(1,2,n-1,x-1,dis({y,z},a[x-2])-dis({y,z},a[x-1])-dis(a[x-1],a[x-2])-(dis(a[x],a[x-2])-dis(a[x],a[x-1])-dis(a[x-1],a[x-2])));
            //线段树2对下标x-1修改
            a[x]={y,z};
        }
        else printf("%lld\n",query(1,1,n-1,x,y-1)+query1(1,2,n-1,x+1,y-1));
    }
}
```

---

## 作者：jyz666 (赞：1)

# 题解 P3113 【[USACO14DEC]Marathon G】

[传送门](https://www.luogu.com.cn/problem/P3113)

最后几篇之一...(平静）

裸的线段树a...

该题包括询问与更新，很容易想到要用数据结构维护。 

因为奶牛要按序经过检查点并且询问的是“子序列”，考虑使用线段树维护。

线段树的每个叶子结点维护 $l$ 与 $l+1$两点间距离$sum$。

考虑如何维护“跳过检查点的情况”，我们用维护点 $l$ 的叶子结点来维护跳过 $l+1$ 这个点直接到达 $l+2$点所能缩短的距离$del$。

这样$Pushup$时只需把儿子的$sum$加起来，把儿子的$del$取个$max$就行。更新时单点修改即可。

### 上代码》》

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
int n,q;
int px[MAXN],py[MAXN];
int sum[MAXN<<2],del[MAXN<<2];
char ch[5];
inline int Getd(int a,int b){
    return fabs(px[a]-px[b])+fabs(py[a]-py[b]);
}
inline void Build(int k,int l,int r){
    if(l==r){
        if(l<n-1) del[k]=Getd(l,l+1)+Getd(l+1,l+2)-Getd(l,l+2);
        else del[k]=0;
        if(l<n) sum[k]=Getd(l,l+1);
        else sum[k]=0;
        return;
    }
    int mid=(l+r)>>1;    
    Build(k<<1,l,mid);
    Build(k<<1|1,mid+1,r);
    sum[k]=sum[k<<1]+sum[k<<1|1];
    del[k]=max(del[k<<1],del[k<<1|1]);
}
inline int Query_sum(int k,int l,int r,int x,int y){
    if(l>y||r<x) return 0;
    if(x<=l&&r<=y) return sum[k];
    int mid=(l+r)>>1;
    return Query_sum(k<<1,l,mid,x,y)+Query_sum(k<<1|1,mid+1,r,x,y);
}
inline int Query_del(int k,int l,int r,int x,int y){
    if(l>y||r<x) return 0;
    if(x<=l&&r<=y) return del[k];
    int mid=(l+r)>>1;
    return max(Query_del(k<<1,l,mid,x,y),Query_del(k<<1|1,mid+1,r,x,y));
} 
inline void Update_sum(int k,int l,int r,int x){
    if(l==r){
        if(l>=1&&l<n) sum[k]=Getd(l,l+1);    
        else sum[k]=0;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) Update_sum(k<<1,l,mid,x);
    else Update_sum(k<<1|1,mid+1,r,x);
    sum[k]=sum[k<<1]+sum[k<<1|1];
}
inline void Update_del(int k,int l,int r,int x){
    if(l==r){
        if(l>=1&&l<n-1) del[k]=Getd(l,l+1)+Getd(l+1,l+2)-Getd(l,l+2);
        else del[k]=0;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) Update_del(k<<1,l,mid,x);
    else Update_del(k<<1|1,mid+1,r,x);
    del[k]=max(del[k<<1],del[k<<1|1]);
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&px[i],&py[i]);
    Build(1,1,n);
    for(int i=1,p1,p2,p3;i<=q;++i){
        scanf("%s",ch);
        if(ch[0]=='Q'){
            scanf("%d%d",&p1,&p2);
            --p2;
            int res=Query_sum(1,1,n,p1,p2);
            --p2;
            res-=Query_del(1,1,n,p1,p2);
            printf("%d\n",res);
        }
        else{
            scanf("%d%d%d",&p1,&p2,&p3);
            px[p1]=p2;
            py[p1]=p3;
            for(int j=p1-1;j<=p1;++j)
                Update_sum(1,1,n,j);
            for(int j=p1-2;j<=p1;++j)
                Update_del(1,1,n,j);
        }
    }
    return 0;
} 

```

芜湖，文化课冲冲冲~


---

## 作者：cly312 (赞：0)

用线段树维护子路径的长度和这条子路径上删除一个点能够减少的最大距离。

那么，修改就修改线段树上对应位置的值，查询就求这一段子路径的距离和子路径上删除一个点能够减少的最大距离，两者相减即可得到答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int maxn=145141;
int n,q;
pii mat[maxn];
int delta[2*maxn];
int dist[2*maxn];
int qa,qb;
int getd(int a,int b){
	return abs(mat[a].first-mat[b].first)+abs(mat[a].second-mat[b].second);
}
void build(int rt,int a,int b){
	if(a>b)return;
	if(a==b){
		if(a<n-1)delta[rt]=getd(a,a+1)+getd(a+1,a+2)-getd(a,a+2);
		else delta[rt]=0;
		if(a<n)dist[rt]=getd(a,a+1);
		else dist[rt]=0;
		return;
	}
	int mid=(a+b)/2;
	build(rt*2,a,mid);
	build(rt*2+1,mid+1,b);
	delta[rt]=max(delta[rt*2],delta[rt*2+1]);
	dist[rt]=dist[rt*2]+dist[rt*2+1];
}
int query_dist(int rt,int a,int b){
	if(a>qb||b<qa)return 0;
	if(qa<=a&&b<=qb)return dist[rt];
	int mid=(a+b)/2;
	return query_dist(rt*2,a,mid)+query_dist(rt*2+1,mid+1,b);
}

int query_delta(int rt,int a,int b){
	if(a>qb||b<qa)return 0;
	if(qa<=a&&b<=qb)return delta[rt];
	int mid=(a+b)/2;
	return max(query_delta(rt*2,a,mid),query_delta(rt*2+1,mid+1,b));
}

void update_dist(int rt,int a,int b){
	if(a>qb||b<qa)return;
	if(qa<=a&&b<=qb){
		if(a>=1&&a<n)dist[rt]=getd(a,a+1);
		else dist[rt]=0;
		return;
	}
	int mid=(a+b)/2;
	update_dist(rt*2,a,mid);
	update_dist(rt*2+1,mid+1,b);
	dist[rt]=dist[rt*2]+dist[rt*2+1];
}
void update_delta(int rt,int a,int b){
	if(a>qb||b<qa)return;
	if(qa<=a&&b<=qb){
		if(a>=1&&a<n-1)delta[rt]=getd(a,a+1)+getd(a+1,a+2)-getd(a,a+2);
		else delta[rt]=0;
		return;
	}
	int mid=(a+b)/2;
	update_delta(rt*2,a,mid);
	update_delta(rt*2+1,mid+1,b);
	delta[rt]=max(delta[rt*2],delta[rt*2+1]);
}

int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>mat[i].first>>mat[i].second;
	}
	build(1,1,n);
	for(int i=0;i<q;i++){
		char c;
		cin>>c;
		if(c=='Q'){
			cin>>qa>>qb;
			qb--;
			int tot=query_dist(1,1,n);
			qb--;
			int del=query_delta(1,1,n);
			cout<<tot-del<<'\n'; 
		}else{
			int ix,pa,pb;
			cin>>ix>>pa>>pb; 
			mat[ix].first=pa;
			mat[ix].second=pb;
			for(int j=ix-1;j<=ix;j++){
				qa=j;
				qb=j;
				update_dist(1,1,n);
			}
			for(int j=ix-2;j<=ix;j++){
				qa=j;
				qb=j;
				update_delta(1,1,n);
			}
		}
	}
}
```

---

