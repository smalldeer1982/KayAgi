# 题目信息

# [USACO08DEC] Patting Heads S

## 题目描述

It's Bessie's birthday and time for party games! Bessie has instructed the N (1 <= N <= 100,000) cows conveniently numbered 1..N to sit in a circle (so that cow i [except at the ends] sits next to cows i-1 and i+1; cow N sits next to cow 1). Meanwhile, Farmer John fills a barrel with one billion slips of paper, each containing some integer in the range 1..1,000,000.

Each cow i then draws a number A\_i (1 <= A\_i <= 1,000,000) (which is not necessarily unique, of course) from the giant barrel.  Taking turns, each cow i then takes a walk around the circle and pats the heads of all other cows j such that her number A\_i is exactly

divisible by cow j's number A\_j; she then sits again back in her original position.

The cows would like you to help them determine, for each cow, the number of other cows she should pat.



## 说明/提示

The 5 cows are given the numbers 2, 1, 2, 3, and 4, respectively.


The first cow pats the second and third cows; the second cows pats no cows; etc.


## 样例 #1

### 输入

```
5 
2 
1 
2 
3 
4 
```

### 输出

```
2 
0 
2 
1 
3 
```

# AI分析结果

### 综合分析与结论

本题的核心在于高效统计每个数的倍数或约数出现的次数，避免暴力枚举带来的高时间复杂度。大部分题解都采用了“倍数统计”或“约数枚举”的思路，通过预处理和优化，将时间复杂度从O(N^2)降低到O(NlogN)或O(N√N)。以下是各题解的要点总结：

1. **倍数统计法**：通过枚举每个数的倍数，统计其贡献。时间复杂度为O(NlogN)，适用于大数据范围。
2. **约数枚举法**：通过枚举每个数的约数，统计其出现次数。时间复杂度为O(N√N)，适用于小数据范围。
3. **桶计数优化**：利用桶记录每个数的出现次数，避免重复计算，进一步提升效率。

### 精选题解

#### 题解1：作者：zhukewen123 (赞：208)
- **星级**：★★★★★
- **关键亮点**：采用倍数统计法，利用桶记录每个数的出现次数，时间复杂度为O(NlogN)，代码简洁且高效。
- **个人心得**：通过倍数统计避免了暴力枚举，优化了时间复杂度，代码实现清晰易懂。

```cpp
void get_factor(){
    for (int i = 1;  i <= 10000000; i++){
    	if(!b[i]) continue;
    	for (int j = 1; j <= 10000000 / i; j++){
    		 if(b[i*j]) cnt[i*j]+=b[i];
    		 if(i*j==i) cnt[i]--;
        }   	
    } 
}
```

#### 题解2：作者：AMSDE (赞：41)
- **星级**：★★★★
- **关键亮点**：通过枚举倍数构造答案，时间复杂度为O(NlogN)，代码结构清晰，优化思路明确。
- **个人心得**：通过提前构造答案，避免了重复计算，代码实现简洁高效。

```cpp
for (int i=1;i<=Max;i++){
    if (num[i]==0) continue;
    for (int j=i;j<=Max;j+=i) ans[j]+=num[i];
}
```

#### 题解3：作者：Garrison (赞：29)
- **星级**：★★★★
- **关键亮点**：通过桶计数优化，避免重复计算，时间复杂度为O(NlogN)，代码实现简洁。
- **个人心得**：通过桶计数优化，减少了重复计算，代码实现简洁高效。

```cpp
for(int i=1;i<=m;++i){
    if(b[i]!=0)
        for(int j=1;j*i<=m;++j)
            ans[j*i]+=b[i];
}
```

### 最优关键思路与技巧

1. **倍数统计法**：通过枚举每个数的倍数，统计其贡献，时间复杂度为O(NlogN)，适用于大数据范围。
2. **桶计数优化**：利用桶记录每个数的出现次数，避免重复计算，进一步提升效率。
3. **约数枚举法**：通过枚举每个数的约数，统计其出现次数，时间复杂度为O(N√N)，适用于小数据范围。

### 可拓展之处

1. **类似题目**：可以扩展到统计每个数的因子个数、最大公约数等问题。
2. **算法套路**：倍数统计法和约数枚举法可以应用于其他需要高效统计倍数或约数的题目中。

### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)

### 个人心得总结

- **调试经历**：在实现倍数统计法时，需要注意避免重复计算，特别是当i和j相等时，需要特殊处理。
- **踩坑教训**：在约数枚举法中，完全平方数需要特殊处理，避免重复统计。
- **顿悟感想**：通过倍数统计法，可以大幅降低时间复杂度，提升代码效率。

---
处理用时：22.37秒