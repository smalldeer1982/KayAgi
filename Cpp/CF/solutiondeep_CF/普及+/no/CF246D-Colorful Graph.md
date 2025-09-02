# 题目信息

# Colorful Graph

## 题目描述

You've got an undirected graph, consisting of $ n $ vertices and $ m $ edges. We will consider the graph's vertices numbered with integers from 1 to $ n $ . Each vertex of the graph has a color. The color of the $ i $ -th vertex is an integer $ c_{i} $ .

Let's consider all vertices of the graph, that are painted some color $ k $ . Let's denote a set of such as $ V(k) $ . Let's denote the value of the neighbouring color diversity for color $ k $ as the cardinality of the set $ Q(k)={c_{u} : c_{u}≠k $ and there is vertex $ v $ belonging to set $ V(k) $ such that nodes $ v $ and $ u $ are connected by an edge of the graph $ } $ .

Your task is to find such color $ k $ , which makes the cardinality of set $ Q(k) $ maximum. In other words, you want to find the color that has the most diverse neighbours. Please note, that you want to find such color $ k $ , that the graph has at least one vertex with such color.

## 样例 #1

### 输入

```
6 6
1 1 2 3 5 8
1 2
3 2
1 4
4 3
4 5
4 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 6
4 2 5 2 4
1 2
2 3
3 1
5 3
5 4
3 4
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 多彩图

## 题目描述
你有一个无向图，由 $n$ 个顶点和 $m$ 条边组成。我们将图的顶点编号为从1到 $n$ 。图的每个顶点都有一种颜色。第 $i$ 个顶点的颜色是整数 $c_{i}$ 。

让我们考虑图中所有染成某种颜色 $k$ 的顶点。我们将这样的顶点集合记为 $V(k)$ 。我们将颜色 $k$ 的相邻颜色多样性值记为集合 $Q(k)$ 的基数，其中 $Q(k)=\{c_{u} : c_{u}≠k \text{ 且存在属于集合 } V(k) \text{ 的顶点 } v \text{ ，使得顶点 } v \text{ 和 } u \text{ 通过图的一条边相连}\}$ 。

你的任务是找到这样一种颜色 $k$ ，使得集合 $Q(k)$ 的基数最大。换句话说，你想找到具有最多样化邻居的颜色。请注意，你要找到这样一种颜色 $k$ ，使得图中至少有一个顶点具有这种颜色。

## 样例 #1
### 输入
```
6 6
1 1 2 3 5 8
1 2
3 2
1 4
4 3
4 5
4 6
```
### 输出
```
3
```

## 样例 #2
### 输入
```
5 6
4 2 5 2 4
1 2
2 3
3 1
5 3
5 4
3 4
```
### 输出
```
2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕统计每种颜色的相邻不同颜色的种类数，然后找出数量最多的颜色。主要难点在于如何高效地去重，避免重复统计同一种相邻颜色。不同题解采用了不同的数据结构来解决这个问题，如 `map` 和 `set` 。使用 `map` 时，通过记录每种颜色与其他颜色是否相连来避免重复计算；使用 `set` 则利用其自动去重的特性，直接将相邻的不同颜色插入 `set` 中。

### 所选的题解
- **作者：AKPC (5星)**
    - **关键亮点**：思路清晰，详细解释了 `map` 的性质及在本题中的应用，代码简洁明了。
    - **个人心得**：指出 `unordered_map` 用哈希实现有误差但更快，提醒使用时需注意。
    - **重点代码核心思想**：用 `map` 数组 `mp` 记录每种颜色是否连接其他颜色，避免重复计算，同时用 `ans` 数组累计每种颜色的答案。
    - **核心代码片段**：
```cpp
for (int i=1;i<=m;i++){
    cin>>x>>y;
    if (a[x]==a[y]) continue;
    if (!mp[a[x]][a[y]]) ans[a[x]]++;
    mp[a[x]][a[y]]=1;
    if (!mp[a[y]][a[x]]) ans[a[y]]++;
    mp[a[y]][a[x]]=1;
}
for (int i=1;i<=100000;i++) if (tmp[i]&&ans[i]>maxn) maxn=ans[i],res=i;
```
- **作者：wxzzzz (4星)**
    - **关键亮点**：简洁阐述题意和思路，代码逻辑清晰，利用 `map` 对相邻颜色种类数进行去重和统计。
    - **重点代码核心思想**：用 `map<pair<int, int>, bool>` 类型的 `flag` 记录已经统计过的不同颜色顶点对，避免重复计算，`cntc` 数组统计每种颜色相邻的不同颜色种类数。
    - **核心代码片段**：
```cpp
while (m--) {
    cin >> x >> y;
    if (c[x] == c[y])
        continue;
    if (!flag[{c[x], c[y]}]) {
        cntc[c[x]]++, flag[{c[x], c[y]}] = 1;
    }
    if (!flag[{c[y], c[x]}]) {
        cntc[c[y]]++, flag[{c[y], c[x]}] = 1;
    }
}
sort(s + 1, s + 1 + cnts);
for (int i = 1; i <= cnts; i++) {
    if (cntc[s[i]] > maxn) {
        maxn = cntc[s[i]], ans = s[i];
    }
}
```
- **作者：chu_K (4星)**
    - **关键亮点**：以 `set` 为切入点，详细介绍 `set` 的性质及操作，代码简洁易懂。
    - **重点代码核心思想**：利用 `set` 自动去重的特性，将不同颜色的相邻顶点插入对应的 `set` 中，最后遍历找出元素最多的 `set` 对应的颜色。
    - **核心代码片段**：
```cpp
for (int i=1; i<=m; i++)
{
    cin >> u >> v;
    if (a[u]!=a[v]) e[a[u]].insert(a[v]),e[a[v]].insert(a[u]);
}
for (int i=1; i<=n; i++)
    if (e[a[i]].size()>e[ans].size())
        ans=a[i];
```

### 最优关键思路或技巧
使用 `set` 或 `map` 数据结构来解决去重问题是关键技巧。`set` 利用其自动去重特性，简洁高效；`map` 则通过记录状态避免重复计算，二者都能有效解决本题中对相邻颜色去重统计的难点。

### 同类型题或类似算法套路拓展
此类题目通常围绕图的顶点属性（如颜色）进行统计分析，类似套路是利用合适的数据结构（如 `set`、`map`）对数据进行去重和统计。在处理图相关问题时，若涉及顶点属性的计数与去重，可考虑此类方法。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)

---
处理用时：58.01秒