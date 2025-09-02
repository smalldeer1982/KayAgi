---
title: "MCLB - Magic Crystals and Laser Beams"
layout: "post"
diff: 难度0
pid: SP9968
tag: []
---

# MCLB - Magic Crystals and Laser Beams

## 题目描述

John 和 Ged 正在玩一个与魔法水晶和激光束有关的游戏。开始时，他们将 64 颗魔法水晶排成一行，两人站在这行水晶的右侧，用激光束射击这些水晶。水晶有两种颜色，每种颜色的行为不同。红色水晶会吸收激光束，而蓝色水晶则允许激光束穿过并作用到下一颗水晶。无论是哪种情况，水晶都会改变颜色：红色水晶会变成蓝色，蓝色水晶会变成红色。其他颜色的水晶由于行为不明确，不会参与游戏。当所有水晶都变成红色时，游戏结束。

玩了很久之后，John 想知道，在初始水晶状态下，经过多少次激光射击可以达到他设想的目标状态。在游戏结束前，请帮助他们确定能否实现这个目标。如果无法实现，请告诉他们。

**输入格式:**

水晶排列用字符串表示，字符串最右边代表这行水晶的末端。输入第一行为一个整数 $T$，表示测试用例的数量。接下来有 $2T$ 行输入，每个测试用例包含两行字符串，每行恰好 64 个字符，仅包含 R（红色）或 B（蓝色）。第一行为游戏的初始状态，第二行为 John 想检查是否可达的目标状态。

**输出格式:**

对每个测试用例，输出一行，格式为 **“Case K: 状态”**，其中 $K$ 是测试用例编号。状态要么是 “The goal state could be reached after X laser beams.”，要么是 “The goal state will never be reached!”，其中 $X$ 是达到目标状态所需的激光束次数。

**样例输入:**

3  
BBRRBRBRBRBBRBBBRBBRBRBBBRBBBRBRRRBBRBRBBRBRBRBRBBRBRBRBRRBBBBBR  
BBRRBRBRBRBBRBBBRBBRBRBBBRBBBRBRRRBBRBRBBRBRBRBRBBRBRBRBRBRRRRRR  
BBRRBRBRBRBBRBBBRBBRBRBBBRBBBRBRRRBBRBRBBRBRBRBRBBRBRBRBRRBBBBBR  
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR  
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR  
BBRRBRBRBRBBRBBBRBBRBRBBBRBBBRBRRRBBRBRBBRBRBRBRBBRBRBRBRRBBBBBR

**样例输出:**

Case 1: The goal state could be reached after 2 laser beams.  
Case 2: The goal state will never be reached!  
Case 3: The goal state will never be reached!

 **本翻译由 AI 自动生成**

