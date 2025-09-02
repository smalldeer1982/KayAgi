# 题目信息

# [USACO13FEB] Tractor S

## 题目描述

FJ有块农田太崎岖了，他要买一辆新拖拉机才能在这里巡视。这块农田由N x N个格子的非负整数表示高度(1<=N<=500)。拖拉机从当前格子走到相邻格子（东、南、西、北四个方向）的代价为高度差D，则FJ驶过这两个格子的拖拉机最少也要值D块钱。

FJ愿意花足够的钱买一辆新的拖拉机使得他能以最小的高度差走遍所有格子的一半(如果格子总数是奇数，那么一半的值为四舍五入的值)。因为FJ很懒，所以他找到你帮他编程计算他最小需要花多少钱买到符合这些要求的拖拉机。

## 样例 #1

### 输入

```
5 
0 0 0 3 3 
0 0 0 0 3 
0 9 9 3 3 
9 9 9 3 3 
9 9 9 9 3 
```

### 输出

```
3 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕两种思路：二分答案+搜索（DFS或BFS）、并查集+最小生成树（Kruskal算法）。
 - **二分答案+搜索**：利用二分答案将最优化问题转化为可行性问题，通过DFS或BFS判断在给定高度差下能否遍历至少一半格子。此思路难点在于理解二分的单调性及搜索函数的正确实现。
 - **并查集+最小生成树**：以相邻格子高度差为边权建图，用Kruskal算法生成最小生成树，同时用并查集维护集合大小，当集合大小超过一半时输出当前边权。难点在于建图、并查集操作及最小生成树算法的结合。

### 所选的题解
 - **作者：daihang (赞：46)  星级：5星**
    - **关键亮点**：思路清晰，代码结构完整，详细解释了建图、并查集维护集合大小及Kruskal算法的实现，还提供了快读优化。
    - **核心代码**：
```cpp
// 计算点编号
int ex(int i,int j){
    return (i - 1)*n + j;
}
// Kruskal算法主流程
for (int i = 1; i < tp; i++) {
    int x = edge[i].u;
    int y = edge[i].v;
    int w = edge[i].w;
    x = find(x);
    y = find(y);
    if (x!= y) {
        fa[x] = y;
        siz[y] += siz[x];
        if (siz[y] >= (n * n + 1) / 2) {
            cout << w << endl;
            return 0;
        }
    }
}
```
    - **核心思想**：通过`ex`函数将二维坐标转化为一维编号用于建图。在Kruskal算法中，遍历排序后的边，若边两端点不在同一集合则合并，并检查新集合大小是否满足要求。
 - **作者：JJA_ (赞：12)  星级：4星**
    - **关键亮点**：提供了暴力DFS和DFS+二分两种方法，对思路和代码解释详细，有助于理解二分答案和DFS的结合。
    - **个人心得**：暴力DFS会超时，通过二分优化可解决。
    - **核心代码**：
```cpp
// DFS函数
int dfs(int x, int y, int d) {
    int sum = 1;
    flag[x][y] = 1;
    for (int i = 1; i <= 4; i++) {
        int px = x + xpos[i];
        int py = y + ypos[i];
        if (abs(mapp[x][y] - mapp[px][py]) <= d && px >= 1 && py >= 1 && px <= n && py <= n &&!flag[px][py]) {
            sum += dfs(px, py, d);
        }
    }
    return sum;
}
// 二分答案
while (l <= r) {
    int mid = (l + r) / 2;
    if (chkans(mid) == 1) {
        r = mid - 1, ans = mid;
    } else {
        l = mid + 1;
    }
}
```
    - **核心思想**：`dfs`函数计算在高度差`d`下从点`(x, y)`出发能遍历的格子数。二分答案过程中，通过`chkans`函数（内部调用`dfs`）判断当前二分的高度差`mid`是否满足遍历至少一半格子的要求。
 - **作者：CR_Raphael (赞：8)  星级：4星**
    - **关键亮点**：代码简洁明了，直接阐述以相邻点高度差建图，跑“伪”最小生成树并维护并查集大小的思路。
    - **核心代码**：
```cpp
// 重载比较运算符
bool operator<(road a, road b) {
    return a.l < b.l;
}
// 并查集查找函数
int find(int a) {
    if (fa[a] == a) return a;
    fa[a] = find(fa[a]);
    return fa[a];
}
// 合并函数
void add(int a, int b) {
    int faa, fab;
    faa = find(a);
    fab = find(b);
    fa[fab] = faa;
    size[faa] += size[fab];
    if (size[faa] > maxsize) {
        maxsize = size[faa];
        maxi = faa;
    }
    return;
}
// 主函数中构建图及Kruskal过程
m = 0;
for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++) {
        for (ii = 0; ii <= 1; ii++) {
            mi = i + zi[ii];
            mj = j + zj[ii];
            if (mi > n || mj > n) continue;
            m++;
            r[m].st = (i - 1)*n + j;
            r[m].en = (mi - 1)*n + mj;
            r[m].l = abs(node[i][j] - node[mi][mj]);
        }
    }
sort(r + 1, r + 1 + m);
maxsize = 0;
i = 0;
n = n * n;
while (maxsize < n / 2) {
    i++;
    if (i > m) break;
    t = r[i];
    ta = t.en;
    tb = t.st;
    if (find(ta) == find(tb)) continue;
    add(ta, tb);
}
printf("%d\n", t.l);
```
    - **核心思想**：重载`<`运算符方便对边按权值排序。`find`函数实现并查集路径压缩查找。`add`函数合并两个集合并更新最大集合大小。主函数中构建图并执行Kruskal算法，找到满足集合大小要求的最小边权。

### 最优的关键思路或技巧
 - **二分答案**：将求最大高度差最小值的最优化问题转化为判断在某高度差下能否遍历至少一半格子的可行性问题，降低问题复杂度。
 - **并查集与最小生成树结合**：利用并查集维护连通性和集合大小，在最小生成树构建过程中快速判断是否满足遍历格子数要求。

### 可拓展之处
此类题目属于图论中求最值相关问题，常见套路是通过二分答案或贪心策略将问题转化为可高效解决的形式。类似题目可考察不同的图结构、边权计算方式或遍历条件。

### 相似知识点洛谷题目
 - [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)：基础最小生成树模板题，巩固Kruskal或Prim算法。
 - [P1196 [NOI2002] 银河英雄传说](https://www.luogu.com.cn/problem/P1196)：并查集应用，需维护额外信息，与本题并查集维护集合大小类似。
 - [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：典型二分答案题目，锻炼二分答案的应用能力。 

---
处理用时：52.25秒