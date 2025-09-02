---
title: "Cracking the Code"
layout: "post"
diff: 普及/提高-
pid: CF630L
tag: []
---

# Cracking the Code

## 题目描述

### 题意简述
给出一个五位数

我们设这个这个五位数的各个数位上的数字分别为<first digit><second digit><third digit><fourth digit><fifth digit>
  
现在我们把这个数各个数位上的数字按如下方式排列成新的数：<first digit><third digit><fifth digit><fourth digit><second digit>
  
然后我们要求其五次幂的后五个数字
  
例如对于数字12345，重新排列后得到13542，五次幂为455 422 043 125 550 171 232，输出71232

## 输入格式

一行，长度为5的正整数，没有前导零。

## 输出格式

一行，5个数字，没有间隔符。

## 样例 #1

### 输入

```
12345

```

### 输出

```
71232
```

