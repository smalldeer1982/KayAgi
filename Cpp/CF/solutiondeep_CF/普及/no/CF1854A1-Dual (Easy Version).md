# 题目信息

# Dual (Easy Version)

## 题目描述

[Popskyy &amp; tiasu - Dual](https://soundcloud.com/popskyy/popskyy-tiasu-dual)

⠀



The only difference between the two versions of this problem is the constraint on the maximum number of operations. You can make hacks only if all versions of the problem are solved.

You are given an array $ a_1, a_2,\dots, a_n $ of integers (positive, negative or $ 0 $ ). You can perform multiple operations on the array (possibly $ 0 $ operations).

In one operation, you choose $ i, j $ ( $ 1 \leq i, j \leq n $ , they can be equal) and set $ a_i := a_i + a_j $ (i.e., add $ a_j $ to $ a_i $ ).

Make the array non-decreasing (i.e., $ a_i \leq a_{i+1} $ for $ 1 \leq i \leq n-1 $ ) in at most $ 50 $ operations. You do not need to minimize the number of operations.

## 说明/提示

In the first test case, by adding $ a_1 = 2 $ to $ a_2 $ , we get the array $ [2, 3] $ which is non-decreasing.

In the second test case, the array changes as:

- $ [1, 2, -10, 3] $
- $ [1, 2, -10, 6] $
- $ [1, 2, -10, 12] $
- $ [1, 2, 2, 12] $

In the third test case, the final array is $ [2, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
10
2
2 1
4
1 2 -10 3
5
2 1 1 1 1
8
0 0 0 0 0 0 0 0
5
1 2 -4 3 -10
10
11 12 13 14 15 -15 -16 -17 -18 -19
7
1 9 3 -4 -3 -2 -1
3
10 9 8
20
1 -14 2 -10 6 -5 10 -13 10 7 -14 19 -5 19 1 18 -16 -7 12 8
20
-15 -17 -13 8 14 -13 10 -4 11 -4 -16 -6 15 -4 -2 7 -9 5 -5 17```

### 输出

```
1
2 1
3
4 4
4 4
3 4
4
2 1
3 1
4 1
5 1
0
7
3 4
3 4
5 4
5 4
5 4
5 4
5 4
15
6 1
6 1
6 1
7 2
7 2
7 2
8 3
8 3
8 3
9 4
9 4
9 4
10 5
10 5
10 5
8
3 4
3 4
2 4
2 4
2 4
2 4
1 4
1 4
3
2 1
3 1
3 1
31
14 1
18 7
13 11
15 11
6 4
5 17
19 6
19 12
10 5
11 12
1 17
15 19
16 10
14 2
16 11
20 7
7 6
9 5
3 6
6 14
17 18
18 14
12 3
17 16
8 18
13 16
9 8
14 8
16 2
11 8
12 7
31
5 12
19 13
9 1
5 17
18 19
6 16
15 8
6 9
15 14
7 10
19 7
17 20
14 4
15 20
4 3
1 8
16 12
16 15
5 6
12 10
11 15
20 3
20 19
13 14
11 14
18 10
7 3
12 17
4 7
13 2
11 13```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个包含 $n$ 个整数的数组 $a_1, a_2, \dots, a_n$（整数可以是正数、负数或零）。你可以进行多次操作（可能为零次操作）。在每次操作中，你可以选择 $i, j$（$1 \leq i, j \leq n$，$i$ 和 $j$ 可以相等），并将 $a_i$ 设置为 $a_i + a_j$（即将 $a_j$ 加到 $a_i$ 上）。目标是在最多 50 次操作内使数组变为非递减数组（即 $a_i \leq a_{i+1}$ 对于 $1 \leq i \leq n-1$）。你不需要最小化操作次数。

#### 说明/提示
- 在第一个测试用例中，通过将 $a_1 = 2$ 加到 $a_2$ 上，得到数组 $[2, 3]$，它是非递减的。
- 在第二个测试用例中，数组变化如下：
  - $[1, 2, -10, 3]$
  - $[1, 2, -10, 6]$
  - $[1, 2, -10, 12]$
  - $[1, 2, 2, 12]$
- 在第三个测试用例中，最终数组为 $[2, 3, 3, 3, 3]$。

### 算法分类
构造

### 题解分析与结论
本题的核心是通过构造操作使数组变为非递减数组。题解中主要分为以下几种思路：
1. **分类处理**：根据数组元素的符号（全正、全负、混合）进行分类处理，分别采用前缀和、后缀和或通过最大绝对值元素统一符号后再进行处理。
2. **倍增操作**：通过倍增操作使某个元素的绝对值足够大，然后将其加到其他元素上，统一符号后再进行前缀和或后缀和操作。
3. **贪心策略**：选择操作次数较少的方案，优先处理符号较少的元素。

### 精选题解
#### 题解1：legend_cn（★★★★★）
**关键亮点**：
- 分类处理清晰，分别处理全正、全负、混合情况。
- 通过最大绝对值元素统一符号，再进行处理，操作次数控制在 $2n-2$ 次内。
- 代码简洁，注释清晰，易于理解。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    if (i == id) continue;
    ans[++tot] = {i, id};
    a[i] += a[id];
}
if (a[id] > 0) {
    for (int i = 2; i <= n; i++) ans[++tot] = {i, i - 1};
} else {
    for (int i = n; i > 1; i--) ans[++tot] = {i - 1, i};
}
```

#### 题解2：引领天下（★★★★☆）
**关键亮点**：
- 通过倍增操作使某个元素足够大，然后统一符号。
- 操作次数控制在 $2n+5$ 次内，适用于 Easy Version。
- 思路清晰，代码简洁。

**核心代码**：
```cpp
while (a[n] < 128) a[n] *= 2, ans.push_back(make_pair(n, n));
for (int i = 2; i < n; i++) ans.push_back(make_pair(i, n)), ans.push_back(make_pair(n, n));
```

#### 题解3：信息向阳花木（★★★★☆）
**关键亮点**：
- 通过最大绝对值元素统一符号，再进行处理，操作次数控制在 $2n-2$ 次内。
- 代码简洁，注释清晰，易于理解。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    if (i == k) continue;
    ans[++tot] = {i, k};
    a[i] += a[k];
}
if (a[k] < 0) for (int i = n; i > 1; i--) ans[++tot] = {i - 1, i};
if (a[k] > 0) for (int i = 1; i < n; i++) ans[++tot] = {i + 1, i};
```

### 最优关键思路
1. **统一符号**：通过最大绝对值元素统一数组的符号，简化后续处理。
2. **前缀和/后缀和**：在统一符号后，使用前缀和或后缀和操作使数组变为非递减数组。
3. **倍增操作**：通过倍增操作使某个元素的绝对值足够大，确保统一符号的操作次数最少。

### 拓展思路
- **类似题目**：可以通过类似思路解决其他需要统一符号或通过特定操作使数组满足某种性质的题目。
- **优化操作次数**：在操作次数有限的情况下，优先选择操作次数较少的方案。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：36.99秒