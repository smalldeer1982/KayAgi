# 题目信息

# Peaceful Rooks

## 题目描述

You are given a $ n \times n $ chessboard. Rows and columns of the board are numbered from $ 1 $ to $ n $ . Cell $ (x, y) $ lies on the intersection of column number $ x $ and row number $ y $ .

Rook is a chess piece, that can in one turn move any number of cells vertically or horizontally. There are $ m $ rooks ( $ m < n $ ) placed on the chessboard in such a way that no pair of rooks attack each other. I.e. there are no pair of rooks that share a row or a column.

In one turn you can move one of the rooks any number of cells vertically or horizontally. Additionally, it shouldn't be attacked by any other rook after movement. What is the minimum number of moves required to place all the rooks on the main diagonal?

The main diagonal of the chessboard is all the cells $ (i, i) $ , where $ 1 \le i \le n $ .

## 说明/提示

Possible moves for the first three test cases:

1. $ (2, 3) \to (2, 2) $
2. $ (2, 1) \to (2, 3) $ , $ (1, 2) \to (1, 1) $ , $ (2, 3) \to (2, 2) $
3. $ (2, 3) \to (2, 4) $ , $ (2, 4) \to (4, 4) $ , $ (3, 1) \to (3, 3) $ , $ (1, 2) \to (1, 1) $

## 样例 #1

### 输入

```
4
3 1
2 3
3 2
2 1
1 2
5 3
2 3
3 1
1 2
5 4
4 5
5 1
2 2
3 3```

### 输出

```
1
3
4
2```

# AI分析结果

### 题目内容重写
#### Peaceful Rooks

**题目描述**

给定一个 $ n \times n $ 的棋盘，棋盘的行和列编号从 $ 1 $ 到 $ n $。单元格 $ (x, y) $ 位于第 $ x $ 列和第 $ y $ 行的交叉处。

车是国际象棋中的一种棋子，可以在一步中垂直或水平移动任意数量的单元格。棋盘上有 $ m $ 个车（$ m < n $），它们被放置在棋盘上，且没有任何一对车互相攻击。即，没有任何一对车共享同一行或同一列。

在一步中，你可以将一个车垂直或水平移动任意数量的单元格。此外，移动后该车不能被任何其他车攻击。问最少需要多少步才能将所有车移动到主对角线上？

棋盘的主对角线是指所有单元格 $ (i, i) $，其中 $ 1 \le i \le n $。

**说明/提示**

前三个测试用例的可能移动方式：

1. $ (2, 3) \to (2, 2) $
2. $ (2, 1) \to (2, 3) $, $ (1, 2) \to (1, 1) $, $ (2, 3) \to (2, 2) $
3. $ (2, 3) \to (2, 4) $, $ (2, 4) \to (4, 4) $, $ (3, 1) \to (3, 3) $, $ (1, 2) \to (1, 1) $

**样例 #1**

**输入**

```
4
3 1
2 3
3 2
2 1
1 2
5 3
2 3
3 1
1 2
5 4
4 5
5 1
2 2
3 3
```

**输出**

```
1
3
4
2
```

### 算法分类
并查集

### 综合分析与结论
本题的核心在于如何通过最少步数将所有车移动到主对角线上，且移动过程中不能互相攻击。题解中主要使用了并查集来处理车的位置冲突问题，尤其是当车的位置形成环时，需要额外的移动步数来打破环。

### 所选高星题解

#### 题解1：MC小萌新 (4星)
**关键亮点**：
- 使用并查集检测环，通过环的数量来增加移动步数。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
int find(int x){
    if(x==fa[x])
        return x;
    return fa[x]=find(fa[x]);
}
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m;
        ans=m;
        for(int i=1;i<=n;++i)
            fa[i]=i;
        for(int i=1;i<=m;++i){
            cin>>x>>y;
            if(x==y){
                --ans;
                continue;
            }
            if(find(x)==find(y))
                ++ans;
            else
                fa[x]=y;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心思想**：
- 使用并查集来检测车的位置是否形成环，如果形成环则需要额外移动步数。
- 通过并查集的 `find` 和 `union` 操作来维护车的位置关系。

#### 题解2：滑稽的小宫 (4星)
**关键亮点**：
- 详细解释了如何通过图论中的环和链来处理车的位置冲突。
- 提供了详细的模拟和证明，确保算法的正确性和最优性。

**核心代码**：
```cpp
void dfs(int x){
    dfn[x]=low[x]=++s;
    st[top++]=x;
    inst[x]=1;
    for(int i=hd[x];i;i=nxt[i]){
        int nex=to[i];
        if(!vis[nex])continue;
        if(!dfn[nex]){
            dfs(nex);
            low[x]=std::min(low[x],low[nex]);
        }else if(inst[nex])low[x]=std::min(low[x],dfn[nex]);
    }if(low[x]==dfn[x]){
        int cnt=0;
        do{
            cnt++;
            inst[st[top-1]]=0;
        }while(st[--top]!=x);
        if(cnt<=1)ans+=1;
        else ans+=cnt+1;
    }return;
}
```
**核心思想**：
- 使用 Tarjan 算法来检测强连通分量（环），并根据环的大小来增加移动步数。
- 通过 DFS 来遍历图，检测环并计算需要的移动步数。

### 最优关键思路或技巧
- **并查集**：用于检测车的位置是否形成环，从而决定是否需要额外移动步数。
- **图论中的环和链**：通过图论中的环和链来处理车的位置冲突，确保移动的最优性。

### 可拓展之处
- 类似的问题可以扩展到其他棋子的移动，如象、皇后等，处理它们的移动冲突。
- 可以进一步优化并查集的实现，减少时间复杂度。

### 推荐题目
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
2. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
3. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

---
处理用时：37.46秒