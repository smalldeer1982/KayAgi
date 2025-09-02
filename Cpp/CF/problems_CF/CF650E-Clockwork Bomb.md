---
title: "Clockwork Bomb"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF650E
tag: []
---

# Clockwork Bomb

## 题目描述

My name is James diGriz, I'm the most clever robber and treasure hunter in the whole galaxy. There are books written about my adventures and songs about my operations, though you were able to catch me up in a pretty awkward moment.

I was able to hide from cameras, outsmart all the guards and pass numerous traps, but when I finally reached the treasure box and opened it, I have accidentally started the clockwork bomb! Luckily, I have met such kind of bombs before and I know that the clockwork mechanism can be stopped by connecting contacts with wires on the control panel of the bomb in a certain manner.

I see $ n $ contacts connected by $ n-1 $ wires. Contacts are numbered with integers from $ 1 $ to $ n $ . Bomb has a security mechanism that ensures the following condition: if there exist $ k>=2 $ contacts $ c_{1},c_{2},...,c_{k} $ forming a circuit, i. e. there exist $ k $ distinct wires between contacts $ c_{1} $ and $ c_{2} $ , $ c_{2} $ and $ c_{3} $ , $ ... $ , $ c_{k} $ and $ c_{1} $ , then the bomb immediately explodes and my story ends here. In particular, if two contacts are connected by more than one wire they form a circuit of length $ 2 $ . It is also prohibited to connect a contact with itself.

On the other hand, if I disconnect more than one wire (i. e. at some moment there will be no more than $ n-2 $ wires in the scheme) then the other security check fails and the bomb also explodes. So, the only thing I can do is to unplug some wire and plug it into a new place ensuring the fact that no circuits appear.

I know how I should put the wires in order to stop the clockwork. But my time is running out! Help me get out of this alive: find the sequence of operations each of which consists of unplugging some wire and putting it into another place so that the bomb is defused.

## 输入格式

The first line of the input contains $ n $ ( $ 2<=n<=500000 $ ), the number of contacts.

Each of the following $ n-1 $ lines contains two of integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n $ , $ x_{i}≠y_{i} $ ) denoting the contacts currently connected by the $ i $ -th wire.

The remaining $ n-1 $ lines contain the description of the sought scheme in the same format.

It is guaranteed that the starting and the ending schemes are correct (i. e. do not contain cicuits nor wires connecting contact with itself).

## 输出格式

The first line should contain $ k $ ( $ k>=0 $ ) — the minimum number of moves of unplugging and plugging back some wire required to defuse the bomb.

In each of the following $ k $ lines output four integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ , $ d_{i} $ meaning that on the $ i $ -th step it is neccesary to unplug the wire connecting the contacts $ a_{i} $ and $ b_{i} $ and plug it to the contacts $ c_{i} $ and $ d_{i} $ . Of course the wire connecting contacts $ a_{i} $ and $ b_{i} $ should be present in the scheme.

If there is no correct sequence transforming the existing scheme into the sought one, output -1.

## 说明/提示

Picture with the clarification for the sample tests:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF650E/30f5b033e4475bbc88fc85d3b241085ea07d2b6f.png)

## 样例 #1

### 输入

```
3
1 2
2 3
1 3
3 2

```

### 输出

```
1
1 2 1 3

```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
2 4
4 1
1 3

```

### 输出

```
3
1 2 1 3
4 3 4 1
2 3 2 4

```

