---
title: "Border"
layout: "post"
diff: 提高+/省选-
pid: CF1010C
tag: ['最大公约数 gcd', '进制', '构造']
---

# Border

## 题目描述

Astronaut Natasha arrived on Mars. She knows that the Martians are very poor aliens. To ensure a better life for the Mars citizens, their emperor decided to take tax from every tourist who visited the planet. Natasha is the inhabitant of Earth, therefore she had to pay the tax to enter the territory of Mars.

There are $ n $ banknote denominations on Mars: the value of $ i $ -th banknote is $ a_i $ . Natasha has an infinite number of banknotes of each denomination.

Martians have $ k $ fingers on their hands, so they use a number system with base $ k $ . In addition, the Martians consider the digit $ d $ (in the number system with base $ k $ ) divine. Thus, if the last digit in Natasha's tax amount written in the number system with the base $ k $ is $ d $ , the Martians will be happy. Unfortunately, Natasha does not know the Martians' divine digit yet.

Determine for which values $ d $ Natasha can make the Martians happy.

Natasha can use only her banknotes. Martians don't give her change.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100\,000 $ , $ 2 \le k \le 100\,000 $ ) — the number of denominations of banknotes and the base of the number system on Mars.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — denominations of banknotes on Mars.

All numbers are given in decimal notation.

## 输出格式

On the first line output the number of values $ d $ for which Natasha can make the Martians happy.

In the second line, output all these values in increasing order.

Print all numbers in decimal notation.

## 说明/提示

Consider the first test case. It uses the octal number system.

If you take one banknote with the value of $ 12 $ , you will get $ 14_8 $ in octal system. The last digit is $ 4_8 $ .

If you take one banknote with the value of $ 12 $ and one banknote with the value of $ 20 $ , the total value will be $ 32 $ . In the octal system, it is $ 40_8 $ . The last digit is $ 0_8 $ .

If you take two banknotes with the value of $ 20 $ , the total value will be $ 40 $ , this is $ 50_8 $ in the octal system. The last digit is $ 0_8 $ .

No other digits other than $ 0_8 $ and $ 4_8 $ can be obtained. Digits $ 0_8 $ and $ 4_8 $ could also be obtained in other ways.

The second test case uses the decimal number system. The nominals of all banknotes end with zero, so Natasha can give the Martians only the amount whose decimal notation also ends with zero.

## 样例 #1

### 输入

```
2 8
12 20

```

### 输出

```
2
0 4 
```

## 样例 #2

### 输入

```
3 10
10 20 30

```

### 输出

```
1
0 
```



---

---
title: "Tonya and Burenka-179"
layout: "post"
diff: 提高+/省选-
pid: CF1718C
tag: ['数学', '最大公约数 gcd']
---

# Tonya and Burenka-179

## 题目描述

Tonya 收到了一个长度为 $ n $ 的数列，写在了他的生日卡片上。出于某种原因，这个卡片原来是一个循环数组，所以严格位于第 $n$ 个元素右侧的元素的下标是 $ 1 $ 。Tonya 想更好地研究它，所以他买了一个机器人 `Burenka-179`。

Burenka 的程序是一个数对 $ (s, k) $ ，其中 $ 1 \leq s \leq n $ ， $ 1 \leq k \leq n-1 $ 。请注意，$k$ 不能等于 $n$。最初，Tonya 将机器人放在数组 $ s $ 的位置。之后，Burenka 在数组中准确地向前或者向后走了 $ n $ 步。如果在开始的时候，Burenka 站在 $i$ 的位置，那么会发生以下情况：

1. 数字$a_{i}$被加入到了到程序的有用值中。
2. Burenka 向右移动了 $k$ 步（ 一般情况下 $ i := i + k $ ，如果 $ i $ 变得大于 $ n $ ，则 $ i := i - n $ ）。

如果任何程序的初始有用值为 $ 0 $ ，则帮助 Tonya 算出程序最大可能的有用值。

此外，Tonya 的朋友 Ilyusha 要求他更改数组 $ q $ 次。每次他想为给定下标 $ p $ 和值 $ x $ 分配 $ a_p := x $ 。在每次进行这些更改之后，你得再次算出程序的最大可能有用值。

## 输入格式

第一行包含单个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) 是测试用例的数量。测试用例的描述如下。

每个测试用例的第一行包含两个整数 $ n $ 和 $ q $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 0 \le q \le 2 \cdot 10^5 $ )。

每个测试用例的第二行包含 $ n $ 个整数， $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — 数组的元素。

以下 $ q $ 行每行代表了更改操作，每行包含两个整数 $ p $ 和 $ x $ ( $ 1 \leq p \leq n $ , $ 1 \leq x \leq 10^9 $ )，意味着你应该分配$ a_p := x $ 。

保证所有测试用例的 $ n $ 和 $ q $ 的总和不超过 $ 2 \cdot 10^5 $ 。

## 输出格式

对于每个测试用例，输出 $ q+1 $ 个数字——程序最初和每次更改后的最大有用值。

## 说明/提示

在第一个测试用例中，最初时和更改后时，可以在 $ s = 1 $ 、 $ k = 1 $ 或 $ s = 2 $ 、 $ k = 1 $ 处找到答案。

