# 题目信息

# [USACO5.3] 校园网Network of Schools

## 题目描述

一些学校连入一个电脑网络。那些学校已订立了协议：每个学校都会给其它的一些学校分发软件（称作“接受学校”）。注意即使 $B$ 在 $A$ 学校的分发列表中，$A$ 也不一定在 $B$ 学校的列表中。

你要写一个程序计算，根据协议，为了让网络中所有的学校都用上新软件，必须接受新软件副本的最少学校数目（子任务 A）。更进一步，我们想要确定通过给任意一个学校发送新软件，这个软件就会分发到网络中的所有学校。为了完成这个任务，我们可能必须扩展接收学校列表，使其加入新成员。计算最少需要增加几个扩展，使得不论我们给哪个学校发送新软件，它都会到达其余所有的学校（子任务 B）。一个扩展就是在一个学校的接收学校列表中引入一个新成员。

## 说明/提示

$2 \le N \le 100$。

题目翻译来自NOCOW。

USACO Training Section 5.3


## 样例 #1

### 输入

```
5
2 4 3 0
4 5 0
0
0
1 0```

### 输出

```
1
2```

# AI分析结果

### 综合分析与结论
这些题解大多围绕缩点的思路来解决问题，核心是将强连通分量缩成一个点，把图转化为有向无环图（DAG），再统计入度和出度为 0 的点的数量来求解两个子任务。对于子任务 A，答案是缩点后入度为 0 的点的个数；对于子任务 B，答案是入度为 0 的点和出度为 0 的点的个数的最大值，同时要注意特判整个图本身就是强连通分量的情况。大部分题解使用 Tarjan 算法进行缩点，也有少数使用 Floyd 算法求传递闭包来缩点。

### 所选题解
- **作者：_Lemon_（4星）**
  - **关键亮点**：思路清晰，代码结构规范，详细注释了每个步骤，对 Tarjan 算法的实现和缩点过程解释得很清楚，便于理解。
  - **核心代码**：
```cpp
void tarjian(int x)//常规缩点
{
    sum++;
    tim[x]=low[x]=sum;
    sta[top]=x;
    top++;
    ins[x]=1;
    for(int w=head[x];w!=0;w=e[w].next)
    {
         if(ins[e[w].to]==0)
          {
                tarjian(e[w].to);
                low[x]=min(low[x],low[e[w].to]);
          }
         else if(ins[e[w].to]==1)
                low[x]=min(low[x],tim[e[w].to]);
    }
    if(tim[x]==low[x])
    {
        col++;
        do
        {
            top--;
            color[sta[top]]=col;
            ins[sta[top]]=-1;
        }while(sta[top]!=x);
    }
    return ;
}
```
  - **核心实现思想**：Tarjan 算法的标准实现，通过 `tim` 数组记录节点的时间戳，`low` 数组记录节点能追溯到的最早时间戳，利用栈来维护强连通分量，当 `tim[x] == low[x]` 时，说明找到了一个强连通分量，将栈中元素出栈并染色。

- **作者：crh1272336175（4星）**
  - **关键亮点**：不仅给出了完整的代码，还对问题进行了详细的分析和证明，逻辑严谨，对第二问的结论证明很有参考价值。
  - **核心代码**：
```cpp
void tarjan(int x)
{
    low[x]=dfn[x]=++num;
    stk.push(x); ins[x]=1;
    for(int i=head[x]; i; i=Next[i])
    {
        int y=des[i];
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        } 
        else if(ins[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x])
    {
        int y; cnt++;
        do
        {
            y=stk.top(); stk.pop(); ins[y]=0;
            c[y]=cnt; scc[cnt].push_back(y);
        }while(y!=x);
    }
}
```
  - **核心实现思想**：同样是 Tarjan 算法的实现，使用 `dfn` 数组记录节点的时间戳，`low` 数组记录节点能追溯到的最早时间戳，栈 `stk` 用于维护强连通分量，当 `dfn[x] == low[x]` 时，将栈中元素出栈并记录到对应的强连通分量中。

- **作者：多多良假伞（4星）**
  - **关键亮点**：思路清晰，对问题的分析和代码实现都有详细的注释，对 Tarjan 算法的解释和缩点后统计入度出度的过程很清晰。
  - **核心代码**：
```cpp
void tarjan(int now){//个人感觉是比较正常的tarjan写法
    dfn[now]=low[now]=++ti;
    sa.push(now);vis[now]=true;
    for(int i=head[now];i;i=edge[i].next){
        int j=edge[i].to;
        if(!dfn[j]) tarjan(j),low[now]=min(low[now],low[j]);
        else if(vis[j]) low[now]=min(low[now],dfn[j]);
    }
    if(dfn[now]==low[now]){
        ++clnum;
        while(now!=sa.top()){
            int t=sa.top();
            sa.pop();vis[t]=false;
            color[t]=clnum;++sum[clnum];
        }
        sa.pop();vis[now]=false;
        color[now]=clnum;++sum[clnum];//染色(求强连通分量)
    }
}
```
  - **核心实现思想**：Tarjan 算法的实现，使用 `dfn` 数组记录节点的时间戳，`low` 数组记录节点能追溯到的最早时间戳，栈 `sa` 用于维护强连通分量，当 `dfn[now] == low[now]` 时，将栈中元素出栈并染色，统计强连通分量的大小。

### 最优关键思路或技巧
- **缩点思想**：将强连通分量缩成一个点，把图转化为 DAG，简化问题的处理。
- **Tarjan 算法**：高效地找出图中的强连通分量，时间复杂度为 $O(n + m)$。
- **特判处理**：注意整个图本身就是强连通分量的情况，此时子任务 B 的答案为 0。

### 可拓展之处
同类型题或类似算法套路：
- **有向图的连通性问题**：如判断有向图是否强连通，求有向图的强连通分量个数等。
- **图的拓扑排序**：在 DAG 中进行拓扑排序，解决一些依赖关系的问题。
- **图的最小生成树**：在无向图中求最小生成树，如 Prim 算法、Kruskal 算法等。

### 推荐题目
- [P2341 [USACO03FALL][HAOI2006]受欢迎的牛 G](https://www.luogu.com.cn/problem/P2341)
- [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
- [P1262 间谍网络](https://www.luogu.com.cn/problem/P1262)

### 个人心得摘录与总结
- **作者：Ametsuji_akiya**：指出了大部分网络题解在证明和构造答案方法上的错误，提醒我们在解决问题时要严谨思考，不能盲目相信已有的结论。
- **作者：George1123**：提醒我们要注意特判所有点强连通的情况，避免因遗漏特殊情况而导致错误。

---
处理用时：53.03秒