---
title: "Strong Password"
layout: "post"
diff: 普及-
pid: CF1997A
tag: ['贪心', '分类讨论']
---

# Strong Password

## 题目描述

有一个由小写字母组成的字符串 $s$，你可以在其任意位置插入一个小写字母（包括最前面和最后面），请最大化其权值。你只需要输出任意权值最大的新字符串。

其中，字符串的权值定义如下计算：

- 若某个字符前面没有字符，或前面的字符与其不同，则其为字符串贡献 $2$ 点权值。

- 若某个字符前面的字符与其相同，则其为字符串贡献 $1$ 点权值。

## 输入格式

第一行输入一个整数 $t(1\le t\le 1000)$，表示测试组数。

接下来 $t$ 行，每行一个字符串 $s(1\le\lvert s\rvert\le 10)$，表示待处理的字符串。

## 输出格式

输出共 $t$ 行，每行一个字符串，第 $i$ 行输出第 $i$ 组测试数据的答案。

## 样例 #1

### 输入

```
4
a
aaa
abb
password
```

### 输出

```
wa
aada
abcb
pastsword
```



---

---
title: "Game with Doors"
layout: "post"
diff: 普及-
pid: CF2004B
tag: ['贪心', '分类讨论']
---

# Game with Doors

## 题目描述

### 题面描述
有 $100$ 个房间排成一列，之间有 $99$ 个门; 第 $i$ 个门连接第 $i$ 个房间和第 $i+1$ 个房间。每扇门可以上锁也可以不上锁。最初，所有的门都没有锁。

我们说，房间 $x$ 是可以到房间 $y$ 的，如果 $x$ 与 $y$ 之间的所有门都没锁。

你知道的:

- 爱丽丝在 $[l,r]$ 的某个房间里;
- Bob 在 $[L,R]$ 的某个房间里;
- 爱丽丝和鲍勃在不同的房间。

然而，你并不知道他们所在的确切房间。

你不希望爱丽丝和鲍勃能够联系到对方，所以你要锁上一些门来防止这种情况发生。无论 Alice 和 Bob 在给定段中的起始位置如何，您需要锁定的门的最小数量是多少？

## 输入格式

第一行包含单个整数 $t$ ( $1 \le t \le 10^4$ )ー测试用例的数量。

每个测试用例的第一行包含两个整数 $ l $ 和 $ r $ ( $ 1 \le l < r \le 100 $ ) ーー Alice 所在房间段。

每个测试用例的第二行包含两个整数 $ L $ 和 $ R $ ( $ 1 \le L < R \le 100 $ ) ーー Bob 所在房间段。

## 输出格式

对于每个测试用例，打印一个整数ーー必须锁定的门的最小数目，以便 Alice 和 Bob 不能相遇，而不管它们在给定段中的起始位置如何。

## 样例 #1

### 输入

```
4
1 2
3 4
2 5
2 5
3 7
6 7
4 5
2 8
```

### 输出

```
1
3
2
3
```



---

---
title: "The Strict Teacher (Easy Version)"
layout: "post"
diff: 普及-
pid: CF2005B1
tag: ['数学', '分类讨论']
---

# The Strict Teacher (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions are the constraints on $ m $ and $ q $ . In this version, $ m=2 $ and $ q=1 $ . You can make hacks only if both versions of the problem are solved.

Narek and Tsovak were busy preparing this round, so they have not managed to do their homework and decided to steal David's homework. Their strict teacher noticed that David has no homework and now wants to punish him. She hires other teachers to help her catch David. And now $ m $ teachers together are chasing him. Luckily, the classroom is big, so David has many places to hide.

The classroom can be represented as a one-dimensional line with cells from $ 1 $ to $ n $ , inclusive.

At the start, all $ m $ teachers and David are in distinct cells. Then they make moves. During each move

- David goes to an adjacent cell or stays at the current one.
- Then, each of the $ m $ teachers simultaneously goes to an adjacent cell or stays at the current one.

This continues until David is caught. David is caught if any of the teachers (possibly more than one) is located in the same cell as David. Everyone sees others' moves, so they all act optimally.

Your task is to find how many moves it will take for the teachers to catch David if they all act optimally.

Acting optimally means the student makes his moves in a way that maximizes the number of moves the teachers need to catch him; and the teachers coordinate with each other to make their moves in a way that minimizes the number of moves they need to catch the student.

Also, as Narek and Tsovak think this task is easy, they decided to give you $ q $ queries on David's position. Note: this is the easy version, and you are given only one query.

