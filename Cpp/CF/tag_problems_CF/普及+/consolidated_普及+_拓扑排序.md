---
title: "Toss a Coin to Your Graph..."
layout: "post"
diff: 普及+/提高
pid: CF1679D
tag: ['二分', '拓扑排序']
---

# Toss a Coin to Your Graph...

## 题目描述

One day Masha was walking in the park and found a graph under a tree... Surprised? Did you think that this problem would have some logical and reasoned story? No way! So, the problem...

Masha has an oriented graph which $ i $ -th vertex contains some positive integer $ a_i $ . Initially Masha can put a coin at some vertex. In one operation she can move a coin placed in some vertex $ u $ to any other vertex $ v $ such that there is an oriented edge $ u \to v $ in the graph. Each time when the coin is placed in some vertex $ i $ , Masha write down an integer $ a_i $ in her notebook (in particular, when Masha initially puts a coin at some vertex, she writes an integer written at this vertex in her notebook). Masha wants to make exactly $ k - 1 $ operations in such way that the maximum number written in her notebook is as small as possible.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le m \le 2 \cdot 10^5 $ , $ 1 \le k \le 10^{18} $ ) — the number of vertices and edges in the graph, and the number of operation that Masha should make.

The second line contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 10^9 $ ) — the numbers written in graph vertices.

Each of the following $ m $ lines contains two integers $ u $ and $ v $ ( $ 1 \le u \ne v \le n $ ) — it means that there is an edge $ u \to v $ in the graph.

It's guaranteed that graph doesn't contain loops and multi-edges.

## 输出格式

Print one integer — the minimum value of the maximum number that Masha wrote in her notebook during optimal coin movements.

If Masha won't be able to perform $ k - 1 $ operations, print $ -1 $ .

## 说明/提示

Graph described in the first and the second examples is illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679D/f21a10b2a32ca5315b6d3233f4e3f1d967d3f865.png)In the first example Masha can initially put a coin at vertex $ 1 $ . After that she can perform three operations: $ 1 \to 3 $ , $ 3 \to 4 $ and $ 4 \to 5 $ . Integers $ 1, 2, 3 $ and $ 4 $ will be written in the notepad.

In the second example Masha can initially put a coin at vertex $ 2 $ . After that she can perform $ 99 $ operations: $ 2 \to 5 $ , $ 5 \to 6 $ , $ 6 \to 2 $ , $ 2 \to 5 $ , and so on. Integers $ 10, 4, 5, 10, 4, 5, \ldots, 10, 4, 5, 10 $ will be written in the notepad.

In the third example Masha won't be able to perform $ 4 $ operations.

## 样例 #1

### 输入

```
6 7 4
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 7 100
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
2 1 5
1 1
1 2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
1 0 1
1000000000
```

### 输出

```
1000000000
```



---

---
title: "Medium Demon Problem (hard version)"
layout: "post"
diff: 普及+/提高
pid: CF2044G2
tag: ['贪心', '拓扑排序']
---

# Medium Demon Problem (hard version)

## 题目描述

这是该问题的困难版本。两个版本之间的关键区别已用粗体强调。

有一群 $n$ 只蜘蛛聚在一起交换毛绒玩具。一开始，每只蜘蛛手里都有一个毛绒玩具。每年，如果第 $i$ 只蜘蛛至少有一个毛绒玩具，它会把自己的一个毛绒玩具送给第 $r_i$ 只蜘蛛。否则，它会选择不做任何事情。注意，所有毛绒玩具的转移同时进行。在这个版本中，每只蜘蛛在任何时候都可以拥有多个毛绒玩具。

如果今年（在进行交换之前）每只蜘蛛拥有的毛绒玩具数量与去年（交换之前）相同，那么这一年就是稳定的。需要注意的是，第一年不可能是稳定的。

请找出施行直到稳定的第一个年份。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示蜘蛛的数量。

接下来的一行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n$（$1 \leq r_i \leq n, r_i \neq i$），表示每只蜘蛛所指定的收件蜘蛛编号。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数代表过程第一次变得稳定的年份。

## 说明/提示

对于第二个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 1, 1, 1, 1]$。由于这个数组与去年相同，所以第二年是稳定的。

