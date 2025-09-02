---
title: "The number of positions"
layout: "post"
diff: 入门
pid: CF124A
tag: ['模拟', '数学', '枚举']
---

# The number of positions

## 题目描述

Translated by @隐鬼在侧

## 样例 #1

### 输入

```
3 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2 3

```

### 输出

```
3

```



---

---
title: "Cookies"
layout: "post"
diff: 入门
pid: CF129A
tag: ['字符串', '数学', '概率论']
---

# Cookies

## 输出格式

感谢@面瘫者 提供的翻译

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10
1 2 2 3 4 4 4 2 2 2

```

### 输出

```
8

```

## 样例 #3

### 输入

```
11
2 2 2 2 2 2 2 2 2 2 99

```

### 输出

```
1

```



---

---
title: "Elections"
layout: "post"
diff: 入门
pid: CF1593A
tag: ['数学']
---

# Elections

## 题目描述

三名候选人参加竞选 。第一名候选人得到了 $a$ 票，第二名候选人得到了 $b$ 票，第三名候选人得到了 $c$ 票 。对于每一个候选人，解决以下问题 ：

至少给该候选人增加多少票，使得该候选人的票数严格大于其它候选人？

注意，每个问题是独立存在的 。

## 输入格式

第一行包含一个整数 $t$ $(1\leq t\leq 10^4)$，表示数据组数 。

每组数据包含三个整数 $a$，$b$，$c$，$(0\leq a,b,c\leq 10^9)$ 分别表示三个候选人的票数 。

## 输出格式

每组数据输出三个整数，用空格隔开，分别表示三个问题的答案 。

## 样例 #1

### 输入

```
5
0 0 0
10 75 15
13 13 17
1000 0 0
0 1000000000 0
```

### 输出

```
1 1 1
66 0 61
5 5 0
0 1001 1001
1000000001 0 1000000001
```



---

---
title: "A.M. Deviation"
layout: "post"
diff: 入门
pid: CF1605A
tag: ['数学']
---

# A.M. Deviation

## 题目描述

给出 3 个数 $a_1,a_2,a_3$，现有一种操作可以在 $a_1,a_2,a_3$ 中任选两个数，使其中一个 +1，另一个 -1。操作次数不限。

要求最小化 $|a_1+a_3-2\times a_2|$。

## 输入格式

第一行输入一个整数 $t$ 表示数据组数。

每组数据读入一行 3 个整数 $a_1,a_2,a_3$。

## 输出格式

对于每组数据输出一行一个整数表示最小的 $|a_1+a_3-2\times a_2|$。

## 说明/提示

$1\le t\le 5000,1\le a_1,a_2,a_3\le 10^8$。

## 样例 #1

### 输入

```
3
3 4 5
2 2 6
1 6 5
```

### 输出

```
0
1
0
```



---

---
title: "Distance"
layout: "post"
diff: 入门
pid: CF1612A
tag: ['数学']
---

# Distance

## 题目描述

Let's denote the Manhattan distance between two points $ p_1 $ (with coordinates $ (x_1, y_1) $ ) and $ p_2 $ (with coordinates $ (x_2, y_2) $ ) as $ d(p_1, p_2) = |x_1 - x_2| + |y_1 - y_2| $ . For example, the distance between two points with coordinates $ (1, 3) $ and $ (4, 2) $ is $ |1 - 4| + |3 - 2| = 4 $ .

You are given two points, $ A $ and $ B $ . The point $ A $ has coordinates $ (0, 0) $ , the point $ B $ has coordinates $ (x, y) $ .

Your goal is to find a point $ C $ such that:

- both coordinates of $ C $ are non-negative integers;
- $ d(A, C) = \dfrac{d(A, B)}{2} $ (without any rounding);
- $ d(B, C) = \dfrac{d(A, B)}{2} $ (without any rounding).

Find any point $ C $ that meets these constraints, or report that no such point exists.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 3000 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ x $ and $ y $ ( $ 0 \le x, y \le 50 $ ) — the coordinates of the point $ B $ .

## 输出格式

For each test case, print the answer on a separate line as follows:

- if it is impossible to find a point $ C $ meeting the constraints, print "-1 -1" (without quotes);
- otherwise, print two non-negative integers not exceeding $ 10^6 $ — the coordinates of point $ C $ meeting the constraints. If there are multiple answers, print any of them. It can be shown that if any such point exists, it's possible to find a point with coordinates not exceeding $ 10^6 $ that meets the constraints.

## 说明/提示

Explanations for some of the test cases from the example:

- In the first test case, the point $ B $ has coordinates $ (49, 3) $ . If the point $ C $ has coordinates $ (23, 3) $ , then the distance from $ A $ to $ B $ is $ |49 - 0| + |3 - 0| = 52 $ , the distance from $ A $ to $ C $ is $ |23 - 0| + |3 - 0| = 26 $ , and the distance from $ B $ to $ C $ is $ |23 - 49| + |3 - 3| = 26 $ .
- In the second test case, the point $ B $ has coordinates $ (2, 50) $ . If the point $ C $ has coordinates $ (1, 25) $ , then the distance from $ A $ to $ B $ is $ |2 - 0| + |50 - 0| = 52 $ , the distance from $ A $ to $ C $ is $ |1 - 0| + |25 - 0| = 26 $ , and the distance from $ B $ to $ C $ is $ |1 - 2| + |25 - 50| = 26 $ .
- In the third and the fourth test cases, it can be shown that no point with integer coordinates meets the constraints.
- In the fifth test case, the point $ B $ has coordinates $ (42, 0) $ . If the point $ C $ has coordinates $ (21, 0) $ , then the distance from $ A $ to $ B $ is $ |42 - 0| + |0 - 0| = 42 $ , the distance from $ A $ to $ C $ is $ |21 - 0| + |0 - 0| = 21 $ , and the distance from $ B $ to $ C $ is $ |21 - 42| + |0 - 0| = 21 $ .

## 样例 #1

### 输入

```
10
49 3
2 50
13 0
0 41
42 0
0 36
13 37
42 16
42 13
0 0
```

### 输出

```
23 3
1 25
-1 -1
-1 -1
21 0
0 18
13 12
25 4
-1 -1
0 0
```



---

---
title: "Equal Candies"
layout: "post"
diff: 入门
pid: CF1676B
tag: ['模拟', '数学']
---

# Equal Candies

## 题目描述

There are $ n $ boxes with different quantities of candies in each of them. The $ i $ -th box has $ a_i $ candies inside.

You also have $ n $ friends that you want to give the candies to, so you decided to give each friend a box of candies. But, you don't want any friends to get upset so you decided to eat some (possibly none) candies from each box so that all boxes have the same quantity of candies in them. Note that you may eat a different number of candies from different boxes and you cannot add candies to any of the boxes.

What's the minimum total number of candies you have to eat to satisfy the requirements?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 50 $ ) — the number of boxes you have.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^7 $ ) — the quantity of candies in each box.

## 输出格式

For each test case, print a single integer denoting the minimum number of candies you have to eat to satisfy the requirements.

## 说明/提示

For the first test case, you can eat $ 1 $ candy from the second box, $ 2 $ candies from the third box, $ 3 $ candies from the fourth box and $ 4 $ candies from the fifth box. Now the boxes have $ [1, 1, 1, 1, 1] $ candies in them and you ate $ 0 + 1 + 2 + 3 + 4 = 10 $ candies in total so the answer is $ 10 $ .

For the second test case, the best answer is obtained by making all boxes contain $ 5 $ candies in them, thus eating $ 995 + 995 + 0 + 995 + 995 + 995 = 4975 $ candies in total.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
6
1000 1000 5 1000 1000 1000
10
1 2 3 5 1 2 7 9 13 5
3
8 8 8
1
10000000
```

### 输出

```
10
4975
38
0
0
```



---

---
title: "2-3 Moves"
layout: "post"
diff: 入门
pid: CF1716A
tag: ['数学']
---

# 2-3 Moves

## 题目描述

你的任务是求出从 $0$ 点到 $n$ 点的最短时间。

## 输入格式

接下来的 $t$ 行每行输入一个 $n$ 表示需要到达的点 $n$。

## 输出格式

$1 \leq t \leq 10^4$，$1 \leq n \leq 10^9$。

## 样例 #1

### 输入

```
4
1
3
4
12
```

### 输出

```
2
1
2
4
```



---

---
title: "Accumulation of Dominoes"
layout: "post"
diff: 入门
pid: CF1725A
tag: ['数学']
---

