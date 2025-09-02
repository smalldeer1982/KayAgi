---
title: "Long Binary String"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1698G
tag: []
---

# Long Binary String

## 题目描述

There is a binary string $ t $ of length $ 10^{100} $ , and initally all of its bits are $ \texttt{0} $ . You are given a binary string $ s $ , and perform the following operation some times:

- Select some substring of $ t $ , and replace it with its XOR with $ s $ . $ ^\dagger $

 After several operations, the string $ t $ has exactly two bits $ \texttt{1} $ ; that is, there are exactly two distinct indices $ p $ and $ q $ such that the $ p $ -th and $ q $ -th bits of $ t $ are $ \texttt{1} $ , and the rest of the bits are $ \texttt{0} $ . Find the lexicographically largest $ ^\ddagger $ string $ t $ satisfying these constraints, or report that no such string exists.

 $ ^\dagger $ Formally, choose an index $ i $ such that $ 0 \leq i \leq 10^{100}-|s| $ . For all $ 1 \leq j \leq |s| $ , if $ s_j = \texttt{1} $ , then toggle $ t_{i+j} $ . That is, if $ t_{i+j}=\texttt{0} $ , set $ t_{i+j}=\texttt{1} $ . Otherwise if $ t_{i+j}=\texttt{1} $ , set $ t_{i+j}=\texttt{0} $ .

 $ ^\ddagger $ A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length if in the first position where $ a $ and $ b $ differ, the string $ a $ has a bit $ \texttt{1} $ and the corresponding bit in $ b $ is $ \texttt{0} $ .

## 输入格式

The only line of each test contains a single binary string $ s $ ( $ 1 \leq |s| \leq 35 $ ).

## 输出格式

If no string $ t $ exists as described in the statement, output -1. Otherwise, output the integers $ p $ and $ q $ ( $ 1 \leq p < q \leq 10^{100} $ ) such that the $ p $ -th and $ q $ -th bits of the lexicographically maximal $ t $ are $ \texttt{1} $ .

## 说明/提示

In the first test, you can perform the following operations. $ $$$\texttt{00000}\ldots \to \color{red}{\texttt{1}}\texttt{0000}\ldots \to \texttt{1}\color{red}{\texttt{1}}\texttt{000}\ldots $ $ </p><p>In the second test, you can perform the following operations.  $ $ \texttt{00000}\ldots \to \color{red}{\texttt{001}}\texttt{00}\ldots \to \texttt{0}\color{red}{\texttt{011}}\texttt{0}\ldots $ $ </p><p>In the third test, you can perform the following operations.  $ $ \texttt{00000}\ldots \to \color{red}{\texttt{1111}}\texttt{0}\ldots \to \texttt{1}\color{red}{\texttt{0001}}\ldots $ $ </p><p>It can be proven that these strings  $ t $  are the lexicographically largest ones.</p><p>In the fourth test, you can't make a single bit  $ \\texttt{1}$$$, so it is impossible.

## 样例 #1

### 输入

```
1
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
001
```

### 输出

```
3 4
```

## 样例 #3

### 输入

```
1111
```

### 输出

```
1 5
```

## 样例 #4

### 输入

```
00000
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
00000111110000011111000001111101010
```

### 输出

```
6 37452687
```

