# Boring Segments

## 题目描述

You are given $ n $ segments on a number line, numbered from $ 1 $ to $ n $ . The $ i $ -th segments covers all integer points from $ l_i $ to $ r_i $ and has a value $ w_i $ .

You are asked to select a subset of these segments (possibly, all of them). Once the subset is selected, it's possible to travel between two integer points if there exists a selected segment that covers both of them. A subset is good if it's possible to reach point $ m $ starting from point $ 1 $ in arbitrary number of moves.

The cost of the subset is the difference between the maximum and the minimum values of segments in it. Find the minimum cost of a good subset.

In every test there exists at least one good subset.

## 样例 #1

### 输入

```
5 12
1 5 5
3 4 10
4 10 6
11 12 5
10 12 3```

### 输出

```
3```

## 样例 #2

### 输入

```
1 10
1 10 23```

### 输出

```
0```

# 题解

## 作者：iMya_nlgau (赞：11)

题目让我们最小化所选线段权值的最大值与最小值之差，所以显然可以用双指针做。

双指针的过程中，加入一条线段 $[l,r]$，我们在线段树上将区间 $[l,r-1]$ 加一，删除该线段时就在线段树上将区间 $[l,r-1]$ 减一，判断区间是否被全部覆盖就查询 $[1,m-1]$ 的最小值是否大于零即可。

至于为什么是 $[l,r-1]$，我们可以发现题目要求我们选的线段必须要有重合部分，转化之后就变成将区间 $[1,m-1]$ 覆盖即可，会好做一些。

时间复杂度为 $O(n\log m)$。

