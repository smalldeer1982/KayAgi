# 题目信息

# 「NnOI R2-T3」Horizon Blue

## 题目描述

小 C 喜欢在画板上画画。他进行了 $ n $ 次操作，每次操作有如下三种可能：

- ```1 k b``` 代表小 C 绘制了一条解析式为 $ y=kx+b $ 的直线。
- ```2 k b``` 代表小 C 询问你直线 $ y=kx+b $ 与多少条被绘制的直线有**恰好**一个公共点。
- ```3 k b``` 代表小 C 擦除所有与直线 $ y=kx+b $ 有**至少**一个公共点的直线。

**注意：两条重合的直线有无数个交点。**

**注意：询问时重合的直线应分别计算。**

## 说明/提示

**【样例 1 解释】**

第 1 次操作，绘制直线 $ y=x $。

第 2 次操作，绘制直线 $ y=-x $。

第 3 次操作，可以发现直线 $ y=2x+1 $ 与前两条线相交。

第 4 次操作，擦掉所有 $ y=x+3 $ 相交的线，直线 $ y=-x $ 被擦掉。

第 5 次操作，$ y=2x+1 $ 显然与 $ y=x $ 相交。

第 6 次操作，$ y=x+1 $ 与 $ y=x $ 斜率相等，是平行线，不相交。

**【数据范围】**

对于 $ 100\% $ 的数据，$ 1 \le n \le 10^5 $，$ 1 \le |k| \le 10^5 $，$ 0 \le |b| \le 10^5 $。

**提示：本题开启捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& n \le 5000 & 27 \r
\textsf2& \vert k\vert,\vert b\vert \le 50 & 21 \r
\textsf3& 无第\ 3\ 类操作 & 13 \r
\textsf4& 第\ i\ 次操作满足\ k=i & 14 \r
\textsf5& 无特殊限制 & 25 \r
\end{array}
$$

在赛后新添加的 hack 测试点将放入 subtask 6。

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
| idea | 船酱魔王 |
| data | 船酱魔王 |
| check | EstasTonne |
| solution | 船酱魔王 |

## 样例 #1

### 输入

```
6
1 1 0
1 -1 0
2 2 1
3 1 3
2 2 1
2 1 1```

### 输出

```
2
1
0```

## 样例 #2

### 输入

```
10
1 1 0
1 1 0
2 1 1
2 1 0
2 2 5
3 1 0
2 2 5
1 2 3
1 3 4
2 3 5```

### 输出

```
0
0
2
0
1```

# AI分析结果



### 综合分析与结论
本题核心在于高效维护直线集合的交点关系，关键点在于：  
1. 操作2只需统计不同斜率的直线数量  
2.操作3需要快速删除所有相交直线（不同斜率）和重合直线（同斜率同截距）  
最优解法均采用分层数据结构：外层维护斜率集合，内层维护截距集合，时间复杂度O(n log n)

---

### 精选题解及评分

#### 1. 作者：NaN_HQJ2007_NaN（⭐⭐⭐⭐⭐）
**核心亮点**：  
- 双STL嵌套结构（set存斜率，multiset存截距）  
- 通过偏移量处理负数  
- 操作3时间复杂度O(m log n)（m为被删斜率数量）  
**关键代码**：
```cpp
set<int> s; // 斜率集合
multiset<int> st[N]; // 每个斜率的截距集合
void op3(int k, int b) {
    // 清除非k斜率的所有截距
    for(auto it=s.begin(); it!=s.end(); ){
        int w = *it;
        if(w != k) {
            tot -= st[w].size();
            st[w].clear();
            it = s.erase(it);
        } else ++it;
    }
    // 删除相同斜率且截距相等的
    tot -= st[k].count(b);
    st[k].erase(b);
}
```

#### 2. 作者：DengDuck（⭐⭐⭐⭐）
**创新点**：  
- 使用map套map实现二维计数  
- 通过set维护有效斜率集合  
- 清空操作采用集合遍历优化  
**调试心得**：  
"发现直接用map遍历会超时，改为先保存要保留的k再重建map"

#### 3. 作者：Thenyu（⭐⭐⭐）
**亮点**：  
- 数组+map组合存储  
- 预存斜率列表加速遍历  
**优化技巧**：  
用vector维护当前存在的斜率，避免全量遍历

---

### 最优思路总结
**核心数据结构**：  
1. 外层结构（斜率）：`unordered_map<int, ...>` 或 `set`  
2. 内层结构（截距）：`unordered_map<int, int>` 或 `multiset`  

**关键操作**：  
- 删除时优先处理非当前斜率集合  
- 利用STL的批量删除特性（如map.erase()）  
- 使用偏移量（+1e5）处理负数下标  

**代码模板**：
```cpp
int total; // 总直线数
unordered_map<int, int> slope_cnt; // 各斜率计数
unordered_map<int, unordered_map<int, int>> line_cnt; // 各直线计数

void op3(int k, int b) {
    // 删除不同斜率
    total -= (total - slope_cnt[k]);
    slope_cnt = {{k, slope_cnt[k]}}; 
    
    // 删除相同斜率重合直线
    total -= line_cnt[k][b];
    line_cnt[k].erase(b);
    slope_cnt[k] = total;
}
```

---

### 推荐练习题目
1. [P3369 普通平衡树](https://www.luogu.com.cn/problem/P3369) - STL嵌套使用  
2. [P3391 文艺平衡树](https://www.luogu.com.cn/problem/P3391) - 区间操作优化  
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908) - 分层统计思想

---
处理用时：52.30秒