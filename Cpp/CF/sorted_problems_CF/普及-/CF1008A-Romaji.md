---
title: "Romaji"
layout: "post"
diff: 普及-
pid: CF1008A
tag: ['字符串']
---

# Romaji

## 题目描述

Vitya has just started learning Berlanese language. It is known that Berlanese uses the Latin alphabet. Vowel letters are "a", "o", "u", "i", and "e". Other letters are consonant.

In Berlanese, there has to be a vowel after every consonant, but there can be any letter after any vowel. The only exception is a consonant "n"; after this letter, there can be any letter (not only a vowel) or there can be no letter at all. For example, the words "harakiri", "yupie", "man", and "nbo" are Berlanese while the words "horse", "king", "my", and "nz" are not.

Help Vitya find out if a word $ s $ is Berlanese.

## 输入格式

The first line of the input contains the string $ s $ consisting of $ |s| $ ( $ 1\leq |s|\leq 100 $ ) lowercase Latin letters.

## 输出格式

Print "YES" (without quotes) if there is a vowel after every consonant except "n", otherwise print "NO".

You can print each letter in any case (upper or lower).

## 说明/提示

In the first and second samples, a vowel goes after each consonant except "n", so the word is Berlanese.

In the third sample, the consonant "c" goes after the consonant "r", and the consonant "s" stands on the end, so the word is not Berlanese.

## 样例 #1

### 输入

```
sumimasen

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
ninja

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
codeforces

```

### 输出

```
NO

```

