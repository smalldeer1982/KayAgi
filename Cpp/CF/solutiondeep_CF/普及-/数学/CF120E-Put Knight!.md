# 题目信息

# Put Knight!

## 题目描述

Petya and Gena play a very interesting game "Put a Knight!" on a chessboard $ n×n $ in size. In this game they take turns to put chess pieces called "knights" on the board so that no two knights could threat each other. A knight located in square $ (r,c) $ can threat squares $ (r-1,c+2) $ , $ (r-1,c-2) $ , $ (r+1,c+2) $ , $ (r+1,c-2) $ , $ (r-2,c+1) $ , $ (r-2,c-1) $ , $ (r+2,c+1) $ and $ (r+2,c-1) $ (some of the squares may be located outside the chessboard). The player who can't put a new knight during his move loses. Determine which player wins considering that both players play optimally well and Petya starts.

## 样例 #1

### 输入

```
2
2
1
```

### 输出

```
1
0
```

# AI分析结果

【题目内容】
# 放置骑士！

## 题目描述

佩蒂亚和吉娜在一个大小为 $n×n$ 的棋盘上玩一个非常有趣的游戏“放置骑士！”。在这个游戏中，他们轮流将称为“骑士”的棋子放在棋盘上，使得没有两个骑士可以互相威胁。位于方格 $ (r,c) $ 的骑士可以威胁方格 $ (r-1,c+2) $ , $ (r-1,c-2) $ , $ (r+1,c+2) $ , $ (r+1,c-2) $ , $ (r-2,c+1) $ , $ (r-2,c-1) $ , $ (r+2,c+1) $ 和 $ (r+2,c-1) $（有些方格可能位于棋盘外）。无法放置新骑士的玩家输掉游戏。考虑到双方都玩得非常好且佩蒂亚先手，请确定哪位玩家会获胜。

## 样例 #1

### 输入

```
2
2
1
```

### 输出

```
1
0
```

【题解分析与结论】

各题解的思路基本一致，核心思想是利用棋盘的对称性来判断胜负。当 $n$ 为奇数时，先手可以通过占据中心点获得优势，最终获胜；当 $n$ 为偶数时，后手可以通过对称策略反制先手，最终获胜。所有题解都强调了使用文件读写的重要性，否则会导致得分错误。

【评分较高的题解】

1. **作者：RainFestival (5星)**
   - **关键亮点**：简洁明了地提出了核心结论，代码简洁且高效。
   - **代码核心**：
     ```cpp
     printf("%d\n",!(n%2));
     ```
   - **个人心得**：通过猜测结论并验证，发现结论正确，体现了博弈论中的对称性思维。

2. **作者：Marshall001 (4星)**
   - **关键亮点**：详细解释了对称下法的思路，强调了文件读写的必要性。
   - **代码核心**：
     ```cpp
     if(n%2==0) cout<<"1"; else cout<<"0";
     ```
   - **个人心得**：强调了文件读写的重要性，提醒了其他玩家可能忽略的细节。

3. **作者：云岁月书 (4星)**
   - **关键亮点**：通过打表法快速得出结论，并进一步解释了博弈论中的对称性策略。
   - **代码核心**：
     ```cpp
     if(n&1) puts("0"); else puts("1");
     ```
   - **个人心得**：通过打表法快速验证结论，体现了快速解题的技巧。

【最优关键思路或技巧】

- **对称性策略**：利用棋盘的对称性，先手或后手通过占据中心点或对称位置来控制棋盘，最终决定胜负。
- **文件读写**：题目要求必须使用文件读写，否则会导致得分错误，这是解题时需要注意的细节。

【可拓展之处】

- **类似题目**：可以扩展到其他棋盘类博弈问题，如皇后、车等棋子的放置问题，利用对称性或中心点策略来判断胜负。
- **博弈论应用**：可以进一步学习博弈论中的其他策略，如Nim游戏、Grundy数等，应用于更复杂的博弈问题。

【推荐题目】

1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

【个人心得总结】

- **调试经历**：多位作者强调了文件读写的重要性，提醒了其他玩家可能忽略的细节。
- **顿悟感想**：通过对称性策略快速得出结论，体现了博弈论中的对称性思维。

---
处理用时：33.94秒