---
title: "Difference of GCDs"
layout: "post"
diff: 普及/提高-
pid: CF1708B
tag: ['数论', '构造']
---

# Difference of GCDs

## 题目描述

You are given three integers $ n $ , $ l $ , and $ r $ . You need to construct an array $ a_1,a_2,\dots,a_n $ ( $ l\le a_i\le r $ ) such that $ \gcd(i,a_i) $ are all distinct or report there's no solution.

Here $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line contains three integers $ n $ , $ l $ , $ r $ ( $ 1 \le n \le 10^5 $ , $ 1\le l\le r\le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, if there is no solution, print "NO" (without quotes). You can print letters in any case (upper or lower).

Otherwise, print "YES" (without quotes). In the next line, print $ n $ integers $ a_1,a_2,\ldots,a_n $ — the array you construct.

If there are multiple solutions, you may output any.

## 说明/提示

In the first test case, $ \gcd(1,a_1),\gcd(2,a_2),\ldots,\gcd(5,a_5) $ are equal to $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , respectively.

## 样例 #1

### 输入

```
4
5 1 5
9 1000 2000
10 30 35
1 1000000000 1000000000
```

### 输出

```
YES
1 2 3 4 5
YES
1145 1926 1440 1220 1230 1350 1001 1000 1233
NO
YES
1000000000
```



---

---
title: "Build Permutation"
layout: "post"
diff: 普及/提高-
pid: CF1713C
tag: ['数论']
---

# Build Permutation

## 题目描述

A  $ \mathbf{0} $ -indexed array $ a $ of size $ n $ is called good if for all valid indices $ i $ ( $ 0 \le i \le n-1 $ ), $ a_i + i $ is a perfect square $ ^\dagger $ .

Given an integer $ n $ . Find a permutation $ ^\ddagger $ $ p $ of $ [0,1,2,\ldots,n-1] $ that is good or determine that no such permutation exists.

 $ ^\dagger $ An integer $ x $ is said to be a perfect square if there exists an integer $ y $ such that $ x = y^2 $ .

 $ ^\ddagger $ An array $ b $ is a permutation of an array $ a $ if $ b $ consists of the elements of $ a $ in arbitrary order. For example, $ [4,2,3,4] $ is a permutation of $ [3,2,4,4] $ while $ [1,2,2] $ is not a permutation of $ [1,2,3] $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the permutation $ p $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ distinct integers $ p_0, p_1, \dots, p_{n-1} $ ( $ 0 \le p_i \le n-1 $ ) — the permutation $ p $ — if the answer exists, and $ -1 $ otherwise.

## 说明/提示

In the first test case, we have $ n=3 $ . The array $ p = [1, 0, 2] $ is good since $ 1 + 0 = 1^2 $ , $ 0 + 1 = 1^2 $ , and $ 2 + 2 = 2^2 $

In the second test case, we have $ n=4 $ . The array $ p = [0, 3, 2, 1] $ is good since $ 0 + 0 = 0^2 $ , $ 3 + 1 = 2^2 $ , $ 2+2 = 2^2 $ , and $ 1+3 = 2^2 $ .

## 样例 #1

### 输入

```
3
3
4
7
```

### 输出

```
1 0 2 
0 3 2 1 
1 0 2 6 5 4 3
```



---

---
title: "Add Modulo 10"
layout: "post"
diff: 普及/提高-
pid: CF1714E
tag: ['数论']
---

# Add Modulo 10

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \dots, a_n $

You can apply the following operation an arbitrary number of times:

- select an index $ i $ ( $ 1 \le i \le n $ ) and replace the value of the element $ a_i $ with the value $ a_i + (a_i \bmod 10) $ , where $ a_i \bmod 10 $ is the remainder of the integer dividing $ a_i $ by $ 10 $ .

For a single index (value $ i $ ), this operation can be applied multiple times. If the operation is applied repeatedly to the same index, then the current value of $ a_i $ is taken into account each time. For example, if $ a_i=47 $ then after the first operation we get $ a_i=47+7=54 $ , and after the second operation we get $ a_i=54+4=58 $ .

Check if it is possible to make all array elements equal by applying multiple (possibly zero) operations.

For example, you have an array $ [6, 11] $ .

- Let's apply this operation to the first element of the array. Let's replace $ a_1 = 6 $ with $ a_1 + (a_1 \bmod 10) = 6 + (6 \bmod 10) = 6 + 6 = 12 $ . We get the array $ [12, 11] $ .
- Then apply this operation to the second element of the array. Let's replace $ a_2 = 11 $ with $ a_2 + (a_2 \bmod 10) = 11 + (11 \bmod 10) = 11 + 1 = 12 $ . We get the array $ [12, 12] $ .

Thus, by applying $ 2 $ operations, you can make all elements of an array equal.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. What follows is a description of each test case.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the size of the array.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \le a_i \le 10^9 $ ) — array elements.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case print:

