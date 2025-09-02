# [GCJ 2022 Qualification] Chain Reactions

## 题目描述

Wile 独自生活在沙漠中，他通过建造复杂的连锁反应机器来自娱自乐。每台机器由 $\mathbf{N}$ 个模块组成，编号为 $1, 2, \ldots, \mathbf{N}$。每个模块会指向一个编号比它小的模块，如果没有可指向的模块，则指向虚空。

没有被任何其他模块指向的模块称为**启动器**。Wile 可以手动触发启动器。当一个模块被触发时，它会触发它所指向的模块（如果有的话），后者可能继续触发第三个模块（如果它指向某个模块），依此类推，直到链条到达虚空或已经触发过的模块为止。这被称为**连锁反应**。

每个 $\mathbf{N}$ 个模块都有一个乐趣值 $\mathbf{F}_i$。Wile 从一次连锁反应中获得的乐趣是该连锁反应中所有被触发模块的乐趣值的最大值。Wile 将按某种顺序依次触发每个启动器模块一次。整个过程中 Wile 获得的总乐趣是每次连锁反应所获乐趣的总和。

例如，假设 Wile 有 4 个模块，乐趣值分别为 $\mathbf{F}_1 = 60$、$\mathbf{F}_2 = 20$、$\mathbf{F}_3 = 40$ 和 $\mathbf{F}_4 = 50$，模块 1 指向虚空，模块 2 和 3 指向模块 1，模块 4 指向模块 2。此时有两个启动器（3 和 4），Wile 需要按某种顺序触发它们。

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/v8jwu5d8)

如上图所示，如果 Wile 先手动触发模块 4，模块 4、2 和 1 会在同一次连锁反应中被触发，乐趣值为 $\max(50, 20, 60) = 60$。接着，当 Wile 触发模块 3 时，模块 3 会单独被触发（模块 1 无法再次触发），乐趣值为 40，整个过程的总乐趣为 $60 + 40 = 100$。

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/94l7nhpi)

然而，如果 Wile 先手动触发模块 3，模块 3 和 1 会在同一次连锁反应中被触发，乐趣值为 $\max(40, 60) = 60$。接着，当 Wile 触发模块 4 时，模块 4 和 2 会在同一次连锁反应中被触发，乐趣值为 $\max(50, 20) = 50$，整个过程的总乐趣为 $60 + 50 = 110$。

给定模块的乐趣值和指向关系，计算 Wile 在最优触发顺序下能获得的最大总乐趣。

## 说明/提示

**样例解释**

样例 #1 是题目描述中解释的案例。

在样例 #2 中，有 $4$ 个启动器（模块 $2$ 到 $5$），因此有 $4$ 次连锁反应。按顺序 $3, 5, 4, 2$ 触发它们，得到的连锁反应乐趣值分别为 $3, 5, 4, 2$，总乐趣为 $14$。注意我们是在对输入中的四个最大乐趣值求和，因此无法获得更大的值。

在样例 #3 中，$5$ 个启动器的最优触发顺序是 $4, 5, 7, 6, 8$。

**限制条件**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{F}_i \leq 10^9$。
- $0 \leq \mathbf{P}_i \leq i - 1$，对所有 $i$ 成立。

**测试集 1（10 分，可见评测结果）**

- 时间限制：5 秒。
- $1 \leq \mathbf{N} \leq 10$。

**测试集 2（12 分，可见评测结果）**

- 时间限制：5 秒。
- $1 \leq \mathbf{N} \leq 1000$。

**测试集 3（5 分，隐藏评测结果）**

- 时间限制：10 秒。
- $1 \leq \mathbf{N} \leq 100000$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
4
60 20 40 50
0 1 1 2
5
3 2 1 4 5
0 1 1 1 0
8
100 100 100 90 80 100 90 100
0 1 2 1 2 3 1 3```

### 输出

```
Case #1: 110
Case #2: 14
Case #3: 490```

# 题解

## 作者：Sheep_YCH (赞：3)

## 洛谷 P12982

