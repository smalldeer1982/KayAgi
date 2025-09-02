# 题目信息

# Many Perfect Squares

## 题目描述

You are given a set $ a_1, a_2, \ldots, a_n $ of distinct positive integers.

We define the squareness of an integer $ x $ as the number of perfect squares among the numbers $ a_1 + x, a_2 + x, \ldots, a_n + x $ .

Find the maximum squareness among all integers $ x $ between $ 0 $ and $ 10^{18} $ , inclusive.

Perfect squares are integers of the form $ t^2 $ , where $ t $ is a non-negative integer. The smallest perfect squares are $ 0, 1, 4, 9, 16, \ldots $ .

## 说明/提示

In the first test case, for $ x = 0 $ the set contains two perfect squares: $ 1 $ and $ 4 $ . It is impossible to obtain more than two perfect squares.

In the second test case, for $ x = 3 $ the set looks like $ 4, 9, 16, 25, 100 $ , that is, all its elements are perfect squares.

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
5
1 6 13 22 97
1
100
5
2 5 10 17 26```

### 输出

```
2
5
1
2```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一组不同的正整数 $a_1, a_2, \ldots, a_n$。

我们定义整数 $x$ 的“平方度”为在数列 $a_1 + x, a_2 + x, \ldots, a_n + x$ 中完全平方数的个数。

请找出在 $0$ 到 $10^{18}$ 之间的所有整数 $x$ 中，最大的平方度。

完全平方数是指形如 $t^2$ 的整数，其中 $t$ 是非负整数。最小的完全平方数是 $0, 1, 4, 9, 16, \ldots$。

#### 说明/提示

在第一个测试用例中，当 $x = 0$ 时，数列中有两个完全平方数：$1$ 和 $4$。无法得到超过两个完全平方数。

在第二个测试用例中，当 $x = 3$ 时，数列变为 $4, 9, 16, 25, 100$，即所有元素都是完全平方数。

#### 样例 #1

##### 输入

```
4
5
1 2 3 4 5
5
1 6 13 22 97
1
100
5
2 5 10 17 26
```

##### 输出

```
2
5
1
2
```

### 算法分类

数学

### 题解分析与结论

该题的核心在于通过数学推导找到合适的 $x$，使得 $a_i + x$ 尽可能多的成为完全平方数。所有题解都基于以下思路：

1. **平方差公式**：通过平方差公式 $(p^2 - q^2) = (p - q)(p + q)$，将问题转化为枚举 $a_j - a_i$ 的因数，进而求出 $x$。
2. **枚举与优化**：通过枚举 $a_j - a_i$ 的因数，计算可能的 $x$，并统计 $a_i + x$ 中完全平方数的个数。优化点在于如何高效判断一个数是否为完全平方数。
3. **时间复杂度**：由于 $n$ 较小（$n \leq 50$），且 $a_i \leq 10^9$，枚举因数和计算 $x$ 的时间复杂度在可接受范围内。

### 高星题解推荐

#### 题解1：WilliamFranklin (赞：11)

- **星级**：★★★★★
- **关键亮点**：
  - 详细推导了平方差公式的应用，并给出了清晰的数学证明。
  - 优化了判断完全平方数的方法，使用 `sqrt` 函数代替质因数分解，显著降低了时间复杂度。
  - 代码结构清晰，注释详细，易于理解。

```cpp
bool check(int x) {
    int y = sqrt(x);
    if (y * y == x) return 1;
    else return 0;
}
```

#### 题解2：shipeiqian (赞：7)

- **星级**：★★★★
- **关键亮点**：
  - 通过枚举 $a_j - a_i$ 的因数，推导出 $x$ 的计算公式，思路清晰。
  - 代码简洁，逻辑清晰，适合初学者理解。

```cpp
int diff = a[j] - a[i];
for (int t = 1; t * t <= diff; t++) {
    if (diff % t != 0 || (diff / t + t) % 2 == 1) continue;
    ll temp = (diff / t - t) / 2;
    ll x = temp * temp - a[i];
    if (x < 0) continue;
    int cnt = 0;
    for (int k = 1; k <= n; k++) {
        ll now = sqrtl(a[k] + x);
        if (now * now == a[k] + x) cnt++;
    }
    ans = max(ans, cnt);
}
```

#### 题解3：Andy_Li (赞：6)

- **星级**：★★★★
- **关键亮点**：
  - 详细分析了时间复杂度，并给出了实际运行时间的估算。
  - 代码实现简洁，逻辑清晰，适合有一定基础的读者。

```cpp
ll xx = a[j] - a[i];
for (ll k = 1; k * k <= xx; k++) {
    if (xx % k == 0) {
        ll x = k, y = xx / k;
        if ((y - x) % 2 == 1) continue;
        ll d = x + (y - x) / 2;
        ll e = d - x;
        ll t = max(d, e) * max(d, e) - a[j];
        if (t <= 0) continue;
        int cnt = 0;
        for (int q = 1; q <= n; q++) {
            if ((ll)(sqrt(a[q] + t)) * (ll)(sqrt(a[q] + t)) == a[q] + t) cnt++;
        }
        if (cnt > ans) {
            ans = cnt;
            tt = t;
        }
    }
}
```

### 最优关键思路与技巧

1. **平方差公式的应用**：通过平方差公式将问题转化为枚举因数的形式，大大简化了问题的复杂度。
2. **高效判断完全平方数**：使用 `sqrt` 函数直接判断一个数是否为完全平方数，避免了复杂的质因数分解。
3. **枚举与剪枝**：通过枚举 $a_j - a_i$ 的因数，并结合剪枝策略，减少了不必要的计算。

### 可拓展之处

该题的思路可以拓展到其他涉及平方数或因数分解的问题，例如：

1. **寻找满足特定条件的平方数**：如寻找满足某种性质的平方数序列。
2. **因数分解与枚举**：在其他需要因数分解的问题中，类似的枚举与剪枝策略可以有效降低时间复杂度。

### 推荐题目

1. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1463 [POI2001][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)

### 个人心得总结

- **调试经历**：在判断完全平方数时，最初使用质因数分解的方法导致超时，后来改用 `sqrt` 函数显著提升了效率。
- **踩坑教训**：在计算 $x$ 时，忽略了 $x$ 必须为非负整数的条件，导致部分测试用例失败。
- **顿悟感想**：通过平方差公式将问题转化为因数枚举，大大简化了问题的复杂度，体现了数学在算法中的重要性。

---
处理用时：52.01秒