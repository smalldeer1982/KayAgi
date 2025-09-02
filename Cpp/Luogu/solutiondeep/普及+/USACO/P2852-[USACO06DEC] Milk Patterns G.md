# 题目信息

# [USACO06DEC] Milk Patterns G

## 题目描述

Farmer John has noticed that the quality of milk given by his cows varies from day to day. On further investigation, he discovered that although he can't predict the quality of milk from one day to the next, there are some regular patterns in the daily milk quality.

To perform a rigorous study, he has invented a complex classification scheme by which each milk sample is recorded as an integer between 0 and 1,000,000 inclusive, and has recorded data from a single cow over N (1 ≤ N ≤ 20,000) days. He wishes to find the longest pattern of samples which repeats identically at least K (2 ≤ K ≤ N) times. This may include overlapping patterns -- 1 2 3 2 3 2 3 1 repeats 2 3 2 3 twice, for example.

Help Farmer John by finding the longest repeating subsequence in the sequence of samples. It is guaranteed that at least one subsequence is repeated at least K times.


## 样例 #1

### 输入

```
8 2
1
2
3
2
3
2
3
1```

### 输出

```
4```

# AI分析结果

### 综合分析与结论
本题主要是求至少重复 $k$ 次的最长子串长度，各题解提供了多种不同的思路和算法，主要围绕后缀数组、后缀自动机（SAM）、哈希、随机化、并查集等方法展开。

- **后缀数组相关**：很多题解利用后缀数组求出 $sa$ 和 $height$ 数组，再结合单调队列、二分查找等方法求解。核心思路是利用 $height$ 数组的性质，即两个后缀的最长公共前缀（LCP）是它们之间 $height$ 的最小值，通过寻找连续 $k - 1$ 个 $height$ 的最小值的最大值来得到答案。
- **后缀自动机（SAM）**：利用 SAM 可以方便地求出子串的出现次数，遍历满足出现次数大于等于 $k$ 的节点，取其 $len$ 的最大值即为答案。
- **哈希**：通过二分答案，用哈希统计每个长度的子串出现的次数，判断是否有子串出现次数大于等于 $k$。
- **随机化**：随机选若干个长度为 $len$ 的子串，用 KMP 计算其在原串中出现的次数，使用部分代替整体，但存在一定出错概率。
- **并查集**：先离散化数据，跑一遍 SA 求出 $h$ 数组，将 $h$ 从大到小排序，从大到小枚举重复串的长度，合并 $h_i$ 所连接的两个节点，判断合并后的并查集大小是否满足要求。

### 所选题解
- **作者：Treeloveswater（4星）**
  - **关键亮点**：思路清晰，详细阐述了离散化 + 后缀数组 + 二分查找的解法，代码注释丰富，可读性高。
  - **个人心得**：提到评测数据与题目描述不符，最大数较小，认为数据是离散过的，强烈要求更新评测数据。
- **作者：hongzy（4星）**
  - **关键亮点**：明确指出用单调队列处理，复杂度为 $O(n)$，对样例进行了详细分析，代码结构清晰。
  - **个人心得**：无。
- **作者：cyh_toby（4星）**
  - **关键亮点**：对后缀数组处理 LCP 相关问题的思路解释详细，注意到了数据的细节处理，如对串中元素加一避免对 0 元素的单独处理，单调队列边界细节也有说明。
  - **个人心得**：无。

### 重点代码及核心实现思想
#### Treeloveswater 的题解
```cpp
// 检查长度为 length 的子串是否出现至少 k 次
bool check(int length)
{
    int l=0,r=l+k_k-2;
    while(r<=n-1)
    {
        int ok=query(l,r); // RMQ 查询区间最小值
        if(ok>=length)return true;
        l++;r++;
    }
    return false;
}

int main()
{
    // 输入处理
    scanf("%d%d",&n,&k_k);
    nep(i,0,n)scanf("%d",&lq[i]),num[i]=i;
    len=n;
    // 离散化
    sort(num,num+n,cmp);
    s[num[0]]=1;
    cnt=1;
    for(int i=0;i<n-1;i++)
        if(lq[num[i]]!=lq[num[i+1]])s[num[i+1]]=++cnt;
        else s[num[i+1]]=cnt;
    // 后缀数组相关操作
    make_sa();
    make_height();
    init();
    // 二分查找
    int l=1,r=n,answer=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))answer=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d\n",answer);
}
```
**核心实现思想**：先对数据进行离散化，然后构建后缀数组和 $height$ 数组，利用 RMQ 预处理 $height$ 数组。通过二分答案，对于每个中间值 $mid$，检查是否存在长度为 $mid$ 的子串出现至少 $k$ 次，若存在则更新答案并继续二分。

