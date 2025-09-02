# 誘拐 2 (Abduction 2)

## 题目描述

#「JOISC 2017 Day 4」绑架 2


**题目译自 [JOISC 2017](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/index.html) Day4 T1「[誘拐 2](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d4.pdf)（[Abduction 2](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d4-en.pdf)）」**

某地的道路网可视为由 $H$ 条东西向道路与 $W$ 条南北向道路构成的网格，相邻的两条平行道路之间的距离为 $1 \:\textrm{km}$。东西向道路从北到南依次编号为 $ 1\ldots H $，南北向道路从西到东依次编号为 $ 1\ldots W $ 。   
东西向道路和南北向道路相交形成路口，规定 $ x $ 号南北向街道和 $ y $ 号东西向街道形成的路口的坐标是 $ (x, y) $ 。  
每条道路有一个车流指数。$i$ 号东西向道路 $(1\le i\le H)$ 的车流指数为 $A_{\;\!i}$ ，$j$ 号南北向道路 $(1\le j\le W)$ 的车流指数为 $B_j$ 。所有道路的车流指数互不相同。

给出 $Q$ 个互不相同的坐标 $(S_1, T_1), (S_2, T_2),\ldots,(S_Q, T_Q)$ 作为备选起点。对于每个备选起点，请计算：如果按照下述规则移动，最多可以移动多远。  
- 移动开始时，可以任意选择方向。
- 当到达十字路口时：
  * 如果 直行方向的道路的车流指数 比 该十字路口的另一条道路的车流指数 小，就转弯。你可以选择左转还是右转。但如果你在城市边界上，可能只能左转/右转。
  * 如果 直行方向的道路的车流指数 比 该十字路口的另一条道路的车流指数 大，就直行。但如果前面没路（比如到了城市边界），就只能停在此处。
  * 不能掉头。

## 说明/提示

$2 \le H, W \le 5\times 10^4, 1\le Q\le 100,$ $1\le A_i, B_j\le 10^9(1\le i\le H, 1\le j\le W),$ $1\le S_k\le H, 1\le T_k\le W(1\le k\le Q)$ 。  
保证所有道路的车流指数互不相同，所有的备选起点互不相同。

|Subtask #|分值|$H,W$|$Q$|
|-|-|-|-|
|1|13|$H,W\le 8$|$Q=1$|
|2|10|$H,W\le 2000$|$Q=1$|
|3|17|$H, W \le 5\times 10^4$|$Q=1$|
|4|4|$H,W\le 2000$|$Q\le 100$|
|5|56|$H, W \le 5\times 10^4$|$Q\le 100$|

感谢 Planet6174 提供的翻译

# 题解

## 作者：Azazеl (赞：12)

### AT2542 誘拐 2 (Abduction 2)  
#### 题意  
$\ \ \ \ $给出一个平面直角坐标系，规定每条横向和纵向的线都有一个对应的数值，给出若干次询问，每次询问从某个点开始以任意方向出发，每到一个交点就选择经过该点的两条直线中对应数值较大的那条线走，如果需要改变方向可以任意选择左转或者右转，求按照这样的规则走下去最大能经过多少边。  

------------
#### 题解  
$\ \ \ \ $拿到这道题先是没有思路，但我们看看数据范围，说不定对解题会有帮助。  

$\ \ \ \ $第一个子任务 $H,W \le 8,Q=1$ 时我们可以直接用DFS暴力过去，因此： 

$\texttt{Algorithm 1 暴力搜索}$  
$\ \ \ \ $即从起点开始搜索，每到一个点判断直走或者转弯，直走就直接更改对应横或纵坐标，转弯则分两类讨论并取最大值即可，代码应该不是很难写，在此不（lan）给（de）出（xie）。  
$\ \ \ \ $通过构造，我们可以知道路径最长是 $2\times \max\{H,W\}$ ，因此最大共有 $2\times \max\{H,W\}!$ 的搜索次数(当然这跑不满)。并且我们可以证明这条路线不会重叠，因此不用担心重复计算。此时理论上可以通过第一个子任务。  

$\texttt{Algorithm 2 线段树优化/ST表}$  
$\ \ \ \ $打完暴力第一件事是什么？考虑优化暴力。我们发现其实直走的过程是单纯一步步走的，但是这种直走其实没有意义的，如果我们知道下一个在左边的转点和在右边的转点，我们就可以快速地忽略掉直走。  

