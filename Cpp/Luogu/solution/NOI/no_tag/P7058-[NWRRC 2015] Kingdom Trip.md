# [NWRRC 2015] Kingdom Trip

## 题目描述

从前有一个王国，由一位聪明的国王统治。在他统治的四十三年间，通过成功的军事行动和娴熟的外交手段，王国变成了一个无限平坦的二维平面。这样的形式极大地简化了旅行，因为没有边界。

王国计划举办一个盛大的节日。有 $n$ 个地点供人们聚集。国王希望能更近距离地观察他的子民，因此他下令在这些地点之间进行旅行。他希望在每个地点发表演讲。最初，他的旅行被设计为一个多边形链 $p$：$p_{1} \to p_{2} \to \ldots \to p_{n}$。

国王不仅聪明，而且年事已高。因此，他的助手们想出了一个主意，跳过一些地点，以便让国王尽可能少地发表演讲。新的旅行计划必须是由 $p$ 的某个子序列组成的多边形链：从 $p_{1}$ 开始，到 $p_{n}$ 结束，形式上为 $p_{i_{1}} \to p_{i_{2}} \to \cdots \to p_{i_{m}}$，其中 $1 = i_{1} < i_{2} < \cdots < i_{m} = n$。助手们知道，如果从 $p_{j}$ 到线段 $p_{i_{k}} \to p_{i_{k+1}}$ 的距离超过 $d$，对于这样的 $k$，即 $i_{k} < j < i_{k+1}$，国王不会允许跳过地点 $j$。

帮助助手们找到包含最少可能地点的新路线。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 2
2 6
8 2
14 2
12 9
13 8
```

### 输出

```
3
```

# 题解

## 作者：ix35 (赞：3)

求出 $chk(i,j)$ 表示是否对所有 $k\in (i,j)$ 都有 $P_k$ 到 $P_iP_j$ 的距离不超过 $d$，随后我们用 $dp(i)$ 表示到达 $i$ 能经过的最少点数然后随便 DP 就可以了。

那么如何求 $chk(i,j)$ 呢？

考虑某个 $k>i$，如果要满足 $P_k$ 到 $P_iP_j$ 距离不超过 $d$，那么：

- 若 $P_kP_i\leq d$，那么没有限制；

- 否则，$P_iP_j$ 与 $P_iP_k$ 的夹角应当不大于 $\arcsin(\dfrac{d}{|P_iP_k|})$。

于是在处理所有 $chk(i,j)$ 时，我们顺次扫描 $k>i$，记录它对 $P_iP_j$ 极角的区间限制，然后对这个 $k$ 计算它是否在 $i+1,\ldots,k-1$ 所划定的区间内即可。

时间复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2010;
const double pi=acos(-1.0),eps=1e-8;
struct P {
	double x,y;
}p[MAXN];
int n,dp[MAXN],trans[MAXN][MAXN];
double d,al,ar,bl,br;
double calcslp (P a,P b) {
	return atan2(b.y-a.y,b.x-a.x);
}
double calcdis (P a,P b) {
	return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
pair<double,double> calc (P a,P b) {
	double plragl=calcslp(a,b);
	double delagl=asin(d/calcdis(a,b));
	pair<double,double> res=make_pair(plragl-delagl,plragl+delagl);
	return res;
}
int main () {
	scanf("%d%lf",&n,&d);
	for (int i=1;i<=n;i++) {
		scanf("%lf%lf",&p[i].x,&p[i].y);
		for (int j=i+1;j<=n;j++) {trans[i][j]=1;}
	}
	for (int i=1;i<=n;i++) {
		al=bl=-pi-eps,ar=br=pi+eps;
		for (int j=i+1;j<=n;j++) {
			double tmp=calcslp(p[i],p[j]);
			if ((tmp<al||tmp>ar)&&(tmp<bl||tmp>br)) {trans[i][j]=0;}
			if (calcdis(p[i],p[j])>d) {
				pair<double,double> bd=calc(p[i],p[j]);
				if (bd.first>=-pi-eps&&bd.second<=pi+eps) {
					al=max(al,bd.first),ar=min(ar,bd.second);
					bl=max(bl,bd.first),br=min(br,bd.second);
				} else if (bd.first<-pi-eps) {
					ar=min(ar,bd.second);
					bl=max(bl,bd.first+2*pi);
				} else {
					ar=min(ar,bd.second-2*pi);
					bl=max(bl,bd.first);
				}
			}
		}
	}
	for (int i=n;i>=1;i--) {
		al=bl=-pi-eps,ar=br=pi+eps;
		for (int j=i-1;j>=1;j--) {
			double tmp=calcslp(p[i],p[j]);
			if ((tmp<al||tmp>ar)&&(tmp<bl||tmp>br)) {trans[j][i]=0;}
			if (calcdis(p[i],p[j])>d) {
				pair<double,double> bd=calc(p[i],p[j]);
				if (bd.first>=-pi-eps&&bd.second<=pi+eps) {
					al=max(al,bd.first),ar=min(ar,bd.second);
					bl=max(bl,bd.first),br=min(br,bd.second);
				} else if (bd.first<-pi-eps) {
					ar=min(ar,bd.second);
					bl=max(bl,bd.first+2*pi);
				} else {
					ar=min(ar,bd.second-2*pi);
					bl=max(bl,bd.first);
				}
			}
		}
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1]=1;
	for (int i=2;i<=n;i++) {
		for (int j=1;j<i;j++) {
			if (trans[j][i]) {dp[i]=min(dp[i],dp[j]+1);}
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}

```


