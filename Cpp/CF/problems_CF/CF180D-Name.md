---
title: "Name"
layout: "post"
diff: 普及+/提高
pid: CF180D
tag: []
---

# Name

## 题目描述

Everything got unclear to us in a far away constellation Tau Ceti. Specifically, the Taucetians choose names to their children in a very peculiar manner.

Two young parents abac and bbad think what name to give to their first-born child. They decided that the name will be the permutation of letters of string $ s $ . To keep up with the neighbours, they decided to call the baby so that the name was lexicographically strictly larger than the neighbour's son's name $ t $ .

On the other hand, they suspect that a name tax will be introduced shortly. According to it, the Taucetians with lexicographically larger names will pay larger taxes. That's the reason abac and bbad want to call the newborn so that the name was lexicographically strictly larger than name $ t $ and lexicographically minimum at that.

The lexicographical order of strings is the order we are all used to, the "dictionary" order. Such comparison is used in all modern programming languages to compare strings. Formally, a string $ p $ of length $ n $ is lexicographically less than string $ q $ of length $ m $ , if one of the two statements is correct:

- $ n&lt;m $ , and $ p $ is the beginning (prefix) of string $ q $ (for example, "aba" is less than string "abaa"),
- $ p_{1}=q_{1} $ , $ p_{2}=q_{2} $ , ..., $ p_{k-1}=q_{k-1} $ , $ p_{k}&lt;q_{k} $ for some $ k $ ( $ 1<=k<=min(n,m) $ ), here characters in strings are numbered starting from 1.

Write a program that, given string $ s $ and the heighbours' child's name $ t $ determines the string that is the result of permutation of letters in $ s $ . The string should be lexicographically strictly more than $ t $ and also, lexicographically minimum.

## 输入格式

The first line contains a non-empty string $ s $ ( $ 1<=|s|<=5000 $ ), where $ |s| $ is its length. The second line contains a non-empty string $ t $ ( $ 1<=|t|<=5000 $ ), where $ |t| $ is its length. Both strings consist of lowercase Latin letters.

## 输出格式

Print the sought name or -1 if it doesn't exist.

## 说明/提示

In the first sample the given string $ s $ is the sought one, consequently, we do not need to change the letter order there.

## 样例 #1

### 输入

```
aad
aac

```

### 输出

```
aad

```

## 样例 #2

### 输入

```
abad
bob

```

### 输出

```
daab

```

## 样例 #3

### 输入

```
abc
defg

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
czaaab
abcdef

```

### 输出

```
abczaa

```

