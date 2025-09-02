---
title: "ANARC08J - A Day at the Races"
layout: "post"
diff: 难度0
pid: SP4559
tag: []
---

# ANARC08J - A Day at the Races

## 题目描述

一级方程式赛车是汽车比赛中最顶级的一类赛事。一个典型的赛季由一系列比赛组成，这些比赛被称为“大奖赛”。像法拉利、雷诺这样的车队会派出世界顶尖车手驾驶的赛车参赛。在整个赛季中，车队争夺两个锦标赛的冠军：车手锦标赛和车队锦标赛。

在车手锦标赛中，车手们的目标是在赛季结束时获得最高的总积分。比赛规则规定，在每场大奖赛中，前八名车手分别获得10、8、6、5、4、3、2、1分。如果积分相同，比较第一名次数较多的车手，若仍相同则比较第二名次数，以此类推至第八名。如果仍不能分出高下，则按姓氏及名字的字典序排列。

每场比赛后，各个车手获得的积分会累计到他们所属的车队中。赛季结束时，总积分最高的车队将赢得车队锦标赛。为了增加赛季的刺激性，赞助商被允许在赛季中途购买其他车队的车手。如果车队积分相同，则按车队名称的字典序排序。你的任务是根据提供的数据，按照上述规则计算出车手和车队的排名情况。

## 输入格式

你的程序会处理一个或多个数据集，每个数据集代表一个一级方程式赛季。所有输入行不超过255个字符。从样例输入输出可以看出，每个赛季数据的第一行是一个整数$N$，其中$0 < N < 32$，表示该赛季的大奖赛数量。每场大奖赛的名称单独占一行（最长64个字符），接着是一张表格，列出该场比赛中前八名车手的名字、姓氏和所属车队。每个名字和姓氏都是至多12个字符的可打印ASCII字符，且不包含空格。每个车队名称由可打印的ASCII字符组成，最长18个字符，可能包含空格（但无前导或尾随空格）。车队名称后跟一个点号`.`，该点号不计入名称。每场比赛的列表之后有一行由三个破折号`---`组成的行。输入的最后一行是一个零。

## 输出格式

对于每个数据集，按以下格式输出结果：首先输出“Season k :”，其中$k$为数据集编号（从1开始）。下一行输出“Drivers Standing:”。然后依次列出该赛季的车手排名。每位车手的名字和姓氏之间用一个空格隔开，名字部分左对齐且占用25个字符宽度，后接一个空格，再接车手的总积分。车手排名空一行后，输出“Teams Standing:”。接下来列出车队排名，每个车队名称左对齐，占用25个字符宽度，后跟一个空格，再显示该车队的总积分。车队排名结束后空一行。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2 
FORMULA 1 Gran Premio Telefonica de Espana 2006
Pos  Driver                    Team
1    Fernando Alonso           Renault.
2    Michael Schumacher        Ferrari.
3    Giancarlo Fisichella      Renault.
4    Felipe Massa              Ferrari.
5    Kimi Raikkonen            McLaren-Mercedes.
6    Jenson Button             Honda.
7    Rubens Barrichello        Honda.
8    Nick Heidfeld             Sauber-BMW.
---
FORMULA 1 Grand Prix de Monaco 2006
Pos  Driver                    Team
1    Fernando Alonso           Renault.
2    Jaun-Pablo Montoya        McLaren-Mercedes.
3    David Coulthard           RBR-Ferrari.
4    Rubens Barrichello        Honda.
5    Michael Schumacher        Ferrari.
6    Giancarlo Fisichella      Renault.
7    Nick Heidfeld             Sauber-BMW.
8    Ralf Schumacher           Toyota.
---
0
```

### 输出

```
Season 1:
Drivers Standing:
Fernando Alonso          20
Michael Schumacher       12
Giancarlo Fisichella     9
Jaun-Pablo Montoya       8
Rubens Barrichello       7
David Coulthard          6
Felipe Massa             5
Kimi Raikkonen           4
Jenson Button            3
Nick Heidfeld            3
Ralf Schumacher          1

Teams Standing:
Renault                  29
Ferrari                  17
McLaren-Mercedes         12
Honda                    10
RBR-Ferrari              6
Sauber-BMW               3
Toyota                   1
```

