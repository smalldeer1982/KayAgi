# 题目信息

# Serval and Mocha's Array

## 题目描述

Mocha likes arrays, and Serval gave her an array consisting of positive integers as a gift.

Mocha thinks that for an array of positive integers $ a $ , it is good iff the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of all the elements in $ a $ is no more than its length. And for an array of at least $ 2 $ positive integers, it is beautiful iff all of its prefixes whose length is no less than $ 2 $ are good.

For example:

- $ [3,6] $ is not good, because $ \gcd(3,6)=3 $ is greater than its length $ 2 $ .
- $ [1,2,4] $ is both good and beautiful, because all of its prefixes whose length is no less than $ 2 $ , which are $ [1,2] $ and $ [1,2,4] $ , are both good.
- $ [3,6,1] $ is good but not beautiful, because $ [3,6] $ is not good.

Now Mocha gives you the gift array $ a $ of $ n $ positive integers, and she wants to know whether array $ a $ could become beautiful by reordering the elements in $ a $ . It is allowed to keep the array $ a $ unchanged.

## 说明/提示

In the first test case, neither $ [3,6] $ nor $ [6,3] $ are beautiful, so it's impossible to obtain a beautiful array by reordering the elements in $ a $ .

In the second test case, $ [1,2,4] $ is already beautiful. Keeping the array $ a $ unchanged can obtain a beautiful array.

## 样例 #1

### 输入

```
6
2
3 6
3
1 2 4
3
3 6 1
3
15 35 21
4
35 10 35 14
5
1261 227821 143 4171 1941```

### 输出

```
No
Yes
Yes
No
Yes
Yes```

# AI分析结果

### 题目内容
# Serval和Mocha的数组

## 题目描述
Mocha喜欢数组，Serval送给她一个由正整数组成的数组作为礼物。

Mocha认为，对于一个正整数数组 $a$ ，当且仅当 $a$ 中所有元素的[最大公约数](https://en.wikipedia.org/wiki/Greatest_common_divisor)不超过其长度时，该数组是好的。对于一个至少有 $2$ 个正整数的数组，当且仅当其所有长度不小于 $2$ 的前缀都是好的时，该数组是美丽的。

例如：
- $[3,6]$ 不是好的，因为 $\gcd(3,6)=3$ 大于其长度 $2$ 。
- $[1,2,4]$ 既是好的也是美丽的，因为其所有长度不小于 $2$ 的前缀，即 $[1,2]$ 和 $[1,2,4]$ ，都是好的。
- $[3,6,1]$ 是好的但不是美丽的，因为 $[3,6]$ 不是好的。

现在Mocha给你一个包含 $n$ 个正整数的礼物数组 $a$ ，她想知道通过重新排列 $a$ 中的元素，数组 $a$ 是否能变成美丽的。允许保持数组 $a$ 不变。

## 说明/提示
在第一个测试用例中，$[3,6]$ 和 $[6,3]$ 都不是美丽的，所以不可能通过重新排列 $a$ 中的元素得到一个美丽的数组。

在第二个测试用例中，$[1,2,4]$ 已经是美丽的。保持数组 $a$ 不变就能得到一个美丽的数组。

## 样例 #1
### 输入
```
6
2
3 6
3
1 2 4
3
3 6 1
3
15 35 21
4
35 10 35 14
5
1261 227821 143 4171 1941```
### 输出
```
No
Yes
Yes
No
Yes
Yes```

### 算法分类
数学

### 综合分析与结论
由于暂无题解，通用建议如下：首先需要深刻理解好数组与美丽数组的定义。解决该问题的关键在于找到一种方法判断能否通过重新排列数组元素使其满足美丽数组的条件。可以考虑从最大公约数的性质入手，例如若数组中存在一个元素能整除其他所有元素，那么在重新排列时将其放在合适位置可能有助于满足前缀条件。扩展思路上，类似这种基于数组元素某种数学关系定义的性质判断问题，通常可以深入挖掘数学性质来简化判断过程，比如研究最大公约数在数组元素不同排列下的变化规律。

### 洛谷相关题目推荐
1. P1072 [HNOI2009] 辗转相除，考察最大公约数相关知识。
2. P2613 【模板】有理数取余，涉及数论中的取余运算及相关数学推导。
3. P1890 [USACO06NOV] Bad Hair Day G，虽看似是单调栈问题，但其中也蕴含一定的数学逻辑思维。 

---
处理用时：20.24秒