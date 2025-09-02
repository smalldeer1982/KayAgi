# 题目信息

# Pashmak and Graph

## 题目描述

Pashmak's homework is a problem about graphs. Although he always tries to do his homework completely, he can't solve this problem. As you know, he's really weak at graph theory; so try to help him in solving the problem.

You are given a weighted directed graph with $ n $ vertices and $ m $ edges. You need to find a path (perhaps, non-simple) with maximum number of edges, such that the weights of the edges increase along the path. In other words, each edge of the path must have strictly greater weight than the previous edge in the path.

Help Pashmak, print the number of edges in the required path.

## 说明/提示

In the first sample the maximum trail can be any of this trails: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/46950f7ebb1a8fb1042610e7d90ce693216dd148.png).

In the second sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/0a8ef1a8d44f73ed1581f13e754f7328cc98bdea.png).

In the third sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/077a752077571978dd842d2ca5ed7e4dcecd7b85.png).

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 2
3 1 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4
```

### 输出

```
6
```

# AI分析结果

### 题目中文重写
#### Pashmak与图

#### 题目描述
Pashmak的作业是一道关于图的问题。尽管他总是努力完成作业，但他无法解决这个问题。众所周知，他在图论方面非常薄弱，所以请尝试帮助他解决这个问题。

给定一个包含 $n$ 个顶点和 $m$ 条边的加权有向图。你需要找到一条（可能是非简单的）边数最多的路径，使得路径上的边的权值严格递增。换句话说，路径中的每条边的权值必须严格大于路径中前一条边的权值。

请帮助Pashmak，输出所需路径的边数。

#### 说明/提示
在第一个样例中，最长路径可以是以下任意一条：[此处为第一个样例路径的图片链接]。
在第二个样例中，最长路径是：[此处为第二个样例路径的图片链接]。
在第三个样例中，最长路径是：[此处为第三个样例路径的图片链接]。

#### 样例 #1
##### 输入
```
3 3
1 2 1
2 3 1
3 1 1
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
3 3
1 2 1
2 3 2
3 1 3
```
##### 输出
```
3
```

#### 样例 #3
##### 输入
```
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4
```
##### 输出
```
6
```

### 题解综合分析与结论
#### 思路对比
这些题解的核心思路都是将问题转化为动态规划问题，通过对边按权值排序来消除后效性。不同题解的主要差异在于处理相同权值边的方式。
- 大部分题解（如Star_Cried、BriMon等）使用临时数组存储相同权值边的转移结果，避免相互影响。
- xy0313的题解则强调在相同边中按起点答案大的优先遍历，并考虑用更新前的起点更新终点。
- violetctl39的题解从大到小排序边权，通过标记避免相同边权的重复更新。

#### 算法要点
- **排序**：对所有边按权值排序，确保转移时边权递增。
- **状态定义**：通常定义 $f[i]$ 表示以点 $i$ 为结尾的最长路径长度。
- **状态转移**：对于边 $(u, v, w)$，更新 $f[v] = \max(f[v], f[u] + 1)$。
- **处理相同权值边**：使用临时数组或队列存储相同权值边的转移结果，避免相互影响。

#### 解决难点
本题的主要难点在于处理相同权值的边，以保证边权严格递增。不同题解采用了不同的方法：
- **临时数组**：如Star_Cried、BriMon等题解，使用临时数组 $g$ 存储相同权值边的转移结果，最后再合并到 $f$ 数组中。
- **优先遍历**：xy0313的题解按起点答案大的优先遍历相同边权的边，避免小答案更新后被大答案重新更新。
- **标记**：violetctl39的题解通过标记 $vis$ 记录当前点是否已经被边权为 $w$ 的边更新过，避免重复更新。

### 高评分题解
- **Star_Cried（5星）**
    - **关键亮点**：思路清晰，代码简洁，核心代码仅15行，详细解释了DP的思路和处理相同权值边的方法。
    - **核心代码**：
```cpp
for(int i=1,j;i<=m;i=j+1){
    j=i;
    while(e[j+1].val==e[i].val)j++;
    for(int k=i;k<=j;k++) g[e[k].u]=f[e[k].u],g[e[k].v]=f[e[k].v];
    for(int k=i;k<=j;k++) f[e[k].v]=max(f[e[k].v],g[e[k].u]+1);
} 
```
    - **核心实现思想**：先将相同权值的边分组，然后用临时数组 $g$ 记录当前权值边的起点和终点的DP值，最后更新终点的DP值。

- **BriMon（4星）**
    - **关键亮点**：详细解释了将图上问题转化为直线上问题的思路，使用栈维护更新过的点，降低时间复杂度。
    - **核心代码**：
```cpp
for (reg int i = 1 ; i <= m ; i ++)
{
    int j = i + 1;
    while(ed[i].val == ed[j].val) j ++;
    for (reg int k = i ; k < j ; k ++)
    {
        g[ed[k].y] = max(g[ed[k].y], f[ed[k].x] + 1);
        stack[++top] = ed[k].y;
    }
    while(top)
    {
        f[stack[top]] = max(f[stack[top]], g[stack[top]]);
        g[stack[top]] = 0;
        top--;
    }
    i = j - 1;
}
```
    - **核心实现思想**：同样先将相同权值的边分组，用临时数组 $g$ 记录转移结果，使用栈维护更新过的点，最后将临时数组的值合并到 $f$ 数组中。

- **YellowBean_Elsa（4星）**
    - **关键亮点**：清晰阐述了从序列上最长上升子序列方法迁移到本题的思路，使用临时数组和记录数组处理相同权值边。
    - **核心代码**：
```cpp
fu(i,1,m){
    int j=i-1;
    while(e[++j].w==e[i].w){ 
        used[++cnt]=e[j].y;
        g[e[j].y]=Max(g[e[j].y],f[e[j].x]+1);
    }
    while(cnt){
        f[used[cnt]]=Max(g[used[cnt]],f[used[cnt]]);
        g[used[cnt]]=0;cnt--;
    }
    i=j-1;
}
```
    - **核心实现思想**：枚举相同权值的边，用临时数组 $g$ 记录转移结果，用 $used$ 数组记录更新过的点，最后将临时数组的值合并到 $f$ 数组中。

### 最优关键思路或技巧
- **排序消除后效性**：对边按权值排序，使得转移时边权递增，保证了动态规划的无后效性。
- **临时数组处理相同权值边**：使用临时数组存储相同权值边的转移结果，避免相互影响，确保边权严格递增。

### 拓展思路
本题的思路可以拓展到其他需要处理严格递增或递减条件的图论问题，例如在有向图中寻找最长严格递减路径等。在处理类似问题时，可以考虑对边或节点进行排序，然后使用动态规划解决。

### 推荐题目
- [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：考察最长上升子序列和最长不上升子序列的应用。
- [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：区间动态规划问题，需要处理环形结构。
- [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)：经典的动态规划问题，通过状态转移方程求解字符串的编辑距离。

### 个人心得摘录与总结
- **xy0313**：意识到仅按边权排序无法得到正确结果，通过分析具体例子发现需要在相同边中按起点答案大的优先遍历，并考虑用更新前的起点更新终点。
- **_JF_**：在处理环的问题时，发现不能进行缩点，通过换一种思考方式，按边权从小到大更新解决了边权限制问题。这些心得提醒我们在解题时要仔细分析特殊情况，灵活运用不同的思路和方法。 

---
处理用时：47.10秒