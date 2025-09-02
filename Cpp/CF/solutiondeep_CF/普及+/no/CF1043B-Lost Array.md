# 题目信息

# Lost Array

## 题目描述

Bajtek, known for his unusual gifts, recently got an integer array $ x_0, x_1, \ldots, x_{k-1} $ .

Unfortunately, after a huge array-party with his extraordinary friends, he realized that he'd lost it. After hours spent on searching for a new toy, Bajtek found on the arrays producer's website another array $ a $ of length $ n + 1 $ . As a formal description of $ a $ says, $ a_0 = 0 $ and for all other $ i $ ( $ 1 \le i \le n $ ) $ a_i = x_{(i-1)\bmod k} + a_{i-1} $ , where $ p \bmod q $ denotes the remainder of division $ p $ by $ q $ .

For example, if the $ x = [1, 2, 3] $ and $ n = 5 $ , then:

- $ a_0 = 0 $ ,
- $ a_1 = x_{0\bmod 3}+a_0=x_0+0=1 $ ,
- $ a_2 = x_{1\bmod 3}+a_1=x_1+1=3 $ ,
- $ a_3 = x_{2\bmod 3}+a_2=x_2+3=6 $ ,
- $ a_4 = x_{3\bmod 3}+a_3=x_0+6=7 $ ,
- $ a_5 = x_{4\bmod 3}+a_4=x_1+7=9 $ .

So, if the $ x = [1, 2, 3] $ and $ n = 5 $ , then $ a = [0, 1, 3, 6, 7, 9] $ .

Now the boy hopes that he will be able to restore $ x $ from $ a $ ! Knowing that $ 1 \le k \le n $ , help him and find all possible values of $ k $ — possible lengths of the lost array.

## 说明/提示

In the first example, any $ k $ is suitable, since $ a $ is an arithmetic progression.

Possible arrays $ x $ :

- $ [1] $
- $ [1, 1] $
- $ [1, 1, 1] $
- $ [1, 1, 1, 1] $
- $ [1, 1, 1, 1, 1] $

In the second example, Bajtek's array can have three or five elements.

Possible arrays $ x $ :

- $ [1, 2, 2] $
- $ [1, 2, 2, 1, 2] $

For example, $ k = 4 $ is bad, since it leads to $ 6 + x_0 = 8 $ and $ 0 + x_0 = 1 $ , which is an obvious contradiction.

In the third example, only $ k = n $ is good.

Array $ [1, 4, -2] $ satisfies the requirements.

Note that $ x_i $ may be negative.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
5
1 2 3 4 5 ```

## 样例 #2

### 输入

```
5
1 3 5 6 8
```

### 输出

```
2
3 5 ```

## 样例 #3

### 输入

```
3
1 5 3
```

### 输出

```
1
3 ```

# AI分析结果

### 题目内容
# 丢失的数组

## 题目描述
Bajtek以他独特的礼物而闻名，最近他得到了一个整数数组 $x_0, x_1, \ldots, x_{k - 1}$ 。

不幸的是，在与他那些非凡的朋友们举办了一场盛大的数组派对之后，他意识到自己把这个数组弄丢了。在花了几个小时寻找新玩具后，Bajtek在数组制造商的网站上找到了另一个长度为 $n + 1$ 的数组 $a$ 。正如对 $a$ 的形式描述所说，$a_0 = 0$ ，并且对于所有其他 $i$ （$1 \le i \le n$），$a_i = x_{(i - 1)\bmod k} + a_{i - 1}$ ，其中 $p \bmod q$ 表示 $p$ 除以 $q$ 的余数。

例如，如果 $x = [1, 2, 3]$ 且 $n = 5$ ，那么：
- $a_0 = 0$ ，
- $a_1 = x_{0\bmod 3}+a_0=x_0 + 0 = 1$ ，
- $a_2 = x_{1\bmod 3}+a_1=x_1 + 1 = 3$ ，
- $a_3 = x_{2\bmod 3}+a_2=x_2 + 3 = 6$ ，
- $a_4 = x_{3\bmod 3}+a_3=x_0 + 6 = 7$ ，
- $a_5 = x_{4\bmod 3}+a_4=x_1 + 7 = 9$ 。

所以，如果 $x = [1, 2, 3]$ 且 $n = 5$ ，那么 $a = [0, 1, 3, 6, 7, 9]$ 。

现在这个男孩希望他能够从 $a$ 中恢复出 $x$ ！已知 $1 \le k \le n$ ，请帮助他并找出所有可能的 $k$ 值 —— 丢失数组的可能长度。

## 说明/提示
在第一个示例中，任何 $k$ 都是合适的，因为 $a$ 是一个等差数列。

可能的数组 $x$ ：
- $[1]$
- $[1, 1]$
- $[1, 1, 1]$
- $[1, 1, 1, 1]$
- $[1, 1, 1, 1, 1]$

在第二个示例中，Bajtek的数组可以有三个或五个元素。

可能的数组 $x$ ：
- $[1, 2, 2]$
- $[1, 2, 2, 1, 2]$

例如，$k = 4$ 是不合适的，因为这会导致 $6 + x_0 = 8$ 且 $0 + x_0 = 1$ ，这显然是矛盾的。

在第三个示例中，只有 $k = n$ 是合适的。

数组 $[1, 4, -2]$ 满足要求。

注意，$x_i$ 可能是负数。

## 样例 #1
### 输入
```
5
1 2 3 4 5
```
### 输出
```
5
1 2 3 4 5 
```
## 样例 #2
### 输入
```
5
1 3 5 6 8
```
### 输出
```
2
3 5 
```
## 样例 #3
### 输入
```
3
1 5 3
```
### 输出
```
1
3 
```

### 算法分类
数学

### 题解综合分析与结论
这三道题解思路基本一致，都是先通过对数组 $a$ 求相邻两项的差得到可能的 $x$ 数组，再通过枚举 $k$ 值并检查 $x$ 数组每隔 $k$ 个元素是否相同来确定满足条件的 $k$ 。不同点在于检查元素是否相同的实现细节略有差异。整体来看，三道题解思路较为直接，代码实现也相对基础，没有复杂的优化，质量相近，均未达到4星水平。

### 通用建议与扩展思路
通用建议：在实现检查 $x$ 数组每隔 $k$ 个元素是否相同的逻辑时，可以考虑使用更高效的数据结构或算法优化，例如利用哈希表来存储已经检查过的元素模式，减少重复计算。
扩展思路：类似题目可以改变数组生成的规则，或者增加更多的限制条件，如要求 $x$ 数组元素满足特定范围等。还可以拓展到多维数组的情况。

### 洛谷相似题目推荐
1. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及到对序列的操作和规律分析，与本题对数组规律的探索类似。
2. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学方法解决数组相关问题，与本题利用数学关系处理数组的思路相似。
3. [P1441 砝码称重](https://www.luogu.com.cn/problem/P1441)：需要通过分析和枚举来解决问题，和本题通过枚举 $k$ 值解决问题的方式类似。 

---
处理用时：44.77秒