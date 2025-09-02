# 题目信息

# Robot on the Board 1

## 题目描述

The robot is located on a checkered rectangular board of size $ n \times m $ ( $ n $ rows, $ m $ columns). The rows in the board are numbered from $ 1 $ to $ n $ from top to bottom, and the columns — from $ 1 $ to $ m $ from left to right.

The robot is able to move from the current cell to one of the four cells adjacent by side.

The sequence of commands $ s $ executed by the robot is given. Each command is denoted by one of the symbols 'L', 'R', 'D' or 'U', and triggers the movement to left, right, down or up, respectively.

The robot can start its movement in any cell. The robot executes the commands starting from the first one, strictly in the order in which they are listed in $ s $ . If the robot moves beyond the edge of the board, it falls and breaks. A command that causes the robot to break is not considered successfully executed.

The robot's task is to execute as many commands as possible without falling off the board. For example, on board $ 3 \times 3 $ , if the robot starts a sequence of actions $ s= $ "RRDLUU" ("right", "right", "down", "left", "up", "up") from the central cell, the robot will perform one command, then the next command will force him to cross the edge. If the robot starts moving from the cell $ (2, 1) $ (second row, first column) then all commands will be executed successfully and the robot will stop at the cell $ (1, 2) $ (first row, second column).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1607E/e9041329204b86a5b243e3524c9fedaa23a2383e.png)The robot starts from cell $ (2, 1) $ (second row, first column). It moves right, right, down, left, up, and up. In this case it ends in the cell $ (1, 2) $ (first row, second column).Determine the cell from which the robot should start its movement in order to execute as many commands as possible.

## 样例 #1

### 输入

```
4
1 1
L
1 2
L
3 3
RRDLUU
4 3
LUURRDDLLLUU```

### 输出

```
1 1
1 2
2 1
3 2```

# AI分析结果

### 题目内容（中文重写）
# 棋盘上的机器人 1

## 题目描述
机器人位于一个大小为 $n \times m$（$n$ 行，$m$ 列）的方格矩形棋盘上。棋盘的行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $m$。

机器人能够从当前单元格移动到相邻的四个单元格之一。

给出了机器人执行的命令序列 $s$。每个命令由符号 'L'、'R'、'D' 或 'U' 之一表示，分别触发向左、右、下或上的移动。

机器人可以从任何单元格开始移动。机器人从第一个命令开始执行命令，严格按照 $s$ 中列出的顺序执行。如果机器人移出棋盘边缘，它就会掉落并损坏。导致机器人损坏的命令不被视为成功执行。

机器人的任务是在不掉出棋盘的情况下尽可能多地执行命令。例如，在 $3 \times 3$ 的棋盘上，如果机器人从中心单元格开始执行动作序列 $s =$ "RRDLUU"（“右”、“右”、“下”、“左”、“上”、“上”），机器人将执行一个命令，然后下一个命令将迫使它越过边缘。如果机器人从单元格 $(2, 1)$（第二行，第一列）开始移动，那么所有命令都将成功执行，机器人将停在单元格 $(1, 2)$（第一行，第二列）。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1607E/e9041329204b86a5b243e3524c9fedaa23a2383e.png)
机器人从单元格 $(2, 1)$（第二行，第一列）开始。它向右、向右、向下、向左、向上和向上移动。在这种情况下，它最终停在单元格 $(1, 2)$（第一行，第二列）。
确定机器人应该从哪个单元格开始移动，以便在不掉出棋盘的情况下尽可能多地执行命令。

## 样例 #1

### 输入
```
4
1 1
L
1 2
L
3 3
RRDLUU
4 3
LUURRDDLLLUU
```

### 输出
```
1 1
1 2
2 1
3 2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟机器人的移动过程，通过不同的方法来判断机器人是否会越界，从而找到能执行最多命令的起始位置。

- **思路对比**：部分题解从初始点 $(1, 1)$ 开始模拟，遇到越界情况尝试调整起始点；部分题解通过记录机器人在各个方向的最大偏移量，根据偏移量判断是否越界；还有题解采用三分法分别对行和列进行求解。
- **算法要点**：大多数题解都需要记录机器人的当前位置、最大偏移量等信息，在模拟过程中不断更新这些信息，根据越界条件进行判断和处理。
- **解决难点**：主要难点在于如何准确判断机器人是否会越界，以及在越界时如何调整起始点或确定最终的起始位置。

### 所选题解
- **2huk（4星）**
    - **关键亮点**：思路清晰，代码简洁，通过维护当前走过的点中行列的最大值来判断整体移动是否会出界。
    - **核心代码**：
```cpp
int T, n, m, len;
char s[N];
int sx, sy, nowx, nowy, maxx, maxy;

