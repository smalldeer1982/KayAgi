---
title: "Salary Changing"
layout: "post"
diff: 提高+/省选-
pid: CF1251D
tag: ['二分']
---

# Salary Changing

## 题目描述

You are the head of a large enterprise. $ n $ people work at you, and $ n $ is odd (i. e. $ n $ is not divisible by $ 2 $ ).

You have to distribute salaries to your employees. Initially, you have $ s $ dollars for it, and the $ i $ -th employee should get a salary from $ l_i $ to $ r_i $ dollars. You have to distribute salaries in such a way that the median salary is maximum possible.

To find the median of a sequence of odd length, you have to sort it and take the element in the middle position after sorting. For example:

- the median of the sequence $ [5, 1, 10, 17, 6] $ is $ 6 $ ,
- the median of the sequence $ [1, 2, 1] $ is $ 1 $ .

It is guaranteed that you have enough money to pay the minimum salary, i.e $ l_1 + l_2 + \dots + l_n \le s $ .

Note that you don't have to spend all your $ s $ dollars on salaries.

You have to answer $ t $ test cases.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of test cases.

The first line of each query contains two integers $ n $ and $ s $ ( $ 1 \le n < 2 \cdot 10^5 $ , $ 1 \le s \le 2 \cdot 10^{14} $ ) — the number of employees and the amount of money you have. The value $ n $ is not divisible by $ 2 $ .

The following $ n $ lines of each query contain the information about employees. The $ i $ -th line contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le 10^9 $ ).

It is guaranteed that the sum of all $ n $ over all queries does not exceed $ 2 \cdot 10^5 $ .

It is also guaranteed that you have enough money to pay the minimum salary to each employee, i. e. $ \sum\limits_{i=1}^{n} l_i \le s $ .

## 输出格式

For each test case print one integer — the maximum median salary that you can obtain.

## 说明/提示

In the first test case, you can distribute salaries as follows: $ sal_1 = 12, sal_2 = 2, sal_3 = 11 $ ( $ sal_i $ is the salary of the $ i $ -th employee). Then the median salary is $ 11 $ .

In the second test case, you have to pay $ 1337 $ dollars to the only employee.

In the third test case, you can distribute salaries as follows: $ sal_1 = 4, sal_2 = 3, sal_3 = 6, sal_4 = 6, sal_5 = 7 $ . Then the median salary is $ 6 $ .

## 样例 #1

### 输入

```
3
3 26
10 12
1 4
10 11
1 1337
1 1000000000
5 26
4 4
2 4
6 8
5 6
2 7

```

### 输出

```
11
1337
6

```



---

---
title: "Anonymity Is Important"
layout: "post"
diff: 提高+/省选-
pid: CF1641C
tag: ['线段树', '二分']
---

# Anonymity Is Important

## 题目描述

In the work of a doctor, it is important to maintain the anonymity of clients and the results of tests. The test results are sent to everyone personally by email, but people are very impatient and they want to know the results right away.

That's why in the testing lab "De-vitro" doctors came up with an experimental way to report the results. Let's assume that $ n $ people took the tests in the order of the queue. Then the chief doctor Sam can make several statements, in each telling if there is a sick person among the people in the queue from $ l $ -th to $ r $ -th (inclusive), for some values $ l $ and $ r $ .

During the process, Sam will check how well this scheme works and will be interested in whether it is possible to find out the test result of $ i $ -th person from the information he announced. And if it can be done, then is that patient sick or not.

Help Sam to test his scheme.

## 输入格式

The first line contains two integers $ n $ , $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the number of people and the number of queries.

In each of the next $ q $ lines, the description of the query is given. The first number in the line is $ t $ ( $ t = 0 $ or $ t = 1 $ ) — the type of the query.

If $ t = 0 $ , the line contains three more integers $ l, r, x $ ( $ 1 \le l \le r \le n $ , $ x = 0 $ or $ x = 1 $ ). This query means that Sam tells that among the people in the queue from $ l $ -th to $ r $ -th (inclusive):

- there was at least one sick person, if $ x=1 $ ,
- there is no sick people, if $ x=0 $ .

If $ t = 1 $ , the line contains one more integer $ j $ ( $ 1 \le j \le n $ ) — the position of the patient in the queue, for which Sam wants to know the status.

All queries are correct, that means that there always exists an example of the queue of length $ n $ for which all reported results (statements from queries with $ t = 0 $ ) are true.

## 输出格式

After each Sam question (query with $ t = 1 $ ) print:

- "NO", if the patient is definitely not sick,
- "YES", if the patient is definitely sick.
- "N/A", if it is impossible to definitely identify the status of patient having the given information.

## 说明/提示

In the first test for the five first queries:

1. Initially Sam tells that people $ 4 $ , $ 5 $ are not sick.
2. In the next query Sam asks the status of the patient $ 5 $ . From the previous query, we know that the patient is definitely not sick.
3. In the next query Sam asks the status of the patient $ 6 $ . We don't know any information about that patient now.
4. After that Sam tells that there exists a sick patient among $ 4 $ , $ 5 $ , $ 6 $ .
5. In the next query Sam asks the status of the patient $ 6 $ . Now we can tell that this patient is definitely sick.

## 样例 #1

### 输入

```
6 9
0 4 5 0
1 5
1 6
0 4 6 1
1 6
0 2 5 1
0 2 2 0
1 3
1 2
```

### 输出

```
NO
N/A
YES
YES
NO
```



---

---
title: "Mark and Professor Koro"
layout: "post"
diff: 提高+/省选-
pid: CF1705E
tag: ['线段树', '二分', '位运算']
---

# Mark and Professor Koro

## 题目描述

After watching a certain anime before going to sleep, Mark dreams of standing in an old classroom with a blackboard that has a sequence of $ n $ positive integers $ a_1, a_2,\dots,a_n $ on it.

Then, professor Koro comes in. He can perform the following operation:

- select an integer $ x $ that appears at least $ 2 $ times on the board,
- erase those $ 2 $ appearances, and
- write $ x+1 $ on the board.

Professor Koro then asks Mark the question, "what is the maximum possible number that could appear on the board after some operations?"

Mark quickly solves this question, but he is still slower than professor Koro. Thus, professor Koro decides to give Mark additional challenges. He will update the initial sequence of integers $ q $ times. Each time, he will choose positive integers $ k $ and $ l $ , then change $ a_k $ to $ l $ . After each update, he will ask Mark the same question again.

Help Mark answer these questions faster than Professor Koro!

Note that the updates are persistent. Changes made to the sequence $ a $ will apply when processing future updates.

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 2\leq n\leq 2\cdot 10^5 $ , $ 1\leq q\leq 2\cdot 10^5 $ ) — the length of the sequence $ a $ and the number of updates, respectively.

The second line contains $ n $ integers $ a_1,a_2,\dots,a_n $ ( $ 1\leq a_i\leq 2\cdot 10^5 $ )

Then, $ q $ lines follow, each consisting of two integers $ k $ and $ l $ ( $ 1\leq k\leq n $ , $ 1\leq l\leq 2\cdot 10^5 $ ), telling to update $ a_k $ to $ l $ .

## 输出格式

Print $ q $ lines. The $ i $ -th line should consist of a single integer — the answer after the $ i $ -th update.

## 说明/提示

In the first example test, the program must proceed through $ 4 $ updates.

The sequence after the first update is $ [2,3,2,4,5] $ . One sequence of operations that achieves the number $ 6 $ the following.

- Initially, the blackboard has numbers $ [2,3,2,4,5] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,5,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [4,5,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [5,\color{red}{5}] $ .
- Erase two copies of $ 5 $ and write $ 6 $ , yielding $ [\color{red}{6}] $ .

Then, in the second update, the array is changed to $ [2,3,2,4,3] $ . This time, Mark cannot achieve $ 6 $ . However, one sequence that Mark can use to achieve $ 5 $ is shown below.

- Initially, the blackboard has $ [2,3,2,4,3] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,3,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [3,4,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [3,\color{red}{5}] $ .

In the third update, the array is changed to $ [2,3,2,1,3] $ . One way to achieve $ 4 $ is shown below.

- Initially, the blackboard has $ [2,3,2,1,3] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [2,2,1,\color{red}{4}] $ .

## 样例 #1

### 输入

```
5 4
2 2 2 4 5
2 3
5 3
4 1
1 4
```

### 输出

```
6
5
4
5
```

## 样例 #2

### 输入

```
2 1
200000 1
2 200000
```

### 输出

```
200001
```



---

---
title: "Qpwoeirut and Vertices"
layout: "post"
diff: 提高+/省选-
pid: CF1706E
tag: ['线段树', 'Kruskal 重构树', 'ST 表', '整体二分']
---

# Qpwoeirut and Vertices

## 题目描述

You are given a connected undirected graph with $ n $ vertices and $ m $ edges. Vertices of the graph are numbered by integers from $ 1 $ to $ n $ and edges of the graph are numbered by integers from $ 1 $ to $ m $ .

Your task is to answer $ q $ queries, each consisting of two integers $ l $ and $ r $ . The answer to each query is the smallest non-negative integer $ k $ such that the following condition holds:

- For all pairs of integers $ (a, b) $ such that $ l\le a\le b\le r $ , vertices $ a $ and $ b $ are reachable from one another using only the first $ k $ edges (that is, edges $ 1, 2, \ldots, k $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ q $ ( $ 2\le n\le 10^5 $ , $ 1\le m, q\le 2\cdot 10^5 $ ) — the number of vertices, edges, and queries respectively.

Each of the next $ m $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i, v_i\le n $ ) — ends of the $ i $ -th edge.

It is guaranteed that the graph is connected and there are no multiple edges or self-loops.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1\le l\le r\le n $ ) — descriptions of the queries.

It is guaranteed that that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ , and the sum of $ q $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print $ q $ integers — the answers to the queries.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/8251767c792df96adbc7d8ce1ae896aca10bb309.png)Graph from the first test case. The integer near the edge is its number.In the first test case, the graph contains $ 2 $ vertices and a single edge connecting vertices $ 1 $ and $ 2 $ .

