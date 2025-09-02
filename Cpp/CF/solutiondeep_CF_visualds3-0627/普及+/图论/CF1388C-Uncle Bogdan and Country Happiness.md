# 题目信息

# Uncle Bogdan and Country Happiness

## 题目描述

Uncle Bogdan is in captain Flint's crew for a long time and sometimes gets nostalgic for his homeland. Today he told you how his country introduced a happiness index.

There are $ n $ cities and $ n−1 $ undirected roads connecting pairs of cities. Citizens of any city can reach any other city traveling by these roads. Cities are numbered from $ 1 $ to $ n $ and the city $ 1 $ is a capital. In other words, the country has a tree structure.

There are $ m $ citizens living in the country. A $ p_i $ people live in the $ i $ -th city but all of them are working in the capital. At evening all citizens return to their home cities using the shortest paths.

Every person has its own mood: somebody leaves his workplace in good mood but somebody are already in bad mood. Moreover any person can ruin his mood on the way to the hometown. If person is in bad mood he won't improve it.

Happiness detectors are installed in each city to monitor the happiness of each person who visits the city. The detector in the $ i $ -th city calculates a happiness index $ h_i $ as the number of people in good mood minus the number of people in bad mood. Let's say for the simplicity that mood of a person doesn't change inside the city.

Happiness detector is still in development, so there is a probability of a mistake in judging a person's happiness. One late evening, when all citizens successfully returned home, the government asked uncle Bogdan (the best programmer of the country) to check the correctness of the collected happiness indexes.

Uncle Bogdan successfully solved the problem. Can you do the same?

More formally, You need to check: "Is it possible that, after all people return home, for each city $ i $ the happiness index will be equal exactly to $ h_i $ ".

## 说明/提示

Let's look at the first test case of the first sample:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/001794ade043a3f0f7ed603305eb551246689207.png)At first, all citizens are in the capital. Let's describe one of possible scenarios:

- a person from city $ 1 $ : he lives in the capital and is in good mood;
- a person from city $ 4 $ : he visited cities $ 1 $ and $ 4 $ , his mood was ruined between cities $ 1 $ and $ 4 $ ;
- a person from city $ 3 $ : he visited cities $ 1 $ and $ 3 $ in good mood;
- a person from city $ 6 $ : he visited cities $ 1 $ , $ 3 $ and $ 6 $ , his mood was ruined between cities $ 1 $ and $ 3 $ ;

 In total, - $ h_1 = 4 - 0 =         4 $ ,
- $ h_2 = 0 $ ,
- $ h_3 = 1 - 1 = 0 $ ,
- $ h_4 = 0 - 1 = -1 $ ,
- $ h_5 = 0 $ ,
- $ h_6 = 0 - 1 = -1 $ ,
- $ h_7 = 0 $ .

The second case of the first test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/a9264c4828a85c9989a95ed8604e23cfb9f3dcda.png)All people have already started in bad mood in the capital — this is the only possible scenario.

The first case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/b8bbd8cbfa8f12355a17c596fd18bc65433a619c.png)The second case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/5c48a1551b8fe0dc0edc02bc5782fb0068b84587.png)It can be proven that there is no way to achieve given happiness indexes in both cases of the second test.

## 样例 #1

### 输入

```
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5```

### 输出

```
YES
YES```

## 样例 #2

### 输入

```
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3```

### 输出

```
NO
NO```

# AI分析结果



### 算法分类
树形动态规划（DFS遍历与条件验证）

---

### 题解思路与核心难点分析

#### 核心思路
1. **两次DFS遍历**  
   - **第一次DFS**：计算每个节点经过的总人数（包含子树的所有路径）
   - **第二次DFS**：验证三个关键条件：
     - 条件1：$|h_i| \leq p_i$（情绪差不超过总人数）
     - 条件2：$(p_i - h_i) \equiv 0 \pmod{2}$（奇偶性一致）
     - 条件3：子树高兴人数总和 $\leq$ 当前节点高兴人数

