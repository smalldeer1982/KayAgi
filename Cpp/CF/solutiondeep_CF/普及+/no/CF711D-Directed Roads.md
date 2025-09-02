# 题目信息

# Directed Roads

## 题目描述

ZS the Coder and Chris the Baboon has explored Udayland for quite some time. They realize that it consists of $ n $ towns numbered from $ 1 $ to $ n $ .

There are $ n $ directed roads in the Udayland. $ i $ -th of them goes from town $ i $ to some other town $ a_{i} $ ( $ a_{i}≠i $ ). ZS the Coder can flip the direction of any road in Udayland, i.e. if it goes from town $ A $ to town $ B $ before the flip, it will go from town $ B $ to town $ A $ after.

ZS the Coder considers the roads in the Udayland confusing, if there is a sequence of distinct towns $ A_{1},A_{2},...,A_{k} $ ( $ k&gt;1 $ ) such that for every $ 1<=i&lt;k $ there is a road from town $ A_{i} $ to town $ A_{i+1} $ and another road from town $ A_{k} $ to town $ A_{1} $ . In other words, the roads are confusing if some of them form a directed cycle of some towns.

Now ZS the Coder wonders how many sets of roads (there are $ 2^{n} $ variants) in initial configuration can he choose to flip such that after flipping each road in the set exactly once, the resulting network will not be confusing.

Note that it is allowed that after the flipping there are more than one directed road from some town and possibly some towns with no roads leading out of it, or multiple roads between any pair of cities.

## 说明/提示

Consider the first sample case. There are $ 3 $ towns and $ 3 $ roads. The towns are numbered from $ 1 $ to $ 3 $ and the roads are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/bbf0ca4cbc925b1d673ae3b61e28811a0ccacf51.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/43ec097315a08660c95bbf7f709c76c8ce606dd6.png) initially. Number the roads $ 1 $ to $ 3 $ in this order.

The sets of roads that ZS the Coder can flip (to make them not confusing) are $ {1},{2},{3},{1,2},{1,3},{2,3} $ . Note that the empty set is invalid because if no roads are flipped, then towns $ 1,2,3 $ is form a directed cycle, so it is confusing. Similarly, flipping all roads is confusing too. Thus, there are a total of $ 6 $ possible sets ZS the Coder can flip.

The sample image shows all possible ways of orienting the roads from the first sample such that the network is not confusing.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/329f4376794f6e7da8ed8bb533f70d300253c072.png)

## 样例 #1

### 输入

```
3
2 3 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
2 1 1 1
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5
2 4 2 5 3
```

### 输出

```
28
```

# AI分析结果

### 题目内容
# 有向道路

## 题目描述
ZS 程序员和 Chris 狒狒在 Udayland 探索了很长时间。他们发现这个地方由 $n$ 个城镇组成，编号从 $1$ 到 $n$。

Udayland 有 $n$ 条有向道路。第 $i$ 条道路从城镇 $i$ 通向另一个城镇 $a_{i}$（$a_{i}≠i$）。ZS 程序员可以翻转 Udayland 中任何一条道路的方向，也就是说，如果在翻转前它从城镇 $A$ 通向城镇 $B$，那么翻转后它将从城镇 $B$ 通向城镇 $A$。

ZS 程序员认为，如果存在一个由不同城镇组成的序列 $A_{1},A_{2},...,A_{k}$（$k>1$），使得对于每一个 $1\leq i<k$ 都有一条从城镇 $A_{i}$ 到城镇 $A_{i + 1}$ 的道路，并且还有一条从城镇 $A_{k}$ 到城镇 $A_{1}$ 的道路，那么 Udayland 的道路就会令人困惑。换句话说，如果其中一些道路形成了一些城镇的有向环，那么这些道路就会令人困惑。

现在 ZS 程序员想知道，在初始配置中，他可以选择多少组道路（共有 $2^{n}$ 种变体）进行翻转，使得在恰好翻转集合中的每条道路一次后，最终的网络不会令人困惑。

注意，翻转后允许从某个城镇有不止一条有向道路，也可能存在一些没有道路通向外部的城镇，或者任意两个城市之间有多条道路。

## 说明/提示
考虑第一个样例。有 $3$ 个城镇和 $3$ 条道路。城镇编号从 $1$ 到 $3$，初始道路为：$1 \to 2$，$2 \to 3$，$3 \to 1$。按此顺序将道路编号为 $1$ 到 $3$。

ZS 程序员可以翻转（以使它们不令人困惑）的道路集合是 $\{1\},\{2\},\{3\},\{1,2\},\{1,3\},\{2,3\}$。注意，空集是无效的，因为如果不翻转任何道路，那么城镇 $1,2,3$ 会形成一个有向环，所以会令人困惑。同样，翻转所有道路也会令人困惑。因此，ZS 程序员总共有 $6$ 种可能的道路集合可以翻转。

样例图片展示了第一个样例中所有使网络不令人困惑的道路定向方式。

## 样例 #1
### 输入
```
3
2 3 1
```
### 输出
```
6
```
## 样例 #2
### 输入
```
4
2 1 1 1
```
### 输出
```
8
```
## 样例 #3
### 输入
```
5
2 4 2 5 3
```
### 输出
```
28
```

### 算法分类
数学（组合数学）

