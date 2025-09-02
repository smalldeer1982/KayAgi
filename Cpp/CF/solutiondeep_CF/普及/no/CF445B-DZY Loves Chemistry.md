# 题目信息

# DZY Loves Chemistry

## 题目描述

DZY loves chemistry, and he enjoys mixing chemicals.

DZY has $ n $ chemicals, and $ m $ pairs of them will react. He wants to pour these chemicals into a test tube, and he needs to pour them in one by one, in any order.

Let's consider the danger of a test tube. Danger of an empty test tube is $ 1 $ . And every time when DZY pours a chemical, if there are already one or more chemicals in the test tube that can react with it, the danger of the test tube will be multiplied by $ 2 $ . Otherwise the danger remains as it is.

Find the maximum possible danger after pouring all the chemicals one by one in optimal order.

## 说明/提示

In the first sample, there's only one way to pour, and the danger won't increase.

In the second sample, no matter we pour the $ 1 $ st chemical first, or pour the $ 2 $ nd chemical first, the answer is always $ 2 $ .

In the third sample, there are four ways to achieve the maximum possible danger: 2-1-3, 2-3-1, 1-2-3 and 3-2-1 (that is the numbers of the chemicals in order of pouring).

## 样例 #1

### 输入

```
1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1
1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 2
1 2
2 3
```

### 输出

```
4
```

# AI分析结果



# DZY Loves Chemistry

## 题目描述

DZY 喜欢化学，他热衷于混合各种化学物质。

DZY 有 $n$ 种化学物质，其中有 $m$ 对物质会发生反应。他需要将这些物质依次倒入试管中，倒入顺序可以任意安排。

试管的初始危险值为 $1$。每次倒入一种化学物质时，如果试管中已存在至少一种能与该物质反应的物质，则危险值会乘以 $2$，否则危险值不变。

求倒入所有化学物质后，可能达到的最大危险值。

## 样例 #1

### 输入
```
1 0
```

### 输出
```
1
```

## 样例 #2

### 输入
```
2 1
1 2
```

### 输出
```
2
```

## 样例 #3

### 输入
```
3 2
1 2
2 3
```

### 输出
```
4
```

---

**算法分类**：并查集

---

## 题解综合分析

### 最优思路总结
核心思路是**将反应关系视为连通性关系**，通过统计有效合并次数或计算连通块数量来推导危险值：
1. **并查集统计有效边**：每次合并两个不同连通块时，危险值翻倍。最终危险值为 $2^{有效合并次数}$
2. **连通块公式法**：若最终形成 $s$ 个连通块，则危险值为 $2^{n-s}$。每个连通块大小为 $k$ 时贡献 $k-1$ 次翻倍，总次数为 $\sum (k_i-1) = n-s$

### 高星题解推荐

#### 题解作者：aeiouaoeiu（★★★★★）
**核心亮点**：  
- 通过图的连通块数量直接计算答案 $2^{n-s}$，时间复杂度 $O(n+m)$  
- 数学推导清晰，代码简洁高效  
**关键代码**：
```cpp
void dfs(ll u){
    vis[u]=1;
    for(auto v:edge[u]) if(!vis[v]) dfs(v);
}

// 主逻辑
for(int i=1;i<=n;i++) if(!vis[i]) s++, dfs(i);
cout<<(1ll<<(n-s))<<"\n";
```

#### 题解作者：GeChang（★★★★☆）
**核心亮点**：  
- 使用并查集统计有效合并次数  
- 代码结构清晰，适合并查集入门学习  
**关键代码**：
```cpp
ll root_x=getroot(x), root_y=getroot(y);
if(root_x != root_y) {
    p[root_x] = root_y;
    wei *= 2;
}
```

#### 题解作者：codeLJH114514（★★★★☆）
**核心亮点**：  
- 明确推导出公式 $2^{有效合并次数}$  
- 代码包含路径压缩和按秩合并优化  
**关键代码**：
```cpp
void Union(int x, int y) {
    x = Root(x), y = Root(y);
    if(s[x] > s[y]) swap(x,y);
    f[x] = y, s[y] += s[x];
}
```

---

## 关键实现技巧
1. **并查集路径压缩**：优化查找根节点效率  
2. **按秩合并**：保持树结构的平衡性  
3. **位运算加速**：用 `1ll << k` 代替 `pow(2,k)` 避免浮点误差  
4. **连通块公式**：直接计算 $2^{n-s}$ 避免逐次乘法  

---

## 拓展训练
1. [P1551 亲戚](https://www.luogu.com.cn/problem/P1551) - 基础并查集应用  
2. [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197) - 逆向连通块维护  
3. [P2502 [HAOI2006] 旅行](https://www.luogu.com.cn/problem/P2502) - 图连通性结合最值问题  

---

## 题解心得摘录
- **aeiouaoeiu**："危险值的计算实际等价于每个连通块的生成树边数"  
- **青龍剑**："第三组数据启发我们，反应关系具有传递性，这正是并查集擅长的领域"  
- **codeLJH114514**："注意 $2^{49}$ 会超出 32 位整数范围，必须使用 64 位整型"

---
处理用时：53.95秒