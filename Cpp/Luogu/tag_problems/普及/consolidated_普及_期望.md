---
title: "[HBCPC2024] Points on the Number Axis A"
layout: "post"
diff: 普及/提高-
pid: P10867
tag: ['数学', '2024', 'O2优化', '期望', 'XCPC', '湖北']
---
# [HBCPC2024] Points on the Number Axis A
## 题目描述

Alice is playing a single-player game on the number axis.

There are $n$ points on the number axis. Each time, the player selects two points. The two points will be removed, and their midpoint will be added. When there is only one point on the axis, the game ends. Formally, if the two chosen points is $x_i$ and $x_j$, then $\dfrac{x_i+x_j}{2}$ will be added after the operation.

In order to play this game happily, Alice will always select two points randomly.

Now Alice have a question: where is the expected position of the last point.

It can be proven that the answer can be expressed in the form $\dfrac{p}{q}$, you only need to output the value of $p\cdot q^{-1} \bmod 998\,244\,353$.
## 输入格式

The first line contains one integer $n$ ($1 \le n \le 10^6$).

The second line contains $n$ integers $x_i$ ($0 \le x_1 \le \dots \le x_n < 998\,244\,353$), denoting the position of the $i$-th point.

Note that two points may be in the same position.
## 输出格式

Output one integer, the answer modulo $998\,244\,353$.
## 样例

### 样例输入 #1
```
3
1 2 4
```
### 样例输出 #1
```
332748120

```


---

---
title: "[蓝桥杯 2024 省 Java B] 星际旅行"
layout: "post"
diff: 普及/提高-
pid: P11046
tag: ['2024', '广度优先搜索 BFS', '概率论', '期望', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 Java B] 星际旅行
## 题目背景

备注：原题（Java）时间限制 3.0s，空间限制 512 MB。
## 题目描述

小明国庆节准备去某星系进行星际旅行，这个星系里一共有 $n$ 个星球，其中布置了 $m$ 道双向传送门，第 $i$ 道传送门可以连接 $a_i$，$b_i$ 两颗星球（$a_i \neq b_i$ 且任意两颗星球之间最多只有一个传送门）。

他看中了一款 “旅游盲盒”，一共有 $Q$ 个盲盒，第 $i$ 个盲盒里的旅行方案规定了旅行的起始星球 $x_i$ 和最多可以使用传送门的次数 $y_i$。只要从起始星球出发，使用传送门不超过规定次数能到达的所有星球都可以去旅行。

小明关心在每个方案中有多少个星球可以旅行到。小明只能在这些盲盒里随机选一个购买，他想知道能旅行到的不同星球的数量的期望是多少。
## 输入格式

输入共 $m + Q + 1$ 行。

第一行为三个正整数 $n, m, Q$。

后面 $m$ 行，每行两个正整数 $a_i$，$b_i$。

后面 $Q$ 行，每行两个整数 $x_i$，$y_i$。
## 输出格式

输出共一行，一个浮点数（四舍五入保留两位小数）。
## 样例

### 样例输入 #1
```
3 2 3
1 2
2 3
2 1
2 0
1 1
```
### 样例输出 #1
```
2.00
```
## 提示

【样例解释】

- 第一个盲盒可以旅行到 $1, 2, 3$。
- 第二个盲盒可以旅行到 $2$。
- 第三个盲盒可以旅行到 $1, 2$。

所以期望是 $(3 + 1 + 2) / 3 = 2.00$。

【数据范围】

- 对于 $20 \%$ 的评测用例，保证 $n \leq 300$。
- 对于 $100 \%$ 的评测用例，保证 $n \leq 1000$，$m \leq \min \left\{\dfrac{n(n - 1)}{2}, 5n\right\}$，$Q \leq 50000$，$0 \leq y_i \leq n$，$1 \leq x_i \leq n$。


---

---
title: "[SWERC 2023] Throwing dice"
layout: "post"
diff: 普及/提高-
pid: P13800
tag: ['2023', '期望', 'ICPC']
---
# [SWERC 2023] Throwing dice
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a11e720cc14242ff598268192fbaaa26b9332c02.png)

:::

Alice and Bob are discussing penalty shoot-outs and their randomness: "We might as well be throwing dice to determine the winner!", Alice said. And so they started simulating penalty shoot-outs by each throwing dice, summing the points indicated on their dice, and comparing these sums. The player with the largest sum wins; in case both sums are equal, there is a tie.


But even in such situations, some player might have an edge over their opponent, depending on which dice they throw. Thus, just by looking at the dice they are about to throw, Alice and Bob want to determine who has the better edge.


Alice has $M$ fair dice, with $A_1, A_2, \dots, A_M$ sides. For all integers $k$ and $l$ such that $1 \leq k \leq M$ and $1 \leq l \leq A_k$, the $k^\text{th}$ die of Alice has a probability $1/A_k$ of showing its face numbered $l$. Then, Alice's score is the sum of the numbers displayed by her $M$ dice. Similarly, Bob has $N$ fair dice, with $B_1, B_2, \dots, B_N$ sides.


Given these dice, Alice has a probability $\mathbb{P}_A$ of having a strictly larger score than Bob, and Bob has a probability $\mathbb{P}_B$ of having a strictly larger score than Alice. Which probability is the largest one?

## 输入格式

The input consists of three lines, each one containing space-separated integers. The first line contains the numbers $M$ and $N$. The second line contains the numbers $A_1, A_2, \dots, A_M$. The third line contains the numbers $B_1, B_2, \dots, B_N$.

**Limits**
	
- $1 \leq M \leq 100~000$;
- $1 \leq N \leq 100~000$;
- $4 \leq A_k \leq 1~000~000~000$ for all $k \leq M$;
- $4 \leq B_k \leq 1~000~000~000$ for all $k \leq N$;

