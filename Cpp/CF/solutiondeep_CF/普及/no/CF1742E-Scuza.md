# 题目信息

# Scuza

## 题目描述

Timur has a stairway with $ n $ steps. The $ i $ -th step is $ a_i $ meters higher than its predecessor. The first step is $ a_1 $ meters higher than the ground, and the ground starts at $ 0 $ meters.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1742E/1bd007a2ef6a288af14a4e7592f626054d160b81.png)The stairs for the first test case.Timur has $ q $ questions, each denoted by an integer $ k_1, \dots, k_q $ . For each question $ k_i $ , you have to print the maximum possible height Timur can achieve by climbing the steps if his legs are of length $ k_i $ . Timur can only climb the $ j $ -th step if his legs are of length at least $ a_j $ . In other words, $ k_i \geq a_j $ for each step $ j $ climbed.

Note that you should answer each question independently.

## 说明/提示

Consider the first test case, pictured in the statement.

- If Timur's legs have length $ 1 $ , then he can only climb stair $ 1 $ , so the highest he can reach is $ 1 $ meter.
- If Timur's legs have length $ 2 $ or $ 4 $ , then he can only climb stairs $ 1 $ , $ 2 $ , and $ 3 $ , so the highest he can reach is $ 1+2+1=4 $ meters.
- If Timur's legs have length $ 9 $ or $ 10 $ , then he can climb the whole staircase, so the highest he can reach is $ 1+2+1+5=9 $ meters.

 In the first question of the second test case, Timur has no legs, so he cannot go up even a single step. :(

## 样例 #1

### 输入

```
3
4 5
1 2 1 5
1 2 4 9 10
2 2
1 1
0 1
3 1
1000000000 1000000000 1000000000
1000000000```

### 输出

```
1 4 4 9 9 
0 2 
3000000000```

# AI分析结果

### 题目内容重写

**题目描述**

Timur有一个有$n$级台阶的楼梯。第$i$级台阶比前一级高$a_i$米。第一级台阶比地面高$a_1$米，地面高度为$米。

Timur有$q$个问题，每个问题用一个整数$k_1, \dots, k_q$表示。对于每个问题$k_i$，你需要打印出Timur在腿长为$k_i$的情况下，能够达到的最大高度。Timur只能爬上第$j$级台阶，如果他的腿长至少为$a_j$。换句话说，对于每个被爬上的台阶$j$，$k_i \geq a_j$。

注意，每个问题应该独立回答。

**说明/提示**

考虑第一个测试用例，如题目描述中的图所示。

- 如果Timur的腿长为$1$，那么他只能爬上第1级台阶，所以他能达到的最大高度是$1$米。
- 如果Timur的腿长为$2$或$4$，那么他只能爬上第1、2、3级台阶，所以他能达到的最大高度是$1+2+1=4$米。
- 如果Timur的腿长为$9$或$10$，那么他可以爬上整个楼梯，所以他能达到的最大高度是$1+2+1+5=9$米。

在第二个测试用例的第一个问题中，Timur没有腿，所以他甚至不能爬上任何一级台阶。

**样例输入**

```
3
4 5
1 2 1 5
1 2 4 9 10
2 2
1 1
0 1
3 1
1000000000 1000000000 1000000000
1000000000
```

**样例输出**

```
1 4 4 9 9 
0 2 
3000000000
```

### 算法分类
二分、前缀和

### 题解分析与结论

该题的核心在于如何高效地回答每个查询，即给定腿长$k$，找到能够爬到的最高台阶。由于直接遍历每个查询会超时，因此需要优化。大多数题解都采用了**二分查找**和**前缀和**的技巧来优化查询过程。

- **二分查找**：由于台阶的高度差是单调不递减的，因此可以通过二分查找来确定在给定腿长$k$下能够爬到的最高台阶。
- **前缀和**：通过预处理台阶高度的前缀和，可以在$O(1)$时间内计算出任意台阶的总高度。

### 评分较高的题解

#### 题解1：作者：szhqwq (赞：7)
**星级：5星**
**关键亮点**：
- 使用了二分查找和前缀和的组合，思路清晰，代码简洁。
- 通过预处理数组$a$和$s$，分别存储每个台阶的最大高度差和前缀和，使得查询时间复杂度降低到$O(\log n)$。

**核心代码**：
```cpp
int l = 0, r = n + 1;
while (l < r) {
    int mid = l + r >> 1;
    if (a[mid] <= k) l = mid + 1;
    else r = mid;
}
cout << s[l - 1] << " ";
```

#### 题解2：作者：CQ_Bab (赞：3)
**星级：4星**
**关键亮点**：
- 同样使用了二分查找和前缀和的组合，代码结构清晰。
- 通过维护一个数组$a$来存储每个台阶的最大高度差，便于二分查找。

**核心代码**：
```cpp
int l = 0, r = n;
while (l <= r) {
    int mid = l + r >> 1;
    if (a[mid] > k) r = mid - 1;
    else l = mid + 1;
}
cout << pre[l - 1] << " ";
```

#### 题解3：作者：hu_led (赞：1)
**星级：4星**
**关键亮点**：
- 使用了二分查找和前缀和的组合，代码结构清晰。
- 通过预处理数组$re$和$sum$，分别存储每个台阶的最大高度差和前缀和，使得查询时间复杂度降低到$O(\log n)$。

**核心代码**：
```cpp
int l = 0, r = n + 1;
while (l < r) {
    int mid = (l + r) >> 1;
    if (re[mid] <= k) l = mid + 1;
    else r = mid;
}
printf("%lld ", sum[l - 1]);
```

### 最优关键思路或技巧
- **二分查找**：利用台阶高度差的单调性，通过二分查找快速确定能够爬到的最高台阶。
- **前缀和**：通过预处理台阶高度的前缀和，快速计算任意台阶的总高度。

### 可拓展之处
- 类似的问题可以扩展到其他具有单调性的场景，例如在某个范围内查找满足条件的最值。
- 前缀和技巧可以广泛应用于需要快速计算区间和的场景。

### 推荐题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)

### 个人心得摘录
- **调试经历**：在二分查找时，注意边界条件的处理，避免出现死循环或越界的情况。
- **踩坑教训**：预处理数组时，确保数组的大小足够，避免数组越界。
- **顿悟感想**：通过二分查找和前缀和的组合，可以大大优化查询时间复杂度，提高代码效率。

---
处理用时：38.74秒