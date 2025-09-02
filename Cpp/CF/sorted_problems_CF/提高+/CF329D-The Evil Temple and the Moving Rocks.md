---
title: "The Evil Temple and the Moving Rocks"
layout: "post"
diff: 提高+/省选-
pid: CF329D
tag: []
---

# The Evil Temple and the Moving Rocks

## 题目描述

Important: All possible tests are in the pretest, so you shouldn't hack on this problem. So, if you passed pretests, you will also pass the system test.

You are an adventurer currently journeying inside an evil temple. After defeating a couple of weak monsters, you arrived at a square room consisting of tiles forming an $ n×n $ grid, surrounded entirely by walls. At the end of the room lies a door locked with evil magical forces. The following inscriptions are written on the door:

 The sound of clashing rocks will awaken the door!Being a very senior adventurer, you immediately realize what this means. In the room next door lies an infinite number of magical rocks. There are four types of rocks:

- '^': this rock moves upwards;
- '<': this rock moves leftwards;
- '>': this rock moves rightwards;
- 'v': this rock moves downwards.

To open the door, you first need to place the rocks on some of the tiles (one tile can be occupied by at most one rock). Then, you select a single rock that you have placed and activate it. The activated rock will then move in its direction until it hits another rock or hits the walls of the room (the rock will not move if something already blocks it in its chosen direction). The rock then deactivates. If it hits the walls, or if there have been already $ 10^{7} $ events of rock becoming activated, the movements end. Otherwise, the rock that was hit becomes activated and this procedure is repeated.

If a rock moves at least one cell before hitting either the wall or another rock, the hit produces a sound. The door will open once the number of produced sounds is at least $ x $ . It is okay for the rocks to continue moving after producing $ x $ sounds.

The following picture illustrates the four possible scenarios of moving rocks.

- Moves at least one cell, then hits another rock. A sound is produced, the hit rock becomes activated. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/e59337ab587cdbd312be54b98490f9dd41771d7b.png)
- Moves at least one cell, then hits the wall (i.e., the side of the room). A sound is produced, the movements end. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/c851677c9f0333311db78372cd0f7a39ffa6d87e.png)
- Does not move because a rock is already standing in the path. The blocking rock becomes activated, but no sounds are produced. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/c66c40007af71e8e53cf79ddc8cdd98e93f6d4dd.png)
- Does not move because the wall is in the way. No sounds are produced and the movements end. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/cc4822df065eca79c7f861576c809682dbd03809.png)

Assume there's an infinite number of rocks of each type in the neighboring room. You know what to do: place the rocks and open the door!

## 输入格式

The first line will consists of two integers $ n $ and $ x $ , denoting the size of the room and the number of sounds required to open the door. There will be exactly three test cases for this problem:

- $ n=5,x=5 $ ;
- $ n=3,x=2 $ ;
- $ n=100,x=10^{5} $ .

All of these testcases are in pretest.

## 输出格式

Output $ n $ lines. Each line consists of $ n $ characters — the $ j $ -th character of the $ i $ -th line represents the content of the tile at the $ i $ -th row and the $ j $ -th column, and should be one of these:

- '^', '<', '>', or 'v': a rock as described in the problem statement.
- '.': an empty tile.

Then, output two integers $ r $ and $ c $ ( $ 1<=r,c<=n $ ) on the next line — this means that the rock you activate first is located at the $ r $ -th row from above and $ c $ -th column from the left. There must be a rock in this cell.

If there are multiple solutions, you may output any of them.

## 说明/提示

Here's a simulation of the first example, accompanied with the number of sounds produced so far.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/993406596a8a9d2174b87998a59e0de263168fa6.png) 0 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/b35282721e4af0a10d08ab1a78c0f07e1070b1ab.png) 1 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/ab195786b1f075b2dea28b2ce43b3c8a652b5402.png) 2 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/ca56c629d5cdddddcb6d12b51e02f1bbb53818d4.png) 3 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/de9249ae306be70d11ecaaf2ef1c74c2c830e965.png) 4 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/6ebca45731d036edba59b18dc824f53a3538bd23.png) still 4 sounds In the picture above, the activated rock switches between the '^' rock and the '<' rock. However, no sound is produced since the '^' rock didn't move even a single tile. So, still 4 sound.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/01e80bfbe73cce15e24d09cbfa6668f94e0a4d77.png) 5 sounds At this point, 5 sound are already produced, so this solution is already correct. However, for the sake of example, we will continue simulating what happens.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/0e90e3332608eaa6aff1cdf25b2e9cbf4f28970b.png) 6 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/23837a3b87bcf845e820a5cd4ea38533148b7e0a.png) 7 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/531092411052672c8c8a68c14289ed1d95d42f7e.png) still 7 sounds  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/964734e8afeb0b85aaaeee1f6f71f9f03ec4f5dc.png) 8 sounds And the movement stops. In total, it produces 8 sounds. Notice that the last move produced sound.

Here's a simulation of the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/228f1e59c6313428337f4ca8d5beee2d44d5dc0b.png) 0 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/f1858e1b5f4d00ad15cd32166d7ec7c3df4920e3.png) 1 sound  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/a96837bf11495f1f735decb970e12cdb49ee1c50.png) 2 sounds Now, the activated stone will switch continuously from one to another without producing a sound until it reaches the $ 10^{7} $ limit, after which the movement will cease.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329D/cb118e148b6ce5c1e286426601b934f8d8e94470.png)In total, it produced exactly 2 sounds, so the solution is correct.

## 样例 #1

### 输入

```
5 5

```

### 输出

```
>...v
v.<..
..^..
>....
..^.<
1 1

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
>;v
^<.
^.<
1 3

```

