# 题目信息

# 停止問題

## 题目描述

Defunge 程序由一个 $R$ 行 $C$ 列的字符数组组成。下面是一个 Defunge 程序的例子：

```plain
6>--v.
.^--_@
```

Defunge 程序从程序的左上角（即第一行第一列）开始执行。**它的执行方向一开始为"右"**，每次朝着执行方向走一步，**如果走出界了，要跳到另一边**。每走到一个格子上，就要执行这个格子上的命令。 Defunge 程序还有一个存储器，这个存储器只能存储 $[0,15]$ 的一个整数，**存储器一开始存储** $\bold{0}$。

在 Defunge 程序中，有且只有 $11+10=21$ 种命令，下面是它们各自的含义：

- `<`：把执行方向设置为"左"。
- `>`：把执行方向设置为"右"。
- `^`：把执行方向设置为"上"。
- `v`：把执行方向设置为"下"。
- `_`：如果存储器存储的数字是 $0$，就把执行方向设置为"右"，否则设置为"左"。
- `|`：如果存储器存储的数字是 $0$，就把执行方向设置为"下"，否则设置为"上"。
- `?`：把执行方向设置为"上下左右"中的**任意**一个（类似于 dfs 把四个方向全搜一遍）。
- `.`：什么也不做。
- `@`：停止程序。
- `0`-`9`：把存储器设置为这个字符表示的数值。
- `+`：让存储器的数值加 $1$。注意当存储器的数值为 $15$ 时要把它设为 $0$。
- `-`：让存储器的数值减 $1$。注意当存储器的数值为 $0$ 时要把它设为 $15$。

现在，给你一个 Defunge 程序，请判断这个程序是否能停止（即执行到命令`@`）。如果能，输出`YES`，否则输出`NO`。

## 说明/提示

$1\leq R,C\leq 20$，保证程序里只有上文提到的 $21$ 种命令。

# AI分析结果

### 题目内容重写（中文）

Defunge 程序由一个 $R$ 行 $C$ 列的字符数组组成。下面是一个 Defunge 程序的例子：

```plain
6>--v.
.^--_@
```

Defunge 程序从程序的左上角（即第一行第一列）开始执行。**它的执行方向一开始为"右"**，每次朝着执行方向走一步，**如果走出界了，要跳到另一边**。每走到一个格子上，就要执行这个格子上的命令。 Defunge 程序还有一个存储器，这个存储器只能存储 $[0,15]$ 的一个整数，**存储器一开始存储** $\bold{0}$。

在 Defunge 程序中，有且只有 $11+10=21$ 种命令，下面是它们各自的含义：

- `<`：把执行方向设置为"左"。
- `>`：把执行方向设置为"右"。
- `^`：把执行方向设置为"上"。
- `v`：把执行方向设置为"下"。
- `_`：如果存储器存储的数字是 $0$，就把执行方向设置为"右"，否则设置为"左"。
- `|`：如果存储器存储的数字是 $0$，就把执行方向设置为"下"，否则设置为"上"。
- `?`：把执行方向设置为"上下左右"中的**任意**一个（类似于 dfs 把四个方向全搜一遍）。
- `.`：什么也不做。
- `@`：停止程序。
- `0`-`9`：把存储器设置为这个字符表示的数值。
- `+`：让存储器的数值加 $1$。注意当存储器的数值为 $15$ 时要把它设为 $0$。
- `-`：让存储器的数值减 $1$。注意当存储器的数值为 $0$ 时要把它设为 $15$。

现在，给你一个 Defunge 程序，请判断这个程序是否能停止（即执行到命令`@`）。如果能，输出`YES`，否则输出`NO`。

### 题解综合分析与结论

本题的核心是模拟 Defunge 程序的执行过程，难点在于处理方向变化、存储器数值的变化以及边界条件。由于存在 `?` 命令，程序需要向四个方向进行搜索，因此使用深度优先搜索（DFS）是较为合适的选择。为了避免死循环，需要使用一个四维数组来记录每个状态（位置、方向、存储器值）是否已经被访问过。

### 所选高星题解

#### 题解1：作者：Jorisy (赞：7)  
**星级：4.5**  
**关键亮点：**  
1. 使用四维数组 `b[25][25][20][5]` 来记录状态，避免重复访问。
2. 使用 `switch` 语句处理不同的命令，代码结构清晰。
3. 通过 `exit(0)` 直接结束程序，简化了输出逻辑。

**个人心得：**  
作者提到在处理减1操作时，为了避免负数取模，先增加15再取模16，这一技巧值得借鉴。

