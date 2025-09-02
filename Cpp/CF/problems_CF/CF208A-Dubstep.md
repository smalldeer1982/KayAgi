---
title: "Dubstep"
layout: "post"
diff: 普及/提高-
pid: CF208A
tag: ['模拟', '字符串', '枚举']
---

# Dubstep

## 题目描述

## 题目翻译
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB",再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"
现在给出转变后的字符串，求出原来的字符串

## 输入格式

输入包括一个非空字符串SSS，其中SSS仅由大写字母组成并且的长度不超过200
保证原来的字符串不含有"WUB"并且至少有一个单词

## 输出格式

输出转变前的字符串，每个单词用空格分隔

## 样例 #1

### 输入

```
WUBWUBABCWUB

```

### 输出

```
ABC 
```

## 样例 #2

### 输入

```
WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB

```

### 输出

```
WE ARE THE CHAMPIONS MY FRIEND 
```

