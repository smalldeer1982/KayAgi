# 题目信息

# [ICPC 2015 WF] Keyboarding

## 题目描述

How many keystrokes are necessary to type a text message? You may think that it is equal to the number of characters in the text, but this is correct only if one keystroke generates one character. With pocket-size devices, the possibilities for typing text are often limited. Some devices provide only a few buttons, significantly fewer than the number of letters in the alphabet. For such devices, several strokes may be needed to type a single character. One mechanism to deal with these limitations is a virtual keyboard displayed on a screen, with a cursor that can be moved from key to key to select characters. Four arrow buttons control the movement of the cursor, and when the cursor is positioned over an appropriate key, pressing the fifth button selects the corresponding character and appends it to the end of the text. To terminate the text, the user must navigate to and select the Enter key. This provides users with an arbitrary set of characters and enables them to type text of any length with only five hardware buttons.

In this problem, you are given a virtual keyboard layout and your task is to determine the minimal number of strokes needed to type a given text, where pressing any of the five hardware buttons constitutes a stroke. The keys are arranged in a rectangular grid, such that each virtual key occupies one or more connected unit squares of the grid. The cursor starts in the upper left corner of the keyboard and moves in the four cardinal directions, in such a way that it always skips to the next unit square in that direction that belongs to a different key. If there is no such unit square, the cursor does not move.

![](https://cdn.luogu.com.cn/upload/image_hosting/3cxjl2y4.png)

   Figure 1: Sample Input 1. An example virtual keyboard and hardware buttons. 

Figure 1, illustrating Sample Input 1, shows a possible way to type CONTEST using 30 strokes on an example virtual keyboard. The red dots represent the virtual keys where the select button was pressed.

## 说明/提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015

## 样例 #1

### 输入

```
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
```

### 输出

```
30
```

## 样例 #2

### 输入

```
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
```

### 输出

```
160
```

## 样例 #3

### 输入

```
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
```

### 输出

```
19
```

## 样例 #4

### 输入

```
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 输出

```
7
```

# AI分析结果



### 算法分类
广度优先搜索 BFS

### 综合分析
题目要求计算在特殊虚拟键盘上输入字符串的最小按键次数，核心思路是通过广度优先搜索（BFS）遍历所有可能的移动路径，结合预处理优化方向移动逻辑。所有题解均采用以下关键技巧：
1. **方向预处理**：预先计算每个位置在四个方向上的可达目标位置，避免重复计算
2. **状态剪枝**：记录每个坐标点当前已匹配的字符数，跳过非最优状态
3. **分层处理**：将移动操作与选择操作分开处理，优先处理可能的选择操作

### 优质题解推荐

#### 1. Durancer（★★★★☆）
**核心亮点**：
- 完整的方向预处理逻辑
- 结构体封装状态信息
- 初始位置连续按键优化
```cpp
// 方向预处理核心代码
void get() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<4;k++) {
                int x=i, y=j;
                while(a[x][y]==a[x+dx[k]][y+dy[k]]) {
                    x += dx[k], y += dy[k];
                }
                f[k][i][j] = {x, y, 0, 0};
            }
}
```

#### 2. 斜揽残箫（★★★★☆）
**核心亮点**：
- 使用单独数组存储方向数据
- 明确的越界判断函数
- 状态更新逻辑清晰
```cpp
// 移动预处理核心代码
void init() {
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            for(int k=1; k<=4; ++k) {
                int sx = i, sy = j;
                while(mp[sx][sy] == mp[i][j]) {
                    sx += dx[k], sy += dy[k];
                }
                if(check(sx,sy)) disx[k][i][j]=sx, disy[k][i][j]=sy;
                else disx[k][i][j]=INF, disy[k][i][j]=INF;
            }
}
```

#### 3. FLAMEs_（★★★★☆）
**独特技巧**：
- 映射表优化字符处理
- 使用`vis`数组记录最大匹配位置
- 分层处理选择与移动操作
```cpp
// BFS核心逻辑
void bfs() {
    queue<node> q;
    q.push({1,1,0,0});
    while(!q.empty()) {
        node u = q.front(); q.pop();
        if(mp[u.x][u.y]==b[u.step]) {
            if(u.step == len) { cout<<u.dis+1; return; }
            vis[u.x][u.y] = u.step+1;
            q.push({u.x, u.y, u.step+1, u.dis+1});
        }
        for(int k=0; k<4; k++) {
            int x = nex[u.x][u.y][k][0], y = nex[u.x][u.y][k][1];
            if(vis[x][y]>=u.step) continue;
            vis[x][y] = u.step;
            q.push({x, y, u.step, u.dis+1});
        }
    }
}
```

### 关键思路总结
1. **方向跳跃预处理**：对每个位置预计算四个方向的下一个不同字符位置，将O(n)移动计算转为O(1)查询
2. **分层状态处理**：将移动步数与已匹配字符数分开记录，优先处理选择操作
3. **剪枝优化**：使用`vis[x][y]`记录坐标(x,y)处的最大已匹配字符数，避免重复处理非最优状态

### 拓展练习
1. [P1131 时态同步](https://www.luogu.com.cn/problem/P1131) - BFS在树形结构中的应用
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - 经典BFS棋盘移动问题
3. [P3958 奶酪](https://www.luogu.com.cn/problem/P3958) - 三维空间BFS与几何判断结合

---
处理用时：50.91秒