# 题目信息

# Taxi drivers and Lyft

## 题目描述

Palo Alto is an unusual city because it is an endless coordinate line. It is also known for the office of Lyft Level 5.

Lyft has become so popular so that it is now used by all $ m $ taxi drivers in the city, who every day transport the rest of the city residents — $ n $ riders.

Each resident (including taxi drivers) of Palo-Alto lives in its unique location (there is no such pair of residents that their coordinates are the same).

The Lyft system is very clever: when a rider calls a taxi, his call does not go to all taxi drivers, but only to the one that is the closest to that person. If there are multiple ones with the same distance, then to taxi driver with a smaller coordinate is selected.

But one morning the taxi drivers wondered: how many riders are there that would call the given taxi driver if they were the first to order a taxi on that day? In other words, you need to find for each taxi driver $ i $ the number $ a_{i} $ — the number of riders that would call the $ i $ -th taxi driver when all drivers and riders are at their home?

The taxi driver can neither transport himself nor other taxi drivers.

## 说明/提示

In the first example, we have only one taxi driver, which means an order from any of $ n $ riders will go to him.

In the second example, the first taxi driver lives at the point with the coordinate $ 2 $ , and the second one lives at the point with the coordinate $ 6 $ . Obviously, the nearest taxi driver to the rider who lives on the $ 3 $ coordinate is the first one, and to the rider who lives on the coordinate $ 5 $ is the second one. The rider who lives on the $ 4 $ coordinate has the same distance to the first and the second taxi drivers, but since the first taxi driver has a smaller coordinate, the call from this rider will go to the first taxi driver.

In the third example, we have one rider and the taxi driver nearest to him is the fourth one.

## 样例 #1

### 输入

```
3 1
1 2 3 10
0 0 1 0
```

### 输出

```
3 ```

## 样例 #2

### 输入

```
3 2
2 3 4 5 6
1 0 0 0 1
```

### 输出

```
2 1 ```

## 样例 #3

### 输入

```
1 4
2 4 6 10 15
1 1 1 1 0
```

### 输出

```
0 0 0 1 ```

# AI分析结果

### 题目内容重写

**题目描述**

Palo Alto 是一个不寻常的城市，因为它是一个无限的坐标线。它也因为 Lyft Level 5 的办公室而闻名。

Lyft 变得如此流行，以至于现在城市中的所有 $m$ 个出租车司机都在使用它，他们每天运送城市中的其他居民——$n$ 个乘客。

每个居民（包括出租车司机）在 Palo Alto 都有一个独特的位置（没有两个居民的坐标是相同的）。

Lyft 系统非常聪明：当一个乘客叫车时，他的呼叫不会发送给所有的出租车司机，而是只发送给离他最近的那个司机。如果有多个司机距离相同，则选择坐标较小的那个司机。

但有一天早上，出租车司机们想知道：有多少乘客会叫他们的车，如果他们是当天第一个叫车的司机？换句话说，你需要为每个出租车司机 $i$ 找到 $a_{i}$ —— 当所有司机和乘客都在家时，会叫第 $i$ 个司机的乘客数量。

出租车司机不能运送自己或其他出租车司机。

**说明/提示**

在第一个例子中，我们只有一个出租车司机，这意味着任何 $n$ 个乘客的订单都会发送给他。

在第二个例子中，第一个出租车司机住在坐标为 $2$ 的点，第二个司机住在坐标为 $6$ 的点。显然，住在坐标为 $3$ 的乘客最近的司机是第一个，而住在坐标为 $5$ 的乘客最近的司机是第二个。住在坐标为 $4$ 的乘客到第一个和第二个司机的距离相同，但由于第一个司机的坐标较小，这个乘客的呼叫会发送给第一个司机。

在第三个例子中，我们有一个乘客，离他最近的司机是第四个。

**样例 #1**

### 输入

```
3 1
1 2 3 10
0 0 1 0
```

