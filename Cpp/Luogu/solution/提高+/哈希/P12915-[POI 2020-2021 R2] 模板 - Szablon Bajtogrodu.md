# [POI 2020/2021 R2] 模板 / Szablon Bajtogrodu

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/4833)。

## 题目描述

**题目译自 [XXVIII Olimpiada Informatyczna – II etap](https://sio2.mimuw.edu.pl/c/oi28-2/dashboard/) [Szablon Bajtogrodu](https://szkopul.edu.pl/problemset/problem/y-mTVYClxMJcgMhUnHaUqPPq/statement/)**

在 Bajtogród 里有 $n$ 个路口，它们通过一个简洁的双向街道网络连接在一起。这个网络之所以简洁，是因为从任意一个路口到另一个路口，恰好只有一条路径。每条街道都有自己的名字，就像城市里常见的那样。

当 Bajtek 在城里散步时，他会记下经过的每条街道名称的首字母。沿着若干连续街道（不回头）走过的路线，我们称之为一条**路径**。于是，走完某条路径后，Bajtek 会记下一个与这条路径对应的字符串。

今天，Bajtek 走了一条路径 $T$，发现它有个既有趣又没啥实际用处的特性：如果在 Bajtogród 中找出所有与路径 $T$ 对应相同字符串的路径，这些路径加起来至少会经过每条街道一次。Bajtek 把这种路径对应的字符串称为 **Bajtogród 的模板**。

过了一会儿，Bajtek 开始怀疑，自己认定的路径 $T$ 是否真的是 Bajtogród 的模板？或者，Bajtogród 根本就没有模板？他请你帮忙研究这个问题，找出 Bajtogród 所有的模板（如果存在的话）。

## 说明/提示

**样例 1 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/06on46rj.png)

在这个例子中，所有对应字符串 `AAB` 的六条路径（图中标红）加起来覆盖了每条街道至少一次，因此 `AAB` 是字节城的模板之一。

**附加样例**

1. 该样例满足 $n=21$，路径为一条直线，街道名称首字母交替为 `A` 和 `B`；
2. 该样例满足 $n=200$，没有模板；
3. 该样例满足 $n=200$，路径为一条直线，每条街道名称首字母均为 `A`；
4. 该样例满足 $n=1001$，星形结构，由五条长度为 $200$ 的路径组成，每条街道名称首字母均为 `A`；
5. 该样例满足 $n=1001$，星形结构，街道名称首字母一半为 `A`，一半为 `B`。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$ | $n \leq 50$ | $15$ |
| $2$ | $n \leq 200$ | $35$ |
| $3$ | 无附加限制 | $50$ |

## 样例 #1

### 输入

```
13
1 2 A
1 3 A
2 4 B
3 5 B
4 6 A
4 7 A
5 8 A
5 9 A
6 10 B
7 11 B
8 12 B
13 9 B```

### 输出

```
14
AAB
AABAB
AB
ABAABAB
ABAB
BA
BAA
BAAB
BAABAB
BABA
BABAA
BABAAB
BABAABA
BABAABAB```

# 题解

## 作者：Monomial (赞：1)

考虑一个比较暴力的思路，我们拉出所有的路径，然后判定是否所有边都在一条这样的路径上。

用 $\text{bitset}$ 维护，可以做到时间复杂度 $\mathcal{O}(n^2)$，空间复杂度 $\mathcal{O}(\frac{n^3}{\omega})$。但这题所开的空间不足以通过。

于是我们考虑进行分块。我们分成 $B$ 个一组，每次只去判定这 $B$ 条边是否在路径上，于是有时间复杂度 $\mathcal{O}(\frac{n^3}{B})$，空间复杂度 $\mathcal{O}(\frac{n^2B}{\omega})$，取 $B=500$ 就能避免空间爆掉。

然而此时我们已经接近成功了，但仍然无法通过，因为在树是一条链的情况下，总的本质不同的串的数量会几乎达到 $n^2$，跑起来非常慢。这是否可以优化呢？答案是肯定的。我们实际上只需要搜出叶子开始，或以叶子结尾的串即可，因为模板串必定需要经过所有的叶子连出的边，这样最终本质不同的合法串数量会有一定减少，可以轻松跑过。

