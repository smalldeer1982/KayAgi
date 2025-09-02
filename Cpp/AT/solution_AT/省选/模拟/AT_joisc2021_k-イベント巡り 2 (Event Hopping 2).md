# イベント巡り 2 (Event Hopping 2)

## 题目描述

IOI Park 将有 $n$ 场活动。

这些活动的编号从 $1$ 到 $n$。 活动 $i$ 从时间 $L_i+10^{-1}$ 到时间 $R_i-10^{-1}$ 举行。数据保证 $L_i$ 和 $R_i$ 是整数。

JOI 君决定参加其中的 $k$ 个活动。但是，JOI 君不能在中间加入或离开每个活动。**在两个活动场所间移动的时间忽略不计**。

JOI 君希望参加编号较小的活动。严格来说，JOI 君参加的 $k$ 个活动的编号依次为 $a_1,\cdots,a_k$，其中 $1 \le a_1 < \cdots < a_k \le n$。如果序列 $(a_1, \cdots, a_k)$ 的编号小于 $(b_1, \cdots, b_k)$，当且仅当存在 $j\ (1 \le j \le k)$ 满足在区间 $[1,j-1]$ 里的所有 $l$ 都有 $a_l=b_l$ 和 $a_j<b_j$。



给出每个活动的信息和 JOI 君参加的活动个数 $k$，判断 JOI 君是否可以参加 $k$ 个活动，如果可以，输出所有的 $k$ 个活动的编号。

## 说明/提示

#### 样例 #1 解释

有 $2$ 种方式可以参加正好 $4$ 个活动。

- 参加 $1, 3, 4, 5$；
- 参加 $2, 3, 4, 5$。

数列 $(1,3,4,5)$ 比数列 $(2, 3, 4, 5)$ 字典序小，所以输出 $1, 3, 4, 5$。

#### 样例 #2 解释

无论怎么选择都不可能正好参加 $3$ 个活动，所以输出 $\tt -1$。

#### 样例 #3 解释

本样例满足所有 Subtask 的条件。

#### 数据规模与约定

**因洛谷限制，本题不予评测每个 Subtask 的第 $1\sim 20$ 个测试点。**

**本题采用 Subtask 计分法。**

| Subtask | 分值占比百分率 | $n$ | $L_i$ |
| :----: | :----: | :----: | :----:|
| $1$ | $7\%$ | / | $L_i \le L_{i+1}\ (1 \le i \le n − 1)$ |
| $2$ | $1\%$ | $\le20$ | / |
| $3$ | $31\%$ | $\le 3 \times 10^3$ |/ |
| $4$ | $61\%$ | / | / |

**注：斜线表示无特殊限制。**

对于 $100\%$ 的数据：
- $1\le n\le 10^5$；
- $1 \le k \le n$；
- $1\le L_i \le R_i \le 10^9$，且 $1\le i \le n$。



