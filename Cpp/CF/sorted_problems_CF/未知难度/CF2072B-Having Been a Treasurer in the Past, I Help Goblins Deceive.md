---
title: "Having Been a Treasurer in the Past, I Help Goblins Deceive"
layout: "post"
diff: 难度0
pid: CF2072B
tag: []
---

# Having Been a Treasurer in the Past, I Help Goblins Deceive

## 题目描述

After completing the first quest, Akito left the starting cave. After a while, he stumbled upon a goblin village.

Since Akito had nowhere to live, he wanted to find out the price of housing. It is well known that goblins write numbers as a string of characters '-' and '\_', and the value represented by the string $ s $ is the number of distinct subsequences $ ^{\text{∗}} $ of the string $ s $ that are equal to the string "-\_-" (this is very similar to goblin faces).

For example, the string $ s= $ "-\_--\_-" represents the number $ 6 $ , as it has $ 6 $ subsequences "-\_-":

1. $ s_1+s_2+s_3 $
2. $ s_1+s_2+s_4 $
3. $ s_1+s_2+s_6 $
4. $ s_1+s_5+s_6 $
5. $ s_3+s_5+s_6 $
6. $ s_4+s_5+s_6 $

Initially, the goblins wrote a random string-number $ s $ in response to Akito's question, but then they realized that they wanted to take as much gold as possible from the traveler. To do this, they ask you to rearrange the characters in the string $ s $ so that the value of the number represented by the string $ s $ is maximized.

 $ ^{\text{∗}} $ A subsequence of a string $ a $ is a string $ b $ that can be obtained by deleting several (possibly $ 0 $ ) characters from $ a $ . Subsequences are considered different if they are obtained by deleting different sets of indices.

## 输入格式

The first line contains the number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

In the first line of each test case, there is one number $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the string written by the goblins.

In the second line of each test case, there is a string $ s $ of length $ n $ , consisting only of characters '-' and '\_' — the string written by the goblins.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, you need to output one number — the maximum number of subsequences equal to the string "-\_-", if the characters in the string $ s $ are optimally rearranged.

## 说明/提示

In the first test case, it is beneficial to rearrange the characters to form the string "-\_-". This is the only string of three characters that has at least one subsequence "-\_-".

In the second test case, there is only one character "-", and at least two are needed for the subsequence "-\_-". This means that for any rearrangement of characters, the answer will be $ 0 $ .

In the seventh and eighth test cases, the length of the string $ n < 3 $ , which means that subsequences of length $ 3 $ do not exist.

## 样例 #1

### 输入

```
8
3
--_
5
__-__
9
--__-_---
4
_--_
10
_-_-_-_-_-
7
_------
1
-
2
_-
```

### 输出

```
1
0
27
2
30
9
0
0
```