# Accumulation of Dominoes

## 题目描述

给定一个 $N$ 行 $M$ 列的矩阵，数字从 $1$ 开始，从左到右，从上到下依次在矩阵内排列。

定义 domino 为矩阵内相邻的两个差为 $1$ 的数，求一共有多少个不同的 domino。

两个 domino 不同当且仅当第一个 domino 其中的至少一个数在第二个 domino 没有出现。

## 输入格式

一行两个整数 $N$ 和 $M$ ( $ 1 \leq N, M \leq 10^9 $ ) ，表示矩阵共有 $N$ 行 $M$ 列。

## 输出格式

一个整数，表示一共有多少个不同的 domino。

## 样例 #1

### 输入

```
3 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
1
```



---

---
title: "Joey Takes Money"
layout: "post"
diff: 入门
pid: CF1731A
tag: ['数学', '贪心']
---

# Joey Takes Money

## 题目描述

- **题目翻译如下**

Joey 很穷，因此他的朋友 Chandler 想要借给他一些钱。但是 Joey 的自尊心很强，为了不让他的自尊心受挫又能给他钱，Chandler 打算和他玩一个游戏。   

在这个游戏中，Chandler 会给 Joey 一个数组 $a_1,a_2,\dots,a_n(n\ge 2,a_i \in \mathbb{Z^+})$。Joey 可以对这个数组进行如下的操作任意次：

1. 选择一对 $ i $ 和 $ j $ ( $ 1 \le i < j \le n) $ .
2. 选择两个整数 $ x $ 和 $ y $ ( $ x, y \ge 1 $ ) 使得 $ x \cdot y = a_i \cdot a_j $ .
3. 将 $a_i, a_j$ 分别替换为 $x, y$.

最后， Joey 将得到的钱就是 $a$ 数组中所有值的和。即 Joey 所得的钱 $= \sum^{n}_{i=1}a_{i}$ .

你需要求出一个整数 $ans$，即 Joey 最多可以得到的钱，并输出 $2022 \cdot ans$ 。为什么要乘以 $2022$ 呢？因为我们再也见不到它了！（悲）

输入数据保证 $a$ 数组内所有数的乘积不超过 $10^{12}$，即 $\prod^{n}_{i=1}a_{i} \le 10^{12}$.

## 输入格式

输入包含多组测试数据。  
- 第一行，一个整数 $T$，代表测试数据组数。  
- 对于每一组测试数据，第一行为一个整数 $n(2 \leq n \leq 50)$，表示数组 $a$ 的长度。第二行为 $n$ 个整数 $a_1,a_2,\dots,a_n( 1 \leq a_i \leq 10^6 )$，表示 $a$ 数组。保证 $a$ 数组内所有数的乘积不超过 $10^{12}$，即 $\prod^{n}_{i=1}a_{i} \le 10^{12}$.

## 输出格式

共一行，一个整数，表示 Joey 最多可以得到的钱乘以 2022 后的值。

## 说明/提示

在测试样例的第一组测试数据中，Joey 可以这么做：

- 他选择 $ i = 1 , j = 2 $ (可得 $ a[i] \cdot a[j] = 6 $ ), 使 $ x = 6, y = 1 $ ，然后改变原数组使 $ a[i] = x = 6 , a[j] = y = 1 $ . 即原数组发生如下变化：
$$[2, 3, 2] \xrightarrow[x = 6,\; y = 1]{i = 1,\; j = 2} [6, 1, 2] $$        
- 他选择 $i = 1 , j = 3 $  (可得  $ a[i] \cdot a[j] = 12 $ ), 使 $ x = 12 , y = 1 $  然后改变原数组使 $ a[i] = x = 12 , a[j] = y = 1 $ . 即原数组发生如下变化： 
$$ [6, 1, 2] \xrightarrow[x = 12,; y = 1]{i = 1,\; j = 3} [12, 1, 1] $$

综上所述， Joey 可以得到的最多的钱即为 $12+1+1=14$ 元，所以输出应为 $14\times 2022 = 28308$.

## 样例 #1

### 输入

```
3
3
2 3 2
2
1 3
3
1000000 1000000 1
```

### 输出

```
28308
8088
2022000000004044
```



---

---
title: "Two Groups"
layout: "post"
diff: 入门
pid: CF1747A
tag: ['数学', '贪心']
---

# Two Groups

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You want to distribute these $ n $ integers into two groups $ s_1 $ and $ s_2 $ (groups can be empty) so that the following conditions are satisfied:

- For each $ i $ $ (1 \leq i \leq n) $ , $ a_i $ goes into exactly one group.
- The value $ |sum(s_1)| - |sum(s_2)| $ is the maximum possible among all such ways to distribute the integers.Here $ sum(s_1) $ denotes the sum of the numbers in the group $ s_1 $ , and $ sum(s_2) $ denotes the sum of the numbers in the group $ s_2 $ .

Determine the maximum possible value of $ |sum(s_1)| - |sum(s_2)| $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 2 \cdot 10^4) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \leq n \leq 10^5) $ — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2 \ldots a_n $ $ (-10^9 \leq a_i \leq 10^9) $ — elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible value of $ |sum(s_1)| - |sum(s_2)| $ .

## 说明/提示

In the first testcase, we can distribute as $ s_1 = \{10\} $ , $ s_2 = \{-10\} $ . Then the value will be $ |10| - |-10| = 0 $ .

In the second testcase, we can distribute as $ s_1 = \{0, 11, -1\} $ , $ s_2 = \{-2\} $ . Then the value will be $ |0 + 11 - 1| - |-2| = 10 - 2 = 8 $ .

In the third testcase, we can distribute as $ s_1 = \{2, 3, 2\} $ , $ s_2 = \{\} $ . Then the value will be $ |2 + 3 + 2| - |0| = 7 $ .

In the fourth testcase, we can distribute as $ s_1 = \{-9, -4, 0\} $ , $ s_2 = \{2, 0\} $ . Then the value will be $ |-9 - 4 + 0| - |2 + 0| = 13 - 2 = 11 $ .

## 样例 #1

### 输入

```
4
2
10 -10
4
-2 -1 11 0
3
2 3 2
5
-9 2 0 0 -4
```

### 输出

```
0
8
7
11
```



---

---
title: "Cut the Triangle"
layout: "post"
diff: 入门
pid: CF1767A
tag: ['数学']
---

# Cut the Triangle

## 题目描述

You are given a non-degenerate triangle (a non-degenerate triangle is a triangle with positive area). The vertices of the triangle have coordinates $ (x_1, y_1) $ , $ (x_2, y_2) $ and $ (x_3, y_3) $ .

You want to draw a straight line to cut the triangle into two non-degenerate triangles. Furthermore, the line you draw should be either horizontal or vertical.

Can you draw the line to meet all the constraints?

Here are some suitable ways to draw the line:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1767A/eae3d7282c3158bdbed223cdc7230dcfb540b234.png)However, these ways to draw the line are not suitable (the first line cuts the triangle into a triangle and a quadrangle; the second line doesn't cut the triangle at all; the third line is neither horizontal nor vertical):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1767A/bffea37399e8b2b37904bb00d4f9d390b630614c.png)

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of four lines. The first of them is empty. The $ i $ -th of the next three lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le 10^8 $ ) — the coordinates of the $ i $ -th vertex of the triangle.

Additional constraint on the input: in each test case, the triangle formed by three vertices has positive area (i. e. it is non-degenerate).

## 输出格式

For each test case, print YES if it is possible to cut the triangle according to the statement, or NO otherwise. You may print each letter in any case (YES, yes, Yes will all be recognized as positive answer, NO, no and nO will all be recognized as negative answer).

## 样例 #1

### 输入

```
4


4 7
6 8
3 5


4 5
4 7
6 8


5 8
1 8
2 5


3 6
6 6
6 3
```

### 输出

```
YES
YES
YES
NO
```



---

---
title: "Yet Another Promotion"
layout: "post"
diff: 入门
pid: CF1793A
tag: ['数学', '贪心']
---

# Yet Another Promotion

## 题目描述

The famous store "Second Food" sells groceries only two days a month. And the prices in each of days differ. You wanted to buy $ n $ kilos of potatoes for a month. You know that on the first day of the month $ 1 $ kilo of potatoes costs $ a $ coins, and on the second day $ b $ coins. In "Second Food" you can buy any integer kilograms of potatoes.

