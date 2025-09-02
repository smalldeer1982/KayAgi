# 题目信息

# Strongly Composite

## 题目描述

A prime number is an integer greater than $ 1 $ , which has exactly two divisors. For example, $ 7 $ is a prime, since it has two divisors $ \{1, 7\} $ . A composite number is an integer greater than $ 1 $ , which has more than two different divisors.

Note that the integer $ 1 $ is neither prime nor composite.

Let's look at some composite number $ v $ . It has several divisors: some divisors are prime, others are composite themselves. If the number of prime divisors of $ v $ is less or equal to the number of composite divisors, let's name $ v $ as strongly composite.

For example, number $ 12 $ has $ 6 $ divisors: $ \{1, 2, 3, 4, 6, 12\} $ , two divisors $ 2 $ and $ 3 $ are prime, while three divisors $ 4 $ , $ 6 $ and $ 12 $ are composite. So, $ 12 $ is strongly composite. Other examples of strongly composite numbers are $ 4 $ , $ 8 $ , $ 9 $ , $ 16 $ and so on.

On the other side, divisors of $ 15 $ are $ \{1, 3, 5, 15\} $ : $ 3 $ and $ 5 $ are prime, $ 15 $ is composite. So, $ 15 $ is not a strongly composite. Other examples are: $ 2 $ , $ 3 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 10 $ and so on.

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ a_i > 1 $ ). You have to build an array $ b_1, b_2, \dots, b_k $ such that following conditions are satisfied:

- Product of all elements of array $ a $ is equal to product of all elements of array $ b $ : $ a_1 \cdot a_2 \cdot \ldots \cdot a_n = b_1 \cdot b_2 \cdot \ldots \cdot b_k $ ;
- All elements of array $ b $ are integers greater than $ 1 $ and strongly composite;
- The size $ k $ of array $ b $ is the maximum possible.

Find the size $ k $ of array $ b $ , or report, that there is no array $ b $ satisfying the conditions.

## 说明/提示

In the first test case, we can get array $ b = [18] $ : $ a_1 \cdot a_2 = 18 = b_1 $ ; $ 18 $ is strongly composite number.

In the second test case, we can get array $ b = [60] $ : $ a_1 \cdot a_2 \cdot a_3 = 60 = b_1 $ ; $ 60 $ is strongly composite number.

In the third test case, there is no array $ b $ satisfying the conditions.

In the fourth test case, we can get array $ b = [4, 105] $ : $ a_1 \cdot a_2 \cdot a_3 = 420 = b_1 \cdot b_2 $ ; $ 4 $ and $ 105 $ are strongly composite numbers.

## 样例 #1

### 输入

```
8
2
3 6
3
3 4 5
2
2 3
3
3 10 14
2
25 30
1
1080
9
3 3 3 5 5 5 7 7 7
20
12 15 2 2 2 2 2 3 3 3 17 21 21 21 30 6 6 33 31 39```

### 输出

```
1
1
0
2
2
3
4
15```

# AI分析结果

### 题目内容重写

#### 强合数

**题目描述**

质数是指大于 $1$ 且恰好有两个因数的整数。例如，$7$ 是质数，因为它的因数是 $\{1, 7\}$。合数是指大于 $1$ 且有多于两个不同因数的整数。

注意，整数 $1$ 既不是质数也不是合数。

让我们来看一些合数 $v$。它有多个因数：有些因数是质数，有些是合数。如果 $v$ 的质因数数量小于或等于其合因数数量，我们称 $v$ 为强合数。

例如，数字 $12$ 有 $6$ 个因数：$\{1, 2, 3, 4, 6, 12\}$，其中 $2$ 和 $3$ 是质数，而 $4$、$6$ 和 $12$ 是合数。因此，$12$ 是强合数。其他强合数的例子包括 $4$、$8$、$9$、$16$ 等。

另一方面，$15$ 的因数是 $\{1, 3, 5, 15\}$：$3$ 和 $5$ 是质数，$15$ 是合数。因此，$15$ 不是强合数。其他非强合数的例子包括 $2$、$3$、$5$、$6$、$7$、$10$ 等。

给定 $n$ 个整数 $a_1, a_2, \dots, a_n$（$a_i > 1$），你需要构建一个数组 $b_1, b_2, \dots, b_k$，满足以下条件：

