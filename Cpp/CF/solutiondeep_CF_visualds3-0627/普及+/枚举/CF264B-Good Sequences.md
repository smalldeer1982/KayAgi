# 题目信息

# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10
```

### 输出

```
4
```

# AI分析结果



---

**算法分类**  
动态规划（质因数分解优化）

---

**题解思路与核心难点**  
- **核心思路**：将问题转化为动态规划，利用质因数分解优化状态转移。维护每个质因子的最长序列长度，避免暴力枚举所有可能的前驱。  
- **关键变量**：  
  - `dp[i]`：以第i个元素结尾的最长好序列长度。  
  - `f[p]`：所有含有质因子p的元素中，最长的序列长度。  
- **解决难点**：  
  - **质因数分解**：快速获取每个数的质因子（预处理或动态分解）。  
  - **转移优化**：通过质因子共享特性，将O(n²)优化至O(n√a)。  

---

**最优题解评分**  
1. **傅思维666**（⭐️⭐️⭐️⭐️⭐️）  
   - 预处理质因子列表，代码结构清晰，时间效率高。  
2. **happybob**（⭐️⭐️⭐️⭐️）  
   - 动态分解质因子，代码简洁，空间占用更小。  
3. **叶枫**（⭐️⭐️⭐️⭐️）  
   - 利用最小质因子快速分解，预处理巧妙。  

---

**最优思路提炼**  
1. **质因子驱动DP**：每个数的转移仅依赖其质因子对应的历史最大值。  
2. **状态维护技巧**：  
   - 分解当前数的质因子，取所有质因子的`f[p]`最大值加1更新当前`dp`。  
   - 更新所有质因子的`f[p]`为当前`dp`值，确保后续转移可用。  
3. **预处理优化**：线性筛预处理质因子列表，加速分解过程。  

---

**代码片段（核心逻辑）**  
```cpp
// 预处理质因子列表
for (int i = 2; i <= maxn; i++) {
    if (!vis[i]) prime[++tot] = i;
    for (int j = 1; j <= tot && i * prime[j] <= maxn; j++) {
        vis[i*prime[j]] = 1;
        if (i % prime[j] == 0) break;
    }
}
// 主DP逻辑
for (int i = 1; i <= n; i++) {
    int x = a[i], max_len = 0;
    // 分解质因子并计算最大f[p]
    for (int p : get_prime_factors(x)) {
        max_len = max(max_len, f[p]);
    }
    dp[i] = max_len + 1;
    // 更新所有质因子的f[p]
    for (int p : get_prime_factors(x)) {
        f[p] = max(f[p], dp[i]);
    }
    ans = max(ans, dp[i]);
}
```

---

**可视化设计**  
- **动画演示**：  
  1. **像素网格**：将数列显示为一行像素块，每个块标注数值。  
  2. **质因子高亮**：处理当前数时，显示其质因子并连线到历史最大`f[p]`。  
  3. **动态更新**：质因子对应`f[p]`的值变化时，以闪烁效果提示。  
- **音效与交互**：  
  - **分解音效**：分解质因子时播放短促“滴”声。  
  - **更新音效**：`f[p]`更新时播放上扬音调。  
  - **控制面板**：支持暂停/步进，速度调节（慢速/快速）。  

---

**相似题目推荐**  
1. [CF510D - Fox And Jumping](https://codeforces.com/problemset/problem/510/D)  
2. [洛谷 P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)  
3. [LeetCode 300. 最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)  

---

**总结**  
通过质因数分解将相邻元素的关联性转化为共享因子的状态维护，是此类问题的通用优化思路。预处理质因子和动态维护最大值数组的结合，极大提升了算法效率。

---
处理用时：92.06秒