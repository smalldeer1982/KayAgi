---
title: "Multithreading"
layout: "post"
diff: 省选/NOI-
pid: CF26E
tag: []
---

# Multithreading

## 题目描述

You are given the following concurrent program. There are $ N $ processes and the $ i $ -th process has the following pseudocode:

`repeat  $ n_{i} $  times<br></br>     $ y_{i} $  :=  $ y $ <br></br>     $ y $  :=  $ y_{i}+1 $ <br></br>end repeat<br></br>`Here $ y $ is a shared variable. Everything else is local for the process. All actions on a given row are atomic, i.e. when the process starts executing a row it is never interrupted. Beyond that all interleavings are possible, i.e. every process that has yet work to do can be granted the rights to execute its next row. In the beginning $ y=0 $ . You will be given an integer $ W $ and $ n_{i} $ , for $ i=1,...\ ,N $ . Determine if it is possible that after all processes terminate, $ y=W $ , and if it is possible output an arbitrary schedule that will produce this final value.

## 输入格式

In the first line of the input you will be given two space separated integers $ N $ ( $ 1<=N<=100 $ ) and $ W $ ( $ -10^{9}<=W<=10^{9} $ ). In the second line there are $ N $ space separated integers $ n_{i} $ ( $ 1<=n_{i}<=1000 $ ).

## 输出格式

On the first line of the output write Yes if it is possible that at the end $ y=W $ , or No otherwise. If the answer is No then there is no second line, but if the answer is Yes, then on the second line output a space separated list of integers representing some schedule that leads to the desired result. For more information see note.

## 说明/提示

For simplicity, assume that there is no repeat statement in the code of the processes, but the code from the loop is written the correct amount of times. The processes are numbered starting from 1. The list of integers represent which process works on its next instruction at a given step. For example, consider the schedule 1 2 2 1 3. First process 1 executes its first instruction, then process 2 executes its first two instructions, after that process 1 executes its second instruction, and finally process 3 executes its first instruction. The list must consists of exactly $ 2·Σ\ _{i=1...N}n_{i} $ numbers.

## 样例 #1

### 输入

```
1 10
11

```

### 输出

```
No

```

## 样例 #2

### 输入

```
2 3
4 4

```

### 输出

```
Yes
1 1 2 1 2 2 2 2 2 1 2 1 1 1 1 2

```

## 样例 #3

### 输入

```
3 6
1 2 3

```

### 输出

```
Yes
1 1 2 2 2 2 3 3 3 3 3 3

```

