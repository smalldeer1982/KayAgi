---
title: "Football Championship"
layout: "post"
diff: 普及+/提高
pid: CF200C
tag: []
---

# Football Championship

## 题目描述

这个题目是说，Berland的国家队成功加入一场足球联赛的半决赛。下面是球赛的规则：

**·** 两队比赛，比赛结束后哪支队伍进的球比对方队伍多，哪方获胜。

**·** 胜利得3分，平局两队各得1分，失败不得分（得0分）。

**·** 这四队中得到第一或第二的队伍进入下一轮。

每个队伍的名次是由总得分来算的：分越多，名次越高。如果两个队伍有同样的分，以下列方式来决定高低（越靠前的规则越优先考虑，如果还是不能分出高低，再往下判断。下列第一个权重最高）：

**·** 每个队的进球数减去失球数，得到的结果越高排名就越高。

**·** 总进球数越高，排名就越高。

**·** 如果以上都不行的话，则以字典序排列。

现在还有一场比赛未打。一共6场比赛，已知前五场的队伍与得分。某个队伍和Berland还没交战。教练想让你找到如此X:Y（X是Berland的得分，Y是另一只球队的得分），可以满足下列条件：

**·** X>Y，Berland得赢；

**·** Berland赢后，得进前二名；

**·** 如果不止一种答案，尽可能让X-Y小；

**·** 如果还是有很多答案（不止一个），你应该让Y尽可能小。

## 输入格式

一共有五行。

每一行都是以“team1 team2 goals1:goals2”（没引号）形式出现。表示team1跟team2交战一局。team1进了goal1个球，team2进了goal2个球。team1和team2都是非空字符串，并且都是大写字母，总长度不超过20。goal1和goal2都是0~9的正整数。

Berland队名字是"BERLAND"。保证只有Berland和另一支队伍打了2场比赛，其他队打了3场。

## 输出格式

输出比分X:Y。X是Berland分数，Y是另一只球队的分数。如果怎么样也无法得到第一或第二，输出一行"IMPOSSIBLE"（没引号）。

提示：最后一场分数也不一定小，比如10:0这种情况。

## 样例 #1

### 输入

```
AERLAND DERLAND 2:1
DERLAND CERLAND 0:3
CERLAND AERLAND 0:1
AERLAND BERLAND 2:0
DERLAND BERLAND 4:0

```

### 输出

```
6:0

```

## 样例 #2

### 输入

```
AERLAND DERLAND 2:2
DERLAND CERLAND 2:3
CERLAND AERLAND 1:3
AERLAND BERLAND 2:1
DERLAND BERLAND 4:1

```

### 输出

```
IMPOSSIBLE

```

