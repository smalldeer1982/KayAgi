# New Year and Castle Construction

## 题目描述

给定大小为 $N$ 的点集 $S$。保证点集中的任意三点不共线，且不存在重复的点。

设 $f(p)$ 表示满足如下条件的 $S$ 的四元子集 $T$ 的个数：

1. $T \subset S\ \land p \notin T$
2. $T$ 中的元素能组成一个四边形，且满足 $p$ 在四边形内部。

请你求出的 $\sum_{p \in S} f(p)$ 的值。

## 样例 #1

### 输入

```
5
-1 0
1 0
-10 -1
10 -1
0 3```

### 输出

```
2```

## 样例 #2

### 输入

```
8
0 1
1 2
2 2
1 3
0 -1
-1 -2
-2 -2
-1 -3```

### 输出

```
40```

## 样例 #3

### 输入

```
10
588634631 265299215
-257682751 342279997
527377039 82412729
145077145 702473706
276067232 912883502
822614418 -514698233
280281434 -41461635
65985059 -827653144
188538640 592896147
-857422304 -529223472```

### 输出

```
213```

# 题解

## 作者：Kewth (赞：25)


考虑一个 5 个点构成的集合（简称 5-set ），有三种情况：

1. 凸包是五边形，那么这个 5-set 不可能是一个四边形内部一个点
2. 凸包是四边形，那么这个 5-set 只可能是凸包作为四边形取包含里面那个点
3. 凸包是三角l形，那么这个 5-set 可以选出两个四边形来分别包含凸包内的两个点

记上面三种 5-set 的个数分别为 $x_5, x_4, x_3$ ，那么答案就是 $x_4 + 2x_3$ 。

赛时感觉分别统计 $x_4, x_3$ 没思路了，赛后看见出题人给出了一个惊为天人的做法。

容易知道 $X = x_5 + x_4 + x_3 = C_n^5$ ，设 $Y = 5x_5 + 4x_4 + 3x_3$ ，  
那么答案 $ans = 5X - Y$ ，问题转换为求 $Y$ 。

这个 $Y$ 的形式非常优美，就是每个 5-set 的凸包的边数的和。

枚举每条边 E ，考虑它在多少个 5-set 中作为凸包，那么 E 已经可以确定两个点，  
就是考虑有多少 3-set 全部在 E 的一端，假设 E 的一端有 k 个点，  
那么这一端的贡献就是 $C_k^3$ ，而统计一条边一端的点数是很容易的，  
只需要枚举一个顶点 x 然后对于 x 引出的每条边极角排序，  
按极角序枚举每条边的同时维护一端即可，复杂度 $O(n^2logn)$ 。

然而卡精度还卡常，不能使用 atan2 以及 double 甚至 long double 运算。

需要用向量叉积代替极角以避免 double 带来的精度误差以及 atan2 的频繁调用带来的时间开销。

参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 2505;
int x[maxn], y[maxn];
struct Vec {
	int x, y;
};
Vec v[maxn << 1];