- YES if it is possible to make all array elements equal;
- NO otherwise.

You can print YES and NO in any case (for example, the strings yEs, yes, Yes and YES will be recognized as a positive answer) .

## 说明/提示

The first test case is clarified above.

In the second test case, it is impossible to make all array elements equal.

In the third test case, you need to apply this operation once to all elements equal to $ 5 $ .

In the fourth test case, you need to apply this operation to all elements until they become equal to $ 8 $ .

In the fifth test case, it is impossible to make all array elements equal.

In the sixth test case, you need to apply this operation to all elements until they become equal to $ 102 $ .

## 样例 #1

### 输入

```
10
2
6 11
3
2 18 22
5
5 10 5 10 5
4
1 2 4 8
2
4 5
3
93 96 102
2
40 6
2
50 30
2
22 44
2
1 5
```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
No
Yes
No
```



---

---
title: "Nearly Shortest Repeating Substring"
layout: "post"
diff: 普及/提高-
pid: CF1950E
tag: ['模拟', '数论']
---

# Nearly Shortest Repeating Substring

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin characters. Find the length of the shortest string $ k $ such that several (possibly one) copies of $ k $ can be concatenated together to form a string with the same length as $ s $ and, at most, one different character.

More formally, find the length of the shortest string $ k $ such that $ c = \underbrace{k + \cdots + k}_{x\rm\ \text{times}} $ for some positive integer $ x $ , strings $ s $ and $ c $ has the same length and $ c_i \neq s_i $ for at most one $ i $ (i.e. there exist $ 0 $ or $ 1 $ such positions).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of string $ s $ .

The second line of each test case contains the string $ s $ , consisting of lowercase Latin characters.

The sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, print the length of the shortest string $ k $ satisfying the constraints in the statement.

## 说明/提示

In the first test case, you can select $ k = \texttt{a} $ and $ k+k+k+k = \texttt{aaaa} $ , which only differs from $ s $ in the second position.

In the second test case, you cannot select $ k $ of length one or two. We can have $ k = \texttt{abba} $ , which is equal to $ s $ .

## 样例 #1

### 输入

```
5
4
abaa
4
abba
13
slavicgslavic
8
hshahaha
20
stormflamestornflame
```

### 输出

```
1
4
13
2
10
```



---

---
title: "Earning on Bets"
layout: "post"
diff: 普及/提高-
pid: CF1979C
tag: ['数论']
---

# Earning on Bets

## 题目描述

You have been offered to play a game. In this game, there are $ n $ possible outcomes, and for each of them, you must bet a certain integer amount of coins. In the event that the $ i $ -th outcome turns out to be winning, you will receive back the amount of coins equal to your bet on that outcome, multiplied by $ k_i $ . Note that exactly one of the $ n $ outcomes will be winning.

Your task is to determine how to distribute the coins in such a way that you will come out ahead in the event of any winning outcome. More formally, the total amount of coins you bet on all outcomes must be strictly less than the number of coins received back for each possible winning outcome.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 50 $ ) — the number of outcomes.

The second line of each test case contains $ n $ integers $ k_1,k_2,\ldots,k_n $ ( $ 2 \le k_i \le 20 $ ) — the multiplier for the amount of coins if the $ i $ -th outcome turns out to be winning.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ -1 $ if there is no way to distribute the coins as required. Otherwise, output $ n $ integers $ x_1, x_2,\ldots, x_n $ ( $ 1 \le x_i \le 10^{9} $ ) — your bets on the outcomes.

It can be shown that if a solution exists, there is always a solution that satisfies these constraints.

If there are multiple suitable solutions, output any of them.

## 说明/提示

In the first test case, the coins can be distributed as follows: $ 27 $ coins on the first outcome, $ 41 $ coins on the second outcome, $ 12 $ coins on the third outcome. Then the total amount of coins bet on all outcomes is $ 27 + 41 + 12 = 80 $ coins. If the first outcome turns out to be winning, you will receive back $ 3 \cdot 27 = 81 $ coins, if the second outcome turns out to be winning, you will receive back $ 2 \cdot 41 = 82 $ coins, if the third outcome turns out to be winning, you will receive back $ 7 \cdot 12 = 84 $ coins. All these values are strictly greater than $ 80 $ .

In the second test case, one way is to bet one coin on each of the outcomes.

## 样例 #1

### 输入

```
6
3
3 2 7
2
3 3
5
5 5 5 5 5
6
7 9 3 17 9 13
3
6 3 2
5
9 4 6 8 3
```

### 输出

```
27 41 12 
1 1 
-1
1989 1547 4641 819 1547 1071 
-1
8 18 12 9 24
```



---

---
title: "GCD-sequence"
layout: "post"
diff: 普及/提高-
pid: CF1980D
tag: ['数学', '数论']
---

# GCD-sequence

## 题目描述

最大公约数（GCD）是两个整数 $x$ 和 $y$ 可以整除的最大整数 $z$。例如，$\text{GCD}(36, 48) = 12$，$\text{GCD}(5, 10) = 5$，以及 $\text{GCD}(7,11) = 1$。

Kristina 有一个由正整数组成的数组 $a$，其中有 $n$ 个数。她想要计算相邻两个数的最大公约数，得到一个新数组 $b$，称为最大公约数序列。

因此，最大公约数序列的元素 $b$ 将使用公式 $b_i = \text{GCD}(a_i, a_{i + 1})$ 计算得到 $1 \le i \le n - 1$。

确定是否可以从数组 $a$ 中移除恰好一个数字，使得最大公约数序列 $b$ 是非递减的（即，$b_i \le b_{i+1}$ 始终为真）。

例如，如果 Khristina 有一个数组 $a = [20, 6, 12, 3, 48, 36]$。如果她从中移除 $a_4 = 3$ 并计算 $b$ 的最大公约数序列，她会得到：

+ $b_1 = \text{GCD}(20, 6) = 2$
+ $b_2 = \text{GCD}(6, 12) = 6$ 
+ $b_3 = \text{GCD}(12, 48) = 12$ 
+ $b_4 = \text{GCD}(48, 36) = 12$  

结果得到的最大公约数序列 $b = [2,6,12,12]$ 是非递减的，因为 $b_1 \le b_2 \le b_3 \le b_4$。

## 输入格式

输入数据的第一行包含一个数字 $t$（$1 \le t \le 10^4$）— 测试中的测试用例数量。

接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^5$）— 数组 $a$ 中元素的数量。

每个测试用例的第二行包含恰好 $n$ 个整数 $a_i$（$1 \le a_i \le 10^9$）— 数组 $a$ 的元素。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行：

+ 如果可以移除数组 $a$ 中的恰好一个数字，使得 $b$ 的最大公约数序列是非递减的，则输出 `YES`;
否则输出 `NO`。

你可以以任何形式输出答案（例如，字符串 `yEs`，`yes`，`Yes`，和 `YES` 都将被视为肯定答案）。

## 样例 #1

### 输入

```
12
6
20 6 12 3 48 36
4
12 6 3 4
3
10 12 3
5
32 16 8 4 2
5
100 50 2 10 20
4
2 4 8 1
10
7 4 6 2 4 5 1 4 2 8
7
5 9 6 8 5 9 2
6
11 14 8 12 9 3
9
5 7 3 10 6 3 12 6 3
3
4 2 4
8
1 6 11 12 6 12 3 6
```

### 输出

```
YES
NO
YES
NO
YES
YES
NO
YES
YES
YES
YES
YES
```



---

---
title: "Dora and C++"
layout: "post"
diff: 普及/提高-
pid: CF2007C
tag: ['数论']
---

# Dora and C++

## 题目描述

Dora 刚学了编程语言C++！

但是，她一点也不明白C++的含义。 她认为C++是两种在长度为 $n$ 的数组 $c$ 上的加法操作。Dora 有两个整数 $ a $ 与 $ b $ 。 每一次操作，她可以选择一件事情去做。

- 选择一个整数 $ i $ ，其中 $ 1 \leq i \leq n $ ，然后把 $ c_i $ 加上 $ a $ 。
- 选择一个整数 $ i $ ，其中 $ 1 \leq i \leq n $ ，然后把 $ c_i $ 加上 $ b $ 。

注意，这里 $ a $ 与 $ b $ 是常数，且他们可以相同。

让我们规定一个数组的值域 $ d $ 为 $ \max(d_i) - \min(d_i) $ 。仅举几例：数组 $ [1, 2, 3, 4] $ 的值域是 $ 4 - 1 = 3 $ ，数组 $ [5, 2, 8, 2, 2, 1] $ 的值域是 $ 8 - 1 = 7 $ ， 数组 $ [3, 3, 3] $ 的值域是 $ 3 - 3 = 0 $ 。

经过若干次操作 (可能是 $ 0 $ )， Dora 计算出了新数组的值域。 请你帮助 Dora 最小化其值，但是自从 Dora 爱上了仅凭自己探索，你只需要告诉她最小化后的值。

## 输入格式

每一个测试点有多组数据。第一行包括一个整数 $ t $  $( 1 \leq t \leq 10^4 )$  代表测试数据的组数。

对于每组测试数据，第一行有三个整数 $ n $ , $ a $  $ b $  $( 1 \leq n \leq 10^5 $ , $ 1 \leq a, b \leq 10^9 )$   表示数组 $ c $ 的长度，以及两个常数 $a$  $b$ 的值。

第二行包括 $ n $ 个整数 $ c_1, c_2, \ldots, c_n $ ( $ 1 \leq c_i \leq 10^9 $ ) 代表数组 $ c $ 的初始值。

保证对于全部的数据 $ Σn \leq 10^5 $。

## 输出格式

对与每组测试数据，你需要输出一个整数，表示若干次操作后数组的值域可能到达的最小值。


#### 样例解释

第一组数据中，我们可以将 $ c_1 = 1 $ 加上 $ a = 5 $ 。 数组 $ c $ 将会变为 $ [6, 3, 4, 4] $ ，其值域为 $ 3 $ 。注意，达到正解的方案不唯一。

第二组数据中，我们可以将 $ c_1 = 1 $ 加上 $ a = 2 $ ，然后将 $ c_1 = 加上 $ by $ b = 3 $ 。当然，我们也可以将 $ c_2 = 3 $ 加上 $ b = 3 $ ，之后将 $ c_3 = 4 $ 加上 $ a = 2 $ 。数组 $ c $ 将会变为 $ [6, 6, 6, 6] $ ，其值域为 $ 0 $ .

## 样例 #1

### 输入

```
10
4 5 5
1 3 4 4
4 2 3
1 3 4 6
4 7 7
1 1 2 6
3 15 9
1 9 5
3 18 12
1 4 5
7 27 36
33 13 23 12 35 24 41
10 6 9
15 5 6 9 8 2 12 15 3 8
2 1 1000000000
1 1000000000
6 336718728 709848696
552806726 474775724 15129785 371139304 178408298 13106071
6 335734893 671469786
138885253 70095920 456876775 9345665 214704906 375508929
```

### 输出

```
3
0
3
2
3
5
1
0
17
205359241
```



---

---
title: "Digits"
layout: "post"
diff: 普及/提高-
pid: CF2043B
tag: ['数论']
---

# Digits

## 输入格式

Artem 在黑板上连续写了 $n!$ 次数字 $d$。所以，他得到了数字 $dddddd…ddd$（正好是 $n!$ 个数字)。

现在，他很好奇黑板上写的数字能够被从 $1$ 到 $9$ 的哪些奇数整除。
第一行包含一个整数 $t$ $(1 \le t \le 100)$，表示测试用例的数量。接下来是 $t$ 个测试用例。

每个测试用例由一行组成，包含两个整数 $n$ 和 $d$，$(2 \le n \le 10 ^ 9, 1 \le d \le 9)$。

## 输出格式

对于每个测试用例，按升序输出题目所求的奇数。

by ClV_Csy

## 样例 #1

### 输入

```
3
2 6
7 1
8 5
```

### 输出

```
1 3 
1 3 7 9 
1 3 5 7 9
```



---

---
title: "Maximum modulo equality"
layout: "post"
diff: 普及/提高-
pid: CF2050F
tag: ['数论', 'ST 表']
---

# Maximum modulo equality

## 题目描述

给你一个长度为 $n$ 的数组 $a$ 和 $q$ 次查询。  
每次查询给定两个数 $l$ 和 $r$，求出最大的 $m$ 使得 $a_l \bmod m = a_{l + 1} \bmod m = \dots = a_r \bmod m$，其中 $a \bmod b$ 是 $a$ 除以 $b$ 的余数。  
**特别的，当 $m$ 可能是无限大时，请输出 $0$。**

## 输入格式

第一行输入一个整数 $t(1 \le t \le 10^4)$，表示测试用例数。  
对于每个测试用例：
+ 第一行输入两个整数 $n$ 和 $q(1 \le n, q \le 2 \times 10^5)$，表示数组长度和查询次数。  
+ 第二行输入 $n$ 个整数 $a_i(1 \le a_i \le 10^9)$，表示数组中的元素。  
+ 接下来的 $q$ 行中，每行输入两个整数 $l$ 和 $r(1 \le l \le r \le n)$，表示查询范围。

保证 $\sum n, \sum q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
3
5 5
5 14 2 6 3
4 5
1 4
2 4
3 5
1 1
1 1
7
1 1
3 2
1 7 8
2 3
1 2
```

