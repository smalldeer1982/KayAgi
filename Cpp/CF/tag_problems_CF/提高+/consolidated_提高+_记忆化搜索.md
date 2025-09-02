---
title: "Classy Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF1036C
tag: ['搜索', '记忆化搜索', '数位 DP']
---

# Classy Numbers

## 题目描述

Let's call some positive integer classy if its decimal representation contains no more than $ 3 $ non-zero digits. For example, numbers $ 4 $ , $ 200000 $ , $ 10203 $ are classy and numbers $ 4231 $ , $ 102306 $ , $ 7277420000 $ are not.

You are given a segment $ [L; R] $ . Count the number of classy integers $ x $ such that $ L \le x \le R $ .

Each testcase contains several segments, for each of them you are required to solve the problem separately.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 10^4 $ ) — the number of segments in a testcase.

Each of the next $ T $ lines contains two integers $ L_i $ and $ R_i $ ( $ 1 \le L_i \le R_i \le 10^{18} $ ).

## 输出格式

Print $ T $ lines — the $ i $ -th line should contain the number of classy integers on a segment $ [L_i; R_i] $ .

## 样例 #1

### 输入

```
4
1 1000
1024 1024
65536 65536
999999 1000001

```

### 输出

```
1000
1
0
2

```



---

---
title: "Coloring Brackets"
layout: "post"
diff: 提高+/省选-
pid: CF149D
tag: ['搜索', '记忆化搜索', '区间 DP']
---

# Coloring Brackets

## 题目描述

### 题意描述

给出一个配对的括号序列（如 “$\texttt{(())()}$”、“$\texttt{()}$” 等，“$\texttt{)()}$”、“$\texttt{(()}$”是不符合要求的），对该序列按照以下方法染色。

1. 一个括号可以染成红色、蓝色或者不染色。
2. 一对匹配的括号需要且只能将其中一个染色。
3. 相邻两个括号颜色不能相同（但都可以不染色）。

求符合条件的染色方案数，对 $1000000007$ 取模。

## 输入格式

一行一个字符串 $s$，表示括号序列（$2 \leqslant |s| \leqslant 700$）。

## 输出格式

一个数字，表示染色的方案数（对 $1000000007$ 取模）。

## 样例 #1

### 输入

```
(())

```

### 输出

```
12

```

## 样例 #2

### 输入

```
(()())

```

### 输出

```
40

```

## 样例 #3

### 输入

```
()

```

### 输出

```
4

```



---

---
title: "Zebra-like Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF2086E
tag: ['数学', '贪心', '记忆化搜索', '数位 DP']
---

# Zebra-like Numbers

## 题目描述

我们称一个正整数为斑马数（zebra-like），如果它的二进制表示从最高有效位开始是交替的比特位，并且最低有效位等于 $1$。例如，数字 $1$、$5$ 和 $21$ 都是斑马数，因为它们的二进制表示 $1$、$101$ 和 $10101$ 满足要求，而数字 $10$ 不是斑马数，因为它的二进制表示 $1010$ 的最低有效位是 $0$。

我们定义一个正整数 $e$ 的斑马值为最小的整数 $p$，使得 $e$ 可以表示为 $p$ 个斑马数（可以相同也可以不同）的和。

给定三个整数 $l$、$r$ 和 $k$，计算满足 $l \le x \le r$ 且 $x$ 的斑马值等于 $k$ 的整数 $x$ 的数量。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。接下来是测试用例的描述。

每个测试用例的唯一一行包含三个整数 $l$、$r$（$1 \le l \le r \le 10^{18}$）和 $k$（$1 \le k \le 10^{18}$）。

## 输出格式

对于每个测试用例，输出一个整数——区间 $[l, r]$ 内斑马值为 $k$ 的整数的数量。

## 说明/提示

- 在第一个测试用例中，有 $13$ 个符合条件的数字：$3, 7, 11, 15, 23, 27, 31, 43, 47, 63, 87, 91, 95$。每个数字都可以表示为 $3$ 个斑马数的和。
- 在第二个测试用例中，数字 $1$ 的斑马值为 $1$，因此输出 $1$。
- 在第四个测试用例中，区间 $[2, 10]$ 内没有数字的斑马值为 $100$，因此输出 $0$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1 100 3
1 1 1
15 77 2
2 10 100
1234567 123456789101112131 12
```

### 输出

```
13
1
3
0
4246658701
```



---

---
title: "Zuma"
layout: "post"
diff: 提高+/省选-
pid: CF607B
tag: ['字符串', '搜索', '记忆化搜索', '区间 DP']
---

# Zuma

## 题目描述

$\texttt{Genos}$ 最近在他的手机上下载了祖玛游戏。在祖玛游戏里，存在 $n$ 个一行的宝石，第 $i$ 个宝石的颜色是 $C_i$。这个游戏的目标是尽快的消灭一行中所有的宝石。

在一秒钟，$\texttt{Genos}$ 能很快的挑选出这些有颜色的宝石中的一个回文的、连续的子串，并将这个子串移除。每当一个子串被删除后，剩余的宝石将连接在一起，形成一个新的行列。

你的任务是：求出把整个宝石串都移除的最短时间。

## 输入格式

第一行包含一个整数 $n(1 \le n \le 500)$，表示宝石串的长度。第二行包含 $n$ 个被空格分开的整数，第 $i(1 \le i \le n)$ 个表示这行中第 $i$ 个珠子的颜色。

## 输出格式

输出一个整数，把这行珠子移除的最短时间。

## 说明/提示

在第一个例子中，$\texttt{Genos}$ 可以在一秒钟就把这行珠子全部移走。在第二个例子中，$\texttt{Genos}$ 一次只能移走一个珠子，所以移走三个珠子花费他三秒。在第三个例子中，为了达到 $2$ 秒的最快时间，先移除回文串 $\texttt{4 4}$,再移除回文串 $\texttt{1 2 3 2 1}$。

感谢 @Administrator2004 提供的翻译

## 样例 #1

### 输入

```
3
1 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
7
1 4 4 2 3 2 1

```

### 输出

```
2

```



---

