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
title: "[NOIP 2003 提高组] 传染病控制"
layout: "post"
diff: 提高+/省选-
pid: P1041
tag: ['搜索', '2003', 'NOIP 提高组']
---
# [NOIP 2003 提高组] 传染病控制
## 题目背景

本题是错题，后来被证明没有靠谱的多项式复杂度的做法。测试数据非常的水，各种玄学做法都可以通过，不代表算法正确。因此本题题目和数据仅供参考。

[关于此类题目的详细内容](https://www.luogu.com.cn/paste/isdgwj5l)

---

近来，一种新的传染病肆虐全球。蓬莱国也发现了零星感染者，为防止该病在蓬莱国大范围流行，该国政府决定不惜一切代价控制传染病的蔓延。不幸的是，由于人们尚未完全认识这种传染病，难以准确判别病毒携带者，更没有研制出疫苗以保护易感人群。于是，蓬莱国的疾病控制中心决定采取切断传播途径的方法控制疾病传播。经过 WHO（世界卫生组织）以及全球各国科研部门的努力，这种新兴传染病的传播途径和控制方法已经研究清楚，剩下的任务就是由你协助蓬莱国疾控中心制定一个有效的控制办法。

## 题目描述

研究表明，这种传染病的传播具有两种很特殊的性质；

第一是它的传播途径是树型的，一个人 $X$ 只可能被某个特定的人 $Y$ 感染，只要 $Y$ 不得病，或者是 $XY$ 之间的传播途径被切断，则 $X$ 就不会得病。


第二是，这种疾病的传播有周期性，在一个疾病传播周期之内，传染病将只会感染一代患者，而不会再传播给下一代。


这些性质大大减轻了蓬莱国疾病防控的压力，并且他们已经得到了国内部分易感人群的潜在传播途径图（一棵树）。但是，麻烦还没有结束。由于蓬莱国疾控中心人手不够，同时也缺乏强大的技术，以致他们在一个疾病传播周期内，只能设法切断一条传播途径，而没有被控制的传播途径就会引起更多的易感人群被感染（也就是与当前已经被感染的人有传播途径相连，且连接途径没有被切断的人群）。当不可能有健康人被感染时，疾病就中止传播。所以，蓬莱国疾控中心要制定出一个切断传播途径的顺序，以使尽量少的人被感染。


你的程序要针对给定的树，找出合适的切断顺序。


## 输入格式

输入格式：  
第一行是两个整数 $n$ 和 $p$。  
接下来 $p$ 行，每一行有 $2$ 个整数 $i$ 和 $j$，表示节点 $i$ 和 $j$ 间有边相连。（意即，第 $i$ 人和第 $j$ 人之间有传播途径相连）。其中节点 $1$ 是已经被感染的患者。

## 输出格式

$1$ 行，总共被感染的人数。

## 样例

### 样例输入 #1
```
7 6
1 2
1 3
2 4
2 5
3 6
3 7

```
### 样例输出 #1
```
3

```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 300$。

**【题目来源】**

NOIP 2003 提高组第四题


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
title: "[NOIP 2006 提高组] 2^k进制数"
layout: "post"
diff: 提高+/省选-
pid: P1066
tag: ['数学', '高精度', '2006', 'NOIP 提高组', '进制']
---
# [NOIP 2006 提高组] 2^k进制数
## 题目描述

设 $r$ 是个 $2^k$ 进制数，并满足以下条件：

- $r$ 至少是个 $2$ 位的 $2^k$ 进制数。

- 作为 $2^k$ 进制数，除最后一位外，$r$ 的每一位严格小于它右边相邻的那一位。

- 将 $r$ 转换为二进制数 $q$ 后，则 $q$ 的总位数不超过 $w$。

在这里，正整数 $k,w$ 是事先给定的。

问：满足上述条件的不同的 $r$ 共有多少个？

我们再从另一角度作些解释：设 $S$ 是长度为 $w$ 的 $01$ 字符串（即字符串 $S$ 由 $w$ 个 $0$ 或 $1$ 组成），$S$ 对应于上述条件三中的 $q$。将 $S$ 从右起划分为若干个长度为 $k$ 的段，每段对应一位 $2^k$ 进制的数，如果 $S$ 至少可分成 $2$ 段，则 $S$ 所对应的二进制数又可以转换为上述的 $2^k$ 进制数 $r$。

例：设 $k=3,w=7$。则 $r$ 是个八进制数（ $2^3=8$ ）。由于 $w=7$，长度为 $7$ 的 $01$ 字符串按 $3$ 位一段分，可分为 $3$ 段（即 $1,3,3$，左边第一段只有一个二进制位），则满足条件的八进制数有：

$2$ 位数：  
高位为 $1$：$6$ 个（即 $12,13,14,15,16,17$ ）,   
高位为 $2$：$5$ 个，  
…，  
高位为 $6$：$1$ 个（即 $67$ ）。  
共 $6+5+…+1=21$ 个。

$3$ 位数：  
高位只能是 $1$，  
第 $2$ 位为 $2$：$5$ 个（即 $123,124,125,126,127$ ），  
第 $2$ 位为 $3$：$4$ 个，  
…，    
第 $2$ 位为 $6$：$1$ 个（即 $167$ ）。  
共 $5+4+…+1=15$ 个。

所以，满足要求的 $r$ 共有 $36$ 个。

## 输入格式

一行两个正整数 $k,w$ 用一个空格隔开：

## 输出格式

一行一个个正整数，为所求的计算结果。  
即满足条件的不同的 $r$ 的个数（用十进制数表示），要求不得有前导零，各数字之间不得插入数字以外的其他字符（例如空格、换行符、逗号等）。

（提示：作为结果的正整数可能很大，但不会超过 $200$ 位）

## 样例

### 样例输入 #1
```
3 7
```
### 样例输出 #1
```
36
```
## 提示

【数据范围】  
$1\le k \le 9$    
$1\le w \le 3\times 10^4$

NOIP 2006 提高组 第四题



---

---
title: "[NOIP 2009 普及组] 道路游戏"
layout: "post"
diff: 提高+/省选-
pid: P1070
tag: ['动态规划 DP', '2009', 'NOIP 普及组']
---
# [NOIP 2009 普及组] 道路游戏
## 题目描述

小新正在玩一个简单的电脑游戏。

游戏中有一条环形马路，马路上有 $n$ 个机器人工厂，两个相邻机器人工厂之间由一小段马路连接。小新以某个机器人工厂为起点，按顺时针顺序依次将这 $n$ 个机器人工厂编号为 $1\sim n$，因为马路是环形的，所以第 $n$ 个机器人工厂和第 $1$ 个机器人工厂是由一段马路连接在一起的。小新将连接机器人工厂的这 $n$ 段马路也编号为 $1\sim n$，并规定第 $i$ 段马路连接第 $i$ 个机器人工厂和第 $i+1$ 个机器人工厂（$1\le i\le n-1$），第 $n$ 段马路连接第 $n$ 个机器人工厂和第 $1$ 个机器人工厂。

游戏过程中，每个单位时间内，每段马路上都会出现一些金币，金币的数量会随着时间发生变化，即不同单位时间内同一段马路上出现的金币数量可能是不同的。小新需要机器人的帮助才能收集到马路上的金币。所需的机器人必须在机器人工厂用一些金币来购买，机器人一旦被购买，便会沿着环形马路按顺时针方向一直行走，在每个单位时间内行走一次，即从当前所在的机器人工厂到达相邻的下一个机器人工厂，并将经过的马路上的所有金币收集给小新，例如，小新在 $i$（$1\le i\le n$）号机器人工厂购买了一个机器人，这个机器人会从 $i$ 号机器人工厂开始，顺时针在马路上行走，第一次行走会经过 $i$ 号马路，到达 $i+1$ 号机器人工厂（如果 $i=n$，机器人会到达第 $1$ 个机器人工厂），并将 $i$ 号马路上的所有金币收集给小新。游戏中，环形马路上不能同时存在 $2$ 个或者 $2$ 个以上的机器人，并且每个机器人最多能够在环形马路上行走 $p$ 次。小新购买机器人的同时，需要给这个机器人设定行走次数，行走次数可以为 $1\sim p$ 之间的任意整数。当马路上的机器人行走完规定的次数之后会自动消失，小新必须立刻在任意一个机器人工厂中购买一个新的机器人，并给新的机器人设定新的行走次数。

以下是游戏的一些补充说明：

1. 游戏从小新第一次购买机器人开始计时。
2. 购买机器人和设定机器人的行走次数是瞬间完成的，不需要花费时间。
3. 购买机器人和机器人行走是两个独立的过程，机器人行走时不能购买机器人，购买完机器人并且设定机器人行走次数之后机器人才能行走。
4. 在同一个机器人工厂购买机器人的花费是相同的，但是在不同机器人工厂购买机器人的花费不一定相同。
5. 购买机器人花费的金币，在游戏结束时再从小新收集的金币中扣除，所以在游戏过程中小新不用担心因金币不足，无法购买机器人而导致游戏无法进行。也因为如此，游戏结束后，收集的金币数量可能为负。

现在已知每段马路上每个单位时间内出现的金币数量和在每个机器人工厂购买机器人需要的花费，请你告诉小新，经过 $m$ 个单位时间后，扣除购买机器人的花费，小新最多能收集到多少金币。

## 输入格式

第一行 $3$ 个正整数 $n,m,p$，意义如题目所述。

接下来的 $n$ 行，每行有 $m$ 个正整数，每两个整数之间用一个空格隔开，其中第 $i$ 行描述了 $i$ 号马路上每个单位时间内出现的金币数量（$1\le $ 金币数量 $\le 100$），即第 $i$ 行的第 $j$（$1\le j\le m$）个数表示第 $j$ 个单位时间内 $i$ 号马路上出现的金币数量。

最后一行，有 $n$ 个整数，每两个整数之间用一个空格隔开，其中第 $i$ 个数表示在 $i$ 号机器人工厂购买机器人需要花费的金币数量（$1\le $ 金币数量 $\le 100$）。
## 输出格式

共一行，包含 $1$ 个整数，表示在 $m$ 个单位时间内，扣除购买机器人花费的金币之后，小新最多能收集到多少金币。
## 样例

### 样例输入 #1
```
2 3 2 
1 2 3 
2 3 4 
1 2
```
### 样例输出 #1
```
5
```
## 提示

对于 $40\%$ 的数据，$2\le n\le 40$，$1\le m\le 40$。

对于 $90\%$ 的数据，$2\le n\le 200$，$1\le m\le 200$。

对于 $100\%$ 的数据，$2\le n\le 1000$，$1\le m\le 1000$，$1\le p\le m$。

NOIP 2009 普及组 第四题



---

---
title: "[NOIP 2009 提高组] 最优贸易"
layout: "post"
diff: 提高+/省选-
pid: P1073
tag: ['动态规划 DP', '搜索', '图论', '2009', 'NOIP 提高组', '最短路', '强连通分量']
---
# [NOIP 2009 提高组] 最优贸易
## 题目背景

本题原题数据极弱，Subtask 0 中的测试点为原题测试点，Subtask 1 中的测试点为 Hack 数据。
## 题目描述

$C$ 国有 $n$ 个大城市和 $m$ 条道路，每条道路连接这 $n$ 个城市中的某两个城市。任意两个城市之间最多只有一条道路直接相连。这 $m$ 条道路中有一部分为单向通行的道路，一部分为双向通行的道路，双向通行的道路在统计条数时也计为 $1$ 条。

$C$ 国幅员辽阔，各地的资源分布情况各不相同，这就导致了同一种商品在不同城市的价格不一定相同。但是，同一种商品在同一个城市的买入价和卖出价始终是相同的。

商人阿龙来到 $C$ 国旅游。当他得知同一种商品在不同城市的价格可能会不同这一信息之后，便决定在旅游的同时，利用商品在不同城市中的差价赚回一点旅费。设 $C$ 国 $n$ 个城市的标号从 $1\sim n$，阿龙决定从 $1$ 号城市出发，并最终在 $n$ 号城市结束自己的旅行。在旅游的过程中，任何城市可以重复经过多次，但不要求经过所有 $n$ 个城市。阿龙通过这样的贸易方式赚取旅费：他会选择一个经过的城市买入他最喜欢的商品――水晶球，并在之后经过的另一个城市卖出这个水晶球，用赚取的差价当做旅费。由于阿龙主要是来 $C$ 国旅游，他决定这个贸易只进行最多一次，当然，在赚不到差价的情况下他就无需进行贸易。

假设 $C$ 国有 $5$ 个大城市，城市的编号和道路连接情况如下图，单向箭头表示这条道路为单向通行，双向箭头表示这条道路为双向通行。

![](https://cdn.luogu.com.cn/upload/image_hosting/flre534z.png)

假设 $1\sim n$ 号城市的水晶球价格分别为 $4,3,5,6,1$。

阿龙可以选择如下一条线路：$1\to2\to3\to5$，并在 $2$ 号城市以 $3$ 的价格买入水晶球，在 $3$ 号城市以 $5$ 的价格卖出水晶球，赚取的旅费数为 $2$。

阿龙也可以选择如下一条线路：$1\to4\to5\to4\to5$，并在第 $1$ 次到达 $5$ 号城市时以 $1$ 的价格买入水晶球，在第 $2$ 次到达 $4$ 号城市时以 $6$ 的价格卖出水晶球，赚取的旅费数为 $5$。

现在给出 $n$ 个城市的水晶球价格，$m$ 条道路的信息（每条道路所连接的两个城市的编号以及该条道路的通行情况）。请你告诉阿龙，他最多能赚取多少旅费。
## 输入格式

第一行包含 $2$ 个正整数 $n$ 和 $m$，中间用一个空格隔开，分别表示城市的数目和道路的数目。

第二行 $n$ 个正整数，每两个整数之间用一个空格隔开，按标号顺序分别表示这 $n$ 个城市的商品价格。

接下来 $m$ 行，每行有 $3$ 个正整数 $x,y,z$，每两个整数之间用一个空格隔开。如果 $z=1$，表示这条道路是城市 $x$ 到城市 $y$ 之间的单向道路；如果 $z=2$，表示这条道路为城市 $x$ 和城市 $y$ 之间的双向道路。


## 输出格式

一个整数，表示最多能赚取的旅费。如果没有进行贸易，则输出 $0$。
## 样例

### 样例输入 #1
```
5 5 
4 3 5 6 1 
1 2 1 
1 4 1 
2 3 2 
3 5 1 
4 5 2 
```
### 样例输出 #1
```
5
```
## 提示

【数据范围】

输入数据保证 $1$ 号城市可以到达 $n$ 号城市。

对于 $10\%$ 的数据，$1\leq n\leq 6$。

对于 $30\%$ 的数据，$1\leq n\leq 100$。

对于 $50\%$ 的数据，不存在一条旅游路线，可以从一个城市出发，再回到这个城市。

对于 $100\%$ 的数据，$1\leq n\leq 100000$，$1\leq m\leq 500000$，$1\leq  x,y\leq  n$，$1\leq  z\leq  2$，$1\leq $ 各城市的编号 $\leq  n$。

水晶球价格 $\leq 100$。

NOIP 2009 提高组 第三题


---

---
title: "[NOISG 2023 Qualification] Burgers"
layout: "post"
diff: 提高+/省选-
pid: P10730
tag: ['动态规划 DP', '2023', 'NOISG（新加坡）']
---
# [NOISG 2023 Qualification] Burgers
## 题目描述

龙虾 Kai 经营着一家汉堡店。做一个汉堡需要 $n$ 种原料，第 $i$ 种原料他有 $x_i$ 份。

他手中有两种汉堡食谱，这两种汉堡对于第 $i$ 种原料分别需要 $a_i$ 份和 $b_i$ 份来制作。

计算 Kai 最多能用这些原料制作多少个汉堡。
## 输入格式

第一行，一个正整数 $n$。

第二行 $n$ 个整数，表示 $x$。

第三行 $n$ 个整数，表示 $a$。

第四行 $n$ 个整数，表示 $b$。
## 输出格式

一行一个整数表示最多能制作多少个汉堡。
## 样例

### 样例输入 #1
```
3
14 10 100
3 1 1
2 3 1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
2
83 72
1 3
1 3
```
### 样例输出 #2
```
24
```
## 提示

### 【样例 #1 解释】

Kai 可以制作 $3$ 个第一种汉堡和 $2$ 个第二种汉堡。

### 【样例 #2 解释】

Kai 可以制作 $24$ 个第一种汉堡或 $24$ 个第二种汉堡。

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$9$|对于所有的 $1 \le i \le n$，$a_i=b_i$。|
|$2$|$17$|$n,x_i\le100$|
|$3$|$25$|$n,x_i\le1500$|
|$4$|$49$|无|

对于 $100\%$ 的数据，$1\le n\le100000,1\le x_i,a_i,b_i\le10^9$。


---

---
title: "[NOISG 2019 Prelim] Square or Rectangle?"
layout: "post"
diff: 提高+/省选-
pid: P10735
tag: ['数学', '2019', '二分', '交互题', 'Special Judge', 'NOISG（新加坡）']
---
# [NOISG 2019 Prelim] Square or Rectangle?
## 题目背景

翻译自 [NOISG2019 Prelim D.Square or Rectangle?](https://github.com/noisg/sg_noi_archive/blob/master/2019_prelim/)。

请注意，本题为**交互题**，请**尽量使用 C++ 进行作答**。同时，你**只需要实现题目中要求的函数**。**不要将答案输出在标准输出。**
## 题目描述

现在有一个 $N\times N$ 的网格，网格内**有一个至少占网格总大小 $4\%$ 的矩形**。但是，你现在不知道这个矩形是长方形还是正方形，你需要**定义一个函数**来完成这个问题。

### 【实现细节】
你需要定义以下函数：

`bool am_i_square(int N, int Q)`

- $N$：网格的大小
- $Q$：能询问评测机的次数。

为了确定形状，你可以向评测机至多调用 $Q$ 次 `bool inside_shape(int X, int Y)` 函数。调用这个来询问评测机方格 $(X,Y)$ 是否在这个矩形中。

一旦你确定了形状，你就可以返回一个 `bool` 类型的量，代表这个矩形是否为**正方形**。

评测机会调用你的函数 $T$ 次。$T$ 的大小见【数据范围与评测方法】。
## 输入格式

见【实现细节】。
## 输出格式

见【实现细节】。
## 提示

### 【样例】
考虑以下调用：

![](https://cdn.luogu.com.cn/upload/image_hosting/so2eprl8.png)

`am_i_square(5, 25)`

这表示这是一个 $5 \times 5$ 大小的网格，你可以调用至多 $25$ 次。

`inside_shape(3, 3) = true`

这询问了方格 $(3,3)$ 是否在矩形内，它在正方形的正中间，所以返回 `true`。

`inside_shape(5, 4) = false`

这询问了方格 $(5,4)$ 是否在矩形内，它不在正方形内，所以返回 `false`。

`inside_shape(1, 1) = false`

这询问了方格 $(1,1)$ 是否在矩形内，它不在正方形内，所以返回 `false`。

`inside_shape(2, 4) = true`

这询问了方格 $(2,4)$ 是否在矩形内，它在正方形的左下角，所以返回 `true`。

综上，我们可以确定这是一个正方形，所以该函数返回 `true`。
### 【数据范围与评测方法】
对于 $100\%$ 的测试点：$N=100,1\leq T \leq 1000$。
| $\text{Subtask}$ | 分值 | 附加条件 |
| :----------: | :----------: | :----------: |
| $0$ | $14$ | $Q=10^4$ |
| $1$ | $19$ | $Q=100$ |
| $2$ | $18$ | $Q=40$，图形至少占网格总大小的 $25\%$ |
| $3$ | $49$ | $Q=50$，得分见下文 |
### 【Subtask 3 的计分方法】
记你在所有调用中最大使用了 $q$ 次询问。
- 若 $q >50$，你得到 $0$ 分。
- 若 $34 \leq q \leq 50$，你得到 $40-30\times \frac{q-34}{17}$ 的分数。
- 若 $q \leq 33$，你得到满分。
### 【提示】
请在你的函数前加上以下内容：
```cpp
#include <bits/stdc++.h>
using namespace std;
extern "C" bool inside_shape(int x,int y);
```
同时，请在你的 `bool am_i_square(int N, int Q)` 前加上`extern "C" `。


---

---
title: "[NOIP 2009 提高组] 靶形数独"
layout: "post"
diff: 提高+/省选-
pid: P1074
tag: ['搜索', '2009', 'NOIP 提高组', '剪枝', '位运算']
---
# [NOIP 2009 提高组] 靶形数独
## 题目背景

**此为远古题，不保证存在可以通过任意符合要求的输入数据的程序**。
## 题目描述

小城和小华都是热爱数学的好学生，最近，他们不约而同地迷上了数独游戏，好胜的他们想用数独来一比高低。但普通的数独对他们来说都过于简单了，于是他们向 Z 博士请教，Z 博士拿出了他最近发明的“靶形数独”，作为这两个孩子比试的题目。

靶形数独的方格同普通数独一样，在 $9$ 格宽且 $9$ 格高的大九宫格中有 $9$ 个 $3$ 格宽且 $3$ 格高的小九宫格（用粗黑色线隔开的）。在这个大九宫格中，有一些数字是已知的，根据这些数字，利用逻辑推理，在其他的空格上填入 $1$ 到 $9$ 的数字。每个数字在每个小九宫格内不能重复出现，每个数字在每行、每列也不能重复出现。但靶形数独有一点和普通数独不同，即每一个方格都有一个分值，而且如同一个靶子一样，离中心越近则分值越高。（如图）

![](https://cdn.luogu.com.cn/upload/image_hosting/dhvuc32i.png)

上图具体的分值分布是：最里面一格（黄色区域）为 $10$ 分，黄色区域外面的一圈（红色区域）每个格子为 $9$ 分，再外面一圈（蓝色区域）每个格子为 $8$ 分，蓝色区域外面一圈（棕色区域）每个格子为 $7$ 分，最外面一圈（白色区域）每个格子为 $6$ 分，如上图所示。比赛的要求是：每个人必须完成一个给定的数独（每个给定数独可能有不同的填法），而且要争取更高的总分数。而这个总分数即每个方格上的分值和完成这个数独时填在相应格上的数字的乘积的总和

总分数即每个方格上的分值和完成这个数独时填在相应格上的数字的乘积的总和。如图，在以下的这个已经填完数字的靶形数独游戏中，总分数为 $2829$。游戏规定，将以总分数的高低决出胜负。

![](https://cdn.luogu.com.cn/upload/image_hosting/yx82mmnc.png)

由于求胜心切，小城找到了善于编程的你，让你帮他求出，对于给定的靶形数独，能够得到的最高分数。

## 输入格式

一共 $9$ 行。每行 $9$ 个整数（每个数都在 $0 \sim 9$ 的范围内），表示一个尚未填满的数独方格，未填的空格用“$0$”表示。每两个数字之间用一个空格隔开。

## 输出格式

输出共 $1$ 行。输出可以得到的靶形数独的最高分数。如果这个数独无解，则输出整数 $-1$。

## 样例

### 样例输入 #1
```
7 0 0 9 0 0 0 0 1 
1 0 0 0 0 5 9 0 0 
0 0 0 2 0 0 0 8 0 
0 0 5 0 2 0 0 0 3 
0 0 0 0 0 0 6 4 8 
4 1 3 0 0 0 0 0 0 
0 0 7 0 0 2 0 9 0 
2 0 1 0 6 0 8 0 4 
0 8 0 5 0 4 0 1 2

```
### 样例输出 #1
```
2829
```
### 样例输入 #2
```
0 0 0 7 0 2 4 5 3 
9 0 0 0 0 8 0 0 0 
7 4 0 0 0 5 0 1 0 
1 9 5 0 8 0 0 0 0 
0 7 0 0 0 0 0 2 5 
0 3 0 5 7 9 1 0 8 
0 0 0 6 0 1 0 0 0 
0 6 0 9 0 0 0 0 1 
0 0 0 0 0 0 0 0 6
```
### 样例输出 #2
```
2852
```
## 提示

#### 数据规模与约定

- 对于 $40\%$ 的数据，数独中非 $0$ 数的个数不少于 $30$；
- 对于 $80\%$ 的数据，数独中非 $0$ 数的个数不少于 $26$；
- 对于 $100\%$ 的数据，数独中非 $0$ 数的个数不少于 $24$。

NOIP 2009 提高组 第三题


---

---
title: "[NOIP 2004 提高组] 虫食算"
layout: "post"
diff: 提高+/省选-
pid: P1092
tag: ['搜索', '数学', '2004', 'NOIP 提高组']
---
# [NOIP 2004 提高组] 虫食算
## 题目描述

所谓虫食算，就是原先的算式中有一部分被虫子啃掉了，需要我们根据剩下的数字来判定被啃掉的数字。来看一个简单的例子：

$$\begin{aligned}
 \verb!43#9865#045! \\
+\qquad \verb!8468#6633! \\[-1em]\underline{\kern{8em}} \\
 \verb!44445509678! \\
\end{aligned}$$

其中 `#` 号代表被虫子啃掉的数字。根据算式，我们很容易判断：第一行的两个数字分别是 $5$ 和 $3$，第二行的数字是 $5$。

现在，我们对问题做两个限制：

首先，我们只考虑加法的虫食算。这里的加法是 $n$ 进制加法，算式中三个数都有 $n$ 位，允许有前导的 $0$。

其次，虫子把所有的数都啃光了，我们只知道哪些数字是相同的，我们将相同的数字用相同的字母表示，不同的数字用不同的字母表示。如果这个算式是 $n$ 进制的，我们就取英文字母表的前 $n$ 个大写字母来表示这个算式中的 $0$ 到 $n - 1$ 这 $n$ 个不同的数字：但是这 $n$ 个字母并不一定顺序地代表 $0$ 到 $n-1$。输入数据保证 $n$ 个字母分别至少出现一次。

$$\begin{aligned}
 \verb!BADC! \\
+\quad \verb!CBDA! \\[-1em]\underline{\kern{4em}} \\
 \verb!DCCC! \\
\end{aligned}$$

上面的算式是一个4进制的算式。很显然，我们只要让 $\verb!ABCD!$ 分别代表 $0123$，便可以让这个式子成立了。你的任务是，对于给定的 $n$ 进制加法算式，求出 $n$ 个不同的字母分别代表的数字，使得该加法算式成立。输入数据保证有且仅有一组解。

## 输入格式

输入的第一行是一个整数 $n$，代表进制数。

第二到第四行，每行有一个由大写字母组成的字符串，分别代表两个加数以及和。这 $3$ 个字符串左右两端都没有空格，从左到右依次代表从高位到低位，并且恰好有 $n$ 位。

## 输出格式

输出一行 $n$ 个用空格隔开的整数，分别代表 $A,B, \dots$ 代表的数字。

## 样例

### 样例输入 #1
```
5
ABCED
BDACE
EBBAA

```
### 样例输出 #1
```
1 0 3 4 2

```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n \le 10$；
- 对于 $50\%$ 的数据，保证 $n \le 15$；
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 26$。


---

---
title: "[NOISG 2022 Qualification] Tree Cutting"
layout: "post"
diff: 提高+/省选-
pid: P11294
tag: ['树形数据结构', '2022', '深度优先搜索 DFS', '树形 DP', 'NOISG（新加坡）']
---
# [NOISG 2022 Qualification] Tree Cutting
## 题目背景

一个国家有 $N$ 个城市，编号为 $1$ 到 $N$，以及 $N-1$ 条双向公路。通过这些公路，可以从任意一个城市到达另一个城市。

城市 $x$ 和城市 $y$ 之间的距离定义为连接两城市所需经过的公路数。

州长决定拆除一条公路，并新建另一条公路，使得任意两城市之间的最远距离最大化。
## 题目描述

请计算新建公路后，任意两城市之间的最大距离。
## 输入格式

- 第一行包含一个整数 $N$，表示城市的数量。
- 接下来的 $N-1$ 行，每行包含两个整数 $u$ 和 $v$，表示城市 $u$ 和 $v$ 之间有一条双向公路。
## 输出格式

输出一个整数，表示新建公路后任意两城市之间的最大距离。
## 样例

### 样例输入 #1
```
4
1 2
1 3
3 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
6
1 2
2 3
2 5
4 5
5 6
```
### 样例输出 #2
```
5
```
## 提示

【样例解释】

对于样例 $1$，最远距离无法增加，仍然为 $3$。  

对于样例 $2$，可以拆除公路 $2-5$，新建公路 $3-4$，最远路径为 $1-2-3-4-5-6$，其长度为 $5$。

【数据范围】

- $2 \leq N \leq 300,000$
- $1 \leq u, v \leq N$

| 子任务编号 | 分值 | 额外限制条件                             |
| :--------: | :--: | :--------------------------------------: |
| $1$        | $5$  | $N \leq 10$                              |
| $2$        | $10$ | $N \leq 100$                             |
| $3$        | $15$ | $N \leq 3000$                            |
| $4$        | $15$ | $N \leq 300,000$，至多一个城市连接至少 $3$ 条公路 |
| $5$        | $55$ | 无额外限制                              |


---

---
title: "[NOISG 2018 Prelim]  Island"
layout: "post"
diff: 提高+/省选-
pid: P11298
tag: ['数学', '图论', '2018', 'Special Judge', 'NOISG（新加坡）']
---
# [NOISG 2018 Prelim]  Island
## 题目背景

翻译自 [NOISG 2018 Prelim C. Island](https://github.com/noisg/sg_noi_archive/tree/master/2018_prelim)。

**本题已启用 Special Judge，满足题目条件的任何答案都将视为正确。保证 SPJ 用时不超过 $1$ 秒**。
## 题目描述

老鼠吱吱发现了一座小岛，这座小岛上的人以捕鱼为生，所以他们的 $n$ 所房子（标号为 $1$ 到 $n$）都在小岛的**边缘**，大家还需要交换各自的鱼，所以有些路在小岛的中间。

为了连接城镇，在岛的内部创建了 $m$ 个路口（标号为 $n+1$ 到 $n+m$）。为了最大限度地降低建设成本，这个岛上**只有 $n+m−1$ 条路**，这样任何两个城镇之间就有且仅有一条路。

换言之，道路网络可以**表示为一棵树**，有 $n$ 个叶子（代表 $n$  所房子）和 $m$ 个非叶子节点（代表 $m$ 个路口）。根据树的性质，这棵树有 $n+m−1$条边（代表 $n+m-1$ 条路）。

此外，**每个路口至少有三条路与之相连**，除了路口外，路不会与其他路相交，也没有桥梁或隧道（它们很贵）。以下是一个有 $37$ 所房子、$20$ 个路口和 $56$ 条道路的岛的参考图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h32hwja1.png)

老鼠吱吱很喜欢这座小岛，但是因为某种原因，它的地图被吹走了。但是吱吱想规划它的行程，所以他想知道小岛房子的位置。

幸运的是，它记录了**每一条道路的起点和终点**的观察记录本还在，现在请你推出，共有几种不同的情况使得小岛房子的位置不同。

**注意小岛是环形的，经过旋转完全一样的顺序视为同一种顺序**。
## 输入格式

第一行两个整数 $n,m$。

接下来 $n+m-1$ 行，每行两个整数 $u,v$，表示这条道路的起点与终点。如 $u \leq n$，则起点是一所房子，否则是一个路口。对 $v$ 同理。
## 输出格式

若干行，第 $i$ 行两个整数 $a_i,b_i$。

假设你的答案由 $k$ 行构成。你的输出表示 答案 $P=a_1^{b_1}a_2^{b_2}\cdots a_k^{b_k}$（也可记作 $\prod_{j=1}^ka_j^{b_j}$）。

你的输出应满足以下要求：
- $0\leq k\leq 10^6$
- $1\leq a_i,b_i\leq 10^{18}$

**如果无解，请什么都不要输出**。
## 样例

### 样例输入 #1
```
5 2
1 7
3 7
6 2
7 4
6 7
5 6
```
### 样例输出 #1
```
3 1
4 1
```
### 样例输入 #2
```
5 1
6 1
6 2
6 3
6 4
6 5
```
### 样例输出 #2
```
3 1
2 3
```
### 样例输入 #3
```
6 3
7 1
7 2
8 3
8 4
9 5
9 6
7 8
9 8
```
### 样例输出 #3
```
24 1
```
## 提示

### 【样例 #1 解释】
有 $12$ 种合法的排列，如下图。

使用其他的方式（如 $4^1\times3^1$）也是可以的。

所有排列如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/847a8hm5.png)
### 【样例 #2 解释】
有 $24$ 种合法的排列，其中一种如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/xrc1rdel.png)

算出答案是 $5!=120$ 的很有可能是因为没有考虑旋转后一样的视为同一种方案的问题。
### 【样例 #3 解释】
有 $24$ 种合法的排列，其中一种如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/d7xgyycj.png)
### 【数据范围】
| $\text{Subtask}$ | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | 样例 |
| $1$ | $7$ | $n+m\leq 2\times 10^5,m\leq1$ |
| $2$ | $20$ | $n+m\leq 2\times 10^5,m\leq10$ |
| $3$ | $31$ | $n+m\leq 10^3$ |
| $4$ | $42$ | $n+m\leq 2\times 10^5$ |

对于 $100\%$ 的数据：
- $2 \leq n,0\leq m$
- $n+m \leq 2\times10^5$


---

---
title: "[NOISG 2020 Qualification] Firefighting"
layout: "post"
diff: 提高+/省选-
pid: P11322
tag: ['2020', 'Special Judge', 'NOISG（新加坡）']
---
# [NOISG 2020 Qualification] Firefighting
## 题目背景

在 Mouseopolis，这座鼠国的大都会，一场大火席卷了整座城市。为了防止类似灾难再次发生，鼠国的国王 Squeaky 决定在鼠国的城镇中建立消防站。
## 题目描述

鼠国由 $N$ 个城镇组成，编号为 $1$ 到 $N$。城镇之间通过 $N-1$ 条双向道路连接，每条道路连接两个城镇，并且道路的长度可能不同。城镇网络保证任何两个城镇之间都可以通过某些道路相连。

为了有效扑灭火灾，国王的顾问认为消防站到火灾发生地点的距离不得超过 $K$ 公里，否则火势将难以控制。然而，建设消防站的成本较高，国王希望尽可能减少消防站的数量。

任务是确定在鼠国的哪些城镇建设消防站，以使得需要建设的消防站数量最少。
## 输入格式

- 第一行包含两个整数 $N$ 和 $K$，分别表示城镇的数量和消防站的最大服务距离。
- 接下来的 $N-1$ 行，每行包含三个整数 $A_i, B_i, D_i$，表示城镇 $A_i$ 和城镇 $B_i$ 之间有一条长度为 $D_i$ 公里的双向道路。
## 输出格式

- 第一行包含一个整数 $F$，表示需要建设的最少消防站数量。
- 第二行包含 $F$ 个整数，表示建设消防站的城镇编号。

可以按任意顺序输出。如果有多种可行方案，输出任意一种即可。
## 样例

### 样例输入 #1
```
9 4
1 2 10
2 3 4
8 9 4
8 7 3
7 3 5
3 4 1
4 5 3
5 6 2
```
### 样例输出 #1
```
4
1 8 3 6
```
### 样例输入 #2
```
9 26
2 1 21
2 9 21
2 8 21
2 3 56
3 4 37
4 5 29
7 6 25
6 4 24
```
### 样例输出 #2
```
4
5 6 2 3
```
### 样例输入 #3
```
3 18
1 2 35
2 3 49
```
### 样例输出 #3
```
3
1 2 3
```
### 样例输入 #4
```
10 3
10 9 1
9 8 1
8 5 1
1 2 1
2 3 1
5 4 1
3 4 1
5 6 1
6 7 1
```
### 样例输出 #4
```
2
4 10
```
## 提示

【样例解释】

对于样例 #1，最少需要在城镇 $1, 8, 3, 6$ 建立消防站，以保证每个城镇到最近的消防站的距离不超过 $4$ 公里。

对于样例 #2，最少需要在城镇 $5, 6, 2, 3$ 建立消防站。

对于样例 #3，必须在每个城镇建立消防站。

对于样例 #4，可以在城镇 $4$ 和 $10$ 建立消防站，或者选择其他符合条件的方案。

【数据范围】

- $1 \leq N \leq 3 \times 10^5$  
- $1 \leq K \leq 10^{15}$  
- $1 \leq A_i, B_i \leq N$  
- $1 \leq D_i \leq 10^9$

| 子任务编号 | 分值       | 限制条件                      |
|:--------:|:---------:|:--------------------------:|
| $1$      | $3$       | $K \leq 20$，且 $D_i \geq 30$ |
| $2$      | $5$       | $N \leq 17, K \leq 17$，且 $D_i = 1$ |
| $3$      | $9$       | $N \leq 17, K \leq 10^6$，且 $D_i \leq 10^4$ |
| $4$      | $19$      | $K \leq 30$，且 $D_i \geq 20$ |
| $5$      | $26$      | $N \leq 3 \times 10^3$     |
| $6$      | $38$      | 无额外限制                 |


---

---
title: "[NOIP2024] 编辑字符串"
layout: "post"
diff: 提高+/省选-
pid: P11361
tag: ['2024', 'NOIP 提高组']
---
# [NOIP2024] 编辑字符串
## 题目描述

小 M 有两个长度为 $n$ 且字符集为 $\{0, 1\}$ 的字符串 $s_1, s_2$。

小 M 希望两个字符串中对应位置字符相同的出现次数尽可能多，即满足 $s_{1,i} = s_{2,i}$ 的 $i(1 \leq i \leq n)$ 尽可能多。为此小 M 有一个字符串编辑工具，这个工具提供的基本操作是在一个字符串中交换两个**相邻**的字符。为了保持字符串的可辨识性，规定两个字符串中的部分字符不能参与交换。小 M 可以用工具对 $s_1$ 或 $s_2$ 进行多次字符交换，其中可以参与交换的字符能够交换任意多次。

现在小 M 想知道，在使用编辑工具后，两个字符串中对应位置字符相同的出现次数最多能有多少。
## 输入格式

**本题包含多组测试数据。**

输入的第一行包含一个整数 $T$，表示测试数据的组数。

接下来包含 $T$ 组数据，每组数据的格式如下：

- 第一行包含一个整数 $n$，表示字符串长度。
- 第二行包含一个长度为 $n$ 且字符集为 $\{0, 1\}$ 的字符串 $s_1$。
- 第三行包含一个长度为 $n$ 且字符集为 $\{0, 1\}$ 的字符串 $s_2$。
- 第四行包含一个长度为 $n$ 且字符集为 $\{0, 1\}$ 的字符串 $t_1$，其中 $t_{1,i}$ 为 $1$ 表示 $s_{1,i}$ 可以参与交换，$t_{1,i}$ 为 $0$ 表示 $s_{1,i}$ 不可以参与交换。
- 第五行包含一个长度为 $n$ 且字符集为 $\{0, 1\}$ 的字符串 $t_2$，其中 $t_{2,i}$ 为 $1$ 表示 $s_{2,i}$ 可以参与交换，$t_{2,i}$ 为 $0$ 表示 $s_{2,i}$ 不可以参与交换。
## 输出格式

对于每组测试数据输出一行，包含一个整数，表示对应的答案。
## 样例

### 样例输入 #1
```
1
6
011101
111010
111010
101101
```
### 样例输出 #1
```
4
```
## 提示

**【样例 1 解释】**

最开始时，$s_1 = \tt{011101}$，第 $4$ 和第 $6$ 个字符不能参与交换；$s_2 = \tt{111010}$，第 $2$ 和第 $5$ 个字符不能参与交换。

考虑如下操作：先交换 $s_{1,1}$ 与 $s_{1,2}$ 得到 $s_1 = \tt{101101}$，再交换 $s_{1,2}$ 与 $s_{1,3}$ 得到 $s_1 = \tt{110101}$，最后交换 $s_{2,3}$ 与 $s_{2,4}$ 得到 $s_2 = \tt{110110}$。此时 $s_1$ 与 $s_2$ 的前 $4$ 个位置上的字符都是相同的。可以证明不存在更好的方案，故输出 $4$。

**【样例 2 解释】**

见附件的 edit/edit2.in 与 edit/edit2.ans。

该样例共有 $10$ 组测试数据，其中第 $i(1 \leq i \leq 10)$ 组测试数据满足数据范围中描述的测试点 $2i - 1$ 的限制。

**【数据范围】**

对于所有的测试数据，保证：$1 \leq T \leq 10$，$1 \leq n \leq 10^5$。

| 测试点编号 | $n\leq$ | 特殊性质 |
| :----------: | :----------: | :----------: |
| $1\sim 4$ | $10$ | 无 |
| $5,6$ | $10^3$ | A |
| $7,8$ | $10^5$ | A |
| $9,10$ | $10^3$ | B |
| $11,12$ | $10^5$ | B |
| $13,14$ | $10^3$ | C |
| $15,16$ | $10^5$ | C |
| $17,18$ | $10^3$ | 无 |
| $19,20$ | $10^5$ | 无 |


- 特殊性质 A：保证 $s_1$ 的所有字符相同。
- 特殊性质 B：保证 $t_1 = t_2$。
- 特殊性质 C：保证 $t_1$ 和 $t_2$ 中各自恰有一个字符  $\tt 0$。


---

---
title: "[NOISG 2023 Finals] Inspections"
layout: "post"
diff: 提高+/省选-
pid: P11534
tag: ['2023', '颜色段均摊（珂朵莉树 ODT）', 'NOISG（新加坡）', '离线处理']
---
# [NOISG 2023 Finals] Inspections
## 题目描述

兔子 Benson 正要造一架飞机！

Benson 的工厂有 $n$ 个机器，由 $1\sim n$ 编号。每台机器会工作一天，且每一天只能有一台机器工作。他需要制造 $m$ 个部件，由 $1\sim m$ 编号。每个部件用两个整数 $l_i, r_i$ 表示，其中 $l_i\leq r_i$。

制造第 $i$ 个部件时，Benson 将依次运行编号为 $l_i, l_i+1,\cdots,r_i$ 的机器。当一台机器结束工作，下一台机器会立即启动。此外，Benson 会依次制造这 $m$ 个部件。当一个部件制造完毕，下一个部件会立即开始制造。

为了保障机器的安全，工厂设有一个检查系数 $s$。若一台机器已经连续 $s$ 或更多天没有启动，那么这次启动前必须对其进行安全检查。特别地，第一次启动某个机器时无需进行安全检查。

Benson 有 $q$ 个询问 $s_1, s_2, \cdots, s_q$。对于每个检查系数 $s_j$，请你帮助他计算完成所有部件所需的检查次数。
## 输入格式

第一行三个正整数 $n, m, q$，用空格隔开。

接下来 $m$ 行，每行两个整数 $l_i,r_i$，描述第 $i$ 个部件。

接下来一行 $q$ 个整数 $s_1,s_2,\cdots,s_q$，表示 $q$ 个检查系数。
## 输出格式

输出一行 $q$ 个整数，表示当检查系数为 $s_j$ 时，所需检查机器的次数。
## 样例

### 样例输入 #1
```
5 3 7
1 3
3 5
2 3
0 1 2 3 4 5 6

```
### 样例输出 #1
```
3 2 2 2 1 0 0 

```
### 样例输入 #2
```
6 6 7
1 6
1 5
1 4
1 3
1 2
1 1
1 2 3 4 5 6 7

```
### 样例输出 #2
```
15 14 12 9 5 0 0 

```
## 提示

#### 样例 #1 解释

Benson 会按照如下顺序启动机器：$1,2,3,3,4,5,2,3$。

第 $4$ 天启动的 $3$ 号机器连续 $0$ 天未启动；

第 $7$ 天启动的 $2$ 号机器连续 $4$ 天未启动；

第 $8$ 天启动的 $3$ 号机器连续 $3$ 天未启动。

当检查系数为 $0$ 时，$3$ 号机器会在第 $4$ 天和第 $8$ 天被安全检查，而 $2$ 号机器会在第 $7$ 天被安全检查。

当检查系数为 $2$ 时，$3$ 号机器会在第 $8$ 天被安全检查，而 $2$ 号机器会在第 $7$ 天被安全检查。

#### 数据范围

| Subtask | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $0$ | 样例 |
| $1$ | $11$ | $n,m,q\leq 200$ |
| $2$ | $18$ | $n,m\leq 2000$ |
| $3$ | $22$ | $l_i=1$ |
| $4$ | $26$ | $m\leq2000$ |
| $5$ | $23$ | 无 |

对于 $100\%$ 的数据：

- $1\leq n, m,q\leq 2\times 10^5$
- $1\leq l_i\leq r_i\leq n$
- $0\leq s_j\leq 10^{12}$

注：由于洛谷限制，数据不完全按照原题分配子任务。


---

---
title: "[NOISG 2023 Finals] Airplane"
layout: "post"
diff: 提高+/省选-
pid: P11535
tag: ['2023', '最短路', 'NOISG（新加坡）']
---
# [NOISG 2023 Finals] Airplane
## 题目描述

兔子 Benson 正要启动飞机！

有 $n$ 块 Benson 可以飞入的区域，由 $1\sim n$ 编号。受地形限制，进入第 $i$ 块区域时，需要保证飞机的高度不低于 $a_i$。保证 $a_1=a_n=0$。

此外，由于风况复杂而 Benson 的经验尚不充足（毕竟他是只兔子），他只能在某些特定的航线上双向飞行。具体地，有 $m$ 条航线，由 $1\sim m$ 编号，其中第 $i$ 条航线 $u_j,v_j$ 表示 Benson 可以在这两块区域间直接飞行。

Benson 发现，他可以通过在直接的航线上飞行，使得这些区域两两可达。

现在，Benson 在 $1$ 号区域，高度为 $0$。他希望降落在 $n$ 号区域，高度自然也为 $0$。每一分钟，Benson 可以跨过一条航线或不移动，并**同时**使飞机的高度上升 $1$、下降 $1$ 或保持不变。注意，当他到达 $i$ 区域时，必须保证飞机的高度不低于 $a_i$。

Benson 想知道，从 $1$ 号区域出发，在 $n$ 号区域降落，所需的最小时间。
## 输入格式

第一行两个正整数 $n, m$，用空格隔开。

接下来一行 $n$ 个整数 $a_1, a_2,\cdots, a_n$，表示区域的高度限制。

接下来 $m$ 行，每行两个正整数 $u_j,v_j$，表示一条在 $u_j,v_j$ 间的双向航线。
## 输出格式

一行一个整数，表示 Benson 所需的最小时间。
## 样例

### 样例输入 #1
```
3 2
0 2 0
1 2
2 3

```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
11 12
0 0 0 0 0 0 2 2 1 5 0
1 2
2 3
3 4
4 5
5 6
6 11
1 7
7 8
8 9
9 11
1 10
10 11

```
### 样例输出 #2
```
5
```
## 提示

#### 样例 #1 解释

Benson 从 $1$ 出发，在 $3$ 降落，总共需要 $4$ 分钟：

- 第 $1$ 分钟，Benson 不移动，同时高度从 $0$ 变为 $1$；
- 第 $2$ 分钟，从 $1$ 移动到 $2$，同时高度从 $1$ 变为 $2$；
- 第 $3$ 分钟，从 $2$ 移动到 $3$，同时高度从 $2$ 变为 $1$；
- 第 $4$ 分钟，Benson 不移动，同时高度从 $1$ 变为 $0$。

#### 数据范围

| Subtask | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $0$ | 样例 |
| $1$ | $22$ | $m=n-1,u_j=j,v_j=j+1$ |
| $2$ | $10$ | $n\leq 2000$，$m\leq 4000$，$a_i\leq 2000$ |
| $3$ | $31$ | $n\leq 2000$，$m\leq 4000$ |
| $4$ | $37$ | 无 |

对于 $100\%$ 的数据：

- $1\leq n\leq 2\times 10^5$
- $1\leq m\leq 4\times 10^5$
- $0\leq a_i\leq 10^8$，$a_1=a_n=0$
- $1\leq u_j,v_j\leq n$，$u_j\ne v_j$


---

---
title: "[NOIP 2008 提高组] 双栈排序"
layout: "post"
diff: 提高+/省选-
pid: P1155
tag: ['图论', '2008', 'NOIP 提高组', '二分图']
---
# [NOIP 2008 提高组] 双栈排序
## 题目描述

Tom 最近在研究一个有趣的排序问题。如图所示，通过 $2$ 个栈 $S_1$ 和 $S_2$，Tom 希望借助以下 $4$ 种操作实现将输入序列升序排序。

![](https://cdn.luogu.com.cn/upload/image_hosting/gwxu91ud.png)

- 操作 $\verb!a!$：将第一个元素压入栈 $S_1$。
- 操作 $\verb!b!$：将 $S_1$ 栈顶元素弹出至输出序列。
- 操作 $\verb!c!$：将第一个元素压入栈 $S_2$。
- 操作 $\verb!d!$：将 $S_2$ 栈顶元素弹出至输出序列。


如果一个 $1\sim n$ 的排列 $P$ 可以通过一系列合法操作使得输出序列为 $(1,2,\cdots,n-1,n)$，Tom 就称 $P$ 是一个“可双栈排序排列”。例如 $(1,3,2,4)$ 就是一个“可双栈排序序列”，而 $(2,3,4,1)$ 不是。下图描述了一个将 $(1,3,2,4)$ 排序的操作序列：$\texttt {a,c,c,b,a,d,d,b}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jwdjwfee.png)

当然，这样的操作序列有可能有几个，对于上例 $(1,3,2,4)$，$\texttt{a,b,a,a,b,b,a,b}$ 是另外一个可行的操作序列。Tom 希望知道其中字典序最小的操作序列是什么。
## 输入格式

第一行是一个整数 $n$。

第二行有 $n$ 个用空格隔开的正整数，构成一个 $1\sim n$ 的排列。
## 输出格式

共一行，如果输入的排列不是“可双栈排序排列”，输出 `0`。

否则输出字典序最小的操作序列，每两个操作之间用空格隔开，行尾没有空格。
## 样例

### 样例输入 #1
```
4
1 3 2 4
```
### 样例输出 #1
```
a b a a b b a b
```
### 样例输入 #2
```
4
2 3 4 1
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
3
2 3 1
```
### 样例输出 #3
```
a c a b b d
```
## 提示

$30\%$ 的数据满足：$n\le10$。

$50\%$ 的数据满足：$n\le50$。

$100\%$ 的数据满足：$n\le1000$。

2021.06.17 加强 by [SSerxhs](https://www.luogu.com.cn/user/29826)。hack 数据单独分为一个 subtask 防止混淆。

noip2008 提高第四题


---

---
title: "[NOISG 2025 Finals] Reachability"
layout: "post"
diff: 提高+/省选-
pid: P12017
tag: ['2025', '背包 DP', '树形 DP', 'NOISG（新加坡）']
---
# [NOISG 2025 Finals] Reachability
## 题目描述

Sheepland is a country with $n$ cities. There are $n − 1$ roads connecting pairs of cities with each other. Road $j$ directly connects cities $u[j]$ and $v[j]$. Initially, it is possible to travel from any city to any other city using only these roads.

All $n - 1$ roads in Sheepland are planned to be renovated. Under the renovation plan, each road $j$ will be in one of four states:

1. Two-way: citizens from both cities $u[j]$ and $v[j]$ may cross this road into the other city.
2. One-way from city $u[j]$ to city $v[j]$: only citizens from city $u[j]$ may cross this road into city $v[j]$.
3. One-way from city $v[j]$ to city $u[j]$: only citizens from city $v[j]$ may cross this road into city $u[j]$.
4. Closed: no citizens from cities $u[j]$ or $v[j]$ may cross this road into the other city.

Unfortunately, the renovation plan has gone missing!

To try to recover it, you ask the mayor of each city how many cities are reachable from their city under the renovation plan. The mayor of the $i$-th city replies with $l[i]$. However, some
mayors may have provided incorrect values.

A city $v$ is considered reachable from a city u if there exists a sequence $c_1, c_2, c_3, \ldots, c_k$ where $c_1 = u, c_k = v$ and a crossable road exists from $c_x$ to $c_{x+1}$ for all $1 \leq x \leq k - 1$. In particular, a city is reachable from itself.

Help Sheepland determine whether there exists a renovation plan that is consistent with the number of cities reachable from each city, as reported by all mayors!

## 输入格式

Your program must read from standard input.

The first line of input contains one integer $n$.

The second line of input contains $n$ space-separated integers $l[1], l[2], \ldots, l[n]$.

The following $n - 1$ lines of input each contain two space-separated integers. The $j$-th of these lines contains $u[j]$ and $v[j]$.

## 输出格式

Your program must print to standard output.

Output `YES` if a renovation plan that is consistent with the number of cities reachable from each city, as reported by all mayors, exists and `NO` otherwise.

## 样例

### 样例输入 #1
```
9
5 2 3 5 2 3 1 1 1
1 4
4 5
2 5
3 6
5 6
6 9
7 8
4 7
```
### 样例输出 #1
```
YES
```
### 样例输入 #2
```
9
5 2 3 5 2 3 1 1 2
1 4
4 5
2 5
3 6
5 6
6 9
7 8
4 7
```
### 样例输出 #2
```
NO
```
### 样例输入 #3
```
7
3 3 1 3 2 1 2
3 4
1 2
6 2
7 3
5 6
4 2
```
### 样例输出 #3
```
YES
```
## 提示

### Subtasks

For all test cases, the input will satisfy the following bounds:

- $1 \leq n \leq 5000$
- $1 \leq l[i] \leq n$ for all $1 \leq i \leq n$
- $1 \leq u[j], v[j] \leq n$ for all $1 \leq j \leq n - 1$
- $u[j] \neq v[j]$ for all $1 \leq j \leq n − 1$
- Initially, it is possible to travel from any city to any other city using roads only.

Your program will be tested on input instances that satisfy the following restrictions:

| Subtask | Marks | Additional Constraints |
| :-: | :-: | :-: |
| $0$ | $0$ | Sample test cases |
| $1$ | $4$ | $n \leq 7$ |
| $2$ | $5$ | $n \leq 15$ |
| $3$ | $11$ | $l[1] = l[2] = \cdots = l[n]$ |
| $4$ | $10$ | If a plan exists, at least one such plan has no two-way roads |
| $5$ | $45$ | $n \leq 400$ |
| $6$ | $25$ | No additional constraints |

### Sample Test Case 1 Explanation

This test case is valid for subtasks $2, 5$, and $6$.

Refer to the diagram below. The renovation plan is consistent with the number of cities reachable from each city, as reported by all mayors.

![](https://cdn.luogu.com.cn/upload/image_hosting/h1yj84mf.png)

### Sample Test Case 2 Explanation

This test case is valid for subtasks $2, 4, 5$, and $6$.

There does not exist a renovation plan consistent with the number of cities reachable from each city, as reported by all mayors.

### Sample Test Case 3 Explanation

This test case is valid for subtasks $1, 2, 5$, and $6$.



---

---
title: "[NOISG 2025 Finals] Robots"
layout: "post"
diff: 提高+/省选-
pid: P12018
tag: ['2025', 'NOISG（新加坡）']
---
# [NOISG 2025 Finals] Robots
## 题目描述

Funnyland is modelled as a grid of size $(h + 2) \times (w + 2)$. The rows of the grid are numbered $0$ to $h + 1$ from top to bottom, and the columns of the grid are numbered $0$ to $w + 1$ from left to right. We refer to the cell located at row r and column c of the grid as cell $(r, c)$.

Initially, all cells in this grid are coloured *white*, except for the rightmost column of cells, which are all coloured *black*.

The columns $1$ to $w$ each contain exactly one special cell. Each of these special cells are to be coloured *red* or *blue*. The edges of the grid (i.e., the topmost row, the bottommost row, the leftmost column, and the rightmost column) will never contain special cells.

Several robots will be placed on cells in the leftmost column and will move according to the colour of their cell:

- If the cell is white, the robot moves right.
- If the cell is red, the robot moves upward.
- If the cell is blue, the robot moves downward.
- If the cell is black, the robot does not move.

Robots do not collide with each other; each robot moves independently of other robots. Multiple robots are allowed to occupy the same cell.

A query consists of two integers $a$ and $b$ ($1 \leq a < b \leq h$). For each $a \leq c \leq b$, there will be a robot starting at $(c, 0)$. Across all possible configurations of colouring the special cells red or blue, determine the minimum number of distinct final cells the robots can occupy.

Note that different queries may result in different configurations of colouring the cells red and blue.

## 输入格式

Your program must read from standard input.

The first line of input contains two space-separated integers $h$ and $w$.

The second line of input contains $w$ space-separated integers $x[1], x[2], \ldots, x[w]$, indicating that the special cells are $(x[1], 1), (x[2], 2), \ldots, (x[w], w)$.

The third line of input contains one integer $q$.

The following $q$ lines of input each contain two space-separated integers. The $i$-th of these lines contains $a[i]$ and $b[i]$.

## 输出格式

Your program must print to standard output.

The output should contain $q$ lines. The $i$-th of these lines should contain one integer, the answer to the $i$-th query.

## 样例

### 样例输入 #1
```
4 4
3 2 4 1
3
1 4
1 3
2 4
```
### 样例输出 #1
```
2
1
1
```
### 样例输入 #2
```
15 16
5 15 3 4 13 8 3 7 14 6 2 10 11 12 9 1
20
4 10
7 15
5 15
2 6
7 15
5 15
12 15
13 14
5 14
13 14
2 11
3 11
2 5
9 11
3 15
5 14
1 13
3 7
7 12
4 8
```
### 样例输出 #2
```
2
2
3
2
2
3
1
1
3
1
3
2
1
1
3
3
4
1
2
1
```
## 提示

### Subtasks

For all test cases, the input will satisfy the following bounds:

- $1 \leq w, q \leq 200\,000$
- $2 \leq h \leq 200\,000$
- $1 \leq x[j] \leq h$ for all $1 \leq j \leq w$
- $1 \leq a[i] < b[i] \leq h$ for all $1 \leq i \leq q$

Your program will be tested on input instances that satisfy the following restrictions:

| Subtask | Marks | Additional Constraints |
| :-: | :-: | :-: |
| $0$ | $0$ | Sample test cases |
| $1$ | $10$ | $h, w \leq 16, q \leq 20$ |
| $2$ | $4$ | $a[i] + 1 = b[i]$ |
| $3$ | $12$ | $x[1] < x[2] < \cdots < x[w]$ |
| $4$ | $43$ | $h, w, q \leq 5000$ |
| $5$ | $31$ | No additional constraints |

### Sample Test Case 1 Explanation

This test case is valid for subtasks $1, 4$, and $5$.

The grid is coloured as foll
This test case is valid for subtasks $1, 4$, and $5$.
ows, with the special cells in violet.

![](https://cdn.luogu.com.cn/upload/image_hosting/fnpx3ay1.png)

For the first query, we can colour the special cells at $(3, 1)$ and $(4, 3)$ blue, $(2, 2)$ and $(1, 4)$ red to achieve the following:

![](https://cdn.luogu.com.cn/upload/image_hosting/09mu5rbg.png)

- The robot starting at $(1, 0)$ moves to $(1, 1), (1, 2), (1, 3), (1, 4), (0, 4), (0, 5)$, and ends at $(0, 5)$.
- The robot starting at $(2, 0)$ moves to $(2, 1), (2, 2), (1, 2), (1, 3), (1, 4), (0, 4), (0, 5)$, and ends at $(0, 5)$.
- The robot starting at $(3, 0)$ moves to $(3, 1), (4, 1), (4, 2), (4, 3), (5, 3), (5, 4)$, and ends at $(5, 5)$.
- The robot starting at $(4, 0)$ moves to $(4, 1), (4, 2), (4, 3), (5, 3), (5, 4)$, and ends at $(5, 5)$.

The robots end at $2$ distinct cells, $(0, 5)$ and $(5, 5)$, hence the correct output is $2$.

For the second query, we can colour the special cells as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/q0umkoee.png)

The robots starting at $(1, 0), (2, 0)$, and $(3, 0)$ all end at $(0, 5)$.

For the third query, we can colour the special cells as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/1vjztie5.png)

The robots starting at $(2, 0), (3, 0)$, and $(4, 0)$ all end at $(3, 5)$.

### Sample Test Case 2 Explanation

This test case is valid for subtasks $1, 4$, and $5$.



---

---
title: "[NOISG 2025 Prelim] Itinerary"
layout: "post"
diff: 提高+/省选-
pid: P12195
tag: ['2025', 'NOISG（新加坡）']
---
# [NOISG 2025 Prelim] Itinerary
## 题目描述

The Scientific Committee is planning to visit $n$ cities. The $n$ cities are connected by exactly $n - 1$ roads such that it is possible to move between all pairs of cities using the roads. Road $i$ is built between cities $u[i]$ and $v[i]$.

Each city has its own airport. To begin the trip, the committee will fly from Singapore to one of the cities. To make the most out of their trip in the most efficient way possible, the committee wants to visit each city **at least once** by using each road **exactly twice** (once in each direction), before flying back home from the last city they find themselves in. A trip satisfying this condition is called a **tour**.

![](https://cdn.luogu.com.cn/upload/image_hosting/glw0pqmy.png)

For example, let the diagram above represent a map of $n = 8$ cities. One possible tour starting from city $1$ is $1 \to 3 \to 5 \to 3 \to 4 \to 2 \to 8 \to 2 \to 4 \to 6 \to 4 \to 7 \to 4 \to 3 \to 1$. Observe that this tour visits all cities a total of $2n - 1$ (equal to $15$) times and ends at the same city it started from (city $1$). It can be shown that these two properties are true for all tours in all possible maps of cities.

The committee also wants to visit $m$ events which will happen in order from event $1$ to event $m$. Event $j$ will be held in city $s[j]$. A city can hold zero, one or multiple events, but no two consecutive events are held in the same city, i.e., $s[j] = s[j + 1]$.

A tour that allows the committee to visit all events must visit the cities $s[1], s[2], \ldots, s[m]$ in order, not necessarily consecutively. Such a tour is called an **itinerary**. Formally, let $t[1], t[2], \ldots, t[2n - 1]$ be the sequence of cities visited in some tour. A tour is an itinerary if and only if $s$ is a subsequence of $t$. That is, $s$ can be obtained by deleting zero or more elements from $t$ and maintaining the order of the remaining elements. Using the same example as above, suppose that $m = 4$ and $s = [3, 5, 2, 7]$, then the tour $1 \to \textbf{3} \to \textbf{5} \to 3 \to 4 \to \textbf{2} \to 8 \to 2 \to 4 \to 6 \to 4 \to \textbf{7} \to 4 \to 3 \to 1$ above is an itinerary because the cities $3, 5, 2, 7$ are visited in order during the tour (underlined and marked in bold).

The committee is still deciding which city to start from, but they agree that a city is a good choice to start from if there exists an itinerary that starts from it. For all cities, help the committee determine if there exists at least one itinerary starting from that city.

## 输入格式

Your program must read from standard input.

The first line of input contains two space-separated integers $n$ and $m$, describing the number of cities and the number of events respectively.

The following $n - 1$ lines of input each contain two space-separated integers. The $i$-th of these lines contains $u[i]$ and $v[i]$, describing the endpoints of the $i$-th road.

The last line of input contains $m$ space-separated integers $s[1], s[2], \ldots, s[m]$, describing the cities that are holding events.

## 输出格式

Your program must print to standard output.

The output should contain $n$ lines. If there exists an itinerary starting from city $i$, then the $i$-th line should contain a single integer $1$. Otherwise, the $i$-th line should contain a single integer $0$.

## 样例

### 样例输入 #1
```
8 4
1 3
2 4
3 4
4 6
5 3
2 8
7 4
3 5 2 7
```
### 样例输出 #1
```
1
0
1
1
0
1
1
0
```
### 样例输入 #2
```
8 4
1 3
2 4
3 4
4 6
5 3
2 8
7 4
3 2 5 7
```
### 样例输出 #2
```
0
0
0
0
0
0
0
0
```
### 样例输入 #3
```
4 7
1 2
1 3
1 4
2 1 2 1 2 1 2
```
### 样例输出 #3
```
0
0
0
0
```
### 样例输入 #4
```
5 2
1 2
2 3
3 4
4 5
2 4
```
### 样例输出 #4
```
1
1
1
1
1
```
## 提示

### Subtasks

For all test cases, the input will satisfy the following bounds:

- $2 \leq n \leq 200\,000$
- $1 \leq m \leq 2n - 1$
- $1 \leq u[i], v[i] \leq n$ for all $1 \leq i \leq n - 1$
- $1 \leq s[j] \leq n$ for all $1 \leq j \leq m$
- $s[j] \neq s[j + 1]$ for all $1 \leq j \leq m - 1$
- It is possible to move between all pairs of cities using the roads.

Your program will be tested on input instances that satisfy the following restrictions:

| Subtask | Marks | Additional Constraints |
| :-: | :-: | :-: |
| $0$ | $0$ | Sample test cases |
| $1$ | $7$ | $n \leq 1000, m = 2n - 1$ |
| $2$ | $10$ | $u[i] = 1, v[i] = i + 1$ |
| $3$ | $6$ | $n \leq 1000, u[i] = i, v[i] = i + 1$ |
| $4$ | $7$ | $u[i] = i, v[i] = i + 1$ |
| $5$ | $14$ | $n \leq 1000, m \leq 10$ |
| $6$ | $5$ | $n \leq 1000$ |
| $7$ | $19$ | $m \leq 10$ |
| $8$ | $11$ | $s[1] = s[m]$ |
| $9$ | $21$ | No additional constraints |

### Sample Test Case 1 Explanation

This test case is valid for subtasks $5, 6, 7$, and $9$.

This test case is described as an example in the problem statement.

There are itineraries starting from cities $1, 3, 4, 6$, and $7$. An itinerary starting from city $1$ is given in the problem statement.

On the other hand, it can be shown that there are no itineraries starting from cities $2, 5$, and $8$.

### Sample Test Case 2 Explanation

This test case is valid for subtasks $5, 6, 7$, and $9$.

This test case is the same as the example in the problem statement, except $s[2]$ and $s[3]$ are swapped. No itineraries exist at all.

### Sample Test Case 3 Explanation

This test case is valid for subtasks $1, 2, 5, 6, 7, 8$, and $9$.

### Sample Test Case 4 Explanation

This test case is valid for subtasks $3, 4, 5, 6, 7$, and $9$.


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
title: "[NOIP 2011 提高组] 观光公交"
layout: "post"
diff: 提高+/省选-
pid: P1315
tag: ['贪心', '递推', '2011', 'NOIP 提高组']
---
# [NOIP 2011 提高组] 观光公交
## 题目背景

感谢 @Transhumanist 提供的一组 Hack 数据
## 题目描述

风景迷人的小城 Y 市，拥有 $n$ 个美丽的景点。由于慕名而来的游客越来越多，Y 市特意安排了一辆观光公交车，为游客提供更便捷的交通服务。观光公交车在第 $0$ 分钟出现在 $1$ 号景点，随后依次前往 $2,3,4,\cdots,n$ 号景点。从第 $i$ 号景点开到第 $i+1$ 号景点需要 $D_i$ 分钟。任意时刻，公交车只能往前开，或在景点处等待。

设共有 $m$ 个游客，每位游客需要乘车 $1$ 次从一个景点到达另一个景点，第 $i$ 位游客在 $T_i$ 分钟来到景点 $A_i$，希望乘车前往景点 $B_i$（$A_i<B_i$）。为了使所有乘客都能顺利到达目的地，公交车在每站都必须等待需要从该景点出发的所有乘客都上车后才能出发开往下一景点。

假设乘客上下车不需要时间。一个乘客的旅行时间，等于他到达目的地的时刻减去他来到出发地的时刻。因为只有一辆观光车，有时候还要停下来等其他乘客，乘客们纷纷抱怨旅行时间太长了。于是聪明的司机 ZZ 给公交车安装了 $k$ 个氮气加速器，每使用一个加速器，可以使其中一个 $D_i-1$。对于同一个 $D_i$ 可以重复使用加速器，但是必须保证使用后 $D_i\ge0$。

那么 ZZ 该如何安排使用加速器，才能使所有乘客的旅行时间总和最小？
## 输入格式

第 $1$ 行是 $3$ 个整数 $n,m,k$，每两个整数之间用一个空格隔开。分别表示景点数、乘客数和氮气加速器个数。

第 $2$ 行是 $n-1$ 个整数，每两个整数之间用一个空格隔开，第 $i$ 个数表示从第 $i$ 个景点开往第 $i+1$ 个景点所需要的时间，即 $D_i$。

第 $3$ 行至 $m+2$ 行每行 $3$ 个整数 $T_i,A_i,B_i$，每两个整数之间用一个空格隔开。第 $i+2$ 行表示第 $i$ 位乘客来到出发景点的时刻，出发的景点编号和到达的景点编号。
## 输出格式

一个整数，表示最小的总旅行时间。

## 样例

### 样例输入 #1
```
3 3 2
1 4
0 1 3
1 1 2
5 2 3
```
### 样例输出 #1
```
10

```
## 提示

**【输入输出样例说明】**

对 $D_2$ 使用 $2$ 个加速器，从 $2$ 号景点到 $3$ 号景点时间变为 $2$ 分钟。

公交车在第 $1$ 分钟从 $1$ 号景点出发，第 $2$ 分钟到达 $2$ 号景点，第 $5$ 分钟从 $2$ 号景点出发，第 $7$ 分钟到达 $3$ 号景点。

第 $1$ 个旅客旅行时间 $7-0=7$ 分钟。

第 $2$ 个旅客旅行时间 $2-1=1$ 分钟。

第 $3$ 个旅客旅行时间 $7-5=2$ 分钟。

总时间 $7+1+2=10$ 分钟。

**【数据范围】**

对于 $10\%$ 的数据，$k=0$。

对于 $20\%$ 的数据，$k=1$。

对于 $40\%$ 的数据，$2 \le n \le 50$，$1 \le m \le 10^3$，$0 \le k \le 20$，$0 \le D_i \le 10$，$0 \le T_i \le 500$。

对于 $60\%$ 的数据，$1 \le n \le 100$，$1 \le m \le 10^3$，$0 \le k \le 100$，$0 \le D_i \le 100$，$0 \le T_i \le 10^4$。

对于 $100\%$ 的数据，$1 \le n \le 10^3$，$1 \le m \le 10^4$，$0 \le k \le 10^5$，$0 \le D_i \le 100$，$0 \le T_i \le 10^5$。


---

---
title: "[NOI2025] 三目运算符"
layout: "post"
diff: 提高+/省选-
pid: P13274
tag: ['线段树', '2025', 'NOI']
---
# [NOI2025] 三目运算符
## 题目背景

ternary.cpp / 2 s / 512 MiB
## 题目描述

对于一个长度为 $n$ ($n \geq 3$) 的 01 串 $S = s_1 \ldots s_n$，定义变换 $T = f(S) = t_1 \ldots t_n$ 如下：

$$t_i = \begin{cases} 
s_i, & i \leq 2, \\
s_i, & i \geq 3 \text{ 且 } s_{i-2} = 0, \\
s_{i-1}, & i \geq 3 \text{ 且 } s_{i-2} = 1.
\end{cases}$$

定义变换 $f$ 的 **不动点** 如下：若 01 串 $T$ 满足 $f(T) = T$，则称 $T$ 为变换 $f$ 的不动点。

记 $f^k(S)$ 为 $S$ 经过 $k$ 次变换得到的串。特别地，记 $f^0(S) = S$。求最小的自然数 $k$，使得 $f^k(S)$ 为变换 $f$ 的不动点，即满足 $f^{k+1}(S) = f^k(S)$ 的最小的自然数 $k$。可以证明，一定存在自然数 $k$ 使得 $f^k(S)$ 为变换 $f$ 的不动点。

小 Z 觉得这个问题过于简单，因此他增加了 $q$ 次修改操作。第 $i$ ($1 \leq i \leq q$) 次修改会给定两个正整数 $l_i, r_i$ ($1 \leq l_i \leq r_i \leq n$)，然后将区间 $[l_i, r_i]$ 内的所有原有的 0 替换为 1，所有原有的 1 替换为 0。你需要对初始时及每次修改后的字符串 $S$，求出最小的自然数 $k$，使得 $f^k(S)$ 为变换 $f$ 的不动点。

## 输入格式

**本题包含多组测试数据。**

输入的第一行包含两个非负整数 $c, t$，分别表示测试点编号与测试数据组数。$c = 0$ 表示该测试点为样例。

接下来依次输入每组测试数据，对于每组测试数据：

第一行包含两个正整数 $n, q$，分别表示 $S$ 的长度和修改次数。

第二行包含一个长度为 $n$ 的 01 串 $S = s_1 \ldots s_n$，表示初始时的字符串。

第 $i + 2$ ($1 \leq i \leq q$) 行包含两个正整数 $l_i, r_i$，表示一次修改操作。
## 输出格式

对于每组测试数据，设初始时的答案为 $k_0$，第 $i$ ($1 \leq i \leq q$) 次修改后的答案为 $k_i$，输出一行一个正整数，表示 $\oplus_{i=0}^{q} ((i + 1) \times k_i)$，其中 $\oplus$ 表示 **二进制按位异或**。
## 样例

### 样例输入 #1
```
0 2
5 2
11010
3 3
2 2
7 3
1010100
7 7
2 4
1 2
```
### 样例输出 #1
```
2
4
```
## 提示

该样例共包含两组测试数据。

对于第一组测试数据：
- 初始时，$S = 11010$，$f(S) = 11100$，$f^2(S) = 11110$，$f^3(S) = f^4(S) = 11111$，因此 $k_0 = 3$；
- 第一次操作后，$S = 11110$，$f(S) = f^2(S) = 11111$，因此 $k_1 = 1$；
- 第二次操作后，$S = 10110$，$f(S) = f^2(S) = 10011$，因此 $k_2 = 1$。

故答案为 $\bigoplus_{i=0}^{q} ((i+1) \times k_i) = (1 \times 3) \oplus (2 \times 1) \oplus (3 \times 1) = 3 \oplus 2 \oplus 3 = 2$。

对于第二组测试数据：
- 初始时，$S = 1010100$，$k_0 = 1$；
- 第一次操作后，$S = 1010101$，$k_1 = 1$；
- 第二次操作后，$S = 1101101$，$k_2 = 5$；
- 第三次操作后，$S = 0001101$，$k_3 = 2$。

故答案为 $\bigoplus_{i=0}^{q} ((i+1) \times k_i) = (1 \times 1) \oplus (2 \times 1) \oplus (3 \times 5) \oplus (4 \times 2) = 4$。

**【样例 2】**

见选手目录下的 ternary/ternary2.in 与 ternary/ternary2.ans。该样例满足测试点 1 ~ 3 的约束条件。

【样例 2】

见选手目录下的 ternary/ternary2.in 与 ternary/ternary2.ans。

该样例满足测试点 1 ~ 3 的约束条件。

**【样例 3】**

见选手目录下的 ternary/ternary3.in 与 ternary/ternary3.ans。

该样例满足测试点 4 ~ 6 的约束条件。

**【样例 4】**

见选手目录下的 ternary/ternary4.in 与 ternary/ternary4.ans。

该样例满足测试点 13、14 的约束条件。

**【样例 5】**

见选手目录下的 ternary/ternary5.in 与 ternary/ternary5.ans。

该样例满足测试点 17 ~ 19 的约束条件。

**【数据范围】**

设 $N, Q$ 分别为单个测试点内所有测试数据的 $n, q$ 的和。对于所有测试数据，保证：
- $1 \leq t \leq 5$;
- $3 \leq n \leq 4 \times 10^5$, $N \leq 8 \times 10^5$;
- $1 \leq q \leq 4 \times 10^5$, $Q \leq 8 \times 10^5$;
- 对于所有 $1 \leq i \leq n$, 均有 $s_i \in \{0, 1\}$;
- 对于所有 $1 \leq i \leq q$, 均有 $1 \leq l_i \leq r_i \leq n$。

| 测试点编号 | $n, q \leq$ | $N, Q \leq$ | 特殊性质 |
| :-: | :-: | :-: | :-: |
| $1 \sim 3$ | $200$ | $10^3$ | A |
| $4 \sim 6$ | $200$ | $10^3$ | 无 |
| $7, 8$ | $5,000$ | $10^4$ | A |
| $9 \sim 11$ | $5,000$ | $10^4$ | 无 |
| $12$ | $10^5$ | $2 \times 10^5$ | A |
| $13, 14$ | $10^5$ | $2 \times 10^5$ | B |
| $15, 16$ | $10^5$ | $2 \times 10^5$ | 无 |
| $17 \sim 19$ | $4 \times 10^5$ | $8 \times 10^5$ | C |
| $20$ | $4 \times 10^5$ | $8 \times 10^5$ | 无 |

特殊性质 A: 保证初始时及每次修改后，存在整数 $p \in [2, n]$ 满足 $s_1 = s_2 = \cdots = s_p = 1$ 且 $s_{p+1} = \cdots = s_n = 0$。

特殊性质 B: 保证对于所有 $1 \leq i \leq q$, 均有 $l_i = 1$, $r_i = n$。

特殊性质 C: 保证对于所有 $1 \leq i \leq q$, 均有 $l_i = 1$, 且 $r_1 \leq r_2 \leq \cdots \leq r_q$。

附加文件来自于 [QOJ](https://qoj.ac/contest/2316/problem/13082)。


---

---
title: "[NOI2013] 矩阵游戏"
layout: "post"
diff: 提高+/省选-
pid: P1397
tag: ['递推', '2013', 'NOI', '矩阵乘法', '线性递推']
---
# [NOI2013] 矩阵游戏
## 题目描述

婷婷是个喜欢矩阵的小朋友，有一天她想用电脑生成一个巨大的 $n$ 行 $m$ 列的矩阵（你不用担心她如何存储）。她生成的这个矩阵满足一个神奇的性质：若用 $F[i,j]$ 来表示矩阵中第 $i$ 行第 $j$ 列的元素，则 $F[i,j]$ 满足下面的递推式:

$$\begin{aligned}
F[1, 1] &= 1 \\
F[i, j] &=a\times F[i, j-1]+b, &j\neq 1 \\
F[i, 1] &=c\times F[i-1, m]+d, &i\neq 1 \\
\end{aligned}$$

递推式中 $a,b,c,d$ 都是给定的常数。

现在婷婷想知道 $F[n,m]$ 的值是多少，请你帮助她。由于最终结果可能很大，你只需要输出 $F[n,m]$ 除以 $10^9+7$ 的余数。

## 输入格式

包含一行有六个整数 $n,m,a,b,c,d$。意义如题所述。

## 输出格式

包含一个整数，表示 $F[n,m]$ 除以 $10^9+7$ 的余数。

## 样例

### 样例输入 #1
```
3 4 1 3 2 6

```
### 样例输出 #1
```
85

```
## 提示

【样例1说明】

样例中的矩阵为：

$$\begin{pmatrix}
 1 &  4 &  7 & 10 \\
26 & 29 & 32 & 35 \\
76 & 79 & 82 & 85 \\
\end{pmatrix}$$

### 数据范围

| 测试点编号 | 数据范围 |
| :-: | :-: |
| 1 | $1 \le n,m \le 10$；$1 \le a,b,c,d \le 1000$ |
| 2 | $1 \le n,m \le 100$；$1 \le a,b,c,d \le 1000$ |
| 3 | $1 \le n,m \le 10^3$；$1 \le a,b,c,d \le 10^9$ |
| 4 | $1 \le n,m \le 10^3$；$1 \le a,b,c,d \le 10^9$ |
| 5 | $1 \le n,m \le 10^9$；$1 \le a = c \le 10^9$；$1 \le b = d \le 10^9$ |
| 6 | $1 \le n,m \le 10^9$；$a = c = 1$；$1 \le b,d \le 10^9$ |
| 7 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 8 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 9 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 10 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 11 | $1 \le n,m \le 10^{1\,000}$；$a = c = 1$；$1 \le b,d \le 10^9$ |
| 12 | $1 \le n,m \le 10^{1\,000}$；$1 \le a = c \le 10^9$；$1 \le b = d \le 10^9$ |
| 13 | $1 \le n,m \le 10^{1\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 14 | $1 \le n,m \le 10^{1\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 15 | $1 \le n,m \le 10^{20\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 16 | $1 \le n,m \le 10^{20\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 17 | $1 \le n,m \le 10^{1\,000\,000}$；$a = c = 1$；$1 \le b,d \le 10^9$ |
| 18 | $1 \le n,m \le 10^{1\,000\,000}$；$1 \le a = c \le 10^9$；$1 \le b = d \le 10^9$ |
| 19 | $1 \le n,m \le 10^{1\,000\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 20 | $1 \le n,m \le 10^{1\,000\,000}$；$1 \le a,b,c,d \le 10^9$ |


---

---
title: "[NOI2013] 快餐店"
layout: "post"
diff: 提高+/省选-
pid: P1399
tag: ['递推', '2013', '线段树', 'NOI', '深度优先搜索 DFS', '基环树']
---
# [NOI2013] 快餐店
## 题目描述

小 T 打算在城市 C 开设一家外送快餐店。送餐到某一个地点的时间与外卖店到该地点之间最短路径长度是成正比的，小 T 希望快餐店的地址选在离最远的顾客距离最近的地方。

快餐店的顾客分布在城市 C 的 $N$ 个建筑中，这 $N$ 个建筑通过恰好 $N$ 条双向道路连接起来，不存在任何两条道路连接了相同的两个建筑。任意两个建筑之间至少存在一条由双向道路连接而成的路径。小 T 的快餐店可以开设在任一建筑中，也可以开设在任意一条道路的某个位置上（该位置与道路两端的建筑的距离不一定是整数）。

现给定城市 C 的地图（道路分布及其长度），请找出最佳的快餐店选址，输出其与最远的顾客之间的距离。
## 输入格式

第一行包含一个整数 $N$，表示城市 C 中的建筑和道路数目。

接下来 $N$ 行，每行 $3$ 个整数，$A_i,B_i,L_i$（$1\leq i\leq N$，$L_i>0$），表示一条道路连接了建筑 $A_i$ 与 $B_i$，其长度为 $L_i$。

## 输出格式

输出仅包含一个实数，四舍五入保留**恰好一位小数**，表示最佳快餐店选址距离最远用户的距离。

注意：你的结果必须恰好有一位小数，小数位数不正确不得分。
## 样例

### 样例输入 #1
```
4 
1 2 1 
1 4 2 
1 3 2 
2 4 1

```
### 样例输出 #1
```
2.0 
```
### 样例输入 #2
```
5
1 5 100
2 1 77
3 2 80
4 1 64
5 3 41
```
### 样例输出 #2
```
109.0
```
## 提示

### 样例解释 1

![](https://cdn.luogu.com.cn/upload/image_hosting/r0dmxcgy.png)

### 样例解释 2

![](https://cdn.luogu.com.cn/upload/image_hosting/pf8eaowl.png)

### 数据范围

- 对于 $10\%$ 的数据，$N\leq 80$，$L_i=1$；
- 对于 $30\%$ 的数据，$N\leq 600$，$L_i\leq 100$；
- 对于 $60\%$ 的数据，$N\leq 2000$，$L_i\leq 10^9$；
- 对于 $100\%$ 的数据，$1\leq N\leq 10^5$，$1\leq L_i \leq 10^9$。


---

---
title: "[NOI2010] 能量采集"
layout: "post"
diff: 提高+/省选-
pid: P1447
tag: ['数学', '2010', 'NOI', '最大公约数 gcd', '莫比乌斯反演', '整除分块']
---
# [NOI2010] 能量采集
## 题目描述

栋栋有一块长方形的地，他在地上种了一种能量植物，这种植物可以采集太阳光的能量。在这些植物采集能量后，栋栋再使用一个能量汇集机器把这些植物采集到的能量汇集到一起。

栋栋的植物种得非常整齐，一共有 $n$ 列，每列有 $m$ 棵，植物的横竖间距都一样，因此对于每一棵植物，栋栋可以用一个坐标 $(x, y)$ 来表示，其中 $x$ 的范围是 $1$ 至 $n$，$y$ 的范围是 $1$ 至 $m$，表示是在第 $x$ 列的第 $y$ 棵。

由于能量汇集机器较大，不便移动，栋栋将它放在了一个角上，坐标正好是 $(0, 0)$。

能量汇集机器在汇集的过程中有一定的能量损失。如果一棵植物与能量汇集机器连接而成的线段上有 $k$ 棵植物，则能量的损失为 $2k + 1$。例如，当能量汇集机器收集坐标为 $(2, 4)$ 的植物时，由于连接线段上存在一棵植物 $(1, 2)$，会产生 $3$ 的能量损失。注意，如果一棵植物与能量汇集机器连接的线段上没有植物，则能量损失为 $1$。现在要计算总的能量损失。

下面给出了一个能量采集的例子，其中 $n = 5$，$m = 4$，一共有 $20$ 棵植物，在每棵植物上标明了能量汇集机器收集它的能量时产生的能量损失。

![](https://cdn.luogu.com.cn/upload/image_hosting/fhzpmm7b.png)

在这个例子中，总共产生了 $36$ 的能量损失。
## 输入格式

一行两个整数 $n,m$。
## 输出格式

仅包含一个整数，表示总共产生的能量损失。

## 样例

### 样例输入 #1
```
5 4

```
### 样例输出 #1
```
36

```
### 样例输入 #2
```
3 4
```
### 样例输出 #2
```
20

```
## 提示

- 对于 $10\%$ 的数据：$n, m \leq 10$；
- 对于 $50\%$ 的数据：$n, m \leq 100$；
- 对于 $80\%$ 的数据：$n, m \leq 10^3$；
- 对于 $90\%$ 的数据：$n, m \leq 10^4$；
- 对于 $100\%$ 的数据：$1 \leq n, m \leq 10^5$。


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
title: "[NOI2004] 郁闷的出纳员"
layout: "post"
diff: 提高+/省选-
pid: P1486
tag: ['2004', '线段树', '平衡树', 'NOI']
---
# [NOI2004] 郁闷的出纳员
## 题目描述

OIER 公司是一家大型专业化软件公司，有着数以万计的员工。作为一名出纳员，我的任务之一便是统计每位员工的工资。这本来是一份不错的工作，但是令人郁闷的是，我们的老板反复无常，经常调整员工的工资。如果他心情好，就可能把每位员工的工资加上一个相同的量。反之，如果心情不好，就可能把当前在公司的所有员工的工资扣除一个相同的量。我真不知道除了调工资他还做什么其它事情。

工资的频繁调整很让员工反感，尤其是集体扣除工资的时候，一旦某位员工发现自己的工资已经低于了合同规定的工资下界，他就会立刻气愤地离开公司，并且再也不会回来了。每位员工的工资下界都是统一规定的。每当一个人离开公司，我就要从电脑中把他的工资档案删去，同样，每当公司招聘了一位新员工，我就得为他新建一个工资档案。

老板经常到我这边来询问工资情况，他并不问具体某位员工的工资情况，而是问现在工资第 $k$ 多的员工拿多少工资。每当这时，我就不得不对数万个员工进行一次漫长的排序，然后告诉他答案。

好了，现在你已经对我的工作了解不少了。正如你猜的那样，我想请你编一个工资统计程序。怎么样，不是很困难吧？

如果某个员工的初始工资低于最低工资标准，那么将不计入最后的答案内。
## 输入格式

第一行有两个整数 $n$ 和 $\min$。$n$ 表示下面有多少条命令，$\min$ 表示工资下界。

接下来的 $n$ 行，每行一个字符 $x$ 和一个整数 $k$，表示一条命令。命令可以是以下四种之一：

- `I k`  新建一个工资档案，初始工资为 $k$。如果某员工的初始工资低于工资下界，他将立刻离开公司。
- `A k`   把每位员工的工资加上 $k$。
- `S k`   把每位员工的工资扣除 $k$。
- `F k`    查询第 $k$ 多的工资。

在初始时，可以认为公司里一个员工也没有。
## 输出格式

对于每条 `F` 命令，你的程序要输出一行，仅包含一个整数，为当前工资第  $k$ 多的员工所拿的工资数，如果 $k$ 大于目前员工的数目，则输出 $-1$。

输出的最后一行包含一个整数，为离开公司的员工的总数。

请注意，初始工资低于工资下界的员工不算做离开公司的员工。
## 样例

### 样例输入 #1
```
9 10
I 60
I 70
S 50
F 2
I 30
S 15
A 5
F 1
F 2

```
### 样例输出 #1
```
10
20
-1
2

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- `I` 命令的条数不超过 $10^5$；
- `A` 和 `S` 命令的总条数不超过 $100$；
- `F` 命令的条数不超过 $10^5$；
- 每次工资调整的调整量不超过 $10^3$；
- 新员工的工资不超过 $10^5$。
- $0 \leq n \leq 3 \times 10^5$，$0 \leq \text{min} \leq 10^9$，输入的所有数字均在 $32$ 位带符号整形范围内。


---

---
title: "[NOIP 2010 提高组] 引水入城"
layout: "post"
diff: 提高+/省选-
pid: P1514
tag: ['动态规划 DP', '搜索', '2010', 'NOIP 提高组', '广度优先搜索 BFS']
---
# [NOIP 2010 提高组] 引水入城
## 题目背景

NOIP2010 提高组 T4
## 题目描述

在一个遥远的国度，一侧是风景秀美的湖泊，另一侧则是漫无边际的沙漠。该国的行政区划十分特殊，刚好构成一个 $N$ 行 $M$ 列的矩形，如上图所示，其中每个格子都代表一座城市，每座城市都有一个海拔高度。

![](https://cdn.luogu.com.cn/upload/image_hosting/rcqfo04b.png)



为了使居民们都尽可能饮用到清澈的湖水，现在要在某些城市建造水利设施。水利设施有两种，分别为蓄水厂和输水站。蓄水厂的功能是利用水泵将湖泊中的水抽取到所在城市的蓄水池中。

因此，只有与湖泊毗邻的第 $1$ 行的城市可以建造蓄水厂。而输水站的功能则是通过输水管线利用高度落差，将湖水从高处向低处输送。故一座城市能建造输水站的前提，是存在比它海拔更高且拥有公共边的相邻城市，已经建有水利设施。由于第 $N$ 行的城市靠近沙漠，是该国的干旱区，所以要求其中的每座城市都建有水利设施。那么，这个要求能否满足呢？如果能，请计算最少建造几个蓄水厂；如果不能，求干旱区中不可能建有水利设施的城市数目。

## 输入格式

每行两个数，之间用一个空格隔开。输入的第一行是两个正整数 $N,M$，表示矩形的规模。接下来 $N$ 行，每行 $M$ 个正整数，依次代表每座城市的海拔高度。

## 输出格式

两行。如果能满足要求，输出的第一行是整数 $1$，第二行是一个整数，代表最少建造几个蓄水厂；如果不能满足要求，输出的第一行是整数 $0$，第二行是一个整数，代表有几座干旱区中的城市不可能建有水利设施。

## 样例

### 样例输入 #1
```
2 5
9 1 5 4 3
8 7 6 1 2

```
### 样例输出 #1
```
1
1

```
### 样例输入 #2
```
3 6
8 4 5 6 4 4
7 3 4 3 3 3
3 2 2 1 1 2
```
### 样例输出 #2
```
1
3
```
## 提示

**样例 1 说明**

只需要在海拔为 $9$ 的那座城市中建造蓄水厂，即可满足要求。

**样例 2 说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/qoz3f0lv.png)

上图中，在 $3 $ 个粗线框出的城市中建造蓄水厂，可以满足要求。以这 $3 $ 个蓄水厂为源头在干旱区中建造的输水站分别用 $3$ 种颜色标出。当然，建造方法可能不唯一。

**数据范围**

本题有 10 个测试数据，每个数据的范围如下表所示：

| 测试数据编号 | 能否满足要求 | $N\le$ | $M\le$ |
| :----------: | :----------: | :----------: | :----------: |
| 1 | 不能 | $10$ | $10$ |
| 2 | 不能 | $100$ | $100$ |
| 3 | 不能 | $500$ | $500$ |
| 4 | 能 | $1$ | $10$ |
| 5 | 能 | $10$ | $10$ |
| 6 | 能 | $100$ | $20$ |
| 7 | 能 | $100$ | $50$ |
| 8 | 能 | $100$ | $100$ |
| 9 | 能 | $200$ | $200$ |
| 10 | 能 | $500$ | $500$ |

对于所有 10 个数据，每座城市的海拔高度都不超过 $10^6$。


---

---
title: "[NOI2016] 区间"
layout: "post"
diff: 提高+/省选-
pid: P1712
tag: ['2016', '线段树', 'NOI', '离散化', 'O2优化', '排序', '双指针 two-pointer']
---
# [NOI2016] 区间
## 题目描述

在数轴上有 $n$ 个闭区间从 $1$ 至 $n$ 编号，第 $i$ 个闭区间为 $[l_i,r_i]$ 。

现在要从中选出 $m$ 个区间，使得这 $m$ 个区间共同包含至少一个位置。换句话说，就是使得存在一个 $x$ ，使得对于每一个被选中的区间 $[l_i,r_i]$，都有 $l_i \leq x \leq r_i$ 。

对于一个合法的选取方案，它的花费为被选中的最长区间长度减去被选中的最短区间长度。

区间 $[l_i,r_i]$ 的长度定义为 $(r_i-l_i)$ ，即等于它的右端点的值减去左端点的值。

求所有合法方案中最小的花费。如果不存在合法的方案，输出 $-1$。
## 输入格式

第一行包含两个整数，分别代表 $n$ 和 $m$。

第 $2$ 到第 $(n + 1)$ 行，每行两个整数表示一个区间，第 $(i + 1)$ 行的整数 $l_i, r_i$ 分别代表第 $i$ 个区间的左右端点。
## 输出格式

输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
6 3
3 5
1 2
3 4
2 2
1 5
1 4
```
### 样例输出 #1
```
2
```
## 提示

#### 样例输入输出 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/qoddox9k.png)
 
 如图，当 $n=6$，$m=3$ 时，花费最小的方案是选取 $[3,5],[3,4],[1,4]$ 这三个区间，它们共同包含了 $4$ 这个位置，所以是合法的。其中最长的区间是 $[1, 4]$，最短的区间是 $[3, 4]$，所以它的花费是 $(4 - 1) - (4 - 3) = 2$。

#### 数据规模与约定

本题共 20 个测试点，各测试点信息如下表。
| 测试点编号 | $ n= $ | $ m= $ | $ l_i,r_i $ |
|:-:|:-:|:-:|:-:|
| 1 | $ 20 $ | $ 9 $ | $ 0 \le l_i \le r_i \le 100 $ |
| 2 | $ 20 $ | $ 10 $ | $ 0 \le l_i \le r_i \le 100 $ |
| 3 | $ 199 $ | $ 3 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 4 | $ 200 $ | $ 3 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 5 | $ 1000 $ | $ 2 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 6 | $ 2000 $ | $ 2 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 7 | $ 199 $ | $ 60 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 8 | $ 200 $ | $ 50 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 9 | $ 200 $ | $ 50 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 10 | $ 1999 $ | $ 500 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 11 | $ 2000 $ | $ 400 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 12 | $ 2000 $ | $ 500 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 13 | $ 30000 $ | $ 2000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 14 | $ 40000 $ | $ 1000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 15 | $ 50000 $ | $ 15000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 16 | $ 100000 $ | $ 20000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 17 | $ 200000 $ | $ 20000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 18 | $ 300000 $ | $ 50000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 19 | $ 400000 $ | $ 90000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 20 | $ 500000 $ | $ 200000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |

对于全部的测试点，保证 $1 \leq m \leq n$，$1 \leq n \leq 5 \times 10^5$，$1 \leq m \leq 2 \times 10^5$，$0 \leq l_i \leq r_i \leq 10^9$。


---

---
title: "[NOI2009] 管道取珠"
layout: "post"
diff: 提高+/省选-
pid: P1758
tag: ['字符串', '动态规划 DP', '递推', '2009', 'NOI']
---
# [NOI2009] 管道取珠
## 题目描述

管道取珠是小 X 很喜欢的一款游戏。在本题中，我们将考虑该游戏的一个简单改版。游戏画面如图 1 所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7p4r2ip9.png)

游戏初始时，左侧上下两个管道分别有一定数量的小球（有深色球和浅色球两种类型），而右侧输出管道为空。每一次操作，可以从左侧选择一个管道，并将该管道中最右侧的球推入右边输出管道。

例如：我们首先从下管道中移一个球到输出管道中，将得到图 2 所示的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/xj1kay44.png)

假设上管道中有 $n$ 个球, 下管道中有 $m$ 个球，则整个游戏过程需要进行 $n+m$ 次操作，即将所有左侧管道中的球移入输出管道。最终 $n+m$ 个球在输出管道中从右到左形成输出序列。

爱好数学的小 X 知道，他共有 $\dbinom{n+m}{m}$ 种不同的操作方式，而不同的操作方式可能导致相同的输出序列。举个例子，对于图 3 所示的游戏情形：

![](https://cdn.luogu.com.cn/upload/image_hosting/0m1t5d3h.png)

我们用 A 表示浅色球，B 表示深色球。并设移动上管道右侧球的操作为 U，移动下管道右侧球的操作为 D，则共有 $\binom{2+1}{1}=3$ 种不同的操作方式，分别为 UUD，UDU，DUU；最终在输出管道中形成的输出序列（从右到左）分别为 BAB，BBA，BBA。可以发现后两种操作方式将得到同样的输出序列。

假设最终可能产生的不同种类的输出序列共有 $K$ 种，其中：第 $i$ 种输出序列的产生方式（即不同的操作方式数目）有 $a_i$ 个。聪明的小 X 早已知道，

$$
\sum a_i=\binom{n+m}{m}
$$

因此，小 X 希望计算得到：

$$
\sum a_i^2
$$

你能帮助他计算这个值么？由于这个值可能很大，因此只需要输出该值对 $1024523$ 取模后的结果。

## 输入格式

输入文件中的第一行为两个整数 $n,m$，分别表示上下两个管道中球的数目。

第二行中为一个长度为 $n$ 的字符串，表示上管道中从左到右球的类型。其中：A 表示浅色球，B 表示深色球。

第三行中为一个长度为 $m$ 的字符串，表示下管道中从左到右球的类型。

保证两个字符串都只包含 A,B 两个字母。
## 输出格式

输出一个整数，即为 $\sum a_i^2$ 对 $1024523$ 取模的结果。

## 样例

### 样例输入 #1
```
2 1
AB
B

```
### 样例输出 #1
```
5
```
## 提示

### 样例解释

样例对应图 3。

共有两种不同的输出序列形式，序列 BAB 有 $1$ 种产生方式，而序列 BBA 有 $2$ 种产生方式，因此答案为 $5$。

### 数据范围

- 对于 $30\%$ 的数据，满足 $m,n \leq 12$；
- 对于 $100\%$ 的数据，满足 $1 \leq m,n \leq 500$。


---

---
title: "淘汰赛制"
layout: "post"
diff: 提高+/省选-
pid: P1769
tag: ['动态规划 DP', '递推', '递归', 'NOI 导刊']
---
# 淘汰赛制
## 题目描述

淘汰赛制是一种极其残酷的比赛制度。$2^n$ 名选手分别标号 $1,2,3,\cdots,2^n-1,2^n$，他们将要参加 $n$ 轮的激烈角逐。每一轮中，将所有参加该轮的选手按标号从小到大排序后，第 $1$ 位与第 $2$ 位比赛，第 $3$ 位与第 $4$ 位比赛，第 $5$ 位与第 $6$ 位比赛……只有每场比赛的胜者才有机会参加下一轮的比赛（不会有平局）。这样，每轮将淘汰一半的选手。$n$ 轮过后，只剩下一名选手，该选手即为最终的冠军。

现在已知每位选手分别与其他选手比赛获胜的概率，请你预测一下谁夺冠的概率最大。
## 输入格式

第一行是一个整数 $n(1 \le n \le 10)$，表示总轮数。接下来 $2^n$ 行，每行 $2^n$ 个整数，第 $i$ 行第 $j$ 个是 $p_{i,j}$。（$0 \le p_{i_j} \le 100$，$p_{i,i}=0$，$p_{i,j}+p_{j,i}=100$），表示第 $i$ 号选手与第 $j$ 号选手比赛获胜的概率。
## 输出格式

输出只有一个整数 $c$，表示夺冠概率最大的选手编号（若有多位选手，输出编号最小者）。

## 样例

### 样例输入 #1
```
2
0 90 50 50
10 0 10 10
50 90 0 50
50 90 50 0

```
### 样例输出 #1
```
 1
```
## 提示

- $30\%$ 的数据满足 $n \le 3$；
- $100\%$ 的数据满足 $n \le 10$。

_NOI导刊 2010 提高（01）



---

---
title: "方程的解"
layout: "post"
diff: 提高+/省选-
pid: P1771
tag: ['动态规划 DP', '数学', '高精度', '递归', 'NOI 导刊']
---
# 方程的解
## 题目描述

佳佳碰到了一个难题，请你来帮忙解决。对于不定方程 $a_1+a_2+\cdots +a_{k-1}+a_k=g(x)$，其中 $k\ge 2$ 且 $k\in \mathbb{N}^*$，$x$ 是正整数，$g(x)=x^x \bmod 1000$（即 $x^x$ 除以 $1000$ 的余数），$x,k$ 是给定的数。我们要求的是这个不定方程的正整数解组数。

举例来说，当 $k=3,x=2$ 时，方程的解分别为：
$$\begin{cases} a_1=1\\ a_2=1\\ a_3=2 \end{cases}$$
$$\begin{cases} a_1=1\\ a_2=2\\ a_3=1 \end{cases}$$
$$\begin{cases} a_1=2\\ a_2=1\\ a_3=1 \end{cases}$$
## 输入格式

输入有且只有一行，为用空格隔开的两个正整数，依次为 $k,x$。
## 输出格式

输出有且只有一行，为方程的正整数解组数。

## 样例

### 样例输入 #1
```
3 2
```
### 样例输出 #1
```
3
```
## 提示

- 对于 $40\%$ 的数据，$\mathit{ans} \le 10^{16}$；
- 对于 $100\%$ 的数据，$k \le 100$，$x \le 2^{31}-1$，$k \le g(x)$。

NOI导刊2010提高（01）



---

---
title: "[ZJOI2006] 物流运输"
layout: "post"
diff: 提高+/省选-
pid: P1772
tag: ['动态规划 DP', '图论', '2006', '各省省选', '浙江', 'NOI 导刊', '最短路']
---
# [ZJOI2006] 物流运输
## 题目描述

物流公司要把一批货物从码头 A 运到码头 B。由于货物量比较大，需要 $n$ 天才能运完。货物运输过程中一般要转停好几个码头。  

物流公司通常会设计一条固定的运输路线，以便对整个运输过程实施严格的管理和跟踪。由于各种因素的存在，有的时候某个码头会无法装卸货物。这时候就必须修改运输路线，让货物能够按时到达目的地。  

但是修改路线是—件十分麻烦的事情，会带来额外的成本。因此物流公司希望能够订一个 $n$ 天的运输计划，使得总成本尽可能地小。

## 输入格式

第一行是四个整数 $n,m,k,e$。$n$ 表示货物运输所需天数，$m$ 表示码头总数，$k$ 表示每次修改运输路线所需成本，$e$ 表示航线条数。  

接下来 $e$ 行每行是一条航线描述，包括了三个整数，依次表示航线连接的两个码头编号以及航线长度。其中码头 A 编号为 $1$，码头 B 编号为 $m$。单位长度的运输费用为 $1$。航线是**双向**的。  

再接下来一行是一个整数 $d$，后面的 $d$ 行每行是三个整数 $p,a,b$。表示编号为 $p$ 的码头在 $[a,b]$ 天之内无法装卸货物。同一个码头有可能在多个时间段内不可用。但任何时间都存在至少一条从码头 A 到码头 B 的运输路线。

## 输出格式

包括了一个整数表示最小的总成本。  
总成本为 $n$ 天运输路线长度之和 $+ k \times$ 改变运输路线的次数。

## 样例

### 样例输入 #1
```
  5 5 10 8
  1 2 1
  1 3 3
  1 4 2
  2 3 2
  2 4 4
  3 4 1
  3 5 2
  4 5 2
  4
  2 2 3
  3 1 1
  3 3 3
  4 4 5

```
### 样例输出 #1
```
32
```
## 提示

【数据范围】
对于 $100\%$ 的数据，$1 \le n \le 100$，$1\le m \le 20$, $1 \le k \le 500$, $1 \le e \le 200$。

【样例输入说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/4lcnync6.png)

上图依次表示第 $1$ 至第 $5$ 天的情况，阴影表示不可用的码头。

【样例输出说明】

前三天走 $1 \to 4 \to 5$，后两天走 $1 \to 3 \to 5$，这样总成本为 $(2+2)\times 3+(3+2)\times 2+10=32$。

\_NOI导刊2010提高（01）



---

---
title: "万圣节后的早晨"
layout: "post"
diff: 提高+/省选-
pid: P1778
tag: ['NOI 导刊']
---
# 万圣节后的早晨
## 题目描述

要求你写一个程序，在一个地图中，找到最小步数将每个鬼移动到他们指定的位置。地图包含一些小方格。每格要么是墙（鬼不能进入），要么是走廊（鬼能进入）。

每一步里，你可以同时移动任意数量的鬼。每个鬼要么待在原地不动，要么移动到相邻的格子里（相邻的格子有公共边），如果移动满足下列条件，则移动是可行的。

1. 没有一个以上的鬼在同一个格子里；
2. 没有一对鬼在一步里交换了位置。

例如，假设鬼的位置是如右上图所示的，其中sharp(#)表示墙，空格表示走廊，a,b,c表示鬼：

```plain
####
 ab#
#c##
####
```
经过一步移动后，地图可以变成如下的样子：

```plain
####     ####     ####       ####
 ab#     a b#     acb#       ab #
#c##     #c##     # ##       #c##   
####     ####     ####       ####
```
## 输入格式

输入包括最多 $10$ 组数据，每组数据包含一幅地图。输入格式如下：

$$\begin{matrix}
w & h & n \\
c_{1,1} & c_{1,2} & \cdots & c_{1,w} \\
c_{2,1} & c_{2,2} & \cdots & c_{2,w} \\
\vdots & \vdots & \ddots & \vdots \\
c_{h,1} & c_{h,2} & \cdots & c_{h,w} \\
\end{matrix}$$

第一行的 $w，h$ 和 $n$ 表示地图的宽度和高度，$n$ 表示鬼的数目，他们满足 $4 \le w \le 16$，$4 \le h \le 16$，$1 \le n \le 3$。

接下来 $h$ 行，每行 $w$ 个字符：

- 一个 `#` 表示墙。
- 一个小写字母表示鬼的初始位置（该位置也是走廊）。
- 一个大写字母表示鬼的目标位置（该位置也是走廊）。
- 一个空格表示空的走廊。

在每幅地图里，前 $n$ 个小写字母和前 $n$ 个大写字母表示鬼的初始位置及鬼的目标位置。我们需要将小写字母表示的鬼移动到对应的大写字母的位置里。

最后一组数据后一行有三个 $0$。
## 输出格式

对每组数据输出一行一个整数，表示最小的移动步数。

## 样例

### 样例输入 #1
```
5 5 2
#####
#A#B#
#   #
#b#a#
#####
16 4 3
################
## ########## ##
#    ABCcba    #
################
16 16 3
################
### ##    #   ##
##  #  ##   # c#
#  ## ########b#
# ##  # #   #  #
#  # ##   # # ##
##  a#  # # #  #
### ## #### ## #
##   #   #  #  #
#  ##### # ## ##
####   #B# #   #
##  C#   #   ###
#  # # ####### #
# ######  A##  #
#        #     #
################
```
### 样例输出 #1
```
7
36
77
```


---

---
title: "魔鬼杀手"
layout: "post"
diff: 提高+/省选-
pid: P1779
tag: ['NOI 导刊']
---
# 魔鬼杀手
## 题目描述

你生活在一个怪兽世界里。你需要用魔法反抗这些怪兽。

每个怪兽都有一定的 hit points，表示他们的生命值。你可以靠施魔法，降低怪兽的 hit points。每个魔法都会有一定的 damage，表示会减少被攻击者 damage 的 hit point。一个怪兽被击败了当前仅当它的 hitpoint 小于等于 0。另一方面，魔法是要消耗魔力的。因为你的魔力是有限的，你希望用最少的魔力击败所有的怪兽。写一个程序完成这个任务。

## 输入格式

输入按如下的格式给出：

| | | | | 
| :-: | :-: | :-: | :-: |
| $N$ | | | |
| $HP_1$ | | | |
| $HP_2$ | | | |
| ... | | | |
| $HP_N$ | | | |
| $M$ | | | |
| $Name_1$ | $MP_1$ | $Target_1$ | $Damage_1$ |
| $Name_2$ | $MP_2$ | $Target_2$ | $Damage_2$ |
| ... | | | |
| $Name_M$ | $MP_M$ | $Target_M$ | $Damage_M$ |

$N$ 是怪兽的数量（$1\le N\le 100$），$HP_{i}$ 表示第 $i$ 个怪兽的 hit point（$l\le HP_i\le 100000$），$M$ 表示可用的魔法数量（$1\le M\le 100$），$Name_j$ 是第 $j$ 种魔法的名字，最长会有 $30$ 个大写或小写字母，$MP_j$ 是这种魔法需要消耗的魔力（$0\le MP_j\le 99$），$Target_j$ 要么是 "Single"，要么是 "All"，表示该魔法只攻击单个怪兽或对全体怪兽同时有效。$Damage_j$ 表示对于所有玫击对象，可以减少攻击对象 $Damage_j$ 的 hit point（$0\le Damage_j\le 999999$）。

所有数字都是整数。最少有一种魔法的 $Damage$ 是非零的。
## 输出格式

输出一行，包含一个整数，表示最小需要消耗的魔力。

## 样例

### 样例输入 #1
```
3
8000 15000 30000
3
Flare 45 Single 8000
Meteor 62 All 6000
Ultimate 80 All 9999
```
### 样例输出 #1
```
232
```


---

---
title: "染色的立方体"
layout: "post"
diff: 提高+/省选-
pid: P1780
tag: ['NOI 导刊']
---
# 染色的立方体
## 题目描述

小胖最近迷上了3D物体，尤其是立方体。他手里有很多个立方体，他想让所有的立方体全都长得一样，所以他决定给某些立方体的表面重涂颜色，使得所有的立方体完全相同。但是小胖是很懒的，他想知道最少涂多少次颜色，可以让所有立方体完全相同。

## 输入格式

每个测试点包含至多 $200$ 组数据。

每组数据第一行 $n\ (1≤n≤4)$，表示立方体的数量，接下来 $n$ 行，每行 $6$ 个字符串 $\mathit{color}_1,\allowbreak\mathit{color}_2,\allowbreak\mathit{color}_3,\allowbreak\mathit{color}_4,\allowbreak\mathit{color}_5,\allowbreak\mathit{color}_6$，表示立方体 $6$ 个面的颜色。

其中，面的标号如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/xlfu6oe0.png)

两个立方体被视为相同，当且仅当它们可以在某种摆放方式下，每个面的颜色都对应相同。

如下图所示的两个立方体是相同的。

![](https://cdn.luogu.com.cn/upload/image_hosting/equmi6mp.png)

如下图所示的两个立方体是不同的。

![](https://cdn.luogu.com.cn/upload/image_hosting/jqp05oyq.png)

一种涂色的方案如下：
 
![](https://cdn.luogu.com.cn/upload/image_hosting/mewvgalo.png)

## 输出格式

每组数据，输出一行一个整数，表示最少的涂色数。（涂一个面算一次涂色）

## 样例

### 样例输入 #1
```
3
scarlet green blue yellow magenta cyan
blue pink green magenta cyan lemon
purple red blue yellow cyan green
2
red green blue yellow magenta cyan
cyan green blue yellow magenta red
2
red green gray gray magenta cyan
cyan green gray gray magenta red
2
red green blue yellow magenta cyan
magenta red blue yellow cyan green
3
red green blue yellow magenta cyan
cyan green hlue yellow magenta red
magenta red blue yellow cyan green
3
blue green green green green blue
green blue blue green green green
green green green green green sea-green
3
red yellow red yellow red yellow
red red yellow yellow red yellow
red red red red red red
4
violet violet salmon salmon salmon salmon
violet salmon salmon salmon salmon violet
violet violet salmon salmon violet violet
violet violet violet violet salmon salmon
1
red green hlue yellow magenta cyan
4
magenta pink red scarlet vermilion wine-red
aquamarine blue cyan indigo sky-blue turciuoise-blue
blond cream chrome-yellow lemon olive yellow
chrome-green emerald-green green olive vilidian sky-blue
0
```
### 样例输出 #1
```
4
2
0
0
2
3
4
4
0
16
```


---

---
title: "关灯"
layout: "post"
diff: 提高+/省选-
pid: P1805
tag: ['高精度', '递推', 'NOI 导刊', '线性递推']
---
# 关灯
## 题目描述

在某条道路上，有 $n$ 盏灯排成一排，它们有的是开着的，有的是关着的。

由于天马上就要亮了，上级给了你一个任务：把所有的灯都关掉。

只不过，这些灯都比较智能，不会被轻易关掉。它们的开或关遵循如下规则：

- 每一步只能开或关一盏灯。
- 编号为 $1$ 的灯可以随意开或关。
- 如果编号为 $1, 2, \cdots,k-1$ 的灯都关上了了，并且编号为 $k$ 的灯在开着，我们可以随意开或关第 $k+1$ 盏灯。

在关灯之前，请你计算：至少要多少步才能关上所有灯？
## 输入格式

第 $1$ 行一个整数 $n$，表示灯的个数。

第 $2$ 行有 $n$ 个整数，如果第 $i$ 个整数 $O_i=0$，表示第 $i$ 个盏灯初始的时候是关着的；如果 $O_i=1$，表示第 $i$ 盏灯初始的时候是开着的。
## 输出格式

共一行一个整数，表示最少需要多少步才能关上所有灯。

## 样例

### 样例输入 #1
```
4

1 0 1 0
```
### 样例输出 #1
```
6
```
## 提示

【输出解释】

- 初始状态 $1010$；
- 第 $1$ 步 $1110$；
- 第 $2$ 步 $0110$；
- 第 $3$ 步 $0100$；
- 第 $4$ 步 $1100$；
- 第 $5$ 步 $1000$；
- 第 $6$ 步 $0000$。

### 数据范围及约定

- 对于 $40\%$ 的数据，$n \le 30$；
- 对于 $70\%$ 的数据，$n \le 300$；
- 对于 $100\%$ 的数据，$n \le 1000$。


---

---
title: "集合分组【征集 spj】"
layout: "post"
diff: 提高+/省选-
pid: P1810
tag: ['NOI 导刊']
---
# 集合分组【征集 spj】
## 题目描述

现有 $k$ 个整数集合，第 $i$ 个集合有 $s_i$ 个元素。

集合中的数都为正数，且不大于 $n$。现定义集合 $A$ 与集合 $B$ 相似，当且仅当满足如下条件之一：

1. $B$ 与 $A$ 相似；
2. 将 $A$ 集合删去一个元素，或更改一个元素的值之后 $A$ 集合与 $B$ 集合相等。

现要将 $K$ 个集合分成至多 $M$ 组（$M>N$），使得每一组内的集合互不相似。要求你给出一种合法的方案。如果无解请输出 `impossible`。
## 输入格式

输入文件第一行有三个数 $n, k, m$，意义如题目所述。

接下来有 $k$ 行，每行第一数 $s_i$ 表示序列长度。之后 $s_i$ 个数为些集合的元素。

## 输出格式

如果存在合法方案，输出 $k$ 个数，表示每个集合（按输入顺序）被分到的组的编号（$1\sim m$）。否则，若不存在合法方案则输出 `impossible`。
## 样例

### 样例输入 #1
```
8 20 12 
5 1 3 5 6 4 
5 1 3 5 6 3 
4 5 6 3 3 
4 5 6 3 4 
4 4 6 5 8 
4 7 7 7 7 
3 7 7 7 
2 2 2 
3 2 2 7 
3 1 2 3 
3 1 2 4 
10 1 2 3 4 5 6 7 8 7 6 
10 8 7 6 5 4 3 2 1 2 1 
20 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 3 5 7 
5 4 6 4 6 4 
5 6 4 6 4 6 
6 6 6 6 6 6 6 
3 6 6 6 
1 1 
1 2
```
### 样例输出 #1
```
2 
1 
9 
1 
6 
2 
4 
5 
3 
7 
8 
5 
4 
8
7 
9 
1 
1 
2
3
```
## 提示

### 数据范围及约定

- 对于 $30\%$ 的数据满足 $n \le 10$，$m \le 2$，$k \le 10$；
- 对于 $100\%$ 的数据满足 $1\le n \le 100$，$1\le m \le 100$，$1\le k \le 50000$，$1\le s_i \le 100$。


---

---
title: "最短路"
layout: "post"
diff: 提高+/省选-
pid: P1811
tag: ['NOI 导刊', 'Special Judge', 'O2优化']
---
# 最短路
## 题目描述

给定一个包含 $N$ 个点，$M$ 条边的无向图，每条边的边权均为 $1$。

再给定 $K$ 个三元组 $(A,B,C)$，表示从 $A$ 点走到 $B$ 点后不能往 $C$ 点走。注意三元组是有序的，如可以从 $B$ 点走到 $A$ 点再走到 $C$。

现在你要在 $K$ 个三元组的限制下，找出 $1$ 号点到 $N$ 号点的最短路径，并输出任意一条合法路径，会有 Check 检查你的输出。
## 输入格式

输入文件第一行有三个数 $N$，$M$，$K$，意义如题目所述。

接下来 $M$ 行每行两个数 $A$，$B$，表示 $A$，$B$ 间有一条边。

再下面 $K$ 行，每行三个数 $(A,B,C)$ 描述一个三元组。
## 输出格式

输出文件共两行数，第一行一个数 $S$ 表示最短路径长度。 。

第二行 $S+1$ 个数，表示从 $1$ 到 $N$ 所经过的节点。 。
## 样例

### 样例输入 #1
```
4 4 2
1 2
2 3
3 4
1 3
1 2 3
1 3 4
```
### 样例输出 #1
```
4 
1 3 2 3 4 
```
## 提示

对于 $40\%$ 的数据满足 $N \le 10$，$M \le 20$，$K \le 5$。

对于 $100\%$ 的数据满足 $N \le 3000$，$M \le 20000$，$K \le 100000$。


---

---
title: "棋盘染色"
layout: "post"
diff: 提高+/省选-
pid: P1817
tag: ['NOI 导刊']
---
# 棋盘染色
## 题目描述

给定一个 $N \times M$ 的网格，每个格子可以染成黑色或者白色，要求所有黑色格子连通，所有白色格子连通，并且至少有一个黑色格子贴边，至少有一个白色格子贴边。问有多少种染色方法？ 
## 输入格式

第一行有两个正整数 $N, M$。
## 输出格式

只有一个正整数表示答案。

## 样例

### 样例输入 #1
```
1 2   

```
### 样例输出 #1
```
2   

```
### 样例输入 #2
```
2 3

```
### 样例输出 #2
```
30

```
## 提示

对于 $100 \%$ 的数据：$1 \le N \le 7$，$1 \le M \le 8$。



---

---
title: "电影投票"
layout: "post"
diff: 提高+/省选-
pid: P1818
tag: ['NOI 导刊']
---
# 电影投票
## 题目描述

有一个投票系统可以给电影评分，规定每票都必须投 $1$ 到 $10$ 的整数。现在希望投尽量少的票让一个电影的平均分数低于某个值。
## 输入格式

多组数据，对于每组数据只有一行，有两个带 $1$ 位小数的实数 $X$ 、 $Y$ 和一个正整数 $N$，表示一部电影的平均得分保留 $1$ 位小数后的结果和 XP 期望的平均得分保留一位小数后的结果，并且该电影已经被投了 $N$ 次票了。保证 $Y$ 小于等于 $X$。
## 输出格式

对于每组数据，输出一个正整数 $\mathit{ans}$，表示最坏情况下只要 XP 投 $\mathit{ans}$ 张票，一定能让这部电影的平均得分保留一位小数后小于等于 $Y$。
## 样例

### 样例输入 #1
```
9.5 2.0 12 

4.4 3.4 12478   

10 3.4 23577
```
### 样例输出 #1
```
86   

5094   

63033
```
## 提示

### 数据范围及约定

- 对于 $30\%$ 的数据，$1\le N \le 100$，$1\le T \le 100$；
- 对于 $100\%$ 的数据，$1\le T \le 10^4$，$X,Y\in[1,10]$，$1\le N \le 10^6$。

### 注意事项

保留一位小数采取四舍五入保留法。实数可能会有精度误差。


---

---
title: "速算游戏"
layout: "post"
diff: 提高+/省选-
pid: P1834
tag: ['NOI 导刊']
---
# 速算游戏
## 题目描述

jyx 和 cyy 打赌，比谁 $24$ 点算得快，算得慢的那个人请客。$24$ 点的规则是这样的：给定 $4$ 个 $1\sim 9$ 的整数，用括号改变运算顺序，通过加、减、乘、除中的一系列运算，得到整数 $24$。

注意所有中间结果必须是整数（例如 $(2\times 2)/4$ 是允许的，而 $2\times (2/4)$ 是不允许的）。

为了赢得这个比赛，请写一个程序帮助我作弊，快速地计算出 $24$ 点。
## 输入格式

一行 $4$ 个整数，为给定的 $4$ 个数字。输入数据保证有解。

## 输出格式

一行，以字符串的形式输出结果。注意将每一步的运算的括号补齐（例如 $(3+5)+6$ 和 $3\times(5+6)$）。如果有多种解答，输出字典顺序最小的一个。
## 样例

### 样例输入 #1
```
2 3 5 7 
```
### 样例输出 #1
```
(((3*5)+2)+7)
```


---

---
title: "单人纸牌"
layout: "post"
diff: 提高+/省选-
pid: P1837
tag: ['NOI 导刊']
---
# 单人纸牌
## 题目描述

单人纸牌游戏，共 $36$ 张牌分成 $9$ 叠，每叠 $4$ 张牌面向上。每次，游戏者可以从某两个不同的牌堆最顶上取出两张牌面相同的牌（如黑桃 $10$ 和梅花 $10$）并且一起拿走。如果最后所有纸牌都被取走，则游戏者就赢了，否则游戏者就输了。

George 很热衷于玩这个游戏，但是一旦有时有多种选择的方法，George 就不知道取哪一种好了，George 会从中随机地选择一种走，例如：顶上的 $9$ 张牌为 $\tt KS,\tt KH,\tt KD,\tt 9H,\tt 8S,\tt 8D,\tt 7C,\tt 7D,\tt 6H$，显然有 $5$ 种取法：$\tt (KS,KH),(KS,KD),(KH,KD),(8S,8D),(7C,7D)$，当然 George 取到每一种取法的概率都是 $1/5$。

有一次，George 的朋友 Andrew 告诉他，这样做是很愚蠢的，不过 George 不相信，他认为如此玩最后成功的概率是非常大的。请写一个程序帮助 George 证明他的结论：计算按照他的策略，最后胜利的概率。
## 输入格式

输入共 $9$ 行，每行 $4$ 组用空格分开的字串，每个字串两个字符，分别表示牌面和花色，按照从堆底到堆顶的顺序给出。

## 输出格式

一行，最后胜利的概率，精确到小数点后 $6$ 位。

## 样例

### 样例输入 #1
```
AS 9S 6C KS 

JC QH AC KH 

7S QD JD KD 

QS TS JS 9H 

6D TD AD 8S 

QC TH KC 8D 

8C 9D TC 7C 

9C 7H JH 7D 

8H 6S AH 6H 
```
### 样例输出 #1
```
0.589314
```


---

---
title: "游戏"
layout: "post"
diff: 提高+/省选-
pid: P1846
tag: ['NOI 导刊']
---
# 游戏
## 题目描述

给定两个正整数数列，你要用它们来做一个游戏：你需要对数列进行若干次操作，每一次操作，应选择两个正整数 $k_1$ 和 $k_2$，并删除第一个数列的最后 $k_1$ 个数，计算出它们的和 $s_1$；删除第二个数列的最后 $k_2$ 个数，计算出它们的和 $s_2$。这一次操作的得分就是 $(s_2-k_2)\times(s_1-k_1)$。两个数列应同时被清空，不允许一个数列空了，而另一个数列中还有数。游戏的总得分就是每一次操作的得分总和。

求最小的总得分。
## 输入格式

第一行是两个整数 $n$ 和 $m$，分别表示第一个数列和第二个数列的初始长度。

第二行有 $n$ 个正整数，是第一个数列的数。

第三行有 $m$ 个正整数，是第二个数列的数。

数列中的数都不超过 $1000$。
## 输出格式

一个整数，表示最小的总得分。

## 样例

### 样例输入 #1
```
3 2
1 2 3 
1 2 
```
### 样例输出 #1
```
2
```
## 提示

- 对于 $20\%$ 的数据，$n,m\le20$；
- 对于 $40\%$ 的数据，$n,m\le200$；
- 对于 $100\%$ 的数据，$n,m\le2000$。


---

---
title: "[NOIP 2016 提高组] 换教室"
layout: "post"
diff: 提高+/省选-
pid: P1850
tag: ['动态规划 DP', '2016', 'NOIP 提高组', '期望']
---
# [NOIP 2016 提高组] 换教室
## 题目背景

NOIP2016 提高组 D1T3
## 题目描述

对于刚上大学的牛牛来说，他面临的第一个问题是如何根据实际情况申请合适的课程。


在可以选择的课程中，有 $2n$ 节课程安排在 $n$ 个时间段上。在第 $i$（$1 \leq i \leq n$）个时间段上，两节内容相同的课程同时在不同的地点进行，其中，牛牛预先被安排在教室 $c_i$ 上课，而另一节课程在教室 $d_i$ 进行。


在不提交任何申请的情况下，学生们需要按时间段的顺序依次完成所有的 $n$ 节安排好的课程。如果学生想更换第 $i$ 节课程的教室，则需要提出申请。若申请通过，学生就可以在第 $i$ 个时间段去教室 $d_i$ 上课，否则仍然在教室 $c_i$ 上课。


由于更换教室的需求太多，申请不一定能获得通过。通过计算，牛牛发现申请更换第 $i$ 节课程的教室时，申请被通过的概率是一个已知的实数 $k_i$，并且对于不同课程的申请，被通过的概率是互相独立的。


学校规定，所有的申请只能在学期开始前一次性提交，并且每个人只能选择至多 $m$ 节课程进行申请。这意味着牛牛必须一次性决定是否申请更换每节课的教室，而不能根据某些课程的申请结果来决定其他课程是否申请；牛牛可以申请自己最希望更换教室的 $m$ 门课程，也可以不用完这 $m$ 个申请的机会，甚至可以一门课程都不申请。


因为不同的课程可能会被安排在不同的教室进行，所以牛牛需要利用课间时间从一间教室赶到另一间教室。


牛牛所在的大学有 $v$ 个教室，有 $e$ 条道路。每条道路连接两间教室，并且是可以双向通行的。由于道路的长度和拥堵程度不同，通过不同的道路耗费的体力可能会有所不同。 当第 $i$（$1 \leq i \leq n-1$）节课结束后，牛牛就会从这节课的教室出发，选择一条耗费体力最少的路径前往下一节课的教室。


现在牛牛想知道，申请哪几门课程可以使他因在教室间移动耗费的体力值的总和的期望值最小，请你帮他求出这个最小值。

## 输入格式

第一行四个整数 $n,m,v,e$。$n$ 表示这个学期内的时间段的数量；$m$ 表示牛牛最多可以申请更换多少节课程的教室；$v$ 表示牛牛学校里教室的数量；$e$ 表示牛牛的学校里道路的数量。


第二行 $n$ 个正整数，第 $i$（$1 \leq i \leq n$）个正整数表示 $c_i$，即第 $i$ 个时间段牛牛被安排上课的教室；保证 $1 \le c_i \le v$。


第三行 $n$ 个正整数，第 $i$（$1 \leq i \leq n$）个正整数表示 $d_i$，即第 $i$ 个时间段另一间上同样课程的教室；保证 $1 \le d_i \le v$。


第四行 $n$ 个实数，第 $i$（$1 \leq i \leq n$）个实数表示 $k_i$，即牛牛申请在第 $i$ 个时间段更换教室获得通过的概率。保证 $0 \le k_i \le 1$。


接下来 $e$ 行，每行三个正整数 $a_j, b_j, w_j$，表示有一条双向道路连接教室 $a_j, b_j$，通过这条道路需要耗费的体力值是 $w_j$；保证 $1 \le a_j, b_j \le v$，$1 \le w_j \le 100$。


保证 $1 \leq n \leq 2000$，$0 \leq m \leq 2000$，$1 \leq v \leq 300$，$0 \leq e \leq 90000$。


保证通过学校里的道路，从任何一间教室出发，都能到达其他所有的教室。


保证输入的实数最多包含 $3$ 位小数。

## 输出格式

输出一行，包含一个实数，四舍五入精确到小数点后恰好 $2$ 位，表示答案。你的输出必须和标准输出完全一样才算正确。

测试数据保证四舍五入后的答案和准确答案的差的绝对值不大于 $4 \times 10^{-3}$。（如果你不知道什么是浮点误差，这段话可以理解为：对于大多数的算法，你可以正常地使用浮点数类型而不用对它进行特殊的处理）

## 样例

### 样例输入 #1
```
3 2 3 3
2 1 2
1 2 1
0.8 0.2 0.5 
1 2 5
1 3 3
2 3 1

```
### 样例输出 #1
```
2.80
```
## 提示

**样例 1 说明**

所有可行的申请方案和期望收益如下：

- 不作申请，耗费的体力值的期望为 $8.0$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     无      |  $1.0$  |  $8$  |

- 申请更换第 $1$ 个时间段的上课教室，耗费的体力值的期望为 $4.8$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $1$      |  $0.8$  |  $4$  |
|     无      |  $0.2$  |  $8$  |

- 申请更换第 $2$ 个时间段的上课教室，耗费的体力值的期望为 $6.4$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $2$      |  $0.2$  |  $0$  |
|     无      |  $0.8$  |  $8$  |

- 申请更换第 $3$ 个时间段的上课教室，耗费的体力值的期望为 $6.0$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $3$      |  $0.5$  |  $4$  |
|     无      |  $0.5$  |  $8$  |

- 申请更换第 $1,2$ 个时间段的上课教室，耗费的体力值的期望为 $4.48$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $1,2$      |  $0.16$  |  $4$  |
|     $1$      |  $0.64$  |  $4$  |
|     $2$     |  $0.04$  |  $0$  |
|     无      |  $0.16$  |  $8$  |

- 申请更换第 $1,3$ 个时间段的上课教室，耗费的体力值的期望为 $2.8$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $1,3$      |  $0.4$  |  $0$  |
|     $1$      |  $0.4$  |  $4$  |
|     $3$     |  $0.1$  |  $4$  |
|     无      |  $0.1$  |  $8$  |

- 申请更换第 $2,3$ 个时间段的上课教室，耗费的体力值的期望为 $5.2$。

| 申请通过的时间段 | 出现的概率 | 耗费的体力值 |
| :--------: | :----: | :----: |
|     $2,3$      |  $0.1$  |  $4$  |
|     $2$      |  $0.1$  |  $0$  |
|     $3$     |  $0.4$  |  $4$  |
|     无      |  $0.4$  |  $8$  |

因此，最优方案为：申请更换第 $1,3$ 个时间段的上课教室。耗费的体力值的期望为 $2.8$。 

**提示**

1. 道路中可能会有多条双向道路连接相同的两间教室。 也有可能有道路两端连接的是同一间教室。
2. 请注意区分 $n,m,v,e$ 的意义, $n$ 不是教室的数量, $m$ 不是道路的数量。

**数据范围与说明**

| 测试点编号 | $n\le$ | $m\le$ | $v\le$ | 是否具有特殊性质 1 | 是否具有特殊性质 2 |
| :--------: | :----: | :----: | :----: | :----------------: | :----------------: |
|     1      |  $1$   |  $1$   | $300$  |      $\times$      |      $\times$      |
|     2      |  $2$   |  $0$   |  $20$  |      $\times$      |      $\times$      |
|     3      |  $2$   |  $1$   | $100$  |      $\times$      |      $\times$      |
|     4      |  $2$   |  $2$   | $300$  |      $\times$      |      $\times$      |
|     5      |  $3$   |  $0$   |  $20$  |      $\surd$       |      $\surd$       |
|     6      |  $3$   |  $1$   | $100$  |      $\surd$       |      $\times$      |
|     7      |  $3$   |  $2$   | $300$  |      $\times$      |      $\times$      |
|     8      |  $10$  |  $0$   | $300$  |      $\surd$       |      $\surd$       |
|     9      |  $10$  |  $1$   |  $20$  |      $\surd$       |      $\times$      |
|     10     |  $10$  |  $2$   | $100$  |      $\times$      |      $\times$      |
|     11     |  $10$  |  $10$  | $300$  |      $\times$      |      $\surd$       |
|     12     |  $20$  |  $0$   |  $20$  |      $\surd$       |      $\times$      |
|     13     |  $20$  |  $1$   | $100$  |      $\times$      |      $\times$      |
|     14     |  $20$  |  $2$   | $300$  |      $\surd$       |      $\times$      |
|     15     |  $20$  |  $20$  | $300$  |      $\times$      |      $\surd$       |
|     16     | $300$  |  $0$   |  $20$  |      $\times$      |      $\times$      |
|     17     | $300$  |  $1$   | $100$  |      $\times$      |      $\times$      |
|     18     | $300$  |  $2$   | $300$  |      $\surd$       |      $\surd$       |
|     19     | $300$  | $300$  | $300$  |      $\times$      |      $\surd$       |
|     20     | $2000$ |  $0$   |  $20$  |      $\times$      |      $\times$      |
|     21     | $2000$ |  $1$   |  $20$  |      $\times$      |      $\times$      |
|     22     | $2000$ |  $2$   | $100$  |      $\times$      |      $\times$      |
|     23     | $2000$ | $2000$ | $100$  |      $\times$      |      $\times$      |
|     24     | $2000$ | $2000$ | $300$  |      $\times$      |      $\times$      |
|     25     | $2000$ | $2000$ | $300$  |      $\times$      |      $\times$      |
 

特殊性质 1：图上任意不同的两点 $u,v$ 间，存在一条耗费体力最少的路径只包含一条道路。

特殊性质 2：对于所有的 $1≤ i≤ n,\ k_i= 1$。



---

---
title: "独眼兔"
layout: "post"
diff: 提高+/省选-
pid: P1863
tag: ['计算几何', 'NOI 导刊']
---
# 独眼兔
## 题目描述

太郎有一只特殊的兔子，它只有一只左眼，所以当它移动时是不能向右转弯的。一天，太郎跟独眼兔做一个游戏，太郎在平面内放了 $n$ 个萝卜，每个萝卜有个位置 $(x_i,y_i)$，且任意两个萝卜的 $x_i$，$y_i$ 都是不相同的，独眼兔要去吃这些萝卜。设萝卜 $A(x_i,y_i)$ 是所有萝卜中最小的，那独眼兔会从 $(0,y_i)$ 出发，走向萝卜 $A$，然后开始吃萝卜。当它吃完一个萝卜后，独眼兔会确定下一个萝卜作为目标，然后径直向萝卜走去，当然当它移动的时候是不能向右转弯的。独眼兔还有一个特点，它走过的路径上会留下特殊的气味，所以独眼兔不希望它将要走的路与前面它走过的路相交。太郎想知道独眼兔如何才能吃到最多的萝卜。
## 输入格式

第一行是个整数 $n$；

接下来 $n$ 行，每行两个整数。第 $i+1$ 行表示第 $i$ 号萝卜的位置 $(x_i,y_i)$。
## 输出格式

一行，输出最多能吃到的萝卜数，后面输出吃萝卜的顺序。
## 样例

### 样例输入 #1
```
10
4 5
9 8
5 9
1 7
3 2
6 3
10 10
8 1
2 4
7 6

```
### 样例输出 #1
```
10 8 7 3 4 9 5 6 2 1 10
```
## 提示

- $40\%$ 的数据，$n\le100$；
- $100\%$ 的数据，$n\le1000$，$0\lt x_i\le10^4$，$0\lt y_i\le10^4$。


---

---
title: "魔法物品"
layout: "post"
diff: 提高+/省选-
pid: P1899
tag: ['动态规划 DP', '贪心', '递归', 'NOI 导刊']
---
# 魔法物品
## 题目描述


有两种类型的物品：普通物品和魔法物品。普通物品没有魔法属性，而魔法物品拥有一些魔法属性。每种普通物品有一个价值 $P$，但每种魔法物品有两种价值：鉴定前的价值 $P_1$ 和鉴定后的价值 $P_2$（当然，$P_2$ 总是大于 $P_1$）。

为了鉴定一个魔法物品，你需要购买一个鉴定卷轴，用它来鉴定魔法物品。鉴定完一件魔法物品以后，鉴定卷轴便会消失。每个鉴定卷轴将会消耗 $P_i$ 元钱。如果没有足够的钱，你将无法购买任何鉴定卷轴。    
现在，你正在一个集市中，同时拥有很多物品。你知道每件物品的价值并且想要出售全部物品。那么，你最多能够获得多少钱呢？

你可以假定：

- 开始的时候你没有钱。
- 所有的魔法物品都还没有被鉴定。
- 只要你有足够的钱，你可以购买任意多的鉴定卷轴。
## 输入格式

第一行有两个整数 $N$ 和 $P_i$（$1 \le P_i \le 5000$），表示你拥有的物品数和一个鉴定卷轴的价格。  
接下来 $N$ 行，每行给出一件物品的价格。  
对于每件普通物品行仅有一个整数 $P$（$1 \le P \le 10000$）。  
对于每件魔法物品,那一行将会有两个整数 $P_1$ 和 $P_2$（$1 \le P_1 < P_2 \le 10000$）。
## 输出格式

输出一个整数表示你最多能够获得多少钱。
## 样例

### 样例输入 #1
```
2 10
10
20 100

```
### 样例输出 #1
```
100

```
## 提示

对于 $30\%$ 的数据，$1\le N \le 50$。  
对于 $100\%$ 的数据，$1 \le N \le 1000$。


---

---
title: "Olympic"
layout: "post"
diff: 提高+/省选-
pid: P1946
tag: ['搜索', 'NOI 导刊']
---
# Olympic
## 题目描述

奥运会正在如火如荼的进行着，金牌榜上也有许多队伍需要排名。你需要选择三个整数 $P_g,P_s$ 和 $P_b$，分别表示每获得一块金、银、铜牌所对应得分。并且满足 $1000 \ge P_g \ge P_s \ge P_b \ge 1$。队伍将依据他们获得的分数进行排序（高分在前）。现在，为了使你所在的队伍排名尽可能的靠前，由你来选择 $P_g,P_s,P_b$。
## 输入格式

第一行一个整数 $n\ (1\le n\le 15)$，表示有 $n$ 支队伍进行排名。

以下 $n$ 行，每行三个整数 $G,S,B\ (0\le G,S,B\le 10^5)$，表示每只队伍获得的金、银、铜牌个数。


1. 第一支队伍即为你所在的队伍；
2. 分数相同时，你所在的队伍排名为最前。
## 输出格式

一行输出三个数 $P_g,P_s,P_b$，中间用空格隔开。

若有多组解，则输出 $P_g$ 最小的解，若仍有多组，则输出 $P_s$ 最小的解，若还有多组解，输出 $P_b$ 最小的解。
## 样例

### 样例输入 #1
```
3

1 1 1

0 1 2

2 1 0
```
### 样例输出 #1
```
1 1 1
```
## 提示

### 数据范围

- 对于 $10\%$ 的数据，保证最优解的 $P_g \le 10$；
- 对于 $30\%$ 的数据，保证最优解的 $P_g \le 100$。



---

---
title: "[USACO08JAN] Telephone Lines S"
layout: "post"
diff: 提高+/省选-
pid: P1948
tag: ['搜索', '图论', '2008', '二分', 'USACO', 'NOI 导刊', '广度优先搜索 BFS']
---
# [USACO08JAN] Telephone Lines S
## 题目描述

Farmer John wants to set up a telephone line at his farm. Unfortunately, the phone company is uncooperative, so he needs to pay for some of the cables required to connect his farm to the phone system.

There are N (1 ≤ N ≤ 1,000) forlorn telephone poles conveniently numbered 1..N that are scattered around Farmer John's property; no cables connect any them. A total of P (1 ≤ P ≤ 10,000) pairs of poles can be connected by a cable; the rest are too far apart.

The i-th cable can connect the two distinct poles Ai and Bi, with length Li (1 ≤ Li ≤ 1,000,000) units if used. The input data set never names any {Ai, Bi} pair more than once. Pole 1 is already connected to the phone system, and pole N is at the farm. Poles 1 and N need to be connected by a path of cables; the rest of the poles might be used or might not be used.

As it turns out, the phone company is willing to provide Farmer John with K (0 ≤ K < N) lengths of cable for free. Beyond that he will have to pay a price equal to the length of the longest remaining cable he requires (each pair of poles is connected with a separate cable), or 0 if he does not need any additional cables.

Determine the minimum amount that Farmer John must pay.

多年以后，笨笨长大了，成为了电话线布置师。由于地震使得某市的电话线全部损坏，笨笨是负责接到震中市的负责人。该市周围分布着 $1\le N\le1000$ 根据 $1\cdots N$ 顺序编号的废弃的电话线杆，任意两根线杆之间没有电话线连接，一共有 $1\le p\le10000$ 对电话杆可以拉电话线。其他的由于地震使得无法连接。

第i对电线杆的两个端点分别是 $a_i$ ，$b_i$，它们的距离为 $1\le l_i\le1000000$。数据中每对 $(a_i,b_i)$ 只出现一次。编号为 $1$ 的电话杆已经接入了全国的电话网络，整个市的电话线全都连到了编号 $N$ 的电话线杆上。也就是说，笨笨的任务仅仅是找一条将 $1$ 号和 $N$ 号电线杆连起来的路径，其余的电话杆并不一定要连入电话网络。

电信公司决定支援灾区免费为此市连接 $k$ 对由笨笨指定的电话线杆，对于此外的那些电话线，需要为它们付费，总费用决定于其中最长的电话线的长度（每根电话线仅连接一对电话线杆）。如果需要连接的电话线杆不超过 $k$ 对，那么支出为 $0$。

请你计算一下，将电话线引导震中市最少需要在电话线上花多少钱？

## 输入格式

输入文件的第一行包含三个数字 $n,p,k$。

第二行到第 $p+1$ 行，每行分别都为三个整数 $a_i,b_i,l_i$。

## 输出格式

一个整数，表示该项工程的最小支出，如果不可能完成则输出 `-1`。

## 样例

### 样例输入 #1
```
5 7 1
1 2 5
3 1 4
2 4 8
3 2 3
5 2 9
3 4 7
4 5 6

```
### 样例输出 #1
```
4

```


---

---
title: "[NOI2001] 聪明的打字员"
layout: "post"
diff: 提高+/省选-
pid: P1949
tag: ['搜索', '2001', 'NOI']
---
# [NOI2001] 聪明的打字员
## 题目描述

阿兰是某机密部门的打字员，她现在接到一个任务：需要在一天之内输入几百个长度固定为6的密码。当然，她希望输入的过程中敲击键盘的总次数越少越好。

不幸的是，出于保密的需要，该部门用于输入密码的键盘是特殊设计的，键盘上没有数字键，而只有以下六个键：`swap0`，`swap1`，`up`，`down`，`left`，`right`。为了说明这 $6$ 个键的作用，我们先定义录入区的 $6$ 个位置的编号，从左至右依次为 $1,2,3,4,5,6$。下面列出每个键的作用：

- `swap0`：按 `swap0`，光标位置不变，将光标所在的位置的数字与录入区的 $1$ 号位置的数字（左起第一个数字）交换。如果光标已经处在录入区的 $1$ 号位置，则按 `swap0` 键之后录入区的数字不变。

- `swap1`：按 `swap1`，光标位置不变，将光标所在位置的数字与录入区的 $6$ 号位置的数字（左起第六个数字）交换。如果光标已经处在录入区的 $6$ 号位置，则按 `swap1` 键之后录入区的数字不变。

- `up`：按 `up`，光标位置不变，讲光标所在位置的数字加 $1$（除非该数字是 $9$）。例如，如果光标所在位置的数字为 $2$，按 `up` 之后，该处的数字变为 $3$；如果光标所在位置的数字为 $9$，按 `up` 之后，该处的数字不变，光标位置也不变；

- `down`：按 `down`，光标位置不变，讲光标所在位置的数字减 $1$（除非该数字是 $0$）。如果光标所在位置的数字为 $0$，按 `down` 之后，该处的数字不变，光标位置也不变；

- `left`：按 `left`，光标左移一个位置，如果光标已在录入区的 $1$ 号位置（左起第一个位置）上，则光标不动；

- `right`：按 `right`，光标右移一个位置，如果光标已在录入区的 $6$ 号位置（左起第六个位置）上，则光标不动；

当然，为了使这样的键盘发挥作用，每次录入密码之前，录入区总会随机出现一个长度为 $6$ 的初始密码，而且光标会固定出现在 $1$ 号位置上。当巧妙的使用上述六个特殊键之后，可以得到目标密码，这时光标允许停留在任何一个位置。

现在，阿兰需要你的帮助，编写一个程序，求出录入一个密码需要的最少的击键次数。
## 输入格式

仅一行，含有两个长度为 $6$ 的数，前者为初始密码，后者为目标密码，两个密码之间用一个空格隔开。
## 输出格式

仅一行，含有一个正整数，为最少需要的击键次数。
## 样例

### 样例输入 #1
```
123456 654321
```
### 样例输出 #1
```
11
```


---

---
title: "长方形"
layout: "post"
diff: 提高+/省选-
pid: P1950
tag: ['动态规划 DP', 'NOI 导刊']
---
# 长方形
## 题目描述

小明今天突发奇想，想从一张用过的纸中剪出一个长方形。

为了简化问题，小明做出如下规定：

（1）这张纸的长宽分别为 $n,m$。小明将这张纸看成是由$n\times m$个格子组成，在剪的时候，只能沿着格子的边缘剪。

（2）这张纸有些地方小明以前在上面画过，剪出来的长方形不能含有以前画过的地方。

（3）剪出来的长方形的大小没有限制。

小明看着这张纸，想了好多种剪的方法，可是到底有几种呢？小明数不过来，你能帮帮他吗？

## 输入格式

第一行两个正整数 $n,m$，表示这张纸的长度和宽度。

接下来有 $n$ 行，每行 $m$ 个字符，每个字符为 `*` 或者 `.`。

字符 `*` 表示以前在这个格子上画过，字符 `.` 表示以前在这个格子上没画过。

## 输出格式

仅一个整数，表示方案数。

## 样例

### 样例输入 #1
```
6 4
....
.***
.*..
.***
...*
.***
```
### 样例输出 #1
```
38
```
## 提示

【数据规模】

对 $10\%$ 的数据，满足 $1\leq n\leq 10,1\leq m\leq 10$

对 $30\%$ 的数据，满足 $1\leq n\leq 50,1\leq m\leq 50$

对 $100\%$ 的数据，满足 $1\leq n\leq 1000,1\leq m\leq 1000$



---

---
title: "Sum"
layout: "post"
diff: 提高+/省选-
pid: P1956
tag: ['数学', 'NOI 导刊']
---
# Sum
## 题目描述

给出一个数列  $a_1,a_2,\cdots,a_n$ 和  $k,p$；

设  $S_{i,j}=\sum\limits_{k=i}^ja_k$，则：
 $$\mathit{Answer}=\min\{S_{i,j}\bmod p\ |\ S_{i,j}\bmod p\ge k\}$$
其中， $i\le j, \{S_{i,j}\bmod p\ |\ S_{i,j}\bmod p\ge k\}\ne\varnothing$。
## 输入格式

第一行三个正整数  $n,k,p$。

第二行  $n$ 个正整数，表示  $a_1,a_2,\cdots,a_n$。
## 输出格式

一行一个正整数，表示  $\mathit{Answer}$。
## 样例

### 样例输入 #1
```
7 2 17
12
13
15
11
16
26
11
```
### 样例输出 #1
```
2
```
## 提示

### 数据范围

对于 $100\%$ 的数据， $1\le n\le10^5$，$1\le k,p,a_i\le10^{18}$。


---

---
title: "最轻的天平"
layout: "post"
diff: 提高+/省选-
pid: P1961
tag: ['递归', 'NOI 导刊']
---
# 最轻的天平
## 题目描述

天平的两边有时不一定只能挂物品，还可以继续挂着另一个天平，现在给你一些天平的情况和它们之间的连接关系，要求使得所有天平都能平衡所需物品的总重量最轻，一个天平平衡当且仅当“左端点的重量\*左端点到支点的距离=右端点的重量\*右端点到支点的距离”。注意题目中的输入保证这些天平构成一个整体。

## 输入格式

第一行包含一个 $N(N \le 100)$，表示天平的数量，天平编号为 $l$ 到 $N$，接下来包含 $N$ 行描述天平的情况，每行 $4$ 个整数 $P,Q,R,B$，$P$ 和 $Q$ 表示横杆上支点到左边的长度与到右边的距离的比例为 $P:Q$，$R$ 表示左边悬挂的情况，如果 $R=0$ 说明悬挂的是物品，否则表示左边悬挂的是天平 $R:B$ 表示右边的悬挂情况，如果 $B=O$ 表示右边悬挂的是物品，否则右边悬挂着天平 $B$。

对于所有的输入，保证 $W\times L<2^{31}$，其中 $w$ 为最轻的天平重量，而 $L$ 为输入中描述左右比例时出现的最大值。
## 输出格式

输出一个整数表示使得所有天平都平衡所需最轻的物品总重量。

## 样例

### 样例输入 #1
```
4

3 2 0 4

1 3 0 0

4 4 2 1

2 2 0 0
```
### 样例输出 #1
```
40
```
## 提示

【样例说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/k8lsxvj9.png)


---

---
title: "[NOIP 2013 提高组] 火柴排队"
layout: "post"
diff: 提高+/省选-
pid: P1966
tag: ['2013', '树状数组', 'NOIP 提高组', '排序']
---
# [NOIP 2013 提高组] 火柴排队
## 题目背景

NOIP2013 提高组 D1T2
## 题目描述

涵涵有两盒火柴，每盒装有 $n$ 根火柴，每根火柴都有一个高度。 现在将每盒中的火柴各自排成一列， 同一列火柴的高度互不相同， 两列火柴之间的距离定义为：$ \sum (a_i-b_i)^2$。

其中 $a_i$ 表示第一列火柴中第 $i$ 个火柴的高度，$b_i$ 表示第二列火柴中第  $i$ 个火柴的高度。

每列火柴中相邻两根火柴的位置都可以交换，请你通过交换使得两列火柴之间的距离最小。请问得到这个最小的距离，最少需要交换多少次？如果这个数字太大，请输出这个最小交换次数对 $10^8-3$ 取模的结果。

## 输入格式

共三行，第一行包含一个整数 $n$，表示每盒中火柴的数目。

第二行有 $n$ 个整数，每两个整数之间用一个空格隔开，表示第一列火柴的高度。

第三行有 $n$ 个整数，每两个整数之间用一个空格隔开，表示第二列火柴的高度。

## 输出格式

一个整数，表示最少交换次数对 $10^8-3$ 取模的结果。

## 样例

### 样例输入 #1
```
4
2 3 1 4
3 2 1 4

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4
1 3 4 2
1 7 2 4
```
### 样例输出 #2
```
2
```
## 提示

**输入输出样例说明一**

最小距离是 $ 0$，最少需要交换 $1$ 次，比如：交换第 $1 $ 列的前 $ 2$ 根火柴或者交换第 $2$ 列的前 $2 $ 根火柴。

**输入输出样例说明二**

最小距离是 $10$，最少需要交换 $2$ 次，比如：交换第 $1$ 列的中间 $2$ 根火柴的位置，再交换第 $2$ 列中后 $2$ 根火柴的位置。

**数据范围**

对于 $10\%$ 的数据， $1 \leq n \leq 10$；

对于 $30\%$ 的数据，$1 \leq n \leq 100$；

对于 $60\%$ 的数据，$1 \leq n \leq 10^3$；

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq$ 火柴高度 $< 2^{31}$。


---

---
title: "[NOIP 2013 提高组] 货车运输"
layout: "post"
diff: 提高+/省选-
pid: P1967
tag: ['图论', '贪心', '2013', '倍增', '并查集', 'NOIP 提高组', '生成树', '最近公共祖先 LCA']
---
# [NOIP 2013 提高组] 货车运输
## 题目背景

NOIP2013 提高组 D1T3
## 题目描述

A 国有 $n$ 座城市，编号从 $1$ 到 $n$，城市之间有 $m$ 条双向道路。每一条道路对车辆都有重量限制，简称限重。  

现在有 $q$ 辆货车在运输货物， 司机们想知道每辆车在不超过车辆限重的情况下，最多能运多重的货物。

## 输入格式

第一行有两个用一个空格隔开的整数 $ n,m$，表示 A 国有 $ n$ 座城市和 $m$ 条道路。  

接下来 $m$ 行每行三个整数 $x, y, z$，每两个整数之间用一个空格隔开，表示从 $x $ 号城市到 $ y $ 号城市有一条限重为 $z$ 的道路。    
注意： $x \neq y$，两座城市之间可能有多条道路 。

接下来一行有一个整数 $q$，表示有 $q$ 辆货车需要运货。

接下来 $q$ 行，每行两个整数 $x,y$，之间用一个空格隔开，表示一辆货车需要从 $x$ 城市运输货物到 $y$ 城市，保证 $x \neq y$

## 输出格式

共有 $q$ 行，每行一个整数，表示对于每一辆货车，它的最大载重是多少。  
如果货车不能到达目的地，输出 $-1$。

## 样例

### 样例输入 #1
```
4 3
1 2 4
2 3 3
3 1 1
3
1 3
1 4
1 3
```
### 样例输出 #1
```
3
-1
3
```
## 提示

对于 $30\%$ 的数据，$1 \le n < 1000$，$1 \le m < 10,000$，$1\le q< 1000$；

对于 $60\%$ 的数据，$1 \le n < 1000$，$1 \le m < 5\times 10^4$，$1 \le q< 1000$；

对于 $100\%$ 的数据，$1 \le n < 10^4$，$1 \le m < 5\times 10^4$，$1 \le q< 3\times 10^4 $，$0 \le z \le 10^5$。



---

---
title: "[NOI2015] 软件包管理器"
layout: "post"
diff: 提高+/省选-
pid: P2146
tag: ['树形数据结构', '2015', '线段树', 'NOI', '深度优先搜索 DFS', '树链剖分']
---
# [NOI2015] 软件包管理器
## 题目背景

Linux 用户和 OSX 用户一定对软件包管理器不会陌生。通过软件包管理器，你可以通过一行命令安装某一个软件包，然后软件包管理器会帮助你从软件源下载软件包，同时自动解决所有的依赖（即下载安装这个软件包的安装所依赖的其它软件包），完成所有的配置。Debian/Ubuntu 使用的 apt-get，Fedora/CentOS 使用的 yum，以及 OSX 下可用的 homebrew 都是优秀的软件包管理器。  

## 题目描述

你决定设计你自己的软件包管理器。不可避免地，你要解决软件包之间的依赖问题。如果软件包 $a$ 依赖软件包 $b$，那么安装软件包 $a$ 以前，必须先安装软件包 $b$。同时，如果想要卸载软件包 $b$，则必须卸载软件包 $a$。

现在你已经获得了所有的软件包之间的依赖关系。而且，由于你之前的工作，除 $0$ 号软件包以外，在你的管理器当中的软件包都会依赖一个且仅一个软件包，而 $0$ 号软件包不依赖任何一个软件包。且依赖关系不存在环（即不会存在 $m$ 个软件包 $a_1,a_2, \dots , a_m$，对于 $i<m$，$a_i$ 依赖 $a_{i+1}$，而 $a_m$ 依赖 $a_1$ 的情况）。

现在你要为你的软件包管理器写一个依赖解决程序。根据反馈，用户希望在安装和卸载某个软件包时，快速地知道这个操作实际上会改变多少个软件包的安装状态（即安装操作会安装多少个未安装的软件包，或卸载操作会卸载多少个已安装的软件包），你的任务就是实现这个部分。

注意，安装一个已安装的软件包，或卸载一个未安装的软件包，都不会改变任何软件包的安装状态，即在此情况下，改变安装状态的软件包数为 $0$。

## 输入格式

第一行一个正整数 $n$，表示软件包个数，从 $0$ 开始编号。  
第二行有 $n-1$ 个整数，第 $i$ 个表示 $i$ 号软件包依赖的软件包编号。  
然后一行一个正整数 $q$，表示操作个数，格式如下：  

- `install x` 表示安装 $x$ 号软件包
- `uninstall x` 表示卸载 $x$ 号软件包

一开始所有软件包都是未安装的。  

对于每个操作，你需要输出这步操作会改变多少个软件包的安装状态，随后应用这个操作（即改变你维护的安装状态）。
## 输出格式

输出 $q$ 行，每行一个整数，表示每次询问的答案。
## 样例

### 样例输入 #1
```
7
0 0 0 1 1 5
5
install 5
install 6
uninstall 1
install 4
uninstall 0
```
### 样例输出 #1
```
3
1
3
2
3
```
### 样例输入 #2
```
10
0 1 2 1 3 0 0 3 2
10
install 0
install 3
uninstall 2
install 7
install 5
install 9
uninstall 9
install 4
install 1
install 9
```
### 样例输出 #2
```
1
3
2
1
3
1
1
1
0
1
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1504.png)  
一开始所有软件包都处于未安装状态。

安装 $5$ 号软件包，需要安装 $0,1,5$ 三个软件包。

之后安装 $6$ 号软件包，只需要安装 $6$ 号软件包。此时安装了 $0,1,5,6$ 四个软件包。

卸载 $1$ 号软件包需要卸载 $1,5,6$ 三个软件包。此时只有 $0$ 号软件包还处于安装状态。

之后安装 $4$ 号软件包，需要安装 $1,4$ 两个软件包。此时 $0,1,4$ 处在安装状态。最后，卸载 $0$ 号软件包会卸载所有的软件包。

【数据范围】  
![](https://cdn.luogu.com.cn/upload/pic/1505.png)


---

---
title: "[NOI2005] 瑰丽华尔兹"
layout: "post"
diff: 提高+/省选-
pid: P2254
tag: ['动态规划 DP', '2005', '单调队列', 'NOI', '队列']
---
# [NOI2005] 瑰丽华尔兹
## 题目背景

你跳过华尔兹吗？当音乐响起，当你随着旋律滑动舞步，是不是有一种漫步仙境的惬意？

众所周知，跳华尔兹时，最重要的是有好的音乐。但是很少有几个人知道，世界上最伟大的钢琴家一生都漂泊在大海上，他的名字叫丹尼・布德曼・T.D.・柠檬・1900，朋友们都叫他 1900。

1900 在 20 世纪的第一年出生在往返于欧美的邮轮弗吉尼亚号上。很不幸，他刚出生就被抛弃，成了孤儿。1900 孤独的成长在弗吉尼亚号上，从未离开过这个摇晃的世界。也许是对他命运的补偿，上帝派可爱的小天使艾米丽照顾他。可能是天使的点化，1900 拥有不可思议的钢琴天赋：从未有人教，从没看过乐谱，但他却能凭着自己的感觉弹出最沁人心脾的旋律。当 1900 的音乐获得邮轮上所有人的欢迎时，他才 8 岁，而此时，他已经乘着海轮往返欧美大陆 50 余次了。

虽说是钢琴奇才，但 1900 还是个孩子，他有着和一般男孩一样的好奇和调皮，只不过更多一层浪漫的色彩罢了：这是一个风雨交加的夜晚，海风卷起层层巨浪拍打着弗吉尼亚号，邮轮随着巨浪剧烈的摇摆。船上的新萨克斯手迈克斯・托尼晕船了，1900 招呼托尼和他一起坐到舞厅里的钢琴上，然后松开了固定钢琴的闸，于是，钢琴随着海轮的倾斜滑动起来。准确的说，我们的主角 1900…

## 题目描述

不妨认为舞厅是一个 $N$ 行 $M$ 列的矩阵，矩阵中的某些方格上堆放了一些家具，其他的则是空地。钢琴可以在空地上滑动，但不能撞上家具或滑出舞厅，否则会损坏钢琴和家具，引来难缠的船长。每个时刻，钢琴都会随着船体倾斜的方向向相邻的方格滑动一格，相邻的方格可以是向东、向西、向南或向北的。而艾米丽可以选择施魔法或不施魔法：如果不施魔法，则钢琴会滑动；如果施魔法，则钢琴会原地不动。

艾米丽是个天使，她知道每段时间的船体的倾斜情况。她想使钢琴在舞厅里滑行的路程尽量长，这样 1900 会非常高兴，同时也有利于治疗托尼的晕船。但艾米丽还太小，不会算，所以希望你能帮助她。

## 输入格式

输入文件的第一行包含 $5$ 个数 $N$, $M$, $x$, $y$ 和 $K$。$N$ 和 $M$ 描述舞厅的大小，$x$ 和 $y$ 为钢琴的初始位置；我们对船体倾斜情况是按时间的区间来描述的，且从 $1$ 开始计算时间，比如 “在 $[1, 3]$ 时间里向东倾斜，$[4, 5]$ 时间里向北倾斜”，因此这里的 $K$ 表示区间的数目。

以下 $N$ 行，每行 $M$ 个字符，描述舞厅里的家具。第 $i$ 行第 $j$ 列的字符若为 `.`，则表示该位置是空地；若为 `x`，则表示有家具。

以下 $K$ 行，顺序描述 $K$ 个时间区间，格式为：$s_i\ t_i\ d_i (1 \leq i \leq K)$。表示在时间区间 $[s_i, t_i]$ 内，船体都是向 $d_i$ 方向倾斜的。$d_i$ 为 $1$, $2$, $3$, $4$ 中的一个，依次表示北、南、西、东（分别对应矩阵中的上、下、左、右）。输入保证区间是连续的，即

$s_1 = 1$，$s_i = t_{i-1} + 1 (1 < i \leq K)$，$t_K = T$。
## 输出格式

输出文件仅有 $1$ 行，包含一个整数，表示钢琴滑行的最长距离 (即格子数)。

## 样例

### 样例输入 #1
```
4 5 4 1 3
..xx.
.....
...x.
.....
1 3 4
4 5 1
6 7 3
```
### 样例输出 #1
```
6
```
## 提示

钢琴的滑行路线：

 ![](https://cdn.luogu.com.cn/upload/pic/1307.png) 

钢琴在“×”位置上时天使使用一次魔法，因此滑动总长度为 $6$。

【数据范围】

$50\%$ 的数据中，$1\leq N, M\leq 200，T\leq 200$；

$100\%$ 的数据中，$1\leq N$, $M \leq 200$，$K \leq 200$，$T\leq 40000$。



---

---
title: "[NOIP 2014 普及组] 子矩阵"
layout: "post"
diff: 提高+/省选-
pid: P2258
tag: ['动态规划 DP', '搜索', '2014', 'NOIP 普及组', '枚举', '剪枝']
---
# [NOIP 2014 普及组] 子矩阵
## 题目背景

NOIP2014 普及组 T4
## 题目描述

给出如下定义：

1. 子矩阵：从一个矩阵当中选取某些行和某些列交叉位置所组成的新矩阵（保持行与列的相对顺序）被称为原矩阵的一个子矩阵。

    例如，下面图中选取第 $2,4$ 行和第 $2,4,5$ 列交叉位置的元素得到一个 $2 \times 3$ 的子矩阵如下所示。

|$9$|$\color{#6a5acd}3$|$3$|$\color{#6a5acd}3$|$\color{#6a5acd}9$|
|:-|:-|:-|:-|:-|
|$\color{#6a5acd}9$|$\color{blue}4$|$\color{#6a5acd}8$|$\color{blue}7$|$\color{blue}4$|
|$1$|$\color{#6a5acd}7$|$4$|$\color{#6a5acd}6$|$\color{#6a5acd}6$|
|$\color{#6a5acd}6$|$\color{blue}8$|$\color{#6a5acd}5$|$\color{blue}6$|$\color{blue}9$|
|$7$|$\color{#6a5acd}4$|$5$|$\color{#6a5acd}6$|$\color{#6a5acd}1$|

此矩阵的其中一个 $2\times3$ 的子矩阵是：

|$4$|$7$|$4$|
|:-|:-|:-|
|$8$|$6$|$9$|

2. 相邻的元素：矩阵中的某个元素与其上下左右四个元素（如果存在的话）是相邻的。

3. 矩阵的分值：矩阵中每一对相邻元素之差的绝对值之和。

本题任务：给定一个 $n$ 行 $m$ 列的正整数矩阵，请你从这个矩阵中选出一个 $r$ 行 $c$ 列的子矩阵，使得这个子矩阵的分值最小，并输出这个分值。
## 输入格式

第一行包含用空格隔开的四个整数 $n,m,r,c$，意义如问题描述中所述，每两个整数之间用一个空格隔开。

接下来的 $n$ 行，每行包含 $m$ 个用空格隔开的整数，用来表示问题描述中那个 $n$ 行 $m$ 列的矩阵。
## 输出格式

一个整数，表示满足题目描述的子矩阵的最小分值。

## 样例

### 样例输入 #1
```
5 5 2 3
9 3 3 3 9
9 4 8 7 4
1 7 4 6 6
6 8 5 6 9
7 4 5 6 1
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
7 7 3 3  
7 7 7 6 2 10 5
5 8 8 2 1 6 2 
2 9 5 5 6 1 7 
7 9 3 6 1 7 8 
1 9 1 4 7 8 8 
10 5 9 1 1 8 10
1 3 1 5 4 8 6
```
### 样例输出 #2
```
16
```
## 提示

#### 样例 1 说明

该矩阵中分值最小的 $2$ 行 $3$ 列的子矩阵由原矩阵的第 $4$ 行、第 $5$ 行与第 $1$ 列、第 $3$ 列、第 $4$ 列交叉位置的元素组成，为：

|$6$|$5$|$6$|
|:-|:-|:-|
|$7$|$5$|$6$|

其分值为 $|6-5|+|5-6|+|7-5|+|5-6|+|6-7|+|5-5|+|6-6|=6$。

#### 样例 2 说明

该矩阵中分值最小的 $3$ 行 $3$ 列的子矩阵由原矩阵的第 $4$ 行、第 $5$ 行、第 $6$ 行与第 $2$ 列、第 $6$ 列、第 $7$ 列交叉位置的元素组成，选取的分值最小的子矩阵为：

|$9$|$7$|$8$|
|:-|:-|:-|
|$9$|$8$|$8$|
|$5$|$8$|$10$|

#### 数据范围

- 对于 $50\%$ 的数据，$1\leq n\leq 12$，$1\leq m\leq 12$，矩阵中的每个元素 $1\leq a_{i,j}\leq20$；

- 对于 $100\%$ 的数据，$1\leq n\leq 16$，$1\leq m\leq 16$，矩阵中的每个元素 $1\leq a_{i,j}\leq 1000$，$1\leq r\leq n$，$1\leq c\leq m$。


---

---
title: "[NOIP 2014 提高组] 解方程"
layout: "post"
diff: 提高+/省选-
pid: P2312
tag: ['数学', '2014', 'NOIP 提高组', '枚举', '哈希 hashing', '素数判断,质数,筛法']
---
# [NOIP 2014 提高组] 解方程
## 题目背景

NOIP2014 提高组 D2T3
## 题目描述

已知多项式方程：

$$a_0+a_1x+a_2x^2+\cdots+a_nx^n=0$$ 

求这个方程在 $[1,m]$  内的整数解（$n$  和 $m$  均为正整数）。
## 输入格式

输入共 $n + 2$  行。  

第一行包含 $2$  个整数 $n, m$ ，每两个整数之间用一个空格隔开。  

接下来的 $n+1$  行每行包含一个整数，依次为 $a_0,a_1,a_2\ldots a_n$ 。
## 输出格式

第一行输出方程在 $[1,m]$  内的整数解的个数。  

接下来每行一个整数，按照从小到大的顺序依次输出方程在 $[1,m]$  内的一个整数解。
## 样例

### 样例输入 #1
```
2 10 
1
-2
1
```
### 样例输出 #1
```
1
1
```
### 样例输入 #2
```
2 10
2
-3
1
```
### 样例输出 #2
```
2
1
2
```
### 样例输入 #3
```
2 10
1
3
2
```
### 样例输出 #3
```
0
```
## 提示

对于 $30\%$  的数据：$0<n\le 2,|a_i|\le 100,a_n≠0,m<100$ 。  

对于 $50\%$  的数据：$0<n\le 100,|a_i|\le 10^{100},a_n≠0,m<100$ 。  

对于 $70\%$  的数据：$0<n\le 100,|a_i|\le 10^{10000},a_n≠0,m<10^4$ 。  

对于 $100\%$  的数据：$0<n\le 100,|a_i|\le 10^{10000},a_n≠0,m<10^6$ 。  


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
title: "[NOI2014] 动物园"
layout: "post"
diff: 提高+/省选-
pid: P2375
tag: ['字符串', '递推', '2014', 'NOI', 'KMP 算法']
---
# [NOI2014] 动物园
## 题目描述

近日，园长发现动物园中好吃懒做的动物越来越多了。例如企鹅，只会卖萌向游客要吃的。为了整治动物园的不良风气，让动物们凭自己的真才实学向游客要吃的，园长决定开设算法班，让动物们学习算法。

某天，园长给动物们讲解 KMP 算法。

园长：“对于一个字符串 $S$，它的长度为 $L$。我们可以在 $O(L)$ 的时间内，求出一个名为 $\mathrm{next}$ 的数组。有谁预习了 $\mathrm{next}$ 数组的含义吗？”

熊猫：“对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀又是它的前缀的字符串中（它本身除外），最长的长度记作 $\mathrm{next}[i]$。”

园长：“非常好！那你能举个例子吗？”

熊猫：“例 $S$ 为 $\verb!abcababc!$，则 $\mathrm{next}[5]=2$。因为$S$的前$5$个字符为 $\verb!abcab!$，$\verb!ab!$ 既是它的后缀又是它的前缀，并且找不到一个更长的字符串满足这个性质。同理，还可得出 $\mathrm{next}[1] = \mathrm{next}[2] = \mathrm{next}[3] = 0$，$\mathrm{next}[4] = \mathrm{next}[6] = 1$，$\mathrm{next}[7] = 2$，$\mathrm{next}[8] = 3$。”

园长表扬了认真预习的熊猫同学。随后，他详细讲解了如何在 $O(L)$ 的时间内求出 $\mathrm{next}$ 数组。

下课前，园长提出了一个问题：“KMP 算法只能求出 $\mathrm{next}$ 数组。我现在希望求出一个更强大 $\mathrm{num}$ 数组一一对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀同时又是它的前缀，并且该后缀与该前缀不重叠，将这种字符串的数量记作 $\mathrm{num}[i]$。例如 $S$ 为 $\verb!aaaaa!$，则 $\mathrm{num}[4] = 2$。这是因为$S$的前 $4$ 个字符为 $\verb!aaaa!$，其中 $\verb!a!$ 和 $\verb!aa!$ 都满足性质‘既是后缀又是前缀’，同时保证这个后缀与这个前缀不重叠。而 $\verb!aaa!$ 虽然满足性质‘既是后缀又是前缀’，但遗憾的是这个后缀与这个前缀重叠了，所以不能计算在内。同理，$\mathrm{num}[1] = 0,\mathrm{num}[2] = \mathrm{num}[3] = 1,\mathrm{num}[5] = 2$。”

最后，园长给出了奖励条件，第一个做对的同学奖励巧克力一盒。听了这句话，睡了一节课的企鹅立刻就醒过来了！但企鹅并不会做这道题，于是向参观动物园的你寻求帮助。你能否帮助企鹅写一个程序求出$\mathrm{num}$数组呢？

特别地，为了避免大量的输出，你不需要输出 $\mathrm{num}[i]$ 分别是多少，你只需要输出所有 $(\mathrm{num}[i]+1)$ 的乘积，对 $10^9 + 7$ 取模的结果即可。

## 输入格式

第 $1$ 行仅包含一个正整数 $n$，表示测试数据的组数。  
随后 $n$ 行，每行描述一组测试数据。每组测试数据仅含有一个字符串 $S$，$S$ 的定义详见题目描述。数据保证 $S$ 中仅含小写字母。输入文件中不会包含多余的空行，行末不会存在多余的空格。

## 输出格式

包含 $n$ 行，每行描述一组测试数据的答案，答案的顺序应与输入数据的顺序保持一致。对于每组测试数据，仅需要输出一个整数，表示这组测试数据的答案对 $10^9+7$ 取模的结果。输出文件中不应包含多余的空行。

## 样例

### 样例输入 #1
```
3
aaaaa
ab
abcababc
```
### 样例输出 #1
```
36
1
32 
```
## 提示

测试点编号| 约定
-|-  
1| $n \le 5, L \le 50$  
2| $n \le 5, L \le 200$  
3| $n \le 5, L \le 200$  
4| $n \le 5, L \le 10,000$  
5| $n \le 5, L \le 10,000$  
6| $n \le 5, L \le 100,000$  
7| $n \le 5, L \le 200,000$   
8| $n \le 5, L \le 500,000$  
9| $n \le 5, L \le 1,000,000$  
10| $n \le 5, L \le 1,000,000$  



---

---
title: "[NOI2002] 荒岛野人"
layout: "post"
diff: 提高+/省选-
pid: P2421
tag: ['2002', 'NOI']
---
# [NOI2002] 荒岛野人
## 题目描述

克里特岛以野人群居而著称。岛上有排列成环行的 $m$ 个山洞。这些山洞顺时针编号为 $1,2,\dots ,m$ 。岛上住着 $n$ 个野人，一开始依次住在山洞 $C_1,C_2,\dots ,C_n$中，以后每年，第 $i$ 个野人会沿顺时针向前走 $P_i$ 个洞住下来。

每个野人 $i$ 有一个寿命值 $L_i$，即生存的年数。

下面四幅图描述了一个有 $6$ 个山洞，住有三个野人的岛上前四年的情况。三个野人初始的洞穴编号依次为 $1,2,3$；每年要走过的洞穴数依次为 $3,7,2$；寿命值依次为 $4,3,1$。

![](https://cdn.luogu.com.cn/upload/pic/15476.png)

奇怪的是，虽然野人有很多，但没有任何两个野人在有生之年处在同一个山洞中，使得小岛一直保持和平与宁静，这让科学家们很是惊奇。他们想知道，至少有多少个山洞，才能维持岛上的和平呢？
## 输入格式

第 $1$ 行为一个整数 $n(1\leq n\leq 15)$，即野人的数目。

第 $2$ 行到第 $N+1$ 每行为三个整数 $C_i, P_i, L_i (1\leq C_i,P_i \leq 100, 0\leq L_i\leq 10^6 )$，表示每个野人所住的初始洞穴编号，每年走过的洞穴数及寿命值。
## 输出格式

仅包含一个数 $M$，即最少可能的山洞数。输入数据保证有解，且 $M$ 不大于 $10^6$。
## 样例

### 样例输入 #1
```
3
1 3 4
2 7 3
3 2 1
```
### 样例输出 #1
```
6
```
## 提示

$1\leq N\leq 15$，$1\leq C_i,P_i\leq 100$，$0\leq L_i\leq 10^6$  

保证 $M\leq 10^6$  





---

---
title: "[NOIP 2015 提高组] 斗地主"
layout: "post"
diff: 提高+/省选-
pid: P2668
tag: ['搜索', '贪心', '2015', 'NOIP 提高组', '深度优先搜索 DFS']
---
# [NOIP 2015 提高组] 斗地主
## 题目背景

NOIP2015 Day1T3
## 题目描述

牛牛最近迷上了一种叫斗地主的扑克游戏。斗地主是一种使用黑桃、红心、梅花、方片的 $A$ 到 $K$ 加上大小王的共 $54$ 张牌来进行的扑克牌游戏。在斗地主中，牌的大小关系根据牌的数码表示如下：$3<4<5<6<7<8<9<10<J<Q<K<A<2<\text{小王}<\text{大王}$，而花色并不对牌的大小产生影响。每一局游戏中，一副手牌由 $n$ 张牌组成。游戏者每次可以根据规定的牌型进行出牌，首先打光自己的手牌一方取得游戏的胜利。

现在，牛牛只想知道，对于自己的若干组手牌，分别最少需要多少次出牌可以将它们打光。请你帮他解决这个问题。

需要注意的是，本题中游戏者每次可以出手的牌型与一般的斗地主相似而略有不同。具体规则如下：

 ![](https://cdn.luogu.com.cn/upload/pic/1827.png) 

**本题数据随机，不支持hack，要hack或强力数据请点击[这里](https://www.luogu.org/problem/P2540)**。

## 输入格式

第一行包含用空格隔开的 $2$ 个正整数 $T,n$，表示手牌的组数以及每组手牌的张数。

接下来 $T$ 组数据，每组数据 $n$ 行，每行一个非负整数对 $a_i,b_i$，表示一张牌，其中 $a_i$ 表示牌的数码，$b_i$ 表示牌的花色，中间用空格隔开。特别的，我们用 $1$ 来表示数码 $A$，$11$ 表示数码 $J$，$12$ 表示数码 $Q$，$13$ 表示数码 $K$；黑桃、红心、梅花、方片分别用 $1-4$ 来表示；小王的表示方法为 `0 1`，大王的表示方法为 `0 2`。
## 输出格式

共 $T$ 行，每行一个整数，表示打光第 $i$ 组手牌的最少次数。
## 样例

### 样例输入 #1
```
1 8
7 4
8 4
9 1
10 4
11 1
5 1
1 4
1 1
```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
1 17
12 3
4 3
2 3
5 4
10 2
3 3
12 2
0 1
1 3
10 1
6 2
12 1
11 3
5 2
12 4
2 2
7 2

```
### 样例输出 #2
```
6

```
## 提示

**样例 1 说明**

共有 $1$ 组手牌，包含 $8$ 张牌：方片 $7$，方片 $8$，黑桃 $9$，方片 $10$，黑桃 $J$，黑桃 $5$，方片 $A$ 以及黑桃 $A$。可以通过打单顺子（方片 $7$，方片 $8$，黑桃 $9$，方片 $10$，黑桃 $J$），单张牌（黑桃 $5$）以及对子牌（黑桃 $A$以及方片 $A$）在 $3$ 次内打光。

对于不同的测试点， 我们约定手牌组数 $T$ 与张数 $n$ 的规模如下：

| 测试点编号 | $T=$ | $n=$ |
| :------: | :----: | :----: |
|  1       |  $100$   |  $2$  |
|  2       |  $100$   |  $2$  |
|  3       |  $100$   |  $3$  |
|  4       |  $100$   |  $3$  |
|  5       |  $100$   |  $4$  |
|  6       |  $100$   |  $4$  |
|  7       |  $100$   |  $10$  |
|  8       |  $100$   |  $11$  |
|  9       |  $100$   |  $12$  |
|  10       |  $100$   |  $13$  |
|  11       |  $100$   |  $14$  |
|  12       |  $100$   |  $15$  |
|  13       |  $10$   |  $16$  |
|  14       |  $10$   |  $17$  |
|  15       |  $10$   |  $18$  |
|  16       |  $10$   |  $19$  |
|  17       |  $10$   |  $20$  |
|  18       |  $10$   |  $21$  |
|  19       |  $10$   |  $22$  |
|  20       |  $10$   |  $23$  |

数据保证：所有的手牌都是随机生成的。



---

---
title: "[NOIP 2015 普及组] 推销员"
layout: "post"
diff: 提高+/省选-
pid: P2672
tag: ['贪心', '2015', '线段树', '树状数组', 'NOIP 普及组']
---
# [NOIP 2015 普及组] 推销员
## 题目背景

NOIP2015 普及组 T4
## 题目描述

阿明是一名推销员，他奉命到螺丝街推销他们公司的产品。螺丝街是一条死胡同，出口与入口是同一个，街道的一侧是围墙，另一侧是住户。螺丝街一共有 $N$ 家住户，第 $i$ 家住户到入口的距离为 $S_i$ 米。由于同一栋房子里可以有多家住户，所以可能有多家住户与入口的距离相等。阿明会从入口进入，依次向螺丝街的 $X$ 家住户推销产品，然后再原路走出去。

阿明每走 $1$ 米就会积累 $1$ 点疲劳值，向第 $i$ 家住户推销产品会积累 $A_i$ 点疲劳值。阿明是工作狂，他想知道，对于不同的 $X$，在不走多余的路的前提下，他最多可以积累多少点疲劳值。

## 输入格式

第一行有一个正整数 $N$，表示螺丝街住户的数量。

接下来的一行有 $N$ 个正整数，其中第 $i$ 个整数 $S_i$ 表示第 $i$ 家住户到入口的距离。数据保证 $S_1 \le S_2 \le \cdots \le S_n <10^8$。

接下来的一行有 $N$ 个正整数，其中第 $i$ 个整数 $A_i$ 表示向第 $i$ 户住户推销产品会积累的疲劳值。数据保证 $A_i<1000$。

## 输出格式

输出 $N$ 行，每行一个正整数，第 $i$ 行整数表示当 $X=i$ 时，阿明最多积累的疲劳值。

## 样例

### 样例输入 #1
```
5
1 2 3 4 5
1 2 3 4 5
```
### 样例输出 #1
```
15
19
22
24
25
```
### 样例输入 #2
```
5
1 2 2 4 5
5 4 3 4 1
```
### 样例输出 #2
```
12
17
21
24
27
```
## 提示

**输入输出样例 1 说明**

$X=1$：向住户 $5$ 推销，往返走路的疲劳值为 $5+5$，推销的疲劳值为 $5$，总疲劳值为 $15$。

$X=2$：向住户 $4,5$ 推销，往返走路的疲劳值为 $5+5$，推销的疲劳值为 $4+5$，总疲劳值为 $5+5+4+5=19$。

$X=3$：向住户 $3,4,5$ 推销，往返走路的疲劳值为 $5+5$，推销的疲劳值 $3+4+5$，总疲劳值为 $5+5+3+4+5=22$。

$X=4$：向住户 $2,3,4,5$ 推销，往返走路的疲劳值为 $5+5$，推销的疲劳值 $2+3+4+5$，总疲劳值 $5+5+2+3+4+5=24$。

$X=5$：向住户 $1,2,3,4,5$ 推销，往返走路的疲劳值为 $5+5$，推销的疲劳值 $1+2+3+4+5$，总疲劳值 $5+5+1+2+3+4+5=25$。


**输入输出样例 2 说明**

$X=1$：向住户 $4$ 推销，往返走路的疲劳值为 $4+4$，推销的疲劳值为 $4$，总疲劳值 $4+4+4=12$。

$X=2$：向住户 $1,4$ 推销，往返走路的疲劳值为 $4+4$，推销的疲劳值为 $5+4$，总疲劳值 $4+4+5+4=17$。

$X=3$：向住户 $1,2,4$ 推销，往返走路的疲劳值为 $4+4$，推销的疲劳值为 $5+4+4$，总疲劳值 $4+4+5+4+4=21$。

$X=4$：向住户 $1,2,3,4$ 推销，往返走路的疲劳值为 $4+4$，推销的疲劳值为 $5+4+3+4$，总疲劳值 $4+4+5+4+3+4=24$。或者向住户 $1,2,4,5$推销，往返走路的疲劳值为 $5+5$，推销的疲劳值为 $5+4+4+1$，总疲劳值 $5+5+5+4+4+1=24$。

$X=5$：向住户 $1,2,3,4,5$ 推销，往返走路的疲劳值为$5+5$，推销的疲劳值为 $5+4+3+4+1$，总疲劳值 $5+5+5+4+3+4+1=27$。

**数据范围**

对于 $20\%$ 的数据，$1 \le N \le20$；  
对于 $40\%$ 的数据，$1\le N \le 100$；  
对于 $60\%$ 的数据，$1 \le N \le 1000$；  
对于 $100\%$ 的数据，$1 \le N \le 100000$。



---

---
title: "[NOIP 2015 提高组] 运输计划"
layout: "post"
diff: 提高+/省选-
pid: P2680
tag: ['图论', '2015', '二分', 'NOIP 提高组', '最近公共祖先 LCA', '树链剖分']
---
# [NOIP 2015 提高组] 运输计划
## 题目背景

NOIP2015 Day2T3
## 题目描述

公元 $2044$ 年，人类进入了宇宙纪元。

L 国有 $n$ 个星球，还有 $n-1$ 条双向航道，每条航道建立在两个星球之间，这 $n-1$ 条航道连通了 L 国的所有星球。

小 P 掌管一家物流公司， 该公司有很多个运输计划，每个运输计划形如：有一艘物流飞船需要从 $u_i$ 号星球沿最快的宇航路径飞行到 $v_i$ 号星球去。显然，飞船驶过一条航道是需要时间的，对于航道 $j$，任意飞船驶过它所花费的时间为 $t_j$，并且任意两艘飞船之间不会产生任何干扰。

为了鼓励科技创新， L 国国王同意小 P 的物流公司参与 L 国的航道建设，即允许小 P 把某一条航道改造成虫洞，飞船驶过虫洞不消耗时间。

在虫洞的建设完成前小 P 的物流公司就预接了 $m$ 个运输计划。在虫洞建设完成后，这 $m$ 个运输计划会同时开始，所有飞船一起出发。当这 $m$ 个运输计划都完成时，小 P 的物流公司的阶段性工作就完成了。

如果小 P 可以自由选择将哪一条航道改造成虫洞， 试求出小 P 的物流公司完成阶段性工作所需要的最短时间是多少？
## 输入格式

第一行包括两个正整数 $n, m$，表示 L 国中星球的数量及小 P 公司预接的运输计划的数量，星球从 $1$ 到 $n$ 编号。

接下来 $n-1$ 行描述航道的建设情况，其中第 $i$ 行包含三个整数 $a_i, b_i$ 和 $t_i$，表示第 $i$ 条双向航道修建在 $a_i$ 与 $b_i$ 两个星球之间，任意飞船驶过它所花费的时间为 $t_i$。  

接下来 $m$ 行描述运输计划的情况，其中第 $j$ 行包含两个正整数 $u_j$ 和 $v_j$，表示第 $j$ 个运输计划是从 $u_j$ 号星球飞往 $v_j$号星球。
## 输出格式

一个整数，表示小 P 的物流公司完成阶段性工作所需要的最短时间。
## 样例

### 样例输入 #1
```
6 3 
1 2 3 
1 6 4 
3 1 7 
4 3 6 
3 5 5 
3 6 
2 5 
4 5
```
### 样例输出 #1
```
11
```
## 提示

所有测试数据的范围和特点如下表所示

 ![](https://cdn.luogu.com.cn/upload/pic/1831.png) 

**请注意常数因子带来的程序效率上的影响。**

对于 $100\%$ 的数据，保证：$1 \leq a_i,b_i \leq n$，$0 \leq t_i \leq 1000$，$1 \leq u_i,v_i \leq n$。



---

---
title: "[NOI2003] 木棒游戏"
layout: "post"
diff: 提高+/省选-
pid: P2702
tag: ['2003', 'NOI']
---
# [NOI2003] 木棒游戏
## 题目背景

这是一个很古老的游戏。用木棒在桌上拼出一个不成立的等式，移动且只移动一根木棒使得等式成立。现在轮到你了。

## 题目描述

你只能移动用来构成数字的木棒，不能移动构成运算符（+、-、=）的木棒，所以加号、减号、等号是不会改变的。移动前后，木棒构成的数字必须严格与图2中的0~9相符。如果移动一根木棒可以使等式成立，则输出新的等式，否则输出No。

## 输入格式

输入数据要符合逻辑。字符串的长度小于等于1000。

## 输出格式

如果有解，则输出正确的等式，格式与输入的格式相同（以“#”结尾，中间不能有分隔符，也不要加入多余字符）。此时输入数据保证解是唯一的。

如果无解，则输出“No”（N大写，o小写）。

## 样例

### 样例输入 #1
```
1+1=3#
```
### 样例输出 #1
```
1+1=2#
```
### 样例输入 #2
```
1+1=3+5#
```
### 样例输出 #2
```
No
```
### 样例输入 #3
```
11+77=34#
```
### 样例输出 #3
```
17+17=34#
```


---

---
title: "[NOI2001] 炮兵阵地"
layout: "post"
diff: 提高+/省选-
pid: P2704
tag: ['2001', 'NOI', '进制', '状压 DP']
---
# [NOI2001] 炮兵阵地
## 题目描述

司令部的将军们打算在 $N\times M$ 的网格地图上部署他们的炮兵部队。

一个 $N\times M$ 的地图由 $N$ 行 $M$ 列组成，地图的每一格可能是山地（用 $\texttt{H}$ 表示），也可能是平原（用 $\texttt{P}$ 表示），如下图。

在每一格平原地形上最多可以布置一支炮兵部队（山地上不能够部署炮兵部队）；一支炮兵部队在地图上的攻击范围如图中黑色区域所示：

 ![](https://cdn.luogu.com.cn/upload/pic/1881.png) 

如果在地图中的灰色所标识的平原上部署一支炮兵部队，则图中的黑色的网格表示它能够攻击到的区域：沿横向左右各两格，沿纵向上下各两格。

图上其它白色网格均攻击不到。从图上可见炮兵的攻击范围不受地形的影响。

现在，将军们规划如何部署炮兵部队，在防止误伤的前提下（保证任何两支炮兵部队之间不能互相攻击，即任何一支炮兵部队都不在其他支炮兵部队的攻击范围内），在整个地图区域内最多能够摆放多少我军的炮兵部队。


## 输入格式

第一行包含两个由空格分割开的正整数，分别表示 $N$ 和 $M$。

接下来的 $N$ 行，每一行含有连续的 $M$ 个字符，按顺序表示地图中每一行的数据。

## 输出格式

一行一个整数，表示最多能摆放的炮兵部队的数量。

## 样例

### 样例输入 #1
```
5 4
PHPP
PPHH
PPPP
PHPP
PHHP
```
### 样例输出 #1
```
6
```
## 提示

对于 $100\%$ 的数据，$1 \leq N\le 100$，$1 \leq M\le 10$，保证字符仅包含 `P` 与 `H`。


---

---
title: "[NOIP 2016 提高组] 蚯蚓"
layout: "post"
diff: 提高+/省选-
pid: P2827
tag: ['2016', '堆', 'NOIP 提高组', 'O2优化', '队列']
---
# [NOIP 2016 提高组] 蚯蚓
## 题目背景

NOIP2016 提高组 D2T2
## 题目描述

本题中，我们将用符号 $\lfloor c \rfloor$ 表示对 $c$ 向下取整，例如：$\lfloor 3.0 \rfloor = \lfloor 3.1 \rfloor = \lfloor 3.9 \rfloor = 3$。

蛐蛐国最近蚯蚓成灾了！隔壁跳蚤国的跳蚤也拿蚯蚓们没办法，蛐蛐国王只好去请神刀手来帮他们消灭蚯蚓。

蛐蛐国里现在共有 $n$ 只蚯蚓（$n$ 为正整数）。每只蚯蚓拥有长度，我们设第 $i$ 只蚯蚓的长度为 $a_i\,(i=1,2,\dots,n)$，并保证所有的长度都是非负整数（即：可能存在长度为 $0$ 的蚯蚓）。

每一秒，神刀手会在所有的蚯蚓中，准确地找到最长的那一只（如有多个则任选一个）将其切成两半。神刀手切开蚯蚓的位置由常数 $p$（是满足 $0 < p < 1$ 的有理数）决定，设这只蚯蚓长度为 $x$，神刀手会将其切成两只长度分别为 $\lfloor px \rfloor$ 和 $x - \lfloor px \rfloor$ 的蚯蚓。特殊地，如果这两个数的其中一个等于 $0$，则这个长度为 $0$ 的蚯蚓也会被保留。此外，除了刚刚产生的两只新蚯蚓，其余蚯蚓的长度都会增加 $q$（是一个非负整常数）。

蛐蛐国王知道这样不是长久之计，因为蚯蚓不仅会越来越多，还会越来越长。蛐蛐国王决定求助于一位有着洪荒之力的神秘人物，但是救兵还需要 $m$ 秒才能到来……（$m$ 为非负整数）

蛐蛐国王希望知道这 $m$ 秒内的战况。具体来说，他希望知道：

- $m$ 秒内，每一秒被切断的蚯蚓被切断前的长度（有 $m$ 个数）；
- $m$ 秒后，所有蚯蚓的长度（有 $n + m$ 个数）。

蛐蛐国王当然知道怎么做啦！但是他想考考你……
## 输入格式

第一行包含六个整数 $n,m,q,u,v,t$，其中：$n,m,q$ 的意义见【问题描述】；$u,v,t$ 均为正整数；你需要自己计算 $p=u / v$（保证 $0 < u < v$）；$t$ 是输出参数，其含义将会在【输出格式】中解释。

第二行包含 $n$ 个非负整数，为 $a_1, a_2, \dots, a_n$，即初始时 $n$ 只蚯蚓的长度。

同一行中相邻的两个数之间，恰好用一个空格隔开。

保证 $1 \leq n \leq 10^5$，$0 \leq m \leq 7 \times 10^6$，$0 < u < v \leq 10^9$，$0 \leq q \leq 200$，$1 \leq t \leq 71$，$0 \leq a_i \leq 10^8$。
## 输出格式

第一行输出 $\left \lfloor \frac{m}{t} \right \rfloor$ 个整数，按时间顺序，依次输出第 $t$ 秒，第 $2t$ 秒，第 $3t$ 秒，……被切断蚯蚓（在被切断前）的长度。

第二行输出 $\left \lfloor \frac{n+m}{t} \right \rfloor$ 个整数，输出 $m$ 秒后蚯蚓的长度；需要按从大到小的顺序，依次输出排名第 $t$，第 $2t$，第 $3t$，……的长度。

同一行中相邻的两个数之间，恰好用一个空格隔开。即使某一行没有任何数需要输出，你也应输出一个空行。

请阅读样例来更好地理解这个格式。
## 样例

### 样例输入 #1
```
3 7 1 1 3 1
3 3 2
```
### 样例输出 #1
```
3 4 4 4 5 5 6
6 6 6 5 5 4 4 3 2 2
```
### 样例输入 #2
```
3 7 1 1 3 2
3 3 2
```
### 样例输出 #2
```
4 4 5
6 5 4 3 2
```
### 样例输入 #3
```
3 7 1 1 3 9
3 3 2
```
### 样例输出 #3
```
//空行
2
```
## 提示

**样例解释 1**

在神刀手到来前：$3$ 只蚯蚓的长度为 $3,3,2$。

$1$ 秒后：一只长度为 $3$ 的蚯蚓被切成了两只长度分别为$1$ 和 $2$ 的蚯蚓，其余蚯蚓的长度增加了 $1$。最终 $4$ 只蚯蚓的长度分别为 $(1,2),4,3$。括号表示这个位置刚刚有一只蚯蚓被切断。

$2$ 秒后：一只长度为 $4$ 的蚯蚓被切成了 $1$ 和 $3$。$5$ 只蚯蚓的长度分别为：$2,3,(1,3),4$。

$3$ 秒后：一只长度为 $4$ 的蚯蚓被切断。$6$ 只蚯蚓的长度分别为：$3,4,2,4,(1,3)$。

$4$ 秒后：一只长度为 $4$ 的蚯蚓被切断。$7$ 只蚯蚓的长度分别为：$4,(1,3),3,5,2,4$。

$5$ 秒后：一只长度为 $5$ 的蚯蚓被切断。$8$ 只蚯蚓的长度分别为：$5,2,4,4,(1,4),3,5$。

$6$ 秒后：一只长度为 $5$ 的蚯蚓被切断。$9$ 只蚯蚓的长度分别为：$(1,4),3,5,5,2,5,4,6$。

$7$ 秒后：一只长度为 $6$ 的蚯蚓被切断。$10$ 只蚯蚓的长度分别为：$2,5,4,6,6,3,6,5,(2,4)$。所以，$7$ 秒内被切断的蚯蚓的长度依次为 $3,4,4,4,5,5,6$。$7$ 秒后，所有蚯蚓长度从大到小排序为 $6,6,6,5,5,4,4,3,2,2$。

**样例解释 2**

这个数据中只有 $t=2$ 与上个数据不同。只需在每行都改为每两个数输出一个数即可。

虽然第一行最后有一个 $6$ 没有被输出，但是第二行仍然要重新从第二个数再开始输出。

**样例解释 3**

这个数据中只有 $t=9$ 与上个数据不同。

注意第一行没有数要输出，但也要输出一个空行。


**数据范围**

![](https://cdn.luogu.com.cn/upload/pic/3458.png)



---

---
title: "[NOIP 2016 提高组] 愤怒的小鸟"
layout: "post"
diff: 提高+/省选-
pid: P2831
tag: ['搜索', '2016', 'NOIP 提高组', '状压 DP']
---
# [NOIP 2016 提高组] 愤怒的小鸟
## 题目背景

NOIP2016 提高组 D2T3
## 题目描述

Kiana 最近沉迷于一款神奇的游戏无法自拔。

简单来说，这款游戏是在一个平面上进行的。

有一架弹弓位于 $(0,0)$ 处，每次 Kiana 可以用它向第一象限发射一只红色的小鸟，小鸟们的飞行轨迹均为形如 $y=ax^2+bx$ 的曲线，其中 $a,b$ 是 Kiana 指定的参数，且必须满足 $a < 0$，$a,b$ 都是实数。

当小鸟落回地面（即 $x$ 轴）时，它就会瞬间消失。

在游戏的某个关卡里，平面的第一象限中有 $n$ 只绿色的小猪，其中第 $i$ 只小猪所在的坐标为 $\left(x_i,y_i \right)$。

如果某只小鸟的飞行轨迹经过了 $\left( x_i, y_i \right)$，那么第 $i$ 只小猪就会被消灭掉，同时小鸟将会沿着原先的轨迹继续飞行；

如果一只小鸟的飞行轨迹没有经过 $\left( x_i, y_i \right)$，那么这只小鸟飞行的全过程就不会对第 $i$ 只小猪产生任何影响。

例如，若两只小猪分别位于 $(1,3)$ 和 $(3,3)$，Kiana 可以选择发射一只飞行轨迹为 $y=-x^2+4x$ 的小鸟，这样两只小猪就会被这只小鸟一起消灭。

而这个游戏的目的，就是通过发射小鸟消灭所有的小猪。

这款神奇游戏的每个关卡对 Kiana 来说都很难，所以 Kiana 还输入了一些神秘的指令，使得自己能更轻松地完成这个游戏。这些指令将在【输入格式】中详述。

假设这款游戏一共有 $T$ 个关卡，现在 Kiana 想知道，对于每一个关卡，至少需要发射多少只小鸟才能消灭所有的小猪。由于她不会算，所以希望由你告诉她。
## 输入格式

第一行包含一个正整数 $T$，表示游戏的关卡总数。

下面依次输入这 $T$ 个关卡的信息。每个关卡第一行包含两个非负整数 $n,m$，分别表示该关卡中的小猪数量和 Kiana 输入的神秘指令类型。接下来的 $n$ 行中，第 $i$ 行包含两个正实数 $x_i,y_i$，表示第 $i$ 只小猪坐标为 $(x_i,y_i)$。数据保证同一个关卡中不存在两只坐标完全相同的小猪。

如果 $m=0$，表示 Kiana 输入了一个没有任何作用的指令。

如果 $m=1$，则这个关卡将会满足：至多用 $\lceil n/3 + 1 \rceil$ 只小鸟即可消灭所有小猪。

如果 $m=2$，则这个关卡将会满足：一定存在一种最优解，其中有一只小鸟消灭了至少 $\lfloor n/3 \rfloor$ 只小猪。

保证 $1\leq n \leq 18$，$0\leq m \leq 2$，$0 < x_i,y_i < 10$，输入中的实数均保留到小数点后两位。

上文中，符号 $\lceil c \rceil$ 和 $\lfloor c \rfloor$ 分别表示对 $c$ 向上取整和向下取整，例如：$\lceil 2.1 \rceil = \lceil 2.9 \rceil = \lceil 3.0 \rceil = \lfloor 3.0 \rfloor = \lfloor 3.1 \rfloor = \lfloor 3.9 \rfloor = 3$。
## 输出格式

对每个关卡依次输出一行答案。

输出的每一行包含一个正整数，表示相应的关卡中，消灭所有小猪最少需要的小鸟数量。
## 样例

### 样例输入 #1
```
2
2 0
1.00 3.00
3.00 3.00
5 2
1.00 5.00
2.00 8.00
3.00 9.00
4.00 8.00
5.00 5.00
```
### 样例输出 #1
```
1
1
```
### 样例输入 #2
```
3
2 0
1.41 2.00
1.73 3.00
3 0
1.11 1.41
2.34 1.79
2.98 1.49
5 0
2.72 2.72
2.72 3.14
3.14 2.72
3.14 3.14
5.00 5.00
```
### 样例输出 #2
```
2
2
3

```
### 样例输入 #3
```
1
10 0
7.16 6.28
2.02 0.38
8.33 7.78
7.68 2.09
7.46 7.86
5.77 7.44
8.24 6.72
4.42 5.11
5.42 7.79
8.15 4.99
```
### 样例输出 #3
```
6

```
## 提示

【样例解释1】

这组数据中一共有两个关卡。

第一个关卡与【问题描述】中的情形相同，$2$ 只小猪分别位于 $(1.00,3.00)$ 和 $(3.00,3.00)$，只需发射一只飞行轨迹为 $y = -x^2 + 4x$ 的小鸟即可消灭它们。

第二个关卡中有 $5$ 只小猪，但经过观察我们可以发现它们的坐标都在抛物线 $y = -x^2 + 6x$上，故 Kiana 只需要发射一只小鸟即可消灭所有小猪。

【数据范围】

| 测试点编号 |   $n\leqslant$ |   $m=$ |  $T\leqslant$ |
| :----------: | :----------: | :----------: | :----------: |
|   $1$ |   $2$ |   $0$ |  $10$ |
|   $2$ |   $2$ |   $0$ |  $30$ |
|   $3$ |   $3$ |   $0$ |  $10$ |
|   $4$ |   $3$ |   $0$ |  $30$ |
|   $5$ |   $4$ |   $0$ |  $10$ |
|   $6$ |   $4$ |   $0$ |  $30$ |
|   $7$ |   $5$ |   $0$ |  $10$ |
|   $8$ |   $6$ |   $0$ |  $10$ |
|   $9$ |   $7$ |   $0$ |  $10$ |
|   $10$ |   $8$ |   $0$ |  $10$ |
|   $11$ |   $9$ |   $0$ |  $30$ |
|   $12$ |   $10$ |   $0$ |  $30$ |
|   $13$ |   $12$ |   $1$ |  $30$ |
|   $14$ |   $12$ |   $2$ |  $30$ |
|   $15$ |   $15$ |   $0$ |  $15$ |
|   $16$ |   $15$ |   $1$ |  $15$ |
|   $17$ |   $15$ |   $2$ |  $15$ |
|   $18$ |   $18$ |   $0$ |  $5$ |
|   $19$ |   $18$ |   $1$ |  $5$ |
|   $20$ |   $18$ |   $2$ |  $5$ |


---

---
title: "[NOIP 2017 提高组] 逛公园"
layout: "post"
diff: 提高+/省选-
pid: P3953
tag: ['搜索', '2017', 'NOIP 提高组', '记忆化搜索', '最短路']
---
# [NOIP 2017 提高组] 逛公园
## 题目背景

NOIP2017 D1T3
## 题目描述

策策同学特别喜欢逛公园。公园可以看成一张 $N$ 个点 $M$ 条边构成的有向图，且没有 自环和重边。其中 $1$ 号点是公园的入口，$N$ 号点是公园的出口，每条边有一个非负权值， 代表策策经过这条边所要花的时间。

策策每天都会去逛公园，他总是从 $1$ 号点进去，从 $N$ 号点出来。

策策喜欢新鲜的事物，它不希望有两天逛公园的路线完全一样，同时策策还是一个 特别热爱学习的好孩子，它不希望每天在逛公园这件事上花费太多的时间。如果 $1$ 号点 到 $N$ 号点的最短路长为 $d$，那么策策只会喜欢长度不超过 $d + K$ 的路线。

策策同学想知道总共有多少条满足条件的路线，你能帮帮它吗？

为避免输出过大，答案对 $P$ 取模。

如果有无穷多条合法的路线，请输出 $-1$。

## 输入格式

第一行包含一个整数 $T$, 代表数据组数。

接下来 $T$ 组数据，对于每组数据： 第一行包含四个整数 $N,M,K,P$，每两个整数之间用一个空格隔开。


接下来 $M$ 行，每行三个整数 $a_i,b_i,c_i$，代表编号为 $a_i,b_i$ 的点之间有一条权值为 $c_i$ 的有向边，每两个整数之间用一个空格隔开。

## 输出格式

输出文件包含 $T$ 行，每行一个整数代表答案。

## 样例

### 样例输入 #1
```
2
5 7 2 10
1 2 1
2 4 0
4 5 2
2 3 2
3 4 1
3 5 2
1 5 3
2 2 0 10
1 2 0
2 1 0
```
### 样例输出 #1
```
3
-1


```
## 提示

【样例解释1】


对于第一组数据，最短路为 $3$。 $1\to 5, 1\to 2\to 4\to 5, 1\to 2\to 3\to 5$ 为 $3$ 条合法路径。


【测试数据与约定】

对于不同的测试点，我们约定各种参数的规模不会超过如下


测试点编号　　|$T$　　　|$N$　　　|$M$　　　|$K$　　　|是否有 $0$ 边
-|-|-|-|-|-
$1$|$5$|$5$|$10$|$0$|否
$2$|$5$|$10^3$|$2\times 10^3$|$0$|否
$3$|$5$|$10^3$|$2\times 10^3$|$50$|否
$4$|$5$|$10^3$|$2\times 10^3$|$50$|否
$5$|$5$|$10^3$|$2\times 10^3$|$50$|否
$6$|$5$|$10^3$|$2\times 10^3$|$50$|是
$7$|$5$|$10^5$|$2\times 10^5$|$0$|否
$8$|$3$|$10^5$|$2\times 10^5$|$50$|否
$9$|$3$|$10^5$|$2\times 10^5$|$50$|是
$10$|$3$|$10^5$|$2\times 10^5$|$50$|是


对于 $100\%$ 的数据，$1 \le P \le 10^9$，$1 \le a_i,b_i \le N$，$0 \le c_i \le 1000$。

数据保证：至少存在一条合法的路线。

---

- 2019.8.30 增加了一组 hack 数据 by @skicean
- 2022.7.21 增加了一组 hack 数据 by @djwj233


---

---
title: "[NOIP 2017 普及组] 跳房子"
layout: "post"
diff: 提高+/省选-
pid: P3957
tag: ['动态规划 DP', '2017', '二分', '单调队列', 'NOIP 普及组', '队列']
---
# [NOIP 2017 普及组] 跳房子
## 题目背景

NOIP2017 普及组 T4
## 题目描述

跳房子，也叫跳飞机，是一种世界性的儿童游戏，也是中国民间传统的体育游戏之一。

跳房子的游戏规则如下：

在地面上确定一个起点，然后在起点右侧画 $n$ 个格子，这些格子都在同一条直线上。每个格子内有一个数字（整数），表示到达这个 格子能得到的分数。玩家第一次从起点开始向右跳，跳到起点右侧的一个格子内。第二次再从当前位置继续向右跳，依此类推。规则规定：

玩家每次都必须跳到当前位置右侧的一个格子内。玩家可以在任意时刻结束游戏，获得的分数为曾经到达过的格子中的数字之和。

现在小 R 研发了一款弹跳机器人来参加这个游戏。但是这个机器人有一个非常严重的缺陷，它每次向右弹跳的距离只能为固定的 $d$。小 R 希望改进他的机器人，如果他花 $g$ 个金币改进他的机器人，那么他的机器人灵活性就能增加 $g$，但是需要注意的是，每 次弹跳的距离至少为 $1$。具体而言，当 $g<d$ 时，他的机器人每次可以选择向右弹跳的距离为 $d-g,d-g+1,d-g+2,\ldots,d+g-1,d+g$；否则当 $g \geq d$ 时，他的机器人每次可以选择向右弹跳的距离为 $1,2,3,\ldots,d+g-1,d+g$。

现在小 R 希望获得至少 $k$ 分，请问他至少要花多少金币来改造他的机器人。
## 输入格式

第一行三个正整数 $n,d,k$，分别表示格子的数目，改进前机器人弹跳的固定距离，以及希望至少获得的分数。相邻两个数 之间用一个空格隔开。

接下来 $n$ 行，每行两个整数 $x_i,s_i$，分别表示起点到第 $i$ 个格子的距离以及第 $i$ 个格子的分数。两个数之间用一个空格隔开。保证 $x_i$ 按递增顺序输入。
## 输出格式

共一行，一个整数，表示至少要花多少金币来改造他的机器人。若无论如何他都无法获得至少 $k$ 分，输出 $-1$。
## 样例

### 样例输入 #1
```
7 4 10
2 6
5 -3
10 3
11 -3
13 1
17 6
20 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
7 4 20
2 6
5 -3
10 3
11 -3
13 1
17 6
20 2
```
### 样例输出 #2
```
-1
```
## 提示

**样例 1 说明**

花费 $2$ 个金币改进后，小 R 的机器人依次选择的向右弹跳的距离分别为 $ 2, 3, 5, 3, 4,3$，先后到达的位置分别为 $2, 5, 10, 13, 17, 20$，对应 $ 1, 2, 3, 5, 6, 7$ 这 $6$ 个格子。这些格子中的数字之和 $ 15$ 即为小 R 获得的分数。

**样例 2 说明**

由于样例中 $7$ 个格子组合的最大可能数字之和只有 $18$，所以无论如何都无法获得 $20$ 分。

**数据规模与约定**

本题共 10 组测试数据，每组数据等分。

对于全部的数据满足 $1 \le n \le 5\times10^5$，$1 \le d \le2\times10^3$，$1 \le x_i, k \le 10^9$，$|s_i| < 10^5$。

对于第 $1, 2$ 组测试数据，保证 $n\le 10$。

对于第 $3, 4, 5$ 组测试数据，保证 $n \le 500$。

对于第 $6, 7, 8$ 组测试数据，保证 $d = 1$。


---

---
title: "[NOI2008] 设计路线"
layout: "post"
diff: 提高+/省选-
pid: P4201
tag: ['2008', 'NOI']
---
# [NOI2008] 设计路线
## 题目描述

Z 国坐落于遥远而又神奇的东方半岛上，在小 Z 的统治时代公路成为这里主要的交通手段。Z 国共有 $N$ 座城市，一些城市之间由双向的公路所连接。非常神奇的是 Z 国的每个城市所处的经度都不相同，并且最多只和一个位于它东边的城市直接通过公路相连。Z 国的首都是 Z 国政治经济文化旅游的中心，每天都有成千上万的人从 Z 国的其他城市涌向首都。

为了使 Z 国的交通更加便利顺畅，小 Z 决定在 Z 国的公路系统中确定若干条规划路线，将其中的公路全部改建为铁路。

我们定义每条规划路线为一个长度大于 $1$ 的城市序列，每个城市在该序列中最多出现一次，序列中相邻的城市之间由公路直接相连（待改建为铁路）。并且，每个城市最多只能出现在一条规划路线中，也就是说，任意两条规划路线不能有公共部分。

当然在一般情况下是不可能将所有的公路修建为铁路的，因此从有些城市出发去往首都依然需要通过乘坐长途汽车，而长途汽车只往返于公路连接的相邻的城市之间，因此从某个城市出发可能需要不断地换乘长途汽车和火车才能到达首都。

我们定义一个城市的“不便利值”为从它出发到首都需要乘坐的长途汽车的次数，而 Z 国的交通系统的“不便利值”为所有城市的不便利值的最大值，很明显首都的“不便利值”为 $0$。小 Z 想知道如何确定规划路线修建铁路使得 Z 国的交通系统的“不便利值”最小，以及有多少种不同的规划路线的选择方案使得“不便利值”达到最小。当然方案总数可能非常大，小 Z 只关心这个天文数字 $\bmod\ Q$ 后的值。

注意：规划路线 $1-2-3$ 和规划路线 $3-2-1$ 是等价的，即将一条规划路线翻转，依然认为是等价的。两个方案不同当且仅当其中一个方案中存在一条规划路线不属于另一个方案。


## 输入格式

第一行包含三个正整数 $N,M,Q$，其中 $N$ 表示城市个数， $M$ 表示公路总数，$N$ 个城市从 $1 \sim N$ 编号，其中编号为 $1$ 的是首都。$Q$ 表示上文提到的设计路线的方法总数的模数。

接下来 $M$ 行，每行两个不同的整数 $a_i,b_i(1 \le a_i,b_i \le N)$，表示有一条公路连接城市 $a_i$ 和城市 $b_i$。

输入数据保证一条公路只出现一次。
## 输出格式

应包含两行。

第 $1$ 行为一个整数，表示最小的“不便利值”。

第 $2$ 行为一个整数，表示使“不便利值”达到最小时不同的设计路线的方法总数 $\bmod\ Q$ 的值。

如果某个城市无法到达首都，则输出两行 $-1$。
## 样例

### 样例输入 #1
```
5 4 100 
1 2 
4 5 
1 3 
4 1
```
### 样例输出 #1
```
1 
10
```
## 提示

对于 $20 \%$ 的数据，$1 \le N,M \le 10$。

对于 $50 \%$ 的数据，$1 \le N,M \le 200$。

对于 $60 \%$ 的数据，$1 \le N,M \le 5000$。

对于 $100 \%$ 的数据，$1 \le N,M \le 10 ^ 5$，$1 \le Q \le 1.2 \times 10 ^ 8$。


---

---
title: "[NOI2005] 聪聪与可可"
layout: "post"
diff: 提高+/省选-
pid: P4206
tag: ['搜索', '2005', 'NOI', '广度优先搜索 BFS', '深度优先搜索 DFS', '记忆化搜索', '期望']
---
# [NOI2005] 聪聪与可可
## 题目描述

在一个魔法森林里，住着一只聪明的小猫聪聪和一只可爱的小老鼠可可。虽然灰姑娘非常喜欢她们俩，但是，聪聪终究是一只猫，而可可终究是一只老鼠，同样不变的是，聪聪成天想着要吃掉可可。

一天，聪聪意外得到了一台非常有用的机器，据说是叫 GPS，对可可能准确的定位。有了这台机器，聪聪要吃可可就易如反掌了。于是，聪聪准备马上出发，去找可可。而可怜的可可还不知道大难即将临头，仍在森林里无忧无虑的玩耍。小兔子乖乖听到这件事，马上向灰姑娘报告。灰姑娘决定尽快阻止聪聪，拯救可可，可她不知道还有没有足够的时间。

整个森林可以认为是一个无向图，图中有 $N$ 个美丽的景点，景点从 $1$ 至 $N$ 编号。小动物们都只在景点休息、玩耍。在景点之间有一些路连接。

当聪聪得到 GPS 时，可可正在景点 $M$（$M \le N$）处。以后的每个时间单位，可可都会选择去相邻的景点（可能有多个）中的一个或停留在原景点不动。而去这些地方所发生的概率是相等的。假设有 $P$ 个景点与景点 $M$ 相邻，它们分别是景点 $R$、景点 $S$、……、景点 $Q$，在时刻 $T$ 可可处在景点 $M$，则在 $(T+1)$ 时刻，可可有 $1/(1 +P)$ 的可能在景点 $R$，有 $1/(1 +P)$ 的可能在景点 $S$，……，有 $1/(1 +P)$ 的可能在景点 $Q$，还有$1/(1 +P)$的可能停在景点 $M$。

我们知道，聪聪是很聪明的，所以，当她在景点 $C$ 时，她会选一个更靠近可可的景点，如果这样的景点有多个，她会选一个标号最小的景点。由于聪聪太想吃掉可可了，如果走完第一步以后仍然没吃到可可，她还可以在本段时间内再向可可走近一步。

在每个时间单位，假设聪聪先走，可可后走。在某一时刻，若聪聪和可可位于同一个景点，则可怜的可可就被吃掉了。

灰姑娘想知道，平均情况下，聪聪几步就可能吃到可可。而你需要帮助灰姑娘尽快的找到答案。
## 输入格式

数据的第 1 行为两个整数 $N$ 和 $E$，以空格分隔，分别表示森林中的景点数和连接相邻景点的路的条数。

第 2 行包含两个整数 $C$ 和 $M$，以空格分隔，分别表示初始时聪聪和可可所在的景点的编号。

接下来 E 行，每行两个整数，第 $i+2$ 行的两个整数 $A_i$ 和 $B_i$ 表示景点 $A_i$ 和景点 $B_i$ 之间有一条路。所有的路都是无向的，即：如果能从 A 走到 B，就可以从 B 走到 A。

输入保证任何两个景点之间不会有多于一条路直接相连，且聪聪和可可之间必有路直接或间接的相连。
## 输出格式

输出 1 个实数，四舍五入保留三位小数，表示平均多少个时间单位后聪聪会把可可吃掉。
## 样例

### 样例输入 #1
```
4 3 
1 4 
1 2 
2 3 
3 4
```
### 样例输出 #1
```
1.500 

```
### 样例输入 #2
```
9 9 
9 3 
1 2 
2 3 
3 4 
4 5 
3 6 
4 6 
4 7 
7 8 
8 9
```
### 样例输出 #2
```
2.167
```
## 提示

【样例说明 1】 

开始时，聪聪和可可分别在景点 1 和景点 4。 

第一个时刻，聪聪先走，她向更靠近可可(景点 4)的景点走动，走到景点 2， 然后走到景点 3；假定忽略走路所花时间。 

可可后走，有两种可能： 第一种是走到景点 3，这样聪聪和可可到达同一个景点，可可被吃掉，步数为 $1$，概率为$0.5$。
 
第二种是停在景点 4，不被吃掉。概率为 $0.5$。

到第二个时刻，聪聪向更靠近可可(景点 4)的景点走动，只需要走一步即和 可可在同一景点。因此这种情况下聪聪会在两步吃掉可可。 所以平均的步数是 $1\times 1/2 + 2\times 1/2 =1.5$ 步。

【样例说明 2】

森林如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8uiq0ltc.png)

对于 50%的数据，$1≤N≤50$。  
对于所有的数据，$1≤N,E≤1000$。 


---

---
title: "[NOI2004] 降雨量"
layout: "post"
diff: 提高+/省选-
pid: P4273
tag: ['计算几何', '2004', 'NOI']
---
# [NOI2004] 降雨量
## 题目描述

M 国是个多雨的国家，尤其是 P 城，频繁的降雨给人们的出行带来了不少麻烦。为了方便行人雨天过马路，有关部门在每处人行横道的上空都安装了一种名为“自动伞”的装置。（如图 $1$ 所示）
![](https://cdn.luogu.com.cn/upload/image_hosting/109hsm74.png)
每把自动伞都可以近似地看作一块长方形的板，厚度不计。这种伞有相当出色的吸水能力，落到上面的雨水都会完全被伞顶的小孔吸入，并通过管道运走。不下雨时，这些伞闲置着。一旦下雨，它们便立刻开始作匀速率直线往返运动：从马路的一边以固定的速率移动到另一边，再从另一边以相同的速率返回，如此往复，直到雨停为止。任何时刻自动伞都不会越过马路的边界。有了自动伞，下雨天没带伞的行人只要躲在伞下行走，就不会被雨淋着了。

由于自动伞的大小有限，当需要使用自动伞过马路的人比较多时，一把自动伞显然是不够的，所以有关部门在几处主要的人行横道上空安装了多把自动伞。每把自动伞的宽度都等于人行横道的宽度，高度各不相同，长度不一定相同，移动速率也不一定相同。

现在已知一处人行横道的详细情况，请你计算从开始下雨到 $T$ 秒钟后的这段时间内，一共有多少体积的雨水降落到人行横道上。
## 输入格式

第一行有四个整数 $N$，$W$，$T$，$V$。$N$ 表示自动伞的数目，$W$ 表示马路的宽度，$T$ 表示需要统计从开始下雨到多长时间后的降雨情况，$V$ 表示单位面积单位时间内的降雨体积。

为了描述方便，我们画出了一个如图 $2$ 所示的天空中五把伞的剖面图，取马路左边界为原点，取向右为 $x$ 轴正方向，取向上为 $y$ 轴正方向，建立平面直角坐标系。这样，每把自动伞都可以看作平面上的一条线段。

![](https://cdn.luogu.com.cn/upload/image_hosting/5z9mrtlz.png)

接下来的 $N$ 行，每行用三个整数描述一把自动伞。第一个数 $x$ 是伞的初始位置，用它左端点的横坐标表示。第二个数 $l$ 是伞的长度，即 $x$ 方向上的尺寸。第三个数 $v$ 是伞的速度，$v$ 的大小表示移动的速率。如果 $v > 0$，表示开始时伞向右移动；如果 $v < 0$，表示开始时伞向左移动；如果 $v = 0$，表示伞不动。
## 输出格式

输出文件只包含一个实数，表示从开始下雨到 $T$ 秒钟后，一共有多少体积的
水降落到人行横道上。输出结果精确到小数点后第二位。
## 样例

### 样例输入 #1
```
2 4 3 10
0 1 1
3 1 -1
```
### 样例输出 #1
```
65.00
```
## 提示

【约定】

○ 雨点均匀地匀速竖直下落

○ 自动伞和马路两者都是水平的

○ 自动伞的宽度和人行横道的宽度相等，都等于 $1$

○ $N \leq 10$

○ $W \leq 100$

○ $T \leq 100$

○ $V \leq 50$

○ 所有自动伞的往返次数之和不超过 $250$，一来一回算一个往返。



---

---
title: "[NOI2002] 贪吃的九头龙"
layout: "post"
diff: 提高+/省选-
pid: P4362
tag: ['动态规划 DP', '2002', 'NOI', '树形 DP']
---
# [NOI2002] 贪吃的九头龙
## 题目背景

传说中的九头龙是一种特别贪吃的动物。虽然名字叫“九头龙”，但这只是 说它出生的时候有九个头，而在成长的过程中，它有时会长出很多的新头，头的 总数会远大于九，当然也会有旧头因衰老而自己脱落。 
## 题目描述

有一天，有 $M$ 个脑袋的九头龙看到一棵长有 $N$ 个果子的果树，喜出望外，恨不得一口把它全部吃掉。可是必须照顾到每个头，因此它需要把 $N$ 个果子分成 $M$ 组，每组至少有一个果子，让每个头吃一组。

这 $M$ 个脑袋中有一个最大，称为“大头”，是众头之首，它要吃掉恰好 $K$ 个果子，而且 $K$ 个果子中理所当然地应该包括唯一的一个最大的果子。果子由 $N-1$ 根树枝连接起来，由于果树是一个整体，因此可以从任意一个果子出发沿着树枝“走到”任何一个其他的果子。

对于每段树枝，如果它所连接的两个果子需要由不同的头来吃掉，那么两个头会共同把树枝弄断而把果子分开；如果这两个果子是由同一个头来吃掉，那么这个头会懒得把它弄断而直接把果子连同树枝一起吃掉。当然，吃树枝并不是很舒服的，因此每段树枝都有一个吃下去的“难受值”，而九头龙的难受值就是所有头吃掉的树枝的“难受值”之和。

九头龙希望它的“难受值”尽量小，你能帮它算算吗？

例如图 $1$ 所示的例子中，果树包含 $8$ 个果子，$7$ 段树枝，各段树枝的“难受值”标记在了树枝的旁边。九头龙有两个脑袋，大头需要吃掉 $4$ 个果子，其中必须包含最大的果子。即 $N=8$，$M=2$，$K=4$：

![](https://cdn.luogu.com.cn/upload/pic/16595.png )

图一描述了果树的形态，图二描述了最优策略。 
## 输入格式

输入的第 $1$ 行包含三个整数 $N\ (1 \le N \le 300)$，$M(2 \le M \le N)$，$K(1 \le K \le N)$。$N$ 个果子依次编号 $1,2, \cdots N$，且最大的果子的编号总是 $1$。

第 $2$ 行到第 $N$ 行描述了果树的形态，每行包含三个整数 $a\ (1 \le a \le N), b\ (1 \le b \le N), c\ (0 \le c \le 10^5)$，表示存在一段难受值为 $c$ 的树枝连接果子 $a$ 和果子 $b$。
## 输出格式

输出仅有一行，包含一个整数，表示在满足“大头”的要求 的前提下，九头龙的难受值的最小值。如果无法满足要求，输出 $-1$。

## 样例

### 样例输入 #1
```
8 2 4 
1 2 20 
1 3 4 
1 4 13 
2 5 10 
2 6 12 
3 7 15 
3 8 5 
```
### 样例输出 #1
```
4
```
## 提示

该样例对应于题目描述中的例子。 


---

---
title: "[NOI2003] 逃学的小孩"
layout: "post"
diff: 提高+/省选-
pid: P4408
tag: ['2003', 'NOI', '枚举', '树的直径']
---
# [NOI2003] 逃学的小孩
## 题目描述

Chris 家的电话铃响起了，里面传出了 Chris 的老师焦急的声音：“喂，是 Chris 的家长吗？你们的孩子又没来上课，不想参加考试了吗？”一听说要考试，Chris 的父母就心急如焚，他们决定在尽量短的时间内找到 Chris。他们告诉 Chris 的老师：“根据以往的经验，Chris 现在必然躲在朋友 Shermie 或 Yashiro 家里偷玩《拳皇》游戏。现在，我们就从家出发去找 Chris，一旦找到，我们立刻给您打电话。”说完砰的一声把电话挂了。

Chris 居住的城市由 $N$ 个居住点和若干条连接居住点的双向街道组成，经过街道 $x$ 需花费 $T_{x}$ 分钟。可以保证，任意两个居住点间有且仅有一条通路。Chris 家在点 $C$，Shermie 和 Yashiro 分别住在点 $A$ 和点 $B$。Chris 的老师和 Chris 的父母都有城市地图，但 Chris 的父母知道点 $A$、$B$、$C$ 的具体位置而 Chris 的老师不知。

为了尽快找到 Chris，Chris 的父母会遵守以下两条规则：

1. 如果 $A$ 距离 $C$ 比 $B$ 距离 $C$ 近，那么 Chris 的父母先去 Shermie 家寻找 Chris，如果找不到，Chris 的父母再去 Yashiro 家；反之亦然。
2. Chris 的父母总沿着两点间唯一的通路行走。

显然，Chris 的老师知道 Chris 的父母在寻找 Chris 的过程中会遵守以上两条规则，但由于他并不知道 $A$、$B$、$C$ 的具体位置，所以现在他希望你告诉他，最坏情况下 Chris的父母要耗费多长时间才能找到 Chris？
## 输入格式

输入文件第一行是两个整数 $N$ 和 $M$，分别表示居住点总数和街道总数。

以下 $M$ 行，每行给出一条街道的信息。第 $i+1$ 行包含整数 $U_{i}$、$V_{i}$、$T_{i}$，表示街道 $i$ 连接居住点 $U_{i}$ 和 $V_{i}$，并且经过街道 $i$ 需花费 $T_{i}$ 分钟。街道信息不会重复给出。
## 输出格式

输出文件仅包含整数 $T$，即最坏情况下 Chris 的父母需要花费 $T$ 分钟才能找到 Chris。
## 样例

### 样例输入 #1
```
4 3
1 2 1
2 3 1
3 4 1
```
### 样例输出 #1
```
4
```
## 提示

对于 $100\%$ 的数据，$3 \le N \le 2\times 10^5$，$1 \le U_{i},V_{i} \le N$，$1 \le T_{i} \le 10^{9}$。


---

---
title: "[NOIP 2018 普及组] 摆渡车"
layout: "post"
diff: 提高+/省选-
pid: P5017
tag: ['动态规划 DP', '2018', 'NOIP 普及组', '枚举', '深度优先搜索 DFS', '斜率优化']
---
# [NOIP 2018 普及组] 摆渡车
## 题目背景

NOIP2018 普及组 T3
## 题目描述

有 $n$ 名同学要乘坐摆渡车从人大附中前往人民大学，第 $i$ 位同学在第 $t_i$ 分钟去 等车。只有一辆摆渡车在工作，但摆渡车容量可以视为无限大。摆渡车从人大附中出发、 把车上的同学送到人民大学、再回到人大附中（去接其他同学），这样往返一趟总共花费 $m$ 分钟（同学上下车时间忽略不计）。摆渡车要将所有同学都送到人民大学。  

凯凯很好奇，如果他能任意安排摆渡车出发的时间，那么这些同学的等车时间之和最小为多少呢？    

注意：摆渡车回到人大附中后可以即刻出发。
## 输入格式

第一行包含两个正整数 $n, m$，以一个空格分开，分别代表等车人数和摆渡车往返一趟的时间。    
第二行包含 $n$ 个正整数，相邻两数之间以一个空格分隔，第 $i$ 个非负整数 $t_i$ 代表第 $i$ 个同学到达车站的时刻。 
## 输出格式

输出一行，一个整数，表示所有同学等车时间之和的最小值（单位：分钟）。 
## 样例

### 样例输入 #1
```
5 1 
3 4 4 3 5 
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
5 5 
11 13 1 5 5 
```
### 样例输出 #2
```
4
```
## 提示

**样例 1 说明**    

同学 $1$ 和同学 $4$ 在第 $3$ 分钟开始等车，等待 $0$ 分钟，在第 $3$ 分钟乘坐摆渡车出发。摆渡车在第 $4$ 分钟回到人大附中。   
同学 $2$ 和同学 $3$ 在第 $4$ 分钟开始等车，等待 $0$ 分钟，在第 $4$ 分钟乘坐摆渡车 出发。摆渡车在第 $5$ 分钟回到人大附中。   
同学 $5$ 在第 $5$ 分钟开始等车，等待 $0$ 分钟，在第 $5$ 分钟乘坐摆渡车出发。自此 所有同学都被送到人民大学。总等待时间为 $0$。

**样例 2 说明**  

同学 $3$ 在第 $1$ 分钟开始等车，等待 $0$ 分钟，在第 $1$ 分钟乘坐摆渡车出发。摆渡 车在第 $6$ 分钟回到人大附中。   
同学 $4$ 和同学 $5$ 在第 $5$ 分钟开始等车，等待 $1$ 分钟，在第 $6$ 分钟乘坐摆渡车 出发。摆渡车在第 $11$ 分钟回到人大附中。   
同学 $1$ 在第 $11$ 分钟开始等车，等待 $2$ 分钟；同学 $2$ 在第 $13$ 分钟开始等车， 等待 $0$ 分钟。他/她们在第 $13$ 分钟乘坐摆渡车出发。自此所有同学都被送到人民大学。 总等待时间为 $4$。  
可以证明，没有总等待时间小于 $4$ 的方案。 

**数据规模与约定**

对于 $10\%$ 的数据，$n ≤ 10$，$m = 1$，$0 ≤ t_i ≤ 100$。   
对于 $30\%$ 的数据，$n ≤ 20$，$m ≤ 2$，$0 ≤ t_i ≤ 100$。  
对于 $50\%$ 的数据，$n ≤ 500$，$m ≤ 100$，$0 ≤ t_i ≤ 10^4$。  
另有 $20\%$ 的数据，$n ≤ 500$，$m ≤ 10$，$0 ≤ t_i ≤ 4 \times  10^6$。  
对于 $100\%$ 的数据，$n ≤ 500$，$m ≤ 100$，$0 ≤ t_i ≤ 4 \times 10^6$。


---

---
title: "[NOIP 2018 提高组] 赛道修建"
layout: "post"
diff: 提高+/省选-
pid: P5021
tag: ['贪心', '2018', '二分', 'NOIP 提高组', '最近公共祖先 LCA']
---
# [NOIP 2018 提高组] 赛道修建
## 题目描述

C 城将要举办一系列的赛车比赛。在比赛前，需要在城内修建 $m$ 条赛道。 

C 城一共有 $n$ 个路口，这些路口编号为 $1,2,…,n$，有 $n-1$ 条适合于修建赛道的双向通行的道路，每条道路连接着两个路口。其中，第 $i$ 条道路连接的两个路口编号为 $a_i$ 和 $b_i$，该道路的长度为 $l_i$。借助这 $n-1$ 条道路，从任何一个路口出发都能到达其他所有的路口。 

一条赛道是一组互不相同的道路 $e_1,e_2,…,e_k$，满足可以从某个路口出发，依次经过 道路 $e_1,e_2,…,e_k$（每条道路经过一次，不允许调头）到达另一个路口。一条赛道的长度等于经过的各道路的长度之和。为保证安全，要求每条道路至多被一条赛道经过。 

目前赛道修建的方案尚未确定。你的任务是设计一种赛道修建的方案，使得修建的 $m$ 条赛道中长度最小的赛道长度最大（即 $m$ 条赛道中最短赛道的长度尽可能大）
## 输入格式

输入文件第一行包含两个由空格分隔的正整数 $n,m$，分别表示路口数及需要修建的 赛道数。 

接下来 $n-1$ 行，第 $i$ 行包含三个正整数 $a_i,b_i,l_i$，表示第 $i$ 条适合于修建赛道的道 路连接的两个路口编号及道路长度。保证任意两个路口均可通过这 $n-1$ 条道路相互到达。每行中相邻两数之间均由一个空格分隔。 
## 输出格式

输出共一行，包含一个整数，表示长度最小的赛道长度的最大值。 
## 样例

### 样例输入 #1
```
7 1 
1 2 10 
1 3 5 
2 4 9 
2 5 8 
3 6 6 
3 7 7
```
### 样例输出 #1
```
31
```
### 样例输入 #2
```
9 3 
1 2 6 
2 3 3 
3 4 5 
4 5 10 
6 2 4 
7 2 9 
8 4 7 
9 4 4
```
### 样例输出 #2
```
15
```
## 提示

【输入输出样例 1 说明】 

所有路口及适合于修建赛道的道路如下图所示：      

![](https://cdn.luogu.com.cn/upload/image_hosting/bkj3pfqm.png)

道路旁括号内的数字表示道路的编号，非括号内的数字表示道路长度。 需要修建 $1$ 条赛道。可以修建经过第 $3,1,2,6$ 条道路的赛道（从路口 $4$ 到路口 $7$）， 则该赛道的长度为 $9 + 10 + 5 + 7 = 31$，为所有方案中的最大值。

【输入输出样例 2 说明】

 所有路口及适合于修建赛道的道路如下图所示：   
  

![](https://cdn.luogu.com.cn/upload/image_hosting/e9lcljwr.png)

需要修建 $3$ 条赛道。可以修建如下 $3$ 条赛道： 
1. 经过第 $1,6 $条道路的赛道（从路口 $1$ 到路口$ 7$），长度为 $6 + 9 = 15$； 
2. 经过第$ 5,2,3,8$ 条道路的赛道（从路口$ 6$ 到路口 $9$），长度为 $4 + 3 + 5 + 4 = 16$；
3. 经过第 $7,4$ 条道路的赛道（从路口 $8$ 到路口$ 5$），长度为 $7 + 10 = 17$。 长度最小的赛道长度为 $15$，为所有方案中的最大值。 

### 数据规模与约定

所有测试数据的范围和特点如下表所示 :

| 测试点编号 | $n$ | $m$ | $a_i=1$ | $b_i=a_i+1$ | 分支不超过 $3$ |
|:-:|:-:|:-:|:-:|:-:|:-:|
| $1$ | $\le 5$ | $=1$ | 否 | 否 | 是 |
| $2$ | $\le 10$ | $\le n-1$ | 否 | 是 | 是 |
| $3$ | $\le 15$ | $\le n-1$ | 是 | 否 | 否 |
| $4$ | $\le 10^3$ | $=1$ | 否 | 否 | 是 |
| $5$ | $\le 3\times 10^4$ | $=1$ | 是 | 否 | 否 |
| $6$ | $\le 3\times 10^4$ | $=1$ | 否 | 否 | 否 |
| $7$ | $\le 3\times 10^4$ | $\le n-1$ | 是 | 否 | 否 |
| $8$ | $\le 5\times 10^4$ | $\le n-1$ | 是 | 否 | 否 |
| $9$ | $\le 10^3$ | $\le n-1$ | 否 | 是 | 是 |
| $10$ | $\le 3\times 10^4$ | $\le n-1$ | 否 | 是 | 是 |
| $11$ | $\le 5\times 10^4$ | $\le n-1$ | 否 | 是 | 是 |
| $12$ | $\le 50$ | $\le n-1$ | 否 | 否 | 是 |
| $13$ | $\le 50$ | $\le n-1$ | 否 | 否 | 是 |
| $14$ | $\le 200$ | $\le n-1$ | 否 | 否 | 是 |
| $15$ | $\le 200$ | $\le n-1$ | 否 | 否 | 是 |
| $16$ | $\le 10^3$ | $\le n-1$ | 否 | 否 | 是 |
| $17$ | $\le 10^3$ | $\le n-1$ | 否 | 否 | 否 |
| $18$ | $\le 3\times 10^4$ | $\le n-1$ | 否 | 否 | 否 |
| $19$ | $\le 3\times 10^4$ | $\le n-1$ | 否 | 否 | 否 |
| $20$ | $\le 5\times 10^4$ | $\le n-1$ | 否 | 否 | 否 |

其中，「分支不超过 $3$」的含义为：每个路口至多有 $3$ 条道路与其相连。

对于所有的数据，$2 \le n \le 5\times 10^4, \ 1 \le m \le n − 1,\ 1 \le a_i,b_i \le n,\  1 \le l_i \le 10^4$。


---

---
title: "[NOIP 2018 提高组] 旅行"
layout: "post"
diff: 提高+/省选-
pid: P5022
tag: ['搜索', '贪心', '2018', 'NOIP 提高组', '深度优先搜索 DFS', '基环树']
---
# [NOIP 2018 提高组] 旅行
## 题目背景

NOIP2018 提高组 D2T1
## 题目描述

小 Y 是一个爱好旅行的 OIer。她来到 X 国，打算将各个城市都玩一遍。 
  
小 Y 了解到，X 国的 $n$ 个城市之间有 $m$ 条双向道路。每条双向道路连接两个城市。 不存在两条连接同一对城市的道路，也不存在一条连接一个城市和它本身的道路。并且， 从任意一个城市出发，通过这些道路都可以到达任意一个其他城市。小 Y 只能通过这些 道路从一个城市前往另一个城市。   

小 Y 的旅行方案是这样的：任意选定一个城市作为起点，然后从起点开始，每次可 以选择一条与当前城市相连的道路，走向一个没有去过的城市，或者沿着第一次访问该 城市时经过的道路后退到上一个城市。当小 Y 回到起点时，她可以选择结束这次旅行或 继续旅行。需要注意的是，小 Y 要求在旅行方案中，每个城市都被访问到。   

为了让自己的旅行更有意义，小 Y 决定在每到达一个新的城市（包括起点）时，将 它的编号记录下来。她知道这样会形成一个长度为 $n$ 的序列。她希望这个序列的字典序 最小，你能帮帮她吗？  对于两个长度均为 $n$ 的序列 $A$ 和 $B$，当且仅当存在一个正整数 $x$，满足以下条件时， 我们说序列 $A$ 的字典序小于 $B$。 
  
- 对于任意正整数 $1 ≤ i < x$，序列 $A$ 的第 $i$ 个元素 $A_i$ 和序列 $B$ 的第 $i$ 个元素 $B_i$ 相同。   
- 序列 $A$ 的第 $x$ 个元素的值小于序列 $B$ 的第 $x$ 个元素的值。 
## 输入格式

输入文件共 $m + 1$ 行。第一行包含两个整数 $n,m(m ≤ n)$，中间用一个空格分隔。
 
接下来 m 行，每行包含两个整数 $u,v (1 ≤ u,v ≤ n)$ ，表示编号为 $u$ 和 $v$ 的城市之 间有一条道路，两个整数之间用一个空格分隔。 
## 输出格式

输出文件包含一行，$n$ 个整数，表示字典序最小的序列。相邻两个整数之间用一个 空格分隔。 
## 样例

### 样例输入 #1
```
6 5 
1 3 
2 3 
2 5 
3 4 
4 6
```
### 样例输出 #1
```
1 3 2 5 4 6
```
### 样例输入 #2
```
6 6 
1 3 
2 3 
2 5 
3 4 
4 5 
4 6
```
### 样例输出 #2
```
1 3 2 4 5 6
```
## 提示

【数据规模与约定】   

对于 $100\%$ 的数据和所有样例， $1 \le n \le 5000 $ 且 $m = n − 1$ 或 $m = n$ 。

对于不同的测试点， 我们约定数据的规模如下：

![](https://cdn.luogu.com.cn/upload/pic/43271.png)


---

---
title: "[NOIP 1997 提高组] 棋盘问题 加强版"
layout: "post"
diff: 提高+/省选-
pid: P5512
tag: ['搜索', '1997', 'NOIP 提高组', 'Special Judge']
---
# [NOIP 1997 提高组] 棋盘问题 加强版
## 题目背景

[P1549](https://www.luogu.org/problem/P1549) 数据加强版。

**数据从 5 扩大到了 10。**



因为本题数据可能存在诸多争议，故特开一题用来测试加强版数据。
## 题目描述

在 $N \times N$（$1 \le N \le 10$）的棋盘上，填入 $1, 2, \dots, N ^ 2$ 共 $N ^ 2$ 个数，使得任意两个相邻的数之和为素数。

例如：当 $N = 2$ 时，有：

| $1$ | $2$ |
| :-----------: | :-----------: |
| $4$ | $3$ |

其相邻数的和为素数的有：

$1+2,1+4,4+3,2+3$

当 $N=4$ 时，一种可以填写的方案如下：

| $1$ | $2$ | $11$ | $12$ |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $16$ | $15$ | $8$ | $5$ |
| $13$ | $4$ | $9$ | $14$ |
| $6$ | $7$ | $10$ | $3$ |

在这里我们约定：左上角的格子里必须填数字 $1$。
## 输入格式

一行一个整数 $N$。
## 输出格式

如有多种解，则输出第一行、第一列之和为最小的排列方案；若无解，则输出 `NO`。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
1 2
4 3
```
### 样例输入 #2
```
1
```
### 样例输出 #2
```
NO
```
## 提示

$N\leq10$

 $N=1,2,...,10$ 的数据都各有一个点，由于某些原因， $N$ 不一定与测试点编号相等。

----

**数据新修复于 `2020.1.20`**


---

---
title: "[NOI2001] 陨石的秘密"
layout: "post"
diff: 提高+/省选-
pid: P5694
tag: ['动态规划 DP', '2001', 'NOI']
---
# [NOI2001] 陨石的秘密
## 题目描述

公元11380年，一颗巨大的陨石坠落在南极。于是，灾难降临了，地球上出现了一系列反常的现象。当人们焦急万分的时候，一支中国科学家组成的南极考察队赶到了出事地点。经过一番侦察，科学家们发现陨石上刻有若干行密文，每一行都包含5个整数：

```
1 1 1 1 6
0 0 6 3 57
8 0 11 3 2845
```

著名的科学家 SS 发现，这些密文实际上是一种复杂运算的结果。为了便于大家理解这种运算，他定义了一种 SS 表达式：

1. SS 表达式是仅由 `{`, `}`, `[`, `]`, `(`, `)` 组成的字符串。
2. 一个空串是 SS 表达式。
3. 如果 $ A $ 是SS表达式，且 $ A $ 中不含字符 `{`, `}`, `[`, `]`，则 $ (A) $ 是SS表达式。
4. 如果 $ A $ 是 SS 表达式，且 $ A $ 中不含字符 `{`, `}`，则 $ [A] $ 是 SS 表达式。
5. 如果 $ A $ 是 SS 表达式，则 $ \{A\} $ 是 SS 表达式。
6. 如果 $ A $ 和 $ B $ 都是 SS 表达式，则 $ AB $ 也是 SS 表达式。

一个 SS 表达式 $ E $ 的深度 $ D(E) $定义如下：

$$
\scriptstyle{
D(E) =
\begin{cases}
 \scriptstyle{0}, & \scriptstyle{\text{如果 } E \text{ 是空串}} \\
 \scriptstyle{D(A) + 1}, &  \scriptstyle{\text{如果 } E = (A) \text{ 或者 } E = [A] \text{ 或者 } E = \{A\}, \text{ 其中 } A \text{ 是 SS 表达式}} \\
 \scriptstyle{\max(D(A), D(B))}, &  \scriptstyle{\text{ 如果 } E = AB, \text{其中 } A, B \text{ 是 SS 表达式}}
\end{cases}
}
$$

例如 `(){()}[]` 的深度为 $ 2 $。

密文中的复杂运算是这样进行的：

设密文中每行前 $ 4 $ 个数依次为 $ L_1, L_2, L_3, D $，求出所有深度为 $ D $，含有 $ L_1 $ 对 `{}`，$ L_2 $ 对 `[]`，$ L_3 $ 对 `()` 的 SS 串的个数，并用这个数对当前的年份 $ 11380 $ 求余数，这个余数就是密文中每行的第 $ 5 $ 个数，我们称之为“神秘数”。

密文中某些行的第五个数已经模糊不清，而这些数字正是揭开陨石秘密的钥匙。现在科学家们聘请你来计算这个神秘数。

## 输入格式

共一行，$ 4 $ 个整数 $ L_1, L_2, L_3, D $。相邻两个数之间用一个空格分隔。
## 输出格式

共一行，包含一个整数，即神秘数。
## 样例

### 样例输入 #1
```
1 1 1 2
```
### 样例输出 #1
```
8
```
## 提示

$ 0 \le L_1, L_2, L_3 \le 10$，$0 \le D \le 30 $。


---

---
title: "[NOI1999] 钉子和小球"
layout: "post"
diff: 提高+/省选-
pid: P5750
tag: ['1999', 'NOI']
---
# [NOI1999] 钉子和小球
## 题目描述

有一个三角形木板,竖直立放，上面钉着 $ \frac{ n (n+1) } { 2 } $ 颗钉子，还有 ($n+1$) 个格子 （当 $n=5$ 时如图 1 ） 。每颗钉子和周围的钉子的距离都等于 $d$ ，每个格子的宽度也都等于 $d$ ，且除了最左端和最右端的格子外每个格子都正对着最下面一排钉子的间隙。

让一个直径略小于 $d$ 的小球中心正对着最上面的钉子在板上自由滚落，小球每碰到一个钉子都可能落向左边或右边 （概率各 $1/2$ ） ，且球的中心还会正对着下一颗将要碰上的钉子。例如图2 就是小球一条可能的路径。

我们知道小球落在第 $i$ 个格子中的概率 $p_i$ = $ \frac{C_n^i}{2^n}$ = $ \frac{ n! }{ 2^n i! (n-i)! } $ ，其中 $i$ 为格子的编号，从左至右依次为 $ 0 , 1 , ... , n $.
 
现在的问题是计算拔掉某些钉子后，小球落在编号为 $m$ 的格子中的概率 $p_m$ 。假定最下面一排钉子不会被拔掉。例如图3 是某些钉子被拔掉后小球一条可能的路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/ntaygrw7.png)

 图1  $\qquad$$\qquad$ $\quad$$\quad$  图2    $\quad$$\qquad$ $\qquad$$\quad$                       图3 
## 输入格式

第1行为整数 $n$ （$ 2 \leq n \leq  50 $）和 $m$ （ $ 0 \leq m \leq n $ ）。以下 $n$ 行依次为木板上从上至下$n$行钉子的信息，每行中 ‘*’ 表示钉子还在， ‘.’ 表示钉子被拔去，注意在这 $n$ 行中空格符可能出现在任何位置。
## 输出格式

仅一行，是一个既约分数( $0$ 写成 $0/1$ ) ，为小球落在编号为 $m$ 的格子中的概率 $p_m$ 。

既约分数的定义： $A/B$ 是既约分数，当且仅当 $A$ 、 $B$ 为正整数且 $A$ 和 $B$ 没有大于$1$的公因子。
## 样例

### 样例输入 #1
```
5 2
    *    
   * .
  * * *
 * . * *
* * * * *

```
### 样例输出 #1
```
7/16

```


---

---
title: "[NOI1997] 卫星覆盖"
layout: "post"
diff: 提高+/省选-
pid: P5762
tag: ['1997', 'NOI']
---
# [NOI1997] 卫星覆盖
## 题目描述

SERCOI（Space-Earth Resource Cover-Observe lnstitute） 是一个致力于利用卫星技术对空间和地球资源进行覆盖观测的组织。现在他们研制成功一种新型资源观测卫星 -SERCOI-308。这种卫星可以覆盖空间直角坐标系中一定大小的立方体空间，卫星处于该立方体的中心。
    其中 $（x,y,z）$ 为立方体的中心点坐标， $r$ 为此中心点到立方体各个面的距离（即 $r$ 为立方体高的一半）．立方体的各条边均平行于相应的坐标轴。我们可以用一个四元组 $(x,y,z,r)$ 描述一颗卫星的状态，它所能覆盖的空间体积 。
由于一颗卫星所能覆盖的空间体积是有限的，因此空间中可能有若干颗卫星协同工作。它们所覆盖的空间区域可能有重叠的地方，如下图所示（阴影部分表示重叠的区域）。

![](https://cdn.luogu.com.cn/upload/image_hosting/yeajeuoh.png)

写一个程序，根据给定的卫星分布情况，计算它们所覆盖的总体积。

## 输入格式

第一行是一个正整数 $N$ （$ 1 \le N \le 100 $）：表示空间中的卫星总数。接下来的 $N$ 行每行给出了一颗卫星的状态，用空格隔开的四个正整数 $x,y,z,r$ 依次表示了该卫星所能覆盖的立方体空间的中心点坐标和半高，其中 ($ -1000 \le x,y,z \le 1000$，$1 \le r \le 200 )$。
## 输出格式

只有一行,包括一个正整数，表示所有这些卫星所覆盖的空间总体积。

## 样例

### 样例输入 #1
```
3
0 0 0 3
1 -1 0 1
19 3 5 6

```
### 样例输出 #1
```
1944

```


---

---
title: "[NOI Online #1 提高组] 序列"
layout: "post"
diff: 提高+/省选-
pid: P6185
tag: ['2020', '并查集', '二分图', 'NOI Online']
---
# [NOI Online #1 提高组] 序列
## 题目背景

## 由于本题数据较难构造，所以无法保证卡掉所有错误做法。


## 题目描述

小 D 有一个长度为 $n$ 的整数序列 $a_{1 \dots n}$，她想通过若干次操作把它变成序列 $b_i$。

小 D 有 $m$ 种可选的操作，第 $i$ 种操作可使用三元组 $(t_i,u_i,v_i)$ 描述：若 $t_i=1$，则她可以使 $a_{u_i}$ 与 $a_{v_i}$ 都加一或都减一；若 $t_i=2$，则她可以使 $a_{u_i}$ 减一、$a_{v_i}$ 加一，或是 $a_{u_i}$ 加一、$a_{v_i}$ 减一，因此当 $u_i=v_i$ 时，这种操作相当于没有操作。

小 D 可以以任意顺序执行操作，且每种操作都可进行无限次。现在给定序列与所有操作，请你帮她判断是否存在一种方案能将 $a_i$ 变为 $b_i$。题目保证两个序列长度都为 $n$。若方案存在请输出 `YES`，否则输出 `NO`。
## 输入格式

本题输入文件包含多组数据。

第一行一个正整数 $T$ 表示数据组数。对于每组数据：

第一行两个整数 $n,m$，表示序列长度与操作种数。

第二行 $n$ 个整数表示序列 $a_i$。

第三行 $n$ 个整数表示序列 $b_i$。

接下来 $m$ 行每行三个整数 $t_i,u_i,v_i$，第 $i$ 行描述操作 $i$。

注意：同一个三元组 $(t_i,u_i,v_i)$ 可能在输入中出现多次。
## 输出格式

对于每组数据输出一行一个字符串 `YES` 或 `NO` 表示答案。
## 样例

### 样例输入 #1
```
3
1 1
1
3
1 1 1
2 3
1 2
4 5
1 1 2
2 1 2
1 1 2
3 3
1 2 3
5 5 4
1 1 2
1 1 3
2 2 3
```
### 样例输出 #1
```
YES
YES
YES
```
## 提示

#### 样例 1 解释

第一组数据：使用一次操作 $1$。  
第二组数据：使用三次操作 $1$。  
第三组数据：使用三次操作 $1$，令 $a_1,a_2$ 都增加 $3$，再使用一次操作 $2$，令 $a_1,a_3$ 都增加 $1$。

---

#### 数据范围与提示

对于测试点 $1 \sim 5$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=1$。  
对于测试点 $6 \sim 10$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=2$。  
对于测试点 $11 \sim 12$：$n=2$，$a_i,b_i \le 99$，$u_i \ne v_i$。  
对于测试点 $13 \sim 16$：$t_i=2$。  
对于测试点 $17$：$n,m \le 20$。  
对于测试点 $18$：$n,m \le 10^3$。  
对于所有测试点：$1 \le T \le 10$，$1 \le n,m \le 10^5$，$1 \le a_i,b_i \le 10^9$，$t_i \in \{1,2\}$，$1\le u_i,v_i \le n$。


---

---
title: "[NOI Online #1 提高组] 冒泡排序"
layout: "post"
diff: 提高+/省选-
pid: P6186
tag: ['2020', '树状数组', 'NOI Online']
---
# [NOI Online #1 提高组] 冒泡排序
## 题目描述

给定一个 $1 ∼ n$ 的排列 $p_i$，接下来有 $m$ 次操作，操作共两种：
1. 交换操作：给定 $x$，将当前排列中的第 $x$ 个数与第 $x+1$ 个数交换位置。
2. 询问操作：给定 $k$，请你求出当前排列经过 $k$ 轮冒泡排序后的逆序对个数。
对一个长度为 $n$ 的排列 $p_i$ 进行一轮冒泡排序的伪代码如下：
```
for i = 1 to n-1:
  if p[i] > p[i + 1]:
    swap(p[i], p[i + 1])
```
## 输入格式

第一行两个整数 $n$，$m$，表示排列长度与操作个数。

第二行 $n$ 个整数表示排列 $p_i$。

接下来 $m$ 行每行两个整数 $t_i$，$c_i$，描述一次操作：
- 若 $t_i=1$，则本次操作是交换操作，$x=c_i$；
- 若 $t_i=2$，则本次操作是询问操作，$k=c_i$。
## 输出格式

对于每次询问操作输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 6
1 2 3
2 0
1 1
1 2
2 0
2 1
2 2
```
### 样例输出 #1
```
0
2
1
0
```
## 提示

#### 样例一解释
第一次操作：排列为 $\{1,2,3\}$，经过 0 轮冒泡排序后为 $\{1,2,3\}$，$0$ 个逆序对。

第二次操作：排列变为 $\{2,1,3\}$。

第三次操作：排列变为 $\{2,3,1\}$。

第四次操作：经过 $0$ 轮冒泡排序后排列变为 $\{2,3,1\}$，$2$ 个逆序对。

第五次操作：经过 $1$ 轮冒泡排序后排列变为 $\{2,1,3\}$，$1$ 个逆序对。

第六次操作：经过 $2$ 轮冒泡排序后排列变为 $\{1,2,3\}$，$0$ 个逆序对。

---

#### 数据范围与提示
对于测试点 1 ∼ 2：$n,m \leq 100$。

对于测试点 3 ∼ 4：$n,m \leq 2000$。

对于测试点 5 ∼ 6：交换操作个数不超过 $100$。

对于所有测试点：$2 \leq n,m \leq 2 \times 10^5$，$t_i \in \{1,2\}$，$1 \leq x < n$，$0 \leq k < 2^{31}$。


---

---
title: "[NOI Online #1 提高组] 最小环"
layout: "post"
diff: 提高+/省选-
pid: P6187
tag: ['贪心', '2020', 'NOI Online']
---
# [NOI Online #1 提高组] 最小环
## 题目描述

给定一个长度为 $n$ 的正整数序列 $a_i$，下标从 $1$ 开始编号。我们将该序列视为一个首尾相邻的环，更具体地，对于下标为 $i$, $j(i \leqslant j)$ 的两个数 $a_i$, $a_j$，它们的距离为 $\min(j-i, i+n-j)$。

现在再给定 $m$ 个整数 $k_1$, $k_2$,..., $k_m$，对每个 $k_i(i=1$, $2$,..., $m)$，你需要将上面的序列 $a_i$ 重新排列，使得环上任意两个距离为 $k_i$ 的数字的乘积之和最大。
## 输入格式

第一行两个正整数 $n$, $m$，表示序列长度与询问数。

接下来一行 $n$ 个正整数表示 $a_i$。

接下来 $m$ 行每行一个非负整数表示 $k_i$。

## 输出格式

共 $m$ 行，每行一个整数表示答案。
## 样例

### 样例输入 #1
```
6 4
1 2 3 4 5 6
0
1
2
3
```
### 样例输出 #1
```
91
82
85
88
```
## 提示

#### 输入输出样例 1 解释
- $k=0$ 时：答案为每个数平方的和。
- $k=1$ 时：一种最优方案：$\{3,1,2,4,6,5\}$。答案为 $3 \times 1 + 1 \times 2 + 2 \times 4 + 4 \times 6 + 6 \times 5 + 5 \times 3 = 82$。
- $k=2$ 时：一种最优方案：$\{3,6,1,4,2,5\}$。答案为 $3 \times 1 + 1 \times 2 + 2 \times 3 + 6 \times 4 + 4 \times 5 + 5 \times 6 = 85$。
- $k=3$ 时，一个合法的排列是 $1,5,3,2,6,4$ ，答案为 $88$。注意这里答案不是 $44$。

---

#### 数据范围与提示
对于所有测试数据：$1 \leqslant m \leqslant n \leqslant 2 \times 10^5$，$0 \leqslant k \leqslant \lfloor n/2\rfloor$，$1 \leqslant a_i \leqslant 10^5$。

| 测试点编号 | $n \leqslant$ | 特殊性质|
| :--- | :--- | :--- |
| 1 | $10$ | 无 |
| 2 | $18$ | 无 |
| 3 | $36$ | $n$ 为偶数且 $m=1$，$k=2$ |
| 4,5 | $1000$ | $m \leqslant 10$，$k=1$ |
| 6 | $50$ | $m \leqslant 10$，$k \leqslant 2$ |
| 7,8 | $3000$ | 无 |
| 9,10 | $2 \times 10^5$ | 无 |


---

---
title: "[NOI Online #2 入门组] 荆轲刺秦王"
layout: "post"
diff: 提高+/省选-
pid: P6474
tag: ['搜索', '2020', 'NOI Online']
---
# [NOI Online #2 入门组] 荆轲刺秦王
## 题目背景

本测试数据为脚造，欢迎提供 hack。

第 18 组数据卡了很多人，放于附件中供检查。
## 题目描述

时隔数年，刺客荆轲再次来到咸阳宫，试图刺杀嬴政。

咸阳宫的地图可以描述为一个 $n$ 行 $m$ 列的矩形。在这里，我们规定每一行中从左到右为 $x$ 轴正方向，每一列中从下到上为 $y$ 轴正方向，左下角的点坐标为 $(1,1)$。矩形中的点可以分为 $4$ 种：

1. 起点，也就是荆轲的所在点，在地图中用字符 `S` 代表。
2. 终点，也就是嬴政的所在点，在地图中用字符 `T` 代表。
3. 卫兵，在地图中用一个正整数 $a_{i,j}$ 代表。在这里，一个卫兵 $(i,j)$ 可以观察到与他曼哈顿距离小于 $a_{i,j}$ 的点。也就是卫兵 $(i,j)$ 可以观察到所有满足 $|x-i|+|y-j|<a_{i,j}$ 的点 $(x,y)$。
4. 空地，在地图中用字符 `.` 代表。

荆轲的正常移动方式为每秒向八连通的任意方向前进一格。如下图，中间的点为荆轲当前所在点，每一秒，他可以走向其余的八个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/9rnnpj4z.png)

需要注意的是，正常移动时，荆轲不能踏进任何一个有卫兵或者卫兵能观察到的格子。当然，他也不能走出咸阳宫，也就是说，无论何时，荆轲的坐标 $(x,y)$ 都必须满足 $1\le x\le m$ 且 $1\le y\le n$。

荆轲还有两种技能：隐身和瞬移。

1. 隐身：下一秒荆轲进入隐身状态，卫兵观察不到荆轲，荆轲可以进入卫兵的观察范围内，但仍然不能进入卫兵所在的格子。注意这个状态只能维持一秒。
2. 瞬移：荆轲下一秒移动的距离改为 $d$，但这时只能向上下左右四个方向移动。即可以移动到 
$(x+d,y)$，$(x-d,y)$，$(x,y+d)$，$(x,y-d)$。
在本题中，两种技能可以同时使用，而且不考虑冷却时间，即一次用完可以立即用下一次，两种技能都分别有使用次数限制，你也可以不用完所有次数。

现在给出咸阳城的地图，请计算荆轲到达秦王所在点所需的最短时间。此外，在所用时间相同情况下，荆轲希望使用的两种技能总次数尽可能少；在所用时间与技能次数相同情况下，荆轲希望使用的隐身次数尽可能少。
## 输入格式

第一行五个整数 $n$, $m$, $c_1$, $c_2$, $d$，代表地图的大小为 $n\times m$，隐身的使用限制次数为 $c_1$，瞬移的使用限制次数为 $c_2$ 和一次瞬移的距离为 $d$。

接下来 $n$ 行，每行 $m$ 个元素。每个元素为字符 `S`、`T`、`.` 或者一个正整数 $a_{i,j}$，代表一个格点，具体含义详见题目描述。
## 输出格式

若荆轲无法到达秦王所在点，则输出一行一个 $-1$。

否则输出一行三个整数 $t$, $u_1$, $u_2$，依次代表所需的最短时间，隐身的使用次数与瞬移的使用次数。
## 样例

### 样例输入 #1
```
5 4 0 0 5
. 1 T 1
. . . 2
. 1 . .
S . . .
1 . . .
```
### 样例输出 #1
```
3 0 0
```
### 样例输入 #2
```
8 6 2 3 3
. S . . . .
. . . . . .
. . . . . .
. . . . . .
. . . . . .
2 . 2 . 2 .
. . 1 . T .
3 . 1 . . 3

```
### 样例输出 #2
```
3 1 3
```
### 样例输入 #3
```
8 6 5 5 2
. S . . . .
. . . . . .
. . . . . .
1 1 3 2 . 1
2 3 2 2 1 3 
3 2 4 1 4 3 
2 6 1 5 T 2 
8 1 6 3 2 10
```
### 样例输出 #3
```
-1
```
## 提示

#### 样例 1 解释

起点为 $(1,2)$，荆轲可以依次走到 $(1,3)$, $(2,4)$, $(3,5)$ 到达终点。

#### 样例 2 解释

起点为 $(2,8)$，荆轲可以依次走到 $(2,5)$, $(2,2)$, $(5,2)$，需要注意的是，即使最后一步到达终点，但因为终点在卫兵的观察范围之内，所以仍然需要隐身进入。

#### 数据范围与提示


对于测试点 $1\sim 6$：$n$, $m\le 10$，$c_1=c_2=0$，保证所需的最短时间不超过 $5$ 或者无解。

对于测试点 $7\sim 10$：$n$, $m\le 20$，$c_1=c_2=0$，保证 `T` 的位置不在任何一个卫兵的观察范围之中。

对于测试点 $11\sim 12$：$n$, $m\le 20$，$c_1=0$

对于测试点 $13\sim 14$：$n$, $m\le 20$，$c_1$, $c_2 \le 5$。

对于测试点 $15\sim 16$：卫兵个数不超过 $350$。

对于所有测试点：$2\le n$, $m\le 350$，$1\le a_{i,j}\le 350$，$0\le c_1$, $c_2\le 15$，$1\le d\le 350$。

保证 `S` 的位置不在任何卫兵的观察范围中。


---

---
title: "[NOI Online #2 入门组] 建设城市"
layout: "post"
diff: 提高+/省选-
pid: P6475
tag: ['动态规划 DP', '2020', '排列组合', 'NOI Online']
---
# [NOI Online #2 入门组] 建设城市
## 题目描述

球球是一位建筑师。一天，他收到市长的任务：建设城市。球球打算建造 $2n$ 座高楼。为了保证城市美观，球球做出了如下计划：

- 球球喜欢整齐的事物。他希望高楼从左向右排成一行，编号依次为 $1\sim 2n$。

- 球球喜欢整数，他要求每座高楼的高度都是正整数。

- 由于材料限制，高楼的高度无法超过 $m$。

- 球球喜欢中间高，两边低的造型。他要求前 $n$ 座高楼的高度不下降，后 $n$ 座高楼的高度不上升。

- 球球打算选两座编号为 $x,y$ 的高楼作为这座城市的地标。他认为只有当这两座高楼高度相等时，才会让城市变得美观。

球球把自己的想法告诉了市长。市长希望得知所有建设城市的方案数。两种方案不同，当且仅当某座高楼的高度在两个方案中不同。这个问题可难倒了球球。球球找到了你，希望你能帮他算出答案。由于答案可能很大，你只需要给出答案对 $998244353$ 取模后的结果。
## 输入格式

从标准输入读入数据。

仅一行四个整数 $m,n,x,y$，变量意义见题目描述。
## 输出格式

输出到标准输出。

仅一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 2 1 3
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
1000 1000 535 1477
```
### 样例输出 #2
```
295916566
```
## 提示

对于样例 $1$，所有的方案为：$\{1,1,1,1\},\{1,2,1,1\},\{1,3,1,1\},\{2,2,2,1\},\{2,2,2,2\},\\\{2,3,2,1\},\{2,3,2,2\},\{3,3,3,1\},\{3,3,3,2\},\{3,3,3,3\}$。

对于 $10\%$ 的数据，$1\le n,m\le 5$。

对于 $30\%$ 的数据，$1\le n,m\le 100$。

对于 $60\%$ 的数据，$1\le n,m\le 1000$。

对于 $100\%$ 的数据，$1\le x < y \le 2n$， $1\le n,m \le 10^5$。


---

---
title: "[NOI Online #2 提高组] 子序列问题"
layout: "post"
diff: 提高+/省选-
pid: P6477
tag: ['2020', '线段树', '树状数组', 'NOI Online']
---
# [NOI Online #2 提高组] 子序列问题
## 题目背景

2s 512M
## 题目描述

给定一个长度为 $n$ 的正整数序列 $A_1$, $A_2$, $\cdots$, $A_n$。定义一个函数 $f(l,r)$ 表示：序列中下标在 $[l,r]$ 范围内的子区间中，不同的整数个数。换句话说，$f(l,r)$ 就是集合 $\{A_l,A_{l+1},\cdots,A_r\}$ 的大小，这里的集合是不可重集，即集合中的元素互不相等。

现在，请你求出 $\sum_{l=1}^n\sum_{r=l}^n (f(l,r))^2$。由于答案可能很大，请输出答案对 $10^9 +7$ 取模的结果。
## 输入格式

第一行一个正整数 $n$，表示序列的长度。

第二行 $n$ 个正整数，相邻两个正整数用空格隔开，表示序列 $A_1$, $A_2$, $\cdots$, $A_n$。
## 输出格式

仅一行一个非负整数，表示答案对 $10^9+7$ 取模的结果。

## 样例

### 样例输入 #1
```
4
2 1 3 2
```
### 样例输出 #1
```
43
```
### 样例输入 #2
```
3
1 1 1
```
### 样例输出 #2
```
6
```
## 提示

对于 $10\%$ 的数据，满足 $1 \leq n \leq 10$；

对于 $30\%$ 的数据，满足 $1 \leq n \leq 100$；

对于 $50\%$ 的数据，满足 $1\leq n \leq 10^3$；

对于 $70\%$ 的数据，满足 $1 \leq n \leq 10^5$；

对于 $100\%$ 的数据，满足 $1\leq n\leq 10^6$，集合中每个数的范围是 $[1,10^9]$。


---

---
title: "[NOI Online #3 提高组] 魔法值"
layout: "post"
diff: 提高+/省选-
pid: P6569
tag: ['2020', '倍增', '矩阵运算', 'NOI Online']
---
# [NOI Online #3 提高组] 魔法值
## 题目描述

H 国的交通由 $n$ 座城市与 $m$ 条道路构成，城市与道路都从 $1$ 开始编号，其中 $1$ 号城市是 H 国的首都。H 国中一条道路将把两个不同城市直接相连，且任意两个城市间至多有一条道路。

H 国是一个信奉魔法的国家，在第 $j$ 天，$i$ 号城市的魔法值为 $f_{i,j}$。H 国的魔法师已观测到第 0 天时所有城市的魔法值 $f_{i,0}$，且他们还发现，之后的每一天每个城市的魔法值，都将会变为所有与该城市直接相连的城市的前一天魔法值的异或值，即

$$
f_{x,j}=f_{v_1,j-1}\oplus f_{v_2,j-1}\oplus \cdots\oplus f_{v_k,j-1}
$$

其中 $j\ge 1$，$v_1,v_2,\cdots,v_k$ 是所有与 $x$ 号城市直接相连的城市，$\oplus$ 为异或运算。

现在 H 国的国王问了你 $q$ 个问题，对于第 $i$（$1\le i\le q$）个问题你需要回答：第 $a_i$ 天时首都的魔法值是多少。
## 输入格式

第一行三个用空格分隔的整数 $n,m,q$，表示城市数、道路数与问题数。

第二行 $n$ 个用空格分隔的整数，第 $i$ 个整数表示 $f_{i, 0}$。

接下来 $m$ 行，每行两个用空格分隔的正整数 $u,v$，表示一条连接 $u$ 号城市与 $v$ 号城市的道路。

接下来 $q$ 行每行一个整数，第 $i$ 行的整数表示 $a_i$。
## 输出格式

按顺序输出 $q$ 行每行一个整数，表示对应问题的答案。
## 样例

### 样例输入 #1
```
3 3 1
0 0 1
1 2
1 3
2 3
1

```
### 样例输出 #1
```
1
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，满足 $a_i \leq 100$。
- 对于 $40\%$ 的数据，满足 $n \leq 20$。
- 另有 $30\%$ 的数据，满足 $m=\frac{n(n-1)}{2}$。
- 对于 $100\%$ 的数据，满足 $1 \leq n,q \leq 100$，$1 \leq m \leq \frac{n(n-1)}{2}$，$1\leq a_i < 2^{32}$，$0\leq f_i < 2^{32}$。

#### 说明

data provider ：@一扶苏一，数据有锅请联系她。如果被朴素的快速幂水过去了也请联系她。


---

---
title: "[NOIP2020] 字符串匹配"
layout: "post"
diff: 提高+/省选-
pid: P7114
tag: ['字符串', '2020', '倍增', 'NOIP 提高组', '哈希 hashing']
---
# [NOIP2020] 字符串匹配
## 题目描述

小 C 学习完了字符串匹配的相关内容，现在他正在做一道习题。

对于一个字符串 $S$，题目要求他找到 $S$ 的所有具有下列形式的拆分方案数：

$S = ABC$，$S = ABABC$，$S = ABAB \ldots ABC$，其中 $A$，$B$，$C$ 均是非空字符串，且 $A$ 中出现奇数次的字符数量不超过 $C$ 中出现奇数次的字符数量。

更具体地，我们可以定义 $AB$ 表示两个字符串 $A$，$B$ 相连接，例如 $A = \texttt{aab}$，$B = \texttt{ab}$，则 $AB = \texttt{aabab}$。

并递归地定义 $A^1=A$，$A^n = A^{n - 1} A$（$n \ge 2$ 且为正整数）。例如 $A = \texttt{abb}$，则 $A^3=\texttt{abbabbabb}$。

则小 C 的习题是求 $S = {(AB)}^iC$ 的方案数，其中 $F(A) \le F(C)$，$F(S)$ 表示字符串 $S$ 中出现奇数次的字符的数量。两种方案不同当且仅当拆分出的 $A$、$B$、$C$ 中有至少一个字符串不同。

小 C 并不会做这道题，只好向你求助，请你帮帮他。
## 输入格式

本题有多组数据，输入文件第一行一个正整数 $T$ 表示数据组数。

每组数据仅一行一个字符串 $S$，意义见题目描述。$S$ 仅由英文小写字母构成。
## 输出格式

对于每组数据输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
nnrnnr
zzzaab
mmlmmlo

```
### 样例输出 #1
```
8
9
16

```
### 样例输入 #2
```
5
kkkkkkkkkkkkkkkkkkkk
lllllllllllllrrlllrr
cccccccccccccxcxxxcc
ccccccccccccccaababa
ggggggggggggggbaabab

```
### 样例输出 #2
```
156
138
138
147
194

```
### 样例输入 #3
```
见附件中的 string/string3.in
```
### 样例输出 #3
```
见附件中的 string/string3.ans
```
### 样例输入 #4
```
见附件中的 string/string4.in
```
### 样例输出 #4
```
见附件中的 string/string4.ans
```
## 提示

**【样例 #1 解释】**

对于第一组数据，所有的方案为

1. $A=\texttt{n}$，$B=\texttt{nr}$，$C=\texttt{nnr}$。
2. $A=\texttt{n}$，$B=\texttt{nrn}$，$C=\texttt{nr}$。
3. $A=\texttt{n}$，$B=\texttt{nrnn}$，$C=\texttt{r}$。
4. $A=\texttt{nn}$，$B=\texttt{r}$，$C=\texttt{nnr}$。
5. $A=\texttt{nn}$，$B=\texttt{rn}$，$C=\texttt{nr}$。
6. $A=\texttt{nn}$，$B=\texttt{rnn}$，$C=\texttt{r}$。
7. $A=\texttt{nnr}$，$B=\texttt{n}$，$C=\texttt{nr}$。
8. $A=\texttt{nnr}$，$B=\texttt{nn}$，$C=\texttt{r}$。

**【数据范围】**

| 测试点编号 | $\lvert S \rvert \le$ | 特殊性质 |
|:-:|:-:|:-:|
| $1 \sim 4$ | $10$ | 无 |
| $5 \sim 8$ | $100$ | 无 |
| $9 \sim 12$ | $1000$ | 无 |
| $13 \sim 14$ | $2^{15}$ | $S$ 中只包含一种字符 |
| $15 \sim 17$ | $2^{16}$ | $S$ 中只包含两种字符 |
| $18 \sim 21$ | $2^{17}$ | 无 |
| $22 \sim 25$ | $2^{20}$ | 无 |

对于所有测试点，保证 $1 \le T \le 5$，$1 \le |S| \le 2^{20}$。 


---

---
title: "[NOI Online 2021 入门组] 重力球"
layout: "post"
diff: 提高+/省选-
pid: P7473
tag: ['图论', '2021', '最短路', 'NOI Online']
---
# [NOI Online 2021 入门组] 重力球
## 题目描述

“重力球”游戏在一块 $n\times n$ 的正方形区域中进行，记从上往下第 $i$ 行，从左往右第 $j$ 列的位置为 $(i,j)$。

正方形区域中存在 $m$ 个障碍，第 $i$ 个障碍占据位置 $(x_i,y_i)$，此外，正方形区域的边界外都是障碍。

现在有两个小球，位置分别是 $(a,b)$ 和 $(c,d)$，在游戏中你可以进行如下操作：

- 指定上、下、左、右中的一个方向，将重力方向“切换”为这个方向。此时两个小球会同时向这个方向移动，直到碰到障碍。

你要用最少的操作次数使得两个小球到达同一个位置。

现有 $q$ 局游戏，每局游戏中只有小球的初始位置不同，而障碍位置是不变的，你需要对每局游戏都求出最小操作次数，或报告无解。
## 输入格式

第一行包含三个整数 $n,m,q$，分别表示矩形区域大小，障碍个数和游戏局数。

接下来 $m$ 行，每行包含两个整数 $x_i,y_i$，表示位置 $(x_i,y_i)$ 上有一个障碍。数据保证所有障碍所处的位置互不相同。

接下来 $q$ 行，每行四个整数 $a,b,c,d$，表示一局游戏中两个小球的初始位置，保证初始位置不存在障碍。
## 输出格式

输出共 $q$ 行，第 $i$ 行输出一个整数表示第 $i$ 局游戏需要的最小操作次数，如果无解则输出 `-1`。
## 样例

### 样例输入 #1
```
4 4 3
2 2
2 4
3 2
4 4
1 3 4 3
2 1 2 1
1 2 3 4
```
### 样例输出 #1
```
1
0
3
```
## 提示

### 样例 $1$ 解释

该样例中障碍分布如图中红叉所示。

第一组询问中只需将重力改向上（或改向下）即可使两球同时到达。

第二组询问中两球已经在同一位置故不需操作。

第三组询问中改变3 次重力的方向，依次改为向左、向下、向左，小球移动路线分别如图中粉色、橙色、棕色线所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7nngrov0.png)
### 数据范围与提示
对于 $20\%$ 的数据：$n,m\le 2$。

对于 $50\%$ 的数据：$n,m\le30$。

对于另外 $30\%$ 的数据：$q=1$。

对于 $100\%$ 的数据：$1\le n,m\le250，1\le q\le10^5，1\le x_i,y_i,a,b,c,d\le n$。

数据由 [SSerxhs](https://www.luogu.com.cn/user/29826) 提供。

数据参考了 小喵喵不喜欢计算几何 2020 ICPC 区域赛（南京）A 题的构造方案，在此表示感谢。


---

---
title: "[NOIP2021] 数列"
layout: "post"
diff: 提高+/省选-
pid: P7961
tag: ['动态规划 DP', '2021', 'NOIP 提高组', 'O2优化', '排列组合']
---
# [NOIP2021] 数列
## 题目描述

给定整数 $n, m, k$，和一个长度为 $m + 1$ 的正整数数组 $v_0, v_1, \ldots, v_m$。

对于一个长度为 $n$，下标从 $1$ 开始且每个元素均不超过 $m$ 的非负整数序列 $\{a_i\}$，我们定义它的权值为 $v_{a_1} \times v_{a_2} \times \cdots \times v_{a_n}$。

当这样的序列 $\{a_i\}$ 满足整数 $S = 2^{a_1} + 2^{a_2} + \cdots + 2^{a_n}$ 的二进制表示中 $1$ 的个数不超过 $k$ 时，我们认为 $\{a_i\}$ 是一个合法序列。

计算所有合法序列 $\{a_i\}$ 的权值和对 $998244353$ 取模的结果。
## 输入格式

输入第一行是三个整数 $n, m, k$。

第二行 $m + 1$ 个整数，分别是 $v_0, v_1, \ldots, v_m$。
## 输出格式

仅一行一个整数，表示所有合法序列的权值和对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
5 1 1
2 1

```
### 样例输出 #1
```
40

```
### 样例输入 #2
```
见附件中的 sequence/sequence2.in
```
### 样例输出 #2
```
见附件中的 sequence/sequence2.ans
```
## 提示

**【样例解释 #1】**

由于 $k = 1$，而且由 $n \leq S \leq n \times 2^m$ 知道 $5 \leq S \leq 10$，合法的 $S$ 只有一种可能：$S = 8$，这要求 $a$ 中必须有 $2$ 个 $0$ 和 $3$ 个 $1$，于是有 $\binom{5}{2} = 10$ 种可能的序列，每种序列的贡献都是 $v_0^2 v_1^3 = 4$，权值和为 $10 \times 4 = 40$。

**【数据范围】**

对所有测试点保证 $1 \leq k \leq n \leq 30$，$0 \leq m \leq 100$，$1 \leq v_i < 998244353$。

|    测试点    |  $n$  |   $k$    |  $m$   |
| :----------: | :---: | :------: | :----: |
|  $1 \sim 4$  | $=8$  | $\leq n$ |  $=9$  |
|  $5 \sim 7$  | $=30$ | $\leq n$ |  $=7$  |
| $8 \sim 10$  | $=30$ | $\leq n$ | $=12$  |
| $11 \sim 13$ | $=30$ |   $=1$   | $=100$ |
| $14 \sim 15$ | $=5$  | $\leq n$ | $=50$  |
|     $16$     | $=15$ | $\leq n$ | $=100$ |
| $17 \sim 18$ | $=30$ | $\leq n$ | $=30$  |
| $19 \sim 20$ | $=30$ | $\leq n$ | $=100$ |


---

---
title: "[NOI Online 2022 提高组] 丹钓战"
layout: "post"
diff: 提高+/省选-
pid: P8251
tag: ['2022', 'O2优化', 'NOI Online']
---
# [NOI Online 2022 提高组] 丹钓战
## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

**这一题中出现了评测记录测试点编号错乱的问题，是民间数据命名方式冲突导致的。但是我们保证其相对顺序没有混乱。**

民间数据提供者：@Froggy。
## 题目描述

有 $n$ 个二元组 $(a_i, b_i)$，编号为 $1$ 到 $n$。

有一个初始为空的栈 $S$，向其中加入元素 $(a_i, b_i)$ 时，先不断弹出栈顶元素直至栈空或栈顶元素 $(a_j , b_j)$ 满足 $a_i \neq a_j$ 且 $b_i < b_j$，然后再将其加入栈中。

如果一个二元组入栈后栈内只有这一个元素，则称该二元组是“成功的”。

有 $q$ 个询问 $[l_i, r_i]$，表示若将编号在 $[l_i, r_i]$ 中的二元组按编号从小到大依次入栈，会有多少个二元组是“成功的”。

询问之间相互独立。
## 输入格式

第一行两个正整数 $n,q$。

第二行 $n$ 个正整数表示 $a_i$。

第三行 $n$ 个正整数表示 $b_i$。

接下来 $q$ 行，每行两个正整数 $l_i, r_i$，表示一组询问。
## 输出格式

$q$ 行，每行一个自然数表示一组询问的答案。
## 样例

### 样例输入 #1
```
10 4
3 1 3 1 2 3 3 2 1 1
10 10 2 9 7 5 4 7 6 1
1 4
7 8
7 10
1 8
```
### 样例输出 #1
```
3
2
2
3
```
## 提示

**【样例解释】**

以第一次询问 $[1, 4]$ 为例。

一开始栈为 $\{\}$。

加入 $1$ 号二元组后栈为 $\{(3, 10)\}$，栈中只有一个元素，该二元组是“成功的”。

加入 $2$ 号二元组 $(1, 10)$ 时，栈顶的 $(3, 10)$ 的 $b$ 值不大于 $2$ 号二元组的，因此弹栈。此时栈空，$2$
号二元组入栈，栈为 $\{(1, 10)\}$，该二元组是“成功的”。

加入 $3$ 号二元组 $(3, 2)$，此时栈顶元素与之 $a$ 值不同，$b$ 值比它更大，因而不需要弹栈，直接将 $3$ 号二元组入栈，栈为 $\{(1, 10),(3, 2)\}$，栈中有多个元素，该二元组不是“成功的”。

加入 $4$ 号二元组 $(1, 9)$，此时栈顶元素 $(3, 2)$ 的 $b$ 值比它小，弹栈。弹栈后栈顶元素 $(1, 10)$ 与
$(1, 9)$ 的 $a$ 值相同，继续弹栈。此时栈空，$4$ 号二元组入栈，栈为 $\{(1, 9)\}$，该二元组是“成功的”。共有 $3$ 个二元组是“成功的”，因而答案为 $3$。

**【样例 2,3,4】**

见附件 $\texttt{stack/stack*.in}$ 与 $\texttt{stack/stack*.ans}$。

链接：<https://pan.baidu.com/s/14XxLN63bxvpJAod81foGOg> 
提取码：gugu

**【数据范围与提示】**

对于所有测试点：$1 \leq n, q \leq 5 \times 10^5$，$1 \leq a_i, b_i \leq n$，$1 \leq l_i \leq r_i \leq n$。

每个测试点的具体限制见下表：

| 测试点编号   | 特殊性质        |
| ------------ | --------------- |
| $1 \sim 3$   | $n,q \leq 1000$ |
| $4 \sim 6$   | $n \leq 5000$   |
| $7 \sim 10$  | $n,q \leq 10^5$ |
| $11 \sim 12$ | $b_i=n-i+1$     |
| $13 \sim 15$ | $a_i=i$         |
| $16 \sim 20$ | 无              |


---

---
title: "[NOI Online 2022 提高组] 讨论"
layout: "post"
diff: 提高+/省选-
pid: P8252
tag: ['2022', 'Special Judge', 'O2优化', 'NOI Online']
---
# [NOI Online 2022 提高组] 讨论
## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

**这一题中出现了评测记录测试点编号错乱的问题，是民间数据命名方式冲突导致的。但是我们保证其相对顺序没有混乱。**

民间数据提供者：@AutumnKite，由 @tiger2005 进行加强。
## 题目描述

有 $n$ 个人正在打模拟赛，模拟赛有 $n$ 道题目。  
有两人都会的题目并且没有人会的题目包含另一个人时，两者之间才会讨论。  
（定义第 $i$ 个人会的题目的集合为 $S_i$ ，即当 $S_x\cap S_y\neq\varnothing\land S_x\not\subseteq S_y\land S_y\not\subseteq S_x$ 时，第 $x$ 人和第 $y$ 人会讨论）  
为了让模拟赛的效果更好，希望你可以找出一对会讨论的人或判断不存在。
## 输入格式

第一行一个正整数 $T$ 表示数据组数，对于每组数据：  
第一行一个正整数 $n$ 表示人数和题目数量。  
接下来 $n$ 行，第 $i$ 行第一个自然数 $k_i$ 表示第 $i$ 个人会 $k_i$ 道题。接下来 $k_i$ 个正整数，每个数 $x$ 表示第 $i$ 个人会第 $x$ 道题。
## 输出格式

对于每组数据：  
如果没有会讨论的人，输出 `NO`。  
否则第一行输出 `YES`，第二行输出两个正整数 $x$ 和 $y$，表示第 $x$ 人和第 $y$ 人会讨论。  
如果有多种方案，输出任意一种即可。
## 样例

### 样例输入 #1
```
2
5
4 1 2 3 5
3 1 2 3
2 1 2
1 1
1 4
4
3 1 2 3
3 2 3 4
0
4 1 2 3 4
```
### 样例输出 #1
```
NO
YES
1 2
```
## 提示

**【样例 2】**

见附件中的 `discuss/discuss2.in` 与 `discuss/discuss2.ans`。

**【数据范围与提示】**

对于所有测试点：令一组数据中 $m=\sum k_i$，则 $1\le T\le 5$，$1\le \sum n\le {10}^6$，$1\le \sum m\le 2\times {10}^6$，$0\le k_i\le n$。

每个测试点的具体限制见下表：

![](https://cdn.luogu.com.cn/upload/image_hosting/zmkoxviw.png)


---

---
title: "[NOI Online 2022 入门组] 数学游戏"
layout: "post"
diff: 提高+/省选-
pid: P8255
tag: ['2022', 'O2优化', '最大公约数 gcd', 'NOI Online']
---
# [NOI Online 2022 入门组] 数学游戏
## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

民间数据提供者：@一扶苏一。本题不保证民间数据强度，详见[这个帖子](https://www.luogu.com.cn/discuss/422596)。
## 题目描述

Kri 喜欢玩数字游戏。

一天，他在草稿纸上写下了 $t$ 对正整数 $(x,y)$，并对于每一对正整数计算出了 $z=x\times y\times\gcd(x,y)$。

可是调皮的 Zay 找到了 Kri 的草稿纸，并把每一组的 $y$ 都擦除了，还可能改动了一些 $z$。

现在 Kri 想请你帮忙还原每一组的 $y$，具体地，对于每一组中的 $x$ 和 $z$，你需要输出最小的正整数 $y$，使得 $z=x\times y\times\gcd(x,y)$。如果这样的 $y$ 不存在，也就是 Zay 一定改动了 $z$，那么请输出 $-1$。

注：$\gcd(x,y)$ 表示 $x$ 和 $y$ 的最大公约数，也就是最大的正整数 $d$，满足 $d$ 既是 $x$ 的约数，又是 $y$ 的约数。
## 输入格式

第一行一个整数 ，表示有 $t$ 对正整数 $x$ 和 $z$。

接下来 $t$ 行，每行两个正整数 $x$ 和 $z$，含义见题目描述。
## 输出格式

对于每对数字输出一行，如果不存在满足条件的正整数 $y$，请输出 $-1$，否则输出满足条件的最小正整数 $y$。
## 样例

### 样例输入 #1
```
1
10 240
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
3
5 30
4 8
11 11
```
### 样例输出 #2
```
6
-1
1
```
### 样例输入 #3
```
见附件中的 math3.in
```
### 样例输出 #3
```
见附件中的 math3.out
```
### 样例输入 #4
```
见附件中的 math4.in
```
### 样例输出 #4
```
见附件中的 math4.out
```
## 提示

**【样例 1 解释】**

$x\times y\times \gcd(x,y)=10\times 12\times\gcd(10,12)=240$。

**【数据范围】**

对于 $20\%$ 的数据，$t, x, z \le {10}^3$。

对于 $40\%$ 的数据，$t \le {10}^3$，$x \le {10}^6$，$z \le {10}^9$。

对于另 $30\%$ 的数据，$t \le {10}^4$。

对于另 $20\%$ 的数据，$x \le {10}^6$。

对于 $100\%$ 的数据，$1 \le t \le 5 \times {10}^5$，$1 \le x \le {10}^9$，$1 \le z < 2^{63}$。


---

---
title: "[NOI Online 2022 入门组] 字符串"
layout: "post"
diff: 提高+/省选-
pid: P8256
tag: ['2022', 'O2优化', 'NOI Online']
---
# [NOI Online 2022 入门组] 字符串
## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

**这一题中出现了评测记录测试点编号错乱的问题，是民间数据命名方式冲突导致的。但是我们保证其相对顺序没有混乱。**

民间数据提供者：@tiger2005。
## 题目描述

Kri 非常喜欢字符串，所以他准备找 $t$ 组字符串研究。

第 $i$ 次研究中，Kri 准备了两个字符串 $S$ 和 $R$ ，其中 $S$ 长度为 $n$，且只由 `0`, `1`, `-` 三种字符构成（注：这里的第三种字符是减号），$R$ 初始时为空。

每次研究，Zay 会带着一个美丽的长度为 $m$ 的字符串 $T$ 来找 Kri 玩，Kri 非常羡慕 Zay 拥有如此美丽的字符串，便也想用字符串 $S$ 和 $R$ 变出字符串 $T$。

具体地，Kri 将会进行 $n$ 次操作。每次操作中，Kri 会取出 $S$ 的第一个字符（记为 $c$），并将其从 $S$ 中删去。如果 $c = \texttt{-}$，则 Kri 要删去 $R$ 的开头字符或结尾字符（数据保证删去后 $R$ 不为空）。否则，Kri 会将 $c$ 加入到 $R$ 的末尾。

当进行完所有操作后，Kri 会检查 $R$ 是否和 $T$ 相等。如果 $R = T$，Kri 就会感到开心；否则，Kri 会感到难受。

请问在每次研究中，Kri 有多少种操作方式使自己最后感到开心？我们定义两种方案不同，当且仅当在某种方案的某次操作中， Kri 删去了 $R$ 的开头字符。而在另一种方案的这次操作中， Kri 删去了 $R$ 的结尾字符。

由于答案可能很大，你只需要输出答案除以 $1,000,000,007$（即 $10^9+7$）的余数。
## 输入格式

第一行一个正整数 $t$。

接下来有 $t$ 组数据分别表示 $t$ 次字符串的研究，对于每组数据：

第一行有两个正整数 $n,m$，分别表示字符串 $S,T$ 的长度。

第二行是字符串 $S$。

第三行是字符串 $T$。
## 输出格式

共 $t$ 行，第 $i$ 行表示第 $i$ 组研究的答案。
## 样例

### 样例输入 #1
```
3
6 2
10-01-
01
7 3
010-1-1
101
6 4
111-00
1100
```
### 样例输出 #1
```
2
1
2
```
### 样例输入 #2
```
见附件中的 string2.in
```
### 样例输出 #2
```
见附件中的 string2.out
```
## 提示

**【样例 1 解释】**

对于第一组数据，有以下两种方案：

- 第一个 `-` 删 $R$ 的开头，第二个 `-` 删 $R$ 的开头。
- 第一个 `-` 删 $R$ 的结尾，第二个 `-` 删 $R$ 的开头。

**【数据范围】**

对于 $20\%$ 的数据，$n,m\le 15$。

对于 $30\%$ 的数据，$n,m\le 30$。

对于 $70\%$ 的数据，$n,m\le 80$。

对于另 $10\%$ 的数据，保证答案不超过 $1$。

对于 $100\%$ 的数据，$1\le t\le 5$，$1\le n,m\le 400$。


---

---
title: "[春季测试 2023] 圣诞树"
layout: "post"
diff: 提高+/省选-
pid: P9119
tag: ['2023', 'NOIP 提高组', 'Special Judge', 'O2优化']
---
# [春季测试 2023] 圣诞树
## 题目描述

众所周知，3202 年的圣诞节快要到了，因此小 Ω 买了一棵圣诞树和一根挂满了彩灯的电线，并打算把这根电线缠绕在圣诞树上。

圣诞树可以视作一个二维平面上有 $n$ 个顶点的**凸多边形**。这 $n$ 个顶点可以用于固定电线，且按**逆时针顺序**依次编号为 $1, \ldots, n$。其中第 $i$ 个顶点的坐标为 $(x_i, y_i)$，记其中 **$y$ 坐标最大**的顶点的编号为 $k$（若有多个满足条件的顶点，则取**编号最小**的）。不保证编号为 $1$ 的顶点的 $x$ 坐标最小。

下图左侧展示了一棵圣诞树的轮廓，其中 **$y$ 坐标最大**的顶点的编号为 $k = 5$。

![图 2：一棵圣诞树及一种可能的挂电线的方案](https://cdn.luogu.com.cn/upload/image_hosting/ayjegrhj.png)

小 Ω 希望用挂满了彩灯的电线装饰这棵圣诞树。出于美观性考虑，她希望这根电线**经过所有顶点恰好一次**；为了连接电源，这根电线需要**从 $(x_k, y_k)$ 出发**。形式化地，她需要决定一个 $1, \cdots, n$ 的**排列** $p_1, \cdots, p_n$，满足 $p_1 = k$，随后这根电线从 $(x_{p_1}, y_{p_1})$ 出发，依次经过 $(x_{p_2}, y_{p_2}), \cdots, (x_{p_n}, y_{p_n})$。此时，电线长度为 $\sum_{i=1}^{n-1}{\operatorname{d}((x_{p_i}, y_{p_i}), (x_{p_{i+1}}, y_{p_{i+1}}))}$。

- 其中 $\operatorname{d}$ 为平面上的**欧几里得距离**，即 $\operatorname{d}((x, y), (x', y')) = \sqrt{(x - x')^2 + (y - y')^2}$。

上图右侧展示了一种可能的方案，此时对应的排列为 $5, 4, 8, 6, 3, 9, 1, 7, 2$。

为了节省成本，她希望你能在所有可能的方案中，给出一种使电线长度**最短**的方案。如果使电线长度最短的方案不唯一，你只需要求出其中**任意**一种。

**考虑到浮点数产生的误差，你输出的方案与最优方案的线段长度的相对误差或绝对误差不超过 $10^{-10}$ 时即认为答案正确**。

## 输入格式

第一行包含一个正整数 $n$，表示圣诞树的顶点数。

接下来 $n$ 行，其中第 $i$ 行包含两个精确到小数点后 $9$ 位的实数 $x_i, y_i$ 表示编号为 $i$ 的顶点的坐标。

数据保证这 $n$ 个点**两两不同**，并且依次连接 $(x_1, y_1), (x_2, y_2), \cdots, (x_n, y_n)$ 将形成一个**凸多边形**。

## 输出格式

输出一行包含 $n$ 个由单个空格隔开的正整数 $p_1, p_2, \cdots, p_n$，表示一个 $1, \cdots, n$ 的排列，满足 $p_1 = k$，且电线的长度 $\sum_{i=1}^{n-1}{\operatorname{d}((x_{p_i}, y_{p_i}), (x_{p_{i+1}}, y_{p_{i+1}}))}$ 在所有可能的方案中**最短**。如果这样的方案不唯一，请输出其中任意一种方案。

## 样例

### 样例输入 #1
```
3
0.000000000 0.000000000
3.000000000 0.000000000
1.000000000 1.000000000

```
### 样例输出 #1
```
3 1 2

```
## 提示

**【样例 1 解释】**

这一样例中只有下图所示的两种方案，对应排列分别为 $3, 1, 2$ 或 $3, 2, 1$，电线长度分别为 $3 + \sqrt{2}$ 和 $3 + \sqrt{5}$，而 $3 + \sqrt{2} < 3 + \sqrt{5}$。

因此答案对应的排列为 $3, 1, 2$。

![图 3：样例 1 的全部两种可能的方案](https://cdn.luogu.com.cn/upload/image_hosting/tcwvp72y.png)

**【数据范围】**

对于所有数据，保证 $3 \le n \le 1000$；$|x_i|, |y_i| \le 10^7$。

|测试点编号|$n \le$|特殊性质|
|:-:|:-:|:-:|
|1, 2|$4$|无|
|3, 4, 5, 6|$9$|无|
|7, 8, 9, 10, 11, 12|$18$|无|
|13, 14|$10^3$|A|
|15, 16|$10^3$|B|
|17, 18, 19, 20|$10^3$|无|

特殊性质 A：保证存在正整数 $m \ge n$，使得输入的 $n$ 个顶点对应正 $m$ 边形中连续的一段顶点。

特殊性质 B：保证 $x_1 < x_2 < \cdots < x_n$，且 $y_1 > y_2 > \cdots > y_n$。



---