In the first query, $ l=1 $ and $ r=1 $ . It is possible to reach any vertex from itself, so the answer to this query is $ 0 $ .

In the second query, $ l=1 $ and $ r=2 $ . Vertices $ 1 $ and $ 2 $ are reachable from one another using only the first edge, through the path $ 1 \longleftrightarrow 2 $ . It is impossible to reach vertex $ 2 $ from vertex $ 1 $ using only the first $ 0 $ edges. So, the answer to this query is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/af65cd675bd4523d08062174925e59fd8900ee43.png)Graph from the second test case. The integer near the edge is its number.In the second test case, the graph contains $ 5 $ vertices and $ 5 $ edges.

In the first query, $ l=1 $ and $ r=4 $ . It is enough to use the first $ 3 $ edges to satisfy the condition from the statement:

- Vertices $ 1 $ and $ 2 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 $ (edge $ 1 $ ).
- Vertices $ 1 $ and $ 3 $ are reachable from one another through the path $ 1 \longleftrightarrow 3 $ (edge $ 2 $ ).
- Vertices $ 1 $ and $ 4 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 1 $ and $ 3 $ ).
- Vertices $ 2 $ and $ 3 $ are reachable from one another through the path $ 2 \longleftrightarrow 1 \longleftrightarrow 3 $ (edges $ 1 $ and $ 2 $ ).
- Vertices $ 2 $ and $ 4 $ are reachable from one another through the path $ 2 \longleftrightarrow 4 $ (edge $ 3 $ ).
- Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ).

If we use less than $ 3 $ of the first edges, then the condition won't be satisfied. For example, it is impossible to reach vertex $ 4 $ from vertex $ 1 $ using only the first $ 2 $ edges. So, the answer to this query is $ 3 $ .

In the second query, $ l=3 $ and $ r=4 $ . Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ). If we use any fewer of the first edges, nodes $ 3 $ and $ 4 $ will not be reachable from one another.

## 样例 #1

### 输入

```
3
2 1 2
1 2
1 1
1 2
5 5 5
1 2
1 3
2 4
3 4
3 5
1 4
3 4
2 2
2 5
3 5
3 2 1
1 3
2 3
1 3
```

### 输出

```
0 1 
3 3 0 5 5 
2
```



---

---
title: "Rain"
layout: "post"
diff: 提高+/省选-
pid: CF1710B
tag: ['二分', '差分']
---

# Rain

## 题目描述

You are the owner of a harvesting field which can be modeled as an infinite line, whose positions are identified by integers.

It will rain for the next $ n $ days. On the $ i $ -th day, the rain will be centered at position $ x_i $ and it will have intensity $ p_i $ . Due to these rains, some rainfall will accumulate; let $ a_j $ be the amount of rainfall accumulated at integer position $ j $ . Initially $ a_j $ is $ 0 $ , and it will increase by $ \max(0,p_i-|x_i-j|) $ after the $ i $ -th day's rain.

A flood will hit your field if, at any moment, there is a position $ j $ with accumulated rainfall $ a_j>m $ .

You can use a magical spell to erase exactly one day's rain, i.e., setting $ p_i=0 $ . For each $ i $ from $ 1 $ to $ n $ , check whether in case of erasing the $ i $ -th day's rain there is no flood.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 1 \leq m \leq 10^9 $ ) — the number of rainy days and the maximal accumulated rainfall with no flood occurring.

Then $ n $ lines follow. The $ i $ -th of these lines contains two integers $ x_i $ and $ p_i $ ( $ 1 \leq x_i,p_i \leq 10^9 $ ) — the position and intensity of the $ i $ -th day's rain.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a binary string $ s $ length of $ n $ . The $ i $ -th character of $ s $ is 1 if after erasing the $ i $ -th day's rain there is no flood, while it is 0, if after erasing the $ i $ -th day's rain the flood still happens.

## 说明/提示

In the first test case, if we do not use the spell, the accumulated rainfall distribution will be like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/40bd9aae46d3e796ba1ad418de0578aa41ab0c1c.png)If we erase the third day's rain, the flood is avoided and the accumulated rainfall distribution looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/d422db8867ffc7f0ea195742c50ffb3752e7d523.png)In the second test case, since initially the flood will not happen, we can erase any day's rain.

In the third test case, there is no way to avoid the flood.

## 样例 #1

### 输入

```
4
3 6
1 5
5 5
3 4
2 3
1 3
5 2
2 5
1 6
10 6
6 12
4 5
1 6
12 5
5 5
9 7
8 3
```

### 输出

```
001
11
00
100110
```



---

---
title: "Disks"
layout: "post"
diff: 提高+/省选-
pid: CF1949I
tag: ['二分图']
---

# Disks

## 题目描述

# 圆盘


你在平面上有 $ n $ 个圆盘。每个圆盘的中心具有整数坐标，每个圆盘的半径为正整数。没有两个圆盘在一个正面积的区域重叠，但圆盘之间可能相切。

你的任务是确定是否可以改变圆盘的半径，使得：

- 原来相切的圆盘仍然相切。
- 没有两个圆盘在一个正面积的区域重叠。
- 所有半径的总和严格减小。

新的半径可以是任意正实数。不能改变圆盘的中心。

## 输入格式

第一行包含一个整数 $ n $ （ $ 1\le n \le 1000 $ ）— 圆盘的数量。

接下来的 $ n $ 行，每行包含三个整数。第 $ i $ 行包含 $ x_i $ ， $ y_i $ （ $ -10^9 \leq x_i, y_i \le 10^9 $ ），以及 $ r_i $ （ $ 1 \leq r_i \le 10^9 $ ）— 第 $ i $ 个圆盘的中心坐标和半径。

## 输出格式

如果可以按照要求改变半径，则打印 $ \texttt{YES} $ 。否则，打印 $ \texttt{NO} $ 。

## 样例 #1

### 样例输入 #1

```
5
0 2 1
0 0 1
4 -3 4
11 0 3
11 5 2
```

### 样例输出 #1

```
YES
```

## 样例 #2

### 样例输入 #2

```
4
2 2 2
7 2 3
7 7 2
2 7 3
```

### 样例输出 #2

```
NO
```

## 说明/提示

在第一个样例中，可以将第一个和第三个圆盘的半径减小 $ 0.5 $ ，将第二个圆盘的半径增加 $ 0.5 $ 。这样，所有半径的总和减小了 $ 0.5 $ 。改变半径前后的情况如下图所示。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1949I/1f564e55d56b152b57e25e4b9913f6abfe12e4f8.png) 第一个样例（左）和改变圆盘半径的有效方法（右）。在第二个样例中，如下图所示，无法按照要求改变圆盘的半径。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1949I/160a9b50ca0114a94aa27312025cf229be0abcc8.png) 第二个样例。

## 样例 #1

### 输入

```
5
0 2 1
0 0 1
4 -3 4
11 0 3
11 5 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
2 2 2
7 2 3
7 7 2
2 7 3
```

### 输出

```
NO
```



---

---
title: "Coloring Game"
layout: "post"
diff: 提高+/省选-
pid: CF1991E
tag: ['二分图']
---

# Coloring Game

## 题目描述

This is an interactive problem.

Consider an undirected connected graph consisting of $ n $ vertices and $ m $ edges. Each vertex can be colored with one of three colors: $ 1 $ , $ 2 $ , or $ 3 $ . Initially, all vertices are uncolored.

Alice and Bob are playing a game consisting of $ n $ rounds. In each round, the following two-step process happens:

1. Alice chooses two different colors.
2. Bob chooses an uncolored vertex and colors it with one of the two colors chosen by Alice.

Alice wins if there exists an edge connecting two vertices of the same color. Otherwise, Bob wins.

You are given the graph. Your task is to decide which player you wish to play as and win the game.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 1 \le n \le 10^4 $ , $ n - 1 \le m \le \min(\frac{n \cdot (n - 1)}{2}, 10^4) $ ) — the number of vertices and the number of edges in the graph, respectively.

Each of the next $ m $ lines of each test case contains two integers $ u_i $ , $ v_i $ ( $ 1 \le u_i, v_i \le n $ ) — the edges of the graph. It is guaranteed that the graph is connected and there are no multiple edges or self-loops.

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, you need to output a single line containing either "Alice" or "Bob", representing the player you choose.

Then for each of the following $ n $ rounds, the following two-step process happens:

1. Alice (either you or the interactor) will output two integers $ a $ and $ b $ ( $ 1 \le a, b \le 3 $ , $ a \neq b $ ) — the colors chosen by Alice.
2. Bob (either you or the interactor) will output two integers $ i $ and $ c $ ( $ 1 \le i \le n $ , $ c = a $ or $ c = b $ ) — the vertex and the color chosen by Bob. Vertex $ i $ must be a previously uncolored vertex.

