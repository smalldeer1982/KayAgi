# [GCJ 2021 Qualification] Reversort Engineering

## 题目描述

**注意：问题 "Reversort" 和 "Reversort Engineering" 的题目描述主体部分相同，仅最后一段不同。这两个问题可以独立解决。**

Reversort 是一种用于将**互不相同**的整数列表按升序排序的算法。该算法基于 "Reverse" 操作，每次应用该操作会反转列表中某个连续部分的顺序。

算法的伪代码如下：

```
Reversort(L):
  for i := 1 to length(L) - 1
    j := position with the minimum value in L between i and length(L), inclusive
    Reverse(L[i..j])
```

经过 $i - 1$ 次迭代后，列表的第 $1$, $2$, $\ldots$, $i - 1$ 个位置将包含 $L$ 中前 $i - 1$ 小的元素，并按升序排列。在第 $i$ 次迭代中，算法会反转从第 $i$ 个位置到当前第 $i$ 小元素所在位置的子列表。这将使第 $i$ 小的元素最终位于第 $i$ 个位置。

例如，对于一个包含 $4$ 个元素的列表，算法将执行 $3$ 次迭代。以下是处理 $L = [4, 2, 1, 3]$ 的过程：

1. $i = 1$, $j = 3 \longrightarrow L = [1, 2, 4, 3]$
2. $i = 2$, $j = 2 \longrightarrow L = [1, 2, 4, 3]$
3. $i = 3$, $j = 4 \longrightarrow L = [1, 2, 3, 4]$

在我们的架构中，执行该算法最耗时的部分是 Reverse 操作。因此，我们衡量每次迭代成本的标准仅仅是传递给 Reverse 的子列表长度，即 $j - i + 1$。整个算法的成本是每次迭代成本的总和。

在上述示例中，迭代成本依次为 $3$、$1$ 和 $2$，总成本为 $6$。

现在给定列表大小 $N$ 和目标成本 $C$。请找出一个由 $1$ 到 $N$ 的 $N$ 个不同整数组成的列表，使得对其应用 Reversort 的成本恰好为 $C$，或者判定这样的列表不存在。


## 说明/提示

**样例解释**

样例 #1 已在题目描述中说明。

在样例 #2 中，算法在所提出的输出上仅运行一次迭代。在该次迭代中，reverse 操作应用于长度为 1 的子列表，因此其成本为 1。

在样例 #3 中，第一次迭代反转了整个列表，成本为 7。此后列表已排序，但仍有 5 次迭代，每次成本为 1。另一个有效输出是 7 5 4 3 2 1 6。对于该输出，第一次迭代的成本为 6，最后一次的成本为 2，其余每次的成本为 1。

在样例 #4 中，Reversort 必然执行 6 次迭代，每次迭代的成本至少为 1，因此无法达到要求的低总成本。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{C} \leq 1000$。

**测试集 1（7 分，可见判定结果）**

- $2 \leq \mathbf{N} \leq 7$。

**测试集 2（11 分，可见判定结果）**

- $2 \leq \mathbf{N} \leq 100$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4 6
2 1
7 12
7 2
2 1000```

### 输出

```
Case #1: 4 2 1 3
Case #2: 1 2
Case #3: 7 6 5 4 3 2 1
Case #4: IMPOSSIBLE
Case #5: IMPOSSIBLE```

# 题解

## 作者：Sheep_YCH (赞：1)

## 洛谷 P13023

[题目传送门](https://www.luogu.com.cn/problem/P13023)

### 题目大意

题目描述的相当清楚了，如果不理解，可以参考题目中给出的例子，并在草稿纸上画图帮助理解。

### 题目分析

我们注意到， Reversort 的过程和每个元素的绝对大小无关，只与每个元素之间的相对大小有关，因此，我们可以用类似递推的思想来解决这道题目。

记 $S(N,C)$ 为一个长度为 $N$，Reversort 的代价为 $C$ 的排列。

如果有 $S(N-1, C-1)$，想要得到 $S(N, C)$，只需要在最前面添加一个更小的数字即可。

如果有 $S(N-1, C-2)$，想要得到 $S(N, C)$，需要把更小的数字插入到第一个元素后面。

如果有 $S(N-1, C-3)$，想要得到 $S(N, C)$，需要把前两个元素翻转，然后把更小的数字插入到第二个元素后面。

综上，我们不难发现：如果有 $S(N-1, C-x)$，想要得到 $S(N, C)$，需要把前 $x-1$ 个元素翻转，然后把更小的数字插入到第 $x-1$ 个元素后面，作为第 $x$ 个元素，其中 $x$ 的取值范围是 $[1, N]$。

对于长度为 $N$ 的排列，最小的 $C$ 是 $N-1$，最大的 $C$ 是 $\sum_{i=2}^{N} i$，显然在其中的值皆可以被取到。
也就是，问题的本质相当于构造一个长度为 $N$ 的数组，且第一个元素固定为 $0$，第 $i$ 个元素的最小值为 $1$，最大值为 $i$，使得它们的和等于 $C$。
其等价于构造一个长度为 $N$ 的数组，且第 $i$ 个元素的最小值为 $0$，最大值为 $i-1$，使它们的和等于 $C - (N-1)$。

得到这个差值数组后，按照上面的方法构造构建 $S(N, C)$ 即可。

### Code

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
const int INF = 2e9 + 5;

int n, c, S[MAXN];
vector<int> Ans;

void Solve() {
	cin >> n >> c;
	if(c > n * (n + 1) / 2 - 1 || c < n - 1) {
		cout << "IMPOSSIBLE";
		return ;
	} // 如果比最小值小或者比最大值大，那么不符合条件
	S[1] = 0; int now = c - (n - 1);
	for(int i = 2; i <= n; i ++) {
		S[i] = min(i - 1, now);
		now -= S[i];
		S[i] ++; // 不要忘记+1
	}
	Ans.clear();
	Ans.push_back(n);
	Ans.push_back(n); // 我习惯下标从1开始，故插入两个n
	for(int i = 2; i <= n; i ++) {
		reverse(Ans.begin() + 1, Ans.begin() + S[i]);
		Ans.insert(Ans.begin() + S[i], n - i + 1); // 从大到小挨个往里插入
	}
	for(int i = 1; i <= n; i ++) cout << Ans[i] << " ";
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; cin >> T;
	for(int Case = 1; Case <= T; Case ++) {
		cout << "Case #" << Case << ": ";
		Solve();
		cout << "\n";
	}
	
	return 0;

}
```

---

