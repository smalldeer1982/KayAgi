---
title: "Enlarge GCD"
layout: "post"
diff: 提高+/省选-
pid: CF1034A
tag: ['枚举', '素数判断,质数,筛法', '概率论']
---

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \leq n \leq 3 \cdot 10^5 $ ) — the number of integers Mr. F has.

The second line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 1.5 \cdot 10^7 $ ).

## 输出格式

Print an integer — the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

You should not remove all of the integers.

If there is no solution, print «-1» (without quotes).

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4

```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
6 9 15 30

```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 1 1

```

### 输出

```
-1
```



---

---
title: "Space Isaac"
layout: "post"
diff: 提高+/省选-
pid: CF1045B
tag: ['字符串', '枚举', '位运算']
---

# Space Isaac

## 题目描述

Everybody seems to think that the Martians are green, but it turns out they are metallic pink and fat. Ajs has two bags of distinct nonnegative integers. The bags are disjoint, and the union of the sets of numbers in the bags is $ \{0,1,…,M-1\} $ , for some positive integer $ M $ . Ajs draws a number from the first bag and a number from the second bag, and then sums them modulo $ M $ .

What are the residues modulo $ M $ that Ajs cannot obtain with this action?

## 输入格式

The first line contains two positive integer $ N $ ( $ 1 \leq N \leq 200\,000 $ ) and $ M $ ( $ N+1 \leq M \leq 10^{9} $ ), denoting the number of the elements in the first bag and the modulus, respectively.

The second line contains $ N $ nonnegative integers $ a_1,a_2,\ldots,a_N $ ( $ 0 \leq a_1<a_2< \ldots< a_N<M $ ), the contents of the first bag.

## 输出格式

In the first line, output the cardinality $ K $ of the set of residues modulo $ M $ which Ajs cannot obtain.

In the second line of the output, print $ K $ space-separated integers greater or equal than zero and less than $ M $ , which represent the residues Ajs cannot obtain. The outputs should be sorted in increasing order of magnitude. If $ K $ =0, do not output the second line.

## 说明/提示

In the first sample, the first bag and the second bag contain $ \{3,4\} $ and $ \{0,1,2\} $ , respectively. Ajs can obtain every residue modulo $ 5 $ except the residue $ 2 $ : $  4+1 \equiv 0, \, 4+2 \equiv 1, \, 3+0 \equiv 3, \, 3+1 \equiv 4  $ modulo $ 5 $ . One can check that there is no choice of elements from the first and the second bag which sum to $ 2 $ modulo $ 5 $ .

In the second sample, the contents of the first bag are $ \{5,25,125,625\} $ , while the second bag contains all other nonnegative integers with at most $ 9 $ decimal digits. Every residue modulo $ 1\,000\,000\,000 $ can be obtained as a sum of an element in the first bag and an element in the second bag.

## 样例 #1

### 输入

```
2 5
3 4

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
4 1000000000
5 25 125 625

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2 4
1 3

```

### 输出

```
2
0 2

```



---

---
title: "Linear Kingdom Races"
layout: "post"
diff: 提高+/省选-
pid: CF115E
tag: ['动态规划 DP', '线段树', '枚举']
---

# Linear Kingdom Races

## 题目描述

你是一个赛车比赛的组织者，想在线性王国中安排一些比赛。

线性王国有 $n$ 条连续的从左到右的道路。道路从左到右依次编号为从 $1$ 到 $n$，因此道路按照升序排列。在这些道路上可能会有几场比赛，每一场比赛都将使用这些道路的某个连续的子序列。而且，如果某场比赛举行了，你将获得一定数额的金钱。没有比赛在时间上重叠，所以每一段道路可以在多个比赛中使用。

不幸的是，**所有道路**的状况都不佳，需要修理。每条路都有与之相关的维修费用，你需要支付这笔费用来修理道路。只有在某场比赛中需要使用的所有道路**都进行了修复**，才能进行比赛。你的任务是修复道路并使你的利润最大化。你的利润被定义为你从比赛中获得的总金额减去你花在修理道路上的钱。**请注意，您可以决定不修任何道路，并获得利润 $0$。**

输出你能获得的最大利润。

## 输入格式

第一行包括两个整数 $n,m$（$1 \leq n,m \leq 2\cdot 10^5$），分别表示道路的数量和比赛的数量。

接下来 $n$ 行，每行一个整数，表示这条道路修复需要的代价。

再接下来 $m$ 行，每行包括三个整数 $l_b,u_b,p$（$1 \leq l_b,u_b \leq n,1 \leq p \leq 10^9$），表示第 $b$ 场比赛需要使用道路 $[l_b,u_b]$，你会获得收益 $p$。

## 输出格式

输出一个整数，表示你能获得的最大利润。

## 说明/提示

在第一个样例中，最优解是修复 $1, 2, 3, 7$。你将会在第 $1, 2, 4$ 三场比赛中获得 $15$ 的收益。道路修理费用是 $11$，因此你的利润是 $4$。

## 样例 #1

### 输入

```
7 4
3
2
3
2
1
2
3
1 2 5
2 3 5
3 5 3
7 7 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2 1
0
3
1 2 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 1
10
10
10
1 3 10

```

### 输出

```
0

```



---

---
title: "A Simple Task"
layout: "post"
diff: 提高+/省选-
pid: CF11D
tag: ['动态规划 DP', '枚举', '状态合并']
---

# A Simple Task

## 题目描述

Given a simple graph, output the number of simple cycles in it. A simple cycle is a cycle with no repeated vertices or edges.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1<=n<=19 $ , $ 0<=m $ ) – respectively the number of vertices and edges of the graph. Each of the subsequent $ m $ lines contains two integers $ a $ and $ b $ , ( $ 1<=a,b<=n $ , $ a≠b $ ) indicating that vertices $ a $ and $ b $ are connected by an undirected edge. There is no more than one edge connecting any pair of vertices.

## 输出格式

Output the number of cycles in the given graph.

## 说明/提示

The example graph is a clique and contains four cycles of length 3 and three cycles of length 4.

## 样例 #1

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4

```

### 输出

```
7

```



---

---
title: "Compatible Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF165E
tag: ['动态规划 DP', '枚举', '进制']
---

# Compatible Numbers

## 题目描述

Two integers $ x $ and $ y $ are compatible, if the result of their bitwise "AND" equals zero, that is, $ a $ $ & $ $ b=0 $ . For example, numbers $ 90 $ $ (1011010_{2}) $ and $ 36 $ $ (100100_{2}) $ are compatible, as $ 1011010_{2} $ $ & $ $ 100100_{2}=0_{2} $ , and numbers $ 3 $ $ (11_{2}) $ and $ 6 $ $ (110_{2}) $ are not compatible, as $ 11_{2} $ $ & $ $ 110_{2}=10_{2} $ .

You are given an array of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of elements in the given array. The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=4·10^{6} $ ) — the elements of the given array. The numbers in the array can coincide.

## 输出格式

Print $ n $ integers $ ans_{i} $ . If $ a_{i} $ isn't compatible with any other element of the given array $ a_{1},a_{2},...,a_{n} $ , then $ ans_{i} $ should be equal to -1. Otherwise $ ans_{i} $ is any such number, that $ a_{i} $ $ & $ $ ans_{i}=0 $ , and also $ ans_{i} $ occurs in the array $ a_{1},a_{2},...,a_{n} $ .

## 样例 #1

### 输入

```
2
90 36

```

### 输出

```
36 90
```

## 样例 #2

### 输入

```
4
3 6 3 6

```

### 输出

```
-1 -1 -1 -1
```

## 样例 #3

### 输入

```
5
10 6 9 8 2

```

### 输出

```
-1 8 2 2 8
```



---

---
title: "Hossam and a Letter"
layout: "post"
diff: 提高+/省选-
pid: CF1771E
tag: ['动态规划 DP', '枚举', '双指针 two-pointer']
---

# Hossam and a Letter

## 题目描述

Hossam bought a new piece of ground with length $ n $ and width $ m $ , he divided it into an $ n \cdot m $ grid, each cell being of size $ 1\times1 $ .

Since Hossam's name starts with the letter 'H', he decided to draw the capital letter 'H' by building walls of size $ 1\times1 $ on some squares of the ground. Each square $ 1\times1 $ on the ground is assigned a quality degree: perfect, medium, or bad.

The process of building walls to form up letter 'H' has the following constraints:

- The letter must consist of one horizontal and two vertical lines.
- The vertical lines must not be in the same or neighboring columns.
- The vertical lines must start in the same row and end in the same row (and thus have the same length).
- The horizontal line should connect the vertical lines, but must not cross them.
- The horizontal line can be in any row between the vertical lines (not only in the middle), except the top and the bottom one. (With the horizontal line in the top row the letter looks like 'n', and in the bottom row like 'U'.)
- It is forbidden to build walls in cells of bad quality.
- You can use at most one square of medium quality.
- You can use any number of squares of perfect quality.

Find the maximum number of walls that can be used to draw the letter 'H'.

Check the note for more clarification.

## 输入格式

The first line of the input contains two integer numbers $ n $ , $ m $ ( $ 1 \le n, m \le 400 $ ).

The next $ n $ lines of the input contain $ m $ characters each, describing the grid. The character '.' stands for a perfect square, the character 'm' stands for a medium square, and the character '\#' stands for a bad square.

## 输出格式

Print a single integer — the maximum number of walls that form a capital letter 'H'.

If it is not possible to draw any letter 'H', print $ 0 $ .

## 说明/提示

In the first test case, we can't build the letter 'H'.

For the second test case, the figure below represents the grid and some of the valid letters 'H'. Perfect, medium, and bad squares are represented with white, yellow, and black colors respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771E/7ab52d112de710667f4c7cf4e814613751fe43eb.png)

## 样例 #1

### 输入

```
2 3
#m.
.#.
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7 8
...#.m..
..m...m.
.#..#.m#
...m..m.
m.......
..#.m.mm
......m.
```

### 输出

```
16
```



---

---
title: "Multiple Lamps"
layout: "post"
diff: 提高+/省选-
pid: CF1909E
tag: ['枚举']
---

# Multiple Lamps

## 题目描述

[Kid2Will - Fire Aura](https://soundcloud.com/xgp/kid2will-fire-aura)

⠀



You have $ n $ lamps, numbered from $ 1 $ to $ n $ . Initially, all the lamps are turned off.

You also have $ n $ buttons. The $ i $ -th button toggles all the lamps whose index is a multiple of $ i $ . When a lamp is toggled, if it was off it turns on, and if it was on it turns off.

You have to press some buttons according to the following rules.

- You have to press at least one button.
- You cannot press the same button multiple times.
- You are given $ m $ pairs $ (u_i, v_i) $ . If you press the button $ u_i $ , you also have to press the button $ v_i $ (at any moment, not necessarily after pressing the button $ u_i $ ). Note that, if you press the button $ v_i $ , you don't need to press the button $ u_i $ .

You don't want to waste too much electricity. Find a way to press buttons such that at the end at most $ \lfloor n/5 \rfloor $ lamps are on, or print $ -1 $ if it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq m \leq 2 \cdot 10^5 $ ) — the number of lamps and the number of pairs, respectively.

Each of the next $ m $ lines contains two integers $ u_i $ , $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \neq v_i $ ). If you press the button $ u_i $ , you also have to press the button $ v_i $ . It is guaranteed that the pairs $ (u_i, v_i) $ are distinct.

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases do not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case:

