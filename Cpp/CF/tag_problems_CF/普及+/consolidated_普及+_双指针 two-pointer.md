---
title: "Same Count One"
layout: "post"
diff: 普及+/提高
pid: CF1774D
tag: ['贪心', '构造', '双指针 two-pointer']
---

# Same Count One

## 题目描述

给定 $n$ 个长度为 $m$ 的，只包含 $0$ 和 $1$ 的数组，选择任意两个数组交换位置 $pos$ 上的数。在经过最少的操作后使得每个数组中的 $1$ 数量相等，并输出操作过程。

## 输入格式

第一行一个整数 $t$  $( 1 \leq t \leq 2\cdot 10^4 )$ 表示有 $t$ 组测试数据。

每组测试数据：第一行两个整数 $ n $ 和 $ m $ 。 $( 2 \leq n \leq 10^5 $ , $ 2 \leq m \leq 10^5 , \sum n\times m \le 10^6)$ 

接下来 $ n $ 行，每行 $ m $ 个整数（ $ 0 $ 或 $ 1 $ ）。

## 输出格式

对于每一组测试样例，若无法满足要求，输出 $ -1 $ .

否则, 第一行输出一个整数 $ k $ $ (0 \le k \le mn) $ ，即最小的操作数量。

接下来输出 $ k $ 行，每行 $ 3 $ 个整数, $ x, y, z $ $ (1 \le x, y \le n, 1 \le z \le m) $ , 表示交换 $ a_{x, z}, a_{y, z} $ : 即交换第 $ x $ 和第 $ y $ 行的第 $ z $ 个数。

## 样例 #1

### 输入

```
3
3 4
1 1 1 0
0 0 1 0
1 0 0 1
4 3
1 0 0
0 1 1
0 0 1
0 0 0
2 2
0 0
0 1
```

### 输出

```
1
2 1 1
1
4 2 2
-1
```



---

---
title: "Cutting Game"
layout: "post"
diff: 普及+/提高
pid: CF1974F
tag: ['二分', '双指针 two-pointer']
---

# Cutting Game

## 题目描述

Alice and Bob were playing a game again. They have a grid of size $ a \times b $ ( $ 1 \le a, b \le 10^9 $ ), on which there are $ n $ chips, with at most one chip in each cell. The cell at the intersection of the $ x $ -th row and the $ y $ -th column has coordinates $ (x, y) $ .

Alice made the first move, and the players took turns. On each move, a player could cut several (but not all) rows or columns from the beginning or end of the remaining grid and earn a point for each chip that was on the cut part of the grid. Each move can be described by the character 'U', 'D', 'L', or 'R' and an integer $ k $ :

- If the character is 'U', then the first $ k $ remaining rows will be cut;
- If the character is 'D', then the last $ k $ remaining rows will be cut;
- If the character is 'L', then the first $ k $ remaining columns will be cut;
- If the character is 'R', then the last $ k $ remaining columns will be cut.

Based on the initial state of the grid and the players' moves, determine the number of points earned by Alice and Bob, respectively.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ a $ , $ b $ , $ n $ , and $ m $ ( $ 2 \le a, b \le 10^9 $ , $ 1 \le n, m \le 2 \cdot 10^5 $ ) — the dimensions of the grid, the number of chips, and the number of moves.

Each of the next $ n $ lines contain two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i \le a $ , $ 1 \le y_i \le b $ ) — the coordinates of the chips. All pairs of coordinates are distinct.

Each of the next $ m $ lines contain a character $ c_j $ and an integer $ k_j $ — the description of the $ j $ -th move. It is guaranteed that $ k $ is less than the number of rows/columns in the current grid. In other words, a player cannot cut the entire remaining grid on their move.

It is guaranteed that the sum of the values of $ n $ across all test cases in the test does not exceed $ 2 \cdot 10^5 $ . It is guaranteed that the sum of the values of $ m $ across all test cases in the test does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two integers — the number of points earned by Alice and Bob, respectively.

## 说明/提示

Below is the game from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974F/9f1554443f39a3c1eca0a96dffd50920759ede0a.png)On her turn, Alice cut $ 2 $ rows from the bottom and scored $ 2 $ points, then Bob cut $ 1 $ column from the right and scored one point. Note that if Bob had cut $ 1 $ row from the bottom, he would have also scored $ 1 $ point.

## 样例 #1

### 输入

