# Radio stations

## 题目描述

In the lattice points of the coordinate line there are $ n $ radio stations, the $ i $ -th of which is described by three integers:

- $ x_{i} $ — the coordinate of the $ i $ -th station on the line,
- $ r_{i} $ — the broadcasting range of the $ i $ -th station,
- $ f_{i} $ — the broadcasting frequency of the $ i $ -th station.

We will say that two radio stations with numbers $ i $ and $ j $ reach each other, if the broadcasting range of each of them is more or equal to the distance between them. In other words $ min(r_{i},r_{j})>=|x_{i}-x_{j}| $ .

Let's call a pair of radio stations $ (i,j) $ bad if $ i&lt;j $ , stations $ i $ and $ j $ reach each other and they are close in frequency, that is, $ |f_{i}-f_{j}|<=k $ .

Find the number of bad pairs of radio stations.

## 样例 #1

### 输入

```
3 2
1 3 10
3 2 5
4 10 8
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 3 10
3 2 5
4 10 8
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 1
1 3 2
2 2 4
3 2 1
4 2 1
5 3 3
```

### 输出

```
2
```

## 样例 #4

### 输入

```
5 1
1 5 2
2 5 4
3 5 1
4 5 1
5 5 3
```

### 输出

```
5
```

# 题解

## 作者：chen_qian (赞：14)

发现还没有 CDQ 分治的题解，来写一个。

一个最浅显的思路，就是找

$$ x_i<x_j$$
$$x_i+r_i\ge x_j$$
$$x_i\ge x_j-r_j$$
$$\left|f_i-f_j\right|\le k$$

满足以上四个条件的点对数量。这四个偏序关系让我们很容易想到 CDQ 分治。

~~所以就直接上四维 CDQ 吧~~。

这样会超时，所以，我们考虑简化条件。具体来说，就是把几个不等式合并，然后就可以尝试 CDQ 了。

很容易发现一二三式可以整合成 
	
 $$\left|x_i-x_j\right|\le \min(r_i,r_j)$$
 
 但是我们既然要使用 CDQ ，我们一定要保证不等式两边不会有相互的关系。以上这个式子不满足这个条件。所以我们需要拆掉绝对值，或者 $\min$。但显然，假如我们拆掉绝对值，那式子就拆回去了，所以我们考虑拆右边。那么条件可以化成：
 
 $$ r_j\le r_i$$

$$\left|x_i-x_j\right|\le r_j$$

$$\left|f_i-f_j\right|\le k$$

所以我们先将所有点按 $r_i$ 排序，考虑如何满足下面两个式子。

这里我们考虑 $\mathrm{i}$ 向  $\mathrm{j}$ 做贡献的话，我们可以发现，假如我们使用双指针的方式来维护二式，首先就是要对于 $x_i$ 进行排序，这可能导致我们将前面的排除后，导致后面的没有统计到，但是三式 $k$ 为定值，所以得出以下顺序。

1. 排序满足一式

2. CDQ 满足三式（单边双指针实现）

4. 数据结构满足二式

这样这个题目就得以解决。

```cpp
#include<bits/stdc++.h>
#define lb(x) x&-x
#define N 100005
using namespace std;
int n,k,m;
long long ans;
int pos1[N],pos2[N];
struct node{
	int x,y,z,L,R;
	int id,flag; 
}p[N];
bool cmp1(node a,node b){
	if(a.y!=b.y) return a.y>b.y;
	if(a.z!=b.z) return a.z<b.z;
	return a.x<b.x; 
}
bool cmp2(node a,node b){
	if(a.z!=b.z) return a.z<b.z;
	if(a.x!=b.x) return a.x<b.x;
	return a.y>b.y;
}
int c[3*N];
void add(int x,int v){
	for(;x<=m;x+=lb(x)) c[x]+=v;
}
int ask(int x){
	int sum=0;
	for(;x;x-=lb(x)) sum+=c[x];
	return sum; 
} 
void clear(int x){
	for(;x<=m;x+=lb(x)){
		if(!c[x]) return ;
		c[x]=0;
	}
}
void solve(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	sort(p+l,p+mid+1,cmp2);
	sort(p+mid+1,p+r+1,cmp2);
	int j1=l,j2=l-1;
	for(int i=mid+1;i<=r;i++){
		while(j1<=mid&&p[i].z-p[j1].z>k) add(p[j1].x,-1),j1++;
		while(j2<mid&&p[j2+1].z-p[i].z<=k){
			j2++; 
			add(p[j2].x,1);
		}
		ans+=ask(p[i].R)-ask(p[i].L-1); 
	}
	for(int i=j1;i<=j2;i++)add(p[i].x,-1);
}
int b[3*N],cnt;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		int a,r,c;
		scanf("%d%d%d",&a,&r,&c);
		p[i].x=a;
		p[i].y=r;
		p[i].z=c;
		p[i].L=max(0,a-r);
		p[i].R=a+r;
		b[++cnt]=p[i].x;
		b[++cnt]=p[i].L;
		b[++cnt]=p[i].R;
	}
	sort(b+1,b+cnt+1);
	m=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;i++){
		p[i].x=lower_bound(b+1,b+m+1,p[i].x)-b;
		p[i].L=lower_bound(b+1,b+m+1,p[i].L)-b;
		p[i].R=lower_bound(b+1,b+m+1,p[i].R)-b;
	}
	sort(p+1,p+n+1,cmp1);
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
} 
```

经过这个题，我们可以得出关于 CDQ 维护偏序问题时的两个小技巧。

1. 对于有交叉关系的偏序式子，可以尝试合并和简化。（实际上本题并没有减少不等式的数量，但是我们把它转化成可以用 CDQ 解决的形式）

2. 较复杂的不等式优先使用数据结构解决。





---

## 作者：lzyqwq (赞：4)