对于第三个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 2, 1, 1, 0]$。随后进行第二次交换。
- 第三年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 3, 0, 1, 0]$。随后进行第三次交换。
- 第四年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 4, 0, 0, 0]$。随后进行第四次交换。
- 第五年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 4, 0, 0, 0]$。由于这个阵列与上一年相同，第五年是稳定的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
2 1
5
2 3 4 5 1
5
2 1 4 2 3
5
4 1 1 5 4
10
4 3 9 1 6 7 9 10 10 3
```

### 输出

```
2
2
5
5
5
```



---

---
title: "Fox And Names"
layout: "post"
diff: 普及+/提高
pid: CF510C
tag: ['字符串', '图论建模', '拓扑排序']
---

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ): number of names.

Each of the following $ n $ lines contain one string $ name_{i} $ ( $ 1<=|name_{i}|<=100 $ ), the $ i $ -th name. Each name contains only lowercase Latin letters. All names are different.

## 输出格式

If there exists such order of letters that the given names are sorted lexicographically, output any such order as a permutation of characters 'a'–'z' (i. e. first output the first letter of the modified alphabet, then the second, and so on).

Otherwise output a single word "Impossible" (without quotes).

## 样例 #1

### 输入

```
3
rivest
shamir
adleman

```

### 输出

```
bcdefghijklmnopqrsatuvwxyz

```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever

```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz

```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck

```

### 输出

```
acbdefhijklmnogpqrstuvwxyz

```



---

---
title: "Coprocessor"
layout: "post"
diff: 普及+/提高
pid: CF909E
tag: ['排序', '拓扑排序', '队列']
---

# Coprocessor

## 题目描述

给你 $N$ 个任务，任务从 $0$ 开始标号，有些只能用主处理器处理，另外的任务只能用副处理器处理。其中存在 $M$ 个依赖关系，如果任务 $i$ 依赖于任务 $j$，那么称 $j$ 是 $i$ 的前继任务。

主处理器和副处理器都可以一次处理很多个任务。一个任务能被处理的条件为其所有的前继任务已经被执行过了，或者前继任务和自己同时被放进同一个处理器处理。


现在给出这些依赖关系和每个任务处理要用的处理器，求副处理器最少运行了几次。保证依赖关系是一张有向无环图。

## 输入格式

第一行输入两个非负整数 $N, M\ (1 \le N \le 10 ^ 5,\ 0 \le M \le 10 ^ 5)$。

接下来输入一行 $N$ 个整数 $E _ i\ (E _ i \in \{0, 1\})$，若 $E _ i = 0$ 则表示任务 $i$ 只能在主处理器上运行，否则其只能在副处理器上运行。

接下来 $M$ 行，每行两个非负整数 $T _ 1, T _ 2\ (0 \le T _ i < n,\ T _ 1 \ne T _ 2)$，表示任务 $T _ 1$ 依赖于任务 $T _ 2$。

## 输出格式

一行一个整数表示答案。

感谢 @Styx  提供的翻译。

## 样例 #1

### 输入

```
4 3
0 1 0 1
0 1
1 2
2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
1 1 1 0
0 1
0 2
3 0

```

### 输出

```
1

```



---

---
title: "Almost Acyclic Graph"
layout: "post"
diff: 普及+/提高
pid: CF915D
tag: ['枚举', '排序', '拓扑排序']
---

# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=500 $ , $ 1<=m<=min(n(n-1),100000) $ ) — the number of vertices and the number of edges, respectively.

Then $ m $ lines follow. Each line contains two integers $ u $ and $ v $ denoting a directed edge going from vertex $ u $ to vertex $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ). Each ordered pair $ (u,v) $ is listed at most once (there is at most one directed edge from $ u $ to $ v $ ).

## 输出格式

If it is possible to make this graph acyclic by removing at most one edge, print YES. Otherwise, print NO.

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5

```

### 输出

```
NO

```



---

---
title: "Divide by three, multiply by two"
layout: "post"
diff: 普及+/提高
pid: CF977D
tag: ['搜索', '拓扑排序', '哈希 hashing']
---

# Divide by three, multiply by two

## 题目描述

有一个长度为 $n$ 的数列 $a_i$，要求你将这个数列重排成一个排列 $p_i$，使得对于任意的 $p_i(1 \le i < n)$：



- $p_i \times 2 = p_{i+1}$，或者

- 当 $p_i$ 可以被 $3$ 整除时，$p_i \div 3 = p_{i+1}$。



保证答案存在。

## 输入格式

输入包含两行。



第一行一个整数 $n(2 \le n \le 100)$，表示数列中的元素个数。  

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n (1 \le a_i \le 10^{18})$，描述这个数列。

## 输出格式

输出应包含 $n$ 个整数 $p_1, p_2, \dots, p_n$，表示你的答案。

## 说明/提示

在第一个样例中，一种可能的合法排列为 $[9,3,6,12,4,8]$。

## 样例 #1

### 输入

```
6
4 8 6 3 12 9

```

### 输出

```
9 3 6 12 4 8 

```

## 样例 #2

### 输入

```
4
42 28 84 126

```

### 输出

```
126 42 84 28 

```

## 样例 #3

### 输入

```
2
1000000000000000000 3000000000000000000

```

### 输出

```
3000000000000000000 1000000000000000000 

```



---

