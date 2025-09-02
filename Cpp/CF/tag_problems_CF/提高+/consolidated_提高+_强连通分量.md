---
title: "Mouse Hunt"
layout: "post"
diff: 提高+/省选-
pid: CF1027D
tag: ['模拟', '强连通分量', '概率论']
---

# Mouse Hunt

## 题目描述

伯兰州立大学的医学部刚刚结束了招生活动。和以往一样，约80%的申请人都是女生并且她们中的大多数人将在未来4年（真希望如此）住在大学宿舍里。

宿舍楼里有$n$个房间和**一只老鼠**！女孩们决定在一些房间里设置捕鼠器来除掉这只可怕的怪物。在$i$号房间设置陷阱要花费$c_i$伯兰币。房间编号从$1$到$n$。

要知道老鼠不是一直原地不动的，它不停地跑来跑去。如果$t$秒时它在$i$号房间，那么它将在$t+1$秒时跑到$a_i$号房间，但这期间不会跑到别的任何房间里($i=a_i$表示老鼠没有离开原来的房间)。时间从$0$秒开始，一旦老鼠窜到了有捕鼠器的房间里，这只老鼠就会被抓住。

如果女孩们知道老鼠一开始在哪里不就很容易吗？不幸的是，情况不是这样，老鼠在第$0$秒时可能会在从$1$到$n$的任何一个房间内。

那么女孩们最少要花多少钱设置捕鼠器，才能保证老鼠无论从哪个房间开始流窜最终都会被抓到？

## 输入格式

第1行一个整数n($1\le n \le 2*10^5$)，表示宿舍楼里的房间数。

第2行有$n$个整数，$c_1, c_2, \dots, c_n(1\le c_i \le 10^4)$，$c_i$表示在$i$号房间设置捕鼠器的花费。

第3行有$n$个整数，$a_1, a_2, \dots, a_n(1\le a_i \le n)$，$a_i$是老鼠在$i$号房间时，下一秒会窜到的房间号。

## 输出格式

输出一个整数，表示设置捕鼠器的最小花费（保证无论老鼠一开始在什么位置最终都能被抓住！）。

## 样例 #1

### 输入

```
5
1 2 3 2 10
1 3 4 3 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 10 2 10
2 4 2 2

```

### 输出

```
10

```

## 样例 #3

### 输入

```
7
1 1 1 1 1 1 1
2 2 2 3 6 7 6

```

### 输出

```
2

```



---

---
title: "Anya's Simultaneous Exhibition"
layout: "post"
diff: 提高+/省选-
pid: CF1779E
tag: ['强连通分量']
---

# Anya's Simultaneous Exhibition

## 题目描述

This is an interactive problem.

Anya has gathered $ n $ chess experts numbered from $ 1 $ to $ n $ for which the following properties hold:

- For any pair of players one of the players wins every game against the other (and no draws ever occur);
- Transitivity does not necessarily hold — it might happen that $ A $ always beats $ B $ , $ B $ always beats $ C $ and $ C $ always beats $ A $ .

 Anya does not know, for each pair, who is the player who beats the other.To organize a tournament, Anya hosts $ n-1 $ games. In each game, she chooses two players. One of them wins and stays, while the other one is disqualified. After all the games are hosted only one player will remain. A player is said to be a candidate master if they can win a tournament (notice that the winner of a tournament may depend on the players selected by Anya in the $ n-1 $ games).

Since Anya is a curious girl, she is interested in finding the candidate masters. Unfortunately, she does not have much time. To speed up the process, she will organize up to $ 2n $ simuls (short for "simultaneous exhibition", in which one player plays against many).

In one simul, Anya chooses exactly one player who will play against some (at least one) of the other players. The chosen player wins all games they would win in a regular game, and the same holds for losses. After the simul finishes, Anya is only told the total number of games won by the chosen player (but not which ones). Nobody is disqualified during a simul.

Can you help Anya host simuls and determine the candidate masters?

The winning players in each pair could be changed between the simuls, but only in a way that preserves the results of all previous simuls. These changes may depend on your queries.

## 输出格式

Firstly, the jury sends one integer $ n $ ( $ 3 \leq n \leq 250 $ ) which should be read — the number of players. After that, your program may ask queries or report an answer.

To ask a query, print "? $ i \; s_1 s_2 \ldots s_n $ " (without quotes), where $ i $ is the index of the player who will play against some of the other players in the simul. $ s $ is a binary string that denotes the players they play against. $ i $ plays against every player $ j $ for which $ s_j = 1 $ holds (and $ s_j = 1 $ should hold for at least one $ 1 \leq j \leq n $ ). Please note that $ s_i = 0 $ must hold since a player cannot play against themselves, otherwise, the query is considered to be incorrect.

After this, you should read an integer — the number of games player $ i $ has won.

When you have identified the answer, you must print "! $ c_1 c_2 \ldots c_n $ " (without quotes) and terminate your program. $ c $ is a binary string which represents the candidate masters. Player $ i $ is a candidate master if $ c_i=1 $ holds, otherwise, they are not.

If you ask more than $ 2n $ queries or if one of the queries is malformed, the interaction terminates immediately and your program receives verdict Wrong Answer.

