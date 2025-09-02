# 题目信息

# Ela and Crickets

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/f0f8b416d84260abf4a5738763b563a4a29739c9.png)Ela likes Chess a lot. During breaks, she usually challenges her co-worker in DTL to some chess games. She's not an expert at classic chess, but she's very interested in Chess variants, where she has to adapt to new rules and test her tactical mindset to win the game.The problem, which involves a non-standard chess pieces type that is described below, reads: given $ 3 $ white crickets on a $ n \cdot n $ board, arranged in an "L" shape next to each other, there are no other pieces on the board. Ela wants to know with a finite number of moves, can she put any white cricket on the square on row $ x $ , column $ y $ ?

An "L"-shape piece arrangement can only be one of the below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/514135a9cb3021fdd11c6f5877903e61238e21da.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/e135bddf869fc3c4e5900f14eaae8062e1263b64.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/b79b64cfe0ed70ae5dd5a6ed54ba57554fdeec32.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/07b44b1ac7a379c6fed131cb7e0805a4ed084742.png)For simplicity, we describe the rules for crickets on the board where only three white crickets are. It can move horizontally, vertically, or diagonally, but only to a square in some direction that is immediately after another cricket piece (so that it must jump over it). If the square immediately behind the piece is unoccupied, the cricket will occupy the square. Otherwise (when the square is occupied by another cricket, or does not exist), the cricket isn't allowed to make such a move.

See an example of valid crickets' moves on the pictures in the Note section.

## 说明/提示

Here's the solution for the first test case. The red square denotes where the crickets need to reach. Note that in chess horizontals are counted from bottom to top, as well as on this picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/5d188af801d8843cba510dd4aca2e2621bb3a163.png)

## 样例 #1

### 输入

```
6
8
7 2 8 2 7 1
5 1
8
2 2 1 2 2 1
5 5
8
2 2 1 2 2 1
6 6
8
1 1 1 2 2 1
5 5
8
2 2 1 2 2 1
8 8
8
8 8 8 7 7 8
4 8```

### 输出

```
YES
NO
YES
NO
YES
YES```

# AI分析结果

### 题目内容重写
# Ela 和 Crickets

## 题目描述

Ela 非常喜欢国际象棋。在休息时，她经常挑战她的同事 DTL 下棋。她不是经典国际象棋的专家，但她对国际象棋变体非常感兴趣，在这些变体中，她必须适应新规则并测试她的战术思维以赢得比赛。问题涉及一种非标准的棋子类型，描述如下：给定一个 $n \times n$ 的棋盘，棋盘上有三个排成“L”形的白色 crickets，棋盘上没有其他棋子。Ela 想知道，在有限的步数内，她是否可以将任何一个白色 cricket 移动到棋盘上的第 $x$ 行、第 $y$ 列的方格上？

“L”形棋子的排列只能是以下四种情况之一：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/514135a9cb3021fdd11c6f5877903e61238e21da.png)，
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/e135bddf869fc3c4e5900f14eaae8062e1263b64.png)，
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/b79b64cfe0ed70ae5dd5a6ed54ba57554fdeec32.png)，
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/07b44b1ac7a379c6fed131cb7e0805a4ed084742.png)

为了简化问题，我们描述棋盘上只有三个白色 crickets 时的移动规则。cricket 可以水平、垂直或斜向移动，但只能跳到某个方向上紧邻另一个棋子的方格上（即必须跳过它）。如果紧邻的方格未被占据，cricket 将占据该方格。否则（当方格被另一个 cricket 占据或不存在时），cricket 不允许进行这样的移动。

### 说明/提示

以下是第一个测试用例的解决方案。红色方格表示 crickets 需要到达的位置。请注意，在国际象棋中，行是从下往上计数的，图片中也是如此。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/5d188af801d8843cba510dd4aca2e2621bb3a163.png)

### 样例 #1

#### 输入

```
6
8
7 2 8 2 7 1
5 1
8
2 2 1 2 2 1
5 5
8
2 2 1 2 2 1
6 6
8
1 1 1 2 2 1
5 5
8
2 2 1 2 2 1
8 8
8
8 8 8 7 7 8
4 8```

#### 输出

```
YES
NO
YES
NO
YES
YES```

### 算法分类
数学、模拟

### 题解分析与结论

#### 题解1：Binary_Lee
- **星级**：4.5
- **关键亮点**：通过分类讨论和奇偶性分析，得出了目标点是否可达的结论，并处理了特殊情况（如棋盘角落）。
- **核心代码**：
  ```cpp
  bool check(){
      bool _1=0,_2=0;
      if((x[2]==1||x[2]==n)&&tx!=x[2]) _1=1;
      if((y[2]==1||y[2]==n)&&ty!=y[2]) _2=1;
      if(_1&&_2) return 0;
      if(((x[2]+tx)&1)&&((y[2]+ty)&1)) return 0;
      return 1;
  }
  ```
- **个人心得**：通过模拟跳跃过程，发现目标点的奇偶性必须与折点的奇偶性相同，否则无法到达。

#### 题解2：Withershine
- **星级**：4
- **关键亮点**：通过将“L”形补成一个 $2 \times 2$ 的正方形，发现了不可达点的规律，并利用数学公式进行了判断。
- **核心代码**：
  ```cpp
  ll mid_r = p1.r + p2.r + p3.r - 2 * max(p1.r , max(p2.r , p3.r));
  ll mid_c = p1.c + p2.c + p3.c - 2 * max(p1.c , max(p2.c , p3.c));
  if((mid_r + target.r) % 2 == 0 && (mid_c + target.c) % 2 == 0)
  {
      printf("NO\n");
      continue;
  }
  else
  {
      printf("YES\n");
      continue;
  }
  ```
- **个人心得**：通过观察“L”形的结构，发现了不可达点的数学规律，简化了判断过程。

### 最优关键思路
1. **奇偶性分析**：通过分析目标点与折点的奇偶性，可以快速判断是否可达。
2. **特殊情况处理**：当“L”形位于棋盘角落时，只能到达两条边上的点，需进行特判。
3. **数学公式推导**：通过数学公式推导出不可达点的位置，简化了判断逻辑。

### 可拓展之处
- 类似的问题可以扩展到其他棋类游戏中的棋子移动规则，尤其是涉及跳跃和限制移动的规则。
- 可以通过类似的奇偶性分析和数学推导，解决其他棋盘上的可达性问题。

### 推荐题目
1. [P1737C - Ela and Crickets](https://www.luogu.com.cn/problem/CF1737C)
2. [P1736 - Chessboard](https://www.luogu.com.cn/problem/CF1736)
3. [P1735 - Chessboard](https://www.luogu.com.cn/problem/CF1735)

---
处理用时：40.36秒