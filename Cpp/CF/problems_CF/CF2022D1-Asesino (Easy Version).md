---
title: "Asesino (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2022D1
tag: ['构造']
---

# Asesino (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, you can ask at most $ n+69 $ questions. You can make hacks only if both versions of the problem are solved.

This is an interactive problem.

It is a tradition in Mexico's national IOI trainings to play the game "Asesino", which is similar to "Among Us" or "Mafia".

Today, $ n $ players, numbered from $ 1 $ to $ n $ , will play "Asesino" with the following three roles:

- Knight: a Knight is someone who always tells the truth.
- Knave: a Knave is someone who always lies.
- Impostor: an Impostor is someone everybody thinks is a Knight, but is secretly a Knave.

Each player will be assigned a role in the game. There will be exactly one Impostor but there can be any (possible zero) number of Knights and Knaves.

As the game moderator, you have accidentally forgotten the roles of everyone, but you need to determine the player who is the Impostor.

To determine the Impostor, you will ask some questions. In each question, you will pick two players $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ ; $ i \neq j $ ) and ask if player $ i $ thinks that player $ j $ is a Knight. The results of the question is shown in the table below.

 KnightKnaveImpostorKnightYesNoYesKnaveNoYesNoImpostorNoYes— The response of the cell in row $ a $ and column $ b $ is the result of asking a question when $ i $ has role $ a $ and $ j $ has row $ b $ . For example, the "Yes" in the top right cell belongs to row "Knight" and column "Impostor", so it is the response when $ i $ is a Knight and $ j $ is an Impostor.Find the Impostor in at most $ n + 69 $ questions.

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

Note that answering does not count to your limit of $ n+69 $ questions.

If you have made an invalid output, used more than $ n+69 $ questions or wrongly determined the Impostor, the jury will respond with "-1" and you will receive a Wrong Answer verdict. Upon receiving "-1", your program must terminate immediately. Otherwise, you may receive an arbitrary verdict because your solution might be reading from a closed stream.

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
- In the eighth query, player $ i $ is a Knight and player $ j $ is a Impostor. The answer is "yes" since Knights always tell the truth and Knights think that the Impostor is a Knight.

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

1

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

? 2 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3
```

