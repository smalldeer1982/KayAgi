# Developing Game

## 题目描述

Pavel is going to make a game of his dream. However, he knows that he can't make it on his own so he founded a development company and hired $ n $ workers of staff. Now he wants to pick $ n $ workers from the staff who will be directly responsible for developing a game.

Each worker has a certain skill level $ v_{i} $ . Besides, each worker doesn't want to work with the one whose skill is very different. In other words, the $ i $ -th worker won't work with those whose skill is less than $ l_{i} $ , and with those whose skill is more than $ r_{i} $ .

Pavel understands that the game of his dream isn't too hard to develop, so the worker with any skill will be equally useful. That's why he wants to pick a team of the maximum possible size. Help him pick such team.

## 样例 #1

### 输入

```
4
2 8 9
1 4 7
3 6 8
5 8 10
```

### 输出

```
3
1 3 4
```

## 样例 #2

### 输入

```
6
3 5 16
1 6 11
4 8 12
7 9 16
2 10 14
8 13 15
```

### 输出

```
4
1 2 3 5
```

# 题解

## 作者：WaterSun (赞：11)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18666404)

这是一个不需要扫描线的做法/cy

# 思路

注意到选择出来的人的 $[l_i,r_i]$ 必须有交，并且每个人的 $v_i$ 都得在交里面。

考虑枚举交的左端点 $L$，维护每一个右端点 $R$ 的答案。容易发现当一个人 $i$ 满足 $l_i \leq L \leq v_i \leq R \leq r_i$ 时会对一个右端点 $R$ 产生贡献。

于是当 $l_i \leq L \leq v_i$ 时，对于所有在 $[v_i,r_i]$ 区间的 $R$ 都可以被第 $i$ 个人贡献。

一个经典的处理这个问题的方法是，在 $L$ 移动到 $l_i$ 时将第 $i$ 个人的贡献加入，在 $v_i + 1$ 时将第 $i$ 个人的贡献减去。容易使用线段树维护，区间加法，全局最值。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second

using namespace std;

typedef pair<int,int> pii;
const int N = 3e5 + 10;
int n,ans,ansl,ansr;
vector<pii> Q[N];

struct sec{
    int l,r,v;
}arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)
    #define mid (tr[u].l + tr[u].r >> 1)

    struct node{
        int l,r,tag;
        pii Max;
    }tr[N << 2];

    inline void calc(int u,int k){
        tr[u].Max.fst += k; tr[u].tag += k;
    }

    inline void pushup(int u){
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(ls(u),tr[u].tag); calc(rs(u),tr[u].tag);
            tr[u].tag = 0;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return (tr[u].Max.snd = l),void();
        build(ls(u),l,mid); build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r) return calc(u,k);
        pushdown(u);
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    #undef ls
    #undef rs
    #undef mid
}T;

