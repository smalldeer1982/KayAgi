# 题目信息

# Beautiful Numbers

## 题目描述

Vitaly is a very weird man. He's got two favorite digits $ a $ and $ b $ . Vitaly calls a positive integer good, if the decimal representation of this integer only contains digits $ a $ and $ b $ . Vitaly calls a good number excellent, if the sum of its digits is a good number.

For example, let's say that Vitaly's favourite digits are $ 1 $ and $ 3 $ , then number $ 12 $ isn't good and numbers $ 13 $ or $ 311 $ are. Also, number $ 111 $ is excellent and number $ 11 $ isn't.

Now Vitaly is wondering, how many excellent numbers of length exactly $ n $ are there. As this number can be rather large, he asks you to count the remainder after dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

A number's length is the number of digits in its decimal representation without leading zeroes.

## 样例 #1

### 输入

```
1 3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3 10
```

### 输出

```
165
```

# AI分析结果

### 题目内容
# 美丽数字

## 题目描述
维塔利是个非常奇怪的人。他有两个喜欢的数字 $a$ 和 $b$。维塔利将一个正整数称为“好数”，如果这个整数的十进制表示只包含数字 $a$ 和 $b$。维塔利将一个“好数”称为“极好数”，如果它的各位数字之和是一个“好数”。

例如，假设维塔利最喜欢的数字是 $1$ 和 $3$，那么数字 $12$ 不是“好数”，而数字 $13$ 或 $311$ 是。此外，数字 $111$ 是“极好数”，而数字 $11$ 不是。

现在维塔利想知道，长度恰好为 $n$ 的“极好数”有多少个。由于这个数字可能相当大，他要求你计算它除以 $1000000007$（$10^{9}+7$）的余数。

一个数的长度是其十进制表示中不含前导零的数字个数。

## 样例 #1
### 输入
```
1 3 3
```
### 输出
```
1
```

## 样例 #2
### 输入
```
2 3 10
```
### 输出
```
165
```

### 算法分类
组合数学

### 题解综合分析与结论
所有题解的核心思路一致，均基于以下要点：
 - **思路**：一个数是否为“极好数”与数字顺序无关，只与数字和有关。先枚举“极好数”中 $a$ 的个数 $i$，则 $b$ 的个数为 $n - i$，计算数字和 $a\times i + b\times (n - i)$，判断其是否为“好数”，若是，则此类组合构成的“极好数”数量为从 $n$ 个位置中选 $i$ 个放 $a$ 的组合数 $C_{n}^{i}$，将所有满足条件的组合数累加即为答案。
 - **算法要点**：通过枚举确定 $a$ 和 $b$ 的个数组合，利用组合数公式计算每种组合能构成的“极好数”数量。
 - **解决难点**：计算组合数时涉及除法取模，需使用逆元解决。各题解在计算逆元及实现细节上有所不同，部分通过线性预处理逆元，部分使用费马小定理结合快速幂求逆元。

### 通用建议与扩展思路
 - **通用建议**：在解决此类组合数学问题时，关键在于理解问题本质，找到与组合数的联系，并合理处理取模运算。代码实现上，注意边界条件和数据范围，确保计算准确性。
 - **扩展思路**：同类型题常围绕特定数字规则生成数字并计数，可拓展到更多数字种类、不同数字和判断条件等。类似算法套路包括利用数论知识优化计算，如组合数的快速计算方法；对于复杂判断条件，可提前预处理相关数据以提高效率。

### 相似知识点洛谷题目
 - [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)
 - [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)
 - [P1313 计算系数](https://www.luogu.com.cn/problem/P1313) 

---
处理用时：28.98秒