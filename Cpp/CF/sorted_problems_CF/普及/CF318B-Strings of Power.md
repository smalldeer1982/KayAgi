---
title: "Strings of Power"
layout: "post"
diff: 普及/提高-
pid: CF318B
tag: []
---

# Strings of Power

## 题目描述

Volodya likes listening to heavy metal and (occasionally) reading. No wonder Volodya is especially interested in texts concerning his favourite music style.

Volodya calls a string powerful if it starts with "heavy" and ends with "metal". Finding all powerful substrings (by substring Volodya means a subsequence of consecutive characters in a string) in a given text makes our hero especially joyful. Recently he felt an enormous fit of energy while reading a certain text. So Volodya decided to count all powerful substrings in this text and brag about it all day long. Help him in this difficult task. Two substrings are considered different if they appear at the different positions in the text.

For simplicity, let us assume that Volodya's text can be represented as a single string.

## 输入格式

Input contains a single non-empty string consisting of the lowercase Latin alphabet letters. Length of this string will not be greater than $ 10^{6} $ characters.

## 输出格式

Print exactly one number — the number of powerful substrings of the given string.

Please, do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample the string "heavymetalisheavymetal" contains powerful substring "heavymetal" twice, also the whole string "heavymetalisheavymetal" is certainly powerful.

In the second sample the string "heavymetalismetal" contains two powerful substrings: "heavymetal" and "heavymetalismetal".

## 样例 #1

### 输入

```
heavymetalisheavymetal

```

### 输出

```
3
```

## 样例 #2

### 输入

```
heavymetalismetal

```

### 输出

```
2
```

## 样例 #3

### 输入

```
trueheavymetalissotruewellitisalsosoheavythatyoucanalmostfeeltheweightofmetalonyou

```

### 输出

```
3
```

