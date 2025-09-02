# 题目信息

# Love Triangles

## 题目描述

There are many anime that are about "love triangles": Alice loves Bob, and Charlie loves Bob as well, but Alice hates Charlie. You are thinking about an anime which has $ n $ characters. The characters are labeled from $ 1 $ to $ n $ . Every pair of two characters can either mutually love each other or mutually hate each other (there is no neutral state).

You hate love triangles (A-B are in love and B-C are in love, but A-C hate each other), and you also hate it when nobody is in love. So, considering any three characters, you will be happy if exactly one pair is in love (A and B love each other, and C hates both A and B), or if all three pairs are in love (A loves B, B loves C, C loves A).

You are given a list of $ m $ known relationships in the anime. You know for sure that certain pairs love each other, and certain pairs hate each other. You're wondering how many ways you can fill in the remaining relationships so you are happy with every triangle. Two ways are considered different if two characters are in love in one way but hate each other in the other. Print this count modulo $ 1000000007 $ .

## 说明/提示

In the first sample, the four ways are to:

- Make everyone love each other
- Make 1 and 2 love each other, and 3 hate 1 and 2 (symmetrically, we get 3 ways from this).

In the second sample, the only possible solution is to make 1 and 3 love each other and 2 and 4 hate each other.

## 样例 #1

### 输入

```
3 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 1
```

### 输出

```
0
```

# AI分析结果



### 唯一算法分类：无算法分类

---

### 综合分析与结论
题目核心是将爱恨关系转化为图论模型，判断约束一致性并统计连通块数量。关键点如下：
1. **模型转换**：将爱边视为同一集合，恨边视为不同集合，转化为带权并查集或二分图问题。
2. **矛盾检测**：若存在冲突约束（如奇环、矛盾边），则无解。
3. **连通块统计**：最终答案为 `2^(连通块数-1) % MOD`，每个连通块有两种相对状态选择。

**可视化设计思路**：
- **像素风格动画**：用方格表示节点，颜色区分不同集合（如蓝色代表集合A，红色代表集合B）。
- **合并过程展示**：动态绘制并查集合并操作，连线颜色表示爱（绿色）或恨（橙色）。
- **矛盾触发音效**：当检测到矛盾时播放错误音效，方格闪烁红色。
- **自动演示模式**：逐步展示每个输入的边如何影响节点关系，并最终输出连通块数。

---

### 题解清单 (≥4星)
1. **Cry_For_theMoon（5星）**  
   - **亮点**：使用带权并查集高效处理关系，代码简洁，逻辑严谨。  
   - **关键代码**：通过异或操作维护节点到根的距离，巧妙处理爱恨约束。

2. **Brioche（4星）**  
   - **亮点**：通过二分图染色模型直观解释问题，DFS判断奇环。  
   - **关键代码**：递归染色过程中动态检测矛盾。

3. **esquigybcu（4星）**  
   - **亮点**：扩展并查集（2n节点）清晰分离集合关系，易于理解。  
   - **关键代码**：通过合并 `i` 与 `j+n` 处理恨边约束。

---

### 最优思路/技巧提炼
1. **带权并查集**：用 `d[x]` 表示节点到根的异或距离，爱边对应 `d[x]^d[y]=0`，恨边对应 `d[x]^d[y]=1`。
2. **二分图染色**：爱边强制同色，恨边强制异色，DFS染色检测合法性。
3. **连通块计数**：每个连通块独立确定状态，最终方案数为 `2^(k-1)`（k为连通块数）。

---

### 同类型题与算法套路
1. **并查集模型**：处理元素分组与动态约束（如[P2024 食物链](https://www.luogu.com.cn/problem/P2024)）。
2. **二分图判定**：检测奇环或约束冲突（如[P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)）。
3. **连通块计数**：统计独立子图数量（如[P1197 星球大战](https://www.luogu.com.cn/problem/P1197)）。

---

### 推荐相似题目
1. [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)  
   **相似点**：二分答案+恨边约束模型。
2. [P1892 团伙](https://www.luogu.com.cn/problem/P1892)  
   **相似点**：扩展并查集处理朋友/敌人关系。
3. [CF862B Mahmoud and Ehab and the bipartiteness](https://codeforces.com/problemset/problem/862/B)  
   **相似点**：二分图性质与边数统计。

---

### 核心代码实现（带权并查集）
```cpp
int Find(int x) {
    if (fa[x] == x) return x;
    int rt = Find(fa[x]);
    d[x] ^= d[fa[x]]; // 路径压缩时更新异或距离
    return fa[x] = rt;
}

void merge(int u, int v, int w) {
    int ru = Find(u), rv = Find(v);
    if (ru == rv) {
        if ((d[u] ^ d[v]) != w) exit(0); // 检测矛盾
    } else {
        d[ru] = d[u] ^ d[v] ^ w; // 按约束合并
        fa[ru] = rv;
    }
}
```

---

### 可视化与复古游戏化设计
1. **像素风格界面**：  
   - **Canvas绘制**：节点为16x16像素方块，边为动态连线。
   - **颜色编码**：爱边（绿色）、恨边（橙色）、矛盾（红色闪烁）。

2. **音效设计**：  
   - **合并成功**：8-bit “滴”声。
   - **检测矛盾**：短促“哔”声伴随红色闪光。

3. **自动演示逻辑**：  
   ```javascript
   function autoPlay(edges) {
       edges.forEach(([u, v, w], step) => {
           highlightNodes(u, v); // 高亮当前边
           applyEdgeConstraint(u, v, w); // 更新并查集
           if (checkConflict()) playErrorSound();
           delay(1000); // 步进间隔
       });
       showResult(Math.pow(2, countComponents() - 1)); // 显示答案
   }
   ```

---

### 个人心得摘录
> **Cry_For_theMoon**：  
> “带权并查集的异或操作天然适合处理二元关系，将爱恨约束转化为数学运算，避免复杂判断。”  
>   
> **Brioche**：  
> “DFS染色时忘记处理反向边，调试半天才发现递归参数传递错误，教训深刻。”

---
处理用时：60.24秒