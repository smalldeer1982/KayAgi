---
title: "Anna and the Valentine's Day Gift"
layout: "post"
diff: 普及/提高-
pid: CF1931E
tag: ['贪心']
---

# Anna and the Valentine's Day Gift

## 题目描述

Sasha gave Anna a list $ a $ of $ n $ integers for Valentine's Day. Anna doesn't need this list, so she suggests destroying it by playing a game.

Players take turns. Sasha is a gentleman, so he gives Anna the right to make the first move.

- On her turn, Anna must choose an element $ a_i $ from the list and reverse the sequence of its digits. For example, if Anna chose the element with a value of $ 42 $ , it would become $ 24 $ ; if Anna chose the element with a value of $ 1580 $ , it would become $ 851 $ . Note that leading zeros are removed. After such a turn, the number of elements in the list does not change.
- On his turn, Sasha must extract two elements $ a_i $ and $ a_j $ ( $ i \ne j $ ) from the list, concatenate them in any order and insert the result back into the list. For example, if Sasha chose the elements equal to $ 2007 $ and $ 19 $ , he would remove these two elements from the list and add the integer $ 200719 $ or $ 192007 $ . After such a turn, the number of elements in the list decreases by $ 1 $ .

Players can't skip turns. The game ends when Sasha can't make a move, i.e. after Anna's move there is exactly one number left in the list. If this integer is not less than $ 10^m $ (i.e., $ \ge 10^m $ ), Sasha wins. Otherwise, Anna wins.

It can be shown that the game will always end. Determine who will win if both players play optimally.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follows the description of the test cases.

The first line of each test case contains integers $ n $ , $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le m \le 2 \cdot 10^6 $ ) — the number of integers in the list and the parameter determining when Sasha wins.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the list that Sasha gave to Anna.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output:

- "Sasha", if Sasha wins with optimal play;
- "Anna", if Anna wins with optimal play.

## 说明/提示

Consider the first test case.

Anna can reverse the integer $ 2 $ , then Sasha can concatenate the integers $ 2 $ and $ 14 $ , obtaining the integer $ 214 $ , which is greater than $ 10^2 = 100 $ . If Anna had reversed the integer $ 14 $ , Sasha would have concatenated the integers $ 41 $ and $ 2 $ , obtaining the integer $ 412 $ , which is greater than $ 10^2 = 100 $ . Anna has no other possible moves, so she loses.

## 样例 #1

### 输入

```
9
2 2
14 2
3 5
9 56 1
4 10
1 2007 800 1580
4 5
5000 123 30 4
10 10
6 4 6 2 3 1 10 9 10 7
1 1
6
1 1
10
8 9
1 2 9 10 10 2 10 2
4 5
10 10 10 10
```

### 输出

```
Sasha
Anna
Anna
Sasha
Sasha
Anna
Anna
Anna
Sasha
```

