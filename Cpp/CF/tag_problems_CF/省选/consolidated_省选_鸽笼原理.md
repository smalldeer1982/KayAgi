---
title: "Asesino (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2022D2
tag: ['鸽笼原理', '构造']
---

# Asesino (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, you must use the minimum number of queries possible. You can make hacks only if both versions of the problem are solved.

This is an interactive problem.

It is a tradition in Mexico's national IOI trainings to play the game "Asesino", which is similar to "Among Us" or "Mafia".

Today, $ n $ players, numbered from $ 1 $ to $ n $ , will play "Asesino" with the following three roles:

- Knight: a Knight is someone who always tells the truth.
- Knave: a Knave is someone who always lies.
- Impostor: an Impostor is someone everybody thinks is a Knight, but is secretly a Knave.

Each player will be assigned a role in the game. There will be exactly one Impostor but there can be any (possible zero) number of Knights and Knaves.

As the game moderator, you have accidentally forgotten the roles of everyone, but you need to determine the player who is the Impostor.

To determine the Impostor, you will ask some questions. In each question, you will pick two players $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ ; $ i \neq j $ ) and ask if player $ i $ thinks that player $ j $ is a Knight. The results of the question is shown in the table below.

 KnightKnaveImpostorKnightYesNoYesKnaveNoYesNoImpostorNoYes— The response of the cell in row $ a $ and column $ b $ is the result of asking a question when $ i $ has role $ a $ and $ j $ has row $ b $ . For example, the "Yes" in the top right cell belongs to row "Knight" and column "Impostor", so it is the response when $ i $ is a Knight and $ j $ is an Impostor.Find the Impostor in the minimum number of queries possible. That is, let $ f(n) $ be the minimum integer such that for $ n $ players, there exists a strategy that can determine the Impostor using at most $ f(n) $ questions. Then, you should use at most $ f(n) $ questions to determine the Impostor.

Note: the grader is adaptive: the roles of the players are not fixed in the beginning and may change depending on your questions. However, it is guaranteed that there exists an assignment of roles that is consistent with all previously asked questions under the constraints of this problem.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the number of people playing the game.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

To ask a question, output a line in the following format:

- "? i j" ( $ 1 \leq i,j \leq n $ ; $ i \neq j $ ) — to ask player $ i $ if they think player $ j $ is a Knight.

The jury will output a "1" if player $ i $ thinks player $ j $ is a Knight, and "0" otherwise.

When you have determined which player the Impostor is, output a line in the following format:

- "! i" ( $ 1 \leq i \leq n $ ) — the Impostor is player $ i $ .

Note that answering does not count to your limit of $ f(n) $ questions.

If you have made an invalid output, used more than $ f(n) $ questions or wrongly determined the Impostor, the jury will respond with "-1" and you will receive a Wrong Answer verdict. Upon receiving "-1", your program must terminate immediately. Otherwise, you may receive an arbitrary verdict because your solution might be reading from a closed stream.

After printing a query do not forget to output the end of the line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- sys.stdout.flush() in Python;
- std::io::stdout().flush() in Rust;
- see the documentation for other languages.

Hack format

For hacks, use the following format.

The first line should contain a single integer $ t $ — the number of test cases.

The first line of each test case should contain the integer $ n $ followed by the string "manual".

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -1 \le a_i \le 1 $ ) — the roles of each player. $ 1 $ denotes a Knight, $ 0 $ denotes a Knave, and $ -1 $ dentoes an Impostor. There must be exactly one Impostor, that is there must be exactly one index $ i $ such that $ a_i=-1 $ .

As an example, the hack format for the example input is:

```
<pre class="lstlisting">```
2<br></br>7 manual<br></br>0 1 0 -1 0 1 0<br></br>4 manual<br></br>0 1 -1 0<br></br>
```
```

## 说明/提示

Note that the example test cases do not represent an optimal strategy for asking questions and are only shown for the sake of demonstrating the interaction format. Specifically, we cannot determine which player is the Impostor from the questions asked in the examples.

In the first test case of the example, players at indices $ 2 $ and $ 6 $ are Knights, players at indices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are Knaves, and the Impostor is at index $ 4 $ . The following is an explanation of the questions asked:

