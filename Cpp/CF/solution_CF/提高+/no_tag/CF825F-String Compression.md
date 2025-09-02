# String Compression

## 题目描述

Ivan wants to write a letter to his friend. The letter is a string $ s $ consisting of lowercase Latin letters.

Unfortunately, when Ivan started writing the letter, he realised that it is very long and writing the whole letter may take extremely long time. So he wants to write the compressed version of string $ s $ instead of the string itself.

The compressed version of string $ s $ is a sequence of strings $ c_{1},s_{1},c_{2},s_{2},...,c_{k},s_{k} $ , where $ c_{i} $ is the decimal representation of number $ a_{i} $ (without any leading zeroes) and $ s_{i} $ is some string consisting of lowercase Latin letters. If Ivan writes string $ s_{1} $ exactly $ a_{1} $ times, then string $ s_{2} $ exactly $ a_{2} $ times, and so on, the result will be string $ s $ .

The length of a compressed version is $ |c_{1}|+|s_{1}|+|c_{2}|+|s_{2}|...\ |c_{k}|+|s_{k}| $ . Among all compressed versions Ivan wants to choose a version such that its length is minimum possible. Help Ivan to determine minimum possible length.

## 说明/提示

In the first example Ivan will choose this compressed version: $ c_{1} $ is 10, $ s_{1} $ is a.

In the second example Ivan will choose this compressed version: $ c_{1} $ is 1, $ s_{1} $ is abcab.

In the third example Ivan will choose this compressed version: $ c_{1} $ is 2, $ s_{1} $ is c, $ c_{2} $ is 1, $ s_{2} $ is z, $ c_{3} $ is 4, $ s_{3} $ is ab.

## 样例 #1

### 输入

```
aaaaaaaaaa
```

### 输出

```
3
```

## 样例 #2

### 输入

```
abcab
```

### 输出

```
6
```

## 样例 #3

### 输入

```
cczabababab
```

### 输出

```
7
```

