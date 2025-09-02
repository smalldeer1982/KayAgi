---
title: "Misha, Grisha and Underground"
layout: "post"
diff: 普及+/提高
pid: CF832D
tag: []
---

# Misha, Grisha and Underground

## 题目描述

Misha and Grisha are funny boys, so they like to use new underground. The underground has $ n $ stations connected with $ n-1 $ routes so that each route connects two stations, and it is possible to reach every station from any other.

The boys decided to have fun and came up with a plan. Namely, in some day in the morning Misha will ride the underground from station $ s $ to station $ f $ by the shortest path, and will draw with aerosol an ugly text "Misha was here" on every station he will pass through (including $ s $ and $ f $ ). After that on the same day at evening Grisha will ride from station $ t $ to station $ f $ by the shortest path and will count stations with Misha's text. After that at night the underground workers will wash the texts out, because the underground should be clean.

The boys have already chosen three stations $ a $ , $ b $ and $ c $ for each of several following days, one of them should be station $ s $ on that day, another should be station $ f $ , and the remaining should be station $ t $ . They became interested how they should choose these stations $ s $ , $ f $ , $ t $ so that the number Grisha will count is as large as possible. They asked you for help.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2<=n<=10^{5} $ , $ 1<=q<=10^{5} $ ) — the number of stations and the number of days.

The second line contains $ n-1 $ integers $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}<=n $ ). The integer $ p_{i} $ means that there is a route between stations $ p_{i} $ and $ i $ . It is guaranteed that it's possible to reach every station from any other.

The next $ q $ lines contains three integers $ a $ , $ b $ and $ c $ each ( $ 1<=a,b,c<=n $ ) — the ids of stations chosen by boys for some day. Note that some of these ids could be same.

## 输出格式

Print $ q $ lines. In the $ i $ -th of these lines print the maximum possible number Grisha can get counting when the stations $ s $ , $ t $ and $ f $ are chosen optimally from the three stations on the $ i $ -th day.

## 说明/提示

In the first example on the first day if $ s $ = $ 1 $ , $ f $ = $ 2 $ , $ t $ = $ 3 $ , Misha would go on the route $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ , and Grisha would go on the route $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ . He would see the text at the stations $ 1 $ and $ 2 $ . On the second day, if $ s $ = $ 3 $ , $ f $ = $ 2 $ , $ t $ = $ 3 $ , both boys would go on the route $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ . Grisha would see the text at $ 3 $ stations.

In the second examle if $ s $ = $ 1 $ , $ f $ = $ 3 $ , $ t $ = $ 2 $ , Misha would go on the route $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 3 $ , and Grisha would go on the route $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 3 $ and would see the text at both stations.

## 样例 #1

### 输入

```
3 2
1 1
1 2 3
2 3 3

```

### 输出

```
2
3

```

## 样例 #2

### 输入

```
4 1
1 2 3
1 2 3

```

### 输出

```
2

```

