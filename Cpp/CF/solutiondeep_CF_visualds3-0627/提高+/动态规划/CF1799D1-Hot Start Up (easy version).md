# 题目信息

# Hot Start Up (easy version)

## 题目描述

This is an easy version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

You have a device with two CPUs. You also have $ k $ programs, numbered $ 1 $ through $ k $ , that you can run on the CPUs.

The $ i $ -th program ( $ 1 \le i \le k $ ) takes $ cold_i $ seconds to run on some CPU. However, if the last program we ran on this CPU was also program $ i $ , it only takes $ hot_i $ seconds ( $ hot_i \le cold_i $ ). Note that this only applies if we run program $ i $ multiple times consecutively — if we run program $ i $ , then some different program, then program $ i $ again, it will take $ cold_i $ seconds the second time.

You are given a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers from $ 1 $ to $ k $ . You need to use your device to run programs $ a_1, a_2, \ldots, a_n $ in sequence. For all $ 2 \le i \le n $ , you cannot start running program $ a_i $ until program $ a_{i - 1} $ has completed.

Find the minimum amount of time needed to run all programs $ a_1, a_2, \ldots, a_n $ in sequence.

## 说明/提示

In the first test case, we can do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 3 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 2 $ seconds to run.
- Run program $ a_3 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 3 + 2 + 1 = 6 $ seconds to run them all. We can show this is optimal.

In the second test case, we can use do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 5 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 3 $ seconds to run.
- Run program $ a_3 = 1 $ on CPU $ 1 $ . The last program run on this CPU was also program $ 1 $ , so it takes $ hot_1 = 2 $ seconds to run.
- Run program $ a_4 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 5 + 3 + 2 + 1 = 11 $ seconds. We can show this is optimal.

## 样例 #1

### 输入

```
9
3 2
1 2 2
3 2
2 1
4 2
1 2 1 2
5 3
2 1
4 3
1 2 3 1
100 100 100
1 1 1
5 2
2 1 2 1 1
65 45
54 7
5 3
1 3 2 1 2
2 2 2
1 1 1
5 1
1 1 1 1 1
1000000000
999999999
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
1 3
3
4 5 6
1 2 3
8 3
3 3 3 1 2 3 2 1
10 10 8
10 10 5```

### 输出

```
6
11
301
225
8
4999999996
11
6
63```

# AI分析结果



# 题目重写

## 题目描述

这是问题的简单版本。与困难版本的区别仅在于对 $t$、$n$、$k$ 的限制不同。

你有一个带有两个 CPU 的设备。还有编号为 $1$ 到 $k$ 的 $k$ 种程序可以在 CPU 上运行。

第 $i$ 种程序（$1 \le i \le k$）在某 CPU 上运行时需要 $cold_i$ 秒。但如果该 CPU 上一次运行的程序也是第 $i$ 种，则只需要 $hot_i$ 秒（$hot_i \le cold_i$）。注意：仅当连续多次运行同一程序时生效——如果运行程序 $i$，再运行其他程序，然后再运行程序 $i$，第二次仍需要 $cold_i$ 秒。

给定一个长度为 $n$ 的序列 $a_1, a_2, \ldots, a_n$，其中每个元素为 $1$ 到 $k$ 的整数。你需要按顺序运行这些程序。对于所有 $2 \le i \le n$，只有在前一个程序 $a_{i-1}$ 完成后才能开始运行 $a_i$。

求运行所有程序的最小总时间。

## 样例 #1

输入输出与说明与原题一致，此处省略。

---

# 算法分类  
**线性DP**

---

# 题解分析与结论

## 核心思路
所有题解均采用动态规划，核心思想是：
1. **状态定义**：设 `dp[i][j]` 表示处理完前 `i` 个程序，另一个 CPU 最后一次运行的程序类型为 `j` 时的最小耗时。
2. **状态转移**：根据当前程序 `a[i]` 是否与前一个程序 `a[i-1]` 相同，分两种情况进行转移：
   - 若 `a[i] == a[i-1]`，则必须使用同一 CPU（节省时间）。
   - 否则，选择将当前程序放在前一个 CPU 或另一个 CPU 上，更新状态。
