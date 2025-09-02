# 题目信息

# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2
```

### 输出

```
1
1 
```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8
```

### 输出

```
3
1 3 2 
```

# AI分析结果

### 题目内容重写（中文）

#### 神秘的礼物

**题目描述**

Peter决定给他的澳大利亚朋友送一张生日贺卡，为了让礼物更加神秘，他决定制作一个信封链。这里的链是指一个信封序列 $ A $ = { $ a_{1},a_{2},...,a_{n} $ }，其中第 $ i $ 个信封的宽度和高度分别严格大于第 $ (i-1) $ 个信封的宽度和高度。链的大小是指链中信封的数量。

Peter希望从他拥有的信封中制作一个最大尺寸的链，并且这个链要能够放入一张贺卡。如果贺卡的宽度和高度分别小于链中最小的信封的宽度和高度，那么贺卡就可以放入链中。不允许旋转贺卡和信封。

Peter有很多信封，但时间很少，这个艰巨的任务交给你来完成。

**样例 #1**

输入：
```
2 1 1
2 2
2 2
```

输出：
```
1
1 
```

**样例 #2**

输入：
```
3 3 3
5 4
12 11
9 8
```

输出：
```
3
1 3 2 
```

---

### 题解综合分析与结论

本题的核心是求一个二维严格上升子序列（LIS），并且需要输出具体的序列。题解中主要采用了动态规划（DP）的思路，部分题解还结合了排序和记忆化搜索等优化手段。以下是各题解的要点总结：

1. **动态规划**：大多数题解都采用了DP的思路，状态转移方程为 $f_i = \max\{f_j+1 | j<i, w_j<w_i, h_j<h_i\}$，表示以第 $i$ 个信封结尾的最长链的长度。
2. **排序优化**：部分题解通过按宽度或高度排序，简化了DP的过程，避免了重复计算。
3. **记忆化搜索**：个别题解使用了记忆化搜索来避免重复计算，提高了效率。
4. **输出序列**：通过记录前驱节点或使用链表结构，题解能够输出具体的信封序列。

### 评分较高的题解

#### 题解1：Juanzhang (4星)

**关键亮点**：
- 使用了记忆化搜索，避免了重复计算，时间复杂度与递推相当。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码**：
```cpp
int dfs(int x) {
	if (~dp[x]) return dp[x];
	dp[x] = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].fir.fir > a[x].fir.fir && a[i].fir.sec > a[x].fir.sec && dp[x] < dfs(i)) {
			dp[x] = dp[i], pre[x] = i;
		}
	}
	return ++dp[x];
}
```

#### 题解2：Plozia (4星)

**关键亮点**：
- 详细解释了二维LIS的处理方法，特别是排序后的状态转移方程。
- 代码结构清晰，注释详细，适合进阶学习。

**核心代码**：
```cpp
for (int i = 1; i <= cnt; ++i) {
	f[i] = 1;
	for(int j = 1; j < i; ++j) {
		if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i]) {
			f[i] = f[j] + 1;
			las[i] = j;
		}
	}
}
```

#### 题解3：CaiXY06 (4星)

**关键亮点**：
- 通过排序简化了DP过程，代码简洁高效。
- 使用了前驱数组记录路径，便于输出序列。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
	f[i] = 1;
	for (int j = 1; j < i; j++)
		if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i]) {
			f[i] = f[j] + 1;
			pre[i] = j;
		}
}
```

### 最优关键思路与技巧

1. **排序优化**：先按宽度或高度排序，简化DP过程，避免重复计算。
2. **记忆化搜索**：通过记忆化搜索减少重复计算，提高效率。
3. **前驱记录**：使用前驱数组或链表结构记录路径，便于输出具体序列。

### 可拓展之处

本题可以拓展到更高维度的LIS问题，或者结合其他优化算法如二分查找来进一步优化时间复杂度。类似的问题还包括多维偏序问题、最长公共子序列等。

### 推荐题目

1. [P3902 递增](https://www.luogu.org/problem/P3902) - 一维LIS问题，适合初学者练习。
2. [P1020 导弹拦截](https://www.luogu.org/problem/P1020) - 二维LIS问题，与本题类似。
3. [P1091 合唱队形](https://www.luogu.org/problem/P1091) - 双向LIS问题，适合进阶练习。

### 个人心得摘录

- **Juanzhang**：记忆化搜索可以避免计算不需要的部分，时间复杂度与递推相当。
- **Plozia**：排序后只需要考虑高度的严格上升，简化了状态转移方程。
- **CaiXY06**：通过前驱数组记录路径，便于递归输出序列。

这些心得展示了如何通过优化算法和数据结构来提高代码的效率和可读性。

---
处理用时：46.49秒