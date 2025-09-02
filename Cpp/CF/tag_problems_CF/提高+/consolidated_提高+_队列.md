---
title: "Trips"
layout: "post"
diff: 提高+/省选-
pid: CF1037E
tag: ['搜索', '队列']
---

# Trips

## 题目描述

**题目大意：**

一共有$n$个人，他们开始互不认识，而每天早上不认识的两个人会变成朋友。一共有$m$天，每天晚上有的人要去旅行，去旅行的人必须满足ta有至少$k$个朋友也去旅行

求每天去旅行的最大人数

## 输入格式

第一行3个整数，表示$n,m,k$

往下m行，每行两个整数$x,y$，表示这天早上$x$和$y$会变成朋友

## 输出格式

共$m$行，每行一个整数，表示每天晚上最多能去旅游的人数

## 样例 #1

### 输入

```
4 4 2
2 3
1 2
1 3
1 4

```

### 输出

```
0
0
3
3

```

## 样例 #2

### 输入

```
5 8 2
2 1
4 2
5 4
5 2
4 3
5 1
4 1
3 2

```

### 输出

```
0
0
0
3
3
4
4
5

```

## 样例 #3

### 输入

```
5 7 2
1 5
3 2
2 5
3 4
1 2
5 3
1 3

```

### 输出

```
0
0
0
0
3
4
4

```



---

---
title: "New Year Snowmen"
layout: "post"
diff: 提高+/省选-
pid: CF140C
tag: ['离散化', '优先队列', '队列']
---

# New Year Snowmen

## 题目描述

As meticulous Gerald sets the table and caring Alexander sends the postcards, Sergey makes snowmen. Each showman should consist of three snowballs: a big one, a medium one and a small one. Sergey's twins help him: they've already made $ n $ snowballs with radii equal to $ r_{1} $ , $ r_{2} $ , ..., $ r_{n} $ . To make a snowman, one needs any three snowballs whose radii are pairwise different. For example, the balls with radii $ 1 $ , $ 2 $ and $ 3 $ can be used to make a snowman but $ 2 $ , $ 2 $ , $ 3 $ or $ 2 $ , $ 2 $ , $ 2 $ cannot. Help Sergey and his twins to determine what maximum number of snowmen they can make from those snowballs.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of snowballs. The next line contains $ n $ integers — the balls' radii $ r_{1} $ , $ r_{2} $ , ..., $ r_{n} $ ( $ 1<=r_{i}<=10^{9} $ ). The balls' radii can coincide.

## 输出格式

Print on the first line a single number $ k $ — the maximum number of the snowmen. Next $ k $ lines should contain the snowmen's descriptions. The description of each snowman should consist of three space-separated numbers — the big ball's radius, the medium ball's radius and the small ball's radius. It is allowed to print the snowmen in any order. If there are several solutions, print any of them.

## 样例 #1

### 输入

```
7
1 2 3 4 5 6 7

```

### 输出

```
2
3 2 1
6 5 4

```

## 样例 #2

### 输入

```
3
2 2 3

```

### 输出

```
0

```



---

---
title: "Kuzya and Homework"
layout: "post"
diff: 提高+/省选-
pid: CF1582G
tag: ['单调队列', '素数判断,质数,筛法']
---

# Kuzya and Homework

## 题目描述

Kuzya started going to school. He was given math homework in which he was given an array $ a $ of length $ n $ and an array of symbols $ b $ of length $ n $ , consisting of symbols '\*' and '/'.

Let's denote a path of calculations for a segment $ [l; r] $ ( $ 1 \le l \le r \le n $ ) in the following way:

- Let $ x=1 $ initially. For every $ i $ from $ l $ to $ r $ we will consequently do the following: if $ b_i= $ '\*', $ x=x*a_i $ , and if $ b_i= $ '/', then $ x=\frac{x}{a_i} $ . Let's call a path of calculations for the segment $ [l; r] $ a list of all $ x $ that we got during the calculations (the number of them is exactly $ r - l + 1 $ ).

