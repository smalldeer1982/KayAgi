---
title: "Sonya Partymaker"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF713E
tag: []
---

# Sonya Partymaker

## 题目描述

Owl Sonya decided to become a partymaker. To train for this role she gather all her owl friends in the country house. There are $ m $ chairs located in a circle and consequently numbered with integers from $ 1 $ to $ m $ . Thus, chairs $ i $ and $ i+1 $ are neighbouring for all $ i $ from $ 1 $ to $ m-1 $ . Chairs $ 1 $ and $ m $ are also neighbouring. Some chairs are occupied by her friends. There are $ n $ friends in total. No two friends occupy the same chair. Rules are the following:

1. Each participant removes from the game the chair he is currently sitting on.
2. Each of the participants choose a direction that she will follow: clockwise (indices increase, from $ m $ goes to $ 1 $ ) and counter-clockwise (indices decrease, from $ 1 $ goes to $ m $ ). This direction may coincide or be different for any pair of owls.
3. Each turn all guests move one step in the chosen directions. If some guest move to the position with a chair there, he removes this chair from the game.
4. Game ends if there are no more chairs left in the game.

Owls are very busy and want to get rid of the game as soon as possible. They cooperate to pick the direction. Your goal is to find the minimum number o moves required to finish the game.

## 输入格式

The first line of the input contains a single integer $ m $ ( $ 1<=m<=10^{9} $ ) — the length of the circle.

The second line contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of friends.

Last line contains an increasing sequence of $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=m $ ) — initial positions of all owls.

## 输出格式

Print the minimum number of move required to finish the game. Note, that $ 0 $ also may be an answer.

## 说明/提示

In the first sample, it's possible if all owls will move clockwise, i.e. in the direction of increasing indices.

In the sample, first owl has to move clockwise, while the second — counterclockwise.

In the third sample, the first and the fourth owls should move counterclockwise, while the third and the sixth — clockwise. The second and the firth may move in any direction.

## 样例 #1

### 输入

```
6
3
1 3 5

```

### 输出

```
1

```

## 样例 #2

### 输入

```
6
2
1 6

```

### 输出

```
2

```

## 样例 #3

### 输入

```
406
6
1 2 3 204 205 206

```

### 输出

```
100

```

