# 题目信息

# Greenhouse Effect

## 题目描述

Emuskald is an avid horticulturist and owns the world's longest greenhouse — it is effectively infinite in length.

Over the years Emuskald has cultivated $ n $ plants in his greenhouse, of $ m $ different plant species numbered from 1 to $ m $ . His greenhouse is very narrow and can be viewed as an infinite line, with each plant occupying a single point on that line.

Emuskald has discovered that each species thrives at a different temperature, so he wants to arrange $ m-1 $ borders that would divide the greenhouse into $ m $ sections numbered from 1 to $ m $ from left to right with each section housing a single species. He is free to place the borders, but in the end all of the $ i $ -th species plants must reside in $ i $ -th section from the left.

Of course, it is not always possible to place the borders in such way, so Emuskald needs to replant some of his plants. He can remove each plant from its position and place it anywhere in the greenhouse (at any real coordinate) with no plant already in it. Since replanting is a lot of stress for the plants, help Emuskald find the minimum number of plants he has to replant to be able to place the borders.

## 说明/提示

In the first test case, Emuskald can replant the first plant to the right of the last plant, so the answer is 1.

In the second test case, the species are already in the correct order, so no replanting is needed.

## 样例 #1

### 输入

```
3 2
2 1
1 2.0
1 3.100
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 5.0
2 5.5
3 6.0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 3
1 14.284235
2 17.921382
1 20.328172
3 20.842331
1 25.790145
1 27.204125
```

### 输出

```
2
```

# AI分析结果



### 题目中文翻译
# 温室效应

## 题目描述

Emuskald是一位狂热的园艺爱好者，拥有世界上最长的温室——其长度实际上是无限的。

多年来，Emuskald在温室中培育了$n$株植物，分属$m$个不同的物种（编号1到$m$）。温室非常狭窄，可以视为一条无限长的直线，每株植物占据直线上的一个点。

Emuskald发现每个物种在不同温度下生长最佳，因此他希望布置$m-1$个分界线，将温室从左到右划分为$m$个区域（编号1到$m$），每个区域只包含一个物种的植物。他可以自由放置分界线，但最终所有第$i$个物种的植物必须位于第$i$个区域。

由于可能无法直接通过分界线实现目标，Emuskald需要重新种植部分植物。他可以将任意植物移动到空位（任意实数坐标）。请求出最少需要移动的植物数量。

## 说明/提示

第一个测试案例中，可将第一株植物移到最后一株右侧，答案为1。

第二个测试案例中，物种已按正确顺序排列，无需移动。

---

**算法分类**：动态规划

---

### 题解综合分析
本题核心在于通过最长非递减子序列（LIS）求解最大保留植物数。数轴的无限性允许任意插入位置，只需保证物种编号的单调性，最终移动次数为总数量减去LIS长度。

---

### 精选题解（评分≥4星）

1. **lotus_grow（★★★★★）**
   **关键亮点**：
   - 使用`upper_bound`实现O(n log n)的LIS优化算法
   - 代码简洁高效，直接处理输入流
   **核心代码**：
   ```cpp
   memset(f,0x3f,sizeof(f));
   for(int i=1,x;i<=n;i++) {
       scanf("%d%lf",&x,&t);
       *upper_bound(f+1,f+n+1,x)=x;
   }
   ans=n+1-(lower_bound(f+1,f+n+1,0x3f3f3f3f)-f);
   ```
   **实现思想**：维护单调数组，通过二分查找快速更新最长序列。

2. **ZolaWatle（★★★★☆）**
   **关键亮点**：
   - 传统DP思路清晰，适合理解基础LIS原理
   - 完整展示状态转移过程
   **核心代码**：
   ```cpp
   for(int i=2;i<=n;i++)
       for(int j=1;j<i;j++)
           if(a[i]>=a[j])
               dp[i]=max(dp[i],dp[j]+1);
   ```
   **实现思想**：双重循环遍历，动态更新每个位置的最优解。

3. **__JiCanDuck__（★★★★☆）**
   **个人心得**：
   > "位置是没有用的。我们只需要将种类排成单调不降序列即可"
   **代码亮点**：简洁的O(n²)实现，适合教学演示。

---

### 最优思路总结
**关键技巧**：将物理位置问题转化为序列单调性问题，利用LIS模型求解最大保留数。实数位置的无限性消除了插入位置的限制，使问题简化为纯序列分析。

**算法优化**：优先采用贪心+二分的O(n log n)解法处理较大数据规模。

---

### 拓展训练
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)（LIS经典应用）
2. [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)（转化为LIS问题）
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)（双向LIS应用）

---
处理用时：55.40秒