For example, let $ a=[7, $ $ 12, $ $ 3, $ $ 5, $ $ 4, $ $ 10, $ $ 9] $ , $ b=[/, $ $ *, $ $ /, $ $ /, $ $ /, $ $ *, $ $ *] $ , $ l=2 $ , $ r=6 $ , then the path of calculations for that segment is $ [12, $ $ 4, $ $ 0.8, $ $ 0.2, $ $ 2] $ .

Let's call a segment $ [l;r] $ simple if the path of calculations for it contains only integer numbers.

Kuzya needs to find the number of simple segments $ [l;r] $ ( $ 1 \le l \le r \le n $ ). Since he obviously has no time and no interest to do the calculations for each option, he asked you to write a program to get to find that number!

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ).

The third line contains $ n $ symbols without spaces between them — the array $ b_1, b_2 \ldots b_n $ ( $ b_i= $ '/' or $ b_i= $ '\*' for every $ 1 \le i \le n $ ).

## 输出格式

Print a single integer — the number of simple segments $ [l;r] $ .

## 样例 #1

### 输入

```
3
1 2 3
*/*
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
6 4 10 1 2 15 1
*/*/*//
```

### 输出

```
8
```



---

---
title: "Non-equal Neighbours"
layout: "post"
diff: 提高+/省选-
pid: CF1585F
tag: ['动态规划 DP', '单调队列', '容斥原理']
---

# Non-equal Neighbours

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . Your task is to calculate the number of arrays of $ n $ positive integers $ b_1, b_2, \ldots, b_n $ such that:

- $ 1 \le b_i \le a_i $ for every $ i $ ( $ 1 \le i \le n $ ), and
- $ b_i \neq b_{i+1} $ for every $ i $ ( $ 1 \le i \le n - 1 $ ).

The number of such arrays can be very large, so print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print the answer modulo $ 998\,244\,353 $ in a single line.

## 说明/提示

In the first test case possible arrays are $ [1, 2, 1] $ and $ [2, 1, 2] $ .

In the second test case possible arrays are $ [1, 2] $ , $ [1, 3] $ , $ [2, 1] $ and $ [2, 3] $ .

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
0
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
title: "Least Cost Bracket Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF3D
tag: ['字符串', '优先队列', '队列']
---

# Least Cost Bracket Sequence

## 题目描述

This is yet another problem on regular bracket sequences.

A bracket sequence is called regular, if by inserting "+" and "1" into it we get a correct mathematical expression. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not. You have a pattern of a bracket sequence that consists of characters "(", ")" and "?". You have to replace each character "?" with a bracket so, that you get a regular bracket sequence.

For each character "?" the cost of its replacement with "(" and ")" is given. Among all the possible variants your should choose the cheapest.

## 输入格式

The first line contains a non-empty pattern of even length, consisting of characters "(", ")" and "?". Its length doesn't exceed $ 5·10^{4} $ . Then there follow $ m $ lines, where $ m $ is the number of characters "?" in the pattern. Each line contains two integer numbers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=10^{6} $ ), where $ a_{i} $ is the cost of replacing the $ i $ -th character "?" with an opening bracket, and $ b_{i} $ — with a closing one.

## 输出格式

Print the cost of the optimal regular bracket sequence in the first line, and the required sequence in the second.

Print -1, if there is no answer. If the answer is not unique, print any of them.

## 样例 #1

### 输入

```
(??)
1 2
2 8

```

### 输出

```
4
()()

```



---

---
title: "Exposition"
layout: "post"
diff: 提高+/省选-
pid: CF6E
tag: ['单调队列', '枚举', '期望', '队列']
---

# Exposition

## 题目描述

There are several days left before the fiftieth birthday of a famous Berland's writer Berlbury. In this connection the local library decided to make an exposition of the works of this famous science-fiction writer. It was decided as well that it is necessary to include into the exposition only those books that were published during a particular time period. It is obvious that if the books differ much in size, the visitors will not like it. That was why the organizers came to the opinion, that the difference between the highest and the lowest books in the exposition should be not more than $ k $ millimeters.

