---
title: "The Psychic Poker Player"
layout: "post"
diff: 难度0
pid: UVA131
tag: []
---

# The Psychic Poker Player

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=67

[PDF](https://uva.onlinejudge.org/external/1/p131.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA131/25e03579971d2e95a25b307ae3eb67b9fbc54b08.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA131/5cbf0ff3d07f4b5bf7d11b66c704ab102f82f962.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA131/5f11845aac0c9934e3b8dcb86d0474cfa0a21154.png)

## 样例 #1

### 输入

```
TH JH QC QD QS QH KH AH 2S 6S
2H 2S 3H 3S 3C 2D 3D 6C 9C TH
2H 2S 3H 3S 3C 2D 9C 3D 6C TH
2H AD 5H AC 7H AH 6H 9H 4H 3C
AC 2D 9C 3S KD 5S 4D KS AS 4C
KS AH 2H 3C 4H KC 2C TC 2D AS
AH 2C 9S AD 3C QH KS JS JD KD
6C 9C 8C 2D 7C 2H TC 4C 9S AH
3D 5S 2H QD TD 6S KH 9H AD QH
```

### 输出

```
Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush
Hand: 2H 2S 3H 3S 3C Deck: 2D 3D 6C 9C TH Best hand: four-of-a-kind
Hand: 2H 2S 3H 3S 3C Deck: 2D 9C 3D 6C TH Best hand: full-house
Hand: 2H AD 5H AC 7H Deck: AH 6H 9H 4H 3C Best hand: flush
Hand: AC 2D 9C 3S KD Deck: 5S 4D KS AS 4C Best hand: straight
Hand: KS AH 2H 3C 4H Deck: KC 2C TC 2D AS Best hand: three-of-a-kind
Hand: AH 2C 9S AD 3C Deck: QH KS JS JD KD Best hand: two-pairs
Hand: 6C 9C 8C 2D 7C Deck: 2H TC 4C 9S AH Best hand: one-pair
Hand: 3D 5S 2H QD TD Deck: 6S KH 9H AD QH Best hand: highest-card
```