- If there is no choice of buttons that makes at most $ \lfloor n/5 \rfloor $ lamps on at the end, output a single line containing $ -1 $ .
- Otherwise, output two lines. The first line should contain an integer $ k $ ( $ 1 \le k \le n $ ) — the number of pressed buttons. The second line should contain $ k $ integers $ b_1, b_2, \dots, b_k $ ( $ 1 \le b_i \le n $ ) — the indices of the pressed buttons (in any order). The $ b_i $ must be distinct, and at the end at most $ \lfloor n/5 \rfloor $ lamps must be turned on.

## 说明/提示

In the first test case, you need to turn at most $ \lfloor 4/5 \rfloor $ lamps on, which means that no lamp can be turned on. You can show that no choice of at least one button turns $ 0 $ lamps on.

In the second test case, you can press buttons $ 3 $ , $ 5 $ , $ 1 $ , $ 2 $ .

- Initially, all the lamps are off;
- after pressing button $ 3 $ , the lamps whose index is a multiple of $ 3 $ (i.e., $ 3 $ ) are toggled, so lamp $ 3 $ is turned on;
- after pressing button $ 5 $ , the lamps whose index is a multiple of $ 5 $ (i.e., $ 5 $ ) are toggled, so lamps $ 3 $ , $ 5 $ are turned on;
- after pressing button $ 1 $ , the lamps whose index is a multiple of $ 1 $ (i.e., $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ ) are toggled, so lamps $ 1 $ , $ 2 $ , $ 4 $ are turned on;
- after pressing button $ 2 $ , the lamps whose index is a multiple of $ 2 $ (i.e., $ 2 $ , $ 4 $ ) are toggled, so lamp $ 1 $ is turned on.

This is valid because

- you pressed at least one button;
- you pressed all the buttons at most once;
- you pressed button $ u_2 = 5 $ , which means that you had to also press button $ v_2 = 1 $ : in fact, button $ 1 $ has been pressed;
- at the end, only lamp $ 1 $ is on.

In the third test case, pressing the buttons $ 8 $ , $ 9 $ , $ 10 $ turns only the lamps $ 8 $ , $ 9 $ , $ 10 $ on.

## 样例 #1

### 输入

```
4
4 0
5 2
4 1
5 1
15 9
7 8
8 9
9 10
10 9
11 1
12 2
13 3
14 4
15 5
5 4
1 2
2 3
3 4
4 5
```

### 输出

```
-1
4
3 5 1 2
3
8 9 10
1
5
```



---

---
title: "Reconstruction"
layout: "post"
diff: 提高+/省选-
pid: CF1984F
tag: ['动态规划 DP', '枚举']
---

# Reconstruction

## 题目描述

There is a hidden array $ a_1, a_2, \ldots, a_n $ of length $ n $ whose elements are integers between $ -m $ and $ m $ , inclusive.

You are given an array $ b_1, b_2, \ldots, b_n $ of length $ n $ and a string $ s $ of length $ n $ consisting of the characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{?} $ .

For each $ i $ from $ 1 $ to $ n $ inclusive, we must have:

- If $ s_i = \texttt{P} $ , $ b_i $ is the sum of $ a_1 $ through $ a_i $ .
- If $ s_i = \texttt{S} $ , $ b_i $ is the sum of $ a_i $ through $ a_n $ .

Output the number of ways to replace all $ \texttt{?} $ in $ s $ with either $ \texttt{P} $ or $ \texttt{S} $ such that there exists an array $ a_1, a_2, \ldots, a_n $ with elements not exceeding $ m $ by absolute value satisfying the constraints given by the array $ b_1, b_2, \ldots, b_n $ and the string $ s $ .

Since the answer may be large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 2 \cdot 10^3 $ , $ 2 \leq m \leq 10^{9} $ ) — the length of the hidden array $ a_1, a_2, \ldots, a_n $ and the maximum absolute value of an element $ a_i $ .

The second line of each test case contains a string $ s $ of length $ n $ consisting of characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{?} $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ |b_i| \leq m \cdot n $ ).

The sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^3 $ .

## 输出格式

For each test case, output a single integer — the number of ways to replace all $ \texttt{?} $ in $ s $ with either $ \texttt{P} $ or $ \texttt{S} $ that result in the existence of a valid array $ a_1, a_2, \ldots, a_n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, we can see that the following array satisfies all constraints, thus the answer is $ 1 $ :

1. $ \texttt{P} $ — $ {[\color{red}{\textbf{1}},3,4,2]} $ : sum of $ 1 $ .
2. $ \texttt{S} $ — $ {[1,\color{red}{\textbf{3},4,2}]} $ : sum of $ 9 $ .
3. $ \texttt{P} $ — $ {[\color{red}{1,3,\textbf{4}},2]} $ : sum of $ 8 $ .
4. $ \texttt{P} $ — $ {[\color{red}{1,3,4,\textbf{2}}]} $ : sum of $ 10 $ .

In the second test case, it can be shown that no array $ a $ with all $ |a_i| \leq m = 10^9 $ satisfies all constraints.

## 样例 #1

### 输入

```
6
4 10
PSPP
1 9 8 10
4 1000000000
????
1 1 1 4000000000
8 1000000000
?P?SSP?P
-857095623 -1424391899 -851974476 673437144 471253851 -543483033 364945701 -178537332
4 7
PPSS
4 2 1 3
9 20
?????????
1 2 3 4 5 6 7 8 9
3 1000000000
P??
-145463248 -974068460 -1287458396
```

### 输出

```
1
0
2
1
14
1
```



---

---
title: "Ancient Berland Circus"
layout: "post"
diff: 提高+/省选-
pid: CF1C
tag: ['计算几何', '枚举', '最大公约数 gcd']
---

# Ancient Berland Circus

## 题目描述

Nowadays all circuses in Berland have a round arena with diameter 13 meters, but in the past things were different.

In Ancient Berland arenas in circuses were shaped as a regular (equiangular) polygon, the size and the number of angles could vary from one circus to another. In each corner of the arena there was a special pillar, and the rope strung between the pillars marked the arena edges.

Recently the scientists from Berland have discovered the remains of the ancient circus arena. They found only three pillars, the others were destroyed by the time.

You are given the coordinates of these three pillars. Find out what is the smallest area that the arena could have.

## 输入格式

The input file consists of three lines, each of them contains a pair of numbers –– coordinates of the pillar. Any coordinate doesn't exceed 1000 by absolute value, and is given with at most six digits after decimal point.

## 输出格式

Output the smallest possible area of the ancient arena. This number should be accurate to at least 6 digits after the decimal point. It's guaranteed that the number of angles in the optimal polygon is not larger than 100.

## 样例 #1

### 输入

```
0.000000 0.000000
1.000000 1.000000
0.000000 1.000000

```

### 输出

```
1.00000000

```



---

---
title: "Serval and Colorful Array (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2085F1
tag: ['贪心', '枚举', '差分']
---

# Serval and Colorful Array (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的区别在于此版本中 $n \leq 3000$。仅当您解决了该问题的所有版本时才能进行 hack。

Serval 有一个魔法数 $k$（$k \geq 2$）。我们称数组 $r$ 为 colorful 当且仅当：
- $r$ 的长度为 $k$，且
- $1$ 到 $k$ 之间的每个整数在 $r$ 中恰好出现一次。

给定一个由 $n$ 个介于 $1$ 到 $k$ 的整数组成的数组 $a$。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。您可以对 $a$ 执行以下操作：
- 选择一个下标 $i$（$1 \leq i < n$），然后交换 $a_i$ 和 $a_{i+1}$。

求使得 $a$ 中至少存在一个 colorful 子数组$^{\text{∗}}$所需的最小操作次数。可以证明在题目约束下这总是可行的。

$^{\text{∗}}$数组 $b$ 是数组 $a$ 的子数组，当且仅当 $b$ 可以通过从 $a$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 1000$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$2 \leq k \leq n \leq 3000$）——数组 $a$ 的长度和 Serval 的魔法数。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq k$）——数组 $a$ 的元素。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。

保证所有测试用例的 $n$ 之和不超过 $3000$。

## 输出格式

对于每个测试用例，输出一个整数 —— 使得 $a$ 中至少存在一个 colorful 子数组所需的最小操作次数。

## 说明/提示

第一个测试案例中，由于子数组 $[a_1, a_2] = [1, 2]$ 和 $[a_2, a_3] = [2, 1]$ 已经是 colorful 的，因此无需执行任何操作。答案为 $0$。

第二个测试案例中，我们可以交换 $a_1$ 和 $a_2$ 得到 $[1, \underline{2, 1, 3}, 1, 1, 2]$，其中包含一个 colorful 子数组 $[a_2, a_3, a_4] = [2, 1, 3]$。由于原数组初始时没有 colorful 子数组，因此答案为 $1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2
1 2 1
7 3
2 1 1 3 1 1 2
6 3
1 1 2 2 2 3
6 3
1 2 2 2 2 3
10 5
5 1 3 1 1 2 2 4 1 3
9 4
1 2 3 3 3 3 3 2 4
```

### 输出

```
0
1
2
3
4
5
```



---

---
title: "Mani and Segments"
layout: "post"
diff: 提高+/省选-
pid: CF2101D
tag: ['线段树', '枚举', '扫描线']
---

# Mani and Segments

## 题目描述

一个长度为 $|b|$ 的数组 $b$ 被称为"可爱的"，当且仅当其最长递增子序列（LIS）的长度与最长递减子序列（LDS）的长度 $^{\text{∗}}$ 之和恰好比数组长度大 1。更正式地说，数组 $b$ 是可爱的当且仅当 $\operatorname{LIS}(b) + \operatorname{LDS}(b) = |b| + 1$。

给定一个长度为 $n$ 的排列 $a$ $^{\text{†}}$。你的任务是统计排列 $a$ 中所有非空子数组 $^{\text{‡}}$ 中满足可爱条件的数量。

$^{\text{∗}}$ 序列 $x$ 是序列 $y$ 的子序列，如果可以通过从 $y$ 中删除任意位置（可能为零或全部）的元素得到 $x$。

数组的最长递增（递减）子序列是指元素按严格递增（递减）顺序排列的最长子序列。

$^{\text{†}}$ 长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

$^{\text{‡}}$ 数组 $x$ 是数组 $y$ 的子数组，如果可以通过从 $y$ 的开头和结尾删除若干（可能为零或全部）元素得到 $x$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——排列 $a$ 的长度。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）——排列 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出排列 $a$ 中满足可爱条件的非空子数组数量。

## 说明/提示

在第一个测试用例中，所有 6 个非空子数组都是可爱的：
- $[3]$：$\operatorname{LIS}([3]) + \operatorname{LDS}([3]) = 1 + 1 = 2$
- $[1]$：$\operatorname{LIS}([1]) + \operatorname{LDS}([1]) = 1 + 1 = 2$
- $[2]$：$\operatorname{LIS}([2]) + \operatorname{LDS}([2]) = 1 + 1 = 2$
- $[3, 1]$：$\operatorname{LIS}([3, 1]) + \operatorname{LDS}([3, 1]) = 1 + 2 = 3$
- $[1, 2]$：$\operatorname{LIS}([1, 2]) + \operatorname{LDS}([1, 2]) = 2 + 1 = 3$
- $[3, 1, 2]$：$\operatorname{LIS}([3, 1, 2]) + \operatorname{LDS}([3, 1, 2]) = 2 + 2 = 4$

在第二个测试用例中，一个可爱的子数组是 $[2, 3, 4, 5, 1]$，因为 $\operatorname{LIS}([2, 3, 4, 5, 1]) = 4$ 且 $\operatorname{LDS}([2, 3, 4, 5, 1]) = 2$，满足 $4 + 2 = 5 + 1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
3 1 2
5
2 3 4 5 1
4
3 4 1 2
7
1 2 3 4 5 6 7
10
7 8 2 4 5 10 1 3 6 9
```

