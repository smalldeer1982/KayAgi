---
title: "Bears and Juice"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF643F
tag: []
---

# Bears and Juice

## 题目描述

There are $ n $ bears in the inn and $ p $ places to sleep. Bears will party together for some number of nights (and days).

Bears love drinking juice. They don't like wine but they can't distinguish it from juice by taste or smell.

A bear doesn't sleep unless he drinks wine. A bear must go to sleep a few hours after drinking a wine. He will wake up many days after the party is over.

Radewoosh is the owner of the inn. He wants to put some number of barrels in front of bears. One barrel will contain wine and all other ones will contain juice. Radewoosh will challenge bears to find a barrel with wine.

Each night, the following happens in this exact order:

1. Each bear must choose a (maybe empty) set of barrels. The same barrel may be chosen by many bears.
2. Each bear drinks a glass from each barrel he chose.
3. All bears who drink wine go to sleep (exactly those bears who chose a barrel with wine). They will wake up many days after the party is over. If there are not enough places to sleep then bears lose immediately.

At the end, if it's sure where wine is and there is at least one awake bear then bears win (unless they have lost before because of the number of places to sleep).

Radewoosh wants to allow bears to win. He considers $ q $ scenarios. In the $ i $ -th scenario the party will last for $ i $ nights. Then, let $ R_{i} $ denote the maximum number of barrels for which bears surely win if they behave optimally. Let's define ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643F/3cf222972365b649aecc64bb442b708fd8b7a182.png). Your task is to find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643F/7ba18b4dd857c67bb4a6e2b14cb4cab7c95a919c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643F/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the exclusive or (also denoted as XOR).

Note that the same barrel may be chosen by many bears and all of them will go to sleep at once.

## 输入格式

The only line of the input contains three integers $ n $ , $ p $ and $ q $ ( $ 1<=n<=10^{9} $ , $ 1<=p<=130 $ , $ 1<=q<=2000000 $ ) — the number of bears, the number of places to sleep and the number of scenarios, respectively.

## 输出格式

Print one integer, equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643F/7ba18b4dd857c67bb4a6e2b14cb4cab7c95a919c.png).

## 说明/提示

In the first sample, there are $ 5 $ bears and only $ 1 $ place to sleep. We have $ R_{1}=6,R_{2}=11,R_{3}=16 $ so the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643F/3044a14b49b8a41a1aadeeb76be7dca4826f9b52.png). Let's analyze the optimal strategy for scenario with $ 2 $ days. There are $ R_{2}=11 $ barrels and $ 10 $ of them contain juice.

- In the first night, the $ i $ -th bear chooses a barrel $ i $ only. 
  - If one of the first $ 5 $ barrels contains wine then one bear goes to sleep. Then, bears win because they know where wine is and there is at least one awake bear.
  - But let's say none of the first $ 5 $ barrels contains wine. In the second night, the $ i $ -th bear chooses a barrel $ 5+i $ . 
      - If one of barrels $ 6–10 $ contains wine then one bear goes to sleep. And again, bears win in such a situation.
      - If nobody went to sleep then wine is in a barrel $ 11 $ .

In the second sample, there is only one bear. He should choose an empty set of barrels in each night. Otherwise, he would maybe get wine and bears would lose (because there must be at least one awake bear). So, for any number of days we have $ R_{i}=1 $ . The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643F/17441c3ac6d006f5ad9af5d20538f3ec4ec78ffd.png).

## 样例 #1

### 输入

```
5 1 3

```

### 输出

```
32

```

## 样例 #2

### 输入

```
1 100 4

```

### 输出

```
4

```

## 样例 #3

### 输入

```
3 2 1

```

### 输出

```
7

```

## 样例 #4

### 输入

```
100 100 100

```

### 输出

```
381863924

```

