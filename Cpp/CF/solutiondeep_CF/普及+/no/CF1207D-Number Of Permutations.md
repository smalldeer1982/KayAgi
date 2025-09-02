# 题目信息

# Number Of Permutations

## 题目描述

You are given a sequence of $ n $ pairs of integers: $ (a_1, b_1), (a_2, b_2), \dots , (a_n, b_n) $ . This sequence is called bad if it is sorted in non-descending order by first elements or if it is sorted in non-descending order by second elements. Otherwise the sequence is good. There are examples of good and bad sequences:

- $ s = [(1, 2), (3, 2), (3, 1)] $ is bad because the sequence of first elements is sorted: $ [1, 3, 3] $ ;
- $ s = [(1, 2), (3, 2), (1, 2)] $ is bad because the sequence of second elements is sorted: $ [2, 2, 2] $ ;
- $ s = [(1, 1), (2, 2), (3, 3)] $ is bad because both sequences (the sequence of first elements and the sequence of second elements) are sorted;
- $ s = [(1, 3), (3, 3), (2, 2)] $ is good because neither the sequence of first elements $ ([1, 3, 2]) $ nor the sequence of second elements $ ([3, 3, 2]) $ is sorted.

Calculate the number of permutations of size $ n $ such that after applying this permutation to the sequence $ s $ it turns into a good sequence.

A permutation $ p $ of size $ n $ is a sequence $ p_1, p_2, \dots , p_n $ consisting of $ n $ distinct integers from $ 1 $ to $ n $ ( $ 1 \le p_i \le n $ ). If you apply permutation $ p_1, p_2, \dots , p_n $ to the sequence $ s_1, s_2, \dots , s_n $ you get the sequence $ s_{p_1}, s_{p_2}, \dots , s_{p_n} $ . For example, if $ s = [(1, 2), (1, 3), (2, 3)] $ and $ p = [2, 3, 1] $ then $ s $ turns into $ [(1, 3), (2, 3), (1, 2)] $ .

## 说明/提示

In first test case there are six permutations of size $ 3 $ :

1. if $ p = [1, 2, 3] $ , then $ s = [(1, 1), (2, 2), (3, 1)] $ — bad sequence (sorted by first elements);
2. if $ p = [1, 3, 2] $ , then $ s = [(1, 1), (3, 1), (2, 2)] $ — bad sequence (sorted by second elements);
3. if $ p = [2, 1, 3] $ , then $ s = [(2, 2), (1, 1), (3, 1)] $ — good sequence;
4. if $ p = [2, 3, 1] $ , then $ s = [(2, 2), (3, 1), (1, 1)] $ — good sequence;
5. if $ p = [3, 1, 2] $ , then $ s = [(3, 1), (1, 1), (2, 2)] $ — bad sequence (sorted by second elements);
6. if $ p = [3, 2, 1] $ , then $ s = [(3, 1), (2, 2), (1, 1)] $ — good sequence.

## 样例 #1

### 输入

```
3
1 1
2 2
3 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
2 3
2 2
2 1
2 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
1 1
1 1
2 3
```

### 输出

```
4
```

# AI分析结果

### 题目内容（中文重写）
# 排列的数量

## 题目描述
给定一个包含 $n$ 对整数的序列：$(a_1, b_1), (a_2, b_2), \dots , (a_n, b_n)$ 。如果该序列按第一个元素非降序排序，或者按第二个元素非降序排序，则称这个序列是“坏的”，否则该序列是“好的”。以下是好序列和坏序列的示例：
- $s = [(1, 2), (3, 2), (3, 1)]$ 是坏序列，因为第一个元素组成的序列是有序的：$[1, 3, 3]$ ；
- $s = [(1, 2), (3, 2), (1, 2)]$ 是坏序列，因为第二个元素组成的序列是有序的：$[2, 2, 2]$ ；
- $s = [(1, 1), (2, 2), (3, 3)]$ 是坏序列，因为两个序列（第一个元素序列和第二个元素序列）都是有序的；
- $s = [(1, 3), (3, 3), (2, 2)]$ 是好序列，因为第一个元素组成的序列 $([1, 3, 2])$ 和第二个元素组成的序列 $([3, 3, 2])$ 都不是有序的。

计算大小为 $n$ 的排列的数量，使得将这个排列应用到序列 $s$ 后，序列 $s$ 变成一个好序列。

