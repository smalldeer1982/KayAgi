# 题目信息

# Vasya's Calendar

## 题目描述

Vasya lives in a strange world. The year has $ n $ months and the $ i $ -th month has $ a_{i} $ days. Vasya got a New Year present — the clock that shows not only the time, but also the date.

The clock's face can display any number from $ 1 $ to $ d $ . It is guaranteed that $ a_{i}<=d $ for all $ i $ from $ 1 $ to $ n $ . The clock does not keep information about the current month, so when a new day comes, it simply increases the current day number by one. The clock cannot display number $ d+1 $ , so after day number $ d $ it shows day $ 1 $ (the current day counter resets). The mechanism of the clock allows you to increase the day number by one manually. When you execute this operation, day $ d $ is also followed by day $ 1 $ .

Vasya begins each day checking the day number on the clock. If the day number on the clock does not match the actual day number in the current month, then Vasya manually increases it by one. Vasya is persistent and repeats this operation until the day number on the clock matches the actual number of the current day in the current month.

A year passed and Vasya wonders how many times he manually increased the day number by one, from the first day of the first month to the last day of the $ n $ -th month inclusive, considering that on the first day of the first month the clock display showed day $ 1 $ .

## 说明/提示

In the first sample the situation is like this:

- Day 1. Month 1. The clock shows $ 1 $ . Vasya changes nothing.
- Day 2. Month 1. The clock shows $ 2 $ . Vasya changes nothing.
- Day 1. Month 2. The clock shows $ 3 $ . Vasya manually increases the day number by $ 1 $ . After that the clock shows $ 4 $ . Vasya increases the day number by $ 1 $ manually. After that the clock shows $ 1 $ .
- Day 2. Month 2. The clock shows $ 2 $ . Vasya changes nothing.

 In total, Vasya manually changed the day number by $ 1 $ exactly $ 2 $ times.

## 样例 #1

### 输入

```
4
2
2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
3
3 4 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
31
12
31 28 31 30 31 30 31 31 30 31 30 31
```

### 输出

```
7
```

# AI分析结果

### 题目内容
# Vasya的日历

## 题目描述
Vasya生活在一个奇怪的世界。一年有$n$个月，第$i$个月有$a_{i}$天。Vasya收到了一份新年礼物——一个不仅能显示时间，还能显示日期的时钟。

时钟的表盘可以显示从$1$到$d$的任意数字。保证对于从$1$到$n$的所有$i$，都有$a_{i}\leq d$。时钟不记录当前月份的信息，所以当新的一天到来时，它只是简单地将当前日期数字增加$1$。时钟不能显示数字$d + 1$，所以在日期数字$d$之后，它会显示日期$1$（当前日期计数器重置）。时钟的机制允许你手动将日期数字增加$1$。当你执行此操作时，日期$d$之后同样会显示日期$1$。

Vasya每天都会查看时钟上的日期数字。如果时钟上的日期数字与当前月份的实际日期数字不匹配，那么Vasya会手动将其增加$1$。Vasya很执着，会重复此操作，直到时钟上的日期数字与当前月份的实际日期数字匹配。

一年过去了，Vasya想知道，从第一个月的第一天到第$n$个月的最后一天（包括这两天），考虑到第一个月的第一天时钟显示为日期$1$，他手动将日期数字增加$1$的次数是多少。

## 说明/提示
在第一个样例中，情况如下：
- 第1天，第1个月。时钟显示$1$。Vasya不做任何更改。
- 第2天，第1个月。时钟显示$2$。Vasya不做任何更改。
- 第1天，第2个月。时钟显示$3$。Vasya手动将日期数字增加$1$。之后时钟显示$4$。Vasya再次手动将日期数字增加$1$。之后时钟显示$1$。
- 第2天，第2个月。时钟显示$2$。Vasya不做任何更改。

  总共，Vasya手动将日期数字增加$1$的次数恰好为$2$次。

## 样例 #1
### 输入
```
4
2
2 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5
3
3 4 3
```
### 输出
```
3
```

## 样例 #3
### 输入
```
31
12
31 28 31 30 31 30 31 31 30 31 30 31
```
### 输出
```
7
```

### 算法分类
数学

### 综合分析与结论
所有题解思路基本一致，核心思路都是计算每个月需要手动调整的天数并累加，即每个月需调整的天数为$d - a_{i}$，但最后一个月无需调整。各题解都注意到了这一特殊情况，只是在代码实现细节上略有不同，如循环范围的控制、输入输出方式等。整体来看，这些题解质量较为接近，差异不大。

### 通用建议与扩展思路
- 通用建议：在处理这类问题时，要清晰理解题目中的特殊条件（如本题最后一个月不调整），并在代码实现中准确处理。同时，注意代码的简洁性和可读性，选择合适的数据结构和循环方式。
- 扩展思路：类似题目可能会改变日期重置规则、增加月份或日期的其他限制条件等。可以通过改变条件进行自我练习，加深对这类日期计算问题的理解。例如，改变时钟重置规则为每$k$天重置一次，或者增加月份之间的关联条件等。 

### 相似知识点洛谷题目
 - [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：通过枚举和数学运算解决问题，锻炼对数字关系的处理能力。
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：利用数学方法找出满足条件的连续自然数序列，与本题类似，都需要对数据进行分析和运算。
 - [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合数学知识（斐波那契数列性质和最大公约数算法）解决问题，培养运用数学知识解决编程问题的能力。 

---
处理用时：30.03秒