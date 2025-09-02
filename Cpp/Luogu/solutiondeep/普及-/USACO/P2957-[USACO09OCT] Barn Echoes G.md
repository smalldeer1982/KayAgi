# 题目信息

# [USACO09OCT] Barn Echoes G

## 题目描述

The cows enjoy mooing at the barn because their moos echo back, although sometimes not completely. Bessie, ever the excellent

secretary, has been recording the exact wording of the moo as it goes out and returns. She is curious as to just how much overlap there is.

Given two lines of input (letters from the set a..z, total length in the range 1..80), each of which has the wording of a moo on it, determine the greatest number of characters of overlap between one string and the other. A string is an overlap between two other strings if it is a prefix of one string and a suffix of the other string.

By way of example, consider two moos:

```
moyooyoxyzooo
yzoooqyasdfljkamo
```
The last part of the first string overlaps 'yzooo' with the first part of the second string. The last part of the second string

overlaps 'mo' with the first part of the first string. The largest overlap is 'yzooo' whose length is 5.

POINTS: 50

奶牛们非常享受在牛栏中哞叫，因为她们可以听到她们哞声的回音。虽然有时候并不能完全听到完整的回音。Bessie 曾经是一个出色的秘书，所以她精确地纪录了所有的哞叫声及其回声。她很好奇到底两个声音的重复部份有多长。

输入两个字符串（长度为 $1$ 到 $80$ 个字母），表示两个哞叫声。你要确定最长的重复部份的长度。两个字符串的重复部份指的是同时是一个字符串的前缀和另一个字符串的后缀的字符串。

我们通过一个例子来理解题目。考虑下面的两个哞声：

```
moyooyoxyzooo
yzoooqyasdfljkamo
```

第一个串的最后的部份 `yzooo` 跟第二个串的第一部份重复。第二个串的最后的部份 `mo` 跟第一个串的第一部份重复。所以 `yzooo` 跟 `mo` 都是这 $2$ 个串的重复部份。其中，`yzooo` 比较长，所以最长的重复部份的长度就是 $5$。


## 说明/提示

'abcxxxxabcx' is a prefix of the first string and a suffix of the second string.


## 样例 #1

### 输入

```
abcxxxxabcxabcd 
abcdxabcxxxxabcx 
```

### 输出

```
11 
```

# AI分析结果



### 综合分析与结论
本题核心是寻找两个字符串的最长公共前后缀。所有题解均围绕「暴力枚举子串」与「优化比较方式」展开，主要差异在于比较手段（直接比较、哈希、KMP）和实现思路。由于题目数据范围极小（长度≤80），暴力枚举即可高效解决，而哈希/KMP等优化算法更适合大范围数据。

### 高星题解推荐
---

#### 1. 作者：Alex_Wei（4星）
**关键亮点**  
- 直接暴力枚举所有可能的长度，利用 `substr` 截取前后缀  
- 倒序枚举长度，找到即退出，避免冗余计算  
- 代码简洁，可读性极强，适合快速理解题意  

**核心代码**  
```cpp
for(int x=a.size()-1;x>=0;x--){ // 倒序枚举长度
    string prea = a.substr(0,x), sufa = a.substr(a.size()-x,x);
    string preb = b.substr(0,x), sufb = b.substr(b.size()-x,x);
    if(prea == sufb || preb == sufa) // 两种情况比较
        cout << x << endl, exit(0);
}
```

---

#### 2. 作者：huayt（4星）
**关键亮点**  
- 哈希预处理前后缀，快速比较子串  
- 双重哈希校验（前缀与后缀交叉比较）  
- 代码结构清晰，哈希冲突处理合理  

**核心代码**  
```cpp
// 哈希预处理
for(int i=1; i<=lena; i++) hl[i] = hl[i-1]*base + (stra[i]-96);
for(int i=1; i<=lenb; i++) hr[i] = hr[i-1]*base + (strb[i]-96);

// 比较哈希值
ULL get(ULL h[], int l, int r) {
    return h[r] - h[l-1] * p[r-l+1];
}
if (get(hl,1,i) == get(hr, lenb-i+1, lenb)) // 前缀与后缀比较
```

---

#### 3. 作者：Illenium（4星）
**关键亮点**  
- 分两次独立比较两种重叠方向（A前缀-B后缀、B前缀-A后缀）  
- 提前终止循环的优化，减少无效比较  
- 代码极度简洁，适合新手快速实现  

**核心代码**  
```cpp
for(i = n; i >=1; i--) // A的前缀与B的后缀比较
    if(a.substr(0,i) == b.substr(b.size()-i,i)) break;
for(j = n; j >=1; j--) // B的前缀与A的后缀比较
    if(b.substr(0,j) == a.substr(a.size()-j,j)) break;
cout << max(i,j);
```

---

### 最优技巧总结
1. **暴力枚举+倒序优化**：从最大可能长度倒序枚举，找到即终止，避免全量计算。  
2. **哈希加速比较**：预处理前后缀哈希值，将子串比较转换为哈希值比对，适用于大规模数据。  
3. **双方向独立校验**：分别处理A→B和B→A两种重叠方向，确保所有情况覆盖。

---

### 拓展建议
**同类题型推荐**  
- [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)  
- [P3449 [POI2006]PAL-Palindromes](https://www.luogu.com.cn/problem/P3449)（最长双回文串）  
- [P1368 【模板】最小表示法](https://www.luogu.com.cn/problem/P1368)（循环字符串处理）

**个人心得摘录**  
- **调试陷阱**：`substr`参数为`(起始位置, 长度)`而非`(起始, 结束)`，需注意下标越界（如Alex_Wei题解中的`swap(a,b)`避免越界）。  
- **思维盲点**：KMP的`next`数组可快速计算最长公共前后缀，但需深入理解其原理（子夜葵题解）。  
- **优化直觉**：哈希冲突可通过双哈希降低概率，但本题数据量小可忽略（huayt题解）。

---
处理用时：58.16秒