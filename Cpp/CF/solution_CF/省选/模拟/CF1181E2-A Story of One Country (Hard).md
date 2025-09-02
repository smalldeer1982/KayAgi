# A Story of One Country (Hard)

## 题目描述

本题与上一题的区别仅在于数据范围。

Petya 决定在暑假期间访问 Byteland。结果发现，这个国家的历史非常独特。

最初，在现在的 Berland 这片土地上有 $n$ 个不同的国家。每个国家都有自己的领土，在地图上表示为一个矩形。矩形的边平行于坐标轴，顶点的坐标均为整数。任意两个国家的领土没有重叠，但可能会相互接触。随着时间的推移，有时两个国家会合并成一个国家。只有当它们领土的并集也是一个矩形时，才能合并。最终，只剩下一个国家——Byteland。

最初，每个国家的领土内都有一座矩形城堡。城堡的边平行于坐标轴，顶点的坐标均为整数。有些城堡可能会接触到所属国家的边界、边或其他城堡。奇迹般地，经过所有合并后，这些城堡依然完好无损。不幸的是，我们现在仅能通过这些城堡的位置来还原最初各国的领土。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181E2/f468812bfa112254fc0a226123d17950651543de.png) Byteland 的可能形成过程。蓝色部分为城堡。Petya 很疑惑为什么没有留下关于最初各国的任何信息。他怀疑整个故事都是假的。有人向他推荐了你，认为你很聪明。请你判断是否存在一种可能的初始领土划分，使得这个故事成立。

## 说明/提示

下图展示了第一个和第二个样例中的城堡。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181E2/65c05eff44019e46877011da23e6739903c4b116.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181E2/13651d9028d4dc1ad40258518684f2d9fe9c5d09.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
0 0 1 2
0 2 1 3
1 0 2 1
1 1 2 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
0 0 2 1
1 2 3 3
2 0 3 2
0 1 1 3
```

### 输出

```
NO
```

# 题解

## 作者：Lice (赞：8)

### Description

在一个二维平面上有若干个矩形。定义一个矩形的（或有边在无限远处）区域为符合条件的条件为：

- 这个区域仅包含一个矩形，且不能使边界穿过任何一个矩形的内部。
- 这个区域可以用一个水平或竖直的直线分割为两个符合条件的区域。

现给定一个有 $n$ 个矩形的平面，请你判断整个平面区域是否符合条件。

### Hint

- for all: $1\le n\le 10^5$
    - for Easy: $n\le 10^3$
- $0\le \text{坐标大小} \le 10^9$

### Solution

#### Easy Version

对于小规模的数据，我们直接按题意分治即可。

对于一组矩形，我们可以先找一条分割线，分为两组矩形然后递归处理。

如何找分割线？不难想到按 $x,y$ 坐标分别直接排序。

这个做法复杂度 $O(n^2 \log n)$，足以通过 Easy 数据。

#### Code(Easy)

```cpp
/*
 * Author : _Wallace_
 * Source : https://www.cnblogs.com/-Wallace-/
 * Problem : Codeforces 1181E1 A Story of One Country (Easy)
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 1e5 + 5;

struct area {
	int u, d, l, r;
} ar[N];
typedef vector<area> areaList;
int n;

bool cmp_x(const area& x, const area& y) {
	return x.l < y.l;
}
bool cmp_y(const area& x, const area& y) {
	return x.u < y.u;
}

bool solve(areaList ar) {
	if (ar.size() == 1) return true;
	
	sort(ar.begin(), ar.end(), cmp_x);
	int maxR = ar.begin()->r;
	for (register int i = 1; i < ar.size(); i++)
		if (maxR <= ar[i].l)
			return solve(areaList(ar.begin(), ar.begin() + i))
				&& solve(areaList(ar.begin() + i, ar.end()));
		else maxR = max(maxR, ar[i].r);
	
	sort(ar.begin(), ar.end(), cmp_y);
	int maxD = ar.begin()->d;
	for (register int i = 1; i < ar.size(); i++)
		if (maxD <= ar[i].u)
			return solve(areaList(ar.begin(), ar.begin() + i))
				&& solve(areaList(ar.begin() + i, ar.end()));
		else maxD = max(maxD, ar[i].d);
	
	return false;
}

signed main() {
	cin >> n;
	areaList dat;
	for (register int i = 1; i <= n; i++) {
		area ar;
		cin >> ar.l >> ar.u >> ar.r >> ar.d;
		dat.push_back(ar);
	}
	
	if (solve(dat)) cout << "YES" << endl;
	else cout << "NO" << endl;
}
```

#### Hard

上面的算法之所以效率不高，很大原因是由于递归内部的排序。

因此不妨直接维护矩形的有序——```set```。

这里维护两个 set，分别按 $x, y$ 坐标排序。

假如找到了一条分割线，那么我们将这部分的矩形导出转移至两个新的 set 中，递归分治处理。

但假如分割线在非常后面，这就导致导出矩形的时间开销非常大。

于是我们使用 **启发式分裂** 的思想：当分割线在非常后面，虽然前面元素非常多，但后面元素却很少。使用为什么不导出后面，保留前面呢？

假如我们总是这样做，那么导出部分的效率就可以得到保证。

---------------------

现在又有一个棘手的问题——怎么找分割线？

假如直接扫 set 找，最坏还得扫过整个 set，复杂度又退化到了平方级别。

于是我们有想到 [Non-boring sequences](https://strncmp.blog.luogu.org/solution-uva1608) 中的 **中途相遇法**。

那个是一维意义上的中途相遇，而这里则是 **二维平面上的中途相遇**。

具体怎么做？题目不是给我们每个矩形的四个参数吗？于是我们根据 4 个方向，一个开 4 个 set。

并且我们要求 4 个方向同时向中间推进。

当其中一个方向找到了分割线，那么就 **直接开始导出**。由于这里可以导出的矩形个数一定不超过整个 set 的一半，于是不需要判断两边的个数多少，自然就保证了启发式分裂的实施。

时间复杂度为 $T(n) = T(x) + T(n - x) + O(x\log n)$ ，其中 $x$ 为导出的矩形的个数。

当 $x = \frac{n}{2}$ 时达到最劣情况，为 $O(n\log^2 n)$。

#### Code(Hard)

```cpp
/*
 * Author : _Wallace_
 * Source : https://www.cnblogs.com/-Wallace-/
 * Problem : Codeforces 1181E2 A Story of One Country (Hard)
 */
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;
const int N = 1e5 + 5;
const int MaxU = 1e9;

