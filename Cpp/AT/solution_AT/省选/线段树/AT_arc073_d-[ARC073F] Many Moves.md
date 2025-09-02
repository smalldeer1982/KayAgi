# [ARC073F] Many Moves

## 题目描述

## 题意

在一行中有$n$个格子，从左往右编号为$1$到$n$。

有$2$颗棋子，一开始分别位于位置$A$和$B$。按顺序给出$Q$个要求，每个要求是如下形式：

- 给出一个位置$x_i$，要求将两个棋子中任意一个移动到位置$x_i$。

将一颗棋子移动一格需要花费$1$秒，就是说将棋子从$X$位置移动到$Y$位置需要花费$|X-Y|$秒。

为了回答要求，你只能移动棋子，并且同一时刻只能移动一颗棋子。要求的顺序是不可更改的。在同一时间允许两颗棋子在同一个格子内。

## 样例 #1

### 输入

```
8 3 1 8
3 5 1```

### 输出

```
7```

## 样例 #2

### 输入

```
9 2 1 9
5 1```

### 输出

```
4```

## 样例 #3

### 输入

```
9 2 1 9
5 9```

### 输出

```
4```

## 样例 #4

### 输入

```
11 16 8 1
1 1 5 1 11 4 5 2 5 3 3 3 5 5 6 7```

### 输出

```
21```

# 题解

## 作者：ywy_c_asm (赞：12)

这里的dp状态和另一篇题解的似乎不太一样，但是都用了线段树优化dp……

首先最无脑的暴力就是$dp[i][a][b]$表示处理完i个操作之后这两个棋子的位置分别在a和b的最小代价，这个大概是$O(n^3)$~$O(n^4)$的。

然后一个很显然的优化就是进行完i操作之后**一定会有一个棋子在$x_i$位置**，那么我们可以把这个状态改为$dp[i][j]$表示前i个操作，不在$x_i$的那个棋子在$j$的最小代价。

然后我想到这了之后觉得这也是暴力就扔到一边了，但是我们仔细讨论一下这个的转移情况之后就会——

①$j\not=x_{i-1}$，那么显然这个在j的棋子在上一步也没有移动，这一步移动到$x_i$的棋子在上一步的时候一定在$x_{i-1}$，所以就是$dp[i-1][j]+|x_i-x_{i-1}|$。

②$j=x_{i-1}$，当然这个也可以用①的转移，但是这就多了一种情况即上一步不是$x_{i-1}$的棋子在这一步移到了$x_i$，我们枚举这个棋子上一步在什么位置即$min\{dp[i-1][k]+|x_i-k|\}$，然后根据套路我们讨论k把这个绝对值拆开，即$k<=x_i$时为$min\{dp[i-1][k]-k\}+x_i$，$k>=x_i$时为$min\{dp[i-1][k]+k\}-x_i$。

于是一切就都很显然了，我们把这个二维状态的dp放到线段树上像滚动数组一样滚动就行了，那么转移②就在线段树上维护区间内最小的$dp[k]+k$与$dp[k]-k$（这里的dp把第一维省略了，第二维是线段树的下标）然后在区间上查，转移①在线段树上打标记即可。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define ls(_o) (_o << 1)
#define rs(_o) ((_o << 1) | 1)
#define abs(_o) ((_o < 0) ? -(_o) : _o)
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	ll min1[1000001], min2[1000001], adds[1000001];
	int x[200001];
	inline void down(int tree) {
	    if (!adds[tree])
	        return;
	    ll c = adds[tree];
	    adds[tree] = 0;
	    adds[ls(tree)] += c;
	    adds[rs(tree)] += c;
	    min1[ls(tree)] += c;
	    min2[ls(tree)] += c;
	    min1[rs(tree)] += c;
	    min2[rs(tree)] += c;
	}
	inline void up(int tree) {
	    min1[tree] = min(min1[ls(tree)], min1[rs(tree)]);
	    min2[tree] = min(min2[ls(tree)], min2[rs(tree)]);
	}
	void setpt(int l, int r, int tree, int pt, ll num) {
	    if (l == r) {
	        min1[tree] = min(min1[tree], num - l);
	        min2[tree] = min(min2[tree], num + l);
	        return;
	    }
	    int mid = (l + r) >> 1;
	    down(tree);
	    if (pt <= mid)
	        setpt(l, mid, ls(tree), pt, num);
	    else
	        setpt(mid + 1, r, rs(tree), pt, num);
	    up(tree);
	}
	ll query1(int rl, int rr, int l, int r, int tree) {
	    if (rl == l && rr == r)
	        return (min1[tree]);
	    int mid = (l + r) >> 1;
	    down(tree);
	    if (rl > mid)
	        return (query1(rl, rr, mid + 1, r, rs(tree)));
	    if (rr <= mid)
	        return (query1(rl, rr, l, mid, ls(tree)));
	    return (min(query1(rl, mid, l, mid, ls(tree)), query1(mid + 1, rr, mid + 1, r, rs(tree))));
	}
	ll query2(int rl, int rr, int l, int r, int tree) {
	    if (rl == l && rr == r)
	        return (min2[tree]);
	    int mid = (l + r) >> 1;
	    down(tree);
	    if (rl > mid)
	        return (query2(rl, rr, mid + 1, r, rs(tree)));
	    if (rr <= mid)
	        return (query2(rl, rr, l, mid, ls(tree)));
	    return (min(query2(rl, mid, l, mid, ls(tree)), query2(mid + 1, rr, mid + 1, r, rs(tree))));
	}
	ll query(int l, int r, int tree) {
	    if (l == r)
	        return (min1[tree] + l);
	    int mid = (l + r) >> 1;
	    down(tree);
	    return (min(query(l, mid, ls(tree)), query(mid + 1, r, rs(tree))));
	}
	void ywymain() {
	    int n = get(), q = get(), a = get(), b = get();
	    x[0] = a;
	    memset(min1, 0x3f, sizeof(min1));
	    memset(min2, 0x3f, sizeof(min2));
	    setpt(1, n, 1, b, 0);
	    for (register int i = 1; i <= q; i++) {
	        x[i] = get();
	        ll cjr = min(query1(1, x[i], 1, n, 1) + x[i], query2(x[i], n, 1, n, 1) - x[i]);
	        adds[1] += abs(x[i] - x[i - 1]);
	        min1[1] += abs(x[i] - x[i - 1]);
	        min2[1] += abs(x[i] - x[i - 1]);
	        setpt(1, n, 1, x[i - 1], cjr);
	    }
	    cout << query(1, n, 1) << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}

