# 题目信息

# Chip Game

## 题目描述

Burenka and Tonya are playing an old Buryat game with a chip on a board of $ n \times m $ cells.

At the beginning of the game, the chip is located in the lower left corner of the board. In one move, the player can move the chip to the right or up by any odd number of cells (but you cannot move the chip both to the right and up in one move). The one who cannot make a move loses.

Burenka makes the first move, the players take turns. Burenka really wants to win the game, but she is too lazy to come up with a strategy, so you are invited to solve the difficult task of finding it. Name the winner of the game (it is believed that Burenka and Tonya are masters of playing with chips, so they always move in the optimal way).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1719A/a6c823a6eb354fdb9ffdf07a308c103419371a6a.png)Chip's starting cell is green, the only cell from which chip can't move is red. if the chip is in the yellow cell, then blue cells are all options to move the chip in one move.

## 说明/提示

In the first case, Burenka has no move, so Tonya wins.

In the second case, Burenka can move $ 3 $ cells to the right, after which Tony will not be able to make a move, which means that Burenka wins.

In the third case, Burenka can move $ 5 $ squares to the right. Then we can say that we have a game on a board of $ 1 \times 5 $ cells, and Tonya is the first player. In such game the second player wins, so in the original one Burenka will win.

## 样例 #1

### 输入

```
6
1 1
1 4
5 6
2 2
6 3
999999999 1000000000```

### 输出

```
Tonya
Burenka
Burenka
Tonya
Burenka
Burenka```

# AI分析结果

### 题目内容
# 芯片游戏

## 题目描述
Burenka和Tonya正在玩一个古老的布里亚特游戏，在一个$n \times m$单元格的棋盘上有一个芯片。

游戏开始时，芯片位于棋盘的左下角。在一步中，玩家可以将芯片向右或向上移动任意奇数个单元格（但不能在一步中同时向右和向上移动芯片）。无法移动的一方输掉游戏。

Burenka先走，玩家轮流行动。Burenka非常想赢得游戏，但她太懒了，不想想出策略，所以请你来解决这个难题，找出游戏的获胜者（假设Burenka和Tonya都是玩芯片游戏的高手，所以他们总是以最优方式移动）。

![芯片的起始单元格为绿色，唯一无法移动芯片的单元格为红色。如果芯片在黄色单元格中，那么蓝色单元格是在一步中移动芯片的所有可选位置。](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1719A/a6c823a6eb354fdb9ffdf07a308c103419371a6a.png)

## 说明/提示
在第一种情况下，Burenka没有可走的步，所以Tonya获胜。

在第二种情况下，Burenka可以向右移动3个单元格，之后Tony将无法移动，这意味着Burenka获胜。

在第三种情况下，Burenka可以向右移动5个方格。然后我们可以说，我们在一个$1 \times 5$单元格的棋盘上进行游戏，而Tonya是第一个玩家。在这样的游戏中，第二个玩家获胜，所以在原来的游戏中Burenka将获胜。

## 样例 #1
### 输入
```
6
1 1
1 4
5 6
2 2
6 3
999999999 1000000000
```
### 输出
```
Tonya
Burenka
Burenka
Tonya
Burenka
Burenka
```
### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是基于奇偶性来判断游戏的获胜者。难点在于如何将二维棋盘的移动问题转化为简单的奇偶性判断。
- **思路方面**：多数题解考虑到每次移动奇数格，一轮（先手后手各走一步）下来横纵坐标增加值之和为偶数。从起点$(1,1)$出发，根据终点坐标$(n,m)$的奇偶性组合来判断胜负。部分题解通过降维，将二维棋盘转化为一维线段来思考，本质也是利用奇偶性。
- **算法要点**：关键在于判断$n$和$m$的奇偶性组合，或者$n + m$（或$n + m - 2$等类似与总移动距离相关的式子）的奇偶性，以此确定先手或后手谁能获胜。
- **解决难点**：把复杂的二维移动策略问题简化为奇偶性判断，通过分析每轮移动的奇偶特性以及起点终点坐标关系来突破难点。