If any of your outputs are invalid, the jury will output "-1" and you will receive a Wrong Answer verdict.

At the end of all $ n $ turns, if you have lost the game, the jury will output "-1" and you will receive a Wrong Answer verdict.

If your program has received a $ -1 $ instead of a valid value, it must terminate immediately. Otherwise, you may receive an arbitrary verdict because your solution might be reading from a closed stream.

Note that if you are playing as Alice, and there already exists an edge connected two vertices of the same color, the interactor will not terminate early and you will keep playing all $ n $ rounds.

After outputting, do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

In this problem, hacks are disabled.

## 说明/提示

Note that the sample test cases are example games and do not necessarily represent the optimal strategy for both players.

In the first test case, you choose to play as Alice.

1. Alice chooses two colors: $ 3 $ and $ 1 $ . Bob chooses vertex $ 3 $ and colors it with color $ 1 $ .
2. Alice chooses two colors: $ 1 $ and $ 2 $ . Bob chooses vertex $ 2 $ and colors it with color $ 2 $ .
3. Alice chooses two colors: $ 2 $ and $ 1 $ . Bob chooses vertex $ 1 $ and colors it with color $ 1 $ .

Alice wins because the edge $ (3, 1) $ connects two vertices of the same color.

In the second test case, you choose to play as Bob.

1. Alice chooses two colors: $ 2 $ and $ 3 $ . Bob chooses vertex $ 1 $ and colors it with color $ 2 $ .
2. Alice chooses two colors: $ 1 $ and $ 2 $ . Bob chooses vertex $ 2 $ and colors it with color $ 1 $ .
3. Alice chooses two colors: $ 2 $ and $ 1 $ . Bob chooses vertex $ 4 $ and colors it with color $ 1 $ .
4. Alice chooses two colors: $ 3 $ and $ 1 $ . Bob chooses vertex $ 3 $ and colors it with color $ 3 $ .

Bob wins because there are no edges with vertices of the same color.

## 样例 #1

### 输入

```
2
3 3
1 2
2 3
3 1


3 1

2 2

1 1
4 4
1 2
2 3
3 4
4 1

2 3

1 2

2 1

3 1
```

### 输出

```
Alice
3 1

1 2

2 1






Bob

1 2

2 1

4 1

3 3
```



---

---
title: "Med-imize"
layout: "post"
diff: 提高+/省选-
pid: CF1993D
tag: ['动态规划 DP', '二分']
---

# Med-imize

## 题目描述

Given two positive integers $ n $ and $ k $ , and another array $ a $ of $ n $ integers.

In one operation, you can select any subarray of size $ k $ of $ a $ , then remove it from the array without changing the order of other elements. More formally, let $ (l, r) $ be an operation on subarray $ a_l, a_{l+1}, \ldots, a_r $ such that $ r-l+1=k $ , then performing this operation means replacing $ a $ with $ [a_1, \ldots, a_{l-1}, a_{r+1}, \ldots, a_n] $ .

For example, if $ a=[1,2,3,4,5] $ and we perform operation $ (3,5) $ on this array, it will become $ a=[1,2] $ . Moreover, operation $ (2, 4) $ results in $ a=[1,5] $ , and operation $ (1,3) $ results in $ a=[4,5] $ .

You have to repeat the operation while the length of $ a $ is greater than $ k $ (which means $ |a| \gt k $ ). What is the largest possible median $ ^\dagger $ of all remaining elements of the array $ a $ after the process?

 $ ^\dagger $ The median of an array of length $ n $ is the element whose index is $ \left \lfloor (n+1)/2 \right \rfloor $ after we sort the elements in non-decreasing order. For example: $ median([2,1,5,4,3]) = 3 $ , $ median([5]) = 5 $ , and $ median([6,8,2,4]) = 4 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the largest median possible after performing the operations.

## 说明/提示

In the first test case, you can select a subarray $ (l, r) $ which can be either $ (1, 3) $ or $ (2, 4) $ . Thus, two obtainable final arrays are $ [3] $ and $ [2] $ . The former one has the larger median ( $ 3 > 2 $ ) so the answer is $ 3 $ .

In the second test case, three obtainable final arrays are $ [6, 4] $ , $ [3, 4] $ , and $ [3, 2] $ . Their medians are $ 4 $ , $ 3 $ , and $ 2 $ respectively. The answer is $ 4 $ .

In the third test case, only one element is left in the final array and it can be any element of the initial array. The largest one among them is $ 9 $ , so the answer is $ 9 $ .

## 样例 #1

### 输入

```
5
4 3
3 9 9 2
5 3
3 2 5 6 4
7 1
5 9 2 6 5 4 6
8 2
7 1 2 6 8 3 4 5
4 5
3 4 5 6
```

### 输出

```
3
4
9
6
4
```



---

---
title: "Level Up"
layout: "post"
diff: 提高+/省选-
pid: CF1997E
tag: ['线段树', '二分', '树状数组']
---

# Level Up

## 题目描述

Monocarp正在玩一款电脑游戏。他从等级 $ 1 $ 开始。他将依次与 $ n $ 只怪物战斗，这些怪物的等级从 $ 1 $ 到 $ n $ 不等。

对于按顺序给出的每个怪物，Monocarp的遭遇如下：

- 如果Monocarp的等级高于怪物的等级，则怪物会逃跑；
- 否则，Monocarp会与怪物战斗。

在每与第 $ k $ 个怪物战斗（逃跑的怪物不计算在内）后，Monocarp的等级会增加 $ 1 $ 。因此，他在与 $ k $ 个怪物战斗后等级变为 $ 2 $ ，在与 $ 2k $ 个怪物战斗后等级变为 $ 3 $ ，以此类推。

你需要处理 $ q $ 个查询，每个查询的格式如下：

- $ i~x $ ：如果参数 $ k $ 等于 $ x $ ，Monocarp是否会与第 $ i $ 个怪物战斗？

## 输入格式

第一行包含两个整数 $ n $ 和 $ q $ （ $ 1 \le n, q \le 2 \cdot 10^5 $ ） — 怪物的数量和查询的数量。

第二行包含 $ n $ 个整数 $ a_1, a_2, \dots, a_n $ （ $ 1 \le a_i \le 2 \cdot 10^5 $ ） — 每个怪物的等级。

接下来的 $ q $ 行，每行包含两个整数 $ i $ 和 $ x $ （ $ 1 \le i, x \le n $ ） — 查询中指定的怪物索引和需要升级的战斗次数。

## 输出格式

对于每个查询，如果Monocarp会与第 $ i $ 个怪物战斗，则输出 "YES" ，否则输出 "NO" 。

## 样例 #1

### 输入

```
4 16
2 1 2 1
1 1
2 1
3 1
4 1
1 2
2 2
3 2
4 2
1 3
2 3
3 3
4 3
1 4
2 4
3 4
4 4
```

### 输出

```
YES
NO
YES
NO
YES
YES
YES
NO
YES
YES
YES
NO
YES
YES
YES
YES
```

## 样例 #2

### 输入

```
7 15
1 1 2 1 1 1 1
5 3
2 2
2 2
1 6
5 1
5 5
7 7
3 5
7 4
4 3
2 5
1 2
5 6
4 1
6 1
```

### 输出

```
NO
YES
YES
YES
NO
YES
YES
YES
NO
NO
YES
YES
YES
NO
NO
```



---

---
title: "Fairy"
layout: "post"
diff: 提高+/省选-
pid: CF19E
tag: ['二分图', '最近公共祖先 LCA', '差分']
---

# Fairy

## 题目描述

Once upon a time there lived a good fairy A. One day a fine young man B came to her and asked to predict his future. The fairy looked into her magic ball and said that soon the fine young man will meet the most beautiful princess ever and will marry her. Then she drew on a sheet of paper $ n $ points and joined some of them with segments, each of the segments starts in some point and ends in some other point. Having drawn that picture, she asked the young man to erase one of the segments from the sheet. Then she tries to colour each point red or blue so, that there is no segment having points of the same colour as its ends. If she manages to do so, the prediction will come true. B wants to meet the most beautiful princess, that's why he asks you to help him. Find all the segments that will help him to meet the princess.

## 输入格式

The first input line contains two integer numbers: $ n $ — amount of the drawn points and $ m $ — amount of the drawn segments ( $ 1<=n<=10^{4},0<=m<=10^{4} $ ). The following $ m $ lines contain the descriptions of the segments. Each description contains two different space-separated integer numbers $ v $ , $ u $ ( $ 1<=v<=n,1<=u<=n $ ) — indexes of the points, joined by this segment. No segment is met in the description twice.

## 输出格式

In the first line output number $ k $ — amount of the segments in the answer. In the second line output $ k $ space-separated numbers — indexes of these segments in ascending order. Each index should be output only once. Segments are numbered from 1 in the input order.

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4

```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
4 5
1 2
2 3
3 4
4 1
1 3

```

### 输出

```
1
5 
```



---

---
title: "Call During the Journey"
layout: "post"
diff: 提高+/省选-
pid: CF2000G
tag: ['二分', '最短路']
---

# Call During the Journey

## 题目描述

