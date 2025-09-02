# 题目信息

# Ticks

## 题目描述

Casimir has a rectangular piece of paper with a checkered field of size $ n \times m $ . Initially, all cells of the field are white.

Let us denote the cell with coordinates $ i $ vertically and $ j $ horizontally by $ (i, j) $ . The upper left cell will be referred to as $ (1, 1) $ and the lower right cell as $ (n, m) $ .

Casimir draws ticks of different sizes on the field. A tick of size $ d $ ( $ d > 0 $ ) with its center in cell $ (i, j) $ is drawn as follows:

1. First, the center cell $ (i, j) $ is painted black.
2. Then exactly $ d $ cells on the top-left diagonally to the center and exactly $ d $ cells on the top-right diagonally to the center are also painted black.
3. That is all the cells with coordinates $ (i - h, j \pm h) $ for all $ h $ between $ 0 $ and $ d $ are painted. In particular, a tick consists of $ 2d + 1 $ black cells.

An already painted cell will remain black if painted again. Below you can find an example of the $ 4 \times 9 $ box, with two ticks of sizes $ 2 $ and $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1579C/b2b898f1569af103ffaf93cfc9bbbe7d51da03c3.png)You are given a description of a checkered field of size $ n \times m $ . Casimir claims that this field came about after he drew some (possibly $ 0 $ ) ticks on it. The ticks could be of different sizes, but the size of each tick is at least $ k $ (that is, $ d \ge k $ for all the ticks).

Determine whether this field can indeed be obtained by drawing some (possibly none) ticks of sizes $ d \ge k $ or not.

## 说明/提示

The first sample test case consists of two asterisks neither of which can be independent ticks since ticks of size $ 0 $ don't exist.

The second sample test case is already described in the statement (check the picture in the statement). This field can be obtained by drawing ticks of sizes $ 2 $ and $ 3 $ , as shown in the figure.

The field in the third sample test case corresponds to three ticks of size $ 1 $ . Their center cells are marked with $ \color{blue}{\text{blue}} $ , $ \color{red}{\text{red}} $ and $ \color{green}{\text{green}} $ colors:

\*.\*.\* $ \color{blue}{\textbf{*}} $ \*\*. $ \color{green}{\textbf{*}}\color{red}{\textbf{*}} $ .....The field in the fourth sample test case could have been obtained by drawing two ticks of sizes $ 1 $ and $ 2 $ . Their vertices are marked below with $ \color{blue}{\text{blue}} $ and $ \color{red}{\text{red}} $ colors respectively:

.....\*...\*.\*.\*... $ \color{red}{\textbf{*}} $ .\*... $ \color{blue}{\textbf{*}} $ .The field in the fifth sample test case can not be obtained because $ k = 2 $ , and the last asterisk in the fourth row from the top with coordinates $ (4, 5) $ can only be a part of a tick of size $ 1 $ .

The field in the sixth sample test case can not be obtained because the top left asterisk $ (1, 1) $ can't be an independent tick, since the sizes of the ticks must be positive, and cannot be part of a tick with the center cell in the last row, since it is separated from it by a gap (a point, '.') in $ (2, 2) $ .

In the seventh sample test case, similarly, the field can not be obtained by the described process because the asterisks with coordinates $ (1, 2) $ (second cell in the first row), $ (3, 1) $ and $ (3, 3) $ (leftmost and rightmost cells in the bottom) can not be parts of any ticks.

## 样例 #1

### 输入

```
8
2 3 1
*.*
...
4 9 2
*.*.*...*
.*.*...*.
..*.*.*..
.....*...
4 4 1
*.*.
****
.**.
....
5 5 1
.....
*...*
.*.*.
..*.*
...*.
5 5 2
.....
*...*
.*.*.
..*.*
...*.
4 7 1
*.....*
.....*.
..*.*..
...*...
3 3 1
***
***
***
3 5 1
*...*
.***.
.**..```

### 输出

```
NO
YES
YES
YES
NO
NO
NO
NO```

# AI分析结果

### 题目内容

Casimir 有一张大小为 $n \times m$ 的方格纸，初始时所有格子都是白色的。Casimir 在纸上画了一些不同大小的“勾形”（ticks），每个勾形的大小为 $d$（$d > 0$），其中心位于某个格子 $(i, j)$。勾形的绘制规则如下：

1. 首先，中心格子 $(i, j)$ 被涂黑。
2. 然后，从中心格子向左上角和右上角各延伸 $d$ 个格子，并将这些格子也涂黑。
3. 具体来说，所有坐标为 $(i - h, j \pm h)$ 的格子（$0 \leq h \leq d$）都会被涂黑。因此，一个勾形由 $2d + 1$ 个黑色格子组成。