Fortunately, "Second Food" has announced a promotion for potatoes, which is valid only on the first day of the month — for each $ m $ kilos of potatoes you buy, you get $ 1 $ kilo as a gift! In other words, you can get $ m + 1 $ kilograms by paying for $ m $ kilograms.

Find the minimum number of coins that you have to spend to buy at least $ n $ kilos of potatoes.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10\,000 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ a $ and $ b $ $ (1 \leq a, b \leq 10^9) $ — the prices of $ 1 $ kilo of potatoes on the first and second days, respectively.

The second line contains two integers $ n $ and $ m $ $ (1 \leq n, m \leq 10^9) $ — the required amount of potatoes to buy and the amount of potatoes to use the promotion.

## 输出格式

For each test case print one integer — the minimum number of coins that you have to pay to buy at least $ n $ kilos of potatoes.

## 说明/提示

In the first test case, on the first day you buy $ 1 $ kilo and get $ 1 $ more for a promotion. On the second day, you can buy $ 1 $ kilo of potatoes. Thus, you will spend $ 5+4=9 $ coins in total.

In the second test case, on the first day you buy $ 2 $ kilo and get another $ 1 $ more for a promotion. This way you will spend $ 2 \cdot 5 = 10 $ coins.

## 样例 #1

### 输入

```
5
5 4
3 1
5 4
3 2
3 4
3 5
20 15
10 2
1000000000 900000000
1000000000 8
```

### 输出

```
9
10
9
135
888888888900000000
```



---

---
title: "2023"
layout: "post"
diff: 入门
pid: CF1916A
tag: ['数学']
---

# 2023

## 题目描述

求一个元素乘积为 $2023$ 的数组 $a$，其中的 $k$ 个元素被移除后得到数组 $b$。现在告诉你 $b$，问是否能找到一个满足以上条件的数组 $a$。

## 输入格式

多组测试，第一行一个整数 $t(1\le t\le 100)$——测试数据的数量，接下来描述一组数据的输入：
- 第一行 $2$ 个整数 $n$，$k$，（$1\le n,k\le 5$），分别表示 $b$ 的长度和 $a$ 中被移除元素的个数；
- 接下来一行 $n$ 个整数，表示 $b$。

## 输出格式

对于每组数据，如果不存在一个满足要求的 $a$，输出 `NO`，否则输出 `YES`，并换行输出 $a$ 中被删除的 $k$ 个元素，大小写不敏感。

## 样例 #1

### 输入

```
7
2 2
5 2
3 1
7 17 7
4 2
1 289 1 1
3 1
7 17 17
1 1
289
1 1
2023
1 3
1
```

### 输出

```
NO
NO
YES
7 1
YES
1
YES
7
YES
1
YES
7 17 17
```



---

---
title: "Least Product"
layout: "post"
diff: 入门
pid: CF1917A
tag: ['数学']
---

# Least Product

## 题目描述

You are given an array of integers $ a_1, a_2, \dots, a_n $ . You can perform the following operation any number of times (possibly zero):

- Choose any element $ a_i $ from the array and change its value to any integer between $ 0 $ and $ a_i $ (inclusive). More formally, if $ a_i < 0 $ , replace $ a_i $ with any integer in $ [a_i, 0] $ , otherwise replace $ a_i $ with any integer in $ [0, a_i] $ .

Let $ r $ be the minimum possible product of all the $ a_i $ after performing the operation any number of times.

Find the minimum number of operations required to make the product equal to $ r $ . Also, print one such shortest sequence of operations. If there are multiple answers, you can print any of them.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 500 $ ) - the number of test cases. This is followed by their description.

The first line of each test case contains the a single integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \leq a_i \leq 10^9 $ ).

## 输出格式

For each test case:

- The first line must contain the minimum number of operations $ k $ ( $ 0 \leq k \leq n $ ).
- The $ j $ -th of the next $ k $ lines must contain two integers $ i $ and $ x $ , which represent the $ j $ -th operation. That operation consists in replacing $ a_i $ with $ x $ .

## 说明/提示

In the first test case, we can change the value of the first integer into $ 0 $ and the product will become $ 0 $ , which is the minimum possible.

In the second test case, initially, the product of integers is equal to $ 2 \cdot 8 \cdot (-1) \cdot 3 = -48 $ which is the minimum possible, so we should do nothing in this case.

## 样例 #1

### 输入

```
4
1
155
4
2 8 -1 3
4
-1 0 -2 -5
4
-15 -75 -25 -30
```

### 输出

```
1
1 0
0
0
1
3 0
```



---

---
title: "Little Nikita"
layout: "post"
diff: 入门
pid: CF1977A
tag: ['数学']
---

# Little Nikita

## 题目描述

The little boy Nikita was given some cubes as a present. He decided to build a tower out of them.

Initially, the tower doesn't have any cubes. In one move, Nikita either puts exactly $ 1 $ cube on top of the tower or removes exactly $ 1 $ cube from the top of the tower. Is it possible that after $ n $ moves, the resulting tower has exactly $ m $ cubes?

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 100 $ ).

## 输出格式

For each test case, output "Yes" (without quotes) if Nikita can obtain a tower with $ m $ cubes, and "No" (without quotes) otherwise.

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the first test case, Nikita can put $ 1 $ cube on top of the tower $ 3 $ times in a row, so the answer is "Yes".

In the second test case, Nikita can only end up with either a tower with no blocks or a tower with $ 2 $ blocks, so the answer is "No".

## 样例 #1

### 输入

```
3
3 3
2 4
5 3
```

### 输出

```
Yes
No
Yes
```



---

---
title: "Maximum Multiple Sum"
layout: "post"
diff: 入门
pid: CF1985B
tag: ['模拟', '数学']
---

# Maximum Multiple Sum

## 题目描述

给定一个整数$ n $，找到一个整数$ x $，这样:

- $ 2 \leq x \leq n $。
- 将 $ x $ 中小于等于 $ n $ 的倍数之和取最大值。形式上是 $ x + 2x + 3x + \dots + kx $，其中 $ kx \leq n $ 比 $ x $ 的所有可能值都大。

## 输入格式

第一行包含$ t $ ($ 1 \leq t \leq 100 $)——测试用例的数量。

每个测试用例包含一个整数 $ n $ ($ 2 \leq n \leq 100 $)。

## 输出格式

对于每个测试用例，输出一个整数，即$ x $的最优值。可以看出只有一个唯一的答案。

## 说明/提示

对于“$ n = 3 $”，“$ x $”可能取值为“$ 2 $”和“$ 3 $”。所有小于等于$ n $的$ 2 $的倍数之和为$ 2 $，所有小于等于$ n $的$ 3 $的倍数之和为$ 3 $。因此，$ 3 $是$ x $的最优值。

对于$ n = 15 $, $ x $的最优值为$ 2 $。小于或等于$ n $的所有$ 2 $的倍数之和为$ 2 + 4 + 6 + 8 + 10 + 12 + 14 = 56 $，可以证明它是$ x $的所有其他可能值的最大值。

## 样例 #1

### 输入

```
2
3
15
```

### 输出

```
3
2
```



---

---
title: "Upload More RAM"
layout: "post"
diff: 入门
pid: CF1987A
tag: ['数学']
---

# Upload More RAM

## 题目描述

哦不，$ForceCodes$ 服务器内存不足！幸运的是，您可以通过上传一些$ RAM$ 来帮助他们！

您要上传
$?GB$ 的 $RAM$。每秒，您将上传$0$或$1GB$ 内存。但是，您的网络速度是有限制的：在任何对连续秒数，最多只能上传总共 $1GB$ 的 $RAM$。

查找上传所需的最短秒数
$nGB$ 或 $RAM$！

## 输入格式

