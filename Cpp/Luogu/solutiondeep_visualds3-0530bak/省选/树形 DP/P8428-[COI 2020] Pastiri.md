# 题目信息

# [COI 2020] Pastiri

## 题目描述

给定一棵 $N$ 点的树，点编号为 $1$ 到 $N$，现在在 $K$ 个点上有羊，你的任务是在树上分配一些牧羊人。

这些牧羊人很懒，只会看管离他最近的羊。当然如果有多个离他最近的羊，那么他会都看管。

当然，牧羊人可以和羊在同一个点上，但这样牧羊人只会看管这一个点上的那个羊。

求一种牧羊人的分配方案使得牧羊人总数最小。

## 说明/提示

#### 样例 3 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/qwahnh8z.png)

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（8 pts）：$1 \le N \le 5 \times 10^5$，任意一个点 $i$ 都与 $i+1$ 相连（$1 \le i \le N-1$）。
- Subtask 2（18 pts）：$1 \le K \le 15$，$1 \le N \le 5 \times 10^5$。
- Subtask 3（23 pts）：$1 \le N \le 2000$。
- Subtask 4（51 pts）：$1 \le N \le 5 \times 10^5$。

对于 $100\%$ 的数据，$1 \le K \le N$，$1 \le a_i,b_i \le N$，$1 \le  o_i \le N$。

**本题使用 Special Judge，checker 提供者 @[Lynkcat](https://www.luogu.com.cn/user/120911)，感谢他的贡献。**

#### 说明

翻译自 [Croatian Olympiad in Informatics 2020 B Pastiri](https://hsin.hr/coci/archive/2019_2020/olympiad_tasks.pdf)。

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4
1 4```

### 输出

```
2
1 3```

## 样例 #2

### 输入

```
9 5
1 2
2 3
3 4
3 5
1 6
1 7
7 8
8 9
2 5 6 7 9```

### 输出

```
3
1 4 9```

## 样例 #3

### 输入

```
20 9
1 2
2 3
2 4
4 5
4 6
5 7
7 8
8 9
7 10
10 11
6 12
6 13
6 17
13 14
14 15
14 16
17 18
18 19
18 20
1 3 9 11 12 15 16 19 20```

### 输出

```
3
5 14 18```

# AI分析结果



---

## **算法分类**  
贪心算法（树结构应用）

---

## **综合分析与结论**  
### **核心思路**  
题目要求用最少的牧羊人覆盖所有羊，关键在于贪心策略：  
1. **预处理距离**：计算每个节点到最近羊的最短距离（多源BFS）。  
2. **深度排序**：按深度从大到小处理未被覆盖的羊。  
3. **祖先选择**：对最深羊，沿父节点链上跳，找到最浅的祖先节点作为牧羊人（该节点到羊的距离等于路径长度）。  
4. **覆盖标记**：从牧羊人出发，DFS/BFS标记所有满足条件的节点（子节点的距离递减且未被覆盖）。  

### **解决难点**  
- **贪心正确性**：最深羊的覆盖无法被其他子树更优解决，选择最高祖先可最大化覆盖范围。  
- **高效覆盖**：DFS时根据距离提前终止分支，确保每个节点只遍历一次，复杂度O(n)。  

### **可视化设计**  
1. **动画流程**：  
   - **树结构**：用节点颜色区分羊（红色）、牧羊人（蓝色）、覆盖区域（渐变色）。  
   - **跳祖先**：高亮当前最深羊，沿父节点链向上移动，动态显示路径。  
   - **覆盖扩散**：从牧羊人节点开始，扩散式标记覆盖区域，符合条件则变绿。  
2. **复古风格**：  
   - **像素网格**：树节点以8位风格方块表示，音效提示关键操作（选中羊、放置牧羊人）。  
   - **自动模式**：逐步执行贪心步骤，背景播放循环芯片音乐，成功时播放胜利音效。  

---

## **题解清单 (≥4星)**  
1. **cc0000 (4.5星)**  
   - **亮点**：代码简洁，利用SPFA预处理距离，DFS剪枝优化覆盖标记。  
   - **关键代码**：  
     ```cpp  
     void dfs(int p,int s) {  
         d[p]=1;  
         for(int i=head[p];i;i=nxt[i]) {  
             int v=to[i];  
             if(dis[v]!=s-1||d[v]) continue;  
             dfs(v,s-1);  
         }  
     }  
     ```  
2. **wYYSZLwSSY (4.5星)**  
   - **亮点**：详细证明贪心正确性，利用`dis`判断子树覆盖，代码可读性高。  
   - **关键代码**：  
     ```cpp  
     void dfs1(int x,int fa,int last) {  
         bl[x]=1;  
         if(!last) return;  
         for(auto j:eg[x]) {  
             if(bl[j] || dis[j]>last-1) continue;  
             dfs1(j,x,last-1);  
         }  
     }  
     ```  
3. **MerlinLee (4星)**  
   - **亮点**：结合`dp`和`vis`标记，动态更新覆盖状态，适合教学理解。  
   - **关键代码**：  
     ```cpp  
     void solve(int k,int fa,int s) {  
         p[k]=0,vi[k]=1;  
         if(!s) return;  
         for(int i=last[k];i;i=nxt[i])  
             if(dis[to[i]]==s-1 && !vi[to[i]])  
                 solve(to[i],k,s-1);  
     }  
     ```  

---

## **最优思路提炼**  
1. **贪心策略**：从最深羊出发，选择最浅的祖先节点作为牧羊人，最大化覆盖范围。  
2. **覆盖剪枝**：DFS时仅遍历满足`dis[子节点] = 当前距离-1`的路径，避免重复计算。  
3. **线性复杂度**：预处理距离O(n)，排序O(k log k)，覆盖标记O(n)。  

---

## **同类型题推荐**  
1. **P3523 [POI2011] DYN-Dynamite**：树中选择点覆盖关键节点，类似贪心策略。  
2. **P3942 将军令**：最小点覆盖，每个点覆盖一定距离内的节点。  
3. **P2279 [HNOI2003] 消防局的设立**：覆盖问题，节点覆盖半径为2的子树。  

---

## **个人心得摘录**  
- **调试教训**：DFS标记时需严格判断`dis`递减，否则会错误覆盖其他牧羊人的区域。  
- **顿悟点**：最深羊的覆盖必须由自身或其祖先处理，其他子树无法覆盖更深节点。  

---

## **可视化算法演示**  
```javascript  
// 伪代码：Canvas绘制牧羊人覆盖过程  
function animateStep(sheepNode, shepherd) {  
    // 高亮当前最深羊  
    highlight(sheepNode, 'red');  
    // 向上跳祖先，显示路径  
    let current = sheepNode;  
    while (validAncestor(current)) {  
        current = current.parent;  
        drawPath(current, 'yellow');  
    }  
    // 确定牧羊人位置  
    highlight(shepherd, 'blue');  
    // 扩散覆盖区域  
    let queue = [shepherd];  
    while (queue.length > 0) {  
        let node = queue.pop();  
        for (let child of node.children) {  
            if (child.dis === node.dis - 1 && !child.covered) {  
                child.covered = true;  
                queue.push(child);  
                drawCover(child, 'green');  
            }  
        }  
    }  
}  
```  

---

**颜色方案**：羊（#FF0000）、牧羊人（#0000FF）、覆盖区域（渐变色#00FF00→#008800）。  
**音效**：选中羊（8-bit "beep"）、放置牧羊人（"click"）、覆盖完成（"fanfare"）。

---
处理用时：98.42秒