---
title: "Chat room"
layout: "post"
diff: 入门
pid: CF58A
tag: ['模拟', '字符串', '枚举', '队列']
---

# Chat room

## 题目描述

Vasya has recently learned to type and log on to the Internet. He immediately entered a chat room and decided to say hello to everybody. Vasya typed the word $ s $ . It is considered that Vasya managed to say hello if several letters can be deleted from the typed word so that it resulted in the word "hello". For example, if Vasya types the word "ahhellllloou", it will be considered that he said hello, and if he types "hlelo", it will be considered that Vasya got misunderstood and he didn't manage to say hello. Determine whether Vasya managed to say hello by the given word $ s $ .

## 输入格式

The first and only line contains the word $ s $ , which Vasya typed. This word consisits of small Latin letters, its length is no less that 1 and no more than 100 letters.

## 输出格式

If Vasya managed to say hello, print "YES", otherwise print "NO".

## 样例 #1

### 输入

```
ahhellllloou

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
hlelo

```

### 输出

```
NO

```



---

---
title: "Fake News (easy)"
layout: "post"
diff: 入门
pid: CF802G
tag: ['模拟', '字符串', '枚举', '队列']
---

# Fake News (easy)

## 题目描述

As it's the first of April, Heidi is suspecting that the news she reads today are fake, and she does not want to look silly in front of all the contestants. She knows that a newspiece is fake if it contains heidi as a subsequence. Help Heidi assess whether the given piece is true, but please be discreet about it...

## 输入格式

The first and only line of input contains a single nonempty string $ s $ of length at most $ 1000 $ composed of lowercase letters (a-z).

## 输出格式

Output YES if the string $ s $ contains heidi as a subsequence and NO otherwise.

## 说明/提示

A string $ s $ contains another string $ p $ as a subsequence if it is possible to delete some characters from $ s $ and obtain $ p $ .

## 样例 #1

### 输入

```
abcheaibcdi

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
hiedi

```

### 输出

```
NO
```



---