3. **空间优化**：通过滚动数组或压缩状态维度，将空间复杂度从 $O(nk)$ 降为 $O(k)$。

## 解决难点
- **状态简化**：通过观察发现，必有一个 CPU 最后一次运行的是 `a[i-1]`，因此只需记录另一个 CPU 的状态。
- **转移方程推导**：通过枚举前一个状态的所有可能，选择最优转移路径。
- **边界处理**：正确初始化第一个程序的状态。

## 关键状态转移
$$
\begin{cases}
dp[i][j] = \min(dp[i][j], dp[i-1][j] + \text{cost}(a[i])) \\
dp[i][a[i-1]] = \min(dp[i][a[i-1]], dp[i-1][j] + \text{cost}(j))
\end{cases}
$$
其中 $\text{cost}(x) = \begin{cases} 
hot_{a[i]} & (x == a[i]) \\
cold_{a[i]} & \text{否则}
\end{cases}$

---

# 题解评分（≥4星）

1. **SlyCharlotte（★★★★★）**  
   - **亮点**：代码简洁，状态定义清晰，转移逻辑直白。  
   - **关键代码**：通过双重循环直接枚举前序状态，利用 `min` 更新当前状态。

2. **穼柗°（★★★★☆）**  
   - **亮点**：使用对称转移方程，代码结构紧凑。  
   - **优化点**：采用 `fill` 初始化数组，减少冗余操作。

3. **Sun_pirf（★★★★☆）**  
   - **亮点**：注释详细，状态转移方程推导完整。  
   - **特色**：通过预处理冷热时间数组提升可读性。

---

# 最优思路提炼

## 关键技巧
1. **状态压缩**：利用「必有一个 CPU 运行前序程序」的特性，将状态维度从三维降为二维。
2. **滚动更新**：每一层状态仅依赖前一层，可用一维数组实现。
3. **时间计算优化**：通过预判连续相同程序直接累加热时间。

---

# 类似题目推荐
1. [CF1799D2](https://codeforces.com/contest/1799/problem/D2)（本题的困难版，需进一步优化）
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)（经典 0-1 背包问题）
3. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)（线性 DP 基础题）

---

# 可视化与算法演示

## 动态规划矩阵演示
- **动画方案**：以网格展示 `dp[i][j]`，每次更新时高亮当前行和前一行的相关单元格。
- **颜色标记**：  
  - 红色：当前正在更新的状态。  
  - 绿色：转移来源的前序状态。  
- **交互功能**：支持步进播放、速度调节，展示每一步的 `min` 操作和数值变化。

## 复古像素风格设计
- **8位调色板**：用 16 色像素块表示 DP 矩阵，每个格子显示数值简写。
- **音效设计**：  
  - 转移时播放 "beep" 音效。  
  - 更新最小值时播放上扬音调。  
- **自动演示**：模拟贪吃蛇式路径，自动按顺序更新 DP 状态。

---

# 核心代码片段
```cpp
// SlyCharlotte 的 DP 实现（简化版）
ll dp[maxn][maxn];
void solve() {
    // 初始化
    for (int i=0; i<=n; i++) fill(dp[i], INF);
    dp[1][0] = cold[a[1]];

    // 状态转移
    for (int i=2; i<=n; i++) {
        int prev = a[i-1];
        for (int j=0; j<=k; j++) {
            // 情况1：沿用前序 CPU
            ll cost = (a[i] == prev) ? hot[a[i]] : cold[a[i]];
            dp[i][j] = min(dp[i][j], dp[i-1][j] + cost);
            
            // 情况2：使用另一 CPU
            cost = (a[i] == j) ? hot[a[i]] : cold[a[i]];
            dp[i][prev] = min(dp[i][prev], dp[i-1][j] + cost);
        }
    }
    // 取最小值作为答案
    cout << *min_element(dp[n], dp[n]+k+1);
}
```

---

# 总结
本题通过巧妙的 DP 状态设计，将看似复杂的双 CPU 调度问题转化为经典的线性 DP 问题。关键点在于识别状态的可压缩性，并通过合理的转移方程实现高效计算。同类问题可通过类似的状态简化思路进行优化。

---
处理用时：87.68秒