每个测试都包含多个测试用例。输入的第一行包含单个整数$?$ ( $ 1\le t \le10^4$ ） —— 测试用例的数量。测试用例的描述如下。

每个测试用例的第一行也是唯一的一行包含两个整数$n$和$k$( $1\le?,k\le100 $） —— 要上传的$GB$数和时间窗口的长度。

## 输出格式

对于每个测试用例，输出一个整数——上传所需的最小秒数
$nGB$ 或 $RAM$。

## 样例 #1

### 输入

```
6
5 1
2 2
2 3
1 7
11 5
100 100
```

### 输出

```
5
3
4
1
51
9901
```



---

---
title: "Legs"
layout: "post"
diff: 入门
pid: CF1996A
tag: ['数学']
---

# Legs

## 题目描述

It's another beautiful day on Farmer John's farm.

After Farmer John arrived at his farm, he counted $ n $ legs. It is known only chickens and cows live on the farm, and a chicken has $ 2 $ legs while a cow has $ 4 $ .

What is the minimum number of animals Farmer John can have on his farm assuming he counted the legs of all animals?

## 输入格式

The first line contains single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

Each test case contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^3 $ , $ n $ is even).

## 输出格式

For each test case, output an integer, the minimum number of animals Farmer John can have on his farm.

## 样例 #1

### 输入

```
3
2
6
8
```

### 输出

```
1
2
2
```



---

---
title: "Theatre Square"
layout: "post"
diff: 入门
pid: CF1A
tag: ['数学']
---

# Theatre Square

## 题目描述

贝尔兰首都的剧院广场呈矩形，尺寸为 $n \times m$。在该市周年纪念日之际，人们决定用正方形的花岗岩石板铺设广场。每块石板的尺寸为 $a \times a$。

铺砌广场所需的石板最少数量是多少？石板可以覆盖比剧院广场更大的表面，但必须覆盖广场。不允许打碎石板。石板的边应与广场的边平行。

## 输入格式

输入包含三个正整数：$n$、$m$ 和 $a$（$1 \le n、m、a \le 10^9 $）。

## 输出格式

输出所需的石板数量。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
6 6 4

```

### 输出

```
4

```



---

---
title: "Zhan's Blender"
layout: "post"
diff: 入门
pid: CF2013A
tag: ['数学']
---

# Zhan's Blender

## 题目描述

今天，在“NSPhM”举办了一场俱乐部展会。小Z为了宣传他的糕点俱乐部，决定展示一下他的搅拌机的力量。

小Z有 $n$ 个水果。

搅拌机每秒最多能搅拌 $x$ 个水果。

每秒钟，小Z最多能向搅拌机内放入 $y$ 个水果。然后，搅拌机会搅拌其中的 $min(x,c)$ 个水果，$c$ 代表搅拌机内的水果数量。搅拌后，被搅拌的水果会被移出搅拌机。

请你帮助小Z计算出搅拌所有水果的最短用时。

## 输入格式

每个测试点包含多组测试数据。第一行一个整数 $t (1 \le t \le 1000)$ 表示数据组数。

每组测试数据的第一行一个整数 $n (0 \le n \le 10^9)$ 表示水果数，第二行包含两个整数 $x$ 和 $y (1 \le x,y \le 10^9)$，分别表示搅拌机每秒最多能搅拌的水果数和小Z每秒最多能向搅拌机内放入的水果数。

## 输出格式

对于每组测试数据，输出一个整数表示搅拌所有水果的最短用时。

## 说明/提示

在第一组样例中，先将 $2$ 个水果放入搅拌机，搅拌机会搅拌这 $2$ 个水果，最后搅拌机中将剩下 $0$ 个水果。然后将 $3$ 个水果放入搅拌机，搅拌机会搅拌这 $3$ 个水果。

在第二组样例中，每次将 $1$ 个水果放入搅拌机，重复 $3$ 次。

在第三组样例中，先将 $3$ 个水果放入搅拌机，然后再放 $3$ 个。

Translated By HShiDianLu.

## 样例 #1

### 输入

```
5
5
3 4
3
1 2
6
4 3
100
4 3
9
3 3
```

### 输出

```
2
3
2
34
3
```



---

---
title: "Find Minimum Operations"
layout: "post"
diff: 入门
pid: CF2020A
tag: ['数学', '进制']
---

# Find Minimum Operations

## 题目描述

You are given two integers $ n $ and $ k $ .

In one operation, you can subtract any power of $ k $ from $ n $ . Formally, in one operation, you can replace $ n $ by $ (n-k^x) $ for any non-negative integer $ x $ .

Find the minimum number of operations required to make $ n $ equal to $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 10^9 $ ).

## 输出格式

For each test case, output the minimum number of operations on a new line.

## 说明/提示

In the first test case, $ n = 5 $ and $ k = 2 $ . We can perform the following sequence of operations:

1. Subtract $ 2^0 = 1 $ from $ 5 $ . The current value of $ n $ becomes $ 5 - 1 = 4 $ .
2. Subtract $ 2^2 = 4 $ from $ 4 $ . The current value of $ n $ becomes $ 4 - 4 = 0 $ .

It can be shown that there is no way to make $ n $ equal to $ 0 $ in less than $ 2 $ operations. Thus, $ 2 $ is the answer.

In the second test case, $ n = 3 $ and $ k = 5 $ . We can perform the following sequence of operations:

1. Subtract $ 5^0 = 1 $ from $ 3 $ . The current value of $ n $ becomes $ 3 - 1 = 2 $ .
2. Subtract $ 5^0 = 1 $ from $ 2 $ . The current value of $ n $ becomes $ 2 - 1 = 1 $ .
3. Subtract $ 5^0 = 1 $ from $ 1 $ . The current value of $ n $ becomes $ 1 - 1 = 0 $ .

It can be shown that there is no way to make $ n $ equal to $ 0 $ in less than $ 3 $ operations. Thus, $ 3 $ is the answer.

## 样例 #1

### 输入

```
6
5 2
3 5
16 4
100 3
6492 10
10 1
```

### 输出

```
2
3
1
4
21
10
```



---

---
title: "Profitable Interest Rate"
layout: "post"
diff: 入门
pid: CF2024A
tag: ['数学', '贪心']
---

# Profitable Interest Rate

## 题目描述

Alice 有 $a$ 个硬币。她可以开设一个名为“有利”的银行存款账户，但开设该账户的最低金额要求是 $b$ 个硬币。

还有一种名为“无利”的存款账户，可以用任意数量的硬币开设。Alice 注意到，如果她使用 $x$ 个硬币开设“无利”账户，开设“有利”账户所需的最低金额会减少 $2x$ 个硬币。然而，这些硬币之后不能再存入“有利”账户。

请帮助 Alice 确定她在先向“无利”账户存入一些硬币（可能为 $0$ ）后，最多能向“有利”账户存入多少硬币。如果 Alice 永远无法开设“有利”账户，则输出 $0$。

## 输入格式

**本题有多组测试数据。**

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——表示测试用例的数量。接下来的每个测试用例描述如下。

每个测试用例包含一行，由两个整数 $a$ 和 $b$ 组成（$1 \leq a, b \leq 10^9$）——分别表示 Alice 拥有的硬币数和开设“有利”账户的初始最低要求。

## 输出格式

对于每个测试用例，输出一个整数——Alice 最多能向“有利”账户存入的硬币数。如果 Alice 永远无法开设“有利”账户，则输出 $0$。

## 说明/提示

在第一个测试用例中，$a \geq b$，所以 Alice 可以直接用全部的 10 个硬币开设“有利”账户。

在第二个测试用例中，Alice 可以用 2 个硬币开设“无利”账户。然后她剩下 5 个硬币，而开设“有利”账户的最低要求将减少 4 个硬币，变为 5 个硬币。因此，Alice 将能够用 5 个硬币开设“有利”账户。

在第三个测试用例中，Alice 无法开设“有利”账户。

## 样例 #1

### 输入

```
5
10 5
7 9
5 100
1 1
1 2
```

### 输出

```
10
5
0
1
0
```



---

---
title: "King Keykhosrow's Mystery"
layout: "post"
diff: 入门
pid: CF2034A
tag: ['数学']
---

# King Keykhosrow's Mystery

## 题目描述

传说，凯霍斯鲁国王有一座巨大的宝库，收藏了来自波斯帝国各地的珍宝。宝库被一把魔法锁封住了，只有解开谜语才能打开。

谜语包括两个整数 $a,b$，你要找到满足以下条件的最小整数 $m$ 才能解锁宝库：

- $m$ 必须大于等于 $a,b$ 中的至少一个。
- $m$ 除以 $a$ 的余数必须等于 $m$ 除以 $b$ 的余数。

你必须找到最小的 $m$ 才能解锁宝库！

## 输入格式

第一行，一个整数 $t$ ($1\le t\le 100$)，表示数据组数。

对于每组数据，输入两个整数 $a,b$ ($1\le a,b\le 1000$)。

## 输出格式

对于每组数据，输出满足条件的最小 $m$。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
2
4 6
472 896
```

### 输出

```
12
52864
```



---

---
title: "Coin Transformation"
layout: "post"
diff: 入门
pid: CF2043A
tag: ['数学', '贪心']
---

# Coin Transformation

## 题目描述

最开始，你有一枚价值为 $n$ 的硬币。你可以任意多次地执行以下操作：

- 将一枚价值为 $x$ 的硬币（其中 $x > 3$）转换成两枚价值为 $\lfloor \frac{x}{4} \rfloor$ 的硬币。

经过一系列操作后，你最多能得到多少枚硬币？

## 输入格式

第一行输入一个整数 $t$ ($1 \le t \le 10^4$)，表示测试用例的数量。

接下来每个测试用例占一行，包含一个整数 $n$ ($1 \le n \le 10^{18}$)。

## 输出格式

对于每个测试用例，输出一个整数，表示通过任意次数的操作后，你能获得的最大硬币数量。

## 说明/提示

例如，在第一个例子中，你只有一枚价值为 $1$ 的硬币，无法进行任何转换。所以，答案是 $1$。

在第二个例子中，你可以把一枚价值为 $5$ 的硬币转化为两枚价值为 $1$ 的硬币。

在第三个例子中，你可以把一枚价值为 $16$ 的硬币转化为两枚价值为 $4$ 的硬币。然后，每枚价值为 $4$ 的硬币可以继续转化成两枚价值为 $1$ 的硬币。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
5
16
1000000000000000000
```

### 输出

```
1
2
4
536870912
```



---

---
title: "MEX Table"
layout: "post"
diff: 入门
pid: CF2057A
tag: ['数学']
---

# MEX Table

## 题目描述

某天，顽皮的学生马克在课堂上捣乱，于是老师萨沙让他上黑板。萨沙给了马克一个 $n$ 行 $m$ 列的表格，要他在表格中填写数字 $0, 1, \ldots, n \cdot m - 1$。每个数字必须使用且仅使用一次，并要求这些数字的排列方式使得每行和每列的 MEX（最小未出现非负整数）之和最大化。具体来说，他需要使 $\sum\limits_{i = 1}^{n} \operatorname{mex}(\{a_{i,1}, a_{i,2}, \ldots, a_{i,m}\}) + \sum\limits_{j = 1}^{m} \operatorname{mex}(\{a_{1,j}, a_{2,j}, \ldots, a_{n,j}\})$ 最大，其中 $a_{i,j}$ 表示第 $i$ 行第 $j$ 列的数字。老师萨沙只关心最终的结果，因此他要求马克只需要告诉他在最佳填法下行和列 MEX 之和的最大值。

**注释**：MEX（最小未出现非负整数）定义为在给定的整数集合中未出现的最小非负整数。例如：
- 对于集合 $\{2,2,1\}$，$\operatorname{mex} = 0$，因为数字 $0$ 没有出现在集合中。
- 对于集合 $\{3,1,0,1\}$，$\operatorname{mex} = 2$，因为数字 $0$ 和 $1$ 出现在集合中，而 $2$ 没有。
- 对于集合 $\{0,3,1,2\}$，$\operatorname{mex} = 4$，因为数字 $0, 1, 2, 3$ 都出现在集合中，而 $4$ 没有。

## 输入格式

输入包含多个测试用例。第一行输入一个整数 $t$（$1 \le t \le 1000$），表示测试用例的数量。接下来的每个测试用例由两部分组成：

- 一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 10^9$），分别表示表格的行数和列数。

## 输出格式

对于每个测试用例，输出一个整数，表示在所有可能的排列方式中，行和列的 MEX 之和的最大值。

## 说明/提示

- 在第一个测试用例中，由于表格中唯一的数字是 $0$，因此第一行和第一列的 MEX 之和为 $\operatorname{mex}(\{0\}) + \operatorname{mex}(\{0\}) = 1 + 1 = 2$。
  
- 在第二个测试用例中，可以将表格填充为如下：

$$
\begin{array}{cc}
3 & 0 \\
2 & 1 \\
\end{array}
$$

这样计算可得 $\sum\limits_{i = 1}^{n} \operatorname{mex}(\{a_{i,1}, a_{i,2}, \ldots, a_{i,m}\}) + \sum\limits_{j = 1}^{m} \operatorname{mex}(\{a_{1,j}, a_{2,j}, \ldots, a_{n,j}\}) = \operatorname{mex}(\{3, 0\}) + \operatorname{mex}(\{2, 1\}) + \operatorname{mex}(\{3, 2\}) + \operatorname{mex}(\{0, 1\}) = 1 + 0 + 0 + 2 = 3$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1 1
2 2
3 5
```

### 输出

```
2
3
6
```



---

---
title: "Draw a Square"
layout: "post"
diff: 入门
pid: CF2074A
tag: ['数学', '标签482']
---

# Draw a Square

## 题目描述

粉色士兵们给了你平面上的 $4$ 个不同点。这 $4$ 个点的坐标分别为 $(-l, 0)$、$(r, 0)$、$(0, -d)$ 和 $(0, u)$，其中 $l$、$ r$、$d$、$u$ 是正整数。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2074A/cae2389956c359d11ac6b1eaa6f81027eb9d1dfa.png) 

