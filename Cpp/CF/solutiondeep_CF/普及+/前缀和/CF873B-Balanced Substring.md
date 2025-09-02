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

给定一个由字符 0 和 1 组成的字符串 $s$。子串 $[l,r]$ 定义为字符串 $s_l s_{l+1} ... s_r$，其长度为 $r-l+1$。若子串中 0 的数量等于 1 的数量，则称为平衡子串。求最长平衡子串的长度。

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

---

## 题解分析与结论

### 关键思路总结
1. **问题转换**：将 0 视为 -1，1 视为 1，平衡子串等价于子串和为 0。
2. **前缀和优化**：维护前缀和数组，若 $sum[r] = sum[l-1]$，则子串 $[l, r]$ 平衡。
3. **快速查询首次出现位置**：用数组（而非哈希表）记录每个前缀和首次出现的位置，时间复杂度优化至 $O(n)$。
4. **偏移量处理**：前缀和范围 $[-n, n]$，通过加 $n$ 转换为非负索引，避免负数下标问题。

---

## 高分题解精选

### 题解1：zhengrunzhe（★★★★★）
**亮点**：数组替代哈希表，极致优化时间复杂度，边界处理严谨。
```cpp
#include<cstdio>
int max(int a,int b){return a>b?a:b;}
const int N=1e5+10;
int n,sum[N],first[N+N],ans;
char s[N];
int main() {
    scanf("%d",&n);
    scanf("%s",s+1);
    for (int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='1'?1:-1);
    for (int i=1;i<=n;i++) {
        if (first[sum[i]+n]) ans=max(ans,i-first[sum[i]+n]+1);
        if (!first[sum[i-1]+n]) first[sum[i-1]+n]=i;
    }
    printf("%d\n",ans);
    return 0;
}
```

**核心思想**：
- 遍历时记录 `sum[i-1]` 的首次出现位置，后续若 `sum[j]` 相同则子串长度为 `j - first[sum[j]]`。

---

### 题解2：ynxynx（★★★★★）
**亮点**：代码简洁，逻辑与题解1一致，直接处理偏移量。
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=1e5+10;
int n,sum[N],f[2*N],ans;
char s[N];
int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='1'?1:-1);
    for(int i=1;i<=n;i++){
        if(f[sum[i]+n]) ans=max(ans,i-f[sum[i]+n]+1);
        if(!f[sum[i-1]+n]) f[sum[i-1]+n]=i;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

### 题解3：曼恩薄荷（★★★★☆）
**亮点**：使用 `map` 更直观，适合理解思路，但效率略低。
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[100005],n,ans;
map<int,int>Map;
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        int t; scanf("%1d",&t);
        s[i] = s[i-1] + (t ? 1 : -1);
        if(!s[i]) ans = max(ans,i);
        if(!Map[s[i]]) Map[s[i]] = i;
        else ans = max(i-Map[s[i]],ans);
    }
    printf("%d",ans);
    return 0;
}
```

**个人心得**：  
需注意 `map` 的初始值处理，首次出现的 `sum[i]` 需直接记录位置，后续遇到相同值时才可计算长度。

---

## 拓展练习
1. **洛谷 P1115** - 最大子段和（前缀和/动态规划）
2. **洛谷 P3131** - 寻找和能被7整除的最长子数组（前缀和+模运算）
3. **洛谷 P3406** - 海底高铁（差分与前缀和结合）

---
处理用时：223.99秒