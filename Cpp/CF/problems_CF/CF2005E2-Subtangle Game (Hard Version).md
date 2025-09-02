---
title: "Subtangle Game (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2005E2
tag: ['动态规划 DP']
---

# Subtangle Game (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are the constraints on all the variables. You can make hacks only if both versions of the problem are solved.

Tsovak and Narek are playing a game. They have an array $ a $ and a matrix $ b $ of integers with $ n $ rows and $ m $ columns, numbered from $ 1 $ . The cell in the $ i $ -th row and the $ j $ -th column is $ (i, j) $ .

They are looking for the elements of $ a $ in turns; Tsovak starts first. Each time a player looks for a cell in the matrix containing the current element of $ a $ (Tsovak looks for the first, then Narek looks for the second, etc.). Let's say a player has chosen the cell $ (r, c) $ . The next player has to choose his cell in the submatrix starting at $ (r + 1, c + 1) $ and ending in $ (n, m) $ (the submatrix can be empty if $ r=n $ or $ c=m $ ). If a player cannot find such a cell (or the remaining submatrix is empty) or the array ends (the previous player has chosen the last element), then he loses.

Your task is to determine the winner if the players play optimally.

Note: since the input is large, you may need to optimize input/output for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    ios_base::sync_with_stdio(false);<br></br>    cin.tie(NULL); cout.tie(NULL);<br></br>}<br></br>
```
```

## 输入格式

The first line of the input contains $ t $ ( $ 1 \le t \le 1500 $ ) – the number of test cases.

The first line of each test case contains three integers $ l $ , $ n $ , and $ m $ ( $ 1 \le l, n, m \le 1500 $ ) – the size of the array and the sizes of the matrix.

The second line contains $ l $ integers $ a_1, a_2, a_3, \ldots a_l $ ( $ 1 \le a_i \le n \cdot m $ ) – the elements of the array $ a $ .

The $ i $ -th of the last $ n $ lines contains $ m $ integers $ b_{i,1}, b_{i,2}, b_{i,3}, \ldots b_{i,m} $ ( $ 1 \le b_{i,j} \le n \cdot m $ ) – representing the $ i $ -th row of the matrix.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 3 \cdot 10^6 $ .

It is guaranteed that the sum of $ l $ over all test cases does not exceed $ 1500 $ .

## 输出格式

You should output $ t $ lines, the $ i $ -th of them containing a character representing the answer of the $ i $ -th test case: "T" if Tsovak wins or "N", otherwise (without quotes).

## 说明/提示

In the first example, Tsovak starts by looking for $ 1 $ . There is only one occurrence of $ 1 $ at $ (1,1) $ , so he chooses it. Then Narek needs to look for $ 2 $ in the submatrix of $ (2, 2) $ , which consists of just the last two elements: $ 6 $ and $ 2 $ . He chooses $ 2 $ , and then Tsovak loses since the array has ended.

In the second example, Tsovak needs to choose $ 1 $ . There is a $ 1 $ at the cell $ (n,m) $ , so he chooses that cell. Then, since the submatrix of $ (n + 1, m + 1) $ is empty, Narek cannot find $ 2 $ , so he loses.

## 样例 #1

### 输入

```
3
2 2 3
1 2
1 3 6
4 6 2
2 2 4
1 2
1 1 3 2
4 2 5 1
2 4 2
1 2
3 4
5 6
7 8
8 8
```

### 输出

```
N
T
N
```

