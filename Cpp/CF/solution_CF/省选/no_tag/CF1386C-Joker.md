# Joker

## 题目描述

Joker returns to Gotham City to execute another evil plan. In Gotham City, there are $ N $ street junctions (numbered from $ 1 $ to $ N $ ) and $ M $ streets (numbered from $ 1 $ to $ M $ ). Each street connects two distinct junctions, and two junctions are connected by at most one street.

For his evil plan, Joker needs to use an odd number of streets that together form a cycle. That is, for a junction $ S $ and an even positive integer $ k $ , there is a sequence of junctions $ S, s_1, \ldots, s_k,       S $ such that there are streets connecting (a) $ S $ and $ s_1 $ , (b) $ s_k $ and $ S $ , and (c) $ s_{i-1} $ and $ s_i $ for each $ i = 2, \ldots, k $ .

However, the police are controlling the streets of Gotham City. On each day $ i $ , they monitor a different subset of all streets with consecutive numbers $ j $ : $ l_i \leq j \leq       r_i $ . These monitored streets cannot be a part of Joker's plan, of course. Unfortunately for the police, Joker has spies within the Gotham City Police Department; they tell him which streets are monitored on which day. Now Joker wants to find out, for some given number of days, whether he can execute his evil plan. On such a day there must be a cycle of streets, consisting of an odd number of streets which are not monitored on that day.

## 说明/提示

The graph in the example test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1386C/02355ffc3a7f4ba1f3c2044169f1480727f331fb.png)

## 样例 #1

### 输入

```
6 8 2
1 3
1 5
1 6
2 5
2 6
3 4
3 5
5 6
4 8
4 7```

### 输出

```
NO
YES```

# 题解

## 作者：critnos (赞：8)

整体二分，一个相当具有一般性的方法。

把数组复制一份接在末尾，然后预处理 $ans$ 表示左端点对应的最左的右端点使得 $[l,ans_l]$ 不是二分图。

每次直接判断 $[ans_{r+1}\le m+l-1]$。

$ans_l$ 显然单调，所以设 $(l,r,L,R)$ 表示 $L\le f_l\le f_r\le R$。

所以设 $mid \in [l,r]$ 则显然有 $(l,mid-1,L,ans_{mid}),(mid+1,r,ans_{mid},R)$。

考虑求出 $ans_{mid}$，显然不能直接从 $mid$ 开始扫，所以在整体二分的过程中若 $r+1\le L-1$ 则保留 $[r+1,L-1]$ 中的边然后扫的时候跳过这段。

时间复杂度与 $r-l+1,R-L+1$ 相关，显然这些的总和为 $O(n\log n)$。

用可撤销并查集拆点维护二分图，时间复杂度 $O(n\log^2 n)$。

完整代码：

```cpp
#include<bits/stdc++.h>
#define Yukinoshita namespace
#define Yukino std
#define ll long long
#define u unsigned
using Yukinoshita Yukino;
int read()
{
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}
const int mxn=4e5+5;
int f[mxn],sz[mxn],ans[mxn],x[mxn],y[mxn];
inline int find(int x)
{
	for(;x!=f[x];x=f[x]);
	return x;
}
int n,ti;
struct undo
{
	int x,y,t;
};
stack<undo> stk; 
void merge_(int x,int y)
{
	y=find(y);
	if(x==y) return;
	if(sz[x]>sz[y]) swap(x,y);
	f[x]=y,sz[y]+=sz[x];
	stk.push({x,y,ti});
}
int merge(int x,int y)
{
	ti++;
	int fx=find(x),fy=find(y);
	if(fx==fy) return 1;
	merge_(fx,y+n),merge_(fy,x+n);
	return 0;
}
void undo()
{
	for(;stk.size()&&stk.top().t==ti;stk.pop())
		f[stk.top().x]=stk.top().x,
		sz[stk.top().y]-=sz[stk.top().x];
	ti--;
}
void solve(int l,int r,int L,int R)//保证  r+1~L-1 被加入 
{
	if(l>r||L>R) return;
	if(L==R)
	{
		for(;l<=r;l++)
			ans[l]=L;
		return;
	}
	int i,j,mid=l+r>>1;
	for(i=mid;i<=R;i++)
	{
		if(i==r+1) i=max(i,L);
		if(merge(x[i],y[i]))
			break;
	}
	ans[mid]=i;
	for(;i>=L&&i>=mid;i--)
	{
		if(i==L-1) i=min(i,r);
		undo();
	}	
	solve(l,mid-1,L,ans[mid]);
	for(i=mid;i<=r&&i<=L-1;i++)
		undo();
	for(i=max(r+1,L);i<=ans[mid]-1;i++)
		merge(x[i],y[i]);
	solve(mid+1,r,ans[mid],R);
	for(i=max(r+1,L);i<=ans[mid]-1;i++)
		undo();
}
int main()
{
	int m,q,i,j,l,r,s;
	n=read(),m=read(),q=read();
	for(i=1;i<=n*2;i++)
		f[i]=i,sz[i]=1;
	for(i=1;i<=m;i++)
		x[i]=x[i+m]=read(),y[i]=y[i+m]=read();
	x[m*2+1]=y[m*2+1]=1;
	solve(1,m+1,1,m*2+1);
	while(q--)
	{
		l=read(),r=read();
		puts(ans[r+1]<=m+l-1?"YES":"NO");
	}
}
```


