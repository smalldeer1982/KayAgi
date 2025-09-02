---
title: "Businessmen Problems"
layout: "post"
diff: 普及-
pid: CF981B
tag: []
---

# Businessmen Problems

## 题目描述

Two famous competing companies ChemForces and TopChemist decided to show their sets of recently discovered chemical elements on an exhibition. However they know that no element should be present in the sets of both companies.

In order to avoid this representatives of both companies decided to make an agreement on the sets the companies should present. The sets should be chosen in the way that maximizes the total income of the companies.

All elements are enumerated with integers. The ChemForces company has discovered $ n $ distinct chemical elements with indices $ a_1, a_2, \ldots, a_n $ , and will get an income of $ x_i $ Berland rubles if the $ i $ -th element from this list is in the set of this company.

The TopChemist company discovered $ m $ distinct chemical elements with indices $ b_1, b_2, \ldots, b_m $ , and it will get an income of $ y_j $ Berland rubles for including the $ j $ -th element from this list to its set.

In other words, the first company can present any subset of elements from $ \{a_1, a_2, \ldots, a_n\} $ (possibly empty subset), the second company can present any subset of elements from $ \{b_1, b_2, \ldots, b_m\} $ (possibly empty subset). There shouldn't be equal elements in the subsets.

Help the representatives select the sets in such a way that no element is presented in both sets and the total income is the maximum possible.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of elements discovered by ChemForces.

The $ i $ -th of the next $ n $ lines contains two integers $ a_i $ and $ x_i $ ( $ 1 \leq a_i \leq 10^9 $ , $ 1 \leq x_i \leq 10^9 $ ) — the index of the $ i $ -th element and the income of its usage on the exhibition. It is guaranteed that all $ a_i $ are distinct.

The next line contains a single integer $ m $ ( $ 1 \leq m \leq 10^5 $ ) — the number of chemicals invented by TopChemist.

The $ j $ -th of the next $ m $ lines contains two integers $ b_j $ and $ y_j $ , ( $ 1 \leq b_j \leq 10^9 $ , $ 1 \leq y_j \leq 10^9 $ ) — the index of the $ j $ -th element and the income of its usage on the exhibition. It is guaranteed that all $ b_j $ are distinct.

## 输出格式

Print the maximum total income you can obtain by choosing the sets for both companies in such a way that no element is presented in both sets.

## 说明/提示

In the first example ChemForces can choose the set ( $ 3, 7 $ ), while TopChemist can choose ( $ 1, 2, 4 $ ). This way the total income is $ (10 + 2) + (4 + 4 + 4) = 24 $ .

In the second example ChemForces can choose the only element $ 10^9 $ , while TopChemist can choose ( $ 14, 92, 35 $ ). This way the total income is $ (239) + (15 + 65 + 89) = 408 $ .

## 样例 #1

### 输入

```
3
1 2
7 2
3 10
4
1 4
2 4
3 4
4 4

```

### 输出

```
24

```

## 样例 #2

### 输入

```
1
1000000000 239
3
14 15
92 65
35 89

```

### 输出

```
408

```

