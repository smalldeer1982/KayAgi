# 题目信息

# Vasya and Robot

## 题目描述

Vasya has $ n $ items lying in a line. The items are consecutively numbered by numbers from $ 1 $ to $ n $ in such a way that the leftmost item has number $ 1 $ , the rightmost item has number $ n $ . Each item has a weight, the $ i $ -th item weights $ w_{i} $ kilograms.

Vasya needs to collect all these items, however he won't do it by himself. He uses his brand new robot. The robot has two different arms — the left one and the right one. The robot can consecutively perform the following actions:

1. Take the leftmost item with the left hand and spend $ w_{i}·l $ energy units ( $ w_{i} $ is a weight of the leftmost item, $ l $ is some parameter). If the previous action was the same (left-hand), then the robot spends extra $ Q_{l} $ energy units;
2. Take the rightmost item with the right hand and spend $ w_{j}·r $ energy units ( $ w_{j} $ is a weight of the rightmost item, $ r $ is some parameter). If the previous action was the same (right-hand), then the robot spends extra $ Q_{r} $ energy units;

Naturally, Vasya wants to program the robot in a way that the robot spends as little energy as possible. He asked you to solve this problem. Your task is to find the minimum number of energy units robot spends to collect all items.

## 说明/提示

Consider the first sample. As $ l=r $ , we can take an item in turns: first from the left side, then from the right one and last item from the left. In total the robot spends $ 4·42+4·99+4·3=576 $ energy units.

The second sample. The optimal solution is to take one item from the right, then one item from the left and two items from the right. In total the robot spends $ (2·4)+(7·1)+(2·3)+(2·2+9)=34 $ energy units.

## 样例 #1

### 输入

```
3 4 4 19 1
42 3 99
```

### 输出

```
576
```

## 样例 #2

### 输入

```
4 7 2 3 9
1 2 3 4
```

### 输出

```
34
```

# AI分析结果



# 中文题目描述
## Vasya与机器人

### 题目描述

Vasya有$n$个物品排成一列，物品编号从$1$到$n$（左端为1，右端为n）。每个物品有重量$w_i$。机器人通过左右手依次取物品：

1. 左手取最左物品，消耗$w_i \cdot l$能量，若前一次也是左手操作则额外消耗$Q_l$
2. 右手取最右物品，消耗$w_j \cdot r$能量，若前一次也是右手操作则额外消耗$Q_r$

求收集所有物品的最小总能量。

### 输入输出样例

样例1：  
输入：  
3 4 4 19 1  
42 3 99  
输出：  
576  

样例2：  
输入：  
4 7 2 3 9  
1 2 3 4  
输出：  
34  

---

**算法分类**：贪心

---

## 题解分析与结论

### 题解对比与评分

1. **Gypsophila（★★★★★）**  
   **亮点**：  
   - 前缀和与后缀和的预处理巧妙  
   - 通过绝对差值判断连续操作次数  
   - 代码结构清晰，时间复杂度$O(n)$  

2. **DiDi123（★★★★☆）**  
   **亮点**：  
   - 动态维护左右区间和，节省空间  
   - 使用辅助函数计算额外消耗，逻辑明确  
   **心得**：  
   > "第一眼想到区间DP，但数据规模要求线性解法，转而通过贪心性质分析断点结构"

3. **PCCP（★★★★☆）**  
   **亮点**：  
   - 简洁的数学表达式计算额外消耗  
   - 对交替操作的数学抽象（$2i-n$判断）  

---

### 核心思路

**关键策略**：  
最优解必然存在一个分割点$x$，使得前$x$个物品全由左手取，剩余由右手取。通过枚举所有分割点，结合以下要素计算最小值：  
1. **基础消耗**：前缀和×左手系数 + 后缀和×右手系数  
2. **额外消耗**：当左右操作次数差≥2时，计算连续操作的惩罚次数  

**实现技巧**：  
- 预处理前缀和数组`pre`与后缀和数组`suf`  
- 利用绝对值差公式`(abs(R-L)-1)*Q`计算额外消耗  

---

### 核心代码实现

**Gypsophila的代码核心逻辑**：  
```cpp
for(int i = 0; i <= n; i++) {
    int L = i, R = n - i;
    int sum = pre[i]*l + suf[i+1]*r; // 基础消耗
    if(abs(R-L) >= 2) { // 需要连续操作
        sum += (R > L ? qr : ql) * (abs(R-L)-1);
    }
    ans = min(ans, sum);
}
```

**DiDi123的动态维护技巧**：  
```cpp
int extra(int x, int y) {
    if(x == y) return 0;
    return (x < y) ? (y-x-1)*qr : (x-y-1)*ql;
}

// 主循环动态更新区间和
for(int i=0; i<=n; i++) {
    lsum += w[i], rsum -= w[i];
    ans = min(ans, lsum*l + rsum*r + extra(i, n-i));
}
```

---

### 拓展思路

**同类问题套路**：  
- 序列分段决策问题（如P1220 关路灯）  
- 贪心结合前缀和的最优化问题（如P2280 [HNOI2003] 激光炸弹）  

**推荐练习题目**：  
1. P1220 关路灯（贪心+区间DP）  
2. P1094 纪念品分组（双指针贪心）  
3. P2280 激光炸弹（前缀和优化）  

---

**总结**：通过分解问题为前缀后缀两部分，利用贪心性质避免暴力枚举，结合数学公式处理连续操作的惩罚，是该类问题的典型解决范式。

---
处理用时：182.50秒