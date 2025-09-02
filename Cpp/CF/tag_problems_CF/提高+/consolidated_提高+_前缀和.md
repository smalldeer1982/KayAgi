---
title: "Vasya and Magic Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF1042E
tag: ['前缀和', '期望', '逆元']
---

# Vasya and Magic Matrix

## 题目描述

Vasya has got a magic matrix $ a $ of size $ n \times m $ . The rows of the matrix are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ m $ from left to right. Let $ a_{ij} $ be the element in the intersection of the $ i $ -th row and the $ j $ -th column.

Vasya has also got a chip. Initially, the chip is in the intersection of the $ r $ -th row and the $ c $ -th column (that is, in the element $ a_{rc} $ ). Vasya performs the following process as long as possible: among all elements of the matrix having their value less than the value of the element with the chip in it, Vasya randomly and equiprobably chooses one element and moves his chip to this element.

After moving the chip, he adds to his score the square of the Euclidean distance between these elements (that is, between the element in which the chip is now and the element the chip was moved from). The process ends when there are no elements having their values less than the value of the element with the chip in it.

Euclidean distance between matrix elements with coordinates $ (i_1, j_1) $ and $ (i_2, j_2) $ is equal to $ \sqrt{(i_1-i_2)^2 + (j_1-j_2)^2} $ .

Calculate the expected value of the Vasya's final score.

It can be shown that the answer can be represented as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime integer numbers, and $ Q \not\equiv 0~(mod ~ 998244353) $ . Print the value $ P \cdot Q^{-1} $ modulo $ 998244353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ $ (1 \le n, m \le 1\,000) $ — the number of rows and the number of columns in the matrix $ a $ .

The following $ n $ lines contain description of the matrix $ a $ . The $ i $ -th line contains $ m $ integers $ a_{i1}, a_{i2}, \dots, a_{im} ~ (0 \le a_{ij} \le 10^9) $ .

The following line contains two integers $ r $ and $ c $ $ (1 \le r \le n, 1 \le c \le m) $ — the index of row and the index of column where the chip is now.

## 输出格式

Print the expected value of Vasya's final score in the format described in the problem statement.

## 说明/提示

In the first example, Vasya will move his chip exactly once. The expected value of the final score is equal to $ \frac{1^2 + 2^2+ 1^2}{3} = 2 $ .

## 样例 #1

### 输入

```
1 4
1 1 2 1
1 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 3
1 5 7
2 3 1
1 2

```

### 输出

```
665496238

```



---

---
title: "Binary Numbers AND Sum"
layout: "post"
diff: 提高+/省选-
pid: CF1066E
tag: ['模拟', '进制', '前缀和']
---

# Binary Numbers AND Sum

## 题目描述

## 题目大意



现在，给你两个位数为 $n$ 和 $m$ 的两个二进制数$a$,$b$，现在，我们要进行如下操作：



* 计算$a$&$b$

* 答案累加上一个操作的值

* $b$右移一位，最后一位直接舍弃



现在,请你算出最终的答案，并输出，答案对998244353取模

## 输入格式

第一行，两个整数$n$,$m$,$(1≤n,m≤2 \times 10^5)$



第一行，一个长度为$n$的二进制数$a$



第一行，一个长度为$m$的二进制数$b$

## 输出格式

一行，一个数，表示答案

## 样例 #1

### 输入

```
4 4
1010
1101

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4 5
1001
10101

```

### 输出

```
11

```



---

---
title: "Yet Another Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1747D
tag: ['数学', '贪心', '前缀和']
---

# Yet Another Problem

## 题目描述

You are given an array $ a $ of $ n $ integers $ a_1, a_2, a_3, \ldots, a_n $ .

You have to answer $ q $ independent queries, each consisting of two integers $ l $ and $ r $ .

- Consider the subarray $ a[l:r] $ $ = $ $ [a_l, a_{l+1}, \ldots, a_r] $ . You can apply the following operation to the subarray any number of times (possibly zero)- 
  1. Choose two integers $ L $ , $ R $ such that $ l \le L \le R \le r $ and $ R - L + 1 $ is odd.
  2. Replace each element in the subarray from $ L $ to $ R $ with the XOR of the elements in the subarray $ [L, R] $ .
- The answer to the query is the minimum number of operations required to make all elements of the subarray $ a[l:r] $ equal to $ 0 $ or $ -1 $ if it is impossible to make all of them equal to $ 0 $ .

