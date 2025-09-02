---
title: "SCAVHUNT - Scavenger Hunt"
layout: "post"
diff: 难度0
pid: SP3374
tag: []
---

# SCAVHUNT - Scavenger Hunt

## 题目描述

Bill 曾是美国最出色的童子军，因为他总能组织出最精彩的寻宝游戏（孩子们根据提示找出特定路线的游戏）而成为一名超级明星。如今 Bill 已经退休，不过，他的继任者很快就通过全国选举选出，一个名叫 George 的人。然而，George 表现不佳，他渴望从 Bill 的路线设计中学习经验。不巧的是，Bill 只留给继任者一些零碎的笔记。Bill 从未将完整路线记录下来，他只在小纸片上写下两个连续的步骤，然后把这些纸片混合在一起，通过不断练习来记忆这些路线，就像有些人为考试学习那样：反复阅读第一个步骤，试图记住接下来的步骤。这样做很合理，因为每一步通常都依赖前一步的信息。然而，George 希望能拥有一份按照正确顺序写好的完整路线。请帮助他重建这些路线，让全国人民重新获得快乐。

## 输入格式

第一行包含场景数量。每个场景描述一条路线，其第一行标明该路线共有多少个步骤（$3 \le S \le 333$）。接下来的 $S - 1$ 行，每行包含一对连续的步骤，用空格隔开。每个步骤的名称都是一个由字母组成的字符串。

## 输出格式

对于每个场景，先输出一行“Scenario #i:”，其中 i 为场景编号，从 1 开始。然后按正确顺序输出 $S$ 行，每行包含路线的一个步骤。每个场景的输出要以一个空行结束。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
4
SwimmingPool OldTree
BirdsNest Garage
Garage SwimmingPool
3
Toilet Hospital
VideoGame Toilet
```

### 输出

```
Scenario #1:
BirdsNest
Garage
SwimmingPool
OldTree

Scenario #2:
VideoGame
Toilet
Hospital
```