int main(){
    n = read();
    for (re int i = 1,l,r,v;i <= n;i++){
        l = read(),v = read(),r = read();
        arr[i] = {l,r,v};
        Q[l].push_back({1,i});
        Q[v + 1].push_back({-1,i});
    }
    T.build(1,1,3e5);
    for (re int i = 1;i <= 3e5;i++){
        for (pii p:Q[i]){
            sec tmp = arr[p.snd];
            T.modify(1,tmp.v,tmp.r,p.fst);
        }
        pii res = T.tr[1].Max;
        if (res.fst > ans){
            ans = res.fst;
            ansl = i,ansr = res.snd;
        }
    }
    printf("%d\n",ans);
    for (re int i = 1;i <= n;i++){
        if (arr[i].l <= ansl && ansr <= arr[i].r && ansl <= arr[i].v && arr[i].v <= ansr) printf("%d ",i);
    }
    return 0;
}
```

---

## 作者：jun头吉吉 (赞：10)

# CF377D 【Developing Game】
- [$\color{skyblue}{\texttt{My\ Blog}}$](https://chen-jia-liang.gitee.io/blog/2020/10/04/%E9%A2%98%E8%A7%A3-CF377D-%E3%80%90Developing-Game%E3%80%91/)
## 题意
有$n$个工人，第$i$个工人的能力是$v_i$,他只与能力在$[l_i,r_i]$之间的人在一起工作，问最多能选出多少人一起工作并输出方案。
## 题解
第一眼看到这题应该是想到最大团吧。但$ 1\le n\le10^{5} $连连边都要$\small{\color{blue}{\texttt{Time\ limit\ exceeded}}}$，用[随机化](https://www.luogu.com.cn/paste/760hs0nj)~~CF还敢用随机算法~~会$\small{\color{blue}{\texttt{Wrong answer on test 11}}}$。但随机化能给我们的正解一些启发。

我们随机化算法跑的时候记录了四个变量，及$maxl,minv,maxv,minr$，分别表示最大的$l$，最小的$v$，最大的$v$，最小的$r$。在新加入一个点时，只有满足新的$maxl\le minv,maxv\le minr$才可以加入。格式化地，如果我们选了一个集合$\mathcal{S}$合法，则必有：
$$\max_{i\in \mathcal{S}}l_i\le \min_{i\in \mathcal{S}}v_i\le\max_{i\in \mathcal{S}}v_i\le\min_{i\in \mathcal{S}}r_i$$

把两部分拆开来看。

$\max\limits_{i\in \mathcal{S}} l_i\leq \min\limits_{i\in \mathcal{S}} v_i$，可以看做是所有$[l_i,v_i]$的线段有共同覆盖的地方。对$\max\limits_{i\in \mathcal{S}} v_i\leq \min\limits_{i\in \mathcal{S}} r_i$也是同理。因此，我们把一个工人$l_i,v_i,r_i$，看作是一个矩形，左下角为$(l_i,v_i)$右上角为$(v_i,r_i)$，那么上式就可以看做是这$|\mathcal{S}|$个矩形有公共部分。

于是剩下的操作就很简单了。类似于[P1502窗口的星星](https://www.luogu.com.cn/problem/P1502)。对于一个矩形，我们可以通过差分在$x=l_i$时将$[v_i,r_i]$的次数加一，在$x=v_i+1$时将$[v_i,r_i]$覆盖次数减一，开一个线段树维护最大值即可。

至于输出方案，我们线段树能找到一个点$(x,y)$使其覆盖次数最大，那么把所有$l_i\le x \le v_i \le y\le r_i$的工人输出就行了

### 总结
[$\color{#8e44ad}{\texttt{Rainbow\_sjy}\heartsuit\texttt{OI}}$](https://www.luogu.com.cn/user/151935)说这是一个![扫描线神仙题](https://cdn.luogu.com.cn/upload/image_hosting/5pc6b6ey.png)，但事实上本题的难点并不在扫描线，而在于毒瘤转化。
## 代码
~~想到了这一步代码还是很好写的吧~~
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace out{
	char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
	inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
	inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
	template <typename T>void write(T x) {
		static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
		while (len>=0)putc(buf[len]),--len;
	}
}
using namespace std;
const int N=5e5+10;
struct node{
    pair<long long,int>ans;
    long long tag;
    int l,r;
}T[N*8];
#define lson (x<<1)
#define rson (x<<1|1)
void pushup(int x){T[x].ans=max(T[lson].ans,T[rson].ans);}
void pushdown(int x){
    if(T[x].tag){
        T[lson].tag+=T[x].tag;T[lson].ans.first+=T[x].tag;
        T[rson].tag+=T[x].tag;T[rson].ans.first+=T[x].tag;
        T[x].tag=0;
    }
}
void build(int x,int l,int r){
    T[x].l=l,T[x].r=r;
    if(l==r){T[x].ans={0,l};return;}
    int mid=l+r>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    pushup(x);
}
pair<long long,int>query(int x,int l,int r){
    if(l<=T[x].l&&T[x].r<=r)return T[x].ans;
    pushdown(x);
	int mid=T[x].l+T[x].r>>1;
    if(r<=mid)return query(lson,l,r);
    if(mid<l)return query(rson,l,r);
    return max(query(lson,l,r),query(rson,l,r));
}
void upd(int x,int l,int r,int val){
    if(l<=T[x].l&&T[x].r<=r){T[x].ans.first+=val;T[x].tag+=val;return;}
    pushdown(x);
    int mid=T[x].l+T[x].r>>1;
    if(l<=mid)upd(lson,l,r,val);
    if(mid<r)upd(rson,l,r,val);
    pushup(x);
}
int n;
struct Worker{int l,r,v;Worker(int l,int v,int r):l(l),v(v),r(r){}};
vector<Worker>a;
vector<vector<pair<pair<int,int>,int>>>opt;
#define pb push_back
signed main(){
	in::read(n);opt=vector<vector<pair<pair<int,int>,int>>>(3e5+4);
	for(int i=1,l,v,r;i<=n;i++)
		in::read(l,v,r),
		a.pb(Worker(l,v,r)),
		opt[l].pb({{v,r},1}),opt[v+1].pb({{v,r},-1});
	build(1,0,3e5);
	int ans=0,x,y;
	for(int i=0;i<=3e5+3;i++){
		for(auto OPT:opt[i])upd(1,OPT.first.first,OPT.first.second,OPT.second);
		if(T[1].ans.first>ans)
			ans=T[1].ans.first,
			x=i,y=T[1].ans.second;
	}
	printf("%d\n",ans);
	int tmp=0;
	for(auto worker:a)
		if(++tmp&&worker.l<=x&&x<=worker.v&&worker.v<=y&&y<=worker.r)
			printf("%d ",tmp);
}
```

