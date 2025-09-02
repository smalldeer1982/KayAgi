---
title: "Two Posters"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1638F
tag: []
---

# Two Posters

## 题目描述

You want to advertise your new business, so you are going to place two posters on a billboard in the city center. The billboard consists of $ n $ vertical panels of width $ 1 $ and varying integer heights, held together by a horizontal bar. The $ i $ -th of the $ n $ panels has height $ h_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638F/248fedf6954feaff373111c2b5be4b885dfbc9ba.png)Initially, all panels hang down from the bar (their top edges lie on it), but before placing the two posters, you are allowed to move each panel up by any integer length, as long as it is still connected to the bar (its bottom edge lies below or on it).

After the moves are done, you will place two posters: one below the bar and one above it. They are not allowed to go over the bar and they must be positioned completely inside of the panels.

What is the maximum total area the two posters can cover together if you make the optimal moves? Note that you can also place a poster of $ 0 $ area. This case is equivalent to placing a single poster.

## 输入格式

The first line of input contains one integer $ n $ ( $ 1 \le n \le 10^4 $ ) — the number of vertical panels.

The second line of input contains $ n $ integers $ h_1, h_2, ..., h_n $ ( $ 1 \le h_i \le 10^{12} $ ) — the heights of the $ n $ vertical panels.

## 输出格式

Print a single integer — the maximum total area the two posters can cover together.

## 说明/提示

In the first sample test, we can choose an upper poster with area $ 12 $ and a lower poster of area $ 6 $ as in the image below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638F/0100a99d0411aa7185136cd640cb514920fb0633.png)In the second sample test, we can cover the whole billboard using a single poster.

## 样例 #1

### 输入

```
6
2 2 3 5 4 5
```

### 输出

```
18
```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
1
```