## 输入格式

In the first line of the input, you are given a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. The description of each test case follows.

In the first line of each test case, you are given three integers $ n $ , $ m $ , and $ q $ ( $ 3 \le n \le 10^9 $ , $ m=2 $ , $ q=1 $ ) — the number of cells on the line, the number of teachers, and the number of queries.

In the second line of each test case, you are given $ m $ distinct integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le n $ ) — the cell numbers of the teachers.

In the third line of each test case, you are given $ q $ integers $ a_1, a_2, \ldots, a_q $ ( $ 1 \le a_i \le n $ ) — David's cell number for every query.

It is guaranteed that for any $ i $ , $ j $ such that $ 1 \le i \le m $ and $ 1 \le j \le q $ , $ b_i \neq a_j $ .

## 输出格式

For each test case, output $ q $ lines, the $ i $ -th of them containing the answer of the $ i $ -th query.

## 说明/提示

In the first example, the student can just stay at cell $ 2 $ . The teacher, initially located in cell $ 1 $ , can reach cell $ 2 $ in one move. Therefore, the answer is $ 1 $ .

In the second example, the student should just stay at cell $ 1 $ . The teacher, initially located in cell $ 3 $ , can reach cell $ 1 $ in two moves. Therefore, the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8
```

### 输出

```
1
2
2
```



---

---
title: "Preparing for the Exam"
layout: "post"
diff: 普及-
pid: CF2051C
tag: ['分类讨论']
---

# Preparing for the Exam

## 题目描述

Monocarp 正在为他的第一场大学考试做准备。这场考试可能会涉及到 $n$ 个不同的问题，编号从 $1$ 到 $n$。一共有 $m$ 个不同的问题列表，每个列表包含正好 $n-1$ 个不同的问题。对于每个列表 $i$，用一个整数 $a_i$ 指定唯一没有出现在第 $i$ 个列表中的问题。例如，当 $n = 4$ 且 $a_i = 3$ 时，第 $i$ 个列表里有问题 $[1, 2, 4]$。

在考试的时候，Monocarp 将会拿到其中的一个问题列表，然后老师会要求他回答列表中所有的问题。要通过考试，Monocarp 必须回答列表中所有问题。

Monocarp 已经掌握了 $k$ 个问题的答案，这些问题编号是 $q_1, q_2, \dots, q_k$。请判断对于每一个问题列表，Monocarp 是否能够通过考试。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量（$1 \le t \le 10^4$）。

每个测试用例包含以下三行：

- 第一行给出三个整数 $n$、$m$ 和 $k$（$2 \le n \le 3 \times 10^5$；$1 \le m, k \le n$）；
- 第二行包含 $m$ 个不同的整数 $a_1, a_2, \dots, a_m$（$1 \le a_i \le n$；$a_i < a_{i+1}$）；
- 第三行包含 $k$ 个不同的整数 $q_1, q_2, \dots, q_k$（$1 \le q_i \le n$；$q_i < q_{i+1}$）。

注意：所有测试用例中 $n$ 的总和不超过 $3 \times 10^5$。

## 输出格式

对于每个测试用例，输出一个长度为 $m$ 的由 '1' 和 '0' 组成的字符串。如果 Monocarp 能通过这个问题列表，则对应位置输出 '1'，否则输出 '0'。

## 说明/提示

在第一个测试用例中，Monocarp 已掌握的问题是 $[1, 3, 4]$。我们来看所有的问题列表：

- 第一个列表的问题是 $[2, 3, 4]$。Monocarp 不懂第 $2$ 个问题，所以不能通过；
- 第二个列表的问题是 $[1, 3, 4]$。Monocarp 知道这些问题，因此能通过；
- 第三个列表的问题是 $[1, 2, 4]$。Monocarp 不懂第 $2$ 个问题，所以不能通过；
- 第四个列表的问题是 $[1, 2, 3]$。Monocarp 不懂第 $2$ 个问题，所以不能通过。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
4 4 3
1 2 3 4
1 3 4
5 4 3
1 2 3 4
1 3 4
4 4 4
1 2 3 4
1 2 3 4
2 2 1
1 2
2
```

### 输出

```
0100
0000
1111
10
```



---

---
title: "MIN = GCD"
layout: "post"
diff: 普及-
pid: CF2084B
tag: ['数学', '分类讨论']
---

# MIN = GCD

## 题目描述

