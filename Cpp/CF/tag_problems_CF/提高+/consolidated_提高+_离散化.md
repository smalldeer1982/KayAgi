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
title: "Bitwise Slides"
layout: "post"
diff: 提高+/省选-
pid: CF2066C
tag: ['动态规划 DP', '离散化', '位运算']
---

# Bitwise Slides

## 题目描述

给定一个数组 $a_1, a_2, \ldots, a_n$，以及三个初始值为零的变量 $P, Q, R$。

你需要按从 $1$ 到 $n$ 的顺序依次处理所有数字 $a_1, a_2, \ldots, a_n$。当处理当前元素 $a_i$ 时，你必须从以下三个操作中任选一个执行：
1. $P := P \oplus a_i$
2. $Q := Q \oplus a_i$
3. $R := R \oplus a_i$

其中 $\oplus$ 表示按位异或操作。

执行操作时必须遵守核心规则：每次操作后，三个数 $P, Q, R$ 必须满足两两不互异。

所有 $n$ 个操作共有 $3^n$ 种可能的执行方式。求其中不违反核心规则的方式数量。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出不违反核心规则的操作方式数量对 $10^9 + 7$ 取模后的结果。

## 说明/提示

第一个测试用例中，存在 3 种合法操作序列：PPP、QQQ、RRR。

第二个测试用例中，存在 9 种合法操作序列：PPPP、PPPQ、PPPR、QQQP、QQQQ、QQQR、RRRP、RRRQ、RRRR。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3
1 7 9
4
179 1 1 179
5
1 2 3 3 2
12
8 2 5 3 9 1 8 12 9 9 9 4
1
1000000000
```

### 输出

```
3
9
39
123
3
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
title: "Ant colony"
layout: "post"
diff: 提高+/省选-
pid: CF474F
tag: ['线段树', '离散化']
---

# Ant colony

## 题目描述

Mole is hungry again. He found one ant colony, consisting of $ n $ ants, ordered in a row. Each ant $ i $ ( $ 1<=i<=n $ ) has a strength $ s_{i} $ .

In order to make his dinner more interesting, Mole organizes a version of «Hunger Games» for the ants. He chooses two numbers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) and each pair of ants with indices between $ l $ and $ r $ (inclusively) will fight. When two ants $ i $ and $ j $ fight, ant $ i $ gets one battle point only if $ s_{i} $ divides $ s_{j} $ (also, ant $ j $ gets one battle point only if $ s_{j} $ divides $ s_{i} $ ).

After all fights have been finished, Mole makes the ranking. An ant $ i $ , with $ v_{i} $ battle points obtained, is going to be freed only if $ v_{i}=r-l $ , or in other words only if it took a point in every fight it participated. After that, Mole eats the rest of the ants. Note that there can be many ants freed or even none.

In order to choose the best sequence, Mole gives you $ t $ segments $ [l_{i},r_{i}] $ and asks for each of them how many ants is he going to eat if those ants fight.

## 输入格式

The first line contains one integer $n$ ($1 ≤ n ≤ 10^5$), the size of the ant colony.

The second line contains $n$ integers $s_1, s_2, \ldots, s_n$ ($1 ≤ s_i ≤ 10^9$), the strengths of the ants.

The third line contains one integer $t$ ($1 ≤ t ≤ 10^5$), the number of test cases.

Each of the next $t$ lines contains two integers $l_i$ and $r_i$ ($1 ≤ l_i ≤ r_i ≤ n$), describing one query.

## 输出格式

Print to the standard output $t$ lines. The $i$-th line contains number of ants that Mole eats from the segment $[l_i, r_i]$.

## 说明/提示

In the first test battle points for each ant are $v = [4, 0, 2, 0, 2]$, so ant number $1$ is freed. Mole eats the ants $2, 3, 4, 5$.

In the second test case battle points are $v = [0, 2, 0, 2]$, so no ant is freed and all of them are eaten by Mole.

In the third test case battle points are $v = [2, 0, 2]$, so ants number $3$ and $5$ are freed. Mole eats only the ant $4$.

In the fourth test case battle points are $v = [0, 1]$, so ant number $5$ is freed. Mole eats the ant $4$.

## 样例 #1

### 输入

```
5
1 3 2 4 2
4
1 5
2 5
3 5
4 5

```

