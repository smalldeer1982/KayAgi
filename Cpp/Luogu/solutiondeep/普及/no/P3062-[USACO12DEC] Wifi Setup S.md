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



### 算法分类
动态规划

### 题解综合分析
题目核心是覆盖有序排列的连续区间，最优解通过动态规划枚举最后一个区间的分割点实现。关键技巧是将费用计算转换为整数运算（乘2处理），避免浮点精度问题。所有题解中动态规划解法占主导，贪心解法存在正确性争议。

### 精选题解（评分≥4星）
1. **Parat_rooper**（4星）
   - 亮点：状态压缩优化，将二维状态优化为一维，通过预处理排序保证连续性
   - 代码核心：
     ```cpp
     for (int i = 1; i <= n; i++) {
       for (int j = 1; j <= i; j++) {
         cost[i] = min(cost[j - 1] + (w[i] - w[j]) * b + 2 * a, cost[i]);
       }
     }
     ```

2. **信守天下（动态规划版本）**（4星）
   - 亮点：代码简洁，直接定义 dp 状态转移，注释清晰
   - 代码核心：
     ```cpp
     for (int i = 1; i <= n; i++) {
       dp[i] = 0x7fffffff;
       for (int j = 1; j <= i; j++) {
         dp[i] = min(dp[i], dp[j - 1] + (p[i] - p[j]) * b + 2 * a);
       }
     }
     ```

3. **Expecto**（4星）
   - 亮点：状态定义巧妙，直接通过乘2处理浮点问题，代码极简
   - 代码核心：
     ```cpp
     for (int i=1;i<=n;i++){
         f[i]=6666666666;
         for (int j=0;j<i;j++)
             f[i]=min(f[i],f[j]+2*a+(x[i-1]-x[j])*b);
     }
     ```

### 关键思路总结
1. **排序预处理**：将奶牛位置排序，确保覆盖区间的连续性
2. **整数化处理**：将浮点费用计算转换为整数运算（如乘2处理）
3. **状态转移**：`dp[i] = min(dp[j-1] + 覆盖[j..i]的代价)`，其中覆盖代价通过区间端点差计算
4. **滚动优化**：通过一维数组滚动更新，降低空间复杂度

### 同类型拓展
类似区间覆盖问题可采用相同思路：
- 路灯布置问题（覆盖连续区间最小代价）
- 资源分段优化问题（如视频分段缓存）
- 时间区间调度中的最小设备数问题

### 推荐练习题
1. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220)（区间DP）
2. [P1095 守望者的逃离](https://www.luogu.com.cn/problem/P1095)（动态规划决策）
3. [P5017 摆渡车](https://www.luogu.com.cn/problem/P5017)（时间分段优化）

### 题解心得摘录
- **Parat_rooper**：通过观察发现二维状态冗余，优化为一维数组提升效率
- **_lmz_**：从暴力DFS到记忆化搜索的优化过程，强调避免重复计算的重要性
- **信守天下**：对比贪心与DP解法，指出贪心在特定数据下的局限性
- **scp233**：调试中发现浮点精度问题，采用整数运算规避误差

---
处理用时：63.56秒