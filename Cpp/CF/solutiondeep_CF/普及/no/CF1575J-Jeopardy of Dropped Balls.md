# 题目信息

# Jeopardy of Dropped Balls

## 题目描述

Mr. Chanek has a new game called Dropping Balls. Initially, Mr. Chanek has a grid $ a $ of size $ n \times m $

Each cell $ (x,y) $ contains an integer $ a_{x,y} $ denoting the direction of how the ball will move.

- $ a_{x,y}=1 $ — the ball will move to the right (the next cell is $ (x, y + 1) $ );
- $ a_{x,y}=2 $ — the ball will move to the bottom (the next cell is $ (x + 1, y) $ );
- $ a_{x,y}=3 $ — the ball will move to the left (the next cell is $ (x, y - 1) $ ).

Every time a ball leaves a cell $ (x,y) $ , the integer $ a_{x,y} $ will change to $ 2 $ . Mr. Chanek will drop $ k $ balls sequentially, each starting from the first row, and on the $ c_1, c_2, \dots, c_k $ -th ( $ 1 \leq c_i \leq m $ ) columns.

Determine in which column each ball will end up in (position of the ball after leaving the grid).

## 说明/提示

In the first example, the first ball will drop as follows. Note that the cell $ (1, 1) $ will change direction to the bottom direction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575J/fa2adb81fdf96ce1b92e46629bbcb5cf70e88c62.png)The second and third balls will drop as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575J/7c28f503603add2e57bd518e7c027aa1a32b9f99.png)All balls will be dropped from the first row and on the $ c_1, c_2, \dots, c_k $ -th columns respectively. A ball will stop dropping once it leaves the grid.

## 样例 #1

### 输入

```
5 5 3
1 2 3 3 3
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
1 2 1```

### 输出

```
2 2 1```

## 样例 #2

### 输入

```
1 2 2
1 3
1 2```

### 输出

```
1 2```

# AI分析结果

### 题目内容重写
Mr. Chanek有一个新游戏叫做“Dropping Balls”。最初，Mr. Chanek有一个大小为$n \times m$的网格$a$。每个单元格$(x,y)$包含一个整数$a_{x,y}$，表示球将如何移动的方向。

- $a_{x,y}=1$ — 球将向右移动（下一个单元格是$(x, y + 1)$）；
- $a_{x,y}=2$ — 球将向下移动（下一个单元格是$(x + 1, y)$）；
- $a_{x,y}=3$ — 球将向左移动（下一个单元格是$(x, y - 1)$）。

每当一个球离开单元格$(x,y)$时，整数$a_{x,y}$将变为$2$。Mr. Chanek将依次投放$k$个球，每个球从第一行开始，分别在第$c_1, c_2, \dots, c_k$列（$1 \leq c_i \leq m$）上。

确定每个球最终将落在哪一列（球离开网格后的位置）。

### 算法分类
模拟

### 题解综合分析
本题的核心是通过模拟球的移动过程来确定每个球的最终位置。由于每个球经过的单元格会改变其方向，因此需要实时更新网格状态。大多数题解采用了直接模拟的方法，部分题解通过优化减少了不必要的计算。

### 所选高星题解
#### 1. 作者：RE_Prince (4星)
**关键亮点**：
- 直接模拟球的移动过程，代码简洁易懂。
- 通过`ios::sync_with_stdio(0)`加速输入输出，优化了性能。

**核心代码**：
```cpp
while (T--) {
    int col;
    cin >> col;
    x = 1, y = col;
    while (x <= n) {
        int s = a[x][y];
        a[x][y] = 2;
        if (s == 1) y++;
        if (s == 2) x++;
        if (s == 3) y--;
    }
    cout << y << " ";
}
```

#### 2. 作者：xzy090626 (4星)
**关键亮点**：
- 提供了两种实现方式：递归和while循环，适合不同编程习惯的读者。
- 详细分析了时间复杂度，帮助读者理解算法的效率。

**核心代码**：
```cpp
while(x <= n && y <= m) {
    int tmp = s[x][y];
    s[x][y] = 2;
    if(tmp==1) y++;
    else if(tmp==2) x++;
    else y--;
}
```

#### 3. 作者：徐天乾 (4星)
**关键亮点**：
- 代码简洁，直接按题目要求进行处理。
- 通过`scanf`和`printf`进一步优化了输入输出性能。

**核心代码**：
```cpp
while (x<=n){
    v=a[x][y];a[x][y]=2;
    if (v==1) y++;
    if (v==2) x++;
    if (v==3) y--;
}
```

### 最优关键思路或技巧
1. **实时更新网格状态**：每次球经过一个单元格后，立即更新该单元格的方向为2，确保后续球的移动路径正确。
2. **输入输出优化**：使用`ios::sync_with_stdio(0)`或`scanf`/`printf`加速输入输出，减少程序运行时间。
3. **多种实现方式**：递归和while循环两种实现方式，适合不同编程习惯的读者。

### 可拓展之处
本题可以拓展为更复杂的网格移动问题，例如引入更多的移动方向或动态变化的网格状态。类似的问题可以考察学生对模拟和状态更新的理解。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1131 最小生成树](https://www.luogu.com.cn/problem/P1131)

---
处理用时：28.84秒