---
title: "Buying Shovels"
layout: "post"
diff: 普及-
pid: CF1360D
tag: ['数学', '数论', '枚举']
---

# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le       100 $ ) — the number of test cases in the input. Then, $ t $ test cases follow, one per line.

Each test case consists of two positive integers $ n $ ( $ 1       \le n \le 10^9 $ ) and $ k $ ( $ 1 \le k \le 10^9 $ ) — the number of shovels and the number of types of packages.

## 输出格式

Print $ t $ answers to the test cases. Each answer is a positive integer — the minimum number of packages.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733
```

### 输出

```
2
8
1
999999733
1
```



---

---
title: "GCD Problem"
layout: "post"
diff: 普及-
pid: CF1617B
tag: ['数论', '最大公约数 gcd']
---

# GCD Problem

## 题目描述

Given a positive integer $ n $ . Find three distinct positive integers $ a $ , $ b $ , $ c $ such that $ a + b + c = n $ and $ \operatorname{gcd}(a, b) = c $ , where $ \operatorname{gcd}(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. Description of the test cases follows.

The first and only line of each test case contains a single integer $ n $ ( $ 10 \le n \le 10^9 $ ).

## 输出格式

For each test case, output three distinct positive integers $ a $ , $ b $ , $ c $ satisfying the requirements. If there are multiple solutions, you can print any. We can show that an answer always exists.

## 说明/提示

In the first test case, $ 6 + 9 + 3 = 18 $ and $ \operatorname{gcd}(6, 9) = 3 $ .

In the second test case, $ 21 + 39 + 3 = 63 $ and $ \operatorname{gcd}(21, 39) = 3 $ .

In the third test case, $ 29 + 43 + 1 = 73 $ and $ \operatorname{gcd}(29, 43) = 1 $ .

## 样例 #1

### 输入

```
6
18
63
73
91
438
122690412
```

### 输出

```
6 9 3
21 39 3
29 43 1
49 35 7
146 219 73
28622 122661788 2
```



---

---
title: "Z mod X = C"
layout: "post"
diff: 普及-
pid: CF1684B
tag: ['数论', '构造']
---

# Z mod X = C

## 题目描述

给定三个整数 $a,b,c$，求三个整数 $x,y,z$，满足

$$x \bmod{y} =a$$
$$y \bmod{z} =b$$
$$z \bmod{x} =c$$

对于给定数据，保证答案存在。

## 输入格式

**本题有多组数据。**

第一行：一个整数 $t$，表示测试数据的组数。

第 $2$ 行至第 $t+1$ 行：每行三个整数 $a,b,c$，含义如上文所述。

## 输出格式

对于每组数据，输出三个整数 $x,y,z$ ($1 \le x, y, z \le 10^{18}$)，含义为上文所述。

如果有多组答案，输出任意一组即可。

## 说明/提示

$1 \le t \le 10^4$

$1 \le a < b < c \le 10^8$

## 样例 #1

### 输入

```
4
1 3 4
127 234 421
2 7 8
59 94 388
```

### 输出

```
12 11 4
1063 234 1484
25 23 8
2221 94 2609
```



---

---
title: "Woeful Permutation"
layout: "post"
diff: 普及-
pid: CF1712B
tag: ['数论']
---

# Woeful Permutation

## 题目描述

I wonder, does the falling rain



Forever yearn for it's disdain?

Effluvium of the Mind



You are given a positive integer $ n $ .

Find any permutation $ p $ of length $ n $ such that the sum $ \operatorname{lcm}(1,p_1) + \operatorname{lcm}(2, p_2) + \ldots + \operatorname{lcm}(n, p_n) $ is as large as possible.

Here $ \operatorname{lcm}(x, y) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ x $ and $ y $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1\,000 $ ). Description of the test cases follows.

The only line for each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print $ n $ integers $ p_1 $ , $ p_2 $ , $ \ldots $ , $ p_n $ — the permutation with the maximum possible value of $ \operatorname{lcm}(1,p_1) + \operatorname{lcm}(2, p_2) + \ldots + \operatorname{lcm}(n, p_n) $ .

If there are multiple answers, print any of them.

## 说明/提示

For $ n = 1 $ , there is only one permutation, so the answer is $ [1] $ .

For $ n = 2 $ , there are two permutations:

- $ [1, 2] $ — the sum is $ \operatorname{lcm}(1,1) + \operatorname{lcm}(2, 2) = 1 + 2 = 3 $ .
- $ [2, 1] $ — the sum is $ \operatorname{lcm}(1,2) + \operatorname{lcm}(2, 1) = 2 + 2 = 4 $ .

## 样例 #1

### 输入

```
2
1
2
```

### 输出

```
1 
2 1
```



---

---
title: "Madoka and Strange Thoughts"
layout: "post"
diff: 普及-
pid: CF1717A
tag: ['数论']
---

# Madoka and Strange Thoughts

## 题目描述

给定一个整数 $n$，求出有多少组满足条件的 $\left ( a, b\right) (1 \le a, b \le n)$，使得 $\frac{\operatorname{lcm}(a, b) }{\gcd(a, b) } \le 3$。

在该题目中，$\gcd(a, b)$ 指的是 $a$ 和 $b$ 的最大公约数，而 $lcm(a, b)$ 指的是 $a$ 和 $b$ 的最小公倍数。

## 输入格式

第一行输入一个整数 $t(1 \le t \le 10^4)$，代表测试数据的组数。

接下来 $t$ 行，每行一个整数 $n(1 \le n \le 10^8)$，代表题目中的整数 $n$。

## 输出格式

对于每个测试数据，输出一个整数，代表满足条件的 $(a, b)$ 的数量。

## 样例 #1

### 输入

```
6
1
2
3
4
5
100000000
```

### 输出

```
1
4
7
10
11
266666666
```



---

---
title: "Mathematical Circus"
layout: "post"
diff: 普及-
pid: CF1719B
tag: ['数论', '构造']
---

# Mathematical Circus

## 题目描述

A new entertainment has appeared in Buryatia — a mathematical circus! The magician shows two numbers to the audience — $ n $ and $ k $ , where $ n $ is even. Next, he takes all the integers from $ 1 $ to $ n $ , and splits them all into pairs $ (a, b) $ (each integer must be in exactly one pair) so that for each pair the integer $ (a + k) \cdot b $ is divisible by $ 4 $ (note that the order of the numbers in the pair matters), or reports that, unfortunately for viewers, such a split is impossible.

Burenka really likes such performances, so she asked her friend Tonya to be a magician, and also gave him the numbers $ n $ and $ k $ .

Tonya is a wolf, and as you know, wolves do not perform in the circus, even in a mathematical one. Therefore, he asks you to help him. Let him know if a suitable splitting into pairs is possible, and if possible, then tell it.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The following is a description of the input data sets.

The single line of each test case contains two integers $ n $ and $ k $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq k \leq 10^9 $ , $ n $ is even) — the number of integers and the number being added $ k $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, first output the string "YES" if there is a split into pairs, and "NO" if there is none.

If there is a split, then in the following $ \frac{n}{2} $ lines output pairs of the split, in each line print $ 2 $ numbers — first the integer $ a $ , then the integer $ b $ .

## 说明/提示

In the first test case, splitting into pairs $ (1, 2) $ and $ (3, 4) $ is suitable, same as splitting into $ (1, 4) $ and $ (3, 2) $ .

In the second test case, $ (1 + 0) \cdot 2 = 1 \cdot (2 + 0) = 2 $ is not divisible by $ 4 $ , so there is no partition.

## 样例 #1

### 输入

```
4
4 1
2 0
12 10
14 11
```

### 输出

```
YES
1 2
3 4
NO
YES
3 4
7 8
11 12
2 1
6 5
10 9
YES
1 2
3 4
5 6
7 8
9 10
11 12
13 14
```



---

---
title: "Doremy's Perfect Math Class"
layout: "post"
diff: 普及-
pid: CF1764B
tag: ['数学', '数论']
---

# Doremy's Perfect Math Class

## 题目描述

"Everybody! Doremy's Perfect Math Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's math class, Doremy is teaching everyone subtraction. Now she gives you a quiz to prove that you are paying attention in class.

You are given a set $ S $ containing positive integers. You may perform the following operation some (possibly zero) number of times:

- choose two integers $ x $ and $ y $ from the set $ S $ such that $ x > y $ and $ x - y $ is not in the set $ S $ .
- add $ x-y $ into the set $ S $ .

You need to tell Doremy the maximum possible number of integers in $ S $ if the operations are performed optimally. It can be proven that this number is finite.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line contains an integer $ n $ ( $ 2 \le n\le 10^5 $ ) — the size of the set $ S $ .

The second line contains $ n $ integers $ a_1,a_2,\dots,a_n $ ( $ 1\le a_1 < a_2 < \cdots < a_n \le 10^9 $ ) — the positive integers in $ S $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, you need to output the maximum possible number of integers in $ S $ . It can be proven that this value is finite.

## 说明/提示

In the first test case, no such $ x $ and $ y $ exist. The maximum possible number of integers in $ S $ is $ 2 $ .

In the second test case,

- $ S=\{5,10,25\} $ at first. You can choose $ x=25 $ , $ y=10 $ , then add $ x-y=15 $ to the set.
- $ S=\{5,10,15,25\} $ now. You can choose $ x=25 $ , $ y=5 $ , then add $ x-y=20 $ to the set.
- $ S=\{5,10,15,20,25\} $ now. You can not perform any operation now.

After performing all operations, the number of integers in $ S $ is $ 5 $ . It can be proven that no other sequence of operations allows $ S $ to contain more than $ 5 $ integers.

## 样例 #1

### 输入

```
2
2
1 2
3
5 10 25
```

### 输出

```
2
5
```



---

---
title: "Chaya Calendar"
layout: "post"
diff: 普及-
pid: CF1932B
tag: ['数论']
---

# Chaya Calendar

## 题目描述

某部落相信启示有 $n$ 个迹象。随着时间的推移，人们发现第 $i$ 个迹象每隔 $a_i$ 年出现一次（在 $a_i$ 年、$2\cdot a_i$ 年、$3\cdot a_i$ 年等）。

根据传说，为了发生启示，这些迹象必须按顺序出现。也就是说，首先他们等待第一个迹象的出现，然后严格在其之后，第二个迹象将出现，依此类推。也就是说，如果第 $i$ 个迹象出现在第 $x$ 年，部落将从第 $(x+1)$ 年开始等待第 $(i+1)$ 个迹象的出现。值得注意的是，**等待后面的迹象发生时，前面的所有迹象都可以多次在出现**。

第 $n$ 个迹象将在哪一年出现，启示将会第一次发生？

## 输入格式

输入的第一行包含一个整数 $t$（$1\le t\le1000$），表示测试数据的数量。然后是每组测试数据的描述。

每组测试数据的第一行包含一个整数 $n$（$1\le n\le100$），表示迹象的数量。

每组测试数据的第二行包含 $n$ 个整数 $a_1,a_2,a_3, \dots,a_n$（$1\le a_i\le10^6$），是对迹象的周期性的描述。

## 输出格式

对于每组测试数据，输出一个整数，表示所有 $n$ 个迹象将出现的年份。

### 样例解释
在示例的第一组输入数据中：

- 在第 $ 3 $ 年发现第一个迹象；
- 在第 $ 4 $ 年发现第二个迹象；
- 在第 $ 8 $ 年发现第三个迹象；
- 在第 $ 10 $ 年发现第四个迹象；
- 在第 $ 18 $ 年发现第五个迹象；
- 在第 $ 36 $ 年发现第六个迹象；
- 可以证明，这是第一次发生“启示”。

## 样例 #1

### 输入

```
4
6
3 2 4 5 9 18
5
1 2 3 4 5
5
1 1 1 1 1
6
50 30 711 200 503 1006
```

### 输出

```
36
5
5
2012
```



---

---
title: "Collatz Conjecture"
layout: "post"
diff: 普及-
pid: CF1982B
tag: ['数论']
---

# Collatz Conjecture

## 题目描述

Recently, the first-year student Maxim learned about the Collatz conjecture, but he didn't pay much attention during the lecture, so he believes that the following process is mentioned in the conjecture:

There is a variable $ x $ and a constant $ y $ . The following operation is performed $ k $ times:

- increase $ x $ by $ 1 $ , then
- while the number $ x $ is divisible by $ y $ , divide it by $ y $ .

 Note that both of these actions are performed sequentially within one operation.For example, if the number $ x = 16 $ , $ y = 3 $ , and $ k = 2 $ , then after one operation $ x $ becomes $ 17 $ , and after another operation $ x $ becomes $ 2 $ , because after adding one, $ x = 18 $ is divisible by $ 3 $ twice.

Given the initial values of $ x $ , $ y $ , and $ k $ , Maxim wants to know what is the final value of $ x $ .

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. Then follows the description of the test cases.

The only line of each test case contains three integers $ x $ , $ y $ , and $ k $ ( $ 1 \le x, k \le 10^{9} $ , $ 2 \le y \le 10^{9} $ ) — the initial variable, constant and the number of operations.

## 输出格式

For each test case, output a single integer — the number obtained after applying $ k $ operations.

## 说明/提示

In the first test case, there is only one operation applied to $ x = 1 $ , resulting in $ x $ becoming $ 2 $ .

In the second test case, for $ x = 2 $ , within one operation, one is added to $ x $ and it's divided by $ y = 3 $ , resulting in $ x $ becoming $ 1 $ .

In the third test case, $ x $ changes as follows:

- After the first operation, $ x = 1 $ , because $ 24 + 1 = 25 $ and $ 25 $ is divisible by $ y = 5 $ twice within one operation.
- After the second operation, $ x = 2 $ .
- After the third operation, $ x = 3 $ .
- After the fourth operation, $ x = 4 $ .
- After the fifth operation, $ x = 1 $ .

## 样例 #1

### 输入

```
13
1 3 1
2 3 1
24 5 5
16 3 2
2 2 1
1337 18 1
1 2 144133
12345678 3 10
998244353 2 998244353
998244353 123456789 998244352
998244354 998241111 998244352
998244355 2 9982443
1000000000 1000000000 1000000000
```

### 输出

```
2
1
1
2
3
1338
1
16936
1
21180097
6486
1
2
```



---

---
title: "Dora's Set"
layout: "post"
diff: 普及-
pid: CF2007A
tag: ['贪心', '数论']
---

# Dora's Set

## 题目描述

Dora 有一个整数集合 $s$。在最开始，她会将所有满足 $l\le x\le r$ 的整数 $x$ 放入 $s$ 中。然后她允许你进行如下操作：
- 首先，在 $s$ 中选择三个不同的整数 $a,b,c$，并且需要确保它们满足 $\gcd(a,b)=\gcd(b,c)=\gcd(a,c)=1$。
- 然后，将这三个整数从 $s$ 中删除。

其中 $\gcd(x,y)$ 是整数 $x$ 与 $y$ 的[最大公因数](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

你最多能进行多少次操作呢？

## 输入格式

**每个测试点有多组数据。**

第一行有一个正整数 $t$，表示数据的组数。

## 输出格式

对于每组数据，输出一个整数，代表你所能进行的最大操作次数。

### 样例解释翻译

在第一组数据中，你只能进行一次操作，且这次操作中只能选择 $a=1,b=2,c=3$，因为 $\gcd(1,2)=\gcd(2,3)=\gcd(1,3)=1$，然后集合中就没有整数了，所以你不能再进行操作了。

在第二组数据中，你只能选择 $a=3,b=5,c=7$ 进行一次操作。

在第三组数据中，你可以选择 $a=11,b=19,c=20$ 进行第一次操作，选择 $a=13,b=14,c=15$ 进行第二次操作，选择 $a=10,b=17,c=21$ 进行第三次操作。在三次操作后，集合 $s$ 中剩余 $12,16,18$ 这三个整数。可以证明你最多只能进行 $3$ 次操作。

## 样例 #1

### 输入

```
8
1 3
3 7
10 21
2 8
51 60
2 15
10 26
1 1000
```

### 输出

```
1
1
3
1
2
3
4
250
```



---

---
title: "Robin Hood and the Major Oak"
layout: "post"
diff: 普及-
pid: CF2014B
tag: ['数学', '数论']
---

# Robin Hood and the Major Oak

## 题目描述

在 Sherwood（原文地名）里，树木是我们的庇护所，我们都是森林的孩子。

Sherwood 中的 Major Oak（原文物品名称）以它宏伟的树叶而闻名，这些树叶为 Robin Hood（原文人名）和他的快乐男男女女们提供了庇护。

Major Oak 在 $i$ 年长出 $i^i$ 片新叶子。它从第一年开始就有 $1$ 片叶子。

树叶在树上最多能持续 $k$ 年。换句话说，第 $i$ 年长出的树叶可以持续到第 $i$ 年到第 $i+k-1$ 年。

这段文本的意思是：Robin 认为偶数是幸运的。请帮助 Robin 确定 Major Oak 在第 $n$ 年是否有偶数片叶子。

## 输入格式

输入的第一行包含一个整数 $t$（$1\le t\le 10^4$）——测试用例的数量。

每个测试用例包含两个整数 $n$，$k$（$1\le n\le 10^9$，$1\le k\le n$）——请求的年份和叶子保持的时间长度。

## 输出格式

对于每个测试用例，输出一行，如果年份 $n$ 时，Major Oak 的叶子数量为偶数，则输出 `YES`；否则输出 `NO`。

你可以以任何大小写形式输出答案。例如，字符串 `yEs`、`yes`、`Yes` 和 `YES` 将被识别为肯定回答。

## 说明/提示

在第一个测试用例中，只有 $ 1 $ 片叶子。

在第二个测试用例中，$ k=1 $ ，所以第 $ 2 $ 年会有 $ 2^2=4 $ 片叶子。

在第三个测试用例中，$ k=2 $ ，所以第 $ 2 $ 年会有 $ 1+2^2=5 $ 片叶子。

在第四个测试用例中，$ k=2 $ ，所以第 $ 3 $ 年会有 $ 2^2 + 3^3 = 4 + 27 = 31 $ 片叶子。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
5
1 1
2 1
2 2
3 2
4 4
```

