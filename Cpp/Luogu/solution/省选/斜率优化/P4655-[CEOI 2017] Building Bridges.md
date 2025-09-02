# [CEOI 2017] Building Bridges

## 题目描述

有 $n$ 根柱子依次排列，每根柱子都有一个高度。第 $i$ 根柱子的高度为 $h_i$。

现在想要建造若干座桥，如果一座桥架在第 $i$ 根柱子和第 $j$ 根柱子之间，那么需要 $(h_i-h_j)^2$​​ 的代价。

在造桥前，所有用不到的柱子都会被拆除，因为他们会干扰造桥进程。第 $i$ 根柱子被拆除的代价为 $w_i$，注意 $w_i$ 不一定非负，因为可能政府希望拆除某些柱子。

现在政府想要知道，通过桥梁把第 $1$ 根柱子和第 $n$ 根柱子连接的最小代价。注意桥梁不能在端点以外的任何地方相交。

## 说明/提示

对于 $100\%$ 的数据，有 $2\le n\le 10^5;0\le h_i,\vert w_i\vert\le 10^6$。

## 样例 #1

### 输入

```
6
3 8 7 1 6 6
0 -1 9 1 2 0```

### 输出

```
17```

# 题解

## 作者：panyf (赞：66)

提供一个李超线段树的解法。

首先， $O(n^2)$ 的 dp 转移方程极其显然：

$f_i=\min\{f_j+h_i^2-2h_ih_j+h_j^2+s_{i-1}-s_j\}$

其中， $s$ 是拆除代价 $w$ 的前缀和。

将式子化简，得到：

$f_i=h_i^2+s_{i-1}+\min\{f_j-2h_ih_j+h_j^2-s_j\}$

令 $a_j=-2h_j$ ， $b_j=f_j+h_j^2-s_j$ ，则：

$f_i=h_i^2+s_{i-1}+\min\{a_jh_i+b_j\}$

问题转化为，插入直线 $y_j=a_jx+b_j$ ，求 $x=h_i$ 时 $y_j$ 的最小值。

很明显，可以用李超线段树优化，时间复杂度 $O(n\log n)$ 。

代码很短，比 cdq 分治好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//注意开long long
const int N=1e5+9,M=1e6+9;
ll a[N],b[N],h[N],w[N],f[N];
int s[M<<2],u;
inline ll g(int x,int o){return b[o]+a[o]*x;}
//对给定直线和横坐标求纵坐标
void upd(int k,int l,int r,int t){
	if(l==r){
		if(g(l,t)<g(l,s[k]))s[k]=t;
		return;
	}
	int m=l+r>>1;
	if(g(m,t)<g(m,s[k]))swap(t,s[k]);
	if(g(l,t)<g(l,s[k]))upd(k<<1,l,m,t);
	else if(g(r,t)<g(r,s[k]))upd(k<<1|1,m+1,r,t);
}//插入直线
ll qry(int k,int l,int r){
	if(l==r)return g(u,s[k]);
	int m=l+r>>1;
	return min(g(u,s[k]),u<=m?qry(k<<1,l,m):qry(k<<1|1,m+1,r));
}//查询
int main(){
	int n,i;
	scanf("%d",&n),b[0]=1e18;
	for(i=1;i<=n;++i)scanf("%lld",h+i);
	for(i=1;i<=n;++i)scanf("%lld",w+i),w[i]+=w[i-1];
	a[1]=-2*h[1],b[1]=h[1]*h[1]-w[1],upd(1,0,M,1);
	for(i=2;i<=n;++i){
		u=h[i],f[i]=h[i]*h[i]+w[i-1]+qry(1,0,M);
		a[i]=-2*h[i],b[i]=f[i]+h[i]*h[i]-w[i],upd(1,0,M,i);
	}
	printf("%lld",f[n]);
	return 0;
}
```


---

## 作者：Rusalka (赞：21)

我社区贡献分快掉没了

有两篇 CDQ 分治的题解被数据 #19 卡掉了

[题目链接](https://www.luogu.com.cn/problem/P4655)

### 题意简述

- 有 $n$ 根柱子，第 $i$ 根柱子高度为 $h_i$；拆除一个柱子需要花费 $w_i$；在柱子 $i$、$j$ 间连接的花费为 $(h_i-h_j)^2$。你需要保留一些柱子，其中第 $1$ 和 $n$ 号柱子必须保留，拆除其余柱子，并连接相邻的保留的柱子。

- 你需要确定一个保留方案，使得总花费最小。

- $n \le 10^5$，$h_i, |w_i| \le 10^6$。

### 算法

花费为平方式，这很斜率优化。

设 $f_i$ 表示考虑前 $i$ 个柱子并强制保留第 $i$ 个柱子的最小花费，记 $s_i=\sum\limits_{j=1}^iw_j$。

$$f_i = \min\{f_j+s_{i-1}-s_j+(h_i-h_j)^2\}$$

用斜优的套路拆拆式子，记 $X_i=h_i$，$Y_i=h_i^2+f_i-s_i$，且 $j \le k$：

$$2h_i(X_k-X_j) \ge {Y_k-Y_j}$$

你开心地写了个单调队列二分，然后开心的爆零了。

然后你发现这题不仅斜率不单调，连自变量取值也是不单调的。也就是说仅仅单调队列是没法维护的。

那怎么办呢？

不妨强行让自变量单调。考虑分治，此时右区间对左边是没有贡献的，所以先计算左区间的 DP 值，然后考虑其对右区间的影响，最后再递归右区间。回溯时再按照 $X_i$ 为第一关键字，$Y_i$ 为第二关键字归并排序。

具体来说，我们在递归前先在该区间内按照 $X_i$ 排序，这样就保证了自变量和斜率单调不降，故左区间对右区间的转移直接单调队列即可。

当递归到单个结点 $l$ 时，它的 DP 值已经计算完了，可以算出 $Y_l$。  

你发现这就是 CDQ 分治，容易发现像这样在分治过程中转移是不会遗漏的。

时间复杂度 $O(n\log n)$。

### 代码实现

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAXN = 100010;

int n;
ll h[MAXN], s[MAXN], f[MAXN];
inline ll pw2(ll x) {return x*x;}
inline ll X(int i) {return h[i];}
inline ll Y(int i) {return pw2(h[i])+f[i]-s[i];}
struct node{
	ll x, y;
	int ind;
	node(ll X=0,ll Y=0,int I=0):x(X),y(Y),ind(I){}
	bool operator<(const node&o)const{return x ^ o.x ? x < o.x : y < o.y;}
}a[MAXN], tmp[MAXN];

int q[MAXN], he, ta;

void cdq(int l, int r)
{
	if(l == r)
	{
		a[l].y = Y(l);
		return ;
	}
	int mid = (l+r)>>1;
	int x = l, y = mid+1;
	for(int i=l;i<=r;i++)
		if(a[i].ind <= mid) tmp[x++] = a[i];
		else tmp[y++] = a[i];
	for(int i=l;i<=r;i++)
		a[i] = tmp[i];
	cdq(l, mid);
	he = 1; ta = 0;
	for(int i=l;i<=mid;i++)
	{
		if(i > l && a[i].x == a[i-1].x) continue;
		while(he < ta && (a[i].y-a[q[ta]].y)*(a[q[ta]].x-a[q[ta-1]].x) <= (a[q[ta]].y-a[q[ta-1]].y)*(a[i].x-a[q[ta]].x))
			--ta;
		q[++ta] = i;
	}
	for(int i=mid+1;i<=r;i++)
	{
		while(he < ta && a[q[he+1]].y-a[q[he]].y <= 2*a[i].x*(a[q[he+1]].x-a[q[he]].x)) ++he;
		int u = a[i].ind, v = a[q[he]].ind;
		f[u] = min(f[u], f[v] + s[u-1] - s[v] + pw2(h[u] - h[v]));
	}
	cdq(mid+1, r);
	x = l; y = mid+1;
	int now = l;
	while(x <= mid && y <= r)
	{
		if(a[x].x < a[y].x || (a[x].x == a[y].x && a[x].y < a[y].y)) tmp[now++] = a[x++];
		else tmp[now++] = a[y++];
	}
	while(x <= mid) tmp[now++] = a[x++];
	while(y <= r) tmp[now++] = a[y++];
	for(int i=l;i<=r;i++) a[i] = tmp[i];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",h+i), a[a[i].ind = i].x = h[i];
	for(int i=1;i<=n;i++)
		scanf("%lld",s+i), s[i] += s[i-1];
	for(int i=2;i<=n;i++)
		f[i] = 0x3f3f3f3f3f3f3f3f;
	sort(a+1, a+n+1);
	cdq(1, n);
	printf("%lld\n",f[n]);
	return 0;
}
```


---

## 作者：浮尘ii (赞：12)

设 $S_n=\sum_{i=1}^n w_i$，则有
$$\begin{aligned}F_i&=\min\{F_j+S_{i-1}-S_j+(h_i-h_j)^2\}\\   &=S_{i-1}+h_i^2+\min\{F_j-S_j+h_j^2-2h_ih_j\}\\\end{aligned}$$

假设 $h_j \lt h_k$，则 $k$ 比 $j$ 更优的条件为
$$\begin{aligned}F_j-S_j+h_j^2-2h_ih_j &\ge F_k-S_k+h_k^2-2h_ih_k\\2h_i(h_k-h_j) &\ge F_k-S_k+h_k^2-(F_j-S_j+h_j^2)\end{aligned}$$

设 $y_i=F_i-S_i+h_i^2,x_i=h_i$，则
$$\frac{y_k-y_j}{x_k-x_j} \le 2h_i$$

CDQ 分治斜率优化 DP 即可，按照 $h_i$ 排序，建出凸壳，右半边斜率单调递增，用斜率优化 DP 的模型解决即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const int maxN = 100005;

int N, H[maxN], W[maxN];
int Pos[maxN];
ll S[maxN], Y[maxN], X[maxN];
ll F[maxN];

inline ld slope(int j, int k)
{
	if (X[k] == X[j])
		return Y[k] > Y[j] ? 1e20 : -1e20;
	return (ld)(Y[k] - Y[j]) / (X[k] - X[j]);
}

