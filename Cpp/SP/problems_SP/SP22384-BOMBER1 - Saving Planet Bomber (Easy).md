---
title: "BOMBER1 - Saving Planet Bomber (Easy)"
layout: "post"
diff: 难度0
pid: SP22384
tag: []
---

# BOMBER1 - Saving Planet Bomber (Easy)

## 题目描述

Jay 和 Nemo 是星际旅行者。在游历 Bomber 星云时，他们决定在著名的 Bingeling 帝国停留一段时间。为了方便管理开销，他们找到了一份在帮助 Bomberman 的科学家 Dr. Ein 手下的实习工作。

然而此时，凶恶的 Bomber 入侵者突破了星球 Bomber 的防御，占领了整个帝国。我们可以将帝国看作一个 **N×N×N** 的迷宫，其中每个格子都被敌人占据。也可以简单地将其看作一个边长为 **N** 的巨型立方体。

现在，Jay 和 Nemo 的任务是指导 Bomberman 安置炸弹来消灭敌人。得益于 Dr. Ein 的最新发明，Bomberman 的炸弹拥有无限的爆炸范围。也就是说，当炸弹在坐标 **(x, y, z)** 爆炸时，它不仅会摧毁所有位于 **(\*, y, z)** 的敌人，还能摧毁位于 **(x, \*, z)** 和 **(x, y, \*)** 的敌人。由于帝国的大部分资源已被敌人占领，他们只剩下 **M** 枚炸弹可用。尽管 Jay 和 Nemo 在计算机科学领域出类拔萃，但他们的三维空间想象力却较为贫乏。因此，他们请你——地球上最伟大的程序员来帮助他们判断：在给定的条件下，能否成功击败入侵者？

## 输入格式

第一行包含一个整数 **T**，表示测试用例的数量。接下来的 **T** 行中，每行包含两个以空格分隔的整数 **N** 和 **M**，分别表示迷宫的尺寸和可用的炸弹数量。

## 输出格式

对于每个测试用例，如果可以消灭所有敌人，输出 "`POSSIBLE`"；否则输出 "`IMPOSSIBLE`"。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4\n1 0\n1 1\n1 2\n2 1\n\n\n
```

### 输出

```
IMPOSSIBLE\nPOSSIBLE\nPOSSIBLE\nIMPOSSIBLE\n\n
Warning: Large I/O. Tested for most languages, but let me know if you are getting TLE.\n
```

