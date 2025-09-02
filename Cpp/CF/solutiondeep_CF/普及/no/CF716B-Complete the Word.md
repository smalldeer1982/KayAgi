# 题目信息

# Complete the Word

## 题目描述

ZS the Coder loves to read the dictionary. He thinks that a word is nice if there exists a substring (contiguous segment of letters) of it of length $ 26 $ where each letter of English alphabet appears exactly once. In particular, if the string has length strictly less than $ 26 $ , no such substring exists and thus it is not nice.

Now, ZS the Coder tells you a word, where some of its letters are missing as he forgot them. He wants to determine if it is possible to fill in the missing letters so that the resulting word is nice. If it is possible, he needs you to find an example of such a word as well. Can you help him?

## 说明/提示

In the first sample case, ABCDEFGHIJKLMNOPQRZTUVWXYS is a valid answer beacuse it contains a substring of length $ 26 $ (the whole string in this case) which contains all the letters of the English alphabet exactly once. Note that there are many possible solutions, such as ABCDEFGHIJKLMNOPQRSTUVWXYZ or ABCEDFGHIJKLMNOPQRZTUVWXYS.

In the second sample case, there are no missing letters. In addition, the given string does not have a substring of length $ 26 $ that contains all the letters of the alphabet, so the answer is $ -1 $ .

In the third sample case, any string of length $ 26 $ that contains all letters of the English alphabet fits as an answer.

## 样例 #1

### 输入

```
ABC??FGHIJK???OPQR?TUVWXY?
```

### 输出

```
ABCDEFGHIJKLMNOPQRZTUVWXYS```

## 样例 #2

### 输入

```
WELCOMETOCODEFORCESROUNDTHREEHUNDREDANDSEVENTYTWO
```

### 输出

```
-1```

## 样例 #3

### 输入

```
??????????????????????????
```

### 输出

```
MNBVCXZLKJHGFDSAQPWOEIRUYT```

## 样例 #4

### 输入

```
AABCDEFGHIJKLMNOPQRSTUVW??M
```

### 输出

```
-1```

# AI分析结果



### 题目中文翻译

# 完成单词

## 题目描述

ZS喜欢阅读字典。他认为一个单词是"完美"的，当且仅当存在其某个长度为26的连续子串（即连续的字母段），其中每个英文字母恰好出现一次。特别地，若字符串长度严格小于26，则不可能存在这样的子串，因此该单词不完美。

现在ZS给出一个包含缺失字母（用?表示）的单词，要求你判断是否能填充这些缺失字母使得单词变得完美。若可行，还需要输出一种可能的填充结果，否则输出-1。

## 输入输出样例

样例1输入：  
`ABC??FGHIJK???OPQR?TUVWXY?`  
样例1输出：  
`ABCDEFGHIJKLMNOPQRZTUVWXYS`  
（存在多个合法解）

样例2输入：  
`WELCOMETOCODEFORCESROUNDTHREEHUNDREDANDSEVENTYTWO`  
样例2输出：  
`-1`  
（无缺失字母且不满足条件）

---

### 算法分类  
**构造**

---

### 题解综合分析

**核心逻辑**：  
遍历所有长度为26的窗口，统计字母出现情况。若某个窗口满足：  
1. 现有字母无重复  
2. 缺失字母数 ≤ 问号数量  
则可用问号填充缺失字母，剩余问号随意填充。

**难点对比**：  
1. 滑动窗口的频率维护方式（直接统计 vs 增量更新）  
2. 问号填充顺序的优化（顺序查找空缺 vs 预存空缺列表）  
3. 剩余问号处理方式（统一填充'A' vs 随机填充）

---

### 高星题解推荐

#### 1. wkjwkj（⭐⭐⭐⭐⭐）  
**关键亮点**：  
- 滑动窗口增量更新频率数组，时间复杂度O(n)  
- 清晰的双重检查逻辑（重复字母检查 + 空缺填充）  
- 剩余问号统一填充处理

**核心代码片段**：  
```cpp
for(int i=26; i<=len; i++) { // 滑动窗口右端点
    if(s[i]>='A' && s[i]<='Z') b[s[i]-'A'+1]++;
    // 检查重复字母
    bool yes = false;
    for(int j=1;j<=26;j++) if(b[j]>1) yes = true;
    if(yes) continue;
    
    // 填充问号
    for(int p=i-25; p<=i; p++) {
        if(s[p] == '?') {
            for(int j=1;j<=26;j++)
                if(b[j]==0) { s[p] = j+'A'-1; break; }
        }
    }
    // 剩余问号统一填充
    for(int i=1;i<=len;i++) 
        if(s[i]=='?') s[i] = 'A';
}
```

#### 2. YueYang1235（⭐⭐⭐⭐）  
**关键亮点**：  
- 优化频率数组更新方式（头减尾增）  
- 使用整数数组替代字符映射提升效率  
- 严格处理窗口边界条件

**代码亮点**：  
```cpp
for(int i=1; i<=26; i++) ha[a[i]]++; // 初始窗口
for(int i=2; i<=n-24; i++) { // 滑动窗口
    ha[a[i-1]]--;          // 移除左端点
    ha[a[i+25]]++;         // 添加右端点
    if(检查通过) {
        // 填充逻辑
    }
}
```

#### 3. The_outcast_person（⭐⭐⭐⭐）  
**关键亮点**：  
- 预存空缺字母列表实现O(1)填充  
- 使用字符串拼接优化空缺字母访问

**核心实现**：  
```cpp
string k = "";
for(char j='A'; j<='Z'; j++) 
    if(!t[j]) k += j; // 预存空缺字母
int now = 0;
for(int j=i; j<=i+25; j++) 
    if(s[j] == '?') s[j] = k[now++];
```

---

### 最优技巧总结  
1. **滑动窗口优化**：通过增量更新频率数组，将时间复杂度从O(26n)降为O(n)  
2. **空缺字母预存**：提前收集可填充字母，实现O(1)时间填充  
3. **双重校验机制**：先检查字母重复性，再验证问号数量是否足够  
4. **剩余问号处理**：统一填充避免复杂判断（SPJ支持任意填充）

---

### 拓展训练建议  
类似问题可练习：  
1. **滑动窗口应用**：  
   - P2558 [ACWing] 最长无重复子串  
   - P3400 [POI] 字符串统计  
2. **字符串构造**：  
   - P1279 字符重组（NOI真题）  
3. **哈希优化**：  
   - P3834 滑动窗口最大值（双指针+单调队列）

---

### 题解心得摘录  
1. **G__G**：  
   "调代码时因为i和j不分调了两晚上" → 强调变量命名清晰的重要性  
2. **Siteyava_145**：  
   "SPJ支持任意填充" → 发现题目隐藏特性可简化代码  
3. **Elhaithan**：  
   "随机数填充可能引发意外错误" → 优先使用确定性填充方式

---
处理用时：72.61秒