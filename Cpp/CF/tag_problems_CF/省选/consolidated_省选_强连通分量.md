---
title: "Beautiful Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1904F
tag: ['倍增', '强连通分量', 'Tarjan', '最近公共祖先 LCA']
---

# Beautiful Tree

## 题目描述

Lunchbox has a tree of size $ n $ rooted at node $ 1 $ . Each node is then assigned a value. Lunchbox considers the tree to be beautiful if each value is distinct and ranges from $ 1 $ to $ n $ . In addition, a beautiful tree must also satisfy $ m $ requirements of $ 2 $ types:

- "1 a b c" — The node with the smallest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .
- "2 a b c" — The node with the largest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .

Now, you must assign values to each node such that the resulting tree is beautiful. If it is impossible to do so, output $ -1 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n, m \le 2 \cdot 10^5 $ ).

The next $ n - 1 $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n, u \ne v $ ) — denoting an edge between nodes $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

The next $ m $ lines each contain four integers $ t $ , $ a $ , $ b $ , and $ c $ ( $ t \in \{1,2\} $ , $ 1 \le a, b, c \le n $ ). It is guaranteed that node $ c $ is on the path between nodes $ a $ and $ b $ .

## 输出格式

If it is impossible to assign values such that the tree is beautiful, output $ -1 $ . Otherwise, output $ n $ integers, the $ i $ -th of which denotes the value of node $ i $ .

## 样例 #1

### 输入

```
7 5
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
1 2 7 1
1 7 5 7
2 4 2 2
```

### 输出

```
1 6 7 5 3 4 2
```

## 样例 #2

### 输入

```
2 2
1 2
1 1 2 1
1 1 2 2
```

### 输出

```
-1
```



---

---
title: "For the Emperor!"
layout: "post"
diff: 省选/NOI-
pid: CF2046D
tag: ['强连通分量', '费用流']
---

# For the Emperor!

## 题目描述

在古罗马，为了击败野蛮人，制定了一项计划，但要实施该计划，每个城市都必须得到通知。

罗马帝国的北部由 $n$ 个城市组成，这些城市通过 $m$ 条单向道路相连。起初，第 $i$ 个城市有 $a_i$ 名信使，每名信使可以沿着现有的道路自由地在城市间移动。一名信使可以携带一份计划副本，并在他访问的城市中传达信息，并且可以在他当前所在的城市为其他信使制作无限多的副本。

开始时，你需要制作一定数量的计划，并将它们交给选定的信使。你的目标是确保每座城市都被携带计划的信使访问过。找出最初需要制作的计划的最小数量，以确保信使能够将计划送到每一个城市，或者确定根本无法做到这一点。

## 输入格式

每个测试数据包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$2 \le n \le 200$，$1 \le m \le 800$）—— 分别表示城市的数量和道路的数量。

第二行包含 $n$ 个非负整数 $a_1, a_2, \ldots, a_n$（$0 \le a_{i} \le n$）—— 分别表示每个城市初始拥有的信使数量。

接下来的 $m$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u,v \le n, u \ne v$），表示从城市 $u$ 到城市 $v$ 有一条单向道路。道路可能会重复出现。

保证所有测试用例中 $n$ 的总和不超过 $200$。保证所有测试用例中 $m$ 的总和不超过 $800$。

## 输出格式

对于每个测试用例，输出一行包含一个整数 —— 表示最初需要给信使的计划副本的最小数量，如果不可能通知到所有城市，则输出 $-1$。

## 样例 #1

### 输入

```
2
7 6
2 1 0 1 2 3 4
1 2
1 3
2 4
2 5
3 6
3 7
4 4
1 1 1 1
1 2
1 3
2 4
3 4
```

### 输出

```
2
2
```



---

---
title: "Tourists"
layout: "post"
diff: 省选/NOI-
pid: CF487E
tag: ['线段树', '强连通分量', '树链剖分', '圆方树']
---

# Tourists

## 题目描述

Cyberland 有 $n$ 座城市，编号从 $1$ 到 $n$，有 $m$ 条双向道路连接这些城市。第 $j$ 条路连接城市 $a_j$ 和 $b_j$。每天，都有成千上万的游客来到 Cyberland 游玩。

在每一个城市，都有纪念品售卖，第 $i$ 个城市售价为 $w_i$。这个售价有时会变动。

每一个游客的游览路径都有固定起始城市和终止城市，且不会经过重复的城市。

他们会在路径上的城市中，售价最低的那个城市购买纪念品。

你能求出每一个游客在所有合法的路径中能购买的最低售价是多少吗？

你要处理 $q$ 个操作：

`C a w`： 表示 $a$ 城市的纪念品售价变成 $w$。

`A a b`： 表示有一个游客要从 $a$ 城市到 $b$ 城市，你要回答在所有他的旅行路径中最低售价的最低可能值。

## 输入格式

第一行包含用一个空格隔开的三个数 $n, m, q$。

接下来 $n$ 行，每行包含一个数 $w_i$。

接下来 $m$ 行，每行包含用一个空格隔开的两个数 $a_j$,$b_j$。（$1 \le a _ j, b _ j \le n,a _ j \neq b _ j$）

数据保证没有两条道路连接同样一对城市，也没有一条道路两端是相同的城市。并且任意两个城市都可以相互到达。

接下来 $q$ 行，每行是 `C a w` 或 `A a b` ，描述了一个操作。

## 输出格式

对于每一个 A 类操作，输出一行表示对应的答案。

## 样例 #1

### 输入

```
3 3 3
1
2
3
1 2
2 3
1 3
A 2 3
C 1 5
A 2 3

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
7 9 4
1
2
3
4
5
6
7
1 2
2 5
1 5
2 3
3 4
2 4
5 6
6 7
5 7
A 2 3
A 6 4
A 6 7
A 3 3

```

### 输出

```
2
1
5
3

```



---