在图中，通过连接四个点 $L$、$R$、$D$、$U$ 绘制了一个正方形。请判断是否可以使用给定的四个点作为顶点绘制一个正方形$^{\text{∗}}$。

$^{\text{∗}}$正方形的定义是一个由 $4$ 个顶点组成的多边形，其所有边长相等且所有内角相等。多边形的任意两条边不得相交。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含四个整数 $l$、$r$、$d$、$u$（$1 \le l, r, d, u \le 10$）。

## 输出格式

对于每个测试用例，如果可以使用这四个点绘制正方形，则输出 "Yes"。否则输出 "No"。

答案可以以任意大小写形式输出。例如字符串 "yEs"、"yes" 和 "YES" 都会被识别为肯定回答。

## 说明/提示

在第一个测试用例中，给定的四个点构成正方形，因此答案是 "Yes"。

在第二个测试用例中，给定的四个点不构成正方形，因此答案是 "No"。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
2 2 2 2
1 2 3 4
```

### 输出

```
Yes
No
```



---

---
title: "Cloudberry Jam"
layout: "post"
diff: 入门
pid: CF2086A
tag: ['数学']
---

# Cloudberry Jam

## 题目描述

卡累利阿森林中最珍贵的浆果是云莓。制作云莓果酱时，需要取等量的浆果和糖一起熬煮。也就是说，如果你有 $2$ 公斤浆果，就需要 $2$ 公斤糖。然而，用 $2$ 公斤浆果和 $2$ 公斤糖熬制出的果酱并不是预期的 $4$ 公斤，而是只有 $3$ 公斤，因为在熬制过程中会有部分果酱蒸发。具体来说，在标准熬制过程中，恰好有四分之一的果酱（即 $25\%$）会蒸发。

需要准备多少公斤云莓才能制作 $n$ 个 $3$ 公斤装的果酱罐？

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2086A/a0f0b52f65b14c6ab71d13c5f41576b89b50d011.png)

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 10^{4}$）——测试用例的数量。接下来的行描述每个测试用例。

每个测试用例包含一个整数 $n$（$1 \le n \le 10^8$）——需要制作的果酱罐数。


## 输出格式

对于每个测试用例，输出一个整数——制作果酱所需的云莓重量（以公斤为单位）。


## 说明/提示

- 对于测试用例 $1$，题目描述中已经给出解释——制作 $1$ 罐果酱需要 $2$ 公斤云莓。

- 考虑测试用例 $2$：如果我们取 $6$ 公斤浆果和 $6$ 公斤糖，将得到 $\frac{(6 + 6) \cdot 3}{4} = 9$ 公斤果酱；这相当于 $\frac{9}{3} = 3$ 罐果酱。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
1
3
```

### 输出

```
2
6
```



---

---
title: "Treasure Hunt"
layout: "post"
diff: 入门
pid: CF2090A
tag: ['数学']
---

# Treasure Hunt

## 题目描述

小 B 和他的朋友小 K 发现了一张藏宝图，现在他们只需要挖出埋藏在 $$$a.5$$$ 米深处的宝藏。

他们轮流进行挖掘：第一天由小 B 挖掘，第二天由小 K 挖掘，之后每天交替进行。小 B 每天恰好挖 $$$x$$$ 米土壤，小 K 每天挖 $$$y$$$ 米。他们想知道最终会由谁率先挖到宝藏，即在谁的工作日期间，累计挖掘深度首次超过 $$$a.5$$$ 米。

但他们忙于挖掘无法计算，请帮助他们判断谁会先挖到宝藏！

## 输入格式

第一行包含一个整数 $$$t$$$（$$$1 \le t \le 1000$$$）——测试用例数量。接下来是测试用例描述。

