# [JOI Open 2023] 细胞自动机 / Cell Automaton

## 题目背景

**译自 [JOI Open 2023](https://contests.ioi-jp.org/open-2023/index.html) T2 「[セルオートマトン](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2023/cell/2023-open-cell-statement.pdf) / [Cell Automaton](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2023/cell/2023-open-cell-statement-en.pdf)」**

## 题目描述

我们有一个充分大的二维网格，网格由从上到下和从左到右的正方形单元格密铺而成。

有一个单元格是坐标原点。令 $(x,y)$ 表示表示从原点向右移动 $x$ 个单元格，再向上移动 $y$ 个单元格所到达的单元格。这里，向左移动 $a$ 个单元格意味着向右移动 $-a$ 个单元格。类似地，向下移动 $a$ 个单元格意味着向上移动 $-a$ 个单元格。

在时刻 $0$，单元格 $(X_1,Y_1),(X_2,Y_2),\ldots,(X_N,Y_N)$ 是黑色的，其余单元格是白色的。

对于 $t=0,1,2,\ldots$，根据单元格在 $t$ 时刻的颜色，单元格在 $t+1$ 时刻的颜色按如下方法确定：

- 如果在时刻 $t$ 时单元格是黑色，那么在时刻 $t+1$ 这个单元格变为灰色。
- 如果在时刻 $t$ 时单元格是灰色，那么在时刻 $t+1$ 这个单元格变为白色。
- 如果在时刻 $t$ 时单元格是白色，并且与其相邻的四个单元格（即，与其共边的四个单元格）中至少有一个在时刻 $t$ 是黑色的，那么在时刻 $t+1$ 这个单元格变为黑色。否则，它将在时刻 $t+1$ 保持白色。

你有 $Q$ 次查询。对于第 $j$ 个查询，你应该回答在时刻 $T_j$ 时有多少黑色单元格。

给定在时刻 $0$ 时的单元格颜色信息和查询，写一个程序回答询问。

## 说明/提示

**【样例解释 #1】**

下图展示了在时刻 $0$ 时的单元格情况。因为有 $2$ 个黑色单元格，所以第一个询问的回答是 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6mmzh2tq.png)

下图展示了在时刻 $1$ 时的单元格情况。因为有 $8$ 个黑色单元格，所以第二个询问的回答是 $8$。

