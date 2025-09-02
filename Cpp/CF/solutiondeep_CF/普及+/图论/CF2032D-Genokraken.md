# 题目信息

# Genokraken

## 题目描述

This is an interactive problem.

Upon clearing the Waterside Area, Gretel has found a monster named Genokraken, and she's keeping it contained for her scientific studies.

The monster's nerve system can be structured as a tree $ ^{\dagger} $ of $ n $ nodes (really, everything should stop resembling trees all the time $ \ldots $ ), numbered from $ 0 $ to $ n-1 $ , with node $ 0 $ as the root.

Gretel's objective is to learn the exact structure of the monster's nerve system — more specifically, she wants to know the values $ p_1, p_2, \ldots, p_{n-1} $ of the tree, where $ p_i $ ( $ 0 \le p_i < i $ ) is the direct parent node of node $ i $ ( $ 1 \le i \le n - 1 $ ).

She doesn't know exactly how the nodes are placed, but she knows a few convenient facts:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths $ ^{\ddagger} $ . Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- The nodes are indexed in a way that if $ 1 \le x \le y \le n - 1 $ , then $ p_x \le p_y $ .
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)The tree in this picture does not satisfy the condition, because if we remove node $ 0 $ , then node $ 2 $ (which was initially adjacent to the node $ 0 $ ) will not be the end of the path $ 4-2-5 $ .The tree in this picture does not satisfy the condition, because $ p_3 \le p_4 $ must hold.The tree in this picture does not satisfy the condition, because node $ 1 $ has only one adjacent node.Gretel can make queries to the containment cell:

- "? a b" ( $ 1 \le a, b < n $ , $ a \ne b $ ) — the cell will check if the simple path between nodes $ a $ and $ b $ contains the node $ 0 $ .

However, to avoid unexpected consequences by overstimulating the creature, Gretel wants to query at most $ 2n - 6 $ times. Though Gretel is gifted, she can't do everything all at once, so can you give her a helping hand?

 $ ^{\dagger} $ A tree is a connected graph where every pair of distinct nodes has exactly one simple path connecting them.

 $ ^{\ddagger} $ A path is a tree whose vertices can be listed in the order $ v_1, v_2, \ldots, v_k $ such that the edges are $ (v_i, v_{i+1}) $ ( $ 1 \le i < k $ ).

## 说明/提示

In the first test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .

In the second test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .
- The answer to "? 2 4" is $ 0 $ . This means that the simple path between nodes $ 2 $ and $ 4 $ doesn't contain node $ 0 $ .

In the third test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

## 样例 #1

### 输入

```
3
4

1

5

1

0

9```

### 输出

```
? 2 3

! 0 0 1

? 2 3

? 2 4

! 0 0 1 2

! 0 0 0 1 3 5 6 7```

# AI分析结果

### 题目中文重写
## Genokraken

### 题目描述
这是一道交互题。

在清理完水边区域后，格蕾特发现了一只名为Genokraken的怪物，并将它关起来进行科学研究。

怪物的神经系统可以构造成一棵有 $n$ 个节点的树（真的，所有东西都不应该总是像树一样……），节点编号从 $0$ 到 $n - 1$，以节点 $0$ 为根。

格蕾特的目标是了解怪物神经系统的确切结构 —— 更具体地说，她想知道树中 $p_1, p_2, \ldots, p_{n - 1}$ 的值，其中 $p_i$（$0 \leq p_i < i$）是节点 $i$（$1 \leq i \leq n - 1$）的直接父节点。

她并不确切知道节点的具体位置，但她知道一些有用的信息：
- 如果移除根节点 $0$ 及其所有相邻边，这棵树将变成一个仅由路径组成的森林。每个最初与节点 $0$ 相邻的节点都将是某条路径的端点。
- 节点的编号方式使得如果 $1 \leq x \leq y \leq n - 1$，那么 $p_x \leq p_y$。
- 节点 $1$ 恰好有两个相邻节点（包括节点 $0$）。

![不符合条件的树示例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)
![不符合条件的树示例2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)
![不符合条件的树示例3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)
第一幅图中的树不满足条件，因为如果移除节点 $0$，那么节点 $2$（最初与节点 $0$ 相邻）将不是路径 $4 - 2 - 5$ 的端点。
第二幅图中的树不满足条件，因为必须满足 $p_3 \leq p_4$。
第三幅图中的树不满足条件，因为节点 $1$ 只有一个相邻节点。

格蕾特可以向关押怪物的牢房进行询问：
- “? a b”（$1 \leq a, b < n$，$a \neq b$） —— 牢房将检查节点 $a$ 和 $b$ 之间的简单路径是否包含节点 $0$。

然而，为了避免过度刺激怪物而产生意外后果，格蕾特希望询问次数最多为 $2n - 6$ 次。尽管格蕾特很有天赋，但她无法一次性完成所有事情，那么你能帮她一把吗？

注：
- 树是一种连通图，其中每对不同的节点都恰好有一条简单路径相连。
- 路径是一种树，其顶点可以按 $v_1, v_2, \ldots, v_k$ 的顺序列出，使得边为 $(v_i, v_{i + 1})$（$1 \leq i < k$）。

### 说明/提示
在第一个测试用例中，Genokraken的神经系统形成了如下树：
![第一个测试用例的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)
- “? 2 3” 的答案是 $1$。这意味着节点 $2$ 和 $3$ 之间的简单路径包含节点 $0$。

在第二个测试用例中，Genokraken的神经系统形成了如下树：
![第二个测试用例的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)
- “? 2 3” 的答案是 $1$。这意味着节点 $2$ 和 $3$ 之间的简单路径包含节点 $0$。
- “? 2 4” 的答案是 $0$。这意味着节点 $2$ 和 $4$ 之间的简单路径不包含节点 $0$。

