---
title: "Chat Screenshots"
layout: "post"
diff: 普及/提高-
pid: CF1931F
tag: ['拓扑排序']
---

# Chat Screenshots

## 题目描述

There are $ n $ people in the programming contest chat. Chat participants are ordered by activity, but each person sees himself at the top of the list.

For example, there are $ 4 $ participants in the chat, and their order is $ [2, 3, 1, 4] $ . Then

- $ 1 $ -st user sees the order $ [1, 2, 3, 4] $ .
- $ 2 $ -nd user sees the order $ [2, 3, 1, 4] $ .
- $ 3 $ -rd user sees the order $ [3, 2, 1, 4] $ .
- $ 4 $ -th user sees the order $ [4, 2, 3, 1] $ .

 $ k $ people posted screenshots in the chat, which show the order of participants shown to this user. The screenshots were taken within a short period of time, and the order of participants has not changed.

Your task is to determine whether there is a certain order that all screenshots correspond to.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of input test cases. The descriptions of test cases follow.

The first line of the description of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5, n \cdot k \le 2 \cdot 10^5 $ ) — the number of chat participants and the number of participants who posted screenshots.

The following $ k $ lines contain descriptions of screenshots posted by the participants.

The $ i $ -th row contains $ n $ integers $ a_{ij} $ each ( $ 1 \le a_{ij} \le n $ , all $ a_{ij} $ are different) — the order of participants shown to the participant $ a_{i0} $ , where $ a_{i0} $ — the author of the screenshot. You can show that in the screenshot description it will always be at the top of the list.

It is guaranteed that the sum of $ n \cdot k $ for all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed that all the authors of the screenshots are different.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As an answer, output "YES" if there exists at least one order of participants, under which all $ k $ screenshots could have been obtained. Otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
10
5 1
1 2 3 4 5
4 4
1 2 3 4
2 3 1 4
3 2 1 4
4 2 3 1
6 2
1 3 5 2 4 6
6 3 5 2 1 4
3 3
1 2 3
2 3 1
3 2 1
10 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
1 1
1
5 2
1 2 3 5 4
2 1 3 5 4
3 3
3 1 2
2 3 1
1 3 2
5 4
3 5 1 4 2
2 5 1 4 3
1 5 4 3 2
5 1 4 3 2
3 3
1 3 2
2 1 3
3 2 1
```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO
```



---

---
title: "Medium Demon Problem (easy version)"
layout: "post"
diff: 普及/提高-
pid: CF2044G1
tag: ['拓扑排序']
---

# Medium Demon Problem (easy version)

## 题目描述

这是问题的简化版。两个版本之间的关键区别以粗体显著标出。

有一群 $n$ 只蜘蛛聚在一起交换他们的毛绒玩具。最初，每只蜘蛛都有 $1$ 个毛绒玩具。每年，如果第 $i$ 只蜘蛛拥有至少一个毛绒玩具，它就会给第 $r_i$ 只蜘蛛一个毛绒玩具。否则，它将不会进行任何操作。注意，所有的毛绒玩具转移是同时进行的。在这个版本中，如果一只蜘蛛在任意时刻拥有超过 $1$ 个毛绒玩具，它们会丢掉多余的，只保留一个。

如果在某年开始时，每只蜘蛛拥有的毛绒玩具数量与上一年相同，则这一年的过程是稳定的。请注意，第 $1$ 年永远不会是稳定的。

请找出该过程中首次出现稳定的年份。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

每个测试用例的第一行输入一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示蜘蛛的数量。

接下来的第二行输入 $n$ 个整数 $r_1, r_2, \ldots, r_n$（$1 \leq r_i \leq n, r_i \neq i$），表示每只蜘蛛的毛绒玩具接收者。

保证所有测试用例中的 $n$ 总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每一个测试用例，请在新的一行输出一个整数，表示过程首次达到稳定的年份。

## 说明/提示

对于第二个测试用例：

- 在第 $1$ 年，每只蜘蛛的毛绒玩具数量为 $[1, 1, 1, 1, 1]$。然后进行当年的交换。
- 到了第 $2$ 年，各蜘蛛的毛绒玩具数量仍然为 $[1, 1, 1, 1, 1]$。由于数量没有变化，因此这一年是稳定的。

对于第三个测试用例：

- 在第 $1$ 年，所有蜘蛛的毛绒玩具数量为 $[1, 1, 1, 1, 1]$。然后进行第 $1$ 年的交换。
- 在第 $2$ 年，这些数量变为 $[1, 1, 1, 1, 0]$ 。然后进行第 $2$ 年的交换。即便有两只蜘蛛给了第 $2$ 只蜘蛛毛绒玩具，第 $2$ 只蜘蛛也只能保留一个。
- 到第 $3$ 年，数量变为 $[1, 1, 0, 1, 0]$。然后进行交换。
- 第 $4$ 年，数量变为 $[1, 1, 0, 0, 0]$。然后进行交换。
- 第 $5$ 年，数量仍然为 $[1, 1, 0, 0, 0]$。由于数量保持不变，这一年是稳定的。

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
4
5
```



---

---
title: "Substring"
layout: "post"
diff: 普及/提高-
pid: CF919D
tag: ['排序', '拓扑排序']
---

# Substring

## 题目描述

You are given a graph with $ n $ nodes and $ m $ directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is $ 3 $ . Your task is find a path whose value is the largest.

## 输入格式

The first line contains two positive integers $ n,m $ ( $ 1<=n,m<=300000 $ ), denoting that the graph has $ n $ nodes and $ m $ directed edges.

The second line contains a string $ s $ with only lowercase English letters. The $ i $ -th character is the letter assigned to the $ i $ -th node.

Then $ m $ lines follow. Each line contains two integers $ x,y $ ( $ 1<=x,y<=n $ ), describing a directed edge from $ x $ to $ y $ . Note that $ x $ can be equal to $ y $ and there can be multiple edges between $ x $ and $ y $ . Also the graph can be not connected.

## 输出格式

Output a single line with a single integer denoting the largest value. If the value can be arbitrarily large, output -1 instead.

## 说明/提示

In the first sample, the path with largest value is $ 1→3→4→5 $ . The value is $ 3 $ because the letter 'a' appears $ 3 $ times.

## 样例 #1

### 输入

```
5 4
abaca
1 2
1 3
3 4
4 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6 6
xzyabc
1 2
3 1
2 3
5 4
4 3
6 4

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
10 14
xzyzyzyzqx
1 2
2 4
3 5
4 5
2 6
6 8
6 5
2 10
3 9
10 9
4 6
1 10
2 8
3 7

```

### 输出

```
4

```



---