大小为 $n$ 的排列 $p$ 是一个由 $n$ 个不同整数（范围从 $1$ 到 $n$，即 $1 \le p_i \le n$ ）组成的序列 $p_1, p_2, \dots , p_n$ 。如果将排列 $p_1, p_2, \dots , p_n$ 应用到序列 $s_1, s_2, \dots , s_n$ ，就会得到序列 $s_{p_1}, s_{p_2}, \dots , s_{p_n}$ 。例如，如果 $s = [(1, 2), (1, 3), (2, 3)]$ 且 $p = [2, 3, 1]$ ，那么 $s$ 就会变成 $[(1, 3), (2, 3), (1, 2)]$ 。

## 说明/提示
在第一个测试用例中，有六种大小为 $3$ 的排列：
1. 如果 $p = [1, 2, 3]$ ，那么 $s = [(1, 1), (2, 2), (3, 1)]$ ，这是一个坏序列（按第一个元素排序）；
2. 如果 $p = [1, 3, 2]$ ，那么 $s = [(1, 1), (3, 1), (2, 2)]$ ，这是一个坏序列（按第二个元素排序）；
3. 如果 $p = [2, 1, 3]$ ，那么 $s = [(2, 2), (1, 1), (3, 1)]$ ，这是一个好序列；
4. 如果 $p = [2, 3, 1]$ ，那么 $s = [(2, 2), (3, 1), (1, 1)]$ ，这是一个好序列；
5. 如果 $p = [3, 1, 2]$ ，那么 $s = [(3, 1), (1, 1), (2, 2)]$ ，这是一个坏序列（按第二个元素排序）；
6. 如果 $p = [3, 2, 1]$ ，那么 $s = [(3, 1), (2, 2), (1, 1)]$ ，这是一个好序列。

## 样例 #1
### 输入
```
3
1 1
2 2
3 1
```
### 输出
```
3
```

## 样例 #2
### 输入
```
4
2 3
2 2
2 1
2 4
```
### 输出
```
0
```

## 样例 #3
### 输入
```
3
1 1
1 1
2 3
```
### 输出
```
4
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是利用容斥原理来解决问题，即好序列的数量等于总排列数减去第一维有序的方案数和第二维有序的方案数，再加上两维都有序的方案数。
- **思路**：先将问题转化为容斥问题，通过计算不同维度有序的排列方案数，利用容斥原理得到最终结果。
- **算法要点**：
    - 计算总排列数：$n!$。
    - 计算某一维有序的方案数：统计该维中相同元素的出现次数，将每个相同元素出现次数的阶乘相乘。
    - 计算两维都有序的方案数：先对二元组排序，检查第二维是否有序，若有序则按相同元素出现次数的阶乘相乘计算。
- **解决难点**：
    - 处理相同元素的排列组合，通过统计出现次数并计算阶乘来得到方案数。
    - 处理容斥关系，避免重复计算。
    - 处理取模运算，防止结果溢出。

### 所选题解
- **米奇（4星）**：
    - **关键亮点**：思路清晰，代码实现规范，详细地处理了各种情况，包括不同维度的排序和方案数的计算，并且对取模运算也有正确处理。
- **Lolierl（4星）**：
    - **关键亮点**：对容斥原理的解释清晰，代码简洁，直接计算各部分方案数，最后根据容斥原理得到结果。
- **fsy_juruo（4星）**：
    - **关键亮点**：对计数过程的解释详细，使用了 `map` 来统计元素出现次数，代码结构清晰。

### 重点代码
#### 米奇的代码核心部分
```cpp
// 计算阶乘
jc[0]=1;
for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
// 计算第一维有序的方案数
sort(a+1,a+n+1,cmp);
ans1=1;
for(int l=1,r=1;l<=n;l=r+1) {
    r=l;
    while(r<n&&a[r+1].x==a[r].x) r++;
    int x=r-l+1;
    ans1=ans1*jc[x]%mod;
}
// 计算第二维有序的方案数
sort(a+1,a+n+1,cmp2);
ans2=1;
for(int l=1,r=1;l<=n;l=r+1) {
    r=l;
    while(r<n&&a[r+1].y==a[r].y) r++;
    int x=r-l+1;
    ans2=ans2*jc[x]%mod;
}
// 计算两维都有序的方案数
sort(a+1,a+n+1,cmp);
bool flag=0;
for(int i=2;i<=n;i++)
    if(a[i].y<a[i-1].y) {
        ans3=0;
        flag=1;
    }
if(!flag) {
    ans3=1;
    for(int l=1,r=1;l<=n;l=r+1) {
        r=l;
        while(r<n&&a[r+1].x==a[r].x&&a[r+1].y==a[r].y) r++;
        int x=r-l+1;
        ans3=ans3*jc[x]%mod;
    }
}
// 根据容斥原理计算结果
int x=((ans1+ans2-ans3)%mod+mod)%mod;
x=(jc[n]-x+mod)%mod;
```
**核心实现思想**：先预处理阶乘，然后分别对第一维和第二维排序，统计相同元素的个数并计算方案数。对于两维都有序的情况，先检查第二维是否有序，若有序则按相同元素的个数计算方案数。最后根据容斥原理计算最终结果。

#### Lolierl的代码核心部分
```cpp
// 初始化阶乘
t[0] = 1; t[1] = 1; 
for(int i = 2; i <= n; i++)
    t[i] = (1ll * t[i - 1] * i) % M; 
