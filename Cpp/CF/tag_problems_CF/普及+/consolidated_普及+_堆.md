---
title: "Lunar New Year and a Wander"
layout: "post"
diff: 普及+/提高
pid: CF1106D
tag: ['堆']
---

# Lunar New Year and a Wander

## 题目描述

Lunar New Year is approaching, and Bob decides to take a wander in a nearby park.

The park can be represented as a connected graph with $ n $ nodes and $ m $ bidirectional edges. Initially Bob is at the node $ 1 $ and he records $ 1 $ on his notebook. He can wander from one node to another through those bidirectional edges. Whenever he visits a node not recorded on his notebook, he records it. After he visits all nodes at least once, he stops wandering, thus finally a permutation of nodes $ a_1, a_2, \ldots, a_n $ is recorded.

Wandering is a boring thing, but solving problems is fascinating. Bob wants to know the lexicographically smallest sequence of nodes he can record while wandering. Bob thinks this problem is trivial, and he wants you to solve it.

A sequence $ x $ is lexicographically smaller than a sequence $ y $ if and only if one of the following holds:

- $ x $ is a prefix of $ y $ , but $ x \ne y $ (this is impossible in this problem as all considered sequences have the same length);
- in the first position where $ x $ and $ y $ differ, the sequence $ x $ has a smaller element than the corresponding element in $ y $ .

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 10^5 $ ), denoting the number of nodes and edges, respectively.

The following $ m $ lines describe the bidirectional edges in the graph. The $ i $ -th of these lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ ), representing the nodes the $ i $ -th edge connects.

Note that the graph can have multiple edges connecting the same two nodes and self-loops. It is guaranteed that the graph is connected.

## 输出格式

Output a line containing the lexicographically smallest sequence $ a_1, a_2, \ldots, a_n $ Bob can record.

## 说明/提示

In the first sample, Bob's optimal wandering path could be $ 1 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ . Therefore, Bob will obtain the sequence $ \{1, 2, 3\} $ , which is the lexicographically smallest one.

In the second sample, Bob's optimal wandering path could be $ 1 \rightarrow 4 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 5 $ . Therefore, Bob will obtain the sequence $ \{1, 4, 3, 2, 5\} $ , which is the lexicographically smallest one.

## 样例 #1

### 输入

```
3 2
1 2
1 3

```

### 输出

```
1 2 3 

```

## 样例 #2

### 输入

```
5 5
1 4
3 4
5 4
3 2
1 5

```

### 输出

```
1 4 3 2 5 

```

## 样例 #3

### 输入

```
10 10
1 4
6 8
2 5
3 7
9 4
5 6
3 4
8 10
8 9
1 10

```

### 输出

```
1 4 3 7 9 8 6 5 2 10 

```



---

---
title: "Fibonacci Strings"
layout: "post"
diff: 普及+/提高
pid: CF1718B
tag: ['贪心', '堆']
---

# Fibonacci Strings

## 题目描述

In all schools in Buryatia, in the $ 1 $ class, everyone is told the theory of Fibonacci strings.

"A block is a subsegment of a string where all the letters are the same and are bounded on the left and right by the ends of the string or by letters other than the letters in the block. A string is called a Fibonacci string if, when it is divided into blocks, their lengths in the order they appear in the string form the Fibonacci sequence ( $ f_0 = f_1 = 1 $ , $ f_i = f_{i-2} + f_{i-1} $ ), starting from the zeroth member of this sequence. A string is called semi-Fibonacci if it possible to reorder its letters to get a Fibonacci string."

Burenka decided to enter the Buryat State University, but at the entrance exam she was given a difficult task. She was given a string consisting of the letters of the Buryat alphabet (which contains exactly $ k $ letters), and was asked if the given string is semi-Fibonacci. The string can be very long, so instead of the string, she was given the number of appearances of each letter ( $ c_i $ for the $ i $ -th letter) in that string. Unfortunately, Burenka no longer remembers the theory of Fibonacci strings, so without your help she will not pass the exam.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The following is a description of the input data sets.

The first line of each test case contains one integer $ k $ ( $ 1 \leq k \leq 100 $ ) — the number of letters in the alphabet.

The second line of each test case contains $ k $ integers $ c_1, c_2, \ldots, c_k $ ( $ 1 \leq c_i \leq 10^9 $ ) — the number of occurrences of each letter in the string.

