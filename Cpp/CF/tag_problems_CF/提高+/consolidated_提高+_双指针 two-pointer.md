---
title: "Boring Segments"
layout: "post"
diff: 提高+/省选-
pid: CF1555E
tag: ['线段树', '排序', '双指针 two-pointer']
---

# Boring Segments

## 题目描述

You are given $ n $ segments on a number line, numbered from $ 1 $ to $ n $ . The $ i $ -th segments covers all integer points from $ l_i $ to $ r_i $ and has a value $ w_i $ .

You are asked to select a subset of these segments (possibly, all of them). Once the subset is selected, it's possible to travel between two integer points if there exists a selected segment that covers both of them. A subset is good if it's possible to reach point $ m $ starting from point $ 1 $ in arbitrary number of moves.

The cost of the subset is the difference between the maximum and the minimum values of segments in it. Find the minimum cost of a good subset.

In every test there exists at least one good subset.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 3 \cdot 10^5 $ ; $ 2 \le m \le 10^6 $ ) — the number of segments and the number of integer points.

Each of the next $ n $ lines contains three integers $ l_i $ , $ r_i $ and $ w_i $ ( $ 1 \le l_i < r_i \le m $ ; $ 1 \le w_i \le 10^6 $ ) — the description of the $ i $ -th segment.

In every test there exists at least one good subset.

## 输出格式

Print a single integer — the minimum cost of a good subset.

## 样例 #1

### 输入

```
5 12
1 5 5
3 4 10
4 10 6
11 12 5
10 12 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 10
1 10 23
```

### 输出

```
0
```



---

---
title: "Chopping Carrots (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1706D2
tag: ['数学', '线段树', '双指针 two-pointer']
---

# Chopping Carrots (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 输入格式

第一行包括一个整数 $t$（$ 1 \le t \le 100 $），表示接下来测试组的数量。

对于每一个测试组，第一行包括两个整数 $n$ 和 $k$（$ 1 \le n, k \le 10^5 $）。

对于每一个测试组，第二行包括 $n$ 个整数 $ a_1, a_2, \ldots, a_n $（$ 1 \le a_1 \le a_2 \le \ldots \le a_n \le 10^5 $）。

保证 $\sum n \le 10^5$。

## 输出格式

对于每一个测试组，输出一个整数，表示满足上述条件的数组 $p$ 的花费的最小值。

## 样例 #1

### 样例输入 #1

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 样例输出 #1

```
2
0
13
1
4
7
0
```

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 输出

```
2
0
13
1
4
7
0
```



---

---
title: "Hossam and a Letter"
layout: "post"
diff: 提高+/省选-
pid: CF1771E
tag: ['动态规划 DP', '枚举', '双指针 two-pointer']
---

# Hossam and a Letter

## 题目描述

Hossam bought a new piece of ground with length $ n $ and width $ m $ , he divided it into an $ n \cdot m $ grid, each cell being of size $ 1\times1 $ .

Since Hossam's name starts with the letter 'H', he decided to draw the capital letter 'H' by building walls of size $ 1\times1 $ on some squares of the ground. Each square $ 1\times1 $ on the ground is assigned a quality degree: perfect, medium, or bad.

The process of building walls to form up letter 'H' has the following constraints:

- The letter must consist of one horizontal and two vertical lines.
- The vertical lines must not be in the same or neighboring columns.
- The vertical lines must start in the same row and end in the same row (and thus have the same length).
- The horizontal line should connect the vertical lines, but must not cross them.
- The horizontal line can be in any row between the vertical lines (not only in the middle), except the top and the bottom one. (With the horizontal line in the top row the letter looks like 'n', and in the bottom row like 'U'.)
- It is forbidden to build walls in cells of bad quality.
- You can use at most one square of medium quality.
- You can use any number of squares of perfect quality.

Find the maximum number of walls that can be used to draw the letter 'H'.

Check the note for more clarification.

## 输入格式

The first line of the input contains two integer numbers $ n $ , $ m $ ( $ 1 \le n, m \le 400 $ ).

The next $ n $ lines of the input contain $ m $ characters each, describing the grid. The character '.' stands for a perfect square, the character 'm' stands for a medium square, and the character '\#' stands for a bad square.

## 输出格式

Print a single integer — the maximum number of walls that form a capital letter 'H'.

If it is not possible to draw any letter 'H', print $ 0 $ .

