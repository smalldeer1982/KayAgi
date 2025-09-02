# 题目信息

# Windblume Ode

## 题目描述

A bow adorned with nameless flowers that bears the earnest hopes of an equally nameless person.

You have obtained the elegant bow known as the Windblume Ode. Inscribed in the weapon is an array of $ n $ ( $ n \ge 3 $ ) positive distinct integers (i.e. different, no duplicates are allowed).

Find the largest subset (i.e. having the maximum number of elements) of this array such that its sum is a composite number. A positive integer $ x $ is called composite if there exists a positive integer $ y $ such that $ 1 < y < x $ and $ x $ is divisible by $ y $ .

If there are multiple subsets with this largest size with the composite sum, you can output any of them. It can be proven that under the constraints of the problem such a non-empty subset always exists.

## 说明/提示

In the first test case, the subset $ \{a_2, a_1\} $ has a sum of $ 9 $ , which is a composite number. The only subset of size $ 3 $ has a prime sum equal to $ 11 $ . Note that you could also have selected the subset $ \{a_1, a_3\} $ with sum $ 8 + 2 = 10 $ , which is composite as it's divisible by $ 2 $ .

In the second test case, the sum of all elements equals to $ 21 $ , which is a composite number. Here we simply take the whole array as our subset.

## 样例 #1

### 输入

```
4
3
8 1 2
4
6 9 4 2
9
1 2 3 4 5 6 7 8 9
3
200 199 198```

### 输出

```
2
2 1
4
2 1 4 3
9
6 9 1 2 3 4 5 7 8
3
1 2 3```

# AI分析结果

### 题目内容
# 风花之颂

## 题目描述
一把装饰着无名花朵的弓，承载着同样无名之人的殷切希望。

你获得了名为“风花之颂”的优雅长弓。在这把武器上铭刻着一个由 $n$（$n \geq 3$）个不同正整数组成的数组（即各不相同，不允许有重复）。

找出这个数组的最大子集（即元素数量最多的子集），使得其元素之和为合数。一个正整数 $x$ 如果存在一个正整数 $y$，满足 $1 < y < x$ 且 $x$ 能被 $y$ 整除，则称 $x$ 为合数。

如果有多个具有此最大规模且和为合数的子集，你可以输出其中任何一个。可以证明，在本题的约束条件下，这样的非空子集总是存在的。

## 说明/提示
在第一个测试用例中，子集 $\{a_2, a_1\}$ 的和为 $9$，这是一个合数。唯一大小为 $3$ 的子集的和为质数，等于 $11$。注意，你也可以选择子集 $\{a_1, a_3\}$，其和为 $8 + 2 = 10$，因为它能被 $2$ 整除，所以也是合数。

在第二个测试用例中，所有元素的和等于 $21$，这是一个合数。在这里，我们直接将整个数组作为我们的子集。

## 样例 #1
### 输入
```
4
3
8 1 2
4
6 9 4 2
9
1 2 3 4 5 6 7 8 9
3
200 199 198
```
### 输出
```
2
2 1
4
2 1 4 3
9
6 9 1 2 3 4 5 7 8
3
1 2 3
```
### 算法分类
数学

### 题解综合分析与结论
所有题解的核心思路基本一致，都是先计算数组所有元素的和，判断其是否为合数。若和为合数，则直接输出整个数组；若和为质数，由于 $n \geq 3$ 且大于 $2$ 的偶数均为合数，此时和为奇数，所以数组中必有奇数，去掉任意一个奇数后和为偶数，即为合数。各题解的差异主要体现在代码实现细节，如输入输出方式、判断合数的方法、标记和处理要去掉的奇数的方式等。

### 通用建议与扩展思路
对于此类题目，关键在于理解合数、质数的性质以及数字和的奇偶性规律。可以进一步拓展到更复杂的数字组合问题，比如限制子集中元素的其他条件，或者改变判断数字性质的规则等。在代码实现上，可以注重优化输入输出效率，以及对判断函数的优化等。

### 相似知识点洛谷题目
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P2689 质数口袋](https://www.luogu.com.cn/problem/P2689)
3. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)

### 个人心得摘录与总结
 - “一道弱智题，没删 ```freopen``` 调了好久。这道题最难的地方在于看出所谓复合数实际上就是合数。”：强调了理解题意中关键概念的重要性，同时也提醒注意调试时一些可能遗忘的代码细节。 

---
处理用时：23.52秒