你所居住的城市由 $n$ 个交叉路口和连接几对交叉路口的 $m$ 条街道组成。您可以在每条街道上向任一方向前进。没有两条街道连接同一对交叉路口，也没有一条街道只连接一个交叉路口。您可以从任何一个交叉路口到达另一个交叉路口，但可能会经过其他一些交叉路口。

每分钟，你可以在路口 $u_i$ 登上一辆公交车，然后行驶 $l_{i1}$ 分钟到达路口 $v_i$ 。相反，您可以在 $l_{i1}$ 分钟内从路口 $v_i$ 到达路口 $u_i$ 。您只能在交叉路口上下车。只有当您正在某交叉路口时，才能在该交叉路口登上公共汽车。

您也可以沿着每条街道步行，这需要 $l_{i2} \gt l_{i1}$ 分钟。

您可以在十字路口停车。

您住在十字路口编号 $1$ 处。今天您在 $0$ 点起床，在路口编号 $n$ 处有一个重要活动安排，您必须在 $t_0$ 点之前到达。你还计划打一个电话，通话时间为 $t_1$ 至 $t_2$ 分钟（ $t_1 \lt t_2 \lt t_0$ ）。

通话期间，您不能乘坐公共汽车，但可以在任何街道上行走、停靠在站点处或待在家里。您可以在 $t_1$ 分钟下车，在 $t_2$ 分钟再次上车。

由于您希望获得充足的睡眠，您开始好奇您可以多晚离开家，以便有时间讲电话，同时还不会在活动中迟到？

## 输入格式

第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ ) - 测试用例数。下面是测试用例的说明。

每个测试用例的第一行包含两个整数 $n$ , $m$ ( $2 \le n \le 10^5, 1 \le m \le 10^5$ ) - 城市中十字路口和街道的数量。

每个测试用例的第二行分别包含三个整数 $t_0$ , $t_1$ , $t_2$ ( $1 \lt t_1 \lt t_2 \lt t_0 \le 10^9$ ) - 事件开始时间、电话开始时间和结束时间。

每个测试用例接下来的 $m$ 行包含对街道的描述。

第 $i$ 行包含四个整数 $u_i$ 、 $v_i$ 、 $l_{i1}$ 、 $l_{i2}$ （ $1 \le u_i, v_i \le n$ 、 $u_i \neq v_i$ 、 $1 \le l_{i1} \lt l_{i2} \le 10^9$ ）--即由第 $i$ 条街道连接的十字路口的编号，以及沿街乘坐公交车和步行所需的时间。保证没有两条街道连接同一对交叉路口，并且可以从任何一个交叉路口到达另一个交叉路口。

保证所有测试用例中 $n$ 的值之和不超过 $10^5$ 。同时保证所有测试用例中 $m$ 的值之和不超过 $10^5$ 。

## 输出格式

对于每个测试用例，输出一个整数--您离开家的最晚时间，以便有时间讲电话而不会迟到。如果您不能按时到达活动地点，则输出 `-1`。

## 样例 #1

### 输入

```
7
5 5
100 20 80
1 5 30 100
1 2 20 50
2 3 20 50
3 4 20 50
4 5 20 50
2 1
100 50 60
1 2 55 110
4 4
100 40 60
1 2 30 100
2 4 30 100
1 3 20 50
3 4 20 50
3 3
100 80 90
1 2 1 10
2 3 10 50
1 3 20 21
3 2
58 55 57
2 1 1 3
2 3 3 4
2 1
12 9 10
2 1 6 10
5 5
8 5 6
2 1 1 8
2 3 4 8
4 2 2 4
5 3 3 4
4 5 2 6
```

### 输出

```
0
-1
60
80
53
3
2
```



---

---
title: "Ksyusha and the Loaded Set"
layout: "post"
diff: 提高+/省选-
pid: CF2000H
tag: ['线段树', '二分']
---

# Ksyusha and the Loaded Set

## 题目描述

Ksyusha 决定创办一家游戏开发公司。为了在竞争中脱颖而出并取得成功，她决定编写一个属于自己的游戏引擎。这个引擎需要支持一个初始包含 $n$ 个不同整数 $a_1, a_2, \ldots, a_n$ 的集合。

接下来，这个集合将依次进行 $m$ 次操作。可进行的操作类型如下：

- 向集合中插入一个元素 $x$；
- 从集合中移除一个元素 $x$；
- 查询集合的 $k$-负载。

集合的 $k$-负载定义为最小的正整数 $d$，使得整数 $d, d + 1, \ldots, d + (k - 1)$ 全都不在这个集合中。例如，集合 $\{3, 4, 6, 11\}$ 的 $3$-负载是 $7$，因为数字 $7, 8, 9$ 不在集合里，并且没有更小的值满足这个条件。

由于 Ksyusha 忙于管理工作，所以需要你来帮忙实现这个引擎的操作支持。

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^4$），表示有 $t$ 组测试用例。

接下来的行描述每个测试用例。

每个测试用例的第一行输入一个整数 $n$（$1 \le n \le 2 \cdot 10^5$），表示集合的初始大小。

接着一行输入 $n$ 个严格递增的整数 $a_1, a_2, \ldots, a_n$（$1 \le a_1 < a_2 < \ldots < a_n \le 2 \cdot 10^6$），表示集合的初始状态。

然后一行输入一个整数 $m$（$1 \le m \le 2 \cdot 10^5$），表示操作的数量。

接下来的 $m$ 行描述这些操作，格式如下：

