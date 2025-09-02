---
title: "Weighted Increasing Subsequences"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1621G
tag: ['动态规划 DP', '树状数组']
---

# Weighted Increasing Subsequences

## 题目描述

You are given the sequence of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ .

The sequence of indices $ i_1 < i_2 < \ldots < i_k $ of length $ k $ denotes the subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ of length $ k $ of sequence $ a $ .

The subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ of length $ k $ of sequence $ a $ is called increasing subsequence if $ a_{i_j} < a_{i_{j+1}} $ for each $ 1 \leq j < k $ .

The weight of the increasing subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ of length $ k $ of sequence $ a $ is the number of $ 1 \leq j \leq k $ , such that exists index $ i_k < x \leq n $ and $ a_x > a_{i_j} $ .

For example, if $ a = [6, 4, 8, 6, 5] $ , then the sequence of indices $ i = [2, 4] $ denotes increasing subsequence $ [4, 6] $ of sequence $ a $ . The weight of this increasing subsequence is $ 1 $ , because for $ j = 1 $ exists $ x = 5 $ and $ a_5 = 5 > a_{i_1} = 4 $ , but for $ j = 2 $ such $ x $ doesn't exist.

Find the sum of weights of all increasing subsequences of $ a $ modulo $ 10^9+7 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains the single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the sequence $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the sequence $ a $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the sum of weights of all increasing subsequences $ a $ modulo $ 10^9+7 $ .

## 说明/提示

In the first test case the following increasing subsequences of $ a $ have not zero weight:

- The weight of $ [a_1] = [6] $ is $ 1 $ .
- The weight of $ [a_2] = [4] $ is $ 1 $ .
- The weight of $ [a_2, a_3] = [4, 8] $ is $ 1 $ .
- The weight of $ [a_2, a_4] = [4, 6] $ is $ 1 $ .

 The sum of weights of increasing subsequences is $ 4 $ .In the second test case there are $ 7 $ increasing subsequences of $ a $ with not zero weight: $ 3 $ with weight $ 1 $ , $ 3 $ with weight $ 2 $ and $ 1 $ with weight $ 3 $ . The sum of weights is $ 12 $ .

## 样例 #1

### 输入

```
4
5
6 4 8 6 5
4
1 2 3 4
3
3 2 2
4
4 5 6 5
```

### 输出

```
4
12
0
6
```



---

---
title: "Minimize Inversions Number"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1637H
tag: ['树状数组']
---

# Minimize Inversions Number

## 题目描述

You are given a permutation $ p $ of length $ n $ .

You can choose any subsequence, remove it from the permutation, and insert it at the beginning of the permutation keeping the same order.

For every $ k $ from $ 0 $ to $ n $ , find the minimal possible number of inversions in the permutation after you choose a subsequence of length exactly $ k $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 50\,000 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ) — the length of the permutation.

The second line of each test case contains the permutation $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ).

It is guaranteed that the total sum of $ n $ doesn't exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case output $ n + 1 $ integers. The $ i $ -th of them must be the answer for the subsequence length of $ i - 1 $ .

## 说明/提示

In the second test case:

- For the length $ 0 $ : $ [4, 2, 1, 3] \rightarrow [4, 2, 1, 3] $ : $ 4 $ inversions.
- For the length $ 1 $ : $ [4, 2, \mathbf{1}, 3] \rightarrow [1, 4, 2, 3] $ : $ 2 $ inversions.
- For the length $ 2 $ : $ [4, \mathbf{2}, \mathbf{1}, 3] \rightarrow [2, 1, 4, 3] $ , or $ [4, 2, \mathbf{1}, \textbf{3}] \rightarrow [1, 3, 4, 2] $ : $ 2 $ inversions.
- For the length $ 3 $ : $ [4, \mathbf{2}, \mathbf{1}, \mathbf{3}] \rightarrow [2, 1, 3, 4] $ : $ 1 $ inversion.
- For the length $ 4 $ : $ [\mathbf{4}, \mathbf{2}, \mathbf{1}, \mathbf{3}] \rightarrow [4, 2, 1, 3] $ : $ 4 $ inversions.

## 样例 #1

### 输入

```
3
1
1
4
4 2 1 3
5
5 1 3 2 4
```

### 输出

```
0 0
4 2 2 1 4
5 4 2 2 1 5
```



---

---
title: "Yandex Cuneiform (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046F1
tag: ['贪心', '树状数组']
---

# Yandex Cuneiform (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that in this version, there are no question marks. You can hack only if you solved all versions of this problem.

For a long time, no one could decipher Sumerian cuneiform. However, it has finally succumbed to pressure! Today, you have the chance to decipher Yandex cuneiform.

Yandex cuneiform is defined by the following rules:

1. An empty string is a Yandex cuneiform.
2. If you insert exactly one copy of each of the three letters 'Y', 'D', and 'X' into a Yandex cuneiform in such a way that no two adjacent letters become equal after the operation, you obtain a Yandex cuneiform.
3. If a string can't be obtained using the above rules, it is not a Yandex cuneiform.

