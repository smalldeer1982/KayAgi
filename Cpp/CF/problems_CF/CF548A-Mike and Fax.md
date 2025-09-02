---
title: "Mike and Fax"
layout: "post"
diff: 普及-
pid: CF548A
tag: []
---

# Mike and Fax

## 题目描述

While Mike was walking in the subway, all the stuff in his back-bag dropped on the ground. There were several fax messages among them. He concatenated these strings in some order and now he has string $ s $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF548A/8e6eb6a5966077211062d31ebdd4df5e9f389a77.png)He is not sure if this is his own back-bag or someone else's. He remembered that there were exactly $ k $ messages in his own bag, each was a palindrome string and all those strings had the same length.

He asked you to help him and tell him if he has worn his own back-bag. Check if the given string $ s $ is a concatenation of $ k $ palindromes of the same length.

## 输入格式

The first line of input contains string $ s $ containing lowercase English letters ( $ 1<=|s|<=1000 $ ).

The second line contains integer $ k $ ( $ 1<=k<=1000 $ ).

## 输出格式

Print "YES"(without quotes) if he has worn his own back-bag or "NO"(without quotes) otherwise.

## 说明/提示

Palindrome is a string reading the same forward and backward.

In the second sample, the faxes in his back-bag can be "saddas" and "tavvat".

## 样例 #1

### 输入

```
saba
2

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
saddastavvat
2

```

### 输出

```
YES

```

