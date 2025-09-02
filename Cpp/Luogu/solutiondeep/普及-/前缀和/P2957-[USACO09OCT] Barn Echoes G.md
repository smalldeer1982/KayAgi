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
本题核心是寻找两个字符串的最大重叠部分（一个字符串的前缀与另一个字符串的后缀）。各题解主要采用暴力枚举、哈希预处理、KMP算法三种思路。最优解法为暴力枚举（数据范围小）+ 从大到小提前终止的优化策略，时间复杂度O(n²)在n≤80时完全可行。哈希方法展示了更高效的前后缀比较技巧，KMP则提供了字符串匹配的进阶思路。

---

### 精选题解（评分≥4星）

#### 1. Alex_Wei（★★★★☆）
**关键亮点**：  
- 利用`substr`函数简洁实现前后缀提取  
- 从大到小枚举长度，找到即终止  
- 交换字符串避免越界的细节处理  
**代码核心**：
```cpp
for(int x=a.size()-1;x>=0;x--){ // 倒序枚举
    string prea = a.substr(0,x), sufa = a.substr(a.size()-x,x);
    string preb = b.substr(0,x), sufb = b.substr(b.size()-x,x);
    if(prea==sufb || preb==sufa) return x; // 匹配即返回
}
```

#### 2. huayt（★★★★☆）
**关键亮点**：  
- 双哈希预处理前后缀  
- 通过哈希值比较避免逐字符对比  
- 边界处理清晰  
**核心实现**：
```cpp
// 预处理双哈希
for(int i=1;i<=lena;i++) hl[i] = hl[i-1]*base + s[i];
for(int i=1;i<=lenb;i++) hr[i] = hr[i-1]*base + t[i];

// 比较哈希值
if(get(hl,1,i) == get(hr,lenb-i+1,lenb)) 
    max_len = max(max_len, i);
```

#### 3. 子夜葵（★★★★☆）
**关键亮点**：  
- 利用KMP的next数组特性  
- 主串与模式串互换两次匹配  
- 时间复杂度优化至O(n+m)  
**代码核心**：
```cpp
int KMP(char a[], int la, char b[], int lb) {
    buildNext(b, lb); // 构建next数组
    int i = 0, j = 0;
    while(i < la) { // 匹配过程
        if(j == -1 || a[i] == b[j]) i++, j++;
        else j = next[j];
    }
    return j; // j即最大匹配长度
}
```

---

### 最优技巧总结
1. **逆向枚举长度**：从最大可能长度开始，首次匹配即为最优解，避免全遍历。  
2. **哈希预处理**：将字符串比较转化为数值比较，时间复杂度从O(n³)降为O(n²)。  
3. **KMP特性利用**：通过部分匹配表直接获取最长公共前后缀长度。  

---

### 拓展与相关题目
**同类型题目推荐**：  
1. P3375 【模板】KMP字符串匹配  
2. P1368 最小表示法  
3. P3449 [POI2006]PAL-Palindromes  

**关键套路**：  
- 字符串前后缀处理可结合哈希、KMP、Z-Algorithm  
- 滚动哈希设计时注意基数和模数选择  
- 当数据范围较小时，优先考虑暴力枚举的简洁性  

---

### 题解心得分镜
**Alex_Wei的调试经验**：  
> "如果a比b长，先调换位置避免substr时访问越界"  
—— 通过交换字符串统一处理边界，避免代码冗余  

**huayt的哈希心得**：  
> "自然溢出法比取模更快，双哈希可防碰撞"  
—— 哈希参数选择对效率和正确性的平衡  

**Illenium的简洁哲学**：  
> "string类函数为我省了好多功夫"  
—— 合理利用STL可大幅降低编码复杂度

---
处理用时：65.21秒