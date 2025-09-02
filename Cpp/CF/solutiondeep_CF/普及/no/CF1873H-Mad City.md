# 题目信息

# Mad City

## 题目描述

Marcel 和 Valeriu 住在一座包含 $n$ 座建筑物和 $n$ 条无向边的城市。

初始时，Marcel 和 Valeriu 分别处于建筑物 $a$ 和建筑物 $b$。 Marcel 想要抓住 Valeriu。Valeriu 被 Marcel 抓住，当且仅当二人在某一时刻处于同一条边或同一座建筑物中。

在每次行动中，他们会选择移动到一个相邻的建筑物中，或停留在原地。由于 Valeriu 十分了解 Marcel，Valeriu 能够预测出 Marcel 的下一步行动。Valeriu 可以利用这些信息来制定行动路线。二人同时开始和结束行动。

对于任何两个建筑物，有且仅有一条路径将二者相连。

假设二人都绝顶聪明，判断 Valeriu 是否能够永远不被 Marcel 抓住。

## 样例 #1

### 输入

```
6
3 2 1
2 1
3 2
1 3
4 1 4
1 4
1 2
1 3
2 3
4 1 2
1 2
2 3
2 4
3 4
7 1 1
4 1
2 1
5 3
4 6
4 2
7 5
3 4
8 5 3
8 3
5 1
2 6
6 8
1 2
4 8
5 7
6 7
10 6 1
1 2
4 3
5 8
7 8
10 4
1 9
2 4
8 1
6 2
3 1```

### 输出

```
YES
NO
YES
NO
NO
YES```

# AI分析结果

【题目内容】
# Mad City

## 题目描述

Marcel 和 Valeriu 住在一座包含 $n$ 座建筑物和 $n$ 条无向边的城市。

初始时，Marcel 和 Valeriu 分别处于建筑物 $a$ 和建筑物 $b$。 Marcel 想要抓住 Valeriu。Valeriu 被 Marcel 抓住，当且仅当二人在某一时刻处于同一条边或同一座建筑物中。

在每次行动中，他们会选择移动到一个相邻的建筑物中，或停留在原地。由于 Valeriu 十分了解 Marcel，Valeriu 能够预测出 Marcel 的下一步行动。Valeriu 可以利用这些信息来制定行动路线。二人同时开始和结束行动。

对于任何两个建筑物，有且仅有一条路径将二者相连。

假设二人都绝顶聪明，判断 Valeriu 是否能够永远不被 Marcel 抓住。

【算法分类】
图论

【题解分析与结论】
本题的核心在于判断 Valeriu 是否能够通过移动到环上来永远逃脱 Marcel 的追捕。题解主要集中在如何找到环、计算 Valeriu 和 Marcel 到环的最短路径，并比较两者的距离。

【评分较高的题解】
1. **作者：_Ink (赞：21)**  
   - **星级：5星**  
   - **关键亮点**：使用拓扑排序找到环，并通过 BFS 计算 Valeriu 和 Marcel 到环的最短路径，思路清晰且代码简洁。  
   - **核心代码**：
     ```cpp
     void topu(int x) {
         vist[x] = true;
         for(int i = head[x]; i; i = nxt[i]) {
             int y = to[i];
             if(vist[y] || rd[y] == 0) continue;
             rd[y] --; rd[x] --;
             if(x == tagn) tagn = y; // 点被删，转移 tag 位置 
             if(rd[y] != 1) continue;
             topu(y);
         }
         vist[x] = false;
     }
     ```
   - **个人心得**：通过拓扑排序找到环的过程非常巧妙，避免了复杂的环检测算法。

2. **作者：I_am_AKed_by_NOI (赞：2)**  
   - **星级：4星**  
   - **关键亮点**：使用 Tarjan 算法找到环，并通过 DFS 和 BFS 计算最短路径，思路清晰但代码稍显复杂。  
   - **核心代码**：
     ```cpp
     void tarjan(int u, int in_edge) {
         dfn[u] = low[u] = ++id;
         stk[++top] = u;
         for(int k = last[u]; k; k = a[k].pre) {
             int y = a[k].y;
             if(!dfn[y]) {
                 tarjan(y, k);
                 low[u] = min(low[u], low[y]);
             }
             else if(k != (in_edge ^ 1)) {
                 low[u] = min(low[u], dfn[y]);
             }
         }
         if(dfn[u] == low[u]) {
             ++cnt;
             int y;
             do {
                 y = stk[top--];
                 Size[cnt]++;
                 ys[cnt].push_back(y);
                 id[y] = cnt;
             } while(u != y);
         }
     }
     ```
   - **个人心得**：Tarjan 算法虽然复杂，但在处理环检测时非常有效。

3. **作者：rui_er (赞：1)**  
   - **星级：4星**  
   - **关键亮点**：使用并查集和 LCA 来找到环，并通过 Dijkstra 计算最短路径，思路新颖且代码高效。  
   - **核心代码**：
     ```cpp
     void dfs(int u, int f) {
         dis[u] = dis[f] + 1;
         fa[0][u] = f;
         rep(i, 1, 18) fa[i][u] = fa[i-1][fa[i-1][u]];
         for(int v : e[u]) if(v != f) dfs(v, u);
     }
     ```
   - **个人心得**：通过并查集和 LCA 的结合，避免了复杂的环检测算法，代码简洁高效。

【最优关键思路或技巧】
1. **拓扑排序找环**：通过拓扑排序找到环的过程非常高效，避免了复杂的环检测算法。
2. **BFS 计算最短路径**：BFS 在计算最短路径时非常高效，尤其适用于无权图。
3. **并查集与 LCA 结合**：通过并查集和 LCA 的结合，可以高效地找到环并计算最短路径。

【可拓展之处】
本题的解法可以拓展到其他基环树相关的问题，如基环树上的动态规划、基环树的最短路问题等。

【推荐题目】
1. P8943 - 基环树上的动态规划
2. P8944 - 基环树的最短路问题
3. P8945 - 基环树的环检测与处理

---
处理用时：33.12秒