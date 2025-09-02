---
title: "Legen..."
layout: "post"
diff: 省选/NOI-
pid: CF696D
tag: []
---

# Legen...

## 题目描述

Barney was hanging out with Nora for a while and now he thinks he may have feelings for her. Barney wants to send her a cheesy text message and wants to make her as happy as possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696D/5ab3ea47563ae6400cc578e63bb9e0de4cf3a082.png)Initially, happiness level of Nora is $ 0 $ . Nora loves some pickup lines like "I'm falling for you" and stuff. Totally, she knows $ n $ pickup lines, each consisting only of lowercase English letters, also some of them may be equal (in writing, but different in pronouncing or meaning though). Every time Nora sees $ i $ -th pickup line as a consecutive subsequence of Barney's text message her happiness level increases by $ a_{i} $ . These substrings may overlap, for example, Nora will see the pickup line aa twice and the pickup line ab once in text message aaab.

Due to texting app limits, Barney's text may have up to $ l $ characters.

Barney asked you to help him make Nora as much happy as possible, it's gonna be legen...

## 输入格式

The first line of input contains two integers $ n $ and $ l $ ( $ 1<=n<=200,1<=l<=10^{14} $ ) — the number of pickup lines and the maximum length of Barney's text.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=100 $ ), meaning that Nora's happiness level increases by $ a_{i} $ after every time seeing $ i $ -th pickup line.

The next $ n $ lines contain the pickup lines. $ i $ -th of them contains a single string $ s_{i} $ consisting of only English lowercase letter. Summary length of all pickup lines does not exceed $ 200 $ .

All strings are not empty.

## 输出格式

Print the only integer — the maximum possible value of Nora's happiness level after reading Barney's text.

## 说明/提示

An optimal answer for the first sample case is hearth containing each pickup line exactly once.

An optimal answer for the second sample case is artart.

## 样例 #1

### 输入

```
3 6
3 2 1
heart
earth
art

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3 6
3 2 8
heart
earth
art

```

### 输出

```
16

```