---

## 作者：EityDawn (赞：5)

## 思路
设我们选出来的人构成了集合 $S$，那么对任意的 $i\in S$，满足 $\max\{l_i\}\le v_i \le \min\{r_i\}$。

不妨抽象出线段 $[l_i,v_i]$，则集合 $S$ 中的线段有交集，而对于线段 $[v_i,r_i]$ 也必须有交集，相当于在二维平面内左下角为 $(l_i,v_i)$，右上角为 $(v_i,r_i)$ 的矩形中，选出尽可能多的矩形，使它们两两都相交。之后在选出的这些矩形相交的区域内，随便选择一个点 $(x,y)$，对于合法的 $i$ 满足 $l_i\le x \le v_i $ 且 $v_i\le y \le r_i$。

实现上可以扫描线 + 线段树来完成。

枚举纵坐标 $y$，当 $y=v_i$ 时，我们给线段 $[l_i,v_i]$ 加上 $1$ 的贡献，而在 $y\in[v_i,r_i]$ 时，线段 $[l_i,v_i]$ 一直都有贡献，所以在 $y=r_i+1$ 时，记得消去线段 $[l_i,v_i]$ 的贡献。每次修改完之后，询问最大值，更新我们要求的 $(x,y)$。

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
const int N=1e5+10,M=3e5+10,V=3e5;
struct SGT{
    pair<ll,int>ma;
    int tag;
}t[M<<2];
#define ma(x) t[x].ma
#define tag(x) t[x].tag
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
void push_up(int x){ma(x)=max(ma(lc(x)),ma(rc(x)));}
void add(int v,int x){ma(x).first+=v,tag(x)+=v;}
void push_down(int x)
{
    if(!tag(x)) return;
    add(tag(x),lc(x)),add(tag(x),rc(x)),tag(x)=0;
}
void build(int l,int r,int x)
{
    if(l==r) return void(ma(x)={0,l});
    int mid=(l+r)>>1;
    build(l,mid,lc(x)),build(mid+1,r,rc(x));
    return push_up(x);
}
void add(int p,int q,int v,int l,int r,int x)
{
    if(p<=l&&q>=r) return add(v,x);
    push_down(x);
    int mid=(l+r)>>1;
    if(p<=mid) add(p,q,v,l,mid,lc(x));
    if(q>mid) add(p,q,v,mid+1,r,rc(x));
    return push_up(x);
}
struct SEG{
    int l,r,v;
}S[N<<1];
int l[N],r[N],v[N],rt=1,n;
vector<int>Seg[M];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>l[i]>>v[i]>>r[i];
        S[i]={l[i],v[i],1},S[i+n]={l[i],v[i],-1};
        Seg[v[i]].push_back(i),Seg[r[i]+1].push_back(i+n);
    }
    build(1,V,rt);
    int Ans=0,L,R;
    for(int i=1;i<=V;i++)
    {
        for(auto id:Seg[i]) add(S[id].l,S[id].r,S[id].v,1,V,rt);
        if(ma(rt).first>Ans){
            Ans=ma(rt).first;
            L=ma(rt).second,R=i;
        }
    }
    cout<<Ans<<'\n';
    for(int i=1;i<=n;i++)
        if(l[i]<=L&&L<=v[i]&&v[i]<=R&&R<=r[i]) cout<<i<<" ";
    return 0;
}
```

---

## 作者：破壁人五号 (赞：3)

[题目链接](http://codeforces.com/problemset/problem/377/D)

# 题目大意：

有 $n$ 个人，每人有属性 $l_i,v_i,r_i(l_i\leq v_i\leq r_i)$，要求选出最大的人的集合 $S$ 使得 $\forall x,y\in S$ 有 $l_y\leq v_x\leq r_y$

# 题解：

简单分析一下这些不等式可以发现题目的要求可以转化为：$\max\limits_{i\in S} l_i\leq \min\limits_{i\in S} v_i\leq \max\limits_{i\in S} v_i\leq\min\limits_{i\in S} r_i$

进一步地，我们将要求转化为找到 $L,R$，使得 $\max\limits_{i\in S} l_i\leq L\leq \min\limits_{i\in S} v_i,\max\limits_{i\in S} v_i\leq R\leq\min\limits_{i\in S} r_i$

我们将 $(L,R)$ 看作二维平面上的一个点，一个人就对应着一个矩形。集合中选出多个人，对 $(L,R)$ 的限制就是这些矩形的交。选出最多的人，就是要找到一个点被尽可能多的矩形覆盖。

以样例为例

```plain
4
2 8 9
1 4 7
3 6 8
5 8 10
```

![一个 sample](https://i.loli.net/2019/08/13/DsXtg5IWhoj8aBw.png)

找到这个点可以用扫描线+线段树。记录最优的点的位置，输出方案时挨个判断矩形是否包含该点。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int getint(){
    int ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}

const int N=200100,M=600300;
int a[M<<2],tag[M<<2],pos[M<<2];
inline void pushup(int x){
	if(a[x<<1]>a[x<<1|1]){
		pos[x]=pos[x<<1];
		a[x]=a[x<<1];
	}else{
		pos[x]=pos[x<<1|1];
		a[x]=a[x<<1|1];
	}
}
inline void pushdown(int x){
	tag[x<<1]+=tag[x];
	a[x<<1]+=tag[x];
	tag[x<<1|1]+=tag[x];
	a[x<<1|1]+=tag[x];
	tag[x]=0;
}
void modify(int l,int r,int val,int x,int nl,int nr){
	pushdown(x);
	if(l<=nl&&nr<=r){
		a[x]+=val;
		tag[x]+=val;
		return;
	}
	int mid=nl+nr>>1;
	if(nl<=r&&mid>=l)modify(l,r,val,x<<1,nl,mid);
	if(mid+1<=r&&nr>=l)modify(l,r,val,x<<1|1,mid+1,nr);
	pushup(x);
}
inline int query(){
	return a[1];
}
void build(int x,int l,int r){
	if(l==r){
		pos[x]=l;
		return;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pos[x]=pos[x<<1];
}
int l[N],r[N],v[N];
struct seg{
	int x,u,d;
	bool b;
};
seg s[N];
bool cmp(seg a,seg b){
	if(a.x!=b.x)return a.x<b.x;
	else return a.b<b.b;
}
int main(){
	int n=getint();
	for(int i=0;i<n;i++){
		l[i]=getint();
		v[i]=getint();
		r[i]=getint();
		s[i*2].x=l[i];   s[i*2].u=r[i];   s[i*2].d=v[i];   s[i*2].b=0;
		s[i*2+1].x=v[i]; s[i*2+1].u=r[i]; s[i*2+1].d=v[i]; s[i*2+1].b=1;
	}
	build(1,1,3e5+1);
	sort(s,s+n*2,cmp);
	int ans=0,ansp=0,ansx=0;
	for(int i=0;i<n*2;i++){
		modify(s[i].d,s[i].u,s[i].b?-1:1,1,1,3e5+1);
		if(query()>ans){
			ans=query();
			ansp=pos[1];
			ansx=s[i].x;
		}
	}
	cout<<ans<<endl;
	for(int i=0;i<n;i++){
		if(l[i]<=ansx&&ansx<=v[i]&&v[i]<=ansp&&ansp<=r[i])cout<<i+1<<" ";
	}
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：2)

### 思路：

把每个人当成一个三元组 $[l_i,r_i,v_i]$。

然后去考虑每个人对哪个能力区间 $[L,R]$ 有贡献。应该是左端点在 $[l_i,v_i]$，右端点在 $[v_i,r_i]$ 的区间拍到一个二维平面上，求最多有多少个矩形交一起线段树维护扫描线就可以了。

### 代码：
```
#include<bits/stdc++.h>
#define N (600000 + 10)
using namespace std;
inline int read() {
	int cnt = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -f; c = getchar();}
	while (isdigit(c)) {cnt = (cnt << 3) + (cnt << 1) + (c ^ 48); c = getchar();}
	return cnt * f;
}

