# 题目信息

# Billetes MX (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is guaranteed that $ q \leq 10^5 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 说明/提示

In the first test case of the example, we initially have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ , so the first answer is $ 1 $ . For the second query, the grid does not satisfy the condition, and thus the answer is $ 0 $ .

## 样例 #1

### 输入

```
3
3 3 8 1
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
3 3 1
2 5 2 0
1 1 10
1 2 30
2 5 0 2
1 1 10
1 2 30```

### 输出

```
1
0
489373567
651321892
769740174
489373567```

# AI分析结果


### 💡 Kay的C++算法解析：Billetes MX (Hard Version) 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：**并查集在异或约束系统中的应用**  
🗣️ **初步分析**：
> 网格"美丽"的条件本质是任意两行对应列的异或值相同（或任意两列对应行的异或值相同）。这就像建立一套"密码体系"：每行/列有一个密钥，网格值是两个密钥的异或。  
> - **核心技巧**：将网格转化为图模型——行和列作为节点，已知值作为带权边（权=异或值）。用并查集维护连通性，同时检查约束一致性（无矛盾环）。  
> - **可视化设计**：像素动画将展示节点（行/列）如何通过边连接成连通块。合并时播放"咔嚓"音效，矛盾时屏幕闪烁红色，成功时播放"胜利"音效。  
> - **复古游戏化**：采用8-bit像素风格，节点为彩色方块，连通块同色。控制面板含单步/自动模式，速度滑块调节"AI探险家"移动速度。

---

#### 2. 精选优质题解参考
**题解一（作者：larsr）**  
* **点评**：  
  思路直击本质——网格值可分解为行密钥⊕列密钥。代码简洁高效：  
  - 并查集统一管理行/列节点（1~n为行，n+1~n+m为列）  
  - 用`fv`数组动态维护节点到根的异或值  
  - 巧用`hf`标记矛盾（初始为INF，矛盾时置0）  
  代码规范：变量名`f`（父节点）、`fv`（异或值）含义清晰，边界处理严谨（如`hf`机制）。实践价值高，可直接用于竞赛。

**题解二（作者：2020HZ06）**  
* **点评**：  
  创新性从列前缀和角度建模：  
  - 维护列前缀和节点（1~m）的约束关系  
  - `query`函数递归计算节点到根的异或值  
  - 按秩合并优化树结构（虽未完全实现）  
  代码可读性稍弱（变量名如`sgn`不够直观），但算法有效性高，提供了另一种视角。

---

#### 3. 核心难点辨析与解题策略
1. **难点：约束系统建模**  
   *分析*：需发现网格值可表示为`A[i][j] = row_key[i] ⊕ col_key[j]`。优质题解通过建图（行/列为节点）或列前缀和转换解决。  
   💡 **学习笔记**：复杂约束可转化为图论问题——节点表变量，边表关系。

2. **难点：动态维护异或一致性**  
   *分析*：并查集合并时需调整权值，保证路径异或值正确。题解一用`fv`数组+路径压缩；题解二用递归`query`实时计算。  
   💡 **学习笔记**：带权并查集的本质是维护节点到根的路径信息。

3. **难点：方案数计算与自由度**  
   *分析*：连通块数`s`决定自由度。因全局异或常数不改变网格，实际自由度为`s-1`，方案数为$2^{30(s-1)}$。  
   💡 **学习笔记**：系统自由度 = 连通块数 - 1（基准节点固定）。

✨ **解题技巧总结**  
- **问题分解**：将网格约束拆解为节点间异或关系（如`row_i ⊕ col_j = v`）  
- **增量处理**：动态并查集支持实时添加约束（本题`q`次更新）  
- **矛盾检测**：合并时检查环上异或值是否一致（不一致则方案数=0）  

---

#### 4. C++核心代码实现赏析
**通用核心实现（基于题解一）**  
```cpp
#include <cstdio>
#include <cstring>
#define ll long long
#define N 200010
const int mod = 1e9+7;

ll mul[N], hf; // mul: 预计算幂次； hf: 矛盾标记
int f[N], fv[N], ans; // f:父节点；fv:到父节点异或值；ans:连通块数

int getfa(int x) {
    if (f[x] == x) return x;
    int root = getfa(f[x]);
    fv[x] ^= fv[f[x]]; // 路径压缩时更新异或值
    return f[x] = root;
}

void uni(int u, int v, int w) {
    int ru = getfa(u), rv = getfa(v);
    if (ru == rv) {
        if (fv[u] ^ fv[v] ^ w) hf = 0; // 检查环上异或一致性
        return;
    }
    f[ru] = rv;
    fv[ru] = fv[u] ^ fv[v] ^ w; // 调整权值使u⊕v=w
    ans--; // 连通块减少
}
```

