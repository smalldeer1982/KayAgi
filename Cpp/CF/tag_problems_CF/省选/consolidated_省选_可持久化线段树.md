---
title: "Tower Defense"
layout: "post"
diff: 省选/NOI-
pid: CF1651F
tag: ['线段树', '可持久化线段树', '分块']
---

# Tower Defense

## 题目描述

Monocarp is playing a tower defense game. A level in the game can be represented as an OX axis, where each lattice point from $ 1 $ to $ n $ contains a tower in it.

The tower in the $ i $ -th point has $ c_i $ mana capacity and $ r_i $ mana regeneration rate. In the beginning, before the $ 0 $ -th second, each tower has full mana. If, at the end of some second, the $ i $ -th tower has $ x $ mana, then it becomes $ \mathit{min}(x + r_i, c_i) $ mana for the next second.

There are $ q $ monsters spawning on a level. The $ j $ -th monster spawns at point $ 1 $ at the beginning of $ t_j $ -th second, and it has $ h_j $ health. Every monster is moving $ 1 $ point per second in the direction of increasing coordinate.

When a monster passes the tower, the tower deals $ \mathit{min}(H, M) $ damage to it, where $ H $ is the current health of the monster and $ M $ is the current mana amount of the tower. This amount gets subtracted from both monster's health and tower's mana.

Unfortunately, sometimes some monsters can pass all $ n $ towers and remain alive. Monocarp wants to know what will be the total health of the monsters after they pass all towers.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of towers.

The $ i $ -th of the next $ n $ lines contains two integers $ c_i $ and $ r_i $ ( $ 1 \le r_i \le c_i \le 10^9 $ ) — the mana capacity and the mana regeneration rate of the $ i $ -th tower.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of monsters.

The $ j $ -th of the next $ q $ lines contains two integers $ t_j $ and $ h_j $ ( $ 0 \le t_j \le 2 \cdot 10^5 $ ; $ 1 \le h_j \le 10^{12} $ ) — the time the $ j $ -th monster spawns and its health.

The monsters are listed in the increasing order of their spawn time, so $ t_j < t_{j+1} $ for all $ 1 \le j \le q-1 $ .

## 输出格式

Print a single integer — the total health of all monsters after they pass all towers.

## 样例 #1

### 输入

```
3
5 1
7 4
4 2
4
0 14
1 10
3 16
10 16
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
2 1
4 1
5 4
7 5
8 3
9
1 21
2 18
3 14
4 24
5 8
6 25
7 19
8 24
9 24
```

### 输出

```
40
```



---

---
title: "Rollbacks (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1858E2
tag: ['可持久化线段树']
---

# Rollbacks (Hard Version)

## 题目描述

This is a hard version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 输入格式

The first line contains an integer $ q $ ( $ 1 \leq q \leq 10^6 $ ) — the number of queries.

The next $ q $ lines contain the queries as described above.

It is guaranteed that

- in the queries of the first type, $ 1 \le x \le 10^6 $ ;
- in the queries of the second type, $ k \ge 1 $ and $ k $ does not exceed the current length of the array $ a $ ;
- at the moment of the queries of the third type, there is at least one query of the first or of the second type that can be rolled back.

It is also guaranteed that the number of queries of the fourth type (?) does not exceed $ 10^5 $ .

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query, so don't forget to flush output after printing answers. You can use functions like fflush(stdout) in C++ and BufferedWriter.flush in Java or similar after each writing in your program.

## 输出格式

For each query of the fourth type output one integer — the number of distinct elements in array $ a $ at the moment of query.

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1, 1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?
```

### 输出

```
2
1
1
```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?
```

### 输出

```
2
0
```



---

---
title: "Subtree Minimum Query"
layout: "post"
diff: 省选/NOI-
pid: CF893F
tag: ['可持久化线段树']
---

# Subtree Minimum Query

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Each vertex has a number written on it; number $ a_{i} $ is written on vertex $ i $ .

Let's denote $ d(i,j) $ as the distance between vertices $ i $ and $ j $ in the tree (that is, the number of edges in the shortest path from $ i $ to $ j $ ). Also let's denote the  $ k $ -blocked subtree of vertex $ x $ as the set of vertices $ y $ such that both these conditions are met:

- $ x $ is an ancestor of $ y $ (every vertex is an ancestor of itself);
- $ d(x,y)<=k $ .

