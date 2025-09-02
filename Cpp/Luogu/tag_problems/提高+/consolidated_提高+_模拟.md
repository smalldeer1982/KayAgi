---
title: "[USACO24FEB] Test Tubes S"
layout: "post"
diff: 提高+/省选-
pid: P10191
tag: ['模拟', '贪心', 'USACO', '2024', 'Special Judge', 'O2优化']
---
# [USACO24FEB] Test Tubes S
## 题目描述

Bessie 最近开始对化学感兴趣。目前，她有两种不同颜色 $1$ 和 $2$ 的液体，彼此之间无法混合。她有两个无限容量的试管，各装有 $N$（$1\le N\le 10^5$）单位的这两种颜色的液体混合物。由于液体无法混合，一旦沉淀，它们就会分成不同颜色的层。因此，两个试管可以被视为两个字符串 $f_1f_2\ldots f_N$ 和 $s_1s_2\ldots s_N$，其中 $f_i$ 表示距离第一个试管底部 $i$ 单位处的液体的颜色，$s_i$ 表示距离第二个试管底部 $i$ 单位处的液体的颜色。输入保证两种颜色的液体至少各有一个单位。

Bessie 想要分离这些液体，以使得每个试管包含一种颜色的液体的所有单位。她有第三个无限容量的空烧杯来帮助她完成这一任务。当 Bessie 进行一次「倾倒」时，她将一个试管或烧杯顶部的所有颜色为 $i$ 的液体移至另一个的顶部。

求出将所有液体分离到两个试管中所需的最小的倾倒次数，以及所需的移动操作。两个试管最终包含的液体颜色不影响正确性，但烧杯必须是空的。

有 $T$（$1\le T\le 10$）个测试用例，每个测试用例有一个参数 $P$。

设将液体分离至试管中的最小倾倒次数为 $M$。

- 若 $P=1$，当你仅输出 $M$ 时可以得到分数。
- 若 $P=2$，当你输出 $A$，其中 $M\le A\le M+5$，并在以下 $A$ 行输出以该操作次数构造的一个方案时，可以得到分数。每一行包含来源试管和目标试管（$1$，$2$，或用 $3$ 表示烧杯）。操作之前，来源试管必须是非空的，并且不得将一个试管向其自身倾倒。
- 若 $P=3$，当你输出 $M$，并输出以该操作次数构造的一个方案时，可以得到分数。
## 输入格式

输入的第一行包含 $T$，为测试用例的数量。对于每一个测试用例，第一行包含 $N$ 和 $P$，为每个试管最初装有液体的数量以及询问类型。下一行包含 $f_1f_2f_3\ldots f_N$，表示第一个试管。$f_i\in \{1,2\}$，$f_1$ 表示试管的底部。下一行包含 $s_1s_2s_3\ldots s_N$，表示第二个试管。$s_i\in \{1,2\}$，$s_1$ 表示试管的底部。

输入保证两个字符串均包含至少一个 $1$ 和一个 $2$。
## 输出格式

对于每一个测试用例，输出一个整数，表示分离试管中液体的最少倾倒次数。根据询问类型，你可能还需要提供合法的构造方案。
## 样例

### 样例输入 #1
```
6
4 1
1221
2211
4 2
1221
2211
4 3
1221
2211
6 3
222222
111112
4 3
1121
1222
4 2
1121
1222
```
### 样例输出 #1
```
4
4
1 2
1 3
2 1
3 2
4
1 2
1 3
2 1
3 2
1
2 1
5
2 3
1 2
1 3
1 2
3 1
6
2 3
1 2
1 3
1 2
2 1
3 2
```
## 提示

### 样例解释

在前三个测试用例中，分离试管的最小倾倒次数为 $4$。我们可以看到以下操作是如何分离试管的：

初始状态：

```plain
1: 1221
2: 2211
3: 
```

在操作 `1 2` 后：

```plain
1: 122
2: 22111
3: 
```

在操作 `1 3` 后：

```plain
1: 1
2: 22111
3: 22
```

在操作 `2 1` 后：

```plain
1: 1111
2: 22
3: 22
```

在操作 `3 2` 后：

```plain
1: 1111
2: 2222
3:
```

在最后一个测试用例中，最小倾倒次数为 $5$。然而，由于 $P=2$，给出的 $6$ 次操作的构造也是合法的，因为它与最优解的差在 $5$ 次倾倒之内。

### 测试点性质

- 测试点 $2-6$：$P=1$。
- 测试点 $7-11$：$P=2$。
- 测试点 $12-21$：没有额外限制。

除此之外，输入保证除样例外的所有测试点均有 $T=10$。


---

---
title: "[NOIP 2003 提高组] 侦探推理"
layout: "post"
diff: 提高+/省选-
pid: P1039
tag: ['模拟', '字符串', '2003', '二分', 'NOIP 提高组', '枚举']
---
# [NOIP 2003 提高组] 侦探推理
## 题目描述

明明同学最近迷上了侦探漫画《柯南》并沉醉于推理游戏之中，于是他召集了一群同学玩推理游戏。游戏的内容是这样的，明明的同学们先商量好由其中的一个人充当罪犯（在明明不知情的情况下），明明的任务就是找出这个罪犯。接着，明明逐个询问每一个同学，被询问者可能会说：

$$
\def\arraystretch{1.5}
\begin{array}{|l|l|}\hline
\textbf{\textsf{证词内容}} & \textbf{\textsf{证词含义}}\\\hline
\text{I am guilty.} & \text{我是罪犯。} \\\hline
\text{I am not guilty.} & \text{我不是罪犯。} \\\hline
\text{{\tt XXX} is guilty.} & \text{{\tt XXX} 是罪犯。其中 {\tt XXX} 表示某个同学的名字。} \\\hline
\text{{\tt XXX} is not guilty.} & \text{{\tt XXX} 不是罪犯。} \\\hline
\text{Today is {\tt XXX}.} &
\begin{aligned}
&\text{今天是 {\tt XXX}。其中 {\tt XXX} 表示某个星期的单词。}\\
&\text{星期只有可能是以下之一：}\\
&\texttt{Monday}, \texttt{Tuesday}, \texttt{Wednesday}, \texttt{Thursday}, \\
&\texttt{Friday}, \texttt{Saturday}, \texttt{Sunday}。
\end{aligned}
\\\hline
\end{array}$$

证词中出现的其他话，都不列入逻辑推理的内容。


明明所知道的是，他的同学中有 $N$ 个人始终说假话，其余的人始终说真。


现在，明明需要你帮助他从他同学的话中推断出谁是真正的凶手，请记住，凶手只有一个！


## 输入格式

输入由若干行组成。

第一行有三个整数，$M,N$ 和 $P$。$M$ 是参加游戏的明明的同学数，$N$ 是其中始终说谎的人数，$P$ 是证言的总数。  
  
接下来 $M$ 行，每行是明明的一个同学的名字（英文字母组成，没有空格，全部大写）。

往后有 $P$ 行，每行开始是某个同学的名宇，紧跟着一个冒号和一个空格，后面是一句证词，符合前表中所列格式。证词每行不会超过 $250$ 个字符。

输入中不会出现连续的两个空格，而且每行开头和结尾也没有空格。

## 输出格式

如果你的程序能确定谁是罪犯，则输出他的名字；如果程序判断出不止一个人可能是罪犯，则输出 `Cannot Determine`；如果程序判断出没有人可能成为罪犯，则输出 `Impossible`。


## 样例

### 样例输入 #1
```
3 1 5
MIKE
CHARLES
KATE
MIKE: I am guilty.
MIKE: Today is Sunday.
CHARLES: MIKE is guilty.
KATE: I am guilty.
KATE: How are you??

```
### 样例输出 #1
```
MIKE

```
## 提示

对于 $100\%$ 数据，满足 $1\le M\le 20$，$0\le N\le M$，$1\le P\le 100$。

**【题目来源】**

NOIP 2003 提高组第二题


---

---
title: "[NOIP 2005 普及组] 循环"
layout: "post"
diff: 提高+/省选-
pid: P1050
tag: ['模拟', '字符串', '高精度', '递推', '2005', 'NOIP 普及组']
---
# [NOIP 2005 普及组] 循环
## 题目描述

乐乐是一个聪明而又勤奋好学的孩子。他总喜欢探求事物的规律。一天，他突然对数的正整数次幂产生了兴趣。


众所周知，$2$ 的正整数次幂最后一位数总是不断的在重复 $2,4,8,6,2,4,8,6…$ 我们说 $2$ 的正整数次幂最后一位的循环长度是 $4$（实际上 $4$ 的倍数都可以说是循环长度，但我们只考虑最小的循环长度）。类似的，其余的数字的正整数次幂最后一位数也有类似的循环现象：

$$
\def\arraystretch{1.5}
\begin{array}{c|c|c}\hline
\textbf{数字}& \textbf{循环} & \textbf{循环长度} \cr\hline\hline
2 & 2,4,8,6 & 4\cr\hline
3 & 3,9,7,1 & 4\cr\hline
4 & 4,6 & 2\cr\hline
5 & 5 &  1\cr\hline
6 & 6 & 1\cr\hline
7 & 7,9,3,1 & 4\cr\hline
8 & 8,4,2,6 & 4\cr\hline
9 & 9,1 & 2\cr\hline
\end{array}
$$

这时乐乐的问题就出来了：是不是只有最后一位才有这样的循环呢？对于一个整数 $n$ 的正整数次幂来说，它的后 $k$ 位是否会发生循环？如果循环的话，循环长度是多少呢？

注意：

1. 如果 $n$ 的某个正整数次幂的位数不足 $k$，那么不足的高位看做是 $0$。
2. 如果循环长度是 $L$，那么说明对于任意的正整数 $a$，$n$ 的 $a$ 次幂和 $a+L$ 次幂的最后 $k$ 位都相同。

## 输入格式

共一行，包含两个整数 $n$ 和 $k$。$n$ 和 $k$ 之间用一个空格隔开，表示要求 $n$ 的正整数次幂的最后 $k$ 位的循环长度。
## 输出格式

一个整数，表示循环长度。如果循环不存在，输出 $-1$。
## 样例

### 样例输入 #1
```
32 2
```
### 样例输出 #1
```
4
```
## 提示

**【数据范围】**

对于 $30 \%$ 的数据，满足 $k \le 4$；  
对于$100 \%$ 的数据，满足 $1 \le n < {10}^{100}$，$1 \le k \le 100$。

**【题目来源】**

NOIP 2005 普及组第四题


---

---
title: "[NOIP 2005 提高组] 篝火晚会"
layout: "post"
diff: 提高+/省选-
pid: P1053
tag: ['模拟', '2005', 'NOIP 提高组']
---
# [NOIP 2005 提高组] 篝火晚会
## 题目描述

佳佳刚进高中，在军训的时候，由于佳佳吃苦耐劳，很快得到了教官的赏识，成为了“小教官”。在军训结束的那天晚上，佳佳被命令组织同学们进行篝火晚会。一共有 $n$ 个同学，编号从 $1$ 到 $n$。一开始，同学们按照 $1,2,\cdots ,n$ 的顺序坐成一圈，而实际上每个人都有两个最希望相邻的同学。如何下命令调整同学的次序，形成新的一个圈，使之符合同学们的意愿，成为摆在佳佳面前的一大难题。


佳佳可向同学们下达命令，每一个命令的形式如下：

$$(b_1, b_2,... b_{m-1}, b_m)$$

这里 $m$ 的值是由佳佳决定的，每次命令 $m$ 的值都可以不同。这个命令的作用是移动编号是 $b_1,b_2,\cdots, b_m$ 的这 $m$ 个同学的位置。要求 $b_1$ 换到 $b_2$ 的位置上，$b_2$ 换到 $b_3$ 的位置上，……，要求 $b_m$ 换到 $b_1$ 的位置上。执行每个命令都需要一些代价。我们假定如果一个命令要移动 $m$ 个人的位置，那么这个命令的代价就是 $m$。我们需要佳佳用最少的总代价实现同学们的意愿，你能帮助佳佳吗？

## 输入格式

第一行是一个整数 $n$，表示一共有 $n$ 个同学。

其后 $n$ 行每行包括 $2$ 个不同的正整数，以一个空格隔开，分别表示编号是 $1$ 的同学最希望相邻的两个同学的编号，编号是 $2$  的同学最希望相邻的两个同学的编号，……，编号是$n$的同学最希望相邻的两个同学的编号。

## 输出格式

一个整数，为最小的总代价。如果无论怎么调整都不能符合每个同学的愿望，则输出 $-1$。

## 样例

### 样例输入 #1
```
4
3 4
4 3
1 2
1 2

```
### 样例输出 #1
```
2
```
## 提示

- 对于 $30\%$ 的数据，满足 $n \le 1000$；
- 对于 $100\%$ 的数据，满足 $3\le n  \le  50000$。

**【题目来源】**

NOIP 2005 提高组第三题


---

---
title: "[NOIP 2005 提高组] 等价表达式"
layout: "post"
diff: 提高+/省选-
pid: P1054
tag: ['模拟', '字符串', '2005', 'NOIP 提高组']
---
# [NOIP 2005 提高组] 等价表达式
## 题目描述

明明进了中学之后，学到了代数表达式。有一天，他碰到一个很麻烦的选择题。这个题目的题干中首先给出了一个代数表达式，然后列出了若干选项，每个选项也是一个代数表达式，题目的要求是判断选项中哪些代数表达式是和题干中的表达式等价的。

这个题目手算很麻烦，因为明明对计算机编程很感兴趣，所以他想是不是可以用计算机来解决这个问题。假设你是明明，能完成这个任务吗？

这个选择题中的每个表达式都满足下面的性质：

1. 表达式只可能包含一个变量 $\tt a$。
2. 表达式中出现的数都是正整数，而且都小于 $10000$。
3. 表达式中可以包括四种运算 `+`（加），`-`（减），`*`（乘），`^`（乘幂），以及小括号 `()`。小括号的优先级最高，其次是 `^`，然后是 `*`，最后是 `+` 和 `-`。`+` 和 `-` 的优先级是相同的。相同优先级的运算（**包括 `^` 运算**）都是**从左到右**进行。
4. 幂指数只可能是 $1$ 到 $10$ 之间的正整数（包括 $1$ 和 $10$）。
5. 表达式内部，头部或者尾部都可能有一些多余的空格。

下面是一些合理的表达式的例子：

`((a^1) ^ 2)^3`，`a*a+a-a`，`((a+a))`，`9999+(a-a)*a`，`1 + (a -1)^3`，`1^10^9`

## 输入格式

第一行给出的是题干中的表达式。

第二行是一个整数 $n$，表示选项的个数。后面$n$行，每行包括一个选项中的表达式。这 $n$ 个选项的标号分别是 $A,B,C,D\cdots $


输入中的表达式的长度都不超过 $50$ 个字符，而且保证选项中总有表达式和题干中的表达式是等价的。

## 输出格式

一行，包括一系列选项的标号，表示哪些选项是和题干中的表达式等价的。选项的标号按照字母顺序排列，而且之间没有空格。


## 样例

### 样例输入 #1
```
( a + 1) ^2
3
(a-1)^2+4*a
a + 1+ a
a^2 + 2 * a * 1 + 1^2 + 10 -10 +a -a

```
### 样例输出 #1
```
AC
```
## 提示

- 对于 $30\%$ 的数据，表达式中只可能出现两种运算符 `+` 和 `-`；
- 对于其它的数据，四种运算符 `+-*^` 在表达式中都可能出现。  
- 对于 $100\%$ 的数据，表达式中都可能出现小括号 `()`，$2 \le n \le  26$。

**【题目来源】**

NOIP 2005 提高组第四题


---

---
title: "[EPXLQ2024 fall round] 好排列"
layout: "post"
diff: 提高+/省选-
pid: P11413
tag: ['模拟', '堆', '优先队列', '链表']
---
# [EPXLQ2024 fall round] 好排列
## 题目背景

温昭雪喜欢构造排列。
## 题目描述

她的目标是构造一个由 $n$ 个数组成的排列 $A_1,A_2,\dots,A_n$，初始时 $A$ 中的所有元素都是 $0$。

接下来，对于数 $i$（$1 \le i \le n$），她通过下面方式由 $1$ 到 $n$ 确定其位置：

- 如果 $i=1$，将其放到最左侧。

- 如果 $i=2$，将其放到最右侧。

- 如果都不是，定义 $f_0(x)$ 表示 $x$ 左侧（包含 $x$，下同）的连续的 $0$ 的个数，$g_0(x)$ 为 $x$ 右侧的连续的 $0$ 的个数。特别地，如果 $x \le 0$ 或 $x > n$，$f_0(x)=g_0(x)=n+1$。
- 定义 $f_1(x)$ 表示 $x$ 左侧的连续非 $0$ 位置的个数，$g_1(x)$ 表示 $x$ 右侧的连续非 $0$ 位置的个数。特别地，如果 $x \le 0$ 或 $x > n$，$f_0(x)=g_0(x)=0$。
- 如果存在位置 $j$，使得 $\min(f_0(j), g_0(j)) > 1$，则选择位置 $j$ 最大化 $\min(f_0(j), g_0(j))$。如果有多个位置的值相同，选择 $j$ 较小的。
- 如果不存在这样的位置，则选择位置 $j$ 使得 $f_0(j)=1$ 并最小化 $f_1(j-1) + g_1(j+1)$。如果有多个位置的值相同，选择 $j$ 较小的。

温昭雪的幸运数字是 $k$。为了避免输出过多，她只想知道数字 $k$ 处于排列的什么位置。
## 输入格式

**本题单个测试点内有多组测试数据。**

输入第一行 $T$，表示数据组数。

以下 $T$ 行，每行两个正整数 $n,k$。
## 输出格式

输出 $T$ 行，每行一个正整数 $x$，表示排列长度为 $n$ 时，$A_x=k$。
## 样例

### 样例输入 #1
```
2
3 1
6 4
```
### 样例输出 #1
```
1
4

```
## 提示

### 样例解释

第一组测试数据对应的排列为 $\{1,3,2\}$。

第二组测试数据对应的排列为 $\{1,5,3,4,6,2\}$。

### 数据规模与约定


| 测试点编号 | $n$ | $k$ | $T$ | $\sum n$ | 特殊性质 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| $1,2$ | $\le 10$ | $\le 10$ | $\le 10$ | $\le 100$ | |
| $3,4$ | $\le 100$ | $\le 100$ | $\le 10$ | $\le 1000$ | |
| $5$ | $\le 1000$ | $\le 10$ | $\le 10$ | $\le 10^4$ | |
| $6,7$ | $\le 1000$ | $\le 1000$ | $\le 100$ | $\le 10^5$ |
| $8,9$ | $\le 10^4$ | $\le 10$ | $\le 100$ | $\le 10^5$ |
| $10 \sim 13$ | $\le 10^4$ | $\le 10^4$ | $\le 100$ | $\le 10^6$  | $n,k$ 均为奇数 |
| $14 \sim 17$ | $\le 10^4$ | $\le 10^4$ | $\le 100$ | $\le 10^6$ | $n,k$ 均为偶数 |
| $18,19$ | $\le 10^5$ | $\le 10$ | $\le 10$ | $\le 10^5$ | |
| $20,21$ | $\le 10^5$ | $\le 10^5$ | $\le 100$ | $\le 10^6$ | |
| $22\sim 25$ | $\le 10^6$ | $\le 10^6$ | $\le 100$ | $\le 10^6$ | |

对于奇数编号的测试点，内存限制为 $\text{512 MB}$；对于偶数编号的测试点，内存限制为 $\text{64 MB}$。

对于所有数据，保证 $1 \le k \le n \le 10^6, \sum n \le 10^6$。


---

