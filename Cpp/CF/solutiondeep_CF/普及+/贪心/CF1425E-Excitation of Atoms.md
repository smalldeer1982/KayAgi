# 题目信息

# Excitation of Atoms

## 题目描述

Mr. Chanek is currently participating in a science fair that is popular in town. He finds an exciting puzzle in the fair and wants to solve it.

There are $ N $ atoms numbered from $ 1 $ to $ N $ . These atoms are especially quirky. Initially, each atom is in normal state. Each atom can be in an excited. Exciting atom $ i $ requires $ D_i $ energy. When atom $ i $ is excited, it will give $ A_i $ energy. You can excite any number of atoms (including zero).

These atoms also form a peculiar one-way bond. For each $ i $ , $ (1 \le i < N) $ , if atom $ i $ is excited, atom $ E_i $ will also be excited at no cost. Initially, $ E_i $ = $ i+1 $ . Note that atom $ N $ cannot form a bond to any atom.

Mr. Chanek must change exactly $ K $ bonds. Exactly $ K $ times, Mr. Chanek chooses an atom $ i $ , $ (1 \le i < N) $ and changes $ E_i $ to a different value other than $ i $ and the current $ E_i $ . Note that an atom's bond can remain unchanged or changed more than once. Help Mr. Chanek determine the maximum energy that he can achieve!

note: You must first change exactly $ K $ bonds before you can start exciting atoms.

## 说明/提示

An optimal solution to change $ E_5 $ to 1 and then excite atom 5 with energy 1. It will cause atoms 1, 2, 3, 4, 5 be excited. The total energy gained by Mr. Chanek is (5 + 6 + 7 + 8 + 10) - 1 = 35.

Another possible way is to change $ E_3 $ to 1 and then exciting atom 3 (which will excite atom 1, 2, 3) and exciting atom 4 (which will excite atom 4, 5, 6). The total energy gained by Mr. Chanek is (5 + 6 + 7 + 8 + 10 + 2) - (6 + 7) = 25 which is not optimal.

## 样例 #1

### 输入

```
6 1
5 6 7 8 10 2
3 5 6 7 1 10```

### 输出

```
35```

# AI分析结果



# Excitation of Atoms（原子的激发）

## 题目描述

Chanek 先生正在参加一个科学展览会，遇到了一个有趣的谜题：

有 $N$ 个原子，编号 $1$ 到 $N$。每个原子初始处于正常状态。激发原子 $i$ 需要消耗 $D_i$ 能量，激发后会获得 $A_i$ 能量。原子间存在单向关联：对于每个 $1 \le i < N$，若原子 $i$ 被激发，则其关联的原子 $E_i$（初始为 $i+1$）会被免费激发。原子 $N$ 没有关联原子。

必须**恰好修改 $K$ 次关联关系**（每次修改选择 $i$，将 $E_i$ 改为不同于当前值的其他值），修改完成后选择激发任意数量原子。求能获得的最大净能量（总获得能量 - 总消耗能量）。

## 样例解释

修改 $E_5$ 为 1，激发原子 5 会依次激发 1→2→3→4→5。总获得能量为 5+6+7+8+10=36，消耗 1，净能量 35。

---

## 题解分析与结论

### 题解对比与评分

1. **chenxia25 题解（★★★★☆）**
   - **关键亮点**：通过拓扑结构分析，对 K=1 的情况提出两种关键修改方向（前连/后连），并给出对应的集合划分方式。
   - **不足**：代码实现细节未完整展示。
   - **个人心得**：强调"分情况讨论时需寻找结论而非暴力求解"的解题思维。

2. **suxxsfe 题解（★★★★★）**
   - **关键亮点**：
     - 引入前缀和预处理 $sum_i$ 与增益数组 $gain_i$（表示从 $i$ 开始的后缀最优解）。
     - 对 K=1 的两种修改方式给出精确数学表达式，并给出完整代码。
     - 通过 min(d[i]) 优化 K>1 的情况。
   - **代码技巧**：预处理 gain 数组时使用逆向扫描，确保最优解的继承性。

### 最优解法核心思路

1. **K=0 情况**  
   直接计算每个原子作为激发起点时的最大增益：$max(gain_1, 0)$，其中 $gain_i = max(sum[n] - sum[j-1] - D_j)$（$j \ge i$）。

2. **K>1 情况**  
   构造全连接图：修改 $E_1,E_2,...,E_{n-1}$ 形成以某个原子为中心的全连接结构。此时只需选择 $D_i$ 最小的原子激发，总收益为 $sum[n] - min(D_i)$。

3. **K=1 情况**  
   分两类修改方式：
   - **前向修改**（将 $E_i$ 改为 1）：激发区间 [1,i] 需取该区间最小 $D_j$，并叠加 [i+1,n] 的最优后缀。
   - **后向修改**（将 $E_{i-1}$ 改为 i+1）：计算两种子情况（激发点在修改点前/后）的最大值。

### 关键代码实现

```cpp
// 预处理增益数组
for(int i=1;i<=n;i++) gain[i] = sum[n]-sum[i-1]-d[i];
for(int i=n-1;i;i--) gain[i] = max(gain[i], gain[i+1]); // 逆向继承最优解

// K>1 时的处理
long long ans = sum[n]-d[1]; // 修改为全连接后的收益
for(int i=2;i<n;i++) ans = max(ans, sum[n]-d[i]); // 枚举每个原子作为中心
ans = max(ans, a[n]-d[n]); // 单独处理原子n

// K=1 时的前向修改计算
long long minD = min(d[1],d[2]);
for(int i=2;i<n;i++) {
    ans = max(ans, sum[i]-minD + max(0ll,gain[i+1])); 
    minD = min(minD, d[i+1]);
}
```

### 拓展与相似题目

1. **类似分情况讨论**  
   - 洛谷 P1273 有线电视网（树形DP分情况）
   - 洛谷 P5021 赛道修建（贪心+二分）

2. **预处理优化技巧**  
   - 洛谷 P1115 最大子段和（前缀和变形）
   - 洛谷 P3146 248（区间DP预处理）

3. **图结构修改问题**  
   - 洛谷 P4568 飞行路线（分层图最短路）

---

**总结启示**：对于需要修改图结构的题目，通常可通过分析极端情况（如全连接）寻找突破口。预处理增益数组与逆向扫描技巧能有效优化复杂情况的计算。

---
处理用时：53.71秒