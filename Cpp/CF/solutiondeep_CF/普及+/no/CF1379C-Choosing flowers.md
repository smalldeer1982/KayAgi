# 题目信息

# Choosing flowers

## 题目描述

有 $m$ 种物品，每种物品有无限个，你可以购买 $n$ 个物品。

对于第 $i$ 种物品：

第一次买时的贡献是 $a_i$ ,接下来每购买一个的贡献都是 $b_i$。即当你买了 $x_i$ 个第 $i$ 种物品时，贡献是 $a_i+b_i \times (x_i-1)$

现在要你求出最大贡献。

## 样例 #1

### 输入

```
2
4 3
5 0
1 4
2 2

5 3
5 2
4 2
3 1```

### 输出

```
14
16```

# AI分析结果

### 题目翻译
已有，无需翻译

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，即最多只有一种物品会被选超过一次。因为若有多种物品被选多次，用 $b$ 值大的替换 $b$ 值小的一定更优。在此基础上，各题解采用了不同的实现方式。部分题解通过枚举被选多次的物品，结合排序和二分查找来优化时间复杂度；部分题解采用递归函数处理不同选择情况。

### 所选题解
- __phiu（4星）
    - 关键亮点：思路清晰，先证明至多让一种物品选多次的结论，然后枚举该物品，通过排序和二分查找优化，用前缀和维护 $a_i$ 的和，时间复杂度为 $O(n^2)$ 优化到 $O(n\log n)$。
- feecle6418（4星）
    - 关键亮点：将每种物品的价格排序后扫描，用递归函数处理不同选择情况，总决策数为 $O(n)$，复杂度 $O(n\log n)$，可采用基数排序优化到 $O(n)$。
- strcmp（4星）
    - 关键亮点：同样基于至多一种物品选多次的结论，枚举物品，将物品按 $a_i$ 降序排序，利用三分法求凸函数极值，时间复杂度 $\Theta(m \log n)$。

### 重点代码
#### __phiu 的核心代码
```cpp
sort(a+1,a+n+1) ;
for(int i=1;i<=n;i++) sum[i] = sum[i-1] + a[i].a;
long long ans = 0 ;
for(int i=1;i<=n;i++) {
    int l = 1, r = n;
    while(l<=r) {
        int mid = l+r >>1 ;
        if(a[mid].a>=a[i].b)
            l=mid+1;
        else
            r=mid-1;
    }
    l--;
    if(l>=m)
        ans=max(ans,sum[m]);
    else if(l >= i ) ans = max(ans,sum[l]+1ll*(m-l)*a[i].b) ;
    else ans = max(ans,sum[l]+a[i].a+1ll*(m-l-1)*a[i].b);
}
```
核心实现思想：先对物品按 $a_i$ 排序，计算前缀和。然后枚举被选多次的物品，二分查找第一个比当前物品 $b_i$ 小的 $a_j$，根据不同情况计算贡献并更新最大贡献。

#### feecle6418 的核心代码
```cpp
ll calc(int i,int n){
    if(i>2*m||n<=0)return 0;
    ll ans=0;
    if(a[i].tp==1){
        ans+=a[i].x,n--;
        if(p[a[i].id])return ans+a[p[a[i].id]].x*n;
        else {
            f[a[i].id]=1;
            return ans+calc(i+1,n);
        }
    }
    if(a[i].tp==2){
        if(f[a[i].id]){
            ans+=n*a[i].x,n=0;
            return ans;
        }
        else {
            ll tmp=ans+g[a[i].id][0]+(n-1)*g[a[i].id][1];
            p[a[i].id]=i;
            return max(tmp,ans+calc(i+1,n));
        }
    }
}
```
核心实现思想：递归函数 `calc` 处理不同选择情况，若当前是第一次买的价格，直接买；若第一次已买过，剩余的都买这种；若第一次没买，尝试两种选择并取最大值。

#### strcmp 的核心代码
```cpp
ll solve(int now, ll p) {
    ll w = n - p; ll pre = 0, b = a[now].y;
    if (w > m) w = m;
    if (w >= now) { pre = sum[min(w + 1, m)] - a[now].x; }
    else pre = sum[w];
    return b * (p - 1) + pre + a[now].x;
}
for (int i = 1; i <= m; i++) {
    ll l = 1, r = n;
    while (l + 1 < r) {
        ll mid = l + r >> 1;
        ll a1 = solve(i, mid - 1), a2 = solve(i, mid + 1);
        if (a1 >= a2) ans = max(ans, a1), r = mid;
        else ans = max(ans, a2), l = mid;
    }
    ans = max(ans, solve(i, l));
    ans = max(ans, solve(i, r));
}
```
核心实现思想：`solve` 函数计算 $(a_x,\,b_x)$ 选取 $p$ 次之后的总贡献，通过三分法求凸函数的极值，更新最大贡献。

### 关键思路或技巧
- **贪心策略**：最多只有一种物品会被选超过一次，这是解题的关键思想，基于此可以简化问题。
- **排序与二分查找**：对物品按 $a_i$ 排序，然后二分查找满足条件的 $a_j$，可以优化时间复杂度。
- **前缀和**：用前缀和维护 $a_i$ 的和，方便快速计算部分和。

### 拓展思路
同类型题可能会有更多的限制条件或变化，例如物品有数量限制、增加新的属性等。类似算法套路可以应用于其他贪心问题，先分析问题的最优策略，然后通过排序、二分等方法优化实现。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：经典的贪心问题，通过优先队列实现。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：简单的贪心问题，按照一定规则排序求解。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心算法的典型应用，根据单位价值排序。

### 个人心得
- strcmp：“NOIP 模拟赛的 T3，赛时切了，看见没有相同的做法，故记之。” 总结：记录自己独特的解题思路，有助于后续复习和分享。

---
处理用时：47.78秒