ll cross(Vec a, Vec b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

inline ll C(ll n, int m) {
	ll res = 1;
	for(int i = 0; i < m; i ++) (res *= n - i) /= i + 1;
	return res;
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		read(x[i], y[i]);

	ll X = C(n, 5), Y = 0;
	for(int i = 1; i <= n; i ++) {
		int vp = 0;
		for(int j = 1; j <= n; j ++)
			if(j != i)
				v[++ vp] = Vec({x[j] - x[i], y[j] - y[i]});
		std::sort(v + 1, v + vp + 1, [](Vec a, Vec b) {
					int ain = a.y < 0 or (a.x > 0 and a.y == 0);
					int bin = b.y < 0 or (b.x > 0 and b.y == 0);
					if(ain != bin) return ain < bin;
					return cross(a, b) > 0;
				});

		for(int j = 1; j <= vp; j ++)
			v[vp + j] = v[j];

		int las = 1;
		for(int j = vp + 1; j <= (vp << 1); j ++) {
			while(las + vp <= j or cross(v[j], v[las]) > 0) ++ las;
			Y += C(j - las, 3);
		}
	}

	printf("%lld\n", X * 5 - Y);
}
```

---

## 作者：jiazhaopeng (赞：6)

这里提供一种新的做法。

用四边形框起来一个点看起来比较难统计，而用三角形框住一个点则较为简单。设四边形的方案数为 $Y$，三角形的方案数为 $X$。可以发现，$Y = \frac{(n-4)}{2}X$。证明：对于一种四边形（不一定是凸四边形）框一个点的情况，可以连上任意一条对角线，转化为三角形框一个点后再选一个点（可以在三角形内部）。并且如果我们按 $(n-4)X$ 计数的话每种四边形的情况会被算恰好两遍（因为选每条对角线都会被算一次）。

考虑如何计算 $X$。枚举被框住的点 $A$，将其余点极角排序。枚举两个点 $B,C$，第三个点可以是图中阴影部分的点。直接做可以做到 $O(n^3)$。

![CF1284E](https://cdn.luogu.com.cn/upload/image_hosting/zg9s2e5p.png)

前缀和优化一下，大概是 $S_B - S_C$ 的形式，其中 $S_B$ 表示一条射线从 $Y$ 轴负方向逆时针旋转到 $\overrightarrow{BA}$ 所经过的点的数量。通过处理 $S_C$ 的前缀和，我们可以在枚举 $B$ 的时候计算所有 $C$ 的贡献。复杂度 $O(n^2)$，算上极角排序的复杂度为 $O(n^2 \log n)$。

还是有一些细节的。具体细节看代码吧。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#define N 2511
typedef long long ll;
template<typename T> inline void read(T &x) {
	x = 0; char c = getchar(); bool flag = false;
	while (!isdigit(c)) { if (c == '-') flag = true; c = getchar(); }
	while (isdigit(c)) x = x * 10 + (c ^ 48), c = getchar();
	if (flag)	x = -x;
}
using namespace std;
int n;
struct Vectors {
	ll x, y;
	Vectors(ll xx = 0, ll yy = 0) { x = xx, y = yy; }
	inline Vectors operator +(const Vectors &a) const {
		return Vectors(x + a.x, y + a.y);
	}
	inline Vectors operator -(const Vectors &a) const {
		return Vectors(x - a.x, y - a.y);
	}
	inline ll operator *(const Vectors &a) const {
		return x * a.y - y * a.x;
	}
}vt[N], h[N];
int htot;
ll ans;
inline bool cmp(const Vectors &a, const Vectors &b) {//极角排序
	if (a.y < 0 && b.y > 0)	return true;
	if (a.y > 0 && b.y < 0)	return false;
	if (a.y == 0 && a.x < 0) return true;
	if (b.y == 0 && b.x < 0) return false;
	return a * b > 0;
}
int f[N], sum[N];
inline void calc(int p) {
	htot = 0;
	for (int i = 1; i <= n; ++i) if (i != p) h[++htot] = vt[i] - vt[p];
	sort(h + 1, h + 1 + htot, cmp);
	int ptr = htot;//上下方的分界点
	for (int i = 1; i <= htot; ++i) if (h[i].y > 0 || (h[i].y == 0 && h[i].x > 0)) {
		ptr = i; break;
	}
	int pt = htot - 1;
	for (int i = htot; i >= ptr; --i) {//双指针求 S_A
		while (pt && h[pt] * h[i] > 0) --pt;
		f[i] = pt;
	}
	sum[ptr - 1] = 0;
	for (int i = ptr; i <= htot; ++i) sum[i] = sum[i - 1] + f[i];//前缀和优化计算答案
	for (int i = ptr + 1; i <= htot; ++i) {
		ans += f[i] * (i - ptr) - sum[i - 1];
	}
}
int main() {
	read(n);
	for (int i = 1; i <= n; ++i) read(vt[i].x), read(vt[i].y);
	for (int i = 1; i <= n; ++i) calc(i);//统计 B,C 都在 A 上方的情况
	for (int i = 1; i <= n; ++i) vt[i].x = -vt[i].x, vt[i].y = -vt[i].y;
	for (int i = 1; i <= n; ++i) calc(i);//统计 B,C 都在 A 下方的情况
	ans = (ans * (n - 4)) >> 1;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：QwQcOrZ (赞：5)

考虑对于每个点算出 $f(p)$

设 $p$ 的坐标在点 $P$，四边形的四个顶点分别为 $A,B,C,D$。

随便观察一下得知 $P$ 在四边形内的条件为四个向量 $\overrightarrow{PA},\overrightarrow{PB},\overrightarrow{PC},\overrightarrow{PD}$ 不在同一个半平面内。

证明显然，因为向量在同一个半平面内时四边形的四个顶点在 $P$ 的同一侧。

枚举点 $p$，将所有向量按极角排序，然后计算所有的四边形减掉不合法的四边形数量。

不合法的四边形数量可以通过枚举极角最大的向量然后双指针计算。

$\texttt{Code Below}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
const int N=2505;
const long double pi=acos(-1.0L);

ll read(){static ll x;scanf("%lld",&x);return x;}
void write(ll x){printf("%lld",x);}
void print(ll x,char c='\n'){write(x),putchar(c);}

long double a[N];
int C[N][4],x[N],y[N];

signed main()
{
	int n=read(),ans=0;
	for (int i=1;i<=n;i++) x[i]=read(),y[i]=read();
	for (int i=C[0][0]=1;i<=n;i++)
	for (int j=C[i][0]=1;j<=3;j++)
	C[i][j]=C[i-1][j-1]+C[i-1][j];
	for (int k=1;k<=n;k++)
	{
		int m=0;
		for (int i=1;i<=n;i++) if (i!=k) a[++m]=atan2((long double)(y[i]-y[k]),(long double)(x[i]-x[k]));
		sort(a+1,a+1+m);
		for (int i=1,j=1,k=1;i<=m;i++)
		{
			while (j<=i&&a[i]-a[j]>pi) j++;
			while (k<=m&&a[k]-a[i]<pi) k++;
			ans+=C[i-1][3]-C[j-1+k-i-1][3];
            //第一个组合数计算的是所有四边形数量，第二个组合数计算的是不合法的四边形数量
		}
	}
	print(ans);
	
	return 0;
}
```

另外，这题卡精度，记得把所有实数运算全部开上 `long double`

---

## 作者：CYJian (赞：4)

我看目前已有的题解，好像做法都和我的不同啊 QwQ。这里就介绍一下我的赛时做法吧（赛时的极角排序写挂了一直 WA on test 4...看半天硬是没看出来）

---

我的做法是基于以下这个结论的：

> 对于一个点 $O$，若其在四边形 $ABCD$ 的内部，且 $A$、$B$、$C$、$D$ 是按照以 $O$ 为参照点顺时针方向排列，那么满足：$OA \times OB < 0$，$OB \times OC < 0$，$OC \times OD < 0$，$OD \times OA < 0$。

正确性？我只能说过于显然。知道叉积应该就能 Get 吧。

然后我们考虑这样一个计数方法：

1. 枚举四边形的内部点 $O$
2. 枚举钦定为四边形顶点的点 $A$
3. 统计以 $O$ 为起点，在 $\overrightarrow{OA}$ 顺时针方向 $180 \degree$ 内的向量个数 $x$，在 $\overrightarrow{OA}$ 逆时针方向 $180 \degree$ 内的向量个数 $y$
4. 将答案加上 $x \times \binom{y}{2}$，再减去 $\binom{y}{3}$

为啥是对的呢？

首先我们先枚举一个内部的点 $O$ 和四边形上的一个点 $A$。

考虑一个 naive 的想法：如果我们在 $\overrightarrow{OA}$ 一侧选择一个点，另一侧选择两个点，这样的四边形就能满足条件。

但是事实上并不是所有的都满足条件。我们考虑下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ln6uv4t4.png)

