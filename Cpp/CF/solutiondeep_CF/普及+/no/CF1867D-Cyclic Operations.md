# 题目信息

# Cyclic Operations

## 题目描述

Egor has an array $ a $ of length $ n $ , initially consisting of zeros. However, he wanted to turn it into another array $ b $ of length $ n $ .

Since Egor doesn't take easy paths, only the following operation can be used (possibly zero or several times):

- choose an array $ l $ of length $ k $ ( $ 1 \leq l_i \leq n $ , all $ l_i $ are distinct) and change each element $ a_{l_i} $ to $ l_{(i\%k)+1} $ ( $ 1 \leq i \leq k $ ).

He became interested in whether it is possible to get the array $ b $ using only these operations. Since Egor is still a beginner programmer, he asked you to help him solve this problem.

The operation $ \% $ means taking the remainder, that is, $ a\%b $ is equal to the remainder of dividing the number $ a $ by the number $ b $ .

## 说明/提示

Let's consider the first example:

- Apply the operation with $ l $ = $ [1,2,3] $ . Now $ a $ = $ [2,3,1,0,0] $ .
- Apply the operation with $ l $ = $ [3,5,4] $ . Now $ a $ = $ [2,3,5,3,4] $ = $ b $ .

 We see that it is possible to get the array $ b $ . Therefore, the answer is YES.In the second example, it can be proven that the array $ b $ cannot be obtained, therefore the answer is NO.

## 样例 #1

### 输入

```
6
5 3
2 3 5 3 4
4 2
2 4 3 1
1 1
1
3 1
1 2 3
5 3
5 4 3 2 1
6 1
1 2 3 1 5 6```

### 输出

```
YES
NO
YES
YES
NO
NO```

# AI分析结果

【题目内容】
# 循环操作

## 题目描述

Egor 有一个长度为 $n$ 的数组 $a$，初始时全为 $0$。他希望将其转换为另一个长度为 $n$ 的数组 $b$。

由于 Egor 不喜欢简单的路径，因此只能使用以下操作（可能零次或多次）：

- 选择一个长度为 $k$ 的数组 $l$（$1 \leq l_i \leq n$，且所有 $l_i$ 互不相同），并将每个元素 $a_{l_i}$ 修改为 $l_{(i\%k)+1}$（$1 \leq i \leq k$）。

他感兴趣的是，是否可以通过仅使用这些操作来得到数组 $b$。由于 Egor 还是个编程初学者，他请你帮助他解决这个问题。

操作 $\%$ 表示取余，即 $a\%b$ 等于 $a$ 除以 $b$ 的余数。

## 说明/提示

考虑第一个例子：

- 应用操作 $l$ = $[1,2,3]$。现在 $a$ = $[2,3,1,0,0]$。
- 应用操作 $l$ = $[3,5,4]$。现在 $a$ = $[2,3,5,3,4]$ = $b$。

我们可以看到，可以得到数组 $b$。因此，答案是 YES。在第二个例子中，可以证明无法得到数组 $b$，因此答案是 NO。

## 样例 #1

### 输入

```
6
5 3
2 3 5 3 4
4 2
2 4 3 1
1 1
1
3 1
1 2 3
5 3
5 4 3 2 1
6 1
1 2 3 1 5 6```

### 输出

```
YES
NO
YES
YES
NO
NO```

【算法分类】图论

【题解分析与结论】
本题的核心在于通过图论中的基环树和环的性质来判断是否可以通过给定的操作将数组 $a$ 转换为数组 $b$。大多数题解都采用了类似的思路：通过构建图并分析环的大小来判断是否满足条件。其中，拓扑排序、Tarjan 算法、DFS 等方法被广泛使用。

【评分较高的题解】

1. **作者：intconstlee (赞：10)**
   - **星级：5**
   - **关键亮点**：通过拓扑排序和基环树的性质，清晰地分析了环的大小与操作的关系，代码简洁且高效。
   - **代码核心思想**：使用拓扑排序去除非环部分，然后通过 DFS 查找环并判断其大小是否等于 $k$。
   ```cpp
   void topu() {
       queue<int> q;
       for(int i=1;i<=n;i++) if(dg[i]==0) q.push(i);
       while(!q.empty()) {
           int u=q.front(); vis[u]=1,q.pop();
           if(!--dg[to[u]]) q.push(to[u]);
       }
   }
   void findcir(int u) {
       int siz=0;
       while(!vis[u]) vis[u]=1,u=to[u],siz++;
       if(siz!=k) ans=0;
   }
   ```

2. **作者：Creeper_l (赞：6)**
   - **星级：4**
   - **关键亮点**：通过简单的 DFS 查找环，并判断环的大小是否等于 $k$，代码简洁且易于理解。
   - **代码核心思想**：通过 DFS 遍历图，记录环的大小并判断是否满足条件。
   ```cpp
   for(int i = 1;i <= n;i++) {
       if(vis[i] == true) continue;
       int u = i,cnt = 0;
       while(vis[u] == false) vis[u] = i,num[u] = ++cnt,u = a[u];
       if(vis[u] != i) continue;
       if(cnt - num[u] + 1 != k) flag = false;
   }
   ```

3. **作者：fast_photon (赞：3)**
   - **星级：4**
   - **关键亮点**：通过 Tarjan 算法缩点，判断每个强连通分量的大小是否等于 $k$，思路清晰且代码实现较为完整。
   - **代码核心思想**：使用 Tarjan 算法查找强连通分量，并判断其大小是否等于 $k$。
   ```cpp
   void tarjan(int u) {
       num++;
       low[u] = num, dfn[u] = num;
       ins[u] = 1;
       st.push(u);
       for(int i = head[u]; i != -1; i = e[i].nxt) {
           int v = e[i].to;
           if(dfn[v] == 0) {
               tarjan(v);
               low[u] = min(low[u], low[v]);
           } else if(ins[v] != 0) {
               low[u] = min(low[u], dfn[v]);
           }
       }
       if(low[u] == dfn[u]) {
           sccs++; 
           int now, ccnt = 0;
           do {
               now = st.top();
               ins[now] = 0;
               pos[now] = sccs;
               ccnt++;
               st.pop();
           } while(now != u);
           sz[sccs] = ccnt;
       }
   }
   ```

【最优关键思路或技巧】
1. **基环树与环的性质**：通过构建图并分析环的大小来判断是否满足操作条件。
2. **拓扑排序与 DFS**：通过拓扑排序去除非环部分，再通过 DFS 查找环并判断其大小。
3. **Tarjan 算法**：通过 Tarjan 算法缩点，判断每个强连通分量的大小是否等于 $k$。

【可拓展之处】
类似的问题可以通过图论中的基环树和环的性质来解决，特别是在处理循环操作或循环依赖的问题时，可以考虑构建图并分析其环结构。

【推荐题目】
1. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
2. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)
3. [P2746 [USACO5.3] 校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)

【个人心得摘录】
- **intconstlee**：通过拓扑排序和基环树的性质，清晰地分析了环的大小与操作的关系，代码简洁且高效。
- **Creeper_l**：通过简单的 DFS 查找环，并判断环的大小是否等于 $k$，代码简洁且易于理解。
- **fast_photon**：通过 Tarjan 算法缩点，判断每个强连通分量的大小是否等于 $k$，思路清晰且代码实现较为完整。

---
处理用时：53.29秒