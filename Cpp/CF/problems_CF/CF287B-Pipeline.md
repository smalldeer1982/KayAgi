---
title: "Pipeline"
layout: "post"
diff: 普及+/提高
pid: CF287B
tag: []
---

# Pipeline

## 题目描述

Vova, the Ultimate Thule new shaman, wants to build a pipeline. As there are exactly $ n $ houses in Ultimate Thule, Vova wants the city to have exactly $ n $ pipes, each such pipe should be connected to the water supply. A pipe can be connected to the water supply if there's water flowing out of it. Initially Vova has only one pipe with flowing water. Besides, Vova has several splitters.

A splitter is a construction that consists of one input (it can be connected to a water pipe) and $ x $ output pipes. When a splitter is connected to a water pipe, water flows from each output pipe. You can assume that the output pipes are ordinary pipes. For example, you can connect water supply to such pipe if there's water flowing out from it. At most one splitter can be connected to any water pipe.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF287B/d347ad4c15760876dd4efdb4df653ce9dd1bfe47.png)The figure shows a $ 4 $ -output splitterVova has one splitter of each kind: with $ 2 $ , $ 3 $ , $ 4 $ , ..., $ k $ outputs. Help Vova use the minimum number of splitters to build the required pipeline or otherwise state that it's impossible.

Vova needs the pipeline to have exactly $ n $ pipes with flowing out water. Note that some of those pipes can be the output pipes of the splitters.

## 输入格式

The first line contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=10^{18} $ , $ 2<=k<=10^{9} $ ).

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

Print a single integer — the minimum number of splitters needed to build the pipeline. If it is impossible to build a pipeline with the given splitters, print -1.

## 样例 #1

### 输入

```
4 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 5

```

### 输出

```
1

```

## 样例 #3

### 输入

```
8 4

```

### 输出

```
-1

```

