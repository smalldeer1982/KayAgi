# [USACO05DEC] Cleaning Shifts S

## 题目描述

约翰的奶牛们从小娇生惯养，她们无法容忍牛棚里的任何脏东西。约翰发现，如果要使这群有洁癖的奶牛满意，他不得不雇佣她们中的一些来清扫牛棚，约翰的奶牛中有 $ N(1 \leq N \leq 10000) $ 头愿意通过清扫牛棚来挣一些零花钱。

由于在某个时段中奶牛们会在牛棚里随时随地地乱扔垃圾，自然地，她们要求在这段时间里，无论什么时候至少要有一头奶牛正在打扫。需要打扫的时段从某一天的第 $ M $ 秒开始，到第 $ E $ 秒结束 $ (0 \leq M \leq E \leq 86399) $。注意这里的秒是指时间段而不是时间点，也就是说，每天需要打扫的总时间是 $ E-M+1 $ 秒。

约翰已经从每头牛那里得到了她们愿意接受的工作计划：对于某一头牛，她每天都愿意在笫 $ T_1 \ldots T_2 $ 秒的时间段内工作 $ (M \leq T_1 \leq T_2 \leq E) $ ，所要求的报酬是 $ S $ 美元 $ (0 \leq S \leq 500000) $。与需打扫时段的描述一样，如果一头奶牛愿意工作的时段是每天的第 $ 10 \ldots 20 $ 秒，那她总共工作的时间是 $ 11 $ 秒，而不是 $ 10 $ 秒。

约翰一旦决定雇佣某一头奶牛，就必须付给她全额的工资，而不能只让她工作一段时间，然后再按这段时间在她愿意工作的总时间中所占的百分比来决定她的工资。现在请你帮约翰决定该雇佣哪些奶牛以保持牛棚的清洁，当然，在能让奶牛们满意的前提下，约翰希望使总花费尽量小。

## 说明/提示

约翰有 $ 3 $ 头牛，牛棚在第 $ 0 $ 秒到第 $ 4 $ 秒之间需要打扫。 约翰雇佣前两头牛清扫牛棚，可以只花 $ 5 $ 美元就完成一整天的清扫。


## 样例 #1

### 输入

```
3 0 4
0 2 3
3 4 2
0 0 1```

### 输出

```
5```

# 题解

## 作者：小菜鸟 (赞：67)

大多数人用的线段树，好写好调的最短路居然没什么人写？

最短路的唯一一篇题解没判无解，码风毒瘤？

是时候来一篇认真的最短路题解了！

考虑转化题意。

要让起点到终点之间的全部点被覆盖，

我们就可以把每一头奶牛视为从起始时间到终止时间连一条边权为工资的边。

同时，每一个时间点向前一条时间点连一条边权为零的边。

~~感性理解一下，~~ 我们发现用这种方式建图，当某个点能够被到达时，从起点到它之间的每一个点都必定已被覆盖。

因为对任何一个点而言，只有当一条起点被覆盖的边以它为终点或越过它，它才是被覆盖的；而一条边的起点要被覆盖，同样要满足上述条件。以此类推，从起点到它之间的所有点都应该被覆盖了。

于是当终点能被到达时，就满足了所有时间点都被覆盖的要求。

由于向后的边权就是工资，向前的边权为零不影响答案，

所以起点到终点的最短路就是答案。。。

终点无法到达就是无解。。。

还有一点很重要，题中给的是时间点，而这个算法需要时间段。

那么我们把每条边的终点加一，就把一个时间点拆出了起点和终点，变成了时间段。

于是代码就出来了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

char gc()
{
    static char buf[1<<16],*p1=buf,*p2=buf;
    if(p1==p2)
    {
        p2=(p1=buf)+fread(buf,1,1<<16,stdin);
        if(p1==p2)return EOF;
    }
    return *p1++;
}

//#define gc getchar

template<typename _Tp>
void read(_Tp& x)
{
    x=0;
    char c=gc();
    while(c<'0'||c>'9')c=gc();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=gc();
    }
}

const int N=100005,M=300005;

int head[N];
long long dis[N];
bool vis[N];

struct Edge
{
    int next,to;
    long long w;
};
Edge E[M];
void add(int u,int v,int w)
{
    static int tot=0;
    E[++tot].next=head[u];
    E[tot].to=v;
    E[tot].w=w;
    head[u]=tot;
}

typedef std::pair<long long,int> Node;

