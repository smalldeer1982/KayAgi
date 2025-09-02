# 题目信息

# They Are Everywhere

## 题目描述

Sergei B., the young coach of Pokemons, has found the big house which consists of $ n $ flats ordered in a row from left to right. It is possible to enter each flat from the street. It is possible to go out from each flat. Also, each flat is connected with the flat to the left and the flat to the right. Flat number $ 1 $ is only connected with the flat number $ 2 $ and the flat number $ n $ is only connected with the flat number $ n-1 $ .

There is exactly one Pokemon of some type in each of these flats. Sergei B. asked residents of the house to let him enter their flats in order to catch Pokemons. After consulting the residents of the house decided to let Sergei B. enter one flat from the street, visit several flats and then go out from some flat. But they won't let him visit the same flat more than once.

Sergei B. was very pleased, and now he wants to visit as few flats as possible in order to collect Pokemons of all types that appear in this house. Your task is to help him and determine this minimum number of flats he has to visit.

## 说明/提示

In the first test Sergei B. can begin, for example, from the flat number $ 1 $ and end in the flat number $ 2 $ .

In the second test Sergei B. can begin, for example, from the flat number $ 4 $ and end in the flat number $ 6 $ .

In the third test Sergei B. must begin from the flat number $ 2 $ and end in the flat number $ 6 $ .

## 样例 #1

### 输入

```
3
AaA
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
bcAAcbc
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6
aaBCCe
```

### 输出

```
5
```

# AI分析结果



### 题目重写
#### 题目名称：它们无处不在

**题目描述**  
Sergei B. 是一位年轻的宝可梦教练，他发现一栋由 $n$ 个公寓排成一行的房子，每个公寓内恰好有一只特定类型的宝可梦。他需要从某个公寓进入，访问若干连续公寓（不能重复访问），并收集所有类型的宝可梦。求他需要访问的最少公寓数。

**输入格式**  
- 第一行输入整数 $n$  
- 第二行输入长度为 $n$ 的字符串，表示每个公寓的宝可梦类型（区分大小写）

**输出格式**  
输出最小需要访问的公寓数

**样例**  
输入1：  
```
3
AaA
```
输出1：  
```
2
```
解释：从1号公寓到2号公寓可收集'A'和'a'两种类型

### 算法分类  
滑动窗口（尺取法）

---

### 题解分析与结论  
**核心思路**  
求包含所有字符的最短连续子串，典型滑动窗口问题。通过维护左右指针动态调整窗口，用哈希表统计窗口内字符出现次数，并通过计数器判断是否包含所有字符。

**题解对比**  
1. **尺取法**（4.5星）：  
   - 左右指针维护窗口，右指针扩展直到包含所有字符，左指针收缩优化答案  
   - 用`map<char, int>`统计字符出现次数，`cnt`记录当前字符种类数  
   - 时间复杂度：$O(n)$

2. **二分+滑动窗口**（3星）：  
   - 二分答案长度，每次用滑动窗口检查该长度是否可行  
   - 时间复杂度：$O(n \log n)$，代码复杂度较高  

**最优思路**  
双指针滑动窗口法更优，关键技巧：  
1. 右指针扩展时更新字符计数和种类数  
2. 当窗口包含所有字符时，左指针持续右移以缩小窗口  
3. 用`ans`变量动态维护最小窗口长度

---

### 推荐题解  
#### 题解1：MIN__2500（4.5星）  
**核心代码**  
```cpp
int l=1, r=0, cnt=0;
while(l<=n && r<n) {
    r++;
    if(mm[arr[r]] == 0) cnt++;
    mm[arr[r]]++;
    
    while(cnt == size) { // 当包含所有字符时收缩窗口
        ans = min(ans, r-l+1);
        mm[arr[l]]--;
        if(mm[arr[l]] == 0) cnt--;
        l++;
    }
}
```
**亮点**  
- 代码结构清晰，变量命名规范  
- 使用`set`统计总字符种类数，逻辑严密  

#### 题解2：kevin1616（4星）  
**核心代码**  
```cpp
int l=0, r=1, tmp=0;
while(r <= n) {
    if(!mp2[a[r]]) sum++;
    mp2[a[r]]++;
    
    while(sum == m) { // 收缩优化
        ans = min(ans, r-l);
        mp2[a[l]]--;
        if(!mp2[a[l]]) sum--;
        l++;
    }
    r++;
}
```
**亮点**  
- 使用两个`map`分离总统计和窗口统计  
- 代码注释详细，便于理解  

---

### 关键技巧总结  
1. **哈希表优化**：用ASCII码直接映射到数组（`cnt[128]`）替代`map`可提升效率  
2. **窗口收缩条件**：当`cnt == total`时持续收缩左边界，直到不满足条件  
3. **去重技巧**：初始遍历用`set`统计总字符种类数  

---

### 同类题目推荐  
1. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)  
2. [P340 最长无重复子串](https://www.luogu.com.cn/problem/P340)  
3. [CF660C Hard Process](https://codeforces.com/problemset/problem/660/C)  

---

### 题解心得摘录  
> "移动左指针时若该字符计数归零，必须减少`cnt`，否则会误判窗口状态" —— Stars_visitor_tyw  
> "初始统计总字符数后要清空哈希表，否则会影响后续窗口统计" —— 老彩笔  
> "右指针每次只能移动一步，但左指针可能连续移动多步" —— shame_djj

---
处理用时：60.60秒