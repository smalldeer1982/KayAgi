# 题目信息

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
14
```

## 样例 #3

### 输入

```
9 3
```

### 输出

```
14
```

## 样例 #4

### 输入

```
3 6
```

### 输出

```
12
```

## 样例 #5

### 输入

```
506 2708
```

### 输出

```
3218
```

# AI分析结果



### 题目重述
有一个由正方形瓷砖组成的无限大板子。你需要将恰好 $a$ 个瓷砖染红，$b$ 个染蓝，满足：
1. 所有染色瓷砖形成面积为 $a+b$ 的矩形
2. 红色或蓝色瓷砖至少有一种也形成矩形
求所有染色方案中最小周长。

### 题解分析与结论
所有题解均基于以下核心思路：
1. 枚举大矩形尺寸 $i \times \frac{a+b}{i}$，从 $\sqrt{a+b}$ 开始向下枚举以快速找到最小周长
2. 预存颜色块的因子，快速判断是否存在可嵌入的子矩形
3. 通过双指针或降序遍历优化因子匹配过程

最优思路：预处理颜色块的因子，枚举大矩形时利用双指针快速匹配最大可用因子，时间复杂度优化到 $O(\sqrt{a} + \sqrt{b} + \sqrt{a+b})$。

---

### 精选题解

#### 1. Siyuan（⭐⭐⭐⭐⭐）
**关键亮点**：
- 预处理因子后使用双指针优化匹配
- 分别处理红蓝两种颜色可能性
- 时间复杂度严格控制在 $O(\sqrt{a})$ 

**核心代码**：
```cpp
long long solve(long long tot,long long a) {
    std::vector<int> f;
    for(int i=1;1LL*i*i<=a;++i) if(a%i==0) f.push_back(i);
    int p=(int)f.size()-1;
    for(int i=sqrt(tot);i>=1;--i) {
        if(tot%i) continue;
        while(f[p]>i) --p;
        if(a/f[p]<=tot/i) return 2LL*(i+tot/i);
    }
    return 1LL<<60;
}
```
**实现思想**：
1. 预计算所有 $a$ 的因子存入数组
2. 倒序枚举大矩形宽度 $i$
3. 移动指针找到最大可用因子 $f[p] \leq i$
4. 验证高度是否满足条件

#### 2. Bring（⭐⭐⭐⭐）
**关键亮点**：
- 实时维护当前最大可用因子
- 代码极简（仅20行）
- 利用变量复用优化内存

**核心代码**：
```cpp
Frn_(i,sqrt(c),1)if(!(c%i)){
    f=min(f,i),g=min(g,i);
    while(a%f)--f; // 找到最大可用红因子
    if(a/f<=c/i)wr((i+c/i)<<1),exit(0);
    while(b%g)--g; // 找到最大可用蓝因子
    if(b/g<=c/i)wr((i+c/i)<<1),exit(0);
}
```
**实现思想**：
- 动态维护 $f,g$ 为当前最大可用因子
- 每次循环先限制因子不超过当前大矩形宽度
- 通过取余运算快速判断因子有效性

#### 3. BLUESKY007（⭐⭐⭐）
**关键亮点**：
- 直观的暴力检查方法
- 代码易于理解
- 预处理部分因子

**核心代码**：
```cpp
bool check(int u,long long v){
    for(int i=1;i<=u;i++){
        if(a%i==0 && a/i<=v) return true;
        if(b%i==0 && b/i<=v) return true;
    }
    return false;
}
```
**实现思想**：
- 直接枚举1到当前宽度所有数
- 检查是否能作为颜色块的宽度
- 时间复杂度较高但代码简单

---

### 关键技巧总结
1. **因子预处理**：提前计算颜色块的所有因子，避免重复计算
2. **降序枚举**：从 $\sqrt{a+b}$ 开始倒序查找，快速得到最小周长解
3. **双指针优化**：维护指针指向最大可用因子，将匹配复杂度降为 $O(1)$
4. **实时维护因子**：动态调整当前最大可用因子，减少无效判断

---

### 拓展训练
1. [CF449D - Jzzhu and Chocolate](https://codeforces.com/problemset/problem/449/D)（因子分解应用）
2. [洛谷 P1362 - 兔子数](https://www.luogu.com.cn/problem/P1362)（枚举优化）
3. [LeetCode 492 - Construct the Rectangle](https://leetcode.com/problems/construct-the-rectangle/)（周长最小化问题）

---

### 调试经验摘录
1. **Bring**："$f$ 在每次循环开始时应设为 $\min(f,i)$，否则会错过可用因子" → 强调因子范围动态调整的重要性
2. **Siyuan**："预处理因子后使用双指针，比每次重新计算快10倍以上" → 体现预处理的价值
3. **BLUESKY007**："先检查红色再检查蓝色，避免重复计算" → 流程顺序优化技巧

---
处理用时：50.15秒