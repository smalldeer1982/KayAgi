---
title: "Sweep Line"
layout: "post"
diff: 难度0
pid: CF1952E
tag: []
---

# Sweep Line

## 题目描述

Be careful not to make a mistake. You might have to start all over again.

— Someone, probably

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 2 $ ) — the array $ a $ .

## 输出格式

Output a single integer — the number of solutions, modulo $ 20240401 $ .

## 说明/提示

In the first sample, the array looks like this:

 $  \color{blue}{1}  $  $  \color{blue}{1}  $  $  \color{darkgreen}{2}  $  $  \color{blue}{1}  $  $  \color{blue}{1}  $  $  \color{darkgreen}{2}  $  $  \color{gray}{0}  $ Obviously, the answer here is $ 1 \pmod{20240401} $ .

In the second sample, the array looks like this:

 $  \color{blue}{1}  $  $  \color{blue}{1}  $  $  \color{darkgreen}{2}  $  $  \color{blue}{1}  $  $  \color{blue}{1}  $  $  \color{blue}{1}  $  $  \color{gray}{0}  $ I do not know why the answer here is $ 2 \pmod{20240401} $ , I had to take a guess.

In the third sample, the array looks like this:

 $  \color{gray}{0}  $  $  \color{blue}{1}  $  $  \color{darkgreen}{2}  $  $  \color{blue}{1}  $  $  \color{blue}{1}  $  $  \color{blue}{1}  $  $  \color{gray}{0}  $ If the answer here is not $ 0 \pmod{20240401} $ , I am literally going to explode.

## 样例 #1

### 输入

```
7
1 1 2 1 1 2 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
1 1 2 1 1 1 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
0 1 2 1 1 1 0
```

### 输出

```
0
```