### 输出

```
NO
YES
NO
NO
YES
```



---

---
title: "Everyone Loves Tres"
layout: "post"
diff: 普及-
pid: CF2035B
tag: ['数论', '构造']
---

# Everyone Loves Tres

## 题目描述

There are 3 heroes and 3 villains, so 6 people in total.



Given a positive integer $ n $ . Find the smallest integer whose decimal representation has length $ n $ and consists only of $ 3 $ s and $ 6 $ s such that it is divisible by both $ 33 $ and $ 66 $ . If no such integer exists, print $ -1 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 500 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 1\le n\le 500 $ ) — the length of the decimal representation.

## 输出格式

For each test case, output the smallest required integer if such an integer exists and $ -1 $ otherwise.

## 说明/提示

For $ n=1 $ , no such integer exists as neither $ 3 $ nor $ 6 $ is divisible by $ 33 $ .

For $ n=2 $ , $ 66 $ consists only of $ 6 $ s and it is divisible by both $ 33 $ and $ 66 $ .

For $ n=3 $ , no such integer exists. Only $ 363 $ is divisible by $ 33 $ , but it is not divisible by $ 66 $ .

For $ n=4 $ , $ 3366 $ and $ 6666 $ are divisible by both $ 33 $ and $ 66 $ , and $ 3366 $ is the smallest.

