# 题目信息

# Cobb

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ and an integer $ k $ . Find the maximum value of $ i \cdot j - k \cdot (a_i | a_j) $ over all pairs $ (i, j) $ of integers with $ 1 \le i < j \le n $ . Here, $ | $ is the [bitwise OR operator](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 说明/提示

Let $ f(i, j) = i \cdot j - k \cdot (a_i | a_j) $ .

In the first test case,

- $ f(1, 2) = 1 \cdot 2 - k \cdot (a_1 | a_2) = 2 - 3 \cdot (1 | 1) = -1 $ .
- $ f(1, 3) = 1 \cdot 3 - k \cdot (a_1 | a_3) = 3 - 3 \cdot (1 | 3) = -6 $ .
- $ f(2, 3) = 2 \cdot 3 - k \cdot (a_2 | a_3) = 6 - 3 \cdot (1 | 3) = -3 $ .

So the maximum is $ f(1, 2) = -1 $ .

In the fourth test case, the maximum is $ f(3, 4) = 12 $ .

## 样例 #1

### 输入

```
4
3 3
1 1 3
2 2
1 2
4 3
0 1 2 3
6 6
3 2 0 0 5 6```

### 输出

```
-1
-4
3
12```

# AI分析结果

### 题目内容重写

#### 题目描述

给定 $n$ 个整数 $a_1, a_2, \ldots, a_n$ 和一个整数 $k$。找到所有满足 $1 \le i < j \le n$ 的整数对 $(i, j)$ 中，$i \cdot j - k \cdot (a_i | a_j)$ 的最大值。其中，$|$ 是[按位或运算符](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

#### 说明/提示

设 $f(i, j) = i \cdot j - k \cdot (a_i | a_j)$。

在第一个测试用例中，

- $f(1, 2) = 1 \cdot 2 - k \cdot (a_1 | a_2) = 2 - 3 \cdot (1 | 1) = -1$。
- $f(1, 3) = 1 \cdot 3 - k \cdot (a_1 | a_3) = 3 - 3 \cdot (1 | 3) = -6$。
- $f(2, 3) = 2 \cdot 3 - k \cdot (a_2 | a_3) = 6 - 3 \cdot (1 | 3) = -3$。

所以最大值是 $f(1, 2) = -1$。

在第四个测试用例中，最大值是 $f(3, 4) = 12$。

#### 样例 #1

##### 输入

```
4
3 3
1 1 3
2 2
1 2
4 3
0 1 2 3
6 6
3 2 0 0 5 6
```

##### 输出

```
-1
-4
3
12
```

### 算法分类

枚举、位运算

### 题解分析与结论

该题的核心在于如何高效地枚举所有可能的 $(i, j)$ 对，并计算 $i \cdot j - k \cdot (a_i | a_j)$ 的最大值。由于直接暴力枚举的时间复杂度为 $O(n^2)$，在 $n$ 较大时会超时，因此需要优化。

#### 优化思路

1. **剪枝策略**：由于 $i \cdot j$ 的增长速度远快于 $k \cdot (a_i | a_j)$，因此可以只枚举 $i$ 和 $j$ 在接近 $n$ 的范围内，从而减少枚举次数。
2. **数学分析**：通过分析 $i \cdot j$ 和 $k \cdot (a_i | a_j)$ 的关系，可以得出 $i$ 和 $j$ 的取值范围，从而进一步减少枚举次数。

### 所选高星题解

#### 题解1：作者：ttq012 (赞：5)

**星级**：★★★★★  
**关键亮点**：通过数学分析，得出只需枚举后 $200$ 个左右的数字即可找到最大值，时间复杂度大幅降低。

**核心代码**：
```cpp
int pass = max(1, n - 248);
long long ans = -100000000000000LL;
for (int i = n; i >= pass; i --)
    for (int j = n; j >= pass; j --)
        if (i != j)
            ans = max(ans, 1LL * i * j - k * (a[i] | a[j]));
```
**实现思想**：通过限制 $i$ 和 $j$ 的枚举范围为 $n$ 到 $n-248$，减少了枚举次数，同时保证了答案的正确性。

#### 题解2：作者：NXYorz (赞：5)

**星级**：★★★★★  
**关键亮点**：通过固定 $j$，分析 $i$ 的取值范围，进一步优化了枚举范围，时间复杂度为 $O(nk)$。

**核心代码**：
```cpp
for(ll j = 1; j <= n; j++)
    for(ll i = max(1 , j - 2 * k); i < j; i++)
        ans = max(ans , i * j - k * (a[i] | a[j]));
```
**实现思想**：通过固定 $j$，并限制 $i$ 的取值范围为 $j-2k$ 到 $j-1$，减少了枚举次数。

#### 题解3：作者：wind_whisper (赞：2)

**星级**：★★★★  
**关键亮点**：通过分析 $i \cdot j$ 和 $k \cdot (a_i | a_j)$ 的关系，得出枚举 $j$ 的范围，时间复杂度为 $O(kn \log n)$。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=n;j>i&&1ll*i*j>mx;j--){
        mx=max(mx,calc(i,j));
    }
}
```
**实现思想**：通过限制 $j$ 的枚举范围，并在 $i \cdot j$ 小于当前最大值时提前退出，减少了不必要的计算。

### 最优关键思路或技巧

1. **剪枝策略**：通过限制 $i$ 和 $j$ 的枚举范围，减少不必要的计算。
2. **数学分析**：通过分析 $i \cdot j$ 和 $k \cdot (a_i | a_j)$ 的关系，得出更优的枚举范围。

### 可拓展之处

该题的优化思路可以应用于其他需要枚举大量组合的问题，尤其是当组合的某个部分增长较快时，可以通过数学分析减少枚举范围。

### 推荐题目

1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

### 个人心得摘录

- **ttq012**：通过数学分析得出只需枚举后 $200$ 个左右的数字，大大减少了计算量。
- **NXYorz**：固定 $j$ 并分析 $i$ 的取值范围，进一步优化了枚举范围。
- **wind_whisper**：通过分析 $i \cdot j$ 和 $k \cdot (a_i | a_j)$ 的关系，得出枚举 $j$ 的范围，减少了不必要的计算。

---
处理用时：43.68秒