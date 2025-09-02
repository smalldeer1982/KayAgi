# 题目信息

# [USACO06DEC] Wormholes G

## 题目背景

[英文题面见此链接](https://www.luogu.com.cn/paste/mxuf6zpl)

## 题目描述

John 在他的农场中闲逛时发现了许多虫洞。虫洞可以看作一条十分奇特的有向边，并可以使你返回到过去的一个时刻（相对你进入虫洞之前）。

John 的每个农场有 $m$ 条小路（无向边）连接着 $n$ 块地（从 $1 \sim n$ 标号），并有 $w$ 个虫洞。

现在 John 希望能够从某块地出发，走过一条路径回到出发点，且同时也回到了出发时刻以前的某一时刻。请你告诉他能否做到。

## 说明/提示

#### 样例 2 解释

John 只需要沿着 $1 \rightarrow 2 \rightarrow 3 \rightarrow 1$ 的路径一直转圈即可，每转完一圈，时间就会减少一秒。

#### 数据范围与约定

对于 $100\%$ 的数据，$1 \le T \le 5$，$1 \le n \le 500$，$1 \le m \le 2500$，$1 \le w \le 200$，$1 \le p \le 10^4$。

## 样例 #1

### 输入

```
2
3 3 1
1 2 2
1 3 4
2 3 1
3 1 3
3 2 1
1 2 3
2 3 4
3 1 8```

### 输出

```
NO
YES```

# AI分析结果

### 综合分析与结论
本题核心是判断图中是否存在负环，各题解采用了多种算法，包括 Floyd、SPFA（BFS 和 DFS 版）、Bellman - Ford 等。不同算法各有优劣，Floyd 代码简单但时间复杂度高，SPFA 灵活且有多种优化方式，Bellman - Ford 则较为基础。

### 所选题解
- **作者：Drifting (赞：24)，4星**
    - **关键亮点**：使用 Floyd 算法判负环，代码简洁，思路清晰，有快读优化。
    - **个人心得**：提到卡常极为痛苦，建议开 O2 优化。
- **作者：wjy666 (赞：14)，4星**
    - **关键亮点**：采用 DFS 版 SPFA 判负环，速度快，2ms 就过了，有详细注释。
    - **个人心得**：强调了 DFS 版 SPFA 在本题中的优越性。
- **作者：Sakura_Peng (赞：12)，4星**
    - **关键亮点**：提出超级源点的方法，结合 DFS 版 SPFA 判负环，对负环判断有详细解释。

### 重点代码与核心实现思想
#### Drifting 的 Floyd 判负环
```cpp
bool check()
{
    for (register int k = 1; k <= n; k++)
        for (register int i = 1; i <= n; i++)
        {
            for (register int j = 1; j <= n; j++)
            {
                int res = dis[i][k] + dis[k][j];
                if (dis[i][j] > res)
                    dis[i][j] = res;
            }
            if (dis[i][i] < 0)
                return 1;
        }
    return 0;
}
```
核心思想：Floyd 算法通过枚举中间点 k，更新任意两点间的最短距离。若存在某个点的到自身的最短距离小于 0，则存在负环。

#### wjy666 的 DFS 版 SPFA
```cpp
void spfa(int k) { 
    if (fl[k]==1) {fl[k]=0; flag=1; return;} 
    fl[k]=1; 
    if (!mp[k].empty())
        For(i,0,mp[k].size()-1)
            if (sum[mp[k][i].nex]>mp[k][i].dis+sum[k]){
                sum[mp[k][i].nex]=mp[k][i].dis+sum[k];
                spfa(mp[k][i].nex); if (flag==1) {fl[k]=0; return;} 
            }
    fl[k]=0; 
}
```
核心思想：DFS 版 SPFA 从一个点开始深度优先搜索，若某个点被再次访问，则说明存在负环。

#### Sakura_Peng 的超级源点 + DFS 版 SPFA
```cpp
void pd(int x)
{
    if (flag)
        return ;
    b[x]=1;
    int k=h[x];
    while (k!=-1)
    {
        if (dis[a[k].to]>dis[x]+a[k].dis)
        {
            dis[a[k].to]=dis[x]+a[k].dis;
            if (b[a[k].to])
            {
                flag=1;
                return ;
            }
            else
                pd(a[k].to);
        }
        k=a[k].next;
    }
    b[x]=0;
}
```
核心思想：建立超级源点，将其与所有点相连，权值为 0。从超级源点开始 DFS 搜索，若某个点被再次访问，则存在负环。

### 最优关键思路或技巧
- **超级源点**：当有多个源点时，建立超级源点可以减少枚举源点的冗余操作，提高效率。
- **DFS 版 SPFA**：在判断负环时，DFS 版 SPFA 能更快地发现负环，因为它可以记录路径，一旦某个点被再次访问就可判断存在负环。
- **快读优化**：在输入数据较多时，使用快读可以减少输入时间，提高程序效率。

### 可拓展之处
同类型题或类似算法套路：
- 其他负环判断问题，如一些图论中的最短路径问题，若存在负权边，就需要判断是否存在负环。
- 差分约束系统问题，可转化为图论中的负环判断问题。

### 推荐题目
- [P3385 【模板】负环](https://www.luogu.org/problemnew/show/P3385)
- [P1993 小 K 的农场](https://www.luogu.org/problemnew/show/P1993)
- [P5960 【模板】差分约束算法](https://www.luogu.org/problemnew/show/P5960)

### 个人心得摘录与总结
- **Drifting**：卡常痛苦，建议开 O2 优化，说明在处理时间复杂度较高的算法时，优化的重要性。
- **wjy666**：强调 DFS 版 SPFA 在本题中的优越性，提醒我们在不同场景下选择合适的算法。
- **C20210114 卢思吉**：多次提交未 AC 是因为没注意虫洞是有向边，小路是无向边，且前向星要每次清零，说明在处理图论问题时，边的方向和数据初始化的重要性。

---
处理用时：44.66秒