---
title: "Water Taps"
layout: "post"
diff: 提高+/省选-
pid: CF954E
tag: ['贪心', '排序']
---

# Water Taps

## 题目描述

Consider a system of $ n $ water taps all pouring water into the same container. The $ i $ -th water tap can be set to deliver any amount of water from $ 0 $ to $ a_{i} $ ml per second (this amount may be a real number). The water delivered by $ i $ -th tap has temperature $ t_{i} $ .

If for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you set $ i $ -th tap to deliver exactly $ x_{i} $ ml of water per second, then the resulting temperature of water will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/4d0f711b0c4dc1450cd61a20f118d34a644e0d79.png) (if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/dbce41b29215315b290a54646261b5eaa9727507.png), then to avoid division by zero we state that the resulting water temperature is $ 0 $ ).

You have to set all the water taps in such a way that the resulting temperature is exactly $ T $ . What is the maximum amount of water you may get per second if its temperature has to be $ T $ ?

## 输入格式

The first line contains two integers $ n $ and $ T $ ( $ 1<=n<=200000 $ , $ 1<=T<=10^{6} $ ) — the number of water taps and the desired temperature of water, respectively.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) where $ a_{i} $ is the maximum amount of water $ i $ -th tap can deliver per second.

The third line contains $ n $ integers $ t_{1} $ , $ t_{2} $ , ..., $ t_{n} $ ( $ 1<=t_{i}<=10^{6} $ ) — the temperature of water each tap delivers.

## 输出格式

Print the maximum possible amount of water with temperature exactly $ T $ you can get per second (if it is impossible to obtain water with such temperature, then the answer is considered to be $ 0 $ ).

Your answer is considered correct if its absolute or relative error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
2 100
3 10
50 150

```

### 输出

```
6.000000000000000

```

## 样例 #2

### 输入

```
3 9
5 5 30
6 6 10

```

### 输出

```
40.000000000000000

```

## 样例 #3

### 输入

```
2 12
1 3
10 15

```

### 输出

```
1.666666666666667

```

