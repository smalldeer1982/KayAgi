---
title: "CLOCKS - The Clocks"
layout: "post"
diff: 提高+/省选-
pid: SP7216
tag: []
---

# CLOCKS - The Clocks

## 题目描述

 ```
|-------|    |-------|    |-------|    
|       |    |       |    |   |   |    
|---O   |    |---O   |    |   O   |          
|       |    |       |    |       |           
|-------|    |-------|    |-------|    
    A            B            C

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O   |    |   O   |
|   |   |    |   |   |    |   |   |
|-------|    |-------|    |-------|
    D            E            F

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O---|    |   O   |
|   |   |    |       |    |   |   |
|-------|    |-------|    |-------|  (Figure 1)
    G            H            I
```
- - - - - -

There are nine clocks in a 3\*3 array (figure 1). The goal is to return all the dials to 12 o'clock with as few moves as possible. There are nine different allowed ways to turn the dials on the clocks. Each such way is called a move. Select for each move a number 1 to 9. That number will turn the dials 90' (degrees) clockwise on those clocks which are affected according to figure 2 below.

 ```
Move   Affected clocks
 
 1         ABDE
 2         ABC
 3         BCEF
 4         ADG
 5         BDEFH
 6         CFI
 7         DEGH
 8         GHI
 9         EFHI    (Figure 2)
```

## 输入格式

Read nine numbers from standard input. These numbers give the start positions of the dials. 0=12 o'clock, 1=3 o'clock, 2=6 o'clock, 3=9 o'clock. The example in figure 1 gives the following input data file:

 ```
3 3 0
2 2 2 
2 1 2
```

## 输出格式

Write to the standard output the shortest sequence of moves (numbers), which returns all the dials to 12 o'clock. In case there are many solutions, write the solution which is the least in lexicographic order. In our example the output is as follows:

 ```
4 5 8 9
```

