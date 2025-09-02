---
title: "Eating Queries"
layout: "post"
diff: 普及-
pid: CF1676E
tag: ['贪心', '二分']
---

# Eating Queries

## 题目描述

Timur has $ n $ candies. The $ i $ -th candy has a quantity of sugar equal to $ a_i $ . So, by eating the $ i $ -th candy, Timur consumes a quantity of sugar equal to $ a_i $ .

Timur will ask you $ q $ queries regarding his candies. For the $ j $ -th query you have to answer what is the minimum number of candies he needs to eat in order to reach a quantity of sugar greater than or equal to $ x_j $ or print -1 if it's not possible to obtain such a quantity. In other words, you should print the minimum possible $ k $ such that after eating $ k $ candies, Timur consumes a quantity of sugar of at least $ x_j $ or say that no possible $ k $ exists.

Note that he can't eat the same candy twice and queries are independent of each other (Timur can use the same candy in different queries).

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The description of test cases follows.

The first line contains $ 2 $ integers $ n $ and $ q $ ( $ 1 \leq n, q \leq 1.5\cdot10^5 $ ) — the number of candies Timur has and the number of queries you have to print an answer for respectively.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^4 $ ) — the quantity of sugar in each of the candies respectively.

Then $ q $ lines follow.

Each of the next $ q $ lines contains a single integer $ x_j $ ( $ 1 \leq x_j \leq 2 \cdot 10^9 $ ) – the quantity Timur wants to reach for the given query.

It is guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases do not exceed $ 1.5 \cdot 10^5 $ .

## 输出格式

For each test case output $ q $ lines. For the $ j $ -th line output the number of candies Timur needs to eat in order to reach a quantity of sugar greater than or equal to $ x_j $ or print -1 if it's not possible to obtain such a quantity.

## 说明/提示

For the first test case:

For the first query, Timur can eat any candy, and he will reach the desired quantity.

For the second query, Timur can reach a quantity of at least $ 10 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the third query, there is no possible answer.

For the fourth query, Timur can reach a quantity of at least $ 14 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the second test case:

For the only query of the second test case, we can choose the third candy from which Timur receives exactly $ 3 $ sugar. It's also possible to obtain the same answer by choosing the fourth candy.

## 样例 #1

### 输入

```
3
8 7
4 3 3 1 1 4 5 9
1
10
50
14
15
22
30
4 1
1 2 3 4
3
1 2
5
4
6
```

### 输出

```
1
2
-1
2
3
4
8
1
1
-1
```



---

---
title: "Find the Car"
layout: "post"
diff: 普及-
pid: CF1971E
tag: ['二分']
---

# Find the Car

## 题目描述

Timur is in a car traveling on the number line from point $ 0 $ to point $ n $ . The car starts moving from point $ 0 $ at minute $ 0 $ .

There are $ k+1 $ signs on the line at points $ 0, a_1, a_2, \dots, a_k $ , and Timur knows that the car will arrive there at minutes $ 0, b_1, b_2, \dots, b_k $ , respectively. The sequences $ a $ and $ b $ are strictly increasing with $ a_k = n $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971E/d53ef18fd3d7973a4983a5295563984c39a519c6.png)Between any two adjacent signs, the car travels with a constant speed. Timur has $ q $ queries: each query will be an integer $ d $ , and Timur wants you to output how many minutes it takes the car to reach point $ d $ , rounded down to the nearest integer.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ k $ , and $ q $ , ( $ k \leq n \leq 10^9 $ ; $ 1 \leq k, q \leq 10^5 $ ) — the final destination, the number of points Timur knows the time for, and the number of queries respectively.

The second line of each test case contains $ k $ integers $ a_i $ ( $ 1 \leq a_i \leq n $ ; $ a_i < a_{i+1} $ for every $ 1 \leq i \leq k-1 $ ; $ a_k = n $ ).

The third line of each test case contains $ k $ integers $ b_i $ ( $ 1 \leq b_i \leq 10^9 $ ; $ b_i < b_{i+1} $ for every $ 1 \leq i \leq k-1 $ ).

Each of the following $ q $ lines contains a single integer $ d $ ( $ 0 \leq d \leq n $ ) — the distance that Timur asks the minutes passed for.

The sum of $ k $ over all test cases doesn't exceed $ 10^5 $ , and the sum of $ q $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each query, output a single integer — the number of minutes passed until the car reaches the point $ d $ , rounded down.

