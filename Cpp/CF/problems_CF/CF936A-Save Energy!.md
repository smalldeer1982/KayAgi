---
title: "Save Energy!"
layout: "post"
diff: 普及/提高-
pid: CF936A
tag: []
---

# Save Energy!

## 题目描述

Julia is going to cook a chicken in the kitchen of her dormitory. To save energy, the stove in the kitchen automatically turns off after $ k $ minutes after turning on.

During cooking, Julia goes to the kitchen every $ d $ minutes and turns on the stove if it is turned off. While the cooker is turned off, it stays warm. The stove switches on and off instantly.

It is known that the chicken needs $ t $ minutes to be cooked on the stove, if it is turned on, and $ 2t $ minutes, if it is turned off. You need to find out, how much time will Julia have to cook the chicken, if it is considered that the chicken is cooked evenly, with constant speed when the stove is turned on and at a constant speed when it is turned off.

## 输入格式

The single line contains three integers $ k $ , $ d $ and $ t $ ( $ 1<=k,d,t<=10^{18} $ ).

## 输出格式

Print a single number, the total time of cooking in minutes. The relative or absolute error must not exceed $ 10^{-9} $ .

Namely, let's assume that your answer is $ x $ and the answer of the jury is $ y $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/4392ea91cc80355fbf47ddfe5d10204ae8a86dac.png).

## 说明/提示

In the first example, the chicken will be cooked for 3 minutes on the turned on stove, after this it will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/946fbd87d05fe2e24b8af4d0aa7735f7b1052cc7.png). Then the chicken will be cooked for one minute on a turned off stove, it will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/a9bdc1b9aee6e89dbd96641ebe23053a20526f44.png). Thus, after four minutes the chicken will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/6991f0a9cff42170b98fc979c8ddd5223ae7cf0e.png). Before the fifth minute Julia will turn on the stove and after $ 2.5 $ minutes the chicken will be ready ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/b3b22ef8237f8837aeb119d85eaee973ea63486d.png).

In the second example, when the stove is turned off, Julia will immediately turn it on, so the stove will always be turned on and the chicken will be cooked in 20 minutes.

## 样例 #1

### 输入

```
3 2 6

```

### 输出

```
6.5

```

## 样例 #2

### 输入

```
4 2 20

```

### 输出

```
20.0

```

