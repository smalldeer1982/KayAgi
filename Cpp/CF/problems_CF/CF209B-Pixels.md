---
title: "Pixels"
layout: "post"
diff: 提高+/省选-
pid: CF209B
tag: []
---

# Pixels

## 题目描述

Flatland is inhabited by pixels of three colors: red, green and blue. We know that if two pixels of different colors meet in a violent fight, only one of them survives the fight (that is, the total number of pixels decreases by one). Besides, if pixels of colors $ x $ and $ y $ $ (x≠y) $ meet in a violent fight, then the pixel that survives the fight immediately changes its color to $ z $ $ (z≠x; z≠y) $ . Pixels of the same color are friends, so they don't fight.

The King of Flatland knows that his land will be peaceful and prosperous when the pixels are of the same color. For each of the three colors you know the number of pixels of this color that inhabit Flatland. Help the king and determine whether fights can bring peace and prosperity to the country and if it is possible, find the minimum number of fights needed to make the land peaceful and prosperous.

## 输入格式

The first line contains three space-separated integers $ a $ , $ b $ and $ c $ $ (0<=a,b,c<=2^{31}; a+b+c&gt;0) $ — the number of red, green and blue pixels, correspondingly.

## 输出格式

Print a single number — the minimum number of pixel fights before the country becomes peaceful and prosperous. If making the country peaceful and prosperous is impossible, print -1.

## 说明/提示

In the first test sample the country needs only one fight to achieve peace and prosperity. Besides, it can be any fight whatsoever. For example, let's assume that the green and the blue pixels fight, then the surviving pixel will be red. As a result, after the fight there are two red pixels. There won't be other pixels.

In the second sample the following sequence of fights is possible: red and blue, green and red, red and blue. As a result, after all fights there is one green pixel left.

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 1 0

```

### 输出

```
3

```

