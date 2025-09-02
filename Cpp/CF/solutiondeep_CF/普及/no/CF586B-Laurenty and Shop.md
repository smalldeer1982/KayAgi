# 题目信息

# Laurenty and Shop

## 题目描述

A little boy Laurenty has been playing his favourite game Nota for quite a while and is now very hungry. The boy wants to make sausage and cheese sandwiches, but first, he needs to buy a sausage and some cheese.

The town where Laurenty lives in is not large. The houses in it are located in two rows, $ n $ houses in each row. Laurenty lives in the very last house of the second row. The only shop in town is placed in the first house of the first row.

The first and second rows are separated with the main avenue of the city. The adjacent houses of one row are separated by streets.

Each crosswalk of a street or an avenue has some traffic lights. In order to cross the street, you need to press a button on the traffic light, wait for a while for the green light and cross the street. Different traffic lights can have different waiting time.

The traffic light on the crosswalk from the $ j $ -th house of the $ i $ -th row to the $ (j+1) $ -th house of the same row has waiting time equal to $ a_{ij} $ ( $ 1<=i<=2,1<=j<=n-1 $ ). For the traffic light on the crossing from the $ j $ -th house of one row to the $ j $ -th house of another row the waiting time equals $ b_{j} $ ( $ 1<=j<=n $ ). The city doesn't have any other crossings.

The boy wants to get to the store, buy the products and go back. The main avenue of the city is wide enough, so the boy wants to cross it exactly once on the way to the store and exactly once on the way back home. The boy would get bored if he had to walk the same way again, so he wants the way home to be different from the way to the store in at least one crossing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF586B/04e19dedf810ee5c633b66631501e6fe5923174b.png)Figure to the first sample.Help Laurenty determine the minimum total time he needs to wait at the crossroads.

## 说明/提示

The first sample is shown on the figure above.

In the second sample, Laurenty's path can look as follows:

- Laurenty crosses the avenue, the waiting time is $ 3 $ ;
- Laurenty uses the second crossing in the first row, the waiting time is $ 2 $ ;
- Laurenty uses the first crossing in the first row, the waiting time is $ 1 $ ;
- Laurenty uses the first crossing in the first row, the waiting time is $ 1 $ ;
- Laurenty crosses the avenue, the waiting time is $ 1 $ ;
- Laurenty uses the second crossing in the second row, the waiting time is $ 3 $ .

 In total we get that the answer equals $ 11 $ .In the last sample Laurenty visits all the crossings, so the answer is $ 4 $ .

## 样例 #1

### 输入

```
4
1 2 3
3 2 1
3 2 2 3
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3
1 2
3 3
2 1 3
```

### 输出

```
11
```

## 样例 #3

### 输入

```
2
1
1
1 1
```

### 输出

```
4
```

# AI分析结果



# Laurenty and Shop

## 题目描述

小男孩Laurenty需要从家到商店买食材并返回，路径必须满足往返路线不同。城镇有两排各n栋房屋，商店在第一排首，家在第二排尾。所有街道和主大道的交通灯有不同等待时间。求总等待时间的最小值。

**算法分类**：枚举、前缀和

## 题解对比与结论

### 最优思路
1. **预处理前缀和与后缀和**：计算从各中间点穿过主大道后到达商店（或回家）的累计时间。
2. **双重循环枚举不同路径**：确保去程和返程路径通过不同的中间点，避免路径重复。
3. **时间复杂度优化**：利用前缀和与后缀和预处理将单路径计算复杂度降为O(1)，总复杂度O(n²)。

---

### 高星题解推荐

#### 题解四（作者：_Rainlzy）⭐️⭐️⭐️⭐️
**亮点**  
- 代码简洁，利用前缀和与后缀和预处理各路径时间。
- 双重循环确保路径不重复，完全符合题意要求。

**核心代码**  
```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        if(i==j) continue;
        minn = a[i] + f[i] + b[i];   // 去程路径i的时间
        minn += a[j] + f[j] + b[j];  // 返程路径j的时间
        ans = min(minn, ans);
    }
```
**实现思路**  
- 前缀和`a[i]`表示从第一排第i栋到首栋的累计时间。
- 后缀和`b[i]`表示从第二排第i栋到尾栋的累计时间。
- 枚举所有不同中间点组合，计算总时间最小值。

---

#### 题解三（作者：skyskyCCC）⭐️⭐️⭐️⭐️
**亮点**  
- 明确使用前后缀和优化路径计算。
- 代码逻辑清晰，注释辅助理解。

**个人心得**  
> "这道题本来想找最短路和次小路的，但开数组时才发现不需要，要加训了。"  
> —— 作者反思了预处理优化的必要性。

---

### 拓展思路
- **同类问题**：网格路径问题常结合前缀和/动态规划优化。
- **变形题**：若允许多次穿越主大道，可转化为最短路径问题（如Dijkstra算法）。

---

### 推荐习题
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)（枚举与剪枝）
2. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（前缀和优化）
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)（图论最短路）

---
处理用时：281.65秒