每个测试用例的单行中包含三个数字 $$$x$$$、$$$y$$$、$$$a$$$（$$$1 \leq x, y, a \leq 10^9$$$）。


## 输出格式

对于每个测试用例：
- 若小 B 先挖到宝藏，输出 "NO"
- 否则输出 "YES"
答案大小写不敏感。

## 说明/提示

第一个测试用例中：
- 第 1 天挖 1 米
- 第 2 天累计 3 米（1 + 2）
- 第 3 天累计 4 米（1 + 2 + 1）
- 第 4 天累计 6 米（超过 5.5 米）
因此由小 K 率先挖到。

第二个测试用例中：
- 第 1 天挖 2 米
- 第 2 天累计 3 米（2 + 1）
- 第 3 天累计 5 米（超过 4.5 米）
因此由小 B 率先挖到。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
1 2 4
2 1 4
2 2 1
```

### 输出

```
YES
NO
NO
```



---

---
title: "Dr. TC"
layout: "post"
diff: 入门
pid: CF2106A
tag: ['数学']
---

# Dr. TC

## 题目描述

为了测试病人的智力水平，TC 医生设计了以下测试。

首先，他创建一个长度为 $n$ 的二进制字符串$^{\text{∗}}$ $s$。然后，他创建 $n$ 个二进制字符串 $a_1, a_2, \ldots, a_n$。已知 $a_i$ 是通过先复制 $s$，然后翻转第 $i$ 个字符（$\texttt{1}$ 变为 $\texttt{0}$，反之亦然）得到的。创建完所有 $n$ 个字符串后，他将它们排列成一个网格，其中第 $i$ 行是 $a_i$。

例如：
- 如果 $s = \texttt{101}$，则 $a = [\texttt{001}, \texttt{111}, \texttt{100}]$；
- 如果 $s = \texttt{0000}$，则 $a = [\texttt{1000}, \texttt{0100}, \texttt{0010}, \texttt{0001}]$。

病人需要在不到一秒的时间内计算出黑板上所有 $\texttt{1}$ 的数量。你能通过这个测试吗？

$^{\text{∗}}$ 二进制字符串是指仅由字符 $\texttt{1}$ 和 $\texttt{0}$ 组成的字符串。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 1000$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10$）——二进制字符串 $s$ 的长度。

每个测试用例的第二行包含一个长度为 $n$ 的二进制字符串 $s$。

## 输出格式

对于每个测试用例，输出一个整数，表示黑板上所有 $\texttt{1}$ 的数量。


## 说明/提示

第一个样例已在题目描述中解释。

对于第二个样例，黑板上唯一的字符串是 $\texttt{0}$，因此答案是 $0$。

在第三个样例中，黑板上将显示以下字符串：$[\texttt{10000}, \texttt{01000}, \texttt{00100}, \texttt{00010}, \texttt{00001}]$，所以黑板上共有 $5$ 个 $\texttt{1}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
101
1
1
5
00000
2
11
3
010
```

### 输出

```
5
0
5
2
4
```



---

---
title: "Race"
layout: "post"
diff: 入门
pid: CF2112A
tag: ['数学', '枚举']
---

# Race

## 题目描述

Alice 和 Bob 正在参加一场电视节目的游戏。游戏开始的时候，奖品会被放在某个点上，第一个到达奖品所在位置的人将获得奖品。

Alice 决定她将从点 $a$ 起跑。Bob 还没有决定他的出发点。

Bob 知道奖品会落在点 $x$ 或点 $y$ 处，他可以在 Alice 之前到达奖品的位置当且仅当他的出发点和奖品的距离严格小于 Alice 的出发点和奖品的距离。点 $c$ 和点 $d$ 之间的距离是 $\vert c-d\vert$。

你的任务是回答 Bob 能不能选出一个整点，使得无论奖品是在点 $x$ 还是点 $y$ 处出现，都能保证他比 Alice 先到达奖品处。他可以选择除了 $a$ 以外的所有整点，包括 $x$ 和 $y$。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 1000)$，表示数据组数。

对于每组数据，一行三个整数 $a,x,y(1\le a,x,y\le 100)$。三个数字两两不同。

## 输出格式

对于每组数据，如果答案为可以，那么输出一行一个字符串 `YES`；否则输出一行一个字符串 `NO`。

## 说明/提示

**样例解释**

对于第一组数据，Bob 可以选择点 $4$，如果奖品出现在点 $x$，Bob 和它之间的距离为 $\vert 4-3\vert=1$，Alice 和它之间的距离为 $\vert 1-3\vert=2$。如果奖品出现在点 $y$，Bob 和它之间的距离为 $\vert 4-4\vert=0$，Alice 和它之间的距离为 $\vert 1-4\vert=3$。

对于第二组数据，Bob 可以选择点 $2$，如果奖品出现在点 $x$，Bob 和它之间的距离为 $\vert 2-3\vert=1$，Alice 和它之间的距离为 $\vert 5-3\vert=2$。如果奖品出现在点 $y$，Bob 和它之间的距离为 $\vert 2-1\vert=1$，Alice 和它之间的距离为 $\vert 5-1\vert=4$。

对于第三组数据，Bob 无法选择一个点保证自己胜利。


## 样例 #1

### 输入

```
3
1 3 4
5 3 1
3 1 5
```

### 输出

```
YES
YES
NO
```



---

---
title: "Square Year"
layout: "post"
diff: 入门
pid: CF2114A
tag: ['数学']
---

# Square Year

## 题目描述

> 注意到 $2025 = {(20+25)}^2$。

给你一个用长度为 $4$ 的字符串表示的年份，年份表示中允许使用前导零，因此 `0001`、`0185`、`1375` 等都是合法的年份表示。你需要把这个年份变为 ${(a+b)}^2$ 的格式（其中 $a$ 和 $b$ 为非负整数），或判断无解。

例如，如果给出的年份是 `0001`，那么一种可能的解为 $a=0,\ b=1$，此时 ${(0+1)}^2=1$。

## 输入格式

第一行输入一个正整数 $t\ (1 \le t \le {10}^4)$，表示测试数据组数。

以后 $t$ 行，每行一个长度为 $4$ 且仅含有数字字符的字符串 $s$，代表一个年份。

## 输出格式

对于每组测试数据，输出一行：如果满足条件的非负整数 $a$ 和 $b$ 存在，那么输出 $a$ 和 $b$，以空格分隔（如果有多解，输出任意一组）。如果无解，输出一个整数 $-1$。

## 样例 #1

### 输入

```
5
0001
1001
1000
4900
2025
```

### 输出

```
0 1
-1
-1
34 36
20 25
```



---

---
title: "Triangular numbers"
layout: "post"
diff: 入门
pid: CF47A
tag: ['搜索', '数学', '枚举']
---

# Triangular numbers

## 题目描述

A triangular number is the number of dots in an equilateral triangle uniformly filled with dots. For example, three dots can be arranged in a triangle; thus three is a triangular number. The $ n $ -th triangular number is the number of dots in a triangle with $ n $ dots on a side. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF47A/7344b4fd5acb7c973775cffc0c5a51a81c6ee4d9.png). You can learn more about these numbers from Wikipedia (http://en.wikipedia.org/wiki/Triangular\_number).

Your task is to find out if a given integer is a triangular number.

## 输入格式

The first line contains the single number $ n $ ( $ 1<=n<=500 $ ) — the given integer.

## 输出格式

If the given integer is a triangular number output YES, otherwise output NO.

## 样例 #1

### 输入

```
1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3

```

### 输出

```
YES

```



---

---
title: "Vanya and Cubes"
layout: "post"
diff: 入门
pid: CF492A
tag: ['模拟', '数学', '枚举']
---

# Vanya and Cubes

## 题目描述

Vanya got $ n $ cubes. He decided to build a pyramid from them. Vanya wants to build the pyramid as follows: the top level of the pyramid must consist of $ 1 $ cube, the second level must consist of $ 1+2=3 $ cubes, the third level must have $ 1+2+3=6 $ cubes, and so on. Thus, the $ i $ -th level of the pyramid must have $ 1+2+...+(i-1)+i $ cubes.

Vanya wants to know what is the maximum height of the pyramid that he can make using the given cubes.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{4} $ ) — the number of cubes given to Vanya.

## 输出格式

Print the maximum possible height of the pyramid in the single line.

## 说明/提示

Illustration to the second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF492A/95fc6e512a79cba53044cb07f98e0b0b07a634cb.png)

## 样例 #1

### 输入

