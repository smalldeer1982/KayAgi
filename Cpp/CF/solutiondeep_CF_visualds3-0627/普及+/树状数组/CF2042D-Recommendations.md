# 题目信息

# Recommendations

## 题目描述

有 $n$ 个区间 $S_i=[l_i,r_i]$，对于每个区间求出 $|\bigcap\limits_{j} S_j|-|S_i|$，其中 $j\neq i$，且 $S_i\subseteq S_j$。即对于每个区间求出其包区间交集的大小，并减去自己的大小。

## 样例 #1

### 输入

```
4
3
3 8
2 5
4 5
2
42 42
1 1000000000
3
42 42
1 1000000000
42 42
6
1 10
3 10
3 7
5 7
4 4
1 2```

### 输出

```
0
0
1
999999999
0
0
0
0
0
2
3
2
4
8```

# AI分析结果



## 算法分类
**排序与数据结构优化**

---

## 题解思路与核心难点

### 核心思路
1. **问题拆解**：对每个区间 $S_i$，求其所有包区间的交集 $\bigcap S_j$ 的左右端点。交集左端点为所有包区间的最大左端点 $L$，右端点为所有包区间的最小右端点 $R$。答案即为 $(R-L+1) - (r_i - l_i +1)$。
2. **数据结构优化**：通过两次排序（按左端点升序、按右端点降序）结合数据结构（multiset/线段树）快速维护极值。
3. **重复区间处理**：当多个区间完全相同时，其交集计算结果为 $0$，需特殊处理。

### 解决难点
- **高效查找极值**：如何快速找到所有包含当前区间的包区间的最大左端点 $L$ 和最小右端点 $R$。
- **离线处理**：通过排序将动态问题转化为静态二维数点问题，利用数据结构批量处理查询。
- **重复区间判定**：在排序后通过相邻元素比较或哈希表记录重复区间，确保正确性。

---

## 题解评分 (≥4星)

### 1. Hide_In_The_Shadow（★★★★☆）
- **亮点**：双排序 + multiset 维护极值，代码简洁高效。通过分组处理相同左/右端点的区间，避免重复计算。
- **优化点**：使用 `multiset` 快速查找极值，时间复杂度稳定 $O(n\log n)$。
- **代码示例**：
  ```cpp
  // 按左端点排序处理右端点极值
  sort(a+1, a+n+1, cmp0);
  multiset<int> s;
  for (int i=1; i<=n; ) {
      s.insert(a[i].r);
      auto it = s.lower_bound(a[i].r);
      if (++it != s.end()) R = *it;
      // 处理相同左端点的区间
  }
  ```

### 2. SilverLi（★★★★☆）
- **亮点**：线段树维护极值，支持离散化处理大范围数据。利用线段树区间查询快速获取 $L$ 和 $R$。
- **优化点**：离散化后压缩区间范围，适合处理大值域问题。
- **代码示例**：
  ```cpp
  // 线段树维护最大值和最小值
  segtree<int, [](int a, int b){ return max(a,b); }, [](){ return -inf; }> pre;
  segtree<int, [](int a, int b){ return min(a,b); }, [](){ return inf; }> suf;
  pre.set(l, l); suf.set(l, r);
  ```

### 3. lyxxys（★★★★☆）
- **亮点**：树状数组维护后缀最大值，结合排序处理极值。通过翻转区间对称处理左右端点。
- **优化点**：树状数组实现简单，适合离线处理二维数点问题。
- **代码示例**：
  ```cpp
  // 树状数组查询后缀最大值
  fenwick Y(tot);
  Y.update(mps[r], l);
  L = Y.query(mps[r]);
  ```

---

## 最优思路与技巧提炼
1. **双排序策略**：先按左端点升序处理右端点极值，再按右端点降序处理左端点极值。
2. **极值维护**：使用 `multiset` 或线段树快速查询当前区间的极值。
3. **重复区间处理**：在排序后检查相邻元素是否相同，若相同则答案直接置 $0$。

---

## 相似题目推荐
1. **CF817F MEX Queries**（区间覆盖与极值查询）
2. **LeetCode 850. Rectangle Area II**（区间交集与扫描线）
3. **洛谷 P1904 天际线**（极值维护与事件处理）

---

## 算法可视化设计
### 核心流程动画
1. **排序过程**：展示区间按左端点升序排列，右端点降序排列的动态过程。
2. **极值查询**：高亮当前处理的区间，显示 `multiset` 中插入和查找极值的操作。
3. **重复区间标记**：用不同颜色标记重复区间，显示其答案被置 $0$。

### 复古像素风格实现
- **颜色方案**：使用 8-bit 调色板（如深蓝表示区间，红色表示当前操作）。
- **Canvas 绘制**：网格化显示区间分布，当前处理区间用闪烁效果突出。
- **音效触发**：插入数据结构时播放“滴”声，查询成功时播放上升音调。

---

## 核心代码实现（Hide_In_The_Shadow）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,l[N],r[N];
struct seg{ int l,r,id; }a[N];
bool cmp0(seg a,seg b){ return a.l<b.l; }
bool cmp1(seg a,seg b){ return a.r<b.r; }

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;++i) cin>>a[i].l>>a[i].r, a[i].id=i;
        // 处理右端点极值
        sort(a+1,a+n+1,cmp0);
        multiset<int> s;
        for(int i=1;i<=n;){
            int pre=i;
            while(i<=n && a[i].l==a[pre].l) s.insert(a[i++].r);
            for(int j=pre;j<i;++j){
                auto it=s.upper_bound(a[j].r);
                r[a[j].id] = (it!=s.end()) ? *it : -1;
            }
        }
        // 处理左端点极值
        sort(a+1,a+n+1,cmp1);
        multiset<int,greater<int>> s2;
        for(int i=n;i>=1;){
            int pre=i;
            while(i>=1 && a[i].r==a[pre].r) s2.insert(a[i--].l);
            for(int j=i+1;j<=pre;++j){
                auto it=s2.upper_bound(a[j].l);
                l[a[j].id] = (it!=s2.end()) ? *it : -1;
            }
        }
        // 计算结果
        for(int i=1;i<=n;++i){
            if(l[i]==-1 || r[i]==-1) cout<<"0\n";
            else cout<<(r[i]-l[i]+1)-(a[i].r-a[i].l+1)<<'\n';
        }
    }
    return 0;
}
```

---
处理用时：86.08秒