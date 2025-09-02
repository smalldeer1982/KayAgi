# 题目信息

# Santa's Gift

## 题目描述

Santa has an infinite number of candies for each of $ m $ flavours. You are given a rooted tree with $ n $ vertices. The root of the tree is the vertex $ 1 $ . Each vertex contains exactly one candy. The $ i $ -th vertex has a candy of flavour $ f_i $ .

Sometimes Santa fears that candies of flavour $ k $ have melted. He chooses any vertex $ x $ randomly and sends the subtree of $ x $ to the Bakers for a replacement. In a replacement, all the candies with flavour $ k $ are replaced with a new candy of the same flavour. The candies which are not of flavour $ k $ are left unchanged. After the replacement, the tree is restored.

The actual cost of replacing one candy of flavour $ k $ is $ c_k $ (given for each $ k $ ). The Baker keeps the price fixed in order to make calculation simple. Every time when a subtree comes for a replacement, the Baker charges $ C $ , no matter which subtree it is and which flavour it is.

Suppose that for a given flavour $ k $ the probability that Santa chooses a vertex for replacement is same for all the vertices. You need to find out the expected value of error in calculating the cost of replacement of flavour $ k $ . The error in calculating the cost is defined as follows.

 $ $$$ Error\ E(k) =\ (Actual Cost\ –\ Price\ charged\ by\ the\ Bakers) ^ 2. $ $ </p><p>Note that the actual cost is the cost of replacement of one candy of the flavour  $ k $  multiplied by the number of candies in the subtree.</p><p>Also, sometimes Santa may wish to replace a candy at vertex  $ x $  with a candy of some flavour from his pocket.</p><p>You need to handle two types of operations: </p><ul> <li> Change the flavour of the candy at vertex  $ x $  to  $ w $ . </li><li> Calculate the expected value of error in calculating the cost of replacement for a given flavour  $ k$$$.

## 说明/提示

For $ 1 $ -st query, the error in calculating the cost of replacement for flavour $ 1 $ if vertex $ 1 $ , $ 2 $ or $ 3 $ is chosen are $ 66^2 $ , $ 66^2 $ and $ (-7)^2 $ respectively. Since the probability of choosing any vertex is same, therefore the expected value of error is $ \frac{66^2+66^2+(-7)^2}{3} $ .

Similarly, for $ 2 $ -nd query the expected value of error is $ \frac{41^2+(-7)^2+(-7)^2}{3} $ .

After $ 3 $ -rd query, the flavour at vertex $ 2 $ changes from $ 1 $ to $ 3 $ .

For $ 4 $ -th query, the expected value of error is $ \frac{(-7)^2+(-7)^2+(-7)^2}{3} $ .

Similarly, for $ 5 $ -th query, the expected value of error is $ \frac{89^2+41^2+(-7)^2}{3} $ .

## 样例 #1

### 输入

```
3 5 5 7
3 1 4
1 1
73 1 48 85 89
2 1
2 3
1 2 3
2 1
2 3
```

### 输出

```
2920.333333333333
593.000000000000
49.000000000000
3217.000000000000
```

# AI分析结果



---

## 唯一算法分类  
树链剖分

---

## 综合分析与结论  
### 核心算法流程  
1. **公式推导**：将期望误差展开为 $\frac{b_x^2 \sum S_i^2 - 2b_xC \sum S_i}{n} + C^2$，只需维护每个颜色的 $\sum S_i$（子树中该颜色的节点数之和）和 $\sum S_i^2$（平方和）。  
2. **树链剖分**：将树结构转化为线性序列，实现高效的路径操作（从任意节点到根的路径修改）。  
3. **动态开点线段树**：为每个颜色动态创建线段树，支持区间加法、平方和更新（利用 $\sum (x+v)^2 = \sum x^2 + 2v\sum x + nv^2$）。  

### 可视化设计  
- **树结构展示**：用像素化风格绘制树的层次结构，高亮当前操作路径（如修改节点颜色时，从节点到根的路径闪烁）。  
- **线段树动态生长**：当颜色首次被修改时，对应的线段树节点以像素方块形式动态生成，伴随 8-bit 音效。  
- **音效设计**：路径修改时播放 "blip" 音效，查询时播放 "success" 音效，错误操作触发 "error" 音效。  
- **自动演示模式**：模拟算法流程，逐步展示树剖分解、线段树更新，速度可调节。  