struct area {
	int l, r, u, d;
};
typedef vector<area> areaList;
int n;

struct cmp_l {
	inline bool operator () (const area& a, const area& b) {
		return a.l != b.l ? a.l < b.l : a.u < b.u;
	}
};
struct cmp_r {
	inline bool operator () (const area& a, const area& b) {
		return a.r != b.r ? a.r > b.r : a.d > b.d;
	}
};
struct cmp_u {
	inline bool operator () (const area& a, const area& b) {
		return a.u != b.u ? a.u < b.u : a.l < b.l;
	}
};
struct cmp_d {
	inline bool operator () (const area& a, const area& b) {
		return a.d != b.d ? a.d > b.d : a.r > b.r;
	}
};
typedef set<area, cmp_l> setL;
typedef set<area, cmp_r> setR;
typedef set<area, cmp_u> setU;
typedef set<area, cmp_d> setD;

bool solve(setL& sl, setR& sr, setU& su, setD& sd) {
	int size = sl.size();
	if (size == 1) return true;
	
	setL pl; setR pr;
	setU pu; setD pd;
	
	setL::iterator itl = sl.begin();
	setR::iterator itr = sr.begin();
	setU::iterator itu = su.begin();
	setD::iterator itd = sd.begin();
	
	int maxR = itl->r, maxD = itu->d;
	int minL = itr->l, minU = itd->u;
	
	while (--size) {
		++itl;
		if (maxR <= itl->l) {
			for (setL::iterator j = sl.begin(); j != itl; j++)
				pl.insert(*j), pr.insert(*j), pu.insert(*j), pd.insert(*j);
			for (setL::iterator j = sl.begin(); j != itl; j++)
				sr.erase(*j), su.erase(*j), sd.erase(*j);
			sl.erase(sl.begin(), itl);
			return solve(pl, pr, pu, pd) && solve(sl, sr, su, sd);
		} else {
			maxR = max(maxR, itl->r);
		}
		
		++itr;
		if (minL >= itr->r) {
			for (setR::iterator j = sr.begin(); j != itr; j++)
				pl.insert(*j), pr.insert(*j), pu.insert(*j), pd.insert(*j);
			for (setR::iterator j = sr.begin(); j != itr; j++)
				sl.erase(*j), su.erase(*j), sd.erase(*j);
			sr.erase(sr.begin(), itr);
			return solve(pl, pr, pu, pd) && solve(sl, sr, su, sd);
		} else {
			minL = min(minL, itr->l);
		}
		
		++itu;
		if (maxD <= itu->u) {
			for (setU::iterator j = su.begin(); j != itu; j++)
				pl.insert(*j), pr.insert(*j), pu.insert(*j), pd.insert(*j);
			for (setU::iterator j = su.begin(); j != itu; j++)
				sl.erase(*j), sr.erase(*j), sd.erase(*j);
			su.erase(su.begin(), itu);
			return solve(pl, pr, pu, pd) && solve(sl, sr, su, sd);
		} else {
			maxD = max(maxD, itu->d);
		}
		
		++itd;
		if (minU >= itd->d) {
			for (setD::iterator j = sd.begin(); j != itd; j++)
				pl.insert(*j), pr.insert(*j), pu.insert(*j), pd.insert(*j);
			for (setD::iterator j = sd.begin(); j != itd; j++)
				sl.erase(*j), sr.erase(*j), su.erase(*j);
			sd.erase(sd.begin(), itd);
			return solve(pl, pr, pu, pd) && solve(sl, sr, su, sd);
		} else {
			minU = min(minU, itd->u);
		}
	}
	
	return false;
}

