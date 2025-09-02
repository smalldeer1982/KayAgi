# 题目信息

# Problems for Round

## 题目描述

There are $ n $ problems prepared for the next Codeforces round. They are arranged in ascending order by their difficulty, and no two problems have the same difficulty. Moreover, there are $ m $ pairs of similar problems. Authors want to split problems between two division according to the following rules:

- Problemset of each division should be non-empty.
- Each problem should be used in exactly one division (yes, it is unusual requirement).
- Each problem used in division 1 should be harder than any problem used in division 2.
- If two problems are similar, they should be used in different divisions.

Your goal is count the number of ways to split problem between two divisions and satisfy all the rules. Two ways to split problems are considered to be different if there is at least one problem that belongs to division 1 in one of them and to division 2 in the other.

Note, that the relation of similarity is not transitive. That is, if problem $ i $ is similar to problem $ j $ and problem $ j $ is similar to problem $ k $ , it doesn't follow that $ i $ is similar to $ k $ .

## 说明/提示

In the first sample, problems $ 1 $ and $ 2 $ should be used in division 2, while problems $ 4 $ and $ 5 $ in division 1. Problem $ 3 $ may be used either in division 1 or in division 2.

In the second sample, all pairs of problems are similar and there is no way to split problem between two divisions without breaking any rules.

Third sample reminds you that the similarity relation is not transitive. Problem $ 3 $ is similar to both $ 1 $ and $ 2 $ , but $ 1 $ is not similar to $ 2 $ , so they may be used together.

## 样例 #1

### 输入

```
5 2
1 4
5 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 2
3 1
3 2
```

### 输出

```
1
```

# AI分析结果



# Problems for Round 中文翻译

## 题目描述

有 $n$ 道题目准备用于下一场 Codeforces 比赛，按难度升序排列且无重复难度。给定 $m$ 对相似题目，要求将这些题目分配到两个组别（division1 和 division2），满足以下规则：

1. 每个组别非空；
2. 每个题目必须属于且仅属于一个组；
3. division1 的所有题目难度严格大于 division2 的所有题目；
4. 相似题目必须分在不同组。

求满足条件的分组方案数。两种方案不同当且仅当至少存在一题在两个方案中的组别不同。

## 样例解释

样例1：当分割点在问题2和4之间时，方案数为2。  
样例2：所有题目两两相似，无法分配，输出0。  
样例3：问题3必须分到与1和2不同的组，唯一可行分割点为2。

---

**算法分类**  
构造

---

## 题解对比与总结

### 共同思路
维护两个边界值：
1. `maxx`：所有相似对中较小值的最大值（即 division2 的最大难度下界）
2. `minx`：所有相似对中较大值的最小值（即 division1 的最小难度上界）

最终合法分割点数为 `max(0, minx - maxx)`，代表可自由分配的问题区间。

### 各题解亮点
1. **Fuxh_18（5星）**  
   - **亮点**：特判处理 `m=0` 的情况，代码简洁且逻辑清晰。
   - **代码核心**：
     ```cpp
     mx = max(mx, min(a, b)); // 维护 division2 的最大下界
     mn = min(mn, max(a, b)); // 维护 division1 的最小上界
     if (mn > mx) cout << mn - mx; // 合法区间长度
     ```

2. **szh_AK_all（4星）**  
   - **亮点**：巧妙初始化 `tmp=1` 和 `ans=n`，无需特判 `m=0`。
   - **代码核心**：
     ```cpp
     tmp = max(tmp, min(x, y)); // 动态更新下界
     ans = min(ans, max(x, y)); // 动态更新上界
     cout << max(ans - tmp, 0);
     ```

3. **lhs_chris（4星）**  
   - **亮点**：差分数组标记不可行分割点，适合通用区间覆盖问题。
   - **代码核心**：
     ```cpp
     a[1]++; a[x]--; // 标记左不可行区间
     a[y]++; a[n]--; // 标记右不可行区间
     ```

---

## 最优思路
初始化 `maxx` 和 `minx` 为合理区间边界，遍历所有相似对动态调整边界，最终计算区间差值。无需特判 `m=0`，初始值 `maxx=1` 和 `minx=n` 可自然覆盖所有分割点。

**核心代码实现**：
```cpp
int main() {
    int n, m, tmp = 1, ans;
    cin >> n >> m;
    ans = n;
    while (m--) {
        int x, y;
        cin >> x >> y;
        tmp = max(tmp, min(x, y));
        ans = min(ans, max(x, y));
    }
    cout << max(ans - tmp, 0);
}
```

---

## 同类题目推荐
1. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056) - 贪心选择分割线
2. [P3143 Diamond Collector S](https://www.luogu.com.cn/problem/P3143) - 维护两个区间的边界
3. [P2882 Face The Right Way G](https://www.luogu.com.cn/problem/P2882) - 差分数组应用

---
处理用时：355.54秒