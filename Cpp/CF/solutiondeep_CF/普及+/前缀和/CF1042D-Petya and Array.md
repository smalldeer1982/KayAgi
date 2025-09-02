# 题目信息

# Petya and Array

## 题目描述

Petya has an array $ a $ consisting of $ n $ integers. He has learned partial sums recently, and now he can calculate the sum of elements on any segment of the array really fast. The segment is a non-empty sequence of elements standing one next to another in the array.

Now he wonders what is the number of segments in his array with the sum less than $ t $ . Help Petya to calculate this number.

More formally, you are required to calculate the number of pairs $ l, r $ ( $ l \le r $ ) such that $ a_l + a_{l+1} + \dots + a_{r-1} + a_r < t $ .

## 说明/提示

In the first example the following segments have sum less than $ 4 $ :

- $ [2, 2] $ , sum of elements is $ -1 $
- $ [2, 3] $ , sum of elements is $ 2 $
- $ [3, 3] $ , sum of elements is $ 3 $
- $ [4, 5] $ , sum of elements is $ 3 $
- $ [5, 5] $ , sum of elements is $ -1 $

## 样例 #1

### 输入

```
5 4
5 -1 3 4 -1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 0
-1 2 -3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4 -1
-2 1 -2 3
```

### 输出

```
3
```

# AI分析结果



### 题目重写
#### Petya 的数组

**题目描述**  
Petya 有一个包含 $n$ 个整数的数组 $a$。他最近学习了部分和，现在可以快速计算数组中任意连续段的元素和。这里的连续段指的是数组中相邻元素的非空序列。

现在他想知道数组中满足和小于 $t$ 的连续段有多少个。请帮助 Petya 计算这个数量。

更形式化地说，需要计算满足 $l \le r$ 且 $a_l + a_{l+1} + \dots + a_r < t$ 的二元组 $(l, r)$ 的数量。

---

### 题解分析与结论

#### 核心思路总结
所有题解均基于前缀和转换问题为二维偏序问题：
1. 将区间和转化为前缀和之差：$sum[r] - sum[l-1] < t$
2. 变形为 $sum[l-1] > sum[r] - t$，转化为求满足该条件的 $(l, r)$ 对数量
3. 使用数据结构（树状数组/线段树）维护前缀和的有序性，支持快速查询与插入

#### 最优技巧提炼
- **动态开点线段树**：无需离散化，通过偏移量处理负数（如加上 $10^{15}$）
- **离散化+树状数组**：将前缀和离散化为排名，降低空间复杂度
- **CDQ分治**：通过分治处理二维偏序，归并过程中统计答案

---

### 高星题解推荐

#### 1. 作者：PanH（★★★★☆）
**关键亮点**  
- 动态开点权值线段树处理大范围数据  
- 通过添加大数偏移（$G=1e15$）解决负数问题  
- 逆向扫描数组，将左端点查询转化为右端点插入

```cpp
// 核心代码：动态开点线段树的插入与查询
void insert(int l,int r,int &k,int x) {
    make(k);
    if(l==r) return tree[k]++;
    if(x<=mid) insert(l,mid,lson[k],x);
    else insert(mid+1,r,rson[k],x);
    tree[k] = tree[lson[k]] + tree[rson[k]];
}
// 逆向扫描统计答案
for(int i=n;i;i--) {
    insert(1,G<<1,rt,a[i]+G);
    ans += query(1,G<<1,rt,1,a[i-1]+t+G-1);
}
```

#### 2. 作者：5k_sync_closer（★★★★☆）
**关键亮点**  
- 极简树状数组实现，仅 30 行代码  
- 利用 lower_bound 隐式处理离散化  
- 合并离散化与树状数组操作，提升代码紧凑性

```cpp
// 核心代码：离散化与树状数组操作融合
#define F(x) v[m++] = x       // 收集所有可能值
#define H(x) lower_bound(v, v+m, x)-v+1  // 获取离散化后排名

int main() {
    // 离散化收集所有sum值及sum-t值
    for(int i=0;i<=n;i++) F(a[i]), F(a[i]-t+1);
    sort(v, v+m); 
    m = unique(v, v+m) - v;  // 去重
    
    // 树状数组维护前缀和的排名
    C(H(0));  // 初始插入sum[0]
    for(int i=1;i<=n;i++) {
        ans += query(H(a[i]-t+1)-1); // 查询比a[i]-t大的数量
        C(H(a[i])); // 插入当前前缀和
    }
}
```

#### 3. 作者：Ofnoname（★★★★☆）
**关键亮点**  
- 内存池预分配优化线段树空间  
- 负数处理通过扩大值域范围至 $[-2e14, 2e14]$  
- 递归式线段树查询与插入，逻辑清晰易懂

```cpp
// 核心代码：递归式线段树操作
i64 sum(Node *p, i64 l, i64 r, const i64 val) {
    if (p == null) return 0;
    if (l > val) return p->num;  // 整个区间都>val
    if (r < val) return 0;       // 整个区间都<val
    i64 mid = l + r >> 1;
    return sum(p->ls,l,mid,val) + sum(p->rs,mid+1,r,val);
}
// 查询时传入扩展后的值域范围
ans += Seg.sum(INILIST, a[i]-T);
```

---

### 调试经验摘录
- **CreeperLordVader**：线段树左右子节点写反导致错误，离散化后未使用long long导致溢出  
- **djh123**：树状数组初始化时漏掉sum[0]导致统计错误  
- **iodwad**：CDQ分治中未处理剩余元素导致答案偏小  

---

### 相似题目推荐
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
   - 二维偏序经典问题，可用树状数组/CDQ分治解决
   
2. [P5463 小鱼比可爱（加强版）](https://www.luogu.com.cn/problem/P5463)  
   - 统计满足条件的二维偏序对，需处理大值域

3. [P5142 区间方差](https://www.luogu.com.cn/problem/P5142)  
   - 前缀和与数据结构结合维护区间统计量

---
处理用时：69.94秒