## 输出格式

For each test case print the string "YES" if the corresponding string is semi-Fibonacci, and "NO" if it is not.

You can print "YES" and "NO" in any case (for example, the strings "yEs", "yes", "Yes" will be recognized as a positive answer).

## 说明/提示

In the first test case, a one-character string is semi-Fibonacci, being itself a Fibonacci string.

In the second test case, a string of two different characters is Fibonacci.

In the third test case, the string "abb" (let the first of the alphabet letter be a, the second letter b) is not a semi-Fibonacci string, since no permutation of its letters ("abb", "bab", and "bba") is a Fibonacci string.

In the fourth test case, two permutations of the letters of the string "abaccac" (the first letter is a, the second letter is b, the third letter is c) are Fibonacci strings — "abaaccc" and "cbccaaa".

## 样例 #1

### 输入

```
6
1
1
2
1 1
2
1 2
3
3 1 3
2
7 5
6
26 8 3 4 13 34
```

### 输出

```
YES
YES
NO
YES
NO
YES
```



---

---
title: "Kirill and Mushrooms"
layout: "post"
diff: 普及+/提高
pid: CF1945F
tag: ['线段树', '堆']
---

# Kirill and Mushrooms

## 题目描述

当营地里的每个人都进入梦乡后，基里尔便偷偷溜出帐篷，到智慧的橡树下采蘑菇。

众所周知，橡树下生长着 $n$ 朵蘑菇，每朵蘑菇都有 $v_i$ 的魔力。 基里尔非常想用这些蘑菇制作一种魔力最大的灵药。

灵药的强度等于其中蘑菇的数量与这些蘑菇中最小魔力的乘积。要配制灵药，基里尔要依次采摘生长在橡树下的蘑菇。基里尔可以按照任何顺序采集蘑菇。

然而，事情并非如此简单。智慧的橡树给出了一个排列 $p_1,p_2,...,p_n$，如果基里尔只采摘 $k$ 朵蘑菇，那么 $v_{p_1},v_{p_2},...,v_{p_{k-1}}$ 都将变为 $0$。 基里尔不会使用魔力为零的蘑菇来配制灵药。

你的任务是帮助基里尔采集蘑菇，使他能够酿造出最大魔力的灵药。然而，基里尔有点害怕在橡树旁待太久，所以在所有适合采集蘑菇的方案中，他要求你找到蘑菇数量最少的那个。

## 输入格式

每个数据包含多个测试用例。

第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ ) ，表示测试用例的数量。

每个测试用例的第一行都包含一个整数 $n$（$1 \le n \le 2\cdot 10^5$），表示蘑菇的数量。

第二行包含一个大小为 $n$ 的数组 $v$（$1\le v_i \le 10^9$），表示蘑菇的魔力。

第三行包含一个长度为 $n$ 的排列 $p$。

保证所有测试用例中的 $n$ 的值之和不超过 $2\cdot 10^5$。

## 输出格式

对于每个测试用例，输出两个用空格隔开的整数，分别为可以酿造的灵药的最大浓度和基里尔为此需要使用的最少蘑菇数量。

## 说明/提示

在样例的第一个测试用例中，你需要采摘前两朵蘑菇，因此灵药的魔力等于 $2 \cdot \min(a_1, a_2) = 2 \cdot \min(9, 8) = 2 \cdot 8 = 16$。 请注意，采摘两朵蘑菇后，第三朵蘑菇的魔力将变为 $0$。

## 样例 #1

### 输入

```
6
3
9 8 14
3 2 1
5
1 2 3 4 5
1 2 3 4 5
6
1 2 3 4 5 6
6 5 4 3 2 1
5
1 4 6 10 10
2 1 4 5 3
4
2 2 5 5
4 2 3 1
5
1 2 9 10 10
1 4 2 3 5
```

### 输出

```
16 2
9 3
8 2
20 2
5 1
20 2
```



---

---
title: "Cook and Porridge"
layout: "post"
diff: 普及+/提高
pid: CF1945G
tag: ['模拟', '堆']
---

# Cook and Porridge

## 题目描述

Finally, lunchtime!

 $ n $ schoolchildren have lined up in a long queue at the cook's tent for porridge. The cook will be serving porridge for $ D $ minutes. The schoolchild standing in the $ i $ -th position in the queue has a priority of $ k_i $ and eats one portion of porridge in $ s_i $ minutes.

