# 题目信息

# [USACO08OPEN] Word Power S

## 题目描述

Farmer John wants to evaluate the quality of the names of his N (1 <= N <= 1000) cows. Each name is a string with no more than 1000 characters, all of which are non-blank.

He has created a set of M (1 <= M <= 100) 'good' strings (no

longer than 30 characters and fully non-blank). If the sequence letters of a cow's name contains the letters of a 'good' string in the correct order as a subsequence (i.e., not necessarily all next to each other), the cow's name gets 1 quality point.

All strings is case-insensitive, i.e., capital letters and lower case letters are considered equivalent.  For example, the name 'Bessie' contains the letters of 'Be', 'sI', 'EE', and 'Es' in the correct order, but not 'is' or 'eB'. Help Farmer John determine the number of quality points in each of his cow's names.

约翰想要计算他那N(l < =N <= 1000)只奶牛的名字的能量.每只奶牛的名字由不超过1000个字 符构成，没有一个名字是空字体串.

约翰有一张“能量字符串表”，上面有M(1 < =M < =100)个代表能量的字符串.每个字符串 由不超过30个字体构成，同样不存在空字符串.一个奶牛的名字蕴含多少个能量字符串，这个名 字就有多少能量.所谓“蕴含”，是指某个能量字符串的所有字符都在名字串中按顺序出现（不 一定一个紧接着一个）.

所有的大写字母和小写字母都是等价的.比如，在贝茜的名字“Bessie”里，蕴含有“Be” “si” “EE”以及“Es”等等字符串，但不蕴含“Ls”或“eB” .请帮约翰计算他的奶牛的名字 的能量.


## 说明/提示

There are 5 cows, and their names are "Bessie", "Jonathan", "Montgomery", "Alicia", and "Angola". The 3 good strings are "se", "nGo", and "Ont".


"Bessie" contains "se", "Jonathan" contains "Ont", "Montgomery" contains both "nGo" and "Ont", Alicia contains none of the good strings, and "Angola" contains "nGo".


## 样例 #1

### 输入

```
5 3 
Bessie 
Jonathan 
Montgomery 
Alicia 
Angola 
se 
nGo 
Ont 
```

### 输出

```
1 
1 
2 
0 
1 
```

# AI分析结果

### 综合分析与结论

本题的核心问题是如何判断一个字符串是否包含另一个字符串的所有字符，且顺序一致。所有题解都采用了模拟的方法，通过遍历字符串来匹配字符。主要的优化点包括：

1. **大小写统一**：所有题解都先将字符串统一为小写或大写，以简化匹配过程。
2. **双指针匹配**：大多数题解使用双指针（一个指向名字字符串，一个指向能量字符串）来匹配字符，确保顺序一致。
3. **提前终止**：部分题解在匹配成功后立即跳出循环，减少不必要的遍历。

### 所选高星题解

#### 题解1：作者：agicy (5星)
**关键亮点**：
- **代码简洁**：使用了函数 `Appered` 来判断是否匹配，代码结构清晰。
- **寄存器优化**：使用了 `register` 关键字来优化循环变量，提升性能。

**核心代码**：
```cpp
bool Appered(const char *Name,const char *Word){
    int i,j,lenN=strlen(Name),lenW=strlen(Word);
    for(i=j=0;i<lenN;i++){
        if(Name[i]==Word[j])
            j++;
        if(j==lenW)
            return true;//出现
    }
    return false;//不出现
}
```
**实现思想**：使用双指针遍历名字和能量字符串，匹配成功后返回 `true`。

#### 题解2：作者：超级小帆船RP (4星)
**关键亮点**：
- **结构体优化**：使用结构体存储字符串及其长度，减少重复计算。
- **提前终止**：在匹配成功后立即跳出循环，减少不必要的遍历。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    int tot=0;
    for(int j=1;j<=m;j++){
        int now=1,L=b[j].len;
        for(int k=1;k<=a[i].len;k++){
            if(a[i].s[k]==b[j].s[now]){
                now++;
                if(now>L){
                    ++tot;
                    break;
                }
            }
        }
    }
    score[i]=tot;
}
```
**实现思想**：使用三重循环，外层遍历名字，中层遍历能量字符串，内层匹配字符。

#### 题解3：作者：珅肐 (4星)
**关键亮点**：
- **STL优化**：使用 `transform` 函数统一大小写，代码简洁。
- **双指针匹配**：使用双指针匹配字符，确保顺序一致。

**核心代码**：
```cpp
inline bool Check(string a,string b){
    for(int i=0,j=0;i<a.length();++i){
        if(a[i]==b[j])++j;
        if(j==b.length())return 1;
    }
    return 0;
}
```
**实现思想**：使用双指针遍历名字和能量字符串，匹配成功后返回 `true`。

### 最优关键思路与技巧

1. **双指针匹配**：使用双指针遍历两个字符串，确保字符顺序一致。
2. **大小写统一**：先将字符串统一为小写或大写，简化匹配过程。
3. **提前终止**：在匹配成功后立即跳出循环，减少不必要的遍历。

### 可拓展之处

- **多字符串匹配**：可以扩展到多个字符串的匹配问题，如KMP算法或AC自动机。
- **动态规划**：可以使用动态规划来优化匹配过程，减少时间复杂度。

### 推荐题目

1. **P3375 【模板】KMP字符串匹配**：考察字符串匹配的经典算法。
2. **P3808 【模板】AC自动机（简单版）**：考察多字符串匹配的经典算法。
3. **P3376 【模板】网络最大流**：考察图论中的最大流问题，与字符串匹配问题有相似的优化思路。

### 个人心得总结

- **调试经历**：部分题解提到在调试过程中发现大小写不统一导致匹配失败，提醒我们在处理字符串时要注意大小写问题。
- **踩坑教训**：部分题解提到在匹配成功后忘记跳出循环，导致不必要的遍历，提醒我们在优化代码时要注意细节。
- **顿悟感想**：部分题解提到使用双指针匹配字符时，顺序一致是关键，提醒我们在处理字符串匹配问题时要注意顺序问题。

---
处理用时：32.26秒