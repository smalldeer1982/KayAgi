# 题目信息

# Array Painting

## 题目描述

You are given an array of $ n $ integers, where each integer is either $ 0 $ , $ 1 $ , or $ 2 $ . Initially, each element of the array is blue.

Your goal is to paint each element of the array red. In order to do so, you can perform operations of two types:

- pay one coin to choose a blue element and paint it red;
- choose a red element which is not equal to $ 0 $ and a blue element adjacent to it, decrease the chosen red element by $ 1 $ , and paint the chosen blue element red.

What is the minimum number of coins you have to spend to achieve your goal?

## 说明/提示

In the first example, you can paint all elements red with having to spend only one coin as follows:

1. paint the $ 2 $ -nd element red by spending one coin;
2. decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 1 $ -st element red;
3. decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 3 $ -rd element red.

In the second example, you can paint all elements red spending only two coins as follows:

1. paint the $ 4 $ -th element red by spending one coin;
2. decrease the $ 4 $ -th element by $ 1 $ and paint the $ 3 $ -rd element red;
3. paint the $ 1 $ -st element red by spending one coin;
4. decrease the $ 3 $ -rd element by $ 1 $ and paint the $ 2 $ -nd element red.

## 样例 #1

### 输入

```
3
0 2 0```

### 输出

```
1```

## 样例 #2

### 输入

```
4
0 0 1 1```

### 输出

```
2```

## 样例 #3

### 输入

```
7
0 1 0 0 1 0 2```

### 输出

```
4```

# AI分析结果

### 中文重写题目内容

# 数组染色

## 题目描述

给定一个包含 $n$ 个整数的数组，每个整数的值为 $0$、$1$ 或 $2$。初始时，数组中的每个元素都是蓝色的。

你的目标是将数组中的每个元素染成红色。为此，你可以执行以下两种操作：

- 花费一枚硬币，选择一个蓝色元素并将其染成红色；
- 选择一个不等于 $0$ 的红色元素和一个与之相邻的蓝色元素，将选中的红色元素减 $1$，并将选中的蓝色元素染成红色。

问：要实现目标，最少需要花费多少枚硬币？

## 说明/提示

在第一个样例中，你可以只花费一枚硬币将所有元素染成红色，具体操作如下：

1. 花费一枚硬币将第 $2$ 个元素染成红色；
2. 将第 $2$ 个元素减 $1$，并将第 $1$ 个元素染成红色；
3. 将第 $2$ 个元素减 $1$，并将第 $3$ 个元素染成红色。

在第二个样例中，你可以只花费两枚硬币将所有元素染成红色，具体操作如下：

1. 花费一枚硬币将第 $4$ 个元素染成红色；
2. 将第 $4$ 个元素减 $1$，并将第 $3$ 个元素染成红色；
3. 花费一枚硬币将第 $1$ 个元素染成红色；
4. 将第 $3$ 个元素减 $1$，并将第 $2$ 个元素染成红色。

## 样例 #1

### 输入

```
3
0 2 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
0 0 1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
0 1 0 0 1 0 2
```

### 输出

```
4
```

### 算法分类
贪心

### 题解分析与结论

本题的核心思路是通过贪心策略最小化硬币的使用。大多数题解都采用了类似的思路：优先处理值为 $2$ 的元素，因为它们可以影响更多的相邻元素，然后再处理值为 $1$ 的元素，最后处理值为 $0$ 的元素。

### 所选高分题解

#### 1. 作者：Register_int (赞：24)
- **星级**: 5星
- **关键亮点**: 使用动态规划的思路，简洁高效，时间复杂度为 $O(n)$。
- **核心代码**:
```cpp
for (int i = 2, j; i <= n; i++) {
    dp[i][a[i]] = min({ dp[i - 1][0] + 1, dp[i - 1][1], dp[i - 1][2] });
    if (a[i]) dp[i][a[i] - 1] = min({ dp[pre[i] - 1][0], dp[pre[i] - 1][1], dp[pre[i] - 1][2] }) + 1;
}
```
- **实现思想**: 通过预处理每个位置前最后出现的 $0$ 的位置，简化了状态转移方程。

#### 2. 作者：saixingzhe (赞：7)
- **星级**: 4星
- **关键亮点**: 通过分段处理连续的非 $0$ 元素，优先处理含有 $2$ 的段，再处理只含 $1$ 的段，最后处理 $0$。
- **核心代码**:
```cpp
for (int i = 1; i <= n; i++) {
    if (a[i] == 2 && !t[i]) {
        ans++;
        t[i] = 1;
        int j = i, d = i;
        while (a[(++j)]) t[j] = 1;
        while (a[(--d)]) t[d] = 1;
        t[d] = 1;
        t[j] = 1;
    }
}
```
- **实现思想**: 通过标记数组记录已经染色的元素，避免重复计算。

#### 3. 作者：__ex (赞：4)
- **星级**: 4星
- **关键亮点**: 通过贪心策略，优先处理含有 $2$ 的连续段，再处理只含 $1$ 的段，最后处理 $0$。
- **核心代码**:
```cpp
if (f) vis[i - cnt - 1] = 1, vis[i] = 1;
else if (i - cnt - 1 && !vis[i - cnt - 1]) vis[i - cnt - 1] = 1;
else vis[i] = 1;
```
- **实现思想**: 通过标记数组记录已经染色的元素，确保每个元素只被染色一次。

### 最优关键思路与技巧
1. **优先处理高价值元素**: 优先处理值为 $2$ 的元素，因为它们可以影响更多的相邻元素。
2. **分段处理**: 将连续的非 $0$ 元素作为一个整体处理，简化问题。
3. **标记数组**: 使用标记数组记录已经染色的元素，避免重复计算。

### 可拓展之处
本题的贪心策略可以应用于类似的染色问题，如区间覆盖、任务调度等。通过优先处理高价值或高影响力的元素，可以有效地减少资源的使用。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：45.47秒