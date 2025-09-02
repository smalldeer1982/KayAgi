---
title: "Om Nom and Dark Park"
layout: "post"
diff: 普及/提高-
pid: CF526B
tag: []
---

# Om Nom and Dark Park

## 题目描述

Om Nom is the main character of a game "Cut the Rope". He is a bright little monster who likes visiting friends living at the other side of the park. However the dark old parks can scare even somebody as fearless as Om Nom, so he asks you to help him.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/131af3f0d0c50854dd04093b7cc403fcf25a1e8b.png)The park consists of $ 2^{n+1}-1 $ squares connected by roads so that the scheme of the park is a full binary tree of depth $ n $ . More formally, the entrance to the park is located at the square $ 1 $ . The exits out of the park are located at squares $ 2^{n},2^{n}+1,...,2^{n+1}-1 $ and these exits lead straight to the Om Nom friends' houses. From each square $ i $ ( $ 2<=i<2^{n+1} $ ) there is a road to the square ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/1a134f5ff0a48756afece69eeb883c670c5ab534.png). Thus, it is possible to go from the park entrance to each of the exits by walking along exactly $ n $ roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/f5acd0d816020c5e5a5f00b96e0b0428cadec703.png) To light the path roads in the evening, the park keeper installed street lights along each road. The road that leads from square $ i $ to square ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/1a134f5ff0a48756afece69eeb883c670c5ab534.png) has $ a_{i} $ lights.Om Nom loves counting lights on the way to his friend. Om Nom is afraid of spiders who live in the park, so he doesn't like to walk along roads that are not enough lit. What he wants is that the way to any of his friends should have in total the same number of lights. That will make him feel safe.

He asked you to help him install additional lights. Determine what minimum number of lights it is needed to additionally place on the park roads so that a path from the entrance to any exit of the park contains the same number of street lights. You may add an arbitrary number of street lights to each of the roads.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10 $ ) — the number of roads on the path from the entrance to any exit.

The next line contains $ 2^{n+1}-2 $ numbers $ a_{2},a_{3},...\ a_{2^{n+1}-1} $ — the initial numbers of street lights on each road of the park. Here $ a_{i} $ is the number of street lights on the road between squares $ i $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/1a134f5ff0a48756afece69eeb883c670c5ab534.png). All numbers $ a_{i} $ are positive integers, not exceeding $ 100 $ .

## 输出格式

Print the minimum number of street lights that we should add to the roads of the park to make Om Nom feel safe.

## 说明/提示

Picture for the sample test. Green color denotes the additional street lights.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/a991902237b78dc527346d24d4ba436bdc2cc2af.png)

## 样例 #1

### 输入

```
2
1 2 3 4 5 6

```

### 输出

```
5

```