- 数组 $a$ 的所有元素的乘积等于数组 $b$ 的所有元素的乘积：$a_1 \cdot a_2 \cdot \ldots \cdot a_n = b_1 \cdot b_2 \cdot \ldots \cdot b_k$；
- 数组 $b$ 的所有元素都是大于 $1$ 的强合数；
- 数组 $b$ 的大小 $k$ 尽可能大。

求数组 $b$ 的大小 $k$，或者报告不存在满足条件的数组 $b$。

**说明/提示**

在第一个测试用例中，我们可以得到数组 $b = [18]$：$a_1 \cdot a_2 = 18 = b_1$；$18$ 是强合数。

在第二个测试用例中，我们可以得到数组 $b = [60]$：$a_1 \cdot a_2 \cdot a_3 = 60 = b_1$；$60$ 是强合数。

在第三个测试用例中，不存在满足条件的数组 $b$。

在第四个测试用例中，我们可以得到数组 $b = [4, 105]$：$a_1 \cdot a_2 \cdot a_3 = 420 = b_1 \cdot b_2$；$4$ 和 $105$ 是强合数。

**样例 #1**

**输入**

```
8
2
3 6
3
3 4 5
2
2 3
3
3 10 14
2
25 30
1
1080
9
3 3 3 5 5 5 7 7 7
20
12 15 2 2 2 2 2 3 3 3 17 21 21 21 30 6 6 33 31 39
```

**输出**

```
1
1
0
2
2
3
4
15
```

### 算法分类
**数学**

### 题解分析与结论

本题的核心是通过质因数分解和组合，将给定的数组 $a$ 的乘积分解为尽可能多的强合数。强合数的定义要求其质因数数量小于或等于合因数数量，因此我们需要找到一种最优的质因数组合方式。

### 精选题解

#### 题解1：作者：Otue (赞：4)
**星级：4星**
**关键亮点：**
- 通过质因数分解，优先使用两个相同的质数构成强合数，再使用三个不同的质数构成强合数。
- 代码简洁，思路清晰，直接计算每个质数的个数并分配。

**核心代码：**
```cpp
int res = 0, cnt = 0;
for (auto i = vis.begin(); i != vis.end(); i++) {
    int t = i -> second;
    res += t / 2; // 两个相同质数
    cnt += t % 2;
}
cout << res + cnt / 3 << endl; // 三个不同质数
```

#### 题解2：作者：One_JuRuo (赞：2)
**星级：4星**
**关键亮点：**
- 详细分析了强合数的构成条件，并给出了数学证明。
- 通过线性筛预处理最小质因数，优化了质因数分解的效率。

**核心代码：**
```cpp
for (auto i : m) {
    cnt += i.second / 2;
    if (i.second % 2) ++siz; // 统计剩下的质因数个数
}
cnt += siz / 3;
printf("%d\n", cnt);
```

#### 题解3：作者：yanwh1 (赞：2)
**星级：4星**
**关键亮点：**
- 通过质因数分解，优先使用两个相同的质数构成强合数，再使用三个不同的质数构成强合数。
- 代码实现简洁，直接计算每个质数的个数并分配。

**核心代码：**
```cpp
int ans = 0, sum = 0;
for (rint i = 1; i <= tot; i++)
    ans += s[i] / 2, sum += s[i] % 2, s[i] = 0;
ans += sum / 3;
```

### 最优关键思路或技巧
1. **质因数分解**：首先对数组 $a$ 的所有元素进行质因数分解，统计每个质数的个数。
2. **优先使用两个相同的质数**：优先将两个相同的质数组合成一个强合数，这样可以最大化强合数的数量。
3. **使用三个不同的质数**：对于剩余的质数，每三个不同的质数组合成一个强合数。
4. **优化质因数分解**：通过线性筛预处理最小质因数，可以显著提高质因数分解的效率。

### 可拓展之处
- 类似的问题可以扩展到其他类型的数，如“强质数”或“强平方数”，通过类似的质因数分解和组合方法解决。
- 可以进一步优化质因数分解的算法，例如使用 Pollard's Rho 算法处理大数分解。

### 推荐题目
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1069 分解质因数](https://www.luogu.com.cn/problem/P1069)
3. [P1072 质数判定](https://www.luogu.com.cn/problem/P1072)

---
处理用时：42.33秒