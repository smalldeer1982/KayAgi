# 题目信息

# Tic-tac-toe

## 题目描述

Certainly, everyone is familiar with tic-tac-toe game. The rules are very simple indeed. Two players take turns marking the cells in a $ 3×3 $ grid (one player always draws crosses, the other — noughts). The player who succeeds first in placing three of his marks in a horizontal, vertical or diagonal line wins, and the game is finished. The player who draws crosses goes first. If the grid is filled, but neither Xs, nor 0s form the required line, a draw is announced.

You are given a $ 3×3 $ grid, each grid cell is empty, or occupied by a cross or a nought. You have to find the player (first or second), whose turn is next, or print one of the verdicts below:

- illegal — if the given board layout can't appear during a valid game;
- the first player won — if in the given board layout the first player has just won;
- the second player won — if in the given board layout the second player has just won;
- draw — if the given board layout has just let to a draw.

## 样例 #1

### 输入

```
X0X
.0.
.X.
```

### 输出

```
second
```

# AI分析结果

### 题目中文重写
# 井字棋

## 题目描述
当然，每个人都熟悉井字棋游戏。实际上，规则非常简单。两名玩家轮流在一个 $3×3$ 的网格中标记格子（一名玩家总是画叉，另一名玩家总是画圈）。先成功将自己的三个标记连成水平、垂直或对角直线的玩家获胜，游戏结束。画叉的玩家先开始。如果网格被填满，但叉和圈都没有形成所需的直线，则宣布平局。

给定一个 $3×3$ 的网格，每个网格单元格要么为空，要么被叉或圈占据。你需要找出接下来轮到哪位玩家（先手或后手），或者输出以下判决之一：
- illegal —— 如果给定的棋盘布局在合法游戏中不可能出现；
- the first player won —— 如果在给定的棋盘布局中先手玩家刚刚获胜；
- the second player won —— 如果在给定的棋盘布局中后手玩家刚刚获胜；
- draw —— 如果给定的棋盘布局刚刚导致平局。

## 样例 #1
### 输入
```
X0X
.0.
.X.
```
### 输出
```
second
```

### 综合分析与结论
这些题解主要思路都是模拟井字棋游戏的判断过程。算法要点在于统计棋子数量、判断是否有玩家获胜以及判断棋盘布局是否合法。难点在于处理各种非法情况，如双方都赢、一方赢后另一方还继续下棋等。

### 所选题解
- **作者：Alex_Wei（5星）**
    - **关键亮点**：思路清晰，使用 `dfs` 判断三个棋子是否连成一线，代码结构完整，对各种情况的特判详细。
    - **个人心得**：强调特判细节很重要，避免一些隐藏的错误情况。
    - **核心代码**：
```cpp
void dfs(int a,int b,int c,int d,int e,char t) {
    if(e==3) {
        if(t=='X') pf=1;
        else ps=1;
        return;
    }
    else if(a+c<4&&a+c>0&&b+d<4&&b+d>0&&p[a+c][b+d]==t)
        dfs(a,b,a+c,b+d,e+1,t);
}
```
核心实现思想：通过 `dfs` 从一个棋子开始，按照指定方向遍历，若连续三个棋子相同则标记相应玩家获胜。

- **作者：One_JuRuo（4星）**
    - **关键亮点**：代码简洁，对各种情况的分类讨论清晰明了，通过暴力统计棋子数量和获胜情况进行判断。
    - **核心代码**：
```cpp
for(int i=1;i<=3;++i)
    for(int j=1;j<=3;++j) m[i][j]=(ch[j]=='X')?1:(ch[j]=='0')?2:0,++num[m[i][j]];
for(int i=1;i<=3;++i) if(m[i][1]==m[i][2]&&m[i][2]==m[i][3]) ++win[m[i][1]];
for(int j=1;j<=3;++j) if(m[1][j]==m[2][j]&&m[2][j]==m[3][j]) ++win[m[1][j]];
if(m[1][1]==m[2][2]&&m[2][2]==m[3][3]) ++win[m[1][1]];
if(m[3][1]==m[2][2]&&m[2][2]==m[1][3]) ++win[m[3][1]];
```
核心实现思想：先统计每种棋子的数量，再分别统计每行、每列和两条对角线上相同棋子的数量，以此判断是否有玩家获胜。

- **作者：Loner_Knowledge（4星）**
    - **关键亮点**：将判断赢家和棋盘合法性的逻辑封装成函数，代码模块化程度高，提高了代码的可读性和可维护性。
    - **核心代码**：
```cpp
bool Check1(char c) {
    for(int i=0;i<3;++i) {
        if(str[0][i]==c&&str[1][i]==c&&str[2][i]==c) return 1;
        if(str[i][0]==c&&str[i][1]==c&&str[i][2]==c) return 1;
    }
    if(str[1][1]!=c) return 0;
    if(str[0][0]==c&&str[2][2]==c) return 1;
    if(str[0][2]==c&&str[2][0]==c) return 1;
    return 0;
}
bool Check2() {
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j) {
            if(str[i][j]=='X') ++fcnt;
            else if(str[i][j]=='0') ++scnt;
        }
    if(fcnt!=scnt+1&&fcnt!=scnt) return 0;
    if(Check1('X')&&fcnt==scnt) return 0;
    if(Check1('0')&&fcnt==scnt+1) return 0;
    return 1;
}
```
核心实现思想：`Check1` 函数用于检查指定玩家是否获胜，`Check2` 函数用于检查棋盘布局是否合法，通过统计棋子数量和调用 `Check1` 函数进行判断。

### 最优关键思路或技巧
- 使用函数封装逻辑，提高代码的模块化程度和可读性，如 `Loner_Knowledge` 的题解。
- 对各种非法情况进行详细特判，避免遗漏，如 `Alex_Wei` 的题解。
- 利用暴力统计棋子数量和获胜情况，简单直接，如 `One_JuRuo` 的题解。

### 可拓展之处
同类型题如五子棋、围棋等棋类游戏的局面判断，可采用类似的思路，先统计棋子数量，再判断是否有玩家获胜，同时要注意处理更多复杂的非法情况。

### 洛谷相似题目推荐
- P1518 [USACO2.4]两只塔姆沃斯牛 The Tamworth Two：模拟牛和农夫在网格中的移动，判断相遇情况，需要处理各种边界和特殊情况。
- P1036 选数：通过枚举和组合的方式选择数字，判断是否满足条件，类似于井字棋中判断各种可能的局面。
- P1427 小鱼的数字游戏：简单的模拟题，需要处理输入输出和数组的操作，与井字棋的模拟思路有一定相似性。

### 个人心得摘录与总结
- **Alex_Wei**：强调特判细节很重要，在处理复杂情况时，要考虑到各种可能的非法情况，避免遗漏。
- **CrTsIr400**：在判断输赢和非法情况时容易踩坑，需要仔细考虑各种情况，如双方都赢、一方赢后另一方还继续下棋等。
- **学霸壹号**：容易把题目中的字符看错，要仔细审题；同时，使用宏定义可以简化代码中的字符串输出。
- **gary2005**：本题坑较多，需要多次提交才能通过，要对各种特殊情况进行充分的判断。
- **灵光一闪**：容易把数字“0”看成字母“O”，导致错误，做题时要仔细看清题目中的字符。

---
处理用时：46.06秒