The library has $ n $ volumes of books by Berlbury, arranged in chronological order of their appearance. The height of each book in millimeters is know, it is $ h_{i} $ . As Berlbury is highly respected in the city, the organizers want to include into the exposition as many books as possible, and to find out what periods of his creative work they will manage to cover. You are asked to help the organizers cope with this hard task.

## 输入格式

The first line of the input data contains two integer numbers separated by a space $ n $ ( $ 1<=n<=10^{5} $ ) and $ k $ ( $ 0<=k<=10^{6} $ ) — the amount of books by Berlbury in the library, and the maximum allowed height difference between the lowest and the highest books. The second line contains $ n $ integer numbers separated by a space. Each number $ h_{i} $ ( $ 1<=h_{i}<=10^{6} $ ) is the height of the $ i $ -th book in millimeters.

## 输出格式

In the first line of the output data print two numbers $ a $ and $ b $ (separate them by a space), where $ a $ is the maximum amount of books the organizers can include into the exposition, and $ b $ — the amount of the time periods, during which Berlbury published $ a $ books, and the height difference between the lowest and the highest among these books is not more than $ k $ milllimeters.

In each of the following $ b $ lines print two integer numbers separated by a space — indexes of the first and the last volumes from each of the required time periods of Berlbury's creative work.

## 样例 #1

### 输入

```
3 3
14 12 10

```

### 输出

```
2 2
1 2
2 3

```

## 样例 #2

### 输入

```
2 0
10 10

```

### 输出

```
2 1
1 2

```

## 样例 #3

### 输入

```
4 5
8 19 10 13

```

### 输出

```
2 1
3 4

```



---

---
title: "Contest Balloons"
layout: "post"
diff: 提高+/省选-
pid: CF725D
tag: ['模拟', '贪心', '优先队列', '队列']
---

# Contest Balloons

## 题目描述

ACM比赛，大家都知道。AC一题会有一个气球。
现在有$n(2<=n<=300000)$ 支队伍，每支队伍的重量是$w_i$ ，拥有$t_i$ 个气球$(w_i,t_i<=10^{18})$ ，当一支队伍的气球个数比它的重量都要大时，这个队伍就会飘起来，从而被取消比赛资格。
现在你带领的是1号队，你希望你队伍的名次尽可能靠前，你是个有原则的人，不会偷气球，但你可以把气球送给别的队伍，让他们飞起来。
求最终你的队伍所获得的最好名次

## 输入格式

第一行：一个正整数$n(2<=n<=300000)$ ，队伍的总数
第二行到第$n+1$ 行：每行两个整数$t_i,w_i(0<=t_i<=w_i<=10^{18})$ ，分别表示第$i$ 个队伍气球的个数以及它的重量。你的队伍是1号队。

## 输出格式

仅有一行，输出你带领的队伍能够达到的最好名次

感谢@2016wudi 提供的翻译

## 样例 #1

### 输入

```
8
20 1000
32 37
40 1000
45 50
16 16
16 16
14 1000
2 1000

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
4 4
4 4
4 4
4 4
4 4
4 4
5 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
7
14000000003 1000000000000000000
81000000000 88000000000
5000000000 7000000000
15000000000 39000000000
46000000000 51000000000
0 1000000000
0 0

```

### 输出

```
2

```



---

---
title: "Sockets"
layout: "post"
diff: 提高+/省选-
pid: CF732E
tag: ['贪心', '优先队列', '队列']
---

# Sockets

## 题目描述

ICM ACPC 世界决赛就要来临了！不幸的是，赛事组织者因为在准备赛题时太忙碌了，他们几乎忘了一个关键点——为参赛者的工作站准备电力资源。  
  
赛场有 $n$ 台为参赛者准备的电脑，第 $i$ 台电脑拥有与正整数 $p_i$ 相等大小的电源。同时，有 $m$ 个可用的插座，第 $j$ 个插座拥有与正整数 $s_j$ 相等的电源。只有当 $p_i = s_j$ 时才可以将第 $i$ 台电脑和第 $j$ 个插座连接。一台电脑只可以接一个插座。不仅如此，如果所有的电脑与插座的电源都不同，那么没有任何电脑可以接通至插座。  
  
