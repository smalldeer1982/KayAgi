# Labyrinth Adventures

## 题目描述

有一个 $n\times n$ 的方格图，坐标编号类似平面直角坐标系，左下角为 $(1, 1)$。

这个方格图被分成了 $n$ 层，左下角 $(1, 1)$ 为第一层，随后每层都向外拓展一圈，如下图就是 $n=5$ 的时候的情况：

![](https://espresso.codeforces.com/003bbba1ff0347bde56714b878262c5fe414679d.png)

层与层之间有墙隔开，但每层都有两个门，分别分布在该层顶部和右侧，门是双向的。

现在给出这些门的坐标，有 $m$ 次询问，每次给定两个坐标 $(x_1, y_1)$ 和 $(x_2,y_2)$，请你回答两点之间的最短路。

## 说明/提示

$1 \le n \le 10^5$；

$2 \le m \le 2 \times 10^5$。

## 样例 #1

### 输入

```
2
1 1 1 1
10
1 1 1 1
1 1 1 2
1 1 2 1
1 1 2 2
1 2 1 2
1 2 2 1
1 2 2 2
2 1 2 1
2 1 2 2
2 2 2 2```

### 输出

```
0
1
1
2
0
2
1
0
1
0```

## 样例 #2

### 输入

```
4
1 1 1 1
2 1 2 2
3 2 1 3
5
2 4 4 3
4 4 3 3
1 2 3 3
2 2 4 4
1 4 2 3```

### 输出

```
3
4
3
6
2```

# 题解

## 作者：FelFa_1414666 (赞：5)

## 分析

图中矩阵被分为了 $n$ 层，不难看出：

>  同一层中任意两个位置之间的最短路都是它们的曼哈顿距离 ($|x_1-x_2|+|y_1-y_2|$)。这个距离一定是最优的。也就是说要去同一层中另一个位置，绕到别的层肯定不会更优。

我们假设每次都是从较低的层走到较高的层，每次移动最多只能向上一层，结合上面结论，我们可以得出:

> 每一次移动一定是在当前层中移动或向上一层，不可能向下走。

$n$ 是 $10^5$ 级别的，肯定不能将图中每个位置存下来，因为层与层之间只有两个固定入口相同（暂且称之为门）。所以如果我们要从第 $i$ 层某位置 走到第 $j$ 层某位置，一定要先到第 $i$ 层的一个门，向上走到第 $j-1$ 层的一个门，再上到第 $j$ 层走到终点。起点和终点部分的曼哈顿距离可以直接计算，所以只要记录**门与门之间的最短路**即可。而门的数量是 $\operatorname O(n)$ 的。

---

## 解法 1

考虑用朴素的方法求解最短路。$dist_{i,j,0/1,0/1}$ 表示以第 $i$ 层某个门作为起点，到第 $j$ 层某个门的最短路。每次询问都要固定起点完整跑一遍，单次复杂度达到 $\operatorname O(n)$。

我们可以用**倍增算法**优化这个问题。设 $dist_{i,j,0/1,0/1}$ 表示以第 $i$ 层某个门作为起点，到第 $i+2^j$ 层某个门的最短路。这样对于单个起点，跑一遍最短路的复杂度是 $\operatorname O(\log n)$，每次询问都可以把原区间分解成不超过 $\log n$ 个已知区间求解。

转化成多个区间后，维护 $dp_{i,0/1}$ 表示考虑到第 $i$ 个区间，当前层的 $0/1$ 号门到起点的距离，处理出终点的距离即可。

- 时间复杂度：$\operatorname O(n\log n)$
- 空间复杂度：$\operatorname O(n\log n)$

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
#define y1 woshishabi
using namespace std;
const ll INF=1000000000000000008;
int n,m,lg[100005],to[100005][25];
ll x[100005][2],y[100005][2],dist[100005][25][2][2];
ll dis(ll x1,ll y1,ll x2,ll y2)//曼哈顿距离
{
	return abs(x1-x2)+abs(y1-y2);
}
ll solve(int s,int k1,int g,int k2)//求两个门之间的距离
{
	ll dp[2][2];
	dp[0][k1]=0;
	dp[0][k1^1]=dis(x[s][k1],y[s][k1],x[s][k1^1],y[s][k1^1]);
	int cur=s,pre=0,now=1;
	for(int i=lg[g-s]-1;i>=0;i--)//分解成多个区间
		if (to[cur][i]<=g)
		{
			for(int k=0;k<2;k++)
				dp[now][k]=min(dp[pre][0]+dist[cur][i][0][k],dp[pre][1]+dist[cur][i][1][k]);
			cur=to[cur][i];
			swap(pre,now);
		}
	return dp[pre][k2];
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	for(int i=0;i<n-1;i++)
		cin>>x[i][0]>>y[i][0]>>x[i][1]>>y[i][1],--x[i][0],--x[i][1],--y[i][0],--y[i][1];
	for(int i=1;i<=n;i++)//倍增的常数优化
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	memset(to,0x3f,sizeof(to));
	memset(dist,0x3f,sizeof(dist));
	for(int i=0;i<n;i++)
	{
		to[i][0]=i+1;
		for(int j=0;j<2;j++)
		{
			dist[i][0][0][j]=dis(x[i][0]+1,y[i][0],x[i+1][j],y[i+1][j])+1;
			dist[i][0][1][j]=dis(x[i][1],y[i][1]+1,x[i+1][j],y[i+1][j])+1;
		}
	}
	for(int i=n-1;i>=0;i--)//预处理倍增数组
		for(int j=1;j<=lg[n-1-i];j++)
		{
			to[i][j]=to[to[i][j-1]][j-1];
			for(int k=0;k<2;k++)
			for(int l=0;l<2;l++)
				dist[i][j][k][l]=min(dist[i][j-1][k][0]+dist[to[i][j-1]][j-1][0][l],
				dist[i][j-1][k][1]+dist[to[i][j-1]][j-1][1][l]);
		}
	cin>>m;
	while(m--)
	{
		int sx,sy,gx,gy;
		cin>>sx>>sy>>gx>>gy;--sx,--sy,--gx,--gy;
		int sid=max(sx,sy),gid=max(gx,gy);//起始点所在层
		if (sid>gid)
			swap(sid,gid),swap(sx,gx),swap(sy,gy);
		if (sid==gid)
			cout<<dis(sx,sy,gx,gy)<<endl;
		else
		{
			ll ans=INF;
			for(int k=0;k<2;k++)//枚举起始层分别走哪个门，求最小答案
				ans=min(ans,min(dis(sx,sy,x[sid][k],y[sid][k])+solve(sid,k,gid-1,0)+1+dis(x[gid-1][0]+1,y[gid-1][0],gx,gy),
				dis(sx,sy,x[sid][k],y[sid][k])+solve(sid,k,gid-1,1)+1+dis(x[gid-1][1],y[gid-1][1]+1,gx,gy)));
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## Solution 2

除了倍增，还有一种数据结构可以把大区间分解成不超过 $\log n$ 个小区间求解最短路。当然是通过**线段树**。

线段树上每个节点维护一个区间 $[l,r]$，里面储存第 $l$ 层的每个门到第 $r$ 层每个门的最短路。每个大区间是左右两个相邻子区间合并的结果。而相邻区间的合并则要枚举中间进出哪个门来求最小距离。每次询问一个区间，就在线段树上分解为不超过 $\log n$ 个区间，将他们按顺序合并得到要求的门与门距离。

时间复杂度：$\operatorname O(n\log n)$

空间复杂度： $\operatorname O(n)$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
#define y1 IronManSucks
using namespace std;
const ll INF=1000000000000000008;
int n,m;
ll x[100005][2],y[100005][2];
ll dis(ll x1,ll y1,ll x2,ll y2)//曼哈顿距离
{
	return abs(x1-x2)+abs(y1-y2);
}
struct node//线段树节点
{
	int l,r;
	ll d[2][2];//门与门之间最短路
	bool flag;
	node(){
		l=r=flag=0;
		memset(d,0,sizeof(d));
	}
	node operator+(node &b){//区间合并
		if (flag)return b;//如果当前一个区间为空，则合并结果为另一个区间
		if (b.flag)return *this; 
		node c;
		c.l=l,c.r=b.r;
		for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
		{
			c.d[i][j]=INF;
			for(int k=0;k<2;k++)//枚举中间进出的门
				c.d[i][j]=min(c.d[i][j],min(d[i][0]+1+dis(x[r][0]+1,y[r][0],x[r+1][k],y[r+1][k])+b.d[k][j],
				d[i][1]+1+dis(x[r][1],y[r][1]+1,x[r+1][k],y[r+1][k])+b.d[k][j]));
		}
		return c;
	}
};
struct segtree//非递归线段树
{
	node seg[200005];
	void build()//建树
	{
		for(int i=0;i<n;i++)//初始化单个节点的区间
		{
			seg[i+n].l=seg[i+n].r=i;
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					seg[i+n].d[j][k]=dis(x[i][j],y[i][j],x[i][k],y[i][k]);
		}
		for(int i=n-1;i>0;i--)//合并子区间
			seg[i]=seg[i<<1]+seg[i<<1|1];
	}
	node query(int l,int r)//区间查询
	{
		node resl,resr;//从左端和右端两边开始合并的答案
		resl.flag=resr.flag=1;
		for(l+=n,r+=n;l<r;l>>=1,r>>=1)
		{
			if (l&1) resl=resl+seg[l++];
			if (r&1) resr=seg[--r]+resr;
		}
		return resl+resr;
	}
}t;
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	for(int i=0;i<n-1;i++)
		for(int j=0;j<2;j++)
			cin>>x[i][j]>>y[i][j],--x[i][j],--y[i][j];
	t.build();
	cin>>m;
	while(m--)
	{
		int sx,sy,gx,gy;
		cin>>sx>>sy>>gx>>gy;--sx,--sy,--gx,--gy;
		int sid=max(sx,sy),gid=max(gx,gy);
		if (sid>gid)
			swap(sx,gx),swap(sy,gy),swap(sid,gid);
		if (sid==gid)
			cout<<dis(sx,sy,gx,gy)<<endl;
		else
		{
			node res=t.query(sid,gid);
			ll ans=INF;
			for(int i=0;i<2;i++)
				ans=min(ans,min(dis(sx,sy,x[sid][i],y[sid][i])+res.d[i][0]+1+dis(x[gid-1][0]+1,y[gid-1][0],gx,gy),
				dis(sx,sy,x[sid][i],y[sid][i])+res.d[i][1]+1+dis(x[gid-1][1],y[gid-1][1]+1,gx,gy)));
			cout<<ans<<endl;		
		}	
	}
	return 0;
}
```

另：关于我的非递归线段树，如果理解不了的可以见 codeforces 的这篇 blog。[传送门](https://codeforces.com/blog/entry/18051)。



---

## 作者：JWRuixi (赞：4)

~~线段树常数和码量均吊打倍增????~~

- 题意

有一个 $n \times n$ 的网格图，坐标编号类似平面直角坐标系，左下角 $(1,1)$。

这个方格图被分成了 $n$ 层，格子 $(i,j)$ 在第 $max(i,j)$ 层。层与层之间有墙隔开，但每层都有两个门，分别分布在该层顶部和右侧，门是双向的。

给出所有门的坐标，$m$ 次询问，每次询问两个格子 $(x_1,y_1)$ 和 $(x_2,y_2)$ 间的最短路。

$n\le 10^5,m\le 2\times10^5$。

![](https://espresso.codeforces.com/522ad0e61c0b740a60c9203c9178279992c8ab2e.png)

- 分析

定义 $d(x,y)$ 为点 $(x,y)$ 所在的层。

不妨假设 $d(x_1,y_1)\le d(x_2,y_2)$，不难将整个走的过程分解成三个部分：
1. 从 $(x_1,y_1)$ 走到位于 $d(x_1,y_1)$ 这一层的一个门，定为入口。
2. 从入口走到位于 $d(x_2,y_2)-1$ 的一个门，定为出口。
3. 从出口走到 $(x_2,y_2)$。

考虑如何计算三个部分：
1. 因为处于同一层，所以直接计算 $|x_1-x_s|+|y_1-y_s|$ 即可。
2. 考虑 dp，设 $f_{i,0/1}$ 表示走到第 $i$ 层的第 $1/2$ 个门的最短路，直接转移即可。
3. 同上，直接计算 $|x_2-x_t|+|y_2-y_t|$ 即可。

直接做的复杂度使 $\mathcal O(nm)$ 的，但是不难发现第 $2$ 部分的计算有着大量的重复，且形式类似于矩阵乘法，考虑用动态 dp 优化。

设 $\text{dis}(o_1,o_2)$ 表示当前层从 $o_1$ 号门走到 $o_2$ 号门的距离，则可以设计出转移矩阵（方程）。

$$\begin{bmatrix}f_{i,0}&f_{i,1}\end{bmatrix}\begin{bmatrix}dis(0,0)&dis(0,1)\\dis(1,0)&dis(1,1)\end{bmatrix}=\begin{bmatrix}f_{i+1,0}&f_{i+1,1}\end{bmatrix}$$

于是做到这里我们就做完了！可以用倍增或者线段树直接维护就可以了，~~如果加上修改的话好像就只能线段树了~~，实测线段树常数更小……

最后的时间复杂度 $\mathcal O(n\log n + m)$ 或 $\mathcal O((n+m)\log n)$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define int long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(1e5 + 500);
int n, m;
pii d[maxn][2];

struct Matrix {
	int g[2][2];
	Matrix () { memset(g, 0, sizeof(g)); }
	inline Matrix operator * (const Matrix &rhs) const {
		Matrix res;
		res.g[0][0] = min(g[0][0] + rhs.g[0][0], g[0][1] + rhs.g[1][0]);
		res.g[0][1] = min(g[0][0] + rhs.g[0][1], g[0][1] + rhs.g[1][1]);
		res.g[1][0] = min(g[1][0] + rhs.g[0][0], g[1][1] + rhs.g[1][0]);
		res.g[1][1] = min(g[1][0] + rhs.g[0][1], g[1][1] + rhs.g[1][1]);
		return res;
	}
} a[maxn], o;

struct SGT {
	Matrix tr[maxn << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
	inline void pushup (int p) {
		tr[p] = tr[ls] * tr[rs];
	}
	inline void build (int l, int r, int p) {
		if (l == r) return tr[p] = a[l], void();
		const int mid = (l + r) >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		pushup(p);
	}
	inline Matrix qry (int s, int t, int l, int r, int p) {
		if (s <= l && r <= t) return tr[p];
		const int mid = (l + r) >> 1;
		if (t <= mid) return qry(s, t, l, mid, ls);
		else if (mid < s) return qry(s, t, mid + 1, r, rs);
		else return qry(s, t, l, mid, ls) * qry(s, t, mid + 1, r, rs);
	}
} T;

inline int dis (pii a, pii b) {
	return abs(a.fi - b.fi) + abs(a.se - b.se);
}

signed main () {
	n = read();
	for (int i = 1; i < n; i++) d[i][0] = {read(), read()}, d[i][1] = {read(), read()};
	m = read();
	for (int i = 1; i < n; i++) {
		pii t[2] = {{d[i][0].fi + 1, d[i][0].se}, {d[i][1].fi, d[i][1].se + 1}};
		a[i].g[0][0] = dis(t[0], d[i + 1][0]) + 1;
		a[i].g[0][1] = dis(t[0], d[i + 1][1]) + 1;
		a[i].g[1][0] = dis(t[1], d[i + 1][0]) + 1;
		a[i].g[1][1] = dis(t[1], d[i + 1][1]) + 1;
	}
	T.build(1, n - 1, 1);
	while (m--) {
		pii a = {read(), read()}, b = {read(), read()};
		int da = max(a.fi, a.se), db = max(b.fi, b.se);
		if (da > db) swap(da, db), swap(a, b);
		if (da == db) {
			write(dis(a, b)), puts("");
			continue;
		}
		Matrix res;
		res.g[0][0] = dis(a, d[da][0]), res.g[0][1] = dis(a, d[da][1]);
		if(db - da > 1) res = res * T.qry(da, db - 2, 1, n - 1, 1);
		pii t[2] = {{d[db - 1][0].fi + 1, d[db - 1][0].se}, {d[db - 1][1].fi, d[db - 1][1].se + 1}};
		write(min(res.g[0][0] + dis(b, t[0]), res.g[0][1] + dis(b, t[1])) + 1), puts("");
	}
}
```

---

## 作者：rizynvu (赞：2)

能够发现这个最短路的形态一定是从低层一层一层走到高层的。

那么这就说明若起点终点对应层数为 $x, y$。  
若 $x = y$ 则直接算，就是曼哈顿距离。  
否则不妨钦定 $x < y$（不满足就交换，不影响结果），那么层数 $z\in [x, y)$ 的其中一个门肯定都会被经过。

于是考虑把 $\operatorname{dis}((x_1, y_1), (x_2, y_2))$ 拆成到同一层两个门的距离的和的最小值。  
记在路径之中经过的其中一层的两个门为 $(x_3, y_3), (x_4, y_4)$，那么就可以拆成 $\min\{\operatorname{dis}((x_1, y_1), (x_3, y_3)) + \operatorname{dis}((x_3, y_3), (x_2, y_2)), \operatorname{dis}((x_1, y_1), (x_4, y_4)) + \operatorname{dis}((x_4, y_4), (x_2, y_2))\}$。  

同时对于 $\operatorname{dis}((x_1, y_1), (x_3, y_3))$ 也可以继续拆下去。  
记 $(x_1, y_1)$ 所在层的两个门为 $(x_5, y_5), (x_6, y_6)$，那么可以类似的拆为 $\min\{\operatorname{dis}((x_1, y_1), (x_5, y_5)) + \operatorname{dis}((x_5, y_5), (x_3, y_3)), \operatorname{dis}((x_1, y_1), (x_6, y_6)) + \operatorname{dis}((x_6, y_6), (x_3, y_3))\}$。

对于 $\operatorname{dis}((x_1, y_1), (x_5, y_5))$ 因为同层关系就是好算的了。

于是能够发现只需要知道门的最短路距离就可以得到答案了。

但是考虑到门的个数还是 $\mathcal{O}(n)$ 的，直接跑还是不太行。  
但是注意到每次询问对应的是一个区间，于是可以考虑分治。

具体的，考虑处理到 $[l, r]$，那么记 $m = \lfloor\frac{l + r}{2}\rfloor$。  
考虑就以 $m$ 层的门为起点，跑出与其他 $[l, r]$ 层内的门的最短路。  
那么对于一个层数在 $[x, y](l\le x\le y\le r)$ 的询问，若这个层数跨过了 $m$ 层的门，即 $x\le m < y$，那么就可以在此统计贡献了。

对于还没有统计到的询问，考虑分成两部分 $[l, m], (m, r]$，继续递归下去处理。

时间复杂度 $\mathcal{O}((n + q)\log n)$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
constexpr ll inf = 1e18;
constexpr inline int dis(int x1, int y1, int x2, int y2) {
   return abs(x1 - x2) + abs(y1 - y2);
}
constexpr inline int dep(int x, int y) {
   return std::max(x, y);
}
using Z = std::tuple<int, int, int, int, int>;
constexpr int maxn = 1e5 + 10, maxm = 2e5 + 10;
int dx[maxn][2], dy[maxn][2];
ll ans[maxm];
ll f[2][maxn][2];
inline void solve(int l, int r, std::vector<Z> qry) {
   if (l >= r) return ;
   int mid = l + r >> 1;
   for (int op : {0, 1}) {
      auto d = f[op];
      d[mid][op] = 0, d[mid][op ^ 1] = dis(dx[mid][0], dy[mid][0], dx[mid][1], dy[mid][1]);
      for (int i = mid - 1; i >= l; i--) {
         d[i][0] = 1ll + std::min(d[i + 1][0] + dis(dx[i][0] + 1, dy[i][0], dx[i + 1][0], dy[i + 1][0]), 
                                  d[i + 1][1] + dis(dx[i][0] + 1, dy[i][0], dx[i + 1][1], dy[i + 1][1]));
         d[i][1] = 1ll + std::min(d[i + 1][0] + dis(dx[i][1], dy[i][1] + 1, dx[i + 1][0], dy[i + 1][0]),
                                  d[i + 1][1] + dis(dx[i][1], dy[i][1] + 1, dx[i + 1][1], dy[i + 1][1]));
      }
      for (int i = mid + 1; i < r; i++) {
         d[i][0] = 1ll + std::min(d[i - 1][0] + dis(dx[i - 1][0] + 1, dy[i - 1][0], dx[i][0], dy[i][0]),
                                  d[i - 1][1] + dis(dx[i - 1][1], dy[i - 1][1] + 1, dx[i][0], dy[i][0]));
         d[i][1] = 1ll + std::min(d[i - 1][0] + dis(dx[i - 1][0] + 1, dy[i - 1][0], dx[i][1], dy[i][1]),
                                  d[i - 1][1] + dis(dx[i - 1][1], dy[i - 1][1] + 1, dx[i][1], dy[i][1]));
      }
   }
   std::vector<Z> qryL, qryR;
   for (auto [x1, y1, x2, y2, id] : qry) {
      int dep1 = dep(x1, y1), dep2 = dep(x2, y2);
      if (dep1 <= mid && mid < dep2) {
         ans[id] = inf;
         for (int op : {0, 1}) {
            auto d = f[op];
            ll d1 = std::min(d[dep1][0] + dis(x1, y1, dx[dep1][0], dy[dep1][0]), 
                             d[dep1][1] + dis(x1, y1, dx[dep1][1], dy[dep1][1]));
            ll d2 = std::min(d[dep2 - 1][0] + dis(x2, y2, dx[dep2 - 1][0] + 1, dy[dep2 - 1][0]),
                             d[dep2 - 1][1] + dis(x2, y2, dx[dep2 - 1][1], dy[dep2 - 1][1] + 1));
            ans[id] = std::min(ans[id], 1ll + d1 + d2);
         }
      } else if (dep2 <= mid) {
         qryL.emplace_back(x1, y1, x2, y2, id);
      } else {
         qryR.emplace_back(x1, y1, x2, y2, id);
      }
   }
   solve(l, mid, qryL), solve(mid + 1, r, qryR);
}
int main() {
   int n, m;
   scanf("%d", &n);
   for (int i = 1; i < n; i++) {
      for (int j : {0, 1}) {
         scanf("%d%d", &dx[i][j], &dy[i][j]);
      }
   }
   scanf("%d", &m);
   std::vector<Z> qry;
   for (int i = 1; i <= m; i++) {
      int qx[2], qy[2];
      scanf("%d%d%d%d", &qx[0], &qy[0], &qx[1], &qy[1]);
      if (dep(qx[0], qy[0]) == dep(qx[1], qy[1])) {
         ans[i] = dis(qx[0], qy[0], qx[1], qy[1]);
         continue;
      }
      if (dep(qx[0], qy[0]) > dep(qx[1], qy[1])) {
         std::swap(qx[0], qx[1]), std::swap(qy[0], qy[1]);
      }
      qry.emplace_back(qx[0], qy[0], qx[1], qy[1], i);
   }
   solve(1, n, qry);
   for (int i = 1; i <= m; i++) {
      printf("%lld\n", ans[i]);
   }
   return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

容易发现这题的图共有 $n$ 层，而 $i$ 层只有通往 $i+1$ 层的门和返回 $i-1$ 层的门，那么一次最短的路程一定是连续通过 $x,x+1,\ldots,y-1,y$ 层。

那么问题就变成了一段区间的最短路径，而每层门只有两个，定义 $f_{i,j,k,l}$ 表示 $i$ 层第 $k$ 个门进而 $j$ 层第 $l$ 个门进。由于每层门只有两个，于是可以直接枚举转移。而由于答案组成是区间，直接线段树维护即可。

注意比如我第 $i$ 层和第 $i+1$ 层合并，一定不能直接算两扇门的曼哈顿距离，这样是错误的，因为两个点不在同一层，而每一层是按直角分布的，所以要先转成同一层再求曼哈顿距离。

[code](https://codeforces.com/contest/1681/submission/298185120)。

---

## 作者：Jerrywang09 (赞：1)

细节非常多的题。考虑线段树维护矩阵做动态 DP。线段树区间 $[l,r]$ 的矩阵的元素 $(i,j)$ 表示从第 $l$ 层的第 $i$ 扇门出发，到达第 $r+1$ 层的第 $j$ 扇门的最短路径长度。

同层内的两个点的路径长度就是它们的曼哈顿距离，需要处理出每扇门“出门”后到下一层的哪个位置。回答询问时注意两个点在同一层或相邻层的情况。

```cpp
// Title:  Labyrinth Adventures
// Source: CF1681E
// Author: Jerrywang
#include <bits/stdc++.h>
#define int long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=100010;
using namespace std;

int n; struct site {int x, y;} a[N][2], b[N][2];
int dis(site a, site b)
{
	return abs(a.x-b.x)+abs(a.y-b.y);
}

struct mat
{
	int a[2][2];
	void O() {memset(a, 0x3f, sizeof a);}
	void E() {O(); rep(i, 0, 1) a[i][i]=0;}
};
mat operator *(mat a, mat b)
{
	mat res; res.O();
	rep(k, 0, 1) rep(i, 0, 1) rep(j, 0, 1)
		res.a[i][j]=min(res.a[i][j], a.a[i][k]+b.a[k][j]);
	return res;
}

struct node
{
	int l, r; mat a;
} t[N<<2];
#define lc p<<1
#define rc p<<1|1
void build(int p, int l, int r)
{
	t[p]={l, r};
	if(l==r)
	{
		mat &A=t[p].a;
		rep(i, 0, 1) rep(j, 0, 1)
			A.a[i][j]=dis(b[l][i], a[l+1][j])+1;
		return;
	}
	int mid=l+r>>1;
	build(lc, l, mid), build(rc, mid+1, r);
	t[p].a=t[lc].a*t[rc].a;
}
mat query(int p, int l, int r)
{
	if(l<=t[p].l && t[p].r<=r) return t[p].a;
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return query(lc, l, r);
	if(l>mid)  return query(rc, l, r);
	return query(lc, l, r)*query(rc, l, r);
}

signed main()
{
	scanf("%lld", &n);
	rep(i, 1, n-1)
	{
		scanf("%lld%lld%lld%lld", &a[i][0].x, &a[i][0].y, &a[i][1].x, &a[i][1].y);
		b[i][0]={a[i][0].x+1, a[i][0].y};
		b[i][1]={a[i][1].x, a[i][1].y+1};
	}
	build(1, 1, n-1);
	int T; scanf("%lld", &T);
	while(T--)
	{
		site s, t; scanf("%lld%lld%lld%lld", &s.x, &s.y, &t.x, &t.y);
		int l=max(s.x, s.y), r=max(t.x, t.y), res=LLONG_MAX;
		if(l==r)
		{
			printf("%lld\n", dis(s, t)); continue;
		}
		if(l>r) swap(l, r), swap(s, t);
		if(r==l+1)
		{
			rep(i, 0, 1)
				res=min(res, dis(s, a[l][i])+dis(b[l][i], t)+1);
			printf("%lld\n", res);
		}
		if(r>l+1)
		{
			mat tmp=query(1, l, r-2);
			rep(i, 0, 1) rep(j, 0, 1)
				res=min(res, dis(s, a[l][i])+tmp.a[i][j]+dis(b[r-1][j], t)+1);
			printf("%lld\n", res);
		}
	}
	
	return 0;
}
```

---

## 作者：Str_ywr (赞：1)

提供一种题解里面没有的分块写法。

首先我们定义第 $i$ 层贴的两个传送门中，上方的那个为 $(i,0)$，右边的那个为 $(i,1)$。

我们发现两个点 $x,y$ 之间的路径由三部分组成:

$1$. $x$ 走向它所在层的某一传送门 $p$。

$2$. $y$ 所在层的上一层的某个传送门 $q$ 走向 $y$。

$3$. $p$ 走向 $q$。

那么我们可以把传送门进行分块:

具体来说：

$dis_{i,j,k}$  表示从传送门 $(i,j)$ 到达传送门 $(i+1,k)$ 的长度。

预处理出，块边界的传送门到块边界的传送门之间的距离。

即 $f$ 数组，具体见代码。

对于每一次询问，可以暴力求出不完整的块，然后用 $f$ 数组得到完整的块。

复杂度：

预处理 : $O(n\sqrt{n})$。

查询 : $O(m\sqrt{n})$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ '0');
        ch = getchar();
    }
    return x * f;
}
const int N = 2e5 + 10, T = 1e3 + 10;
int len, t, L[N], R[N], pos[N];
int n, m; ll f[T][T][2][2]; //fi,j,k,l表示 从(L[i],k)号传送门 到 (R[j],l)号的传送门的最短距离 
ll dis[N][2][2];
struct Node {
	int dx[2], dy[2];
}node[N];
int getdis(int x, int y, int a, int b) {
	return abs(x - a) + abs(y - b);
}
void op(ll to[2][2], int i) {//op表示从i转移到i+1
	//toi,j表示从(起点层,i)号传送门到(终点层,j)号传送门的最短路 
	ll ton[2][2];
	for (int j = 0; j <= 1; j++) {
		for (int k = 0; k <= 1; k++) {
			ton[j][k] = min(to[j][0] + dis[i][0][k], to[j][1] + dis[i][1][k]);
		}
	}
	for (int j = 0; j <= 1; j++) {
		for (int k = 0; k <= 1; k++) {
			to[j][k] = ton[j][k];
		}
	}
}
void pre(int x) {
	int nw = x;
	ll to[2][2] = {}; to[0][1] = to[1][0] = 1e18;
	//toi,j表示从(起点层,i)号传送门到(终点层,j)号传送门的最短路 
	//一开始起点层和终点层一样， 所以0, 1和1, 0就是不合法的状态 
	for (int i = L[x]; i <= n; i++) {
		if (i == R[nw]) {
			memcpy(f[x][nw], to, sizeof to);
			nw++;
		}
		if (i < n) op(to, i);
	}
}
ll ask(int x, int y, int a, int b) {
	int l = max(x, y), r = max(a, b) - 1;
	//max(x,y)就是这个点所在的层数 
	ll to[2][2] = {}; to[0][1] = to[1][0] = 1e18;
	int p = pos[l], q = pos[r];
	if (q - p < 2) {
		for (int i = l; i < r; i++) op(to, i);
		ll ans = 1e18;
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 1; k++) {
				ans = min(ans, to[j][k] + getdis(x, y, node[l].dx[j], node[l].dy[j]) + 
				getdis(node[r].dx[k], node[r].dy[k], a, b));
			}
		}
		return ans;
	}
	//暴力预处理前面 
	for (int i = l; i < L[p+1]; i++) op(to, i);
	
	//p -> q
	ll ton[2][2];
	for (int j = 0; j <= 1; j++) {
		for (int k = 0; k <= 1; k++) {
			ton[j][k] = min(to[j][0] + f[p+1][q-1][0][k], to[j][1] + f[p+1][q-1][1][k]);
		}
	}
	for (int j = 0; j <= 1; j++) {
		for (int k = 0; k <= 1; k++) {
			to[j][k] = ton[j][k];
		}
	}
	
	//暴力预处理后面 
	for (int i = R[q-1]; i < r; i++) op(to, i);
	
	//统计最终答案 
	ll ans = 1e18; //最多到 1e10 
	for (int j = 0; j <= 1; j++) {
		for (int k = 0; k <= 1; k++) {
			ans = min(ans, to[j][k] + getdis(x, y, node[l].dx[j], node[l].dy[j]) + 
			getdis(node[r].dx[k], node[r].dy[k], a, b));
		}
	}
	return ans;
}
int main() {
	n = read(); n--; //n--是因为第n层没有传送门 
	for (int i = 1; i <= n; i++) {
		node[i].dx[0] = read() + 1, node[i].dy[0] = read(); //这里我存储的是穿过传送门以后所在的位置 
		node[i].dx[1] = read(), node[i].dy[1] = read() + 1;
	} m = read();
	len = max(1.0, ceil(n * 1.0 / (2 * sqrt(m)))); t = n / len;
	for (int i = 1; i <= t; i++) {
		L[i] = (i - 1) * len + 1;
		R[i] = i * len;
	}
	if (n % len) {
		++t; L[t] = R[t-1] + 1; R[t] = n;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 1; k++) {
				dis[i][j][k] = getdis(node[i].dx[j], node[i].dy[j], node[i+1].dx[k], node[i+1].dy[k]);
			}
		}
	}
	for (int i = 1; i <= t; i++) {
		for (int j = L[i]; j <= R[i]; j++) {
			pos[j] = i;
		}
	}
	for (int i = 1; i <= t; i++) {
		pre(i);
	}
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read(), a = read(), b = read();
		//max(x,y)就是这个点所在的层数 
		if (max(x, y) > max(a, b)) {
			swap(x, a); swap(y, b);
		} else if (max(x, y) == max(a, b)) {
			printf("%d\n", getdis(x, y, a, b)); continue;
		}
		printf("%lld\n", ask(x, y, a, b));
	}
    return 0;
}
```

~~给个赞吧~~qwq

---

## 作者：daniEl_lElE (赞：1)

## 思路

首先，我们考虑如果没有多次询问，单次询问 $(1,1)$ 到 $(n,n)$ 之间的距离怎么做。

考虑 $dp_{i,0/1}$ 表示看到第 $i$ 层，目前通过 $0/1$（代指上或右）边的通道离开第 $i$ 层最少需要走的步数，$dp_{i,0/1}=\min(dp_{i-1,0/1}+dist(a_{i-1,0/1},a_{i,0/1})+1))$，其中 $a_{i,0/1}$ 表示第 $i$ 层的 $0/1$ 通道所在位置，最后只需要求 $dp_{n-1,0/1}$ 和终点之间的距离即可，复杂度 $O(n)$。

这时，我们看到原来的，有多次询问的问题。在做有多次询问的 `DP` 题目时应该很容易序列上动态 `DP`。首先，我们将 $dp$ 状态存到矩阵中。由上面的状态转移方程我们可以将每一层的推倒变成矩阵的形式，然后做序列上动态 `DP` 即可。注意一下同层之间的点距离的计算以及在前往相邻层的步骤 $+1$ 上的问题即可。复杂度 $O(q\log n)$，即可通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define y1 abcdefg
using namespace std;//上一行注意y1。
struct mtx{//矩阵
	int a[5][5];
};
mtx mul(mtx aa,mtx bb){
	mtx ans;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=2;j++){
			ans.a[i][j]=1e18;
		}
	}
	for(int i=1;i<=2;i++){
		for(int j=1;j<=2;j++){
			for(int k=1;k<=2;k++){
				ans.a[i][j]=min(ans.a[i][j],aa.a[i][k]+bb.a[k][j]);//修改过的矩阵乘法，对所有的取min
			}
		}
	}
	return ans;
}
mtx c[200005];//初始的矩阵
struct sgt{
	mtx f[800005];
	void build(int i,int l,int r){
		if(l>r) return ;
		if(l==r){
			f[i]=c[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=mul(f[i*2],f[i*2+1]);
	}
	mtx qry(int i,int l,int r,int ql,int qr){
		if(ql>qr||l>r){
			mtx ret;
			for(int j=1;j<=2;j++) for(int k=1;k<=2;k++) ret.a[j][k]=0;
			return ret;
		}
		if(ql<=l&&qr>=r){
			return f[i];
		}
		if(ql>r||qr<l){
			mtx ret;
			for(int j=1;j<=2;j++) for(int k=1;k<=2;k++) ret.a[j][k]=0;
			return ret;
		}
		int mid=(l+r)>>1;
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		else if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		else return mul(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;//线段树板子
mtx oriv;
int tcdist(int x1,int x2,int y1,int y2){//计算同一层中两个点的距离，注意一些细节
	int levn=max(x1,y1),levm=max(x2,y2);
	if(x1==x2){
		return llabs(y2-y1);
	}
	else if(y1==y2){
		return llabs(x2-x1);
	}
	else{
		int tot=0;
		tot+=max(llabs(levn-x1),llabs(levn-y1));
		tot+=max(llabs(levm-x2),llabs(levm-y2));
		return tot; 
	}
}
signed main(){
	int n;
	cin>>n;
	int d1[n+1],d2[n+1],usl1[n+1],usl2[n+1];
	for(int i=1;i<n;i++){
		cin>>usl1[i]>>d1[i]>>d2[i]>>usl2[i];
	}
	for(int i=1;i<n-1;i++){//构造矩阵，即距离
		c[i].a[1][1]=llabs(d1[i+1]-d1[i])+1;
		c[i].a[1][2]=llabs(i+1-d1[i])+llabs(i+1-d2[i+1])+1;
		c[i].a[2][1]=llabs(i+1-d1[i+1])+llabs(i+1-d2[i])+1;
		c[i].a[2][2]=llabs(d2[i+1]-d2[i])+1;
	}
	tree.build(1,1,n-2);
	int q;
	cin>>q;
	while(q--){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		int levn=max(x1,y1),levm=max(x2,y2);
		if(levm<levn){//不知道有没有这种数据，但还是写了个
			swap(x1,x2);
			swap(y1,y2);
			swap(levn,levm);
		}
		if(levm==levn){
			cout<<tcdist(x1,x2,y1,y2)<<endl;//同一层直接输出
		}
		else{
			mtx dd=tree.qry(1,1,n-2,levn,levm-2);//求变化矩阵，注意n-2,levm-2
			oriv.a[1][1]=tcdist(x1,usl1[levn],y1,d1[levn])+1;
			oriv.a[1][2]=tcdist(x1,d2[levn],y1,usl2[levn])+1;
			oriv.a[2][1]=oriv.a[2][2]=0;//构造初始矩阵
			if(levn!=levm-1) oriv=mul(oriv,dd);//注意当在相邻层中不用计算
			cout<<min(oriv.a[1][1]+tcdist(x2,usl1[levm-1]+1,y2,d1[levm-1]),oriv.a[1][2]+tcdist(x2,d2[levm-1],y2,usl2[levm-1]+1))<<endl;//取min即可
		}
	}
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

设 $U_i$ 表示第 $i$ 层向上的点，$R_i$ 表示第 $i$ 层向右的点，$L_i$ 表示第 $i$ 层向右的点到达的点，$D_i$ 表示第 $i$ 层向上的点到达的点。

考虑只有一组询问怎么做。

一个比较显然的结论是同层之间两点距离是两点间的曼哈顿距离。

设 $f_{i,0/1}$ 表示从起点 $S$ 出发到第 $i$ 层向上 / 向右门所到达的点的的最短路，答案即为 $\max(f_{B,0}+\mathrm{dis}(U_B,T),f_{B,1}+\mathrm{dis}(R_B,T))$，其中 $B$ 为 $T$ 所在的层数。

接着，我们还可以发现，其实 $\delta(L_i,D_{i+1})=\mathrm{dis}(L_i,D_{i+1})$，其余也类似。证明请读者自行证明。

那么我们就可以进行 $f_i$ 的转移，即 $f_{i,0}=\min(f_{i-1,0}+\mathrm{dis}(D_{i-1},D_i),f_{i-1,1}+\mathrm{dis}(U_{i-1},D_i))$，$f_{i,1}$ 类似，发现可以写成 $(\min,+)$ 矩乘的形式，即：
$$
\left[
\begin{matrix}
f_{i-1,0} & f_{i-1,1}
\end{matrix}
\right]\left[
\begin{matrix}
\mathrm{di}s(D_{i-1},D_i)&\mathrm{dis}(L_{i-1},D_i)\\
\mathrm{dis}(L_{i-1},D_i)&\mathrm{dis}(L_{i-1},L_i)
\end{matrix}
\right]=\left[
\begin{matrix}
f_{i,0} & f_{i,1}
\end{matrix}
\right]
$$

我们对中间的矩阵使用线段树维护区间乘积 $M_{l,r}$，设询问的点为 $A,B$，其中 $A$ 的层号 $d_A$ 比 $B$ 的层号 $d_B$ 小。则最后的答案为：
$$
\left[
\begin{matrix}
\mathrm{dis}(A,U_{d_A})&\mathrm{dis}(A,R_{d_A})
\end{matrix}
\right]M_{d_A,d_B-2}\left[
\begin{matrix}
\mathrm{dis}(B,D_{d_B-1})\\
\mathrm{dis}(B,L_{d_B-1})
\end{matrix}
\right]
$$

细节比较多，要仔细想一想。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using ll=long long;
const int sz=1e5+10;
const ll inf=0x3fffffffffffffff;
template<int n,int m>
struct Matrix{
  ll a[n][m];
  Matrix(){for(int i=0;i<n;i++)std::fill(a[i],a[i]+m,inf);}
  Matrix(std::vector<std::vector<ll>>b){
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=b[i][j];
  }
  Matrix(std::vector<ll>b){
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=b[i*m+j];
  }
  ll* operator[](int x){return a[x];}
  const ll* operator[](int x)const{return a[x];}
  Matrix<n,m>operator+(const Matrix<n,m>&b)const{
    Matrix<n,m>res;
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
        res[i][j]=std::min(a[i][j],b[i][j]);
    return res;
  }
  template<int s>
  Matrix<n,s>operator*(const Matrix<m,s>&b)const{
    Matrix<n,s>res;
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
        for(int k=0;k<s;k++)
          res[i][k]=std::min(res[i][k],a[i][j]+b[j][k]);
    return res;
  }
};
const Matrix<2,2>unit=Matrix<2,2>({0,0,0,0});
std::pair<int,int>b[sz][2];
int dis(std::pair<int,int>x,std::pair<int,int>y){
  return std::abs(x.first-y.first)+std::abs(x.second-y.second);
}
struct SegT{
  Matrix<2,2>tree[sz<<2];
  void build(int p,int ln,int rn){
    if(ln==rn)return tree[p]=Matrix<2,2>({dis(b[ln][0],b[ln+1][0]),dis(b[ln][0],b[ln+1][1]),dis(b[ln][1],b[ln+1][0]),dis(b[ln][1],b[ln+1][1])}),void();
    int mid=ln+rn>>1;
    build(p<<1,ln,mid);
    build(p<<1|1,mid+1,rn);
    tree[p]=tree[p<<1]*tree[p<<1|1];
  }
  template<int n>
  void query(int p,int ln,int rn,int l,int r,Matrix<n,2>&ans){
    if(l>r)return;
    if(ln>=l&&rn<=r)return ans=ans*tree[p],void();
    int mid=ln+rn>>1;
    if(l<=mid)query(p<<1,ln,mid,l,r,ans);
    if(r>mid)query(p<<1|1,mid+1,rn,l,r,ans);
  }
}st;
std::pair<int,int>a[sz][2];
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n,q;
  std::cin>>n;
  for(int i=1,xu,yu,xr,yr;i<n;i++){
    std::cin>>xu>>yu>>xr>>yr;
    a[i][0]=std::make_pair(xu,yu);
    a[i][1]=std::make_pair(xr,yr);
    xu++,yr++;
    b[i][0]=std::make_pair(xu,yu);
    b[i][1]=std::make_pair(xr,yr);
  }
  if(n>2)st.build(1,1,n-2);
  std::cin>>q;
  while(q--){
    std::pair<int,int>A,B;
    std::cin>>A.first>>A.second>>B.first>>B.second;
    if(std::max(A.first,A.second)>std::max(B.first,B.second))std::swap(A,B);
    int ta=std::max(A.first,A.second),tb=std::max(B.first,B.second);
    if(ta==tb)std::cout<<dis(A,B)<<"\n";
    else{
      Matrix<1,2>l({dis(A,a[ta][0]),dis(A,a[ta][1])});
      l=l*Matrix<2,2>({1,dis(a[ta][0],b[ta][1]),dis(a[ta][1],b[ta][0]),1});
      Matrix<2,1>r({dis(B,b[tb-1][0]),dis(B,b[tb-1][1])});
      if(ta<tb-1)st.query(1,1,n-2,ta,tb-2,l);
      std::cout<<(l*r)[0][0]<<"\n";
    }
  }
  return 0;
}
```

