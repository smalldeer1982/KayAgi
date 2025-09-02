# 题目信息

# Trails and Glades

## 题目描述

Vasya went for a walk in the park. The park has $ n $ glades, numbered from 1 to $ n $ . There are $ m $ trails between the glades. The trails are numbered from 1 to $ m $ , where the $ i $ -th trail connects glades $ x_{i} $ and $ y_{i} $ . The numbers of the connected glades may be the same $ (x_{i}=y_{i}) $ , which means that a trail connects a glade to itself. Also, two glades may have several non-intersecting trails between them.

Vasya is on glade 1, he wants to walk on all trails of the park exactly once, so that he can eventually return to glade 1. Unfortunately, Vasya does not know whether this walk is possible or not. Help Vasya, determine whether the walk is possible or not. If such walk is impossible, find the minimum number of trails the authorities need to add to the park in order to make the described walk possible.

Vasya can shift from one trail to another one only on glades. He can move on the trails in both directions. If Vasya started going on the trail that connects glades $ a $ and $ b $ , from glade $ a $ , then he must finish this trail on glade $ b $ .

## 说明/提示

In the first test case the described walk is possible without building extra trails. For example, let's first go on the first trail, then on the second one, and finally on the third one.

In the second test case the described walk is impossible without adding extra trails. To make the walk possible, it is enough to add one trail, for example, between glades number one and two.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 5
1 1
1 2
1 2
2 2
1 2
```

### 输出

```
1
```

# AI分析结果



### 算法分类
图论-欧拉回路、并查集、连通性分析

---

### 题解思路与难点对比

#### 核心思路
题目要求构造欧拉回路，需满足两个条件：
1. **所有顶点的度数为偶数**：通过统计奇数度顶点数目，两两配对添加边。
2. **图必须连通**：处理各个连通块，确保边数最小化。

#### 题解对比
1. **wucstdio 的题解**：
   - **要点**：分连通块处理，每个块内奇数顶点数目为偶数则需额外边。
   - **实现**：并查集统计连通块，计算奇数顶点数目。若块内无奇点则贡献1，否则贡献奇点数/2。
   - **难点**：处理连通块间的连接边时，通过奇点配对隐式完成。

2. **GalwayGirl 的题解**：
   - **要点**：将连通块分为奇偶两类，贡献为奇点数/2 + 偶块数目。
   - **实现**：DFS 统计奇偶块，特判单一偶块情况。
   - **难点**：偶块需额外连接成环，奇块利用保留顶点连接。

3. **i207M 的题解**：
   - **要点**：直接统计总奇点数/2 + 偶块数目 + 连通块数-1。
   - **实现**：DFS 标记连通块，优先处理奇点。
   - **难点**：偶块贡献1，奇块贡献奇点/2，快速合并答案。

#### 结论
所有题解核心均为处理奇点数目与连通性，区别在于对偶块的处理：
- **奇点块**：内部配对后保留两个顶点用于连接其他块。
- **偶块**：需额外添加一条边生成奇点，再与其他块连接。

最优思路为 **wucstdio** 的实现，结合并查集高效处理连通性，并正确分块计算贡献。

---

### 可视化算法分析

#### 关键步骤动画演示
1. **奇点处理**：
   - 遍历顶点，标记奇点（红色）。
   - 两两配对奇点（连线黄色），消去奇点。

2. **连通块处理**：
   - 并查集合并连通块（不同颜色区分）。
   - 若块内无奇点（蓝色块），添加一条边（绿色虚线）。

3. **整体连接**：
   - 不同块间通过保留的奇点连接（紫色边）。

#### 复古像素化设计
- **颜色方案**：奇点（红），偶点（蓝），连通块边界（绿），连接边（黄/紫）。
- **Canvas 绘制**：网格化顶点，逐步连线并播放 8-bit 音效。
- **自动演示**：按步骤高亮当前操作，如合并块时显示合并动画。

---

### 题解评分（≥4星）

1. **wucstdio（★★★★☆）**：
   - 思路清晰，正确分块处理。
   - 代码高效使用并查集，但注释较少。

2. **Milmon（★★★★☆）**：
   - 公式简洁，正确特判单偶块。
   - 代码可读性强，但DFS稍慢。

3. **Deamer（★★★★☆）**：
   - 结合连通块标记与度数统计。
   - 代码包含详细注释，适合理解。

---

### 核心代码实现（wucstdio）
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,pa[1000005],num[1000005],size[1000005];
bool d[1000005],flag[1000005];
int find(int x) { return x==pa[x]?x:pa[x]=find(pa[x]); }

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) pa[i]=i, size[i]=1;
    flag[1] = 1; // 标记1号点必须访问
    for(int i=1;i<=m;i++) {
        int u,v; scanf("%d%d",&u,&v);
        d[u] ^= 1; d[v] ^= 1; // 度数奇偶性取反
        int x=find(u), y=find(v);
        if(x != y) { // 并查集合并
            if(size[x] > size[y]) swap(x,y);
            pa[x] = y; size[y] += size[x];
        }
        flag[y] = 1; // 标记连通块存在边
    }
    
    int rest=0; // 有效连通块数目（包含边或1号点）
    for(int i=1;i<=n;i++) 
        if(i==find(i) && flag[find(i)]) rest++;
    if(!flag[find(1)]) rest++; // 处理1号点孤立的情况
    
    for(int i=1;i<=n;i++) if(d[i]) num[find(i)]++; // 统计各块奇点数
    
    if(rest == 1) { // 单一连通块直接输出奇点/2
        printf("%d\n", num[find(1)]/2);
        return 0;
    }
    
    int ans=0;
    for(int i=1;i<=n;i++) {
        if(find(i)==i && flag[i]) {
            ans += num[i] >> 1; // 奇点贡献
            if(num[i] == 0) ans++; // 偶块贡献1
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

### 相似题目推荐
1. **洛谷 P2731 骑马修栅栏**（欧拉路径）
2. **洛谷 P1341 无序字母对**（欧拉回路构造）
3. **洛谷 P3520 最短路径问题**（连通性+最短路）

---
处理用时：430.38秒