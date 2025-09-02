---
title: "Passports"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1012F
tag: []
---

# Passports

## 题目描述

Gleb is a famous competitive programming teacher from Innopolis. He is planning a trip to $ N $ programming camps in the nearest future. Each camp will be held in a different country. For each of them, Gleb needs to apply for a visa.

For each of these trips Gleb knows three integers: the number of the first day of the trip $ s_{i} $ , the length of the trip in days $ len_{i} $ , and the number of days $ t_{i} $ this country's consulate will take to process a visa application and stick a visa in a passport. Gleb has $ P $ ( $ 1<=P<=2 $ ) valid passports and is able to decide which visa he wants to put in which passport.

For each trip, Gleb will have a flight to that country early in the morning of the day $ s_{i} $ and will return back late in the evening of the day $ s_{i}+len_{i}-1 $ .

To apply for a visa on the day $ d $ , Gleb needs to be in Innopolis in the middle of this day. So he can't apply for a visa while he is on a trip, including the first and the last days. If a trip starts the next day after the end of the other one, Gleb can't apply for a visa between them as well. The earliest Gleb can apply for a visa is day 1.

After applying for a visa of country $ i $ on day $ d $ , Gleb will get his passport back in the middle of the day $ d+t_{i} $ . Consulates use delivery services, so Gleb can get his passport back even if he is not in Innopolis on this day. Gleb can apply for another visa on the same day he received his passport back, if he is in Innopolis this day.

Gleb will not be able to start his trip on day $ s_{i} $ if he doesn't has a passport with a visa for the corresponding country in the morning of day $ s_{i} $ . In particular, the passport should not be in another country's consulate for visa processing.

Help Gleb to decide which visas he needs to receive in which passport, and when he should apply for each visa.

## 输入格式

In the first line of the input there are two integers $ N $ ( $ 1<=N<=22 $ ) and $ P $ ( $ 1<=P<=2 $ )—the number of trips and the number of passports Gleb has, respectively.

The next $ N $ lines describe Gleb's trips. Each line contains three positive integers $ s_{i} $ , $ len_{i} $ , $ t_{i} $ ( $ 1<=s_{i},len_{i},t_{i}<=10^{9} $ )—the first day of the trip, the length of the trip and number of days the consulate of this country needs to process a visa application. It is guaranteed that no two trips intersect.

## 输出格式

If it is impossible to get all visas on time, just print "NO" (quotes for clarity). Otherwise, print "YES" and $ N $ lines describing trips. For each trip, first print number of the passport Gleb should put this country's visa in, and then print number of the day he should apply for it. Print trips in the same order as they appear in the input. Days are numbered from 1, starting with tomorrow—the first day you can apply for a visa. Passports are numbered from 1 to $ P $ .

If there are several possible answers, print any of them.

## 说明/提示

Examples with answer "YES" are depicted below.

Each cell of the stripe represents a single day. Rectangles represent trips, each trip starts in the morning and ends in the evening. Rectangles with angled corners represent visa applications. Each application starts in the middle of a day and ends $ t_{i} $ days after. The trip and the visa application for the same country have the same color.

In examples with two passports, visa applications and trips depicted above the time stripe are made using the first passport, visa applications and trips depicted below the time stripe are made using the second passport.

Example 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012F/5dd918dca964117b03bd6cbb40c0de3c70717164.png)Example 2:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012F/9f7d11ad4fe06fc57150d3e5a44e43c98adc3505.png)Example 3:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012F/387c81ed9fa5730dca096a0f2c80c759707484e1.png)

## 样例 #1

### 输入

```
2 1
3 1 1
6 1 1

```

### 输出

```
YES
1 1
1 4

```

## 样例 #2

### 输入

```
3 1
13 2 2
7 3 1
19 3 4

```

### 输出

```
YES
1 10
1 1
1 2

```

## 样例 #3

### 输入

```
7 2
15 1 1
14 1 1
18 1 1
21 1 1
9 4 6
22 2 5
5 4 3

```

### 输出

```
YES
2 13
1 1
1 16
1 19
1 2
2 16
2 1

```

## 样例 #4

### 输入

```
3 1
7 3 1
13 2 3
19 3 4

```

### 输出

```
NO

```

