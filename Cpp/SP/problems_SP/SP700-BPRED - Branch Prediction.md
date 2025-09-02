---
title: "BPRED - Branch Prediction"
layout: "post"
diff: 难度0
pid: SP700
tag: []
---

# BPRED - Branch Prediction

## 题目描述

众所周知，如今的 Intel 级高性能处理器通过并行处理多个任务来加速指令的执行。其中，最复杂的任务之一是分支预测。现代处理器将指令拆分成独立的部分并行执行，这就需要在实际用于条件判断的运算数可用前提前预测执行路径会走哪个分支。这项复杂的任务尚未得到彻底解决，但启发式方法正在发挥作用。

我们要解决的问题相较于实际的分支预测简单得多。假设程序中的每条指令格式如下：
- 所有标签均为仅由字母构成的字符串，并区分大小写。

此外，假设选中某个分支的概率为 **P**（所有分支概率相同）。如果分支被选中，程序控制流跳转到对应的标签；否则顺序执行下一条语句。程序从 "**start**"（小写）标签开始执行，并在 "**end**"（小写）标签结束。**start** 自身作跳转，执行完后控制流继续下一条指令；**end** 自身作跳转，执行后处理即以 100% 概率结束。程序的最后一行总是 "end"。

任务是计算指定语句的预期执行次数。

## 输入格式

输入包含若干组测试数据。  
第一行是一个整数 T，表示测试数据的组数。  
对于每组测试数据：  
第一行包含三个参数：一个整数 N（随后跟随的线路数），一个实数 P 和一个标签 L。  
接下来的 N 行每行定义一条指令（两个标签）。

## 输出格式

对于每组测试数据，输出一行：  
「标签 L 预期执行的次数是 R」，  
其中 L 是输入中指定的标签，  
R 是标签的预期执行次数，保留到小数点后五位。

## 说明/提示

- T ≤ 20
- 3 ≤ N ≤ 120
- P 介于 0.01 和 0.99 之间，即没有百分之百确定的跳转。
- 可以假设所有出现在跳转语句中的标签都已被定义。
- 每个标签长度不足 10 个字符。
- 每行各有一个唯一的标签。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n
  3\n
  5 .5 B\n
  C start\n
  start start\n
  B C\n

  D C\n
  end end\n
  5 .99 C\n
  start start\n
  A B\n
  B A\n

  C end\n
  end end\n
  3 .5 label\n
  start start\n
  label label\n
  end end
```

### 输出

```
\n
  Expected number of times label B is executed is 4.00000\n
  Expected number of times label C is executed is 1.00000\n
  Expected number of times label label is executed is 2.00000
```

