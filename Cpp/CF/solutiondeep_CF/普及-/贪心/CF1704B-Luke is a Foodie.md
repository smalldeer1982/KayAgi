# 题目信息

# Luke is a Foodie

## 题目描述

Luke likes to eat. There are $ n $ piles of food aligned in a straight line in front of him. The $ i $ -th pile contains $ a_i $ units of food.

Luke will walk from the $ 1 $ -st pile towards the $ n $ -th pile, and he wants to eat every pile of food without walking back. When Luke reaches the $ i $ -th pile, he can eat that pile if and only if $ |v - a_i| \leq x $ , where $ x $ is a fixed integer, and $ v $ is Luke's food affinity.

Before Luke starts to walk, he can set $ v $ to any integer. Also, for each $ i $ ( $ 1 \leq i \leq n $ ), Luke can change his food affinity to any integer before he eats the $ i $ -th pile.

Find the minimum number of changes needed to eat every pile of food.

Note that the initial choice for $ v $ is not considered as a change.

## 说明/提示

In the first test case, Luke can set $ v $ to $ 5 $ before he starts to walk. And he can walk straight to eat every piles of food without changing $ v $ .

In the second test case, Luke can set $ v $ to $ 3 $ before he starts to walk. And he could change $ v $ to $ 10 $ before he eats the second pile. After that, he can walk straight to eat remaining food without changing $ v $ .

In the fourth test case, Luke can set $ v $ to $ 3 $ before he starts to walk. And he could change $ v $ to $ 8 $ before he eats the sixth pile. After that, he can walk straight to eat remaining food without changing $ v $ .

In the fifth test case, Luke can set $ v $ to $ 4 $ before he starts to walk. And he could change $ v $ to $ 6 $ before he eats the fourth pile. Then he could change $ v $ to $ 12 $ before he eats the seventh pile. After that, he can walk straight to eat remaining food without changing $ v $ .

## 样例 #1

### 输入

```
7
5 3
3 8 5 6 7
5 3
3 10 9 8 7
12 8
25 3 3 17 8 6 1 16 15 25 17 23
10 2
1 2 3 4 5 6 7 8 9 10
8 2
2 4 6 8 6 4 12 14
8 2
2 7 8 9 6 13 21 28
15 5
11 4 13 23 7 10 5 21 20 11 17 5 29 16 11```

### 输出

```
0
1
2
1
2
4
6```

# AI分析结果



# Luke 是个吃货

## 题目描述

Luke 喜欢吃东西。他面前有排成一列的 $n$ 堆食物，第 $i$ 堆有 $a_i$ 单位食物。Luke 从第 $1$ 堆走向第 $n$ 堆，想吃完所有食物且不回头。当走到第 $i$ 堆时，只有当 $|v - a_i| \leq x$ 时才能吃该堆，其中 $x$ 是固定整数，$v$ 是 Luke 的食物亲和度。

Luke 在开始前可以设置 $v$ 为任意整数，且在吃每堆前可以调整 $v$。求最小调整次数（初始设置不计入调整）。

## 样例与说明

样例输入输出详见原题，关键点在于通过维护区间或极值差来最小化调整次数。

---

## 题解分析与结论

### 核心思路
所有优质题解均基于**极值差判定法**：将序列分割为若干段，每段内最大值与最小值之差不超过 $2x$。此时每段只需调整一次 $v$ 值（初始设置视为第0次调整），调整次数即分割次数。

**算法步骤**：
1. 维护当前段的 max/min 值
2. 当新元素加入后若 max-min > 2x，则分割新段
3. 分割次数即为答案

### 最优题解（评分≥4星）

#### 题解作者：luo_shen（5星）
**亮点**：代码简洁高效，思路直击核心，逻辑清晰易理解。
```cpp
int main() {
    int T = read();
    while(T--) {
        n=read(),x=read();
        int mn,mx,ans=0;
        mx=mn=read(); // 初始赋值不计入次数
        for(int i=1;i<n;i++) {
            int now=read();
            mx = max(mx,now);
            mn = min(mn,now);
            if(mx-mn > 2*x) { // 触发分割
                mx=mn=now;
                ans++;
            }
        }
        printf("%d\n",ans);
    }
}
```

#### 题解作者：yinhy09（5星）
**亮点**：完整代码框架，包含读入优化，适合竞赛环境。
```cpp
void solve() {
    ll minn=9e18, maxx=-9e18, ans=0;
    for(int i=1;i<=n;i++) {
        a[i] = read();
        minn = min(minn, a[i]);
        maxx = max(maxx, a[i]);
        if(maxx - minn > 2*x) { // 分割条件
            ans++;
            maxx = minn = a[i];
        }
    }
    printf("%lld\n", ans);
}
```

### 关键技巧总结
1. **极值维护法**：通过动态维护区间最大/小值避免复杂区间计算
2. **分割条件**：max-min > 2x 时必然需要调整，将问题转化为序列分割
3. **贪心思想**：每次尽可能延长当前段长度，确保全局最优

### 同类题目推荐
1. [CF1304C Air Conditioner](https://www.luogu.com.cn/problem/CF1304C)（温度区间交集维护）
2. [P3143 Diamond Collector S](https://www.luogu.com.cn/problem/P3143)（极值差限定下的序列分割）
3. [P2216 [HAOI2007] 理想的正方形](https://www.luogu.com.cn/problem/P2216)（二维滑动窗口极值维护）

### 个人心得摘录
- **初始值处理**：初始设置不算调整次数，需将首个元素同时设为初始 max/min
- **分割重置**：触发分割后要立即将当前元素设为新段的初始极值
- **复杂度控制**：O(n) 遍历是此类题的标准解法，避免复杂数据结构

---
处理用时：62.43秒