# 题目信息

# Sort the Array

## 题目描述

Being a programmer, you like arrays a lot. For your birthday, your friends have given you an array $ a $ consisting of $ n $ distinct integers.

Unfortunately, the size of $ a $ is too small. You want a bigger array! Your friends agree to give you a bigger array, but only if you are able to answer the following question correctly: is it possible to sort the array $ a $ (in increasing order) by reversing exactly one segment of $ a $ ? See definitions of segment and reversing in the notes.

## 说明/提示

Sample 1. You can reverse the entire array to get $ [1,2,3] $ , which is sorted.

Sample 3. No segment can be reversed such that the array will be sorted.

Definitions

A segment $ [l,r] $ of array $ a $ is the sequence $ a[l],a[l+1],...,a[r] $ .

If you have an array $ a $ of size $ n $ and you reverse its segment $ [l,r] $ , the array will become:

 $ a[1],a[2],...,a[l-2],a[l-1],a[r],a[r-1],...,a[l+1],a[l],a[r+1],a[r+2],...,a[n-1],a[n]. $

## 样例 #1

### 输入

```
3
3 2 1
```

### 输出

```
yes
1 3
```

## 样例 #2

### 输入

```
4
2 1 3 4
```

### 输出

```
yes
1 2
```

## 样例 #3

### 输入

```
4
3 1 2 4
```

### 输出

```
no
```

## 样例 #4

### 输入

```
2
1 2
```

### 输出

```
yes
1 1
```

# AI分析结果



【中文重写题目】  
# 排序数组  

## 题目描述  
作为程序员，你非常喜欢数组。生日时，朋友赠送了一个包含 n 个不同整数的数组 a。但你觉得数组太小，想要更大的数组！朋友答应给你更大的数组，前提是你能正确回答：能否通过精确反转数组 a 的一个连续片段，使其变为递增有序？  

## 输入输出样例  
样例1：输入数组[3,2,1]，反转整个数组后得到有序数组。  
样例3：无法找到任何可反转的片段使数组有序。  

【算法分类】  
模拟  

【题解综合分析】  
各解法核心思路均为：定位待反转区间→验证反转后有序。关键差异在于区间定位方式和验证逻辑的优化。  

★★★★★ 精选题解（评分与亮点）  
1. William20（4星）  
- 亮点：双指针定位差异区间，排序对比验证  
- 核心逻辑：  
   ```cpp
   sort(b, b + n);  // 创建排序副本
   // 双指针定位首个差异区间
   while(a[l]==b[l]) l++;  
   while(a[r]==b[r]) r--;  
   reverse(a+l, a+r+1);  // 反转验证
   ```

2. 小豆子范德萨（4星）  
- 亮点：对称交换代替reverse，内存优化  
- 核心实现：  
   ```cpp
   while(l<r) swap(v1[l++],v1[r--]);  // 手动交换减少库依赖
   ```

3. 断清秋（3.5星）  
- 亮点：直接比较排序前后差异区间  
- 注意点：需处理数组本就有序的特殊情况  

【最优思路提炼】  
1. 创建排序副本作为目标数组  
2. 双向扫描定位首个差异区间的左右端点  
3. 反转该区间后与目标数组比对  
4. 特例处理：原数组已有序时输出1 1  

【调试心得】  
- 边界处理：反转区间端点需+1（数组从0或1开始易出错）  
- 验证陷阱：反转后的区间外部必须自然有序（如样例3的3 1 2 4反转后中间仍无序）  

【相似题目推荐】  
1. P1908 逆序对 → 分析数组有序性  
2. P1115 最大子段和 → 区间定位技巧  
3. P2107 小Z的AK计划 → 区间操作与验证

---
处理用时：40.18秒