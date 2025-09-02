---
title: "Message Transmission Error (easy version)"
layout: "post"
diff: 入门
pid: CF2010C1
tag: ['模拟', '字符串']
---

# Message Transmission Error (easy version)

## 题目描述

This is a simplified version of the problem. It differs from the difficult one only in its constraints.

At the Berland State University, the local network between servers does not always operate without errors. When transmitting two identical messages consecutively, an error may occur, resulting in the two messages merging into one. In this merging, the end of the first message coincides with the beginning of the second. Of course, the merging can only occur at identical characters. The length of the merging must be a positive number less than the length of the message text.

For example, when transmitting two messages "abrakadabra" consecutively, it is possible that it will be transmitted with the described type of error, resulting in a message like "abrakadabrabrakadabra" or "abrakadabrakadabra' (in the first case, the merging occurred at one character, and in the second case, at four).

Given the received message $ t $ , determine if it is possible that this is the result of an error of the described type in the operation of the local network, and if so, determine a possible value of $ s $ .

A situation where two messages completely overlap each other should not be considered an error. For example, if the received message is "abcd", it should be considered that there is no error in it. Similarly, simply appending one message after another is not a sign of an error. For instance, if the received message is "abcabc", it should also be considered that there is no error in it.

## 输入格式

The input consists of a single non-empty string $ t $ , consisting of lowercase letters of the Latin alphabet. The length of the string $ t $ does not exceed $ 100 $ characters.

## 输出格式

If the message $ t $ cannot contain an error, output "NO" (without quotes) in a single line of output.

Otherwise, in the first line, output "YES" (without quotes), and in the next line, output the string $ s $ — a possible message that could have led to the error. If there are multiple possible answers, any of them is acceptable.

## 说明/提示

In the second example, a suitable answer could also be the string "acacaca".

## 样例 #1

### 输入

```
abrakadabrabrakadabra
```

### 输出

```
YES
abrakadabra
```

## 样例 #2

### 输入

```
acacacaca
```

### 输出

```
YES
acaca
```

## 样例 #3

### 输入

```
abcabc
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
abababab
```

### 输出

```
YES
ababab
```

## 样例 #5

### 输入

```
tatbt
```

### 输出

```
NO
```

