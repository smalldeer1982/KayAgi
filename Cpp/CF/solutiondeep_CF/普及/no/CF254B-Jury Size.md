# 题目信息

# Jury Size

## 题目描述

In 2013, the writers of Berland State University should prepare problems for $ n $ Olympiads. We will assume that the Olympiads are numbered with consecutive integers from 1 to $ n $ . For each Olympiad we know how many members of the jury must be involved in its preparation, as well as the time required to prepare the problems for her. Namely, the Olympiad number $ i $ should be prepared by $ p_{i} $ people for $ t_{i} $ days, the preparation for the Olympiad should be a continuous period of time and end exactly one day before the Olympiad. On the day of the Olympiad the juries who have prepared it, already do not work on it.

For example, if the Olympiad is held on December 9th and the preparation takes 7 people and 6 days, all seven members of the jury will work on the problems of the Olympiad from December, 3rd to December, 8th (the jury members won't be working on the problems of this Olympiad on December 9th, that is, some of them can start preparing problems for some other Olympiad). And if the Olympiad is held on November 3rd and requires 5 days of training, the members of the jury will work from October 29th to November 2nd.

In order not to overload the jury the following rule was introduced: one member of the jury can not work on the same day on the tasks for different Olympiads. Write a program that determines what the minimum number of people must be part of the jury so that all Olympiads could be prepared in time.

## 样例 #1

### 输入

```
2
5 23 1 2
3 13 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
12 9 2 1
12 8 1 3
12 8 2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1
1 10 1 13
```

### 输出

```
1
```

# AI分析结果



【题目翻译】
# 陪审团人数

## 题目描述

2013年，Berland州立大学的出题组需要为n场奥林匹克竞赛准备题目。每场竞赛编号为1到n的连续整数。已知每场竞赛需要p_i名评委参与题目准备，且需要连续工作t_i天。准备工作必须在竞赛开始前一天完成，竞赛当天评委不再参与该场竞赛的准备工作。

例如：若竞赛在12月9日举行，需要7名评委准备6天，则这7人将在12月3日至12月8日工作（12月9日不工作）。若竞赛在11月3日举行且需要5天准备，评委将在10月29日至11月2日工作。

限制条件：每位评委在同一天不能参与多场竞赛的准备工作。求满足所有竞赛需求的最小评委人数。

【算法分类】
差分

【题解分析】

### 通用思路
1. **日期转换**：将月份+日期转换为一年中的第几天
2. **跨年处理**：通过+100天将可能跨越上一年的日期映射到数组有效范围内
3. **区间处理**：使用差分数组优化区间累加操作，最后求前缀和得到每日需求人数
4. **最大值统计**：在有效日期范围内求最大值即为答案

### 最优思路提炼
1. **差分数组**：通过区间首+1、区间尾+1位置-1的操作，将O(n*d)复杂度优化为O(n+D)
2. **偏移处理**：通过+100天将可能为负数的日期转换为正数索引
3. **前缀和优化**：差分数组的前缀和即为每日实际需求人数

【精选题解】

⭐️⭐️⭐️⭐️⭐️ 作者：封禁用户（差分版）
**亮点**：同时提供暴力与差分解法，完整处理跨年边界，代码简洁
```cpp
int k[13] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
//...
int st = k[mon] + day - tim + 101;
int la = k[mon] + day + 100;
t[la + 1] -= peo, t[st] += peo;
for (int i = 1; i <= 465; i++) t[i] += t[i - 1];
```

⭐️⭐️⭐️⭐️⭐️ 作者：nominater
**亮点**：规范使用差分模板，明确注释关键步骤
```cpp
l = d[month[i]] + day[i] - con[i] + 101;
r = d[month[i]] + day[i] + 100;
f[r+1]-=person[i],f[l]+=person[i];
//...
for (int i = 1; i <= 465; i++) f[i] += f[i - 1];
```

【关键代码实现】
```cpp
int days[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334};
int diff[1000] = {0}; // 差分数组

// 处理每个竞赛
int month = 12, day = 8, people = 2, duration = 5;
int start_day = days[month] + day - duration + 100 + 1; // +100处理跨年
int end_day = days[month] + day + 100;
diff[start_day] += people;
diff[end_day + 1] -= people;

// 计算前缀和并求最大值
int max_people = 0;
for(int i=1; i<=700; i++){
    diff[i] += diff[i-1];
    if(i >= 101 && i <= 465) max_people = max(max_people, diff[i]);
}
```

【拓展总结】
1. **同类问题**：所有涉及区间覆盖统计的问题（如会议室安排、课程时间冲突）
2. **调试技巧**：注意日期转换的边界值（如2月天数、数组偏移量）
3. **优化经验**：当遇到区间累加问题时，优先考虑差分数组优化

【推荐习题】
1. P1719 最大加权矩形（二维差分）
2. P3406 海底高铁（区间覆盖统计）
3. P3667 太阳（环形区间处理）

---
处理用时：60.33秒