# 题目信息

# Shohag Loves XOR (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ \mathbf{x \neq y} $ and $ x \oplus y $ is a divisor $ ^{\text{∗}} $ of either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ b $ is a divisor of the number $ a $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 说明/提示

In the first test case, for $ x = 6 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 9 $ , and they are $ 4 $ , $ 5 $ , and $ 7 $ .

- $ y = 4 $ is valid because $ x \oplus y = 6 \oplus 4 = 2 $ and $ 2 $ is a divisor of both $ x = 6 $ and $ y = 4 $ .
- $ y = 5 $ is valid because $ x \oplus y = 6 \oplus 5 = 3 $ and $ 3 $ is a divisor of $ x = 6 $ .
- $ y = 7 $ is valid because $ x \oplus y = 6 \oplus 7 = 1 $ and $ 1 $ is a divisor of both $ x = 6 $ and $ y = 7 $ .

In the second test case, for $ x = 5 $ , there are $ 2 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 7 $ , and they are $ 4 $ and $ 6 $ .

- $ y = 4 $ is valid because $ x \oplus y = 5 \oplus 4 = 1 $ and $ 1 $ is a divisor of both $ x = 5 $ and $ y = 4 $ .
- $ y = 6 $ is valid because $ x \oplus y = 5 \oplus 6 = 3 $ and $ 3 $ is a divisor of $ y = 6 $ .

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1```

### 输出

```
3
2
1
1
0```

# AI分析结果

### 题目内容重写（中文）

# Shohag 喜欢异或（简单版）

## 题目描述

这是该问题的简单版本。两个版本之间的差异以粗体标出。只有在两个版本的问题都解决时，才能进行 hack。

Shohag 有两个整数 $x$ 和 $m$。请帮助他计算满足 $1 \le y \le m$ 且 $\mathbf{x \neq y}$ 的整数 $y$ 的数量，使得 $x \oplus y$ 是 $x$、$y$ 或两者的除数。这里的 $\oplus$ 是 [按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) 运算符。

$^{\text{∗}}$ 数 $b$ 是数 $a$ 的除数，如果存在整数 $c$ 使得 $a = b \cdot c$。

## 说明/提示

在第一个测试用例中，对于 $x = 6$，在 $1$ 到 $m = 9$ 的整数中有 $3$ 个有效的 $y$ 值，分别是 $4$、$5$ 和 $7$。

- $y = 4$ 是有效的，因为 $x \oplus y = 6 \oplus 4 = 2$，且 $2$ 是 $x = 6$ 和 $y = 4$ 的除数。
- $y = 5$ 是有效的，因为 $x \oplus y = 6 \oplus 5 = 3$，且 $3$ 是 $x = 6$ 的除数。
- $y = 7$ 是有效的，因为 $x \oplus y = 6 \oplus 7 = 1$，且 $1$ 是 $x = 6$ 和 $y = 7$ 的除数。

在第二个测试用例中，对于 $x = 5$，在 $1$ 到 $m = 7$ 的整数中有 $2$ 个有效的 $y$ 值，分别是 $4$ 和 $6$。

- $y = 4$ 是有效的，因为 $x \oplus y = 5 \oplus 4 = 1$，且 $1$ 是 $x = 5$ 和 $y = 4$ 的除数。
- $y = 6$ 是有效的，因为 $x \oplus y = 5 \oplus 6 = 3$，且 $3$ 是 $y = 6$ 的除数。

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1
```

### 输出

```
3
2
1
1
0
```

### 题解分析与结论

本题的核心在于如何高效地计算满足条件的 $y$ 的数量。由于 $m$ 的范围可能非常大（$10^{18}$），直接暴力枚举 $y$ 是不可行的。因此，题解的关键在于如何缩小 $y$ 的枚举范围。