void dijkstra(int s)
{
    memset(dis,0x3f,sizeof(dis));
    std::priority_queue<Node,std::vector<Node>,std::greater<Node> > q;
    dis[s]=0;
    q.push(Node(0,s));
    while(!q.empty())
    {
        int u=q.top().second;
        if(vis[u])
        {
            q.pop();
            continue;
        }
        q.pop();
        vis[u]=1;
        for(int i=head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(dis[v]>dis[u]+E[i].w)
            {
                dis[v]=dis[u]+E[i].w;
                q.push(Node(dis[v],v));
            }
        }
    }
}

int main()
{
    int n,S,E;
    read(n),read(S),read(E);
    for(int i=S;i<E;++i)
    {
        add(i+1,i,0);
    }
    for(int i=0;i<n;++i)
    {
        int u,v,w;
        read(u),read(v),read(w);
        if(u<S)u=S;
        if(v>E)v=E;
        add(u,v+1,w);
    }
    dijkstra(S);
    printf("%lld",dis[E+1]==0x3f3f3f3f3f3f3f3f?-1:dis[E+1]);
}

```



---

## 作者：Froggy (赞：22)

### 数据结构优化DP

~~线段树是什么,我不知道~~

所以搞了个$fhq \ Treap$

什么?不知道?不会?左转某谷日报,右转平衡树模板题

$dp_{i}$表示覆盖$[L,i]$的最小花费,初始化$\ \ \ dp_{L-1}=0$

把牛按$T2$从小到大排序

设目前是第$i$头牛,存牛的数据的数组为$a$

$dp_{a[i].T2}= \min\limits_{a[i].T1-1 \le j \le a[i].T2-1} \{dp_{j}\}+a[i].s$

这是$O(n^2)$

取区间最小值显然可以用数据结构优化

线段树,emm...

NO

用$fhq \ Treap$

因为只用存有用的位置,不用把每个位置都开了,缩小了常数和空间

如果$n$很大,$fhq \ Treap$就有它的好处了:**不用离散化**

每个节点只用记录所拥有子树的最小值即可

$O(n \log n)$

写个插入和取区间最小值即可:

插入:

```cpp
void Insert(int pos,int val){
	int l,r;
	Split(root,pos-1,l,r);
	root=Merge(Merge(l,NewNode(pos,val)),r);
}
```

取区间最小值:

```cpp
int Ask(int x,int y){
	int l,p,r;
	Split(root,y,l,r);
	Split(l,x-1,l,p);
	int ans;
	if(!p)ans=-1;
	else ans=t[p].mn;
	root=Merge(Merge(l,p),r);
	return ans;
}
```

*Code:* ~~长长长...~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define N 200010
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,L,R,dp[N],root,cnt;
struct Cow{
	int l,r,s;
}a[N];
bool cmp(Cow x,Cow y){
	return x.r<y.r;
}
struct fhq_node{
	int key,ch[2],mn,val,pos,siz;
}t[N];
void update(int k){
	t[k].mn=t[k].val;
	t[k].siz=t[t[k].ch[0]].siz+t[t[k].ch[1]].siz+1;
	if(t[k].ch[0])t[k].mn=min(t[t[k].ch[0]].mn,t[k].mn);
	if(t[k].ch[1])t[k].mn=min(t[t[k].ch[1]].mn,t[k].mn);
} 
int NewNode(int pos,int val){
	int k=++cnt;
	t[k].siz=1;
	t[k].val=t[k].mn=val;
	t[k].pos=pos;
	t[k].ch[1]=t[k].ch[0]=0;
	t[k].key=rand();
	return k;
}
int Merge(int l,int r){
	if(!l||!r)return l+r;
	if(t[l].key<t[r].key){
		t[l].ch[1]=Merge(t[l].ch[1],r);
		update(l);
		return l;
	}
	else{
		t[r].ch[0]=Merge(l,t[r].ch[0]);
		update(r);
		return r;
	}
}
void Split(int k,int data,int &l,int &r){
	if(!k){
		l=r=0;
		return ;
	}
	if(t[k].pos<=data){
		l=k;
		Split(t[k].ch[1],data,t[k].ch[1],r);
	}
	else{
		r=k;
		Split(t[k].ch[0],data,l,t[k].ch[0]);
	}
	update(k);
}
void Insert(int pos,int val){
	int l,r;
	Split(root,pos-1,l,r);
	root=Merge(Merge(l,NewNode(pos,val)),r);
}
int Ask(int x,int y){
	int l,p,r;
	Split(root,y,l,r);
	Split(l,x-1,l,p);
	int ans;
	if(!p)ans=-1;
	else ans=t[p].mn;
	root=Merge(Merge(l,p),r);
	return ans;
}
int main(){
	memset(dp,0x3f,sizeof(dp));
	srand(time(0));
	n=read();L=read()+1,R=read()+1;
	root=NewNode(L-1,0);
	for(int i=1;i<=n;i++){
		a[i].l=read()+1,a[i].r=read()+1,a[i].s=read();
	}
	
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		int tmp=Ask(a[i].l-1,a[i].r-1);
		if(tmp==-1){
			continue;
		}
		dp[a[i].r]=tmp+a[i].s;
		Insert(a[i].r,dp[a[i].r]);
	}
	int ans=999999999;
	for(int i=R;i<=a[n].r;i++){
		ans=min(ans,dp[i]);
	} 
	if(ans==999999999){
		cout<<-1<<endl;
	} 
	else cout<<ans<<endl;
	return 0;
}

```



