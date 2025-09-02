# 题目信息

# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3
```

### 输出

```
8
```

# AI分析结果



---

## 算法分类
**点分治**

---

## 综合分析与结论

### 核心思路
题目要求在树中统计满足路径数字组合能被 M 整除的有序点对。由于树形结构特性，核心解法为点分治：
1. **分治中心处理**：每次选择树的重心作为分治中心，统计经过该点的所有路径。
2. **路径表示与变形**：
   - 预处理 10 的幂次和逆元，计算每个节点到分治中心的顺读（`dis_down`）和逆读（`dis_up`）数字的模值。
   - 变形模方程：将路径拼接条件转化为 `dis_up[u] ≡ -dis_down[v] * inv_10^(dep[v])`，利用哈希表快速匹配。
3. **容斥优化**：通过遍历子树前先统计贡献再累加，避免重复计算同一子树内的路径。

### 解决难点
- **模运算处理**：利用扩展欧几里得求逆元（因 M 不保证为质数）。
- **路径拼接公式推导**：将树路径转化为可分离计算的模方程，是点分治实现的关键。
- **数据结构优化**：使用 `map` 或哈希表存储中间结果，实现 O(1) 查询匹配路径数。

---

## 题解清单 (≥4星)

1. **MikukuOvO（5星）**
   - **亮点**：点分治思路清晰，代码简洁，预处理逆元和幂次模块化，容斥处理直接。
   - **关键代码**：`calc` 函数通过两次遍历避免重复统计。

2. **xfrvq（4.5星）**
   - **亮点**：公式推导详细，强调逆元处理，代码可读性强。
   - **心得**：明确说明使用 `map` 替代哈希表避免 TLE。

3. **Register_int（4星）**
   - **亮点**：代码结构规范，包含完整点分治框架和逆元预处理，适合学习实现。
   - **优化**：使用 `vector` 存储子树节点，减少内存开销。

---

## 核心代码实现

### 预处理逆元与幂次
```cpp
void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) x=1, y=0;
    else exgcd(b, a%b, y, x), y -= a/b*x;
}
ll inv(ll a) {
    ll x, y; exgcd(a, mod, x, y);
    return (x%mod + mod) % mod;
}
p10[0] = 1;
for (int i=1; i<=n; i++) 
    p10[i] = p10[i-1] * 10 % mod;
inv10[n] = inv(p10[n]);
for (int i=n-1; i>=0; i--)
    inv10[i] = inv10[i+1] * 10 % mod;
```

### 点分治核心逻辑
```cpp
void calc(int u) {
    map<ll, ll> mp;
    // 遍历子树统计贡献
    for (auto v : tree[u]) {
        vector<tuple<ll, ll>> paths;
        dfs(v, u, 0, 0, 0, paths); // 收集所有路径
        for (auto [a, dep] : paths) {
            ll key = (-a * inv10[dep]) % mod;
            ans += mp[(key + mod) % mod];
        }
        for (auto [a, dep] : paths) {
            ll val = a % mod;
            mp[val]++;
        }
    }
}
```

---

## 同类型题与推荐
1. **P2634 [国家集训队] 聪聪可可**  
   - 统计树上路径长度模 3 为 0 的点对数量，点分治模板题。

2. **P4178 Tree**  
   - 统计路径权值 ≤k 的点对数量，点分治结合双指针或排序。

3. **P4149 [IOI2011]Race**  
   - 求权值和为 k 的最短路径边数，点分治维护路径权值映射。

---

## 可视化设计

### 算法演示（Canvas动画）
- **分治中心高亮**：红色标记当前分治重心，子树用不同颜色区分。
- **路径追踪**：点击节点展示其到分治中心的顺读/逆读数值，动态显示哈希表插入与查询。
- **公式推导面板**：右侧展示当前路径的模方程变形过程，颜色标注匹配键值。

### 复古像素风格
- **8位树形结构**：节点以像素方块表示，边为绿色线条，分治中心闪烁。
- **音效反馈**：
  - **路径匹配成功**：短促“叮”声（C4音符）。
  - **分治完成**：播放 8-bit 胜利音效。
- **自动演示**：按空格键进入自动分治流程，AI 逐步选择重心并统计路径。

---

## 个人心得摘录
- **逆元处理误区**：某题解因误用费马小定理导致 WA，改用扩展欧几里得后通过。
- **调试技巧**：通过小数据验证路径拼接公式，确保模运算正确性。
- **优化经验**：使用 `unordered_map` 在 CF 平台易 TLE，改用排序 + 双指针或 `map` 更稳定。

---

**通过点分治的高效分解与模运算的巧妙变形，该问题得以优雅解决，是树分治与数论结合的经典案例。**

---
处理用时：74.13秒