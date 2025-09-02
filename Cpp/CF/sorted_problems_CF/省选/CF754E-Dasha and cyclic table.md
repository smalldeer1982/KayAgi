---
title: "Dasha and cyclic table"
layout: "post"
diff: 省选/NOI-
pid: CF754E
tag: ['字符串']
---

# Dasha and cyclic table

## 题目描述

Dasha is fond of challenging puzzles: Rubik's Cube $ 3×3×3 $ , $ 4×4×4 $ , $ 5×5×5 $ and so on. This time she has a cyclic table of size $ n×m $ , and each cell of the table contains a lowercase English letter. Each cell has coordinates $ (i,j) $ ( $ 0<=i&lt;n $ , $ 0<=j&lt;m $ ). The table is cyclic means that to the right of cell $ (i,j) $ there is the cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/a5d005af310d530b73654f2e5c374c68f16d2ee4.png), and to the down there is the cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/1a381522c9ac4a424562398196989e9e4585022e.png).

Dasha has a pattern as well. A pattern is a non-cyclic table of size $ r×c $ . Each cell is either a lowercase English letter or a question mark. Each cell has coordinates $ (i,j) $ ( $ 0<=i&lt;r $ , $ 0<=j&lt;c $ ).

The goal of the puzzle is to find all the appearance positions of the pattern in the cyclic table.

We say that the cell $ (i,j) $ of cyclic table is an appearance position, if for every pair $ (x,y) $ such that $ 0<=x&lt;r $ and $ 0<=y&lt;c $ one of the following conditions holds:

- There is a question mark in the cell $ (x,y) $ of the pattern, or
- The cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF754E/54ce001d702da711f4c8fe98e24e25993cb660d2.png) of the cyclic table equals to the cell $ (x,y) $ of the pattern.

Dasha solved this puzzle in no time, as well as all the others she ever tried. Can you solve it?.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=400 $ ) — the cyclic table sizes.

Each of the next $ n $ lines contains a string of $ m $ lowercase English characters — the description of the cyclic table.

The next line contains two integers $ r $ and $ c $ ( $ 1<=r,c<=400 $ ) — the sizes of the pattern.

Each of the next $ r $ lines contains a string of $ c $ lowercase English letter and/or characters '?' — the description of the pattern.

## 输出格式

Print $ n $ lines. Each of the $ n $ lines should contain $ m $ characters. Each of the characters should equal '0' or '1'.

The $ j $ -th character of the $ i $ -th ( $ 0 $ -indexed) line should be equal to '1', in case the cell $ (i,j) $ is an appearance position, otherwise it should be equal to '0'.

## 样例 #1

### 输入

```
5 7
qcezchs
hhedywq
wikywqy
qckrqzt
bqexcxz
3 2
??
yw
?q

```

### 输出

```
0000100
0001001
0000000
0000000
0000000

```

## 样例 #2

### 输入

```
10 10
fwtoayylhw
yyaryyjawr
ywrdzwhscy
hnsyyxiphn
bnjwzyyjvo
kkjgseenwn
gvmiflpcsy
lxvkwrobwu
wyybbcocyy
yysijsvqry
2 2
??
yy

```

### 输出

```
1000100000
0000000001
0001000000
0000010000
0000000000
0000000000
0000000000
0100000010
1000000001
0000010000

```

## 样例 #3

### 输入

```
8 6
ibrgxl
xqdcsg
okbcgi
tvpetc
xgxxig
igghzo
lmlaza
gpswzv
1 4
gx??

```

### 输出

```
000100
000001
000000
000000
010001
000000
000000
000000

```