$\ \ \ \ $而寻找的过程抽象出来，就是给出一个数列和一个位置，分别求在该位置两边第一个大于这个数的位置。  
$\ \ \ \ $这可以想到线段树，维护最大值，以找左边为例：进入函数的时候先判断是否满足两个条件（在左边和最大值大于给定值），满足则优先在右边返回查询结果，右边无果再返回左边；查询右边时同理。  
$\ \ \ \ $因此我们分别维护行和列的数列最大值，在搜索时直接通过线段树 $\log n$ 地找到下一个转向的坐标即可。当然由于我们是无修改查询最大值，也可以用 ST 表，方法同上。

$\ \ \ \ $这样我们应该就能通过前三个子任务了。  

$\texttt{Algorithm 3 记忆化} $  
$\ \ \ \ $但是我们来看后面两个子任务，它们的不同点在于询问的点变多了，这样我们就会发现一个问题：有可能会在搜索其他点时产生重复计算。  

$\ \ \ \ $解决重复计算那肯定会用到记忆化，但是我们是开不下 $H\times W$的数组的，因此我们得另寻出路。  

$\ \ \ \ $考虑在加入了线段树这个优化后，我们在每个点会有点坐标与到达这个点是纵向还是横向到达的，因此我们以方向和横坐标 $\texttt{or}$ 纵坐标作为下标开 $map$，这样我们就可以开下数组了。 ~~（STL大法吼）~~  

$\ \ \ \ $至此,我们可以通过全部子任务。  

------------
#### 代码 
```cpp
#include <map>
#include <cstdio>
#include <algorithm>
#define ls p<<1//个人的宏定义习惯，但容易拖慢速度，不建议使用
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define ll long long
using namespace std;
int NS[500005],EW[500005];
int a[500005];
int n,m,q;
struct Seg{
	int tr[2000005];
	void push_up(int p){tr[p]=max(tr[ls],tr[rs]);}
	void build(int p,int l,int r,int arr[])
	{
		if(l==r)
		{
			tr[p]=arr[l];
			return;
		}
		int mid=(l+r)>>1;
		build(lson,arr);build(rson,arr);
		push_up(p);
	}
	int queryL(int p,int l,int r,int k,int v)//在k左边且值大于v的第一个下标 
	{
		if(l>=k||tr[p]<=v) return 0;
		if(l==r) return l;
		int mid=(l+r)>>1;
		int index=queryL(rson,k,v);
		if(index) return index;
		else return queryL(lson,k,v);
	}
	int queryR(int p,int l,int r,int k,int v)//在k右边且值大于v的第一个下标 
	{
		if(r<=k||tr[p]<=v) return 0;
		if(l==r) return l;
		int mid=(l+r)>>1;
		int index=queryR(lson,k,v);
		if(index) return index;
		else return queryR(rson,k,v);
	}
}h,z;
map <int,ll> M[2][50005];
ll dfs(int x,int y,int dir)//dir=1代表从南北到达这个路口且往东西走，否则是从东西到达这个路口且往南北走
{
	if(M[dir][x][y]) return M[dir][x][y];
	ll tmp=0;
	if(!dir)
	{
		int L=z.queryL(1,1,n,x,NS[y]),R=z.queryR(1,1,n,x,NS[y]);
		if(L) tmp=max(tmp,(ll)x-L+dfs(L,y,1));
		else tmp=max(tmp,(ll)x-1);
		if(R) tmp=max(tmp,(ll)R-x+dfs(R,y,1));
		else tmp=max(tmp,(ll)n-x);
	}
	else
	{
		int D=h.queryL(1,1,m,y,EW[x]),U=h.queryR(1,1,m,y,EW[x]);
		if(D) tmp=max(tmp,(ll)y-D+dfs(x,D,0));
		else tmp=max(tmp,(ll)y-1);
		if(U) tmp=max(tmp,(ll)U-y+dfs(x,U,0));
		else tmp=max(tmp,(ll)m-y);
	}
	return M[dir][x][y]=tmp;
}
int main() {
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1;i<=n;i++) scanf("%d",&EW[i]);
	for(int i=1;i<=m;i++) scanf("%d",&NS[i]);
	h.build(1,1,m,NS);z.build(1,1,n,EW);
	for(int i=1,x,y;i<=q;i++)
	{
		scanf("%d %d",&x,&y);
		printf("%lld\n",max(dfs(x,y,1),dfs(x,y,0)));//起始点所有方向都可以
	}
	return 0;
}
```  
----
#### 最后  
$\ \ \ \ $你谷现在交不了 AT，因此代码没有在洛谷上的通过记录，但一定是可以通过的。  
$\ \ \ \ $~~另外同机房有一位大佬硬生生每次查询都清空了map，竟然能跑过，但是捞了个最劣解，具体哪个OJ就不说了。awa~~

