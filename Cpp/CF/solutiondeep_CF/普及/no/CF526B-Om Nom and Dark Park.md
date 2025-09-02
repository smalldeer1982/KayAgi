# 题目信息

# Om Nom and Dark Park

## 题目描述

Om Nom is the main character of a game "Cut the Rope". He is a bright little monster who likes visiting friends living at the other side of the park. However the dark old parks can scare even somebody as fearless as Om Nom, so he asks you to help him.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/131af3f0d0c50854dd04093b7cc403fcf25a1e8b.png)The park consists of $ 2^{n+1}-1 $ squares connected by roads so that the scheme of the park is a full binary tree of depth $ n $ . More formally, the entrance to the park is located at the square $ 1 $ . The exits out of the park are located at squares $ 2^{n},2^{n}+1,...,2^{n+1}-1 $ and these exits lead straight to the Om Nom friends' houses. From each square $ i $ ( $ 2<=i<2^{n+1} $ ) there is a road to the square ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/1a134f5ff0a48756afece69eeb883c670c5ab534.png). Thus, it is possible to go from the park entrance to each of the exits by walking along exactly $ n $ roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/f5acd0d816020c5e5a5f00b96e0b0428cadec703.png) To light the path roads in the evening, the park keeper installed street lights along each road. The road that leads from square $ i $ to square ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/1a134f5ff0a48756afece69eeb883c670c5ab534.png) has $ a_{i} $ lights.Om Nom loves counting lights on the way to his friend. Om Nom is afraid of spiders who live in the park, so he doesn't like to walk along roads that are not enough lit. What he wants is that the way to any of his friends should have in total the same number of lights. That will make him feel safe.

He asked you to help him install additional lights. Determine what minimum number of lights it is needed to additionally place on the park roads so that a path from the entrance to any exit of the park contains the same number of street lights. You may add an arbitrary number of street lights to each of the roads.

## 说明/提示

Picture for the sample test. Green color denotes the additional street lights.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526B/a991902237b78dc527346d24d4ba436bdc2cc2af.png)

## 样例 #1

### 输入

```
2
1 2 3 4 5 6
```

### 输出

```
5
```

# AI分析结果



# Om Nom and Dark Park

## 题目描述

Om Nom 是游戏《割绳子》的主角，他是一只聪明的小怪兽，喜欢拜访住在公园另一边的朋友。然而黑暗的老旧公园甚至能让无所畏惧的 Om Nom 感到害怕，因此他请求你的帮助。

公园由 $2^{n+1}-1$ 个正方形区域通过道路连接构成，其结构是一个深度为 $n$ 的满二叉树。具体来说，公园入口位于区域 1，出口位于区域 $2^n,2^n+1,...,2^{n+1}-1$，这些出口直通 Om Nom 朋友的家。从每个区域 $i$（$2 \leq i < 2^{n+1}$）都有一条道路通向区域 $\lfloor i/2 \rfloor$，因此从入口到任意出口恰好需要经过 $n$ 条道路。

公园管理员在每条道路上安装了路灯。连接区域 $i$ 到其父节点的道路有 $a_i$ 盏路灯。Om Nom 希望在前往任意朋友家的路径上，所有道路的灯光总数相同。请求出需要额外添加的最少路灯数量。

## 算法分类
贪心

---

## 题解对比与结论

### 核心思路
各题解均采用**自底向上递归**的贪心策略，核心思想为：
1. 对每个节点处理其左右子树路径和
2. 调整当前节点到子节点的边权，使左右子树路径和相等
3. 差值累加至总答案，确保局部最优解导向全局最优

### 最优题解亮点

#### 题解作者：q779（★★★★★）
**关键亮点**：
- 代码简洁高效，时间复杂度 $O(2^n)$
- 直接通过后序遍历递归，无需预处理
- 差值计算与路径和更新一气呵成

**核心代码**：
```cpp
int dfs(int x) {
    if(x > MX) return 0;
    int ls = dfs(x<<1), rs = dfs(x<<1|1);
    ans += abs(ls + a[x<<1] - (rs + a[x<<1|1]));
    return max(a[x<<1] + ls, a[x<<1|1] + rs);
}
```

#### 题解作者：Hooch（★★★★☆）
**关键亮点**：
- 显式分层处理，逻辑直观
- 注释清晰，解释父子节点权值调整关系

**核心代码**：
```cpp
inline int dfs(int d, int x) {
    if(d > m) return 0;
    int lson = dfs(d+1, x<<1), rson = dfs(d+1, x<<1|1);
    ans += abs((lson - rson) + (a[x<<1] - a[x<<1|1]));
    return max(lson + a[x<<1], rson + a[x<<1|1]);
}
```

---

## 关键技巧总结
1. **逆向贪心调整**：从叶子向根处理，确保每个节点的调整覆盖最大子树
2. **路径和差值计算**：`ans += abs(左路径和 - 右路径和)` 直接反映最小调整量
3. **递归返回值设计**：返回当前子树调整后的最大路径和，供上层节点使用

---

## 同类题目推荐
1. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)  
   （树形结构最优解问题）
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)  
   （树形DP与局部最优决策）
3. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220)  
   （贪心策略在路径问题中的应用）

---
处理用时：94.60秒