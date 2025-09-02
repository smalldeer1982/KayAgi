---
title: "Fight the Monster"
layout: "post"
diff: 普及+/提高
pid: CF487A
tag: []
---

# Fight the Monster

## 题目描述

A monster is attacking the Cyberland!

Master Yang, a braver, is going to beat the monster. Yang and the monster each have 3 attributes: hitpoints ( $ HP $ ), offensive power ( $ ATK $ ) and defensive power ( $ DEF $ ).

During the battle, every second the monster's HP decrease by $ max(0,ATK_{Y}-DEF_{M}) $ , while Yang's HP decreases by $ max(0,ATK_{M}-DEF_{Y}) $ , where index $ Y $ denotes Master Yang and index $ M $ denotes monster. Both decreases happen simultaneously Once monster's $ HP<=0 $ and the same time Master Yang's $ HP>0 $ , Master Yang wins.

Master Yang can buy attributes from the magic shop of Cyberland: $ h $ bitcoins per $ HP $ , $ a $ bitcoins per $ ATK $ , and $ d $ bitcoins per $ DEF $ .

Now Master Yang wants to know the minimum number of bitcoins he can spend in order to win.

## 输入格式

A monster is attacking the Cyberland!

Master Yang, a braver, is going to beat the monster. Yang and the monster each have 3 attributes: hitpoints ( $ HP $ ), offensive power ( $ ATK $ ) and defensive power ( $ DEF $ ).

During the battle, every second the monster's HP decrease by $ max(0,ATK_{Y}-DEF_{M}) $ , while Yang's HP decreases by $ max(0,ATK_{M}-DEF_{Y}) $ , where index $ Y $ denotes Master Yang and index $ M $ denotes monster. Both decreases happen simultaneously Once monster's $ HP<=0 $ and the same time Master Yang's $ HP>0 $ , Master Yang wins.

Master Yang can buy attributes from the magic shop of Cyberland: $ h $ bitcoins per $ HP $ , $ a $ bitcoins per $ ATK $ , and $ d $ bitcoins per $ DEF $ .

Now Master Yang wants to know the minimum number of bitcoins he can spend in order to win.

## 输出格式

The only output line should contain an integer, denoting the minimum bitcoins Master Yang should spend in order to win.

## 说明/提示

For the first sample, prices for $ ATK $ and $ DEF $ are extremely high. Master Yang can buy $ 99 $ HP, then he can beat the monster with $ 1 $ HP left.

For the second sample, Master Yang is strong enough to beat the monster, so he doesn't need to buy anything.

## 样例 #1

### 输入

```
1 2 1
1 100 1
1 100 100

```

### 输出

```
99

```

## 样例 #2

### 输入

```
100 100 100
1 1 1
1 1 1

```

### 输出

```
0

```