---

## 作者：ollo (赞：8)

感觉这道题的题解讲的都不是很清楚，来写一发。

# 题目大意

给定一张 $n$ 个点 $m$ 条边的图，$q$ 次询问，每次询问删掉 $[l_i,r_i]$ 内的边，问这张图是否存在奇环。

# 大致思路

考虑到一张图是二分图的充要条件是这张图不存在奇环，由于充要条件可逆，题目条件可转化为问删去一些边后这张图是否是二分图。

删边这个操作是我们不喜欢的，可以考虑将边集扩大一倍后改成加边操作，此时我们有两个思考方向：

## 1.二分

### subtask 3 $i\in(1,q),l_i=1$

考虑到若当前存在可行方案，加上一条边后依然可行，这启示我们这个问题是具有单调性的。不妨以右端点排序后二分，可以暴力跑二分图黑白染色，时间复杂度是 $O(n \log q)$ 的。

### subtask 4 $i\in(1,q),l_i\leq300$

受到上一档部分分的启发，不妨将询问离线，以左端点为依据分组，对于每一个不同的左端点做一遍subtask 3，时间复杂度也是 $O(n \log q)$。

### subtask 5 无特殊性质

观察之前的做法，发现二分的过程是极其相似的，自然地想到整体二分，对于每个 $l_i$，令 $to$ 表示最后一个不是二分图的区间的右端点，设 $(l,r,L,R)$ 表示 $L\leq f_l \leq f_r \leq R$，对于 $mid\in[l,r]$，显然可以分治为 $(l,mid-1,L,ans_{mid})$ 和 $(mid + 1,r,ans_{mid},R)$

求出 $ans_{mid}$ 显然不能从 $mid$ 开始，若 $r+1\leq L-1$ 则保留这一段区间然后扫的时候跳过即可。

此时还有最后一个问题：不能暴力判断二分图了。联想到【模板】线段树分治，使用可撤销扩展域并查集维护。时间复杂度 $O(n \log^2n)$

## 2.LCT

考虑二分做法最后提到的线段树分治，显然在化简完问题后这就是一个线段树分治形式，可以将询问视为时间轴，仿照其做。

但是有一个问题，边在时间轴上的区间不是连续的，我们可以隔一天加一次边将总区间数卡到 $\frac{nq}{2}$ 个，这是不好的。

但是对于这类问题我们还有一个 LCT 做法，同二分思路一样的考虑预处理出 $to$，使用一个双指针，同时维护一个支持删边加边维护最小生成树的 LCT （其中边权为加入时间）就可以快速的预处理出来了。时间复杂度 $O(n \log n + q)$，更为优秀。

## code

此处给出整体二分的代码，在 LOJ 和 CF 上可过。
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 4e5 + 10;
int read(){
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}