- In the first query, player $ i $ is a Knave and player $ j $ is a Knave. The answer is "yes" since Knaves always lie.
- In the second query, player $ i $ is a Knave and player $ j $ is a Knight. The answer is "no" since Knaves always lie.
- In the third query, player $ i $ is a Knight and player $ j $ is a Knave. The answer is "no" since Knights always tell the truth.
- In the fourth query, player $ i $ is a Knight and player $ j $ is a Knight. The answer is "yes" since Knights always tell the truth.
- In the fifth query, player $ i $ is a Impostor and player $ j $ is a Knave. The answer is "yes" since the Impostor always lies.
- In the sixth query, player $ i $ is a Impostor and player $ j $ is a Knight. The answer is "no" since the Impostor always lies.
- In the seventh query, player $ i $ is a Knave and player $ j $ is a Impostor. The answer is "no" since Knaves always lie and Knaves thinks that the Impostor is a Knight.

## 样例 #1

### 输入

```
2
7

1

0

0

1

1

0

0

4

0

1

1

1
```

### 输出

```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3
```



---

---
title: "Secret Message"
layout: "post"
diff: 省选/NOI-
pid: CF2057G
tag: ['鸽笼原理', '构造']
---

# Secret Message

## 题目描述

每个周六晚上，平行班的老师亚历山大 B，总会把一封密码信息写在交互式在线白板上，发送给另一位老师亚历山大 G。这封信相当重要，而亚历山大 G 正在授课，因此在线白板就成了一个理想的秘密传递工具。

这个白板是一个由 $n$ 行 $m$ 列构成的网格。网格中每个单元格大小是 $1 \times 1$。部分单元格已经填满，用符号 "." 表示，不能在其中书写；剩下的未填满的单元格称为自由单元格，用符号 "#" 代表。

我们需要关注白板的两个特性：

- $s$：自由单元格的数量。
- $p$：由这些自由单元格构成的图形的边界周长。

设 $A$ 为当前所有自由单元格的集合。你的任务是从中找到一个子集 $S \subseteq A$，满足以下条件：

- $|S| \le \frac{1}{5} \cdot (s+p)$，即集合 $S$ 的大小不超过 $s$ 和 $p$ 的加和的五分之一。
- 每一个自由单元格，要么已经在 $S$ 中，要么与 $S$ 中的某个单元格相邻（共用一条边）。

可以证明，总有这样的集合 $S$ 存在，你只需找到任意符合条件的一个即可。

## 输入格式

首先输入一个整数 $t$ 表示测试用例的数量（$1 \le t \le 80\,000$）。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ （$1 \le n, m \le 2 \cdot 10^6$），分别表示网格的行数和列数。

接下来的 $n$ 行给出网格的具体描述。

所有测试用例中，所有 $n \cdot m$ 的总和不超过 $2 \cdot 10^6$。

## 输出格式

对于每个测试用例，输出 $n$ 行，每行有 $m$ 个字符，表示网格中的单元状态：

- "#" 表示该单元格在 $A$ 中但不在 $S$ 中；
- "S" 表示该单元格同时在 $A$ 和 $S$ 中；
- "." 表示该单元格既不在 $A$ 中也不在 $S$ 中。

## 说明/提示

例如：

- 在第一个例子中，$s=5$ 和 $p=12$，所以 $S$ 的单元格数量不能超过 $\frac{1}{5} \cdot (5+12) = 3.4$，即 $|S| \le 3$。给出的 $S$ 集合包含 1 个单元格，符合条件。

- 在第二个例子中，$s=12$ 和 $p=16$，所以 $S$ 的单元格数量不能超过 $\frac{1}{5} \cdot (12+16)= 5.6$，即 $|S| \le 5$。给出的 $S$ 集合包含 4 个单元格，符合条件。

- 在第三个例子中说明了周长的概念。任何网格图形都有一个由线段组成的边界，边界线段的长度总和即为周长。在示例中，黑色粗线标示的是自由单元格形成图形的边界，其总长度为 $p=24$。同时，$s=11$，故上限为 $|S| \le 7$，给出的 $S$ 集合大小为 6，符合条件。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2057G/7a81d6643999264740192ed7581cb70b4cce9f3c.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3 3
.#.
###
.#.
2 6
######
######
3 7
###....
#.#.###
###....
```

### 输出

```
.#.
#S#
.#.
#S##S#
#S##S#
S#S....
#.#.S#S
S#S....
```



---