![](https://cdn.luogu.com.cn/upload/image_hosting/s5gw87z0.png)

下图展示了在时刻 $2$ 时的单元格情况。因为有 $12$ 个黑色单元格，所以第三个询问的回答是 $12$。

![](https://cdn.luogu.com.cn/upload/image_hosting/2uavkaeg.png)

这组样例满足子任务 $1,2,6,7$ 的限制。

**【样例解释 #2】**

这组样例满足子任务 $1,2,4,6,7$ 的限制。

**【样例解释 #3】**

这组样例满足子任务 $1,2,6,7$ 的限制。

**【数据范围】**

对于所有数据，满足：

- $1\le N\le 10^5$
- $1\le Q\le 5\times 10^5$
- $|X_i|,|Y_i|\le 10^9$
- $(X_i,Y_i)\neq (X_j,Y_j)\ (1\le i < j\le N)$
- $0\le T_j\le 10^9$
- $T_j<T_{j+1}$

详细子任务附加限制及分值如下表所示。

| 子任务 |               附加限制                | 分值 |
| :----: | :-----------------------------------: | :--: |
|  $1$   |     $\lvert X_i\rvert ,\lvert Y_i\rvert \le 50,T_j\le 50$     | $4$  |
|  $2$   | $\lvert X_i\rvert ,\lvert Y_i\rvert \le 1\ 000,T_j\le 1\ 000$ | $12$ |
|  $3$   |             $X_i=Y_i,Q=1$             | $8$  |
|  $4$   |               $X_i=Y_i$               | $8$  |
|  $5$   |           $N\le 2\ 000,Q=1$           | $17$ |
|  $6$   |             $N\le 2\ 000$             | $25$ |
|  $7$   |              无附加限制               | $26$ |

## 样例 #1

### 输入

```
2 3
0 2
1 0
0
1
2
```

### 输出

```
2
8
12
```

## 样例 #2

### 输入

```
3 5
0 0
2 2
5 5
0
1
2
3
4
```

### 输出

```
3
12
21
24
26
```

## 样例 #3

### 输入

```
4 10
-3 -3
3 3
-4 4
4 -4
0
1
2
3
4
5
6
7
8
9
```

### 输出

```
4
16
32
48
56
56
55
56
60
64
```

# 题解

## 作者：EXODUS (赞：6)

# Part 1：前言
JPOI 独自の巨大なデータ構造！

由于笔者能力有限，这里的代码部分只提供了 JOI 写了 10k 的 std，很抱歉因此造成的不便。以后写了这道题，会把我的代码放上来（如果会写？/cf）。

# Part 2：正文
首先观察一个点是如何扩张的。由于灰色格子的存在，一定不会使得一个格子两次变成黑色。进一步考虑一个格子变成黑色的时间，我们发现是这个点到其最近的黑格子的曼哈顿距离。那么到此为止我们就会做前两个 Subtask 了。具体而言是对所有格子做 bfs 求出多源最短路，然后查询的时候查所有最短距离为 $t$ 的点的数量。

然后观察 $x=y,q=1$ 的部分分。注意到此时相当于是在对角线上有若干个斜长方形，每次每个方形会向外扩一圈，如果相交就合并成一个大的斜长方形。那么我们可以考虑每次询问时暴力枚举每一个黑色初始点生成的正方形，判断其是否和其下一个黑点正方形相交并计算其贡献，这样就是一个 $O(n\log n+qn)$ 的做法。

进一步考虑 $x=y$，我们注意到这种相交事件只会发生 $n$ 次，而对于一段未发生相交事件的时刻，答案是一个一次函数（考虑到每一次扩展实际上是对于每个方形多四个黑点），因此总的答案实际上是一个分 $n$ 段的函数。预处理出来这 $n$ 段即可，具体而言是对横坐标排序后计算出相邻两个的相交时刻，再按照相交时刻排序，改变一次函数的斜率和截距，这样复杂度是 $O(n\log n+q)$ 的。

现在考虑 $x\neq y,q=1$。此时最大的问题是方形相交以后会变成不规则图形，而这是我们难以维护的。那么我们转而考虑计算每一条边的贡献。注意到图形的相交实际上是边的相交，那么我们枚举每一条边，去掉其在 $t$ 时刻时跟前面相交的部分，将其贡献入答案，就得到了一个 $O(qn^2)$ 的做法。

进一步考虑 $q\neq 1$，仿照上面我们对 $q\neq 1$ 的处理。我们发现计算边的贡献后，对于一段未发生相交事件的时刻，每条边的贡献仍然是一个一次函数。那么我们仍然枚举每一条边的和前面的边，计算其相交的时间，然后再按照时间排序，处理出这个线性函数即可，这样复杂度是 $O(n^2+qn)$ 的，对所有一次函数加和即可做到 $O(n^2+q)$ 。

最后考虑正解怎么做。考虑边的总的贡献函数实际上长成什么样子。注意到所有边的分段总数实际上是 $O(n)$ 级别的，这是因为总贡献函数会改变当且仅当这个两条边相交或者一条边被其余的边完全覆盖。对于这两种情况，我们分别考虑。对于边相交的情况，我们做八次扫描线，每次计算每一个初始方形的每一个端点在每一个方向上的最近边。对于第二种情况，我们可以通过第一次的结果计算而来（这一点在官解中没有详细提到，但由于笔者并没有实现不知道具体细节应当怎么做，故具体细节可以见代码），那么我们对于扫描出来的所有时间段做分段函数处理即可，时间复杂度 $O(n\log n+q)$。



# Part 3：代码

```cpp
/*
	FULL-SCORE SOLUTION
	- Time Complexity: O((Q + N) log N)
*/

#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class value {
public:
	long long x; int p1, p2; // value: x + p1 * eps + p2 * eps^2 (eps > 0 is an arbitrary value which is small enough)
	value() : x(0), p1(0), p2(0) {}
	value(long long x_, int p1_, int p2_) : x(x_), p1(p1_), p2(p2_) {}
	bool operator<(const value& v) const { return x != v.x ? x < v.x : (p1 != v.p1 ? p1 < v.p1 : p2 < v.p2); }
	bool operator>(const value& v) const { return x != v.x ? x > v.x : (p1 != v.p1 ? p1 > v.p1 : p2 > v.p2); }
	value operator+() const { return value(+x, +p1, +p2); }
	value operator-() const { return value(-x, -p1, -p2); }
	value& operator+=(const value& v) { x += v.x; p1 += v.p1; p2 += v.p2; return *this; }
	value& operator-=(const value& v) { x -= v.x; p1 -= v.p1; p2 -= v.p2; return *this; }
	value operator+(const value& v) const { return value(*this) += v; }
	value operator-(const value& v) const { return value(*this) -= v; }
};

class nearest_info {
public:
	int idx; value d1, d2;
	nearest_info() : idx(-1), d1(value()), d2(value()) {}
	nearest_info(int idx_, const value& d1_, const value& d2_) : idx(idx_), d1(d1_), d2(d2_) {}
};

class segment {
public:
	long long a, b, l, r; // y = ax + b (l <= x <= r)
	segment() : a(0), b(0), l(0), r(0) {}
	segment(long long a_, long long b_, long long l_, long long r_) : a(a_), b(b_), l(l_), r(r_) {}
};

// FUNCTION FOR SOLVING "CONTINUOUS VERSION" OF THE PROBLEM
// - Given N points (X[0], Y[0]), ..., (X[N-1], Y[N-1]) and Q queries with T[0], T[1], ..., T[Q-1]
// - For each query j, answer the following:
//   - Consider N squares that, for i = 0, 1, ..., N-1, the lower-left point is at (X[i], Y[i]) and the upper-right point is at (X[i]+T[j], Y[i]+T[j]).
//   - Calculate the area of union of these N squares.
vector<long long> area_union(int N, int Q, const vector<long long>& X, const vector<long long>& Y, const vector<long long>& T) {
	// step #1. compute nearest colliding square, for each square's corner
	vector<value> xp(N), yp(N);
	for (int i = 0; i < N; i++) {
		xp[i] = value(X[i], i, 0);
		yp[i] = value(Y[i], 0, i);
	}
	vector<vector<nearest_info> > nearest(8, vector<nearest_info>(N)); // d1: distance, d2: "orthogonal" distance
	for (int i = 0; i < 8; i++) {
		vector<value> xv(N), yv(N);
		for (int j = 0; j < N; j++) {
			switch (i) {
				case 0: xv[j] = +xp[j]; yv[j] = +yp[j]; break;
				case 1: xv[j] = +xp[j]; yv[j] = -yp[j]; break;
				case 2: xv[j] = -yp[j]; yv[j] = +xp[j]; break;
				case 3: xv[j] = -yp[j]; yv[j] = -xp[j]; break;
				case 4: xv[j] = -xp[j]; yv[j] = -yp[j]; break;
				case 5: xv[j] = -xp[j]; yv[j] = +yp[j]; break;
				case 6: xv[j] = +yp[j]; yv[j] = -xp[j]; break;
				case 7: xv[j] = +yp[j]; yv[j] = +xp[j]; break;
			}
		}
		vector<int> perm(N);
		for (int i = 0; i < N; i++) {
			perm[i] = i;
		}
		sort(perm.begin(), perm.end(), [&](int va, int vb) {
			return yv[va] < yv[vb];
		});
		set<value> s;
		for (int j : perm) {
			set<value>::iterator it = s.lower_bound(xv[j] - yv[j]);
			while (it != s.end() && xv[abs(it->p1)] < xv[j]) {
				it = s.erase(it);
			}
			if (it != s.begin()) {
				--it;
				nearest[i][j] = nearest_info(abs(it->p1), xv[j] - xv[abs(it->p1)], yv[j] - yv[abs(it->p1)]);
			}
			s.insert(xv[j] - yv[j]);
		}
	}
	for (int i = 0; i < 8; i += 2) {
		int p = vector<int>({ 7, 2, 1, 4, 3, 6, 5, 0 })[i];
		for (int j = 0; j < N; j++) {
			if (nearest[i][j].idx != -1 && nearest[p][j].idx != -1) {
				if (nearest[i][j].d1 > nearest[p][j].d1) {
					nearest[i][j] = nearest_info();
				}
				else {
					nearest[p][j] = nearest_info();
				}
			}
		}
	}

	// step #2. compute "time lapse" of each square's edge
	vector<vector<vector<nearest_info> > > timelapse(8, vector<vector<nearest_info> >(N)); // d1: time, d2: distance from another corner
	for (int i = 0; i < 8; i++) {
		int p1 = vector<int>({ 7, 2, 1, 4, 3, 6, 5, 0 })[i];
		int p2 = vector<int>({ 4, 5, 6, 7, 0, 1, 2, 3 })[i];
		for (int j = 0; j < N; j++) {
			if (nearest[p1][j].idx != -1) {
				timelapse[i][j].push_back(nearest_info(nearest[p1][j].idx, nearest[p1][j].d1, nearest[p1][j].d1));
			}
			if (nearest[p2][j].idx != -1) {
				timelapse[i][nearest[p2][j].idx].push_back(nearest_info(j, nearest[p2][j].d1, nearest[p2][j].d2));
			}
		}
		for (int j = 0; j < N; j++) {
			sort(timelapse[i][j].begin(), timelapse[i][j].end(), [&](const nearest_info& f1, const nearest_info& f2) {
				return f1.d1 < f2.d1;
			});
		}
	}

	// step #3. find all crashes & rectangular holes
	const long long INF = (3LL << 60);
	vector<vector<value> > eliminate(4, vector<value>(N, value(INF, 0, 0)));
	for (int i = 0; i < 8; i += 2) {
		for (int j = 0; j < N; j++) {
			if (!timelapse[i + 0][j].empty() && !timelapse[i + 1][j].empty()) {
				nearest_info f0 = timelapse[i + 0][j].back();
				nearest_info f1 = timelapse[i + 1][j].back();
				value t = f0.d2 + f1.d2;
				if ((timelapse[(i + 2) % 8][f0.idx].empty() || timelapse[(i + 2) % 8][f0.idx].back().d1 < t) && timelapse[(i + 3) % 8][f0.idx].back().d1 < t) {
					eliminate[((i + 2) % 8) / 2][f0.idx] = min(eliminate[((i + 2) % 8) / 2][f0.idx], t);
				}
				if ((timelapse[(i + 7) % 8][f1.idx].empty() || timelapse[(i + 7) % 8][f1.idx].back().d1 < t) && timelapse[(i + 6) % 8][f1.idx].back().d1 < t) {
					eliminate[((i + 6) % 8) / 2][f1.idx] = min(eliminate[((i + 6) % 8) / 2][f1.idx], t);
				}
				eliminate[i / 2][j] = min(eliminate[i / 2][j], t);
			}
		}
	}

	// step #4. final calculation
	vector<segment> seg;
	for (int i = 0; i < 8; i += 2) {
		for (int j = 0; j < N; j++) {
			seg.push_back(segment(1, 0, 0, eliminate[i / 2][j].x));
			for (int k = 0; k < 2; k++) {
				if (!timelapse[i + k][j].empty()) {
					seg.push_back(segment(-1, timelapse[i + k][j][0].d2.x, timelapse[i + k][j][0].d1.x, eliminate[i / 2][j].x));
					for (int l = 1; l < timelapse[i + k][j].size(); l++) {
						seg.push_back(segment(0, -(timelapse[i + k][j][l - 1].d2 - timelapse[i + k][j][l].d2).x, timelapse[i + k][j][l].d1.x, eliminate[i / 2][j].x));
					}
				}
			}
		}
	}
	vector<long long> tcomp({ 0, INF });
	for (segment s : seg) {
		if ((s.a != 0 || s.b != 0) && s.l != s.r) {
			tcomp.push_back(s.l);
			tcomp.push_back(s.r);
		}
	}
	sort(tcomp.begin(), tcomp.end());
	tcomp.erase(unique(tcomp.begin(), tcomp.end()), tcomp.end());
	vector<long long> polya(tcomp.size()), polyb(tcomp.size()); // y = ax + b
	for (segment s : seg) {
		if ((s.a != 0 || s.b != 0) && s.l != s.r) {
			int pl = lower_bound(tcomp.begin(), tcomp.end(), s.l) - tcomp.begin();
			int pr = lower_bound(tcomp.begin(), tcomp.end(), s.r) - tcomp.begin();
			polya[pl] += s.a;
			polya[pr] -= s.a;
			polyb[pl] += s.b;
			polyb[pr] -= s.b;
		}
	}
	for (int i = 1; i < tcomp.size(); i++) {
		polya[i] += polya[i - 1];
		polyb[i] += polyb[i - 1];
	}
	vector<long long> cum(tcomp.size());
	for (int i = 0; i < int(tcomp.size()) - 1; i++) {
		long long yl = polya[i] * tcomp[i] + polyb[i];
		long long yr = polya[i] * tcomp[i + 1] + polyb[i];
		cum[i + 1] = cum[i] + (yl + yr) * (tcomp[i + 1] - tcomp[i]) / 4;
	}
	vector<long long> answer(Q);
	for (int i = 0; i < Q; i++) {
		int pos = lower_bound(tcomp.begin(), tcomp.end(), T[i] + 1) - tcomp.begin() - 1;
		long long yl = polya[pos] * tcomp[pos] + polyb[pos];
		long long yt = polya[pos] * T[i] + polyb[pos];
		answer[i] = cum[pos] + (yl + yt) * (T[i] - tcomp[pos]) / 4;
	}
	return answer;
}

// FUNCTION FOR SOLVING THE MAIN PROBLEM
vector<long long> solve(int N, int Q, const vector<long long>& X, const vector<long long>& Y, const vector<long long>& T) {
	auto half = [&](long long x) {
		return (x >= 0 ? x / 2 : -((-x + 1) / 2));
	};
	vector<long long> xa, ya, xb, yb;
	for (int i = 0; i < N; i++) {
		if ((X[i] + Y[i]) % 2 == 0) {
			xa.push_back((X[i] + Y[i] + 0) / 2); ya.push_back((X[i] - Y[i] + 0) / 2);
			xa.push_back((X[i] + Y[i] + 0) / 2); ya.push_back((X[i] - Y[i] + 2) / 2);
			xa.push_back((X[i] + Y[i] + 2) / 2); ya.push_back((X[i] - Y[i] + 0) / 2);
			xa.push_back((X[i] + Y[i] + 2) / 2); ya.push_back((X[i] - Y[i] + 2) / 2);
			xb.push_back((X[i] + Y[i] + 2) / 2); yb.push_back((X[i] - Y[i] + 2) / 2);
		}
		else {
			xa.push_back((X[i] + Y[i] + 1) / 2); ya.push_back((X[i] - Y[i] + 1) / 2);
			xb.push_back((X[i] + Y[i] + 1) / 2); yb.push_back((X[i] - Y[i] + 1) / 2);
			xb.push_back((X[i] + Y[i] + 1) / 2); yb.push_back((X[i] - Y[i] + 3) / 2);
			xb.push_back((X[i] + Y[i] + 3) / 2); yb.push_back((X[i] - Y[i] + 1) / 2);
			xb.push_back((X[i] + Y[i] + 3) / 2); yb.push_back((X[i] - Y[i] + 3) / 2);
		}
	}
	vector<long long> T2(Q * 2);
	for (int i = 0; i < Q; i++) {
		T2[i * 2 + 0] = T[i];
		T2[i * 2 + 1] = (T[i] >= 1 ? T[i] - 1 : 0);
	}
	vector<long long> resa = area_union(xa.size(), Q * 2, xa, ya, T2);
	vector<long long> resb = area_union(xb.size(), Q * 2, xb, yb, T2);
	vector<long long> answer(Q, 0);
	for (int i = 0; i < Q; i++) {
		if (T[i] == 0) {
			answer[i] = N;
		}
		else {
			answer[i] += resa[2 * i + 0] - (T[i] >= 2 ? resa[2 * i + 1] : 0);
			answer[i] += resb[2 * i + 0] - (T[i] >= 2 ? resb[2 * i + 1] : 0);
			if (T[i] == 1) {
				answer[i] -= N;
			}
		}
	}
	return answer;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int N, Q;
	cin >> N >> Q;
	vector<long long> X(N), Y(N), T(Q);
	for (int i = 0; i < N; i++) {
		cin >> X[i] >> Y[i];
	}
	for (int i = 0; i < Q; i++) {
		cin >> T[i];
	}
	vector<long long> answer = solve(N, Q, X, Y, T);
	for (int i = 0; i < Q; i++) {
		cout << answer[i] << '\n';
	}
	return 0;
}

```


---