```

---

## 作者：Zxsoul (赞：11)

**题目简化**

- 给出两个位置，并给出 $Q$ 个询问，要求任意移动其中一个的位置到指定位置，时间消耗就是移动的距离，问最小的完成问题的时间

朴素的DP $i$ 记录次数，其中有一个棋子一定在 $x_i$ 的位置上， 所以我们只需要记录另一个位置在哪
$$
f_{i,j}+abs(x_i-x_{i+1})\to f_{i+1,j}
\\ \min\{f_{i,j}+abs(j-x_{i+1})\}\to f_{i+1,x_i}
$$
注意上面最后一个是 $x_i$ 而不是 $x_{i+1}$ 因为第二维记录的是不是当前位置的位置。

首先**混动数组优化空间**，然后再观察柿子的性质：

对于第一个转移，不难发现，混动后，是对整个区间修改同一个定值。

对于第二个转移，无论 $j$ 的位置，改变的只有 $x_{i+1}$，也就是快速维护这个的最小值。

我们用扫描线的思想，线段树记录 $j$ ，$i$ 做时间线。

- 对于第一个操作，区间修改就好。
- 对于第二个操作，找到区间最小值，单点修改就好。

所以貌似是区间修改和单点修改？

对于第二类操作求最值，可以把绝对值拆开，然后求两个区间的最小值，最后合并就好。    

注意开 `ll`，时间复杂度 $O(n+Q\log n)$

**几个坑点**

- 因为滚掉了一维，所以必须保证转移的 $dp$ 数组是上一维的。
- 根据转移方程可知，在一次转移时，可能更改一个位置两次，这时需要保留最小值，具体实现是在线段树修改时取 `min`

第一次做到线段树优化 dp，转移上调了好久。

```c
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;
#define int long long
#define root 1,n,1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int B=2e5+10;
const int inf=0x3f3f3f3f;
int read()
{
	int x=0,ch=getchar();
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x;
} 
struct node
{
	int l,r,sum,col;
	int minx1,minx2;
	node() {l=r=sum=col=0,minx1=minx2=inf;}
	void init(int l_,int r_) {l=l_,r=r_,sum=0,minx1=inf,minx2=inf;}
}z[B<<2];
int n,M,s,t;
node operator +(const node &l,const node &r)
{
	node p;
	p.l=l.l,p.r=r.r,p.minx1=min(l.minx1,r.minx1), p.minx2=min(l.minx2,r.minx2);
	p.col=0;
	return p; 
} 
void update(int rt) { z[rt]=z[rt<<1]+z[rt<<1|1];}
void color(int rt,int v) {z[rt].col+=v;z[rt].minx1+=v, z[rt].minx2+=v; return;}
void push(int rt) {if (z[rt].col) {color(rt<<1,z[rt].col); color(rt<<1|1,z[rt].col); z[rt].col=0;} }
void build(int l,int r,int rt) 
{
	if (l==r) {z[rt].init(l,r);return;} 
	int m=l+r>>1; 
	build(lson); build(rson); 
	update(rt);
}
void modify(int l,int r,int rt,int nowl,int nowr,int v)	
{
	if (nowl<=l && r<=nowr) {color(rt,v);return;}
}//区间操作
void one_modify(int l,int r,int rt,int x,int v)
{
	if (l==r) {z[rt].minx1=min(z[rt].minx1,v+x); z[rt].minx2=min(z[rt].minx2,v-x);return;}
	int m=l+r>>1; push(rt); 
	if (x<=m) one_modify(lson,x,v);
	else if (m<x) one_modify(rson,x,v);
	update(rt); 
} 
node query(int l,int r,int rt,int nowl,int nowr)
{
	if (nowl<=l && r<=nowr) return z[rt];
	int m=l+r>>1;
	push(rt);
	if (nowl<=m)
	{
		if (m<nowr) return query(lson,nowl,nowr)+query(rson,nowl,nowr);
		return query(lson,nowl,nowr); 
	}
	return query(rson,nowl,nowr);
} 
int All_query(int l,int r,int rt,int nowl,int nowr)
{
	if (l==r) return z[rt].minx1-z[rt].l;
	int m=l+r>>1;
	push(rt);
	if (nowl<=m)
	{
		if (m<nowr) return min(All_query(lson,nowl,nowr),All_query(rson,nowl,nowr));
		return All_query(lson,nowl,nowr); 
	}
	return All_query(rson,nowl,nowr);
}
int m;
int x[B];
signed main()
{
	n=read(),M=read(),s=read(),t=read();
	build(root);
	x[0]=s; one_modify(root,t,0);
	for (int i=1;i<=M;i++)
	{
		x[i]=read();
		int fail=query(root,x[i],n).minx1-x[i];
		int bef	=query(root,1,x[i]).minx2+x[i];//得到两个的最小值
		fail=min(fail,bef);
		modify(root,1,n,abs(x[i]-x[i-1]));
		one_modify(root,x[i-1],fail); 
	}
	printf("%lld\n",All_query(root,1,n));
	
}
```
希望通过，蟹蟹。

---

## 作者：Saliеri (赞：6)

奇怪的做法。

设 $dp_{i,j}$ 表示满足前 $i$ 个限制过后，一个在 $x_i$，另一个在 $j$ 的答案。

转移：$dp_{i,j} = \min(dp_{i-1,j}+|x_{i-1}-x_i|,\min_k(dp_{i-1,k}+|k-x_{i}|)+|j-x_{i-1}|)$。

将 $dp_{i,j}$ 考虑为关于 $j$ 的函数，则转移对应两个操作：

- 原图像向上平移 $|x_{i-1}-x_i|$ 个单位；
- 将图像与以 $(x_{i-1},\min_k(dp_{i-1,k}+|k-x_{i}|))$ 为顶点的 V 形绝对值函数对位取 min。

可以发现，这样转移得到的任意 $dp_{i}$ 都是一条斜率交替为 $\pm 1$ 的折线。

考虑 $\min_k(dp_{i-1,k}+|k-x_{i}|)$ 如何快速求解。因为 $dp_i$ 的斜率的绝对值为 1，因此使得 $k$ 向 $x_{i-1}$ 靠近必然不劣，即 $\min_k(dp_{i-1,k}+|k-x_{i}|) = dp_{i-1,x_{i}}$。

我们采用 `std::set` 维护这个折线的所有 "谷"，所有操作都可以完成。时间复杂度均摊 $O(n\log n)$。

```cpp
#include <set>
#include <cstdio>
namespace HyjMh{
	const int maxn = 2e5+5;
	typedef long long ll;
	int abs(int x){return x<0?-x:x;}
	ll min(ll a,ll b){return a<b?a:b;}
	struct pt{int x;ll y;bool operator <(pt b)const{return x<b.x;}};
	typedef std::set<pt>::iterator it; 
	int pipidashik,n,A,B,x[maxn];ll tgy;std :: set<pt> zzg;//zigzag
	ll Val(int p){
		it i = zzg.lower_bound({p,0});ll r = 1e18;
		if(i != zzg.end())r = min(r,i->y+i->x-p);
		if(i != zzg.begin())--i,r = min(r,i->y+p-i->x);
		return r+tgy;
	}
	void Ins(pt p){
		p.y -= tgy;
		it i = zzg.lower_bound(p),l,r;r = l = i;
		if(l != zzg.begin()){
			--l;while(l->y>=p.y+abs(l->x-p.x))
				{i = l;if(l == zzg.begin()){zzg.erase(i);break;}else --l,zzg.erase(i);}
		}
		while(r != zzg.end() && r->y>=p.y+abs(r->x-p.x))i = r,++r,zzg.erase(i);
		zzg.insert(p);
	}
	int main(){
		scanf("%d %d %d %d",&pipidashik,&n,&A,&B);
		for(int i=1;i<=n;++i)scanf("%d",&x[i]);
		zzg.insert({B,abs(A-x[1])});Ins({A,abs(B-x[1])});
		for(int i=2,dlt;i<=n;++i)
			if(x[i] != x[i-1])dlt = abs(x[i]-x[i-1]),tgy += dlt,Ins({x[i-1],Val(x[i])-dlt});
		ll ans = 1e18;for(pt p:zzg)ans = min(ans,p.y);
		return printf("%lld\n",ans+tgy),0;
	}
}
int main(){return HyjMh::main();}
```

---

## 作者：lytqwq (赞：4)

### 暴力：

设 $f_{i,j}$ $(i>j)$ 表示一个棋子在第 $i$ 次要求的位置， 另一个棋子在 位置 $j$ 。

有状态转移方程 。


$$
f_{i,j}=f_{i-1,j}+|wz_i-wz_{i-1}|

$$

特别的，当 $j=wz_{i-1}$ 时，有 ：

$$
f_{i,j}=\min{f_{i-1,k}+|wz_i-k|} 
$$

我们暴力 $dp$ ，时间复杂度 $O(n^2)$ 。

### 正解：

观察前面的状态转移方程，我们发现，第一个式子很简单，第二个式子只有 $n$ 个 $f$ 会这么更新，所以：

我们开一个线段树，保存当前 $f_i$ ，

每次到第 $i$ 次移动，

 第 $wz_{i-1}$ 个位置应该更新到 $ \min{f_{i-1,k}+|wz_i-k|} $  。
 
绝对值我们可以分类讨论，分成 $wz_i$ 前面的 和 后面的 。

其他所有位置 $+ |wz_i-wz_{i-1}| $ 。


我们写个区间加区间求最小值，这里我写了个 $f_{i,j}+j$ 和 $f_{i,j}+n-j$的两个最小值（因为前面绝对值的分类讨论）。



时间复杂度 $O(nlogn)$ 。


代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long int N=200010,inf=1e12;
long long int n,Q,A,B,x[N];
long long int ans1[N<<2],ans2[N<<2],tag[N<<2];
long long int ls(long long int x){return x<<1;}
long long int rs(long long int x){return x<<1|1;}
void push_up(long long int p){
	ans1[p]=min(ans1[ls(p)],ans1[rs(p)]);
	ans2[p]=min(ans2[ls(p)],ans2[rs(p)]);
}
void f(long long int p,long long int l,long long int r,long long int k){
	ans1[p]+=k;
	ans2[p]+=k;
	tag[p]+=k;
}
void push_down(long long int p,long long int l,long long int r){
	long long int mid=(l+r)>>1;
	f(ls(p),l,mid,tag[p]);
	f(rs(p),mid+1,r,tag[p]);
	tag[p]=0;
}
void build(long long int p,long long int l,long long int r){
	if(l==r){
		ans1[p]=ans2[p]=inf;
		if(l==B){
			ans1[p]=l;ans2[p]=n-l;
		}
		return ;
	}
	long long int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	push_up(p);
}
void update(long long int p,long long int nl,long long int nr,long long int l,long long int r,long long int k){
	if(nl>nr)return ;
	if(nl<=l&&r<=nr){
		f(p,l,r,k);
		return ;
	}
	push_down(p,l,r);
	long long int mid=(l+r)>>1;
	if(nl<=mid)update(ls(p),nl,nr,l,mid,k);
	if(mid+1<=nr)update(rs(p),nl,nr,mid+1,r,k);
	push_up(p);
}
void update2(long long int p,long long int nn,long long int l,long long int r,long long int k){
	if(l==r){
		ans1[p]=k+l;ans2[p]=k+n-l;
		return ;
	}
	push_down(p,l,r);
	long long int mid=(l+r)>>1;
	if(nn<=mid)update2(ls(p),nn,l,mid,k);
	if(mid+1<=nn)update2(rs(p),nn,mid+1,r,k);
	push_up(p);
}
long long int query(long long int p,long long int nl,long long int nr,long long int l,long long int r,long long int flag){
	if(nl>nr)return inf;
	long long int ans=inf;
	if(nl<=l&&r<=nr){
		if(flag==1)return ans1[p];
		else return ans2[p];
	}
	push_down(p,l,r);
	long long int mid=(l+r)>>1;
	if(nl<=mid)ans=min(ans,query(ls(p),nl,nr,l,mid,flag));
	if(mid+1<=nr)ans=min(ans,query(rs(p),nl,nr,mid+1,r,flag));
	push_up(p);
	return ans;
}
long long int findans(long long int p,long long int l,long long int r){
	if(l==r)return ans1[p]-l;
	long long int mid=(l+r)>>1;
	push_down(p,l,r);
	return min(findans(ls(p),l,mid),findans(rs(p),mid+1,r));
}
int main(){
	scanf("%lld%lld%lld%lld",&n,&Q,&A,&B);
	for(long long int i=1;i<=Q;i++){
		scanf("%lld",&x[i]);
	}
	build(1,1,n);
	x[0]=A;
	for(long long int i=1;i<=Q;i++){
		long long int min1=query(1,1,x[i],1,n,2)-(n-x[i]);
		long long int min2=query(1,x[i],n,1,n,1)-x[i];
		update(1,1,n,1,n,abs(x[i]-x[i-1]));
		update2(1,x[i-1],1,n,min(min1,min2));
	}
	printf("%lld\n",findans(1,1,n));
}
```



~~你们知道我快省选了，线段树到现在还忘开四倍数组的绝望吗~~






---

## 作者：Ebola (赞：4)

