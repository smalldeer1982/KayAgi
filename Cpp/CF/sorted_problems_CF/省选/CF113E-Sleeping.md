---
title: "Sleeping"
layout: "post"
diff: 省选/NOI-
pid: CF113E
tag: []
---

# Sleeping

## 题目描述

One day Vasya was lying in bed watching his electronic clock to fall asleep quicker.

Vasya lives in a strange country, where days have $ h $ hours, and every hour has $ m $ minutes. Clock shows time in decimal number system, in format H:M, where the string H always has a fixed length equal to the number of digits in the decimal representation of number $ h-1 $ . To achieve this, leading zeros are added if necessary. The string M has a similar format, and its length is always equal to the number of digits in the decimal representation of number $ m-1 $ . For example, if $ h=17 $ , $ m=1000 $ , then time equal to 13 hours and 75 minutes will be displayed as "13:075".

Vasya had been watching the clock from $ h_{1} $ hours $ m_{1} $ minutes to $ h_{2} $ hours $ m_{2} $ minutes inclusive, and then he fell asleep. Now he asks you to count how many times he saw the moment at which at least $ k $ digits changed on the clock simultaneously.

For example, when switching 04:19 $ → $ 04:20 two digits change. When switching 23:59 $ → $ 00:00, four digits change.

Consider that Vasya has been watching the clock for strictly less than one day. Note that the last time Vasya saw on the clock before falling asleep was "h2:m2". That is, Vasya didn't see the moment at which time "h2:m2" switched to the next value.

## 输入格式

The first line of the input file contains three space-separated integers $ h $ , $ m $ and $ k $ ( $ 2<=h,m<=10^{9} $ , $ 1<=k<=20 $ ). The second line contains space-separated integers $ h_{1} $ , $ m_{1} $ ( $ 0<=h_{1}&lt;h $ , $ 0<=m_{1}&lt;m $ ). The third line contains space-separated integers $ h_{2} $ , $ m_{2} $ ( $ 0<=h_{2}&lt;h $ , $ 0<=m_{2}&lt;m $ ).

## 输出格式

Print a single number — the number of times Vasya saw the moment of changing at least $ k $ digits simultaneously.

Please do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin stream (also you may use the %I64d specificator).

## 说明/提示

In the first example Vasya will see the following moments of time: 4:4 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF113E/36de14eb23d8ee46ce065565960590d715b12072.png) 0:0 $ → $ 0:1 $ → $ 0:2 $ → $ 0:3 $ → $ 0:4 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF113E/36de14eb23d8ee46ce065565960590d715b12072.png) 1:0 $ → $ 1:1 $ → $ 1:2 $ → $ 1:3 $ → $ 1:4 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF113E/36de14eb23d8ee46ce065565960590d715b12072.png) 2:0 $ → $ 2:1 $ → $ 2:2 $ → $ 2:3 $ → $ 2:4. Double arrow (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF113E/36de14eb23d8ee46ce065565960590d715b12072.png)) marks the sought moments of time (in this example — when Vasya sees two numbers changing simultaneously).

In the second example $ k=1 $ . Any switching time can be accepted, since during switching of the clock at least one digit is changed. Total switching equals to $ 24·60=1440 $ , but Vasya have not seen one of them — the switching of 23:59 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF113E/36de14eb23d8ee46ce065565960590d715b12072.png) 00:00.

In the third example Vasya fell asleep immediately after he began to look at the clock, so he did not see any change.

## 样例 #1

### 输入

```
5 5 2
4 4
2 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
24 60 1
0 0
23 59

```

### 输出

```
1439

```

## 样例 #3

### 输入

```
24 60 3
23 59
23 59

```

### 输出

```
0

```

