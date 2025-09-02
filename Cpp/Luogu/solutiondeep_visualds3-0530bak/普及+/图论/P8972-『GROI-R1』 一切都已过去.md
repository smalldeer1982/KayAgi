# 题目信息

# 『GROI-R1』 一切都已过去

## 题目背景

悦关上窗，拉上帘布。

果然还是想不起来啊。

隐约记得曾和什么人一起做过这样的事。

仰面躺下，手执一只木笺。

「究竟如何，才能拥有“过去”啊……」

她闭上双眼。

「6 岁前的记忆……究竟如何才能寻回？」

## 题目描述

悦正在寻找她的记忆。忽然，她来到了有 $n$ 个节点的一棵树上。树上每一条边都有各自边权，每一个点都有各自的点权。

「把经历都聚拢起来，能完整地复原吗……」

悦从树上的一个点，慢慢地走到了另一个点，可是她什么也没找到。但是，她不知道，玘一直在远处望着她走过的道路。

玘发现，悦全程****没有走回头路****。他想把悦****走过的每一条边的边权乘起来****，可惜他发现他遇到了一个这一生未曾见到过的数字。

「为什么会这样呢？」

玘想到悦是突然出现在树上的，最初的点一定有蹊跷！他****把最初那个点的点权乘上****……

突然，一束彼岸花的红光亮起！世界重新安静了下来。

悦看到了玘留下的字样，可惜她不能从中看出任何过去的记忆。现在，你要帮她判断：把经历都聚拢起来，****能完整地复原过去吗****？我们称悦的一条路径能“复原过去”，当且仅当玘****留下的乘积是一个整数****。

**形式化题面**

给定一棵 $n$ 个节点的树和 $q$ 次询问。每次询问给出两个整数 $x,y$，表示询问树上以 $x$ 和 $y$ 为端点的简单路径上边权乘积与点 $x$ 的点权相乘是否为整数。

## 说明/提示

**样例解释**

根据输入可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3e4jqu6f.png)

对于第一个询问 $(1,5)$ 可以发现悦经过的边的边权分别是 $0.1$ 和 $0.99$，她出发的 $1$ 号点的点权为 $1$。$1\times0.1\times0.99=0.099$ 不是整数。所以输出 `No`。

对于后面两次询问同理。

**数据范围**

**本题采用捆绑测试。**

| 子任务编号 | 数据范围 | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $\text{Subtask1}$ | $n,q\le3\times 10^3$ |  | $15$ |
| $\text{Subtask2}$ | $n\le500$，$q\le10^5$ |  | $10$ |
| $\text{Subtask3}$ | $n,q\le10^5$ | $\text{BE}$ | $10$ |
| $\text{Subtask4}$ | $n,q\le10^5$ | $\text{A}$ | $5$ |
| $\text{Subtask5}$ | $n,q\le10^5$ | $\text{B}$ | $10$ |
| $\text{Subtask6}$ | $n,q\le10^5$ | $\text{C}$ | $5$ |
| $\text{Subtask7}$ | $n,q\le10^5$ | $\text{D}$ | $10$ |
| $\text{Subtask8}$ | $n,q\le2×10^5$ |  | $35$ |

特殊性质 $\text{A}$：保证树退化成一条链。

特殊性质 $\text{B}$：保证树随机生成（即对于每一个节点随机选择它的父亲节点）。

特殊性质 $\text{C}$：保证 $w\in\{0.1,0.3,0.5,0.7,0.9\}$。

特殊性质 $\text{D}$：保证 $w\in\{0.1,0.2,0.3,0.4,0.6,0.7,0.8,0.9\}$。

特殊性质 $\text{E}$：保证 $w\le2$ 且 $w$ 小数位数不超过 $1$ 位。

