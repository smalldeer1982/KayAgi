# 题目信息

# [USACO23FEB] Equal Sum Subarrays G

## 题目描述

注意：本题的时间限制为 3 秒，为默认时间的 1.5 倍。

FJ 给了 Bessie 一个长度为 $N$ 的数组 $a$（$2 \leq N \leq 500, -10^{15} \leq a_i \leq 10^{15}$），其中所有 $\dfrac{N(N+1)}{2}$ 个连续子数组的和都是不同的。对于每个下标 $i \in [1,N]$，帮助 Bessie 计算最小的改变量，使得数组中存在两个不同的连续子数组的和相等。

## 样例 #1

### 输入

```
2
2 -3```

### 输出

```
2
3```

## 样例 #2

### 输入

```
3
3 -10 4```

### 输出

```
1
6
1```

# AI分析结果

### 综合分析与结论
这些题解围绕如何计算数组中每个下标对应的最小改变量，使得数组存在两个不同连续子数组的和相等展开。大部分题解的核心思路是找出一个包含该下标和一个不包含该下标的区间，计算它们的最小差值。时间复杂度主要有 $O(n^5)$、$O(n^3\log n)$、$O(n^3)$ 和 $O(n^2\log n)$ 几种，其中 $O(n^3)$ 和 $O(n^2\log n)$ 的做法较为常见。

### 所选题解
- **作者：MessageBoxA（5星）**
  - **关键亮点**：思路清晰，详细阐述了题目性质，通过归纳区间相交和包含的情况简化问题，采用 $O(n^2\log n)$ 的算法优化时间复杂度，代码注释详细。
  - **个人心得**：提到该做法细节很多，交了十几发才过，提醒读者注意区间操作时的范围和开闭。
- **作者：DengDuck（4星）**
  - **关键亮点**：思路直接，先提取所有区间并排序，根据相邻区间更新答案，时间复杂度为 $O(n^3)$，代码简洁易懂。
- **作者：yzh_Error404（4星）**
  - **关键亮点**：采用 $O(n^2\log n)$ 的算法，通过线段树支持区间修改和单点查询，对不同区间位置关系分情况讨论，代码实现完整。

### 重点代码
#### MessageBoxA 的核心代码
```cpp
for(int l=2;l<=n;l++){
    minx=LLINF;
    for(int r=n;r>=l;r--){
        tmp=pre[r]-pre[l-1];
        minx=min(minx,abs(tmp));
        res=s.lower_bound({tmp,-1,-1});//找后继
        if(res!=s.end()) minx=min(minx,abs(res->val-tmp));
        if(res!=s.begin()){
            res--;//找前驱
            minx=min(minx,abs(res->val-tmp));
        }
        ans[r]=min(ans[r],minx);

        tmp=-tmp;
        res=s.lower_bound({tmp,-1,-1});//找后继
        if(res!=s.end())
            if(!is_range_merge_cover_all(l,r,res->l,res->r))
                minx=min(minx,abs(res->val-tmp));
        if(res!=s.begin()){
            res--;//找前驱
            if(!is_range_merge_cover_all(l,r,res->l,res->r))
                minx=min(minx,abs(res->val-tmp));
        }
        ans[r]=min(ans[r],minx);
    }
    for(int i=1;i<=l;i++)
        s.insert({pre[l]-pre[i-1],i,l});
}
```
**核心实现思想**：枚举左端点 $l$，将 $l$ 之前的区间放入 `set` 中，倒序枚举右端点 $r$，计算区间 $[l,r]$ 的和，在 `set` 中查找与之最接近的区间和，更新答案，同时考虑区间和互为相反数的情况。

#### DengDuck 的核心代码
```cpp
for(int i=2;i<=cnt;i++)
{
    LL l1=t[i].l,l2=t[i-1].l;
    LL r1=t[i].r,r2=t[i-1].r;
    LL p=dkabs(sum[r2]-sum[l2-1]-sum[r1]+sum[l1-1]);
    memset(b,0,sizeof(b));
    for(int j=l1;j<=r1;j++)b[j]^=1;
    for(int j=l2;j<=r2;j++)b[j]^=1;
    for(int j=1;j<=n;j++)if(b[j])ans[j]=min(ans[j],p);
}
```
**核心实现思想**：将所有区间按和排序，遍历相邻区间，计算它们的差值，找出仅在其中一个区间出现的下标，更新这些下标的答案。

#### yzh_Error404 的核心代码
```cpp
for(register int i=1;i<cnt;i++)
{
    node l=e[i],r=e[i+1];
    int now=r.val-l.val;
    if(l.l>r.l)swap(l,r);
    if(l.r<r.l)//相离
    {
        change(1,1,n,l.l,l.r,now);
        change(1,1,n,r.l,r.r,now);
    }
    else if(l.r>r.r)//包含
    {
        change(1,1,n,l.l,r.l-1,now);
        change(1,1,n,r.r+1,l.r,now);
    }
    else//相交
    {
        change(1,1,n,l.l,r.l-1,now);
        change(1,1,n,l.r+1,r.r,now);
    }
}
```
**核心实现思想**：将所有区间按和排序，遍历相邻区间，根据区间的位置关系（相离、包含、相交），使用线段树对仅在其中一个区间出现的下标进行区间修改，更新答案。

### 最优关键思路或技巧
- **区间性质归纳**：将有交的区间情况归纳为无交的情况，简化问题。
- **排序优化**：将所有区间按和排序，相邻区间的差值可能是最小的，减少不必要的比较。
- **数据结构优化**：使用 `set` 进行二分查找，使用线段树支持区间修改和单点查询，降低时间复杂度。

### 可拓展之处
同类型题可能会有不同的数组性质或限制条件，例如数组元素范围变化、区间和的特殊要求等。类似算法套路包括枚举区间、排序、二分查找、数据结构优化等，可根据具体题目灵活运用。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察区间和的计算和动态规划。
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：涉及区间和的计算和数学推导。
- [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)：需要维护区间和的最大值，可使用单调队列优化。

### 个人心得总结
- MessageBoxA 提到 $O(n^2\log n)$ 的做法细节很多，交了十几发才过，提醒读者注意区间操作时的范围和开闭。
- Disjoint_cat 发现直接双指针做法 TLE 后，通过离散化将复杂度从 $O(n^3\log(n^2))$ 优化到 $O(n^3)$，强调了优化排序复杂度的重要性。

---
处理用时：47.49秒