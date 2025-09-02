# 题目信息

# Nice Garland

## 题目描述

You have a garland consisting of $ n $ lamps. Each lamp is colored red, green or blue. The color of the $ i $ -th lamp is $ s_i $ ('R', 'G' and 'B' — colors of lamps in the garland).

You have to recolor some lamps in this garland (recoloring a lamp means changing its initial color to another) in such a way that the obtained garland is nice.

A garland is called nice if any two lamps of the same color have distance divisible by three between them. I.e. if the obtained garland is $ t $ , then for each $ i, j $ such that $ t_i = t_j $ should be satisfied $ |i-j|~ mod~ 3 = 0 $ . The value $ |x| $ means absolute value of $ x $ , the operation $ x~ mod~ y $ means remainder of $ x $ when divided by $ y $ .

For example, the following garlands are nice: "RGBRGBRG", "GB", "R", "GRBGRBG", "BRGBRGB". The following garlands are not nice: "RR", "RGBG".

Among all ways to recolor the initial garland to make it nice you have to choose one with the minimum number of recolored lamps. If there are multiple optimal solutions, print any of them.

## 样例 #1

### 输入

```
3
BRB
```

### 输出

```
1
GRB
```

## 样例 #2

### 输入

```
7
RGBGRBB
```

### 输出

```
3
RGBRGBR
```

# AI分析结果



# 优美花环

## 题目描述

你有一个由 $n$ 盏灯组成的花环。每盏灯颜色为红色（'R'）、绿色（'G'）或蓝色（'B'）。需要重新染色若干盏灯，使得最终的花环满足：任意两盏同色灯的位置差必须是 3 的倍数。求最少需要重新染色的灯数，并输出任意一种最优方案。

## 样例 #1

### 输入
```
3
BRB
```

### 输出
```
1
GRB
```

## 样例 #2

### 输入
```
7
RGBGRBB
```

### 输出
```
3
RGBRGBR
```

---

**算法分类**：枚举

---

## 题解综合分析

题目要求构造周期为3的循环序列。核心思路是枚举所有可能的3字符排列（共6种），计算每种排列的修改次数。最优解必定是这6种排列循环展开后修改次数最少的情况。

### 精选题解

#### 1. MattL 题解（⭐⭐⭐⭐⭐）
**亮点**：代码简洁高效，直接使用模3运算匹配循环模式  
**关键思路**：
- 预定义6种可能的循环模式
- 遍历每个字符比较差异计数
- 时间复杂度 O(6n) 完全可接受

```cpp
string mb[] = {"RGB","RBG","BRG","BGR","GBR","GRB"};
for(int u=0;u<6;u++) {
    cnt = 0;
    for(int i=0;i<s.size();i++)
        cnt += (s[i] != mb[u][i%3]);
    // 更新最小值...
}
```

#### 2. _louhc 题解（⭐⭐⭐⭐）
**亮点**：利用 STL 的 `next_permutation` 生成排列  
**技巧**：通过整数映射颜色，简化比较逻辑
```cpp
do {
    a1 = m[0]对应的颜色; // 类似代码省略
    // 分三类处理余数位置...
} while(next_permutation(m, m+3));
```

#### 3. fsy_juruo 题解（⭐⭐⭐）
**亮点**：DFS生成全排列，适合教学演示  
**不足**：实现稍显复杂，效率略低
```cpp
void dfs(int step) {
    if(step > 3) {
        // 计算差异数...
    }
    // 递归生成排列...
}
```

---

## 关键思路总结
1. **循环模式枚举**：问题可规约为寻找最优的3字符循环基模式
2. **模运算匹配**：利用 `i%3` 快速对应循环位置
3. **差异计数优化**：通过线性扫描统计差异，时间复杂度最优

---

## 拓展训练
1. [CF978E](https://www.luogu.com.cn/problem/CF978E) - 类似的位置约束问题
2. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706) - 排列生成基础
3. [CF1295B](https://www.luogu.com.cn/problem/CF1295B) - 周期性模式应用

---

## 题解心得摘录
- **MattL**：认识到循环基长度固定是突破口  
- **da32s1da**：预处理余数位置的颜色统计加速计算  
- **Zechariah**：通过暴力DFS验证了问题的全排列特性  

> "问题突破口在于发现最终序列必须呈现严格的3周期特征" —— 摘自某题解调试心得

---
处理用时：42.90秒