### 输出

```
6
15
9
28
36
```



---

---
title: "Cowboys"
layout: "post"
diff: 提高+/省选-
pid: CF212C
tag: ['字符串', '枚举']
---

# Cowboys

## 题目描述

问题描述
 
　　n个牛仔站立于一个环中，并且每个牛仔都用左轮手枪指着他旁边的人！每个牛仔指着他顺时针或者逆时针方向上的相邻的人。正如很多西部片那样，在这一刻，绳命是入刺的不可惜……对峙的场景每秒都在变化。每秒钟牛仔们都会分析局势，当一对相邻的牛仔发现他们正在互指的时候，就会转过身。一秒内每对这样的牛仔都会转身。所有的转身都同时在一瞬间发生。我们用字母来表示牛仔所指的方向。“A”表示顺时针方向，“B”表示逆时针方向。如此，一个仅含“A”“B”的字符串便用来表示这个由牛仔构成的环。这是由第一个指着顺时针方向的牛仔做出的记录。例如，牛仔环“ABBBABBBA”在一秒后会变成“BABBBABBA”；而牛仔环“BABBA”会变成“ABABB”。 这幅图说明了“BABBA”怎么变成“ABABB” 一秒过去了，现在用字符串s来表示牛仔们的排列。你的任务是求出一秒前有多少种可能的排列。如果某个排列中一个牛仔指向顺时针，而在另一个排列中他指向逆时针，那么这两个排列就是不同的。

## 输入格式

　　输入数据包括一个字符串s，它只含有“A”和“B”。

## 输出格式

　　输出你求出来的一秒前的可能排列数。
  
数据规模和约定

　　s的长度为3到100（包含3和100）

由 @落叶知秋声 提供翻译

## 样例 #1

### 输入

```
BABBBABBA

```

### 输出

```
2

```

## 样例 #2

### 输入

```
ABABB

```

### 输出

```
2

```

## 样例 #3

### 输入

```
ABABAB

```

### 输出

```
4

```



---

---
title: "Anniversary"
layout: "post"
diff: 提高+/省选-
pid: CF226C
tag: ['枚举', '斐波那契数列']
---

# Anniversary

## 题目描述

There are less than 60 years left till the 900-th birthday anniversary of a famous Italian mathematician Leonardo Fibonacci. Of course, such important anniversary needs much preparations.

Dima is sure that it'll be great to learn to solve the following problem by the Big Day: You're given a set $ A $ , consisting of numbers $ l $ , $ l+1 $ , $ l+2 $ , $ ... $ , $ r $ ; let's consider all its $ k $ -element subsets; for each such subset let's find the largest common divisor of Fibonacci numbers with indexes, determined by the subset elements. Among all found common divisors, Dima is interested in the largest one.

Dima asked to remind you that Fibonacci numbers are elements of a numeric sequence, where $ F_{1}=1 $ , $ F_{2}=1 $ , $ F_{n}=F_{n-1}+F_{n-2} $ for $ n>=3 $ .

Dima has more than half a century ahead to solve the given task, but you only have two hours. Count the residue from dividing the sought largest common divisor by $ m $ .

## 输入格式

The first line contains four space-separated integers $ m $ , $ l $ , $ r $ and $ k $ $ (1<=m<=10^{9}; 1<=l&lt;r<=10^{12}; 2<=k<=r-l+1) $ .

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specifier.

## 输出格式

Print a single integer — the residue from dividing the sought greatest common divisor by $ m $ .

## 样例 #1

### 输入

```
10 1 8 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
10 1 8 3

```

### 输出

```
1

```



---

---
title: "Test"
layout: "post"
diff: 提高+/省选-
pid: CF25E
tag: ['字符串', '枚举', 'KMP 算法']
---

# Test

## 题目描述

Sometimes it is hard to prepare tests for programming problems. Now Bob is preparing tests to new problem about strings — input data to his problem is one string. Bob has 3 wrong solutions to this problem. The first gives the wrong answer if the input data contains the substring $ s_{1} $ , the second enters an infinite loop if the input data contains the substring $ s_{2} $ , and the third requires too much memory if the input data contains the substring $ s_{3} $ . Bob wants these solutions to fail single test. What is the minimal length of test, which couldn't be passed by all three Bob's solutions?

## 输入格式

There are exactly 3 lines in the input data. The $ i $ -th line contains string $ s_{i} $ . All the strings are non-empty, consists of lowercase Latin letters, the length of each string doesn't exceed $ 10^{5} $ .

## 输出格式

Output one number — what is minimal length of the string, containing $ s_{1} $ , $ s_{2} $ and $ s_{3} $ as substrings.

## 样例 #1

### 输入

```
ab
bc
cd

```

### 输出

```
4

```

## 样例 #2

### 输入

```
abacaba
abaaba
x

```

### 输出

```
11

```



---

---
title: "Lucky Common Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF346B
tag: ['字符串', '动态规划 DP', '枚举', 'KMP 算法']
---

# Lucky Common Subsequence

## 题目描述

In mathematics, a subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. For example, the sequence BDF is a subsequence of ABCDEF. A substring of a string is a continuous subsequence of the string. For example, BCD is a substring of ABCDEF.

You are given two strings $ s_{1} $ , $ s_{2} $ and another string called $ virus $ . Your task is to find the longest common subsequence of $ s_{1} $ and $ s_{2} $ , such that it doesn't contain $ virus $ as a substring.

## 输入格式

The input contains three strings in three separate lines: $ s_{1} $ , $ s_{2} $ and $ virus $ ( $ 1<=|s_{1}|,|s_{2}|,|virus|<=100 $ ). Each string consists only of uppercase English letters.

## 输出格式

Output the longest common subsequence of $ s_{1} $ and $ s_{2} $ without $ virus $ as a substring. If there are multiple answers, any of them will be accepted.

If there is no valid common subsequence, output 0.

## 样例 #1

### 输入

```
AJKEQSLOBSROFGZ
OVGURWZLWVLUXTH
OZ

```

### 输出

```
ORZ

```

## 样例 #2

### 输入

```
AA
A
A

```

### 输出

```
0

```



---

---
title: "Moon Craters"
layout: "post"
diff: 提高+/省选-
pid: CF39C
tag: ['数学', '离散化', '枚举']
---

# Moon Craters

## 题目描述

There are lots of theories concerning the origin of moon craters. Most scientists stick to the meteorite theory, which says that the craters were formed as a result of celestial bodies colliding with the Moon. The other version is that the craters were parts of volcanoes.

An extraterrestrial intelligence research specialist professor Okulov (the namesake of the Okulov, the author of famous textbooks on programming) put forward an alternate hypothesis. Guess what kind of a hypothesis it was –– sure, the one including extraterrestrial mind involvement. Now the professor is looking for proofs of his hypothesis.

Professor has data from the moon robot that moves linearly in one direction along the Moon surface. The moon craters are circular in form with integer-valued radii. The moon robot records only the craters whose centers lay on his path and sends to the Earth the information on the distance from the centers of the craters to the initial point of its path and on the radii of the craters.

According to the theory of professor Okulov two craters made by an extraterrestrial intelligence for the aims yet unknown either are fully enclosed one in the other or do not intersect at all. Internal or external tangency is acceptable. However the experimental data from the moon robot do not confirm this theory! Nevertheless, professor Okulov is hopeful. He perfectly understands that to create any logical theory one has to ignore some data that are wrong due to faulty measuring (or skillful disguise by the extraterrestrial intelligence that will be sooner or later found by professor Okulov!) That’s why Okulov wants to choose among the available crater descriptions the largest set that would satisfy his theory.

## 输入格式

The first line has an integer $ n $ ( $ 1<=n<=2000 $ ) — the number of discovered craters. The next $ n $ lines contain crater descriptions in the " $ c_{i} $ $ r_{i} $ " format, where $ c_{i} $ is the coordinate of the center of the crater on the moon robot’s path, $ r_{i} $ is the radius of the crater. All the numbers $ c_{i} $ and $ r_{i} $ are positive integers not exceeding $ 10^{9} $ . No two craters coincide.

## 输出格式

In the first line output the number of craters in the required largest set. In the next line output space-separated numbers of craters that this set consists of. The craters are numbered from $ 1 $ to $ n $ in the order in which they were given in the input data. The numbers may be output in any order. If the result is not unique, output any.

## 样例 #1

### 输入

```
4
1 1
2 2
4 1
5 1

```

### 输出

```
3
1 2 4

```



---

---
title: "Roman and Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF401D
tag: ['动态规划 DP', '枚举', '状态合并', '进制', '构造']
---

# Roman and Numbers

## 题目描述

Roman is a young mathematician, very famous in Uzhland. Unfortunately, Sereja doesn't think so. To make Sereja change his mind, Roman is ready to solve any mathematical problem. After some thought, Sereja asked Roma to find, how many numbers are close to number $ n $ , modulo $ m $ .

Number $ x $ is considered close to number $ n $ modulo $ m $ , if:

- it can be obtained by rearranging the digits of number $ n $ ,
- it doesn't have any leading zeroes,
- the remainder after dividing number $ x $ by $ m $ equals 0.

Roman is a good mathematician, but the number of such numbers is too huge for him. So he asks you to help him.

## 输入格式

The first line contains two integers: $ n $ $ (1<=n&lt;10^{18}) $ and $ m $ $ (1<=m<=100) $ .

## 输出格式

In a single line print a single integer — the number of numbers close to number $ n $ modulo $ m $ .

## 说明/提示

In the first sample the required numbers are: 104, 140, 410.

In the second sample the required number is 232.

## 样例 #1

### 输入

```
104 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
223 4

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7067678 8

```

### 输出

```
47

```



---

---
title: "Jzzhu and Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF449D
tag: ['枚举', '状态合并', '容斥原理']
---

