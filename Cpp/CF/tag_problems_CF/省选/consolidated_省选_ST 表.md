---
title: "Game in Tree (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2013F1
tag: ['贪心', 'ST 表']
---

# Game in Tree (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ \mathbf{u = v} $ . You can make hacks only if both versions of the problem are solved.

Alice and Bob are playing a fun game on a tree. This game is played on a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Recall that a tree with $ n $ vertices is an undirected connected graph with $ n - 1 $ edges.

Alice and Bob take turns, with Alice going first. Each player starts at some vertex.

On their turn, a player must move from the current vertex to a neighboring vertex that has not yet been visited by anyone. The first player who cannot make a move loses.

You are given two vertices $ u $ and $ v $ . Represent the simple path from vertex $ u $ to $ v $ as an array $ p_1, p_2, p_3, \ldots, p_m $ , where $ p_1 = u $ , $ p_m = v $ , and there is an edge between $ p_i $ and $ p_{i + 1} $ for all $ i $ ( $ 1 \le i < m $ ).

You need to determine the winner of the game if Alice starts at vertex $ 1 $ and Bob starts at vertex $ p_j $ for each $ j $ (where $ 1 \le j \le m $ ).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

Each of the following $ n - 1 $ lines contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ ), denoting an undirected edge between vertices $ a $ and $ b $ . It is guaranteed that these edges form a tree.

The last line of each test case contains two integers $ u $ and $ v $ ( $ 2 \le u, v \le n $ , $ \mathbf{u = v} $ ).

It is guaranteed that the path from $ u $ to $ v $ does not pass through vertex $ 1 $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ m $ lines.

In the $ i $ -th line, print the winner of the game if Alice starts at vertex $ 1 $ and Bob starts at vertex $ p_i $ . Print "Alice" (without quotes) if Alice wins, or "Bob" (without quotes) otherwise.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2013F1/e1cf544a0db6c078ce895e1ac7918ee5810cf6b5.png) Tree from the first and second examples.In the first test case, the path will be ( $ 2,2 $ ). Bob starts at vertex $ 2 $ , Alice will not be able to move anywhere on her first turn and will lose.

In the second test case, the path will be ( $ 3,3 $ ). Bob starts at vertex $ 3 $ , Alice will move to vertex $ 2 $ , and Bob will have no remaining vertices to visit and will lose.

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 2
3
1 2
2 3
3 3
6
1 2
1 3
2 4
2 5
1 6
4 4
```

### 输出

```
Bob
Alice
Alice
```



---

---
title: "Narrower Passageway"
layout: "post"
diff: 省选/NOI-
pid: CF2045E
tag: ['数学', 'ST 表', '单调栈']
---

# Narrower Passageway

## 题目描述

你是 ICPC 王国的一名战略家，近日你收到情报，王国附近的一条狭窄通道将遭遇怪物的袭击。这条通道可以简化为一个 2 行 $N$ 列的网格。我们用 $(r, c)$ 表示网格中第 $r$ 行第 $c$ 列的格子。每天会安排一个力量值为 $P_{r, c}$ 的士兵驻守在 $(r, c)$ 位置上。

这里常年大雾，每列都有 $50\%$ 的概率被雾气笼罩。一旦某列被雾气覆盖，两个驻守该列的士兵将无法执行任务。否则，士兵将正常部署。

我们定义一个连通区域 $[u, v]$（$u \leq v$）为从第 $u$ 列到第 $v$ 列连续且无雾的列。下面的示例中，灰色部分代表被雾覆盖的格子，共有四个连通区域：$[1, 2]$、$[4, 6]$、$[9, 9]$ 和 $[11, 11]$。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/47744495c3a12fb362399d4924e5c674c3e83888.png)

连通区域 $[u, v]$ 的力量可以这样计算。设 $m_1$ 和 $m_2$ 分别为该区域内第一行和第二行士兵力量的最大值。具体来说，对于 $r \in \{1, 2\}$，有 $m_r = \max (P_{r, u}, P_{r, u + 1}, \dots, P_{r, v})$。如果 $m_1 = m_2$，则该区域的力量是 $0$；否则，力量为 $\min (m_1, m_2)$。

一个工作日的总力量定义为所有连通区域力量的总和。请计算在任意一天部署的期望总力量。

## 输入格式

第一行是一个整数 $N$，表示列数（$1 \leq N \leq 100\,000$）。

接下来的两行，每行包含 $N$ 个整数，表示士兵的力量值 $P_{r, c}$（$1 \leq P_{r, c} \leq 200\,000$）。

## 输出格式

设 $M = 998\,244\,353$。可以证明期望总力量表示为一个不可约分数 $\frac{x}{y}$，其中 $x$ 和 $y$ 是整数，且 $y \not\equiv 0 \pmod{M}$。请输出一个整数 $k$，使得 $0 \leq k < M$ 且 $k \cdot y \equiv x \pmod{M}$。

## 说明/提示

样例输入/输出 #1 解释

这条通道可能有 $8$ 种不同的布局。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/70a3bbc18f3f05a2f49fd32453ba66ee47116d57.png)

每种布局出现的概率是相同的。因此，期望总力量为 $(0 + 5 + 10 + 5 + 5 + 0 + 5 + 0) / 8 = \frac{15}{4}$。由于 $249\,561\,092 \cdot 4 \equiv 15 \pmod{998\,244\,353}$，所以样例的输出为 $249\,561\,092$。

样例输入/输出 #2 解释

期望总力量为 $\frac{67}{16}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
8 4 5
5 4 8
```

### 输出

```
249561092
```

## 样例 #2

### 输入

```
5
10 20 5 8 5
5 20 7 5 8
```

### 输出

```
811073541
```



---

---
title: "Dreamoon and Notepad"
layout: "post"
diff: 省选/NOI-
pid: CF477E
tag: ['模拟', '二分', 'ST 表', '分类讨论']
---

# Dreamoon and Notepad

## 题目描述

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 输入格式

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 输出格式

For each query print the result of the query.

## 说明/提示

In the first sample, the first query can be solved with keys: HOME, right.

The second query can be solved with keys: down, down, down, END, down.

The third query can be solved with keys: down, END, down.

The fourth query can be solved with keys: END, down.

## 样例 #1

### 输入

```
9
1 3 5 3 1 3 5 3 1
4
3 5 3 1
3 3 7 3
1 0 3 3
6 0 7 3

```

### 输出

```
2
5
3
2

```

## 样例 #2

### 输入

```
2
10 5
1
1 0 1 5

```

### 输出

```
3

```



---

