# [ICPC 2015 WF] Tile Cutting

## 题目描述

Youssef 是一名专业贴瓷砖的修墙工，并且擅长用瓷砖贴出马赛克图案（如上图所示）。所有的瓷砖的尺寸长度均为整数，单位为 $cm$。在马赛克图案中，平行四边形是不可或缺的。因此，Youssef 会使用切割机，将矩形的瓷砖进行切割。在切割过程中，Youssef 选择使用网格辅助切割机进行切割（在瓷砖上布上 $cm$ 的网格方便切割）。

切割过程有以下要求：

1.	可以从两个不同端点的连线切割（可以斜着切割）
2.	新平行四边形的四个角必须在矩形瓷砖的最外侧边上
3.	平行四边形的边不能与矩形的任意一条边边重叠

现在给出切割的面积的两个边界值 $a_{lo}$ 和 $a_{hi}$，求出 Youssef 能够最多切割掉的小矩形瓷砖数量。

## 样例 #1

### 输入

```
2
4 4
2 6
```

### 输出

```
4 8
6 20
```

# 题解

## 作者：Elegia (赞：16)

另一篇题解已经指出，答案序列就是
$$
\left(\sum_{n\ge 1} \sigma_0(n) x^n\right)^2
$$

考虑 $\sigma_0(n)$ 是 $ab=n$ 的解数，不妨设 $a\le b$，可以写出
$$
\sum_{n\ge 1}\sigma_0(n)x^n = \sum_{h\ge 1} x^{h^2} \frac{1+x^h}{1-x^h}
$$
由于最低次项为 $h^2$，我们只需要考虑 $h\le \sqrt n$ 的部分，因此我们可以在 $O(n^{3/2})$ 的时间内计算出 $f(x) \cdot \sum_{n\ge 1} \sigma_0(n) x^n$。

综上，我们可以在 $O(n^{3/2})$ 的时间完成预处理。虽然比 FFT 慢，但是它的优点是**短**！

正常缩进的本代码目前在 CF 上是最短的，欢迎大家继续优化码长。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 500000;

int f[N + 5], g[N + 5], h[N + 5];

int main() {
	for (int i = 1; i <= N; ++i)
		for (int j = i; j <= N; j += i)
			++f[j];
	for (int i = 1, t; (t = i * i) <= N; ++i) {
		memcpy(g, f, sizeof(g));
		for (int j = N - t; j >= i; --j) g[j] += g[j - i];
		for (int j = i; j <= N - t; ++j) g[j] += g[j - i];
		for (int j = 0; j <= N - t; ++j) h[j + t] += g[j];
	}
	int Q; cin >> Q;
	while (Q--) {
		int l, r; cin >> l >> r;
		int pos = max_element(h + l, h + r + 1) - h;
		cout << pos << ' ' << h[pos] << '\n';
	}

	return 0;
}
```

---

## 作者：donaldqian (赞：6)

考试题，感谢 [JDScript0117](https://www.luogu.com.cn/user/910593) 提供的解法。

为了方便，我们设 $f(i)$ 表示平行四边形面积为 $i$ 时的答案。这篇 [题解](https://www.luogu.com.cn/article/qlptdn76) 已经证明 $f(n) = \sum\limits_{a\ge 1}d(a)d(n-a)$，这里 $d(n)$ 表示 $n$ 的因子个数，并假设负数的 $d$ 为 $0$。

$$
\begin{align*}
f(n)&=\sum\limits_{a+b=n}d(a)d(b)\\
&=\sum\limits_{a+b=n}\sum\limits_{x|b}d(a)\\
&=\sum\limits_{x\ge 1}\sum\limits_{k\ge 1}d(n-xk)\\
&=\sum\limits_{x=1}^n\sum\limits_{i=1}^{n-1}[i\bmod x=n\bmod x]\times d(i)\\
&=\sum\limits_{x=1}^{B-1}\sum\limits_{i=1}^{n-1}[i\bmod x=n\bmod x]\times d(i)+\sum\limits_{x=B}^n\sum\limits_{k\ge 1}^{\lfloor\frac{n}{x}\rfloor}d(n-xk)
\end{align*}
$$

其中 $B$ 是某个值。我们发现前面一坨容易 $O(nB)$ 处理，考虑后面一坨怎么做。

定义 $g(i,x)=\sum\limits_{j\ge 0}d(i-xj)=g(i-x,x)+d(i)$，其中第二维值域为 $O(\frac{n}{B})$，可以 $O(\frac{n^2}{B})$ 处理。

那么我们有 $\sum\limits_{x=B}^n\sum\limits_{k= 1}^{\lfloor\frac{n}{x}\rfloor}d(n-xk)=\sum\limits_{k=1}^{\lfloor\frac{n}{B}\rfloor}g(n-Bk,k)$，故也可以 $O(\frac{n^2}{B})$ 计算，显然 $B=\sqrt n$ 时有最优复杂度 $O(n^{\frac{3}{2}})$。

然后每次询问可以用 st 表做到 $O(1)$，最后复杂度 $O(n^{\frac{3}{2}}+n\log n+T)$。（不会 st 表的小朋友可以用线段树哦！）

代码。
```cpp
#define R 500000