在我们枚举点 $O$ 和点 $C$ 时，$B$、$C$、$D$、$E$ 组成的四边形我们会计算一次。但是这个四边形没有包括 $O$。

考虑这样不合法的四边形会有啥特征：会存在一个四边形上的点，在向量的顺时针方向 $180\degree$ 内，其它三个点都在范围内！

也就是说，我们只需要在枚举每个向量的时候，减去这样的四边形个数就行了。

并且不难发现，这样的不合法的四边形只会恰好被加一次，减一次，所以正好抵消了。

然后再考虑合法的四边形：比如上图中的四边形 $ACDE$ 就是一个合法的四边形。但是除了在枚举 $C$ 的时候会被计算一次外，我们发现，在枚举 $A$ 的时候也会被计算一次！

那么合法的四边形都只会被恰好计算两次么？

我们考虑这样一个事情：因为 $\angle AOC + \angle COD + \angle DOE + \angle EOA = 360 \degree$，且 $\angle AOC < 180 \degree,\angle COD < 180 \degree,\angle DOE < 180 \degree,\angle EOA < 180 \degree$，且任意三点不共线。那么一定不存在相邻两个角都为 $90\degree$。
然后可以分类讨论了：

一、三个锐/直角，一个钝角：

显然有两对角度数和小于 $180\degree$。再考虑锐角和钝角的和：如果小于 $180\degree$，则会出现：另外两个锐/直角度数和大于 $180\degree$ 的超自然现象。

