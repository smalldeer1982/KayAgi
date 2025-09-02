# 题目信息

# Bear and Forgotten Tree 3

## 题目描述

A tree is a connected undirected graph consisting of $ n $ vertices and $ n-1 $ edges. Vertices are numbered $ 1 $ through $ n $ .

Limak is a little polar bear and Radewoosh is his evil enemy. Limak once had a tree but Radewoosh stolen it. Bear is very sad now because he doesn't remember much about the tree — he can tell you only three values $ n $ , $ d $ and $ h $ :

- The tree had exactly $ n $ vertices.
- The tree had diameter $ d $ . In other words, $ d $ was the biggest distance between two vertices.
- Limak also remembers that he once rooted the tree in vertex $ 1 $ and after that its height was $ h $ . In other words, $ h $ was the biggest distance between vertex $ 1 $ and some other vertex.

The distance between two vertices of the tree is the number of edges on the simple path between them.

Help Limak to restore his tree. Check whether there exists a tree satisfying the given conditions. Find any such tree and print its edges in any order. It's also possible that Limak made a mistake and there is no suitable tree – in this case print "-1".

## 说明/提示

Below you can see trees printed to the output in the first sample and the third sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639B/d620db1cf9f574a403a626cbbf75f44f3128c4d9.png)

## 样例 #1

### 输入

```
5 3 2
```

### 输出

```
1 2
1 3
3 4
3 5```

## 样例 #2

### 输入

```
8 5 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8 4 2
```

### 输出

```
4 8
5 7
2 3
8 1
2 1
5 6
1 5
```

# AI分析结果



# Bear and Forgotten Tree 3（中文翻译）

## 题目描述
一棵树是由 $n$ 个顶点和 $n-1$ 条边组成的连通无向图，顶点编号为 $1$ 到 $n$。已知三个参数 $n$，$d$，$h$：
1. 树有恰好 $n$ 个顶点
2. 树的直径为 $d$（任意两顶点间最长路径）
3. 以顶点 1 为根时树的高度为 $h$（根到最远顶点的距离）

判断是否存在这样的树，若存在输出任意符合条件的边集，否则输出 -1。

## 输入输出样例
样例 #1 输入：5 3 2  
样例 #1 输出：4条边构成的树  
样例 #2 输入：8 5 2 → 输出：-1

---

**算法分类**：构造

---

### 题解综合分析
各题解均采用构造两条链的思路：  
1. **无解条件**：d > 2h（直径超出高度两倍）、d=1且h=1时n>2  
2. **构造核心**：先构建高度链（1→h+1），再构建直径延长链（1→h+2→d+1）  
3. **剩余节点**：当d=h时挂在中间节点，否则挂在根节点  

**关键难点**：直径与高度的数学关系约束，剩余节点的合理放置不影响原有结构

---

### 精选题解（评分≥4⭐）

#### 1. 樱雪喵（5⭐）
**亮点**：  
- 代码简洁优雅，逻辑清晰  
- 采用分层构造思想，处理剩余节点的逻辑简明  
**核心代码**：
```cpp
for(int i=2;i<=h+1;i++) cout<<i-1<<" "<<i<<endl;  // 构造高度链
for(int i=h+2;i<=d+1;i++) cout<<((i==h+2)?1:i-1)<<" "<<i<<endl;  // 构造直径延长链
for(int i=d+2;i<=n;i++) cout<<((d==h)?2:1)<<" "<<i<<endl;  // 剩余节点处理
```

#### 2. fuxuantong123（4⭐）
**亮点**：  
- 变量命名直观，逻辑分层明确  
- 特别处理d>h的情况分支  
**核心逻辑**：  
```cpp
// 构造高度链
for(int i=1;i<h;i++) printf("%d %d\n",i,i+1);  
// 构造直径延长链
if(d>h) printf("1 %d\n",h+2);  
// 剩余节点统一挂在h节点
for(int i=d+2;i<=n;i++) printf("%d %d\n",h,i);
```

#### 3. wgyhm（4⭐）
**亮点**：  
- 注释清晰，数学约束处理完整  
- 使用统一逻辑处理剩余节点  
**核心代码**：  
```cpp
if(d>h) {  // 构造直径延长链
    printf("1 %d\n",h+2);
    for(int i=h+3;i<=d+1;i++) printf("%d %d\n",i-1,i);
}
for(int i=d+2;i<=n;i++) printf("%d %d\n",h,i);  // 剩余节点处理
```

---

### 最优技巧总结
1. **双链构造法**：通过构建高度链和直径延长链满足核心约束
2. **数学约束判断**：d ≤ 2h 是构造可行的充要条件
3. **剩余节点处理**：当d=h时挂到第二层节点，其他情况挂根节点
4. **特判优先**：处理边界条件如n=2、d=1等极端情况

---

### 拓展训练
1. [P1099 树网的核](https://www.luogu.com.cn/problem/P1099)（树的直径性质）
2. [P5536 核心城市](https://www.luogu.com.cn/problem/P5536)（树的构造与中心选择）
3. [P3629 巡逻](https://www.luogu.com.cn/problem/P3629)（树的最长路径处理）

---

### 题解心得摘录
- **调试教训**：多篇题解强调特判d=1且h=1时n>2的情况（易漏边界）  
- **顿悟感想**：将树分解为高度链和直径延长链的构造法具有普适性  
- **实现技巧**：使用链式构造的循环结构能简化代码逻辑

---
处理用时：55.62秒