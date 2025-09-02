# 题目信息

# Hot Start Up (hard version)

## 题目描述

This is a hard version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

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



**唯一算法分类**  
动态规划

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
所有题解均采用动态规划，核心在于状态设计与转移优化：
- **状态定义**：多数题解将状态压缩为一维，如 `dp[i]` 表示处理到当前程序时，另一CPU最后运行的程序类型为 `i` 的最小时间。
- **转移优化**：通过观察连续程序间的相似性，利用全局变量记录最小值，避免重复遍历。

#### **解决难点**
1. **状态爆炸**：原始二维状态 `dp[i][j]` 的复杂度为 `O(nk^2)`，通过压缩状态至一维并利用滚动变量优化至 `O(n)`。
2. **快速转移**：维护全局最小值 `minn` 和累加偏移量 `s`，将转移操作简化为常数时间。

#### **关键步骤**
- **状态转移方程**：
  ```math
  dp[a_{i-1}] = \min(\text{全局最小值} + cold_{a_i}, dp[a_i] + hot_{a_i}) - cold_{a_i}
  ```
- **偏移量累加**：通过 `s` 记录全局时间偏移，避免逐个更新 `dp` 数组。

---

### **题解评分 (≥4星)**

1. **thostever (★★★★★)**  
   - **亮点**：状态压缩至一维，代码简洁高效，线性时间复杂度。  
   - **代码片段**：  
     ```cpp
     for(int i=1;i<=n;i++) {
         if(a[i]==a[i-1]) s += hot[a[i]];
         else {
             s += cold[a[i]];
             dp[a[i-1]] = min(dp[a[i]] + hot[a[i]], minn + cold[a[i]]) - cold[a[i]];
             minn = min(minn, dp[a[i-1]]);
         }
     }
     ```

2. **2018ljw (★★★★☆)**  
   - **亮点**：前缀和优化转移，维护每类最小值，思路清晰。  
   - **关键公式**：  
     ```math
     dp_i = \min(\text{全局最小值} + cold_{a_{i+1}}, \text{同类最小值} + hot_{a_{i+1}})
     ```

3. **sjr3065335594 (★★★★☆)**  
   - **亮点**：结合费用预支思想，公式推导严谨，代码易移植。

---

### **最优思路或技巧提炼**

1. **状态压缩**：仅维护另一CPU的最后程序类型，将二维状态降至一维。
2. **全局偏移量**：用 `s` 记录累加时间，避免逐个更新 `dp` 值。
3. **双最小值维护**：分别记录全局最小值和同类最小值，加速转移。

---

### **同类型题与算法套路**

- **通用解法**：动态规划 + 滚动数组优化，适用于序列决策问题（如任务调度、路径规划）。
- **相似题目**：  
  1. **洛谷 P1776**（单调队列优化DP）  
  2. **洛谷 P1048**（0-1背包问题）  
  3. **洛谷 P1091**（线性DP）

---

### **个人心得摘录**

- **Super_Cube**：  
  > “考场思路错误后通过特判越界情况修正，调试中发现转移方程需考虑 `l_i` 不存在的情况。”

---

### **可视化与算法演示**

#### **动画设计**
- **界面布局**：  
  - 左侧画布显示两个CPU方块，右侧显示 `dp` 数组和全局变量 `minn`、`s`。
  - 当前程序高亮显示，颜色区分 `hot`（绿色）和 `cold`（红色）。

#### **关键帧**
1. **初始状态**：两个CPU为空，`dp` 数组初始化为 `INF`，`s=0`。
2. **程序处理**：  
   - 若当前程序与前一个相同，`s += hot`，对应CPU闪动绿色。  
   - 否则，更新 `dp[a_{i-1}]`，全局最小值 `minn` 刷新，对应CPU闪动红色。
3. **变量跟踪**：高亮 `dp` 数组中变化的位置，显示数值变化。

#### **复古风格**
- **8位像素风**：CPU用16x16像素块表示，`dp` 数组以网格显示，数值用8位字体。
- **音效**：  
  - 转移成功：短促“滴”声。  
  - 更新最小值：上扬音调。

#### **交互功能**
- **步进控制**：允许单步执行，观察 `dp` 和 `s` 变化。
- **自动模式**：AI自动运行，速度可调（1x/2x/5x）。

---

### **核心代码实现**

```cpp
// thostever 的核心代码（简化版）
ll dp[N], s = 0, minn = 0;
for (int i = 1; i <= n; i++) {
    if (a[i] == a[i-1]) {
        s += hot[a[i]];
    } else {
        s += cold[a[i]];
        ll new_val = min(dp[a[i]] + hot[a[i]], minn + cold[a[i]]) - cold[a[i]];
        minn = min(minn, new_val);
        dp[a[i-1]] = new_val;
    }
}
printf("%lld\n", minn + s);
```

---

### **总结**
本题通过动态规划的状态压缩和全局变量优化，将复杂度降至线性。可视化设计结合复古像素风格和交互式步进，可直观展示状态转移过程，适合教学与算法演示。

---
处理用时：71.08秒