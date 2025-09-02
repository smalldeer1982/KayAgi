# Ordering T-Shirts

## 题目描述

在一场比赛中，有$P$位选手参加比赛。在最后的结果中排名最靠前的$C(C \leq P)$位选手会得到由主办方赠送的一件衬衫。主办方决定在比赛开始前将必要的衬衫做好，但是他们不知道会有哪些选手成为前$C$名。

主办方已经统计好了$P$位选手希望的衬衫尺码。衬衫尺码共有$N$种，编号$1$到$N$。一些选手希望获得某一固定尺码的衬衫，而一些选手则希望获得某两个编号相邻的尺码中的一个尺码的衬衫。

现在请计算出主办方最少需要多少衬衫，使得无论哪$C$位选手最靠前，都存在一种分配方案使得所有人都能获得他想要的尺码的衬衫。

## 样例 #1

### 输入

```
2 200
100 250 100
```

### 输出

```
200
```

## 样例 #2

### 输入

```
4 160
88 69 62 29 58 52 44
```

### 输出

```
314
```

# 题解

## 作者：Leasier (赞：3)

首先不要把题看错了：**对于那些有两个选项的选手，你可以分别决定他们选择哪个选项**。

设我们最终买了 $cnt_i$ 件衬衫 $i$，我们尝试给出一组 $cnt_i$ 合法的判定条件。

注意到衬衫的分配本质上是一个二分图匹配问题：

- $S \to^C S'$，表示一共最多有 $C$ 个选手。
- $S' \to^{c_i} i$，表示只想要衬衫 $i$ 的选手。
- $S' \to^{c_i} (i, i + 1)$，表示接受衬衫 $i, i + 1$ 的选手。
- $i' \to^{cnt_i} T$，表示有 $cnt_i$ 件衬衫 $i$。
- $i \to^{+ \infty} i'$，表示只想要衬衫 $i$ 的选手选择衬衫 $i$。
- $(i, i + 1) \to^{+ \infty} i', (i + 1)'$，表示接受衬衫 $i, i + 1$ 的选手选择衬衫 $i$ 或 $i + 1$。
- 若有完美匹配则该解合法。

考虑霍尔定理，可得：

- $\forall 1 \leq l \leq r \leq n$，$\min(\displaystyle\sum_{i = 2l - 1}^{2r - 1} c_i, C) \leq \sum_{i = l}^r cnt_i$。

现在我们尝试来构造一组 $\displaystyle\sum_{i = 1}^n cnt_i$ 最小的解。

考虑顺序构造，当我们已知 $cnt_{1 \sim i - 1}$ 的最优值，我们对 $cnt_i$ 的限制为：

- $\forall 1 \leq j \leq i$，$cnt_i \geq \min(\displaystyle\sum_{k = 2j - 1}^{2i - 1} c_k, C) - \displaystyle\sum_{k = j}^{i - 1} cnt_k$。

于是 $(cnt_i)_{\min}$ 为右式最小值，单调队列维护即可。

~~正确性证明感性理解一下就行（~~

时间复杂度为 $O(n)$。

代码：
```cpp
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

ll sumc[400007], sum_cnt[200007];
deque<int> q;

inline ll calc(int x){
	return sum_cnt[x - 1] - sumc[x * 2 - 2];
}

int main(){
	int n, m;
	ll C;
	cin >> n >> C;
	m = n * 2 - 1;
	for (int i = 1; i <= m; i++){
		int c;
		cin >> c;
		sumc[i] = sumc[i - 1] + c;
	}
	for (int i = 1, j = 1; i <= n; i++){
		ll cur = calc(i), cnt = 0;
		while (j <= i && sumc[i * 2 - 1] - sumc[j * 2 - 2] >= C) j++;
		while (!q.empty() && calc(q.back()) < cur) q.pop_back();
		q.push_back(i);
		while (!q.empty() && q.front() < j) q.pop_front();
		if (j > 1) cnt = max(cnt, C - (sum_cnt[i - 1] - sum_cnt[j - 2]));
		if (!q.empty()){
			int head = q.front();
			cnt = max(cnt, (sumc[i * 2 - 1] - sumc[head * 2 - 2]) - (sum_cnt[i - 1] - sum_cnt[head - 1]));
		}
		sum_cnt[i] = sum_cnt[i - 1] + cnt;
	}
	cout << sum_cnt[n];
	return 0;
}
```

---

