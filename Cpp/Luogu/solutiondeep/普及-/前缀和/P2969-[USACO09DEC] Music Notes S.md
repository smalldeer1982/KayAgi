# 题目信息

# [USACO09DEC] Music Notes S

## 题目描述

FJ is going to teach his cows how to play a song. The song consists of N (1 <= N <= 50,000) notes, and the i-th note lasts for B\_i (1 <= B\_i <= 10,000) beats (thus no song is longer than 500,000,000 beats). The cows will begin playing the song at time 0; thus, they will play note 1 from time 0 through just before time B\_1, note 2 from time B\_1 through just before time B\_1 + B\_2, etc.

However, recently the cows have lost interest in the song, as they feel that it is too long and boring. Thus, to make sure his cows are paying attention, he asks them Q (1 <= Q <= 50,000) questions of the form, 'In the interval from time T through just before time T+1, which note should you be playing?' The cows need your help to answer these questions which are supplied as T\_i (0 <= T\_i <=

end\_of\_song). 

Consider this song with three notes of durations 2, 1, and 3 beats:

```cpp
Beat:   0    1    2    3    4    5    6    ...
        |----|----|----|----|----|----|--- ...
        1111111111     :              :
                  22222:              :
                       333333333333333:
``` 
Here is a set of five queries along with the resulting answer:

Query    Note

2        2

3        3

4        3

0        1

1        1


## 样例 #1

### 输入

```
3 5 
2 
1 
3 
2 
3 
4 
0 
1 
```

### 输出

```
2 
3 
3 
1 
1 
```

# AI分析结果



### 综合分析与结论  
题目核心为快速定位时间点对应的音符。各题解主要采用两种思路：**前缀和+二分**（STL或手写）与**排序查询+线性处理**。最优解为前缀和结合STL的`upper_bound`，时间复杂度为O(n + q log n)，兼顾代码简洁与效率。

---

### 高星题解推荐  
#### 1. 作者：x_faraway_x ⭐⭐⭐⭐⭐  
**关键亮点**：  
- 使用STL的`upper_bound`直接定位第一个大于查询值的前缀和位置，代码简洁高效。  
- 前缀和数组巧妙记录音符结束时间，逻辑清晰。  

**核心代码**：  
```cpp
sum[i] = sum[i-1] + b[i];  // 构建前缀和数组
printf("%d\n", upper_bound(sum+1, sum+1+n, x) - sum);  // 直接输出结果
```

#### 2. 作者：RiverHamster ⭐⭐⭐⭐  
**关键亮点**：  
- 对查询按时间排序后，用指针线性扫描，时间复杂度O(n + q log q)。  
- 维护原始输出顺序，适合处理极大量查询。  

**核心代码**：  
```cpp
sort(a+1, a+1+q, cmptm);  // 按查询时间排序
int p = 1;
for (int i=1; i<=q; i++) {
    while (a[i].tm >= tim[p]) p++;  // 指针线性移动
    a[i].ans = p;
}
```

#### 3. 作者：BBD186587 ⭐⭐⭐⭐  
**关键亮点**：  
- 记录从错误到正确的调试过程，展示暴力→二分优化思路。  
- 手写二分实现，帮助理解底层逻辑。  

**个人心得**：  
> "桶排MLE，暴力TLE，最终二分AC。大数据需注意复杂度！"  

**核心代码**：  
```cpp
int l=1, r=n, mid;
while (l <= r) {
    mid = (l + r) / 2;
    if (T在mid区间内) return mid;
    else if (T在左区间) r = mid-1;
    else l = mid+1;
}
```

---

### 最优思路与技巧总结  
1. **前缀和+二分查找**：  
   - 构建前缀和数组`sum[i]`表示前i个音符的总时长。  
   - 对查询T，用`upper_bound(sum, sum+n+1, T)`找到第一个大于T的位置，其下标即为答案。  
2. **STL高效应用**：`upper_bound`直接处理有序序列，避免手写二分。  
3. **排序优化查询**：当查询数量极大时，排序后线性处理可降低常数因子。  

---

### 拓展与举一反三  
- **类似问题**：区间覆盖查询（如P2280 [HNOI2003]激光炸弹）、动态时间线（如P1502 窗口的星星）。  
- **算法套路**：前缀和+二分适用于静态区间查询；排序+双指针适合离线批量查询。  

---

### 推荐练习题  
1. **P1873 砍树**（二分答案）  
2. **P1020 导弹拦截**（LIS优化，二分维护序列）  
3. **P1044 数字范围查询**（前缀和与区间统计）  

通过练习巩固二分与前缀和的组合应用，提升对时间复杂度的敏感度。

---
处理用时：72.85秒