---

## 作者：zhylj (赞：21)

更好体验见博客 [https://www.cnblogs.com/zhylj/p/10387852.html](https://www.cnblogs.com/zhylj/p/10387852.html)

### 题目

给定 $n$ 个区间 $[a_i, b_i]$, 花费为 $c_i$, 求覆盖 $[L, R]$ 区间的所有整数的最小花费. $0\le n \le 10^4, 0\le L,R\le 86399$

### 分析

一道很水的题目.

设 $f(i)$ 代表目前选择了第 $i$ 个区间, 且第 $i$ 个区间以前的的所有数都选择到了.

易得:
$$
f(i) = \min_{b_j > a_i, b_i < b_j} f(j) + c_i
$$
一看, 这不就是裸的二维偏序 (其实我并不知道二维偏序的定义是啥).

先把区间按 $b_i$ 排序, 得到:
$$
f(i) = \min_{b_j > a_i} f(j) + c_i
$$
显然有:
$$
b_j > a_i \Rightarrow X-b_j < X-a_i
$$
其中 $X$ 随便取一个较大的值.

发现这个东西只做了单点减少和前缀最小值.

可以用树状数组维护, 时间复杂度 $O(R\log n)$.

$92\ ms$ 就过了.

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int kMaxSize = 1e6 + 5, inf = 0x3f3f3f3f;

int s[kMaxSize + 233], n;

void Modify(int x, int y) {
	x = kMaxSize - x;
	while(x <= kMaxSize) {
		s[x] = std::min(s[x], y);
		x += x & -x;
	}
}

int Query(int x) {
	x = kMaxSize - x;
	int ret = inf;
	while(x > 0) {
		ret = std::min(s[x], ret);
		x -= x & -x;
	}
	return ret;
}

struct Struct {
	int a, b, c;
} p[kMaxSize];

bool cmp(Struct x, Struct y) {
	return x.b < y.b;
}

int f[kMaxSize], ans = inf;
int main() {
	memset(s, 0x3f, sizeof(s));
	memset(f, 0x3f, sizeof(f));
	int l, r;
	scanf("%d%d%d", &n, &l, &r);
	for(int i = 1; i <= n; i++)
		scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
	std::sort(p + 1, p + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		if(p[i].a > l) f[i] = Query(p[i].a - 1) + p[i].c;
		else f[i] = p[i].c;
		Modify(p[i].b, f[i]);
		if(p[i].b >= r) ans = std::min(ans, f[i]);
	}
	if(ans >= inf) printf("-1");
	else printf("%d", ans);
	return 0;
}
```

---

## 作者：追梦_Chen (赞：19)

# 这里推荐一种数据结构优化DP的写法,
我们先把该题目转换成一个**带权值的线段覆盖**问题：


给定一个区间[l,r]，接着再给n条带权值的边，边的左端点为$a_i$, 右端点为$b_i$,使用该边的代价为$c_i$



------------


### 我们用f[x]表示覆盖[l,x]的最小代价
排序，按 $b_i$ 的值升序排序，从 $b_1$ 到 $b_n$ 遍历一遍，
我们能推出一个状态转移方程:$$f[b_i]=min ({f[x]},f[b_i])+c_i$$

$f[x]$的含义是：数组f在区间$[a_i-1,b_i]$的最小值

# 证明

我们设上一段的左端点为p,右端点为q，如果区间能够被完全覆盖那么$a_{i-1}$一定小于等于q，而上一段的 f[q] 已经求出来了，根据无后效性，数组f在区间$[a_i-1,b_i]$的最小值就能由f[q]转移过来了；如果不能覆盖，该区间的最小值会是一个无穷大的值，输出-1，程序结束。


# 技巧
```cpp
如果我们直接朴素（暴力）的来找数组f在区间a[i]-1到b[i]的最小值的话，肯定超时，于是我们可以用线段树来实现单点修改，区间查询的功能~
```

# 放代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;
const int maxn=251000;
int n,l,r;
int f[maxn];
struct node{
    int a,b,c;
}cow[maxn];
struct tree{
    int l,r,dat;
}t[maxn*4]; 
bool cmp(node a,node b){
    return a.b<b.b;
}//按b的值升序排序 
void build(int p,int l,int r){
    t[p].l=l,t[p].r=r;
    if(l==r){
        t[p].dat=f[l];
        return;
    }
    int mid=(l+r)/2;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    t[p].dat=min(t[p*2].dat,t[p*2+1].dat); 
}//建树 

void change(int p,int x,int v){
    if(t[p].l==t[p].r){
        t[p].dat=v;
        return;
    }
    int mid=(t[p].l+t[p].r)/2;
    if(x<=mid)  change(p*2,x,v);
    else change(p*2+1,x,v);
    t[p].dat=min(t[p*2].dat,t[p*2+1].dat);
}//单点修改 

int ask(int p,int l,int r){
    if(l<=t[p].l&&r>=t[p].r){
        return t[p].dat; 
    }
    int mid=(t[p].l+t[p].r)/2;
    int val=1<<30;
    if(l<=mid)  val=min(val,ask(p*2,l,r));
    if(r>mid)   val=min(val,ask(p*2+1,l,r));
    return val;
}//区间查询 

int main(){
    scanf("%d %d %d",&n,&l,&r);
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&cow[i].a,&cow[i].b,&cow[i].c);
    }
    sort(cow+1,cow+n+1,cmp);//按b的值升序排序 
    memset(f,0x3f,sizeof(f));
    f[l]=0;//从起点到起点，花费当然是0了 
    build(1,l,r);
    for(int i=1;i<=n;i++){
        f[cow[i].b]=min(f[cow[i].b],ask(1,cow[i].a-1,cow[i].b)+cow[i].c);
        //找区间[ a[i]-1,b[i] ] 的最小值 
        change(1,cow[i].b,f[cow[i].b]);
        if(cow[i].b>=r){
            if(f[cow[i].b]==0x3f3f3f3f){
                printf("-1");  //不能完全覆盖 
            }else{
                printf("%d",f[cow[i].b]);
            }  //覆盖到了r直接输出最小值，程序结束 
            return 0;
        }
    }
    return 0;
}

```

---

## 作者：greenheadstrange (赞：8)

#### 前备知识：线段树（单点修改区间查询）
不会的童鞋可以去练习一下:

[P3372 【模板】线段树 1](https://www.luogu.org/problemnew/show/P3372)

设f[x]为清理[L,x]需要花费的最小代价。
把所有的奶牛的r进行从小到大的排序，按顺序扫描这些奶牛

则f[ri]=min(f[ri],min(f[x])+ci)其中ai-1<=x<bi
                                           
初始值f[L-1]=0,其余为inf
                                           
考虑优化：min(f[x])是一个区间的最小值，f数组还需要修改，很容易想到线段树，由于本题的线段坐标比较小，直接在[L-1,R]上建树。
###### 小提示：
1. 当左右端点超出[L,R]边界时可以放缩到边界，
```cpp
a[i].l=max(a[i].l,L);
a[i].r=min(a[i].r,R);
```
2. 当L=0时，上述讲的f[L-1]会炸数组。只需在读入时将l,r都加一即可
```cpp
L++;R++;
a[i].l++;a[i].r++;
```
少废话,直接上代码
                                           
```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff/2
using namespace std;
const int A=100005;
struct note{
	int l,r,s;
}tree[A*4],a[A];//为了方便，两个数组一起定义
int n,L,R,f[A];
bool cmp(note aa,note bb){//按照右端点排序
	return aa.r<bb.r;
}
void updata(int x){//更新操作
	tree[x].s=min(tree[2*x].s,tree[2*x+1].s);
}
void build(int x,int l,int r){//建立线段树
//	cout<<x<<" "<<l<<" "<<r<<"\n";
	tree[x].l=l;
	tree[x].r=r;
	tree[x].s=INF;
	if(l==r)return;
	int mid=(l+r)/2;
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
}
void revise(int x,int k,int p){//单点修改
//	cout<<tree[x].l<<" "<<k<<" "<<tree[x].r<<"\n";
	if(k<tree[x].l||k>tree[x].r)return;
	if(tree[x].l==k&&tree[x].r==k){tree[x].s=p;return;}
	int mid=(tree[x].l+tree[x].r)/2;
	if(k<=mid)revise(2*x,k,p);
	else revise(2*x+1,k,p);
	updata(x);
}
int ask(int x,int l,int r){//区间查询
	if(r<tree[x].l||tree[x].r<l)return INF;
	if(l<=tree[x].l&&tree[x].r<=r)return tree[x].s;
	return min(ask(2*x,l,r),ask(2*x+1,l,r));
}
int main(){
	scanf("%d%d%d",&n,&L,&R);L++;R++;
	for(int i=L;i<=R;i++)f[i]=INF;//初始化为极值
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].s);
		a[i].l++;a[i].r++;
		a[i].l=max(a[i].l,L);
		a[i].r=min(a[i].r,R);
	}
	build(1,L-1,R);
	revise(1,L-1,0);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
//		cout<<a[i].l<<" "<<a[i].r<<" "<<(1,a[i].l-1,a[i].r)<<" ";
		f[a[i].r]=min(f[a[i].r],ask(1,a[i].l-1,a[i].r)+a[i].s);
//		cout<<f[a[i].r]<<"\n";
		revise(1,a[i].r,f[a[i].r]);
	}
	if(f[R]==INF)puts("-1");
	else printf("%d",f[R]);
	return 0;
}
```


结束语（与本题无关）：如果坐标很大时可以考虑离散化哦！

---

## 作者：水库中的水库 (赞：7)

[推荐访问博客哦](http://ljf-cnyali.cn/2019/08/15/USACO05DEC-Cleaning-Shifts-DP-%E7%BA%BF%E6%AE%B5%E6%A0%91/)

先将每个$T_1,T_2$减去$M-1$，这样题目转化为最少的点覆盖$1\rightarrow E-M+1$

令$dp[i]$表示覆盖从$1\rightarrow i$的最小代价，则可以得到:$dp[T_2]=min_{T_1\leq i\leq T_2}dp[i-1]+S$

首先按$T_2$从小到大排序，依次考虑

再以每个$dp$值建一棵线段树维护最小值，直接转移即可

```cpp
/***************************************************************
	File name: P4644.cpp
	Author: ljfcnyali
	Create time: 2019年08月15日 星期四 13时03分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1000010;

int n, m, e, Min[maxn], num = 86400;
struct node
{
    int s, t, w;
    bool operator < (const node &a) const { return t < a.t; }
} a[maxn];

inline void PushUp(int root)
{
    Min[root] = min(Min[lson], Min[rson]);
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) { Min[root] = min(Min[root], val); return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Min[root];
    int Mid = l + r >> 1, sum = 0x3f3f3f3f;
    if ( L <= Mid ) sum = min(sum, Query(lson, l, Mid, L, R));
    if ( Mid < R ) sum = min(sum, Query(rson, Mid + 1, r, L, R));
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &e);
    e = e - m + 1;
    REP(i, 1, n) { scanf("%d%d%d", &a[i].s, &a[i].t, &a[i].w); a[i].s -= m - 1; a[i].t -= m - 1; }
    sort(a + 1, a + n + 1);
    memset(Min, 0x3f, sizeof(Min));
    Modify(1, 0, num, 0, 0);
    REP(i, 1, n)
    {
        int x = Query(1, 0, num, a[i].s - 1, a[i].t - 1);
        if ( x == 0x3f3f3f3f ) continue ;
        Modify(1, 0, num, a[i].t, x + a[i].w);
    }
    int x = Query(1, 0, num, e, e);
    printf("%d\n", x == 0x3f3f3f3f ? -1 : x);
    return 0;
}
```



---

## 作者：VPYEKINDAR (赞：5)

如果没有权值 此题为一个简单的线段覆盖问题 
但是现在我们有了权值 问题就变了 接下来是我的思路

------------
那么我们一定是通过线段进行跳跃 也就是我们利用了线段离我们的目标更近了一步 比如__——（不止这两条线段）对于这种线段无重叠情况 我们很容易想到解法 也就是对线段之间连边 我们只需要考虑起点到终点最大值 
```
for(int i=1;i<=n;i++){
scanf("%d%d%d",&node[i].a,&node[i].b,&node[i].c);add(node[i].a,node[i].b+1,node[i].c);}```
这样建边 对每一个线段点作为图中点 就可以解决问题


------------
对于重叠情况 我们可以发现需要往后走几步才会到达下一个线段首端而且这样是没有代价的 所以可以有
```
for(int i=m;i<=s;i++)
{
add(i,i-1,0);	
	}```
    到此 问题完美解决 下面是代码(spfa)
```
#include <bits/stdc++.h>
using namespace std;
struct p{
	int a,b,c;
}node[20010];
int cmp(p a,p b){
return a.a<b.a;	
}
int n,m,s,k;
struct z{
int v,next,w;	
}st[200010];
int head[200010],dis[200010],vis[200010];
int add(int a,int b,int c){
st[++k].v=b	;
st[k].w=c;
st[k].next=head[a];
head[a]=k;
}
int spfa()
{
	for(int i=m;i<=s+1;i++)
	dis[i]=1000000000;
queue<int> q;
q.push(m);
vis[m]=1;
dis[m]=0;
while(!q.empty()){
int v=q.front();
q.pop();
vis[v]=0;
for(int i=head[v];i;i=st[i].next){
int w=st[i].w,u=st[i].v;
if(dis[u]>dis[v]+w){
dis[u]=dis[v]+w;
if(!vis[u]){
vis[u]=1;
q.push(u);	
}	
}	
}	
}
	
}
int main()
{
scanf("%d%d%d",&n,&m,&s);
for(int i=1;i<=n;i++){
scanf("%d%d%d",&node[i].a,&node[i].b,&node[i].c);add(node[i].a,node[i].b+1,node[i].c);}
for(int i=m;i<=s;i++)
{
add(i,i-1,0);	
	}	
	spfa();
	printf("%d",dis[s+1]);
} ```

---

## 作者：skydogli (赞：4)

## 线段树维护优化$DP$裸题。

#### 首先，题目变量名取得十分奇特，所以我们约定：开始时间由M变为B，每个奶牛的花费由S变为cost，时间段总长为L

#### 另外,文中的|是集合的符号不是 $or$ 运算哈

按照普通的$DP$思路，设$f[i]$为从M到$i$的最小花费，每个时间段更新都扫一次，复杂度$O(N*L)$，肯定是过不了的。

然后我们发现，每个时间段都扫一遍性价比是很低的，因为如果我们不更新$(f[j]>f[i]|j<i)$，那么每个奶牛只会做一次贡献，所以我们直接按$t2$排序，则$DP$时，$f[t2[i]]=min(f[t2[i]],min(f[x]|t1[i]-1<x<t2[i])+cost[i])$

显然，这个$min$里面的东西是可以用线段树维护的。

然后就$O(n{log_2}n)$了，常数挺小，思路简单，感觉不用过多解释了

#### 代码细节&解释

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define MN 25005
#define INF 2147483647777
#define Ls (nod<<1)
#define Rs (nod<<1|1)
#define mid ((l+r)>>1)
struct data{
    int t1,t2,cost;
}w[MN];
int n,b,e;
LL f[MN<<4],ans[MN<<2];
//f：线段树中的答案 ans:从L到i的答案
inline LL min(int a,int b){
    return a<b?a:b;
}
inline bool cmp(data a,data b){
    return a.t2<b.t2;
}
inline int read(){
    int a=0;
    char c=getchar();
    while(c>57||c<48) c=getchar();
    while(47<c&&c<58){
        a=a*10+c-48;
        c=getchar();
    }
    return a;
}//快读
void build(int nod,int l,int r){
    f[nod]=INF;
    if(l==r)return;
    build(Ls,l,mid);
    build(Rs,mid+1,r);
}//建树
LL ask(int nod,int l,int r,int b,int e){
    if(l>e||r<b)return INF;
    if((b<=l&&r<=e)||l==r) return f[nod];
    return min(ask(Ls,l,mid,b,e),ask(Rs,mid+1,r,b,e));
}//最小值
void pushup(int nod,int l,int r,int loc){
    if(l>loc||r<loc) return;
    if(l==r) {f[nod]=ans[loc];return;}
    pushup(Ls,l,mid,loc);
    pushup(Rs,mid+1,r,loc);
    f[nod]=min(f[Ls],f[Rs]);
}//修改
int main(){
    n=read();b=read();e=read();
    for(int i=1;i<=n;++i){
        w[i].t1=read();
        w[i].t2=read();
        w[i].cost=read();
    }
    build(1,b,e);
    sort(w+1,w+1+n,cmp);//按t2排序，更新完前面再更新后面
    for(int i=b;i<=e;++i)ans[i]=INF;
    for(int i=1;i<=n;++i){
        int temp=ans[w[i].t2];
        ans[w[i].t2]=min(ans[w[i].t2],((w[i].t1>b)?ask(1,b,e,w[i].t1-1,w[i].t2):0)+(LL)w[i].cost);//这里要注意，当t1为b时要特判
        if(temp!=ans[w[i].t2])pushup(1,b,e,w[i].t2);
    }
    ans[e]!=INF?printf("%lld",ans[e]):puts("-1");
    return 0;
}


```

---

## 作者：小乐 (赞：4)

# 数据结构DP做法
> ##### P.S: 下面有一篇题解也是数据结构DP，但是代码有一定错误
> - ### 题目转换：需要令一个区间被完全覆盖，并且令所需代价最小，其中可花费一定代价让一头牛覆盖一个区间。
> - f[i] 表示覆盖从0 ~ i所需要的最小代价
> - c[i].l、c[i].r 表示当前牛可覆盖的区间
> - c[i].salary 表示当前牛所需代价
> - L, R 表示所需要覆盖的区间

## 转移方程
$$f[min(c[i].r, r)] = \min_{\max(L - 1, c[i].l - 1)<= j <= \min(R, c[i].r - 1)}{f[j]} + c[i].salary$$

初值f[L - 1] = 0, 其余为最大值。

## 意义
表示从当前牛的**左端点往前一个点**和**右端点往前一个点**中找一个最小代价点，转移到当前点。

但我们发现，在寻找的过程中明显会超时，所以用一个线段树来维护区间最小值。


## 代码
```c
#include <cstdio>
#include <cstring>
#include <algorithm>
#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)
using namespace std;

struct TreeNode {
	int l;
	int r;
	int m;
} t[2100000];

struct Cow {
	int l;
	int r;
	int salary;
	bool operator <(const Cow &c) const {
		return (this -> r) < c.r;
	}
} c[500010];

int n, l, r;
int f[1000010];

void build(int current, int l, int r) {
	t[current].l = l, t[current].r = r;
	if (l == r) {
		t[current].m = f[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(current * 2, l, mid);
	build(current * 2 + 1, mid + 1, r);
	t[current].m = min(t[current * 2].m, t[current * 2 + 1].m);
}

int ask(int current, int l, int r) {
	if (t[current].l == l && t[current].r == r) return t[current].m;
	int mid = (t[current].l + t[current].r) >> 1;
	if (l > mid) return ask(current * 2 + 1, l, r);
	if (r <= mid) return ask(current * 2, l, r);
	return min(ask(current * 2, l, mid), ask(current * 2 + 1, mid + 1, r));
}

void change(int current, int p, const int &value) {
	if (t[current].l == t[current].r) {
		t[current].m = value;
		return;
	}
	int mid = (t[current].l + t[current].r) >> 1;
	if (p > mid) change(current * 2 + 1, p, value);
	  else if (p <= mid) change(current * 2, p, value);
	t[current].m = min(t[current * 2 + 1].m, t[current * 2].m);
}

int main() {
	n = read(); l = read(), r = read();
	++l, ++r;
	for (int i = 0; i < n; ++i) {
		c[i].l = read(), c[i].r = read(), c[i].salary = read();
		++c[i].l, ++c[i].r;
	}
	memset(f, 0x7f7f7f7f, sizeof(f));
	sort(c, c + n);
	f[l - 1] = 0;
	build(1, l - 1, r);
	int temp, rawR;
	for (int i = 0; i < n; ++i) {
		rawR = min(r, c[i].r);
		temp = f[rawR];
		f[rawR] = min(f[rawR], ask(1, max(c[i].l - 1, l - 1), min(r, c[i].r - 1)) + c[i].salary);
		if (f[rawR] != temp) change(1, rawR, f[rawR]);
	}
	if (f[r] == f[r + 1]) puts("-1");
	  else printf("%d\n", f[r]);
	return 0;
}
```
P.S: 删去了快读, 数组设大了。

---

## 作者：wubaiting2020 (赞：4)

# 这道题本身只是一道比较水的dp，但是……它会卡O(n^2)的算法!!!  
## 所以，我们可以用数据结构优化！我用的线段树（单修区查多好写呀）  
要注意几点：  
1.dp数组在起点要清零  
2.循环取最小值时是从**t[i].l-1**到t[i].r  
3.线段树minn要取最大  
4.区间排序按右端点排  

------------

先上70分代码（我先得了100分为了题解再亲测了一遍70……）
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
const int INF=0x3f3f3f3f,MAXX=100000;
int n,l,r;
int cnt;
int dp[MAXX+5];
struct node{int l,r,v;}t[MAXX+5];
bool cmp(node x,node y){return x.r<y.r;}//按右端点从小到大排序 
int main()
{
	scanf("%d %d %d",&n,&l,&r);
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		if(x<l)x=l;if(y>r)y=r;//不知道有没有，但是为了以防万一还是写上了 
		if(x>y)continue;//同上 
		t[++cnt].l=x;t[cnt].r=y;t[cnt].v=z;
	}
	sort(t+1,t+cnt+1,cmp);
	memset(dp,0x3f,sizeof(dp));//dp数组清最大值 
	dp[l]=0;//左端点初值 
	for(int i=1;i<=cnt;i++)
	{
		int k=INF;
		for(int j=t[i].l-1;j<=t[i].r;j++)k=min(k,dp[j]);//从t[i].l-1——t[i].r 
		dp[t[i].r]=min(dp[t[i].r],k+t[i].v);//更新 
	}
	if(dp[r]==INF)printf("-1");//如果最后值为INF说明中间必定有时间打扫不到，输出-1 
	else printf("%d",dp[r]);
	return 0;
}

```

------------

满分代码
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
const int INF=0x3f3f3f3f,MAXX=100000;
int delta=10;
int n,l,r;
int cnt;
int dp[MAXX+5];
struct tree{int l,r,minn;}tree[MAXX*8+5];
struct node{int l,r,v;}t[MAXX+5];
bool cmp(node x,node y){return x.r<y.r;}//按右端点从小到大排序 
void Build(int k,int l,int r)
{
	tree[k].l=l;tree[k].r=r;tree[k].minn=INF;//线段树最小值清最大 
	if(l==r){return;}
	int mid=(l+r)>>1;
	Build(k<<1,l,mid);
	Build(k<<1|1,mid+1,r);
}
void add(int k,int x,int v)
{
	if(x<tree[k].l||x>tree[k].r)return;
    tree[k].minn=min(tree[k].minn,v);
    int mid=(tree[k].l+tree[k].r)>>1;
    add(k<<1,x,v);add(k<<1|1,x,v);
}
int ask(int k,int l,int r)
{
    int ans=INF;
    if(l<=tree[k].l&&r>=tree[k].r)return tree[k].minn;
    int mid=(tree[k].l+tree[k].r)>>1;
    if(l<=mid)ans=min(ans,ask(k<<1,l,r));
    if(r>mid)ans=min(ans,ask(k<<1|1,l,r));
    return ans;
}//模版线段树单修区查 
int main()
{
	Build(1,1,100000);//按数据范围建树 
	scanf("%d %d %d",&n,&l,&r);
	l+=10;r+=10;//全部加一个小数，不然会玄学RE
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		x+=10;y+=10;
		if(x<l)x=l;if(y>r)y=r;//不知道有没有，但是为了以防万一还是写上了 
		if(x>y)continue;//同上 
		t[++cnt].l=x;t[cnt].r=y;t[cnt].v=z;
	}
	sort(t+1,t+cnt+1,cmp);
	memset(dp,0x3f,sizeof(dp));//dp数组清最大值 
	dp[l]=0;//左端点初值 
	add(1,l,0);//更新到线段树里 
	for(int i=1;i<=cnt;i++)
	{
		int k=INF;
		k=min(k,ask(1,t[i].l-1,t[i].r));//从t[i].l-1——t[i].r 
//		cout<<1;
		dp[t[i].r]=min(dp[t[i].r],k+t[i].v);//更新的同时更新到线段树里 
		add(1,t[i].r,dp[t[i].r]);
//		cout<<2;
	}
	if(dp[r]==INF)printf("-1");//如果最后值为INF说明中间必定有时间打扫不到，输出-1 
	else printf("%d",dp[r]);
	return 0;
}



```



---