---

## 作者：冷却心 (赞：0)

Hiten /bx /bx。

唐诗赤石题。

首先显然答案只有 $O(n)$ 种，我们任取一个叶子节点，那么他到他父亲的边一定是合法字符串的开头，所以答案集合一定是他到所有点的路径字符串集合的子集，于是我们枚举这 $n$ 个字符串依次判断是否合法即可。

判断一个字符串是否合法，那么可以找到这个字符串在树上的所有出现位置，然后用树上差分给边加一，最后判断每条边是否都有权值。于是我们对每个点记录以他为起点的所有字符串的结尾位置，这个可以哈希之后套一个 `unordered_map` 或其他哈希表记录下标，然后用 $O(n^2)$ 个 `vector` 存路径终点。那么判断一个字符串是否合法就是枚举每个点作为起点，哈希值相同的路径的结尾位置，然后树上差分，最后判断每条边是否合法。树上差分的部分每次 $O(n)$，总复杂度 $O(n^2)$，前面枚举路径的部分由于总路径数 $O(n^2)$，所以总复杂度 $O(n^2)$，然后做完了。注意树上差分中求 LCA 的部分不能带 $\log$，可以暴力跳但是加记忆化。以及一个字符串合法那么它倒过来也合法，所以也要计入答案并去重。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ull unsigned long long
using namespace std;
const int N = 2e3 + 10;
const ull MOD = 998244853;
const ull P = 131;
int n; vector<pair<int, char> > G[N];
unordered_map<ull, int> idx[N]; int len[N];
vector<int> vec[N][N]; int lca[N][N];
int S;
void DFS1(int u, int f, ull hsh) {
	if (idx[S].find(hsh) == idx[S].end()) idx[S][hsh] = ++ len[S];
	vec[S][idx[S][hsh]].push_back(u);
	for (auto [v, c] : G[u]) if (v != f) DFS1(v, u, (hsh * P + c) % MOD);
}
int depth[N], fa[N];
void DFS2(int u, int f) {
	depth[u] = depth[f] + 1, fa[u] = f; for (auto [v, c] : G[u]) if (v != f) DFS2(v, u);
}
int LCA(int u, int v) {
	if (lca[u][v] != -1) return lca[u][v];
	if (u == v) return lca[u][v] = u;
	if (depth[u] < depth[v]) swap(u, v);
	return lca[u][v] = lca[v][u] = LCA(fa[u], v);
}
int sum[N];
void DFS3(int u, int f) {
	for (auto [v, c] : G[u]) if (v != f) DFS3(v, u), sum[u] += sum[v];
}
bool res[N]; string cur; set<string> Ans;
void DFS4(int u, int f) {
	if (res[u]) {
		Ans.insert(cur); string tmp;
		for (int i = (int)cur.size() - 1; i >= 0; i --) tmp.push_back(cur[i]);
		Ans.insert(tmp);
	}
	for (auto [v, c] : G[u]) if (v != f) {
		cur.push_back(c); DFS4(v, u); cur.pop_back();
	} return ;
}
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; char c;
	for (int i = 1, u, v; i < n; i ++) {
		cin >> u >> v >> c; G[u].push_back({v, c}), G[v].push_back({u, c});
	}
	for (int i = 1; i <= n; i ++) S = i, DFS1(i, 0, 0);
	DFS2(1, 0);
	memset(lca, -1, sizeof lca);
	S = 1; while (G[S].size() > 1) ++ S;
	for (auto [hsh, o] : idx[S]) {
		for (int i = 1; i <= n; i ++) sum[i] = 0;
		for (int i = 1; i <= n; i ++) if (idx[i].find(hsh) != idx[i].end()) {
			int t = idx[i][hsh];
			for (int j : vec[i][t]) sum[i] ++, sum[j] ++, sum[LCA(i, j)] -= 2;
		}
		DFS3(1, 0); bool flag = true;
		for (int i = 2; i <= n; i ++) flag &= (sum[i] != 0);
		if (flag) res[vec[S][o][0]] = 1;
	} DFS4(S, 0);
	cout << Ans.size() << "\n";
	for (string s : Ans) cout << s << "\n";
	return 0;
}
```

---

