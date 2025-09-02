# 题目信息

# [USACO18JAN] Blocked Billboard II B

## 题目描述

Bessie the cow used to have such a nice view from her barn, looking across road at a set of two billboards advertising delicious looking cow feed. Unfortunately, one of these billboards has recently been updated so it now advertises "Farmer Larry's Lawnmowers". Bessie is not a fan of lawnmowers since their only purpose, as far as she can tell, is cutting back the grass in her field that she finds so tasty (if you haven't noticed, much of Bessie's thought process revolves around food).

Fortunately, the remaining cow feed billboard is situated in front of the lawnmower billboard, potentially obscuring it.

Bessie, determined to remove the offensive lawnmower billboard completely from her view, hatches a risky plan. She plans to steal a large rectangular tarp from the barn and sneak out late at night to cover the remaining portion of the lawnmower billboard, so that she can no longer see any part of it.

Given the locations of the two billboards, please help Bessie compute the minimum area of the tarp she will need. Since the only tarps available in the barn are rectangular in size, Bessie observes that she may conceivably need a tarp whose area is slightly larger than the exposed area of the lawnmower billboard, as illustrated in the example below. The tarp may only be placed such that its sides are parallel to those of the other billboards (i.e., it cannot be "tilted"). 

## 说明/提示

### Sample Explanation 1

Here, the cow feed billboard obscures the lower right corner of the lawnmower billboard, but this doesn't really help, since Bessie still needs to use a tarp whose size is as large as the entire lawnmower billboard. 

## 样例 #1

### 输入

```
2 1 7 4
5 -1 10 3```

### 输出

```
15```

# AI分析结果



### 综合分析与结论
本题解核心在于处理两个矩形的覆盖关系，存在两种主流解法：  
1. **数学几何法**（O(1)）：通过分类讨论两矩形的位置关系（完全覆盖/部分覆盖/无覆盖），直接计算最小覆盖面积  
2. **暴力标记法**（O(n²)）：利用坐标范围小的特点，通过二维数组标记区域后遍历求极值  

最优解法为数学几何法，其优势在于时间复杂度低且代码简洁，但需要严密的逻辑覆盖所有情况。暴力法虽然直观，但存在冗余计算且需处理坐标偏移。

---

### 精选题解与评分

#### 1. 作者：cff_0102（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**：  
- 系统性地划分所有覆盖情况（完全覆盖、单边覆盖、无覆盖）  
- 每个条件独立判断并直接输出结果，代码高效简洁  
- 包含清晰的图示链接辅助理解  

**核心代码**：
```cpp
if(x1_<=x1 && x2<=x2_ && y1_<=y1 && y2<=y2_) cout<<0,exit(0);
// 完全覆盖则直接返回0
if(x1<x1_ && x1_<x2 && x2<=x2_ && y1_<=y1 && y2<=y2_) // 右覆盖情况
  cout<<(x1_-x1)*(y2-y1),exit(0);
// 其余三种单边覆盖判断类似...
cout<<(x2-x1)*(y2-y1); // 默认返回原面积
```

#### 2. 作者：Silent1019（⭐️⭐️⭐️⭐️）
**关键亮点**：  
- 清晰的坐标偏移处理（+1000解决负数下标问题）  
- 两次遍历分别求极值，逻辑简明  
- 特判全覆盖情况  

**代码亮点**：
```cpp
for(int i=s[0][0];i<s[0][2];i++) // 标记割草机广告
  for(int j=s[0][1];j<s[0][3];j++)
    g[i][j] = 1;
for(int i=s[1][0];i<s[1][2];i++) // 覆盖标记为0
  for(int j=s[1][1];j<s[1][3];j++)
    g[i][j] = 0;
```

---

### 关键思路与技巧
1. **几何分类讨论核心逻辑**：  
   - 完全覆盖：`A.x1 ≤ B.x1 ∧ B.x2 ≤ A.x2 ∧ A.y1 ≤ B.y1 ∧ B.y2 ≤ A.y2`  
   - 单边覆盖：检查是否有一条边被完全覆盖（上下左右共4种情况）  
   - 无有效覆盖时返回原面积  

2. **暴力法注意事项**：  
   - 坐标偏移处理：`x+1000` 避免负数下标  
   - 循环边界处理：注意左闭右开或左闭右闭的一致性  

---

### 拓展与相似题目
1. [P1883 函数](https://www.luogu.com.cn/problem/P1883) - 极值问题与区间覆盖思想  
2. [P1318 积水面积](https://www.luogu.com.cn/problem/P1318) - 二维区域标记与极值计算  
3. [P2331 [SCOI2005] 最大子矩阵](https://www.luogu.com.cn/problem/P2331) - 矩形覆盖的动态规划处理  

---

### 题解中的调试心得
1. **坐标偏移必要性**：  
   - 多篇题解提到必须加1000偏移量避免RE，如："数组下标不能是负数，所以加上1000"  
2. **条件判断顺序**：  
   - 需先判断完全覆盖，否则可能漏判特殊情形  
3. **边界值陷阱**：  
   - 部分代码使用 `i <= x2` 而非 `i < x2`，需确认题目是否将坐标视为点或格子

---
处理用时：47.09秒