---

## 作者：5k_sync_closer (赞：9)

对于一个矩形，已知其四边上**不考虑其内部道路**的所有答案，考虑其中车流指数最大的道路。

![](https://cdn.luogu.com.cn/upload/image_hosting/q9y7cl4x.png)

如图，红线为矩形中车流指数最大的道路，

两端点 $(k,s),(k,t)$ **不考虑矩形中内部道路**的答案分别为 $x,y$，

则 $\forall i\in[s,t]$，可以确定 $(k,i)$ 的答案为 $\max\{x+i-s,y+t-i\}$。

若所询问的点在红线上，则可以返回答案，否则向所询问的点所在的子矩形递归。

![](https://cdn.luogu.com.cn/upload/image_hosting/a5hn2ps9.png)

设所询问的点在上半个子矩形中。

如图，蓝线为子矩形中车流指数最大的道路，

端点 $(s',k')$ 在黑线上，已知**不考虑子矩形中内部道路**的答案，

端点 $(t',k')$ 在红线上，**不考虑子矩形中内部道路**的答案为 $\max\{x+t'-s,y+t-t'\}$。

若所询问的点在蓝线上，则可以返回答案，否则向所询问的点所在的子矩形递归。

特别地，最初整个矩形四边上**不考虑其内部道路**的所有答案为 $0$。

而且题目中有：

>移动开始时，可以任意选择方向。

所以需要考虑开始时的移动方向，递归终止时如果不满足此时枚举的方向需要继续递归。

用 ST 表维护子矩形中车流指数最大的道路。

容易发现最坏情况下最多递归 $H+W$ 层，所以复杂度为 $O(Q(H+W))$。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct S
{
    int s, t;
    long long x, y;
    bool v;
} a[50050], b[50050];
int n, m, q, x, y;
long long s;
struct T
{
    int n;
    pair<int, int> a[20][50050];
    void B(int _)
    {
        n = _;
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[0][i].first), a[0][i].second = i;
        for (int i = 1; 1 << i <= n; ++i)
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
                a[i][j] = max(a[i - 1][j], a[i - 1][j + (1 << i - 1)]);
    }
    pair<int, int> Q(int x, int y)
    {
        if (x > y)
            return {0, 0};
        int k = __lg(y - x + 1);
        return max(a[k][x], a[k][y - (1 << k) + 1]);
    }
} X, Y;
long long D(int s1, int s2, int t1, int t2, int k1, int k2, int f, int g)
{
    auto P = X.Q(s1 + (f >> 0 & 1), t1 - (f >> 1 & 1)),
         Q = Y.Q(s2 + (f >> 2 & 1), t2 - (f >> 3 & 1));
    int x = P.second, y = Q.second;
    if (P > Q)
    {
        a[x] =
            {s2, t2,
             b[s2].v ? max(b[s2].x + x - b[s2].s, b[s2].y + b[s2].t - x) : 0,
             b[t2].v ? max(b[t2].x + x - b[t2].s, b[t2].y + b[t2].t - x) : 0,
             1};
        if (k1 == x)
        {
            if (g == 0)
                return D(s1, s2, x, t2, k1, k2, f | 2, g);
            if (g == 1)
                return D(x, s2, t1, t2, k1, k2, f | 1, g);
            if (g == 2)
                return a[x].x + k2 - s2;
            if (g == 3)
                return a[x].y + t2 - k2;
        }
        if (k1 > x)
            return D(x, s2, t1, t2, k1, k2, f | 1, g);
        if (k1 < x)
            return D(s1, s2, x, t2, k1, k2, f | 2, g);
    }
    if (P < Q)
    {
        b[y] =
            {s1, t1,
             a[s1].v ? max(a[s1].x + y - a[s1].s, a[s1].y + a[s1].t - y) : 0,
             a[t1].v ? max(a[t1].x + y - a[t1].s, a[t1].y + a[t1].t - y) : 0,
             1};
        if (k2 == y)
        {
            if (g == 0)
                return b[y].x + k1 - s1;
            if (g == 1)
                return b[y].y + t1 - k1;
            if (g == 2)
                return D(s1, s2, t1, y, k1, k2, f | 8, g);
            if (g == 3)
                return D(s1, y, t1, t2, k1, k2, f | 4, g);
        }
        if (k2 > y)
            return D(s1, y, t1, t2, k1, k2, f | 4, g);
        if (k2 < y)
            return D(s1, s2, t1, y, k1, k2, f | 8, g);
    }
}
void F(int x, int y, int g)
{
    for (int i = 1; i <= n; ++i)
        a[i].v = 0;
    for (int i = 1; i <= m; ++i)
        b[i].v = 0;
    s = max(s, D(1, 1, n, m, x, y, 0, g));
}
signed main()
{
    scanf("%d%d%d", &n, &m, &q);
    X.B(n);
    Y.B(m);
    while (q--)
    {
        scanf("%d%d", &x, &y);
        s = 0;
        if (x != 1)
            F(x, y, 0);
        if (x != n)
            F(x, y, 1);
        if (y != 1)
            F(x, y, 2);
        if (y != m)
            F(x, y, 3);
        printf("%lld\n", s);
    }
    return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：1)

# JOISC2017J 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2017_j)

**题目大意**

> 给一个 $n\times m$ 的网格图，每行每列分别有权值。
>
> 你可以以如下方式在网格图上运动：
>
> - 起始时任选方向。
> - 当到达一个交点时：
>   - 若直走权值大于转弯权值，那么直走，如果前方是边界则结束运动。
>   - 否则选一种方向转向。
>
> $q$ 次询问从 $(s,t)$ 出发的最长运动距离。
>
> 数据范围：$n,m\le 5\times 10^4,q\le 100$。

**思路分析**

直接记搜 $dp(i,j,d)$ 表示到达第 $(i,j)$ 行接下来方向为 $j$ 的最长路，用 ST 表快速求下一个转向的位置。

对于每个询问，把拓展到的点围成一个矩形，显然在矩形内部的路径一定会走到矩形上的并转向。

而矩形内的点只要 $\mathcal O(1)$ 步走到矩形边界上，因此最终态就是矩形面积和为 $\mathcal O(n^2)$ 级别。

显然每个矩形进行一次搜索就会使得长或宽增加至少 $1$，并且一定是交替增加长和宽的。

因此每个矩形拓展 $\dfrac n{\sqrt q}$ 步后，矩形周长为 $\mathcal O\left(\dfrac n{\sqrt q}\right)$ 级别，这一部分总拓展次数为 $\mathcal O(n\sqrt q)$，接下来每一次拓展都会使得矩形面积和增加至少 $\mathcal O\left(\dfrac n{\sqrt q}\right)$，拓展次数为 $\mathcal O(n\sqrt q)$ 级别。

时间复杂度 $\mathcal O(n\sqrt q\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5e4+1;
struct RMQ {
	int f[MAXN][18];
	inline int bit(int x) { return 1<<x; }
	inline void build(int *a,int n) {
		for(int i=1;i<=n;++i) f[i][0]=a[i];
		for(int k=1;k<18;++k) {
			for(int i=1;i+bit(k-1)<=n;++i) {
				f[i][k]=max(f[i][k-1],f[i+bit(k-1)][k-1]);
			}
		}
	}
	inline int query(int l,int r) {
		int k=__lg(r-l+1);
		return max(f[l][k],f[r-bit(k)+1][k]);
	}
}	R,C;
int n,m,q,a[MAXN],b[MAXN];
map <tuple<int,int,int>,int> dp;
const int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
inline int dfs(int x,int y,int d) {
	//d: {U,L,D,R}
	auto T=make_tuple(x,y,d);
	if(dp.count(T)) return dp[T];
	auto valid=[&](int i,int j) { return 1<=i&&i<=n&&1<=j&&j<=m; };
	if(!valid(x+dx[d],y+dy[d])) return dp[T]=0;
	int l=1,r=max(n,m),res=0;
	auto check=[&](int k) -> bool {
		if(!valid(x+k*dx[d],y+k*dy[d])) return false;
		if(d==0) return R.query(x-k,x-1)<=b[y];
		if(d==1) return C.query(y-k,y-1)<=a[x];
		if(d==2) return R.query(x+1,x+k)<=b[y];
		if(d==3) return C.query(y+1,y+k)<=a[x];
		return 0;
	};
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) res=mid,l=mid+1;
		else r=mid-1;
	}
	int nx=x+(res+1)*dx[d],ny=y+(res+1)*dy[d];
	return dp[T]=valid(nx,ny)?max(dfs(nx,ny,d^1),dfs(nx,ny,d^3))+res+1:res;
}
signed main() {
	scanf("%lld%lld%lld",&n,&m,&q);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=m;++i) scanf("%lld",&b[i]);
	R.build(a,n),C.build(b,m);
	while(q--) {
		int x,y;
		scanf("%lld%lld",&x,&y);
		printf("%lld\n",max(max(dfs(x,y,0),dfs(x,y,2)),max(dfs(x,y,1),dfs(x,y,3))));
	}
	return 0;
}
```



---

## 作者：Purslane (赞：0)

# Solution

有趣的题目。

显然我们做的事情是：选定方向，每个十字路口如果发现另一个方向的车流量更大就转向另一个方向（注意对于边界“只能左（右）转”的限制可以直接忽视，因为不这么做显然会更劣。）

考虑找到“主干道”，也就是车流量最大的一条路。考虑一条路径，有两种情况（先看一张图片，中间红色的表示主干道）：

![](https://s21.ax1x.com/2025/04/02/pEy7bKf.png)

1. 如果路径不经过主干道，那么显然可以递归到两个小矩形中（也就是蓝色线和黑色线圈出来的部分。）
2. 如果路径经过主干道，那么一定是通过紫色的箭头走到红线上（或者，直接从红线上沿着红线出发）。之后可以选择左转或者右转（如果直接从红线上出发就不能选择了）。

所以我们维护当前分治的矩形。对于四条边维护，如果从这条边钻出去，还能最多走：$0$ 步，或者 $\max\{v_1+dis_1,v_2+dis_2\}$。

对于每个矩形，如果查询向量已经是钻出矩形的，直接返回值；否则，找到主干道——如果查询向量在主干道上，也直接返回值；否则，根据查询向量和主干道的关系，更新 $v$，并且进行新的递归。

注意到最多递归 $O(h+w)$ 层，所以复杂度为 $O((h+w)q)$。

我写的代码有点丑啊，将就着看把。。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e4+10+10;
int n,m,q,a[MAXN],b[MAXN];
pair<int,int> st1[MAXN][20],st2[MAXN][20];
pair<int,int> qur1(int l,int r) {if(l>r) return {-1,0};int k=log2(r-l+1);return max(st1[l][k],st1[r-(1<<k)+1][k]);}
pair<int,int> qur2(int l,int r) {if(l>r) return {-1,0};int k=log2(r-l+1);return max(st2[l][k],st2[r-(1<<k)+1][k]);}
int ad[4][2];
void solve(int xl,int xr,int yl,int yr,int sx,int sy,int ex,int ey,int &ans) {
	if(ey==yl) return ans=max(ans,ad[2][0]+ex-xl+1),ans=max(ans,ad[2][1]+xr-ex+1),void();
	if(ey==yr) return ans=max(ans,ad[3][0]+ex-xl+1),ans=max(ans,ad[3][1]+xr-ex+1),void();
	if(ex==xl) return ans=max(ans,ad[0][0]+ey-yl+1),ans=max(ans,ad[0][1]+yr-ey+1),void();
	if(ex==xr) return ans=max(ans,ad[1][0]+ey-yl+1),ans=max(ans,ad[1][1]+yr-ey+1),void();
	
	auto pr1=qur1(xl+1,xr-1),pr2=qur2(yl+1,yr-1);
	if(pr1.first<pr2.first) {
		int cy=pr2.second;
		int p1=max(ad[0][0]+cy-yl,ad[0][1]+yr-cy);
		int p2=max(ad[1][0]+cy-yl,ad[1][1]+yr-cy);
		p1=max(0ll,p1),p2=max(0ll,p2);
		if(sy==cy&&ey==cy) {
			if(sx>=ex) return ans=max(ans,sx-xl+p1),void();
			return ans=max(ans,xr-sx+p2),void();
		}
		if(ey<=cy) {
			ad[3][0]=p1,ad[3][1]=p2;
			ad[0][1]+=yr-cy,ad[1][1]+=yr-cy;	
			solve(xl,xr,yl,cy,sx,sy,ex,ey,ans);
		}
		else {
			ad[2][0]=p1,ad[2][1]=p2;
			ad[0][0]+=cy-yl,ad[1][0]+=cy-yl;
			solve(xl,xr,cy,yr,sx,sy,ex,ey,ans);
		}
	}
	else {
		int cx=pr1.second;
		int p1=max(ad[2][0]+cx-xl,ad[2][1]+xr-cx);
		int p2=max(ad[3][0]+cx-xl,ad[3][1]+xr-cx);
		p1=max(0ll,p1),p2=max(0ll,p2);
		if(sx==cx&&ex==cx) {
			if(sy>=ey) return ans=max(ans,sy-yl+p1),void();
			return ans=max(ans,yr-sy+p2),void();
		}
		if(ex<=cx) {
			ad[1][0]=p1,ad[1][1]=p2;
			ad[2][1]+=xr-cx,ad[3][1]+=xr-cx;	
			solve(xl,cx,yl,yr,sx,sy,ex,ey,ans);
		}
		else {
			ad[0][0]=p1,ad[0][1]=p2;
			ad[2][0]+=cx-xl,ad[3][0]+=cx-xl;
			solve(cx,xr,yl,yr,sx,sy,ex,ey,ans);
		}
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	ffor(i,1,n) cin>>a[i],st1[i][0]={a[i],i};
	ffor(i,1,m) cin>>b[i],st2[i][0]={b[i],i};
	ffor(len,1,19) for(int l=1,r=(1<<len);r<=n;l++,r++) st1[l][len]=max(st1[l][len-1],st1[l+(1<<len-1)][len-1]);
	ffor(len,1,19) for(int l=1,r=(1<<len);r<=m;l++,r++) st2[l][len]=max(st2[l][len-1],st2[l+(1<<len-1)][len-1]);
	ffor(i,1,q) {
		int x,y,ans=1;
		cin>>x>>y;
		memset(ad,-0x3f,sizeof(ad)),solve(0,n+1,0,m+1,x,y,x,y+1,ans);
		memset(ad,-0x3f,sizeof(ad)),solve(0,n+1,0,m+1,x,y,x,y-1,ans);
		memset(ad,-0x3f,sizeof(ad)),solve(0,n+1,0,m+1,x,y,x+1,y,ans);
		memset(ad,-0x3f,sizeof(ad)),solve(0,n+1,0,m+1,x,y,x-1,y,ans);
		cout<<ans-1<<'\n';
	}
	return 0;
}
```

