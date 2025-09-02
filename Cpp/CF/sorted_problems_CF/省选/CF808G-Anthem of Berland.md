---
title: "Anthem of Berland"
layout: "post"
diff: 省选/NOI-
pid: CF808G
tag: []
---

# Anthem of Berland

## 题目描述

Berland has a long and glorious history. To increase awareness about it among younger citizens, King of Berland decided to compose an anthem.

Though there are lots and lots of victories in history of Berland, there is the one that stand out the most. King wants to mention it in the anthem as many times as possible.

He has already composed major part of the anthem and now just needs to fill in some letters. King asked you to help him with this work.

The anthem is the string $ s $ of no more than $ 10^{5} $ small Latin letters and question marks. The most glorious victory is the string $ t $ of no more than $ 10^{5} $ small Latin letters. You should replace all the question marks with small Latin letters in such a way that the number of occurrences of string $ t $ in string $ s $ is maximal.

Note that the occurrences of string $ t $ in $ s $ can overlap. Check the third example for clarification.

## 输入格式

The first line contains string of small Latin letters and question marks $ s $ ( $ 1<=|s|<=10^{5} $ ).

The second line contains string of small Latin letters $ t $ ( $ 1<=|t|<=10^{5} $ ).

Product of lengths of strings $ |s|·|t| $ won't exceed $ 10^{7} $ .

## 输出格式

Output the maximum number of occurrences of string $ t $ you can achieve by replacing all the question marks in string $ s $ with small Latin letters.

## 说明/提示

In the first example the resulting string $ s $ is "winlosewinwinlwinwin"

In the second example the resulting string $ s $ is "glorytoreorand". The last letter of the string can be arbitrary.

In the third example occurrences of string $ t $ are overlapping. String $ s $ with maximal number of occurrences of $ t $ is "abcabcab".

## 样例 #1

### 输入

```
winlose???winl???w??
win

```

### 输出

```
5

```

## 样例 #2

### 输入

```
glo?yto?e??an?
or

```

### 输出

```
3

```

## 样例 #3

### 输入

```
??c?????
abcab

```

### 输出

```
2

```