在第三个测试用例中，Genokraken的神经系统形成了如下树：
![第三个测试用例的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

### 样例 #1
#### 输入
```
3
4
1
5
1
0
9
```
#### 输出
```
? 2 3
! 0 0 1
? 2 3
? 2 4
! 0 0 1 2
! 0 0 0 1 3 5 6 7
```

### 题解综合分析与结论
这些题解的核心目标都是在不超过 $2n - 6$ 次询问的限制下，还原出树的结构。各题解的思路和方法有所不同，主要差异在于切入点和构建树的顺序。

- **思路对比**：部分题解从节点 $1$ 入手，利用其特殊性质逐步确定树的结构；而有些题解则从后往前，从节点 $n - 1$ 开始倒推每个节点的父节点。
- **算法要点**：多数题解都运用了双指针的思想，通过不断移动指针和进行询问来确定节点的父节点。同时，利用树的性质（如删除节点 $0$ 后为链、父节点编号单调不减等）来减少询问次数。
- **解决难点**：关键在于如何巧妙地利用询问结果和树的性质，在满足询问次数限制的条件下准确还原树的结构。

### 所选题解
- **elpsconr（5星）**
    - **关键亮点**：思路清晰，从后往前构建树，易于理解，且询问次数较少，最多为 $n - 2$ 次，远低于 $2n - 6$ 的限制。
    - **核心代码**：
```cpp
inline void solve(){
  cin>>n;
  rep(i,1,n-1) a[i]=0;
  int l=n-2;
  rep_(i,n-1,1){
    while(l>0&&ask(i,l)) l--;
    a[i]=max(l--,0ll);
  }
  show();
}
```
核心实现思想：从最后一个节点 $n - 1$ 开始，用指针 $l$ 从 $n - 2$ 开始倒着枚举，若节点 $i$ 和 $l$ 之间的路径包含节点 $0$，则 $l$ 减 $1$，直到不包含节点 $0$，此时 $l$ 即为 $i$ 的父节点。

- **tai_chi（4星）**
    - **关键亮点**：从节点 $1$ 入手，利用其特殊性质，分两部分确定树的结构，询问次数刚好为 $2n - 6$，满足题目要求。
    - **核心代码**：
```cpp
void solve()
{
  int n; cin>>n;
  vector<int> p(n+5,0);
  p[1]=0;
  int t=0;
  for(int i=2;i<=n-1;i++)
  {
    int r=ask(1,i);
    if(r==0){t=i; break;}
    else p[i]=0;
  }
  p[t]=1;
  int now=2;
  for(int i=t+1;i<=n-1;i++)
  {
    while(ask(now,i)==1) now++;
    p[i]=now;
    now++;
  }
  cout<<"! ";
  for(int i=1;i<=n-1;i++) cout<<p[i]<<" ";
  cout<<endl;
}
```
核心实现思想：先依次询问 $(1, 2), (1, 3), \dots, (1, t)$ 直到答案为 $0$，确定 $t$ 为 $1$ 的儿子，且 $[2, t - 1]$ 的父亲都是 $0$。之后用双指针，指针 $now$ 指向当前测试的父亲节点，确定剩余节点的父节点。

- **gyyyyx（4星）**
    - **关键亮点**：利用队列存储可能的父亲节点，结合 $p$ 数组单调不降的性质，优化询问过程，总询问次数刚好为 $2n - 6$。
    - **核心代码**：
```cpp
int main(){
  cin>>T;
  while(T--){
    cin>>n;int u(2);
    for(h=1,t=0;u<n;++u){
      q[++t]=u;
      if(Ask(1,u)){f[u]=1;break;}
      f[u]=0;
    }
    for(++u;u<n;++u){
      while(!Ask(q[h],u)) ++h;
      f[q[++t]=u]=q[h++];
      if(t==h) break;
    }
    for(++u;u<n;++u) f[u]=u-1;
    cout<<"! ";
    for(int i(1);i<n;++i) cout<<f[i]<<" ";
    cout<<endl;
  }
  return 0;
}
```
核心实现思想：先从 $u = 2$ 开始询问 `? 1 u`，找到所有直接挂在 $0$ 节点下面的节点。对于剩余节点，用队列存储可能的父亲节点，从队头开始询问，若回答为 $1$ 则删去队头节点，直到回答为 $0$ 确定父节点。

### 最优关键思路或技巧
- **逆向思维**：如elpsconr的题解，从后往前构建树，简化了问题的处理过程。
- **双指针法**：多个题解都运用了双指针，通过移动指针和询问来确定节点的父节点，有效减少了询问次数。
- **利用树的性质**：充分利用树删除节点 $0$ 后为链、父节点编号单调不减等性质，对询问结果进行分析和推理。

### 可拓展之处
同类型题可能会改变树的性质或询问方式，例如改变树的形态（如变成二叉树）、增加或减少询问的限制条件等。类似算法套路包括利用双指针、队列等数据结构，结合树的性质进行推理和判断。

### 洛谷相似题目推荐
- [P1114 “非常男女”计划](https://www.luogu.com.cn/problem/P1114)：涉及序列的性质和双指针的运用。
- [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)：使用双指针解决区间问题。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：需要利用数列的性质进行推理和计算。

### 个人心得摘录与总结
- **elpsconr**：赛时受题目误导尝试从 $1$ 出发正向构建树，后来发现从后往前构建更简单。这提示我们在解题时不要局限于常规思路，可尝试从不同方向思考问题。

---
处理用时：60.29秒