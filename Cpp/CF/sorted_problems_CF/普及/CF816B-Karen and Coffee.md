---
title: "Karen and Coffee"
layout: "post"
diff: 普及/提高-
pid: CF816B
tag: ['前缀和']
---

# Karen and Coffee

## 题目描述

To stay woke and attentive during classes, Karen needs some coffee!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF816B/84ca24fa194ecce1cb9c3e825b543dfb7809c444.png)Karen, a coffee aficionado, wants to know the optimal temperature for brewing the perfect cup of coffee. Indeed, she has spent some time reading several recipe books, including the universally acclaimed "The Art of the Covfefe".

She knows $ n $ coffee recipes. The $ i $ -th recipe suggests that coffee should be brewed between $ l_{i} $ and $ r_{i} $ degrees, inclusive, to achieve the optimal taste.

Karen thinks that a temperature is admissible if at least $ k $ recipes recommend it.

Karen has a rather fickle mind, and so she asks $ q $ questions. In each question, given that she only wants to prepare coffee with a temperature between $ a $ and $ b $ , inclusive, can you tell her how many admissible integer temperatures fall within the range?

## 输入格式

The first line of input contains three integers, $ n $ , $ k $ ( $ 1<=k<=n<=200000 $ ), and $ q $ ( $ 1<=q<=200000 $ ), the number of recipes, the minimum number of recipes a certain temperature must be recommended by to be admissible, and the number of questions Karen has, respectively.

The next $ n $ lines describe the recipes. Specifically, the $ i $ -th line among these contains two integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=200000 $ ), describing that the $ i $ -th recipe suggests that the coffee be brewed between $ l_{i} $ and $ r_{i} $ degrees, inclusive.

The next $ q $ lines describe the questions. Each of these lines contains $ a $ and $ b $ , ( $ 1<=a<=b<=200000 $ ), describing that she wants to know the number of admissible integer temperatures between $ a $ and $ b $ degrees, inclusive.

## 输出格式

For each question, output a single integer on a line by itself, the number of admissible integer temperatures between $ a $ and $ b $ degrees, inclusive.

## 说明/提示

In the first test case, Karen knows $ 3 $ recipes.

1. The first one recommends brewing the coffee between $ 91 $ and $ 94 $ degrees, inclusive.
2. The second one recommends brewing the coffee between $ 92 $ and $ 97 $ degrees, inclusive.
3. The third one recommends brewing the coffee between $ 97 $ and $ 99 $ degrees, inclusive.

A temperature is admissible if at least $ 2 $ recipes recommend it.

She asks $ 4 $ questions.

In her first question, she wants to know the number of admissible integer temperatures between $ 92 $ and $ 94 $ degrees, inclusive. There are $ 3 $ : $ 92 $ , $ 93 $ and $ 94 $ degrees are all admissible.

In her second question, she wants to know the number of admissible integer temperatures between $ 93 $ and $ 97 $ degrees, inclusive. There are $ 3 $ : $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In her third question, she wants to know the number of admissible integer temperatures between $ 95 $ and $ 96 $ degrees, inclusive. There are none.

In her final question, she wants to know the number of admissible integer temperatures between $ 90 $ and $ 100 $ degrees, inclusive. There are $ 4 $ : $ 92 $ , $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In the second test case, Karen knows $ 2 $ recipes.

1. The first one, "wikiHow to make Cold Brew Coffee", recommends brewing the coffee at exactly $ 1 $ degree.
2. The second one, "What good is coffee that isn't brewed at at least $ 36.3306 $ times the temperature of the surface of the sun?", recommends brewing the coffee at exactly $ 200000 $ degrees.

A temperature is admissible if at least $ 1 $ recipe recommends it.

In her first and only question, she wants to know the number of admissible integer temperatures that are actually reasonable. There are none.

## 样例 #1

### 输入

```
3 2 4
91 94
92 97
97 99
92 94
93 97
95 96
90 100

```

### 输出

```
3
3
0
4

```

## 样例 #2

### 输入

```
2 1 1
1 1
200000 200000
90 100

```

### 输出

```
0

```

