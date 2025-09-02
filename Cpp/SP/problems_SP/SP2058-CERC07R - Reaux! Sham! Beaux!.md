---
title: "CERC07R - Reaux! Sham! Beaux!"
layout: "post"
diff: 难度0
pid: SP2058
tag: []
---

# CERC07R - Reaux! Sham! Beaux!

## 题目描述

Roshambo 是一个全球知名的简单游戏。在不同的国家和地区，各自有着不同的名字——在德语里叫「Schnick, Schnack, Schnuck」；日语称为「Janken」；西班牙语中是「Cachipún」；波兰语里是「Papier, kamień, nożyce」；而在捷克，叫做「Kámen, nůžky, papír」。

尽管名称各异，游戏的规则却如出一辙：两个玩家同时出手，摆出三种可能的形状之一：石头（紧握的拳头）、布（张开的手掌）或剪刀（伸出的两根手指）。如果两位玩家出示相同的形状，则为平局，双方都不得分。否则将根据石头砸剪刀，剪刀剪布，布包石头的规则决定胜负。

在捷克技术大学，一些学生也常用这个游戏来解决小争端。比如两个合住的学生，昨晚一起庆祝后今早没人愿意起床去听课。他们商定只有一个人去听课做笔记就好，可由谁去呢？此时，Roshambo 是一个高效的决策工具。

世界上甚至还有 Roshambo 的世界系列赛。我们的团队计划在 2009 年举办世界锦标赛。你的任务是帮我们开发一个 Roshambo 计分系统，编写一个程序评估两个玩家之间的比赛成绩。

由于参赛者来自不同的国家，系统需要能够识别各种语言的输入。下表列出了三种 Roshambo 符号在不同语言中的名称。需要注意的是，同一种符号在某些语言中可能有两个不同的名称。

| 语言       | 代码 | 石头                     | 剪刀            | 布                       |
|------------|------|-------------------------|-----------------|-------------------------|
| 捷克       | cs   | Kamen                   | Nuzky           | Papir                   |
| 英语       | en   | Rock                    | Scissors        | Paper                   |
| 法语       | fr   | Pierre                  | Ciseaux         | Feuille                 |
| 德语       | de   | Stein                   | Schere          | Papier                  |
| 匈牙利语   | hu   | Ko \| Koe               | Ollo \| Olloo   | Papir                   |
| 意大利语   | it   | Sasso \| Roccia         | Forbice         | Carta \| Rete           |
| 日语       | jp   | Guu                     | Choki           | Paa                     |
| 波兰语     | pl   | Kamien                  | Nozyce          | Papier                  |
| 西班牙语   | es   | Piedra                  | Tijera          | Papel                   |

## 输入格式

输入包含多场比赛的信息。每场比赛的信息以两行开始，分别描述两位玩家。每行包括两个小写字母表示的玩家语言代码（参见上表），一个空格和玩家的名字。名字最多由 20 个大写或小写字母组成。

玩家信息之后，是最多 100 行的每回合详细信息。每个回合使用两个用空格隔开的词描述，分别代表第一位和第二位玩家使用的符号，符号用玩家母语表示。所有允许的词在上表中列出，首字母大写，其他字母小写。

最后一回合后以一行破折号（"-"）定义比赛的结束，随即下一场比赛开始。唯一的例外是输入的最后一场比赛，以句点（"."）结束，而不是破折号。

## 输出格式

对每场比赛，输出五行信息。第一行格式为「Game #G:」，G 为游戏的编号，从 1 开始递增。

第二行格式为第一个玩家的名字后接一个冒号（":"）、一个空��和该玩家赢得的回合数。然后是一个空格和单词「points」。如果玩家的分数为 1，则用单数形式「point」。

第三行以相同形式显示第二个玩家的名字和分数。

第四行描述比赛结果。需写明「WINNER」，后接一个冒号、空格及得分更多的玩家姓名。如果两位玩家得分相同，则写「TIED GAME」。

第五行为空行，用于视觉上分隔各场比赛。

## 说明/提示

无

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
cs Pepik
en Johnny
Nuzky Scissors
Papir Rock
Papir Scissors
-
de Gertruda
cs Lenka
Stein Papir
Schere Kamen
.
```

### 输出

```
Game #1:
Pepik: 1 point
Johnny: 1 point
TIED GAME

Game #2:
Gertruda: 0 points
Lenka: 2 points
WINNER: Lenka
```