## 说明/提示

For the first test case, the car goes from point $ 0 $ to point $ 10 $ in $ 10 $ minutes, so the speed is $ 1 $ unit per minute and:

- At point $ 0 $ , the time will be $ 0 $ minutes.
- At point $ 6 $ , the time will be $ 6 $ minutes.
- At point $ 7 $ , the time will be $ 7 $ minutes.

For the second test case, between points $ 0 $ and $ 4 $ , the car travels at a speed of $ 1 $ unit per minute and between $ 4 $ and $ 10 $ with a speed of $ 2 $ units per minute and:

- At point $ 6 $ , the time will be $ 5 $ minutes.
- At point $ 4 $ , the time will be $ 4 $ minutes.
- At point $ 2 $ , the time will be $ 2 $ minutes.
- At point $ 7 $ , the time will be $ 5.5 $ minutes, so the answer is $ 5 $ .

For the fourth test case, the car travels with $ 1.2 $ units per minute, so the answers to the queries are:

- At point $ 2 $ , the time will be $ 1.66\dots $ minutes, so the answer is $ 1 $ .
- At point $ 6 $ , the time will be $ 5 $ minutes.
- At point $ 5 $ , the time will be $ 4.16\dots $ minutes, so the answer is $ 4 $ .

## 样例 #1

### 输入

```
4
10 1 3
10
10
0
6
7
10 2 4
4 10
4 7
6
4
2
7
1000000000 1 1
1000000000
1000000000
99999999
6 1 3
6
5
2
6
5
```

### 输出

```
0 6 7 
5 4 2 5 
99999999 
1 5 4
```



---

---
title: "Final Boss"
layout: "post"
diff: 普及-
pid: CF1985F
tag: ['二分']
---

# Final Boss

## 题目描述

你正在面对你最喜欢的游戏中的最终  BOSS。敌人的生命值是 $h$。你的角色有 $ n $ 攻击。第 i 次攻击会对 BOSS 造成 $ a_i $ 伤害，但冷却时间为 $ c_i $ 个回合，也就是说，如果你当前的回合为 $ x $，那么下一次可以使用该攻击的时间为 $ x + c_i $ 个回合。 每个回合，你都可以一次性使用当前未冷却的所有攻击。如果所有攻击都处于冷却状态，则本回合什么也不做，跳到下一回合。

最初，所有攻击都不在冷却时间内。要花多少回合才能打败 BOSS？当 BOSS 的生命值为 $ 0 $ 或更低时，它就被打败了。

## 输入格式

第一行包含 $ t $ ( $ 1 \leq t \leq 10^4 $ ) - 测试用例的数量。

每个测试用例的第一行包含两个整数 $ h $ 和 $ n $ ( $ 1 \leq h, n \leq 2 \cdot 10^5 $ ) - BOSS 的血量和你的攻击次数。

每个测试用例的第 $2$ 行包含 $ n $ 整数 $ a_1, a_2, ..., a_n $ ( $ 1 \leq a_i \leq 2 \cdot 10^5 $ ) - 你的攻击伤害。

每个测试用例的第 $3$ 行包含 n 个整数 $ c_1, c_2, ..., c_n $ ( $ 1 \leq c_i \leq 2 \cdot 10^5 $ ) - 你的攻击冷却时间。

保证所有测试用例中的 $ h $ 和 $ n $ 之和不超过 $ 2 \cdot 10^5 $ .

## 输出格式

对于每个测试用例，输出一个整数，即击败 BOSS 所需的最少回合数。

## 样例 #1

### 输入

```
8
3 2
2 1
2 1
5 2
2 1
2 1
50 3
5 6 7
5 6 7
50 3
2 2 2
3 3 3
90000 2
200000 200000
1 1
100000 1
1
200000
6 7
3 2 3 2 3 1 2
6 5 9 5 10 7 7
21 6
1 1 1 1 1 1
5 5 8 10 7 6
```

### 输出

```
1
3
15
25
1
19999800001
1
21
```



---

---
title: "Robin Hood in Town"
layout: "post"
diff: 普及-
pid: CF2014C
tag: ['数学', '二分']
---

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 输入格式