# Jzzhu and Numbers

## 题目描述

Jzzhu have $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . We will call a sequence of indexes $ i_{1},i_{2},...,i_{k} $ $ (1<=i_{1}<i_{2}<...<i_{k}<=n) $ a group of size $ k $ .

Jzzhu wonders, how many groups exists such that $ a_{i1} $ & $ a_{i2} $ & ... & $ a_{ik}=0 $ $ (1<=k<=n) $ ? Help him and print this number modulo $ 1000000007 $ $ (10^{9}+7) $ . Operation $ x $ & $ y $ denotes bitwise AND operation of two numbers.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{6}) $ . The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=10^{6}) $ .

## 输出格式

Output a single integer representing the number of required groups modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
3
2 3 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4
0 1 2 3

```

### 输出

```
10

```

## 样例 #3

### 输入

```
6
5 2 0 5 2 1

```

### 输出

```
53

```



---

---
title: "CGCDSSQ"
layout: "post"
diff: 提高+/省选-
pid: CF475D
tag: ['枚举', '最大公约数 gcd', '线性递推']
---

# CGCDSSQ

## 题目描述

Given a sequence of integers $ a_{1},...,a_{n} $ and $ q $ queries $ x_{1},...,x_{q} $ on it. For each query $ x_{i} $ you have to count the number of pairs $ (l,r) $ such that $ 1<=l<=r<=n $ and $ gcd(a_{l},a_{l+1},...,a_{r})=x_{i} $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475D/57fa10a542946ca7729b1feeb84648963b002c6d.png) is a greatest common divisor of $ v_{1},v_{2},...,v_{n} $ , that is equal to a largest positive integer that divides all $ v_{i} $ .

## 输入格式

Given a sequence of integers $ a_{1},...,a_{n} $ and $ q $ queries $ x_{1},...,x_{q} $ on it. For each query $ x_{i} $ you have to count the number of pairs $ (l,r) $ such that $ 1<=l<=r<=n $ and $ gcd(a_{l},a_{l+1},...,a_{r})=x_{i} $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475D/57fa10a542946ca7729b1feeb84648963b002c6d.png) is a greatest common divisor of $ v_{1},v_{2},...,v_{n} $ , that is equal to a largest positive integer that divides all $ v_{i} $ .

## 输出格式

For each query print the result in a separate line.

## 样例 #1

### 输入

```
3
2 6 3
5
1
2
3
4
6

```

### 输出

```
1
2
2
0
1

```

## 样例 #2

### 输入

```
7
10 20 3 15 1000 60 16
10
1
2
3
4
5
6
10
20
60
1000

```

### 输出

```
14
0
2
2
2
0
2
2
1
1

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
title: "Restoring Increasing Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF490E
tag: ['字符串', '枚举', '构造']
---

# Restoring Increasing Sequence

## 题目描述

Peter wrote on the board a strictly increasing sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Then Vasil replaced some digits in the numbers of this sequence by question marks. Thus, each question mark corresponds to exactly one lost digit.

Restore the the original sequence knowing digits remaining on the board.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the sequence. Next $ n $ lines contain one element of the sequence each. Each element consists only of digits and question marks. No element starts from digit 0. Each element has length from 1 to 8 characters, inclusive.

## 输出格式

If the answer exists, print in the first line "YES" (without the quotes). Next $ n $ lines must contain the sequence of positive integers — a possible variant of Peter's sequence. The found sequence must be strictly increasing, it must be transformed from the given one by replacing each question mark by a single digit. All numbers on the resulting sequence must be written without leading zeroes. If there are multiple solutions, print any of them.

If there is no answer, print a single line "NO" (without the quotes).

## 样例 #1

### 输入

```
3
?
18
1?

```

### 输出

```
YES
1
18
19

```

## 样例 #2

### 输入

```
2
??
?

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
12224
12??5
12226
?0000
?00000

```

### 输出

```
YES
12224
12225
12226
20000
100000

```



---

---
title: "Anya and Cubes"
layout: "post"
diff: 提高+/省选-
pid: CF525E
tag: ['搜索', '枚举', '剪枝', '折半搜索 meet in the middle']
---

# Anya and Cubes

## 题目描述

Anya loves to fold and stick. Today she decided to do just that.

Anya has $ n $ cubes lying in a line and numbered from $ 1 $ to $ n $ from left to right, with natural numbers written on them. She also has $ k $ stickers with exclamation marks. We know that the number of stickers does not exceed the number of cubes.

Anya can stick an exclamation mark on the cube and get the factorial of the number written on the cube. For example, if a cube reads $ 5 $, then after the sticking it reads $ 5! $, which equals $ 120 $.

You need to help Anya count how many ways there are to choose some of the cubes and stick on some of the chosen cubes at most $ k $ exclamation marks so that the sum of the numbers written on the chosen cubes after the sticking becomes equal to $ S $. Anya can stick at most one exclamation mark on each cube. Can you do it?

Two ways are considered the same if they have the same set of chosen cubes and the same set of cubes with exclamation marks.

## 输入格式

The first line of the input contains three space-separated integers $ n $, $ k $ and $ S\ (1\le n\le25,\ 0\le k\le n,\ 1\le S\le10^{16})$ — the number of cubes and the number of stickers that Anya has, and the sum that she needs to get.

The second line contains $ n $ positive integers $ a_{i}\ ( 1\le a_{i}\le10^{9}) $ — the numbers, written on the cubes. The cubes in the input are described in the order from left to right, starting from the first one.

Multiple cubes can contain the same numbers.

## 输出格式

Output the number of ways to choose some number of cubes and stick exclamation marks on some of them so that the sum of the numbers became equal to the given number $ S $ .

## 说明/提示

In the first sample the only way is to choose both cubes and stick an exclamation mark on each of them.

In the second sample the only way is to choose both cubes but don't stick an exclamation mark on any of them.

In the third sample it is possible to choose any of the cubes in three ways, and also we may choose to stick or not to stick the exclamation mark on it. So, the total number of ways is six.

## 样例 #1

### 输入

```
2 2 30
4 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 2 7
4 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1 1
1 1 1

```

### 输出

```
6

```



---

---
title: "Lengthening Sticks"
layout: "post"
diff: 提高+/省选-
pid: CF571A
tag: ['枚举', '容斥原理']
---

# Lengthening Sticks

## 题目描述

You are given three sticks with positive integer lengths of $ a,b $ , and $ c $ centimeters. You can increase length of some of them by some positive integer number of centimeters (different sticks can be increased by a different length), but in total by at most $ l $ centimeters. In particular, it is allowed not to increase the length of any stick.

Determine the number of ways to increase the lengths of some sticks so that you can form from them a non-degenerate (that is, having a positive area) triangle. Two ways are considered different, if the length of some stick is increased by different number of centimeters in them.

## 输入格式

The single line contains $ 4 $ integers $ a,b,c,l $ ( $ 1<=a,b,c<=3·10^{5} $ , $ 0<=l<=3·10^{5} $ ).

## 输出格式

Print a single integer — the number of ways to increase the sizes of the sticks by the total of at most $ l $ centimeters, so that you can make a non-degenerate triangle from it.

## 说明/提示

In the first sample test you can either not increase any stick or increase any two sticks by $ 1 $ centimeter.

In the second sample test you can increase either the first or the second stick by one centimeter. Note that the triangle made from the initial sticks is degenerate and thus, doesn't meet the conditions.

## 样例 #1

### 输入

```
1 1 1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
1 2 3 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
10 2 1 7

```

### 输出

```
0

```



---

---
title: "Journey"
layout: "post"
diff: 提高+/省选-
pid: CF57D
tag: ['枚举', '最短路', '前缀和']
---

# Journey

## 题目描述

兔子Stewie发现了一个新的平行宇宙。这个宇宙是二维的且是矩形网格，包含n行，m列。它是非常小的：网格的一个格子只能包含一个粒子。这个宇宙中的每一个粒子要么是静态的，要么是动态的。每个静态粒子总是保持在同一位置。由于莫名其妙的引力定律，平行宇宙中没有两个静态粒子存在于一行或一列中，也不可能存在于其它静态粒子的左上，左下，右上，右下的4个格子中。一个动态粒子出现在一个随机的空格子中，随机地选择目的格子（目的格子可能与起始格子重合，请看样例），并沿着最短的路径移动到没有被静态粒子占据的目标格子中。所有空格子被选择为路径的开始或结束的概率是相同的。到达目标格子后，粒子消失。在同一个时刻只允许有一个动态粒子存在。每个移动过程中，这个粒子必须从一个格子移动到相邻的一个格子，这个过程需要一个银河秒。Stewie对宇宙中一个粒子的平均寿命感兴趣。


------------

## 输入格式

第一行包含两个用空格分开的整数：n，m（2＜n，m <＝1000），表示宇宙的大小。后面有n行，每行m个符号，每一个符号描述了没有动态粒子的宇宙——如果第i行第 j个符号等于‘X’，表示有一个静态粒子，如果它是空的，则等于“.”。保证所描述的宇宙满足上述静态粒子排布规则

## 输出格式

输出有一行，一个数，表示粒子的平均寿命。
结果如与正确答案有10的-6次方以内误差，即为正确。

## 样例 #1

### 输入

```
2 2
..
.X

```

### 输出

```
0.888888888889

```

## 样例 #2

### 输入

```
3 3
...
.X.
...

```

### 输出

```
2.000000000000

```



---

---
title: "Once Again..."
layout: "post"
diff: 提高+/省选-
pid: CF582B
tag: ['枚举', '矩阵乘法']
---

# Once Again...

## 题目描述

现有一个长度为 $n×T$ 的序列 $a_1, a_2, ..., a_{n×T}$ ，满足 $a_i=a_{i-n} (n<i<=n×T)$ 。请找出这个序列中的最长不降子序列的长度。

## 输入格式

输入的第一行有两个空格隔开的整数 $n$ 和 $T$ $(1<=n<=100,1<=T<=10^7)$ 。第二行有$n$ 个空格隔开的正整数 $a_1,a_2,...,a_n (1<=a_i<=300)$ 描述了这个序列的前 $n$ 项。

## 输出格式

输出一个整数——最长不降子序列的长度。

## 输入输出样例
略

## 说明/提示

样例中给出的序列如下：3, **1**, 4, **2**, **3**, 1, **4**, 2, 3, 1, **4**, 2. 加粗的数字是一种最长不降子序列的方案。

## 样例 #1

### 输入

```
4 3
3 1 4 2

```

### 输出

```
5

```



---

---
title: "Chocolate Bar"
layout: "post"
diff: 提高+/省选-
pid: CF598E
tag: ['枚举']
---

# Chocolate Bar

## 题目描述

你有一块长方形的巧克力，这块巧克力共有n*m小块。你想吃k小块巧克力，因此你也许需要掰开这块巧克力。

在每一次操作中你可以把任意一块矩形形状的巧克力掰成两块矩形形状的巧克力。你只能沿着巧克力小块之间的分割线掰开巧克力——可以沿着水平方向或是竖直方向掰开。掰开巧克力的花费等于分割线长度的平方。