## 输出格式

The output should contain a single line, consisting of a single uppercase word: $\texttt{ALICE}$ if $\mathbb{P}_A > \mathbb{P}_B$, $\texttt{TIED}$ if $\mathbb{P}_A = \mathbb{P}_B$, and $\texttt{BOB}$ if $\mathbb{P}_A < \mathbb{P}_B$.
## 样例

### 样例输入 #1
```
8 1
4 4 4 4 4 4 4 4
6
```
### 样例输出 #1
```
ALICE
```
### 样例输入 #2
```
2 2
6 4
4 6
```
### 样例输出 #2
```
TIED
```
## 提示

**Sample Explanation 1**

Since Alice has 8 dice, her score is always 8 or more; Bob's score is always 6 or less. Hence, Alice has a probability $\mathbb{P}_A = 100\%$ of beating Bob, and he has a probability $\mathbb{P}_B = 0\%$ of beating her. Consequently, $\mathbb{P}_A > \mathbb{P}_B$.

**Sample Explanation 2**

Alice has a probability $\mathbb{P}_A = 125/288$ of beating Bob; he also has a probability $\mathbb{P}_B = 125/288$ of beating her.


---

---
title: "「TAOI-1」拼凑的断音"
layout: "post"
diff: 普及/提高-
pid: P9217
tag: ['Special Judge', 'O2优化', '排序', '期望']
---
# 「TAOI-1」拼凑的断音
## 题目背景

> flick tap flick tap 面を滑って \
> swipe tap swipe tap 「A.R→T」\
> flick tap flick tap 開いて叩いて \
> swipe swipe swipe swipe …もう嫌だな \
> ズルズル 糸が呟く
## 题目描述

你的面前有 $n$ 个音符，它们的动听程度由数列 $\{a_n\}$ 描述。

现在有 $n$ 种魔法，第 $i$ 种魔法会让 $a_i$ 增加 $s(s \gt 0)$。每种魔法的成功几率都为 $\dfrac{p}{q}$，并且彼此独立。

求在施加魔法情况下，最终最动听的音符的动听程度（即，$\max\limits_{i=1}^n a_i$）的期望。

**本题目有 Special Judge，你可以用两种不同的方式输出答案，具体见【输出格式】处**。
## 输入格式

第一行为四个整数 $n, p, q, s$。

第二行为 $n$ 个整数 $a_i$，由空格隔开。
## 输出格式

**本题有两种不同的输出格式**。

- 第一种输出格式：

  请在第一行输出 `1`。
  
  接着，在第二行输出所求的期望，它应当是一个实数。
  
  如果您的答案与标准答案相差不超过 $10^{-4}$，则判定为正确。但由于众所周知的浮点数的误差，不保证评测结果百分百准确。如果您确信自己的程序正确但无法 AC，可以尝试使用第二种输出方式。

- 第二种输出格式：
  
  请在第一行输出 `2`。
  
  接下来，若你求出的期望是 $\dfrac{m}{n}$（显然期望为一个有理数），则请在第二行输出它对 $998244353$ 取模的结果，即一个 $[0, 998244353)$ 的整数 $x$，使得 $xn \equiv m \pmod {998244353}$。
## 样例

### 样例输入 #1
```
3 1 3 2
1 2 3
```
### 样例输出 #1
```
1
3.888889
```
### 样例输入 #2
```
3 1 3 2
1 2 3
```
### 样例输出 #2
```
2
554580200
```
## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（20 points）：$n \leq 15$。
- Subtask 2（15 points）：保证 $\forall i \in [1, n), a_i \leq a_{i+1}$，$a_n \geq a_{n-1}+s$。
- Subtask 3（15 points）：保证 $\forall i,j\in[1,n], a_i = a_j$。
- Subtask 4（50 points）：无特殊限制。

对于所有测试数据，$1 \leq n \leq 10^5$，$1 \leq p \lt q \leq 10^7$，$1 \leq a_i,s \leq 10^7$。

### 样例解释

注意到两个样例的输入相同，区别仅在于输出格式不同。

以下列举了所有可能的魔法施加情况和其对应的最大值以及出现概率：

| 魔法情况 | 动听度最大值 | 出现概率 | 对期望的贡献 |
| :------: | :----------: | :------: | :----------: |
|${\color{black}1},{\color{black}2},{\color{black}3}$|$3$|$\dfrac{8}{27}$|$\dfrac{8}{9}$|
|${\color{red}3},{\color{black}2},{\color{black}3}$|$3$|$\dfrac{4}{27}$|$\dfrac{4}{9}$|
|${\color{black}1},{\color{red}4},{\color{black}3}$|$4$|$\dfrac{4}{27}$|$\dfrac{16}{27}$|
|${\color{black}1},{\color{black}2},{\color{red}5}$|$5$|$\dfrac{4}{27}$|$\dfrac{20}{27}$|
|${\color{red}3},{\color{red}4},{\color{black}3}$|$4$|$\dfrac{2}{27}$|$\dfrac{8}{27}$|
|${\color{red}3},{\color{black}2},{\color{red}5}$|$5$|$\dfrac{2}{27}$|$\dfrac{10}{27}$|
|${\color{black}1},{\color{red}4},{\color{red}5}$|$5$|$\dfrac{2}{27}$|$\dfrac{10}{27}$|
|${\color{red}3},{\color{red}4},{\color{red}5}$|$5$|$\dfrac{1}{27}$|$\dfrac{5}{27}$|

可得，最终的答案为 $\dfrac{35}{9}$。

+ 若使用第一种输出方式，它的值约为 $3.888889$。
+ 若使用第二种输出方式，可以发现 $554580200 \times 9 \equiv 35 \pmod {998244353}$。


---