The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 2\cdot10^5 $ ) — the total population.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the wealth of each person.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum number of gold that the richest person must find for Robin Hood to appear. If it is impossible, output $ -1 $ instead.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25
```

### 输出

```
-1
-1
0
15
16
0
```



---

---
title: "Brightness Begins"
layout: "post"
diff: 普及-
pid: CF2020B
tag: ['数学', '二分']
---

# Brightness Begins

## 题目描述

想象你有 $n$ 个编号为 $1, 2, \ldots, n$ 的灯泡。最初，所有灯泡都是开着的。翻转一个灯泡的状态意味着如果它原来是开着的，就把它关掉；否则就把它打开。

接下来，您需要执行以下操作：

对于每个 $i=1,2,\ldots,n$，翻转所有灯泡 $j$ 的状态，使得 $j$ 能被 $i^\dagger$ 整除。

在执行完所有操作后，将会有一些灯泡仍然亮着。你的目标是使这个数量恰好为 $k$。

找到最小的合适 $n$，使得执行操作后，灯泡的数量恰好为 $k$。我们可以证明答案总是存在的。

$ ^\dagger $ 如果存在一个整数 $ z $ 使得 $ x = y\cdot z $ ，那么一个整数 $ x $ 可以被 $ y $ 整除。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1\le t\le 10^4$）。测试用例的描述如下。

每个测试用例的唯一一行包含一个整数 $k$（$1\le k\le 10^{18}$）。

## 输出格式

对于每个测试用例，输出 $n$——最小灯泡数量。

## 说明/提示

在第一个测试用例中，最小数量的灯泡是 $2$。让我们用一个数组来表示所有灯泡的状态，其中$1$对应于打开的灯泡，$0$ 对应于关闭的灯泡。最初，数组是 $[1, 1]$。

- 在执行了 $i=1$ 的操作后，数组变成了 $[\underline{0},\underline{0}]$。
- 在执行了 $i=2$ 的操作后，数组变成了 $[0,\underline{1}]$。

最后，有 $k=1$ 个灯泡亮着。我们还可以证明答案不可能小于 $2$。

在第二个测试用例中，最小数量的灯泡是 $5$。最初，数组是 $[1, 1, 1, 1, 1]$。

- 在执行了 $i=1$ 的操作后，数组变成了 $[\underline{0},\underline{0},\underline{0},\underline{0},\underline{0}]$。
- 在执行了 $i=2$ 的操作后，数组变成了 $[0,\underline{1},0,\underline{1},0]$。
- 在执行了 $i=3$ 的操作后，数组变成了 $[0,1,\underline{1},1,0]$。
- 在执行了 $i=4$ 的操作后，数组变成了 $[0,1,1,\underline{0},0]$。
- 在执行了 $i=5$ 的操作后，数组变成了 $[0,1,1,0,\underline{1}]$。

最后，有 $k=3$ 个灯泡亮着。我们还可以证明答案不可能小于 $5$。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
3
1
3
8
```

### 输出

```
2
5
11
```



---

---
title: "Buying Lemonade"
layout: "post"
diff: 普及-
pid: CF2024B
tag: ['贪心', '二分']
---

# Buying Lemonade

## 题目描述

有一台柠檬水自动售货机。机器上有 $n$ 个槽位和 $n$ 个按钮，每个槽位对应一个按钮，但你并不知道每个按钮对应的是哪个槽位。

当您按下第 $i$ 个按钮时，有两种可能的事件：
- 若 $i$ 号槽位有至少一瓶柠檬水，则其中一瓶柠檬水会从这个槽位里掉下来，然后你会把它取走。
- 若 $i$ 号槽位没有柠檬水，则什么都不会发生。

柠檬水下落速度很快，因此您看不清它从哪个槽位掉出。您只知道每个槽位中瓶装柠檬水的数量 $a_i (1 \le i \le n)$。

您需要求出至少收到 $k$ 瓶柠檬水的最小按按钮次数。

数据保证机器中至少存在 $k$ 瓶柠檬水。

## 输入格式

第一行一个整数 $t$，表示有 $t$ 组测试用例。

对于每个测试用例，第一行两个整数 $n$，$k$；第二行 $n$ 个整数 $a_1, a_2, a_3, \cdots a_n$。

## 输出格式

共 $t$ 行，每行一个整数。

## 说明/提示

对于 $100\%$ 的数据，保证 $1 \le n \le 2 \times 10^5$，$1 \le a_i, k \le 10^9$，

## 样例 #1

### 输入

```
5
2 1
1 1
2 2
1 2
3 4
2 1 3
10 50
1 1 3 8 8 9 12 13 27 27
2 1000000000
1000000000 500000000
```

