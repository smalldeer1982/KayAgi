# 题目信息

# Programming Competition

## 题目描述

BerSoft is the biggest IT corporation in Berland. There are $ n $ employees at BerSoft company, numbered from $ 1 $ to $ n $ .

The first employee is the head of the company, and he does not have any superiors. Every other employee $ i $ has exactly one direct superior $ p_i $ .

Employee $ x $ is considered to be a superior (direct or indirect) of employee $ y $ if one of the following conditions holds:

- employee $ x $ is the direct superior of employee $ y $ ;
- employee $ x $ is a superior of the direct superior of employee $ y $ .

The structure of BerSoft is organized in such a way that the head of the company is superior of every employee.

A programming competition is going to be held soon. Two-person teams should be created for this purpose. However, if one employee in a team is the superior of another, they are uncomfortable together. So, teams of two people should be created so that no one is the superior of the other. Note that no employee can participate in more than one team.

Your task is to calculate the maximum possible number of teams according to the aforementioned rules.

## 说明/提示

In the first test case, team $ (3, 4) $ can be created.

In the second test case, no team can be created, because there are only $ 2 $ employees and one is the superior of another.

In the third test case, team $ (2, 3) $ can be created.

In the fourth test case, teams $ (2, 4) $ , $ (3, 5) $ and $ (6, 7) $ can be created.

In the fifth test case, teams $ (2, 3) $ , $ (6, 4) $ and $ (5, 7) $ can be created.

## 样例 #1

### 输入

```
6
4
1 2 1
2
1
5
5 5 5 1
7
1 2 1 1 3 3
7
1 1 3 2 2 4
7
1 2 1 1 1 3```

### 输出

```
1
0
1
3
3
3```

# AI分析结果



# Programming Competition 题目中文翻译

## 题目描述

BerSoft 是 Berland 最大的 IT 公司。公司有 $n$ 名员工，编号从 $1$ 到 $n$。

第一个员工是公司领导，没有上级。其他每个员工 $i$ 都有一个直接上级 $p_i$。

员工 $x$ 被认为是员工 $y$ 的上级（直接或间接）的条件：
- $x$ 是 $y$ 的直接上级；
- $x$ 是 $y$ 上级的上级。

公司结构保证领导是所有员工的上级。

编程竞赛需要组建两人团队，要求团队成员不能互为上下级。求最大可组建的团队数。

## 说明/提示

样例解释略（详见原题）。

---

### 题解分析与结论

#### 关键思路
采用树形 DP，核心思路为：
1. **子树规模分析**：对每个子树，计算其总节点数 $sz_u$。
2. **最大子树判断**：若最大子树的规模超过其他子树总和，则优先内部匹配后与外部节点配对。
3. **贪心决策**：若最大子树不占优，则按 $\lfloor (sz_u-1)/2 \rfloor$ 取理论最大值。

#### 最优题解

**题解作者：cpchenpi（⭐⭐⭐⭐⭐）**

**核心思路**：
- `dp[u]` 表示以 `u` 为根的子树最大匹配数。
- 分两种情况处理：
  - 最大子树 `v` 的规模超过其他子树总和：`ans[u] = min(理论上限, v的内部匹配数 + 其他子树总节点数)`。
  - 否则直接取理论上限 `(sz[u]-1)/2`。

**代码实现**：
```cpp
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> sons(n + 1);
    vector<int> sz(n + 1), ans(n + 1);
    // 建树
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        sons[p].push_back(i);
    }
    // 树形DP
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        int mxi = 0; // 最大子树
        for (int v : sons[u]) {
            dfs(v);
            sz[u] += sz[v];
            if (sz[v] > sz[mxi]) mxi = v;
        }
        // 分情况计算答案
        if (sz[mxi] > (sz[u]-1)/2) 
            ans[u] = min((sz[u]-1)/2, ans[mxi] + (sz[u]-1 - sz[mxi]));
        else 
            ans[u] = (sz[u]-1)/2;
    };
    dfs(1);
    cout << ans[1] << "\n";
}
```

---

### 相似题目推荐
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352) - 树形 DP 基础
2. [P2014 选课](https://www.luogu.com.cn/problem/P2014) - 树形依赖背包
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040) - 区间 DP 结合树结构

---

### 关键技巧总结
- **子树规模剪裁**：通过比较最大子树与其他子树总和的相对大小，快速确定最优匹配策略。
- **树形DP设计**：通过后序遍历自底向上传递子树信息，确保状态转移的正确性。
- **理论上限计算**：利用 $\lfloor (n-1)/2 \rfloor$ 快速确定可能的最大匹配数。

---
处理用时：60.76秒