## 样例 #1

### 输入

```
6
1
2
3
4
5
7
```

### 输出

```
-1
66
-1
3366
36366
3336366
```



---

---
title: "Superultra's Favorite Permutation"
layout: "post"
diff: 普及-
pid: CF2037C
tag: ['数学', '数论']
---

# Superultra's Favorite Permutation

## 题目描述

Superultra, a little red panda, desperately wants primogems. In his dreams, a voice tells him that he must solve the following task to obtain a lifetime supply of primogems. Help Superultra!

Construct a permutation $ ^{\text{∗}} $ $ p $ of length $ n $ such that $ p_i + p_{i+1} $ is composite $ ^{\text{†}} $ over all $ 1 \leq i \leq n - 1 $ . If it's not possible, output $ -1 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^{\text{†}} $ An integer $ x $ is composite if it has at least one other divisor besides $ 1 $ and $ x $ . For example, $ 4 $ is composite because $ 2 $ is a divisor.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if it's not possible to construct $ p $ , output $ -1 $ on a new line. Otherwise, output $ n $ integers $ p_1, p_2, \ldots, p_n $ on a new line.

## 说明/提示

In the first example, it can be shown that all permutation of size $ 3 $ contain two adjacent elements whose sum is prime. For example, in the permutation $ [2,3,1] $ the sum $ 2+3=5 $ is prime.

