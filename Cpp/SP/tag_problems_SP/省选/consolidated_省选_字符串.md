---
title: "VIDEO - Video game combos"
layout: "post"
diff: 省选/NOI-
pid: SP10502
tag: ['字符串', '动态规划 DP']
---

# VIDEO - Video game combos

## 题目描述

 Bessie is playing a video game! In the game, the three letters 'A', 'B', and 'C' are the only valid buttons. Bessie may press the buttons in any order she likes. However, there are only N distinct combos possible (1 <= N <= 20). Combo i is represented as a string S\_i which has a length between 1 and 15 and contains only the letters 'A', 'B', and 'C'.

 Whenever Bessie presses a combination of letters that matches with a combo, she gets one point for the combo. Combos may overlap with each other or even finish at the same time! For example if N = 3 and the three possible combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will end with 3 points. Bessie may score points for a single combo more than once.

 Bessie of course wants to earn points as quickly as possible. If she presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of points she can earn?

## 样例 #1

### 输入

```
3 7
ABA
CB
ABACB
```

### 输出

```
4
```



---

---
title: "LCS - Longest Common Substring"
layout: "post"
diff: 省选/NOI-
pid: SP1811
tag: ['字符串', '后缀自动机 SAM', '后缀数组 SA', '构造']
---

# LCS - Longest Common Substring

## 题目描述

A string is finite sequence of characters over a non-empty finite set Σ.

In this problem, Σ is the set of lowercase letters.

Substring, also called factor, is a consecutive sequence of characters occurrences at least once in a string.

Now your task is simple, for two given strings, find the length of the longest common substring of them.

Here common substring means a substring of two or more strings.

## 输入格式

The input contains exactly two lines, each line consists of no more than 250000 lowercase letters, representing a string.

## 输出格式

The length of the longest common substring. If such string doesn't exist, print "0" instead.

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla
```

### 输出

```
3
```



---

---
title: "LCS2 - Longest Common Substring II"
layout: "post"
diff: 省选/NOI-
pid: SP1812
tag: ['字符串', '后缀自动机 SAM', '后缀数组 SA']
---

# LCS2 - Longest Common Substring II

## 题目描述

题面描述
给定一些字符串，求出它们的最长公共子串

## 输入格式

输入至多$10$ 行，每行包含不超过$100000$ 个的小写字母，表示一个字符串

## 输出格式

一个数，最长公共子串的长度
若不存在最长公共子串，请输出$0$ 。

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla
aaaajfaaaa
```

### 输出

```
2
```



---

---
title: "WORDRING - Word Rings"
layout: "post"
diff: 省选/NOI-
pid: SP2885
tag: ['字符串', '队列']
---

# WORDRING - Word Rings

## 题目描述

如果字符串A的**结尾两个**字符与字符串B的**开头两个**字符相匹配，我们称A与B能 **“ 相连 ”** ( 注意：A与B能相连，不代表B与A能相连 ) 

 当若干个串首尾 “ 相连 ” 成一个环时，我们称之为一个环串（一个串首尾相连也算） 

 我们希望从给定的全小写字符串中找出一个环串，使这个环串的平均长度最长     
 
```
 intercommunicational
 alkylbenzenesulfonate
 tetraiodophenolphthalein
```

如上例：第一个串能与第二个串相连，第二个串能与第三个串相连，第三个串又能与第一个串相连。按此顺序连接，便形成了一个环串。

长度为 20+21+24=65 ( **首尾重复部分需计算两次** ) ，总共使用了3个串，所以平均长度是 65/3≈21.6666

## 输入格式

多组数据  
 每组数据第一行一个整数n，表示字符串数量   
 接下来n行每行一个长度**小于等于1000**的字符串  
 读入以n=0结束

## 输出格式

若不存在环串，输出"No solution."。否则输出最长的环串平均长度。

Translated by @远藤沙椰

## 样例 #1

### 输入

```
3
intercommunicational
alkylbenzenesulfonate
tetraiodophenolphthalein
0
```

### 输出

```
21.66
```



---