二、两个锐/直角，两个钝角：

同样使用上面的反证法，可以得到的确只有两对相邻的角的度数小于 $180\degree$。

---

那么我们就只需要将上面计数出来的答案除以二就得到了答案。

统计的时候如果暴力统计复杂度就是 $O(n^3)$，如果使用极角排序后 `Two-Points` （貌似也可以叫成尺取法）计算，复杂度为 $O(n^2 \log n)$

~~这个做法可以求出每个点的 $f$ 值，貌似可以算成一种加强卡掉一些别的做法 QwQ~~

Code：(头文件请自行补充)

```cpp
const int MAXN = 10000;

struct Node {
	int x, y;

	Node() {}
	Node(int x, int y):x(x), y(y) {}

	inline void rd() { x = read(), y = read(); }

	friend Node operator + (Node a, Node b) { return Node(a.x + b.x, a.y + b.y); }
	friend Node operator - (Node a, Node b) { return Node(a.x - b.x, a.y - b.y); }
	friend ll operator * (Node a, Node b) { return 1LL * a.x * b.y - 1LL * a.y * b.x; }
}a[MAXN], b[MAXN];

inline bool cmp(Node a, Node b) {
	// if(1LL * a.x * b.x == 0) return !a.x ? (a.y > 0 || b.x < 0) : !(b.y > 0 || a.x < 0);
	// else if(1LL * a.x * b.x < 0) return a.x > b.x;
	// 比赛的时候作死，硬要分象限讨论，然后上面一个 if 没写全当场暴毙
	return a * b < 0;
}

int main() {
	int n = read(); ll res = 0;
	for(int i = 1; i <= n; i++) a[i].rd();
	for(int i = 1; i <= n; i++) {
		int N = 0;
		for(int j = 1; j <= n; j++) if(i != j) b[++N] = a[j] - a[i];
		sort(b + 1, b + 1 + N, cmp);
		for(int j = 1; j <= N; j++) b[j + N] = b[j];
		for(int l = 1, r = 2; l <= N; l++) {
			while(r < l + N && b[l] * b[r] <= 0) ++r;
			int n1 = r - l - 1, n2 = N - n1 - 1;
			res += 1LL * n1 * n2 * (n1 - 1) / 2;
			res -= 1LL * n1 * (n1 - 1) * (n1 - 2) / 6;
		}
	}
	cout << res / 2 << endl;
	return 0;
} // 出乎意料的好写呢（但比赛的时候还是写挂了 QwQ
```

