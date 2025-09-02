# Diagonals

## 题目描述

Vitaly503 is given a checkered board with a side of $ n $ and $ k $ chips. He realized that all these $ k $ chips need to be placed on the cells of the board (no more than one chip can be placed on a single cell).

Let's denote the cell in the $ i $ -th row and $ j $ -th column as $ (i ,j) $ . A diagonal is the set of cells for which the value $ i + j $ is the same. For example, cells $ (3, 1) $ , $ (2, 2) $ , and $ (1, 3) $ lie on the same diagonal, but $ (1, 2) $ and $ (2, 3) $ do not. A diagonal is called occupied if it contains at least one chip.

Determine what is the minimum possible number of occupied diagonals among all placements of $ k $ chips.

## 说明/提示

In the first test case, there are no chips, so 0 diagonals will be occupied. In the second test case, both chips can be placed on diagonal $ (2, 1), (1, 2) $ , so the answer is 1. In the third test case, 3 chips can't be placed on one diagonal, but placing them on $ (1, 2), (2, 1), (1, 1) $ makes 2 diagonals occupied. In the 7th test case, chips will occupy all 5 diagonals in any valid placing.

## 样例 #1

### 输入

```
7
1 0
2 2
2 3
2 4
10 50
100 239
3 9```

### 输出

```
0
1
2
3
6
3
5```