通过对题目的分析，可以发现以下关键点：
1. **$y$ 的范围限制**：当 $y \ge 2x$ 时，$x \oplus y$ 必定大于 $x$，且不可能是 $y$ 的除数。因此，$y$ 的有效范围可以缩小到 $1 \le y \le \min(2x, m)$。
2. **二进制位数的限制**：$y$ 的二进制位数不能超过 $x$ 的二进制位数，否则 $x \oplus y$ 无法成为 $y$ 的除数。

基于以上分析，大多数题解都采用了将 $y$ 的范围缩小到 $1 \le y \le \min(2x, m)$ 的策略，从而将时间复杂度降低到 $O(x)$，能够通过题目。

### 精选题解

#### 题解1：作者：SUNCHAOYI (赞：4)
- **星级**：4
- **关键亮点**：通过分析 $y$ 的范围限制，提出 $y < 2x$ 的结论，并给出了详细的证明。代码实现简洁，直接枚举 $1 \le y \le x$ 的范围，并判断 $x \oplus y$ 是否为 $x$ 或 $y$ 的除数。
- **代码核心**：
  ```cpp
  for (int i = 1; i <= x; ++i) {
      ll y = x ^ i;
      if (!(1 <= y && y <= m)) continue;
      if (x % (x ^ y) == 0 || y % (x ^ y) == 0) ++cnt;
  }
  ```

#### 题解2：作者：Fiendish (赞：4)
- **星级**：4
- **关键亮点**：通过二进制位数的分析，进一步缩小了 $y$ 的枚举范围，提出 $y$ 的位数不能超过 $x$ 的位数。代码实现中使用了 `__lg(x)` 来获取 $x$ 的二进制位数，从而进一步优化了枚举范围。
- **代码核心**：
  ```cpp
  for (int i = 1; i < min((1ll << ((int)__lg(x) + 1)), m + 1); i++)
      if (i != x && (x % (i ^ x) == 0 || i % (i ^ x) == 0)) ans++;
  ```

#### 题解3：作者：Limerency (赞：3)
- **星级**：3
- **关键亮点**：通过分析 $f(x) = f(y)$（$f(p)$ 表示 $p$ 的二进制位数），直接枚举所有 $f(x) = f(y)$ 的 $y$，从而将时间复杂度降低到 $O(2^{\lfloor\log x \rfloor})$。代码实现较为简洁，但复杂度略高于前两个题解。
- **代码核心**：
  ```cpp
  for (int i = hb >> 1; i <= lm; i ++) {
      int t = (x ^ i);
      if (x != i) if (x % t == 0 || i % t == 0) ans ++;
  }
  ```

### 最优关键思路与技巧

1. **范围缩小**：通过分析 $y$ 的范围限制，将 $y$ 的枚举范围缩小到 $1 \le y \le \min(2x, m)$，从而将时间复杂度从 $O(m)$ 降低到 $O(x)$。
2. **二进制位数分析**：通过分析 $y$ 的二进制位数不能超过 $x$ 的位数，进一步优化了枚举范围。
3. **位运算优化**：使用 `__lg(x)` 等位运算技巧，快速获取 $x$ 的二进制位数，进一步优化了代码实现。

### 可拓展之处

1. **类似问题**：类似的问题可以通过分析二进制位数和范围限制来优化枚举范围，例如在涉及异或操作和因数判断的题目中。
2. **位运算技巧**：在处理涉及二进制操作的问题时，位运算技巧（如 `__lg(x)`）可以大大简化代码实现。

### 推荐题目

1. [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

### 个人心得摘录

- **SUNCHAOYI**：通过分析 $y$ 的范围限制，提出 $y < 2x$ 的结论，并给出了详细的证明。代码实现简洁，直接枚举 $1 \le y \le x$ 的范围，并判断 $x \oplus y$ 是否为 $x$ 或 $y$ 的除数。
- **Fiendish**：通过二进制位数的分析，进一步缩小了 $y$ 的枚举范围，提出 $y$ 的位数不能超过 $x$ 的位数。代码实现中使用了 `__lg(x)` 来获取 $x$ 的二进制位数，从而进一步优化了枚举范围。

---
处理用时：67.09秒