const int maxn = 500010, B = 710;
int f[B], s[maxn], d[maxn], a[maxn];

bool operator > (pii x, pii y) { return x.first == y.first ? x.second < y.second : x.first > y.first; }
pii max_ (pii x, pii y) { return x > y ? x : y; }
pii st[maxn][19];

signed main () {
	for (int i = 1; i <= R; i++) {
		for (int j = i; j <= R; j += i) d[j]++;
	}
	for (int j = 1; j < B; j++) {
		int lst = 0;
		for (int i = 0; i < j; i++) f[i] = 0;
		for (int i = 1; i <= R; i++) {
			if (++lst == j) lst = 0;
			if (j <= i) a[i] += f[lst];
			f[lst] += d[i];
		}
	}
	for (int j = 1; j <= B; j++) {
		for (int i = 1; i <= R; i++) {
			if (j * B <= i) a[i] += s[i - j * B];
			s[i] = (i < j ? 0 : s[i - j]) + d[i];
		}
	}
	for (int i = 1; i <= R; i++) st[i][0] = {a[i], i};
	for (int j = 1; j < 19; j++) {
		for (int i = 1; i <= R; i++) if (i + (1 << j) - 1 <= R) {
			st[i][j] = max_ (st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
	int t, l, r, len; read (t);
	while (t--) {
		read (l), read (r), len = log2 (r - l + 1);
		pii ans = max_ (st[l][len], st[r - (1 << len) + 1][len]);
		printf("%d %d\n", ans.second, ans.first);
	}
	return 0;
}
```

---

## 作者：Lyccrius (赞：2)

考虑这样一个平行四边形：

![](https://s4.ax1x.com/2021/12/22/T1PKdP.png)

其面积为 $(a + b)(c + d) - ac - bd = ad + bc$。

记 $g(p)$ 为满足条件且面积为 $p$ 的数量，那么 $g(p) = \sum_{a, b, c, d} [ad + bc = p]$。

记 $h(p) = \sum_{a, b} [ab = p]$，则 $g(p) = \sum_{i = 0}^p h(i) h(p - i)$。

易证 $h(p)$ 为 $p$ 的因子个数，可以 $\mathcal O(a \log a)$ 筛出。

这是一个多项式乘法的形式，FFT 后用 RMQ 求解即可。

```cpp
#include <iostream>
#include <complex>
#include <cmath>

typedef double dbl;
typedef std::complex<dbl> cmd;

const int maxN = 500;
const int maxA = 500000;
const int logA = 20;
const int maxM = 1 << logA;
const dbl pi = acos(-1.0);

int n;
int alo, ahi;
int c[maxM + 10];
cmd f[maxM + 10];

void FFT(cmd *a, int n, int k) {
	if (n == 1) return;
	int mid = n / 2;
	cmd al[mid];
	cmd ar[mid];
	for (int i = 0; i < mid; i++) {
		al[i] = a[2 * i];
		ar[i] = a[2 * i + 1];
	}
	FFT(al, mid, k);
	FFT(ar, mid, k);
	cmd w1(cos(2.0 * pi / n), k * sin(2.0 * pi / n));
	cmd wk(1.0, 0.0);
	for (int i = 0; i < mid; i++, wk *= w1) {
		a[i] = al[i] + wk * ar[i];
		a[i + mid] = al[i] - wk * ar[i];
	}
	return;
}

struct SegmentTree {
	struct Node {
		int pos;
		int val;
	} node[4 * maxM + 10];

	Node Merge(Node a, Node b) {
		if (a.val >= b.val) return a;
		return b;
	}

	void PushUp(int u) {
		node[u] = Merge(node[2 * u], node[2 * u + 1]);
		return;
	}

	void Modify(int u, int l, int r, int pos, int val) {
		if (l == r) {
			node[u].pos = l;
			node[u].val = val;
			return;
		}
		int mid = (l + r) / 2;
		if (pos <= mid) Modify(2 * u, l, mid, pos, val);
		if (pos >= mid + 1) Modify(2 * u + 1, mid + 1, r, pos, val);
		PushUp(u);
		return;
	}

	Node Query(int u, int l, int r, int s, int t) {
		if (s <= l && r <= t) return node[u];
		int mid = (l + r) / 2;
		if (t <= mid) return Query(2 * u, l, mid, s, t);
		if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
		return Merge(Query(2 * u, l, mid, s, t), Query(2 * u + 1, mid + 1, r, s, t));
	}
} SGT;

int main() {
	for (int i = 1; i <= maxA; i++) for (int j = i; j <= maxA; j += i) c[j]++;
    for (int i = 1; i <= maxA; i++) f[i].real(c[i]);
	FFT(f, maxM, 1);
	for (int i = 0; i < maxM; i++) f[i] = f[i] * f[i];
	FFT(f, maxM, -1);
	for (int i = 1; i < maxM; i++) SGT.Modify(1, 1, maxM, i, (int) (f[i].real() / maxM + 0.5));//, printf("*%d: %d\n", i, (int) (f[i].real() / maxM + 0.5));
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> alo >> ahi;
		SegmentTree::Node ans = SGT.Query(1, 1, maxM, alo, ahi);
		std::cout << ans.pos << ' ' << ans.val << '\n';
	}
	return 0;
}
```

---

## 作者：ArrTue (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6913)

[双倍经验传送门](https://www.luogu.com.cn/problem/UVA1718)

#### 前置知识：

多项式乘法。

#### 题意：

- 在网格图中，记 $g(p)$ 为满足下列条件的格点平行四边形数量：
	1. 有两个顶点分别位于 x、y 轴正半轴上，其余部分处于第一象限；
	2. 没有边竖直或水平；
	3. 面积为 $p$。
- 有 $n$ 个询问，每个询问给出 $l,r$，问满足 $l\le p\le r$ 并使 $g(p)$ 最大的整数 $p$ 以及对应的 $g(p)$。

- $n\le200$，$1\le l\le r\le5\times10^5$。

#### 分析：

注意到 $l,r$ 范围，提示我们可以先预处理出 $g$。

不妨考虑如下的一个平行四边形：

![](https://s4.ax1x.com/2021/12/22/T1PKdP.png)

其面积为 $(a+b)(c+d)-ac-bd=ad+bc$。而只要 $a,b,c,d$ 其中至少一者不同，就是不同的平行四边形。因此 $g(p)=\sum\limits_{a,b,c,d}[ad+bc=p]$。

注意到 $ad,bc$ 等价，可假设 $h(x)=\sum\limits_{a,b}[ab=x]$，则 $g(p)=\sum\limits_i\sum\limits_{a,d}[ad=i]\sum\limits_{b,c}[bc=p-i]=\sum\limits_{i=0}^ph(i)h(p-i)$。

观察到该式与多项式乘法形式类似，不妨记 $f$ 为一个多项式，第 $i$ 项为 $h(i)$，则 $f^2$ 的第 $i$ 项即为 $g(i)$。

易证 $h(x)$ 就是 $x$ 的因子个数，可以 $\mathcal O(r\log r)$ 筛出。

而 $f$ 为一个 $r$ 项的多项式，可以用 $\mathcal O(r\log r)$ 求出 $f^2$，每次查询等价于查询 $f^2$ 的连续若干项的最小值，可以 $\mathcal O(r\log r)$ 预处理 ST 表，$\mathcal O(1)$ 询问。

---

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i=l, _=r; i<=_; ++i)
using namespace std;
typedef long long ll;
inline int read() {
	int res=0; bool k=1; char ch;
	while(!isdigit(ch=getchar())) k=ch^45;
	do res=res*10+(ch&15); while(isdigit(ch=getchar()));
	return k? res: -res;
}
#define double long double
const double pi=acos(-1);
const int mN=1<<20|9, N=1<<20, mM=5e5+9, M=5e5, mD=20;  //N 为多项式项数，M 为 r 上限
int n, st[mM][mD], lg[mM], ans[mM];

struct Cpl {
	double a, b;
	Cpl (double a=0, double b=0): a(a), b(b) {}
} omega[mN], f[mN];
Cpl operator + (Cpl x, Cpl y) {return Cpl(x.a+y.a, x.b+y.b);}
Cpl operator - (Cpl x, Cpl y) {return Cpl(x.a-y.a, x.b-y.b);}
Cpl operator * (Cpl x, Cpl y) {return Cpl(x.a*y.a-x.b*y.b, x.a*y.b+x.b*y.a);}

void FFT(Cpl *a, int n, bool k) {
	if(n==1) return;
	static Cpl tmp[mN];
	Cpl *b=a+(n>>1), x, y;
	rep(i, 0, n-1) tmp[i]=a[i];
	rep(i, 0, n-1>>1) a[i]=tmp[i<<1], b[i]=tmp[i<<1|1];
	FFT(a, n>>1, k), FFT(b, n>>1, k);
	rep(i, 0, n-1>>1) x=a[i], y=omega[k? N-N/n*i: N/n*i]*b[i], a[i]=x+y, b[i]=x-y;
}
inline int max_num(int a, int b) {return ans[a]==ans[b] && a<b || ans[a]>ans[b]? a: b;}

int main() {
	rep(i, 0, N) omega[i]=Cpl(cos(2*pi/N*i), sin(2*pi/N*i));
	rep(i, 2, M) lg[i]=lg[i>>1]+1;
	rep(i, 1, M) rep(j, 1, M/i) ++f[i*j].a;
	FFT(f, N, 0);
	rep(i, 0, N-1) f[i]=f[i]*f[i];
	FFT(f, N, 1), ans[0]=-1;
	rep(i, 1, M) ans[st[i][0]=i]=(int) (f[i].a/N+0.3);
	rep(d, 1, 19) rep(i, 0, M-(1<<d)+1) st[i][d]=max_num(st[i][d-1], st[i+(1<<d-1)][d-1]);
	for(int n=read(); n--; ) {
		int x=read(), y=read(), d;
		if(x>y) d=x, x=y, y=d;
		d=lg[y-x+1], x=max_num(st[x][d], st[y-(1<<d)+1][d]);
		printf("%d %d\n", x, ans[x]);
	}
	return 0;
}
```

---