In the second example, we can verify that the sample output is correct because $ 1+8 $ , $ 8+7 $ , $ 7+3 $ , $ 3+6 $ , $ 6+2 $ , $ 2+4 $ , and $ 4+5 $ are all composite. There may be other constructions that are correct.

## 样例 #1

### 输入

```
2
3
8
```

### 输出

```
-1
1 8 7 3 6 2 4 5
```



---

---
title: "Shohag Loves Mod"
layout: "post"
diff: 普及-
pid: CF2039A
tag: ['数论', '构造']
---

# Shohag Loves Mod

## 题目描述

Shohag 有一个整数 $n$，请帮助他找到一个升序序列 $1\le a_1< a_2<\cdots<a_n\le100$，使得对于所有满足 $1\le i < j \le n$ 的数对 $(i,j)$，都满足 $a_i \bmod i\neq a_j \bmod j$。

可以证明，在给定限制下，一定存在合法的序列。

$a\bmod b$ 表示 $a$ 除以 $b$ 的余数。比如，$7\bmod 3=1, 8\bmod 4=0, 69\bmod 10=9$。

## 输入格式

第一行，一个整数 $t$（$1\le t\le 50$） 表示数据组数。

对于每组数据，输入一行，一个整数 $n$（$2\le n\le 50$）。

