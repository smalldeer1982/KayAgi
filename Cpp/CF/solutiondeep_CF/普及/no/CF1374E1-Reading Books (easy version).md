# 题目信息

# Reading Books (easy version)

## 题目描述

Alice 和 Bob 一共有 $n$ 本书要读。第 $i$ 本书有三个属性：阅读时间 $t_i$，$a_i$（为 $1$ 表示 Alice 喜欢这本书，为 $0$ 表示 Alice 不喜欢），$b_i$（为 $1$ 表示 Bob 喜欢这本书，为 $0$ 表示 Bob 不喜欢）。



他们需要从这些书中选择若干本，满足



- 这些书中至少有 $k$ 本是 Alice 喜欢的，至少有 $k$ 本是 Bob 喜欢的。

- 阅读的总时间最小（总时间为选中的书的 $t_i$ 的总和）

## 样例 #1

### 输入

```
8 4
7 1 1
2 1 1
4 0 1
8 1 1
1 0 1
1 1 1
1 0 1
3 0 0```

### 输出

```
18```

## 样例 #2

### 输入

```
5 2
6 0 0
9 0 0
1 0 1
2 1 1
5 1 0```

### 输出

```
8```

## 样例 #3

### 输入

```
5 3
3 0 0
2 1 0
3 1 0
5 0 1
3 0 1```

### 输出

```
-1```

# AI分析结果

### 题目内容重写（中文）

Alice 和 Bob 一共有 $n$ 本书要读。第 $i$ 本书有三个属性：阅读时间 $t_i$，$a_i$（为 $1$ 表示 Alice 喜欢这本书，为 $0$ 表示 Alice 不喜欢），$b_i$（为 $1$ 表示 Bob 喜欢这本书，为 $0$ 表示 Bob 不喜欢）。

他们需要从这些书中选择若干本，满足：

- 这些书中至少有 $k$ 本是 Alice 喜欢的，至少有 $k$ 本是 Bob 喜欢的。
- 阅读的总时间最小（总时间为选中的书的 $t_i$ 的总和）

### 算法分类
贪心

### 题解分析与结论

本题的核心思路是通过贪心策略选择阅读时间最小的书籍，同时满足 Alice 和 Bob 各自喜欢的书籍数量至少为 $k$。大多数题解都采用了类似的贪心思路，即将书籍分类并排序，然后通过合并或选择最小时间的书籍来达到目标。

### 精选题解

#### 题解1：Dream__Sky (4星)
**关键亮点**：
- 将书籍分为四类：两人都喜欢、Alice 喜欢、Bob 喜欢、两人都不喜欢。
- 通过合并 Alice 和 Bob 各自喜欢的书籍，使其贡献等同于两人都喜欢的书籍。
- 最终排序并选择前 $k$ 本最小时间的书籍。

**核心代码**：
```cpp
sort(b+1,b+1+cnt2),sort(c+1,c+1+cnt3);//排序
for(int i=1;i<=min(cnt2,cnt3);i++)
    a[++cnt1]=b[i]+c[i];//合并，使贡献相同 
if(cnt1<k) return cout<<-1,0;//无解 
sort(a+1,a+1+cnt1);
for(int i=1;i<=k;i++) daan+=a[i];
cout<<daan;
```

#### 题解2：45dino (4星)
**关键亮点**：
- 使用 STL 的 `vector` 和 `sort` 函数，代码简洁易读。
- 将 Alice 和 Bob 各自喜欢的书籍合并后，统一排序并选择前 $k$ 本最小时间的书籍。

**核心代码**：
```cpp
sort(a.begin(),a.end());
sort(b.begin(),b.end());
for(int i=0;i<min(a.size(),b.size());i++)
    c.push_back(a[i]+b[i]);
sort(c.begin(),c.end());
if(c.size()<k) { puts("-1"); return 0; }
for(int i=0;i<k;i++) ans+=c[i];
cout<<ans;
```

#### 题解3：Clouder (4星)
**关键亮点**：
- 使用前缀和优化，减少重复计算。
- 枚举选择两人都喜欢的书籍数量，计算最小总时间。

**核心代码**：
```cpp
for(int i = 1;i<=acnt;++i) SA[i] = SA[i-1] + A[i];
for(int i = 1;i<=bcnt;++i) SB[i] = SB[i-1] + B[i];
for(int i = 1;i<=ccnt;++i) SC[i] = SC[i-1] + C[i];
long long ans = 1ll << 60;
for (int i = std::max(0,k - std::min(acnt, bcnt)); i <= ccnt && i <= k; ++i) 
    ans = std::min(ans, SA[k - i] + SB[k - i] + SC[i]);
if (ans == 1ll << 60) puts("-1");
else printf("%lld",ans);
```

### 最优关键思路
1. **分类与排序**：将书籍按照 Alice 和 Bob 的喜好分类，并按阅读时间排序。
2. **合并贡献**：将 Alice 和 Bob 各自喜欢的书籍合并，使其贡献等同于两人都喜欢的书籍。
3. **贪心选择**：选择前 $k$ 本最小时间的书籍，确保满足条件。

### 拓展思路
类似的问题可以通过贪心策略解决，尤其是在需要满足多个条件且要求最小化或最大化某个值的情况下。例如，选择满足多个约束条件的最小代价或最大收益。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：29.43秒