---
title: "Present"
layout: "post"
diff: 普及+/提高
pid: CF460C
tag: ['模拟', '线段树', '差分']
---

# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 输入格式

The first line contains space-separated integers $ n $ , $ m $ and $ w $ $ (1<=w<=n<=10^{5}; 1<=m<=10^{5}) $ . The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the maximum final height of the smallest flower.

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 5 1
5 8

```

### 输出

```
9

```

