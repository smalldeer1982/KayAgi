# 题目信息

# Effects of Anti Pimples

## 题目描述

Chaneka has an array $ [a_1,a_2,\ldots,a_n] $ . Initially, all elements are white. Chaneka will choose one or more different indices and colour the elements at those chosen indices black. Then, she will choose all white elements whose indices are multiples of the index of at least one black element and colour those elements green. After that, her score is the maximum value of $ a_i $ out of all black and green elements.

There are $ 2^n-1 $ ways for Chaneka to choose the black indices. Find the sum of scores for all possible ways Chaneka can choose the black indices. Since the answer can be very big, print the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, below are the $ 15 $ possible ways to choose the black indices:

- Index $ 1 $ is black. Indices $ 2 $ , $ 3 $ , and $ 4 $ are green. Maximum value among them is $ 19 $ .
- Index $ 2 $ is black. Index $ 4 $ is green. Maximum value among them is $ 14 $ .
- Index $ 3 $ is black. Maximum value among them is $ 19 $ .
- Index $ 4 $ is black. Maximum value among them is $ 9 $ .
- Indices $ 1 $ and $ 2 $ are black. Indices $ 3 $ and $ 4 $ are green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ and $ 3 $ are black. Indices $ 2 $ and $ 4 $ are green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ and $ 4 $ are black. Indices $ 2 $ and $ 3 $ are green. Maximum value among them is $ 19 $ .
- Indices $ 2 $ and $ 3 $ are black. Index $ 4 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 2 $ and $ 4 $ are black. Maximum value among them is $ 14 $ .
- Indices $ 3 $ and $ 4 $ are black. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 2 $ , and $ 3 $ are black. Index $ 4 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 2 $ , and $ 4 $ are black. Index $ 3 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 3 $ , and $ 4 $ are black. Index $ 2 $ is green. Maximum value among them is $ 19 $ .
- Indices $ 2 $ , $ 3 $ , and $ 4 $ are black. Maximum value among them is $ 19 $ .
- Indices $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ are black. Maximum value among them is $ 19 $ .

The total sum is $ 19+14+19+9+19+19+19+19+14+19+19+19+19+19+19 = 265 $ .

## 样例 #1

### 输入

```
4
19 14 19 9```

### 输出

```
265```

## 样例 #2

### 输入

```
1
0```

### 输出

```
0```

## 样例 #3

### 输入

```
15
90000 9000 99000 900 90900 9900 99900 90 90090 9090 99090 990 90990 9990 99990```

### 输出

```
266012571```

# AI分析结果

### 题目内容重写

**题目描述**

Chaneka 有一个数组 $[a_1, a_2, \ldots, a_n]$。最初，所有元素都是白色的。Chaneka 将选择一个或多个不同的索引，并将这些索引处的元素涂成黑色。然后，她将选择所有白色元素，这些元素的索引是至少一个黑色元素索引的倍数，并将这些元素涂成绿色。之后，她的得分是所有黑色和绿色元素中 $a_i$ 的最大值。

共有 $2^n - 1$ 种选择黑色索引的方式。求所有可能选择黑色索引的方式得分的总和。由于答案可能非常大，请输出答案对 $998244353$ 取模的结果。

**说明/提示**

在第一个样例中，共有 $15$ 种选择黑色索引的方式：

- 索引 $1$ 是黑色。索引 $2$、$3$ 和 $4$ 是绿色。它们的最大值是 $19$。
- 索引 $2$ 是黑色。索引 $4$ 是绿色。它们的最大值是 $14$。
- 索引 $3$ 是黑色。它们的最大值是 $19$。
- 索引 $4$ 是黑色。它们的最大值是 $9$。
- 索引 $1$ 和 $2$ 是黑色。索引 $3$ 和 $4$ 是绿色。它们的最大值是 $19$。
- 索引 $1$ 和 $3$ 是黑色。索引 $2$ 和 $4$ 是绿色。它们的最大值是 $19$。
- 索引 $1$ 和 $4$ 是黑色。索引 $2$ 和 $3$ 是绿色。它们的最大值是 $19$。
- 索引 $2$ 和 $3$ 是黑色。索引 $4$ 是绿色。它们的最大值是 $19$。
- 索引 $2$ 和 $4$ 是黑色。它们的最大值是 $14$。
- 索引 $3$ 和 $4$ 是黑色。它们的最大值是 $19$。
- 索引 $1$、$2$ 和 $3$ 是黑色。索引 $4$ 是绿色。它们的最大值是 $19$。
- 索引 $1$、$2$ 和 $4$ 是黑色。索引 $3$ 是绿色。它们的最大值是 $19$。
- 索引 $1$、$3$ 和 $4$ 是黑色。索引 $2$ 是绿色。它们的最大值是 $19$。
- 索引 $2$、$3$ 和 $4$ 是黑色。它们的最大值是 $19$。
- 索引 $1$、$2$、$3$ 和 $4$ 是黑色。它们的最大值是 $19$。