---

## 作者：chroneZ (赞：0)

很人类智慧的一道题。

先考虑权最大的直线有什么性质：如果从这条直线上任意一点出发，沿这条直线直行，移动一定会在边界处终止。

容易发现，从起点开始，每次移动都形如从一条权较小的直线拐入一条权更大的直线，这样就形成了子问题结构。

据此考虑分治，从整个矩形开始，每次用当前矩形内权最大的直线（下文称为“当前直线”）分割矩形进行分治。不妨设这条直线是纵向的，记这条直线交当前矩形上下边界的两个交点分别为 $p_{u}, p_{d}$。

我们要考虑的是，从这条直线上的某个点出发，沿直线移动，向上 / 下移动到 $p_u$ / $p_d$ 时，还能再移动的最大距离。记 $ans_u$ 表示以 $p_u$ 为起点时，沿上边界直行的答案，$ans_d$ 同理。特别地，如果上 / 下边界对应的直线没有在之前的分治过程中出现过（即上 / 下边界对应的直线的权小于当前直线的权），那么将 $ans_u$ / $ans_d$ 应该视为 $0$。则从直线上的点 $x$ 出发，答案为 $\max(ans_u + x - p_u, ans_d + p_d - x)$。

这样一来，先钦定从询问点出发时的方向（左 / 右 / 上 / 下），从整个矩形开始分治，如果询问点与分治到的直线相交，且直线与钦定的出发方向一致，则可以返回答案；否则向询问点所在的子矩形分治。这样一来递归层数最劣 $\mathcal{O}(H + W)$。