---

## 作者：Nelofus (赞：0)

[更好的阅读体验](https://senex-nostalgia.github.io/2023/09/21/P7058-gym100801K-NWRRC2015-Kingdom-Trip/)

[参考资料](https://yhx-12243.github.io/OI-transit/records/lg7058%3Bgym100801K.html)

## 题解

首先 $\mathcal O(n^3)$ 是容易的，直接 $f_i$ 表示前 $i$ 个的最小值，然后暴力就行了。

这个转移一眼就不能优化，主要比较大的问题是在判断一个点能不能转移的时候复杂度是 $\mathcal O(n)$ 的，考虑怎么算出来。

当我们固定右端点 $r$ 的时候，我们希望计算出每个左端点 $l$ 是否是可转移的。

这个东西不太好做，要考虑所有除了 $l$ 以外的点，那我们反过来想，考虑每个 $i$ 对 $l$ 造成什么限制。

分两种情况：

1. $|P_iP_r|\le d$

   这种情况是没有影响的，因为 $\operatorname {dis}(P_i,P_lP_r)\le |P_iP_r|\le d$，所以一定可行。

2. $|P_iP_r|>d$

   先考虑直线的限制，即 $P_l$ 到**直线** $P_iP_r$ 的距离不超过 $d$。

   也就是 $|P_lP_r|\cdot |\sin \angle P_lP_rP_i|\le d$。
   $$
   \begin{aligned}
   |P_lP_r|\cdot |\sin \angle P_lP_rP_i|&\le d\\
   |\sin \angle P_lP_rP_i|&\le \frac{d}{|P_lP_r|}\\
   |\angle P_lP_rP_i|&\le \arcsin(\frac{d}{|P_lP_r|})
   \end{aligned}
   $$
   ![P7058-2.png](https://s2.loli.net/2023/09/21/JaVLtFe8Nw4iQjs.png)

   也就是 $P_l$ 应该落在这个以 $P_i$ 为圆心，$d$ 为半径，用 $P_r$ 与该圆的切线划出的区域内。

   但实际上我们不希望它落到 $P_r$ 的那一侧，所以我们需要判掉这种情况——但这实际上并不需要作特别的处理，$\arcsin$ 的值域是 $[-\frac{\pi}{2},\frac{\pi}{2}]$，所以其必然求出的是绿的一个角，而这种情况下的角度实际上是个钝角，所以是负的。

   满足限制的角度就是所有合法1的角度求交集。

   还有一个问题是会有

   ![P7058-2.png](https://s2.loli.net/2023/09/21/kLFADIPcSbonTsy.png)

   这种情况中的 $P_l$ 出现，它显然不合法，但根据上面的判法它合法了。

   考虑利用对称性，对着每个 $P_l$ 再反向求一遍所有合法的 $P_r$，那么一个 $P_l$ 和 $P_r$ 之间能够转移当且仅当 $P_r$ 对 $P_l$ 合法且 $P_l$ 对 $P_r$ 合法。容易看出，这样我们就能判掉上面的情况。

## 代码

```cpp
#include <bits/stdc++.h>
using i64 = int64_t;
using f64 = double;

constexpr int N = 2010;
const f64 pi = acos(-1), eps = 1e-8;

struct Point {
	f64 x, y;
	Point(){}
	Point(const f64 &x, const f64 &y) : x(x), y(y) {}
} P[N];

using Vector = Point;
inline Vector operator + (const Vector &a, const Vector &b)	{return Vector(a.x + b.x, a.y + b.y);}
inline Vector operator - (const Vector &a, const Vector &b)	{return Vector(a.x - b.x, a.y - b.y);}
inline Vector operator * (const Vector &a, const f64 &x)	{return Vector(a.x * x, a.y * x);}
inline Vector operator / (const Vector &a, const f64 &x)	{return Vector(a.x / x, a.y / x);}
inline Vector Vec(const Point &a, const Point &b) {return b - a;};

inline f64 Dot(const Vector &A, const Vector &B) {return A.x * B.x + A.y * B.y;}
inline f64 Cross(const Vector &a, const Vector &b) {return a.x * b.y - a.y * b.x;}
inline f64 Length(const Vector &V) {return sqrt(Dot(V, V));}
// 重载 atan2
inline f64 atan2(const Point &a) {return atan2(a.y, a.x);}

bool able[N][N];
int f[N];

int n;
f64 d;

template<typename T>
inline void chkmin(T &x, const T &y) {if (x > y)	x = y;}
template<typename T>
inline void chkmax(T &x, const T &y) {if (x < y)	x = y;}

std::pair<f64, f64> seg(Point a, Point b) {
	// 基础是向量 A->B 的极角
	f64 base = atan2(Vec(a, b));
	f64 angel = asin(d / Length(Vec(a, b)));
	return std::make_pair(base - angel, base + angel);
}

inline int dcmp(const f64 &x) {
	if (fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1;
}
// -1 为小于, 0 为等于, 1 为大于
inline int dcmp(const f64 &x, const f64 &y) {return dcmp(x - y);}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	memset(f, 0x3f, sizeof(f));

	std::cin >> n >> d;
	for (int i = 1; i <= n; i++)
		std::cin >> P[i].x >> P[i].y;
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			able[i][j] = true;

	for (int i = 1; i <= n; i++) {
		f64 al = -pi, bl = -pi;
		f64 ar = pi, br = pi;

		for (int j = i + 1; j <= n; j++) {
			f64 t = atan2(Vec(P[i], P[j]));
			if ((dcmp(t, al) < 0 || dcmp(t, ar) > 0) && (dcmp(t, bl) < 0 || dcmp(t, br) > 0))
				able[i][j] = false;

			if (dcmp(Length(Vec(P[i], P[j])), d) <= 0)
				continue;
			const auto &[segl, segr] = seg(P[i], P[j]);

			// 考虑射线 P[i] -> P[j] 的方向
			// 和原来要的区间同向
			if (dcmp(segl, -pi) >= 0 && dcmp(segr, pi) <= 0) {
				chkmax(al, segl), chkmax(bl, segl);
				chkmin(ar, segr), chkmin(br, segr);
			} else if (dcmp(segl, -pi) < 0) {
				chkmin(ar, segr);
				chkmax(bl, segl + 2 * pi);
			} else {
				chkmin(ar, segr - 2 * pi);
				chkmax(bl, segl);
			}
		}
	}

	for (int i = n; i >= 1; i--) {
		f64 al = -pi, bl = -pi;
		f64 ar = pi, br = pi;

		for (int j = i - 1; j >= 1; j--) {
			f64 t = atan2(Vec(P[i], P[j]));
			if ((dcmp(t, al) < 0 || dcmp(t, ar) > 0) && (dcmp(t, bl) < 0 || dcmp(t, br) > 0))
				able[j][i] = false;
			
			if (dcmp(Length(Vec(P[i], P[j])), d) <= 0)
				continue;

			const auto &[segl, segr] = seg(P[i], P[j]);

			// 考虑射线 P[i] -> P[j] 的方向
			// 和原来要的区间同向
			if (dcmp(segl, -pi) >= 0 && dcmp(segr, pi) <= 0) {
				chkmax(al, segl), chkmax(bl, segl);
				chkmin(ar, segr), chkmin(br, segr);
			} else if (dcmp(segl, -pi) < 0) {
				chkmin(ar, segr);
				chkmax(bl, segl + 2 * pi);
			} else {
				chkmin(ar, segr - 2 * pi);
				chkmax(bl, segl);
			}
		}
	}

	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++)
			if (able[j][i]) {
				chkmin(f[i], f[j] + 1);
			}
	}
	std::cout << f[n] << '\n';
	return 0;
}
```



---

