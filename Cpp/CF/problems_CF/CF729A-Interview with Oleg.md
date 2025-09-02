---
title: "Interview with Oleg"
layout: "post"
diff: 入门
pid: CF729A
tag: []
---

# Interview with Oleg

## 题目描述

Polycarp has interviewed Oleg and has written the interview down without punctuation marks and spaces to save time. Thus, the interview is now a string $ s $ consisting of $ n $ lowercase English letters.

There is a filler word ogo in Oleg's speech. All words that can be obtained from ogo by adding go several times to the end of it are also considered to be fillers. For example, the words ogo, ogogo, ogogogo are fillers, but the words go, og, ogog, ogogog and oggo are not fillers.

The fillers have maximal size, for example, for ogogoo speech we can't consider ogo a filler and goo as a normal phrase. We should consider ogogo as a filler here.

To print the interview, Polycarp has to replace each of the fillers with three asterisks. Note that a filler word is replaced with exactly three asterisks regardless of its length.

Polycarp has dealt with this problem in no time. Can you do the same? The clock is ticking!

## 输入格式

The first line contains a positive integer $ n $ ( $ 1<=n<=100 $ ) — the length of the interview.

The second line contains the string $ s $ of length $ n $ , consisting of lowercase English letters.

## 输出格式

Print the interview text after the replacement of each of the fillers with "\*\*\*". It is allowed for the substring "\*\*\*" to have several consecutive occurences.

## 说明/提示

The first sample contains one filler word ogogo, so the interview for printing is "a\*\*\*b".

The second sample contains two fillers ogo and ogogogo. Thus, the interview is transformed to "\*\*\*gmg\*\*\*".

## 样例 #1

### 输入

```
7
aogogob

```

### 输出

```
a***b

```

## 样例 #2

### 输入

```
13
ogogmgogogogo

```

### 输出

```
***gmg***

```

## 样例 #3

### 输入

```
9
ogoogoogo

```

### 输出

```
*********

```

