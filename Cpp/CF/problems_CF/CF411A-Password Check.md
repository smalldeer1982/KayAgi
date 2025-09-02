---
title: "Password Check"
layout: "post"
diff: 入门
pid: CF411A
tag: []
---

# Password Check

## 题目描述

You have probably registered on Internet sites many times. And each time you should enter your invented password. Usually the registration form automatically checks the password's crypt resistance. If the user's password isn't complex enough, a message is displayed. Today your task is to implement such an automatic check.

Web-developers of the company Q assume that a password is complex enough, if it meets all of the following conditions:

- the password length is at least 5 characters;
- the password contains at least one large English letter;
- the password contains at least one small English letter;
- the password contains at least one digit.

You are given a password. Please implement the automatic check of its complexity for company Q.

## 输入格式

The first line contains a non-empty sequence of characters (at most $ 100 $ characters). Each character is either a large English letter, or a small English letter, or a digit, or one of characters: "!", "?", ".", ",", "\_".

## 输出格式

If the password is complex enough, print message "Correct" (without the quotes), otherwise print message "Too weak" (without the quotes).

## 样例 #1

### 输入

```
abacaba

```

### 输出

```
Too weak

```

## 样例 #2

### 输入

```
X12345

```

### 输出

```
Too weak

```

## 样例 #3

### 输入

```
CONTEST_is_STARTED!!11

```

### 输出

```
Correct

```

