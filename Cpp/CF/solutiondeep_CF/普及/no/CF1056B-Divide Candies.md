# 题目信息

# Divide Candies

## 题目描述

Arkady and his friends love playing checkers on an $ n \times n $ field. The rows and the columns of the field are enumerated from $ 1 $ to $ n $ .

The friends have recently won a championship, so Arkady wants to please them with some candies. Remembering an old parable (but not its moral), Arkady wants to give to his friends one set of candies per each cell of the field: the set of candies for cell $ (i, j) $ will have exactly $ (i^2 + j^2) $ candies of unique type.

There are $ m $ friends who deserve the present. How many of these $ n \times n $ sets of candies can be split equally into $ m $ parts without cutting a candy into pieces? Note that each set has to be split independently since the types of candies in different sets are different.

## 说明/提示

In the first example, only the set for cell $ (3, 3) $ can be split equally ( $ 3^2 + 3^2 = 18 $ , which is divisible by $ m=3 $ ).

In the second example, the sets for the following cells can be divided equally:

- $ (1, 2) $ and $ (2, 1) $ , since $ 1^2 + 2^2 = 5 $ , which is divisible by $ 5 $ ;
- $ (1, 3) $ and $ (3, 1) $ ;
- $ (2, 4) $ and $ (4, 2) $ ;
- $ (2, 6) $ and $ (6, 2) $ ;
- $ (3, 4) $ and $ (4, 3) $ ;
- $ (3, 6) $ and $ (6, 3) $ ;
- $ (5, 5) $ .

In the third example, sets in all cells can be divided equally, since $ m = 1 $ .

## 样例 #1

### 输入

```
3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 5
```

### 输出

```
13
```

## 样例 #3

### 输入

```
1000000000 1
```

### 输出

```
1000000000000000000
```

# AI分析结果

### 题目内容重写

#### 题目描述

Arkady 和他的朋友们喜欢在一个 $n \times n$ 的棋盘上玩跳棋。棋盘的行和列从 $1$ 到 $n$ 编号。

朋友们最近赢得了一个冠军，Arkady 想用一些糖果来犒劳他们。他想起了一个古老的寓言（但没有记住其寓意），决定为棋盘的每个格子准备一份糖果：格子 $(i, j)$ 的糖果集合将包含恰好 $i^2 + j^2$ 颗独特类型的糖果。

有 $m$ 个朋友值得这份礼物。有多少个这样的 $n \times n$ 糖果集合可以被平均分成 $m$ 份，而不需要将任何一颗糖果切碎？注意，每个集合必须独立分割，因为不同集合中的糖果类型是不同的。

#### 说明/提示

在第一个例子中，只有格子 $(3, 3)$ 的集合可以被平均分割（$3^2 + 3^2 = 18$，可以被 $m=3$ 整除）。

在第二个例子中，以下格子的集合可以被平均分割：

- $(1, 2)$ 和 $(2, 1)$，因为 $1^2 + 2^2 = 5$，可以被 $5$ 整除；
- $(1, 3)$ 和 $(3, 1)$；
- $(2, 4)$ 和 $(4, 2)$；
- $(2, 6)$ 和 $(6, 2)$；
- $(3, 4)$ 和 $(4, 3)$；
- $(3, 6)$ 和 $(6, 3)$；
- $(5, 5)$。

在第三个例子中，所有格子的集合都可以被平均分割，因为 $m = 1$。

#### 样例 #1

##### 输入

```
3 3
```

##### 输出

```
1
```

#### 样例 #2

##### 输入

```
6 5
```

##### 输出

```
13
```

#### 样例 #3

##### 输入

```
1000000000 1
```

##### 输出

```
1000000000000000000
```

### 算法分类

数学

### 题解分析与结论

题目要求计算满足 $i^2 + j^2$ 能被 $m$ 整除的格子数量。由于 $n$ 可能很大，直接枚举会超时，因此需要利用数学性质进行优化。

#### 题解1：Sooke

**星级：4.5星**

**关键亮点：**
- 利用模运算的性质，将问题转化为在模 $m$ 意义下的余数统计。
- 通过周期性分析，减少了计算量，避免了直接枚举。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
for (int i = 1; i <= m; i++) { cnt[i * i % m] += n / m; } // 加上周期长度.
for (int i = n / m * m + 1; i <= n; i++) { cnt[1ll * i * i % m]++; } // 处理零散部分.
for (int i = 0; i < m; i++) { ans += cnt[i] * cnt[i ? m - i : 0]; } // 合并计算.
```

**实现思想：**
- 首先计算每个周期内 $i^2 \mod m$ 的余数，并统计每种余数的出现次数。
- 然后处理剩余的零散部分，更新余数统计。
- 最后根据余数统计结果，计算满足条件的格子数量。

### 最优关键思路

利用模运算的周期性和余数统计，将问题转化为在模 $m$ 意义下的余数匹配问题，从而大大减少了计算量。

### 拓展思路

类似的问题可以利用模运算的性质进行优化，例如在计算大范围内满足某种条件的数时，可以通过模运算的周期性来减少计算量。

### 推荐题目

1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)

---
处理用时：30.46秒