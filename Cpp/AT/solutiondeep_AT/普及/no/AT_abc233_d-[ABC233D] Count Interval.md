# 题目信息

# [ABC233D] Count Interval

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc233/tasks/abc233_d

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ と、整数 $ K $ が与えられます。

$ A $ の連続部分列のうち、要素の和が $ K $ になるものはいくつありますか？  
 すなわち、以下の条件を全て満たす整数の組 $ (l,r) $ はいくつありますか？

- $ 1\leq\ l\leq\ r\leq\ N $
- $ \displaystyle\sum_{i=l}^{r}A_i\ =\ K $

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ |A_i|\ \leq\ 10^9 $
- $ |K|\ \leq\ 10^{15} $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ (l,r)=(1,2),(3,3),(2,6) $ の $ 3 $ 組が条件を満たします。

### Sample Explanation 2

条件を満たす $ (l,r) $ の組が $ 1 $ つも存在しないこともあります。

## 样例 #1

### 输入

```
6 5

8 -3 5 7 0 -4```

### 输出

```
3```

## 样例 #2

### 输入

```
2 -1000000000000000

1000000000 -1000000000```

### 输出

```
0```

# AI分析结果



# [ABC233D] Count Interval

## 题目描述

**题目大意**  
给定长度为 $N$ 的数列 $A=(A_1,A_2,\ldots,A_N)$ 和整数 $K$，求满足区间和为 $K$ 的连续子数组个数。即寻找满足以下条件的整数对 $(l,r)$ 的数量：
- $1 \leq l \leq r \leq N$
- $\sum_{i=l}^{r} A_i = K$

**输入格式**  
第一行输入 $N$ 和 $K$，第二行输入数组 $A$。

**输出格式**  
输出满足条件的区间个数。

**样例解释**  
样例1中满足条件的区间有 $(1,2),(3,3),(2,6)$ 共3组。

---

**算法分类**  
前缀和、哈希表

---

## 题解分析与结论

### 核心思路对比
所有题解均采用前缀和+哈希表的优化思路，将暴力 $O(n^2)$ 的解法优化至 $O(n)$：
1. **前缀和转换**：将区间和 $sum(l,r) = K$ 转换为 $sum[r] - sum[l-1] = K$。
2. **哈希表加速查询**：枚举右端点 $r$ 时，查询哈希表中满足 $sum[l-1] = sum[r]-K$ 的历史值出现次数。
3. **边遍历边更新**：在计算过程中动态维护哈希表，记录每个前缀和的出现次数。

### 关键实现技巧
1. **初始条件处理**：必须初始化哈希表包含 $sum[0] = 0$ 的情况（对应区间从第一个元素开始的情况）。
2. **更新顺序**：先查询当前 $sum[r]-K$ 的计数，再将当前前缀和加入哈希表，避免包含自身。
3. **数据类型**：使用 `long long` 防止溢出。

---

## 精选题解

### 题解1：Jerry_heng（⭐⭐⭐⭐⭐）
**亮点**  
- 代码简洁，直接维护累加和变量，无需显式前缀和数组。
- 显式初始化 `mp[0] = 1`，逻辑清晰易懂。
- 输入与计算同步进行，节省内存空间。

**核心代码**  
```cpp
map<int,int> mp;
int n,k,sum,ans;
signed main(){
    cin>>n>>k;
    mp[0]=1; // 关键初始化
    for(int i=1;i<=n;i++){
        int x; cin>>x;
        sum += x;
        ans += mp[sum - k];
        mp[sum]++;
    }
    cout<<ans;
}
```

---

### 题解2：fish_love_cat（⭐⭐⭐⭐）
**亮点**  
- 注释明确解释统计逻辑，易于理解。
- 采用显式前缀和数组，结构清晰。
- 强调 `long long` 的重要性。

**核心代码**  
```cpp
map<long long,long long> mapp;
long long a[200005],ans;
int main(){
    cin>>n>>k;
    for(long long i=1;i<=n;i++){
        cin>>a[i];
        a[i] += a[i-1]; // 实时计算前缀和
    }
    for(long long i=1;i<=n;i++){
        mapp[a[i-1]]++; // 记录历史前缀和
        ans += mapp[a[i]-k];
    }
    cout<<ans;
}
```

---

### 题解3：loser_seele（⭐⭐⭐⭐）
**亮点**  
- 使用 `unordered_map` 提升查询效率。
- 循环中动态维护前缀和数组，逻辑紧凑。
- 强调时间复杂度优化思路。

**核心代码**  
```cpp
unordered_map<long long,int> q;
long long sum[200020];
int main(){
    for(int i=0;i<n;i++){
        cin>>a[i];
        sum[i+1] = sum[i] + a[i]; // 显式前缀和数组
    }
    for(int i=1;i<=n;i++){
        q[sum[i-1]]++; // 动态记录历史值
        ans += q[sum[i] - k];
    }
}
```

---

## 拓展与练习
**相似题目推荐**  
1. [P1114 非常男女](https://www.luogu.com.cn/problem/P1114) - 前缀和统计性别平衡区间  
2. [P3131 Subsequences Summing to Sevens](https://www.luogu.com.cn/problem/P3131) - 求模7余0的子区间  
3. [P1865 窗口](https://www.luogu.com.cn/problem/P1865) - 滑动窗口与区间和统计  

**心得总结**  
- 前缀和与哈希表是处理区间和问题的经典组合。
- 初始条件极易遗漏（如 `sum[0]` 的处理），需特别关注边界情况。
- 数据范围较大时优先选择 `unordered_map`，但需注意哈希冲突风险。

---
处理用时：122.83秒