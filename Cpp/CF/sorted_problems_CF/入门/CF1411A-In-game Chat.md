---
title: "In-game Chat"
layout: "post"
diff: 入门
pid: CF1411A
tag: []
---

# In-game Chat

## 题目描述

You have been assigned to develop a filter for bad messages in the in-game chat. A message is a string $ S $ of length $ n $ , consisting of lowercase English letters and characters ')'. The message is bad if the number of characters ')' at the end of the string strictly greater than the number of remaining characters. For example, the string ")bc)))" has three parentheses at the end, three remaining characters, and is not considered bad.

## 输入格式

The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 100 $ ). Description of the $ t $ test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 100 $ ). The second line of each test case contains a string $ S $ of length $ n $ , consisting of lowercase English letters and characters ')'.

## 输出格式

For each of $ t $ test cases, print "Yes" if the string is bad. Otherwise, print "No".

You can print each letter in any case (upper or lower).

## 样例 #1

### 输入

```
5
2
))
12
gl))hf))))))
9
gege)))))
14
)aa))b))))))))
1
)
```

### 输出

```
Yes
No
Yes
Yes
Yes
```

