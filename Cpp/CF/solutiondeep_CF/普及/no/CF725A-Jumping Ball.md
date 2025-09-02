# 题目信息

# Jumping Ball

## 题目描述

In a new version of the famous Pinball game, one of the most important parts of the game field is a sequence of $ n $ bumpers. The bumpers are numbered with integers from $ 1 $ to $ n $ from left to right. There are two types of bumpers. They are denoted by the characters '<' and '>'. When the ball hits the bumper at position $ i $ it goes one position to the right (to the position $ i+1 $ ) if the type of this bumper is '>', or one position to the left (to $ i-1 $ ) if the type of the bumper at position $ i $ is '<'. If there is no such position, in other words if $ i-1&lt;1 $ or $ i+1&gt;n $ , the ball falls from the game field.

Depending on the ball's starting position, the ball may eventually fall from the game field or it may stay there forever. You are given a string representing the bumpers' types. Calculate the number of positions such that the ball will eventually fall from the game field if it starts at that position.

## 说明/提示

In the first sample, the ball will fall from the field if starts at position $ 1 $ or position $ 2 $ .

In the second sample, any starting position will result in the ball falling from the field.

## 样例 #1

### 输入

```
4
<<><
```

### 输出

```
2```

## 样例 #2

### 输入

```
5
>>>>>```

### 输出

```
5```

## 样例 #3

### 输入

```
4
>><<
```

### 输出

```
0```

# AI分析结果



# Jumping Ball

## 题目描述

在弹球游戏的新版本中，游戏场地的核心部分由 $n$ 个缓冲器组成的序列构成。缓冲器从左到右依次编号为 $1$ 到 $n$，每个缓冲器有两种类型，分别用字符 '<' 和 '>' 表示。当球撞击位置 $i$ 的缓冲器时：若类型为 '>' 则向右移动到 $i+1$，若类型为 '<' 则向左移动到 $i-1$。当移动到 $i-1<1$ 或 $i+1>n$ 时，球会掉出场地。

给定缓冲器类型的字符串，计算有多少个起始位置能使球最终掉出场地。

## 说明/提示

样例1中，起始位置1和2会使球掉落。  
样例2中，所有位置都会使球掉落。  
样例3中，没有位置能使球掉落。

## 样例 #1

### 输入
```
4
<<><
```

### 输出
```
2
```

## 样例 #2

### 输入
```
5
>>>>>
```

### 输出
```
5
```

## 样例 #3

### 输入
```
4
>><<
```

### 输出
```
0
```

**算法分类**：模拟

---

### 题解综合分析

所有题解均基于以下关键观察：
1. **左侧连续 '<' 序列**：起始于这些位置的球会连续左移直至掉出左边界
2. **右侧连续 '>' 序列**：起始于这些位置的球会连续右移直至掉出右边界
3. **中间区域必然循环**：非两端连续序列的位置必然形成循环路径

#### 最优思路总结
直接统计左侧连续 '<' 的数量和右侧连续 '>' 的数量之和即为答案。该解法时间复杂度 O(n)，空间复杂度 O(1)，为理论最优解。

---

### 精选题解

#### 题解作者：Aragron_II（★★★★★）
**核心亮点**：
- 双指针遍历法简洁直观
- 代码仅需8行，无冗余逻辑
- 时间复杂度严格线性

**代码核心**：
```cpp
int main() {
    cin>>n>>st;
    int t=0;
    while(st[t]=='<') ans++,t++; // 统计左侧连续'<'
    t=n-1;
    while(st[t]=='>') ans++,t--; // 统计右侧连续'>'
    cout<<ans;
}
```

#### 题解作者：InversionShadow（★★★★☆）
**独特贡献**：
- 通过样例推导给出严格结论证明
- 代码变量命名规范，可读性强

**关键代码**：
```cpp
for(int i=0; i<n; ) {
    if(s[i]=='<') sum++,i++; // 左段扫描
    else break;
}
for(int i=n-1; i>=0; ) {
    if(s[i]=='>') sum++,i--; // 右段扫描
    else break;
}
```

#### 题解作者：xiaomuyun（★★★★☆）
**实现技巧**：
- 使用字符串下标直接访问
- 边界处理清晰

**代码片段**：
```cpp
for(int i=0; i<n; ++i){
    if(s[i]=='>') break;
    ++res; // 累计左侧
}
for(int i=n-1; i>=0; --i){
    if(s[i]=='<') break;
    ++res; // 累计右侧
}
```

---

### 拓展应用
1. **循环路径检测**：若题目允许更复杂的移动规则（如多步跳跃），需使用DFS/BFS+visited数组检测循环
2. **动态规划变体**：若缓冲器具有状态变化，可结合记忆化搜索

---

### 相似题目推荐
1. [CF1025D - 弹跳汉堡](https://codeforces.com/problemset/problem/1025/D)（循环路径检测）
2. [P1120 弹珠游戏](https://www.luogu.com.cn/problem/P1120)（路径模拟）
3. [P1510 传球游戏](https://www.luogu.com.cn/problem/P1510)（循环路径计数）

---

### 题解者心得摘录
"左侧连续的 '<' 和右侧连续的 '>' 是唯一能掉出的情况，中间必定形成闭环" —— Aragron_II  
"本题看似需要模拟，实则通过观察结构特征可直接计算" —— InversionShadow  
"最左端连续左移与最右端连续右移的简单相加即为答案" —— xiaomuyun

---
处理用时：67.27秒