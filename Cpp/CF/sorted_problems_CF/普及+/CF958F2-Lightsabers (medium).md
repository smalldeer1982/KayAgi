---
title: "Lightsabers (medium)"
layout: "post"
diff: 普及+/提高
pid: CF958F2
tag: []
---

# Lightsabers (medium)

## 题目描述

There is unrest in the Galactic Senate. Several thousand solar systems have declared their intentions to leave the Republic. Master Heidi needs to select the Jedi Knights who will go on peacekeeping missions throughout the galaxy. It is well-known that the success of any peacekeeping mission depends on the colors of the lightsabers of the Jedi who will go on that mission.

Heidi has $ n $ Jedi Knights standing in front of her, each one with a lightsaber of one of $ m $ possible colors. She knows that for the mission to be the most effective, she needs to select some contiguous interval of knights such that there are exactly $ k_{1} $ knights with lightsabers of the first color, $ k_{2} $ knights with lightsabers of the second color, $ ... $ , $ k_{m} $ knights with lightsabers of the $ m $ -th color.

However, since the last time, she has learned that it is not always possible to select such an interval. Therefore, she decided to ask some Jedi Knights to go on an indefinite unpaid vacation leave near certain pits on Tatooine, if you know what I mean. Help Heidi decide what is the minimum number of Jedi Knights that need to be let go before she is able to select the desired interval from the subsequence of remaining knights.

## 输入格式

The first line of the input contains $ n $ ( $ 1<=n<=2·10^{5} $ ) and $ m $ ( $ 1<=m<=n $ ). The second line contains $ n $ integers in the range $ {1,2,...,m} $ representing colors of the lightsabers of the subsequent Jedi Knights. The third line contains $ m $ integers $ k_{1},k_{2},...,k_{m} $ (with ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958F2/35fb4fe66d9c5af5cfc16ee37846c2adee7f43fd.png)) – the desired counts of Jedi Knights with lightsabers of each color from $ 1 $ to $ m $ .

## 输出格式

Output one number: the minimum number of Jedi Knights that need to be removed from the sequence so that, in what remains, there is an interval with the prescribed counts of lightsaber colors. If this is not possible, output $ -1 $ .

## 样例 #1

### 输入

```
8 3
3 3 1 2 2 1 1 3
3 1 1

```

### 输出

```
1

```

