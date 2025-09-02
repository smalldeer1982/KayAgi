# 题目信息

# Tic-Tac-Toe

## 题目背景

两头熊在玩一个游戏。

这个游戏的棋盘是由9个大方格排成$3\*3$的形式，每个大方格中有9个小方格，也是排成$3\*3$的形式。一个熊执x棋，一个执o棋。第一步由执x棋的熊下，可以下在任意一个小方格中，然后从第二步开始，上一个熊把棋下在的小方格在它所属的$3\*3$小方格中的对应位置，这头熊需要下在3\*3的大方格的对应位置大方格中的9个小方格中的一个。比如上一头熊下到了(6,4)(6,4)位置,(6,4)(6,4)位属于中间的那个大方格，在中间那个大方格的9个小方格中属于左下位，下一步就必须下到9个大方格的左下位的那个大方格中的9个小方格中的一个(样例1)。但是如果这9个小方格已经都被下过棋子了，那么就可以从其他地方任选一个小格子下棋(样例2)。

给定一个棋盘，上面有当前已经下完的棋子，再给出最后一步的坐标，要求在棋盘上下一步可以下的位置上打出"!"(无引号)

## 题目描述

Two bears are playing tic-tac-toe via mail. It's boring for them to play usual tic-tac-toe game, so they are a playing modified version of this game. Here are its rules.

