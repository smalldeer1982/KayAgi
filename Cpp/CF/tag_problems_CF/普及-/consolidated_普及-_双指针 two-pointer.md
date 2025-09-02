---
title: "Prefiquence"
layout: "post"
diff: 普及-
pid: CF1968B
tag: ['双指针 two-pointer']
---

# Prefiquence

## 题目描述

You are given two binary strings $ a $ and $ b $ . A binary string is a string consisting of the characters '0' and '1'.

Your task is to determine the maximum possible number $ k $ such that a prefix of string $ a $ of length $ k $ is a subsequence of string $ b $ .

A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements.

## 输入格式

The first line consists of a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1\le n,m \le 2 \cdot 10^5 $ ) — the length of string $ a $ and the length of string $ b $ , respectively.

The second line of each test case contains a binary string $ a $ of length $ n $ .

The third line of each test case contains a binary string $ b $ of length $ m $ .

It is guaranteed that the sum of values $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Similarly, the sum of values $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the maximum $ k $ , such that the first $ k $ characters of $ a $ form a subsequence of $ b $ .

## 说明/提示

In the first example, the string ' $ 10 $ ' is a subsequence of ' $ 1\color{red}11\color{red}0 $ ' but the string ' $ 100 $ ' is not. So the answer is $ 2 $ .

In the fifth example, $ a $ =' $ 100 $ ', $ b $ =' $ 1\color{red}{10}1\color{red}0 $ ', whole string $ a $ is a subsequence of string $ b $ . So the answer is $ 3 $ .

In the sixth example, string $ b $ does not contain ' $ 1 $ ' so the answer is $ 0 $ .

## 样例 #1

### 输入

```
6
5 4
10011
1110
3 3
100
110
1 3
1
111
4 4
1011
1111
3 5
100
11010
3 1
100
0
```

### 输出

```
2
2
1
1
3
0
```



---

---
title: "Substring and Subsequence"
layout: "post"
diff: 普及-
pid: CF1989B
tag: ['贪心', '双指针 two-pointer']
---

# Substring and Subsequence

## 题目描述

You are given two strings $ a $ and $ b $ , both consisting of lowercase Latin letters.

A subsequence of a string is a string which can be obtained by removing several (possibly zero) characters from the original string. A substring of a string is a contiguous subsequence of that string.

For example, consider the string abac:

- a, b, c, ab, aa, ac, ba, bc, aba, abc, aac, bac and abac are its subsequences;
- a, b, c, ab, ba, ac, aba, bac and abac are its substrings.

Your task is to calculate the minimum possible length of the string that contains $ a $ as a substring and $ b $ as a subsequence.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

The first line of each test case contains a string $ a $ ( $ 1 \le |a| \le 100 $ ), consisting of lowercase Latin letters.

The second line of each test case contains a string $ b $ ( $ 1 \le |b| \le 100 $ ), consisting of lowercase Latin letters.

## 输出格式

For each test case, print a single integer — the minimum possible length of the string that contains $ a $ as a substring and $ b $ as a subsequence.

## 说明/提示

In the examples below, the characters that correspond to the subsequence equal to $ b $ are bolded.

In the first example, one of the possible answers is caba.

In the second example, one of the possible answers is ercf.

In the third example, one of the possible answers is mmm.

In the fourth example, one of the possible answers is contest.

In the fifth example, one of the possible answers is abcdefg.

## 样例 #1

### 输入

```
5
aba
cb
er
cf
mmm
mmm
contest
test
cde
abcefg
```

### 输出

```
4
4
3
7
7
```



---

---
title: "Bouquet (Easy Version)"
layout: "post"
diff: 普及-
pid: CF1995B1
tag: ['贪心', '双指针 two-pointer']
---

# Bouquet (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version, the flowers are specified by enumeration.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ flowers in the store, each of which is characterized by the number of petals, and a flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use in her bouquet should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the number of test cases. This is followed by descriptions of the test cases.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 1 \le n \le 2 \cdot 10^5, 1 \le m \le 10^{18} $ ) — the number of flowers in the store and the number of coins the girl possesses, respectively. The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of petals of the $ i $ -th flower in the store.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot {10}^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible number of petals in the bouquet that the girl can assemble while meeting all the conditions listed above.

## 说明/提示

In the first test case, you can assemble a bouquet with $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the third test case, you can assemble a bouquet with only one flower of any type, so the answer is $ 610 $ . In the fourth test case, you can assemble a bouquet with $ (4, 4, 5) $ , which gives you $ 13 $ petals, and it is the maximum amount of petals that the girl can buy.

## 样例 #1

### 输入

```
5
5 10
1 1 2 2 3
8 20
4 2 7 5 6 1 1 1
8 100000
239 30 610 122 24 40 8 2
11 13
2 4 11 1 1 2 3 5 4 3 2
8 1033
206 206 206 207 207 207 207 1000
```

### 输出

```
7
13
610
13
1033
```



---

