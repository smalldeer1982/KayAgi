# [POI 2006] EST-Aesthetic Text

## 题目描述

让我们考虑一个由 $n$ 个单词组成的文本，这些单词从 1 到 $n$ 编号。我们用一个数列 $(a_1, a_2, \ldots, a_{k-1})$ 来表示将其分解为 $k$ 行的任意方式，使得编号从 1 到 $a_1$ 的单词在第一行，编号从 $a_1 + 1$ 到 $a_2$ 的单词在第二行，依此类推，最后编号从 $a_{k-1} + 1$ 到 $n$ 的单词在最后一行，即第 $k$ 行。

每个单词都有一定的长度（以字符数衡量）。令 $length(x)$ 表示第 $x$ 个单词的长度。此外，行中的每两个相邻单词之间用一个字符宽度的空格隔开。行的长度被定义为该行中单词长度的总和，加上它们之间的空格数。令 $line(w)$ 表示第 $w$ 行的长度。即，如果第 $w$ 行包含编号从 $i$ 到 $j$ 的单词（包括 $i$ 和 $j$），其长度为：

```cpp
XXXX (第 1 行)
XXX XX (第 2 行)
XXXXX (第 3 行)
```

$$line(w) = length(i) + \ldots + length(j) + (j-i)$$

例如，考虑一个由 4 个单词组成的文本，其长度分别为 4, 3, 2 和 5，以及将其分解为 3 行的方式 (1,3)。那么第一行的长度是 4，第二行是 6，第三行是 5：

我们称数值

$$|line(1) - line(2)| + \ldots + |line(k-1) - line(k)|$$

为将给定文本分解为 $k$ 行的美学系数。特别地，如果分解只有一行，其美学系数为 0。

不言而喻，系数越小，分解越美观。我们只考虑那些没有行长度超过某个常数 $m$ 的分解。在所有这样的分解中，我们寻找最美观的，即美学系数最小的分解。上述示例分解的系数是 3，这正是 $m=6$ 和 $m=7$ 时美学系数的最小值。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 4
4 3 2 5```

### 输出

```
3```

# 题解

## 作者：Alex_Wei (赞：2)

> *[P3446 [POI2006]EST-Aesthetic Text](https://www.luogu.com.cn/problem/P3446)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

还算有趣的动态规划。遇到这种区间划分题首先考虑 DP，设 $f_{i,j}$ 表示以第 $i$ 个单词结尾为一行，且这一行长度为 $j$ 的最小答案，那么有 $f_{i,j}=\min_{\\k=1}^m(f_{p,k}+|j-k|)$，其中 $p$ 满足 $i-p-1+\sum_{\\q=p+1}^i l_q=j$。直接转移的复杂度为 $\mathcal{O}(n^2m)$（枚举 $p$ 算出对应的 $j$）。

不过我们注意到有很多 $j$ 都是空值，说明这个定义有些劣。不妨修改定义，设 $f_{i,j}$ 表示最后一行为 $i-j+1\sim i$ 的答案，再设 $L_{i,j}$ 表示 $j-1+\sum_{\\p\in [i-j+1,i]}l_p$ 即 $i-j+1\sim i$ 组成一行的长度，那么有：
$$
f_{i,j}=\min_{p\in[1,i-j]}(f_{i-j,p}+|L_{i-j,p}-L_{i,j}|)
$$
此时时间复杂度优化为 $\mathcal{O}(n^3)$，但仍无法接受。接下来使用拆绝对值的技巧，即维护 $pre_{i,j}$ 表示 $f_{i,j}-L_{i,j}$，$suf_{i,j}$ 表示 $f_{i,j}+L_{i,j}$，那么对于 $f_{i,j}$ 对应的转移位置 $i-j$，我们只需找到最后一个位置 $p$ 使得 $L_{i-j,p}\leq L_{i,j}$，那么 $f_{i,j}$ 可以由 $pre_{i,p}$ 关于 $p$ 的前缀 $\min$ 加上 $L_{i,j}$，以及 $suf_{i,p+1}$ 关于 $p$ 的后缀 $\min$ 减去 $L_{i,j}$ 得到。

又因为固定 $i-j$ 时，$L_{i,j}$ 随着 $i$ 增大而增大，这说明 $f_{i+k,j+k}$ 从 $i-j$ 处转移时的 $p$ 随着 $k$ 增加而递增，因此对每个位置 $i$ 在求出 $f_{i,j}$ 维护一个转移指针即可做到平方。

```cpp
const int N = 2e3 + 5;
int n, m, ans = 2e9, L[N], pos[N], tot[N], f[N][N];
int len[N][N], pre[N][N], suf[N][N];
int main(){
	cin >> m >> n;
	for(int i = 1; i <= n; i++) {
		cin >> L[i], L[i] += L[i - 1];
		for(int j = i - 1; ~j; j--) {
			int cur = i - j - 1 + L[i] - L[j];
			if(cur > m) break; tot[i]++;
			if(!j) f[i][tot[i]] = 0;
			else {
				f[i][tot[i]] = 2e9;
				while(pos[j] < tot[j] && len[j][pos[j] + 1] <= cur) pos[j]++;
				if(pos[j]) cmin(f[i][tot[i]], pre[j][pos[j]] + cur);
				if(pos[j] < tot[j]) cmin(f[i][tot[i]], suf[j][pos[j] + 1] - cur);
			} len[i][tot[i]] = cur;
		} pre[i][0] = suf[i][tot[i] + 1] = 2e9;
		for(int j = 1; j <= tot[i]; j++) pre[i][j] = min(pre[i][j - 1], f[i][j] - len[i][j]);
		for(int j = tot[i]; j; j--) suf[i][j] = min(suf[i][j + 1], f[i][j] + len[i][j]);
		if(i == n) for(int j = 1; j <= tot[n]; j++) cmin(ans, f[i][j]);
	} cout << ans << endl;
	return 0;
}
```

---

