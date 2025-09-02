# 题目信息

# Bessie's Birthday Cake (Hard Version)

## 题目描述

[Proof Geometric Construction Can Solve All Love Affairs - manbo-p](https://soundcloud.com/alice-law-314125270/manbo-p-proof-geometric-construction-can-solve-all-love-affairs)

⠀



This is the hard version of the problem. The only difference between the two versions is the constraint on $ y $ . In this version $ 0 \leq y \leq n - x $ . You can make hacks only if both versions are solved.

Bessie has received a birthday cake from her best friend Elsie, and it came in the form of a regular polygon with $ n $ sides. The vertices of the cake are numbered from $ 1 $ to $ n $ clockwise. You and Bessie are going to choose some of those vertices to cut non-intersecting diagonals into the cake. In other words, the endpoints of the diagonals must be part of the chosen vertices.

Bessie would only like to give out pieces of cake which result in a triangle to keep consistency. The size of the pieces doesn't matter, and the whole cake does not have to be separated into all triangles (other shapes are allowed in the cake, but those will not be counted).

Bessie has already chosen $ x $ of those vertices that can be used to form diagonals. She wants you to choose no more than $ y $ other vertices such that the number of triangular pieces of cake she can give out is maximized.

What is the maximum number of triangular pieces of cake Bessie can give out?

## 说明/提示

In test cases $ 1 $ , $ 2 $ and $ 3 $ , you can get $ 6 $ , $ 5 $ and $ 2 $ non-intersecting triangular pieces of cake, respectively. A possible construction is shown in the following pictures:

The green dots represent vertices that Bessie chose, the yellow dots represent vertices that you chose, the blue lines represent diagonals that are drawn, and the red numbers represent triangles that are counted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C2/1d0397b12ffc5a0058affa34960ac433601c6be3.png)

## 样例 #1

### 输入

```
3
8 4 2
1 6 2 5
7 3 1
6 4 3
4 2 2
1 3```

### 输出

```
6
5
2```

# AI分析结果



【题目内容】
# 贝西的生日蛋糕（困难版）

## 题目描述

贝西从她最好的朋友艾尔西那里收到了一块生日蛋糕，蛋糕是一个正 $n$ 边形。顶点按顺时针方向编号为 $1$ 到 $n$。贝西和你将选择一些顶点，在这些顶点间切割互不相交的对角线，使得分出的三角形块数量最大化。贝西已经选择了 $x$ 个顶点，你可以再选择不超过 $y$ 个顶点。求能形成的最大三角形数量。

## 输入格式

多组测试数据。每组数据第一行为三个整数 $n, x, y$，第二行为 $x$ 个互不相同的整数表示已选顶点。

## 输出格式

每组数据输出一个整数表示最大三角形数量。

## 样例

### 输入
```
3
8 4 2
1 6 2 5
7 3 1
6 4 3
4 2 2
1 3
```

### 输出
```
6
5
2
```

---

【题解综合分析】

各题解核心思路均为**贪心处理相邻已选顶点的间隔**，优先选择能带来更高贡献的奇数长度间隔。关键技巧包括：

1. **间隔分类与排序**：将相邻顶点间的未选点间隔按奇偶性分类，优先处理奇数间隔。
2. **贪心填充策略**：在奇数间隔中，每个新增点可贡献 2 个三角形，完全填充时额外增加 1 个。
3. **贡献计算优化**：剩余可用点数用于偶数间隔，每个点稳定贡献 2 个三角形。

---

【高分题解推荐】

### 题解作者：littlebug（⭐⭐⭐⭐）
**关键亮点**：
- 清晰地将间隔分为奇偶两类，按从小到大排序处理。
- 处理奇数间隔时，完全填充可获得额外贡献。
- 代码结构简洁，包含详细的贡献计算逻辑。

**核心代码**：
```cpp
vector<int> eve; // 存储奇数间隔
sort(a + 1, a + x + 1); // 排序已选顶点

// 计算相邻顶点间隔
for (int i = 2; i <= x; ++i) {
    int k = a[i] - a[i-1] - 1;
    if (k % 2) eve.push_back(k);
}

// 处理奇数间隔
sort(eve.begin(), eve.end());
for (int k : eve) {
    if (y >= k / 2) {
        y -= k / 2;
        cnt += k;
    } else {
        cnt += y * 2;
        y = 0;
        break;
    }
}

// 剩余点数处理偶数间隔
cnt = min(n, cnt + y * 2);
cout << cnt - 2 << '\n'; // 初始x-2 + 新增贡献
```

### 题解作者：Angela2022（⭐⭐⭐⭐）
**关键亮点**：
- 提出基本图形（两已选点间的未选点段）概念，直观分析填充策略。
- 强调奇数段全填充的特殊贡献，代码实现严格分类处理。

**核心代码**：
```cpp
sort(d + 1, d + CNT + 1, cmp); // 按奇偶性排序

for (int i : 奇数段) {
    int need = i / 2; // 需要填充的点数
    if (y >= need) {
        cnt += need * 2 + 1; // 全填充额外+1
        y -= need;
    }
}
```

### 题解作者：hyman00（⭐⭐⭐）
**关键亮点**：
- 将间隔处理统一为奇偶两类，代码高度模块化。
- 对部分填充时的贡献计算有简洁的数学推导。

---

【最优思路总结】
1. **间隔计算与排序**：排序已选顶点，计算各间隔长度，奇偶分类后优先处理奇数段。
2. **贪心填充策略**：对每个奇数段，尽可能完全填充以激活额外贡献；剩余点数处理偶数段。
3. **贡献公式**：初始贡献为 $x-2$，每新增一个点最多贡献 2 个三角形（奇数段完全填充时额外 +1）。

---

【举一反三】
- **同类问题**：环形结构的最优覆盖（如 CF1110E），贪心处理间隔奇偶性。
- **算法套路**：间隔分类排序 + 贪心填充，适用于资源分配类问题。

---

【相似题目推荐】
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351) - 图论中的间隔贡献计算。
2. [CF1110E Magic Stones](https://www.luogu.com.cn/problem/CF1110E) - 环形结构的最优操作策略。
3. [P5021 赛道修建](https://www.luogu.com.cn/problem/P5021) - 贪心选择最优间隔进行资源分配。

---
处理用时：97.71秒