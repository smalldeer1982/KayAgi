# 题目信息

# Arrays Sum

## 题目描述

You are given a non-decreasing array of non-negative integers $ a_1, a_2, \ldots, a_n $ . Also you are given a positive integer $ k $ .

You want to find $ m $ non-decreasing arrays of non-negative integers $ b_1, b_2, \ldots, b_m $ , such that:

- The size of $ b_i $ is equal to $ n $ for all $ 1 \leq i \leq m $ .
- For all $ 1 \leq j \leq n $ , $ a_j = b_{1, j} + b_{2, j} + \ldots + b_{m, j} $ . In the other word, array $ a $ is the sum of arrays $ b_i $ .
- The number of different elements in the array $ b_i $ is at most $ k $ for all $ 1 \leq i \leq m $ .

Find the minimum possible value of $ m $ , or report that there is no possible $ m $ .

## 说明/提示

In the first test case, there is no possible $ m $ , because all elements of all arrays should be equal to $ 0 $ . But in this case, it is impossible to get $ a_4 = 1 $ as the sum of zeros.

In the second test case, we can take $ b_1 = [3, 3, 3] $ . $ 1 $ is the smallest possible value of $ m $ .

In the third test case, we can take $ b_1 = [0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2] $ and $ b_2 = [0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2] $ . It's easy to see, that $ a_i = b_{1, i} + b_{2, i} $ for all $ i $ and the number of different elements in $ b_1 $ and in $ b_2 $ is equal to $ 3 $ (so it is at most $ 3 $ ). It can be proven that $ 2 $ is the smallest possible value of $ m $ .

## 样例 #1

### 输入

```
6
4 1
0 0 0 1
3 1
3 3 3
11 3
0 1 2 2 3 3 3 4 4 4 4
5 3
1 2 3 4 5
9 4
2 2 3 5 7 11 13 13 17
10 7
0 1 1 2 3 3 4 5 5 6```

### 输出

```
-1
1
2
2
2
1```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个非递减的非负整数数组 $a_1, a_2, \ldots, a_n$，以及一个正整数 $k$。

你需要找到 $m$ 个非递减的非负整数数组 $b_1, b_2, \ldots, b_m$，满足以下条件：

1. 每个 $b_i$ 的长度都等于 $n$。
2. 对于所有 $1 \leq j \leq n$，$a_j = b_{1, j} + b_{2, j} + \ldots + b_{m, j}$。换句话说，数组 $a$ 是数组 $b_i$ 的和。
3. 每个数组 $b_i$ 中不同元素的个数不超过 $k$。

求最小的 $m$，或者报告不存在这样的 $m$。

#### 说明/提示

- 在第一个测试用例中，不存在可能的 $m$，因为所有数组的元素都应为 $0$，但这样无法得到 $a_4 = 1$。
- 在第二个测试用例中，可以取 $b_1 = [3, 3, 3]$，此时 $m=1$ 是最小值。
- 在第三个测试用例中，可以取 $b_1 = [0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2]$ 和 $b_2 = [0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2]$。此时 $m=2$ 是最小值。

#### 样例输入

```
6
4 1
0 0 0 1
3 1
3 3 3
11 3
0 1 2 2 3 3 3 4 4 4 4
5 3
1 2 3 4 5
9 4
2 2 3 5 7 11 13 13 17
10 7
0 1 1 2 3 3 4 5 5 6
```

#### 样例输出

```
-1
1
2
2
2
1
```

### 算法分类

贪心

### 题解分析与结论

该题的核心思路是通过贪心策略，尽可能多地利用每个数组 $b_i$ 的不同元素个数限制 $k$，从而最小化 $m$。具体来说，可以通过以下步骤实现：

1. **特判 $k=1$ 的情况**：如果 $k=1$，则所有 $b_i$ 必须完全相同，且 $a$ 也必须完全相同，否则无解。
2. **计算 $a$ 中不同元素的个数 $cnt$**：如果 $cnt \leq k$，则只需要一个数组 $b_1$ 即可。
3. **贪心策略**：如果 $cnt > k$，则每次尽可能多地利用 $k$ 个不同元素，将 $a$ 中的元素逐步减少，直到 $a$ 中所有元素被消除。每次操作可以消除 $k-1$ 个不同元素（因为需要保留一个元素用于后续操作）。

### 所选题解

#### 题解1：作者：7KByte (赞：2)

**星级：4星**

**关键亮点**：
- 通过贪心策略，直接计算所需的最小 $m$，思路清晰。
- 代码简洁，逻辑明确，易于理解。

**核心代码**：
```cpp
int sum = 0;
rep(i,1,n) if(i==1||a[i]!=a[i-1]) sum++;
if(k==1&&sum!=1) puts("-1");
else if(k==1) puts("1"); 
else {
    int now = max(0, sum - k);
    if(now) printf("%d\n", 1 + (now - 1) / (k - 1) + 1);
    else printf("%d\n", 1);
}
```

#### 题解2：作者：s_r_f (赞：0)

**星级：4星**

**关键亮点**：
- 通过差分数组的思路，推导出 $m$ 的计算公式，思路新颖。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
int cnt = 1; tot -= k;
while (tot > 0) tot -= k - 1, ++cnt;
cout << cnt << '\n';
```

#### 题解3：作者：Little09 (赞：0)

**星级：4星**

**关键亮点**：
- 通过贪心策略，直接计算所需的最小 $m$，思路清晰。
- 代码简洁，逻辑明确，易于理解。

**核心代码**：
```cpp
int cnt = 1;
for (int i = 2; i <= n; i++) if (a[i] != a[i - 1]) cnt++;
int ans = (cnt + k - 3) / (k - 1);
if (ans == 0) ans++;
cout << ans << endl;
```

### 最优关键思路或技巧

1. **贪心策略**：通过每次尽可能多地利用 $k$ 个不同元素，逐步减少 $a$ 中不同元素的个数，从而最小化 $m$。
2. **特判 $k=1$ 的情况**：当 $k=1$ 时，$a$ 必须完全一致，否则无解。
3. **差分数组思路**：通过差分数组的思路，推导出 $m$ 的计算公式，进一步优化了计算过程。

### 可拓展之处

该题的贪心策略可以推广到其他类似的问题中，例如在给定限制条件下，如何最小化资源的使用量。类似的问题可以考察如何通过贪心策略优化资源分配或任务调度。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：42.66秒