2. **数学推导**  
   通过方程组 $good + bad = p_i$ 和 $good - bad = h_i$，可得：
   - $good = (p_i + h_i)/2$
   - $bad = (p_i - h_i)/2$

#### 解决难点
1. **树形结构约束**：需确保父节点的高兴人数足够覆盖所有子节点的高兴人数（否则说明存在矛盾的情绪变化路径）。
2. **全局合法性验证**：必须同时满足三个条件，任何节点违反任一条件则全局无解。

---

### 题解评分（≥4星）

| 题解作者 | 评分 | 关键亮点 |
|---------|------|---------|
| fls233666 | ★★★★★ | 清晰的两次DFS设计，条件验证逻辑完整 |
| F_Mu      | ★★★★☆ | 简洁的递归实现，数学推导明确 |
| 白鲟      | ★★★★☆ | 逆向思维（坏情绪约束），代码高效 |

---

### 最优思路与技巧提炼

1. **两次DFS分层处理**  
   - 第一层计算总人数，第二层验证条件，避免状态交叉。
2. **条件验证顺序优化**  
   先检查局部条件（条件1、2），再处理子树条件（条件3），提高剪枝效率。
3. **数学公式直接计算**  
   通过方程组直接求解高兴/坏情绪人数，避免复杂状态转移。

---

### 同类型题推荐
1. **CF 915E**：树形结构动态约束验证
2. **洛谷 P1351**：树形DP与条件组合
3. **LeetCode 1245**：树的直径与路径约束

---

### 可视化与算法演示设计

#### 核心动画流程
1. **第一次DFS（总人数计算）**  
   - **节点颜色**：初始白色 → 计算完成后变为绿色。
   - **数值显示**：节点旁动态显示累计的 $p_i$ 值。
   - **遍历路径**：用蓝色高亮当前DFS路径。

2. **第二次DFS（条件验证）**  
   - **条件1验证**：若失败，节点闪烁红色并显示 $|h_i| > p_i$。
   - **条件2验证**：奇偶性错误时，节点显示黄色叹号。
   - **条件3验证**：子树高兴人数超过父节点时，父子连线变为红色。

#### 复古像素风格实现
- **颜色方案**：使用16色调色板（如绿色代表合法，红色代表错误）。
- **音效设计**：
  - **计算完成**：8-bit "完成"音效（频率上升）。
  - **条件失败**：短促的"错误"音效（低频脉冲）。
- **自动演示**：按空格键切换手动/自动模式，自动模式下算法以固定速度逐步执行。

#### 交互示例（伪代码）
```javascript
class Node {
  constructor(id, p, h) {
    this.x = random(100, 700); // 像素坐标
    this.y = random(100, 500);
    this.p = p; // 总人数
    this.h = h; // 情绪差
  }
  
  draw() {
    // 绘制8位风格节点
    fillSprite(this.x, this.y, this.color);
    drawText(this.p, this.x + 8, this.y + 8);
  }
}

function dfs1(node) {
  node.children.forEach(child => {
    dfs1(child);
    node.p += child.p; // 累计子树人数
  });
  playSound('blip'); // 每次计算完成播放音效
}
```

---

### 关键代码片段（fls233666题解）

```cpp
void dfs1(int rp) { // 第一次DFS：计算总人数
  for (auto child : tree[rp]) {
    if (!visited[child]) {
      visited[child] = true;
      dfs1(child);
      p[rp] += p[child];
    }
  }
}

void ck(int rp) { // 第二次DFS：验证条件
  if (h[rp] > p[rp] || (p[rp] - h[rp]) % 2) {
    ans = false; return;
  }
  int hp = (p[rp] + h[rp]) / 2; // 计算高兴人数
  int sum = 0;
  for (auto child : tree[rp]) {
    sum += child_hp[child]; // 累加子树高兴人数
  }
  if (sum > hp) ans = false; // 条件3验证
}
```

---

### 总结与扩展
该问题的核心在于树形结构的全局约束验证，通过分层DFS和数学推导可高效解决。类似问题可借鉴条件分阶段验证的思路，优先处理局部约束再处理全局依赖。

---
处理用时：79.98秒