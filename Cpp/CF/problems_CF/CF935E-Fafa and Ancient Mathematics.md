---
title: "Fafa and Ancient Mathematics"
layout: "post"
diff: 提高+/省选-
pid: CF935E
tag: []
---

# Fafa and Ancient Mathematics

## 题目描述

Ancient Egyptians are known to have understood difficult concepts in mathematics. The ancient Egyptian mathematician Ahmes liked to write a kind of arithmetic expressions on papyrus paper which he called as Ahmes arithmetic expression.

An Ahmes arithmetic expression can be defined as:

- " $ d $ " is an Ahmes arithmetic expression, where $ d $ is a one-digit positive integer;
- " $ (E_{1}opE_{2}) $ " is an Ahmes arithmetic expression, where $ E_{1} $ and $ E_{2} $ are valid Ahmes arithmetic expressions (without spaces) and $ op $ is either plus $ (+) $ or minus $ (-) $ .

 For example 5, (1-1) and ((1+(2-3))-5) are valid Ahmes arithmetic expressions.On his trip to Egypt, Fafa found a piece of papyrus paper having one of these Ahmes arithmetic expressions written on it. Being very ancient, the papyrus piece was very worn out. As a result, all the operators were erased, keeping only the numbers and the brackets. Since Fafa loves mathematics, he decided to challenge himself with the following task:

Given the number of plus and minus operators in the original expression, find out the maximum possible value for the expression on the papyrus paper after putting the plus and minus operators in the place of the original erased operators.

## 输入格式

The first line contains a string $ E $ $ (1<=|E|<=10^{4}) $ — a valid Ahmes arithmetic expression. All operators are erased and replaced with '?'.

The second line contains two space-separated integers $ P $ and $ M $ ( $ 0<=min(P,M)<=100 $ ) — the number of plus and minus operators, respectively.

It is guaranteed that $ P+M= $ the number of erased operators.

## 输出格式

Print one line containing the answer to the problem.

## 说明/提示

- The first sample will be $ (1+1)=2 $ .
- The second sample will be $ (2+(1-2))=1 $ .
- The third sample will be $ ((1-(5-7))+((6+2)+7))=18 $ .
- The fourth sample will be $ ((1+(5+7))-((6-2)-7))=16 $ .

## 样例 #1

### 输入

```
(1?1)
1 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
(2?(1?2))
1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
((1?(5?7))?((6?2)?7))
3 2

```

### 输出

```
18

```

## 样例 #4

### 输入

```
((1?(5?7))?((6?2)?7))
2 3

```

### 输出

```
16

```