总得分为 $19+14+19+9+19+19+19+19+14+19+19+19+19+19+19 = 265$。

**样例 #1**

### 输入

```
4
19 14 19 9
```

### 输出

```
265
```

**样例 #2**

### 输入

```
1
0
```

### 输出

```
0
```

**样例 #3**

### 输入

```
15
90000 9000 99000 900 90900 9900 99900 90 90090 9090 99090 990 90990 9990 99990
```

### 输出

```
266012571
```

### 算法分类
组合数学

### 题解分析与结论

本题的核心在于计算每个元素在所有可能的黑色索引选择方式中对得分的贡献。通过预处理每个索引及其倍数的最大值，将问题转化为求所有子序列的最大值之和。最终通过排序和组合数学的方法计算每个元素的贡献。

### 精选题解

#### 1. 作者：definieren (赞：19)
**星级：5**
**关键亮点：**
- 通过预处理每个索引及其倍数的最大值，将问题转化为求所有子序列的最大值之和。
- 使用排序和组合数学的方法，计算每个元素的贡献。
- 时间复杂度为 $O(n \log n)$，代码简洁高效。

**核心代码：**
```cpp
for (int i = 1; i <= n; i ++)
    for (int j = i; j <= n; j += i)
        cmax(a[i], a[j]);
sort(a + 1, a + n + 1), pw[0] = 1;
for (int i = 1; i <= n; i ++) pw[i] = add(pw[i - 1], pw[i - 1]);
for (int i = 1; i <= n; i ++) cadd(ans, int(1ll * a[i] * pw[i - 1] % MOD));
```

#### 2. 作者：lwx20211103 (赞：11)
**星级：4**
**关键亮点：**
- 详细解释了题意和解题思路，适合初学者理解。
- 通过预处理和排序，计算每个元素的贡献。
- 时间复杂度为 $O(n \log n)$，代码清晰。

**核心代码：**
```cpp
for (int i = 1; i <= n; i ++)
    for (int j = i; j <= n; j += i)
        maxsum[i] = max(maxsum[i], nums[j]);
sort(maxsum + 1, maxsum + 1 + n, cmp);
for (int i = n - 1; i >= 0; i --)
    ans = (ans + qpow(2, i) * maxsum[n - i]) % mod;
```

#### 3. 作者：aCssen (赞：5)
**星级：4**
**关键亮点：**
- 通过预处理和排序，计算每个元素的贡献。
- 使用组合数学的方法，计算每个元素的贡献。
- 时间复杂度为 $O(n \log n)$，代码简洁。

**核心代码：**
```cpp
for (int i = 1; i <= n; i ++)
    for (int j = i; j <= n; j += i)
        f[i] = max(f[i], a[j]);
sort(f + 1, f + n + 1);
for (int i = n; i >= 1; i --)
    ans = (ans + (f[i] * p[i - 1]) % MOD) % MOD;
```

### 最优关键思路
- 预处理每个索引及其倍数的最大值，将问题转化为求所有子序列的最大值之和。
- 使用排序和组合数学的方法，计算每个元素的贡献。

### 拓展思路
- 类似的问题可以通过预处理和组合数学的方法来解决，例如求所有子序列的最大值、最小值等。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1045 最大子段和](https://www.luogu.com.cn/problem/P1045)
3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

### 个人心得摘录
- **definieren**：通过预处理和排序，将问题转化为求所有子序列的最大值之和，代码简洁高效。
- **lwx20211103**：详细解释了题意和解题思路，适合初学者理解，代码清晰。
- **aCssen**：使用组合数学的方法，计算每个元素的贡献，代码简洁。

---
处理用时：44.95秒