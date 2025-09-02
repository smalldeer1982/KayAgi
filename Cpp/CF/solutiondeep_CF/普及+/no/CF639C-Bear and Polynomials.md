# 题目信息

# Bear and Polynomials

## 题目描述

Limak is a little polar bear. He doesn't have many toys and thus he often plays with polynomials.

He considers a polynomial valid if its degree is $ n $ and its coefficients are integers not exceeding $ k $ by the absolute value. More formally:

Let $ a_{0},a_{1},...,a_{n} $ denote the coefficients, so ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639C/b2e2221d8fc8543b45bad8022a862376e8bf8aaa.png). Then, a polynomial $ P(x) $ is valid if all the following conditions are satisfied:

- $ a_{i} $ is integer for every $ i $ ;
- $ |a_{i}|<=k $ for every $ i $ ;
- $ a_{n}≠0 $ .

Limak has recently got a valid polynomial $ P $ with coefficients $ a_{0},a_{1},a_{2},...,a_{n} $ . He noticed that $ P(2)≠0 $ and he wants to change it. He is going to change one coefficient to get a valid polynomial $ Q $ of degree $ n $ that $ Q(2)=0 $ . Count the number of ways to do so. You should count two ways as a distinct if coefficients of target polynoms differ.

## 说明/提示

In the first sample, we are given a polynomial $ P(x)=10-9x-3x^{2}+5x^{3} $ .

Limak can change one coefficient in three ways:

1. He can set $ a_{0}=-10 $ . Then he would get $ Q(x)=-10-9x-3x^{2}+5x^{3} $ and indeed $ Q(2)=-10-18-12+40=0 $ .
2. Or he can set $ a_{2}=-8 $ . Then $ Q(x)=10-9x-8x^{2}+5x^{3} $ and indeed $ Q(2)=10-18-32+40=0 $ .
3. Or he can set $ a_{1}=-19 $ . Then $ Q(x)=10-19x-3x^{2}+5x^{3} $ and indeed $ Q(2)=10-38-12+40=0 $ .

In the second sample, we are given the same polynomial. This time though, $ k $ is equal to $ 12 $ instead of $ 10^{9} $ . Two first of ways listed above are still valid but in the third way we would get $ |a_{1}|&gt;k $ what is not allowed. Thus, the answer is $ 2 $ this time.

## 样例 #1

### 输入