**题解一核心片段赏析**  
```cpp
void uni(int u, int v, int w) {
    // ... 获取根节点
    if (ru == rv) {
        if (fv[u] ^ fv[v] ^ w) hf = 0;
        return;
    }
    f[ru] = rv;
    fv[ru] = fv[u] ^ fv[v] ^ w; // 关键权值调整
    ans--;
}
```
> **解读**：当合并两个连通块时，通过调整新边权值`fv[ru]`，使得从`u`到`v`的路径异或值恰好等于约束`w`。若节点已连通，则验证现有路径是否满足`w`。  
> 💡 **学习笔记**：权值调整公式保证合并后任意节点到新根的路径异或值不变。

**题解二核心片段赏析**  
```cpp
int query(int x) {
    if (fa[x] == x) return 0;
    return lz[x] ^ query(fa[x]); // 递归计算到根异或值
}
```
> **解读**：`query`实时计算节点`x`到根的异或值。递归过程中累加路径上所有边的权值（`lz`存储到父节点的异或）。  
> 💡 **学习笔记**：递归查询避免显式存储路径，但需注意递归深度（可改为迭代）。

---

#### 5. 算法可视化：像素动画演示
**主题**：8-bit像素风《并查集探险》  
**核心演示**：动态展示节点合并、连通块染色与矛盾检测  

##### 动画设计细节：
1. **像素场景**  
   - **左侧**：网格视图，已知格子显示数字（如`(2,3):6`）  
   - **右侧**：节点图，行节点（蓝方块），列节点（黄方块）  
   - **控制面板**：开始/暂停/单步/速度滑块（FC手柄风格）

2. **关键动效与音效**  
   | 事件                | 视觉表现                          | 音效            |
   |---------------------|----------------------------------|----------------|
   | 添加已知值           | 网格闪烁+节点间画线（显示权值）     | "叮"（电子音）  |
   | 合并连通块           | 小连通块飞向大连通块（同色染色）    | "咔嚓"（拼合音）|
   | 发现矛盾            | 屏幕红光闪烁                      | 低沉错误音      |
   | 完成计算            | 连通块脉冲发光+方案数像素字体弹出  | 胜利旋律        |

3. **AI自动演示模式**  
   - 点击"AI"按钮：节点自动按输入顺序合并，速度由滑块控制  
   - 关键步骤暂停：合并前显示`fv[u]^fv[v]^w`计算过程  
   - 实时数据显示：当前连通块数`ans`和方案数  

**设计思路**：像素风格降低理解压力，游戏化反馈（音效/动画）强化学习动机。路径验证环节的逐步展示帮助理解带权并查集核心机制。

---

#### 6. 拓展练习与相似问题思考
1. **通用技巧迁移**  
   异或约束系统建模适用于：  
   - 位运算方程组（如`x⊕y=1`）  
   - 图论中的环约束（如判断异或环合法性）  
   - 集合关系表示（如扩展域并查集）  

2. **洛谷习题推荐**  
   - **P2024 [NOI2001]食物链**  
     > 带权并查集经典！用模3运算维护三种生物关系，巩固权值调整技巧。  
   - **P1525 [NOIP2010]关押罪犯**  
     > 二分图判定+并查集应用，学会将冲突转化为约束边。  
   - **P1892 [BOI2003]团伙**  
     > 扩展域并查集实战，理解"朋友域"和"敌人域"的拆分思想。

---

#### 7. 学习心得与经验分享
> **来自larsr的经验**：  
> "最初纠结于网格直接计算，后来意识到图论转化才是关键。调试时打印`f`和`fv`数组极大帮助验证路径正确性。"  
>  
> **Kay点评**：  
> 复杂问题常需跳出直观，寻找更抽象的模型（如本题的节点图）。调试时可视化中间状态（如并查集树）是高效定位错误的秘诀。

---

通过本指南，我们深入解析了异或约束系统的并查集解法精髓。记住：将复杂约束分解为节点与边，用并查集维护连通性与权值，你就能破解此类难题！🚀

---
处理用时：256.80秒