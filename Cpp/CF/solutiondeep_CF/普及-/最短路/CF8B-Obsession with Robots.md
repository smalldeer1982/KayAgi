# 题目信息

# Obsession with Robots

## 题目描述

The whole world got obsessed with robots,and to keep pace with the progress, great Berland's programmer Draude decided to build his own robot. He was working hard at the robot. He taught it to walk the shortest path from one point to another, to record all its movements, but like in many Draude's programs, there was a bug — the robot didn't always walk the shortest path. Fortunately, the robot recorded its own movements correctly. Now Draude wants to find out when his robot functions wrong. Heh, if Draude only remembered the map of the field, where he tested the robot, he would easily say if the robot walked in the right direction or not. But the field map was lost never to be found, that's why he asks you to find out if there exist at least one map, where the path recorded by the robot is the shortest.

The map is an infinite checkered field, where each square is either empty, or contains an obstruction. It is also known that the robot never tries to run into the obstruction. By the recorded robot's movements find out if there exist at least one such map, that it is possible to choose for the robot a starting square (the starting square should be empty) such that when the robot moves from this square its movements coincide with the recorded ones (the robot doesn't run into anything, moving along empty squares only), and the path from the starting square to the end one is the shortest.

In one movement the robot can move into the square (providing there are no obstrutions in this square) that has common sides with the square the robot is currently in.

## 样例 #1

### 输入

```
LLUUUR
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
RRUULLDD
```

### 输出

```
BUG
```

# AI分析结果

### 题目翻译
# 对机器人的痴迷

## 题目描述
整个世界都对机器人痴迷，为了跟上时代的步伐，伟大的伯兰程序员德劳德（Draude）决定制造自己的机器人。他一直在努力研究这个机器人。他教会了机器人从一个点走到另一个点的最短路径，并记录下所有的移动过程。然而，就像德劳德的许多程序一样，出现了一个漏洞——机器人并不总是走最短路径。幸运的是，机器人正确地记录了自己的移动过程。现在，德劳德想找出他的机器人何时出现故障。哎，如果德劳德还记得他测试机器人的场地地图，他就能轻易地判断出机器人走的方向是否正确。但场地地图已经丢失，再也找不到了，这就是为什么他要求你找出是否至少存在一张地图，使得机器人记录的路径是最短的。

地图是一个无限的方格区域，每个方格要么是空的，要么包含一个障碍物。众所周知，机器人从不试图碰到障碍物。通过记录机器人的运动，找出是否至少存在一个这样的地图，可以为机器人选择一个起始方格（起始方格应该是空的），这样当机器人从这个方格移动时，它的运动与记录的运动一致（机器人不会碰到任何东西，只沿着空的方格移动），从起点到终点的路径最短。

在一次移动中，机器人可以移动到与它当前所在方格有公共边的方格（前提是该方格中没有障碍物）。

## 样例 #1
### 输入
```
LLUUUR
```
### 输出
```
OK
```

## 样例 #2
### 输入
```
RRUULLDD
```
### 输出
```
BUG
```

### 综合分析与结论
这些题解的核心思路都是判断机器人走过的路径是否可能是最短路径，判断依据主要有两点：一是路径上不能有重复的格子；二是走到某个格子时，除了刚走过的格子外，其周围其他格子不能有已经走过的。

- **思路对比**：大部分题解都是模拟机器人的行走过程，在每一步判断是否满足上述两个条件。部分题解使用了方向数组简化坐标的移动，部分题解使用了函数封装判断逻辑。
- **算法要点**：利用二维数组标记已经走过的格子，根据机器人的移动指令更新坐标，在每一步检查是否满足最短路径的条件。
- **解决难点**：关键在于理解最短路径的判断条件，以及处理边界情况（如防止数组越界）。

### 所选题解
- **作者：封禁用户 (赞：14)，4星**
    - **关键亮点**：思路清晰，代码注释详细，对判断条件的解释通俗易懂。
    - **个人心得**：提醒注意 `check` 函数中变量命名，避免使用 `x1` 和 `y1` 导致编译错误。