## 说明/提示

In the first test case, we can't build the letter 'H'.

For the second test case, the figure below represents the grid and some of the valid letters 'H'. Perfect, medium, and bad squares are represented with white, yellow, and black colors respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771E/7ab52d112de710667f4c7cf4e814613751fe43eb.png)

## 样例 #1

### 输入

```
2 3
#m.
.#.
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7 8
...#.m..
..m...m.
.#..#.m#
...m..m.
m.......
..#.m.mm
......m.
```

### 输出

```
16
```



---

---
title: "Trees and Segments"
layout: "post"
diff: 提高+/省选-
pid: CF1858D
tag: ['动态规划 DP', '双指针 two-pointer']
---

# Trees and Segments

## 题目描述

# 树木与区间


夏季信息学学校的教师们决定在一排中种植 $ n $ 棵树，而且决定只种植橡树和冷杉树。为此，他们制定了一个计划，可以用长度为 $ n $ 的二进制字符串 $ s $ 表示。如果 $ s_i = 0 $，则第 $ i $ 棵树应该是橡树，如果 $ s_i = 1 $，则第 $ i $ 棵树应该是冷杉树。

树木种植的日子就是明天，后天一个督察将来到学校。督察非常喜欢大自然，他将根据以下方式评估这一排树的美丽程度：

- 首先，他将计算 $ l_0 $，作为该计划 $ s $ 中连续的橡树的最大数目（计划 $ s $ 中由零构成的最大子串）。如果树行中没有橡树，则 $ l_0 = 0 $。
- 然后，他将计算 $ l_1 $，作为该计划 $ s $ 中连续的冷杉树的最大数目（计划 $ s $ 中由一构成的最大子串）。如果树行中没有冷杉树，则 $ l_1 = 0 $。
- 最后，他将计算树行的美丽程度为 $ a \cdot l_0 + l_1 $，其中 $ a $ 是督察最喜欢的数。

教师们知道参数 $ a $ 的值，但出于安全原因，他们不能告诉你。他们只告诉你 $ a $ 是从 $ 1 $ 到 $ n $ 的整数。

由于树木尚未种植，教师们决定在不超过 $ k $ 棵树上更改树的类型（即在计划中从 $ 0 $ 更改为 $ 1 $ 或从 $ 1 $ 更改为 $ 0 $），以便根据督察的计算来最大化树行的美丽程度。

对于从 $ 1 $ 到 $ n $ 的每个整数 $ j $ 独立回答以下问题：

- 如果督察最喜欢的数为 $ j $，则在不超过 $ k $ 次更改的情况下，教师们可以通过更改树的类型来实现树行的最大美丽程度是多少？

## 输入格式

第一行包含一个整数 $ t $（$ 1 \le t \le 1000 $） — 测试用例的数量。

每个测试用例由一行组成，包含两个整数 $ n $ 和 $ k $（$ 1 \le n \le 3000 $，$ 0 \le k \le n $） — 行中树木的数量以及最大更改次数。

第二行包含长度为 $ n $ 的字符串 $ s $，由零和一组成 — 计划的描述。

保证所有测试用例中的所有 $ n $ 值的总和不超过 $ 3000 $。

## 输出格式

对于每个测试用例，输出 $ n $ 个整数，其中第 $ j $ 个整数（$ 1 \le j \le n $）是在使用 $ a = j $ 计算美丽程度后，教师们在不超过 $ k $ 次更改的情况下可以实现的树行的最大美丽程度。

## 样例 #1

### 样例输入 #1

```
5
3 0
111
4 1
0110
5 0
10000
6 2
101101
7 1
0001101
```

### 样例输出 #1

```
3 3 3 
4 5 7 9 
5 9 13 17 21 
6 9 13 17 21 25 
7 10 13 17 21 25 29
```

## 说明/提示

在第一个测试用例中，不允许进行任何更改，因此始终满足 $ l_0 = 0 $ 和 $ l_1 = 3 $。因此，不管 $ a $ 的值如何，树行的美丽程度都将是 $ 3 $。

在第二个测试用例中，对于 $ a \in \{1, 2\} $，教师们可以将计划 $ s $ 更改为 $ 0111 $（通过更改 $ s_4 $），对于 $ a \in \{3, 4\} $，他们可以将计划 $ s $ 更改为 $ 0010 $（通过更改 $ s_2 $）。在这种情况下，每个 $ a $ 的树行的美丽程度计算如下：