---

## 作者：Felix72 (赞：0)

由于不同层的路径必须经过门，我们可以把门之间的距离预处理出来，再动态规划更新。具体就是先走到当前层的门，再动规出与终点层之间的距离，最后计算从门走到终点的距离。

观察方程，发现可以矩阵加速，于是套上线段树可以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, d1x[N], d1y[N], d2x[N], d2y[N], m, sx, sy, ex, ey;
long long ans[N];
inline int dist(int sx, int sy, int ex, int ey)
{return abs(sx - ex) + abs(sy - ey);}
struct matrix //矩阵类 
{
	int h, w;
	long long s[5][5];
};
inline matrix mul(matrix x, matrix y) //广义矩阵乘法 
{
	matrix ans;
	ans.h = x.h, ans.w = y.w;
	memset(ans.s, 0x3f, sizeof(ans.s));
	for(int i = 1; i <= x.h; ++i)
		for(int j = 1; j <= x.w; ++j)
			for(int k = 1; k <= y.w; ++k)
				ans.s[i][k] = min(ans.s[i][k], x.s[i][j] + y.s[j][k]);
	return ans;
}
matrix org[N];
int rt, idx;
struct SGT //线段树 
{
	int ls, rs;
	matrix data;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define data(x) tree[x].data
}tree[N * 2];
inline void pushup(int now)
{data(now) = mul(data(ls(now)), data(rs(now)));}
inline void build(int &now, int l, int r)
{
	if(!now) now = ++idx;
	if(l == r) {data(now) = org[l]; return ;}
	int mid = l + r >> 1;
	if(l <= mid) build(ls(now), l, mid);
	if(mid < r) build(rs(now), mid + 1, r);
	pushup(now);
}
inline matrix ask(int now, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return data(now);
	int mid = l + r >> 1;
	if(R <= mid) return ask(ls(now), l, mid, L, R);
	if(mid < L) return ask(rs(now), mid + 1, r, L, R);
	return mul(ask(ls(now), l, mid, L, R), ask(rs(now), mid + 1, r, L, R));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	memset(ans, -1, sizeof(ans));
	cin >> n;
	for(int i = 1; i < n; ++i) cin >> d1y[i] >> d1x[i] >> d2y[i] >> d2x[i];
	for(int i = 2; i < n; ++i)
	{
		int d1, d2, d3, d4;
		//d1 U - U d2 U - R d3 R - U d4 R - R
		d1 = dist(d1x[i - 1], d1y[i - 1] + 1, d1x[i], d1y[i] + 1);
		d2 = dist(d1x[i - 1], d1y[i - 1] + 1, d2x[i] + 1, d2y[i]);
		d3 = dist(d2x[i - 1] + 1, d2y[i - 1], d1x[i], d1y[i] + 1);
		d4 = dist(d2x[i - 1] + 1, d2y[i - 1], d2x[i] - 1, d2y[i]);
		org[i].h = org[i].w = 2;
		org[i].s[1][1] = d1, org[i].s[1][2] = d2;
		org[i].s[2][1] = d3, org[i].s[2][2] = d4;
	}
	build(rt, 1, n);
	cin >> m;
	for(int i = 1; i <= m; ++i)
	{
		cin >> sy >> sx >> ey >> ex;
		if(max(sx, sy) > max(ex, ey)) swap(sx, ex), swap(sy, ey);
		if(max(sx, sy) == max(ex, ey))
		{
			ans[i] = dist(sx, sy, ex, ey);
			continue;
		}
		matrix st, dp, fin; int ids = max(sx, sy), idt = max(ex, ey);
		st.h = 1, st.w = 2;
		st.s[1][1] = dist(sx, sy, d1x[ids], d1y[ids] + 1);
		st.s[1][2] = dist(sx, sy, d2x[ids] + 1, d2y[ids]);
		if(ids + 1 == idt) //特判掉同层和临层情况 
		{
			ans[i] = 1e18;
			ans[i] = min(ans[i], (long long)st.s[1][1] + dist(d1x[ids], d1y[ids] + 1, ex, ey));
			ans[i] = min(ans[i], (long long)st.s[1][2] + dist(d2x[ids] + 1, d2y[ids], ex, ey));
			continue;
		}
		dp = ask(rt, 1, n, ids + 1, idt - 1);
		fin = mul(st, dp);
		ans[i] = 1e18;
		ans[i] = min(ans[i], (long long)fin.s[1][1] + dist(d1x[idt - 1], d1y[idt - 1] + 1, ex, ey));
		ans[i] = min(ans[i], (long long)fin.s[1][2] + dist(d2x[idt - 1] + 1, d2y[idt - 1], ex, ey));
	}
	for(int i = 1; i <= m; ++i) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：Acee (赞：0)

DDP 水题。

首先，先写一下这题的暴力 dp，设 $f_{i, 0}$ 为在第 $i$ 层，走第 $1$ 个出口的最短路，$f_{i, 1}$ 同理。

若处于同一层，两点的距离显然为曼哈顿距离。

转移也就十分的明显：

$$f_{i, 0} = \min \left \{ f_{i - 1, 0} + dis \left (p \left [ i - 1 \right ] \left [ 0 \right ], p \left [ i \right ] \left [ 0 \right ] \right ) , f_{i - 1, 1} + dis \left (p \left [ i - 1 \right ] \left [ 1 \right ], p \left [ i \right ] \left [ 0 \right ] \right ) \right \}$$

$$f_{i, 1} = \min \left \{ f_{i - 1, 1} + dis \left (p \left [ i - 1 \right ] \left [ 1 \right ], p \left [ i \right ] \left [ 1 \right ] \right ) , f_{i - 1, 0} + dis \left (p \left [ i - 1 \right ] \left [ 0 \right ], p \left [ i \right ] \left [ 1 \right ] \right ) \right \}$$

此处的 $p$ 数组表示传送门位置，$dis$ 函数表示两点间距离。

但是复杂度为 $O(nm)$，很明显过不去。

若用矩阵写出上面的公式：

$$
\begin{bmatrix}
 f_{i, 0} & f_{i, 1}
\end{bmatrix}

\begin{bmatrix}
dis \left (p \left [ i \right ] \left [ 0 \right ], p \left [ i + 1 \right ] \left [ 0 \right ] \right )  &  dis \left (p \left [ i \right ] \left [ 0 \right ], p \left [ i + 1 \right ] \left [ 1 \right ] \right ) \\
dis \left (p \left [ i \right ] \left [ 1 \right ], p \left [ i + 1 \right ] \left [ 0 \right ] \right )  &  dis \left (p \left [ i \right ] \left [ 1 \right ], p \left [ i + 1 \right ] \left [ 1 \right ] \right )
\end{bmatrix}

=

\begin{bmatrix}
 f_{i + 1, 0} & f_{i + 1, 1}
\end{bmatrix}

$$

此处将矩阵乘法的求和换成了求最小值。

那么就可用 DDP 优化。

代码懒得贴了。

---

## 作者：Arghariza (赞：0)

目前为止我是 Luogu 上最优解，不保证后面会不会被神仙同学刷下来，比如 @sinsop90。

upd : 现在不是了，@JWRuixi 用循环展开把我爆踩/ll。


---

令 $a_{i,0}$ 表示第 $i$ 层上面那个门，$a_{i,1}$ 表示右边的门，$b_{i,0/1}$ 分别表示**它们连向的格子**。

首先对于一个询问点对 $(u,v)$，我们考虑一个平凡的 dp：

$dp_{i,0/1}$ 表示从起点 $u$ 出发并从第 $i$ 层的上方/右方走出的最短路，包括走出后到达的那个格子，即如果是从 $a_{i,0}$ 上方走出，答案包括点 $(x(a_{i,0})+1,y(a_{i,0}))$ 的贡献。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1681E/2bd489cb114438619341dcbf3bce60b79757d6e9.png)