### 输出

```
1
2
5
53
1000000000
```



---

---
title: "Black Cells"
layout: "post"
diff: 普及-
pid: CF2026B
tag: ['贪心', '二分']
---

# Black Cells

## 题目描述

You are given a strip divided into cells, numbered from left to right from $ 0 $ to $ 10^{18} $ . Initially, all cells are white.

You can perform the following operation: choose two white cells $ i $ and $ j $ , such that $ i \ne j $ and $ |i - j| \le k $ , and paint them black.

A list $ a $ is given. All cells from this list must be painted black. Additionally, at most one cell that is not in this list can also be painted black. Your task is to determine the minimum value of $ k $ for which this is possible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 < a_i < 10^{18} $ ; $ a_i < a_{i + 1} $ ).

Additional constraint on the input: the sum of $ n $ across all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, print a single integer — the minimum value of $ k $ for which it is possible to paint all the given cells black.

## 说明/提示

In the first example, with $ k=1 $ , it is possible to paint the cells $ (1, 2) $ .

In the second example, with $ k=1 $ , it is possible to paint the cells $ (7, 8) $ .

In the third example, with $ k=2 $ , it is possible to paint the cells $ (2, 4) $ and $ (8, 9) $ .

In the fourth example, with $ k=3 $ , it is possible to paint the cells $ (0, 1) $ , $ (5, 8) $ and $ (10, 13) $ .

## 样例 #1

### 输入

```
4
2
1 2
1
7
3
2 4 9
5
1 5 8 10 13
```

### 输出

```
1
1
2
3
```



---

---
title: "Large Array and Segments"
layout: "post"
diff: 普及-
pid: CF2086B
tag: ['贪心', '二分']
---

# Large Array and Segments

## 题目描述

给定一个由 $n$ 个正整数组成的数组 $a$，以及一个正整数 $k$。根据以下规则从数组 $a$ 创建数组 $b$：

- 数组 $b$ 包含 $n \cdot k$ 个元素；
- 数组 $b$ 的前 $n$ 个元素与数组 $a$ 相同，即对于 $i \le n$，有 $b_{i} = a_{i}$；
- 对于任意 $i > n$，有 $b_{i} = b_{i - n}$。

例如，若 $a = [2, 3, 1, 4]$ 且 $k = 3$，则 $b = [2, 3, 1, 4, 2, 3, 1, 4, 2, 3, 1, 4]$。

给定一个数 $x$，要求统计满足以下条件的位置 $l$（$1 \le l \le n \cdot k$）的数量：存在位置 $r \ge l$，使得数组 $b$ 在区间 $[l, r]$ 上的元素之和不小于 $x$（即 $b_{l} + b_{l+1} + \dots + b_{r} \ge x$）。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 10^{4}$）——测试用例的数量。接下来是每个测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$k$、$x$（$1 \le n, k \le 10^{5}$；$1 \le x \le 10^{18}$）。  
第二行包含 $n$ 个整数 $a_{i}$（$1 \le a_{i} \le 10^{8}$）。  

输入数据的额外限制：
- 所有测试用例的 $n$ 之和不超过 $2 \cdot 10^{5}$；
- 所有测试用例的 $k$ 之和不超过 $2 \cdot 10^{5}$。


## 输出格式

对于每个测试用例，输出一个整数——数组 $b$ 中满足条件的位置 $l$ 的数量。


## 说明/提示

在第一个测试用例中，数组 $b$ 如下所示：

$$[3, 4, 2, 1, 5, 3, 4, 2, 1, 5, 3, 4, 2, 1, 5]$$

共有 $12$ 个位置 $l$ 满足存在对应的位置 $r$。以下是其中部分（非全部）示例：
- $l = 1$，存在 $r = 6$，区间 $[1, 6]$ 的和为 $18$；
- $l = 2$，存在 $r = 5$，区间 $[2, 5]$ 的和为 $12$；
- $l = 6$，存在 $r = 9$，区间 $[6, 9]$ 的和为 $10$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
5 3 10
3 4 2 1 5
15 97623 1300111
105 95 108 111 118 101 95 118 97 108 111 114 97 110 116
1 100000 1234567891011
1
1 1 1
1
1 1 1
2
2 1 2
1 1
2 1 5
2 1
```

### 输出

```
12
1452188
0
1
1
1
0
```



---

