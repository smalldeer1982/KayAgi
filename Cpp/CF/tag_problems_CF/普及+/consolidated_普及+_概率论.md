---
title: "Santa's Bot"
layout: "post"
diff: 普及+/提高
pid: CF1279D
tag: ['概率论']
---

# Santa's Bot

## 题目描述

Santa Claus has received letters from $ n $ different kids throughout this year. Of course, each kid wants to get some presents from Santa: in particular, the $ i $ -th kid asked Santa to give them one of $ k_i $ different items as a present. Some items could have been asked by multiple kids.

Santa is really busy, so he wants the New Year Bot to choose the presents for all children. Unfortunately, the Bot's algorithm of choosing presents is bugged. To choose a present for some kid, the Bot does the following:

- choose one kid $ x $ equiprobably among all $ n $ kids;
- choose some item $ y $ equiprobably among all $ k_x $ items kid $ x $ wants;
- choose a kid $ z $ who will receive the present equipropably among all $ n $ kids (this choice is independent of choosing $ x $ and $ y $ ); the resulting triple $ (x, y, z) $ is called the decision of the Bot.

If kid $ z $ listed item $ y $ as an item they want to receive, then the decision valid. Otherwise, the Bot's choice is invalid.

Santa is aware of the bug, but he can't estimate if this bug is really severe. To do so, he wants to know the probability that one decision generated according to the aforementioned algorithm is valid. Can you help him?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of kids who wrote their letters to Santa.

Then $ n $ lines follow, the $ i $ -th of them contains a list of items wanted by the $ i $ -th kid in the following format: $ k_i $ $ a_{i, 1} $ $ a_{i, 2} $ ... $ a_{i, k_i} $ ( $ 1 \le k_i, a_{i, j} \le 10^6 $ ), where $ k_i $ is the number of items wanted by the $ i $ -th kid, and $ a_{i, j} $ are the items themselves. No item is contained in the same list more than once.

It is guaranteed that $ \sum \limits_{i = 1}^{n} k_i \le 10^6 $ .

## 输出格式

Print the probatility that the Bot produces a valid decision as follows:

Let this probability be represented as an irreducible fraction $ \frac{x}{y} $ . You have to print $ x \cdot y^{-1} \mod 998244353 $ , where $ y^{-1} $ is the inverse element of $ y $ modulo $ 998244353 $ (such integer that $ y \cdot y^{-1} $ has remainder $ 1 $ modulo $ 998244353 $ ).

## 样例 #1

### 输入

```
2
2 2 1
1 1

```

### 输出

```
124780545

```

## 样例 #2

### 输入

```
5
2 1 2
2 3 1
3 2 4 3
2 1 4
3 4 3 2

```

### 输出

```
798595483

```



---

---
title: "Distance in Tree"
layout: "post"
diff: 普及+/提高
pid: CF161D
tag: ['点分治', '分治', '概率论']
---

# Distance in Tree

## 题目描述

## 题目大意
输入点数为$N$一棵树

求树上长度恰好为$K$的路径个数

## 输入格式

第一行两个数字$N,K$,如题意

接下来的$N-1$行中,每行两个整数$u,v$表示一条树边$(u,v)$

## 输出格式

一个整数$ans$,如题意

在$Codeforces$上提交时记得用$\%I64d$哦.QwQ

## 说明/提示

$1 \leq n \leq 50000$

$1 \leq k \leq 500$

感谢@Zhang_RQ 提供的翻译

## 样例 #1

### 输入

```
5 2
1 2
2 3
3 4
2 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 3
1 2
2 3
3 4
4 5

```

### 输出

```
2

```



---

---
title: "Math Division"
layout: "post"
diff: 普及+/提高
pid: CF2081A
tag: ['动态规划 DP', '概率论']
---

# Math Division

## 题目描述

Ecrade 有一个整数 $x$。他将以长度为 $n$ 的二进制数的形式向你展示这个数。

存在两种操作：
1. 将 $x$ 替换为 $\left\lfloor \frac{x}{2}\right\rfloor$，其中 $\left\lfloor \frac{x}{2}\right\rfloor$ 是小于等于 $\frac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \frac{x}{2}\right\rceil$，其中 $\left\lceil \frac{x}{2}\right\rceil$ 是大于等于 $\frac{x}{2}$ 的最小整数。

Ecrade 将执行若干次操作直到 $x$ 变为 $1$。每次操作时，他会独立地以 $\frac{1}{2}$ 的概率选择执行第一种操作或第二种操作。

Ecrade 想知道他将执行的操作次数的期望值（模 $10^9 + 7$）。由于问题有一定难度，请你帮助他！

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^5$）——测试用例数量。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^5$）——$x$ 的二进制表示长度。

每个测试用例的第二行包含一个长度为 $n$ 的二进制字符串：表示 $x$ 的二进制形式，从最高有效位到最低有效位给出。保证 $x$ 的最高有效位为 $1$。

