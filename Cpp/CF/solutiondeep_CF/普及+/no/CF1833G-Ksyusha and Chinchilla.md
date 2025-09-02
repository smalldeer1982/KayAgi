# 题目信息

# Ksyusha and Chinchilla

## 题目描述

在一棵树上删去一些边，使得形成的几个连通块，都**有且仅有** $3$ 个结点。

## 样例 #1

### 输入

```
4
9
1 2
4 3
7 9
5 4
4 6
3 2
8 7
1 7
6
1 2
1 3
4 3
1 5
6 1
6
1 2
3 2
3 4
4 5
6 5
5
1 3
5 3
5 2
3 4```

### 输出

```
2
2 8 
-1
1
3 
-1```

## 样例 #2

### 输入

```
4
2
1 2
3
1 2
3 1
6
1 2
3 1
3 4
3 5
6 1
9
2 6
6 9
9 1
9 7
1 8
7 3
8 5
4 7```

### 输出

```
-1
0

1
2 
2
4 3```

# AI分析结果

### 题目内容
在一棵树上删去一些边，使得形成的几个连通块，都**有且仅有** $3$ 个结点。

### 样例 #1

#### 输入

```
4
9
1 2
4 3
7 9
5 4
4 6
3 2
8 7
1 7
6
1 2
1 3
4 3
1 5
6 1
6
1 2
3 2
3 4
4 5
6 5
5
1 3
5 3
5 2
3 4
```

#### 输出

```
2
2 8 
-1
1
3 
-1
```

### 样例 #2

#### 输入

```
4
2
1 2
3
1 2
3 1
6
1 2
3 1
3 4
3 5
6 1
9
2 6
6 9
9 1
9 7
1 8
7 3
8 5
4 7
```

#### 输出

```
-1
0

1
2 
2
4 3
```

### 算法分类
深度优先搜索 DFS

### 题解综合分析
该题的核心思路是通过深度优先搜索（DFS）遍历树，计算每个子树的大小，并根据子树的大小决定是否删除与父节点的边。如果子树的大小恰好为3，则删除该边，否则继续递归处理。如果子树的大小大于3，则无法形成合法的连通块，直接输出无解。

### 精选题解

#### 题解1：Iniaugoty (5星)
**关键亮点**：
- 使用链式前向星存储树结构，节省空间。
- 通过DFS计算子树大小，并根据子树大小决定是否删除边。
- 代码清晰，逻辑严谨，处理多组数据时清空操作高效。

**核心代码**：
```cpp
void dfs(int step,int father){
    if(!ans) return;
    int f=0;
    for(int i=head[step];i;i=e[i].next)
        if(e[i].to==father) f=e[i].id;
        else dfs(e[i].to,step),size[step]+=size[e[i].to];
    size[step]++;
    if(size[step]==3) size[step]=0,cut[f]=1;
    else if(size[step]>3) ans=0;
}
```

#### 题解2：Coffee_zzz (4星)
**关键亮点**：
- 使用树形DP的思想，递归计算子树大小。
- 通过标记变量判断是否有解，避免不必要的计算。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
bool init(int u,int f){
    int v,e;
    siz[u]=1;
    for(int i=head[u];i;i=edge[i].nxt){
        v=edge[i].to;
        if(v==f){
            e=i;
            continue;
        }
        init(v,u);
        siz[u]=siz[u]+siz[v];
    }
    if(f==0) return 1;
    if(siz[u]==3){
        siz[u]=0;
        ans[++pos]=edge[e].id;
    }
    else if(siz[u]>3){
        return 0;
    }
    return 1;
}
```

#### 题解3：Zhangikun (4星)
**关键亮点**：
- 通过DFS预处理子树大小，再进行二次DFS删除边。
- 使用vector存储删除的边，方便输出。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
void dfs2(int cur,int fa){
    for(auto p:nbr[cur]){
        int nxt=p.first,id=p.second;
        if(nxt==fa)continue;
        if(hd[nxt]==3){
            erz_nbr.push_back(id);
            hd[cur]-=3;
            init+=3;
            continue;
        }
        hd[cur]-=hd[nxt];
        dfs2(nxt,cur);
        if(hd[nxt]==3){
            erz_nbr.push_back(id);
            init+=3;
            continue;
        }
        hd[cur]+=hd[nxt];
    }
}
```

### 最优关键思路
1. **DFS遍历**：通过DFS计算每个子树的大小，并根据子树大小决定是否删除边。
2. **子树大小判断**：当子树大小为3时，删除与父节点的边，并将子树大小置为0；当子树大小大于3时，直接判定无解。
3. **多组数据清空**：在处理多组数据时，确保每次清空相关数组和变量，避免数据污染。

### 拓展思路
类似的问题可以通过树形DP或DFS解决，关键在于如何通过子树的大小来判断是否进行删除操作。类似题目包括树的划分、子树统计等。

### 推荐题目
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
2. [P2014 选课](https://www.luogu.com.cn/problem/P2014)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

### 个人心得
在处理树形问题时，DFS是一个非常强大的工具，尤其是在需要计算子树大小或进行子树划分时。通过递归的方式，可以清晰地表达出问题的逻辑结构，并且代码实现也相对简洁。

---
处理用时：47.54秒