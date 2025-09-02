---
title: "Peculiar apple-tree"
layout: "post"
diff: 普及/提高-
pid: CF930A
tag: []
---

# Peculiar apple-tree

## 题目描述

In Arcady's garden there grows a peculiar apple-tree that fruits one time per year. Its peculiarity can be explained in following way: there are $ n $ inflorescences, numbered from $ 1 $ to $ n $ . Inflorescence number $ 1 $ is situated near base of tree and any other inflorescence with number $ i $ ( $ i&gt;1 $ ) is situated at the top of branch, which bottom is $ p_{i} $ -th inflorescence and $ p_{i}&lt;i $ .

Once tree starts fruiting, there appears exactly one apple in each inflorescence. The same moment as apples appear, they start to roll down along branches to the very base of tree. Each second all apples, except ones in first inflorescence simultaneously roll down one branch closer to tree base, e.g. apple in $ a $ -th inflorescence gets to $ p_{a} $ -th inflorescence. Apples that end up in first inflorescence are gathered by Arcady in exactly the same moment. Second peculiarity of this tree is that once two apples are in same inflorescence they annihilate. This happens with each pair of apples, e.g. if there are $ 5 $ apples in same inflorescence in same time, only one will not be annihilated and if there are $ 8 $ apples, all apples will be annihilated. Thus, there can be no more than one apple in each inflorescence in each moment of time.

Help Arcady with counting number of apples he will be able to collect from first inflorescence during one harvest.

## 输入格式

First line of input contains single integer number $ n $ ( $ 2<=n<=100000 $ ) — number of inflorescences.

Second line of input contains sequence of $ n-1 $ integer numbers $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}&lt;i $ ), where $ p_{i} $ is number of inflorescence into which the apple from $ i $ -th inflorescence rolls down.

## 输出格式

Single line of output should contain one integer number: amount of apples that Arcady will be able to collect from first inflorescence during one harvest.

## 说明/提示

In first example Arcady will be able to collect only one apple, initially situated in $ 1 $ st inflorescence. In next second apples from $ 2 $ nd and $ 3 $ rd inflorescences will roll down and annihilate, and Arcady won't be able to collect them.

In the second example Arcady will be able to collect 3 apples. First one is one initially situated in first inflorescence. In a second apple from $ 2 $ nd inflorescence will roll down to $ 1 $ st (Arcady will collect it) and apples from $ 3 $ rd, $ 4 $ th, $ 5 $ th inflorescences will roll down to $ 2 $ nd. Two of them will annihilate and one not annihilated will roll down from $ 2 $ -nd inflorescence to $ 1 $ st one in the next second and Arcady will collect it.

## 样例 #1

### 输入

```
3
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2 2 2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
18
1 1 1 4 4 3 2 2 2 10 8 9 9 9 10 10 4

```

### 输出

```
4

```

