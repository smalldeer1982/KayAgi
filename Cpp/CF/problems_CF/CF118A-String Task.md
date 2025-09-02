---
title: "String Task"
layout: "post"
diff: 入门
pid: CF118A
tag: ['模拟', '字符串', '枚举']
---

# String Task

## 题目描述

Petya started to attend programming lessons. On the first lesson his task was to write a simple program. The program was supposed to do the following: in the given string, consisting if uppercase and lowercase Latin letters, it:

- deletes all the vowels,
- inserts a character "." before each consonant,
- replaces all uppercase consonants with corresponding lowercase ones.

Vowels are letters "A", "O", "Y", "E", "U", "I", and the rest are consonants. The program's input is exactly one string, it should return the output as a single string, resulting after the program's processing the initial string.

Help Petya cope with this easy task.

## 输入格式

The first line represents input string of Petya's program. This string only consists of uppercase and lowercase Latin letters and its length is from $ 1 $ to $ 100 $ , inclusive.

## 输出格式

Print the resulting string. It is guaranteed that this string is not empty.

## 样例 #1

### 输入

```
tour

```

### 输出

```
.t.r

```

## 样例 #2

### 输入

```
Codeforces

```

### 输出

```
.c.d.f.r.c.s

```

## 样例 #3

### 输入

```
aBAcAba

```

### 输出

```
.b.c.b

```

