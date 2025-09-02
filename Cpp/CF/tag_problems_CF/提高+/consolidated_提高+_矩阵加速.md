---
title: "Magic Gems"
layout: "post"
diff: 提高+/省选-
pid: CF1117D
tag: ['动态规划 DP', '矩阵加速']
---

# Magic Gems

## 题目描述

xht37 有很多魔法宝石。每颗魔法宝石可以分解成 $ m $ 颗普通宝石，魔法宝石和普通宝石都占据 $ 1 $ 体积的空间，但普通宝石不能再被分解。

xht37 想要使一些魔法宝石分解，使得所有宝石占据的空间**恰好**为 $ n $ 单位体积。显然，一个魔法宝石分解后会占据 $ m $ 体积空间，不分解的魔法宝石仍占据 $ 1 $ 体积空间。

现在 xht37 想要求出有多少种分解方案，可以让最后得到的宝石**恰好**占据 $ n $ 单位体积。两种分解方案不同当且仅当分解的魔法宝石数量不同，或者是所用的宝石的编号不同。

xht37 当然知道怎么做，但是他想考考你。

## 输入格式

输入包含两个数字 $ n,m (1 \le N \le 10^{18},2 \le M \le 100)$ 。

## 输出格式

输出能使宝石占据恰好 $ n $ 体积的方案数。因为方案数实在太大了，请输出方案数 $ \mod 10^9+7 $ 后的结果。

### 样例解释

该样例中一颗魔法宝石可以分解得到两颗普通宝石，我们的目标是拿到 $ 4 $ 颗宝石。

让我们用 $ 1 $ 代表魔法宝石，$ 0 $ 代表普通宝石。

则存在如下几种方案：

* $ 1111 $ ：没有宝石被分解。
* $ 0011 $ ：第一颗宝石分解。
* $ 1001 $ ：第二颗宝石分解。
* $ 1100 $ ：第三颗宝石分解。
* $ 0000 $ ：第一颗和第二颗宝石分解。

因此答案为 $ 5 $ 。

## 样例 #1

### 输入

```
4 2

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
3

```



---

---
title: "Bro Thinks He's Him"
layout: "post"
diff: 提高+/省选-
pid: CF2065H
tag: ['动态规划 DP', '线段树', '树状数组', '矩阵加速', '前缀和']
---

# Bro Thinks He's Him

## 题目描述

Skibidus 自认为是"天选之人"！他通过解决这个难题证明了这一点。你也能证明自己吗？

给定一个二进制字符串 $^{\text{∗}}$ $t$，定义 $f(t)$ 为将 $t$ 分割成由相同字符组成的连续子串的最小数量。例如，$f(\texttt{00110001}) = 4$，因为 $t$ 可以被分割为 $\texttt{[00][11][000][1]}$，每个括号内的子串均由相同字符组成。

Skibidus 给你一个二进制字符串 $s$ 和 $q$ 次查询。每次查询会翻转字符串中的一个字符（即 $\texttt{0}$ 变为 $\texttt{1}$，$\texttt{1}$ 变为 $\texttt{0}$），且修改会保留到后续查询。每次查询后，你需要输出所有非空子序列 $^{\text{†}}$ $b$ 的 $f(b)$ 之和模 $998\,244\,353$ 的结果。

 $^{\text{∗}}$ 二进制字符串仅包含字符 $\texttt{0}$ 和 $\texttt{1}$。

 $^{\text{†}}$ 字符串的子序列是指通过删除原字符串中若干（可能为零）个字符得到的新字符串。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例数量。

每个测试用例的第一行包含一个二进制字符串 $s$（$1 \leq |s| \leq 2 \cdot 10^5$）。

每个测试用例的第二行包含一个整数 $q$（$1 \leq q \leq 2 \cdot 10^5$）——查询次数。

每个测试用例的第三行包含 $q$ 个整数 $v_1, v_2, \ldots, v_q$（$1 \leq v_i \leq |s|$），表示第 $i$ 次查询翻转 $s_{v_i}$ 处的字符。

保证所有测试用例的 $|s|$ 之和与 $q$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在一行中输出 $q$ 个整数——每次查询后的答案模 $998\,244\,353$。

## 说明/提示

第一个测试用例在第一次查询后，$s$ 变为 $\texttt{001}$。计算所有子序列的 $f$ 值：
- $f(s_1) = f(\texttt{0}) = 1$
- $f(s_2) = f(\texttt{0}) = 1$
- $f(s_3) = f(\texttt{1}) = 1$
- $f(s_1 s_2) = f(\texttt{00}) = 1$
- $f(s_1 s_3) = f(\texttt{01}) = 2$
- $f(s_2 s_3) = f(\texttt{01}) = 2$
- $f(s_1 s_2 s_3) = f(\texttt{001}) = 2$

这些值的总和为 $10$，模 $998\,244\,353$ 后结果为 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
101
2
1 3
10110
3
1 2 3
101110101
5
7 2 4 4 1
```

### 输出

```
10 7 
61 59 67 
1495 1169 1417 1169 1396
```



---

---
title: "Darth Vader and Tree"
layout: "post"
diff: 提高+/省选-
pid: CF514E
tag: ['动态规划 DP', '动态规划优化', '矩阵加速']
---

# Darth Vader and Tree

## 题目描述

When Darth Vader gets bored, he sits down on the sofa, closes his eyes and thinks of an infinite rooted tree where each node has exactly $ n $ sons, at that for each node, the distance between it an its $ i $ -th left child equals to $ d_{i} $ . The Sith Lord loves counting the number of nodes in the tree that are at a distance at most $ x $ from the root. The distance is the sum of the lengths of edges on the path between nodes.

But he has got used to this activity and even grew bored of it. 'Why does he do that, then?' — you may ask. It's just that he feels superior knowing that only he can solve this problem.

Do you want to challenge Darth Vader himself? Count the required number of nodes. As the answer can be rather large, find it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two space-separated integers $ n $ and $ x $ ( $ 1<=n<=10^{5},0<=x<=10^{9} $ ) — the number of children of each node and the distance from the root within the range of which you need to count the nodes.

The next line contains $ n $ space-separated integers $ d_{i} $ ( $ 1<=d_{i}<=100 $ ) — the length of the edge that connects each node with its $ i $ -th child.

## 输出格式

Print a single number — the number of vertexes in the tree at distance from the root equal to at most $ x $ .

## 说明/提示

Pictures to the sample (the yellow color marks the nodes the distance to which is at most three)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514E/dfa75ce6cc0df1087a16e02cadbd273a08641d03.png)

## 样例 #1

### 输入

```
3 3
1 2 3

```

### 输出

```
8

```



---

