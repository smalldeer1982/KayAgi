---
title: "NWERC10G - Selling Land"
layout: "post"
diff: 普及+/提高
pid: SP8628
tag: []
---

# NWERC10G - Selling Land

## 题目描述

As you may know, the country of Absurdistan is full of abnormalities. For example, the whole country can be divided into unit squares that are either grass or swamp. Also, the country is famous for its incapable bureaucrats. If you want to buy a piece of land (called a parcel), you can only buy a rectangular area, because they cannot handle other shapes. The price of the parcel is determined by them and is proportional to the perimeter of the parcel, since the bureaucrats are unable to multiply integers and thus cannot calculate the area of the parcel.

Per owns a parcel in Absurdistan surrounded by swamp and he wants to sell it, possibly in parts, to some buyers. When he sells a rectangular part of his land, he is obliged to announce this to the local bureaucrats. They will first tell him the price he is supposed to sell it for. Then they will write down the name of the new owner and the coordinates of the south-east corner of the parcel being sold. If somebody else already owns a parcel with a south-east corner at the same spot, the bureaucrats will deny the change of ownership.

Per realizes that he can easily trick the system. He can sell overlapping areas, because bureaucrats only check whether the south-east corners are identical. However, nobody wants to buy a parcel containing swamp.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP8628/85e58efc3f46182a4b5c9b0fef12eae109adb228.png)

Now Per would like to know how many parcels of each perimeter he needs to sell in order to maximize his profit. Can you help him? You may assume that he can always find a buyer for each piece of land, as long as it doesn't contain any swamps. Also, Per is sure that no square within his parcel is owned by somebody else.

## 输入格式

On the first line a positive integer: the number of test cases, at most 100. After that per test case:

- One line with two integers n and m (1
- n lines, each with m characters. Each character is either `\#' or `.'. The j-th character on the i-th line is a `\#' if position (i, j) is a swamp, and `.' if it is grass. The north-west corner of Per's parcel has coordinates (1, 1), and the south-east corner has coordinates (n,m).

## 输出格式

Per test case:

- Zero or more lines containing a complete list of how many parcels of each perimeter Per needs to sell in order to maximize his profit. More specifically, if Per should sell p

## 样例 #1

### 输入

```
1
6 5
..#.#
.#...
#..##
...#.
#....
#..#.
```

### 输出

```
6 x 4
5 x 6
5 x 8
3 x 10
1 x 12
```