You are given $ m $ queries to the tree. $ i $ -th query is represented by two numbers $ x_{i} $ and $ k_{i} $ , and the answer to this query is the minimum value of $ a_{j} $ among such vertices $ j $ such that $ j $ belongs to $ k_{i} $ -blocked subtree of $ x_{i} $ .

Write a program that would process these queries quickly!

Note that the queries are given in a modified way.

## 输入格式

The first line contains two integers $ n $ and $ r $ ( $ 1<=r<=n<=100000 $ ) — the number of vertices in the tree and the index of the root, respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the numbers written on the vertices.

Then $ n-1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1<=x,y<=n $ ) and representing an edge between vertices $ x $ and $ y $ . It is guaranteed that these edges form a tree.

Next line contains one integer $ m $ ( $ 1<=m<=10^{6} $ ) — the number of queries to process.

Then $ m $ lines follow, $ i $ -th line containing two numbers $ p_{i} $ and $ q_{i} $ , which can be used to restore $ i $ -th query ( $ 1<=p_{i},q_{i}<=n $ ).

 $ i $ -th query can be restored as follows:

Let $ last $ be the answer for previous query (or $ 0 $ if $ i=1 $ ). Then $ x_{i}=((p_{i}+last)modn)+1 $ , and $ k_{i}=(q_{i}+last)modn $ .

## 输出格式

Print $ m $ integers. $ i $ -th of them has to be equal to the answer to $ i $ -th query.

## 样例 #1

### 输入

```
5 2
1 3 2 3 5
2 3
5 1
3 4
4 1
2
1 2
2 3

```

### 输出

```
2
5

```



---

---
title: "Jamie and To-do List"
layout: "post"
diff: 省选/NOI-
pid: CF916D
tag: ['线段树', '可持久化线段树', '可持久化']
---

# Jamie and To-do List

## 题目描述

“为什么我要完成这么多作业？”

Jamie 正忙于他的学校生活。

他开始忘记他必须做的作业。他决定把这些事情写在 To-Do List 上。

他为他的每项任务分配一个价值优先级(较低的价值意味着更重要)，这样他就可以决定他需要花更多的时间在哪个任务上。

几天后，Jamie 发现名单太大了，他甚至不能自己管理名单！由于您是 Jamie 的好朋友，请帮助他编写一个程序来支持待办事项列表中的以下操作:

`set ai xi`：设置任务 $a_i$ 的优先级为 $x_i$，如果该列表中没有出现则加入该任务。

`remove a_i`：删除该任务。

`query a_i`：求优先级比 $a_i$ 小的任务个数，如果没有则输出 $-1$。

`undo sum`：删除此次操作之前的 $sum$ 次操作。

在 Day 0，To-Do List 为空，在接下来 $Q$ 个日子内，Jamie 都会在四个操作中任选一个执行。

对于每个询问操作，输出对应的答案。

## 输入格式

第一行是一个整数 $Q$。

接下来的 $Q$ 行为任一个操作，第 $i$ 为第 $i$ 天的操作。

**保证最后一行是询问操作。**

## 输出格式

对于所有的查询操作，输出对应的答案。

## 说明/提示

保证输入的字符串由小写字符构成，设其长度为 $len$，则 $1\leq len\leq15$。

$1\le Q\le10^5$，并且保证对于所有的 undo 操作，$sum$ 不超过该天之前的天数。

## 样例 #1

### 输入

```
8
set chemlabreport 1
set physicsexercise 2
set chinesemockexam 3
query physicsexercise
query chinesemockexam
remove physicsexercise
query physicsexercise
query chinesemockexam

```

### 输出

```
1
2
-1
1

```

## 样例 #2

### 输入

```
8
set physicsexercise 2
set chinesemockexam 3
set physicsexercise 1
query physicsexercise
query chinesemockexam
undo 4
query physicsexercise
query chinesemockexam

```

### 输出

```
0
1
0
-1

```

## 样例 #3

### 输入

```
5
query economicsessay
remove economicsessay
query economicsessay
undo 2
query economicsessay

```

### 输出

```
-1
-1
-1

```

## 样例 #4

### 输入

```
5
set economicsessay 1
remove economicsessay
undo 1
undo 1
query economicsessay

```

### 输出

```
-1

```



---