#### hongzy 的题解
```cpp
int main() {
    // 输入处理
    scanf("%d%d", &n, &k);
    k --;
    for(int i=1; i<=n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    // 离散化
    sort(b+1, b+n+1);
    for(int i=1; i<=n; i++) {
        map[ b[i] ] = map[ b[i-1] ] + (b[i] != b[i-1]);
        lim = max(lim, map[ b[i] ]);
    }
    for(int i=1; i<=n; i++)
        a[i - 1] = map[ a[i] ];
    a[n] = 0;
    // 后缀排序和计算 Height 数组
    Suffix_Array(lim + 1);
    Get_Height();
    // 单调队列处理
    int ans = 0;
    deque<int> Q;
    for(int i=1; i<=n; i++) {
        while(!Q.empty() && Q.front() <= i - k) Q.pop_front();
        while(!Q.empty() && height[Q.back()-1] >= height[i-1]) Q.pop_back();
        Q.push_back(i);
        if(i >= k) ans = max(ans, height[Q.front() - 1]);
    }
    printf("%d\n", ans);
    return 0;
}
```
**核心实现思想**：先对数据离散化，然后构建后缀数组和 $height$ 数组。使用单调队列维护连续 $k - 1$ 个 $height$ 的最小值，遍历过程中更新答案。

#### cyh_toby 的题解
```cpp
int main()
{
    // 输入处理
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
        s[i]++;// 避免对 0 的特殊处理
    }
    // 后缀数组相关操作
    for (int i = 1; i <= n; i++) cnt[s[i]]++;
    w = 1e6;
    for (int i = 1; i <= w; i++) cnt[i] += cnt[i-1];
    for (int i = n; i >= 1; i--) sa[cnt[s[i]]--] = i;
    w = 0;
    for (int i = 1; i <= n; i++)
        rk[sa[i]] = s[sa[i]] == s[sa[i-1]] ? w : ++w;
    for (int j = 1; j < n; j <<= 1) {
        // 省略部分代码
    }
    for (int i = 1, j = 0; i <= n; i++) {
        if (j) j--;
        while (s[i+j] == s[sa[rk[i]-1]+j]) j++;
        ht[rk[i]] = j;
    }
    // 单调队列处理
    for (int i = 1; i <= n; i++) {
        while (hd != tl && q[hd] <= i-k+1) hd++;
        while (hd != tl && ht[q[tl-1]] >= ht[i]) tl--;
        q[tl++] = i;
        if (i > 1) ans = max(ans, ht[q[hd]]);
    }
    printf("%d", ans);
    return 0;
}
```
**核心实现思想**：先对数据进行处理，避免对 0 元素的单独处理。构建后缀数组和 $height$ 数组，使用单调队列维护连续 $k - 1$ 个 $height$ 的最小值，更新答案。

### 最优关键思路或技巧
- **后缀数组与 $height$ 数组的运用**：利用后缀数组对后缀进行排序，$height$ 数组记录相邻后缀的 LCP 长度，通过分析 $height$ 数组可以高效地解决子串重复问题。
- **单调队列优化**：在处理 $height$ 数组时，使用单调队列可以在 $O(n)$ 时间内维护连续 $k - 1$ 个 $height$ 的最小值，从而降低时间复杂度。
- **二分查找**：通过二分答案，将问题转化为判定性问题，减少不必要的计算，提高效率。

### 可拓展之处
- **同类型题**：求最长重复子串、最长公共子串等问题都可以使用后缀数组、后缀自动机、哈希等方法解决。
- **类似算法套路**：在处理字符串相关问题时，可以考虑使用后缀数组、后缀自动机、哈希等数据结构和算法，结合二分查找、单调队列等优化技巧。

### 推荐题目
- [P3809 【模板】后缀排序](https://www.luogu.com.cn/problem/P3809)
- [P2408 不同子串个数](https://www.luogu.com.cn/problem/P2408)
- [P4070 [SDOI2016]生成魔咒](https://www.luogu.com.cn/problem/P4070)

### 个人心得摘录与总结
- **Treeloveswater**：发现评测数据与题目描述不符，最大数较小，认为数据是离散过的，提醒我们在做题时要注意数据范围，对数据进行合理处理。
- **唐一文**：模拟赛时因数组越界丢分，强调了在编写代码时要注意边界条件，避免因小错误导致失分。
- **睿3030**：使用随机化算法时，发现对于某些数据点出错概率高，需要进行特判，说明随机化算法虽然有一定的优势，但也存在局限性，在实际应用中需要谨慎考虑。

---
处理用时：72.21秒