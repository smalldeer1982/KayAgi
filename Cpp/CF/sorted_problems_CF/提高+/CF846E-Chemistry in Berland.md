---
title: "Chemistry in Berland"
layout: "post"
diff: 提高+/省选-
pid: CF846E
tag: []
---

# Chemistry in Berland

## 题目描述

Igor is a post-graduate student of chemistry faculty in Berland State University (BerSU). He needs to conduct a complicated experiment to write his thesis, but laboratory of BerSU doesn't contain all the materials required for this experiment.

Fortunately, chemical laws allow material transformations (yes, chemistry in Berland differs from ours). But the rules of transformation are a bit strange.

Berland chemists are aware of $ n $ materials, numbered in the order they were discovered. Each material can be transformed into some other material (or vice versa). Formally, for each $ i $ $ (2<=i<=n) $ there exist two numbers $ x_{i} $ and $ k_{i} $ that denote a possible transformation: $ k_{i} $ kilograms of material $ x_{i} $ can be transformed into $ 1 $ kilogram of material $ i $ , and $ 1 $ kilogram of material $ i $ can be transformed into $ 1 $ kilogram of material $ x_{i} $ . Chemical processing equipment in BerSU allows only such transformation that the amount of resulting material is always an integer number of kilograms.

For each $ i $ ( $ 1<=i<=n $ ) Igor knows that the experiment requires $ a_{i} $ kilograms of material $ i $ , and the laboratory contains $ b_{i} $ kilograms of this material. Is it possible to conduct an experiment after transforming some materials (or none)?

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=10^{5} $ ) — the number of materials discovered by Berland chemists.

The second line contains $ n $ integer numbers $ b_{1},b_{2}...\ b_{n} $ ( $ 1<=b_{i}<=10^{12} $ ) — supplies of BerSU laboratory.

The third line contains $ n $ integer numbers $ a_{1},a_{2}...\ a_{n} $ ( $ 1<=a_{i}<=10^{12} $ ) — the amounts required for the experiment.

Then $ n-1 $ lines follow. $ j $ -th of them contains two numbers $ x_{j+1} $ and $ k_{j+1} $ that denote transformation of $ (j+1) $ -th material ( $ 1<=x_{j+1}<=j,1<=k_{j+1}<=10^{9} $ ).

## 输出格式

Print YES if it is possible to conduct an experiment. Otherwise print NO.

## 样例 #1

### 输入

```
3
1 2 3
3 2 1
1 1
1 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3
3 2 1
1 2 3
1 1
1 2

```

### 输出

```
NO

```