```
3 1000000000
10 -9 -3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 12
10 -9 -3 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 20
14 -7 19
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 熊与多项式

## 题目描述
利马克是一只小北极熊。它没有太多玩具，所以经常玩多项式。

如果一个多项式的次数为 $n$ 且其系数为绝对值不超过 $k$ 的整数，那么利马克认为这个多项式是有效的。更正式地说：

设 $a_{0},a_{1},...,a_{n}$ 表示系数，所以 $P(x)=\sum_{i = 0}^{n}a_{i}x^{i}$。那么，多项式 $P(x)$ 是有效的，当且仅当满足以下所有条件：
- 对于每个 $i$，$a_{i}$ 是整数；
- 对于每个 $i$，$|a_{i}|\leq k$；
- $a_{n}\neq0$。

利马克最近得到了一个有效的多项式 $P$，其系数为 $a_{0},a_{1},a_{2},...,a_{n}$。它注意到 $P(2)\neq0$，并且它想改变这一点。它打算改变一个系数，以得到一个次数为 $n$ 的有效多项式 $Q$，使得 $Q(2)=0$。计算这样做的方法数。如果目标多项式的系数不同，则将两种方法视为不同的方法。

## 说明/提示
在第一个样例中，我们得到多项式 $P(x)=10 - 9x - 3x^{2}+5x^{3}$。

利马克可以通过三种方式改变一个系数：
1. 它可以将 $a_{0}$ 设置为 $-10$。那么它将得到 $Q(x)=-10 - 9x - 3x^{2}+5x^{3}$，并且确实 $Q(2)=-10 - 18 - 12 + 40 = 0$。
2. 或者它可以将 $a_{2}$ 设置为 $-8$。那么 $Q(x)=10 - 9x - 8x^{2}+5x^{3}$，并且确实 $Q(2)=10 - 18 - 32 + 40 = 0$。
3. 或者它可以将 $a_{1}$ 设置为 $-19$。那么 $Q(x)=10 - 19x - 3x^{2}+5x^{3}$，并且确实 $Q(2)=10 - 38 - 12 + 40 = 0$。

在第二个样例中，我们得到相同的多项式。但这一次，$k$ 等于 $12$ 而不是 $10^{9}$。上面列出的前两种方法仍然有效，但在第三种方法中，我们会得到 $|a_{1}|>k$，这是不允许的。因此，这次的答案是 $2$。

## 样例 #1
### 输入
```
3 1000000000
10 -9 -3 5
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3 12
10 -9 -3 5
```
### 输出
```
2
```

## 样例 #3
### 输入
```
2 20
14 -7 19
```
### 输出
```
0
```

### 算法分类
数学

### 题解综合分析与结论
- **BYR_KKK 的题解思路**：通过枚举多项式的每一项，设除当前枚举项外其他项的和为 $s$，当前项为 $a_i2^i$，要使 $P(2)$ 经改变一项后为 $0$，即判断 $a_i2^i + s = 0$ 有无解。由于值域大，采用哈希思想，转化为判断同余方程 $a_i2^i\equiv -s(\pmod P)$ 的解，移项得到 $a_i\equiv -s\cdot 2^{-i}$，选取大于 $k$ 的 $P$，同时注意负数解。时间复杂度 $O(n\log V)$。
- **樱雪喵的题解思路**：把 $x = 2$ 代入多项式得到 $P(2)=\sum_{i = 0}^{n}a_i 2^i$，将系数非 $[0,1]$ 的部分向后进位转化为二进制形式 $P(2)=\sum_{i = 0}^{n + 1}b_i 2^i$（除 $b_{n + 1}$ 外 $b_i\in\{0,1\}$）。只改一个系数使 $P(2)$ 为 $0$，在二进制下等价于小于某位置 $i$ 的 $b_j$ 均为 $0$。找到第一个 $b_i\neq 0$ 的位置，从该位置依次考虑答案，维护 $P(2)$ 是当前位对应值的几倍，若倍数大于 $2k$ 则停止。

两者解决难点的方式不同，BYR_KKK 主要通过哈希解决值域大的问题，樱雪喵则是利用二进制的特性来简化问题判断。

### 题解情况
- **BYR_KKK 的题解**：
  - **星级**：3 星
  - **关键亮点**：利用哈希解决高值域下方程解的判断问题，思路较为清晰，但代码采用三模，相对复杂。
- **樱雪喵的题解**：
  - **星级**：3 星
  - **关键亮点**：巧妙地将多项式转化为二进制形式，利用二进制特性简化判断，代码实现较为简洁，但思路理解上有一定难度。

### 通用建议与扩展思路
对于此类多项式相关数学问题，可以多从数论知识以及多项式的特殊性质出发思考。比如对于多项式求值，可以考虑一些特殊值代入后的性质，像本题代入 $x = 2$。对于系数的处理，可以结合进制、同余等知识。类似的题目可能会改变多项式的定义、求值的特殊点或者系数的限制条件等，解题时需灵活运用数学知识。

### 洛谷相似题目推荐
- P1082 [同余方程](https://www.luogu.com.cn/problem/P1082)：考察数论中的同余方程相关知识，与本题中利用同余方程解决问题的思路有一定相关性。
- P2155 [SDOI2008]沙拉公主的困惑](https://www.luogu.com.cn/problem/P2155)：涉及数论、组合数学等知识，对于锻炼数论相关解题能力有帮助，与本题同属数学类问题。
- P3951 [小凯的疑惑](https://www.luogu.com.cn/problem/P3951)：数论相关问题，通过分析数的性质来解决问题，和本题一样需要挖掘题目中的数学特性。 

---
处理用时：46.07秒