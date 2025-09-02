# 题目信息

# Connectivity Addicts

## 题目描述

This is an interactive problem.

Given a simple undirected graph with $ n $ vertices numbered from $ 1 $ to $ n $ , your task is to color all the vertices such that for every color $ c $ , the following conditions hold:

1. The set of vertices with color $ c $ is connected;
2. $ s_c \leq n_c^2 $ , where $ n_c $ is the number of vertices with color $ c $ , and $ s_c $ is the sum of degrees of vertices with color $ c $ .

 It can be shown that there always exists a way to color all the vertices such that the above conditions hold. Initially, you are only given the number $ n $ of vertices and the degree of each vertex.

In each query, you can choose a vertex $ u $ . As a response, you will be given the $ k $ -th edge incident to $ u $ , if this is the $ k $ -th query on vertex $ u $ .

You are allowed to make at most $ n $ queries.

An undirected graph is simple if it does not contain multiple edges or self-loops.

The degree of a vertex is the number of edges incident to it.

A set $ S $ of vertices is connected if for every two different vertices $ u, v \in S $ , there is a path, which only passes through vertices in $ S $ , that connects $ u $ and $ v $ . That is, there is a sequence of edges $ (u_1, v_1), (u_2, v_2), \dots, (u_k, v_k) $ with $ k \geq 1 $ such that

1. $ u_1 = u $ , $ v_k = v $ , and $ v_i = u_{i+1} $ for every $ 1 \leq i < k $ ; and
2. $ u_k \in S $ and $ v_k \in S $ for every $ 1 \leq i \leq k $ .

 Especially, a set containing only one vertex is connected.

## 说明/提示

In the example, there is only one test case.

In the test case, there are $ n = 5 $ vertices with vertices $ 1, 2, 3, 4 $ of degree $ 2 $ and vertex $ 5 $ of degree $ 0 $ . It is obvious that vertex $ 5 $ is isolated, i.e., it does not connect to any other vertices.

A possible interaction is shown in the sample input and output, where $ 4 $ "?" queries are made on vertex $ 1 $ twice and vertex $ 3 $ twice. According to the responses to these queries, we know that each of vertex $ 1 $ and vertex $ 3 $ connects to two vertices $ 2 $ and $ 4 $ .

A possible solution is shown in the sample output, where vertex $ 1 $ and vertex $ 2 $ are colored by $ 1 $ , vertex $ 3 $ and vertex $ 4 $ are colored by $ 2 $ , and vertex $ 5 $ is colored by $ 3 $ . It can be seen that this solution satisfies the required conditions as follows.

- For color $ c = 1 $ , vertex $ 1 $ and vertex $ 2 $ are connected. Moreover, $ n_1 = 2 $ and $ s_1 = d_1 + d_2 = 2 + 2 = 4 \leq n_1^2 = 2^2 = 4 $ ;
- For color $ c = 2 $ , vertex $ 3 $ and vertex $ 4 $ are connected. Moreover, $ n_2 = 2 $ and $ s_2 = d_3 + d_4 = 2 + 2 = 4 \leq n_2^2 = 2^2 = 4 $ ;
- For color $ c = 3 $ , there is only one vertex (vertex $ 5 $ ) colored by $ 3 $ . Moreover, $ n_3 = 1 $ and $ s_3 = d_5 = 0 \leq n_3^2 = 1^2 = 1 $ .

## 样例 #1

### 输入

```
1
5
2 2 2 2 0

2

4

2

4```

### 输出

```
? 1

? 1

? 3

? 3

! 1 1 2 2 3```

# AI分析结果


### Kay的C++算法解析：Connectivity Addicts 深入学习指南

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`贪心策略`与`并查集应用`

