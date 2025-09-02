---
title: "Magazine Ad"
layout: "post"
diff: 普及+/提高
pid: CF803D
tag: []
---

# Magazine Ad

## 题目描述

The main city magazine offers its readers an opportunity to publish their ads. The format of the ad should be like this:

There are space-separated non-empty words of lowercase and uppercase Latin letters.

There are hyphen characters '-' in some words, their positions set word wrapping points. Word can include more than one hyphen.

It is guaranteed that there are no adjacent spaces and no adjacent hyphens. No hyphen is adjacent to space. There are no spaces and no hyphens before the first word and after the last word.

When the word is wrapped, the part of the word before hyphen and the hyphen itself stay on current line and the next part of the word is put on the next line. You can also put line break between two words, in that case the space stays on current line. Check notes for better understanding.

The ad can occupy no more that $ k $ lines and should have minimal width. The width of the ad is the maximal length of string (letters, spaces and hyphens are counted) in it.

You should write a program that will find minimal width of the ad.

## 输入格式

The first line contains number $ k $ ( $ 1<=k<=10^{5} $ ).

The second line contains the text of the ad — non-empty space-separated words of lowercase and uppercase Latin letters and hyphens. Total length of the ad don't exceed $ 10^{6} $ characters.

## 输出格式

Output minimal width of the ad.

## 说明/提示

Here all spaces are replaced with dots.

In the first example one of possible results after all word wraps looks like this:

`<br></br>garage.<br></br>for.<br></br>sa-<br></br>le<br></br>`The second example:

`<br></br>Edu-ca-<br></br>tion-al.<br></br>Ro-unds.<br></br>are.so.fun<br></br>`

## 样例 #1

### 输入

```
4
garage for sa-le

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4
Edu-ca-tion-al Ro-unds are so fun

```

### 输出

```
10

```

