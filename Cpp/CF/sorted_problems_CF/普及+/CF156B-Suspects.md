---
title: "Suspects"
layout: "post"
diff: 普及+/提高
pid: CF156B
tag: []
---

# Suspects

## 题目描述

As Sherlock Holmes was investigating a crime, he identified $ n $ suspects. He knows for sure that exactly one of them committed the crime. To find out which one did it, the detective lines up the suspects and numbered them from $ 1 $ to $ n $ . After that, he asked each one: "Which one committed the crime?". Suspect number $ i $ answered either "The crime was committed by suspect number $ a_{i} $ ", or "Suspect number $ a_{i} $ didn't commit the crime". Also, the suspect could say so about himself ( $ a_{i}=i $ ).

Sherlock Holmes understood for sure that exactly $ m $ answers were the truth and all other answers were a lie. Now help him understand this: which suspect lied and which one told the truth?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=10^{5},0<=m<=n $ ) — the total number of suspects and the number of suspects who told the truth. Next $ n $ lines contain the suspects' answers. The $ i $ -th line contains either "+ $ a_{i} $ " (without the quotes), if the suspect number $ i $ says that the crime was committed by suspect number $ a_{i} $ , or "- $ a_{i} $ " (without the quotes), if the suspect number $ i $ says that the suspect number $ a_{i} $ didn't commit the crime ( $ a_{i} $ is an integer, $ 1<=a_{i}<=n $ ).

It is guaranteed that at least one suspect exists, such that if he committed the crime, then exactly $ m $ people told the truth.

## 输出格式

Print $ n $ lines. Line number $ i $ should contain "Truth" if suspect number $ i $ has told the truth for sure. Print "Lie" if the suspect number $ i $ lied for sure and print "Not defined" if he could lie and could tell the truth, too, depending on who committed the crime.

## 说明/提示

The first sample has the single person and he confesses to the crime, and Sherlock Holmes knows that one person is telling the truth. That means that this person is telling the truth.

In the second sample there are three suspects and each one denies his guilt. Sherlock Holmes knows that only two of them are telling the truth. Any one of them can be the criminal, so we don't know for any of them, whether this person is telling the truth or not.

In the third sample the second and the fourth suspect defend the first and the third one. But only one is telling the truth, thus, the first or the third one is the criminal. Both of them can be criminals, so the second and the fourth one can either be lying or telling the truth. The first and the third one are lying for sure as they are blaming the second and the fourth one.

## 样例 #1

### 输入

```
1 1
+1

```

### 输出

```
Truth

```

## 样例 #2

### 输入

```
3 2
-1
-2
-3

```

### 输出

```
Not defined
Not defined
Not defined

```

## 样例 #3

### 输入

```
4 1
+2
-3
+4
-1

```

### 输出

```
Lie
Not defined
Lie
Not defined

```

