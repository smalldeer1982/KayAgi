---
title: "Winding polygonal line"
layout: "post"
diff: 省选/NOI-
pid: CF1158D
tag: []
---

# Winding polygonal line

## 题目描述

Vasya has $ n $ different points $ A_1, A_2, \ldots A_n $ on the plane. No three of them lie on the same line He wants to place them in some order $ A_{p_1}, A_{p_2}, \ldots, A_{p_n} $ , where $ p_1, p_2, \ldots, p_n $ — some permutation of integers from $ 1 $ to $ n $ .

After doing so, he will draw oriented polygonal line on these points, drawing oriented segments from each point to the next in the chosen order. So, for all $ 1 \leq i \leq n-1 $ he will draw oriented segment from point $ A_{p_i} $ to point $ A_{p_{i+1}} $ . He wants to make this polygonal line satisfying $ 2 $ conditions:

- it will be non-self-intersecting, so any $ 2 $ segments which are not neighbors don't have common points.
- it will be winding.

Vasya has a string $ s $ , consisting of $ (n-2) $ symbols "L" or "R". Let's call an oriented polygonal line winding, if its $ i $ -th turn left, if $ s_i =  $ "L" and right, if $ s_i =  $ "R". More formally: $ i $ -th turn will be in point $ A_{p_{i+1}} $ , where oriented segment from point $ A_{p_i} $ to point $ A_{p_{i+1}} $ changes to oriented segment from point $ A_{p_{i+1}} $ to point $ A_{p_{i+2}} $ . Let's define vectors $ \overrightarrow{v_1} = \overrightarrow{A_{p_i} A_{p_{i+1}}} $ and $ \overrightarrow{v_2} = \overrightarrow{A_{p_{i+1}} A_{p_{i+2}}} $ . Then if in order to rotate the vector $ \overrightarrow{v_1} $ by the smallest possible angle, so that its direction coincides with the direction of the vector $ \overrightarrow{v_2} $ we need to make a turn counterclockwise, then we say that $ i $ -th turn is to the left, and otherwise to the right. For better understanding look at this pictures with some examples of turns:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/d5299b6f90549459cc8717af240386941199ff67.png)There are left turns on this picture  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/a11fbd8181dcd2ab10ca7331a2bf5db3787c2cdb.png)There are right turns on this pictureYou are given coordinates of the points $ A_1, A_2, \ldots A_n $ on the plane and string $ s $ . Find a permutation $ p_1, p_2, \ldots, p_n $ of the integers from $ 1 $ to $ n $ , such that the polygonal line, drawn by Vasya satisfy two necessary conditions.

## 输入格式

The first line contains one integer $ n $ — the number of points ( $ 3 \leq n \leq 2000 $ ). Next $ n $ lines contains two integers $ x_i $ and $ y_i $ , divided by space — coordinates of the point $ A_i $ on the plane ( $ -10^9 \leq x_i, y_i \leq 10^9 $ ). The last line contains a string $ s $ consisting of symbols "L" and "R" with length $ (n-2) $ . It is guaranteed that all points are different and no three points lie at the same line.

## 输出格式

If the satisfying permutation doesn't exists, print $ -1 $ . In the other case, print $ n $ numbers $ p_1, p_2, \ldots, p_n $ — the permutation which was found ( $ 1 \leq p_i \leq n $ and all $ p_1, p_2, \ldots, p_n $ are different). If there exists more than one solution, you can find any.

## 说明/提示

This is the picture with the polygonal line from the $ 1 $ test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/d2411e0ea8639f748eaeabd4798b3f5ad7d71d3c.png)As we see, this polygonal line is non-self-intersecting and winding, because the turn in point $ 2 $ is left.

This is the picture with the polygonal line from the $ 2 $ test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1158D/905963ceb06b1d6041871a65036c396bc8d6cd07.png)

## 样例 #1

### 输入

```
3
1 1
3 1
1 3
L

```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
6
1 0
0 1
0 2
-1 0
-1 -1
2 1
RLLR

```

### 输出

```
6 1 3 4 2 5

```

