# 题目信息

# [USACO10OCT] Soda Machine G

## 题目描述

To meet the ever-growing demands of his N (1 &amp;lt;= N &amp;lt;= 50,000) cows, Farmer John has bought them a new soda machine. He wants to figure out the perfect place to install the machine.

The field in which the cows graze can be represented as a one-dimensional number line. Cow i grazes in the range A\_i..B\_i (1 &amp;lt;= A\_i &amp;lt;= B\_i; A\_i &amp;lt;= B\_i &amp;lt;= 1,000,000,000) (a range that includes its endpoints), and FJ can place the soda machine at any integer point in the range 1..1,000,000,000.  Since cows are extremely lazy and try to move as little as possible, each cow would like to have the soda machine installed within her grazing range.

Sadly, it is not always possible to satisfy every cow's desires. Thus FJ would like to know the largest number of cows that can be satisfied.

To demonstrate the issue, consider four cows with grazing ranges 3..5, 4..8, 1..2, and 5..10; below is a schematic of their grazing ranges:

```cpp

         1   2   3   4   5   6   7   8   9  10  11  12  13
         |---|---|---|---|---|---|---|---|---|---|---|---|-...
                 aaaaaaaaa
                     bbbbbbbbbbbbbbbbb
         ccccc           ddddddddddddddddddddd
```
As can be seen, the first, second and fourth cows share the point 5, but the third cow's grazing range is disjoint.  Thus, a maximum of 3 cows can have the soda machine within their grazing range.


有N个人要去膜拜JZ，他们不知道JZ会出现在哪里，因此每个人有一个活动范围，只要JZ出现在这个范围内就能被膜拜，

伟大的JZ当然希望膜拜他的人越多越好，但是JZ不能分身，因此只能选择一个位置出现，他最多可以被多少人膜拜呢，

这个简单的问题JZ当然交给你了


## 说明/提示

If the soda machine is placed at location 5, cows 1, 2, and 4 can be satisfied. It is impossible to satisfy all four cows.


## 样例 #1

### 输入

```
4 
3 5 
4 8 
1 2 
5 10 
```

### 输出

```
3 
```

# AI分析结果



### 算法分类
差分、离散化

---

### 题解对比与结论
题目核心是求数轴上被最多区间覆盖的点。各题解普遍采用 **差分+离散化** 或 **事件排序扫描线** 的思路解决。关键点在于处理大范围坐标时，通过离散化压缩数据规模，再用差分或扫描线方式统计覆盖次数。

---

### 精选题解

#### 1. Starria的脑残粉（5星）
**亮点**：  
- 事件排序扫描线思路，代码极简  
- 将区间端点拆分为事件（+1和-1），排序后遍历维护当前覆盖数  
- 处理顺序巧妙：相同坐标时，起点事件（+1）优先于终点事件（-1）

**核心代码**：
```cpp
struct lsg{int x,y;}a[2000000];
bool pd(lsg x,lsg y){return x.x<y.x||x.x==y.x&&x.y>y.y;}
sort(a+1,a+1+n*2,pd);
for (int i=1;i<=n*2;i++)sum+=a[i].y,ans=max(ans,sum);
```

#### 2. fls233666（5星）
**亮点**：  
- 差分数组结合离散化，逻辑清晰  
- 离散化后对区间左端点+1，右端点+1处-1，避免处理顺序问题  
- 前缀和求最大值，代码简洁高效

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    ll l=lower_bound(op+1,op+1+cnt,num[i].x)-op;
    ll r=lower_bound(op+1,op+1+cnt,num[i].y)-op;
    h[l]++; h[r+1]--;
}
for(int i=1;i<=2*n;i++) ans=max(ans,h[i]);
```

#### 3. jgvccc（4星）
**亮点**：  
- 树状数组维护区间覆盖，思路新颖  
- 离散化后区间更新，单点查询最大值  
- 代码结构清晰，但复杂度略高于差分法

**核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    int l=lower_bound(b+1,b+cnt+1,l[i])-b;
    int r=lower_bound(b+1,b+cnt+1,r[i])-b;
    add(l,1); add(r+1,-1);
}
for(int i=1;i<=cnt;i++) ans=max(ans,sum(i));
```

---

### 关键技巧总结
1. **离散化压缩坐标**：将所有端点排序去重，映射到连续整数。
2. **差分数组优化**：区间修改转换为端点操作，前缀和统计覆盖数。
3. **事件排序扫描线**：将区间端点视为事件（+1/-1），按坐标排序后遍历求最大覆盖。
4. **处理顺序**：同一坐标下，起点事件（+1）优先处理，确保正确统计覆盖数。

---

### 同类题目推荐
1. [P1884 [USACO12FEB]Overplanting S](https://www.luogu.com.cn/problem/P1884)  
   **相似点**：二维区间覆盖，差分+离散化扩展应用。
   
2. [P3669 [USACO17OPEN]Paired Up S](https://www.luogu.com.cn/problem/P3669)  
   **相似点**：事件排序扫描线，维护覆盖状态。

3. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)  
   **相似点**：区间合并与覆盖统计，离散化处理。

---
处理用时：249.94秒