# [湖南集训] Crazy Rabbit

## 题目描述

兔子们决定在自己的城堡里安排一些士兵进行防守。

给出 $n$ 个点的坐标，和城堡里一个圆心在原点的圆形的障碍，兔子们希望从中选出 $k$ 个兔子，使得它们两两**所在的直线**都不与圆相交。

兔子们希望知道最多能选出多少兔子。

## 说明/提示

#### 样例 1 解释

 ![](https://cdn.luogu.com.cn/upload/pic/6853.png) 

选择第 $1, 2, 6, 4$ 只兔子即可。

---

#### 数据规模与约定

- 对于 $10\%$ 的数据，保证 $1\leq n\leq 20$。
- 对于 $30\%$ 的数据，保证 $1\leq n\leq 100$。
- 对于 $100\%$ 的数据，保证 $1\leq n\leq 2000$，$1\leq r,x_i,y_i \leq 5000$。

## 样例 #1

### 输入

```
6 3
0 6
-7 -4
-3 -2
7 -5
-2 3
8 -3```

### 输出

```
4```

# 题解

## 作者：Maniac丶坚果 (赞：9)

【10分做法】

暴力枚举两个点判断他们是否会与圆相交。

然后转化为一个最大独立集的问题。很遗憾这一步的复杂度是$O(2^n)$的。

【30分做法/100分做法】

考虑能不能先对每个点做点文章。

我们首先处理出每个兔子与圆的两条切线。可以看做是他们覆盖了圆上的一个区间。

这一步不难，如果实在不会请看图（需要用到atan2函数）![](https://cdn.luogu.com.cn/upload/pic/14007.png)
（补上图）
$cos\alpha = r / L$

$cos\theta = atan2(y,x)$

仔细观察下图。

![](https://cdn.luogu.com.cn/upload/pic/14008.png)

可以发现，如果两个点与圆相交，那么他们的切线所处理而来的区间是相离的（从左到右从上到下的第1和第3个点
当然，如果是包含的，也是一个道理：可以看做是一个点关于圆心做了一个对称。
反之，如果两个点连线不与圆相交，则区间一定是相交但不包含的。

于是可以用到类似于tc559 div11000的思想，把圆拉成一条直线并对过拆分点的所有区间取个反。这样就变成了找尽可能多的线段并且使得他们彼此相交但不包含了。

此时，可以注意到由于选择的东西每两个线段都是要交的，所以科学表述一下，就是对于选择的区间对（a1,b1),(a2,b2)... (ak,bk)，一定会满足这样的性质：

 对于所有的$1 <=i <= j<=k$, 有$a_i.x <= a_j.x ,a_i.y <=a_j.y$
也就是说，第2,3...k个区间的左端点都是要在第1个区间的右端点左侧的。

对区间按左端点排序后，枚举第一个区间并运用上面的性质处理出可能合法的区间，然后拿这些区间右端点做最长上升子序列即可。这个LIS的复杂度决定你的总复杂度是大约$n^2logn$的还是$n^3$的（所以总的来说我想不太会有人30分吧）。

代码：
```
#include <bits/stdc++.h>
#define MP make_pair
#define FI first
#define SE second

using namespace std;
const int maxn = 2005;
const double pi = acos(-1.0);
int n,R;
inline int read()
{
	int x = 0, f = 1;
	char ch = 0;
	for (;!isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (;isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
	return x * f;
}
struct Point
{
	double x,y;	
	Point() {}
	Point(double _x, double _y) {x = _x, y = _y;}
	Point operator + (const Point &a) const{ return Point(x + a.x,y + a.y);}
	Point operator += (const Point &a) {return *this = *this + a;}
	Point operator - (const Point &a) const{return Point (x - a.x, y - a.y);}
	Point operator -= (const Point &a) {return *this = *this - a;}
	double operator ^ (const Point &a) const{return x * a.y - y * a.x;}
	double cd() {return sqrt(x * x + y * y);}
}a[maxn];
pair<double,double> A[maxn];
//atan2函数表示的是从X轴逆时针旋转的角度 ，（可以是负值，返回弧度）
//需要角度时需要乘180 / pi 
double b[maxn],c[maxn];
inline int check(int x)
{
	if (x == 0) return 0;
	int len = 0; c[++len] = b[1];
	for (int i =2 ; i <= x; ++i)
	{
		if (b[i] > c[len]) {c[++len] = b[i]; continue;}
		int l = upper_bound(c + 1, c + len + 1,b[i]) - c;
		c[l] = b[i];
	}
	return len;
 } 
int main()
{
	n = read(), R = read();

	for (int i = 1; i <= n; ++i) 
	{
		int x = read(),y = read(); 
		a[i] = Point(x * 1.0,y* 1.0);
		double k = a[i].cd(), angle = atan2(a[i].y,a[i].x),Cos = acos(R / k);
		double L = angle - Cos, R = angle + Cos;
		while (L <= -pi) L += 2.0 * pi; while (R > pi) R -= 2.0 * pi;
		if (L > R) swap(L,R);
		A[i] = MP(L,R);
	}
	sort(A + 1, A + n + 1);
	int ans = -1;
	for (int i = 1,len; i <= n; ++i)
	{
		len = 0;
		for (int j = i + 1; j <= n; ++j)
		if (A[j].FI <= A[i].SE && A[j].SE > A[i].SE)
		b[++len] = A[j].SE;
		ans = max(ans,check(len));
	}
	printf("%d\n",ans + 1);
}
```

---

## 作者：Hanx16Kira (赞：0)

# [湖南集训] Crazy Rabbit

[Luogu P3897](https://www.luogu.com.cn/problem/P3897)

## Solution

考虑对于每个点作出对圆的两条切线，那么每一个点都可以对应成圆上的一个区间。具体的区间可以使用 `atan2` 和 `acos` 计算出来。

考虑这一个转化有什么作用。观察发现，如果两个点可以同时选，那么这两个点对应的区间一定是相交且不是包含关系。容易证明这是充要条件。

那么问题转化成为了选出尽可能多的区间，使得所有区间两两相交且不包含。观察数据范围发现可以枚举一个起点区间，然后剩下的计算只要能在 $\mathcal O(n\log n)$ 内完成都是可行的。

考虑枚举起点区间，然后将所有左端点在起点区间内，右端点不在起点区间内的区间取出。将这些区间按照左端点排序，那么因为不能存在包含关系，那么此时能选择的区间的右端点应该是递增的。也就是选定了起点区间并将其他区间按照上述规则排序后只需要求右端点的 LIS 即可算出答案。那么 $\mathcal O(n^2\log n)$ 的做法显然。

由于原问题的区间是在一个圆上的，因此需要确定一个分割点。考虑跨过分割点的区间如何处理。会发现如果将这个区间变成其在圆上的补集不会导致答案变化。

代码上细节有点多，需要仔细实现。

```cpp
// Cirno is not baka!
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define Rof(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define Debug(...) { \
    fprintf(stderr, "Function{%s},line[%d]:\t", __FUNCTION__, __LINE__); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
}
#define FILE(filename) { \
    freopen(#filename ".in", "r", stdin); \
    freopen(#filename ".out", "w", stdout); \
}
#define All(x) x.begin(), x.end()
#define rAll(x) x.rbegin(), x.rend()
#define pii pair<int, int>
#define fi first
#define se second
#define i64 long long
#define mkp make_pair
// #define int long long
using namespace std;

const int _N = 1e6 + 5, mod = 1e9 + 7;
template<typename T> void Max(T &x, T y) {x = max(x, y);}
template<typename T> void Min(T &x, T y) {x = min(x, y);}
template<typename T1, typename T2>
void Addmod(T1 &x, T2 y) {x += y; x >= mod ? x -= mod : x;}
template<typename T1, typename T2>
T1 Add(T1 x, T2 y) {x += y; return x >= mod ? x - mod : x;}

namespace BakaCirno {
    const double PI = acos(-1), inf = 1e18;
    int N, radiu;
    struct Vec2 {
        int x, y;
        Vec2(int x = 0, int y = 0) : x(x), y(y) {}
        double operator() () {return sqrt(1. * x * x + 1. * y * y);}
    } P[_N];
    vector<pair<double, double>> vec;
    void Solve() {
        cin >> N >> radiu;
        For(i, 1, N) {
            cin >> P[i].x >> P[i].y;
            double mid = atan2(P[i].y, P[i].x);
            double angle = acos(radiu / P[i]());
            double L = mid - angle, R = mid + angle;
            auto Mod = [](double &angle) {
                while (angle < 0) angle += 2 * PI;
                while (angle >= 2 * PI) angle -= 2 * PI;
            };
            Mod(L), Mod(R);
            if (L > R) swap(L, R);
            vec.emplace_back(L, R);
            assert(L >= 0 && L <= 2 * PI);
            assert(R >= 0 && R <= 2 * PI);
        }
        sort(vec.begin(), vec.end());
        auto Calc = [](const vector<double> &A)->int {
            static double f[_N]; int len = 0;
            For (i, 0, A.size() - 1) {
                *upper_bound(f + 1, f + len + 1, A[i]) = A[i];
                if (f[len + 1]) ++len;
            }
            For(i, 0, len) f[i] = inf;
            return len;
        };
        int ans = 0;
        For(i, 0, N - 1) {
            vector<double> cur;
            cur.emplace_back(vec[i].se);
            For(j, i + 1, N - 1)
                if (vec[j].fi <= vec[i].se && vec[j].se >= vec[i].se)
                    cur.push_back(vec[j].se);
            ans = max(ans, Calc(cur));
        }
        cout << ans << '\n';
    }
}

signed main() {
    // FILE(test);
    cin.tie(0)->sync_with_stdio(0); int T = 1;
    // cin >> T;
    while (T--) BakaCirno::Solve();
}
```

---