- **作者：Loner_Knowledge (赞：8)，4星**
    - **关键亮点**：代码简洁，逻辑清晰，使用方向数组和函数封装，提高了代码的可读性和可维护性。
- **作者：cyrxdzj (赞：4)，4星**
    - **关键亮点**：思路明确，结合图形解释判断条件，易于理解。

### 重点代码
#### 作者：封禁用户
```cpp
inline bool check(int x_,int y_) {
    if (data[x_][y_]) return true;
    int tot=0;
    for (int i=0; i<4; i++) {
        int dx=fx[i]+x;
        int dy=fy[i]+y;
        if (data[dx][dy]) tot++;
    }
    return tot>1;
}
signed main() {
    x=y=101;
    cin>>s1;
    int len=s1.size();
    for (int i=0; i<len; i++) {
        data[x][y]=1;
        if (s1[i]=='L') {
            y--;
            if (check(x,y)) {
                printf("BUG\n");
                return 0;
            }
        }
        // 其他方向类似处理
    }
    printf("OK\n");
    return 0;
}
```
**核心实现思想**：`check` 函数用于判断当前格子是否满足最短路径的条件，`main` 函数模拟机器人的行走过程，在每一步调用 `check` 函数进行判断。

#### 作者：Loner_Knowledge
```cpp
bool Check(int x,int y) {
    if(mark[x][y])
        return 1;
    int cnt=0;
    for(int i,j,k=0;k<4;++k) {
        i=x+Const[0][k];
        j=y+Const[1][k];
        if(mark[i][j])
            ++cnt;
    }
    return cnt>1;
}
bool Solve(int x,int y) {
    mark[x][y]=1;
    for(int i=0,t;s[i];++i) {
        t=Use(s[i]);
        x+=Const[0][t];
        y+=Const[1][t];
        if(Check(x,y))
            return 0;
        mark[x][y]=1;
    }
    return 1;
}
int main() {
    scanf("%s",s);
    printf("%s",Solve(101,101)? "OK":"BUG");
    return 0;
}
```
**核心实现思想**：`Check` 函数判断当前格子是否满足最短路径条件，`Solve` 函数模拟机器人行走并调用 `Check` 函数进行判断。

#### 作者：cyrxdzj
```cpp
int main()
{
    scanf("%s",&input);
    graph[x][y]=1;
    for(int i=0;i<strlen(input);i++)
    {
        char move=input[i];
        if(move=='U') {
            x--;
        }
        // 其他方向类似处理
        if(graph[x][y]) {
            printf("BUG\n");
            return 0;
        }
        if(graph[x-1][y]+graph[x+1][y]+graph[x][y-1]+graph[x][y+1]>1) {
            printf("BUG\n");
            return 0;
        }
        graph[x][y]=1;
    }
    printf("OK\n");
    return 0;
}
```
**核心实现思想**：在 `main` 函数中模拟机器人行走，在每一步判断是否满足最短路径条件。

### 最优关键思路或技巧
- **使用二维数组标记**：用二维数组标记已经走过的格子，方便判断是否重复走过。
- **方向数组**：使用方向数组简化坐标的移动，提高代码的可读性和可维护性。
- **封装判断逻辑**：将判断是否满足最短路径条件的逻辑封装在函数中，使代码结构更清晰。

### 可拓展之处
同类型题或类似算法套路：
- 迷宫路径问题：给定迷宫地图和起点终点，判断是否存在最短路径，或找出最短路径的长度。
- 图的最短路径问题：在图中寻找两点之间的最短路径，可使用广度优先搜索（BFS）、Dijkstra 算法等。

### 推荐题目
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)

### 个人心得摘录与总结
- **封禁用户**：提醒注意 `check` 函数中变量命名，避免使用 `x1` 和 `y1` 导致编译错误，说明在编程时要注意变量命名规范，避免潜在的错误。
- **Aw顿顿**：一开始以为是空图，写的程序样例都没通过，后来看英文题面才发现是迷宫问题，要按照广搜的思路来，说明做题前要仔细理解题意，不能想当然。

---
处理用时：38.75秒