```
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
25

```

### 输出

```
4

```



---

---
title: "Watermelon"
layout: "post"
diff: 入门
pid: CF4A
tag: ['数学', '枚举']
---

# Watermelon

## 题目描述

一个炎热的夏天，Pete 和他的朋友 Billy 感到十分口渴，于是在西瓜摊上买了一个重 $w$ 公斤的西瓜。

他们回到家准备分西瓜。因为两个人都十分喜爱偶数，所以他们俩希望分出来的两块西瓜的重量都是偶数公斤。帮助他们判断是否可能做到这一点。

## 输入格式

一行一个整数 $w\,(0\le w\le100)$。

## 输出格式

如果可以按照他们的意愿分配西瓜，输出 `YES`；否则输出 `NO`。

### 样例 #1 解释

他们可以将西瓜分成 $2$ 公斤和 $6$ 公斤。

-----

翻译 By @[Eason_cyx](https://www.luogu.com.cn/user/741244)。

## 样例 #1

### 输入

```
8

```

### 输出

```
YES

```



---

---
title: "123-sequence"
layout: "post"
diff: 入门
pid: CF52A
tag: ['数学', '贪心', '概率论']
---

# 123-sequence

## 题目描述

There is a given sequence of integers $ a_{1},a_{2},...,a_{n} $ , where every number is from 1 to 3 inclusively. You have to replace the minimum number of numbers in it so that all the numbers in the sequence are equal to each other.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ). The second line contains a sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=3 $ ).

## 输出格式

Print the minimum number of replacements needed to be performed to make all the numbers in the sequence equal.

## 说明/提示

In the example all the numbers equal to 1 and 3 should be replaced by 2.

## 样例 #1

### 输入

```
9
1 3 2 2 2 1 1 2 3

```

### 输出

```
5

```



---

---
title: "Soldier and Bananas"
layout: "post"
diff: 入门
pid: CF546A
tag: ['字符串', '数学', '概率论']
---

# Soldier and Bananas

## 题目描述

A soldier wants to buy $ w $ bananas in the shop. He has to pay $ k $ dollars for the first banana, $ 2k $ dollars for the second one and so on (in other words, he has to pay $ i·k $ dollars for the $ i $ -th banana).

He has $ n $ dollars. How many dollars does he have to borrow from his friend soldier to buy $ w $ bananas?

## 输入格式

The first line contains three positive integers $ k,n,w $ ( $ 1<=k,w<=1000 $ , $ 0<=n<=10^{9} $ ), the cost of the first banana, initial number of dollars the soldier has and number of bananas he wants.

## 输出格式

Output one integer — the amount of dollars that the soldier must borrow from his friend. If he doesn't have to borrow money, output $ 0 $ .

## 样例 #1

### 输入

```
3 17 4

```

### 输出

```
13
```



---

---
title: "A Student's Dream"
layout: "post"
diff: 入门
pid: CF62A
tag: ['数学', '贪心']
---

# A Student's Dream

## 题目描述

**题目大意：**

有两个人要握手，女孩左手有 $a_l$ 个手指，右手有 $a_r$ 个手指；男孩左手有 $b_l$ 个手指，右手有 $b_r$ 个手指。握手规则为：男孩可以用左手握女孩的右手，也可以用右手握女孩的左手。在女孩的两根手指中间必须有男孩的一根手指，并且男孩的三根手指之间必须有女孩的一根手指。

现在要判断如果可以握手输出 `YES`，不能输出 `NO`。

## 样例 #1

### 输入

```
5 1
10 5

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 5
3 3

```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 2
11 6

```

### 输出

```
NO
```



---

---
title: "The New Year: Meeting Friends"
layout: "post"
diff: 入门
pid: CF723A
tag: ['模拟', '数学']
---

# The New Year: Meeting Friends

## 题目描述

有三个朋友在一条笔直的岛上生活着，我们将其看做一条直线（数轴）。第一个人的家在点$x_1$​ 处，第二个人的家在点$x_2$处，第三个人的家在点$x_3$处。他们计划一起庆祝新年，所以他们需要在直线上的任一某点见面。请你帮他们找出一个点，使得他们走的总距离最短，并求出这个总距离。

## 输入格式

第一行有三个数，$x_1$，$x_2$​ ，$x_3$ ，(1<=$x_1$​ ，$x_2$​ ，$x_3$<=100)。分别对应第一、第二和第三个人的房子的位置。

## 输出格式

输出一个整数：最小的总距离以满足他们能在一起庆祝新年。

## 说明/提示

在第一个样例中，朋友们应在点4见面。因此，第一个朋友必须走3个单位距离（从点7到点4），第二个朋友也要走3个单位距离（从点1到点4），而第三位朋友不用去任何地方，因为他住在点4。

感谢@cplus 提供的翻译

## 样例 #1

### 输入

```
7 1 4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
30 20 10

```

### 输出

```
20

```



---

---
title: "Buy a Shovel"
layout: "post"
diff: 入门
pid: CF732A
tag: ['模拟', '搜索', '数学']
---

# Buy a Shovel

## 题目描述

Polycarp urgently needs a shovel! He comes to the shop and chooses an appropriate one. The shovel that Policarp chooses is sold for $ k $ burles. Assume that there is an unlimited number of such shovels in the shop.

In his pocket Polycarp has an unlimited number of "10-burle coins" and exactly one coin of $ r $ burles ( $ 1<=r<=9 $ ).

What is the minimum number of shovels Polycarp has to buy so that he can pay for the purchase without any change? It is obvious that he can pay for 10 shovels without any change (by paying the requied amount of 10-burle coins and not using the coin of $ r $ burles). But perhaps he can buy fewer shovels and pay without any change. Note that Polycarp should buy at least one shovel.

## 输入格式

The single line of input contains two integers $ k $ and $ r $ ( $ 1<=k<=1000 $ , $ 1<=r<=9 $ ) — the price of one shovel and the denomination of the coin in Polycarp's pocket that is different from "10-burle coins".

Remember that he has an unlimited number of coins in the denomination of 10, that is, Polycarp has enough money to buy any number of shovels.

## 输出格式

Print the required minimum number of shovels Polycarp has to buy so that he can pay for them without any change.

## 说明/提示

In the first example Polycarp can buy 9 shovels and pay $ 9·117=1053 $ burles. Indeed, he can pay this sum by using 10-burle coins and one 3-burle coin. He can't buy fewer shovels without any change.

In the second example it is enough for Polycarp to buy one shovel.

In the third example Polycarp should buy two shovels and pay $ 2·15=30 $ burles. It is obvious that he can pay this sum without any change.

## 样例 #1

### 输入

```
117 3

```

### 输出

```
9

```

## 样例 #2

### 输入

```
237 7

```

### 输出

```
1

```

## 样例 #3

### 输入

```
15 2

```

### 输出

```
2

```



---

---
title: "Display Size"
layout: "post"
diff: 入门
pid: CF747A
tag: ['数学', '枚举']
---

# Display Size

## 题目描述

A big company decided to launch a new series of rectangular displays, and decided that the display must have exactly $ n $ pixels.

Your task is to determine the size of the rectangular display — the number of lines (rows) of pixels $ a $ and the number of columns of pixels $ b $ , so that:

- there are exactly $ n $ pixels on the display;
- the number of rows does not exceed the number of columns, it means $ a<=b $ ;
- the difference $ b-a $ is as small as possible.

## 输入格式

The first line contains the positive integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of pixels display should have.

## 输出格式

Print two integers — the number of rows and columns on the display.

## 说明/提示

In the first example the minimum possible difference equals 2, so on the display should be 2 rows of 4 pixels.

In the second example the minimum possible difference equals 0, so on the display should be 8 rows of 8 pixels.

In the third example the minimum possible difference equals 4, so on the display should be 1 row of 5 pixels.

## 样例 #1

### 输入

```
8

```

### 输出

```
2 4

```

## 样例 #2

### 输入

```
64

```

### 输出

```
8 8

```

## 样例 #3

### 输入

```
5

```

### 输出

```
1 5

```

## 样例 #4

### 输入

```
999999

```

### 输出

```
999 1001

