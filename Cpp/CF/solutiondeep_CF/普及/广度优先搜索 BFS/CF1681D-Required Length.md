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

### 题目内容重写

**题目描述**

给定两个整数 $n$ 和 $x$。你可以对整数 $x$ 进行多次操作。

每次操作如下：选择 $x$ 的十进制表示中至少出现一次的数字 $y$，并将 $x$ 替换为 $x \cdot y$。

你的目标是使 $x$ 的十进制表示的长度（不含前导零）等于 $n$。问最少需要多少次操作才能实现这一目标？

**说明/提示**

在第二个样例中，以下操作序列可以达到目标：

1. 将 $x$ 乘以 $2$，得到 $x = 2 \cdot 2 = 4$；
2. 将 $x$ 乘以 $4$，得到 $x = 4 \cdot 4 = 16$；
3. 将 $x$ 乘以 $6$，得到 $x = 16 \cdot 6 = 96$；
4. 将 $x$ 乘以 $9$，得到 $x = 96 \cdot 9 = 864$。

**样例 #1**

输入：
```
2 1
```
输出：
```
-1
```

**样例 #2**

输入：
```
3 2
```
输出：
```
4
```

**样例 #3**

输入：
```
13 42
```
输出：
```
12
```

### 题解综合分析与结论

本题的核心是通过对 $x$ 进行乘法操作，使其位数达到 $n$。由于每次操作只能选择 $x$ 的某一位数字进行乘法，因此问题的关键在于如何选择乘法顺序以最小化操作次数。

#### 关键思路与技巧
1. **BFS与剪枝**：大多数题解采用了BFS（广度优先搜索）来遍历所有可能的乘法路径，并通过剪枝策略（如最优情况剪枝、可行性剪枝）来减少搜索空间。
2. **状态压缩**：部分题解通过将 $x$ 的状态压缩为 $2^a \times 3^b \times 5^c \times 7^d$ 的形式，减少了状态数量，从而提高了搜索效率。
3. **记忆化**：使用 `set` 或 `map` 来记录已经访问过的状态，避免重复计算。

#### 最优题解推荐

1. **作者：litachloveyou (赞：21)**  
   **星级：5星**  
   **关键亮点**：  
   - 使用BFS结合贪心策略，从高到低选择乘法数字，减少搜索路径。
   - 引入最优情况剪枝，提前终止无效搜索路径。
   - 代码简洁，逻辑清晰，易于理解。

   **核心代码**：
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
           k /= 10;
       }
       for (int i = 9; i > 1; i--) { // 从9开始
           if (a[i] >= 1) {
               bfs(x * i, c + 1);
           }
       }
   }
   ```

2. **作者：dbxxx (赞：4)**  
   **星级：4星**  
   **关键亮点**：  
   - 使用BFS结合状态压缩，将 $x$ 的状态表示为 $2^a \times 3^b \times 5^c \times 7^d$，减少了状态数量。
   - 使用 `set` 进行记忆化，避免重复计算。
   - 代码结构清晰，优化程度较高。

   **核心代码**：
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
   **星级：4星**  
   **关键亮点**：  
   - 使用动态规划（DP）结合状态压缩，将 $x$ 的状态表示为 $2^a \times 3^b \times 5^c \times 7^d$，减少了状态数量。
   - 通过刷表法进行状态转移，优化了DP的效率。
   - 代码结构清晰，优化程度较高。

   **核心代码**：
   ```cpp
   for (int a = 0; a < 64; a++) {
       for (int b = 0; b < 40; b++) {
           for (int c = 0; c < 28; c++) {
               for (int d = 0; d < 23; d++) {
                   ll now = num(a, b, c, d);
                   if (now == -1) break;
                   ll set = 0, tmp = now;
                   while (tmp) set |= (1 << (tmp % 10)), tmp /= 10;
                   for (int k = __builtin_ctz(set); set; set -= set & -set, k = __builtin_ctz(set)) {
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
                       }
                   }
                   if (now >= min) ans = std::min(ans, f[a][b][c][d]);
               }
           }
       }
   }
   ```

### 可拓展之处
1. **类似问题**：可以扩展到其他进制下的乘法操作，或者引入其他操作（如加法、减法）来改变 $x$ 的值。
2. **算法套路**：BFS结合剪枝、状态压缩、记忆化等技巧可以应用于其他搜索问题，如最短路径、状态转移等。

### 推荐题目
1. **P1135 奇怪的电梯**：考察BFS与状态转移。
2. **P1443 马的遍历**：考察BFS与剪枝策略。
3. **P1074 靶形数独**：考察DFS与剪枝策略。

### 个人心得摘录
- **litachloveyou**：通过贪心策略和剪枝，大大减少了搜索空间，使得原本无法通过的样例得以通过。
- **dbxxx**：使用状态压缩和 `set` 进行记忆化，优化了BFS的效率，代码实现简洁。
- **CWzwz**：通过动态规划结合状态压缩，减少了状态数量，优化了DP的效率，代码结构清晰。

---
处理用时：67.55秒