🗣️ **初步分析**：
> 本题的关键在于利用贪心策略构造满足连通性和度数约束的染色方案。想象我们要给游乐场的小朋友分组（节点染色），规则是：同组孩子必须手拉手围成圈（连通），且全组"活跃度"（度数之和）不能超过组员数量的平方。我们的策略是：让最活跃的孩子（度数最大节点）当组长，挨个拉他的朋友入组。如果拉到其他组的孩子，就整组并入对方；如果都是新朋友，就成立新组。  
> - **核心难点**：如何在未知图结构的条件下，用不超过n次查询完成构造？解法按度数降序处理节点，查询时动态合并连通块，保证每次操作后新组都满足度数约束  
> - **可视化设计**：动画将展示像素化的节点（8位风格方块），度数越大方块越大。处理当前节点时闪烁黄色，查询邻接点时显示连接线。合并时触发像素色块扩散特效，配"咔嚓"音效。自动演示模式以贪吃蛇AI形式逐步展开构造过程  

---

#### 2. 精选优质题解参考
**题解一（周子衡）**  
* **点评**：提出关键引理（度数最大节点的邻域必满足约束），奠定算法理论基础。代码用`vector`存储邻接点，染色逻辑清晰。亮点在于严格证明贪心正确性，变量`col`命名直观，边界处理完整，竞赛实用性强  

**题解二（zac2010）**  
* **点评**：代码简洁高效，用`vector<int>().swap(v)`及时释放内存。亮点在于抓住充分条件（$\max deg \leq n_c$），排序后线性扫描，实践性强。输出格式规范，适合初学者模仿  

**题解三（william555）**  
* **点评**：采用并查集维护连通性，`gf`函数实现路径压缩。亮点在于用`mark`数组记录访问状态，避免冗余查询。虽赞数少但代码规范，逻辑闭环，是并查集应用的优秀范例  

---

#### 3. 核心难点辨析与解题策略
1. **贪心选择突破口**  
   * **分析**：为何必须按度数降序处理？若先处理小度数节点，其邻域可能包含大度数节点，导致后续无法满足约束。优质解法均从最大度数节点切入，利用其度数优势保证$s_c \leq n_c^2$  
   * 💡 **学习笔记**：贪心策略中，处理顺序直接影响正确性  

2. **交互次数控制**  
   * **分析**：关键技巧是"遇到已染色邻接点则终止查询"。设节点$u$有$d_u$个邻居，最坏需$d_u$次查询。但按度数降序处理时，高$d_u$节点优先处理，后续节点查询时可能提前遇到已染色点而中断  
   * 💡 **学习笔记**：利用已知信息剪枝是交互题核心优化手段  

3. **连通性维护方式**  
   * **分析**：并查集(`william555`)和染色数组(`zac2010`)各有优势。前者显式维护连通分量关系，后者代码更简洁。选择依据是是否需要后续连通查询  
   * 💡 **学习笔记**：数据结构服务于场景需求  

### ✨ 解题技巧总结
- **降序贪心原则**：优先处理约束最强的元素（最大度数节点）  
- **交互剪枝**：设置终止条件避免全量查询（遇染色点即退出）  
- **增量式验证**：每添加节点后，隐含$n_c$增大而$max deg$不变，自然保持约束  

---