### 输出

```
3 ```

**样例 #2**

### 输入

```
3 2
2 3 4 5 6
1 0 0 0 1
```

### 输出

```
2 1 ```

**样例 #3**

### 输入

```
1 4
2 4 6 10 15
1 1 1 1 0
```

### 输出

```
0 0 0 1 ```

### 算法分类
二分

### 题解分析与结论

本题的核心问题是为每个出租车司机计算有多少乘客会选择他们作为最近的司机。由于坐标是唯一的，且所有位置都是有序的，因此可以通过二分查找来优化查找过程，避免暴力枚举。

#### 题解对比与评分

1. **题解作者：_Cloud_**
   - **评分：5星**
   - **关键亮点**：使用前缀和与后缀和的思路，分别记录每个位置左边和右边最近的司机，然后通过比较距离来确定每个乘客的选择。代码实现简洁，时间复杂度为 $O(n+m)$，是目前最快的方法。
   - **代码核心思想**：
     ```cpp
     for (int i = 1; i <= n + m; i++) {
         if (a[i].s == 0) {
             if (sumf[i] == 214748364 && sumb[i] < 214748364) {
                 ans[sumb[i]]++;
                 continue;
             }
             if ((sumb[i] == 214748364 && sumf[i] < 214748364)) {
                 ans[sumf[i]]++;
                 continue;
             }
             if (a[i].z - a[sumf[i]].z <= a[sumb[i]].z - a[i].z) {
                 ans[sumf[i]]++;
             } else {
                 ans[sumb[i]]++;
             }
         }
     }
     ```

2. **题解作者：DarkShadow**
   - **评分：4星**
   - **关键亮点**：通过预处理每个乘客左右两边的司机，然后通过比较距离来确定每个乘客的选择。代码实现清晰，时间复杂度为 $O(n+m)$。
   - **代码核心思想**：
     ```cpp
     for (int i = 1; i <= n + m; i++) {
         if (d[i]) continue;
         if (lst[i] == 0) t = nxt[i];
         else if (nxt[i] == 0) t = lst[i];
         else if (pos[i] - pos[lst[i]] <= pos[nxt[i]] - pos[i]) t = lst[i];
         else t = nxt[i];
         ans[t]++;
     }
     ```

3. **题解作者：TRZ_2007**
   - **评分：4星**
   - **关键亮点**：使用二分查找来确定每个乘客最近的司机，时间复杂度为 $O(n \log m)$，代码实现简洁。
   - **代码核心思想**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         if (p[i] >= d[m]) { ans[m]++; continue; }
         id = lower_bound(d + 1, d + m + 1, p[i]) - d;
         if (d[id] - p[i] >= p[i] - d[id - 1]) ++ans[id - 1];
         else ++ans[id];
     }
     ```

### 最优关键思路或技巧

1. **前缀和与后缀和**：通过预处理每个位置左边和右边最近的司机，可以快速确定每个乘客的选择，时间复杂度为 $O(n+m)$。
2. **二分查找**：对于每个乘客，使用二分查找来确定最近的司机，时间复杂度为 $O(n \log m)$。

### 可拓展之处

1. **类似问题**：可以扩展到多维空间中的最近邻问题，使用类似的前缀和或二分查找方法。
2. **优化思路**：如果坐标范围较大，可以考虑使用离散化来优化空间复杂度。

### 推荐题目

1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

### 个人心得摘录

1. **_Cloud_**：通过前缀和与后缀和的思路，可以快速确定每个乘客的选择，代码实现简洁，是目前最快的方法。
2. **DarkShadow**：预处理每个乘客左右两边的司机，然后通过比较距离来确定每个乘客的选择，代码实现清晰。
3. **TRZ_2007**：使用二分查找来确定每个乘客最近的司机，代码实现简洁，时间复杂度为 $O(n \log m)$。

---
处理用时：42.12秒