比如上面这张图，对于询问 $u=(2,2)$，$dp_{3,0}=4$，即 $(2,2)\to(2,1)\to(3,1)\to(3,2)\to (4,2)$，一共走了 $4$ 步。

显然有：
$$dp_{i,j}=\min\limits_{k\in \{0,1\}}\{dp_{i-1,k}+dis(b_{i-1,k},b_{i,j})\}$$

这个 $dis$ 显然是可以 $O(1)$ 计算且固定的，那我们就做完了。

把这个转移写成矩阵形式：

$$[dp_{i-1,0}\quad dp_{i-1,1}]\begin{bmatrix}dis(b_{i-1,0},b_{i,0})\quad dis(b_{i-1,0},b_{i,1})\\dis(b_{i-1,1},b_{i,0})\quad dis(b_{i-1,1},b_{i,1})\end{bmatrix}=[dp_{i,0}\quad dp_{i,1}]$$

转移矩阵对于每一位是固定的，于是对于 $u\to v$ 为 $l$ 层到 $r$ 层的询问，中间 $l+1,r-1$ 层的转移可以倍增求区间积，两边暴力转移即可。

复杂度 $O(b^3q\log n)$，$b$ 为矩阵大小即 $2$。

[评测记录。](https://codeforces.com/contest/1681/submission/191255790)

---

## 作者：User_Unauthorized (赞：0)

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1681E.html)**

