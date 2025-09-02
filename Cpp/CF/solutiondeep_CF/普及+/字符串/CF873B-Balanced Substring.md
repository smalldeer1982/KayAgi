# 题目信息

# Balanced Substring

## 题目描述

You are given a string $ s $ consisting only of characters 0 and 1. A substring $ [l,r] $ of $ s $ is a string $ s_{l}s_{l+1}s_{l+2}...\ s_{r} $ , and its length equals to $ r-l+1 $ . A substring is called balanced if the number of zeroes (0) equals to the number of ones in this substring.

You have to determine the length of the longest balanced substring of $ s $ .

## 说明/提示

In the first example you can choose the substring $ [3,6] $ . It is balanced, and its length is $ 4 $ . Choosing the substring $ [2,5] $ is also possible.

In the second example it's impossible to find a non-empty balanced substring.

## 样例 #1

### 输入

```
8
11010111
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
111
```

### 输出

```
0
```

# AI分析结果



# Balanced Substring

## 题目描述

给定一个仅由字符0和1组成的字符串$s$。子串$[l,r]$表示字符串$s_ls_{l+1}s_{l+2}...s_r$，其长度等于$r-l+1$。若子串中0的数量等于1的数量，则称为平衡子串。

请确定$s$中最长平衡子串的长度。

## 说明/提示

第一个样例中可以选择子串$[3,6]$，它是平衡的且长度为4。选择子串$[2,5]$也是可行的。

第二个样例中无法找到非空的平衡子串。

## 样例 #1

### 输入

```
8
11010111
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
111
```

### 输出

```
0
```

---

### 综合分析与结论

各题解均采用**前缀和+哈希表**的核心思路，主要差异在于哈希表实现方式（数组vs map）和具体实现细节。关键技巧在于将0视为-1转化为求零和区间，通过维护前缀和首次出现位置快速计算区间长度。

---

### 高分题解精选

#### 1. zhengrunzhe（⭐⭐⭐⭐⭐）
**亮点**：使用数组替代map，通过偏移量处理负数下标，时间复杂度严格O(n)
```cpp
int sum[N], first[N+N];
for (int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='1'?1:-1);
for (int i=1;i<=n;i++) {
    if (first[sum[i]+n]) ans=max(ans,i-first[sum[i]+n]);
    if (!first[sum[i-1]+n]) first[sum[i-1]+n]=i;
}
```
**心得**："为什么要map啊，还带个log" 强调数组直接寻址的优化价值

#### 2. 曼恩薄荷（⭐⭐⭐⭐）
**亮点**：map实现更易理解，处理前缀和为0的特殊情况
```cpp
map<int,int> Map;
if(!s[i]) ans = max(ans,i);
if(!Map[s[i]]) Map[s[i]] = i;
else ans = max(i-Map[s[i]],ans);
```
**特点**：使用`scanf("%1d")`实现逐字符处理

#### 3. AC_Automation（⭐⭐⭐⭐）
**亮点**：即时更新答案，减少空间占用
```cpp
if(book[sum+100000]==0) book[sum+100000]=i;
else ans=max(ans,i-book[sum+100000]);
```
**优化**：仅维护当前所需的哈希记录，节省内存

---

### 关键思路总结
1. **转化思想**：将0视为-1，问题转化为求零和区间
2. **前缀和特性**：sum[r]=sum[l-1]时区间[l,r]平衡
3. **哈希表优化**：记录每个sum值的首次出现位置
4. **负数处理**：通过+n或固定偏移量保证数组下标合法

---

### 相似题目推荐
1. P1115 最大子段和（前缀和极值）
2. CF1398C Subarray Sum Equals K（相同前缀差应用）
3. P3406 海底高铁（前缀和统计技巧）

---

### 实用调试心得
1. **边界处理**：前缀和数组应从sum[0]=0开始
2. **偏移量选择**：足够覆盖[-n,n]范围（如+n或1e5）
3. **初始化陷阱**：哈希表需特殊标记未访问状态（如0x3f3f3f）
4. **更新顺序**：先检查答案再更新哈希表，避免覆盖更优解

---
处理用时：45.34秒