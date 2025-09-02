---
title: "Haiku"
layout: "post"
diff: 入门
pid: CF78A
tag: ['模拟', '概率论']
---

# Haiku

## 题目描述

Haiku is a genre of Japanese traditional poetry.

A haiku poem consists of 17 syllables split into three phrases, containing 5, 7 and 5 syllables correspondingly (the first phrase should contain exactly 5 syllables, the second phrase should contain exactly 7 syllables, and the third phrase should contain exactly 5 syllables). A haiku masterpiece contains a description of a moment in those three phrases. Every word is important in a small poem, which is why haiku are rich with symbols. Each word has a special meaning, a special role. The main principle of haiku is to say much using a few words.

To simplify the matter, in the given problem we will consider that the number of syllable in the phrase is equal to the number of vowel letters there. Only the following letters are regarded as vowel letters: "a", "e", "i", "o" and "u".

Three phases from a certain poem are given. Determine whether it is haiku or not.

## 输入格式

The input data consists of three lines. The length of each line is between $ 1 $ and $ 100 $ , inclusive. The $ i $ -th line contains the $ i $ -th phrase of the poem. Each phrase consists of one or more words, which are separated by one or more spaces. A word is a non-empty sequence of lowercase Latin letters. Leading and/or trailing spaces in phrases are allowed. Every phrase has at least one non-space character. See the example for clarification.

## 输出格式

Print "YES" (without the quotes) if the poem is a haiku. Otherwise, print "NO" (also without the quotes).

## 样例 #1

### 输入

```
on  codeforces 
beta round is running
   a rustling of keys 

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
how many gallons
of edo s rain did you drink
                                cuckoo

```

### 输出

```
NO
```

