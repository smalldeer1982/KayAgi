---
title: "Turtle and Multiplication"
layout: "post"
diff: 提高+/省选-
pid: CF1981D
tag: ['欧拉回路']
---

# Turtle and Multiplication

## 题目描述

Turtle just learned how to multiply two integers in his math class, and he was very excited.

Then Piggy gave him an integer $ n $ , and asked him to construct a sequence $ a_1, a_2, \ldots, a_n $ consisting of integers which satisfied the following conditions:

- For all $ 1 \le i \le n $ , $ 1 \le a_i \le 3 \cdot 10^5 $ .
- For all $ 1 \le i < j \le n - 1 $ , $ a_i \cdot a_{i + 1} \ne a_j \cdot a_{j + 1} $ .

Of all such sequences, Piggy asked Turtle to find the one with the minimum number of distinct elements.

Turtle definitely could not solve the problem, so please help him!

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ) — the length of the sequence $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output $ n $ integers $ a_1, a_2, \ldots, a_n $ — the elements of the sequence $ a $ .

If there are multiple answers, print any of them.

## 说明/提示

In the third test case, $ a = [3, 4, 2, 6] $ violates the second condition since $ a_1 \cdot a_2 = a_3 \cdot a_4 $ . $ a = [2, 3, 4, 4] $ satisfy the conditions but its number of distinct elements isn't minimum.

## 样例 #1

### 输入

```
3
2
3
4
```

### 输出

```
114514 114514
1 2 2
3 3 4 4
```



---

---
title: "Stardew Valley"
layout: "post"
diff: 提高+/省选-
pid: CF1994F
tag: ['欧拉回路']
---

# Stardew Valley

## 题目描述

Pelican Town represents $ n $ houses connected by $ m $ bidirectional roads. Some roads have NPCs standing on them. Farmer Buba needs to walk on each road with an NPC and talk to them.

Help the farmer find a route satisfying the following properties:

- The route starts at some house, follows the roads, and ends at the same house.
- The route does not follow any road more than once (in both directions together).
- The route follows each road with an NPC exactly once.

 Note that the route can follow roads without NPCs, and you do not need to minimize the length of the route.It is guaranteed that you can reach any house from any other by walking on the roads with NPCs only.

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 5 \cdot 10^5, 1 \leq m \leq 5 \cdot 10^5 $ ) — the number of houses and roads in Pelican Town respectively.

In each of the next $ m $ lines, three integers $ u $ , $ v $ , and $ c $ ( $ 1 \leq u, v \leq n, c = 0/1 $ ) are given — the ends of the road and whether an NPC is on this road. If $ c = 1 $ , then the road has an NPC. If $ c = 0 $ , then the road has no NPC.

The graph may contain multiple edges and loops, and if there are multiple edges with NPCs standing on them, the route must follow each of these roads.

It is guaranteed that you can reach any house from any other by walking on the roads with NPCs only.

It is guaranteed that the sum of $ n $ and $ m $ for all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, if there is no solution, then output "No" (without quotes).

Otherwise, output "Yes" (without quotes), and then output $ k $ — the number of roads in the route. In the next line, output $ k + 1 $ numbers — the houses of the route in the order of traversal. Note that the first house should match the last one, as the route is cyclic.

If there are multiple answers, you can print any of them.

You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

Note that in the third test case, there are multiple edges $ (5, 2) $ . You must walk on two of them.

## 样例 #1

### 输入

```
3
3 2
1 2 1
2 3 1
3 3
1 2 1
1 3 1
2 3 0
5 9
1 2 0
5 2 1
5 4 1
5 1 1
2 3 1
5 2 1
4 1 0
4 3 0
5 2 0
```

### 输出

```
NO
YES
3
1 2 3 1 
YES
7
1 2 5 4 3 2 5 1
```



---

---
title: "Trails and Glades"
layout: "post"
diff: 提高+/省选-
pid: CF209C
tag: ['连通块', '欧拉回路', '概率论']
---

# Trails and Glades

## 题目描述

Vasya went for a walk in the park. The park has $ n $ glades, numbered from 1 to $ n $ . There are $ m $ trails between the glades. The trails are numbered from 1 to $ m $ , where the $ i $ -th trail connects glades $ x_{i} $ and $ y_{i} $ . The numbers of the connected glades may be the same $ (x_{i}=y_{i}) $ , which means that a trail connects a glade to itself. Also, two glades may have several non-intersecting trails between them.

Vasya is on glade 1, he wants to walk on all trails of the park exactly once, so that he can eventually return to glade 1. Unfortunately, Vasya does not know whether this walk is possible or not. Help Vasya, determine whether the walk is possible or not. If such walk is impossible, find the minimum number of trails the authorities need to add to the park in order to make the described walk possible.

