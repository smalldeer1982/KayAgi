---
title: "DCEPC703 - Totient Game"
layout: "post"
diff: 难度0
pid: SP11474
tag: []
---

# DCEPC703 - Totient Game

## 题目描述

Bahl 和 Debnath 总是喜欢在网上寻找新奇的游戏。昨天，Bahl 偶然间发现了一款名为“Totient 游戏”的新游戏，并迫不及待地展示给了 Debnath。他们觉得这个游戏非常有趣，于是决定一同尝试。游戏规则如下：

1. 游戏中有 $N$ 堆石子。
2. 两位玩家轮流操作，每次可以选择一堆石子，将其分成两个大小不等的堆，分别为 $i$ 和 $j$。要求 $\text{Totient}(i) \times \text{Totient}(j) = \text{Totient}(i \times j)$，同时 $i + j$ 等于该堆石子的原有数量。
3. 如果一个玩家无法进行有效操作，则该玩家输掉游戏。

Bahl 坚持要先手开始游戏。你能预测谁会赢吗？**假设双方都以最佳策略进行游戏。**

[了解更多关于欧拉函数的信息，请点击此处](http://en.wikipedia.org/wiki/Euler%27s_totient_function)

## 输入格式

第一行输入整数 $T$，表示测试用例的数量。

接下来的每个测试用例以两行形式给出：第一行是整数 $N$，表示石子堆的数量。第二行包含 $N$ 个用空格分隔的整数，每个整数表示一堆石子的数量。

## 输出格式

输出 $T$ 行，每行对应一个测试用例，表示获胜者。若 Bahl 获胜，输出 `Bahl`；若 Debnath 获胜，输出 `Debnath`。

## 说明/提示

$$1 \le T \le 100$$

$$1 \le N \le 100$$

$$1 \le \text{每堆石子的数量} \le 10^9$$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
3
1 2 3
```

### 输出

```
Bahl
```

