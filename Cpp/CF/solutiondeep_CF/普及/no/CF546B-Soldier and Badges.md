# 题目信息

# Soldier and Badges

## 题目描述

Colonel has $ n $ badges. He wants to give one badge to every of his $ n $ soldiers. Each badge has a coolness factor, which shows how much it's owner reached. Coolness factor can be increased by one for the cost of one coin.

For every pair of soldiers one of them should get a badge with strictly higher factor than the second one. Exact values of their factors aren't important, they just need to have distinct factors.

Colonel knows, which soldier is supposed to get which badge initially, but there is a problem. Some of badges may have the same factor of coolness. Help him and calculate how much money has to be paid for making all badges have different factors of coolness.

## 说明/提示

In first sample test we can increase factor of first badge by $ 1 $ .

In second sample test we can increase factors of the second and the third badge by $ 1 $ .

## 样例 #1

### 输入

```
4
1 3 1 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
5
1 2 3 2 5
```

### 输出

```
2```

# AI分析结果



# Soldier and Badges

## 题目描述

上校有 $n$ 枚徽章，每枚徽章有一个酷炫值。他需要将这些徽章分配给 $n$个士兵，每个士兵一枚徽章。每个徽章的酷炫值可以通过支付硬币增加（每花费 1 个硬币可增加 1 点酷炫值）。

要求所有士兵的徽章酷炫值必须严格不同。现给定初始分配方案，求最少需要支付多少硬币。

## 说明/提示

样例 1 中：将第一个徽章 +1 后得到 [2,3,1,4]（实际只需保证严格不同，顺序无关）

样例 2 中：将第二个和第三个徽章各 +1 后得到 [1,3,4,2,5]

## 样例 #1

### 输入
```
4
1 3 1 4
```

### 输出
```
1
```

## 样例 #2

### 输入
```
5
1 2 3 2 5
```

### 输出
```
2
```

---

**算法分类**：贪心

---

### 题解分析与结论

各题解核心思路均围绕排序后调整元素实现严格递增，核心差异在于实现方式：
1. **桶排序法**：统计频次后将冗余元素右移（时间复杂度 O(n)）
2. **直接排序法**：排序后强制递增，累加差值（时间复杂度 O(nlogn)）
3. **总和差值法**：计算调整前后总和差值（本质与直接排序法相同）

---

### 精选题解

#### 题解1：test_check（桶排序法） ⭐⭐⭐⭐
**核心亮点**：  
- 利用桶数组统计元素出现次数  
- 将多余元素向右扩散，保证每个桶只保留一个元素  
- 空间换时间（需开两倍数组避免越界）  

**代码核心**：
```cpp
int flag[6001] = {0}; // 统计桶
for(int i=1; i<=n*2; i++) {
    if(flag[i]>1) {
        flag[i+1] += (flag[i]-1); // 右移多余元素
        sum += (flag[i]-1);       // 累加操作次数
        flag[i] = 1;
    }
}
```

#### 题解2：tryrtj（直接排序法） ⭐⭐⭐⭐  
**核心亮点**：  
- 排序后强制递增序列，直观易理解  
- 线性扫描处理重复元素  
- 代码简洁高效（时间复杂度 O(nlogn)）

**代码核心**：
```cpp
sort(a, a+n);
int q = a[0];
for(int i=1; i<n; i++) {
    if(a[i] <= q) {
        zong += q+1 - a[i];
        q++; 
    } else {
        q = a[i];
    }
}
```

---

### 关键思路总结
1. **排序预处理**：通过排序将问题转化为单调递增序列调整问题  
2. **贪心调整**：每个元素至少比前一个大 1，保证局部最优  
3. **差值累加**：总调整量等于调整后序列总和与原序列总和的差值  

---

### 同类题目推荐
1. [P1152 欢乐的跳](https://www.luogu.com.cn/problem/P1152) - 相邻差值处理  
2. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240) - 典型贪心策略  
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心选择最优解  

---

### 实践心得摘录
> "如果一意孤行，flag数组开小会导致RE" —— test_check  
> 调试中发现必须开两倍数组空间，否则在极端数据下会越界。这提醒我们处理桶排序时要仔细分析最坏情况的空间需求。

---
处理用时：63.11秒