### 输出

```
4
4
1
1

```



---

---
title: "Mishka and Interesting sum"
layout: "post"
diff: 提高+/省选-
pid: CF703D
tag: ['线段树', '树状数组', '离散化']
---

# Mishka and Interesting sum

## 题目描述

Little Mishka enjoys programming. Since her birthday has just passed, her friends decided to present her with array of non-negative integers $ a_{1},a_{2},...,a_{n} $ of $ n $ elements!

Mishka loved the array and she instantly decided to determine its beauty value, but she is too little and can't process large arrays. Right because of that she invited you to visit her and asked you to process $ m $ queries.

Each query is processed in the following way:

1. Two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) are specified — bounds of query segment.
2. Integers, presented in array segment $ [l,r] $ (in sequence of integers $ a_{l},a_{l+1},...,a_{r} $ ) even number of times, are written down.
3. XOR-sum of written down integers is calculated, and this value is the answer for a query. Formally, if integers written down in point 2 are $ x_{1},x_{2},...,x_{k} $ , then Mishka wants to know the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7210428d91e1c7505cfe57a2df3abdc28a7ac76c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/4298d47c0191af3c0a3103f431751061bc7e2362.png) — operator of exclusive bitwise OR.

Since only the little bears know the definition of array beauty, all you are to do is to answer each of queries presented.

## 输入格式

The first line of the input contains single integer $ n $ ( $ 1<=n<=1000000 $ ) — the number of elements in the array.

The second line of the input contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — array elements.

The third line of the input contains single integer $ m $ ( $ 1<=m<=1000000 $ ) — the number of queries.

Each of the next $ m $ lines describes corresponding query by a pair of integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) — the bounds of query segment.

## 输出格式

Print $ m $ non-negative integers — the answers for the queries in the order they appear in the input.

## 说明/提示

In the second sample:

There is no integers in the segment of the first query, presented even number of times in the segment — the answer is $ 0 $ .

In the second query there is only integer $ 3 $ is presented even number of times — the answer is $ 3 $ .

In the third query only integer $ 1 $ is written down — the answer is $ 1 $ .

In the fourth query all array elements are considered. Only $ 1 $ and $ 2 $ are presented there even number of times. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/1f43581f72fc5ce3c0b862a8034cb76a29952125.png).

In the fifth query $ 1 $ and $ 3 $ are written down. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7a7518e2f6c019be104f1f3114e7d17043192b15.png).

## 样例 #1

### 输入

```
3
3 7 8
1
1 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
7
1 2 1 3 3 2 3
5
4 7
4 5
1 3
1 7
1 5

```

### 输出

```
0
3
1
3
2

```



---

---
title: "MEX Queries"
layout: "post"
diff: 提高+/省选-
pid: CF817F
tag: ['线段树', '离散化']
---

# MEX Queries

## 题目描述

You are given a set of integer numbers, initially it is empty. You should perform $ n $ queries.

There are three different types of queries:

- 1 $ l $ $ r $ — Add all missing numbers from the interval $ [l,r] $
- 2 $ l $ $ r $ — Remove all present numbers from the interval $ [l,r] $
- 3 $ l $ $ r $ — Invert the interval $ [l,r] $ — add all missing and remove all present numbers from the interval $ [l,r] $

After each query you should output MEX of the set — the smallest positive (MEX $ >=1 $ ) integer number which is not presented in the set.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=10^{5} $ ).

Next $ n $ lines contain three integer numbers $ t,l,r $ ( $ 1<=t<=3,1<=l<=r<=10^{18} $ ) — type of the query, left and right bounds.

## 输出格式

Print MEX of the set after each query.

## 说明/提示

Here are contents of the set after each query in the first example:

1. $ {3,4} $ — the interval $ [3,4] $ is added
2. $ {1,2,5,6} $ — numbers $ {3,4} $ from the interval $ [1,6] $ got deleted and all the others are added
3. $ {5,6} $ — numbers $ {1,2} $ got deleted

## 样例 #1

### 输入

```
3
1 3 4
3 1 6
2 1 3

```

### 输出

```
1
3
1

```

## 样例 #2

### 输入

```
4
1 1 3
3 5 6
2 4 4
3 1 6

```

### 输出

```
4
4
4
1

```



---

