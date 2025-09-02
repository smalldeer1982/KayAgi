---
title: "Video Cards"
layout: "post"
diff: 普及+/提高
pid: CF731F
tag: []
---

# Video Cards

## 题目描述

Little Vlad is fond of popular computer game Bota-2. Recently, the developers announced the new add-on named Bota-3. Of course, Vlad immediately bought only to find out his computer is too old for the new game and needs to be updated.

There are $ n $ video cards in the shop, the power of the $ i $ -th video card is equal to integer value $ a_{i} $ . As Vlad wants to be sure the new game will work he wants to buy not one, but several video cards and unite their powers using the cutting-edge technology. To use this technology one of the cards is chosen as the leading one and other video cards are attached to it as secondary. For this new technology to work it's required that the power of each of the secondary video cards is divisible by the power of the leading video card. In order to achieve that the power of any secondary video card can be reduced to any integer value less or equal than the current power. However, the power of the leading video card should remain unchanged, i.e. it can't be reduced.

Vlad has an infinite amount of money so he can buy any set of video cards. Help him determine which video cards he should buy such that after picking the leading video card and may be reducing some powers of others to make them work together he will get the maximum total value of video power.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the number of video cards in the shop.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=200000 $ ) — powers of video cards.

## 输出格式

The only line of the output should contain one integer value — the maximum possible total power of video cards working together.

## 说明/提示

In the first sample, it would be optimal to buy video cards with powers $ 3 $ , $ 15 $ and $ 9 $ . The video card with power $ 3 $ should be chosen as the leading one and all other video cards will be compatible with it. Thus, the total power would be $ 3+15+9=27 $ . If he buys all the video cards and pick the one with the power $ 2 $ as the leading, the powers of all other video cards should be reduced by $ 1 $ , thus the total power would be $ 2+2+14+8=26 $ , that is less than $ 27 $ . Please note, that it's not allowed to reduce the power of the leading video card, i.e. one can't get the total power $ 3+1+15+9=28 $ .

In the second sample, the optimal answer is to buy all video cards and pick the one with the power $ 2 $ as the leading. The video card with the power $ 7 $ needs it power to be reduced down to $ 6 $ . The total power would be $ 8+2+2+6=18 $ .

## 样例 #1

### 输入

```
4
3 2 15 9

```

### 输出

```
27

```

## 样例 #2

### 输入

```
4
8 2 2 7

```

### 输出

```
18

```

