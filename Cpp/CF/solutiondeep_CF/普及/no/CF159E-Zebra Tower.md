# 题目信息

# Zebra Tower

## 题目描述

Little Janet likes playing with cubes. Actually, she likes to play with anything whatsoever, cubes or tesseracts, as long as they are multicolored. Each cube is described by two parameters — color $ c_{i} $ and size $ s_{i} $ . A Zebra Tower is a tower that consists of cubes of exactly two colors. Besides, the colors of the cubes in the tower must alternate (colors of adjacent cubes must differ). The Zebra Tower should have at least two cubes. There are no other limitations. The figure below shows an example of a Zebra Tower.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF159E/f33171cfff84c23150eb82e578a37293690a12de.png)A Zebra Tower's height is the sum of sizes of all cubes that form the tower. Help little Janet build the Zebra Tower of the maximum possible height, using the available cubes.

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
3 3
```

### 输出

```
9
3
2 3 1 
```

## 样例 #2

### 输入

```
2
1 1
2 1
```

### 输出

```
2
2
2 1 
```

# AI分析结果



# Zebra Tower

## 题目描述

小珍妮特喜欢玩立方体。实际上，只要是多色的物体，无论是立方体还是超立方体，她都喜欢。每个立方体有两个参数——颜色 $c_i$ 和大小 $s_i$。斑马塔是由恰好两种颜色的立方体组成的塔，且相邻立方体的颜色必须不同。斑马塔至少需要两个立方体。目标是构造高度（所有立方体大小之和）最大的斑马塔。

---

**算法分类**：贪心

---

## 题解综合分析

### 核心思路
1. **颜色分组排序**：将相同颜色立方体按大小降序排列，颜色组按元素数量降序排列
2. **前缀和优化**：预处理每个颜色前k个元素的和，维护每个长度下的最大价值
3. **交替匹配**：枚举每个颜色组，找到能与之形成最佳交替排列的互补颜色组

### 最优解法要点
- **贪心排序**：确保优先处理数量多的颜色组，提升匹配效率
- **动态维护最大值**：使用前缀和数组记录各长度下的最大价值及对应颜色
- **边界处理**：精确处理两颜色组长度相等或相差1的交替排列情况

---

## 精选题解

### 题解作者：7KByte（⭐⭐⭐⭐）
**关键亮点**：
- 创新性地使用颜色组排序规则（数量优先，大小降序）
- 通过前缀和数组实现快速价值匹配
- 完整处理输出序列构造逻辑

**核心代码思路**：
```cpp
struct node{
    int c,s,op;
    bool operator<(const node o)const{
        if(h[c] != h[o.c]) return h[c] > h[o.c]; // 颜色数量优先
        if(c != o.c) return c < o.c;             // 颜色编号次之
        return s > o.s;                          // 同颜色按大小降序
    }
};
// 预处理颜色组边界
rep(i,2,n) if(u[i].c != u[i-1].c) {
    ll[u[i-1].c] = pre;
    rr[u[i-1].c] = i-1;
    calc(pre, i-1);  // 计算该颜色组的前缀和
    pre = i;
}
```

**实现技巧**：
- 使用`map`维护颜色出现次数，确保排序正确性
- 通过`c[i]`数组记录选择i个立方体的最大价值及对应颜色
- 在`calc`函数中同时处理长度相等和相差1的情况

---

## 同类题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略
2. [P3819 线段覆盖](https://www.luogu.com.cn/problem/P3819) - 排序与贪心结合
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 交替覆盖处理

---

## 关键思路总结
1. **排序策略**：双关键字排序（颜色组大小→单元素大小）是解法的基石
2. **前缀和优化**：通过预处理每个颜色组的前缀和，快速计算匹配价值
3. **交替构造**：通过维护两种颜色组的长度关系，确保形成合法斑马塔

该解法展现了如何将复杂条件转化为可计算的数学模型，体现了贪心策略与预处理技巧的有机结合。

---
处理用时：56.13秒