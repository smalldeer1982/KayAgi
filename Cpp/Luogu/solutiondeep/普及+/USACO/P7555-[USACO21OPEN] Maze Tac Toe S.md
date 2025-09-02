# 题目信息

# [USACO21OPEN] Maze Tac Toe S

## 题目描述

奶牛 Bessie 喜欢玩走迷宫。她同样喜欢玩井字棋（更准确地说，奶牛版的井字棋，马上会进行介绍）。Farmer John 找到了一种全新的方式，可以使她同时玩到这两种游戏！

首先，奶牛井字棋：与在 $3 \times 3$ 棋盘内放置 `X` 和 `O` 不同，奶牛当然是在 $3 \times 3$ 棋盘内放置 `M` 和 `O`。在一方的回合内，玩家可以选择将一个 `M` 或一个 `O` 放在任意一个空格内（这是另一个与标准井字棋的不同之处，标准的井字棋中一名玩家始终放 `X` 而另一名玩家始终放 `O`）。奶牛井字棋的胜利方是首位拼出 `MOO` 的玩家，可以是同行、同列或对角线。倒着拼出也是可以的，例如一名玩家在棋盘的一行内拼出 `OOM` 也可以获胜。如同标准井字棋一样，有可能最后没有玩家取得胜利。奶牛井字棋的一次行动通常用 3 个字符表示，`Mij` 或 `Oij`，其中 $i$ 和 $j$ 在范围 $1 \ldots 3$ 之间，表示放置 `M` 或 `O` 的行与列。

为了给 Bessie 增加一些挑战，Farmer John 设计了一个由 $N \times N$ 个方格组成的正方形迷宫（$3 \leq N \leq 25$）。某些方格，包括所有的边界方格，有巨大的草堆，使得 Bessie 不能移动到这些方格。Bessie 可以沿东南西北四个方向在迷宫内的所有其他方格内自由行动。某些方格内有一张纸，上面写有奶牛井字棋的一次行动。当 Bessie 在迷宫中移动时，任何时刻她停留在这样的方格上，她都必须于迷宫中移动之时在同时进行的奶牛井字棋游戏内做出对应的行动（除非奶牛井字棋中对应的方格已经被填上了，在这种情况下她不进行行动）。在奶牛井字棋游戏内没有与她对阵的玩家，但迷宫中的某些方格可能会不利于她最终拼出 `MOO`。

如果 Bessie 在获胜之时就会立刻停止奶牛井字棋，请求出她可以通过适当的方式在迷宫中移动而完成的不同的胜利状态棋盘数量。

## 说明/提示

#### 样例说明

在这个样例中，Bessie 最终可能达成 $8$ 种胜利的棋盘状态：

```plain
O.M
.O.
MOM

O..
.O.
.OM

O.M
.O.
.OM

O..
.O.
MOM

O..
...
OOM

..M
.O.
OOM

...
.O.
OOM

...
...
OOM
```

对其中一种情况进行说明：

```plain
O..
...
OOM
```

在这里，Bessie 可以先移动到 `O11` 方格，然后移动到下方并通过 `O32`、`M33` 和 `O31`。此时游戏结束，因为她获得了胜利（例如她不能再前往位于她当前所在的 `O31` 方格北面的 `M11` 方格）。

#### 说明

供题：Brian Dean

## 样例 #1

### 输入

```
7
#####################
###O11###...###M13###
###......O22......###
###...######M22######
###BBB###M31###M11###
###...O32...M33O31###
#####################```

### 输出

```
8```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过搜索（主要是深度优先搜索）来遍历迷宫中的路径，并利用状态压缩将井字棋的状态用三进制数表示，以记录不同的井字棋状态，避免重复搜索。在搜索过程中，判断当前状态是否胜利，若胜利则记录该状态。各题解的主要区别在于代码实现细节和部分优化处理。

### 所选题解
- **作者：tiger2005 (赞：8)  ★★★★**
  - **关键亮点**：思路清晰，代码结构合理，对状态的判断和处理逻辑明确，通过预处理所有状态的可行性提高效率。
- **作者：打程序的咸鱼 (赞：2)  ★★★★**
  - **关键亮点**：对状态压缩的原理和过程解释详细，代码实现简洁，使用 `set` 来存储胜利状态，方便去重。

