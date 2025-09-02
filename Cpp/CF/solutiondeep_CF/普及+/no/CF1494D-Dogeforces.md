# 题目信息

# Dogeforces

## 题目描述

The Dogeforces company has $ k $ employees. Each employee, except for lower-level employees, has at least $ 2 $ subordinates. Lower-level employees have no subordinates. Each employee, except for the head of the company, has exactly one direct supervisor. The head of the company is a direct or indirect supervisor of all employees. It is known that in Dogeforces, each supervisor receives a salary strictly more than all his subordinates.

The full structure of the company is a secret, but you know the number of lower-level employees and for each pair of lower-level employees, the salary of their common supervisor is known (if there are several such supervisors, then the supervisor with the minimum salary). You have to restore the structure of the company.

## 说明/提示

One of the possible structures in the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1494D/b4b5e03fae4e04d10365f74dfd3682f3acad7010.png)

## 样例 #1

### 输入

```
3
2 5 7
5 1 7
7 7 4```

### 输出

```
5
2 1 4 7 5 
4
1 5
2 5
5 4
3 4```

# AI分析结果

### 题目翻译
# Dogeforces

## 题目描述
Dogeforces 公司有 $k$ 名员工。除了基层员工外，每名员工至少有 $2$ 名下属。基层员工没有下属。除公司负责人外，每名员工都只有一名直属上级。公司负责人是所有员工的直接或间接上级。已知在 Dogeforces 公司中，每名上级的工资都严格高于其所有下属。

公司的完整架构是保密的，但你知道基层员工的数量，并且对于每对基层员工，他们的共同上级（如果有多个这样的上级，则取工资最低的上级）的工资是已知的。你需要还原公司的架构。

## 说明/提示
第一个样例的一种可能架构：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1494D/b4b5e03fae4e04d10365f74dfd3682f3acad7010.png)

## 样例 #1
### 输入
```
3
2 5 7
5 1 7
7 7 4
```
### 输出
```
5
2 1 4 7 5 
4
1 5
2 5
5 4
3 4
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕根据给定的基层员工信息和他们共同上级的工资来构造公司的树状架构。思路大致可分为两类：
1. **递归分治思路**：通过找到根节点，将叶节点分类为不同子树的节点，再递归处理子树来构建整棵树。
2. **Kruskal 重构树思路**：利用 Kruskal 重构树的特性，结合对父子节点权值关系的处理来构建树。

各题解的算法要点和解决的难点如下：
- **递归分治思路**：
    - **算法要点**：先找到根节点权值（所有叶节点两两 LCA 权值中的最大值），根据叶节点与根节点的 LCA 关系将叶节点分类，递归处理同一子树的叶节点。
    - **解决难点**：如何合理地将叶节点分类到不同子树，以及递归处理子树时保证树的结构正确。
- **Kruskal 重构树思路**：
    - **算法要点**：将所有叶节点间的 LCA 权值看作边权，构建 Kruskal 重构树，同时处理父子节点权值相等的情况。
    - **解决难点**：如何处理父子节点权值相等的情况，以满足题目中父亲权值严格大于儿子权值的要求。

### 所选题解
- **kouylan（4星）**
    - **关键亮点**：思路清晰，代码可读性高，详细阐述了递归分治的过程。
- **DaiRuiChen007（4星）**
    - **关键亮点**：结合 Kruskal 重构树，对父子节点权值相等的情况进行了详细的分类讨论。
- **Rui_R（4星）**
    - **关键亮点**：对递归分治的复杂度进行了详细的分析和证明。

### 重点代码
#### kouylan 的递归分治代码
```cpp
int getroot(vector<int> leaf)
{
    if(leaf.size()==1)
    {
        c[leaf[0]] = a[leaf[0]][leaf[0]];
        return leaf[0];
    }
    int mx=0;
    for(int i=1;i<leaf.size();i++)
        mx = max(mx,a[leaf[0]][leaf[i]]);
    int root=(++m);
    c[root] = mx;
    int del[1005];
    for(int i=0;i<=leaf.size();i++)
        del[i] = 0;
    vector<int> son;
    for(int i=0;i<leaf.size();i++)
        if(!del[i])
        {
            son.clear();
            for(int j=i;j<leaf.size();j++)
                if(a[leaf[i]][leaf[j]]!=mx)
                {
                    son.push_back(leaf[j]);
                    del[j] = 1;
                }
            fa[getroot(son)] = root;
        }
    return root;
}
```
**核心实现思想**：先判断叶节点数量是否为 1，若是则直接返回该节点。否则找到根节点权值，将叶节点分类到不同子树，递归处理子树并更新父节点信息。

#### DaiRuiChen007 的 Kruskal 重构树代码
```cpp
sort(edges.begin(),edges.end());
int siz=n;
for(auto e:edges) {
    int x=find(e.u),y=find(e.v);
    if(x==y) continue;
    if(val[x]==e.w&&val[y]==e.w) {
        del[y]=true,dsu[y]=x;
        for(int i:G[y]) G[x].push_back(i);
        G[y].clear();
    } else if(val[x]==e.w) {
        dsu[y]=x;
        G[x].push_back(y);
    } else if(val[y]==e.w) {
        dsu[x]=y;
        G[y].push_back(x);
    } else {
        dsu[x]=dsu[y]=++siz;
        dsu[siz]=siz,val[siz]=e.w;
        G[siz].push_back(x),G[siz].push_back(y);
    }
}
```
**核心实现思想**：对边按权值排序，依次合并不同连通块，根据父子节点权值关系进行不同的处理。

#### Rui_R 的递归分治代码
```cpp
int Epk(std::vector<int> &v){
    if(v.size() == 1) return c[v[0]]=a[v[0]][v[0]],v[0] ;
    int Maxx = 0;
    for(int i=1;i<(int)v.size();i++) Maxx = max(Maxx,a[v[0]][v[i]]);
    int rt = ++ncnt;c[rt] = Maxx;
    std::vector<int> del;del.resize(v.size());
    std::vector<int> go ;
    for(int i=0;i<(int)v.size();i++){
        if(del[i]) continue ;
        go.clear();
        for(int j=i;j<(int)v.size();j++){
            if(a[v[i]][v[j]]!=Maxx){
                go.push_back(v[j]);
                del[j] = true;
            }
        }
        fa[Epk(go)] = rt;
    }
    return rt ;
}
```
**核心实现思想**：与 kouylan 的思路类似，通过递归处理子树来构建树结构。

### 最优关键思路或技巧
- **递归分治**：利用树的递归性质，将大问题分解为小问题，逐步构建树结构。
- **Kruskal 重构树**：将问题转化为图的最小生成树问题，利用 Kruskal 算法的特性来构建树。

### 拓展思路
同类型题或类似算法套路：
- 其他树的构造问题，如根据节点间的距离信息构造树。
- 图的重构问题，根据图的某些性质或信息还原图的结构。

### 推荐题目
- [P1196 银河英雄传说](https://www.luogu.com.cn/problem/P1196)：考察并查集的应用。
- [P1967 货车运输](https://www.luogu.com.cn/problem/P1967)：涉及 Kruskal 重构树和 LCA 的知识。
- [P2279 [HNOI2003]消防局的设立](https://www.luogu.com.cn/problem/P2279)：树的构造和贪心算法的结合。

### 个人心得
无。

---
处理用时：57.92秒