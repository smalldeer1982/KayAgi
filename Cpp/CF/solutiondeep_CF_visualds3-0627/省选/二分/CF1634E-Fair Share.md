# 题目信息

# Fair Share

## 题目描述

Even a cat has things it can do that AI cannot.

— Fei-Fei Li



You are given $ m $ arrays of positive integers. Each array is of even length.

You need to split all these integers into two equal multisets $ L $ and $ R $ , that is, each element of each array should go into one of two multisets (but not both). Additionally, for each of the $ m $ arrays, exactly half of its elements should go into $ L $ , and the rest should go into $ R $ .

Give an example of such a division or determine that no such division exists.

## 说明/提示

In the first array, we add the first element to $ R $ and the second to $ L $ . Now $ L = \{2\} $ , and $ R = \{1\} $ .

In the second array, we add the first and third elements to $ L $ and the rest to $ R $ . Now $ L = \{1, 2, 3\} $ and $ R = \{1, 2, 3\} $ .

In the third array, we add elements 2, 3, and 6 to $ L $ , and others — to $ R $ . As a result, $ L = R = \{1, 1, 2, 2, 3, 3\} $ .

## 样例 #1

### 输入

```
3
2
1 2
4
1 2 3 3
6
1 1 2 2 3 3```

### 输出

```
YES
RL
LRLR
RLLRRL```

# AI分析结果



## 唯一算法分类
无算法分类

## 综合分析与结论

### 题解核心思路与难点
所有题解均采用图论建模策略，核心分为三步：
1. **奇偶校验**：若任意数值出现奇数次，直接无解
2. **构建双向约束图**：
   - **位边**：同一数组中相邻元素连边，强制二者分属不同集合
   - **值边**：相同数值的成对出现位置连边，确保数值均分到两个集合
3. **二分图染色**：通过 DFS 或 BFS 对图的连通分量进行黑白染色，确定每个元素的分配方案

**难点**在于如何正确构建约束关系的边结构，并证明图的二分性。所有题解均通过「位边+值边交替」的特性，推导出图中不存在奇数环，从而保证二分图性质成立。

### 可视化设计思路（基于复古像素风格）
1. **动画方案**：
   - 每个数组元素表示为像素网格中的一个方块，颜色区分数值
   - 构建边时用不同颜色高亮位边（蓝色）与值边（黄色）
   - 染色过程动态展示：当前遍历的节点闪烁，相邻节点随染色同步变色（黑/白对应 L/R）
2. **交互设计**：
   - **音效**：建边时播放“滴”声，染色成功时播放“咔”声，无解时播放警报音
   - **自动演示**：按帧逐步展示建边与染色流程，模拟贪吃蛇 AI 路径探索
   - **复古调色板**：使用 8-bit 风格的 16 色调色板，如 #FF0000（红）表示错误，#00FF00（绿）表示通过

## 题解清单（≥4星）

### 作者：dingcx（★★★★☆）
- **亮点**：代码简洁高效，用 `map` 跟踪数值配对，DFS 染色逻辑清晰
- **关键代码段**：
  ```cpp
  // 建边逻辑（位边与值边）
  if (j % 2 == 0) e[tot].push_back(tot-1), e[tot-1].push_back(tot); // 位边
  if (mp[x] > 0) e[tot].push_back(mp[x]), e[mp[x]].push_back(tot);  // 值边
  ```

### 作者：I_am_Accepted（★★★★★）
- **亮点**：提出两种等价算法（欧拉回路与二分图），理论分析深入
- **关键图示**：通过欧拉回路定向实现集合分配，适用于更高维扩展

### 作者：XL4453（★★★★☆）
- **亮点**：代码高度压缩，离散化处理巧妙，适合竞赛快速实现
- **核心判断**：
  ```cpp
  if (mp[num[tot]] == 0) mp[num[tot]] = tot;  // 值边配对管理
  else add(mp[num[tot]], tot), mp[num[tot]] = 0;
  ```

## 最优思路提炼
- **约束建模**：将「元素分配冲突」转化为图的边约束，确保二分图性质
- **成对处理**：数值出现次数与数组长度均需成对，通过奇偶校验快速排除无效情况
- **交替染色**：DFS 时交替切换颜色，天然适配二分图的递归性质

## 类似题目推荐
1. **P1330 封锁阳光大学**：二分图判定与最小覆盖
2. **CF862B Mahmoud and Ehab and the bipartiteness**：二分图边数扩展
3. **P1155 双栈排序**：通过图论建模解决元素分配问题

## 核心代码实现（dingcx 版本）
```cpp
#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const int MAXN=2e5+10;
map<int,int> mp; // 数值配对跟踪
vector<int> e[MAXN<<1]; // 邻接表
bool vis[MAXN];
int ans[MAXN];

void dfs(int u, int num) {
    ans[u] = num; vis[u] = 1;
    for (int v : e[u]) if (!vis[v]) dfs(v, num^1);
}

int main() {
    int m, tot = 0; scanf("%d", &m);
    for (int i=1; i<=m; i++) {
        int n; scanf("%d", &n);
        for (int j=1; j<=n; j++) {
            int x; scanf("%d", &x); tot++;
            // 位边构建
            if (j % 2 == 0) {
                e[tot].push_back(tot-1);
                e[tot-1].push_back(tot);
            }
            // 值边构建
            if (mp.count(x)) {
                int prev = mp[x];
                e[tot].push_back(prev);
                e[prev].push_back(tot);
                mp.erase(x);
            } else mp[x] = tot;
        }
    }
    if (!mp.empty()) { puts("NO"); return 0; }
    for (int i=1; i<=tot; i++) if (!vis[i]) dfs(i, 0);
    puts("YES");
    // 输出分配结果
    int ptr = 0;
    for (int i=1; i<=m; i++) {
        int n; scanf("%d", &n);
        for (int j=1; j<=n; j++) putchar(ans[++ptr] ? 'L' : 'R');
        putchar('\n');
    }
    return 0;
}
```

## 可视化与复古游戏设计
1. **Canvas 绘制**：将每个元素位置映射为网格坐标，边用线段连接
2. **音效触发**：
   - 建边时播放 `beep(500, 50)`（500Hz，50ms）
   - 染色时播放 `beep(800, 30)`，错误时 `beep(200, 200)`
3. **自动演示模式**：按帧推进建边与染色，模拟 AI 决策路径
4. **积分系统**：每正确染色一个连通块得 100 分，连击倍率递增

## 个人心得摘录
> "在 Debug 中发现建边顺序影响染色结果，但最终只要保证二分图性质，任意合法染色均可。竞赛中需注意输出格式与输入顺序的映射。" —— dingcx

---
处理用时：79.47秒