PII Solve()
{
    n = read(), m = read();
    scanf("%s", s + 1);
    len = strlen(s + 1);
    sx = sy = nowx = nowy = maxx = maxy = 1;
    
    for (re int i = 1; i <= len; ++ i )
    {
        re char c = s[i];

        if (c == 'U')
        {
            if (nowx > 1) -- nowx;
            else if (maxx < n) ++ maxx, ++ sx;
            else return {sx, sy};
        }
        else if (c == 'D')
        {
            if (nowx < n) ++ nowx;
            else return {sx, sy};
        }
        else if (c == 'L')
        {
            if (nowy > 1) -- nowy;
            else if (maxy < m) ++ maxy, ++ sy;
            else return {sx, sy};
        }
        else
        {
            if (nowy < m) ++ nowy;
            else return {sx, sy};
        }

        maxx = max(maxx, nowx);
        maxy = max(maxy, nowy);
    }
    
    return {sx, sy};
}
```
核心实现思想：从 $(1, 1)$ 开始模拟机器人的移动，根据不同的命令更新当前位置，若遇到越界情况，尝试调整起始点，若无法调整则返回当前起始点。

- **Jur_Cai（4星）**
    - **关键亮点**：利用三分法分别对行和列进行求解，思路独特，将 $\sf{U,D}$ 和 $\sf{L,R}$ 操作分开处理，降低了问题的复杂度。
    - **核心代码**：
```cpp
inline int fud(int pos) {
    int res=0;
    for(int i=1; i<=len; i++) {
        if(op[i]=='U') {
            if(pos>1) pos--,res++;
        } else if(op[i]=='D') {
            if(pos<n) pos++,res++;
        }
    }
    return res;
}
inline int flr(int pos) {
    int res=0;
    for(int i=1; i<=len; i++) {
        if(op[i]=='L') {
            if(pos>1) pos--,res++;
        } else if(op[i]=='R') {
            if(pos<m) pos++,res++;
        }
    }
    return res;
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int l,r,ans;
        scanf("%d%d",&n,&m);
        scanf("%s",op+1),len=strlen(op+1);
        l=1,r=n,ans=1;
        while(l<=r) {
            int mid=(l+r)>>1;
            if(l==r) {
                ans=l;
                break;
            }
            if(l+1==r) {
                if(fud(l)>fud(r)) ans=l;
                else ans=r;
                break;
            }
            if(fud(mid-1)>fud(mid+1)) ans=mid-1,r=mid;
            else ans=mid+1,l=mid;
        }
        cout<<ans<<" ";
        l=1,r=m,ans=1;
        while(l<=r) {
            int mid=(l+r)>>1;
            if(l==r) {
                ans=l;
                break;
            }
            if(l+1==r) {
                if(flr(l)>flr(r)) ans=l;
                else ans=r;
                break;
            }
            if(flr(mid-1)>flr(mid+1)) ans=mid-1,r=mid;
            else ans=mid+1,l=mid;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```
核心实现思想：定义两个函数分别计算在某一行或某一列开始时能执行的命令数，利用三分法找到能执行命令数最多的行和列。

- **让风忽悠你（4星）**
    - **关键亮点**：思路简洁明了，通过记录向下和向右移动距离的最大值，判断改变起点位置是否合理，避免了复杂的计算。
    - **核心代码**：
```cpp
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        sx=sy=1; // 假设初始起点为(1,1) 
        maxx=maxy=x=y=0;
        scanf(" %s",s+1);
        int len=strlen(s+1);
        for(int i=1;i<=len;i++){
            // 左右移动 
            if(s[i]=='R'){
                if(sx+x==m) break; // 判断越界
                x++;
            }
            else if(s[i]=='L'){
                if(sx+maxx>=m && sx+x==1) break; // 判断此时是否碰到边界以及改变起点位置是否合理 
                if(x<=0 && sx+x==1) sx++; // 判断是否需要改变起点 
                x--;
            } 
            // 上下移动同理 
            else if(s[i]=='D'){
                if(sy+y==n) break;
                y++;
            }
            else if(s[i]=='U'){
                if(sy+maxy>=n && sy+y==1) break;
                if(y<=0 && sy+y==1) sy++;
                y--;
            }
            maxx=max(maxx,x);
            maxy=max(maxy,y);
            // 找出向右向下移动距离的最大值 
        }
        printf("%d %d\n",sy,sx);
    }
    return 0;
}
```
核心实现思想：从 $(1, 1)$ 开始模拟，根据不同的命令更新当前位置，若遇到越界情况，判断改变起点位置是否合理，若不合理则停止模拟，最后输出起点位置。

### 最优关键思路或技巧
- 大多数题解都采用从 $(1, 1)$ 开始模拟的方法，这种方法简单直观，容易实现。
- 通过记录机器人在各个方向的最大偏移量，可以方便地判断机器人是否会越界。
- 部分题解采用三分法，将 $\sf{U,D}$ 和 $\sf{L,R}$ 操作分开处理，降低了问题的复杂度。

### 拓展思路
同类型题或类似算法套路：
- 可以考虑增加更多的移动规则，如斜向移动、跳跃等，增加问题的复杂度。
- 可以将棋盘改为不规则形状，需要重新考虑越界判断的方法。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：考察组合数学和搜索算法。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：考察广度优先搜索 BFS 算法。
- [P1420 最长连号](https://www.luogu.com.cn/problem/P1420)：考察模拟和简单的计数算法。

### 个人心得摘录与总结
- **Jur_Cai**：提到题解区都是 $O(n)$ 的，自己 vp 的时候只想到了三分的做法，且三分学得比较逊，写得有些奇怪。总结：不同的人可能会想到不同的解题方法，即使方法不是最优的，也可以尝试实现，同时要不断学习和提高自己的算法水平。

---
处理用时：92.24秒