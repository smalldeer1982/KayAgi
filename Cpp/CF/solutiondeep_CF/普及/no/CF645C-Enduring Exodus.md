# 题目信息

# Enduring Exodus

## 题目描述

In an attempt to escape the Mischievous Mess Makers' antics, Farmer John has abandoned his farm and is traveling to the other side of Bovinia. During the journey, he and his $ k $ cows have decided to stay at the luxurious Grand Moo-dapest Hotel. The hotel consists of $ n $ rooms located in a row, some of which are occupied.

Farmer John wants to book a set of $ k+1 $ currently unoccupied rooms for him and his cows. He wants his cows to stay as safe as possible, so he wishes to minimize the maximum distance from his room to the room of his cow. The distance between rooms $ i $ and $ j $ is defined as $ |j-i| $ . Help Farmer John protect his cows by calculating this minimum possible distance.

## 说明/提示

In the first sample, Farmer John can book room $ 3 $ for himself, and rooms $ 1 $ and $ 4 $ for his cows. The distance to the farthest cow is $ 2 $ . Note that it is impossible to make this distance $ 1 $ , as there is no block of three consecutive unoccupied rooms.

In the second sample, Farmer John can book room $ 1 $ for himself and room $ 3 $ for his single cow. The distance between him and his cow is $ 2 $ .

In the third sample, Farmer John books all three available rooms, taking the middle room for himself so that both cows are next to him. His distance from the farthest cow is $ 1 $ .

## 样例 #1

### 输入

```
7 2
0100100
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 1
01010
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 2
000
```

### 输出

```
1
```

# AI分析结果



# 题目中文翻译
# 持久的迁徙

## 题目描述

为了躲避恶作剧制造者的捣乱，农夫约翰离开农场前往牛国另一端。途中，他与他的$k$头奶牛决定入住豪华的Grand Moo-dapest酒店。酒店有$n$个房间排成一列，部分已被占用。

农夫约翰希望预定$k+1$个当前未被占用的连续房间供自己与奶牛使用。为了让奶牛尽可能安全，他希望最小化自己房间到最远奶牛房间的最大距离。房间$i$与$j$的距离定义为$|j-i|$。请帮助计算这个最小可能的最大距离。

## 说明/提示

样例1中，农夫选择3号房，奶牛住1、4号房，最远距离为2。注意无法找到三个连续空房使距离降为1。

样例2选择1号房与3号房，距离为2。

样例3中占据所有三个空房，中间自住，最远距离为1。

# 算法分类
二分

# 题解分析与结论

## 核心思路对比
各题解主要采用以下三种思路：
1. **二分答案+前缀和**（EXODUS）：二分最大距离x，通过前缀和快速验证区间内是否满足k+1空房
2. **连续区间中位数法**（Priori_Incantatem）：枚举连续的k+1空房区间，取中位数位置作为农夫房间
3. **双指针滑动窗口**（Pentiment）：维护当前窗口的最优农夫房间位置

## 最优题解推荐

### 题解1：EXODUS（★★★★★）
**核心亮点**：
- 经典二分答案框架清晰
- 前缀和预处理O(1)验证区间空房数
- 时间复杂度O(n log n)效率稳定

**关键代码**：
```cpp
bool check(int x){
    for(int i=1;i<=n;i++){
        if(s[i]!='0')continue;
        int l=max(i-x,1), r=min(i+x,n);
        if(sum[r]-sum[l-1]>=k+1)return 1;
    }return 0;
}
// 二分主循环
int l=0,r=n,ans=0;
while(l<=r){
    int mid=(l+r)>>1;
    if(check(mid))ans=mid,r=mid-1;
    else l=mid+1;
}
```

### 题解2：Priori_Incantatem（★★★★☆）
**核心亮点**：
- 预处理空房位置降低维度
- 利用中位数性质缩小搜索范围
- 实际运行效率接近线性

**关键优化**：
```cpp
for(int i=0;i+k<t;i++){
    tmp=(a[i+k]+a[i])/2; // 计算理论最优位置
    l=lower_bound(a,a+t-1,tmp)-a; // 二分查找最近空房
    ans=min(ans,max(a[l]-a[i],a[i+k]-a[l]));
    // 检查相邻位置防止边界问题
}
```

### 题解3：cqbzhr（★★★☆☆）
**核心思路**：
- 类似Priori_Incantatem的中位数法
- 直接遍历连续区间取极值
- 未处理边界可能产生误差

# 关键技巧总结
1. **二分答案框架**：处理最值问题的标准解法，重点在check函数设计
2. **前缀和优化**：快速计算任意区间的空房数量，将验证复杂度降为O(n)
3. **中位数性质**：在连续空房区间中，选择中间位置能最小化最大距离
4. **滑动窗口维护**：双指针维护当前有效窗口，动态调整最优位置

# 拓展建议
类似问题可考虑：
- 环形排列的空房选择（如P3512 [POI2010] PIL-Pilots）
- 二维空间中的最优化布局（如P2216 [HAOI2007] 理想的正方形）
- 动态变化的空房状态（结合线段树维护）

# 相似题目推荐
1. P1316 丢瓶盖（二分答案+贪心验证）
2. P2678 跳石头（最大化最小间隔）
3. P1824 进击的奶牛（一维空间最优布局）

---
处理用时：70.20秒