At the beginning of each minute of the break, the cook serves the first schoolchild in the queue one portion of porridge, after which the schoolchild goes to eat their portion. If the $ i $ -th schoolchild is served a portion at the beginning of the $ x $ -th minute, then they will return to the queue at the end of the $ (x + s_i) $ -th minute.

When the $ i $ -th schoolchild returns to the queue, the schoolchildren at the end of the queue whose priority is strictly lower than that of the $ i $ -th schoolchild must let them pass. Thus, they will stand in the queue behind the last schoolchild whose priority is not lower than their own. That is, behind the last schoolchild $ j $ with $ k_j \ge k_i $ . If there is no such schoolchild in the queue, the $ i $ -th schoolchild will stand at the front of the queue.

If several schoolchildren return at the same time, they will return to the queue in ascending order of their $ s_i $ .

For example, if $ n = 3 $ , $ D = 3 $ , $ k = [2, 3, 2] $ , and $ s = [2, 1, 3] $ , the serving will occur as follows:

- At the beginning of minute $ 1 $ , the students in the queue are $ [1, 2, 3] $ , and student $ 1 $ is served porridge;
- at the beginning of minute $ 2 $ , the students in the queue are $ [2, 3] $ , and student $ 2 $ is served porridge;
- at the beginning of minute $ 3 $ , the student in the queue is $ [3] $ , and student $ 3 $ is served porridge;
- at the end of minute $ 3 $ , student $ 2 $ returns to the queue, and the queue becomes $ [2] $ ;
- at the end of minute $ 3 $ , student $ 1 $ returns to the queue, and the queue becomes $ [2, 1] $ , as his priority is lower.

Determine the minimum number of minutes after the start of the break that each schoolchild will receive porridge at least once, or report that this will not happen within $ D $ minutes.

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. This is followed by a description of the test cases.

The first line of each test case contains two integers $ n $ and $ D $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le D \le 3\cdot 10^5 $ ) — the number of schoolchildren in the queue and the break time, respectively.

The next $ n $ lines contain two integers $ k_i $ and $ s_i $ ( $ 1 \le k_i, s_i, \le 10^9 $ ) — the priority and the time to eat one portion of porridge for the respective schoolchild. The schoolchildren are given in the order they stand in the queue (from the front to the end).

It is guaranteed that the sum of the values of $ n $ for all input data sets does not exceed $ 2\cdot 10^5 $ . Similarly, it is guaranteed that the sum of the values of $ D $ for all input data sets does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of minutes after which each schoolchild will receive porridge at least once. If this does not happen within the break time, output $ -1 $ .

## 样例 #1

### 输入

```
7
3 3
2 2
3 1
2 3
5 10
10 3
7 1
11 3
5 1
6 1
5 20
4 2
7 2
8 5
1 5
3 1
5 17
1 3
8 2
8 3
2 2
1 1
5 14
8 2
4 2
1 3
8 3
6 4
1 11
4 5
5 14
8 2
4 2
1 3
8 3
6 4
```

### 输出

```
3
-1
12
6
6
1
6
```



---

---
title: "Shop Game"
layout: "post"
diff: 普及+/提高
pid: CF1969D
tag: ['贪心', '堆']
---

# Shop Game

## 题目描述

Alice 和 Bob 正在商店里玩游戏。商店里有 $n$ 件商品；每件商品有两个参数： $a_i$（Alice 买进的物品价格）和 $b_i$（愿意出的物品价格）。

Alice 希望选择一个商品子集（可能是空）并购买它们。之后，Bob 会执行以下操作：

- 如果 Alice 购买的物品少于 $k$，Bob 可以免费拿走所有物品；
- 否则，他会免费拿走 Alice 购买的 $k$ 个物品（由 Bob 选择是哪些 $k$ 个物品），至于其他被选中的物品，Bob 会从 Alice 那里购买，并为 $i$ 号物品支付 $b_i$。

Alice 的利润等于 $\sum\limits_{i\in S}b_i-\sum\limits_{j \in T}a_j$，其中 $S$ 是 Bob 从 Alice 处购买的物品集，$T$ 是 Alice 从商店购买的物品集。换句话说，Alice 的利润就是 Bob 支付给她的金额和她购买商品所花费的金额之间的差额。

