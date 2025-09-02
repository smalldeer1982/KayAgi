# 题目信息

# Substring

## 题目描述

You are given a graph with $ n $ nodes and $ m $ directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is $ 3 $ . Your task is find a path whose value is the largest.

## 说明/提示

In the first sample, the path with largest value is $ 1→3→4→5 $ . The value is $ 3 $ because the letter 'a' appears $ 3 $ times.

## 样例 #1

### 输入

```
5 4
abaca
1 2
1 3
3 4
4 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 6
xzyabc
1 2
3 1
2 3
5 4
4 3
6 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 14
xzyzyzyzqx
1 2
2 4
3 5
4 5
2 6
6 8
6 5
2 10
3 9
10 9
4 6
1 10
2 8
3 7
```

### 输出

```
4
```

# AI分析结果

### 题目中文重写
# 子串

## 题目描述
给定一个包含 $n$ 个节点和 $m$ 条有向边的图。每个节点都被赋予一个小写字母。我们将一条路径的值定义为该路径上出现频率最高的字母的数量。例如，如果一条路径上的字母是 "abaca"，那么该路径的值就是 $3$。你的任务是找到值最大的路径。

## 说明/提示
在第一个样例中，值最大的路径是 $1→3→4→5$。该路径的值为 $3$，因为字母 'a' 出现了 $3$ 次。

## 样例 #1
### 输入
```
5 4
abaca
1 2
1 3
3 4
4 5
```
### 输出
```
3
```

## 样例 #2
### 输入
```
6 6
xzyabc
1 2
3 1
2 3
5 4
4 3
6 4
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
10 14
xzyzyzyzqx
1 2
2 4
3 5
4 5
2 6
6 8
6 5
2 10
3 9
10 9
4 6
1 10
2 8
3 7
```
### 输出
```
4
```

### 综合分析与结论
这些题解的核心思路都是结合拓扑排序和动态规划（DP）来解决问题。
- **思路**：先判断图中是否有环，若有环则路径值可能无穷大，输出 -1；若无环，则利用拓扑排序的顺序进行 DP 计算，找出路径上出现频率最高的字母的最大数量。
- **算法要点**：
    - **拓扑排序**：统计入队节点数量，若小于节点总数 $n$，则图中有环。
    - **DP**：定义 $dp[i][j]$ 表示走到第 $i$ 个节点时，字母 $j$ 的最大出现次数。根据当前节点字母与枚举字母是否相同，更新 $dp$ 值。
- **解决难点**：
    - **判断环**：利用拓扑排序的特性，若存在环，环上节点入度不会减为 0，入队节点数小于 $n$。
    - **状态转移**：根据节点字母与枚举字母的关系，正确更新 $dp$ 值。

### 所选题解
- **Merron（4星）**
    - **关键亮点**：思路清晰，对拓扑排序和 DP 的讲解详细，代码注释丰富。
    - **个人心得**：提到在 `Linux Ubuntu` 下使用 `getchar()` 本地运行会 RE，而使用 `cin` 正常，希望得到大佬指教。
- **Binary_Lee（4星）**
    - **关键亮点**：思路简洁明了，通过图示解释判环过程，代码简洁。
- **ArcherHavetoLearnWhk（4星）**
    - **关键亮点**：思路清晰，对路径权值无穷大情况和 DP 过程的分析详细，使用 `auto` 简洁枚举邻点。

### 重点代码
#### Merron 的核心代码
```cpp
while(!Q.empty())
{
    int x = Q.front();
    Q.pop();
    in[x] = -1; //delete this edge 
    sum ++;// count
    for(int i = 0; i < E[x].size(); i ++)
    {
        int y = E[x][i];
        for(int j = 1; j <= 26; j ++)
        {
            if(val[y] == j)
                dp[y][j] = max(dp[y][j], dp[x][j] + 1);
            else
                dp[y][j] = max(dp[y][j], dp[x][j]);
        }
        in[y] --;
        if(!in[y])
            Q.push(y);
    }
}
```
**核心实现思想**：在拓扑排序过程中，对于当前节点 $x$ 的所有邻接节点 $y$，枚举 26 个字母，根据 $y$ 节点的字母与枚举字母是否相同，更新 $dp[y][j]$ 的值。

#### Binary_Lee 的核心代码
```cpp
while(q.size()){
    int k=q.front();
    q.pop();
    cnt++;
    for(int i=0;i<a[k].size();i++){
        int tmp=a[k][i];
        for(int j=0;j<26;j++){
            if(b[tmp]==j) f[tmp][j]=max(f[tmp][j],f[k][j]+1);
            else f[tmp][j]=max(f[tmp][j],f[k][j]);
        }
        in[tmp]--;
        if(!in[tmp]) q.push(tmp);
    }
}
```
**核心实现思想**：在拓扑排序的队列处理过程中，对于队首节点 $k$ 的邻接节点 $tmp$，枚举 26 个字母，根据 $tmp$ 节点的字母与枚举字母是否相同，更新 $f[tmp][j]$ 的值。

#### ArcherHavetoLearnWhk 的核心代码
```cpp
while(!q.empty()){//拓扑排序
    int u=q.front();
    q.pop();//取出队首的点
    tot++;//统计取出结点数
    in[u]=-114514;//入度设为负数避免再次入队
    for(auto v:e[u]){//简洁的auto和:写法枚举当前结点的邻点
        for(int j=0;j<26;j++){//dp
            if(s[v]==j)dp[v][j]=max(dp[v][j],dp[u][j]+1);
            else dp[v][j]=max(dp[v][j],dp[u][j]);//状态转移
        }
        in[v]--;//当前邻点入度减一
        if(!in[v])q.push(v);//入度为0就入队
    }
}
```
**核心实现思想**：在拓扑排序过程中，对于队首节点 $u$ 的邻接节点 $v$，枚举 26 个字母，根据 $v$ 节点的字母与枚举字母是否相同，更新 $dp[v][j]$ 的值。

### 最优关键思路或技巧
- **拓扑排序判环**：利用拓扑排序过程中入队节点数量与节点总数的关系判断图中是否有环。
- **状态定义**：使用二维数组 $dp[i][j]$ 记录走到第 $i$ 个节点时，字母 $j$ 的最大出现次数，便于状态转移。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及有向图路径问题，可先判断图中是否有环，若无环则利用拓扑排序的顺序进行动态规划。
- 对于状态转移问题，根据不同条件分类讨论，正确更新状态值。

### 推荐题目
- [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)
- [P3243 [HNOI2015]菜肴制作](https://www.luogu.com.cn/problem/P3243)
- [P2051 [AHOI2009]中国象棋](https://www.luogu.com.cn/problem/P2051)

---
处理用时：53.24秒