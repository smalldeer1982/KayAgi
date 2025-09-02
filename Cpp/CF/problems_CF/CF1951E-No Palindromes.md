---
title: "No Palindromes"
layout: "post"
diff: 提高+/省选-
pid: CF1951E
tag: []
---

# No Palindromes

## 题目描述

[Christopher Tin ft. Soweto Gospel Choir - Baba Yetu](https://youtu.be/d4iOF4yoNQw)

ඞ



You are given a string $ s $ consisting of lowercase Latin characters. You need to partition $ ^\dagger $ this string into some substrings, such that each substring is not a palindrome $ ^\ddagger $ .

 $ ^\dagger $ A partition of a string $ s $ is an ordered sequence of some $ k $ strings $ t_1, t_2, \ldots, t_k $ , such that $ t_1 + t_2 + \ldots + t_k = s $ , where $ + $ here represents the concatenation operation.

 $ ^\ddagger $ A string $ s $ is considered a palindrome if it reads the same backwards as forwards. For example, $ \mathtt{racecar} $ , $ \mathtt{abccba} $ , and $ \mathtt{a} $ are palindromes, but $ \mathtt{ab} $ , $ \mathtt{dokibird} $ , and $ \mathtt{kurosanji} $ are not.

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case contains a string $ s $ consisting of lowercase Latin characters ( $ 1 \le |s| \le 10^6 $ ).

It is guaranteed that the sum of $ |s| $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print on one line "YES" if there exists a partition of $ s $ whose parts are not palindromes, or "NO" if there is no such partition.

If the answer is "YES", on the second line, print an integer $ k $ — the number of parts that $ s $ needs to be partitioned to such that each part is not a palindrome. On the third line, print $ k $ strings $ t_1, t_2, \ldots, t_k $ representing such a partition. If there are multiple such partitions, print any of them.

## 说明/提示

In the first test case, since $ \mathtt{sinktheyacht} $ is already non-palindrome, the partition $ [\mathtt{sinktheyacht}] $ is valid.

In the second test case, as any substring of the string $ s $ is palindrome, there are no valid partitions.

In the third test case, another valid partition is $ [\mathtt{uw},\mathtt{uo}, \mathtt{wou}, \mathtt{wu}] $ .

## 样例 #1

### 输入

```
3
sinktheyacht
lllllllll
uwuowouwu
```

### 输出

```
YES
1
sinktheyacht
NO
YES
3
uw uow ouwu
```

