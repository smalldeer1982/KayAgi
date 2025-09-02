# 题目信息

# Hossam and Combinatorics

## 题目描述

Hossam woke up bored, so he decided to create an interesting array with his friend Hazem.

Now, they have an array $ a $ of $ n $ positive integers, Hossam will choose a number $ a_i $ and Hazem will choose a number $ a_j $ .

Count the number of interesting pairs $ (a_i, a_j) $ that meet all the following conditions:

- $ 1 \le i, j \le n $ ;
- $ i \neq j $ ;
- The absolute difference $ |a_i - a_j| $ must be equal to the maximum absolute difference over all the pairs in the array. More formally, $ |a_i - a_j| = \max_{1 \le p, q \le n} |a_p - a_q| $ .

## 说明/提示

In the first example, the two ways are:

- Hossam chooses the fourth number $ 8 $ and Hazem chooses the fifth number $ 1 $ .
- Hossam chooses the fifth number $ 1 $ and Hazem chooses the fourth number $ 8 $ .

In the second example, the four ways are:

- Hossam chooses the second number $ 2 $ and Hazem chooses the sixth number $ 10 $ .
- Hossam chooses the sixth number $ 10 $ and Hazem chooses the second number $ 2 $ .
- Hossam chooses the fifth number $ 2 $ and Hazem chooses the sixth number $ 10 $ .
- Hossam chooses the sixth number $ 10 $ and Hazem chooses the fifth number $ 2 $ .

## 样例 #1

### 输入

```
2
5
6 2 3 8 1
6
7 2 8 3 2 10```

### 输出

```
2
4```

# AI分析结果

### 题目内容
# Hossam和组合数学

## 题目描述
Hossam醒来后觉得无聊，所以他决定和他的朋友Hazem一起创建一个有趣的数组。

现在，他们有一个包含$n$个正整数的数组$a$ ，Hossam将选择一个数字$a_i$ ，Hazem将选择一个数字$a_j$ 。

计算满足以下所有条件的有趣数对$(a_i, a_j)$的数量：
- $1 \le i, j \le n$ ；
- $i \neq j$ ；
- 绝对差$|a_i - a_j|$必须等于数组中所有数对的最大绝对差。更正式地说，$|a_i - a_j| = \max_{1 \le p, q \le n} |a_p - a_q|$ 。

## 说明/提示
在第一个示例中，两种方式是：
- Hossam选择第4个数$8$ ，Hazem选择第5个数$1$ 。
- Hossam选择第5个数$1$ ，Hazem选择第4个数$8$ 。

在第二个示例中，四种方式是：
- Hossam选择第2个数$2$ ，Hazem选择第6个数$10$ 。
- Hossam选择第6个数$10$ ，Hazem选择第2个数$2$ 。
- Hossam选择第5个数$2$ ，Hazem选择第6个数$10$ 。
- Hossam选择第6个数$10$ ，Hazem选择第5个数$2$ 。

## 样例 #1
### 输入
```
2
5
6 2 3 8 1
6
7 2 8 3 2 10
```
### 输出
```
2
4
```

### 算法分类
数学

### 综合分析与结论
由于暂无题解，通用思路是先找出数组中的最大值和最小值，计算出最大绝对差。然后分别统计最大值和最小值的个数，根据排列组合原理，满足条件的有趣数对数量为最大值的个数乘以最小值的个数再乘以2（因为数对$(a_i, a_j)$ 和$(a_j, a_i)$ 是不同的情况）。

### 扩展思路
同类型题通常围绕数组元素间的差值关系以及组合计数展开。类似算法套路是先确定关键的边界值（如最大最小值），再基于这些边界值进行组合计算。

### 洛谷相似题目推荐
1. P1088 [NOIP2004 普及组] 火星人：涉及到排列组合与模拟，与本题在组合计数上有相似之处。
2. P1303 A*B Problem：看似简单的数学运算，实则考查对高精度乘法的理解，与本题同属数学范畴。
3. P1147 连续自然数和：通过数学推导和枚举来解决问题，与本题在运用数学方法解决数组相关问题上类似。 

---
处理用时：15.87秒