# 题目信息

# Electrification

## 题目描述

At first, there was a legend related to the name of the problem, but now it's just a formal statement.

You are given $ n $ points $ a_1, a_2, \dots, a_n $ on the $ OX $ axis. Now you are asked to find such an integer point $ x $ on $ OX $ axis that $ f_k(x) $ is minimal possible.

The function $ f_k(x) $ can be described in the following way:

- form a list of distances $ d_1, d_2, \dots, d_n $ where $ d_i = |a_i - x| $ (distance between $ a_i $ and $ x $ );
- sort list $ d $ in non-descending order;
- take $ d_{k + 1} $ as a result.

If there are multiple optimal answers you can print any of them.

## 样例 #1

### 输入

```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4
```

### 输出

```
3
500000000
4
```

# AI分析结果



# Electrification

## 题目描述

给定 $ n $ 个在 $ OX $ 轴上的点 $ a_1, a_2, \dots, a_n $，寻找整数点 $ x $ 使得函数 $ f_k(x) $ 最小。

函数 $ f_k(x) $ 定义如下：
1. 计算每个点与 $ x $ 的绝对距离 $ d_i = |a_i - x| $
2. 将 $ d $ 升序排序
3. 取排序后第 $ k+1 $ 个元素作为结果

若存在多个最优解，输出任意一个即可。

## 样例输入输出

### 输入
```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4
```

### 输出
```
3
500000000
4
```

---

## 题解综合分析

### 关键思路
最优解法的核心在于发现：**第 $ k+1 $ 小的距离对应的点必定来自原数组的某个连续区间**。通过枚举所有长度为 $ k+1 $ 的连续区间，找到区间端点差最小的区间，其中点即为最优解。

### 最优题解

#### 1. wanghaoyu120104（五星）
**亮点**：直接遍历所有连续区间，时间复杂度 $ O(n) $，代码简洁高效。
```cpp
for(int i=1;i<=n-k;i++) {
    if(mi>a[i+k]-a[i]) {
        mi=a[i+k]-a[i];
        ans=a[i]+mi/2;
    }
}
```
**思路**：遍历每个左端点，计算连续 $ k+1 $ 个点的区间长度，记录最小区间的中点。

#### 2. SamuelXuch（四星）
**亮点**：同线性遍历思路，代码实现清晰。
```cpp
for(int i=1;i<=n-k;i++) {
    if(ans>a[i+k]-a[i]){
        ans=a[i+k]-a[i];
        pos=a[i]+ans/2;
    }
}
```
**思路**：与五星解法一致，变量命名更直观。

#### 3. cosf（四星）
**亮点**：补充了区间端点的数学推导，强化了思路正确性。
```cpp
x = floor((a[i-k] + a[i])/2)
```
**思路**：通过数学证明最优解位于区间中点，提升算法可信度。

---

## 最优解法总结
**核心技巧**：  
1. **连续区间性质**：前 $ k+1 $ 小的距离对应的点必为连续区间。
2. **中点最优性**：连续区间的最优解一定位于区间中点。
3. **线性扫描**：遍历所有可能区间，维护最小区间长度。

**代码实现要点**：
1. 排序原数组保证连续性。
2. 遍历时仅需比较区间端点差。
3. 直接计算中点无需复杂运算。

---

## 相似题目推荐
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)  
   **相似点**：利用排序后数组的连续性性质，双指针维护区间。

2. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)  
   **相似点**：滑动窗口寻找满足条件的最小区间。

3. [P2217 [HAOI2007] 分割矩阵](https://www.luogu.com.cn/problem/P2217)  
   **相似点**：通过二分答案结合区间划分验证解的可行性。

---
处理用时：78.78秒