本题译自 [第２０回日本情報オリンピック 2020/2021春季トレーニング合宿 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [競技 4 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/2021-sp-d4-notice.pdf) [T1 日文题面](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/event2.pdf)。

# 题解

## 作者：Otue (赞：0)

### 题目描述

有 $n$ 场活动。这些活动的编号从 $1$ 到 $n$。 活动 $i$ 从时间 $L_i+10^{-9}$ 到时间 $R_i-10^{-9}$ 举行。数据保证 $L_i$ 和 $R_i$ 是整数。你决定参加其中的 $k$ 个活动。但是，你不能在中间加入或离开每个活动。**在两个活动场所间移动的时间忽略不计**。

你希望参加编号字典序较小的活动。给出每个活动的信息和你参加的活动个数 $k$，判断 JOI 君是否可以参加 $k$ 个活动，如果可以，输出所有的 $k$ 个活动的编号。

### 思路

首先将 $R_i$ 减一转化成区间互不相交。再将 $L_i,R_i$ 离散化。

考虑这类问题的直接贪心：选择没有交叉，右端点最靠左的。定义 $f(l,r)$ 表示区间 $[l,r]$ 最多能选的互不重合的区间个数。

考虑倍增求解 $f$。定义 $g_{i,j}$ 表示从 $i$ 开始选择 $2^j$ 个区间后，下一次进行选择时的左端点的最小值。显然有 $g_{l_i,0}=r_i+1$。转移需要继承上一次的答案：`g[i][j] = min{g[i + 1][j], g[g[i][j - 1][j - 1]}`。那么 $f(i,j)$ 只需要从 $i$ 开始倍增，累计答案即可。

回归本题，如何求解字典序最小的问题，那就是从 $1$ 到 $n$ 区间依次填入。只要当前的区间填入后可以保证 **可将 $k$ 个区间全部填入**，当前区间就是解。

如何判断 $[L_i,R_i]$ 是否可以填入？即可维护一个 set 表示当前未参加活动的区间，最开始区间为 $[1,n]$。若 $[L_i,R_i]$ 是一个 **未布置活动的区间** 的子集，设这个 **未布置活动的区间** 为 $[L,R]$，则 $L\leq L_i\leq R_i\leq R$。

可以计算出填入这个 $[L_i,R_i]$ 区间后的 **可填入区间变化量** 是：$f(L,L_i-1)+f(R_i+1,R)+1-f(L,R)$。填入之后，把当前 $[L,R]$ 分裂成 $[L,L_i-1]$ 和 $[R_i+1,R]$ 即可。

如何找到当前区间所被包含的区间？重定义 set 的 `<` 符号 `r < x.l`，那么如果两个区间重合，`set` 就会判定其为相等。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 2e5 + 5;

int n, k, b[N], tot, f[N][18], now;
vector<int> ans;

struct edge {
	int l, r;
}ed[N];

int query(int l, int r) {
	if (l > r) return 0;
	int x = l, res = 0;
	_pfor(i, 17, 0) {
		if (f[x][i] <= r + 1) {
			res += (1ll << i);
			x = f[x][i];
		}
	}
	return res;
}

struct stu {
	int l, r;
	bool operator < (const stu x) const {
		return r < x.l;
	}
};
set<stu> S;

signed main() {
	cin >> n >> k;
	_for(i, 1, n) {
		cin >> ed[i].l >> ed[i].r; ed[i].r--;
		b[++tot] = ed[i].l; b[++tot] = ed[i].r;
	}
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	_for(i, 1, tot + 3) _for(j, 0, 17) {
		f[i][j] = tot + 3;
	}
	_for(i, 1, n) {
		ed[i].l = lower_bound(b + 1, b + tot + 1, ed[i].l) - b;
		ed[i].r = lower_bound(b + 1, b + tot + 1, ed[i].r) - b;
		f[ed[i].l][0] = min(f[ed[i].l][0], ed[i].r + 1);
	}
	_pfor(i, tot, 1) {
		f[i][0] = min(f[i][0], f[i + 1][0]);
		_for(j, 1, 17) f[i][j] = min(f[i + 1][j], f[f[i][j - 1]][j - 1]); 
	}
	S.insert({1, tot}); now = query(1, tot);
	if (now < k) puts("-1"), exit(0);
	_for(i, 1, n) {
		auto it = S.find({ed[i].l, ed[i].r});
		if (it == S.end()) continue; stu tmp = *it;
		if (tmp.r < ed[i].r || tmp.l > ed[i].l) continue;
		int delta = query(tmp.l, ed[i].l - 1) + 1 + query(ed[i].r + 1, tmp.r) - query(tmp.l, tmp.r);
		if (now + delta >= k) {
			now += delta;
			ans.push_back(i);
			S.erase(it);
			if (tmp.l <= ed[i].l - 1) S.insert({tmp.l, ed[i].l - 1});
			if (ed[i].r + 1 <= tmp.r) S.insert({ed[i].r + 1, tmp.r});
		}
		if (ans.size() >= k) break;
	}
	for (auto v : ans) cout << v << endl;
}
```

---