---
title: "「FAOI-R4」蒲公英的约定"
layout: "post"
diff: 提高+/省选-
pid: P11787
tag: ['模拟', '树形数据结构', '线性数据结构', '2025', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「FAOI-R4」蒲公英的约定
## 题目背景

**[背景部分或许更好的阅读体验](https://www.luogu.com.cn/article/bz5b7xlo)**

**提示：题目背景与题意并无显著关联。**

$$ 1 $$

“怎么又来了一个，还是个女生，不知道好不好看。”曹玉明还没盖上水杯，就有些迫不及待地对着自己的“小弟”戏谑道，丝毫不管台上还在说话的王老师，“还是从八班转过来的，必须好好教育一下。”

“大哥说的对，这帮实验班的不是什么好东西。”旁边的小个子男生附和着，“必须先挫掉她的锐气。”

说话间，一位穿着花白裙子的女生走了进来，一阵春风吹过还未关紧的窗户，把她的裙子掀的飘了起来，曹玉明的身边划过一丝清香，还未来得及去思索这气息的来源，只听得一声铁器撞在桌面的声音，他的腿上也感到一阵水流带来的寒意。

“你长眼睛了吗？”曹玉明扶起水杯，便大声喊着。那女生连忙弯下腰道歉。她衣兜一朵小小的蒲公英差点掉了出来，散发着一种若隐若现的馨香。他这才注意到那女生的容貌，乌黑的头发宛如瀑布一样自然地垂下来，白皙的脸上闪着明朗的春日晨曦，澄澈的眼眸犹如潭水......他还没来得及说“没事”，台上猛然传来一声王老师的河东狮吼“怎么第一天就迟到了”，那女生赶忙坐在空位上。

他还没回过神，眼神朝向那个残留着一点香气的方向，呆呆地望着。旁边一阵“咯咯”声传来，虽然细微却也惊醒了他，“笑什么笑，再给你上一课。”他抬起手，小个子男生的脸上随着一声清脆的响声多了个有些猩红的巴掌印，顿时不敢出声，曹玉明也听清楚了老师说的话，那个女生好像叫什么“张艳奇”。“好土的名字。”他嘟囔着，也没注意到小个子又要倾泻而出的笑意。

$$ 2 $$

“我服了，怎么又到这天杀的化学课了，又要看到王头那张老不死的臭脸了，还是实验课，我说白了小林你去给我说一下那个挨千刀的什么硫酸铜实验怎么做，要我被骂了第一个干的就是你！”小个子男生有些颤抖，“我也不知道啊，大哥。”他那小小的脸上又多了一个更加鲜红的巴掌印。

此时老师进来了，毕竟是对校规还有些残存的敬畏，即使是作为南城三中的一霸曹玉明也不再造次，王老师进到班里，在讲台上放了一份名单，“因为新同学的转入，大家以后分组实验的搭档可能改变，你们去看一下！”王老师把一张表格挂在黑板上，“今天金属活动性置换反应实验还是按照学号两两分组。”

曹玉明率先挤到了人群中，惊呼一声，学号表上自己前面竟然有个不认识的女生，好像叫什么“张嫣琪”，学号是“425”，而曹玉明是“426”。他在脑海里搜索了自己可怜的知识库，终于想起第二个字的读音，“原来是你啊！”他感叹于神奇的姓名机缘，也有些莫名其妙的兴奋。

实验桌前，看着试剂瓶中的蓝色溶液，还有面前的一小点铁粉，曹玉明抓耳挠腮，而张嫣琪已经熟练的用镊子夹起了铁块，放进了装了一点蓝色溶液的烧杯中。瞬时间铁粉变红，曹玉明的脸上也红了，张嫣琪拂了一下他的额头，“帅哥，别呆坐着了，实验做完了。”看着曹玉明不解的眼神，张嫣琪有一点惊讶，“硫酸铜中铜金属活动性没有铁强”，她没有一丝烦躁和嫌弃，“铁就把铜置换出来了。”

“置换”“活动性”这些词在曹玉明的脑海里宛如天书，他竟不知道怎么接上，脑海里只剩下张嫣琪的那句“帅哥”。张嫣琪见他的呆滞而有些无奈，决定先缓解一下气氛，“你不好奇我是怎么来到这里的吗？”挣扎在化学知识漩涡中的曹玉明赶忙问道，“好奇”，曹玉明急忙喊出来，掩饰自己的尴尬。他听到这世界上除了好好学习走高考和像他一样混社会，居然还可以学艺术、练体育，也能考上好大学，而在他面前的就是一位，舞蹈生，她已经拿到了一所本地高中艺术班的签约，并不想在实验班的频繁刷题中浪费时间了，就准备来到轻松一点的环境。

他有些无地自容，原先还以为面前的人是因为犯了什么事才被“发配”来这四班的，而他在这里都是居于平均以下的位置。在长久地沉默中，她好像觉察出来了什么，在他头上敲了三下。他也心领神会，“那就中午吧”，他有些小声，似是为了盖掩自己的羞愧。

$$ 3 $$

“今天还去网……”姓林的小个子男生脸上又多了一抹淡淡的红色，悻悻走开了。而 90 分钟的时间对于曹玉明来说宛如一个世纪，他终于知道了什么是反应，什么是化合，什么是置换。他用了一个自己脑海边缘的一个词，“我还任重道远啊。”而张嫣琪把衣兜里的蒲公英拿了出来，双手递给他，“这是我和你的约定。”他拿出一张纸，是南城一中的宣传报，“我相信你！”

从那以后，曹玉明的身边，那位小个子男生出现的越来越少，每个 90 分钟的午休，网吧里少了一个高大帅气的身影，四班教室的空荡又多了一分。那根蒲公英静静地水培在曹玉明的书桌前，曹玉明看着蒲公英的生长，成绩单上的排名数字却不断的变小。

2010 年 6 月 21 日，学校放了三天的假，小林和其他的帮派成员依然无所事事，反正这只是一段枷锁的开解而已；曹玉明又一次看着自己二模区排的数字，213，而目光停留在一本《2010 年南城区中考中招说明》，书上南城一中的“统招”一行赫然写着“262 人”，他又撸起袖子，翻开一本数学模拟卷，飞转的笔在前 23 个数字号码上矫若游龙，“119 分钟”，他有些沮丧，“在函数题上卡了好久啊，不过至少差不多做完了”。

$$ 4 $$

6 月 25 日，下午 14 点 40，这次的题目有些难，他这时才开始做函数题，以往都能给函数题和压轴题留上一整个小时的。他有些急切，所以飞速地读完了题目要求，“怎么这是个分数啊，第一问就来这个？”他差点叫出声，笔有些颤抖，验算了好几遍，确认这个数又浪费了好久。第二问问得有些新颖，他有些胆怯不敢下笔，没想出什么妙法后只得开始繁琐的分类讨论，草稿纸上一整面近乎满了，丝毫没有注意到考试快要结束了的他还在算着，写上四个答案区间后，他小心翼翼地又看了一遍区间有没有重叠。

“考试即将结束，收卷时请注意答题卡朝上。”“什么”他惊叫出来，“请注意考试纪律，再违反将以考试违纪处理！”他不敢再说话，看着离考试结束只剩下 2 分钟，和空白一整页的压轴大题，他早已忘记当时干了什么。他只记得，交卷时自己压轴题上第一问涂涂改改，第二问根本空白；他只记得，同学们欢呼着“这次函数题真简洁”，而好像他们口中的题目与他做的都不太像同一道；他只记得，那一晚他的书桌上是湿的，“我要考上南城一中”的白色贴纸仍然孤傲的悬挂，却有如败局已定的军队即将失守的一座堡垒……

“你真是我们的奇迹！”班级的毕业聚会在 7 月举行，“你知道你由那个混混变成了什么吗？你已经高出南城二中录取线了，你考上了一所区重点！”曹玉明低着头，一阵夏日的微风拂过，蒲公英的毛絮掉了大半，他赶忙收起衣兜，但又掉了几根毛絮。

$$ 5 $$

搬迁自然是远学的结局，曹玉明亦不例外。一根手指的长度，他在地图上一次次地算着，“五十三公里，”一声哀嚎声传来，“那就是高速开车也得一个小时，比从这里到机场都远。”他丝毫没有听到父母对一个“不良少年”考上普高——还是重点中学——的嘉许和电话里和房东的讨价声。

搬迁来得很急，甚至没来得及送走太阳辐射在这个内地小城最后的疯狂。最后一次打开这座房子的窗户，无形的波浪向着曹玉明探出窗户的身体扑来，直到额头上沁下的汗珠落在一根软绵绵的白絮上，他赶忙把手心的那串珍宝向里拉回，所剩不多的白絮还是掉了几根。

三伏的热气让把蒲公英插回花瓶里时的手抖了抖，一滴水浸到了白色的单纸，他顺着“南城二中”四个字晕开的痕迹看了下去，越看却对这张灾难的告知书越来越入迷。

还没来得及擦干手，笔触已经落到书桌前的那张贴纸，“一”下面多了一横，“前 3 名”有些突兀地写了上去。他的嘴角从那个下午开始，第一次有了一点上扬。

$$ 6 $$

“信不信我处分你啊！”南城一中里，一位穿着西服领导模样的人物，叫骂着。“我给你这次跨校交流的机会，雇大巴车跨越几十公里不是为了让你作为优秀学生代表带头旷课的！”但是他跑出了曾经梦寐以求的校门。在那个校园安保并不完善的年代，他轻而易举地拦下一辆出租车，坐了上去。

“南城机场！”他气喘吁吁。30 分钟的车程说长也不长，他想了很多。他想起，如果学校能早一天来安排这次参观，如果那个为期六年的海外培养计划能晚一天开始，如果当年自己没有看错那个正负符号，如果自己多刷一套数学题……如果硫酸铜置换实验那天有个女生没来学校，如果那个水杯没有放在桌角，如果……

航站楼里，一个穿着南城二中校服的少年看着一架飞机，丝毫不注意领带已经快要脱落了。那飞机上的白色舱体，是否有一片是那天她裙子的颜色呢？少年手里一条快要光秃秃的的蒲公英被飞机启动的气流吹过，最后几根絮毛向前方飞去，少年不再能追上它们，他停下脚步，看着絮毛随着风飞得很远很远……
## 题目描述

随着 B 市中考招生方式的多元化，中考统招的名额数量日益减少，在本题目中，你需要根据平行志愿的招生原则（我们会给出详细的解释），高效模拟这一过程。

小 $ \zeta $ 为了更好的填报志愿，找到了某年的中考志愿填报和录取的情况。

具体地，$ n $ 位学生第 $ i $ 个人会填报 $ l_i $ 个志愿，即 $l_i$ 所学校。第 $ i $ 个人的第 $ j $ 志愿为学校 $ a_{i,j} $。总共有 $ m $ 所参与招生的学校，第 $ i $ 所提供了 $ t_i $ 个名额。

按照以下流程确认每个人的录取情况，记 $ b_i $ 为学校 $ i $ 已经招生人数：

* 找到**所有**目前未确定录取结果的**最高分学生**；
* 设**未招满**学校集合 $ S=\{i \mid i \in [1,m] \land t_i > b_i\} $；
* 对于每个当前的最高分学生 $x$，从第一志愿到最后志愿枚举学校 $i=a_{x,1},a_{x,2},\cdots,a_{x,l_x}$：
	* 如果 $i\in S$，则学生 $x$ 被学校 $i$ 录取，令 $b_i\gets b_i+1$，结束；否则，继续枚举下一个。
    * 若枚举所有 $i$ 后没有结束，则学生 $x$ 不被任何学校录取。
* 在上一步中 $ b_i $ 改变不会改变 $ S $，也就是说可能会出现一些学校 $b_i>t_i$。无论这些学生有没有被录取，他们的录取结果都确定了。
* 反复执行该过程直至所有学生录取结果都确定。

对于一次询问，格式如下：

* `x v`：永久性改变 $ t_x \leftarrow t_x-v $，输出录取结果变化的学生个数。
## 输入格式

第一行三个整数 $ n,m,q $，代表学生人数、学校个数和询问次数。

接下来一行，$ m $ 个整数，第 $ i $ 个整数 $ t_i $ 代表高中校 $ i $ 的招生名额数。

接下来 $ n $ 行，第 $ i $ 行第一个整数 $ l_i $ 代表学生 $ i $ 的志愿填报个数，接下来 $ l_i $ 个整数依次代表这位学生的第一至最后志愿高中校，最后一个整数 $ o_i $ 表示学生 $ i $ 的中考分数。

接下来 $ q $ 行，每行均为 `x v` 格式，代表一次询问，含义详见题目描述。
## 输出格式

$ q $ 行，每行一个整数代表录取结果改变的学生数量。
## 样例

### 样例输入 #1
```
5 3 5
1 2 5
3 1 2 3 3
3 1 2 3 2
3 3 2 1 5
2 3 2 4
1 3 4
3 1
3 2
3 1
3 1
2 2
```
### 样例输出 #1
```
0
0
2
2
3
```
## 提示

#### 【样例解释 \#1】

初始时，录取结果分别为（$ 0 $ 表示未被任何学校录取）$ \{1,2,3,3,3\} $。

前两次操作后，录取结果不变。

第三次操作后，录取结果分别为 $ \{1,2,3,2,0\} $。

第四次操作后，录取结果分别为 $ \{1,0,2,2,0\} $。

第五次操作后，录取结果分别为 $ \{0,0,1,0,0\} $。

#### 【数据规模与约定】

对于 $ 100\% $ 的数据：

* $ 1 \le n,m,q \le 3 \times 10^5 $；
* $ 0 \le t_i \le 10^6 $，$ 0 \le l_i \le m $，$ \sum l_i \le 10^6 $，$ 1 \le a_{i,j} \le m $，$ 0 \le o_i \le 10^6 $；
* 对于同一个 $ i $ **不保证** $ a_{i,j} $ 互不相同；
* 对于每次操作有 $ 1 \le x \le m $ 和 $ 0 \le v \le 10^6 $，操作后保证 $ t_i \ge 0 $。

**提示：本题开启捆绑测试。**

* Subtask 1（15 pts）：$ n,m,q \le 500 $，$ \sum l_i \le 5000 $。
* Subtask 2（20 pts）：$ o_i $ 只有两种取值。
* Subtask 3（35 pts）：所有的 $ o_i $ 互异。
* Subtask 4（30 pts）：无特殊限制。


---

---
title: "[eJOI 2024] 足球决斗 / CF Duels"
layout: "post"
diff: 提高+/省选-
pid: P12360
tag: ['模拟', '二分', '2024', 'eJOI（欧洲）']
---
# [eJOI 2024] 足球决斗 / CF Duels
## 题目描述

基希讷乌，摩尔多瓦的首都，有两支各由 $N$ 名球员组成的足球队，进行一系列的对决。为了增加趣味，他们按照以下一对一的方式安排比赛：

- 总共有 $N$ 场对决，每场在不同的体育场进行。
- 每场对决将有两队中的一名球员对决。
- 每个球员将只参加一场对决。
- 每个体育场将为各自的对决胜利者提供一定金额的奖金。
- 技能等级更高的球员赢得对决。保证总有技能等级更高的球员。

在所有比赛结束后，冠军队是获得奖金总额超过对方球队的队伍。如果获得的奖金相同，则没有冠军。

你是第一支球队的经理，你的任务是安排你的 $N$ 名球员参加 $N$ 场对决获得冠军。

作为第一支足球队的经理，你拥有以下信息：

- $N$ 个整数，表示你队伍中球员的技能等级
- $N$ 个整数，表示对方队伍中球员的技能等级

作为经理，你还派了一名侦查员访问每个体育场。侦查员按从 $1$ 到 $N$ 的顺序访问体育场，首先访问体育场 $1$，然后是体育场 $2$，最后访问体育场 $N$。侦查员访问完体育场 $i$ 后，他会向你报告对方球队在体育场 $i$ 的对决球员的技能等级。

可能在侦查员访问了一些体育场之后，你已经可以预见你的球队将成为冠军。换句话说，有可能在侦查员访问了一些体育场后，你可以确定你能成为冠军。**你可能仍然需要等待侦查员访问剩余的体育场，以便为你的球队建立分配方案。**

你的任务是找出侦查员需要访问的最少体育场数量，以确保你的球队能够夺冠，或者确定不可能成为冠军。
## 输入格式

第一行，一个正整数 $N$；

第二行 $N$ 个整数 $p_1,p_2,\dots,p_N$，表示体育馆的奖金数。

第三行 $N$ 个整数 $b_1,b_2,\dots,b_N$，其中 $b_i$ 表示对方球队在第 $i$ 个体育馆派出球员的足球水平。

第四行 $N$ 个整数 $a_1,a_2,\dots,a_N$，表示你的队员的足球水平。
## 输出格式

输出一个整数，表示你需要了解的体育场的最少数量，以确保你的球队能够成为冠军。

此外，如果你立即知道你的球队在任何情况下都会成为冠军，应该输出 $0$；即使在你了解所有 $N$ 个体育场的信息后，仍然无法找到获胜策略，那么输出 $-1$。
## 样例

### 样例输入 #1
```
5
1 5 4 3 1
5 9 3 12 8
1 10 4 2 6
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
6
6 1 21 22 23 24
1 12 6 8 10 11
2 3 4 5 7 9
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3
1 1 3
3 4 6
2 1 7
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
3
1 1 3
3 4 6
2 1 5
```
### 样例输出 #4
```
-1
```
## 提示

**【样例 #1 解释】**
对于第一个样例，在侦查员分享体育场 $1$ 和 $2$ 的信息后，你仍不能保证成为冠军。原因是，如果对手按以下方式安排球员：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $8$ | $12$ | $3$ |

你最好的选择是打成平局：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 你的球员技能等级 | $6$ | $10$ | $1$ | $2$ | $4$ |

你将赢得体育场 $1,2,5$ 的比赛，获得奖金总额 $1+5+1=7$，而对手将赢得体育场 $3,4$ 的比赛，获得奖金总额 $4+3=7$。

在侦查员分享体育场 $1,2,3$ 的信息后，你可以确定你将成为冠军。原因是，如果对手按以下方式安排球员：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $3$ | 未知 | 未知 |

对手的两种选择是：

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $3$ | $12$ | $8$ |
| 你的球员技能等级 | $6$ | $10$ | $4$ | $1$ | $2$ |

| 体育场 | $1$ | $2$ | $3$ | $4$ | $5$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 奖金 | $1$ | $5$ | $4$ | $3$ | $1$ |
| 对手球员技能等级 | $5$ | $9$ | $3$ | $8$ | $12$ |
| 你的球员技能等级 | $6$ | $10$ | $4$ | $1$ | $2$ |

我们可以注意到，在这两种情况下，我们的球队将在体育场 $1,2,3$ 获胜，获得奖金总额 $1+5+4=10$，而对手将获得奖金总额 $3+1=4$。由于 $10>4$，我们可以确定在这两种情况下我们都会获胜，因此最小答案是 $3$。

**【样例 2 解释】** 对于第二个样例，可以证明，在侦查员提供体育场 $1,2$ 的信息后，你将首次确定成为冠军。然而，与第一个样例不同，你不会有一个固定的获胜分配。相反，对于对手在体育场 $3, 4, 5, 6$ 中的不同安排，你需要有不同的应对策略来赢得冠军。

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$12$|$p_i=1,N\le10$|
|$2$|$16$|$p_i=1$|
|$3$|$14$|答案为 $0$ 或 $1$|
|$4$|$18$|答案为 $-1$ 或 $N-1$|
|$5$|$10$|$n\le5$|
|$6$|$30$|无|

对于 $100\%$ 的数据，$1 \le N \le 5 \times 10^4,1 \le a_i,b_i \le 10^6$，且所有 $a_i,b_i$ 两两不同。


---

---
title: "[NERC 2022] Amazing Trick"
layout: "post"
diff: 提高+/省选-
pid: P12790
tag: ['模拟', '图论', '2022', 'Special Judge', '置换', '随机化', '构造', 'ICPC', 'Ad-hoc', 'NERC/NEERC']
---
# [NERC 2022] Amazing Trick
## 题目描述

Alice is a magician and she creates a new trick. She has $n$ cards with different numbers from $1$ to $n$ written on them. First, she asks an audience member to shuffle the deck and put cards in a row. Let's say the $i$-th card from the left has the number $a_i$ on it. 

Then Alice picks two permutations $p$ and $q$. There is a restriction on $p$ and $q$ --- $\textbf{permutations can't have fixed points}$. Which means $\forall i: p_i \ne i\ and\ q_i \ne i$.

After permutations are chosen, Alice shuffles the cards according to them. Now the $i$-th card from the left is the card $a[p[q[i]]$. The trick is considered successful if $i$-th card from the left has the number $i$ on it after the shuffles.

Help Alice pick the permutations $p$ and $q$ or say it is not possible for the specific starting permutation $a$. 
## 输入格式

The first line of the input contains the number of tests $t$ ($1 \leq t \leq 10^5$). 

Each test is described in two lines. The first line contains one integer $n$ --- the number of cards ($1 \leq n \leq 10^5$). The second line contains $n$ integers $a_i$ --- the initial permutation of the cards ($1 \leq a_i \leq n$; $\forall i \neq j: a_i \neq a_j$). 

It is guaranteed that the sum of $n$ over all tests does not exceed $10^5$.
## 输出格式

Print the answer for each test case in the same order the cases appear in the input.

For each test case, print $\tt{Impossible}$ in a single line, if no solution exists.

Otherwise, print $\tt{Possible}$ in the first line, and in the following two lines print permutations $p$ and $q$.
## 样例

### 样例输入 #1
```
4
2
2 1
3
1 2 3
4
2 1 4 3
5
5 1 4 2 3
```
### 样例输出 #1
```
Impossible
Possible
3 1 2
2 3 1
Possible
3 4 2 1
3 4 2 1
Possible
4 1 2 5 3
3 1 4 5 2
```


---

---
title: "[GCJ 2020 #1A] Square Dance"
layout: "post"
diff: 提高+/省选-
pid: P13055
tag: ['模拟', '2020', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ 2020 #1A] Square Dance
## 题目描述

You are organizing an international dancing competition. You have already obtained all of the following:

* A dance floor with $\mathbf{R}$ rows and $\mathbf{C}$ columns, consisting of unit square cells;
* $\mathbf{R} \times \mathbf{C}$ competitors;
* A cutting-edge automated judge for the competition.

But you are still missing an audience! You are worried that the competition might not be interesting enough, so you have come up with a way to calculate the interest level for the competition.

Each competitor occupies one square unit cell of the floor and stays there until they are eliminated. A compass neighbor of a competitor $\mathrm{x}$ is another competitor $\mathrm{y}$ chosen such that $\mathrm{y}$ shares a row or column with $\mathrm{x}$, and there are no competitors still standing in cells in between $\mathrm{x}$ and $\mathrm{y}$. Each competitor may have between 0 and 4 compass neighbors, inclusive, and the number may decrease if all the other competitors in one orthogonal direction are eliminated.

The competition runs one round at a time. In between rounds $\mathrm{i}$ and $\mathrm{i}+1$, if a competitor $\mathrm{d}$ had at least one compass neighbor during round $\mathrm{i}$, and $\mathrm{d}$ 's skill level is strictly less than the average skill level of all of $\mathrm{d}$ 's compass neighbors, $\mathrm{d}$ is eliminated and is not part of the competition for rounds $\mathrm{i}+1, \mathrm{i}+2, \mathrm{i}+3$, etc. Notice that $\mathrm{d}$ still counts as a neighbor of their other compass neighbors for the purpose of other eliminations that may also happen between rounds $\mathrm{i}$ and $\mathrm{i}+1$. Competitors that do not have any compass neighbors are never eliminated. If after a round no competitor is eliminated, then the competition ends.

The interest level of a round is the sum of skill levels of the competitors dancing in that round (even any competitors that are to be eliminated between that round and the next). The interest level of the competition is the sum of the interest levels of all of the rounds.

Given the skill levels of the dancers that are on the floor for the first round, what is the interest level of the competition?
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow. Each test case begins with a line containing two integers $\mathbf{R}$ and $\mathbf{C}$. Then, there are $\mathbf{R}$ more lines containing $\mathbf{C}$ integers each. The $\mathrm{j}$-th value on the $\mathrm{i}$-th of these lines, $\mathrm{S}_{\mathrm{i}, \mathrm{j}}$, represents the skill level of the dancer in the cell in the $\mathrm{i}$-th row and $\mathrm{j}$-th column of the floor.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the interest level of the competition.
## 样例

### 样例输入 #1
```
4
1 1
15
3 3
1 1 1
1 2 1
1 1 1
1 3
3 1 2
1 3
1 2 3
```
### 样例输出 #1
```
Case #1: 15
Case #2: 16
Case #3: 14
Case #4: 14
```
## 提示

**Sample Explanation**

In Sample Case #1, only one competitor is on the floor. Since the competitor does not have any compass neighbors, they dance in one round, and then the competition is over. Thus the answer is equal to the dancer's skill level, 15.

In Sample Case #2, the interest level of the first round is $1+1+1+1+2+1+1+1+1=10$.

The competitors that are not in the center nor in a corner have a skill level of 1 , but the average of their compass neighbors is $4 / 3$, which is greater than 1 , so they are eliminated. The floor during the second round looks like this:

```
1 . 1
. 2 .
1 . 1
```

This round is the last one. The competitors in the corner have two compass neighbors each, but the average of their skill level is equal to their own. The competitor in the center has no compass neighbor. The interest level of the round is $1+1+2+1+1=6$. This means the interest level of the competition is $10+6=16$.

In Sample Case #3, the competitor with skill level 1 is eliminated after the first round, while the other two remain. In the second round, the two other competitors become compass neighbors, and this causes the competitor with skill level 2 to be eliminated. There is a single competitor in the third round, which makes it the last one. The interest levels of the rounds are 6, 5 and 3, making the interest level of the competition 14.

**Limits**

- $1 \leqslant S_{i, j} \leqslant 10^{6}$, for all $i$ and $j$.

**Test set 1 (9 Pts, Visible Verdict)**

- $1 \leqslant \mathrm{T} \leqslant 100$.
- $1 \leqslant \mathrm{R} \times \mathrm{C} \leqslant 100$.

**Test set 2 (28 Pts, Hidden Verdict)**

- $10 \leqslant \mathrm{T} \leqslant 100$.
- $1000<\mathrm{R} \times \mathrm{C} \leqslant 10^{5}$, in exactly 10 cases.
- $1 \leqslant \mathrm{R} \times \mathrm{C} \leqslant 1000$, in exactly $\mathrm{T}-10$ cases.


---

---
title: "[NOIP 2011 提高组] Mayan 游戏"
layout: "post"
diff: 提高+/省选-
pid: P1312
tag: ['模拟', '搜索', '2011', 'NOIP 提高组', '剪枝']
---
# [NOIP 2011 提高组] Mayan 游戏
## 题目描述

Mayan puzzle 是最近流行起来的一个游戏。游戏界面是一个$7$ 行 $\times5$ 列的棋盘，上面堆放着一些方块，方块不能悬空堆放，即方块必须放在最下面一行，或者放在其他方块之上。游戏通关是指在规定的步数内消除所有的方块，消除方块的规则如下：

1. 每步移动可以且仅可以沿横向（即向左或向右）拖动某一方块一格：当拖动这一方块时，如果拖动后到达的位置（以下称目标位置）也有方块，那么这两个方块将交换位置（参见输入输出样例说明中的图 $6$ 到图 $7$）；如果目标位置上没有方块，那么被拖动的方块将从原来的竖列中抽出，并从目标位置上掉落（直到不悬空，参见下面图 $1$ 和图 $2$）；

![](https://cdn.luogu.com.cn/upload/image_hosting/gyse4ktp.png)

2. 任一时刻，如果在一横行或者竖列上有连续三个或者三个以上相同颜色的方块，则它们将立即被消除（参见图1 到图3）。

![](https://cdn.luogu.com.cn/upload/image_hosting/et7at5fd.png)

注意：

a) 如果同时有多组方块满足消除条件，几组方块会同时被消除（例如下面图 $4$，三个颜色为 $1$ 的方块和三个颜色为 $2$ 的方块会同时被消除，最后剩下一个颜色为 $2$ 的方块）。

b) 当出现行和列都满足消除条件且行列共享某个方块时，行和列上满足消除条件的所有方块会被同时消除（例如下面图5 所示的情形，$5$ 个方块会同时被消除）。

3. 方块消除之后，消除位置之上的方块将掉落，掉落后可能会引起新的方块消除。注意：掉落的过程中将不会有方块的消除。

上面图 $1$ 到图 $3$ 给出了在棋盘上移动一块方块之后棋盘的变化。棋盘的左下角方块的坐标为 $(0,0)$，将位于 $(3,3)$ 的方块向左移动之后，游戏界面从图 $1$ 变成图 $2$ 所示的状态，此时在一竖列上有连续三块颜色为 $4$ 的方块，满足消除条件，消除连续 $3$ 块颜色为 $4$ 的方块后，上方的颜色为 $3$ 的方块掉落，形成图 $3$ 所示的局面。

## 输入格式

共 $6$ 行。

第一行为一个正整数 $n$，表示要求游戏通关的步数。

接下来的 $5$ 行，描述 $7 \times 5$ 的游戏界面。每行若干个整数，每两个整数之间用一个空格隔开，每行以一个 $0$ 结束，自下向上表示每竖列方块的颜色编号（颜色不多于 $10$ 种，从 $1$ 开始顺序编号，相同数字表示相同颜色）。

输入数据保证初始棋盘中没有可以消除的方块。
## 输出格式

如果有解决方案，输出 $n$ 行，每行包含 $3$ 个整数 $x,y,g$，表示一次移动，每两个整数之间用一个空格隔开，其中 $(x,y)$ 表示要移动的方块的坐标，$g$ 表示移动的方向，$1$ 表示向右移动，$-1$ 表示向左移动。注意：多组解时，按照 $x$ 为第一关键字，$y$ 为第二关键字，$1$ 优先于 $-1$，给出一组字典序最小的解。游戏界面左下角的坐标为 $(0,0)$。

如果没有解决方案，输出一行 `-1`。

## 样例

### 样例输入 #1
```
3
1 0
2 1 0
2 3 4 0
3 1 0
2 4 3 4 0
```
### 样例输出 #1
```
2 1 1
3 1 1
3 0 1
```
## 提示

**【输入输出样例说明】**

按箭头方向的顺序分别为图 $6$ 到图 $11$

![](https://cdn.luogu.com.cn/upload/image_hosting/vmb8yy6n.png)

样例输入的游戏局面如上面第一个图片所示，依次移动的三步是：$(2,1)$ 处的方格向右移动，$(3,1)$ 处的方格向右移动，$(3,0)$ 处的方格向右移动，最后可以将棋盘上所有方块消除。

**【数据范围】**

对于 $30\%$ 的数据，初始棋盘上的方块都在棋盘的最下面一行；

对于 $100\%$ 的数据，$0<n \le 5$。


---

---
title: "[CERC 2020] Art Transaction"
layout: "post"
diff: 提高+/省选-
pid: P13651
tag: ['模拟', '2020', 'ICPC', 'CERC']
---
# [CERC 2020] Art Transaction
## 题目描述

The largest picture stolen by the gangsters from the State Gallery is to be evaluated by an expert before it is sold on the black market. The composition of the picture clearly follows mainstream tendencies in contemporary AI art. The picture can be viewed as a grid of square cells where each cell is either empty or non-empty. A non-empty cell contains exactly one of these objects: a sun, a house, a chupacabra, a left slope, a right slope, a bird, a drake, or a grill. Two cells are adjacent if they share an edge in the grid. A connection between two cells is a sequence of cells which contains both given cells and in which each two consecutive cells are adjacent in the picture. An area is a set of cells. It is connected if there is a connection between any two cells in the area.

The value of the picture is the total of all values generated by all rules listed below.

- Suns:\
A non-empty cell, not containing a sun, is illuminated by a sun if there is no other object on a straight line between the cell and another cell with a sun. The straight line may be horizontal, vertical or diagonal (both diagonal directions apply). When a cell is illuminated by multiple suns it is still counted only once. A sun cannot illuminate itself. Each illuminated cell generates $100$ .

- Biggest bird:\
A drake is a bird. A flock of birds is maximal connected area of cells each of which contains a bird. The width of a flock is the length of a maximum contiguous sequence of cells on one line in a flock. A flock of birds generates $500 \cdot (\text{width of the flock})$.

- Flock perimeter:\
Each flock of birds (see previous rule) generates value $60 \cdot (\text{flock perimeter})$. Flock perimeter is the total number of edges each of which separates a flock cell from a cell which does not contain a bird or from the outside of the picture.

- House view up:\
When an empty cell is located above a cell containing a house, it is in the same column, and there is no non-empty field between the empty cell and the house, the empty cell generates $10$.

- $3 \times 3$ blocks:\
Each unique $3 \times 3$ block (possibly overlapping) generates $1$.

- Animals I:\
Each edge between a cell with an animal and an empty cell generates $15$.

- Freedom:\
Cell X is a freedom cell if it is either adjacent to the picture border or there is a connection between a cell adjacent to the picture border and a cell adjacent to X and the connection contains only empty cells. Each non-empty freedom cell generates $7$.

- Chupacabra:\
A drake is a bird. Each bird which can be reached by a chupacabra performing one chess knight move in the grid generates $200$

- Peaks:\
A pair of adjacent cells with characters `/` (left slope) and `\` (right slope, in this order) on one line is a peak. Peak summit is an imaginary point in the middle of the segment connecting the uppermost points of both symbols in the peak. Peak value is equal to the maximum Manhattan distance from the peak summit to the summit of another peak in the grid. Note that peak value is an integer. Each peak P generates $50 \cdot (P \text{ value})$ when there are at least two peaks in the picture. Otherwise, a single peak in the picture generates $0$.

- Drake/grill:\
Each cell with a drake and with at least one adjacent cell with a grill generates $500$ .

- Minimum frequency:\
Frequency of an object X is the number of the objects (including X) of the same type as X in the entire picture. Each single object which frequency is minimum among all objects in the picture generates $10$.

- Empty fields:\
Each empty field generates $1$.

- Animals II:\
All animals in the picture together generate single value $1 \cdot (\text{number of chupacabras}) \cdot (\text{number of birds which are not drakes}) \cdot (\text{number of drakes})$.

- House view down:\
When an empty field is located above a house, is in the same column, and there is no non-empty field between the empty field and the house, the empty field generates $5$.

- Grill/drake:\
Each cell with a grill and with at least one adjacent cell with a drake generates $50$.

- Houses and grills:\
Houses and grills in the picture generate $3 \cdot \min \{ \text{number of all houses}, \text{number of all grills} \}$.
## 输入格式

The first input line contains one integer $N$ ($1 \leq N \leq 50$), the number of the rows and the columns in the picture. Next, there are $N$ lines, each specifies one line in the picture. One character on the line represents one cell and its contents.

The interpretation of particular characters in the picture representation follows:
empty cell ` ` (space), sun `*`, house `^`, chupacabra `!`, left slope `/`, right slope `\`, bird `v`, drake `D`, grill `G`.
## 输出格式

Print one integer, the value of the input picture.
## 样例

### 样例输入 #1
```
9
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
```
### 样例输出 #1
```
12672
```
### 样例输入 #2
```
3
!  
  v
 D 
```
### 样例输出 #2
```
2059
```


---

---
title: "[NOI1998] 围巾裁剪"
layout: "post"
diff: 提高+/省选-
pid: P1448
tag: ['模拟', '动态规划 DP', '1998', 'NOI']
---
# [NOI1998] 围巾裁剪
## 题目背景

NOI1998 Day2 T1
## 题目描述

裁缝有一块非常珍贵的丝绸围巾。可惜的是，围巾的某些部分已经被蛀虫给咬坏了。裁缝当然不愿意就这么把围巾给丢了，于是，他想把围巾给裁成两块小围巾送给他的两个女儿。自然，两块小围巾的面积之和越大越好。

这块围巾是一个正三角形，三条边被均匀地分成了 $N$ 段，即这个正三角形被均匀地分成了 $N^2$ 个单元，每个单元是一个面积为 $1$ 的正三角形。

如图所示为一个 $N=5$ 的围巾，图中带阴影的单元表示被蛀虫咬坏的部分。  
从上往下看，围巾被分成了 $N$ 行：
- 第一行有 $1$ 个单元。
- 第二行有 $3$ 个单元，其中有 $2$ 个是形如 $\Delta$ 的，有 $1$ 个是形如 $\nabla$ 的（这两种三角形我们认为是形状相同的）。
- 第三行有 $5$ 个单元，其中有 $3$ 个是形如 $\Delta$ 的，有 $2$ 个是形如 $\nabla$ 的……

用坐标 $(X,Y)$ 给每个单元定位，第一行的单元的坐标为 $(1,1)$；第二行从左到右的三个单元的坐标依次为 $(2,1)$、$(2,2)$、$(2,3)$；……

![](https://cdn.luogu.com.cn/upload/image_hosting/rwklebsy.png)

围巾的剪裁条件如下：  
  1. 裁成的两块小围巾形状与原来的大围巾完全相同，都是正三角形；
  2. 每一块小围巾里都不存在被蛀虫咬坏的部分；
  3. 裁剪时必须沿着单元的边界裁剪；
  4. 要求两块小围巾的面积的总和最大。

图中，最优的裁剪方法已经用粗线画了出来，面积和为 $4+9=13$。  
现在需要你编一个程序来帮助裁缝解决这个问题。
## 输入格式

- 输入的第一行为一个整数 $N$（$1\leq N\leq100$），表示这块围巾总共被分成了 $N^2$ 个单元。
- 第二行为一个整数 $M$（$1\leq M\leq N^2-2$），表示这块围巾共有 $M$ 个单元被蛀虫咬坏了。
- 接下来的 $M$ 行，每一行有两个正整数 $X$ 和 $Y$，为这 $M$ 个被蛀虫咬坏的单元的坐标。

输入文件中同一行相邻两项之间用一个或多个空格隔开。
## 输出格式

输出文件仅含一个整数，为你所找到的裁出两块小围巾面积总和的最大值。
## 样例

### 样例输入 #1
```
5
5
3 2
4 1
4 4
5 4
5 2
```
### 样例输出 #1
```
13
```
## 提示

**【样例解释】**

如「题目描述」中图所示，两块小围巾面积总和的最大值为 $4+9=13$。

**【数据范围】**

- 对于 $50\%$ 的数据，$1\leq N\leq50$；
- 对于 $100\%$ 的数据，$1\leq N\leq100$，$0\leq M\leq N^2$，$1\leq X\leq N$，$1\leq Y\leq 2\times N-1$。

本题数据为 Windows（CRLF）格式。


---

---
title: "数7"
layout: "post"
diff: 提高+/省选-
pid: P1662
tag: ['模拟']
---
# 数7
## 题目描述

$1337$ 个人排成一个圈，从 $1$ 号人开始报数，初始方向是 $1,2,3\dots$。如果某个人报的数是 $7$ 的倍数或数字中含有 $7$，那么报数的方向就反一下。问报数字 $X$ 的是第几号人？

**比如初始 $20$ 个数字的情况是：**

| 数字 $X$ | 报的人的编号 |
| :----------: | :----------: |
| $1$ | $1$ |
| $2$ | $2$ |
| $3$ | $3$ |
| $4$ | $4$ |
| $5$ | $5$ |
| $6$ | $6$ |
| $7$ | $7$ |
| $8$ | $6$ |
| $9$ | $5$ |
| $10$ | $4$ |
| $11$ | $3$ |
| $12$ | $2$ |
| $13$ | $1$ |
| $14$ | $1337$ |
| $15$ | $1$ |
| $16$ | $2$ |
| $17$ | $3$ |
| $18$ | $2$ |
| $19$ | $1$ |
| $20$ | $1337$ |

## 输入格式

一行一个整数 $X$。
## 输出格式

一行一个整数，表示最终报数字 $X$ 的是第几号人。
## 样例

### 样例输入 #1
```
1000
```
### 样例输出 #1
```
1311
```
## 提示

**【数据规模与约定】**

对于 $30\%$ 的数据，满足 $X\leq10^6$；

对于 $90\%$ 的数据，满足 $X\leq10^8$；

对于 $100\%$ 的数据，满足 $X\leq10^9$。


---

---
title: "Diamond A&B(2)"
layout: "post"
diff: 提高+/省选-
pid: P1741
tag: ['模拟', '字符串']
---
# Diamond A&B(2)
## 题目背景

由于本题较难，将本题拆做两题，分别为 diamond A 以及 diamond B。本题为 Diamond B。


## 题目描述

教主上电视了！这个消息绝对是一个爆炸性的新闻。一经传开，大街上瞬间就没人了（都回家看电视去了），商店打烊，工厂停业。大家都把电视机的音量开到最大，教主的声音回响在大街小巷。

小 L 给小 X 慌乱地打开自己家的电视机，发现所有频道都播放的是教主的采访节目（-\_-bbb）。只见电视屏幕上的教主笑意吟吟，给大家出了一道难题：

一个边长为 $n$ 的大菱形被均匀地划分成了 $n\times n$ 个边长为 $1$ 的小菱形组成的网格，但是网格中部分边被抹去了，小 $L$ 想知道，大菱形内有多少个平行四边形，这些平行四边形内不存在边（平行四边形内是空的）。

教主说，如果谁写出了程序，移动用户请将程序发送到 xxxx，联通用户请将程序发送到 xxxx……如果答对这个题，将有机会参加抽奖，大奖将是教主签名的 Orz 教主 T-Shirt 一件！这个奖品太具有诱惑力了。于是你需要编一个程序完成这么一道题。

## 输入格式

输入的第一行为一个正整数 $n$，为大菱形的边长。

以下 $2n$ 行，每行 $2n$ 个字符，字符为空格，$\verb!/!$，$\verb!\!$ 中的一个。

前 $n$ 行，第 $i$ 行中居中有 $2i$ 个字符，这 $2i$ 个字符中位置为奇数的字符只可能为 $\verb!/!$ 或者空格，位置为偶数的字符只可能为 $\verb!\!$ 或空格，若为空格表示这样一条边不存在，其余字符均为空格，描述了大菱形的上半部分。

后 $n$ 行，第 $i$ 行居中有有 $2(n-i+1)$ 个字符，与上半部分类似地描述了菱形的下半部分。

输入文件保证大菱形的轮廓上没有边被抹去。
## 输出格式

输出仅包括一个整数，为满足要求的平行四边形个数。

## 样例

### 样例输入 #1
```
4

1111

11101

1000

10111

1100

10101

0111

11101

1111


```
### 样例输出 #1
```
3
```
## 提示

### 数据范围及约定

- 对于 $20\%$ 的数据，$n \le 10$；
- 对于 $40\%$ 的数据，$n \le 60$；
- 对于 $60\%$ 的数据，$n \le 200$；
- 对于 $100\%$ 的数据，$n \le 888$。


---

---
title: "贪吃虫"
layout: "post"
diff: 提高+/省选-
pid: P1751
tag: ['模拟', '搜索', '图论', '深度优先搜索 DFS']
---
# 贪吃虫
## 题目背景

我们都知道一个很著名的游戏——贪吃蛇。它的一大特点是当前一个食物被吃掉后，后一个食物才会出现。今天我们要做的另一个游戏——贪吃虫也很类似。

## 题目描述

贪吃虫有 $k$ 条，在一棵有 $n$ 个节点的树上，每只虫子都在不同的节点上。第一个食物到来时，所有的 $k$ 只虫会从它们当前的位置出发，前往食物的位置。它们的移动遵循如下规则：

- 这棵树上的任何两个节点之间有且仅有一条路，所有的贪吃虫沿着唯一的路径前往食物所在的位置；
- 如果有一只贪吃虫到达了食物所在的位置，食物马上就被吃掉了；
- 如果有另外一只贪吃虫在某一只贪吃虫通往食物的道路上，那么距离食物较远的那只虫子会停止移动，停留在当前的节点上；
- 如果有多只虫子尝试进入同一个节点，只有编号最小的虫子能够到达，其它的贪吃虫停留在它们当前的位置上；
- 吃掉食物的那只虫子会停留在食物的位置上；
- 食物被吃掉之后会出现在树上的另外一个节点上。这时所有的贪吃虫会重新出发，尝试再一次吃掉食物。为了简化过程，我们假设从一个节点移动到相邻的节点需要花费一个单位时间。

## 输入格式

第 $1$ 行一个整数 $n$，表示树上的节点个数。

第 $2$ 至 $N$ 行，第 $i+1$ 行包含了一个两个整数 $:A_i,B_i$，表示从节点 $A_i$ 到节点 $B_i$ 有一条边直接相连。

第 $N+1$ 行有一个整数 $k$，表示树上贪吃虫的个数。

第 $N+2$ 至 $N+1+k$ 行，第 $N+1+i$ 行有一个整数 $P_i$，表示第 $i$ 只贪吃虫开始时的位置，任何两只贪吃虫的初始位置不相同。

第 $N+2+k$ 行：有一个整数 $h$，表示食物一共在树上出现了多少次。

接下来的 $h$ 行，每行一个整数，表示食物依次出现的位置。
## 输出格式

输出一共包含 $k$ 行，第 $i$ 行有两个整数 $C_i$ 和 $D_i$。分别表示第 $i$ 只贪吃虫最终停留的位置和这只贪吃虫吃到食物的次数。
## 样例

### 样例输入 #1
```
4

1 2

1 3

2 4

2

1

2

2

2

4
```
### 样例输出 #1
```
1 0

4 2


```
## 提示


### 数据范围及约定

对于全部数据，$1 \le n \le 5000$，$1 \le k \le 1000$，$k \le n$，$1 \le h \le 500$。


---

---
title: "正方形"
layout: "post"
diff: 提高+/省选-
pid: P1761
tag: ['模拟']
---
# 正方形
## 题目描述

有 $n$ 个大小不一的正方形，现将它们依次以 $45$ 度斜放入第一象限，每个正方形都要与 $x$ 轴有一个交点，且不能与之前放入的正方形重叠。在此前提下，正方形与 $x$ 轴交点的坐标应尽可能小。问这样放置后，从上往下看，至少能部分被看见的正方形有哪些？
## 输入格式

每个测试点包含多组测试数据。每个测试数据的第一行是一个整数 $n$，第二行是 $n$ 个正整数，表示每个正方形的边长。输入以一行单独的 $0$ 结束。
## 输出格式

对于每个测试数据输出一行，增序输出至少可看到部分的正方形的编号，用空格隔开。

## 样例

### 样例输入 #1
```
4 

3 5 1 4 

3 

2 1 2 

0 
```
### 样例输出 #1
```
1 2 4 

1 3
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/flwonnba.png)

### 数据范围及约定

- 对于 $50\%$ 的数据，$n \le 10$；
- 对于 $100\%$ 的数据，$n \le 50$ 正方形的大小不超过 $30$。



---

---
title: "对撞机"
layout: "post"
diff: 提高+/省选-
pid: P1871
tag: ['模拟', 'Special Judge']
---
# 对撞机
## 题目描述

在2312年，宇宙中发现了 $n$ 台巨型对撞机，这些对撞机分别用 $1 \sim n$ 的自然数标识。科学家们不知道启动这些对撞机会发生什么危险事故，所以这些机器，刚开始都是出于关闭的状态。

随着科学家们的研究发现，第 $i$ 台对撞机启动是安全的，当且仅当其他已经启动的对撞机的标识数都跟这台对撞机标识数互质。（例如假设前面启动的对撞机标识数是 $j$，如果 $i$ 能启动，那么 $i,j$ 互质，即 $\gcd(i,j) = 1$）。如果两台对撞机的标识数不为互质数就启动，那么就会发生爆炸事故。

基于前面的研究，科学家们准备做各种启动和关闭对撞机的实验。为了确保科学家们的生命安全，你要设计一个远程遥控的软件。

刚开始，所有的对撞机都是关闭状态。你的程序将会收到许多询问，格式为“启动、关闭第 $i$ 台对撞机”。这个程序应该能处理这些询问（根据收到询问的先后顺序处理）。程序按照如下的格式输出处理结果。

如果询问为 `+ i`（表示启动第 $i$ 台对撞机），程序应该按照下面三种情况之一输出结果。

- `Success`，表示启动第 $i$ 台是安全的。
- `Already on`，表示第 $i$ 台在询问之前就已经启动了。
- `Conflict with j`，表示第 $i$ 台与前面已经启动的第 $j$ 台冲突。如果前面有多台对撞机跟 $i$ 冲突，那么只输出其中任何一台即可。

如果询问为 `- i`（表示关闭第 $i$ 台对撞机），程序应该按照下面两种情况之一输出结果。

- `Success`，表示关闭第 $i$ 台对撞机。
- `Already off`，表示第 $i$ 台对撞机在询问之前就已经关闭了。
## 输入格式

第一行输入两个以空格隔开的整数 $n$ 和 $m$，分别表示对撞机的数量和询问数。

接下来 $m$ 行，表示询问，每行仅可能是 `+ i` 或 `- i`，表示开启或关闭第 $i$ 台对撞机。
## 输出格式

输出 $m$ 行，输出结果按照上面题目给定格式输出。
## 样例

### 样例输入 #1
```
10 10 
+ 6
+ 10
+ 5
- 10
- 5
- 6
+ 10 
+ 3
+ 6
+ 3

```
### 样例输出 #1
```
Success
Conflict with 6
Success
Already off
Success
Success
Success
Success
Conflict with 3
Already on

```
## 提示

**数据范围**

$1 \le n,m \le 10^5$，$1 \le i \le n$。

---

感谢 @cn：苏卿念 提供 Special Judge



---

---
title: "地砖铺设"
layout: "post"
diff: 提高+/省选-
pid: P2102
tag: ['模拟', '字符串', '贪心']
---
# 地砖铺设
## 题目描述

在游戏厅大赚了一笔的小 Z 终于赢到了他想要的家具。乘此机会，他想把自己的房间好好整理一下。

在百货公司，可以买到各种各样正方形的地砖，为了美观起见，小 Z 不希望同样颜色的正方形地砖相邻。所以他找到了小 C 来帮忙解决这件事情。

小 C 很快解决了这个任务。然而，出于某种强迫症，她希望在地上按照长宽划分成网格后，逐行逐列每一块的颜色组成的序列的字典序最小。她希望你帮忙验证一下她的方案。

## 输入格式

第一行，包含两个整数 $N$ 和 $M$，表示房间的长和宽。
## 输出格式

$N$ 行，每行 $M$ 列，表示地砖铺设的方案，需要这个方案是字典序最小的合法方案。（可以认为，输出的方案去掉回车后形成的字符串字典序最小）

## 样例

### 样例输入 #1
```
4 3
```
### 样例输出 #1
```
AAA
AAA
AAA
BCB
```
## 提示

对于 $50\%$ 的数据，保证 $N,M \leq 5$。

对于 $100\%$ 的数据，保证 $1 \leq N,M \leq 100$。



---

---
title: "图书馆书架上的书"
layout: "post"
diff: 提高+/省选-
pid: P2125
tag: ['模拟', '数学']
---
# 图书馆书架上的书
## 题目背景

NOIP2014 即将来临，JC 书院信息学兴趣小组也在积极准备着，于是乎 usqwedf 、梁大大、畜牧办专场、YH 大神和 LHT 大神也要推出“蓝翔杯”。

在图书馆、 MC 等大神们相继举办了 JC 书院联合竞赛“弃疗杯”“UID#3”，据说 YH 大神还要苦苦钻研网络流的 JC 书院 $13$ 届 $13$ 班的 WZF 神牛和 MZC 神牛听到这个消息后决定联袂打造“十三点杯”。但是出一套题目是一项繁重的工作，于是他们决定再拉上和他们同届并且同班还同为 JC 书院信息学兴趣小组成员同时也在图书馆正在找“Hello World”标程的蒟蒻 SY。

可怜的蒟蒻 SY 因为还要写一大堆的作业，怎么也不肯答应，终于 WZF 神牛妥协说：“我来出一道题，你要是做出来了我们就不让你出题，否则……你懂的。”蒟蒻 SY 才刚看完 WZF 神牛即兴出的题目，便带着哭腔对 WZF 神牛说：“你们赢了。”。

可是蒟蒻 SY 实在是太弱了，根本不会出题，他绞尽脑汁，终于想到了一个办法——将 WZF 神牛出的题目 copy 一下。
## 题目描述

图书馆有 $n$ 个书架，第 $1$ 个书架后面是第 $2$ 个书架，第 $2$ 个书架后面是第 $3$ 个书架……第 $n-1$ 个书架后面是第 $n$ 个书架，第 $n$ 个书架后面是第 $1$ 个书架，第 $i$ 个书架上有 $b_i$ 本书。现在，为了让图书馆更美观，WZF 神牛让蒟蒻 SY 搬动书架上的书，使每个书架上的书一样多。由于搬动的书可能会很多，所以蒟蒻 SY 只能将一个书架上的书搬到与其相邻的两个书架上。那么蒟蒻 SY 最少搬动几本书呢？
## 输入格式

共 $2$ 行，第 $1$ 行 $1$ 个正整数 $n$，第 $2$ 行 $n$ 个非负整数，第 $i$ 个为 $b_i$。
## 输出格式

输出共 $n+1$ 行。

第一行 $1$ 个正整数 $m$，表示蒟蒻 SY 最少搬动 $m$ 本书；

之后 $n$ 行，每行 $2$ 个整数，第 $i$ 行有两个整数 $af_i$ 和 $ab_i$，分别表示蒟蒻 SY 要将第 $i$ 个书架上的 $af_i$ 本书和 $ab_i$ 本书分别搬到它前面的一个书架上和它后面的一个书架上。
## 样例

### 样例输入 #1
```
5
15 7 11 3 14

```
### 样例输出 #1
```
12
2 3
-3 0
0 1
-1 -6
6 -2

```
## 提示

### 数据范围及约定

对于全部数据，$1\le n\le 10^5+1$，且 $n$ 必为奇数；$b_i\le 10^7$。

若 $af_i$ 为负数，则说明蒟蒻 SY 要把第 $i$ 个书架前面的那个书架上的 $-af_i$ 本书搬到第 $i$ 个书架上。

同理，若 $ab_i$ 为负数，则说明蒟蒻 SY 要把第 $i$ 个书架后面的那个书架上的 $-ab_i$ 本书搬到第 $i$ 个书架上。



---

---
title: "序列排序"
layout: "post"
diff: 提高+/省选-
pid: P2127
tag: ['模拟', '贪心', '离散化']
---
# 序列排序
## 题目描述

小C有一个N个数的整数序列，这个序列的中的数两两不同。小C每次可以交换序列中的任意两个数，代价为这两个数之和。小C希望将整个序列升序排序，问小C需要的最小代价是多少？

## 输入格式

第一行，一个整数N。

第二行，N个整数，表示小C的序列。

## 输出格式

一行，一个整数，表示小C需要的最小代价。

## 样例

### 样例输入 #1
```
6
8 4 5 3 2 7
```
### 样例输出 #1
```
34
```
## 提示

数据范围：

对于30%的数据，1<=N<=10；

对于全部的数据，1<=N<=100000，输入数据中的其他整数均为正整数且不超过 $10^9$。



---

---
title: "小Z的掷骰游戏"
layout: "post"
diff: 提高+/省选-
pid: P2139
tag: ['模拟']
---
# 小Z的掷骰游戏
## 题目描述

小 Z 得到了一种奇特的骰子（如下图所示），想要用它进行掷骰游戏。

![](https://cdn.luogu.com.cn/upload/pic/1263.png)

游戏很简单，小 Z 每次都从同样的位置将一个骰子竖直抛下，当骰子落到平面或另一个骰子上时停下来。然而，由于这是一种奇特的骰子，它还会继续翻滚和下落。这种骰子有以下特性：

- 普通骰子可能往四个方向翻滚，而这种骰子只能往 $4,5,6$ 这三个面的方向翻滚。在下图所示的情况中，这种骰子只能往两个方向翻滚；

![](https://cdn.luogu.com.cn/upload/pic/1264.png)

- 这种骰子只有在翻滚后会导致其下落时才会翻滚（如下图所示），当有多个方向可以翻滚时，它会往数字最大的面的方向翻滚；

![](https://cdn.luogu.com.cn/upload/pic/1265.png)

- 这种骰子翻滚恰好 $90^\circ$ 后会竖直下落，当落到平面或另一个骰子上时停下来（如下图中的 $B$ 和 $C$ 所示），然后继续翻滚和下落的过程。

![](https://cdn.luogu.com.cn/upload/pic/1266.png)

上图就是将 $4$ 个骰子均以上面是 $6$ 前面是 $4$ 的状态依次抛下的过程。

现在小 Z 抛了 $n$ 个骰子，他想知道游戏结束后从上面看每个数字分别出现了多少次（如下图所示），希望你帮帮他。

![](https://cdn.luogu.com.cn/upload/pic/1267.png)
## 输入格式

每次多组数据，每组数据格式如下：

第 $1$ 行，一个整数 $n$，表示抛了 $n$ 个骰子；

第 $2\sim n+1$ 行，每行包含两个整数 $t,f$，表示一个骰子以上面是 $t$ 前面是 $f$ 的状态抛下。
## 输出格式

对于每组数据，输出一行，每行包含六个整数，表示游戏结束后从上面看每个数字分别出现的次数。

## 样例

### 样例输入 #1
```
4
6 4
6 4
6 4
6 4
1
2 1

```
### 样例输出 #1
```
0 1 1 0 0 1
0 1 0 0 0 0
```
## 提示

本题有 $4$ 个点，每个点 $25$ 分。

对于 $25\%$ 的数据，$n=1$。

对于另外 $25\%$ 的数据，$n=2$。

对于 $100\%$ 的数据，$1 \leq n \leq 100$，不超过 $30$ 组数据。


---

---
title: "[USACO13JAN] Painting the Fence S"
layout: "post"
diff: 提高+/省选-
pid: P2205
tag: ['模拟', '数学', '2013', '线段树', 'USACO', '离散化']
---
# [USACO13JAN] Painting the Fence S
## 题目描述

Farmer John has devised a brilliant method to paint the long fence next to his barn (think of the fence as a one-dimensional number line).  He simply attaches a paint brush to his favorite cow Bessie, and then retires to drink a cold glass of water as Bessie walks back and forth across the fence, applying paint to any segment of the fence that she walks past.

Bessie starts at position 0 on the fence and follows a sequence of N moves (1 <= N <= 100,000).  Example moves might be "10 L", meaning Bessie moves 10 units to the left, or "15 R", meaning Bessie moves 15 units to the right.  Given a list of all of Bessie's moves, FJ would like to know what area of the fence gets painted with at least K coats of paint.  Bessie will move at most 1,000,000,000 units away from the origin during her walk.



Farmer John 想出了一个给牛棚旁的长围墙涂色的好方法。（为了简单起见，我们把围墙看做一维的数轴，每一个单位长度代表一块栅栏）

他只是简单的把刷子蘸满颜料，系在他最喜欢的奶牛Bessie上，然后让Bessie来回地经过围墙，自己则在一旁喝一杯冰镇的凉水。（……-\_-|||) 

Bessie 经过的所有围墙都会被涂上一层颜料。Bessie从围墙上的位置0出发，并将会进行N次移动(1 <= N <= 100,000)。比如说，“10 L”的意思就是Bessie向左移动了10个单位。再比如说“15 R”的意思就是Bessie向右移动了15个单位。

给出一系列Bessie移动的清单。FJ 想知道有多少块栅栏涂上了至少K层涂料。注意：Bessie最多会移动到离原点1,000,000,000单位远的地方。

## 输入格式

\* 第1行： 两个整数： N K

\* 第2...N+1 行： 每一行都描述了Bessie的一次移动。 （比如说 “15 L"）

## 输出格式

\* 一个整数：被至少涂上K层涂料的栅栏数

（注意：输出的最后一定要输出换行符！否则会WA）

## 样例

### 样例输入 #1
```
6 2 
2 R 
6 L 
1 R 
8 L 
1 R 
2 R 
```
### 样例输出 #1
```
6
```
## 提示

PS1：来源：usaco jan silver P01 想看原题的请戳http://www.usaco.org/index.php?page=viewproblem2&cpid=226）

PS2：测试数据也可以在在http://www.usaco.org/index.php?page=jan13problems上下载，还可以看到题解（不过是英文的:-D）

PS3:如果有翻译的问题或题目的不理解，可以在问答后面留言的说。



---

---
title: "[USACO13OPEN] What's Up With Gravity S"
layout: "post"
diff: 提高+/省选-
pid: P2208
tag: ['模拟', '图论', '2013', 'USACO', '枚举', '分治', '广度优先搜索 BFS']
---
# [USACO13OPEN] What's Up With Gravity S
## 题目描述

Captain Bovidian is on an adventure to rescue her crew member, Doctor Beefalo.  Like all great adventures, this story plays out in a two dimensional N by M grid (1 <= N, M <= 500), representing a side view of the captain's world.  Some grid cells are empty while others are blocked and cannot be traversed.

Unfortunately, Captain Bovidian cannot jump.  She must obey the following rules of physics while traversing her world.

1) If there is no cell directly underneath Captain Bovidian (that is, if she is at the edge of the grid), then she flies out into space and fails her mission.

2) If the cell directly underneath Captain Bovidian is empty, then she falls into that cell.

3) Otherwise:

a) Captain Bovidian may move left or right if the corresponding cell exists and is empty.

b) Or, Captain Bovidian may flip the direction of gravity.

When Captain Bovidian changes the direction of gravity, the cell that's 'underneath' her (as mentioned in rules 1 and 2) toggles between the cell with one higher row index and the cell with one lower row index (the first row in the input has index 1, and the last row has index N). Initially, the cells with one higher row index are underneath Captain Bovidian.

Doctor Beefalo is lost somewhere in this world.  Help Captain Bovidian arrive at her cell using the least number of gravity flips as possible.  If it is impossible to reach Doctor Beefalo, please output -1.


Bovidian 船长正在拯救她的船员，Beefalo 博士。

和所有伟大的冒险故事一样，这个故事也是发生在一个2D平面上的。囧

这个平面是M\*N的格子组成的网格，代表着船长的世界的一个侧视图。

有些格子是空的，另一些则是实心的，并且不能直接通过。

很不幸的是，船长跳不起来。她必须遵守这个世界的特殊物理法则。

1）如果船长的正下方没有方块（换句话说，即使她正在网格的边缘），那么她就会掉入宇宙中，同时意味着冒险失败。

2）如果船长的正下方的方块是空的，那么她就会掉到这个方块，

3）在不满足1）与2）的情况下，船长可以做一下的事情：

a) 如果左边(或右边）的方格是空的，那么她可以走到那个格子。

b船长可以翻转重力的方向

当船长改变翻转重力的方向时，我们就改变船长”下方“的定义。

”下方“的定义只能是两种

(A)比船长位置所在的方格的列编号更大的格子，

(B)比船长位置所在的方格的列编号更小的格子,

一开始的时候，“下方”的定义是比船长位置所在方格的列编号更大的格子。

Beefalo博士正迷失在这个世界中的某一处，请帮助船长从起点到达博士的地方。

如果可以到达，请输出最少需要的翻转重力的次数。


如果不可以到达，请输出-1

## 输入格式

第1行输入两个整数 N,M

第2行到N+1行中，第i+1行则是代表船长世界的第i行。每行有M个字符。

其中","代表着一个空的格子，"#"代表着一个实心的格子，"C"代表着船长的位置，"D"代表着博士的位置。

## 输出格式

一行，输出一个整数。

如果船长可以到达，请输出最少需要的翻转重力的次数。

如果不可以到达，请输出-1

## 样例

### 样例输入 #1
```
5 5
#####
#...#
#...D
#C...
##.##
```
### 样例输出 #1
```
3
```
## 提示

输出解释：

首先，船长在（4,2），接着她翻转重力，到达（2,2）

接着她向右走走到（2,4），接着她第二次翻转重力，到达（4,4）

然后她继续向右走到（4,5），最后在翻转一次重力，到达博士所在的（3,5）



---

---
title: "[HNOI2003] 操作系统"
layout: "post"
diff: 提高+/省选-
pid: P2278
tag: ['模拟', '2003', '各省省选', '湖南', '优先队列', '队列']
---
# [HNOI2003] 操作系统
## 题目描述

写一个程序来模拟操作系统的进程调度。假设该系统只有一个 CPU，每一个进程的到达时间，执行时间和运行优先级都是已知的。其中运行优先级用自然数表示，数字越大，则优先级越高。

如果一个进程到达的时候 CPU 是空闲的，则它会一直占用 CPU 直到该进程结束。除非在这个过程中，有一个比它优先级高的进程要运行。在这种情况下，这个新的（优先级更高的）进程会占用 CPU，而老的只有等待。

如果一个进程到达时，CPU 正在处理一个比它优先级高或优先级相同的进程，则这个（新到达的）进程必须等待。

一旦 CPU 空闲，如果此时有进程在等待，则选择优先级最高的先运行。如果有多个优先级最高的进程，则选择到达时间最早的。

## 输入格式

输入包含若干行，每一行有四个自然数（均不超过 $10^8$），分别是进程号，到达时间，执行时间和优先级。不同进程有不同的编号，不会有两个相同优先级的进程同时到达。输入数据已经按到达时间从小到大排序。输入数据保证在任何时候，等待队列中的进程不超过 $15000$ 个。

## 输出格式

按照进程结束的时间输出每个进程的进程号和结束时间。

## 样例

### 样例输入 #1
```
1 1 5 3 
2 10 5 1 
3 12 7 2 
4 20 2 3 
5 21 9 4 
6 22 2 4 
7 23 5 2 
8 24 2 4 

```
### 样例输出 #1
```
1 6
3 19
5 30
6 32
8 34
4 35
7 40
2 42

```


---

---
title: "[NOI2014] 随机数生成器"
layout: "post"
diff: 提高+/省选-
pid: P2354
tag: ['模拟', '贪心', '2014', 'NOI']
---
# [NOI2014] 随机数生成器
## 题目描述

小 H 最近在研究随机算法。随机算法往往需要通过调用随机数生成函数（例如 Pascal 中的 random 和 C/C++中的 rand）来获得随机性。事实上，随机数生成函数也并不是真正的“随机”，其一般都是利用某个算法计算得来的。

比如，下面这个二次多项式递推算法就是一个常用算法：

算法选定非负整数 $x_0,a,b,c,d$ 作为随机种子，并采用如下递推公式进行计算。

对于任意 $i ≥ 1,x_i=(a \times x_{i-1}^2+b \times x_{i-1}+c)\mod d$ 这样可以得到一个任意长度的非负整数数列$\{x_i\},i \ge 1$，一般来说，我们认为这个数列是随机的。

利用随机序列 ${xi},i≥1$，我们还可以采用如下算法来产生一个 $1$ 到 $K$ 的随机排列$ \{ Ti \},i=1 ... k$：

1. 初始设 $T$ 为 $1$ 到 $K$ 的递增序列；
2. 对 $T$ 进行 $K$ 次交换，第 $i$ 次交换，交换 $T_i$ 和 $T_{(x_i \bmod i) + 1}$ 的值。

此外，小 H 在这 $K$ 次交换的基础上，又额外进行了 $Q$ 次交换操作，对于第i 次额外交换，小 H 会选定两个下标 $u_i$ 和 $v_i$，并交换 $T_{u_i}$ 和 $T_{v_i}$ 的值。

为了检验这个随机排列生成算法的实用性，小 H 设计了如下问题：

小 H 有一个 $N$ 行 $M$ 列的棋盘，她首先按照上述过程，通过 $N \times M + Q$ 次交换操作，生成了一个 $1\sim N \times M$ 的随机排列 $\{Ti\},i=1 ... N \times M$，然后将这 $N \times M$ 个数逐行逐列依次填入这个棋盘：也就是第 $i$ 行第 $j$ 列的格子上所填入的数应为 $ T_{(i-1) \times M+j} $。

接着小 H 希望从棋盘的左上角，也就是第一行第一列的格子出发，每次向右走或者向下走，在不走出棋盘的前提下，走到棋盘的右下角，也就是第 $N$ 行第 $M$ 列的格子。

小 H 把所经过格子上的数字都记录了下来，并从小到大排序，这样，对于任何一条合法的移动路径，小 H 都可以得到一个长度为 $N + M - 1$ 的升序序列，我们称之为路径序列。

小 H 想知道，她可能得到的字典序最小的路径序列应该是怎样的呢？
## 输入格式

第 1 行包含 $5$ 个整数，依次为 $x_0,a,b,c,d$ ，描述小H采用的随机数生成算法所需的随机种子。

第 2 行包含三个整数 $N,M,Q$ ，表示小H希望生成一个1到 $N \times M$ 的排列来填入她 $N$ 行 $M$ 列的棋盘，并且小H在初始的 $N \times M$ 次交换操作后，又进行了 $Q$ 次额外的交换操作。

接下来 $Q$ 行，第 $i$ 行包含两个整数 $u_i,v_i$，表示第 $i$ 次额外交换操作将交换 $T_{u_i}$和 $T_{v_i}$ 的值。
## 输出格式

输出一行，包含 $N+M-1$ 个由空格隔开的正整数，表示可以得到的字典序最小的路径序列。
## 样例

### 样例输入 #1
```
1 3 5 1 71 
3 4 3 
1 7 
9 9 
4 9 
```
### 样例输出 #1
```
1 2 6 8 9 12 
```
### 样例输入 #2
```
654321 209 111 23 70000001 
10 10 0 
```
### 样例输出 #2
```
1 3 7 10 14 15 16 21 23 30 44 52 55 70 72 88 94 95 97
```
### 样例输入 #3
```
123456 137 701 101 10000007 
20 20 0 
```
### 样例输出 #3
```
1 10 12 14 16 26 32 38 44 46 61 81 84 101 126 128 135 140 152 156 201 206 237 242 243 253 259 269 278 279 291 298 338 345 347 352 354 383 395 

```
## 提示

对于样例 1，根据输入的随机种子，小 H 所得到的前 12 个随机数xi为：

9 5 30 11 64 42 36 22 1 9 5 30

根据这 12 个随机数，小 H 在进行初始的 12 次交换操作后得到的排列为：

6 9 1 4 5 11 12 2 7 10 3 8

在进行额外的 3 次交换操作之后，小 H 得到的最终的随机排列为：

12 9 1 7 5 11 6 2 4 10 3 8


```cpp
12 9 1 7 
5 11 6 2 
4 10 3 8
```

最优路径依次经过的数字为 ：12-9-1-6-28。

![](https://cdn.luogu.com.cn/upload/pic/2590.png)



---

---
title: "整式的计算【数据有误】"
layout: "post"
diff: 提高+/省选-
pid: P2379
tag: ['模拟', '字符串', '数学', '洛谷原创']
---
# 整式的计算【数据有误】
## 题目背景

小明上了初中，整式计算总是出错，所以他找到了爱编程的你，让你设计一个程序帮帮他。

## 题目描述

输入几个单项式或多项式，计算结果。

## 输入格式

包括+，-,\*,字母(只包括a到z26个小写字母)单项式两边没有括号，多项式两边有( )或[ ]，保证在每一个因式中，单项式在多项式前面。（长度不超过255）

## 输出格式

输出这个表达式的结果，每个因式按字典序排列。

## 样例

### 样例输入 #1
```
(a+b)*(a+b+c)
```
### 样例输出 #1
```
a^2+2ab+ac+b^2+bc
```
### 样例输入 #2
```
(a+b)*(a+b+c)
```
### 样例输出 #2
```
a^2+2ab+ac+b^2+bc
```
### 样例输入 #3
```
(2a+b)*(2a-b)
```
### 样例输出 #3
```
4a^2-b^2
```
### 样例输入 #4
```
(a+b)*(a+b)*(a+b)
```
### 样例输出 #4
```
a^3+3a^2b+3ab^2+b^3
```
### 样例输入 #5
```
f*(a+b+d+z)+f^2
```
### 样例输出 #5
```
af+bf+df+fz+f^2
```
### 样例输入 #6
```
(a+b+2c)*(a+b-2c)-(a+b)*(a+b)
```
### 样例输出 #6
```
-4c^2
```
## 提示

水题一道。



---

---
title: "白雪皑皑"
layout: "post"
diff: 提高+/省选-
pid: P2391
tag: ['模拟', '并查集', '福建省历届夏令营']
---
# 白雪皑皑
## 题目背景

“柴门闻犬吠，风雪夜归人”，冬天，不期而至。千里冰封，万里雪飘。空中刮起了鸭毛大雪。雪花纷纷，降落人间。 美能量星球（pty 在 spore 上的一个殖民地）上的人们被这美景所震撼。但是 pty 却不高兴，他不喜欢白色的世界，他觉得这样太单调了。所以他想对雪花进行染色，让世界变得多彩些。

## 题目描述

现在有 $n$ 片雪花排成一列。 pty 要对雪花进行 $m$ 次染色操作，第 $i$ 次染色操作中，把第 $((i\times p+q)\bmod n)+1$ 片雪花和第 $((i\times q+p)\bmod n)+1$ 片雪花之间的雪花（包括端点）染成颜色 $i$。其中 $p,q$ 是给定的两个正整数。他想知道最后 $n$ 片雪花被染成了什么颜色。没有被染色输出 $0$。
## 输入格式

输入共四行，每行一个整数，分别为 $n,m,p,q$，意义如题中所述。
## 输出格式

输出共 $n$ 行，每行一个整数，第 $i$ 行表示第 $i$ 片雪花的颜色。
## 样例

### 样例输入 #1
```
4
3
2
4
```
### 样例输出 #1
```
2
2
3
0
```
## 提示

- 对于 $20\%$ 的数据满足：$n,m\leq 1000$。
- 对于 $40\%$ 的数据满足：$n\leq 8000$，$m\leq 10^6$。
- 对于 $80\%$ 的数据满足：$n\leq 5\times 10^5$，$m\leq 10^7$。
- 对于 $100\%$ 的数据满足：$1\leq n\leq 10^6$，$1\leq m\leq 10^7$。

保证 $1\leq m\times p+q,m\times q+p\leq 2\times 10^9$。


---

---
title: "yyy loves physics IV"
layout: "post"
diff: 提高+/省选-
pid: P2413
tag: ['模拟', '字符串', '搜索']
---
# yyy loves physics IV
## 题目背景

“颤抖吧，实验室！”

yyy再一次来到了那个惨遭蹂躏的实验室。

## 题目描述

这次，在 Round1 里几乎壮烈牺牲的电路君又被翻了出来。一共有 $N$（$1 \le N \le 26$）个元件。

物理学霸 yyy 用一堆导线将他们连了起来，串联，并联，各种联……

但由于 yyy 的操作太不规范，导致每个元件都有损坏的风险，yyy 用他那天才的脑子算出元件 $i$ 损坏而断开的概率是 $p_i$（$0 \le p_i \le 1$），因为电路太复杂，yyy 请你帮忙算出电路断路的概率。

电路连接方式：

- 一个元件是最小的电路，用 $A$ 表示元件 $1$，$B$ 表示元件 $2$，以此类推。

- $K$ 个电路组成的串联电路表示为电路 $1,2,\dots,K$。

- $K$ 个电路组成的并联电路表示为（电路 $1$）（电路 $2$）......（电路 $K$）。
## 输入格式

第 $1$ 行是一个整数 $n$，表示一共有多少个元件；

第 $2$ 行是表示电路的字符串；

最后是 $n$ 行，每行是一个实数 $p_i$，表示元件 $i$ 断路的概率。
## 输出格式

一个实数，表示整个电路断路的概率，精确到小数点后 $4$ 位。
## 样例

### 样例输入 #1
```
5                            
(A,B)((C)(D),E)
0.2
0.3
0.4
0.5
0.6
```
### 样例输出 #1
```
0.2992
```


---

---
title: "[HAOI2006] 均分数据"
layout: "post"
diff: 提高+/省选-
pid: P2503
tag: ['模拟', '贪心', '2006', '河南', '各省省选', '模拟退火']
---
# [HAOI2006] 均分数据
## 题目描述

已知 $n$ 个正整数 $a_1,a_2 ... a_n$ 。今要将它们分成 $m$ 组，使得各组数据的数值和最平均，即各组数字之和的均方差最小。均方差公式如下：

$$\sigma = \sqrt{\frac 1m \sum\limits_{i=1}^m(\overline x - x_i)^2},\overline x = \frac 1m \sum\limits_{i=1}^m x_i$$

其中 $\sigma$ 为均方差，$\bar{x}$ 为各组数据和的平均值，$x_i$ 为第 $i$ 组数据的数值和。
## 输入格式

第一行是两个整数，表示 $n,m$ 的值（ $n$ 是整数个数，$m$ 是要分成的组数）

第二行有 $n$ 个整数，表示 $a_1,a_2 ... a_n$。整数的范围是 $[1,50]$。

（同一行的整数间用空格分开）

## 输出格式

输出一行一个实数，表示最小均方差的值(保留小数点后两位数字)。

## 样例

### 样例输入 #1
```
6 3
1 2 3 4 5 6

```
### 样例输出 #1
```
0.00
```
## 提示

样例解释：$1,6$、$2,5$、$3,4$ 分别为一组

【数据规模】

对于 $40\%$ 的数据，保证有 $m \le n \le 10$，$2 \le m \le 6$

对于 $100\%$ 的数据，保证有 $m \le n \le 20$，$2 \le m \le 6$



---

---
title: "函数"
layout: "post"
diff: 提高+/省选-
pid: P2582
tag: ['模拟']
---
# 函数
## 题目背景

Alice 和 Bob 玩游戏。
## 题目描述

Alice 给出一个 $1$~$n$ 的排列表示一个函数 $y=f(x)$，即给出的第 $i$ 个数字即为 $f(i)$。  

现在 Bob 需要给出一个字典序尽可能小的函数 $y=g(x)$，使得对于任意 $i$，$f(g(i))=g(f(i))$。
## 输入格式

第一行一个整数 $n$。  

第二行 $n$ 个整数，依次表示 $f(1),f(2) \cdots f(n)$。
## 输出格式

共一行，$n$ 个整数，依次表示 $g(1),g(2) \cdots g(n)$。
## 样例

### 样例输入 #1
```
5
1 2 3 4 5
```
### 样例输出 #1
```
1 1 1 1 1
```
### 样例输入 #2
```
5
2 3 4 5 1
```
### 样例输出 #2
```
1 2 3 4 5
```
## 提示

#### 【样例解释】
#### 样例 1 说明
- $g(f(1))=f(g(1))=1$。
- $g(f(2))=f(g(2))=1$。
- $g(f(3))=f(g(3))=1$。
- $g(f(4))=f(g(4))=1$。
- $g(f(5))=f(g(5))=1$。

#### 样例 2 说明
- $g(f(1))=f(g(1))=2$。
- $g(f(2))=f(g(2))=3$。
- $g(f(3))=f(g(3))=4$。
- $g(f(4))=f(g(4))=5$。
- $g(f(5))=f(g(5))=1$。

---

#### 【数据规模与约定】
对于 $30\%$ 的数据，$n \le 5$。
对于 $60\%$ 的数据，$n \le 10^3$。
对于 $100\%$ 的数据，$1 \le n \le 8 \times 10^5$。


---

---
title: "美丽的序列"
layout: "post"
diff: 提高+/省选-
pid: P2659
tag: ['模拟', '洛谷原创']
---
# 美丽的序列
## 题目背景

GD是一个热衷于寻求美好事物的人，一天他拿到了一个美丽的序列。

## 题目描述

为了研究这个序列的美丽程度，GD定义了一个序列的“美丽度”和“美丽系数”：对于这个序列的任意一个区间[l，r]，这个区间的“美丽度”就是这个区间的长度与这个区间的最小值的乘积，而整个序列的“美丽系数”就是它的所有区间的“美丽度”的最大值。现在GD想要你帮忙计算这个序列的“美丽系数”。

## 输入格式

第一行一个整数n，代表序列中的元素个数。 第二行n个整数a1、a2„an，描述这个序列。

## 输出格式

一行一个整数，代表这个序列的“美丽系数”。

## 样例

### 样例输入 #1
```
3 

1 2 3
```
### 样例输出 #1
```
4
```
## 提示

样例解释 选取区间［2，3］，可以获得最大“美丽系数”为2\*2=4。 数据范围 对于20%的数据，n<=2000； 对于60%的数据，n<=200000； 对于100%的数据，1<=n<=2000000，0<=ai<=2000000。 提示 你可能需要一个读入优化。



---

---
title: "[AHOI2016初中组] 黑白序列"
layout: "post"
diff: 提高+/省选-
pid: P2779
tag: ['模拟', '2016', '线段树', '安徽']
---
# [AHOI2016初中组] 黑白序列
## 题目背景

小可可知道小雪喜欢什么样子的黑白序列。
## 题目描述

首先，对于任何正整数 $n$，如果一个黑白序列是由连续 $n$ 个黑接上连续 $n$ 个白，那一定是小雪喜欢的黑白序列。

其次，如果有两个黑白序列小雪都喜欢，那么把这两个序列接起来得到的新序列，小雪也一定喜欢。小雪不会喜欢更多别的黑白序列。

例如，如果用字符 `B` 和 `W` 分别表示黑色，`W` 表示白色，那么 `BW`，`BBWW`，`BBBWWW` 以及 `BWBW`，`BWBBWW`，`BWBBWWBW` 都是小雪喜欢的黑白序列。而 `W`，`WW`，`WB`，`WBBW` 以及 `BBBWW` 都不是小雪喜欢的黑白序列。

现在小可可准备了一个未完成的黑白序列，用 `B` 和 `W` 表示黑色和白色，用 `?` 表示尚未确定，他希望知道一共有多少种不同的方法，在决定了每一个 `?` 位置的颜色后可以得到一个小雪喜欢的黑白序列。

两个方案若有至少一位不同才能算是不同的，不是 `?` 的位置是不允许修改的。

答案对 $10^9 + 9$（一个素数）取模。






## 输入格式

第一行输入一个长度大于零的字符串，由 `B`，`W` 和 `?` 组成。

## 输出格式

输出一个整数，表示答案。
## 样例

### 样例输入 #1
```
B?B?????
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
??BB????W???BB??????
```
### 样例输出 #2
```
26
```
### 样例输入 #3
```
????????B???????????W??B?????W????????????????????W????????W
```
### 样例输出 #3
```
10058904
```
## 提示

#### 样例输入输出 1 解释
有六种合法方案，依次得到的最终黑白序列为： 

- `BBBBWWWW`，
- `BBBWWWBW`，
- `BWBBBWWW`，
- `BWBBWWBW`，
- `BWBWBBWW`，
- `BWBWBWBW`。

#### 数据规模与约定

- 对于 $20\%$ 的数据，输入长度不超过 $22$。
- 对于 $60\%$ 的数据，输入长度不超过 $5000$。
- 对于 $100\%$ 的数据，输入长度不超过 $500000$，保证序列中只含 `W`，`B`，`?` 三种字符，其中 `?` 是英文字符。


---

---
title: "教主的魔法"
layout: "post"
diff: 提高+/省选-
pid: P2801
tag: ['模拟', '分块']
---
# 教主的魔法
## 题目描述

教主最近学会了一种神奇的魔法，能够使人长高。于是他准备演示给 XMYZ 信息组每个英雄看。于是 $N$ 个英雄们又一次聚集在了一起，这次他们排成了一列，被编号为 $1, 2, \ldots, N$。


每个人的身高一开始都是不超过 $1000$ 的正整数。教主的魔法每次可以把闭区间 $[L, R]$（$1≤L≤R≤N$）内的英雄的身高全部加上一个整数 $W$。（虽然 $L=R$ 时并不符合区间的书写规范，但我们可以认为是单独增加第 $L(R)$ 个英雄的身高）


CYZ、光哥和 ZJQ 等人不信教主的邪，于是他们有时候会问 WD 闭区间 $[L, R]$ 内有多少英雄身高大于等于 $C$，以验证教主的魔法是否真的有效。


WD 巨懒，于是他把这个回答的任务交给了你。

## 输入格式

第 $1$ 行为两个整数 $N, Q$。$Q$ 为问题数与教主的施法数总和。

第 $2$ 行有 $N$ 个正整数，第 $i$ 个数代表第 $i$ 个英雄的身高。


第 $3$ 到第 $Q+2$ 行每行有一个操作：


1. 若第一个字母为 `M`，则紧接着有三个数字 $L, R, W$。表示对闭区间 $[L, R]$ 内所有英雄的身高加上 $W$。

2. 若第一个字母为 `A`，则紧接着有三个数字 $L, R, C$。询问闭区间 $[L, R]$ 内有多少英雄的身高大于等于 $C$。

## 输出格式

对每个 `A` 询问输出一行，仅含一个整数，表示闭区间 $[L, R]$ 内身高大于等于 $C$ 的英雄数。

## 样例

### 样例输入 #1
```
5 3
1 2 3 4 5
A 1 5 4
M 3 5 1
A 1 5 4
```
### 样例输出 #1
```
2
3

```
## 提示

【输入输出样例说明】

原先 $5$ 个英雄身高为 $1, 2, 3, 4, 5$，此时 $[1, 5]$ 间有 $2$ 个英雄的身高大于等于 $4$。教主施法后变为 $1, 2, 4, 5, 6$，此时 $[1, 5]$ 间有 $3$ 个英雄的身高大于等于 $4$。

【数据范围】

对于 $30\%$ 的数据，$N≤1000$，$Q≤1000$。

对于 $100\%$ 的数据，$N≤10^6$，$Q≤3000$，$1≤W≤1000$，$1≤C≤10^9$。

---

$\text{upd 2022.8.18}$：新增加一组 Hack 数据。  
$\text{upd 2023.8.16}$：新增加一组 [Hack 数据](https://www.luogu.com.cn/discuss/661585)。


---

---
title: "[USACO11FEB] The Lost Cows G"
layout: "post"
diff: 提高+/省选-
pid: P3013
tag: ['模拟', '字符串', '2011', 'USACO', 'Special Judge', '深度优先搜索 DFS']
---
# [USACO11FEB] The Lost Cows G
## 题目描述

One sunny day farmer John was kidnapped by evil farmer Marcus's cows. FJ wasn't too concerned about his forced holiday but wanted to make sure that his cows got home safely together.

The cows are spread out in every one of FJ's N (3 <= N <= 200) pastures conveniently numbered 1..N. The barn is located at pasture 1. The farm has an interesting navigation system: at every pasture i there are M (1 <= M <= 200) signs S\_ij (1 <= S\_ij <= N) which one could reference as S\_i1..S\_iM; each sign points the way to a pasture. Sometimes a sign points to a path that leads back to the same

pasture.

Farmer Marcus's cows allow FJ to write a single message to all of his cows. FJ's plan is to write a list of sign numbers such that any cow who follows those instructions will all arrive at the barn when each cow has completed all the instructions.

When a cow starts at a given pasture then she will first follow the path indicated by the first sign number on FJ's list. When she arrives at the second pasture, she looks at the second sign of FJ's list and follows the path marked by that sign. She continues until she exhausts the instruction list, at which point she should be at the barn.

Find a list of instructions containing no more than 5,000,000 sign numbers that will guide every cow, from every pasture, to the barn after all instructions are followed.  It is guaranteed that such a list exists.

Consider a set of three signs in four pastures that direct the cows like these do:

```cpp
** Pasture# ** 
1    2    3    4 
Sign 1   4    4    1    3 
Sign 2   1    3    2    4 
Sign 3   4    2    3    1 
```
The set of instructions below will direct cows to the barn from any of the four pastures:

```cpp
Instruction#   Sign#            Instruction#   Sign# 
1           1                   5           3 
2           2                   6           1 
3           1                   7           3 
4           2 
```
The cow in pasture 1 will read sign #1 at time 1 and be directed to pasture 4.  At time 2, she is in pasture 4 and (per FJ's

instructions) read sign #2 and then be directed to pasture 4. Below is a table that shows the cow's travels:

```cpp
* * * *  Cow in pasture  1  * * * * 
Time    CurrentPasture#    WhichSign     Sign->Nextpasture 
1            1               1                4 
2            4               2                4 (same pasture!) 
3            4               1                3 
4            3               2                2 
5            2               3                2 (same pasture)
6            2               1                4 
7            4               3                1 Barn! 
```
Similarly: Pasture 2's cow visits pastures [2]-4-4-3-2-2-4-1. Pasture 3's cow visits pastures [3]-1-1-4-4-1-4-1.

Pasture 4's cow visits pastures [4]-3-2-4-4-1-4-1.


Given a set of signs, create a set of instructions. 

## 输入格式

\* Line 1: Two space separated integers: N and M

\* Lines 2..M+1: Line i+1 describes the contents of each pasture's N signs with N integers: S\_1i..S\_Ni

## 输出格式

\* Lines 1..?: The sign numbers the cows should follow, one per line.

## 样例

### 样例输入 #1
```
4 3 
4 4 1 3 
1 3 2 4 
4 2 3 1 

```
### 样例输出 #1
```
1 
2 
1 
2 
3 
1 
3 

```
## 题目翻译

### 题目描述

给定一张 $n(3\leq n\leq 200)$ 个点的图，每个点都恰好有 $m(1\leq m\leq 200)$ 条出边，第 $i$ 个点的第 $j$ 条出边指向 $a_{i,j}$。

现在这张图上每个点都有一头牛。每次你可以报出一个数 $x(1\leq x\leq m)$，这会使得每一头牛沿着当前所在的点的第 $x$ 条边走一步（即当前在点 $u$ 的牛移动到点 $a_{u,x}$）。

你需要发出不超过 $5\times 10^6$ 条指令，使得在所有的指令执行完后，所有的牛都在编号为 $1$ 的点上。

### 输入格式

第一行两个整数 $n,m$。

接下来 $m$ 行每行 $n$ 个整数，第 $i$ 行的第 $j$ 个整数是 $a_{j,i}$。

### 输出格式

在第 $i$ 行输出你发出的第 $i$ 条指令。


---

---
title: "[USACO14DEC] Guard Mark G"
layout: "post"
diff: 提高+/省选-
pid: P3112
tag: ['模拟', '贪心', '2014', 'USACO', '状压 DP']
---
# [USACO14DEC] Guard Mark G
## 题目描述

 Farmer John and his herd are playing frisbee.  Bessie throws thefrisbee down the field, but it's going straight to Mark the field handon the other team!  Mark has height H (1 <= H <= 1,000,000,000), butthere are N cows on Bessie's team gathered around Mark (2 <= N <= 20).They can only catch the frisbee if they can stack up to be at least ashigh as Mark.  Each of the N cows has a height, weight, and strength.A cow's strength indicates the maximum amount of total weight of thecows that can be stacked above her. 
 
 Given these constraints, Bessie wants to know if it is possible forher team to build a tall enough stack to catch the frisbee, and if so,what is the maximum safety factor of such a stack.  The safety factorof a stack is the amount of weight that can be added to the top of thestack without exceeding any cow's strength.



## 输入格式

INPUT: (file guard.in) 

The first line of input contains N and H.

The next N lines of input each describe a cow, giving its height,weight, and strength.  All are positive integers at most 1 billion.

 
## 输出格式

OUTPUT: (file guard.out) 

 If Bessie's team can build a stack tall enough to catch the frisbee, please output the maximum achievable safety factor for such a stack. 

Otherwise output "Mark is too tall" (without the quotes). 


## 样例

### 样例输入 #1
```
4 10 
9 4 1 
3 3 5 
5 5 10 
4 4 5 
```
### 样例输出 #1
```
2 
```
## 题目翻译

FJ将飞盘抛向身高为H(1 <= H <= 1,000,000,000)的Mark，但是Mark被N(2 <= N <= 20)头牛包围。牛们可以叠成一个牛塔，如果叠好后的高度大于或者等于Mark的高度，那牛们将抢到飞盘。

每头牛都一个身高，体重和耐力值三个指标。耐力指的是一头牛最大能承受的叠在他上方的牛的重量和。请计算牛们是否能够抢到飞盘。若是可以，请计算牛塔的最大稳定强度，稳定强度是指，在每头牛的耐力都可以承受的前提下，还能够在牛塔最上方添加的最大重量。




---

---
title: "[USACO14DEC] Marathon G"
layout: "post"
diff: 提高+/省选-
pid: P3113
tag: ['模拟', '动态规划 DP', '2014', 'USACO', '枚举']
---
# [USACO14DEC] Marathon G
## 题目背景

作为一名狂热的马拉松长跑运动员，贝茜喜欢为她的同伴们开设马拉松课程。她最近设计了一个有N个检查点的路线(1 < = N < = 100,000)，必须按顺序经过。


不幸的是，贝茜意识到其他的奶牛可能没有足够的耐力跑完全程。因此，她想知道特定的子路线需要多长时间才能跑完，其中的子路线是从完整路线的检查点中截取的的连续子序列。让事情变得更复杂的是，贝西知道其他的牛十分懒惰，可能会选择在任何时候跳过一个检查点——无论哪一种方法都能在最短的时间内完成。然而，他们不允许在子路线中跳过第一个或最后一个检查点。


为了建造最好的马拉松赛道，贝茜想要研究一下在她目前的课程中对检查点位置做出改变后可能造成的后果。请帮助她确定检查点位置的哪些更改将会影响运行不同子路线所需的时间(考虑到奶牛可能会选择在子路线跑步时忽略一个检查点)。

由于该课程设置在市中心的街道网络中，两个检查点之间的距离(x1,y1)和(x2,y2)是由| x1 - x2 | + | y1 - y2 |得出的。

## 题目描述

An avid marathon runner herself, Bessie enjoys creating marathon courses for her fellow cows to run.  She has most recently designed a route specified by N checkpoints (1 <= N <= 100,000) that must be visited in sequence.


Unfortunately, Bessie realizes that the other cows may not have the stamina to run the full route. She therefore wants to know how long certain sub-routes take to run, where a sub-route is a contiguous subsequence of the checkpoints from the full route.  To make matters more complicated, Bessie knows that the other cows, being lazy, might choose to skip one checkpoint any time they run a sub-route -- whichever one results in a minimum total travel time.  They are not allowed to skip the first or last checkpoints in a sub-route, however.

 
In order to build the best possible marathon course, Bessie wants to investigate the ramifications of making changes to the checkpoint locations in her current course.  Please help her determine how certain changes to checkpoint locations will affect the time required to run different sub-routes (taking into account that the cows might choose to omit one checkpoint any time they run a sub-route).

 
Since the course is set in a downtown area with a grid of streets, the distance between two checkpoints at locations (x1, y1) and (x2, y2) is given by |x1-x2| + |y1-y2|. 
## 输入格式


INPUT: (file marathon.in) 

The first line gives N and Q (1 <= Q <= 100,000). 

The next N lines contain (x, y) locations of N checkpoints in the 

sequence they must be visited along the route.  All coordinates are in the range -1000 .. 1000.


The next Q lines consist of updates and queries, one per line, to be processed in the order they are given. Lines will either take the form "U I X Y" or "Q I J".  A line of the form "U I X Y" indicates that the location of checkpoint I (1 <= I <= N) is to be changed to location (X, Y).  A line of the form "Q I J" asks for the minimum travel time of the sub-route from checkpoint I to checkpoint J (I <= J), given that the cows choose to skip one checkpoint along this sub-route (but not the endpoints I and J).


## 输出格式

 
OUTPUT: (file marathon.out) 

For each sub-route length request, output on a single line the desired length. 


## 样例

### 样例输入 #1
```
5 5 
-4 4 
-5 -3 
-1 5 
-3 4 
0 5 
Q 1 5 
U 4 0 1 
U 4 -1 1 
Q 2 4 
Q 1 4 

```
### 样例输出 #1
```
11 
8 
8 

```


---

---
title: "[JLOI2013] 删除物品"
layout: "post"
diff: 提高+/省选-
pid: P3253
tag: ['模拟', '2013', '树状数组', '吉林', '栈']
---
# [JLOI2013] 删除物品
## 题目描述

箱子再分配问题需要解决如下问题：

1. 一共有 $N$ 个物品，堆成 $M$ 堆。

2. 所有物品都是一样的，但是它们有不同的优先级。

3. 你只能够移动某堆中位于顶端的物品。

4. 你可以把任意一堆中位于顶端的物品移动到其它某堆的顶端。若此物品是当前所有物品中优先级最高的，可以直接将之删除而不用移动。

5. 求出将所有物品删除所需的最小步数。删除操作不计入步数之中。

6. 这是一个比较难解决的问题，这里你只需要解决一个比较简单的版本：不会有两个物品有着相同的优先级，且 $M=2$。

## 输入格式

第一行是包含两个整数 $N_1$, $N_2$ 分别表示两堆物品的个数。接下来有 $N_1$ 行整数按照从顶到底的顺序分别给出了第一堆物品中的优先级，数字越大，优先级越高。再接下来的 $N_2$ 行按照同样的格式给出了第二堆物品的优先级。

## 输出格式

对于每个数据，请输出一个整数，即最小移动步数。

## 样例

### 样例输入 #1
```
3 3
1
4
5
2
7
3
```
### 样例输出 #1
```
6
```
## 提示

$1\leq N_1+N_2\leq 100000$



---

---
title: "[POI 2009] TAB-Arrays"
layout: "post"
diff: 提高+/省选-
pid: P3492
tag: ['模拟', '2009', 'POI（波兰）']
---
# [POI 2009] TAB-Arrays
## 题目描述

Let us consider an array of size ![](http://main.edu.pl/images/OI16/tab-en-tex.1.png) filled with pairwise different integers.

The following operations are allowed on the array:

interchanging two rows,              interchanging two columns.

We call two arrays alike if one of them can be obtained from the other by a sequence of aforementioned operations.

Write a programme that for a given set of pairs of arrays tells which pairs are alike.


## 输入格式

The first line of the standard input contains one integer ![](http://main.edu.pl/images/OI16/tab-en-tex.2.png) (![](http://main.edu.pl/images/OI16/tab-en-tex.3.png))   denoting the number of pairs of arrays.

Then descriptions of successive array pairs follow in subsequent lines.

Each description starts with a line holding two integers ![](http://main.edu.pl/images/OI16/tab-en-tex.4.png) and ![](http://main.edu.pl/images/OI16/tab-en-tex.5.png) (![](http://main.edu.pl/images/OI16/tab-en-tex.6.png)), separated by a single space, that denote the common number of rows and columns of the arrays, respectively.

The ![](http://main.edu.pl/images/OI16/tab-en-tex.7.png) lines that follow describe the first array.

In the ![](http://main.edu.pl/images/OI16/tab-en-tex.8.png)-th of them there are ![](http://main.edu.pl/images/OI16/tab-en-tex.9.png) integers ![](http://main.edu.pl/images/OI16/tab-en-tex.10.png) (![](http://main.edu.pl/images/OI16/tab-en-tex.11.png)), separated by single spaces…

## 输出格式

Your programme should print out ![](http://main.edu.pl/images/OI16/tab-en-tex.19.png) lines to the standard output.

The ![](http://main.edu.pl/images/OI16/tab-en-tex.20.png)-th of these should hold one word: "TAK" (yes in Polish) if the  arrays of the ![](http://main.edu.pl/images/OI16/tab-en-tex.21.png)-th pair are alike, or "NIE" (no in Polish) otherwise.

## 样例

### 样例输入 #1
```
2
4 3
1 2 3
4 5 6
7 8 9
10 11 12
11 10 12
8 7 9
5 4 6
2 1 3
2 2
1 2
3 4
5 6
7 8

```
### 样例输出 #1
```
TAK
NIE

```
## 题目翻译

多组数据（不超过 $10$ 组），每组数据给出两个 $n$ 行 $m$ 列的矩阵 ($n,m\leq 1000$)，保证每个矩阵内元素互不相同且权值均在 $[-10^6,10^6]$ 之间，你需要报告能否把其中一个矩阵通过若干次交换两行或者交换两列的操作变成另外一个矩阵。

单个读入数据可达 130MB 左右，请优化读入效率。


---

---
title: "[POI 2010] TES-Intelligence Test"
layout: "post"
diff: 提高+/省选-
pid: P3500
tag: ['模拟', '2010', '二分', 'POI（波兰）']
---
# [POI 2010] TES-Intelligence Test
## 题目描述

One of the tasks in the Byteotian Intelligence Test (BIT) is to cross out    numbers from an initial sequence in such a way that leaves as a result    certain given sequences.

Byteasar longs to become the IQ Master of Byteotia, but he is no good in    this kind of tasks.

But since practice makes perfect, he intends to practise a lot.

So much in fact that he asks you to write a program that will facilitate    the training by verifying his answers quickly.
## 输入格式

The first line of the standard input contains one integer $m$ ($1\le m\le 1\ 000\ 000$).

The second line holds $m$ integers $a_1,a_2,\cdots,a_m$ ($1\le a_i\le 1\ 000\ 000$ for $1\le i\le m$), separated by single spaces,      that constitute the initial sequence of the test.

The third line of the input holds one integer $n$.

The following $2n$ lines describe the sequences to be obtained by crossing out      numbers from the initial sequence.

Each sequence's description takes two successive lines.

The first of these two lines contains an integer $m_i$ ($1\le m_i\le 1\ 000\ 000$).

The second contains an $m_i$-element long sequence of integers $b_{i,1},b_{i,2},\cdots,b_{i,m_i}$($1\le b_{i,j}\le 1\ 000\ 000$ for $1\le j\le m_i$)separated by single spaces. You may assume that the total length on given $n$ sequences does not exceed $1\ 000\ 000$.
## 输出格式

Your program should print out $n$ lines to the standard output.

The $i$-th line (for $1\le i\le n$) should hold one word,      "TAK" (yes in Polish) if the $i$-th input sequence can be obtained by      crossing out (i.e., removing) some, not necessarily contiguous, numbers from the initial sequence,      or "NIE" (no in Polish) otherwise. Mind you, only the words should be printed,      no quotation marks. Of course, the order of the numbers left after crossing out is important,      as can be seen in the example.
## 样例

### 样例输入 #1
```
7
1 5 4 5 7 8 6
4
5
1 5 5 8 6
3
2 2 2
3
5 7 8
4
1 5 7 4
```
### 样例输出 #1
```
TAK
NIE
TAK
NIE
```
## 题目翻译

### 题目描述

**译自 POI 2010 Stage 1.「[Intelligence Test](https://szkopul.edu.pl/problemset/problem/Arkza0f7GKKb-m1YZJulnlMk/site/?key=statement)」**

给出一个母串 $a_1,a_2,a_3,\cdots ,a_n$ ，若干次询问，每次询问给出一个子串 $b_1,b_2,\cdots b_m$ ，请你求出这个子串是不是母串的子序列。

### 输入格式

第一行一个正整数 $n$ 。  
第二行 $n$ 个空格隔开的正整数 $a_1,a_2,\cdots ,a_n$ ，表示母串。  
第三行一个正整数 $q$ ，表示询问次数。  
接下来 $2 \times q$ 行，每两行表示一次询问，其中的第一行是一个正整数 $m$ ，第二行是 $m$ 个空格隔开的正整数表示 $b_1,b_2,\cdots ,b_m$ ，表示询问的子串。

### 输出格式

输出共 $q$ 行，每行一个字符串。  
若第 $i$ 次询问的串是母串的子序列，那么第 $i$ 行应为 ```TAK``` ，否则应为 ```NIE``` 。

对于 $100\%$ 的数据，有 $1\le n,m,a_i,b_i\le 1\ 000\ 000$ ，且 $\sum m\le 1\ 000\ 000$ ，这里 $\sum m$ 表示 $q$ 组询问的 $m$ 之和。

翻译来自于 [LibreOJ](https://loj.ac/p/2429)。


---

---
title: "[POI 2010] GRA-The Minima Game"
layout: "post"
diff: 提高+/省选-
pid: P3507
tag: ['模拟', '动态规划 DP', '贪心', '2010', 'POI（波兰）']
---
# [POI 2010] GRA-The Minima Game
## 题目描述

Alice and Bob learned the minima game, which they like very much, recently.

The rules of the game are as follows.

A certain number of cards lies on a table, each inscribed with a positive integer.

The players make alternate moves, Alice making the first one.

A move consists in picking an arbitrary positive number of cards from the table.

For such move the player receives a number of points equal to the minimum    of the numbers inscribed on the cards he collected.

The game ends when the last card is removed from the table.

The goal of each player is maximizing the difference between their and their opponent's score.

Alice and Bob have duly noted that there is an optimal strategy in the game.

Thus they are asking you to write a program that, for a given set of cards,    determines the outcome of the game when both players play optimally.
## 输入格式

In the first line of the standard input there is one integer ![](http://main.edu.pl/images/OI17/gra-en-tex.1.png) (![](http://main.edu.pl/images/OI17/gra-en-tex.2.png)) given,      denoting the number of cards.

The second line holds ![](http://main.edu.pl/images/OI17/gra-en-tex.3.png) positive integers ![](http://main.edu.pl/images/OI17/gra-en-tex.4.png) (![](http://main.edu.pl/images/OI17/gra-en-tex.5.png)),      separated by single spaces, that are inscribed on the cards.

## 输出格式

Your program should print out a single line with a single integer to the standard      output - the number of points by which Alice wins over Bob, assuming they both play optimally;      if it is Bob who has more points, the result should be negative.

## 样例

### 样例输入 #1
```
3
1 3 1
```
### 样例输出 #1
```
2
```
## 题目翻译

### 题目描述

**译自 POI 2010 Stage 3. Day 1「[The Minima Game](https://szkopul.edu.pl/problemset/problem/3buviDQZWLE83AxVhvJJurgU/site/?key=statement)」**

Alice 和 Bob 玩一个游戏。Alice 先手，两人轮流进行操作，每轮一个玩家可以选择若干张牌（至少一张），并获得相当于这些牌上所写数字的最小值的分数，直到没有牌为止。两人都希望自己的分数与对方分数之差最大。若两个玩家都使用最佳策略，求游戏的最终结果。

### 输入格式

第一行有一个整数 $n$，表示牌的数量。

接下来一行有 $n$ 个正整数 $k_1, k_2, ..., k_n$，表示牌上所写的数字。

### 输出格式

输出一行一个整数，表示最终 Alice 的分数与 Bob 分数之差。如果 Bob 的分数更多，你应该输出一个负数。

### 样例解释

Alice 先选择 $3$，得到 $3$ 分。Bob 拿走所有牌并得到 $1$ 分，游戏最后的比分为 $3:1$，因此 Alice 比 Bob 多两分。

### 数据范围

$1\le n\le 10^6$，$1\le k_i\le 10^9$。

翻译来自于 [LibreOJ](https://loj.ac/p/2455)。


---

---
title: "电阻网络"
layout: "post"
diff: 提高+/省选-
pid: P3617
tag: ['模拟', '贪心', '递归', '洛谷原创', '分治']
---
# 电阻网络
## 题目背景

什么是电阻?这个大家应该都知道。什么是电路?大家也应该知道。但是本题当中，电路的定义或许有点不同：

电路都带有正、负极接点，正极在左，负极在右。具体地：电路分为以下几类：

单独的一个1Ω电阻(及其两端的接点)是电路(虽然导线也可以被视为0Ω的电阻，但是单独的导线不是电路)

如果A和B都是电路，设1,2,3是从左到右的三个接点，那么将A的正负极分别接在1与2上，将B的正负极分别接在2与3上，那么1到3的部分是电路，其中1为正极，3为负极。

如果A和B都是电路,设1,2,3,2',3',1’是六个接点，其中1在2和3的左侧，2在2’的左侧，3在3’的左侧，2,和3,在1’的左侧，并且1与2，1与3，2’与1’，3’与1’间均连有导线, 那么将A的正负极分别接在2与2’上，将B的正负极分别接在3与3’上，那么1到1'的部分是电路，其中1为正极，1’为负极。

现在给出一个电路，求它正负极之间的电阻。

## 题目描述

Cjwssb最近在物理学科上遇到了难题，他不会计算一个电路中的总电阻，现在他找到了你，希望你能帮助他。

这个电路有如下限定

1、    电路只由导线以及电阻为一欧的电阻组成

2、    保证电路从左到右连接，即每个电阻或导线的两个连接点xy保证x<y

3、    保证接线柱1为电源正极，接线柱n为电源负极

4、    保证每个接线柱只会被串联或者并联两个分支电路或者不接任何电线或电阻

## 输入格式

第一行为两个正整数n,m,分别代表接点数和电阻数。保证编号小的接点在编号大的接点的左侧。

接下来m行，每行三个整数ai,bi,ci，代表这个电阻连接了ai与bi接点，其阻值为ci ，其中ci只可能是0或1，且对于任意的i，保证ai<bi。

## 输出格式

输出一个实数，表示总的电阻值，保留三位小数输出。

## 样例

### 样例输入 #1
```
7 7
1 2 0
1 3 0
2 4 1
3 5 1
4 6 0
5 6 0
6 7 1

```
### 样例输出 #1
```
1.500
```
## 提示

样例解释

画出图来，答案是显然的。

数据规模与约定

对于20%的数据n≤5,m≤5。

对于50%的数据n≤100,m≤120。

对于70%的数据n≤1,000,m≤1200。

对于100%的数据n≤100,000,m≤120000

数据是在人工指定的n下随机生成的，保证答案不会超过10.000。

By：saffah



---

---
title: "[CERC2016] 自由的套娃 Free Figurines"
layout: "post"
diff: 提高+/省选-
pid: P3682
tag: ['模拟', '2016']
---
# [CERC2016] 自由的套娃 Free Figurines
## 题目描述

俄罗斯套娃是一些尺寸递增的木制雕像，它们可以嵌套在一起。每个套娃可以放进一个更大的套娃，也可以被放入一个更小的套娃。每个套娃内部最多只能直接嵌套一个套娃，但是那个套娃内部还可以继续嵌套。


给定n个尺寸互不相同的套娃，按尺寸从小到大依次编号为1到n。如果套娃a被直接嵌入套娃b，那么我们称b是a的父亲，如果一个套娃没有父亲，那么我们称它是自由的。一组镶嵌方案可以用每个套娃的父亲来表示。


我们可以每步可以做以下两种操作中的任意一种：


1.把一个自由的套娃直接嵌入一个更大的没有被放入东西的套娃。


2.选择一个不自由的套娃，将其从其父亲中取出。


给定初始局面，请计算达到目标局面的最小的操作步数。

## 输入格式

第一行包含一个正整数n(1<=n<=100000)，表示套娃的个数。

第二行包含n个整数p\_1,p\_2,...,p\_n(0<=p\_i<=n)，依次表示初始局面中每个套娃的父亲，0表示自由套娃。

第三行包含n个整数q\_1,q\_2,...,q\_n(0<=q\_i<=n)，依次表示目标局面中每个套娃的父亲，0表示自由套娃。

输入数据保证初始局面和目标局面均合法。

## 输出格式

输出一行一个整数，即最小操作步数。

## 样例

### 样例输入 #1
```
7
3 5 4 0 7 0 0
3 5 0 6 7 0 0

```
### 样例输出 #1
```
2
```


---

---
title: "冰精冻西瓜"
layout: "post"
diff: 提高+/省选-
pid: P3787
tag: ['模拟', '线段树', '树状数组', '洛谷原创', 'Special Judge']
---
# 冰精冻西瓜
## 题目背景

 ![](https://cdn.luogu.com.cn/upload/pic/5279.png) 

盛夏，冰之妖精琪露诺发现了一大片西瓜地，终于可以吃到美味的冻西瓜啦。

## 题目描述

琪露诺是拥有操纵冷气程度的能力的妖精，一天她发现了一片西瓜地。这里有 $n$ 个西瓜，由 $n-1$ 条西瓜蔓连接，形成一个有根树，琪露诺想要把它们冷冻起来慢慢吃。

这些西瓜蔓具有神奇的性质，可以将经过它的冷气的寒冷程度放大或缩小，每条西瓜蔓放大/缩小冷气寒冷程度的能力值为 $w_i$，表示冷气经过它后，寒冷程度值 $x$ 会变为 $ x\times w_i$。每个西瓜也有一个寒冷程度值，炎热的夏日，所有西瓜的寒冷程度值初始都为 $0$。

琪露诺会做出两种动作:

①.对着西瓜 $i$ 放出寒冷程度为 $x$ 的冷气。这股冷气顺着西瓜蔓向“西瓜树”的叶子节点蔓延，冷气的寒冷程度会按照上面的规则变化。遇到一个西瓜连了多条西瓜蔓时，每条叶子节点方向的西瓜蔓均会获得与原先寒冷程度相等的冷气。途径的所有西瓜的寒冷程度值都会加上冷气的寒冷程度值。

**冷气只会向释放点的子树蔓延，不会向根方向蔓延**

⑨.向你询问西瓜 $i$ 的寒冷程度值是多少。

等等，为什么会有⑨？因为笨蛋琪露诺自己也会忘记放了多少冰呢。

所以，帮她计算的任务就这么交给你啦。

## 输入格式

第一行一个整数 $n$，表示西瓜的数量。

西瓜编号为 $1\sim n$，$1$ 为这棵“西瓜树”的根。

接下来 $n-1$ 行，每行有两个整数 $u$、$v$ 和一个实数 $w$，表示西瓜 $u$ 和西瓜 $v$ 之间连接有一条藤蔓，它放大/缩小冷气寒冷程度的能力值为 $w$。

接下来一行一个整数 $m$，表示操作的数量。

接下来 $m$ 行，每行两个或三个整数。

第一个数只能是 $1$ 或 $9$。

如果为 $1$，接下来一个整数 $i$ 和一个实数 $x$，表示对西瓜 $i$ 放出寒冷程度为 $x$ 的冷气。

如果为 $9$，接下来一个整数 $i$，表示询问编号为 $i$ 的西瓜的寒冷程度值。

## 输出格式

对于每个操作⑨，输出一行一个实数，表示对应西瓜的寒冷程度值。

## 样例

### 样例输入 #1
```
4
1 2 1.00000000
2 3 0.00000000
3 4 1.00000101
9
1 1 3.00000000
9 2
9 3
1 2 1.42856031
9 4
9 2
1 3 4.23333333
9 2
9 4
```
### 样例输出 #1
```
3.00000000
0.00000000
0.00000000
4.42856031
4.42856031
4.23333761
```
## 提示

子任务可能出现如下的特殊性质:

“西瓜树”退化为一条链

输入数据中的实数均保留8位小数，选手的答案被判作正确当且仅当输出与标准答案误差不超过10^-7。请特别注意浮点数精度问题。

 ![](https://cdn.luogu.com.cn/upload/pic/5278.png) 

实际数据中，冷气的寒冷程度x的范围为 [-0.1,0.1]

(样例中的冷气寒冷程度的范围为[1,5])

命题人:orangebird,鸣谢oscar。



---

---
title: "妖梦斩木棒"
layout: "post"
diff: 提高+/省选-
pid: P3797
tag: ['模拟', '线段树', '洛谷原创']
---
# 妖梦斩木棒
## 题目背景

 ![](https://cdn.luogu.com.cn/upload/pic/5848.png) 

妖梦是住在白玉楼的半人半灵，拥有使用剑术程度的能力。

## 题目描述

有一天，妖梦正在练习剑术。地面上摆放了一支非常长的木棒，妖梦把它们切成了等长的n段。现在这个木棒可以看做由三种小段构成，中间的n-2段都是左右都被切断的断头，我们记做’X’，最左边的一段和最右边的一段各有一个圆头，记做’（‘和’）’。幽幽子吃饱后闲来无事，决定戏弄一下妖梦。她拿来了许多这样的三种小段木棒，来替换掉妖梦切下来的n段中的一部分，然后问妖梦一些问题。这些操作可以这样描述:

1 x C 将第x个小段的木棒替换成C型，C只会是’X’,’(‘,’)’中的一种

2 l r 询问妖梦从第l段到第r段之间(含l,r)，有多少个完整的木棒

完整的木棒左右两端必须分别为’(‘和’)’，并且中间要么什么都没有，要么只能有’X’。

虽然妖梦能够数清楚这些问题，但幽幽子觉得她回答得太慢了，你能教给妖梦一个更快的办法吗？

## 输入格式

第一行两个整数n，m，n表示共有n段木棒，m表示有m次操作。

木棒的初始形状为(XXXXXX......XXXXXX)。

接下来m行，每行三个整数/字符，用空格隔开。第一个整数为1或2，表示操作的类型，若类型为1，则接下来一个整数x，一个字符C。若类型为2，接下来两个整数l,r。含义见题目描述。

## 输出格式

对于每一个操作2，输出一行一个整数，表示对应询问的答案。

## 样例

### 样例输入 #1
```
4 4
2 1 4
2 2 4
1 2 (
2 2 4
```
### 样例输出 #1
```
1
0
1
```
## 提示

对于30%的数据，2<=n,m<=1000。

对于100%的数据，2<=n,m<=200000。

by-orangebird



---

---
title: "[TJOI2010] 分金币"
layout: "post"
diff: 提高+/省选-
pid: P3878
tag: ['2010', '各省省选', 'O2优化', '模拟退火', '进制', '天津']
---
# [TJOI2010] 分金币
## 题目描述

现在有 $n$ 枚金币，它们可能会有不同的价值，第 $i$ 枚金币的价值为 $v_i$。

现在要把它们分成两部分，要求这两部分金币数目之差不超过 $1$，问这样分成的两部分金币的价值之差最小是多少？


## 输入格式

**本题单个测试点内有多组测试数据**。

输入的第一行是一个正整数 $T$，表示该测试点内数据组数。

对于每组测试数据的格式为：

每组测试数据占两行。

第一行是一个整数 $n$，表示金币的个数。

第二行有 $n$ 个整数，第 $i$ 个整数表示第 $i$ 个金币的价值 $v_i$。
## 输出格式

对于每组数据输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
3
2 2 4
4
1 2 3 6

```
### 样例输出 #1
```
0
2

```
## 提示

#### 数据规模与约定

- 对 $30\%$ 的数据，保证 $1 \leq v_i \leq 1000$
- 对于 $100\%$ 的数据，保证 $1 \leq T \leq 20$，$1 \leq n \leq 30$，$1 \leq v_i \leq 2^{30}$。


---

---
title: "三体问题【std 疑似有误】"
layout: "post"
diff: 提高+/省选-
pid: P3945
tag: ['模拟', 'Special Judge', '向量']
---
# 三体问题【std 疑似有误】
## 题目背景

@FirstLight0521 出题人在这里哦~

三体人所居住的星系由于三体运动的不确定性而导致三体星人生活动荡不安，善良的人类程序员（也就是你了！伟大的英雄！）决定帮助愚蠢得连程序都不会写的三体星人模拟天体的运动轨迹。这时，无聊的“歌者”文明决定戏弄一下你，于是给三体星系添加了一些新的星体。

## 题目描述

输入 $N$ 个天体与他们在空间中的坐标 $(x_i,y_i,z_i)$、初速度 $(v_x,v_y,v_z)$ 与质量 $M_i$，已知三体世界受到“歌者”影响时间的流动不是连续的（每 $0.01$ 秒钟刷新一次），天体均视为质点，求 $t$ 时刻所有天体的坐标。

本题万有引力常数 $G$ 取 $6.67408 \times 10^{-11}$，在代码中可以写成：

```cpp
#define G 6.67408e-11
```

当你的答案与标准答案的相对误差不超过 $0.5 \%$ 的时候，你在本测试点得到 AC。也就是说，保留多少位小数你可以自行确定。标准答案将会保留 $12$ 位小数。本题开启 SPJ 判断你的答案是否正确。

## 输入格式

第一行一个正整数 $N$ 和一个非负实数 $t$，分别表示天体数与时刻。

接下来 $N$ 行，每行 $7$ 个实数 $x_i,y_i,z_i,M_i,v_x,v_y,v_z$，分别表示各天体坐标、质量与初速度（三个方向上的分速度）。

## 输出格式

$N$ 行，每行为第 $i$ 个天体在 $t$ 时刻的坐标 $x_i,y_i,z_i$，以单个空格隔开。

## 样例

### 样例输入 #1
```
3 100
0 10 0 10000000 0.006207480877613 0 0
8.660254037844 -5 0 10000000 -0.003103740438807 -0.00537583613352 0
-8.660254037844 -5 0 10000000 -0.003103740438807 0.00537583613352 0
```
### 样例输出 #1
```
0.620349511786 9.980741705470 0.000000000000
8.333401109655 -5.527609289167 0.000000000000
-8.953750621441 -4.453132416303 0.000000000000
```
### 样例输入 #2
```
3 100
0 10 0 10000000 0.06207480877613 0 0
8.760254037844 -5 0 10000000 -0.03103740438807 -0.0537583613352 0
-8.660254037844 -5 0 10000000 -0.03103740438807 0.0537583613352 0
```
### 样例输出 #2
```
6.204092324054 9.982347016794 0.000000000000
5.642963405596 -10.364100727695 0.000000000000
-11.747055729651 0.381753710901 0.000000000000
```
## 提示

$3 \le N \le 30,0 \le t \le 100,-100 \le x_i,y_i,z_i \le 100$。$M_i$ 在 `long long` 范围内。


---

---
title: "[JSOI2008] 球形空间产生器"
layout: "post"
diff: 提高+/省选-
pid: P4035
tag: ['2008', '各省省选', '江苏', '模拟退火', '高斯消元', '构造']
---
# [JSOI2008] 球形空间产生器
## 题目描述

有一个球形空间产生器能够在 $n$ 维空间中产生一个坚硬的球体。现在，你被困在了这个 $n$ 维球体中，你只知道球面上 $n+1$ 个点的坐标，你需要以最快的速度确定这个 $n$ 维球体的球心坐标，以便于摧毁这个球形空间产生器。
## 输入格式

第一行是一个整数 $n$ $(1\le N\le 10)$。接下来的 $n+1$ 行，每行有 $n$ 个实数，表示球面上一点的 $n$ 维坐标。每一个实数精确到小数点后 $6$ 位，且其绝对值都不超过 $20000$。
## 输出格式

有且只有一行，依次给出球心的 $n$ 维坐标（ $n$ 个实数），两个实数之间用一个空格隔开。每个实数精确到小数点后 $3$ 位。数据保证有解。你的答案必须和标准输出一模一样才能够得分。
## 样例

### 样例输入 #1
```
2
0.0 0.0
-1.0 1.0
1.0 0.0
```
### 样例输出 #1
```
0.500 1.500
```
## 提示

提示：给出两个定义：

1. 球心：到球面上任意一点距离都相等的点。
2. 距离：设两个 $n$ 维空间上的点 $A,B$ 的坐标为 $(a_1, a_2, \cdots , a_n), (b_1, b_2, \cdots , b_n)$，则 $A,B$ 的距离定义为：$dist = \sqrt{ (a_1-b_1)^2 + (a_2-b_2)^2 + \cdots + (a_n-b_n)^2 }$。



---

---
title: "[HEOI2014] 南园满地堆轻絮"
layout: "post"
diff: 提高+/省选-
pid: P4105
tag: ['模拟', '贪心', '2014', '二分', '各省省选', '河北']
---
# [HEOI2014] 南园满地堆轻絮
## 题目描述

小 Z 是 ZRP（Zombies’ Republic of Poetry，僵尸诗歌共和国）的一名诗歌爱好者，最近 他研究起了诗词音律的问题。

在过去，诗词是需要编成曲子唱出来的，比如下面这首《菩萨蛮》，唱出来的话其对应的音符就是这样的：

```cpp
 南  园  满 地 堆 轻 絮， 愁 闻 一 霎 清 明 雨   
 1   1  5 5 6 6 5  4 4 3 3 2 2 1  
```
因而可以发现，`1 1 5 5 6 6 5 4 4 3 3 2 2 1`这串音符就成为了研究音律的关键。

小 Z 翻阅了众多史料发现，过去的一首曲子的音调是不下降的。 小 Z 想要知道对于一首给定的曲子，如何通过提高音调或者降低音调，将它的音调修改的不下降，而且使得修改幅度最大的那个音符的修改幅度尽量小。即如果把一个包含 $n$ 个音 符的曲子看做是一个正整数数列 $A[1] \cdots A[n]$，那么目标是求另一个正整数数列 $B[1]…B[n]$， 使得对于任意的 $1≤i<n$ 有 $B[i] ≤B[i+1]$，而且使得 $Ans = Max\{|A[j]-B[j]|,1≤j≤n\}$尽量 小。
小 Z 很快就想清楚了做法，但是鉴于他还忙着写诗，所以这个任务就交给了你。

## 输入格式

由于数据规模可能较大，因此采用如下方式生成数据。

每个数据包含 7 个数：$n,S_a,S_b,S_c,S_d,A[1],Mod$，即共有 n 个音符，第一个音符为 A[1]。

生成规则如下： 定义生成函数 $F(x) = S_a*x^3 + S_b*x^2 + S_c*x + S_d$; 那么给出递推公式 $A[i] =( F(A[i-1]) + F(A[i-2]) )\%mod$，此处规定 $A[0] = 0$. 由于中间过程的数可能会特别大，所以要求每一步与 $A$ 中的每个数都对一个给定的数 $Mod$ 取模。

## 输出格式

输出一行，包含一个正整数 $Ans$。

## 样例

### 样例输入 #1
```
3 815 6901 3839 178 199 10007 
```
### 样例输出 #1
```
1334
```
## 提示

【数据范围】

对于 10% 的数据， $n≤3$

对于 20% 的数据,  $n≤10$

对于 30% 的数据,  $n≤100$

对于 50% 的数据,  $n≤1000$

对于 70% 的数据,  $n≤100000$

对于 100% 的数据, $n≤5000000$，$S_a,S_b,S_c,S_d,A[1] ≤10000$，$ Mod≤1000000007 $

【友情提示】

样例中生成的数列为：  199 4568 1901，此时将 4568 修改为 3234,1901 也修改为 3234 即可，代价为 1334。



---

---
title: "外太空旅行"
layout: "post"
diff: 提高+/省选-
pid: P4212
tag: ['模拟', '枚举', '随机化', '状压 DP']
---
# 外太空旅行
## 题目描述

在人类的触角伸向银河系的边缘之际，普通人上太空旅行已经变得稀松平常了。某理科试验班有 $n$ 个人，现在班主任要从中选出尽量多的人去参加一次太空旅行活动。
可是 $n$ 名同学并不是和平相处的。有的人，比如小 A 和小 B 整天狼狈为奸，是好朋友；但还有的人，比如（政治敏感）和（政治敏感）就水火不相容。这 $n$ 名同学，由于是理科生，都非常的理性，所以“朋友的朋友就是朋友”和“敌人的朋友就是敌人”这两句话对这些同学无效。换句话说，有可能小 A 和小 B 是朋友，小 B 和小 C 是朋友，但是小 A 和小 C 两人势如水火。  
任意两个人之间要不就是敌人，要不就是朋友。  
因为在太空船上发生人员斗殴事件是很恶劣也很危险的，因此选出来参加旅行活动的同学必须互相之间都是朋友。你的任务就是确定最多可以选多少人参加旅行。
## 输入格式

第一行一个整数 $n(1 \le n \le 50)$。所有的同学按照 $1 \sim n$ 编号。  
接下来若干行，每行两个用空格隔开的整数 $a, b(1 \le a,b \le n)$，表示 $a$ 和 $b$ 是朋友。
注意：如果一个数对 $(x,y)$（或者 $(y,x)$）没有在文件中出现，那么编号为 $x$ 和 $y$ 的两个同学就是敌人。
## 输出格式

一个数，即最多可以选多少人参加活动。
## 样例

### 样例输入 #1
```
4
1 2
2 3
3 1
1 4
```
### 样例输出 #1
```
3
```


---

---
title: "[COCI 2017/2018 #1] Deda"
layout: "post"
diff: 提高+/省选-
pid: P4422
tag: ['模拟', '2017', '线段树', 'COCI（克罗地亚）']
---
# [COCI 2017/2018 #1] Deda
## 题目描述

Little Marica is making up a ~~nonsensical~~ unusual fairy tale and is telling to her grandfather who keeps interrupting her and asking her ~~stupid~~ intriguing questions.

In Marica’s fairy tale, $N$ children, denoted with numbers from $1$ to $N$ by their age (from the youngest denoted with $1$, to the oldest denoted with $N$), embarked on a train ride. The train leaves from the station $0$ and stops in order at stations $1, 2, 3 \dots$ to infinity.

Each of the following Marica’s statements is of the form: “$At\  stop\ X, child\ A\ got\ out$”, where the order of these statements is completely arbitrary. In other words, it does not depend on the station order. Her grandfather sometimes asks a question of the form: “$\textit{ Based on the statements so far, of the children denoted with a number greater than or equal}\allowbreak\textit{ to B, who is the youngest child that rode for Y or less stops?}$” If at the moment the grandfather asks the question it hasn’t been said so far that a child is getting off the train, we assume that the child is riding for an infinite amount of stops.

Marica must give a correct answer to each of her grandfather’s questions, otherwise the grandfather will get mad and go to sleep. The answer must be correct in the moment when the grandfather asks the question, while it can change later given Marica’s new statements, but that doesn’t matter. Write a program that tracks Marica’s statements and answers her grandfather’s questions.
## 输入格式

The first line of input contains the positive integers $N$ and $Q$ $(2 \le N, Q \le 2 \times 10^{5})$, the number of children and the number of statements. Each of the following $Q$ lines describes:

- either Marica’s statement of the form `M X A`, where $M$ denotes Marica, and $X$ and $A$ are positive integers $(1 \le X \le 10^{9}, 1 \le A \le N)$ from the task,
- or her grandfather’s question of the form `D Y B`, where $D$ denotes the grandfather, and $Y$ and $B$ are positive integers $(1 \le Y \le 10^{9}, 1 \le B \le N)$ from the task.

All of Marica’s statements correspond to different children and at least one line in the input is her grandfather’s question.
## 输出格式

For each grandfather’s question, output the number of the required child in its own line. If no such child exists, output `-1`.
## 样例

### 样例输入 #1
```
3 4
M 10 3
M 5 1
D 20 2
D 5 1

```
### 样例输出 #1
```
3
1

```
### 样例输入 #2
```
10 10
M 20 10
D 1 9
M 2 3
D 17 10
M 20 2
D 8 2
M 40 1
D 25 2
M 33 9
D 37 9

```
### 样例输出 #2
```
-1
-1
3
2
9
```
## 题目翻译

### 题面描述
小马里卡正在创作一个奇妙的童话故事。她一边编故事，一边讲给她的爷爷听。爷爷可高兴了，于是问了她一些有趣的问题。

在小马里卡的故事中，有 $N$ 个年龄分别为 $1$~$N$ 岁的孩子（最小的为 $1$ 岁，最大的为 $N$ 岁）。有一天，她们一起乘火车出去旅行。铁路线上有好多个车站，分别以 $0, 1, 2, 3 \dots$ 编号。其中第 $0$ 站为始发站，火车每到一个车站都会停下来逗留一段时间。每个孩子都可以在选择自己喜欢的车站下车。

小马里卡喜欢这样讲述她的故事：“在第 $X$ 站，年龄为 $A$ 岁的孩子下车了。”不过小马里卡的习惯非常不好，她讲述故事的顺序是完全随机的。换句话说，$X$ 是不单调的。爷爷知道小马里卡的坏习惯，所以他喜欢时不时问一些有趣的问题来找小马里的麻烦。问题是这样的：“年龄大于等于 $B$ 且在第 $Y$ 站（包含第 $Y$ 站）以前下车的最年轻的小孩是多大？”

小马里卡必须正确回答爷爷的问题，否则爷爷会因生气而睡觉。值得注意的是，小马里卡的答案必须在当时是正确的。虽然小马里卡在随后的讲述中可能会改变问题的答案，但这都是无关紧要的。

小马里卡对自己的坏习惯十分无奈。由于故事的顺序过于杂乱，小马里卡根本无法正确回答爷爷的问题。于是她找到了聪明的你。请帮小马里卡编写一个程序，动态追踪她的讲述，并回答爷爷的问题。

### 输入格式
输入的第一行包含两个正整数 $N,Q\ (2 \le N,Q \le 2 \times 10^{5})$，分别代表孩子的数量和语句的数量。

接下来 $Q$ 行，每行一个语句。语句的格式为 `M X A` 或 `D Y B`，分别代表小马里卡的讲述和爷爷的问题。其中 `M`、`D` 为大写字母，$X$、$Y$、$A$、$B$ $(1 \le X,Y \le 10^{9},1 \le A,B \le N)$ 分别为一个正整数。其意义请见【题面描述】。题目中保证至少有一个 `D`。

### 输出格式
对于每一个问题 `D` 输出一个答案。答案为一个整数。如果爷爷的问题无解，请输出 `-1`。



---

---
title: "River Jumping"
layout: "post"
diff: 提高+/省选-
pid: P4753
tag: ['模拟', '搜索', '贪心', 'Special Judge', 'O2优化', '洛谷月赛']
---
# River Jumping
## 题目描述

有一条宽度为 $N$ 的河上，小 D 位于坐标为 $0$ 的河岸上，他想到达坐标为 $N$ 的河岸上后再回到坐标为 $0$ 的位置。在到达坐标为 $N$ 的河岸之前小 D 只能向坐标更大的位置跳跃，在到达坐标为 $N$ 的河岸之后小 D 只能向坐标更小的位置跳跃。在河的中间有 $M$ 个岩石，小 D 希望能跳到每个岩石上恰好一次。由于小 D 的跳跃能力太强，小 D 的跳跃长度有个下限 $S$，但没有上限。现在请你判断他是否能够完成他的目标。
## 输入格式

第一行输入两个整数 $N,M,S$，分别表示河的宽度，岩石的数量和跳跃长度的下限。

第二行输入 $M$ 个整数，分别表示 $M$ 个岩石的坐标 $w_1,w_2,\cdots,w_N$。保证 $\{w_i\}$ 为递增序列。
## 输出格式

如果小D可以完成他的目标，第一行输出 `YES`，第二行输出 $M+2$ 个数，依次表示小D跳到的石头编号。特殊的，坐标为 $0$ 的河岸编号为 $0$，坐标为$N$的河岸标号为 $M+1$ 。如果有多种解法，允许输出任意一种。

如果小 D 不能完成他的目标，第一行输出 `NO`。
## 样例

### 样例输入 #1
```
6 1 3
3
```
### 样例输出 #1
```
YES
1 2 0
```
### 样例输入 #2
```
6 2 2
2 4
```
### 样例输出 #2
```
YES
2 3 1 0
```
### 样例输入 #3
```
5 2 3
2 3
```
### 样例输出 #3
```
NO
```
## 提示

对于全部数据，保证 $1 \le N,S \le 100000$，$0 \le M < N$，$1 \le w_i < N$。


---

---
title: "True Vegetable"
layout: "post"
diff: 提高+/省选-
pid: P4754
tag: ['模拟', '贪心', 'O2优化', '洛谷月赛']
---
# True Vegetable
## 题目描述

小A现在有$N$道题，编号为$1,2,\cdots,N$。每道题的起始毒瘤程度为$0$或$1$。在每回合，小A可以将编号连续的$K$道题的毒瘤程度+1。但小B因为本身比较菜，不是很愿意小A出毒瘤题，所以在$w_i$回合开始时可以向第$x_i$题传播$v_i$点的菜气，使得第$x_i$的毒瘤程度减少$v_i$点（减后可以为负）。这里我们假定菜是有限的，在释放了$v_i$点的菜气后，小B需要至少$r_{v_i}$个回合不能释放菜气。现在小A知道了小B释放菜气的计划，他想知道他至少需要多少个回合可以使得每道题的毒瘤程度至少为$1$。
## 输入格式

第一行输入四个整数，$N,M,K,L$，分别为题目的数量，小B的操作数量，每次连续增加毒瘤程度题目的数量和释放菜气的最大值。

第二行输入$N$个整数$a_1,a_2,\cdots,a_N$，分别为$N$个题目的毒瘤程度。

第三行输入$L$个整数$r_1,r_2,\cdots,r_L$，分别为释放$1$到$L$点菜气的冷却回合数。

接下来有$M$行，每行输入三个整数$w_i,x_i,v_i$，表示小B在第$w_i$回合开始时向第$x_i$题释放了$v_i$点的菜气。保证$\{w_i\}$为递增序列。
## 输出格式

请输出小A将每道题的毒瘤程度加到至少为$1$最少需要的回合数。
## 样例

### 样例输入 #1
```
6 1 3 2
0 0 0 0 0 0
1 2
2 1 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
6 1 3 2
1 0 0 0 0 0
1 2
2 1 1
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
6 1 6 2
0 0 0 0 0 0
1 2
2 1 1
```
### 样例输出 #3
```
1
```
## 提示

$1 \le N,M \le 5 \times 10^5$

$1 \le K \le N$

$1 \le L \le 100$

$a[i] \in \{0,1\}$

$1 = r_1 < r_2 < \cdots < r_L \le 2 \times L$

$1 \le w_i \le N+L$

$w_i+r_{v_i} \le w_{i+1}$

$1 \le x_i \le N$

$1 \le v_i \le L$


---

---
title: "[USACO15DEC] Bessie's Dream G"
layout: "post"
diff: 提高+/省选-
pid: P4818
tag: ['模拟', '搜索', '2015', 'USACO']
---
# [USACO15DEC] Bessie's Dream G
## 题目描述

After eating too much fruit in Farmer John's kitchen, Bessie the cow is getting some very strange dreams! In her most recent dream, she is trapped in a maze in the shape of an $N×M$ grid of tiles $(1≤N,M≤1,000)$. She starts on the top-left tile and wants to get to the bottom-right tile. When she is standing on a tile, she can potentially move to the adjacent tiles in any of the four cardinal directions.

But wait! Each tile has a color, and each color has a different property! Bessie's head hurts just thinking about it:

- If a tile is **red**, then it is impassable.

- If a tile is **pink**, then it can be walked on normally.

- If a tile is **orange**, then it can be walked on normally, but will make Bessie smell like oranges.

- If a tile is **blue**, then it contains piranhas that will only let Bessie pass if she smells like oranges.

- If a tile is **purple**, then Bessie will slide to the next tile in that direction (unless she is unable to cross it). If this tile is also a purple tile, then Bessie will continue to slide until she lands on a non-purple tile or hits an impassable tile. Sliding through a tile counts as a move. **Purple tiles will also remove Bessie's smell.**

(If you're confused about purple tiles, the example will illustrate their use.)

Please help Bessie get from the top-left to the bottom-right in as few moves as possible. 
## 输入格式

 The first line has two integers $N$ and $M$, representing the number of rows and columns of the maze.

The next $N$ lines have $M$ integers each, representing the maze:

- The integer '0' is a red tile

- The integer '1' is a pink tile

- The integer '2' is an orange tile

- The integer '3' is a blue tile

- The integer '4' is a purple tile 

The top-left and bottom-right integers will always be '1'. 
## 输出格式

A single integer, representing the minimum number of moves Bessie must use to cross the maze, or -1 if it is impossible to do so. 
## 样例

### 样例输入 #1
```
4 4
1 0 2 1
1 1 4 1
1 0 4 0
1 3 1 1
```
### 样例输出 #1
```
10
```
## 提示

In this example, Bessie walks one square down and two squares to the right (and then slides one more square to the right). She walks one square up, one square left, and one square down (sliding two more squares down) and finishes by walking one more square right. This is a total of 10 moves (DRRRULDDDR).

Problem credits: Nathan Pinsker, inspired by the game "Undertale". 
## 题目翻译

### 题目描述

Bessie 在 Farmer John 的厨房暴食水果后，开始做奇怪的梦！在最近的梦境中，她被困在一个 $N \times M$ 的网格迷宫（$1 \leq N,M \leq 1,000$）中。她需要从左上角的格子移动到右下角的格子。当站在某个格子时，她可以向四个基本方向移动至相邻格子。

但请注意！每个格子有不同的颜色和特殊属性：

- **红色（0）**：不可通行  
- **粉色（1）**：可正常通行  
- **橙色（2）**：可正常通行，且会使 Bessie 带有橙子气味  
- **蓝色（3）**：仅当 Bessie 带有橙子气味时方可通行  
- **紫色（4）**：Bessie 将沿该方向滑动到下一个格子（除非无法通过）。若下一个格子仍是紫色，则继续滑动直至遇到非紫色格子或不可通行格子。**每次滑动均计为一步移动**，且**紫色格子会消除 Bessie 的气味**

（若对紫色格子机制有疑问，样例将帮助理解）

请帮助 Bessie 找到从左上角到右下角的最短路径步数。

### 输入格式

第一行包含两个整数 $N$ 和 $M$，表示迷宫的行数和列数。  
接下来 $N$ 行每行包含 $M$ 个整数描述迷宫：  
- 0 表示红色  
- 1 表示粉色  
- 2 表示橙色  
- 3 表示蓝色  
- 4 表示紫色  

保证左上角和右下角的格子始终为 1。

### 输出格式

输出一个整数，表示 Bessie 穿越迷宫所需的最少步数，若无法到达则输出 -1。

### 说明/提示

样例中，Bessie 的移动路径为：向下 1 步，向右 2 步（滑动再向右 1 步），向上 1 步，向左 1 步，向下 1 步（滑动再向下 2 步），最后向右 1 步。总计 10 步（路径表示为 DRRRULDDDR）。

题目提供者：Nathan Pinsker，灵感来自游戏《Undertale》  


---

---
title: "Nagisa loves Tomoya"
layout: "post"
diff: 提高+/省选-
pid: P4828
tag: ['模拟', '数学', '洛谷月赛']
---
# Nagisa loves Tomoya
## 题目描述

可爱的古河渚得到了一个序列。她定义一次操作为 将所有的 $a_i$ 变为 $a_i+a_{(i\ mod \ n+1)}$ 
然后她会向你进行 $Q$ 次询问，每次问你 $x,y$ ,意义为在第 $x$ 次操作后位置 $y $ 的元素是多少。

这个问题太简单了，我们的 Nagisa 轻易地就解决了这个问题。请问您能解决这个问题吗？

## 输入格式

一个整数 $n$，表示序列的长度。

接下来一行 $n$ 个整数，表示这个序列。


接下来一行一个整数 $Q$，表示询问次数

接下来 $Q$ 行，每行两个整数 $x,y$，意义如题所示。
## 输出格式

共 $Q$ 行，每行一个整数表示询问的答案，请注意对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
5
1 2 3 4 5
2
1 2
2 2
```
### 样例输出 #1
```
5
12
```
## 提示

对于$30 \%$的数据，满足：
$1 \leq n \leq 100$

$1 \leq x \leq 100$

$1 \leq Q \leq 100$

对于 $50\%$ 的数据：

$1\leq n \leq 100000$

$1 \leq x \leq 500$

$1 \leq Q \leq 100$

对于 $100 \%$ 的数据，满足

$1 \leq n \leq 10^6$

$1 \leq a_i \leq 10^9$

$1 \leq x \leq 2000$

$1 \leq Q \leq 10^4$


---

---
title: "PION贪吃蛇"
layout: "post"
diff: 提高+/省选-
pid: P4944
tag: ['模拟', '搜索', '队列']
---
# PION贪吃蛇
## 题目背景

NOIP2018原创模拟题 T3

NOIP DAY1 T3 or DAY 2 T2 难度

贪吃蛇大家都玩过吧，当然不同版本有不同规则。下面介绍PION贪吃蛇。
## 题目描述

![图A](https://cdn.luogu.com.cn/upload/pic/31298.png)

***表示方法：***

该题中贪吃蛇存在于一个n行m列的矩形中，用 ‘.’ 表示空地，用 '#’ 表示蛇身，用 ‘@’表示蛇头，用‘&’表示食物
例如：图一表示 $5*6$ 的矩形，有一条蛇，蛇长度为 $7$，有两个食物

***基本规则：***

1.蛇头每一秒就会移动一格，身体自然会跟着移动，用W表示向上，S表示向下，A表示向左，D表示向右

2.蛇每吃一个食物就长度就会加一，而增加的长度体现在食物所在的地方，你可以把吃食物理解成食物变成了蛇头，之前的蛇头变成了蛇身，这一秒不移动

例如：图二的三幅图展示了第一秒，第二秒，和第三秒的情况

3.蛇如果死亡，身体（包括头）一定会全部变成食物

4.PION贪吃蛇的蛇头碰到自己或别的蛇的身体就会死亡

例如：图三的三幅图展示了第二条蛇撞在别人身体上死亡的过程

5.蛇头撞在边界上也会引起死亡，但蛇头刚好现在边界上不会

例如：图四第二幅图虽然蛇头在边界上，但是只是刚好，如果此时进行D操作蛇就会死亡，如果进行W或S就不会

6.如果有操作使蛇头向相反方向运动，之后如果与身体重合蛇也会死亡（比如：图二第一幅图使用A操作,蛇就会死亡，此时在原地成为三个食物，你也可以理解为蛇下一秒不行动而自杀了）

7.两条蛇蛇头相撞，主动撞上的死亡

8.蛇的移动按编号由小到大进行（编号的含义见下文）

## 输入格式

第一行三个数 $n,m,k$ 表示 $n*m$ 的矩形，$k$ 表示操作次数

接下来 $n$ 行每行 $m$ 个字符，表示地图

再接下来 $c$ 行（注意：图中有几条蛇就有几行），每行 $k$ 个字符，表示有 $k$ 个操作（如果执行了某个操作蛇死了，就忽略后面的操作）

我们将蛇编号：按每条蛇蛇头的坐标从小到大编号为 $1，2，...，c$（越靠近上边的坐标越小，如果相同越靠近左边的坐标越小）

例如：图三第一幅图两条蛇的蛇头坐标分别为（$4,3）,（3,7）$所以较长的蛇编号为 $2$，较短的蛇编号为 $1$
## 输出格式

$c+1$ 行，输出 $k$ 次操作后每一条蛇的长度，编号；每一行第一个为长度，第二个数为编号

最后一行输出剩下食物的总个数

注意：输出按长度由大到小排序（长度相同按编号由小到大排序），死亡的蛇长度为 $0$
## 样例

### 样例输入 #1
```
5 7 6
.&...&.
..##@..
.&...&.
..##@..
.&...&.
DWAAAA
WDDDDD
```
### 样例输出 #1
```
5 1
0 2
7
```
### 样例输入 #2
```
9 9 4
.........
.#######.
.......#.
.@#.&@.#.
&.#.&&.#.
&&######.
.&.......
..@####..
.........
ASSD
ASDD
WASD
```
### 样例输出 #2
```
22 1
4 2
0 3
6
```
## 提示

***样例说明：***

![图B](https://cdn.luogu.com.cn/upload/pic/31357.png)

图五，图六展示了从第 $0$ 秒开始之后每一秒地图的状态，请看图理解（样例二图四有点小错误）

***数据范围：***

$10\%$ 数据满足 $n,m\leq 5,c=1,k\leq3$

$30\%$ 数据满足 $n,m\leq 10,c\leq 2,k\leq 5$

$50\%$ 数据满足 $n,m\leq 50,c\leq 5,k\leq 20$

$70\%$ 数据满足 $n,m\leq 100,c\leq 7,k\leq 50$

$100\%$ 数据满足 $n,m\leq 200,c\leq 20,k\leq 100$，且图中的蛇不会引起混淆（对于任意蛇头，最多只有一块蛇身于其相连，而蛇身最多为二连块）,且数据保证图中的蛇均可以判断身体与头的对应关系，不会造成蛇身形态多解


---

---
title: "水の斗牛"
layout: "post"
diff: 提高+/省选-
pid: P5013
tag: ['模拟', 'O2优化']
---
# 水の斗牛
## 题目背景

蒟蒻${\rm CYJian}$拉着${\rm JerryC}$和${\rm Justin}$等一众机房巨佬来打斗牛辣！！
## 题目描述

现在一共有$N$个人玩起了斗牛。一共玩了T局，每局有三个人参与游戏，每个人的初始分都是0。

本题为了方便，对于斗牛的基本规则做了些许变动，具体规则如下：

## 1.基本规则

每一轮斗牛开始时，每一位玩家都会拿到5张牌。

每张牌一定是一个2到10之间的整数或A(表示1)。

每张牌有一个花色，a代表黑桃，b代表红桃，c代表梅花，d代表方块。


## 2.牌型

五张牌中，除炸弹和无牛牌型以外，都分为两个部分：牛和分。其中牛包括三张点数相同(铁板)或三张点数和为10的倍数的牌，分包括剩下的两张牌，一套牌的分即为这两张牌模10的余数。

1)炸弹：四张点数相同的牌。

2)牛牛：分恰好为0。

3)牛：分不为0，分和牛数的数值相同。如分是5，则这套牌被称为牛五。

4)无牛：不存在三张牌，其点数相同或其点数和为10的倍数。

## 3.牌型大小关系

炸弹>牛牛>牛九>牛八>……>牛二>牛一>无牛

双方拥有炸弹时，炸弹点数大的更大；

相同牛数且只有一方有铁板时，有铁板的比没有铁板的大；

相同牛数且双方拥有铁板时，铁板点数大的更大；

相同牛数且双方均没有铁板或双方均无牛时，我们比较双方牌中点数最大的一张牌，点数更大的一方更大；若双方点数最大的一张牌点数相同，则花色更大的一方更大，花色大小为黑桃>红桃>梅花>方块。

## 4.计分

一局牌的底分为10，即每位玩家都会押10分。

对于其中的两位玩家，我们在比较完双方的牌型之后，选择牌型更大的一方的牌型来计算得失分数的翻倍。具体如下：

1)炸弹：底分×10。

2)牛牛：底分×3。

3)牛七/牛八/牛九：底分×2。

4)牛六~牛一：底分。

5)无牛：底分。

6)铁板：在计算完牌型得分之后，在牌型得分的基础上×2。注意铁板翻倍不与炸弹同时进行。

我们在计分时，采用两两之间计分的方式，也就是说对于三名玩家A、B、C，我们先计算A和B之间的分数得失，再计算A和C之间的分数得失，最后计算B和C之间的分数得失。

现在我们假设所有玩家都足够聪明，也就是说，所有玩家都会打出他们手上的牌中最大的牌型。${\rm CYJian}$想知道，在这T轮游戏结束之后，每位玩家的得分情况。
## 输入格式

第一行两个整数id，T，N。其中id表示测试点编号，对于部分分可能有一定帮助。其中样例的测试点编号为0。

接下来N行，每行一个仅包括大小写字母和数字的长度少于11的字符串表示玩家名称。

接下来T组，每组数据六行，可分为三个相同的部分：

第一行一个字符串表示玩家名称。

第二行五个字符串表示该玩家手中的手牌。每一个字符串的第一个字符表示花色，其余字符表示牌的大小。
## 输出格式

共N行，每行一个字符串和一个数字，中间用空格隔开。表示一名玩家和他的最终得分。

请按照玩家名称的输入顺序输出。
## 样例

### 样例输入 #1
```
0 2 3
CYJian
JerryC
Justin
CYJian
a10 b10 c10 d10 a9
JerryC
cA b2 c3 d4 d5
Justin
aA bA dA a4 c6
CYJian
aA b2 c3 d4 a5
JerryC
bA c2 d3 a4 b5
Justin
cA d2 a3 c4 c5
```
### 样例输出 #1
```
CYJian 220
JerryC -160
Justin -60
```
### 样例输入 #2
```
0 3 4
CYJian
JerryC
Samcompu
Hsl2363
CYJian
a2 b5 c8 d4 aA
Samcompu
a2 bA c3 a4 c5
JerryC
aA b2 c7 c4 c6
Hsl2363
aA bA cA dA a10
Samcompu
a2 b2 c2 d2 b10
JerryC
a3 b3 c3 d3 c10
Hsl2363
a5 c6 d8 a9 b9
JerryC
b6 b2 c9 a7 d2
CYJian
b5 d5 c5 a6 d9
```
### 样例输出 #2
```
CYJian 120
JerryC 150
Samcompu -60
Hsl2363 -210

```
## 提示

样例一解释：

第一局玩家牌型如下：

${\rm CYJian}$：炸弹

${\rm JerryC}$：牛五

${\rm Justin}$：铁板牛牛

所以${\rm CYJian}$加200分，${\rm JerryC}$扣160分，${\rm Justin}$扣40分。

第二局中，所有人都是牛五，但是${\rm CYJian}$拥有黑桃五，${\rm JerryC}$拥有红桃五，${\rm Justin}$拥有梅花五，所以${\rm CYJian}$加20分，${\rm JerryC}$没有变化，${\rm Justin}$扣20分。

数据范围：

| 测试点编号 |   $T$    |   $N$   | 特殊性质 |
| :--------: | :------: | :-----: | :------: |
|    $1$     |   $0$    |   $3$   |    性质4    |
|    $2$     |   $5$   |  $5$   |    性质4    |
|  $3$-$4$   |   $5$   |  $5$   |  性质1   |
|  $5$-$6$   |   $5$   |  $5$   |  性质2   |
|  $7$-$8$   |   $5$   |  $5$   |  性质3   |
|  $9$-$10$  |   $5$   |  $5$   |  性质5   |
| $11$-$12$  |   $10$    |   $10$   |  性质5   |
| $13$-$14$  |   $100$   |  $100$   |  性质5   |
| $15$-$16$  |  $1000$   |  $1000$  |  性质5   |
| $17$-$18$  |  $10000$  | $10000$  |  性质5   |
| $19$-$20$  | $100000$ | $100000$ |  性质5，1.5s   |

性质1：保证所有的人拥有炸弹。

性质2：保证每一手牌花色全部相同。

性质3：保证每一手牌所有数字不同。

性质4：保证数据手造。

性质5：保证数据随机生成。

保证每一局没有重复的牌。

保证每一个人的名字不相同。

保证出题人是${\rm CYJian}$。

保证数据没有锅。

不保证没有人能做出来。

不保证此题代码很长。


---

---
title: "跑酷"
layout: "post"
diff: 提高+/省选-
pid: P5033
tag: ['模拟']
---
# 跑酷
## 题目背景

[赛时答疑](https://www.luogu.org/discuss/show/80694)  

跑酷这东西，还是得看人品的（比如 zm 和 mt）…
## 题目描述

在 Minecraft 中，跑酷可以算得上是一门技术了，Steve 现在想在一个跑道上（二维）进行跑酷。但是 Steve 不知道能不能跑到终点，于是他便查询了 MC Wiki，来获得更多的知识。内容具体如下：

### 生命值

1. 我们规定每个玩家的初始生命为 $20$ 点。
2. 掉落伤害的计算:
   - 如果玩家的高度为 $3$ 格或以下，免除此伤害。
   - 如果玩家的高度为 $4$ 格或以上，便会造成 $x-3$ 点伤害，$x$ 为摔落的高度。
   - 这里的高度均指相对高度，即当前方块与下一个方块之间的高度差。
3. 掉落伤害降低的情况：见特殊方块。

4. 当生命值为 $0$ 的时候，视为不能到达终点。

### 跑酷

1. 对于站在一个方块上的玩家来说，玩家最多可以往前面跳 $3$ 格并且可以往上跳一个格子。
2. 对于站在一个方块上的玩家来说，玩家最多也可以往前跳 $4$ 格，但是不能向上跳一个格子。
3. 为了计算方便，我们规定下落时玩家不会移动，也就是说，如果下一个方块比现在方块的高度要低的话，我们只能正好下落到下一个方块的位置。
4. 默认终点为最后一个方块。

### 特殊方块

1. **粘液块**：会使你跳跃至 $60\%$ 坠落距离的高度，如果有小数，我们向下取整。当你达到最高点的时候，只能往前再移动一格。当然，如果落在前方的方块上，同样要受到摔落伤害。你也可以按住 Shift 键来免除反弹。我们认为在粘液块上面进行跑酷不受减速的限制。  
2. **蜘蛛网**：下落时会让你免除伤害。我们也认为玩家在蜘蛛网上跑酷不受减速的限制。  

Steve 找到了你，让你帮他去解决这个问题。判断 Steve 能不能到达终点。

- 如果能到达终点，输出最少的跳跃次数；
- 如果不能到达终点，请输出：`qwq`。
## 输入格式

第一行为一个整数 $n$，表示有 $n$ 个方块。

从第二行开始，下面连续 $n$ 行，表示有 $n$ 个方块。每个方块都有它的属性：横坐标，高度和是否为特殊方块。（普通方块输入为 $\verb!P!$，粘液块为 $\verb!N!$，蜘蛛网为 $\verb!Z!$）

## 输出格式

如果能到达终点，输出一个整数，表示最少的跳跃次数；
如果不能到达终点，请输出 `qwq`。
## 样例

### 样例输入 #1
```
2
1 4 P
4 5 P
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
1 6 P
2 4 N
3 4 P
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
2
5 8 P
7 11 P
```
### 样例输出 #3
```
qwq
```
## 提示



### 数据范围及约定

数据保证输入的横坐标单调递增。每一个横坐标只有一格方块。

数据保证不会在相邻的横坐标中间出现两个特殊方块。

对于方块而言，默认是都没有浮空方块的存在；也就是说，所有方块下面都会有支撑柱。

为了方便，不能先跳跃再下落。也就是说，只能下落到前面一格的方块。

对于 $30\%$ 的数据 $n\le 10$；  
对于另外 $20\%$ 的数据，保证不存在特殊方块；  
对于这前面的 $50\%$ 的数据，保证 Steve 往前跳只能跳四格远或者三格远一格高；  
对于 $100\%$ 的数据 $1\le n\le 1000$，$1\le x_{\rm max}\le 10000$，$1\le height\le 1000$。

保证数据有一定梯度。


---

---
title: "[THUPC 2019] 鸭棋"
layout: "post"
diff: 提高+/省选-
pid: P5380
tag: ['模拟', '2019', 'THUPC']
---
# [THUPC 2019] 鸭棋
## 题目描述

#### 题目背景

鸭棋是一种风靡鸭子界的棋类游戏。事实上，它与中国象棋有一些相似之处，但规则不尽相同。在这里，我们将为你介绍鸭棋的规则。

**同时，我们下发了一个模拟鸭棋规则的玩具，你可以结合这个玩具理解题目**（也可以在 AK 后与你的队友进行对弈）。详情请见「玩具使用说明」。

鸭棋在一个 $10\times 9$（$10$ 行 $9$ 列）的网格棋盘上进行，网格上的每个格点都可以有棋子停留。对弈双方一方执红（`red`）棋、另一方执蓝（`blue`）棋，双方轮流执行操作，轮到一位玩家操作时，他必须选择一枚自己的棋子，并按照规则进行一步移动。

鸭棋发明者鸭子德规定一局鸭棋由红方执先手，并设计了初始棋盘布局如下：

![initial_board.png](https://cdn.luogu.com.cn/upload/pic/58700.png)

##### 棋子类型与走子规则

棋子分为 $7$ 类，下面介绍了它们的名字以及它们的移动规则。介绍移动规则时，我们默认棋子所处位置为 $\left( x,y\right)$（表示第 $x$ 行的第 $y$ 列，下同），并列出它可以到达的位置：

* **王**（`captain`)：可达的位置共 $4$ 个，包括 $\left(x\pm 1,y\right)$ 及 $\left(x,y\pm 1\right)$。
* **士**（`guard`）：可达的位置共 $4$ 个，包括 $\left(x\pm 1,y\pm 1\right)$ 及 $\left(x\pm 1,y\mp 1\right)$。
* **象**（`elephant`）：可达的位置至多 $4$ 个，对于任意 $s_x,s_y\in \left\{ 1,-1\right\}$，分别有：
    * 如果位置 $\left(x+s_x\times 1 ,y+ s_y\times 1\right)$ 上**无任意一方**的棋子停留，则 $\left( x+s_x \times 2,y+s_y \times 2\right)$ 为一个可达的位置。
* **马**（`horse`）：可达的位置至多 $8$ 个，对于任意 $s_x,s_y\in \left\{ 1,-1\right\}$，分别有：
    * 如果位置 $\left(x+s_x\times 1 ,y\right)$ 上**无任意一方**的棋子停留，则 $\left( x+s_x \times 2,y+s_y \times 1\right)$ 为一个可达的位置。
    * 如果位置 $\left(x ,y+ s_y \times 1 \right)$ 上**无任意一方**的棋子停留，则 $\left( x+s_x \times 1,y+s_y \times 2\right)$ 为一个可达的位置。
* **车**（`car`）：可在**不跨越其他棋子**的前提下，到达同行或同列的所有其他位置。
* **鸭**（`duck`）：可达的位置至多 $8$ 个，对于任意 $s_x,s_y\in \left\{ 1,-1\right\}$，分别有：
    * 如果位置 $\left(x+s_x\times 2 ,y+s_y \times 1\right),\left(x+s_x\times 1 ,y\right)$ 上均**无任意一方**的棋子停留，则 $\left( x+s_x \times 3,y+s_y \times 2\right)$ 为一个可达的位置。
    * 如果位置 $\left(x+s_x \times 1 ,y+ s_y \times 2 \right),\left(x ,y+ s_y \times 1 \right)$ 上均**无任意一方**的棋子停留，则 $\left( x+s_x \times 2,y+s_y \times 3\right)$ 为一个可达的位置。
* **兵**（`soldier`）：可达的位置共 $8$ 个，包括 $\left(x\pm 1,y\right)$ 及 $\left(x,y\pm 1\right)$ 及 $\left(x\pm 1,y\pm 1\right)$ 及 $\left(x\pm 1,y\mp 1\right)$。

**除上面描述的规则之外，棋子移动还有如下额外规则：**

* 不能将棋子移动到棋盘外的某个位置。
* 玩家不能将棋子移动到**已经停留了己方棋子**的位置。
* 如果玩家将棋子移动到了一个**已经停留了对方棋子**的位置，那么原本停留在该位置上的这个**对方棋子**将被移出游戏。

##### 胜利条件与将军局面

玩家在这个游戏中的目标是将对方的**王**移出游戏。一旦一方的**王**被移出游戏，则另一方立即宣告胜利。

对于一个棋盘的状态，如果存在一方有一步合法的操作能够将另一方的**王**移出游戏，则我们说当前局面是一个**将军**的局面。需要友情提示的是，根据定义，将军局面的形成包括（但不限于）如下这些可能：

1. 一方将一枚棋子移动到可以攻击对方**王**的位置

2. 在己方**王**受到威胁时不采取措施躲避

3. 主动将**王**移动至会受到攻击的位置

**除此之外，需要特别说明的是，游戏结束后，由于双方不可再操作，因此不可能出现将军局面，即便此时另一方王处于被「攻击」的位置。**

#### 题目描述

今年的 IDCC（International Duck Chess Competition，国际鸭棋大赛）正在如火如荼地进行着。你观摩了一场精彩绝伦的比赛，但你对对弈过程的记忆已经模糊不清了，只有系统留下的他们的**操作序列**，序列中的每个**操作**为当前操作者试图移动某个位置的棋子至另一个位置。你希望用这个序列，来复现出整局棋局的对弈过程。即，对于每步操作，你需要**首先判其是否合法**，若合法，则**进一步求出**：

1. 这步操作移动了哪个棋子。
2. 这步操作后，是否存在棋子被移出游戏，如有则还需求出被移出游戏的棋子。
3. 这步操作后，是否形成将军局面。
4. 这步操作后，游戏是否结束。

可能包含的不合法情况如下：

* 此步移动的初始位置无己方棋子停留。
* 此步移动的初始位置有己方棋子停留，但移动不符合规则。
* 游戏已经结束。

序列中的不合法操作是需要被忽略的。比如，如果轮到红方移动，此时序列中的当前操作恰好是不合法的，则这个操作将被忽略，序列中的下一步操作将成为红方这步的操作（如仍不合法则继续忽略，直至出现合法的操作）。
## 输入格式

第一行一个非负整数 $Q$，表示操作序列的长度。接下来依次描述每个操作。

接下来 $Q$ 行，每行 $4$ 个整数 $x_s, y_s, x_t, y_t$（$0\leq x_s,x_t < 10$，$0\leq y_s,y_t < 9$），描述一个欲将 $\left(x_s,y_s\right)$ 处棋子移动到 $\left(x_t,y_t\right)$ 的操作。在这里，我们规定左下角（即红方**车**摆放的位置，图见「题目背景」）为 $\left(0,0\right)$。

保证 $Q\leq 1000$。
## 输出格式

输出 $Q$ 行，对于每个操作依次输出复现结果。每行输出一个操作的结果：

* 如果该操作为不合法操作，则请输出 `Invalid command`。
* 如果为合法操作，则依次回答「题目描述」中的问题 $1\sim 4$：
    * 被移动的棋子用 `[颜色] [类型]`（注意中间包含空格）来描述，请使用它们的英文名称（见「题目背景」）。如，红象为 `red elephant`，蓝王为 `blue captain`。
    * 被移出游戏的棋子的描述方式与上面类似。特别地，**如果无棋子被移出游戏，则该问题的答案为 `NA`**。
    * 用 `yes`、`no` 分别表示形成、不形成将军局面。
    * 用 `yes`、`no` 分别表示游戏结束、游戏不结束。
    * 用 `;`（分号）将所有问题的答案隔开。
    * 比如，四个问题的答案分别为：被移动的棋子是蓝车，无棋子被移出游戏，形成将军局面，游戏未结束。则该行应输出 `blue car;NA;yes;no`。
## 样例

### 样例输入 #1
```
18
0 0 7 0
9 0 8 0
0 1 1 3
0 2 2 0
0 3 1 2
0 4 0 3
9 4 8 4
3 2 2 3
7 0 4 2
7 0 5 3
9 2 7 4
2 0 4 3
9 1 8 3
4 3 6 6
7 4 9 2
8 4 9 4
6 6 9 4
9 8 8 8
```
### 样例输出 #1
```
Invalid command
Invalid command
Invalid command
Invalid command
red guard;NA;no;no
Invalid command
blue captain;NA;no;no
red soldier;NA;no;no
Invalid command
Invalid command
blue elephant;NA;no;no
red duck;NA;no;no
blue horse;NA;no;no
red duck;blue soldier;no;no
Invalid command
blue captain;NA;yes;no
red duck;blue captain;no;yes
Invalid command
```
## 提示

##### 玩具使用说明

你可以在玩具所在目录下执行如下命令来运行玩具（链接: <https://pan.baidu.com/s/12MJGgZB9zKcE3qgRbRozGw> 提取码: 4d5c）：

```
./duckchess
```

特别地，在**初次运行前**，你需要执行如下命令为它添加运行权限：


```
chmod +x duckchess
```

##### 版权信息

来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2019。

题解等资源可在 <https://github.com/wangyurzee7/THUPC2019> 查看。


---

---
title: "[ICPC 2019 WF] Karel the Robot"
layout: "post"
diff: 提高+/省选-
pid: P6259
tag: ['模拟', '2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Karel the Robot
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。
## 题目描述

Did you know that the word "robot" is almost 100 years old? It was first introduced in 1920, in the science-fiction theatrical play $R.U.R.$ , written by Karel Capek. As a tribute to this Czech writer, an educational programming language was named Karel many years later at Stanford University. Your task is to implement an interpreter of a simplified version of this programming language.

The Karel programming language controls a robot named Karel, who lives in a grid of unit squares. Some of the squares are free, while others contain a barrier. Karel always occupies one of the free squares and faces one of the four cardinal directions. The two basic commands are "move forward" and "turn left." The language also provides simple conditional and looping statements. The main educational potential of the language lies in the possibility of defining new procedures for more complex tasks.

Our simplified version of the language can be described by the following grammar:

```plain
<program> := "" | <command> <program>
<command> := "m" | "l" | <proc-call> |
             "i" <condition> "(" <program> ")(" <program> ")" |
             "u" <condition> "(" <program> ")"
<condition> := "b" | "n" | "s" | "e" | "w"
<proc-call> := <uppercase-letter>
<proc-def> := <uppercase-letter> "=" <program>
```
There are five types of commands:

- $\texttt m$ ("move forward") advances Karel's position by one grid square in its current heading, unless there is a barrier, in which case the command has no effect.
- $\texttt l$ ("turn left") makes Karel turn left $90$ degrees.
- $\texttt X$ where $\texttt X$ is any uppercase letter, invokes the procedure named $\texttt X$. 
- $\texttt i$ ("if") followed by a single-letter condition, and two programs in parentheses. If the condition is satisfied, the first program is executed. Otherwise, the second program is executed.
- $\texttt u$ ("until") followed by a single-letter condition, and a program in parentheses. If the condition is satisfied, nothing is done. Otherwise, the program is executed and then the command is repeated.

A condition can be either '$b$', which is satisfied if and only if there is a barrier in the next square in Karel's current heading, or one of the four directional letters `n`, `s`, `e`, or `w`, which is satisfied if and only if Karel's current heading is north, south, east, or west, respectively.


For instance, a simple program `ub(m)` can be understood to mean: “keep moving forward until there is a barrier," while `un(l)` means "turn to the north." A procedure definition `R=lll` defines a new procedure `R` which effectively means "turn right."

## 输入格式

The first line of input contains four integers $r, c, d$ and $e$, where $r$ and $c$ $(1 \leq r, c \leq 40)$ are the dimensions of the grid in which Karel lives, $d$ $(0 \leq d \leq 26)$ is the number of procedure definitions, and $e$ $(1 \leq e \leq 10)$ is the number of programs to be executed.

Then follow $r$ lines describing the grid (running north to south), each containing c characters (running west to east), each character being either `.` (denoting a free square) or `#` (denoting a barrier). All squares outside this given area are considered barriers, which means Karel may never leave the area.

Each of the next $d$ lines contains a procedure definition, associating a procedure name (one uppercase letter) with a program forming the procedure body. No procedure name is defined more than once. Procedure bodies may contain invocations of procedures that have not yet been defined.

The last $2e$ lines describe the programs to be executed. Each such description consists of a pair of lines. The first line of each pair contains two integers $i$ and $j$ and a character $h$, where $i$ $(1 \leq i\leq r)$ is the row and $j$ $(1 \leq j \leq c)$ is the column of Karel's initial position, and $h \in \{ \texttt n, \texttt s, \texttt e, \texttt w\}$ represents Karel's initial heading. It is guaranteed that the initial position is a free square. The second line of each pair contains a program to be executed from that initial position.

All procedure bodies and all programs to be executed are at least $1$ and at most $100$ characters long, syntactically correct, and only contain invocations of procedures that are defined. The lines with procedure definitions and programs to be executed contain no whitespace characters.

## 输出格式

For each program execution, output the final position of Karel after the complete program is executed from the respective initial position. Follow the format used to describe initial positions, that is, two numbers and a directional character. If a particular execution never terminates, output `inf` instead.

## 样例

### 样例输入 #1
```
4 8 5 7
.......#
..#....#
.###...#
.....###
R=lll
G=ub(B)
B=ub(m)lib(l)(m)
H=ib()(mmHllmll)
I=III
1 1 w
G
1 1 e
G
2 2 n
G
2 6 w
BR
4 1 s
ib(lib()(mmm))(mmmm)
1 1 e
H
2 2 s
I

```
### 样例输出 #1
```
1 1 w
inf
1 1 w
2 4 s
4 4 e
1 4 e
inf

```
## 提示

Source: ICPC World Finals 2019.
## 题目翻译

## 题目描述

你知道“机器人”这个词已经有100年的历史了吗？它最早出现在1920年的科幻戏剧《R.U.R.R.U.R.》中，卡雷尔·卡佩克写的。为了向这位捷克作家致敬，一种教育编程语言在多年后在斯坦福大学被命名为Karel。您的任务是实现此编程语言简化版本的解释器。

Karel编程语言控制着一个名叫Karel的机器人，他生活在一个单位方格的网格中。一些方块是自由的，而另一些方块包含障碍物。卡雷尔总是占据一个自由正方形，面向四个基本方向之一。两个基本命令是“向前移动”和“向左转”。该语言还提供简单的条件语句和循环语句。该语言的主要教育潜力在于为更复杂的任务定义新程序的可能性。

我们简化的语言版本可以用以下语法描述：

```
<program> := "" | <command> <program>
<command> := "m" | "l" | <proc-call> |
             "i" <condition> "(" <program> ")(" <program> ")" |
             "u" <condition> "(" <program> ")"
<condition> := "b" | "n" | "s" | "e" | "w"
<proc-call> := <uppercase-letter>
<proc-def> := <uppercase-letter> "=" <program>
```
有五种类型的命令：

m（“向前移动”）在当前航向中将Karel的位置向前移动一个方格，除非有障碍物，在这种情况下，命令无效。

l（“左转”）使卡雷尔左转9090度。

x，其中x是任何大写字母，调用名为x的过程。

i（“if”）后跟一个单字母条件，括号中有两个程序。如果满足条件，则执行第一个程序。否则，执行第二个程序。

u（“直到”），后跟一个单字母条件，括号中是一个程序。如果条件满足，则什么也不做。否则，将执行该程序，然后重复该命令。

条件可以是“b”，当且仅当Karel当前航向的下一个方格中存在障碍物时满足，或者四个方向字母n、s、e或w中的一个，当且仅当Karel当前航向分别为北、南、东或西时满足。

例如，一个简单的程序ub（m）可以理解为“继续前进，直到有障碍物为止”，而un（l）表示“转向北方”。程序定义R=lll定义了一个新的程序R，它实际上意味着“右转”

输入的第一行包含四个整数r、c、dr、c、d和e，其中r和c（1≤r、 c≤40）是Karel居住的网格的尺寸，d（0≤D≤26）是程序定义的数量，e（1）≤E≤10） 是要执行的程序数。

然后沿着描述网格的r行（从北到南），每个包含c字符（从西到东），每个字符都是。（表示自由正方形）或#（表示障碍物）。该区域以外的所有广场都被视为障碍物，这意味着卡雷尔可能永远不会离开该区域。

接下来的d行中的每一行都包含一个过程定义，将过程名称（一个大写字母）与构成过程主体的程序相关联。没有多次定义过程名称。过程主体可能包含尚未定义的过程调用。

最后两行描述了要执行的程序。每个这样的描述由一对行组成。每对的第一行包含两个整数ii和jj以及一个字符hh，其中i（1≤我≤r） 是行和j（1）≤J≤c） 是Karel初始位置的列，h∈{n，s，e，w}代表Karel的初始标题。保证初始位置为自由正方形。每对的第二行包含从该初始位置执行的程序。

所有要执行的过程体和所有程序的长度至少为11个字符，最多为100100个字符，语法正确，并且仅包含已定义过程的调用。包含要执行的过程定义和程序的行不包含空格字符。

输出格式

对于每个程序执行，在从各自的初始位置执行完整程序后，输出Karel的最终位置。遵循用于描述初始位置的格式，即两个数字和一个方向字符。如果特定执行从未终止，则改为输出inf。


---

---
title: "[ICPC 2016 WF] Clock Breaking"
layout: "post"
diff: 提高+/省选-
pid: P6920
tag: ['模拟', '2016', '枚举', 'ICPC']
---
# [ICPC 2016 WF] Clock Breaking
## 题目描述

After numerous unfortunate freak fatalities and the lawsuits, settlements, protests, and boycotts that naturally followed, the beleaguered executives at ACME Clock Manufacturers have decided they need to finally fix their disastrous quality control issues. It has been known for years that the digital clocks they manufacture have an unacceptably high ratio of faulty liquid-crystal display (LCD) screens, and yet these heartless souls have repeatedly failed to address the issue, or even warn their hapless consumers!

You have been called in as a quality consultant to finally put a stop to the madness. Your job is to write an automated program that can test a clock and find faults in its display.

These clocks use a standard 7-segment LCD display for all digits (shown on the left in Figure 1), plus two small segments for the ‘:’, and show all times in a 24-hour format. The minute before midnight is 23:59, and midnight is 0:00. The ‘:’ segments of a working clock are on at all times. The representation of each digit using the seven segments is shown on the right in Figure 1.

![](https://cdn.luogu.com.cn/upload/image_hosting/3ornshtp.png)

   Figure 1: LCD display of each digit. 

Your program will be given the display of a clock at several consecutive minutes, although you do not know exactly what time these displays start. Some of the LCD segments are burnt out (permanently off) and some are burnt in (permanently on). Your program must determine, where possible, which segments are definitely malfunctioning and which are definitely in working order.
## 输入格式

The first input line contains a single integer $n$ ($1 \leq n \leq 100$), which is the number of consecutive minutes of a clock’s display. The next $8n-1$ lines contain $n$ ASCII images of these clock displays of size $7 \times 21$, with a single blank line separating the representations.

All digit segments are represented by two characters, and each colon segment is represented by one character. The character ‘X’ indicates a segment that is on. The character ‘.’ indicates anything else (segments that are off or non-segment portions of the display). See the sample input/output for details; the first output shows every possible LCD segment along with the smaller segments used to represent the ‘:’. No clock representation has an ‘X’ in a non-segment position or only half of a segment showing.
## 输出格式

Display a $7 \times 21$ ASCII image with a ‘0’ for every segment that is burnt out, a ‘1’ for every segment that is burnt in, a ‘W’ for every segment that is definitely working, and a ‘?’ for every segment for which the status cannot be determined. Use ‘.’ for non-segments. If the given displays cannot come from consecutive minutes, display impossible.
## 样例

### 样例输入 #1
```
3
......XX.....XX...XX.
.....X..X...X..X....X
.....X..X.X.X..X....X
.............XX...XX.
.....X..X......X.X..X
.....X..X......X.X..X
......XX.....XX...XX.

......XX.....XX...XX.
.....X..X...X..X....X
.....X..X.X.X..X....X
.............XX...XX.
.....X..X......X.X..X
.....X..X......X.X..X
......XX.....XX...XX.

.............XX...XX.
........X...X..X....X
........X.X.X..X....X
.............XX......
........X...X..X.X..X
........X...X..X.X..X
......XX.....XX...XX.

```
### 样例输出 #1
```
.??...WW.....??...??.
?..?.W..?...?..1.0..?
?..?.W..?.?.?..1.0..?
.??...??.....11...WW.
?..?.W..?.0.W..?.1..?
?..?.W..?...W..?.1..?
.??...11.....??...??.

```
### 样例输入 #2
```
2
......XX.....XX...XX.
...X....X...X..X.X..X
...X....X.X.X..X.X..X
......XX..........XX.
...X.X....X.X..X.X..X
...X.X......X..X.X..X
......XX.....XX...XX.

......XX.....XX......
...X....X...X..X.....
...X....X.X.X..X.....
......XX.............
...X.X....X.X..X.....
...X.X......X..X.....
......XX.....XX......

```
### 样例输出 #2
```
impossible

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

### 题目描述  

在无数不幸的畸形死亡事件以及随之而来的诉讼、和解、抗议和抵制之后，ACME时钟制造商的高管们决定最终解决灾难性的质量控制问题。多年来，人们都知道，他们制造的数字钟的液晶显示屏故障率高得令人无法接受，然而，这些无情的人们却一再未能解决这个问题，甚至未能警告他们不幸的消费者！  

你被邀请担任质量顾问，最终制止了这种疯狂。你的工作是编写一个自动程序，可以测试时钟并发现其显示中的故障。  

这些时钟使用标准的7段LCD显示屏显示所有数字（如图1左侧所示），加上两个小段显示`：`，并以24小时计时法显示所有时间。午夜前一分钟是23:59，午夜是0:00。工作时钟的`：`段始终打开。图1右侧显示了使用七段表示的`0~9`每个数字。  

![图1：每个数字的LCD显示。](https://cdn.luogu.com.cn/upload/image_hosting/3ornshtp.png)   

图1：每个数字的LCD显示。

### 输入格式  

第一行有一个数$n(1\ \le\ n\ \le\ 100)$，这是时钟显示的连续分钟数。  

接下来$8n-1$行包括$n$个时钟显示的$7\times 21$的ASCII图像，每两个之间会有一行的空白用于间隔  

所有表示数字的段由两个连续的字符表示，每个表示冒号的段由一个字符表示。字符`X`表示打开的段。字符`.`指示其他任何内容（显示的分段或非分段部分）。详见样本输入、输出；第一个输出显示每个可能的LCD段以及用于表示`：`的较小段。没有时钟表示在非段位置有`X`，或仅显示段的一半。  

### 输出格式  

显示一个$7\times 21$ASCII图像，每个烧坏的段显示一个`0`，每个烧进的段显示`1`，每个正常工作的段显示为`W`，以及一个`？`对于无法确定状态的每个段。使用`.`对于非分段。如果给定的显示不能来自连续分钟，则显示`impossible`。  

### 输入输出样例  

### 说明/提示  

时间限制：3000ms=3s  

空间限制：1048576KB=1024MB=1GB  

出处:2016年国际大学生编程大赛（`ACM-ICPC`）世界总决赛


---

---
title: "Mivik 的游戏"
layout: "post"
diff: 提高+/省选-
pid: P7119
tag: ['模拟', '2020', '线段树', 'O2优化']
---
# Mivik 的游戏
## 题目背景

Mivik 和 W!ʌ!k 在玩游戏！
## 题目描述

Mivik 首先把 $n$ 枚硬币摆成一排，其中有一些正面朝上，其余的都是反面朝上。W!ʌ!k 打算不断执行以下操作直到这 $n$ 枚硬币中没有硬币反面朝上：

- 如果现在这 $n$ 枚硬币中有 $k$ 枚硬币反面朝上，那么翻转从左到右第 $k$ 枚硬币。具体地，如果从左到右第 $k$ 枚硬币正面朝上，则将其变为反面朝上；如果从左到右第 $k$ 枚硬币反面朝上，则将其变为正面朝上。

在 W!ʌ!k 开始玩游戏之前，Mivik 想考考 W!ʌ!k。Mivik 想让 W!ʌ!k 算出他总共会进行多少次这样的操作，或者是 W!ʌ!k 永远无法停止执行操作。

W!ʌ!k 很快解决了这个问题，但是心理比 yky 还变态的 Mivik 显然不会放过他。Mivik 进行了很多次操作，每次他翻转了一个区间的硬币，他要求 W!ʌ!k 算出他总共会进行多少次这样的操作，或者是 W!ʌ!k 永远无法停止执行操作。

**请注意，W!ʌ!k 只是需要计算总共会进行多少次操作，而不会真正进行操作。**
## 输入格式

输入共 $\left(m+2\right)$ 行。

第一行为两个非负整数 $n,m$，其中 $n$ 表示 Mivik 的硬币的个数，$m$ 表示 Mivik 进行的翻转操作的次数。

第二行为一个只包含有 $\texttt H$ 和 $\texttt T$ 的字符串。第 $i$ 个字符 $s_i$ 为 $\texttt H$ 则表示从左到右第 $i$ 枚硬币初始时是正面朝上；$s_i$ 为 $\texttt T$ 则表示从左到右第 $i$ 枚硬币初始时是反面朝上。

接下来 $m$ 行，每行两个正整数 $l_i,r_i$，表示 Mivik 翻转了从左到右数 $l_i\sim r_i$（包括 $l_i$ 和 $r_i$）的硬币。
## 输出格式

输出 $\left(m+1\right)$ 行，分别表示在真正执行操作前后共 $\left(m+1\right)$ 个时刻开始 W!ʌ!k 总共会进行多少次这样的操作，或者是 W!ʌ!k 永远无法停止执行操作。如果某一时刻 W!ʌ!k 不能停止执行操作，则在对应行输出字符串 $\texttt{never}$。
## 样例

### 样例输入 #1
```
2 2
TT
2 2
1 2

```
### 样例输出 #1
```
2
1
3

```
### 样例输入 #2
```
5 0
HTHTH

```
### 样例输出 #2
```
8

```
### 样例输入 #3
```
10 10
HTHHTHTHHH
9 9
5 5
10 10
7 7
6 6
9 9
4 4
9 9
7 7
2 2

```
### 样例输出 #3
```
19
30
27
40
33
38
27
28
37
40
47

```
## 提示

### 样例解释 #1
初始时两枚硬币都是反面朝上，因此如果 W!ʌ!k 从此刻开始执行操作， W!ʌ!k 会将编号为 $2$ 的硬币翻转过来。操作后只有一枚硬币反面朝上，因此第 $2$ 次操作会将编号为 $1$ 的硬币翻转过来。在第 $2$ 次操作后没有硬币反面朝上，因此 W!ʌ!k 不会再执行操作，总共会执行 $2$ 次操作。

### 样例解释 #2
这 $8$ 次操作分别翻转了第 $2,1,2,3,4,3,2,1$ 枚硬币。

### 测试点约束
**本题采用捆绑测试。**

对于全部数据，有 $1\le n,m\le10^6$，$s_i\in\left\{\texttt H,\texttt T\right\}$，$1\le l_i\le r_i\le n$。

每个子任务的具体限制见下表：

| 子任务编号 | 分值 | 特殊限制 |
|:-:|:-:|:-:|
| 1 | 10 | $n\le3$ |
| 2 | 20 | $n,m\le100$ |
| 3 | 30 | $m\le10$ |
| 4 | 20 | $l_i=r_i$ |
| 5 | 20 | 无 |

**本题读入输出量较大，请使用较快的读入输出方式。**


---

---
title: "[THUPC 2017] 体育成绩统计"
layout: "post"
diff: 提高+/省选-
pid: P7426
tag: ['模拟', '2017', 'THUPC']
---
# [THUPC 2017] 体育成绩统计
## 题目背景

正所谓「无体育，不清华」。为了更好地督促同学们进行体育锻炼，更加科学地对同学们进行评价，五道口体校的老师们在体育成绩的考核上可谓是煞费苦心。然而每到学期期末时，面对海量的原始数据，如何对数据进行处理，得到同学们的体育总评成绩却又成了体育部老师的一大难题。
## 题目描述

对于大一的同学们来说，体育课的总评成绩由五部分组成：体育课专项成绩（满分 $50$ 分）、长跑测试成绩（满分 $20$ 分）、「阳光长跑」成绩（满分 $10$ 分）、体质测试成绩（满分 $10$ 分）、「大一专项计划」成绩（满分 $10$ 分）。

体育课专项成绩将由任课体育老师直接给出。

长跑测试成绩将由期末长跑测试确定，其中男生需进行 $3000$ 米测试，女生需进行 $1500$ 米测试，具体评分标准为：
|  | $20$ | $18$ | $16$ | $14$ | $12$ | $10$ | $8$ | $6$ | $4$ | $2$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 男生 | $12'30''$ | $13'00''$ | $13'30''$ | $14'00''$ | $14'30''$ | $15'10''$ | $15'50''$ | $16'30''$ | $17'10''$ | $18'00''$ |
| 女生 | $6'40''$ | $6'57''$ | $7'14''$ | $7'31''$ | $7'50''$ | $8'05''$ | $8'20''$ | $8'35''$ | $8'50''$ | $9'00''$ |

「阳光长跑」是通过手机 App 来记录同学们的课外长跑情况，根据对原始跑步数据进行筛选，得到课外长跑的合法次数，来最终确定此部分的成绩。

一条合法的锻炼记录需同时满足：

男生长跑距离 $3000$ 米以上（包含 $3000$ 米），女生长跑距离 $1500$ 米以上（包含 $1500$ 米）；

平均速度（运动距离/(结束时间-开始时间)）不慢于 $2$ 米／秒，且不快于 $5$ 米／秒；

总暂停时间不得超过 $4$ 分 $30$ 秒；

平均步幅（距离／步数）不超过 $1.5$ 米；

开始时间需与上条合法记录的结束时间间隔 $6$ 小时以上（包含 $6$ 小时）；

「阳光长跑」的合法次数与该部分得分的对应如下：
| 分数 | $10$ | $9$ | $8$ | $7$ | $6$ | $4$ | $2$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 次数 | $[21,+∞)$ | $[19,20]$ | $[17,18]$ | $[14,16]$ | $[11,13]$ | $[7,10]$ | $[3,6]$ |

对于体质测试部分，若达到合格标准则得到该部分满分 $10$ 分，否则该部分不得分。

「大一专项计划」的 $10$ 分由两部分组成：出勤次数占 $5$ 分，期末检测占 $5$ 分。

其中出勤次数为「班级训练营」的参加次数和「阳光长跑」的合法次数之和，出勤得分与出勤次数的对应如下：
| 分数 | $5$ | $4$ | $3$ | $2$ | $1$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 次数 | $[18,+∞)$ | $[15,17]$ | $[12,14]$ | $[9,11]$ | $[6,8]$ |

不难看出，要想准确无误地计算出每个人的体育成绩并不是一件轻松的事，于是体育部的老师找到了正在打校赛的你，他将提供所有需要用到的数据，希望你帮他算算清华大一同学的体育总评成绩及等级。

百分制成绩与等级、绩点对应如下：
| A | A- | B+ | B | B- | C+ | C | C- |D+  | D | F |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $[95,100]$ | $[90,95)$ | $[85,90)$ | $[80,85)$ | $[77,80)$ | $[73,77)$ | $[70,73)$ | $[67,70)$ | $[63,67)$ | $[60,63)$ | $[0,60)$ |

## 输入格式

从标准输入读入数据。

输入第一行，包含一个正整数 $n$，表示大一年级的学生人数。

接下来 $n$ 行，每行表示一位学生（按学号字典序给出），各项数据之间用空格隔开，一位学生的数据包括：

- 一个长度为 $10$ 的正整数 $p$（数据保证不包含前导零），表示第 $i$ 位同学的学号；
- 一个字符，M 或 F，若为 M 表示第 $i$ 位同学为男生，若为 F 则表示第 $i$ 位同学为女生；
- 一个介于 $0$ 到 $50$ 之间的非负整数 $s$，表示第 $i$ 位同学的体育课专项成绩；
- 一个形如 `a'b"` 的字符串，表示第 $i$ 位同学的期末长跑测试成绩为 $a$ 分 $b$ 秒；
- 一个字符，P 或 F，若为 P 表示第 $i$ 位同学的体质测试通过，若为 F 则表示第 $i$ 位同学的体质测试没有通过；
- 一个介于 $0$ 到 $5$ 之间的非负整数 $f$，表示第 $i$ 位同学的「大一专项计划」的期末检测成绩；
- 一个非负整数 $c$，表示第 $i$ 位同学参加「班级训练营」的次数。

接下来一行，包括一个非负整数 $m$，表示需要筛选的「阳光长跑」数据条数。

接下来 $m$ 行，每行表示一条需要筛选的「阳光长跑」数据（按开始时间顺序给出），各项之间用空格隔开，一条数据包括：

- 一个形如 `2017MMDD` 的字符串，表示第 $j$ 条记录的完成日期；
- 一个长度为 $10$ 的正整数 $p$（数据保证不包含前导零），表示第 $j$ 条记录的来源学号；
- 两个形如 `hh:mm:ss` 的字符串，分别表示第 $j$ 条记录的开始时间和结束时间；
- 一个精确到小数点后两位的非负浮点数 $l$，表示第 $j$ 条记录的运动距离，单位为千米；
- 一个形如 `a'b"` 的字符串，表示第 $j$ 条记录的总暂停时间为 $a$ 分 $b$ 秒；
- 一个非负整数 $s$，表示第 $j$ 条记录的运动总步数。

输入格式可参见下发样例文件。
## 输出格式

输出到标准输出。

输出文件共包括 $n$ 行。请你按照学号**字典序**输出每一位同学的学号、百分制总评成绩以及等级。每位同学一行，一行内用空格隔开。
## 样例

### 样例输入 #1
```
1
2015011233 M 34 14'30" P 3 3
8
20170508 2015011233 17:02:33 17:19:33 2.99 0'0" 3333
20170509 2015011233 17:12:15 17:38:46 3.01 2'3" 4300
20170510 2015011233 22:03:06 22:13:08 3.05 0'0" 2772
20170511 2015011233 22:08:05 22:28:13 3.02 5'3" 3775
20170512 2015011233 18:03:12 18:17:56 3.02 0'0" 2001
20170513 2015011233 17:30:23 17:46:08 3.01 0'0" 3020
20170513 2015011233 22:03:34 22:20:08 3.04 2'0" 3058
20170514 2015011233 07:16:22 07:32:34 3.00 0'0" 3244
```
### 样例输出 #1
```
2015011233 59 F
```
## 提示

对于 $100\%$ 的数据，$n\le 10^4,0\le a,b\le 59,0\le c\le 100,m\le 1.5\times 10^5,0\le l\le 100,0\le s\le 10^6$。
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。


---

---
title: "「SWTR-7」Scores（hard version）"
layout: "post"
diff: 提高+/省选-
pid: P7876
tag: ['模拟', '2021', 'Special Judge', 'O2优化', '图论建模', '图遍历', '构造', '洛谷月赛']
---
# 「SWTR-7」Scores（hard version）
## 题目背景

#### 本题是 Scores 的 hard 版本。注意题目限制与 [easy](https://www.luogu.com.cn/problem/P7873) 版本不同。

#### 请注意特殊的时空限制。
## 题目描述

小 A 的班上有 $n$ 个学生。最近他们进行了一场考试，共有 $m$ 个学科。第 $i$ 个学生第 $j$ 门学科的得分为**整数** $s_{i,j}\ (0\leq s_{i,j}\leq 100)$。

同学们很重视自己在班上的排名，所以他们经常会比较自己和别的同学的分数。如果一个学生 $i$ **至少有一门学科**的分数比 $j$ **高**，ta 就会觉得自己不比 $j$ 差；相反，如果 ta **每门学科**的分数都比 $j$ **低**，ta 就会觉得自己被 $j$ 吊打了。

实际上，**上述两种情况并不是严格意义上相反的**。但是喜好八卦的小 A 打听到了每两个同学之间的分数情况，他惊讶地发现：**一个同学 $i$ 要么被 $j$ 吊打，要么不比 $j$ 差。** 同时，**如果 $i,j$ 被同一个人吊打，或同时吊打同一个人，则他们之间也有一方被另一方吊打**。我们用一个矩阵 $a_{i,j}\ (i\neq j)$ 来描述小 A 知道的同学们之间的分数关系：$a_{i,j}=0$ 表示 $i$ 被 $j$ 吊打；$a_{i,j}=1$ 表示 $i$ 不比 $j$ 差。

小 A 想知道这种情况会不会发生，即是否存在这样一张 $n\times m$ 的成绩表 $s$ 满足矩阵 $a$ 所描述的分数关系，从而确定有没有撒谎的同学。如果存在 $s$，请先输出 $\texttt{YES}$，再**任意**输出一种符合要求的成绩表；否则输出 $\texttt{NO}$。

注意：这里所求的 $s$ 所需满足的条件是 $a$ 的限制，而**不只是**小 A 所发现的性质，因为**他发现的性质已经在给出的 $a$ 中体现**。
## 输入格式

**本题有多组数据。**

第一行一个整数 $t$，**表示该测试点编号**。  
第二行一个整数 $T$，**表示数据组数**。

对于每组数据：  
第一行两个整数 $n,m$。  
接下来 $n$ 行，每行 $n$ 个由空格隔开的 0 或 1 描述 $a$。第 $i+1$ 行第 $j$ 个数表示 $a_{i,j}$。

特别的，为了方便读入，**规定 $a_{i,i}=0$**。但你需要知道**它没有任何实际意义**。
## 输出格式

对于每组数据：

如果不存在满足条件的 $s$，输出一行字符串 $\texttt{NO}$。  
否则先输出一行字符串 $\texttt{YES}$，再输出 $n$ 行，每行 $m$ 个由空格隔开的整数，第 $i+1$ 行第 $j$ 个数表示 $s_{i,j}\ (0\leq s_{i,j}\leq 100)$。
## 样例

### 样例输入 #1
```
0
5
5 3
0 1 1 1 1
1 0 1 1 1
1 1 0 1 1
1 1 1 0 1
1 1 1 1 0
2 7
0 1
0 0
5 4
0 1 1 0 1
0 0 0 0 1
0 1 0 0 1
1 1 1 0 1
1 1 1 1 0
3 1
0 1 1
1 0 1
1 1 0
3 2
0 1 0
0 0 1
1 0 0
```
### 样例输出 #1
```
YES
100 99 97
98 100 99
95 97 100
0 98 100
99 99 99
YES
98 100 94 98 72 53 53
97 99 93 97 71 52 52
YES
90 80 70 60
50 40 30 20
60 50 40 30
100 90 80 70
40 60 80 100
NO
NO
```
## 提示

**「Special Judge」**

**本题使用 Special Judge。请认真阅读输出格式，输出格式有误可能导致 UKE 或 WA。**

SPJ 首先会判断你的第一行输出是否与答案相同。  
如果相同且答案为 $\texttt{YES}$，则 SPJ 会判断你的输出是否符合所有限制。  
如果有解且你输出 $\texttt{YES}$，但给出方案错误，你将获得该测试点 $50\%$ 的分数。

你需要满足的限制如下：  
- $0\leq s_{i,j}\leq 100$。
- 对于任意 $i,j\ (i\neq j)$，若 $a_{i,j}=0$，则对于任意 $k\ (1\leq k\leq m)$，有 $s_{i,k}<s_{j,k}$；若 $a_{i,j}=1$，则存在一个 $k\in [1,m]$，使得 $s_{i,k}>s_{j,k}$。

你需要注意的是，所有输出都应严格符合输出格式。如果你对答案的存在性判断正确，但是输出方案时 $s_{i,j}<0$ 或 $s_{i,j}>100$，SPJ 会判定为 WA，得 $0$ 分，而不是 $50\%\ \times$ 该测试点分数。

**「数据范围与约定」**

本题共有 6 个测试点。

- Testcase #0（1 point）：是样例。
- Testcase #1（10 points）：$n=1$。
- Testcase #2（10 points）：$m=1$。
- Testcase #3（30 points）：$m=2$。
- Testcase #4（20 points）：$a_{i,j}=1\ (i\neq j)$。
- Testcase #5（29 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 100$，$a_{i,j}\in\{0,1\}$，$T=50$（除 Testcase #0）。  
对于 $a$ 的限制：若 $a_{i,j}=a_{i,k}=0$，则 $a_{j,k}$ 和 $a_{k,j}$ 中至少有一个为 $0$；若 $a_{i,k}=a_{j,k}=0$，则 $a_{i,j}$ 和 $a_{j,i}$ 中至少有一个为 $0$。  
对于所有测试点，**时间限制 500ms，空间限制 16MB。**

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) A2。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。


---

---
title: "[CoE R4 B/Stoi2041] 龙拳"
layout: "post"
diff: 提高+/省选-
pid: P8302
tag: ['模拟', '数学', '数论', '洛谷原创', 'O2优化', '枚举', '洛谷月赛']
---
# [CoE R4 B/Stoi2041] 龙拳
## 题目背景

![](bilibili:BV1fx411N7bU?page=28)
## 题目描述

对于 $n \in \mathbb{Z_{\ge 2}}$，设 $g(n)$ 为 $n$ 的小于 $n$ 的最大约数，如 $g(7) = 1, g(12) = 6$。

定义 $f(n) = n + g(n)$。记 $f^{(0)}(n)=n$，且对 $m \in \mathbb{Z_{\ge 0}}$ 有 $f^{(m+1)}(n)=f(f^{(m)}(n))$。

多次询问，每次询问给定正整数 $n,k$，求最小的自然数 $m_0$，使得对于任意 $m \ge m_0$，均有 $f^{(m)}(n) \mid f^{(m+k)}(n)$。

若不存在这样的 $m_0$，则令 $m_0=-1$。
## 输入格式

第一行一个正整数 $T$ 表示询问次数。

接下来 $T$ 行，每行两个正整数 $n,k$，表示一次询问。
## 输出格式

对于每组询问输出一个整数表示答案。
## 样例

### 样例输入 #1
```
2
2 3
3 4

```
### 样例输出 #1
```
0
-1

```
## 提示

### 样例解释

当 $n=2,k=3$ 时，$m_0=0$。

当 $n=3,k=4$ 时不存在满足条件的 $m_0$。

---

### 数据规模

**本题采用捆绑测试。**

- 子任务 $1$（$1$ 分）：$T=k=1$；
- 子任务 $2$（$12$ 分）：$T,n,k \le 10$；
- 子任务 $3$（$24$ 分）：$T \le 10,n \le 10^5$；
- 子任务 $4$（$36$ 分）：$T \le 10^3$；
- 子任务 $5$（$27$ 分）：无特殊限制。

对于 $100\%$ 的数据，保证 $1 \le T \le 2 \times 10^6$，$2 \le n \le 3 \times 10^7$，$1 \le k \le 10^9$。



---

---
title: "[蓝桥杯 2021 国 A] 冰山"
layout: "post"
diff: 提高+/省选-
pid: P8767
tag: ['模拟', '堆', '2021', '蓝桥杯国赛']
---
# [蓝桥杯 2021 国 A] 冰山
## 题目描述

一片海域上有一些冰山，第 $i$ 座冰山的体积为 $V_{i}$ 。

随着气温的变化，冰山的体积可能增大或缩小。第 $i$ 天, 每座冰山的变化量都是 $X_{i}$。当 $X_{i}>0$ 时，所有冰山体积增加 $X_{i}$；当 $X_{i}<0$ 时，所有冰山体积减少 $-X_{i}$；当 $X_{i}=0$ 时，所有冰山体积不变。

如果第 $i$ 天某座冰山的体积变化后小于等于 $0$，则冰山会永远消失。

冰山有大小限制 $k$。如果第 $i$ 天某座冰山 $j$ 的体积变化后 $V_{j}$ 大于 $k$，则它会分裂成一个体积为 $k$ 的冰山和 $V_{j}-k$ 座体积为 $1$ 的冰山。

第 $i$ 天结束前（冰山增大、缩小、消失、分裂完成后），会漂来一座体积为 $Y_{i}$ 的冰山（$Y_{i}=0$ 表示没有冰山漂来）。

小蓝在连续的 $m$ 天对这片海域进行了观察，并准确记录了冰山的变化。小蓝想知道, 每天结束时所有冰山的体积之和（包括新漂来的）是多少。

由于答案可能很大，请输出答案除以 $998244353$ 的余数。
## 输入格式

输入的第一行包含三个整数 $n, m, k$, 分别表示初始时冰山的数量、观察的 天数以及冰山的大小限制。

第二行包含 $n$ 个整数 $V_{1}, V_{2}, \cdots, V_{n}$，表示初始时每座冰山的体积。

接下来 $m$ 行描述观察的 $m$ 天的冰山变化。其中第 $i$ 行包含两个整数 $X_{i}, Y_{i}$，意义如前所述。
## 输出格式

输出 $m$ 行，每行包含一个整数，分别对应每天结束时所有冰山的体积之和除以 $998244353$ 的余数。 
## 样例

### 样例输入 #1
```
1 3 6
1
6 1
2 2
-1 1
```
### 样例输出 #1
```
8
16
11
```
## 提示

**【样例说明】**

在本样例说明中, 用 $\left[a_{1}, a_{2}, \cdots, a_{n}\right]$ 来表示每座冰山的体积。

初始时的冰山为 [1]。

第 $1$ 天结束时，有 $3$ 座冰山： $[1,1,6]$ 。

第 $2$ 天结束时，有 $6$ 座冰山： $[1,1,2,3,3,6]$ 。

第 $3$ 天结束时，有 $5$ 座冰山： $[1,1,2,2,5]$ 。

**【评测用例规模与约定】**

对于 $40 \%$ 的评测用例, $n, m, k \leq 2000$;

对于 $60 \%$ 的评测用例, $n, m, k \leq 20000$;

对于所有评测用例, $1 \leq n, m \leq 10^5,1 \leq k \leq 10^{9}, 1 \leq V_{i} \leq k, 0 \leq Y_{i} \leq k$, $-k \leq X_{i} \leq k$ 。 

蓝桥杯 2021 国赛 A 组 G 题。


---

---
title: "[蓝桥杯 2022 省 A] 扫描游戏"
layout: "post"
diff: 提高+/省选-
pid: P8777
tag: ['模拟', '计算几何', '2022', '排序', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 扫描游戏
## 题目描述

有一根围绕原点 $O$ 顺时针旋转的棒 $OA$，初始时指向正上方（Y 轴正向）。平面中有若干物件，第 $i$ 个物件的坐标为 $\left(x_{i}, y_{i}\right)$，价值为 $z_{i}$。当棒扫到某个物件时，棒的长度会瞬间增长 $z_{i}$，且物件瞬间消失（棒的顶端恰好碰到物件也视为扫到)，如果此时增长完的棒又额外碰到了其他物件，也按上述方式消去（它和上述那个点视为同时消失）。

如果将物件按照消失的时间排序，则每个物件有一个排名，同时消失的物件排名相同，请输出每个物件的排名，如果物件永远不会消失则输出 $-1$。
## 输入格式

输入第一行包含两个整数 $n$、$L$，用一个空格分隔，分别表示物件数量和棒的初始长度。

接下来 $n$ 行每行包含第三个整数 $x_{i}, y_{i}, z_{i}$。

注意存在 $(x_{i}, y_{i})=(0,0)$ 的情况，这些点视为一开始就立刻被碰到。
## 输出格式

输出一行包含 $n$ 整数，相邻两个整数间用一个空格分隔，依次表示每个物件的排名。
## 样例

### 样例输入 #1
```
5 2
0 1 1
0 3 2
4 3 5
6 8 1
-51 -33 2
```
### 样例输出 #1
```
1 1 3 4 -1
```
## 提示

对于 $30 \%$ 的评测用例，$1 \leq n \leq 500$ ；

对于 $60 \%$ 的评测用例，$1 \leq n \leq 5000$;

对于所有评测用例，$1 \leq n \leq 2\times10^5,-10^{9} \leq x_{i}, y_{i} \leq 10^{9}, 1 \leq L, z_{i} \leq 10^{9}$ 。 

样蓝桥杯 2022 省赛 A 组 H 题。


---

---
title: "[USACO22DEC] Mountains G"
layout: "post"
diff: 提高+/省选-
pid: P8904
tag: ['模拟', '数学', '线段树', 'USACO', '2022']
---
# [USACO22DEC] Mountains G
## 题目描述

沿着 Farmer John 的农场边缘有 $N(1 \le N \le 2000)$ 座排成一行等间隔分布的山。这些山可以用一个高度数组 $h_1,h_2, \cdots ,h_N$ 表示。对于山 $i$，如果没有一座山严格高于连接山 $j$ 和 $i$ 山顶的视线，则可以看到山 $j$。形式化地说，对于两座山 $i<j$，如果不存在 $k$ 使得 $i<k<j$ 并且 $(k,h_k)$ 高于连接 $(i,h_i)$ 和 $(j,h_j)$ 的线段，则这两座山之间互相可以看到对方。给定 $Q(1 \le Q \le 2000)$ 次更新操作，每次更新增加一座山的高度。求每次更新后可以互相看到的山的无序对数。 
## 输入格式

输入的第一行包含 $N$。

第 $2$ 行包含 $N$ 个高度 $h_1,h_2,\cdots,h_N$（对每一个 $i$，有 $0 \le h_i \le 10^9$）。

第 $3$ 行包含 $Q$。

第 $4$ 到 $3+Q$ 行每行包含 $x,y(1 \le x \le N,1 \le y)$，其中 $x$ 为山的编号，$y$ 是山增加的高度。输入保证这座山更新后的高度不超过 $10^9$。 
## 输出格式

输出 $Q$ 行，包含每次更新后可以互相看到的山的无序对数。 
## 样例

### 样例输入 #1
```
5
2 4 3 1 5
3
4 3
1 3
3 2
```
### 样例输出 #1
```
7
10
7
```
## 提示

### 样例 1 解释

初始时，以下的山之间可以互相看到：$(1,2)$，$(2,3)$，$(2,5)$，$(3,4)$，$(3,5)$，$(4,5)$，共 $6$ 对。

第一次更新后，山 $4$ 的高度为 $4$，这不会阻挡现有的可见性，但使得山 $4$ 现在可以看到山 $2$，从而使得答案变为 $7$。

第二次更新后，山 $1$ 的高度为 $5$，这不会阻挡现有的可见性，但使得山 $1$ 现在可以看到山 $3$，$4$ 和 $5$，从而使得答案变为 $10$。

第三次更新后，山 $3$ 的高度为 $5$，阻挡了山 $1$ 看到山 $4$，阻挡了山 $2$ 看到山 $4$ 和 $5$，同时由于该山本就可以看到其他所有山，所以并没有使得该山看到更多的山，从而使得答案变为 $7$。

### 测试点性质

 - 测试点 $2-5$ 满足 $N,Q \le 100$。
 - 测试点 $6-11$ 满足 $Q \le 10$。
 - 测试点 $12-21$ 没有额外性质。


---