#### 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int read(){
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c^'0'),c=getchar();
	return x;
}
const int maxn=3e5+10;
const int maxm=1e6+10;
struct Node{
	int l,r,dat,tag;
}tr[maxm*4];
inline void pushup(int x){
	tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);
}
inline void pushdown(int x){
	if(tr[x].tag){
		tr[x<<1].dat+=tr[x].tag,tr[x<<1].tag+=tr[x].tag;
		tr[x<<1|1].dat+=tr[x].tag,tr[x<<1|1].tag+=tr[x].tag;
		tr[x].tag=0;
	}
}
void build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].dat=tr[x].tag=0;
	if(l==r) return;
	int mid=l+r>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r); 
}
void modify(int x,int l,int r,int v){
	if(l<=tr[x].l&&r>=tr[x].r){
		tr[x].dat+=v,tr[x].tag+=v;
		return;
	}
	pushdown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) modify(x<<1,l,r,v);
	if(r>mid) modify(x<<1|1,l,r,v);
	pushup(x);
}
int n,m;
struct Segment{
	int l,r,w;
	bool operator<(const Segment &x)const{
		return w<x.w;
	}
}s[maxn];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) s[i].l=read(),s[i].r=read()-1,s[i].w=read();
	sort(s+1,s+n+1);
	build(1,1,m-1);
	int ans=0x3f3f3f3f;
	for(int l=1,r=0;l<=n;l++){
		while(!tr[1].dat){
			if(++r>n){
				printf("%d\n",ans);
				return 0;
			}
			modify(1,s[r].l,s[r].r,1);
		}
		ans=min(ans,s[r].w-s[l].w);
		modify(1,s[l].l,s[l].r,-1);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lizhous (赞：4)

## 分析

看到极差首先想到对 $w_i$ 排序。

又发现只要不影响极差取区间是多多益善的。

所以排完序后答案必然是在区间序列中一段连续的区间。

使用尺取法，顺序枚举左端点。每次相当于删了一个区间，动态维护最小的合法右端点，如果出现不合法就向右推。这样只需要取左右端点的差即可。问题转移到判断合法上。

我们把区间覆盖删除看作区间加减 $1$，查询全局有没有空位就是全局最小值是否为 $0$。有脑线段树。

## 代码
只留主要部分

```cpp
scanf("%lld%lld",&n,&m);
for(int i=1;i<=n;i++)
{
	scanf("%lld%lld%lld",&q[i].l,&q[i].r,&q[i].w);
}
sort(q+1,q+n+1,cmp);
int ans=1000000000; 
for(int l=1,r=0;l<=n;l++)
{
	if(l>1)
	{
		add(1,1,m,q[l-1].l,q[l-1].r-1,-1);
	}
	while(get(1,1,m,1,m-1)==0)
	{
		r++;
		if(r>n)
		{
			printf("%lld\n",ans);
			return 0;
		}
		add(1,1,m,q[r].l,q[r].r-1,1);
	}
	ans=min(ans,q[r].w-q[l].w);
}
printf("%lld\n",ans);
```

---

## 作者：_LPF_ (赞：4)

# E

> 给定 $n$ 个区间，每个有价值，求选择一些区间使得 $1\sim n$ 都被覆盖且区间最大价值 - 最小价值的最小值。

长得像个二分答案，但是很难高效判定，想别的方法。

和[这题](https://www.luogu.com.cn/problem/P1712)的思路几乎一样的，对于价值排序后，双指针得到合法区间，利用线段树模拟一下联通情况即可。

具体一点，对于区间按价值排序后，右指针每次移动至 $1\sim n$ 全部覆盖，然后左指针同样移动至临界点。

这样的值显然是最小的，线段树维护一个 区间加 & 区间最小值 即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 3e5 + 10;
const int M = 2e6 + 10;
const int INF = 2e9;

int n, m, dat[M << 1], add[M << 1];
struct Edge{int l, r, w;} a[N];

int read(){
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? -1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

bool cmp(Edge a, Edge b){return a.w < b.w;}

int Min(int a, int b){return a < b ? a : b;}

void Push_Down(int p){
	if(!add[p]) return;
	int l = p << 1, r = p << 1 | 1;
	dat[l] += add[p], add[l] += add[p];
	dat[r] += add[p], add[r] += add[p];
	add[p] = 0;
}

void Modify(int p, int l, int r, int L, int R, int v){
	if(L <= l && r <= R) {dat[p] += v, add[p] += v; return;}
	Push_Down(p);
	int mid = (l + r) >> 1;
	if(L <= mid) Modify(p << 1, l, mid, L, R, v);
	if(R >  mid) Modify(p << 1 | 1, mid + 1, r, L, R, v);
	dat[p] = Min(dat[p << 1], dat[p << 1 | 1]);
}

int main(){
	n = read(), m = read() - 1;
	for(int i = 1; i <= n; i ++)
		a[i].l = read(), a[i].r = read() - 1, a[i].w = read();
	sort(a + 1, a + n + 1, cmp);
	
	int L = 0, R = 0, ans = INF;
	while(true){
		while(R + 1 <= n && dat[1] == 0)
			R ++, Modify(1, 1, m, a[R].l, a[R].r, 1);
		if(dat[1] == 0) break;
		while(L + 1 <= R && dat[1] >  0)
			L ++, Modify(1, 1, m, a[L].l, a[L].r, - 1);
		ans = Min(ans, a[R].w - a[L].w);
	}
	printf("%d\n", ans);
	return 0;
}
```

# 

---

## 作者：Constant (赞：2)

## 题意简述

有一条范围 $[1,m]$ 的数轴，有 $n$ 条线段 ，第 $i$ 条为 $[l_i,r_i]$ ，权值为 $w_i$ ，选取一些线段使得它们可以覆盖整条数轴（包括非整数的点），求权值的极差最小值。

## Solution

我觉得本题可以学习的一个很好的思想是，对于这种极差问题，我们可以先考虑把区间按权值从小到大排序，然后用双指针求最值。

具体地，先考虑加入区间，此时移动右端点，如果当前所取区间还没有完全覆盖数轴，那么我就一直取，直到被完全覆盖，便停止。

这样做的合理性在于要求的是极差，我们按权值排序后，都是尽可能让权值小的先取。

也就是说，我们只会在还没有覆盖数轴这种迫不得已的情况下才会取更大的线段，且排序后每次取的都是当前可以取的最小的权值，这样就保证了极差最小的合法性。

然后考虑能否删去一些区间，也即移动左端点。

如果当前左端点区间删去仍然使得条件满足，那么左端点向右移动一位。

这样做的合法性在于，极差只会受到最大值和最小值的影响，最大值当前已经不变了，只需要使得最小值尽可能大。

其实，这也正是我们排序的关键所在，如果原来的序列权值是乱序的，每次加入，删除区间时，不好考虑对极差的影响，不知道是否应该继续加入或删除，排序正巧妙地规避了这一问题。

还有一个问题，就是如何判断数轴已经全部被覆盖，只需要每次给选的区间打上标记即可，而这个操作完全可以用线段树来实现，只需要判断全局最小值是否为 $0$ 。

时间复杂度 $O(nlogm)$ 。





---

## 作者：henrytb (赞：2)

先将这些线段按照 $w$ 从大到小排个序。

对于这种最小化 $\max-\min$ 的套路：枚举最小值，找到合法且最小的最大值。

那么我们可以开一个线段树，维护覆盖每个点的线段中最小的 $w$ 的全局 $\max$。

枚举到一个 $\min$ 时，我们把这个线段覆盖成当前的 $w$。这时候线段树维护的全局 $\max$ 就是当前最小可能的 $\max$。

code：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n,m,ans=0x3f3f3f3f;
struct node{
    int l,r,w;
}a[300005];
struct Segment{
    int l,r,cov,mx;
}t[4000005];
bool cmp(node a,node b) {
    return a.w>b.w;
}
void pushdown(int p) {
    if(t[p].cov) {
        t[p<<1].cov=t[p].cov;
        t[p<<1|1].cov=t[p].cov;
        t[p<<1].mx=t[p].cov;
        t[p<<1|1].mx=t[p].cov;
        t[p].cov=0;
    }
}
void pushup(int p) {t[p].mx=max(t[p<<1].mx,t[p<<1|1].mx);}
void build(int p,int l,int r) {
    t[p].l=l;t[p].r=r;
    if(l==r) {t[p].mx=0x3f3f3f3f;return ;}
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
}
void modify(int p,int l,int r,int v) {
    if(l<=t[p].l&&t[p].r<=r) {
        t[p].cov=v;
        t[p].mx=v;
        return;
    } 
    pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(l<=mid) modify(p<<1,l,r,v);
    if(mid<r) modify(p<<1|1,l,r,v);
    pushup(p);
}
int query(int p,int l,int r) {
    if(l<=t[p].l&&t[p].r<=r) return t[p].mx;
    pushdown(p);
    int ans=0;
    int mid=(t[p].l+t[p].r)>>1;
    if(l<=mid) ans=max(ans,query(p<<1,l,r));
    if(mid<r) ans=max(ans,query(p<<1|1,l,r));
    return ans;
}
int main() {
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].w);
    sort(a+1,a+n+1,cmp);
    build(1,1,m);
    rep(i,1,n) {
        modify(1,a[i].l,a[i].r-1,a[i].w);
        ans=min(ans,query(1,1,m-1)-a[i].w);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：0xFF (赞：1)

#### 题目大意


------------
在一条 $[1,m]$ 的数轴上有 $n$ 条线段，第 $i$ 条线段覆盖了从 $l_i$ 到 $r_i$ 范围内的数轴，每条线段有一权值 $w_i$，从中选出任意条**首尾相接**的覆盖整个数轴的线段，最小化线段的极差。

#### 思路分析


------------
对于选出的线段的权值，由于题目要求的是极差，所以我们只关心这些线段中权值最大的和权值最小的。

在数轴上开一棵线段树。

考虑按照权值对这 $n$ 条线段排序后双指针维护。

需要注意的是，由于选出的线段必须是收尾相接的，两线段能够并成一个区间必须有至少一个交点，只需每次修改线段树上 $[l_i+1,r_i]$ 这段区间，最后查询 $[2,m]$ 是否满足条件即可。

要判断已经选出的线段是否覆盖整个数轴就需要记录这段区间的最小值，如果一段区间的最小值大于 $0$ 即表示整段区间都被覆盖完全，此时更新答案，即右指针对应位置的权值减去左指针对应位置的权值。

时间复杂度 $\Theta(n \log m)$。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N = 3e5 + 10;
const int M = 1e6 +10; 
const int INF = 1e9 + 10;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
struct Tree{
	int l,r,sum,mn,add;
}tree[M<<2];
void push_up(int p){
	tree[p].mn = min(tree[p<<1].mn , tree[p<<1|1].mn);
}
void build(int p,int l,int r){
	tree[p].l = l , tree[p].r = r;
	if(l == r){
		tree[p].mn = tree[p].sum = 0;
		return;
	}
	int mid = l + r >> 1;
	build(p<<1,l,mid); build(p<<1|1,mid+1,r);
	push_up(p);
} 
void Add(int p,int k){
	tree[p].add += k , tree[p].mn += k;
}
void push_down(int p){
	if(tree[p].add != 0){
		Add(p<<1,tree[p].add);
		Add(p<<1|1,tree[p].add);
		tree[p].add = 0;
	}
}
void modify(int p,int l,int r,int k){
	if(l <= tree[p].l && tree[p].r <= r){
		tree[p].add += k , tree[p].mn += k;
		return;
	}
	push_down(p);
	int mid = tree[p].l + tree[p].r >> 1;
	if(l <= mid) modify(p<<1,l,r,k);
	if(r >  mid) modify(p<<1|1,l,r,k);
	push_up(p);
}
int query(int p,int l,int r){
	if(l <= tree[p].l && tree[p].r <= r){
		return tree[p].mn;
	}
	push_down(p);
	int res = INF;
	int mid = tree[p].l + tree[p].r >> 1;
	if(l <= mid) res = min(res,query(p<<1,l,r));
	if(r >  mid) res = min(res,query(p<<1|1,l,r));
	return res; 
}
struct Node{
	int l,r,w;
}a[N];
bool cmp(Node a,Node b){
	return a.w < b.w;
}
int pos = 1;
int ans = INF;
int main(){
	int n = read() , m = read();
	build(1,1,m);
	for(int i=1;i<=n;i++){
		a[i].l = read() , a[i].r = read() , a[i].w = read(); 
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		modify(1,a[i].l+1,a[i].r,1);
		while(query(1,2,m) > 0){
			modify(1,a[pos].l+1,a[pos].r,-1);
//			cout<<pos<<" "<<i<<" "<<a[pos].w<<" "<<a[i].w<<endl;
			ans = min(ans,a[i].w - a[pos].w);
			pos++;
//			cout<<ans<<endl;
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
5 12
1 5 5
3 4 10
4 10 6
11 12 5
10 12 3
*/
```


---

## 作者：Akoasm_X (赞：1)

### 题目大意
给定 $n$ 个带权区间，最小化能覆盖 $m$ 的最大区间权值和最小权值的差值

### 解题思路
把所有区间按权值从大到小排序，依次加入每个区间，判断是否覆盖全集，统计目前**起关键作用**的最小值。

怎么理解这个关键作用呢，例如一个数字只被一个区间覆盖，那这个区间是一定要选中的，那它就起关键作用。

还有一个问题，如果一个数能被两段区间覆盖，那我们无疑选择权值较大的那个，才能得到更小的权值差。

区间覆盖问题很自然地想到了线段树等操作，维护一个最小值，然后每次加入一段区间就覆盖下去，最后做差。

然后我就发现我连样例都没过，结束之后五分钟过了（）。

这里要对 $[\,1\,,\,m-1\,]$ 建树，每个叶节点表示从 $i \to i+1$ 的代价，然后再执行线段树操作即可

代码如下
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define lson (x<<1),l,mid
#define rson (x<<1|1),mid+1,r
using namespace std;
const int maxn = 1e6+20;
int n,m,Ans,L,R;
struct Node
{
	int mark,va;
}Tree[maxn<<2];
struct node
{
	int l,r,va;
	bool operator <(const node A)const{
		return va==A.va ? l < A.l : va < A.va ;
	}
}in[maxn];

inline int read() 
{
    int x = 0 , f = 1 ; char c = getchar() ;
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1 ; c = getchar() ; } 
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; c = getchar() ; } 
    return x * f ;
}

void build(int x,int l,int r)
{
	if(l==r)
	{
		Tree[x].va = -1e9;
		return ;
	}
	build(lson);build(rson);
	Tree[x].va = -1e9;
}

void Cover(int x,int k)
{
	Tree[x].va = k;
	Tree[x].mark = k;
}

void pushdown(int x)
{
	if(Tree[x].mark)
	{
		Cover((x<<1),Tree[x].mark);
		Cover((x<<1|1),Tree[x].mark);
		Tree[x].mark = 0;
	}
}

void update(int x,int l,int r,int k)
{
	if(L<=l&&r<=R) {Cover(x,k);return ;}
	pushdown(x);
	if(L<=mid) update(lson,k);
	if(mid<R) update(rson,k);
	Tree[x].va = min(Tree[x<<1].va,Tree[x<<1|1].va);
}

int main()
{//个人习惯，n,m与题目中不对应吗，是相反的 
	m = read();n = read()-1;
	build(1,1,n);//一定要有的一步，把最小值设成0 
	Ans = 2e9;
	for(int i=1;i<=m;i++) in[i].l = read(),in[i].r = read()-1,in[i].va = read();
	sort(in+1,in+1+m);
	for(int i=1;i<=m;i++)
	{
		L = in[i].l ;R = in[i].r;
		update(1,1,n,in[i].va);//先覆盖，再查询全局最小值 
		Ans = min(Ans,in[i].va-Tree[1].va);
	}
	printf("%d\n",Ans);
	return 0;
}
```



---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1555E)

## 题目分析

线段树处理区间覆盖。

题目只要求区间 $w$ 极差最小，使用区间数量不限。

若知道了要用上的区间的 $w_{max},w_{min}$，则显然 $w_i \in [w_{min},w_{max}]$ 的所有区间一股脑全用上就行了，对答案无影响。

这就得出了一个 $O(n \log m)$ 的算法：

直接对区间按 $w$ 升序排序。

定义两个指针 $l,r$，分别指着 $w_{min}$ 和 $w_{max}$。

若数轴未被完全覆盖，则 $r$ 右移。

若数轴已被完全覆盖，记录极差，且 $l$ 右移。

$l,r$ 初始化均为 $1$。

当 $r$ 右移，即在数轴上增添覆盖区间，在线段树对应位置加 $1$。

当 $l$ 右移，即在数轴上删去区间，在线段树对应位置减 $1$。

本题线段树维护区间最小值。当节点权值为 $0$，代表其所维护区间未被完全覆盖。

**注意：题目要求区间首尾需有重叠部分**，输入时将区间右端点统一减 $1$ 处理即可。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 1000010
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int inf = 1e9;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, m, ans = inf;
struct Tree {int l, r, w, f;} T[N << 2];
struct Node {int l, r, w;} a[N];

inline bool cmp(const Node &a, const Node &b) {return a.w < b.w;}

inline void Pushup(int k) {T[k].w = min(T[ls].w, T[rs].w);}

inline void Pushdown(int k)
{
	if (!T[k].f) return;
	T[ls].f += T[k].f; T[rs].f += T[k].f;
	T[ls].w += T[k].f; T[rs].w += T[k].f;
	T[k].f = 0;
}

inline void Build(int k, int l, int r)
{
	T[k].l = l; T[k].r = r;
	if (l == r) return;
	int mid = l + r >> 1;
	Build(ls, l, mid);
	Build(rs, mid + 1, r);
}

inline void Update(int k, int x, int y, int v)
{
	if (x <= T[k].l && T[k].r <= y)
	{
		T[k].f += v;
		T[k].w += v;
		return;
	}
	Pushdown(k);
	int mid = T[k].l + T[k].r >> 1;
	if (x <= mid) Update(ls, x, y, v);
	if (mid < y) Update(rs, x, y, v);
	Pushup(k);
}

int main()
{
	read(n); read(m); m--;
	for (rei i = 1; i <= n; i++) read(a[i].l), read(a[i].r), read(a[i].w), a[i].r--;
	sort(a + 1, a + 1 + n, cmp); Build(1, 1, m);
	int p = 0; 
	for (rei i = 1; i <= n; i++)
	{
		p = max(p, i);
		for (; p <= n && !T[1].w; p++) Update(1, a[p].l, a[p].r, 1);
		if (T[1].w) ans = min(a[p - 1].w - a[i].w, ans);
		Update(1, a[i].l, a[i].r, -1);
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：徐天乾 (赞：0)

## 题目大意
有 $n$ 个线段，每条线段有三个值 $l_{i},r_{i},w_{i}$，表示
覆盖 $[l_{i},r_{i}]$ 的权值为 $w_{i}$。要你选择一些线段，使其覆盖 $[1,m]$，并且要**权值的最大值减权值的最小值**最小，问你最小值是多少。

## 前置芝士

1. 线段树；
1. 尺取。

如果不会的话先把 [CF253B](https://www.luogu.com.cn/problem/CF253B)（尺取）和 [P3372](https://www.luogu.com.cn/problem/P3372)（线段树）打了。

## 思路
首先，在会前置芝士的情况下很容易就想到先将权值 $w_{i}$ 从小到大进行排序，然后用两根指针 $t,w$  进行维护，每次判断 $[1,n]$ 中的最小值是否大于 $0$（大于 $0$ 意味着全部被覆盖），之后取一个最小值即可。

注意：线段树的数组至少是 $4$ 倍（PS：本来想先试一试会不会 MLE，没想到一遍过，连离散化都不需要）。

最后，贴上我~~丑陋的~~程序：
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,n,m,t,w,MIN,add[4000400],Min[4000400];  
struct node{int l,r,w;}a[300300];
bool cmp(node x,node y){return x.w<y.w;}
void pushdown(int num,int l,int r){
	if (add[num]==0) return ;
	add[num<<1]+=add[num];  add[num<<1|1]+=add[num];
	Min[num<<1]+=add[num];  Min[num<<1|1]+=add[num];
	add[num]=0;
}
void update(int L,int R,int c,int l,int r,int num){
	if (L<=l&&r<=R) {Min[num]+=c;add[num]+=c;return ;}
	int m=(l+r)>>1;
	pushdown(num,m-l+1,r-m);
	if (L<=m) update(L,R,c,l,m,num<<1);
	if (R>m) update(L,R,c,m+1,r,num<<1|1);    
	Min[num]=min(Min[num<<1],Min[num<<1|1]);
}
int main(){
	scanf("%d %d",&n,&m);m--;  //注意：根据题目“首尾相接”的定义，此处需减1，后面也是同理，你可以思考一下原因（不然样例也过不了，会输出1）
	for (i=1;i<=n;i++) scanf("%d %d %d",&a[i].l,&a[i].r,&a[i].w),a[i].r--;
	sort(a+1,a+1+n,cmp);  /*进行从小到大的排序*/  MIN=(2e9); //先取一个最大值
	for (t=1,w=1;w<=n;w++){  //每一轮w指针向后移
		update(a[w].l,a[w].r,1,1,m,1);  //区间内所有数+1
		if (!Min[1]) continue;       //Min[1]代表[1,m]的最小值，如果为0则是没有覆盖成功，直接退出
		while (t<=w&&Min[1]>0) update(a[t].l,a[t].r,-1,1,m,1),t++; //然后t指针后移，知道不成立
		MIN=min(MIN,a[w].w-a[t-1].w);  //因为t指针此时指向不成立的位子，而t-1的位子此时是成立的，所以此处t-1
	}
	printf("%d\n",MIN); //输出（完结撒花）
	return 0;
} 
```

## 结语
如果 AC 了这题，建议再去做 [P1712](https://www.luogu.com.cn/problem/P1712)，~~这可是双倍经验啊~~，此题与这题同样思路，但是因为数据大还需要离散化，可以帮你去练练手。


好了，谢谢大家观看。


---

## 作者：BreakPlus (赞：0)

[$\Large \text{CF1555E Boring Segment}$](https://www.luogu.com.cn/problem/CF1555E)

### $\text{Discription}$

在 $n$ 条线段中选出一些线段覆盖 $1 \sim m$ 整条线段，使得线段的权值的极差最小。

### $\text{Solution}$

看到“最大值和最小值的差尽量小”，二分已不足以求解（因为不确定最大值和最小值）。先考虑贪心，当选择线段的最大权值和最小权值确定时，权值在它们之间的线段选择了，答案肯定不会更劣。我们把线段按权值排序，选择的就一定是一堆连续的线段了。

连续的一段，有条件限制，想到了啥？Two-pointers。我们枚举左端点，然后把上次的右端点继续向右移动即可。但是有一个问题，我们该怎么判断是否全部覆盖呢？可以用线段树维护区间最小值，每新加、删除一条线段就区间修改，当 $1 \sim m$ 之间的线段被覆盖次数的最小值 $\ge 1$ 的时候说明全部被覆盖了。

### $\text{Code}$
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=4000010;
#define int long long
struct Node{
	int l,r,w;
}node[maxn];
struct Segment{
	int ls,rs,mx,tag;
}seg[maxn]; 
int n,m;
inline void build(int l,int r,int pos){
	seg[pos].ls=l,seg[pos].rs=r;
	if(l==r) return;
	int mid=l+r>>1;
	if(l<=mid) build(l,mid,pos<<1);
	if(mid<r) build(mid+1,r,pos<<1|1);
}
int minn(int a,int b){
	return a<b?a:b;
}
inline void pushdown(int pos){
	if(seg[pos].tag){
		seg[pos<<1].tag+=seg[pos].tag;
		seg[pos<<1].mx+=seg[pos].tag;
		seg[pos<<1|1].tag+=seg[pos].tag;
		seg[pos<<1|1].mx+=seg[pos].tag;
		seg[pos].tag=0;
	}
}
inline void pushup(int pos){
	seg[pos].mx=minn(seg[pos<<1].mx,seg[pos<<1|1].mx);
}
inline void change(int l,int r,int cost,int pos){
	if(l<=seg[pos].ls&&seg[pos].rs<=r){
		seg[pos].tag+=cost;
		seg[pos].mx+=cost;
		return;
	}
	pushdown(pos);
	int mid=seg[pos].ls+seg[pos].rs>>1;
	if(l<=mid) change(l,r,cost,pos<<1);
	if(mid<r) change(l,r,cost,pos<<1|1);
	pushup(pos);
}
inline bool cmp(Node A,Node B){
	return A.w<B.w;
}
int ans=2e9;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&node[i].l,&node[i].r,&node[i].w);
	build(1,m-1,1);
	sort(node+1,node+n+1,cmp);
	int hd=1,tl=0;
	while(hd<=n){
		bool flag=false;
		if(seg[1].mx>0){
			flag=true;
		}
		else {
			while(tl<n){
				tl++; change(node[tl].l,node[tl].r-1,1,1);
				if(seg[1].mx>0){
					flag=true;
					break;
				}
			}
		}
		if(flag){
			//printf("check: %lld %lld\n",hd,tl);
			if(ans>(node[tl].w-node[hd].w)) ans=(node[tl].w-node[hd].w);
		}
		change(node[hd].l,node[hd].r-1,-1,1); hd++;
	} 
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_Clown_ (赞：0)

# E.Boring Segments
$\mathtt{Difficulty}$=$\mathtt{2100}$

题意是最小化最大值和最小值的差，不难想到 $\texttt{two-pointer}$。

枚举左端点，然后把上次的右端点继续向右移动即可。

我们不妨使用线段树来维护这个区间。

插入、删除就是在线段树 $[l,r-1]$ 上加减，维护区间。

时间复杂度 $\mathcal{O(n\log m)}$，想必是正解吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Struct
{
    int Left,Right,Value;
    inline bool operator <(const Struct &Compare)const
    {
        return Value<Compare.Value;
    }
};
struct Node
{
    int Tmp,Tag;
};
int N,M;
Struct S[1000010];
Node C[4000040];
inline void Pd(int Rt)
{
    if(C[Rt].Tag)
    {
        C[Rt*2].Tag+=C[Rt].Tag;
        C[Rt*2+1].Tag+=C[Rt].Tag;
        C[Rt*2].Tmp+=C[Rt].Tag;
        C[Rt*2+1].Tmp+=C[Rt].Tag;
    }
    C[Rt].Tag=0;
}
inline void Pu(int Rt)
{
    C[Rt].Tmp=min(C[Rt*2].Tmp,C[Rt*2+1].Tmp);
}
inline void Add(int Rt,int L,int R,int LL,int RR,int VV)
{
    if(L>=LL&&R<=RR){C[Rt].Tag+=VV,C[Rt].Tmp+=VV;return;}
    Pd(Rt);
    if((L+R>>1)>=LL)Add(Rt*2,L,(L+R>>1),LL,RR,VV);
    if((L+R>>1)<RR)Add(Rt*2+1,(L+R>>1)+1,R,LL,RR,VV);
    Pu(Rt);
}
int main(void)
{
    register int i,Cnt=0,Ans=INT_MAX,T=0;
    cin>>N>>M,M--;
    for(i=1;i<=N;i++)cin>>S[i].Left>>S[i].Right>>S[i].Value,S[i].Right--;
    sort(S+1,S+N+1);
    while(!C[1].Tmp)Cnt++,Add(1,1,M,S[Cnt].Left,S[Cnt].Right,1);
    Add(1,1,M,S[Cnt].Left,S[Cnt].Right,-1);
    for(i=Cnt;i<=N;i++)
    {
        Add(1,1,M,S[i].Left,S[i].Right,1);
        while(C[1].Tmp)T++,Add(1,1,M,S[T].Left,S[T].Right,-1);
        Add(1,1,M,S[T].Left,S[T].Right,1);
        Ans=min(Ans,S[i].Value-S[T].Value),T--;
    }
    cout<<Ans<<endl;
    return 0;
}
```

---

## 作者：caoji2001 (赞：0)

## 大致思路
设 $a_i$ ($1 \leq i \leq m - 1$) 表示为 $i$ 与 $i + 1$ 提供通路的 `segments` 的数量，即同时覆盖了 $i$ 与 $i + 1$ 的 `segments` 的数量。那么数字 $1$ 与 $m$ 之间存在通路，当前仅当对于 $\forall{a_i}$ ($1 \leq i \leq m - 1$)，均有 $a_i \geq 1$，即 $max\{a_i | 1 \leq i \leq m - 1\} \geq 1$。因此对于选择区间的操作，假设选择的区间范围是 $[l_i, r_i]$, 可使 $a_i := a_i + 1$ $(l_i \leq i \leq r_i)$。同理，对于取消选择区间的操作，假设选择的区间范围是 $[l_i, r_i]$, 可使 $a_i := a_i - 1$ $(l_i \leq i \leq r_i)$。

对于上述区间查询、区间修改的需求，我们可使用线段树维护区间最小值，时间复杂度为 $O(\log m)$。

此外，由于最终的花费为选择的 `segments` 中代价最大与代价最少的差，因此假设当前选择的线段中代价最大的为 $w_{max}$，代价最小的为 $w_{min}$，则我们一定可以选取所有代价位于 $[w_{min}, w_{max}]$ 之间的 `segments`，因为选取这些线段对最终答案不会造成影响，不会使得结果变得更差。因此我们可以贪心的考虑问题，将所有 `segments` 按照它们的代价进行排序，之后使用双指针维护选择的 `segments` 的区间，对于每次的查询及修改操作，通过上述的线段树实现即可。

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;
using i64 = long long;

// 线段树（维护区间最小值）
struct segtree {
    struct node {
        int mn = 0;
        int add = 0;

        void apply(int v) {
            mn += v;
            add += v;
        }
    };

    int n;
    vector<node> tree;

    node unite(const node &a, const node &b) const {
        node res;
        res.mn = min(a.mn, b.mn);

        return res;
    }

    void pull(int p) {
        tree[p] = unite(tree[p * 2], tree[p * 2 + 1]);
    }

    void push(int s, int t, int p) {
        if (tree[p].add) {
            int mid = (s + t) / 2;

            tree[p * 2].apply(tree[p].add);
            tree[p * 2 + 1].apply(tree[p].add);

            tree[p].add = 0;
        }
    }

    int get(int l, int r) {
        return get(l, r, 1, n, 1).mn;
    }

    node get(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r) {
            return tree[p];
        }

        push(s, t, p);

        node res;

        int mid = (s + t) / 2;
        if (r <= mid) {
            res = get(l, r, s, mid, p * 2);
        } else if (l > mid) {
            res = get(l, r, mid + 1, t, p * 2 + 1);
        } else {
            res = unite(get(l, r, s, mid, p * 2), get(l, r, mid + 1, t, p * 2 + 1));
        }

        return res;
    }

    void modify(int l, int r, int c) {
        modify(l, r, c, 1, n, 1);
    }

    void modify(int l, int r, int c, int s, int t, int p) {
        if (l <= s && t <= r) {
            tree[p].apply(c);
            return;
        }

        push(s, t, p);

        int mid = (s + t) / 2;
        if (l <= mid)
            modify(l, r, c, s, mid, p * 2);
        if (mid < r)
            modify(l, r, c, mid + 1, t, p * 2 + 1);

        pull(p);
    }

    void build(int s, int t, int p, const vector<int> &v) {
        if (s == t) {
            tree[p].mn = v[s];
            return;
        }

        int mid = (s + t) / 2;

        build(s, mid, p * 2, v);
        build(mid + 1, t, p * 2 + 1, v);

        pull(p);
    }

    segtree(int _n): n(_n) {
        tree.resize(n * 4 + 5);
    }

    segtree(const vector<int> &v) {
        n = int(v.size()) - 1;
        tree.resize(n * 4 + 5);

        build(1, n, 1, v);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> v(n + 1);
    for (int i = 1; i <= n; i++) {
        int l, r, w;
        cin >> l >> r >> w;

        v[i] = {l, r - 1, w};
    }
    sort(v.begin() + 1, v.begin() + 1 + n, [&](auto x, auto y) {
        return get<2>(x) < get<2>(y);
    });

    segtree seg(m - 1);

    int l = 1, r = 0, res = INT_MAX;
    while (r < n) {
        while (r < n && !seg.get(1, m - 1)) {
            r++;
            seg.modify(get<0>(v[r]), get<1>(v[r]), +1);
        }

        if (seg.get(1, m - 1) > 0) {
            while (seg.get(1, m - 1) > 0) {
                seg.modify(get<0>(v[l]), get<1>(v[l]), -1);
                l++;
            }

            res = min(res, get<2>(v[r]) - get<2>(v[l - 1]));
        }
    }

    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // int t;
    // cin >> t;
    // while (t--)
        solve();

    return 0;
}
```


---

