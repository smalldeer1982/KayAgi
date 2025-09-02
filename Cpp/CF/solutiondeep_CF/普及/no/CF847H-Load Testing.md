# 题目信息

# Load Testing

## 题目描述

Polycarp plans to conduct a load testing of its new project Fakebook. He already agreed with his friends that at certain points in time they will send requests to Fakebook. The load testing will last $ n $ minutes and in the $ i $ -th minute friends will send $ a_{i} $ requests.

Polycarp plans to test Fakebook under a special kind of load. In case the information about Fakebook gets into the mass media, Polycarp hopes for a monotone increase of the load, followed by a monotone decrease of the interest to the service. Polycarp wants to test this form of load.

Your task is to determine how many requests Polycarp must add so that before some moment the load on the server strictly increases and after that moment strictly decreases. Both the increasing part and the decreasing part can be empty (i. e. absent). The decrease should immediately follow the increase. In particular, the load with two equal neigbouring values is unacceptable.

For example, if the load is described with one of the arrays \[1, 2, 8, 4, 3\], \[1, 3, 5\] or \[10\], then such load satisfies Polycarp (in each of the cases there is an increasing part, immediately followed with a decreasing part). If the load is described with one of the arrays \[1, 2, 2, 1\], \[2, 1, 2\] or \[10, 10\], then such load does not satisfy Polycarp.

Help Polycarp to make the minimum number of additional requests, so that the resulting load satisfies Polycarp. He can make any number of additional requests at any minute from $ 1 $ to $ n $ .

## 说明/提示

In the first example Polycarp must make two additional requests in the third minute and four additional requests in the fourth minute. So the resulting load will look like: \[1, 4, 5, 6, 5\]. In total, Polycarp will make $ 6 $ additional requests.

In the second example it is enough to make one additional request in the third minute, so the answer is $ 1 $ .

In the third example the load already satisfies all conditions described in the statement, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
1 4 3 2 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
1 2 2 2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
10 20 40 50 70 90 30
```

### 输出

```
0
```

# AI分析结果



【题目翻译】
# 负载测试

## 题目描述

Polycarp计划对其新项目Fakebook进行负载测试。他已经与朋友商定在特定时间点向Fakebook发送请求。测试将持续$n$分钟，在第$i$分钟朋友们将发送$a_i$个请求。

Polycarp希望测试一种特殊形式的负载：当服务被媒体报道后，预计会出现先严格递增后严格递减的负载形式。你需要计算最少需要增加多少请求才能使序列满足这种形式（递增部分和递减部分都可以为空，但相邻元素不能相等）。

## 样例 #1

### 输入
```
5
1 4 3 2 5
```

### 输出
```
6
```

## 样例 #2

### 输入
```
5
1 2 2 2 1
```

### 输出
```
1
```

【算法分类】
前缀和

---

### 题解综合分析

各题解均采用**双数组预处理+枚举峰值点**的核心思路：
1. 预处理从左到右的递增数组`left[]`及其累计增量`cost_left[]`
2. 预处理从右到左的递减数组`right[]`及其累计增量`cost_right[]`
3. 枚举每个位置作为峰值点，计算总操作次数的最小值

关键难点：
1. 峰值点的左右部分必须严格递增递减，且峰值点本身需要同时满足左右约束
2. 处理全递增或全递减的特殊情况
3. 数据范围较大（$n \leq 1e6$），需要O(n)时间复杂度

---

### 高分题解推荐

#### 1. 作者：_Passerby_ (⭐⭐⭐⭐⭐)
**核心亮点**：
- 数学形式化推导最优解表达式
- 引入前缀和数组的差分计算优化
- 完整处理边界情况（全递增/全递减）

**关键代码**：
```cpp
long long calculate() {
    vector<long long> left(n+1), right(n+2), costL(n+1), costR(n+2);
    // 预处理递增序列
    left[1] = a[1];
    for(int i=2; i<=n; i++) {
        left[i] = max(left[i-1]+1, a[i]);
        costL[i] = costL[i-1] + (left[i]-a[i]);
    }
    // 预处理递减序列 
    right[n] = a[n];
    for(int i=n-1; i>=1; i--) {
        right[i] = max(right[i+1]+1, a[i]);
        costR[i] = costR[i+1] + (right[i]-a[i]);
    }
    // 计算最小值
    long long ans = min(costL[n], costR[1]);
    for(int i=2; i<n; i++) {
        long long peak = max(left[i], right[i]);
        ans = min(ans, costL[i-1] + costR[i+1] + (peak - a[i]));
    }
    return ans;
}
```

#### 2. 作者：OIerJiang_1017 (⭐⭐⭐⭐)
**核心亮点**：
- 代码结构清晰，变量命名规范
- 明确处理峰值点冲突的max操作
- 详细注释说明预处理逻辑

**优化点**：
使用滚动变量代替数组可优化空间，但题解代码已满足题目要求

---

### 最优思路总结
**关键技巧**：
1. **双数组预处理**：分别计算每个位置作为递增终点和递减起点的最小高度
2. **前缀和差分**：通过`cost[i] = cost[i-1] + (required_height - a[i])`快速计算累计增量
3. **峰值点处理**：枚举每个可能的峰值点，取`max(left[i], right[i])`保证同时满足左右约束

**拓展应用**：
- 类似的山形数组问题（如LeetCode 1095. 山脉数组）
- 需要同时满足前后约束的最优化问题（如双向动态规划）

---

### 相似题目推荐
1. [P2947 [USACO09MAR] Look Up S](https://www.luogu.com.cn/problem/P2947) - 双向单调栈处理
2. [P2866 [USACO06NOV] Bad Hair Day S](https://www.luogu.com.cn/problem/P2866) - 单调栈与前缀处理
3. [P2550 [AHOI2001] 彩票摇奖](https://www.luogu.com.cn/problem/P2550) - 双指针处理有序序列

---
处理用时：49.10秒