## 输出格式

对于每组数据，输出 $n$ 个整数，表示符合题目条件的一个序列。如果有多个符合条件的序列，输出任意一个即可。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
2
3
6
```

### 输出

```
2 7 8
2 3 32 35 69 95
```



---

---
title: "Game of Division"
layout: "post"
diff: 普及-
pid: CF2040A
tag: ['数论']
---

# Game of Division

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ and an integer $ k $ .

Two players are playing a game. The first player chooses an index $ 1 \le i \le n $ . Then the second player chooses a different index $ 1 \le j \le n, i \neq j $ . The first player wins if $ |a_i - a_j| $ is not divisible by $ k $ . Otherwise, the second player wins.

We play as the first player. Determine whether it is possible to win, and if so, which index $ i $ should be chosen.

The absolute value of a number $ x $ is denoted by $ |x| $ and is equal to $ x $ if $ x \ge 0 $ , and $ -x $ otherwise.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100 $ ; $ 1 \le k \le 100 $ ) — the length of the array and the number $ k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 100 $ ) — the elements of the array $ a $ .

## 输出格式

For each test case, if it is impossible for the first player to win, print "NO" (without quotes).

Otherwise, print "YES" (without quotes) and on the next line the appropriate index $ 1 \le i \le n $ . If there are multiple solutions, print any of them.

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer.

## 说明/提示

In the first test case, the first player can choose $ a_2 = 2 $ . Then:

- If the second player chooses $ a_1 = 1 $ , the resulting difference is $ |2 - 1| = 1 $ which is not divisible by $ k = 2 $ .
- If the second player chooses $ a_3 = 3 $ , the resulting difference is $ |2 - 3| = 1 $ which is not divisible by $ k = 2 $ .

In the second test case:

- If the first player chooses $ a_1 = 1 $ and then the second player chooses $ a_4 = 5 $ , the resulting difference is $ |1 - 5| = 4 $ which is divisible by $ k = 2 $ .
- If the first player chooses $ a_2 = 2 $ and then the second player chooses $ a_3 = 4 $ , the resulting difference is $ |2 - 4| = 2 $ which is divisible by $ k = 2 $ .
- If the first player chooses $ a_3 = 4 $ and then the second player chooses $ a_2 = 2 $ , the resulting difference is $ |4 - 2| = 2 $ which is divisible by $ k = 2 $ .
- If the first player chooses $ a_4 = 5 $ and then the second player chooses $ a_1 = 1 $ , the resulting difference is $ |5 - 1| = 4 $ which is divisible by $ k = 2 $ .

 In any case, the second player wins.

## 样例 #1

### 输入

```
7
3 2
1 2 3
4 2
1 2 4 5
5 3
10 7 3 4 5
5 3
1 31 15 55 36
2 1
17 17
2 2
17 18
1 3
6
```

### 输出

```
YES
2
NO
YES
3
NO
NO
YES
2
YES
1
```



---

---
title: "Kevin and Combination Lock"
layout: "post"
diff: 普及-
pid: CF2048A
tag: ['数论']
---

# Kevin and Combination Lock

## 题目描述

Kevin is trapped in Lakeside Village by Grace. At the exit of the village, there is a combination lock that can only be unlocked if Kevin solves it.

The combination lock starts with an integer $  x  $ . Kevin can perform one of the following two operations zero or more times:

1. If $  x \neq 33  $ , he can select two consecutive digits $  3  $ from $  x  $ and remove them simultaneously. For example, if $  x = 13\,323  $ , he can remove the second and third $  3  $ , changing $  x  $ to $  123  $ .
2. If $  x \geq 33  $ , he can change $  x  $ to $  x - 33  $ . For example, if $  x = 99  $ , he can choose this operation to change $  x  $ to $  99 - 33 = 66  $ .

When the value of $  x  $ on the combination lock becomes $  0  $ , Kevin can unlock the lock and escape from Lakeside Village. Please determine whether it is possible for Kevin to unlock the combination lock and escape.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ).

The only line of each test case contains a positive integer $ x $ ( $ 1\leq x\leq 10^9 $ ).

## 输出格式

For each test case, output "YES" or "NO" (without quotes) in one line, representing whether Kevin can unlock the combination lock and escape. You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

For the first test case, $ 165\xrightarrow{-33}132\xrightarrow{-33}99\xrightarrow{-33}66\xrightarrow{-33}33\xrightarrow{-33}0 $ .

For the second test case, $ 6369\xrightarrow{-33}6{\color{red}{33}}6\xrightarrow{\text{remove "33"}}66\xrightarrow{-33}33\xrightarrow{-33}0 $ .

For the third test case, it can be proven that, regardless of the operations performed, $ 666 $ cannot be transformed into $ 0 $ .

## 样例 #1

### 输入

```
5
165
6369
666
114514
133333332
```

### 输出

```
YES
YES
NO
NO
YES
```



---

---
title: "Lucky Permutation Triple"
layout: "post"
diff: 普及-
pid: CF303A
tag: ['数学', '数论']
---

# Lucky Permutation Triple

## 题目描述

Bike is interested in permutations. A permutation of length $ n $ is an integer sequence such that each integer from 0 to $ (n-1) $ appears exactly once in it. For example, $ [0,2,1] $ is a permutation of length 3 while both $ [0,2,2] $ and $ [1,2,3] $ is not.

A permutation triple of permutations of length $ n $ $ (a,b,c) $ is called a Lucky Permutation Triple if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/bd0aa9c2cfa6e7dfc9681d8813c19703f16dbc42.png). The sign $ a_{i} $ denotes the $ i $ -th element of permutation $ a $ . The modular equality described above denotes that the remainders after dividing $ a_{i}+b_{i} $ by $ n $ and dividing $ c_{i} $ by $ n $ are equal.

Now, he has an integer $ n $ and wants to find a Lucky Permutation Triple. Could you please help him?

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{5}) $ .

## 输出格式

If no Lucky Permutation Triple of length $ n $ exists print -1.

Otherwise, you need to print three lines. Each line contains $ n $ space-seperated integers. The first line must contain permutation $ a $ , the second line — permutation $ b $ , the third — permutation $ c $ .

If there are multiple solutions, print any of them.

## 说明/提示

In Sample 1, the permutation triple $ ([1,4,3,2,0],[1,0,2,4,3],[2,4,0,1,3]) $ is Lucky Permutation Triple, as following holds:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/6124807a627fcd49ae8fab0d91c9fa90239af12b.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/598c5f3180986ca384de6df51e7cb84d8ea4e757.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/66b44a153ea212b6a13d195278ac6715ce383457.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/dd4f61ae15bc4151613d0da9fe47b466aa949e1e.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/0ea0fc069d3b3e3451d396fd4b6ef6f3d9456398.png).

In Sample 2, you can easily notice that no lucky permutation triple exists.

## 样例 #1

### 输入

```
5

```

### 输出

```
1 4 3 2 0
1 0 2 4 3
2 4 0 1 3

```

## 样例 #2

### 输入

```
2

```

### 输出

```
-1

```



---

---
title: "Vanya and Books"
layout: "post"
diff: 普及-
pid: CF552B
tag: ['数论']
---

# Vanya and Books

## 题目描述

Vanya got an important task — he should enumerate books in the library and label each book with its number. Each of the $ n $ books should be assigned with a number from $ 1 $ to $ n $ . Naturally, distinct books should be assigned distinct numbers.

Vanya wants to know how many digits he will have to write down as he labels the books.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{9} $ ) — the number of books in the library.

## 输出格式

Print the number of digits needed to number all the books.

## 说明/提示

Note to the first test. The books get numbers $ 1,2,3,4,5,6,7,8,9,10,11,12,13 $ , which totals to $ 17 $ digits.

Note to the second sample. The books get numbers $ 1,2,3,4 $ , which totals to 4 digits.

## 样例 #1

### 输入

```
13

```

### 输出

```
17

```

## 样例 #2

### 输入

```
4

```

### 输出

```
4

```



---