考虑dp。设f\[i\]表示一个棋子位于i，另一个棋子位于i-1时的最小代价，然后不难列出n²的dp转移方程：

$$f_{i}=\min\limits_{j=1}^{i-1}\left(f_j+\sum\limits_{k=j+1}^{i-1}\Delta_k+|x_i-x_{j-1}|\right)$$

其中$\Delta_k=|x_k-x_{k-1}|$

于是我们可以求出$\Delta_k$的前缀和$sum$，然后式子可以化为：

$$f_{i}=\min\limits_{j=1}^{i-1}\left(f_j-sum_j+|x_i-x_{j-1}|\right)+sum_{i-1}$$

区间最小值这种东西，用线段树搞搞就好了。但有个绝对值，所以我们要维护两颗线段树，一棵存$f_j-sum_j-x_{j-1}$，另一棵存$f_j-sum_j+x_{j-1}$，然后以x的值为下标，这样对于每个i，我们只要在线段树一的\[1, xi\]中查找最小值，找到最小值加上xi+sum\[i-1\]，在线段树二中的查找也是类似的

然后初值有点麻烦，我的做法是设x0=a，然后f\[1\]=|b-x1|，再按上面说的去做。但这样涉及到a和b选哪个的问题，所以要跑完一遍后交换a和b再跑一遍取最小值才行