int m, n, tot;
int ls[N], rs[N];
int to[N];//每个确定的左端点的最小右端点
int f[N], siz[N];
struct S{int x, y, tim;};
stack<S> s;

inline int find(int x){for(;x!=f[x];x=f[x]);return x;}

void megre(int x, int y){
    y = find(y);
    if(x == y) return ;
    if(siz[x] > siz[y]) swap(x, y);
    f[x] = y;siz[y] += siz[x];
    s.push({x, y, tot});
}

inline bool check(int x, int y){
	tot++;
    int fx = find(x), fy = find(y);
    if(fx == fy) return 1;
    megre(fx, y + n);megre(fy, x + n);
    return 0;
}

inline void goback(){
	for(;s.size() && s.top().tim == tot;s.pop()){f[s.top().x] = s.top().x;siz[s.top().y] -= siz[s.top().x];}
	tot--;
}

void Dinic(int l, int r, int L, int R){
    if(l > r || L > R) return ;
    if(L == R){
        for(; l <= r; l++) to[l] = L;
        return ;
    }
    int mid = l + r >> 1, i, j;
    for(i = mid; i <= R; i++){
        if(i == r + 1) i = max(i, L);
        if(check(ls[i], rs[i])) break;
    }to[mid] = i;
    for(; i >= L && i >= mid; i--){
        if(i == L - 1) i = min(i, r);
        goback();
    }
    Dinic(l, mid - 1, L, to[mid]);for(int i = mid; i <= r && i <= L - 1; i++) goback();
    for(int i = max(r + 1, L); i <= to[mid] - 1; i++) check(ls[i], rs[i]);
    Dinic(mid + 1, r, to[mid], R);for(int i = max(r + 1, L); i <= to[mid] - 1; i++) goback();
}