对于 $100\%$ 的数据满足 $1\le n,q\le2\times10^5$，$0\le a_i\le10^9$，$0\le w\le10^4$，$1\le u,v,x,y\le n$，$x\ne y$，$w$ 小数位数不超过 $4$ 位。

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
1 2 0.1
2 3 0.20
3 4 0.5
2 5 0.99
1 5
1 4
4 3```

### 输出

```
No
No
Yes```

# AI分析结果



**唯一算法分类**：LCA（最近公共祖先）与数论分解质因数结合

---

### **题解思路与核心难点**
1. **核心算法流程**：
   - **浮点数转整数**：所有边权乘 $10^4$ 消除小数位，记录小数位数（如 0.1 → 1 × 10^1，小数位数为1）
   - **质因数分解**：统计每条边权中2和5的因子数，例如 0.1 → 1 → 分解后无2和5因子
   - **预处理路径**：通过DFS预处理每个节点到根的路径上：
     - 总小数位数之和（`sum[u]`）
     - 因子2的总数（`two[u]`）
     - 因子5的总数（`five[u]`）
   - **LCA查询**：利用LCA计算路径上的 `sum/two/five` 差值，判断 $\min(two, five) \geq sum$

2. **解决难点**：
   - **精度爆炸**：通过质因数分解代替直接计算乘积
   - **路径查询**：LCA优化路径统计至 $O(\log n)$ 时间
   - **0的特殊处理**：将0的因子数设为极大值，确保直接返回Yes

---

### **题解评分 (≥4星)**
1. **迟暮天复明** (⭐⭐⭐⭐⭐)
   - 亮点：代码简洁，提出「分子分母因子抵消」的数学证明，预处理与LCA结合清晰
   - 核心代码：
     ```cpp
     int lca = LCA(x, y);
     int total_2 = two[x] + two[y] - 2 * two[lca] + count_two(a[x]);
     int total_5 = five[x] + five[y] - 2 * five[lca] + count_five(a[x]);
     ```

2. **Stars_visitor_tyw** (⭐⭐⭐⭐)
   - 亮点：单独处理0的计数，新增`zero[]`数组，逻辑更鲁棒
   - 核心代码：
     ```cpp
     if (zero[x] + zero[y] - 2 * zero[lca] > 0) return Yes;
     ```

3. **TernaryTree** (⭐⭐⭐⭐)
   - 亮点：结构体封装质因数统计，代码可扩展性强
   - 核心代码：
     ```cpp
     struct T { int two, five, digits; };
     T operator + (T a, T b) { ... } // 重载运算符统计路径
     ```

---

### **最优思路与技巧提炼**
- **质因数替代法**：将浮点数精度问题转化为2/5因子数的比较
- **LCA差分优化**：通过 `two[u] + two[v] - 2 * two[lca]` 快速计算路径总和
- **0的特殊标记**：用极大值表示无穷因子数，简化判断逻辑

---

### **类似题目推荐**
1. [AT_agc047_a](https://www.luogu.com.cn/problem/AT_agc047_a)：判断多个浮点数乘积是否为整数
2. [CF1114E](https://codeforces.com/problemset/problem/1114/E)：质因数分解与路径查询结合
3. [P4281](https://www.luogu.com.cn/problem/P4281)：LCA基础应用

---

### **可视化与算法演示**
**动画设计**：
1. **树结构展示**：用Canvas绘制树形结构，节点标注 `(two, five, sum)`
2. **路径高亮**：点击节点x和y时，高亮其到LCA的路径，显示路径上各边的统计值
3. **因子比较**：动态显示路径总`two/five`与`sum`，用颜色区分是否满足条件
4. **复古像素风**：用8位风格渲染树节点，点击时播放「选择音效」，正确/错误时播放不同音效

**代码片段**（伪代码）：
```javascript
// 伪代码：路径统计可视化
function highlightPath(x, y) {
  let lca = findLCA(x, y);
  let path = getPath(x, lca).concat(getPath(y, lca));
  path.forEach(node => {
    node.color = "#FFD700"; // 金色高亮
    playSound("select.wav"); // 8位音效
  });
  showResult(min(totalTwo, totalFive) >= totalSum);
}
```

---

### **个人心得摘录**
> "WA了13次才意识到0的处理：边权为0时无论其他值如何都直接返回Yes，必须单独维护`zero[]数组或标记极大值" —— User_leo

---

### **核心代码实现**
```cpp
// 预处理DFS（以Stars_visitor_tyw代码为例）
void dfs(int u, int fa) {
    for (auto edge : tree[u]) {
        int v = edge.to;
        if (v == fa) continue;
        sum[v] = sum[u] + edge.decimal_places;
        two[v] = two[u] + count_two(edge.w);
        five[v] = five[u] + count_five(edge.w);
        zero[v] = zero[u] + (edge.w == 0);
        dfs(v, u);
    }
}

// LCA查询判断
bool isIntegerPath(int x, int y) {
    int lca = findLCA(x, y);
    int total_decimal = sum[x] + sum[y] - 2 * sum[lca];
    int total_two = two[x] + two[y] - 2 * two[lca];
    int total_five = five[x] + five[y] - 2 * five[lca];
    return (min(total_two, total_five) >= total_decimal) || (zero[x] + zero[y] - 2 * zero[lca] > 0);
}
```

---
处理用时：71.58秒