- `+ x`（插入元素 $x$，$1 \le x \le 2 \cdot 10^6$，保证 $x$ 不在集合中）；
- `- x`（删除元素 $x$，$1 \le x \le 2 \cdot 10^6$，保证 $x$ 在集合中）；
- `? k`（查询 $k$-负载，$1 \le k \le 2 \cdot 10^6$）。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$，$m$ 的总和也不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出所有 `?` 类型操作的答案。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
1 2 5 905 2000000
15
- 2
? 2
? 1
- 1
? 1
+ 4
+ 2
? 2
+ 6
- 4
+ 7
? 2
? 3
? 4
? 2000000
5
3 4 5 6 8
9
? 5
- 5
? 5
+ 1
? 2
- 6
- 8
+ 6
? 5
5
6 7 8 9 10
10
? 5
- 6
? 4
- 10
+ 5
- 8
+ 3
+ 2
- 3
+ 10
```

### 输出

```
2 2 1 6 3 8 8 2000001 
9 9 9 7 
1 1
```



---

---
title: "Eri and Expanded Sets"
layout: "post"
diff: 提高+/省选-
pid: CF2006C
tag: ['数学', '二分', '数论', 'ST 表']
---

# Eri and Expanded Sets

## 题目描述

### 题目翻译


------------

有一个包含合法的数的集合。为了将这个集合扩展的尽可能大，Eri可以在集合中选择两个整数 $x \neq y $ ，它们的平均数 $ \frac{x+y}2 $ 是一个合法的不在集合中的数，然后把 $ \frac{x+y}2 $ 置入这个集合。整数 $ x $ 和 $ y $ 仍在这个集合中。

如果我们称这个集合为连续集，那么，当集合内的元素被排序后，相邻的两个元素之间极差为 $1$ 。例如, 集合 $ \{2\} $ , $ \{2, 5, 4, 3\} $ , $ \{5, 6, 8, 7\} $ 是连续集, 但 $ \{2, 4, 5, 6\} $ , $ \{9, 7\} $ 不是。

Eri 喜欢连续集. 假使我们有一序列 $ b $ ,  Eri 把 $ b $ 中所有的元素置入集合。 如果经过上述若干次操作后，该集合转化为了一个连续集，这个序列 $ b $ 就会被我们称作是“闪耀的”。

需要注意的是，如果一个相同的整数多次出现在序列中，我们只会把它加入集合一次，集合总是只包含合法的数。

Eri 有一个序列 $ a $ 包含 $ n $ 个合法的数。请帮他算出整数数对 $ (l,r) $ 的数量$( 1 \leq l \leq r \leq n )$ ，令子序列 $ a_l, a_{l+1}, \ldots, a_r $ 是闪耀的。

## 输入格式

每一个测试点包含多组测试数据。第一行只有一个整数  $ t $ $(1 \leq t \leq 10^4)$ 表示测试数据的组数。   
对于每组数据，第一行包含一个整数 $ n $ $( 1 \leq n \leq 4 \cdot 10^5 )$ 表示序列 $ a $ 的长度。

第二行有 $ n $ 个整数 $ a_1, a_2, \ldots a_n $  $( 1 \leq a_i \leq 10^9 )$ 表示序列中的元素 $ a_i $ 。  

保证 $Σn \leq 4 \cdot 10^5$ 。

## 输出格式

对于每组测试数据，输出一行一个整数，表示“闪耀的”子序列的数量。
#### 样例解释
在第一组测试数据中，序列 $ a = [2, 2] $ 有 $ 3 $ 个子序列：$ [2] $ , $ [2] $ ,  $ [2, 2] $ 。这些子序列构造的集合中只包含一个整数 $ 2 $ ，因此它总是连续集。 所有的子序列都是闪耀的，所以答案是 $ 3 $ .

在第二组测试数据中，注意到子序列 $ [3, 6, 10] $ . 我们可以进行下列操作：

$\{3,6,10\} \xrightarrow{x=6,y=10} \{3,6,8,10\} \xrightarrow{x=6,y=8} \{3,6,7,8,10\} \xrightarrow{x=3,y=7} \{3,5,6,7,8,10\} $ $     $ $ \xrightarrow{x=3,y=5} \{3,4,5,6,7,8,10\} \xrightarrow{x=8,y=10} \{3,4,5,6,7,8,9,10\} $   
   
$ \\{3,4,5,6,7,8,9,10\\} $  是一个连续集，所以子序列 $ \[3, 6, 10\]$ 是闪耀的。

## 样例 #1

### 输入

```
6
2
2 2
6
1 3 6 10 15 21
5
6 30 18 36 9
1
1000000000
6
1 1 4 5 1 4
12
70 130 90 90 90 108 612 500 451 171 193 193
```

### 输出

```
3
18
5
1
18
53
```



---

---
title: "Best Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF2026E
tag: ['网络流', '二分图']
---

# Best Subsequence

## 题目描述

Given an integer array $ a $ of size $ n $ .

Let's define the value of the array as its size minus the number of set bits in the bitwise OR of all elements of the array.

For example, for the array $ [1, 0, 1, 2] $ , the bitwise OR is $ 3 $ (which contains $ 2 $ set bits), and the value of the array is $ 4-2=2 $ .

Your task is to calculate the maximum possible value of some subsequence of the given array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < 2^{60} $ ).

## 输出格式

For each test case, print the maximum possible value of some subsequence of the given array.

## 样例 #1

### 输入

```
4
3
0 0 0
4
1 0 1 2
1
5
8
7 1 48 14 13 8 7 6
```

### 输出

```
3
2
0
3
```



---

---
title: "Make It Equal"
layout: "post"
diff: 提高+/省选-
pid: CF2038B
tag: ['二分']
---

# Make It Equal

## 题目描述

给定一个长度为 $n$ 的整数数列 $a$，下标从 $1$ 到 $n$。

你可以进行任意次（可以为 $0$ 次）以下操作：选择一个满足 $1\le i\le n$ 的 $i$，使 $a_i$ 减少 $2$，$a_{(i\mod n)+1}$ 增加 $1$。

现询问是否有一种操作方案，使得 $a_1=a_2=\dots=a_n=p$ 且 $p\ge 0$，若有，输出最少操作次数，否则输出 $-1$。

## 输入格式

本题多测。

第一行一个整数 $t(1\le t\le 10^4)$，代表测试样例组数。

对于每组测试样例：

第一行一个整数 $n(2\le n\le 2\times 10^5)$。

第二行 $n$ 个整数 $a_1,a_2,\dots,a_n(1\le a_i\le 10^9)$。

保证 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组测试样例，输出一行一个整数，代表最少操作次数，若不存在操作方案，输出 $-1$。

Translated by @[ARIS2_0](https://www.luogu.com.cn/user/1340759)

## 样例 #1

### 输入

```
3
2
1 1
3
1 3 2
4
2 1 2 6
```

### 输出

```
0
-1
3
```



---

---
title: "Adventurers"
layout: "post"
diff: 提高+/省选-
pid: CF2046C
tag: ['线段树', '二分', '树状数组', '扫描线']
---

# Adventurers

## 题目描述

Once, four Roman merchants met in a Roman mansion to discuss their trading plans. They faced the following problem: they traded the same type of goods, and if they traded in the same city, they would inevitably incur losses. They decided to divide up the cities between them where they would trade.

The map of Rome can be represented in this problem as a plane with certain points marked — the cities of the Roman Empire.

The merchants decided to choose a certain dividing point $ (x_0, y_0) $ . Then, in a city with coordinates $ (x_i, y_i) $ ,

- the first merchant sells goods if $ x_0 \le x_i $ and $ y_0 \le y_i $ ;
- the second merchant sells goods if $ x_0 > x_i $ and $ y_0 \le y_i $ ;
- the third merchant sells goods if $ x_0 \le x_i $ and $ y_0 > y_i $ ;
- the fourth merchant sells goods if $ x_0 > x_i $ and $ y_0 > y_i $ .

The merchants want to choose $ (x_0, y_0) $ in such a way as to maximize the smallest number of cities that any of them gets (i. e., as fair as possible). Please find such a point for them.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^5 $ ) — the number of cities on the map.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^9 \le x_i, y_i \le 10^9 $ ) — the coordinates of the cities.

Note that some points may coincide. This is because some cities may be so close that they cannot be distinguished on the map at the given scale.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, in the first line, print a single integer $ k $ ( $ 0 \le k \le \frac{n}{4} $ ) — the maximum possible number of cities that each merchant can get at a minimum.

In the second line, print two integers $ x_0 $ and $ y_0 $ ( $ |x_0|, |y_0| \le 10^9 $ ) — the coordinates of the dividing point. If there are multiple suitable points, print any of them.

## 样例 #1

### 输入

```
4
4
1 1
1 2
2 1
2 2
4
0 0
0 0
0 0
0 0
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
7
1 1
1 2
1 3
1 4
2 1
3 1
4 1
```

### 输出

```
1
2 2
0
0 0
2
1 0
0
0 0
```



---

---
title: "Broken Queries"
layout: "post"
diff: 提高+/省选-
pid: CF2049E
tag: ['二分', '分类讨论']
---

# Broken Queries

## 题目描述

你是一位魔法师，你的作品被一条龙摧毁了，于是你决心用一台神奇的范围追踪器来追捕这条龙。然而，那条龙似乎在捉弄你。

这是一个交互式问题。

有一个隐藏的二进制数组 $a$，长度为 $n$（$n$ 是 2 的幂），以及一个隐藏的整数 $k$（$2 \le k \le n - 1$）。数组 $a$ 中仅有一个元素是 1，其余元素都是 0。对于两个整数 $l$ 和 $r$（$1 \le l \le r \le n$），定义区间和为 $s(l, r) = a_l + a_{l+1} + \cdots + a_r$。

你持有一个魔法装置，它能接收区间并返回区间和，但如果区间的长度至少是 $k$，则装置返回结果的相反值。具体来说，每次你可以提交一对整数 $[l, r]$ 进行查询（$1 \le l \le r \le n$），装置会按照下述规则返回 0 或 1：

- 如果 $r - l + 1 < k$，则返回 $s(l, r)$ 的实际值。
- 如果 $r - l + 1 \ge k$，则返回 $1 - s(l, r)$。

你需要用不超过 33 次查询找到隐藏的 $k$。

请注意，这个装置对于不同的测试用例始终固定不变，即隐藏的数组 $a$ 和整数 $k$ 在游戏开始前就已经确定，并在整个过程中不变。

## 输入格式

每个测试包含多个测试用例。第一行输入一个整数 $t$（$1 \le t \le 500$）表示测试用例的数量。接下来就是每个测试用例的详细描述。

每个测试用例的第一行包含一个正整数 $n$（$4 \le n \le 2^{30}$），表示隐藏数组的长度。保证 $n$ 是 2 的幂，即 $n = 2^m$，这里 $m$ 是非负整数。

你可以通过输出一行形如 “`? l r`” 的指令进行查询，这里的 $1 \le l \le r \le n$。之后，你会读取一个整数：0 或 1，来获取结果。

如果要输出答案 $k$，则请输出 “`! k`”。输出答案后，程序将进入下一个测试用例。

每次输出查询时，请确保在最后输出换行符并刷新输出，否则可能会因此超时。

如果在任何一步中收到 $-1$ 作为反馈，你的程序必须立即终止，这意味着你的查询有误或已犯下其他错误，未能及时退出可能导致随意判定。

## 说明/提示

在第一个测试用例中，给出隐藏整数 $k = 6$ 且数组中唯一的 1 位于索引 6 上，因此数组 $a = [0, 0, 0, 0, 0, 1, 0, 0]$。

- 对于查询 (3, 5)，因为 $5 - 3 + 1 = 3 < k$，装置返回实际结果。因为 6 不在区间 $\[3, 5\]$ 内，返回 0。
- 对于查询 (1, 8)，因为 $8 - 1 + 1 = 8 \ge k$，装置返回相反结果，返回 0。
- 对于查询 (4, 8)，因为 $8 - 4 + 1 = 5 < k$，装置返回实际结果，返回 1。
- 对于查询 (3, 8)，因为 $8 - 3 + 1 = 6 \ge k$，装置返回相反结果，返回 0。

示例解决方案输出 $k=6$，这也是正确的答案。

在第二个测试用例中，$k = 2$，数组中的 1 位于索引 3，因此 $a = [0, 0, 1, 0]$。

注意，示例解决方案在某些情况下可能无法充分确定 $k$，这仅仅是作为示例来提供参考。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
8

0

0

1

0

4

1

0
```

### 输出

```
? 3 5

? 1 8

? 4 8

? 3 8

! 6

? 3 3

? 3 4

! 2
```



---

---
title: "Canteen (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2089B2
tag: ['贪心', '二分', '单调队列']
---

# Canteen (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本的区别在于此版本中，对 $$$k$$$ 没有额外限制。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $$$t$$$（$$1 \le t \le 2 \cdot 10^4$$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $$$n$$$、$$k$$（$$1 \le n \le 2 \cdot 10^5$$，$$0 \le k \le 2 \cdot 10^{14}$$）。

每个测试用例的第二行包含 $$$n$$$ 个整数 $$$a_0, a_1, \ldots, a_{n - 1}$$$（$$1 \le a_i \le 10^9$$）。

