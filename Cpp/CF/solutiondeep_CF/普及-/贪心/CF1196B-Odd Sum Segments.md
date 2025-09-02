# 题目信息

# Odd Sum Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . You want to split it into exactly $ k $ non-empty non-intersecting subsegments such that each subsegment has odd sum (i. e. for each subsegment, the sum of all elements that belong to this subsegment is odd). It is impossible to rearrange (shuffle) the elements of a given array. Each of the $ n $ elements of the array $ a $ must belong to exactly one of the $ k $ subsegments.

Let's see some examples of dividing the array of length $ 5 $ into $ 3 $ subsegments (not necessarily with odd sums): $ [1, 2, 3, 4, 5] $ is the initial array, then all possible ways to divide it into $ 3 $ non-empty non-intersecting subsegments are described below:

- $ [1], [2], [3, 4, 5] $ ;
- $ [1], [2, 3], [4, 5] $ ;
- $ [1], [2, 3, 4], [5] $ ;
- $ [1, 2], [3], [4, 5] $ ;
- $ [1, 2], [3, 4], [5] $ ;
- $ [1, 2, 3], [4], [5] $ .

Of course, it can be impossible to divide the initial array into exactly $ k $ subsegments in such a way that each of them will have odd sum of elements. In this case print "NO". Otherwise, print "YES" and any possible division of the array. See the output format for the detailed explanation.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
```

### 输出

```
YES
1 3 5
NO
NO
```

# AI分析结果



【题目内容中文重写】

# 奇数分段

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$，要求将其分割为恰好 $k$ 个互不相交的连续子段，每个子段的和必须是奇数。数组元素顺序不可改变，每个元素必须属于且仅属于一个子段。

若无法满足条件则输出"NO"，否则输出"YES"并给出任意一种分割方案。需要处理 $q$ 组独立查询。

## 样例 #1

### 输入

```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
```

### 输出

```
YES
1 3 5
NO
NO
```

---

【题解综合分析与结论】

关键思路：**奇数个数决定分段可行性**。当且仅当满足以下两个条件时可分割：
1. 奇数总数 ≥ k
2. 奇数总数与 k 的奇偶性相同（即奇数总数 - k 为偶数）

分割策略：选取前 k-1 个奇数作为分割点，最后一个子段以数组末尾结束。

---

【精选题解】

## 题解作者：__shadow__（★★★★★）

**关键亮点**  
- 数学建模：通过奇偶性定律建立简洁的条件判断式  
- 时间复杂度 O(n)：仅需单次扫描统计奇数位置  
- 空间优化：仅存储必要分割点位置  

**核心代码**  
```cpp
if (sum < k || (sum - k) % 2 != 0) {
    printf("NO\n");
} else {
    printf("YES\n");
    for (int i = 1; i <= k - 1; i++) 
        printf("%d ", a[i]);
    printf("%d\n", n);
}
```

**实现思路**  
1. 统计所有奇数的位置存入数组  
2. 验证奇数个数是否满足条件  
3. 输出前 k-1 个奇数的位置及数组末尾  

---

## 题解作者：xh001（★★★★★）

**关键亮点**  
- 位运算优化：使用 `x&1` 快速判断奇偶  
- 代码简洁性：完整处理逻辑仅需 20 行  

**核心代码**  
```cpp
if((sum-k)%2==1 || cnt<k) {
    cout<<"NO\n";
} else {
    cout<<"YES\n";
    for(ll i=1;i<k;i++) 
        cout<<a[i]<<' '; 
    cout<<n<<endl;
}
```

**实现思路**  
- 读取时直接筛选奇数位置  
- 条件判断与输出逻辑一体化  

---

## 题解作者：HoshizoraZ（★★★★☆）

**关键亮点**  
- 贪心策略：优先构造最短有效子段  
- 前缀和验证：确保最后子段合法性  

**核心代码**  
```cpp
for(ll i=1; i<=n; i++){
    if(cnt + 1 == k) break;
    if((sum[i] - sum[last]) & 1){
        ans[++cnt] = i;
        last = i;
    } 
}
if((sum[n] - sum[last]) & 1) // 验证最后子段
```

**实现思路**  
- 动态计算前缀和  
- 贪心寻找合法分割点  
- 显式验证最后子段奇偶性  

---

【最优技巧总结】

**核心思维**  
- **奇偶性建模**：将复杂的分割问题转化为奇数个数的奇偶性判断  
- **分割点构造**：前 k-1 个奇数确定最小分割点，末尾自动保证合法性  

**拓展应用**  
- 类似问题可考虑将条件转化为数学约束（如质数个数、模数特征等）  
- 分段问题可优先考虑前缀和、贪心构造、数学约束三种方法  

---

【推荐练习题】  
1. CF1003D Coins and Queries（奇偶性应用）  
2. CF1352G Special Permutation（奇偶位置构造）  
3. P2671 [NOIP2015 提高组] 求和（奇偶分组统计）

---
处理用时：121.23秒