---
title: "Beauty of the mountains"
layout: "post"
diff: 普及+/提高
pid: CF1982D
tag: ['数论', '前缀和']
---

# Beauty of the mountains

## 题目描述

Nikita loves mountains and has finally decided to visit the Berlyand mountain range! The range was so beautiful that Nikita decided to capture it on a map. The map is a table of $ n $ rows and $ m $ columns, with each cell containing a non-negative integer representing the height of the mountain.

He also noticed that mountains come in two types:

- With snowy caps.
- Without snowy caps.

Nikita is a very pragmatic person. He wants the sum of the heights of the mountains with snowy caps to be equal to the sum of the heights of the mountains without them. He has arranged with the mayor of Berlyand, Polikarp Polikarpovich, to allow him to transform the landscape.

Nikita can perform transformations on submatrices of size $ k \times k $ as follows: he can add an integer constant $ c $ to the heights of the mountains within this area, but the type of the mountain remains unchanged. Nikita can choose the constant $ c $ independently for each transformation. Note that $ c $ can be negative.

Before making the transformations, Nikita asks you to find out if it is possible to achieve equality of the sums, or if it is impossible. It doesn't matter at what cost, even if the mountains turn into canyons and have negative heights.

If only one type of mountain is represented on the map, then the sum of the heights of the other type of mountain is considered to be zero.

## 输入格式

Each test consists of several test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. This is followed by a description of test cases.

The first line of each test case contains three integers $ n, m, k $ ( $ 1 \le n, m \le 500, 1 \le k \le min(n, m) $ ).

The next $ n $ lines of each test case contain $ m $ integers $ a_{i j} $ ( $ 0 \le a_{i j} \le 10^{9} $ ) — the initial heights of the mountains.

The next $ n $ binary strings of length $ m $ for each test case determine the type of mountain, ' $ 0 $ ' — with snowy caps, ' $ 1 $ ' — without them.

It is guaranteed that the sum of $ n \cdot m $ for all test cases does not exceed $ 250\,000 $ .

## 输出格式

For each test case, output "YES" without quotes if it is possible to equalize the sums of the mountain heights, otherwise output "NO" without quotes. You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

The mountain array from the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/c2cad4d039daa4458ac8328be539df0f39115b35.png)Initially, the sum of the heights of the mountains with snowy caps is $ 11 + 3 + 4 + 3 + 0 + 1 + 15 = 37 $ , and without them is $ 7 + 2 = 9 $ .

To equalize these sums, we can perform two transformations:

First transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/26401332927c782774104130bd94cec3d8dea8ef.png)Note that the constant $ c $ can be negative.

After the first transformation, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/8985a2e394a22468e2807bb57386a8c62bc3f888.png)Second transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/83de4303ed287bb4d20cf33c8ab2494ed765c011.png)As a result, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/1dfddde2b777b3b24d753c3d41d8fe42319ee24e.png)The sum of the heights of the mountains with snowy caps is $ 17 + 9 + 9 - 16 - 20 - 19 + 15 = -5 $ , and without them is $ 7 - 12 = -5 $ , thus the answer is YES.

## 样例 #1

### 输入

```
8
3 3 2
7 11 3
4 2 3
0 1 15
100
010
000
4 4 3
123 413 24 233
123 42 0 216
22 1 1 53
427 763 22 6
0101
1111
1010
0101
3 3 2
2 1 1
1 1 2
1 5 4
010
101
010
3 3 2
2 1 1
1 1 2
1 5 3
010
101
010
3 4 3
46 49 50 1
19 30 23 12
30 25 1 46
1000
0100
0010
5 4 4
39 30 0 17
22 42 30 13
10 44 46 35
12 19 9 39
21 0 45 40
1000
1111
0011
0111
1100
2 2 2
3 4
6 7
00
00
2 2 2
0 0
2 0
01
00
```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
YES
```

