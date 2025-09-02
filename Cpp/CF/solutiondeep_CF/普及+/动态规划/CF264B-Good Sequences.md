# 题目信息

# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10
```

### 输出

```
4
```

# AI分析结果

### 题目内容重写

**题目描述**

松鼠Liss对序列感兴趣。她还有一些对整数的偏好。她认为$n$个整数$a_{1},a_{2},...,a_{n}$是好的。

现在她对好的序列感兴趣。一个序列$x_{1},x_{2},...,x_{k}$被称为好的，如果它满足以下三个条件：

- 序列是严格递增的，即$x_{i}<x_{i+1}$对于每个$i$ $(1<=i<=k-1)$。
- 没有两个相邻的元素是互质的，即$gcd(x_{i},x_{i+1})>1$对于每个$i$ $(1<=i<=k-1)$（其中$gcd(p,q)$表示整数$p$和$q$的最大公约数）。
- 序列中的所有元素都是好的整数。

找出最长的好序列的长度。

### 题解分析与结论

本题的核心在于如何高效地找到满足条件的序列。大多数题解采用了动态规划（DP）的思路，通过维护一个状态数组来记录以某个数结尾的最长序列长度，并通过优化转移过程来降低时间复杂度。

### 所选高分题解

#### 题解1：傅思维666 (4星)
**关键亮点：**
- 通过引入辅助数组$f[i]$来记录含有因子$i$的$a[x]$中的最大$dp[x]$，从而优化了转移过程。
- 使用质因数分解来减少枚举次数，显著降低了时间复杂度。

**核心代码：**
```cpp
for(int i=1;i<=n;i++) {
    int tmp=0;
    for(int j=0;j<fac[a[i]].size();j++)
        tmp=max(tmp,f[fac[a[i]][j]]);
    dp[i]=max(dp[i],tmp+1);
    for(int j=0;j<fac[a[i]].size();j++)
        f[fac[a[i]][j]]=max(f[fac[a[i]][j]],dp[i]);
}
```

#### 题解2：是个汉子 (4星)
**关键亮点：**
- 直接更新质因子的$f$值，避免了不必要的更新，进一步优化了性能。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
inline void solve(int x){
    int m=sqrt(x),sum=0;
    for(int i=2;i<=m;i++)
        if(x%i==0) sum=max(max(sum,f[i]),f[x/i]);
    sum=max(sum,f[x]);
    for(int i=2;i<=m;i++)
        if(x%i==0){
            f[i]=sum+1;
            while(x%i==0) x/=i;
        }
    f[x]=sum+1;
    ans=max(ans,sum+1);
}
```

#### 题解3：DYT_ (4星)
**关键亮点：**
- 通过建图的方式处理转移，虽然空间复杂度较高，但思路新颖。
- 使用最长路算法来求解，提供了另一种解决问题的视角。

**核心代码：**
```cpp
int dfs(int x) {
    if(~dis[x]) return dis[x];
    dis[x]=1;
    for(int i=head[x];i;i=edge[i].nxt)
        getmax(dis[x],dfs(edge[i].v)+1);
    return dis[x];
}
```

### 最优关键思路与技巧

1. **质因数分解**：通过将每个数分解为质因数，可以大大减少需要枚举的因子数量，从而优化转移过程。
2. **辅助数组$f[i]$**：通过维护一个记录含有因子$i$的最大$dp[x]$的数组，可以快速找到转移的最大值。
3. **建图与最长路**：虽然空间复杂度较高，但通过建图并使用最长路算法，提供了另一种解决问题的思路。

### 拓展与推荐题目

1. **洛谷P1020 导弹拦截**：考察最长上升子序列的变形。
2. **洛谷P1091 合唱队形**：考察双向最长上升子序列。
3. **洛谷P1439 【模板】最长公共子序列**：考察最长公共子序列的优化解法。

### 个人心得总结

- **调试经历**：在处理质因数分解时，需要注意边界条件，如1的处理和重复因子的排除。
- **踩坑教训**：在优化转移时，确保所有可能的转移路径都被考虑到，避免遗漏。
- **顿悟感想**：通过引入辅助数组和质因数分解，可以显著提高算法的效率，这在实际编程中是非常有用的技巧。

---
处理用时：41.22秒