# 题目信息

# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1```

### 输出

```
-1```

## 样例 #2

### 输入

```
3 2```

### 输出

```
4```

## 样例 #3

### 输入

```
13 42```

### 输出

```
12```

# AI分析结果

### 题目内容重写（中文）

给定两个整数 $n$ 和 $x$。你可以对整数 $x$ 进行若干次操作。

每次操作如下：选择 $x$ 的十进制表示中至少出现一次的数字 $y$，并将 $x$ 替换为 $x \cdot y$。

你的目标是使 $x$ 的十进制表示的长度（不含前导零）等于 $n$。问最少需要多少次操作才能实现这一目标？

### 样例 #1

#### 输入

```
2 1
```

#### 输出

```
-1
```

### 样例 #2

#### 输入

```
3 2
```

#### 输出

```
4
```

### 样例 #3

#### 输入

```
13 42
```

#### 输出

```
12
```

---

### 题解分析与结论

本题的核心是通过对 $x$ 进行乘法操作，使其位数达到 $n$。由于每次操作可以选择 $x$ 的任意一位数字进行乘法，因此问题可以转化为一个搜索问题，通常使用 BFS 或 DFS 来解决。

#### 题解对比与评分

1. **作者：litachloveyou (赞：21)**
   - **评分：4.5星**
   - **关键亮点**：使用了 BFS 结合剪枝策略，通过计算当前数位与目标数位的差值进行剪枝，优化了搜索效率。
   - **个人心得**：通过贪心策略从高位开始乘，进一步优化了搜索路径。
   - **核心代码**：
     ```cpp
     void bfs(ll x, ll c) {
         if (n + c - leg(x) >= ans) return; // 最优情况剪枝
         if (leg(x) == n) {
             ans = c; // 更新答案
             que = true;
             return;
         }
         vector<int> a(10);
         ll k = x;
         while (k) {
             a[k % 10]++;
             k = k / 10;
         }
         for (int i = 9; i > 1; i--) { // 从9开始
             if (a[i] >= 1) {
                 bfs(x * i, c + 1);
             }
         }
     }
     ```

2. **作者：dbxxx (赞：4)**
   - **评分：4星**
   - **关键亮点**：通过 BFS 结合 set 进行状态判重，避免了重复计算，优化了空间和时间复杂度。
   - **核心代码**：
     ```cpp
     while (!q.empty()) {
         int x = q.front().first, step = q.front().second;
         q.pop();
         if (x >= l) {
             printf("%llu\n", step);
             return 0;
         }
         std::memset(hav, false, sizeof(hav));
         int t = x;
         while (t) {
             hav[t % 10] = true;
             t /= 10;
         }
         for (int i = 2; i <= 9; ++i) if (hav[i]) {
             if (vis.count(x * i)) continue;
             q.emplace(x * i, step + 1);
             vis.insert(x * i);
         }
     }
     ```

3. **作者：CWzwz (赞：2)**
   - **评分：4星**
   - **关键亮点**：使用了动态规划的思路，通过四维状态压缩减少了状态数，优化了搜索效率。
   - **核心代码**：
     ```cpp
     for (int a = 0; a < 64; a++) {
         for (int b = 0; b < 40; b++) {
             for (int c = 0; c < 28; c++) {
                 for (int d = 0; d < 23; d++) {
                     ll now = num(a, b, c, d);
                     if (now == -1) break;  // 超出范围不管
                     ll set = 0, tmp = now;
                     while (tmp) set |= (1 << (tmp % 10)), tmp /= 10; // 压 set_now
                     for (int k = __builtin_ctz(set); set; set -= set & -set, k = __builtin_ctz(set)) { // 枚二进制位
                         if (k == 0 || k == 1) continue;
                         if (now * k > max) break;
                         if (k == 2 || k == 3 || k == 5 || k == 7) {
                             f[a + (k == 2)][b + (k == 3)][c + (k == 5)][d + (k == 7)] = std::min(f[a + (k == 2)][b + (k == 3)][c + (k == 5)][d + (k == 7)], f[a][b][c][d] + 1);
                         } else if (k == 4) {
                             f[a + 2][b][c][d] = std::min(f[a + 2][b][c][d], f[a][b][c][d] + 1);
                         } else if (k == 6) {
                             f[a + 1][b + 1][c][d] = std::min(f[a + 1][b + 1][c][d], f[a][b][c][d] + 1);
                         } else if (k == 8) {
                             f[a + 3][b][c][d] = std::min(f[a + 3][b][c][d], f[a][b][c][d] + 1);
                         } else if (k == 9) {
                             f[a][b + 2][c][d] = std::min(f[a][b + 2][c][d], f[a][b][c][d] + 1);
                         } // 刷表
                     }
                     if (now >= min) ans = std::min(ans, f[a][b][c][d]);
                 }
             }
         }
     }
     ```

### 最优关键思路与技巧

1. **BFS + 剪枝**：通过 BFS 进行状态搜索，结合剪枝策略（如当前操作次数与目标位数的差值）来优化搜索效率。
2. **状态压缩**：使用四维状态压缩（如 $2^a \times 3^b \times 5^c \times 7^d$）来减少状态数，避免重复计算。
3. **贪心策略**：从高位开始乘，优先选择较大的数字进行乘法操作，以尽快增加位数。

### 可拓展之处

1. **类似问题**：可以考虑扩展到其他进制下的位数增长问题，或者扩展到其他操作（如加法、减法等）。
2. **优化方向**：可以进一步优化状态压缩的方式，或者结合启发式搜索（如 A* 算法）来加速搜索过程。

### 推荐题目

1. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
3. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)

---
处理用时：49.99秒