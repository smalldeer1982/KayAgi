# 题目信息

# Round Table Knights

## 题目描述

There are $ n $ knights sitting at the Round Table at an equal distance from each other. Each of them is either in a good or in a bad mood.

Merlin, the wizard predicted to King Arthur that the next month will turn out to be particularly fortunate if the regular polygon can be found. On all vertices of the polygon knights in a good mood should be located. Otherwise, the next month will bring misfortunes.

A convex polygon is regular if all its sides have same length and all his angles are equal. In this problem we consider only regular polygons with at least 3 vertices, i. e. only nondegenerated.

On a picture below some examples of such polygons are present. Green points mean knights in a good mood. Red points mean ones in a bad mood.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF71C/05771d25f3570e788948383d5e55e90ca186c9da.png)King Arthur knows the knights' moods. Help him find out if the next month will be fortunate or not.

## 样例 #1

### 输入

```
3
1 1 1
```

### 输出

```
YES```

## 样例 #2

### 输入

```
6
1 0 1 1 1 0
```

### 输出

```
YES```

## 样例 #3

### 输入

```
6
1 0 0 1 0 1
```

### 输出

```
NO```

# AI分析结果



### 题目内容重写

# 圆桌骑士

## 题目描述

$ n $ 位骑士围坐在圆桌旁，彼此间距相等。每位骑士处于好心情（1）或坏心情（0）。

梅林预言下个月将是幸运的，当且仅当能找到所有顶点都是好心情骑士组成的正多边形。否则下个月将充满不幸。

凸多边形是正则的当且仅当所有边等长且所有角相等。本题中仅考虑顶点数 ≥3 的非退化正多边形。

帮助亚瑟王根据骑士心情判断未来是否幸运。

## 输入输出样例

样例 #1：
输入：
3
1 1 1
输出：
YES

样例 #2：
输入：
6
1 0 1 1 1 0
输出：
YES

样例 #3：
输入：
6
1 0 0 1 0 1
输出：
NO

---

### 算法分类
**数学**

---

### 题解对比分析

**共同思路**：
1. 正多边形的顶点数必须是 n 的因数
2. 枚举所有可能的因数（≥3），检查是否存在符合条件的顶点分布
3. 通过因数成对特性优化枚举到√n

**差异对比**：
- AKPC 和 lightningZ 的题解通过分解因数时同时处理 i 和 n/i，确保覆盖所有可能情况
- qingchenMC 显式处理了环状结构的遍历问题
- 部分题解错误处理因数范围（如枚举到 n/2 而非 √n）

---

### 高分题解推荐

#### 1. AKPC（5星）
**关键亮点**：
- 因数成对处理，时间复杂度最优
- 边界条件处理严谨（排除边数≤2的情况）
- 代码简洁清晰，逻辑模块化

**核心代码**：
```cpp
int check(int x) {
    for (int i=1; i<=n/x; i++) 
        if (ok(i, n/x)) return 1;
    return 0;
}
// 主枚举逻辑
for (int i=1; i*i<=n; i++) {
    if (n%i==0 && ((check(i)&&i>=3) || (check(n/i)&&n/i>=3))) {
        cout << "YES";
        return 0;
    }
}
```

#### 2. lightningZ（4.5星）
**关键亮点**：
- 变量命名更直观（ZDX→判断函数）
- 显式注释增强可读性
- 完全匹配题目数学特性

**个人心得**：
> "注意边数必须 ≥3 的约束，这是容易被忽略的边界条件"

#### 3. qingchenMC（4星）
**关键亮点**：
- 显式处理环状遍历问题
- 双重检查机制确保正确性
- 代码注释详细

**优化点**：
```cpp
for(int j=1; j<=x; j++) { // 枚举所有可能起点
    bool flag = true;
    for(int k=j; k<=n; k+=x) // 环状检查
        if(!c[k]) flag = false;
    if(flag) return true;
}
```

---

### 最优思路总结
1. **因数分解**：通过√n枚举法快速获取所有可能边数
2. **环形验证**：对每个可能的边数，检查所有起点对应的顶点序列
3. **剪枝优化**：跳过边数≤2的无效情况，减少无效计算

---

### 拓展思考
- **同型问题**：环形数组的周期性验证问题（如[CF_1343B](https://codeforces.com/problemset/problem/1343/B)）
- **优化方向**：预处理所有因数后再检查，减少重复计算
- **变式思考**：若允许非凸多边形时的解法差异

---

### 推荐习题
1. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)（因数分解应用）
2. [CF_1027B](https://codeforces.com/problemset/problem/1027/B)（环状结构数学问题）
3. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)（因数分解基础）

---
处理用时：104.31秒