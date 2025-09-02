---
title: "MEXICAN - Mexican Standoff"
layout: "post"
diff: 难度0
pid: SP5300
tag: []
---

# MEXICAN - Mexican Standoff

## 题目描述

圣萨巴镇实在太小，容不下两名枪手同居。不巧的是，所有的枪手都在一个晴朗的春日早晨聚集在此。事情演变至此，是因为他们都想赢得警长女儿艾丽斯的芳心。既然只有一人能如愿，他们决定用绅士的方式解决问题——进行一场墨西哥式决斗。

决斗有多个回合。在每个回合中，所有存活的枪手会聚集成一个圈，面朝圆心。为了不在排列位置时争执，他们决定按照名字的字典序排列，然后连接队伍两端形成一个圆圈。所有人就位后，艾丽斯会将一条丝巾扔在地上，当丝巾落地时，枪手们同时拔出左手和右手的枪并开火。每个人的左手枪瞄准左边的同伴，右手枪瞄准右边的同伴。由于枪手们反应时间不同，因此开火时间也不尽相同。如果有人在开枪之前被击中，他将死亡，无法开火。如果两人同时向对方开火，他们会一起死去。每轮结束后，存活的人会移走死者，再准备进行下一轮。如果某轮结束后只剩一人存活，决斗就结束，幸运者将迎娶艾丽斯。如果某轮之后无人生还，那艾丽斯将继续单身。

艾丽斯只喜欢其中的某些人。因此，她决定在每回合开始前，从一名枪手的左枪或右枪中（但不能两边一起）卸掉一颗子弹。出于懒惰，她想知道最少需要多少回合卸掉子弹才能确保嫁给她喜欢的人。如果她不喜欢任何人，意味着她希望继续单身。

## 输入格式

第一行输入的是测试用例数量 $T$（$1 \le T \le 30$）。每个测试用例的第一行包含枪手数量 $N$（$2 \le N \le 60$）。接下来的 $N$ 行中，每行包含一个枪手的名字（由 1 到 20 个小写字母组成，每个名字唯一）、他的反应时间（以毫秒为单位，$1 \le$ 反应时间 $\le 1000$）以及艾丽斯是否喜欢他（用 Y 或 N 表示），用空格隔开。

## 输出格式

对每个测试用例，输出一个整数，表示艾丽斯需要最少卸掉子弹的回合数以实现愿望；如果无法实现则输出 -1。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n3\n3\ngood 100 Y\nbad 200 N\nugly 100 N\n3 \ngood 100 N\nbad 200 N\nugly 100 N\n3 \ngood 100 Y\nbad 100 N\nugly 100 N\n\n
```

### 输出

```
1\n0 \n-1\n\nExplanation\n1. Alice likes only Good, so she removes a bullet from the gun which Ugly will use to fire at Good.\nGood survives while Bad and Ugly are killed.\n2. Alice doesn't like any of them, and she doesn't have to lift a finger to remain single.\n3. Alice likes only Good, but all of them are equally fast, so she can't save him and will remain\nsingle in his memory.
```