```
6
4 4 3 2
4 1
3 3
2 4
D 2
R 1
4 4 3 3
4 1
3 2
2 3
D 1
L 1
U 2
3 5 3 2
1 3
2 2
3 3
R 2
R 2
6 4 4 2
1 4
2 3
5 3
1 1
R 1
U 1
9 3 2 1
6 1
3 3
D 8
10 10 2 5
7 5
9 1
R 1
L 2
D 1
U 4
D 1
```

### 输出

```
2 1
2 0
0 3
1 1
2 0
0 1
```



---

---
title: "Kachina's Favorite Binary String"
layout: "post"
diff: 普及+/提高
pid: CF2037E
tag: ['贪心', '双指针 two-pointer']
---

# Kachina's Favorite Binary String

## 题目描述

这是一道交互题。

卡齐娜有一个长为 $n$ 的 01 串 $s$。她定义 $f(l,r)$ 为子段 $s_ls_{l+1}\cdots s_r$ 中等于 $\texttt{01}$ 的子序列的个数。子序列不要求连续；两个位置不同的子序列被认为是 **不同** 的，即便它们含有相同的字符序列。

你需要通过向卡齐娜提问来猜出 $s$。每次提问，你可以选择两个下标 $l,r(1\le l < r\le n)$，询问她 $f(l,r)$ 的值。你最多提问 $n$ 次。如果 $s$ 不可能在 $n$ 次询问内确定，输出 $\texttt{IMPOSSIBLE}$。

## 输入格式

第一行一个整数 $t(1\le t\le 10^3)$ — 测试数据的组数。

每组测试数据一行一个整数 $n(2\le n\le 10^4)$ — 01 串 $s$ 的长度。

保证各组测试数据 $n$ 的总和不超过 $10^4$。

## 输出格式

每次提问，按照以下格式输出一行（不含括号）：

- $\texttt{? l r}(1\le l < r\le n)$

测试程序会返回一个整数 $f(l,r)$。当你确定答案后，按照以下格式输出一行：

- 如果 $s$ 无法确定，输出 $\texttt{"! IMPOSSIBLE"}$
- 否则输出 $\texttt{"! s"}$

输出答案不算一次提问。

## 说明/提示

**第一个样例：**

第一次提问中，你询问卡齐娜 $f(1,5)$ 的值，她向输入流中返回 $4$。

第二次提问中，你询问卡齐娜 $f(2,4)$ 的值。因为在 $\texttt{100}$ 中没有等于 $\texttt{01}$ 的子序列，她向输入流中返回 $0$。

提问四次后，你输出正确答案 $\texttt{01001}$。

**第二个样例：**

第一次提问中，你询问卡齐娜 $f(1,2)$ 的值，她向输入流中返回 $0$。

注意到你除了 $\texttt{? 1 2}$ 提不出别的问题了，但 01 串 $\texttt{00}$ 和 $\texttt{11}$ 的答案都是 $0$，无法确定唯一答案，所以输出 $\texttt{IMPOSSIBLE}$。

样例仅用于展示交互格式，不代表正解方法。

## 样例 #1

### 输入

```
2
5

4

0

1

2

2

0
```

### 输出

```
? 1 5

? 2 4

? 4 5

? 3 5

! 01001

? 1 2

! IMPOSSIBLE
```



---

---
title: "Local Construction"
layout: "post"
diff: 普及+/提高
pid: CF2103D
tag: ['构造', '双指针 two-pointer']
---

# Local Construction

## 题目描述

在数组 $b_1, b_2, \ldots, b_m$ 中，元素 $b_i$（$1 \le i \le m$）是局部最小值当且仅当满足以下至少一个条件：
- $2 \le i \le m - 1$ 且 $b_i < b_{i - 1}$ 且 $b_i < b_{i + 1}$，或
- $i = 1$ 且 $b_1 < b_2$，或
- $i = m$ 且 $b_m < b_{m - 1}$。

类似地，元素 $b_i$（$1 \le i \le m$）是局部最大值当且仅当满足以下至少一个条件：
- $2 \le i \le m - 1$ 且 $b_i > b_{i - 1}$ 且 $b_i > b_{i + 1}$，或
- $i = 1$ 且 $b_1 > b_2$，或
- $i = m$ 且 $b_m > b_{m - 1}$。

注意，对于只有一个元素的数组，局部最小值和局部最大值没有定义。

给定一个隐藏的排列 $^{\text{∗}}$ $p$，其长度为 $n$。对该排列交替执行以下两种操作，从操作 1 开始，直到 $p$ 中只剩一个元素：
- 操作 1 —— 删除 $p$ 中所有不是局部最小值的元素。
- 操作 2 —— 删除 $p$ 中所有不是局部最大值的元素。

