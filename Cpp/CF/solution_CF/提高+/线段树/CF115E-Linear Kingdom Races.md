# Linear Kingdom Races

## 题目描述

你是一个赛车比赛的组织者，想在线性王国中安排一些比赛。

线性王国有 $n$ 条连续的从左到右的道路。道路从左到右依次编号为从 $1$ 到 $n$，因此道路按照升序排列。在这些道路上可能会有几场比赛，每一场比赛都将使用这些道路的某个连续的子序列。而且，如果某场比赛举行了，你将获得一定数额的金钱。没有比赛在时间上重叠，所以每一段道路可以在多个比赛中使用。

不幸的是，**所有道路**的状况都不佳，需要修理。每条路都有与之相关的维修费用，你需要支付这笔费用来修理道路。只有在某场比赛中需要使用的所有道路**都进行了修复**，才能进行比赛。你的任务是修复道路并使你的利润最大化。你的利润被定义为你从比赛中获得的总金额减去你花在修理道路上的钱。**请注意，您可以决定不修任何道路，并获得利润 $0$。**

输出你能获得的最大利润。

## 说明/提示

在第一个样例中，最优解是修复 $1, 2, 3, 7$。你将会在第 $1, 2, 4$ 三场比赛中获得 $15$ 的收益。道路修理费用是 $11$，因此你的利润是 $4$。

## 样例 #1

### 输入

```
7 4
3
2
3
2
1
2
3
1 2 5
2 3 5
3 5 3
7 7 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 1
0
3
1 2 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 1
10
10
10
1 3 10
```

### 输出

```
0
```

# 题解

## 作者：Priori_Incantatem (赞：49)

看完题后，你的第一个想法可能是考虑每场比赛是否进行，并计算相应的路费。  
但是，如果两次比赛的路线重合，路费就只用支付一次。由此就产生了后效性，对我们的DP造成了困难。

那么，我们可以反过来想：考虑每条路是否支付路费（修路），并算出所有可以进行的比赛赚到的钱。  
设 $f[i]$ 表示前 $i$ 条路中修复若干条路后可以赚到的最多的钱。  
转移方程：  
- $f[i]=f[i-1]$，即**不修**第 $i$ 条路。
- $f[i]=\max\limits_{0\le j <i} \{f[j]+\operatorname{val}(j+1,i)-\operatorname{cost}(j+1,i)\}$，将区间 $[j+1,i]$ 中的路都修好。其中 $\operatorname{cost}(j+1,i)$ 表示修好区间中所有路所要花的钱；$\operatorname{val}(j+1,i)$ 表示区间中的路都修好的情况下，举行比赛可以赚到的钱。

我们考虑用线段树来优化，第 $j$ 个位置 $(0 \le j \le n)$ 的 $c[j]$ 储存 $f[j]+\operatorname{val}(j+1,i)-\operatorname{cost}(j+1,i)$  
每次枚举到一个新的 $i$ 时：
1. 将 $c[0\dots i-1]$ 减去 $a[i]$（修路的价钱），因为都要多修一条路。
2. 对于每个右端点 $r=i$ 的比赛 $(l,r,v)$，将 $c[0\dots l-1]$ 都加上 $v$。因为在这些状态中，$[l,r]$ 区间的路都修好了（可以进行比赛）。
3. 更新当前状态：$f[i]=\max(f[i-1],\max\limits_{0\le j < i}\{c[j]\})$。
4. 最后，更新线段树中的 $c[i]$。

