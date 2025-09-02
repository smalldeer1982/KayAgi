# 题目信息

# Omkar and Completion

## 题目描述

You have been blessed as a child of Omkar. To express your gratitude, please solve this problem for Omkar!

An array $ a $ of length $ n $ is called complete if all elements are positive and don't exceed $ 1000 $ , and for all indices $ x $ , $ y $ , $ z $ ( $ 1 \leq x,y,z \leq n $ ), $ a_{x}+a_{y} \neq a_{z} $ (not necessarily distinct).

You are given one integer $ n $ . Please find any complete array of length $ n $ . It is guaranteed that under given constraints such array exists.

## 说明/提示

It can be shown that the outputs above are valid for each test case. For example, $ 44+44 \neq 384 $ .

Below are some examples of arrays that are NOT complete for the 1st test case:

 $ [1,2,3,4,5] $

Notice that $ a_{1}+a_{2} = a_{3} $ .

 $ [1,3000,1,300,1] $

Notice that $ a_{2} = 3000 > 1000 $ .

## 样例 #1

### 输入

```
2
5
4```

### 输出

```
1 5 3 77 12
384 384 44 44```

# AI分析结果

### 题目内容
# Omkar和数组完成

## 题目描述
你作为Omkar的孩子受到了祝福。为了表达你的感激之情，请为Omkar解决这个问题！

一个长度为$n$的数组$a$被称为完整的，如果所有元素都是正数且不超过$1000$，并且对于所有索引$x$、$y$、$z$（$1 \leq x,y,z \leq n$），都有$a_{x}+a_{y} \neq a_{z}$（不一定是不同的索引）。

你会得到一个整数$n$。请找出任意一个长度为$n$的完整数组。保证在给定的限制条件下这样的数组是存在的。

## 说明/提示
可以证明上述输出对于每个测试用例都是有效的。例如，$44 + 44 \neq 384$。

以下是一些对于第一个测试用例来说不完整的数组示例：
 - $[1,2,3,4,5]$，注意到$a_{1}+a_{2} = a_{3}$。
 - $[1,3000,1,300,1]$，注意到$a_{2} = 3000 > 1000$。

## 样例 #1
### 输入
```
2
5
4
```
### 输出
```
1 5 3 77 12
384 384 44 44
```

### 算法分类
构造

### 题解综合分析与结论
这些题解的核心思路都是通过构造满足条件的数组来解决问题。大部分题解利用了简单的数学性质，如奇数相加为偶数，或相同数相加不等于自身等。不同题解在具体实现上有所差异，但本质都是基于这些基本性质进行构造。

### 通用建议与扩展思路
 - **思路**：本题关键在于找到一种简单且通用的构造方式，使数组满足$a_{x}+a_{y} \neq a_{z}$的条件。可以从简单的数学关系入手，如奇偶性、数的倍数关系等。
 - **扩展**：同类型题目通常会要求构造满足特定条件的序列或数据结构。解决这类问题时，要深入分析条件背后的数学原理，通过简单的数学性质来设计构造方法。例如，类似的题目可能会改变数组元素的限制条件，或者改变不等式关系，解题时需要灵活运用数学知识进行构造。

### 洛谷相似题目
 - [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)：给定两个整数集合，要求找出满足一定差值关系的数对数量，需要构造合适的数据结构和算法来高效解决。
 - [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：根据给定的规则构造出小玉游泳距离的序列，涉及到简单的数学运算和循环构造。
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：从给定的数中选取若干个数，使其和为质数，需要构造合适的枚举和判断方法。 

---
处理用时：26.34秒