具体来说，在每次奇数轮迭代时执行操作 1，在每次偶数轮迭代时执行操作 2，直到 $p$ 中只剩一个元素。

对于每个下标 $i$（$1 \le i \le n$），设 $a_i$ 为元素 $p_i$ 被删除的轮次编号，若未被删除则设为 $-1$。

可以证明，最多经过 $\lceil \log_2 n \rceil$ 轮迭代后 $p$ 中只剩一个元素（即 $a_i \le \lceil \log_2 n \rceil$）。

给定数组 $a_1, a_2, \ldots, a_n$，你的任务是构造任意一个满足数组 $a$ 的排列 $p$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是（因为 $2$ 出现了两次），$[1,3,4]$ 也不是（因为 $n=3$ 但出现了 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$）——排列 $p$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le \lceil \log_2 n \rceil$ 或 $a_i = -1$）——元素 $p_i$ 被删除的轮次编号。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

保证至少存在一个满足数组 $a$ 的排列 $p$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数，表示满足数组 $a$ 的排列。

如果有多个解，输出任意一个即可。

## 说明/提示

在第一个测试用例中，对排列 $[3, 2, 1]$ 执行的操作如下：
1. $[3, 2, 1]$ 的唯一局部最小值是 $1$，因此删除 $3$ 和 $2$。此时只剩一个元素，过程终止。
这满足数组 $a = [1, 1, -1]$，因为 $p_1$ 和 $p_2$ 在第 1 轮被删除，而 $p_3$ 未被删除。

在第二个测试用例中，对排列 $[4, 3, 5, 1, 2]$ 执行的操作如下：
1. $[4, 3, 5, 1, 2]$ 的局部最小值是 $3$ 和 $1$，因此删除 $4$、$5$ 和 $2$。
2. $[3, 1]$ 的唯一局部最大值是 $3$，因此删除 $1$。此时只剩一个元素，过程终止。
这满足数组 $a = [1, -1, 1, 2, 1]$，因为 $p_1$、$p_3$ 和 $p_5$ 在第 1 轮被删除，$p_4$ 在第 2 轮被删除，$p_2$ 未被删除。

在第三个测试用例中，对排列 $[6, 7, 2, 4, 3, 8, 5, 1]$ 执行的操作如下：
1. 局部最小值是 $6$、$2$、$3$ 和 $1$，因此删除 $7$、$4$、$8$ 和 $5$。
2. 局部最大值是 $6$ 和 $3$，因此删除 $2$ 和 $1$。
3. 局部最小值是 $3$，因此删除 $6$。此时只剩一个元素，过程终止。

在第四个测试用例中，一个满足条件的排列是 $[6, 5, 2, 1, 3, 4, 7]$。$1$ 是唯一的局部最小值，因此它会在第一轮后保留。注意，其他排列也可能满足条件，例如 $[6, 4, 3, 1, 2, 5, 7]$ 也是正确的解。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
3
1 1 -1
5
1 -1 1 2 1
8
3 1 2 1 -1 1 1 2
7
1 1 1 -1 1 1 1
5
1 1 1 1 -1
5
-1 1 1 1 1
5
-1 1 2 1 2
```

### 输出

```
3 2 1
4 3 5 1 2
6 7 2 4 3 8 5 1
6 5 2 1 3 4 7
5 4 3 2 1
1 2 3 4 5
4 5 2 3 1
```



---

---
title: "Diverse Substrings"
layout: "post"
diff: 普及+/提高
pid: CF386C
tag: ['枚举', '双指针 two-pointer']
---

# Diverse Substrings

## 题目描述

给定一个字符串 $s$，定义 $d(x)$ 为字符串 $x$ 内不同的字符个数。

求有多少个 $s$ 的子串 $s1$，使得 $d(s1)$ 为给定的 $t_{i}$。

## 输入格式

第一行包含一个字符串 $s$。

## 输出格式

第一行输出 $d(s)$。

然后输出 $t_1,t_2,\cdots,t_{d(s)}$ 对应的子串数量。

$1 \le |s| \le 3 \times 10^5$。

## 样例 #1

### 输入

```
abca

```

### 输出

```
3
4
3
3

```

## 样例 #2

### 输入

```
aabacaabbad

```

### 输出

```
4
14
19
28
5

```



---