You can find more details about XOR operation [here](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 输入格式

The first line contains two integers $ n $ and $ q $ $ (1 \le n, q \le 2 \cdot 10^5) $ — the length of the array $ a $ and the number of queries.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ $ (0 \le a_i \lt 2^{30}) $ — the elements of the array $ a $ .

The $ i $ -th of the next $ q $ lines contains two integers $ l_i $ and $ r_i $ $ (1 \le l_i \le r_i \le n) $ — the description of the $ i $ -th query.

## 输出格式

For each query, output a single integer — the answer to that query.

## 说明/提示

In the first query, $ l = 3, r = 4 $ , subarray = $ [3, 3] $ . We can apply operation only to the subarrays of length $ 1 $ , which won't change the array; hence it is impossible to make all elements equal to $ 0 $ .

In the second query, $ l = 4, r = 6 $ , subarray = $ [3, 1, 2] $ . We can choose the whole subarray $ (L = 4, R = 6) $ and replace all elements by their XOR $ (3 \oplus 1 \oplus 2) = 0 $ , making the subarray $ [0, 0, 0] $ .

In the fifth query, $ l = 1, r = 6 $ , subarray = $ [3, 0, 3, 3, 1, 2] $ . We can make the operations as follows:

1. Choose $ L = 4, R = 6 $ , making the subarray $ [3, 0, 3, 0, 0, 0] $ .
2. Choose $ L = 1, R = 5 $ , making the subarray $ [0, 0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7 6
3 0 3 3 1 2 3
3 4
4 6
3 7
5 6
1 6
2 2
```

### 输出

```
-1
1
1
-1
2
0
```



---

---
title: "Decomposition"
layout: "post"
diff: 提高+/省选-
pid: CF1766E
tag: ['动态规划 DP', '前缀和']
---

# Decomposition

## 题目描述

For a sequence of integers $ [x_1, x_2, \dots, x_k] $ , let's define its decomposition as follows:

Process the sequence from the first element to the last one, maintaining the list of its subsequences. When you process the element $ x_i $ , append it to the end of the first subsequence in the list such that the bitwise AND of its last element and $ x_i $ is greater than $ 0 $ . If there is no such subsequence in the list, create a new subsequence with only one element $ x_i $ and append it to the end of the list of subsequences.

For example, let's analyze the decomposition of the sequence $ [1, 3, 2, 0, 1, 3, 2, 1] $ :

- processing element $ 1 $ , the list of subsequences is empty. There is no subsequence to append $ 1 $ to, so we create a new subsequence $ [1] $ ;
- processing element $ 3 $ , the list of subsequences is $ [[1]] $ . Since the bitwise AND of $ 3 $ and $ 1 $ is $ 1 $ , the element is appended to the first subsequence;
- processing element $ 2 $ , the list of subsequences is $ [[1, 3]] $ . Since the bitwise AND of $ 2 $ and $ 3 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 0 $ , the list of subsequences is $ [[1, 3, 2]] $ . There is no subsequence to append $ 0 $ to, so we create a new subsequence $ [0] $ ;
- processing element $ 1 $ , the list of subsequences is $ [[1, 3, 2], [0]] $ . There is no subsequence to append $ 1 $ to, so we create a new subsequence $ [1] $ ;
- processing element $ 3 $ , the list of subsequences is $ [[1, 3, 2], [0], [1]] $ . Since the bitwise AND of $ 3 $ and $ 2 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 2 $ , the list of subsequences is $ [[1, 3, 2, 3], [0], [1]] $ . Since the bitwise AND of $ 2 $ and $ 3 $ is $ 2 $ , the element is appended to the first subsequence;
- processing element $ 1 $ , the list of subsequences is $ [[1, 3, 2, 3, 2], [0], [1]] $ . The element $ 1 $ cannot be appended to any of the first two subsequences, but can be appended to the third one.

The resulting list of subsequences is $ [[1, 3, 2, 3, 2], [0], [1, 1]] $ .

Let $ f([x_1, x_2, \dots, x_k]) $ be the number of subsequences the sequence $ [x_1, x_2, \dots, x_k] $ is decomposed into.

Now, for the problem itself.

You are given a sequence $ [a_1, a_2, \dots, a_n] $ , where each element is an integer from $ 0 $ to $ 3 $ . Let $ a[i..j] $ be the sequence $ [a_i, a_{i+1}, \dots, a_j] $ . You have to calculate $ \sum \limits_{i=1}^n \sum \limits_{j=i}^n f(a[i..j]) $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 3 $ ).

## 输出格式

Print one integer, which should be equal to $ \sum \limits_{i=1}^n \sum \limits_{j=i}^n f(a[i..j]) $ .

## 样例 #1

### 输入

```
8
1 3 2 0 1 3 2 1
```

### 输出

```
71
```

## 样例 #2

### 输入

```
5
0 0 0 0 0
```

### 输出

```
35
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
title: "Game of the Year"
layout: "post"
diff: 提高+/省选-
pid: CF1783E
tag: ['数学', '贪心', '树状数组', '数论', '前缀和', 'ST 表']
---

# Game of the Year

## 题目描述

Monocarp 和 Polycarp 正在玩电脑游戏。游戏特点：$ n $ 个编号从 $ 1 $ 到 $ n $ 的BOSS。

他俩将用以下方式与BOSS战斗

- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- ...

Monocarp 在第 $ a_i $ 次尝试中撒掉了第 $ i $ 只BOSS。Polycarp 在第 $ b_i $ 次尝试中撒掉了第 $ i $ 只BOSS。其中一个人撒掉第 $ i $ 只BOSS后，他们就会尝试撒第 $ (i+1) $ 只BOSS。并且他们的尝试计数器都会清空。撒掉第 $ n $ 只BOSS后，游戏结束。

找到从$ 1 $ 到 $ n $所有的 $ k $ 值， 使得 Monocarp 可以杀死所有的BOSS。

## 输入格式

第一行输入一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) — 样例数。

每个样例第一行输入一个整数 $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — BOSS的数量。

每个样例第二行输入 $ n $ 个整数： $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — Monocarp 撒死每只BOSS的尝试次数。

每个样例第三行输入 $ n $ 个整数： $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ) — Polycarp 撒死每只BOSS的尝试次数。

