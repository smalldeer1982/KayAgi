---
title: "Flowers"
layout: "post"
diff: 普及+/提高
pid: CF474D
tag: ['动态规划 DP', '前缀和']
---

# Flowers

## 题目描述

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输出格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

- For $ K $ = $ 2 $ and length $ 1 $ Marmot can eat ( $ R $ ).
- For $ K $ = $ 2 $ and length $ 2 $ Marmot can eat ( $ RR $ ) and ( $ WW $ ).
- For $ K $ = $ 2 $ and length $ 3 $ Marmot can eat ( $ RRR $ ), ( $ RWW $ ) and ( $ WWR $ ).
- For $ K $ = $ 2 $ and length $ 4 $ Marmot can eat, for example, ( $ WWWW $ ) or ( $ RWWR $ ), but for example he can't eat ( $ WWWR $ ).

## 样例 #1

### 输入

```
3 2
1 3
2 3
4 4

```

### 输出

```
6
5
5

```

