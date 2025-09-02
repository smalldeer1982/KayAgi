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



1. **唯一算法分类**  
前缀和与哈希（数组优化）

---

2. **综合分析与结论**  
**核心思路**：将0视为-1，1视为1，计算前缀和。平衡子串对应前缀和相等的两个端点，其最长长度即为两位置之差。  
**难点**：  
- 前缀和可能为负，需偏移处理（如+max_n）保证数组索引合法。  
- 正确计算子串长度（右端点i与左端点j对应的子串是j+1到i，长度i-j）。  
**解决方案**：  
- 使用数组记录每个前缀和首次出现的位置，偏移n避免负数。  
- 遍历时动态更新数组，并计算当前前缀和与历史位置的差值长度。  

**可视化设计**：  
- **动画方案**：显示字符串转数值后的数组，前缀和曲线图。每次遍历i时高亮当前sum[i]，并连线匹配的历史sum[j]位置，动态更新最大长度。  
- **颜色标记**：当前sum[i]（红色）、历史匹配点（绿色）、最大长度标记（黄色）。  
- **步进控制**：允许单步执行观察前缀和数组与首次出现位置的更新过程。  
- **复古像素风格**：用8-bit像素块表示前缀和变化，音效在找到更长长度时播放上扬音效。  

---

3. **题解清单 (≥4星)**  
- **zhengrunzhe (5星)**：高效数组处理，O(1)查询，代码简洁。  
- **曼恩薄荷 (4星)**：思路清晰，但使用map略慢，适合教学。  
- **ynxynx (4星)**：与zhengrunzhe类似，代码稍作调整，同样高效。  

---

4. **最优思路与代码**  
**关键技巧**：  
- 前缀和偏移避免负数索引。  
- 遍历时记录sum[i-1]的位置，确保子串计算为i到k的长度k-i+1。  

**核心代码**：  
```cpp
int n, sum[N], first[N*2], ans;
char s[N];
scanf("%d%s", &n, s+1);
for (int i=1; i<=n; i++) 
    sum[i] = sum[i-1] + (s[i]=='1' ? 1 : -1);
memset(first, 0, sizeof(first));
for (int i=1; i<=n; i++) {
    int curr = sum[i] + n; // 偏移处理
    if (first[curr]) 
        ans = max(ans, i - first[curr] +1);
    int prev = sum[i-1] + n;
    if (!first[prev]) 
        first[prev] = i; // 记录sum[i-1]首次出现的位置i
}
printf("%d\n", ans);
```

---

5. **同类题型与推荐**  
- **通用解法**：前缀和+哈希表处理子数组和为特定值问题。  
- **类似题目**：  
  - LeetCode 525. 连续数组（同题）  
  - 洛谷 P1115 最大子段和（前缀和变形）  
  - 洛谷 P3131 [USACO16JAN] Subsequences Summing to Sevens  
  - 洛谷 P2697 宝石串（平衡子串变种）  

---

6. **个人心得**  
- **调试关键**：前缀和索引从0开始，处理i=1时的sum[0]初始值。  
- **易错点**：子串长度计算应为i-j而非i-j+1，但zhengrunzhe通过存入i的位置巧妙转化为+1的正确计算。  

---

7. **可视化实现要点**  
- **Canvas绘制**：横向像素条表示前缀和值，绿色块标记首次出现位置，红色块当前i。  
- **音效触发**：发现更长长度时播放“升级”音效，错误计算时短促“哔”声。  
- **自动演示**：按帧逐步推进，用户可暂停调整速度观察哈希表变化。

---
处理用时：258.26秒