为了解决问题，Puch Williams 教授紧急订购了一车适配器（电源分离器）。每个适配器都有一个插头与一个插座，在它们之间还有一个分压器。在将适配器插入一个带有 $x$ 的电源后，适配器上的插座将会拥有一个 $\left \lceil \frac{x}{2} \right \rceil $ 的电源，这代表着将被插入的插座的电源除以 $2$，再取顶。例如：$\left \lceil \frac{10}{2} \right \rceil =5$，$\left \lceil \frac{15}{2} \right \rceil =8$。  
  
每个适配器只能使用一次。它可以被多次串联。例如，在将一个适配器插入一个插入带有 $10$ 电源的插座的适配器时，可以将一个带有 $3$ 电源的电脑插入这个适配器。  
  
组织者们会安装这些适配器，以确保它会同时输送给最多 $c$ 台电脑。如果有多种连接方案，组织者们想要在连接最多 $c$ 台电脑的前提下，使用最少 $u$ 个适配器的方案。  
  
你的任务是帮助组织者们计算完成这个任务最大的 $c$ 和最小的 $u$。  
  
这一车适配器是足够这个任务使用的，同时数据保证至少可以连接一台电脑。

## 输入格式

第一行包含两个整数 $n$ 和 $m$（$1 \le n,m \le 200000$），分别为电脑的数量和插座的数量。  
第二行包含 $n$ 个整数，$p_1,p_2,\ldots,p_n$（$1 \le p_i \le 10^9$），为电脑的电源。  
第三行包含 $m$ 个整数，$s_1,s_2,\ldots,s_m$（$1 \le s_i \le 10^9$），为插座的电源。

## 输出格式

第一行输出两个数字 $c$ 和 $u$，分别为最多可以连接的电脑数量与最少可以使用的适配器数量。  
第二行输出 $m$ 个数字，$a_1,a_2,\ldots,a_m$（$0 \le a_i \le 10^9$），为插在第 $i$ 个插座上的适配器数量。$a_i$ 的和应等于 $u$。  
第三行输出 $n$ 个数字，$b_1,b_2,\ldots,b_m$（$0 \le b_i \le m$），为第 $j$ 台电脑插入的插座序号。若 $b_j=0$，代表第 $j$ 台电脑不应插入任何插座。当 $b_j\ne 0$ 时，任何 $b_j$ 应不相等。在插入了 $a_{bj}$ 个适配器后，第 $j$ 台电脑的电源应与第 $b_j$ 个插座的电源相等。非 $0$ 的 $b_j$ 的数量应等于 $c$。  
如果有多组答案，请输出任意一组。

## 样例 #1

### 输入

```
2 2
1 1
2 2

```

### 输出

```
2 2
1 1
1 2

```

## 样例 #2

### 输入

```
2 1
2 100
99

```

### 输出

```
1 6
6
1 0

```



---

---
title: "Buy Low Sell High"
layout: "post"
diff: 提高+/省选-
pid: CF865D
tag: ['贪心', '优先队列', '队列']
---

# Buy Low Sell High

## 题目描述

你可以完美地预测某只股票接下来 $N$ 天的价格，你想利用这一知识盈利，但你每天只想买卖一股，这表明你每天要么什么都不干，要么买入一股，要么卖出一股。起初你没有股票，你也不能在没有股票时卖出股票。你希望在第 $N$ 天结束时不持有股票，并最大化盈利。

## 输入格式

第一行一个整数 $N$（$2 \le N \le 3 \times 10^5$），表示天数。

接下来一行 $N$ 个整数 $p_1,p_2,\dots p_N$（$1 \le p_i \le 10^6$），表示第 $i$ 天的股价。

## 输出格式

输出你第 $N$ 天结束时的最大盈利。

### 样例解释

在股价为 $5,4$ 时各买入一股，在股价为 $9,12$ 时各卖出一股，接着在股价为 $2$ 时买入一股，股价为 $10$ 时卖出一股，总收益为 $20$。

Translated by uid $408071$。

## 样例 #1

### 输入

```
9
10 5 4 7 9 12 6 2 10

```

### 输出

