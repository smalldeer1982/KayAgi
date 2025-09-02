# Swaps

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_c

$ N $ 要素からなる $ 2 $ つの整数列 $ A_1,...,A_N $ 及び $ B_1,...,B_N $ が与えられます。 以下の操作を $ N-2 $ 回まで ($ 0 $ 回でもよい) 行うことで、$ 1 $ 以上 $ N $ 以下のすべての整数 $ i $ に対して $ A_i\ \leqq\ B_i $ となるようにできるかを判定してください。

- $ 1 $ 以上 $ N $ 以下の相異なる整数 $ x $, $ y $ を選び、$ A_x $ の値と $ A_y $ の値を入れ替える。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ A_i,B_i\ ≦\ 10^9 $

### Sample Explanation 1

$ A_2 $ の値と $ A_3 $ の値を入れ替えればよいです。

## 样例 #1

### 输入

```
3
1 3 2
1 2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
1 2 3
2 2 2```

### 输出

```
No```

## 样例 #3

### 输入

```
6
3 1 2 6 3 4
2 2 8 3 4 3```

### 输出

```
Yes```

# 题解

## 作者：UnyieldingTrilobite (赞：5)

题意大概是说给你两个长度为 $n$ 的正整数序列 $A,B$ 问能不能对 $A$ 进行 $n-2$ 次交换操作使得在每个位置 $i$ 上都有 $A_i\le B_i$。

我们注意到选择排序一共是 $n-1$ 次交换，用几乎一模一样的方式就能在 $n-1$ 次交换内让 $A_i$ 任意排列。观察最终约束的形式，肯定最好是能让 $A$ 中第 $k$ 小的数和 $B$ 中第 $k$ 小的数全都去配上，那要是这都不行，直接判掉，输出 `No`。

还有另外一种情况是如果存在一个 $k$ 满足 $A$ 中第 $k+1$ 小的数不大于 $B$ 中第 $k$ 小的数，那就可以先把除去 $k$ 和 $k+1$ 以外的 $n-2$ 个名次配好（由于这两个名次的干扰，这一步实际上需要 $n-2$ 次操作，可以自行理解一下），然后 $A$ 中剩下这两个名次的数就一定和 $B$ 中这两个名次的数对应上了（只是按名次顺序匹配还是按名次顺序交叉匹配的关系，因为很显然此时只要最多再一次交换就能把 $A$ 完全和 $B$ 按名次顺序匹配上），然而注意到这两个名次不管怎么匹配都是符合题意的（这是因为我们一开始的假设），于是就一定输出 `Yes`。这种情况实际上对应于 $A$ 不需要严格排序就能满足题意。

现在就只剩一种情况了：$A$ 可以满足题意，但必须严格排好序。那这部分就相当于判断严格排序是否能通过 $n-2$ 次操作实现。我们观察到可以从 $A$ 中第 $k$ 小数的下标向 $B$ 中第 $k$ 小的下标连边（一共 $n$ 个节点）。由于每个点有且仅有一条入边和出边，实际上最后的图一定是若干个环。显然，一个包含了 $x$ 个节点的环上的下标要想严格排序至多 $x-1$ 次操作（和全局排序同理），那也就是若至少有两个环就可以 $n-2$ 次排完否则不能。唯一可能有点小问题的地方在于重复元素，但实际上这种情况早就在前两段里被讨论完了，不会进入这一步。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 9;
pair<int, int> a[N], b[N];
int n, tar[N];
bool vst[N];
int getcnt() {
  int ret = 0;
  for (int i = 1; i <= n; ++i)
    if (int x = i; !vst[x]) {
      ++ret;
      do vst[x] = true;
      while (!vst[x = tar[x]]);
    }
  return ret;
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i].first;
  for (int i = 1; i <= n; ++i) cin >> b[i].first;
  for (int i = 1; i <= n; ++i) a[i].second = b[i].second = i;
  sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
  for (int i = 1; i <= n; ++i)
    if (a[i].first > b[i].first) return puts("No"), 0;
  for (int i = 1; i < n; ++i)
    if (a[i + 1].first <= b[i].first) return puts("Yes"), 0;
  for (int i = 1; i <= n; ++i) tar[a[i].second] = b[i].second;
  puts(getcnt() >= 2 ? "Yes" : "No");
  return 0;
}
```

---

## 作者：喵仔牛奶 (赞：0)

# Solution

先将二元组 $(a_i,b_i)$ 按 $b_i$ 从小到大排序。设 $a$ 从小到大排序后为 $a'$，如果 $\exist i\in[1,n],a'_i>b_i$ 则答案为 **NO**。

设排列 $p$ 使得 $a'_i=a_{p_i}$。我们知道排序一个排列的交换次数是 $n$ 减去置换环个数。如果 $p$ 中置换环超过一个，显然可以排好序，答案为 **YES**。

考虑改动一下 $p$ 使其置换环个数超过一，显然对 $p$ 进行一次有意义的交换（交换后和原来不一样）就可以达成这一点。要求交换后仍然有 $\forall i\in[1,n],a_{p_i}\le b_i$，显然我们会交换相邻的数，也就是说如果 $\exist i\in[1,n),a_{p_{i+1}}\le b_i$ 就答案为 **YES**，否则为 **NO**。

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
	int n, chk, p[N]; pii a[N];
	int main() {
		cin >> n, chk = 1;
		REP(i, 1, n) cin >> a[i].se;
		REP(i, 1, n) cin >> a[i].fi, p[i] = i;
		sort(a + 1, a + 1 + n);
		sort(p + 1, p + 1 + n, [&](int x, int y) { return a[x].se < a[y].se; });
		REP(i, 1, n)
			if (a[p[i]].se > a[i].fi) chk = 0;
		int ct = 1;
		for (int x = p[1]; x != 1; )
			ct ++, x = p[x];
		if (ct == n) {
			int c = 0;
			REP(i, 1, n - 1)
				if (a[p[i + 1]].se <= a[i].fi) c = 1;
			chk &= c;
		}
		cout << (chk ? "Yes" : "No") << '\n';
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

## 作者：liangbowen (赞：0)

[blog](https://www.cnblogs.com/liangbowen/p/18474007)。不会做结论题，怎么办？？？不会做结论题，怎么办？？？不会做结论题，怎么办？？？

---

不妨对 $b$ 排序，将 $a$ 对应到相应的位置。那么题目有两个条件：

+ \#1：$\forall a_i\le b_i$。
+ \#2：操作限制。

注意到 $n-1$ 次操作就能对 $a$ 排序。所以 $n-2$ 次操作可将 $a$ **变成一个 Almost Sorted 的状态**。

启示我们对 $a$ 排序（下文记为 $a^\prime$）并直接进行分讨。具体地：

+ 若 $\exists a^\prime_i>b_i$，由 \#1，不会存在一个合法的 $a$，**NO**。
+ 否则，若 $\exists a^\prime_{i+1}\le b_i$，则有 $a^\prime_i\le a^\prime_{i+1}\le b_i\le b_{i+1}$，即交换 $a^\prime_i,a^\prime_{i+1}$ 后仍满足 \#1。可以发现它也满足 \#2，**YES**。
+ 否则，交换任一 $a^\prime_i,a^\prime_j$ 后都不满足 \#1，即合法的 $a$ 必须有序。直接检验 $a^\prime$ 是否满足 \#2 即可。

[code](https://atcoder.jp/contests/nikkei2019-2-qual/submissions/58897541)，时间复杂度 $O(n\log n)$。

---

