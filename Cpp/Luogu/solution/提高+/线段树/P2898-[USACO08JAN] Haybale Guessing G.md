# [USACO08JAN] Haybale Guessing G

## 题目描述

给一个长度为 $n$ 的数组 $q$ 个条件，数组中的数字互不相同，每个条件格式形如  $l_i,r_i,x_i$ 表示这个数组的区间 $[l_i,r_i]$ 内的最小值为 $x_i$，输出最早与前面的条件有矛盾的条件的编号，如果所有条件都不发生矛盾，输出 $0$。

## 说明/提示

对于 $100\%$ 的数据，保证：
  - $1 \le q \le 25000$
  - $1 \le n \le 10^6$
  - $1 \le l_i \le r_i \le n$
  - $1 \le x_i \le 10^9$

## 样例 #1

### 输入

```
20 4
1 10 7
5 19 7
3 12 8
11 15 12
```

### 输出

```
3
```

# 题解

## 作者：George1123 (赞：36)

**广告：[blog$\spadesuit$](https://www.luogu.com.cn/blog/Wendigo/)**

[P2898 【\[USACO08JAN\]haybale猜测Haybale Guessing】](https://www.luogu.com.cn/problem/P2898)

**题意：有一个没有重复数的正整数序列，每句话告诉你 $l\sim r$ 区间的最小值为 $f$，求第一句与前面矛盾的话。**

### 此题算法：并查集 $+$ 二分

**二分枚举第一句矛盾的话 $x$ 。**

拿出 $1\sim x$ 句话，按 $f$ 从大到小排序。

从左到右读每一句话：

如果出现两段**没有重合区域的话满足 $f$ 相等**，得出矛盾。

![矛盾1.jpg](https://i.loli.net/2020/01/11/SMXmeJdxVONUtGc.jpg)

如果出现**所有 $f$ 相等的话 $\ll$区域交$\gg$ 已经全为一块**，得出矛盾。

![newtest.jpg](https://i.loli.net/2020/01/11/wfMbJBKeEnIF6Oi.jpg)

**将所有相同 $f$ 相等的话 $\ll$区域并$\gg$ 合并为一块**。 

如果都不满足矛盾，就得出符合。

最后结束二分，得出第一句矛盾的话。

## 以下是代码 $+$ 注释

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int Q=3e4+10;
int d(){int x;scanf("%d",&x);return x;}
int n,q;
struct ask{int l,r,f;}a[Q],cp[Q];
bool cmp(ask x,ask y){ //按 f 从大到小排序
	if(x.f==y.f) return x.l<y.l;
	return x.f>y.f;
}
struct mas{ //并查集
	int f[N];
	void clear(int x){
		for(int i=1;i<=x;i++)
			f[i]=i;
	}
	int find(int x){
		if(f[x]==x) return x;
		return f[x]=find(f[x]); 
	}
}s;
bool check(int x){ //判断1~x这些话矛不矛盾，原理如上
	s.clear(n+1);
	for(int i=1;i<=x;i++)
		cp[i]=a[i];
	sort(cp+1,cp+x+1,cmp);
	int p=cp[1].f,lx,ln,rx,rn;
	lx=ln=cp[1].l,rx=rn=cp[1].r;
	for(int i=2;i<=x;i++){
		if(p==cp[i].f){
			ln=min(ln,cp[i].l);
			rn=min(rn,cp[i].r);
			lx=max(lx,cp[i].l);
			rx=max(rx,cp[i].r);
			if(lx>rn) return 0;
		} else {
			if(s.find(lx)>rn) return 0;
			for(int j=s.find(ln);;j=s.find(j+1))
				if(j>rx) break;
				else s.f[j]=s.f[j+1];
			p=cp[i].f;
			lx=ln=cp[i].l;
			rx=rn=cp[i].r;
		}
	}
	return s.find(lx)<=rn;
}
int main(){
	n=d(),q=d();
	for(int i=1;i<=q;i++)
		a[i].l=d(),a[i].r=d(),a[i].f=d();
	int l=0,r=q+1;
	while(l<r-1){ //二分得出答案
		int mid=(l+r)>>1;
		if(check(mid)) l=mid;
		else r=mid;
	}
	if(r==q+1) puts("0");
	else printf("%d\n",r);
	return 0;
}
```

用线段树也可以做到，但又麻烦又慢。

**画图、写题解不易，快点个赞吧。**

谢谢大家! !







---

## 作者：Mizuhara (赞：24)

楼下老哥的并查集操作好是巧妙，但是并没有讲具体如何用并查集来

覆盖区间以至于我查了好多资料才搞明白。。。（也许是因为我⑨）

所以，在此将并查集实现这题的原理讲一讲。

---

有如下问题：

长为$n$的序列，开始均无颜色，

有$m$个操作，每次将$l$到$r$的数全染成$c$色，

求最终的序列。


我们考虑将染色反着来，则一个数若被染色一次，

则这就是它的最终颜色，不会改变。

所以下次若在遇到这个数则需要跳过，

也就是对已经染色的区间$[l,r]$，我们令其中的所有数都有一个指针，

以指向右边第一个还没有操作的数。

于是我们令$father[i]$表示$i$右边（包括$i$本身）第一个没有染色的数，

将$i$染色后，令$father[i] = find(i + 1)$,

之后就是正常的并查集操作了。

-----------------

然后这题是个特例，染色虽然是正着来的，但染的颜色全是一种，

只存在$0 - >1$，染一次则以后不变色，所以也可用这种方法做。

---

## 作者：asuldb (赞：18)

抄题解.jpg

完全完全不会啊，这道题简直太神了

不过抄题解可真开心

首先这道题目保证了每一个位置上的数都是不同的，那么就能得到第一种判断不合法的方式

**如果两个区间的最小值一样，但是两个区间的交集为空集，那么就是不合法的**

因为最小值肯定来自于同一个位置

之后就是第二种情况

![图](https://cdn.luogu.com.cn/upload/pic/42224.png)

上面那两个红色区间的最小值是$4$，但是下面那个被完全包含的绿色区间的最小值是$3$这显然非常不合法

但是如果是这个样子呢

![图](https://cdn.luogu.com.cn/upload/pic/42225.png)

显然是可以的，因为那些$3$可以来自红色区间以外的位置

![图](https://cdn.luogu.com.cn/upload/pic/42226.png)

就有不行了，因为这个时候$3$又只能来自于那个较小的绿色区间了，而那个较小的绿色区间又被红色完全覆盖了

这个时候就能得出第二个判断方法

**如果最小值相同的区间，其交集被最小值比它的区间的并集覆盖，那么就不合法**

所以我们需要覆盖并集，判断交集是否被完全覆盖

显然区间的交集和并集随手就能求出来，但是覆盖这个问题得需要一棵线段树来判断

同时为了方便的进行判断$2$，我们得让区间的最小值是有序的，所以一个一个扫是行不通了，我们得二分答案，找到最后一个合法的位置$+1$就是答案了

代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define LL long long
#define re register
#define maxn 25005
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
struct Seg
{
	int x,y,q;
}a[maxn],b[maxn];
int l[4000005],r[4000005],d[4000005],tag[4000005];
int n,m;
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
void build(int x,int y,int i)
{
	l[i]=x,r[i]=y;
	if(x==y) return;
	int mid=x+y>>1;
	build(x,mid,i<<1),build(mid+1,y,i<<1|1);
}
void clear(int x,int y,int i)
{
	d[i]=0,tag[i]=0;
	if(x==y) return;
	int mid=x+y>>1;
	clear(x,mid,i<<1),clear(mid+1,y,i<<1|1);
}
inline void pushdown(int i)
{
	if(!tag[i]) return;
	tag[i<<1]=tag[i<<1|1]=1;
	d[i<<1]=r[i<<1]-l[i<<1]+1;
	d[i<<1|1]=r[i<<1|1]-l[i<<1|1]+1;
	tag[i]=0;
}
void change(int x,int y,int i)
{
	if(x<=l[i]&&y>=r[i]) 
	{
		d[i]=r[i]-l[i]+1;
		tag[i]=1;
		return;
	}
	pushdown(i);
	int mid=l[i]+r[i]>>1;
	if(y<=mid) change(x,y,i<<1);
		else if(x>mid) change(x,y,i<<1|1);
			else change(x,y,i<<1|1),change(x,y,i<<1);
	d[i]=d[i<<1]+d[i<<1|1];
}
int query(int x,int y,int i)
{
	if(x<=l[i]&&y>=r[i]) return d[i];
	pushdown(i);
	int mid=l[i]+r[i]>>1;
	if(y<=mid) return query(x,y,i<<1);
	if(x>mid) return query(x,y,i<<1|1);
	return query(x,y,i<<1)+query(x,y,i<<1|1);
}
inline int cmp(Seg A,Seg B)
{
	return A.q>B.q;
}
inline int check(int now)
{
	for(re int i=1;i<=now;i++)
		b[i]=a[i];
	std::sort(b+1,b+now+1,cmp);
	clear(1,n,1);
	int pre=1,nl=b[1].x,nr=b[1].y,Ul=b[1].x,Ur=b[1].y;
	for(re int i=2;i<=now;i++)
	{
		if(b[i].q==b[pre].q)
		{
			nl=max(nl,b[i].x);
			Ul=min(Ul,b[i].x);
			Ur=max(Ur,b[i].y);
			nr=min(nr,b[i].y);
		}
		else
		{
			if(nl>nr) return 0;
			if(query(nl,nr,1)==nr-nl+1) return 0;
			change(Ul,Ur,1);
			pre=i;
			nl=Ul=b[i].x,nr=Ur=b[i].y;
		}
	}
	if(nl>nr) return 0; 
	if(query(nl,nr,1)==nr-nl+1) return 0;
	return 1;
}
int main()
{
	n=read(),m=read();
	for(re int i=1;i<=m;i++) a[i].x=read(),a[i].y=read(),a[i].q=read();
	build(1,n,1);
	int L=1,R=m;
	int ans=0;
	while(L<=R)
	{
		int mid=L+R>>1;
		if(check(mid)) L=mid+1,ans=mid;
			else R=mid-1;
	}
	if(ans==m) puts("0");
		else printf("%d\n",ans+1);
	return 0;
}
```

---

## 作者：elijahqi (赞：10)

并查集+二分

题意：给出一些区间的最小值 求问 最早哪个问题会产生矛盾 输出

针对这个产生矛盾 我们可以二分判断 哪个地方最早出现矛盾

然后每次针对二分的一个值 我去判断一下是否成立 我首先针对权值排序

然后从大到小去覆盖 出现第一个无法覆盖的区域我就返回false

每次我是判断交集 覆盖并集 用并查集可以完成

```cpp
#include<cstdio>
#include<algorithm>
#define Q 30000
#define N 1100000
#define inf 0x3f3f3f3f
using namespace std;
inline char gc(){
    static char now[1<<16],*T,*S;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0;char ch=gc();
    while (ch<'0'||ch>'9') ch=gc();
    while (ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
    return x;
}
struct node{
    int l,r,v;
}data[Q],data1[Q];
inline bool cmp(node a,node b){
    if (a.v>b.v) return true;else if (a.v<b.v) return false;
    return a.l<b.l;
}
int fa[N],n;
inline int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline bool check(int x){
    int l=0,r=inf;int l1=inf,r1=0;
    for (int i=1;i<=n+1;++i) fa[i]=i;
    for (int i=1;i<=x;++i) data[i]=data1[i];sort(data+1,data+x+1,cmp);
    int last_v=data[1].v;l=l1=data[1].l;r=r1=data[1].r; 
    for (int i=2;i<=x;++i){
        if (last_v!=data[i].v){
            int x=find(l);
            if(x<=r) {int now=find(l1);
                while (now<=r1) fa[now]=fa[now+1],now=find(now+1);
            }else return false;
            last_v=data[i].v;l=l1=data[i].l;r=r1=data[i].r;
        }else{
            l=max(l,data[i].l);r=min(r,data[i].r);l1=min(l1,data[i].l);r1=max(r1,data[i].r);
            if (l>r) return false;
        };
    }if (find(l)>r) return false;
    return true;
}
int l,r,q;
int main(){
    //freopen("bzoj1594.in","r",stdin);
    n=read();q=read();
    for (int i=1;i<=q;++i) data1[i].l=read(),data1[i].r=read(),data1[i].v=read();
    l=0;r=q;
    while (l<=r){
        int mid=l+r>>1;
        if (check(mid)) l=mid+1;else r=mid-1;
    }if (l>q)printf("0");else printf("%d",l);
    return 0;
}
```
线段树+二分

线段树也可以很好的解决这个问题  那就是可以每次nlogn重建线段树 但是显然动态加点线段树效果会更好 这里 其实这个题目是有个坑的 那就是 如果我认为整个区间的最小值是1e9那么因为我每个数都只会出现一次 所以其实这个询问也是不合法的所以我可以考虑每次贪心的把大的填入 然后看一下 我这次需要填入多少个 然后再判断下 大的数还能填多少 据此判断是否可行即可

线段树的详细解法 楼下已经写的挺清楚了 就是动态加点线段树成功的把这题跑进了100ms

```cpp
#include<cstdio>
#include<algorithm>
#define Q 33000
#define N 1100000
using namespace std;
inline char gc(){
    static char now[1<<16],*T,*S;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0;char ch=gc();
    while (ch<'0'||ch>'9') ch=gc();
    while (ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
    return x;
}
struct node{
    int l,r,v;
}data1[Q],data[Q];
struct node1{
    int l,r,left,right,v,lazy;
}tree[N<<2];
inline bool cmp(node a,node b){
    if (a.v>b.v) return true;else if (a.v<b.v) return false;
    return a.l<b.l;
}
int num,n,q,root;
inline void init(int &x){
    x=++num;tree[x].left=tree[x].right=tree[x].l=tree[x].r=tree[x].lazy=tree[x].v=0;
}
inline void pushdown(int x){
    if (!tree[x].lazy) return ;
    int mid=tree[x].l+tree[x].r>>1;
    if (!tree[x].left) init(tree[x].left);
    if (!tree[x].right) init(tree[x].right);
    int l=tree[x].left,r=tree[x].right;
    tree[l].l=tree[x].l;tree[l].r=mid;tree[r].l=mid+1;tree[r].r=tree[x].r;
    tree[l].v=mid-tree[x].l+1;tree[r].v=tree[x].r-mid;
    tree[l].lazy=tree[r].lazy=tree[x].lazy;
    tree[x].lazy=0;
} 
inline void update(int x){
    int l=tree[x].left,r=tree[x].right;
    tree[x].v=tree[l].v+tree[r].v;
}
void insert1(int &x,int l,int r,int l1,int r1){
    if(l>r) return; 
    if (!x) init(x);tree[x].l=l;tree[x].r=r;
    if (l1<=l&&r1>=r){tree[x].v=tree[x].r-tree[x].l+1;tree[x].lazy=1;return;}
    int mid=tree[x].l+tree[x].r>>1;pushdown(x);
    if (l1<=mid) insert1(tree[x].left,l,mid,l1,r1);
    if (r1>mid) insert1(tree[x].right,mid+1,r,l1,r1);
    update(x);
}
int query(int x,int l,int r){
    if (l>r) return 0;
    if (!x) return 0;
    if (l<=tree[x].l&&r>=tree[x].r) return tree[x].v;
    int mid=tree[x].l+tree[x].r>>1;pushdown(x);int tmp=0;
    if (l<=mid) tmp+=query(tree[x].left,l,r);
    if (r>mid) tmp+=query(tree[x].right,l,r);
    return tmp;
}
inline bool check(int x){
    for (int i=1;i<=x;++i) data[i]=data1[i];int tot=1e9;
    sort(data+1,data+x+1,cmp);num=0;int l,r,l1,r1;root=0;tree[0].l=tree[0].r=tree[0].left=tree[0].right=0;
    int last_v=data[1].v;l=l1=data[1].l;r=r1=data[1].r; int differ=0;
    for (int i=2;i<=x;++i){
        if (data[i].v!=last_v){
            if (query(root,l,r)==r-l+1) return false;int pre=tree[root].v;
            insert1(root,1,n,l1,r1);differ=tree[root].v-pre;
            if (tot-last_v+1<differ) return 0;tot-=differ;
            l=l1=data[i].l;r=r1=data[i].r;last_v=data[i].v;
        }else{
            l=max(l,data[i].l);r=min(r,data[i].r);l1=min(l1,data[i].l);r1=max(r1,data[i].r);
            if (l>r) return false;
        };
        
    }
    if (query(root,l,r)==r-l+1) return false;
    int pre=tree[root].v;
    insert1(root,1,n,l1,r1);differ=tree[root].v-pre;
    if (tot-last_v+1<differ) return 0;tot-=differ;
    return true;
}
int main(){
    freopen("bzoj1594.in","r",stdin);
    n=read();q=read();
    for (int i=1;i<=q;++i){data1[i].l=read();data1[i].r=read();data1[i].v=read();}
    int l=1,r=q;
    while (l<=r){
        int mid=l+r>>1;
        if (check(mid)) l=mid+1;else r=mid-1;
    }
    if (l>q) printf("0");else printf("%d",l);
    return 0;
}
```

---

## 作者：Rbu_nas (赞：7)

简要题意：小母牛回答你 $q$ 次区间 $[l,r]$ 上的最小值，判断最早哪个句子会出现矛盾。

这题有点米奇妙妙屋。

先来思考简单的情况，知道两个区间的最小值，如何判定矛盾？

显然这种情况是矛盾的：

![1](https://i.loli.net/2020/10/12/UW9lgOiCYhmHKbu.png)

然而这道题还有一个条件，序列上每个位置 $a_i$ 不同，所以这种情况也不可能发生：

![2](https://i.loli.net/2020/10/12/Kz8oM9vImnDCsSE.png)

还有一种 $l_2$ 只有一个端点 $\in$ $l_1$ 的情况——区间有交集，但不是完全覆盖 $\Rightarrow$ 区间最小值可以不一样也可以一样。

整理一下：

- 两区间**无交集**，他们的最小值不应该相同。

- 一个区间**被**大区间**完全覆盖**，它的最小值只能大于等于大区间最小值。

也就是说这道题的判定转化为了一个区间覆盖的判定问题，是否出现矛盾我们通过区间覆盖的关系来求。

我们将区间最小值从大往小排序，这样的话如果一个区间最小值比较小，但它被大区间覆盖了（相应地 这个大区间的最小值比它大，排在前面），这个时候就不对劲；如果枚举到几个区间最小值相同，但他们互不相干，也能推导出矛盾关系。所以这样处理就变成了区间覆盖问题。

![还挺牛](https://i.loli.net/2020/10/12/3I2zXLHON7nscF6.png)

好啦我会做啦！把 $1$ 到 $q$ 的回答按 $val$ 排序，再记一个回答的编号 `q[i].id` 搞搞，这样就能知道啥时候有矛盾了！

naive!

这道题求的是最早的矛盾出现时间，如果排序后一个 $id=4$ 的区间被 $id=5$ 的区间覆盖且出现了矛盾，能说明最早的矛盾在 $4$ 吗？不能。这个时候我们只能知道在这个时间段有矛盾，但是没法定位最早的矛盾。又因为在 $1-k$ 的句子中没有矛盾，$1-k'(k'\le k)$ 中肯定也没有矛盾，这个问题实际上是有单调性的。问题只会出现在 没有问题的时间 之后，所以可以二分这个时间 $k$，如果没矛盾那么二分后面的，出现矛盾则往前二分。

区间覆盖可以用线段树区间 set 来做。这个区间能被完整查询到则说明被覆盖了。如果有 $val$ 相同的我们更新一下交集和并集，都有交集的话那肯定没事了，然后把这些段的并集 update 到树上。这个时候它们的并集肯定是一段完整的区间段的，因为有一个区间和前面的 $val$ 相同的没交集就出错了。要是没有 $val$ 相同的我们就判断一下 $q_i$ 这个区间段能不能被查到，更新就更新它这一段就好了。

我感觉应该讲的比较详细了，结合代码看看应该比较好懂。

```cpp
const int inf = 1000000000;

inline int read() {
    register int x = 0, c = getchar();
    bool f = 1;
    for(; !isdigit(c); c = getchar()) f ^= c == '-';
    for(; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    return f ? x : -x;
}

struct A {
    int l, r, mn;
    inline bool operator<(const A &rhs) const {
        return mn == rhs.mn ? l < rhs.l : mn > rhs.mn; // 按 val 排序
    }
} a[MAXN], b[MAXN];

int n, m;

struct Node {
    int sum, tag;
} tr[MAXN * 4];

#define ls(p) p << 1
#define rs(p) p << 1 | 1

inline void maintain(int p, int l, int r, int v) {
    tr[p].sum = (r - l + 1) * v;
    tr[p].tag = v; // segtree 区间set
}

inline void pushDw(int p, int l, int r) {
    int mid = (l + r) >> 1;
    maintain(ls(p), l, mid, tr[p].tag);
    maintain(rs(p), mid + 1, r, tr[p].tag);
    tr[p].tag = 0;
}

void update(int p, int l, int r, int ql, int qr, int v) {
    if(ql > qr) return;
    if(ql <= l && r <= qr) return maintain(p, l, r, v);
    if(tr[p].tag) pushDw(p, l, r);
    int mid = (l + r) >> 1;
    if(ql <= mid) update(ls(p), l, mid, ql, qr, v);
    if(qr > mid) update(rs(p), mid + 1, r, ql, qr, v);
    tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
}

int query(int p, int l, int r, int ql, int qr) {
    if(ql > qr) return 0;
    if(ql <= l && r <= qr) return tr[p].sum;
    if(tr[p].tag) pushDw(p, l, r);
    int mid = (l + r) >> 1, ret = 0;
    if(ql <= mid) ret += query(ls(p), l, mid, ql, qr);
    if(qr > mid) ret += query(rs(p), mid + 1, r, ql, qr);
    return ret;
}

inline bool chk(int x) {
    memset(tr, 0, sizeof tr);
    for(int i = 1; i <= x; ++i)
        b[i] = a[i];
    sort(b + 1, b + x + 1);
    int ul, ur, nl, nr;
    for(int i = 1; i <= x;) {
        int j = i;
        while(j <= x && b[j].mn == b[i].mn) ++j;
        ul = nl = b[i].l, ur = nr = b[i].r; // ul ur 并集；nl nr 交集
        for(int k = i + 1; k < j; ++k) { // 如果j=i开始往后扫 最后i=j更新i的话，注意循环范围
            ul = min(b[k].l, ul);
            ur = max(b[k].r, ur);
            nl = max(b[k].l, nl);
            nr = min(b[k].r, nr);
        }
        if(nl > nr) return 0;
        if(query(1, 1, n, nl, nr) == nr - nl + 1) return 0;
        update(1, 1, n, ul, ur, 1); // 如果没有相同的这样写就相当于 bi.l bi.r
        i = j;
    }
    return 1;
}

int main(void) {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i)
        a[i].l = read(), a[i].r = read(), a[i].mn = read();
    int l = 1, r = m + 1;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(chk(mid)) l = mid + 1;
        else r = mid;
    }
    printf("%d\n", l == m + 1 ? 0 : l);
    // 注意这里，这种二分写法 (l + r) / 2 是取不到 r 的，但是这里 r=m 是可以成为答案的
    // 所以这种写法需要由原来的 [1,x] 扩展到 [1,x+1]，x 为 r 的取值点
    return 0;
}

```

---

## 作者：kouylan (赞：5)

## 题解 P2898 【[USACO08JAN]Haybale Guessing G】

[洛谷题面传送门](https://www.luogu.com.cn/problem/P2898)

我们先来考虑一下，什么样的情况会矛盾？

题目中说，每个位置的数不同。那就说明同一个数所对应的几个区间必定有交集。那么，没有交集必然是矛盾的。如下图就是矛盾的情况

![](https://cdn.luogu.com.cn/upload/image_hosting/ystri4xp.png)

还有，大区间内有数更小的区间，那这必定是不合法的，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/0gk71jtp.png)

总结一下，一共有两种情况会产生矛盾：
1. 数相同的区间无交集
1. 大数的区间内有较小数的区间

接下来我们看如何判断。

第一种情况，判断交集。这还是很简单的，这里就不作过多的解释。

第二种情况，我们从大到小考虑。核心的思路是这样的：如果这个区间上存在点被较大的区间覆盖，那就是不合法的。这里我们可以采用并查集。我们可以把当前区间内的每个点都指向区间最右侧的端点。这样，里面小区间的点所指向的额点，就会不在这个小区间里，那么就是不合法的。

最后，判断是第几句话时，只需要二分一个 $\mathrm{mid}$，去判断第 $1$ 句到第 $\mathrm{mid}$ 句话是否都合法即可。

下面是 AC 代码
```cpp
/*
luogu P2898
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

int n,m;
int lj,rj,lb,rb;
struct quer{
	int l,r,f;
}a[25005],b[25005];
struct dsu{
	int fa[1000005];
	void init()
	{
		for(int i=1;i<=n+2;fa[i]=i,i++);
	}
	int find_(int x)
	{
		return x==fa[x] ? x : fa[x]=find_(fa[x]);
	}
}c;

bool cmp(quer a,quer b)
{
	return a.f==b.f ? a.l<b.l : a.f>b.f;
}

bool legal(int m)
{
	c.init();
	for(int i=1;i<=m;a[i]=b[i],i++);
	sort(a+1,a+1+m,cmp);
	a[m+1].f = 0;
	int num=0;
	for(int i=1;i<=m+1;i++)
	{
		if(a[i].f!=num)
		{
			if(i!=1)
			{
				if(lj>rj)
					return false;
				if(c.find_(lj)>rj)
					return false;
				for(int j=c.find_(lb);j<=rb;j=c.find_(j+1))
					c.fa[j] = c.fa[j+1];
			}
			num = a[i].f;
			lj = rb = -INF, rj = lb = INF;
		}
		if(a[i].f==num)
		{
			lj = max(lj,a[i].l), rj = min(rj,a[i].r);
			lb = min(lb,a[i].l), rb = max(rb,a[i].r);
		}
	}
	return true;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;cin>>b[i].l>>b[i].r>>b[i].f,i++);
	int l=1,r=m,ans=1;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(legal(mid))
		{
			ans = mid;
			l = mid+1;
		}
		else
			r = mid-1;
	}
	cout<<(ans==m ? 0 : ans+1)<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：UKE_Automation (赞：4)

### P2898 [USACO08JAN] Haybale Guessing G 题解

#### Problem

给出一个长度为 $n$ 的数组，同时给出 $q$ 个条件，每个条件描述原数组一段的最小值。根据这些条件，判断在第几个条件时开始出现矛盾。

#### Solution

要求出最早的出现矛盾的条件，而在这个条件之前的所有条件都不冲突、之后便开始冲突，满足单调性，因此可以**二分答案**。

具体的，二分这个条件，然后判断。所以接下来的难点就在于如何判断当前条件是否冲突。

考虑出现冲突的两种情况：

1. 当两个区间的最小值相等时，如果两个区间没有交集，则与题目要求的“草垛数量互不相等”矛盾，故此时会有冲突。

2. 当两个区间的最小值不等，且最小值较大的区间包含着最小值较小的区间，则也会发生冲突。

根据上面的分析，我们发现需要维护**区间的交集与并集**，其中并集判断最小值相等的情况，并集判断最小值大的区间是否覆盖最小值较小的区间。

而看到这些字眼，自然而然的会想到**并查集**。具体的，把相同最小值区间 $[l,r]$ 都连向 $r$，然后利用并查集维护交并集即可。

具体的可以看注释。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int Inf = 2e9;
const int Maxn = 1e6 + 5;

int n, q;
struct node{
	int l, r, minn;
}a[Maxn], p[Maxn];//输入的数组和辅助数组 

bool cmp(node x, node y) {
	return x.minn > y.minn;
/*
按照最小值从大到小排序，可以在判断的时候更方便的处理第二种情况 
*/
} 

int fa[Maxn];

int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));//路径压缩并查集 
}

bool check(int x) {//判断前 x 个是否合法 
	for(int i = 1; i <= x; i++) 
		p[i] = a[i];//辅助数组 
	for(int i = 1; i <= n + 1; i++) 
		fa[i] = i;//并查集初始化 
	sort(p + 1, p + x + 1, cmp);//排序 
	int minl, minr, maxl, maxr;//记录当前最小值相同的区间的信息 
	minl = maxl = p[1].l;
	minr = maxr = p[1].r;
	for(int i = 2; i <= x; i++) {
		if(p[i].minn == p[i - 1].minn) {//最小值相同 
			minl = min(minl, p[i].l);
			maxl = max(maxl, p[i].l);
			minr = min(minr, p[i].r);
			maxr = max(maxr, p[i].r);//更新极值端点 
			if(maxl > minr) return 0;//如果两个区间没有交集，返回冲突 
		}
		else {//最小值不同 
			if(find(maxl) > minr) return 0;//这个点被最小值更大的点覆盖了，那就会有冲突 
			for(int j = fa[minl]; j <= maxr; j = fa[j]) {//遍历区间，全部连向右端点 
				find(j);
				fa[j] = find(j + 1);
			}
			//完善上一个区间的信息 
			minl = maxl = p[i].l;
			minr = maxr = p[i].r;//开始记录新的最小值区间 
		}
	}
	if(find(maxl) > minr) return 0;//一定要在判断一次 
	return 1;
}

int ans;

void bs() {//二分答案 
	int l = 1, r = q + 1, mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(check(mid)) {
			l = mid + 1;	
			ans = mid + 1;//注意判断的是不冲突的前 x 个，答案记录的是第一个冲突的，所以是 x + 1 
		}	
		else {
			r = mid - 1;
		}	
	}
	if(ans > q) ans = 0;//没有冲突 
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> q;
	for(int i = 1; i <= q; i++) {
		cin >> a[i].l >> a[i].r >> a[i].minn;
	}
	bs();
	cout << ans;	
	return 0;
}
```


---

## 作者：Muel_imj (赞：4)

[P2898](https://www.luogu.com.cn/problem/P2898)

并查集做法确实很巧妙，但实际上最优解是**线段树**
目前本人最优解第三，此处讲一下线段树的做法


首先二分不再赘述

矛盾的条件
=
1. 同一数值，多次出现，几个区间间交集为空集（因为每个数值存在一个）
2. 一个数值出现时，它的区间已经被较大值的区间覆盖（此时本数值放在区间内任意位置，都会使之前给出的信息不成立）

具体的操作：
=
1. 预处理 对数值离散化
2. 先把重复数值处理，求交集和并集（它的交集是它**可以存在的区间**，它的并集是它**可以覆盖的区间**），若无交集则矛盾
3. 对二分取定的前 K 条信息进行排序，先处理较大数值（因为每个数值会不会被覆盖只跟大于它的数有关）
4. 访问到某条信息时，先在线段树上查询本区间**是否有位置未被覆盖**， 若有则该数值还有生存空间，若无返回 0 ，然后修改它的区间

存储
-
众所周知这是个区间覆盖的问题，但是**一个较小值的区间被哪个值覆盖并不重要**， 所以线段树里只需要存 bool ， 被覆盖则为 真 ，否则为 假

然后，因为要查询的是是否有**未被覆盖的位置**， 所以存的是区间所有数值的与, 也就是
$$t[k] = t[lt]\,\&\,t[rt]$$

修改&查询
-
0. 用交集查询，用并集修改
1. 修改时的操作全部都是  $t[k]\,\|\,=1$ 
因为递归时当前树上节点对应**区间越来越小**，所以若当前节点值为 真 ，再往下也都是 真 ，所以就**不用再往下递归**
2. 查询时同上条，若当前节点是 真 ，那么不再递归
3. 当前节点值为 真 ，说明它子树节点都会是 真 ，仔细想想，这与 延迟标记 不是一样吗？所以节点值可以兼职 延迟标记

记得建树初始化（不用 pushup ）

丑陋的代码：
```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<vector>
#include<algorithm>
#define reg register int
#define ttT template <typename T>
#define EL puts("Elaina")
using namespace std;
inline char gc(){
    static char buf[1<<20],*p1,*p2;
    if(p1==p2){p1=buf,p2=buf+fread(buf,1,1<<20,stdin);if(p1==p2)return EOF;}
    return *p1++;
}
ttT inline void read(T &x){
    x=0;int f=1;char ch=gc();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}
    x*=f;
}
ttT inline void write(T x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar((x%10)^48);
}
const int maxn=1e6+3,maxm=25000+3,INF=0x7fffffff;
int n,m,b[maxm];
struct qestion{
    int l,r,v;
}a[maxm];
struct nump{
    int l,r;//交
    int l2,r2;//并
}c[maxm];//下标为数值（草堆数）
#define lt (k<<1)
#define rt (k<<1|1)
struct tree{
    int l,r;
    bool v;
}t[maxn<<2];
inline void pushup(int k){
    t[k].v=t[lt].v&t[rt].v;
}
inline void pushdown(int k){
    if(t[k].v)t[lt].v=t[rt].v=true;
}
inline void build(int k,int l,int r){
    t[k].l=l,t[k].r=r,t[k].v=false;
    if(l==r)return;
    else{
        int mid=(l+r)>>1;
        build(lt,l,mid);
        build(rt,mid+1,r);
    }
}
inline bool query(int L,int R,int k){
    if(t[k].v)return true;
    if(L<=t[k].l&&t[k].r<=R)return t[k].v;
    else{
        pushdown(k);
        bool ans=true;
        if(L<=t[lt].r)ans&=query(L,R,lt);
        if(R>=t[rt].l)ans&=query(L,R,rt);
        return ans;
    }
}
inline void updata(int L,int R,int k){
    if(t[k].v)return;
    if(L<=t[k].l&&t[k].r<=R)t[k].v=true;
    else{
        pushdown(k);
        if(L<=t[lt].r)updata(L,R,lt);
        if(R>=t[rt].l)updata(L,R,rt);
        pushup(k);
    }
}
/*
1、相同数字，多次出现，某两个区间不重叠
2、修改后失去某个数值
对数值 离散化
修改：较大值覆盖较小值
*/
inline bool check(int k){
    if(!k)return true;
    memset(c,0,sizeof(c));
    vector <int> apr;//出现过的数值
    int minv=INF,maxv=-INF;
    for(reg i=1;i<=k;++i){
        int v=a[i].v;
        minv=min(minv,a[i].l),maxv=max(maxv,a[i].r);//需要建树的区间
        if(!c[v].l){
            c[v].l=c[v].l2=a[i].l,c[v].r=c[v].r2=a[i].r;
            apr.push_back(v);
        }
        else{
            c[v].l=max(c[v].l,a[i].l),c[v].r=min(c[v].r,a[i].r);
            if(c[v].l>c[v].r)return false;
            c[v].l2=min(c[v].l2,a[i].l),c[v].r2=max(c[v].r2,a[i].r);
        }
    }
    sort(apr.begin(),apr.end());
    build(1,minv,maxv);
    for(reg i=apr.size()-1;i>=0;--i){
        int v=apr[i];
        if(query(c[v].l,c[v].r,1))return false;
        updata(c[v].l2,c[v].r2,1);
    }
    return true;
}
void solve(){
    read(n),read(m);
    for(reg i=1;i<=m;++i){
        read(a[i].l),read(a[i].r),read(a[i].v);
        b[i]=a[i].v;
    }
    sort(b+1,b+m+1);
    int lb=unique(b+1,b+m+1)-b-1;
    for(reg i=1;i<=m;++i)
        a[i].v=lower_bound(b+1,b+lb+1,a[i].v)-b;
    int l=0,r=m,mid,ans;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid))ans=mid,l=mid+1;
        else r=mid-1;
    }
    if(ans==m)ans=-1;
    write(ans+1),puts("");
}
int main(){
    solve();
    return 0;
}
```


---

## 作者：APOI (赞：4)

# 题解

二分+线段树
有人用神奇姿势の并查集来代替线段树来搞..但是我不懂QwQ
于是我就打了线段树。。代码迷の长&迷の慢。。orzorz
我们要先想矛盾之处会在哪里。

1、没有交集的两个区间出现了相同的最小值x。因为每个数各不相同。即x的交集不合法或者说没有交集。

2、已知某段区间的最小值为x，但是这段区间中的某个子区间的最小值为y，而y<x，那么对于已知的条件就矛盾了。即x所在区间的并集包含了y所在区间的交集的话就矛盾了(x>y)。

二分答案，把询问排序。

怎么排？按值从大到小，这样就方便处理矛盾2。

把x的区间都找到，得到其交集和并集的区间。
直接用交集的区间判断矛盾1咯。

对于矛盾二，用线段树维护标记下在哪段区间（用并集标记）已经知道最小值。

因为从大到小排的序，所以更新在线段树里标记的都是比现在的数大的数标记的。那么如果查询到现在这个数的交集区间已经被标记了，就是矛盾2啊有矛盾了。
然后，，，就这样啊。。。

```cpp
#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
#define maxn 2000010  
#define Q 30000  
  
struct node {int l,r,c;}a[Q],b[Q];  
bool cmp(node x,node y){return x.c>y.c;}  
struct tree  
{  
    int l,r,lc,rc;bool c;  
}tr[maxn];int len,n;  
void bt(int l,int r)  
{  
    len++;int now=len;  
    tr[now].l=l;tr[now].r=r;  
    tr[now].lc=tr[now].rc=-1;  
    tr[now].c=0;  
    if (l<r)  
    {  
        int mid=(l+r)>>1;  
        tr[now].lc=len+1;bt(l,mid);  
        tr[now].rc=len+1;bt(mid+1,r);  
    }  
}  
void change(int now,int l,int r)  
{  
    if (tr[now].l==l && tr[now].r==r) {tr[now].c=1;return;}  
    int mid=(tr[now].l+tr[now].r)>>1,lc=tr[now].lc,rc=tr[now].rc;  
    if (r<=mid) change(lc,l,r);  
    else if (l>mid) change(rc,l,r);  
    else change(lc,l,mid),change(rc,mid+1,r);  
    if (!tr[now].c) tr[now].c=(tr[lc].c&tr[rc].c);  
}  
bool query(int now,int l,int r)  
{  
    if (tr[now].c) return true;  
    if (tr[now].l==l && tr[now].r==r) return tr[now].c;  
    int mid=(tr[now].l+tr[now].r)>>1,lc=tr[now].lc,rc=tr[now].rc;  
    if (r<=mid) return query(lc,l,r);  
    else if (l>mid) return query(rc,l,r);  
    else return (query(lc,l,mid)&query(rc,mid+1,r));  
}  
int mymin(int x,int y) {return (x<y)?x:y;}  
int mymax(int x,int y) {return (x>y)?x:y;}  
bool check(int mid)  
{  
    int i,j,k,l1,l2,r1,r2;  
    for (i=1;i<=n*2;i++) tr[i].c=0;  
    for (i=1;i<=mid;i++) b[i]=a[i];  
    sort(b+1,b+1+mid,cmp);  
    for (i=1;i<=mid;)  
    {  
        for (j=i;j<=mid && b[j].c==b[i].c;j++);  
        l1=l2=b[i].l;r1=r2=b[i].r;//[l1,r1]是交集区间 [l2,r2]是并集区间  
        for (k=i+1;k<j;k++)  
        {  
            l1=mymin(l1,b[k].l);  
            l2=mymax(l2,b[k].l);  
            r1=mymax(r1,b[k].r);  
            r2=mymin(r2,b[k].r);  
        }  
        if (l2>r2) return true;  
        if (query(1,l2,r2)) return true;  
        change(1,l1,r1);i=j;  
    }return false;  
}  
int main()  
{  
    freopen("bales.in","r",stdin);  
    freopen("bales.out","w",stdout);  
    int q,i,l,r,bk;  
    scanf("%d%d",&n,&q);  
    len=0;bt(1,n);  
    for (i=1;i<=q;i++)  
        scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].c);  
    l=1;r=q;bk=0;  
    while (l<=r)//二分  
    {  
        int mid=(l+r)>>1;  
        if (check(mid)) {bk=mid;r=mid-1;}  
        else l=mid+1;  
    }  
    printf("%d\n",bk);  
    return 0;  
}
```




---

## 作者：Position (赞：3)

出现矛盾的区间符合两个条件之一：

1.题目中的两个干草堆没有任何数量是一样的，所以如果两个区间没有交集并且它们的最小值相同，则这两个区间产生矛盾

2.如果一个区间包含另一个区间，被包含的区间的最小值大于另一个区间，则两个区间产生矛盾



考虑对原先问答的顺序进行二分答案，对于一个二分出的mid作如下处理：


为了方便处理矛盾2，将从1到mid的每个区间的值按照从大到小进行排序


对于值相同的区间，求出并集和交集的范围，如果不存在并集，则mid不可行


维护一颗线段树，将交集的区间覆盖为1


查询并集的区间是否被覆盖为1，如果是，则mid不可行



```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAXN 1000050
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Node
{
    int l,r,val;
    friend bool operator <(Node a,Node b){return a.val>b.val;}
}a[25005],b[25005];
struct Tree
{
    int l,r;
    bool c;
}s[MAXN*4];
int n,m;
inline void build(int l,int r,int pos)
{
    s[pos].l=l,s[pos].r=r;
    s[pos].c=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,pos<<1);
    build(mid+1,r,pos<<1|1);
}
inline void clear(int l,int r,int pos)
{
    s[pos].c=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    clear(l,mid,pos<<1);
    clear(mid+1,r,pos<<1|1);
}
inline void update(int l,int r,int pos)
{
    if(l==s[pos].l&&s[pos].r==r){s[pos].c=1;return;}
    int mid=(s[pos].l+s[pos].r)>>1;
    if(r<=mid) update(l,r,pos<<1);
    else if(l>mid) update(l,r,pos<<1|1);
    else update(l,mid,pos<<1),update(mid+1,r,pos<<1|1);
    if(!s[pos].c) s[pos].c=(s[pos<<1].c&s[pos<<1|1].c);
}
inline bool query(int l,int r,int pos)
{
    if(s[pos].c) return 1;
    if(l==s[pos].l&&s[pos].r==r) return s[pos].c;
    int mid=(s[pos].l+s[pos].r)>>1;
    if(r<=mid) return query(l,r,pos<<1);
    else if(l>mid) return query(l,r,pos<<1|1);
    else return (query(l,mid,pos<<1)&query(mid+1,r,pos<<1|1));
}
bool check(int mid)
{
    clear(1,n,1);
    for(int i=1;i<=mid;i++) b[i]=a[i];
    sort(b+1,b+mid+1);
    int l1,l2,r1,r2,j;
    for(int i=1;i<=mid;i=j)
    {
        j=i;
        while(j<=mid&&b[j].val==b[i].val) j++;
        l1=r2=999999999;l2=r1=-1;
        for(int k=i;k<j;k++)
        {
            l1=min(l1,b[k].l);
            l2=max(l2,b[k].l);
            r1=max(r1,b[k].r);
            r2=min(r2,b[k].r);
        }
        if(l2>r2) return 0;
        if(query(l2,r2,1)) return 0;
        update(l1,r1,1);
    }
    return 1;
}
int main()
{
    n=read(),m=read();
    build(1,n,1);
    for(int i=1;i<=m;i++)
        a[i].l=read(),a[i].r=read(),a[i].val=read();
    int l=1,r=m,ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    printf("%d",(ans+1)%(m+1));
}
```cpp

---

## 作者：xiazha (赞：2)

显然，根据此题的单调性，我们采用二分答案解题。

设目前二分的答案为 $id$。那么有两种情况是矛盾的。

- 题目中说元素互不相同，则若两个不相交的区间最小值相等的话，矛盾。

- 若两个最小值相同区间的并其中包含的某个区间在题目给定条件中的最小值比这两个集合的最小值小，矛盾。

但是我们不能暴力判断这两个条件，所以考虑将 $x_1$ 至 $x_{id}$ 由大至小排序。

维护每个 $x$ 相等的区间，记录 $minl$，$minr$，$maxl$，$maxr$，表示此区间内最小的 $l_i$，$r_i$ 与最大的 $l_i$，$r_i$。

对于第一种情况，十分简单，若 $maxl > minr$，则产生矛盾。

对于第二种情况，这是一个棘手的问题。由于此时判断过了第一种情况，也就是说 $maxl \leq minr$，所以每两个区间的并都包含了 $maxl$ 到 $minr$ 区间。于是我们只需判断之前这个区间内是不是已经被完全覆盖，但是我们不能暴力判断。考虑并查集，维护数组连通性即可，若读者不知道如何用并查集维护数组连通性，见 [P2391](https://www.luogu.com.cn/problem/P2391)。

---

## 作者：scp020 (赞：1)

# P2898 [USACO08JAN] Haybale Guessing G 题解

集训考到的题，赛时没想出来，很巧妙的做法。

## 解法

前置芝士：线段树，二分。

注意到题面要我们求最早与前面的条件有矛盾的条件的编号，所以这个答案是有单调性的，即假设前 $i$ 个条件有矛盾，则对于所有的 $j > i$，前 $j$ 个条件也有矛盾。相应的，对于所有的 $j < i$，前 $j$ 个条件没有矛盾。就此单调性，我们考虑二分答案。下面考虑如何写这个 check。

考虑什么时候条件之间有矛盾，分两种情况，如下图所示。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/dgt4tac3.png)

1. 因为题中说数组中的数字互不相同，所以如果两个相离的区间的最小值相同，则两条件一定矛盾。这个情况显然。

2. 如果区间 $A$ 包含区间 $B$，且区间 $A$ 的最小值大于区间 $B$ 的最小值则两条件一定矛盾。这个情况显然。

所以我们使用线段树标记区间，看是否违反情况二。用简单的循环就可以判断是否违反情况一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO
{
	/*
	fast input/output
	*/
};
using namespace fast_IO;
int n,q,l=1,r,mid,ans;
/**
 * seg_node:
 * 1. sum,lazy,lc,rc
 * 2. pushup
 * 3. pushdown
 * 
 * segment_tree:
 * 1. build
 * 2. clear
 * 3. fix
 * 4. ask
*/
#define ls l,mid
#define rs mid+1,r
struct seg_node
{
	int sum,lazy;
	seg_node *lc,*rc;
	inline void pushup()
	{
		sum=lc->sum+rc->sum;
	}
	inline void pushdown(const int &l,const int &r)
	{
		if(lazy)
		{
			int mid=(l+r)/2;
			lc->sum=mid-l+1,rc->sum=r-mid,lc->lazy=rc->lazy=1,lazy=0;
		}
	}
};
class seg_tree
{
private:
	seg_node *root;
	inline seg_node *build(int l,int r)
	{
		seg_node *rt=new seg_node;
		if(l<r)
		{
			int mid=(l+r)/2;
			rt->lc=build(ls),rt->rc=build(rs);
		}
		return rt;
	}
	inline void clear(seg_node *rt,int l,int r)
	{
		rt->sum=rt->lazy=0;
		if(l<r)
		{
			int mid=(l+r)/2;
			clear(rt->lc,ls),clear(rt->rc,rs);
		}
	}
	inline void fix(seg_node *rt,const int &L,const int &R,int l,int r)
	{
		if(L<=l && r<=R)
		{
			rt->sum=r-l+1,rt->lazy=1;
			return;
		}
		rt->pushdown(l,r);
		int mid=(l+r)/2;
		if(L<=mid) fix(rt->lc,L,R,ls);
		if(R>mid) fix(rt->rc,L,R,rs);
		rt->pushup();
	}
	inline int ask(seg_node *rt,const int &L,const int &R,int l,int r)
	{
		if(L<=l && r<=R) return rt->sum;
		rt->pushdown(l,r);
		int mid=(l+r)/2,ret=0;
		if(L<=mid) ret+=ask(rt->lc,L,R,ls);
		if(R>mid) ret+=ask(rt->rc,L,R,rs);
		return ret;
	}
public:
	inline void build()
	{
		root=build(1,n);
	}
	inline void clear()
	{
		clear(root,1,n);
	}
	inline void fix(const int &L,const int &R)
	{
		fix(root,L,R,1,n);
	}
	inline int ask(const int &L,const int &R)
	{
		return ask(root,L,R,1,n);
	}
};
seg_tree tree;
struct que
{
	int l,r,x;
	inline bool operator<(const que &rhs) const
	{
		return x>rhs.x;
	}
};
que a[25010],tmp[25010];
inline bool judge(int x)
{
	for(int i=1;i<=x;i++) tmp[i]=a[i];
	sort(tmp+1,tmp+x+1),tree.clear();
	for(int i=1,j,l1,l2,r1,r2;i<=x;i=j)
	{
		j=i,l1=l2=tmp[i].l,r1=r2=tmp[i].r;
		while(tmp[i].x==tmp[j].x && j<=x) j++;
		for(int k=i;k<j;k++)
			l1=min(l1,tmp[k].l),r1=max(r1,tmp[k].r),l2=max(l2,tmp[k].l),r2=min(r2,tmp[k].r);
		if(l2>r2) return false;
		if(tree.ask(l2,r2)==r2-l2+1) return false;
		tree.fix(l1,r1);
	}
	return true;
}
int main()
{
	read(n),read(q),r=q,tree.build();
	for(int i=1;i<=q;i++) read(a[i].l),read(a[i].r),read(a[i].x);
	while(l<=r)
	{
		mid=(l+r)/2;
		if(judge(mid)) l=mid+1;
		else ans=mid,r=mid-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：MuelsyseU (赞：1)

**题意：有一个没有重复数的长为 $n$ 的正整数序列，依次给出 $q$ 个条件，表示 $[l,r]$ 区间的最小值为 $x$，求第一个与之前的条件矛盾的条件。**

## 1. 关于该做法

实质上本题这种求最早矛盾处的类型无非是并查集或者二分，其中本题运用二分的方法可以得到一系列非常简单的区间覆盖的做法，而区间覆盖问题可以用线段树做也可以用并查集维护，这样最优可以达到 $O(q\log q \operatorname\alpha(n))$ 的复杂度。这个复杂度由于常数小可以跑出最优解，在思维上也没有什么难度。

但是这种思路的核心是每次 `check` 时把前缀的一部分询问按照 $x$ 从大到小排序处理覆盖。而其实本题可以采用离线做法直接整体按 $x$ 排序，然后利用 **区间历史最值** 的方式得到一个区间出现冲突的 **时间**。这种做法的核心思想是不使用二分，而是通过线段树处理出若干次冲突发生的时间，通过 **取 `min`** 的方式更新答案最后输出。复杂度为 $O(q \log n)$。

## 2. 思想

本题一共存在 **三种矛盾情况**，分别是：

1. 注意到这个数组元素都不超过 $10^9$ 并且没有重复数，那么假如 $x$ 很大以至于就算把 $x,x+1,...,10^9$ 都放在给定区间内也填不满这一区间的长度 $(r-l+1)$，显然自相矛盾。

2. 对于相同 $x$ 值的若干个条件，它们实质上限定了这个 $x$ 一定出现在它们给定区间的 **交** 区间中（因为没有重复），那么如果出现没有交集的情况即为矛盾。

3. 考虑它们的交集 $[l,r]$，如果存在一个条件 $(l',r',x')$ 使得 $x'>x$，那么 $[l`,r`]$ 区间内都不能放 $x$ 这个数，我们称 $[l`,r`]$ 被覆盖。假如 $[l,r]$ 全部被若干个这样的其它区间覆盖，那就没有位置放置 $x$，矛盾。

把三种矛盾情况各次发生的时间取 $min$ 即可。

**首先考虑没有重复 $x$ 值的情况。**

我们把询问排序，按 $x$ 从大到小访问每个区间。这样依次区间查询并在线段树上覆盖 $[l,r]$，那么如果被查询的区间全部被覆盖过就存在矛盾。

但是问题是我们不知道发生矛盾的具体时间。可以发现这时候线段树上每个位置只有被覆盖和没被覆盖两种状态，没有充分利用每个位置的权值。于是可以**用节点的权值维护时间**。

设从大到小遍历到第 $j$ 个区间，把 $[l,r]$ 修改成这个条件**在输入顺序中**的下标 $i$，维护每一位置的历史最小值，**也就是这个位置第一次被比当前 $x$ 更大的区间覆盖的时间**，初始每一位置是 $∞$。那么对于一个区间 $[l,r]$，我们只需查询这个区间**历史最小值的最大值**，也就是这个区间第一次出现无法放置 $x$ 的情况时间，如果不是 $∞$ 那么存在矛盾，再用这个最大值与第 $j$ 个区间的 $i$ 值取 $max$ 的值更新 $ans$。

区间历史最值可以用 ~~吉老师线段树~~ _Segment Tree Beats_ 来维护。这种做法在 [洛谷日报](https://www.luogu.com.cn/blog/Hakurei-Reimu/seg-beats) 等文章中有详细的说明。

**考虑有重复 $x$ 值的情况。**

这时候我们需要考虑到区间 **交** 的问题。可以发现假如按照输入顺序处理，那么每读入一个条件 $(l,r,x)$，都意味着能放置 $x$ 的区间缩小到了 $[l,r]$ 与之前所有 $x$ 相等的区间的交区间。但是交区间必须**按照原顺序**逐步缩小。

综上所述，我们**以 $x$ 从大到小为第一关键字，初始下标 $i$ 从小到大为第二关键字把条件排序**。遍历所有条件，把所有 $x$ 相同的区间按照顺序统一处理，并且查询当前交区间的历史最值。把这个值和当前遍历到的区间的 $i$ 值取 $min$，也就是说到 $i$ 这个时候交区间被缩小到不能再容纳 $x$ 的程度。

## 3. 实现

1. 区间历史最值线段树空间常数较大，最好用函数式线段树来压缩空间。
2. 为了避免同 $x$ 值的区间互相覆盖影响答案，应该在这些区间都查询完毕后再统一处理修改。

```cpp
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
using namespace std;

//STB
struct SegTree {
    int l,r,cnt=1;
    int mx,ms,tag=-1;
} t[2000010];
int T,n,m,tot,ans=inf;
void maintain(int p){
    t[p].mx=max(t[t[p].l].mx,t[t[p].r].mx);
    t[p].ms=max(t[t[p].l].ms,t[t[p].r].ms);
    if(t[t[p].l].mx!=t[t[p].r].mx) t[p].ms=max(t[p].ms,min(t[t[p].l].mx,t[t[p].r].mx));
    t[p].cnt=0;
    t[p].cnt+=(t[p].mx==t[t[p].l].mx?t[t[p].l].cnt:0);
    t[p].cnt+=(t[p].mx==t[t[p].r].mx?t[t[p].r].cnt:0);
}
int build(int l,int r){
    int p=++tot;
    if(l==r) t[p].mx=inf;
    else {
        int mid=(l+r)>>1;
        t[p].l=build(l,mid);
        t[p].r=build(mid+1,r);
        maintain(p);
    }
    return p;
}
void update(int p,int k){
    if(k<t[p].mx) t[p].mx=t[p].tag=k;
}
void spread(int p){
    if(~t[p].tag){
        update(t[p].l,t[p].tag);
        update(t[p].r,t[p].tag);
        t[p].tag=-1;
    }
}
void change(int p,int pl,int pr,int l,int r,int x){
    if(pl>r||pr<l||x>=t[p].mx) return;
    else if(l<=pl&&pr<=r&&x>t[p].ms) update(p,x);
    else {
        spread(p);
        int mid=(pl+pr)>>1;
        if(l<=mid) change(t[p].l,pl,mid,l,r,x);
        if(r>mid) change(t[p].r,mid+1,pr,l,r,x);
        maintain(p);
    }
}
int ask(int p,int pl,int pr,int l,int r){
    if(pl>=l&&pr<=r) return t[p].mx;
    spread(p);
    int mid=(pl+pr)>>1;
    int ans=0;
    if(l<=mid) ans=max(ans,ask(t[p].l,pl,mid,l,r));
    if(r>mid) ans=max(ans,ask(t[p].r,mid+1,pr,l,r));
    return ans;
}
inline int read(){
    char c=getchar();
    int x=0, f=1;
    while(!isdigit(c)) f=(c=='-'?-1:f),c=getchar();
    while(isdigit(c)) x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x*f;
}
struct Lim {
    int l,r,x,i;
} a[30010];
bool cmp(Lim x,Lim y){
    return x.x==y.x?x.i<y.i:x.x>y.x;
};
int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        a[i].i=i,a[i].l=read(),a[i].r=read(),a[i].x=read();
        // 矛盾情况 1
        if(1e9-a[i].x<a[i].r-a[i].l) ans=min(a[i].i,ans);
    }
    sort(a+1,a+1+n,cmp);
    build(1,m);
    int k=1;
    // 记录当前交区间
    Lim tmp=a[1];
    for(int i=1;i<=n;i++){
        // 统一处理区间修改
        if(a[i].x!=a[k].x){
            for(int j=k;j<i;j++) change(1,1,m,a[j].l,a[j].r,a[j].i);
            tmp=a[i],k=i;
        }
        // 矛盾情况 2
        tmp.l=max(tmp.l,a[i].l);
        tmp.r=min(tmp.r,a[i].r);
        if(tmp.l>tmp.r){
            ans=min(ans,a[i].i);
            continue;
        }
        // 矛盾情况 3
        int t=ask(1,1,m,tmp.l,tmp.r);
        if(t!=inf) ans=min(ans,max(a[i].i,t));
    }
    cout<<(ans==inf?0:ans);
    return 0;
}
```


---

## 作者：YksKuusiTAlv (赞：1)

## pre

首先注意一下翻译里面并没有提到的一点，也是让我没看懂样例的一点，就是这个长度为 $n$ 的数组里面的数**各不相同**。

有很多人用并查集写的这道题，题解里面也有一些用线段树写的，不过我认为我的做法和各位线段树大佬的有些许不同。

## solution

同样，单调性和二分查找这里不再赘述，直接说给定 $n$ 个条件，判断他们是否合法。

根据样例我们可以看出，对于同一个数 $num$ ，如果给定了多个形如 $[l_i,r_i]->num$ 的条件，是可以缩小这个数的范围的。

通俗的说，**我们把线段树上面信息 $data$ 的意义设置为当前（位置/区间）可以放置的最小的数**。

那么，当我们拿到这些条件的时候，我们先给条件以 $num$ 为关键字排序，然后逐一区间修改 $[l_i,r_i]->num$  ，正好可以满足我们的需要，因为一个区间如果最小值为 $num$ ，那么这个区间内的所有数的最小值都是 $num$ ，**因为之前放的数肯定比当前小**，所以直接区间修改即可。

然后我们再次遍历所有条件，看能否找到矛盾。

（墙烈推荐大家根据情况模拟几个例子有利于理解）

情况一：我们查询 $[l_i,r_i]$ 的最小值，发现这个最小值大于 $num_i$ ，那么直接返回失败。因为**出现这种情况当且仅当他的这个区间完全被比他大的数覆盖了**，那么必定有矛盾。

情况二：我们查询 $[l_i,r_i]$ 的最小值，发现这个最小值等于 $num_i$ ，那说明这个条件必定没有矛盾，直接检查下一个即可。

情况三：我们查询 $[l_i,r_i]$ 的最小值，发现这个最小值小于 $num_i$ ，**出现这种情况的唯一可能就是存在一个 $num_j$ ，他的实际范围被多个条件缩小到了一个范围，然后查询 $[l_i,r_i]$ 的时候有更小的数在这个区间里面**，这个时候，我们需要分类讨论。

如果这个比 $num_i$ 小的数完全包含于 $[l_i,r_i]$ ，那么说明不合法。

否则无法说明不合法，直接去找下一个条件。

## code
（放这么丑的代码真是对不起大家的眼睛啦）
```c++
#include <cstring>
#include <algorithm>
#include <cstdio>
#define mp make_pair
#define R register int
#define int long
#define printf Ruusupuu = printf

int Ruusupuu ;

using namespace std ;
typedef long long L ;
typedef long double D ;
typedef unsigned long long G ;
typedef pair< int , int > PI ;
const int N = 1e6 + 10 ;
const int M = 3e4 + 10 ;
const int Inf = 0x3f3f3f3f ;

inline int read(){
	int w = 0 ; bool fg = 0 ; char ch = getchar() ;
	while( ch < '0' || ch > '9' ) fg |= ( ch == '-' ) , ch = getchar() ;
	while( ch >= '0' && ch <= '9' ) w = ( w << 1 ) + ( w << 3 ) + ( ch ^ '0' ) , ch = getchar() ;
	return fg ? -w : w ; 
}

int n , q , mid , lx , rx , dlt , fg [N] ;
struct QS{ int l , r , num ; } a [M] , fq [M] , as [M] ;
inline bool cmp( QS a , QS b ){ return a.num < b.num ; }  

int l [N << 2] , r [N << 2] , data [N << 2] , lz [N << 2] ;
#define ud( x ) data [x] = data [x << 1] < data [x << 1 | 1] ? data [x << 1] : data [x << 1 | 1] ;

inline void sp( int x ){
	if( !lz [x] ) return ;
	int k = lz [x] ; lz [x] = 0 ;
	data [x << 1] = lz [x << 1] = data [x << 1 | 1] = lz [x << 1 | 1] = k ;
}

void build( int x , int ll , int rr ){
	l [x] = ll , r [x] = rr , data [x] = Inf ; lz [x] = 0 ;
	if( ll == rr ) return ; 
	int mid = ( ll + rr ) >> 1 ;
	build( x << 1 , ll , mid ) , build( x << 1 | 1 , mid + 1 , rr ) ;
}

void cge( int x ){
	if( l [x] >= lx && r [x] <= rx ){ data [x] = lz [x] = dlt ; return ; }
	sp( x ) ; 
	int mid = ( l [x] + r [x] ) >> 1 ;
	if( lx <= mid ) cge( x << 1 ) ;
	if( rx > mid ) cge( x << 1 | 1 ) ;
	ud( x ) ;  
}

int ask( int x ){
	if( l [x] >= lx && r [x] <= rx ) return data [x] ;
	sp( x ) ;
	int mid = ( l [x] + r [x] ) >> 1 , ans = Inf ;
	if( lx <= mid ) ans = min( ans , ask( x << 1 ) ) ;
	if( rx > mid ) ans = min( ans , ask( x << 1 | 1 ) ) ;
	return ans ;
}

void sc(){
	n = read() , q = read() ;
	for( R i = 1 ; i <= q ; i ++ ) a [i].l = read() , a [i].r = read() , a [i].num = read() ;
}

inline bool check(){
	build( 1 , 1 , n ) ; 
	for( R i = 1 ; i <= mid ; i ++ ) fq [i] = a [i] , as [i].l = as [i].r = as [i].num = fg [i] = 0 ;
	sort( fq + 1 , fq + 1 + mid , cmp ) ;

	int ls = fq [1].l , rs = fq [1].r , now = fq [1].num , top = 0 ;
	
	//多次使用记得清空 
	
	for( R i = 2 ; i <= mid ; i ++ ){
		if( now != fq [i].num ){
			as [++ top].num = now , as [top].l = ls , as [top].r = rs ;
			lx = ls , rx = rs , dlt = now , cge( 1 ) ;
			now = fq [i].num , ls = fq [i].l , rs = fq [i].r ;
		}
		 
		else{
			ls = max( ls , fq [i].l ) , rs = min( rs , fq [i].r ) ;
			if( rs < ls ) return 0 ;
		}
	} 
	as [++ top].num = now , as [top].l = ls , as [top].r = rs ;
	lx = ls , rx = rs , dlt = now , cge( 1 ) ;
	
	//先把所有条件都插入
	
	for( R i = 1 ; i <= mid ; i ++ ){
		lx = fq [i].l , rx = fq [i].r ;	
		int sn = ask( 1 ) ; 
		if( sn > fq [i].num ) return 0 ;
		if( sn < fq [i].num ){
			for( R j = 1 ; j <= top ; j ++ )	
				if( as [j].num == sn ){
					if( as [j].l >= lx && as [j].r <= rx ) return 0 ;
					else break ;
				}
		} 
	}  // 再逐一寻找矛盾
	
	return 1 ;

}

void work(){
	int lside = 1 , rside = q , ans = 0 ;
	while( lside <= rside ){
		mid = ( lside + rside ) >> 1 ;
		if( check() ) ans = mid , lside = mid + 1 ;
		else rside = mid - 1 ;
	}
	printf( "%ld\n" , ( ans + 1 ) % ( q + 1 ) ) ; //直接一个简洁写法，不用if else
}

signed main(){	
	sc() ;
	work() ;
	return 0 ;
} 
```


---

## 作者：Billion (赞：0)

发现结果具有单调性，于是我们可以二分最早能确定条件矛盾的位置 $m$，于是现在我们只需判定 $1 \sim m$ 中的条件是否矛盾即可。

##

如何判定呢？我们可以对每个条件的限制做如下转化：

- 由于序列中的数互不相同，显然对于所有 $x$ 相同的条件，若它们区间的交集为空则一定矛盾，否则设它们的交集为 $[l,r]$，则需要满足 $[l,r]$ 中的数都大于等于 $x$ 且至少存在一个 $x$，而如果此时存在另一个条件 $(l',r',x')$ 满足 $[l,r] \subset [l',r']$ 且 $x'>x$，容易发现此时就一定会发生矛盾了。
    
  注意这里的 **$[l,r]$** 是某些**x相同的区间的交集**，而 **$[l',r']$** 是某个**单独的区间**（因为此时所有的单独区间都应被考虑，不只是交集），别弄混了。

- 这样我们已经说明了这个转化的必要性，而不难发现不满足这些（即所有 $x$ 相同的区间的交集不为空且这些区间的交集不被其他任一 $x$ 更大的区间包含）时，一定能构造出合法方案（只需在区间交集的没有被更大的 $x$ 覆盖的任一位置填 $x$ 即可，这样既能使自身合法也能不破坏其他条件），于是其也具有充分性。

故该转化与原题意是等价的，我们就可以直接按照这个做了。

##

具体地，二分一个 $m$ 之后，我们把 $1 \sim m$ 的条件按 $x$ 从大到小排序，然后先判断所有 $x$ 相同的区间是否有交（若没有说明矛盾），再依次遍历每个条件，每遍历到一个不同的 $x$ 就把其对应的所有条件的所有区间都打上标记。在打标记之前，要判断这些区间的交是否已经全部被标记了，若是，则因为一定是被 $x$ 更大的条件打上的标记，一定会发生矛盾；否则继续遍历。若能顺利遍历完，则没有矛盾。过程中区间标记与查询都可以用线段树完成（标记是区间赋值 $1$，查询是否被覆盖是看区间和是否等于区间长度）。

##

于是就做完了，时间复杂度 $O(\log q(q \log q+q \log n))$。~~好像可以用更快的并查集维护，不过线段树比较无脑~~。

**code：**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int oo=1e9+10; 
int n,q;
struct www{
	int l,r,x;
}a[30010],t[30010];
bool cmp(www A,www B){return A.x>B.x;}
// 基本线段树操作
int tr[4000010],b[4000010];
void pd(int l,int r,int p){
	if(l==r or b[p]==-1) return;
	int mid=(l+r)>>1;
	tr[p<<1]=b[p]*(mid-l+1); b[p<<1]=b[p];
	tr[p<<1|1]=b[p]*(r-mid); b[p<<1|1]=b[p];
	b[p]=-1;
}
void update(int l,int r,int ll,int rr,int p){
	if(ll>=l and rr<=r){
		tr[p]=(rr-ll+1);
		b[p]=1;
		return;
	}
	pd(ll,rr,p);
	int mid=(ll+rr)>>1;
	if(l<=mid) update(l,r,ll,mid,p<<1);
	if(r>mid) update(l,r,mid+1,rr,p<<1|1);
	tr[p]=tr[p<<1]+tr[p<<1|1];
}
int sum(int l,int r,int ll,int rr,int p){
	if(ll>=l and rr<=r) return tr[p];
	pd(ll,rr,p);
	int mid=(ll+rr)>>1,res=0;
	if(l<=mid) res+=sum(l,r,ll,mid,p<<1);
	if(r>mid) res+=sum(l,r,mid+1,rr,p<<1|1);
	return res;
}
bool check(int m){
	for(int i=1;i<=m;++i) t[i]=a[i];
	sort(t+1,t+m+1,cmp); 
	tr[1]=0; b[1]=0;
	int lj=t[1].l,rj=t[1].r,lb=t[1].l,rb=t[1].r;
  // [lj,rj]是目前x相同的区间的交。
  // [lb,rb]是目前x相同的区间的并，因为合法时所有x相同的区间有交，所以它们的并也是一个连续区间，很好维护。
	for(int i=2;i<=m;++i){
		if(t[i].x==t[i-1].x){
			if(t[i].l>rj or lj>t[i].r) return 0;
			lj=max(lj,t[i].l); rj=min(rj,t[i].r);
			lb=min(lb,t[i].l); rb=max(rb,t[i].r);
		}
		else{
			if(sum(lj,rj,1,n,1)==rj-lj+1) return 0;
			update(lb,rb,1,n,1);
			lj=t[i].l; rj=t[i].r; lb=t[i].l; rb=t[i].r;
		}
	}
	if(sum(lj,rj,1,n,1)==rj-lj+1) return 0;
	return 1;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for(int i=0;i<=(n<<2);++i) b[i]=-1;
	for(int i=1;i<=q;++i) cin >> a[i].l >> a[i].r >> a[i].x;
	int l=1,r=q,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else{
			ans=mid;
			r=mid-1;
		}
	}
	cout << ans << '\n';
	return 0;
}

```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P2898)

# 前置知识

[二分答案](https://oi-wiki.org/basic/binary/#二分答案) | [并查集](https://oi-wiki.org/ds/dsu/)

# 解法

对条件的合法性判断其他题解已经讲得很明白了，这里不再赘述。这里主要讲一下用并查集实现黑白染色问题。

以下内容称被覆盖为黑色，不被覆盖为白色。

本题因为是单向染色，即从白到黑，故可类似 [luogu P1840 Color the Axis](https://www.luogu.com.cn/problem/P1840) 和 [D](https://oi-wiki.org/topic/dsu-app/#d) 的并查集或线段树做法；如果是双向染色，则需要 [CF915E Physical Education Lessons](https://www.luogu.com.cn/problem/CF915E) 的珂朵莉树或线段树做法。

[luogu P1840 Color the Axis](https://www.luogu.com.cn/problem/P1840) 在染色的过程中，我们只关注白色的数量。题意可以转换为给定 $n$ 棵树组成的森林，每次操作将 $[l_i,r_i]$ 的树删除，求每个操作执行后剩余的树的个数。删除第 $i$ 棵树等效替代于将第 $i$ 棵树和第 $i-1$ 或第 $i+1$ 棵树合并为一棵树。为方便理解，我们将第 $i$ 棵树和第 $i+1$ 棵树合并为以 $i+1$ 为父亲节点，以 $i$ 为子节点的一棵（子）树。本题要求求该位置是否为黑色，但同样可以用类似的方法进行合并。
  - 例子：设 $n=5,m=1$ 时操作为将 $[2,4]$ 的树删除。过程如下
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/doqymj5s.png)

    ![](https://cdn.luogu.com.cn/upload/image_hosting/r9o292va.png)

    ![](https://cdn.luogu.com.cn/upload/image_hosting/9djwtjyu.png)

    ![](https://cdn.luogu.com.cn/upload/image_hosting/q5j1b1gy.png)

	经路径压缩后如下
	
	![](https://cdn.luogu.com.cn/upload/image_hosting/doqymj5s.png)

    ![](https://cdn.luogu.com.cn/upload/image_hosting/r9o292va.png)

    ![](https://cdn.luogu.com.cn/upload/image_hosting/9wvr4725.png)

    ![](https://cdn.luogu.com.cn/upload/image_hosting/rtnqermh.png)

  - 这里可以感性理解下。作者语文功底不是很好，可能解释不是很清楚。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	int l,r,x;
}a[1000002],b[1000002];
int f[1000002];
bool cmp(node a,node b)
{
	if(a.x==b.x)
	{
		if(a.l==b.l)
		{
			return a.r<b.r;
		}
		else
		{
			return a.l<b.l;
		}
	}
	else
	{
		return a.x>b.x;
	}
}
int find(int x)
{
	return (f[x]==x)?x:f[x]=find(f[x]);
}
bool check(int mid,int n)
{
	int i,j,maxl,maxr,minl,minr,ls;
	for(i=1;i<=n+1;i++)//第n棵树要和第n+1棵树合并
	{
		f[i]=i;
	}
	for(i=1;i<=mid;i++)
	{
		b[i].l=a[i].l;
		b[i].r=a[i].r;
		b[i].x=a[i].x;
	}
	sort(b+1,b+1+mid,cmp);
	ls=b[1].x;
	maxl=minl=b[1].l;
	maxr=minr=b[1].r;
	for(i=2;i<=mid;i++)
	{
		if(ls==b[i].x)
		{
			maxl=max(maxl,b[i].l);
			minl=min(minl,b[i].l);
			maxr=max(maxr,b[i].r);
			minr=min(minr,b[i].r);
			if(maxl>minr)
			{
				return false;
			}
		}
		else
		{ 
			if(find(maxl)>minr)
			{
				return false;
			}
			else
			{
				for(j=find(minl);j<=maxr;j=find(j+1))//将第j棵树和第j+1棵树合并为同一棵树
				{
					f[j]=f[j+1];
				}
				ls=b[i].x;
				maxl=minl=b[i].l;
				maxr=minr=b[i].r;
			}
		}
	}
	return find(maxl)<=minr;
}
int main()
{
	int n,m,i,l=0,r,mid;
	cin>>n>>m;
	r=m;
	for(i=1;i<=m;i++)
	{
		cin>>a[i].l>>a[i].r>>a[i].x;
	}
	while(l<=r)
	{
		mid=(l+r)/2;
		if(check(mid,n)==true)
		{
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<((r==m)?0:l)<<endl;//注意当没有矛盾时输出0
	return 0;
}
```

---

## 作者：sgl654321 (赞：0)

### 题目大意
- 有一个长度为 $n$ 的数组，其中每个位置上的数都不同。
- 给定 $q$ 条语句，限制 $\min\{a_i\}(i\in[l,r])=x$。
- 请问最多满足到哪一条语句，使得前面所有的语句不会有矛盾。

### 解题思路
首先，显然可以二分答案。因为满足的语句个数越多，成为答案的可能性就越小。同时，如果可以满足 $1\sim x$ 所有的语句，一定能满足 $1\sim x-1$ 所有的语句。

接着我们把原题转化为了一个判定性问题。考虑如何判断。

根据题意，有以下两种情况，是会互相矛盾的。

1. 存在两个区间 $A[l_1,r_1]$ 和 $B[l_2,r_2]$，$A\cap B=\varnothing$，同时 $\min_A=\min_B$。

这种情况，就不符合“其中每个数都不同”这一条件了。

2. 存在两个区间 $A[l_1,r_1]$ 和 $B[l_2,r_2]$，$A\subseteq B$，而 $\min_A<\min_B$。

这种情况中，$A$ 是 $B$ 的真子集，说明 $A$ 的最小值一定大于等于 $B$ 的最小值。如果 $\min_A<\min_B$ 显然就矛盾了。

容易想到对所有的语句按照最小值 $x$ 从大到小排序，然后进行区间覆盖和查询。这里将使用线段树求解。

排序之后，我们把 $x$ 相等的语句整理在一起，并求出这些语句提到的区间的**交集**和**并集**。

如果**交集**为空，就出现了第一种会互相矛盾的情况，可以直接跳过。如果非空，则这个最小值 $x$ 一定出现在这个交集内，这个并集内的最小值一定等于 $x$。

我们区间查询这个**交集**是否以前被完全覆盖过。如果被完全覆盖过，那么就出现了第二种互相矛盾的情况。

如果上述两步都没有出现互相矛盾，那么我们将这个**并集**进行区间覆盖。


### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long l,r,x;
}a[25010],b[25010];
struct xianduanshu{
	long long l,r,sum,tag;
	//线段树中，存储一个区间内被覆盖过的点有几个。 
}t[4000010];
long long n,q,l,r,mid,ans,zuixiao;
long long bingx,bingy,jiaox,jiaoy,len;
bool cmp(node n1,node n2){
	return n1.x>n2.x; 
}
void build(long long i,long long l,long long r){
	t[i].l=l;t[i].r=r;
	t[i].sum=t[i].tag=0;
	if(l==r)return;
	long long mid=(l+r)>>1;
	build(i*2,l,mid);
	build(i*2+1,mid+1,r);
}
void down(long long i){
	if(t[i].tag==0)return;
	t[i*2].tag=t[i].tag;
	t[i*2+1].tag=t[i].tag;
	t[i*2].sum=t[i*2].r-t[i*2].l+1;
	t[i*2+1].sum=t[i*2+1].r-t[i*2+1].l+1;
	t[i].tag=0;
}
void chaxun(long long i,long long l,long long r){
	if(l<=t[i].r&&r>=t[i].l){
		if(l<=t[i].l&&r>=t[i].r){
			len+=t[i].sum;
			return;
		} 
		down(i);
		chaxun(i*2,l,r);
		chaxun(i*2+1,l,r);
	}
}
void xiugai(long long i,long long l,long long r){
	if(l<=t[i].r&&r>=t[i].l){
		if(l<=t[i].l&&r>=t[i].r){
			t[i].sum=t[i].r-t[i].l+1;
			t[i].tag=1;
			return;
		} 
		down(i);
		xiugai(i*2,l,r);
		xiugai(i*2+1,l,r);
		t[i].sum=t[i*2].sum+t[i*2+1].sum;
	}
}
bool check(long long x){
	for(int i=1;i<=x;i++)
		b[i]=a[i];
	sort(b+1,b+1+x,cmp);//对区间按照 x 从大到小排序 
	build(1,1,n);
	int j;
	for(int i=1;i<=x;){
		j=i;
		while(j+1<=x&&b[j+1].x==b[i].x)j++;
		//处理出 x 相等的一堆区间 
		bingx=jiaox=b[i].l;
		bingy=jiaoy=b[i].r;
		for(int k=i;k<=j;k++){
			bingx=min(bingx,b[k].l);
			bingy=max(bingy,b[k].r);
			jiaox=max(jiaox,b[k].l);
			jiaoy=min(jiaoy,b[k].r);
		}
		if(jiaox>jiaoy)return 0;
		//没有交集，说明一个数出现了两次，第一种互相矛盾产生了。
		//交集就是这个数 b[k].x 出现的位置。 
		len=0;chaxun(1,jiaox,jiaoy);//看看区间是否被完全覆盖了。 
		if(len==jiaoy-jiaox+1)return 0;
		//上面说明这个交集区间全部被一个更大的数给覆盖过了
		//说明这个大区间的最小值为 x，但里面有个小区间的最小值
		//小于 x。 第二种互相矛盾的情况产生了。 
		xiugai(1,bingx,bingy);
		//这些并集区间的最小值就是 b[k].x。对并集进行区间覆盖。 
		i=j+1;	
	}
		
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=q;i++)
		cin>>a[i].l>>a[i].r>>a[i].x;
	l=1;r=q;
	while(l<=r){//二分答案。 
		mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	if(ans==q)cout<<0<<endl;
	else cout<<ans+1<<endl;
	return 0;
}
```

---

