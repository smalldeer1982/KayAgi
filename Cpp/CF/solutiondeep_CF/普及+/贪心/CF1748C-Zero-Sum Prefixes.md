# 题目信息

# Zero-Sum Prefixes

## 题目描述

The score of an array $ v_1,v_2,\ldots,v_n $ is defined as the number of indices $ i $ ( $ 1 \le i \le n $ ) such that $ v_1+v_2+\ldots+v_i = 0 $ .

You are given an array $ a_1,a_2,\ldots,a_n $ of length $ n $ . You can perform the following operation multiple times:

- select an index $ i $ ( $ 1 \le i \le n $ ) such that $ a_i=0 $ ;
- then replace $ a_i $ by an arbitrary integer.

What is the maximum possible score of $ a $ that can be obtained by performing a sequence of such operations?

## 说明/提示

In the first test case, it is optimal to change the value of $ a_2 $ to $ -2 $ in one operation.

The resulting array $ a $ will be $ [2,-2,1,-1,0] $ , with a score of $ 3 $ :

- $ a_1+a_2=2-2=0 $ ;
- $ a_1+a_2+a_3+a_4=2-2+1-1=0 $ ;
- $ a_1+a_2+a_3+a_4+a_5=2-2+1-1+0=0 $ .

In the second test case, it is optimal to change the value of $ a_3 $ to $ -2\,000\,000\,000 $ , giving us an array with a score of $ 1 $ .

In the third test case, it is not necessary to perform any operations.

## 样例 #1

### 输入

```
5
5
2 0 1 -1 0
3
1000000000 1000000000 0
4
0 0 0 0
8
3 0 2 -10 10 -30 30 0
9
1 0 0 1 -1 0 1 0 -1```

### 输出

```
3
1
4
4
5```

# AI分析结果



# Zero-Sum Prefixes

## 题目描述

数组 $v_1,v_2,\ldots,v_n$ 的得分数定义为满足 $v_1+v_2+\ldots+v_i = 0$ 的索引 $i$（$1 \le i \le n$）的数量。

给定长度为 $n$ 的数组 $a_1,a_2,\ldots,a_n$。你可以进行多次如下操作：
- 选择一个满足 $a_i=0$ 的索引 $i$
- 将 $a_i$ 替换为任意整数

求通过执行该操作能获得的最大可能得分。

## 样例 #1

### 输入
```
5
5
2 0 1 -1 0
3
1000000000 1000000000 0
4
0 0 0 0
8
3 0 2 -10 10 -30 30 0
9
1 0 0 1 -1 0 1 0 -1
```

### 输出
```
3
1
4
4
5
```

---

### 题解综合分析

#### 核心思路
所有高分题解均基于以下观察：
1. **分段处理**：以 0 的位置将数组划分为多个区间，每个区间的得分相互独立
2. **众数优化**：在每个区间内，通过修改当前段的起始 0 的值，将该区间内出现次数最多的前缀和变为 0
3. **前缀和映射**：使用哈希表统计各区间的前缀和频次，时间复杂度为 O(nlogn)

#### 最优技巧
1. **虚位哨兵**：在数组末尾添加虚 0 处理最后一段（如 Nuclear_Fish_cyq 的代码）
2. **逆向遍历**：部分解法采用逆向统计避免重复计算（如 XL4453 的代码）
3. **双阶段处理**：单独处理第一个 0 之前的原生前缀和为 0 的情况

---

### 精选题解（评分4★+）

#### 题解1. Hovery（9赞）
**亮点**：
- 清晰的区间划分逻辑
- 直观的众数统计实现
```cpp
for (;i <= n;){
    int j = i + 1, Max = 1;
    map<int, int> mp;
    while (a[j] && j <= n) j++;
    for (int k = i ;k < j;k++) {
        mp[b[k]]++;
        Max = max(Max, mp[b[k]]);
    }
    ans += Max;
    i = j;
}
```
**评分**：4.5★  
**关键实现**：通过连续扫描非零元素确定区间边界，使用 map 维护前缀和频次

#### 题解2. Nuclear_Fish_cyq（1赞）
**亮点**：
- 逆向遍历优化空间
- 特判首个 0 前的原生前缀和
```cpp
for(int i = n - 1; i >= 0; i--){
    cnt[s[i]]++;
    maxn = max(maxn, cnt[s[i]]);
    if(a[i] == 0){
        ans += maxn;
        maxn = 0;
        cnt.clear();
    }
}
cout << ans + cnt[0] << endl;
```
**评分**：4★  
**心得**：发现逆向遍历可以简化区间处理逻辑，最后需要加上未处理的 cnt[0]

#### 题解3. XL4453（0赞）
**亮点**：
- 极简实现（仅 30 行）
- 最优空间复杂度（O(1) 额外空间）
```cpp
for(int i=n;i>=1;i--){
    mp[sum[i]]++;
    cnt=max(cnt,mp[sum[i]]);
    if(a[i]==0){
        ans+=cnt;
        cnt=0;
        mp.clear();
    }
}
ans+=mp[0];
```
**评分**：4.2★  
**优化点**：省去显式的区间划分数组，直接通过逆向扫描动态维护

---

### 关键实现代码
**分段众数统计核心逻辑**：
```cpp
// 正向处理版本
vector<int> zeros = {虚位0位置};
for(int i=0; i<zeros.size()-1; i++){
    unordered_map<long, int> freq;
    int max_count = 0;
    for(int j=zeros[i]; j<zeros[i+1]; j++){
        freq[prefix[j]]++;
        max_count = max(max_count, freq[prefix[j]]);
    }
    ans += max_count;
}
```

---

### 同类型题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   **相似点**：前缀和极值处理

2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)  
   **相似点**：区间覆盖统计与贪心决策

3. [CF1005C Summarize to the Power of Two](https://codeforces.com/problemset/problem/1005/C)  
   **相似点**：哈希表维护前驱元素的优化思路

---

### 调试经验总结
1. **数据溢出**：需使用 long long 存储前缀和（如 WaterSun 代码中的错误点）
2. **边界处理**：第一个 0 前可能存在原生前缀和为 0 的情况（Nuclear_Fish_cyq 的 hack 数据）
3. **容器选择**：map 比 unordered_map 更稳定（Dry_ice 的踩坑记录）

---
处理用时：55.12秒