```
20

```

## 样例 #2

### 输入

```
20
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4

```

### 输出

```
41

```



---

---
title: "Too Easy Problems"
layout: "post"
diff: 提高+/省选-
pid: CF913D
tag: ['贪心', '排序', '优先队列']
---

# Too Easy Problems

## 题目描述

你正在准备一场关于调度理论的考试。

这场考试会持续正好 $T$ 毫秒，由 $n$ 道题目组成。

你可以用 $t_i$ 毫秒解决第 $i$ 个问题，或者忽略它并不消耗时间。你也不需要用来在做完一道题之后休息的时间。

不幸的是，你的老师认为一些题目对你来说太简单了。因此，他对于每道题 $i$ 规定了一个整数 $a_i$，表示题目 $i$ 只在你总共解决了不超过 $a_i$ 个问题（包括问题 $i$ ）的情况下为你的最终成绩加上一分。

正式地，假设你在考试中解决了问题 $p_1,p_2,\cdots,p_k$。那么，你的最终成绩 $s$ 会等于在 $1$ 到 $k$ 之间的满足 $k\le a_{p_j}$ 的 $j$ 的个数。

你已经意识到这场考试真正的第一道题目已经放在了你面前。因此，你想要选择一组题目来解决，从而最大化你的最终成绩。不要忘记这场考试有时间限制，而你必须有足够的时间来解决所有你选择的题目。如果存在多个最优解，任意输出一组即可。

## 输入格式

第一行包含 $2$ 个整数，$n$ 和 $T$，分别是考试中题目的数量和考试时长的毫秒数。

接下来的 $n$ 行每行包括两个整数 $a_i$ 和 $t_i$。题目编号从 $1$ 到 $n$。

## 输出格式

在第一行，输出一个单独的整数 $s$，表示你的可能得到的最终成绩的最大值。

在第二行，输出一个单独的整数 $k$ 表示你应该解决的问题数量。

在第三行，以任意顺序输出 $k$ 个不同整数 $p_1,p_2,\cdots,p_k$，即你应当解决的题目编号。

如果有多个最优解，你可以输出其中任意一个。

## 样例解释

在第一个样例中，你应该解决题目 $3$、$1$ 和 $4$。在这种解下你会花费 $80+100+90=270$ 毫秒，在考试的长度 $300$ms 以内（甚至给自己留出了 $30$ms 休息时间）。题目 $3$ 和题目 $1$ 会分别为你带来 $1$ 分，然而题目 $4$ 不会。你会得到 $2$ 分。

在第二个样例中，这场灾难性的考试的长度甚至不足以解决一道题目（所以你显然一分都得不到）。

在第三个样例中，你刚好有足够的时间 $(42+58=100)$ 来解决这两道题并且微笑着把答卷交给老师。

## 说明/提示

$1\le n\le 2\times10^5$

$1\le T\le10^9$

$0\le k\le n$

## 样例 #1

### 输入

```
5 300
3 100
4 150
4 80
2 90
2 300

```

### 输出

```
2
3
3 1 4

```

## 样例 #2

### 输入

```
2 100
1 787
2 788

```

### 输出

```
0
0


```

## 样例 #3

### 输入

```
2 100
2 42
2 58

```

### 输出

```
2
2
1 2

```



---

---
title: "Cutlet"
layout: "post"
diff: 提高+/省选-
pid: CF939F
tag: ['单调队列', '枚举', '队列']
---

# Cutlet

## 题目描述

Arkady wants to have a dinner. He has just returned from a shop where he has bought a semifinished cutlet. He only needs to fry it. The cutlet should be fried for $ 2n $ seconds, in particular, it should be fried for $ n $ seconds on one side and $ n $ seconds on the other side. Arkady has already got a frying pan and turn on fire, but understood that maybe he won't be able to flip the cutlet exactly after $ n $ seconds after the beginning of cooking.

