# 题目信息

# Billetes MX (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, it is guaranteed that $ q = 0 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 说明/提示

In the first test case of the example, we have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ .

## 样例 #1

### 输入

```
2
3 3 8 0
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
2 5 2 0
1 1 10
1 2 30```

### 输出

```
1
489373567```

# AI分析结果


### 💡 Kay的C++算法解析：Billetes MX (Easy Version) 深入学习指南 💡

> 今天我们来分析这道关于「美丽网格」的题目，它巧妙结合了图论和组合数学。我们将通过并查集建模、连通块计数等核心技巧，揭开异或约束下的网格构造奥秘！

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`图论建模与并查集应用`

🗣️ **初步分析**：
> 想象网格是一张巨大的「密码网」，每个格子的值由行密码和列密码组合而成（`A[i][j] = 行密码[i] ⊕ 列密码[j]`）。这种结构天然满足题目要求——任何子网格四角的异或值都为0。  
> 通过并查集，我们将行列密码的约束关系转化为连通块管理：  
> - **核心流程**：每个已知格子`(r,c,v)`在行节点`r`和列节点`c`间建立权值为`v`的边  
> - **难点突破**：合并时检查环的异或一致性，统计连通块数量`s`后，方案数 = `(2^30)^(s-1) mod 1e9+7`  
> - **可视化设计**：像素网格中，用闪烁线条连接行列节点，形成环时高亮显示并播放音效（成功：清脆"叮"声；冲突：警报音）

---

#### 2. 精选优质题解参考
**题解一（larsr）**
* **点评**：思路直击本质——将网格约束转化为二分图模型。代码中`getfa()`维护节点到根的异或值`fv[]`，`uni()`合并时智能检查环约束（`if (fv[xu]^fv[xv]^w) hf=0`）。亮点在于用`ans`动态统计连通块数，使方案数计算简洁高效（`mul[ans] = (2^30)^(s-1)`）。变量命名规范（如`fv`=find value），边界处理严谨，可直接用于竞赛。

**题解二（lfxxx）**
* **点评**：采用按位拆解+扩展域并查集的巧妙思路。核心亮点在于每位独立处理时，将每个列节点拆分为0/1两个域（如`fa[2*c-1]`和`fa[2*c]`），根据异或值建立域间约束关系。虽然实现稍复杂，但展示了处理位运算约束的通用方法，具有教学价值。

---

#### 3. 核心难点辨析与解题策略
1.  **难点：网格约束的图论转化**
    * **分析**：发现`A[i][j]=行密码⊕列密码`是破题关键！这要求将行/列抽象为节点，格子值作为边权
    * 💡 **学习笔记**：矩阵约束 → 二分图建模是经典套路

2.  **难点：并查集的异或维护**
    * **分析**：合并时需保证异或路径一致性。larsr解法中`fv[u]`维护节点到根的异或值，合并时通过`fv[u_new]=w^fv[xu]^fv[xv]`保证新路径正确
    * 💡 **学习笔记**：带权并查集的权值更新公式是核心

3.  **难点：方案数计算原理**
    * **分析**：`s`个连通块中，只有1个块的根可自由赋值（2^30种选择），其余块由约束唯一确定，故方案数=`(2^30)^(s-1)`
    * 💡 **学习笔记**：连通块数=自由变量数+1

✨ **解题技巧总结**  
- **模型转换术**：将矩阵约束转化为图论问题（行/列→节点，格子→边）  
- **并查集魔改**：用`fv[]`维护异或路径，合并时动态检查约束一致性  
- **连通块魔法**：通过连通块计数快速计算方案数  

---

#### 4. C++核心代码实现赏析
**本题通用核心实现**  
```cpp
void uni(int u, int v, int w) {
    int xu = u, xv = v;
    u = getfa(u); v = getfa(v);
    if(u == v) {
        if(fv[xu]^fv[xv]^w) hf=0; // 环约束检查
        return;
    }
    f[u] = v;
    fv[u] = w^fv[xu]^fv[xv]; // 权值调整公式
    ans--; // 连通块减少
}
```

**题解一（larsr）片段**  
```cpp
if(u == v) {
    if((fv[xu]^fv[xv]^w) != 0) hf=0;
    return;
}
```
> **解读**：当两个节点已连通时，检查新边权`w`是否与现有路径一致（`fv[xu]^fv[xv]`即路径异或值）。若冲突则置`hf=0`标记无解。  
> 💡 **学习笔记**：环检查是保证方案存在的关键阀门！

**题解二（lfxxx）片段**  
```cpp
// 根据异或值建立域间关系
if(val_bit == col_bit) { // 相同值
    merge(u0, v0); 
    merge(u1, v1);
} else { // 不同值
    merge(u0, v1);
    merge(u1, v0);
}
```
> **解读**：按位处理时，若某位值相同，则合并两节点的0域和1域；若不同，则交叉合并（0↔1）。这种「域分裂」完美编码了异或约束。  
> 💡 **学习笔记**：扩展域并查集是处理二值约束的利器！

---

#### 5. 算法可视化：像素动画演示
![](https://via.placeholder.com/400x200?text=8-bit+像素网格+动画示意图)  
* **主题**：复古游戏《密码连接者》  
* **核心演示**：  
  1. 左侧像素网格显示当前矩阵，右侧并查集森林（行节点蓝色/列节点绿色）  
  2. **添加已知格子**：网格中数字亮起→行列节点间升起金色光链（伴随"叮"声）  
  3. **形成环**：光链闭合时高亮环路，显示路径异或值（成功：绿环+欢快音效；失败：红环+警报）  
  4. **连通块统计**：每合并成功，森林中连通块闪烁合并，右上角方案数实时更新  
* **交互设计**：  
  - 控制面板：步进/播放/重置按钮 + 速度滑块  
  - 音效系统：连接(叮)、成功(上扬和弦)、冲突(低音警报)  
  - 游戏化：每完成一组查询点亮一颗星星，集齐三颗通关  

---

#### 6. 拓展练习与相似问题思考
* **技巧迁移场景**：  
  1. 带权并查集维护等式约束（如`A=B+k`）  
  2. 扩展域处理敌对关系（如食物链问题）  
  3. 动态连通性统计方案数（如连通块计数）  

* **洛谷推荐**：  
  1. [P2024 食物链](https://www.luogu.com.cn/problem/P2024) → 扩展域并查集经典应用  
  2. [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525) → 二分图建模思维拓展  
  3. [P4185 MooTube](https://www.luogu.com.cn/problem/P4185) → 连通块动态统计  

---

> 通过这次探索，我们解锁了「约束转化+并查集统计」的组合拳。记住：复杂问题往往有简洁的图论本质！下次遇到矩阵约束时，不妨尝试行列节点建模法哦~ ✨

---
处理用时：203.67秒