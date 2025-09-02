---
title: "My pretty girl Noora"
layout: "post"
diff: 提高+/省选-
pid: CF822D
tag: []
---

# My pretty girl Noora

## 题目描述

In Pavlopolis University where Noora studies it was decided to hold beauty contest "Miss Pavlopolis University". Let's describe the process of choosing the most beautiful girl in the university in more detail.

The contest is held in several stages. Suppose that exactly $ n $ girls participate in the competition initially. All the participants are divided into equal groups, $ x $ participants in each group. Furthermore the number $ x $ is chosen arbitrarily, i. e. on every stage number $ x $ can be different. Within each group the jury of the contest compares beauty of the girls in the format "each with each". In this way, if group consists of $ x $ girls, then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/969c596ed060cb668747b79aae52c3adc4b7f3f8.png) comparisons occur. Then, from each group, the most beautiful participant is selected. Selected girls enter the next stage of the competition. Thus if $ n $ girls were divided into groups, $ x $ participants in each group, then exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/8f8703916c06209ae2c6ec59180f52b09e3975b5.png) participants will enter the next stage. The contest continues until there is exactly one girl left who will be "Miss Pavlopolis University"

But for the jury this contest is a very tedious task. They would like to divide the girls into groups in each stage so that the total number of pairwise comparisons of the girls is as few as possible. Let $ f(n) $ be the minimal total number of comparisons that should be made to select the most beautiful participant, if we admit $ n $ girls to the first stage.

The organizers of the competition are insane. They give Noora three integers $ t $ , $ l $ and $ r $ and ask the poor girl to calculate the value of the following expression: $ t^{0}·f(l)+t^{1}·f(l+1)+...+t^{r-l}·f(r) $ . However, since the value of this expression can be quite large the organizers ask her to calculate it modulo $ 10^{9}+7 $ . If Noora can calculate the value of this expression the organizers promise her to help during the beauty contest. But the poor girl is not strong in mathematics, so she turned for help to Leha and he turned to you.

## 输入格式

The first and single line contains three integers $ t $ , $ l $ and $ r $ ( $ 1<=t&lt;10^{9}+7,2<=l<=r<=5·10^{6} $ ).

## 输出格式

In the first line print single integer — the value of the expression modulo $ 10^{9}+7 $ .

## 说明/提示

Consider the sample.

It is necessary to find the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/cada51a85db8e48cf197de751d78ba932c387644.png).

 $ f(2)=1 $ . From two girls you can form only one group of two people, in which there will be one comparison.

 $ f(3)=3 $ . From three girls you can form only one group of three people, in which there will be three comparisons.

 $ f(4)=3 $ . From four girls you can form two groups of two girls each. Then at the first stage there will be two comparisons, one in each of the two groups. In the second stage there will be two girls and there will be one comparison between them. Total $ 2+1=3 $ comparisons. You can also leave all girls in same group in the first stage. Then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/f0bdffc4a640a3c926e3ac1b0c07f337ac1e9d1c.png) comparisons will occur. Obviously, it's better to split girls into groups in the first way.

Then the value of the expression is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/766d39075b51c44c1ef841a8899d917995ced842.png).

## 样例 #1

### 输入

```
2 2 4

```

### 输出

```
19

```

