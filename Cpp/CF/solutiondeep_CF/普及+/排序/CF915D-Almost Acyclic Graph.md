# 题目信息

# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5
```

### 输出

```
NO
```

# AI分析结果



# Almost Acyclic Graph（中文翻译）

## 题目描述

给定一个包含 $n$ 个顶点和 $m$ 条边的有向图。允许删除至多一条边，判断能否使该图变为无环图（即不存在任何起点和终点相同的路径）。

## 输入格式

- 第一行两个整数 $n$ 和 $m$
- 接下来 $m$ 行每行两个整数表示有向边

## 输出格式

YES/NO

## 样例

### 样例1
输入：
```
3 4
1 2
2 3
3 2
3 1
```
输出：
```
YES
```

### 样例2
输入：
```
5 6
1 2
2 3
3 2
3 1
2 1
4 5
```
输出：
```
NO
```

---

### 关键思路总结
**核心优化思想**：删除任意边等价于目标顶点入度减1。通过枚举每个顶点进行入度减1的模拟，单次拓扑排序时间复杂度 $O(n+m)$，整体复杂度优化至 $O(n(n+m))$。

**算法亮点**：
1. 避免暴力枚举边，利用入度性质合并等效操作
2. 预处理原始入度数组，每次拓扑使用副本
3. 通过拓扑排序节点计数判断环的存在性

---

### 精选题解分析

#### 题解作者：青烟绕指柔（★★★★★）
**核心亮点**：
- 时间复杂度严格 $O(n(n+m))$
- 代码简洁（仅20行核心逻辑）
- 使用队列优化拓扑过程

**代码核心**：
```cpp
int n,m,dag[N],t[N];
vector<int> g[N];

int top_sort(){ // 拓扑排序模板
    int cnt=0; queue<int> q;
    for(int i=1;i<=n;i++) if(!dag[i]) q.push(i);
    while(q.size()){
        int u=q.front(); q.pop(); cnt++;
        for(int to:g[u]) if(--dag[to]==0) q.push(to);
    }
    return cnt==n;
}

signed main(){
    // 读入数据...
    for(int i=1;i<=n;i++) t[i]=dag[i]; // 保存原始入度
    for(int i=1;i<=n;i++) if(dag[i]){
        dag[i]--;         // 关键：模拟删除一条入边
        if(top_sort()) return puts("YES"),0;
        for(int i=1;i<=n;i++) dag[i]=t[i]; // 恢复入度
    }
    puts("NO");
}
```

#### 题解作者：CharlesZiy（★★★★☆）
**核心亮点**：
- 详细注释说明入度副本必要性
- 完整封装拓扑排序函数
- 处理入度减1时的边界条件

**调试心得**：
> "每次拓扑排序都要把原来的入度数组复制一份过来，因为在拓扑排序中会对入度数组进行操作。保留副本是必须的，否则会影响后续的判断"

#### 题解作者：Nukumizu_Kaju（★★★★☆）
**代码优化**：
- 独立维护入度数组副本
- 提前判断原始图是否已无环
- 使用STL vector邻接表存储

---

### 同类题目推荐
1. [P2662 拆地毯](https://www.luogu.com.cn/problem/P2662) - 图论中的删边操作应用
2. [P1347 排序](https://www.luogu.com.cn/problem/P1347) - 拓扑排序的经典应用
3. [P3183 食物链](https://www.luogu.com.cn/problem/P3183) - 带权拓扑计数

---

### 关键调试经验
1. **入度副本必须保存**：多个题解提到未保存原始入度导致错误
2. **拓扑计数位置**：必须在出队时计数，不能在入队时计数（否则会漏判环）
3. **空队列处理**：初始入度为0的节点需要全部入队
4. **时间复杂度陷阱**：直接枚举边会达到 $O(10^5 \times 10^5)$ 级别运算，必须通过入度优化

---
处理用时：54.40秒