You are given a template. A template is a string consisting of the characters 'Y', 'D', 'X', and '?'.

You need to check whether there exists a way to replace each question mark with 'Y', 'D', or 'X' to obtain a Yandex cuneiform, and if it exists, output any of the matching options, as well as a sequence of insertion operations to obtain the resulting cuneiform.

In this version of the problem, there are no question marks in the template.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

Each test case consists of a single line containing a template of length $ n $ ( $ 3 \leq n < 2 \cdot 10^5 $ , $ n \bmod 3 = 0 $ ), consisting only of characters 'Y', 'D', 'X'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing 'NO' if it is not possible to obtain a cuneiform from the given template.

Otherwise, output 'YES' on the first line, and on the second line, any obtainable cuneiform. After that, you need to output the sequence of operations that leads to the cuneiform you printed.

A sequence of operations is described by $ \frac{n}{3} $ triples of pairs. A pair has the form c p, where $ c $ is one of the letters 'Y', 'D', or 'X', and $ p $ is the position at which the letter $ c $ should be inserted. The insertion position is the number of letters to skip from the beginning of the string for the insertion. For example, after inserting the character 'D' into the string "YDX" with $ p=3 $ , the result is "YDXD", and with $ p=0 $ , it is "DYDX". Note that the index cannot exceed the current length of the string.

The operations are applied from top to bottom, left to right. After inserting each triple to the string, there should be no two adjacent identical characters.

## 说明/提示

In the second example, the string is transformed like this: $ "" \to \mathtt{YDX} \to \mathtt{YDXDYX} $ .

## 样例 #1

### 输入

```
4
YDX
YDXDYX
YDX
DYYDXYXYX
```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO
```



---

---
title: "Kevin and Strange Operation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2048H
tag: ['动态规划 DP', '树状数组']
---

# Kevin and Strange Operation

## 题目描述

Kevin is exploring problems related to binary strings in Chinatown. When he was at a loss, a stranger approached him and introduced a peculiar operation:

- Suppose the current binary string is $  t  $ , with a length of $  \vert t \vert  $ . Choose an integer $  1 \leq p \leq \vert t \vert  $ . For all $  1 \leq i < p  $ , simultaneously perform the operation $  t_i = \max(t_i, t_{i+1})  $ , and then delete $  t_p  $ .

For example, suppose the current binary string is 01001, and you choose $  p = 4  $ . Perform $  t_i = \max(t_i, t_{i+1})  $ for $ t_1 $ , $ t_2 $ , and $  t_3  $ , transforming the string into 11001, then delete $  t_4  $ , resulting in 1101.

Kevin finds this strange operation quite interesting. Thus, he wants to ask you: Given a binary string $  s  $ , how many distinct non-empty binary strings can you obtain through any number of operations (possibly zero)?

Since the answer may be very large, you only need to output the result modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t \le 10^4 $ ) — the number of test cases.

For each test case, the only line contains a binary string $  s  $ ( $  1 \le \lvert s \rvert \le 10^6  $ ).

It is guaranteed that the sum of $ \lvert s \rvert $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print a single integer in the only line of the output — the number of distinct non-empty binary strings you can obtain, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, all the binary strings you can obtain are: 11001, 1001, 1101, 001, 101, 111, 01, 11, and 1. There are $  9  $ in total.

## 样例 #1

### 输入

```
2
11001
000110111001100
```

### 输出

```
9
73
```



---

---
title: "Cool Slogans"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF700E
tag: ['线段树', '后缀自动机 SAM', '后缀数组 SA']
---

# Cool Slogans

## 题目描述

Bomboslav set up a branding agency and now helps companies to create new logos and advertising slogans. In term of this problems, slogan of the company should be a non-empty substring of its name. For example, if the company name is "hornsandhoofs", then substrings "sand" and "hor" could be its slogans, while strings "e" and "hornss" can not.

Sometimes the company performs rebranding and changes its slogan. Slogan $ A $ is considered to be cooler than slogan $ B $ if $ B $ appears in $ A $ as a substring at least twice (this occurrences are allowed to overlap). For example, slogan $ A= $ "abacaba" is cooler than slogan $ B= $ "ba", slogan $ A= $ "abcbcbe" is cooler than slogan $ B= $ "bcb", but slogan $ A= $ "aaaaaa" is not cooler than slogan $ B= $ "aba".

You are given the company name $ w $ and your task is to help Bomboslav determine the length of the longest sequence of slogans $ s_{1},s_{2},...,s_{k} $ , such that any slogan in the sequence is cooler than the previous one.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the length of the company name that asks Bomboslav to help. The second line contains the string $ w $ of length $ n $ , that consists of lowercase English letters.

## 输出格式

Print a single integer — the maximum possible length of the sequence of slogans of the company named $ w $ , such that any slogan in the sequence (except the first one) is cooler than the previous

## 样例 #1

### 输入

```
3
abc

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
ddddd

```

### 输出

```
5

```

## 样例 #3

### 输入

```
11
abracadabra

```

### 输出

```
3

```



---