保证所有测试用例的 $n$ 总和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出一个整数表示 Ecrade 将执行的操作次数的期望值（模 $10^9 + 7$）。

形式化地，令 $M = 10^9 + 7$。可以证明精确答案可以表示为不可约分数 $\dfrac{p}{q}$，其中 $p$ 和 $q$ 为整数且 $q \not \equiv 0 \pmod{M}$。请输出 $p \cdot q^{-1} \bmod M$。换句话说，输出满足 $0 \le x < M$ 且 $x \cdot q \equiv p \pmod{M}$ 的整数 $x$。

## 说明/提示

为简化描述，我们将第一种操作称为 $\text{OPER 1}$，第二种操作称为 $\text{OPER 2}$。

第一个测试用例中，$x=6$，存在六种可能的操作序列：
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。

因此，操作次数的期望为 $2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} + 2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} = \dfrac{5}{2} \equiv 500\,000\,006 \pmod{10^9 + 7}$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3
110
3
100
10
1101001011
```

### 输出

```
500000006
2
193359386
```



---

---
title: "Greg and Graph"
layout: "post"
diff: 普及+/提高
pid: CF295B
tag: ['枚举', '最短路', '概率论']
---

# Greg and Graph

## 题目描述

Greg 有一个有边权的有向图，包含 $n$ 个点。这个图的每两个点之间都有两个方向的边。Greg 喜欢用他的图玩游戏，现在他发明了一种新游戏：

- 游戏包含 $n$ 步。
- 第 $i$ 步 Greg 从图中删掉编号为 $x_i$ 的点。当删除一个点时，这个点的出边和入边都会被删除。
- 在执行每一步之前，Greg 想知道所有点对间最短路长度的和。最短路可以经过任何没删掉的点。换句话说，如果我们假设 $d(i, v, u)$ 是在删掉 $x_i$ 前 $v$ 和 $u$ 间的最短路长度，那么Greg想知道下面这个求和的值：$\sum_{v, u, v \neq u} d(i, v, u)$ 。

帮帮 Greg，输出每一步之前要求的值。

## 输入格式

第一行包含一个整数 $n \ (1 \leq n \leq 500)$ ，代表图中的点数。

下面 $n$ 行每行包含 $n$ 个整数，代表边权：第 $i$ 行的第 $j$ 个数 $a_{ij} \ (1 \leq a_{ij} \leq 10^5, a_{ii} = 0)$ 代表从 $i$ 到 $j$ 的边权。

最后一行包含 $n$ 个整数：$x_1, x_2, \dots, x_n \ (1 \leq x_i \leq n)$ ，分别为Greg每一步删掉的点的编号。

## 输出格式

输出 $n$ 个整数，第 $i$ 个数等于游戏的第 $i$ 步之前统计的求和值。

请不要在 C++ 中使用 `%lld` 标志来输出 64 位整数 `long long`，推荐使用 `cin, cout` 流或者用 `%I64d` 标志。

Translated by @KSkun

## 样例 #1

### 输入

```
1
0
1

```

### 输出

```
0 
```

## 样例 #2

### 输入

```
2
0 5
4 0
1 2

```

### 输出

```
9 0 
```

## 样例 #3

### 输入

```
4
0 3 1 1
6 0 400 1
2 4 0 1
1 1 1 0
4 1 2 3

```

### 输出

```
17 23 404 0 
```



---

---
title: "Bookshelves"
layout: "post"
diff: 普及+/提高
pid: CF981D
tag: ['贪心', '概率论', '位运算']
---

# Bookshelves

## 题目描述

## 题意：

$Keks$ 先生是 $Byteland$ 大陆的典型的白领。

他办公室里有一个书架，上面有几本书，每本书都有一个值为正整数的价格。

$Keks$ 先生把书架的价值定义为书价的总和。         

出乎意料地是， $Keks$ 先生升职了，现在他要去一个新的办公室。

他知道，在新的办公室里，他将有不止一个书架，而恰恰是 $K$ 个书架。

他认为 $K$ 个书架的美丽程度在于所有书架的价值的“按位与”和。 

他还决定不花时间重新整理书籍，所以他会先把几本书放在第一个书架上，下几本书放在下一个书架上，以此类推。当然，他会在每一个架子上放置至少一本书。这样，他会把所有的书放在 $K$ 个书架上，尽量使书架的美观程度越大越好。计算这个最大可能的美丽程度。

## 输入格式

两行，

第一行两个数：$n,k$ 书本数，书架数。

第二行 $n$ 个整数，每本书的价值。

## 输出格式

一个数，最大可能的美丽程度

## 样例 #1

### 输入

```
10 4
9 14 28 1 7 13 15 29 2 31

```

### 输出

```
24

```

## 样例 #2

### 输入

```
7 3
3 14 15 92 65 35 89

```

### 输出

```
64

```



---

