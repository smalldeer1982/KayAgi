# [NOISG 2021 Qualification] Departure

## 题目描述

有一个城市，城市里有 $N$ 条路线，每条路线上，在每天午夜会有一辆巴士从起点出发，第二天午夜到达终点。第 $i$ 辆公交车的起点为 $S_i$，终点为 $E_i$。人们可以在巴士路线上的的**任何地方**上车、下车或者换乘。

体育馆是这个城市的中心，坐标为 $0$。在体育馆西边 $x$ 千米的点，坐标为 $-x$，在体育馆东边 $x$ 千米的点，坐标为 $x$。

现在有 $M$ 个人需要从体育馆回家，你需要求出每一个人回家的最短时间。

## 说明/提示

#### 数据范围

**本题采用捆绑测试。**

以下定义 $\operatorname{sign}(x) = \begin{cases}
1 &\text{if } x > 0 \\
0 &\text{if } x = 0 \\
-1 &\text{if } x < 0 \\
\end{cases}$。

Subtask0 为样例。

Subtask1（10 pts）$N \leq 10^4$，$M \leq 10^3$，$\operatorname{sign}(S_i)\neq\operatorname{sign}(E_i)$。

Subtask2（14 pts）$N \leq 100$，$M \leq 10^3$。

Subtask3（12 pts）$N \leq 10^3$，$M \leq 10^5$，保证最后答案的值均不大于 $10^3$，保证任意坐标在不超过 $10^2$ 条线路上。

Subtask4（8 pts）$M \leq 10^3$，保证任意坐标在不超过 $10^4$ 条线路上。

Subtask5（15 pts）$M \leq 10^4$，保证最后答案的值均不大于 $10^2$。

Subtask6（13 pts）$\operatorname{sign}(S_i)\neq\operatorname{sign}(E_i)$。

Subtask7（28 pts）无特殊限制。

数据保证 $1 \leq N,M \leq 10^6$，$-10^6 \leq S_i,E_i,P_j \leq 10^6$，$S_i \neq E_i$，$P_j \neq 0$。

## 样例 #1

### 输入

```
5 8
0 5
3 11
1 -8
4 10
1 -3
1 2 5 6 8 -3 -7 11```

### 输出

```
1 5
2 5
1 1
4 3
13 8
4 9
8 9
2 1```

## 样例 #2

### 输入

```
3 2
-1 4
-2 5
0 -5
4 -4```

### 输出

```
6 7
4 5```

## 样例 #3

### 输入

```
5 3
0 2
2 4
4 6
6 8
8 10
9 10 10```

### 输出

```
9 2
5 1
5 1```

# 题解

## 作者：steambird (赞：2)

非常好思维题，$n \le 10^6$，使我的李超线段树只得部分分。

## 思路

### Step 1. 观察性质

首先可以注意到，一个人不会坐反方向的车。这是因为坐回头车再登上正确方向的车完全可以等效于在路边等正确的车来。因此，我们可以向一个方向转移所需信息。

下面讨论从 $0$ 到正方向的情况。向负方向的情况是完全一样的（因为我们已经证明不会坐反方向的车）。

### Step 2. 考虑朴素思路

于是我们就可以快乐地写出关于每辆巴士 $(s,e)$ 的 dp 方程（设 $S$ 表示所有巴士组成的集合，$dp_i$ 表示到 $i$ 位置所需最短时间）：

$$ dp_0=0 $$

$$ dp_i = \min_{j \in \{x \in S \mid x_s \le i \le x_e \}}(\lceil dp_{j_s} \rceil + {{i - j_s} \over {j_e - j_s}}) $$

然后将 $S$ 按 $s$ 从小到大排序即可转移（靠前的 $dp_j$ 此时一定是确定的）。

这一 dp 式子可以看作从每个 $x_s$ 出发插入一个等差数列（或者线段 $y=x_s+{x \over {x_e - x_s}}, x \in [x_s,x_e]$），这可以用李超线段树维护，时间复杂度 $O(n  \log^2 n)$。