已经涂黑的格子如果再次被涂黑，仍然保持黑色。题目给定一个 $n \times m$ 的方格纸，Casimir 声称这张纸是通过绘制一些勾形得到的，且每个勾形的大小至少为 $k$（即 $d \geq k$）。请判断这张方格纸是否确实可以通过绘制一些大小至少为 $k$ 的勾形得到。

### 算法分类
模拟

### 题解分析与结论

题目的核心是通过模拟勾形的绘制过程，判断给定的方格纸是否可以通过绘制大小至少为 $k$ 的勾形得到。所有题解都采用了枚举和模拟的思路，主要区别在于实现细节和优化程度。

#### 关键思路总结：
1. **枚举中心点**：遍历每个格子，尝试将其作为勾形的中心点。
2. **模拟勾形绘制**：从中心点向左上角和右上角延伸，判断是否满足勾形的条件（即延伸的长度至少为 $k$）。
3. **标记已覆盖的格子**：如果满足条件，则标记这些格子为已覆盖。
4. **检查覆盖情况**：最后检查所有需要涂黑的格子是否都被标记过，若全部标记则输出 `YES`，否则输出 `NO`。

#### 优化技巧：
- **提前终止**：在模拟勾形绘制时，若发现无法满足条件，提前终止循环。
- **最小化标记范围**：只标记满足条件的勾形所覆盖的格子，避免重复标记。

### 精选题解

#### 题解1：EternalHeart1314（评分：4星）
**关键亮点**：
- 代码简洁，逻辑清晰。
- 通过 `while` 循环模拟勾形的绘制过程，并提前终止不满足条件的勾形。
- 使用二维数组 `a` 记录哪些格子被勾形覆盖，最后检查所有黑色格子是否都被覆盖。

**核心代码**：
```cpp
for(int i(1); i <= n; ++ i) {
    for(int j(1); j <= m; ++ j) {
        if(s[i][j] == '*') {
            cnt = 0, x = i, y = z = j;
            while(-- x && -- y && ++ z <= m && s[x][y] == '*' && s[x][z] == '*') {
                ++ cnt;
            }
            if(cnt >= k) {
                a[i][j] = true;
                x = i, y = z = j;
                while(-- x && -- y && ++ z <= m && s[x][y] == '*' && s[x][z] == '*') {
                    a[x][y] = a[x][z] = true;
                }
            }
        }
    }
}
```

#### 题解2：M_CI（评分：4星）
**关键亮点**：
- 使用双层循环枚举勾形的起点，并模拟勾形的绘制过程。
- 通过 `fl` 变量判断勾形是否合法，若合法则标记所有覆盖的格子。
- 最后通过比较原图和标记图来判断是否满足条件。

**核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    for(int j=1;j<=m;j++) {
        for(int u=k;i+u<=n&&j+2*u<=m;u++) {
            bool fl=1;
            int x=i,y=j;
            for(int v=1;v<=u+1;v++) {
                if(c[x][y]!='*') {
                    fl=0;
                    break;
                }
                x++;
                y++;
            }
            x-=2;
            for(int v=1;v<=u;v++) {
                if(c[x][y]!='*') {
                    fl=0;
                    break;
                }
                x--;
                y++;
            }
            if(fl) {
                x=i; y=j;
                for(int v=1;v<=u+1;v++) {
                    f[x][y]='*';
                    x++;
                    y++;
                }
                x-=2;
                for(int v=1;v<=u;v++) {
                    f[x][y]='*';
                    x--;
                    y++;
                }
            }
        }
    }
}
```

#### 题解3：漠寒（评分：4星）
**关键亮点**：
- 使用 `vis` 数组记录哪些格子被勾形覆盖。
- 通过 `check` 和 `dcheck` 函数判断勾形是否合法，若合法则标记覆盖的格子。
- 最后检查所有需要涂黑的格子是否都被覆盖。

**核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    for(int j=1;j<=m;j++) {
        if(!check(i,j))continue;
        if(!dcheck(i,j))continue;
        int x=i,y=j,l=j,t=1;
        for(;t<=k;x--,y--,l++,t++) {
            vis[x][y]=vis[x][l]=1;
        }
        for(;x>=1;x--,y--,l++,t++) {
            if(!a[x][y]||!a[x][l])break;
            vis[x][y]=vis[x][l]=1;
        }
    }
}
```

### 推荐题目
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：43.01秒