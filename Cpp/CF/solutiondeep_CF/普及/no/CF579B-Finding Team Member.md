# 题目信息

# Finding Team Member

## 题目描述

There is a programing contest named SnakeUp, $ 2n $ people want to compete for it. In order to attend this contest, people need to form teams of exactly two people. You are given the strength of each possible combination of two people. All the values of the strengths are distinct.

Every contestant hopes that he can find a teammate so that their team’s strength is as high as possible. That is, a contestant will form a team with highest strength possible by choosing a teammate from ones who are willing to be a teammate with him/her. More formally, two people $ A $ and $ B $ may form a team if each of them is the best possible teammate (among the contestants that remain unpaired) for the other one.

Can you determine who will be each person’s teammate?

## 说明/提示

In the first sample, contestant $ 1 $ and $ 2 $ will be teammates and so do contestant $ 3 $ and $ 4 $ , so the teammate of contestant $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ will be $ 2 $ , $ 1 $ , $ 4 $ , $ 3 $ respectively.

## 样例 #1

### 输入

```
2
6
1 2
3 4 5
```

### 输出

```
2 1 4 3
```

## 样例 #2

### 输入

```
3
487060
3831 161856
845957 794650 976977
83847 50566 691206 498447
698377 156232 59015 382455 626960
```

### 输出

```
6 5 4 3 2 1
```

# AI分析结果



# Finding Team Member 题解中文翻译

## 题目描述

有一个名为 SnakeUp 的编程竞赛，$2n$ 人想参加。为了参赛，需要组成两人一队的队伍。给出每两个人组成的队伍的实力值，所有实力值各不相同。

每位参赛者都希望找到队友，使他们的队伍实力尽可能高。即，参赛者会从愿意成为队友的人中选择一个能组成最高实力队伍的搭档。更正式地说，两个人 $A$ 和 $B$ 可以组成队伍当且仅当在未被配对的选手中，他们是彼此的最佳搭档。

请确定每个人的队友是谁？

## 说明/提示

第一个样例中，选手 $1$ 和 $2$ 组队，$3$ 和 $4$ 组队，因此选手 $1$、$2$、$3$、$4$ 的队友分别是 $2$、$1$、$4$、$3$。

## 样例 #1

### 输入
```
2
6
1 2
3 4 5
```

### 输出
```
2 1 4 3
```

## 样例 #2

### 输入
```
3
487060
3831 161856
845957 794650 976977
83847 50566 691206 498447
698377 156232 59015 382455 626960
```

### 输出
```
6 5 4 3 2 1
```

---

**算法分类**：贪心

---

## 题解分析与结论

题目要求将 $2n$ 人两两配对，使得每对选手互为当前未配对选手中的最优解。所有题解均采用**贪心算法**，核心思路为：

1. **将全部可能的配对按实力值降序排序**
2. **从高到低遍历配对**，若两人均未配对则强制组队
3. 通过标记数组维护已配对状态

该策略的正确性基于：全局最优解的配对必然包含实力值最大的有效配对。每次选择当前最大且未被占用的配对，不会影响后续更优解的产生。

---

## 精选题解

### 题解作者：xiaomuyun（结构体数组版本） ★★★★☆

**关键亮点**：
1. **清晰的输入处理**：正确解析三角形输入格式
2. **高效的结构体排序**：将所有组合存入数组后排序
3. **简洁的贪心实现**：逆序遍历排序数组，优先处理高实力组合

**代码核心思路**：
```cpp
struct strength { int u, v, w; };
vector<strength> pairs;

// 读取所有可能的组合
for (int i = 1; i <= 2*n; i++) 
    for (int j = 1; j < i; j++) 
        pairs.push_back({i, j, val});

// 按实力值降序排序
sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
    return a.w > b.w;
});

// 贪心选择未配对的组合
vector<int> ans(2*n+1);
vector<bool> used(2*n+1);
for (auto& p : pairs) {
    if (!used[p.u] && !used[p.v]) {
        ans[p.u] = p.v;
        ans[p.v] = p.u;
        used[p.u] = used[p.v] = true;
    }
}
```

**个人心得**：
> "输入处理非常坑人，特别注意三角形输入方式。贪心策略需要从后往前遍历排序后的数组，确保优先处理最大实力组合。"

---

## 最优思路总结

**关键技巧**：
1. **降序贪心匹配**：通过排序确保优先处理最优解候选
2. **状态标记法**：使用布尔数组记录已匹配选手，实现 $O(1)$ 状态查询
3. **对称存储结果**：`ans[x] = y` 时同步设置 `ans[y] = x`，简化输出逻辑

**同类拓展**：
- 任务调度中的最优匹配问题
- 稳定婚姻问题（Gale-Shapley算法）
- 最大权匹配问题（需使用KM算法）

---

## 推荐习题
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心策略应用
2. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230) - 带时间约束的贪心
3. [P1250 种树](https://www.luogu.com.cn/problem/P1250) - 区间贪心处理

---
处理用时：165.39秒