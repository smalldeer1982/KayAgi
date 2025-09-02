# 题目信息

# Towers

## 题目描述

As you know, all the kids in Berland love playing with cubes. Little Petya has $ n $ towers consisting of cubes of the same size. Tower with number $ i $ consists of $ a_{i} $ cubes stacked one on top of the other. Petya defines the instability of a set of towers as a value equal to the difference between the heights of the highest and the lowest of the towers. For example, if Petya built five cube towers with heights (8, 3, 2, 6, 3), the instability of this set is equal to 6 (the highest tower has height 8, the lowest one has height 2).

The boy wants the instability of his set of towers to be as low as possible. All he can do is to perform the following operation several times: take the top cube from some tower and put it on top of some other tower of his set. Please note that Petya would never put the cube on the same tower from which it was removed because he thinks it's a waste of time.

Before going to school, the boy will have time to perform no more than $ k $ such operations. Petya does not want to be late for class, so you have to help him accomplish this task.

## 说明/提示

In the first sample you need to move the cubes two times, from the second tower to the third one and from the second one to the first one. Then the heights of the towers are all the same and equal to 6.

## 样例 #1

### 输入

```
3 2
5 8 5
```

### 输出

```
0 2
2 1
2 3
```

## 样例 #2

### 输入

```
3 4
2 2 4
```

### 输出

```
1 1
3 2
```

## 样例 #3

### 输入

```
5 3
8 3 2 6 3
```

### 输出

```
3 3
1 3
1 2
1 3
```

# AI分析结果



【中文题目重写】

# 塔楼

## 题目描述

众所周知，伯兰国的所有孩子都喜欢玩立方体。小Petya有$n$座由相同尺寸立方体堆成的塔楼，第$i$座塔楼包含$a_i$个立方体。Petya定义塔楼集合的不稳定性为最高塔与最矮塔的高度差。例如，若五座塔高度为（8, 3, 2, 6, 3），则不稳定性为6（最高8，最矮2）。

男孩希望通过最多$k$次操作使不稳定性尽可能小。每次操作可将某个塔顶的立方体移到另一座塔顶（不允许移回原塔）。

## 输入输出样例

### 样例 #1
输入：
```
3 2
5 8 5
```
输出：
```
0 2
2 1
2 3
```

### 样例 #2
输入：
```
3 4
2 2 4
```
输出：
```
1 1
3 2
```

### 样例 #3
输入：
```
5 3
8 3 2 6 3
```
输出：
```
3 3
1 3
1 2
1 3
```

---

**算法分类**：贪心

---

### 题解综合分析

**核心思路**：每次操作都选择将当前最高塔的立方体移至最矮塔，通过维护高度桶快速定位极值，批量处理移动操作以优化时间复杂度。

---

### 高分题解选录

#### 题解作者：Alex_Wei（★★★★★）
**关键亮点**：
1. 桶结构动态维护高度分布，O(1)时间获取当前极值
2. 批量处理移动次数，时间复杂度优化至O(max(n,k))
3. 边界处理严谨（差值≤1时停止）

**代码核心**：
```cpp
int n,k,a,l=1e9,r;
vector<int> buc[12345],al,ar;

// 初始化桶结构
for(int i=1;i<=n;i++) {
    cin>>a;
    buc[a].push_back(i);
    l=min(l,a);
    r=max(r,a);
}

// 主处理逻辑
while(k && l+1<r) {
    int val=min(k, (int)min(buc[l].size(), buc[r].size()));
    k -= val;
    while(val--) {
        // 记录移动操作
        al.push_back(buc[r].back());
        ar.push_back(buc[l].back());
        // 更新桶结构
        buc[r-1].push_back(buc[r].back());
        buc[l+1].push_back(buc[l].back());
        buc[r].pop_back();
        buc[l].pop_back();
    }
    // 动态调整极值
    if(buc[l].empty()) l++;
    if(buc[r].empty()) r--;
}
```

---

### 关键技巧总结
1. **贪心策略**：每次操作最大程度降低高度差
2. **桶结构优化**：通过值域分桶快速定位极值塔
3. **批量处理**：单次处理min(k, 极值塔数量)次操作
4. **动态极值调整**：在桶空时自动收缩值域范围

---

### 拓展训练推荐
1. CF978D（贪心+极值调整）
2. P1094（贪心+双指针）
3. P5019（贪心+差分应用）

---

### 同类问题特征
当题目要求通过有限操作使序列满足极值相关条件时，通常可考虑：
1. 贪心策略优先处理最大矛盾
2. 维护当前状态的极值信息
3. 采用合适数据结构（如堆、桶）优化极值查询

---
处理用时：77.90秒