signed main(){/*
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);*/
	int q,i,l,r;
	n=read();m=read();q=read();
    for(i = 1; i <= m; i++){
        ls[i + m] = ls[i]=read();rs[i + m] = rs[i]=read();
    }
    for(i = 1; i <= 2 * n; i++) f[i] = i, siz[i] = 1;
    ls[m * 2 + 1] = rs[m * 2 + 1] = 1;
    Dinic(1, m + 1, 1, 2 * m + 1);
    while(q--){
        l=read(), r=read();
		puts(to[r+1]<=m+l-1?"YES":"NO");
    }
    return 0;
}
```

## 总结

无论是对于整体二分和线段树分治而言，这都是一道很好的练手题；对于整体二分，可以体验一步步推到整体二分的过程；对于线段树分治，可以熟练并了解更多写法。（但是考场先开 T4 的我就是纯纯小丑了）

---

## 作者：xfrvq (赞：6)

省流：分治、可撤销+扩展域并查集。

---

首先“前缀+后缀”的这个形态有点烦。转化需要技巧：把数组复制一份粘贴在后面，后缀加前缀就是一个连续区间了。

我们定义 $f$ 数组，$f_i$ 是满足 $[i,f_i]$ 有奇环的最小值。看区间 $[L,R]$ 是否有奇环就可以看 $f_L$ 是否 $\ge R$。

然后考虑怎么求出 $f_i$。我们知道 $f_i\ge i$ 且是单调不降的。

这个时候自然的想到双指针，双指针的过程中需要数据结构维护，数据结构需要做加边、删边、查奇环。支持加边和查奇环？trick 我没见过也不会，就被初见杀了。

解法可以使用连反边的扩展域并查集。如果每条边加入时我们都连上反边，如果一条边加入时两个点已经在一个集合而非相反的两个集合，说明产生了奇环（后者是偶环情况）。

但是并查集无法删除任意的一条边。而且当计算的位置 $p\gets p+1$ 时，要被删掉的边 $p$ 是最先加入的边。这下不会了。

然后考虑设计结合值域，设计分治函数来计算。

定义函数 `sol(l,r,vl,vr)`，作用是计算 $f_l,\cdots,f_r$，限制是 $f_l\le\cdots\le f_r$ 在值域区间 $[v_l,v_r]$ 中。

因为不好从值域上入手来计算，所以分治就直接找编号中点 $p=\dfrac{l+r}2$，然后计算其答案，这个答案还是要用数据结构。

因为分治算法，我们认为复杂度必须基于 $l\cdots r$ 和 $v_l\cdots v_r$，因此需要在数据结构里

+ 事先加 $r\cdots v_l$ 的边（如果在分治函数里加就复杂度不对了）。
+ 然后加 $p\cdots r$ 的边。
+ 最后从 $v_l$ 开始一条一条加，加到出现奇环的时候就是答案。

思路是清晰。用什么数据结构维护呢？这个问题不同于上面的双指针。要删除的是最后加的边（$p\cdots r$ 和 $v_l\cdots f_p$），这样与其说是“删除”，不如说是“撤销”。

刚刚说加边和查奇环要用并查集但并查集不能删除。这里是撤销。而并查集可以通过以下来做到可撤销。

+ 去掉路径压缩。这时因为保证不了复杂度，所以加上启发式合并。
+ 每一次合并（`fa[x]=y,siz[y]+=siz[x]`），记录下此时的 $x,y$。
+ 撤销（$\tt undo$）就 `fa[x]=x,siz[y]-=siz[x]` 就行了。

---

事实上分治部分细节不少。

+ 对于 $\mathtt{sol}(l,r,v_l,v_r)$
+ 找到中点 $p=\dfrac{l+r}2$，加入 $p\cdots r$ 的边
+ 从 $v_l$ 开始一条一条加，加到出现奇环时记录为 $f_p$。
+ 撤销上两步操作。
+ 分治：计算 $\mathtt{sol}(l,p-1,v_l,f_p)$
+ 算之前记得把 $[p,v_l)$ 的边加入到并查集，算之后再撤销。
+ 分治：计算 $\mathtt{sol}(p+1,r,f_p,v_r)$
+ 算之前记得把 $(r,f_p)$ 的边加入到并查集，算之后再撤销。
+ 上两步的复杂度你可能疑惑（这不是涉及到了 $r\cdots v_l$ 吗）其实这里面有一部分是已经加了的（$[p,v_l)\cap(r,v_l)$ 和 $(r,f_p)\cap(r,v_l)$），只要加没有加过的部分复杂度就是对的。



---

## 作者：Prean (赞：4)

自己在物理课上编了一道题，大概就是这题把删除区间的边改为保留区间的边。。。~~都不觉得判断短路和判断二分图有点儿像吗~~

题意：给定一张无向图，每次暂时删除一个区间内的边，问删除后这个区间是否为二分图。

首先倍长区间，删除区间变为保留区间。

考虑对每条边 $ i $ 处理一个序列上的一个位置 $ e_i $，表示对原图加入 $ [e_i,i] $ 的边后整张图不是二分图，取最大的 $ e_i $。

很容易能够发现有 $ e_i \leq e_{i+1} $，也就是 $ e_i $ 存在单调性。

左端点单调不递减，考虑使用双指针。

由于判断二分图相当于判断是否存在奇环，而偶环具有传递性（如果有两个偶环，那么套在一起后一定没有奇环），所以考虑使用 LCT 动态维护区间图的一颗生成树。

加入一条边后考虑两件事：

1. 如果加入后产生了奇环，应该删除哪条边？

很明显是令左端点右移，直到没有奇环位置。

2. 如果加入后产生了偶环，应该删掉哪条边？

很明显是偶环上第一个被加入的边。

预处理出 $ e_i $ 之后，就可以通过判断 $ \max_{i=l}^r e_i < l $ 来判断一个区间是否为二分图了。通过 P3901 的 trick，维护前缀 $ \max $ 即可做到 $ O(n\log n+q) $。

---

## 作者：gdf_yhm (赞：3)

[https://www.cnblogs.com/yhddd/p/18408090](https://www.cnblogs.com/yhddd/p/18408090)

[CF1386C](https://www.luogu.com.cn/problem/CF1386C)

[P6684](https://www.luogu.com.cn/problem/P6684)

cf 上时限 $1$ 秒，洛谷 $2$ 秒。

### 思路

维护是否有奇环可用拓展域并查集。暴力复杂度 $O(mq)$。发现插入容易删除困难，用不删除的莫队，可撤销并查集，复杂度 $O((n+q)\sqrt m\log n)$。大概要 $5$ 秒左右，只能过洛谷上的前 $5$ 个子任务。

等价对于每个 $r$ 求最小的 $l$ 使得 $[1,l]$ 和 $[r,m]$ 的边能组成奇环。将边复制一遍接在后面，即对于每个 $i$ 求最小的 $p$ 使得 $[i,p]$ 间的边组成奇环。这里 $p$ 有单调性。依次求每个 $i$，每次右移 $p$，加入的这条边 $p$ 会在求 $[i,p]$ 时都有贡献。插入容易删除困难，用线段树分治。初始没有边，分治到 $i$ 时会对之后一个区间加入若干条边，一共加边 $m$ 次。总复杂度 $O(m\log^2 m)$。

不开 long long 就能过 cf。

### code

```cpp
int n,m,q;
pii g[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<int> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int id){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		tree[nd].pb(id);
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,id);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,id);
}
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
int st[maxn<<5],tp,fl;
void merge(int x,int y){
	int u=fd(x),v=fd(y),uu=fd(x+n),vv=fd(y+n);
	if(u==v){
		fl=1;
		return ;
	}
	if(u!=vv){
		if(siz[u]<siz[vv])swap(u,vv);
		st[++tp]=vv;f[vv]=u,siz[u]+=siz[vv];
		if(siz[v]<siz[uu])swap(v,uu);
		st[++tp]=uu;f[uu]=v,siz[v]+=siz[uu];
	}
}
void del(){
	int u=st[tp];siz[f[u]]-=siz[u],f[u]=u;
	tp--;
}
int ans[maxn];
int p=1;
void dfs(int nd,int l,int r){
	int lst=tp,flag=fl;
	for(int i:tree[nd])merge(g[i].fi,g[i].se);
	if(l==r){
		while(p<=2*m&&!fl){
			merge(g[p].fi,g[p].se);
			updata(1,1,m+1,l+1,min(p,m+1),p);
			p++;
		}
		if(!fl)ans[l]=p;
		else ans[l]=p-1;
	}
	else dfs(ls,l,mid),dfs(rs,mid+1,r);
	while(tp>lst)del();
	fl=flag;
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++)g[i]={read(),read()},g[i+m]=g[i];
	for(int i=1;i<=2*n;i++)f[i]=i,siz[i]=1;
	dfs(1,1,m+1);
	while(q--){
		int l=read(),r=read();
		if(ans[r+1]<=m+l-1)puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：鱼跃于渊 (赞：1)

一道神仙整体二分题。  

# 做法  

每次询问会禁用 $[l,r]$ 之间的边，也就是说只能用 $[1,l-1]\cup [r+1,n]$ 之间的边。  
感觉这个看起来不太好搞，我们可以把边复制一遍，这样我们就可以看作是只能用 $[r+1,l+m-1]$ 之间的边。  

考虑暴力怎么做。  
首先一张图不存在奇环的充要条件是该图为二分图，而判断图是否为二分图可以用扩展域并查集解决。  
也就是说我们对于每次询问，把 $[r+1,l+m-1]$ 之间的边加入并查集中，判断即可。  
这样子时间复杂度是 $O(m^2)$ 的，期望得分 $14$ 分。  

我们思考部分分，可以发现如果左端点 $l$ 是固定的，可以通过二分求出最靠右的 $r$，使得 $[l,r]$ 之间的边组成二分图。我们记这个位置为 $f_l$。  
对于部分分我们可以二分求解每个 $f_l$，期望得分 $49$ 分。  

接下来我们很容易从分别二分求解想到一起二分求解——整体二分。  
具体而言，整体二分 $(l,r,L,R)$，其中 $[l,r]$ 是值域，$[L,R]$ 是操作域。  
我们令 $mid\gets \lfloor \frac{L+R}{2}\rfloor$，求出 $f_{mid}$，然后分成 $(l,f_{mid},L,mid-1)$ 和 $(f_{mid},r,mid+1,R)$ 两个子问题。  
不过发现一个问题，如果我们每次都是暴力判断二分图，时间复杂度是 $O(n^2\log^2 n)$ 的，显然过不去。  
考虑使用可撤销并查集，然后在整体二分 $(l,r,L,R)$ 时保留重复的区间 $[R,l]$ 即可。  
时间复杂度 $O(n\log^2n)$，期望得分 $100$ 分。  

# 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
const int N=4e5+5;
struct edge{
	int u,v,tm;
}e[N];
int n,m,q,ti;
int fg[N];
int fa[N],siz[N];
stack <edge> st;
int find(int x){
	return x==fa[x]?x:find(fa[x]);
}
void join(int x,int y){
	x=find(x);y=find(y);
	if(x==y) return;
	if(siz[x]>siz[y]) swap(x,y);
	fa[x]=y;siz[y]+=siz[x];
	st.push({x,y,ti});
}
bool merge(edge tp){
	ti++;
	int fx=find(tp.u),fy=find(tp.v);
	if(fx==fy) return 1;
	join(fx,tp.v+n);join(fy,tp.u+n);
	return 0;
}
void split(){
	for(edge tp;!st.empty()&&st.top().tm==ti;st.pop()){
		tp=st.top();
		fa[tp.u]=tp.u;
		siz[tp.v]-=siz[tp.u];
	}
	ti--;
}
void solve(int l,int r,int L,int R){
	if(l>r||L>R) return;
	if(l==r){
		per(i,L,R) fg[i]=l;
		return;
	}
	int p,mid=(L+R)>>1;
	for(p=mid;p<=r;p++){
		if(p==R+1) p=max(p,l);
		if(merge(e[p])) break;
	}
	fg[mid]=p;
	for(;p>=max(l,mid);p--){
		if(p==l-1) p=min(p,R);
		split();
	}
	solve(l,fg[mid],L,mid-1);
	per(i,mid,min(R,l-1)) split();
	per(i,max(R+1,l),fg[mid]-1) merge(e[i]);
	solve(fg[mid],r,mid+1,R);
	per(i,max(R+1,l),fg[mid]-1) split();
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[i]=e[i+m]={u,v,i};
	}
	e[m*2+1]={1,1,m+1};
	iota(fa+1,fa+n*2+1,1);
	fill(siz+1,siz+n*2+1,1);
	solve(1,m*2+1,1,m+1);
	for(int i=1,l,r;i<=q;i++){
		cin>>l>>r;
		cout<<(fg[r+1]<=l+m-1?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：Cx114514 (赞：0)

### 题目链接：[[BalticOI 2020 Day1] 小丑](https://www.luogu.com.cn/problem/P6684) / [Joker](https://www.luogu.com.cn/problem/CF1386C)
考虑将整个边的序列复制粘贴一遍，放在原序列的右侧。

这样，删除一个区间 $\left[l,r\right]$ 可以看作保留 $\left[r+1,n+l-1\right]$。

令 $R_i$ 表示以 $i$ 为左端点，右端点最左是多少才能使得这一个区间中的边组成一个奇环。

只要我们求出了所有的 $R$，对于每次查询，我们都可以 $O\left(1\right)$ 求解。

不难发现，$R$ 满足单调性，考虑整体二分。

令整体二分函数为 $solve\left(l,r,tl,tr\right)$，表示当前考虑左端点在 $\left[l,r\right]$ 中的情况，其 $R$ 的可能值在 $\left[tl,tr\right]$ 中。

在整体二分时，我们每次求出 $R_{mid}$，则函数可分解为 $solve\left(l,mid-1,tl,R_{mid}\right)$ 和 $solve\left(mid+1,r,R_{mid},tr\right)$。

问：如何求出 $R_{mid}$。

答：从 $mid$ 开始向后一直加边，用可撤销扩展域并查集维护，如果不会的话可以看 [[NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)。

但是，直接这么做的话复杂度冗余会很大。

当 $r\le tl$ 时，我们可以直接保留 $\left[r,tl\right]$，避免重复计算。

时间复杂度 $O\left(n\log^2 n\right)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int read()
{
	int f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
	    if (c == '-') f = -1;
	    c = getchar();
    }
	int x = 0;
	while (isdigit(c))
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int buf[25];

void write(long long x)
{
	int p = 0;
	if (x < 0)
	{
	    putchar('-');
	    x = -x;
	}
	if (x == 0) putchar('0');
	else
	{
		while (x)
		{
			buf[++p] = x % 10;
			x /= 10;
		}
		for (int i = p; i >= 1; i--)
			putchar('0' + buf[i]);
	}
}

int n, m, q, cnt, fa[400005], u[400005], v[400005], R[400005], sz[400005];

struct node
{
	int x, y, num;
};

stack < node > s;

int search(int x)
{
	if (fa[x] == x) return x;
	return search(fa[x]);
}

void _merge(int x, int y)
{
	x = search(x);
	y = search(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
	s.push({x, y, cnt});
}

int merge(int x, int y)
{
	cnt++;
	int xx = search(x);
	int yy = search(y);
	if (xx == yy) return 1;
	_merge(xx, y + n);
	_merge(x + n, yy);
	return 0;
}

void undo()
{
	if (s.empty())
	{
		cnt--;
		return;
	}
	node t = s.top();
	while (t.num == cnt)
	{
		s.pop();
		fa[t.y] = t.y;
		sz[t.x] -= sz[t.y];	
		if (s.empty()) break;
		t = s.top();
	}
	cnt--;
}

void solve(int l, int r, int tl, int tr)
{
	if (l > r || tl > tr) return;
	if (tl == tr)
	{
		for (int i = l; i <= r; i++)
			R[i] = tl;
		return;
	}
	int mid = (l + r) / 2;
	int t;
	for (t = mid; t <= tr; t++)
	{
		if (t == r + 1) t = max(t, tl);
		if (merge(u[t], v[t])) break;
	}
	R[mid] = t;
	for (; t >= tl && t >= mid; t--)
	{
		if (t == tl) t = min(t, r);
		undo();
	}
	solve(l, mid - 1, tl, R[mid]);
	for (t = mid; t <= r && t < tl; t++)
		undo();
	for (t = max(r + 1, tl); t <= R[mid] - 1; t++)
		merge(u[t], v[t]);
	solve(mid + 1, r, R[mid], tr);
	for (t = max(r + 1, tl); t <= R[mid] - 1; t++)
		undo();
}

int main()
{
	n = read(), m = read(), q = read();
	for (int i = 1; i <= 2 * n; i++)
	{
		fa[i] = i;
		sz[i] = 1;
	}
	for (int i = 1; i <= m; i++)
	{
		u[i] = read(), v[i] = read();
		u[i + m] = u[i];
		v[i + m] = v[i];
	}
	u[2 * m + 1] = v[2 * m + 1] = 1;
	solve(1, m + 1, 1, 2 * m + 1);	
	while (q--)
	{
		int l, r;
		l = read(), r = read();
		if (R[r + 1] <= m + l - 1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

前缀加后缀是序列拼接后的一段区间。考虑倍长序列后对于每个 $l$ 求出 $c_l$ 表示最小的 $r$ 使得 $[l,r]$ 区间的边连完后有奇环。那么可以 $O(1)$ 查询。

容易知道 $c$ 单调，但是双指针做不了删除。直接想法是考虑回滚莫队，但是并查集需要撤销所以带个 $\log$ 的复杂度。总复杂度 $O(n\sqrt{n} \log n)$，时限很紧不太能过。

考虑整体二分，具体地对于 $[l,r,L,R]$，表示现在求 $[l,r]$ 答案，且答案必然在值域 $[L,R]$ 内。$L=R$ 时是终点，否则 $mid=\lfloor \dfrac{l+r}{2} \rfloor$，然后我们求出 $c_{mid}$ 并递归到两边。问题是求的时候显然不能暴力拓展，考虑类似线段树分治的东西，每次进入区间前保留 $[r,L)$ 的并查集就可以快速进行操作。总复杂度 $O(n\log^2n+q)$。

代码：


```cpp
// LUOGU_RID: 168323601
// LUOGU_RID: 168316103
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ranges>
#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int N = 4e5 + 5;

int n, m, q;
int u[N], v[N], cr[N];

class Dsu
{
public:
	int fa[N], sz[N];
	void Init()
	{
		for (int i = 1; i < N; i++) fa[i] = i, sz[i] = 1;
	}
	int find(int u)
	{
		return (fa[u] == u ? u : find(fa[u]));
	}
	auto merge(int u, int v)
	{
		if ((u = find(u)) == (v = find(v))) return make_pair(-1, -1);
		if (sz[u] < sz[v]) swap(u, v);
		fa[v] = u, sz[u] += sz[v];
		return make_pair(u, v);
	}
	void rollback(auto x)
	{
		if (x.first == -1) return;
		fa[x.second] = x.second, sz[x.first] -= sz[x.second];
	}
}dsu;

void solve(int l, int r, int L, int R)
{
	//[r,L)的边已经被加入了
	if (L == R)
	{
		for (int i = l; i <= r; i++) cr[i] = L;
		return;
	}
	int mid = l + r >> 1;
	vector<pair<int, int>> e;
	bool flag = 0;
	for (int i = mid; i < r; i++)
	{
		e.emplace_back(dsu.merge(u[i], v[i] + n));
		e.emplace_back(dsu.merge(u[i] + n, v[i]));
		flag |= (dsu.find(u[i]) == dsu.find(u[i] + n));
		flag |= (dsu.find(v[i]) == dsu.find(v[i] + n));
		if (flag)
		{
			cr[mid] = i;
			break;
		}
	}
	if (!flag)
	{
		for (int i = max(L, r);; i++)
		{
			if (flag)
			{
				cr[mid] = i - 1;
				break;
			}
			e.emplace_back(dsu.merge(u[i], v[i] + n));
			e.emplace_back(dsu.merge(u[i] + n, v[i]));
			flag |= (dsu.find(u[i]) == dsu.find(u[i] + n));
			flag |= (dsu.find(v[i]) == dsu.find(v[i] + n));
		}
	}
	for (auto& x : e | views::reverse)
	{
		dsu.rollback(x);
	}
	e.clear(), e.shrink_to_fit();
	if (L <= r)
	{
		for (int i = mid - 1; i < L; i++)
		{
			e.emplace_back(dsu.merge(u[i], v[i] + n));
			e.emplace_back(dsu.merge(u[i] + n, v[i]));
		}
	}
	else
	{
		for (int i = mid - 1; i < r; i++)
		{
			e.emplace_back(dsu.merge(u[i], v[i] + n));
			e.emplace_back(dsu.merge(u[i] + n, v[i]));
		}
	}
	if (l != mid) solve(l, mid - 1, L, cr[mid]);
	for (auto& x : e | views::reverse)
	{
		dsu.rollback(x);
	}
	e.clear(), e.shrink_to_fit();
	for (int i = max(L, r); i < cr[mid]; i++)
	{
		e.emplace_back(dsu.merge(u[i], v[i] + n));
		e.emplace_back(dsu.merge(u[i] + n, v[i]));
	}
	if (mid != r) solve(mid + 1, r, cr[mid], R);
	for (auto& x : e | views::reverse)
	{
		dsu.rollback(x);
	}
	e.clear(), e.shrink_to_fit();
}

namespace FastIo
{
	char buf[1 << 20], * p1, * p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
	int read()
	{
		char ch = getchar();
		int x = 0;
		while (ch < '0' || ch > '9') ch = getchar();
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

int main()
{
	dsu.Init();
	n = FastIo::read(), m = FastIo::read(), q = FastIo::read();
	for (int i = 1; i <= m; i++)
	{
		u[i] = FastIo::read(), v[i] = FastIo::read();
		u[i + m] = u[i], v[i + m] = v[i];
	}
	solve(1, 2 * m, 1, 2 * m);
	while (q--)
	{
		int l, r;
		l = FastIo::read(), r = FastIo::read();
		if (cr[r + 1] <= l + m - 1) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

