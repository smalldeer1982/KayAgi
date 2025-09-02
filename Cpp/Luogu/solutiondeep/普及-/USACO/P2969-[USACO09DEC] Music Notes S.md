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
本题核心是区间归属查询，各题解主要围绕两种思路展开：
1. **前缀和+二分查找**：通过计算音符时间的前缀和数组，利用二分快速定位查询点所在区间（时间复杂度O(n + q log n)）
2. **离线排序+线性扫描**：将查询按时间排序后，结合有序的音符时间进行线性匹配（时间复杂度O(n + q log q)）

其中第一种思路被更多题解采用，尤其利用STL的`upper_bound`函数实现极简代码，是该题的最优解。

---

### 高星题解推荐（评分≥4星）

#### 1. x_faraway_x（★★★★★）
**核心亮点**：
- 使用STL的`upper_bound`实现5行核心逻辑
- 代码极简（仅22行），可读性极佳
- 时间复杂度最优（O(n + q log n)）
**关键代码**：
```cpp
sum[i] = sum[i-1] + b[i]; // 前缀和数组
printf("%d\n", upper_bound(sum+1,sum+1+n,x)-sum); // 直接STL二分
```

#### 2. RiverHamster（★★★★☆）
**核心亮点**：
- 离线处理思路新颖，适合海量查询场景
- 通过双排序避免重复计算
- 时间复杂度稳定（O(n + q log q)）
**关键实现**：
```cpp
sort(a+1,a+1+q,cmptm); // 按查询时间排序
int p=1; // 线性扫描指针
for(int i=1;i<=q;i++){
    if(a[i].tm<tim[p]) a[i].ans=p;
    else p++,i--; // 指针不回退
}
```

#### 3. BBD186587（★★★★☆）
**核心亮点**：
- 详细记录从暴力到二分的优化过程
- 手写二分帮助理解底层逻辑
- 包含调试心路历程，对新人友好
**调试心得**：
> "这道橙题我交了十几发才过，所以来交发题解纪念下" —— 通过尝试桶排、暴力枚举最终理解二分必要性，展示典型调试过程

---

### 最优思路提炼
**前缀和 + STL二分**：
1. 预处理前缀和数组`sum[]`，其中`sum[i]`表示前i个音符的总时间
2. 对查询值x，找到最小的i满足`sum[i] > x`（即`upper_bound`）
3. 时间复杂度：O(n)预处理 + O(q log n)查询

**关键代码模板**：
```cpp
// 预处理
vector<int> sum(n+1);
partial_sum(begin(b), end(b), sum.begin()+1);

// 查询处理
int query(int x) {
    return upper_bound(sum.begin()+1, sum.end(), x) - sum.begin();
}
```

---

### 拓展与延伸
**同类问题套路**：
1. **区间归属问题**：转化为有序序列的二分查找（如IP地址归属、时间区间查询）
2. **离线处理**：当查询可预先排序时，指针扫描法能显著降低时间复杂度
3. **STL应用**：`lower_bound/upper_bound`可解决90%的二分场景

**推荐练习题**：
1. [P1873 砍树](https://www.luogu.com.cn/problem/P1873)（二分答案）
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)（贪心+二分维护序列）
3. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（二分答案+区间验证）

---
处理用时：67.96秒