int n, Y[N], cnt, ans = 0, ansx, ansy, tot;
int l[N], r[N], v[N];
struct node2 {
	int x, Y1, Y2, tag;
}seg[N << 1];

struct node {
	int l, r;
	int tag, gmax, pos;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define tag(p) tree[p].tag
	#define gmax(p) tree[p].gmax
	#define pos(p) tree[p].pos
} tree[N << 2];

void pushdown(int p) {
	tag(p << 1) += tag(p);
	tag(p << 1 | 1) += tag(p);
	gmax(p << 1) += tag(p);
	gmax(p << 1 | 1) += tag(p);
	tag(p) = 0;
}

void pushup(int p) {
	if (gmax(p << 1) > gmax(p << 1 | 1)) {
		pos(p) = pos(p << 1);
		gmax(p) = gmax(p << 1);
	} else {
		pos(p) = pos(p << 1 | 1);
		gmax(p) = gmax(p << 1 | 1);
	}
}

void build (int p, int l, int r) {
	l(p) = l, r(p) = r;
	if (l == r) {pos(p) = Y[l]; return;}
	int mid = (l + r) >> 1;
	build (p << 1, l, mid);
	build (p << 1 | 1, mid + 1, r);
	pos(p) = pos(p << 1);
}

void modify(int p, int l, int r, int k) {
	pushdown(p);
	if (l <= Y[l(p)] && r >= Y[r(p)]) {tag(p) += k, gmax(p) += k; return;}
	int mid = (l(p) + r(p)) >> 1;
	if (l <= Y[mid]) modify(p << 1, l, r, k);
	if (r > Y[mid]) modify(p << 1 | 1, l, r, k);
	pushup(p);
}
bool cmp(node2 a, node2 b) {
	return a.x == b.x ? a.tag > b.tag : a.x < b.x;
}

