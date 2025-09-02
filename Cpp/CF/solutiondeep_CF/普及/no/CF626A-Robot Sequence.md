# 题目信息

# Robot Sequence

## 题目描述

Calvin the robot lies in an infinite rectangular grid. Calvin's source code contains a list of $ n $ commands, each either 'U', 'R', 'D', or 'L' — instructions to move a single square up, right, down, or left, respectively. How many ways can Calvin execute a non-empty contiguous substrings of commands and return to the same square he starts in? Two substrings are considered different if they have different starting or ending indices.

## 说明/提示

In the first case, the entire source code works, as well as the "RL" substring in the second and third characters.

Note that, in the third case, the substring "LR" appears three times, and is therefore counted three times to the total result.

## 样例 #1

### 输入

```
6
URLLDR
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
DLUU
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7
RLRLRLR
```

### 输出

```
12
```

# AI分析结果



# Robot Sequence

## 题目描述

Calvin机器人位于无限大的矩形网格中。其源代码包含n个命令，每个命令为'U'、'R'、'D'或'L'，分别表示向上、右、下、左移动一格。求有多少个非空连续子命令串，使得执行后机器人回到起点。不同起始或结束位置的子串视为不同。

## 说明/提示

样例1中整个字符串有效，且第二、三字符构成的"RL"有效。样例3中"LR"出现三次，被计数三次。

---

**算法分类**：枚举、前缀和

---

### 题解分析与结论

所有题解均围绕如何高效统计满足条件的子串展开，核心思路为：
1. **必要条件**：子串中U与D数量相等，L与R数量相等
2. **暴力枚举**：三重循环枚举起点、终点并统计字符，时间复杂度O(n³)
3. **优化方向**：通过逐步累加或前缀和将复杂度降至O(n²)

---

### 高分题解推荐

#### 1. WsW_（优化累加法） ★★★★☆
**亮点**：  
- 外层枚举起点，内层动态维护方向计数
- 逐步扩展子串时增量更新，避免重复计算
- 代码简洁，空间优化（仅用4个变量）

核心代码：
```cpp
for(int i=0;i<n;i++){
    for(int j=i;j<n;j++){
        if(ch[j]=='U')a[1]++;
        // 其他方向同理...
        if(a[1]==a[2]&&a[3]==a[4])ans++;
    }
    memset(a,0,sizeof(a)); // 起点变更时重置
}
```

#### 2. Daniel_yao（坐标模拟法） ★★★★☆  
**亮点**：  
- 实时维护坐标而非方向计数
- 逻辑直观，便于调试
- 显式处理坐标归零判断

核心代码：
```cpp
for(int i=1;i<=n;i++){
    int x=0, y=0;
    for(int j=i;j<=n;j++){
        if(s[j]=='U')x++;
        // 其他方向处理...
        ans += (x==0 && y==0);
    }
}
```

#### 3. codeLJH114514（前缀和法） ★★★★  
**亮点**：  
- 预处理四个方向的前缀和数组
- 查询子串时直接O(1)计算差值
- 适合多次查询场景的可扩展性

核心实现：
```cpp
// 预处理前缀和
for(int i=0;i<n;i++) 
    for(int j=1;j<=4;j++)
        cnt[j][i] = cnt[j][i-1] + (s[i]==letter[j]);

// 查询时
if(Count(U) == Count(D) && Count(L) == Count(R)) 
    ans++;
```

---

### 关键技巧总结

1. **增量统计**：枚举起点后逐步扩展终点，避免重复计算子串
2. **状态复用**：利用前缀和或实时坐标维护，降低时间复杂度
3. **条件转化**：将返回原点转化为方向计数的数学约束

---

### 同类题目推荐

1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147) - 连续区间和问题
2. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102) - 统计满足条件的配对
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406) - 差分与前缀和的综合应用

---

### 题解心得摘录

> "外层枚举起点后，内层只需线性扫描终点并维护状态，将三次方优化为平方" —— GossWandering  
> "实时计算坐标比统计方向更直观，减少变量数量" —— Daniel_yao  
> "前缀和数组虽然需要预处理，但能极大提升查询效率" —— codeLJH114514

---
处理用时：67.85秒