例如，如果你有一块2*3的巧克力，那么你可以沿着水平方向掰从而得到两块1*3的巧克力，这次操作的花费即为3^2=9。或者你也可以沿着竖直方向掰从而得到一块2*1的巧克力和一块2*2的巧克力，这次操作的花费即为2^2=4。

对于每一个给出的n，m和k，计算出最小花费。你可以用多块巧克力凑出k小块巧克力。剩余的巧克力可以不是完整的一块。

## 输入格式

输入数据的第一行包括1个整数t(1<=t<=40910)，表示数据组数。

接下来的t行每一行都包含3个整数n，m和k(1<=n,m<=30,1<=k<=min(n*m,50))，其意义见上文。

## 输出格式

输出t行，分别表示每一组数据的最小花费。

## 说明/提示

在样例一的第1行这组数据情况下一共需要进行2次操作：
1.把2*2的巧克力掰成两块2*1的巧克力，花费为2^2=4；
2.把2*1的巧克力掰成两块1*1的巧克力，花费为1^2=1。

在样例一的第2行这组数据情况下操作步骤同上。

Translated by @radish布団

## 样例 #1

### 输入

```
4
2 2 1
2 2 3
2 2 2
2 2 4

```

### 输出

```
5
5
4
0

```



---

---
title: "Fibonacci-ish"
layout: "post"
diff: 提高+/省选-
pid: CF633D
tag: ['枚举', '剪枝', '概率论']
---

# Fibonacci-ish

## 题目描述

Yash has recently learnt about the Fibonacci sequence and is very excited about it. He calls a sequence Fibonacci-ish if

1. the sequence consists of at least two elements
2. $ f_{0} $ and $ f_{1} $ are arbitrary
3. $ f_{n+2}=f_{n+1}+f_{n} $ for all $ n>=0 $ .

You are given some sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is rearrange elements of this sequence in such a way that its longest possible prefix is Fibonacci-ish sequence.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=1000 $ ) — the length of the sequence $ a_{i} $ .

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ |a_{i}|<=10^{9} $ ).

## 输出格式

Print the length of the longest possible Fibonacci-ish prefix of the given sequence after rearrangement.

## 说明/提示

In the first sample, if we rearrange elements of the sequence as $ -1 $ , $ 2 $ , $ 1 $ , the whole sequence $ a_{i} $ would be Fibonacci-ish.

In the second sample, the optimal way to rearrange elements is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/d3ff4ea2c12e52c9ca4c15e14139f2b01f478bed.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/67db7509088e9e5340d450cc0af986d1466ce169.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/7be78903e0b1130fefbb3533b84d31cf4efaa940.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/0d98505f3f5d3d9cd5c06747ea4bb30d03a8d1e8.png), $ 28 $ .

## 样例 #1

### 输入

```
3
1 2 -1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
28 35 7 14 21

```

### 输出

```
4

```



---

---
title: "Bulls and Cows"
layout: "post"
diff: 提高+/省选-
pid: CF63C
tag: ['模拟', '枚举']
---

# Bulls and Cows

## 题目描述

The "Bulls and Cows" game needs two people to play. The thinker thinks of a number and the guesser tries to guess it.

The thinker thinks of a four-digit number in the decimal system. All the digits in the number are different and the number may have a leading zero. It can't have more than one leading zero, because all it's digits should be different. The guesser tries to guess the number. He makes a series of guesses, trying experimental numbers and receives answers from the first person in the format " $ x $ bulls $ y $ cows". $ x $ represents the number of digits in the experimental number that occupy the same positions as in the sought number. $ y $ represents the number of digits of the experimental number that present in the sought number, but occupy different positions. Naturally, the experimental numbers, as well as the sought number, are represented by four-digit numbers where all digits are different and a leading zero can be present.

For example, let's suppose that the thinker thought of the number 0123. Then the guessers' experimental number 1263 will receive a reply "1 bull 2 cows" (3 occupies the same positions in both numbers and 1 and 2 are present in both numbers but they occupy different positions). Also, the answer to number 8103 will be "2 bulls 1 cow" (analogically, 1 and 3 occupy the same positions and 0 occupies a different one).

When the guesser is answered "4 bulls 0 cows", the game is over.

Now the guesser has already made several guesses and wants to know whether his next guess can possibly be the last one.

## 输入格式

The first input line contains an integer $ n $ ( $ 1<=n<=10 $ ) which represents the number of already made guesses. Then follow $ n $ lines in the form of " $ a_{i} $ $ b_{i} $ $ c_{i} $ ", where $ a_{i} $ is the $ i $ -th experimental number, $ b_{i} $ is the number of bulls, $ c_{i} $ is the number of cows ( $ 1<=i<=n $ , $ 0<=b_{i},c_{i},b_{i}+c_{i}<=4 $ ). The experimental numbers are correct, i.e., each of them contains exactly four digits, in each of them all the four digits are different, and there can be a leading zero. All the experimental numbers are different. As the guesser hasn't guessed the number yet, the answer "4 bulls 0 cows" is not present.

## 输出格式

If the input data is enough to determine the sought number, print the number with four digits on a single line. If it has less than four digits, add leading zero. If the data is not enough, print "Need more data" without the quotes. If the thinker happens to have made a mistake in his replies, print "Incorrect data" without the quotes.

## 样例 #1

### 输入

```
2
1263 1 2
8103 2 1

```

### 输出

```
Need more data
```

## 样例 #2

### 输入

```
2
1234 2 2
1256 0 2

```

### 输出

```
2134
```

## 样例 #3

### 输入

```
2
0123 1 1
4567 1 2

```

### 输出

```
Incorrect data
```



---

---
title: "Image Preview"
layout: "post"
diff: 提高+/省选-
pid: CF650B
tag: ['枚举', '前缀和']
---

# Image Preview

## 题目描述

Vasya's telephone contains $ n $ photos. Photo number 1 is currently opened on the phone. It is allowed to move left and right to the adjacent photo by swiping finger over the screen. If you swipe left from the first photo, you reach photo $ n $ . Similarly, by swiping right from the last photo you reach photo $ 1 $ . It takes $ a $ seconds to swipe from photo to adjacent.

For each photo it is known which orientation is intended for it — horizontal or vertical. Phone is in the vertical orientation and can't be rotated. It takes $ b $ second to change orientation of the photo.

