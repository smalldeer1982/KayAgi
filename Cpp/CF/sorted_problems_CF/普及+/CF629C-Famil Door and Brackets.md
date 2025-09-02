---
title: "Famil Door and Brackets"
layout: "post"
diff: 普及+/提高
pid: CF629C
tag: []
---

# Famil Door and Brackets

## 题目描述

As Famil Door’s birthday is coming, some of his friends (like Gabi) decided to buy a present for him. His friends are going to buy a string consisted of round brackets since Famil Door loves string of brackets of length $ n $ more than any other strings!

The sequence of round brackets is called valid if and only if:

1. the total number of opening brackets is equal to the total number of closing brackets;
2. for any prefix of the sequence, the number of opening brackets is greater or equal than the number of closing brackets.

Gabi bought a string $ s $ of length $ m $ ( $ m<=n $ ) and want to complete it to obtain a valid sequence of brackets of length $ n $ . He is going to pick some strings $ p $ and $ q $ consisting of round brackets and merge them in a string $ p+s+q $ , that is add the string $ p $ at the beginning of the string $ s $ and string $ q $ at the end of the string $ s $ .

Now he wonders, how many pairs of strings $ p $ and $ q $ exists, such that the string $ p+s+q $ is a valid sequence of round brackets. As this number may be pretty large, he wants to calculate it modulo $ 10^{9}+7 $ .

## 输入格式

First line contains $ n $ and $ m $ ( $ 1<=m<=n<=100000,n-m<=2000 $ ) — the desired length of the string and the length of the string bought by Gabi, respectively.

The second line contains string $ s $ of length $ m $ consisting of characters '(' and ')' only.

## 输出格式

Print the number of pairs of string $ p $ and $ q $ such that $ p+s+q $ is a valid sequence of round brackets modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample there are four different valid pairs:

1. $ p= $ "(", $ q= $ "))"
2. $ p= $ "()", $ q= $ ")"
3. $ p= $ "", $ q= $ "())"
4. $ p= $ "", $ q= $ ")()"

In the second sample the only way to obtain a desired string is choose empty $ p $ and $ q $ .

In the third sample there is no way to get a valid sequence of brackets.

## 样例 #1

### 输入

```
4 1
(

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4 4
(())

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 3
(((

```

### 输出

```
0

```

