---
title: "Puzzle Lover"
layout: "post"
diff: 省选/NOI-
pid: CF613E
tag: []
---

# Puzzle Lover

## 题目描述

Oleg Petrov loves crossword puzzles and every Thursday he buys his favorite magazine with crosswords and other word puzzles. In the last magazine Oleg found a curious puzzle, and the magazine promised a valuable prize for it's solution. We give a formal description of the problem below.

The puzzle field consists of two rows, each row contains $ n $ cells. Each cell contains exactly one small English letter. You also are given a word $ w $ , which consists of $ k $ small English letters. A solution of the puzzle is a sequence of field cells $ c_{1} $ , $ ... $ , $ c_{k} $ , such that:

- For all $ i $ from $ 1 $ to $ k $ the letter written in the cell $ c_{i} $ matches the letter $ w_{i} $ ;
- All the cells in the sequence are pairwise distinct;
- For all $ i $ from $ 1 $ to $ k-1 $ cells $ c_{i} $ and $ c_{i+1} $ have a common side.

Oleg Petrov quickly found a solution for the puzzle. Now he wonders, how many distinct solutions are there for this puzzle. Oleg Petrov doesn't like too large numbers, so calculate the answer modulo $ 10^{9}+7 $ .

Two solutions $ c_{i} $ and $ c'_{i} $ are considered distinct if the sequences of cells do not match in at least one position, that is there is such $ j $ in range from $ 1 $ to $ k $ , such that $ c_{j}≠c'_{j} $ .

## 输入格式

The first two lines contain the state of the field for the puzzle. Each of these non-empty lines contains exactly $ n $ small English letters.

The next line is left empty.

The next line is non-empty and contains word $ w $ , consisting of small English letters.

The length of each line doesn't exceed $ 2000 $ .

## 输出格式

Print a single integer — the number of distinct solutions for the puzzle modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
code
edoc

code

```

### 输出

```
4

```

## 样例 #2

### 输入

```
aaa
aaa

aa

```

### 输出

```
14

```

