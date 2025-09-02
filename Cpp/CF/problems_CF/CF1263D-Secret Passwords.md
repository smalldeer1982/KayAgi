---
title: "Secret Passwords"
layout: "post"
diff: 普及+/提高
pid: CF1263D
tag: []
---

# Secret Passwords

## 题目描述

One unknown hacker wants to get the admin's password of AtForces testing system, to get problems from the next contest. To achieve that, he sneaked into the administrator's office and stole a piece of paper with a list of $ n $ passwords — strings, consists of small Latin letters.

Hacker went home and started preparing to hack AtForces. He found that the system contains only passwords from the stolen list and that the system determines the equivalence of the passwords $ a $ and $ b $ as follows:

- two passwords $ a $ and $ b $ are equivalent if there is a letter, that exists in both $ a $ and $ b $ ;
- two passwords $ a $ and $ b $ are equivalent if there is a password $ c $ from the list, which is equivalent to both $ a $ and $ b $ .

If a password is set in the system and an equivalent one is applied to access the system, then the user is accessed into the system.

For example, if the list contain passwords "a", "b", "ab", "d", then passwords "a", "b", "ab" are equivalent to each other, but the password "d" is not equivalent to any other password from list. In other words, if:

- admin's password is "b", then you can access to system by using any of this passwords: "a", "b", "ab";
- admin's password is "d", then you can access to system by using only "d".

Only one password from the list is the admin's password from the testing system. Help hacker to calculate the minimal number of passwords, required to guaranteed access to the system. Keep in mind that the hacker does not know which password is set in the system.

## 输入格式

The first line contain integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — number of passwords in the list. Next $ n $ lines contains passwords from the list – non-empty strings $ s_i $ , with length at most $ 50 $ letters. Some of the passwords may be equal.

It is guaranteed that the total length of all passwords does not exceed $ 10^6 $ letters. All of them consist only of lowercase Latin letters.

## 输出格式

In a single line print the minimal number of passwords, the use of which will allow guaranteed to access the system.

## 说明/提示

In the second example hacker need to use any of the passwords to access the system.

## 样例 #1

### 输入

```
4
a
b
ab
d

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
ab
bc
abc

```

### 输出

```
1
```

## 样例 #3

### 输入

```
1
codeforces

```

### 输出

```
1
```