所有测试样例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ .

## 输出格式

对于每个样例输出两行。第一行应该包含一个正整数 $ \mathit{cnt} $ — 从 $ 1 $ 到 $ n $ 使得 Monocarp 可以撒死所有BOSS的 $ k $ 的总数。第二行应该包含 $ \mathit{cnt} $ 个正整数 — 所有 $ k $ 的值。

## 说明/提示

考虑最后一组测试样例

使 $ k = 1 $。首先，Monocarp经过1次尝试撒死第一只BOSS。成功，因为 $ a_1 = 1 $。 然后，Monocarp进行一次尝试撒死第二只BOSS。不成功，因为 $ a_2 > 1 $。于是，Polycarp尝试了一下。也不成功，因为 $ b_2 > 1 $。然后Monocarp进行了另一次尝试。仍然不成功，因为 $ a_2 > 2 $。直到Polycarp 在第三次尝试撒掉了BOSS。Monocarp没能撒掉BOSS。因此，$ k = 1 $ 不是答案。

使 $ k = 2 $ . Monocarp仍然在他的第一次尝试中撒死了BOSS。然后，他进行了两次不成功的尝试未能撒死BOSS。然后，Polycarp进行了两次不成功的尝试。然后，Monocarp进行了两次尝试，并且在第四次尝试中撒掉了BOSS。撒掉第三只BOSS的方法也类似。首先，Monocarp进行两次不成功的尝试。然后，Polycarp进行两次不成功的尝试。然后，Monocarp还有两次尝试机会，但在这两次机会中第一次就撒死了BOSS，因为 $ a_3 = 3 $。 第四只BOSS也被Monocarp撒死。因此，$ k = 2 $ 是答案。

## 样例 #1

### 输入

```
3
3
1 1 1
2 3 1
1
1
1
4
1 4 3 2
3 3 4 1
```

### 输出

```
3
1 2 3 
1
1 
2
2 4
```



---

---
title: "Wine Factory (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1919F1
tag: ['线段树', '前缀和']
---

# Wine Factory (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ c_i $ and $ z $ . You can make hacks only if both versions of the problem are solved.

There are three arrays $ a $ , $ b $ and $ c $ . $ a $ and $ b $ have length $ n $ and $ c $ has length $ n-1 $ . Let $ W(a,b,c) $ denote the liters of wine created from the following process.

Create $ n $ water towers. The $ i $ -th water tower initially has $ a_i $ liters of water and has a wizard with power $ b_i $ in front of it. Furthermore, for each $ 1 \le i \le n - 1 $ , there is a valve connecting water tower $ i $ to $ i + 1 $ with capacity $ c_i $ .

For each $ i $ from $ 1 $ to $ n $ in this order, the following happens:

1. The wizard in front of water tower $ i $ removes at most $ b_i $ liters of water from the tower and turns the removed water into wine.
2. If $ i \neq n $ , at most $ c_i $ liters of the remaining water left in water tower $ i $ flows through the valve into water tower $ i + 1 $ .

There are $ q $ updates. In each update, you will be given integers $ p $ , $ x $ , $ y $ and $ z $ and you will update $ a_p := x $ , $ b_p := y $ and $ c_p := z $ . After each update, find the value of $ W(a,b,c) $ . Note that previous updates to arrays $ a $ , $ b $ and $ c $ persist throughout future updates.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 5\cdot 10^5 $ , $ 1 \le q \le 5\cdot 10^5 $ ) — the number of water towers and the number of updates.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the number of liters of water in water tower $ i $ .

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \le b_i \le 10^9 $ ) — the power of the wizard in front of water tower $ i $ .