每个测试用例的第三行包含 $$$n$$$ 个整数 $$$b_0, b_1, \ldots, b_{n - 1}$$$（$$1 \le b_i \le 10^9$$）。

保证所有测试用例的 $$$n$$$ 之和不超过 $$$2 \cdot 10^5$$$。同时保证每个测试用例中 $$$a$$$ 的总和不超过 $$$b$$$ 的总和，且 $$$k$$$ 不超过 $$$a$$$ 的总和。

## 输出格式

对于每个测试用例，输出在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。


## 说明/提示

在第五个测试用例中，$$$a$$$ 的所有元素在恰好 $$$6$$$ 次修改后变为 $$$0$$$。

在第六个测试用例中，Ecrade 可以对 $$$a_3$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[1,2,2,4]$$$：
- 第一轮操作后，$$a=[3,0,0,0]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,1,0,0]$$。

在第七个测试用例中，Ecrade 可以对 $$$a_4$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[2,1,1,1]$$$：
- 第一轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,1,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,1,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3 0
1 1 4
5 1 4
4 0
1 2 3 4
4 3 2 1
4 0
2 1 1 2
1 2 2 1
8 0
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
3 6
1 1 4
5 1 4
4 1
1 2 3 4
4 3 2 1
4 1
2 1 1 2
1 2 2 1
4 2
2 1 1 2
1 2 2 1
```

### 输出

```
1
4
4
8
0
2
2
1
```



---

---
title: "La Vaca Saturno Saturnita"
layout: "post"
diff: 提高+/省选-
pid: CF2094H
tag: ['二分', '数论', '根号分治']
---

# La Vaca Saturno Saturnita

## 题目描述

Saturnita 的情绪取决于一个长度为 $n$ 的数组 $a$（只有他知道其含义）以及一个函数 $f(k, a, l, r)$（只有他知道如何计算）。以下是该函数的伪代码实现：

```
function f(k, a, l, r):
   ans := 0
   for i from l to r (inclusive):
      while k is divisible by a[i]:
         k := k/a[i]
      ans := ans + k
   return ans
```

给定 $q$ 个查询，每个查询包含整数 $k$、$l$ 和 $r$。对于每个查询，请输出 $f(k,a,l,r)$ 的值。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $q$（$1 \leq n \leq 10^5$，$1 \leq q \leq 5 \cdot 10^4$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$2 \leq a_i \leq 10^5$）。

接下来的 $q$ 行，每行包含三个整数 $k$、$l$ 和 $r$（$1 \leq k \leq 10^5$，$1 \leq l \leq r \leq n$）。

保证所有测试用例的 $n$ 之和不超过 $10^5$，且所有测试用例的 $q$ 之和不超过 $5 \cdot 10^4$。

## 输出格式

对于每个查询，在新的一行输出答案。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 3
2 3 5 7 11
2 1 5
2 2 4
2310 1 5
4 3
18 12 8 9
216 1 2
48 2 4
82944 1 4
```

### 输出

```
5
6
1629
13
12
520
```



---

---
title: "Baudelaire (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF2106G2
tag: ['二分', '点分治', '分治']
---

# Baudelaire (hard version)

## 题目描述

这是该问题的困难版本。两个版本之间的唯一区别在于，在困难版本中树的形态可以是任意的。

本题是交互题。

波德莱尔非常富有，因此他购买了一棵大小为 $n$ 的树，这棵树以某个任意节点为根。此外，每个节点的值为 $1$ 或 $-1$。

书呆子牛看到了这棵树并爱上了它。然而计算机科学的收入不足以让他买下这棵树。波德莱尔决定和书呆子牛玩一个游戏，如果他赢了，就把这棵树送给他。

书呆子牛不知道哪个节点是根，也不知道节点的值。但他可以向波德莱尔提出两种类型的查询：

1. `1 k u₁ u₂ ... uₖ`：设 $f(u)$ 为从树的根到节点 $u$ 的路径上所有节点的值之和。书呆子牛可以选择一个整数 $k$（$1 \le k \le n$）和 $k$ 个节点 $u_1, u_2, ..., u_k$，然后他会收到值 $f(u_1) + f(u_2) + ... + f(u_k)$。
2. `2 u`：波德莱尔将切换节点 $u$ 的值。具体来说，如果 $u$ 的值为 $1$，则变为 $-1$，反之亦然。

如果书呆子牛在总共 $n + 200$ 次查询内正确猜出每个节点的值（即执行查询后树的最终值），他就获胜。你能帮助他获胜吗？

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 10^3$），表示树的大小。

接下来的 $n-1$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$，$u \neq v$），表示树中节点 $u$ 和 $v$ 之间有一条边。

保证所有测试用例的 $n$ 之和不超过 $10^3$，并且每个输入的图都是合法的树。

## 输出格式

要提出类型 $1$ 的查询，请按以下格式输出一行（不带引号）：
- `? 1 k u₁ u₂ ... uₖ`（$1 \le k, u_i \le n$）

评测机将返回一个整数，即 $f(u_1) + f(u_2) + ... + f(u_k)$。

要提出类型 $2$ 的查询，请按以下格式输出一行：
- `? 2 u`（$1 \le u \le n$）

评测机会切换节点 $u$ 的值：如果其值为 $1$，则变为 $-1$，反之亦然。

当你找到答案时，请按以下格式输出一行：
- `! v₁ v₂ ... vₙ`（$v_i = 1$ 或 $v_i = -1$，$v_i$ 是执行查询后节点 $i$ 的值）

之后，继续处理下一个测试用例，或者如果是最后一个测试用例则终止程序。输出答案不计入查询次数。

交互器不是自适应的，这意味着树的值在参与者提出查询之前就已经确定。

如果你的程序进行了超过 $n + 200$ 次查询，它应立即终止并收到 Wrong Answer 的判定。否则，你可能会得到任意判定，因为你的解决方案将继续从已关闭的流中读取数据。

在打印查询后，不要忘记输出换行符并刷新输出缓冲区。否则，你可能会得到 Idleness Limit Exceeded 的判定。可以使用以下方法刷新输出：
- C++：`fflush(stdout)` 或 `cout.flush()`
- Java：`System.out.flush()`
- Pascal：`flush(output)`
- Python：`stdout.flush()`
- 其他语言请参考相关文档。

## Hack 格式

对于 Hack 攻击，请使用以下格式：

第一行应包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。

每个测试用例的第一行必须包含两个整数 $n$ 和 $root$（$2 \le n \le 10^3$，$1 \le root \le n$）——树的大小和树的根节点。

每个测试用例的第二行必须包含 $n$ 个整数 $a_1, a_2, ..., a_n$（$|a_i| = 1$）——其中 $a_i$ 是节点 $i$ 的值。

接下来的 $n-1$ 行每行必须包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$）——表示节点 $u$ 和 $v$ 之间有一条边。

所有测试用例的 $n$ 之和不得超过 $10^3$，并且每个输入的图必须是合法的树。

## 说明/提示

在第一个示例中，树的根是节点 $4$，初始值为 $[-1, -1, -1, 1]$（第 $i$ 个值是节点 $i$ 的值）。

初始时，$f(1) = 0$，$f(2) = 0$，$f(3) = -1$，$f(4) = 1$。因此，第一个查询的答案是 $f(1) + f(2) + f(4) = 1$，第二个查询的答案是 $f(3) + f(1) = -1$。

在切换节点 $4$ 的值后，值变为 $[-1, -1, -1, -1]$。此时 $f(1) = -2$，$f(2) = -2$，$f(3) = -3$，$f(4) = -1$。因此 $f(1) + f(2) + f(4) = -5$，$f(3) + f(1) = -5$。

我们最终回答节点的值为 $[-1, -1, -1, -1]$，这是正确的。注意我们报告的是节点在变化后的值，而不是之前的值。

在第二个示例中，树的根是 $2$，初始值为 $[1, 1]$。

在最后一个示例中，树的根是 $1$，初始值为 $[-1, 1, 1, 1, 1, 1, -1]$。

注意这只是一个解释查询如何工作的示例，并不涉及具体的解题策略。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
4
1 4
4 2
2 3

1

-1


-5

-5

2
1 2

2

7
1 2
2 7
7 3
7 4
7 5
7 6

-1
```

### 输出

```
? 1 3 1 2 4

? 1 2 3 1

? 2 4
? 1 3 1 2 4

? 1 2 3 1

! -1 -1 -1 -1


? 1 1 1

! 1 1






? 1 1 1

