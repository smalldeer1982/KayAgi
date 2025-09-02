# 题目信息

# [SDCPC 2023] Matching

## 题目描述

给定长度为 $n$ 的整数序列 $a_1, a_2, \cdots, a_n$，我们将从该序列中构造出一张无向图 $G$。具体来说，对于所有 $1 \le i < j \le n$，若 $i - j = a_i - a_j$，则 $G$ 中将存在一条连接节点 $i$ 与 $j$ 的无向边，其边权为 $(a_i + a_j)$。

求 $G$ 的一个匹配，使得该匹配中所有边的边权之和最大，并输出最大边权之和。

请回忆：无向图的匹配，指的是从该无向图中选出一些边，使得任意两条边都没有公共的节点。特别地，不选任何边也是一个匹配。

## 样例 #1

### 输入

```
3
9
3 -5 5 6 7 -1 9 1 2
3
-5 -4 -3
3
1 10 100
```

### 输出

```
30
0
0
```

# AI分析结果



**算法分类**：贪心

**综合分析**  
题目要求构造图后求最大权匹配。关键是将条件转化为同一连通块内的点满足 $a_i - i$ 相同，形成完全图。每个连通块内按降序排序后，贪心选取相邻两元素之和最大且为正数的对，总和即为答案。

**优质题解推荐**  

1. **作者：hjqhs（4星）**  
   - **亮点**：代码简洁，使用 `unordered_map` 分组后降序排序，逐对累加和为正数的边权。  
   - **代码核心**：  
     ```cpp
     for (auto &p : mp) {
         vector<int> &vec = p.second;
         reverse(vec.begin(), vec.end()); // 转为降序
         for (int i = 0; i + 1 < vec.size(); i += 2) {
             int sm = vec[i] + vec[i + 1];
             if (sm <= 0) break;
             ans += sm;
         }
     }
     ```

2. **作者：Sundar_2022（4星）**  
   - **亮点**：使用 `map` 分组后显式降序排序，通过维护两个临时变量配对，逻辑清晰。  
   - **代码核心**：  
     ```cpp
     for (auto it : Edge) {
         vector<int> E = it.second;
         sort(E.begin(), E.end(), [](int a, int b) { return a > b; });
         int a = INF, b = INF;
         for (auto num : E) {
             if (a == INF) a = num;
             else {
                 b = num;
                 if (a + b > 0) ans += a + b, a = b = INF;
                 else break;
             }
         }
     }
     ```

3. **作者：One_JuRuo（4星）**  
   - **亮点**：直接遍历排序后的连通块元素，从后往前两两配对，处理负数提前终止。  
   - **代码核心**：  
     ```cpp
     for (auto i : m) {
         vector<int> v = i.second;
         sort(v.begin(), v.end()); // 升序排序后反向遍历
         for (int i = v.size() - 1; i >= 1; i -= 2) {
             if (v[i] + v[i - 1] > 0) ans += v[i] + v[i - 1];
             else break;
         }
     }
     ```

**关键思路总结**  
将每个连通块（完全图）的元素降序排序后，依次取相邻两元素配对，若和为正则计入答案。通过分组、排序、贪心配对三步解决。

**类似题目推荐**  
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（贪心分组）  
2. [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209)（区间分组与覆盖）  
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)（降序贪心选择）

---
处理用时：122.38秒