Arkady is too busy with sorting sticker packs in his favorite messenger and can flip the cutlet only in some periods of time. Namely, there are $ k $ periods of time in which he can do it, the $ i $ -th of them is an interval of time from $ l_{i} $ seconds after he starts cooking till $ r_{i} $ seconds, inclusive. Arkady decided that it's not required to flip the cutlet exactly in the middle of cooking, instead, he will flip it several times in such a way that the cutlet will be fried exactly $ n $ seconds on one side and $ n $ seconds on the other side in total.

Help Arkady and find out if it's possible for him to cook the cutlet, if he is able to flip the cutlet only in given periods of time; and if yes, find the minimum number of flips he needs to cook the cutlet.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100000 $ , $ 1<=k<=100 $ ) — the number of seconds the cutlet should be cooked on each side and number of periods of time in which Arkady can flip it.

The next $ k $ lines contain descriptions of these intervals. Each line contains two integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=2·n $ ), meaning that Arkady can flip the cutlet in any moment starting from $ l_{i} $ seconds after the beginning of cooking and finishing at $ r_{i} $ seconds after beginning of cooking. In particular, if $ l_{i}=r_{i} $ then Arkady can flip the cutlet only in the moment $ l_{i}=r_{i} $ . It's guaranteed that $ l_{i}>r_{i-1} $ for all $ 2<=i<=k $ .

## 输出格式

Output "Hungry" if Arkady won't be able to fry the cutlet for exactly $ n $ seconds on one side and exactly $ n $ seconds on the other side.

Otherwise, output "Full" in the first line, and the minimum number of times he should flip the cutlet in the second line.

## 说明/提示

In the first example Arkady should flip the cutlet in time moment $ 3 $ seconds after he starts cooking and in time moment $ 13 $ seconds after he starts cooking.

In the second example, Arkady can flip the cutlet at $ 10 $ seconds after he starts cooking.

## 样例 #1

### 输入

```
10 2
3 5
11 13

```

### 输出

```
Full
2

```

## 样例 #2

### 输入

```
10 3
3 5
9 10
11 13

```

### 输出

```
Full
1

```

## 样例 #3

### 输入

```
20 1
3 19

```

### 输出

```
Hungry

```



---

---
title: "Cashback"
layout: "post"
diff: 提高+/省选-
pid: CF940E
tag: ['动态规划 DP', '单调队列', '队列']
---

# Cashback

## 题目描述

Since you are the best Wraith King, Nizhniy Magazin «Mir» at the centre of Vinnytsia is offering you a discount.

You are given an array $ a $ of length $ n $ and an integer $ c $ .

The value of some array $ b $ of length $ k $ is the sum of its elements except for the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF940E/7767e68a87566f0732f029bd691b100b0a741ae2.png) smallest. For example, the value of the array $ [3,1,6,5,2] $ with $ c=2 $ is $ 3+6+5=14 $ .

Among all possible partitions of $ a $ into contiguous subarrays output the smallest possible sum of the values of these subarrays.

## 输入格式

The first line contains integers $ n $ and $ c $ ( $ 1<=n,c<=100000 $ ).

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of $ a $ .

## 输出格式

Output a single integer — the smallest possible sum of values of these subarrays of some partition of $ a $ .

## 说明/提示

In the first example any partition yields 6 as the sum.

In the second example one of the optimal partitions is $ [1,1],[10,10,10,10,10,10,9,10,10,10] $ with the values 2 and 90 respectively.

In the third example one of the optimal partitions is $ [2,3],[6,4,5,7],[1] $ with the values 3, 13 and 1 respectively.

In the fourth example one of the optimal partitions is $ [1],[3,4,5,5,3,4],[1] $ with the values 1, 21 and 1 respectively.

## 样例 #1

### 输入

```
3 5
1 2 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
12 10
1 1 10 10 10 10 10 10 9 10 10 10

```

### 输出

```
92

```

## 样例 #3

### 输入

```
7 2
2 3 6 4 5 7 1

```

### 输出

```
17

```

## 样例 #4

### 输入

```
8 4
1 3 4 5 5 3 4 1

```

### 输出

```
23

```



---

---
title: "Volleyball"
layout: "post"
diff: 提高+/省选-
pid: CF95C
tag: ['优先队列', '最短路', '队列']
---

# Volleyball

