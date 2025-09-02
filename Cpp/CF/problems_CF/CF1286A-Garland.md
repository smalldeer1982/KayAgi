---
title: "Garland"
layout: "post"
diff: 普及+/提高
pid: CF1286A
tag: []
---

# Garland

## 题目描述

Vadim loves decorating the Christmas tree, so he got a beautiful garland as a present. It consists of $ n $ light bulbs in a single row. Each bulb has a number from $ 1 $ to $ n $ (in arbitrary order), such that all the numbers are distinct. While Vadim was solving problems, his home Carp removed some light bulbs from the garland. Now Vadim wants to put them back on.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1286A/44ebad0b7dea7f3147d7078591406d3a6ec6de35.png)Vadim wants to put all bulb back on the garland. Vadim defines complexity of a garland to be the number of pairs of adjacent bulbs with numbers with different parity (remainder of the division by $ 2 $ ). For example, the complexity of 1 4 2 3 5 is $ 2 $ and the complexity of 1 3 5 7 6 4 2 is $ 1 $ .

No one likes complexity, so Vadim wants to minimize the number of such pairs. Find the way to put all bulbs back on the garland, such that the complexity is as small as possible.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the number of light bulbs on the garland.

The second line contains $ n $ integers $ p_1,\ p_2,\ \ldots,\ p_n $ ( $ 0 \le p_i \le n $ ) — the number on the $ i $ -th bulb, or $ 0 $ if it was removed.

## 输出格式

Output a single number — the minimum complexity of the garland.

## 说明/提示

In the first example, one should place light bulbs as 1 5 4 2 3. In that case, the complexity would be equal to 2, because only $ (5, 4) $ and $ (2, 3) $ are the pairs of adjacent bulbs that have different parity.

In the second case, one of the correct answers is 1 7 3 5 6 4 2.

## 样例 #1

### 输入

```
5
0 5 0 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
1 0 0 5 0 0 2
```

### 输出

```
1
```

