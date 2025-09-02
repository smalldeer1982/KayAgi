# 题目信息

# Dima and Two Sequences

## 题目描述

Little Dima has two sequences of points with integer coordinates: sequence $ (a_{1},1),(a_{2},2),...,(a_{n},n) $ and sequence $ (b_{1},1),(b_{2},2),...,(b_{n},n) $ .

Now Dima wants to count the number of distinct sequences of points of length $ 2·n $ that can be assembled from these sequences, such that the $ x $ -coordinates of points in the assembled sequence will not decrease. Help him with that. Note that each element of the initial sequences should be used exactly once in the assembled sequence.

Dima considers two assembled sequences $ (p_{1},q_{1}),(p_{2},q_{2}),...,(p_{2·n},q_{2·n}) $ and $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{2·n},y_{2·n}) $ distinct, if there is such $ i $ $ (1<=i<=2·n) $ , that $ (p_{i},q_{i})≠(x_{i},y_{i}) $ .

As the answer can be rather large, print the remainder from dividing the answer by number $ m $ .

## 说明/提示

In the first sample you can get only one sequence: $ (1,1),(2,1) $ .

In the second sample you can get such sequences : $ (1,1),(2,2),(2,1),(3,2) $ ; $ (1,1),(2,1),(2,2),(3,2) $ . Thus, the answer is $ 2 $ .

## 样例 #1

### 输入

```
1
1
2
7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 2
2 3
11
```

### 输出

```
2
```

# AI分析结果



# Dima and Two Sequences

## 题目描述

小Dima有两个整数坐标点序列：序列 $ (a_{1},1),(a_{2},2),...,(a_{n},n) $ 和序列 $ (b_{1},1),(b_{2},2),...,(b_{n},n) $ 。

现在Dima想计算能组装出的不同序列数量。组装后的序列必须满足：点的x坐标非递减，且每个初始序列中的元素必须恰好使用一次。两个序列被视为不同当且仅当至少存在一个位置的点不同。

由于答案可能很大，输出结果对 $ m $ 取模后的值。

## 说明/提示

第一个样例只能得到唯一序列：$ (1,1),(2,1) $。

第二个样例有两种可能序列：$ (1,1),(2,2),(2,1),(3,2) $ 和 $ (1,1),(2,1),(2,2),(3,2) $，故答案为2。

---

**算法分类**：组合数学

---

### 题解分析与结论
核心问题转化为：处理x坐标相同的点的全排列，并消除因相同点对顺序交换导致的重复计数。关键点在于：
1. 统计每个x值的总出现次数
2. 计算重复y值的对数
3. 总方案数为各x值的阶乘乘积除以$2^{重复对数}$

---

### 优质题解推荐

#### 1. Allanljx（4星）
**关键亮点**：  
- 使用双map分别统计x出现次数和重复y对数
- 在阶乘计算中动态处理2的幂次，避免逆元问题  
**核心代码**：
```cpp
int get_sum(int maxn, int cnt) {
    int sum = 1;
    for(int i=1; i<=maxn; i++) {
        if(i%2 == 0 && cnt) sum = sum*i/2%mod, cnt--;
        else sum = sum*i%mod;
    }
    return sum;
}
```
**实现思想**：对每个x值的阶乘计算时，每遇到偶数就尝试除以2，直到处理完所有重复对。

#### 2. QWQ_123（4星）
**关键亮点**：  
- 合并两个序列后统一排序处理
- 通过遍历检测相邻重复点计算重复对数  
**核心代码**：
```cpp
sort(a + 1, a + 1 + 2 * n);
for(int i=1; i<=2*n; ) {
    int cnt=1, cc=0;
    while(a[i+1].first == a[i].first) {
        if(a[i].second == a[i+1].second) cc++;
        cnt++; i++;
    }
    // 处理阶乘和2的幂
}
```
**实现思想**：合并序列后排序，通过连续相同x值的区间统计总数量和重复对数。

---

### 关键思路总结
1. **合并处理**：将两个序列合并后统一处理，避免重复计数
2. **动态除2技巧**：在阶乘过程中直接消去2的幂次，解决模数非质数时无法用逆元的问题
3. **重复对检测**：通过比较相邻元素的y值统计重复对数

---

### 拓展建议
类似题目可关注以下方向：
1. 涉及重复元素全排列的去重计算
2. 在模数非质数时的分数取模技巧
3. 合并排序处理多维数据问题

---

### 推荐习题
1. [P1495 曹冲养猪](https://www.luogu.com.cn/problem/P1495)（中国剩余定理）
2. [P3223 排队](https://www.luogu.com.cn/problem/P3223)（组合数学+高精度）
3. [P3773 不同子序列](https://www.luogu.com.cn/problem/P3773)（字符串哈希+组合数学）

---
处理用时：51.69秒