Vasya has $ T $ seconds to watch photos. He want to watch as many photos as possible. If Vasya opens the photo for the first time, he spends $ 1 $ second to notice all details in it. If photo is in the wrong orientation, he spends $ b $ seconds on rotating it before watching it. If Vasya has already opened the photo, he just skips it (so he doesn't spend any time for watching it or for changing its orientation). It is not allowed to skip unseen photos.

Help Vasya find the maximum number of photos he is able to watch during $ T $ seconds.

## 输入格式

The first line of the input contains 4 integers $ n,a,b,T $ ( $ 1<=n<=5·10^{5} $ , $ 1<=a,b<=1000 $ , $ 1<=T<=10^{9} $ ) — the number of photos, time to move from a photo to adjacent, time to change orientation of a photo and time Vasya can spend for watching photo.

Second line of the input contains a string of length $ n $ containing symbols 'w' and 'h'.

If the $ i $ -th position of a string contains 'w', then the photo $ i $ should be seen in the horizontal orientation.

If the $ i $ -th position of a string contains 'h', then the photo $ i $ should be seen in vertical orientation.

## 输出格式

Output the only integer, the maximum number of photos Vasya is able to watch during those $ T $ seconds.

## 说明/提示

In the first sample test you can rotate the first photo (3 seconds), watch the first photo (1 seconds), move left (2 second), rotate fourth photo (3 seconds), watch fourth photo (1 second). The whole process takes exactly 10 seconds.

Note that in the last sample test the time is not enough even to watch the first photo, also you can't skip it.

## 样例 #1

### 输入

```
4 2 3 10
wwhw

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2 4 13
hhwhh

```

### 输出

```
4

```

## 样例 #3

### 输入

```
5 2 4 1000
hhwhh

```

### 输出

```
5

```

## 样例 #4

### 输入

```
3 1 100 10
whw

```

### 输出

```
0

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
title: "Complete The Graph"
layout: "post"
diff: 提高+/省选-
pid: CF715B
tag: ['枚举', '最短路']
---

# Complete The Graph

## 题目描述

ZS the Coder has drawn an undirected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ m $ edges between them. Each edge of the graph is weighted, each weight is a positive integer.

The next day, ZS the Coder realized that some of the weights were erased! So he wants to reassign positive integer weight to each of the edges which weights were erased, so that the length of the shortest path between vertices $ s $ and $ t $ in the resulting graph is exactly $ L $ . Can you help him?

## 输入格式

The first line contains five integers $ n,m,L,s,t $ ( $ 2<=n<=1000,1<=m<=10000,1<=L<=10^{9},0<=s,t<=n-1,s≠t $ ) — the number of vertices, number of edges, the desired length of shortest path, starting vertex and ending vertex respectively.

Then, $ m $ lines describing the edges of the graph follow. $ i $ -th of them contains three integers, $ u_{i},v_{i},w_{i} $ ( $ 0<=u_{i},v_{i}<=n-1,u_{i}≠v_{i},0<=w_{i}<=10^{9} $ ). $ u_{i} $ and $ v_{i} $ denote the endpoints of the edge and $ w_{i} $ denotes its weight. If $ w_{i} $ is equal to $ 0 $ then the weight of the corresponding edge was erased.

It is guaranteed that there is at most one edge between any pair of vertices.

## 输出格式

Print "NO" (without quotes) in the only line if it's not possible to assign the weights in a required way.

Otherwise, print "YES" in the first line. Next $ m $ lines should contain the edges of the resulting graph, with weights assigned to edges which weights were erased. $ i $ -th of them should contain three integers $ u_{i} $ , $ v_{i} $ and $ w_{i} $ , denoting an edge between vertices $ u_{i} $ and $ v_{i} $ of weight $ w_{i} $ . The edges of the new graph must coincide with the ones in the graph from the input. The weights that were not erased must remain unchanged whereas the new weights can be any positive integer not exceeding $ 10^{18} $ .

The order of the edges in the output doesn't matter. The length of the shortest path between $ s $ and $ t $ must be equal to $ L $ .

If there are multiple solutions, print any of them.

## 说明/提示

Here's how the graph in the first sample case looks like :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715B/c442fd279761bfa74ef367b518cede1e1fa97983.png)In the first sample case, there is only one missing edge weight. Placing the weight of $ 8 $ gives a shortest path from $ 0 $ to $ 4 $ of length $ 13 $ .

In the second sample case, there is only a single edge. Clearly, the only way is to replace the missing weight with $ 123456789 $ .

In the last sample case, there is no weights to assign but the length of the shortest path doesn't match the required value, so the answer is "NO".

## 样例 #1

### 输入

```
5 5 13 0 4
0 1 5
2 1 2
3 2 3
1 4 0
4 3 4

```

### 输出

```
YES
0 1 5
2 1 2
3 2 3
1 4 8
4 3 4

```

## 样例 #2

### 输入

```
2 1 123456789 0 1
0 1 0

```

### 输出

```
YES
0 1 123456789

```

## 样例 #3

### 输入

```
2 1 999999999 1 0
0 1 1000000000

```

### 输出

```
NO

```



---

---
title: "Bottles"
layout: "post"
diff: 提高+/省选-
pid: CF730J
tag: ['贪心', '枚举', '背包 DP']
---

# Bottles

## 题目描述

有 $n$ 瓶水，第 $i$ 瓶水的水量为 $a_i$，容量为 $b_i$。将 $1$ 单位水从一个瓶子转移到另一个瓶子所消耗时间为 $1$ 秒，且可以进行无限次转移。求储存所有水所需最小瓶子数 $k$ 以及该情况下所用最小时间 $t$。

## 输入格式

第一行输入一个正整数 $n$（$1\le n\le 100$）。

第二行输入 $n$ 个正整数，第 $i$ 个正整数表示 $a_i$（$1\le a_i \le 100$）。

第三行输入 $n$ 个正整数，第 $i$ 个正整数表示 $b_i$（$1\le b_i \le100$）。

对于每一个 $i$，满足$a_i\le b_i$。

## 输出格式

输出一行两个整数：$k$ 和 $t$。

## 样例 #1

### 输入

```
4
3 3 4 3
4 7 6 5

```

### 输出

```
2 6

```

## 样例 #2

### 输入

```
2
1 1
100 100

```

### 输出

```
1 1

```

## 样例 #3

### 输入

```
5
10 30 5 6 24
10 41 7 8 24

```

### 输出

```
3 11

```



---

---
title: "Vladik and cards"
layout: "post"
diff: 提高+/省选-
pid: CF743E
tag: ['枚举', '剪枝', '状态合并', '向量']
---

# Vladik and cards

## 题目描述

Vladik was bored on his way home and decided to play the following game. He took $ n $ cards and put them in a row in front of himself. Every card has a positive integer number not exceeding $ 8 $ written on it. He decided to find the longest subsequence of cards which satisfies the following conditions:

- the number of occurrences of each number from $ 1 $ to $ 8 $ in the subsequence doesn't differ by more then $ 1 $ from the number of occurrences of any other number. Formally, if there are $ c_{k} $ cards with number $ k $ on them in the subsequence, than for all pairs of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743E/0c6cc5f621659ae2ddf5ab0dac10dd28e326ec14.png) the condition $ |c_{i}-c_{j}|<=1 $ must hold.
- if there is at least one card with number $ x $ on it in the subsequence, then all cards with number $ x $ in this subsequence must form a continuous segment in it (but not necessarily a continuous segment in the original sequence). For example, the subsequence $ [1,1,2,2] $ satisfies this condition while the subsequence $ [1,2,2,1] $ doesn't. Note that $ [1,1,2,2] $ doesn't satisfy the first condition.

Please help Vladik to find the length of the longest subsequence that satisfies both conditions.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of cards in Vladik's sequence.

The second line contains the sequence of $ n $ positive integers not exceeding $ 8 $ — the description of Vladik's sequence.

## 输出格式

Print single integer — the length of the longest subsequence of Vladik's sequence that satisfies both conditions.

## 说明/提示

In the first sample all the numbers written on the cards are equal, so you can't take more than one card, otherwise you'll violate the first condition.

## 样例 #1

### 输入

```
3
1 1 1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
8
8 7 6 5 4 3 2 1

```

### 输出

```
8
```

## 样例 #3

### 输入

```
24
1 8 1 2 8 2 3 8 3 4 8 4 5 8 5 6 8 6 7 8 7 8 8 8

```

### 输出

```
17
```



---

---
title: "Cartons of milk"
layout: "post"
diff: 提高+/省选-
pid: CF767D
tag: ['贪心', '枚举', '排序']
---

# Cartons of milk

## 题目描述

Olya likes milk very much. She drinks $ k $ cartons of milk each day if she has at least $ k $ and drinks all of them if she doesn't. But there's an issue — expiration dates. Each carton has a date after which you can't drink it (you still can drink it exactly at the date written on the carton). Due to this, if Olya's fridge contains a carton past its expiry date, she throws it away.

Olya hates throwing out cartons, so when she drinks a carton, she chooses the one which expires the fastest. It's easy to understand that this strategy minimizes the amount of cartons thrown out and lets her avoid it if it's even possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767D/609b94e7f0b8a5d407df0e97345c78713f56ad66.png)Milk. Best before: 20.02.2017.The main issue Olya has is the one of buying new cartons. Currently, there are $ n $ cartons of milk in Olya's fridge, for each one an expiration date is known (how soon does it expire, measured in days). In the shop that Olya visited there are $ m $ cartons, and the expiration date is known for each of those cartons as well.

Find the maximum number of cartons Olya can buy so that she wouldn't have to throw away any cartons. Assume that Olya drank no cartons today.

## 输入格式

In the first line there are three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m<=10^{6} $ , $ 1<=k<=n+m $ ) — the amount of cartons in Olya's fridge, the amount of cartons in the shop and the number of cartons Olya drinks each day.

In the second line there are $ n $ integers $ f_{1},f_{2},...,f_{n} $ ( $ 0<=f_{i}<=10^{7} $ ) — expiration dates of the cartons in Olya's fridge. The expiration date is expressed by the number of days the drinking of this carton can be delayed. For example, a $ 0 $ expiration date means it must be drunk today, $ 1 $ — no later than tomorrow, etc.

In the third line there are $ m $ integers $ s_{1},s_{2},...,s_{m} $ ( $ 0<=s_{i}<=10^{7} $ ) — expiration dates of the cartons in the shop in a similar format.

## 输出格式

If there's no way for Olya to drink the cartons she already has in her fridge, print -1.

Otherwise, in the first line print the maximum number $ x $ of cartons which Olya can buy so that she wouldn't have to throw a carton away. The next line should contain exactly $ x $ integers — the numbers of the cartons that should be bought (cartons are numbered in an order in which they are written in the input, starting with $ 1 $ ). Numbers should not repeat, but can be in arbitrary order. If there are multiple correct answers, print any of them.

## 说明/提示

In the first example $ k=2 $ and Olya has three cartons with expiry dates $ 0 $ , $ 1 $ and $ 1 $ (they expire today, tomorrow and tomorrow), and the shop has $ 3 $ cartons with expiry date $ 0 $ and $ 3 $ cartons with expiry date $ 2 $ . Olya can buy three cartons, for example, one with the expiry date $ 0 $ and two with expiry date $ 2 $ .

In the second example all three cartons Olya owns expire today and it means she would have to throw packets away regardless of whether she buys an extra one or not.

In the third example Olya would drink $ k=2 $ cartons today (one she alreay has in her fridge and one from the shop) and the remaining one tomorrow.

## 样例 #1

### 输入

```
3 6 2
1 0 1
2 0 2 0 0 2

```

### 输出

```
3
1 2 3
```

## 样例 #2

### 输入

```
3 1 2
0 0 0
1

```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2 1 2
0 1
0

```

### 输出

```
1
1 
```



---

---
title: "Jon Snow and his Favourite Number"
layout: "post"
diff: 提高+/省选-
pid: CF768C
tag: ['枚举']
---

# Jon Snow and his Favourite Number

## 题目描述

题意:

你有一串长度为n的序列a,重复k次操作,问操作后的序列的极值值.
操作:
将序列从小到大排序,从1标号,对序号为奇数的数^(xor)x.

## 输入格式

第一行三个数n,k,x.
接线来一行n个整数,为序列元素.

## 输出格式

一行两个数,第一个为最大值,第二个为最小值.

## 说明/提示

n,k:[1,1e5]
x,a[i]:[1,1e3]

注意:

None.

感谢@尘染梦 提供的翻译

## 样例 #1

### 输入

```
5 1 2
9 7 11 15 5

```

### 输出

```
13 7
```

## 样例 #2

### 输入

```
2 100000 569
605 986

```

### 输出

```
986 605
```



---

---
title: "Hanoi Factory"
layout: "post"
diff: 提高+/省选-
pid: CF777E
tag: ['枚举', '排序']
---

# Hanoi Factory

## 题目描述

你肯定听说过著名的游戏汉诺塔吧，但是你知道有一个神奇的工厂专门制造这种游戏塔上的环吗？很久之前，古埃及的裁定者命令“汉诺工厂”（上文提到的工厂）的工人制造一座尽可能高的汉诺塔，而他们没有做好准备去执行这样一个奇怪的命令，所以他们不得不用已经造好的环。
工厂储备有$n$个环，其内径为$a_i$，外径为$b_i$，高度为$h_i$。要求环的放置条件如下：
-    塔的外半径从下至上为非递增序列，即越下面的环外径不能小于上面的环
-    环不能掉下来，即相邻两环上方的环的外径必须大于下面的环的内径
-    塔的高度必须最大

## 输入格式

第$1$行一个数$n$，代表环的数量
第$2$~$n-1$行，每行3个数$a_i,b_i,h_i$代表环的内径，外径，高度

## 输出格式

一个整数，代表塔的最大高度

## 说明/提示

Translated by Venus

## 样例 #1

### 输入

```
3
1 5 1
2 6 2
3 7 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4
1 2 1
1 3 3
4 6 2
5 7 1

```

### 输出

```
4

```



---

---
title: "Karen and Supermarket"
layout: "post"
diff: 提高+/省选-
pid: CF815C
tag: ['动态规划 DP', '枚举']
---

# Karen and Supermarket

## 题目描述

On the way home, Karen decided to stop by the supermarket to buy some groceries.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815C/155b4f0d440b0d3ff60763603980cf23ed9ae97d.png)She needs to buy a lot of goods, but since she is a student her budget is still quite limited. In fact, she can only spend up to $ b $ dollars.

The supermarket sells $ n $ goods. The $ i $ -th good can be bought for $ c_{i} $ dollars. Of course, each good can only be bought once.

Lately, the supermarket has been trying to increase its business. Karen, being a loyal customer, was given $ n $ coupons. If Karen purchases the $ i $ -th good, she can use the $ i $ -th coupon to decrease its price by $ d_{i} $ . Of course, a coupon cannot be used without buying the corresponding good.

There is, however, a constraint with the coupons. For all $ i>=2 $ , in order to use the $ i $ -th coupon, Karen must also use the $ x_{i} $ -th coupon (which may mean using even more coupons to satisfy the requirement for that coupon).

Karen wants to know the following. What is the maximum number of goods she can buy, without exceeding her budget $ b $ ?

## 输入格式

The first line of input contains two integers $ n $ and $ b $ ( $ 1<=n<=5000 $ , $ 1<=b<=10^{9} $ ), the number of goods in the store and the amount of money Karen has, respectively.

The next $ n $ lines describe the items. Specifically:

