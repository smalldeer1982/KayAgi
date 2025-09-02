---
title: "Island Puzzle"
layout: "post"
diff: 普及/提高-
pid: CF634A
tag: []
---

# Island Puzzle

## 题目描述

A remote island chain contains $ n $ islands, labeled $ 1 $ through $ n $ . Bidirectional bridges connect the islands to form a simple cycle — a bridge connects islands $ 1 $ and $ 2 $ , islands $ 2 $ and $ 3 $ , and so on, and additionally a bridge connects islands $ n $ and $ 1 $ . The center of each island contains an identical pedestal, and all but one of the islands has a fragile, uniquely colored statue currently held on the pedestal. The remaining island holds only an empty pedestal.

The islanders want to rearrange the statues in a new order. To do this, they repeat the following process: First, they choose an island directly adjacent to the island containing an empty pedestal. Then, they painstakingly carry the statue on this island across the adjoining bridge and place it on the empty pedestal.

Determine if it is possible for the islanders to arrange the statues in the desired order.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=200000 $ ) — the total number of islands.

The second line contains $ n $ space-separated integers $ a_{i} $ ( $ 0<=a_{i}<=n-1 $ ) — the statue currently placed on the $ i $ -th island. If $ a_{i}=0 $ , then the island has no statue. It is guaranteed that the $ a_{i} $ are distinct.

The third line contains $ n $ space-separated integers $ b_{i} $ ( $ 0<=b_{i}<=n-1 $ ) — the desired statues of the $ i $ th island. Once again, $ b_{i}=0 $ indicates the island desires no statue. It is guaranteed that the $ b_{i} $ are distinct.

## 输出格式

Print "YES" (without quotes) if the rearrangement can be done in the existing network, and "NO" otherwise.

## 说明/提示

In the first sample, the islanders can first move statue $ 1 $ from island $ 1 $ to island $ 2 $ , then move statue $ 2 $ from island $ 3 $ to island $ 1 $ , and finally move statue $ 1 $ from island $ 2 $ to island $ 3 $ .

In the second sample, the islanders can simply move statue $ 1 $ from island $ 1 $ to island $ 2 $ .

In the third sample, no sequence of movements results in the desired position.

## 样例 #1

### 输入

```
3
1 0 2
2 0 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2
1 0
0 1

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
4
1 2 3 0
0 3 2 1

```

### 输出

```
NO

```

