---
title: "E-mail Addresses"
layout: "post"
diff: 普及+/提高
pid: CF412E
tag: []
---

# E-mail Addresses

## 题目描述

One of the most important products of the R1 company is a popular @r1.com mail service. The R1 mailboxes receive and send millions of emails every day.

Today, the online news thundered with terrible information. The R1 database crashed and almost no data could be saved except for one big string. The developers assume that the string contains the letters of some users of the R1 mail. Recovering letters is a tedious mostly manual work. So before you start this process, it was decided to estimate the difficulty of recovering. Namely, we need to calculate the number of different substrings of the saved string that form correct e-mail addresses.

We assume that valid addresses are only the e-mail addresses which meet the following criteria:

- the address should begin with a non-empty sequence of letters, numbers, characters '\_', starting with a letter;
- then must go character '@';
- then must go a non-empty sequence of letters or numbers;
- then must go character '.';
- the address must end with a non-empty sequence of letters.

You got lucky again and the job was entrusted to you! Please note that the substring is several consecutive characters in a string. Two substrings, one consisting of the characters of the string with numbers $ l_{1},l_{1}+1,l_{1}+2,...,r_{1} $ and the other one consisting of the characters of the string with numbers $ l_{2},l_{2}+1,l_{2}+2,...,r_{2} $ , are considered distinct if $ l_{1}≠l_{2} $ or $ r_{1}≠r_{2} $ .

## 输入格式

The first and the only line contains the sequence of characters $ s_{1}s_{2}...\ s_{n} $ $ (1<=n<=10^{6}) $ — the saved string. It is guaranteed that the given string contains only small English letters, digits and characters '.', '\_', '@'.

## 输出格式

Print in a single line the number of substrings that are valid e-mail addresses.

## 说明/提示

In the first test case all the substrings that are correct e-mail addresses begin from one of the letters of the word agapov and end in one of the letters of the word com.

In the second test case note that the e-mail x@x.x is considered twice in the answer. Note that in this example the e-mail entries overlap inside the string.

## 样例 #1

### 输入

```
gerald.agapov1991@gmail.com

```

### 输出

```
18

```

## 样例 #2

### 输入

```
x@x.x@x.x_e_@r1.com

```

### 输出

```
8

```

## 样例 #3

### 输入

```
a___@1.r

```

### 输出

```
1

```

## 样例 #4

### 输入

```
.asd123__..@

```

### 输出

```
0

```

