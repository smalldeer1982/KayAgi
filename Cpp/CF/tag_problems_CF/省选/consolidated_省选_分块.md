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
title: "Iris and Adjacent Products"
layout: "post"
diff: 省选/NOI-
pid: CF2006D
tag: ['贪心', '分块']
---

# Iris and Adjacent Products

## 题目描述

Iris has just learned multiplication in her Maths lessons. However, since her brain is unable to withstand too complex calculations, she could not multiply two integers with the product greater than $ k $ together. Otherwise, her brain may explode!

Her teacher sets a difficult task every day as her daily summer holiday homework. Now she is given an array $ a $ consisting of $ n $ elements, and she needs to calculate the product of each two adjacent elements (that is, $ a_1 \cdot a_2 $ , $ a_2 \cdot a_3 $ , and so on). Iris wants her brain to work safely, and in order to do that, she would like to modify the array $ a $ in such a way that $ a_i \cdot a_{i + 1} \leq k $ holds for every $ 1 \leq i < n $ . There are two types of operations she can perform:

1. She can rearrange the elements of the array $ a $ in an arbitrary way.
2. She can select an arbitrary element of the array $ a $ and change its value to an arbitrary integer from $ 1 $ to $ k $ .

Iris wants to minimize the number of operations of type $ 2 $  that she uses.

However, that's completely not the end of the summer holiday! Summer holiday lasts for $ q $ days, and on the $ i $ -th day, Iris is asked to solve the Math homework for the subarray $ b_{l_i}, b_{l_i + 1}, \ldots, b_{r_i} $ . Help Iris and tell her the minimum number of type $ 2 $ operations she needs to perform for each day. Note that the operations are independent for each day, i.e. the array $ b $ is not changed.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5\cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ q $ and $ k $ ( $ 2 \leq n \leq 10^5 $ , $ 1 \leq q \leq 10^5 $ , $ 1 \leq k \leq 10^6 $ ) — the length of array $ b $ , the number of days, and the upper bound for the multiplication calculation.

The second line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq k $ ) — the elements of the array $ b $ .

Then $ q $ lines follow, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i < r_i \leq n $ ) — the boundaries of the subarray on the $ i $ -th day.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , and the sum of $ q $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test, output a single line containing $ q $ integers — the minimum number of operations of type $ 2 $ needed for each day.

## 说明/提示

In the first test case, as Iris can always multiply $ 1 $ and $ 1 $ together, no operations are needed, so the answer is $ 0 $ .

In the second test case, the first day's homework is $ [1, 10, 9] $ . Iris can rearrange its elements to get $ [9, 1, 10] $ , so no operations of type $ 2 $ are needed. The second day's homework is $ [10, 9] $ , and she can change one element to get the array $ [1, 9] $ , so one operation of type $ 2 $ is needed.

## 样例 #1

### 输入

```
5
3 1 1
1 1 1
1 3
3 2 10
1 10 9
1 3
2 3
5 4 2
2 2 2 2 2
1 2
2 4
2 5
1 5
6 5 10
3 2 5 10 10 1
1 4
3 6
1 6
2 5
5 6
10 10 10
10 9 8 7 6 5 4 3 2 1
1 10
1 9
1 8
1 7
2 10
3 10
4 10
5 10
3 9
6 8
```

### 输出

```
0 
0 1 
1 1 2 2 
1 1 1 1 0 
3 3 4 3 2 2 1 1 2 1
```



---

---
title: "Variable Damage"
layout: "post"
diff: 省选/NOI-
pid: CF2025G
tag: ['贪心', '分块']
---

# Variable Damage

## 题目描述

Monocarp is gathering an army to fight a dragon in a videogame.

The army consists of two parts: the heroes and the defensive artifacts. Each hero has one parameter — his health. Each defensive artifact also has one parameter — its durability.

Before the battle begins, Monocarp distributes artifacts to the heroes so that each hero receives at most one artifact.