void solve(int l, int r)
{
	if (l == r)
	{
		int i = Pos[l];
		Y[i] = F[i] - S[i] + (ll)H[i] * H[i];
		X[i] = H[i];
		return;
	}
	int m = (l + r) >> 1;
	std::stable_partition(Pos + l, Pos + r + 1, [&](int x) {
		return x <= m;
	});
	solve(l, m);
	static int qu[maxN];
	int *qs = qu, *qe = qu;
	for (int j = l; j <= m; ++j)
	{
		int i = Pos[j];
		while (qe - qs > 1 && slope(*(qe - 1), i) <= slope(*(qe - 1), *qe))
			--qe;
		*++qe = i;
	}
	++qs;
	for (int j = m + 1; j <= r; ++j)
	{
		int i = Pos[j];
		while (qs != qe && slope(*qs, *(qs + 1)) <= 2 * H[i])
			++qs;
		F[i] = std::min(F[i], F[*qs] + (ll)(H[i] - H[*qs]) * (H[i] - H[*qs]) + S[i - 1] - S[*qs]);
	}
	solve(m + 1, r);
	std::inplace_merge(Pos + l, Pos + m + 1, Pos + r + 1, [](int x, int y) {
		return H[x] < H[y];
	});
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", H + i);
	for (int i = 1; i <= N; ++i)
		scanf("%d", W + i), S[i] = S[i - 1] + W[i];
	
	for (int i = 1; i <= N; ++i)
		Pos[i] = i;
	std::sort(Pos + 1, Pos + 1 + N, [](int x, int y) {
		return H[x] < H[y];
	});
	memset(F, 0x7F, sizeof(F));

	F[1] = 0;
	solve(1, N);

	printf("%lld\n", F[N]);

	return 0;
}
```

---

## 作者：Juanzhang (赞：11)

考虑计算所有拆除柱子的贡献，再在转移过程中消去

于是得到一个状态转移方程

$$f_i=\begin{cases}\displaystyle\sum_{i=2}^n w_i&(i=1)\\\displaystyle\min\{f_j+(h_i-h_j)^2-w_i)\}&(i>1)\end{cases}$$

答案即为 $f_n$

于是就有了一个优秀的 $O(n^2)$ 的过不去算法了

然而这玩意儿是可以斜率优化的

通过一番套路地化式子，可以得到

$$f_j+h_j^2=2h_ih_j+f_i-h_i^2+w_i$$

令 $h_j$ 为横坐标， $f_j+h_j^2$ 为纵坐标， $2h_i$ 为斜率

然后……可以发现 $h_j$ 不是递增的……

这就意味着……需要支持插入，询问前驱后继，以及一些复杂的分类讨论……

~~我会平衡树维护动态凸包！~~

然而有更好的离线解决办法：cdq分治

强制让斜率递增然后计算贡献

回想cdq分治的过程，左右递归，计算左侧对右侧的贡献

如果左侧斜率递增，并且左侧编号小于右侧，那么可以通过单调队列维护左侧的凸包来更新右侧答案

并且这样一定能够遍历出每个节点的所有决策点

注意 $long\ long$ ，以及求斜率时 $x_1=x_2$ 的情况

时间复杂度 $O(n\log n)$

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef double db;
typedef long long ll;
const int maxn = 1e5 + 10;
ll f[maxn];
int n, w[maxn];

struct node {
  int x, tid; ll y;
} a[maxn], dat[maxn];

ll sqr(ll x) { return x * x; }
db slope(int x, int y) {
  if (a[x].x == a[y].x) {
    return a[x].y < a[y].y ? 1e18 : -1e18;
  }
  return db(a[x].y - a[y].y) / db(a[x].x - a[y].x);
}

void cdq(int l, int r) {
  if (l == r) {
    a[l].y = f[a[l].tid] + sqr(a[l].x);
    return;
  }
  int mid = (l + r) >> 1;
  for (int i = l, p1 = l, p2 = mid + 1; i <= r; i++) {
    if (a[i].tid <= mid) {
      dat[p1++] = a[i];
    } else {
      dat[p2++] = a[i];
    }
  }
  for (int i = l; i <= r; i++) {
    a[i] = dat[i];
  }
  cdq(l, mid);
  int L = 1, R = 0;
  static int q[maxn];
  for (int i = l; i <= mid; i++) {
    while (L < R && slope(q[R - 1], q[R]) > slope(q[R], i)) R--;
    q[++R] = i;
  }
  for (int i = mid + 1; i <= r; i++) {
    while (L < R && slope(q[L], q[L + 1]) < 2 * a[i].x) L++;
    int x = a[i].tid, y = a[q[L]].tid;
    f[x] = min(f[x], f[y] + sqr(a[i].x - a[q[L]].x) - w[x]);
  }
  cdq(mid + 1, r);
  for (int i = l, p1 = l, p2 = mid + 1; i <= r; i++) {
    if (p2 > r || (p1 <= mid && a[p1].x < a[p2].x)) {
      dat[i] = a[p1++];
    } else {
      dat[i] = a[p2++];
    }
  }
  for (int i = l; i <= r; i++) {
    a[i] = dat[i];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i].x);
    a[i].tid = i, f[i] = 1ll << 60;
  }
  f[1] = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", w + i);
    if (i > 1) f[1] += w[i];
  }
  sort(a + 1, a + n + 1, [](node a, node b) {
    return a.x < b.x;
  });
  cdq(1, n);
  printf("%lld", f[n]);
  return 0;
}
```

---

## 作者：CCCCOrz (赞：10)

不会李超树，写个二进制分组的做法。

首先看到 $ ( h_i - h_j )^2 $ ,差不多就能猜到是斜率优化。

推一波式子：

设 $ f_i $ 为把第 $ 1 $ 根柱子和第 $ i $ 根柱子连接的最小代价，

$ h_i $ 代表第 $ i $ 根柱子的高度，

$ s_i $ 代表拆除前 $ i $ 根柱子的代价之和。

则 $ f_i = \{ f_j + ( h_i - h_j )^2 + s_{i-1} -s_j \}_{\min} \quad (1 \leq j < i) $ 

化简得 $ f_i = {h_i}^2 + s_{i-1}+ \{ f_j + {h_j}^2 -s_j - 2 h_i h_j \}_{\min} \quad (1 \leq j < i) $ 

即我们的横坐标为 $ h_j $ ，纵坐标为 $ f_j + {h_j}^2 -s_j $ ，对每个 $ i $ 求斜率为 $ 2 h_i $ 的直线能截到的截距的最小值。