### 所选的题解
- **作者：D2T1 (5星)**
  - **关键亮点**：思路简洁清晰，直接指出每轮横纵坐标增加值为偶数，根据起点坐标和$n,m$奇偶关系判断胜负，代码简洁高效。
  ```cpp
  #define multiple_test_cases
 
  int n, m;
 
  void solve(){
      n = rdi;
      m = rdi;
      if((n - m) & 1){
          puts("Burenka");
      } else {
          puts("Tonya");
      }
  }
  ```
  核心实现思想：通过判断$n - m$的奇偶性（即$n$和$m$奇偶性是否不同）来确定获胜者，若不同则先手Burenka胜，相同则后手Tonya胜。
- **作者：zajasi (4星)**
  - **关键亮点**：利用曼哈顿距离算出总步数，根据总步数奇偶性判断胜负，思路直接，代码易读。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define int long long
  int t;
  int a,b;
  main(){
      ios::sync_with_stdio(false);
      cin.tie(0);
      cout.tie(0);
      cin>>t;
      while(t--){
          cin>>a>>b;
          int s=abs(a - 1)+abs(b - 1);
          if(s&1){
              cout<<"Burenka\n";
          }
          else{
              cout<<"Tonya\n";
          }
      }
      return 0;
  }
  ```
  核心实现思想：计算从$(1,1)$到$(n,m)$的曼哈顿距离作为总步数$s$，若$s$为奇数则先手Burenka胜，为偶数则后手Tonya胜。
- **作者：Epi4any (4星)**
  - **关键亮点**：采用棋盘染色的方法，根据起点和终点颜色是否相同判断胜负，角度新颖。
  ```cpp
  #include <iostream>
  #include <cstdio>
  using namespace std;

  inline int read() {
      int x = 0, f = 1;
      char ch = getchar();
      while (ch < '0' || ch > '9') {
          if (ch == '-') f = -1;
          ch = getchar();
      }
      while (ch >= '0' && ch <= '9') {
          x = (x << 1) + (x << 3) + (ch ^ 48);
          ch = getchar();
      }
      return x * f;
  }

  int n, m, t;

  int main() {
      t = read();
      while (t--) {
          n = read(), m = read();
          if ((n & 1) && (m & 1) ||!(n & 1) &&!(m & 1)) cout << "Tonya" << endl;
          else cout << "Burenka" << endl;
      }
      return 0;
  }
  ```
  核心实现思想：对棋盘进行染色，发现每次移动会进入不同颜色格子，若起点和终点颜色相同（即$n$和$m$同奇或同偶）则后手Tonya胜，不同则先手Burenka胜。

### 最优关键思路或技巧
将二维棋盘的移动问题转化为奇偶性判断问题，无论是通过分析每轮移动的奇偶特性、计算曼哈顿距离，还是棋盘染色，都是利用奇偶性这一关键性质来简化问题，从而快速判断出游戏的获胜者。

### 拓展思路
此类题目属于博弈论中的简单奇偶性博弈问题。类似套路是将复杂的游戏规则转化为简单的数学关系（如奇偶性、余数等）来判断胜负。例如在一些移动棋子的游戏中，通过分析每次移动的距离特性以及总距离的奇偶性来确定获胜策略。

### 相似知识点洛谷题目
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：涉及到根据奇偶性探索迷宫路径问题。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过分析不同购买方案下的数量关系，利用简单数学运算解决最优购买策略，与本题利用数学关系解决问题思路类似。
- [P5732 杨辉三角](https://www.luogu.com.cn/problem/P5732)：通过数学规律生成杨辉三角，考察对数学规律的观察与实现，与本题找奇偶性规律类似。

### 个人心得摘录总结
部分作者提到一开始思考方向复杂，如想套用Nim取石子问题等，之后才发现可以通过简单奇偶性判断解决，总结出遇到博弈类问题，要先深入分析题目规则特点，尝试从简单数学性质入手找规律，避免一开始就陷入复杂模型。 

---
处理用时：53.23秒