---

## 作者：Yuby (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1284E)

有参考各位大佬和 codeforces 官方题解的思路，主要补充了一些其他题解缺少的小细节，比如破环为链的细节。不喜勿喷。

点数:2500

### 前置知识：

#### 极角排序。

在 $n$ 个点中选择一个点作为原点，并计算其他节点的相对于原点的极坐标，可以理解为重建坐标系，建成一个极坐标系。之后我们按照新坐标对其排序。得到的就是一个用斜率排序，和距离排序的点集了。

### 凸包

自己去学吧，我不会（懒得）讲。

## 分析

这是一道神奇的组合数+容斥题。

定义 5-set 为：从给定的点集选择任意 5 点组成的子集。

我们发现其实题目可以转化为求 5 给节点使得 4 个节点包围另外一个，这 4 个节点连成的图形刚好应该是这 5 个节点的凸包，因为这样才能保证包围另一节点。考虑每一组 5 个节点。注意到不存在任意三点共线，那么对于所有的 5-set 的凸包只存在 3 中情况：

1. 凸包为一个三角形。对答案贡献为 2。容易发现凸包内部两点满足题意。
2. 凸包为一个四边形。对答案贡献为 1。容易发现只有不在凸包上的那一点满足要求。
3. 凸包为一个五边形。对答案无贡献，任意选择一点都不在另外四个点连成的四边形内部。

设这三种情况的个数分别为 $x_1$，$x_2$，$x_3$，答案就是 $2x_1+x_2$。其中我们发现 $x_1+x_2+x_3=\dbinom{n}{5}=C_n^5$。这时 codeforces 的官方题解引入了一个巧妙的容斥。我们发现 $ans=5\times\dbinom{n}{5}-5\times x_3-4\times x_2-3\times x_1$。设 $y=5\times x_3-4\times x_2-3\times x_1$ 那么 $y$ 相当于就是所有 5-set 的凸包边数之和。问题转化为求左右 5-set 的凸包的边数之和。

直接枚举 5 个节点的时间复杂度显然是不能接受的，我们尝试计算每条边对此的贡献，即枚举每一条边。一条边确定了两个点，那么只需再找出 3 个节点使得已经确定的边在凸包上。由于我们不关心另外 3 个点的任何情况，可以发现这三点只需都在这条直线一侧即可。这时我们进行极角排序，双指针维护即可。注意！在极角排序之后这些点挨个连在一起实际上形成了一个环而不是一条链，这时需要我们破环为链进行维护。原因很简单，我们发现枚举的边的斜率是具有单调性的，但是我们假设我们从斜率最小的边 $x$，开始枚举，当枚举到某一条边时，这条边右侧（这里指这个人在这条边离原点近的点朝向离原点较远的点）的点实际上就是边 $x$ 的左侧的点，所以实际是一条链。这里读者可以自己画图辅助理解。

这题卡精度和系统自带的三角函数，用向量叉积替代。

复杂度：$O(n^2\log n^2)$。核心代码如下：