int main() {
	n = read();
	for (register int i = 1; i <= n; ++i) {
		l[i] = read(), v[i] = read(), r[i] = read();
		seg[++tot].x = l[i], seg[tot].Y1 = v[i], seg[tot].Y2 = r[i], seg[tot].tag = 1, Y[tot] = v[i];
		seg[++tot].x = v[i], seg[tot].Y1 = v[i], seg[tot].Y2 = r[i], seg[tot].tag = -1, Y[tot] = r[i];
	}
	sort (Y + 1, Y + tot + 1);
	for (register int i = 1; i <= tot; ++i) if (Y[i] != Y[i + 1]) Y[++cnt] = Y[i];
	build (1, 1, cnt);
	sort (seg + 1, seg + tot + 1, cmp);
	for (register int i = 1; i <= tot; ++i) {
		modify(1, seg[i].Y1, seg[i].Y2, seg[i].tag);
		if (gmax(1) > ans) {
			ans = gmax(1);
			ansx = seg[i].x;
			ansy = pos(1);
		}
	}
	printf("%d\n", ans);
	for (register int i = 1; i <= n; ++i) 
		if (v[i] <= ansy && r[i] >= ansy && l[i] <= ansx && v[i] >= ansx) printf("%d ", i);
	return 0;
}
```


---

## 作者：Felix72 (赞：2)

一个思维加数据结构的题。

## 题意简述

有若干人，每人有一个能力值，以及最大和最小匹配值。选出最多人使他们能两两匹配。

## 思路

我们注意到如果能定一个上下界，使得选出的每个人能力值都在上下界之间，并使得他们的最小匹配值不大于下界，最大匹配值不小于上界，就能使他们两两匹配。这也是方案合法的本质和充要条件。

那么考虑到能力范围很小，可以建线段树，我们可以先枚举下界。那么怎样计算贡献？假设上界已经确定了，那么如果一个人没有入选，那么他的最大匹配值肯定小于上界。换句话说，如果一个人能力在上下界之间，但最大匹配值大于等于上界，这就为方案贡献了一个人。

到这里思路就清晰了。对于能力值合适的人，我们在线段树上将他的能力值和他的最大匹配值这个值域之间加上一，并维护最大值即可。为了输出方案，我们需要顺便维护下标。如果一个人的能力值小于下界了，撤回他的贡献即可。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N = 300010;
typedef pair < int, int > PII;
int n, idx, rt;
int from, to, ans;
struct node {int id, l, v, r;} a[N], b[N];
inline bool cmp(node x, node y) {return x.l < y.l;}
inline bool cmp2(node x, node y) {return x.v < y.v;}
struct Tree
{
	int ls, rs, data, tag, id;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define data(x) tree[x].data
	#define tag(x) tree[x].tag
	#define id(x) tree[x].id
}tree[N * 16];
inline void pushup(int now)
{
	data(now) = 0;
	if(ls(now))
	{
		if(data(ls(now)) >= data(now)) data(now) = data(ls(now)), id(now) = id(ls(now));
	}
	if(rs(now))
	{
		if(data(rs(now)) >= data(now)) data(now) = data(rs(now)), id(now) = id(rs(now));
	}
}
inline void pushdown(int now)
{
	if(tag(now))
	{
		if(ls(now))
		{
			data(ls(now)) += tag(now);
			tag(ls(now)) += tag(now);
		}
		if(rs(now))
		{
			data(rs(now)) += tag(now);
			tag(rs(now)) += tag(now);
		}
		tag(now) = 0;
	}
}
inline void build(int &now, int l, int r)
{
	if(!now) now = ++idx; id(now) = l;
	if(l == r) return ;
	int mid = l + r >> 1;
	if(l <= mid) build(ls(now), l, mid);
	if(mid < r) build(rs(now), mid + 1, r);
}
inline void insert(int now, int l, int r, int L, int R, int num)
{
	if(L <= l && r <= R) {tag(now) += num; data(now) += num; return ;}
	pushdown(now);
	int mid = l + r >> 1;
	if(L <= mid) insert(ls(now), l, mid, L, R, num);
	if(mid < R) insert(rs(now), mid + 1, r, L, R, num);
	pushup(now);
}
inline PII ask(int now, int l, int r, int L, int R)
{
	if(!now) return {0, 0};
	if(L <= l && r <= R) return {id(now), data(now)};
	int mid = l + r >> 1; PII ans = {0, 0};
	if(L <= mid)
	{
		PII cur = ask(ls(now), l, mid, L, R);
		if(cur.second > ans.second) ans = cur;
	}
	if(mid < R)
	{
		PII cur = ask(rs(now), mid + 1, r, L, R);
		if(cur.second > ans.second) ans = cur;
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	build(rt, 1, 300000);
	for(int i = 1; i <= n; ++i) cin >> a[i].l >> a[i].v >> a[i].r, a[i].id = i, b[i] = a[i];
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + n + 1, cmp2);
	int bj = 1;
	for(int i = 1; i <= n; ++i) //枚举，a[i].l是下界 
	{
		while(bj <= n && b[bj].v < a[i].l) insert(rt, 1, 300000, b[bj].v, b[bj].r, -1), ++bj;
		//撤销不合法贡献 
		insert(rt, 1, 300000, a[i].v, a[i].r, 1);
		//加上贡献 
		PII cur = ask(rt, 1, 300000, a[i].l, 300000);
		if(ans < cur.second)
		{
			ans = cur.second;
			from = a[i].l;
			to = cur.first;
		}
		//查询并更新最大值，记录上下界 
	}
	cout << ans << '\n';
	for(int i = 1; i <= n; ++i)
		if(a[i].l <= from && from <= a[i].v && a[i].v <= to && to <= a[i].r)
			cout << a[i].id << " ";
	return 0;
}
```

