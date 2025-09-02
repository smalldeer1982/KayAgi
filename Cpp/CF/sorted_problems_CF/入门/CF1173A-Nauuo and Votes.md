---
title: "Nauuo and Votes"
layout: "post"
diff: 入门
pid: CF1173A
tag: []
---

# Nauuo and Votes

## 题目描述

Nauuo is a girl who loves writing comments.

One day, she posted a comment on Codeforces, wondering whether she would get upvotes or downvotes.

It's known that there were $ x $ persons who would upvote, $ y $ persons who would downvote, and there were also another $ z $ persons who would vote, but you don't know whether they would upvote or downvote. Note that each of the $ x+y+z $ people would vote exactly one time.

There are three different results: if there are more people upvote than downvote, the result will be "+"; if there are more people downvote than upvote, the result will be "-"; otherwise the result will be "0".

Because of the $ z $ unknown persons, the result may be uncertain (i.e. there are more than one possible results). More formally, the result is uncertain if and only if there exist two different situations of how the $ z $ persons vote, that the results are different in the two situations.

Tell Nauuo the result or report that the result is uncertain.

## 输入格式

The only line contains three integers $ x $ , $ y $ , $ z $ ( $ 0\le x,y,z\le100 $ ), corresponding to the number of persons who would upvote, downvote or unknown.

## 输出格式

If there is only one possible result, print the result : "+", "-" or "0".

Otherwise, print "?" to report that the result is uncertain.

## 说明/提示

In the first example, Nauuo would definitely get three upvotes and seven downvotes, so the only possible result is "-".

In the second example, no matter the person unknown downvotes or upvotes, Nauuo would get more upvotes than downvotes. So the only possible result is "+".

In the third example, Nauuo would definitely get one upvote and one downvote, so the only possible result is "0".

In the fourth example, if the only one person upvoted, the result would be "+", otherwise, the result would be "-". There are two possible results, so the result is uncertain.

## 样例 #1

### 输入

```
3 7 0

```

### 输出

```
-
```

## 样例 #2

### 输入

```
2 0 1

```

### 输出

```
+
```

## 样例 #3

### 输入

```
1 1 0

```

### 输出

```
0
```

## 样例 #4

### 输入

```
0 0 1

```

### 输出

```
?
```