- The $ i $ -th line among these starts with two integers, $ c_{i} $ and $ d_{i} $ ( $ 1<=d_{i}<c_{i}<=10^{9} $ ), the price of the $ i $ -th good and the discount when using the coupon for the $ i $ -th good, respectively.
- If $ i>=2 $ , this is followed by another integer, $ x_{i} $ ( $ 1<=x_{i}<i $ ), denoting that the $ x_{i} $ -th coupon must also be used before this coupon can be used.

## 输出格式

Output a single integer on a line by itself, the number of different goods Karen can buy, without exceeding her budget.

## 说明/提示

In the first test case, Karen can purchase the following $ 4 $ items:

- Use the first coupon to buy the first item for $ 10-9=1 $ dollar.
- Use the third coupon to buy the third item for $ 12-2=10 $ dollars.
- Use the fourth coupon to buy the fourth item for $ 20-18=2 $ dollars.
- Buy the sixth item for $ 2 $ dollars.

The total cost of these goods is $ 15 $ , which falls within her budget. Note, for example, that she cannot use the coupon on the sixth item, because then she should have also used the fifth coupon to buy the fifth item, which she did not do here.

In the second test case, Karen has enough money to use all the coupons and purchase everything.

## 样例 #1

### 输入

```
6 16
10 9
10 5 1
12 2 1
20 18 3
10 2 3
2 1 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 10
3 1
3 1 1
3 1 2
3 1 3
3 1 4

```

### 输出

```
5

```



---

---
title: "The Bakery"
layout: "post"
diff: 提高+/省选-
pid: CF833B
tag: ['动态规划 DP', '线段树', '枚举', '动态规划优化']
---

# The Bakery

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833B/f46eccace96d929fa4c99a2b4ae6e89027b73fa1.png)Some time ago Slastyona the Sweetmaid decided to open her own bakery! She bought required ingredients and a wonder-oven which can bake several types of cakes, and opened the bakery.

Soon the expenses started to overcome the income, so Slastyona decided to study the sweets market. She learned it's profitable to pack cakes in boxes, and that the more distinct cake types a box contains (let's denote this number as the value of the box), the higher price it has.

She needs to change the production technology! The problem is that the oven chooses the cake types on its own and Slastyona can't affect it. However, she knows the types and order of $ n $ cakes the oven is going to bake today. Slastyona has to pack exactly $ k $ boxes with cakes today, and she has to put in each box several (at least one) cakes the oven produced one right after another (in other words, she has to put in a box a continuous segment of cakes).

Slastyona wants to maximize the total value of all boxes with cakes. Help her determine this maximum possible total value.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=35000 $ , $ 1<=k<=min(n,50) $ ) – the number of cakes and the number of boxes, respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ) – the types of cakes in the order the oven bakes them.

## 输出格式

Print the only integer – the maximum total value of all boxes with cakes.

## 说明/提示

In the first example Slastyona has only one box. She has to put all cakes in it, so that there are two types of cakes in the box, so the value is equal to $ 2 $ .

In the second example it is profitable to put the first two cakes in the first box, and all the rest in the second. There are two distinct types in the first box, and three in the second box then, so the total value is $ 5 $ .

## 样例 #1

### 输入

```
4 1
1 2 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 2
1 3 3 1 4 4 4

```

### 输出

```
5

```

## 样例 #3

### 输入

```
8 3
7 7 8 7 7 8 1 7

```

### 输出

```
6

```



---

---
title: "Sum of Medians"
layout: "post"
diff: 提高+/省选-
pid: CF85D
tag: ['线段树', '枚举', '排序', '分块']
---

# Sum of Medians

## 题目描述

In one well-known algorithm of finding the $ k $ -th order statistics we should divide all elements into groups of five consecutive elements and find the median of each five. A median is called the middle element of a sorted array (it's the third largest element for a group of five). To increase the algorithm's performance speed on a modern video card, you should be able to find a sum of medians in each five of the array.

A sum of medians of a sorted $ k $ -element set $ S={a_{1},a_{2},...,a_{k}} $ , where $ a_{1}&lt;a_{2}&lt;a_{3}&lt;...&lt;a_{k} $ , will be understood by as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/ade3397df6e8978ddadfc100b4ccb88beefd1e3f.png)The ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) operator stands for taking the remainder, that is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) stands for the remainder of dividing $ x $ by $ y $ .

To organize exercise testing quickly calculating the sum of medians for a changing set was needed.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=10^{5} $ ), the number of operations performed.

Then each of $ n $ lines contains the description of one of the three operations:

- add $ x $  — add the element $ x $ to the set;
- del $ x $  — delete the element $ x $ from the set;
- sum — find the sum of medians of the set.

For any add $ x $  operation it is true that the element $ x $ is not included in the set directly before the operation.

For any del $ x $  operation it is true that the element $ x $ is included in the set directly before the operation.

All the numbers in the input are positive integers, not exceeding $ 10^{9} $ .

## 输出格式

For each operation sum print on the single line the sum of medians of the current set. If the set is empty, print 0.

Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams (also you may use the %I64d specificator).

## 样例 #1

### 输入

```
6
add 4
add 5
add 1
add 2
add 3
sum

```

### 输出

```
3

```

## 样例 #2

### 输入

```
14
add 1
add 7
add 2
add 5
sum
add 6
add 8
add 9
add 3
add 4
add 10
sum
del 1
sum

```

### 输出

```
5
11
13

```



---

---
title: "Powerful array"
layout: "post"
diff: 提高+/省选-
pid: CF86D
tag: ['莫队', '枚举']
---

# Powerful array

## 题目描述

An array of positive integers $ a_{1},a_{2},...,a_{n} $ is given. Let us consider its arbitrary subarray $ a_{l},a_{l+1}...,a_{r} $ , where $ 1<=l<=r<=n $ . For every positive integer $ s $ denote by $ K_{s} $ the number of occurrences of $ s $ into the subarray. We call the power of the subarray the sum of products $ K_{s}·K_{s}·s $ for every positive integer $ s $ . The sum contains only finite number of nonzero summands as the number of different values in the array is indeed finite.

You should calculate the power of $ t $ given subarrays.

## 输入格式

First line contains two integers $ n $ and $ t $ ( $ 1<=n,t<=200000 $ ) — the array length and the number of queries correspondingly.

Second line contains $ n $ positive integers $ a_{i} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array.

Next $ t $ lines contain two positive integers $ l $ , $ r $ ( $ 1<=l<=r<=n $ ) each — the indices of the left and the right ends of the corresponding subarray.

## 输出格式

Output $ t $ lines, the $ i $ -th line of the output should contain single positive integer — the power of the $ i $ -th query subarray.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preferred to use cout stream (also you may use %I64d).

## 说明/提示

Consider the following array (see the second sample) and its \[2, 7\] subarray (elements of the subarray are colored):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86D/5e3c36b108711f9f95c3c3519472e9f583328f8b.png) Then $ K_{1}=3 $ , $ K_{2}=2 $ , $ K_{3}=1 $ , so the power is equal to $ 3^{2}·1+2^{2}·2+1^{2}·3=20 $ .

## 样例 #1

### 输入

```
3 2
1 2 1
1 2
1 3

```

### 输出

```
3
6

```

## 样例 #2

### 输入

```
8 3
1 1 2 2 1 3 1 1
2 7
1 6
2 7

```

### 输出

```
20
20
20

```



---

---
title: "Looking for Order"
layout: "post"
diff: 提高+/省选-
pid: CF8C
tag: ['动态规划 DP', '枚举', '状态合并']
---

# Looking for Order

## 题目描述

Lena喜欢秩序井然的生活。一天，她要去上大学了。突然，她发现整个房间乱糟糟的——她的手提包里的物品都散落在了地上。她想把所有的物品都放回她的手提包。但是，这里有一点问题：她一次最多只能拿两个物品，她也不能移动她的手提包。并且，因为她爱整洁的习惯，如果她拿起了一个物品，她也不能将它放在其他地方，除非放回她的手提包。

Lena把她的房间划分为了一个平面直角坐标系。现在Lena给你她的手提包和每个散落的物品的坐标（当然，一开始的时候她就和手提包站在一个地方）。她从坐标 $(x1,y1)$  走到坐标 $(x2,y2)$  需要用 $(x1-x2)^2+(y1-y2)^2$  单位的时间。现在，Lena将告诉你她的房间的情况，请你为Lena找到一个拾起每个物品的顺序，使她拾起所有物品所需的总时间最小。当然，Lena最后需要返回她的手提包。

## 输入格式

输入文件的第一行为Lena的手提包的坐标 $x_s$  , $y_s$  。第二行为一个正整数 $n$  ，表示总的需要拾起的物品数。接下来的 $n$  行每行包括两个整数，表示每个物品的坐标。

## 输出格式

输出的第一行为一个正整数，表示Lena拾起所有物品所需的最小时间。

输出的第二行为Lena拾起每个物品的顺序。（每一个物品由它的编号代表，0表示手提包）她应该从手提包(0)出发，在手提包(0)结束。

如,0 1 2 0 3 0

表示她从手提包出发，先拾起1号物品，再拾起2号物品，然后返回手提包（并放下1和2），再拾起3号物品，最后返回手提包。

如果有多条允许的路径，输出任一条。

## 输入输出样例
略

感谢@星烁晶熠辉 提供的翻译

## 样例 #1

### 输入

```
0 0
2
1 1
-1 1

```

### 输出

```
8
0 1 2 0 

```

## 样例 #2

### 输入

```
1 1
3
4 3
3 4
0 0

```

### 输出

```
32
0 1 2 0 3 0 

```



---

---
title: "Beads"
layout: "post"
diff: 提高+/省选-
pid: CF8E
tag: ['枚举', '进制', '概率论']
---

# Beads

## 题目描述

One Martian boy called Zorg wants to present a string of beads to his friend from the Earth — Masha. He knows that Masha likes two colours: blue and red, — and right in the shop where he has come, there is a variety of adornments with beads of these two colours. All the strings of beads have a small fastener, and if one unfastens it, one might notice that all the strings of beads in the shop are of the same length. Because of the peculiarities of the Martian eyesight, if Zorg sees one blue-and-red string of beads first, and then the other with red beads instead of blue ones, and blue — instead of red, he regards these two strings of beads as identical. In other words, Zorg regards as identical not only those strings of beads that can be derived from each other by the string turnover, but as well those that can be derived from each other by a mutual replacement of colours and/or by the string turnover.

It is known that all Martians are very orderly, and if a Martian sees some amount of objects, he tries to put them in good order. Zorg thinks that a red bead is smaller than a blue one. Let's put 0 for a red bead, and 1 — for a blue one. From two strings the Martian puts earlier the string with a red bead in the $ i $ -th position, providing that the second string has a blue bead in the $ i $ -th position, and the first two beads $ i-1 $ are identical.

At first Zorg unfastens all the strings of beads, and puts them into small heaps so, that in each heap strings are identical, in his opinion. Then he sorts out the heaps and chooses the minimum string in each heap, in his opinion. He gives the unnecassary strings back to the shop assistant and says he doesn't need them any more. Then Zorg sorts out the remaining strings of beads and buys the string with index $ k $ .