是不是很合理？时间复杂度刚好足够卡过 4s。然而，[你再怎么卡都只有 36 分](https://www.luogu.com.cn/record/178137002)。因为本题要维护分数，设答案最大值为 $W$，实际复杂度为 $O(n \log^2 (nW))$，同时线段树的常数也不能忽略。

### Step 3. 转换思维，考虑优化

注意到我们实际上在求凸包。当所有的线段具有相同的定义域时，我们事实上有更快的算法（按斜率排序，再用栈维护）。但是，根据我们上面的定义，每条线段就是每辆巴士经过的路程，有定义域 $[s,e]$。

考虑每个人坐巴士的行为。如果一个人在某个位置不能通过坐一辆巴士到达目的地，那么这个人的最优策略是坐到最远处（对于更近的位置，完全可以少等一天，因此没必要做得更近）。

因此，我们可以维护第 $i$ 天通过巴士能到达的最远位置 $r_i$。在第 $i$ 天可坐的所有车即为 $s \le r_{i-1}$ 且并未被用于更新答案的车（这些车已经被算为之前几天的答案）。

接下来我们考虑一天内的情况。考虑如何让“线段”的定义域一致。我们发现，如果我们把之前定义的值反一下（$dp_j$（$0 \le j < 1$） 表示 $i+j$ 天时最远能到哪里），则每条线段可以表示为 $y=s+(e-s)x$。

### Step 4. 考虑实现

考虑到一些人~~像我一样~~没学过单调栈维护凸包，因此在此略做讲解。单调栈维护凸包的方法为：

- 首先将所有线段按斜率排序。

- 插入线段 $y=kx+b$ 时，计算该线段与栈顶线段（定义域 $[L,R]$）的交点横坐标 $x$。如果 $x < L$，则弹栈，否则将栈顶划分为两部分，$[L, x]$ 属于原栈顶，$[x, 1]$ 属于新线段。

- 将询问从小到大排序，设当前**栈底**定义域 $[L,R]$，询问 $x$ 时移除栈底直到 $x \ge L$（在这里我们要找最小的 $x$，但给定的是 $y$，所以是移除栈底直到 $f(R) \ge y$，**注意等号要取到**）。

注意，上文提到，用这个方法的条件是所有定义域一致。

时间复杂度 $O(n \log n)$，瓶颈在排序。

## 代码

```c++
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

inline void train() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}

inline int maxi(int a, int b) {
	return a > b ? a : b;
}

inline int mini(int a, int b) {
	return a < b ? a : b;
}

inline long long absx(long long x) {
	return x < 0 ? (-x) : x;
}

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	else return gcd(b, a%b);
}

inline long long lcm(long long a, long long b) {
	return a * b / gcd(absx(a), absx(b));
}

struct Fraction {
	long long a, b;
	Fraction() : a(0), b(1) {

	}
	Fraction(long long a) : a(a), b(1) {

	}
	Fraction(long long a, long long b) : a(a), b(b) {

	}
	Fraction Simplify() {
		if (b < 0) {
			b = -b; a = -a;
		}
		long long g = gcd(absx(a), absx(b));
		return Fraction(a / g, b / g);
	}
	long long Floor() const {
		assert(b > 0);
		return a / b;
	}
};

Fraction operator * (const Fraction &a, const Fraction &b) {
	Fraction result(a.a * b.a, a.b * b.b);
	return result.Simplify();
}

Fraction operator / (const Fraction &a, const Fraction &b) {
	return (a * Fraction(b.b, b.a)).Simplify();
}

Fraction operator + (Fraction a, Fraction b) {
	long long g = gcd(absx(a.b), absx(b.b));
	a.a *= b.b / g;
	b.a *= a.b / g;
	return Fraction(a.a + b.a, a.b*b.b / g).Simplify();
}

Fraction operator - (Fraction a, Fraction b) {
	long long g = gcd(absx(a.b), absx(b.b));
	a.a *= b.b / g;
	b.a *= a.b / g;
	return Fraction(a.a - b.a, a.b*b.b / g).Simplify();
}

bool operator < (Fraction a, Fraction b) {
	long long g = gcd(absx(a.b), absx(b.b));
	a.a *= b.b / g;
	b.a *= a.b / g;
	return a.a < b.a;
}

bool operator <= (Fraction a, Fraction b) {
	long long g = gcd(absx(a.b), absx(b.b));
	a.a *= b.b / g;
	b.a *= a.b / g;
	return a.a <= b.a;
}

constexpr int N = 1e6 + 4;
struct car {
	int s, e;
	car() {

	}
	car(int s, int e) : s(s), e(e) {

	}
};

bool cmp(const car &a, const car &b) {
	return a.s < b.s;
}

bool cmp2(const car &a, const car &b) {
	return a.s > b.s;
}

bool operator > (const car &a, const car &b) {
	int la = absx(a.e - a.s), ra = absx(b.e - b.s);
	return la > ra;
}

priority_queue<car, vector<car>, greater<car> > pc;

struct line {
	int k, b;
	Fraction l, r;
	line() {

	}
	Fraction infer(int dis) const {
		return Fraction(dis - b, k);
	}
	Fraction ry() const {
		return k * r + b;
	}
};

Fraction interact_at(const line &a, const line &b) {
	Fraction k_a = a.k, b_a = a.b;
	Fraction k_b = b.k, b_b = b.b;
	if (a.k == b.k) return Fraction(1e9);
	return (b_b - b_a) / (k_a - k_b);
}

list<line> stb;

inline line stb_put(line gen) {
	static Fraction tit;
	while ((!stb.empty()) && ((tit = interact_at(stb.back(), gen)) <= stb.back().l || (stb.back().k == gen.k && stb.back().b < gen.b))) {
		stb.pop_back();
	}
	Fraction lbound = 0;
	gen.r = 1;
	if ((!stb.empty())) {
		if (tit < 0) {
			tit = 0;
		}
		if (tit < stb.back().r) {
			stb.back().r = tit;
		}
		lbound = stb.back().r;
	}
	gen.l = lbound;
	stb.push_back(gen);
	return gen;
}

vector<car> fwd, bck, query;
Fraction answer[N];
int n, m;

int main() {

	train();

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int s, e;
		cin >> s >> e;
		if (s < e) fwd.push_back(car(s, e));
		else bck.push_back(car(s, e));
	}
	sort(fwd.begin(), fwd.end(), cmp);
	sort(bck.begin(), bck.end(), cmp2);
	for (int i = 1; i <= m; i++) {
		int q;
		cin >> q;
		query.push_back(car(q, i));
	}
	sort(query.begin(), query.end(), cmp);
	auto positive = lower_bound(query.begin(), query.end(), car(0, -1), cmp);
	auto negative = positive;
	auto fwd_pointer = fwd.begin(), bck_pointer = bck.begin();
	if (negative != query.begin()) {
		int boarding_bnd = 0, reaching_bnd = 0, day = 0;
		bool done = false;
		do {
			for (; bck_pointer != bck.end() && bck_pointer->s >= boarding_bnd; bck_pointer++) {
				pc.push(*bck_pointer);
				reaching_bnd = mini(reaching_bnd, bck_pointer->e);
			}
			stb.clear();
			while (!pc.empty()) {
				auto pt = pc.top();
				pc.pop();
				line gen;
				gen.k = absx(pt.e - pt.s);
				gen.b = -pt.s;
				stb_put(gen);
			}
			while (negative->s >= reaching_bnd) {
				while ((stb.size() > 1) && stb.front().ry() < (-negative->s)) {	
					stb.pop_front();
				}
				assert(!stb.empty());
				answer[negative->e] = day + stb.front().infer(-negative->s);
				if (negative == query.begin()) {
					done = true;
					break;
				}
				negative--;
			}
			boarding_bnd = reaching_bnd;
			if (done) break;
			day++;
		} while (!done);
	}
	int boarding_bnd = 0, reaching_bnd = 0, day = 0;
	for (; positive != query.end(); day++) {
		for (; fwd_pointer != fwd.end() && fwd_pointer->s <= boarding_bnd; fwd_pointer++) {
			pc.push(*fwd_pointer);
			reaching_bnd = maxi(reaching_bnd, fwd_pointer->e);
		}
		stb.clear();
		while (!pc.empty()) {
			auto pt = pc.top();
			pc.pop();
			line gen;
			gen.k = absx(pt.e - pt.s);
			gen.b = pt.s;
			stb_put(gen);
		}
		for (; positive != query.end() && positive->s <= reaching_bnd; positive++) {
			while ((stb.size() > 1) && stb.front().ry() < (positive->s)) {
				stb.pop_front();
			}
			assert(!stb.empty());
			answer[positive->e] = day + stb.front().infer(positive->s);
		}
		boarding_bnd = reaching_bnd;
	}
	for (int i = 1; i <= m; i++) {
		cout << answer[i].a << ' ' << answer[i].b << '\n';
	}

	cout << flush;

	return 0;
}

```

---

