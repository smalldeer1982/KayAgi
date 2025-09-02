---
title: "Key races"
layout: "post"
diff: 入门
pid: CF835A
tag: []
---

# Key races

## 题目描述

Two boys decided to compete in text typing on the site "Key races". During the competition, they have to type a text consisting of $ s $ characters. The first participant types one character in $ v_{1} $ milliseconds and has ping $ t_{1} $ milliseconds. The second participant types one character in $ v_{2} $ milliseconds and has ping $ t_{2} $ milliseconds.

If connection ping (delay) is $ t $ milliseconds, the competition passes for a participant as follows:

1. Exactly after $ t $ milliseconds after the start of the competition the participant receives the text to be entered.
2. Right after that he starts to type it.
3. Exactly $ t $ milliseconds after he ends typing all the text, the site receives information about it.

The winner is the participant whose information on the success comes earlier. If the information comes from both participants at the same time, it is considered that there is a draw.

Given the length of the text and the information about participants, determine the result of the game.

## 输入格式

The first line contains five integers $ s $ , $ v_{1} $ , $ v_{2} $ , $ t_{1} $ , $ t_{2} $ ( $ 1<=s,v_{1},v_{2},t_{1},t_{2}<=1000 $ ) — the number of characters in the text, the time of typing one character for the first participant, the time of typing one character for the the second participant, the ping of the first participant and the ping of the second participant.

## 输出格式

If the first participant wins, print "First". If the second participant wins, print "Second". In case of a draw print "Friendship".

## 说明/提示

In the first example, information on the success of the first participant comes in $ 7 $ milliseconds, of the second participant — in $ 14 $ milliseconds. So, the first wins.

In the second example, information on the success of the first participant comes in $ 11 $ milliseconds, of the second participant — in $ 5 $ milliseconds. So, the second wins.

In the third example, information on the success of the first participant comes in $ 22 $ milliseconds, of the second participant — in $ 22 $ milliseconds. So, it is be a draw.

## 样例 #1

### 输入

```
5 1 2 1 2

```

### 输出

```
First

```

## 样例 #2

### 输入

```
3 3 1 1 1

```

### 输出

```
Second

```

## 样例 #3

### 输入

```
4 5 3 1 5

```

### 输出

```
Friendship

```

