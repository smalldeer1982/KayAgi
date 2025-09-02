# 题目信息

# [USACO12DEC] Wifi Setup S

## 题目描述

Farmer John's N cows (1 <= N <= 2000) are all standing at various positions along the straight path from the barn to the pasture, which we can think of as a one-dimensional number line.  Since his cows like to stay in email contact with each-other, FJ wants to install Wifi base stations at various positions so that all of the cows have wireless coverage.

After shopping around, FJ learns that the cost of a Wifi base station depends on distance it can transmit: a base station of power r costs A + B\*r, where A is a fixed cost for installing the base station and B is a cost per unit of transmission distance.  If FJ installs such a device at position x, then it can transmit data to any cow located in the range x-r ... x+r.  A base station with transmission power of r=0 is allowed, but this only provides coverage to a cow located at the same position as the transmitter.

Given the values of A and B, as well as the locations of FJ's cows, please determine the least expensive way FJ can provide wireless coverage for all his cows.

给出在同一条直线上的n个点和两个数A，B，现在要在这条直线上放置若干个信号塔，每个信号塔有一个r值，假设它的位置是x，则它能覆盖的范围是x-r~x+r，放置一个信号塔的花费是A+B\*r，问要覆盖所有的点最小的花费是多少。


## 说明/提示

There are 3 cows at positions 7, 0, and 100.  Installation of a base station of power r costs 20 + 5\*r.


The optimal solution is to build a base station at position 3.5 (with power 3.5) and another at position 100 (with power 0).  The first base station covers cows 1 and 2, and the second covers cow 3.


## 样例 #1

### 输入

```
3 20 5 
7 
0 
100 
```

### 输出

```
57.5 
```

# AI分析结果



### 题解综合分析结论
本题的核心解法是动态规划，通过将问题拆分为覆盖前i个点的最优子结构，利用排序后的坐标计算每个区间的最小覆盖代价。贪心方法虽时间复杂度低，但正确性存疑。动态规划通过预处理排序与状态转移，确保正确性，时间复杂度O(n²)可接受。

### 精选题解

#### 1. Parat_rooper 的优化动态规划（5星）
**关键亮点**：  
- 状态定义清晰，直接维护`cost[i]`表示覆盖前i个点的最小代价  
- 优化状态转移，消除冗余数组，代码简洁高效  
- 整数处理技巧（乘2避免浮点运算）提升代码可读性与运行效率  

**核心代码**：  
```cpp
sort(w + 1, w + n + 1);
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
        cost[i] = min(cost[j - 1] + (w[i] - w[j]) * b + 2 * a, cost[i]);
    }
}
```

#### 2. yinhee 的动态规划（4星）  
**关键亮点**：  
- 明确的状态转移方程`dp[i] = min(dp[j] + cost(j+1,i))`  
- 完整的预处理与输出处理逻辑  
- 代码结构清晰，注释到位  

**核心代码**：  
```cpp
for (int i = 1; i <= n; i++) {
    dp[i] = cost(1, i); // 初始化为覆盖整个区间
    for (int j = 1; j < i; j++) {
        dp[i] = min(dp[i], dp[j] + cost(j + 1, i));
    }
}
```

#### 3. 信守天下 的动态规划（4星）  
**关键亮点**：  
- 简洁的代码实现，直接嵌入排序与状态转移  
- 输出处理完整，兼顾整数与小数情况  
- 对动态规划思想的直观展示  

**核心代码**：  
```cpp
for (int i = 1; i <= n; i++) {
    dp[i] = 0x7fffffff;
    for (int j = 1; j <= i; j++) {
        dp[i] = min(dp[i], dp[j - 1] + (p[i] - p[j]) * b + 2 * a);
    }
}
```

### 关键思路与技巧总结  
1. **排序预处理**：将点按坐标排序，确保区间覆盖连续。  
2. **动态规划状态设计**：`dp[i]`表示覆盖前i个点的最小代价，通过枚举最后一个区间的起点进行转移。  
3. **整数化处理**：将半径计算中的浮点运算转化为整数运算（如乘2），避免精度问题。  
4. **时间复杂度优化**：双重循环的O(n²)在n≤2000时可行，无需进一步优化。  

### 拓展与举一反三  
- **类似问题**：区间覆盖最小代价问题（如活动选择、线段覆盖）  
- **算法套路**：区间型动态规划，通常结合排序与子问题分解。  
- **变形思考**：若信号塔可重叠覆盖，或覆盖半径有上限，需调整状态转移条件。  

### 推荐练习题  
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心思想）  
2. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)（区间DP经典）  
3. [P4933 大师](https://www.luogu.com.cn/problem/P4933)（序列分段动态规划）

---
处理用时：88.18秒