### 输出

```
3 1 4 1 0 
0 
1 6
```



---

---
title: "Interesting Ratio"
layout: "post"
diff: 普及/提高-
pid: CF2091E
tag: ['数论', '素数判断,质数,筛法']
---

# Interesting Ratio

## 题目描述

最近，Misha 在 IT Campus "NEIMARK" 的夏令营中学习了新课题 —— 欧几里得算法。

当发现 $a \cdot b = \text{lcm}(a, b) \cdot \text{gcd}(a, b)$ 时，他有些惊讶。其中 $\text{gcd}(a, b)$ 是 $a$ 和 $b$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)，而 $\text{lcm}(a, b)$ 是[最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple)。Misha 想到既然 LCM 和 GCD 的乘积存在，或许它们的商也值得研究：$F(a, b) = \frac{\text{lcm}(a, b)}{\text{gcd}(a, b)}$。

例如，他取 $a = 2$ 和 $b = 4$，计算得到 $F(2, 4) = \frac{4}{2} = 2$，结果是一个质数（一个数如果恰好有两个因数则为质数）！现在他认为当 $a < b$ 且 $F(a, b)$ 是质数时，这个比值 $F(a, b)$ 是"有趣的比值"。

由于 Misha 刚接触数论，他需要你帮忙计算 —— 满足 $F(a, b)$ 是"有趣的比值"且 $1 \leq a < b \leq n$ 的不同数对 $(a, b)$ 有多少个？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 10^3$)。接下来是每个测试用例的描述。