```cpp
const ll MAXN=5007;
ll n,C[MAXN][7];
struct node
{
	ll x,y;
}a[MAXN],v[MAXN];
ll cross(const node& xx,const node& yy)
{
	return xx.x*yy.y-xx.y*yy.x;
}
bool cmp(const node& xx,const node& yy)
{
	ll flagx=(xx.y<0)|((xx.y==0)&(xx.x>0)),flagy=(yy.y<0)|((yy.y==0)&(yy.x>0));
	if(flagx!=flagy)return flagx<flagy;
	return cross(xx,yy)>0;
}
int main()
{
	n=read();
	for(ll i=1;i<=n;i++)
	{
		a[i].x=read(),a[i].y=read();
	}
	for(ll i=0;i<=n;i++)
	{
		C[i][0]=1;
		if(i<=5)C[i][i]=1;
		for(ll j=1;j<=min(i,5);j++)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	ll ans=0;
	for(ll i=1;i<=n;i++)
	{
		ll cnt=0;
		for(ll j=1;j<=n;j++)if(j!=i)
			v[++cnt]=node{a[j].x-a[i].x,a[j].y-a[i].y};
		sort(v+1,v+cnt+1,cmp);
		for(ll j=1;j<=cnt;j++)v[cnt+j]=v[j];
		ll las=1;
		for(ll j=cnt+1;j<=(cnt<<1);j++)
		{
			while(las+cnt<=j||cross(v[j],v[las])>0)las++;
			ans+=C[j-las][3];
		}
	}
	write(5*C[n][5]-ans);
	return 0;
}
```



---

## 作者：Purple_wzy (赞：1)

题面：https://codeforces.com/problemset/problem/1284/E

题解：

考虑一个五元组形成凸包的情况。

由于三点不共线，因此只可能有三种情况：

1.凸包含有3个点：此时贡献为2;

2.凸包含有4个点：贡献为1;

3.凸包含有5个点：贡献为0。

设这三种情况的个数分别为$x_3$,$x_4$,$x_5$,

那么答案即为2$x_3$+$x_4$。

这个东西很不好求，考虑转化。

首先发现$x_3$+$x_4$+$x_5$=$C(n,5)$

其次，发现如果能求出3$x_3$+4$x_4$+5$x_5$,

那答案就很容易求出。这个式子的几何意义即为

$\sum$每一条边所在的凸包数。

用双指针求出这个东西即可。

