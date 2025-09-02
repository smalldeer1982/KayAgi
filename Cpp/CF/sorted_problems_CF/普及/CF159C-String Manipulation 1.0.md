---
title: "String Manipulation 1.0"
layout: "post"
diff: 普及/提高-
pid: CF159C
tag: ['模拟']
---

# String Manipulation 1.0

## 题目描述

One popular website developed an unusual username editing procedure. One can change the username only by deleting some characters from it: to change the current name $ s $ , a user can pick number $ p $ and character $ c $ and delete the $ p $ -th occurrence of character $ c $ from the name. After the user changed his name, he can't undo the change.

For example, one can change name "arca" by removing the second occurrence of character "a" to get "arc".

Polycarpus learned that some user initially registered under nickname $ t $ , where $ t $ is a concatenation of $ k $ copies of string $ s $ . Also, Polycarpus knows the sequence of this user's name changes. Help Polycarpus figure out the user's final name.

## 输入格式

The first line contains an integer $ k $ ( $ 1<=k<=2000 $ ). The second line contains a non-empty string $ s $ , consisting of lowercase Latin letters, at most $ 100 $ characters long. The third line contains an integer $ n $ ( $ 0<=n<=20000 $ ) — the number of username changes. Each of the next $ n $ lines contains the actual changes, one per line. The changes are written as " $ p_{i} $ $ c_{i} $ " (without the quotes), where $ p_{i} $ ( $ 1<=p_{i}<=200000 $ ) is the number of occurrences of letter $ c_{i} $ , $ c_{i} $ is a lowercase Latin letter. It is guaranteed that the operations are correct, that is, the letter to be deleted always exists, and after all operations not all letters are deleted from the name. The letters' occurrences are numbered starting from 1.

## 输出格式

Print a single string — the user's final name after all changes are applied to it.

## 说明/提示

Let's consider the first sample. Initially we have name "bacbac"; the first operation transforms it into "bacbc", the second one — to "acbc", and finally, the third one transforms it into "acb".

## 样例 #1

### 输入

```
2
bac
3
2 a
1 b
2 c

```

### 输出

```
acb

```

## 样例 #2

### 输入

```
1
abacaba
4
1 a
1 a
1 c
2 b

```

### 输出

```
baa

```

