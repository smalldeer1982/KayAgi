# Barrels

## 题目描述

假设你拥有 $n$ 个水桶，它们依次排放，编号为 $1$ 到 $n$。

每个水桶是相同的，底面积为一个单位，因此水桶内的水量对应水柱的高度。起初，第 $i$ 个水桶中含有 $v_i$ 单位的水。

相邻的水桶之间通过管道相连。具体来说，对于每个从 $1$ 到 $n-1$ 的 $i$，水桶 $i$ 与水桶 $i+1$ 通过一个高度为 $h_i$ 的水平管道相连。管道的宽度可以忽略不计。这些管道可以让水在水桶之间流动。

现在，你想对这些水桶进行操作。你的目标是通过向水桶中投放粘土来最大化第一个水桶中的水量。每一步，你可以选择任意一个水桶，向其中添加一单位的粘土。粘土的单位体积与水相同，但粘土比水重且不会与水混合，因此它会下沉并均匀分布在桶底。

由于粘土具有黏性，当粘土的高度足够时，它会封住管道。更确切地说，如果管道的高度为 $h$，当粘土的高度达到或低于 $h$ 时，管道仍然能正常工作。然而，一旦你向水桶中多加了一单位的粘土，管道就会立刻被封住，阻止水在水桶之间流动。

你拥有大量的粘土，因此可以多次执行上述操作。但在每次操作之后，你需要等待水达到新的平衡状态。

你能让第一个水桶中的水量达到的最大值是多少？

假定水桶足够高，因此不会溢出，并且可以忽略管道的宽度。

## 样例 #1

### 输入

```
2
1 2
2```

### 输出

```
2.500000000000000```

## 样例 #2

### 输入

```
3
3 0 0
6 9```

### 输出

```
3.000000000000000```

## 样例 #3

### 输入

```
5
10 0 0 0 5
11 1 2 5```

### 输出

```
11.916666666666667```

# 题解

## 作者：Register_int (赞：3)

先来考虑题目中的最优策略是怎样的：从右往左选桶，每次将桶中扔进与左侧管道同高的黏土，待平衡后再扔一个将这个管子封死。这显然是最优的，否则由于整个过程中每个桶的液面高度都不降，水会被右侧的其他桶分掉。转化一下就是往最后一个桶灌一些水，再把最后一个桶炸掉。

可以发现，会有一些连续的桶，他们的水面高度是会同步变化的。我们直接将它们合并为一个“大水缸”，用三元组 $(l,r,v)$ 表示他由 $l\sim r$ 的水桶组成、水面高度为 $v$。

考虑加水时会发生怎样的变化:

- 如果当前大水缸满足 $v=h_{l-1}$，说明往里面加的水会沿着这个管子流到下一个，液面暂时不会变化。
- 如果满足 $v<h_r\le h_{l-1}$，那么这个水缸的水面升高到 $h_r$ 时会与前一个水缸合并。之后情况过于复杂暂且忽略。
- 如果满足 $v<h_{l-1}\le h_r$，那么将水缸的水加到 $h_{l-1}$ 后会变为第一种情况。

你发现可以将水分成若干次加进去，每次找到从右开始第一个满足 $v<h_{l-1}$ 的水缸往里加水，再处理后两种情况的合并。因为要么加不满直接退出、要么加到两个管子高度的其中一个，所以加的次数最多是 $n-1$ 加上管子的个数为 $O(n)$。直接用 set 即可维护每个大水缸，炸水桶时修改最右端的水缸即可，时间复杂度 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int MAXN = 2e5 + 10;
const db eps = 1e-8;

inline int f(db a, db b) {
	if (fabs(a - b) < eps) return 0;
	return a < b ? 1 : -1;
}

struct node {
	int l, r; mutable db v;
	node(int l = 0, int r = 0, db v = 0) : l(l), r(r), v(v) {}
	bool operator < (const node &rhs) const { return l < rhs.l; }
}; set<node> s; set<int> p;