After printing a query do not forget to output the end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see the documentation for other languages.

Hacks are disabled in this problem.

## 说明/提示

In the first example, the first query describes a simul in which player $ 1 $ plays against player $ 2 $ (and no one else). The answer to the query is $ 1 $ , meaning that player $ 1 $ won the only game they played. We can conclude that $ 1 $ beats $ 2 $ . Similarly, the second query tells us that $ 2 $ beats $ 3 $ and the third query tells us that $ 3 $ beats $ 1 $ . All players are candidate masters in this case as

- Player $ 1 $ can win the tournament if $ 2 $ and $ 3 $ play first. $ 3 $ loses and leaves, while $ 2 $ stays. $ 1 $ then plays against $ 2 $ and wins;
- Other players can win in the same fashion.

In the second example, the third query describes a simul in which player $ 1 $ plays against every other player. The answer to the query is $ 4 $ , meaning that they won every game they played. It can be concluded that player $ 1 $ also beats every other player. They can never lose, hence they are the only player who can remain at the end of every possible tournament, and the only possible candidate master.

## 样例 #1

### 输入

```
3

1

1

1
```

### 输出

```
? 1 010

? 2 001

? 3 100

! 111
```

## 样例 #2

### 输入

```
5

0

3

4
```

### 输出

```
? 5 10110

? 2 10111

? 1 01111

! 10000
```



---

---
title: "Strictly Positive Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF402E
tag: ['搜索', '强连通分量', '栈']
---

# Strictly Positive Matrix

## 题目描述

You have matrix $ a $ of size $ n×n $ . Let's number the rows of the matrix from $ 1 $ to $ n $ from top to bottom, let's number the columns from $ 1 $ to $ n $ from left to right. Let's use $ a_{ij} $ to represent the element on the intersection of the $ i $ -th row and the $ j $ -th column.

Matrix $ a $ meets the following two conditions:

- for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the following inequality holds: $ a_{ij}>=0 $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF402E/5a3402d889c26bb1dab24aca748b24c9c6e8398d.png).

Matrix $ b $ is strictly positive, if for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the inequality $ b_{ij}&gt;0 $ holds. You task is to determine if there is such integer $ k>=1 $ , that matrix $ a^{k} $ is strictly positive.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=2000 $ ) — the number of rows and columns in matrix $ a $ .

The next $ n $ lines contain the description of the rows of matrix $ a $ . The $ i $ -th line contains $ n $ non-negative integers $ a_{i1},a_{i2},...,a_{in} $ ( $ 0<=a_{ij}<=50 $ ). It is guaranteed that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF402E/5a3402d889c26bb1dab24aca748b24c9c6e8398d.png).

## 输出格式

If there is a positive integer $ k>=1 $ , such that matrix $ a^{k} $ is strictly positive, print "YES" (without the quotes). Otherwise, print "NO" (without the quotes).

## 样例 #1

### 输入

```
2
1 0
0 1

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
5
4 5 6 1 2
1 2 3 4 5
6 4 1 2 4
1 1 1 1 1
4 4 4 4 4

```

### 输出

```
YES

```



---

---
title: "Reachability from the Capital"
layout: "post"
diff: 提高+/省选-
pid: CF999E
tag: ['深度优先搜索 DFS', '强连通分量', '概率论']
---

# Reachability from the Capital

## 题目描述

在 Berland 有 $n$ 座城市和 $m$ 条道路，每条道路连接着一对城市。

Berland 的道路都是**单向**的

为了能让首都能够到达所有的城市，最少需要新修建多少新道路？

新道路也是单向的

## 输入格式

输入的第一行包含三个整数 $n,m$ 和 $s$ $(1\le n \le 5000,0\le m \le 5000 , 1\le s \le n)$ ——城市数，道路数和首都所在城市的标号。 城市的标号为 $1$ \~ $n$
接下来 $m$ 行每行包含一条道路连接着一对城市 $u_i,v_i$ $(1\le u_i,v_i\le n,u_i\ne v_i)$

 对于每对城市 $u,v$，从 $u$ 到 $v$ 最多只能有一条道路。 允许在一对城市之间建造相反方向的道路（即从 $u$ 到 $v$ 和从 $v$ 到 $u$ ）。

## 输出格式

输出一个整数——使从首都可以到达所有城市所需的最少新修建道路数。如果从 $s$ 已经可以到达所有城市，则输出 $0$。

## 说明/提示

样例 1：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/cfa72c5c5f72e8ccb5babda1e509efae921c1e73.png)

例如，您可以添加道路 ( 6, 4 ) , ( 7 , 9 ) , ( 1 , 7 )，以使从 $s = 1$ 可到达所有城市。
样例 2：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/62d78c6df2be4fcc0d6c17ba856e4ad627c47d5f.png)

在此样例中，您可以添加道路（5 , 1），（5 , 2），（5 , 3），（5 , 4）中的任何一条，以使可从 $s = 5$ 到达所有城市。

## 样例 #1

### 输入

```
9 9 1
1 2
1 3
2 3
1 5
5 6
6 1
1 8
9 8
7 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 4 5
1 2
2 3
3 4
4 1

```

### 输出

```
1

```



---