## 题意
有一个 $n\times n$ 的方格图，坐标编号类似平面直角坐标系，左下角为 $(1, 1)$。

这个方格图被分成了 $n$ 层，左下角 $(1, 1)$ 为第一层，随后每层都向外拓展一圈，如下图就是 $n=5$ 的时候的情况：

![](https://espresso.codeforces.com/003bbba1ff0347bde56714b878262c5fe414679d.png)

层与层之间有墙隔开，但每层都有两个门，分别分布在该层顶部和右侧，门是双向的。

现在给出这些门的坐标，有 $m$ 次询问，每次给定两个坐标 $(x_1, y_1)$ 和 $(x_2,y_2)$，请你回答两点之间的最短路。

## 题解

分块做法。

首先读题可以发现门是一定要走的，考虑利用 $\text{DP}$ 预处理出门与门之间的最短距离，设 $f_{i,j,0/1,0/1}$ 表示从顶部 / 右侧门到达第 $i$ 层后到通过顶部 / 右侧门到达第 $j$ 层的最优路径长度。该式的转移是平凡的。

考虑利用分块优化，对于每个块块内处理出两两点对之间的 $f$ 值，对于块块之间按也处理出类似的 $\text{DP}$ 值。

需要平衡复杂度，设块长为 $B$，那么每个块内有 ${B}$ 个元素，即 ${B}^2$ 个点对关系。因为共有 $\dfrac{n}{B}$ 个块，所以这部分的复杂度为 $\mathcal{O}\left(nB\right)$。共有 $\dfrac{n}{B}$ 个块，即 $\left(\dfrac{n}{B}\right)^2$ 个点对，复杂度为 $\mathcal{O}\left(\left(\dfrac{n}{B}\right)^2\right)$。

令 $nB = \left(\dfrac{n}{B}\right)^2$，得 $B = n^{\frac{1}{3}}$，总复杂度为 $\mathcal{O}(n^{\frac{4}{3}})$，可以通过本题。

## Code

出于篇幅考虑，代码另行发布。

- [Code](https://www.cnblogs.com/User-Unauthorized/articles/code-CF1681E.html)

---