---

## 作者：hgckythgcfhk (赞：1)

感觉题解区转化 $\max$ 和 $\min$ 虽然确实是一个很有用的 trick，但在不知道这个 trick 的前提下不太容易想到，换一种方式，考虑两个人能同时选的条件，可以证明，如果集合内任意两个人都能同时选则这个集合内的所有元素可以同时选，我在写这句话的时候突然想到这其实可以看成求一个无向图的最大团，现在在找连边条件，这么说的话感觉这个理解方式就比转化 $\max$ 和 $\min$ 容易多了，毕竟这样只需要考虑两个元素。

暴力枚举讨论两个区间 $3$ 个端点（认为每个人的能力值是中端点）的 $6!$ 种位置关系，先排除一些显然不合法的，每个区间的内部顺序是固定的，那么这相当于在一个长度为 $6$ 的序列上放 $3$ 个第 $1$ 个人的端点，情况只有 $(^6 _3)=20$ 种情况，钦定第一个位置必须放第一个人左端点，因为反之是本质相同的，所以我们只需要讨论 $10$ 种情况，为方便表示，我们把第一个人的端点记为 $1$，第二个人的记为 $0$，每种情况记为一个 $6$ 位的二进制数：

|**情况**|**结果**|
|-|-|
|$111000$|$0$|
|$110100$|$0$|
|$110010$|$0$|
|$110001$|$0$|
|$101100$|$0$|
|$101010$|$1$|
|$101001$|$1$|
|$100110$|$1$|
|$100101$|$1$|
|$100011$|$0$|

这个题本身的性质比如两个人能同时选的必要条件之一是两个人的区间有交（并不充分，看上面的表很容易看出来反例）就提示我们要研究区间的交，实际上就那几个 idea，直接枚举 idea 查表发现两个人能同时选的充分条件是按中端点分成两个区间后，两个人的左区间有交且右区间有交。

上面没考虑端点有重合的情况，但画画图发现重合并不影响，因为我们总可以把重合的点加上或减去 $0.1$，来归纳到表上。

现在的问题就是给定 $n$ 个 $2$ 维的东西，每维是个区间，求最大的两维都有交的集合，这看起来是 $4$ 维的问题，但实际上是 $2$ 维每维两个自由度的，直接这样描述并不一定能直接想到是什么东西，但想想什么东西是 $2$ 维 $4$ 自由度的？居然是矩形（实际上可以枚举所有常见的结构），这也是这个题很妙的地方之一，直接想矩形肯定知道是 $2$ 维 $4$ 自由度的，但 $2$ 维 $4$ 自由度的组合结构我没毫不犹豫的想到矩形，这算是一个看完之后会惊呼居然还可以这样的 trick。

于是答案就是矩形加全局 $\max$，先修改再只做一次询问，方法太多了，其中最好做的就是扫描线。

然后说一下输出方案，我认为这也是本题的难点之一，但现有的题解并没有比较详细的解释，而且我确实在这个地方调了很久，我用了一种比较好想的方法，和题解好像不太一样。