**核心代码：**
```cpp
void dfs(int x,int y,int s,int fx)
{
    while(x<1) x+=r;
    while(r<x) x-=r;
    while(y<1) y+=c;
    while(c<y) y-=c;
    if(b[x][y][s][fx]) return;
    if(a[x][y]=='@')
    {
        cout<<"YES"<<endl;
        exit(0);
    }
    b[x][y][s][fx]=true;
    switch(a[x][y])
    {
        case '>': dfs(x+X[4],y+Y[4],s,4); break;
        case '<': dfs(x+X[3],y+Y[3],s,3); break;
        case '^': dfs(x+X[1],y+Y[1],s,1); break;
        case 'v': dfs(x+X[2],y+Y[2],s,2); break;
        case '_': if(s) dfs(x+X[3],y+Y[3],s,3); else dfs(x+X[4],y+Y[4],s,4); break;
        case '|': if(s) dfs(x+X[1],y+Y[1],s,1); else dfs(x+X[2],y+Y[2],s,2); break;
        case '?': for(int i=1;i<=4;i++) dfs(x+X[i],y+Y[i],s,i); break;
        case '.': dfs(x+X[fx],y+Y[fx],s,fx); break;
        case '+': s++; if(s>15) s=0; dfs(x+X[fx],y+Y[fx],s,fx); break;
        case '-': s--; if(s<0) s=15; dfs(x+X[fx],y+Y[fx],s,fx); break;
        default: s=a[x][y]-48; dfs(x+X[fx],y+Y[fx],s,fx); break;
    }
}
```

#### 题解2：作者：_caiji_ (赞：4)  
**星级：4**  
**关键亮点：**  
1. 使用 `while` 循环处理边界条件，避免负数取模问题。
2. 通过 `exit(0)` 直接结束程序，简化了输出逻辑。
3. 代码结构清晰，逻辑严谨。

**核心代码：**
```cpp
void dfs(int x,int y,int dir,int cnt){
    while(x<1) x+=n;
    while(n<x) x-=n;
    while(y<1) y+=m;
    while(m<y) y-=m;
    if(vis[x][y][dir][cnt]) return ;
    if(a[x][y]=='@') puts("YES"),exit(0);
    vis[x][y][dir][cnt]=1;
    switch(a[x][y]){
        case '>':dfs(x+dx[1],y+dy[1],1,cnt);break;
        case 'v':dfs(x+dx[2],y+dy[2],2,cnt);break;
        case '<':dfs(x+dx[3],y+dy[3],3,cnt);break;
        case '^':dfs(x+dx[4],y+dy[4],4,cnt);break;
        case '+':dfs(x+dx[dir],y+dy[dir],dir,(cnt+1)%16);break;
        case '-':dfs(x+dx[dir],y+dy[dir],dir,(cnt-1+16)%16);break;
        case '|':if(cnt==0) dfs(x+dx[2],y+dy[2],2,cnt); else dfs(x+dx[4],y+dy[4],4,cnt); break;
        case '_':if(cnt==0) dfs(x+dx[1],y+dy[1],1,cnt); else dfs(x+dx[3],y+dy[3],3,cnt); break;
        case '.':dfs(x+dx[dir],y+dy[dir],dir,cnt);break;
        case '?':for(int i=1;i<=4;i++) dfs(x+dx[i],y+dy[i],i,cnt); break;
        default:dfs(x+dx[dir],y+dy[dir],dir,a[x][y]-'0');break;
    }
}
```

#### 题解3：作者：Iron_Heart (赞：1)  
**星级：4**  
**关键亮点：**  
1. 使用 `switch` 语句处理不同的命令，代码结构清晰。
2. 通过 `exit(0)` 直接结束程序，简化了输出逻辑。
3. 代码简洁，逻辑清晰。

**核心代码：**
```cpp
bool dfs(int x, int y, int d, int num) {
    x = (x - 1 + n) % n + 1;
    y = (y - 1 + m) % m + 1;
    if (vis[x][y][d][num]) return 0;
    vis[x][y][d][num] = 1;
    if (mp[x][y] == '@') return 1;
    switch (mp[x][y]) {
        case '<': d = 0; break;
        case '>': d = 3; break;
        case '^': d = 2; break;
        case 'v': d = 1; break;
        case '_': d = num ? 0 : 3; break;
        case '|': d = num ? 2 : 1; break;
        case '?': for (int i = 0; i < 4; ++i) if (dfs(x + dx[i], y + dy[i], i, num)) return 1; return 0;
        case '.': break;
        case '+': num++; if (num == 16) num = 0; break;
        case '-': num--; if (num == -1) num = 15; break;
        default: num = mp[x][y] - '0'; break;
    }
    return dfs(x + dx[d], y + dy[d], d, num);
}
```

### 最优关键思路与技巧

1. **状态记录**：使用四维数组记录每个状态（位置、方向、存储器值），避免重复访问，防止死循环。
2. **边界处理**：通过取模或 `while` 循环处理边界条件，确保程序在走出界时能正确跳转。
3. **命令处理**：使用 `switch` 语句处理不同的命令，代码结构清晰，逻辑严谨。
4. **直接结束程序**：通过 `exit(0)` 直接结束程序，简化了输出逻辑。

### 可拓展之处

1. **类似题目**：可以扩展到其他需要模拟执行过程的题目，如虚拟机、解释器等。
2. **优化方向**：可以考虑使用广度优先搜索（BFS）来减少递归深度，或者使用记忆化搜索来优化性能。

### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
3. [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)

---
处理用时：81.59秒