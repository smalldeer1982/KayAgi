# 题目信息

# [ABC348E] Minimize Sum of Distances

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc348/tasks/abc348_e

$ N $ 頂点からなる木が与えられます。頂点は $ 1 $ から $ N $ までの番号がついており、 $ i $ 番目の辺は頂点 $ A_i,\ B_i $ を結んでいます。

長さ $ N $ の正整数列 $ C\ =\ (C_1,\ C_2,\ \ldots\ ,C_N) $ が与えられます。$ d(a,\ b) $ を頂点 $ a,\ b $ の間にある辺の数とし、 $ x\ =\ 1,\ 2,\ \ldots\ ,N $ に対して $ \displaystyle\ f(x)\ =\ \sum_{i=1}^{N}\ (C_i\ \times\ d(x,\ i)) $ とします。$ \displaystyle\ \min_{1\ \leq\ v\ \leq\ N}\ f(v) $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 与えられるグラフは木である。
- $ 1\ \leq\ C_i\ \leq\ 10^9 $

### Sample Explanation 1

例として、 $ f(1) $ を求めることを考えます。$ d(1,\ 1)\ =\ 0,\ d(1,\ 2)\ =\ 1,\ d(1,\ 3)\ =\ 1,\ d(1,\ 4)\ =\ 2 $ です。 よって、 $ f(1)\ =\ 0\ \times\ 1\ +\ 1\ \times\ 1\ +\ 1\ \times\ 1\ +\ 2\ \times\ 2\ =\ 6 $ となります。 同様に、 $ f(2)\ =\ 5,\ f(3)\ =\ 9,\ f(4)\ =\ 6 $ です。$ f(2) $ が最小なので `5` を出力します。

### Sample Explanation 2

