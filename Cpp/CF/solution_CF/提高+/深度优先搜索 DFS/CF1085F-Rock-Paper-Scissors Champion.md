# Rock-Paper-Scissors Champion

## 题目描述

有 $n$ 名选手将参加一场石头剪子布锦标赛。你可能知道，在一场一对一的石头剪子布比赛中，两名选手各自独立选择自己的手势。比赛结果根据所选手势决定：“布”胜“石头”，“石头”胜“剪刀”，“剪刀”胜“布”，如果两人出相同的手势则为平局。

比赛开始时，所有选手按顺序站成一排，编号从左到右依次为 $1$ 到 $n$。每位选手都有一个预先选择好的手势，并将在整个比赛中一直使用这个手势。比赛的进行方式如下：

- 如果只剩下一名选手，则他成为冠军。
- 否则，任意选择一对相邻的选手进行下一场比赛。失败者被淘汰并离开队列（其原来的邻居变为相邻）。如果比赛为平局，则通过掷硬币决定淘汰者。

主办方已知所有选手的初始手势。他们想知道，有多少名选手有可能成为冠军（即存在一种合理的比赛顺序和硬币结果，使得该选手最终获胜）。然而，有些选手还在调整策略，可能会通知主办方他们的新手势。请你在每次这样的请求后，计算当前有多少名选手有可能成为冠军。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 5
RPS
1 S
2 R
3 P
1 P
2 P
```

### 输出

```
2
2
1
2
2
3
```

# 题解

## 作者：duyi (赞：2)

# CF1086D Rock-Paper-Scissors Champion

先不管修改，只对一个序列求答案。

考虑暴力枚举每个人，判断他是否可能成为冠军。因为 R, S, P 本质是等价的，所以不妨假设我们枚举的人打算出 R。那么他与 S 比时会赢，与 P 比时会输。

如果这个人左右两边都不存在 P，他显然可以夺冠（因为和 R 比时，都可以钦定他获胜）。否则，考虑如果他的左边有 P，那么需要在他和这个 P 比赛之前，提前让一个 S 来击败 P。所以他的左边必须同时也有一个 S。并且只要他左边存在一个 S，就一定能通过安排顺序，使得 S 逐个击败他左边的所有 P。右边也是类似的。

于是我们得出结论：**一个人不能夺冠，当且仅当他的左边或右边，存在一个能击败他的人（P）且不存在能被他击败的人（S）**。

在有修改时，我们用三个数据结构分别维护 R, S, P 三个东西的出现位置。修改时直接在数据结构上更新（单点修改）。然后考虑求答案。枚举 R, S, P 三种东西，考虑这种东西有多少个是**不能夺冠**的。容易发现不能夺冠的是两个区间的并：以 R 为例，不能夺冠的是左边第一个 P 到第一个 S 之间的这段区间，以及右边最后一个 S 到最后一个 P 之间这段区间。用数据结构求区间元素个数即可。

综上我们的数据结构要支持：单点修改（插入 / 删除元素），求第一次 / 最后一次出现的位置，区间求和（求区间元素数量）。可以用线段树上二分，或 $\texttt{std::set}$ + 树状数组来实现（因为只有 $\texttt{std::set}$ 的话可能不支持最后一项操作）。

时间复杂度 $O((n+q)\log n)$。

参考代码：

我选择了用 $\texttt{std::set}$ + 树状数组实现。

```cpp
// problem: CF1086D
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 2e5;
struct FenwickTree {
	int c[MAXN + 5], sz;
	void point_add(int p, int v) {
		for (int i = p; i <= sz; i += (i & (-i))) {
			c[i] += v;
		}
	}
	int query_pre_sum(int p) {
		int res = 0;
		for (int i = p; i; i -= (i & (-i))) {
			res += c[i];
		}
		return res;
	}
	int query_range_sum(int l, int r) {
		assert(l >= 1);
		assert(r <= sz);
		assert(l <= r);
		return query_pre_sum(r) - query_pre_sum(l - 1);
	}
	void init(int _sz) {
		sz = _sz;
	}
	FenwickTree() {}
};

/*
约定: Rock = 0, Scissors = 1, Paper = 2
*/
map<char, int> id;
set<int> s[3];
FenwickTree fwk[3];

int n, q;
char str[MAXN + 5];

void modify(int p, int oldc, int newc) {
	s[oldc].erase(p);
	fwk[oldc].point_add(p, -1);
	s[newc].insert(p);
	fwk[newc].point_add(p, 1);
}
int calc(int me, int lose, int win) {
#define IT set<int> :: iterator
	if (!SZ(s[win]))
		return 0;
	int res = 0;
	
	int p = *s[win].begin();
	IT it = s[lose].lob(p);
	int l1 = -1, r1 = -1, l2 = -1, r2 = -1;
	if (it == s[lose].begin()) {
		int nxt = n + 1;
		if (it != s[lose].end()) nxt = *it;
		if (p + 1 <= nxt - 1) {
			res += fwk[me].query_range_sum(p + 1, nxt - 1);
			l1 = p + 1;
			r1 = nxt - 1;
		}
	}
	p = *s[win].rbegin();
	it = s[lose].upb(p);
	if (it == s[lose].end()) {
		int pre = 0;
		if (it != s[lose].begin()) { --it, pre = *it; }
		if (pre + 1 <= p - 1) {
			res += fwk[me].query_range_sum(pre + 1, p - 1);
			l2 = pre + 1;
			r2 = p - 1;
		}
	}
	if (l1 != -1 && l2 != -1) {
		if (l1 > l2) {
			swap(l1, l2);
			swap(r1, r2);
		}
		if (l2 <= r1) {
			res -= fwk[me].query_range_sum(l2, min(r1, r2));
		}
	}
	return res;
#undef IT
}
int getans() {
	int res = n;
	res -= calc(0, 1, 2);
	res -= calc(1, 2, 0);
	res -= calc(2, 0, 1);
	return res;
}
int main() {
	id['R'] = 0;
	id['S'] = 1;
	id['P'] = 2;
	cin >> n >> q;
	cin >> (str + 1);
	
	fwk[0].init(n);
	fwk[1].init(n);
	fwk[2].init(n);
	for (int i = 1; i <= n; ++i) {
		s[id[str[i]]].insert(i);
		fwk[id[str[i]]].point_add(i, 1);
	}
	cout << getans() << endl;
	for (int tq = 1; tq <= q; ++tq) {
		int p; char c;
		cin >> p >> c;
		modify(p, id[str[p]], id[c]);
		str[p] = c;
		cout << getans() << endl;
	}
	return 0;
}
```





---

