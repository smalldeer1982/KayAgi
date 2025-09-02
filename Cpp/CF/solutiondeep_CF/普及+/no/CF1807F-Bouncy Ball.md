# 题目信息

# Bouncy Ball

## 题目描述

You are given a room that can be represented by a $ n \times m $ grid. There is a ball at position $ (i_1, j_1) $ (the intersection of row $ i_1 $ and column $ j_1 $ ), and it starts going diagonally in one of the four directions:

- The ball is going down and right, denoted by $ \texttt{DR} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i+1, j+1) $ .
- The ball is going down and left, denoted by $ \texttt{DL} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i+1, j-1) $ .
- The ball is going up and right, denoted by $ \texttt{UR} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i-1, j+1) $ .
- The ball is going up and left, denoted by $ \texttt{UL} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i-1, j-1) $ .

After each step, the ball maintains its direction unless it hits a wall (that is, the direction takes it out of the room's bounds in the next step). In this case, the ball's direction gets flipped along the axis of the wall; if the ball hits a corner, both directions get flipped. Any instance of this is called a bounce. The ball never stops moving.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1807F/b981cd1b02284413957fa53dbf389556ca82be95.png)In the above example, the ball starts at $ (1, 7) $ and goes $ \texttt{DL} $ until it reaches the bottom wall, then it bounces and continues in the direction $ \texttt{UL} $ . After reaching the left wall, the ball bounces and continues to go in the direction $ \texttt{UR} $ . When the ball reaches the upper wall, it bounces and continues in the direction $ \texttt{DR} $ . After reaching the bottom-right corner, it bounces once and continues in direction $ \texttt{UL} $ , and so on.

Your task is to find how many bounces the ball will go through until it reaches cell $ (i_2, j_2) $ in the room, or report that it never reaches cell $ (i_2, j_2) $ by printing $ -1 $ .

Note that the ball first goes in a cell and only after that bounces if it needs to.

## 样例 #1

### 输入

```
6
5 7 1 7 2 4 DL
5 7 1 7 3 2 DL
3 3 1 3 2 2 UR
2 4 2 1 2 2 DR
4 3 1 1 1 3 UL
6 4 1 2 3 4 DR```

### 输出

```
3
-1
1
-1
4
0```

# AI分析结果

### 题目内容重写
在一个 $n \times m$ 的网格房间内，有一个球位于位置 $(i_1, j_1)$，并开始沿对角线方向移动。移动方向有四种：
- **DR**：向下右移动，即从 $(i, j)$ 移动到 $(i+1, j+1)$。
- **DL**：向下左移动，即从 $(i, j)$ 移动到 $(i+1, j-1)$。
- **UR**：向上右移动，即从 $(i, j)$ 移动到 $(i-1, j+1)$。
- **UL**：向上左移动，即从 $(i, j)$ 移动到 $(i-1, j-1)$。

当球碰到墙壁时，方向会沿墙壁的轴线翻转；若碰到角落，则两个方向都会翻转。每次方向翻转称为一次反弹。球永远不会停止移动。

你的任务是计算球在到达目标位置 $(i_2, j_2)$ 之前会反弹多少次，或者报告球永远不会到达目标位置，输出 $-1$。

### 算法分类
模拟

### 题解分析与结论
Larryyu 的题解通过模拟球的移动过程来解决问题。其核心思路是：
1. **模拟移动**：根据初始方向，逐步模拟球的移动过程。
2. **反弹处理**：当球碰到墙壁或角落时，更新方向并记录反弹次数。
3. **终止条件**：如果球到达目标位置，输出反弹次数；如果移动步数超过 $4 \times n \times m$ 仍未到达目标位置，则输出 $-1$。

该题解的优点是思路清晰，代码实现简洁，且通过限制最大步数避免了无限循环的问题。

### 所选题解
#### 题解作者：Larryyu (赞：16)
- **星级**：4星
- **关键亮点**：通过模拟球的移动过程，结合反弹处理，简洁高效地解决了问题。代码可读性强，逻辑清晰。
- **个人心得**：无

### 核心代码片段
```cpp
void solve(){
    int n=read(),m=read(),sx=read(),sy=read(),ex=read(),ey=read();
    int dx,dy,x=sx,y=sy,cnt=0;
    string s;
    cin>>s;
    if(s[0]=='D') dx=1;
    else dx=-1;
    if(s[1]=='L') dy=-1;
    else dy=1;
    ll lim=n*m*4;
    while(lim--){
        if(x==ex&&y==ey){ //移到目标点
            cout<<cnt<<endl;
            return ;
        }
        bool is=0;
        if(dx==1&&x==n){ //碰到下侧墙壁
            dx=-1;
            is=1;
        }
        if(dx==-1&&x==1){ //碰到上侧墙壁
            dx=1;
            is=1;
        }
        if(dy==1&&y==m){ //碰到右侧墙壁
            dy=-1;
            is=1;
        }
        if(dy==-1&&y==1){ //碰到左侧墙壁
            dy=1;
            is=1;
        }
        if(is) cnt++; //有反弹
        x+=dx,y+=dy; //移动
    }
    cout<<-1<<endl;
}
```

### 关键思路与技巧
1. **模拟移动**：通过逐步模拟球的移动过程，确保每一步都符合物理规则。
2. **反弹处理**：当球碰到墙壁或角落时，更新方向并记录反弹次数。
3. **终止条件**：通过限制最大步数，避免无限循环，确保算法在合理时间内结束。

### 可拓展之处
类似的问题可以扩展到三维空间中的球体运动，或者考虑球的弹性系数、摩擦力等因素，增加问题的复杂度。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

---
处理用时：31.75秒