需要注意的是如何记录 $ans_u, ans_d$。可以发现只需要对每条直线记录 $p_u, p_d$ 及对应的 $ans_u, ans_d$ 的值，在需要用到直线上一点 $x$ 的点值时直接计算即可。具体实现上，在递归过程中用矩形边界对应的直线交该层直线的交点处的点值，作为当前层的 $ans_u$ / $ans_d$ 即可。

如果用 ST 表查询区间最大值，可以做到每层分治 $\mathcal{O}(1)$。总时间复杂度为 $\mathcal{O}(H \log H + W \log W + Q(H + W))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 5e4 + 10, M = 16;

struct line {
	i64 w, lans, rans, l, r; int vis;
	inline i64 Q(int x) {return (vis ? max(x - l + lans, r - x + rans) : 0);}
} a[N], b[N];

struct ST {
	int l2[N];
	pair<int, int> a[M][N];
	inline void build(line arr[], int n) {
		for(int i = 1; i <= n; i++) {
			a[0][i] = {arr[i].w, i};
		}
		for(int i = 1; i < M; i++) {
			for(int j = 1; j + (1 << i) - 1 <= n; j++) {
				a[i][j] = max(a[i - 1][j], a[i - 1][j + (1 << i - 1)]);
			}
		}
		l2[1] = 0;
		for(int i = 2; i <= n; i++) {
			l2[i] = l2[i >> 1] + 1;
		}
	}
	inline pair<int, int> query(int l, int r) {
		if(r < l) return {0, 0};
		int p = l2[r - l + 1];
		return max(a[p][l], a[p][r - (1 << p) + 1]);
	}
} A, B;