Alice 希望自己的利润最大化，而 Bob 希望 Alice 的利润最小化。您的任务是计算在 Alice 和 Bob 都采取最优行动的情况下 Alice 的利润。

## 输入格式

第一行包含一个整数 $ t $ （ $ 1 \le t \le 10^4 $ )——测试用例的数量。

每个测试用例的第一行包含两个整数 $ n $ 和 $ k $ （ $ 1 \le n \le 2 \cdot 10^5 $，$ 0 \le k \le n $ ）。

第二行包含 $ n $ 整数 $ a_1, a_2, \dots, a_n $ （ $ 1 \le a_i \le 10^9 $ ）。

第三行包含 $ n $ 整数 $ b_1, b_2, \dots, b_n $ （ $ 1 \le b_i \le 10^9 $ ）。

## 输出格式

对于每个测试用例，打印一个整数——如果Alice和Bob都采取最优行为，则Alice的利润。

## 说明/提示

在第一个测试用例中，Alice应该购买 $ 2 $ 然后把它卖给鲍勃，那么她的利润是 $ 2 - 1 = 1 $ 。

在第二个测试用例中，Alice应该购买 $ 1 $，$ 2 $ 和 $ 3 $ 项；然后鲍勃可以接受 $ 1 $ 免费，并支付 $ 2 $ 和 $ 3 $ 。Alice的利润是 $ (3+2) - (1+2+1) = 1 $ 。鲍勃也可以接受 $ 2 $ 为免费的物品，这不会改变Alice的利润。鲍勃不会接受 $ 3 $ 为免费的物品，因为这样 Alice 的利润为 $ 2 $。

## 样例 #1

### 输入

```
4
2 0
2 1
1 2
4 1
1 2 1 4
3 3 2 3
4 2
2 1 1 1
4 2 3 2
6 2
1 3 4 9 1 3
7 6 8 10 6 8
```

### 输出

```
1
1
0
7
```



---

---
title: "Serval and Kaitenzushi Buffet"
layout: "post"
diff: 普及+/提高
pid: CF2085D
tag: ['贪心', '堆']
---

# Serval and Kaitenzushi Buffet

## 题目描述

Serval 发现了一家回转寿司自助餐厅。回转寿司意味着餐厅内有一条传送带，将寿司盘依次传送到顾客 Serval 面前。

在这家餐厅中，每盘寿司恰好包含 $k$ 块寿司，第 $i$ 盘寿司的美味值为 $d_i$。Serval 将在这家餐厅用餐 $n$ 分钟，且在这 $n$ 分钟内必须吃完他从传送带上拿取的所有寿司块。

设未食用的已拿取寿司块计数器为 $r$。初始时 $r = 0$。在第 $i$ 分钟（$1 \leq i \leq n$），只有第 $i$ 盘寿司会被传送到 Serval 面前，他可以执行以下三种操作之一：
- 从传送带上拿取第 $i$ 盘寿司（其美味值为 $d_i$），此时 $r$ 增加 $k$；
- 食用之前从传送带上拿取的 1 块未食用寿司，此时 $r$ 减少 $1$（注意仅当 $r > 0$ 时可执行此操作）；
- 或不做任何操作，此时 $r$ 保持不变。

注意在 $n$ 分钟结束后，$r$ 的值必须为 $0$。

Serval 希望最大化他拿取的所有寿司盘的美味值之和。请帮助他计算这个最大值！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \leq k < n \leq 2 \cdot 10^5$）——用餐的总分钟数及每盘寿司的块数。

第二行包含 $n$ 个整数 $d_1, d_2, \ldots, d_n$（$1 \leq d_i \leq 10^9$）——每盘寿司的美味值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— Serval 拿取的所有寿司盘美味值的最大可能和。

## 说明/提示

第一个测试案例中，可以证明 Serval 最多能吃完一盘寿司。由于第二盘寿司的美味值 $6$ 是所有盘中最大的，他会在第二分钟拿取该盘，并在接下来的 $2$ 分钟内吃完它。

| 分钟 | 1 | 2 | 3 | 4 | 5 |
|------|---|---|---|---|---|
| 操作 | — | 拿取 | 食用 | 食用 | — |
| 操作后 $r$ | 0 | 2 | 1 | 0 | 0 |
| 累计美味值 | 0 | 6 | 6 | 6 | 6 |