[**更好的阅读体验**](https://www.cnblogs.com/MnZnOIerLzy/articles/17181529.html)

# $\texttt{Description}$

**[CodeForces 题目链接](https://codeforces.com/problemset/problem/762/E "CodeForces 题目链接")**

**[洛谷题目链接](https://www.luogu.com.cn/problem/CF762E "洛谷题目链接")**

> - 有 $n$ 个三元组 $(x_i,r_i,f_i)$，求满足以下条件的无序二元组 $(u,v)$ 个数：
>
>   - $|f_u-f_v|\le k$。
>
>   - $x_u-r_u\le x_v\le x_u+r_u$。
>
>   - $x_v-r_v\le x_u\le x_v+r_v$。
>
> - $n\le 10^5$，$k\le 10$，$x_i,r_i\le 10^9$，$f_i\le 10^4$。

# $\texttt{Solution}$

先将所有三元组按照 $r_i$ **从大到小**排序，考虑用 $r$ 小的去覆盖 $r$ 大的，因为这样 $r$ 大的一定能够覆盖到 $r$ 小的。

然后枚举 $n$ 个三元组。对于第 $i$ 个三元组，问题转化为求 $|f_j-f_i|\le k$ 且 $x_i-r_i\le x_j\le x_i+r_i$ 的 $j$ 的个数。注意到 $k\le 10$，枚举每一种智商，对于每一种智商开一棵**权值线段树**，查询 $[x_i-r_i,x_i+r_i]$ 中数的个数。这样空间较大，无法接受，所以使用**动态开点**以及**离散化**策略。查完后再把当前三元组修改到权值线段树上。

这样不会多数少数，且时间复杂度为 $\mathcal{O}(nk\log n)$，空间复杂度为 $\mathcal{O}(n\log n)$，可以接受。

# $\texttt{Code}$

实现细节：

- 可以用指令集卡常。

- 我用指针实现动态开点线段树，注意时刻判断节点是否为 `nullptr`（修改中就新建节点，查询中就返回 $0$）。并且 CodeForces 的结构体指针初始化**不为 `nullptr`**，要写构造函数。

- 离散化可以用 `set` 和 `map` 实现，节省码量。`map` 也可以用 `unordered_map`，但是遇到特意卡哈希的数据就不可行了（下同）。

- 由于智商的值域较大，所以每种智商对应的动态开点线段树的根用 `map` 映射一下。

- 查询的时候，判断一下当前智商中是否有值，可以用 `find` 实现，否则直接访问 `map` 会新建节点，带来更大的空间。

- 不开 `long long` 见祖宗。

**[评测记录](https://codeforces.com/contest/762/submission/196077650 "评测记录")**

```cpp
//Orz treenology
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include<bits/stdc++.h>
#define N 100005
#define ls x->lson
#define rs x->rson
using namespace std;
int n,k,lsh;
long long ans;
set<int>s;
unordered_map<int,int>mp;
struct radio{
    int x,r,f;
    bool operator<(const radio&b)const{
        return r>b.r;
    }
}a[N];
struct node{
    int sum;
    node*lson,*rson;
    node(){
        sum=0;
        lson=rson=nullptr;
    }
};
map<int,node*>rt;
void up(node*&x){
    x->sum=0;
    if(ls!=nullptr){
        x->sum+=ls->sum;
    }
    if(rs!=nullptr){
        x->sum+=rs->sum;
    }
}
void modify(node*&x,int l,int r,int k,int v){
    if(x==nullptr){
        x=new node;
    }
    if(l^r){
        int m=(l+r)>>1;
        if(k<=m){
            modify(ls,l,m,k,v);
        }else{
            modify(rs,m+1,r,k,v);
        }
        up(x);
    }else{
        x->sum+=v;
    }
}
int query(node*x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return x->sum;
    }
    int m=(l+r)>>1,ret=0;
    if(ls!=nullptr&&ql<=m){
        ret+=query(ls,l,m,ql,qr);
    }
    if(rs!=nullptr&&qr>m){
        ret+=query(rs,m+1,r,ql,qr);
    }
    return ret;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i){
        scanf("%d%d%d",&a[i].x,&a[i].r,&a[i].f);
        s.insert(a[i].x);
        s.insert(a[i].x-a[i].r);
        s.insert(a[i].x+a[i].r);
    }
    for(int i:s){
        mp[i]=++lsh;
    }
    sort(a+1,a+1+n);
    for(int i=1,x,l,r;i<=n;++i){
        x=mp[a[i].x];
        l=mp[a[i].x-a[i].r];
        r=mp[a[i].x+a[i].r];
        for(int j=a[i].f-k;j<=a[i].f+k;++j){
            auto it=rt.find(j);
            if(it!=rt.end()){
                ans+=query(it->second,1,lsh,l,r);
            }
        }
        modify(rt[a[i].f],1,lsh,x,1);
    }
    printf("%lld\n",ans);
}
```


# $\texttt{Reference}$

[【题解】CF1045G AI Robots](https://www.luogu.com.cn/blog/explodingkonjac/solution-cf1045g "【题解】CF1045G AI Robots") by [ExplodingKonjac](https://www.luogu.com.cn/user/279800 "ExplodingKonjac")。

---

## 作者：寒鸽儿 (赞：3)

暴力:  
$O(n^2)$ 枚举所有点对  
优化:  
既然一个点被枚举过,那么我们知道了它的信息,不需要再枚举它了。  
通常对于点对我们都是用一些东西来维护之前的点以便快速查询当前点与之前的点的关系。  
我们要存储信息则要解决 $x,r,f$ 的关系。  
我们注意到 $k \leqslant 10$ 这说明我们可以把之前的点按照频率分开统计,对于当前的点暴力枚举所有符合的频率,这不超过20种。  
然后对于 $x$ 如此大的值域就要用到动态的区间维护的结构,这里采用了动态开点线段树。  
对于 $r$ 的维护方式是:显然我们当前有的信息是该点的半径,我们需要保证之前的点若在该半径内必然满足条件。就把$r$降序排列,这样之前的半径一定大于当前的。  
具体地,对$r$降序排序。对每个$f$建立权值线段树。考虑每个电台,枚举所有符合条件的 $f$ ,查询 $[x-r, x+r]$ 的点的个数统计答案,再把当前点加入频率为$f$的线段树即可。  
复杂度$O(knlogn)$
```cpp
#include <cstdio>
#include <algorithm>
#define ll long long

using namespace std;

const int F = 12345, QlogL = 4567890, N = 123456;
int root[F], ls[QlogL], rs[QlogL], dat[QlogL], tot = 1;
inline int newnode() {
	ls[tot] = rs[tot] = dat[tot] = 0;
	return tot++;
}

inline void update(int p) { 
	dat[p] = (ls[p]?dat[ls[p]]:0) + (rs[p]?dat[rs[p]]:0); 
}

void insert(int p, int lp, int rp, int x) {
	if(lp == rp) {
		++dat[p];
		return;
	}
	int mid = (lp + rp) >> 1;
	if(x <= mid) {
		if(!ls[p]) ls[p] = newnode();
		insert(ls[p], lp, mid, x);
	}
	else {
		if(!rs[p]) rs[p] = newnode();
		insert(rs[p], mid+1, rp, x);
	}
	update(p);
}

int qry(int p, int lp, int rp, int l, int r) {
	if(l <= lp && rp <= r) return dat[p];
	int mid = (lp + rp) >> 1;
	int ans = 0;
	if(l <= mid && ls[p]) ans += qry(ls[p], lp, mid, l, r);
	if(r > mid && rs[p]) ans += qry(rs[p], mid+1, rp, l, r);
	return ans;
}

struct node {
	int x, r, f;
} dt[N];
inline bool cmp1(node& a, node&b) { return a.r > b.r; }

int main() {
	int n, k, xm = 0;
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d %d %d", &dt[i].x, &dt[i].r, &dt[i].f);
		xm = max(dt[i].x, xm);
		root[dt[i].f] = newnode();
	}
	sort(dt + 1, dt + n + 1, cmp1);
	ll cnt = 0;
	for(int i = 1; i <= n; ++i) {
		for(int ft = dt[i].f - k; ft <= dt[i].f + k; ++ft) {
			cnt += qry(root[ft], 1, xm, dt[i].x - dt[i].r, dt[i].x + dt[i].r);
		}
		insert(root[dt[i].f], 1, xm, dt[i].x);
	}
	printf("%lld\n", cnt);
	return 0;
}
```

---

## 作者：子丑 (赞：3)

写给 CDQ 初学者的一篇：

### CDQ 保姆级题解

[题目链接](https://www.luogu.com.cn/problem/CF762E)

题目里有两条式子，$|x_i-x_j| \le \min(r_i, r_j)$，$|f_i-f_j| \le k$，式子里有两个绝对值和一个最小值，不好算，康康能不能拆开。

按照一般的 CDQ 思路，我们有一维是事先排序好的，有序数列就可以不管绝对值和最小值了。那要排序哪一维呢，这题里是 $r$，但是我并不明白怎么才能看出来哪维是用来排序的，

![](https://cdn.luogu.com.cn/upload/image_hosting/akd17wdf.png)

---

先不考虑 $f$ 和 $k$。我们将结构体数组以 $r$ 为关键字从**大到小**排序，那么 $\min(r_i, r_j)=r_{\max(i, j)}$，原来的式子可以变成 $|x_i-x_j| \le r_j \space(i \le j)$，发现它可以拆开变成 $x_j-r_j \le x_i \le x_j+r_j$。在 CDQ 的一次操作中，我们用树状数组统计答案，$x_i$ 用于修改，询问时答案增加 $query(x_j+r_j)-query(x_j-r_j-1)$，此处 $i \in [le, mid], j \in [mid+1, ri]$。$x, r$ 的范围很大，需要进行简单的离散化。

现在考虑 $f$ 和 $k$，维护左右区间 $f$ 递增。 式子 $|f_i-f_j| \le k$ 中绝对值的限制让原先通用的双指针不再通用，所以我们要用三个指针，$i_{dn}, i_{up}, j \space ( i_{dn}, i_{up} \in [ le, mid ], j \in [ mid+1, ri ] ) $，维护 $f_{i_{dn}} \le f_j \le f_{i_{up}} $，此时 $|f_i-f_j| \le k$ 可以转化为 $f_j-f_{i_{dn}} > k$ 和 $f_{i_{up}}-f_j \le k$ 两条式子，那么对询问有贡献的点 $ i \in [ i_{dn},  i_{up} ] $。在移动 $i_{dn}$ 时在树状数组中删除，移动 $i_{up}$ 时在树状数组中添加。

---

就可以写了，上代码。

我树状数组的清空操作用了类似懒标记的东西，可以减小常数。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, a, b) for(int i=(a), i##up=(b); i<=i##up; ++i)
#define repf(i, a) for(int i=1, i##up=(a); i<=i##up; ++i)
#define rrep(i, a, b) for(int i=(a), i##dn=(b); i>=i##dn; --i)
#define repe(e, u) for(int e=head[u]; e; e=nxt[e])

int read() {
	int t=0, f=1; char c;
	while(!isdigit(c=getchar())) f=c^45;
	while(isdigit(c)) t=(t<<1)+(t<<3)+(c^48), c=getchar();
	return f? t: -t;
}

const int N=1e5+10, inf=1e9;

int n, k;
ll ans;

struct BIT {
	#define lb(x) ((x)&-(x))
	static const int X=3e5;
	int c[X+10], tik[X+10], tim;
	inline void modify(int x, int v=1) {
		for(; x<=X; x+=lb(x)) if(tik[x]==tim) c[x]+=v; else tik[x]=tim, c[x]=v;
	}
	inline int query(int x, int v=0) {
		for(; x; x^=lb(x)) if(tik[x]==tim) v+=c[x]; else tik[x]=tim, c[x]=0;
		return v;
	}
	inline void clear() { tim++; }
}tre;

int px[N*3], siz;
inline int find(int x) {
	return lower_bound(px+1, px+1+siz, x)-px;
}
struct state {
	int x, r, f, le, ri;
	state() {}
	state(int a, int b, int c): x(a), r(b), f(c) {}
	inline void get() {
		x=read(), r=read(), f=read();
		le=max(1, x-r), ri=min(inf, x+r);
		px[++siz]=x, px[++siz]=le, px[++siz]=ri;
	}
	inline void reset() {
		x=find(x), le=find(le), ri=find(ri);
	}
}st[N];
bool cmpr(state a, state b) {
	if(a.r==b.r) return a.f<b.f||a.f==b.f&&a.x<b.x;
	return a.r>b.r;
}
bool cmpf(state a, state b) {
	if(a.f==b.f) return a.r>b.r||a.r==b.r&&a.x<b.x;
	return a.f<b.f;
}

void sol(int le, int ri) {
	if(le==ri) return;
	int mid=le+ri>>1;
	sol(le, mid), sol(mid+1, ri), tre.clear();
	sort(st+le, st+mid+1, cmpf), sort(st+mid+1, st+ri+1, cmpf);
	int pi_dn=le, pi_up=le, pj=mid+1;
	while(pj<=ri) {
		while(st[pj].f-st[pi_dn].f>k&&pi_dn<=mid) tre.modify(st[pi_dn++].x, -1);
		while(st[pi_up].f-st[pj].f<=k&&pi_up<=mid) tre.modify(st[pi_up++].x);
		ans+=tre.query(st[pj].ri)-tre.query(st[pj].le-1), pj++;
	}
}

int main() {
	n=read(), k=read();
	repf(i, n) st[i].get();
	sort(px+1, px+1+siz), siz=unique(px+1, px+1+siz)-px-1;
	repf(i, n) st[i].reset();
	sort(st+1, st+1+n, cmpr);
	sol(1, n);
	printf("%lld", ans);
}
```

特别鸣谢：[阿丑](https://www.luogu.com.cn/user/364963)

---

## 作者：EityDawn (赞：2)

很显然，我们要求的点对满足 $|x_i-x_j|\le\min(r_i,r_j)~,~|f_i-f_j|\le k$。

对于 $\min(r_i,r_j)$，可以将 $r_i$ 按照降序排序。

约束条件变为 $|x_i-x_j|\le r_i~,~|f_i-f_j|\le k$。

很显然这是一个二维偏序问题。

将式子展开有 $x_i-r_i\le x_j\le x_i+r_i~,~f_i-k\le f_j\le f_i+k$，$j<i$。

要求的就是有多少 $j$ 满足关系。

那么我们可以权值线段树套权值线段树来完成。

外层存 $x_i$，内层存 $f_i$。

注意询问区间 $[x_i-r_i,x_i+r_i]$ 以及 $x_i$ 要提前离散化。

问题就变成了单点修改+区间询问的树套树。

时间复杂度 $O(n\log^2n)$，空间复杂度也是这个。

### code：

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+10;
const int M=1e4;
const int V=1e9;
const int B=3e5;
bool st;
struct radio{
    int x,r,f;
    bool operator<(const radio&a) const{return a.r<r;}
}a[N];
int n,k;
int to=0,ct=0;
struct SGT{
    int lc,rc;
    int sum;
}tr[N*200];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define sum(x) tr[x].sum
int rt[N<<4],lc[N<<4],rc[N<<4];
int root=0;
void modify(int pos,int l,int r,int &x)
{
    if(!x) x=++ct;
    ++sum(x);
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) modify(pos,l,mid,lc(x));
    else modify(pos,mid+1,r,rc(x));
}
void add(int pos,int f,int l,int r,int &x)
{
    if(!x) x=++to;
    modify(f,1,M,rt[x]);
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) add(pos,f,l,mid,lc[x]);
    else add(pos,f,mid+1,r,rc[x]);
}
ll query(int p,int q,int l,int r,int x)
{
    if(!x) return 0;
    if(p<=l&&q>=r) return sum(x);
    int mid=(l+r)>>1;ll ans=0;
    if(p<=mid) ans+=query(p,q,l,mid,lc(x));
    if(q>mid) ans+=query(p,q,mid+1,r,rc(x));
    return ans;
}
ll query(int p,int q,int f,int l,int r,int x)
{
    if(!x) return 0;
    if(p<=l&&q>=r) return query(max(1,f-k),min(M,f+k),1,M,rt[x]);
    int mid=(l+r)>>1;ll ans=0;
    if(p<=mid) ans+=query(p,q,f,l,mid,lc[x]);
    if(q>mid) ans+=query(p,q,f,mid+1,r,rc[x]);
    return ans;
}
int b[3*N],L[N],R[N],len=0;
bool ed;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i].x>>a[i].r>>a[i].f;
        b[++len]=a[i].x,b[++len]=max(1,a[i].x-a[i].r),b[++len]=min(V,a[i].x+a[i].r);
    }
    sort(b+1,b+1+len);sort(a+1,a+1+n);
    len=unique(b+1,b+1+len)-(b+1);
    for(int i=1;i<=n;i++)
    {
        L[i]=lower_bound(b+1,b+1+len,max(1,a[i].x-a[i].r))-b;
        R[i]=lower_bound(b+1,b+1+len,min(V,a[i].x+a[i].r))-b;
        a[i].x=lower_bound(b+1,b+1+len,a[i].x)-b;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=query(L[i],R[i],a[i].f,1,B,root);
        add(a[i].x,a[i].f,1,B,root);
    }
    cout<<ans;
    return 0;
}
```

****

---

## 作者：This_Rrhar (赞：2)

双倍经验 [CF1045G](https://www.luogu.com.cn/problem/CF1045G)

当点对 $(i,j)$ 合法时有

$$
x_i-r_i\le x_j\le x_i+r_i
$$

$$
x_j-r_j\le x_i\le x_j+r_j
$$

$$
|f_i-f_j|\le k
$$

整理后有

$$
|x_i-x_j|\le\min(r_i,r_j)
$$

$$
f_i\in[f_j-k,f_j+k]
$$

考虑 CDQ 分治，此时不妨认为 $i\le mid<j$，那么以 $r$ 为关键字从大到小排序，消掉 $\min$ 后有

$$
|x_i-x_j|\le r_j
$$

$$
f_i\in[f_j-k,f_j+k]
$$

将左右两半区间分别按照 $f$ 从小到大排序，枚举右半区间每个数的同时，用双指针维护左半区间满足第二条式子的区间，再用树状数组就能得到满足第一条式子的区间。

最后由于值域所以要进行离散化。时间复杂度 $O(n\log^2n)$，问题解决。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _r return*this
#define _o &operator
namespace IO
{
	const int _S=1<<21;
	char b[_S],*p1=b,*p2=b,pb[_S],*pp=pb;
	void fl(){fwrite(pb,1,pp-pb,stdout),pp=pb;}
	struct input
	{
		char gc(){if(p1==p2)p2=(p1=b)+fread(b,1,_S,stdin);return p1==p2?' ':*p1++;}
		input _o>>(char&num){do num=gc();while(num==' '||num=='\n'||num=='\r'||num=='\t');_r;}
		template<typename T>input _o>>(T&x)
		{
			char c=gc();T f=1;
			for(x=0;!isdigit(c);)(c=='-'?f=-1:1),c=gc();
			while(isdigit(c))x=(x*10)+(c^48),c=gc();
			x*=f;_r;
		}
		input(){}
	}in;
	long long read(){long long x;return in>>x,x;}
	struct output
	{
		void pt(char num){*pp++=num;if(pp-pb==_S)fl();}
		output _o<<(char num){pt(num);_r;}
		template<typename T>output _o<<(T x)
		{
			if(!x){pt(48);_r;}
			if(x<0)pt('-'),x=-x;
			int s[64],t=0;
			while(x)s[++t]=x%10,x/=10;
			while(t)pt(s[t--]+48);
			_r;
		}
		output _o<<(const char*s){int num=0;while(s[num])pt(s[num++]);_r;}
		output(){}
	}out;
	struct fe{~fe(){fl();}}fls;
}
using IO::in;
using IO::out;
using IO::read;
using ll=long long;

#define N 100001

ll n,m,k;

struct node{ll p,lp,rp,r,q;}a[N],c[N];
bool cmp1(const node&A,const node&B){return A.r>B.r;}
bool cmp2(const node&A,const node&B){return A.q<B.q;}

ll b[N];

ll ans;

struct BIT
{
#define lowbit(x) (x&-x)
	ll C[N];
	void A(ll p,ll x){while(1<=p&&p<=n)C[p]+=x,p+=lowbit(p);}
	ll Q(ll p)
	{
		if(p<=0)return 0;
		ll s=0;
		p=min(p,n);
		while(p)s+=C[p],p-=lowbit(p);
		return s;
	}
	ll Q(ll l,ll r){return Q(r)-Q(l-1);}
}T;

#define mid ((l+r)>>1)
void CDQ(ll l,ll r)
{
	if(l==r)return;
	CDQ(l,mid),CDQ(mid+1,r);
	ll i=l,j=l-1,p;
	for(p=mid+1;p<=r;p++)
	{
		while(i<=mid&&a[p].q-a[i].q>k)T.A(a[i++].p,-1);
		while(j<mid&&a[j+1].q-a[p].q<=k)T.A(a[++j].p,1);
		ans+=T.Q(a[p].lp,a[p].rp);
	}
	for(p=i;p<=j;p++)T.A(a[p].p,-1);
	sort(a+l,a+1+r,cmp2);
}

int main()
{
	in>>n>>k;
	for(int i=1;i<=n;i++)in>>a[i].p>>a[i].r>>a[i].q,b[i]=a[i].p;
	sort(b+1,b+1+n),m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++)
		a[i].lp=lower_bound(b+1,b+1+m,a[i].p-a[i].r)-b,
		a[i].rp=upper_bound(b+1,b+1+m,a[i].p+a[i].r)-b-1,
		a[i].p=lower_bound(b+1,b+1+m,a[i].p)-b;
	sort(a+1,a+1+n,cmp1),CDQ(1,n),out<<ans;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

首先两个电台 $(i,j)$ 能互相干扰的条件是：$x_i\in[x_j-r_j,x_j+r_j]$，$x_j\in[x_i-r_i,x_i+r_i]$，$|f_i-f_j|\le k$。

但是这个相互干扰才算一对是不好统计的。注意到在 $r_i\le r_j$ 时，如果有 $x_j\in[x_i-r_i,x_i+r_i]$，那么一定满足 $x_i\in[x_j-r_j,x_j+r_j]$。

于是将所有电台按照 $r_i$ 从大到小排序。对于每一个 $i$，只用统计 $\forall j \in [1,i)$，$x_j\in[x_i-r_i,x_i+r_i]$ 且 $f_j \in [f_i-k,f_i+k]$ 的数量，然后全加起来就是答案。

这算是一个很典的模型了。具体的，将每个电台 $i$ 对应到平面直角坐标系中的点 $(x_i,f_i)$，那么就是查询左下角为 $(x_i-r_i,f_i-k)$ 右上角为 $(x_i+r_i,f_i+k)$ 的矩形中点的数量。

对于每一个 $f_i$ 建以 $x_i$ 为下标的权值线段树。观察到 $k$ 的范围极小，直接枚举 $f_j$ 的可能取值，然后在对应的权值线段树内查询 $[x_i-r_i,x_i+r_i]$ 里点的数量。

时间复杂度 $O(nk\log n)$。

如果 $k$ 更大呢？只能搓树套树了。或者换个做法，用 cdq 分治解决。

# Code

```cpp
#include<bits/stdc++.h>
const int inf=1e9;
struct segment{
	int val;
	int lc,rc;
}t[3200005];
int root[10005],idx;
void add(int&p,int L,int R,int x){
	if(!p)p=++idx;
	++t[p].val;
	if(L==R)return;
	int mid=L+R>>1;
	if(x<=mid)add(t[p].lc,L,mid,x);
	else add(t[p].rc,mid+1,R,x);
}
int ask(int p,int L,int R,int l,int r){
	if(!p)return 0;
	if(L>=l&&R<=r)return t[p].val;
	int mid=L+R>>1;
	if(r<=mid)return ask(t[p].lc,L,mid,l,r);
	if(l>mid)return ask(t[p].rc,mid+1,R,l,r);
	return ask(t[p].lc,L,mid,l,r)+ask(t[p].rc,mid+1,R,l,r);
}
std::tuple<int,int,int>a[100005];
int n,m;
long long ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d%d%d",&std::get<1>(a[i]),&std::get<0>(a[i]),&std::get<2>(a[i]));
	std::stable_sort(a+1,a+n+1);
	for(int i=n;i;--i){
		for(int j=std::max(1,std::get<2>(a[i])-m);j<=std::min(10000,std::get<2>(a[i])+m);++j)
			ans+=ask(root[j],1,inf,std::max(1,std::get<1>(a[i])-std::get<0>(a[i])),std::min(inf,std::get<1>(a[i])+std::get<0>(a[i])));
		add(root[std::get<2>(a[i])],1,inf,std::get<1>(a[i]));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Z1qqurat (赞：1)

很 trivial 的 *$2200$。提供一种不依赖于 $k$ 大小的解法，目前排在最优解 rk 5，没有卡常。

首先最棘手的就是互相看到这个限制，这其实很像我们以 $c$（题目中的作用半径 $r$）为半径画一个圆，然后两个点要都在对方的圆中，考虑将点按照 $c$ 从大到小排序，那么现在如果点 $i<j$，满足 $j$ 能看见 $i$，由于 $c$ 的单调性，那么 $i$ 一定能看见 $j$，所以这就被我们转化为了一个三维偏序问题（已去绝对值）：

$$
\begin{cases}i<j\\ x_i\in[x_j-r_j,x_j+r_j] \\ q_i\in[q_j-k,q_j+k] \\\end{cases}
$$

你发现就下面那俩区间不好做，考虑抓一个来在外部差分：可以转化为对于每个 $i$，求出满足 $x_i\in[0,x_j+r_j]$ 的 $j$ 数量减去满足 $x_i\in[0,x_j-r_j)$ 的 $j$ 数量。这东西就很好做啊，直接 cdq 分治，$i<j$ 是天然的顺序不用管；可以 cdq 分治归并掉第二维了；然后最后这个区间可以在树状数组上做一个差分（反正询问的是区间和，具有可减性），就可以通过跑两遍 cdq 分治解决，记得对 $q_i,q_i-k,q_i+k$ 做离散化。

需要注意一个点：因为这个差分是对**每一个 $i$** 做的，所以两遍 cdq 的时候的数都是要按照同样的顺序，而跑 cdq 的时候对数排序会影响原先的顺序，所以我们记录一个 cdq 之前的按照 $c$ 从大到小排序的数组即可，否则会被 $c$ 相同的一些点卡掉，容易 WA on #6（别问我为什么知道）。

```cpp
#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r) + 1]
using i64 = int64_t;
using db = double;
using std::cin;
using std::cout;
constexpr int N = 1e5 + 5;

namespace Read {
	inline auto get() { return cin.rdbuf()->sbumpc(); }

	template <typename T>
	void read(T& x) {
   	auto c = 0;
   	do c = get();
   	while (std::isspace(c));
   	x = 0;
   	for (; std::isdigit(c); c = get()) x = x * 10 + c - '0';
	}
} //namespace Read
using Read::read;

int n, k, V;
std::array<int, N * 3> tmp;

struct Node {
   int a, c, q, val, l, r, f; //[l,r]:[q-k,q+k]
} ;
std::array<Node, N> d, t;

namespace BIT {
   std::array<int, N * 3> tr;

   auto ask(int x) {
      auto ret = 0;
      for (auto i = x; i; i -= i & (-i)) ret += tr[i];
      return ret;
   }
   auto ask(int x, int y) {
      return ask(y) - ask(x - 1);
   }
   auto upd(int x, int v) {
      for (auto i = x; i <= V; i += i & (-i)) tr[i] += v;
      return ;
   }
   auto clear(int x) {
      for (auto i = x; i <= V; i += i & (-i)) tr[i] = 0;
      return ;
   }

} //namespace BIT

auto solve(int l, int r) {
   if (l >= r) return ;
   auto mid = l + r >> 1;
   solve(l, mid), solve(mid + 1, r);

   std::sort(All(d, l, mid), [&] (Node x, Node y) { return x.a < y.a; });
   std::sort(All(d, mid + 1, r), [&] (Node x, Node y) { return x.val < y.val; });
   auto p = l, q = mid + 1;
   while (q <= r) {
      while (p <= mid && d[p].a <= d[q].val)
         BIT::upd(d[p].q, 1), p++;
      d[q].f += BIT::ask(d[q].l, d[q].r), q++;
   }
   for (auto i = l; i <= mid; ++i) BIT::clear(d[i].q);
   return ;
}

auto main() -> int {
   std::ios::sync_with_stdio(false);
   cin.tie(nullptr), cout.tie(nullptr);

   read(n), read(k);
   for (auto i = 1; i <= n; ++i) {
      read(d[i].a), read(d[i].c), read(d[i].q);
      tmp[++V] = d[i].q, tmp[++V] = d[i].q - k, tmp[++V] = d[i].q + k;
   }
   std::sort(All(tmp, 1, V)), V = std::unique(All(tmp, 1, V)) - begin(tmp) - 1;
   for (auto i = 1; i <= n; ++i) {
      d[i].l = std::lower_bound(All(tmp, 1, V), d[i].q - k) - begin(tmp);
      d[i].r = std::lower_bound(All(tmp, 1, V), d[i].q + k) - begin(tmp);
      d[i].q = std::lower_bound(All(tmp, 1, V), d[i].q) - begin(tmp);
      d[i].val = d[i].a + d[i].c;
   }
   std::sort(All(d, 1, n), [&] (Node x, Node y) { return x.c > y.c; });
   for (auto i = 1; i <= n; ++i) t[i] = d[i];
   solve(1, n);
   auto ans = (i64)0;
   for (auto i = 1; i <= n; ++i) {
   	ans += d[i].f, d[i] = t[i];
      d[i].f = 0, d[i].val = d[i].a - d[i].c - 1;    
   }
   solve(1, n);
   for (auto i = 1; i <= n; ++i) ans -= d[i].f;
   cout << ans << "\n";
   return 0;
}
```

---

## 作者：MiRaciss (赞：1)




[更好的体验?](https://www.luogu.com.cn/blog/qq-2056188203/solution-cf762e)


## 题意

在一维坐标轴上分布了 $n$ 个机器人，第个机器人的坐标是 $x_i$ 。

第 $i$ 个机器人的视野是 $r_i$ 。也就是说，第 $i$ 个机器人能看到 $[x_i-r_i,x_i+r_i]$ 范围内的所有其他机器人。

第 $i$ 个机器人的智商是 $f_i$ 如果有一对机器人可以互相看到，并且它们的智商相差不超过 $k$ ，那么它们就可以互相交流。

你需要求出来有多少对机器人可以互相交流。


## 题解

设 $i$ , $j$ 满足 $1\leq i \leq j \leq n$

有两个显然的式子：
$$\begin{cases} |x_i-x_j|\leq \min(r_i,r_j) \\ |f_i-f_j|\leq k \end{cases}$$

我们先忽略掉第二个式子

然后发现第一个式子有 $\min$ 操作，~~挺不好看的~~,考虑以 $r$ 为关键字从大到小排序后，化简得:

$$|x_i-x_j|\leq r_j$$

~~发现绝对值也挺不好看的~~，所以去掉绝对值:

$$\begin{cases} x_i-x_j\leq r_j \\ x_j-x_i\leq r_j \end{cases}$$

转换得到:

$$x_i-r_i\leq x_j\leq x_i+r_i$$

所以答案就转换为了对于每一个 $i$ ，满足 $x_i-r_i\leq x_j\leq x_i+r_i$ 的 $j$ 的个数和，这个很好用线段树维护。

这时我们再来看看第二个式子:

$$|f_i-f_j|\leq k$$

同样可以转换为：

$$f_i-k\leq f_j \leq f_i+k$$

再看看 $f$ 的范围为$10^4$，所以我们直接开$10^4$个线段树，然后再分别维护每个线段树就行了。

## 代码

因为我们考试的时候f的数据范围较大，用了离散化，~~但是不影响过题~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll 

int lsh[200005];
int len=0;

struct ss{
	int x,r,q;
}a[200005];
bool cmp(ss x,ss y){
	if(x.r==y.r)
		return x.x<y.x;
	return x.r>y.r;
}
int n,k;

struct zz{
	int l,r;
	int val;
};

int tot=0;
zz t[4000005];
int rt[200005];
int New_Node(){
	tot++;
	t[tot].l=t[tot].r=t[tot].val=0;
	return tot;
}	
struct Tree{
	#define lc t[p].l
	#define rc t[p].r
	void Push_up(int p){
		int now=0;
		if(lc)	now+=t[lc].val;
		if(rc) 	now+=t[rc].val;
		t[p].val=now;
	}
	void Change_Tree(int p,int l,int r,int x){
		if(l==r){
			t[p].val++;
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			if(!lc)	lc=New_Node();
			Change_Tree(lc,l,mid,x);
		}
		else{
			if(!rc)	rc=New_Node();
			Change_Tree(rc,mid+1,r,x);
		}
		Push_up(p);
	}
	int Find_Tree(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R){
			return t[p].val;
		}
		int mid=(l+r)>>1;
		int now=0;
		if(L<=mid&&lc)
			now+=Find_Tree(lc,l,mid,L,R);
		if(mid+1<=R&&rc)
			now+=Find_Tree(rc,mid+1,r,L,R);
		return now;
	} 
}T[200005];

signed main(){
	int Max=0,Min=0x3f3f3f3f;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&a[i].x,&a[i].r,&a[i].q);
		lsh[++len]=a[i].q;
		Max=max(Max,a[i].x+a[i].r);
		Min=min(Min,a[i].x-a[i].r);
	}	
	sort(a+1,a+n+1,cmp);
	sort(lsh+1,lsh+len+1);
	len=unique(lsh+1,lsh+len+1)-(lsh+1);
	for(int i=1;i<=n;i++)
		rt[i]=New_Node();
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=a[i].q-k;j<=a[i].q+k;j++){
			int now=lower_bound(lsh+1,lsh+len+1,j)-lsh;
			if(lsh[now]!=j)
				continue;
			ans+=T[now].Find_Tree(rt[now],Min,Max,a[i].x-a[i].r,a[i].x+a[i].r);
		}
		int now=lower_bound(lsh+1,lsh+len+1,a[i].q)-lsh;
		T[now].Change_Tree(rt[now],Min,Max,a[i].x); 
	}
	cout<<ans<<endl;
	return 0;
}

```




---

## 作者：hnczy (赞：0)

阅读题目很容易发现几个条件：

$i<j,\min(r_i,r_j)\ge \left| x_i-x_j\right|,\left| f_i-f_j\right| \le k$。

这个 $i<j$ 其实是个烟雾弹，没什么用，因为有没有就是乘不乘二的问题。

好，那么我们就可以直接来分析后面的两个条件。

显然，我们可以进行对 $r$ 排序来消掉 $\min$ 这个烦人的东西。再对绝对值进行讨论，这样我们的式子就变成了 $ f_j-k \le f_i \le k+f_j，x_j-r_j \le x_i \le r_j+x_j$。

因为我们这样的式子基本上使用 CDQ 分治来解决的，但是这是一个区间，那我们就不能用一般的 CDQ 来写了，只能用一个双指针来解决，当然，树状数组只需要用一个区间查询即可。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,k,cnt,ans,b[N];
struct node {
	int x,y,z,ll,rr;
	bool operator <(const node &a)const {
		if(x!=a.x)return x>a.x;
		if(y!=a.y)return y<a.y;
		return z<a.z;
	}
} a[N];
struct B_tree {
	int c[N],t[N],T;
	void clear() {
		T++;
	}
	inline int lowbit(int x) {
		return x&-x;
	}
	inline void add(int x,int v) {
		while(x<=cnt) {
			if(t[x]==T)c[x]+=v;
			else t[x]=T,c[x]=v;
			x+=lowbit(x);
		}
	}
	inline int query(int x) {
		int res=0;
		while(x) {
			if(t[x]==T)res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
	inline int query(int l,int r) {
		return query(r)-query(l-1);
	}
} bit;
 
bool cmp(node a,node b){
	if(a.y !=b.y)return a.y<b.y;
	if(a.z!=b.z )return a.z<b.z;
	return a.x >b.x;
}
void cdq(int l,int r) {
	if (l>=r) return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp);
	sort(a+mid+1,a+r+1,cmp);
	int L=l,R=l-1;
	for(int i=mid+1; i<=r; i++) {
		while(L<=mid&&a[i].y-a[L].y >k) {
			bit.add(a[L].z ,-1);
			L++;
		}
		while(R<mid&&a[i].y+k>=a[R+1].y ) {
			R++;
			bit.add(a[R].z,1);
		}
		ans+=bit.query(a[i].ll ,a[i].rr  );
	}
	bit.clear();
	//sort(a+l,a+r+1,cmp);
}
signed main() {
	scanf("%lld%lld",&n,&k);
	for(int i=1,x,f,r; i<=n; i++) {
		scanf("%lld%lld%lld",&x,&r,&f);
		///////x r f
		a[i]= {r,f,x,max(0ll,x-r), x +r };
		b[++cnt]=a[i].z;
		b[++cnt]=a[i].ll ;
		b[++cnt]=a[i].rr ;
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=1; i<=n; i++) {
		a[i].ll =lower_bound(b+1,b+cnt+1,a[i].ll )-b;
		a[i].rr =lower_bound(b+1,b+cnt+1,a[i].rr )-b;
		a[i].z  =lower_bound(b+1,b+cnt+1,a[i].z )-b;
	}
	//cout<<cnt<<endl;
	sort(a+1,a+n+1);
	bit.clear() ;
	cdq(1,n);
	printf("%lld",ans);
	return 0;
}

---

## 作者：huhangqi (赞：0)

很明显是一道偏序问题，我们先列出满足条件的台之间的关系。
$$
\min(r_i,r_j)\ge|x_i-x_j|
$$

$$
|f_i-f_j|\le k
$$

这看起来好像是两条式子，但是不能直接使用二维偏序解决，因为其中含有取最小值操作，所以无法直接使用二维偏序处理。

那么就可以尝试考虑三维偏序了。

先转换一下式子，拆掉绝对值。
$$
r_j\le r_i
$$

$$
f_j-k\le f_i\le f_j+k
$$

$$
x_j-r_j\le x_i \le x_j+r_j
$$



我们首先对于第一维，可以先把最小值问题处理了。我们按照半径长度从小到大排序进行处理即可，对应第一条式子。

对于第二维，我们用 CDQ 以后，对频率进行排序即可，对应第二条式子。

对于第三维，使用树状数组区间修改即可。由于需要使用树状数组，这一部分需要提前离散化。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,ans,tmp[300005],cnt;
struct P{
	int x,b,f,l,r;//分别记录位置，半径，频率， 在可传递范围的左右边界 
}a[100005];
bool cmp(P a,P b){
	return a.b<b.b;//先按照半径排序 
}
bool cmp2(P a,P b){
	return a.f<b.f;//按照频率排序 
}
struct BT{
	int c[200005];
	void init(){
		memset(c,0,sizeof(c));
	}
	int lowbit(int x){
		return x&-x;
	}
	void add(int x,int y){
		for(int i=x;i<=n;i+=lowbit(i))c[i]+=y;
	}
	int query(int x){
		int ans=0;
		for(int i=x;i;i-=lowbit(i))ans+=c[i];
		return ans;
	}
	int query(int l,int r){
		return query(r)-query(l-1);
	}
}bit;
void CDQ(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(a+l,a+mid+1,cmp2),sort(a+mid+1,a+r+1,cmp2);
	int L=mid+1,R=mid+1;
	for(int i=l;i<=mid;i++){
		while(R<=r&&a[R].f-a[i].f<=k)bit.add(a[R].x,1),R++;//通过频率关系确定范围 
		while(L<=r&&a[i].f-a[L].f>k)bit.add(a[L].x,-1),L++;
		ans+=bit.query(a[i].l,a[i].r);
	}
	for(int i=L;i<R;i++)bit.add(a[i].x,-1);
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].b>>a[i].f;
		a[i].l=a[i].x-a[i].b;
		a[i].r=a[i].x+a[i].b;
		tmp[++cnt]=a[i].x;
	}
	sort(tmp+1,tmp+cnt+1);//离散化 
	cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(tmp+1,tmp+cnt+1,a[i].x)-tmp;
		a[i].l=lower_bound(tmp+1,tmp+cnt+1,a[i].l)-tmp;
		a[i].r=upper_bound(tmp+1,tmp+cnt+1,a[i].r)-tmp-1;
	}
	sort(a+1,a+n+1,cmp);
	CDQ(1,n);
	cout<<ans;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

首先可以按照半径的大小从大到小进行排序，这样右边能干扰左边就可以保证互相干扰。

考虑 cdq 分治算法，即对于区间 $[l,mid],[mid+1,r]$ 两个区间，求左区间对右区间的贡献数量。

因为要满足频率差为 $k$ 以内，所以可以对两个区间按照频率从小到大排序。

现在需要对于右区间的每一个频率找左区间频率差在 $k$ 以内且坐标在 $[l,r]$ 范围内的数量。

因为右区间的频率单调递增，考虑走双指针，其中 $j$ 表示当前最后一个使得频率差在 $k$ 以内的位置，那么 $i$ 表示当前第一个使得频率差在 $k$ 以内的位置。

将指针内符合要求的电台的一维坐标放入数据结构中，即 $j$ 是增加贡献且 $i$ 是减去不符合条件的贡献，最后在数据结构中查询 $[l,r]$ 范围内的点的数量即可。

时间复杂度为 $O(N \log^2 N)$。

**注意离散化。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll q,x,len;
	ll l,r;
}a[N];
ll n,k,cnt,ans;
ll b[N];
class BIT{
public:
	ll a[N];
	void add(ll x,ll v){
		for(int i=x;i<=cnt;i+=lowbit(i))
		  a[i]+=v;
	}
	ll qurey(ll x){
		ll ans=0;
		for(int i=x;i;i-=lowbit(i))
		  ans+=a[i];
		return ans;
	}
}T;
bool cmp1(const Node &a,const Node &b){
	return a.len>b.len;
}
bool cmp2(const Node &a,const Node &b){
	return a.q<b.q;
}
void cdq(ll l,ll r){
	if(l==r)
	  return ;
	ll mid=(l+r)>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	ll i=l,j=l-1;
	for(int x=mid+1;x<=r;x++){
		while(i<=mid&&a[x].q-a[i].q>k){
			T.add(a[i].x,-1);
			i++;
		}
		while(j<mid&&a[j+1].q-a[x].q<=k){
			T.add(a[j+1].x,1);
			j++;
		}
		ans+=T.qurey(a[x].r)-T.qurey(a[x].l-1);
	}
	for(int x=i;x<=j;x++)
	  T.add(a[x].x,-1);
	sort(a+l,a+r+1,cmp2);
}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();
		a[i].len=read();
		a[i].q=read();
		a[i].l=a[i].x-a[i].len;
		a[i].r=a[i].x+a[i].len;
		b[++cnt]=a[i].x;
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-(b+1);
//	for(int i=1;i<=cnt;i++)
//	  cerr<<b[i]<<' ';
//	cerr<<'\n';
	for(int i=1;i<=n;i++){
		a[i].l=lower_bound(b+1,b+cnt+1,a[i].l)-b;
		a[i].r=upper_bound(b+1,b+cnt+1,a[i].r)-b-1;
		a[i].x=lower_bound(b+1,b+cnt+1,a[i].x)-b;
//		cerr<<a[i].l<<' '<<a[i].r<<'\n';
	}
	sort(a+1,a+n+1,cmp1);
//	for(int i=1;i<=n;i++)
//	  cerr<<a[i].x<<' '<<a[i].len<<' '<<a[i].q<<' '<<a[i].l<<' '<<a[i].r<<'\n';
	cdq(1,n);
	write(ans);
	return 0;
}
```

---

## 作者：_fairytale_ (赞：0)

学到了拆掉 `min` 的小套路！

题目要求我们数满足以下要求的点对数：

$$
\begin{cases}
i>j\\
|f_i-f_j|\leq k\\
|x_i-x_j|\leq\min(r_i,r_j)
\end{cases}
$$

绝对值和 `min` 都不是好维护的东西，我们考虑把它们拆一拆！

我们直接把点按 $r$ 从大到小排序，这样式子就变成：

$$
\begin{cases}
i>j\\
|f_i-f_j|\leq k\\
|x_i-x_j|\leq r_i
\end{cases}
$$

然后最后一行的那个绝对值也很好拆：

$$
\begin{aligned}
x_i-x_j\leq r_i\\
x_j-x_i\leq r_i\\
x_i-r_i\leq x_j\leq r_i+x_i
\end{aligned}
$$


注意到这个 $f$ 和 $k$ 的范围很小，所以我们直接每个 $f$ 开一棵线段树，处理到 $i$ 时暴力查询 $f_i-k$ 到 $f_i+k$ 的线段树即可。

顺便说一下，如果你把 $r$ 按从小到大排序的话，绝对值拆出来是一棵区间修改单点查询的线段树，这个会爆空间，不要问我为啥知道/kel

```cpp
#include<bits/stdc++.h>
#define re register
#define mid ((l+r)>>1)
#define ll long long
#define rep(x,a,b) for(re int (x)=(a);(x)<=(b);++(x))
using namespace std;
#define inf 2000000000
#define maxn 200100
int n,k;
ll ans;
struct node {
	int x,r,f;
} a[maxn];
#define maxf 10100
struct tree {
	int ls,rs,sum;
} t[maxn<<5];
int rt[maxn],tot;
inline void add(int &p,ll l,ll r,int pos) {
	if(!p)p=++tot;
	++t[p].sum;
	if(l==r)return;
	if(mid>=pos)add(t[p].ls,l,mid,pos);
	else add(t[p].rs,mid+1,r,pos);
}
inline int query(int p,ll l,ll r,int L,int R) {
	if((L<=l&&r<=R)||!p)return t[p].sum;
	ll res=0;
	if(mid>=L)res+=query(t[p].ls,l,mid,L,R);
	if(mid<R)res+=query(t[p].rs,mid+1,r,L,R);
	return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	rep(i,1,n) {
		cin>>a[i].x>>a[i].r>>a[i].f;
	}
	stable_sort(a+1,a+n+1,[](const node &x,const node &y) {
		return x.r>y.r;
	});
	rep(i,1,n) {
		rep(j,max(0,a[i].f-k),a[i].f+k) {
			ans+=query(rt[j],0,inf,a[i].x-a[i].r,a[i].x+a[i].r);
		}
		add(rt[a[i].f],0,inf,a[i].x);
	}
	cout<<ans;
	return 0;
}
```

---