### 题解综合分析与结论
这些题解的核心思路都是基于基环树的性质来计算满足条件的方案数。由于题目给定 $n$ 个点 $n$ 条边，可判断为基环树森林。对于不在环上的边，其方向选择不影响是否成环，有 $2$ 种选择，方案数为 $2^{n - \sum{w_i}}$，其中 $w_i$ 表示每个环上的点数。对于环上的边，总共有 $2^{w_i}$ 种方向设置方式，但全顺时针或全逆时针会形成环，需减去这 $2$ 种情况，即每个环有 $2^{w_i} - 2$ 种合法方案。所以总的方案数为 $2^{n - \sum{w_i}} * \prod{(2^{w_i} - 2)}$。

各题解的主要区别在于找环的方法和代码实现细节。有的使用 DFS 直接找环（如 ChthollyTree、Coros_Trusds 等），有的使用 Tarjan 算法找环（如 Starlight237、xixike），还有的使用并查集 + BFS 找环（如 D2T1）。

### 所选的题解
- **作者：ChthollyTree（5星）**
  - **关键亮点**：思路清晰，先明确问题是基于基环树，分别阐述不在环上的边和环上的边的方案数计算方法，代码实现简洁明了，注释详细。
  - **重点代码**：
```cpp
// 找环的 DFS 函数
void dfs(int x,int h) {
    if(c[x]) {
        an =  h - c[x];
        return;
    }
    c[x] = h;
    dfs(a[x],h+1);
}
// 主函数中计算方案数
LL ans = kasumi(2,n - mm);
for(int i = 1; i <= nn; i ++) {
    ans = ans*(kasumi(2,h[i]) - 2) %mo;
} 
cout<<ans;
```
核心实现思想：通过 DFS 找到环上的点数 `h[i]`，然后根据公式计算不在环上的边的方案数 `kasumi(2,n - mm)` 和环上的边的方案数 `kasumi(2,h[i]) - 2`，最后相乘得到总方案数。
- **作者：Coros_Trusds（4星）**
  - **关键亮点**：从总方案数减去出现环的方案数的角度出发，思路独特，代码结构清晰，对基环树的方案数推导详细。
  - **重点代码**：
```cpp
// 找环的 DFS 函数
inline void dfs(int now,int depth) {
    dep[now]=depth;
    vis[now]=1;
    for(register int i=head[now];i;i=node[i].nxt) {
        int v=node[i].v;
        if(vis[v]==false) {
            dfs(v,depth+1);
        } else if(vis[v]==1) {
            link[++top]=dep[now]-dep[v]+1;
            sum+=link[top];
        }
    }
    vis[now]=2;
}
// 主函数中计算方案数
int mul=1;
for(register int i=1;i<=top;i++) {
    mul=mul*(ksm(2,link[i],mod)-2)%mod;
}
int lastans=mul;
lastans*=ksm(2,n-sum,mod);
printf("%lld\n",lastans%mod);
```
核心实现思想：利用 DFS 标记节点深度，当再次访问已访问节点时，计算环上的点数 `link[i]`，根据公式计算每个环的方案数 `ksm(2,link[i],mod)-2` 并累乘，再乘以不在环上的边的方案数 `ksm(2,n-sum,mod)` 得到总方案数。
- **作者：reyik（4星）**
  - **关键亮点**：直接阐述计算方案数的公式思路，简洁明了，代码实现紧凑，对关键操作有函数封装，如快速幂和乘法取模。
  - **重点代码**：
```cpp
// 找环的 DFS 函数
void dfs(int u,int d) {
    dep[u]=d;vis[u]=1;
    for (int i=head[u];~i;i=e[i].nxt) {
        int v=e[i].to;
        if(!vis[v]) dfs(v,d+1);
        else if(vis[v]==1) w[++top]=dep[u]-dep[v]+1;
    }
    vis[u]=2;
}
// 主函数中计算方案数
int sum=0,res=1;
for (int i=1;i<=top;++i) {
    sum+=w[i];
    res=mul(res,mi2[w[i]]-2+mod);
}
printf("%d\n",mul(res,mi2[n-sum]));
```
核心实现思想：通过 DFS 找到环上的点数 `w[i]`，先计算环上的方案数 `mi2[w[i]]-2+mod` 并累乘，再乘以不在环上的边的方案数 `mi2[n-sum]` 得到总方案数。

### 最优关键思路或技巧
- **利用基环树性质**：将问题转化为对基环树中环上和环外边的方案数计算，这是解决本题的关键思路。
- **分类讨论**：清晰地区分环上和环外的边，分别考虑它们对形成环的影响，从而得出总的方案数公式。
- **快速幂计算**：在计算 $2$ 的幂次方时，使用快速幂算法可以提高计算效率，降低时间复杂度。

### 拓展思路
同类型题通常围绕图的定向、环的存在性及方案数计算等方面。类似算法套路是先判断图的类型（如基环树、树等），再根据图的结构特点，对不同部分（如环、树边等）进行分类讨论，结合组合数学知识计算方案数。

### 洛谷相似题目
- [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)：同样涉及到图中找环及相关计算，不过重点在于找最小环的长度。
- [P3275 [SCOI2011]糖果](https://www.luogu.com.cn/problem/P3275)：与图论和不等式约束有关，通过建图和拓扑排序解决问题，与本题在图的处理上有一定相似性。
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及到图的染色和连通块处理，与本题对图结构的分析和处理思路类似。 

---
处理用时：87.89秒