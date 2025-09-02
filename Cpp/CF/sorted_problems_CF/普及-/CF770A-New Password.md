---
title: "New Password"
layout: "post"
diff: 普及-
pid: CF770A
tag: []
---

# New Password

## 题目描述

Innokentiy decides to change the password in the social net "Contact!", but he is too lazy to invent a new password by himself. That is why he needs your help.

Innokentiy decides that new password should satisfy the following conditions:

- the length of the password must be equal to $ n $ ,
- the password should consist only of lowercase Latin letters,
- the number of distinct symbols in the password must be equal to $ k $ ,
- any two consecutive symbols in the password must be distinct.

Your task is to help Innokentiy and to invent a new password which will satisfy all given conditions.

## 输入格式

The first line contains two positive integers $ n $ and $ k $ ( $ 2<=n<=100 $ , $ 2<=k<=min(n,26) $ ) — the length of the password and the number of distinct symbols in it.

Pay attention that a desired new password always exists.

## 输出格式

Print any password which satisfies all conditions given by Innokentiy.

## 说明/提示

In the first test there is one of the appropriate new passwords — java, because its length is equal to $ 4 $ and $ 3 $ distinct lowercase letters a, j and v are used in it.

In the second test there is one of the appropriate new passwords — python, because its length is equal to $ 6 $ and it consists of $ 6 $ distinct lowercase letters.

In the third test there is one of the appropriate new passwords — phphp, because its length is equal to $ 5 $ and $ 2 $ distinct lowercase letters p and h are used in it.

Pay attention the condition that no two identical symbols are consecutive is correct for all appropriate passwords in tests.

## 样例 #1

### 输入

```
4 3

```

### 输出

```
java

```

## 样例 #2

### 输入

```
6 6

```

### 输出

```
python

```

## 样例 #3

### 输入

```
5 2

```

### 输出

```
phphp

```

