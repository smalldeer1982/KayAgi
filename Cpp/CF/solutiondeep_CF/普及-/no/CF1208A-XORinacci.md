# 题目信息

# XORinacci

## 题目描述

Cengiz recently learned Fibonacci numbers and now he is studying different algorithms to find them. After getting bored of reading them, he came with his own new type of numbers that he named XORinacci numbers. He defined them as follows:

- $ f(0) = a $ ;
- $ f(1) = b $ ;
- $ f(n) = f(n-1) \oplus f(n-2) $ when $ n > 1 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

You are given three integers $ a $ , $ b $ , and $ n $ , calculate $ f(n) $ .

You have to answer for $ T $ independent test cases.

## 说明/提示

In the first example, $ f(2) = f(0) \oplus f(1) = 3 \oplus 4 = 7 $ .

## 样例 #1

### 输入

```
3
3 4 2
4 5 0
325 265 1231232
```

### 输出

```
7
4
76
```

# AI分析结果

### 题目内容
# XORinacci

## 题目描述
Cengiz最近学习了斐波那契数，现在他正在研究不同的算法来求斐波那契数。在看这些内容看腻之后，他想出了自己的一种新数列，他将其命名为XORinacci数。他对其定义如下：
- $ f(0) = a $ ；
- $ f(1) = b $ ；
- 当 $ n > 1 $ 时，$ f(n) = f(n - 1) \oplus f(n - 2) $ ，其中 $ \oplus $ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

给定三个整数 $ a $ 、$ b $ 和 $ n $ ，计算 $ f(n) $ 。

你需要回答 $ T $ 个独立的测试用例。

## 说明/提示
在第一个样例中，$ f(2) = f(0) \oplus f(1) = 3 \oplus 4 = 7 $ 。

## 样例 #1
### 输入
```
3
3 4 2
4 5 0
325 265 1231232
```
### 输出
```
7
4
76
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路都是通过寻找数列规律来求解。由于直接按定义递推在 $n$ 很大时会超时，因此需要挖掘数列特性。各题解均发现该数列以3为周期循环，即 $f(n)=f(n\%3)$ ，然后根据 $n\%3$ 的结果分别输出 $a$（$n\%3 == 0$ 时）、$b$（$n\%3 == 1$ 时）、$a\oplus b$（$n\%3 == 2$ 时）。不同题解在阐述规律的方式上略有差异，有的从异或运算性质出发推导，有的通过列举前几项直观呈现规律。

### 通用建议与扩展思路
解决此类问题关键在于发现数列隐藏规律，可通过列举前几项、分析运算性质等方式挖掘。对于类似自定义运算的数列问题，都可尝试找规律、分析周期性等。同类型题目通常围绕自定义数列规律展开，重点考察对运算性质及数列规律的挖掘能力。

### 洛谷相似题目
1. P1060 开心的金明：通过分析价值与重量关系找最优解，与本题找数列规律类似。
2. P1164 小A点菜：分析价格组合规律，与本题挖掘数列规律思路相仿。
3. P1217 [USACO1.5]回文质数 Prime Palindromes：寻找满足回文和质数条件的数，需挖掘数字规律，和本题找数列规律有相似性。 

---
处理用时：51.54秒