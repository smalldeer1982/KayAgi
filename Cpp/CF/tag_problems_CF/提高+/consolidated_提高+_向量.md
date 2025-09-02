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
title: "Equalize the Remainders"
layout: "post"
diff: 提高+/省选-
pid: CF999D
tag: ['向量', '队列']
---

# Equalize the Remainders

## 题目描述

You are given an array consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ , and a positive integer $ m $ . It is guaranteed that $ m $ is a divisor of $ n $ .

In a single move, you can choose any position $ i $ between $ 1 $ and $ n $ and increase $ a_i $ by $ 1 $ .

Let's calculate $ c_r $ ( $ 0 \le r \le m-1) $ — the number of elements having remainder $ r $ when divided by $ m $ . In other words, for each remainder, let's find the number of corresponding elements in $ a $ with that remainder.

Your task is to change the array in such a way that $ c_0 = c_1 = \dots = c_{m-1} = \frac{n}{m} $ .

Find the minimum number of moves to satisfy the above requirement.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5, 1 \le m \le n $ ). It is guaranteed that $ m $ is a divisor of $ n $ .

The second line of input contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ), the elements of the array.

## 输出格式

In the first line, print a single integer — the minimum number of moves required to satisfy the following condition: for each remainder from $ 0 $ to $ m - 1 $ , the number of elements of the array having this remainder equals $ \frac{n}{m} $ .

In the second line, print any array satisfying the condition and can be obtained from the given array with the minimum number of moves. The values of the elements of the resulting array must not exceed $ 10^{18} $ .

## 样例 #1

### 输入

```
6 3
3 2 0 6 10 12

```

### 输出

```
3
3 2 0 7 10 14 

```

## 样例 #2

### 输入

```
4 2
0 1 2 3

```

### 输出

```
0
0 1 2 3 

```



---