给定一个长度为 $n$ 的正整数序列 $a$。判断是否可以重新排列 $a$，使得存在一个整数 $i$（$1 \le i < n$）满足：
$$
\min([a_1, a_2, \ldots, a_i]) = \gcd([a_{i+1}, a_{i+2}, \ldots, a_n]).
$$
其中，$\gcd(c)$ 表示 $c$ 的[最大公约数](https://en.wikipedia.org/wiki/Greatest_common_divisor)，即能整除 $c$ 中所有整数的最大正整数。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 10^5$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^{18}$）。  

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，如果可能，输出 "Yes"；否则输出 "No"。  

答案可以以任意大小写形式输出（如 "yEs"、"yes"、"Yes" 或 "YES" 均被视为肯定回答）。


## 说明/提示

- 在第一个测试用例中，将 $a$ 重新排列为 $[1, 1]$ 并令 $i=1$，则 $\min([1]) = \gcd([1])$。  
- 在第二个测试用例中，可以证明不可能满足条件。  
- 在第三个测试用例中，将 $a$ 重新排列为 $[3, 2, 2]$ 并令 $i=2$，则 $\min([3, 2]) = \gcd([2])$。  
- 在第五个测试用例中，将 $a$ 重新排列为 $[3, 4, 5, 6, 9]$ 并令 $i=3$，则 $\min([3, 4, 5]) = \gcd([6, 9])$。  

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
2
1 1
2
1 2
3
2 2 3
3
2 3 4
5
4 5 6 9 3
3
998244359987710471 99824435698771045 1000000007
6
1 1 4 5 1 4
```

### 输出

```
Yes
No
Yes
No
Yes
Yes
Yes
```



---

---
title: "Serval and String Theory"
layout: "post"
diff: 普及-
pid: CF2085A
tag: ['字符串', '分类讨论']
---

# Serval and String Theory

## 题目描述

仅由小写拉丁字母组成的字符串 $r$ 被称为**通用字符串**，当且仅当 $r$ 在字典序上小于$^{\text{∗}}$其反转$^{\text{†}}$后的字符串。

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。你需要通过最多 $k$ 次操作使 $s$ 成为通用字符串。每次操作可执行以下步骤：
- 选择两个下标 $i$ 和 $j$（$1 \le i, j \le n$），交换 $s_i$ 和 $s_j$。注意若 $i = j$，则不进行任何操作。

请判断是否能在最多 $k$ 次操作内使 $s$ 成为通用字符串。

$^{\text{∗}}$当两个长度相同的字符串 $a$ 和 $b$ 满足以下条件时，称 $a$ 的字典序小于 $b$：
- 在第一个不同的位置上，$a$ 的字符在字母表中出现的时间早于 $b$ 对应位置的字符。

$^{\text{†}}$字符串 $r$ 的反转是指将 $r$ 从右向左书写得到的新字符串。例如，字符串 $\texttt{abcad}$ 的反转为 $\texttt{dacba}$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 500$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 100$，$0 \le k \le 10^4$）——字符串 $s$ 的长度及允许的最大操作次数。

第二行输入一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

## 输出格式

对于每个测试用例，若能在最多 $k$ 次操作内使 $s$ 成为通用字符串，输出 "YES"，否则输出 "NO"。

答案可以任意大小写形式输出（例如 "yEs"、"yes"、"Yes" 和 "YES" 均视为肯定回答）。


## 说明/提示

第一个测试案例中，任何操作后 $s$ 均保持不变。但 $\texttt{a}$ 的反转仍为 $\texttt{a}$，因此无法使其成为通用字符串。

第二个测试案例中，字符串 $\texttt{rev}$ 的字典序小于其反转 $\texttt{ver}$，因此 $s$ 已经是通用字符串。

第五个测试案例中，可按以下步骤操作：
1. 交换 $s_4$ 和 $s_7$，此时 $s$ 变为 $\texttt{uniserval}$；
2. 交换 $s_1$ 和 $s_3$，此时 $s$ 变为 $\texttt{inuserval}$。

字符串 $\texttt{inuserval}$ 是通用字符串。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
1 10000
a
3 3
rev
6 0
string
6 0
theory
9 2
universal
19 0
codeforcesecrofedoc
19 1
codeforcesecrofedoc
3 1
zzz
```

### 输出

```
NO
YES
NO
YES
YES
NO
YES
NO
```



---

---
title: "Serval and Final MEX"
layout: "post"
diff: 普及-
pid: CF2085B
tag: ['贪心', '分类讨论']
---

# Serval and Final MEX

## 题目描述

给定一个由 $n \ge 4$ 个非负整数组成的数组 $a$。

你需要对 $a$ 执行以下操作，直到其长度变为 $1$：
- 选择两个下标 $l$ 和 $r$（$1 \le {\color{red}{ l < r }} \le |a|$），将子数组 $[a_l, a_{l+1}, \ldots, a_r]$ 替换为一个整数 $\operatorname{mex}([a_l, a_{l+1}, \ldots, a_r])$。其中 $\operatorname{mex}(b)$ 表示整数集合 $b$ 的最小未出现值（MEX）$^{\text{∗}}$。具体来说，令 $x = \operatorname{mex}([a_l, a_{l+1}, \ldots, a_r])$，数组 $a$ 将变为 $[a_1, a_2, \ldots, a_{l-1}, x, a_{r+1}, a_{r+2}, \ldots, a_{|a|}]$。注意此操作后 $a$ 的长度将减少 $(r - l)$。

Serval 希望最终 $a$ 中的唯一元素为 $0$。请帮助他完成这一目标！

更正式地说，你需要找到一个操作序列，使得按顺序执行这些操作后，数组 $a$ 的长度变为 $1$，且该元素为 $0$。

可以证明，在题目约束下至少存在一个有效的操作序列，且任何有效操作序列的长度不超过 $n$。

注意：你**不需要**最小化操作次数。

$^{\text{∗}}$整数集合 $b_1, b_2, \ldots, b_k$ 的最小未出现值（MEX）定义为**不包含**在该集合中的最小非负整数 $x$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 1000$）。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$（$4 \le n \le 5000$）——数组 $a$ 的长度。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le n$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $5000$。


## 输出格式

对于每个测试用例：
- 第一行输出一个整数 $k$（$0 \le k \le n$）——操作序列的长度。
- 随后输出 $k$ 行，第 $i$ 行包含两个整数 $l_i$ 和 $r_i$（$1 \le l_i < r_i \le |a|$）——第 $i$ 次操作中选择的下标，其中 $|a|$ 表示操作前数组的长度。

若存在多个答案，输出任意一种即可。

## 说明/提示

第一个测试案例中，由于 $\operatorname{mex}([1,2,3,4]) = 0$，经过一次操作后数组变为 $[0]$。

第二个测试案例中，数组 $a$ 的变化如下：
$$[
\underline{0,1},0,0,1] \to [
\underline{2,0},0,1] \to [
\underline{1,0},1] \to [
\underline{2,1}] \to [
0].
$$

第三个测试案例中，数组 $a$ 的变化如下：
$$[
0,0,0,0,\underline{0,0}] \to [
0,0,\underline{0,0},1] \to [
\underline{0,0},1,1] \to [
\underline{1,1,1}] \to [
0].
$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
4
1 2 3 4
5
0 1 0 0 1
6
0 0 0 0 0 0
6
5 4 3 2 1 0
4
0 0 1 1
4
1 0 0 0
```

### 输出

```
1
1 4
4
1 2
1 2
1 2
1 2
4
5 6
3 4
1 2
1 3
3
4 5
4 5
1 4
2
1 2
1 3
2
2 4
1 2
```



---

---
title: "Binary Typewriter"
layout: "post"
diff: 普及-
pid: CF2103B
tag: ['数学', '分类讨论']
---

# Binary Typewriter

## 题目描述

给定一个长度为 $n$ 的二进制字符串 $s$ 和一个带有两个按钮（0 和 1）的打字机。初始时，你的手指放在按钮 0 上。你可以执行以下两种操作：

1. 按下当前手指所在的按钮。这将打出该按钮上的字符。
2. 将手指移动到另一个按钮。如果手指在按钮 0 上，则移动到按钮 1，反之亦然。

二进制字符串的代价定义为输入整个字符串所需的最少操作次数。

在输入之前，你可以选择最多反转 $s$ 的一个子串 $^{\text{∗}}$。更正式地说，你可以选择两个下标 $1 \le l \le r \le n$，并将子串 $s_{l \ldots r}$ 反转，得到新字符串 $s_1s_2 \ldots s_{l-1}s_rs_{r-1} \ldots s_ls_{r+1} \ldots s_n$。

你的任务是找出在最多进行一次子串反转后，所有可能得到的字符串中的最小可能代价。

$^{\text{∗}}$ 字符串 $a$ 是字符串 $b$ 的子串，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）字符得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——二进制字符串 $s$ 的长度。

每个测试用例的第二行包含一个二进制字符串 $s_1s_2 \ldots s_n$（$s_i = \mathtt{0}$ 或 $s_i = \mathtt{1}$）——二进制字符串 $s$ 的字符。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出在最多进行一次子串反转后，字符串 $s$ 的最小代价。


## 说明/提示

在第一个测试用例中，我们可以选择不反转任何子串。我们可以执行操作 1 三次来输入 000。

在第二个测试用例中，我们可以选择不反转任何子串。我们可以执行操作 2 将手指移动到按钮 1，然后执行操作 1 三次来输入 111。

在第三个测试用例中，我们可以选择不反转任何子串。我们可以执行操作 1 输入 0，然后执行操作 2 将手指移动到按钮 1，最后执行操作 1 两次输入 11，最终以 4 次操作得到字符串 011。

在第四个测试用例中，我们可以反转子串 $s_{1 \ldots 3}$，得到字符串 001。我们可以执行操作 1 两次输入 00，然后执行操作 2 将手指移动到按钮 1，最后执行操作 1 一次输入 1，最终以 4 次操作得到字符串 001。

在第五个测试用例中，我们可以反转子串 $s_{2 \ldots 3}$，得到字符串 11001。该字符串的代价为 8，操作序列如下：
- 执行操作 2 将手指移动到按钮 1。
- 执行操作 1 两次输入 11。
- 执行操作 2 将手指移动到按钮 0。
- 执行操作 1 两次输入 00。
- 执行操作 2 将手指移动到按钮 1。
- 执行操作 1 一次输入 1。

在第六个测试用例中，我们可以反转子串 $s_{5 \ldots 17}$，得到字符串 1101111011001001000。可以证明，输入该二进制字符串所需的最少操作次数为 29。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
3
000
3
111
3
011
3
100
5
10101
19
1101010010011011100
```

### 输出

```
3
4
4
4
8
29
```



---

---
title: "Card Game"
layout: "post"
diff: 普及-
pid: CF2104C
tag: ['贪心', '分类讨论']
---

# Card Game

## 题目描述

Alice 和 Bob 正在玩一个游戏。他们共有 $n$ 张编号从 $1$ 到 $n$ 的卡牌。游戏开始时，部分卡牌分配给 Alice，其余分配给 Bob。

编号为 $i$ 的卡牌能击败编号为 $j$ 的卡牌当且仅当 $i > j$，但有一个例外：编号 $1$ 的卡牌可以击败编号 $n$ 的卡牌。

游戏会持续进行，直到某一方没有卡牌为止。每一回合的操作如下：
1. Alice 从自己的卡牌中选择一张正面朝上放在桌上；
2. Bob 在看到 Alice 的卡牌后，从自己的卡牌中选择一张正面朝上放在桌上；
3. 如果 Alice 的卡牌击败 Bob 的卡牌，两张卡牌都由 Alice 收走；否则，两张卡牌都由 Bob 收走。

玩家可以使用之前回合中获得的卡牌。

在某一回合开始时没有卡牌的玩家输掉游戏。假设双方都采取最优策略，判断谁会获胜。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 5000$）——测试用例的数量。

每个测试用例包含两行：
- 第一行包含一个整数 $n$（$2 \le n \le 50$）——卡牌的数量；
- 第二行包含 $n$ 个字符，每个字符是 A 或 B。如果第 $i$ 个字符是 A，则编号 $i$ 的卡牌初始属于 Alice；否则属于 Bob。

输入数据的额外约束：每个测试用例中，Alice 和 Bob 初始至少各有一张卡牌。

## 输出格式

对于每个测试用例，如果 Alice 在最优策略下获胜，输出 Alice；否则输出 Bob。可以证明在双方都采取最优策略时，游戏一定会在有限回合内结束，且一方必定获胜。


## 说明/提示

在第一个测试用例中，Alice 和 Bob 各有一张卡牌。由于 Alice 的卡牌能击败 Bob 的卡牌，她在第一回合后获胜。

在第二个测试用例中，Alice 和 Bob 各有一张卡牌。由于 Bob 的卡牌能击败 Alice 的卡牌，他在第一回合后获胜。

在第三个测试用例中，有两种可能的游戏进程：
- 如果 Alice 在第一回合出卡 $1$，Bob 可以用卡 $2$ 应对并收走两张卡。然后 Alice 必须在第二回合出卡 $3$，Bob 会用卡 $4$ 应对，最终 Bob 获胜；
- 如果 Alice 在第一回合出卡 $3$，Bob 可以用卡 $4$ 应对并收走两张卡。然后 Alice 必须出卡 $1$，Bob 可以用卡 $2$ 或卡 $3$ 应对，最终 Bob 获胜。

在第四个测试用例中，有两种可能的游戏进程：
- 如果 Alice 在第一回合出卡 $2$，Bob 可以用卡 $3$ 应对并收走两张卡。然后 Alice 必须在第二回合出卡 $4$，Bob 会用卡 $1$ 应对，最终 Bob 获胜；
- 如果 Alice 在第一回合出卡 $4$，Bob 可以用卡 $1$ 应对并收走两张卡。然后 Alice 必须出卡 $2$，Bob 可以用卡 $3$ 或卡 $4$ 应对，最终 Bob 获胜。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2
AB
2
BA
4
ABAB
4
BABA
3
BAA
5
AAAAB
5
BAAAB
6
BBBAAA
```

### 输出

```
Alice
Bob
Bob
Bob
Alice
Alice
Bob
Alice
```



---

---
title: "Cherry Bomb"
layout: "post"
diff: 普及-
pid: CF2106C
tag: ['贪心', '分类讨论']
---

# Cherry Bomb

## 题目描述

我们称两个长度均为 $n$ 的整数数组 $a$ 和 $b$ 是**互补的**，当且仅当存在一个整数 $x$，使得对于所有 $1 \le i \le n$，$a_i+b_i=x$。例如数组 $a=[2,1,4]$ 和 $b=[3,4,1]$ 是互补的，因为对于所有 $1 \le i \le 3$，$a_i+b_i$ 都等于 $5$。而数组 $a=[1,3]$ 和 $b=[2,1]$ 则不是互补的。

Cow the Nerd 觉得任何人都对数学感兴趣，所以他给了 Cherry Bomb 两个长度均为 $n$ 的整数数组 $a$ 和 $b$，其中元素均为非负整数且不大于 $k$。

但是 Cherry Bomb 不小心弄丢了 $b$ 中的一些数，这些数以 $-1$ 表示。请求出满足以下要求的可能的 $b$ 数组的数量：
- 数组 $a$ 和数组 $b$ 互补。
- $b$ 中的元素均为非负整数且不大于 $k$。

## 输入格式

输入的第一行是测试数据的组数 $t$（$1 \le t \le {10}^4$），以下有 $t$ 组测试数据。

对于每组测试数据，第一行是两个正整数 $n,k$（$1 \le n \le 2\times {10}^5,\ 0 \le k \le {10}^9,\ 1 \le \sum n \le 2\times {10}^5$）。

第二行是 $n$ 个小于等于 $k$ 的非负整数，表示 $a$ 数组。

第三行是 $n$ 个整数，每个整数要么是小于等于 $k$ 的非负整数，要么是 $-1$，表示 $b$ 数组，其中 $-1$ 是未知的数。

## 输出格式

对于每组数据，输出一行一个非负整数，表示满足条件的 $b$ 数组的数量。

## 说明/提示

对于第一组数据，由 $a_3=2$ 且 $b_3=1$，可以求出 $x=3$，从而唯一满足条件的 $b$ 数组为 $[2,0,1]$。

对于第二组数据，$a_2+b_2=1$，$a_4+b_4=0$，所以不可能做到 $a$ 数组与 $b$ 数组互补。

对于第四组数据，以下是所有满足条件的 $b$ 数组：
- $[4,2,3,0,1]$
- $[5,3,4,1,2]$
- $[6,4,5,2,3]$
- $[7,5,6,3,4]$
- $[8,6,7,4,5]$
- $[9,7,8,5,6]$
- $[10,8,9,6,7]$

共有 $7$ 种可能，因此输出 $7$。

## 样例 #1

### 输入

```
7
3 10
1 3 2
-1 -1 1
5 1
0 1 0 0 1
-1 0 1 0 -1
5 1
0 1 0 0 1
-1 1 -1 1 -1
5 10
1 3 2 5 4
-1 -1 -1 -1 -1
5 4
1 3 2 1 3
1 -1 -1 1 -1
5 4
1 3 2 1 3
2 -1 -1 2 0
5 5
5 0 5 4 3
5 -1 -1 -1 -1
```

### 输出

```
1
0
0
7
0
1
0
```



---