总时间复杂度$\operatorname{O}(n\log n)$。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const long long Maxn=200000+10,inf=(1ll<<60);
const long long Maxm=Maxn<<2;
struct node{
	long long p,v;
	node(long long x,long long y)
	{
		p=x,v=y;
	}
};
long long maxv[Maxm],add[Maxm];
long long a[Maxn],f[Maxn];
vector <node> c[Maxn];
long long n,m;
inline long long read()
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void check(long long &x,long long y)
{
	if(y>x)x=y;
}
inline void push_up(long long k)
{
	maxv[k]=max(maxv[k<<1],maxv[k<<1|1]);
}
inline void upd(long long k,long long v)
{
	maxv[k]+=v;
	add[k]+=v;
}
inline void push_down(long long k)
{
	if(!add[k])return;
	upd(k<<1,add[k]);
	upd(k<<1|1,add[k]);
	add[k]=0;
}
void modify(long long k,long long l,long long r,long long x,long long y,long long v)
{
	if(x<=l && r<=y)return upd(k,v);
	push_down(k);
	long long mid=(l+r)>>1;
	if(x<=mid)modify(k<<1,l,mid,x,y,v);
	if(mid<y)modify(k<<1|1,mid+1,r,x,y,v);
	push_up(k);
}
long long query(long long k,long long l,long long r,long long x,long long y)
{
	if(x<=l && r<=y)return maxv[k];
	push_down(k);
	long long mid=(l+r)>>1,ret=-inf;
	if(x<=mid)ret=query(k<<1,l,mid,x,y);
	if(mid<y)check(ret,query(k<<1|1,mid+1,r,x,y));
	return ret;
}
void modify_val(long long k,long long l,long long r,long long pos,long long v)
{
	if(l==r)
	{
		add[k]=0,maxv[k]=v;
		return;
	}
	push_down(k);
	long long mid=(l+r)>>1;
	if(pos<=mid)modify_val(k<<1,l,mid,pos,v);
	else modify_val(k<<1|1,mid+1,r,pos,v);
	push_up(k);
}
int main()
{
	n=read(),m=read();
	for(long long i=1;i<=n;++i)
	a[i]=read();
	while(m--)
	{
		long long x=read(),y=read(),v=read();
		c[y].push_back(node(x,v));
	}
	for(long long i=1;i<=n;++i)
	{
		modify(1,0,n,0,i-1,-a[i]);
		for(long long j=0;j<c[i].size();++j)
		{
			long long p=c[i][j].p,v=c[i][j].v;
			modify(1,0,n,0,p-1,v);
		}
		f[i]=max(query(1,0,n,0,i-1),f[i-1]);
		modify_val(1,0,n,i,f[i]);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：王鲲鹏 (赞：12)

Update 2020-07-15 晚:  
同学zly指出了一些问题，比较严重，更正一次。在公式中忽略了当$i=j$时$l=r=i$的赛事的收益。

---

这是一道 线段树优化DP 的模板题。

我跟第一篇题解的思路相反，定义 $ f[i][j] $ 表示考虑到第i个道路，$[j,i]$全都选择的最大收益。$Ans$表示考虑到$i$时累计的最大收益。

考虑如何从 $ f[i-1][?] $ 转移到 $ f[i][j] $。
对于 $j < i$ ，新增了道路$i$的代价 $cost_i$，和右端点 $r=i$ ，并且能被区间$[j,i]$覆盖的赛事的收益的和。 
$$
f[i][j]=f[i-1][j]-cost_i +\sum\limits_{r=i,l\leq j}p
$$
对于 $j=i$，
$$
f[i][i] = \max_{0\leq k \leq p\leq i-1}\{f[p][k]\}-cost_i=Ans-cost_i+\sum_{l=r=i}p
$$

如何优化到一个比较好的复杂度呢？

可以发现每次新考虑一个道路时，
区间$[1,i]$都相当于在$f[i-1][\cdots]$的基础上减去同一个值$cost_i$；
对每个右端点为$i$ 的比赛，在这个时候有贡献，区间 $[1,l_b]$ 加上 $p_b$（在$f[i-1][\cdots]$的基础上），对$f[i][i]$，可以看做赋值$Ans$（区间减时减去$cost_i$）。

如果考虑滚动数组，发现其实上述转移是区间加，
维护$Ans$的过程是区间求最值。

于是考虑线段树。

最后一个小问题，如何维护右端点在$i$的所有赛事呢？我这里有两种方法，一个是用链表（就是邻接表），一个是按右端点排序后扫描，大家应该都会吧。

代码

```cpp
#include <cstdio>
typedef long long ll;
const int maxn = 200003;
int read() {
    int x = 0, c = getchar();
    while (c < '0' && c > '9') c = getchar();
    while ('0' <= c && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x;
}
int n = 0, m = 0;
int head[maxn], left[maxn], nxt[maxn], cnt = 0;
ll p[maxn], w[maxn];
void insert(int R, int L,int v) {
    nxt[++cnt] = head[R];
    head[R] = cnt;
    left[cnt] = L;
    p[cnt] = v;
}
ll ma[maxn<<2], lazy[maxn<<2];
inline ll max(ll a, ll b) { return a<b?b:a; }
inline void pushDown(int p) {
    ma[p << 1] += lazy[p];    
    ma[p << 1 | 1] += lazy[p];
    lazy[p << 1] += lazy[p];
    lazy[p << 1 | 1] += lazy[p];
    lazy[p] = 0;
}
inline void pushUp(int p) {
    ma[p] = max(ma[p<<1], ma[p<<1|1]);
}
void plus(int p,int L,int R,int l,int r, ll v) {
    if(l <= L && R <= r) {
        ma[p]+=v;
        lazy[p]+=v;
        return;
    }
    pushDown(p);
    int mid = (L+R)>>1;
    if(l <=mid) plus(p<<1,L,mid, l,r,v);
    if(r>mid) plus(p<<1|1,mid+1,R,l,r,v);
    pushUp(p);
}
int main() {
    n = read(); m = read();
    for (int i = 1;i<=n;++i) w[i] = read();
    int L = 0, R = 0, P = 0;
    for(int i=1;i<=m;++i) {
        L=read(); R=read(); P=read();
        insert(R,L,P);
    }
    ll ans = 0;
    for(int i = 1;i<=n;++i) {
        plus(1,1,n,i,i,ans);
        plus(1,1,n,1,i,-w[i]);
        for(int j = head[i];j;j=nxt[j])
            plus(1,1,n,1,left[j], p[j]);
        ans = max(ans,ma[1]);
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：louhao088 (赞：3)

线段树优化 DP 。


------------


令 $f[i][j]$ 表示前 i 个选了第 $i-j$​ 个的最大价值。

于是很容易得出

$f[i][j]=f[i-1][j]+val(i,j)-sum[i]$

由于 $f[i][j]$ 只与 $f[i-1][j]$ 有关，可以去掉第一维。

这样空间复杂度就解决了，但时间还是 $n^2$ 。

考虑线段树优化，每次转移相当于区间加。

求最大值就每次操作都求一个最大值，也就是线段树维护区间最大。

这样复杂度就降为 $O(n \log n)$ 。

注意要开 long long


------------


代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define int long long
#define ls (rt<<1)
#define rs (rt<<1|1) 
#define mid (l+r>>1)
#define mp make_pair
#define fi first
#define se second
const int maxn=2e5+5;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,q,a[maxn],tag[maxn*4],Max[maxn*4],f[maxn],l,r,x,ans;
void push(int rt,int l,int r)
{
	if(tag[rt])
	{
		tag[ls]+=tag[rt],Max[ls]+=tag[rt];
		tag[rs]+=tag[rt];Max[rs]+=tag[rt];tag[rt]=0;
	}
}
void add(int rt,int l,int r,int L,int R,int num)
{
	if(l>R||r<L)return;
	if(l>=L&&r<=R){tag[rt]+=num;Max[rt]+=num;return;}
	push(rt,l,r);
	add(ls,l,mid,L,R,num),add(rs,mid+1,r,L,R,num);
	Max[rt]=max(Max[ls],Max[rs]);
}
int query(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)return 0;
	if(l>=L&&r<=R){return Max[rt];}
	push(rt,l,r);
	return max(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
}
vector<pair<int,int>>b[maxn];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)l=read(),r=read(),x=read(),b[r].push_back(mp(l,x));ans=0;
	for(int i=1;i<=n;i++)
	{
		add(1,1,n,i,i,ans);add(1,1,n,1,i,-a[i]);
		for(auto j:b[i])
			add(1,1,n,1,j.fi,j.se);
		ans=max(query(1,1,n,1,i),ans);
	}cout<<ans<<endl;
 	return 0;
}
```


---

## 作者：lzzVIL (赞：3)

## 前言
	又提供了一篇翻译，感觉神清气爽。
## [题意](https://www.luogu.org/problemnew/show/CF115E)
## 题目描述
你是一个赛车比赛的组织者，想在线性王国中安排一些比赛。

线性王国有n条连续的从左到右的道路。道路从左到右依次编号为从1到n，因此道路按照升序排列。在这些道路上可能会有几场比赛，每一场比赛都将使用这些道路的某个连续的子序列。而且，如果某场比赛举行了，你将获得一定数额的金钱。没有比赛在时间上重叠，所以每一段道路可以在多个比赛中使用。

不幸的是，**所有道路**的状况都不佳，需要修理。每条路都有与之相关的维修费用，你需要支付这笔费用来修理道路。只有在某场比赛中需要使用的所有道路**都进行了修复**，才能进行比赛。你的任务是修复道路并使你的利润最大化。你的利润被定义为你从比赛中获得的总金额减去你花在修理道路上的钱。**请注意，您可以决定不修任何道路，并获得利润0。**

输出你能获得的最大利润。

## 输入输出格式
### 输入格式：
第一行包括两个整数n和m$(1 \leq n,m \leq 2\cdot 10^5)$，分别表示道路的数量和比赛的数量。

接下来n行，每行一个整数，表示这条道路修复需要的代价。

再接下来m行，每行包括三个整数$l_b,u_b,p(1 \leq l_b,u_b \leq n,1 \leq p \leq 10^9)$，表示第b场比赛需要使用道路$l_b,u_b$，你会获得收益p。
### 输出格式：
输出一个整数，表示你能获得的最大利润。

P.S.请不要使用%lld在C++中读写64位整数。推荐使用cin和cout流（也可以使用%I64d）。
## 说明
在第一个样例中，最优解是修复1、2、3和7。你将会在第1、2、4三场比赛中获得15的收益。道路修理费用是11，因此你的利润是4。
## 题解
	这是一道DP动态规划题+线段树优化。
    首先，考虑一个比较暴力的DP。
    先将所有比赛的序列按右端点从小到大排序。
    我们开一个数组f，f[i][j]表示前i段道路中，最右边没有修复的位置是j，这样的最大收益是f[i][j]。
    我们考虑是否对这第i段道路进行修复。
    如果不修复，那么不需要付出代价。但是，这样的情况中，最右边没有修复的位置就是i了。因此我们考虑转移f[i][i]。枚举j(0<=j<=i)，f[i][i]=max(f[i][i],f[i-1][j])。
    如果修复，那么所有以i为右端点的比赛都可以获得收益。因此枚举j(0<=j<li)，f[i][j]=f[i-1][j]+p，不过i之前的所有的都需要付出代价，因此枚举j(0<=j<i)，f[i][j]=f[i-1][j]-cost[i]，cost表示代价。
    但是，这样肯定太慢了，是O(n^2)的，肯定会TLE的。因此，我们考虑用线段树进行维护。
    注意到我们只需要求区间最大值和序列和，因此用线段树就够了。
    这里，我们只需要“下放lazy_tag（懒标记）”“区间加”“区间最大值”这三个操作就够了。
    至于将所有比赛的序列按右端点从小到大排序，我们可以开一个不定长数组a，a[r]每次增加一个pair<ll,ll>(l,x)，就免去了排序（不会的可以老老实实打一遍排序）。
   特别感谢@[BestFy](https://www.luogu.org/space/show?uid=19722)提供的学术指导！
## 代码
```cpp
#include<algorithm>
#include<cctype>
#include<cstdio>
#include<vector>
#define ll long long
#define pll pair<ll,ll>
#define gc getchar
#define MaxN 200020
using namespace std;
//读入优化
inline ll read(){
	char ch=gc();ll x=0,op=1;
	for (;!isdigit(ch);ch=gc()) if (ch=='-') op=-1;
	for (;isdigit(ch);ch=gc()) x=(x<<1)+(x<<3)+ch-'0';
	return x*op;
}
inline void read(ll &x){x=read();}
inline void write(ll x){
	if (x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);putchar(x%10+'0');
}
inline void writeln(){putchar('\n');}
inline void writeln(ll x){write(x);writeln();}
struct segment_tree{
	ll n;
	struct point{ll a,tag,max;}P[MaxN<<2];
    //a表示修路的花费，tag是懒标记，max是最大值
	inline ll ls(ll x){return x<<1;}
	inline ll rs(ll x){return x<<1|1;}
	inline void scan(){for (int i=1;i<=n;++i) read(P[i].a);}
	inline void push_down(ll p){
		if (!P[p].tag) return;
		P[ls(p)].tag+=P[p].tag,P[rs(p)].tag+=P[p].tag;
		P[ls(p)].max+=P[p].tag,P[rs(p)].max+=P[p].tag;
		P[p].tag=0;
	}
    //下方懒标记
	inline void update(ll L,ll R,ll l,ll r,ll p,ll k){
		if(L<=l&&r<=R){P[p].tag+=k,P[p].max+=k;return;}
		push_down(p);ll mid=(l+r)>>1;
	    if(L<=mid) update(L,R,l,mid,ls(p),k);
	    if(R>mid) update(L,R,mid+1,r,rs(p),k);
	    P[p].max=max(P[ls(p)].max,P[rs(p)].max);
	}
    //区间L到R每个节点添加k
	inline ll query(ll L,ll R,ll l,ll r,ll p){
		if(L<=l&&r<=R)return P[p].max;
		push_down(p);ll mid=(l+r)>>1,res=0;
		if(L<=mid) res=max(res,query(L,R,l,mid,ls(p)));
		if(R>mid) res=max(res,query(L,R,mid+1,r,rs(p)));
		return res;
	}
    //查询区间L到R的最大值
} T;//线段树维护DP序列
ll m,cost[MaxN];ll sum,ans,t[MaxN<<2],mx[MaxN<<2];
vector<pll> a[MaxN];
signed main(){
	read(T.n),read(m);T.scan();
	for (ll i=1;i<=m;++i){ll l=read(),r=read(),x=read();a[r].push_back(pll(l,x));}	
    //往不定长数组中添加一对l和x，记录以r为右端点的序列
	for (ll i=1;i<=T.n;++i){
		T.update(i,i,0,T.n,1,T.query(0,i-1,0,T.n,1));
        //不修复，对于j(0<=j<=i)，f[i][i]=max(f[i][i],f[i-1][j])。
		for (ll j=0;j<(ll)a[i].size();++j) T.update(0,a[i][j].first-1,0,T.n,1,a[i][j].second);
        //对于j(0<=j<li)，f[i][j]=f[i-1][j]+p。
		T.update(0,i-1,0,T.n,1,-T.P[i].a);	
        //对于j(0<=j<i)，f[i][j]=f[i-1][j]-T.P[i].a[i]，表示付出代价。
	}
	return writeln(T.P[1].max),0;
}
```

---

## 作者：lxzy_ (赞：2)

~~这个方法稍微有亿点点复杂和玄学，但是比较无脑。~~

首先可以知道，由于比赛用的赛道时连续的，因此被修复的赛道一定是形成一个个连续的区间的。

定义 $f[i]$ 表示第 $i$ 个赛道强制修复，前 $i$ 个赛道的最大收益。 $s_{a,b}$ 表示选择 $[a,b]$ 的花费，$v_{a,b}$ 表示选择 $[a,b]$ 的收益，第 $i$ 场比赛的左右端点，收益分别为 $l_i,r_i,w_i$，第 $i$ 个赛道的花费为 $cost_i$ 。

$$f[i]=\max\limits_{j\leq i}(f[j]-s_{j,i}+v_{j,i})$$

这个方程所表示的含义即 $[j,i]$ 这一段区间需要修复。当然，当 $j=i$ 时需要特判，具体见下。

由于修复的赛道是连续的，因此每次向后枚举时 $(i\rightarrow i+1)$ ， $[0,i]$ 中 $f_j$ 值发生改变的肯定是一个区间，可以考虑使用线段树优化。用一棵线段树 $tree_j$ 维护当前 $[0,i]$ 的所有 $j$ 的 $f_j-s_{j,i}+v_{j,i}$ ， 对于每一次的枚举 $(i\rightarrow i+1)$ ，所有 $tree_j$ 中的 $f_j$ 都是不变的，因此我们只需考虑如何更改 $s_{j,i}$ 和 $v_{j,i}$ 即可。

$s_{j,i}:$ 只需给 $[0,i-1]$ 的 $tree$ 都 $-w_i$ 即可（强制修复）。

$v_{j,i}:$ 这里我们需要特判之前 $j=i$ 的情况（因为 $f_i$ 无法从他自身转移过来），首先枚举 $j=i$ 的情况：即 $\max(f_j)-cost_i+val_i$ （这里的 $val_i$ 指的是所有 $[i,i]$ 的比赛的收益和）。然后枚举 $j<i$ 的情况：对于 $l_k!=r_k$ 的比赛 $[0,l_k]$ 的 $tree$ 都 $+w_k$ ；对于 $l_k=r_k=i$ 的比赛，$[0,l_k-1]$ 的 $tree$ 都 $+w_k$ （因为 $j=i$ 的情况已经计算过其收益） ；另外要注意，如果以上的收益是负数，则 $f_i=0$ （啥也不修复）

$$f[i]=\max(\max\limits_{j < i} tree_j ,f_j-cost_i+w_k)$$

具体实现细节见代码 (ˇ∀ˇ)

```cpp
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<algorithm>
#define INF 0x7f7f7f7f7f7f7f7f
#define int long long
using namespace std;
const int N=2e5+50;
struct Match{int to,val,nxt;}a[N];//链式前向星存储所有赛道，便于枚举r=i的所有赛道
int maxn[N<<2],tag[N<<2],s[N],f[N],head[N],cnt;
int n,m,ans=-INF;
inline int Read()
{
   	int x=0;
   	char ch=getchar();
   	while(ch>'9'||ch<'0') ch=getchar();
   	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-48,ch=getchar();
   	return x;
}
inline int Max(int a,int b){return a>b?a:b;}
inline void Add_Edge(int u,int v,int w)
{
   	cnt++;
   	a[cnt].to=v,a[cnt].val=w,a[cnt].nxt=head[u];
   	head[u]=cnt;
}

//线段树区间修改，区间查询最大值
inline void Add(int k,int l,int r,int v)
{
   	maxn[k]+=v;
   	tag[k]+=v;
}
inline void Pushdown(int k,int l,int r)
{
   	if(!tag[k]) return ;
   	int mid=(l+r)>>1;
   	Add(k<<1,l,mid,tag[k]),Add(k<<1|1,mid+1,r,tag[k]);
   	tag[k]=0;
}
inline int Query(int k,int l,int r,int x,int y)
{
   	if(l>y||r<x) return 0;
   	if(x<=l&&r<=y) return maxn[k];
   	Pushdown(k,l,r);
   	int mid=(l+r)>>1,res=-INF;
   	if(x<=mid) res=Max(res,Query(k<<1,l,mid,x,y));
   	if(y>mid) res=Max(res,Query(k<<1|1,mid+1,r,x,y));
   	return res;
}
inline void Modify(int k,int l,int r,int x,int y,int v)
{
   	if(l>y||r<x) return ;
   	if(x<=l&&r<=y){
   		Add(k,l,r,v);
   		return ;
   	}
   	Pushdown(k,l,r);
   	int mid=(l+r)>>1;
   	if(x<=mid) Modify(k<<1,l,mid,x,y,v);
   	if(y>mid) Modify(k<<1|1,mid+1,r,x,y,v);
   	maxn[k]=Max(maxn[k<<1],maxn[k<<1|1]);
}
signed main()
{
   	n=Read(),m=Read();
   	for(int i=1;i<=n;i++) s[i]=Read();
   	for(int i=1;i<=m;i++){
   		int l=Read(),r=Read(),p=Read();
   		Add_Edge(r,l,p);//以r为起点建立菊花图
    }
    for(int i=1;i<=n;i++){
    	Modify(1,0,n,0,i-1,-s[i]);
    	int tmp=0;
    	for(int j=head[i];j;j=a[j].nxt) Modify(1,0,n,0,a[j].to-(i==a[j].to),a[j].val),tmp+=a[j].val*(i==a[j].to);//枚举所有r=i的赛道，若l=r=i，则[0,r-1] +w ，否则[0,r] +w
   		f[i]=Max(Query(1,0,n,0,i-1),ans-s[i]+tmp);//j<i和j=i两种情况（ans=max(f_j)）
    	ans=Max(0,Max(ans,f[i]));//记得0的情况
    	Modify(1,0,n,i,i,f[i]);//将f_i插入线段树
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：傅思维666 (赞：1)

## 题解：

感谢翻译官的翔实处理。

一道线段树优化DP的问题，设置状态为：$dp[i]$表示前i条道路的最大价值。

我们发现，转移的时候要频繁修改区间，那么为了保证时间复杂度，我们采用线段树来优化这个东西。维护一棵线段树，维护$dp[j]+w[j]$。其中$w[j]$表示更新的贡献。维护过程如下：

首先，对于每个i，先对区间$[0,i-1]$统一减去$v[i]$。

然后对于每个可转移的比赛区间$[l,r]$，对$[0,l-1]$统一加上p。

最后查询的就是$[0,i-1]$的区间最大值。更新状态，并把新状态赋给新线段树。

所以代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#define int long long
#define lson pos<<1
#define rson pos<<1|1
using namespace std;
const int maxn=2*1e5+10;
const int INF=1e9;
struct add
{
	int l,k;
	add(int p,int q)
	{
		l=p,k=q;
	}
};
int n,m;
int v[maxn];
vector<add> vec[maxn];
int tree[maxn<<2],lazy[maxn<<2];
int dp[maxn];
void pushup(int pos)
{
	tree[pos]=max(tree[lson],tree[rson]);
}
void mark(int pos,int l,int r,int k)
{
	tree[pos]+=k;
	lazy[pos]+=k;
}
void pushdown(int pos,int l,int r)
{
	int mid=(l+r)>>1;
	mark(lson,l,mid,lazy[pos]);
	mark(rson,mid+1,r,lazy[pos]);
	lazy[pos]=0;
}
void update(int pos,int l,int r,int x,int y,int k)
{
	int mid=(l+r)>>1;
	if(x<=l && r<=y)
	{
		mark(pos,l,r,k);
		return;
	}
	pushdown(pos,l,r);
	if(x<=mid)
		update(lson,l,mid,x,y,k);
	if(y>mid)
		update(rson,mid+1,r,x,y,k);
	pushup(pos);
}
int query(int pos,int l,int r,int x,int y)
{
	int mid=(l+r)>>1;
	if(x<=l && r<=y)
		return tree[pos];
	pushdown(pos,l,r);
	int ret=-INF;
	if(x<=mid)
		ret=max(ret,query(lson,l,mid,x,y));
	if(y>mid)
		ret=max(ret,query(rson,mid+1,r,x,y));
	return ret;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&v[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		vec[y].push_back(add(x,z));
	}
	for(int i=1;i<=n;i++)
	{
		update(1,0,n,0,i-1,-v[i]);
		for(int j=0;j<vec[i].size();j++)
		{
			int ll=vec[i][j].l,kk=vec[i][j].k;
			update(1,0,n,0,ll-1,kk);
		}
		dp[i]=max(query(1,0,n,0,i-1),dp[i-1]);
		update(1,0,n,i,i,dp[i]);
	}
	printf("%lld",dp[n]);
	return 0;
}
```


---

