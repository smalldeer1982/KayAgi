---
title: "DANCE - The Gordian Dance"
layout: "post"
diff: 难度0
pid: SP60
tag: []
---

# DANCE - The Gordian Dance

## 题目描述

 The Gordian Dance is a traditional Bytelandian dance performed by two pairs of dancers. At the beginning the dancers are standing in the corners of the square _ABCD_, forming two pairs: _A-B_ and _C-D_. Every pair is holding an outstretched string. So in the starting position both strings are stretched horizontally and parallel.

 ![The starting position of dancers.](https://cdn.luogu.com.cn/upload/vjudge_pic/SP60/9186792c446cf7f1eb800cc1d312ad86e27b5ebe.png)The dance consists of a series of moves. There are two kinds of moves:

- (_S_) The dancers standing at points _B_ and _C_ swap positions (without releasing their strings) in such a way that the dancer standing at _B_ raises the hand in which he is holding the string and, when going to point _C_, lets the dancer going from _C_ to _B_ pass in front of him, under his arm.
- (_R_) All dancers make a turn by 90 degrees clockwise without releasing their strings. This means that the dancer from _A_ goes to _B_, the dancer from _B_ goes to _C_, the dancer from _C_ goes to _D_, and the dancer from _D_ goes to _A_.

## 输入格式

 Ten test cases (given one under another, you have to process all!). The first line of each test case consists of one integer _n_ equal to the nmber of moves already made, _0<=n<=1000000_. The second line of each test case consists of one word of length _n_, made up of letters _S_ and/or _R_.

## 输出格式

 For every testcase your program should write to standard output only one line with one integer number: the minimal number of moves required to untangle the strings and stretch them horizontally and parallel.

## 样例 #1

### 输入

```
2
SS
[and 9 test cases more]
```

### 输出

```
5
[and 9 test cases more]
```