int n, a[MAXN]; ll h[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) scanf("%lld", &h[i]); *h = h[n] = 1e18;
	for (int i = 1, j = 1; i <= n; i++) {
		if (a[i] > h[i] || a[i] == h[i] && a[i] == a[i + 1]) continue;
		s.emplace(j, i, a[i]);
		if (a[i] < h[j - 1]) p.insert(j); j = i + 1;
	}
//	for (node p : s) printf("[%d,%d]:%lf ", p.l, p.r, p.v); puts("");
//	system("pause");
	for (int i = n; i > 1; i--) {
//		printf("now:%d\n", i);
		db tot = h[i - 1];
		for (; ; ) {
//			printf("%lf\n", tot);
			if (p.empty()) { s.begin()->v += tot / i; break; }
			auto it = s.lower_bound(*p.rbegin());
			int len = it->r - it->l + 1; ll lh = h[it->l - 1], rh = h[it->r];
//			printf("%lf %lld\n", it->v + tot / len, min(lh, rh));
			if (f(it->v + tot / len, min(lh, rh)) >= 0) it->v += tot / len, tot = 0;
			else tot -= (min(lh, rh) - it->v) * len, it->v = min(lh, rh);
			node tmp = *it; p.erase(it->l);
/*			printf("erase:[%d,%d]:%lf\n", it->l, it->r, it->v), */it = s.erase(it);
			for (; ; tmp.r = it->r/*, printf("erase:[%d,%d]:%lf\n", it->l, it->r, it->v)*/, it = s.erase(it)) {
				if (it == s.end()) break;
				if (f(tmp.v, h[tmp.r]) || f(it->v, h[tmp.r])) break;
			}
			if (f(tmp.v, h[tmp.l - 1]) > 0) p.insert(tmp.l);
			s.emplace(tmp); if (!f(tot, 0)) break;
//			for (node p : s) printf("[%d,%d]:%lf ", p.l, p.r, p.v); puts("");
//			system("pause");
		}
		node tmp = *s.rbegin(); s.erase(tmp), h[i - 1] = 1e18;
		if (tmp.l < tmp.r) s.emplace(tmp.l, tmp.r - 1, tmp.v);
//		for (node p : s) printf("[%d,%d]:%lf ", p.l, p.r, p.v); puts("");
//		system("pause");
	}
	printf("%.15lf", s.begin()->v);
}
```

---

## 作者：lfxxx (赞：0)

先考虑我们的策略如何，我们想要尽可能地把水往前赶，所以考虑从后往前依次放泥土，感性理解就是对于每个前缀问题都可以让每个水桶中的水尽量多，严谨证明可以考虑对于每个前缀问题归纳，这里略去，剩下的问题是如何维护。

考虑水位是如何变化的，首先不妨把联通的水合并成一个连通块，连通块内的水位相同且会一起变化，然后你考虑把一个水桶的水位垫高其实可以转化为向其所在连通块加水，我们考虑向一个连通块加水会产生什么影响。

我们发现，对于连通块 $i$ 加水后，假若从 $i$ 开始往前有一串水位依次递减且每个连通块的水位等于前面一个连通块与其之间的管道高度的连通块，那么加的水最后会流到这一串连通块中最靠前的连通块，由于加水会引起连通块合并（形态变化）以及这一串连通块的形态变化，并且只在最靠前的连通块水位达到与前一个连通块之间的管道高度或者与后面一个连通块间的管道高度时发生变化，所以先一直加水到这两个变化其中之一发生，再去更新形态，由于最靠前的连通块只会越来越靠前，并且每个连通块形态只会变化 $O(1)$ 次，所以用并查集暴力模拟即可做到 $O(n \log n)$。

还有若干细节，具体可以见[代码](https://codeforces.com/contest/2038/submission/298925295)。

---