```cpp
#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef long long LL;
const int N=200010;
int n,q,a,b,X[N];
int delta[N];
LL sumd[N],f[N];

struct SegmentTree
{
    LL mnv[N<<2];int leaf;
    void build()
    {
        for(leaf=1;leaf<=(n+2);leaf<<=1);
        for(int i=1;i<=leaf+n;i++) mnv[i]=INT64_MAX/3;
    }
    void modify(int k,LL x)
    {
        mnv[leaf+k]=min(mnv[leaf+k],x);
        for(int i=(leaf+k)>>1;i;i>>=1)
            mnv[i]=min(mnv[i<<1],mnv[i<<1|1]);
    }
    LL qmin(int l,int r)
    {
        LL res=INT64_MAX/3;
        for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
        {
            if(~l&1) res=min(res,mnv[l^1]);
            if(r&1) res=min(res,mnv[r^1]);
        }
        return res;
    }
}t1,t2;

LL solve(int a,int b)
{
    X[0]=a;
    for(int i=1;i<=q;i++)
    {
        delta[i]=abs(X[i]-X[i-1]);
        sumd[i]=sumd[i-1]+delta[i];
    }
    f[1]=abs(b-X[1]);
    t1.build();t2.build();
    t1.modify(X[0],f[1]-sumd[1]-X[0]);
    t2.modify(X[0],f[1]-sumd[1]+X[0]);
    for(int i=2;i<=q;i++)
    {
        f[i]=t1.qmin(1,X[i])+X[i]+sumd[i-1];
        f[i]=min(f[i],t2.qmin(X[i],n)-X[i]+sumd[i-1]);
        t1.modify(X[i-1],f[i]-sumd[i]-X[i-1]);
        t2.modify(X[i-1],f[i]-sumd[i]+X[i-1]);
    }
    LL ans=INT64_MAX/3;
    for(int i=0;i<=q;i++) ans=min(ans,f[i]+sumd[q]-sumd[i]);
    return ans;
}

int main()
{
    n=read();q=read();a=read();b=read();
    for(int i=1;i<=q;i++) X[i]=read();
    LL ans=min(solve(a,b),solve(b,a));
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：Dita (赞：3)

[题面](https://www.luogu.com.cn/problem/AT2558)

线段树优化 dp 转移。

**solution**

dp 状态肯定是要设两个点的位置

因为在第 $i$ 次操作之后，一定有一个点会在 $x_i$，所以只需要设另一个点的位置就好。

$f_{i,j}$ 表示执行了 $i$ 次操作，两个点的分别在 $x_i$  和 $j$ 的最小代价。

**转移：**

$f_{i, j} = f_{i - 1, j} + |x_i - x_{i - 1}|$ 

$f_{i, x_{i - 1}} = \min\{f_{i - 1, j} + |j - x_{i}|\}$

**优化：**

把二维状态放在线段树上滚掉一维。

以 $j$ 为下标，$f_j$ 为权值建一棵线段树，对于第一个操作就是全局加 $|x_i - x_{i + 1}|$。 

对于第二个操作，首先它也可以按照第一个式子转移，应该很显然。

对于第二个式子，我们分类讨论把绝对值拆开，就成了：

$j > x_{i}:~~ f_{i, x_i} = \min(f_{i - 1, j} + j) - x_{i}$

$j < x_{i}: ~~ f_{i, x_i} = \min(f_{i - 1, j} - j) - x_{i}$

问题就变成了查询区间 $[x_i, n]$ 中的 $f_{j} + j$ 和查询 $[1, x_i]$ 中 $f_{j} - j$ 的最小值了。 

所以在线段树上只需要维护 $f_{j} + j$ 和 $f_j - j$ 就好了。

复杂度：$O(n + Q \log n)$。

**code**

```c++
/*
work by:Ariel_
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

#include <algorithm>
#define lson rt << 1
#define rson rt << 1|1 
#define int long long
#define ll long long
#define rg register
using namespace std;
const int MAXN = 200500;
int read(){
    int x = 0,f = 1; char c = getchar();
    while(c < '0'||c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x*10 + c - '0'; c = getchar();}
    return x*f;
}
int n, a, b, last, cur, tmp, T;
ll ret1, ret2, ret3;
namespace Tree{
   struct Node{
      ll val[3], tag;
      Node(){memset(val, 63, sizeof val);}
   }tree[MAXN << 2];
   void push_up(int rt) {
   	  tree[rt].val[0] = min(tree[lson].val[0], tree[rson].val[0]);
   	  tree[rt].val[1] = min(tree[lson].val[1], tree[rson].val[1]);
   	  tree[rt].val[2] = min(tree[lson].val[2], tree[rson].val[2]);
   }
   void push_down(int rt) {
   	  if (!tree[rt].tag) return;
   	  tree[lson].val[0] += tree[rt].tag, tree[lson].val[1] += tree[rt].tag;
	  tree[lson].val[2] += tree[rt].tag, tree[lson].tag += tree[rt].tag;
   	  tree[rson].val[0] += tree[rt].tag, tree[rson].val[1] += tree[rt].tag;
	  tree[rson].val[2] += tree[rt].tag, tree[rson].tag += tree[rt].tag;
	  tree[rt].tag = 0;
   } 
   void modify(int rt, int l, int r, int p, int v) {
   	    if (l == r){
   	      tree[rt].val[0] = v;
		  tree[rt].val[1] = v - p, tree[rt].val[2] = v + p;
		  return ;
		}
		push_down(rt);
		int mid = l + r >> 1;
		if (p <= mid) modify(lson, l, mid, p, v);
		else modify(rson, mid + 1, r, p, v);
		push_up(rt);
   } 
   void add(ll v) {
   	  tree[1].tag += v;
	  tree[1].val[0] += v, tree[1].val[1] += v, tree[1].val[2] += v; 
   }
   ll query(int rt, int l, int r, int L, int R, int id) {
   	   if (L <= l && r <= R){return tree[rt].val[id];}
   	   push_down(rt);
   	   int mid = l + r >> 1; ll ret = LONG_LONG_MAX;
   	   if (L <= mid) ret = min(ret, query(lson, l, mid, L, R, id));
   	   if (R > mid) ret = min(ret, query(rson, mid + 1, r, L, R, id));
   	   return ret;
   }
}
using namespace Tree;
signed main(){
   n = read(), T = read(), a = read(), b = read();
   last = read();
   modify(1, 1, n, b, abs(a - last));
   modify(1, 1, n, a, abs(b - last));
   for(int i = 1; i < T; i++){
   	  cur = read(), tmp = abs(cur - last);
   	  ret1 = query(1, 1, n, cur, cur, 0) + tmp;
   	  ret2 = query(1, 1, n, 1, cur, 1) + cur;
   	  ret3 = query(1, 1, n, cur + 1, n, 2) - cur;
   	  ret1 = min(ret1, min(ret2, ret3));
   	  add(tmp);
   	  modify(1, 1, n, last, ret1);
   	  last = cur;
   }
   printf("%lld", tree[1].val[0]);
   puts("");
   return 0;
}

```



---

## 作者：To_our_starry_sea (赞：2)

### Solution

注意到，本题与 CSP-S 2024 T3 并无本质区别，只是转移上的细节不同。

套路地，对于任意一次移动之后，两颗棋子中必然至少有一颗在 $pos_i$ 上，因此我们可以可以设计 DP 状态 $dp_{0/1, i}$ 表示第一或第二颗棋子在上一个给定的位置上，而另一颗棋子在位置 $i$ 上时的最小时间。

不难发现，$dp_{0/1}$ 向自身的转移是容易的，只用全局加上 $|pos_i - pos_{i - 1}|$ 即可，表示将位于 $pos_{i - 1}$ 的棋子移到 $pos_i$ 的位置。现在我们考虑如何维护 $dp_0$ 与 $dp_1$ 之间的转移。因为有绝对值，我们可以分类讨论处理。由于操作有对称性，我们只用考虑从 $dp_1$ 向 $dp_0$ 转移的情况。首先，由状态的定义可知，我们只能将第一个棋子移到 $pos_i$ 的位置，而第二个棋子必然在 $pos_{i - 1}$ 的位置上。不难发现，$dp_{0, pos_{i - 1}} \gets \min(dp_{0, pos_{i - 1}},\min(\min\limits_{j = 1}^{pos_i}(dp_{1, j} + pos_i - j), \min\limits_{j = pos_i}^{n}(dp_{1, j} + j - pos_i)))$，即 $dp_{0, pos_{i - 1}} \gets \min(dp_{0, pos_{i - 1}},\min(\min\limits_{j = 1}^{pos_i}(dp_{1, j} - j) + pos_i, \min\limits_{j = pos_i}^{n}(dp_{1, j} + j) - pos_i)$。注意到，最终可能的转移只与 $dp_{1, j} - j$ 和 $dp_{1, j} + j$ 有关，因此我们在维护 $dp_{0/1, j}$ 时同时记录这两个值的最小值。以上操作如果暴力维护是 $O(qn)$ 的。发现我们需要进行全局加，单点修改，区间查询的操作，可以使用线段树维护。注意与 CSP-S T3 不同的是，无法使用全局 tag 的方式做到 $O(q + n)$。最终时间复杂度为 $O(q \log n)$。注意初始时的转移方式需要特判。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ls(rt) (rt << 1)
#define rs(rt) (rt << 1 | 1)
const int MAXN = 200005;
const ll INF = 1e18;
int n, q, A, B, pos[MAXN];
struct Segment_Tree {
    ll ans[MAXN << 2], w1[MAXN << 2], w2[MAXN << 2], layz[MAXN << 2];
    Segment_Tree() {
        memset(ans, 0x3f, sizeof(ans));
        memset(w1, 0x3f, sizeof(w1));
        memset(w2, 0x3f, sizeof(w2));
        memset(layz, 0, sizeof(layz));
    }
    inline void pushup(int rt) {
        ans[rt] = min(ans[ls(rt)], ans[rs(rt)]);
        w1[rt] = min(w1[ls(rt)], w1[rs(rt)]);
        w2[rt] = min(w2[ls(rt)], w2[rs(rt)]);
    }
    inline void pushdown(int rt) {
        if (layz[rt]) {
            layz[ls(rt)] += layz[rt], layz[rs(rt)] += layz[rt];
            ans[ls(rt)] += layz[rt], ans[rs(rt)] += layz[rt];
            w1[ls(rt)] += layz[rt], w1[rs(rt)] += layz[rt];
            w2[ls(rt)] += layz[rt], w2[rs(rt)] += layz[rt];
            layz[rt] = 0;
        }
    }
    inline void change(int rt, int l, int r, int way, ll w) {
        if (l == r) {
            if (w < ans[rt]) {
                ans[rt] = w;
                w1[rt] = ans[rt] - 1ll * l, w2[rt] = ans[rt] + 1ll * l;
            }
            return;
        }
        pushdown(rt);
        int mid = (l + r) >> 1;
        if (way <= mid) change(ls(rt), l, mid, way, w);
        else change(rs(rt), mid + 1, r, way, w);
        pushup(rt);
    }
    inline void add(int rt, int l, int r, int qx, int qy, ll w) {
        if (qx <= l && r <= qy) {
            ans[rt] += w, layz[rt] += w, w1[rt] += w, w2[rt] += w;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt);
        if (qx <= mid) add(ls(rt), l, mid, qx, qy, w);
        if (qy > mid) add(rs(rt), mid + 1, r, qx, qy, w);
        pushup(rt);
    }
    inline ll queryA(int rt, int l, int r, int qx, int qy) {
        if (qx <= l && r <= qy) return ans[rt];
        int mid = (l + r) >> 1;
        ll res = INF;
        pushdown(rt);
        if (qx <= mid) res = queryA(ls(rt), l, mid, qx, qy);
        if (qy > mid) res = min(res, queryA(rs(rt), mid + 1, r, qx, qy));
        return res;
    }
    inline ll queryB(int rt, int l, int r, int qx, int qy) {
        if (qx <= l && r <= qy) return w1[rt];
        int mid = (l + r) >> 1;
        ll res = INF;
        pushdown(rt);
        if (qx <= mid) res = queryB(ls(rt), l, mid, qx, qy);
        if (qy > mid) res = min(res, queryB(rs(rt), mid + 1, r, qx, qy));
        return res;
    }
    inline ll queryC(int rt, int l, int r, int qx, int qy) {
        if (qx <= l && r <= qy) return w2[rt];
        int mid = (l + r) >> 1;
        ll res = INF;
        pushdown(rt);
        if (qx <= mid) res = queryC(ls(rt), l, mid, qx, qy);
        if (qy > mid) res = min(res, queryC(rs(rt), mid + 1, r, qx, qy));
        return res;
    }
} Tr[2]; // 0 means A is in the last position; 1 means B is in the last position
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
int main() {
    n = read(), q = read(), A = read(), B = read();
    Tr[0].change(1, 1, n, B, 0), Tr[1].change(1, 1, n, A, 0);
    for (int i = 1; i <= q; i++) {
        pos[i] = read();
        ll res1 = min(Tr[0].queryB(1, 1, n, 1, pos[i]) + 1ll * pos[i], Tr[0].queryC(1, 1, n, pos[i], n) - 1ll * pos[i]);
        ll res2 = min(Tr[1].queryB(1, 1, n, 1, pos[i]) + 1ll * pos[i], Tr[1].queryC(1, 1, n, pos[i], n) - 1ll * pos[i]);
        Tr[0].add(1, 1, n, 1, n, abs(pos[i] - (i > 1 ? pos[i - 1] : A))), Tr[1].add(1, 1, n, 1, n, abs(pos[i] - (i > 1 ? pos[i - 1] : B)));
        Tr[0].change(1, 1, n, (i > 1 ? pos[i - 1] : B), res2), Tr[1].change(1, 1, n, (i > 1 ? pos[i - 1] : A), res1);
    }
    printf("%lld\n", min(Tr[0].queryA(1, 1, n, 1, n), Tr[1].queryA(1, 1, n, 1, n)));
    return 0;
}
```

---

## 作者：Mortidesperatslav (赞：2)

用 $f_{i,j}$ 表示第 $i$ 次操作，一个棋子在位置 $x_i$，另一个棋子在 $j$ 时的答案。

那么有：

1. $f_{i,x_i}=\displaystyle{\min_{1 \leq j \leq n}\{f_{i-1,j}+|x_i-j|\}}$。

2. $f_{i,j}=f_{i-1,j}+|x_i-x_{i-1}|,j \neq x_i$。

容易发现第二个式子就是整体加上常数，而第一个式子需要求一个区间的极值。

我们可以很自然的想到采用线段树维护。

具体维护方法为，对于每个 $f_j$（$i$ 一维滚动掉），维护 $f_j-j$ 和 $f_j+j$，这样可以避免绝对值的讨论。第一个式子就可以把全局拆成两部分算。

具体看代码（记得开 `long long`，我杂鱼完了调了一上午）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, q, p1, p2, a[200005];
struct seg{
	int vl, vl2, lzy;
}tr[800005];
void pup(int u){
	tr[u].vl = min(tr[u << 1].vl, tr[u << 1 | 1].vl);
	tr[u].vl2 = min(tr[u << 1].vl2, tr[u << 1 | 1].vl2);
}
void build(int u, int l, int r){
	if (l == r){
		if (l == p2){
			tr[u].vl = -l;
			tr[u].vl2 = l;
		}else{
			tr[u].vl = tr[u].vl2 = LLONG_MAX >> 4;
		}
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pup(u);
}
bool inr(int l, int r, int L, int R){
	return (L <= l && r <= R);
}
bool otr(int l, int r, int L, int R){
	return (L > r || R < l);
}
void pdn(int u){
	tr[u << 1].vl += tr[u].lzy;
	tr[u << 1].vl2 += tr[u].lzy;
	tr[u << 1 | 1].vl += tr[u].lzy;
	tr[u << 1 | 1].vl2 += tr[u].lzy;
	tr[u << 1].lzy += tr[u].lzy;
	tr[u << 1 | 1].lzy += tr[u].lzy;
	tr[u].lzy = 0;
}
void upd_sum(int u, int l, int r, int L, int R, int x){
	if (otr(l, r, L, R))
		return;
	if (inr(l, r, L, R)){
		tr[u].vl += x;
		tr[u].vl2 += x;
		tr[u].lzy += x;
		return;
	}
	pdn(u);
	int mid = (l + r) >> 1;
	upd_sum(u << 1, l, mid, L, R, x);
	upd_sum(u << 1 | 1, mid + 1, r, L, R, x);
	pup(u);
}
void upd_mn(int u, int l, int r, int pos, int x){
	if (pos < l || pos > r)
		return;
	if (l == r){
		tr[u].vl = min(tr[u].vl, x - l);
		tr[u].vl2 = min(tr[u].vl2, x + l);
		return;
	}
	pdn(u);
	int mid = (l + r) >> 1;
	upd_mn(u << 1, l, mid, pos, x);
	upd_mn(u << 1 | 1, mid + 1, r, pos, x);
	pup(u);
}
int qry_mn(int u, int l, int r, int L, int R, bool op){
	if (otr(l, r, L, R))
		return 114514325609ll;
	if (inr(l, r, L, R))
		return (op ? tr[u].vl2 : tr[u].vl);
	pdn(u);
	int mid = (l + r) >> 1;
	return min(qry_mn(u << 1, l, mid, L, R, op), qry_mn(u << 1 | 1, mid + 1, r, L, R, op));
}
int qry_ans(int u, int l, int r){
	if (l == r){
		return tr[u].vl + l;
	}
	pdn(u);
	int mid = (l + r) >> 1;
	return min(qry_ans(u << 1, l, mid), qry_ans(u << 1 | 1, mid + 1, r));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> q >> p1 >> p2;
	a[0] = p1;
	build(1, 1, n);
	for (int i = 1; i <= q; i++){
		cin >> a[i];
		int gmn = min(qry_mn(1, 1, n, 1, a[i], 0) + a[i], qry_mn(1, 1, n, a[i] + 1, n, 1) - a[i]);
		upd_sum(1, 1, n, 1, n, abs(a[i] - a[i - 1]));
		upd_mn(1, 1, n, a[i - 1], gmn);
	}
	cout << qry_ans(1, 1, n) << "\n";
	return 0;
}
```

---

## 作者：Masterwei (赞：2)

#### 前言
比较常规的一道题。


#### 思路

发现一个性质，就是在移动到 $a_i$ 这个点时，两个棋子之中一定有个点是 $a_i$，这很显然。

于是我们就得到了 $O(n^2)$ 做法：设 $f_{i,j}$ 表示在移动到第 $i$ 个点，除 $a_i$ 之外另一个棋子的坐标。

转移显然：$f_{i,j}=f_{i-1,j}+\left|a_i-a_{i-1}\right|$ 和 $f_{i,a_{i-1}}=\max(f_{i,a_{i-1}},f_{i-1,j}+\left|j-a_i\right|)$。

考虑优化，我们用一颗值域线段树表示 $dp$ 数组的第二维。

对于第一种转移，我们直接全局加即可。

对于第二种，由于只更新一个值，考虑直接将贡献算出来，分讨 $j\ge a_i$ 或是 $j<a_i$，那么我们线段树维护两个值，一个是 $val1=f_{i,j}-j$，一个是 $val2=f_{i,j}+j$。那么当 $j<a_i$ 时，贡献就是 $val1+a_i$。第二种同理，是 $val2-a_i$。算出一个值的贡献后，线段树单点更新即可。

最后求最大值即可。

时间复杂度为 $O(n+q\log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=2e5+15;
int n,q,A,B;
int a[Maxn];
struct Tree{
	int val1,val2,tag;
}t[Maxn<<2];
void build(int x,int l,int r){
	if(l==r){
		if(l!=B)t[x].val1=t[x].val2=1e18;
		else t[x].val1=-l,t[x].val2=l;
		return;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	t[x].val1=min(t[x<<1].val1,t[x<<1|1].val1);
	t[x].val2=min(t[x<<1].val2,t[x<<1|1].val2);
}
inline void add_(int x,int p){
	t[x].val1+=p;t[x].val2+=p;
	t[x].tag+=p;
}
inline void spread(int x){
	add_(x<<1,t[x].tag);
	add_(x<<1|1,t[x].tag);
	t[x].tag=0;
}
void change(int x,int l,int r,int d,int p){
	if(l==r){
		t[x].val1=min(t[x].val1,p-l);
		t[x].val2=min(t[x].val2,p+l);
		return;
	}int mid=l+r>>1;spread(x);
	if(mid>=d)change(x<<1,l,mid,d,p);
	else change(x<<1|1,mid+1,r,d,p);
	t[x].val1=min(t[x<<1].val1,t[x<<1|1].val1);
	t[x].val2=min(t[x<<1].val2,t[x<<1|1].val2);
}
int query1(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[x].val1;
	int mid=l+r>>1,res=1e18;spread(x);
	if(mid>=L)res=query1(x<<1,l,mid,L,R);
	if(mid<R)res=min(res,query1(x<<1|1,mid+1,r,L,R));
	return res;
}
int query2(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[x].val2;
	int mid=l+r>>1,res=1e18;spread(x);
	if(mid>=L)res=query2(x<<1,l,mid,L,R);
	if(mid<R)res=min(res,query2(x<<1|1,mid+1,r,L,R));
	return res;
}
int ans=1e18;
void dfs(int x,int l,int r){
	if(l==r)return void(ans=min(ans,t[x].val1+l));
	int mid=l+r>>1;spread(x);
	dfs(x<<1,l,mid);dfs(x<<1|1,mid+1,r);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();q=read();A=read();B=read();
	for(int i=1;i<=q;i++)a[i]=read();
	a[0]=A;
	build(1,1,n);
	for(int i=1;i<=q;i++){
		int val=min(query1(1,1,n,1,a[i])+a[i],query2(1,1,n,a[i],n)-a[i]);
		add_(1,abs(a[i]-a[i-1]));
		change(1,1,n,a[i-1],val);
	}
	dfs(1,1,n);
	printf("%lld\n",ans);	
	return 0;
}

```

---

## 作者：Loser_Syx (赞：1)

这不是我们 CSPS2024 T3 吗？我咋没早两个月做到这题？？？

-----

我们考虑当前在第 $i$ 个操作，那么棋子一定有一个在 $x_{i-1}$，定义 $f_{i,j}$ 表示当前棋子在 $j$，另一个棋子在 $x_{i-1}$ 的最小花费。

那么有如下转移

- 动 $x_{i-1}$

  $\forall 1\leq j \leq n, f_{i,j}=f_{i-1,j} + |x_{i-1}-x_i|$。

- 动 $j$

  $f_{i,x_{i-1}}=\min_{k=1}^n f_{i-1,k} + |x_i - k|$。

  发现这个看上去就很可以拆，根据 $k$ 的取值直接分为 $1 \leq k \leq x_i$ 和 $x_i \leq k \leq n$ 就好了。

  - $1 \leq k \leq x_i$

    $\min_{k=1}^{x_i} f_{i-1,k} + |x_i - k|\\=\min_{k=1}^{x_i} f_{i-1,k} + k - x_i\\= (\min^{x_i}_{k=1} f_{i-1,k} + k) - x_i$

  - $x_i \leq k \leq n$

    $\min_{k=1}^{x_i} f_{i-1,k} + |x_i - k|\\=\min_{k=1}^{x_i} f_{i-1,k} + x_i - k\\= (\min^{x_i}_{k=1} f_{i-1,k} - k) + x_i$
 
  由于我们需要区间 $\min$，线段树维护转移原值， $+k$ 和 $-k$ 后的值即可。

故复杂度 $O(n \log n)$。

[code](https://atcoder.jp/contests/arc073/submissions/60710287)。

---

## 作者：Lyrella (赞：1)

# 简要题意

开始时有两个棋子在位置 $A$ 和 $B$，每次给出一个目标点 $\operatorname{aim}_i$，你需要将其中一枚棋子移到此处，代价为 $|X-Y|$，求最小代价。

# 题解

对于这道题我们首先能够想出一个非常暴力的做法，我们设 $f_{i,x,y}$ 表示在第 $i$ 次操作后两个棋子的位置分别为 $x,y$，然后就可以写出转移方程：

1. $f_{i,x,\operatorname{aim}_i}=f_{i-1,x,\operatorname{aim}_{i-1}}+|\operatorname{aim}_i-\operatorname{aim}_{i-1}|$；
2. $f_{i,\operatorname{aim}_i,y}=f_{i-1,\operatorname{aim}_{i-1},y}+|\operatorname{aim}_i-\operatorname{aim}_{i-1}|$；
3. $f_{i,\operatorname{aim}_{i-1},\operatorname{aim}_i}=f_{i-1,\operatorname{aim}_{i-1},j}+|\operatorname{aim}_i-j|$；
4. $f_{i,\operatorname{aim}_i,\operatorname{aim}_{i-1}}=f_{i-1,j,\operatorname{aim}_{i-1}}+|\operatorname{aim}_i-j|$；

这样直接转移时间是 $O(N^2)$，空间是 $O(N^3)$ 的。

于是考虑优化。首先第一维滚动，然后思考怎么优化转移。仔细观察可以发现上面的所有式子中都一定有一维状态是重复的，因为每次只能移动一个棋子。

于是我们改写状态，设 $f_{i,j}$ 表示第 $i$ 次操作后一枚棋子在 $\operatorname{aim}_i$，另一枚在 $j$ 的最小代价，转移方程也很好写：
1. 对于从 $\operatorname{aim}_{i-1}$ 转移到 $\operatorname{aim}_i$ 的情况：$f_{i,j}=f_{i-1,j}+|\operatorname{aim}_{i-1}-\operatorname{aim}_i|$；
2. 对于从其他转移到 $\operatorname{aim}_i$ 的情况：$f_{i,\operatorname{aim}_{i-1}}=f_{i-1,j}+|j-\operatorname{aim}_i|$；

第一维可以干掉，第二维的转移可以看成全局加和单点修改，第一个转移是好实现的，第二个可以先把绝对值拆掉然后分类讨论一下。

于是我们就可以用线段树同时维护 $f_i,f_i+i,f_i-i$ 三个信息就做完了。最后答案 $\min_{1\le i\le n}\{f_i\}$，时间复杂度 $O(m\log n)$，空间复杂度 $O(\text{值域})$。

# 代码
```cpp
int n, m, a, b, c[N];
ll f[N << 2], t1[N << 2], t2[N << 2], tg[N << 2];
#define ls x << 1
#define rs x << 1 | 1
void upd(int x){
    t1[x] = min(t1[ls], t1[rs]);
    t2[x] = min(t2[ls], t2[rs]);
    f[x] = min(f[ls], f[rs]);
}
void build(int x, int l, int r, int aim){
    if(l == r){
        if(l == aim)t1[x] = l, t2[x] = - l;
        else f[x] = t1[x] = t2[x] = INF;
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid, aim), build(rs, mid + 1, r, aim);
    upd(x);
}
void pd(int x){
    if(! tg[x])return;
    if(f[ls] ^ INF)f[ls] += tg[x], t1[ls] += tg[x], t2[ls] += tg[x], tg[ls] += tg[x];
    if(f[rs] ^ INF)f[rs] += tg[x], t1[rs] += tg[x], t2[rs] += tg[x], tg[rs] += tg[x];
    tg[x] = 0;
}
void mdf(int x, int l, int r, int pos, ll y){
    if(l == r)return(void)(f[x] = y, t1[x] = y + l, t2[x] = y - l);
    int mid = l + r >> 1; pd(x);
    if(pos <= mid)mdf(ls, l, mid, pos, y);
    else mdf(rs, mid + 1, r, pos, y);
    upd(x);
}
ll q1(int x, int l, int r, int ql, int qr){
    if(ql <= l and r <= qr)return t1[x];
    int mid = l + r >> 1; ll res = INF; pd(x);
    if(ql <= mid)res = q1(ls, l, mid, ql, qr);
    if(mid < qr)res = min(res, q1(rs, mid + 1, r, ql, qr));
    return res;
}
ll q2(int x, int l, int r, int ql, int qr){
    if(ql <= l and r <= qr)return t2[x];
    int mid = l + r >> 1; ll res = INF; pd(x);
    if(ql <= mid)res = q2(ls, l, mid, ql, qr);
    if(mid < qr)res = min(res, q2(rs, mid + 1, r, ql, qr));
    return res;
}

signed main(){
    // fileio(fil);
    n = rd(), m = rd(), a = rd(), b = rd();
    build(1, 1, n, b);
    c[0] = a;
    for(int i = 1; i <= m; ++i){
        c[i] = rd(); ll v1 = q1(1, 1, n, c[i], n) - c[i], v2 = q2(1, 1, n, 1, c[i]) + c[i];
        ll tt = abs(c[i] - c[i - 1]);
        f[1] += tt, t1[1] += tt, t2[1] += tt, tg[1] += tt;
        v1 = min(v1, v2); mdf(1, 1, n, c[i - 1], v1);
    }
    cout << f[1];
    return 0;
}
```

---

## 作者：happy_zero (赞：1)

下文记 $pos_i=x_i$。

首先有 $O(mV)$ 的 dp：$f_{i,j}$ 表示第 $i$ 次操作，一个棋子在 $pos_i$，另一个在 $j$ 的最小操作，转移：

$$f_{i,j}=f_{i-1,j}+|pos_i-pos_{i-1}|$$
$$f_{i,pos_{i-1}}=\min_{1\le j\le n}\{f_{i-1,j}+|j-pos_i|\}$$

对应的分别是：将上一次在 $pos_{i-1}/j$ 的棋子移到 $pos_{i}$。

初始化：$f_{1,a}=|pos_1-b|,f_{1,b}=|pos_1-a|$。

把 $i$ 这维压掉，记 $g=f_{i-1}$ 辅助转移：

$$f_j=g_j+|pos_i-pos_{i-1}|$$
$$f_{pos_{i-1}}=\min_{1\le j\le n}\{g_j+|j-pos_i|\}$$

发现第一个对应着全局加，打个全局 tag 即可（第二种转移记得减去 $|pos_i-pos_{i-1}|$ 抵消）；

第二个对应着全局 $\max$ 和单点修改，但由于有一个绝对值，拆开，就是要查询 $\min_{1\le j\le pos_i}\{g_j-j\}$ 和 $\min_{pos_i<j\le n}\{g_j+j\}$。于是用线段树维护 $f_j,f_j+j$ 和 $f_j-j$ 即可。

复杂度 $O(Q\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
const int INF = 1e12;
int a, b, t[N << 2], t1[N << 2], t2[N << 2], pos[N];
void pushup(int k) {
    t[k] = min(t[k << 1], t[k << 1 | 1]);
    t1[k] = min(t1[k << 1], t1[k << 1 | 1]);
    t2[k] = min(t2[k << 1], t2[k << 1 | 1]);
}
void build(int k, int l, int r) {
    if (l == r) {
        if (l == a) t[k] = abs(pos[1] - b), t1[k] = t[k] + a, t2[k] = t[k] - a;
        else if (l == b) t[k] = abs(pos[1] - a), t1[k] = t[k] + b, t2[k] = t[k] - b;
        else t[k] = t1[k] = t2[k] = INF;
        return;
    }
    int m = l + r >> 1;
    build(k << 1, l, m);
    build(k << 1 | 1, m + 1, r);
    pushup(k);
}
void updata(int k, int l, int r, int x, int v, int v1, int v2) {
    if (l == r) return t[k] = min(t[k], v), t1[k] = min(t1[k], v1), t2[k] = min(t2[k], v2), void();
    int m = l + r >> 1;
    if (x <= m) updata(k << 1, l, m, x, v, v1, v2);
    else updata(k << 1 | 1, m + 1, r, x, v, v1, v2);
    pushup(k);
}
int query(int k, int l, int r, int L, int R, int op) {
    if (L <= l && r <= R) return (op == 1 ? t1[k] : (op == 2 ? t2[k] : t[k]));
    int m = l + r >> 1, res = INF;
    if (L <= m) res = query(k << 1, l, m, L, R, op);
    if (R > m) res = min(res, query(k << 1 | 1, m + 1, r, L, R, op));
    return res;
}
signed main() {
    int V, m; cin >> V >> m >> a >> b;
    for (int i = 1; i <= m; i++) 
        cin >> pos[i];
    build(1, 1, V); int lazy = 0;
    for (int i = 2; i <= m; i++) {
        lazy += abs(pos[i] - pos[i - 1]);
        int w1 = query(1, 1, V, 1, pos[i], 2) + pos[i];
        int w2 = query(1, 1, V, pos[i], V, 1) - pos[i];
        int w = min(w1, w2) - abs(pos[i] - pos[i - 1]);
        updata(1, 1, V, pos[i - 1], w, w + pos[i - 1], w - pos[i - 1]);
    }
    cout << query(1, 1, V, 1, V, 0) + lazy;
    //最后别忘了加上全局 tag 
    return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [AT_arc073_d](https://www.luogu.com.cn/problem/AT_arc073_d)     

怎么是 2900 啊。     

考虑令 $dp_i$ 表示当前有一个棋子站在 $i$，另一个棋子站在当前询问位置的最小开销，则 $dp$ 转移有两种情况。令上一轮的 $dp$ 为 $f$，这一轮的为 $g$，第一种转移是 $f_i+|q_{now}-q_{now-1}|$ 转移给 $g_i$，第二种转移是 $f_i+|q_{now}-i|$ 转移到 $g_{q_{now}}$，这里考虑按 $i$ 大小拆分，就是询问 $f_i+i$ 和 $f_i-i$ 的两个区间最小值。DP 使用线段树维护即可，需要一个全局加，单点取 $\min$，区间求 $\min$，复杂度 $O(n\log n)$。   

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 10000000000000000ll
using namespace std;
int n,q,a,b,k1,k2,k3,k4,k5,k6,k7,k8,k9,Q[500003];
struct SegT{
	int st;
	int ed;
	int val;
	int val2;
	int lzmk;
}T[3000003];
void pushup(int now){
	T[now].val=min(T[now*2].val,T[now*2+1].val);
	T[now].val2=min(T[now*2].val2,T[now*2+1].val2);
	return;
}
void add(int now,int v){
	T[now].val+=v;
	T[now].val2+=v;
	T[now].lzmk+=v;
	return;
}
void pushdown(int now){
	add(now*2,T[now].lzmk);
	add(now*2+1,T[now].lzmk);
	T[now].lzmk=0;
	return;
}
void build(int now,int st,int ed){
	T[now].st=st;
	T[now].ed=ed;
	if(st==ed){
		T[now].val=T[now].val2=INF;
		return;
	}
	build(now*2,st,((st+ed)>>1));
	build(now*2+1,((st+ed)>>1)+1,ed);
	pushup(now);
	return;
}
int Query(int now,int l,int r){
	if(T[now].st>=l&&T[now].ed<=r)return T[now].val;
	if(T[now].st>r||T[now].ed<l)return INF;
	pushdown(now);
	return min(Query(now*2,l,r),Query(now*2+1,l,r));
}
int Query2(int now,int l,int r){
	if(T[now].st>=l&&T[now].ed<=r)return T[now].val2;
	if(T[now].st>r||T[now].ed<l)return INF;
	pushdown(now);
	return min(Query2(now*2,l,r),Query2(now*2+1,l,r));
}
void modify(int now,int wz,int val,int val2){
	if(T[now].st==T[now].ed){
		T[now].val=min(T[now].val,val);
		T[now].val2=min(T[now].val2,val2);
		return;
	}
	pushdown(now);
	if(wz<=((T[now].st+T[now].ed)>>1))modify(now*2,wz,val,val2);
	else modify(now*2+1,wz,val,val2);
	pushup(now);
	return;
} 
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>q>>a>>b;
	build(1,1,n);
	for(int i=1;i<=q;i++){
		cin>>Q[i];
		if(i==1){
			modify(1,a,abs(b-Q[i])-a,abs(b-Q[i])+a);
			modify(1,b,abs(a-Q[i])-b,abs(a-Q[i])+b);
		}
		else{
			k1=min(Q[i]+Query(1,1,Q[i]),Query2(1,Q[i],n)-Q[i]);
			add(1,abs(Q[i]-Q[i-1]));
			modify(1,Q[i-1],k1-Q[i-1],k1+Q[i-1]);
		}
	}
	k1=Query(1,1,1)+1;
	for(int i=2;i<=n;i++)k1=min(k1,Query(1,i,i)+i);
	cout<<k1;
	return 0;
}
```


---

## 作者：_RainCappuccino_ (赞：0)

> $\texttt{TAGS}$：DP，线段树优化

很像 CSP-S-2024-T3 的状态设计。

我们发现，一定是两个棋子分别交替去满足一段区间的要求，考虑 dp，设 $dp_{i}$ 表示操作 $i$ 时，其中一个棋子在 $x_i$，另一个在 $x_{i + 1}$ 的情况的最小步数。

转移为：$dp_i = \min_{j = 1}^{i - 1}(dp_j + \sum_{j + 2}^{i} |x_i - x_{i - 1}| + |x_{i + 1} - x_j|)$，即用当前棋子去满足 $x_{j + 2} \sim x_i$ 的操作，然后另一个棋子直接移动到 $x_{i + 1}$ 位置。

考虑到 $\sum_{j + 2}^{i} |x_i - x_{i - 1}|$ 可以前缀和预处理，转化为 $sum_i - sum_{j + 1}$，式子变为：$dp_i = \min_{j = 1}^{i - 1}(dp_j + sum_i - sum_{j + 1} + |x_{i + 1} - x_j|)$。

这个绝对值不好处理，考虑拆开讨论。

$$
\left\{\begin{matrix}
dp_i = \min_{j = 1}^{i - 1}(dp_j + sum_i - sum_{j + 1} + x_{i + 1} - x_j) & x_{i + 1} \ge x_j \\ \\
dp_i = \min_{j = 1}^{i - 1}(dp_j + sum_i - sum_{j + 1} - x_{i + 1} + x_j) & x_{i + 1} < x_j
\end{matrix}\right.
$$

然后将与 $i$ 有关的项提出来，就只需要维护与 $j$ 有关的东西了，


$$
\left\{\begin{matrix}
dp_i =  sum_i + x_{i + 1} + \min_{j = 1}^{i - 1}(dp_j - sum_{j + 1} - x_j) & x_{i + 1} \ge x_j \\ \\
dp_i = sum_i - x_{i + 1} + \min_{j = 1}^{i - 1}(dp_j - sum_{j + 1}  + x_j) & x_{i + 1} < x_j
\end{matrix}\right.
$$

那么开两个值域线段树维护对于当前前缀，每个 $x_i$ 对应的 $dp_j - sum_{j + 1} + x_j$ 和 $dp_j - sum_{j + 1} - x_j$ 的最小值，取满足条件的值域区间的区间 $\min$ 即可。

然后考虑 dp 初值，两种情况，用初始在 $A$ 的棋子直接满足 $x_1 \sim x_i$ 的操作，在 $B$ 的棋子直接移动到 $x_{i + 1}$，或者是用初始在 $B$ 的棋子直接满足 $x_1 \sim x_i$ 的操作，在 $A$ 的棋子直接移动到 $x_{i + 1}$。

那么 $dp_i = \min(|x_1 - a| + sum_i + |x_{i + 1} - b|, |x_1 - b| + sum_i + |x_{i + 1} - a|)$。

最后到 $x_n$ 的情况，由于不存在 $x_{n + 1}$，不能直接取用 $dp_n$，最终答案应该为 $\min(dp_i + sum_n - sum_{i + 1})$，即最后直接走到 $n$，然后这题就愉快地结束了。

---

## 作者：Tjqq (赞：0)

闲话：今年 CSP-S T3 疑似这题改版（比这题更简单），但是我场上脑子抽了不会 $O(n)$，只能 65pts 遗憾离场。

提供简单线段树做法

不难想到一个朴素的 $O(n^2)$ 的做法。
设状态 $f_{i,j}$ 和 $g_{i,j}$ 表示到第 $i$ 个操作，选择移动第一个或者第二个棋子到位置 $x_i$，另一个棋子的位置为 $j$。

```cpp
//i move x j move x
chkmin(f[i][j],f[i-1][j]+abs(a[i-1]-a[i]));
chkmin(g[i][j],g[i-1][j]+abs(a[i-1]-a[i]));
//i move x j move y
chkmin(f[i][a[i-1]],g[i-1][j]+abs(j-a[i]));
chkmin(g[i][a[i-1]],f[i-1][j]+abs(j-a[i]));
```

然后就可以直接上权值线段树优化这个非常工整的式子。具体的，线段树每个叶子维护三个值，分别是 $dp[i],dp[i]+i,dp[i]-i$。对于第一类转移直接做全局加法即可，对于第二类转移分成比 $a[i]$ 大的和比 $a[i]$ 小的取 $\min$ 即可。

时间复杂度: $O(n\log n)$

```cpp
//created by fqr & cyx in 2024
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
#define ll long long
#define pb emplace_back
int ff,Ch;
template <typename T> inline void rd(T &x) {
    x=0,ff=1,Ch=getchar();
    while((Ch<'0'||Ch>'9') && Ch!='-') Ch=getchar();
    if(Ch=='-')Ch=getchar(),ff=-1;
    while(Ch>='0' && Ch<='9') {
        x=(x<<1)+(x<<3)+Ch-'0';
        Ch=getchar();
    }
    x*=ff;
}
template <typename T,typename ...Args> inline void rd(T &x,Args &...args) {
    rd(x), rd(args...);
}
using namespace std;
const int N=2e5+5;
const ll inf=0x3f3f3f3f3f3f;
int n,m,A,B;
int a[N];
ll ans=inf;
//ll f[N][N],g[N][N];
//f[i][j]x->a[i] y->j 
void chkmin(ll &x,ll y) {
	if(y<x) x=y;
}
struct sgt {
	#define ls x<<1
	#define rs x<<1|1
	ll add[N<<2],w[N<<2],mn[N<<2][2];
	void push_up(int x) {
		mn[x][0]=min(mn[ls][0],mn[rs][0]); 
		mn[x][1]=min(mn[ls][1],mn[rs][1]);
	}
	void push_down(int x) {
		if(add[x]) {
			add[ls]+=add[x];
			add[rs]+=add[x];
			mn[ls][0]+=add[x];
			mn[rs][0]+=add[x]; 
			mn[ls][1]+=add[x];
			mn[rs][1]+=add[x]; 
			w[ls]+=add[x];
			w[rs]+=add[x];
			add[x]=0;
		}
	}
	void build(int x,int l,int r,int p,int val) {
		mn[x][0]=mn[x][1]=w[x]=inf;
		if(l==r) {
			if(l==p) {
				w[x]=val;
				mn[x][0]=val-l;
				mn[x][1]=val+l;
			}
			return ;
		}
		int mid=l+r>>1;
		build(ls,l,mid,p,val),build(rs,mid+1,r,p,val);
		push_up(x);
	}
	void modify(int x,int l,int r,int pos,ll val) {
		if(l==r) {
			w[x]=min(w[x],val);
			mn[x][0]=w[x]-l;
			mn[x][1]=w[x]+l;
			return ;
		}
		push_down(x); 
		int mid=l+r>>1;
		if(pos<=mid) modify(ls,l,mid,pos,val);
		else modify(rs,mid+1,r,pos,val);
		push_up(x);
	}
	ll ask(int x,int l,int r,int L,int R,bool cur) {
		if(l>=L && r<=R) return mn[x][cur];
		push_down(x);
		int mid=l+r>>1;
		ll ans=inf;
		if(L<=mid) ans=min(ans,ask(ls,l,mid,L,R,cur));
		if(R>mid) ans=min(ans,ask(rs,mid+1,r,L,R,cur));
		return ans;
	}
	void down(ll val) {
		add[1]+=val;
		mn[1][0]+=val;
		mn[1][1]+=val;
	}
	void dfs(int x,int l,int r) {
		if(l==r) {
			ans=min(ans,w[x]);
//			cout<<l<<' '<<w[x]<<'\n'; 
			return ;
		}
		push_down(x);
		int mid=l+r>>1;
		dfs(ls,l,mid),dfs(rs,mid+1,r);
	}
} f,g;
signed main() {
#ifdef LOCAL
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
#endif
	IOS;
	cin>>m>>n>>A>>B;
	for(int i=1; i<=n; i++)
		cin>>a[i];
//	memset(f,0x3f,sizeof(f));
//	memset(g,0x3f,sizeof(g));
//	f[0][B]=0;
//	g[0][A]=0;
//	chkmin(f[1][B],f[0][B]+abs(a[1]-A));
//	chkmin(g[1][A],g[0][A]+abs(a[1]-B));
	f.build(1,1,m,B,abs(a[1]-A));
	g.build(1,1,m,A,abs(a[1]-B));
	for(int i=2; i<=n; i++) {
//		for(int j=1; j<=m; j++) {
//			//i move x j move x
//			chkmin(f[i][j],f[i-1][j]+abs(a[i-1]-a[i]));
//			chkmin(g[i][j],g[i-1][j]+abs(a[i-1]-a[i]));
//			//i move x j move y
//			chkmin(f[i][a[i-1]],g[i-1][j]+abs(j-a[i]));
//			chkmin(g[i][a[i-1]],f[i-1][j]+abs(j-a[i]));
//		}
		ll fl=f.ask(1,1,m,1,a[i],0)+a[i],fr=f.ask(1,1,m,a[i]+1,m,1)-a[i];
		ll gl=g.ask(1,1,m,1,a[i],0)+a[i],gr=g.ask(1,1,m,a[i]+1,m,1)-a[i];
		f.down(abs(a[i]-a[i-1])),g.down(abs(a[i]-a[i-1]));
//		cout<<"modify "<<a[i-1]<<' '<<min(gl,gr)<<" "<<min(fl,fr)<<'\n';
		f.modify(1,1,m,a[i-1],min(gl,gr));
		g.modify(1,1,m,a[i-1],min(fl,fr));
	}
	f.dfs(1,1,m);
	g.dfs(1,1,m);
	cout<<ans;
	return 0;
}
/*

*/
```

---

## 作者：sad_lin (赞：0)

非常厉害的一题，暴力做法枚举当前两颗棋子的位置，再枚举上一次操作时的两颗棋子位置来转移，这样复杂度为 $O(qn^4)$，非常糟糕。

因为转移时总有一个棋子在 $x_i$ 的位置，所有我们可以设状态为 $f_{i,j}$ 为经过了前 $i$ 个位置，当前不在 $x_i$ 位置上的那个棋子在 $j$ 位置上的最小花费，我们进行分类讨论。

当 $j\neq x_{i-1}$ 时，说明 $j$ 这颗棋子上次也没有移动，所以 $x_i$ 是由 $x_{i-1}$ 转移过来的，于是又 $f_{i-1,j}+\left| x_i-x_{i-1} \right|$。

当 $j=x_{i-1}$ 时，此时我们就要枚举 $k$ 找到最小的到 $x_i$ 的距离花费，于是有 $\min {(f_{i-1,k}+\left| x_i-k \right|)}$，我们分类讨论这个 $k$ 的值来去掉这个绝对值，当 $k\ge x_i$ 有 $\min{(f_{i-1,k}+k-x_i)}$，当 $k\le x_i$ 有 $\min{(f_{i-1,k}-x_i+k)}$。

于是我们就可以用线段树分别维护 $f_{k}+k$ 和 $f_{k}-k$ 即可。

因为 $f_{i,k}$ 只与 $f_{i-1,k}$ 有关，所以直接用线段树进行区间查询区间修改来滚动数组即可。

---

## 作者：Xlon_Rainfi (赞：0)

## $\large\mathfrak{1st.\ Preamble|}$ 前言

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_arc073_d) | [AtCoder 原题传送门](https://atcoder.jp/contests/arc073/tasks/arc073_d) | [更好的阅读体验](https://xlon-wu.github.io/2024/09/02/solution-at-arc073d/)。

在某次膜你赛里见到了这道题，赛场上写了个假 DP，喜提零分，然后学长的题解写错了几个字，加上脑抽，瞪眼看了俩小时没看出来，明白后感觉我就是个智 X。

如果其他题解看不懂的可以尝试看看这篇（也就可能只有我这个智 X 需要）。

## $\large\mathfrak{2nd.\ Solution|}$ 题解

### 思路

首先我们知道每次操作最多移动一个棋子（废话）。

然后我们记 $f_{i,a,b}$ 表示操作 $i$ 次，两颗棋子分别在 $a,b$ 所消耗的最小时间。由于 $a,b$ 两者中至少有一个是 $x_i$（根据题目要求），故我们可以少记一维，用 $f_{i,a}$ 表示一个在 $x_i$，另一个在 $a$​ 的最小耗时。

于是我们有转移：

$$
f_{i,j}=f_{i-1,j}+|x_i-x_{i-1}|\\
f_{i,x_i}=\min_{j=1}^{V}\{f_{i-1,j}+|x_i-j|\}
$$

第一个柿子表示原先在 $j$ 的棋子不动，原先在 $x_{i-1}$ 的棋子移动到 $x_i$，需要 $|x_i-x_{i-1}|$ 的代价。

第二个柿子表示原先在 $x_i$ 的棋子不动，原先在 $j$ 的棋子移动到 $x_i$，需要 $|x_i-j|$ 的代价。

然后我们可以发现，$f_i$ 这一层中的值只依赖于 $f_{i-1}$​，然后我们就可以滚动数组优化，变成了一维（三维压成一维，是不是很有成就感）。接下来第一维全部省略。

由于第一种转移的代价是个定值，所以可以直接区间加。

第二种转移我们可以先拆绝对值，拆完后变成下面这样：
$$
f_{x_i}=\min\left\{\min_{j=1}^{x_i}\{f_j-j+x_i\},\min_{j=x_i+1}^{V}\{f_j+j-x_i\}\right\}
$$
这个柿子里的两个小柿子中都有一个固定的 $x_i$，我们只需要求区间最小 $f_j-j$ 和 $f_j+j$，这便转化为了一个动态 RMQ 问题。

**最终实现方法**：维护一棵线段树，需要支持区间加法、查询区间最小 $f_j-j$、查询区间最小 $f_j+j$ 这三个功能。每次查询按照上面的方法计算。

**时间复杂度**：$O(N\log N+Q\log N)$（建树 $O(N\log N)$；每次查询 $O(\log N)$，所有查询共 $O(Q\log N)$）。

## $\large\mathfrak{3rd.\ Code|}$ 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define FOR(i, l, r) for (ll i = l; i <= r; i++)
#define FILE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
#define pii pair<ll, ll>
#define pll pair<long long, long long>
// #define Clock
using namespace std;
const ll N = 2e5 + 10, inf = 1e15;
ll V, a, b, m, op[N], ans;

/* -------- start of segment tree -------- */

#define lc t[x << 1]
#define rc t[x << 1 | 1]
#define ls (x << 1)
#define rs (x << 1 | 1)
#define tx t[x]

struct node {
    ll l, r, val, mi1, mi2;
} t[N << 2];

inline void pushup(ll x) {
	tx.val = min(lc.val, rc.val);
	tx.mi1 = min(lc.mi1, rc.mi1);
	tx.mi2 = min(lc.mi2, rc.mi2);
}

void build(ll x, ll l, ll r) {
    tx.l = l, tx. r = r;
	if (l == r) {
        if (l == a) {
        	tx.val = abs(op[1] - b);
        	tx.mi1 = tx.val + a;
        	tx.mi2 = tx.val - a;
        } else if(l == b) {
        	tx.val = abs(op[1] - a);
        	tx.mi1 = tx.val + b;
        	tx.mi2 = tx.val - b;
        } else tx.val = tx.mi1 = tx.mi2 = inf;
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(x);
}

void change(ll x, ll idx, ll now, ll w) {  // 区间加
	if (idx < tx.l || idx > tx.r) return;
	if (tx.l == idx && tx.r == idx) {
		tx.val = min(tx.val, w);
		tx.mi1 = min(tx.mi1, w + op[now - 1]);
		tx.mi2 = min(tx.mi2, w - op[now - 1]);
		return;
	}
	change(ls, idx, now, w);
	change(rs, idx, now, w);
	pushup(x);
}

ll query(ll x, ll l, ll r, ll ty){  // 这里将两个查询合并在一起
	if (r < tx.l || tx.r < l) return inf;
	if (l <= tx.l && tx.r <= r) {
		if (ty == 0) return tx.val;
		else if (ty == 1) return tx.mi1;
		else if (ty == 2) return tx.mi2;
		else return inf;
	}
	return min(query(ls, l, r, ty), query(rs, l, r, ty));
}

/* --------- end of segment tree --------- */

int main() {
#ifdef Clock
    clock_t Start_Time = clock();
#endif
    // ios::sync_with_stdio(false);
    // cin.tie(0),cout.tie(0);
    // FILE("hard");
    cin >> V >> m >> a >> b;
    for (ll i = 1; i <= m; i ++) cin >> op[i];
    build(1, 1, V);
	for (ll i = 2; i <= m; i ++){
		ans += abs(op[i] - op[i - 1]);
		ll w = min(query(1, 1, op[i], 2) + op[i], query(1, op[i], V, 1) - op[i]) - abs(op[i] - op[i - 1]);
		change(1, op[i - 1], i, w);
	}
	cout << query(1, 1, V, 0) + ans;
#ifdef Clock
    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\nRuntime: " << clock() - Start_Time << " ms\n";
    system("pause");
#endif
    return 0;
}
```

