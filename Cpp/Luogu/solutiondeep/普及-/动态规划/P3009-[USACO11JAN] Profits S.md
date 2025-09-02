# 题目信息

# [USACO11JAN] Profits S

## 题目描述

The cows have opened a new business, and Farmer John wants to see how well they are doing. The business has been running for N (1 <= N <= 100,000) days, and every day i the cows recorded their net profit P\_i (-1,000 <= P\_i <= 1,000).

Farmer John wants to find the largest total profit that the cows have made during any consecutive time period. (Note that a consecutive time period can range in length from one day through N days.) Help him by writing a program to calculate the largest sum of consecutive profits.


奶牛们开始了新的生意，它们的主人约翰想知道它们到底能做得多好。这笔生意已经做了N（1≤N≤100,000）天，每天奶牛们都会记录下这一天的利润Pi（-1,000≤Pi≤1,000）。


约翰想要找到奶牛们在连续的时间期间所获得的最大的总利润。（注：连续时间的周期长度范围从第一天到第N天）。


请你写一个计算最大利润的程序来帮助他。


## 说明/提示

The maximum sum is obtained by taking the sum from the second through the sixth number (4, 9, -2, -5, 8) => 14.

感谢@smartzzh 提供的翻译。


## 样例 #1

### 输入

```
7 
-3 
4 
9 
-2 
-5 
8 
-3 
```

### 输出

```
14 
```

# AI分析结果



### 综合分析与结论
本题是最大子段和的经典问题，各题解主要围绕动态规划与贪心两种思路展开。核心难点在于处理全负数情况、状态转移逻辑的优化以及空间复杂度控制。最优解法时间复杂度均为O(n)，空间复杂度O(1)。

---

### 高评分题解推荐
#### 1. QianianXY（★★★★★）
**核心亮点**：  
- 动态规划边读边处理，代码极简  
- 用极小值初始化`ans`自动处理全负数情况  
- 空间优化（合并输入数组与DP数组）

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] = max(a[i], a[i] + a[i-1]); // 状态转移
    ans = max(a[i], ans); // 实时更新最大值
}
```

#### 2. Y15BeTa（★★★★☆）
**核心亮点**：  
- 无数组优化（仅用临时变量）  
- 明确讨论全负数测试点的处理  
- 强调ans初始化必须极小值

**调试心得**：  
> "第三个点全是负数时，若错误地将temp重置为0会WA。必须保证至少选一个元素。"

**核心代码**：
```cpp
int temp = 0, ans = -2147483647;
for (int i = 1; i <= n; i++) {
    int x; scanf("%d", &x);
    temp = max(temp + x, x); // 滚动更新
    ans = max(ans, temp);
}
```

#### 3. 午尘（★★★★☆）
**核心亮点**：  
- 标准DP模板，适合教学  
- 显式分离状态转移与结果扫描阶段  
- 强调答案可能为负值的初始化

**核心代码**：
```cpp
int f[100001], ans = -1e9;
for (int i = 1; i <= n; i++) {
    f[i] = max(f[i-1] + a[i], a[i]); // 经典转移
    ans = max(ans, f[i]);
}
```

---

### 关键思路总结
1. **动态规划核心方程**：  
   `f[i] = max(f[i-1] + a[i], a[i])`  
   表示以a[i]结尾的最大子段和，要么延续前段，要么独立成段。

2. **空间优化技巧**：  
   滚动变量代替DP数组（如Y15BeTa的`temp`变量）。

3. **特殊值处理**：  
   初始化`ans`为极小值（如`-0x7fffffff`）自动兼容全负数场景。

4. **贪心策略**：  
   当当前和变为负值时重置为0（需额外处理全负数特例）。

---

### 拓展训练
1. **环形最大子段和**（洛谷P1121）  
   需结合前缀和与DP，处理循环数组特性。

2. **二维最大子矩阵**（洛谷P2642）  
   将一维DP思想扩展到二维，枚举行范围后压缩列。

3. **带长度限制的最大子段和**（洛谷P2717）  
   结合滑动窗口或单调队列优化。

---

### 同类题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   完全相同的模板题，可用于巩固基础。

2. [P2642 双子序列最大和](https://www.luogu.com.cn/problem/P2642)  
   要求两个不相交子段的最大和，需要双向DP。

3. [P1121 环状最大子段和](https://www.luogu.com.cn/problem/P1121)  
   经典变式，需处理环形数组特性。

---
处理用时：51.96秒