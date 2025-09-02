# 题目信息

# Berserk Monsters

## 题目描述

Monocarp is playing a computer game (yet again). Guess what is he doing? That's right, killing monsters.

There are $ n $ monsters in a row, numbered from $ 1 $ to $ n $ . The $ i $ -th monster has two parameters: attack value equal to $ a_i $ and defense value equal to $ d_i $ . In order to kill these monsters, Monocarp put a berserk spell on them, so they're attacking each other instead of Monocarp's character.

The fight consists of $ n $ rounds. Every round, the following happens:

- first, every alive monster $ i $ deals $ a_i $ damage to the closest alive monster to the left (if it exists) and the closest alive monster to the right (if it exists);
- then, every alive monster $ j $ which received more than $ d_j $ damage during this round dies. I. e. the $ j $ -th monster dies if and only if its defense value $ d_j $ is strictly less than the total damage it received this round.

For each round, calculate the number of monsters that will die during that round.

## 说明/提示

Explanation for the first test case of the example:

During the first round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 2 $ ;
- the monster $ 2 $ deals $ 4 $ damage to the monster $ 1 $ and the monster $ 3 $ ;
- the monster $ 3 $ deals $ 7 $ damage to the monster $ 2 $ and the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 3 $ and the monster $ 5 $ ;
- the monster $ 5 $ deals $ 10 $ damage to the monster $ 4 $ ;
- the monster $ 1 $ does not die, since it received $ 4 $ damage and its defense is $ 4 $ ;
- the monster $ 2 $ dies, since it received $ 10 $ damage and its defense is $ 9 $ ;
- the monster $ 3 $ dies, since it received $ 9 $ damage and its defense is $ 1 $ ;
- the monster $ 4 $ does not die, since it received $ 17 $ damage and its defense is $ 18 $ ;
- the monster $ 5 $ dies, since it received $ 5 $ damage and its defense is $ 1 $ .

After the first round, the monsters $ 1 $ and $ 4 $ stay alive.

During the second round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 1 $ ;
- the monster $ 1 $ dies, since it received $ 5 $ damage and its defense is $ 4 $ ;
- the monster $ 4 $ does not die, since it received $ 3 $ damage and its defense is $ 18 $ .

During the next three rounds, only the $ 4 $ -th monster is alive, so nothing happens.

## 样例 #1

### 输入

```
3
5
3 4 7 5 10
4 9 1 18 1
2
2 1
1 3
4
1 1 2 4
3 3 4 2```

### 输出

```
3 1 0 0 0 
0 0 
1 1 1 0```

# AI分析结果



### 题目翻译

# 狂暴怪物

## 题目描述

Monocarp正在玩一款电脑游戏（又一次）。猜猜他在做什么？没错，就是在杀怪物。

一行中有 $n$ 个怪物，编号从 $1$ 到 $n$。第 $i$ 个怪物有两个参数：攻击值 $a_i$ 和防御值 $d_i$。为了杀死这些怪物，Monocarp对它们施加了狂暴咒语，让它们互相攻击而不是攻击Monocarp的角色。

战斗包含 $n$ 轮。每轮发生以下过程：

- 首先，每个存活的怪物 $i$ 对左边最近的存活怪物（如果存在）和右边最近的存活怪物（如果存在）造成 $a_i$ 点伤害；
- 然后，每个在本轮中受到超过 $d_j$ 点伤害的存活怪物 $j$ 会死亡。即，当且仅当防御值 $d_j$ 严格小于本轮收到的总伤害时，第 $j$ 个怪物死亡。

对于每一轮，计算该轮死亡的怪物数量。

---

### 题解综合分析

#### 最优思路总结
1. **链表维护存活关系**：使用双向链表维护每个怪物的左右邻居，动态更新存活状态。
2. **均摊分析优化**：每个怪物最多被删除一次，总操作次数为 $O(n)$。
3. **候选集合筛选**：仅检查可能受影响的怪物（被删怪物的邻居），避免全量检查。

#### 推荐题解
1. **Eraine（★★★★★）**
   - **亮点**：线性时间复杂度证明，均摊分析清晰，代码实现高效
   - **关键实现**：
     ```cpp
     // 链表维护核心逻辑
     void del(int u) {
         R[L[u]] = R[u];
         L[R[u]] = L[u];
         add(L[u]);  // 将左邻居加入候选
         add(R[u]);  // 将右邻居加入候选
     }
     // 每轮处理候选集合
     for (int j : dellst) del(j);
     ```
2. **zjinze（★★★★☆）**
   - **亮点**：使用双集合交替处理存活/死亡怪物，逻辑简明
   - **心得**：通过 `set` 自动去重特性优化候选管理

3. **Genius_Star（★★★★☆）**
   - **亮点**：与 CSP-J 小熊果篮问题类比，提供同类问题解决思路
   - **代码技巧**：通过 `set` 维护待检查怪物，减少无效遍历

---

### 相似题目推荐
1. [P7912 [CSP-J 2021] 小熊的果篮](https://www.luogu.com.cn/problem/P7912)  
   **相似点**：双向链表维护动态序列，相邻元素状态变化处理
2. [P2040 打开所有的灯](https://www.luogu.com.cn/problem/P2040)  
   **相似点**：状态传播问题，通过相邻元素触发变化
3. [P2894 [USACO08FEB]Hotel G](https://www.luogu.com.cn/problem/P2894)  
   **相似点**：区间动态维护，利用数据结构优化查询

---

### 关键代码实现（Eraine解法）
```cpp
// 链表删除与候选更新
void del(int u) {
    R[L[u]] = R[u];
    L[R[u]] = L[u];
    add(L[u]); // 左邻居可能受影响
    add(R[u]); // 右邻居可能受影响
}

// 主处理逻辑
for (int round = 1; round <= n; round++) {
    vector<int> to_check = islst;
    islst.clear();
    for (int x : to_check) {
        if (a[L[x]] + a[R[x]] > d[x]) 
            dellst.push_back(x);
    }
    // 删除并更新链表
    for (int x : dellst) del(x);
    cout << dellst.size() << " ";
}
```

---

### 拓展思考
此类问题核心在于**动态维护相邻关系**，常见于以下场景：
1. **元素级联删除**（如病毒传播模型）
2. **区域扩散问题**（如灯光开关连锁反应）
3. **序列动态压缩**（如连续区间合并）

调试时需注意**多测数据清空**，避免状态残留（如`vis[]`数组未重置）。优化方向可考虑用位运算压缩状态，或使用更高效的数据结构（如跳表）维护邻居关系。

---
处理用时：53.28秒