Vasya can shift from one trail to another one only on glades. He can move on the trails in both directions. If Vasya started going on the trail that connects glades $ a $ and $ b $ , from glade $ a $ , then he must finish this trail on glade $ b $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=10^{6}; 0<=m<=10^{6}) $ — the number of glades in the park and the number of trails in the park, respectively. Next $ m $ lines specify the trails. The $ i $ -th line specifies the $ i $ -th trail as two space-separated numbers, $ x_{i} $ , $ y_{i} $ $ (1<=x_{i},y_{i}<=n) $ — the numbers of the glades connected by this trail.

## 输出格式

Print the single integer — the answer to the problem. If Vasya's walk is possible without adding extra trails, print 0, otherwise print the minimum number of trails the authorities need to add to the park in order to make Vasya's walk possible.

## 说明/提示

In the first test case the described walk is possible without building extra trails. For example, let's first go on the first trail, then on the second one, and finally on the third one.

In the second test case the described walk is impossible without adding extra trails. To make the walk possible, it is enough to add one trail, for example, between glades number one and two.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
2 5
1 1
1 2
1 2
2 2
1 2

```

### 输出

```
1

```



---

---
title: "Melody"
layout: "post"
diff: 提高+/省选-
pid: CF2110E
tag: ['图论', '欧拉回路']
---

# Melody

## 题目描述

在 2077 年，统治世界的机器人意识到人类的音乐并不那么出色，于是它们开始创作自己的音乐。

为了创作音乐，机器人拥有一种特殊的乐器，能够产生 $n$ 种不同的声音。每种声音由其音量和音高来表征。一系列声音被称为音乐。如果任意两个连续的声音仅在音量或仅在音高上有所不同，则该音乐被认为是优美的。如果任意三个连续的声音在音量或音高上相同，则该音乐被认为是单调的。

你需要创作一段优美且不单调的音乐，其中包含乐器产生的每个声音恰好一次。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个数字 $n$（$1 \le n \le 2 \cdot 10^5$）——乐器能够产生的声音数量。

接下来是 $n$ 行，其中第 $i$ 行包含一对数字 $v_i, p_i$（$1 \le v_i, \space p_i \le 10^9$）——第 $i$ 个声音的音量和音高。保证在所有 $n$ 个声音中不存在重复，即对于任意 $i \neq j$，至少满足 $v_i \neq v_j$ 或 $p_i \neq p_j$ 中的一个条件。

所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果能够创作出这样的音乐，输出 "YES"，并在下一行输出 $n$ 个数字——构成优美且不单调音乐的声音索引顺序。否则，输出 "NO"。

你可以以任意大小写形式输出每个字母（例如，"yEs"、"yes"、"Yes" 和 "YES" 都会被接受为肯定答案）。

## 说明/提示

在第一个测试用例中，音乐 $(239,239)-(239,179)-(179,179)-(179,239)$ 是合适的，包含了所有声音，且所有连续的声音仅在音量或音高上有所不同。

在第二个测试用例中，可以证明无法用给定的声音创作出合适的音乐。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4
179 239
179 179
239 179
239 239
3
1 1
2 1
3 1
1
5 7
5
1 1
1 2
2 1
2 2
99 99
7
1 1
1 3
2 1
2 2
3 1
3 2
3 3
```

### 输出

```
YES
4 3 2 1 
NO
YES
1 
NO
YES
3 4 6 7 2 1 5
```



---

---
title: "Two Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF2113F
tag: ['图论', '图论建模', '欧拉回路']
---

# Two Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of length $ n $ . You can perform the following operation an unlimited number of times:

- Choose an integer $ i $ from $ 1 $ to $ n $ and swap $ a_i $ and $ b_i $ .

Let $ f(c) $ be the number of distinct numbers in array $ c $ . Find the maximum value of $ f(a) + f(b) $ . Also, output the arrays $ a $ and $ b $ after performing all operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2n $ ) — the elements of array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 2n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print a single integer in the first line — the maximum value of $ f(a) + f(b) $ .

In the second line, print $ n $ integers — the elements of array $ a $ after performing the operations.

In the third line, print $ n $ integers — the elements of array $ b $ after performing the operations.

## 说明/提示

In the first test case, after applying three operations with $ i=2 $ , $ i=4 $ , and $ i=5 $ , we obtain $ a = [1, 3, 4, 5, 2] $ and $ b = [1, 2, 3, 4, 4] $ . After that, $ f(a) + f(b) = 5 + 4 = 9 $ . It can be shown that it is not possible to achieve a greater answer.

In the second test case, after applying the operations: $f([2, 3, 4, 2, 1, 5, 6]) + f([1, 2, 3, 4, 5, 6, 5]) = 6 + 6 = 12 $.

## 样例 #1

### 输入

```
3
5
1 2 4 4 4
1 3 3 5 2
7
2 2 4 4 5 5 5
1 3 3 2 1 6 6
7
12 3 3 4 5 6 4
1 2 13 8 10 13 7
```

### 输出

```
9
1 3 4 5 2 
1 2 3 4 4 
12
2 3 4 2 1 5 6 
1 2 3 4 5 6 5 
14
12 3 13 8 10 6 4 
1 2 3 4 5 13 7
```



---

