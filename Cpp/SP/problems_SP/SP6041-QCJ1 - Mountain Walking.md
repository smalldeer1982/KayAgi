---
title: "QCJ1 - Mountain Walking"
layout: "post"
diff: 难度0
pid: SP6041
tag: []
---

# QCJ1 - Mountain Walking

## 题目描述

在这道题中你的任务是去操控一个机器人勘探一座山。

这座山用一个2D平面描述，由四种字符构成
```
'/':Up,向上
'_':Walk,前进
'\':Down,向下

' ':空格，啥都不表示
```
机器人从地图的左下角开始走，在右下角结束。（起点和终点位于同一行上。）

输出分为两个部分。

第一部分：你需要输出机器人行走的步数（向上，前进，向下都算为1步）

第二部分：走完路程所采取的步骤类型及步数。

例如这样一座山：
```
   _
  / \/\
 /     \
/       \
```
机器人从左下角开始，经过了这样的历程：向上三步，前进一步，向下一步，向上一步，向下三步。之后结束。总路程为9。

## 输入格式

第一行是一个正整数N(N<20)。

第二行是空行。

接着N行描述这座山，每行只可能由`' '`,`'/'`,`'\'`,`'_'`四种字符组成，每行至少会有一个非空格的字符。每行的长度不超过200，且末尾不会有多余空格。

## 输出格式

第一行输出`Total Walk Distance = xx`。

接下来输出多行，每行必须是`Up xx steps`,`Walk xx steps`,`Down xx steps`中的一种（其中xx是一个正整数。）
## 样例
```
Input#1:
3

  /\
 /  \
/    \

Output#1:
Total Walk Distance = 6
Up 3 steps
Down 3 steps
```
```
Input#2:
2

 _____  ___
/     \/   \

Output#2:
Total Walk Distance = 12
Up 1 steps
Walk 5 steps
Down 1 steps
Up 1 steps
Walk 3 steps
Down 1 steps
```
```
Input#3:
5

        _
   /\__/ \
  /       \
 /         \/\_
/              \

Output#3:
Total Walk Distance = 16
Up 4 steps
Down 1 steps
Walk 2 steps
Up 1 steps
Walk 1 steps
Down 3 steps
Up 1 steps
Down 1 steps
Walk 1 steps
Down 1 steps
```

## 样例 #1

### 输入

```
3

  /\
 /  \
/    \
```

### 输出

```
Total Walk Distance = 6
Up 3 steps
Down 3 steps
```

