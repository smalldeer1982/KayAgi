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



### 综合分析
本题是经典的最大子段和问题，各题解主要围绕动态规划、贪心、分治与线段树展开。核心优化点在于时间复杂度与空间复杂度控制，其中动态规划的优化版本（空间O(1)）与贪心法最为高效，均达到O(n)时间。

---

### 精选题解（评分≥4星）

#### 1. 题解作者：Y15BeTa（5星）
**核心亮点**：
- **空间优化到O(1)**：边读边处理，无需存储完整数组。
- **全负数处理**：通过`ans`初始化为极小值确保正确性。
- **代码简洁性**：仅用单层循环，维护`temp`变量代替DP数组。
```cpp
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        int x; scanf("%d",&x);
        temp = max(temp+x, x); // 核心决策：继续累加或重启
        ans = max(ans, temp);
    }
    printf("%d\n",ans);
}
```

#### 2. 题解作者：QianianXY（4星）
**核心亮点**：
- **合并数组优化空间**：复用输入数组存储DP状态。
- **循环内联更新**：同步计算最大值，避免二次遍历。
```cpp
for (int i=1; i<=n; i++) {
    scanf("%d", &a[i]);
    a[i] = max(a[i], a[i] + a[i-1]); // DP转移
    ans = max(a[i], ans); // 实时更新最大值
}
```

#### 3. 题解作者：In_blue（4星）
**核心亮点**：
- **贪心策略**：当前和为负时重置，避免拖累后续。
- **全负数特判**：通过`bol`标记和`num`变量处理极端情况。
```cpp
for (int i=1; i<=n; i++) {
    t += a[i];
    if (t<0) t=0; // 贪心重置
    Max = max(Max, t);
    if (a[i]>0) bol=1; // 标记存在正数
    num = max(num, a[i]); // 记录最大单点
}
```

---

### 最优思路总结
**关键技巧**：动态规划的滚动变量优化  
- **核心决策**：若当前子段和为负，则放弃前面结果，从当前元素重新开始。
- **空间优化**：仅用单个变量维护当前子段和，无需数组。
- **极端值处理**：初始化最大值变量为极小值，确保全负数场景正确。

---

### 拓展与举一反三
1. **环形子段和**：处理首尾相连的情况（如洛谷P1121）。
2. **带长度限制**：限定子段长度不超过k（如滑动窗口优化）。
3. **二维扩展**：求矩阵中的最大子矩阵和（如动态规划降维）。

---

### 推荐练习题
1. **P1115 最大子段和**（模板题，直接应用）
2. **P2642 双子序列最大和**（双向动态规划）
3. **P1121 环状最大子段和**（环形扩展，分情况讨论）

---
处理用时：54.03秒