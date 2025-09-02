# 题目信息

# Searching for Graph

## 题目描述

Let's call an undirected graph of $ n $ vertices  $ p $ -interesting, if the following conditions fulfill:

- the graph contains exactly $ 2n+p $ edges;
- the graph doesn't contain self-loops and multiple edges;
- for any integer $ k $ ( $ 1<=k<=n $ ), any subgraph consisting of $ k $ vertices contains at most $ 2k+p $ edges.

A subgraph of a graph is some set of the graph vertices and some set of the graph edges. At that, the set of edges must meet the condition: both ends of each edge from the set must belong to the chosen set of vertices.

Your task is to find a  $ p $ -interesting graph consisting of $ n $ vertices.

## 样例 #1

### 输入

```
1
6 0
```

### 输出

```
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
```

# AI分析结果

### 题目内容翻译
# 寻找图

## 题目描述
我们称一个具有 $n$ 个顶点的无向图为 $p$ -有趣图，如果满足以下条件：
- 该图恰好包含 $2n + p$ 条边；
- 该图不包含自环和重边；
- 对于任意整数 $k$（$1 \leq k \leq n$），任意由 $k$ 个顶点组成的子图最多包含 $2k + p$ 条边。

图的子图是图的顶点的某个集合和图的边的某个集合。此外，边的集合必须满足条件：集合中每条边的两个端点都必须属于所选的顶点集合。

你的任务是找到一个由 $n$ 个顶点组成的 $p$ -有趣图。

## 样例 #1
### 输入
```
1
6 0
```
### 输出
```
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
```

### 算法分类
构造

### 综合分析与结论
- **思路对比**：
    - 流绪的思路是直接从小枚举点，让当前点和它后面的点全连起来，输出 $2n + p$ 次边。
    - CH30S 的思路与流绪类似，也是枚举输出 $i$ 和 $j$，直到输出 $2n + p$ 组边。
    - oimaster 的思路是先建一棵树保证图连通（让除根节点外的所有点都与根节点相连），然后再连接剩下未连接的点，直到边数达到 $2n + p$ 条。
- **算法要点**：
    - 流绪通过简单的双指针（$x$ 和 $y$）来枚举边。
    - CH30S 只是描述了枚举的思路，未给出具体实现。
    - oimaster 使用邻接表来记录边的连接情况，通过双重循环枚举边。
- **解决难点**：
    - 都需要解决如何在不产生自环和重边的情况下构造出满足边数要求的图。流绪通过保证 $y > x$ 来避免重边；oimaster 通过邻接表标记和跳过 $i == j$ 的情况来避免自环和重边。

### 题解评分
- 流绪：3星。思路较清晰，代码简单易懂，但解释稍显随意。
- CH30S：2星。只描述了思路，未给出代码，缺乏实际参考价值。
- oimaster：3星。思路明确，代码实现完整，但邻接表的使用增加了空间复杂度。

由于所有题解均不足4星，以下给出通用建议与扩展思路：
- **通用建议**：在构造图时，要明确边的生成规则，避免自环和重边。可以先从简单的连接方式入手，如按顺序连接顶点，再根据边数要求进行调整。
- **扩展思路**：对于类似的图构造问题，可以先考虑一些特殊的图结构，如树、完全图等，然后在此基础上进行修改和调整。同时，要注意题目中的各种限制条件，如边数、顶点数、子图的性质等。

### 重点代码及核心实现思想
#### 流绪的代码
```cpp
int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        int n,p;
        cin >> n >> p;
        int x=1,y=2; // 设有一条从1到2的边
        for(int i=1;i<=2*n+p;i++)
        {
            cout << x << " " << y << endl;
            y++;
            if(y == n+1)
                x++,y=x+1; // 没有重边,所以让y>x恒成立
        }
    }
    return 0;
} 
```
**核心实现思想**：使用两个变量 $x$ 和 $y$ 来枚举边，$y$ 从 $x + 1$ 开始递增，当 $y$ 达到 $n + 1$ 时，$x$ 加1，$y$ 重新从 $x + 1$ 开始，直到输出 $2n + p$ 条边。

#### oimaster 的代码
```cpp
void solve(){
    int n,p;
    cin>>n>>p;
    int edge=n*2+p;
    int a[n+1][n+1];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            a[i][j]=0;
    for(int i=2;i<=n;++i){
        a[1][i]=a[i][1]=1;
        cout<<1<<' '<<i<<endl;
        --edge;
    }
    for(int i=2;i<=n;++i)
        for(int j=1;j<=n;++j){
            if(j==i)
                continue;
            if(a[i][j]==0){
                a[i][j]=a[j][i]=1;
                --edge;
                cout<<i<<' '<<j<<endl;
                if(edge==0)
                    return;
            }
        }
}
```
**核心实现思想**：先建一棵树，让除根节点1外的所有点都与1相连，然后使用邻接表 $a$ 来记录边的连接情况，通过双重循环枚举未连接的边，直到边数达到 $2n + p$ 条。

### 洛谷相关题目推荐
- P1341 无序字母对：构造欧拉路径。
- P2731 [USACO3.3]骑马修栅栏 Riding the Fences：构造欧拉回路。
- P1127 词链：构造有向图的欧拉路径。

### 个人心得摘录与总结
- 流绪：作者表示看到题目时很惊讶，觉得第三个条件没什么用，尝试从小枚举点并连接的方法，发现符合要求就通过了，体现了在解题时可以大胆尝试简单思路。

---
处理用时：34.95秒