int n, m;
i64 solve(int hl, int hr, int wl, int wr, int qx, int qy, int dir, int S) {
	// S 用以标记矩形的四个边界是否已经作为最大直线分割过
	int tl = hl, tr = hr; tl += (S >> 2 & 1), tr -= (S >> 3 & 1);
	pair<int, int> x = A.query(tl, tr);
	tl = wl, tr = wr; tl += (S & 1), tr -= (S >> 1 & 1);
	pair<int, int> y = B.query(tl, tr);
	if(x > y) {
		int p = x.second;
		auto &[w, lans, rans, l, r, vis] = a[p];
		vis = 1; lans = b[wl].Q(p), rans = b[wr].Q(p), l = wl, r = wr;
		if(p == qx) {
			if(dir == 1) return a[p].lans + qy - a[p].l;
			if(dir == 2) return a[p].rans + a[p].r - qy;
			if(dir == 3) return solve(hl, p, wl, wr, qx, qy, dir, S | 8);
			if(dir == 4) return solve(p, hr, wl, wr, qx, qy, dir, S | 4);
		}
		if(qx < p) return solve(hl, p, wl, wr, qx, qy, dir, S | 8);
		if(p < qx) return solve(p, hr, wl, wr, qx, qy, dir, S | 4);
	} else {
		int p = y.second;
		auto &[w, lans, rans, l, r, vis] = b[p];
		vis = 1; lans = a[hl].Q(p), rans = a[hr].Q(p), l = hl, r = hr;
		if(p == qy) {
			if(dir == 1) return solve(hl, hr, wl, p, qx, qy, dir, S | 2);
			if(dir == 2) return solve(hl, hr, p, wr, qx, qy, dir, S | 1);
			if(dir == 3) return b[p].lans + qx - b[p].l;
			if(dir == 4) return b[p].rans + b[p].r - qx;
		}
		if(qy < p) return solve(hl, hr, wl, p, qx, qy, dir, S | 2);
		if(p < qy) return solve(hl, hr, p, wr, qx, qy, dir, S | 1);
	}
}

i64 calc(int x, int y, int dir) {
	for(int i = 1; i <= n; i++) a[i].vis = 0;
	for(int i = 1; i <= m; i++) b[i].vis = 0;
	return solve(1, n, 1, m, x, y, dir, 0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	int q; cin >> n >> m >> q;
	for(int i = 1; i <= n; i++) {
		cin >> a[i].w;
	}
	for(int i = 1; i <= m; i++) {
		cin >> b[i].w;
	}
	A.build(a, n); B.build(b, m);
	while(q--) {
		int x, y; cin >> x >> y;
		i64 ans = 0;
		if(y != 1) ans = max(ans, calc(x, y, 1));
		if(y != m) ans = max(ans, calc(x, y, 2));
		if(x != 1) ans = max(ans, calc(x, y, 3));
		if(x != n) ans = max(ans, calc(x, y, 4));
		cout << ans << "\n";
	}
}
```

---