! -1 1 1 1 1 1 -1
```



---

---
title: "Needle in a Numstack"
layout: "post"
diff: 提高+/省选-
pid: CF2108D
tag: ['二分', '分类讨论']
---

# Needle in a Numstack

## 题目描述

这是一个交互式问题。

你在阁楼中发现了数字 $k$ 和 $n$，但丢失了两个数组 $A$ 和 $B$。

你记得以下信息：
- $|A| + |B| = n$，即两个数组的总长度为 $n$。
- $|A| \geq k$ 且 $|B| \geq k$，即每个数组的长度至少为 $k$。
- 数组中的元素只包含 $1$ 到 $k$ 的数字。
- 如果从数组 $A$ 中任取 $k$ 个连续元素，它们都互不相同。同样，如果从数组 $B$ 中任取 $k$ 个连续元素，它们也互不相同。

幸运的是，阁楼里的一个善良精灵找到了这两个数组，并将它们连接成一个长度为 $n$ 的数组 $C$。也就是说，数组 $C$ 的前半部分是 $A$ 的元素，后半部分是 $B$ 的元素。

你可以向精灵最多提出 $250$ 次询问。每次询问提供一个索引 $i$（$1 \leq i \leq n$），精灵会返回数组 $C$ 的第 $i$ 个元素。

你的任务是确定数组 $A$ 和 $B$ 的长度，或者报告无法唯一确定它们的长度。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 300$）。接下来是测试用例的描述。

每个测试用例仅包含一行，包含两个整数 $n$ 和 $k$（$1 \leq k \leq 50$，$2k \leq n \leq 10^6$）。

注意，所有测试用例的 $n$ 之和没有限制。

## 输出格式

对于每个测试用例，交互开始时需要读取整数 $n$。

然后你可以进行最多 $250$ 次查询。

每次查询时，输出一个格式为 "? x"（不带引号）的字符串（$1 \leq x \leq n$）。每次查询后，读取一个整数——查询的答案。

如果你进行了过多的查询，将会得到 Wrong answer 的结果。

当你确定答案时，输出一个格式为 "! a b"（不带引号）的字符串，其中 $a$ 和 $b$ 分别是你找到的数组 $A$ 和 $B$ 的长度。这个回答不计入查询次数。

如果无法唯一确定数组的长度，输出 "! -1"（不带引号）。注意，如果存在不超过 $250$ 次查询即可唯一确定数组长度的情况下你回答 $-1$，将会得到 Wrong answer 的结果。

题目保证存在符合题目描述的数组 $A$ 和 $B$，且交互器的输出是正确的。

交互器是非自适应的，这意味着答案在参与者进行查询之前就已经确定，并且不会受到参与者查询的影响。

如果你的程序进行了超过 $250$ 次查询，应立即终止以避免 Wrong answer。否则，你的程序可能会因为继续读取已关闭的流而得到任意结果。

每次输出查询后，不要忘记换行并刷新输出缓冲区。否则，你可能会得到 "IL"（Idleness limit exceeded）的结果。刷新缓冲区的方法如下：
- C++：使用 `fflush(stdout)` 或 `cout.flush()`；
- Java：使用 `System.out.flush()`；
- Pascal：使用 `flush(output)`；
- Python：使用 `stdout.flush()`；
- 其他语言请参考相关文档。

## 说明/提示

考虑第一个例子。我们查询了数组 $C$ 的前 $3$ 个元素（共 $5$ 个）。现在我们知道了数组 $C$ 的前三个元素为 $[1, 2, 2, ?, ?]$。根据条件，数组 $A$ 中的任意 $k$（$k=2$）个连续元素必须互不相同，因此第三个元素 $2$ 不可能属于数组 $A$，它必定属于数组 $B$。由此可以确定数组 $A$ 的长度为 $2$，数组 $B$ 的长度为 $3$。

图中展示了所有测试用例的数组。被查询的元素用黄色标记。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2108D/3a898b9f4f0ed20651c865ecf957d0078f46a581.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
5 2

1

2

2

18 4

2

4

1

1

4

3 1

10 5

9 3

3

3

2

12 4

1

3

1

3

1

3
```

### 输出

```
? 1

? 2

? 3

! 2 3

? 9

? 13

? 10

? 14

? 6

! 9 9

! -1

! 5 5

? 3

? 6

? 9

! 6 3

? 1

? 2

? 5

? 6

? 9

? 10

! -1
```



---

---
title: "Cheater"
layout: "post"
diff: 提高+/省选-
pid: CF2113D
tag: ['贪心', '二分']
---

# Cheater

## 题目描述

你正在赌场玩一种新的纸牌游戏，规则如下：

1. 游戏使用一副共 $2n$ 张不同点数的牌。
2. 牌堆被均匀分给玩家和庄家：每人获得 $n$ 张牌。
3. 在 $n$ 轮比赛中，玩家和庄家同时打出手中最上面的一张牌。比较两张牌的点数，点数较大的一方获得 $1$ 分。获胜的牌会被移出游戏，而失败的牌会返回持有者的手牌，并放在该玩家手牌堆的最上面。

注意游戏总是会进行恰好 $n$ 轮。

你已经追踪了洗牌过程，知道庄家手牌的从上到下的顺序。为了最大化你的得分，你可以在游戏开始前交换手中任意两张牌的位置（最多交换一次以避免引起怀疑）。

请确定你能获得的最大分数。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 5 \cdot 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^{5}$）——玩家手牌的数量。

第二行包含 $n$ 个整数 $a_{1}, a_{2}, \ldots, a_{n}$（$1 \leq a_{i} \leq 2n$）——玩家手牌从上到下的点数。

第三行包含 $n$ 个整数 $b_{1}, b_{2}, \ldots, b_{n}$（$1 \leq b_{i} \leq 2n$）——庄家手牌从上到下的点数。

保证所有牌的点数都是唯一的。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——你能获得的最大分数。

## 说明/提示

在第一个测试用例中，可以不交换任何牌。游戏过程如下：

1. 比较点数为 $13$ 和 $6$ 的牌。玩家获胜，得 $1$ 分。
2. 比较点数为 $7$ 和 $6$ 的牌。玩家获胜，得 $1$ 分。
3. 比较点数为 $4$ 和 $6$ 的牌。庄家获胜。
4. 比较点数为 $4$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。
5. 比较点数为 $9$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。
6. 比较点数为 $12$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。
7. 比较点数为 $10$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。

因此玩家总共获得 $6$ 分。

在第二个测试用例中，可以交换点数为 $1$ 和 $5$ 的牌，交换后玩家手牌变为 $[5, 6, 1]$。游戏过程如下：

1. 比较点数为 $5$ 和 $2$ 的牌。玩家获胜，得 $1$ 分。
2. 比较点数为 $6$ 和 $2$ 的牌。玩家获胜，得 $1$ 分。
3. 比较点数为 $1$ 和 $2$ 的牌。庄家获胜。

因此玩家总共获得 $2$ 分。

在第三个测试用例中，可以交换点数为 $3$ 和 $10$ 的牌，交换后玩家手牌变为 $[8, 6, 10, 3, 1]$。游戏过程如下：

1. 比较点数为 $8$ 和 $7$ 的牌。玩家获胜，得$1$分。
2. 比较点数为 $6$ 和 $7$ 的牌。庄家获胜。
3. 比较点数为 $6$ 和 $9$ 的牌。庄家获胜。
4. 比较点数为 $6$ 和 $5$ 的牌。玩家获胜，得 $1$ 分。
5. 比较点数为 $10$ 和 $5 $的牌。玩家获胜，得 $1$ 分。

因此玩家总共获得 $3$ 分。

## 样例 #1

### 输入

```
3
7
13 7 4 9 12 10 2
6 1 14 3 8 5 11
3
1 6 5
2 3 4
5
8 6 3 10 1
7 9 5 2 4
```

### 输出

```
6
2
3
```



---

---
title: "Levko and Array"
layout: "post"
diff: 提高+/省选-
pid: CF360B
tag: ['动态规划 DP', '二分']
---

# Levko and Array

## 题目描述

Levko has an array that consists of integers: $ a_{1},a_{2},...\ ,a_{n} $ . But he doesn’t like this array at all.

Levko thinks that the beauty of the array $ a $ directly depends on value $ c(a) $ , which can be calculated by the formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF360B/bc46a8f9d72cc21bf5d1738220033f31da7db825.png) The less value $ c(a) $ is, the more beautiful the array is.It’s time to change the world and Levko is going to change his array for the better. To be exact, Levko wants to change the values of at most $ k $ array elements (it is allowed to replace the values by any integers). Of course, the changes should make the array as beautiful as possible.

Help Levko and calculate what minimum number $ c(a) $ he can reach.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=2000 $ ). The second line contains space-separated integers $ a_{1},a_{2},...\ ,a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ).

## 输出格式

A single number — the minimum value of $ c(a) $ Levko can get.

## 说明/提示

In the first sample Levko can change the second and fourth elements and get array: $ 4 $ , $ 4 $ , $ 4 $ , $ 4 $ , $ 4 $ .

In the third sample he can get array: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ .

## 样例 #1

### 输入

```
5 2
4 7 4 7 4

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 1
-100 0 100

```

### 输出

```
100

```

## 样例 #3

### 输入

```
6 3
1 2 3 7 8 9

```

### 输出

```
1

```



---

---
title: "George and Interesting Graph"
layout: "post"
diff: 提高+/省选-
pid: CF387D
tag: ['网络流', '二分图']
---

# George and Interesting Graph

## 题目描述

- 没有重边；
- 存在结点 $v$（称为中心），使得对于图中的任意结点 $u$，都有边 $(u,v)$ 和 $(v,u)$，注意自环 $(v,v)$ 也应该存在；
- 除去中心外，每个点的入度和出度都恰好为 $2$； 

显然很少有图有趣，但 George 可以把图变得有趣：每次他可以增加一条边或者删除一条已经存在的边。

现在给出图 $G$，George 想知道他最少做多少次操作可以使它变得有趣。

## 输出格式

Translated by @Harry_bh

## 样例 #1

### 输入

```
3 7
1 1
2 2
3 1
1 3
3 2
2 3
3 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 6
1 1
2 2
3 1
3 2
2 3
3 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1
2 2

```

### 输出

