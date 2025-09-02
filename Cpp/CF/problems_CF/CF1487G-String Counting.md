---
title: "String Counting"
layout: "post"
diff: 省选/NOI-
pid: CF1487G
tag: []
---

# String Counting

## 题目描述

You have $ c_1 $ letters 'a', $ c_2 $ letters 'b', ..., $ c_{26} $ letters 'z'. You want to build a beautiful string of length $ n $ from them (obviously, you cannot use the $ i $ -th letter more than $ c_i $ times). Each $ c_i $ is greater than $ \frac{n}{3} $ .

A string is called beautiful if there are no palindromic contiguous substrings of odd length greater than $ 1 $ in it. For example, the string "abacaba" is not beautiful, it has several palindromic substrings of odd length greater than $ 1 $ (for example, "aca"). Another example: the string "abcaa" is beautiful.

Calculate the number of different strings you can build, and print the answer modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 3 \le n \le 400 $ ).

The second line contains $ 26 $ integers $ c_1 $ , $ c_2 $ , ..., $ c_{26} $ ( $ \frac{n}{3} < c_i \le n $ ).

## 输出格式

Print one integer — the number of strings you can build, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
```

### 输出

```
422500
```

## 样例 #2

### 输入

```
3
2 2 2 2 2 2 3 3 3 2 2 2 2 2 2 3 3 3 2 2 3 2 2 3 2 2
```

### 输出

```
16900
```

## 样例 #3

### 输入

```
400
348 322 247 158 209 134 151 267 268 176 214 379 372 291 388 135 147 304 169 149 193 351 380 368 181 340
```

### 输出

```
287489790
```

