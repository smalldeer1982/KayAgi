---
title: "Scrambled"
layout: "post"
diff: 难度0
pid: CF656B
tag: []
---

# Scrambled

## 题目描述

Btoh yuo adn yuor roomatme lhoate wianshg disehs, btu stlil sdmoeboy msut peorrfm tihs cohre dialy. Oen dya yuo decdie to idourtcne smoe syestm. Yuor rmmotaoe sstgegus teh fooniwllg dael. Yuo argee on tow arayrs of ientgres M adn R, nmebur upmicnog dyas (induiclng teh cunrret oen) wtih sicsescuve irnegets (teh ceurrnt dya is zreo), adn yuo wsah teh diehss on dya D if adn olny if terhe etsixs an iednx i scuh taht $ D mod M[i]=R[i] $ , otwsehrie yuor rmootmae deos it. Yuo lkie teh cncepot, btu yuor rmotaome's cuinnng simle meaks yuo ssecupt sthnoemig, so yuo itennd to vefriy teh fnerisas of teh aemnrgeet.

Yuo aer geivn ayarrs M adn R. Cuaclatle teh pceanregte of dyas on wchih yuo edn up dnoig teh wisahng. Amsuse taht yuo hvae iiiftlneny mnay dyas aehad of yuo.

## 输入格式

The first line of input contains a single integer N ( $ 1<=N<=16 $ ).

The second and third lines of input contain N integers each, all between 0 and 16, inclusive, and represent arrays M and R, respectively. All $ M[i] $ are positive, for each $ i $ $ R[i]<M[i] $ .

## 输出格式

Output a single real number. The answer is considered to be correct if its absolute or relative error does not exceed $ 10^{-4} $ .

## 说明/提示

both you and roommate loathe washing dishes, but still somebody must perform this chore daily. One day you decide to introduce some system. Your roommate suggests the following deal. You agree on two arrays of integers M and R, number upcoming days (including the current one) with successive integers (the current day is zero), and you wash the dishes on day D if and only if there exists an index i such that D mod M[i]=R[i] ,otherwise your roommate does it. You like the concept, but your roommate’s cunning smile makes you suspect something, so you intend to verify the fairness of the agreement. You are given arrays M and R. Calculate the percentage of days on which you end up doing the washing. Assume that you have infinitely many days ahead of you.

## 样例 #1

### 输入

```
1
2
0

```

### 输出

```
0.500000

```

## 样例 #2

### 输入

```
2
2 3
1 0

```

### 输出

```
0.666667

```

