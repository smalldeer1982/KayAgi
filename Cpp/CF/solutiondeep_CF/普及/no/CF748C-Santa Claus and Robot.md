# 题目信息

# Santa Claus and Robot

## 题目描述

Santa Claus has Robot which lives on the infinite grid and can move along its lines. He can also, having a sequence of $ m $ points $ p_{1},p_{2},...,p_{m} $ with integer coordinates, do the following: denote its initial location by $ p_{0} $ . First, the robot will move from $ p_{0} $ to $ p_{1} $ along one of the shortest paths between them (please notice that since the robot moves only along the grid lines, there can be several shortest paths). Then, after it reaches $ p_{1} $ , it'll move to $ p_{2} $ , again, choosing one of the shortest ways, then to $ p_{3} $ , and so on, until he has visited all points in the given order. Some of the points in the sequence may coincide, in that case Robot will visit that point several times according to the sequence order.

While Santa was away, someone gave a sequence of points to Robot. This sequence is now lost, but Robot saved the protocol of its unit movements. Please, find the minimum possible length of the sequence.

## 说明/提示

The illustrations to the first three tests are given below.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/055feaa24aaf28c272b502eb1fa7804fe2ce0a51.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/795acf4da6085a8e5b976c179bfde9796711ae28.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/75228340b2ee205f332e39cf435e438e28662e9d.png)

The last example illustrates that each point in the sequence should be counted as many times as it is presented in the sequence.

## 样例 #1

### 输入

```
4
RURD
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
RRULDD
```

### 输出

```
2
```

## 样例 #3

### 输入

```
26
RRRULURURUULULLLDLDDRDRDLD
```

### 输出

```
7
```

## 样例 #4

### 输入

```
3
RLL
```

### 输出

```
2
```

## 样例 #5

### 输入

```
4
LRLR
```

### 输出

```
4
```

# AI分析结果



# 题目中文翻译

## 题目描述

圣诞老人有一个机器人，它生活在无限大的网格上，并沿着网格线移动。给定一个包含 $m$ 个整数坐标点的序列 $p_1,p_2,...,p_m$，机器人会依次访问这些点：从初始位置 $p_0$ 开始，首先沿着 $p_0$ 到 $p_1$ 的最短路径移动，然后从 $p_1$ 的最短路径移动到 $p_2$，依此类推。现在已知机器人移动的单元轨迹（由 R/L/U/D 组成的字符串），求最少的必要点数。

## 输入输出样例
（与原文样例相同，此处省略）

---

**算法分类**：贪心

---

### 精选题解分析

#### 1. ChenZQ 的题解（★★★★☆）
**核心思路**：  
- 维护起点坐标 $(x,y)$ 和当前坐标 $(nx,ny)$，统计步数 $step$
- 每次移动后计算曼哈顿距离，若发现累积步数超过当前起点到终点的曼哈顿距离，说明必须新增转折点
- 此时将前一步坐标设为新起点，重置步数

**代码亮点**：  
- 直观模拟网格移动过程
- 通过坐标差与步数的关系直接判断路径合法性
- 时间复杂度 $O(n)$，空间复杂度 $O(1)$

**核心代码**：
```cpp
int x = 0, y = 0, nx = 0, ny = 0, ans = 0, step = 0;
for (int i = 0; i < n; i++) {
    step++;
    int tx = nx, ty = ny;
    // 更新当前坐标
    if (s[i] == 'U') nx--;
    else if (s[i] == 'D') nx++;
    else if (s[i] == 'L') ny--;
    else ny++;
    // 判断是否合法
    if (abs(nx - x) + abs(ny - y) != step) {
        ans++;
        x = tx; y = ty; // 回退到前一个合法点
        step = 1;       // 重置步数
    }
}
if (x != nx || y != ny) ans++;
cout << ans;
```

---

#### 2. PR_CYJ 的题解（★★★★☆）
**核心思路**：  
- 使用方向向量模拟移动
- 维护上一个转折点坐标 $(ltx, lty)$ 和当前坐标 $(nwx, nwy)$
- 通过比较实际移动步数与曼哈顿距离判断是否新增转折点

**实现技巧**：  
- 使用字典预存方向增量，代码更易维护
- 终点需额外判断

**核心代码**：
```cpp
map<char, int> dx = {{'U',-1}, {'D',1}, {'L',0}, {'R',0}};
map<char, int> dy = {{'U',0}, {'D',0}, {'L',-1}, {'R',1}};

int ltx = 0, lty = 0, nwx = 0, nwy = 0, s = 0, sum = 0;
for (char c : s) {
    nwx += dx[c];
    nwy += dy[c];
    s++;
    if (abs(nwx - ltx) + abs(nwy - lty) != s) {
        sum++;
        ltx = nwx - dx[c]; // 回退到合法点
        lty = nwy - dy[c];
        s = 1;
    }
}
cout << sum + 1; // 补上终点
```

---

#### 3. filletoto 的题解（★★★★☆）
**核心思路**：  
- 维护方向冲突标记数组 `vis`
- 当检测到相反方向时（如当前是 L 且 vis[R] 存在），触发新转折点
- 每次冲突后重置标记数组

**优化点**：  
- 使用 ASCII 直接索引，无需哈希计算
- 代码简洁，仅需一次遍历

**核心代码**：
```cpp
bool vis[128] = {0};
int ans = 0;
for (char c : s) {
    if ((c == 'L' && vis['R']) || (c == 'R' && vis['L']) ||
        (c == 'U' && vis['D']) || (c == 'D' && vis['U'])) {
        ans++;
        memset(vis, 0, sizeof(vis));
    }
    vis[c] = true;
}
cout << ans + 1;
```

---

### 关键思路总结
1. **方向冲突检测**：通过记录当前路径的方向集合，发现相反方向时触发分割点
2. **坐标模拟法**：通过维护起点坐标和曼哈顿距离关系，直接判断路径合法性
3. **贪心性质**：每个决策只依赖当前状态，无需全局回溯

---

### 同类题目推荐
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141) - 连通区域与路径分析
2. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098) - 方向序列处理
3. [P1016 旅行家的预算](https://www.luogu.com.cn/problem/P1016) - 贪心策略选择加油点

---
处理用时：67.93秒