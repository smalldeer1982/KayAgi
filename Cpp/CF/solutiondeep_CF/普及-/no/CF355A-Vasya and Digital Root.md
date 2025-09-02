# 题目信息

# Vasya and Digital Root

## 题目描述

Vasya has recently found out what a digital root of a number is and he decided to share his knowledge with you.

Let's assume that $ S(n) $ is the sum of digits of number $ n $ , for example, $ S(4098)=4+0+9+8=21 $ . Then the digital root of number $ n $ equals to:

1. $ dr(n)=S(n) $ , if $ S(n)&lt;10 $ ;
2. $ dr(n)=dr(S(n)) $ , if $ S(n)>=10 $ .

For example, $ dr(4098)=dr(21)=3 $ .

Vasya is afraid of large numbers, so the numbers he works with are at most $ 10^{1000} $ . For all such numbers, he has proved that $ dr(n)=S(S(S(S(n)))) $ $ (n<=10^{1000}) $ .

Now Vasya wants to quickly find numbers with the given digital root. The problem is, he hasn't learned how to do that and he asked you to help him. You task is, given numbers $ k $ and $ d $ , find the number consisting of exactly $ k $ digits (the leading zeroes are not allowed), with digital root equal to $ d $ , or else state that such number does not exist.

## 说明/提示

For the first test sample $ dr(5881)=dr(22)=4 $ .

For the second test sample $ dr(36172)=dr(19)=dr(10)=1 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
5881
```

## 样例 #2

### 输入

```
5 1
```

### 输出

```
36172
```

## 样例 #3

### 输入

```
1 0
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Vasya和数字根

## 题目描述
Vasya最近发现了数字根是什么，他决定与你分享他的知识。

假设$S(n)$是数字$n$的各位数字之和，例如，$S(4098)=4 + 0 + 9 + 8 = 21$。那么数字$n$的数字根等于：
1. 如果$S(n)<10$，则$dr(n)=S(n)$；
2. 如果$S(n)\geq10$，则$dr(n)=dr(S(n))$。

例如，$dr(4098)=dr(21)=3$。

Vasya害怕大数字，所以他处理的数字最多为$10^{1000}$。对于所有这样的数字，他已经证明$dr(n)=S(S(S(S(n))))$（$n\leq10^{1000}$）。

现在Vasya想快速找到具有给定数字根的数字。问题是，他还没有学会如何做到这一点，所以他请你帮助他。你的任务是，给定数字$k$和$d$，找到一个恰好由$k$位数字组成的数（不允许有前导零），其数字根等于$d$，否则说明这样的数字不存在。

## 说明/提示
对于第一个测试用例，$dr(5881)=dr(22)=4$。

对于第二个测试用例，$dr(36172)=dr(19)=dr(10)=1$。

## 样例 #1
### 输入
```
4 4
```
### 输出
```
5881
```

## 样例 #2
### 输入
```
5 1
```
### 输出
```
36172
```

## 样例 #3
### 输入
```
1 0
```
### 输出
```
0
```

### 算法分类
构造

### 题解综合分析与结论
这些题解思路大致相同，均先判断无解情况，即当$k > 1$且$d = 0$时，不存在满足条件的数，因为若$d = 0$且$k > 1$，首位为$0$不符合无 前导零的要求。对于有解情况，由于$0\leq d\leq9$，直接构造首位为$d$，后$k - 1$位为$0$的数，该数满足数字根为$d$的要求。各题解在代码实现上略有差异，如输入输出方式、循环写法等，但核心思路一致。

### 通用建议与扩展思路
此类构造题关键在于找到满足题目条件的简单构造方式。对于类似题目，可先分析特殊情况确定无解条件，再从数据范围、题目要求出发，思考如何构造出符合条件的解。同类型题常围绕特定数学性质或函数关系构造数据，需深入理解题目定义的概念和规则。

### 洛谷相似题目推荐
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过给定火柴棒数量，构造出满足等式的数字组合，涉及数字构造与条件判断。
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：从给定数字中选取若干个数，使其和为质数，需按特定规则构造数字组合并进行数学判断。
- [P2615 [NOIP2015 提高组] 神奇的幻方](https://www.luogu.com.cn/problem/P2615)：根据幻方的性质构造满足条件的幻方，考查对特定数学结构的构造能力。 

---
处理用时：31.06秒