#### 4. C++核心代码实现赏析
**通用核心实现**（综合优化版）：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T; cin >> T;
    while(T--) {
        int n, col_cnt = 0; cin >> n;
        vector<int> deg(n+1), color(n+1, 0);
        vector<int> ids(n);
        for(int i=1; i<=n; i++) {
            cin >> deg[i];
            ids[i-1] = i;
        }
        
        // 按度数降序排序
        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return deg[a] > deg[b];
        });
        
        for(int u : ids) {
            if(color[u]) continue;  // 跳过已染色节点
            
            vector<int> group = {u};  // 当前组初始化
            bool merged = false;
            
            // 查询所有邻接点
            for(int i=0; i<deg[u]; i++) {
                cout << "? " << u << endl;
                int v; cin >> v;
                
                if(color[v]) {  // 遇到已染色点
                    for(int x : group) color[x] = color[v];
                    merged = true;
                    break;
                }
                group.push_back(v);
            }
            
            // 新建颜色组
            if(!merged) {
                col_cnt++;
                for(int x : group) color[x] = col_cnt;
            }
        }
        
        // 输出染色方案
        cout << "! ";
        for(int i=1; i<=n; i++) 
            cout << color[i] << " ";
        cout << endl;
    }
    return 0;
}
```
**代码解读概要**：  
1. 按度数降序排序节点索引  
2. 遍历未染色节点，查询其邻接点  
3. 遇已染色点则整组合并并中断查询  
4. 未遇则新建颜色组  
5. 总查询次数 ≤ n  

---

**题解一（周子衡）片段赏析**  
* **亮点**：理论严谨，引理证明保证正确性  
* **核心逻辑**：
```cpp
// 伪代码：基于引理的贪心框架
while(存在未染色节点u){
  选择度数最大的未染色u;
  查询d_u次邻接点;
  if(遇到已染色点v) 
      将u及当前邻接点染为v的颜色;
  else 
      新建颜色染整组;
}
```
* **学习笔记**：理论分析指导算法设计，避免盲目试错  

**题解二（zac2010）片段赏析**  
* **亮点**：内存优化与简洁控制流  
* **核心逻辑**：
```cpp
vector<int> v;
FL(j,1,d[id[i]]){
    cout << "? " << id[i] << endl;
    cin >> u; 
    if(c[u]) break;  // 关键剪枝
    v.emplace_back(u);
}
c[id[i]] = c[u]? c[u] : ++col;  // 三元表达式赋值
```
* **学习笔记**：`vector::emplace_back`减少拷贝，三元表达式提升代码密度  

**题解三（william555）片段赏析**  
* **亮点**：并查集维护连通分量  
* **核心逻辑**：
```cpp
int gf(int x){return x==fa[x]?x:fa[x]=gf(fa[x]);}  // 路径压缩

// 合并操作
cout<<"? "<<id<<endl;
int x; cin>>x;
fa[gf(x)] = gf(id);  // 合并到当前集合
if(mark[x]) break;    // 遇到已访问节点退出
```
* **学习笔记**：并查集适合需要频繁合并的场景  

---

### 5. 算法可视化：像素动画演示  
**主题**：8位像素风"贪吃蛇组队"  

**设计思路**：  
> 用复古红白机风格呈现节点（像素方块），度数越大方块尺寸越大。控制面板含调速滑块/步进按钮，背景配8bit循环BGM  

**动画流程**：  
1. **初始化**：  
   - 节点按网格排列，显示度数（像素数字）  
   - 控制面板：开始/暂停、单步、速度滑块（⭐复古旋钮设计）  

2. **核心演示**：  
   - **选择节点**：当前处理节点闪烁黄光，播"滴"声  
   - **查询过程**：  
     * 向邻接点发射像素射线，命中时播"咔嚓"声  
     * 被查询节点显示连接线（⭐闪电特效）  
   - **染色合并**：  
     * 新建组：绿色波浪扩散（配"升级"音效）  
     * 合并组：橙色光晕扩散（配"连接"音效）  

3. **自动演示模式**：  
   - 类似贪吃蛇AI自主移动，每步0.5秒间隔  
   - 完成组队时节点跳动，播胜利音效  

4. **状态提示**：  
   - 左下角信息栏：  
     `正在处理: 节点#5 (度数=4)`  
     `已用查询: 3/5`  

---

### 6. 拓展练习  
**相似问题迁移**：  
1. 满足∑(n_c - deg_i) ≥ 0的连通划分（不等式变形）  
2. 交互次数限制下的图连通性检测  
3. 按节点权重贪心构造连通块  

**洛谷推荐**：  
1. **P3367 【模板】并查集**  
   → 掌握连通性维护基础  
2. **P2661 信息传递**  
   → 交互与图论结合，训练查询策略  
3. **P1090 合并果子**  
   → 深化贪心思想在不同场景的应用  

---

### 7. 学习心得  
> **题解经验摘录**（zac2010）：  
> *"交互题需预先规划查询逻辑，避免无效操作"*  
>  
> **Kay点评**：  
> 尤其适用于度数降序处理中的提前终止策略，通过保存中间状态（已染色节点）显著减少查询次数，该技巧可推广至其他交互题型  

---

**结语**  
通过贪心策略和交互优化，我们证明了满足约束的染色方案必然存在。核心在于把握"最大度数优先处理"原则和动态合并机制。希望本指南助你掌握算法精髓！🚀

---
处理用时：165.94秒