```
6

```



---

---
title: "George and Cards"
layout: "post"
diff: 提高+/省选-
pid: CF387E
tag: ['贪心', '线段树', '二分']
---

# George and Cards

## 题目描述

George is a cat, so he loves playing very much.

Vitaly put $ n $ cards in a row in front of George. Each card has one integer written on it. All cards had distinct numbers written on them. Let's number the cards from the left to the right with integers from $ 1 $ to $ n $ . Then the $ i $ -th card from the left contains number $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Vitaly wants the row to have exactly $ k $ cards left. He also wants the $ i $ -th card from left to have number $ b_{i} $ written on it. Vitaly gave a task to George, to get the required sequence of cards using the remove operation $ n-k $ times.

In one remove operation George can choose $ w $ ( $ 1<=w $ ; $ w $ is not greater than the current number of cards in the row) contiguous cards (contiguous subsegment of cards). Let's denote the numbers written on these card as $ x_{1},x_{2},...,x_{w} $ (from the left to the right). After that, George can remove the card $ x_{i} $ , such that $ x_{i}<=x_{j} $ for each $ j $ $ (1<=j<=w) $ . After the described operation George gets $ w $ pieces of sausage.

George wondered: what maximum number of pieces of sausage will he get in total if he reaches his goal and acts optimally well? Help George, find an answer to his question!

## 输入格式

The first line contains integers $ n $ and $ k $ ( $ 1<=k<=n<=10^{6} $ ) — the initial and the final number of cards.

The second line contains $ n $ distinct space-separated integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the initial row of cards.

The third line contains $ k $ space-separated integers $ b_{1},b_{2},...,b_{k} $ — the row of cards that you need to get. It is guaranteed that it's possible to obtain the given row by using the remove operation for $ n-k $ times.

## 输出格式

Print a single integer — the maximum number of pieces of sausage that George can get if he acts optimally well.

## 样例 #1

### 输入

```
3 2
2 1 3
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10

```

### 输出

```
30

```



---

---
title: "LIS of Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF486E
tag: ['动态规划 DP', '二分', '枚举']
---

# LIS of Sequence

## 题目描述

# 题意：
给你一个长度为n的序列a1,a2,...,an，你需要把这n个元素分成三类：1，2，3：

1:所有的最长上升子序列都不包含这个元素

2:有但非所有的最长上升子序列包含这个元素

3:所有的最长上升子序列都包含这个元素

## 输入格式

第一行包含一个正整数n，表示序列的长度。第二行包含n个正整数a1,a2,...,an，表示序列中的元素。

## 输出格式

一行，包含一个长度为n的、由1,2,3三种数字组成的字符串，第i个数字表示ai所属类别。

## 说明/提示

1≤n≤10^5

1≤ai≤10^5

## 样例 #1

### 输入

```
1
4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 3 2 5

```

### 输出

```
3223

```

## 样例 #3

### 输入

```
4
1 5 2 3

```

### 输出

```
3133

```



---

---
title: "Love Triangles"
layout: "post"
diff: 提高+/省选-
pid: CF553C
tag: ['二分图']
---

# Love Triangles

## 题目描述

There are many anime that are about "love triangles": Alice loves Bob, and Charlie loves Bob as well, but Alice hates Charlie. You are thinking about an anime which has $ n $ characters. The characters are labeled from $ 1 $ to $ n $ . Every pair of two characters can either mutually love each other or mutually hate each other (there is no neutral state).

You hate love triangles (A-B are in love and B-C are in love, but A-C hate each other), and you also hate it when nobody is in love. So, considering any three characters, you will be happy if exactly one pair is in love (A and B love each other, and C hates both A and B), or if all three pairs are in love (A loves B, B loves C, C loves A).

You are given a list of $ m $ known relationships in the anime. You know for sure that certain pairs love each other, and certain pairs hate each other. You're wondering how many ways you can fill in the remaining relationships so you are happy with every triangle. Two ways are considered different if two characters are in love in one way but hate each other in the other. Print this count modulo $ 1000000007 $ .

## 输入格式

The first line of input will contain two integers $ n,m $ ( $ 3<=n<=100000 $ , $ 0<=m<=100000 $ ).

The next $ m $ lines will contain the description of the known relationships. The $ i $ -th line will contain three integers $ a_{i},b_{i},c_{i} $ . If $ c_{i} $ is 1, then $ a_{i} $ and $ b_{i} $ are in love, otherwise, they hate each other ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF553C/26e54e6b3b9751cc71b106d519c04019ef62f5b4.png)).

Each pair of people will be described no more than once.

## 输出格式

Print a single integer equal to the number of ways to fill in the remaining pairs so that you are happy with every triangle modulo $ 1000000007 $ .

## 说明/提示

In the first sample, the four ways are to:

- Make everyone love each other
- Make 1 and 2 love each other, and 3 hate 1 and 2 (symmetrically, we get 3 ways from this).

In the second sample, the only possible solution is to make 1 and 3 love each other and 2 and 4 hate each other.

## 样例 #1

### 输入

```
3 0

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 1

```

### 输出

```
0

```



---

---
title: "Gadgets for dollars and pounds"
layout: "post"
diff: 提高+/省选-
pid: CF609D
tag: ['贪心', '二分', '前缀和']
---

# Gadgets for dollars and pounds

## 题目描述

一个人手上有 $s$ 卢布，他要在 $n$ 天内买 $m$ 样东西中的 $k$ 样。

每个物品有两种支付方式，要么用美元，要么用英镑。

每天有不同的支付方式代价，即换取一美元或英镑，需要付出 $x_i$ 卢布的代价。

求最早完成买 $k$ 样东西的天数。如果无法完成任务，输出 `-1`。

一种商品只能购买一次，但是一天可以买多种商品。

## 输入格式

第一行包含四个整数，$n, m, k, s$。

第二行 $n$ 个整数，表示每天多少卢布换一美元。

第三行 $n$ 个整数，表示多少卢布换一英镑。

接下来是 $m$ 行，每行 $2$ 个整数，表示每样东西用什么货币结账（ $1$ 是美元，$2$ 是英镑），以及要多少那种外币。

## 输出格式

输出最短到第几天买完 $k$ 样商品。

以及输出 $q_i$ 与 $d_i$ 表示在第 $d_i$ 天购买第 $q_i$ 样东西。

## 样例 #1

### 输入

```
5 4 2 2
1 2 3 2 1
3 2 1 2 3
1 1
2 1
1 2
2 2

```

### 输出

```
3
1 1
2 3

```

## 样例 #2

### 输入

```
4 3 2 200
69 70 71 72
104 105 106 107
1 1
2 2
1 2

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4 3 1 1000000000
900000 910000 940000 990000
990000 999000 999900 999990
1 87654
2 76543
1 65432

```

### 输出

```
-1

```



---

---
title: "Sand Fortress"
layout: "post"
diff: 提高+/省选-
pid: CF985D
tag: ['数学', '二分', '枚举']
---

# Sand Fortress

## 题目描述

You are going to the beach with the idea to build the greatest sand castle ever in your head! The beach is not as three-dimensional as you could have imagined, it can be decribed as a line of spots to pile up sand pillars. Spots are numbered $ 1 $ through infinity from left to right.

Obviously, there is not enough sand on the beach, so you brought $ n $ packs of sand with you. Let height $ h_{i} $ of the sand pillar on some spot $ i $ be the number of sand packs you spent on it. You can't split a sand pack to multiple pillars, all the sand from it should go to a single one. There is a fence of height equal to the height of pillar with $ H $ sand packs to the left of the first spot and you should prevent sand from going over it.

Finally you ended up with the following conditions to building the castle:

- $ h_{1}<=H $ : no sand from the leftmost spot should go over the fence;
- For any ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985D/77d67b6184b30d84bfc3e3e2794dc8de9b20fcf2.png) $ |h_{i}-h_{i+1}|<=1 $ : large difference in heights of two neighboring pillars can lead sand to fall down from the higher one to the lower, you really don't want this to happen;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985D/7c65b11667de38fcb78de5945051b7b0879e1abf.png): you want to spend all the sand you brought with you.

As you have infinite spots to build, it is always possible to come up with some valid castle structure. Though you want the castle to be as compact as possible.

Your task is to calculate the minimum number of spots you can occupy so that all the aforementioned conditions hold.

## 输入格式

The only line contains two integer numbers $ n $ and $ H $ ( $ 1<=n,H<=10^{18} $ ) — the number of sand packs you have and the height of the fence, respectively.

## 输出格式

Print the minimum number of spots you can occupy so the all the castle building conditions hold.

## 说明/提示

Here are the heights of some valid castles:

- $ n=5,H=2,[2,2,1,0,...],[2,1,1,1,0,...],[1,0,1,2,1,0,...] $
- $ n=6,H=8,[3,2,1,0,...],[2,2,1,1,0,...],[0,1,0,1,2,1,1,0...] $ (this one has $ 5 $ spots occupied)

The first list for both cases is the optimal answer, $ 3 $ spots are occupied in them.

And here are some invalid ones:

- $ n=5,H=2,[3,2,0,...],[2,3,0,...],[1,0,2,2,...] $
- $ n=6,H=8,[2,2,2,0,...],[6,0,...],[1,4,1,0...],[2,2,1,0,...] $

## 样例 #1

### 输入

```
5 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6 8

```

### 输出

```
3

```



---

