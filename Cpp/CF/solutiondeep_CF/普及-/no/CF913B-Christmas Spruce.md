# 题目信息

# Christmas Spruce

## 题目描述

Consider a rooted tree. A rooted tree has one special vertex called the root. All edges are directed from the root. Vertex $ u $ is called a child of vertex $ v $ and vertex $ v $ is called a parent of vertex $ u $ if there exists a directed edge from $ v $ to $ u $ . A vertex is called a leaf if it doesn't have children and has a parent.

Let's call a rooted tree a spruce if its every non-leaf vertex has at least $ 3 $ leaf children. You are given a rooted tree, check whether it's a spruce.

The definition of a rooted tree can be found [here](https://goo.gl/1dqvzz).

## 说明/提示

The first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/3d87b6a6cda0ba6f4ad05908fb42ae8248c8369b.png)

The second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/bd0b03933e2dbb274b2b58b0c7a13d930c39c80b.png)

It is not a spruce, because the non-leaf vertex $ 1 $ has only $ 2 $ leaf children.

The third example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/a9d72240b2a5e338c43541d320aabfb5ee526dff.png)

## 样例 #1

### 输入

```
4
1
1
1
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
7
1
1
1
2
2
2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
8
1
1
1
1
3
3
3
```

### 输出

```
Yes
```

# AI分析结果

### 题目翻译
# 圣诞云杉

## 题目描述
考虑一棵有根树。有根树有一个特殊的顶点，称为根。所有的边都从根出发指向其他顶点。如果存在一条从顶点 $v$ 到顶点 $u$ 的有向边，则称顶点 $u$ 是顶点 $v$ 的子节点，顶点 $v$ 是顶点 $u$ 的父节点。如果一个顶点没有子节点但有父节点，则称该顶点为叶子节点。

如果一棵有根树的每个非叶子节点至少有 3 个叶子节点作为子节点，我们就称这棵有根树为云杉。给定一棵有根树，请判断它是否为云杉。

有根树的定义可以在[这里](https://goo.gl/1dqvzz)找到。

## 说明/提示
第一个样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/3d87b6a6cda0ba6f4ad05908fb42ae8248c8369b.png)

第二个样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/bd0b03933e2dbb274b2b58b0c7a13d930c39c80b.png)

这不是一棵云杉，因为非叶子节点 1 只有 2 个叶子节点作为子节点。

第三个样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/a9d72240b2a5e338c43541d320aabfb5ee526dff.png)

## 样例 #1
### 输入
```
4
1
1
1
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
7
1
1
1
2
2
2
```
### 输出
```
No
```

## 样例 #3
### 输入
```
8
1
1
1
1
3
3
3
```
### 输出
```
Yes
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是判断给定的有根树中每个非叶子节点是否至少有 3 个叶子节点作为子节点。不同题解在数据结构的选择和实现方式上有所不同，如使用邻接表、结构体、二维数组等存储树的结构，通过递归、枚举等方式遍历节点进行判断。

### 题解评分与分析
- **吴思诚**：4星。关键亮点是使用深度优先搜索（DFS）遍历树，思路清晰，代码简洁。在DFS过程中，统计每个非叶子节点的叶子节点个数，若不满足条件则直接输出 "No" 并结束程序。
- **nalemy**：3星。使用邻接表存储树，通过标记叶子节点，再遍历每个节点检查其叶子节点个数是否满足条件。
- **wenkaijie**：3星。将节点信息存储在结构体中，通过循环判断每个节点是否至少有 3 个子叶节点。

### 重点代码
#### 吴思诚的题解
```cpp
void dfs(int x){
    int len=g[x].size();
    int cnt=0;
    if(!len)
        return;
    for(int i=0;i<len;i++){
        int v=g[x][i];
        if(g[v].size())
            cnt++;
    }
    if(len-cnt<3){
        cout<<"No";
        exit(0);
    }
    for(int i=0;i<len;i++){
        int v=g[x][i];
        dfs(v);
    }
}
```
核心实现思想：使用 DFS 遍历树，对于每个非叶子节点，统计其非叶子节点的个数，用总子节点数减去非叶子节点数得到叶子节点数，若叶子节点数小于 3 则输出 "No" 并结束程序。

#### nalemy 的题解
```cpp
bool inline check_node(int u) {
    int cnt = 0;
    for (int i=0, sz=g[u].size(); i<sz; i++) {
        if (lf[g[u][i]]) cnt++;
        if (cnt == 3) return true;
    }
    return false;
}
bool inline check_tree() {
    for (int u=0; u<n; u++)
        if (!lf[u] && !check_node(u))
            return false;
    return true;
}
```
核心实现思想：先标记每个节点是否为叶子节点，然后通过 `check_node` 函数检查每个非叶子节点的叶子节点个数是否至少为 3，最后通过 `check_tree` 函数遍历所有节点判断整棵树是否满足条件。

#### wenkaijie 的题解
```cpp
bool three_leaves(int xx)//判断函数
{
    node x=tree[xx];
    if(x.numk==0)
        return 1;//叶节点不用判断
    if(x.numk<3)//如果子节点个数<3，就直接废了
        return 0;
    int cnt=0;//cnt用来记录子叶节点的个数
    for(int i=1;i<=x.numk;i++)
        if(tree[x.kid[i]].numk==0)
            cnt++;
    return cnt>=3;//返回cnt是否>3
}
```
核心实现思想：定义 `three_leaves` 函数判断每个节点是否至少有 3 个子叶节点，对于叶子节点直接返回 true，对于子节点个数小于 3 的节点直接返回 false，否则统计子叶节点个数并判断是否满足条件。

### 最优关键思路或技巧
- 可以使用邻接表（如 `vector`）存储树的结构，方便遍历节点的子节点。
- 在遍历过程中，及时判断是否满足条件，若不满足则提前结束程序，避免不必要的计算。

### 可拓展之处
同类型题或类似算法套路：判断树的其他性质，如树的高度、节点的度等。可以使用类似的思路，先存储树的结构，再通过遍历节点进行判断。

### 推荐题目
- [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

### 个人心得
- **zythonc**：介绍了非法逻辑强制中断算法（剪枝），在得到冗余数据时及时暂停循环线程，防止 TLE 的情况发生。如在判断节点的孩子个数小于 3 时，直接输出 "No" 结束程序。 

---
处理用时：46.22秒