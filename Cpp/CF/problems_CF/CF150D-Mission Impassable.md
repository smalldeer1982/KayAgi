---
title: "Mission Impassable"
layout: "post"
diff: 省选/NOI-
pid: CF150D
tag: []
---

# Mission Impassable

## 题目描述

Market stalls now have the long-awaited game The Colder Scrools V: Nvodsk. The game turned out to be difficult as hell and most students can't complete the last quest ("We don't go to Nvodsk..."). That threatened winter exams. The rector already started to wonder whether he should postpone the winter exams till April (in fact, he wanted to complete the quest himself). But all of a sudden a stranger appeared at the door of his office. "Good afternoon. My name is Chuck and I solve any problems" — he said.

And here they are sitting side by side but still they can't complete the mission. The thing is, to kill the final boss one should prove one's perfect skills in the art of managing letters. One should be a real magician to do that. And can you imagine what happens when magicians start competing...

But let's put it more formally: you are given a string and a set of integers $ a_{i} $ . You are allowed to choose any substring that is a palindrome and delete it. At that we receive some number of points equal to $ a_{k} $ , where $ k $ is the length of the deleted palindrome. For some $ k $ , $ a_{k}= $ -1, which means that deleting palindrome strings of such length is forbidden. After a substring is deleted, the remaining part "shifts together", that is, at no moment of time the string has gaps. The process is repeated while the string has at least one palindrome substring that can be deleted. All gained points are summed up.

Determine what maximum number of points can be earned.

"Oh" — said Chuck, raising from the chair, — "I used to love deleting palindromes, just like you, but one day I took an arrow in the Knee".

## 输入格式

The first line contains an integer $ l $ ( $ 1<=l<=150 $ ) — the length of the string.

The second line contains exactly $ l $ integers $ a_{k} $ ( $ -1<=a_{k}<=10^{5} $ ) — the points a player gains for deleting.

The third line contains exactly $ l $ lowercase Latin letters — the original string from which a player can delete palindromes. The line contains no other characters apart from the newline character at the end of the string.

## 输出格式

Print a single number — the maximum number of points one can gain if he plays on the given string.

## 说明/提示

In the first sample we cannot delete any substring, so the best result is $ 0 $ . In the second sample we are allowed to delete only those palindromes whose length equals $ 1 $ , thus, if we delete the whole string, we get $ 7 $ points. In the third sample the optimal strategy is: first we delete character c, then string aa, then bb, and the last one aa. At that we get $ 1+3*5=16 $ points.

## 样例 #1

### 输入

```
7
-1 -1 -1 -1 -1 -1 -1
abacaba

```

### 输出

```
0

```

## 样例 #2

### 输入

```
7
1 -1 -1 -1 -1 -1 -1
abacaba

```

### 输出

```
7

```

## 样例 #3

### 输入

```
7
1 5 -1 -1 -1 -1 10
abacaba

```

### 输出

```
16

```