[题目传送门](https://www.luogu.com.cn/problem/P12982)

~~这么好的题竟然没有人写题解，赶紧来发一篇，望通过qwq~~。

## 题目大意

原题目描述的已经很清晰了（没想到竟然还有动图，好评），注意每个点只能走一次即可。

## 题目分析

这道题拿到手一看：这不是典型的拓扑排序嘛！但仔细观察可以发现，每个点的只能够走一次，嘶~

想了想，发现对于一个非叶子结点 $u$，只能选择一个儿子节点连接 $u$，其他的儿子节点所构成的链就被阻断了，不能够继续向上走了。选择哪个儿子节点连接 $u$ 呢？显然，每条链对总乐趣的贡献是链上的点的点权（乐趣值）中的最大值。而我们知道了 $u$ 的点权为 $F[u]$，选择一个儿子节点 $v$ 连接后，设 $v$ 所在链的最大乐趣值为 $Minimax[v]$，则 $Minimax[u]=\max(Minimax[v],F[u])$。设 $DP[u]$ 为以 $u$ 为根的子树中，不考虑 $u$ 所在链时的最大总乐趣值，即不与 $u$ 连接的每个儿子节点所在链的最大乐趣值的总和。那么以 $u$ 为根的子树的总乐趣就是 $Minimax[u] + DP[u]$。贪心的想，我们选择对于所有儿子节点，我们选择 $v$ 与 $u$ 连接，使 $Minimax[v]$ 是儿子节点当中最小的——这样就保证了 $DP[u]$ 最大且 $Minimax[u]$ 最优（可以仔细想想为什么）。

由此，我们可以发现这是一个简单的**动态规划**题目。遍历时，从叶子节点向上遍历即可。

1. **动态规划状态设计**：
   - $DP[u]$：以 $u$ 为根的子树中，不考虑 $u$ 所在链时的最大总乐趣值。
   - $Minimax[u]$：经过 $u$ 的链中的最大乐趣值。
2. **状态转移**：
   - 对于叶子节点：$DP[u] = 0$（都没有儿子节点所以是 $0$ ），$Minimax[u]=F[u]$。
   - 对于非叶子节点：
     - 计算所有子节点的 $DP[v]+Minimax[v]$ 之和，记为 $\operatorname{Base}$。
     - 选择最小的 $Minimax[v]$，记为 $\operatorname{Minval}$。
     - 状态转移：$DP[u]=\operatorname{Base}-\operatorname{Minval}$，$Minimax[u]=\max(\operatorname{Minval},F[u])$。

## Code

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <queue>
#include <stack>
#define ll long long
using namespace std;
const int MAXN = 1e6 + 5;
const ll INF = 1e18 + 5;

int n, P[MAXN], in[MAXN], Parent[MAXN];
vector<int> E[MAXN];
vector<int> Root;
ll DP[MAXN], Minimax[MAXN], F[MAXN];

void Clear() {
	for(int i = 1; i <= n; i ++) DP[i] = Minimax[i] = F[i] = 0, E[i].clear();
	for(int i = 1; i <= n; i ++) P[i] = in[i] = 0, Parent[i] = -1;
	Root.clear();
	return ;
}

ll Solve() {
	cin >> n;
	Clear();
	for(int i = 1; i <= n; i ++) cin >> F[i];
	for(int i = 1; i <= n; i ++) {
		cin >> P[i];
		if(!P[i]) Parent[i] = -1, Root.push_back(i);
		else {
			E[P[i]].push_back(i);
			in[P[i]] ++;
			Parent[i] = P[i];
		}
	}
	queue<int> Q;
	for(int i = 1; i <= n; i ++) {
		if(E[i].empty()) Q.push(i);
	}
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if(E[u].empty()) {
			DP[u] = 0; Minimax[u] = F[u]; 
		}
		else {
			ll Base = 0, Min_val = INF;
			for(auto v : E[u]) {
				Base += 1ll * (DP[v] + Minimax[v]);
				if(Minimax[v] < Min_val) Min_val = Minimax[v];
			}
			DP[u] = Base - Min_val;
			Minimax[u] = max(F[u], Min_val);
		}
		
		if(Parent[u] != -1) {
			in[Parent[u]] --;
			if(!in[Parent[u]]) Q.push(Parent[u]);
		}
	}
	ll ans = 0;
	for(auto root : Root) {
		ans += 1ll * (DP[root] + Minimax[root]);
	}
	return ans;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; cin >> T;
	for(int Case = 1; Case <= T; Case ++) {
		cout << "Case #" << Case << ": " << Solve() << "\n";
	}
	
	return 0;

}

```

### 注意点

$DP[u]$ 是所有子模块的 $DP[v] + Minimax[v]$ 之和减去最小的 $Minimax[v]$。这里的减法是因为最小的$Minimax[v]$ 对应的子链会被延伸到当前模块 $u$，因此其贡献会被包含在 $Minimax[u]$ 中，不是独立的链，所以要减去防止重复计算。

---

