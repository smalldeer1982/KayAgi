# 题目信息

# Tanya and Postcard

## 题目描述

Little Tanya decided to present her dad a postcard on his Birthday. She has already created a message — string $ s $ of length $ n $ , consisting of uppercase and lowercase English letters. Tanya can't write yet, so she found a newspaper and decided to cut out the letters and glue them into the postcard to achieve string $ s $ . The newspaper contains string $ t $ , consisting of uppercase and lowercase English letters. We know that the length of string $ t $ greater or equal to the length of the string $ s $ .

The newspaper may possibly have too few of some letters needed to make the text and too many of some other letters. That's why Tanya wants to cut some $ n $ letters out of the newspaper and make a message of length exactly $ n $ , so that it looked as much as possible like $ s $ . If the letter in some position has correct value and correct letter case (in the string $ s $ and in the string that Tanya will make), then she shouts joyfully "YAY!", and if the letter in the given position has only the correct value but it is in the wrong case, then the girl says "WHOOPS".

Tanya wants to make such message that lets her shout "YAY!" as much as possible. If there are multiple ways to do this, then her second priority is to maximize the number of times she says "WHOOPS". Your task is to help Tanya make the message.

## 样例 #1

### 输入

```
AbC
DCbA
```

### 输出

```
3 0
```

## 样例 #2

### 输入

```
ABC
abc
```

### 输出

```
0 3
```

## 样例 #3

### 输入

```
abacaba
AbaCaBA
```

### 输出

```
3 4
```

# AI分析结果



# Tanya and Postcard

## 题目描述

小 Tanya 决定在她爸爸生日时送他一张明信片。她已经想好了要写的消息——字符串 $s$，由大小写英文字母组成。Tanya 还不会写字，于是她找到一份报纸，想通过剪下字母拼出字符串 $s$。报纸上的内容由字符串 $t$ 表示，长度不小于 $s$。

Tanya 希望从报纸中剪出恰好 $n$ 个字母（$n$ 为 $s$ 的长度），使得拼出的字符串尽可能像原消息。当某个位置的字母值（包括大小写）完全匹配时，她会欢呼 "YAY!"；若字母值相同但大小写不同，则说 "WHOOPS"。要求最大化 "YAY!" 次数，其次最大化 "WHOOPS" 次数。

## 标签
贪心

---

## 题解综合分析

各题解均采用**桶计数+贪心**的核心思路，差异主要体现在实现细节：
1. **桶的存储方式**：多数使用单个桶按字符存储（ASCII 码索引），部分将大小写分开存储为二维桶
2. **匹配顺序**：先处理完全匹配的字符，再处理大小写不同的情况
3. **去重处理**：通过修改原字符串标记已匹配字符（如置为空格），或直接在桶中扣除计数

### 最优题解推荐

#### 1. 作者：hanzizhou（4.5星）
**亮点**：代码简洁高效，通过修改原字符串标记已处理字符，避免重复计算  
**核心代码**：
```cpp
for(int i=0;i<l1;++i)if(sum[s[i]]>0){
    sum[s[i]]--;ans1++;s[i]=0; // 完全匹配
}
for(int i=0;i<l1;++i)if(s[i]>0){ // 处理剩余字符
    if(islower(s[i]) && sum[toupper(s[i])]){...}
    if(isupper(s[i]) && sum[tolower(s[i])]){...}
}
```
**实现思想**：  
1. 用单个桶统计报纸字符  
2. 第一轮遍历匹配完全相同的字符并标记  
3. 第二轮遍历处理大小写不同的情况

#### 2. 作者：Graphcity（4星）
**亮点**：使用二维桶区分大小写，逻辑清晰  
**核心代码**：
```cpp
// 分别统计大小写
if(ch>='a') s1[ch-'a'+1][0]++;
else s1[ch-'A'+1][1]++; 

// 完全匹配
while(s1[i][0] && s2[i][0]) ans1++... 

// 大小写交叉匹配
while(s1[i][0] && s2[i][1]) ans2++...
```
**实现思想**：  
1. 将大小写分开存储为二维数组  
2. 先处理相同大小写的完全匹配  
3. 再处理跨大小写的部分匹配

#### 3. 作者：shenbairui（4星）
**亮点**：通过 ASCII 码转换实现大小写切换，代码紧凑  
**核心技巧**：
```cpp
a[i]-32 // 大写转小写 
a[i]+32 // 小写转大写
```
**实现思想**：  
1. 使用三个循环分别处理三种匹配情况  
2. 通过修改字符值为空格避免重复处理

---

## 关键思路与技巧
1. **贪心优先级**：先处理完全匹配，再处理大小写不同的情况  
2. **桶计数优化**：使用 ASCII 码直接索引字符（`t[c]`）  
3. **去重技巧**：修改原字符串或维护桶计数来标记已处理字符  
4. **大小写转换**：利用 ASCII 码差（32）快速切换大小写形式

---

## 同类题目推荐
1. [CF514B - 汉诺塔密码](https://codeforces.com/problemset/problem/514/B)  
   - 相似点：字符频率统计与贪心匹配
2. [P1603 斯诺登的密码](https://www.luogu.com.cn/problem/P1603)  
   - 相似点：字符组合与优先级处理
3. [P1179 数字统计](https://www.luogu.com.cn/problem/P1179)  
   - 相似点：字符频率统计与条件计数

---
处理用时：61.10秒