---
title: "Bicolored RBS"
layout: "post"
diff: 普及/提高-
pid: CF1167D
tag: []
---

# Bicolored RBS

## 题目描述

A string is called bracket sequence if it does not contain any characters other than "(" and ")". A bracket sequence is called regular (shortly, RBS) if it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, "", "(())" and "()()" are RBS and ")(" and "(()" are not.

We can see that each opening bracket in RBS is paired with some closing bracket, and, using this fact, we can define nesting depth of the RBS as maximum number of bracket pairs, such that the $ 2 $ -nd pair lies inside the $ 1 $ -st one, the $ 3 $ -rd one — inside the $ 2 $ -nd one and so on. For example, nesting depth of "" is $ 0 $ , "()()()" is $ 1 $ and "()((())())" is $ 3 $ .

Now, you are given RBS $ s $ of even length $ n $ . You should color each bracket of $ s $ into one of two colors: red or blue. Bracket sequence $ r $ , consisting only of red brackets, should be RBS, and bracket sequence, consisting only of blue brackets $ b $ , should be RBS. Any of them can be empty. You are not allowed to reorder characters in $ s $ , $ r $ or $ b $ . No brackets can be left uncolored.

Among all possible variants you should choose one that minimizes maximum of $ r $ 's and $ b $ 's nesting depth. If there are multiple solutions you can print any of them.

## 输入格式

The first line contains an even integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of RBS $ s $ .

The second line contains regular bracket sequence $ s $ ( $ |s| = n $ , $ s_i \in \{ $ "(", ")" $ \} $ ).

## 输出格式

Print single string $ t $ of length $ n $ consisting of "0"-s and "1"-s. If $ t_i $ is equal to 0 then character $ s_i $ belongs to RBS $ r $ , otherwise $ s_i $ belongs to $ b $ .

## 说明/提示

In the first example one of optimal solutions is $ s =  $ " $ \color{blue}{()} $ ". $ r $ is empty and $ b =  $ " $ () $ ". The answer is $ \max(0, 1) = 1 $ .

In the second example it's optimal to make $ s =  $ " $ \color{red}{(}\color{blue}{(}\color{red}{)}\color{blue}{)} $ ". $ r = b =  $ " $ () $ " and the answer is $ 1 $ .

In the third example we can make $ s =  $ " $ \color{red}{(}\color{blue}{((}\color{red}{)()}\color{blue}{)())} $ ". $ r =  $ " $ ()() $ " and $ b =  $ " $ (()()) $ " and the answer is $ 2 $ .

## 样例 #1

### 输入

```
2
()

```

### 输出

```
11

```

## 样例 #2

### 输入

```
4
(())

```

### 输出

```
0101

```

## 样例 #3

### 输入

```
10
((()())())

```

### 输出

```
0110001111
```