The game is played on the following field.

 ![](http://espresso.codeforces.com/9f2cb44894dfaba91b9e381419482b55cfe9ff63.png)Players are making moves by turns. At first move a player can put his chip in any cell of any small field. For following moves, there are some restrictions: if during last move the opposite player put his chip to cell with coordinates $ (x_{l},y_{l}) $ in some small field, the next move should be done in one of the cells of the small field with coordinates $ (x_{l},y_{l}) $ . For example, if in the first move a player puts his chip to lower left cell of central field, then the second player on his next move should put his chip into some cell of lower left field (pay attention to the first test case). If there are no free cells in the required field, the player can put his chip to any empty cell on any field.

You are given current state of the game and coordinates of cell in which the last move was done. You should find all cells in which the current player can put his chip.

A hare works as a postman in the forest, he likes to foul bears. Sometimes he changes the game field a bit, so the current state of the game could be unreachable. However, after his changes the cell where the last move was done is not empty. You don't need to find if the state is unreachable or not, just output possible next moves according to the rules.

## 说明/提示

In the first test case the first player made a move to lower left cell of central field, so the second player can put a chip only to cells of lower left field.

In the second test case the last move was done to upper left cell of lower central field, however all cells in upper left field are occupied, so the second player can put his chip to any empty cell.

In the third test case the last move was done to central cell of central field, so current player can put his chip to any cell of central field, which is already occupied, so he can move anywhere. Pay attention that this state of the game is unreachable.

## 样例 #1

### 输入

```
... ... ...
... ... ...
... ... ...

... ... ...
... ... ...
... x.. ...

... ... ...
... ... ...
... ... ...
6 4
```

### 输出

```
... ... ... 
... ... ... 
... ... ... 

... ... ... 
... ... ... 
... x.. ... 

!!! ... ... 
!!! ... ... 
!!! ... ... 

```

## 样例 #2

### 输入

```
xoo x.. x..
ooo ... ...
ooo ... ...

x.. x.. x..
... ... ...
... ... ...

x.. x.. x..
... ... ...
... ... ...
7 4
```

### 输出

```
xoo x!! x!! 
ooo !!! !!! 
ooo !!! !!! 

x!! x!! x!! 
!!! !!! !!! 
!!! !!! !!! 

x!! x!! x!! 
!!! !!! !!! 
!!! !!! !!! 

```

## 样例 #3

### 输入

```
o.. ... ...
... ... ...
... ... ...

... xxx ...
... xox ...
... ooo ...

... ... ...
... ... ...
... ... ...
5 5
```

### 输出

```
o!! !!! !!! 
!!! !!! !!! 
!!! !!! !!! 

!!! xxx !!! 
!!! xox !!! 
!!! ooo !!! 

!!! !!! !!! 
!!! !!! !!! 
!!! !!! !!! 

```

# AI分析结果



### 题目重写（中文）

**题目名称：井字棋**

**题目背景**  
两只熊在玩一种特殊的井字棋游戏。棋盘由9个3×3的大方格组成，每个大方格又分为9个3×3的小方格。X熊先手，O熊后手，每一步的落子位置受前一步位置约束：若上一步落子在某个大方格的某个小格，下一步必须在该小格对应的大方格位置（例如上一步在中间大方格的左下小格，下一步必须在左下大方格）。若目标大方格已满，则可任意落子。

**题目描述**  
给定当前棋盘状态和最后一步的坐标，找出所有下一步可落子的位置（标记为`!`）。

**输入输出格式**  
输入为9行，每行9个字符（表示小方格状态），最后两行为最后一步坐标。输出棋盘，用`!`标记合法位置。

**样例说明**  
样例1中最后一步位于中间大方格的左下小格，下一步只能标记左下大方格的所有空位。样例2中目标大方格已满，可全局标记。

---

### 算法分类  
**模拟**

---

### 题解分析与结论

#### 核心思路
1. **坐标转换**：将输入的全局坐标转换为对应的大方格位置（取模或整除计算）。
2. **区域检查**：判断目标大方格是否存在空位，若已满则全局标记，否则仅标记目标区域。
3. **输入输出处理**：正确解析棋盘的四维结构并按规则格式化输出。

#### 解决难点
- **坐标映射**：需将全局坐标映射到对应的大方格及其内部小格，需注意取模边界处理（如余0时设为3）。
- **输入格式解析**：四维数组的存储方式需与输入顺序一致（如大方格→小行→大方格列→小列）。
- **输出格式化**：每3个小格加空格，每3个大行加空行。

---

### 精选题解

#### 题解1：EdenSky（4星）
**关键亮点**  
- 使用四维数组清晰表示棋盘结构。
- 宏定义处理取模逻辑，代码简洁。
- 分情况处理局部和全局标记，逻辑清晰。

**核心代码**  
```cpp
#include<iostream>
#define g(a) (a)%3==0?3:(a)%3
using namespace std;
char c[4][4][4][4]; int x,y;
int main(){
  // 输入处理
  for(int x=1;x<=3;x++)
    for(int i=1;i<=3;i++)
      for(int y=1;y<=3;y++)
        for(int j=1;j<=3;j++)
          cin>>c[x][y][i][j];
  cin>>x>>y; x=g(x),y=g(y);
  
  // 检查目标大方格是否为空
  bool is_empty=true;
  for(int i=1;i<=3;i++)
    for(int j=1;j<=3;j++)
      if(c[x][y][i][j]=='.'){
        is_empty=false;
        c[x][y][i][j]='!';
      }
  
  // 输出处理
  if(is_empty) // 全局标记
    for(int x=1;x<=3;x++)
      for(int i=1;i<=3;i++)
        for(int y=1;y<=3;y++)
          for(int j=1;j<=3;j++)
            if(c[x][y][i][j]=='.') cout<<'!';
            else cout<<c[x][y][i][j];
  else // 局部标记
    // ...（类似逻辑）
}
```

---

#### 题解2：codeLJH114514（4星）
**关键亮点**  
- 二维数组存储棋盘，直观处理全局坐标。
- 转换函数将四维结构转为二维输出，简化格式处理。

**核心代码**  
```cpp
void Print() {
    char show[128][128];
    // 将四维数组转为二维输出
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            for(int k=1;k<=3;k++)
                for(int l=1;l<=3;l++)
                    show[(i-1)*3+k][(j-1)*3+l] = c[i][j][k][l];
    // 格式化输出，处理空格和换行
    int cnt=0;
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            cout<<show[i][j];
            if(j%3==0) cout<<" ";
        }
        if(i%3==0) cout<<"\n";
    }
}
```

---

### 关键思路总结
- **坐标转换**：使用取模运算（注意余0特判）确定目标大方格。
- **区域检查**：遍历目标大方格，存在空位则局部标记，否则全局标记。
- **输入输出**：四维数组或二维数组均可，需确保与输入顺序一致，输出时注意格式细节。

---

### 拓展与相似题目
1. **洛谷P1312 棋盘覆盖**（模拟、坐标映射）
2. **洛谷P2670 扫雷游戏**（二维数组遍历与标记）
3. **洛谷P1036 选数**（递归与条件判断）

---
处理用时：150.57秒