---
title: "Tanya and Postcard"
layout: "post"
diff: 普及/提高-
pid: CF518B
tag: []
---

# Tanya and Postcard

## 题目描述

Little Tanya decided to present her dad a postcard on his Birthday. She has already created a message — string $ s $ of length $ n $ , consisting of uppercase and lowercase English letters. Tanya can't write yet, so she found a newspaper and decided to cut out the letters and glue them into the postcard to achieve string $ s $ . The newspaper contains string $ t $ , consisting of uppercase and lowercase English letters. We know that the length of string $ t $ greater or equal to the length of the string $ s $ .

The newspaper may possibly have too few of some letters needed to make the text and too many of some other letters. That's why Tanya wants to cut some $ n $ letters out of the newspaper and make a message of length exactly $ n $ , so that it looked as much as possible like $ s $ . If the letter in some position has correct value and correct letter case (in the string $ s $ and in the string that Tanya will make), then she shouts joyfully "YAY!", and if the letter in the given position has only the correct value but it is in the wrong case, then the girl says "WHOOPS".

Tanya wants to make such message that lets her shout "YAY!" as much as possible. If there are multiple ways to do this, then her second priority is to maximize the number of times she says "WHOOPS". Your task is to help Tanya make the message.

## 输入格式

The first line contains line $ s $ ( $ 1<=|s|<=2·10^{5} $ ), consisting of uppercase and lowercase English letters — the text of Tanya's message.

The second line contains line $ t $ ( $ |s|<=|t|<=2·10^{5} $ ), consisting of uppercase and lowercase English letters — the text written in the newspaper.

Here $ |a| $ means the length of the string $ a $ .

## 输出格式

Print two integers separated by a space:

- the first number is the number of times Tanya shouts "YAY!" while making the message,
- the second number is the number of times Tanya says "WHOOPS" while making the message.

## 样例 #1

### 输入

```
AbC
DCbA

```

### 输出

```
3 0

```

## 样例 #2

### 输入

```
ABC
abc

```

### 输出

```
0 3

```

## 样例 #3

### 输入

```
abacaba
AbaCaBA

```

### 输出

```
3 4

```