// 计算第一维有序的方案数
for(int i = 1; i <= n; i++)
    cnt[s[i].first]++; 
long long c1 = 1; 
for(int i = 1; i <= n; i++)
    if(cnt[i]) c1 = c1 * t[cnt[i]] % M; 
// 计算第二维有序的方案数
memset(cnt, 0, sizeof(cnt)); 
for(int i = 1; i <= n; i++)
    cnt[s[i].second]++; 
long long c2 = 1; 
for(int i = 1; i <= n; i++)
    if(cnt[i]) c2 = c2 * t[cnt[i]] % M; 
// 计算两维都有序的方案数
sort(s + 1, s + n + 1); 
long long c3 = 1; 
int p = 1; 
for(int i = 2; i <= n; i++) {
    if(s[i].second < s[i - 1].second) {c3 = 0; break; }
    if(s[i].first == s[i - 1].first && s[i].second == s[i - 1].second)
        p++; 
    else {
        c3 = c3 * t[p] % M; 
        p = 1; 
    }
}
c3 = c3 * t[p] % M; 
// 根据容斥原理计算结果
long long ans = t[n] - c1 - c2 + c3; 
while(ans < 0) ans += M; 
```
**核心实现思想**：先初始化阶乘，然后分别统计第一维和第二维中相同元素的个数，计算对应维度有序的方案数。对于两维都有序的情况，先排序，检查第二维是否有序，若有序则按相同元素的个数计算方案数。最后根据容斥原理计算最终结果。

#### fsy_juruo的代码核心部分
```cpp
// 预处理阶乘
fac[0] = 1;
_rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
// 统计元素出现次数
_rep(i, 1, n) {
    read(perm[i].first); read(perm[i].second);
    aa[perm[i].first]++; bb[perm[i].second]++;
    ds[perm[i]]++;
}
sort(perm + 1, perm + n + 1);
LL ans = fac[n], tmpa = 1, tmpb = 1, tmpab = 1, valid = 1;
// 检查两维是否都有序
_rep(i, 2, n) {
    if(perm[i].second < perm[i - 1].second) valid = 0;
}
// 计算第一维有序的方案数
map<int, int> :: iterator it;
for(it = aa.begin(); it != aa.end(); it++) {
    pair<int, int> p = *it;
    tmpa = 1ll * tmpa * fac[p.second] % mod;
}
// 计算第二维有序的方案数
for(it = bb.begin(); it != bb.end(); it++) {
    pair<int, int> p = *it;
    tmpb = 1ll * tmpb * fac[p.second] % mod;
}
// 计算两维都有序的方案数
map<pair<int, int>, int> :: iterator ab;
for(ab = ds.begin(); ab != ds.end(); ab++) {
    int cnt = (*ab).second;
    tmpab = 1ll * tmpab * fac[cnt] % mod;
}
// 根据容斥原理计算结果
writesp((ans - tmpa + mod - tmpb + mod + tmpab * valid + mod) % mod);
```
**核心实现思想**：先预处理阶乘，然后使用 `map` 统计第一维、第二维和二元组的出现次数。检查两维是否都有序，若有序则计算对应方案数。最后根据容斥原理计算最终结果。

### 最优关键思路或技巧
- **容斥原理**：将复杂的计数问题转化为多个简单的计数问题，通过容斥关系得到最终结果。
- **统计相同元素个数**：对于有序排列的方案数计算，通过统计相同元素的出现次数，利用阶乘计算排列组合数。
- **取模运算**：在计算过程中进行取模运算，防止结果溢出。

### 拓展思路
同类型题或类似算法套路：
- 涉及多个条件限制的计数问题，可考虑使用容斥原理将问题简化。
- 对于排列组合问题，可通过统计相同元素的个数来计算方案数。

### 洛谷题目推荐
- P1896 [SCOI2005] 互不侵犯：涉及状态压缩和组合数学的问题，需要考虑不同状态下的排列组合情况。
- P2157 [SDOI2009] 学校食堂：需要运用动态规划和组合数学的知识，处理不同状态下的方案数。
- P3181 [HAOI2016] 找相同字符：涉及字符串的组合数学问题，需要计算不同字符组合的方案数。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：82.03秒