$ f(2)\ =\ 1 $ で、これが最小です。

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1 1 1 2```

### 输出

```
5```

## 样例 #2

### 输入

```
2
2 1
1 1000000000```

### 输出

```
1```

## 样例 #3

### 输入

```
7
7 3
2 5
2 4
3 1
3 6
2 1
2 7 6 9 3 4 6```

### 输出

```
56```

# AI分析结果



**唯一算法分类**  
树形DP/换根DP

---

### 综合分析与结论  
**核心思路**  
通过两次DFS实现换根DP：  
1. 第一次DFS计算以根节点为基准的初始答案和子树权值和  
2. 第二次DFS通过转移方程 `f(child) = f(parent) + total - 2*subtree[child]` 推导所有节点答案  
**关键难点**  
- 推导距离变化对总和的影响：子树节点距离-1（贡献减少subtree[child]），非子树节点距离+1（贡献增加total-subtree[child]）  
- 将时间复杂度从O(N²)优化到O(N)的数学建模  
**可视化设计**  
- **颜色标记**：子树节点用蓝色高亮，非子树节点用黄色  
- **动画流程**：  
  1. 展示初始根节点的子树划分  
  2. 移动根节点时用箭头表示方向  
  3. 用颜色闪烁表示总和变化量（蓝色区域减少，黄色区域增加）  
  4. 显示当前节点的总贡献值  
- **复古风格**：用16色像素网格表示树结构，音效在换根时播放8-bit音效  

---

### 题解清单（≥4星）  
1. **作者：f_hxr_（5星）**  
   - 亮点：图解清晰，代码含注释，八倍经验验证  
   - 关键代码：  
     ```cpp
     void solve(int u,int fa,long long ans){
         f[u]=ans;
         for(int i=head[u];i;i=nxt[i]){
             int v=to[i];if(v==fa)continue;
             long long dans=ans - sz[v] + (ALL - sz[v]);
             solve(v,u,dans);
         }
     }
     ```

2. **作者：___PatrickChen___（4.5星）**  
   - 亮点：公式推导简练，代码变量命名规范  
   - 关键代码：  
     ```cpp
     void dfs2(int u, int fa){
         if(u != 1) f[u] = f[fa] - s[u] + s[1] - s[u];
         for(int v : G[u]) if(v != fa) dfs2(v, u);
     }
     ```

3. **作者：Fiendish（4星）**  
   - 亮点：动态转移方程显式写出，处理溢出警告  
   - 关键代码：  
     ```cpp
     f[v] = f[u] + sum - 2*num[v];
     ```

---

### 最优思路或技巧提炼  
1. **两次DFS架构**  
   - 第一次DFS：计算初始答案`f(1)`和子树权值`siz[]`  
   - 第二次DFS：基于父节点答案递推子节点  
2. **转移方程本质**  
   `新贡献 = 父贡献 + 总权值 - 2*子权值`，反映子树内外权值变化  
3. **预处理总权值**  
   将`total = ΣC_i`作为全局变量避免重复计算  

---

### 同类型题与算法套路  
**通用解法**  
- 问题特征：树结构 + 需要所有节点的某种距离相关统计量  
- 固定模式：  
  1. 计算根节点答案和子树统计量  
  2. 设计换根时的增量更新公式  
**同类题目**  
- CF1092F（权值距离和）  
- P3478（普通距离和）  
- P2986（带边权版本）  

---

### 推荐相似题目  
1. [CF1092F. Tree with Maximum Cost](https://www.luogu.com.cn/problem/CF1092F)  
2. [P3478 [POI2008] STA-Station](https://www.luogu.com.cn/problem/P3478)  
3. [P2986 [USACO10MAR] Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)  

---

### 个人心得摘录  
1. **调试教训**  
   - 作者"Fiendish"提到初始值需设为`9e18`避免WA，反映数据规模的重要性  
2. **顿悟时刻**  
   - 作者"f_hxr_"通过画图发现子树内外贡献变化的对称性，将复杂推导简化为`total-2*subtree`  

---

### 可视化算法演示（像素版）  
**HTML/JS核心逻辑**  
```javascript
class PixelTreeAnim {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.nodes = []; // 存储节点像素坐标
    this.highlight = null; // 当前高亮节点
    this.playSound = (type) => { /* 音效触发逻辑 */ };
  }

  drawStep(node, fValue) {
    // 绘制当前节点为16x16像素方块
    this.ctx.fillStyle = '#00F'; // 蓝色表示子树
    drawNode(node);
    this.ctx.fillText(`f=${fValue}`, node.x*32, node.y*32+16);
    this.playSound('move');
  }

  async runDFS(root) {
    // 模拟DFS过程，步进延迟500ms
    for(const child of root.children) {
      this.drawStep(child, calculateF(child));
      await new Promise(r => setTimeout(r, 500));
    }
  }
}
```

**动画特性**  
- **颜色编码**：当前节点红色，子树蓝色，非子树黄色  
- **音效设计**：  
  - 换根时播放`beep`音（Web Audio API生成300Hz方波）  
  - 找到最小值时播放胜利音效  
- **自动演示**：按DFS顺序自动遍历，支持暂停/继续  

---

### 完整代码示例  
**基于作者f_hxr_的C++实现**  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;
typedef long long ll;
vector<int> G[maxn];
ll C[maxn], siz[maxn], f[maxn], total;

void dfs1(int u, int fa, ll dep) {
    f[1] += C[u] * dep;
    siz[u] = C[u];
    for(int v : G[u]) if(v != fa) {
        dfs1(v, u, dep+1);
        siz[u] += siz[v];
    }
}

void dfs2(int u, int fa) {
    for(int v : G[u]) if(v != fa) {
        f[v] = f[u] + total - 2*siz[v];
        dfs2(v, u);
    }
}

int main() {
    int n; cin >> n;
    for(int i=1; i<n; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1; i<=n; i++) {
        cin >> C[i];
        total += C[i];
    }
    dfs1(1, 0, 0);
    dfs2(1, 0);
    cout << *min_element(f+1, f+n+1);
}
```

---
处理用时：77.48秒