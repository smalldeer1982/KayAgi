# 题目信息

# [USACO09OCT] Invasion of the Milkweed G

## 题目描述

Farmer John has always done his best to keep the pastures full of luscious, delicious healthy grass for the cows. He has lost the battle, though, as the evil milkweed has attained a foothold in the northwest part of his farm.

The pasture, as usual, is partitioned into a rectilinear grid of height Y (1 <= Y <= 100) and width X (1 <= X <= 100) with (1,1) being in the lower left corner (i.e., arranged as a normal X,Y coordinate grid). The milkweed has initially begun growing at square (Mx,My). Each week the milkweed propagates to all non-rocky squares that surround any square it already occupies, as many as eight more squares (both the rectilinear squares and the diagonals). After only one week in those squares, it is ready to move on to more squares.

Bessie wants to enjoy all the grass she can before the pastures are taken over by milkweed. She wonders how long it can last. If the milkweed is in square (Mx,My) at time zero, at what time does it complete its invasion of the pasture (which, for the given input data, will always happen)?

The pasture is described by a picture with '.'s for grass and '\*'s for boulders, like this example with X=4 and Y=3:

```
....
..*.
.**.
```

If the milkweed started in the lower left corner (row=1, column=1), then the map would progress like this:

```
    ....  ....  MMM.  MMMM  MMMM
    ..*.  MM*.  MM*.  MM*M  MM*M
    M**.  M**.  M**.  M**.  M**M
week  0    1    2    3    4
```

The milkweed has taken over the entire field after 4 weeks.

## 样例 #1

### 输入

```
4 3 1 1 
.... 
..*. 
.**. 
```

### 输出

```
4 
```

# AI分析结果



**算法分类**: 广度优先搜索 BFS

---

### 综合分析与结论
本题核心是八方向扩散的 BFS 问题，关键点在于坐标转换和层级计数。所有题解均围绕 BFS 展开，部分尝试递推/DFS 但效果不佳。最优解法需正确处理输入坐标的镜像关系，并通过队列层级拓展统计最大扩散时间。

---

### 高星题解推荐

#### 1. 作者：华恋_韵（4.5星）
**关键亮点**  
- 使用标准 BFS 框架，结构清晰，注释明确  
- 正确处理坐标镜像（左下角转左上角）  
- 通过结构体存储坐标和步数，代码可读性强  
**代码核心**  
```cpp
struct node{ int y, x, t; }; // 存储坐标和时间
queue<node> q;
void bfs() {
    q.push(node{sy, sx, 0});
    while (!q.empty()) {
        node now = q.front(); q.pop();
        for (8方向遍历) {
            if (可访问且未标记) {
                q.push(新节点);
                ans = max(ans, 新时间);
            }
        }
    }
}
```

#### 2. 作者：qzcbw（4星）
**关键亮点**  
- 简洁的坐标转换处理  
- 使用二维数组标记已访问点，避免重复计算  
- 在 BFS 过程中直接维护最大值  
**个人心得**  
> "注意行列输入顺序和坐标反转，否则会 WA 多次"

#### 3. 作者：SUNCHAOYI（4星）
**关键亮点**  
- 引用《信息学奥赛一本通》的 BFS 框架，适合初学者  
- 手写队列实现，减少 STL 开销  
- 预处理时通过字符判断直接生成可访问标记  
**代码核心**  
```cpp
int bfs() {
    while (head < tail) {
        取出队首，八方向扩展;
        if (新点合法) {
            更新距离并记录最大值;
            新点入队;
        }
    }
    return ans;
}
```

---

### 最优思路总结
1. **坐标转换**：将左下角坐标系转换为常规的左上角坐标系，通常通过 `y = n - input_y + 1` 实现。  
2. **八方向处理**：使用方向数组 `dx[8]` 和 `dy[8]` 简化代码。  
3. **层级计数**：在 BFS 中通过结构体或队列记录步数，每次扩展时步数+1，维护全局最大值。  
4. **剪枝优化**：通过访问标记数组避免重复计算，提升效率。

---

### 拓展与相似题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)（八方向 BFS）  
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)（矩阵扩散与标记）  
3. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)（层数计数 BFS）

---
处理用时：50.55秒