从矩形回到区间，一个矩形可以用两维的区间表示，而且这个操作和上面的判定条件是相当契合的，很容易想到，考虑扫描线的过程，把其中一维理解成时间，原题转化为每个若干个区间有一段存在的时间区间，一次扫描线可以求出可能成为答案的区间，但这是难写的，起码我不想写，换个思路，求出存在答案的时间区间是好写的，跑两遍扫描线，每次换一个维度作为时间维，如果有多个分别在两维随便拿一个就行，多个说明最优解不唯一，然后直接拿着这两个区间去判就行，事实上这可以看成现在造了一个人，钦定这个人必选，然后把所有能选的选上，同时能和这个人同时选的一定互相能同时选，不过我们要把人的定义从 $3$ 个端点改成两个任意的区间，根据我们扫描线的过程，仔细想想这样做绝对是不多不漏的。

最后，上面求时间区间的时候有点问题，在第 $5$ 组数据中，出现了两个答案矩形有顶点重合的情况，需要我们提前对每个人的所有端点翻倍，然后记录时间区间两个端点的时候也有点边界不好处理，具体的看程序吧，这里直接放 CF 上的[提交记录](https://codeforces.com/problemset/status?my=on)。

---

## 作者：rhineofts (赞：1)

考察选择的人的集合的限制：$\max l_i \le \min v_i $ 且 $\max {v_i} \le \min r_i$。

这个 `max <= min` 的形式容易想到线段求交：$\cap(l_i, r_i) = (\max l_i,\min r_i)$，而两个这样的约束可以用矩形求交刻画。第 $i$ 个人对应的矩形在横坐标上的投影为 $[l_i, v_i]$，在纵坐标上的为 $[v_i, r_i]$。问题转化为：找到一个最大的矩形集合，使得矩形交非空。把贡献摊到点上，就是找一个点，使得覆盖它的矩形尽可能多，这就是第一问的答案，第二问就是输出所有覆盖这个点的矩形。

这个东西可以扫描线+线段树维护：线段树要支持区间加，查询全局最大值以及最大值的位置，这都是简单的。复杂度 $O(n\log n)$。

```c++
const int N = 1e5 + 10;
const int V = N * 3, maxv = 3e5;
int n;

namespace seg {
    int w[V << 2], tag[V << 2], mxpos[V << 2];

    #define ls (u << 1)
    #define rs (u << 1 | 1)
    #define mid (l + r >> 1)
    #define inrange() (ql <= l and r <= qr)
    #define outrange() (qr < l or r < ql)

    void pushup(int u) {
        w[u] = max(w[ls], w[rs]);
        if (w[ls] > w[rs]) mxpos[u] = mxpos[ls];
        else mxpos[u] = mxpos[rs];
    }

    void init(int u, int l, int r) {
        if (l == r) mxpos[u] = l;
        else init(ls, l, mid), init(rs, mid + 1, r), pushup(u);
    }

    void apply(int u, int x) {
        w[u] += x, tag[u] += x;
    }

    void pushdown(int u) {
        if (tag[u]) {
            apply(ls, tag[u]); apply(rs, tag[u]);
            tag[u] = 0;
        }
    }

    void modify(int u, int l, int r, int ql, int qr, int x) {
        if (inrange()) {
            apply(u, x); return;
        }
        if (outrange()) return;
        pushdown(u);
        modify(ls, l, mid, ql, qr, x), modify(rs, mid + 1, r, ql, qr, x);
        pushup(u);
    }
};

struct Line {
    int l, r, y, t;
    Line() {}
    Line(int _l, int _r, int _y, int _t) : l(_l), r(_r), y(_y), t(_t) {}
} b[2 * N];

struct Person {
    int l, r, v;
} a[N];

// max(v) <= min(r)
// max(l) <= min(v)

// (l, v), (v, r)

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;

    F (i, 1, n) {
        int l, v, r; cin >> l >> v >> r;
        a[i].l = l, a[i].r = r, a[i].v = v;
        b[i * 2 - 1] = {l, v, v, 1};
        b[i * 2] = {l, v, r + 1, -1};     
    }

    sort(b + 1, b + 1 + 2 * n, [&](auto& LHS, auto& RHS) {
        if (LHS.y != RHS.y) return LHS.y < RHS.y;
        return LHS.t < RHS.t; // 先删后加
    });

    pii ans = {0, 0}; int mx = 0;

    seg::init(1, 1, maxv);

    F (i, 1, 2 * n) {
        seg::modify(1, 1, maxv, b[i].l, b[i].r, b[i].t);
        if (b[i].y != b[i + 1].y) {
            if (ckmax(mx, seg::w[1])) {
                ans = {seg::mxpos[1], b[i].y};
            }
        }
    }

    cout << mx << '\n';

    F (i, 1, n) {
        if (a[i].l <= ans.x and ans.x <= a[i].v and a[i].v <= ans.y and ans.y <= a[i].r) {
            cout << i << " ";
        }
    }

    return 0;
}
```

---

## 作者：Soh_paramEEMS (赞：0)

这个题一眼就看出端点排序、分段贡献，但是考场就是调不出来，又是 WA 又是 RE 的。非常粗心，还需沉淀。
## 题意
有 $n$ 个工人，第 $i$ 个工人的能力是$v_i$，他只与能力在 $l_i$ 到 $r_i$ 之间的人在一起工作，问最多能选出多少人在一起工作。

$1\le n\le 10^5$，$1\le l_i\le v_i\le r_i\le 3\times 10^5$。

CF377D 题面：在 SMOJ 团队基础上要求输出选人方案。下文将按照 CodeForces 题面要求。
## 思路
~~那当然是无脑按端点排序。~~ 

一个显然的结论：若 $a,b,c$ 三个可以一起工作，那么 $v_a,v_b,v_c\in \mathbb{S}=[l_a,r_a]\cup[l_b,r_b]\cup[l_c,r_c]$，即**三者区间交内**。

如果我们枚举这个交集 $\mathbb{S}$ 的左端点 $l_0$，如果存在工人 $i$，使得 $l_i\le l_0\le v_i$，那么所有的右端点 $r_0\in [v_i,r_i]$，都可以被工人 $i$ 贡献到。至于 $l_0\sim v_i$ 这一段大可以不加了，在后面计算实则等价，就费事倒回来找对应的 $l_0$ 删贡献了，并且方便后面找最优的右端点。

那么就可以枚举左端点 $l_0$，可以用 vector 存端点的贡献变化，用线段树区间加：

```cpp
for(int i=1;i<=n;i++)
{
	int v,l,r;
	scanf("%d%d%d",&l,&v,&r);
	p[l].push_back((term){i,1});
	p[v+1].push_back((term){i,-1});
	R=max(R,r);
}
for(int i=1;i<=R;i++)//枚举区间交左端点 
{
	for(auto x:p[i])
	A.add(1,1,R,a[x.id].v,a[x.id].r,x.val);//v~r 都可以被贡献
}
```
答案就是全局单点最大值了。那方案要怎么办呢？

其实很简单。我们在线段树上，维护单点最大值的同时，维护单点下标；此时在维护 $l_0$，那么这个下标就是相应的最优 $r_0$。记录工人数最多的区间并。然后 $\Theta(n)$ 扫一遍看看每个工人是否满足区间并即可。具体细节见代码：
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls u<<1
#define rs u<<1|1
#define pii pair<int,int> 
#define fi first
#define se second
const int N=1e5+2,M=3e5+2,inf=0x7f7f7f7f;
int n,R;
int ans,anl,anr;
struct term
{
	int id,val;
};
struct vlr
{
	int v,l,r;
}a[N];
vector<term>p[M];
struct SegT
{
	struct node
	{
		pii ma;
		int tag;
	}T[M<<2];
	void pushup(int u)
	{
		T[u].ma=max(T[ls].ma,T[rs].ma);
	}
	void pushdown(int u)
	{
		if(T[u].tag)
		{
			T[ls].ma.fi+=T[u].tag;
			T[ls].tag+=T[u].tag;
			T[rs].ma.fi+=T[u].tag;
			T[rs].tag+=T[u].tag;
			T[u].tag=0;
		}
	}
	void build(int u,int l,int r)
	{
		if(l==r)
		{
			T[u].ma.se=l;
			return;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(u);
	}
	void add(int u,int l,int r,int ql,int qr,int k)
	{
		if(qr<l||r<ql)return;
		if(ql<=l&&r<=qr)
		{
			T[u].ma.fi+=k;
			T[u].tag+=k;
			return;
		}
		pushdown(u);
		int mid=(l+r)>>1;
		if(ql<=mid)add(ls,l,mid,ql,qr,k);
		if(qr>mid)add(rs,mid+1,r,ql,qr,k);
		pushup(u);
	}
}A;
bool check(vlr x)
{
	return x.l<=anl&&anr<=x.r&&anl<=x.v&&x.v<=anr;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int v,l,r;
		scanf("%d%d%d",&l,&v,&r);
		a[i]=(vlr){v,l,r}; 
		p[l].push_back((term){i,1});
		p[v+1].push_back((term){i,-1});
		R=max(R,r);
	}
	A.build(1,1,R);
	for(int i=1;i<=R;i++)//枚举区间交左端点 
	{
		for(auto x:p[i])
		A.add(1,1,R,a[x.id].v,a[x.id].r,x.val);
		if(A.T[1].ma.fi>ans)
		{
			ans=A.T[1].ma.fi;
			anl=i,anr=A.T[1].ma.se;
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
	if(check(a[i]))printf("%d ",i);
	return 0;
}
```

---

