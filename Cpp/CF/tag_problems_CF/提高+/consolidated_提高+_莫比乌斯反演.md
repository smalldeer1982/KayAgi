---
title: "Array Equalizer"
layout: "post"
diff: 提高+/省选-
pid: CF1605E
tag: ['莫比乌斯反演']
---

# Array Equalizer

## 题目描述

## 题面描述
Jeevan 有两个长度为 $n$ 的数组：$a$ 和 $b$。他有以下两种操作：

+ 选择一个 $k$（$1 \le k \le n$），对所有满足 $1 \leq i \leq n$ 并且 $1 \le i \times k \le n$ 的 $i$，令 $a_{ik}=a_{ik} + 1$。
+ 选择一个 $k$（$1 \le k \le n$），对所有满足 $1 \leq i \leq n$ 并且 $1 \le i \times k \le n$ 的 $i$，令 $a_{ik}=a_{ik} - 1$。


不幸的是，他忘记了 $b_1$，因此他会向你提问 $q$ 次，每次给出一个 $x$，表示：

- 如果 $b_1 = x$，那么把 $a$ 变为 $b$ 至少需要几次操作？

## 输入格式

第一行一个整数 $n$（$1 \le n \le 2 \cdot 10^5$），表示 $a$ 和 $b$ 的长度。

第二行 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 10^6$）。

第三行 $n$ 个整数 $b_1, b_2, \dots, b_n$（$1 \le b_i \le 10^6$）。保证 $b_1 = -1$，表示 $b_1$ 是未知的。

第四行一个整数 $q$（$1 \le q \le 2 \cdot 10^5$），表示询问次数。

接下来 $q$ 行，每行一个整数 $x$（$1 \le x \le 10^6$）。

## 输出格式

输出 $q$ 行 $q$ 个整数，表示每个询问的答案。

## 样例 #1

### 输入

```
2
3 7
-1 5
3
1
4
3
```

### 输出

```
2
4
2
```

## 样例 #2

### 输入

```
6
2 5 4 1 3 6
-1 4 6 2 3 5
3
1
8
4
```

### 输出

```
10
29
9
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
title: "Unusual Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF900D
tag: ['数论', '莫比乌斯反演', '组合数学', '容斥原理']
---

# Unusual Sequences

## 题目描述

Count the number of distinct sequences $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i} $ ) consisting of positive integers such that $ gcd(a_{1},a_{2},...,a_{n})=x $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900D/b6b0405f12ef386aeb195f818cd0534bcf4623e0.png). As this number could be large, print the answer modulo $ 10^{9}+7 $ .

 $ gcd $ here means the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor).

## 输入格式

The only line contains two positive integers $ x $ and $ y $ ( $ 1<=x,y<=10^{9} $ ).

## 输出格式

Print the number of such sequences modulo $ 10^{9}+7 $ .

## 说明/提示

There are three suitable sequences in the first test: $ (3,3,3) $ , $ (3,6) $ , $ (6,3) $ .

There are no suitable sequences in the second test.

## 样例 #1

### 输入

```
3 9

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 8

```

### 输出

```
0

```



---

