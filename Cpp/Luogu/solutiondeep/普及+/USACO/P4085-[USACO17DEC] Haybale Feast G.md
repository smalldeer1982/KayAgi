# 题目信息

# [USACO17DEC] Haybale Feast G

## 题目描述

农夫约翰正在为他的奶牛准备一顿美味的晚餐！在他的谷仓里，他有 $N$ 个干草捆 $(1 \le N \le 10^5)$ 。第 $i$ 个干草捆有一定的风味 $F_i(1 \le F_i \le 10^9)$ 和一定的辣度 $S_i(1 \le S_i \le 10^9)$ 。

这顿饭将由一道菜组成，是一个连续的区间，包含一个或多个连续的干草捆(农夫约翰不能改变干草捆的顺序)。这顿饭的总体的风味是这段区间里风味的总和。这顿饭的总体辣度是区间中所有草包的最大辣度。

农夫约翰想确定他的这道菜所能达到的最小辣度，但是这道菜的总风味必须至少为 $M(1 \le M \le 10^{18})$ 。

## 样例 #1

### 输入

```
5 10
4 10
6 15
3 5
4 9
3 6```

### 输出

```
9```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何在满足风味总和至少为 $M$ 的条件下，求出连续区间辣度最大值的最小值。不同题解采用了多种算法和数据结构，如二分答案、前缀和、RMQ（ST 表、线段树、树状数组等）、尺取法、单调队列等。
- **二分答案类**：通过二分辣度的最大值，然后 $O(n)$ 检查是否存在满足条件的连续区间。
- **前缀和 + RMQ 类**：利用前缀和快速计算区间风味总和，再结合 RMQ 数据结构求区间辣度最大值。
- **尺取法类**：利用区间左右端点的单调性，结合单调队列或其他数据结构求解。

### 所选题解
- **wheneveright（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接使用二分答案的方法，时间复杂度为 $O(n \log \max \{S\})$。
    - **个人心得**：无
- **白鲟（4星）**
    - **关键亮点**：详细分析了两种解法，解法 2 利用尺取法和单调队列将时间复杂度优化到 $O(n)$，效率较高。
    - **个人心得**：无
- **Ciyang（4星）**
    - **关键亮点**：提供了多种数据结构（线段树、ST 表、分块）的实现，便于对比学习，同时利用前缀和和二分查找优化时间复杂度。
    - **个人心得**：无

### 重点代码
#### wheneveright 的二分答案解法
```cpp
bool check (int maxs) {
    sum = 0;
    for (int i = 1; i <= N; i++) {
        if (S[i] > maxs) sum = 0;
        else sum += F[i];
        if (sum >= M) return true;
    }
    return false;
}

int main () {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
        R = max (R, S[i]);
    }
    L = 1;
    while (L <= R) check (mid = ((L + R) >> 1)) ? R = mid - 1, res = mid : L = mid + 1;
    printf ("%lld\n", res);
    return 0;
}
```
**核心思想**：二分枚举辣度的最大值，对于每个枚举值，检查是否存在连续区间的风味总和大于等于 $M$。

#### 白鲟的尺取法 + 单调队列解法
```cpp
for(long long i=1,j=0;i<=n;++i)
{
    sum-=f[i-1];
    while(head<=tail&&que[head]<i)
        ++head;
    while(sum<m&&j<n)
    {
        sum+=f[++j];
        while(head<=tail&&s[que[tail]]<=s[j])
            --tail;
        que[++tail]=j;
    }
    if(sum<m)
        break;
    ans=min(ans,s[que[head]]);
}
```
**核心思想**：使用尺取法维护左右端点，单调队列维护区间内的最大辣度。

#### Ciyang 的前缀和 + 线段树解法
```cpp
namespace PrefixSum {
    ll sumf[100001];
    void init() {
        for(int i= 1; i <= n; i++) sumf[i]= sumf[i - 1] + f[i];
        return;
    }
}

namespace SegmentTree {
    int maxs[100001 << 2];
    void build(int nown, int l, int r) {
        if(l == r) {
            maxs[nown]= s[l];
            return;
        }
        int mid= (l + r) >> 1;
        build(nown << 1, l, mid);
        build(nown << 1 | 1, mid + 1, r);
        maxs[nown]= maxi(maxs[nown << 1], maxs[nown << 1 | 1]);
        return;
    }
    int query(int nown, int l, int r, int ml, int mr) {
        if(ml <= l && r <= mr) return maxs[nown];
        int ans= 0, mid= (l + r) >> 1;
        if(mid >= ml) ans= maxi(ans, query(nown << 1, l, mid, ml, mr));
        if(mid < mr) ans= maxi(ans, query(nown << 1 | 1, mid + 1, r, ml, mr));
        return ans;
    }
    inline void init() {
        build(1, 1, n);
        return;
    }
    inline int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
}

int main() {
    scanf("%d%lld", &n, &m);
    for(int i= 1; i <= n; i++) scanf("%d%d", f + i, s + i);
    PrefixSum::init(), SegmentTree::init();
    for(int i= 1; i <= n; i++) {
        ll r= lower_bound(PrefixSum::sumf + i, PrefixSum::sumf + n + 1, m + PrefixSum::sumf[i - 1]) - PrefixSum::sumf;
        if(r != n + 1) ans= mini(ans, SegmentTree::query(i, r));
    }
    printf("%d\n", ans);
    return 0;
}
```
**核心思想**：利用前缀和快速计算区间风味总和，线段树维护区间辣度最大值，二分查找满足条件的右端点。

### 最优关键思路或技巧
- **二分答案**：对于具有单调性的问题，可通过二分答案将问题转化为判定性问题，降低时间复杂度。
- **前缀和**：对于静态区间求和问题，使用前缀和可将查询时间复杂度优化到 $O(1)$。
- **尺取法**：当区间左右端点具有单调性时，使用尺取法可将时间复杂度优化到 $O(n)$。
- **RMQ 数据结构**：如 ST 表、线段树等，可快速查询区间最值。

### 可拓展之处
同类型题或类似算法套路：
- 区间和与区间最值相关问题，可结合前缀和与 RMQ 数据结构求解。
- 具有单调性的问题，可尝试使用二分答案。
- 区间左右端点具有单调性的问题，可使用尺取法。

### 推荐题目
- [P1816 忠诚](https://www.luogu.com.cn/problem/P1816)：RMQ 问题，可使用 ST 表求解。
- [P2429 制杖题](https://www.luogu.com.cn/problem/P2429)：涉及区间和与区间最值，可结合前缀和与 RMQ 数据结构。
- [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)：尺取法的经典应用。

### 个人心得摘录与总结
部分题解提到要注意开 `long long`，避免数据溢出。在选择数据结构时，要根据题目特点选择合适的，如静态区间查询可优先考虑 ST 表，动态区间查询可考虑线段树等。同时，对于具有单调性的问题，可尝试使用二分答案或尺取法优化时间复杂度。

---
处理用时：47.81秒