# 题目信息

# K-Sort

## 题目描述

You are given an array of integers $ a $ of length $ n $ .

You can apply the following operation any number of times (maybe, zero):

- First, choose an integer $ k $ such that $ 1 \le k \le n $ and pay $ k + 1 $ coins.
- Then, choose exactly $ k $ indices such that $ 1 \le i_1 < i_2 < \ldots < i_k \le n $ .
- Then, for each $ x $ from $ 1 $ to $ k $ , increase $ a_{i_x} $ by $ 1 $ .

Find the minimum number of coins needed to make $ a $ non-decreasing. That is, $ a_1 \le a_2 \le \ldots \le a_n $ .

## 说明/提示

In the first test case, $ a $ is already sorted, so you don't have to spend any coins.

In the second test case, the optimal sequence of operations is:

- Choose $ k = 2 $ and the indices $ 2 $ and $ 5 $ : $ [ 2, \color{red}{1}, 4, 7, \color{red}{6} ] \rightarrow [2, 2, 4, 7, 7] $ . This costs $ 3 $ coins.

 It can be proven that it is not possible to make $ a $ non-decreasing by spending less than $ 3 $ coins.

## 样例 #1

### 输入

```
5
3
1 7 9
5
2 1 4 7 6
4
1 3 2 4
1
179
9
344 12 37 60 311 613 365 328 675```

### 输出

```
0
3
2
0
1821```

# AI分析结果



【题目翻译】
# K-排序

## 题目描述

给定一个长度为 $n$ 的整数数组 $a$。你可以进行任意次数的如下操作：

1. 选择一个整数 $k$（$1 \le k \le n$），支付 $k + 1$ 枚硬币
2. 选择恰好 $k$ 个索引 $i_1 < i_2 < ... < i_k$
3. 将这 $k$ 个索引对应的元素都增加 1

求使数组变为非递减序列（即满足 $a_1 \le a_2 \le ... \le a_n$）所需的最小硬币数。

## 输入样例与输出样例（略）

---

### 综合分析与结论

所有题解核心思路一致：  
1. **前缀最大值法**：遍历数组，维护前缀最大值。当当前元素小于前缀最大值时，计算需要增加的差值  
2. **代价公式**：总代价 = 所有差值的总和 + 最大单个差值  
3. **正确性证明**：最大差值决定操作次数下限，其他差值可在这些操作中覆盖  

关键技巧：  
- 将问题转化为差分计算，避免直接模拟操作  
- 通过一次线性扫描同时计算总增量和最大增量  

---

### 优质题解推荐

#### 1. 作者：Scean_Tong（★★★★★）
**核心亮点**：  
- 最简洁的实现，仅需维护两个变量（总增量和最大增量）  
- 代码可读性极佳，时间复杂度 O(n)

```cpp
int ans=0, mx_diff=0;
int mx=a[1];
for(int i=2;i<=n;i++) {
    mx = max(mx, a[i]);
    int diff = mx - a[i];
    mx_diff = max(mx_diff, diff);
    ans += diff;
}
cout << ans + mx_diff;
```

#### 2. 作者：luckyqwq（★★★★☆）
**优化过程**：  
- 初始版本使用排序，后优化为线性扫描  
- 给出完整代码框架，包含输入输出处理  
- 包含错误情况处理（如已有序的情况）

**个人心得**：  
> "这个代码的瓶颈在于排序，优化后变为线性。虽然没啥用，不过在有一些题目中压缩合并还是非常有用的。"

#### 3. 作者：fwtv_24（★★★★☆）
**代码亮点**：  
- 采用滚动变量而非数组存储前缀最大值  
- 包含特殊情况的快速判断（已有序情况）

```cpp
int ans=0, x=0, maxx=0;
for(int i=1; i<=n; i++){
    ans += max(0ll, maxx - a[i]);
    x = max(x, maxx - a[i]);
    maxx = max(maxx, a[i]);
}
cout << ans + x;
```

---

### 拓展与总结
**同类问题套路**：  
1. 差分数组处理区间增减问题（如 CF1526C2）  
2. 贪心思想结合极值特征（如最大差值决定下限）

**推荐练习题**：  
1. [P2947 Look Up](https://www.luogu.com.cn/problem/P2947)（前缀最大值应用）  
2. [CF1526C2 Potions](https://www.luogu.com.cn/problem/CF1526C2)（贪心+前缀处理）  
3. [P4552 IncDec Sequence](https://www.luogu.com.cn/problem/P4552)（差分数组经典题）

---
处理用时：65.44秒