第二个测试案例中，可以证明最优策略是拿取第一、第三和第六盘寿司。这些盘的美味值之和为 $3 + 4 + 9 = 16$。

| 分钟 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|------|---|---|---|---|---|---|---|
| 操作 | 拿取 | 食用 | 拿取 | 食用 | — | 拿取 | 食用 |
| 操作后 $r$ | 1 | 0 | 1 | 0 | 0 | 1 | 0 |
| 累计美味值 | 3 | 3 | 7 | 7 | 7 | 16 | 16 |

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
5 2
3 6 4 1 2
7 1
3 1 4 1 5 9 2
4 3
4 3 2 1
6 2
1 3 5 2 4 6
6 1
1000000000 1 1000000000 1 1000000000 1
```

### 输出

```
6
16
4
6
3000000000
```



---

---
title: "Dining Hall"
layout: "post"
diff: 普及+/提高
pid: CF2090C
tag: ['贪心', '堆']
---

# Dining Hall

## 题目描述

在一个庞大的王国中，有一个无限大的餐厅。

该餐厅可以表示为由单元格 $(x, y)$ 构成的集合，其中 $x, y$ 是自然数。餐厅内还有无数张桌子。每张桌子由四个单元格定义：$(3x + 1, 3y + 1)$、$(3x + 1, 3y + 2)$、$(3x + 2, 3y + 1)$、$(3x + 2, 3y + 2)$，其中 $x, y$ 是非负整数。所有不属于任何桌子的单元格被视为走廊。

客人只能在走廊中移动，且每次只能通过相邻的边移动到相邻的单元格，每次移动耗时相同。注意：客人只能在最后一次移动时坐在桌子上，且必须坐在桌子上。

在王国的一场晚宴中，共有 $n$ 位客人到来，每位客人有一个特征值 $t_i$（取值为 $0$ 或 $1$）。他们按顺序进入大厅，从单元格 $(0, 0)$ 出发走向某张桌子。若第 $i$ 位客人的 $t_i = 1$，则他会选择距离最近的仍有空位的桌子；若 $t_i = 0$，则他会选择距离最近的未被占用的桌子（即使后续可能有其他客人加入）。若存在多张桌子距离相同，则选择 $x$ 坐标最小的单元格；若仍有多个选项，则选择其中 $y$ 坐标最小的单元格。

从单元格到桌子的距离定义为到该桌子上最近的未被占用的单元格的距离。两单元格之间的距离按移动到相邻单元格的次数计算。注意：移动过程中不允许穿过属于桌子的单元格，除非是最后一步（该步骤会将你放置在桌子的最终单元格上）。

为更好理解条件，可参考说明中的图示。

你无需亲自计算所有客人的入座情况，请直接输出每位客人最终入座的单元格。

## 输入格式

第一行包含一个整数 $q$（$1 \leq q \leq 5000$）——测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 50\,000$）——客人数量。

每个测试用例的第二行包含 $n$ 个整数 $t_1, t_2, \ldots, t_n$（$t_i \in \{0, 1\}$）——每位客人的特征值。

保证所有测试用例的 $n$ 之和不超过 $50\,000$。


## 输出格式

对于每个测试用例，输出 $n$ 行——每位客人入座的单元格。

## 说明/提示

第一位客人到单元格 $(1, 1)$ 的距离为 2，因此选择该位置。

第二位客人到单元格 $(1, 2)$ 和 $(2, 1)$ 的距离均为 3，但由于 $1 < 2$，因此选择 $(1, 2)$。无额外约束。

第三位客人到单元格 $(2, 1)$ 的距离为 3，因此选择该位置。

第四位客人到单元格 $(1, 4)$ 的距离为 5，因此选择该位置。

第五位客人到单元格 $(4, 1)$ 的距离为 5。

第六位客人到单元格 $(1, 5)$ 和 $(2, 2)$ 的距离均为 6，但由于 $x$ 坐标更小，因此选择 $(1, 5)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2090C/14307747f44bf893a0cb5c3731d43642a649f3b9.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
6
0 1 1 0 0 1
5
1 0 0 1 1
```

### 输出

```
1 1
1 2
2 1
1 4
4 1
1 5
1 1
1 4
4 1
1 2
2 1
```



---

