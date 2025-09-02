---
title: "PolandBall and Game"
layout: "post"
diff: 普及/提高-
pid: CF755B
tag: []
---

# PolandBall and Game

## 题目描述

两个人玩一个游戏 他们轮流说单词  
每一个人只能说出自己会的单词 并且任何一个在之前被说过(被自己或对方说过)的单词不能被再说一次  

最后无话可说(所有会的单词都被说过)的人负  
问先手是否能获胜

## 输入格式

第一行n,m分别代表先手和后手分别会多少单词  
接下来n行每行一个字符串代表单词 先手会且仅会这些单词
再接下来m行每行一个字符串代表单词 后手会且仅会这些单词

## 输出格式

一个字符串  
先手胜(后手负)输出YES 否则输出NO

## 样例 #1

### 输入

```
5 1
polandball
is
a
cool
character
nope

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2
kremowka
wadowicka
kremowka
wiedenska

```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 2
a
a
b

```

### 输出

```
NO
```