在第二个测试用例中，最初，当 $ s = 1 $ , $ k = 2 $ 或 $ s = 3 $ , $ k = 2 $ 时得到答案。在第一次更改之后，在 $ s = 2 $ , $ k = 2 $ 或 $ s = 4 $ , $ k = 2 $ 处找到答案。

## 样例 #1

### 输入

```
4
2 1
1 2
1 3
4 4
4 1 3 2
2 6
4 6
1 1
3 11
9 3
1 7 9 4 5 2 3 6 8
3 1
2 1
9 1
6 3
1 1 1 1 1 1
1 5
4 4
3 8
```

### 输出

```
3
5
14
16
24
24
24
57
54
36
36
6
18
27
28
```



---

---
title: "Josuke and Complete Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1780E
tag: ['数论', '最大公约数 gcd']
---

# Josuke and Complete Graph

## 题目描述

Josuke 收到了一个巨大的无向带权完全图 $G$ 作为他祖父的礼物。该图形包含$10^{18}$ 个顶点。

这个礼物的特点是不同顶点 $u$ 和 $v$ 之间的边的权重等于 $\gcd(u,v)$ 。

Josuke 决定制作一个新的图 $G'$。为此，他选择两个整数 $l\le r$ ，并删除除 $l\le v\le r$ 的顶点 $v$ 之外的所有顶点以及与其相连的边。

现在 Josuke 想知道 $G'$ 中有的边多少种不同的权重。

## 输入格式

第 $1$ 行一个整数 $t\;(1\le t\le100)$ ，表示数据组数。

接下来 $t$ 行每行两个整数 $l,r\;(1\le l\le r\le10^{18},l\le10^9\;)$ ，表示一组数据中的 $l,r$ 。

## 输出格式

每行一个整数，表示每组数据 $G'$ 中不同权重的边的数量。

Translated by @[w9095](https://www.luogu.com.cn/user/569235)

## 样例 #1

### 输入

```
7
2 4
16 24
2 6
1 10
3 3
2562 2568
125 100090
```

### 输出

```
2
6
3
5
0
5
50045
```



---

---
title: "Three Chairs"
layout: "post"
diff: 提高+/省选-
pid: CF1780F
tag: ['最大公约数 gcd', '莫比乌斯反演', '前缀和']
---

# Three Chairs

## 题目描述

One day Kira found $ n $ friends from Morioh and decided to gather them around a table to have a peaceful conversation. The height of friend $ i $ is equal to $ a_i $ . It so happened that the height of each of the friends is unique.

Unfortunately, there were only $ 3 $ chairs in Kira's house, and obviously, it will not be possible to seat all friends! So, Kira has to invite only $ 3 $ of his friends.

But everything is not so simple! If the heights of the lowest and the tallest of the invited friends are not coprime, then the friends will play tricks on each other, which will greatly anger Kira.

Kira became interested, how many ways are there to choose $ 3 $ of his friends so that they don't play tricks? Two ways are considered different if there is a friend invited in one way, but not in the other.

Formally, if Kira invites friends $ i $ , $ j $ , and $ k $ , then the following should be true: $ \gcd(\min(a_i, a_j, a_k), \max(a_i, a_j, a_k)) = 1 $ , where $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the numbers $ x $ and $ y $ .

Kira is not very strong in computer science, so he asks you to count the number of ways to invide friends.

## 输入格式

The first line contains the number $ n $ ( $ 3 \le n \le 3\cdot10^5 $ ) — the number of Kira's friends.

The next line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 3\cdot10^5 $ ) — heights of Kira's friends.

## 输出格式

In a single line output the number of ways to invite three friends.

## 说明/提示

In the first example, only one way is suitable: invite friends $ 1 $ , $ 2 $ , and $ 3 $ . Here $ 1 < 2 < 3 $ , and the numbers $ 1 $ and $ 3 $ are coprime.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
1 6 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
16 4 8 2
```

### 输出

```
0
```

## 样例 #4

### 输入

```
10
10 1 6 7 9 8 4 3 5 2
```

### 输出

```
77
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
title: "Longest Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF632D
tag: ['最大公约数 gcd', '概率论']
---

# Longest Subsequence

## 题目描述

You are given array $ a $ with $ n $ elements and the number $ m $ . Consider some subsequence of $ a $ and the value of least common multiple (LCM) of its elements. Denote LCM as $ l $ . Find any longest subsequence of $ a $ with the value $ l<=m $ .

A subsequence of $ a $ is an array we can get by erasing some elements of $ a $ . It is allowed to erase zero or all elements.

The LCM of an empty array equals $ 1 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{6} $ ) — the size of the array $ a $ and the parameter from the problem statement.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of $ a $ .

## 输出格式

In the first line print two integers $ l $ and $ k_{max} $ ( $ 1<=l<=m,0<=k_{max}<=n $ ) — the value of LCM and the number of elements in optimal subsequence.

In the second line print $ k_{max} $ integers — the positions of the elements from the optimal subsequence in the ascending order.

Note that you can find and print any subsequence with the maximum length.

## 样例 #1

### 输入

```
7 8
6 2 9 2 7 2 3

```

### 输出

```
6 5
1 2 4 6 7

```

## 样例 #2

### 输入

```
6 4
2 2 2 3 3 3

```

### 输出

```
2 3
1 2 3

```



---