但是我们发现这个题的横坐标不单调，难以用单调栈维护（~~[然后我写了一棵Splay维护凸包](https://www.luogu.com.cn/record/42585702)~~ 

在机房里调了4个小时没调出来，忽然想起可以二进制分组，不仅容易写，常数还小很多，~~于是果断 Ctrl+A Delete~~

简单介绍一下二进制分组：

所谓“分组”，便是把所维护的数据（在本题中是点）分为若干组，其中第 $ i $ 组（$ i \geq 0 $）的点数为 $ 2^i $ (显然无论何时我们都只有不超过 $ O(\log n) $ 个组)

对于每一次插入，我们相当于添加了一个 $ 2^0 $ 大小的组，此时如果已经存在一个 $ 2^0 $ 大小的组，我们可以将它和插入的数据合并，并作为一个 $ 2^1 $ 大小的组，与原有的 $ 2^1 $ 大小的组继续向上合并。直到有一组不存在，我们就用新添加的组代替该组。

在合并时会有一些点因为左右斜率不满足单调性或 $ x $ 值相等而被删除，但是我们仍把两个组合并前的大小（假设都为 $ 2^i $ ）视为两个组的大小之和( $ 2^{i+1} $ )

因为所有点最多会被合并 $ O(\log n) $ 次，共有 $ n $ 个点，所以插入总复杂度是 $ O(n\log n) $ 

对于查找，直接将所有组的最优值全部二分找出，再取个最优即可。因为共有 $ O(\log n) $ 个组，单个组二分查找最优值的复杂度是 $ O(\log n) $ ，所以查找 $ n $ 次的总复杂度 $ O(n\log^2 n) $ 

最终复杂度 $ O(n\log^2 n) $ ，但常数较小，[跑得还挺快](https://www.luogu.com.cn/record/42627083)

代码：（有大量卡常操作，因为我直接从平衡树维护的代码上改的，~~懒得改了~~）

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[100001],h[100001],s[100001];
struct node{
	int at;
	ll x,y;
}b[550000];//所有组放在一个数组里，节省内存
inline ll mmin(const ll &x,const ll &y){
	return x<y?x:y;
}
inline bool chk(const node &n1,const node &n2,const node &n3){
	return n3.x==n2.x?n3.y<=n2.y:(n3.y-n2.y)*(n2.x-n1.x)<=(n2.y-n1.y)*(n3.x-n2.x);
}
struct stk{
	int h,t;//head和tail (tail在这里是尾指针）
	bool ext;//该组是否存在
	inline void add(const node &x){
		while(t>h&&chk(b[t-1],b[t],x))--t;
		if(t>=h&&x.x==b[t].x)
			if(x.y>b[t].y)return;
			else --t;
		b[++t]=x;
	}
	inline node qus(const ll &k){//单组查找
		int l=h,r=t,mid;
		while(l<r){
			mid=l+r>>1;
			if(k*(b[mid+1].x-b[mid].x)>b[mid+1].y-b[mid].y)l=mid+1;
			else r=mid;
		}
		return b[l];
	}
}q[18],z,mr;
inline void cpy(stk &x,const stk &y){//一定要注意是把数据复制过去而非直接改head和tail
	x.t=x.h-1;
	for(int j=y.h;j<=y.t;++j)
		b[++x.t]=b[j];
}
inline void mrg(const int &at){//合并两个组
	mr.h=400001,mr.t=400000;
	for(int i=z.h,j=q[at].h;i<=z.t||j<=q[at].t;)
		if(i>z.t||(j<=q[at].t&&b[i].x>b[j].x))mr.add(b[j]),++j;
		else mr.add(b[i]),++i;
	cpy(z,mr);
}
int sum=-1;
inline void psh(const node &x){//二进制分组的插入
	z.h=265001,z.t=265000,z.ext=1;
	z.add(x);
	int at=0;
	while(at<=sum&&q[at].ext){
		q[at].ext=0;
		mrg(at);
		++at;
	}
	if(at==sum+1)++sum;
	cpy(q[at],z);
	q[at].ext=1;
}
inline node fnd(const ll &k){//二进制分组的查找
	node ans;
	int at=0;
	while(!q[at].ext)++at;
	ans=q[at].qus(k);
	while(++at<=sum){
		const node &t=q[at].qus(k);
		if(t.y-k*t.x<ans.y-k*ans.x)ans=t;
	}
	return ans;
}
inline int rd(){//快读
	register int x=0,f=1;
	register char c=getchar();
	while(c!='-'&&(c<'0'||c>'9'))c=getchar();
	if(c=='-')f=0,c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?x:-x;
}
void pt(const ll &x){//快写
	if(x>9)pt(x/10);
	putchar((x%10)|48);
}
int main(){
	register int n;
	n=rd();
	for(int i=0;i<18;++i)q[i].h=1<<i;
	for(register int i=1;i<=n;++i)h[i]=rd();
	for(register int i=1;i<=n;++i)s[i]=rd()+s[i-1];
	psh((node){1,h[1],h[1]*h[1]-s[1]});//先把第1个柱子特殊处理（因为它不需要任何代价就与自己连接）
	for(register int i=2;i<=n;++i){
		const node &now=fnd(2*h[i]);
		dp[i]=now.y+s[i-1]+h[i]*(h[i]-(now.x<<1));
		psh((node){i,h[i],dp[i]+h[i]*h[i]-s[i]});
	}
	if(dp[n]<0)putchar('-'),dp[n]=-dp[n];//负数输出
	pt(dp[n]);
	return 0;
}
```
~~为什么我所有的题解都用的奇怪做法啊~~

---

## 作者：GKxx (赞：9)

设$s_i$为$w_i$的前缀和，$f_i$表示将第$1$根柱子与第$i$根柱子连接的最小代价。考虑最后一座桥从第$j$根柱子架到第$i$根柱子，于是枚举$j$，有转移

$$f_i=\min\{f_j+s_{i-1}-s_j+(h_i-h_j)^2\}$$

把平方展开，提出仅与$i$有关的项

$$f_i=\min\{f_j-s_j+h_j^2-2h_ih_j\}+s_{i-1}+h_i^2$$

设$y_i=f_i-s_i+h_i^2,x_i=h_i,k_i=2h_i$，那么

$$f_i=\min\{y_j-k_ix_j\}+s_{i-1}+h_i^2$$

是比较显然的斜率优化。由于这里斜率和横坐标都不单调，不能简单用单调队列解决。可以使用splay维护动态凸包。

这里斜率是正的，要最小化截距，我们需要维护下凸壳。

在splay上维护目前的下凸壳上的结点，结点横坐标从小到大的顺序即为splay中序遍历的顺序。

在splay上对每个节点$x$记录$\mathrm{lk}_x$和$\mathrm{rk}_x$两个值，分别代表在凸壳上$x$左侧那个点与它的连线的斜率（不妨称为“左线斜率”）和它右侧那个点与它连线的斜率（不妨称为“右线斜率”）。

我们可以在splay上二分来找到对于$i$的最优决策点$j$进行转移。对于当前节点$x$：

- 如果$\mathrm{lk}_x\leq k_i\leq\mathrm{rk}_x$，说明这条直线在这里与凸壳相切，这个点$x$就是最优决策点。

- 如果$k_i<\mathrm{lk}_x$，说明切点在左侧，对左子树递归调用。

- 如果$k_i>\mathrm{rk}_x$，说明切点在右侧，对右子树递归调用。

求出$f_i$之后要将这个点插入平衡树。首先按横坐标递增顺序找到它的插入位置，插入这个结点并splay到根。然后检查它左右的结点，把由于它的插入而不满足凸包性质的点删除，同时求出它的左右线斜率。最后检查如果它的左线斜率大于右线斜率，说明这个结点不在凸壳上，将它删除。

两个注意点：$f_1$和$f_2$要单独拎出来写，还有注意斜率不存在的情况。

类似的题目可以看看NOI2007的货币兑换

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <cmath>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

typedef long long LL;

const int maxn = 1e5 + 207;
const double inf = 1e16, eps = 1e-10;

LL s[maxn], h[maxn], f[maxn];
double lk[maxn], rk[maxn], xc[maxn], yc[maxn];
int ch[maxn][2], fa[maxn], root;
int n;

inline double slope(int i, int j) {
    if (fabs(xc[i] - xc[j]) <= eps) return yc[i] < yc[j] ? inf : -inf;
    return (yc[i] - yc[j]) / (xc[i] - xc[j]);
}
inline int iden(int x) {
    return ch[fa[x]][0] == x ? 0 : (ch[fa[x]][1] == x ? 1 : -1);
}
inline void rotate(int x) {
    int d = iden(x), y = fa[x];
    if (~iden(y)) ch[fa[y]][iden(y)] = x;
    fa[x] = fa[y];
    if ((ch[y][d] = ch[x][d ^ 1])) fa[ch[x][d ^ 1]] = y;
    fa[ch[x][d ^ 1] = y] = x;
}
inline void splay(int x, int &k) {
    if (x == k) return;
    for (int p = fa[k], y = fa[x]; y != p; y = fa[x]) {
        if (fa[y] != p) rotate(iden(y) ^ iden(x) ? x : y);
        rotate(x);
    }
    k = x;
}
int queryBest(int x, double k) {
    if (!x) return 0;
    if (lk[x] <= k + eps && k <= rk[x] + eps) return x;
    if (k + eps >= rk[x]) return queryBest(ch[x][1], k);
    else return queryBest(ch[x][0], k);
}
inline int getPrev(int x) {
    int ans = 0;
    for (int y = ch[x][0]; y;) {
        if (lk[y] <= slope(y, x) + eps) ans = y, y = ch[y][1];
        else y = ch[y][0];
    }
    return ans;
}
inline int getNext(int x) {
    int ans = 0;
    for (int y = ch[x][1]; y;) {
        if (slope(x, y) <= rk[y] + eps) ans = y, y = ch[y][0];
        else y = ch[y][1];
    }
    return ans;
}
inline void update(int &rt, int x) {
    splay(x, rt);
    if (ch[x][0]) {
        int y = getPrev(x);
        splay(y, ch[x][0]);
        ch[y][1] = 0;
        rk[y] = lk[x] = slope(y, x);
    } else lk[x] = -inf;
    if (ch[x][1]) {
        int y = getNext(x);
        splay(y, ch[x][1]);
        ch[y][0] = 0;
        rk[x] = lk[y] = slope(x, y);
    } else rk[x] = inf;
    if (lk[x] + eps >= rk[x]) {
        rt = ch[x][0];
        fa[ch[rt][1] = ch[x][1]] = rt;
        fa[rt] = 0;
        rk[rt] = lk[ch[rt][1]] = slope(rt, ch[rt][1]);
    }
}
void insert(int &x, int dad, int id) {
    if (!x) { fa[x = id] = dad; return; }
    insert(xc[x] <= xc[id] + eps ? ch[x][1] : ch[x][0], x, id);
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(h[i]);
    for (int i = 1, x; i <= n; ++i) read(x), s[i] = s[i - 1] + x;

    f[1] = 0;
    xc[1] = h[1];
    yc[1] = f[1] - s[1] + 1.0 * h[1] * h[1];
    f[2] = 1ll * (h[2] - h[1]) * (h[2] - h[1]);
    xc[2] = h[2];
    yc[2] = f[2] - s[2] + 1.0 * h[2] * h[2];
    insert(root, 0, 1); update(root, 1);
    insert(root, 0, 2); update(root, 2);

    for (int i = 3; i <= n; ++i) {
        int j = queryBest(root, 2 * h[i]);
        f[i] = f[j] + s[i - 1] - s[j] + (h[i] - h[j]) * (h[i] - h[j]);
        xc[i] = h[i];
        yc[i] = f[i] - s[i] + 1.0 * h[i] * h[i];
        insert(root, 0, i);
        update(root, i);
    }
    writeln(f[n]);
    return 0;
}

---

## 作者：George1123 (赞：8)

[$\Huge \texttt{In Cnblogs}$](https://www.cnblogs.com/Wendigo/p/12803378.html)

---

> [\[CEOI2017\]Building Bridges](https://www.luogu.com.cn/problem/P4655)

> 有 $n$ 个桥墩，高 $h_i$ 重 $w_i$。连接 $i$ 和 $j$ 消耗代价 $(h_i-h_j)^2$，用不到的桥墩被拆除，代价为 $w_i$。求使 $1$ 与 $n$ 联通的最小代价。

> 数据范围：$2\le n\le 10^5$，$0\le h_i,|w_i|\le 10^6$。

---
非常经典的 **[李超线段树](https://www.cnblogs.com/Wendigo/p/12694123.html)维护 $\texttt{dp}$** 的题目，小蒟蒻来分享一下。

---
很明显 $w_i$ 是大片大片消耗的，所以记 $s_i=\sum_{j=1}^i w_j$。

令 $f_i$ 表示**连接到第 $i$ 个桥墩的最小代价**。可以野蛮推式：


![image.png](https://i.loli.net/2020/04/30/aok6zf9UZcXw7hl.png)

这貌似是个斜率优化式子，但蒟蒻不管，用李超线段树怎么做呢？

考虑李超线段树的作用：**多条线段（直线），求单点最值。**

发现这个 $j$ 有很多，而 $i$ 就只有当前一个：所以可以 $i$ 对应单点，$j$ 对应线。换句话说，**可以把每个 $f_i$ 求出来后添加一条直线**。

![image.png](https://i.loli.net/2020/04/30/2jcAYZRgf4ptWTP.png)

---
这题有几个坑，本来是应该由你来快乐地调试的，但是既然写了题解，蒟蒻就放出来了：

1. 因为要计算 $h_j^2$，所以要开 $\texttt{long long}$ 或用 $1ll$ 乘之。
2. 这个李超线段树是权值线段树，下标要开 $10^6$ 个，节点个数要开 $4\cdot 10^6$ 个。

这个做法貌似有点辜负了这题的难度，但是蒟蒻只会这么做。蒟蒻讲不清楚，还是放个蒻蒻的代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
#define lng long long
#define db double
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rz resize
const int inf=0x3f3f3f3f;
const lng INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5,M=1e6;
int n,h[N+7];
lng w[N+7],f[N+7];

//Lichaotree
typedef pair<lng,lng> line;
lng g(line&li,int x){return li.fi*x+li.se;}
int inter(line&la,line&lb){return db(lb.se-la.se)/(la.fi-lb.fi);}
line v[(M<<2)+7];
void add(line li,int k=1,int l=0,int r=M){
	int mid((l+r)>>1);
	lng ly1=g(li,l),ry1=g(li,r),ly=g(v[k],l),ry=g(v[k],r);
	if(ly1>=ly&&ry1>=ry);
	else if(ly1<=ly&&ry1<=ry) v[k]=li;
	else {
		int in=inter(li,v[k]);
		if(ly1<=ly){
			if(in<=mid) add(li,k<<1,l,mid);
			else add(v[k],k<<1|1,mid+1,r),v[k]=li;
		} else {
			if(in>mid) add(li,k<<1|1,mid+1,r);
			else add(v[k],k<<1,l,mid),v[k]=li;
		}
	}
}
lng get(int x,int k=1,int l=0,int r=M){
	lng res(g(v[k],x));
	if(l==r) return res;
	int mid((l+r)>>1);
	if(mid>=x) res=min(res,get(x,k<<1,l,mid));
	else res=min(res,get(x,k<<1|1,mid+1,r));
	return res;
}

//Main
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&w[i]),w[i]+=w[i-1];
	fill(v+1,v+(M<<2)+1,mk(0,INF));
	f[1]=0,add(mk(-2ll*h[1],1ll*h[1]*h[1]-w[1]));
	for(int i=2;i<=n;i++){
		f[i]=1ll*h[i]*h[i]+w[i-1]+get(h[i]);
		add(mk(-2ll*h[i],f[i]+1ll*h[i]*h[i]-w[i]));
	}
	printf("%lld\n",f[n]);
	return 0;
}
```
---

**祝大家学习愉快！**

---

## 作者：TKXZ133 (赞：6)

[Building Bridges](https://www.luogu.com.cn/problem/P4655)

### 题目大意

连接两根柱子 $i,j$ 的代价是 $(h_i-h_j)^2+\sum\limits_{k=j+1}^{i-1}w_k$，连接具有传递性，求将 $1,n$ 连接的最小代价。

### 思路分析

[斜率优化 DP](https://www.cnblogs.com/TKXZ133/p/17532085.html) 板题。

设 $f_i$ 表示考虑到前 $i$ 根柱子并强制选择第 $i$ 根柱子的最小代价，所求即 $f_n$。则容易列出状态转移方程：

$$f_i=\min_{j<i}(f_j+(h_i-h_j)^2+\sum_{k=j+1}^{i-1}w_k)$$

设 $s$ 为 $w$ 的前缀和，即 $s_i=\sum\limits_{j=1}^iw_j$，则方程可化为：

$$f_i=\min_{j<i}(f_j+h_i^2-2h_ih_j+h_j^2+s_{i-1}-s_{j})$$

然后是斜率优化经典操作：

$$\begin{aligned}f_i&=f_j+h_i^2-2h_ih_j+h_j^2+s_{i-1}-s_{j}\\f_i-h_i^2-s_{i-1}&=f_j+h_j^2-s_j-2h_ih_j\\(f_i-h_i^2-s_{i-1})&=(-2h_j)(h_i)+(f_j+h_j^2-s_j)\end{aligned}$$

设：

$$\begin{cases}y=f_i-h_i^2-s_{i-1}\\k=-2h_j\\x=h_i\\b=f_j+h_j^2-s_j\end{cases}$$

问题转化为每次插入一条 $k_i=-2h_i,b_i=f_i+h_i^2-s_i$ 的直线，查询 $x_i=h_i$ 的最值，用[李超线段树](https://www.cnblogs.com/TKXZ133/p/17529789.html)优化即可。

### 代码

~~自我感觉马蜂可看。~~

```
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N=100100,V=1001000;
#define int long long
#define mid ((l+r)>>1)
#define inf 0x3f3f3f3f3f3f3f3f

int n;
int h[N],s[N],f[N];

struct Line{
	int k,b;
}line[N];

int calc(int id,int x){
	return line[id].k*x+line[id].b;
}

bool Less(int id1,int id2,int x){//比较优劣
	return calc(id1,x)<calc(id2,x);
}

struct ST{//简洁的李超线段树
	int a[V<<2];
	void add(int p,int l,int r,int id){
		if(l==r){if(Less(id,a[p],l)) a[p]=id;return ;}
		if(Less(id,a[p],mid)) swap(a[p],id);
		if(Less(id,a[p],l)) add(p<<1,l,mid,id);
		if(Less(id,a[p],r)) add(p<<1|1,mid+1,r,id);
	}
	int query(int p,int l,int r,int x){
		int res=calc(a[p],x);
		if(l==r) return res;
		if(x<=mid) res=min(res,query(p<<1,l,mid,x));
		else res=min(res,query(p<<1|1,mid+1,r,x));
		return res;
	}
}tree;

signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&h[i]);
	for(int i=1;i<=n;i++){
		scanf("%lld",&s[i]);
		s[i]+=s[i-1];
	}
	line[0]={0,inf};//初始化第 0 条直线，保证空转移转移不到第 0 条上
	line[1]=Line{-2*h[1],h[1]*h[1]-s[1]};//初始化第一条直线
	tree.add(1,0,V,1);//加入第一条直线
	for(int i=2;i<=n;i++){
		f[i]=tree.query(1,0,V,h[i])+h[i]*h[i]+s[i-1];//查询，移项过去得 f[i]
		line[i]=Line{-2*h[i],f[i]+h[i]*h[i]-s[i]};//新建直线
		tree.add(1,0,V,i);//插入直线
	}
	cout<<f[n]<<'\n';
	return 0;
}
```

---

## 作者：Gmt丶FFF (赞：6)

明显是 dp。

首先列出 dp 式子，设 $f_i$ 为跳到 $i$ 时的最小代价。

那么：

$f_i=f_j+(h_i-h_j)^2+(sum_{i-1}-sum_j)$。

$f_i=f_j+h_i^2+h_j^2+2h_ih_j+sum_{i-1}-sum_j$

$f_j+h_j^2-sum_j=-2h_ih_j+f_i-h_i^2-sum_{i-1}$

明显斜率式，考虑斜率优化，但 $h_i,h_j$ 均无单调性。

那么就可以用斜率三件套了：李超线段树，平衡树，cdq 分治，这里选择 cdq 分治。

步骤如下：

1、对左边进行分治。

2、维护左边凸包。

3、对右边斜率排序。

4、对右边进行分治。

5、对整个区间的点按 $x$ 排序，用来维护下次的凸包。

递归到边界时注意处理点的坐标

本题求最小值，所以维护下凸包，斜率从小到大排序，剩下的就没什么了。

由于懒，所以排序选择了 sort，比归并复杂度高，但问题不大。

时间复杂度：$O(n\times\log_2^2(n))$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
const int N=2e5+5;
int h[N],sum[N],n,s[N],f[N];
struct node
{
	int name,x,y;
}q[N];
int cmp(node fi,node se)
{
	if(fi.x==se.x)return fi.y>se.y;
	return fi.x<se.x;
}
int cmp2(node fi,node se)
{
	return h[fi.name]<h[se.name];
}
int cmp3(node fi,node se)
{
	return fi.name<se.name;
}
inline int clac(int x)
{
	return x*x;
}
double slope(int x,int y)
{
	if(q[x].x==q[y].x)return -1e18;
	return (q[x].y-q[y].y)*1.0/1.0/(q[x].x-q[y].x);
}
void cdq(int l,int r)
{
	if(l==r)
	{
		q[l].x=h[l];
		q[l].y=f[l]-sum[l]+clac(h[l]);
		return;
	}
	int mid=(l+r)>>1;
	cdq(l,mid);
	int lc=1,rc=0;
	for(int i=l;i<=mid;i++)
	{
		while(lc<rc&&slope(s[rc],s[rc-1])>=slope(i,s[rc]))rc--;
		s[++rc]=i;
	}
	sort(q+mid+1,q+r+1,cmp2);
	for(int i=mid+1;i<=r;i++)
	{
		while(lc<rc&&slope(s[lc],s[lc+1])<=2*h[q[i].name])lc++;
		f[q[i].name]=min(f[q[i].name],f[q[s[lc]].name]+sum[q[i].name-1]-sum[q[s[lc]].name]+clac(h[q[i].name]-h[q[s[lc]].name]));
	}
	sort(q+mid+1,q+r+1,cmp3);
	cdq(mid+1,r);
	sort(q+l,q+r+1,cmp);
}
signed main()
{
	memset(f,0x3f,sizeof(f));
	f[1]=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&h[i]),q[i].name=i;
	for(int i=1;i<=n;i++)scanf("%lld",&sum[i]),sum[i]+=sum[i-1];
	cdq(1,n);
	printf("%lld",f[n]);
	return 0;
}
/*
10
1 2 3 4 5 4 3 2 1 0
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1
*/
```


---

## 作者：huangzirui (赞：5)

介绍一下李超线段树：

李超线段树可以维护一堆线段上求 $x=a$ 的最值的问题。

类似于普通线段树，不过每个区间 $[l,r]$ 都维护的是一条在 $mid$ 处最优的线段。

具体来说，求 $x=a$ 的最值时用每个包含 $a$ 的节点上的线段分别求最值即可。

比如这道题，写出 dp 方程：

$$dp_x=min\{dp_i+(h_i-h_x)^2-W_i+W_x\}$$

其中 $W_x = \sum_{i=1}^{x-1}w_i$

那么可以转化成一个类似斜率优化的式子：

$$dp_x-W_x-{h_x}^2=dp_i+{h_i}^2-W_i-2h_ih_x$$

于是就是求与直线 $x=h_x$ 相交的最低点。

于是可以用李超线段树维护。

```cpp
#include <bits/stdc++.h>
#define l(x) tree[x].l
#define lazy(x) tree[x].lazy
#define ls(x) (tree[x].son[0])
#define rs(x) (tree[x].son[1])
#define ll long long
#define Mid ((L+R)>>1)
using namespace std;
typedef pair<int,int> pii;
inline int read(){
	char c;int x=0;int b=1;do{c=getchar();if(c==45)b=-1;}while(c>57||c<48);
	do x=x*10+c-48,c=getchar();while(c<=57&&c>=48);x*=b;return x;
}
const int maxn=200010;
int i,j,k,n,m,root,cnt;
ll h[maxn],w[maxn],dp[maxn];
struct line{
	ll k,b;
	ll calc(ll x){
		return k*x+b;
	}
};
struct tree{
	line l;
	int son[2];
}tree[maxn*4]
void insert(int &root,int L,int R,line g){
	if(!root){
		root=++cnt;
		lazy(root)=1;
		l(root)=g;
		return;
	}
	if(L==R){
		if(g.calc(L)<l(root).calc(L))l(root)=g;
		return;
	}
	if(g.calc(Mid)<l(root).calc(Mid))swap(l(root),g);
	if(g.k>l(root).k)insert(ls(root),L,Mid,g);
	else if(g.k<l(root).k)insert(rs(root),Mid+1,R,g);
}
ll find(int root,int L,int R,int x){
	if(!root)return 1e18;
	if(L==R)return l(root).calc(x);
	if(x<=Mid)return min(find(ls(root),L,Mid,x),l(root).calc(x));
	return min(find(rs(root),Mid+1,R,x),l(root).calc(x));
}
ll ans=1e18;
signed main() {
	freopen("P4655.in","r",stdin);
	freopen("P4655.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++)h[i]=read();
	for(i=1;i<=n;i++)w[i]=read();
	for(i=1;i<=n;i++)w[i]+=w[i-1];
	dp[1]=0;insert(root,1,1e6,(line){-2*h[1],dp[1]+h[1]*h[1]-w[1]});
	for(i=2;i<=n;i++){
		dp[i]=find(root,1,1e6,h[i])+h[i]*h[i]+w[i-1];
		insert(root,1,1e6,(line){-2*h[i],dp[i]+h[i]*h[i]-w[i]});
	}cout<<dp[n]<<endl;
	//cerr << 1.0*clock()/CLOCKS_PER_SEC << endl;
	return 0;
}
```

---

## 作者：Jμdge (赞：4)

吼题啊。。。 可以考虑分治去做这道题？

据说标算李超线段树然鹅 好多一个 log 的代码跑得还没两个 log 的快 $QVQ$ （常数问题？）

哦！我的CDQ好像也是一个log的...

复杂度白痴傻傻算不清楚 **→_→**

----


首先考虑这题可以 $n^2$ dp ...表达式很朴素，一开始我就用的这个 $n^2$ 做的因为理不出思绪

表达式：

$$f_i=f_j +(h_i-h_j)^2 +W_{i-1}-W_j $$

然后我一开始居然想些乱七八糟的算法没看出来这玩意儿是斜率优化！

哎，手生了，斜率优化都好久没做了呢...QVQ

然后的话我们吧式子展开出来就是：


$$f_i=f_j +h_i^{~~ 2} +  h_j^{~~ 2}  -2·h_ih_j +W_{i-1}-W_j $$

在移一下项变成斜率优化标准形式：


$$    2·h_ih_j +f_i~~~ [+ h_i^{~~ 2} -W_{i-1} ] = f_j + h_j^{~~ 2} -W_j $$

忽略掉 [] 里面的常量，这就是一个一次函数了，我们的目标就是让 f[i] 最小，那么就是维护一个下凸壳


然后我们发现超级难维护：

因为首先这里的斜率 h[i] 是不单调的，并且我们发现横坐标 x 是 h[i] ， 也是不单调的！

也就是说我们要在单调栈里面二分找答案，更要命的是每次要在单调中间插入一个点！用 map ！用 set ！ 口胡倒是容易的啊  $QVQ$， 于是我成功的口胡掉了这道题然后交了 30 分代码（好吧其实我根本不会处理动态凸包啊...）


虽然说会动态凸包的奆佬可以分分钟切了这题，但是身为蒟蒻的我只会分治...


我们考虑可以江一个上凸壳拆成两个，然后分别对 i 计算答案，两者取较优，那么这样的操作并不会影响答案

于是我们可以考虑去让 CDQ 每一层的左部分构造上凸壳然后去更新右边的答案，可以证明这样做是正确的。

另外这里要注意当我们到达一个 CDQ 分治层时，先递归处理左部分，然后再处理当前层，最后再去处理右边的部分

为什么？因为我们构造凸包的时候要先拿到 f[i] 的最优值啊，所以肯定要等到点 i 的 f 值更新完毕之后才能用的啊


```
//by Judge
#include<bits/stdc++.h>
#define fp(i,a,b) for(int i=(a),I=(b)+1;i<I;++i)
#define mid (l+r>>1)
#define ll long long
#define db double
using namespace std;
const db inf=1e18;
const int M=1e5+3;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline bool cmin(ll& a,ll b){return a>b?a=b,1:0;}
inline ll read(){ ll x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,top,num[22][M]; ll f[M];
struct node{ ll id,h,w; }s[M],ss[M];
struct po{ ll x,y,id; }stk[M];
inline void merge(int k,int l,int r){  //预处理使得每个分治块内 h 递增
	if(l==r) return num[k][l]=l,void();
	merge(k+1,l,mid),merge(k+1,mid+1,r);
	int li=l,ri=mid+1;
	fp(i,l,r) if(li>mid) num[k][i]=num[k+1][ri++];
		else if(ri>r) num[k][i]=num[k+1][li++];
		else num[k][i]=s[num[k+1][li]].h<=s[num[k+1][ri]].h?
						num[k+1][li++]:num[k+1][ri++];
}
inline po xl(po a,po b){return {a.x-b.x,a.y-b.y,0};}
inline ll cj(po a,po b){return a.x*b.y-a.y*b.x;}
inline void make_convex(int l,int r){ top=0; //维护 上【划掉】下凸壳
	fp(i,l,r){ po now={s[i].h,f[s[i].id]+s[i].h*s[i].h-s[i].w,s[i].id};
		for(;top>1&&cj(xl(stk[top],stk[top-1]),xl(now,stk[top]))<=0;--top);
		stk[++top]=now;
	}
}
inline db get_k(po& a,po& b){  //拿个斜率
	if(a.x^b.x) return (db)(a.y-b.y)/(db)(a.x-b.x);
	return a.y>b.y?-inf:inf;
}
void CDQ(int k,int l,int r){
	if(l==r) return ; CDQ(k+1,l,mid);
	fp(i,l,r) s[i]=ss[num[k+1][i]];
	make_convex(l,mid); int fs=1;
	fp(i,mid+1,r){  //因为此时 s 中 h 递增所以可以单调队列处理了
		for(;fs<top&&2*s[i].h>get_k(stk[fs],stk[fs+1]);++fs);
		int j=stk[fs].id,ii=s[i].id;
		cmin(f[ii],f[j]+(ss[ii].h-ss[j].h)*(ss[ii].h-ss[j].h)+ss[ii-1].w-ss[j].w);
	} fp(i,mid+1,r) s[i]=ss[i]; CDQ(k+1,mid+1,r); //向下分治
}
int main(){ n=read();
	fp(i,1,n) s[i].h=read();
	fp(i,1,n) s[i].w=s[i-1].w+read();
	fp(i,1,n) s[i].id=i,ss[i]=s[i];
	merge(1,1,n); fp(i,2,n) f[i]=inf;
	return CDQ(1,1,n),!printf("%lld\n",f[n]); //记得 long long
}
```


然后给一个奆佬的动态凸包代码 $QVQ$（没错就是Binamoto！）

差点（好吧其实是已经） AK 了某场有此题的比赛


```
//minamoto
#include<bits/stdc++.h>
#define R register
#define ll long long
#define ld long double
#define pi pair<int,ll>
#define IT map<int,ll>::iterator
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
int read(){
    R int res,f=1;R char ch;
    while((ch=getc())>'9'||ch<'0')(ch=='-')&&(f=-1);
    for(res=ch-'0';(ch=getc())>='0'&&ch<='9';res=res*10+ch-'0');
    return res*f;
}
const int N=1e5+5;
struct node{
	int h;double k;
	node(){}
	node(R int hh,R double kk=0){h=hh,k=kk;}
	inline bool operator <(const node &b)const{return k<b.k;}
	inline bool operator <=(const node &b)const{return k<=b.k;}
	inline bool operator ==(const node &b)const{return h==b.h&&k==b.k;}
};
int h[N];ll sum[N],f[N],g[N];map<int,ll>mp;set<node>s;
int n;bool flag=0;int hi,ht;
inline ll G(R int id){return f[id]+1ll*h[id]*h[id]-sum[id];}
inline bool cross(R int id,pi a,pi b){
	return (ld)(a.first-h[id])*(b.second-g[id])-(ld)(a.second-g[id])*(b.first-h[id])>=0;
}
inline double slope(pi a,pi b){return 1.0*(b.second-a.second)/(b.first-a.first);}
bool in(int id){
	if(h[id]<mp.begin()->first||h[id]>(--mp.end())->first)return false;
	IT it=mp.lower_bound(h[id]);
	if(it!=mp.end()&&it->first==h[id])return it->second<=g[id];
	IT itr=it;--it;
	return cross(id,*it,*itr);
}
void del(IT itl,IT itr){s.erase(node(itl->first,slope(*itl,*itr)));}
void ins(IT it){
	IT itl=it,itr=it;--itl,++itr;
	if(it!=mp.begin())s.insert(node(itl->first,slope(*itl,*it)));
	if(itr!=mp.end())s.insert(node(it->first,slope(*it,*itr)));
}
void update(int id){
	if(in(id))return;
	IT it=mp.lower_bound(h[id]),itr;
	if(it!=mp.end()&&it->first==h[id]){
		IT itl=it,itr=it;--itl,++itr;
		if(it!=mp.begin())del(itl,it);
		if(itr!=mp.end())del(it,itr);
		mp.erase(it);
	}else{
		IT itl=it;--itl;
		if(it!=mp.begin()&&it!=mp.end())del(itl,it);
	}
	it=mp.upper_bound(h[id]),itr=it;
	if(it!=mp.end()){
		++itr;
		while(itr!=mp.end()&&cross(id,*itr,*it))
			del(it,itr),mp.erase(it),it=itr,++itr;
	}
	it=mp.lower_bound(h[id]),itr=it;--itr;
	if(it!=mp.begin()&&itr!=mp.begin()){
		--it,--itr;
		while(it!=mp.begin()&&cross(id,*it,*itr))
			del(itr,it),mp.erase(it),it=itr,--itr;
	}
	mp[h[id]]=g[id];
	it=mp.lower_bound(h[id]),ins(it);
}
int get(int k){
	set<node>::iterator it=s.lower_bound(node(0,1.0*k));
	if(it==s.end())return (--mp.end())->first;
	return it->h;
}
int main(){
	n=read();
	fp(i,1,n)h[i]=read();
	fp(i,1,n)sum[i]=read()+sum[i-1];
	f[1]=0,f[2]=1ll*(h[2]-h[1])*(h[2]-h[1]),g[1]=G(1),g[2]=G(2);
	mp[h[1]]=g[1],update(2);
	fp(i,3,n){
		ht=get(2*h[i]);
		f[i]=sum[i-1]+mp[ht]+1ll*h[i]*h[i]-2ll*h[i]*ht;
		g[i]=G(i);
		update(i);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```



当然超哥线段树也是有的 $QVQ$ （但是只有第一个代码是我滴~）

至于怎么做嘛。。。我就不会了，本题解只讲分治做法...

但是这个超哥线段树代码确实是跑得比我快的...

代码貌似是 zcy 大佬的 emmm... 看到别棕我 $QWQ$

```
#include<bits/stdc++.h>
using namespace std;
#define N 100010
#define M 1000000
#define LL long long
#define LD long double
#define F(x, y, z) for (int x = y; x <= z; ++x)
#define D(x, y, z) for (int x = y; x >= z; --x)
int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }
template <typename T> void read(T &x)
{
	x = 0; T f = 1; char c = getchar();
	for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for ( ; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
LL h[N], s[N], f[N];
int n;
struct LiChao_Tree
{
	LL X[M * 4 + N], Y[M * 4 + N];
	void Build(int k, int l, int r)
	{
		X[k] = 0, Y[k] = 1e14;
		if (l == r) return;
		int mid = l + r >> 1;
		Build(k << 1, l, mid);
		Build(k << 1 | 1, mid + 1, r);
	}
	void Modify(int k, int l, int r, LL x, LL y) 
	{
		int mid = l + r >> 1;
		if (x * mid + y < X[k] * mid + Y[k])
			swap(X[k], x), swap(Y[k],y);
		if (x == X[k] || l == r) return;
		if (x > X[k]) Modify(k << 1, l, mid, x, y);
		else Modify(k << 1 | 1, mid + 1, r, x, y);
	}
	LL Query(int k,int l,int r, int w)
	{
		if (l == r) return X[k] * w + Y[k];
		int mid = l + r >> 1;
		LL ans = X[k] * w + Y[k];
		if (w <= mid) ans = min(ans, Query(k << 1, l, mid, w));
		else ans = min(ans, Query(k << 1 | 1, mid + 1, r, w));
		return ans;
	}
} T;
LL C(int x)
{
	return h[x] * h[x] - s[x] + f[x];	
} 
int main(){
	read(n);
	F(i, 1, n) read(h[i]);
	F(i, 1, n) read(s[i]), s[i] += s[i - 1];
	T.Build(1, 0, M);
	T.Modify(1, 0, M, -2 * h[1], C(1));
	F(i, 2, n)
	{
		f[i] = h[i] * h[i] + s[i - 1] + T.Query(1, 0, M, h[i]);
		T.Modify(1, 0, M, -2 * h[i], C(i));
	}
	cout << f[n] << '\n';
	return 0;
}
```





---

## 作者：是个汉子 (赞：3)

### Solution

设 $f_i$ 为将第 $1$ 根和第 $i$ 根柱子相连的代价，则容易得到状态转移方程：
$$
f_i=\min\{f_j+\sum\limits_{k=j+1}^{i-1}w_k+(h_i-h_j)^2\}
$$


我们可以令 $s_i=\sum\limits_{k=1}^iw_k$ ，这样就可以将 $\sum\limits_{k=j+1}^{i-1}w_k$ 写作 $s_{i-1}-s_j$ ，得：
$$
\begin{aligned}f_i&=\min\{f_j+s_{i-1}-s_j+(h_i-h_j)^2\}\\&=\min\{f_j+s_{i-1}-s_j+h_i^2-2h_ih_j+h_j^2\}\\&=\min\{(-2h_ih_j+f_j-s_j+h_j^2)+(s_{i-1}+h_i^2)\}\end{aligned}
$$

看上去是不是很像斜率优化DP的样子。~~(虽然是李超线段树板子题，不过我们用斜率优化做)~~

\
观察一下可以发现，若 $i$ 确定，$(s_{i-1}+h_i^2)$ 为常数项，可以忽略。

于是就变成了对于一个确定的 $i$，求 $\min\{-2h_ih_j+f_j-s_j+h_j^2\}$ 。

若决策 $j$ 优于决策 $k$ 则：
$$
-2h_ih_j+f_j-s_j+h_j^2<-2h_ih_k+f_k-s_k+h_k^2
$$
化简得：

$$
\dfrac{(f_j-s_j+h_j^2)-(f_k-s_k+h_k^2)}{2(h_j-h_k)}<h_i
$$
令 $Y(i)=f_i-s_i+h_i^2,X(i)=2h_i$ ，则：
$$
\dfrac{Y(j)-Y(k)}{X(j)-X(k)}<h_i
$$



因为 $h_i$ 并不是单调的，所以需要**CDQ分治**来维护

用splay维护动态凸包也不拦你(~~因为我不会~~)

我们考虑将一个单调队列分为左右两个，然后递归处理，发现递归到长度为1时，可以像普通斜率优化一样建点。

回溯时，因为左边对右边会有影响，所以先将左边的状态插入单调队列，再更新右边的状态。

时间复杂度：$O(n\log^2n)$ 

代码就咕咕咕了= =

---

## 作者：Phartial (赞：2)

设 $f_i$ 表示把第 $1$ 根柱子和第 $i$ 根柱子连接的最小代价。

有转移方程 $f_i=\min_{j=1}^{i-1}f_j+(h_i-h_j)^2+(s_{i-1}-s_j)$，其中 $s_i=\sum_{j=1}^iw_j$，即 $w$ 的前缀和。

把式子展开：

$$
f_i=\min_{j=1}^{i-1}f_j+(h_i-h_j)^2+(s_{i-1}-s_j)\\
f_i=\min_{j=1}^{i-1}f_j+h_i^2+h_j^2-2h_ih_j+s_{i-1}-s_j
$$

观察到这是一个典型的斜率优化形式，不妨设 $b_i=h_i^2+s_{i-1}$，$k_i=h_i$，$x_i=2h_i$，$y_i=f_i+h_i^2-s_i$。那么原式变成：

$$f_i=b_i+\min_{j=1}^{i-1}y_j-k_ix_j$$

由于 $x_i$ 和 $k_i$ 没有单调性，所以要用 CDQ 分治维护凸包，二分找决策点，时间复杂度 $O(n\log^2 n)$。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;
using Pll = pair<LL, LL>;

const int kN = 1e5 + 1;

int n, t;
LL h[kN], w[kN], f[kN], s[kN];
Pll q[kN], p[kN];

LL X(int i) { return 2 * h[i]; }
LL Y(int i) { return f[i] - s[i] + h[i] * h[i]; }
LL K(int i) { return h[i]; }
LL B(int i) { return s[i - 1] + h[i] * h[i]; }

Pll operator-(Pll x, Pll y) { return {x.first - y.first, x.second - y.second}; }
LL operator*(Pll x, Pll y) { return x.first * y.second - x.second * y.first; }

void S(int l, int r) {
  if (l == r) {
    if (l != 1) {
      f[l] += B(l);
    }
    return;
  }
  int m = l + r >> 1;
  S(l, m);
  for (int i = l; i <= m; ++i) {
    p[i] = {X(i), Y(i)};
  }
  sort(p + l, p + m + 1);
  t = 0;
  for (int i = l; i <= m; ++i) {
    for (; t > 1 && (p[i] - q[t - 1]) * (q[t] - q[t - 1]) >= 0; --t) {
    }
    q[++t] = p[i];
  }
  q[t + 1] = {q[t].first + 1, 1e18};
  for (int i = m + 1; i <= r; ++i) {
    int _l = 1, _r = t;
    while (_l < _r) {
      int _m = _l + _r >> 1;
      if ((q[_m + 1].second - q[_m].second) < K(i) * (q[_m + 1].first - q[_m].first)) {
        _l = _m + 1;
      } else {
        _r = _m;
      }
    }
    f[i] = min(f[i], q[_l].second - K(i) * q[_l].first);
  }
  S(m + 1, r);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> h[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> w[i];
    s[i] = s[i - 1] + w[i];
  }
  for (int i = 2; i <= n; ++i) {
    f[i] = 1e18;
  }
  S(1, n);
  cout << f[n];
  return 0;
}
```


---

## 作者：lyxeason (赞：2)

### 前置知识

[李超线段树](https://oi-wiki.org/ds/li-chao-tree/)

下面的讲解默认学过李超线段树。

------------
首先可以得出一个最基础的动态规划转移方程：
$$f_i=\min_{1\le j<i}\{f_j+s_{i-1}-s_j+(h_i-h_j)^2\}$$
其中，$f_i$ 为前 $i$ 个柱子，随便建桥，最小代价是多少。$s_i$ 是 $w_i$ 的前缀和~~状态转移应该很显然吧~~。

展开得：
$$f_i=\min_{1\le j<i}\{f_j+s_{i-1}-s_j+{h_i}^2-2h_ih_j+{h_j}^2\}$$
时间复杂度 $O(n^2)$，肯定会超时。

下一步考虑优化转移过程。

先把所有与 $j$ 取值无关的都提出来。
$$f_i=\min_{1\le j<i}\{f_j+s_{i-1}-s_j+{h_i}^2+{h_j}^2-2h_ih_j\}$$
得：
$$f_i=s_{i-1}+{h_i}^2+\min_{1\le j<i}\{f_j-s_j+{h_j}^2-2h_ih_j\}$$
看到其中有一项是 $-2h_ih_j$，再结合数据范围 $0\le h_i\le 10^6$，那么就可以用李超线段树来进行优化。

李超线段树能够在 $O(\log n)$ 的时间复杂度内实现在平面上插入一条直线，查询横坐标为 $x$ 上的最高或最低的直线。

那么在这道题中，设 $a_j=f_j-s_j+{h_j}^2,b_j=-2h_j$，则有：
$$f_i=s_{i-1}+{h_i}^2+\min_{1\le j<i}\{h_ib_j+a_j\}$$

把 $y=b_jx+a_j$ 视作一条直线，那么求 $\min_{1\le j<i}\{h_ib_j+a_j\}$ 就可以转化为求当横坐标为 $h_i$ 时，最低的一条直线。这样就转化为了李超线段树可以求解的问题。

------------
### 代码
###### 代码里有注释

```cpp


#include <cstdio>
#define ll long long

using namespace std;

struct Node {
    int id;
    Node () {
        id = 0;
    }
};

int N;
ll H[100009];
ll W[100009];
ll s[100009];
ll dp[100009];
ll a[100009];
ll b[100009];
Node tr[4000009];

void In () {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%lld", &H[i]);
    for (int i = 1; i <= N; i++) scanf("%lld", &W[i]);
}

inline ll Get_C (ll x, int l) { //找到第 l 条直线横坐标为x处y坐标的值
    return a[l] + b[l] * x;
}

void Add (int x, int l, int r, int id) { //加入第id条直线
    int mid;

    if (l == r) {
        if (Get_C(l, id) < Get_C(l, tr[x].id)) tr[x].id = id;
        return;
    }
    mid = l + r >> 1;
    if (Get_C(mid, id) < Get_C(mid, tr[x].id)) { int t = tr[x].id; tr[x].id = id, id = t; }
    if (Get_C(l, id) < Get_C(l, tr[x].id)) Add(x << 1, l, mid, id);
    else if (Get_C(r, id) < Get_C(r, tr[x].id)) Add(x << 1 | 1, mid + 1, r, id);
}

inline ll Min (ll a, ll b) {
    return a < b ? a : b;
}

ll Query (int x, int l, int r, ll p) {
    int mid;
    
    if (l == r) return Get_C(p, tr[x].id);
    mid = l + r >> 1;
    if (p <= mid) return Min(Get_C(p, tr[x].id), Query(x << 1, l, mid, p));
    else return Min(Get_C(p, tr[x].id), Query(x << 1 | 1, mid + 1, r, p));
}

void Solve () {
    for (int i = 1; i <= N; i++) s[i] = s[i - 1] + W[i];
    a[0] = 1e18; //这里一定要初始化，因为李超线段树里的每个节点计的最优解一开始初始默认为第0条直线
    a[1] = H[1] * H[1] - s[1], b[1] = -2ll * H[1];
    Add(1, 0, 1e6, 1); //先处理一下第一条直线
    for (int i = 2; i <= N; i++) {
        dp[i] = H[i] * H[i] + s[i - 1] + Query(1, 0, 1e6, H[i]);
        a[i] = dp[i] - s[i] + H[i] * H[i], b[i] = -2ll * H[i]; //第i条直线的参数
        Add(1, 0, 1e6, i);
    }
}

void Out () {
    printf("%lld\n", dp[N]);
}

int main () {

    In();
    Solve();
    Out();

    return 0;
}
```

---

## 作者：kouylan (赞：2)

在此提供两种方法：cdq 分治和李超树。

定义 $f(i)$ 为连到第 $i$ 根柱子的最小花费，把 $w_i$ 写成前缀和。

$f(i)=\min\{f(j)+(h_i-h_j)^2+w_{i-1}-w_j\}$

首先介绍 cdq 分治写法。

$f(i)=f(j)+h_j^2-w_j-2h_jh_i+h_i^2+w_{i-1}$

设 $Y(j)=f(j)+h_j^2-w_j,X(j)=h_j$，若 $j_1<j_2$ 且 $j_2$ 优于 $j_1$，我们就有

$Y(j_2)-2h_iX(j_2)\leq Y(j_1)-2h_iX(j_1)$

$\frac{Y(j_2)-Y(j_1)}{X(j_2)-X(j_1)}\leq 2h_i$

这是一个下凸包，但 $h_i$ 不单调，要用 cdq 分治。

分治前，先按照 $k_i$ 从小到大排序（因为这是下凸包，如果是上凸包就要从大到小排序）。分治时，先按照编号分到左右半边，这样 [ $l,mid$ ] 和 [ $mid+1,r$ ] 都是 $k$ 单调的，然后递归处理左半边，使得左半边的 $x$ 有序，再用单调队列维护左半边的凸包，更新右半边的答案，然后再处理右半边，最后，把左右两半按 $x$ 归并起来。

下面是 cdq 分治的 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 0x7f7f7f7f;

int n,h[100005],s[100005],hd=1,tl=0,dq[100005],f[100005];
struct node{
	int x,y,k,u;
}q[100005],q0[100005];

bool cmpk(node a,node b)
{
	return a.k<b.k;
}

bool cmpx(node a,node b)
{
	return a.x<b.x;
}

double k_(int j1,int j2)
{
	if(q[j1].x==q[j2].x)
		return q[j1].y>q[j2].y ? -1.0*INF : 1.0*INF;
	return 1.0*(q[j1].y-q[j2].y)/(q[j1].x-q[j2].x);
}

void cdq_(int l,int r)
{
	if(l==r)
	{
		int j=q[l].u;
		q[l].y = f[j]+h[j]*h[j]-s[j];
		return;
	}
	int mid=l+r>>1;
	int p1=l,p2=mid+1;
	for(int i=l;i<=r;i++)
		if(q[i].u<=mid)
			q0[p1] = q[i], p1++;
		else
			q0[p2] = q[i], p2++;
	for(int i=l;i<=r;i++)
		q[i] = q0[i];
	cdq_(l,mid);
	hd = 1, tl = 0;
	for(int i=l;i<=mid;i++)
	{
		while(hd<tl && k_(dq[tl],i)<=k_(dq[tl-1],dq[tl]))
			tl--;
		dq[++tl] = i;
	}
	for(int i=mid+1;i<=r;i++)
	{
		while(hd<tl && k_(dq[hd],dq[hd+1])<=1.0*q[i].k)
			hd++;
		if(hd<=tl)
		{
			int j=dq[hd];
			f[q[i].u] = min(f[q[i].u],q[j].y-q[i].k*q[j].x+h[q[i].u]*h[q[i].u]+s[q[i].u-1]);
		}
	}
	cdq_(mid+1,r);
	inplace_merge(q+l,q+1+mid,q+1+r,cmpx);
}

signed main()
{
	memset(f,INF,sizeof(f));
	cin>>n;
	for(int i=1;i<=n&&cin>>h[i];i++)
		q[i].x = h[i], q[i].k = 2*h[i], q[i].u = i;
	for(int i=1;i<=n&&cin>>s[i];i++)
		s[i] += s[i-1];
	sort(q+1,q+1+n,cmpk);
	f[1] = 0;
	cdq_(1,n);
	cout<<f[n]<<endl;
	
	return 0;
}
```

然后来介绍李超树的写法。

回到最开始的 dp 式子。

$f(i)=f(j)+h_j^2-w_j-2h_jh_i+h_i^2+w_{i-1}$

设 $B(j)=f(j)+h_j^2-w_j,K(j)=-2h_j$。

$f(i)=K(j)h_i+B(j)+h_i^2+w_{i-1}$

前两项是一条直线，求的是所有直线在 $x=h_i$ 处的最小值。我们只要像线段树优化 dp 一样，每次插入一根直线，更新优势线段即可。

下面是李超树的 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mid (l+r>>1)

const int V = 1e6;
const int INF = 2e17;

int n,h[100005],w[100005],f[100005];
int root,cnt=0;
struct lictree{
	int l,r,v;
}t[1000005*30];

int K(int j)
{
	return -2*h[j];
}

int B(int j)
{
	return f[j]+h[j]*h[j]-w[j];
}

int F(int i,int x)
{
	return K(i)*x+B(i);
}

double I(int i,int j)
{
	return 1.0*(B(i)-B(j))/(K(j)-K(i));
}

void insert(int &o,int l,int r,int i)
{
	if(!o)
	{
		o = ++cnt;
		t[o].v = i;
		return;
	}
	int j=t[o].v;
	if(F(i,l)>=F(j,l) && F(i,r)>=F(j,r))
		return;
	else if(F(i,l)<=F(j,l) && F(i,r)<=F(j,r))
	{
		t[o].v = i;
		return;
	}
	double x=I(i,j);
	if(F(i,l)<=F(j,l))
	{
		if(x<=mid) insert(t[o].l,l,mid,i);
		else insert(t[o].r,mid+1,r,j), t[o].v = i;
	}
	else if(F(i,r)<=F(j,r))
	{
		if(x<=mid) insert(t[o].l,l,mid,j), t[o].v = i;
		else insert(t[o].r,mid+1,r,i);
	}
}

int query(int o,int l,int r,int x)
{
	if(!o) return INF;
	int res=F(t[o].v,x);
	if(l==x && r==x)
		return res;
	if(x<=mid)
		res = min(res,query(t[o].l,l,mid,x));
	else
		res = min(res,query(t[o].r,mid+1,r,x));
	return res;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;cin>>h[i++]);
	for(int i=1;i<=n;cin>>w[i++]);
	for(int i=1;i<=n;i++)
		w[i] += w[i-1];
	f[1] = 0;
	insert(root,1,V,1);
	for(int i=2;i<=n;i++)
	{
		f[i] = query(root,1,V,h[i])+h[i]*h[i]+w[i-1];
		insert(root,1,V,i);
	}
	cout<<f[n]<<endl;
	
	return 0;
}
```

下面我们来比较一下两种算法。推式子时 cdq 分治的写法需要把交叉项当成斜率，李超树时要把交叉项变成横坐标。cdq 分治要快一点，但李超树比较简单无脑。

祝大家 AC 愉快！

---

## 作者：xtx1092515503 (赞：2)

一种李超树维护二次函数的解法。

------

什么？李超树还能维护二次函数？

那是因为本题的函数有特殊的性质。

首先，我们很容易写出DP的式子来：

$$f_i=\min\limits_{j<i}\Big\{f_j+(h_i-h_j)^2+(w_i-w_j)\Big\}$$

然后，常规解法是进一步拆式子得到一次函数。然而，这里因为~~我脑抽了~~并没有进一步推下去。于是，便开始思考这个东西有何性质。

明显，我们可以将其转换为一个形如

$$f_i-w_i=\min\Big\{(h_i-k)^2+h\Big\}$$

的式子。

很轻松可以发现，我们得到的是平面上一堆二次函数 $y=(x-k)^2+h$，要求其在 $x=h_i$ 处的最低点。

一次函数李超树的复杂度，依赖于一次函数的**单调性**：两条函数，在中点处更高的那条，一定不会在两端都比另一条低。

常规二次函数李超树的复杂度是无法被保证的，因为在中点处更高的那条在两端有可能都比另一条低，这就使得线段树上修改一个节点时可能其两个子树都要被访问。

但是，我们发现，这里的二次函数有着特殊的性质：它们二次项系数都为 $1$！如果画出图来就会发现，上述中点处更高但两端更低的情形是不可能出现的，也就是说此处的二次函数**就可以同一次函数一样计算**！

于是复杂度为 $O(n\log n)$，轻松解决。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a[100100],m,mn[400100];
ll b[100100],f[100100];
vector<int>v;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1) 
ll calc(int x,int y){return 1ll*(v[x-1]-v[a[y]-1])*(v[x-1]-v[a[y]-1])-b[y]+f[y];}
void modify(int x,int l,int r,int k){
	if(calc(mid,k)<calc(mid,mn[x]))swap(mn[x],k);
	if(calc(l,k)<calc(l,mn[x]))modify(lson,l,mid,k);
	if(calc(r,k)<calc(r,mn[x]))modify(rson,mid+1,r,k);
}
void build(int x,int l,int r){mn[x]=1;if(l!=r)build(lson,l,mid),build(rson,mid+1,r);}
ll query(int x,int l,int r,int P){
	ll ret=calc(P,mn[x]);
	if(l!=r){
		if(P<=mid)ret=min(ret,query(lson,l,mid,P));
		else ret=min(ret,query(rson,mid+1,r,P));
	}
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),v.push_back(a[i]);
	sort(v.begin(),v.end()),v.resize(m=unique(v.begin(),v.end())-v.begin());
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]),b[i]+=b[i-1],a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
	build(1,1,m);
	for(int i=2;i<=n;i++)f[i]=query(1,1,m,a[i])+b[i-1],modify(1,1,m,i);
	printf("%lld\n",f[n]);
	return 0;
} 
```



---

## 作者：寒鸽儿 (赞：2)

题外话： 前几天神tommy教了李超线段树。  

考虑暴力dp， 设$f_i$为打通到第$i$号节点的最小代价, 有  
$$\displaystyle f_i = \min\limits_{1 \leqslant j < i}\{f_j + \sum_{k=j+1}^i w_k + (h_i-h_j)^2\}$$  
记$S_i = \sum_{i=1}^n w_i$, 变形式子  
$$f_i = h_i^2+S_{i-1}+\min\limits_{1 \leqslant j < i}\{-2h_jh_i+f_j+h_j^2-S_j\}$$  
每个$h_j$都会对后面的所有$h_i$进行更新, 这是一个关于$h_i$的一次函数， $k=-2h_j, \space b = f_j + h_j^2-S_j$。  
用李超线段树即可维护即可在$\mathcal{O(\log n)}$求出单点的函数最值。  
复杂度$\mathcal{O(n \log n)}$  
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define repp(i,a,b) for(int i=a;i<(b);++i)
#define perr(i,a,b) for(int i=a;i>(b);--i)

using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, maxn = 123456, maxh = 1234567;
const ll linf = 0x3f3f3f3f3f3f3f3f;

ll h[maxn], k[maxn], b[maxn], s[maxn], f[maxn];

int dat[maxh << 2];

inline ll calc(int id, int x) {
	return k[id] * x + b[id];
}

void insert(int p, int lp, int rp, int id) {
	if(!dat[p]) { dat[p] = id; return; }
	if(lp == rp) {
		if(calc(dat[p], lp) > calc(id, lp)) dat[p] = lp;
		return;
	}
	int mid = lp + rp >> 1;
	ll pre = calc(dat[p], mid), cur = calc(id, mid);
	if(k[dat[p]] < k[id]) {
		if(cur < pre) insert(p<<1|1, mid+1, rp, dat[p]), dat[p] = id;
		else insert(p<<1, lp, mid, id);
	} else if(k[dat[p]] > k[id]) {
		if(cur < pre) insert(p<<1, lp, mid, dat[p]), dat[p] = id;
		else insert(p<<1|1, mid+1, rp, id);
	} else {
		if(cur < pre) dat[p] = id;
	}
}

ll qry(int p, int lp, int rp, int x) {
	if(lp == rp) return calc(dat[p], x);
	int mid = lp + rp >> 1;
	if(x <= mid) return min(calc(dat[p], x), qry(p<<1, lp, mid, x));
	else return min(calc(dat[p], x), qry(p<<1|1, mid+1, rp, x));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	ll mh = 0;
	cin >> n;
	rep(i, 1, n) cin >> h[i], mh = max(h[i], mh);
	rep(i, 1, n) cin >> s[i];
	rep(i, 2, n) s[i] += s[i-1];
	k[0] = b[0] = inf;
	f[1] = 0;
	k[1] = -2 * h[1], b[1] = -s[1] + h[1]*h[1];
	insert(1, 0, mh, 1);
	rep(i, 2, n) {
		f[i] = h[i] * h[i] + s[i-1] + qry(1, 0, mh, h[i]);
		k[i] = -2 * h[i], b[i] = f[i] + -s[i] + h[i] * h[i];
		insert(1, 0, mh, i);
	}
	cout << f[n] << endl;
	return 0;
}
```

---

## 作者：Peter_Z (赞：2)

博客内食用更佳：[博客传送门](https://blog.csdn.net/The_OIer/article/details/100046779)

题目链接：[传送门](https://www.luogu.org/problem/P4655)

## 大致思路

令$sumw$表示$w$的前缀和。

考虑从$j$推到$i$的情况，转移方程显然：

$dp[i]=min(dp[j]+(h[i]-h[j])^2+sumw[i-1]-sumw[j])$


展开，移项，~~一通乱搞~~，得到$2h[i]*h[j]+dp[i]+$常数$=dp[j]+h[j]^2-sumw[j]$

有乘积项，所以要斜率优化。

发现$h$不单调，所以需要CDQ分治。

然后就是CDQ分治+斜率优化的套路：

先把所有点按照$x$坐标排序（本题$x$坐标为$h$），然后CDQ分治时把$id$在$[l,mid]$和$[mid+1,r]$的分成左右两边区间，这样仍然满足左边和右边区间$x$坐标分别单调。

然后套上单调队列+斜率优化即可qwq。

## 代码

```cpp
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<math.h>
#define re register int
#define rl register ll
using namespace std;
typedef long long ll;
int read() {
    re x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {
        if(ch=='-')    f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9') {
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(int x) {
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
const int Size=100005;
namespace I_Love {

ll n,h[Size],w[Size],sumw[Size],dp[Size];
struct node {
	double x,y;
	int id;
} p[Size],tmp[Size],Queue[Size];
inline bool comp(node a,node b) {
	if(a.x!=b.x)	return a.x<b.x;
	return a.id<b.id;
}
inline bool operator < (node a,node b) {
	return a.x<b.x;
}
void Divide(int l,int r) {
	int mid=(l+r)>>1;
	int ptrl=l-1,ptrr=mid;
	for(re i=l; i<=r; i++) {
		if(p[i].id<=mid) {
			tmp[++ptrl]=p[i];
		} else {
			tmp[++ptrr]=p[i];
		}
	}
	for(re i=l; i<=r; i++) {
		p[i]=tmp[i];
	}
}
void Merge(int l,int r) {
	int mid=(l+r)>>1;
	int ptrl=l,ptrr=mid+1,tot=l-1;
	while(ptrl<=mid && ptrr<=r) {
		if(p[ptrl]<p[ptrr]) {
			tmp[++tot]=p[ptrl++];
		} else {
			tmp[++tot]=p[ptrr++];
		}
	}
	while(ptrl<=mid)	tmp[++tot]=p[ptrl++];
	while(ptrr<=r)		tmp[++tot]=p[ptrr++];
	for(re i=l; i<=r; i++) {
		p[i]=tmp[i];
	}
}
inline double slope(node a,node b) {
	return (b.y-a.y)/(b.x-a.x);
}
void CDQ_Divide(int l,int r) {
	if(l==r) {
		p[l].y=dp[l]+h[l]*h[l]-sumw[l];
		return;
	}
	int mid=(l+r)>>1;
   //
	Divide(l,r);
	CDQ_Divide(l,mid);
	int hd=1,tl=0;
	for(re i=l; i<=mid; i++) {
		while(hd<tl && (p[i].y-Queue[tl].y)*(Queue[tl].x-Queue[tl-1].x)<=(Queue[tl].y-Queue[tl-1].y)*(p[i].x-Queue[tl].x))
			tl--;
		Queue[++tl]=p[i];
	}
	for(re i=mid+1; i<=r; i++) {
		while(hd<tl && slope(Queue[hd],Queue[hd+1])<=p[i].x*2)	hd++;
		int x=p[i].id,y=Queue[hd].id;
		dp[x]=min(dp[x],dp[y]+(h[x]-h[y])*(h[x]-h[y])+sumw[x-1]-sumw[y]);
	}
//	if(l==1 && r==n) {
//		puts("我永远喜欢珂朵莉");
//	}
	CDQ_Divide(mid+1,r);
	Merge(l,r);
}
void Kutori() {
	n=read();
	for(re i=1; i<=n; i++) {
		h[i]=read();
		p[i].x=h[i];
		p[i].id=i;
	}
	for(re i=1; i<=n; i++) {
		w[i]=read();
		sumw[i]=sumw[i-1]+w[i];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1]=0;
	sort(p+1,p+1+n,comp);
	CDQ_Divide(1,n);
	printf("%lld",dp[n]);
}

}
int main() {
	I_Love::Kutori();
    return 0;
}
```

---

## 作者：gyyyyx (赞：1)

[题面](https://www.luogu.com.cn/problem/P4655)

李超线段树优化 $\text{dp}$。

本来想学习一下斜率优化的，但发现这题用斜率优化还要套一个 $\text{CDQ}$ 分治，直接放弃。

不会李超线段树的可以看[我的这篇博客](https://www.luogu.com.cn/blog/s19418/li-chao-xian-duan-shu-xue-xi-bi-ji)。

其实这篇博客也有补充到这题的思路，但讲得不清晰，我再简单说一下。

看题，一眼丁真，可用 $\text{dp}$。

设 $dp_i$ 表示将 $1$ 号与 $i$ 号柱子连接的最小代价，随便推一推，转移方程就出来了：

$$dp_i=\min\limits_{1\leq j<i}\{dp_j+(h_i-h_j)^2+\sum\limits_{k=j}^iw_k\}$$

设 $s_i=\sum\limits_{k=1}^iw_k$，则有：

$$
\begin{aligned}
dp_i&=\min\limits_{0\leq j<i}\{dp_j+h_i^2+h_j^2-2h_ih_j+s_{i-1}-s_j\}\\
&=\min\limits_{0\leq j<i}\{(-2h_i)\cdot h_j+(dp_j+h_j^2-s_j)\}+h_i^2+s_{i-1}\\
\end{aligned}
$$

设 $a_j=-2h_j$，$b_j=dp_j+h_j^2-s_j$，则有：

$$dp_i=\min\limits_{0\leq j<i}\{a_jh_i+b_j\}+h_i^2+s_{i-1}$$

问题转化为已知 $i-1$ 条直线 $y=a_jx+b_j$，求 $x=h_i$ 时的 $y$ 的最小值。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define N 100005
#define M 1000005
using namespace std;
int n;LL h[N],s[N],A[N],B[N];
int Best[M<<2];
inline LL GetY(int id,int x){return A[id]*x+B[id];}
inline bool Cmp(int id1,int id2,int x){
	return GetY(id1,x)<GetY(id2,x);
}
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
void Set(int k,int l,int r,int id){
	Best[k]=id;if(l^r) Set(ls,l,mid,id),Set(rs,mid+1,r,id);
}
void Insert(int k,int l,int r,int id){
	if(Cmp(id,Best[k],mid)) swap(id,Best[k]);
	if(l==r||A[id]==A[Best[k]]) return;
	if(A[id]>A[Best[k]]) Insert(ls,l,mid,id);
	if(A[id]<A[Best[k]]) Insert(rs,mid+1,r,id);
}
LL Query(int k,int l,int r,int x){
	if(l==r) return GetY(Best[k],x);
	LL res(GetY(Best[k],x));
	if(x<=mid) return min(res,Query(ls,l,mid,x));
	return min(res,Query(rs,mid+1,r,x));
}
LL dp[N];
int main(){
	scanf("%d",&n);
	for(int i(1);i<=n;++i) scanf("%lld",&h[i]);
	for(int i(1);i<=n;++i) scanf("%lld",&s[i]),s[i]+=s[i-1];
	A[1]=-2*h[1];B[1]=h[1]*h[1]-s[1];Set(1,0,M,1);
	for(int i(2);i<=n;++i){
		dp[i]=Query(1,0,M,h[i])+h[i]*h[i]+s[i-1];
		A[i]=-2*h[i];B[i]=dp[i]+h[i]*h[i]-s[i];
		Insert(1,0,M,i);
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

小清新斜率优化题。

分段问题显然 dp，令 $f_i$ 为将第 $1$ 根柱子和第 $i$ 根柱子连接的最小代价。$f_1=0$，每次枚举 $i$ 向前直接连接的柱子：

$$f_{i}=\min\limits_{j=1}^{i-1}\left\{f_j+(h_i-h_j)^2+\sum\limits_{k=j+1}^{i-1}w_k\right\}$$

令 $s_{i}=\sum\limits_{j=1}^iw_j$，然后把转移拆开，假设最优决策点为 $j$：

$$f_i=f_j+(h_i-h_j)^2+s_{i-1}-s_{j}$$
$$f_i=f_j+h_i^2+h_j^2-2h_jh_i+s_{i-1}-s_{j}$$
$$f_{i}-s_{i-1}-h_i^2=f_j-s_j+h_j^2-2h_j\times h_i$$

平凡的斜率优化会把上式写成 $b=y-xk$ 的形式，但我们旋转一下坐标系，令 $y_i=f_{i}-s_{i-1}-h_{i}^2$，$b_j=f_j-s_j+h_j^2$，$k_j=-2h_j$，$x_i=h_i$：

$$y_i=k_jx_i+b_j$$

于是我们得到了斜率优化的另一种形式。


我们可以将转移点 $j$ 看作平面上的一条条形如 $y=k_jx+b_j$ 的直线，每次即查询一个 $x$ 坐标上 $y$ 坐标最小的值，支持动态插入一条直线。

李超线段树维护即可。复杂度 $O(n\log w)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define pi pair<int, int>
	#define mp make_pair
	#define fi first
	#define se second
	#define pb push_back
	#define ins insert
	#define era erase
	inline int read () {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using vbzIO::read;
using vbzIO::write;

const int maxn = 1e5 + 100;
const int maxw = 1e6 + 100;
const int inf = 1e18;
int n, h[maxn], w[maxn], s[maxn], f[maxn], tr[maxw << 2];

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
int K(int id) { return - 2 * h[id]; }
int B(int id) { return id ? (f[id] - s[id] + h[id] * h[id]) : inf; }
int gety(int id, int x) { return K(id) * x + B(id); }
int cmp(int x, int y) { return x == y ? 0 : (x > y ? 1 : -1); }
void push(int l, int r, int s, int x) {
    int &t = tr[x];
    if (cmp(gety(s, mid), gety(t, mid)) == -1) swap(s, t);
    int fl = cmp(gety(s, l), gety(t, l)), fr = cmp(gety(s, r), gety(t, r));
    if (fl == -1 || (!fl && s < t)) push(l, mid, s, ls);
    if (fr == -1 || (!fr && s < t)) push(mid + 1, r, s, rs);
}

int qry(int l, int r, int p, int x) {
    if (l == r) return gety(tr[x], p);
    int res = gety(tr[x], p);
    if (p <= mid) return min(res, qry(l, mid, p, ls));
    else return min(res, qry(mid + 1, r, p, rs));
}

signed main() {
	n = read();
    for (int i = 1; i <= n; i++) h[i] = read();
    for (int i = 1; i <= n; i++) w[i] = read(), s[i] = s[i - 1] + w[i];
    push(0, 1e6, 1, 1);
    for (int i = 2; i <= n; i++) {
        int j = qry(0, 1e6, h[i], 1);
        f[i] = j + s[i - 1] + h[i] * h[i];
        push(0, 1e6, i, 1);
    }
    write(f[n]);
	return 0;
}
```

---

## 作者：_lxy_ (赞：1)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/P4655-Solution.html)
#### 分析

发现如果在 $i,j$ 之间建桥，那么 $(i,j)$ 内的所有柱子都是无用的，代价还需加上 $(i,j)$ 内的所有拆除代价。设 $dp_i$ 为从 $1$ 走到 $i$ 的最小代价，于是转移方程就呼之欲出了：
$$
dp_i=\min\limits_{j=1}^{i-1}\{dp_j+(h_i-h_j)^2+s_{i-1}-s_j\}
$$
，其中 $s_i$ 表示拆除代价的前缀和。发现如果枚举每一个 $j$ 时间复杂度是 $\mathcal{O}(n^2)$，显然会 TLE，因此考虑优化。发现这个式子是很典型的斜率优化形式，可以变形为：
$$
dp_i=\min\limits_{j=1}^{i-1}\{dp_j-2h_ih_j+h_j^2-s_j\}+h_i^2+s_{i-1}
$$
然而发现每次查询的斜率并不是有序的，因此不能直接单调队列维护凸包。发现数据范围只到 $10^5$，用李超线段树可以方便的求出当 $x=h_i$ 时最小的 $y$，于是就可以做了。时间复杂度 $\mathcal{O}(n\log n)$。

#### 核心代码

```cpp
qread(n);int i,j,mx=0;for(i=1;i<=n;i++) qread(h[i]),mx=qmax(mx,h[i]);
build(1,0,mx);for(i=1;i<=n;i++) qread(w[i]),w[i]+=w[i-1];
dp[1]=0;upd(1,0,mx,Line{-2*h[1],h[1]*h[1]-w[1]});
for(i=2;i<=n;i++){
    dp[i]=que(1,0,mx,h[i])+h[i]*h[i]+w[i-1];
    upd(1,0,mx,Line{-2*h[i],dp[i]+h[i]*h[i]-w[i]});
}printf("%lld\n",dp[n]);
```

[record](https://www.luogu.com.cn/record/86519916)

---

## 作者：神光qwq (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P4655)

## 思维历程

首先应当思考不带优化的 dp，再进行优化。

先列出最朴素的式子。
$$f_i=\min_{j=1}^{j \le i}\{f_j+(h_i-h_j)^2+sum_{i-1}-sum_j\}$$

其中 $sum_j=\sum_{i=1}^ja_i$，再将与 $i$ 有关项提出。

$$f_i={h_i}^2+sum_{i-1}+\min_{j=1}^{j \le i}\{f_j-2h_ih_j+{h_j}^2-sum_j\}$$

观察到其中有一项为 $-2h_ih_j$，与 $i$ 和 $j$ 都有关，且结合数据范围达到 $10^6$，那么就可以采用李超树进行优化。

简单讲一下李超树的实现，插入直线其实就是对一个区间，首先判断其中点，若新加入直线更优直接交换新旧编号，接下来对两端判断，若新直线（此处表示交换后的 $x$）更优则继续查找下去。

而查询则是正常类似线段树的写法，但是注意要和当前存的直线的取值比较取更优，因为李超树存的其实是**可能的**最优直线，还是会有例外的，不会的可以左转[这里](https://www.luogu.com.cn/problem/P4254)。

首先设 $k=-2h_j$，$x=h_i$，$b=f_j+{h_j}^2-sum_j$（把和 $i$ 有关的设为未知量，用李超树维护之前所有 $k$ 和 $b$ 的最优取值），维护此时的 $y$ 为最小值，其实就是把 $y=kx+b$ 视为一条直线，求对于确定的 $x$ 在之前的哪条直线上的取值最小，得到的就是答案。

对于第一个点直接处理并加入李超树中，对于之后的点先计算取值再加入李超树。

**三个小坑点：**

- 记得开 `long long`。

- 李超树由于叶子节点是区间上的点所以节点空间大小记得开四倍。

- 记得初始化 $b_0$ 同时赋值要大亿点。

~~本人拙见，如有差错，请赐教。~~

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define void inline void
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const ll N=1e6+10;
ll n,h[N],sum[N],dp[N],k[N],b[N],pre[N<<2];
inline ll read(){
	char ch=getchar();ll res=0,f=1;
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
inline ll v(ll num,ll x){//对于x在第num条直线上的取值。
	return k[num]*x+b[num];
}
void modify(ll rt,ll l,ll r,ll x){//这里是插入第x条直线。
	ll mid=(l+r)>>1;
	if(v(x,mid)<v(pre[rt],mid))	swap(x,pre[rt]);
	if(v(x,l)<v(pre[rt],l)) modify(ls,l,mid,x);
	if(v(x,r)<v(pre[rt],r)) modify(rs,mid+1,r,x);
}
inline ll query(ll rt,ll l,ll r,ll x){
	if(l==r) return v(pre[rt],x);
	ll mid=(l+r)>>1;
	if(x<=mid) return min(v(pre[rt],x),query(ls,l,mid,x));//记得取min。
	else return min(v(pre[rt],x),query(rs,mid+1,r,x));
}
int main(){
	n=read(),b[0]=1e18;//一开始默认第0条，所以必须初始化。
	for(ll i=1;i<=n;i++) h[i]=read();
	for(ll i=1;i<=n;i++) sum[i]=read(),sum[i]+=sum[i-1];
	k[1]=-2*h[1],b[1]=h[1]*h[1]-sum[1],modify(1,0,N,1);//第一条直接插入。
	for(ll i=2;i<=n;i++){
		dp[i]=query(1,0,N,h[i])+h[i]*h[i]+sum[i-1];
		k[i]=-2*h[i],b[i]=dp[i]+h[i]*h[i]-sum[i],modify(1,0,N,i);
	}
	printf("%lld",dp[n]);
	return 0;
}
```

---