The fourth line contains $ n - 1 $ integers $ c_1, c_2, \ldots, c_{n - 1} $ ( $ c_i \color{red}{=} 10^{18} $ ) — the capacity of the pipe connecting water tower $ i $ to $ i + 1 $ .

Each of the next $ q $ lines contains four integers $ p $ , $ x $ , $ y $ and $ z $ ( $ 1 \le p \le n $ , $ 0 \le x, y \le 10^9 $ , $ z \color{red}{=} 10^{18} $ ) — the updates done to arrays $ a $ , $ b $ and $ c $ .

Note that $ c_n $ does not exist, so the value of $ z $ does not matter when $ p = n $ .

## 输出格式

Print $ q $ lines, each line containing a single integer representing $ W(a, b, c) $ after each update.

## 说明/提示

The first update does not make any modifications to the arrays.

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 5 $ liters of water in tower 2 and $ 4 $ liters of water is turned into wine. The remaining $ 1 $ liter of water flows into tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 2 $ liters of water flows into tower 4.
- When $ i = 4 $ , there are $ 5 $ liters of water in tower 4. All $ 5 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 4 + 2 + 5 = 12 $ after the first update.

The second update modifies the arrays to $ a = [3, 5, 3, 3] $ , $ b = [1, 1, 2, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 9 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 7 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 10 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 2 + 8 = 12 $ after the second update.

The third update modifies the arrays to $ a = [3, 5, 0, 3] $ , $ b = [1, 1, 0, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 6 $ liters of water in tower 3 and $ 0 $ liters of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 9 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 0 + 8 = 10 $ after the third update.

## 样例 #1

### 输入

```
4 3
3 3 3 3
1 4 2 8
1000000000000000000 1000000000000000000 1000000000000000000
4 3 8 1000000000000000000
2 5 1 1000000000000000000
3 0 0 1000000000000000000
```

### 输出

```
12
12
10
```

## 样例 #2

### 输入

```
5 5
10 3 8 9 2
3 4 10 8 1
1000000000000000000 1000000000000000000 1000000000000000000 1000000000000000000
5 4 9 1000000000000000000
1 1 1 1000000000000000000
2 7 4 1000000000000000000
4 1 1 1000000000000000000
1 8 3 1000000000000000000
```

### 输出

```
34
25
29
21
27
```



---

---
title: "Make a Palindrome"
layout: "post"
diff: 提高+/省选-
pid: CF2004F
tag: ['数学', '前缀和']
---

# Make a Palindrome

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

Let the function $ f(b) $ return the minimum number of operations needed to make an array $ b $ a palindrome. The operations you can make are:

- choose two adjacent elements $ b_i $ and $ b_{i+1} $ , remove them, and replace them with a single element equal to $ (b_i + b_{i + 1}) $ ;
- or choose an element $ b_i > 1 $ , remove it, and replace it with two positive integers $ x $ and $ y $ ( $ x > 0 $ and $ y > 0 $ ) such that $ x + y = b_i $ .

For example, from an array $ b=[2, 1, 3] $ , you can obtain the following arrays in one operation: $ [1, 1, 1, 3] $ , $ [2, 1, 1, 2] $ , $ [3, 3] $ , $ [2, 4] $ , or $ [2, 1, 2, 1] $ .

Calculate $ \displaystyle \left(\sum_{1 \le l \le r \le n}{f(a[l..r])}\right) $ , where $ a[l..r] $ is the subarray of $ a $ from index $ l $ to index $ r $ , inclusive. In other words, find the sum of the values of the function $ f $ for all subarrays of the array $ a $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^5 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, print a single integer — the sum of the values of the function $ f $ for all subarrays of the array $ a $ .

## 样例 #1

### 输入

```
4
3
2 1 3
4
1 1 1 1
5
4 2 3 1 5
4
1 2 1 2
```

### 输出

```
3
0
14
5
```



---

---
title: "Hard Demon Problem"
layout: "post"
diff: 提高+/省选-
pid: CF2044H
tag: ['前缀和']
---

# Hard Demon Problem

## 题目描述

Swing 正在筹备他的煎饼工厂！一个优秀的煎饼工厂需要具备出色的压平能力，所以 Swing 决定使用二维矩阵来测试他的新设备。

给你一个大小为 $ n \times n $ 的矩阵 $ M $，其中每个元素都是正整数。Swing 有 $ q $ 个查询需要回答。

对于每个查询，Swing 会给出四个整数 $ x_1 $、$ y_1 $、$ x_2 $ 和 $ y_2 $，以此定义一个子矩阵，该子矩阵的左上角为 $(x_1, y_1)$，右下角为 $(x_2, y_2)$。他希望你将这个子矩阵展平为一个一维数组 $ A $。具体的展平顺序是：从 $ M_{(x1,y1)} $ 开始，按行从左到右依次加入子矩阵中的元素，直到 $ M_{(x2, y2)} $ 结束。

下图通过红色虚线展示了子矩阵的边界，橙色箭头指示了元素在进入数组 $ A $ 时的顺序，图下方展示了最终的数组 $ A $。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2044H/75bdaf28c8054bf099c5d719d2a33cac51011434.png)

展平后，Swing 想知道 $\sum_{i=1}^{|A|} A_i \cdot i$ 的值，即数组中每个元素 $ A_i $ 乘以其下标 $ i $ 的总和。

## 输入格式

输入的第一行是一个整数 $ t $（$ 1 \leq t \leq 10^3 $），表示测试用例的数量。

每个测试用例的第一行给出两个整数 $ n $ 和 $ q $（$ 1 \leq n \leq 2000, 1 \leq q \leq 10^6 $），分别表示矩阵的大小和查询的个数。

接下来的 $ n $ 行中每行包含 $ n $ 个整数，分别为矩阵 $ M $ 的元素 $ M_{(i,1)}, M_{(i,2)}, \ldots, M_{(i,n)} $（$ 1 \leq M_{(i, j)} \leq 10^6 $）。

接下来的 $ q $ 行每行包含四个整数 $ x_1 $、$ y_1 $、$ x_2 $ 和 $ y_2 $（$ 1 \leq x_1 \leq x_2 \leq n, 1 \leq y_1 \leq y_2 \leq n $），表示每次查询的边界。

确保所有测试用例中的 $ n $ 的总和不超过 $ 2000 $，$ q $ 的总和不超过 $ 10^6 $。

## 输出格式

对于每个测试用例，输出 $ q $ 个查询的结果，每个结果单独占一行。

## 说明/提示

在第一个测试用例的第二个查询中，数组 $ A = [9, 5, 5, 2] $。因此，结果为 $ 1 \cdot 9 + 2 \cdot 5 + 3 \cdot 5 + 4 \cdot 2 = 42 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
4 3
1 5 2 4
4 9 5 3
4 5 2 3
1 5 5 2
1 1 4 4
2 2 3 3
1 2 4 3
3 3
1 2 3
4 5 6
7 8 9
1 1 1 3
1 3 3 3
2 2 2 2
```

### 输出

```
500 42 168 
14 42 5
```



---

---
title: "Bro Thinks He's Him"
layout: "post"
diff: 提高+/省选-
pid: CF2065H
tag: ['动态规划 DP', '线段树', '树状数组', '矩阵加速', '前缀和']
---

# Bro Thinks He's Him

## 题目描述

Skibidus 自认为是"天选之人"！他通过解决这个难题证明了这一点。你也能证明自己吗？

给定一个二进制字符串 $^{\text{∗}}$ $t$，定义 $f(t)$ 为将 $t$ 分割成由相同字符组成的连续子串的最小数量。例如，$f(\texttt{00110001}) = 4$，因为 $t$ 可以被分割为 $\texttt{[00][11][000][1]}$，每个括号内的子串均由相同字符组成。

Skibidus 给你一个二进制字符串 $s$ 和 $q$ 次查询。每次查询会翻转字符串中的一个字符（即 $\texttt{0}$ 变为 $\texttt{1}$，$\texttt{1}$ 变为 $\texttt{0}$），且修改会保留到后续查询。每次查询后，你需要输出所有非空子序列 $^{\text{†}}$ $b$ 的 $f(b)$ 之和模 $998\,244\,353$ 的结果。

 $^{\text{∗}}$ 二进制字符串仅包含字符 $\texttt{0}$ 和 $\texttt{1}$。

 $^{\text{†}}$ 字符串的子序列是指通过删除原字符串中若干（可能为零）个字符得到的新字符串。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例数量。

每个测试用例的第一行包含一个二进制字符串 $s$（$1 \leq |s| \leq 2 \cdot 10^5$）。

每个测试用例的第二行包含一个整数 $q$（$1 \leq q \leq 2 \cdot 10^5$）——查询次数。

每个测试用例的第三行包含 $q$ 个整数 $v_1, v_2, \ldots, v_q$（$1 \leq v_i \leq |s|$），表示第 $i$ 次查询翻转 $s_{v_i}$ 处的字符。

保证所有测试用例的 $|s|$ 之和与 $q$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在一行中输出 $q$ 个整数——每次查询后的答案模 $998\,244\,353$。

## 说明/提示

第一个测试用例在第一次查询后，$s$ 变为 $\texttt{001}$。计算所有子序列的 $f$ 值：
- $f(s_1) = f(\texttt{0}) = 1$
- $f(s_2) = f(\texttt{0}) = 1$
- $f(s_3) = f(\texttt{1}) = 1$
- $f(s_1 s_2) = f(\texttt{00}) = 1$
- $f(s_1 s_3) = f(\texttt{01}) = 2$
- $f(s_2 s_3) = f(\texttt{01}) = 2$
- $f(s_1 s_2 s_3) = f(\texttt{001}) = 2$

这些值的总和为 $10$，模 $998\,244\,353$ 后结果为 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
101
2
1 3
10110
3
1 2 3
101110101
5
7 2 4 4 1
```

### 输出

```
10 7 
61 59 67 
1495 1169 1417 1169 1396
```



---

---
title: "Blossom"
layout: "post"
diff: 提高+/省选-
pid: CF2084E
tag: ['数学', '前缀和', '双指针 two-pointer']
---

# Blossom

## 题目描述

给定一个长度为 $n$ 的排列 $a$ $^{\text{∗}}$，其中部分元素缺失（用 $-1$ 表示）。

定义一个排列的值为其所有非空子段 $^{\text{‡}}$ 的 MEX $^{\text{†}}$ 之和。

求所有可能通过填充 $a$ 中缺失元素形成的有效排列的值的总和，结果对 $10^9 + 7$ 取模。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $0$ 到 $n - 1$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[1,2,0,4,3]$ 是一个排列，但 $[0,1,1]$ 不是排列（因为 $1$ 在数组中出现了两次），$[0,2,3]$ 也不是排列（因为 $n=3$ 但数组中包含 $3$）。

$^{\text{†}}$ 整数集合 $c = \{c_1, c_2, \ldots, c_k\}$ 的最小排除值（MEX）定义为不包含在 $c$ 中的最小非负整数 $x$。

$^{\text{‡}}$ 序列 $a$ 是序列 $b$ 的子段，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 1000$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5000$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$-1 \le a_i < n$）。  

保证 $a$ 中非 $-1$ 的元素互不相同。  
保证所有测试用例的 $n$ 之和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——所有可能有效排列的值的总和对 $10^9 + 7$ 取模的结果。


## 说明/提示

- 在第一个测试用例中，唯一有效的排列是 $[0, 1]$，其值为 $3$，因为：
  $$
  \operatorname{mex}([0]) + \operatorname{mex}([1]) + \operatorname{mex}([0, 1]) = 1 + 0 + 2 = 3
  $$
  因此答案为 $3$。

- 在第二个测试用例中，有两个有效排列：$[0, 1]$ 和 $[1, 0]$。$[0, 1]$ 和 $[1, 0]$ 的值均为 $3$，因此答案为 $3 + 3 = 6$。

- 在第四个测试用例中，有两个有效排列：$[0, 2, 1]$ 和 $[1, 2, 0]$。$[0, 2, 1]$ 的值为 $5$，因为：
  $$
  \operatorname{mex}([0]) + \operatorname{mex}([2]) + \operatorname{mex}([1]) + \operatorname{mex}([0, 2]) + \operatorname{mex}([2, 1]) + \operatorname{mex}([0, 2, 1]) = 1 + 0 + 0 + 1 + 0 + 3 = 5
  $$
  $[1, 2, 0]$ 的值也为 $5$，因为：
  $$
  \operatorname{mex}([1]) + \operatorname{mex}([2]) + \operatorname{mex}([0]) + \operatorname{mex}([1, 2]) + \operatorname{mex}([2, 0]) + \operatorname{mex}([1, 2, 0]) = 0 + 0 + 1 + 0 + 1 + 3 = 5
  $$
  因此答案为 $5 + 5 = 10$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2
0 -1
2
-1 -1
3
2 0 1
3
-1 2 -1
5
-1 0 -1 2 -1
```

### 输出

```
3
6
7
10
104
```



---

---
title: "Vowels"
layout: "post"
diff: 提高+/省选-
pid: CF383E
tag: ['组合数学', '前缀和']
---

# Vowels

## 题目描述

Iahubina is tired of so many complicated languages, so she decided to invent a new, simple language. She already made a dictionary consisting of $ n $ 3-words. A 3-word is a sequence of exactly $ 3 $ lowercase letters of the first 24 letters of the English alphabet ( $ a $ to $ x $ ). She decided that some of the letters are vowels, and all the others are consonants. The whole language is based on a simple rule: any word that contains at least one vowel is correct.

Iahubina forgot which letters are the vowels, and wants to find some possible correct sets of vowels. She asks Iahub questions. In each question, she will give Iahub a set of letters considered vowels (in this question). For each question she wants to know how many words of the dictionary are correct, considering the given set of vowels.

Iahubina wants to know the $ xor $ of the squared answers to all the possible questions. There are $ 2^{24} $ different questions, they are all subsets of the set of the first 24 letters of the English alphabet. Help Iahub find that number.

## 输入格式

The first line contains one integer, $ n $ $ (1<=n<=10^{4}) $ . Each of the next $ n $ lines contains a 3-word consisting of $ 3 $ lowercase letters. There will be no two identical 3-words.

## 输出格式

Print one number, the $ xor $ of the squared answers to the queries.

## 样例 #1

### 输入

```
5
abc
aaa
ada
bcd
def

```

### 输出

```
0

```



---

---
title: "Obsessive String"
layout: "post"
diff: 提高+/省选-
pid: CF494B
tag: ['字符串', '递推', '前缀和']
---

# Obsessive String

## 题目描述

给定两个字符串 $s$ 和 $t$。定义一种合法的截取方案为，在字符串 $s$ 中截取若干（大于 $0$）个互不相交的子串，满足 $t$ 是每个这些子串的子串。

请你输出总方案数模 $10^9 + 7$ 的值。

## 输入格式

输入共两行。第一行一个字符串 $s$，第二行一个字符串 $t$。

## 输出格式

输出共一行，一个非负整数表示答案。

## 说明/提示

保证 $1 \leq |s|, |t| \leq 10^5$，字符串中只包含小写拉丁字母。

## 样例 #1

### 输入

```
ababa
aba

```

### 输出

```
5

```

## 样例 #2

### 输入

```
welcometoroundtwohundredandeightytwo
d

```

### 输出

```
274201

```

## 样例 #3

### 输入

```
ddd
d

```

### 输出

```
12

```



---

---
title: "Modulo Sum"
layout: "post"
diff: 提高+/省选-
pid: CF577B
tag: ['数学', '背包 DP', '前缀和']
---

# Modulo Sum

## 题目描述

# 题面描述

给出 $1$ 个长度为 $n$ 的序列，以及 $1$ 个正整数 $m$。问这个原序列中是否存在非空子序列，使其元素之和能被 $m$ 整除。

## 输入格式

第 $1$ 行，有 $2$ 个正整数，分别为原序列的长度 $n$ 和 除数 $m$。
（数据范围：$1 \leqslant n \leqslant 10^{6}$，$2 \leqslant m \leqslant 10^{3}$）
第 $2$ 行，有 $n$ 个自然数，表示该原序列的元素 $a_i$。
（数据范围：$0 \leqslant a_i \leqslant 10^{9}$）

## 输出格式

仅 $1$ 行，如果存在符合条件的子序列，输出 **YES**，否则输出 **NO**。

# 样例解释

- 第 $1$ 组样例的解释：
存在符合条件的子序列 $\{2,3\}$，其元素之和为 $2 + 3 = 5$，$5$ 可以被 $5$ 整除。
- 第 $2$ 组样例的解释：
由于原序列中只有 $1$ 个元素，因此它只有 $1$ 个子序列 $\{5\}$，但显然 $5$ 不可以被 $6$ 整除。
- 第 $3$ 组样例的解释：
存在符合条件的子序列 $\{3,3\}$，其元素之和为 $3 + 3 = 6$，$6$ 可以被 $6$ 整除。
- 第 $4$ 组样例的解释：
选择整个原序列作为子序列，其元素之和为 $5 + 5 + 5 + 5 + 5 + 5 = 30$，$30$ 可以被 $6$ 整除。

Translated by Sooke

## 样例 #1

### 输入

```
3 5
1 2 3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1 6
5

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
4 6
3 1 1 3

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
6 6
5 5 5 5 5 5

```

### 输出

```
YES

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
title: "Gadgets for dollars and pounds"
layout: "post"
diff: 提高+/省选-
pid: CF609D
tag: ['贪心', '二分', '前缀和']
---

# Gadgets for dollars and pounds

## 题目描述

一个人手上有 $s$ 卢布，他要在 $n$ 天内买 $m$ 样东西中的 $k$ 样。

每个物品有两种支付方式，要么用美元，要么用英镑。

每天有不同的支付方式代价，即换取一美元或英镑，需要付出 $x_i$ 卢布的代价。

求最早完成买 $k$ 样东西的天数。如果无法完成任务，输出 `-1`。

一种商品只能购买一次，但是一天可以买多种商品。

## 输入格式

第一行包含四个整数，$n, m, k, s$。

第二行 $n$ 个整数，表示每天多少卢布换一美元。

第三行 $n$ 个整数，表示多少卢布换一英镑。

接下来是 $m$ 行，每行 $2$ 个整数，表示每样东西用什么货币结账（ $1$ 是美元，$2$ 是英镑），以及要多少那种外币。

## 输出格式

输出最短到第几天买完 $k$ 样商品。

以及输出 $q_i$ 与 $d_i$ 表示在第 $d_i$ 天购买第 $q_i$ 样东西。

## 样例 #1

### 输入

```
5 4 2 2
1 2 3 2 1
3 2 1 2 3
1 1
2 1
1 2
2 2

```

### 输出

```
3
1 1
2 3

```

## 样例 #2

### 输入

```
4 3 2 200
69 70 71 72
104 105 106 107
1 1
2 2
1 2

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4 3 1 1000000000
900000 910000 940000 990000
990000 999000 999900 999990
1 87654
2 76543
1 65432

```

### 输出

```
-1

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
title: "Alyona and a tree"
layout: "post"
diff: 提高+/省选-
pid: CF739B
tag: ['深度优先搜索 DFS', '前缀和', '差分']
---

# Alyona and a tree

## 题目描述

Alyona有一棵有 $n$ 个节点的树。这棵树的根节点是 $1$。在每个节点里，Alyona写了一个正整数，在节点 $i$ 她写了正整数 $a_i$ 。另外，她在这棵树上的每条边上写了一个正整数（不同边上可能有不同的数）。

让我们定义 $dist(v,u)$ 作为从 $v$ 到 $u$ 的简单路径上的边权和。

当且仅当 $u$ 在 $v$ 的子树中并且 $dist(v,u)\leq a_u$，顶点 $v$ 控制顶点 $u(v\neq u)$ 。

Alyona想在某些顶点定居。为了做到这件事，她想知道在每个节点 $v$ 能控制几个节点。

## 输入格式

第一行包含一个整数 $n (1\leq n\leq 2\times 10^5)$

第二行有 $n$ 个整数 $a_1,a_2,\ldots,a_n(1\leq a_i\leq 10^9)$ ,作为节点 $i$ 的数。

下面的 $n-1$ 行，每行有两个整数。第 $i$ 行包含整数 $p_i,w_i(1\leq p_i\leq n,1\leq w_i\leq 10^9)$ ,分别为节点 $i+1$ 的在树上的父节点和 $p_i$ 和 $(i+1)$ 的边上的数字。

数据保证是个树。

## 输出格式

输出 $n$ 个整数，第 $i$ 个数为节点 $i$ 能控制的点数。

## 说明/提示

在样例中，节点 $1$ 控制了节点 $3$ ，节点 $3$ 控制节点 $5$ （注意，这并不代表节点 $1$ 控制了节点 $5$ ）

Translated by @lolte

## 样例 #1

### 输入

```
5
2 5 1 4 6
1 7
1 1
3 5
3 6

```

### 输出

```
1 0 1 0 0

```

## 样例 #2

### 输入

```
5
9 7 8 6 5
1 1
2 1
3 1
4 1

```

### 输出

```
4 3 2 1 0

```



---

---
title: "Mahmoud and Ehab and the xor-MST"
layout: "post"
diff: 提高+/省选-
pid: CF959E
tag: ['生成树', '进制', '前缀和']
---

# Mahmoud and Ehab and the xor-MST

## 题目描述

Ehab is interested in the bitwise-xor operation and the special graphs. Mahmoud gave him a problem that combines both. He has a complete graph consisting of $ n $ vertices numbered from $ 0 $ to $ n-1 $ . For all $ 0<=u<v<n $ , vertex $ u $ and vertex $ v $ are connected with an undirected edge that has weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/31294aedffbec70e119efb89ca1f6d2afecc694a.png) (where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/bc47da33894a98df53134f30108d8405a90ea418.png) is the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Can you find the weight of the minimum spanning tree of that graph?

You can read about complete graphs in [https://en.wikipedia.org/wiki/Complete\_graph](https://en.wikipedia.org/wiki/Complete_graph)

You can read about the minimum spanning tree in [https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)

The weight of the minimum spanning tree is the sum of the weights on the edges included in it.

## 输入格式

The only line contains an integer $ n $ $ (2<=n<=10^{12}) $ , the number of vertices in the graph.

## 输出格式

The only line contains an integer $ x $ , the weight of the graph's minimum spanning tree.

## 说明/提示

In the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/da1dd366c44de9a7fa58c6a7748f6a57cd6a4b83.png) The weight of the minimum spanning tree is 1+2+1=4.

## 样例 #1

### 输入

```
4

```

### 输出

```
4
```



---

