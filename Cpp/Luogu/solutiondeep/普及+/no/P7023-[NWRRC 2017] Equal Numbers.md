# 题目信息

# [NWRRC 2017] Equal Numbers

## 题目描述



You are given a list of $n$ integers $a_{1},$ . . . , $a_{n}.$ You can perform the following operation: choose some $a_{i}$ and multiply it by any positive integer.

Your task is to compute the minimum number of different integers that could be on the list after $k$ operations for all $0 \le k \le n$ .



## 说明/提示

Time limit: 3 s, Memory limit: 512 MB. 



## 样例 #1

### 输入

```
6
3 4 1 2 1 2
```

### 输出

```
4 4 3 3 2 2 1
```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
本题的核心在于通过贪心策略选择最优的操作方式，以减少列表中不同整数的数量。各题解均围绕如何选择操作策略（将数变成其倍数或所有数的最小公倍数）展开，并通过排序和前缀和优化来计算最小不同数的数量。虽然思路相似，但实现细节和优化程度有所不同。

### 所选题解
1. **作者：_GW_ (4星)**
   - **关键亮点**：清晰地将操作策略分为两种方案，并通过排序和前缀和优化计算最小不同数的数量。代码结构清晰，逻辑严谨。
   - **个人心得**：作者提到“要么全用方案1，要么全用方案2”，这一观察简化了问题的复杂性。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=m;i++) {
       for(int j=a[i]*2;j<=1e6;j+=a[i]) {
         if(vis[j]) {
           b[++len]=vis[a[i]];
           break;
         }
       }
     }
     sort(c+1,c+1+m);
     sort(b+1,b+1+len);
     for(int i=1;i<=n;i++) {
       sum[i]=sum[i-1]+c[i];cnt[i]=cnt[i-1]+b[i];
     }
     ```

2. **作者：Starlight237 (4星)**
   - **关键亮点**：通过Lemma0-Lemma3的证明，系统地分析了操作策略的最优性，并提出了两种方案的独立计算方式。代码实现较为复杂，但思路清晰。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=mx;i++) {
       if(fl[i] && buc[i]) A[++t1] = num {i, buc[i]};
       if(buc[i]) Ar[++t2] = num {i, buc[i]};
     }
     sort(A + 1, A + t1 + 1), sort(Ar + 1, Ar + t2 + 1);
     f[1] = n;
     for(int i=2;i<=t2;i++) f[i] = f[i - 1] - Ar[i - 1].cnt;
     ```

3. **作者：陌路的花 (3星)**
   - **关键亮点**：将数类分为两个集合，并分别计算操作后的最小不同数数量。思路较为直接，但代码实现略显冗长。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++){
       if(t.count(a[i])){
         if(t[a[i]]) b[++en] = a[i];
         continue;
       }
       for(int j=2;j*a[i]<=maxn;j++){
         if(s.count(a[i]*j)){
           b[++en] = a[i];
           t[a[i]] = 1;
           break;
         }
       }
       if(t.count(a[i]) == 0) t[a[i]] = 0; 
     }
     ```

### 最优关键思路或技巧
- **贪心策略**：将操作策略分为两种方案（变成倍数或最小公倍数），并通过排序和前缀和优化计算最小不同数的数量。
- **前缀和优化**：通过前缀和快速计算不同操作策略下的最小不同数数量。

### 可拓展之处
- **类似问题**：可以考虑在操作次数有限的情况下，如何通过贪心策略优化其他类型的数组操作问题。
- **算法套路**：贪心策略结合排序和前缀和优化，适用于多种需要最小化或最大化某种指标的问题。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：23.12秒