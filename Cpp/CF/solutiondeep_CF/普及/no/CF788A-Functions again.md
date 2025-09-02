# 题目信息

# Functions again

## 题目描述

Something happened in Uzhlyandia again... There are riots on the streets... Famous Uzhlyandian superheroes Shean the Sheep and Stas the Giraffe were called in order to save the situation. Upon the arriving, they found that citizens are worried about maximum values of the Main Uzhlyandian Function $ f $ , which is defined as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788A/3dafed09a51e28ade00bc9bec53248a85d7ce6d3.png)In the above formula, $ 1<=l&lt;r<=n $ must hold, where $ n $ is the size of the Main Uzhlyandian Array $ a $ , and $ |x| $ means absolute value of $ x $ . But the heroes skipped their math lessons in school, so they asked you for help. Help them calculate the maximum value of $ f $ among all possible values of $ l $ and $ r $ for the given array $ a $ .

## 说明/提示

In the first sample case, the optimal value of $ f $ is reached on intervals $ [1,2] $ and $ [2,5] $ .

In the second case maximal value of $ f $ is reachable only on the whole array.

## 样例 #1

### 输入

```
5
1 4 2 3 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1 5 4 7
```

### 输出

```
6```

# AI分析结果



# Functions again 题目中文翻译

## 题目描述
Uzhlyandia 又发生了变故...街头爆发骚乱...著名超级英雄 Sheap the Sheep 和 Stas the Giraffe 被召来拯救危局。抵达后，他们发现市民们正担忧主函数 $f$ 的最大值，该函数定义如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788A/3dafed09a51e28ade00bc9bec53248a85d7ce6d3.png)

其中 $1 \le l < r \le n$，$n$ 是主数组 $a$ 的长度，$|x|$ 表示绝对值。英雄们需要你帮忙计算给定数组 $a$ 的所有可能 $l,r$ 中 $f$ 的最大值。

## 说明/提示
第一个样例中，最优解出现在区间 [1,2] 和 [2,5]。第二个样例最大值只能在整个数组取得。

## 样例 #1

### 输入
5  
1 4 2 3 1  

### 输出  
3

## 样例 #2

### 输入  
4  
1 5 4 7  

### 输出  
6

---

**算法分类**：动态规划

---

## 题解综合分析

### 核心思路对比
各题解均以预处理相邻元素差绝对值（差分数组）为基础，主要采用两种方法：
1. **动态规划**（主流解法）：维护两种状态分别表示当前位置符号的正负，通过状态转移方程求解最大子段和
2. **最大子段和变形**：通过奇偶起始位置分类，转化为两个独立的最大子段和问题

### 解决难点
1. **符号交替处理**：通过奇偶性判断符号交替规律
2. **状态转移设计**：需保证子段连续性，正确处理符号交替对累加的影响
3. **数值范围处理**：差值的绝对值可能极大（1e9级别），需使用long long

---

## 精选题解（评分≥4星）

### 1. mulberror（5星）
**核心亮点**：  
- 状态定义清晰：`f[i][0/1]` 表示以i结尾的正/负状态最大值
- 转移方程简洁：
  ```cpp
  f[i][0] = max(f[i-1][1]+d[i], d[i])  // 当前正号的最大值
  f[i][1] = max(f[i-1][0]-d[i], 0ll)   // 当前负号的最大值
  ```
- 时间复杂度O(n)，空间优化到线性

**关键代码**：
```cpp
for(int i = 1; i <= n; i++) {
    f[i][0] = max(f[i-1][1] + d[i], d[i]);
    f[i][1] = max(f[i-1][0] - d[i], 0ll);
    ans = max(ans, max(f[i][0], f[i][1]));
}
```

### 2. wind_whisper（4星）
**创新思路**：  
- 构造前缀和数组，通过维护最大/最小值求解
- 数学推导出公式：`ans = max(sum_r - min_prev_sum)`
- 单次遍历同时处理两种符号情况

**关键实现**：
```cpp
ll sum = 0, mi = 0, mx = 0;
for(int i=1; i<n; i++){
    sum += (i&1) ? d[i] : -d[i];  // 构造交替前缀和
    if(i&1) ans = max(ans, sum - mi);  // 奇数起始情况
    else ans = max(ans, mx - sum);     // 偶数起始情况
    mi = min(mi, sum);
    mx = max(mx, sum);
}
```

### 3. Disjoint_cat（4星）
**思维转换**：  
- 将问题拆分为两个独立的最大子段和问题
- 分别处理起始位置为奇数和偶数的情况
- 经典贪心解法变形，时间复杂度O(2n)

**核心代码**：
```cpp
// 奇数起始处理
t = mi = 0;
for(int i=1; i<n; i++) {
    if(i%2) t += d[i];
    else t -= d[i];
    ans1 = max(ans1, t - mi);
    mi = min(mi, t);
}
```

---

## 最优思路总结
**关键技巧**：  
1. **符号状态压缩**：通过两个状态维护交替符号的累加效果
2. **边界处理**：新子段的起始判断（`d[i]`直接作为初始值）
3. **空间优化**：滚动数组思想，仅保留前一状态

**同类型拓展**：  
- 最大子段和的符号约束变种（如交替符号、固定模式）
- 二维矩阵中的最大子区域和问题

---

## 推荐练习题目
1. P1115 最大子段和（基础模板）
2. P2642 双子序列最大和（双区间动态规划）
3. P1982 小朋友的数字（前缀最值应用）

---

## 调试心得摘录
1. **数据类型**："不开long long见祖宗"（OIerJiang_1017）
2. **边界处理**：`i < n`的循环控制，避免访问越界（差分数组长度n-1）
3. **状态初始化**：`f[0][1]`的0值处理保证空子段合法性（mulberror解法）

---
处理用时：69.68秒