## 题目描述

Petya loves volleyball very much. One day he was running late for a volleyball match. Petya hasn't bought his own car yet, that's why he had to take a taxi. The city has $ n $ junctions, some of which are connected by two-way roads. The length of each road is defined by some positive integer number of meters; the roads can have different lengths.

Initially each junction has exactly one taxi standing there. The taxi driver from the $ i $ -th junction agrees to drive Petya (perhaps through several intermediate junctions) to some other junction if the travel distance is not more than $ t_{i} $ meters. Also, the cost of the ride doesn't depend on the distance and is equal to $ c_{i} $ bourles. Taxis can't stop in the middle of a road. Each taxi can be used no more than once. Petya can catch taxi only in the junction, where it stands initially.

At the moment Petya is located on the junction $ x $ and the volleyball stadium is on the junction $ y $ . Determine the minimum amount of money Petya will need to drive to the stadium.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=1000,0<=m<=1000) $ . They are the number of junctions and roads in the city correspondingly. The junctions are numbered from $ 1 $ to $ n $ , inclusive. The next line contains two integers $ x $ and $ y $ ( $ 1<=x,y<=n $ ). They are the numbers of the initial and final junctions correspondingly. Next $ m $ lines contain the roads' description. Each road is described by a group of three integers $ u_{i} $ , $ v_{i} $ , $ w_{i} $ ( $ 1<=u_{i},v_{i}<=n,1<=w_{i}<=10^{9} $ ) — they are the numbers of the junctions connected by the road and the length of the road, correspondingly. The next $ n $ lines contain $ n $ pairs of integers $ t_{i} $ and $ c_{i} $ ( $ 1<=t_{i},c_{i}<=10^{9} $ ), which describe the taxi driver that waits at the $ i $ -th junction — the maximum distance he can drive and the drive's cost. The road can't connect the junction with itself, but between a pair of junctions there can be more than one road. All consecutive numbers in each line are separated by exactly one space character.

## 输出格式

If taxis can't drive Petya to the destination point, print "-1" (without the quotes). Otherwise, print the drive's minimum cost.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specificator.

## 说明/提示

An optimal way — ride from the junction 1 to 2 (via junction 4), then from 2 to 3. It costs 7+2=9 bourles.

## 样例 #1

### 输入

```
4 4
1 3
1 2 3
1 4 1
2 4 1
2 3 5
2 7
7 2
1 2
7 7

```

### 输出

```
9

```



---

---
title: "Equalize the Remainders"
layout: "post"
diff: 提高+/省选-
pid: CF999D
tag: ['向量', '队列']
---

# Equalize the Remainders

## 题目描述

You are given an array consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ , and a positive integer $ m $ . It is guaranteed that $ m $ is a divisor of $ n $ .

In a single move, you can choose any position $ i $ between $ 1 $ and $ n $ and increase $ a_i $ by $ 1 $ .

Let's calculate $ c_r $ ( $ 0 \le r \le m-1) $ — the number of elements having remainder $ r $ when divided by $ m $ . In other words, for each remainder, let's find the number of corresponding elements in $ a $ with that remainder.

Your task is to change the array in such a way that $ c_0 = c_1 = \dots = c_{m-1} = \frac{n}{m} $ .

Find the minimum number of moves to satisfy the above requirement.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5, 1 \le m \le n $ ). It is guaranteed that $ m $ is a divisor of $ n $ .

The second line of input contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ), the elements of the array.

## 输出格式

In the first line, print a single integer — the minimum number of moves required to satisfy the following condition: for each remainder from $ 0 $ to $ m - 1 $ , the number of elements of the array having this remainder equals $ \frac{n}{m} $ .

In the second line, print any array satisfying the condition and can be obtained from the given array with the minimum number of moves. The values of the elements of the resulting array must not exceed $ 10^{18} $ .

## 样例 #1

### 输入

```
6 3
3 2 0 6 10 12

```

### 输出

```
3
3 2 0 7 10 14 

```

## 样例 #2

### 输入

```
4 2
0 1 2 3

```

### 输出

```
0
0 1 2 3 

```



---

