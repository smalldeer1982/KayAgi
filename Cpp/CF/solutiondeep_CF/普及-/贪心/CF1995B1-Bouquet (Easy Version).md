# 题目信息

# Bouquet (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version, the flowers are specified by enumeration.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ flowers in the store, each of which is characterized by the number of petals, and a flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use in her bouquet should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 说明/提示

In the first test case, you can assemble a bouquet with $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the third test case, you can assemble a bouquet with only one flower of any type, so the answer is $ 610 $ . In the fourth test case, you can assemble a bouquet with $ (4, 4, 5) $ , which gives you $ 13 $ petals, and it is the maximum amount of petals that the girl can buy.

## 样例 #1

### 输入

```
5
5 10
1 1 2 2 3
8 20
4 2 7 5 6 1 1 1
8 100000
239 30 610 122 24 40 8 2
11 13
2 4 11 1 1 2 3 5 4 3 2
8 1033
206 206 206 207 207 207 207 1000```

### 输出

```
7
13
610
13
1033```

# AI分析结果



# Bouquet (Easy Version)

## 题目描述

这是该问题的简单版本。唯一区别在于此版本中花朵通过枚举给出。

女孩准备生日并想购买最美的花束。商店共有 $n$ 朵花，每朵花用花瓣数描述，拥有 $k$ 片花瓣的花价值 $k$ 枚硬币。女孩决定花束中任意两朵花的花瓣数差不超过一。同时她希望花束总花瓣数尽可能多。她只有 $m$ 枚硬币，求能获得的最大总花瓣数。

## 样例 #1

### 输入
```
5
5 10
1 1 2 2 3
8 20
4 2 7 5 6 1 1 1
8 100000
239 30 610 122 24 40 8 2
11 13
2 4 11 1 1 2 3 5 4 3 2
8 1033
206 206 206 207 207 207 207 1000
```

### 输出
```
7
13
610
13
1033
```

---

## 题解综合分析

### 最优思路总结
1. **排序预处理**：将花朵按花瓣数排序，使数组具备单调性
2. **双指针滑动窗口**：维护左右指针确定区间，满足：
   - 区间内极差 ≤1 
   - 总花费 ≤m
3. **动态调整窗口**：右指针扩展时计算累积值，当不满足条件时收缩左指针
4. **时间复杂度**：O(n log n)（排序）+ O(n)（双指针扫描）

---

## 高分题解推荐

### 1. [NEKO_Daze] 双指针滑动窗口（⭐⭐⭐⭐⭐）
**关键亮点**：
- 代码简洁清晰（仅15行核心逻辑）
- 完美处理边界条件
- 同步维护花费总和与极差条件

```cpp
sort(a+1,a+n+1);
ll ans=0,i=0,j=1,x=0;
while(i<n){
    i++;
    x+=a[i];
    while(x>m||a[i]-a[j]>1) 
        x-=a[j],j++;
    ans=max(ans,x);
}
```

### 2. [vorDeal] 极差与总和同步判断（⭐⭐⭐⭐）
**实现特点**：
- 反向条件判断逻辑
- 使用前缀和优化计算
- 显式处理空队列情况

```cpp
while(r <= n && (a[r-1] > a[l] + 1 || sum > m))
    sum -= a[l], l++;
res = max(res, sum);
```

### 3. [nightwatch.ryan] 动态窗口扩展（⭐⭐⭐⭐）
**优化技巧**：
- 从右指针出发逆向处理
- 利用排序后单调性简化极差判断
- 使用单层循环减少变量维护

```cpp
for(int l=1,r=1;r<=n;r++){
    cur += a[r];
    while(a[r]-a[l]>1||cur>m) 
        cur -= a[l++];
    maxn = max(maxn, cur);
}
```

---

## 关键技巧与拓展

### 调试经验
- **多测清空**：vorDeal 强调每次测试要重置队列和计数器
- **边界处理**：zjj2024 指出枚举组合时必须取 min 防止越界
- **贪心验证**：__little__Cabbage__ 发现需要双向枚举两种花的组合

### 相似题目推荐
1. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638) - 滑动窗口求最小覆盖区间
2. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102) - 双指针找特定差值组合
3. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147) - 前缀和与滑动窗口结合应用

---

## 核心代码实现

NEKO_Daze 的完整滑动窗口实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[200001];

int main(){
    int t; cin>>t;
    while(t--){
        ll n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        ll ans=0,i=0,j=1,x=0;
        while(i<n){
            i++;
            x+=a[i];
            while(x>m || a[i]-a[j]>1) x-=a[j],j++;
            ans=max(ans,x);
        }
        cout<<ans<<endl;
    }
}
```

---
处理用时：64.35秒