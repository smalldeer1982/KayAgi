# 题目信息

# Weights Assignment For Tree Edges

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Vertices are numbered from $ 1 $ to $ n $ . Any vertex can be the root of a tree.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root.

The tree is specified by an array of ancestors $ b $ containing $ n $ numbers: $ b_i $ is an ancestor of the vertex with the number $ i $ . The ancestor of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root. For example, on the simple path from $ 5 $ to $ 3 $ (the root), the next vertex would be $ 1 $ , so the ancestor of $ 5 $ is $ 1 $ .

The root has no ancestor, so for it, the value of $ b_i $ is $ i $ (the root is the only vertex for which $ b_i=i $ ).

For example, if $ n=5 $ and $ b=[3, 1, 3, 3, 1] $ , then the tree looks like this.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611D/d1bc9693f3c37aa82543dc99b8156e197e08fb59.png)An example of a rooted tree for $ n=5 $ , the root of the tree is a vertex number $ 3 $ .You are given an array $ p $ — a permutation of the vertices of the tree. If it is possible, assign any positive integer weights on the edges, so that the vertices sorted by distance from the root would form the given permutation $ p $ .

In other words, for a given permutation of vertices $ p $ , it is necessary to choose such edge weights so that the condition $ dist[p_i]<dist[p_{i+1}] $ is true for each $ i $ from $ 1 $ to $ n-1 $ . $ dist[u] $ is a sum of the weights of the edges on the path from the root to $ u $ . In particular, $ dist[u]=0 $ if the vertex $ u $ is the root of the tree.

For example, assume that $ p=[3, 1, 2, 5, 4] $ . In this case, the following edge weights satisfy this permutation:

- the edge ( $ 3, 4 $ ) has a weight of $ 102 $ ;
- the edge ( $ 3, 1 $ ) has weight of $ 1 $ ;
- the edge ( $ 1, 2 $ ) has a weight of $ 10 $ ;
- the edge ( $ 1, 5 $ ) has a weight of $ 100 $ .

The array of distances from the root looks like: $ dist=[1,11,0,102,101] $ . The vertices sorted by increasing the distance from the root form the given permutation $ p $ .

Print the required edge weights or determine that there is no suitable way to assign weights. If there are several solutions, then print any of them.

## 说明/提示

The first set of input data of the example is analyzed in the main part of the statement.

In the second set of input data of the example, it is impossible to assign the positive weights to obtain a given permutation of vertices.

## 样例 #1

### 输入

```
4
5
3 1 3 3 1
3 1 2 5 4
3
1 1 2
3 1 2
7
1 1 2 3 4 5 6
1 2 3 4 5 6 7
6
4 4 4 4 1 1
4 2 1 5 6 3```

### 输出

```
1 10 0 102 100
-1
0 3 100 1 1 2 4
6 5 10 0 2 3```

# AI分析结果


### 💡 Kay的C++算法解析：Weights Assignment For Tree Edges 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`树结构构造`（编程技巧应用）  
🗣️ **初步分析**：  
> 这道题要求我们为树的边赋予权重，使节点按到根距离排序后形成给定排列。核心思路是将排列顺序转化为距离值——**想象成游戏中玩家到达终点的名次**：第1名（根节点）距离为0，第2名距离为1，以此类推。边的权重即当前节点与父节点的"名次差"。  
> - **关键约束**：父节点名次必须小于子节点（否则边权为负），且排列首位必须是根节点  
> - **可视化设计**：采用像素风树形迷宫（FC游戏风格），节点按名次编号显示，边权计算时触发"叮"音效。当父节点名次>子节点时，显示"X"符号并播放失败音效  

---

#### 2. 精选优质题解参考
**题解一（JCLinux）**  
* **点评**：思路直击本质——用`tall[]`记录距离，按排列顺序计算边权。代码规范：  
  - 用`tree[]`存储父节点，`p[]`存储排列，变量名清晰  
  - 边界处理严谨（根节点检测、父节点距离存在性检查）  
  - **亮点**：用`flag`标记无解情况，逻辑闭环性强  

**题解二（Inui_Sana）**  
* **点评**：引入排名`rk[]`概念提升可读性，DFS实现树遍历：  
  - 边权=子节点排名-父节点排名（`ans[v]=rk[v]-rk[u]`）  
  - **亮点**：通过递归自然处理层级关系，代码模块化程度高  

**题解三（Chivas_Regal）**  
* **点评**：独创性使用`pair`存储父子关系，反排列`rp[]`优化查询：  
  - 检查逻辑简洁高效（`rp[fath]>rp[son]`即无解）  
  - **亮点**：边权计算直接输出差值，避免额外存储空间  

---