## $\large\mathfrak{4th.\ Postscript|}$ 后记

![](https://cdn.luogu.com.cn/upload/image_hosting/td3bl1dn.png)

这里其实是我脑抽了，第一次不是滚动数组。

---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j}$ 表示考虑到前 $i$ 个请求，显然目前会有一个棋子在 $x_i$ 位置，另一个棋子在 $j$ 位置的最小移动距离。

考虑转移：

* $dp_{i-1,j}+|x_i-x_{i-1}|\to dp_{i,j}$；
* $dp_{i-1,j}+|x_i-j|\to dp_{i,x_{i-1}}$。

第一个转移式等价于 $\displaystyle{\min_{j=1}^ndp_{i-1,j}}+|x_i-x_{i-1}|\to dp_{i,k}$。

考虑如何维护第二个转移式，分 $j\leq x_i$ 和 $j\geq x_i$ 处理。

* $j\leq x_i$ 时：$\displaystyle{\min_{j=1}^{x_i}(dp_{i-1,j}-j)+x_i\to dp_{i,x_{i-1}}}$；
* $j\geq x_i$ 时：$\displaystyle{\min_{j=x_i}^n(dp_{i-1,j}+j)-x_i\to dp_{i,x_{i-1}}}$。

用线段树维护 $dp_{i,j}$，$dp_{i,j}+j$，$dp_{i,j}-j$ 即可。总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int x[1000005],lsh[1000005];
struct sgt{
	int f[1000005],lzt[1000005];
	void init(){
		memset(f,1,sizeof(f));
	}
	void pushdown(int i){
		f[i*2]+=lzt[i];
		f[i*2+1]+=lzt[i];
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]+=cg;
			lzt[i]+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=min(f[i*2],f[i*2+1]);
	}
	void changep(int i,int l,int r,int pos,int cg){
		if(l==r){
			f[i]=min(f[i],cg);
			return ;
		}
		pushdown(i);
		if(pos<=mid) changep(i*2,l,mid,pos,cg);
		else changep(i*2+1,mid+1,r,pos,cg);
		f[i]=min(f[i*2],f[i*2+1]);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql>qr) return 1e18;
		if(ql<=l&&r<=qr) return f[i];
		pushdown(i);
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return min(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree1,tree2,tree3;
signed main(){
	int n,q,a,b; cin>>n>>q>>a>>b; 
	x[1]=a,x[2]=b; for(int i=3;i<=q+2;i++) cin>>x[i];
	for(int i=1;i<=q+2;i++) lsh[i]=x[i]; sort(lsh+1,lsh+q+3);
	for(int i=1;i<=q+2;i++) x[i]=lower_bound(lsh+1,lsh+q+3,x[i])-lsh;
	tree1.init(),tree2.init(),tree3.init();
	tree1.changep(1,1,q+2,x[1],0);
	tree2.changep(1,1,q+2,x[1],0-lsh[x[1]]);
	tree3.changep(1,1,q+2,x[1],0+lsh[x[1]]);
	for(int i=3;i<=q+2;i++){
		int minv=min(tree2.qry(1,1,q+2,1,x[i])+lsh[x[i]],tree3.qry(1,1,q+2,x[i],q+2)-lsh[x[i]]);
		tree1.change(1,1,q+2,1,q+2,llabs(lsh[x[i]]-lsh[x[i-1]]));
		tree2.change(1,1,q+2,1,q+2,llabs(lsh[x[i]]-lsh[x[i-1]]));
		tree3.change(1,1,q+2,1,q+2,llabs(lsh[x[i]]-lsh[x[i-1]]));
		tree1.changep(1,1,q+2,x[i-1],minv);
		tree2.changep(1,1,q+2,x[i-1],minv-lsh[x[i-1]]);
		tree3.changep(1,1,q+2,x[i-1],minv+lsh[x[i-1]]);
	}
	cout<<tree1.qry(1,1,q+2,1,q+2);
	return 0;
}
```

---