时间复杂度：O($n^2$logn)

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register ll
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline ll
#define STS system("pause")
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
typedef pair<ll,ll>pii;
struct Vec{
	ll x,y;
	Vec(ll _x=0,ll _y=0){x=_x;y=_y;}
	friend Vec operator + (Vec a,Vec b){return Vec(a.x+b.x,a.y+b.y);}
	friend Vec operator - (Vec a,Vec b){return Vec(a.x-b.x,a.y-b.y);}
	friend ll operator ^ (Vec a,Vec b){return a.x*b.y-a.y*b.x;}
	friend bool operator < (Vec a,Vec b){
		pii A=make_pair(a.x,a.y),B=make_pair(b.x,b.y);
		bool c=A<make_pair(0ll,0ll),d=B<make_pair(0ll,0ll);
		return c==d?(a^b)>=0:c<d;
	}
}p[2550];
vector<Vec>v;
ll n,m,ans,cnt;
IN C(ll x,ll y){
	re res=1;
	F(i,0,y-1){res*=(x-i);res/=(i+1);}
	return res;
}
int main(){
	read(n);
	F(i,1,n)read(p[i].x),read(p[i].y);
	F(i,1,n){
		v.clear();
		F(j,1,n){
			if(i==j)continue;
			v.emplace_back(p[j]-p[i]);
		}		
		sort(v.begin(),v.end());
		m=0;
		F(j,0,v.size()-1){
			while(m<j+v.size()&&(v[j]^v[m%v.size()])>=0)m++;
			cnt+=C(m-j-1,3);
		}
	}
	ans=C(n,5)*5ll-cnt;
	cout<<ans;
	return 0;
}
```
推荐一下我的博客：https://www.cnblogs.com/Purple-wzy/

---

## 作者：JWRuixi (赞：0)

### 题意

给定点集 $S$，满足任意三点不共线。记 $f(p)(p \in S)$ 表示从点集中选出四个点，满足其围成的四边形能严格包含 $p$，的方案数。求 $\sum\limits_{p \in S} f(p)$。

$n \le 2.5 \times 10^5, |x|, |y| \le 10^9$。

### 分析

考虑枚举 $p$，以 $p$ 为原点，相当于求能包含原点的四边形数。

但是这太难了，我不会！

但是我还会正难则反！

先进行极角排序，我们再枚举四边形的一个端点，发现能使矩形不合法的其它端点的可选集合是一个连续区间（即数组上最远的点满足两点的连线在 $p$ 之上），于是用双指针就结束了！

这题恶心人，它卡精。但是我会 `acosl` 和 `atan2l`，道高一尺，魔高一丈！

### Code

提交记录：<https://codeforces.com/contest/1284/submission/253939566>。

---

## 作者：Hanx16Kira (赞：0)

# New Year and Castle Construction

[Luogu CF1284E](https://www.luogu.com.cn/problem/CF1284E)

## Solution

看数据范围感觉可以 $\mathcal O(N^2)$ 的做，然后对于题目要统计的东西显然四边形内部的那个点最特殊，所以不妨就枚举最中间的这个点来统计答案。

考虑如何选这 $4$ 个点。观察一下性质，如果直接找四个点感觉上没法做，因为这 $4$ 个点相互约束，并且约束条件都不一致，所以考虑熔池一下，考虑什么样的 $4$ 个点不会成为答案。

枚举最中间的点，然后从中心点向所有点作一条射线，那么如果一组点不会成为答案，那么这一组点的射线必定不会处在同一半平面上。考虑怎么计数，先将所有的射线极角排序，然后使用双指针即可找出所有不合法的射线区间。设不合法的区间大小为 $k$，那么这个区间将对答案造成 $-\displaystyle\binom{k}{4}$ 的贡献。总共的答案数量即 $n\times\displaystyle\binom{n-1}{4}$。

时间复杂度为 $\mathcal O(n^2\log n)$。

首先计算 `atan2` 时需要开 `long double`，否则会被卡精度。其次，需要先计算出所有射线的极角后再进行排序，否则计算 `atan2` 的常数极大，极限数据需要跑 $10$ 秒。

```cpp
struct Vec {
    int x, y;
    Vec(int x = 0, int y = 0) : x(x), y(y) {}
    Vec operator + (const Vec& rhs) const {return Vec(x + rhs.x, y + rhs.y);}
    Vec operator - (const Vec& rhs) const {return Vec(x - rhs.x, y - rhs.y);}
    i64 operator * (const Vec& rhs) const {return 1ll * x * rhs.y - 1ll * rhs.x * y;}
};
int N, tot;
Vec poi[_N];
pair<long double, Vec> p[_N];
inline i64 sel3(int x) {return x < 3 ? 0 : 1ll * x * (x - 1) * (x - 2) / 6;}
inline i64 sel4(int x) {return x < 4 ? 0 : 1ll * x * (x - 1) * (x - 2) * (x - 3) / 24;}
i64 solve(int id) {
    tot = 0; Vec cp = poi[id];
    auto getAng = [](const Vec& i, const Vec& j)->long double {
        return atan2l(i.x - j.x, i.y - j.y);
    };
    For(i, 1, N) if (i != id) p[++tot] = {getAng(poi[i], cp), poi[i]};
    sort(p + 1, p + tot + 1, [&cp](const auto& i, const auto& j) {
        return i.first > j.first;
    });
    i64 res = sel4(tot);
    auto nxt = [&](int x)->int {return x == tot ? 1 : x + 1;};
    for (int i = 1, j = 2; i <= tot; ++i) {
        while ((cp - p[i].second) * (p[j].second - cp) < 0) j = nxt(j);
        res -= j > i ? sel3(j - i - 1) : sel3(j + tot - i - 1);
    }
    return res;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    For(i, 1, N) cin >> poi[i].x >> poi[i].y;
    i64 ans = 0;
    For(i, 1, N) ans += solve(i);
    cout << ans << '\n';
}
```

---

