# 题目信息

# Tokitsukaze and Strange Inequality

## 题目描述

Tokitsukaze has a permutation $ p $ of length $ n $ . Recall that a permutation $ p $ of length $ n $ is a sequence $ p_1, p_2, \ldots, p_n $ consisting of $ n $ distinct integers, each of which from $ 1 $ to $ n $ ( $ 1 \leq p_i \leq n $ ).

She wants to know how many different indices tuples $ [a,b,c,d] $ ( $ 1 \leq a < b < c < d \leq n $ ) in this permutation satisfy the following two inequalities:

 $ p_a < p_c $ and $ p_b > p_d $ . Note that two tuples $ [a_1,b_1,c_1,d_1] $ and $ [a_2,b_2,c_2,d_2] $ are considered to be different if $ a_1 \ne a_2 $ or $ b_1 \ne b_2 $ or $ c_1 \ne c_2 $ or $ d_1 \ne d_2 $ .

## 说明/提示

In the first test case, there are $ 3 $ different $ [a,b,c,d] $ tuples.

 $ p_1 = 5 $ , $ p_2 = 3 $ , $ p_3 = 6 $ , $ p_4 = 1 $ , where $ p_1 < p_3 $ and $ p_2 > p_4 $ satisfies the inequality, so one of $ [a,b,c,d] $ tuples is $ [1,2,3,4] $ .

Similarly, other two tuples are $ [1,2,3,6] $ , $ [2,3,5,6] $ .

## 样例 #1

### 输入

```
3
6
5 3 6 1 4 2
4
1 2 3 4
10
5 1 6 2 8 3 4 10 9 7```

### 输出

```
3
0
28```

# AI分析结果

### 题目内容中文重写
# Tokitsukaze与奇怪的不等式

## 题目描述
Tokitsukaze有一个长度为 $n$ 的排列 $p$。回想一下，长度为 $n$ 的排列 $p$ 是一个由 $n$ 个不同整数组成的序列 $p_1, p_2, \ldots, p_n$，每个整数的范围是从 $1$ 到 $n$（$1 \leq p_i \leq n$）。

她想知道在这个排列中有多少个不同的索引元组 $[a,b,c,d]$（$1 \leq a < b < c < d \leq n$）满足以下两个不等式：

$p_a < p_c$ 且 $p_b > p_d$。注意，如果 $a_1 \ne a_2$ 或 $b_1 \ne b_2$ 或 $c_1 \ne c_2$ 或 $d_1 \ne d_2$，则两个元组 $[a_1,b_1,c_1,d_1]$ 和 $[a_2,b_2,c_2,d_2]$ 被认为是不同的。

## 说明/提示
在第一个测试用例中，有 $3$ 个不同的 $[a,b,c,d]$ 元组。

$p_1 = 5$，$p_2 = 3$，$p_3 = 6$，$p_4 = 1$，其中 $p_1 < p_3$ 且 $p_2 > p_4$ 满足不等式，所以 $[a,b,c,d]$ 元组之一是 $[1,2,3,4]$。

同样，另外两个元组是 $[1,2,3,6]$，$[2,3,5,6]$。

## 样例 #1

### 输入
```
3
6
5 3 6 1 4 2
4
1 2 3 4
10
5 1 6 2 8 3 4 10 9 7
```

### 输出
```
3
0
28
```

### 综合分析与结论
- **思路对比**：大部分题解思路一致，通过枚举 $b$ 和 $c$ 来优化暴力枚举 $a,b,c,d$ 的 $O(n^4)$ 复杂度。部分题解使用前缀和、树状数组、线段树等数据结构辅助计算满足条件的 $a$ 和 $d$ 的数量。
- **算法要点**：
    - **前缀和**：预处理出不同区间内满足条件的数的个数，枚举 $b$ 和 $c$ 时直接利用前缀和计算答案。
    - **树状数组**：维护前缀或后缀信息，快速查询小于某个数的元素个数。
    - **线段树**：可用于统计区间内满足条件的元素个数，但复杂度相对较高。
- **解决难点**：核心难点在于优化枚举复杂度，通过枚举 $b$ 和 $c$，将问题转化为计算 $b$ 左边小于 $p_c$ 的数的个数和 $c$ 右边小于 $p_b$ 的数的个数，再利用乘法原理得到结果。

### 所选题解
- **作者：郑朝曦zzx（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细说明了预处理和枚举的过程，使用前缀和数组 $S$ 和 $L$ 分别记录不同区间内小于某个数的个数。
    - **核心代码**：
```cpp
for (int i = n; i >= 1; --i) {
    for (int j = i + 1; j <= n; ++j) {
        if (num[j] > num[i]) {
            S[i][j] = S[i + 1][j] + 1;
            L[i][j] = L[i][j - 1];
        } else {
            S[i][j] = S[i + 1][j];
            L[i][j] = L[i][j - 1] + 1;
        }
    }
}
for (int b = 2; b + 2 <= n; ++b)
    for (int c = b + 1; c + 1 <= n; ++c)
        ans += (LL)(S[1][c] - S[b][c]) * (LL)(L[b][n] - L[b][c]);
```
- **作者：cfkk（4星）**
    - **关键亮点**：思路明确，代码规范，详细解释了暴力和预处理两种思路，通过预处理 $sum1$ 和 $sum2$ 数组来记录每个数左边和右边小于它的数的个数。
    - **核心代码**：
```cpp
for(int i = 1; i <= n; i++){
    int s = 0;
    for(int j = 1; j <= n; j++){
        sum1[i][j] = s;
        s += v[j];
    }
    v[a[i]] = 1;
}
for(int i = n; i; i--){
    int s = 0;
    for(int j = 1; j <= n; j++){
        sum2[i][j] = s;
        s += v[j];
    }
    v[a[i]] = 1;
}
for(int i = 2; i <= n; i++)
    for(int j = i + 1; j <= n - 1; j++)
        res += sum1[i][a[j]] * sum2[j][a[i]];
```
- **作者：timmark（4星）**
    - **关键亮点**：结合树状数组和枚举 $b$、$c$ 的思路，详细说明了如何使用树状数组维护前缀信息，通过 $pre$ 和 $post$ 数组记录不同位置的前缀和后缀信息。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++) c1[i][j]=c1[i-1][j];
    modify1(i,a[i]+1,1);
}
for(int i=n;i;i--){
    for(int j=1;j<=n;j++) c2[i][j]=c2[i+1][j];
    modify2(i,a[i]+1,1);
}
for(int i=2;i<n-1;i++) for(int j=i+1;j<n;j++) ans+=sum1(i-1,a[j])*sum2(j+1,a[i]);
```

### 最优关键思路或技巧
- **枚举优化**：通过枚举 $b$ 和 $c$，将 $O(n^4)$ 的暴力枚举复杂度优化到 $O(n^2)$。
- **数据结构辅助**：使用前缀和、树状数组等数据结构，快速计算满足条件的 $a$ 和 $d$ 的数量。

### 可拓展之处
同类型题可拓展到更多元组的不等式问题，类似算法套路可用于处理涉及区间统计、元素比较的组合计数问题。

### 洛谷推荐题目
- [P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637)
- [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

### 个人心得摘录与总结
部分题解提到要注意开 `long long`，因为四元组的个数可能达到 $n^4$ 级别，不开会导致答案溢出。这提醒我们在处理计数问题时，要考虑结果的数据范围，避免因数据类型选择不当而出错。 

---
处理用时：40.62秒