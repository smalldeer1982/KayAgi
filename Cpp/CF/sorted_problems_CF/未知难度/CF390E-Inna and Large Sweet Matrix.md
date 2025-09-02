---
title: "Inna and Large Sweet Matrix"
layout: "post"
diff: 难度0
pid: CF390E
tag: []
---

# Inna and Large Sweet Matrix

## 题目描述

Inna loves sweets very much. That's why she wants to play the "Sweet Matrix" game with Dima and Sereja. But Sereja is a large person, so the game proved small for him. Sereja suggested playing the "Large Sweet Matrix" game.

The "Large Sweet Matrix" playing field is an $ n×m $ matrix. Let's number the rows of the matrix from $ 1 $ to $ n $ , and the columns — from $ 1 $ to $ m $ . Let's denote the cell in the $ i $ -th row and $ j $ -th column as $ (i,j) $ . Each cell of the matrix can contain multiple candies, initially all cells are empty. The game goes in $ w $ moves, during each move one of the two following events occurs:

1. Sereja chooses five integers $ x_{1},y_{1},x_{2},y_{2},v $ $ (x_{1}<=x_{2},y_{1}<=y_{2}) $ and adds $ v $ candies to each matrix cell $ (i,j) $ $ (x_{1}<=i<=x_{2}; y_{1}<=j<=y_{2}) $ .
2. Sereja chooses four integers $ x_{1},y_{1},x_{2},y_{2} $ $ (x_{1}<=x_{2},y_{1}<=y_{2}) $ . Then he asks Dima to calculate the total number of candies in cells $ (i,j) $ $ (x_{1}<=i<=x_{2}; y_{1}<=j<=y_{2}) $ and he asks Inna to calculate the total number of candies in the cells of matrix $ (p,q) $ , which meet the following logical criteria: ( $ p&lt;x_{1} $ OR $ p&gt;x_{2} $ ) AND ( $ q&lt;y_{1} $ OR $ q&gt;y_{2} $ ). Finally, Sereja asks to write down the difference between the number Dima has calculated and the number Inna has calculated (D - I).

Unfortunately, Sereja's matrix is really huge. That's why Inna and Dima aren't coping with the calculating. Help them!

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ w $ $ (3<=n,m<=4·10^{6}; 1<=w<=10^{5}) $ .

The next $ w $ lines describe the moves that were made in the game.

- A line that describes an event of the first type contains 6 integers: $ 0 $ , $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ and $ v $ $ (1<=x_{1}<=x_{2}<=n; 1<=y_{1}<=y_{2}<=m; 1<=v<=10^{9}) $ .
- A line that describes an event of the second type contains 5 integers: $ 1 $ , $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ $ (2<=x_{1}<=x_{2}<=n-1; 2<=y_{1}<=y_{2}<=m-1) $ .

It is guaranteed that the second type move occurs at least once. It is guaranteed that a single operation will not add more than $ 10^{9} $ candies.

Be careful, the constraints are very large, so please use optimal data structures. Max-tests will be in pretests.

## 输出格式

For each second type move print a single integer on a single line — the difference between Dima and Inna's numbers.

## 说明/提示

Note to the sample. After the first query the matrix looks as:

`<br></br>22200<br></br>22200 <br></br>00000<br></br>00000<br></br>`After the second one it is:

`<br></br>22200<br></br>25500<br></br>03300 <br></br>00000<br></br>`After the third one it is:

`<br></br>22201<br></br>25501<br></br>03301<br></br>00001<br></br>`For the fourth query, Dima's sum equals 5 + 0 + 3 + 0 = 8 and Inna's sum equals 4 + 1 + 0 + 1 = 6. The answer to the query equals 8 - 6 = 2. For the fifth query, Dima's sum equals 0 and Inna's sum equals 18 + 2 + 0 + 1 = 21. The answer to the query is 0 - 21 = -21.

## 样例 #1

### 输入

```
4 5 5
0 1 1 2 3 2
0 2 2 3 3 3
0 1 5 4 5 1
1 2 3 3 4
1 3 4 3 4

```

### 输出

```
2
-21

```

