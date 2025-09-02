---
title: "Nikita and game"
layout: "post"
diff: 省选/NOI-
pid: CF842E
tag: ['最近公共祖先 LCA', '树的直径']
---

# Nikita and game

## 题目描述

Nikita plays a new computer game. There are $ m $ levels in this game. In the beginning of each level a new class appears in the game; this class is a child-class of the class $ y_{i} $ (and $ y_{i} $ is called parent-class for this new class). Thus, the classes form a tree. Initially there is only one class with index $ 1 $ .

Changing the class to its neighbour (child-class or parent-class) in the tree costs $ 1 $ coin. You can not change the class back. The cost of changing the class $ a $ to the class $ b $ is equal to the total cost of class changes on the path from $ a $ to $ b $ in the class tree.

Suppose that at $ i $ -th level the maximum cost of changing one class to another is $ x $ . For each level output the number of classes such that for each of these classes there exists some other class $ y $ , and the distance from this class to $ y $ is exactly $ x $ .

## 输入格式

First line contains one integer number $ m $ — number of queries ( $ 1<=m<=3·10^{5} $ ).

Next $ m $ lines contain description of queries. $ i $ -th line ( $ 1<=i<=m $ ) describes the $ i $ -th level and contains an integer $ y_{i} $ — the index of the parent-class of class with index $ i+1 $ ( $ 1<=y_{i}<=i $ ).

## 输出格式

Suppose that at $ i $ -th level the maximum cost of changing one class to another is $ x $ . For each level output the number of classes such that for each of these classes there exists some other class $ y $ , and the distance from this class to $ y $ is exactly $ x $ .

## 样例 #1

### 输入

```
4
1
1
2
1

```

### 输出

```
2
2
2
3

```

## 样例 #2

### 输入

```
4
1
1
2
3

```

### 输出

```
2
2
2
2

```