All these manupulations will take Zorg a lot of time, that's why he asks you to help and find the string of beads for Masha.

## 输入格式

The input file contains two integers $ n $ and $ k $ ( $ 2<=n<=50;1<=k<=10^{16} $ ) —the length of a string of beads, and the index of the string, chosen by Zorg.

## 输出格式

Output the $ k $ -th string of beads, putting 0 for a red bead, and 1 — for a blue one. If it s impossible to find the required string, output the only number -1.

## 说明/提示

Let's consider the example of strings of length 4 — 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110. Zorg will divide them into heaps: {0001, 0111, 1000, 1110}, {0010, 0100, 1011, 1101}, {0011, 1100}, {0101, 1010}, {0110, 1001}. Then he will choose the minimum strings of beads in each heap: 0001, 0010, 0011, 0101, 0110. The forth string — 0101.

## 样例 #1

### 输入

```
4 4

```

### 输出

```
0101

```



---

---
title: "Mass Change Queries"
layout: "post"
diff: 提高+/省选-
pid: CF911G
tag: ['线段树', '枚举']
---

# Mass Change Queries

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You have to process $ q $ queries to this array; each query is given as four numbers $ l $ , $ r $ , $ x $ and $ y $ , denoting that for every $ i $ such that $ l<=i<=r $ and $ a_{i}=x $ you have to set $ a_{i} $ equal to $ y $ .

Print the array after all queries are processed.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=200000 $ ) — the size of array $ a $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=100 $ ) — the elements of array $ a $ .

The third line contains one integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries you have to process.

Then $ q $ lines follow. $ i $ -th line contains four integers $ l $ , $ r $ , $ x $ and $ y $ denoting $ i $ -th query ( $ 1<=l<=r<=n $ , $ 1<=x,y<=100 $ ).

## 输出格式

Print $ n $ integers — elements of array $ a $ after all changes are made.

## 样例 #1

### 输入

```
5
1 2 3 4 5
3
3 5 3 5
1 5 5 1
1 5 1 5

```

### 输出

```
5 2 5 4 5 
```



---

---
title: "Imbalance Value of a Tree"
layout: "post"
diff: 提高+/省选-
pid: CF915F
tag: ['并查集', '枚举']
---

# Imbalance Value of a Tree

## 题目描述

给定一棵树，每个顶点都被写上了一个数，第 $i$ 个顶点写上的数是 $a_i$。定义一个函数 $I(x,y)$ 表示从顶点 $x$ 到 $y$ 的简单路径上 $a_i$ 的最大值和最小值的差。

你要求出 $\sum_{i=1}^{n}\sum_{j=i}^{n}I(i,j)$。

## 输入格式

第一行一个正整数 $n(1\le n\le 10^6)$，表示树上节点个数。

第二行 $n$ 个正整数 $a_1,a_2,\cdots,a_n$，表示树上每个节点写的数值。

接下来 $n-1$ 行，每行两个正整数 $x,y$，表示一条边连接节点 $x$ 和 $y$（$1\le x,y\le n$，$x\ne y$）。保证图是一棵树。

## 输出格式

输出一个数，表示 $\sum_{i=1}^n\sum_{j=i}^nI(i,j)$。

## 样例 #1

### 输入

```
4
2 2 3 1
1 2
1 3
1 4

```

### 输出

```
6

```



---

---
title: "Connected Components?"
layout: "post"
diff: 提高+/省选-
pid: CF920E
tag: ['枚举', '广度优先搜索 BFS', '连通块']
---

# Connected Components?

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920E/2671f3d87e6b285ebb30abeafea800e65bb56d51.png) edges. Instead of giving you the edges that exist in the graph, we give you $ m $ unordered pairs ( $ x,y $ ) such that there is no edge between $ x $ and $ y $ , and if some pair of vertices is not listed in the input, then there is an edge between these vertices.

You have to find the number of connected components in the graph and the size of each component. A connected component is a set of vertices $ X $ such that for every two vertices from this set there exists at least one path in the graph connecting these vertices, but adding any other vertex to $ X $ violates this rule.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=200000 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920E/2a08d4fdef413c2e634516e97a2188a97c148ac8.png)).

Then $ m $ lines follow, each containing a pair of integers $ x $ and $ y $ ( $ 1<=x,y<=n $ , $ x≠y $ ) denoting that there is no edge between $ x $ and $ y $ . Each pair is listed at most once; ( $ x,y $ ) and ( $ y,x $ ) are considered the same (so they are never listed in the same test). If some pair of vertices is not listed in the input, then there exists an edge between those vertices.

## 输出格式

Firstly print $ k $ — the number of connected components in this graph.

Then print $ k $ integers — the sizes of components. You should output these integers in non-descending order.

## 样例 #1

### 输入

```
5 5
1 2
3 4
3 2
4 2
2 5

```

### 输出

```
2
1 4 
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
title: "Largest Beautiful Number"
layout: "post"
diff: 提高+/省选-
pid: CF946E
tag: ['字符串', '枚举', '构造']
---

# Largest Beautiful Number

## 题目描述

如果一个正整数在十进制表示法下，不含前导零，有偶数个数字，并且对于它的所有数字来说，有一种排列方式使得这些数字组成一个回文数，那么这个数就是“美丽数”。例如4242是一个美丽数，因为它含有4个数字，这4个数字可以组成一个回文数2442。

给定一个正整数s，求严格小于s的最大美丽数。

## 输入格式

第1行，1个整数t，表示数据组数。

下面t行，每行1个十进制数s。

## 输出格式

对于每个s，输出严格小于s的最大美丽数。

数据保证有解。

## 说明/提示

t <= 10^5 
 

s的长度<= 2*10^5 

感谢@刷题永动机 提供的翻译

## 样例 #1

### 输入

```
4
89
88
1000
28923845

```

### 输出

```
88
77
99
28923839

```



---

---
title: "Mahmoud and Ehab and another array construction task"
layout: "post"
diff: 提高+/省选-
pid: CF959D
tag: ['枚举', '素数判断,质数,筛法']
---

# Mahmoud and Ehab and another array construction task

## 题目描述

Mahmoud has an array $ a $ consisting of $ n $ integers. He asked Ehab to find another array $ b $ of the same length such that:

- $ b $ is lexicographically greater than or equal to $ a $ .
- $ b_{i}>=2 $ .
- $ b $ is pairwise coprime: for every $ 1<=i<j<=n $ , $ b_{i} $ and $ b_{j} $ are coprime, i. e. $ GCD(b_{i},b_{j})=1 $ , where $ GCD(w,z) $ is the greatest common divisor of $ w $ and $ z $ .

Ehab wants to choose a special array so he wants the lexicographically minimal array between all the variants. Can you find it?

An array $ x $ is lexicographically greater than an array $ y $ if there exists an index $ i $ such than $ x_{i}>y_{i} $ and $ x_{j}=y_{j} $ for all $ 1<=j<i $ . An array $ x $ is equal to an array $ y $ if $ x_{i}=y_{i} $ for all $ 1<=i<=n $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=10^{5}) $ , the number of elements in $ a $ and $ b $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (2<=a_{i}<=10^{5}) $ , the elements of $ a $ .

## 输出格式

Output $ n $ space-separated integers, the $ i $ -th of them representing $ b_{i} $ .

## 说明/提示

Note that in the second sample, the array is already pairwise coprime so we printed it.

## 样例 #1

### 输入

```
5
2 3 5 4 13

```

### 输出

```
2 3 5 7 11 
```

## 样例 #2

### 输入

```
3
10 3 7

```

### 输出

```
10 3 7 
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

---
title: "Nastya and a Game"
layout: "post"
diff: 提高+/省选-
pid: CF992D
tag: ['枚举', '概率论']
---

# Nastya and a Game

## 题目描述

$Nastya$  在生日那天收到了一个大小为  $n$  的数组，她想知道数组存放的序列中，有多少的子串满足其中所有的数的乘积是数的总和的  $k$  倍。请帮她得到答案。

## 输入格式

第  $1$  行，有  $2$  个整数，分别表示数组的大小  $n$  和倍数  $k$ 。

（数据范围： $1 \leqslant n \leqslant 2 \times 10^{5}$ ， $1 \leqslant k \leqslant 10^5$ ）

第  $2$  行，有  $n$  个整数，表示数组的元素  $a_i$ 。

（数据范围： $1 \leqslant a_i \leqslant 10^8$ ）

## 输出格式

仅  $1$  个整数，表示符合条件的子串数量。

## 说明/提示

- 第  $1$  组样例的解释：

只有  $1$  子串  $\{1\}$ ，因为  $\frac{1}{1}=k=1$ ，所以它恰好是符合条件的。

- 第  $2$  组样例的解释：

 $\{6,\ 3\}$  中所有数的乘积是  $18$ ，总和是  $9$ ，因为  $\frac{18}{9}=k=2$ ，所以它符合条件。

 $\{3,\ 8,\ 1\}$ 中所有数的乘积是  $24$ ，总和是  $12$ ，因为  $\frac{24}{12} = k = 2$ ，所以它也符合条件。

综上所述，共有  $2$  个子串符合条件。

感谢@Sooke 提供翻译以及@ZqlwMatt 修正

## 样例 #1

### 输入

```
1 1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 2
6 3 8 1

```

### 输出

```
2

```



---

---
title: "Roman Digits"
layout: "post"
diff: 提高+/省选-
pid: CF997B
tag: ['枚举']
---

# Roman Digits

## 题目描述

Let's introduce a number system which is based on a roman digits. There are digits I, V, X, L which correspond to the numbers $ 1 $ , $ 5 $ , $ 10 $ and $ 50 $ respectively. The use of other roman digits is not allowed.

Numbers in this system are written as a sequence of one or more digits. We define the value of the sequence simply as the sum of digits in it.

For example, the number XXXV evaluates to $ 35 $ and the number IXI — to $ 12 $ .

Pay attention to the difference to the traditional roman system — in our system any sequence of digits is valid, moreover the order of digits doesn't matter, for example IX means $ 11 $ , not $ 9 $ .

One can notice that this system is ambiguous, and some numbers can be written in many different ways. Your goal is to determine how many distinct integers can be represented by exactly $ n $ roman digits I, V, X, L.

## 输入格式

The only line of the input file contains a single integer $ n $ ( $ 1 \le n \le 10^9 $ ) — the number of roman digits to use.

## 输出格式

Output a single integer — the number of distinct integers which can be represented using $ n $ roman digits exactly.

## 说明/提示

In the first sample there are exactly $ 4 $ integers which can be represented — I, V, X and L.

In the second sample it is possible to represent integers $ 2 $ (II), $ 6 $ (VI), $ 10 $ (VV), $ 11 $ (XI), $ 15 $ (XV), $ 20 $ (XX), $ 51 $ (IL), $ 55 $ (VL), $ 60 $ (XL) and $ 100 $ (LL).

## 样例 #1

### 输入

```
1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2

```

### 输出

```
10

```

## 样例 #3

### 输入

```
10

```

### 输出

```
244

```



---

