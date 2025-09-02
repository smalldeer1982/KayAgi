# Easy As ABC

## 题目描述

You are playing a word puzzle. The puzzle starts with a $ 3 $ by $ 3 $ grid, where each cell contains either the letter A, B, or C.

The goal of this puzzle is to find the lexicographically smallest possible word of length $ 3 $ . The word can be formed by choosing three different cells where the cell containing the first letter is adjacent to the cell containing the second letter, and the cell containing the second letter is adjacent to the cell containing the third letter.

Two cells are adjacent to each other if they share a border or a corner, as shown in the following illustration. Formally, if $ (r, c) $ denotes the cell in the $ r $ -th row and $ c $ -th column, then cell $ (r, c) $ is adjacent to cell $ (r, c + 1) $ , $ (r - 1, c + 1) $ , $ (r - 1, c) $ , $ (r - 1, c - 1) $ , $ (r, c - 1) $ , $ (r + 1, c - 1) $ , $ (r + 1, c) $ , and $ (r + 1, c + 1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/525e4da2ea69e21f85179b7ddc65c24b70ec2325.png)Determine the lexicographically smallest possible word of length $ 3 $ that you can find within the grid.

A string $ s $ of length $ n $ is lexicographically smaller than string $ t $ of the same length if there exists an integer $ 1 \leq i \leq n $ such that $ s_j = t_j $ for all $ 1 \leq j < i $ , and $ s_i < t_i $ in alphabetical order. The following illustration shows some examples on some grids and their the lexicographically smallest possible word of length $ 3 $ that you can find within the grids.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/2e823a64da2250303d9d2bed5748864eed6f5643.png)

## 样例 #1

### 输入

```
BCB
CAC
BCB```

### 输出

```
ABC```

## 样例 #2

### 输入

```
BCB
CCC
CCA```

### 输出

```
ACB```

## 样例 #3

### 输入

```
ACA
CBC
ACA```

### 输出

```
ABA```

## 样例 #4

### 输入

```
ACA
CAC
ACA```

### 输出

```
AAA```

## 样例 #5

### 输入

```
CCC
CBC
CCC```

### 输出

```
BCC```