#### 3. 核心难点辨析与解题策略
1. **根节点位置验证**  
   *分析*：排列首位必须是根节点（距离最小），所有题解首行检测`p[1]==root`  
   💡 学习笔记：树问题优先确认根节点特性  

2. **父子节点名次约束**  
   *分析*：父节点名次必须小于子节点（`rp[fa]<rp[son]`），否则边权为负。通过预存排名快速比较  
   💡 学习笔记：树的有向性决定距离单调性  

3. **边权构造策略**  
   *分析*：设节点在排列中位置为k，则距离=k（或k-1），边权=子距离-父距离  
   💡 学习笔记：相对距离差决定边权，绝对距离值仅需满足递增  

✨ **解题技巧总结**  
- **问题转化**：将抽象排列顺序 → 具体距离数值  
- **预处理优化**：用`rk[]/rp[]`存储排名加速查询  
- **边界先行**：优先处理根节点和非法情况（无解）  

---

#### 4. C++核心代码实现赏析
**通用核心实现**  
```cpp
#include <iostream>
using namespace std;
const int N = 2e5+5;

int main() {
    int t; cin >> t;
    while(t--) {
        int n, root, b[N], p[N], rk[N], ans[N]={0};
        cin >> n;
        for(int i=1; i<=n; i++) {
            cin >> b[i];                // 父节点数组
            if(b[i]==i) root = i;        // 找根节点
        }
        for(int i=1; i<=n; i++) {
            cin >> p[i];                 // 排列顺序
            rk[p[i]] = i;                // 节点->排名映射
        }

        bool valid = (p[1]==root);       // 检查1：首位需为根
        for(int i=2; valid && i<=n; i++) {
            if(rk[b[p[i]]] > rk[p[i]]) { // 检查2：父节点排名>子节点
                valid = false; break;
            }
            ans[p[i]] = rk[p[i]] - rk[b[p[i]]]; // 边权=子排名-父排名
        }

        if(!valid) cout << "-1\n";
        else {
            for(int i=1; i<=n; i++) 
                cout << (i==root ? 0 : ans[i]) << " ";
            cout << endl;
        }
    }
    return 0;
}
```
**代码解读概要**：  
1. 读入父节点数组时识别根节点  
2. 通过`rk[]`映射存储每个节点在排列中的位置  
3. 双重验证：根节点首位性 + 父子节点排名约束  
4. 边权计算基于排名差值，根节点特殊处理  

---

#### 5. 算法可视化：像素动画演示  
![](https://assets.luogu.com.cn/upload/vjudge/sample_cf1611d.gif)  
* **主题**：8-bit风树形迷宫探险  
* **交互设计**：  
  - **动态节点**：像素方块显示节点，顶部标排名（如🥇/🥈/🥉）  
  - **边权计算**：选中边时显示`当前排名 - 父排名 = 边权`公式  
  - **音效系统**：  
    * 合法边权：8-bit "叮"声（NES音效库）  
    * 非法父子：爆炸音效 + 像素方块变💥  
  - **控制面板**：  
    ```js
    const controls = {
      play: () => animate('forward'), 
      step: () => nextNode(),
      speed: document.getElementById('speed-slider') // 调速器
    }
    ```  

* **动画流程**：  
  1. 根节点闪烁绿光（距离=0）  
  2. 按排列顺序高亮节点（蓝→黄渐变表示距离增大）  
  3. 实时显示边权计算过程（如`5号节点：排名3 - 父排名1 = 边权2`）  

---

#### 6. 拓展练习与相似问题思考
* **技巧迁移场景**：  
  1. 带约束的树结构重构（如CF 1294F）  
  2. 基于排名的图论路径构造（如LeetCode 1514）  
  3. 拓扑序约束的边权分配（如Atcoder ABC 216F）  

* **洛谷推荐**：  
  1. **P1351 联合权值**  
     🗣️ 巩固树遍历与节点关系计算  
  2. **P3379 最近公共祖先**  
     🗣️ 理解树结构的基本操作变形  
  3. **P3942 将军令**  
     🗣️ 进阶练习树上的约束分配问题  

---

#### 7. 学习心得与经验分享
> **经验摘录（JCLinux）**：  
> *"在检查父节点时未初始化`tall[]`导致WA，提醒我们务必初始化数组"*  
>   
> **Kay点评**：  
> 这是调试树结构问题的通用教训——**始终初始化存储层级关系的数组**。建议：  
> - 定义数组后立即用`memset`或循环赋初值  
> - 特别关注根节点和边界值（如`tall[root]=0`）  

---

通过本次分析，大家应掌握树结构问题的核心思维：**层级决定顺序，约束驱动构造**。下期我们将探索更复杂的图论构造问题！🚀

---
处理用时：97.45秒