- 对于 $ a = 1 $：$ l_0 = 1 $，$ l_1 = 3 $。树行的美丽程度为 $ 1\cdot 1 + 3 = 4 $。
- 对于 $ a = 2 $：$ l_0 = 1 $，$ l_1 = 3 $。树行的美丽程度为 $ 2\cdot 1 + 3 = 5 $。
- 对于 $ a = 3 $：$ l_0 = 2 $，$ l_1 = 1 $。树行的美丽程度为 $ 3\cdot 2 + 1 = 7 $。
- 对于 $ a = 4 $：$ l_0 = 2 $，$ l_1 = 1 $。树行的美丽程度为 $ 4\cdot 2 + 1 = 9 $。

可以证明，上述更改对于所有 $ a $ 从 $ 1 $ 到 $ 4 $ 都是最优的。

## 样例 #1

### 输入

```
5
3 0
111
4 1
0110
5 0
10000
6 2
101101
7 1
0001101
```

### 输出

```
3 3 3 
4 5 7 9 
5 9 13 17 21 
6 9 13 17 21 25 
7 10 13 17 21 25 29
```



---

---
title: "Blossom"
layout: "post"
diff: 提高+/省选-
pid: CF2084E
tag: ['数学', '前缀和', '双指针 two-pointer']
---

# Blossom

## 题目描述

给定一个长度为 $n$ 的排列 $a$ $^{\text{∗}}$，其中部分元素缺失（用 $-1$ 表示）。

定义一个排列的值为其所有非空子段 $^{\text{‡}}$ 的 MEX $^{\text{†}}$ 之和。

求所有可能通过填充 $a$ 中缺失元素形成的有效排列的值的总和，结果对 $10^9 + 7$ 取模。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $0$ 到 $n - 1$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[1,2,0,4,3]$ 是一个排列，但 $[0,1,1]$ 不是排列（因为 $1$ 在数组中出现了两次），$[0,2,3]$ 也不是排列（因为 $n=3$ 但数组中包含 $3$）。

$^{\text{†}}$ 整数集合 $c = \{c_1, c_2, \ldots, c_k\}$ 的最小排除值（MEX）定义为不包含在 $c$ 中的最小非负整数 $x$。

$^{\text{‡}}$ 序列 $a$ 是序列 $b$ 的子段，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 1000$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5000$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$-1 \le a_i < n$）。  

保证 $a$ 中非 $-1$ 的元素互不相同。  
保证所有测试用例的 $n$ 之和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——所有可能有效排列的值的总和对 $10^9 + 7$ 取模的结果。


## 说明/提示

- 在第一个测试用例中，唯一有效的排列是 $[0, 1]$，其值为 $3$，因为：
  $$
  \operatorname{mex}([0]) + \operatorname{mex}([1]) + \operatorname{mex}([0, 1]) = 1 + 0 + 2 = 3
  $$
  因此答案为 $3$。

- 在第二个测试用例中，有两个有效排列：$[0, 1]$ 和 $[1, 0]$。$[0, 1]$ 和 $[1, 0]$ 的值均为 $3$，因此答案为 $3 + 3 = 6$。

- 在第四个测试用例中，有两个有效排列：$[0, 2, 1]$ 和 $[1, 2, 0]$。$[0, 2, 1]$ 的值为 $5$，因为：
  $$
  \operatorname{mex}([0]) + \operatorname{mex}([2]) + \operatorname{mex}([1]) + \operatorname{mex}([0, 2]) + \operatorname{mex}([2, 1]) + \operatorname{mex}([0, 2, 1]) = 1 + 0 + 0 + 1 + 0 + 3 = 5
  $$
  $[1, 2, 0]$ 的值也为 $5$，因为：
  $$
  \operatorname{mex}([1]) + \operatorname{mex}([2]) + \operatorname{mex}([0]) + \operatorname{mex}([1, 2]) + \operatorname{mex}([2, 0]) + \operatorname{mex}([1, 2, 0]) = 0 + 0 + 1 + 0 + 1 + 3 = 5
  $$
  因此答案为 $5 + 5 = 10$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2
0 -1
2
-1 -1
3
2 0 1
3
-1 2 -1
5
-1 0 -1 2 -1
```

### 输出

```
3
6
7
10
104
```



---

