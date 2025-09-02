---
title: "Did you mean..."
layout: "post"
diff: 普及/提高-
pid: CF858C
tag: []
---

# Did you mean...

## 题目描述

Beroffice text editor has a wide range of features that help working with text. One of the features is an automatic search for typos and suggestions of how to fix them.

Beroffice works only with small English letters (i.e. with 26 letters from a to z). Beroffice thinks that a word is typed with a typo if there are three or more consonants in a row in the word. The only exception is that if the block of consonants has all letters the same, then this block (even if its length is greater than three) is not considered a typo. Formally, a word is typed with a typo if there is a block of not less that three consonants in a row, and there are at least two different letters in this block.

For example:

- the following words have typos: "hellno", "hackcerrs" and "backtothefutttture";
- the following words don't have typos: "helllllooooo", "tobeornottobe" and "oooooo".

When Beroffice editor finds a word with a typo, it inserts as little as possible number of spaces in this word (dividing it into several words) in such a way that each of the resulting words is typed without any typos.

Implement this feature of Beroffice editor. Consider the following letters as the only vowels: 'a', 'e', 'i', 'o' and 'u'. All the other letters are consonants in this problem.

## 输入格式

The only line contains a non-empty word consisting of small English letters. The length of the word is between $ 1 $ and $ 3000 $ letters.

## 输出格式

Print the given word without any changes if there are no typos.

If there is at least one typo in the word, insert the minimum number of spaces into the word so that each of the resulting words doesn't have any typos. If there are multiple solutions, print any of them.

## 样例 #1

### 输入

```
hellno

```

### 输出

```
hell no 

```

## 样例 #2

### 输入

```
abacaba

```

### 输出

```
abacaba 

```

## 样例 #3

### 输入

```
asdfasdf

```

### 输出

```
asd fasd f 

```

