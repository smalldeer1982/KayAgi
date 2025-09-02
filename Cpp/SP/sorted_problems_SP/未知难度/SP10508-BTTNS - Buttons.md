---
title: "BTTNS - Buttons"
layout: "post"
diff: 难度0
pid: SP10508
tag: []
---

# BTTNS - Buttons

## 题目描述

  
Luis has a new toy, is a weird board with NxM cells. The cells can be white or  
black.  
Each cell has a button inside, when you press a button every cell with Manhattan  
distance equal or less than K to the cell with the button pressed change of color  
( white to black, or black to white ).  
At the beginning, every cell is white but somebody pressed some buttons and now  
the board has some black cells.  
Help Luis to find how many buttons were pressed.  
You can assume that no button will be pressed two or more times.  
There will be always only one configuration of buttons pressed that generate the  
final board.

## 输入格式

The first line of input contains an integer t<=10, the number of test cases. It is  
followed by t test cases, each consisting of N+1 lines. The first line of each case  
contains three integers N,M,K separated by space (1<=N,M<=20 , 0<=K<=20).  
The next N lines contains M integers, each integer can be 0 or 1, the final state of  
each cell. ( 0 is white, 1 is black )

## 输出格式

For each case, output a single line consisting of the number of buttons pressed.

## 样例 #1

### 输入

```
2\n2 2 0\n1 0\n0 1\n2 2 1\n1 1\n1 1
```

### 输出

```
2\n4
```