每个测试用例单独一行，包含一个整数 $n$ ($2 \leq n \leq 10^7$)。

保证所有测试用例的 $n$ 之和不超过 $10^7$。


## 输出格式

对于每个测试用例，输出满足条件 $1 \leq a < b \leq n$ 的"有趣比值" $F(a, b)$ 的数量。


## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
5
10
34
10007
```

### 输出

```
4
11
49
24317
```



---

---
title: "Petya and His Friends"
layout: "post"
diff: 普及/提高-
pid: CF66D
tag: ['高精度', '数论']
---

# Petya and His Friends

## 题目描述

Little Petya has a birthday soon. Due this wonderful event, Petya's friends decided to give him sweets. The total number of Petya's friends equals to $ n $ .

Let us remind you the definition of the greatest common divisor: $ GCD(a_{1},...,a_{k})=d $ , where $ d $ represents such a maximal positive number that each $ a_{i} $ ( $ 1<=i<=k $ ) is evenly divisible by $ d $ . At that, we assume that all $ a_{i} $ 's are greater than zero.

Knowing that Petya is keen on programming, his friends has agreed beforehand that the $ 1 $ -st friend gives $ a_{1} $ sweets, the $ 2 $ -nd one gives $ a_{2} $ sweets, ..., the $ n $ -th one gives $ a_{n} $ sweets. At the same time, for any $ i $ and $ j $ ( $ 1<=i,j<=n $ ) they want the $ GCD(a_{i},a_{j}) $ not to be equal to $ 1 $ . However, they also want the following condition to be satisfied: $ GCD(a_{1},a_{2},...,a_{n})=1 $ . One more: all the $ a_{i} $ should be distinct.

Help the friends to choose the suitable numbers $ a_{1},...,a_{n} $ .

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=50 $ ).

## 输出格式

If there is no answer, print "-1" without quotes. Otherwise print a set of $ n $ distinct positive numbers $ a_{1},a_{2},...,a_{n} $ . Each line must contain one number. Each number must consist of not more than $ 100 $ digits, and must not contain any leading zeros. If there are several solutions to that problem, print any of them.

Do not forget, please, that all of the following conditions must be true:

- For every $ i $ and $ j $ ( $ 1<=i,j<=n $ ): $ GCD(a_{i},a_{j})≠1 $
- $ GCD(a_{1},a_{2},...,a_{n})=1 $
- For every $ i $ and $ j $ ( $ 1<=i,j<=n,i≠j $ ): $ a_{i}≠a_{j} $

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 样例 #1

### 输入

```
3

```

### 输出

```
99
55
11115

```

## 样例 #2

### 输入

```
4

```

### 输出

```
385
360
792
8360

```



---

