# 题目信息

# Chain Reaction

## 题目描述

There are $ n $ beacons located at distinct positions on a number line. The $ i $ -th beacon has position $ a_{i} $ and power level $ b_{i} $ . When the $ i $ -th beacon is activated, it destroys all beacons to its left (direction of decreasing coordinates) within distance $ b_{i} $ inclusive. The beacon itself is not destroyed however. Saitama will activate the beacons one at a time from right to left. If a beacon is destroyed, it cannot be activated.

Saitama wants Genos to add a beacon strictly to the right of all the existing beacons, with any position and any power level, such that the least possible number of beacons are destroyed. Note that Genos's placement of the beacon means it will be the first beacon activated. Help Genos by finding the minimum number of beacons that could be destroyed.

## 说明/提示

For the first sample case, the minimum number of beacons destroyed is $ 1 $ . One way to achieve this is to place a beacon at position $ 9 $ with power level $ 2 $ .

For the second sample case, the minimum number of beacons destroyed is $ 3 $ . One way to achieve this is to place a beacon at position $ 1337 $ with power level $ 42 $ .

## 样例 #1

### 输入

```
4
1 9
3 1
6 1
7 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
1 1
2 1
3 1
4 1
5 1
6 1
7 1
```

### 输出

```
3
```

# AI分析结果



# Chain Reaction

## 题目描述

数轴上有 $n$ 个信标，第 $i$ 个信标位于 $a_i$ 处，能量为 $b_i$。当激活第 $i$ 个信标时，会摧毁所有左侧（坐标较小方向）与其距离不超过 $b_i$ 的信标（包含等于的情况）。Saitama 将从右向左依次激活未被摧毁的信标。现允许在最右侧添加一个任意位置和能量的信标，要求计算最少会被摧毁的信标数量。

## 输入输出样例

样例 #1  
输入：
```
4
1 9
3 1
6 1
7 4
```
输出：
```
1
```

样例 #2  
输入：
```
7
1 1
2 1
3 1
4 1
5 1
6 1
7 1
```
输出：
```
3
```

## 算法分类
动态规划

---

## 题解综合分析

### 核心思路
所有题解均采用动态规划结合排序预处理。关键点在于：
1. 将信标按坐标排序后建立连续模型
2. 定义 dp 数组表示保留最大信标数或摧毁最小数量
3. 通过二分查找或线性扫描确定信标影响范围
4. 状态转移时考虑新增信标对右侧信标的摧毁作用

### 最优解法亮点
⭐️ 子翮的题解（4星）
- 将坐标离散化处理，建立位置索引
- 状态转移分三种情况处理：
  ```cpp
  if(没有信标) dp[i] = dp[i-1];
  else if(覆盖全左侧) dp[i] = 1;
  else dp[i] = dp[i-b[i]-1] + 1;
  ```
- 最终答案通过总信标数减去最大保留数求得

⭐️ ListenSnow的题解（4星）
- 使用二分查找确定影响边界：
  ```cpp
  int j = lower_bound(a+1, a+i+1, a[i]-b[i]) - a;
  f[i] = f[j-1] + (i-j)
  ```
- 答案计算时结合右侧未被激活的信标数

⭐️ LincW的题解（4星）
- 明确状态定义：dp[i] 表示从第 i 个信标开始的最小摧毁数
- 通过预处理排序和二分优化转移：
  ```cpp
  int pos = lower_bound(...);
  dp[i] = dp[pos-1] + (i-pos)
  ```

## 关键代码实现

子翮的 DP 核心逻辑：
```cpp
for(int i=0; i<=len; i++) {
    if(mp[i]) {
        int p = power[i];
        if(p >= i) dp[i] = 1;
        else dp[i] = dp[i-p-1] + 1;
    } else {
        dp[i] = dp[i-1];
    }
    ans = max(ans, dp[i]);
}
printf("%d\n", n - ans);
```

## 同类题目推荐
1. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233) - 二维偏序问题
2. [P1095 守望者的逃离](https://www.luogu.com.cn/problem/P1095) - 状态转移与最优决策
3. [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280) - 逆向动态规划应用

## 解题心得
- **排序预处理**是解决离散位置问题的关键（多个题解强调）
- **状态定义方向**影响转移方程复杂度（出言不逊王子提到错误尝试后修正定义）
- **边界处理**需特别注意，如坐标0点是否有信标（Zxsoul题解中的特判）
- **逆向思维**通过保留数推导摧毁数可简化问题（多题解采用n - max保留数）

---
处理用时：53.39秒