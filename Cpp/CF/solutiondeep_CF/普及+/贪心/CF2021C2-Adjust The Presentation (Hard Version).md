# 题目信息

# Adjust The Presentation (Hard Version)

## 题目描述

This is the hard version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ 0 \leq q \leq 2 \cdot 10^5 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line. After that, set $ b_1 := 2 $ , now slide $ 1 $ must be presented by member $ 2 $ which is impossible as member $ 1 $ will present slide $ 1 $ first. Then, set $ b_1 = 1 $ , the $ b $ is the same as the initial $ b $ , making a good presentation possible.

## 样例 #1

### 输入

```
3
4 2 2
1 2 3 4
1 1
1 2
1 1
3 6 2
1 2 3
1 1 2 3 3 2
3 3
2 2
4 6 2
3 1 4 2
3 1 1 2 3 4
3 4
4 2```

### 输出

```
YA
TIDAK
YA
YA
TIDAK
YA
TIDAK
YA
YA```

# AI分析结果



### 题目内容重写
# 调整幻灯片顺序（困难版）

## 题目描述

这是该问题的困难版本。两个版本的区别在于 $q$ 的约束和时间限制不同。本题中 $0 \leq q \leq 2 \cdot 10^5$。只有解决所有版本的问题才能进行 hack。

一个由 $n$ 名成员（编号 $1$ 到 $n$）组成的团队需要在大型会议上展示包含 $m$ 张幻灯片的演示。成员初始按数组 $a$ 的顺序排列。每展示一张幻灯片后，可以将当前队首成员调整到队列任意位置。数组 $b$ 表示每张幻灯片应由哪个成员展示。现需处理 $q$ 次对 $b$ 的持久化修改，每次修改后判断能否满足所有幻灯片的展示顺序要求。

## 输入输出样例
（样例与原文一致，此处略）

---

### 题解综合分析

#### 核心思路总结
所有题解均围绕同一核心观察展开：**合法条件等价于每个元素在 $b$ 中的第一次出现位置必须形成递增序列**。关键差异在于维护这一性质的数据结构选择：

1. **集合维护法**（chenxi2009/Day_Tao）  
   使用 `set` 记录每个元素的所有出现位置，维护相邻元素的首次出现顺序是否合法。通过计数器记录非法相邻对数，$O(1)$ 判断全局合法性。

2. **线段树法**（__3E24AC7002AD9292__/GY程袁浩）  
   将元素按初始排列映射为连续下标，用线段树维护首次出现位置的单调性。单点修改后通过树结构合并区间信息。

3. **哈希法**（Locix_Elaina_Celome）  
   对每个元素的首次出现位置进行哈希，比较哈希值是否与初始排列的前缀哈希匹配。

#### 最优方案提炼
**集合维护法** 在时间和代码复杂度上表现最优：
- 使用 `set<int>` 快速获取每个元素的首次出现位置。
- 维护计数器 `cnt` 表示不满足 $S_{i-1}.begin() < S_i.begin()$ 的相邻对数。
- 修改时仅需处理新旧值及其相邻元素的边界情况，更新 `cnt`。

---

### 精选高分题解（评分≥4星）

#### 1. [chenxi2009] ⭐⭐⭐⭐⭐
**亮点**：  
- 通过 `set` 快速维护元素的首次出现位置。
- 引入错误集合 `st` 记录所有非法元素，空集合即合法。
- 修改时仅检查新旧值及其相邻元素，复杂度 $O(\log m)$。

**核心代码**：
```cpp
set<int> q[200001]; // q[i] 存储元素i的所有出现位置
int cnt = 0; // 记录非法相邻对数

// 修改逻辑（伪代码）
void update(int s, int new_val) {
    int old_val = b[s];
    // 删除旧值影响
    if (q[old_val-1].empty() || *q[old_val-1].begin() > *q[old_val].begin()) 
        st.erase(old_val);
    // 添加新值影响
    if (new_val != 1 && (q[new_val-1].empty() || *q[new_val-1].begin() > *q[new_val].begin()))
        st.insert(new_val);
    // 更新计数器后判断st是否为空
}
```

#### 2. [Day_Tao] ⭐⭐⭐⭐
**亮点**：  
- 引入 `cnt` 直接统计非法相邻对数量。
- 通过 `set` 维护元素出现位置，修改时动态调整 `cnt`。
- 代码结构清晰，边界处理简洁。

**核心代码**：
```cpp
set<int> S[N]; // S[i] 存储元素i的出现位置
int cnt = 0; // 非法相邻对数

void modify(int val, int pos, int op) {
    // 计算旧值对相邻元素的影响
    if (!S[val-1].empty() && *S[val-1].begin() > *S[val].begin())
        cnt += op;
    // 类似处理val+1...
}

// 修改时调用
modify(old_val, pos, -1);
modify(new_val, pos, 1);
```

#### 3. [GY程袁浩] ⭐⭐⭐⭐
**亮点**：  
- 线段树维护首次出现位置的单调性。
- 通过区间合并自动判断全局合法性，适合拓展到更复杂条件。

**核心代码**：
```cpp
struct node {
    int l, r, maxn, minn;
    bool ok; // 区间是否单调
} tr[N<<2];

void pushup(int p) {
    tr[p].ok = tr[p<<1].ok && tr[p<<1|1].ok 
             && (tr[p<<1].maxn <= tr[p<<1|1].minn);
}
```

---

### 关键技巧与拓展
1. **集合维护边界法**：  
   当需要快速查询最小/最大值时，`set` 的 $O(1)$ 访问特性至关重要。修改时只需处理新旧值的相邻元素。

2. **同类型题目推荐**：  
   - [P1972 SDOI2009 HH的项链](https://www.luogu.com.cn/problem/P1972)（区间元素首次出现问题）
   - [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（维护序列顺序性）
   - [P3586 LOG](https://www.luogu.com.cn/problem/P3586)（动态集合维护）

--- 

### 个人心得摘录
- **chenxi2009**：  
  > "注意特判越界情况，例如当元素为1或n时的相邻判断需要单独处理，否则会引入无效状态。"

- **Day_Tao**：  
  > "修改时先删除旧值的影响再插入新值，避免迭代器失效。`set` 的 `lower_bound` 用法在此处简化了前驱后继查询。"

---
处理用时：65.61秒