signed main() {
	cin >> n;
	areaList dat;
	for (register int i = 1; i <= n; i++) {
		area ar;
		cin >> ar.l >> ar.u >> ar.r >> ar.d;
		dat.push_back(ar);
	}
	
	sort(dat.begin(), dat.begin(), cmp_l());
	setL sl(dat.begin(), dat.end());
	
	sort(dat.begin(), dat.begin(), cmp_r());
	setR sr(dat.begin(), dat.end());
	
	sort(dat.begin(), dat.begin(), cmp_u());
	setU su(dat.begin(), dat.end());
	
	sort(dat.begin(), dat.begin(), cmp_d());
	setD sd(dat.begin(), dat.end());
	
	if (solve(sl, sr, su, sd)) cout << "YES" << endl;
	else cout << "NO" << endl;
}
```

---

## 作者：喵仔牛奶 (赞：1)

## Solution

观察：如果一种方案合法，删除若干城堡仍然合法。

证明略。大体就是逐个删除，把删除的王国的矩形划给合并时的另一个矩形，然后再分给合成它的矩形，依此类推。

考虑倒着做，找到最终合成前分隔两个矩形的线，然后变成两个子问题。根据之前的观察，如果最终答案合法，任意切一条横线（或者竖线），如果没有划到城堡，划出的两个方案必定合法。

因此问题变成了每次找一条合法的分隔线。E1 直接暴力找就好了，考虑 E2。

我们知道 $T(n)=T(x)+T(n-x)+\mathcal O(\min(x,n-x))$ 是 $\mathcal O(n\log n)$ 的，考虑在 $\min(x,n-x)$ 的时间内找到一个分隔线。

从四个方向同时向内枚举，就可以做到 $\min(x,n-x)$ 的枚举量。但是还需要维护剩下的点，因此还需要使用 set，每次启发式分裂。

复杂度 $\mathcal O(n\log^2 n)$。

实现的时候可以使用 $4$ 个 set 从四个方向维护，具体见代码。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	struct node {
		int l, r, t;
		bool operator < (const node& p) const {
			if (l != p.l) return l < p.l;
			return (r == p.r ? t < p.t : r < p.r);
		}
	};
	struct tool {
		set<node>::iterator it; vector<int> v; int mx;
		tool() { mx = -1e9; }
	};
	int n, l, r, L, R; node a[N][4]; set<node> s[4];
	bool slv(set<node> s[4]) {
		int n = SZ(s[0]);
		if (n == 1) return 1;
		tool b[4];	
		REP(i, 0, 3) b[i].it = s[i].begin();
		REP(i, 2, n) REP(x, 0, 3) {
			auto &[it, v, mx] = b[x];
			mx = max(mx, it->r), v.pb(it->t), ++ it;
			if (mx <= it->l) {
				set<node> t[4];
				REP(y, 0, 3) for (int z : b[x].v)
					s[y].erase(a[z][y]), t[y].insert(a[z][y]);
				return slv(s) && slv(t);
			}
		}
		return 0;
	}
	int main() {
		cin >> n;
		REP(i, 1, n) {
			cin >> l >> L >> r >> R;
			a[i][0] = {l, r, i}, a[i][1] = {-r, -l, i};
			a[i][2] = {L, R, i}, a[i][3] = {-R, -L, i};
			REP(x, 0, 3) s[x].insert(a[i][x]);
		}
		cout << (slv(s) ? "YES" : "NO") << '\n';
		return 0;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

