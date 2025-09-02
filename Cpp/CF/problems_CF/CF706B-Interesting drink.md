---
title: "Interesting drink"
layout: "post"
diff: 普及-
pid: CF706B
tag: []
---

# Interesting drink

## 题目描述

Vasiliy likes to rest after a hard work, so you may often meet him in some bar nearby. As all programmers do, he loves the famous drink "Beecola", which can be bought in $ n $ different shops in the city. It's known that the price of one bottle in the shop $ i $ is equal to $ x_{i} $ coins.

Vasiliy plans to buy his favorite drink for $ q $ consecutive days. He knows, that on the $ i $ -th day he will be able to spent $ m_{i} $ coins. Now, for each of the days he want to know in how many different shops he can buy a bottle of "Beecola".

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of shops in the city that sell Vasiliy's favourite drink.

The second line contains $ n $ integers $ x_{i} $ ( $ 1<=x_{i}<=100000 $ ) — prices of the bottles of the drink in the $ i $ -th shop.

The third line contains a single integer $ q $ ( $ 1<=q<=100000 $ ) — the number of days Vasiliy plans to buy the drink.

Then follow $ q $ lines each containing one integer $ m_{i} $ ( $ 1<=m_{i}<=10^{9} $ ) — the number of coins Vasiliy can spent on the $ i $ -th day.

## 输出格式

Print $ q $ integers. The $ i $ -th of them should be equal to the number of shops where Vasiliy will be able to buy a bottle of the drink on the $ i $ -th day.

## 说明/提示

On the first day, Vasiliy won't be able to buy a drink in any of the shops.

On the second day, Vasiliy can buy a drink in the shops $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ .

On the third day, Vasiliy can buy a drink only in the shop number $ 1 $ .

Finally, on the last day Vasiliy can buy a drink in any shop.

## 样例 #1

### 输入

```
5
3 10 8 6 11
4
1
10
3
11

```

### 输出

```
0
4
1
5

```