---

## 题解清单（≥4星）  
### 1. Alex_Wei（⭐⭐⭐⭐⭐）  
- **亮点**：公式推导简洁，代码高度优化（仅 44 行），动态开点线段树的 `push_down` 处理完整。  
- **核心代码**：  
  ```cpp
  void add(int x, int c, int v) {
    while(x) modify(1, n, dfn[top[x]], dfn[x], R[c], v), x = fa[top[x]];
  }
  ```
  
### 2. sgl654321（⭐⭐⭐⭐）  
- **亮点**：详细解释动态开点线段树的空间计算，提供调试建议（如 `push_down` 时新建节点）。  
- **核心代码**：  
  ```cpp
  void change(int id,int x,int dc) {
    for(;tp[x]!=1;x=f[tp[x]]) modif(rt[id],1,n,dfn[tp[x]],dfn[x],dc);
    modif(rt[id],1,n,1,dfn[x],dc);
  }
  ```

### 3. Leap_Frog（⭐⭐⭐⭐）  
- **亮点**：代码可读性强，使用结构体封装线段树节点，标记永久化实现清晰。  
- **核心代码**：  
  ```cpp
  struct node{ int ls,rs; ll tg; char ed; node vl; };
  void modif(int ql,int qr,int &x,int l,int r,int v) {
    if(!x) x=++node; // 动态开点逻辑
  }
  ```

---

## 最优思路或技巧提炼  
1. **公式拆解**：将平方误差拆解为线性项和平方项，避免直接计算复杂概率分布。  
2. **动态开点优化**：仅在修改时创建线段树节点，空间复杂度从 $O(mn)$ 降至 $O(m \log^2 n)$。  
3. **树剖路径分解**：将任意节点到根的路径拆分为 $O(\log n)$ 条重链，支持高效区间修改。  

---

## 同类型题与算法套路  
1. **路径统计问题**：如 [CF343D Water Tree](https://codeforces.com/problemset/problem/343/D)，需维护子树和。  
2. **动态开点应用**：如 [P3960 列队](https://www.luogu.com.cn/problem/P3960)，处理稀疏矩阵。  

---

## 推荐相似题目  
1. **P3384** [树链剖分模板](https://www.luogu.com.cn/problem/P3384)  
2. **P5142** [区间方差](https://www.luogu.com.cn/problem/P5142)（维护平方和）  
3. **CF343D** [Water Tree](https://codeforces.com/problemset/problem/343/D)（子树修改+路径查询）  

---

## 个人心得摘录  
> "调试时发现 `push_down` 必须新建节点，否则会丢失历史状态。动态开点的标记下传需特别谨慎。" —— sgl654321  
> "将树剖分解与动态开点结合，代码量骤降 50%！" —— Alex_Wei  

---

## 可视化与算法演示  
### 核心动画设计  
1. **树结构剖分**：  
   - 初始状态：树节点以绿色像素块表示，重边用黄色高亮。  
   - 路径修改：点击节点后，从该节点到根的路径变为红色，分解为多条重链（每段闪烁 3 次）。  

2. **线段树动态生长**：  
   - 修改颜色时，对应线段树的节点以蓝色像素块从左侧 "生长" 出来，伴随 "blip" 音效。  
   - 平方和更新：线段树节点数值变化时，显示公式 $\sum (x+v)^2$ 的浮动提示。  

3. **自动演示模式**：  
   - 点击 "Auto" 按钮后，算法自动执行路径修改和查询，速度可调节（1x/2x/5x）。  
   - 背景播放 8-bit 风格 BGM，成功查询时播放 "胜利" 音效。  

### 代码片段（伪代码）  
```javascript
// 树剖路径修改动画
function animatePathModify(node) {
  let chains = splitChain(node); // 分解为重链数组
  chains.forEach(chain => {
    chain.nodes.forEach(n => highlight(n, 'red', 500)); // 高亮重链节点
    drawSegmentTreeUpdate(chain.range); // 线段树区间更新动画
  });
}
```

---
处理用时：71.58秒