# 题目信息

# Binary Search

## 题目描述

Andrey thinks he is truly a successful developer, but in reality he didn't know about the binary search algorithm until recently. After reading some literature Andrey understood that this algorithm allows to quickly find a certain number $ x $ in an array. For an array $ a $ indexed from zero, and an integer $ x $ the pseudocode of the algorithm is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1436C/98f912f0399d121a6bf6605fa8d3ccffae3c8c30.png)Note that the elements of the array are indexed from zero, and the division is done in integers (rounding down).

Andrey read that the algorithm only works if the array is sorted. However, he found this statement untrue, because there certainly exist unsorted arrays for which the algorithm find $ x $ !

Andrey wants to write a letter to the book authors, but before doing that he must consider the permutations of size $ n $ such that the algorithm finds $ x $ in them. A permutation of size $ n $ is an array consisting of $ n $ distinct integers between $ 1 $ and $ n $ in arbitrary order.

Help Andrey and find the number of permutations of size $ n $ which contain $ x $ at position $ pos $ and for which the given implementation of the binary search algorithm finds $ x $ (returns true). As the result may be extremely large, print the remainder of its division by $ 10^9+7 $ .

## 说明/提示

All possible permutations in the first test case: $ (2, 3, 1, 4) $ , $ (2, 4, 1, 3) $ , $ (3, 2, 1, 4) $ , $ (3, 4, 1, 2) $ , $ (4, 2, 1, 3) $ , $ (4, 3, 1, 2) $ .

## 样例 #1

### 输入

```
4 1 2```

### 输出

```
6```

## 样例 #2

### 输入

```
123 42 24```

### 输出

```
824071958```

# AI分析结果

### 题目内容重写

#### 题目描述

Andrey 认为他是一个成功的开发者，但实际上他直到最近才知道二分查找算法。在阅读了一些文献后，Andrey 明白了这个算法可以快速在数组中找到某个数 $x$。对于一个从零开始索引的数组 $a$ 和一个整数 $x$，算法的伪代码如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1436C/98f912f0399d121a6bf6605fa8d3ccffae3c8c30.png)

注意，数组的元素从零开始索引，并且除法是整数除法（向下取整）。

Andrey 读到这个算法只有在数组有序时才能工作。然而，他发现这个说法并不完全正确，因为确实存在一些无序数组，算法也能找到 $x$！

Andrey 想给这本书的作者写一封信，但在那之前，他必须考虑大小为 $n$ 的排列，使得算法能在这些排列中找到 $x$。一个大小为 $n$ 的排列是一个由 $1$ 到 $n$ 之间的 $n$ 个不同整数组成的数组，顺序任意。

帮助 Andrey 找出大小为 $n$ 的排列中，包含 $x$ 在位置 $pos$ 并且给定的二分查找算法实现能找到 $x$（返回 true）的排列数量。由于结果可能非常大，请输出其对 $10^9+7$ 取模的结果。

#### 说明/提示

第一个测试用例中所有可能的排列：$(2, 3, 1, 4)$，$(2, 4, 1, 3)$，$(3, 2, 1, 4)$，$(3, 4, 1, 2)$，$(4, 2, 1, 3)$，$(4, 3, 1, 2)$。

#### 样例 #1

##### 输入

```
4 1 2
```

##### 输出

```
6
```

#### 样例 #2

##### 输入

```
123 42 24
```

##### 输出

```
824071958
```

### 算法分类
组合数学

### 题解分析与结论

这道题的核心在于理解二分查找的过程，并利用组合数学的方法计算满足条件的排列数。所有题解都通过模拟二分查找过程，确定在查找过程中哪些位置必须小于或大于 $x$，然后利用排列数公式计算最终结果。

### 精选题解

#### 题解1：作者：tuzhewen (5星)

**关键亮点**：
- 清晰地解释了二分查找过程中哪些位置必须小于或大于 $x$。
- 使用排列数公式 $P_{sum1}^{cnt1} \times P_{sum2}^{cnt2} \times (n-cnt1-cnt2-1)!$ 计算结果。
- 代码实现简洁，使用了预处理阶乘和逆元来优化计算。

**核心代码**：
```cpp
ll ans = 1ll * P(x - 1, cnt1) * P(n - x, cnt2) % mod * fac[n - cnt1 - cnt2 - 1] % mod;
```

#### 题解2：作者：XL4453 (4星)

**关键亮点**：
- 通过模拟二分查找过程，确定需要小于或大于 $x$ 的位置数量。
- 使用排列数公式 $\dfrac{c!}{(c-a)!} \times \dfrac{d!}{(d-b)!} \times (c+d-a-b)!$ 计算结果。
- 代码实现直接，使用了循环计算排列数。

**核心代码**：
```cpp
for(int i = x - a; i <= x - 1; i++) ans = (ans * i) % MOD;
for(int i = n - x - b + 1; i <= n - x; i++) ans = (ans * i) % MOD;
for(int i = 1; i <= n - 1 - a - b; i++) ans = (ans * i) % MOD;
```

#### 题解3：作者：vеctorwyx (4星)

**关键亮点**：
- 详细解释了二分查找过程中每个位置与 $x$ 的关系。
- 使用排列数公式 $\dfrac{(x-1)!}{(x-a-1)!} \times \dfrac{(n-x)!}{(n-x-b)!} \times (n-a-b-1)!$ 计算结果。
- 代码实现清晰，使用了循环计算排列数。

**核心代码**：
```cpp
for(int i = x - 1; i >= x - lo; i--) ans = (ans * 1ll * i) % p;
for(int i = n - x; i >= n - x - hi + 1; i--) ans = (ans * 1ll * i) % p;
for(int i = 1; i <= n - hi - lo - 1; i++) ans = (ans * 1ll * i) % p;
```

### 最优关键思路与技巧

1. **模拟二分查找过程**：通过模拟二分查找，确定哪些位置必须小于或大于 $x$。
2. **排列数公式**：利用排列数公式计算满足条件的排列数，注意预处理阶乘和逆元以优化计算。
3. **组合数学**：理解并应用组合数学中的排列数公式，确保计算结果正确。

### 拓展思路

类似的问题可以通过模拟特定算法的过程，并结合组合数学的方法来解决。例如，在查找、排序等算法中，可以通过模拟过程来确定某些位置的约束条件，然后利用排列组合的方法计算满足条件的排列数。

### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1495 【模板】快速幂](https://www.luogu.com.cn/problem/P1495)
3. [P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)

---
处理用时：38.19秒