```



---

---
title: "I'm bored with life"
layout: "post"
diff: 入门
pid: CF822A
tag: ['数学', '最大公约数 gcd']
---

# I'm bored with life

## 题目描述

Holidays have finished. Thanks to the help of the hacker Leha, Noora managed to enter the university of her dreams which is located in a town Pavlopolis. It's well known that universities provide students with dormitory for the period of university studies. Consequently Noora had to leave Vičkopolis and move to Pavlopolis. Thus Leha was left completely alone in a quiet town Vičkopolis. He almost even fell into a depression from boredom!

Leha came up with a task for himself to relax a little. He chooses two integers $ A $ and $ B $ and then calculates the greatest common divisor of integers " $ A $ factorial" and " $ B $ factorial". Formally the hacker wants to find out GCD $ (A!,B!) $ . It's well known that the factorial of an integer $ x $ is a product of all positive integers less than or equal to $ x $ . Thus $ x!=1·2·3·...·(x-1)·x $ . For example $ 4!=1·2·3·4=24 $ . Recall that GCD $ (x,y) $ is the largest positive integer $ q $ that divides (without a remainder) both $ x $ and $ y $ .

Leha has learned how to solve this task very effective. You are able to cope with it not worse, aren't you?

## 输入格式

The first and single line contains two integers $ A $ and $ B $ $ (1<=A,B<=10^{9},min(A,B)<=12) $ .

## 输出格式

Print a single integer denoting the greatest common divisor of integers $ A! $ and $ B! $ .

## 说明/提示

Consider the sample.

 $ 4!=1·2·3·4=24 $ . $ 3!=1·2·3=6 $ . The greatest common divisor of integers $ 24 $ and $ 6 $ is exactly $ 6 $ .

## 样例 #1

### 输入

```
4 3

```

### 输出

```
6

```



---

---
title: "Div. 64"
layout: "post"
diff: 入门
pid: CF887A
tag: ['字符串', '数学', '进制']
---

# Div. 64

## 题目描述

超模$Izabella$ 参加了比赛。她想要给评委留下深刻的印象并且展示她的数学技能。

她的问题如下：对于一个只由$0$ 和$1$ 组成的字符串，判断是否能删掉一些数字，使得得到的二进制数能被$64$ 整除。

## 输入格式

一行，为一个长度不超过$100$ 的$01$ 字符串。

## 输出格式

如果可以，输出$yes$ ，否则输出$no$ 。

感谢@M_sea 提供的翻译

## 样例 #1

### 输入

```
100010001

```

### 输出

```
yes
```

## 样例 #2

### 输入

```
100

```

### 输出

```
no
```



---

---
title: "Supermarket"
layout: "post"
diff: 入门
pid: CF919A
tag: ['数学', '贪心', '排序']
---

# Supermarket

## 题目描述

We often go to supermarkets to buy some fruits or vegetables, and on the tag there prints the price for a kilo. But in some supermarkets, when asked how much the items are, the clerk will say that $ a $ yuan for $ b $ kilos (You don't need to care about what "yuan" is), the same as $ a/b $ yuan for a kilo.

Now imagine you'd like to buy $ m $ kilos of apples. You've asked $ n $ supermarkets and got the prices. Find the minimum cost for those apples.

You can assume that there are enough apples in all supermarkets.

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1<=n<=5000 $ , $ 1<=m<=100 $ ), denoting that there are $ n $ supermarkets and you want to buy $ m $ kilos of apples.

The following $ n $ lines describe the information of the supermarkets. Each line contains two positive integers $ a,b $ ( $ 1<=a,b<=100 $ ), denoting that in this supermarket, you are supposed to pay $ a $ yuan for $ b $ kilos of apples.

## 输出格式

The only line, denoting the minimum cost for $ m $ kilos of apples. Please make sure that the absolute or relative error between your answer and the correct answer won't exceed $ 10^{-6} $ .

Formally, let your answer be $ x $ , and the jury's answer be $ y $ . Your answer is considered correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919A/9c418c1ac059184ac2ec8107da47a63db7a44091.png).

## 说明/提示

In the first sample, you are supposed to buy $ 5 $ kilos of apples in supermarket $ 3 $ . The cost is $ 5/3 $ yuan.

In the second sample, you are supposed to buy $ 1 $ kilo of apples in supermarket $ 2 $ . The cost is $ 98/99 $ yuan.

## 样例 #1

### 输入

```
3 5
1 2
3 4
1 3

```

### 输出

```
1.66666667

```

## 样例 #2

### 输入

```
2 1
99 100
98 99

```

### 输出

```
0.98989899

```



---

---
title: "Chips"
layout: "post"
diff: 入门
pid: CF92A
tag: ['模拟', '数学', '概率论']
---

# Chips

## 题目描述

现在有n个海狮坐成一个圆圈玩♂游♂戏。所有海狮都被顺时针的被编上号码了：2号海狮在1号海狮的左边坐着，3号海狮在2号海狮的左边坐着，……，1号海狮在n号海狮的左边坐着。


我们还有一位慷慨的来自某薯片公司的员工。他为了宣传他的薯片有多好吃，带来了m片薯片来到海狮群做宣传。他站在海狮圈的中间并顺时针转动。第i号海狮可以分到i个薯片。如果这位员工没有足够的薯片，这个黑心的员工就带着剩下的薯片跑了。现在给你n和m，让你求这个员工最后会拿多少薯片。

## 输入格式

一行，包含两个整数n和m。（1<=n<=50，1<=m<=10^4）

## 输出格式

输出这个员工带着多少薯片跑了

感谢@deadpool123 提供翻译

## 样例 #1

### 输入

```
4 11

```

### 输出

```
0

```

## 样例 #2

### 输入

```
17 107

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 8

```

### 输出

```
1

```



---

---
title: "Fafa and his Company"
layout: "post"
diff: 入门
pid: CF935A
tag: ['数学', '枚举', '概率论']
---

# Fafa and his Company

## 题目描述

Fafa owns a company that works on huge projects. There are $ n $ employees in Fafa's company. Whenever the company has a new project to start working on, Fafa has to divide the tasks of this project among all the employees.

Fafa finds doing this every time is very tiring for him. So, he decided to choose the best $ l $ employees in his company as team leaders. Whenever there is a new project, Fafa will divide the tasks among only the team leaders and each team leader will be responsible of some positive number of employees to give them the tasks. To make this process fair for the team leaders, each one of them should be responsible for the same number of employees. Moreover, every employee, who is not a team leader, has to be under the responsibility of exactly one team leader, and no team leader is responsible for another team leader.

Given the number of employees $ n $ , find in how many ways Fafa could choose the number of team leaders $ l $ in such a way that it is possible to divide employees between them evenly.

## 输入格式

The input consists of a single line containing a positive integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of employees in Fafa's company.

## 输出格式

Print a single integer representing the answer to the problem.

## 说明/提示

In the second sample Fafa has 3 ways:

- choose only $ 1 $ employee as a team leader with $ 9 $ employees under his responsibility.
- choose $ 2 $ employees as team leaders with $ 4 $ employees under the responsibility of each of them.
- choose $ 5 $ employees as team leaders with $ 1 $ employee under the responsibility of each of them.

## 样例 #1

### 输入

```
2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10

```

### 输出

```
3

```



---

---
title: "Die Roll"
layout: "post"
diff: 入门
pid: CF9A
tag: ['数学', '递归', '最大公约数 gcd']
---

# Die Roll

## 题目描述

Yakko, Wakko and Dot, world-famous animaniacs, decided to rest from acting in cartoons, and take a leave to travel a bit. Yakko dreamt to go to Pennsylvania, his Motherland and the Motherland of his ancestors. Wakko thought about Tasmania, its beaches, sun and sea. Dot chose Transylvania as the most mysterious and unpredictable place.

But to their great regret, the leave turned to be very short, so it will be enough to visit one of the three above named places. That's why Yakko, as the cleverest, came up with a truly genius idea: let each of the three roll an ordinary six-sided die, and the one with the highest amount of points will be the winner, and will take the other two to the place of his/her dreams.

Yakko thrown a die and got Y points, Wakko — W points. It was Dot's turn. But she didn't hurry. Dot wanted to know for sure what were her chances to visit Transylvania.

It is known that Yakko and Wakko are true gentlemen, that's why if they have the same amount of points with Dot, they will let Dot win.

## 输入格式

The only line of the input file contains two natural numbers Y and W — the results of Yakko's and Wakko's die rolls.

## 输出格式

Output the required probability in the form of irreducible fraction in format «A/B», where A — the numerator, and B — the denominator. If the required probability equals to zero, output «0/1». If the required probability equals to 1, output «1/1».

## 说明/提示

Dot will go to Transylvania, if she is lucky to roll 4, 5 or 6 points.

## 样例 #1

### 输入

```
4 2

```

### 输出

```
1/2

```



---

