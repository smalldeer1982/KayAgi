---
title: "Vitaly and Strings"
layout: "post"
diff: 普及/提高-
pid: CF518A
tag: ['字符串']
---

# Vitaly and Strings

## 题目描述

Vitaly is a diligent student who never missed a lesson in his five years of studying in the university. He always does his homework on time and passes his exams in time.

During the last lesson the teacher has provided two strings $ s $ and $ t $ to Vitaly. The strings have the same length, they consist of lowercase English letters, string $ s $ is lexicographically smaller than string $ t $ . Vitaly wondered if there is such string that is lexicographically larger than string $ s $ and at the same is lexicographically smaller than string $ t $ . This string should also consist of lowercase English letters and have the length equal to the lengths of strings $ s $ and $ t $ .

Let's help Vitaly solve this easy problem!

## 输入格式

The first line contains string $ s $ ( $ 1<=|s|<=100 $ ), consisting of lowercase English letters. Here, $ |s| $ denotes the length of the string.

The second line contains string $ t $ ( $ |t|=|s| $ ), consisting of lowercase English letters.

It is guaranteed that the lengths of strings $ s $ and $ t $ are the same and string $ s $ is lexicographically less than string $ t $ .

## 输出格式

If the string that meets the given requirements doesn't exist, print a single string "No such string" (without the quotes).

If such string exists, print it. If there are multiple valid strings, you may print any of them.

## 说明/提示

String $ s=s_{1}s_{2}...\ s_{n} $ is said to be lexicographically smaller than $ t=t_{1}t_{2}...\ t_{n} $ , if there exists such $ i $ , that $ s_{1}=t_{1},s_{2}=t_{2},...\ s_{i-1}=t_{i-1},s_{i}<t_{i} $ .

## 样例 #1

### 输入

```
a
c

```

### 输出

```
b

```

## 样例 #2

### 输入

```
aaa
zzz

```

### 输出

```
kkk

```

## 样例 #3

### 输入

```
abcdefg
abcdefh

```

### 输出

```
No such string

```