### 重点代码及核心实现思想
#### tiger2005 的题解
```cpp
inline bool isWin(int k){
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++){
            mp[i][j]=k%3;
            if(mp[i][j]==0) mp[i][j]='.';
            else if(mp[i][j]==1) mp[i][j]='M';
            else mp[i][j]='O';
            k/=3;
        }
    string p="";
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++)
            p+=mp[i][j];
        if(p=="MOO" || p=="OOM") return true;
        p="";
    }
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++)
            p+=mp[j][i];
        if(p=="MOO" || p=="OOM") return true;
        p="";
    }
    for(int i=1;i<=3;i++)
        p+=mp[i][i];
    if(p=="MOO" || p=="OOM") return true;
    p="";
    for(int i=1;i<=3;i++)
        p+=mp[i][4-i];
    if(p=="MOO" || p=="OOM") return true;
    return false;
}
int Draw(int k,char q,int x,int y){
    x=3*x+y;
    int u=(k/pw[x])%3;
    if(u!=0) return k;
    return k+(q=='M'?1:2)*pw[x];
}
void dfs(int x,int y,int k){
    if(Maz[x][3*y+1]=='M' || Maz[x][3*y+1]=='O')
        k=Draw(k,Maz[x][3*y+1],Maz[x][3*y+2]-'1',Maz[x][3*y+3]-'1');
    if(dp[x][y][k]) return;
    dp[x][y][k]=true;
    if(isP[k]){
        ans+=!pd[k];
        pd[k]=true;
        return;
    }
    for(int i=0,xx,yy;i<4;i++){
        xx=x+fang[i][0],yy=y+fang[i][1];
        if(Maz[xx][3*yy+1]!='\0' && Maz[xx][3*yy+1]!='#')
            dfs(xx,yy,k);
    }
}
```
**核心实现思想**：`isWin` 函数将三进制状态转换为 `3*3` 的字符数组，然后检查行、列和对角线是否有 `MOO` 或 `OOM` 组合。`Draw` 函数用于更新井字棋状态。`dfs` 函数进行深度优先搜索，在每个位置更新状态，判断是否重复和是否胜利，然后向四个方向继续搜索。

#### 打程序的咸鱼的题解
```cpp
bool test_win(int b)
{
    int cells[3][3];
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++) {
            cells[i][j] = b%3;
            b /= 3;
        }
    for (int r=0; r<3; r++) {
        if (cells[r][0] == 1 && cells[r][1] == 2 && cells[r][2] == 2) return true;
        if (cells[r][0] == 2 && cells[r][1] == 2 && cells[r][2] == 1) return true;
    }
    for (int c=0; c<3; c++) {
        if (cells[0][c] == 1 && cells[1][c] == 2 && cells[2][c] == 2) return true;
        if (cells[0][c] == 2 && cells[1][c] == 2 && cells[2][c] == 1) return true;
    }
    if (cells[0][0] == 1 && cells[1][1] == 2 && cells[2][2] == 2) return true;
    if (cells[0][0] == 2 && cells[1][1] == 2 && cells[2][2] == 1) return true;
    if (cells[2][0] == 1 && cells[1][1] == 2 && cells[0][2] == 2) return true;
    if (cells[2][0] == 2 && cells[1][1] == 2 && cells[0][2] == 1) return true;
    return false;
}
void dfs(int i, int j, int b)
{
    if (beenthere[i][j][b]) return;
    beenthere[i][j][b] = true;
    if (board[i][j][0]=='M' || board[i][j][0]=='O') {
        int r = board[i][j][1]-'1', c = board[i][j][2]-'1', idx = r*3+c;
        int current_char = (b / pow3[idx]) % 3;
        if (current_char == 0) {
            int new_char = board[i][j][0]=='M' ? 1 : 2;
            b = (b % pow3[idx]) + new_char * pow3[idx] + (b - b % pow3[idx+1]);
            if (!beenthere[i][j][b] && test_win(b)) { answers.insert(b); return; }
            beenthere[i][j][b] = true;
        }
    }
    if (board[i-1][j][0] != '#') dfs(i-1,j,b);
    if (board[i+1][j][0] != '#') dfs(i+1,j,b);
    if (board[i][j-1][0] != '#') dfs(i,j-1,b);
    if (board[i][j+1][0] != '#') dfs(i,j+1,b);
}
```
**核心实现思想**：`test_win` 函数将三进制状态转换为 `3*3` 的数组，检查行、列和对角线是否满足胜利条件。`dfs` 函数进行深度优先搜索，在每个位置更新状态，判断是否重复和是否胜利，若胜利则将状态插入 `set` 中，然后向四个方向继续搜索。

### 最优关键思路或技巧
- **状态压缩**：使用三进制数表示井字棋的状态，将 $3 \times 3$ 的棋盘状态压缩为一个整数，方便存储和比较。
- **记忆化搜索**：使用数组记录已经搜索过的状态，避免重复搜索，提高效率。

### 可拓展之处
同类型题或类似算法套路：
- 涉及棋盘状态的搜索问题，如八皇后问题、数独问题等，可以使用状态压缩来表示棋盘状态。
- 迷宫搜索问题，如寻找最短路径、统计不同路径等，可以使用深度优先搜索或广度优先搜索。

### 推荐题目
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
- [P1784 数独](https://www.luogu.com.cn/problem/P1784)
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得
这些题解中没有明显的个人心得（调试/顿悟）内容。 

---
处理用时：52.90秒