The battle consists of rounds that proceed as follows:

- first, the dragon deals damage equal to $ \frac{1}{a + b} $ (a real number without rounding) to each hero, where $ a $ is the number of heroes alive and $ b $ is the number of active artifacts;
- after that, all heroes with health $ 0 $ or less die;
- finally, some artifacts are deactivated. An artifact with durability $ x $ is deactivated when one of the following occurs: the hero holding the artifact either dies or receives $ x $ total damage (from the start of the battle). If an artifact is not held by any hero, it is inactive from the beginning of the battle.

The battle ends when there are no heroes left alive.

Initially, the army is empty. There are $ q $ queries: add a hero with health $ x $ or an artifact with durability $ y $ to the army. After each query, determine the maximum number of rounds that Monocarp can survive if he distributes the artifacts optimally.

## 输入格式

The first line contains one integer $ q $ ( $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of queries.

In the $ i $ -th of the following $ q $ lines, there are two integers $ t_i $ and $ v_i $ ( $ t_i \in \{1, 2\} $ ; $ 1 \le v_i \le 10^9 $ ) — the type of the query and the value of the query parameter. If the type is $ 1 $ , a hero with health $ v_i $ is added. If the type is $ 2 $ , an artifact with durability $ v_i $ is added.

## 输出格式

Print $ q $ integers. After each query, output the maximum number of rounds that Monocarp can survive if he distributes the artifacts optimally.

## 说明/提示

Let's consider the first example.

- An artifact with durability $ 5 $ is added. Since there are no heroes yet, the battle ends immediately.
- A hero with health $ 4 $ is added. Monocarp can give him an artifact with durability $ 5 $ . First, there are rounds in which the hero takes $ \frac{1}{1 + 1} = \frac{1}{2} $ damage. After $ 8 $ such rounds, a total of $ 4 $ damage will have been dealt, and the hero will die, while the artifact will deactivate. There are no more heroes alive, so the battle ends after $ 8 $ rounds.
- A hero with health $ 10 $ is added. Now let the artifact with durability $ 5 $ be with this hero. Then, in the first $ 12 $ rounds, the heroes will take $ 12 \cdot \frac{1}{2 + 1} = 4 $ damage, and the first hero will die. The second hero has $ 6 $ health left, and the artifact has $ 1 $ durability. Now the damage is $ \frac{1}{2} $ , so after another $ 2 $ rounds, the artifact will deactivate. The second hero has $ 5 $ health left. After another $ 5 $ rounds, the second hero will die. Therefore, the answer is $ 12 + 2 + 5 = 19 $ .

## 样例 #1

### 输入

```
3
2 5
1 4
1 10
```

### 输出

```
0
8
19
```

## 样例 #2

### 输入

```
10
1 9
1 6
2 4
1 8
1 3
2 10
1 3
1 6
1 10
2 6
```

### 输出

```
9
15
19
27
30
39
42
48
59
65
```



---

---
title: "Problem with Queries"
layout: "post"
diff: 省选/NOI-
pid: CF2043G
tag: ['分块']
---

# Problem with Queries

## 题目描述

给定一个整数数组 $a$，长度为 $n$。你的任务是处理 $q$ 个查询，这些查询分为两种类型：

- 类型 1：`1 p x` — 将数组中索引为 $p$ 的元素值更新为 $x$；
- 类型 2：`2 l r` — 计算数组 $a$ 中满足条件的索引对 $(i, j)$ 的数量，其中 $l \le i < j \le r$ 且 $a_i \ne a_j$。

请注意，这些查询是编码过的；每个后续查询必须在解出前一个类型 2 查询的答案后才能解码。

## 输入格式

第一行输入一个整数 $n$，表示数组的长度（$1 \le n \le 10^5$）。

第二行输入 $n$ 个整数，分别为 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$）。

第三行输入一个整数 $q$，代表要处理的查询数量（$1 \le q \le 3 \cdot 10^5$）。

接下来的 $q$ 行中，每行描述了一个查询，格式如下：

- 类型 1：以 `1 p' x'` 的形式给出（$0 \le p', x' \le n-1$）；
- 类型 2：以 `2 l' r'` 的形式给出（$0 \le l', r' \le n-1$）。

查询的解码规则如下：设 $\mathit{last}$ 为最近一次处理的类型 2 查询的答案（最初，$\mathit{last} = 0$）。

- 如果是类型 1 查询，则 $p = ((p' + \mathit{last}) \bmod n) + 1$，$x = ((x' + \mathit{last}) \bmod n) + 1$。
- 如果是类型 2 查询，则 $l = ((l' + \mathit{last}) \bmod n) + 1$，$r = ((r' + \mathit{last}) \bmod n) + 1$。如若 $l > r$，则将两者交换。

请务必在回答每一个类型 2 查询后更新 $\mathit{last}$ 的值。

输入保证至少有一个类型 2 的查询。

## 输出格式

对于每一个类型 2 的查询，输出一个整数，即满足条件的索引对 $(i, j)$ 的数量，其中 $l \le i < j \le r$ 且 $a_i \ne a_j$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1 2 3
5
2 0 2
1 0 2
2 0 2
1 2 0
2 1 0
```

### 输出

```
3 2 0
```

## 样例 #2

### 输入

```
7
1 3 4 4 7 1 3
3
2 1 6
2 1 0
2 5 6
```

### 输出

```
13 18 0
```



---

---
title: "Tropical Season"
layout: "post"
diff: 省选/NOI-
pid: CF2066E
tag: ['倍增', '分块']
---

# Tropical Season

## 题目描述

您有 $n$ 个容量无限的桶。第 $i$ 个桶初始装有 $a_i$ 千克水。在此问题中，我们假设所有桶自身重量相同。

已知恰好有一个桶的表面含有少量热带毒药，总重量为 $0.179$ 千克。但您不知道具体是哪个桶含有毒药。您的任务是确定这个有毒的桶。

所有桶都放置在秤上。然而秤不会显示每个桶的确切重量，而是为每对桶显示它们的重量比较结果。因此，对于任意两个桶，您可以判断它们的重量是否相等，若不相等则可知哪个桶更重。毒药和水的重量均计入桶的总重量。

秤始终处于开启状态，其信息可无限次使用。

您还可以进行倒水操作：可以将任意数量的水从任意一个桶倒入另一个桶（两者可为不同桶）。

但倒水时，您必须物理接触被倒出的桶。如果该桶恰好是含毒桶，您将死亡。必须避免这种情况发生。

但您可以将水倒入含毒桶而无需触碰它。

换言之，您可以选择参数 $i, j, x$（$i \neq j$，$1 \leq i, j \leq n$，$0 < x \leq a_i$，且编号 $i$ 的桶不含毒）并执行操作 $a_i := a_i - x$，$a_j := a_j + x$。其中 $x$ 不必是整数。

在利用倒水操作和秤的信息时，能否保证确定含毒桶的同时存活？已知毒药必定存在于恰好一个桶中。

此外，您需要处理 $q$ 次查询。每次查询将移除一个现有桶，或添加一个装有指定水量新桶。每次查询后，您需要回答在恰好存在一个含毒桶的条件下，能否保证确定该桶。

## 输入格式

第一行包含两个整数 $n$ 和 $q$（$1 \le n, q \le 2 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^6$）——现有桶中的水量。

接下来 $q$ 行每行包含一个查询，格式为 + x 或 - x，分别表示添加和移除一个装有 $x$ 千克水的桶。保证执行 - x 查询时存在水量为 $x$ 的桶，且所有查询后至少保留一个桶。所有查询中 $1 \leq x \leq 10^6$。

## 输出格式

输出 $q+1$ 行，依次为初始状态及每次查询后的答案。若可确定含毒桶则输出 "Yes"，否则输出 "No"。输出不区分大小写（如 "yEs"、"YES" 等均视为肯定回答）。

## 说明/提示

第一个测试案例中，初始桶的水量为 $[2, 2, 4, 11]$。可先比较第一和第二个桶的重量：若不等则可断定较重桶含毒；若相等则二者均不含毒。接着可将第一桶所有水倒入第二桶，此时第二和第三桶均有 $4$ 千克水。再次比较二者重量：若不等则较重桶含毒；否则二者均不含毒。唯一可能含毒的桶变为第四个。通过此策略可安全确定含毒桶。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4 7
2 2 4 11
- 2
+ 4
+ 30
+ 40
- 4
+ 2
+ 2
```

### 输出

```
Yes
No
Yes
No
Yes
No
No
Yes
```

## 样例 #2

### 输入

```
6 7
5000 1000 400 400 100 99
+ 1
- 5000
- 1
- 400
- 400
- 100
- 99
```

### 输出

```
No
Yes
Yes
Yes
No
No
No
Yes
```



---

---
title: "String Set Queries"
layout: "post"
diff: 省选/NOI-
pid: CF710F
tag: ['分治', '哈希 hashing', '分块', '字典树 Trie', 'AC 自动机', 'KMP 算法']
---

# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of queries.

Each of the next $ m $ lines contains integer $ t $ ( $ 1<=t<=3 $ ) and nonempty string $ s $ — the kind of the query and the string to process. All strings consist of only lowercase English letters.

The sum of lengths of all strings in the input will not exceed $ 3·10^{5} $ .

## 输出格式

For each query of the third kind print the only integer $ c $ — the desired number of occurrences in the string $ s $ .

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc

```

### 输出

```
2
2

```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd

```

### 输出

```
3
2
1
0

```



---

---
title: "Machine Learning"
layout: "post"
diff: 省选/NOI-
pid: CF940F
tag: ['莫队', '枚举', '分块']
---

# Machine Learning

## 题目描述

You come home and fell some unpleasant smell. Where is it coming from?

You are given an array $ a $ . You have to answer the following queries:

1. You are given two integers $ l $ and $ r $ . Let $ c_{i} $ be the number of occurrences of $ i $ in $ a_{l:r} $ , where $ a_{l:r} $ is the subarray of $ a $ from $ l $ -th element to $ r $ -th inclusive. Find the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $
2. You are given two integers $ p $ to $ x $ . Change $ a_{p} $ to $ x $ .

The Mex of a multiset of numbers is the smallest non-negative integer not in the set.

Note that in this problem all elements of $ a $ are positive, which means that $ c_{0} $ = 0 and $ 0 $ is never the answer for the query of the second type.

## 输入格式

The first line of input contains two integers $ n $ and $ q $ ( $ 1<=n,q<=100000 $ ) — the length of the array and the number of queries respectively.

The second line of input contains $ n $ integers — $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Each of the next $ q $ lines describes a single query.

The first type of query is described by three integers $ t_{i}=1 $ , $ l_{i} $ , $ r_{i} $ , where $ 1<=l_{i}<=r_{i}<=n $ — the bounds of the subarray.

The second type of query is described by three integers $ t_{i}=2 $ , $ p_{i} $ , $ x_{i} $ , where $ 1<=p_{i}<=n $ is the index of the element, which must be changed and $ 1<=x_{i}<=10^{9} $ is the new value.

## 输出格式

For each query of the first type output a single integer — the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $ .

## 说明/提示

The subarray of the first query consists of the single element — $ 1 $ .

The subarray of the second query consists of four $ 2 $ s, one $ 3 $ and two $ 1 $ s.

The subarray of the fourth query consists of three $ 1 $ s, three $ 2 $ s and one $ 3 $ .

## 样例 #1

### 输入

```
10 4
1 2 3 1 1 2 2 2 9 9
1 1 1
1 2 8
2 7 1
1 2 8

```

### 输出

```
2
3
2

```



---

